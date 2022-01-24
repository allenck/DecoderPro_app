#include "ttschedule.h"

/**
 * Define the content of a Schedule record.
 *
 * @author Dave Sand Copyright (C) 2018
 */
///*public*/ class Schedule {
namespace TimeTable
{
    /**
     * Create a new schedule with default values.
     * @param layoutId The parent layout id.
     * @throws IllegalArgumentException SCHEDULE_ADD_FAIL
     */
    /*public*/ TTSchedule::TTSchedule(int layoutId, QObject *parent) : QObject(parent) {
        if (_dm->getLayout(layoutId) == nullptr) {
            throw  IllegalArgumentException(TimeTableDataManager::SCHEDULE_ADD_FAIL);
        }
        _scheduleId = _dm->getNextId("Schedule");  // NOI18N
        _layoutId = layoutId;
        _dm->addSchedule(_scheduleId, this);
    }

    /*public*/ TTSchedule::TTSchedule(int scheduleId, int layoutId, QString scheduleName, QString effDate, int startHour, int duration, QObject *parent) : QObject(parent) {
        _scheduleId = scheduleId;
        _layoutId = layoutId;
        setScheduleName(scheduleName);
        setEffDate(effDate);
        setStartHour(startHour);
        setDuration(duration);
    }


    /*public*/ int TTSchedule::getScheduleId() {
        return _scheduleId;
    }

    /*public*/ int TTSchedule::getLayoutId() {
        return _layoutId;
    }

    /*public*/ QString TTSchedule::getScheduleName() {
        return _scheduleName;
    }

    /*public*/ void TTSchedule::setScheduleName(QString newName) {
        _scheduleName = newName;
    }

    /*public*/ QString TTSchedule::getEffDate() {
        return _effDate;
    }

    /*public*/ void TTSchedule::setEffDate(QString newDate) {
        _effDate = newDate;
    }

    /*public*/ int TTSchedule::getStartHour() {
        return _startHour;
    }

    /**
     * Set the start hour, 0 - 23.
     * @param newStartHour The start hour in the range of 0 to 23.
     * @throws IllegalArgumentException (START_HOUR_RANGE).
     */
    /*public*/ void TTSchedule::setStartHour(int newStartHour) {
        if (newStartHour < 0 || newStartHour > 23) {
            throw  IllegalArgumentException(TimeTableDataManager::START_HOUR_RANGE);
        }
        int oldStartHour = _startHour;
        _startHour = newStartHour;

        try {
            _dm->calculateScheduleTrains(getScheduleId(), false);
            _dm->calculateScheduleTrains(getScheduleId(), true);
        } catch (IllegalArgumentException* ex) {
            _startHour = oldStartHour;  // Roll back start hour change
            throw ex;
        }
    }

    /*public*/ int TTSchedule::getDuration() {
        return _duration;
    }

    /**
     * Set the duration, 1 - 24 hours.
     * @param newDuration The duration in the range of 1 to 24.
     * @throws IllegalArgumentException (DURATION_RANGE).
     */
    /*public*/ void TTSchedule::setDuration(int newDuration) {
        if (newDuration < 1 || newDuration > 24) {
            throw new IllegalArgumentException(TimeTableDataManager::DURATION_RANGE);
        }
        int oldDuration = _duration;
        _duration = newDuration;

        try {
            _dm->calculateScheduleTrains(getScheduleId(), false);
            _dm->calculateScheduleTrains(getScheduleId(), true);
        } catch (IllegalArgumentException* ex) {
            _duration = oldDuration;  // Roll back duration change
            throw ex;
        }
    }

    //@Override
    /*public*/ QString TTSchedule::toString() {
        return _scheduleName;
    }
}
