#include "signaldirectionindicators.h"
#include "fleeting.h"
#include <abstractsignalhead.h>
#include "abstractsignalmast.h"
#include "codebuttonhandler.h"

// /*public*/ /*final*/ class SignalDirectionIndicators implements SignalDirectionIndicatorsInterface {
    /*static*/ /*final*/ QSet<NBHSignal*> SignalDirectionIndicators::_mSignalsUsed = QSet<NBHSignal*>();
    /*public*/ /*static*/ void SignalDirectionIndicators::resetSignalsUsed() { _mSignalsUsed.clear(); }

    //@Override
    /*public*/ void SignalDirectionIndicators::setCodeButtonHandler(CodeButtonHandler* codeButtonHandler) { _mCodeButtonHandler = codeButtonHandler; }

    //@SuppressWarnings("LeakingThisInConstructor")   // NOI18N

/*  From: https://docs.oracle.com/javase/tutorial/collections/implementations/list.html
    CopyOnWriteArrayList is a List implementation backed up by a copy-on-write array.
    This implementation is similar in nature to CopyOnWriteArraySet. No synchronization
    is necessary, even during iteration, and iterators are guaranteed never to throw
    ConcurrentModificationException. This implementation is well suited to maintaining
    event-handler lists, in which change is infrequent, and traversal is frequent and
    potentially time-consuming.
*/
//  /*private*/ /*final*/ CopyOnWriteArrayList<TrafficDirection> _mTimeLockingChangeObservers = new CopyOnWriteArrayList<>();

    /*public*/ SignalDirectionIndicators::SignalDirectionIndicators(QString userIdentifier,
                                        NBHSensor* leftSensor,
                                        NBHSensor* normalSensor,
                                        NBHSensor* rightSensor,
                                        int codingTimeInMilliseconds,
                                        int timeLockingTimeInMilliseconds,
                                        CodeButtonHandlerData::TRAFFIC_DIRECTION trafficDirection,
                                        QList<NBHSignal*> signalListLeftRight,
                                        QList<NBHSignal*> signalListRightLeft,
                                        Fleeting* fleetingObject, SignalDirectionIndicatorsInterface *parent) {

// We need to give time to the ABS system to set signals.  See CALL to routine "allSignalsRedSetThemAllHeld", comments above that line:
        if (codingTimeInMilliseconds < 100) codingTimeInMilliseconds = 100;
        //_mTimeLockingTimerActionListener = (ActionEvent) -> { timeLockingDone(); };
        _mTimeLockingTimerActionListener = new TimeLockingTimerActionListener(this);
        _mTimeLockingTimer = new Timer(codingTimeInMilliseconds + timeLockingTimeInMilliseconds, _mTimeLockingTimerActionListener);
        _mTimeLockingTimer->setRepeats(false);
        //_mCodingTimeTimerActionListener = (ActionEvent) -> { codingTimeDone(); };
        _mCodingTimeTimerActionListener = new CodingTimeTimerActionListener(this);
        _mCodingTimeTimer = new Timer(codingTimeInMilliseconds, _mCodingTimeTimerActionListener);
        _mCodingTimeTimer->setRepeats(false);
        try {
            _mLeftSensor = leftSensor;
            _mNormalSensor = normalSensor;
            _mRightSensor = rightSensor;
//  Partially plagerized from GUI code:
            bool leftTrafficDirection = trafficDirection != CodeButtonHandlerData::TRAFFIC_DIRECTION::RIGHT;
            bool rightTrafficDirection = trafficDirection != CodeButtonHandlerData::TRAFFIC_DIRECTION::LEFT;

            bool entriesInLeftRightTrafficSignalsList = !signalListLeftRight.isEmpty();
            bool entriesInRightLeftTrafficSignalsList = !signalListRightLeft.isEmpty();

            if (leftTrafficDirection && !entriesInRightLeftTrafficSignalsList) { throw  CTCException("SignalDirectionIndicators", userIdentifier, tr("invalid combination"), tr("Left sensor exists but no entries in right to left signals.")); }     // NOI18N
            if (rightTrafficDirection && !entriesInLeftRightTrafficSignalsList) { throw  CTCException("SignalDirectionIndicators", userIdentifier, tr("invalid combination"), tr("Right sensor exists but no entries in left to right signals.")); }    // NOI18N
            if (!leftTrafficDirection && entriesInRightLeftTrafficSignalsList) { throw  CTCException("SignalDirectionIndicators", userIdentifier, tr("invalid combination"), tr("leftSensor is not specified, but there are entry(s) in right to left signals.")); }      // NOI18N
            if (!rightTrafficDirection && entriesInLeftRightTrafficSignalsList) { throw  CTCException("SignalDirectionIndicators", userIdentifier, tr("invalid combination"), tr("rightSensor is not specified, but there are entry(s) in left to right signals.")); }    // NOI18N

            for (NBHSignal* signal : signalListLeftRight) {
                new SignalHeadPropertyChangeListenerMaintainer(signal); // Lazy, constructor does EVERYTHING and leaves a bread crumb trail to this object.
                _mSignalListLeftRight.append(signal);
                addSignal(userIdentifier, signal);
            }

            for (NBHSignal* signal : signalListRightLeft) {
                new SignalHeadPropertyChangeListenerMaintainer(signal); // Lazy, constructor does EVERYTHING and leaves a bread crumb trail to this object.
                _mSignalListRightLeft.append(signal);
                addSignal(userIdentifier, signal);
            }

            _mFleetingObject = fleetingObject;
            setSignalDirectionIndicatorsToDirection(CTCConstants::SIGNALSNORMAL);
            forceAllSignalsToHeld();
          }
          catch (CTCException e) { e.logError(); return; }
    }

    //@Override
    /*public*/ void SignalDirectionIndicators::removeAllListeners() {
        _mCodingTimeTimer->stop();       // Safety:
        //_mCodingTimeTimer->removeActionListener(_mCodingTimeTimerActionListener);
        disconnect(_mCodingTimeTimer, SIGNAL(timeout()), _mCodingTimeTimerActionListener, SLOT(actionPerformed()));
        _mTimeLockingTimer->stop();
        //_mTimeLockingTimer->removeActionListener(_mTimeLockingTimerActionListener);
        disconnect(_mTimeLockingTimer, SIGNAL(timeout()),
         _mTimeLockingTimerActionListener, SLOT(actionPerformed()));
#if 0 // TODO:
        //_mSignalHeadPropertyChangeListenerLinkedList.forEach((signalHeadPropertyChangeListenerMaintainer) ->
        foreach(SignalHeadPropertyChangeListenerMaintainer* signalHeadPropertyChangeListenerMaintainer, SignalHeadPropertyChangeListenerMaintainer::_mSignalHeadPropertyChangeListenerLinkedList)
        {
            signalHeadPropertyChangeListenerMaintainer->removePropertyChangeListener();
        }//);
#endif
    }

    //@Override
    /*public*/ bool SignalDirectionIndicators::isNonfunctionalObject() { return false; }

    //@Override
    /*public*/ void SignalDirectionIndicators::setPresentSignalDirectionLever(int presentSignalDirectionLever) { _mPresentSignalDirectionLever = presentSignalDirectionLever; }

    //@Override
    /*public*/ bool SignalDirectionIndicators::isRunningTime() { return _mTimeLockingTimer->isRunning(); }

    //@Override
    /*public*/ void SignalDirectionIndicators::osSectionBecameOccupied() {
        _mCodingTimeTimer->stop();
        _mTimeLockingTimer->stop();      // MUST be done before the next line:
        possiblyUpdateSignalIndicationSensors();
    }

    //@Override
    /*public*/ void SignalDirectionIndicators::codeButtonPressed(int requestedDirection, bool requestedChangeInSignalDirection) {
// Valid to process:
        _mCodingTimeTimer->stop();
        _mRequestedDirectionObserver->setRequestedDirection(requestedDirection);         // Superfluous since "setSignalsHeldto" does the same, but I'll leave it here
        if (requestedDirection == CTCConstants::SIGNALSNORMAL) {     // Wants ALL STOP.
            if (_mPresentDirection != CTCConstants::SIGNALSNORMAL) { // And is NOT all stop, run time:
                _mTimeLockingTimer->start();
                requestedChangeInSignalDirection = true;    // And override what is passed
            }
        }
// ONLY start the coding timer IF we aren't running time.
        if (!isRunningTime()) { startCodingTime(); }
        if (requestedChangeInSignalDirection) setSignalDirectionIndicatorsToOUTOFCORRESPONDENCE();
        setSignalsHeldTo(requestedDirection);
    }

    //@Override
    /*public*/ void SignalDirectionIndicators::startCodingTime() {
        _mCodingTimeTimer->start();
    }

    //@Override
    /*public*/ bool SignalDirectionIndicators::signalsNormal() {
        return _mPresentDirection == CTCConstants::SIGNALSNORMAL;
    }

    //@Override
    /*public*/ bool SignalDirectionIndicators::signalsNormalOrOutOfCorrespondence() {
        return _mPresentDirection == CTCConstants::SIGNALSNORMAL || _mPresentDirection == CTCConstants::OUTOFCORRESPONDENCE;
    }

    //@Override
    /*public*/ int SignalDirectionIndicators::getPresentDirection() {
        return _mPresentDirection;
    }

    //@Override
    /*public*/ bool SignalDirectionIndicators::inCorrespondence() {
        return _mPresentDirection != CTCConstants::OUTOFCORRESPONDENCE;
    }

    //@Override
    /*public*/ void SignalDirectionIndicators::forceAllSignalsToHeld() {
        setSignalsHeldTo(CTCConstants::SIGNALSNORMAL);
    }

    //@Override
    /*public*/ int SignalDirectionIndicators::getSignalsInTheFieldDirection() {
        bool LRCanGo = false;
        bool RLCanGo = false;
        for (NBHSignal* signal : _mSignalListLeftRight) {
            if (!signal->isDanger()) { LRCanGo = true; break; }
        }
        for (NBHSignal* signal : _mSignalListRightLeft) {
            if (!signal->isDanger()) { RLCanGo = true; break; }
        }
        if (LRCanGo && RLCanGo) {
            CTCException::logError(tr("Signals are non red in both directions"));    // NOI18N
            setSignalDirectionIndicatorsToOUTOFCORRESPONDENCE();    // ooppss!
            return CTCConstants::OUTOFCORRESPONDENCE;
        }
        if (LRCanGo) return CTCConstants::RIGHTTRAFFIC;
        if (RLCanGo) return CTCConstants::LEFTTRAFFIC;
        return CTCConstants::SIGNALSNORMAL;
    }

    //@Override
    /*public*/ void SignalDirectionIndicators::setSignalDirectionIndicatorsToOUTOFCORRESPONDENCE() {
        setSignalDirectionIndicatorsToDirection(CTCConstants::OUTOFCORRESPONDENCE);
    }

    //@Override
    /*public*/ void SignalDirectionIndicators::setRequestedDirection(int direction) {
        _mRequestedDirectionObserver->setRequestedDirection(direction);
    }

    /*private*/ void SignalDirectionIndicators::addSignal(QString userIdentifier, NBHSignal* signal) throw (CTCException) {
    _mSignalsUsed.insert(signal);
        if (!_mSignalsUsed.contains(signal)) { throw CTCException("SignalDirectionIndicators", userIdentifier, signal->getHandleName(), tr("SignalDirectionIndicatorsDuplicateHomeSignal")); }    // NOI18N
    }

    /*private*/ void SignalDirectionIndicators::setSignalsHeldTo(int direction) {
        switch (direction) {
            case CTCConstants::LEFTTRAFFIC:
                setLRSignalsHeldTo(true);
                setRLSignalsHeldTo(false);
                break;
            case CTCConstants::RIGHTTRAFFIC:
                setLRSignalsHeldTo(false);
                setRLSignalsHeldTo(true);
                break;
            default:    // Could be OUTOFCORRESPONDENCE or SIGNALSNORMAL:
                setLRSignalsHeldTo(true);
                setRLSignalsHeldTo(true);
                break;
        }
        _mRequestedDirectionObserver->setRequestedDirection(direction);
    }

    /*private*/ void SignalDirectionIndicators::setRLSignalsHeldTo(bool held) {
     //_mSignalListRightLeft.forEach((signal) ->
     foreach (NBHSignal* signal, _mSignalListRightLeft)
     {
         signal->setHeld(held);
     }//);
    }
    /*private*/ void SignalDirectionIndicators::setLRSignalsHeldTo(bool held) {
    //_mSignalListLeftRight.forEach((signal) ->
     foreach (NBHSignal* signal, _mSignalListRightLeft)
     {
        signal->setHeld(held);
        }//);
    }

    /*private*/ void SignalDirectionIndicators::setSignalDirectionIndicatorsToFieldSignalsState() {
        setSignalDirectionIndicatorsToDirection(getSignalsInTheFieldDirection());
    }

    /*private*/ void SignalDirectionIndicators::setSignalDirectionIndicatorsToDirection(int direction) {
        switch (direction) {
            case CTCConstants::RIGHTTRAFFIC:
                _mLeftSensor->setKnownState(Sensor::INACTIVE);
                _mNormalSensor->setKnownState(Sensor::INACTIVE);
                _mRightSensor->setKnownState(Sensor::ACTIVE);
                break;
            case CTCConstants::LEFTTRAFFIC:
                _mLeftSensor->setKnownState(Sensor::ACTIVE);
                _mNormalSensor->setKnownState(Sensor::INACTIVE);
                _mRightSensor->setKnownState(Sensor::INACTIVE);
                break;
            case CTCConstants::SIGNALSNORMAL:
                _mLeftSensor->setKnownState(Sensor::INACTIVE);
                _mNormalSensor->setKnownState(Sensor::ACTIVE);
                _mRightSensor->setKnownState(Sensor::INACTIVE);
                break;
            default: // Either OUTOFCORRESPONDENCE or invalid passed value:
                _mLeftSensor->setKnownState(Sensor::INACTIVE);
                _mNormalSensor->setKnownState(Sensor::INACTIVE);
                _mRightSensor->setKnownState(Sensor::INACTIVE);
                break;
        }
        _mPresentDirection = direction;
    }

    /*private*/ void SignalDirectionIndicators::timeLockingDone() {
        setSignalDirectionIndicatorsToFieldSignalsState();  // They ALWAYS reflect the field, even if error!
        cancelLockedRoute();
    }

//  Called by "codingTime" object when it's timer fires:
    /*private*/ void SignalDirectionIndicators::codingTimeDone() {
        if (!isRunningTime()) { // Not running time, signals can change dynamically:
/*
    In "CodeButtonPressed", we have taken off the "held" bits if a direction was requested.  The ABS system
    then takes over and attempts to change the signal.  And since some time has passed ("codingTimeInMilliseconds"),
    the signals have had a - chance - to change indication from red.  At this moment in time, if the signal is still
    red, we will set to held all non held signals that are still red.  In this way, if the Dispatcher coded
    a signal for right traffic, and the block to the right was occupied, and we took off the held bit, the
    signal would stay red, but NOT be held.  Then if the block to the right became un-occupied, the signal would
    change to non-red.  This is NOT what Rick Moser wants in discussion on 1/19/17.  He said that the signal should
    REMAIN red even if occupancy goes clear (non fleeting).
*/
//  A way to test if "cancelLockedRoute();" below is called.  Make our signal system inconsistent with
//  our route allocation logic, to verify if the signal system stays red, we deallocate our allocation earlier.
//          for (NBHAbstractSignalCommon signal : _mSignalListLeftRight) {
//              signal.setAppearance(SignalHead.RED);
//          }
            if (allSignalsRedSetThemAllHeld(_mRequestedDirectionObserver->getRequestedDirection())) {
                cancelLockedRoute();
            }
            setSignalDirectionIndicatorsToFieldSignalsState();  // They ALWAYS reflect the field, even if error!
        }
    }

    /*private*/ void SignalDirectionIndicators::cancelLockedRoute() {
        if (_mCodeButtonHandler != nullptr) { _mCodeButtonHandler->cancelLockedRoute(); }
    }

//  We return an indication of whether or not all signals are red.
//  If true, then they all were red, else false.  If requestedDirection is not left or right, then default "true" (fail safe)!
    /*private*/ bool SignalDirectionIndicators::allSignalsRedSetThemAllHeld(int requestedDirection) {
        if (requestedDirection == CTCConstants::LEFTTRAFFIC) {
            bool allRed = true;
            for (NBHSignal* signal : _mSignalListRightLeft) {   // Can't use lambda here!
                if (!signal->isDanger()) { allRed = false; break; }
            }
            if (allRed)
            { //_mSignalListRightLeft.forEach((signalHead) -> signalHead.setHeld(true));
             foreach(NBHSignal* signalHead, _mSignalListRightLeft)
             {
              signalHead->setHeld(true);
             }
            }
            return allRed;
        } else if (requestedDirection == CTCConstants::RIGHTTRAFFIC) {
            bool allRed = true;
            for (NBHSignal* signal : _mSignalListLeftRight) {   // Can't use lambda here!
                if (!signal->isDanger()) { allRed = false; break; }
            }
            if (allRed)
            {// _mSignalListLeftRight.forEach((signalHead) -> signalHead.setHeld(true));
             foreach(NBHSignal* signalHead, _mSignalListLeftRight)
             {
              signalHead->setHeld(true);
             }
            }
            return allRed;
        }
        return true;
    }

/*  With the introduction of SignalMast objects, I had to modify this routine
    to support them ("changedToUniversalRed"):
*/
    /*private*/ void SignalDirectionIndicators::handleSignalChange(PropertyChangeEvent* e) {
        if (_mFleetingObject != nullptr) {
            if (!_mFleetingObject->isFleetingEnabled()) {
                if (changedToUniversalRed(e)) {    // Signal (SignalMast, SignalHead) changed to Red:
                    bool _forceAllSignalsToHeld = false;
                    if (_mPresentSignalDirectionLever == CTCConstants::RIGHTTRAFFIC) {
                        for (NBHSignal* signal : _mSignalListLeftRight) {
                            if (e->getSource() == (NBHSignal*)signal->getBean()) {
                                _forceAllSignalsToHeld = true;
                                break;
                            }
                        }
                    } else if (_mPresentSignalDirectionLever == CTCConstants::LEFTTRAFFIC) {
                        for (NBHSignal* signal : _mSignalListRightLeft) {
                            if (e->getSource() == (NBHSignal*)signal->getBean()) {
                                _forceAllSignalsToHeld = true;
                                break;
                            }
                        }
                    }
                    if (_forceAllSignalsToHeld) forceAllSignalsToHeld();
                }
            }
        }
        possiblyUpdateSignalIndicationSensors();
    }

    /*private*/ bool SignalDirectionIndicators::changedToUniversalRed(PropertyChangeEvent* e) {
        QObject* source = e->getSource();
        if (qobject_cast<AbstractSignalHead*>(source)) {
            if (e->getPropertyName() ==("Appearance")) { // NOI18N
                return SignalHead::RED == e->getNewValue().toInt();
            }
        } else if (qobject_cast<AbstractSignalMast*>(source)) {
            if (e->getPropertyName() == ("Aspect")) { // NOI18N
                AbstractSignalMast* source2 = (AbstractSignalMast*)source;
                return source2->getAspect()== (source2->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::DANGER));
            }
        }
        return false;   // If none of the above, don't know, assume not red.
    }

    /*private*/ void SignalDirectionIndicators::possiblyUpdateSignalIndicationSensors() {
        if (!_mCodingTimeTimer->isRunning() && !isRunningTime()) {   // Not waiting for coding time and not running time, signals can change dynamically:
            setSignalDirectionIndicatorsToFieldSignalsState();      // They ALWAYS reflect the field, even if error!
        }
    }
