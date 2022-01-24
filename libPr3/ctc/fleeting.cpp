#include "fleeting.h"

/*
 *  @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
//package jmri.jmrit.ctc;

//import jmri.Sensor;

///*public*/ class Fleeting {

    /**
     * Class to manage the Fleeting sensor (if defined).  Provides reasonable
     * return values if none defined.
     *
     * @param fleetingToggleInternalSensor  The defined internal fleeting sensor name (ex: "IS:FLEETING")
     * @param defaultFleetingEnabled        The users choice as to whether fleeting is initially enabled or not.
     */
    /*public*/ Fleeting::Fleeting (NBHSensor* fleetingToggleInternalSensor, bool defaultFleetingEnabled, QObject *parent) : QObject(parent) {
        _mFleetingToggleInternalSensor = fleetingToggleInternalSensor;
        _mDefaultFleetingEnabled = defaultFleetingEnabled;
        _mFleetingToggleInternalSensor->setKnownState(_mDefaultFleetingEnabled ? Sensor::ACTIVE : Sensor::INACTIVE);
    }


    /**
     * Stub routine for completeness, we can be consistent in higher level code with this defined (even if it does nothing).
     */
    /*public*/ void Fleeting::removeAllListeners() {}   // None done.

    /**
     * Routine you can call to find out if fleeting is enabled.  Provides reasonable defaults if things don't exist.
     * @return True if fleeting is enabled, else false.
     */
    /*public*/ bool Fleeting::isFleetingEnabled() {
        if (_mFleetingToggleInternalSensor->valid()) return _mFleetingToggleInternalSensor->getKnownState() == Sensor::ACTIVE;
        return _mDefaultFleetingEnabled;
    }
