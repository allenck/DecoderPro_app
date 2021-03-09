#include "location.h"
#include "physicallocation.h"
#include <QVector>
#include "stringutil.h"
#include "track.h"
#include "xml.h"
#include "setup.h"
#include "operationsxml.h"
#include "instancemanager.h"
#include "reporter.h"
#include "reportermanager.h"
#include "rollingstock.h"
#include <QComboBox>
#include "cartypes.h"
#include "carroads.h"
#include "enginetypes.h"
#include "control.h"
#include <QDomElement>
#include "physicallocation.h"
#include "pool.h"
#include "locationmanagerxml.h"
#include "carload.h"
#include "vptr.h"

//Location::Location(QObject *parent) :
//  QObject(parent)
//{
//}
/**
* Represents a location on the layout
*
* @author Daniel Boudreau Copyright (C) 2008, 2012, 2013
* @version $Revision: 29681 $
*/
///*public*/ class Location implements java.beans.PropertyChangeListener {
namespace Operations
{
 /*public*/ /*static*/ /*final*/ QString Location::NONE = "";


 /*public*/ /*static*/ /*final*/ int Location::NORMAL = 1; // types of track allowed at this location
 /*public*/ /*static*/ /*final*/ int Location::STAGING = 2; // staging only

 /*public*/ /*static*/ /*final*/ int Location::EAST = 1; // train direction serviced by this location
 /*public*/ /*static*/ /*final*/ int Location::WEST = 2;
 /*public*/ /*static*/ /*final*/ int Location::NORTH = 4;
 /*public*/ /*static*/ /*final*/ int Location::SOUTH = 8;

 // Switch list status
 /*public*/ /*static*/ /*final*/ QString Location::UNKNOWN = "";
 /*public*/ /*static*/ /*final*/ QString Location::PRINTED = tr("Printed");
 /*public*/ /*static*/ /*final*/ QString Location::CSV_GENERATED = tr("CsvGenerated");
 /*public*/ /*static*/ /*final*/ QString Location::MODIFIED = tr("Modified");
 /*public*/ /*static*/ /*final*/ QString Location::UPDATED = tr("Updated");

 // Switch list states
 /*public*/ /*static*/ /*final*/ int Location::SW_CREATE = 0; // create new switch list
 /*public*/ /*static*/ /*final*/ int Location::SW_APPEND = 1; // append train into to switch list
 /*public*/ /*static*/ /*final*/ int Location::SW_PRINTED = 2; // switch list printed

 // For property change
 /*public*/ /*static*/ /*final*/ QString Location::TRACK_LISTLENGTH_CHANGED_PROPERTY = "trackListLength"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Location::TYPES_CHANGED_PROPERTY = "locationTypes"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Location::TRAINDIRECTION_CHANGED_PROPERTY = "locationTrainDirection"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Location::LENGTH_CHANGED_PROPERTY = "locationTrackLengths"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Location::USEDLENGTH_CHANGED_PROPERTY = "locationUsedLength"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Location::NAME_CHANGED_PROPERTY = "locationName"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Location::SWITCHLIST_CHANGED_PROPERTY = "switchList"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Location::DISPOSE_CHANGED_PROPERTY = "locationDispose"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Location::STATUS_CHANGED_PROPERTY = "locationStatus"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Location::POOL_LENGTH_CHANGED_PROPERTY = "poolLengthChanged"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Location::SWITCHLIST_COMMENT_CHANGED_PROPERTY = "switchListComment";// NOI18N
 /*public*/ /*static*/ /*final*/ QString Location::TRACK_BLOCKING_ORDER_CHANGED_PROPERTY = "locationTrackBlockingOrder";// NOI18N

 /*public*/ Location::Location(QString id, QString name,QObject *parent)
  : PropertyChangeSupport(this, parent) {
  common();
  if(log->isDebugEnabled()) log->debug(tr("New location (%1) id: %2").arg(name).arg(id));
  _name = name;
  _id = id;

 }
 void Location::common()
 {
  log = new Logger("Location");
    setObjectName("Location");
     // a new location accepts all types
     setTypeNames(((CarTypes*)InstanceManager::getDefault("CarTypes"))->getNames());
     setTypeNames(((EngineTypes*)InstanceManager::getDefault("EngineTypes"))->getNames());
     addPropertyChangeListeners();
     _id = NONE;
     _name = NONE;
     _IdNumber = 0;
     _numberRS = 0; // number of cars and engines (total rolling stock)
     _numberCars = 0; // number of cars
     _numberEngines = 0; // number of engines
     _pickupRS = 0;
     _dropRS = 0;
     _locationOps = NORMAL; // type of operations at this location
     _trainDir = EAST + WEST + NORTH + SOUTH; // train direction served by this location
     _length = 0; // length of all tracks at this location
     _usedLength = 0; // length of track filled by cars and engines
     _comment = NONE;
     _switchListComment = NONE; // optional switch list comment
     _switchList = true; // when true print switchlist for this location
     _defaultPrinter = NONE; // the default printer name when printing a switchlist
     _status = UNKNOWN; // print switch list status
     _switchListState = SW_CREATE; // switch list state, saved between sessions
     _trainIconEast =  QPoint(); // coordinates of east bound train icons
     _trainIconWest =  QPoint();
     _trainIconNorth =  QPoint();
     _trainIconSouth =  QPoint();
     _trackHashTable =  QHash<QString, Track*>();
     _physicalLocation = new PhysicalLocation();
     _listTypes = QStringList();

     // IdTag reader associated with this location.
     reader = NULL;

     // Pool
     _idPoolNumber = 0;
     _poolHashTable = QHash<QString, Pool*>();
 }

 /*public*/ QString Location::getId() {
     return _id;
 }

 /**
  * Sets the location's name.
  *
  * @param name
  */
 /*public*/ void Location::setName(QString name) {
     QString old = _name;
     _name = name;
     if (old!=name) {
         setDirtyAndFirePropertyChange(NAME_CHANGED_PROPERTY, old, name);
     }
 }

 // for combo boxes
 /*public*/ QString Location::toString() {
     return _name;
 }

 /*public*/ QString Location::getName() const{
     return _name;
 }

 /**
  * Makes a copy of this location.
  *
  * @param newLocation the location to copy to
  */
 /*public*/ void Location::copyLocation(Location* newLocation) {
     newLocation->setComment(getComment());
     newLocation->setDefaultPrinterName(getDefaultPrinterName());
     newLocation->setLocationOps(getLocationOps());
//       newLocation.setSwitchListComment(getSwitchListComment());
//       newLocation.setSwitchListEnabled(isSwitchListEnabled());
//       newLocation.setTrainDirections(getTrainDirections());
     // TODO should we set the train icon coordinates?
     // rolling stock serviced by this location
     foreach (QString type, newLocation->getTypeNames()) {
         if (acceptsTypeName(type)) {
             continue;
         } else {
             newLocation->deleteTypeName(type);
         }
     }
     copyTracksLocation(newLocation);

 }

 /**
  * Copies all of the tracks at this location. If there's a track already at
  * the copy to location with the same name, the track is skipped.
  *
  * @param location the location to copy the tracks to.
  */
 /*public*/ void Location::copyTracksLocation(Location* location) {
#if 1 //TODO:
     foreach (Track* track, getTrackList()) {
         if (location->getTrackByName(track->getName(), NULL) != (NULL)) {
             continue;
         }
         track->copyTrack(track->getName(), location);
     }
#endif
 }

 /*public*/ PhysicalLocation* Location::getPhysicalLocation() {
     return (_physicalLocation);
 }

 /*public*/ void Location::setPhysicalLocation(PhysicalLocation* l) {
     _physicalLocation = l;
// TODO:       ((LocationManagerXmll*)InstanceManager::getDefault("LocationManagerXml")).setDirty(true);
 }

 /**
  * Set total length of all tracks for this location
  *
  * @param length
  */
 /*public*/ void Location::setLength(int length) {
     int old = _length;
     _length = length;
     if (old != length) {
         setDirtyAndFirePropertyChange(LENGTH_CHANGED_PROPERTY, QString::number(old), QString::number(length));
     }
 }

 /**
  *
  * @return total length of all tracks for this location
  */
 /*public*/ int Location::getLength() {
     return _length;
 }

 /*public*/ void Location::setUsedLength(int length) {
     int old = _usedLength;
     _usedLength = length;
     if (old != length) {
         setDirtyAndFirePropertyChange(USEDLENGTH_CHANGED_PROPERTY, QString::number(old), QString::number(length));
     }
 }

 /**
  *
  * @return The length of the track that is occupied by cars and engines
  */
 /*public*/ int Location::getUsedLength() {
     return _usedLength;
 }

 /**
  * Set the operations mode for this location
  *
  * @param ops NORMAL STAGING
  */
 /*public*/ void Location::setLocationOps(int ops)
 {
     int old = _locationOps;
     _locationOps = ops;
     if (old != ops) {
         setDirtyAndFirePropertyChange("locationOps", QString::number(old), QString::number(ops)); // NOI18N
     }
 }

 /**
  * Gets the operations mode for this location
  *
  * @return NORMAL STAGING
  */
 /*public*/ int Location::getLocationOps() {
     return _locationOps;
 }

 /**
  * Used to determine if location is setup for staging
  *
  * @return true if location is setup as staging
  */
 /*public*/ bool Location::isStaging() {
     return getLocationOps() == STAGING;
 }

 /**
  *
  * @return True if location has spurs
  */
 /*public*/ bool Location::hasSpurs() {
     return hasTrackType(Track::SPUR);
 }

 /**
  *
  * @return True if location has classification/interchange tracks
  */
 /*public*/ bool Location::hasInterchanges() {
     return hasTrackType(Track::INTERCHANGE);
 }

 /**
  *
  * @return True if location has yard tracks
  */
 /*public*/ bool Location::hasYards() {
     return hasTrackType(Track::YARD);
 }

 /**
  *
  * @param trackType
  * @return True if location has the track type specified Track.INTERCHANGE
  *         Track.YARD Track.SPUR Track.Staging
  */
 /*public*/ bool Location::hasTrackType(QString trackType) {
     Track* track;
     //Enumeration<Track> en = _trackHashTable.elements();
     QListIterator<Track*> en(_trackHashTable.values());
     while (en.hasNext()) {
         track = en.next();
         if (track->getTrackType()==(trackType)) {
             return true;
         }
     }
     return false;
 }

 /*public*/ int Location::getNumberOfTracks() {
     return _trackHashTable.size();
 }

 /**
  * Sets the train directions that this location can service. EAST means that
  * an Eastbound train can service the location.
  *
  * @param direction Any combination of EAST WEST NORTH SOUTH
  */
 /*public*/ void Location::setTrainDirections(int direction) {
     int old = _trainDir;
     _trainDir = direction;
     if (old != direction) {
         setDirtyAndFirePropertyChange(TRAINDIRECTION_CHANGED_PROPERTY, (old), (direction));
     }
 }

 /**
  * Gets the train directions that this location can service. EAST means that
  * an Eastbound train can service the location.
  *
  * @return Any combination of EAST WEST NORTH SOUTH
  */
 /*public*/ int Location::getTrainDirections() {
     return _trainDir;
 }
 /**
  * Sets the number of cars and or engines on for this location
  *
  * @param number
  */
 /*public*/ void Location::setNumberRS(int number)
 {
  int old = _numberRS;
  _numberRS = number;
  if (old != number)
  {
   setDirtyAndFirePropertyChange("numberRS", (old), (number)); // NOI18N
  }
 }

 /**
  * Gets the number of cars and engines at this location
  *
  * @return number of cars at this location
  */
 /*public*/ int Location::getNumberRS() {
     return _numberRS;
 }

 /**
  * Sets the number of cars at this location
  *
  * @param number
  */
 /*private*/ void Location::setNumberCars(int number) {
     int old = _numberCars;
     _numberCars = number;
     if (old != number) {
         setDirtyAndFirePropertyChange("numberCars", QString::number(old), // NOI18N
                 QString::number(number)); // NOI18N
     }
 }

 /**
  *
  * @return The number of cars at this location
  */
 /*public*/ int Location::getNumberCars() {
     return _numberCars;
 }

 /**
  * Sets the number of engines at this location
  *
  * @param number
  */
 /*private*/ void Location::setNumberEngines(int number) {
     int old = _numberEngines;
     _numberEngines = number;
     if (old != number) {
         setDirtyAndFirePropertyChange("numberEngines", QString::number(old), // NOI18N
                 QString::number(number)); // NOI18N
     }
 }

 /**
  *
  * @return The number of engines at this location
  */
 /*public*/ int Location::getNumberEngines() {
     return _numberEngines;
 }

 /**
  * When true, a switchlist is desired for this location. Used for preview
  * and printing a manifest for a single location
  *
  * @param switchList
  */
 /*public*/ void Location::setSwitchListEnabled(bool switchList) {
     bool old = _switchList;
     _switchList = switchList;
     if (old != switchList) {
         setDirtyAndFirePropertyChange(SWITCHLIST_CHANGED_PROPERTY, old ? "true" : "false", // NOI18N
                 switchList ? "true" : "false"); // NOI18N
     }
 }

 /**
  * Used to determine if switch list is needed for this location
  *
  * @return true if switch list needed
  */
 /*public*/ bool Location::isSwitchListEnabled() {
     return _switchList;
 }

 /*public*/ void Location::setDefaultPrinterName(QString name) {
     QString old = _defaultPrinter;
     _defaultPrinter = name;
     if (old!=(name)) {
         setDirtyAndFirePropertyChange("defaultPrinter", old, name); // NOI18N
     }
 }

 /*public*/ QString Location::getDefaultPrinterName() {
     return _defaultPrinter;
 }

 /**
  * Automatically sets the print status for this location's switch list to
  * modified if the switch list was printed or CSV generated.
  *
  */
 /*public*/ void Location::setStatusModified() {
     if (getStatus()==(PRINTED) || getStatus()==(CSV_GENERATED) || !Setup::isSwitchListRealTime()) {
         setStatus(MODIFIED);
     }
 }

 /**
  * Sets the print status for this location's switch list
  *
  * @param status UNKNOWN PRINTED MODIFIED
  */
 /*public*/ void Location::setStatus(QString status) {
     QString old = _status;
     _status = status;
     if (old!=(status)) {
         setDirtyAndFirePropertyChange(STATUS_CHANGED_PROPERTY, old, status);
     }
 }

 /*public*/ QString Location::getStatus() {
     return _status;
 }

 /**
  *
  * @param state Location.SW_CREATE Location.SW_PRINTED Location.SW_APPEND
  */
 /*public*/ void Location::setSwitchListState(int state) {
     int old = _switchListState;
     _switchListState = state;
     if (old != state) {
         setDirtyAndFirePropertyChange("SwitchListState", old, state); // NOI18N
     }
 }

 /**
  * Returns the state of the switch list for this location.
  *
  * @return Location.SW_CREATE, Location.SW_PRINTED or Location.SW_APPEND
  */
 /*public*/ int Location::getSwitchListState() {
     return _switchListState;
 }

 /**
  * Sets the train icon coordinates for an eastbound train arriving at this
  * location.
  *
  * @param point The XY coordinates on the panel.
  */
 /*public*/ void Location::setTrainIconEast(QPoint point) {
     QPoint old = _trainIconEast;
     _trainIconEast = point;
     setDirtyAndFirePropertyChange("TrainIconEast", POINTSTRING(old), POINTSTRING(point)); // NOI18N
 }

 /*public*/ QPoint Location::getTrainIconEast() {
     return _trainIconEast;
 }

 /*public*/ void Location::setTrainIconWest(QPoint point) {
     QPoint old = _trainIconWest;
     _trainIconWest = point;
     setDirtyAndFirePropertyChange("TrainIconWest", POINTSTRING(old), POINTSTRING(point)); // NOI18N
 }

 /*public*/ QPoint Location::getTrainIconWest() {
     return _trainIconWest;
 }

 /*public*/ void Location::setTrainIconNorth(QPoint point) {
     QPoint old = _trainIconNorth;
     _trainIconNorth = point;
     setDirtyAndFirePropertyChange("TrainIconNorth", POINTSTRING(old), POINTSTRING(point)); // NOI18N
 }

 /*public*/ QPoint Location::getTrainIconNorth() {
     return _trainIconNorth;
 }

 /*public*/ void Location::setTrainIconSouth(QPoint point) {
     QPoint old = _trainIconSouth;
     _trainIconSouth = point;
     setDirtyAndFirePropertyChange("TrainIconSouth", POINTSTRING(old), POINTSTRING(point)); // NOI18N
 }

 /*public*/ QPoint Location::getTrainIconSouth() {
     return _trainIconSouth;
 }

 /**
  * Adds rolling stock to a specific location.
  *
  * @param rs
  */
 /*public*/ void Location::addRS(RollingStock* rs)
{
     setNumberRS(getNumberRS() + 1);
     if (QString(rs->metaObject()->className()) == "Car") {
         setNumberCars(getNumberCars() + 1);
     } else if (QString(rs->metaObject()->className()) == "Engine") {
         setNumberEngines(getNumberEngines() + 1);
     }
     setUsedLength(getUsedLength() + rs->getTotalLength());
 }

 /*public*/ void Location::deleteRS(RollingStock* rs) {
     setNumberRS(getNumberRS() - 1);
     if (QString(rs->metaObject()->className()) == "Car") {
         setNumberCars(getNumberCars() - 1);
     } else if (QString(rs->metaObject()->className()) == "Engine") {
         setNumberEngines(getNumberEngines() - 1);
     }
     setUsedLength(getUsedLength() - rs->getTotalLength());
 }

 /**
  * Increments the number of cars and or engines that will be picked up by a
  * train at this location.
  */
 /*public*/ void Location::addPickupRS() {
     int old = _pickupRS;
     _pickupRS++;
     setDirtyAndFirePropertyChange("addPickupRS", QString::number(old), QString::number(_pickupRS)); // NOI18N
 }

 /**
  * Decrements the number of cars and or engines that will be picked up by a
  * train at this location.
  */
 /*public*/ void Location::deletePickupRS() {
     int old = _pickupRS;
     _pickupRS--;
     setDirtyAndFirePropertyChange("deletePickupRS", QString::number(old), QString::number(_pickupRS)); // NOI18N
 }

 /**
  * Increments the number of cars and or engines that will be dropped off by
  * trains at this location.
  */
 /*public*/ void Location::addDropRS() {
     int old = _dropRS;
     _dropRS++;
     setDirtyAndFirePropertyChange("addDropRS", QString::number(old), QString::number(_dropRS)); // NOI18N
 }

 /**
  * Decrements the number of cars and or engines that will be dropped off by
  * trains at this location.
  */
 /*public*/ void Location::deleteDropRS() {
     int old = _dropRS;
     _dropRS--;
     setDirtyAndFirePropertyChange("deleteDropRS", QString::number(old), QString::number(_dropRS)); // NOI18N
 }

 /**
  *
  * @return the number of cars and engines that are scheduled for pick up at
  *         this location.
  */
 /*public*/ int Location::getPickupRS() {
     return _pickupRS;
 }

 /**
  *
  * @return the number of cars and engines that are scheduled for drop at
  *         this location.
  */
 /*public*/ int Location::getDropRS() {
     return _dropRS;
 }

 /*public*/ void Location::setComment(QString comment) {
     QString old = _comment;
     _comment = comment;
     if (old!=(comment)) {
         setDirtyAndFirePropertyChange("Location Comment", old, comment); // NOI18N
     }
 }

 /*public*/ QString Location::getComment() {
     return _comment;
 }

 /*public*/ void Location::setSwitchListComment(QString comment) {
     QString old = _switchListComment;
     _switchListComment = comment;
     if (old!=(comment)) {
         setDirtyAndFirePropertyChange(SWITCHLIST_COMMENT_CHANGED_PROPERTY, old, comment);
     }
 }

 /*public*/ QString Location::getSwitchListComment() {
     return _switchListComment;
 }

 /*private*/ QStringList Location::getTypeNames() {
     QVector<QString> types = QVector<QString>(_listTypes.size());
     for (int i = 0; i < _listTypes.size(); i++)
     {
      types.replace(i, _listTypes.at(i));
     }
     return types.toList();
 }

 /*private*/ void Location::setTypeNames(QStringList types) {
if (types.length() == 0) {
         return;
     }
     StringUtil::sort(types);
     foreach (QString type, types) {
         _listTypes.append(type);
     }
 }

 /**
  * Adds the specific type of rolling stock to the will service list
  *
  * @param type of rolling stock that location will service
  */
 /*public*/ void Location::addTypeName(QString type) {
     // insert at start of list, sort later
     if (type == NULL || _listTypes.contains(type)) {
         return;
     }
     _listTypes.insert(0, type);
     log->debug(tr("Location (%1) add rolling stock type (%2)").arg(getName()).arg(type));
     setDirtyAndFirePropertyChange(TYPES_CHANGED_PROPERTY, _listTypes.size() - 1, _listTypes.size());
 }

 /*public*/ void Location::deleteTypeName(QString type) {
     if (!_listTypes.contains(type)) {
         return;
     }
     _listTypes.removeAt(_listTypes.indexOf(type));
    log->debug(tr("Location (%1) delete rolling stock type ({})").arg(getName()).arg(type));
     setDirtyAndFirePropertyChange(TYPES_CHANGED_PROPERTY, _listTypes.size() + 1, _listTypes.size());
 }

 /*public*/ bool Location::acceptsTypeName(QString type) {
     return _listTypes.contains(type);
 }

 /**
  * Adds a track to this location. Valid track types are spurs, yards,
  * staging and interchange tracks.
  *
  * @param name of track
  * @param type of track, Track.INTERCHANGE, Track.SPUR, Track.STAGING,
  *            Track.YARD
  * @return Track
  */
 /*public*/ Track* Location::addTrack(QString name, QString type)
 {
  Track* track = getTrackByName(name, type);
  if (track == (NULL))
  {
   _IdNumber++;
   QString id = _id + "s" + QString::number(_IdNumber);
  log->debug(tr("Adding new (%1) to (%2) track name (%3) id: %4").arg(type).arg(getName()).arg(name).arg(id));
   track = new Track(id, name, type, this);
   _register(track);
  }
  resetMoves(); // give all of the tracks equal weighting
  return track;
 }

 /**
  * Remember a NamedBean Object created outside the manager.
  */
 /*public*/ void Location::_register(Track* track) {
     int old = (_trackHashTable.size());
     _trackHashTable.insert(track->getId(), track);
     // add to the locations's available track length
     setLength(getLength() + track->getLength());
     // find last id created
     QStringList getId = track->getId().split("s");
     int id = getId.at(1).toInt();
     if (id > _IdNumber) {
         _IdNumber = id;
     }
     setDirtyAndFirePropertyChange(TRACK_LISTLENGTH_CHANGED_PROPERTY, old, (_trackHashTable
             .size()));
     // listen for name and state changes to forward
     //track->addPropertyChangeListener(this);
     connect(track, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

 /*public*/ void Location::deleteTrack(Track* track) {
     if (track != (NULL)) {
         //track->removePropertyChangeListener(this);
      disconnect(track, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

         // subtract from the locations's available track length
         setLength(getLength() - track->getLength());
         track->dispose();
         int old = (_trackHashTable.size());
         _trackHashTable.remove(track->getId());
         setDirtyAndFirePropertyChange(TRACK_LISTLENGTH_CHANGED_PROPERTY, old, (_trackHashTable.size()));
     }
 }

 /**
  * Get track at this location by name and type. Track type can be NULL.
  *
  * @param name track's name
  * @param type track type
  * @return track at location
  */
 /*public*/ Track* Location::getTrackByName(QString name, QString type) {
     Track* track;
     //Enumeration<Track> en = _trackHashTable.elements();
     QListIterator<Track*> en(_trackHashTable.values());
     while (en.hasNext()) {
         track = en.next();
         if (type == (NULL)) {
             if (track->getName()==(name)) {
                 return track;
             }
         } else if (track->getName()==(name) && track->getTrackType()==(type)) {
             return track;
         }
     }
     return NULL;
 }

 /*public*/ Track* Location::getTrackById(QString id) {
     return _trackHashTable.value(id);
 }

 /**
  * Gets a list of track ids ordered by id for this location.
  *
  * @return list of track ids for this location
  */
 /*public*/ QStringList Location::getTrackIdsByIdList() {
     QVector<QString> arr = QVector<QString>(_trackHashTable.size());
     QStringList out = QStringList();
     QStringListIterator en( _trackHashTable.keys());
     int i = 0;
     while (en.hasNext()) {
      arr.replace(i, en.next());
         i++;
     }
     StringUtil::sort(arr.toList());
     for (i = 0; i < arr.size(); i++) {
         out.append(arr[i]);
     }
     return out;
 }

 /**
  * Gets a sorted by id list of tracks for this location.
  *
  * @return Sorted list of tracks by id for this location.
  */
 /*public*/ QList<Track*> Location::getTrackByIdList() {
     QList<Track*> out = QList<Track*>();
     QStringList trackIds = getTrackIdsByIdList();
     foreach (QString id, trackIds) {
         out.append(getTrackById(id));
     }
     return out;
 }

 /**
  * Gets a unsorted list of the tracks at this location.
  *
  * @return tracks at this location.
  */
 /*public*/ QList<Track*> Location::getTrackList() {
    QList<Track*> out = QList<Track*>();
     //Enumeration<Track> en = _trackHashTable.elements();
    QListIterator<Track*> en(_trackHashTable.values());
     while (en.hasNext()) {
         out.append(en.next());
     }
     return out;
 }

/**
* Sorted list by track name. Returns a list of tracks of a given track
* type. If type is NULL returns all tracks for the location.
*
* @param type track type: Track.YARD, Track.SPUR, Track.INTERCHANGE,
*            Track.STAGING
* @return list of tracks ordered by name for this location
*/
/*public*/ QList<Track*> Location::getTrackByNameList(QString type)
{
  QList<Track*> out = QList<Track*>();

  foreach (Track* track, getTrackByIdList())
  {
   bool locAdded = false;
   for (int j = 0; j < out.size(); j++)
   {
    if ((QString::compare(track->getName(), out.at(j)->getName(),Qt::CaseInsensitive) < 0)
               && (type != NULL && (track->getTrackType()==(type)) || (type == NULL)))
    {
     out.insert(j, track);
     locAdded = true;
     break;
    }
   }
   if (!locAdded && (type != NULL && (track->getTrackType()==(type)) || (type == NULL))) {
       out.append(track);
   }
  }
  return out;
 }

 /**
  * Sorted list by track moves. Returns a list of a given track type. If type
  * is NULL, all tracks for the location are returned. Tracks with schedules
  * are placed at the start of the list. Tracks that are alternates are
  * removed.
  *
  * @param type track type: Track.YARD, Track.SPUR, Track.INTERCHANGE,
  *            Track.STAGING
  * @return list of tracks at this location ordered by moves
  */
 /*public*/ QList<Track*> Location::getTrackByMovesList(QString type) {

     QList<Track*> moveList = QList<Track*>();

     foreach (Track* track, getTrackByIdList()) {
         bool locAdded = false;
         for (int j = 0; j < moveList.size(); j++) {
             if (track->getMoves() < moveList.at(j)->getMoves()
                     && ((type != NULL) && (track->getTrackType()==(type)) || (type == NULL))) {
                 moveList.insert(j, track);
                 locAdded = true;
                 break;
             }
         }
         if (!locAdded && ((type != NULL) && (track->getTrackType()==(type)) || (type == NULL))) {
             moveList.append(track);
         }
     }
     // bias tracks with schedules to the start of the list
     // remove any alternate tracks from the list
     QList<Track*> out = QList<Track*>();
     for (int i = 0; i < moveList.size(); i++) {
         Track* track = moveList.at(i);
         if (track->getScheduleId()!=(NONE)) {
             out.append(track);
             moveList.removeAt(i--);
         } else if (track->isAlternate()) {
             moveList.removeAt(i--);
         }
     }
     foreach (Track* track, moveList) {
         out.append(track);
     }
     return out;
 }

 /**
  * Sorted list by track blocking order. Returns a list of a given track type. If type
  * is NULL, all tracks for the location are returned.
  *
  * @param type track type: Track.YARD, Track.SPUR, Track.INTERCHANGE,
  *            Track.STAGING
  * @return list of tracks at this location ordered by blocking order
  */
 /*public*/ QList<Track*> Location::getTracksByBlockingOrderList(QString type) {
     QList<Track*> orderList = QList<Track*>();
     foreach (Track* track, getTrackByNameList(type)) {
         bool trackAdded = false;
         for (int j = 0; j < orderList.size(); j++) {
             if (track->getBlockingOrder() < orderList.at(j)->getBlockingOrder()) {
                 orderList.insert(j, track);
                 trackAdded = true;
                 break;
             }
         }
         if (!trackAdded) {
             orderList.append(track);
         }
     }
     return orderList;
 }

 /*public*/ void Location::resetTracksByBlockingOrder() {
     foreach (Track* track, getTrackList()) {
         track->setBlockingOrder(0);
     }
     resequnceTracksByBlockingOrder();
 }

 /*public*/ void Location::resequnceTracksByBlockingOrder() {
     int order = 1;
     foreach (Track* track, getTracksByBlockingOrderList(NULL)) {
         track->setBlockingOrder(order++);
     }
     setDirtyAndFirePropertyChange(TRACK_BLOCKING_ORDER_CHANGED_PROPERTY, true, false);
 }

 /*public*/ void Location::changeTrackBlockingOrderEarlier(Track* track) {
     //first adjust the track being replaced
     Track* repalceTrack = getTrackByBlockingOrder(track->getBlockingOrder() - 1);
     if (repalceTrack != (NULL)) {
         repalceTrack->setBlockingOrder(track->getBlockingOrder());
     }
     track->setBlockingOrder(track->getBlockingOrder() - 1);
     // move the end of order
     if (track->getBlockingOrder() <= 0)
         track->setBlockingOrder(_trackHashTable.size() + 1);
     resequnceTracksByBlockingOrder();
 }

 /*public*/ void Location::changeTrackBlockingOrderLater(Track* track) {
     //first adjust the track being replaced
     Track* repalceTrack = getTrackByBlockingOrder(track->getBlockingOrder() + 1);
     if (repalceTrack != (NULL)) {
         repalceTrack->setBlockingOrder(track->getBlockingOrder());
     }
     track->setBlockingOrder(track->getBlockingOrder() + 1);
     // move the start of order
     if (track->getBlockingOrder() > _trackHashTable.size())
         track->setBlockingOrder(0);
     resequnceTracksByBlockingOrder();
 }

 /*private*/ Track* Location::getTrackByBlockingOrder(int order) {
     foreach (Track* track, getTrackList()) {
         if (track->getBlockingOrder() == order)
             return track;
     }
     return NULL; // not found!
 }

 /*public*/ bool Location::isTrackAtLocation(Track* track) {
     if (track == (NULL)) {
         return true;
     }
     return _trackHashTable.contains(track->getId());
 }

 /**
  * Reset the move count for all tracks at this location
  */
 /*public*/ void Location::resetMoves() {
     QList<Track*> tracks = getTrackList();
     foreach (Track* track ,tracks) {
         track->setMoves(0);
     }
 }

 /**
  * Updates a JComboBox with all of the track locations for this location.
  *
  * @param box JComboBox to be updated.
  */
 /*public*/ void Location::updateComboBox(QComboBox* box)
 {
  box->clear();
  box->addItem("");
  QList<Track*> tracks = getTrackByNameList(NULL);
  foreach (Track* track, tracks)
  {
   box->addItem(track->toString(), VPtr<Track>::asQVariant(track));
  }
 }

 /**
  * Updates a JComboBox with tracks that can service the rolling stock.
  *
  * @param box JComboBox to be updated.
  * @param rs Rolling Stock to be serviced
  * @param filter When true, remove tracks not able to service rs.
  * @param destination When true, the tracks are destinations for the rs.
  */
 /*public*/ void Location::updateComboBox(QComboBox* box, RollingStock* rs, bool filter, bool destination)
 {
     updateComboBox(box);
     if (!filter || rs == (NULL)) {
         return;
     }
     QList<Track*> tracks = getTrackByNameList(NULL);
     foreach (Track* track, tracks) {
         QString status = "";
         if (destination) {
             status = rs->testDestination(this, track);
         } else {
             status = rs->testLocation(this, track);
         }
         if (status==(Track::OKAY) && (!destination || track->getTrackType()!=(Track::STAGING))) {
             box->setCurrentIndex(box->findText(track->getName()));
            log->debug(tr("Available track: %1 for location: %2").arg(track->getName()).arg(getName()));
         } else {
            // box.removeItem(track);
          box->removeItem(box->findText(track->getName()));
         }
     }
 }

 /**
  * Adds a track pool for this location. A track pool is a set of tracks
  * where the length of the tracks is shared between all of them.
  *
  * @param name the name of the Pool* to create
  * @return Pool
  */
 /*public*/ Pool* Location::addPool(QString name) {
     Pool* pool = getPoolByName(name);
     if (pool == (NULL)) {
         _idPoolNumber++;
         QString id = _id + "p" + QString::number(_idPoolNumber);
        log->debug(tr("creating new pool (%1) id: %2").arg(name).arg(id));
         pool = new Pool(id, name);
         _register(pool);
     }
     return pool;
 }

 /*public*/ void Location::removePool(Pool* pool) {
     if (pool != (NULL)) {
         _poolHashTable.remove(pool->getId());
         setDirtyAndFirePropertyChange(POOL_LENGTH_CHANGED_PROPERTY, (_poolHashTable.size() + 1), (_poolHashTable.size()));
     }
 }

 /*public*/ Pool* Location::getPoolByName(QString name) {
     Pool* pool;
     QListIterator<Pool*> en( _poolHashTable.values());
     while (en.hasNext()) {
         pool = en.next();
         if (pool->getName()==(name)) {
             return pool;
         }
     }
     return NULL;
 }

 /*public*/ void Location::_register(Pool* pool) {
     int old = (_poolHashTable.size());
     _poolHashTable.insert(pool->getId(), pool);
     // find last id created
     QStringList getId = pool->getId().split("p");
     int id = getId[1].toInt();
     if (id > _idPoolNumber) {
         _idPoolNumber = id;
     }
     setDirtyAndFirePropertyChange(POOL_LENGTH_CHANGED_PROPERTY, old, (_poolHashTable.size()));
 }

 /*public*/ void Location::updatePoolComboBox(QComboBox* box) {
     box->clear();
     box->addItem(NULL);
     foreach (Pool* pool, getPoolsByNameList()) {
         box->addItem(pool->toString(), VPtr<Pool>::asQVariant(pool));
     }
 }

 /**
  * Gets a list of Pools for this location.
  *
  * @return A list of Pools
  */
 /*public*/ QList<Pool*> Location::getPoolsByNameList() {
     QList<Pool*> pools = QList<Pool*>();
     QListIterator<Pool*> en( _poolHashTable.values());
     while (en.hasNext()) {
         pools.append(en.next());
     }
     return pools;
 }

 /**
  * Used to determine if there are Pools at this location.
  *
  * @return True if there are Pools at this location
  */
 /*public*/ bool Location::hasPools() {
     return _poolHashTable.size() > 0;
 }

 /**
  * Used to determine if there are any planned pickups at this location.
  *
  * @return True if there are planned pickups
  */
 /*public*/ bool Location::hasPlannedPickups() {
     QList<Track*> tracks = getTrackList();
     foreach (Track* track, tracks) {
         if (track->getIgnoreUsedLengthPercentage() > 0) {
             return true;
         }
     }
     return false;
 }

 /**
  * Used to determine if there are any load restrictions at this location.
  *
  * @return True if there are load restrictions
  */
 /*public*/ bool Location::hasLoadRestrications() {
     QList<Track*> tracks = getTrackList();
     foreach (Track* track, tracks) {
         if (track->getLoadOption()!=(Track::ALL_LOADS)) {
             return true;
         }
     }
     return false;
 }

 /**
  * Used to determine if there are any load ship restrictions at this
  * location.
  *
  * @return True if there are load ship restrictions
  */
 /*public*/ bool Location::hasShipLoadRestrications() {
     QList<Track*> tracks = getTrackList();
     foreach (Track* track, tracks) {
         if (track->getShipLoadOption()!=(Track::ALL_LOADS)) {
             return true;
         }
     }
     return false;
 }

 /**
  * Used to determine if there are any road restrictions at this location.
  *
  * @return True if there are road restrictions
  */
 /*public*/ bool Location::hasRoadRestrications() {
     QList<Track*> tracks = getTrackList();
     foreach (Track* track, tracks) {
         if (track->getRoadOption()!=(Track::ALL_ROADS)) {
             return true;
         }
     }
     return false;
 }

 /**
  * Used to determine if there are any track destination restrictions at this location.
  *
  * @return True if there are road restrictions
  */
 /*public*/ bool Location::hasDestinationRestrications() {
     QList<Track*> tracks = getTrackList();
     foreach (Track* track, tracks) {
         if (track->getDestinationOption()!=(Track::ALL_DESTINATIONS)) {
             return true;
         }
     }
     return false;
 }

 /*public*/ bool Location::hasAlternateTracks() {
     foreach (Track* track, getTrackList()) {
         if (track->getAlternateTrack() != (NULL)) {
             return true;
         }
     }
     return false;
 }

 /*public*/ void Location::dispose() {
     QList<Track*> tracks = getTrackList();
     foreach (Track* track, tracks) {
         deleteTrack(track);
     }
     ((CarTypes*)InstanceManager::getDefault("CarTypes"))->removePropertyChangeListener(this);
     ((CarRoads*)InstanceManager::getDefault("CarRoads"))->removePropertyChangeListener(this);
     ((EngineTypes*)InstanceManager::getDefault("EngineTypes"))->removePropertyChangeListener(this);
     // Change name in case object is still in use, for example Schedules
     setName(tr("NotValid %1").arg(getName()));
     setDirtyAndFirePropertyChange(DISPOSE_CHANGED_PROPERTY, QVariant(), DISPOSE_CHANGED_PROPERTY);
 }

 /*private*/ void Location::addPropertyChangeListeners() {
     ((CarTypes*)InstanceManager::getDefault("CarTypes"))->addPropertyChangeListener(this);
     ((CarRoads*)InstanceManager::getDefault("CarRoads"))->addPropertyChangeListener(this);
     ((EngineTypes*)InstanceManager::getDefault("EngineTypes"))->addPropertyChangeListener(this);
 }

 /**
  * Construct this Entry from XML. This member has to remain synchronized
  * with the detailed DTD in operations-locations.dtd
  *
  * @param e Consist XML element
  */
 /*public*/ Location::Location(QDomElement e, QObject* parent) :PropertyChangeSupport(this, parent)
 {
  common();
  // if (log.isDebugEnabled())log->debug("ctor from element "+e);
  QString a;
  if ((a = e.attribute(Xml::ID)) != "") {
      _id = a;
  } else {
     log->warn("no id attribute( in location element when reading operations");
  }
  if ((a = e.attribute(Xml::NAME)) !="") {
      _name = a;
  }
  if ((a = e.attribute(Xml::OPS)) != "") {
      //try {
   bool ok;
          _locationOps = a.toInt(&ok);
      if(!ok) {
         log->error(tr("Location ops isn't a vaild number for location %1").arg(getName()));
      }
  }
  if ((a = e.attribute(Xml::DIR)) != "") {
      //try {
   bool ok;
          _trainDir = a.toInt(&ok);
      if(!ok) {
         log->error(tr("Train directions isn't a vaild number for location %1").arg(getName()));
      }
  }
  if ((a = e.attribute(Xml::SWITCH_LIST)) != "") {
      _switchList = (a==(Xml::_TRUE));
  }
  if ((a = e.attribute(Xml::SWITCH_LIST_STATE)) != "") {
      //try {
   bool ok;
          _switchListState = a.toInt(&ok);
      if(!ok) {
         log->error(tr("Switch list state isn't a vaild number for location %1").arg(getName()));
      }
      if (getSwitchListState() == SW_PRINTED) {
          setStatus(PRINTED);
      }
  }
  if ((a = e.attribute(Xml::PRINTER_NAME)) != "") {
      _defaultPrinter = a;
  }
  // load train icon coordinates
  QString x;
  QString y;
  //try {
   if ((x = e.attribute(Xml::EAST_TRAIN_ICON_X)) != ""
       && (y = e.attribute(Xml::EAST_TRAIN_ICON_Y)) != "") {
          setTrainIconEast( QPoint(x.toInt(), y.toInt()));
      }
   if ((x = e.attribute(Xml::WEST_TRAIN_ICON_X)) != ""
       && (y = e.attribute(Xml::WEST_TRAIN_ICON_Y)) != "") {
          setTrainIconWest( QPoint(x.toInt(), y.toInt()));
      }
   if ((x = e.attribute(Xml::NORTH_TRAIN_ICON_X)) != ""
       && (y = e.attribute(Xml::NORTH_TRAIN_ICON_Y)) != "") {
          setTrainIconNorth( QPoint(x.toInt(), y.toInt()));
      }
   if ((x = e.attribute(Xml::SOUTH_TRAIN_ICON_X)) != ""
       && (y = e.attribute(Xml::SOUTH_TRAIN_ICON_Y)) != "") {
          setTrainIconSouth(QPoint(x.toInt(), y.toInt()));
      }
//       } catch (NumberFormatException nfe) {
//          log->error("Train icon coordinates aren't vaild for location {}", getName());
//       }
   if ((a = e.attribute(Xml::COMMENT)) != "") {
      _comment = OperationsXml::convertFromXmlComment(a);
  }
   if ((a = e.attribute(Xml::SWITCH_LIST_COMMENT)) != "") {
      _switchListComment = a;
  }
   if ((a = e.attribute(Xml::PHYSICAL_LOCATION)) != "") {
      _physicalLocation = PhysicalLocation::parse(a);
  }
  // new way of reading car types using elements added in 3.3.1
   if (e.firstChildElement(Xml::TYPES) != QDomElement()) {
      //@SuppressWarnings("unchecked")
      QDomNodeList carTypes = e.firstChildElement(Xml::TYPES).elementsByTagName(Xml::CAR_TYPE);
      QVector<QString> types = QVector<QString>(carTypes.size());
      for (int i = 0; i < carTypes.size(); i++) {
          QDomElement type = carTypes.at(i).toElement();
          if ((a = type.attribute(Xml::NAME)) != "") {
              types.replace(i,a);
          }
      }
      setTypeNames(types.toList());
      //@SuppressWarnings("unchecked")
      QDomNodeList locoTypes = e.firstChildElement(Xml::TYPES).elementsByTagName(Xml::LOCO_TYPE);
      types = QVector<QString>(locoTypes.size());
      for (int i = 0; i < locoTypes.size(); i++)
      {
          QDomElement type = locoTypes.at(i).toElement();
          if ((a = type.attribute(Xml::NAME)) != NULL)
          {
              types.replace(i, a);
          }
      }
      setTypeNames(types.toList());
  } // old way of reading car types up to version 2.99.6
  else if ((a = e.attribute(Xml::CAR_TYPES)) != NULL) {
      QString names = a;
      QStringList Types = names.split("%%"); // NOI18N
      // if (log.isDebugEnabled())log->debug("rolling stock types: "+names);
      setTypeNames(Types);
  }

  // early version of operations called tracks "secondary"
  if (e.elementsByTagName(Xml::SECONDARY) != QDomNodeList()) {
      //@SuppressWarnings("unchecked")
      QDomNodeList eTracks = e.elementsByTagName(Xml::SECONDARY);
      //foreach (QDomElement eTrack, eTracks) {
      for(int i =0; i < eTracks.size(); i++)
      {
       _register(new Track(eTracks.at(i).toElement(), this));
      }
  }
  if (!e.elementsByTagName(Xml::TRACK).isEmpty())
  {
   //@SuppressWarnings("unchecked")
   QDomNodeList eTracks = e.elementsByTagName(Xml::TRACK);
   if(log->isDebugEnabled()) log->debug(tr("location (%1) has %2 tracks").arg(getName()).arg(eTracks.size()));
   //for (QDomElement eTrack : eTracks) {
   if (log->isDebugEnabled()) log->debug(tr("location %1 has tracks:").arg(getName()));
   for(int i=0; i < eTracks.size(); i++)
   {
    QDomElement e = eTracks.at(i).toElement();
    if(log->isDebugEnabled()) log->debug(tr("%1 id=%2, name =%3").arg(toString()).arg(e.attribute(Xml::ID)).arg(e.attribute(Xml::NAME)));
   }
   for(int i=0; i < eTracks.size(); i++)
   {
    if(eTracks.at(i).toElement().attribute(Xml::ID)!= "") // ignore comment:track
     _register(new Track(eTracks.at(i).toElement(), this));
   }
  }
  if (e.attribute(Xml::READER) != "")
  {
   //@SuppressWarnings("unchecked")
   Reporter* r = ((ReporterManager*)InstanceManager
              ::getDefault("ReporterManager"))
              ->provideReporter(
                      e.attribute(Xml::READER));
      setReporter(r);
  }
  addPropertyChangeListeners();
 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-locations.dtd.
  *
  * @return Contents in a JDOM Element
  */
 /*public*/ QDomElement Location::store(QDomDocument doc)
 {
   QDomElement e = doc.createElement(Xml::LOCATION);
     e.setAttribute(Xml::ID, getId());
     e.setAttribute(Xml::NAME, getName());
     e.setAttribute(Xml::OPS, QString::number(getLocationOps()));
     e.setAttribute(Xml::DIR, QString::number(getTrainDirections()));
     e.setAttribute(Xml::SWITCH_LIST, isSwitchListEnabled() ? Xml::_TRUE : Xml::_FALSE);
     if (!Setup::isSwitchListRealTime()) {
         e.setAttribute(Xml::SWITCH_LIST_STATE, QString::number(getSwitchListState()));
     }
     if (getDefaultPrinterName()!=(NONE)) {
         e.setAttribute(Xml::PRINTER_NAME, getDefaultPrinterName());
     }
     if (getTrainIconEast()!=(QPoint())) {
         e.setAttribute(Xml::EAST_TRAIN_ICON_X, QString::number(getTrainIconEast().x()));
         e.setAttribute(Xml::EAST_TRAIN_ICON_Y, QString::number(getTrainIconEast().y()));
     }
     if (getTrainIconWest()!=(QPoint())) {
         e.setAttribute(Xml::WEST_TRAIN_ICON_X, QString::number(getTrainIconWest().x()));
         e.setAttribute(Xml::WEST_TRAIN_ICON_Y, QString::number(getTrainIconWest().y()));
     }
     if (getTrainIconNorth()!=(QPoint())) {
         e.setAttribute(Xml::NORTH_TRAIN_ICON_X, QString::number(getTrainIconNorth().x()));
         e.setAttribute(Xml::NORTH_TRAIN_ICON_Y, QString::number(getTrainIconNorth().y()));
     }
     if (getTrainIconSouth()!=(QPoint())) {
         e.setAttribute(Xml::SOUTH_TRAIN_ICON_X, QString::number(getTrainIconSouth().x()));
         e.setAttribute(Xml::SOUTH_TRAIN_ICON_Y, QString::number(getTrainIconSouth().y()));
     }
     if (reader != (NULL)) {
         e.setAttribute(Xml::READER, reader->getDisplayName());
     }
     // build list of rolling stock types for this location
     QStringList types = getTypeNames();
     // Old way of saving car types
     if (Control::backwardCompatible) {
         QString buf;// = new StringBuffer();
         foreach (QString type, types) {
             // remove types that have been deleted by user
             if (((CarTypes*)InstanceManager::getDefault("CarTypes"))->containsName(type)
                     || ((EngineTypes*)InstanceManager::getDefault("EngineTypes"))->containsName(type)) {
                 buf.append(type + "%%"); // NOI18N
             }
         }
         e.setAttribute(Xml::CAR_TYPES, buf);
     }
     // new way of saving car types
     //QDomElement eTypes = QDomElement (Xml::TYPES);
              QDomElement eTypes = doc.createElement(Xml::TYPES);
     foreach (QString type, types) {
         // don't save types that have been deleted by user
         if (((EngineTypes*)InstanceManager::getDefault("EngineTypes"))->containsName(type)) {
             //QDomElement eType = QDomElement (Xml::LOCO_TYPE);
              QDomElement eType = doc.createElement(Xml::LOCO_TYPE);
             eType.setAttribute(Xml::NAME, type);
             eTypes.appendChild(eType);
         } else if (((CarTypes*)InstanceManager::getDefault("CarTypes"))->containsName(type)) {
             //QDomElement eType = QDomElement (Xml::CAR_TYPE);
              QDomElement eType = doc.createElement(Xml::CAR_TYPE);
             eType.setAttribute(Xml::NAME, type);
             eTypes.appendChild(eType);
         }
     }
     e.appendChild(eTypes);
     if (_physicalLocation != (NULL)) {
         e.setAttribute(Xml::PHYSICAL_LOCATION, _physicalLocation->toString());
     }

     e.setAttribute(Xml::COMMENT, getComment());
     e.setAttribute(Xml::SWITCH_LIST_COMMENT, getSwitchListComment());

     QList<Track*> tracks = getTrackByIdList();
     foreach (Track* track, tracks) {
         e.appendChild(track->store(doc));
     }
     return e;
 }

 /*private*/ void Location::replaceType(QString oldType, QString newType) {
     if (acceptsTypeName(oldType)) {
         if (newType != (NULL)) {
             addTypeName(newType);
         }
         // now adjust tracks
         QList<Track*> tracks = getTrackList();
         foreach (Track* track, tracks) {
             if (track->acceptsTypeName(oldType)) {
                 track->deleteTypeName(oldType);
                 if (newType != (NULL)) {
                     track->addTypeName(newType);
                 }
             }
             // adjust custom loads
             QStringList loadNames = track->getLoadNames();
             foreach (QString load, loadNames) {
                 QStringList splitLoad = load.split(CarLoad::SPLIT_CHAR);
                 if (splitLoad.length() > 1) {
                     if (splitLoad[0]==(oldType)) {
                         track->deleteLoadName(load);
                         if (newType != (NULL)) {
                             load = newType + CarLoad::SPLIT_CHAR + splitLoad[1];
                             track->addLoadName(load);
                         }
                     }
                 }
             }
             loadNames = track->getShipLoadNames();
             foreach (QString load, loadNames) {
                 QStringList splitLoad = load.split(CarLoad::SPLIT_CHAR);
                 if (splitLoad.length() > 1) {
                     if (splitLoad[0]==(oldType)) {
                         track->deleteShipLoadName(load);
                         if (newType != (NULL)) {
                             load = newType + CarLoad::SPLIT_CHAR + splitLoad[1];
                             track->addShipLoadName(load);
                         }
                     }
                 }
             }
         }
         deleteTypeName(oldType);
     }
 }

 /*
  * set the jmri.Reporter object associated with this location.
  *
  * @param reader jmri.Reporter object.
  */
 /*protected*/ void Location::setReporter(Reporter* r) {
     reader = r;
 }

 /*
  * get the jmri.Reporter object associated with this location.
  *
  * @return jmri.Reporter object.
  */
 /*public*/ Reporter* Location::getReporter() {
     return reader;
 }

 /*private*/ void Location::replaceRoad(QString oldRoad, QString newRoad) {
     // now adjust any track locations
     QList<Track*> tracks = getTrackList();
     foreach (Track* track, tracks) {
         if (track->containsRoadName(oldRoad)) {
             track->deleteRoadName(oldRoad);
             if (newRoad != (NULL)) {
                 track->addRoadName(newRoad);
             }
         }
     }
 }

 /*public*/ void Location::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
        if(log->isDebugEnabled()) log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
                 ->getNewValue().toString()));
     }
     // update length of tracks at this location if track length changes
     if (e->getPropertyName()==(Track::LENGTH_CHANGED_PROPERTY)) {
         setLength(getLength() - e->getOldValue().toInt()
                 + e->getNewValue().toInt());
     }
     // if a track type change, must update all tables
     if (e->getPropertyName()==(Track::TRACK_TYPE_CHANGED_PROPERTY)) {
         setDirtyAndFirePropertyChange(TRACK_LISTLENGTH_CHANGED_PROPERTY, QVariant(), QVariant());
     }
     if (e->getPropertyName()==(CarTypes::CARTYPES_NAME_CHANGED_PROPERTY)
             || e->getPropertyName()==(CarTypes::CARTYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(EngineTypes::ENGINETYPES_NAME_CHANGED_PROPERTY)) {
         replaceType( e->getOldValue().toString(),  e->getNewValue().toString());
     }
     if (e->getPropertyName()==(CarRoads::CARROADS_NAME_CHANGED_PROPERTY)) {
         replaceRoad(e->getOldValue().toString(), e->getNewValue().toString());
     }
 }

 /*protected*/ void Location::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
 ((LocationManagerXml*)InstanceManager::getDefault("LocationManagerXml"))->setDirty(true);
     firePropertyChange(p, old, n);
 }
}
