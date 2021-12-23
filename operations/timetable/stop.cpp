#include "stop.h"
#include "timetabledatamanager.h"

namespace TimeTable
{

/**
 * Define the content of a Stop record.
 *
 * @author Dave Sand Copyright (C) 2018
 */
// /*public*/ class Stop {

    /**
     * Create a new stop with default values.
     * @param trainId The parent train id.
     * @param seq The next stop sequence number.
     * @throws IllegalArgumentException STOP_ADD_FAIL
     */
    /*public*/ Stop::Stop(int trainId, int seq, QObject* parent) : QObject(parent) {
        _dm = TimeTableDataManager::getDataManager();

        if (_dm->getTrain(trainId) == nullptr) {
            throw  IllegalArgumentException(TimeTableDataManager::STOP_ADD_FAIL);
        }
        _stopId = _dm->getNextId("Stop");  // NOI18N
        _trainId = trainId;
        _seq = seq;
        _dm->addStop(_stopId, this);
    }

    /*public*/ Stop::Stop(int stopId, int trainId, int stationId, int seq, int duration,
            int nextSpeed, int arriveTime, int departTime, int stagingTrack, QString stopNotes, QObject* parent) : QObject(parent) {
        _dm = TimeTableDataManager::getDataManager();

        _stopId = stopId;
        _trainId = trainId;
        _stationId = stationId;
        _seq = seq;
        setDuration(duration);
        setNextSpeed(nextSpeed);
        setArriveTime(arriveTime);
        setDepartTime(departTime);
        setStagingTrack(stagingTrack);
        setStopNotes(stopNotes);
    }

    /*public*/ int Stop::getStopId() {
        return _stopId;
    }

    /*public*/ int Stop::getTrainId() {
        return _trainId;
    }

    /*public*/ int Stop::getStationId() {
        return _stationId;
    }

    /*public*/ void Stop::setStationId(int newStationId) {
        int oldDStationId = _stationId;
        _stationId = newStationId;

        try {
            _dm->calculateTrain(_trainId, false);
            _dm->calculateTrain(_trainId, true);
        } catch (IllegalArgumentException* ex) {
            _stationId = oldDStationId;  // Roll back station change
            throw ex;
        }
    }

    /*public*/ int Stop::getSeq() {
        return _seq;
    }

    /*public*/ void Stop::setSeq(int newSeq) {
        _seq = newSeq;
    }

    /*public*/ int Stop::getDuration() {
        return _duration;
    }

    /*public*/ void Stop::setDuration(int newDuration) {
        if (newDuration < 0) {
            throw  IllegalArgumentException(TimeTableDataManager::STOP_DURATION_LT_0);
        }
        int oldDuration = _duration;
        _duration = newDuration;

        try {
            _dm->calculateTrain(_trainId, false);
            _dm->calculateTrain(_trainId, true);
        } catch (IllegalArgumentException* ex) {
            _duration = oldDuration;  // Roll back duration change
            throw ex;
        }
    }

    /*public*/ int Stop::getNextSpeed() {
        return _nextSpeed;
    }

    /*public*/ void Stop::setNextSpeed(int newNextSpeed) {
        if (newNextSpeed < 0) {
            throw  IllegalArgumentException(TimeTableDataManager::NEXT_SPEED_LT_0);
        }
        int oldNextSpeed = _nextSpeed;
        _nextSpeed = newNextSpeed;

        try {
            _dm->calculateTrain(_trainId, false);
            _dm->calculateTrain(_trainId, true);
        } catch (IllegalArgumentException* ex) {
            _nextSpeed = oldNextSpeed;  // Roll back next speed change
            throw ex;
        }
    }

    /*public*/ int Stop::getArriveTime() {
        return _arriveTime;
    }

    /*public*/ void Stop::setArriveTime(int newArriveTime) {
        _arriveTime = newArriveTime;
    }

    /*public*/ int Stop::getDepartTime() {
        return _departTime;
    }

    /*public*/ void Stop::setDepartTime(int newDepartTime) {
        _departTime = newDepartTime;
    }

    /*public*/ int Stop::getStagingTrack() {
        return _stagingTrack;
    }

    /*public*/ void Stop::setStagingTrack(int newStagingTrack) {
        Station* station = _dm->getStation(_stationId);
        if (newStagingTrack < 0 || newStagingTrack > station->getStaging()) {
            throw new IllegalArgumentException(TimeTableDataManager::STAGING_RANGE);
        }

        _stagingTrack = newStagingTrack;
    }

    /*public*/ QString Stop::getStopNotes() {
        return _stopNotes;
    }

    /*public*/ void Stop::setStopNotes(QString newNotes) {
        _stopNotes = newNotes;
    }

    //@Override
    /*public*/ QString Stop::toString() {
        TimeTableDataManager* dataMgr = TimeTableDataManager::getDataManager();
        Station* station = dataMgr->getStation(_stationId);
        return _seq + " :: " + station->getStationName();
    }
}
