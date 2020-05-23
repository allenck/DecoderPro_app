#include "station.h"
#include "timetabledatamanager.h"

namespace TimeTable
{

/**
 * Define the content of a Station record.
 *
 * @author Dave Sand Copyright (C) 2018
 */
///*public*/ class Station {

    /**
     * Create a new station with default values.
     * @param segmentId The parent segment id.
     * @throws IllegalArgumentException STATION_ADD_FAIL
     */
    /*public*/ Station::Station(int segmentId,QObject *parent) : QObject(parent) {
        _dm = TimeTableDataManager::getDataManager();

        if (_dm->getSegment(segmentId) == nullptr) {
            throw IllegalArgumentException(TimeTableDataManager::STATION_ADD_FAIL);
        }
        _stationId = _dm->getNextId("Station");  // NOI18N
        _segmentId = segmentId;
        _dm->addStation(_stationId, this);
    }

    /*public*/ Station::Station(int stationId, int segmentId, QString stationName, double distance, bool doubleTrack, int sidings, int staging,QObject *parent) : QObject(parent) {
        _dm = TimeTableDataManager::getDataManager();

        _stationId = stationId;
        _segmentId = segmentId;
        setStationName(stationName);
        setDistance(distance);
        setDoubleTrack(doubleTrack);
        setSidings(sidings);
        setStaging(staging);
    }


    /*public*/ int Station::getStationId() {
        return _stationId;
    }

    /*public*/ int Station::getSegmentId() {
        return _segmentId;
    }

    /*public*/ QString Station::getStationName() {
        return _stationName;
    }

    /*public*/ void Station::setStationName(QString newName) {
        _stationName = newName;
    }

    /*public*/ double Station::getDistance() {
        return _distance;
    }

    /**
     * Set a new distance.
     * @param newDistance The value to be used.
     * @throws IllegalArgumentException (DISTANCE_LT_0) if the value is less than 0.0.
     */
    /*public*/ void Station::setDistance(double newDistance) {
        if (newDistance < 0) {
            throw  IllegalArgumentException(TimeTableDataManager::DISTANCE_LT_0);
        }
        double oldDistance = _distance;
        _distance = newDistance;

        try {
            int layoutId = _dm->getSegment(getSegmentId())->getLayoutId();
            _dm->calculateLayoutTrains(layoutId, false);
            _dm->calculateLayoutTrains(layoutId, true);
        } catch (IllegalArgumentException ex) {
            _distance = oldDistance;  // Roll back distance change
            throw ex;
        }
    }

    /*public*/ bool Station::getDoubleTrack() {
        return _doubleTrack;
    }

    /*public*/ void Station::setDoubleTrack(bool newDoubleTrack) {
        _doubleTrack = newDoubleTrack;
    }

    /*public*/ int Station::getSidings() {
        return _sidings;
    }

    /**
     * Set a new siding count.
     * @param newSidings The value to be used.
     * @throws IllegalArgumentException (SIDINGS_LT_0) if the value is less than 0.
     */
    /*public*/ void Station::setSidings(int newSidings) {
        if (newSidings < 0) {
            throw  IllegalArgumentException(TimeTableDataManager::SIDINGS_LT_0);
        }
        _sidings = newSidings;
    }

    /*public*/ int Station::getStaging() {
        return _staging;
    }

    /**
     * Set a new staging track count.
     * @param newStaging The value to be used.
     * @throws IllegalArgumentException (STAGING_LT_0, STAGING_IN_USE) if the value is
     * less than 0 or a staging track is referenced by a train stop.
     */
    /*public*/ void Station::setStaging(int newStaging) {
        if (newStaging < 0) {
            throw  IllegalArgumentException(TimeTableDataManager::STAGING_LT_0);
        }
        for (Stop* stop : _dm->getStops(0, getStationId(), false)) {
            if (stop->getStagingTrack() > newStaging) {
                throw  IllegalArgumentException(TimeTableDataManager::STAGING_IN_USE);
            }
        }
        _staging = newStaging;
    }

    //@Override
    /*public*/ QString Station::toString() {
        return _stationName;
    }
}
