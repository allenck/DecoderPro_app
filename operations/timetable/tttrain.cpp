#include "tttrain.h"
#include "timetabledatamanager.h"
#include "ttschedule.h"

/**
 * Define the content of a Train record.
 *
 * @author Dave Sand Copyright (C) 2018
 */
// /*public*/ class Train {
namespace TimeTable
{
    /**
     * Create a new train with default values.
     * @param scheduleId The parent schedule id.
     * @throws IllegalArgumentException TRAIN_ADD_FAIL
     */
    /*public*/ TTTrain::TTTrain(int scheduleId,QObject *parent) : QObject(parent) {
     _dm = TimeTableDataManager::getDataManager();
        if (_dm->getSchedule(scheduleId) == nullptr) {
            throw new IllegalArgumentException(TimeTableDataManager::TRAIN_ADD_FAIL);
        }
        _trainId = _dm->getNextId("Train");  // NOI18N
        _scheduleId = scheduleId;
        _dm->addTrain(_trainId, this);
    }

    /*public*/ TTTrain::TTTrain(int trainId, int scheduleId, int typeId, QString trainName, QString trainDesc,
                int defaultSpeed, int startTime, int throttle, int routeDuration, QString trainNotes, QObject *parent) : QObject(parent) {
      _dm = TimeTableDataManager::getDataManager();
        _trainId = trainId;
        _scheduleId = scheduleId;
        setTypeId(typeId);
        setTrainName(trainName);
        setTrainDesc(trainDesc);
        setDefaultSpeed(defaultSpeed);
        setStartTime(startTime);
        setThrottle(throttle);
        setRouteDuration(routeDuration);
        setTrainNotes(trainNotes);
    }


    /*public*/ int TTTrain::getTrainId() {
        return _trainId;
    }

    /*public*/ int TTTrain::getScheduleId() {
        return _scheduleId;
    }

    /*public*/ int TTTrain::getTypeId() {
        return _typeId;
    }

    /*public*/ void TTTrain::setTypeId(int newType) {
        _typeId = newType;
    }

    /*public*/ QString TTTrain::getTrainName() {
        return _trainName;
    }

    /*public*/ void TTTrain::setTrainName(QString newName) {
        _trainName = newName;
    }

    /*public*/ QString TTTrain::getTrainDesc() {
        return _trainDesc;
    }

    /*public*/ void TTTrain::setTrainDesc(QString newDesc) {
        _trainDesc = newDesc;
    }

    /*public*/ int TTTrain::getDefaultSpeed() {
        return _defaultSpeed;
    }

    /*public*/ void TTTrain::setDefaultSpeed(int newSpeed) {
        if (newSpeed < 0) {
            throw  IllegalArgumentException(TimeTableDataManager::DEFAULT_SPEED_LT_0);
        }
        int oldSpeed = _defaultSpeed;
        _defaultSpeed = newSpeed;

        try {
            _dm->calculateTrain(_trainId, false);
            _dm->calculateTrain(_trainId, true);
        } catch (IllegalArgumentException* ex) {
            _defaultSpeed = oldSpeed;  // Roll back default speed change
            throw ex;
        }
    }

    /*public*/ int TTTrain::getStartTime() {
        return _startTime;
    }

    /*public*/ void TTTrain::setStartTime(int newStartTime) {
        TTSchedule* schedule = _dm->getSchedule(_scheduleId);
        if (!_dm->validateTime(schedule->getStartHour(), schedule->getDuration(), newStartTime)) {
            throw  IllegalArgumentException(QString::asprintf("%s~%d~%d",  // NOI18N
                    TimeTableDataManager::START_TIME_RANGE, schedule->getStartHour(), schedule->getStartHour() + schedule->getDuration()));
        }
        int oldStartTime = _startTime;
        _startTime = newStartTime;

        try {
            _dm->calculateTrain(_trainId, false);
            _dm->calculateTrain(_trainId, true);
        } catch (IllegalArgumentException* ex) {
            _startTime = oldStartTime;  // Roll back start time change
            throw ex;
        }
    }

    /*public*/ int TTTrain::getThrottle() {
        return _throttle;
    }

    /*public*/ void TTTrain::setThrottle(int newThrottle) {
        Layout* layout = _dm->getLayout(_dm->getSchedule(_scheduleId)->getLayoutId());
        if (newThrottle < 0 || newThrottle > layout->getThrottles()) {
            throw  IllegalArgumentException(TimeTableDataManager::THROTTLE_RANGE);
        }

        _throttle = newThrottle;
    }

    /*public*/ int TTTrain::getRouteDuration() {
        return _routeDuration;
    }

    /*public*/ void TTTrain::setRouteDuration(int newRouteDuration) {
        _routeDuration = newRouteDuration;
    }

    /*public*/ QString TTTrain::getTrainNotes() {
        return _trainNotes;
    }

    /*public*/ void TTTrain::setTrainNotes(QString newNotes) {
        _trainNotes = newNotes;
    }

    //@Override
    /*public*/ QString TTTrain::toString() {
        return _trainName;
    }
}
