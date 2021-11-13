#include "autoactivetrain.h"
#include "activetrain.h"
#include "layoutblockmanager.h"
#include "instancemanager.h"
#include "autotrainaction.h"
#include "logger.h"
#include "qmessagebox.h"
#include "dispatcherframe.h"
#include "allocatedsection.h"
#include "section.h"
#include "signalmast.h"
#include "sensor.h"
#include "signalmastlogicmanager.h"
#include "signalmastlogic.h"
#include "signalspeedmap.h"
#include "allocatedsection.h"
#include "scale.h"
#include "thread.h"

//AutoActiveTrain::AutoActiveTrain(QObject *parent) : QObject(parent)
//{

//}
/**
 * This class holds information and options for an ActiveTrain when it is
 * running in AUTOMATIC mode. It is an extension to Active Train for automatic
 * running.
 * <P>
 * This class implements logic that follows a train around a layout. Train
 * follows signals, provided the next Section is allocated to it, and its
 * ActiveTrain's status is RUNNING.
 * <P>
 * This class is linked via it's parent ActiveTrain object.
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
 * The AutoEngineer sub class is based in part on code by Pete Cressman
 * contained in Warrants.java
 *
 * @author	Dave Duchamp Copyright (C) 2010-2011
 */
///*public*/ class AutoActiveTrain implements ThrottleListener {

/**
 * Main constructor method
 */
/*public*/ AutoActiveTrain::AutoActiveTrain(ActiveTrain* at, QObject* parent) : QObject(parent) {
 log = new Logger("AutoActiveTrain");
 // operational instance variables
 _activeTrain = NULL;
 _autoTrainAction = NULL;
 _throttle = NULL;
 _autoEngineer = NULL;
 _address = -1;
 _forward = true;
 _targetSpeed = 0.0;
 _savedStatus = ActiveTrain::RUNNING;
 _currentRampRate = RAMP_NONE;     // current Ramp Rate
 _pausingActive = false;		// true if train pausing thread is active

 // persistent instance variables (saved with train info)
 _rampRate = RAMP_NONE;     // default Ramp Rate
 _speedFactor = 1.0;		// default speed factor
 _maxSpeed = 0.6;			// default maximum train speed
 _resistanceWheels = true;  // true if all train cars show occupancy
 _runInReverse = false;  // true if the locomotive should run through Transit in reverse
 _soundDecoder = false;  // true if locomotive has a sound decoder
 _maxTrainLength = 200.0;  // default train length (scale feet/meters)

 // more operational variables
 _allocatedSectionList = new QList<AllocatedSection*>();
 _lbManager = NULL;
 _lastAllocatedSection = NULL;

 _speedRatio = QList<float>() << -1.0 << 0.0 << 0.25<< 0.35 << 0.50 << 0.65 << 0.8 << 1.15;

 re = NULL;
 useSpeedProfile = false;

 _initialized = false;
 _nextSection = NULL;	                     // train has not reached this Section yet
 _currentAllocatedSection = NULL;    // head of the train is in this Section
 _previousAllocatedSection = NULL;   // previous Section - part of train could still be in this section
 _controllingSignal = NULL;
 _controllingSignalMast = NULL;
 _conSignalListener = NULL;
 _conSignalMastListener = NULL;
 _conSignalProtectedBlock = NULL;
 _currentBlock = NULL;
 _nextBlock = NULL;
 _previousBlock = NULL;
 _stoppingBySensor = false;
 _stopSensor = NULL;
 _stopSensorListener = NULL;
 _stoppingForStopSignal = false;		  // if true, stopping because of signal appearance
 _stoppingByBlockOccupancy = false;    // if true, stop when _stoppingBlock goes UNOCCUPIED
 _stoppingUsingSpeedProfile = false;     // if true, using the speed profile against the roster entry to bring the loco to a stop in a specific distance
 _stoppingBlock = NULL;
 _resumingAutomatic = false;  // if true, resuming automatic mode after WORKING session
 _needSetSpeed = false;  // if true, train will set speed according to signal instead of stopping

 // keeps track of and restores previous speed
 _savedSpeed = 0.0;

 // keeps track of number of horn execution threads that are active
 _activeHornThreads = 0;
 prevSpeed = -1.0;


    _activeTrain = at;
    at->setAutoActiveTrain(this);
    _autoTrainAction = new AutoTrainAction(this);
    _lbManager =(LayoutBlockManager*) InstanceManager::getDefault("LayoutBlockManager");
}
#if 0
static final ResourceBundle rb = ResourceBundle
        .getBundle("jmri.jmrit.dispatcher.DispatcherBundle");
#endif






// accessor functions
/*public*/ ActiveTrain* AutoActiveTrain::getActiveTrain() {
    return _activeTrain;
}

/*public*/ AutoEngineer* AutoActiveTrain::getAutoEngineer() {
    return _autoEngineer;
}

/*public*/ AutoTrainAction* AutoActiveTrain::getAutoTrainAction() {
    return _autoTrainAction;
}

/*public*/ bool AutoActiveTrain::getForward() {
    return _forward;
}

/*public*/ void AutoActiveTrain::setForward(bool set) {
    _forward = set;
}

/*public*/ /*synchronized*/ float AutoActiveTrain::getTargetSpeed() {
    return _targetSpeed;
}

/*public*/ /*synchronized*/ void AutoActiveTrain::setTargetSpeed(float speed) {
    _targetSpeed = speed;
#if 1
    if (speed > 0.002) {
        _autoEngineer->slowToStop(false);
    }
#endif
}

/*public*/ int AutoActiveTrain::getSavedStatus() {
    return _savedStatus;
}

/*public*/ void AutoActiveTrain::setSavedStatus(int status) {
    _savedStatus = status;
}

/*public*/ /*synchronized*/ void AutoActiveTrain::setCurrentRampRate(int rate) {
    _currentRampRate = rate;
}

/*public*/ int AutoActiveTrain::getRampRate() {
    return _rampRate;
}

/*public*/ void AutoActiveTrain::setRampRate(int rate) {
    _rampRate = rate;
    _currentRampRate = rate;
}

/*public*/ float AutoActiveTrain::getSpeedFactor() {
    return _speedFactor;
}

/*public*/ void AutoActiveTrain::setSpeedFactor(float factor) {
    _speedFactor = factor;
}

/*public*/ float AutoActiveTrain::getMaxSpeed() {
    return _maxSpeed;
}

/*public*/ void AutoActiveTrain::setMaxSpeed(float speed) {
    _maxSpeed = speed;
}

/*public*/ bool AutoActiveTrain::getResistanceWheels() {
    return _resistanceWheels;
}

/*public*/ void AutoActiveTrain::setResistanceWheels(bool set) {
    _resistanceWheels = set;
}

/*public*/ bool AutoActiveTrain::getRunInReverse() {
    return _runInReverse;
}

/*public*/ void AutoActiveTrain::setRunInReverse(bool set) {
    _runInReverse = set;
    if (_runInReverse) {
        _forward = false;
    } else {
        _forward = true;
    }
}

/*public*/ bool AutoActiveTrain::getSoundDecoder() {
    return _soundDecoder;
}

/*public*/ void AutoActiveTrain::setSoundDecoder(bool set) {
    _soundDecoder = set;
}

/*public*/ float AutoActiveTrain::getMaxTrainLength() {
    return _maxTrainLength;
}

/*public*/ void AutoActiveTrain::setMaxTrainLength(float length) {
    _maxTrainLength = length;
}


/**
 * Initialize new Auto Active Train or get a new throttle after WORKING Sets
 * up the DCC address and initiates creation of a throttle to run the train.
 */
/*public*/ bool AutoActiveTrain::initialize() {
    //clear all flags
    _pausingActive = false;
    _stoppingBySensor = false;
    _stoppingForStopSignal = false;
    _stoppingByBlockOccupancy = false;
    _stoppingUsingSpeedProfile = false;

    // get decoder address
    try {
        _address = (_activeTrain->getDccAddress()).toInt();
    } catch (NumberFormatException ex) {
       log->warn(tr("invalid dcc address '%1' for %2").arg(_activeTrain->getDccAddress()).arg(_activeTrain->getTrainName()));
        return false;
    }
    if ((_address < 1) || (_address > 9999)) {
       log->warn(tr("invalid dcc address '%1' for %2").arg(_activeTrain->getDccAddress()).arg(_activeTrain->getTrainName()));
        return false;
    }
    // request a throttle for automatic operation, throttle returned via callback below
   log->debug(tr("%1: requesting throttle address=%2").arg(_activeTrain->getTrainName()).arg(_address));
    bool ok = true;
    if (_activeTrain->getTrainSource() == ActiveTrain::ROSTER) {
        if (_activeTrain->getRosterEntry() != NULL) {
            re = _activeTrain->getRosterEntry();
            ok = InstanceManager::throttleManagerInstance()->requestThrottle(_activeTrain->getRosterEntry(), (ThrottleListener*)this, false);
            if (re->getSpeedProfile() != NULL) {
               log->debug(tr("%1: using speed profile from roster entry %2").arg(_activeTrain->getTrainName()).arg( re->getId()));
                useSpeedProfile = true;
            }
        } else {
            ok = InstanceManager::throttleManagerInstance()->requestThrottle(_address, (ThrottleListener*)this);
        }
    } else {
        ok = InstanceManager::throttleManagerInstance()->requestThrottle(_address, (ThrottleListener*)this);
    }
    if (!ok) {
       log->warn("Throttle for locomotive address " + QString::number(_address) + " could not be setup.");
        _activeTrain->setMode(ActiveTrain::DISPATCHED);
        return false;
    }
    return true;
}

// Throttle feedback method - Initiates running AutoEngineer with the new throttle
//@Override
/*public*/ void AutoActiveTrain::notifyThrottleFound(DccThrottle* t) {
    _throttle = t;
    if (_throttle == NULL) {
//        javax.swing.JOptionPane.showMessageDialog(NULL, java.text.MessageFormat.format(tr(
//                "Error28"), new Object[]{_activeTrain->getTrainName()}), tr("InformationTitle"),
//                javax.swing.JOptionPane.INFORMATION_MESSAGE);
     QMessageBox::information(NULL, tr("Information"), tr("Could not start a throttle to run train \"%1\"\nautomatically, changing to manual running.").arg(_activeTrain->getTrainName()));
       log->warn("NULL throttle returned for train  " + _activeTrain->getTrainName() + "during automatic initialization.");
        _activeTrain->setMode(ActiveTrain::DISPATCHED);
        return;
    }
   log->debug(tr("%1: New AutoEngineer, address=%2, length=%3, factor=%4").arg(
            _activeTrain->getTrainName()).arg(
            _throttle->getLocoAddress()->toString()).arg(
            getMaxTrainLength()).arg( _speedFactor));
#if 0
    _autoEngineer = new AutoEngineer(this);
    new Thread(_autoEngineer, "Auto Engineer " + _address).start();
#endif
    _activeTrain->setMode(ActiveTrain::AUTOMATIC);
    if (_resumingAutomatic) {
        _resumingAutomatic = false;
        _activeTrain->setStatus(ActiveTrain::RUNNING);
        setEngineDirection();
        setSpeedBySignal();
    } else if (((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getAutoAllocate()) {
        // starting for the first time with automatic allocation of Sections
        setSpeedBySignal();
    }
}

/*protected*/ DccThrottle* AutoActiveTrain::getThrottle() {
    return _throttle;
}

//@Override
/*public*/ void AutoActiveTrain::notifyFailedThrottleRequest(DccLocoAddress* address, QString reason) {
   log->error("Throttle request failed for " + address->toString() + " because " + reason);
}


/*protected*/ Section* AutoActiveTrain::getLastAllocatedSection() {
    AllocatedSection* as = _allocatedSectionList->at(_allocatedSectionList->size() - 1);
    if (as != NULL) {
        return as->getSection();
    }
    return NULL;
}

/*protected*/ void AutoActiveTrain::saveSpeed() {
    _savedSpeed = _targetSpeed;
}

/*protected*/ void AutoActiveTrain::restoreSavedSpeed() {
    _targetSpeed = _savedSpeed;
}

/*protected*/ void AutoActiveTrain::decrementHornExecution() {
    _activeHornThreads--;
}

/*protected*/ void AutoActiveTrain::incrementHornExecution() {
    _activeHornThreads++;
}

/**
 * Notification methods Handle notification of change in state and occupancy
 * of Sections and Blocks to track the train around the Transit
 */
/*protected*/ void AutoActiveTrain::handleSectionStateChange(AllocatedSection* as) {
    if (!isInAllocatedList(as)) {
        addAllocatedSection(as);
    }
}

/*protected*/ void AutoActiveTrain::handleSectionOccupancyChange(AllocatedSection* as) {
    if (!isInAllocatedList(as)) {
        if (log->isDebugEnabled()) {
           log->debug("Unexpected occupancy change notification - Section " + as->getSection()->getSystemName());
        }
        return;
    }
    if (as->getSection()->getOccupancy() == Section::OCCUPIED) {
        // Section changed to OCCUPIED - process if expected next Section
        if (as->getSection() == _nextSection) {
            setNewCurrentSection(as);
        }
    } else if (as->getSection()->getOccupancy() == Section::UNOCCUPIED) {
        TransitSection* ts = as->getTransitSection();
        if (ts != NULL) {
            _autoTrainAction->removeTransitSection(ts);
        }
    }
}
#if 1
//@SuppressFBWarnings(value = "IS2_INCONSISTENT_SYNC",
//        justification = "OK to not sync here, no conflict expected")
/*protected*/ void AutoActiveTrain::handleBlockStateChange(AllocatedSection* as, Block* b) {
    if (b->getState() == Block::OCCUPIED) {
        // Block changed to OCCUPIED - train has entered this block
       log->trace(tr("%1: handleBlockStateChange to OCCUPIED section %2, block %3, length %4").arg(_activeTrain->getTrainName(),
                as->getSection()->getSystemName(),
                b->getUserName(), QString::number(getBlockLength(b))));
        if (b == _nextBlock) {
            _previousBlock = _currentBlock;
            _currentBlock = _nextBlock;
            _nextBlock = getNextBlock(b, as);
            if (_nextBlock != NULL) {
                if ((_currentBlock == _activeTrain->getEndBlock()) && _activeTrain->getReverseAtEnd()
                        && (as->getSequence() == _activeTrain->getEndBlockSectionSequenceNumber())) {
                    // entered last block of Transit, must stop and reverse
                    stopInCurrentSection(END_REVERSAL);
                    _activeTrain->setRestart();
                } else if ((_currentBlock == _activeTrain->getStartBlock())
                        && _activeTrain->getResetWhenDone() && _activeTrain->isTransitReversed()
                        && (as->getSequence() == _activeTrain->getStartBlockSectionSequenceNumber())) {
                    // entered start block of Transit, must stop and reset for continuing
                    stopInCurrentSection(BEGINNING_RESET);
                    _activeTrain->setRestart();
                } else if ((_currentBlock == _activeTrain->getEndBlock())
                        && _activeTrain->getResetWhenDone() && _activeTrain->getDelayedRestart() != ActiveTrain::NODELAY
                        && (as->getSequence() == _activeTrain->getEndBlockSectionSequenceNumber())) {
                    // entered start block of Transit, must stop and reset for continuing
                    stopInCurrentSection(BEGINNING_RESET);
                    _activeTrain->setRestart();
                    removeCurrentSignal();
                } else {
                    setupNewCurrentSignal(as);
                }
            } else {
                // reached last block in this transit
                removeCurrentSignal();
               log->trace(tr("%1: block occupied stop in Current Section, Block= %2").arg(_activeTrain->getTrainName(), b->getUserName()));
                stopInCurrentSection(NO_TASK);
            }
        } else if (b != _currentBlock) {
           log->trace(tr("%1: block going occupied %2 is not _nextBlock or _currentBlock - ignored.").arg(_activeTrain->getTrainName(), b->getUserName()));
            return;
        }
    } else if (b->getState() == Block::UNOCCUPIED) {
       log->trace(tr("%1: handleBlockStateChange to UNOCCUPIED - Section %2, Block %3, speed %4").arg(_activeTrain->getTrainName()).arg(
                as->getSection()->getSystemName()).arg(b->getUserName()).arg(_targetSpeed));
        if (_stoppingByBlockOccupancy && (b == _stoppingBlock)) {
           log->trace(tr("%1: setStopNow by block occupancy from Block unoccupied, Block= %2").arg(_activeTrain->getTrainName(), b->getSystemName()));
            _stoppingByBlockOccupancy = false;
            _stoppingBlock = NULL;
// djd may need more code here
            if (_needSetSpeed) {
                _needSetSpeed = false;
                setSpeedBySignal();
            } else {
                setStopNow();
            }
        }
    }
    _autoTrainAction->handleBlockStateChange(as, b);
}

#endif
/**
 * support methods
 */
/*protected*/ void AutoActiveTrain::setEngineDirection() {
    if (_runInReverse) {
        if (_activeTrain->isTransitReversed()) {
            _forward = true;
        } else {
            _forward = false;
        }
    } else {
        if (_activeTrain->isTransitReversed()) {
            _forward = false;
        } else {
            _forward = true;
        }
    }
}

/*protected*/ AllocatedSection* AutoActiveTrain::getCurrentAllocatedSection() {
    return _currentAllocatedSection;
}

/*protected*/ void AutoActiveTrain::allocateAFresh() {
    //Reset initialized flag
    _initialized = false;
}

/*private*/ void AutoActiveTrain::addAllocatedSection(AllocatedSection* as) {
    _allocatedSectionList->append(as);
    if (!_initialized) {
        // this is first allocated section, get things started
        _initialized = true;
        _nextSection = as->getSection();
        _currentBlock = _activeTrain->getStartBlock();
        if (as->getSection()->containsBlock(_currentBlock)) {
            // starting Block is in this allocated section - find next Block
            setNewCurrentSection(as);
            _nextBlock = getNextBlock(_currentBlock, as);
        } else if (as->getSection()->connectsToBlock(_currentBlock)) {
            // starting Block is connected to a Block in this allocated section
            EntryPoint* ep = as->getSection()->getEntryPointFromBlock(_currentBlock, as->getDirection());
            if (ep != NULL) {
                _nextBlock = ep->getBlock();
            } else {
               log->error(tr("failure to get entry point to Transit from Block ") + _currentBlock->getSystemName());
            }
        }
        if (_nextBlock != NULL) {
            // set up new current signal
            setupNewCurrentSignal(as);
        }
    }
    // if train is stopping for lack of an allocation, set flag to restart it
    if (!_pausingActive && (_lastAllocatedSection == _currentAllocatedSection)
            && isStopping() && (_activeTrain->getStatus() == ActiveTrain::RUNNING)) {
        _needSetSpeed = true;
    }
    // request next allocation if appropriate--Dispatcher must decide whether to allocate it and when
    if ((!((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getAutoAllocate()) && ((_lastAllocatedSection == NULL)
            || (_lastAllocatedSection->getNextSection() == as->getSection()))) {
        // if AutoAllocate, this is now done in DispatcherFrame::java for all trains
        _lastAllocatedSection = as;
        if (as->getNextSection() != NULL) {
            Section* nSection = as->getNextSection();
            int nextSeq = as->getNextSectionSequence();
            int nextDir = _activeTrain->getAllocationDirectionFromSectionAndSeq(nSection, nextSeq);
            ((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->requestAllocation(_activeTrain, nSection, nextDir, nextSeq, true, NULL);
        }
    }
}

/*protected*/ void AutoActiveTrain::removeAllocatedSection(AllocatedSection* as) {
    int index = -1;
    for (int i = _allocatedSectionList->size(); i > 0; i--) {
        if (_allocatedSectionList->at(i - 1) == as) {
            index = i - 1;
        }
    }
    if (index >= 0) {
        _allocatedSectionList->removeAt(index);
    } else {
       log->warn("unexpected call to removeAllocatedSection - Section " + as->getSection()->getSystemName());
    }
}

/*private*/ bool AutoActiveTrain::isStopping() {
    // here add indicator for new stopping methods, if any are added
    return (_stoppingBySensor || _stoppingByBlockOccupancy || _stoppingUsingSpeedProfile);
}

/*private*/ bool AutoActiveTrain::isInAllocatedList(AllocatedSection* as) {
    for (int i = 0; i < _allocatedSectionList->size(); i++) {
        if (_allocatedSectionList->at(i) == as) {
            return true;
        }
    }
    return false;
}

/*private*/ bool AutoActiveTrain::isSectionInAllocatedList(Section* s) {
    for (int i = 0; i < _allocatedSectionList->size(); i++) {
        if ((_allocatedSectionList->at(i))->getSection() == s) {
            return true;
        }
    }
    return false;
}

/*private*/ void AutoActiveTrain::removeCurrentSignal() {
    if (_conSignalListener != NULL) {
//        _controllingSignal.removePropertyChangeListener(_conSignalListener);
        _conSignalListener = NULL;
    }
    _controllingSignal = NULL;
    if (_conSignalMastListener != NULL) {
//        _controllingSignalMast->removePropertyChangeListener(_conSignalMastListener);
        _conSignalMastListener = NULL;
    }
    _controllingSignalMast = NULL;
}

/*protected*/ /*synchronized*/ void AutoActiveTrain::setupNewCurrentSignal(AllocatedSection* as) {
#if 1
    removeCurrentSignal();
    if (((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getSignalType() == DispatcherFrame::SIGNALHEAD) {
        SignalHead* sh = _lbManager->getFacingSignalHead(_currentBlock, _nextBlock);
        if (sh != NULL) {
            _controllingSignal = sh;
            _conSignalProtectedBlock = _nextBlock;
//            sh.addPropertyChangeListener(_conSignalListener = new PropertyChangeListener() {
//                @Override
//                /*public*/ void propertyChange(PropertyChangeEvent e) {
//                    if (e.getPropertyName() == ("Appearance")) {
//                        // controlling signal has changed appearance
//                        setSpeedBySignal();
//                        if (_stoppingForStopSignal && (_targetSpeed > 0.0)) {
//                            cancelStopInCurrentSection();
//                            _stoppingForStopSignal = false;
//                        }
//                    }
//                }
//            });
            connect(sh, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
            if (log->isDebugEnabled()) {
               log->debug("new current signal = " + sh->getSystemName());
            }
            setSpeedBySignal();
        } // Note: NULL signal head will result when exiting throat-to-throat blocks.
        else if (log->isDebugEnabled()) {
           log->debug("new current signal is NULL - sometimes OK");
        }
    } else {
        //SignalMast
        SignalMast* sm = NULL;
        Block* cB = _currentBlock;
        Block* nB = _nextBlock;
        if (as == NULL) {
            as = _currentAllocatedSection;
        }
        // Find the signal mast at the end of the section by making sure that cB is within as and nB is not.
        //while (as != NULL && as->getSection().containsBlock(nB) && nB != NULL) {
        //    cB = nB;
        //    nB = getNextBlock(nB, as);
        //}
        while (sm == NULL && nB != NULL) {
            sm = _lbManager->getFacingSignalMast(cB, nB);
            if (sm == NULL) {
                cB = nB;
                nB = getNextBlock(nB, as);
            }
        }
        if (sm != NULL) {
            _controllingSignalMast = sm;
            _conSignalProtectedBlock = nB;
//            sm.addPropertyChangeListener(_conSignalMastListener = new PropertyChangeListener() {
//                @Override
//                /*public*/ void propertyChange(PropertyChangeEvent e) {
//                    if (e.getPropertyName() == ("Aspect")) {
//                        // controlling signal has changed appearance
//                        if (_stoppingForStopSignal && (_targetSpeed > 0.0)) {
//                            cancelStopInCurrentSection();
//                            _stoppingForStopSignal = false;
//                        }
//                        setSpeedBySignal();
//                    } else if (e.getPropertyName() == ("Held")) {
//                        if (!((Boolean) e.getNewValue()).boolValue()) {
//                            cancelStopInCurrentSection();
//                            _stoppingForStopSignal = false;
//                        }
//                        setSpeedBySignal();
//                    }
//                }
//            });
            connect(sm, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
           log->debug(tr("%1: new current signalmast %2(%3) for section %4").arg(_activeTrain->getTrainName()).arg(sm->getDisplayName()).arg(
              sm->getAspect()).arg(as->getSectionName()));
            setSpeedBySignal();
        } // Note: NULL signal head will result when exiting throat-to-throat blocks.
        else {
           log->debug(tr("%1: new current signalmast is NULL for section %2 - sometimes OK").arg( _activeTrain->getTrainName()).arg(as->getSectionName()));
        }
    }
#endif
}

/*private*/ Block* AutoActiveTrain::getNextBlock(Block* b, AllocatedSection* as) {
    if (((_currentBlock == _activeTrain->getEndBlock()) && _activeTrain->getReverseAtEnd()
            && (as->getSequence() == _activeTrain->getEndBlockSectionSequenceNumber()))) {
        return _previousBlock;
    }
    if ((_currentBlock == _activeTrain->getStartBlock())
            && _activeTrain->getResetWhenDone() && _activeTrain->isTransitReversed()
            && (as->getSequence() == _activeTrain->getStartBlockSectionSequenceNumber())) {
        return _previousBlock;
    }
    if (as->getNextSection() != NULL) {
        EntryPoint* ep = as->getSection()->getExitPointToSection(_nextSection, as->getDirection());
        if ((ep != NULL) && (ep->getBlock() == b)) {
            // this block is connected to a block in the next section
            return ep->getFromBlock();
        }
    }
    // this allocated section has multiple blocks _or_ there is no next Section
    Block* blk = as->getSection()->getEntryBlock();
    while (blk != NULL) {
        if (b == blk) {
            return as->getSection()->getNextBlock();
        }
        blk = as->getSection()->getNextBlock();
    }
    return NULL;
}

/*private*/ void AutoActiveTrain::setNewCurrentSection(AllocatedSection* as) {
    if (as->getSection() == _nextSection) {
        _previousAllocatedSection = _currentAllocatedSection;
        _currentAllocatedSection = as;
        _nextSection = as->getNextSection();
        TransitSection* ts = as->getTransitSection();
        if (ts != NULL) {
            _autoTrainAction->addTransitSection(ts);
        }
        // check if new next Section exists but is not allocated to this train
        if ((_nextSection != NULL) && !isSectionInAllocatedList(_nextSection)) {
            // next section is not allocated to this train, must not enter it, even if signal is OK.
            stopInCurrentSection(NO_TASK);
            _needSetSpeed = false;
        }
    }
}

// called by above or when resuming after stopped action
/*protected*/ /*synchronized*/ void AutoActiveTrain::setSpeedBySignal() {
    if (_pausingActive || ((_activeTrain->getStatus() != ActiveTrain::RUNNING)
            && (_activeTrain->getStatus() != ActiveTrain::WAITING)) || ((_controllingSignal == NULL)
            && ((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getSignalType() == DispatcherFrame::SIGNALHEAD)
            || (((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getSignalType() == DispatcherFrame::SIGNALMAST && (_controllingSignalMast == NULL
            || (_activeTrain->getStatus() == ActiveTrain::WAITING && !_activeTrain->getStarted())))
            || (_activeTrain->getMode() != ActiveTrain::AUTOMATIC)) {
        // train is pausing or not RUNNING or WAITING in AUTOMATIC mode, or no controlling signal,
        //			don't set speed based on controlling signal
        return;
    }
    if (((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getSignalType() == DispatcherFrame::SIGNALHEAD) {
     //set speed using signalHeads
        switch (_controllingSignal->getAppearance()) {
            case SignalHead::DARK:
            case SignalHead::RED:
            case SignalHead::FLASHRED:
                // May get here from signal changing before Block knows it is occupied, so must
                //      check Block occupancy sensor, which must change before signal.
                if (_conSignalProtectedBlock->getSensor()->getState() == Block::OCCUPIED) {
                    // Train has just passed this signal - ignore this signal
                } else {
                    stopInCurrentSection(NO_TASK);
                    _stoppingForStopSignal = true;
                }
                break;
            case SignalHead::YELLOW:
            case SignalHead::FLASHYELLOW:
                setTargetSpeedState(SLOW_SPEED);
                _activeTrain->setStatus(ActiveTrain::RUNNING);
                break;
            case SignalHead::GREEN:
            case SignalHead::FLASHGREEN:
                setTargetSpeedState(NORMAL_SPEED);
                _activeTrain->setStatus(ActiveTrain::RUNNING);
                break;
            case SignalHead::LUNAR:
            case SignalHead::FLASHLUNAR:
                setTargetSpeedState(RESTRICTED_SPEED);
                _activeTrain->setStatus(ActiveTrain::RUNNING);
                break;
        }
    } else {
        //Set speed using SignalMasts;
        QString displayedAspect = _controllingSignalMast->getAspect();
#if  0
        if (log->isTraceEnabled()) {
           log->trace("{}: Controlling mast {} ({})", _activeTrain->getTrainName(), _controllingSignalMast->getDisplayName(), displayedAspect);
            if (_conSignalProtectedBlock == NULL) {
               log->trace("{}: Protected block is NULL", _activeTrain->getTrainName());
            } else {
               log->trace("{}: Protected block: {} state: {} speed: {}", _activeTrain->getTrainName(),
                        _conSignalProtectedBlock::getSensor().getDisplayName(),
                        (_conSignalProtectedBlock::getSensor().getState()==Block::OCCUPIED ? "OCCUPIED" : "NOT OCCUPIED"),
                        _conSignalProtectedBlock::getBlockSpeed());
            }
        }
#endif
        if ((_controllingSignalMast->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::DANGER) == (displayedAspect))
                || !_controllingSignalMast->getLit() || _controllingSignalMast->getHeld()) {
            if (_conSignalProtectedBlock->getSensor()->getState() == Block::OCCUPIED) {
                // Train has just passed this signal - ignore this signal
               log->debug(tr("%1: _conSignalProtectedBlock is the block just past so ignore %2").arg(_activeTrain->getTrainName()).arg(_conSignalProtectedBlock->getDisplayName()));
            } else {
               log->debug(tr("%1: Signal %2 at Held or Danger so Stop").arg(_activeTrain->getTrainName()).arg( _controllingSignalMast->getDisplayName()));
                stopInCurrentSection(NO_TASK);
                _stoppingForStopSignal = true;
            }
        } else if (_controllingSignalMast->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::PERMISSIVE) != NULL
                && _controllingSignalMast->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::PERMISSIVE) == (displayedAspect)) {
            setTargetSpeedState(RESTRICTED_SPEED);
            _activeTrain->setStatus(ActiveTrain::RUNNING);
        } else {

            //if using signalmasts, set speed to lesser of aspect speed and signalmastlogic speed
            //  (minimum speed on the path to next signal, using turnout and block speeds)

            QString aspectSpeedStr =  _controllingSignalMast->getSignalSystem()->getProperty(displayedAspect, "speed").toString();
//           log->trace("{}: Signal {} speed {} for aspect {}", _activeTrain->getTrainName(), _controllingSignalMast->getDisplayName(), aspectSpeedStr, displayedAspect);
            float speed = -1.0f;
            if (aspectSpeedStr != NULL) {
                try {
                    speed = aspectSpeedStr.toFloat();
                } catch (NumberFormatException nx) {
                    try {
                        speed = ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getSpeed(aspectSpeedStr);
//                       log->trace("{}: Signal {} speed from map for {} is {}", _activeTrain->getTrainName(), _controllingSignalMast->getDisplayName(), aspectSpeedStr, speed);
                    } catch (Exception ex) {
                        //Considered Normal if the speed does not appear in the map
//                       log->trace("{}: Speed not found {}", _activeTrain->getTrainName(), aspectSpeedStr);
                    }
                }
            }
            int aspectSpeed = (int) speed; //save for debug message

            //get maximum speed for the route between current and next signalmasts
            float smLogicSpeed = -1.0f;
            QString smDestinationName = "unknown";
            SignalMastLogic* smLogic = ((SignalMastLogicManager*) InstanceManager::getDefault("SignalMastLogicManager"))->getSignalMastLogic(_controllingSignalMast);
            if (smLogic != NULL) {
                SignalMast* smDestination = smLogic->getActiveDestination();
                if (smDestination != NULL) {
                    smDestinationName = smDestination->getDisplayName();
                    smLogicSpeed = (int) smLogic->getMaximumSpeed(smDestination);
                }
            }

            //use the smaller of aspect speed or route speed
            if (smLogicSpeed > -1.0f && smLogicSpeed < speed) {
                speed = smLogicSpeed;
            }

           log->debug(tr("%1: %2(%3) %4(%5), Dest: %6, path max: %7").arg(
                    _activeTrain->getTrainName()).arg(
                    _controllingSignalMast->getDisplayName()).arg( displayedAspect).arg( aspectSpeedStr).arg( aspectSpeed).arg(
                    smDestinationName).arg( (int) smLogicSpeed));

            if (speed > -1.0f) {
//                    float mls = _controllingSignalMast->getSignalSystem().getMaximumLineSpeed();
//                    float increment = mls / 7f;
//                   log->trace("{}: MaximumLineSpeed is {}, speed is {}", _activeTrain->getTrainName(), mls, speed);
//                    int speedState = (int) Math.ceil(speed / increment);
//                    if (speedState <= 1) {
//                        speedState = 2;
//                    }
//                   log->trace("{}: SpeedState is {}", _activeTrain->getTrainName(), speedState);
                /* We should work on the basis that the speed required in the current block/section is governed by the signalmast
                 that we have passed and not the one we are approaching when we are accelerating.
                 However when we are decelerating we should be aiming to meet the speed required by the approaching signalmast
                 whether that is to slow down or come to a complete stand still.
                 */
                if (prevSpeed == -1 || speed < prevSpeed) {
                   log->debug(tr("%1: Signal %2 setting speed to {%3 for next").arg( _activeTrain->getTrainName()).arg(
                            _controllingSignalMast->getDisplayName()).arg( speed));
                    setTargetSpeedValue(speed);
                } else {
                   log->debug(tr("%1: Signal %2 setting speed to %3 for previous").arg( _activeTrain->getTrainName()));
                    setTargetSpeedValue(prevSpeed);
                }
                prevSpeed = speed;
                _activeTrain->setStatus(ActiveTrain::RUNNING);

            } else {
               log->warn(tr("%1: No specific speeds found so will use the default").arg( _activeTrain->getTrainName()));
                setTargetSpeedState(NORMAL_SPEED);
                _activeTrain->setStatus(ActiveTrain::RUNNING);
            }
        }
    }
}
#if 1

// called to cancel a stopping action that is in progress
/*private*/ /*synchronized*/ void AutoActiveTrain::cancelStopInCurrentSection() {
    if (isStopping()) {
        if (_stoppingBySensor) {
            // cancel stopping by stop sensor
            _needSetSpeed = true;
            handleStopSensorChange();
        } else if (_stoppingByBlockOccupancy) {
            // cancel stopping by block occupancy
            _stoppingByBlockOccupancy = false;
            _stoppingBlock = NULL;
        } else if (_stoppingUsingSpeedProfile) {
            _stoppingUsingSpeedProfile = false;
            _stoppingBlock = NULL;
            _autoEngineer->slowToStop(false);
        }
        // here add other stopping methods if any are added
    }
}
#endif
/*private*/ /*synchronized*/ void AutoActiveTrain::stopInCurrentSection(int task) {
    if (_currentAllocatedSection == NULL) {
       log->error(tr("%1: Current allocated section NULL on entry to stopInCurrentSection").arg( _activeTrain->getTrainName()));
        setStopNow();
        return;
    }
   log->debug(tr("%1: StopInCurrentSection called for %2").arg(_activeTrain->getTrainName()).arg( _currentAllocatedSection->getSectionName()));
    if ((_targetSpeed == 0.0f) || isStopping()) {
       log->debug(tr("%1: train is already stopped or stopping.").arg( _activeTrain->getTrainName()));
        // ignore if train is already stopped or if stopping is in progress
        return;
    }
    // if Section has stopping sensors, use them
    if (_currentAllocatedSection->getSection()->getState() == Section::FORWARD) {
        _stopSensor = _currentAllocatedSection->getSection()->getForwardStoppingSensor();
    } else {
        _stopSensor = _currentAllocatedSection->getSection()->getReverseStoppingSensor();
    }
    if (_stopSensor != NULL) {
        if (_stopSensor->getKnownState() == Sensor::ACTIVE) {
            // stop sensor is already active, stop now
            setStopNow();
        } else {
            if (useSpeedProfile && _currentAllocatedSection->getSection()->getActualLength() > 0) {
                _stoppingUsingSpeedProfile = true;
            } else {
                // sensor is not active
                setTargetSpeedState(RESTRICTED_SPEED);
            }
//            _stopSensor::addPropertyChangeListener(_stopSensorListener
//                    = new java.beans.PropertyChangeListener() {
//                        @Override
//                        /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                            if (e.getPropertyName() == ("KnownState")) {
//                                handleStopSensorChange();
//                            }
//                        }
//                    });
            connect(_stopSensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(on_stopSensor(PropertyChangeEvent*)));
            _stoppingBySensor = true;
        }
    } else if (_currentAllocatedSection->getLength() < _maxTrainLength) {
        // train will not fit comfortably in the Section, stop it immediately
        setStopNow();
    } else if (_resistanceWheels) {
        // train will fit in current allocated Section and has resistance wheels
        // try to stop by watching Section Block occupancy
        if (_currentAllocatedSection->getSection()->getNumBlocks() == 1) {
            if (_previousAllocatedSection != NULL) {
                Block* tBlock = _previousAllocatedSection->getSection()->getLastBlock();
                if ((tBlock != NULL) && (tBlock->getState() == Block::OCCUPIED)) {
                    _stoppingBlock = tBlock;
                    setStopByBlockOccupancy();
                } else {
                    setStopNow();
                }
            } else {
                setStopNow();
            }
        } else {
            // Section has multiple blocks
            Block* exitBlock = _currentAllocatedSection->getExitBlock();
            Block* enterBlock = _currentAllocatedSection->getEnterBlock(_previousAllocatedSection);
            if (exitBlock == NULL) {
                // this is the final Section of the Transit
                Block* testBlock = _currentAllocatedSection->getSection()->getEntryBlock();
                // skip over unused leading blocks, if any
                while ((testBlock != NULL) && (testBlock != enterBlock)) {
                    testBlock = _currentAllocatedSection->getSection()->getNextBlock();
                }
                // is there room in the remaining blocks to hold the train?
                int testLength = getBlockLength(testBlock);
                while (testBlock != NULL) {
                    testBlock = _currentAllocatedSection->getSection()->getNextBlock();
                    if (testBlock != NULL) {
                        testLength += getBlockLength(testBlock);
                    }
                }
                if ((testLength > _maxTrainLength) && (_previousBlock != NULL)
                        && (_previousBlock->getState() == Block::OCCUPIED)) {
                    // fits, pull train entirely into the last Section
                    _stoppingBlock = _previousBlock;
                    setStopByBlockOccupancy();
                } else {
                    setStopNow();
                }
            } else if (enterBlock == NULL) {
                // this is the first Section of the Transit, with train starting in this Section
                setStopNow();
            } else if (exitBlock == enterBlock) {
                // entry and exit are from the same Block
                if ((_previousBlock != NULL) && (_previousBlock->getState() == Block::OCCUPIED)
                        && (getBlockLength(exitBlock) > _maxTrainLength)) {
                    _stoppingBlock = _previousBlock;
                    setStopByBlockOccupancy();
                } else {
                    setStopNow();
                }
            } else {
                // try to move train as far into the Section as it will comfortably fit
                int tstLength = getBlockLength(exitBlock);
                Block* tstBlock = exitBlock;
                int tstBlockSeq = _currentAllocatedSection->getSection()->getBlockSequenceNumber(tstBlock);
                while ((tstLength < _maxTrainLength) && (tstBlock != enterBlock)) {
                    int newSeqNumber = tstBlockSeq - 1;
                    if (_currentAllocatedSection->getDirection() == Section::REVERSE) {
                        newSeqNumber = tstBlockSeq + 1;
                    }
                    tstBlock = _currentAllocatedSection->getSection()->getBlockBySequenceNumber(newSeqNumber);
                    tstBlockSeq = newSeqNumber;
                    tstLength += getBlockLength(tstBlock);
                }
                if (tstLength < _maxTrainLength) {
                    setStopNow();
                } else if (tstBlock == enterBlock) {
                    // train fits, but needs all available Blocks
                    if ((_previousBlock != NULL) && (_previousBlock->getState() == Block::OCCUPIED)) {
                        _stoppingBlock = _previousBlock;
                        setStopByBlockOccupancy();
                    } else {
                        setStopNow();
                    }
                } else {
                    // train fits, and doesn't need all available Blocks
                    int xSeqNumber = tstBlockSeq - 1;
                    if (_currentAllocatedSection->getDirection() == Section::REVERSE) {
                        xSeqNumber = tstBlockSeq + 1;
                    }
                    _stoppingBlock = _currentAllocatedSection->getSection()->
                            getBlockBySequenceNumber(xSeqNumber);
                    setStopByBlockOccupancy();
                }
            }
        }
    } else {
        // train will fit, but no way to stop it reliably
        setStopNow();
    }
    if (task > NO_TASK) {
#if 1
        Runnable* waitForStop = new WaitForTrainToStop(task, this);
        Thread* tWait = new Thread(waitForStop, "Wait for stop " + getActiveTrain()->getActiveTrainName());
        tWait->start();
#endif
    }
}

/*public*/ void AutoActiveTrain::on_sensorChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName() == ("KnownState"))
 {
   handleStopSensorChange();
 }
}

#if 1
/*protected*/ /*synchronized*/ void AutoActiveTrain::executeStopTasks(int task) {
    if (task <= 0) {
        return;
    }
    switch (task) {
    case END_REVERSAL:
    {
            /* Reset _previousBlock to be the _currentBlock if we do a continious reverse otherwise the stop in block method fails
            to stop the loco in the correct block
             if the first block we come to has a stopped or held signal */
            _previousBlock = _currentBlock;
            _activeTrain->setTransitReversed(true);
            AllocatedSection* aSec = _activeTrain->reverseAllAllocatedSections();
            setEngineDirection();
            if ((_nextSection != NULL) && !isSectionInAllocatedList(_nextSection)) {
                ((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->queueScanOfAllocationRequests();
                break;
            }
            setupNewCurrentSignal(aSec);
            setSpeedBySignal();
            break;
    }
    case BEGINNING_RESET:
            if (_activeTrain->getResetWhenDone()) {
                if (_activeTrain->getReverseAtEnd()) {
                    /* Reset _previousBlock to be the _currentBlock if we do a continious
                    reverse otherwise the stop in block method fails  to stop the loco in the correct block
                     if the first block we come to has a stopped or held signal */
                    _previousBlock = _currentBlock;
                }
                if (_activeTrain->getDelayedRestart() == ActiveTrain::NODELAY) {
                    _activeTrain->setTransitReversed(false);
                    _activeTrain->resetAllAllocatedSections();
                    setEngineDirection();
                    if ((_nextSection != NULL) && !isSectionInAllocatedList(_nextSection)) {
                        ((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->queueScanOfAllocationRequests();
                        break;
                    }
                    setupNewCurrentSignal(NULL);
                    setSpeedBySignal();
                } else {
                    // then active train is delayed
                    _activeTrain->setTransitReversed(false);
                    _activeTrain->resetAllAllocatedSections();
                    setEngineDirection();
                    _activeTrain->setRestart();
                    if ((_nextSection != NULL) && !isSectionInAllocatedList(_nextSection)) {
                        ((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->queueScanOfAllocationRequests();
                        break;
                    }
                    setupNewCurrentSignal(NULL);
                    setSpeedBySignal();

                }
            } else {
                // dispatcher cancelled auto restart while train was stopping?
// djd debugging - may need code here
            }
            break;
        default:
           log->error("Request to execute unknown stop train task - " + QString::number(task));
            break;
    }
}
#endif
/*private*/ /*synchronized*/ void AutoActiveTrain::handleStopSensorChange() {
    if (_stopSensor->getState() == Sensor::ACTIVE) {
        _stopSensor->removePropertyChangeListener(_stopSensorListener);
        _stoppingBySensor = false;
        _stopSensorListener = NULL;
        _stopSensor = NULL;
        if (_needSetSpeed) {
            _needSetSpeed = false;
            setSpeedBySignal();
        } else {
            setStopNow();
        }
    }
}

/*private*/ /*synchronized*/ void AutoActiveTrain::setStopNow() {
    setTargetSpeedState(STOP_SPEED);
    if (_currentAllocatedSection == NULL) {  // this may occur if the train is not in the selected block when initially created and the signal is held.
        _activeTrain->setStatus(ActiveTrain::WAITING);
    } else if (_currentAllocatedSection->getNextSection() == NULL) {
        // wait for train to stop - this lets action items complete in a timely fashion
        waitUntilStopped();
        _activeTrain->setStatus(ActiveTrain::DONE);
    } else {
        _activeTrain->setStatus(ActiveTrain::WAITING);
    }
}

/*private*/ void AutoActiveTrain::setStopByBlockOccupancy() {
    // note: _stoppingBlock must be set before invoking this method
    //  verify that _stoppingBlock is actually occupied, if not stop immed
    if (_stoppingBlock->getState() == Block::OCCUPIED) {
        _stoppingByBlockOccupancy = true;
        setTargetSpeedState(RESTRICTED_SPEED);
    } else {
        setStopNow();
    }
}

/*private*/ /*synchronized*/ void AutoActiveTrain::setTargetSpeedState(int speedState) {
#if 1
    _autoEngineer->slowToStop(false);
    if (speedState > STOP_SPEED) {
        float speed = _speedRatio[speedState];
        if (speed > _maxSpeed) {
            speed = _maxSpeed;
        }
        _targetSpeed = speed * _speedFactor;
    } else if (useSpeedProfile) {
        _targetSpeed = _speedRatio[speedState];
        _stoppingUsingSpeedProfile = true;
        _autoEngineer->slowToStop(true);
    } else {
        _targetSpeed = _speedRatio[speedState];
        _autoEngineer->setHalt(true);
    }
#endif
}
//pass in speed as shown on dialogs, and convert to decimal speed needed by throttle
/*private*/ /*synchronized*/ void AutoActiveTrain::setTargetSpeedValue(float speed) {
    _autoEngineer->slowToStop(false);
  float mls = _controllingSignalMast->getSignalSystem()->getMaximumLineSpeed();
  float decSpeed = (speed / mls);
    if (decSpeed > 0.0f) {
        if (decSpeed > _maxSpeed) {
            decSpeed = _maxSpeed;
        }
        _targetSpeed = decSpeed * _speedFactor; //adjust for train's Speed Factor
    } else if (useSpeedProfile) {
        _targetSpeed = decSpeed;
        _stoppingUsingSpeedProfile = true;
        _autoEngineer->slowToStop(true);
    } else {
        _targetSpeed = 0.0f;
        _autoEngineer->setHalt(true);
    }
}
/*private*/ int AutoActiveTrain::getBlockLength(Block* b) {
    if (b == NULL) {
        return (0);
    }
    float fLength = b->getLengthMm() / (float) ((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getScale()->getScaleFactor();
    if (((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getUseScaleMeters()) {
        return (int) (fLength * 0.001f);

    }
    return (int) (fLength * 0.00328084f);
}

/**
 * Initiates running in manual mode with external throttle This method is
 * triggered by an action in the Transit The throttle in use for automatic
 * operation is dispatched
 */
/*protected*/ void AutoActiveTrain::initiateWorking() {
    if (_activeTrain->getStatus() != ActiveTrain::WORKING) {
        if (_autoEngineer != NULL) {
            _autoEngineer->setHalt(true);
            waitUntilStopped();
            _autoEngineer->abort();
            InstanceManager::throttleManagerInstance()->releaseThrottle(_throttle, (ThrottleListener*)this);
            _autoEngineer = NULL;
            _throttle = NULL;
        }
        _activeTrain->setMode(ActiveTrain::MANUAL);
        _activeTrain->setStatus(ActiveTrain::WORKING);
    }
}

/**
 * Returns when train is stopped Note: Provides for _autoEngineer becoming
 * NULL during wait Ties up the current autoActiveTrain thread
 */
/*protected*/ void AutoActiveTrain::waitUntilStopped() {
    bool doneWaiting = false;
    while (!doneWaiting) {
        if (_autoEngineer != NULL) {
            doneWaiting = _autoEngineer->isStopped();
        } else {
            doneWaiting = true;
        }
        if (!doneWaiting) {
            try {
                //Thread.sleep(50);
          SleeperThread::msleep(50);
            } catch (InterruptedException e) {
                // ignore this exception
            }
        }
    }
}

/**
 * Resumes automatic running after a working session using an external
 * throttle This method is triggered by the dispatcher hitting the "Resume
 * Auto Running" button A new throttle is acquired to allow automatic
 * running to resume
 */
/*protected*/ void AutoActiveTrain::resumeAutomaticRunning() {
    if ((_activeTrain->getStatus() == ActiveTrain::WORKING)
            || (_activeTrain->getStatus() == ActiveTrain::READY)) {
        _autoTrainAction->cancelDoneSensor();
        if (initialize()) {
            _resumingAutomatic = true;
        } else {
           log->error("Failed to initialize throttle when resuming automatic mode.");
        }
    }
}
#if 1
/**
 * Pauses the auto active train for a specified number of fast clock minutes
 * Pausing operation is performed in a separate thread
 */
/*public*/ Thread* AutoActiveTrain::pauseTrain(int fastMinutes) {
    if (_pausingActive) {
        // if a pause train thread is currently active, ignore this call
        return (NULL);
    }
    Runnable* pauseTrain = new PauseTrain(fastMinutes, this);
    Thread* tPause = new Thread(pauseTrain, "pause train " + _activeTrain->getTrainName());
    tPause->start();
    return tPause;
}

/*public*/ void AutoActiveTrain::terminate() {
    // here add code to stop the train and release its throttle if it is in autoRun
    while (_activeHornThreads > 0) {
        try {
            SleeperThread::msleep(50);
        } catch (InterruptedException e) {
            // ignore this exception
        }
    }
    _autoTrainAction->clearRemainingActions();
    if (_autoEngineer != NULL) {
        _autoEngineer->setHalt(true);
        try {
            SleeperThread::msleep(50);
        } catch (InterruptedException e) {
            // ignore this exception
        }
        waitUntilStopped();
        _autoEngineer->abort();
        InstanceManager::throttleManagerInstance()->releaseThrottle(_throttle, this);
    }
}

/*public*/ void AutoActiveTrain::dispose() {
    if (_controllingSignalMast != NULL && _conSignalMastListener != NULL) {
        _controllingSignalMast->removePropertyChangeListener(_conSignalMastListener);
    }
    _controllingSignalMast = NULL;
    _conSignalMastListener = NULL;
}

// _________________________________________________________________________________________
// This class waits for train stop in a separate thread
//class WaitForTrainToStop implements Runnable {

//    /*public*/ WaitForTrainToStop(int task) {
//        _task = task;
//    }

//    @Override
    /*public*/ void WaitForTrainToStop::run() {
        bool waitingOnTrain = true;
        try {
            while (waitingOnTrain) {
                if ((aat->getAutoEngineer() != NULL) && (aat->getAutoEngineer()->isStopped())) {
                    waitingOnTrain = false;
                } else {
                    SleeperThread::msleep(_delay);
                }
            }
            aat->executeStopTasks(_task);
        } catch (InterruptedException e) {
            // interrupting will cause termination without executing the task
        }
    }
//    private int _delay = 91;
//    private int _task = 0;
//}

// _________________________________________________________________________________________
// This class pauses the train in a separate thread
//  Train is stopped, then restarted after specified number of fast Minutes have elapsed
//class PauseTrain implements Runnable {

//    /**
//     * A runnable that executes a pause train for a specified number of Fast
//     * Clock minutes
//     */
//    /*public*/ PauseTrain(int fastMinutes) {
//        _fastMinutes = fastMinutes;
//    }

//    @Override
    /*public*/ void PauseTrain::run() {
        // set to pause at a fast ramp rate
        aat->_pausingActive = true;
        _savedTargetSpeed = aat->getTargetSpeed();
        _savedRampRate = aat->getRampRate();
        aat->setCurrentRampRate(AutoActiveTrain::RAMP_FAST);
        aat->stopInCurrentSection(AutoActiveTrain::NO_TASK);
        // wait for train to stop
        bool waitNow = true;
        bool keepGoing = true;
        while (waitNow) {
            try {
                SleeperThread::msleep(101);
                if (aat->_autoEngineer != NULL) {
                    if (aat->_autoEngineer->isStopped()) {
                        waitNow = false;
                    }
                } else {
                    waitNow = false;
                }
            } catch (InterruptedException e) {
               aat->log->error("InterruptedException while watiting to stop for pause - " + e.getMessage());
                waitNow = false;
                keepGoing = false;
            }
        }
        aat->_activeTrain->setStatus(ActiveTrain::PAUSED);
        if (keepGoing) {
            // wait for specified fast clock time
            Timebase* _clock = (Timebase*)InstanceManager::getDefault("Timebase");
            PropertyChangeListener* _clockListener = NULL;
//            _clock->addMinuteChangeListener(_clockListener
//                    = new PropertyChangeListener() {
//                //@Override
//                        /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                            _fastMinutes--;
//                        }
//                    });
            _clock->addMinuteChangeListener(this);
            // wait for fast minutes to tick away
            waitNow = true;
            while (waitNow) {
                try {
                    SleeperThread::msleep(501);
                    if (_fastMinutes <= 0) {
                        waitNow = false;
                    }
                } catch (InterruptedException e) {
                   aat->log->error("InterruptedException while waiting when paused - " + e.getLocalizedMessage());
                    keepGoing = false;
                }
            }
            _clock->removeMinuteChangeListener(this);
        }
        aat->_pausingActive = false;
        if (keepGoing) {
            // this thread was not interrupted
            //   resume running - restore speed, status, and ramp rate
            aat->setCurrentRampRate(_savedRampRate);
            aat->setTargetSpeed(_savedTargetSpeed);
            aat->_activeTrain->setStatus(ActiveTrain::RUNNING);
            aat->setSpeedBySignal();
        }
    }
//    private int _fastMinutes = 0;
//    private float _savedTargetSpeed = 0.0f;
//    private int _savedRampRate = RAMP_NONE;
//}
#endif
// _________________________________________________________________________________________
// This class runs a throttle to control the train in a separate thread.
// (This class started from code by Pete Cressman contained in Warrant.java.)
//class AutoEngineer implements Runnable {

    AutoEngineer::AutoEngineer(AutoActiveTrain* aat) {
 log = new Logger("AutoEngineer");
 this->aat = aat;
 // operational instance variables and flags
 _abort = false;
 _halt = false;  // halt/resume from user's control
 _halted = false; // true if previously halted
 _slowToStop = false;
 _currentSpeed = 0.0f;
 _lastBlock = NULL;
 _speedIncrement = 0.0f  ; //will be recalculated
}


    //@Override
    /*public*/ void AutoEngineer::run() {
        _abort = false;
        setHalt(false);
        slowToStop(false);

        //calculate speed increment to use in each minInterval time
        _speedIncrement = (100.0f / (((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getFullRampTime() / ((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getMinThrottleInterval())
                / aat->_currentRampRate) / 100.0f;
       log->debug(tr("%1: _speedIncrement=%2").arg(  aat->_activeTrain->getTrainName()).arg( _speedIncrement));

        // send direction to train
       log->debug(tr("%1: AutoEngineer.setIsForward(%2)").arg( aat->_activeTrain->getTrainName()).arg(aat-> _forward));
        aat->_throttle->setIsForward(aat->_forward);

        // Give command station a chance to handle direction command
        //try { Thread.sleep(((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame")).getMinThrottleInterval() * 2); } catch(Exception ex) {}
        SleeperThread::sleep(((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getMinThrottleInterval() * 2);

//            setSpeedStep(aat->_throttle->getSpeedStepMode());
        aat->_throttle->setSpeedSetting(_currentSpeed);
//            _ramping = false;
        // this is the running loop, which adjusts speeds, including stop
        while (!_abort) {
            if (_halt && !_halted) {
//                    if (useSpeedProfile) {
//                        re.getSpeedProfile().cancelSpeedChange();
//                    }
                aat->_throttle->setSpeedSetting(0.0f);
                _currentSpeed = 0.0f;
                _halted = true;
            } else if (_slowToStop) {
//                    re.getSpeedProfile().setExtraInitialDelay(1500f);
//                    re.getSpeedProfile().changeLocoSpeed(_throttle, _currentBlock, _targetSpeed);
                _currentSpeed = aat->_throttle->getSpeedSetting();
                if (aat->_currentBlock != _lastBlock) {
                    _lastBlock = aat->_currentBlock;
//                        re.getSpeedProfile().setExtraInitialDelay(1500f);
//                        re.getSpeedProfile().changeLocoSpeed(_throttle, _currentBlock, _targetSpeed);
                } else {
                    if (_currentSpeed <= aat->_targetSpeed) {
                        _halted = true;
                        _slowToStop = false;
                    }
                }
            } else if (!_halt) {
                // change direction if needed
                if (aat->_throttle->getIsForward() != aat->_forward) {
                   log->debug(tr("(AutoEngineer.setIsForward(%1), was %2 for %3").arg(aat->_forward).arg( aat->_throttle->getIsForward()).arg( aat->_throttle->getLocoAddress()->toString()));
                    aat->_throttle->setIsForward(aat->_forward);

                    // Give command station a chance to handle reversing.
                    //try { Thread.sleep(((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame")).getMinThrottleInterval() * 2); } catch(Exception ex) {}
                SleeperThread::msleep(((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getMinThrottleInterval() * 2);
                }
                // test if need to change speed
                if (qAbs(_currentSpeed - aat->_targetSpeed) > 0.001) {
                    if (aat->_currentRampRate == aat->RAMP_NONE) {
                        // set speed immediately
                        _currentSpeed = aat->_targetSpeed;
                        aat->_throttle->setSpeedSetting(_currentSpeed);
                        //                        } else if (!_ramping) {
                        //                            // initialize ramping
                        //                            _ramping = true;
                        //                            _rampCount = 1;
                        //                            _rampTargetCount = _targetCount[_currentRampRate];
                    } else {
                        // ramping the speed
                        //                            _rampCount++;
                        //                            if (_rampCount > _rampTargetCount) {
                        // step up the speed
                        if (_currentSpeed < aat->_targetSpeed) {
                            //                                    if (useSpeedProfile) {
                            //                                        re.getSpeedProfile().cancelSpeedChange();
                            //                                    }
                            // ramp up
                            _currentSpeed += _speedIncrement;
                            if (_currentSpeed >= aat->_targetSpeed) {
                                _currentSpeed = aat->_targetSpeed;
                                //                                        _ramping = false;
                                //                                    } else {
                                //                                        _rampCount = 0;
                            }
//                                aat->_throttle->setSpeedSetting(_currentSpeed);
                        } else {
                            // step down the speed
                            //                                    if (useSpeedProfile) {
                            //                                        re.getSpeedProfile().changeLocoSpeed(_throttle, _currentAllocatedSection->getSection(), _targetSpeed);
                            //                                        _currentSpeed = _targetSpeed;
                            //                                    } else {
                            // ramp down
                            _currentSpeed -= _speedIncrement;
                            if (_currentSpeed <= aat->_targetSpeed) {
                                _currentSpeed = aat->_targetSpeed;
                                //                                            _ramping = false;
                                //                                        } else {
                                //                                            _rampCount = 0;
                            }
//                                aat->_throttle->setSpeedSetting(_currentSpeed);
                            //                                    } // if useSpeedProfile
                        }
                        //                            } // if rampcount
                        aat->_throttle->setSpeedSetting(_currentSpeed);
                    } //ramping
                } //if currentSpeed != targetSpeed
            }
//                if (useSpeedProfile && _currentAllocatedSection != NULL && _currentAllocatedSection != _lastAllocatedSection) {
//                    _lastAllocatedSection = _currentAllocatedSection;
//                }
            // Give other threads a chance to work
            //try { Thread.sleep(((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame")).getMinThrottleInterval()); } catch(Exception ex) {}
 SleeperThread::msleep(((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getMinThrottleInterval() * 2);

        } //while !abort
        // shut down
    }


    /*public*/ /*synchronized*/ void AutoEngineer::slowToStop(bool toStop) {
        _slowToStop = toStop;
        if (!toStop) {
            setHalt(toStop);
        }
    }

    /**
     * Flag from user's control Note: Halt here invokes immediate stop.
     */
    /*public*/ /*synchronized*/ void AutoEngineer::setHalt(bool halt) {
        _halt = halt;
        if (!_halt) {
            _halted = false;
        }
    }

    /**
     * set the train speed directly, bypassing ramping,
     * Input is float speed (0.0 - 1.0)
     */
    /*public*/ /*synchronized*/ void AutoEngineer::setSpeedImmediate(float speed) {
//       log->trace(tr("%1: setting speed directly to %2%").arg( aat->_activeTrain->getTrainName()).arg( (int) (speed * 100)));
        aat->_targetSpeed = speed;
        _currentSpeed = speed + _speedIncrement; // close enough to force change, but skip ramping
//            aat->_throttle->setSpeedSetting(_currentSpeed);
    }

    /**
     * Allow user to test if train is moving or stopped
     */
    /*public*/ /*synchronized*/ bool AutoEngineer::isStopped() {
        if (_currentSpeed > 0.01f) {
            return false;
        }
        return true;
    }

    /**
     * Allow user to test if train is moving at its current requested speed
     */
    /*public*/ /*synchronized*/ bool AutoEngineer::isAtSpeed() {
        if (qAbs(_currentSpeed - aat->_targetSpeed) > 0.01) {
            return false;
        }
        return true;
    }

    /**
     * Flag from user to end run
     */
    /*public*/ void AutoEngineer::abort() {
        _abort = true;
    }

    /*protected*/ void AutoEngineer::setFunction(int cmdNum, bool isSet) {
        switch (cmdNum) {
            case 0:
                aat->_throttle->setF0(isSet);
                break;
            case 1:
                aat->_throttle->setF1(isSet);
                break;
            case 2:
                aat->_throttle->setF2(isSet);
                break;
            case 3:
                aat->_throttle->setF3(isSet);
                break;
            case 4:
                aat->_throttle->setF4(isSet);
                break;
            case 5:
                aat->_throttle->setF5(isSet);
                break;
            case 6:
                aat->_throttle->setF6(isSet);
                break;
            case 7:
                aat->_throttle->setF7(isSet);
                break;
            case 8:
                aat->_throttle->setF8(isSet);
                break;
            case 9:
                aat->_throttle->setF9(isSet);
                break;
            case 10:
                aat->_throttle->setF10(isSet);
                break;
            case 11:
                aat->_throttle->setF11(isSet);
                break;
            case 12:
                aat->_throttle->setF12(isSet);
                break;
            case 13:
                aat->_throttle->setF13(isSet);
                break;
            case 14:
                aat->_throttle->setF14(isSet);
                break;
            case 15:
                aat->_throttle->setF15(isSet);
                break;
            case 16:
                aat->_throttle->setF16(isSet);
                break;
            case 17:
                aat->_throttle->setF17(isSet);
                break;
            case 18:
                aat->_throttle->setF18(isSet);
                break;
            case 19:
                aat->_throttle->setF19(isSet);
                break;
            case 20:
                aat->_throttle->setF20(isSet);
                break;
            case 21:
                aat->_throttle->setF21(isSet);
                break;
            case 22:
                aat->_throttle->setF22(isSet);
                break;
            case 23:
                aat->_throttle->setF23(isSet);
                break;
            case 24:
                aat->_throttle->setF24(isSet);
                break;
            case 25:
                aat->_throttle->setF25(isSet);
                break;
            case 26:
                aat->_throttle->setF26(isSet);
                break;
            case 27:
                aat->_throttle->setF27(isSet);
                break;
            case 28:
                aat->_throttle->setF28(isSet);
                break;
        }
    }
//};
/** routine to convert ramp rate name, stored as a string into the constant value assigned
 *
 * @param rampRate - name of ramp rate, such as "RAMP_FAST"
 * @return integer representing a ramprate constant value
 */

/*public*/ /*static*/ int AutoActiveTrain::getRampRateFromName(QString rampRate) {
    if (rampRate==(tr("RAMP_FAST"))) {
        return RAMP_FAST;
    } else if (rampRate == (tr("RAMP_MEDIUM"))) {
        return RAMP_MEDIUM;
    } else if (rampRate == (tr("RAMP_MED_SLOW"))) {
        return RAMP_MED_SLOW;
    } else if (rampRate == (tr("RAMP_SLOW"))) {
        return RAMP_SLOW;
    }
    return RAMP_NONE;
}

/*public*/ void AutoActiveTrain::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName() == ("Appearance")) {
        // controlling signal has changed appearance
        setSpeedBySignal();
        if (_stoppingForStopSignal && (_targetSpeed > 0.0)) {
            cancelStopInCurrentSection();
            _stoppingForStopSignal = false;
        }
    }
    if (e->getPropertyName() == ("Aspect"))
    {
       // controlling signal has changed appearance
       if (_stoppingForStopSignal && (_targetSpeed > 0.0)) {
           cancelStopInCurrentSection();
           _stoppingForStopSignal = false;
       }
       setSpeedBySignal();
    } else if (e->getPropertyName() == ("Held")) {
       if (!( e->getNewValue().toBool())) {
           cancelStopInCurrentSection();
           _stoppingForStopSignal = false;
       }
       setSpeedBySignal();
   }
}
