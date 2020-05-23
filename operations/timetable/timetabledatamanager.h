#ifndef TIMETABLEDATAMANAGER_H
#define TIMETABLEDATAMANAGER_H

#include <QObject>
#include "layout.h"
#include "traintype.h"
#include "segment.h"
#include "station.h"
#include "stop.h"

class Logger;
namespace TimeTable
{
class SegmentStation;
class TTTrain;
class TTSchedule;
class TimeTableDataManager : public QObject
{
 Q_OBJECT
public:
 /*public*/ TimeTableDataManager(bool loadData, QObject *parent=nullptr);
 /*public*/ static TimeTableDataManager* getDataManager();
 // Exception key words
 /*public*/ static /*final*/ QString CLOCK_LT_1;// = "FastClockLt1";    // NOI18N
 /*public*/ static /*final*/ QString DURATION_LT_0;// = "DurationLt0";    // NOI18N
 /*public*/ static /*final*/ QString THROTTLES_LT_0;// = "ThrottlesLt0";    // NOI18N
 /*public*/ static /*final*/ QString THROTTLES_IN_USE;// = "ThrottlesInUse";    // NOI18N
 /*public*/ static /*final*/ QString SCALE_NF;// = "ScaleNotFound";    // NOI18N
 /*public*/ static /*final*/ QString TIME_OUT_OF_RANGE;// = "TimeOutOfRange";    // NOI18N
 /*public*/ static /*final*/ QString SEGMENT_CHANGE_ERROR;// = "SegmentChangeError";    // NOI18N
 /*public*/ static /*final*/ QString DISTANCE_LT_0;// = "DistanceLt0";    // NOI18N
 /*public*/ static /*final*/ QString SIDINGS_LT_0;// = "SidingsLt0";    // NOI18N
 /*public*/ static /*final*/ QString STAGING_LT_0;// = "StagingLt0";    // NOI18N
 /*public*/ static /*final*/ QString STAGING_IN_USE;// = "StagingInUse";    // NOI18N
 /*public*/ static /*final*/ QString START_HOUR_RANGE;// = "StartHourRange";    // NOI18N
 /*public*/ static /*final*/ QString DURATION_RANGE;// = "DurationRange";    // NOI18N
 /*public*/ static /*final*/ QString DEFAULT_SPEED_LT_0;// = "DefaultSpeedLt0";    // NOI18N
 /*public*/ static /*final*/ QString START_TIME_FORMAT;// = "StartTimeFormat";    // NOI18N
 /*public*/ static /*final*/ QString START_TIME_RANGE;// = "StartTimeRange";    // NOI18N
 /*public*/ static /*final*/ QString THROTTLE_RANGE;// = "ThrottleRange";    // NOI18N
 /*public*/ static /*final*/ QString STAGING_RANGE;// = "StagingRange";    // NOI18N
 /*public*/ static /*final*/ QString STOP_DURATION_LT_0;// = "StopDurationLt0";    // NOI18N
 /*public*/ static /*final*/ QString NEXT_SPEED_LT_0;// = "NextSpeedLt0";    // NOI18N
 /*public*/ static /*final*/ QString LAYOUT_HAS_CHILDREN;// = "LayoutHasChildren";    // NOI18N
 /*public*/ static /*final*/ QString TYPE_HAS_REFERENCE;// = "TypeHasReference";    // NOI18N
 /*public*/ static /*final*/ QString SEGMENT_HAS_CHILDREN;// = "SegmentHaSChildren";    // NOI18N
 /*public*/ static /*final*/ QString STATION_HAS_REFERENCE;// = "StationHasReference";    // NOI18N
 /*public*/ static /*final*/ QString SCHEDULE_HAS_CHILDREN;// = "ScheduleHasChildren";    // NOI18N
 /*public*/ static /*final*/ QString TRAIN_HAS_CHILDREN;// = "TrainHasChildren";    // NOI18N
 /*public*/ static /*final*/ QString TYPE_ADD_FAIL;// = "TypeAddFail";    // NOI18N
 /*public*/ static /*final*/ QString SEGMENT_ADD_FAIL;// = "SegmentAddFail";    // NOI18N
 /*public*/ static /*final*/ QString STATION_ADD_FAIL;// = "StationAddFail";    // NOI18N
 /*public*/ static /*final*/ QString SCHEDULE_ADD_FAIL;// = "ScheduleAddFail";    // NOI18N
 /*public*/ static /*final*/ QString TRAIN_ADD_FAIL;// = "TrainAddFail";    // NOI18N
 /*public*/ static /*final*/ QString STOP_ADD_FAIL;// = "StopAddFail";    // NOI18N
 /*public*/ void setLockCalculate(bool lock);
 /*public*/ void addLayout(int id, Layout* newLayout);
 /*public*/ void addTrainType(int id, TrainType* newTrainType);
 /*public*/ void addSegment(int id, Segment* newSegment);
 /*public*/ void addStation(int id, Station* newStation);
 /*public*/ void addSchedule(int id, TimeTable::TTSchedule* newSchedule);
 /*public*/ void addTrain(int id, TTTrain* newTrain);
 /*public*/ void addStop(int id, Stop* newStop);
 /*public*/ void deleteLayout(int id);
 /*public*/ void deleteTrainType(int id);
 /*public*/ void deleteSegment(int id);
 /*public*/ void deleteStation(int id);
 /*public*/ void deleteSchedule(int id);
 /*public*/ void deleteTrain(int id);
 /*public*/ void deleteStop(int id);
 /*public*/ Layout* getLayout(int id);
 /*public*/ TrainType* getTrainType(int id);
 /*public*/ Segment* getSegment(int id);
 /*public*/ Station* getStation(int id);
 /*public*/ TimeTable::TTSchedule* getSchedule(int id);
 /*public*/ TTTrain* getTrain(int id);
 /*public*/ Stop* getStop(int id);
 /*public*/ int getNextId(QString type);
 /*public*/ QList<Layout*> getLayouts(bool sort);
 /*public*/ QList<TrainType*> getTrainTypes(int fKeyLayout, bool sort) ;
 /*public*/ QList<Segment*> getSegments(int fKeyLayout, bool sort);
 /*public*/ QList<Station*> getStations(int fKeySegment, bool sort);
 /*public*/ QList<TimeTable::TTSchedule*> getSchedules(int fKeyLayout, bool sort);
 /*public*/ QList<TTTrain*> getTrains(int fKeySchedule, int fKeyType, bool sort);
 /*public*/ QList<Stop*> getStops(int fKeyTrain, int fKeyStation, bool sort);
 /*public*/ Layout* getLayoutForStop(int stopId);
 /*public*/ QList<SegmentStation*> getSegmentStations(int layoutId);
 /*public*/ void calculateTrain(int trainId, bool updateStops);
 /*public*/ bool validateTime(int checkStart, int checkDuration, int checkTime);
signals:

public slots:

private:
 static Logger* log;

 /*private*/ QMap<int, Layout*> _layoutMap = QMap<int, Layout*>();
 /*private*/ QMap<int, TrainType*> _trainTypeMap = QMap<int, TrainType*>();
 /*private*/ QMap<int, Segment*> _segmentMap = QMap<int, Segment*>();
 /*private*/ QMap<int, Station*> _stationMap = QMap<int, Station*>();
 /*private*/ QMap<int, TimeTable::TTSchedule*> _scheduleMap = QMap<int, TimeTable::TTSchedule*>();
 /*private*/ QMap<int, TTTrain*> _trainMap = QMap<int, TTTrain*>();
 /*private*/ QMap<int, Stop*> _stopMap = QMap<int, Stop*>();
 /*private*/ QList<SegmentStation*> _segmentStations = QList<SegmentStation*>();

 bool _lockCalculate = false;
 void calculateLayoutTrains(int layoutId, bool updateStops);
 void calculateScheduleTrains(int scheduleId, bool updateStops);

 friend class TTSchedule;
 friend class Layout;
 friend class Station;
};

/**
 * Internal class that provides a combined segment and station view.
 */
/*public*/ class SegmentStation : public QObject
{
 Q_OBJECT
    /*private*/ int _segmentId;
    /*private*/ int _stationId;
 TimeTableDataManager* dm;
public:
    /*public*/ SegmentStation(int segmentId, int stationId, TimeTableDataManager* dm) {
        _segmentId = segmentId;
        _stationId = stationId;
        this->dm = dm;
    }

    /*public*/ int getSegmentId() {
        return _segmentId;
    }

    /*public*/ int getStationId() {
        return _stationId;
    }

    //@Override
    /*public*/ QString toString() {
        return tr("%1 : %2").arg(dm->getSegment(_segmentId)->getSegmentName()).arg(dm->getStation(_stationId)->getStationName());  // NOI18N
    }
};
}

#endif // TIMETABLEDATAMANAGER_H
