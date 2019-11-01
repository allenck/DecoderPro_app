#include "autotrainaction.h"
#include "autoactivetrain.h"
#include "transitsection.h"
#include "transitsectionaction.h"
#include "activetrain.h"
#include "instancemanager.h"
#include "sensor.h"
#include "proxysensormanager.h"
#include "logger.h"
#include "allocatedsection.h"

//AutoTrainAction::AutoTrainAction(QObject *parent) : QObject(parent)
//{

//}
/**
 * This class sets up and executes TransitSectionAction's specified for Sections
 * traversed by one automatically running train. It ia an extension to
 * AutoActiveTrain that handles special actions while its train is running
 * automatically.
 * <P>
 * This class is linked via it's parent AutoActiveTrain object.
 * <P>
 * When an AutoActiveTrain enters a Section, it passes the TransitSection of the
 * entered Section to this class.
 * <P>
 * Similarly when an AutoActiveTrain leaves a Section, it passes the
 * TransitSection of the just vacated Section to this class.
 * <P>
 *
 * This file is part of JMRI.
 * <P>
 * JMRI is open source software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published by the
 * Free Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * @author	Dave Duchamp Copyright (C) 2010-2011
 */
///*public*/ class AutoTrainAction {

/**
 * Main constructor method
 */
/*public*/ AutoTrainAction::AutoTrainAction(AutoActiveTrain* aat, QObject* parent) : QObject(parent) {
 log = new Logger("AutoTrainAction");
 // operational instance variables
 _autoActiveTrain = NULL;
 _activeTrain = NULL;
 _activeTransitSectionList;// = new QList<TransitSection>();
 _activeActionList = new QList<TransitSectionAction*>();
 // this method is called to listen to a Done Sensor if one was provided
 // if Status is WORKING, and sensor goes Active, Status is set to READY
 _doneSensor = NULL;
 _doneSensorListener = NULL;


 _autoActiveTrain = aat;
 _activeTrain = aat->getActiveTrain();
}
#if 0
static final ResourceBundle rb = ResourceBundle
        .getBundle("jmri.jmrit.dispatcher.DispatcherBundle");
#endif


// this method is called when an AutoActiveTrain enters a Section
/*protected*/ /*synchronized*/ void AutoTrainAction::addTransitSection(TransitSection* ts) {
    _activeTransitSectionList->append(ts);
    QList<TransitSectionAction*>* tsaList = ts->getTransitSectionActionList();
    // set up / execute Transit Section Actions if there are any
    if (tsaList->size() > 0) {
        for (int i = 0; i < tsaList->size(); i++) {
            TransitSectionAction* tsa = tsaList->at(i);
            // add to list if not already there
            bool found = false;
            for (int j = 0; j < _activeActionList->size(); j++) {
                if (_activeActionList->at(j) == tsa) {
                    found = true;
                }
            }
            if (!found) {
                _activeActionList->append(tsa);
                tsa->initialize();
            }
            switch (tsa->getWhenCode()) {
                case TransitSectionAction::ENTRY:
                    // on entry to Section - if here Section was entered
                    checkDelay(tsa);
                    break;
                case TransitSectionAction::EXIT:
                    // on exit from Section
                    tsa->setWaitingForSectionExit(true);
                    tsa->setTargetTransitSection(ts);
                    break;
                case TransitSectionAction::BLOCKENTRY:
                    // on entry to specified Block in the Section
                    tsa->setWaitingForBlock(true);
                    break;
                case TransitSectionAction::BLOCKEXIT:
                    // on exit from specified Block in the Section
                    tsa->setWaitingForBlock(true);
                    break;
                case TransitSectionAction::TRAINSTOP:
                // when train stops - monitor in separate thread
#if 0
                case TransitSectionAction::TRAINSTART:
                    // when train starts - monitor in separate thread
                    Runnable monTrain = new MonitorTrain(tsa);
                    Thread tMonTrain = new Thread(monTrain, "Monitor Train Transit Action " + _activeTrain.getDccAddress());
                    tsa->setWaitingThread(tMonTrain);
                    tMonTrain.start();
                    break;
                case TransitSectionAction::SENSORACTIVE:
                // when specified Sensor changes to Active
                case TransitSectionAction::SENSORINACTIVE:
                    // when specified Sensor changes to Inactive
                    if (!waitOnSensor(tsa)) {
                        // execute operation immediately -
                        //  no sensor found, or sensor already in requested state
                        executeAction(tsa);
                    } else {
                        tsa->setWaitingForSensor(true);
                    }
                    break;
#endif
                default:
                    break;
            }
        }
    }
}
#if 0
/**
 * Sets up waiting on Sensor before executing an action If Sensor does not
 * exist, or Sensor is already in requested state, returns false. If waiting
 * for Sensor to change, returns true.
 */
private boolean waitOnSensor(TransitSectionAction tsa) {
    if (tsa->getWaitingForSensor()) {
        return true;
    }
    Sensor s = InstanceManager.sensorManagerInstance().getSensor(tsa->getStringWhen());
    if (s == NULL) {
        log.error("Sensor with name - " + tsa->getStringWhen() + " - was not found.");
        return false;
    }
    int now = s.getKnownState();
    if (((now == Sensor.ACTIVE) && (tsa->getWhenCode() == TransitSectionAction::SENSORACTIVE))
            || ((now == Sensor.INACTIVE) && (tsa->getWhenCode() == TransitSectionAction::SENSORINACTIVE))) {
        // Sensor is already in the requested state, so execute action immediately
        return false;
    }
    // set up listener
    tsa->setTriggerSensor(s);
    tsa->setWaitingForSensor(true);
    final String sensorName = tsa->getStringWhen();
    java.beans.PropertyChangeListener sensorListener = NULL;
    s.addPropertyChangeListener(sensorListener
            = new java.beans.PropertyChangeListener() {
                @Override
                /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
                    if (e.getPropertyName() == ("KnownState")) {
                        handleSensorChange(sensorName);
                    }
                }
            });
    tsa->setSensorListener(sensorListener);
    return true;
}

/*public*/ void handleSensorChange(String sName) {
    // find waiting Transit Section Action
    for (int i = 0; i < _activeActionList.size(); i++) {
        if (_activeActionList.get(i).getWaitingForSensor()) {
            TransitSectionAction tsa = _activeActionList.get(i);
            if (tsa->getStringWhen() == (sName)) {
                // have the waiting action
                tsa->setWaitingForSensor(false);
                if (tsa->getSensorListener() != NULL) {
                    tsa->getTriggerSensor().removePropertyChangeListener(tsa->getSensorListener());
                    tsa->setSensorListener(NULL);
                }
                executeAction(tsa);
                return;
            }
        }
    }
}

// this method is called when the state of a Block in an Allocated Section changes
protected synchronized void handleBlockStateChange(AllocatedSection as, Block b) {
    // Ignore call if not waiting on Block state change
    for (int i = 0; i < _activeActionList.size(); i++) {
        if (_activeActionList.get(i).getWaitingForBlock()) {
            TransitSectionAction tsa = _activeActionList.get(i);
            Block target = InstanceManager.getDefault(jmri.BlockManager.class).getBlock(tsa->getStringWhen());
            if (b == target) {
                // waiting on state change for this block
                if (((b.getState() == Block.OCCUPIED) && (tsa->getWhenCode() == TransitSectionAction::BLOCKENTRY))
                        || ((b.getState() == Block.UNOCCUPIED) && (tsa->getWhenCode() == TransitSectionAction::BLOCKEXIT))) {
                    checkDelay(tsa);
                }
            }
        }
    }
}
#endif
// this method is called when an AutoActiveTrain exits a section
/*protected*/ /*synchronized*/ void AutoTrainAction::removeTransitSection(TransitSection* ts) {
    for (int i = _activeTransitSectionList->size() - 1; i >= 0; i--) {
        if (_activeTransitSectionList->at(i) == ts) {
            _activeTransitSectionList->removeAt(i);
        }
    }
    // perform any actions triggered by leaving Section
    for (int i = 0; i < _activeActionList->size(); i++) {
        if (_activeActionList->at(i)->getWaitingForSectionExit()
                && (_activeActionList->at(i)->getTargetTransitSection() == ts)) {
            // this action is waiting for this Section to exit
            checkDelay(_activeActionList->at(i));
        }
    }
}

// this method is called when an action has been completed
/*private*/ /*synchronized*/ void AutoTrainAction::completedAction(TransitSectionAction* tsa) {
    // action has been performed, clear, and delete it from the active list
    if (tsa->getWaitingForSensor()) {
        tsa->disposeSensorListener();
    }
    tsa->initialize();
    // remove from active list if not continuous running
    if (!_activeTrain->getResetWhenDone()) {
        for (int i = _activeActionList->size() - 1; i >= 0; i--) {
            if (_activeActionList->at(i) == tsa) {
                _activeActionList->removeAt(i);
                return;
            }
        }
    }
}

/**
 * This method is called to clear any actions that have not been completed
 */
/*protected*/ /*synchronized*/ void AutoTrainAction::clearRemainingActions() {
    for (int i = _activeActionList->size() - 1; i >= 0; i--) {
        TransitSectionAction* tsa = _activeActionList->at(i);
#if 0
        QThread* t = tsa->getWaitingThread();
        if (t != NULL) {
            // interrupting an Action thread will cause it to terminate
            t->interrupt();
        }
#endif
        if (tsa->getWaitingForSensor()) {
            // remove a sensor listener if one is present
            tsa->disposeSensorListener();
        }
        tsa->initialize();
        _activeActionList->removeAt(i);
    }
}

// this method is called when an event has occurred, to check if action should be delayed.
/*private*/ /*synchronized*/ void AutoTrainAction::checkDelay(TransitSectionAction* tsa) {
    int delay = tsa->getDataWhen();
    if (delay <= 0) {
        // no delay, execute action immediately
        executeAction(tsa);
    } else {
#if 0
        // start thread to trigger delayed action execution
        Runnable* r = new TSActionDelay(tsa, delay);
        Thread t = new Thread(r, "Check Delay on Action");
        tsa->setWaitingThread(t);
        t.start();
#endif
    }
}


/*private*/ /*synchronized*/ void AutoTrainAction::listenToDoneSensor(TransitSectionAction* tsa) {
    Sensor* s = InstanceManager::sensorManagerInstance()->getSensor(tsa->getStringWhat());
    if (s == NULL) {
        log->error("Done Sensor with name - " + tsa->getStringWhat() + " - was not found.");
        return;
    }
    _doneSensor = s;
    // set up listener
#if 0
    s.addPropertyChangeListener(_doneSensorListener
            = new java.beans.PropertyChangeListener() {
                @Override
                /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
                    if (e.getPropertyName() == ("KnownState")) {
                        int state = _doneSensor.getKnownState();
                        if (state == Sensor.ACTIVE) {
                            if (_activeTrain.getStatus() == ActiveTrain.WORKING) {
                                _activeTrain.setStatus(ActiveTrain.READY);
                            }
                        }
                    }
                }
            });
#endif
}

/*protected*/ /*synchronized*/ void AutoTrainAction::cancelDoneSensor() {
    if (_doneSensor != NULL) {
        if (_doneSensorListener != NULL) {
            _doneSensor->removePropertyChangeListener(_doneSensorListener);
        }
        _doneSensorListener = NULL;
        _doneSensor = NULL;
    }
}

// this method is called to execute the action, when the "When" event has happened.
// it is "/*public*/" because it may be called from a TransitSectionAction::
// djd debugging - need to check this out - probably useless, but harmless
//@SuppressFBWarnings(value = "SWL_SLEEP_WITH_LOCK_HELD",
//        justification = "used only by thread that can be stopped, no conflict with other threads expected")
/*public*/ /*synchronized*/ void AutoTrainAction::executeAction(TransitSectionAction* tsa) {
    if (tsa == NULL) {
        log->error("executeAction called with NULL TransitSectionAction");
        return;
    }
    Sensor* s = NULL;
    float temp = 0.0f;
    switch (tsa->getWhatCode()) {
        case TransitSectionAction::PAUSE:
            // pause for a number of fast minutes--e.g. station stop
            if (_autoActiveTrain->getCurrentAllocatedSection()->getNextSection() != NULL) {
                // pause train if this is not the last Section
#if 0
                QThread* tPause = _autoActiveTrain->pauseTrain(tsa->getDataWhat1());
                tsa->setWaitingThread(tPause);
#endif
            }
            break;
        case TransitSectionAction::SETMAXSPEED:
            // set maximum train speed to value
            temp = tsa->getDataWhat1();
            _autoActiveTrain->setMaxSpeed(temp * 0.01f);
            completedAction(tsa);
            break;
        case TransitSectionAction::SETCURRENTSPEED:
    {
            // set current speed either higher or lower than current value
            temp = tsa->getDataWhat1();
            float spd = temp * 0.01f;
            if (spd > _autoActiveTrain->getMaxSpeed()) {
                spd = _autoActiveTrain->getMaxSpeed();
            }
            _autoActiveTrain->setTargetSpeed(spd * _autoActiveTrain->getSpeedFactor());
            if ((_autoActiveTrain->getRampRate() != AutoActiveTrain::RAMP_NONE)
                    && (_autoActiveTrain->getAutoEngineer() != NULL)) {
                // temporarily turn ramping off
                _autoActiveTrain->setCurrentRampRate(AutoActiveTrain::RAMP_NONE);
#if 0 // TODO:
                 wait for train to achieve speed in a separate thread which will complete action
                Runnable monTrainSpeed = new MonitorTrainSpeed(tsa);
                Thread tMonTrainSpeed = new Thread(monTrainSpeed);
                tsa->setWaitingThread(tMonTrainSpeed);
                tMonTrainSpeed.start();
#endif
            } else {
                completedAction(tsa);
            }
            break;
    }
        case TransitSectionAction::RAMPTRAINSPEED:
    {
            // set current speed to target using specified ramp rate
            temp = tsa->getDataWhat1();
            float spdx = temp * 0.01f;
            if (spdx > _autoActiveTrain->getMaxSpeed()) {
                spdx = _autoActiveTrain->getMaxSpeed();
            }
            _autoActiveTrain->setTargetSpeed(spdx * _autoActiveTrain->getSpeedFactor());
            completedAction(tsa);
            break;
    }
        case TransitSectionAction::TOMANUALMODE:
            // drop out of automated mode and allow manual throttle control
            _autoActiveTrain->initiateWorking();
            if ((tsa->getStringWhat() != NULL) && (tsa->getStringWhat() != (""))) {
                // optional Done sensor was provided, listen to it
                listenToDoneSensor(tsa);
            }
            completedAction(tsa);
            break;
        case TransitSectionAction::SETLIGHT:
            // set light on or off
            if (_autoActiveTrain->getAutoEngineer() != NULL) {
                log->debug(tr("%1: setting light (F0) to %1" ).arg( _activeTrain->getTrainName() ).arg( tsa->getStringWhat()));
                if (tsa->getStringWhat() == ("On")) {
                    _autoActiveTrain->getAutoEngineer()->setFunction(0, true);
                } else if (tsa->getStringWhat() == ("Off")) {
                    _autoActiveTrain->getAutoEngineer()->setFunction(0, false);
                } else {
                    log->error("Incorrect Light ON/OFF setting *" + tsa->getStringWhat() + "*");
                }
            }
            completedAction(tsa);
            break;
        case TransitSectionAction::STARTBELL:
            // start bell (only works with sound decoder)
            if (_autoActiveTrain->getSoundDecoder() && (_autoActiveTrain->getAutoEngineer() != NULL)) {
                log->debug(tr("%1: starting bell (F1)" ).arg( _activeTrain->getTrainName()));
                _autoActiveTrain->getAutoEngineer()->setFunction(1, true);
            }
            completedAction(tsa);
            break;
        case TransitSectionAction::STOPBELL:
            // stop bell (only works with sound decoder)
            if (_autoActiveTrain->getSoundDecoder() && (_autoActiveTrain->getAutoEngineer() != NULL)) {
                log->debug(tr("%1: stopping bell (F1)" ).arg( _activeTrain->getTrainName()));
                _autoActiveTrain->getAutoEngineer()->setFunction(1, false);
            }
            completedAction(tsa);
            break;
        case TransitSectionAction::SOUNDHORN:
        // sound horn for specified number of milliseconds - done in separate thread
        case TransitSectionAction::SOUNDHORNPATTERN:
            // sound horn according to specified pattern - done in separate thread
            if (_autoActiveTrain->getSoundDecoder()) {
                log->debug(tr("%1: sounding horn as specified in action" ).arg( _activeTrain->getTrainName()));
#if 0
                Runnable rHorn = new HornExecution(tsa);
                Thread tHorn = new Thread(rHorn);
                tsa->setWaitingThread(tHorn);
                tHorn.start();
#endif
            } else {
                completedAction(tsa);
            }
            break;
#if 0
        case TransitSectionAction::LOCOFUNCTION:
            // execute the specified decoder function
            if (_autoActiveTrain->getAutoEngineer() != NULL) {
                log.debug("{}: setting function {} to {}", _activeTrain.getTrainName(),
                        tsa->getDataWhat1(), tsa->getStringWhat());
                int fun = tsa->getDataWhat1();
                if (tsa->getStringWhat() == ("On")) {
                    _autoActiveTrain->getAutoEngineer().setFunction(fun, true);
                } else if (tsa->getStringWhat() == ("Off")) {
                    _autoActiveTrain->getAutoEngineer().setFunction(fun, false);
                }
            }
            completedAction(tsa);
            break;
        case TransitSectionAction::SETSENSORACTIVE:
            // set specified sensor active
            s = InstanceManager.sensorManagerInstance().getSensor(tsa->getStringWhat());
            if (s != NULL) {
                // if sensor is already active, set it to inactive first
                if (s.getKnownState() == Sensor.ACTIVE) {
                    try {
                        s.setState(Sensor.INACTIVE);
                    } catch (jmri.JmriException reason) {
                        log.error("Exception when toggling Sensor " + tsa->getStringWhat() + " Inactive - " + reason);
                    }
                }
                try {
                    s.setState(Sensor.ACTIVE);
                } catch (jmri.JmriException reason) {
                    log.error("Exception when setting Sensor " + tsa->getStringWhat() + " Active - " + reason);
                }
            } else if ((tsa->getStringWhat() != NULL) && (!tsa->getStringWhat() == (""))) {
                log.error("Could not find Sensor " + tsa->getStringWhat());
            } else {
                log.error("Sensor not specified for Action");
            }
            break;
        case TransitSectionAction::SETSENSORINACTIVE:
            // set specified sensor inactive
            s = InstanceManager.sensorManagerInstance().getSensor(tsa->getStringWhat());
            if (s != NULL) {
                if (s.getKnownState() == Sensor.ACTIVE) {
                    try {
                        s.setState(Sensor.ACTIVE);
                    } catch (jmri.JmriException reason) {
                        log.error("Exception when toggling Sensor " + tsa->getStringWhat() + " Active - " + reason);
                    }
                }
                try {
                    s.setState(Sensor.INACTIVE);
                } catch (jmri.JmriException reason) {
                    log.error("Exception when setting Sensor " + tsa->getStringWhat() + " Inactive - " + reason);
                }
            } else if ((tsa->getStringWhat() != NULL) && (!tsa->getStringWhat() == (""))) {
                log.error("Could not find Sensor " + tsa->getStringWhat());
            } else {
                log.error("Sensor not specified for Action");
            }
            break;
        case TransitSectionAction::HOLDSIGNAL:
            // set specified signalhead or signalmast to HELD
            SignalMast sm = NULL;
            SignalHead sh = NULL;
            String sName = tsa->getStringWhat();
            sm = InstanceManager.getDefault(SignalMastManager.class).getSignalMast(sName);
            if (sm == NULL) {
                sh = InstanceManager.getDefault(SignalHeadManager.class).getSignalHead(sName);
                if (sh == NULL) {
                    log.error("{}: Could not find SignalMast or SignalHead named '{}'", _activeTrain.getTrainName(), sName);
                } else {
                    log.debug("{}: setting signalHead '{}' to HELD", _activeTrain.getTrainName(), sName);
                    sh.setHeld(true);
                }
            } else {
                log.debug("{}: setting signalMast '{}' to HELD", _activeTrain.getTrainName(), sName);
                sm.setHeld(true);
            }
            break;
        case TransitSectionAction::RELEASESIGNAL:
            // set specified signalhead or signalmast to NOT HELD
            sm = NULL;
            sh = NULL;
            sName = tsa->getStringWhat();
            sm = InstanceManager.getDefault(SignalMastManager.class).getSignalMast(sName);
            if (sm == NULL) {
                sh = InstanceManager.getDefault(SignalHeadManager.class).getSignalHead(sName);
                if (sh == NULL) {
                    log.error("{}: Could not find SignalMast or SignalHead named '{}'", _activeTrain.getTrainName(), sName);
                } else {
                    log.debug("{}: setting signalHead '{}' to NOT HELD", _activeTrain.getTrainName(), sName);
                    sh.setHeld(false);
                }
            } else {
                log.debug("{}: setting signalMast '{}' to NOT HELD", _activeTrain.getTrainName(), sName);
                sm.setHeld(false);
            }
            break;
#endif
        default:
            log->error("illegal What code - " + QString::number(tsa->getWhatCode()) + " - in call to executeAction");
            break;
    }
}
#if 0
class TSActionDelay implements Runnable {

    /**
     * A runnable that implements delayed execution of a
     * TransitSectionAction
     */
    /*public*/ TSActionDelay(TransitSectionAction tsa, int delay) {
        _tsa = tsa;
        _delay = delay;
    }

    @Override
    /*public*/ void run() {
        try {
            Thread.sleep(_delay);
            executeAction(_tsa);
        } catch (InterruptedException e) {
            // interrupting this thread will cause it to terminate without executing the action.
        }
    }
    private TransitSectionAction _tsa = NULL;
    private int _delay = 0;
}

class HornExecution implements Runnable {

    /**
     * A runnable to implement horn execution
     */
    /*public*/ HornExecution(TransitSectionAction tsa) {
        _tsa = tsa;
    }

    @Override
    /*public*/ void run() {
        _autoActiveTrain->incrementHornExecution();
        if (_tsa->getWhatCode() == TransitSectionAction::SOUNDHORN) {
            if (_autoActiveTrain->getAutoEngineer() != NULL) {
                try {
                    _autoActiveTrain->getAutoEngineer().setFunction(2, true);
                    Thread.sleep(_tsa->getDataWhat1());
                } catch (InterruptedException e) {
                    // interrupting will cause termination after turning horn off
                }
            }
            if (_autoActiveTrain->getAutoEngineer() != NULL) {
                _autoActiveTrain->getAutoEngineer().setFunction(2, false);
            }
        } else if (_tsa->getWhatCode() == TransitSectionAction::SOUNDHORNPATTERN) {
            String pattern = _tsa->getStringWhat();
            int index = 0;
            int sleepTime = ((_tsa->getDataWhat1()) * 12) / 10;
            boolean keepGoing = true;
            while (keepGoing && (index < pattern.length())) {
                // sound horn
                if (_autoActiveTrain->getAutoEngineer() != NULL) {
                    _autoActiveTrain->getAutoEngineer().setFunction(2, true);
                    try {
                        if (pattern.charAt(index) == 's') {
                            Thread.sleep(_tsa->getDataWhat1());
                        } else if (pattern.charAt(index) == 'l') {
                            Thread.sleep(_tsa->getDataWhat2());
                        }
                    } catch (InterruptedException e) {
                        // interrupting will cause termination after turning horn off
                        keepGoing = false;
                    }
                } else {
                    // loss of an autoEngineer will cause termination
                    keepGoing = false;
                }
                if (_autoActiveTrain->getAutoEngineer() != NULL) {
                    _autoActiveTrain->getAutoEngineer().setFunction(2, false);
                } else {
                    keepGoing = false;
                }
                index++;
                if (keepGoing && (index < pattern.length())) {
                    try {
                        Thread.sleep(sleepTime);
                    } catch (InterruptedException e) {
                        keepGoing = false;
                    }
                }
            }
        }
        _autoActiveTrain->decrementHornExecution();
        completedAction(_tsa);
    }
    private TransitSectionAction _tsa = NULL;
}

class MonitorTrain implements Runnable {

    /**
     * A runnable to monitor whether the autoActiveTrain is moving or
     * stopped Note: If train stops to do work with a manual throttle, this
     * thread will continue to wait until auto operation is resumed.
     */
    /*public*/ MonitorTrain(TransitSectionAction tsa) {
        _tsa = tsa;
    }

    @Override
    /*public*/ void run() {
        if (_tsa != NULL) {
            boolean waitingOnTrain = true;
            if (_tsa->getWhenCode() == TransitSectionAction::TRAINSTOP) {
                try {
                    while (waitingOnTrain) {
                        if ((_autoActiveTrain->getAutoEngineer() != NULL)
                                && (_autoActiveTrain->getAutoEngineer().isStopped())) {
                            waitingOnTrain = false;
                        } else {
                            Thread.sleep(_delay);
                        }
                    }
                    executeAction(_tsa);
                } catch (InterruptedException e) {
                    // interrupting will cause termination without executing the action
                }
            } else if (_tsa->getWhenCode() == TransitSectionAction::TRAINSTART) {
                if ((_autoActiveTrain->getAutoEngineer() != NULL)
                        && (!_autoActiveTrain->getAutoEngineer().isStopped())) {
                    // if train is not currently stopped, wait for it to stop
                    boolean waitingForStop = true;
                    try {
                        while (waitingForStop) {
                            if ((_autoActiveTrain->getAutoEngineer() != NULL)
                                    && (_autoActiveTrain->getAutoEngineer().isStopped())) {
                                waitingForStop = false;
                            } else {
                                Thread.sleep(_delay);
                            }
                        }
                    } catch (InterruptedException e) {
                        // interrupting will cause termination without executing the action
                    }
                }
                // train is stopped, wait for it to start
                try {
                    while (waitingOnTrain) {
                        if ((_autoActiveTrain->getAutoEngineer() != NULL)
                                && (!_autoActiveTrain->getAutoEngineer().isStopped())) {
                            waitingOnTrain = false;
                        } else {
                            Thread.sleep(_delay);
                        }
                    }
                    executeAction(_tsa);
                } catch (InterruptedException e) {
                    // interrupting will cause termination without executing the action
                }
            }
        }
    }
    private int _delay = 50;
    private TransitSectionAction _tsa = NULL;
}

class MonitorTrainSpeed implements Runnable {

    /**
     * A runnable to monitor whether the autoActiveTrain is moving or
     * stopped Note: If train stops to do work with a manual throttle, this
     * thread will continue to wait until auto operation is resumed.
     */
    /*public*/ MonitorTrainSpeed(TransitSectionAction tsa) {
        _tsa = tsa;
    }

    @Override
    /*public*/ void run() {
        while ((_autoActiveTrain->getAutoEngineer() != NULL)
                && (!_autoActiveTrain->getAutoEngineer().isAtSpeed())) {
            try {
                Thread.sleep(_delay);
            } catch (InterruptedException e) {
                log.error("unexpected interruption of wait for speed");
            }
        }
        _autoActiveTrain->setCurrentRampRate(_autoActiveTrain->getRampRate());
        if (_tsa != NULL) {
            completedAction(_tsa);
        }
    }
    private int _delay = 51;
    private TransitSectionAction _tsa = NULL;
}
#endif
