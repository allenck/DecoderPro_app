#ifndef TRACK_H
#define TRACK_H

#include <QObject>
#include "logger.h"
#include "propertychangesupport.h"
#include "appslib_global.h"

class QDomDocument;
class QDomElement;
namespace Operations
{
 class Train;
 class Route;
 class Schedule;
 class ScheduleItem;
 class Car;
 class RollingStock;
 class Pool;
 class Location;
class APPSLIBSHARED_EXPORT Track : public PropertyChangeSupport
{
 Q_OBJECT
public:
 //explicit Track(QObject *parent = 0);
 /*public*/ Track(QString id, QString name, QString type, Location* location,QObject *parent = 0);
 /*public*/ static /*final*/ QString NONE;// = "";
 /*public*/ static /*final*/ QString ANY; //="Any"; // track accepts any train or route
 /*public*/ static /*final*/ QString TRAINS; //="trains"; // NOI18N track only accepts certain trains
 /*public*/ static /*final*/ QString ROUTES; //="routes"; // NOI18N track only accepts certain routes
 /*public*/ static /*final*/ QString EXCLUDE_TRAINS; //="excludeTrains"; // NOI18N track excludes certain trains
 /*public*/ static /*final*/ QString EXCLUDE_ROUTES; //="excludeRoutes"; // NOI18N track excludes certain routes
 // order cars are serviced
 /*public*/ static /*final*/ QString NORMAL; //=Bundle.getMessage("Normal");
 /*public*/ static /*final*/ QString FIFO; //=Bundle.getMessage("FIFO");
 /*public*/ static /*final*/ QString LIFO; //=Bundle.getMessage("LIFO");

 // the four types of tracks
 /*public*/ static /*final*/ QString STAGING; //="Staging";
 /*public*/ static /*final*/ QString INTERCHANGE; //="Interchange";
 /*public*/ static /*final*/ QString YARD; //="Yard";
 /*public*/ static /*final*/ QString SPUR; //="Siding"; // NOI18N note that early code used Siding as the spur type

 // train directions serviced by this track
 /*public*/ static /*final*/ int EAST; //=1;
 /*public*/ static /*final*/ int WEST; //=2;
 /*public*/ static /*final*/ int NORTH; //=4;
 /*public*/ static /*final*/ int SOUTH; //=8;

 // how roads are serviced by this track
 /*public*/ static /*final*/ QString ALL_ROADS; //=Bundle.getMessage("All"); // track accepts all roads
 /*public*/ static /*final*/ QString INCLUDE_ROADS; //=Bundle.getMessage("Include"); // track accepts only certain roads
 /*public*/ static /*final*/ QString EXCLUDE_ROADS; //=Bundle.getMessage("Exclude"); // track does not accept certain roads
 /*public*/ static /*final*/ QString ALL_LOADS; //=Bundle.getMessage("All"); // track services all loads
 /*public*/ static /*final*/ QString INCLUDE_LOADS; //=Bundle.getMessage("Include");
 /*public*/ static /*final*/ QString EXCLUDE_LOADS; //=Bundle.getMessage("Exclude");

 // destination options
 /*public*/ static /*final*/ QString ALL_DESTINATIONS; //=Bundle.getMessage("All"); // track services all loads
 /*public*/ static /*final*/ QString INCLUDE_DESTINATIONS; //=Bundle.getMessage("Include");
 /*public*/ static /*final*/ QString EXCLUDE_DESTINATIONS; //=Bundle.getMessage("Exclude");

 // schedule modes
 /*public*/ static /*final*/ int SEQUENTIAL; //=0;
 /*public*/ static /*final*/ int MATCH; //=1;

 // schedule status
 /*public*/ static /*final*/ QString SCHEDULE_OKAY; //="";
 // return status when checking rolling stock
 /*public*/ static /*final*/ QString OKAY; //=tr("okay");
 /*public*/ static /*final*/ QString LENGTH; //=tr("rollingStock") + " " + tr("length");
 /*public*/ static /*final*/ QString TYPE; //=tr("type");
 /*public*/ static /*final*/ QString ROAD; //=tr("road");
 /*public*/ static /*final*/ QString LOAD; //=tr("load");
 /*public*/ static /*final*/ QString CAPACITY; //=tr("track") + " " + tr("capacity");
 /*public*/ static /*final*/ QString SCHEDULE; //=tr("schedule");
 /*public*/ static /*final*/ QString CUSTOM; //=tr("custom");
 /*public*/ static /*final*/ QString DESTINATION; //=tr("carDestination");

 // For property change
 /*public*/ static /*final*/ QString TYPES_CHANGED_PROPERTY; //="trackRollingStockTypes"; // NOI18N
 /*public*/ static /*final*/ QString ROADS_CHANGED_PROPERTY; //="trackRoads"; // NOI18N
 /*public*/ static /*final*/ QString NAME_CHANGED_PROPERTY; //="trackName"; // NOI18N
 /*public*/ static /*final*/ QString LENGTH_CHANGED_PROPERTY; //="trackLength"; // NOI18N
 /*public*/ static /*final*/ QString MIN_LENGTH_CHANGED_PROPERTY; //="trackMinLength"; // NOI18N
 /*public*/ static /*final*/ QString SCHEDULE_CHANGED_PROPERTY; //="trackScheduleChange"; // NOI18N
 /*public*/ static /*final*/ QString DISPOSE_CHANGED_PROPERTY; //="trackDispose"; // NOI18N
 /*public*/ static /*final*/ QString TRAINDIRECTION_CHANGED_PROPERTY; //="trackTrainDirection"; // NOI18N
 /*public*/ static /*final*/ QString DROP_CHANGED_PROPERTY; //="trackDrop"; // NOI18N
 /*public*/ static /*final*/ QString PICKUP_CHANGED_PROPERTY; //="trackPickup"; // NOI18N
 /*public*/ static /*final*/ QString TRACK_TYPE_CHANGED_PROPERTY; //="trackType"; // NOI18N
 /*public*/ static /*final*/ QString LOADS_CHANGED_PROPERTY; //="trackLoads"; // NOI18N
 /*public*/ static /*final*/ QString POOL_CHANGED_PROPERTY; //="trackPool"; // NOI18N
 /*public*/ static /*final*/ QString PLANNEDPICKUPS_CHANGED_PROPERTY; //="plannedPickUps"; // NOI18N
 /*public*/ static /*final*/ QString LOAD_OPTIONS_CHANGED_PROPERTY; //="trackLoadOptions"; // NOI18N
 /*public*/ static /*final*/ QString DESTINATIONS_CHANGED_PROPERTY; //="trackDestinations"; // NOI18N
 /*public*/ static /*final*/ QString DESTINATION_OPTIONS_CHANGED_PROPERTY; //="trackDestinationOptions"; // NOI18N
 /*public*/ static /*final*/ QString SCHEDULE_MODE_CHANGED_PROPERTY; //="trackScheduleMode"; // NOI18N
 /*public*/ static /*final*/ QString SCHEDULE_ID_CHANGED_PROPERTY; //="trackScheduleId"; // NOI18N
 /*public*/ static /*final*/ QString SERVICE_ORDER_CHANGED_PROPERTY; //="trackServiceOrder"; // NOI18N
 /*public*/ static /*final*/ QString ALTERNATE_TRACK_CHANGED_PROPERTY; //="trackAlternate"; // NOI18N
 /*public*/ static /*final*/ QString TRACK_BLOCKING_ORDER_CHANGED_PROPERTY; //="trackBlockingOrder"; // NOI18N
 /*public*/ Track* copyTrack(QString newName, Location* newLocation) ;
 /*public*/ QString toString() ;
 /*public*/ QString getId() ;
 /*public*/ Location* getLocation();
 /*public*/ void setName(QString name);
 /*public*/ QString getName() ;
 /*public*/ QString getTrackType() ;
 /*public*/ void setTrackType(QString type);
 /*public*/ QString getTrackTypeName();
 /*public*/ static QString getTrackTypeName(QString trackType);
 /*public*/ void addTypeName(QString type);
 /*public*/ void deleteTypeName(QString type);
 /*public*/ bool acceptsTypeName(QString type);
 /*public*/ int getLength();
 /*public*/ void dispose();
 /*public*/ void setMoves(int moves);
 /*public*/ Track(QDomElement e, Location* location);
 /*public*/ void deleteRS(RollingStock* rs);
 /*public*/ void addPickupRS(RollingStock* rs);
 /*public*/ void deletePickupRS(RollingStock* rs);
 /*public*/ int getPickupRS();
 /*public*/ int getNumberCars();
 /*public*/ int getNumberEngines();
 /*public*/ void setUsedLength(int length);
 /*public*/ int getUsedLength();
 /*public*/ void setReserved(int reserved);
 /*public*/ int getReserved();
 /*public*/ QString accepts(RollingStock* rs);
 /*public*/ bool acceptsRoadName(QString road);
 /*public*/ bool containsRoadName(QString road);
 /*public*/ QDomElement store(QDomDocument doc);
 /*public*/ void setTrainDirections(int direction);
 /*public*/ int getTrainDirections();
 /*public*/ QString getRoadOption();
 /*public*/ void setRoadOption(QString option);
 /*public*/ QStringList getRoadNames();
 /*public*/ int getIgnoreUsedLengthPercentage();
 /*public*/ int getReservedLengthDrops();
 /*public*/ void addRS(RollingStock* rs);
 /*public*/ int getDropRS();
 /*public*/ void addDropRS(RollingStock* rs);
 /*public*/ void deleteDropRS(RollingStock* rs);
 /*public*/ void setComment(QString comment);
 /*public*/ QString getComment();
 /*public*/ int getMoves();
 /*public*/ int getMinimumLength();
 /*public*/ void setLength(int length);
 /*public*/ void setMinimumLength(int length);
 /*public*/ void addReservedInRoute(Car* car) ;
 /*public*/ void deleteReservedInRoute(Car* car);
 /*public*/ void addRoadName(QString road);
 /*public*/ void deleteRoadName(QString road);
 /*public*/ QStringList getTypeNames();
 /*public*/ int getBlockingOrder();
 /*public*/ void setBlockingOrder(int order) ;
 /*public*/ QString getServiceOrder();
 /*public*/ void setServiceOrder(QString order);
 /*public*/ QStringList getLoadNames() ;
 /*public*/ bool addLoadName(QString load);
 /*public*/ QString getLoadOption();
 /*public*/ void setLoadOption(QString option);
 /*public*/ Track* getAlternateTrack();
 /*public*/ Pool* getPool();
 /*public*/ QString getPoolName();
 /*public*/ int getNumberRS();
 /*public*/ QString getDestinationOption();
 /*public*/ QStringList getDestinationIds();
 /*public*/ QString getCommentBoth();
 /*public*/ void setCommentPickup(QString comment) ;
 /*public*/ QString getCommentPickup();
 /*public*/ void setCommentSetout(QString comment) ;
 /*public*/ QString getCommentSetout() ;
 /*public*/ void setCommentBoth(QString comment);
 /*public*/ void setPool(Pool* pool);
 /*public*/ bool deleteLoadName(QString load);
 /*public*/ QStringList getShipLoadNames();
 /*public*/ bool addShipLoadName(QString load);
 /*public*/ bool deleteShipLoadName(QString load);
 /*public*/ bool shipsLoadName(QString load);
 /*public*/ bool shipsLoad(QString load, QString type);
 /*public*/ QString getDropOption();
 /*public*/ QString getShipLoadOption();
 /*public*/ int getDestinationListSize();
 /*public*/ bool isAlternate();
 /*public*/ void setDropOption(QString option);
 /*public*/ QString getPickupOption();
 /*public*/ void setPickupOption(QString option);
 /*public*/ QStringList getDropIds();
 /*public*/ void deleteDropId(QString id);
 /*public*/ QStringList getPickupIds();
 /*public*/ void addPickupId(QString id);
 /*public*/ void deletePickupId(QString id);
 /*public*/ void addDropId(QString id);
 /*public*/ void setLoadSwapEnabled(bool enable);
 /*public*/ bool isLoadSwapEnabled();
 /*public*/ void setLoadEmptyEnabled(bool enable);
 /*public*/ bool isLoadEmptyEnabled() ;
 /*public*/ void setRemoveCustomLoadsEnabled(bool enable);
 /*public*/ bool isRemoveCustomLoadsEnabled();
 /*public*/ void setAddCustomLoadsEnabled(bool enable);
 /*public*/ bool isAddCustomLoadsEnabled() ;
 /*public*/ void setAddCustomLoadsAnySpurEnabled(bool enable);
 /*public*/ bool isAddCustomLoadsAnySpurEnabled();
 /*public*/ void setAddCustomLoadsAnyStagingTrackEnabled(bool enable);
 /*public*/ bool isAddCustomLoadsAnyStagingTrackEnabled();
 /*public*/ void setBlockCarsEnabled(bool enable);
 /*public*/ bool isBlockCarsEnabled();
 /*public*/ QString getScheduleName();
 /*public*/ Schedule* getSchedule();
 /*public*/ QString getScheduleId();
 /*public*/ void setScheduleId(QString id);
 /*public*/ QString getScheduleItemId();
 /*public*/ void setScheduleItemId(QString id);
 /*public*/ ScheduleItem* getCurrentScheduleItem();
 /*public*/ void bumpSchedule();
 /*public*/ ScheduleItem* getNextScheduleItem() ;
 /*public*/ int getScheduleCount();
 /*public*/ void setScheduleCount(int count);
 /*public*/ int getScheduleMode();
 /*public*/ QString checkScheduleValid();
 /*public*/ bool acceptsLoadName(QString load);
 /*public*/ bool acceptsLoad(QString load, QString type);
 /*public*/ void setAlternateTrack(Track* track);
 /*public*/ void setDestinationOption(QString option);
 /*public*/ void setDestinationIds(QStringList ids);
 /*public*/ bool addDestination(Location* destination);
 /*public*/ void deleteDestination(Location* destination);
 /*public*/ int getReservedInRoute();
 /*public*/ int getNumberOfCarsInRoute();
 /*public*/ void setReservationFactor(int factor);
 /*public*/ int getReservationFactor();
 /*public*/ void setScheduleMode(int mode);
 /*public*/ void setShipLoadOption(QString option);
 /*public*/ void setIgnoreUsedLengthPercentage(int percentage);
 /*public*/ bool acceptsDestination(Location* destination);
 /*public*/ bool acceptsPickupTrain(Train* train);
 /*public*/ bool acceptsPickupRoute(Route* route);
 /*public*/ bool containsPickupId(QString id);
 /*public*/ bool acceptsDropTrain(Train* train);
 /*public*/ bool acceptsDropRoute(Route* route) ;
 /*public*/ bool containsDropId(QString id);
 /*public*/ bool isSpaceAvailable(Car* car);
 /*public*/ QString checkSchedule(Car* car);
 /*public*/ QString scheduleNext(Car* car);

signals:

public slots:

private:
 Logger* log;
 void common();
 /*private*/ static /*final*/ int SWAP_GENERIC_LOADS; //=1;
 /*private*/ static /*final*/ int EMPTY_CUSTOM_LOADS; //=2;
 /*private*/ static /*final*/ int GENERATE_CUSTOM_LOADS; //=4;
 /*private*/ static /*final*/ int GENERATE_CUSTOM_LOADS_ANY_SPUR; //=8;
 /*private*/ static /*final*/ int EMPTY_GENERIC_LOADS; //=16;
 /*private*/ static /*final*/ int GENERATE_CUSTOM_LOADS_ANY_STAGING_TRACK; //=32;
 /*private*/ static /*final*/ int BLOCK_CARS;// = 1;
 /*private*/ void clearTypeNames();
 QStringList _typeList;// = new ArrayList<String>();
 /*private*/ void setNumberRS(int number);
 /*private*/ void setNumberCars(int number);
 /*private*/ void setNumberEngines(int number);
 QStringList _roadList;// = new ArrayList<String>();
 QList<QString> _destinationIdList;// = new ArrayList<String>();
 /*private*/ bool checkPlannedPickUps(int length);
 /*private*/ void setRoadNames(QStringList roads);
 /*private*/ void setTypeNames(QStringList types);
 QStringList _loadList ;//= new ArrayList<String>();
 /*private*/ void setLoadNames(QStringList loads);
 /*private*/ /*static*/ bool debugFlag;// = false;
 QStringList _shipLoadList;// = new ArrayList<String>();
 QStringList _dropList;// = new ArrayList<String>();
 QStringList _pickupList;// = new ArrayList<String>();
 /*private*/ void setPickupIds(QStringList ids);
 /*private*/ void setShipLoadNames(QStringList loads);
 /*private*/ void setDropIds(QStringList ids);
 /*private*/ QString searchSchedule(Car* car);
 /*private*/ QString checkScheduleItem(ScheduleItem* si, Car* car);
 /*private*/ void loadNext(ScheduleItem* scheduleItem, Car* car);

protected:
 /*protected*/ QString _id; //=NONE;
 /*protected*/ QString _name; //=NONE;
 /*protected*/ QString _trackType; //=NONE; // yard, spur, interchange or staging
 /*protected*/ Location* _location; // the location for this track
 /*protected*/ QString _alternateTrackId; //=NONE; // the alternate track id
 /*protected*/ QString _roadOption; //=ALL_ROADS; // controls which car roads are accepted
 /*protected*/ int _trainDir; //=EAST + WEST + NORTH + SOUTH; // train direction served by this track
 /*protected*/ int _numberRS; //=0; // number of cars and engines
 /*protected*/ int _numberCars; //=0; // number of cars
 /*protected*/ int _numberEngines; //=0; // number of engines
 /*protected*/ int _pickupRS; //=0; // number of pick ups by trains
 /*protected*/ int _dropRS; //=0; // number of set outs by trains
 /*protected*/ int _length; //=0; // length of track
 /*protected*/ int _reserved; //=0; // length of track reserved by trains
 /*protected*/ int _reservedLengthDrops; //=0; // length of track reserved for drops
 /*protected*/ int _numberCarsInRoute; //=0; // number of cars in route to this track
 /*protected*/ int _usedLength; //=0; // length of track filled by cars and engines
 /*protected*/ int _ignoreUsedLengthPercentage; //=0; // value between 0 and 100, 100 = ignore 100%
 /*protected*/ int _moves; //=0; // count of the drops since creation
 /*protected*/ int _blockingOrder; //=0; // defines the order tracks are serviced by trains
 /*protected*/ QString _comment; //=NONE;

 /*protected*/ QString _commentPickup; //=NONE;
 /*protected*/ QString _commentSetout; //=NONE;
 /*protected*/ QString _commentBoth; //=NONE;

 /*protected*/ QString _loadOption; //=ALL_LOADS; // receive track load restrictions
 /*protected*/ QString _shipLoadOption; //=ALL_LOADS; // ship track load restrictions

 /*protected*/ QString _destinationOption; //=ALL_DESTINATIONS; // track destination restriction

 // schedule options
 /*protected*/ QString _scheduleName; //=NONE; // Schedule name if there's one
 /*protected*/ QString _scheduleId; //=NONE; // Schedule id if there's one
 /*protected*/ QString _scheduleItemId; //=NONE; // the current scheduled item id
 /*protected*/ int _scheduleCount; //=0; // the number of times the item has been delivered
 /*protected*/ int _reservedInRoute; //=0; // length of cars in route to this track
 /*protected*/ int _reservationFactor; //=100; // percentage of track space for cars in route
 /*protected*/ int _mode; //=MATCH; // default is match mode

 // drop options
 /*protected*/ QString _dropOption; //=ANY; // controls which route or train can set out cars
 /*protected*/ QString _pickupOption; //=ANY; // controls which route or train can pick up cars
 /*protected*/ int _loadOptions;// = 0;
 /*protected*/ int _blockOptions;// = 0;
 /*protected*/ QString _order;// = NORMAL;
 // pool
 /*protected*/ Pool* _pool;// = null;
 /*protected*/ int _minimumLength;// = 0;
 /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);
 friend class RollingStock;
 friend class Pool;
 friend class Car;
};
}
#endif // TRACK_H
