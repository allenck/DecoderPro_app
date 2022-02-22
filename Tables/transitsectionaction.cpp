#include "transitsectionaction.h"
#include "transitsection.h"
#include "sensor.h"

/**
 * This class holds information and options for a Action to be applied when an
 * automated train enters, exits, or is inside of a Section in a Transit.
 * <P>
 * A TransitSection holds specified TrainsitSectionActions. A TransitSection may
 * have as many TransitSectionActions as appropriate. Each TransitSectionAction
 * belongs to one and only one TransitSection.
 * <P>
 * TransitSectionActions are specified in two parts: 1. The "When" part
 * specifies when after the automated train enters the Section the action is to
 * be initiated. Optionally, each "when" may be delayed by a specified time (in
 * milliseconds). 2. The "What" part specified what action is to occur.
 * <P>
 * TransitSectionActions are created and editted in the Transit Table, when
 * Transits are defined.
 * <P>
 * This class provides support for SENSORACTIVE and SENSORINACTIVE "when"'s.
 * <P>
 * This file is part of JMRI.
 * <P>
 * JMRI is open source software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published by the
 * Free Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author	Dave Duchamp Copyright (C) 2009, 2010
 */
///*public*/ class TransitSectionAction {


/**
 * Main constructor method
 */
/*public*/ TransitSectionAction::TransitSectionAction(int when, int what) : QObject(){
    common();
    mWhen = when;
    mWhat = what;
}

/**
 * Convenience constructor
 */
/*public*/ TransitSectionAction::TransitSectionAction(int when, int what, int dataWhen, int dataWhat1, int dataWhat2, QString sWhen, QString sWhat) : QObject(){
    common();
    mWhen = when;
    mWhat = what;
    mDataWhen = dataWhen;
    mDataWhat1 = dataWhat1;
    mDataWhat2 = dataWhat2;
    mStringWhen = sWhen;
    mStringWhat = sWhat;
}

void TransitSectionAction::common()
{
 // instance variables
  mWhen = 0;
  mWhat = 0;
  mDataWhen = -1;	// negative number signified no data
  mDataWhat1 = -1;    // negative number signified no data
  mDataWhat2 = -1;    // negative number signified no data
  mStringWhen = "";
  mStringWhat = "";
  /**
   * operational instance variables - flags and data for executing the action
   * (see jmri.jmrit.dispatcher.AutoActiveTrain.java)
   */
  _waitingThread = NULL;
  _waitingForSectionExit = false;
  _targetTransitSection = NULL;
  _waitingForBlock = false;
  _waitingForSensor = false;
  _triggerSensor = NULL;
  _sensorListener = NULL;
}

/**
 * Access methods
 */
/*public*/ int TransitSectionAction::getWhenCode() {
    return mWhen;
}

/*public*/ void TransitSectionAction::setWhenCode(int n) {
    mWhen = n;
}

/*public*/ int TransitSectionAction::getWhatCode() {
    return mWhat;
}

/*public*/ void TransitSectionAction::setWhatCode(int n) {
    mWhat = n;
}

/*public*/ int TransitSectionAction::getDataWhen() {
    return mDataWhen;
}

/*public*/ void TransitSectionAction::setDataWhen(int n) {
    mDataWhen = n;
}

/*public*/ int TransitSectionAction::getDataWhat1() {
    return mDataWhat1;
}

/*public*/ void TransitSectionAction::setDataWhat1(int n) {
    mDataWhat1 = n;
}

/*public*/ int TransitSectionAction::getDataWhat2() {
    return mDataWhat2;
}

/*public*/ void TransitSectionAction::setDataWhat2(int n) {
    mDataWhat2 = n;
}

/*public*/ QString TransitSectionAction::getStringWhen() {
    return mStringWhen;
}

/*public*/ void TransitSectionAction::setStringWhen(QString s) {
    mStringWhen = s;
}

/*public*/ QString TransitSectionAction::getStringWhat() {
    return mStringWhat;
}

/*public*/ void TransitSectionAction::setStringWhat(QString s) {
    mStringWhat = s;
}


/**
 * initialize all operational instance variables (not saved between runs)
 */
/*public*/ void TransitSectionAction::initialize() {
    _waitingThread = NULL;
    _waitingForSectionExit = false;
    _targetTransitSection = NULL;
    _waitingForBlock = false;
    _waitingForSensor = false;
    _triggerSensor = NULL;
    _sensorListener = NULL;
}

/**
 * Operational access methods
 */
/*public*/ QThread* TransitSectionAction::getWaitingThread() {
    return _waitingThread;
}

/*public*/ void TransitSectionAction::setWaitingThread(QThread* t) {
    _waitingThread = t;
}

/*public*/ bool TransitSectionAction::getWaitingForSectionExit() {
    return _waitingForSectionExit;
}

/*public*/ void TransitSectionAction::setWaitingForSectionExit(bool w) {
    _waitingForSectionExit = w;
}

/*public*/ TransitSection* TransitSectionAction::getTargetTransitSection() {
    return _targetTransitSection;
}

/*public*/ void TransitSectionAction::setTargetTransitSection(TransitSection* ts) {
    _targetTransitSection = ts;
}

/*public*/ bool TransitSectionAction::getWaitingForBlock() {
    return _waitingForBlock;
}

/*public*/ void TransitSectionAction::setWaitingForBlock(bool w) {
    _waitingForBlock = w;
}

/*public*/ bool TransitSectionAction::getWaitingForSensor() {
    return _waitingForSensor;
}

/*public*/ void TransitSectionAction::setWaitingForSensor(bool w) {
    _waitingForSensor = w;
}

/*public*/ Sensor* TransitSectionAction::getTriggerSensor() {
    return _triggerSensor;
}

/*public*/ void TransitSectionAction::setTriggerSensor(Sensor* s) {
    _triggerSensor = s;
}

/*public*/ PropertyChangeListener* TransitSectionAction::getSensorListener() {
    return _sensorListener;
}

/*public*/ void TransitSectionAction::setSensorListener(PropertyChangeListener* l) {
    _sensorListener = l;
}

/*public*/ void TransitSectionAction::disposeSensorListener() {
    // if this object has registered a listener, dispose of it
    if (_sensorListener != NULL) {
        _triggerSensor->removePropertyChangeListener(_sensorListener);
//        disconnect(_triggerSensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), _sensorListener->self(), SLOT(propertyChange(PropertyChangeEvent*)));
        _sensorListener = NULL;
        _waitingForSensor = false;
    }
}

/*public*/ void TransitSectionAction::dispose() {
    disposeSensorListener();
}

