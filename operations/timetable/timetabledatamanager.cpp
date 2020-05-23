#include "timetabledatamanager.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "timetablexml.h"
#include "tttrain.h"
#include "ttschedule.h"
#include "station.h"

namespace TimeTable
{

/**
 * Provide data base management services.
 * <p>
 * The data structure was migrated from a MySQL database.  As such, it contains
 * <strong>tables</strong> implemented as TreeMaps and <strong>records</strong>
 * implemented as Classes.  The logical relationships are handled using foreign keys.
 *
 * <pre>
 * Data Structure:
 *   Layout -- Global data.
 *     TrainTypes -- Assigned to trains for diagram colors.
 *     Segments -- Used for division / sub-division arrangements.
 *       Stations -- Any place a train can stop->
 *     Schedules -- Basic information about a schedule.
 *       Trains -- Train characteristics.
 *         Stops -- A junction between a train and a station that contains arrival and departure times.
 * </pre>
 *
 * @author Dave Sand Copyright (C) 2018
 */
// /*public*/ class TimeTableDataManager {

    /**
     * Create a TimeTableDataManager instance.
     * @param loadData False to create an empty instance, otherwise load the data
     */
    /*public*/ TimeTableDataManager::TimeTableDataManager(bool loadData, QObject *parent) : QObject(parent) {
        (TimeTableDataManager*)InstanceManager::setDefault("TimeTableDataManager", this);
        if (loadData) {
            _lockCalculate = true;
            if (!TimeTableXml::doLoad()) {
                log->error("Unable to load the time table data");  // NOI18N
            }
            _lockCalculate = false;
        }
    }

    /**
     * Use the InstanceManager to only allow a single data manager instance.
     * @return the current or new data manager.
     */
    /*public*/ /*static*/ TimeTableDataManager* TimeTableDataManager::getDataManager() {
        TimeTableDataManager* dm = (TimeTableDataManager*)InstanceManager::getNullableDefault("TimeTableDataManager");
        if (dm != nullptr) {
            return dm;
        }
        return new TimeTableDataManager(true);
    }

    // Exception key words
    /*public static final*/ QString TimeTableDataManager::CLOCK_LT_1 = "FastClockLt1";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::DURATION_LT_0 = "DurationLt0";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::THROTTLES_LT_0 = "ThrottlesLt0";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::THROTTLES_IN_USE = "ThrottlesInUse";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::SCALE_NF = "ScaleNotFound";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::TIME_OUT_OF_RANGE = "TimeOutOfRange";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::SEGMENT_CHANGE_ERROR = "SegmentChangeError";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::DISTANCE_LT_0 = "DistanceLt0";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::SIDINGS_LT_0 = "SidingsLt0";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::STAGING_LT_0 = "StagingLt0";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::STAGING_IN_USE = "StagingInUse";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::START_HOUR_RANGE = "StartHourRange";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::DURATION_RANGE = "DurationRange";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::DEFAULT_SPEED_LT_0 = "DefaultSpeedLt0";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::START_TIME_FORMAT = "StartTimeFormat";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::START_TIME_RANGE = "StartTimeRange";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::THROTTLE_RANGE = "ThrottleRange";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::STAGING_RANGE = "StagingRange";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::STOP_DURATION_LT_0 = "StopDurationLt0";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::NEXT_SPEED_LT_0 = "NextSpeedLt0";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::LAYOUT_HAS_CHILDREN = "LayoutHasChildren";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::TYPE_HAS_REFERENCE = "TypeHasReference";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::SEGMENT_HAS_CHILDREN = "SegmentHaSChildren";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::STATION_HAS_REFERENCE = "StationHasReference";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::SCHEDULE_HAS_CHILDREN = "ScheduleHasChildren";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::TRAIN_HAS_CHILDREN = "TrainHasChildren";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::TYPE_ADD_FAIL = "TypeAddFail";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::SEGMENT_ADD_FAIL = "SegmentAddFail";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::STATION_ADD_FAIL = "StationAddFail";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::SCHEDULE_ADD_FAIL = "ScheduleAddFail";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::TRAIN_ADD_FAIL = "TrainAddFail";    // NOI18N
    /*public static final*/ QString TimeTableDataManager::STOP_ADD_FAIL = "StopAddFail";    // NOI18N



    /*public*/ void TimeTableDataManager::setLockCalculate(bool lock) {
        _lockCalculate = lock;
    }

    // ------------ Map maintenance methods ------------ //

    /*public*/ void TimeTableDataManager::addLayout(int id, Layout* newLayout) {
        _layoutMap.insert(id, newLayout);
    }

    /*public*/ void TimeTableDataManager::addTrainType(int id, TrainType* newTrainType) {
        _trainTypeMap.insert(id, newTrainType);
    }

    /*public*/ void TimeTableDataManager::addSegment(int id, Segment* newSegment) {
        _segmentMap.insert(id, newSegment);
    }

    /**
     * Add a new station
     * Create a SegmentStation instance.
     * Add it to the SegmentStation list.
     */
    /*public*/ void TimeTableDataManager::addStation(int id, Station* newStation) {
        _stationMap.insert(id, newStation);
        SegmentStation* segmentStation = new SegmentStation(newStation->getSegmentId(), id, this);
        if (!_segmentStations.contains(segmentStation)) {
            _segmentStations.append(segmentStation);
        }
    }

    /*public*/ void TimeTableDataManager::addSchedule(int id, TimeTable::TTSchedule* newSchedule) {
        _scheduleMap.insert(id, newSchedule);
    }

    /*public*/ void TimeTableDataManager::addTrain(int id, TTTrain* newTrain) {
        _trainMap.insert(id, newTrain);
    }

    /*public*/ void TimeTableDataManager::addStop(int id, Stop* newStop) {
        _stopMap.insert(id, newStop);
    }

    /**
     * Delete the layout if there are no train types, segments or schedules.
     * param id The layout id.
     * @throws IllegalArgumentException LAYOUT_HAS_CHILDREN
     */
    /*public*/ void TimeTableDataManager::deleteLayout(int id) {
        if (!getTrainTypes(id, false).isEmpty()
                || !getSegments(id, false).isEmpty()
                || !getSchedules(id, false).isEmpty()) {
            throw new IllegalArgumentException(LAYOUT_HAS_CHILDREN);
        }
        _layoutMap.remove(id);
    }

    /**
     * Delete the train type if there are no train references.
     * param id The train type id.
     * @throws IllegalArgumentException TYPE_HAS_REFERENCE
     */
    /*public*/ void TimeTableDataManager::deleteTrainType(int id) {
        if (!getTrains(0, id, false).isEmpty()) {
            throw  IllegalArgumentException(TYPE_HAS_REFERENCE);
        }
        _trainTypeMap.remove(id);
    }

    /**
     * Delete the segment if it has no stations.
     * param id The segment id.
     * @throws IllegalArgumentException SEGMENT_HAS_CHILDREN
     */
    /*public*/ void TimeTableDataManager::deleteSegment(int id) {
        if (!getStations(id, false).isEmpty()) {
            throw  IllegalArgumentException(SEGMENT_HAS_CHILDREN);
        }
        _segmentMap.remove(id);
    }

    /**
     * Delete the station if there are no stop references.
     * param id The station id.
     * @throws IllegalArgumentException STATION_HAS_REFERENCE
     */
    /*public*/ void TimeTableDataManager::deleteStation(int id) {
        if (!getStops(0, id, false).isEmpty()) {
            throw IllegalArgumentException(STATION_HAS_REFERENCE);
        }

        int segmentId = getStation(id)->getSegmentId();
        QList<SegmentStation*> list = QList<SegmentStation*>();
        for (SegmentStation* segmentStation : _segmentStations) {
            if (segmentStation->getStationId() == id && segmentStation->getSegmentId() == segmentId) {
                list.append(segmentStation);
            }
        }
        for (SegmentStation* ss : list) {
            _segmentStations.removeOne(ss);
        }

        _stationMap.remove(id);
    }

    /**
     * Delete the schedule if it has no trains.
     * param id The schedule id.
     * @throws IllegalArgumentException SCHEDULE_HAS_CHILDREN
     */
    /*public*/ void TimeTableDataManager::deleteSchedule(int id) {
        if (!getTrains(id, 0, false).isEmpty()) {
            throw IllegalArgumentException(SCHEDULE_HAS_CHILDREN);
        }
        _scheduleMap.remove(id);
    }

    /**
     * Delete the train if it has no stops.
     * param id The train id.
     * @throws IllegalArgumentException TRAIN_HAS_CHILDREN
     */
    /*public*/ void TimeTableDataManager::deleteTrain(int id) {
        if (!getStops(id, 0, false).isEmpty()) {
            throw  IllegalArgumentException(TRAIN_HAS_CHILDREN);
        }
        _trainMap.remove(id);
    }

    /**
     * Delete the stop and update train schedule.
     * param id The stop id.
     */
    /*public*/ void TimeTableDataManager::deleteStop(int id) {
        int trainId = getStop(id)->getTrainId();
        _stopMap.remove(id);
        calculateTrain(trainId, true);
    }

    // ------------ Map access methods: get by id  ------------ //

    /*public*/ Layout* TimeTableDataManager::getLayout(int id) {
        return _layoutMap.value(id);
    }

    /*public*/ TrainType* TimeTableDataManager::getTrainType(int id) {
        return _trainTypeMap.value(id);
    }

    /*public*/ Segment* TimeTableDataManager::getSegment(int id) {
        return _segmentMap.value(id);
    }

    /*public*/ Station* TimeTableDataManager::getStation(int id) {
        return _stationMap.value(id);
    }

    /*public*/ TimeTable::TTSchedule* TimeTableDataManager::getSchedule(int id) {
        return _scheduleMap.value(id);
    }

    /*public*/ TTTrain* TimeTableDataManager::getTrain(int id) {
        return _trainMap.value(id);
    }

    /*public*/ Stop* TimeTableDataManager::getStop(int id) {
        return _stopMap.value(id);
    }

    /**
     * Get the last key from the map and add 1.
     * @param type The record type which is used to select the appropriate map.
     * @return the next id, or 0 if there is an error.
     */
    /*public*/ int TimeTableDataManager::getNextId(QString type) {
        int nextId = 0;
        if(type == "Layout") {
                nextId = (_layoutMap.isEmpty()) ? 1 : _layoutMap.lastKey() + 1;
         }
         else if(type == "TrainType") {
                nextId = (_trainTypeMap.isEmpty()) ? 1 : _trainTypeMap.lastKey() + 1;
        }
        else if(type ==  "Segment") {
                nextId = (_segmentMap.isEmpty()) ? 1 : _segmentMap.lastKey() + 1;
        }
        else if(type ==  "Station") {
                nextId = (_stationMap.isEmpty()) ? 1 : _stationMap.lastKey() + 1;
        }
        else if(type ==  "Schedule") {
                nextId = (_scheduleMap.isEmpty()) ? 1 : _scheduleMap.lastKey() + 1;
        }
        else if(type ==  "Train") {
                nextId = (_trainMap.isEmpty()) ? 1 : _trainMap.lastKey() + 1;
        }
        else if(type == "Stop") {
                nextId = (_stopMap.isEmpty()) ? 1 : _stopMap.lastKey() + 1;
        }
        else {
                log->error(tr("getNextId: Invalid record type: %1").arg(type));  // NOI18N
        }
        return nextId;
    }

    // ------------ Map access methods: get all entries or by foreign key ------------ //

    /**
     * Create a list of layouts
     * @param sort If true, sort the resulting list
     * @return a list of layouts
     */
    /*public*/ QList<Layout*> TimeTableDataManager::getLayouts(bool sort) {
        // No foreign keys
        QList<Layout*> list = QList<Layout*>(_layoutMap.values());
        if (sort) {
//  TODO:          Collections.sort(list, (o1, o2) -> o1.getLayoutName().compareTo(o2.getLayoutName()));
        }
        return list;
    }

    /**
     * Create a list of train types
     * @param fKeyLayout If non-zero, select the types that have the specified foreign key
     * @param sort If true, sort the resulting list
     * @return a list of train types
     */
    /*public*/ QList<TrainType*> TimeTableDataManager::getTrainTypes(int fKeyLayout, bool sort) {
        QList<TrainType*> list = QList<TrainType*>();
        for (TrainType* type : _trainTypeMap.values()) {
            if (fKeyLayout == 0 || fKeyLayout == type->getLayoutId()) {
                list.append(type);
            }
        }
        if (sort) {
//  TODO:             Collections.sort(list, (o1, o2) -> o1.getTypeName().compareTo(o2.getTypeName()));
        }
        return list;
    }

    /**
     * Create a list of segments
     * @param fKeyLayout If non-zero, select the segments that have the specified foreign key
     * @param sort If true, sort the resulting list
     * @return a list of segments
     */
    /*public*/ QList<Segment*> TimeTableDataManager::getSegments(int fKeyLayout, bool sort) {
        QList<Segment*> list = QList<Segment*>();
        for (Segment* segment : _segmentMap.values()) {
            if (fKeyLayout == 0 || fKeyLayout == segment->getLayoutId()) {
                list.append(segment);
            }
        }
        if (sort) {
 //  TODO:            Collections.sort(list, (o1, o2) -> o1.getSegmentName().compareTo(o2.getSegmentName()));
        }
        return list;
    }

    /**
     * Create a list of stations
     * @param fKeySegment If non-zero, select the stations that have the specified foreign key
     * @param sort If true, sort the resulting list
     * @return a list of stations
     */
    /*public*/ QList<Station*> TimeTableDataManager::getStations(int fKeySegment, bool sort) {
        QList<Station*> list = QList<Station*>();
        for (Station* station : _stationMap.values()) {
            if (fKeySegment == 0 || fKeySegment == station->getSegmentId()) {
                list.append(station);
            }
        }
        if (sort) {
 //  TODO:            Collections.sort(list, (o1, o2) -> Double.compare(o1.getDistance(), o2.getDistance()));
        }
        return list;
    }

    /**
     * Create a list of schedules
     * @param fKeyLayout If non-zero, select the schedules that have the specified foreign key
     * @param sort If true, sort the resulting list
     * @return a list of schedules
     */
    /*public*/ QList<TimeTable::TTSchedule*> TimeTableDataManager::getSchedules(int fKeyLayout, bool sort) {
        QList<TimeTable::TTSchedule*> list = QList<TimeTable::TTSchedule*>();
        for (TimeTable::TTSchedule* schedule : _scheduleMap.values()) {
            if (fKeyLayout == 0 || fKeyLayout == schedule->getLayoutId()) {
                list.append(schedule);
            }
        }
        if (sort) {
 //  TODO:            Collections.sort(list, (o1, o2) -> o1.getScheduleName().compareTo(o2.getScheduleName()));
        }
        return list;
    }

    /**
     * Create a list of trains
     * @param fKeySchedule If non-zero, select the trains that have the specified foreign key
     * @param fKeyType If non-zero, select the trains that have the specified foreign key
     * @param sort If true, sort the resulting list
     * @return a list of trains
     */
    /*public*/ QList<TTTrain*> TimeTableDataManager::getTrains(int fKeySchedule, int fKeyType, bool sort) {
        QList<TTTrain*> list = QList<TTTrain*>();
        for (TTTrain* train : _trainMap.values()) {
            if ((fKeySchedule == 0 && fKeyType == 0)
                    || fKeySchedule == train->getScheduleId()
                    || fKeyType == train->getTypeId()) {
                list.append(train);
            }
        }
        if (sort) {
//  TODO:             Collections.sort(list, (o1, o2) -> o1.getTrainName().compareTo(o2.getTrainName()));
        }
        return list;
    }

    /**
     * Create a list of stops
     * @param fKeyTrain If non-zero, select the stops that have the specified foreign key
     * @param fKeyStation If non-zero, select the stops that have the specified foreign key
     * @param sort If true, sort the resulting list
     * @return a list of stops
     */
    /*public*/ QList<Stop*> TimeTableDataManager::getStops(int fKeyTrain, int fKeyStation, bool sort) {
        QList<Stop*> list = QList<Stop*>();
        for (Stop* stop : _stopMap.values()) {
            if ((fKeyTrain == 0 && fKeyStation == 0)
                    || fKeyTrain == stop->getTrainId()
                    || fKeyStation == stop->getStationId()) {
                list.append(stop);
            }
        }
        if (sort) {
//  TODO:             Collections.sort(list, (o1, o2) -> Integer.compare(o1.getSeq(), o2.getSeq()));
        }
        return list;
    }

    // ------------ Special Map access methods ------------ //

    /*public*/ Layout* TimeTableDataManager::getLayoutForStop(int stopId) {
        return getLayout(getSchedule(getTrain(getStop(stopId)->getTrainId())->getScheduleId())->getLayoutId());
    }

    /*public*/ QList<SegmentStation*> TimeTableDataManager::getSegmentStations(int layoutId) {
        QList<SegmentStation*> list = QList<SegmentStation*>();
        for (SegmentStation* segmentStation : _segmentStations) {
            if (getSegment(segmentStation->getSegmentId())->getLayoutId() == layoutId) {
                list.append(segmentStation);
            }
        }
//  TODO:         Collections.sort(list, (o1, o2) -> o1.toString().compareTo(o2.toString()));
        return list;
    }

    // ------------  Calculate Train Times ------------

    /**
     * Update the stops for all of the trains for this layout.
     * Invoked by updates to fast clock speed, metric, scale and station distances.
     * @param layoutId The id for the layout that has been updated.
     */
    void TimeTableDataManager::calculateLayoutTrains(int layoutId, bool updateStops) {
        if (_lockCalculate) return;
        for (TimeTable::TTSchedule* schedule : getSchedules(layoutId, false)) {
            calculateScheduleTrains(schedule->getScheduleId(), updateStops);
        }
    }

    /**
     * Update the stop times for all of the trains that use this schedule.
     * @param scheduleId The id for the schedule that has been updated.
     */
    void TimeTableDataManager::calculateScheduleTrains(int scheduleId, bool updateStops) {
        if (_lockCalculate) return;
        for (TTTrain* train : getTrains(scheduleId, 0, false)) {
            calculateTrain(train->getTrainId(), updateStops);
        }
    }

    /**
     * Calculate the arrival and departure times for all of the stops.
     * @param trainId The id of the train to be updated.
     * @param updateStops When true, update the arrive and depart times.
     * @throws IllegalArgumentException when stop times are outside of the
     * schedule times or a segment change failed.  The TIME_OUT_OF_RANGE
     * exception message includes the stop id and train name.  The SEGMENT_CHANGE_ERROR
     * message includes the segment name and the station name.  The tilde
     * character is used as the string separator.
     */
    /*public*/ void TimeTableDataManager::calculateTrain(int trainId, bool updateStops) {
        if (_lockCalculate) return;
        TTTrain* train = getTrain(trainId);
        TimeTable::TTSchedule* schedule = getSchedule(train->getScheduleId());
        Layout* layout = getLayout(schedule->getLayoutId());
        QList<Stop*> stops = getStops(trainId, 0, true);

        double smile = layout->getScaleMK();
        int startHH = schedule->getStartHour();
        int duration = schedule->getDuration();
        int currentTime = train->getStartTime();
        int defaultSpeed = train->getDefaultSpeed();

        int checkStart = startHH;
        int checkDuration = duration;

        QString currentStationName = "";
        double currentDistance = 0.0;
        int currentSegment = 0;
        int currentSpeed = 0;
        int newArrive = 0;
        int newDepart = 0;
        int elapseTime = 0;
        bool firstStop = true;

        for (Stop* stop : stops) {
            Station* station = getStation(stop->getStationId());
            Segment* segment = getSegment(station->getSegmentId());
            if (firstStop) {
                newArrive = currentTime;
                currentTime += stop->getDuration();
                newDepart = currentTime;
                currentDistance = station->getDistance();
                currentSpeed = (stop->getNextSpeed() > 0) ? stop->getNextSpeed() : defaultSpeed;
                currentStationName = station->getStationName();
                currentSegment = segment->getSegmentId();

                if (validateTime(checkStart, checkDuration, newArrive) && validateTime(checkStart, checkDuration, newDepart)) {
                    if (updateStops) {
                        stop->setArriveTime(newArrive);
                        stop->setDepartTime(newDepart);
                    }
                } else {
                    throw  IllegalArgumentException(tr("%1~%2~%3").arg(TIME_OUT_OF_RANGE).arg(stop->getSeq()).arg(train->getTrainName()));  // NOI18N
                }
                firstStop = false;
                continue;
            }

            // Calculate times for remaining stops
            double wrkDistance = qAbs(currentDistance - station->getDistance());

            // If the segment has changed, a new distance will need to be calculated.
            if (segment->getSegmentId() != currentSegment) {
                // Find the station in the current segment that has the same name
                // as the station in the previous segment.
                Station* wrkStation = nullptr;
                for (Station* findStation : getStations(segment->getSegmentId(), false)) {
                    if (findStation->getStationName() == (currentStationName)) {
                        wrkStation = findStation;
                        break;
                    }
                }
                if (wrkStation == nullptr) {
                    throw new IllegalArgumentException(SEGMENT_CHANGE_ERROR);
                }
                wrkDistance = qAbs(station->getDistance() - wrkStation->getDistance());
            }

            elapseTime = (int) qRound(wrkDistance / smile / currentSpeed * 60);
            if (elapseTime < 1) {
                elapseTime = 1;
            }
            currentTime += elapseTime;
            if (currentTime > 1439)
                currentTime -= 1440;
            newArrive = currentTime;
            currentTime += stop->getDuration();
            if (currentTime > 1439)
                currentTime -= 1440;
            newDepart = currentTime;

            currentDistance = station->getDistance();
            currentSpeed = (stop->getNextSpeed() > 0) ? stop->getNextSpeed() : defaultSpeed;
            currentSegment = station->getSegmentId();
            currentStationName = station->getStationName();

            if (validateTime(checkStart, checkDuration, newArrive) && validateTime(checkStart, checkDuration, newDepart)) {
                if (updateStops) {
                    stop->setArriveTime(newArrive);
                    stop->setDepartTime(newDepart);
                }
            } else {
                throw  IllegalArgumentException(QString::asprintf("%s~%d~%s", TIME_OUT_OF_RANGE, stop->getSeq(), train->getTrainName()));  // NOI18N
            }
        }
    }

    /**
     * Check to see if the supplied time is within the time range for the supplied schedule.
     * If the duration is 24 hours, then all times are valid.
     * Otherwise, we need to calculate the valid range, which can span midnight.
     * @param checkStart The schedule start hour.
     * @param checkDuration The schedule duration.
     * @param checkTime The time value to be check.
     * @return true if the time is valid.
     */
    /*public*/ bool TimeTableDataManager::validateTime(int checkStart, int checkDuration, int checkTime) {
        if (checkDuration == 24 && checkTime < 1440) {
            return true;
        }

        bool dayWrap;
        int lowLimit;
        int highLimit;

        if (checkStart + checkDuration > 24) {
            dayWrap = true;
            lowLimit = checkStart * 60;
            highLimit = ((checkStart + checkDuration - 24) * 60) - 1;
        } else {
            dayWrap = false;
            lowLimit = checkStart * 60;
            highLimit = ((checkStart + checkDuration) * 60) - 1;
        }

        if (dayWrap) {
            if (checkTime < 1440 && (checkTime >= lowLimit || checkTime <= highLimit)) {
                return true;
            }
        } else {
            if (checkTime < 1440 && (checkTime >= lowLimit && checkTime <= highLimit)) {
                return true;
            }
        }
        return false;
    }


    /*private*/ /*static*/ /*final*/ Logger* TimeTableDataManager::log = LoggerFactory::getLogger("TimeTableDataManager");
}
