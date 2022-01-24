#include "trafficlockinginfo.h"

/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 *
 * Just a packet of fields:
 *
 */
///*public*/ class TrafficLockingInfo {

    /*public*/ TrafficLockingInfo::TrafficLockingInfo(bool returnStatus, QObject* parent) : QObject(parent){
        _mReturnStatus = returnStatus;      // Whatever the user wants.
        _mLockedRoute = nullptr;               // Assume none allocated.
    }
