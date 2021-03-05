#include "locationmanager.h"
#include "locationmanagerxml.h"
#include "control.h"
#include "location.h"
#include "logger.h"
#include "xml.h"
#include "propertychangesupport.h"
#include "jcombobox.h"
#include "rosterentry.h"
#include "track.h"
#include "carload.h"
#include "traincommon.h"
#include "instancemanager.h"

//LocationManager::LocationManager(QObject *parent) :
//  QObject(parent)
//{
//}
namespace Operations
{

/**
 * Manages locations.
 *
 * @author Bob Jacobsen Copyright (C) 2003
 * @author Daniel Boudreau Copyright (C) 2008, 2009, 2013, 2014
 * @version $Revision: 29493 $
 */
///*public*/ class LocationManager implements java.beans.PropertyChangeListener {

 /*public*/ /*static*/ /*final*/ QString LocationManager::LISTLENGTH_CHANGED_PROPERTY = "locationsListLength"; // NOI18N

 /*public*/ LocationManager::LocationManager(QObject *parent) :
PropertyChangeSupport(this, parent)
 {
  _id = 0;
  log = new Logger("LocationManager");
  _locationHashTable = QHash<QString, Location*>();
  //pcs = new PropertyChangeSupport(this);
  _maxLocationNameLength = 0;
   _maxTrackNameLength = 0;
   _maxLocationAndTrackNameLength = 0;
   setProperty("InstanceManagerAutoDefault", "true");
   setProperty("InstanceManagerAutoInitialize", "true");
 }

 /*public*/ void LocationManager::dispose() {
     _locationHashTable.clear();
     _id = 0;
 }


 /**
  * @return Number of locations
  */
 /*public*/ int LocationManager::getNumberOfLocations() {
     return _locationHashTable.size();
 }

 /**
  * @return requested Location object or NULL if none exists
  */
 /*public*/ Location* LocationManager::getLocationByName(QString name) {
     Location* location;
     //Enumeration<Location> en = _locationHashTable.elements();
     QListIterator<Location*> en(_locationHashTable.values());
     while (en.hasNext()) {
         location = en.next();
         if (location->getName()==(name)) {
             return location;
         }
     }
     return NULL;
 }

 /*public*/ Location* LocationManager::getLocationById(QString id) {
     return _locationHashTable.value(id);
 }

 /**
  * Request a location associated with a given reporter.
  *
  * @param r Reporter object associated with desired location.
  * @return requested Location object or NULL if none exists
  */
 /*public*/ Location* LocationManager::getLocationByReporter(Reporter* r) {
    foreach(Location* location, _locationHashTable.values()) {
       try {
          if (location->getReporter()==(r))
              return location;
} catch(NullPointerException npe) {
          // it's valid for a reporter to be NULL (no reporter
          // at a given location.
       }
     }
     return NULL;
 }


 /**
  * Finds an existing location or creates a new location if needed requires
  * location's name creates a unique id for this location
  *
  * @param name
  *
  * @return new location or existing location
  */
 /*public*/ Location* LocationManager::newLocation(QString name) {
     Location* location = getLocationByName(name);
     if (location == NULL) {
         _id++;
         location = new Location(QString::number(_id), name);
         int oldSize = _locationHashTable.size();
         _locationHashTable.insert(location->getId(), location);
         setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, (_locationHashTable.size()));
     }
     return location;
 }

 /**
  * Remember a NamedBean Object created outside the manager.
  */
 /*public*/ void LocationManager::_register(Location* location) {
     int oldSize = (_locationHashTable.size());
     _locationHashTable.insert(location->getId(), location);
     // find last id created
     int id = location->getId().toInt();
     if (id > _id) {
         _id = id;
     }
     setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, (_locationHashTable.size()));
 }

 /**
  * Forget a NamedBean Object created outside the manager.
  */
 /*public*/ void LocationManager::deregister(Location* location) {
     if (location == NULL) {
         return;
     }
     location->dispose();
     int oldSize = _locationHashTable.size();
     _locationHashTable.remove(location->getId());
     setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, (_locationHashTable.size()));
 }

 /**
  * Sort by location name
  *
  * @return list of locations ordered by name
  */
 /*public*/ QList<Location*> LocationManager::getLocationsByNameList() {
     // first get id list
     QList<Location*> sortList = getList();
     // now re-sort
     QList<Location*> out = QList<Location*>();
     foreach (Location* location, sortList) {
         for (int j = 0; j < out.size(); j++) {
             if (QString::compare(location->getName(), out.at(j)->getName(),Qt::CaseInsensitive) < 0)
             {
                 out.insert(j, location);
                 break;
             }
         }
         if (!out.contains(location)) {
             out.append(location);
         }
     }
     return out;

 }

 /**
  * Sort by location number, number can alpha numeric
  *
  * @return list of locations ordered by id numbers
  */
 /*public*/ QList<Location*> LocationManager::getLocationsByIdList() {
     QList<Location*> sortList = getList();
     // now re-sort
     QList<Location*> out =  QList<Location*>();
     foreach (Location* location, sortList) {
         for (int j = 0; j < out.size(); j++) {
             try {
           if (location->getId().toInt() < out.value(j)->getId().toInt()) {
                     out.insert(j, location);
                     break;
                 }
             } catch (NumberFormatException e) {
                 log->debug("list id number isn't a number");
             }
         }
         if (!out.contains(location)) {
             out.append(location);
         }
     }
     return out;
 }

 /**
  * Gets an unsorted list of all locations.
  *
  * @return All locations.
  */
 /*public*/ QList<Location*> LocationManager::getList() {
     QList<Location*> out = QList<Location*>();
     //Enumeration<Location> en = _locationHashTable.elements();
     QListIterator<Location*> en(_locationHashTable.values());
     while (en.hasNext()) {
         out.append(en.next());
     }
     return out;
 }

 /**
  * Returns all tracks of type
  *
  * @param type Spur (Track.SPUR), Yard (Track.YARD), Interchange
  *             (Track.INTERCHANGE), Staging (Track.STAGING), or NULL
  *             (returns all track types)
  * @return List of tracks
  */
 /*public*/ QList<Track*> LocationManager::getTracks(QString type) {
     QList<Location*> sortList = getList();
     QList<Track*> trackList = QList<Track*>();
     foreach (Location* location, sortList) {
         QList<Track*> tracks = location->getTrackByNameList(type);
         foreach (Track* track, tracks) {
             trackList.append(track);
         }
     }
     return trackList;
 }

 /**
  * Returns all tracks of type sorted by use
  *
  * @param type Spur (Track.SPUR), Yard (Track.YARD), Interchange
  *             (Track.INTERCHANGE), Staging (Track.STAGING), or NULL
  *             (returns all track types)
  * @return List of tracks ordered by use
  */
 /*public*/ QList<Track*> LocationManager::getTracksByMoves(QString type) {
     QList<Track*> trackList = getTracks(type);
     // now re-sort
     QList<Track*> moveList = QList<Track*>();
     foreach (Track* track, trackList) {
         bool locAdded = false;
         for (int j = 0; j < moveList.size(); j++) {
             if (track->getMoves() < moveList.at(j)->getMoves()) {
                 moveList.insert(j, track);
                 locAdded = true;
                 break;
             }
         }
         if (!locAdded) {
             moveList.append(track);
         }
     }
     return moveList;
 }

 /*public*/ void LocationManager::resetMoves() {
     QList<Location*> locations = getList();
     foreach (Location* loc, locations) {
         loc->resetMoves();
     }
 }

 /**
  *
  * @return locations for this railroad
  */
 /*public*/ JComboBox* LocationManager::getComboBox() {
     JComboBox* box = new JComboBox();
     updateComboBox(box);
     return box;
 }

 /*public*/ void LocationManager::updateComboBox(JComboBox* box) {
     box->clear();
     box->addItem("");
     foreach (Location* loc, getLocationsByNameList()) {
      box->addItem(loc->getName(), VPtr<Location>::asQVariant(loc));
     }
 }

 /*public*/ void LocationManager::replaceLoad(QString type, QString oldLoadName, QString newLoadName) {
     QList<Location*> locs = getList();
     foreach (Location* loc, locs) {
         // now adjust tracks
         QList<Track*> tracks = loc->getTrackList();
         foreach (Track* track, tracks) {
             foreach (QString loadName, track->getLoadNames()) {
                 if (loadName==(oldLoadName)) {
                     track->deleteLoadName(oldLoadName);
                     if (newLoadName != NULL) {
                         track->addLoadName(newLoadName);
                     }
                 }
                 // adjust combination car type and load name
                 QStringList splitLoad = loadName.split(CarLoad::SPLIT_CHAR);
                 if (splitLoad.length() > 1) {
                     if (splitLoad[0]==(type) && splitLoad[1]==(oldLoadName)) {
                         track->deleteLoadName(loadName);
                         if (newLoadName != NULL) {
                             track->addLoadName(type + CarLoad::SPLIT_CHAR + newLoadName);
                         }
                     }
                 }
             }
             // now adjust ship load names
             foreach (QString loadName, track->getShipLoadNames()) {
                 if (loadName==(oldLoadName)) {
                     track->deleteShipLoadName(oldLoadName);
                     if (newLoadName != NULL) {
                         track->addShipLoadName(newLoadName);
                     }
                 }
                 // adjust combination car type and load name
                 QStringList splitLoad = loadName.split(CarLoad::SPLIT_CHAR);
                 if (splitLoad.length() > 1) {
                     if (splitLoad[0]==(type) && splitLoad[1]==(oldLoadName)) {
                         track->deleteShipLoadName(loadName);
                         if (newLoadName != NULL) {
                             track->addShipLoadName(type + CarLoad::SPLIT_CHAR + newLoadName);
                         }
                     }
                 }
             }
         }
     }
 }


 /*public*/ int LocationManager::getMaxLocationNameLength() {
     calculateMaxNameLengths();
     return _maxLocationNameLength;
 }

 /*public*/ int LocationManager::getMaxTrackNameLength() {
     calculateMaxNameLengths();
     return _maxTrackNameLength;
 }

 /*public*/ int LocationManager::getMaxLocationAndTrackNameLength() {
     calculateMaxNameLengths();
     return _maxLocationAndTrackNameLength;
 }

 /*private*/ void LocationManager::calculateMaxNameLengths() {
     if (_maxLocationNameLength != 0) // only do this once
     {
         return;
     }
     QString maxTrackName = "";
     QString maxLocNameForTrack = "";
     QString maxLocationName = "";
     QString maxLocationAndTrackName = "";
     foreach (Track* track, getTracks(NULL)) {
         if (TrainCommon::splitString(track->getName()).length() > _maxTrackNameLength) {
             maxTrackName = track->getName();
             maxLocNameForTrack = track->getLocation()->getName();
             _maxTrackNameLength = TrainCommon::splitString(track->getName()).length();
         }
         if (TrainCommon::splitString(track->getLocation()->getName()).length() > _maxLocationNameLength) {
             maxLocationName = track->getLocation()->getName();
             _maxLocationNameLength = TrainCommon::splitString(track->getLocation()->getName()).length();
         }
         if (TrainCommon::splitString(track->getLocation()->getName()).length()
                 + TrainCommon::splitString(track->getName()).length() > _maxLocationAndTrackNameLength) {
             maxLocationAndTrackName = track->getLocation()->getName() + ", " + track->getName();
             _maxLocationAndTrackNameLength = TrainCommon::splitString(track->getLocation()->getName()).length()
                     + TrainCommon::splitString(track->getName()).length();
         }
     }
     log->info(tr("Max track name (%1) at (%2) length %3").arg(maxTrackName).arg(maxLocNameForTrack).arg(_maxTrackNameLength));
     log->info(tr("Max location name (%1) length %2").arg(maxLocationName).arg(_maxLocationNameLength));
     log->info(tr("Max location and track name (%1 length %2").arg(maxLocationAndTrackName).arg(_maxLocationAndTrackNameLength));
 }

 /*public*/ void LocationManager::load(QDomElement root) {
 if (root.firstChildElement(Xml::LOCATIONS) != QDomElement()) {
        // @SuppressWarnings("unchecked")
         QDomNodeList locs = root.firstChildElement(Xml::LOCATIONS).elementsByTagName(Xml::LOCATION);
         if (log->isDebugEnabled()) {
             log->debug(tr("readFile sees %1 locations").arg(locs.size()));
         }
         for(int i=0; i < locs.count(); i++)
         {
              _register(new Location(locs.at(i).toElement()));
         }
     }
 }

 /*public*/ void LocationManager::store(QDomElement root, QDomDocument doc)
 {
 QDomElement values = doc.createElement(Xml::LOCATIONS);
     root.appendChild(values /*= doc.createElement(Xml::LOCATIONS)*/);
     // add entries
     QList<Location*> locationList = getLocationsByIdList();
     foreach (Location* loc, locationList) {
         values.appendChild(loc->store(doc));
     }
 }
#if 0
 /**
  * There aren't any current property changes being monitored
  *
  */
 /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
     log->debug("LocationManager sees property change: ({}) old: ({}) new: ({})", e.getPropertyName(), e
             .getOldValue(), e.getNewValue()); // NOI18N
 }

#endif
 /*protected*/ void LocationManager::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     // set dirty
     ((LocationManagerXml*)InstanceManager::getDefault("LocationManagerXml"))->setDirty(true);
     firePropertyChange(p, old, n);
 }

//@Override
/*public*/ void LocationManager::initialize()
{
 InstanceManager::getDefault("OperationsSetupXml"); // load setup
 InstanceManager::getDefault("LocationManagerXml"); // load locations
}

}

/* @(#)LocationManager.java */

