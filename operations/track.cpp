#include "track.h"
#include "location.h"
#include "locationmanagerxml.h"
#include "xml.h"
#include "rollingstock.h"
#include "setup.h"
#include "engine.h"
#include "consist.h"
#include "pool.h"
#include "car.h"
#include "cartypes.h"
#include "enginetypes.h"
#include "control.h"
#include "stringutil.h"
#include "locationmanager.h"
#include "carroads.h"
#include "rosterentry.h"
#include "carload.h"
#include "schedule.h"
#include "scheduleitem.h"
#include "schedulemanager.h"
#include "carmanager.h"
#include "carloads.h"
#include "train.h"
#include "route.h"
#include "kernel.h"
#include "trainmanager.h"
#include "trainschedule.h"
#include "trainschedulemanager.h"
#include "instancemanager.h"

//Track::Track(QObject *parent) :
//  QObject(parent)
//{
//}

/**
 * Represents a location (track) on the layout Can be a spur, yard, staging, or
 * interchange track.
 *
 * @author Daniel Boudreau Copyright (C) 2008 - 2014
 * @version $Revision: 29682 $
 */
///*public*/ class Track {
namespace Operations
{
 /*public*/ /*static*/ /*final*/ QString Track::NONE = "";

 /*public*/ /*static*/ /*final*/ QString Track::ANY = "Any"; // track accepts any train or route
 /*public*/ /*static*/ /*final*/ QString Track::TRAINS = "trains"; // NOI18N track only accepts certain trains
 /*public*/ /*static*/ /*final*/ QString Track::ROUTES = "routes"; // NOI18N track only accepts certain routes
 /*public*/ /*static*/ /*final*/ QString Track::EXCLUDE_TRAINS = "excludeTrains"; // NOI18N track excludes certain trains
 /*public*/ /*static*/ /*final*/ QString Track::EXCLUDE_ROUTES = "excludeRoutes"; // NOI18N track excludes certain routes

 // load options
 /*private*/ /*static*/ /*final*/ int Track::SWAP_GENERIC_LOADS = 1;
 /*private*/ /*static*/ /*final*/ int Track::EMPTY_CUSTOM_LOADS = 2;
 /*private*/ /*static*/ /*final*/ int Track::GENERATE_CUSTOM_LOADS = 4;
 /*private*/ /*static*/ /*final*/ int Track::GENERATE_CUSTOM_LOADS_ANY_SPUR = 8;
 /*private*/ /*static*/ /*final*/ int Track::EMPTY_GENERIC_LOADS = 16;
 /*private*/ /*static*/ /*final*/ int Track::GENERATE_CUSTOM_LOADS_ANY_STAGING_TRACK = 32;

 // block options
 /*private*/ /*static*/ /*final*/ int Track::BLOCK_CARS = 1;

 // order cars are serviced
 /*public*/ /*static*/ /*final*/ QString Track::NORMAL = tr("Normal");
 /*public*/ /*static*/ /*final*/ QString Track::FIFO = tr("FIFO");
 /*public*/ /*static*/ /*final*/ QString Track::LIFO = tr("LIFO");

 // the four types of tracks
 /*public*/ /*static*/ /*final*/ QString Track::STAGING = "Staging";
 /*public*/ /*static*/ /*final*/ QString Track::INTERCHANGE = "Interchange";
 /*public*/ /*static*/ /*final*/ QString Track::YARD = "Yard";
 /*public*/ /*static*/ /*final*/ QString Track::SPUR = "Siding"; // NOI18N note that early code used Siding as the spur type

 // train directions serviced by this track
 /*public*/ /*static*/ /*final*/ int Track::EAST = 1;
 /*public*/ /*static*/ /*final*/ int Track::WEST = 2;
 /*public*/ /*static*/ /*final*/ int Track::NORTH = 4;
 /*public*/ /*static*/ /*final*/ int Track::SOUTH = 8;

 // how roads are serviced by this track
 /*public*/ /*static*/ /*final*/ QString Track::ALL_ROADS = tr("All"); // track accepts all roads
 /*public*/ /*static*/ /*final*/ QString Track::INCLUDE_ROADS = tr("Include"); // track accepts only certain roads
 /*public*/ /*static*/ /*final*/ QString Track::EXCLUDE_ROADS = tr("Exclude"); // track does not accept certain roads

 // load options
 /*public*/ /*static*/ /*final*/ QString Track::ALL_LOADS = tr("All"); // track services all loads
 /*public*/ /*static*/ /*final*/ QString Track::INCLUDE_LOADS = tr("Include");
 /*public*/ /*static*/ /*final*/ QString Track::EXCLUDE_LOADS = tr("Exclude");

 // destination options
 /*public*/ /*static*/ /*final*/ QString Track::ALL_DESTINATIONS = tr("All"); // track services all loads
 /*public*/ /*static*/ /*final*/ QString Track::INCLUDE_DESTINATIONS = tr("Include");
 /*public*/ /*static*/ /*final*/ QString Track::EXCLUDE_DESTINATIONS = tr("Exclude");

 // schedule modes
 /*public*/ /*static*/ /*final*/ int Track::SEQUENTIAL = 0;
 /*public*/ /*static*/ /*final*/ int Track::MATCH = 1;

 // schedule status
 /*public*/ /*static*/ /*final*/ QString Track::SCHEDULE_OKAY = "";


 // return status when checking rolling stock
 /*public*/ /*static*/ /*final*/ QString Track::OKAY = tr("okay");
 /*public*/ /*static*/ /*final*/ QString Track::LENGTH = tr("rollingStock") + " " + tr("length");
 /*public*/ /*static*/ /*final*/ QString Track::TYPE = tr("type");
 /*public*/ /*static*/ /*final*/ QString Track::ROAD = tr("road");
 /*public*/ /*static*/ /*final*/ QString Track::LOAD = tr("load");
 /*public*/ /*static*/ /*final*/ QString Track::CAPACITY = tr("track") + " " + tr("capacity");
 /*public*/ /*static*/ /*final*/ QString Track::SCHEDULE = tr("schedule");
 /*public*/ /*static*/ /*final*/ QString Track::CUSTOM = tr("custom");
 /*public*/ /*static*/ /*final*/ QString Track::DESTINATION = tr("carDestination");

 // For property change
 /*public*/ /*static*/ /*final*/ QString Track::TYPES_CHANGED_PROPERTY = "trackRollingStockTypes"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::ROADS_CHANGED_PROPERTY = "trackRoads"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::NAME_CHANGED_PROPERTY = "trackName"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::LENGTH_CHANGED_PROPERTY = "trackLength"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::MIN_LENGTH_CHANGED_PROPERTY = "trackMinLength"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::SCHEDULE_CHANGED_PROPERTY = "trackScheduleChange"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::DISPOSE_CHANGED_PROPERTY = "trackDispose"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::TRAINDIRECTION_CHANGED_PROPERTY = "trackTrainDirection"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::DROP_CHANGED_PROPERTY = "trackDrop"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::PICKUP_CHANGED_PROPERTY = "trackPickup"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::TRACK_TYPE_CHANGED_PROPERTY = "trackType"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::LOADS_CHANGED_PROPERTY = "trackLoads"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::POOL_CHANGED_PROPERTY = "trackPool"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::PLANNEDPICKUPS_CHANGED_PROPERTY = "plannedPickUps"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::LOAD_OPTIONS_CHANGED_PROPERTY = "trackLoadOptions"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::DESTINATIONS_CHANGED_PROPERTY = "trackDestinations"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::DESTINATION_OPTIONS_CHANGED_PROPERTY = "trackDestinationOptions"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::SCHEDULE_MODE_CHANGED_PROPERTY = "trackScheduleMode"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::SCHEDULE_ID_CHANGED_PROPERTY = "trackScheduleId"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::SERVICE_ORDER_CHANGED_PROPERTY = "trackServiceOrder"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::ALTERNATE_TRACK_CHANGED_PROPERTY = "trackAlternate"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Track::TRACK_BLOCKING_ORDER_CHANGED_PROPERTY = "trackBlockingOrder"; // NOI18N

 /*public*/ Track::Track(QString id, QString name, QString type, Location* location,QObject *parent) :
 QObject(parent)
 {
  common();
  log->debug(tr("New (%1) track (%2) id: %3").arg(type).arg(name).arg(id));

  _location = location;
  _trackType = type;
  _name = name;
  _id = id;

 }
 void Track::common()
 {
  log = new Logger("Track");
  _id = NONE;
  _name = NONE;
  _trackType = NONE; // yard, spur, interchange or staging
  _alternateTrackId = NONE; // the alternate track id
  _roadOption = ALL_ROADS; // controls which car roads are accepted
 _trainDir = EAST + WEST + NORTH + SOUTH; // train direction served by this track
 _numberRS = 0; // number of cars and engines
 _numberCars = 0; // number of cars
 _numberEngines = 0; // number of engines
 _pickupRS = 0; // number of pick ups by trains
 _dropRS = 0; // number of set outs by trains
 _length = 0; // length of track
 _reserved = 0; // length of track reserved by trains
 _reservedLengthDrops = 0; // length of track reserved for drops
 _numberCarsInRoute = 0; // number of cars in route to this track
 _usedLength = 0; // length of track filled by cars and engines
 _ignoreUsedLengthPercentage = 0; // value between 0 and 100, 100 = ignore 100%
 _moves = 0; // count of the drops since creation
 _blockingOrder = 0; // defines the order tracks are serviced by trains
  _comment = NONE;
  _pool = NULL;
  _loadOptions = 0;
  _blockOptions = 0;
  _order = NORMAL;
  _minimumLength = 0;

  _commentPickup = NONE;
  _commentSetout = NONE;
  _commentBoth = NONE;

  _loadOption = ALL_LOADS; // receive track load restrictions
  _shipLoadOption = ALL_LOADS; // ship track load restrictions

  _destinationOption = ALL_DESTINATIONS; // track destination restriction

 // schedule options
  _scheduleName = NONE; // Schedule name if there's one
  _scheduleId = NONE; // Schedule id if there's one
  _scheduleItemId = NONE; // the current scheduled item id
 _scheduleCount = 0; // the number of times the item has been delivered
 _reservedInRoute = 0; // length of cars in route to this track
 _reservationFactor = 100; // percentage of track space for cars in route
 _mode = MATCH; // default is match mode

 // drop options
  _dropOption = ANY; // controls which route or train can set out cars
  _pickupOption = ANY; // controls which route or train can pick up cars
  _roadList = QStringList();
  _destinationIdList = QStringList();
  _dropList = QStringList();
  _pickupList = QStringList();


  // a new track accepts all types
  setTypeNames(CarTypes::instance()->getNames());
  setTypeNames(EngineTypes::instance()->getNames());
  pcs = new PropertyChangeSupport(this);
  _typeList = QStringList();
  _loadList = QStringList();
   debugFlag = false;
   _shipLoadList =  QStringList();

 }

 /**
  * Creates a copy of this track.
  *
  * @param newName     The name of the new track.
  * @param newLocation The location of the new track.
  * @return Track
  */
 /*public*/ Track* Track::copyTrack(QString newName, Location* newLocation) {
     Track* newTrack = newLocation->addTrack(newName, getTrackType());

     newTrack->clearTypeNames(); // all types are accepted by a new track
#if 1
     newTrack->setAddCustomLoadsAnySpurEnabled(isAddCustomLoadsAnySpurEnabled());
     newTrack->setAddCustomLoadsAnyStagingTrackEnabled(isAddCustomLoadsAnyStagingTrackEnabled());
     newTrack->setAddCustomLoadsEnabled(isAddCustomLoadsEnabled());

     newTrack->setAlternateTrack(getAlternateTrack());
     newTrack->setBlockCarsEnabled(isBlockCarsEnabled());
     newTrack->setComment(getComment());
     newTrack->setCommentBoth(getCommentBoth());
     newTrack->setCommentPickup(getCommentPickup());
     newTrack->setCommentSetout(getCommentSetout());

     newTrack->setDestinationOption(getDestinationOption());
     newTrack->setDestinationIds(getDestinationIds());

     newTrack->setDropOption(getDropOption()); // must set option before setting ids
     newTrack->setDropIds(getDropIds());

     newTrack->setIgnoreUsedLengthPercentage(getIgnoreUsedLengthPercentage());
     newTrack->setLength(getLength());
     newTrack->setLoadEmptyEnabled(isLoadEmptyEnabled());
     newTrack->setLoadNames(getLoadNames());
     newTrack->setLoadOption(getLoadOption());
     newTrack->setLoadSwapEnabled(isLoadSwapEnabled());

     newTrack->setPickupOption(getPickupOption()); // must set option before setting ids
     newTrack->setPickupIds(getPickupIds());

     // track pools are only shared within a specific location
     if (getPool() != NULL) {
         newTrack->setPool(newLocation->addPool(getPool()->getName()));
         newTrack->setMinimumLength(getMinimumLength());
     }
     newTrack->setRemoveCustomLoadsEnabled(isRemoveCustomLoadsEnabled());
     newTrack->setReservationFactor(getReservationFactor());
     newTrack->setRoadNames(getRoadNames());
     newTrack->setRoadOption(getRoadOption());
     newTrack->setScheduleId(getScheduleId());
     newTrack->setScheduleMode(getScheduleMode());
     newTrack->setServiceOrder(getServiceOrder());
     newTrack->setShipLoadNames(getShipLoadNames());
     newTrack->setShipLoadOption(getShipLoadOption());
     newTrack->setTrainDirections(getTrainDirections());
     newTrack->setTypeNames(getTypeNames());
#endif
     return newTrack;
 }

 // for combo boxes
 /*public*/ QString Track::toString() {
     return _name;
 }

 /*public*/ QString Track::getId() {
     return _id;
 }

 /*public*/ Location* Track::getLocation() {
     return _location;
 }

 /*public*/ void Track::setName(QString name) {
     QString old = _name;
     _name = name;
     if (old!=(name)) {
         setDirtyAndFirePropertyChange(NAME_CHANGED_PROPERTY, old, name);
     }
 }

 /*public*/ QString Track::getName() {
     return _name;
 }

 /**
  * Gets the track type
  *
  * @return Track::SPUR Track::YARD Track::INTERCHANGE or Track::STAGING
  */
 /*public*/ QString Track::getTrackType() {
     return _trackType;
 }

 /**
  * Sets the track type, spur, interchange, yard, staging
  *
  * @param type Track::SPUR Track::YARD Track::INTERCHANGE Track::STAGING
  */
 /*public*/ void Track::setTrackType(QString type) {
     QString old = _trackType;
     _trackType = type;
     if (old!=(type)) {
         setDirtyAndFirePropertyChange(TRACK_TYPE_CHANGED_PROPERTY, old, type);
     }
 }

 /*public*/ QString Track::getTrackTypeName() {
     return (getTrackTypeName(getTrackType()));
 }

 /*public*/ /*static*/ QString Track::getTrackTypeName(QString trackType) {
     if (trackType==(Track::SPUR)) {
         return tr("Spur").toLower();
     }
     if (trackType==(Track::YARD)) {
         return tr("Yard").toLower();
     }
     if (trackType==(Track::INTERCHANGE)) {
         return tr("Class/Interchange"); // this is an abbreviation
     }
     if (trackType==(Track::STAGING)) {
         return tr("Staging").toLower();
     }
     return ("unknown");  // NOI18N
 }
#if 0
 //@Deprecated
 // as of 10/27/2013 version 3.5.5
 /*public*/ void setLocType(QString type) {
     setTrackType(type);
 }
#endif
 /*public*/ void Track::setLength(int length) {
     int old = _length;
     _length = length;
     if (old != length) {
         setDirtyAndFirePropertyChange(LENGTH_CHANGED_PROPERTY, (old), (length));
     }
 }

 /*public*/ int Track::getLength() {
     return _length;
 }

 /**
  * Sets the minimum length of this track when the track is in a pool.
  *
  * @param length minimum
  */
 /*public*/ void Track::setMinimumLength(int length) {
     int old = _minimumLength;
     _minimumLength = length;
     if (old != length) {
         setDirtyAndFirePropertyChange(MIN_LENGTH_CHANGED_PROPERTY, (old), (length));
     }
 }

 /*public*/ int Track::getMinimumLength() {
     return _minimumLength;
 }

 /*public*/ void Track::setReserved(int reserved) {
     int old = _reserved;
     _reserved = reserved;
     if (old != reserved) {
         setDirtyAndFirePropertyChange("reserved", (old), // NOI18N
                 (reserved)); // NOI18N
     }
 }

 /*public*/ int Track::getReserved() {
     return _reserved;
 }

 /*public*/ void Track::addReservedInRoute(Car* car) {
     int old = _reservedInRoute;
     _numberCarsInRoute++;
     _reservedInRoute = old + car->getTotalLength();
     if (old != _reservedInRoute) {
         setDirtyAndFirePropertyChange("reservedInRoute", (old), // NOI18N
                 (_reservedInRoute)); // NOI18N
     }
 }

 /*public*/ void Track::deleteReservedInRoute(Car* car) {
     int old = _reservedInRoute;
     _numberCarsInRoute--;
     _reservedInRoute = old - car->getTotalLength();
     if (old != _reservedInRoute) {
         setDirtyAndFirePropertyChange("reservedInRoute", (old), // NOI18N
                 (_reservedInRoute)); // NOI18N
     }
 }

 /**
  * Used to determine how much track space is going to be consumed by cars in
  * route to this track. See isSpaceAvailable().
  *
  * @return The length of all cars in route to this track including couplers->
  */
 /*public*/ int Track::getReservedInRoute() {
     return _reservedInRoute;
 }

 /*public*/ int Track::getNumberOfCarsInRoute() {
     return _numberCarsInRoute;
 }

 /**
  * Set the reservation factor. Default 100 (100%). Used by the program when
  * generating car loads from staging. A factor of 100% allows the program to
  * fill a track with car loads. Numbers over 100% can overload a track.
  *
  * @param factor A number from 0 to 10000.
  */
 /*public*/ void Track::setReservationFactor(int factor) {
     int old = _reservationFactor;
     _reservationFactor = factor;
     if (old != factor) {
         setDirtyAndFirePropertyChange("reservationFactor", old, factor); // NOI18N
     }
 }

 /*public*/ int Track::getReservationFactor() {
     return _reservationFactor;
 }

 /**
  * Sets the mode of operation for the schedule assigned to this track.
  *
  * @param mode Track::SEQUENTIAL or Track::MATCH
  */
 /*public*/ void Track::setScheduleMode(int mode) {
     int old = _mode;
     _mode = mode;
     if (old != mode) {
         setDirtyAndFirePropertyChange(SCHEDULE_MODE_CHANGED_PROPERTY, old, mode); // NOI18N
     }
 }

 /**
  * Gets the mode of operation for the schedule assigned to this track.
  *
  * @return Mode of operation: Track::SEQUENTIAL or Track::MATCH
  */
 /*public*/ int Track::getScheduleMode() {
     return _mode;
 }

 /*public*/ void Track::setAlternateTrack(Track* track) {
     Track* oldTrack = _location->getTrackById(_alternateTrackId);
     QString old = _alternateTrackId;
     if (track != NULL) {
         _alternateTrackId = track->getId();
     } else {
         _alternateTrackId = NONE;
     }
     if (old!=(_alternateTrackId)) {
         setDirtyAndFirePropertyChange(ALTERNATE_TRACK_CHANGED_PROPERTY, VPtr<Track>::asQVariant(oldTrack), VPtr<Track>::asQVariant(track)); // NOI18N
     }
 }

 /*public*/ Track* Track::getAlternateTrack() {
     return _location->getTrackById(_alternateTrackId);
 }

 /**
  * Used to determine if there's space available at this track for the car->
  * Considers cars in route to this track. Used to prevent overloading the
  * track with cars from staging or cars with custom loads.
  *
  * @param car The car to be set out.
  * @return true if space available.
  */
 /*public*/ bool Track::isSpaceAvailable(Car* car) {
     int carLength = car->getTotalLength();
     if (car->getKernel() != NULL) {
         carLength = car->getKernel()->getTotalLength();
     }
     int trackLength = getLength();
     // is the car or kernel too long for the track?
     if (trackLength < carLength) {
         return false;
     }
     // ignore reservation factor unless car is departing staging
     if (car->getTrack() != NULL && car->getTrack()->getTrackType()==(STAGING)) {
         return (getLength() * getReservationFactor() / 100 - (getReservedInRoute() + carLength) >= 0);
     }
     // if there's alternate, include that length in the calculation
     if (getAlternateTrack() != NULL) {
         trackLength = trackLength + getAlternateTrack()->getLength();
     }
     return (trackLength - (getReservedInRoute() + carLength) >= 0);
 }

 /*public*/ void Track::setUsedLength(int length) {
     int old = _usedLength;
     _usedLength = length;
     if (old != length) {
         setDirtyAndFirePropertyChange("usedLength", (old), // NOI18N
                 (length)); // NOI18N
     }
 }

 /*public*/ int Track::getUsedLength() {
     return _usedLength;
 }

 /**
  * The amount of consumed track space to be ignored when sending new rolling
  * stock to the track.
  *
  * @param percentage a number between 0 and 100
  */
 /*public*/ void Track::setIgnoreUsedLengthPercentage(int percentage) {
     int old = _ignoreUsedLengthPercentage;
     _ignoreUsedLengthPercentage = percentage;
     if (old != percentage) {
         setDirtyAndFirePropertyChange(PLANNEDPICKUPS_CHANGED_PROPERTY, (old), (percentage));
     }
 }

 /*public*/ int Track::getIgnoreUsedLengthPercentage() {
     return _ignoreUsedLengthPercentage;
 }

 /**
  * Sets the number of rolling stock (cars and or engines) on this track
  *
  * @param number
  */
 /*private*/ void Track::setNumberRS(int number) {
     int old = _numberRS;
     _numberRS = number;
     if (old != number) {
         setDirtyAndFirePropertyChange("numberRS", (old), // NOI18N
                 (number)); // NOI18N
     }
 }

 /**
  * Sets the number of cars on this track
  *
  * @param number
  */
 /*private*/ void Track::setNumberCars(int number) {
     int old = _numberCars;
     _numberCars = number;
     if (old != number) {
         setDirtyAndFirePropertyChange("numberCars", (old), // NOI18N
                 (number)); // NOI18N
     }
 }

 /**
  * Sets the number of engines on this track
  *
  * @param number
  */
 /*private*/ void Track::setNumberEngines(int number) {
     int old = _numberEngines;
     _numberEngines = number;
     if (old != number) {
         setDirtyAndFirePropertyChange("numberEngines", (old), // NOI18N
                 (number)); // NOI18N
     }
 }

 /**
  *
  * @return The number of rolling stock (cars and engines) on this track
  */
 /*public*/ int Track::getNumberRS() {
     return _numberRS;
 }

 /**
  *
  * @return The number of cars on this track
  */
 /*public*/ int Track::getNumberCars() {
     return _numberCars;
 }

 /**
  *
  * @return The number of engines on this track
  */
 /*public*/ int Track::getNumberEngines() {
     return _numberEngines;
 }

 /**
  * Adds rolling stock to a specific track.
  *
  * @param rs
  */
 /*public*/ void Track::addRS(RollingStock* rs) {
     setNumberRS(getNumberRS() + 1);
     if (QString(rs->metaObject()->className()) == "Car") {
         setNumberCars(getNumberCars() + 1);
     }
     else if (QString(rs->metaObject()->className()) == "Engine") {
         setNumberEngines(getNumberEngines() + 1);
     }
     setUsedLength(getUsedLength() + rs->getTotalLength());
 }

 /*public*/ void Track::deleteRS(RollingStock* rs) {
     setNumberRS(getNumberRS() - 1);
     if (QString(rs->metaObject()->className()) == "Car") {
         setNumberCars(getNumberCars() - 1);
     }
     else if (QString(rs->metaObject()->className()) == "Engine") {
         setNumberEngines(getNumberEngines() - 1);
     }
     setUsedLength(getUsedLength() - rs->getTotalLength());
 }

 /**
  * Increments the number of cars and or engines that will be picked up by a
  * train from this track.
  */
 /*public*/ void Track::addPickupRS(RollingStock* rs) {
     int old = _pickupRS;
     _pickupRS++;
     if (Setup::isBuildAggressive()) {
         setReserved(getReserved() - rs->getTotalLength());
     }
     setDirtyAndFirePropertyChange("pickupRS", (old), // NOI18N
             (_pickupRS));
 }

 /*public*/ void Track::deletePickupRS(RollingStock* rs) {
     int old = _pickupRS;
     if (Setup::isBuildAggressive()) {
         setReserved(getReserved() + rs->getTotalLength());
     }
     _pickupRS--;
     setDirtyAndFirePropertyChange("pickupRS", (old), // NOI18N
             (_pickupRS));
 }

/**
*
* @return the number of rolling stock (cars and or locos) that are
*         scheduled for pick up from this track.
*/
/*public*/ int Track::getPickupRS() {
  return _pickupRS;
}

/*public*/ int Track::getDropRS() {
 return _dropRS;
}

/*public*/ void Track::addDropRS(RollingStock* rs) {
 int old = _dropRS;
 _dropRS++;
 setMoves(getMoves() + 1);
 setReserved(getReserved() + rs->getTotalLength());
 _reservedLengthDrops = _reservedLengthDrops + rs->getTotalLength();
 setDirtyAndFirePropertyChange("addDropRS", (old), (_dropRS)); // NOI18N
}

/*public*/ void Track::deleteDropRS(RollingStock* rs) {
 int old = _dropRS;
 _dropRS--;
 setReserved(getReserved() - rs->getTotalLength());
 _reservedLengthDrops = _reservedLengthDrops - rs->getTotalLength();
 setDirtyAndFirePropertyChange("deleteDropRS", (old), // NOI18N
         (_dropRS));
}

/*public*/ void Track::setComment(QString comment) {
 QString old = _comment;
 _comment = comment;
 if (old!=(comment)) {
     setDirtyAndFirePropertyChange("trackComment", old, comment); // NOI18N
 }
}

/*public*/ QString Track::getComment() {
     return _comment;
}

 /*public*/ void Track::setCommentPickup(QString comment) {
     QString old = _commentPickup;
     _commentPickup = comment;
     if (old!=(comment)) {
         setDirtyAndFirePropertyChange("trackCommentPickup", old, comment); // NOI18N
     }
 }

 /*public*/ QString Track::getCommentPickup() {
     return _commentPickup;
 }

 /*public*/ void Track::setCommentSetout(QString comment) {
     QString old = _commentSetout;
     _commentSetout = comment;
     if (old!=(comment)) {
         setDirtyAndFirePropertyChange("trackCommentSetout", old, comment); // NOI18N
     }
 }

 /*public*/ QString Track::getCommentSetout() {
     return _commentSetout;
 }

 /*public*/ void Track::setCommentBoth(QString comment) {
     QString old = _commentBoth;
     _commentBoth = comment;
     if (old!=(comment)) {
         setDirtyAndFirePropertyChange("trackCommentBoth", old, comment); // NOI18N
     }
 }

 /*public*/ QString Track::getCommentBoth() {
     return _commentBoth;
 }


 /**
  * Returns all of the rolling stock type names serviced by this track.
  *
  * @return rolling stock type names
  */
 /*public*/ QStringList Track::getTypeNames() {
     QVector<QString> types = QVector<QString>(_typeList.size());
     for (int i = 0; i < _typeList.size(); i++) {
         types.replace(i, _typeList.at(i));
     }
     return types.toList();
 }

 /*private*/ void Track::setTypeNames(QStringList types) {
if (types.length() == 0) {
         return;
     }
     StringUtil::sort(types);
     foreach (QString type, types) {
         if (!_typeList.contains(type)) {
             _typeList.append(type);
         }
     }
 }

 /*private*/ void Track::clearTypeNames() {
     _typeList.clear();
 }

 /*public*/ void Track::addTypeName(QString type) {
     // insert at start of list, sort later
     if (type == NULL || _typeList.contains(type)) {
         return;
     }
     _typeList.insert(0, type);
     log->debug(tr("Track (%1) add rolling stock type (%2)").arg(getName()).arg(type));
     setDirtyAndFirePropertyChange(TYPES_CHANGED_PROPERTY, _typeList.size() - 1, _typeList.size());
 }

 /*public*/ void Track::deleteTypeName(QString type) {
     if (!_typeList.contains(type)) {
         return;
     }
     _typeList.removeAt(_typeList.indexOf(type));
     log->debug(tr("Track (%1) delete rolling stock type (%2)").arg(getName()).arg(type));
     setDirtyAndFirePropertyChange(TYPES_CHANGED_PROPERTY, _typeList.size() + 1, _typeList.size());
 }

 /*public*/ bool Track::acceptsTypeName(QString type) {
     if (!_location->acceptsTypeName(type)) {
         return false;
     }
     return _typeList.contains(type);
 }

 /**
  * Sets the train directions that can service this track
  *
  * @param direction EAST, WEST, NORTH, SOUTH
  */
 /*public*/ void Track::setTrainDirections(int direction) {
     int old = _trainDir;
     _trainDir = direction;
     if (old != direction) {
         setDirtyAndFirePropertyChange(TRAINDIRECTION_CHANGED_PROPERTY, (old), (direction));
     }
 }

 /*public*/ int Track::getTrainDirections() {
     return _trainDir;
 }

 /*public*/ QString Track::getRoadOption() {
     return _roadOption;
 }

 /**
  * Set the road option for this track.
  *
  * @param option ALLROADS, INCLUDEROADS, or EXCLUDEROADS
  */
 /*public*/ void Track::setRoadOption(QString option) {
     QString old = _roadOption;
     _roadOption = option;
     setDirtyAndFirePropertyChange(ROADS_CHANGED_PROPERTY, old, option);
 }


 /*public*/ QStringList Track::getRoadNames() {
     QVector<QString> roads = QVector<QString>(_roadList.size());
     for (int i = 0; i < _roadList.size(); i++) {
      roads.replace(i, _roadList.at(i));
     }
     if (_roadList.size() == 0) {
      return roads.toList();
     }
     StringUtil::sort(roads.toList());
     return roads.toList();
 }

 /*private*/ void Track::setRoadNames(QStringList roads) {
if (roads.length() == 0) {
         return;
     }
     StringUtil::sort(roads);
     foreach (QString roadName, roads) {
         if (roadName!=(NONE)) {
             _roadList.append(roadName);
         }
     }
 }

 /*public*/ void Track::addRoadName(QString road) {
     if (_roadList.contains(road)) {
         return;
     }
     _roadList.append(road);
     log->debug(tr("Track (%1) add car road (%2)").arg(getName()).arg(road));
     setDirtyAndFirePropertyChange(ROADS_CHANGED_PROPERTY, _roadList.size() - 1, _roadList.size());
 }

 /*public*/ void Track::deleteRoadName(QString road) {
     _roadList.removeOne(road);
     log->debug(tr("Track (%1) delete car road (%1)").arg(getName()).arg(road));
     setDirtyAndFirePropertyChange(ROADS_CHANGED_PROPERTY, _roadList.size() + 1, _roadList.size());
 }

 /*public*/ bool Track::acceptsRoadName(QString road) {
     if (_roadOption==(ALL_ROADS)) {
         return true;
     }
     if (_roadOption==(INCLUDE_ROADS)) {
         return _roadList.contains(road);
     }
     // exclude!
     return !_roadList.contains(road);
 }

 /*public*/ bool Track::containsRoadName(QString road) {
     return _roadList.contains(road);
 }

 /**
  * Gets the car receive load option for this track.
  *
  * @return ALL_LOADS INCLUDE_LOADS EXCLUDE_LOADS
  */
 /*public*/ QString Track::getLoadOption() {
     return _loadOption;
 }

 /**
  * Set how this track deals with receiving car loads
  *
  * @param option ALL_LOADS INCLUDE_LOADS EXCLUDE_LOADS
  */
 /*public*/ void Track::setLoadOption(QString option) {
     QString old = _loadOption;
     _loadOption = option;
     setDirtyAndFirePropertyChange(LOADS_CHANGED_PROPERTY, old, option);
 }


 /*private*/ void Track::setLoadNames(QStringList loads) {
if (loads.length() == 0) {
         return;
     }
     StringUtil::sort(loads);
     foreach (QString loadName, loads) {
         if (loadName!=(NONE)) {
             _loadList.append(loadName);
         }
     }
 }

 /**
  * Provides a list of receive loads that the track will either service or
  * exclude. See setLoadOption
  *
  * @return Array of load names as Strings
  */
 /*public*/ QStringList Track::getLoadNames()
 {
  QVector<QString> loads = QVector<QString>(_loadList.size());
  for (int i = 0; i < _loadList.size(); i++) {
      loads.replace(i, _loadList.at(i));
  }
  if (_loadList.size() == 0) {
      return loads.toList();
  }
  StringUtil::sort(loads.toList());
  return loads.toList();
 }

 /**
  * Add a receive load that the track will either service or exclude. See
  * setLoadOption
  *
  * @return true if load name was added, false if load name wasn't in the
  *         list.
  */
 /*public*/ bool Track::addLoadName(QString load) {
     if (_loadList.contains(load)) {
         return false;
     }
     _loadList.append(load);
     log->debug(tr("track (%1) add car load (%2)").arg(getName()).arg(load));
     setDirtyAndFirePropertyChange(LOADS_CHANGED_PROPERTY, _loadList.size() - 1, _loadList.size());
     return true;
 }

 /**
  * Delete a receive load name that the track will either service or exclude.
  * See setLoadOption
  *
  * @return true if load name was removed, false if load name wasn't in the
  *         list.
  */
 /*public*/ bool Track::deleteLoadName(QString load) {
     if (!_loadList.contains(load)) {
         return false;
     }
     _loadList.removeOne(load);
     log->debug(tr("track (%1) delete car load (%2)").arg(getName()).arg(load));
     setDirtyAndFirePropertyChange(LOADS_CHANGED_PROPERTY, _loadList.size() + 1, _loadList.size());
     return true;
 }

 /**
  * Determine if track will service a specific receive load name.
  *
  * @param load the load name to check.
  * @return true if track will service this load.
  */
 /*public*/ bool Track::acceptsLoadName(QString load) {
     if (_loadOption==(ALL_LOADS)) {
         return true;
     }
     if (_loadOption==(INCLUDE_LOADS)) {
         return _loadList.contains(load);
     }
     // exclude!
     return !_loadList.contains(load);
 }

 /**
  * Determine if track will service a specific receive load and car type.
  *
  * @param load the load name to check.
  * @param type the type of car used to carry the load.
  * @return true if track will service this load.
  */
 /*public*/ bool Track::acceptsLoad(QString load, QString type) {
     if (_loadOption==(ALL_LOADS)) {
         return true;
     }
     if (_loadOption==(INCLUDE_LOADS)) {
         return _loadList.contains(load) || _loadList.contains(type + CarLoad::SPLIT_CHAR + load);
     }
     // exclude!
     return !_loadList.contains(load) && !_loadList.contains(type + CarLoad::SPLIT_CHAR + load);
 }

 /**
  * Gets the car ship load option for this track.
  *
  * @return ALL_LOADS INCLUDE_LOADS EXCLUDE_LOADS
  */
 /*public*/ QString Track::getShipLoadOption() {
     return _shipLoadOption;
 }

 /**
  * Set how this track deals with shipping car loads
  *
  * @param option ALL_LOADS INCLUDE_LOADS EXCLUDE_LOADS
  */
 /*public*/ void Track::setShipLoadOption(QString option) {
     QString old = _shipLoadOption;
     _shipLoadOption = option;
     setDirtyAndFirePropertyChange(LOADS_CHANGED_PROPERTY, old, option);
 }


 /*private*/ void Track::setShipLoadNames(QStringList loads) {
     if (loads.length() == 0) {
         return;
     }
     StringUtil::sort(loads);
     foreach (QString shipLoadName, loads) {
         if (shipLoadName!=(NONE)) {
             _shipLoadList.append(shipLoadName);
         }
     }
 }

 /**
  * Provides a list of ship loads that the track will either service or
  * exclude. See setShipLoadOption
  *
  * @return Array of load names as Strings
  */
 /*public*/ QStringList Track::getShipLoadNames() {
     QVector<QString> loads = QVector<QString>(_shipLoadList.size());
     for (int i = 0; i < _shipLoadList.size(); i++) {
         loads.replace(i, _shipLoadList.at(i));
     }
     if (_shipLoadList.size() == 0) {
         return loads.toList();
     }
     StringUtil::sort(loads.toList());
     return loads.toList();
 }

 /**
  * Add a ship load that the track will either service or exclude. See
  * setShipLoadOption
  *
  * @return true if load name was added, false if load name wasn't in the
  *         list.
  */
 /*public*/ bool Track::addShipLoadName(QString load) {
     if (_shipLoadList.contains(load)) {
         return false;
     }
     _shipLoadList.append(load);
     log->debug(tr("track (%1) add car load (%2)").arg(getName()).arg(load));
     setDirtyAndFirePropertyChange(LOADS_CHANGED_PROPERTY, _shipLoadList.size() - 1, _shipLoadList.size());
     return true;
 }

 /**
  * Delete a ship load name that the track will either service or exclude.
  * See setLoadOption
  *
  * @return true if load name was removed, false if load name wasn't in the
  *         list.
  */
 /*public*/ bool Track::deleteShipLoadName(QString load) {
     if (!_shipLoadList.contains(load)) {
         return false;
     }
     _shipLoadList.removeOne(load);
     log->debug(tr("track (%1) delete car load (%2)").arg(getName()).arg(load));
     setDirtyAndFirePropertyChange(LOADS_CHANGED_PROPERTY, _shipLoadList.size() + 1, _shipLoadList.size());
     return true;
 }

 /**
  * Determine if track will service a specific ship load name.
  *
  * @param load the load name to check.
  * @return true if track will service this load.
  */
 /*public*/ bool Track::shipsLoadName(QString load) {
     if (_shipLoadOption==(ALL_LOADS)) {
         return true;
     }
     if (_shipLoadOption==(INCLUDE_LOADS)) {
         return _shipLoadList.contains(load);
     }
     // exclude!
     return !_shipLoadList.contains(load);
 }

 /**
  * Determine if track will service a specific ship load and car type.
  *
  * @param load the load name to check.
  * @param type the type of car used to carry the load.
  * @return true if track will service this load.
  */
 /*public*/ bool Track::shipsLoad(QString load, QString type) {
     if (_shipLoadOption==(ALL_LOADS)) {
         return true;
     }
     if (_shipLoadOption==(INCLUDE_LOADS)) {
         return _shipLoadList.contains(load) || _shipLoadList.contains(type + CarLoad::SPLIT_CHAR + load);
     }
     // exclude!
     return !_shipLoadList.contains(load) && !_shipLoadList.contains(type + CarLoad::SPLIT_CHAR + load);
 }

 /*public*/ QString Track::getDropOption() {
     return _dropOption;
 }

 /**
  * Set the car drop option for this track.
  *
  * @param option ANY, TRAINS, or ROUTES
  */
 /*public*/ void Track::setDropOption(QString option) {
     QString old = _dropOption;
     _dropOption = option;
     if (old!=(option)) {
         _dropList.clear();
     }
     setDirtyAndFirePropertyChange(DROP_CHANGED_PROPERTY, old, option);
 }

 /*public*/ QString Track::getPickupOption() {
     return _pickupOption;
 }

 /**
  * Set the car pick up option for this track.
  *
  * @param option ANY, TRAINS, or ROUTES
  */
 /*public*/ void Track::setPickupOption(QString option) {
     QString old = _pickupOption;
     _pickupOption = option;
     if (old!=(option)) {
         _pickupList.clear();
     }
     setDirtyAndFirePropertyChange(PICKUP_CHANGED_PROPERTY, old, option);
 }


 /*public*/ QStringList Track::getDropIds() {
     QVector<QString> ids = QVector<QString>(_dropList.size());
     for (int i = 0; i < _dropList.size(); i++) {
         ids.replace(i, _dropList.at(i));
     }
     return ids.toList();
 }

 /*private*/ void Track::setDropIds(QStringList ids) {
     foreach (QString id, ids) {
         if (id != NULL) {
             _dropList.append(id);
         }
     }
 }

 /*public*/ void Track::addDropId(QString id) {
     if (_dropList.contains(id)) {
         return;
     }
     _dropList.append(id);
     log->debug(tr("Track (%1) add drop id: %2").arg(getName()).arg(id));
     setDirtyAndFirePropertyChange(DROP_CHANGED_PROPERTY, QVariant(), id);
 }

 /*public*/ void Track::deleteDropId(QString id) {
     _dropList.removeOne(id);
     log->debug(tr("Track (%1) delete drop id: %2").arg(getName()).arg(id));
     setDirtyAndFirePropertyChange(DROP_CHANGED_PROPERTY, id, QVariant());
 }

 /**
  * Determine if train can set out cars to this track. Based on the train's
  * id or train's route id. See setDropOption(option).
  *
  * @param train
  * @return true if the train can set out cars to this track.
  */
 /*public*/ bool Track::acceptsDropTrain(Train* train) {
     if (_dropOption==(ANY)) {
         return true;
     }
     // yard tracks accept all trains
     if (getTrackType()==(YARD)) {
         return true;
     }
     if (_dropOption==(TRAINS)) {
         return containsDropId(train->getId());
     }
     if (_dropOption==(EXCLUDE_TRAINS)) {
         return !containsDropId(train->getId());
     } else if (train->getRoute() == NULL) {
         return false;
     }
     return acceptsDropRoute(train->getRoute());
 }

 /*public*/ bool Track::acceptsDropRoute(Route* route) {
     if (_dropOption==(ANY) || _dropOption==(TRAINS) || _dropOption==(EXCLUDE_TRAINS)) {
         return true;
     }
     // yard tracks accept all routes
     if (getTrackType()==(YARD)) {
         return true;
     }
     if (_dropOption==(EXCLUDE_ROUTES)) {
         return !containsDropId(route->getId());
     }
     return containsDropId(route->getId());
 }

 /*public*/ bool Track::containsDropId(QString id) {
     return _dropList.contains(id);
 }


 /*public*/ QStringList Track::getPickupIds() {
     QVector<QString> ids =  QVector<QString>(_pickupList.size());
     for (int i = 0; i < _pickupList.size(); i++) {
         ids.replace(i, _pickupList.at(i));
     }
     return ids.toList();
 }

 /*private*/ void Track::setPickupIds(QStringList ids) {
     foreach (QString id, ids) {
         if (id != NULL) {
             _pickupList.append(id);
         }
     }
 }

 /**
  * Add train or route id to this track.
  *
  * @param id
  */
 /*public*/ void Track::addPickupId(QString id) {
     if (_pickupList.contains(id)) {
         return;
     }
     _pickupList.append(id);
     log->debug(tr("track (%1) add pick up id %2").arg(getName()).arg(id));
     setDirtyAndFirePropertyChange(PICKUP_CHANGED_PROPERTY, QVariant(), id);
 }

 /*public*/ void Track::deletePickupId(QString id) {
     _pickupList.removeOne(id);
     log->debug(tr("track (%1) delete pick up id %2").arg(getName()).arg(id));
     setDirtyAndFirePropertyChange(PICKUP_CHANGED_PROPERTY, id, QVariant());
 }

 /**
  * Determine if train can pick up cars from this track. Based on the train's
  * id or train's route id. See setPickupOption(option).
  *
  * @param train
  * @return true if the train can pick up cars from this track.
  */
 /*public*/ bool Track::acceptsPickupTrain(Train* train) {
     if (_pickupOption==(ANY)) {
         return true;
     }
     // yard tracks accept all trains
     if (getTrackType()==(YARD)) {
         return true;
     }
     if (_pickupOption==(TRAINS)) {
         return containsPickupId(train->getId());
     }
     if (_pickupOption==(EXCLUDE_TRAINS)) {
         return !containsPickupId(train->getId());
     } else if (train->getRoute() == NULL) {
         return false;
     }
     return acceptsPickupRoute(train->getRoute());
 }

 /*public*/ bool Track::acceptsPickupRoute(Route* route) {
     if (_pickupOption==(ANY) || _pickupOption==(TRAINS) || _pickupOption==(EXCLUDE_TRAINS)) {
         return true;
     }
     // yard tracks accept all routes
     if (getTrackType()==(YARD)) {
         return true;
     }
     if (_pickupOption==(EXCLUDE_ROUTES)) {
         return !containsPickupId(route->getId());
     }
     return containsPickupId(route->getId());
 }

 /*public*/ bool Track::containsPickupId(QString id) {
     return _pickupList.contains(id);
 }

 /**
  * Used to determine if track can service the rolling stock.
  *
  * @param rs the car or loco to be tested
  * @return TYPE, ROAD, LENGTH, OKAY
  */
 /*public*/ QString Track::accepts(RollingStock* rs) {
     // first determine if rolling stock can be move to the new location
     if (!acceptsTypeName(rs->getTypeName())) {
         log->debug(tr("Rolling stock (%1) type (%2) not accepted at location (%3, %4) wrong type").arg(rs->toString()).arg(rs
                ->getTypeName()).arg(getLocation()->getName()).arg(getName())); // NOI18N
         return TYPE + " (" + rs->getTypeName() + ")";
     }
     if (!acceptsRoadName(rs->getRoadName())) {
         log->debug(tr("Rolling stock (%1) road (%2) not accepted at location (%3, %4) wrong road").arg(rs->toString()).arg(rs
                 ->getRoadName()).arg(getLocation()->getName()).arg(getName())); // NOI18N
         return ROAD + " (" + rs->getRoadName() + ")";
     }
     // now determine if there's enough space for the rolling stock
     int length = rs->getTotalLength();
    bool ok;
    rs->getLength().toInt(&ok);
    if(!ok)
    {
         return LENGTH + " (" + rs->getLength() + ")";
     }
#if 0
     if (Car.class.isInstance(rs)) {
         Car car = (Car) rs;
         // does this track service the car's /*final*/ destination?
         if (!acceptsDestination(car->getFinalDestination())) {
             // && getLocation() != car->getFinalDestination()) { // 4/14/2014 I can't remember why this was needed
             return DESTINATION + " (" + car->getFinalDestinationName() + ") "
                     + (tr("carIsNotAllowed").arg(getName()}); // no
         }
         // check for car in kernel
         if (car->getKernel() != NULL && car->getKernel().isLead(car)) {
             length = 0;
             for (Car c : car->getKernel().getCars()) {
                 // don't add length for cars already on this track or already going to this track
                 if (c.getTrack() != NULL && c.getTrack()==(this) || c.getDestinationTrack() != NULL
                         && c.getDestinationTrack()==(this)) {
                     continue;
                 }
                 length += c.getTotalLength();
             }
         }
         if (!acceptsLoad(car->getLoadName(), car->getTypeName())) {
             log->debug("Car  (" + rs->toString() + ") load (" + car->getLoadName() + ") not accepted at location ("
                     + getLocation().getName() + ", " // NOI18N
                     + getName() + ") wrong load"); // NOI18N
             return LOAD + " (" + car->getLoadName() + ")";
         }
     }
#endif
     // check for loco in consist
     if (qobject_cast<Engine*>(rs) != NULL) {
         Engine* eng = (Engine*) rs;
         if (eng->getConsist() != NULL && eng->getConsist()->isLead(eng)) {
             length = 0;
             foreach (Engine* e, eng->getConsist()->getEngines()) {
                 // don't add length for locos already on this track or already going to this track
                 if (e->getTrack() != NULL && e->getTrack()==(this) || e->getDestinationTrack() != NULL
                         && e->getDestinationTrack()==(this)) {
                     continue;
                 }
                 length = length + e->getLength().toInt() + RollingStock::COUPLER;
             }
         }
     }
     if (rs->getTrack() != this && rs->getDestinationTrack() != this
             && (getUsedLength() + getReserved() + length) > getLength()) {
         // not enough track length check to see if track is in a pool
         if (getPool() != NULL && getPool()->requestTrackLength(this, length)) {
             return OKAY;
         }
         // ignore used length option?
         if (checkPlannedPickUps(length)) {
             return OKAY;
         }
         // Note that a lot of the code checks for track length being an issue, therefore it has to be the last
         // check.
         // Is rolling stock too long for this track?
         if ((getLength() < length && getPool() == NULL)
                 || (getPool() != NULL && getPool()->getTotalLengthTracks() < length)) {
             return tr("{%1}, rolling stock length {%2} {%3} is greater than track length %4} {%3}").arg(CAPACITY).arg(length).arg(
                 Setup::getLengthUnit().toLower()).arg(getLength());
         }
         log->debug(tr("Rolling stock (%1) not accepted at location (%2, %3) no room!").arg(rs->toString()).arg(getLocation()
                 ->getName()).arg(getName())); // NOI18N
         return tr("{%1} {%2} {%3}, available track space {%4} {%3}").arg(LENGTH).arg(length).arg(
             Setup::getLengthUnit().toLower()).arg(getLength() - (getUsedLength() + getReserved()));
     }
     return OKAY;
 }

 /**
  *
  * @param length
  * @return true if the program should ignore some percentage of the car's
  *         length currently consuming track space.
  */
 /*private*/ bool Track::checkPlannedPickUps(int length) {
     if (getIgnoreUsedLengthPercentage() > 0) {
         // two checks, number of new set outs shouldn't exceed the track length. The second check protects against
         // overloading, the total number of cars shouldn't exceed the track length plus the number of cars to
         // ignore.
         if (getUsedLength() * (100 - getIgnoreUsedLengthPercentage()) / 100 + getReservedLengthDrops() + length <= getLength()
                 && getUsedLength() + getReserved() + length <= getLength()
                 + (getLength() * getIgnoreUsedLengthPercentage() / 100)) {
             return true;
         }
     }
     return false;
 }

 /*public*/ int Track::getReservedLengthDrops() {
     return _reservedLengthDrops;
 }

 /*public*/ int Track::getMoves() {
     return _moves;
 }

 /*public*/ void Track::setMoves(int moves) {
     int old = _moves;
     _moves = moves;
     setDirtyAndFirePropertyChange("trackMoves", old, moves); // NOI18N
 }

 /*public*/ int Track::getBlockingOrder() {
     return _blockingOrder;
 }

 /*public*/ void Track::setBlockingOrder(int order) {
     int old = _blockingOrder;
     _blockingOrder = order;
     setDirtyAndFirePropertyChange(TRACK_BLOCKING_ORDER_CHANGED_PROPERTY, old, order); // NOI18N
 }

 /**
  * Get the service order for this track. Only yards and interchange have
  * this feature.
  *
  * @return Service order: Track::NORMAL, Track::FIFO, Track::LIFO
  */
 /*public*/ QString Track::getServiceOrder() {
     if (getTrackType()==(SPUR) || getTrackType()==(STAGING)) {
         return NORMAL;
     }
     return _order;
 }

 /*public*/ void Track::setServiceOrder(QString order) {
     QString old = _order;
     _order = order;
     setDirtyAndFirePropertyChange(SERVICE_ORDER_CHANGED_PROPERTY, old, order); // NOI18N
 }

 /**
  * Returns the name of the schedule. Note that this returns the schedule
  * name based on the schedule's id. A schedule's name can be modified by the
  * user.
  *
  * @return Schedule name
  */
 /*public*/ QString Track::getScheduleName() {
     if (getScheduleId()==(NONE)) {
         return NONE;
     }
     Schedule* schedule = getSchedule();
     if (schedule == NULL) {
         log->error("No name schedule for id: " + getScheduleId());
         return NONE;
     }
     return schedule->getName();
 }

 /*public*/ Schedule* Track::getSchedule() {
     if (getScheduleId()==(NONE)) {
         return NULL;
     }
     Schedule* schedule = ScheduleManager::instance()->getScheduleById(getScheduleId());
     if (schedule == NULL) {
         log->error("No schedule for id: " + getScheduleId());
     }
     return schedule;
 }

 /*public*/ QString Track::getScheduleId() {
     // Only spurs can have a schedule
     if (getTrackType()!=(SPUR)) {
         return NONE;
     }
     // old code only stored schedule name, so create id if needed.
     if (_scheduleId==(NONE) && _scheduleName!=(NONE)) {
         Schedule* schedule = ScheduleManager::instance()->getScheduleByName(_scheduleName);
         if (schedule == NULL) {
             log->error("No schedule for name: " + _scheduleName);
         } else {
             _scheduleId = schedule->getId();
         }
     }
     return _scheduleId;
 }

 /*public*/ void Track::setScheduleId(QString id) {
     QString old = _scheduleId;
     _scheduleId = id;
     if (old!=(id)) {
         Schedule* schedule = ScheduleManager::instance()->getScheduleById(id);
         if (schedule == NULL) {
             _scheduleName = NONE;
         } else {
             // set the id to the first item in the list
             if (schedule->getItemsBySequenceList().size() > 0) {
                 setScheduleItemId(schedule->getItemsBySequenceList().at(0)->getId());
             }
             setScheduleCount(0);
         }
         setDirtyAndFirePropertyChange(SCHEDULE_ID_CHANGED_PROPERTY, old, id);
     }
 }

 /**
  * Recommend getCurrentScheduleItem() to get the current schedule item for
  * this track. Protects against user deleting a schedule item from the
  * schedule.
  *
  * @return schedule item id
  */
 /*public*/ QString Track::getScheduleItemId() {
     return _scheduleItemId;
 }

 /*public*/ void Track::setScheduleItemId(QString id) {
     log->debug(tr("Set schedule item id (%1) for track (%2)").arg(id).arg(getName()));
     QString old = _scheduleItemId;
     _scheduleItemId = id;
     setDirtyAndFirePropertyChange(SCHEDULE_CHANGED_PROPERTY, old, id);
 }

 /**
  * Get's the current schedule item for this track Protects against user
  * deleting an item in a shared schedule. Recommend using this versus
  * getScheduleItemId() as the id can be obsolete.
  */
 /*public*/ ScheduleItem* Track::getCurrentScheduleItem() {
     Schedule* sch = getSchedule();
     if (sch == NULL) {
         log->debug(tr("Can not find schedule id: (%1) assigned to track (%2)").arg(getScheduleId()).arg(getName()));
         return NULL;
     }
     ScheduleItem* currentSi = sch->getItemById(getScheduleItemId());
     if (currentSi == NULL && sch->getSize() > 0) {
         log->debug(tr("Can not find schedule item id: (%1) for schedule %2").arg(getScheduleItemId()).arg(getScheduleName()));
         // reset schedule
         setScheduleItemId((sch->getItemsBySequenceList().at(0))->getId());
         currentSi = sch->getItemById(getScheduleItemId());
     }
     return currentSi;
 }

 /*public*/ void Track::bumpSchedule() {
     // bump the track move count
     setMoves(getMoves() + 1);
     // bump the schedule count
     setScheduleCount(getScheduleCount() + 1);
     if (getScheduleCount() < getCurrentScheduleItem()->getCount()) {
         return;
     }
     setScheduleCount(0);
     // is the schedule in match mode?
     if (getScheduleMode() == MATCH) {
         return;
     }
     // go to the next item on the schedule
     getNextScheduleItem();
 }

 /*public*/ ScheduleItem* Track::getNextScheduleItem() {
     Schedule* sch = getSchedule();
     if (sch == NULL) {
         log->warn("Can not find schedule (" + getScheduleId() + ") assigned to track (" + getName() + ")");
         return NULL;
     }
     QList<ScheduleItem*> items = sch->getItemsBySequenceList();
     ScheduleItem* nextSi = NULL;
     for (int i = 0; i < items.size(); i++) {
         nextSi = items.at(i);
         if (getCurrentScheduleItem() == nextSi) {
             if (++i < items.size()) {
                 nextSi = items.at(i);
             } else {
                 nextSi = items.at(0);
             }
             setScheduleItemId(nextSi->getId());
             break;
         }
     }
     return nextSi;
 }

 /**
  * Returns how many times the current schedule item has been accessed.
  *
  * @return count
  */
 /*public*/ int Track::getScheduleCount() {
     return _scheduleCount;
 }

 /*public*/ void Track::setScheduleCount(int count) {
     int old = _scheduleCount;
     _scheduleCount = count;
     setDirtyAndFirePropertyChange(SCHEDULE_CHANGED_PROPERTY, old, count);
 }

 /**
  * Check to see if schedule is valid for the track at this location.
  *
  * @return SCHEDULE_OKAY if schedule okay, otherwise an error message.
  */
 /*public*/ QString Track::checkScheduleValid()
 {
  QString status = SCHEDULE_OKAY;
  if (getScheduleId()==(NONE)) {
      return status;
  }
  Schedule* schedule = getSchedule();
  if (schedule == NULL) {
      //return (tr("CanNotFindSchedule").arg(getScheduleId()});
   return tr("Schedule (%1) missing!").arg(getScheduleId());
  }
  QList<ScheduleItem*> scheduleItems = schedule->getItemsBySequenceList();
  if (scheduleItems.size() == 0) {
      return tr("empty");
  }

  foreach (ScheduleItem* si, scheduleItems)
  {
   // check train schedules
   if (si->getSetoutTrainScheduleId()!=(ScheduleItem::NONE)
           && ((TrainScheduleManager*)InstanceManager::getDefault("TrainScheduleManager"))->getScheduleById(si->getSetoutTrainScheduleId()) == NULL)
   {
       status = (tr("Not Valid <%1>").arg(si->getSetoutTrainScheduleId()));
       break;
   }
   if (si->getPickupTrainScheduleId()!=(ScheduleItem::NONE)
           && ((TrainScheduleManager*)InstanceManager::getDefault("TrainScheduleManager"))->getScheduleById(si->getPickupTrainScheduleId()) == NULL)
   {
       status = (tr("Not Valid <%1>").arg(si->getPickupTrainScheduleId()));
       break;
   }
   if (!_location->acceptsTypeName(si->getTypeName())) {
       status = tr("Not Valid <%1>").arg(si->getTypeName());
       break;
   }
   if (!acceptsTypeName(si->getTypeName())) {
       status = (tr("Not Valid <%1>").arg(si->getTypeName()));
       break;
   }
   // check roads, accepted by track, valid road, and there's at least one car with that road
   if (si->getRoadName()!=(ScheduleItem::NONE)
           && (!acceptsRoadName(si->getRoadName()) || !CarRoads::instance()->containsName(si->getRoadName()) || CarManager
           ::instance()->getByTypeAndRoad(si->getTypeName(), si->getRoadName()) == NULL)) {
       status = (tr("Not Valid <%1>").arg(si->getRoadName()));
       break;
   }
   // check loads
   QStringList loads = CarLoads::instance()->getNames(si->getTypeName());
   if (si->getReceiveLoadName()!=(ScheduleItem::NONE)
           && (!acceptsLoad(si->getReceiveLoadName(), si->getTypeName()) || !loads.contains(si
                   ->getReceiveLoadName()))) {
       status = (tr("Not Valid <%1>").arg(si->getReceiveLoadName()));
       break;
   }
   if (si->getShipLoadName()!=(ScheduleItem::NONE) && !loads.contains(si->getShipLoadName())) {
       status = (tr("Not Valid <%1>").arg(si->getShipLoadName()));
       break;
   }
   // check destination
   if (si->getDestination() != NULL
           && (!si->getDestination()->acceptsTypeName(si->getTypeName()) || LocationManager::instance()
           ->getLocationById(si->getDestination()->getId()) == NULL)) {
       status = tr("Not Valid <%1>").arg(si->getDestination()->toString());
       break;
   }
   // check destination track
   if (si->getDestination() != NULL && si->getDestinationTrack() != NULL) {
       if (!si->getDestination()->isTrackAtLocation(si->getDestinationTrack())) {
           status = (tr("Not Valid <%1>").arg(si
               ->getDestinationTrack()->toString()
               + " (" + tr("Track") + ")"));
           break;
       }
       if (!si->getDestinationTrack()->acceptsTypeName(si->getTypeName())) {
           status = (tr("Not Valid <%1>").arg(si
               ->getDestinationTrack()->toString()
               + " (" + tr("Type") + ")"));
           break;
       }
       if (si->getRoadName()!=(ScheduleItem::NONE)
               && !si->getDestinationTrack()->acceptsRoadName(si->getRoadName())) {
           status = (tr("Not Valid <%1>").arg(si
               ->getDestinationTrack()->toString()
               + " (" + tr("Road") + ")"));
           break;
       }
       if (si->getShipLoadName()!=(ScheduleItem::NONE)
               && !si->getDestinationTrack()->acceptsLoad(si->getShipLoadName(), si->getTypeName())) {
           status = (tr("Not Valid <%1>").arg(si
               ->getDestinationTrack()->toString()
               + " (" + tr("Load") + ")"));
           break;
       }
   }
  }
  return status;
 }

 /**
  * Checks to see if car can be placed on this spur using this schedule.
  * Returns OKAY if the schedule can service the car->
  *
  * @param car
  * @return Track::OKAY track.CUSTOM track.SCHEDULE
  */
 /*public*/ QString Track::checkSchedule(Car* car) {
     // does car already have this destination?
     if (car->getDestinationTrack() == this) {
         return OKAY;
     }
     // only spurs can have a schedule
     if (getTrackType()!=(SPUR)) {
         return OKAY;
     }
     if (getScheduleId()==(NONE)) {
         // does car have a scheduled load?
         if (car->getLoadName()==(CarLoads::instance()->getDefaultEmptyName())
                 || car->getLoadName()==(CarLoads::instance()->getDefaultLoadName())) {
             return OKAY; // no
         }
         return tr("carHasA").arg(CUSTOM, LOAD).arg(car->getLoadName());
     }
     log->debug(tr("Track (%1) has schedule (%2) mode %3 (%4)").arg(getName()).arg(getScheduleName()).arg(getScheduleMode()).arg(
             getScheduleMode() == SEQUENTIAL ? "Sequential" : "Match")); // NOI18N

     ScheduleItem* si = getCurrentScheduleItem();
     if (si == NULL) {
         log->error(tr("Could not find schedule item id: (%1) for schedule (%2)").arg(getScheduleItemId()).arg(getScheduleName())); // NOI18N
         return SCHEDULE + " ERROR"; // NOI18N
     }
     if (getScheduleMode() == SEQUENTIAL) {
         return checkScheduleItem(si, car);
     }
     // schedule in is match mode search entire schedule for a match
     return searchSchedule(car);
 }


 /*private*/ QString Track::searchSchedule(Car* car) {
     if (debugFlag) {
         log->debug(tr("Search match for car (%1) type (%2) load (%3)").arg(car->toString()).arg(car->getTypeName()).arg(car
                 ->getLoadName()));
     }
     if (car->getScheduleItemId()!=(NONE)) {
         ScheduleItem* si = getSchedule()->getItemById(car->getScheduleItemId());
         if (si != NULL && checkScheduleItem(si, car)==(OKAY)) {
             return OKAY;
         }
     }
     for (int i = 0; i < getSchedule()->getSize(); i++) {
         ScheduleItem* si = getNextScheduleItem();
         if (debugFlag) {
             log->debug(tr("Item id: (%1) requesting type (%2) load (%3) /*final*/ dest (%4, %5)").arg(si->getId()).arg(si
                     ->getTypeName()).arg(si->getReceiveLoadName()).arg(si->getDestinationName()).arg(si->getDestinationTrackName())); // NOI18N
         }
         QString status = checkScheduleItem(si, car);
         if (status==(OKAY)) {
             log->debug(tr("Found item match (%1) car (%2) load (%3) ship (%4) destination (%5, %6)").arg(si->getId()).arg(car
                     ->toString()).arg(si->getReceiveLoadName()).arg(si->getShipLoadName()).arg(si->getDestinationName()).arg(si
                     ->getDestinationTrackName())); // NOI18N
             car->setScheduleItemId(si->getId()); // remember which item was a match
             return OKAY;
         } else {
             if (debugFlag) {
                 log->debug(tr("Item id: (%1) status (%2)").arg(si->getId()).arg(status));
             }
         }
     }
     if (debugFlag) {
         log->debug("No Match");
     }
     car->setScheduleItemId(Car::NONE); // clear the car's schedule id
     return SCHEDULE + " " + tr("noMatch");
 }

 /*private*/ QString Track::checkScheduleItem(ScheduleItem* si, Car* car) {
     if (si->getSetoutTrainScheduleId()!=(ScheduleItem::NONE)
             && TrainManager::instance()->getTrainScheduleActiveId()!=(si->getSetoutTrainScheduleId())) {
         TrainSchedule* sch = ((TrainScheduleManager*)InstanceManager::getDefault("TrainScheduleManager"))->getScheduleById(si->getSetoutTrainScheduleId());
         if (sch != NULL) {
             return SCHEDULE + " (" + getScheduleName() + ") " + tr("requestCarOnly") + " ("
                     + sch->getName() + ")";
         }
     }
     // Check for correct car type, road, load
     if (car->getTypeName()!=(si->getTypeName())) {
         return SCHEDULE + " (" + getScheduleName() + ") " + tr("requestCar") + " " + TYPE + " ("
                 + si->getTypeName() + ")";
     }
     if (si->getRoadName()!=(ScheduleItem::NONE) && car->getRoadName()!=(si->getRoadName())) {
         return SCHEDULE + " (" + getScheduleName() + ") " + tr("requestCar") + " " + TYPE + " ("
                 + si->getTypeName() + ") " + ROAD + " (" + si->getRoadName() + ")";
     }
     if (si->getReceiveLoadName()!=(ScheduleItem::NONE) && car->getLoadName()!=(si->getReceiveLoadName())) {
         return SCHEDULE + " (" + getScheduleName() + ") " + tr("requestCar") + " " + TYPE + " ("
                 + si->getTypeName() + ") " + LOAD + " (" + si->getReceiveLoadName() + ")";
     }
     if (car->getScheduleItemId()==(Car::NONE) && si->getRandom()!=(ScheduleItem::NONE)) {
         //try {
      bool ok;
             int value = si->getRandom().toInt(&ok);
             double random = 100 * qrand();
             log->debug(tr("Selected random %1, created random %2").arg(si->getRandom()).arg(random));
             if (random > value) {
                 return (tr("%1 (%2) item (%3) random value %4 is less than generated %5").arg(SCHEDULE,
                     getScheduleName()).arg(si->getId()).arg(value).arg(random));
             }
         if(!ok) {
             log->error(tr("Random value %1 isn't a number").arg(si->getRandom()));
         }
     }
     return OKAY;
 }

 /**
  * Check to see if track has schedule and if it does will schedule the next
  * item in the list. Load the car with the next schedule load if one exists,
  * and set the car's final destination if there's one in the schedule.
  *
  * @param car
  * @return Track::OKAY or Track::SCHEDULE
  */
 /*public*/ QString Track::scheduleNext(Car* car)
 {
  // clean up the car's /*final*/ destination if sent to that destination and there isn't a schedule
  if (getScheduleId()==(NONE)
          && car->getDestination() != NULL
          && car->getDestination()==(car->getFinalDestination())
          && car->getDestinationTrack() != NULL
          && (car->getDestinationTrack()==(car->getFinalDestinationTrack()) || car->getFinalDestinationTrack() == NULL)) {
      car->setFinalDestination(NULL);
      car->setFinalDestinationTrack(NULL);
  }
  // check for schedule, only spurs can have a schedule
  if (getScheduleId()==(NONE) || getSchedule() == NULL)
  {
   return OKAY;
  }
  // is car part of a kernel?
  if (car->getKernel() != NULL && !car->getKernel()->isLead(car))
  {
   log->debug(tr("Car (%1) is part of kernel (%2) not lead").arg(car->toString()).arg(car->getKernelName()));
   return OKAY;
  }
  if (car->getScheduleItemId()!=(Car::NONE))
  {
   QString id = car->getScheduleItemId();
   log->debug(tr("Car (%1) has schedule item id (%2)").arg(car->toString()).arg(car->getScheduleItemId()));
   Schedule* sch = getSchedule();
   if (sch != NULL)
   {
    ScheduleItem* si = sch->getItemById(id);
    car->setScheduleItemId(Car::NONE);
    if (si != NULL) {
        loadNext(si, car);
        return OKAY;
    }
    log->debug(tr("Schedule id (%1) not valid for track (%1").arg(id).arg(getName()));
    // user could have deleted the schedule item after build train, so not really an error
    // return SCHEDULE + " ERROR id " + id + " not valid for track ("+ getName() + ")"; // NOI18N
   }
  }
  if (getScheduleMode() == MATCH && searchSchedule(car)!=(OKAY))
  {
   return SCHEDULE
           + (tr("%1) in match mode, no match").arg(getScheduleName()));
  }
  ScheduleItem* currentSi = getCurrentScheduleItem();
  log->debug(tr("Destination track (%1) has schedule (%2) item id (%3) mode: %4 (%5)").arg(getName()).arg(getScheduleName()).arg(
          getScheduleItemId()).arg(getScheduleMode()).arg(getScheduleMode() == SEQUENTIAL ? "Sequential" : "Match")); // NOI18N
  if (currentSi != NULL
          && (currentSi->getSetoutTrainScheduleId()==(ScheduleItem::NONE) || TrainManager::instance()
          ->getTrainScheduleActiveId()==(currentSi->getSetoutTrainScheduleId()))
          && car->getTypeName()==(currentSi->getTypeName())
          && (currentSi->getRoadName()==(ScheduleItem::NONE) || car->getRoadName()==(
                  currentSi->getRoadName()))
          && (currentSi->getReceiveLoadName()==(ScheduleItem::NONE) || car->getLoadName()==(
                  currentSi->getReceiveLoadName()))) {
      loadNext(currentSi, car);
      car->setScheduleItemId(Car::NONE);
      // bump schedule
      bumpSchedule();
  } else if (currentSi != NULL) {
      // log->debug("Car (" + toString() + ") type (" + getType() + ") road (" + getRoad() + ") load ("
      // + getLoad() + ") arrived out of sequence, needed type (" + currentSi->getType() // NOI18N
      // + ") road (" + currentSi->getRoad() + ") load (" + currentSi.getLoad() + ")"); // NOI18N
      // build return message
      QString timetableName = "";
      QString currentTimetableName = "";
      TrainSchedule* sch = ((TrainScheduleManager*)InstanceManager::getDefault("TrainScheduleManager"))->getScheduleById(
              TrainManager::instance()->getTrainScheduleActiveId());
      if (sch != NULL) {
          timetableName = sch->getName();
      }
      sch = ((TrainScheduleManager*)InstanceManager::getDefault("TrainScheduleManager"))->getScheduleById(currentSi->getSetoutTrainScheduleId());
      if (sch != NULL) {
          currentTimetableName = sch->getName();
      }
      QString mode = tr("sequential");
      if (getScheduleMode() == 1) {
          mode = tr("match");
      }
      return SCHEDULE
              + tr("({0}) in {1} mode, car ({2}) type({3}) timetable({4}) road({5}) load({6}) does not match: type({7}) timetable({8}) road({9}) receive({10})").arg(getScheduleName()).arg(
                  mode).arg(car->toString()).arg(car->getTypeName()).arg(timetableName, car->getRoadName()).arg(
                  car->getLoadName()).arg(currentSi->getTypeName()).arg(currentTimetableName).arg(currentSi->getRoadName()).arg(
                  currentSi->getReceiveLoadName());
  } else {
      log->error("ERROR Track " + getName() + " current schedule item is NULL!");
      return SCHEDULE + " ERROR Track " + getName() + " current schedule item is NULL!"; // NOI18N
  }
  return OKAY;
 }

 /**
  * Loads the car's with a final destination which is the ship address for
  * the schedule item. Also sets the next load and wait count that will kick
  * in when the car arrives at the spur with this schedule.
  *
  * @param scheduleItem
  * @param car
  */
 /*private*/ void Track::loadNext(ScheduleItem* scheduleItem, Car* car) {
     if (scheduleItem == NULL) {
         log->debug(tr("schedule item is NULL!, id: %1").arg(getScheduleId()));
         return;
     }
     // set the car's next load
     car->setNextLoadName(scheduleItem->getShipLoadName());
     // set the car's /*final*/ destination and track
     car->setFinalDestination(scheduleItem->getDestination());
     car->setFinalDestinationTrack(scheduleItem->getDestinationTrack());
     // set the car's pickup day
     car->setNextPickupScheduleId(scheduleItem->getPickupTrainScheduleId());
     // set the wait count
     car->setNextWait(scheduleItem->getWait());
     // bump hit count for this schedule item
     scheduleItem->setHits(scheduleItem->getHits() + 1);

     log->debug(tr("Car (%1) type (%2) next load (%3) final destination (%4, %5) next wait: %6").arg(car->toString()).arg(car
             ->getTypeName()).arg(car->getNextLoadName()).arg(car->getFinalDestinationName()).arg(car
             ->getFinalDestinationTrackName()).arg(car->getNextWait())); // NOI18N
     // set all cars in kernel to the next load
     car->updateKernel();
 }

 /**
  * Enable changing the car generic load state when car arrives at this
  * track.
  *
  * @param enable when true, swap generic car load state
  */
 /*public*/ void Track::setLoadSwapEnabled(bool enable) {
     if (enable) {
         _loadOptions = _loadOptions | SWAP_GENERIC_LOADS;
     } else {
         _loadOptions = _loadOptions & 0xFFFF - SWAP_GENERIC_LOADS;
     }
 }

 /*public*/ bool Track::isLoadSwapEnabled() {
     return (0 < (_loadOptions & SWAP_GENERIC_LOADS));
 }

 /**
  * Enable setting the car generic load state to empty when car arrives at
  * this track.
  *
  * @param enable when true, set generic car load to empty
  */
 /*public*/ void Track::setLoadEmptyEnabled(bool enable) {
     if (enable) {
         _loadOptions = _loadOptions | EMPTY_GENERIC_LOADS;
     } else {
         _loadOptions = _loadOptions & 0xFFFF - EMPTY_GENERIC_LOADS;
     }
 }

 /*public*/ bool Track::isLoadEmptyEnabled() {
     return (0 < (_loadOptions & EMPTY_GENERIC_LOADS));
 }

 /**
  * When enabled, remove Scheduled car loads.
  *
  * @param enable when true, remove Scheduled loads from cars
  */
 /*public*/ void Track::setRemoveCustomLoadsEnabled(bool enable)
 {
  if (enable) {
      _loadOptions = _loadOptions | EMPTY_CUSTOM_LOADS;
  } else {
      _loadOptions = _loadOptions & 0xFFFF - EMPTY_CUSTOM_LOADS;
  }
 }

 /*public*/ bool Track::isRemoveCustomLoadsEnabled() {
     return (0 < (_loadOptions & EMPTY_CUSTOM_LOADS));
 }

 /**
  * When enabled, add custom car loads if there's a demand.
  *
  * @param enable when true, add custom loads to cars
  */
 /*public*/ void Track::setAddCustomLoadsEnabled(bool enable) {
     bool old = isAddCustomLoadsEnabled();
     if (enable) {
         _loadOptions = _loadOptions | GENERATE_CUSTOM_LOADS;
     } else {
         _loadOptions = _loadOptions & 0xFFFF - GENERATE_CUSTOM_LOADS;
     }
     setDirtyAndFirePropertyChange(LOAD_OPTIONS_CHANGED_PROPERTY, old, enable);
 }

 /*public*/ bool Track::isAddCustomLoadsEnabled() {
     return (0 < (_loadOptions & GENERATE_CUSTOM_LOADS));
 }

 /**
  * When enabled, add custom car loads if there's a demand by any
  * spur/industry.
  *
  * @param enable when true, add custom loads to cars
  */
 /*public*/ void Track::setAddCustomLoadsAnySpurEnabled(bool enable) {
     bool old = isAddCustomLoadsAnySpurEnabled();
     if (enable) {
         _loadOptions = _loadOptions | GENERATE_CUSTOM_LOADS_ANY_SPUR;
     } else {
         _loadOptions = _loadOptions & 0xFFFF - GENERATE_CUSTOM_LOADS_ANY_SPUR;
     }
     setDirtyAndFirePropertyChange(LOAD_OPTIONS_CHANGED_PROPERTY, old, enable);
 }

 /*public*/ bool Track::isAddCustomLoadsAnySpurEnabled() {
     return (0 < (_loadOptions & GENERATE_CUSTOM_LOADS_ANY_SPUR));
 }

 /**
  * When enabled, add custom car loads to cars in staging for new
  * destinations that are staging.
  *
  * @param enable when true, add custom load to car
  */
 /*public*/ void Track::setAddCustomLoadsAnyStagingTrackEnabled(bool enable) {
     bool old = isAddCustomLoadsAnyStagingTrackEnabled();
     if (enable) {
         _loadOptions = _loadOptions | GENERATE_CUSTOM_LOADS_ANY_STAGING_TRACK;
     } else {
         _loadOptions = _loadOptions & 0xFFFF - GENERATE_CUSTOM_LOADS_ANY_STAGING_TRACK;
     }
     setDirtyAndFirePropertyChange(LOAD_OPTIONS_CHANGED_PROPERTY, old, enable);
 }

 /*public*/ bool Track::isAddCustomLoadsAnyStagingTrackEnabled() {
     return (0 < (_loadOptions & GENERATE_CUSTOM_LOADS_ANY_STAGING_TRACK));
 }

 /*public*/ void Track::setBlockCarsEnabled(bool enable) {
     if (enable) {
         _blockOptions = _blockOptions | BLOCK_CARS;
     } else {
         _blockOptions = _blockOptions & 0xFFFF - BLOCK_CARS;
     }
 }

 /**
  * When enabled block cars from staging.
  *
  * @return true if blocking is enabled.
  */
 /*public*/ bool Track::isBlockCarsEnabled() {
     return (0 < (_blockOptions & BLOCK_CARS));
 }

 /*public*/ void Track::setPool(Pool* pool) {
     Pool* old = _pool;
     _pool = pool;
     if (old != pool) {
         if (old != NULL) {
             old->remove(this);
         }
         if (_pool != NULL) {
             _pool->add(this);
         }
         setDirtyAndFirePropertyChange(POOL_CHANGED_PROPERTY, VPtr<Pool>::asQVariant(old), VPtr<Pool>::asQVariant(pool));
     }
 }

 /*public*/ Pool* Track::getPool() {
     return _pool;
 }

 /*public*/ QString Track::getPoolName() {
     if (getPool() != NULL) {
         return getPool()->getName();
     }
     return NONE;
 }


 /*public*/ int Track::getDestinationListSize() {
     return _destinationIdList.size();
 }

 /*public*/ bool Track::addDestination(Location* destination) {
     if (_destinationIdList.contains(destination->getId())) {
         return false;
     }
     _destinationIdList.append(destination->getId());
     setDirtyAndFirePropertyChange(DESTINATIONS_CHANGED_PROPERTY, QVariant(), destination->getName()); // NOI18N
     return true;
 }

 /*public*/ void Track::deleteDestination(Location* destination) {
     if (!_destinationIdList.contains(destination->getId())) {
         return;
     }
     _destinationIdList.removeOne(destination->getId());
     setDirtyAndFirePropertyChange(DESTINATIONS_CHANGED_PROPERTY, destination->getName(), QVariant()); // NOI18N
     return;
 }

 /**
  * Returns true if destination is valid from this track.
  *
  * @param destination
  * @return true if track services the destination
  */
 /*public*/ bool Track::acceptsDestination(Location* destination) {
     if (getDestinationOption()==(ALL_DESTINATIONS) || destination == NULL) {
         return true;
     }
     return _destinationIdList.contains(destination->getId());
 }
#
 /*public*/ void Track::setDestinationIds(QStringList ids) {
     foreach (QString id, ids) {
         _destinationIdList.append(id);
     }
 }

 /*public*/ QStringList Track::getDestinationIds() {
//        QStringList ids = _destinationIdList.toArray(new String[0]);
//        return ids;
  return _destinationIdList;
 }

 /**
  * Sets the destination option for this track. The three options are:
  * <P>
  * ALL_DESTINATIONS which means this track services all destinations, the
  * default.
  * <P>
  * INCLUDE_DESTINATIONS which means this track services only certain
  * destinations.
  * <P>
  * EXCLUDE_DESTINATIONS which means this track does not service certain
  * destinations.
  *
  * @param option Track::ALL_DESTINATIONS, Track::INCLUDE_DESTINATIONS, or
  *               Track::EXCLUDE_DESTINATIONS
  */
 /*public*/ void Track::setDestinationOption(QString option) {
     QString old = _destinationOption;
     _destinationOption = option;
     if (option!=(old)) {
         setDirtyAndFirePropertyChange(DESTINATION_OPTIONS_CHANGED_PROPERTY, old, option); // NOI18N
     }
 }

 /*public*/ QString Track::getDestinationOption() {
     if (getTrackType()==(INTERCHANGE) || getTrackType()==(STAGING)) {
         return _destinationOption;
     }
     return ALL_DESTINATIONS;
 }

 /**
  * Used to determine if track has been assigned as an alternate
  *
  * @return true if track is an alternate
  */
 /*public*/ bool Track::isAlternate() {
     foreach (Track* track, getLocation()->getTrackList()) {
         if (track->getAlternateTrack() == this) {
             return true;
         }
     }
     return false;
 }

 /*public*/ void Track::dispose() {
     // change the name in case object is still in use, for example ScheduleItem.java
     setName(tr("Not Valid <%1>").arg(getName() ));
     setDirtyAndFirePropertyChange(DISPOSE_CHANGED_PROPERTY, QVariant(), DISPOSE_CHANGED_PROPERTY);
 }

 /**
  * Construct this Entry from XML. This member has to remain synchronized
  * with the detailed DTD in operations-config.xml
  *
  * @param e Consist XML element
  */
 /*public*/ Track::Track(QDomElement e, Location* location)
 {
  common();
     _location = location;
     QString a;
     if ((a = e.attribute (Xml::ID)) != "") {
         _id = a;
     } else {
         log->warn("no id attribute in track element when reading operations " + e.tagName() + " location= " + location->toString());
     }
     if ((a = e.attribute (Xml::NAME)) != "") {
         _name = a;
     }
     if ((a = e.attribute (Xml::LOC_TYPE)) != "") {
         _trackType = a;
     }
     if ((a = e.attribute (Xml::LENGTH)) != "") {
         //try {
      bool ok;
             _length = a.toInt(&ok);
         if(!ok) {
             log->error(tr("Track length isn't a valid number for track %1").arg(getName()));
         }
     }
     if ((a = e.attribute (Xml::MOVES)) != "") {
         //try {
      bool ok;
             _moves = a.toInt(&ok);
         if(!ok) {
             log->error(tr("Track moves isn't a valid number for track %1").arg(getName()));
         }

     }
     if ((a = e.attribute (Xml::BLOCKING_ORDER)) != NULL) {
         //try {
      bool ok;
             _blockingOrder = a.toInt(&ok);
        if(!ok) {
             log->error(tr("Track blocking order isn't a valid number for track %1").arg(getName()));
         }
     }
     if ((a = e.attribute (Xml::DIR)) != NULL) {
         //try {
      bool ok;
             _trainDir = a.toInt(&ok);
         if(!ok) {
             log->error(tr("Track service direction isn't a valid number for track %1").arg(getName()));
         }
     }
     // old way of reading track comment, see comments below for new format
     if ((a = e.attribute (Xml::COMMENT)) != NULL) {
         //_comment = OperationsXml::convertFromXmlComment(a);
      _comment = a;
     }

     // new way of reading car types using elements added in 3.3.1
     if (e.firstChildElement(Xml::TYPES) != QDomElement()) {
         //@SuppressWarnings("unchecked")
         QDomNodeList carTypes = e.firstChildElement(Xml::TYPES).elementsByTagName(Xml::CAR_TYPE);
         QVector<QString> types = QVector<QString>(carTypes.size());
         for (int i = 0; i < carTypes.size(); i++) {
             QDomElement type = carTypes.at(i).toElement();
             if ((a = type.attribute (Xml::NAME)) != NULL) {
                 types.replace(i, a);
             }
         }
         setTypeNames(types.toList());
         //@SuppressWarnings("unchecked")
         QDomNodeList locoTypes = e.firstChildElement( Xml::TYPES).elementsByTagName(Xml::LOCO_TYPE);
         types =  QVector<QString>(locoTypes.size());
         for (int i = 0; i < locoTypes.size(); i++) {
             QDomElement type = locoTypes.at(i).toElement();
             if ((a = type.attribute (Xml::NAME)) != NULL) {
              types.replace(i, a);
             }
         }
         setTypeNames(types.toList());
     } // old way of reading car types up to version 3.2
     else if ((a = e.attribute (Xml::CAR_TYPES)) != NULL) {
         QString names = a;
         QStringList types = names.split("%%"); // NOI18N
         if (debugFlag) {
             log->debug(tr("track (%1) accepts car types: %2").arg(getName()).arg(names));
         }
         setTypeNames(types);
     }

     if ((a = e.attribute (Xml::CAR_LOAD_OPTION)) != NULL) {
         _loadOption = a;
     }
     // new way of reading car loads using elements
     if (e.firstChildElement(Xml::CAR_LOADS) != QDomElement()) {
         //@SuppressWarnings("unchecked")
         QDomNodeList carLoads = e.firstChildElement(Xml::CAR_LOADS).elementsByTagName(Xml::CAR_LOAD);
         QVector<QString> loads = QVector<QString>(carLoads.size());
         for (int i = 0; i < carLoads.size(); i++) {
             QDomElement load = carLoads.at(i).toElement();
             if ((a = load.attribute (Xml::NAME)) != NULL) {
                 loads.replace(i, a);
             }
         }
         setLoadNames(loads.toList());
     } // old way of reading car loads up to version 3.2
     else if ((a = e.attribute (Xml::CAR_LOADS)) != NULL) {
         QString names = a;
         QStringList loads = names.split("%%"); // NOI18N
         if (log->isDebugEnabled()) {
             log->debug(tr("Track (%1) %2 car loads: %3").arg(getName()).arg(getLoadOption()).arg(names));
         }
         setLoadNames(loads);
     }
     if ((a = e.attribute (Xml::CAR_SHIP_LOAD_OPTION)) != NULL) {
         _shipLoadOption = a;
     }
     // new way of reading car loads using elements
     if (e.firstChildElement(Xml::CAR_SHIP_LOADS) != QDomElement()) {
         //@SuppressWarnings("unchecked")
         QDomNodeList carLoads = e.firstChildElement(Xml::CAR_SHIP_LOADS).elementsByTagName(Xml::CAR_LOAD);
         QVector<QString> loads = QVector<QString>(carLoads.size());
         for (int i = 0; i < carLoads.size(); i++) {
             QDomElement load = carLoads.at(i).toElement();
             if ((a = load.attribute (Xml::NAME)) != NULL) {
                 loads.replace(i, a);
             }
         }
         setShipLoadNames(loads.toList());
     }
     // new way of reading drop ids using elements
     if (e.firstChildElement(Xml::DROP_IDS) != QDomElement()) {
        // @SuppressWarnings("unchecked")
         QDomNodeList dropIds = e.firstChildElement(Xml::DROP_IDS).elementsByTagName(Xml::DROP_ID);
         QVector<QString> ids = QVector<QString>(dropIds.size());
         for (int i = 0; i < dropIds.size(); i++) {
             QDomElement dropId = dropIds.at(i).toElement();
             if ((a = dropId.attribute (Xml::ID)) != NULL) {
                 ids.replace(i, a);
             }
         }
         setDropIds(ids.toList());
     } // old way of reading drop ids up to version 3.2
     else if ((a = e.attribute (Xml::DROP_IDS)) != NULL) {
         QString names = a;
         QStringList ids = names.split("%%"); // NOI18N
         if (debugFlag) {
             log->debug(tr("track (%1) has drop ids: %2").arg(getName()).arg(names));
         }
         setDropIds(ids);
     }
     if ((a = e.attribute (Xml::DROP_OPTION)) != NULL) {
         _dropOption = a;
     }

     // new way of reading pick up ids using elements
     if (e.firstChildElement(Xml::PICKUP_IDS) != QDomElement()) {
         //@SuppressWarnings("unchecked")
         QDomNodeList pickupIds = e.firstChildElement(Xml::PICKUP_IDS).elementsByTagName(Xml::PICKUP_ID);
         QVector<QString> ids = QVector<QString>(pickupIds.size());
         for (int i = 0; i < pickupIds.size(); i++) {
             QDomElement pickupId = pickupIds.at(i).toElement();
             if ((a = pickupId.attribute (Xml::ID)) != NULL) {
                 ids.replace(i, a);
             }
         }
         setPickupIds(ids.toList());
     } // old way of reading pick up ids up to version 3.2
     else if ((a = e.attribute (Xml::PICKUP_IDS)) != NULL) {
         QString names = a;
         QStringList ids = names.split("%%"); // NOI18N
         if (debugFlag) {
             log->debug(tr("track (%1) has pickup ids: %2").arg(getName()).arg(names));
         }
         setPickupIds(ids);
     }
     if ((a = e.attribute (Xml::PICKUP_OPTION)) != NULL) {
         _pickupOption = a;
     }

     // new way of reading car roads using elements
     if (e.firstChildElement(Xml::CAR_ROADS) != QDomElement()) {
        // @SuppressWarnings("unchecked")
         QDomNodeList carRoads = e.firstChildElement(Xml::CAR_ROADS).elementsByTagName(Xml::CAR_ROAD);
         QVector<QString> roads = QVector<QString>(carRoads.size());
         for (int i = 0; i < carRoads.size(); i++) {
             QDomElement road = carRoads.at(i).toElement();
             if ((a = road.attribute (Xml::NAME)) != NULL) {
                 roads.replace(i, a);
             }
         }
         setRoadNames(roads.toList());
     } // old way of reading car roads up to version 3.2
     else if ((a = e.attribute (Xml::CAR_ROADS)) != NULL) {
         QString names = a;
         QStringList roads = names.split("%%"); // NOI18N
         if (debugFlag) {
             log->debug(tr("track (%1) %2 car roads: %3").arg(getName()).arg(getRoadOption()).arg(names));
         }
         setRoadNames(roads);
     }
     if ((a = e.attribute (Xml::CAR_ROAD_OPTION)) != NULL) {
         _roadOption = a;
     } else if ((a = e.attribute (Xml::CAR_ROAD_OPERATION)) != NULL) {
         _roadOption = a;
     }

     if ((a = e.attribute (Xml::SCHEDULE)) != NULL) {
         _scheduleName = a;
     }
     if ((a = e.attribute (Xml::SCHEDULE_ID)) != NULL) {
         _scheduleId = a;
     }
     if ((a = e.attribute (Xml::ITEM_ID)) != NULL) {
         _scheduleItemId = a;
     }
     if ((a = e.attribute (Xml::ITEM_COUNT)) != NULL) {
         //try {
      bool ok;
             _scheduleCount = a.toInt(&ok);
         if(!ok) {
             log->error(tr("Schedule count isn't a valid number for track %1").arg(getName()));
         }
     }
     if ((a = e.attribute (Xml::FACTOR)) != NULL) {
         //try {
      bool ok;
             _reservationFactor = a.toInt(&ok);
         if(!ok) {
             log->error(tr("Reservation factor isn't a vaild number for track %1").arg(getName()));
         }
     }
     if ((a = e.attribute (Xml::SCHEDULE_MODE)) != NULL) {
         //try {
      bool ok;
             _mode = a.toInt(&ok);
         if(!ok) {
             log->error(tr("Schedule mode isn't a vaild number for track %1").arg(getName()));
         }
     }
     if ((a = e.attribute (Xml::ALTERNATIVE)) != NULL) {
         _alternateTrackId = a;
     }

     if ((a = e.attribute (Xml::LOAD_OPTIONS)) != NULL) {
         //try {
      bool ok;
             _loadOptions = a.toInt(&ok);
         if(!ok) {
             log->error(tr("Load options isn't a valid number for track %1").arg(getName()));
         }
     }
     if ((a = e.attribute (Xml::BLOCK_OPTIONS)) != NULL) {
         //try {
      bool ok;
             _blockOptions = a.toInt(&ok);
         if(!ok) {
             log->error(tr("Block options isn't a valid number for track %1").arg(getName()));
         }
     }
     if ((a = e.attribute (Xml::ORDER)) != NULL) {
         _order = a;
     }
     if ((a = e.attribute (Xml::POOL)) != NULL) {
         setPool(getLocation()->addPool(a));
         if ((a = e.attribute (Xml::MIN_LENGTH)) != NULL) {
             //try {
          bool ok;
                 _minimumLength = a.toInt(&ok);
             if(!ok) {
                 log->error(tr("Minimum pool length isn't a valid number for track %1").arg(getName()));
             }
         }
     }
     if ((a = e.attribute (Xml::IGNORE_USED_PERCENTAGE)) != NULL) {
         //try {
      bool ok;
             _ignoreUsedLengthPercentage = a.toInt(&ok);
         if(!ok) {
             log->error(tr("Ignore used percentage isn't a valid number for track %1").arg(getName()));
         }
     }
     if ((a = e.attribute (Xml::TRACK_DESTINATION_OPTION)) != NULL) {
         _destinationOption = a;
     }
     if (e.firstChildElement(Xml::DESTINATIONS) != QDomElement()) {
         //@SuppressWarnings("unchecked")
         QDomNodeList eDestinations = e.firstChildElement(Xml::DESTINATIONS).elementsByTagName(Xml::DESTINATION);
         //for (QDomElement eDestination : eDestinations) {
         for (int i = 0; i < eDestinations.count(); i++)
         {
          QDomElement eDestination = eDestinations.at(i).toElement();
             if ((a = eDestination.attribute (Xml::ID)) != NULL) {
                 _destinationIdList.append(a);
             }
         }
     }

     if (e.firstChildElement(Xml::COMMENTS) != QDomElement()) {
         if (e.firstChildElement(Xml::COMMENTS).firstChildElement(Xml::TRACK) != QDomElement()
                 && (a = e.firstChildElement(Xml::COMMENTS).firstChildElement(Xml::TRACK).attribute (Xml::COMMENT)) != NULL) {
             _comment = a;
         }
         if (e.firstChildElement(Xml::COMMENTS).firstChildElement(Xml::BOTH) != QDomElement()
                 && (a = e.firstChildElement(Xml::COMMENTS).firstChildElement(Xml::BOTH).attribute (Xml::COMMENT)) != NULL) {
             _commentBoth = a;
         }
         if (e.firstChildElement(Xml::COMMENTS).firstChildElement(Xml::PICKUP) != QDomElement()
                 && (a = e.firstChildElement(Xml::COMMENTS).firstChildElement(Xml::PICKUP).attribute (Xml::COMMENT)) != NULL) {
             _commentPickup = a;
         }
         if (e.firstChildElement(Xml::COMMENTS).firstChildElement(Xml::SETOUT) != QDomElement()
                 && (a = e.firstChildElement(Xml::COMMENTS).firstChildElement(Xml::SETOUT).attribute (Xml::COMMENT)) != NULL) {
             _commentSetout = a;
         }
     }

 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-location.dtd.
  *
  * @return Contents in a JDOM Element
  */
 /*public*/ QDomElement Track::store(QDomDocument doc) {
     QDomElement e = doc.createElement(Xml::TRACK);
     e.setAttribute(Xml::ID, getId());
     e.setAttribute(Xml::NAME, getName());
     e.setAttribute(Xml::LOC_TYPE, getTrackType());
     e.setAttribute(Xml::DIR, getTrainDirections());
     e.setAttribute(Xml::LENGTH, getLength());
     e.setAttribute(Xml::MOVES, getMoves() - getDropRS());
     e.setAttribute(Xml::BLOCKING_ORDER, getBlockingOrder());
     // build list of car types for this track
     QStringList types = getTypeNames();
     // Old way of saving car types
     if (Control::backwardCompatible) {
         QString buf;// = new StringBuffer();
         foreach (QString type, types) {
             // remove types that have been deleted by user
             if (CarTypes::instance()->containsName(type) || EngineTypes::instance()->containsName(type)) {
                 buf.append(type + "%%"); // NOI18N
             }
         }
         e.setAttribute(Xml::CAR_TYPES, buf);
     }
     // new way of saving car types using elements
     QDomElement eTypes = doc.createElement(Xml::TYPES);
     foreach (QString type, types) {
         // don't save types that have been deleted by user
         if (EngineTypes::instance()->containsName(type)) {
             QDomElement eType = QDomElement();
             eType.setTagName(Xml::LOCO_TYPE);
             eType.setAttribute(Xml::NAME, type);
             eTypes.appendChild(eType);
         } else if (CarTypes::instance()->containsName(type)) {
             QDomElement eType =QDomElement();
             eType.setTagName(Xml::CAR_TYPE);
             eType.setAttribute(Xml::NAME, type);
             eTypes.appendChild(eType);
         }
     }
     e.appendChild(eTypes);

     if (Control::backwardCompatible) {
         e.setAttribute(Xml::CAR_ROAD_OPERATION, getRoadOption()); // early versions had a misspelling
     }
     // build list of car roads for this track
     if (getRoadOption()!=(ALL_ROADS)) {
         e.setAttribute(Xml::CAR_ROAD_OPTION, getRoadOption());
         QStringList roads = getRoadNames();
         if (Control::backwardCompatible) {
             QString buf;// = new StringBuffer();
             foreach (QString road, roads) {
                 buf.append(road + "%%"); // NOI18N
             }
             e.setAttribute(Xml::CAR_ROADS, buf);
         }
         // new way of saving road names
         QDomElement eRoads = doc.createElement(Xml::CAR_ROADS);
         foreach (QString road, roads) {
             QDomElement eRoad = doc.createElement(Xml::CAR_ROAD);
             eRoad.setAttribute(Xml::NAME, road);
             eRoads.appendChild(eRoad);
         }
         e.appendChild(eRoads);
     }

     // save list of car loads for this track
     if (getLoadOption()!=(ALL_LOADS)) {
         e.setAttribute(Xml::CAR_LOAD_OPTION, getLoadOption());
         QStringList loads = getLoadNames();
         if (Control::backwardCompatible) {
             QString buf;// = new StringBuffer();
             foreach (QString load, loads) {
                 buf.append(load + "%%"); // NOI18N
             }
             e.setAttribute(Xml::CAR_LOADS, buf);
         }
         // new way of saving car loads using elements
         QDomElement eLoads = doc.createElement(Xml::CAR_LOADS);
         foreach (QString load, loads) {
             QDomElement eLoad = QDomElement();
             eLoad.setTagName(Xml::CAR_LOAD);
             eLoad.setAttribute(Xml::NAME, load);
             eLoads.appendChild(eLoad);
         }
         e.appendChild(eLoads);
     }

     // save list of car loads for this track
     if (getShipLoadOption()!=(ALL_LOADS)) {
         e.setAttribute(Xml::CAR_SHIP_LOAD_OPTION, getShipLoadOption());
         QStringList loads = getShipLoadNames();
         // new way of saving car loads using elements
         QDomElement eLoads = doc.createElement(Xml::CAR_SHIP_LOADS);
         foreach (QString load, loads) {
             QDomElement eLoad = doc.createElement(Xml::CAR_LOAD);
             eLoad.setAttribute(Xml::NAME, load);
             eLoads.appendChild(eLoad);
         }
         e.appendChild(eLoads);
     }

     if (getDropOption()!=(ANY)) {
         e.setAttribute(Xml::DROP_OPTION, getDropOption());
         // build list of drop ids for this track
         QStringList dropIds = getDropIds();
         if (Control::backwardCompatible) {
             QString buf = "";
             foreach (QString id, dropIds) {
                 buf.append(id + "%%"); // NOI18N
             }
             e.setAttribute(Xml::DROP_IDS, buf/*.toString()*/);
         }
         // new way of saving drop ids using elements
         QDomElement eDropIds = doc.createElement(Xml::DROP_IDS);
         foreach (QString id, dropIds) {
             QDomElement eDropId = doc.createElement(Xml::DROP_ID);
             eDropId.setAttribute(Xml::ID, id);
             eDropIds.appendChild(eDropId);
         }
         e.appendChild(eDropIds);
     }

     if (getPickupOption()!=(ANY)) {
         e.setAttribute(Xml::PICKUP_OPTION, getPickupOption());
         // build list of pickup ids for this track
         QStringList pickupIds = getPickupIds();
         if (Control::backwardCompatible) {
             QString buf = "";
             foreach (QString id, pickupIds) {
                 buf.append(id + "%%"); // NOI18N
             }
             e.setAttribute(Xml::PICKUP_IDS, buf/*.toString()*/);
         }
         // new way of saving pick up ids using elements
         QDomElement ePickupIds = doc.createElement(Xml::PICKUP_IDS);
         foreach (QString id, pickupIds) {
             QDomElement ePickupId = doc.createElement(Xml::PICKUP_ID);
             ePickupId.setAttribute(Xml::ID, id);
             ePickupIds.appendChild(ePickupId);
         }
         e.appendChild(ePickupIds);
     }

     if (getSchedule() != NULL) {
         e.setAttribute(Xml::SCHEDULE, getScheduleName());
         e.setAttribute(Xml::SCHEDULE_ID, getScheduleId());
         e.setAttribute(Xml::ITEM_ID, getScheduleItemId());
         e.setAttribute(Xml::ITEM_COUNT, (getScheduleCount()));
         e.setAttribute(Xml::FACTOR, (getReservationFactor()));
         e.setAttribute(Xml::SCHEDULE_MODE, (getScheduleMode()));
     }

     if (getAlternateTrack() != NULL) {
         e.setAttribute(Xml::ALTERNATIVE, getAlternateTrack()->getId());
     }
     if (_loadOptions != 0) {
         e.setAttribute(Xml::LOAD_OPTIONS,(_loadOptions));
     }
     if (_blockOptions != 0) {
         e.setAttribute(Xml::BLOCK_OPTIONS, (_blockOptions));
     }
     if (getServiceOrder()!=(NORMAL)) {
         e.setAttribute(Xml::ORDER, getServiceOrder());
     }
     if (getPool() != NULL) {
         e.setAttribute(Xml::POOL, getPool()->getName());
         e.setAttribute(Xml::MIN_LENGTH, (getMinimumLength()));
     }
     if (getIgnoreUsedLengthPercentage() > 0) {
         e.setAttribute(Xml::IGNORE_USED_PERCENTAGE, getIgnoreUsedLengthPercentage());
     }

     if (getDestinationOption()!=(ALL_DESTINATIONS))
     {
         e.setAttribute(Xml::TRACK_DESTINATION_OPTION, getDestinationOption());
         // save destinations if they exist
         QStringList destIds = getDestinationIds();
         if (destIds.length() > 0) {
             QDomElement destinations = QDomElement();
             destinations.setTagName(Xml::DESTINATIONS);
             foreach (QString id, destIds) {
                 Location* loc = LocationManager::instance()->getLocationById(id);
                 if (loc != NULL) {
                     QDomElement destination = QDomElement();
                     destination.setTagName(Xml::DESTINATION);
                     destination.setAttribute(Xml::ID, id);
                     destination.setAttribute(Xml::NAME, loc->getName());
                     destinations.appendChild(destination);
                 }
             }
             e.appendChild(destinations);
         }
     }
     if (Control::backwardCompatible) {
         e.setAttribute(Xml::COMMENT, getComment());
     }
     // save manifest track comments if they exist
     if (getComment()!=(NONE) || getCommentBoth()!=(NONE) || getCommentPickup()!=(NONE)
             || getCommentSetout()!=(NONE)) {
         QDomElement comments = doc.createElement(Xml::COMMENTS);
         QDomElement track = QDomElement();
         track.setTagName(Xml::TRACK);
         QDomElement both = doc.createElement(Xml::BOTH);
         QDomElement pickup = doc.createElement(Xml::PICKUP);
         QDomElement setout = doc.createElement(Xml::SETOUT);
         comments.appendChild(track);
         comments.appendChild(both);
         comments.appendChild(pickup);
         comments.appendChild(setout);
         track.setAttribute(Xml::COMMENT, getComment());
         both.setAttribute(Xml::COMMENT, getCommentBoth());
         pickup.setAttribute(Xml::COMMENT, getCommentPickup());
         setout.setAttribute(Xml::COMMENT, getCommentSetout());
         e.appendChild(comments);
     }

     return e;
 }

#if 0
 /*public*/ synchronized void addPropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.addPropertyChangeListener(l);
 }

 /*public*/ synchronized void removePropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.removePropertyChangeListener(l);
 }
#endif
 /*protected*/ void Track::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     LocationManagerXml::instance()->setDirty(true);
     pcs->firePropertyChange(p, old, n);
 }

}
