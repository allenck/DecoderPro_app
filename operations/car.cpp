#include "car.h"
#include "logger.h"
#include "xml.h"
#include "track.h"
#include "location.h"
#include "kernel.h"
#include "vptr.h"
#include "carmanagerxml.h"
#include "carmanager.h"
#include "cartypes.h"
#include "carloads.h"
#include "carload.h"
#include "locationmanager.h"
#include "instancemanager.h"

//Car::Car()
//{
//}
namespace Operations
{
/**
 * Represents a car on the layout
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2009, 2010, 2012, 2013, 2014
 * @version $Revision: 29824 $
 */
///*public*/ class Car extends RollingStock {

    //CarLoads* carLoads = CarLoads::instance();

    /*public static final*/ QString Car::EXTENSION_REGEX = " ";
    /*public static final*/ QString Car::CABOOSE_EXTENSION = tr("(C)");
    /*public static final*/ QString Car::FRED_EXTENSION = tr("(F)");
    /*public static final*/ QString Car::PASSENGER_EXTENSION = tr("(P)");
    /*public static final*/ QString Car::UTILITY_EXTENSION = tr("(U)");
    /*public static final*/ QString Car::HAZARDOUS_EXTENSION = tr("(H)");
    /*public*/ /*static*/  /*final*/ QString Car::LOAD_CHANGED_PROPERTY = "Car load changed"; // NOI18N property change descriptions
    /*public*/ /*static*/  /*final*/ QString Car::WAIT_CHANGED_PROPERTY = "Car wait changed"; // NOI18N
    /*public*/ /*static*/  /*final*/ QString Car::NEXT_WAIT_CHANGED_PROPERTY = "Car next wait changed"; // NOI18N
    /*public*/ /*static*/  /*final*/ QString Car::FINAL_DESTINATION_CHANGED_PROPERTY = "Car final destination changed"; // NOI18N
    /*public*/ /*static*/  /*final*/ QString Car::FINAL_DESTINATION_TRACK_CHANGED_PROPERTY = "Car final destination track changed"; // NOI18N
    /*public*/ /*static*/  /*final*/ QString Car::RETURN_WHEN_EMPTY_CHANGED_PROPERTY = "Car return when empty changed"; // NOI18N
    /*public*/ /*static*/  /*final*/ QString Car::SCHEDULE_ID_CHANGED_PROPERTY = "car schedule id changed"; // NOI18N
    /*public*/ /*static*/  /*final*/ QString Car::KERNEL_NAME_CHANGED_PROPERTY = "kernel name changed"; // NOI18N

    /*public*/ Car::Car(QObject* parent)
     : RollingStock(parent)
    {
        //super();
     common();
        loaded = true;
    }

    /*public*/ Car::Car(QString road, QString number,QObject* parent)
     : RollingStock(road, number, parent) {
        //super(road, number);
 common();
        loaded = true;
        log->debug(tr("New car (%1 %2)").arg(road).arg(number));
//        addPropertyChangeListeners();
    }
    void Car::common()
    {
     log = new Logger("Car");
     setObjectName("Car");

     _passenger = false;
     _hazardous = false;
     _caboose = false;
     _fred = false;
     _utility = false;
     _loadGeneratedByStaging = false;
     _kernel = NULL;
     _loadName = "empty"; //carLoads.getDefaultEmptyName();
     _wait = 0;

     _rweDestination = NULL; // return when empty destination
     _rweDestTrack = NULL; // return when empty track
     _rweLoadName = "empty"; //carLoads::getDefaultEmptyName();

     // schedule items
     _scheduleId = NONE; // the schedule id assigned to this car
     _nextLoadName = NONE; // next load by schedule
     _nextWait = 0; // next wait by schedule
      _finalDestination = NULL; // final destination by schedule or router
      _finalDestTrack = NULL; // final track by schedule or router
      _previousFinalDestination = NULL; // previous final destination (for train resets)
     _previousFinalDestTrack = NULL; // previous final track (for train resets)
      _previousScheduleId = NONE; // previous schedule id (for train resets)
      _pickupScheduleId = NONE;
     _nextPickupScheduleId = NONE; // when the car needs to be pulled

     carLoads = ((CarLoads*)InstanceManager::getDefault("CarLoads"));

    }

    /*public*/ Car* Car::copy() {
        Car* car = new Car();
       car->setBuilt(_built);
       car->setColor(_color);
       car->setLength(_length);
//       car->setLoadName(_loadName);
//       car->setReturnWhenEmptyLoadName(_rweLoadName);
       car->setNumber(_number);
       car->setOwner(_owner);
       car->setRoadName(_road);
       car->setTypeName(_type);
       car->loaded=true;
        return car;
    }

    /*public*/ void Car::setHazardous(bool hazardous) {
        bool old = _hazardous;
        _hazardous = hazardous;
        if (!old == hazardous) {
            setDirtyAndFirePropertyChange("car hazardous", old ? "true" : "false", hazardous ? "true" : "false"); // NOI18N
        }
    }

    /*public*/ bool Car::isHazardous() {
        return _hazardous;
    }

    /*public*/ void Car::setPassenger(bool passenger) {
        bool old = _passenger;
        _passenger = passenger;
        if (!old == passenger) {
            setDirtyAndFirePropertyChange("car passenger", old ? "true" : "false", passenger ? "true" : "false"); // NOI18N
        }
    }

    /*public*/ bool Car::isPassenger() {
        return _passenger;
    }

    /*public*/ void Car::setFred(bool fred) {
        bool old = _fred;
        _fred = fred;
        if (!old == fred) {
            setDirtyAndFirePropertyChange("car has fred", old ? "true" : "false", fred ? "true" : "false"); // NOI18N
        }
    }

    /*public*/ bool Car::hasFred() {
        return _fred;
    }

    /*public*/ void Car::setLoadName(QString load) {
        QString old = _loadName;
        _loadName = load;
        if (old!=(load)) {
            setDirtyAndFirePropertyChange(LOAD_CHANGED_PROPERTY, old, load);
        }
    }

    /*public*/ QString Car::getLoadName() {
        return _loadName;
    }
#if 0
    @Deprecated
    // saved for scripts
    /*public*/ void setLoad(String load) {
        setLoadName(load);
    }

    @Deprecated
    // saved for scripts
    /*public*/ String getLoad() {
        return getLoadName();
    }
#endif
    /*public*/ void Car::setReturnWhenEmptyLoadName(QString load) {
        QString old = _rweLoadName;
        _rweLoadName = load;
        if (old!=(load)) {
            setDirtyAndFirePropertyChange(LOAD_CHANGED_PROPERTY, old, load);
        }
    }

    /*public*/ QString Car::getReturnWhenEmptyLoadName() {
        return _rweLoadName;
    }

    /**
     * Gets the car load's priority.
     */
    /*public*/ QString Car::getLoadPriority() {
        return (carLoads->getPriority(_type, _loadName));
    }

    /**
     * Gets the car load's type, empty or load.
     *
     * @return type empty or type load
     */
    /*public*/ QString Car::getLoadType() {
        return (carLoads->getLoadType(_type, _loadName));
    }

    /*public*/ QString Car::getPickupComment() {
        return carLoads->getPickupComment(getTypeName(), getLoadName());
    }

    /*public*/ QString Car::getDropComment() {
        return carLoads->getDropComment(getTypeName(), getLoadName());
    }

    /*public*/ void Car::setLoadGeneratedFromStaging(bool fromStaging) {
        _loadGeneratedByStaging = fromStaging;
    }

    /*public*/ bool Car::isLoadGeneratedFromStaging() {
        return _loadGeneratedByStaging;
    }

    /**
     * Used to keep track of which item in a schedule was used for this car.
     *
     * @param id
     */
    /*public*/ void Car::setScheduleItemId(QString id) {
        log->debug(tr("Set schedule item id (%1) for car (%2)").arg(id).arg(toString()));
        QString old = _scheduleId;
        _scheduleId = id;
        if (old!=(id)) {
            setDirtyAndFirePropertyChange(SCHEDULE_ID_CHANGED_PROPERTY, old, id);
        }
    }

    /*public*/ QString Car::getScheduleItemId() {
        return _scheduleId;
    }

    /*public*/ void Car::setNextLoadName(QString load) {
        QString old = _nextLoadName;
        _nextLoadName = load;
        if (old!=(load)) {
            setDirtyAndFirePropertyChange(LOAD_CHANGED_PROPERTY, old, load);
        }
    }

    /*public*/ QString Car::getNextLoadName() {
        return _nextLoadName;
    }

    /*public*/ QString Car::getWeightTons() {
        QString weight = RollingStock::getWeightTons();
        if (_weightTons!=(DEFAULT_WEIGHT)) {
            return weight;
        }
        if (!isCaboose() && !isPassenger()) {
            return weight;
        }
        // .9 tons/foot for caboose and passenger cars
        //try {
        bool ok;
            weight = QString::number((int) getLength().toDouble(&ok) * .9);
        if(!ok){
            log->debug(tr("Car (%1) length not set for caboose or passenger car").arg(toString()));
        }
        return weight;
    }

    /**
     * Returns a car's weight adjusted for load. An empty car's weight is 1/3
     * the car's loaded weight.
     */
    /*public*/ int Car::getAdjustedWeightTons() {
        int weightTons = 0;
        //try {
        bool ok;
            // get loaded weight
            weightTons = getWeightTons().toInt(&ok);
            // adjust for empty weight if car is empty, 1/3 of loaded weight
            if (!isCaboose() && !isPassenger() && getLoadType()==(CarLoad::LOAD_TYPE_EMPTY)) {
                weightTons = weightTons / 3;
            }
        if(!ok) {
            log->debug(tr("Car (%1) weight not set").arg(toString()));
        }
        return weightTons;
    }

    /*public*/ void Car::setWait(int count) {
        int old = _wait;
        _wait = count;
        if (old != count) {
            setDirtyAndFirePropertyChange(NEXT_WAIT_CHANGED_PROPERTY, old, count);
        }
    }

    /*public*/ int Car::getWait() {
        return _wait;
    }

    /*public*/ void Car::setNextWait(int count) {
        int old = _nextWait;
        _nextWait = count;
        if (old != count) {
            setDirtyAndFirePropertyChange(NEXT_WAIT_CHANGED_PROPERTY, old, count);
        }
    }

    /*public*/ int Car::getNextWait() {
        return _nextWait;
    }

    /**
     * Sets when this car will be picked up (day of the week)
     * @param id See TrainSchedule->java
     */
    /*public*/ void Car::setPickupScheduleId(QString id) {
        QString old = _pickupScheduleId;
        _pickupScheduleId = id;
        if (old!=(id)) {
            setDirtyAndFirePropertyChange("car pickup schedule changes", old, id); // NOI18N
        }
    }

    /*public*/ QString Car::getPickupScheduleId() {
        return _pickupScheduleId;
    }

    /*public*/ void Car::setNextPickupScheduleId(QString id) {
        QString old = _nextPickupScheduleId;
        _nextPickupScheduleId = id;
        if (old!=(id)) {
            setDirtyAndFirePropertyChange("next car pickup schedule changes", old, id); // NOI18N
        }
    }

    /*public*/ QString Car::getNextPickupScheduleId() {
        return _nextPickupScheduleId;
    }

    /*public*/ QString Car::getPickupScheduleName() {
//        TrainSchedule sch = TrainScheduleManager.instance().getScheduleById(getPickupScheduleId());
//        String name = NONE;
//        if (sch != NULL) {
//            name = sch.getName();
//        }
//        return name;
     return "?";
    }

    /**
     * Sets the final destination for a car.
     *
     * @param destination The final destination for this car.
     */
    /*public*/ void Car::setFinalDestination(Location* destination) {
        Location* old = _finalDestination;
        if (old != NULL) {
            //old.removePropertyChangeListener(this);
         disconnect(old, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

        }
        _finalDestination = destination;
        if (_finalDestination != NULL) {
            //_finalDestination.addPropertyChangeListener(this);
         connect(_finalDestination, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

        }
        // log->debug("Next destination for car ("+toString()+") old: "+old+" new: "+destination);
        if ((old != NULL && old!=(destination)) || (destination != NULL && destination!=(old))) {
            setDirtyAndFirePropertyChange(FINAL_DESTINATION_CHANGED_PROPERTY, VPtr<Location>::asQVariant(old),VPtr<Location>::asQVariant( destination));
        }
    }
#if 0
    @Deprecated
    // available for old scripts
    /*public*/ void setNextDestination(Location destination) {
        setFinalDestination(destination);
    }
#endif
    /*public*/ Location* Car::getFinalDestination() {
        return _finalDestination;
    }

    /*public*/ QString Car::getFinalDestinationName() {
        if (_finalDestination != NULL) {
            return _finalDestination->getName();
        }
        return NONE;
    }

    /*public*/ void Car::setFinalDestinationTrack(Track* track) {
        Track* old = _finalDestTrack;
        _finalDestTrack = track;
        if (track == NULL) {
            setScheduleItemId(NONE);
        }
        if ((old != NULL && old!=(track)) || (track != NULL && track!=(old))) {
            if (old != NULL) {
                //old.removePropertyChangeListener(this);
             disconnect(old, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
                old->deleteReservedInRoute(this);
            }
            if (_finalDestTrack != NULL) {
                _finalDestTrack->addReservedInRoute(this);
                //_finalDestTrack->PropertyChangeSupport::addPropertyChangeListener(this);
                connect(_finalDestTrack, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
            }
            setDirtyAndFirePropertyChange(FINAL_DESTINATION_TRACK_CHANGED_PROPERTY, VPtr<Track>::asQVariant(old), VPtr<Track>::asQVariant(track));
        }
    }
#if 0
    @Deprecated
    // available for old scripts
    /*public*/ void setNextDestinationTrack(Track track) {
        setFinalDestinationTrack(track);
    }
#endif
    /*public*/ Track* Car::getFinalDestinationTrack() {
        return _finalDestTrack;
    }

    /*public*/ QString Car::getFinalDestinationTrackName() {
        if (_finalDestTrack != NULL) {
            return _finalDestTrack->getName();
        }
        return NONE;
    }

    /*public*/ void Car::setPreviousFinalDestination(Location* location) {
        _previousFinalDestination = location;
    }

    /*public*/ Location* Car::getPreviousFinalDestination() {
        return _previousFinalDestination;
    }

    /*public*/ void Car::setPreviousFinalDestinationTrack(Track* track) {
        _previousFinalDestTrack = track;
    }

    /*public*/ Track* Car::getPreviousFinalDestinationTrack() {
        return _previousFinalDestTrack;
    }

    /*public*/ void Car::setPreviousScheduleId(QString id) {
        _previousScheduleId = id;
    }

    /*public*/ QString Car::getPreviousScheduleId() {
        return _previousScheduleId;
    }

    /*public*/ void Car::setReturnWhenEmptyDestination(Location* destination) {
        Location* old = _rweDestination;
        _rweDestination = destination;
        if ((old != NULL && old!=(destination)) || (destination != NULL && destination!=(old))) {
            setDirtyAndFirePropertyChange(RETURN_WHEN_EMPTY_CHANGED_PROPERTY, QVariant(), QVariant());
        }
    }

    /*public*/ Location* Car::getReturnWhenEmptyDestination() {
        return _rweDestination;
    }

    /*public*/ QString Car::getReturnWhenEmptyDestinationName() {
        if (getReturnWhenEmptyDestination() != NULL) {
            return getReturnWhenEmptyDestination()->getName();
        } else {
            return NONE;
        }

    }

    /*public*/ void Car::setReturnWhenEmptyDestTrack(Track* track) {
        Track* old = _rweDestTrack;
        _rweDestTrack = track;
        if ((old != NULL && old!=(track)) || (track != NULL && track!=(old))) {
            setDirtyAndFirePropertyChange(RETURN_WHEN_EMPTY_CHANGED_PROPERTY, QVariant(), QVariant());
        }

    }

    /*public*/ Track* Car::getReturnWhenEmptyDestTrack() {
        return _rweDestTrack;
    }

    /*public*/ QString Car::getReturnWhenEmptyDestTrackName() {
        if (getReturnWhenEmptyDestTrack() != NULL) {
            return getReturnWhenEmptyDestTrack()->getName();
        } else {
            return NONE;
        }
    }

    /*public*/ QString Car::getReturnWhenEmptyDestName() {
        if (getReturnWhenEmptyDestination() != NULL) {
            return getReturnWhenEmptyDestinationName() + "(" + getReturnWhenEmptyDestTrackName() + ")";
        } else {
            return NONE;
        }
    }

    /*public*/ void Car::setCaboose(bool caboose) {
        bool old = _caboose;
        _caboose = caboose;
        if (!old == caboose) {
            setDirtyAndFirePropertyChange("car is caboose", old ? "true" : "false", caboose ? "true" : "false"); // NOI18N
        }
    }

    /*public*/ bool Car::isCaboose() {
        return _caboose;
    }

    /*public*/ void Car::setUtility(bool utility) {
        bool old = _utility;
        _utility = utility;
        if (!old == utility) {
            setDirtyAndFirePropertyChange("car is utility", old ? "true" : "false", utility ? "true" : "false"); // NOI18N
        }
    }

    /*public*/ bool Car::isUtility() {
        return _utility;
    }

    /**
     * A kernel is a group of cars that are switched as a unit.
     *
     * @param kernel
     */
    /*public*/ void Car::setKernel(Kernel* kernel) {
        if (_kernel == kernel) {
            return;
        }
        QString old = "";
        if (_kernel != NULL) {
            old = _kernel->getName();
            _kernel->_delete(this);
        }
        _kernel = kernel;
        QString newName = "";
        if (_kernel != NULL) {
            _kernel->add(this);
            newName = _kernel->getName();
        }
        if (old!=(newName)) {
            setDirtyAndFirePropertyChange(KERNEL_NAME_CHANGED_PROPERTY, old, newName); // NOI18N
        }
    }

    /*public*/ Kernel* Car::getKernel() {
        return _kernel;
    }

    /*public*/ QString Car::getKernelName() {
        if (_kernel != NULL) {
            return _kernel->getName();
        }
        return NONE;
    }

    /**
     * Updates all cars in a kernel. After the update, the cars will all have
     * the same final destination, load, and next load.
     */
    /*public*/ void Car::updateKernel() {
        if (getKernel() != NULL && getKernel()->isLead(this)) {
            foreach (Car* car, getKernel()->getCars())
            {
               car->setFinalDestination(getFinalDestination());
               car->setFinalDestinationTrack(getFinalDestinationTrack());
  #if 0
               car->setLoadGeneratedFromStaging(isLoadGeneratedFromStaging());
                if (CarLoads.instance().containsName(car.getTypeName(), getLoadName())) {
                   car->setLoadName(getLoadName());
                }
                if (CarLoads.instance().containsName(car.getTypeName(), getNextLoadName())) {
                   car->setNextLoadName(getNextLoadName());
                }
#endif
            }
        }
    }

    /**
     * Used to determine if a car can be set out at a destination (location).
     * Track is optional. In addition to all of the tests that testLocation
     * performs, spurs with schedules are also checked.
     *
     * @return status OKAY, TYPE, ROAD, LENGTH, ERROR_TRACK, CAPACITY, SCHEDULE,
     *         CUSTOM
     */
    /*public*/ QString Car::testDestination(Location* destination, Track* track) {
        QString status = RollingStock::testDestination(destination, track);
        if (status!=(Track::OKAY)) {
            return status;
        }
        // now check to see if the track has a schedule
        if (track == NULL) {
            return status;
        }
        return track->checkSchedule(this);
    }

    /**
     * Sets the car's destination on the layout
     *
     * @param destination
     * @param track       (yard, spur, staging, or interchange track)
     * @return "okay" if successful, "type" if the rolling stock's type isn't
     *         acceptable, or "length" if the rolling stock length didn't fit,
     *         or Schedule if the destination will not accept the car because
     *         the spur has a schedule and the car doesn't meet the schedule
     *         requirements. Also changes the car load status when the car
     *         reaches its destination.
     */
    /*public*/ QString Car::setDestination(Location* destination, Track* track) {
        return setDestination(destination, track, false);
    }

    /**
     * Sets the car's destination on the layout
     *
     * @param destination
     * @param track       (yard, spur, staging, or interchange track)
     * @param force       when true ignore track length, type, & road when
     *                    setting destination
     * @return "okay" if successful, "type" if the rolling stock's type isn't
     *         acceptable, or "length" if the rolling stock length didn't fit,
     *         or Schedule if the destination will not accept the car because
     *         the spur has a schedule and the car doesn't meet the schedule
     *         requirements. Also changes the car load status when the car
     *         reaches its destination.
     */
    /*public*/ QString Car::setDestination(Location* destination, Track* track, bool force) {
        // save destination name and track in case car has reached its destination
        QString destinationName = getDestinationName();
        Track* destinationTrack = getDestinationTrack();
        QString status = RollingStock::setDestination(destination, track, force);
        // return if not Okay
        if (status!=(Track::OKAY)) {
            return status;
        }
        // now check to see if the track has a schedule
        if (track != NULL && destinationTrack != track && loaded) {
            status = track->scheduleNext(this);
            if (status!=(Track::OKAY)) {
                return status;
            }
        }
        // done?
        if (destinationName==(NONE) || (destination != NULL) || getTrain() == NULL) {
            return status;
        }
        // car was in a train and has been dropped off, update load, RWE could set a new final destination
        loadNext(destinationTrack);
        return status;
    }

    /*public*/ void Car::loadNext(Track* destTrack) {
        setLoadGeneratedFromStaging(false);
        // update wait count
        setWait(getNextWait());
        setNextWait(0);
        // and the pickup day
        setPickupScheduleId(getNextPickupScheduleId());
        setNextPickupScheduleId(NONE);
        // arrived at spur?
        if (destTrack != NULL && destTrack->getTrackType()==(Track::SPUR)) {
            updateLoad();
        } // update load optionally when car reaches staging
        else if (destTrack != NULL && destTrack->getTrackType()==(Track::STAGING)) {
            if (destTrack->isLoadSwapEnabled() && getLoadName()==(carLoads->getDefaultEmptyName())) {
                setLoadName(carLoads->getDefaultLoadName());
            } else if (destTrack->isLoadSwapEnabled() && getLoadName()==(carLoads->getDefaultLoadName())) {
                setLoadEmpty();
            } else if (destTrack->isLoadEmptyEnabled() && getLoadName()==(carLoads->getDefaultLoadName())) {
                setLoadEmpty();
            } // empty car if it has a custom load
            else if (destTrack->isRemoveCustomLoadsEnabled() && getLoadName()!=(carLoads->getDefaultEmptyName())
                    && getLoadName()!=(carLoads->getDefaultLoadName())) {
                // remove this car's final destination if it has one
                setFinalDestination(NULL);
                setFinalDestinationTrack(NULL);
                // car arriving into staging with the RWE load?
                if (getLoadName()==(getReturnWhenEmptyLoadName())) {
                    setLoadName(carLoads->getDefaultEmptyName());
                } else {
                    setLoadEmpty(); // note that RWE sets the car's final destination
                }
            }
        }
    }

    /**
     * Updates a car's load when placed at a spur. Load change delayed if wait
     * count is greater than zero.
     */
    /*public*/ void Car::updateLoad() {
        if (getWait() > 0) {
            return; // change load when wait count reaches 0
        }		// arriving at spur with a schedule?
        if (getNextLoadName()!=(NONE)) {
            setLoadName(getNextLoadName());
            setNextLoadName(NONE);
            // RWE load and no destination?
            if (getLoadName()==(getReturnWhenEmptyLoadName()) && getFinalDestination() == NULL) {
                setReturnWhenEmpty();
            }
            return;
        }
        // flip load names
        if (getLoadType()==(CarLoad::LOAD_TYPE_EMPTY)) {
            setLoadName(carLoads->getDefaultLoadName());
        } else {
            setLoadEmpty();
        }
    }

    /**
     * Sets the car's load to empty, triggers RWE load and destination if
     * enabled.
     */
    /*private*/ void Car::setLoadEmpty() {
        if (getLoadName()!=(getReturnWhenEmptyLoadName())) {
            setLoadName(getReturnWhenEmptyLoadName()); // default RWE load is the "E" load
            setReturnWhenEmpty();
        }
    }

    /*private*/ void Car::setReturnWhenEmpty() {
        if (getReturnWhenEmptyDestination() != NULL) {
            setFinalDestination(getReturnWhenEmptyDestination());
            if (getReturnWhenEmptyDestTrack() != NULL) {
                setFinalDestinationTrack(getReturnWhenEmptyDestTrack());
            }
            log->debug(tr("Car (%1) has return when empty destination (%2, %3) load %4").arg(toString()).arg(
                    getFinalDestinationName()).arg(getFinalDestinationTrackName()).arg(getLoadName()));
        }
    }

    /*public*/ void Car::reset() {
        setScheduleItemId(getPreviousScheduleId()); // revert to previous
        setNextLoadName(NONE);
        setNextWait(0);
        setFinalDestination(getPreviousFinalDestination()); // revert to previous
        setFinalDestinationTrack(getPreviousFinalDestinationTrack()); // revert to previous
        if (isLoadGeneratedFromStaging()) {
            setLoadGeneratedFromStaging(false);
            setLoadName(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultEmptyName());
        }

        RollingStock::reset();
    }

    /*public*/ void Car::dispose() {
        setKernel(NULL);
        setFinalDestination(NULL); // removes property change listener
        setFinalDestinationTrack(NULL); // removes property change listener
        ((CarTypes*)InstanceManager::getDefault("CarTypes"))->removePropertyChangeListener(this);
//        CarLengths.instance().removePropertyChangeListener(this);
        RollingStock::dispose();
    }

    // used to stop a track's schedule from bumping when loading car database
    /*private*/ bool loaded = false;

    /**
     * Construct this Entry from XML. This member has to remain synchronized
     * with the detailed DTD in operations-cars.dtd
     *
     * @param e Car XML element
     */
    /*public*/ Car::Car(QDomElement e, QObject* parent) :
        RollingStock(e, parent)
    {
     common();

        loaded = true ;
        QString a;
        if ((a = e.attribute(Xml::PASSENGER)) != NULL) {
            _passenger = a==(Xml::_TRUE);
        }
        if ((a = e.attribute(Xml::HAZARDOUS)) != NULL) {
            _hazardous = a==(Xml::_TRUE);
        }
        if ((a = e.attribute(Xml::CABOOSE)) != NULL) {
            _caboose = a==(Xml::_TRUE);
        }
        if ((a = e.attribute(Xml::FRED)) != NULL) {
            _fred = a==(Xml::_TRUE);
        }
        if ((a = e.attribute(Xml::UTILITY)) != NULL) {
            _utility = a==(Xml::_TRUE);
        }
        if ((a = e.attribute(Xml::KERNEL)) != NULL) {
            Kernel* k = ((CarManager*)InstanceManager::getDefault("CarManager"))->getKernelByName(a);
            if (k != NULL) {
                setKernel(k);
                if ((a = e.attribute(Xml::LEAD_KERNEL)) != NULL && a==(Xml::_TRUE)) {
                    _kernel->setLead(this);
                }
            } else {
                log->error("Kernel " + a + " does not exist");
            }
        }

        if ((a = e.attribute(Xml::LOAD)) != NULL) {
            _loadName = a;
        }
        if ((a = e.attribute(Xml::LOAD_FROM_STAGING)) != NULL && a==(Xml::_TRUE)) {
            setLoadGeneratedFromStaging(true);
        }

        if ((a = e.attribute(Xml::WAIT)) != NULL) {
            //try {
         bool ok;
                _wait = a.toInt(&ok);
            if(!ok) {
                log->error(tr("Wait count (%1) for car (%2) isn't a valid number!").arg(a).arg(toString()));
            }
        }
        if ((a = e.attribute(Xml::PICKUP_SCHEDULE_ID)) != NULL) {
            _pickupScheduleId = a;
        }
        if ((a = e.attribute(Xml::SCHEDULE_ID)) != NULL) {
            _scheduleId = a;
        }
        if ((a = e.attribute(Xml::NEXT_LOAD)) != NULL) {
            _nextLoadName = a;
        }
        if ((a = e.attribute(Xml::NEXT_WAIT)) != NULL) {
            //try {
            bool ok;
                _nextWait = a.toInt(&ok);
            if(!ok) {
                log->error(tr("Next wait count (%1) for car (%1) isn't a valid number!").arg(a).arg(toString()));
            }
        }
        if ((a = e.attribute(Xml::NEXT_PICKUP_SCHEDULE_ID)) != NULL) {
            _nextPickupScheduleId = a;
        }
        if ((a = e.attribute(Xml::NEXT_DEST_ID)) != NULL) {
            setFinalDestination(((LocationManager*)InstanceManager::getDefault("LocationManager"))->getLocationById(a));
        }
        if (getFinalDestination() != NULL && (a = e.attribute(Xml::NEXT_DEST_TRACK_ID)) != NULL) {
            setFinalDestinationTrack(getFinalDestination()->getTrackById(a));
        }
        if ((a = e.attribute(Xml::PREVIOUS_NEXT_DEST_ID)) != NULL) {
            setPreviousFinalDestination(((LocationManager*)InstanceManager::getDefault("LocationManager"))->getLocationById(a));
        }
        if (getPreviousFinalDestination() != NULL && (a = e.attribute(Xml::PREVIOUS_NEXT_DEST_TRACK_ID)) != NULL) {
            setPreviousFinalDestinationTrack(getPreviousFinalDestination()->getTrackById(a));
        }
        if ((a = e.attribute(Xml::PREVIOUS_SCHEDULE_ID)) != NULL) {
            setPreviousScheduleId(a);
        }
        if ((a = e.attribute(Xml::RWE_DEST_ID)) != NULL) {
            _rweDestination = ((LocationManager*)InstanceManager::getDefault("LocationManager"))->getLocationById(a);
        }
        if (_rweDestination != NULL && (a = e.attribute(Xml::RWE_DEST_TRACK_ID)) != NULL) {
            _rweDestTrack = _rweDestination->getTrackById(a);
        }
        if ((a = e.attribute(Xml::RWE_LOAD)) != NULL) {
            _rweLoadName = a;
        }

        addPropertyChangeListeners();

    }

    /**
     * Create an XML element to represent this Entry. This member has to remain
     * synchronized with the detailed DTD in operations-cars.dtd.
     *
     * @return Contents in a JDOM Element
     */
    /*public*/ QDomElement Car::store(QDomDocument doc) {
        QDomElement e = doc.createElement(Xml::CAR);
//        QDomElement e = QDomElement();
//        e.setTagName(Xml::CAR);
        //log->debug("Car::store document " + doc.nodeName());
        RollingStock::store(e);
        if (isPassenger()) {
            e.setAttribute(Xml::PASSENGER, isPassenger() ? Xml::_TRUE : Xml::_FALSE);
        }
        if (isHazardous()) {
            e.setAttribute(Xml::HAZARDOUS, isHazardous() ? Xml::_TRUE : Xml::_FALSE);
        }

        if (isCaboose()) {
            e.setAttribute(Xml::CABOOSE, isCaboose() ? Xml::_TRUE : Xml::_FALSE);
        }
        if (hasFred()) {
            e.setAttribute(Xml::FRED, hasFred() ? Xml::_TRUE : Xml::_FALSE);
        }
        if (isUtility()) {
            e.setAttribute(Xml::UTILITY, isUtility() ? Xml::_TRUE : Xml::_FALSE);
        }

        if (getKernel() != NULL) {
            e.setAttribute(Xml::KERNEL, getKernelName());
            if (getKernel()->isLead(this)) {
                e.setAttribute(Xml::LEAD_KERNEL, Xml::_TRUE);
            }
        }

        e.setAttribute(Xml::LOAD, getLoadName());

        if (isLoadGeneratedFromStaging()) {
            e.setAttribute(Xml::LOAD_FROM_STAGING, Xml::_TRUE);
        }

        if (getWait() != 0) {
            e.setAttribute(Xml::WAIT, getWait());
        }

        if (getPickupScheduleId()!=(NONE)) {
            e.setAttribute(Xml::PICKUP_SCHEDULE_ID, getPickupScheduleId());
        }

        if (getScheduleItemId()!=(NONE)) {
            e.setAttribute(Xml::SCHEDULE_ID, getScheduleItemId());
        }

        if (getNextLoadName()!=(NONE)) {
            e.setAttribute(Xml::NEXT_LOAD, getNextLoadName());
        }

        if (getNextWait() != 0) {
            e.setAttribute(Xml::NEXT_WAIT, (getNextWait()));
        }

        if (getNextPickupScheduleId()!=(NONE)) {
            e.setAttribute(Xml::NEXT_PICKUP_SCHEDULE_ID, getNextPickupScheduleId());
        }

        if (getFinalDestination() != NULL) {
            e.setAttribute(Xml::NEXT_DEST_ID, getFinalDestination()->getId());
            if (getFinalDestinationTrack() != NULL) {
                e.setAttribute(Xml::NEXT_DEST_TRACK_ID, getFinalDestinationTrack()->getId());
            }
        }
        if (getPreviousFinalDestination() != NULL) {
            e.setAttribute(Xml::PREVIOUS_NEXT_DEST_ID, getPreviousFinalDestination()->getId());
            if (getPreviousFinalDestinationTrack() != NULL) {
                e.setAttribute(Xml::PREVIOUS_NEXT_DEST_TRACK_ID, getPreviousFinalDestinationTrack()->getId());
            }
        }

        if (getPreviousScheduleId()!=(NONE)) {
            e.setAttribute(Xml::PREVIOUS_SCHEDULE_ID, getPreviousScheduleId());
        }
        if (getReturnWhenEmptyDestination() != NULL) {
            e.setAttribute(Xml::RWE_DEST_ID, getReturnWhenEmptyDestination()->getId());
            if (getReturnWhenEmptyDestTrack() != NULL) {
                e.setAttribute(Xml::RWE_DEST_TRACK_ID, getReturnWhenEmptyDestTrack()->getId());
            }
        }
        if (getReturnWhenEmptyLoadName()!=(carLoads->getDefaultEmptyName())) {
            e.setAttribute(Xml::RWE_LOAD, getReturnWhenEmptyLoadName());
        }

        return e;
    }

    /*protected*/ void Car::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
        // Set dirty
        ((CarManagerXml*)InstanceManager::getDefault("CarManagerXml"))->setDirty(true);
        RollingStock::setDirtyAndFirePropertyChange(p, old, n);
    }

    /*private*/ void Car::addPropertyChangeListeners() {
        //CarTypes.instance().addPropertyChangeListener(this);
     connect(((CarTypes*)InstanceManager::getDefault("CarTypes")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

//        CarLengths.instance().addPropertyChangeListener(this);
    }

    /*public*/ void Car::propertyChange(PropertyChangeEvent* e)
    {
        RollingStock::propertyChange(e);

        if (e->getPropertyName()==(CarTypes::CARTYPES_NAME_CHANGED_PROPERTY)) {
            if (e->getOldValue()==(getTypeName())) {
                if (log->isDebugEnabled()) {
                 log->debug(tr("Car (%1) sees type name change old: (%2) new: (%3)").arg(toString()).arg(e->getOldValue().toString()).arg(e
                                  ->getNewValue().toString())); // NOI18N
                }
                setTypeName( e->getNewValue().toString());
            }
        }
#if 0
        if (e->getPropertyName()==(CarLengths.CARLENGTHS_NAME_CHANGED_PROPERTY)) {
            if (e->getOldValue()==(getLength())) {
                if (log->isDebugEnabled()) {
                    log->debug("Car ({}) sees length name change old: ({}) new: ({})", toString(), e->getOldValue(), e
                            .getNewValue()); // NOI18N
                }
                setLength((String) e->getNewValue());
            }
        }
#endif
        if (e->getPropertyName()==(Location::DISPOSE_CHANGED_PROPERTY)) {
            if (e->getSource() == _finalDestination) {
                if (log->isDebugEnabled()) {
                    log->debug(tr("delete final destination for car: (%1)").arg(toString()));
                }
                setFinalDestination(NULL);
            }
        }
        if (e->getPropertyName()==(Track::DISPOSE_CHANGED_PROPERTY)) {
            if (e->getSource() == _finalDestTrack) {
                if (log->isDebugEnabled()) {
                    log->debug(tr("delete final destination for car: (%1)").arg(toString()));
                }
                setFinalDestinationTrack(NULL);
            }
        }
    }
}
