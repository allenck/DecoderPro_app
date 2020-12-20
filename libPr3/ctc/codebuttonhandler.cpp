#include "codebuttonhandler.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "turnoutlock.h"
#include "signaldirectionindicatorsinterface.h"
#include "signaldirectionlever.h"
#include "switchdirectionindicators.h"
#include "trafficlockinginfo.h"
#include "switchdirectionlever.h"
#include "lockedroutesmanager.h"
#include "fleeting.h"
#include "codebuttonsimulator.h"
#include "switchdirectionlever.h"
#include "callon.h"
#include "turnoutlock.h"
#include "indicationlockingsignals.h"
#include "trafficlocking.h"


CodeButtonHandler::CodeButtonHandler(QObject *parent) : QObject(parent)
{

}
/**
 * This is the "master" class that handles everything when a code button is
 * pressed.  As such, it has a LOT of external data passed into it's constructor,
 * and operates and modifies all objects it contains on a dynamic basis both
 * when the button is pressed, and when external events happen that affect this
 * object.
 * <p>
 * Notes:
 * <p>
 * Changing both signal direction to non signals normal and switch direction at the same time "is allowed".
 * Lock/Unlock is the LOWEST priority!  Call on is the HIGHEST priority.
 * <p>
 * As of V1.04 of the CTC system, preconditioning (a.k.a. stacking) is supported.  It is enabled
 * by setting the internal sensor (automatically created) "IS:PRECONDITIONING_ENABLED" to active.
 * Any other value inactivates this feature.  For example, the user can create a toggle
 * switch to activate / inactivate it.
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019, 2020
 */
///*public*/ class CodeButtonHandler {


    /*private*/ /*static*/ Sensor* CodeButtonHandler::initializePreconditioningEnabledSensor() {
        Sensor* returnValue = InstanceManager::sensorManagerInstance()->newSensor("IS:PRECONDITIONING_ENABLED", nullptr); // NOI18N
        int knownState = returnValue->getKnownState();
        if (Sensor::ACTIVE != knownState && Sensor::INACTIVE != knownState) {
            try {returnValue->setKnownState(Sensor::INACTIVE); } catch (JmriException ex) {
                LoggerFactory::getLogger("CodeButtonHandler")->debug("Sensor problem, preconditioning won't work.");          // NOI18N
            }
        }
        return returnValue;
    }
    /*private*/ /*static*/ /*final*/ Sensor* CodeButtonHandler::_mPreconditioningEnabledSensor = initializePreconditioningEnabledSensor();

    /*public*/ CodeButtonHandler::CodeButtonHandler(   bool turnoutLockingOnlyEnabled,                              // If this is NOT an O.S. section, but only a turnout lock, then this is true.
                                LockedRoutesManager* lockedRoutesManager,
                                QString userIdentifier,
                                int uniqueID,
                                NBHSensor* codeButtonInternalSensor,                             // Required
                                int codeButtonDelayInMilliseconds,                              // If 0, REAL code button, if > 0, tower operations (simulated code button).
                                NBHSensor* osSectionOccupiedExternalSensor,                      // Required, if ACTIVE prevents turnout, lock or call on from occuring.
                                NBHSensor* osSectionOccupiedExternalSensor2,                     // Optional, if ACTIVE prevents turnout, lock or call on from occuring.
                                SignalDirectionIndicators* signalDirectionIndicators,   // Required
                                SignalDirectionLever* signalDirectionLever,
                                SwitchDirectionIndicators* switchDirectionIndicators,
                                SwitchDirectionLever* switchDirectionLever,
                                Fleeting* fleeting,                                              // If null, then ALWAYS fleeting!
                                CallOn* callOn,
                                TrafficLocking* trafficLocking,
                                TurnoutLock* turnoutLock,
                                IndicationLockingSignals* indicationLockingSignals, QObject *parent)
    : QObject(parent)
   {            // Needed for check of adjacent OS Section(s), and optionally turnoutLock.
#if 1
        signalDirectionIndicators->setCodeButtonHandler(this);
        _mTurnoutLockingOnlyEnabled = turnoutLockingOnlyEnabled;
        _mLockedRoutesManager = lockedRoutesManager;
        _mUserIdentifier = userIdentifier;
        _mUniqueID = uniqueID;
        _mSignalDirectionIndicators = signalDirectionIndicators;
        _mSignalDirectionLever = signalDirectionLever;
        _mSwitchDirectionIndicators = switchDirectionIndicators;
        _mSwitchDirectionLever = switchDirectionLever;
        _mFleeting = fleeting;
        _mCallOn = callOn;
        _mTrafficLocking = trafficLocking;
        _mTurnoutLock = turnoutLock;
        _mIndicationLockingSignals = indicationLockingSignals;
        _mCodeButtonInternalSensor = codeButtonInternalSensor;
        _mCodeButtonInternalSensor->setKnownState(Sensor::INACTIVE);
        //_mCodeButtonInternalSensorPropertyChangeListener = (PropertyChangeEvent e) -> { codeButtonStateChange(e); };
        _mCodeButtonInternalSensorPropertyChangeListener= new CodeButtonStateChangeListener(this);
        _mCodeButtonInternalSensor->addPropertyChangeListener(_mCodeButtonInternalSensorPropertyChangeListener);

        //_mOSSectionOccupiedExternalSensorPropertyChangeListener = (PropertyChangeEvent e) -> { osSectionPropertyChangeEvent(e); };
        _mOSSectionOccupiedExternalSensorPropertyChangeListener = new OsSectionPropertyChangeEventListener(this);
        _mOSSectionOccupiedExternalSensor = osSectionOccupiedExternalSensor;
        _mOSSectionOccupiedExternalSensor->addPropertyChangeListener(_mOSSectionOccupiedExternalSensorPropertyChangeListener);

// NO property change for this, only used for turnout locking:
        _mOSSectionOccupiedExternalSensor2 = osSectionOccupiedExternalSensor2;

        if (codeButtonDelayInMilliseconds > 0) { // SIMULATED code button:
            _mCodeButtonSimulator = new CodeButtonSimulator(codeButtonDelayInMilliseconds,
                                                            _mCodeButtonInternalSensor,
                                                            _mSwitchDirectionLever,
                                                            _mSignalDirectionLever,
                                                            _mTurnoutLock);
        } else {
            _mCodeButtonSimulator = nullptr;
        }
#endif
    }
#if 1
    /**
     * This routine SHOULD ONLY be called by CTCMain when the CTC system is shutdown
     * in order to clean up all resources prior to a restart.  Nothing else should
     * call this.
     */
    /*public*/ void CodeButtonHandler::removeAllListeners() {
//  Remove our registered listeners first:
        _mCodeButtonInternalSensor->removePropertyChangeListener(_mCodeButtonInternalSensorPropertyChangeListener);
        _mOSSectionOccupiedExternalSensor->removePropertyChangeListener(_mOSSectionOccupiedExternalSensorPropertyChangeListener);
//  Give each object a chance to remove theirs also:
        if (_mSignalDirectionIndicators != nullptr) _mSignalDirectionIndicators->removeAllListeners();
        if (_mSignalDirectionLever != nullptr) _mSignalDirectionLever->removeAllListeners();
        if (_mSwitchDirectionIndicators != nullptr) _mSwitchDirectionIndicators->removeAllListeners();
        if (_mSwitchDirectionLever != nullptr) _mSwitchDirectionLever->removeAllListeners();
        if (_mFleeting != nullptr) _mFleeting->removeAllListeners();
        if (_mCallOn != nullptr) _mCallOn->removeAllListeners();
        if (_mTrafficLocking != nullptr) _mTrafficLocking->removeAllListeners();
        if (_mTurnoutLock != nullptr) _mTurnoutLock->removeAllListeners();
        if (_mIndicationLockingSignals != nullptr) _mIndicationLockingSignals->removeAllListeners();
        if (_mCodeButtonSimulator != nullptr) _mCodeButtonSimulator->removeAllListeners();
    }

    /**
     * SignalDirectionIndicators calls us here when time locking is done.
     */
    /*public*/ void CodeButtonHandler::cancelLockedRoute() {
        _mLockedRoutesManager->cancelLockedRoute(_mLockedRoute);     // checks passed parameter for null for us
        _mLockedRoute = nullptr;       // Not valid anymore.
    }

    /*public*/ bool CodeButtonHandler::uniqueIDMatches(int uniqueID) { return _mUniqueID == uniqueID; }
    /*public*/ NBHSensor* CodeButtonHandler::getOSSectionOccupiedExternalSensor() { return _mOSSectionOccupiedExternalSensor; }

    /*private*/ void CodeButtonHandler::osSectionPropertyChangeEvent(PropertyChangeEvent* e) {
        if (isPrimaryOSSectionOccupied()) { // MUST ALWAYS process PRIMARY OS occupied state change to ACTIVE (It's the only one that comes here anyways!)
            if (_mFleeting != nullptr && !_mFleeting->isFleetingEnabled()) { // Impliment "stick" here:
                _mSignalDirectionIndicators->forceAllSignalsToHeld();
            }
            _mSignalDirectionIndicators->osSectionBecameOccupied();
        }
        else { // Process pre-conditioning if available:
            if (_mPreconditioningData->_mCodeButtonPressed) {
                doCodeButtonPress();
                _mPreconditioningData->_mCodeButtonPressed = false;
            }
        }
    }
#endif
    /*public*/ void CodeButtonHandler::externalLockTurnout() {
        if (_mTurnoutLock != nullptr) _mTurnoutLock->externalLockTurnout();
    }
#if 1
    /*private*/ void CodeButtonHandler::codeButtonStateChange(PropertyChangeEvent* e) {
        if (e->getPropertyName() == ("KnownState") && (int)e->getNewValue().toInt() == Sensor::ACTIVE) {
//  NOTE: If the primary O.S. section is occupied, you CANT DO ANYTHING via a CTC machine, except:
//  Preconditioning: IF the O.S. section is occupied, then it is a pre-conditioning request:
            if (isPrimaryOSSectionOccupied()) {
                if (Sensor::ACTIVE == _mPreconditioningEnabledSensor->getKnownState()) {  // ONLY if turned on:
                    _mPreconditioningData->_mSignalDirectionLeverWas = getCurrentSignalDirectionLever(false);
                    _mPreconditioningData->_mSwitchDirectionLeverWas = getSwitchDirectionLeverRequestedState(false);
                    _mPreconditioningData->_mCodeButtonPressed = true;   // Do this LAST so that the above variables are stable in this object,
                                                                        // in case there is a multi-threading issue (yea, lock it would be better,
                                                                        // but this is good enough for now!)
                }
            }
            doCodeButtonPress();
        }
    }

    /*private*/ void CodeButtonHandler::doCodeButtonPress() {
        if (_mSignalDirectionIndicators->isRunningTime()) return;    // If we are running time, IGNORE all requests from the user:
        possiblyAllowLockChange();                              // MUST unlock first, otherwise if dispatcher wanted to unlock and change switch state, it wouldn't!
        possiblyAllowTurnoutChange();                           // Change turnout
//  IF the call on was accepted, then we DON'T attempt to change the signals to a more favorable
//  aspect here.  Additionally see the comments above CallOn.java/"codeButtonPressed" for an explanation
//  of a "fake out" that happens in that routine, and it's effect on this code here:
        if (!possiblyAllowCallOn()) {                           // NO call on occured or was allowed or requested:
            possiblyAllowSignalDirectionChange();               // Slave to it!
        }
    }

// Returns true if call on was actually done, else false
    /*private*/ bool CodeButtonHandler::possiblyAllowCallOn() {
        bool returnStatus = false;
        if (allowCallOnChange()) {
            QSet<Sensor*> sensors = QSet<Sensor*>();                  // Initial O.S. section sensor(s):
            sensors.insert(_mOSSectionOccupiedExternalSensor->getBean());   // Always.
//  If there is a switch direction indicator, and it is reversed, then add the other sensor if valid here:
            if (_mSwitchDirectionIndicators != nullptr && _mSwitchDirectionIndicators->getLastIndicatorState() == CTCConstants::SWITCHREVERSED) {
                if (_mOSSectionOccupiedExternalSensor2->valid()) sensors.insert(_mOSSectionOccupiedExternalSensor2->getBean());
            }
//  NOTE: We DO NOT support preconditioning of call on, ergo false passed to "getCurrentSignalDirectionLever"
            TrafficLockingInfo* trafficLockingInfo = _mCallOn->codeButtonPressed(sensors, _mUserIdentifier, _mSignalDirectionIndicators, getCurrentSignalDirectionLever(false));
            if (trafficLockingInfo->_mLockedRoute != nullptr) { // Was allocated:
                _mLockedRoute = trafficLockingInfo->_mLockedRoute;
            }
            returnStatus = trafficLockingInfo->_mReturnStatus;
        }
        if (_mCallOn != nullptr) _mCallOn->resetToggle();
        return returnStatus;
    }

/*
Rules from http://www.ctcparts.com/about.htm
    "An important note though for programming logic is that the interlocking limits
must be clear and all power switches within the interlocking limits aligned
appropriately for the back to train route for this feature to activate."
*/
    /*private*/ bool CodeButtonHandler::allowCallOnChange() {
// Safety checks:
        if (_mCallOn == nullptr) return false;
// Rules:
        if (isPrimaryOSSectionOccupied()) return false;
        if (_mSignalDirectionIndicators->isRunningTime()) return false;
        if (_mSignalDirectionIndicators->getSignalsInTheFieldDirection() != CTCConstants::SIGNALSNORMAL) return false;
        if (!areOSSensorsAvailableInRoutes()) return false;
        return true;
    }

//  If it doesn't exist, this returns OUTOFCORRESPONDENCE, else return it's present state:
//  NOTE: IF a preconditioned input was available, it OVERRIDES actual Signal Direction Lever (which is ignored in this case).
    /*private*/ int CodeButtonHandler::getCurrentSignalDirectionLever(bool allowMergeInPreconditioning) {
        if (_mSignalDirectionLever == nullptr) return CTCConstants::OUTOFCORRESPONDENCE;
        if (allowMergeInPreconditioning && _mPreconditioningData->_mCodeButtonPressed) { // We can check and it is available:
            if (_mPreconditioningData->_mSignalDirectionLeverWas == CTCConstants::LEFTTRAFFIC
            || _mPreconditioningData->_mSignalDirectionLeverWas == CTCConstants::RIGHTTRAFFIC) { // Was valid:
                return _mPreconditioningData->_mSignalDirectionLeverWas;
            }
        }
        return _mSignalDirectionLever->getPresentSignalDirectionLeverState();
    }

    /*private*/ void CodeButtonHandler::possiblyAllowTurnoutChange() {
        if (allowTurnoutChange()) {
            int requestedState = getSwitchDirectionLeverRequestedState(true);
            notifyTurnoutLockObjectOfNewAlignment(requestedState);          // Tell lock object this is new alignment
            if (_mSwitchDirectionIndicators != nullptr) { // Safety:
                _mSwitchDirectionIndicators->codeButtonPressed(requestedState);  // Also sends commmands to move the points
            }
        }
    }

    /*private*/ bool CodeButtonHandler::allowTurnoutChange() {
// Safety checks:
// Rules:
        if (!_mSignalDirectionIndicators->signalsNormal()) return false;
        if (routeClearedAcross()) return false;               // Something was cleared thru, NO CHANGE
        if (isEitherOSSectionOccupied()) return false;
// 6/28/16: If the switch direction indicators are presently "OUTOFCORRESPONDENCE", IGNORE request, as we are presently working on a change:
        if (!switchDirectionIndicatorsInCorrespondence()) return false;
        if (!turnoutPresentlyLocked()) return false;
        if (!areOSSensorsAvailableInRoutes()) return false;
        return true;
    }

    /*private*/ void CodeButtonHandler::notifyTurnoutLockObjectOfNewAlignment(int requestedState) {
        if (_mTurnoutLock != nullptr) _mTurnoutLock->dispatcherCommandedState(requestedState);
    }

//  If it doesn't exist, this returns OUTOFCORRESPONDENCE, else return it's present state:
//  NOTE: IF a preconditioned input was available, it OVERRIDES actual Switch Direction Lever (which is ignored in this case).
    /*private*/ int CodeButtonHandler::getSwitchDirectionLeverRequestedState(bool allowMergeInPreconditioning) {
        if (_mSwitchDirectionLever == nullptr) return CTCConstants::OUTOFCORRESPONDENCE;
        if (allowMergeInPreconditioning && _mPreconditioningData->_mCodeButtonPressed) { // We can check and it is available:
            if (_mPreconditioningData->_mSwitchDirectionLeverWas == CTCConstants::SWITCHNORMAL
            || _mPreconditioningData->_mSwitchDirectionLeverWas == CTCConstants::SWITCHREVERSED) { // Was valid:
                return _mPreconditioningData->_mSwitchDirectionLeverWas;
            }
        }
        return _mSwitchDirectionLever->getPresentState();
    }

// If it doesn't exist, this returns true.
    /*private*/ bool CodeButtonHandler::switchDirectionIndicatorsInCorrespondence() {
        if (_mSwitchDirectionIndicators != nullptr) return _mSwitchDirectionIndicators->inCorrespondence();
        return true;
    }

    /*private*/ void CodeButtonHandler::possiblyAllowSignalDirectionChange() {
        if (allowSignalDirectionChangePart1()) {
            int presentSignalDirectionLever = getCurrentSignalDirectionLever(true);
            int presentSignalDirectionIndicatorsDirection = _mSignalDirectionIndicators->getPresentDirection();  // Object always exists!
            bool requestedChangeInSignalDirection = (presentSignalDirectionLever != presentSignalDirectionIndicatorsDirection);
// If Dispatcher is asking for a cleared signal direction:
            if (presentSignalDirectionLever != CTCConstants::SIGNALSNORMAL) {
                if (!requestedChangeInSignalDirection) return;  // If presentSignalDirectionLever is the same as the current state, DO NOTHING!
            }
// If user is trying to change direction, FORCE to "SIGNALSNORMAL" per Rick Moser response of 6/29/16:
            if (presentSignalDirectionLever == CTCConstants::LEFTTRAFFIC && presentSignalDirectionIndicatorsDirection == CTCConstants::RIGHTTRAFFIC)
                presentSignalDirectionLever = CTCConstants::SIGNALSNORMAL;
            else if (presentSignalDirectionLever == CTCConstants::RIGHTTRAFFIC && presentSignalDirectionIndicatorsDirection == CTCConstants::LEFTTRAFFIC)
                presentSignalDirectionLever = CTCConstants::SIGNALSNORMAL;

            if (allowSignalDirectionChangePart2(presentSignalDirectionLever)) {
// Tell SignalDirectionIndicators what the current requested state is:
                _mSignalDirectionIndicators->setPresentSignalDirectionLever(presentSignalDirectionLever);
                _mSignalDirectionIndicators->codeButtonPressed(presentSignalDirectionLever, requestedChangeInSignalDirection);
            }
        }
    }

    /*private*/ bool CodeButtonHandler::allowSignalDirectionChangePart1() {
// Safety Checks:
        if (_mSignalDirectionLever == nullptr) return false;
// Rules:
// 6/28/16: If the signal direction indicators are presently "OUTOFCORRESPONDENCE", IGNORE request, as we are presently working on a change:
        if (!_mSignalDirectionIndicators->inCorrespondence()) return false;
        if (!turnoutPresentlyLocked()) return false;
        return true;                                    // Allowed "so far".
    }

    /*private*/ bool CodeButtonHandler::allowSignalDirectionChangePart2(int presentSignalDirectionLever) {
// Safety Checks: (none so far)
// Rules:
        if (presentSignalDirectionLever != CTCConstants::SIGNALSNORMAL) {
// If asking for a route and these indicates an error (a conflict), DO NOTHING!
            if (!trafficLockingValid(presentSignalDirectionLever)) return false;       // Do NOTHING at this time!
        }
        return true;                                    // Allowed
    }

    /*private*/ bool CodeButtonHandler::trafficLockingValid(int presentSignalDirectionLever) {
// If asking for a route and it indicates an error (a conflict), DO NOTHING!
        if (_mTrafficLocking != nullptr) {
            TrafficLockingInfo* trafficLockingInfo = _mTrafficLocking->valid(presentSignalDirectionLever, _mFleeting->isFleetingEnabled());
            _mLockedRoute = trafficLockingInfo->_mLockedRoute;   // Can be null! This is the bread crumb trail when running time expires.
            return trafficLockingInfo->_mReturnStatus;
        }
        return true;        // Valid
    }

    /*private*/ void CodeButtonHandler::possiblyAllowLockChange() {
        if (allowLockChange()) _mTurnoutLock->codeButtonPressed();
    }

    /*private*/ bool CodeButtonHandler::allowLockChange() {
// Safety checks:
        if (_mTurnoutLock == nullptr) return false;
// Rules:
// Degenerate case: If we ONLY have a lock toggle switch, code button and lock indicator then:
// if these 3 are null and the provided signalDirectionIndocatorsObject is non functional, therefore ALWAYS allow it!
//      if (_mSignalDirectionIndicators->isNonfunctionalObject() && _mSignalDirectionLever == null && _mSwitchDirectionIndicators == null && _mSwitchDirectionLever == null) return true;
//  If this is a normal O.S. section, then if either is occupied, DO NOT allow unlock.
//  If this is NOT an O.S. section, but only a lock, AND the dispatcher is trying
//  to UNLOCK or LOCK this section, occupancy is not considered:
        if (!_mTurnoutLockingOnlyEnabled) { // Normal O.S. section:
            if (isEitherOSSectionOccupied()) return false;
        }
        if (!_mTurnoutLock->tryingToChangeLockStatus()) return false;
        if (routeClearedAcross()) return false;
        if (!_mSignalDirectionIndicators->signalsNormal()) return false;
        if (!switchDirectionIndicatorsInCorrespondence()) return false;
        if (!areOSSensorsAvailableInRoutes()) return false;
        return true;
    }

    /*private*/ bool CodeButtonHandler::routeClearedAcross() {
        if (_mIndicationLockingSignals != nullptr) return _mIndicationLockingSignals->routeClearedAcross();
        return false; // Default: Nothing to evaluate, nothing cleared thru!
    }

    /*private*/ bool CodeButtonHandler::turnoutPresentlyLocked() {
        if (_mTurnoutLock == nullptr) return true;     // Doesn't exist, assume locked so that anything can be done to it.
        return _mTurnoutLock->turnoutPresentlyLocked();
    }

//  For "isEitherOSSectionOccupied" and "isPrimaryOSSectionOccupied" below,
//  INCONSISTENT, UNKNOWN and OCCUPIED are all considered OCCUPIED(ACTIVE).
    /*private*/ bool CodeButtonHandler::isEitherOSSectionOccupied() {
        return _mOSSectionOccupiedExternalSensor->getKnownState() != Sensor::INACTIVE || _mOSSectionOccupiedExternalSensor2->getKnownState() != Sensor::INACTIVE;
    }

//  See "isEitherOSSectionOccupied" comment.
    /*private*/ bool CodeButtonHandler::isPrimaryOSSectionOccupied() {
        return _mOSSectionOccupiedExternalSensor->getKnownState() != Sensor::INACTIVE;
    }

    /*private*/ bool CodeButtonHandler::areOSSensorsAvailableInRoutes() {
        QSet<Sensor*> sensors = QSet<Sensor*>();
        sensors.insert(_mOSSectionOccupiedExternalSensor->getBean());
        if (_mOSSectionOccupiedExternalSensor2->valid()) sensors.insert(_mOSSectionOccupiedExternalSensor2->getBean());
        return _mLockedRoutesManager->checkRoute(sensors, _mUserIdentifier, "Turnout Check");
    }
#endif
