#include "transmitter.h"
#include "instancemanager.h"
#include "throttlemanager.h"

using namespace RPS;
/**
 * Represents a RPS transmitter, generally a locomotive.
 * <p>
 * The "ID" is used to identify this transmitter in RPS. The "rosterName" is the
 * name (ID) of the roster entry this was originally created from.
 *
 * @author	Bob Jacobsen Copyright (C) 2006, 2008
 */
///*public*/ class Transmitter implements ThrottleListener {

Transmitter::Transmitter(QString id, bool polled, int address, bool longAddress, QObject*parent) : QObject(parent){
 lastMeasurement = NULL;
 needReqThrottle = true;

    setID(id);
    setPolled(polled);
    setAddress(address);
    setLongAddress(longAddress);
}

/*public*/ QString Transmitter::getID() {
    return id;
}

/*public*/ void Transmitter::setID(QString id) {
    this->id = id;
}

/*public*/ QString Transmitter::getRosterName() {
    return rosterName;
}

/*public*/ void Transmitter::setRosterName(QString rosterName) {
    this->rosterName = rosterName;
}

/*public*/ bool Transmitter::isLongAddress() {
    return longAddress;
}

/*public*/ void Transmitter::setLongAddress(bool longAddress) {
    this->longAddress = longAddress;
}

/*public*/ int Transmitter::getAddress() {
    return address;
}

/*public*/ void Transmitter::setAddress(int address) {
    this->address = address;
}

/*public*/ bool Transmitter::isPolled() {
    return polled;
}

/*public*/ void Transmitter::setPolled(bool polled) {
    this->polled = polled;
}


/*public*/ void Transmitter::setLastMeasurement(Measurement* last) {
    lastMeasurement = last;
}

/*public*/ Measurement* Transmitter::getLastMeasurement() {
    return lastMeasurement;
}


DccThrottle* Transmitter::getThrottle() {
    return throttle;
}

bool Transmitter::checkInit() {
    if (throttle != NULL) {
        return true;
    }
    if (!needReqThrottle) {
        return false;
    }
    // request throttle
    InstanceManager::throttleManagerInstance()->requestThrottle(address, longAddress, (ThrottleListener*)this);
    return false;
}

//@Override
/*public*/ void Transmitter::notifyThrottleFound(DccThrottle* t) {
    needReqThrottle = false;
    throttle = t;
}

//@Override
/*public*/ void Transmitter::notifyFailedThrottleRequest(DccLocoAddress* /*address*/, QString /*reason*/) {
}

