#include "switchdirectionindicators.h"
#include "turnout.h"

/*
 *  @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
//package jmri.jmrit.ctc;

//import java.awt.event.ActionListener;
//import java.beans.PropertyChangeEvent;
//import java.beans.PropertyChangeListener;
//import javax.swing.Timer;
//import jmri.Sensor;
//import jmri.Turnout;

/*
If you have REAL feedback from the switch that sets it's position:
    You SHOULD set "Feedback" to "True" and rely on this message to set the switch in "correspondence".
    If you didn't set "Feedback" to "True" in this case, and the timeout amount was shorter than
    the time it took the switch to "feed back" it's information, the switch will be OUT OF CORRESPONDENCE
    and both lights will REMAIN unlit.  In this case, throwing it AGAIN will eventually report proper!
    If the "feedback" message from the unit is lost, then the lights will REMAIN (properly!) out of correspondence!

This object ACTUALLY CONTROLS THE SWITCH, AND sends commands to move the points.
*/

//  /*public*/ class SwitchDirectionIndicators {

/*public*/ SwitchDirectionIndicators::SwitchDirectionIndicators(   QString userIdentifier,
                                    NBHSensor* normalIndicatorSensor,
                                    NBHSensor* reveresedIndicatorSensor,
                                    NBHTurnout* actualTurnout,
                                    int codingTimeInMilliseconds,           // Instead of "CodingDistrict"
                                    bool feedbackDifferent, QObject *parent) : QObject(parent) {
    _mNormalIndicatorSensor = normalIndicatorSensor;
    _mReversedIndicatorSensor = reveresedIndicatorSensor;
    _mActualTurnout = actualTurnout;
    _mActualTurnoutHasFeedback = _mActualTurnout->getFeedbackMode() != Turnout::DIRECT && _mActualTurnout->getFeedbackMode() != Turnout::MONITORING;

    if (_mActualTurnoutHasFeedback) {
        // Let real sensor that drives turnout feedback set indicators:
        //_mActualTurnoutPropertyChangeListener = (PropertyChangeEvent e) -> { if (e.getPropertyName().equals("KnownState")) setSwitchIndicationSensorsToPresentState(); };   // NOI18N
      _mActualTurnoutPropertyChangeListener = new ActualTurnoutPropertyChangeListener(this);
     _mActualTurnout->addPropertyChangeListener(_mActualTurnoutPropertyChangeListener);
        setSwitchIndicationSensorsToPresentState();
    } else { // Simulate feedback delay if any:
        //_mSimulatedTurnoutFeedbackTimerActionListener = (ActionEvent) -> { setSwitchIndicationSensorsToPresentState(); };
        _mSimulatedTurnoutFeedbackTimerActionListener = new SimulatedTurnoutFeedbackTimerActionListener(this);
        _mSimulatedTurnoutFeedbackTimer = new Timer(codingTimeInMilliseconds, _mSimulatedTurnoutFeedbackTimerActionListener);
        _mSimulatedTurnoutFeedbackTimer->setRepeats(false);
/*      IF AND ONLY IF the layout owner DOES NOT initialize all DIRECT or MONITORING turnouts BEFORE
    starting this CTC system, we wind up with turnouts that have KnownState = UNKNOWN
    Here, IF AND ONLY IF the layout owner initialized those turnouts prior to starting this CTC system,
    we now "give a chance" for us to find out the real state, and update the state if know, otherwise,
    we ASSUME it is SWITCHNORMAL for those people who don't.
*/
        setSwitchIndicationSensorsToPresentState();
        if (_mLastActualTurnoutState == CTCConstants::CTC_UNKNOWN) {
            setSwitchIndicatorSensors(CTCConstants::SWITCHNORMAL);
        }
    }
}

/*public*/ void SwitchDirectionIndicators::removeAllListeners() {
    _mActualTurnout->removePropertyChangeListener(_mActualTurnoutPropertyChangeListener);
    if (_mSimulatedTurnoutFeedbackTimer != nullptr) {
        _mSimulatedTurnoutFeedbackTimer->stop();
        //_mSimulatedTurnoutFeedbackTimer->removeActionListener(_mSimulatedTurnoutFeedbackTimerActionListener);
        disconnect(_mSimulatedTurnoutFeedbackTimer, SIGNAL(timeout()), _mSimulatedTurnoutFeedbackTimerActionListener->self(), SLOT(actionPerformed()));
    }
}

/*public*/ void SwitchDirectionIndicators::codeButtonPressed(int requestedState) {
    if (_mWaitingForFeedbackOrTimer) return;    // We've already done something in the past, ignore new request
    if (requestedState != _mLastActualTurnoutState) {   // It's different:
        _mWaitingForFeedbackOrTimer = true;     // We're doing something now!
        setSwitchIndicatorSensors(CTCConstants::OUTOFCORRESPONDENCE);
        if (requestedState == CTCConstants::SWITCHNORMAL) { _mActualTurnout->setCommandedState(Turnout::CLOSED); }
        else if (requestedState == CTCConstants::SWITCHREVERSED) { _mActualTurnout->setCommandedState(Turnout::THROWN); } // Any other passed invalid value is ignored.
        if (!_mActualTurnoutHasFeedback) _mSimulatedTurnoutFeedbackTimer->start();   // Simulate feedback (fire timer only once)
    }
}

/*private*/ int SwitchDirectionIndicators::getPresentState() {
    int actualTurnoutKnownState = _mActualTurnout->getKnownState();
    if (actualTurnoutKnownState == Turnout::CLOSED) _mLastActualTurnoutState = CTCConstants::SWITCHNORMAL;
    else if (actualTurnoutKnownState == Turnout::THROWN) _mLastActualTurnoutState = CTCConstants::SWITCHREVERSED;
    else _mLastActualTurnoutState = CTCConstants::CTC_UNKNOWN;
    return _mLastActualTurnoutState;
}

/*public*/ int SwitchDirectionIndicators::getLastIndicatorState() {
    return _mLastIndicatorState;
}

/*public*/ bool SwitchDirectionIndicators::inCorrespondence() {
    if (_mLastActualTurnoutState == CTCConstants::CTC_UNKNOWN) return true;   // Fake out calling routine to allow it to call us at "CodeButtonPressed"
    return _mLastIndicatorState != CTCConstants::OUTOFCORRESPONDENCE;
}

/*public*/ NBHSensor* SwitchDirectionIndicators::getProperIndicatorSensor(bool isNormal) {
    return isNormal ? _mNormalIndicatorSensor : _mReversedIndicatorSensor;
}

/*private*/ void SwitchDirectionIndicators::setSwitchIndicatorSensors(int requestedState) {
    switch(requestedState) {
        case CTCConstants::SWITCHNORMAL:
            _mNormalIndicatorSensor->setKnownState(Sensor::ACTIVE);
            _mReversedIndicatorSensor->setKnownState(Sensor::INACTIVE);
            _mLastIndicatorState = CTCConstants::SWITCHNORMAL;
            break;
        case CTCConstants::SWITCHREVERSED:
            _mNormalIndicatorSensor->setKnownState(Sensor::INACTIVE);
            _mReversedIndicatorSensor->setKnownState(Sensor::ACTIVE);
            _mLastIndicatorState = CTCConstants::SWITCHREVERSED;
            break;
        default:
            _mNormalIndicatorSensor->setKnownState(Sensor::INACTIVE);
            _mReversedIndicatorSensor->setKnownState(Sensor::INACTIVE);
            _mLastIndicatorState = CTCConstants::OUTOFCORRESPONDENCE;
            break;
    }
}

/*private*/ void SwitchDirectionIndicators::setSwitchIndicationSensorsToPresentState() {
    if (_mSimulatedTurnoutFeedbackTimer != nullptr) _mSimulatedTurnoutFeedbackTimer->stop();
    _mWaitingForFeedbackOrTimer = false;
    setSwitchIndicatorSensors(getPresentState());
}

//  /*private*/ int getTransmissionDelayInMilliseconds(CodingDistrict codingDistrict) {
//      if (codingDistrict != null) return codingDistrict.getTransmissionDelayInMilliseconds();
//      return 0;
//  }
