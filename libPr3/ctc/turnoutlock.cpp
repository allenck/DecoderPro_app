#include "turnoutlock.h"

TurnoutLock::TurnoutLock(QObject *parent) : QObject(parent)
{

}
#if 0
/**
This only works with Digitrax DS54's and DS64's configured to LOCALLY change the switch via either
a pushbutton or toggle switch.  Specifically in JMRI / DS64 programmer, OpSw 21 SHOULD
be checked.  DS54's should be similarly configured.

The other way:
One would NOT check OpSw21, and then one would have to write JMRI software (or a script)
to process the message from the DS54/DS64, and then send the appropriate turnout
"CLOSED/THROWN" command to the turnout to effect the change.

Advantage:      No turnout movement when crew requests change unless allowed by Dispatcher.
Disadvantage:   Software MUST be running in order to throw turnout "normally".  In other
                words cannot run the layout without the computer, and with all turnouts
                controlled by the dispatcher set to "local control".

This modules way:
The purpose of this module is to "countermand" attempts by the field crews to throw
a switch that is under dispatcher control.  This works ONLY for switches that have feedback.

Advantage:      Computer NOT necessary to throw switch.
Disadvantage:   Switch will "partially throw" until the feedback contact changes and sends
                a message to the software, which then countermands it.  If a train is on the
                switch, it may be derailed.

NOTES:
    If a route is cleared thru, you MUST be prevented from UNLOCKING a locked switch.
Failure to provide such an object will just allow unlocking while a route is cleared thru.

If dispatcherSensorLockToggle is None, then INSURE that you call "ExternalLockTurnout" at some
point to lock the turnout, since this starts up with the turnout unlocked!

* See the documentation for the matrix regarding Command and Feedback normal/reversed.
 */

///*public*/ class TurnoutLock {

    /*public*/ TurnoutLock( String userIdentifier,
                        NBHSensor dispatcherSensorLockToggle,          // Toggle switch that indicates lock/unlock on the panel.  If None, then PERMANENTLY locked by the Dispatcher!
                        NBHTurnout actualTurnout,                       // The turnout being locked: LTxx a real turnout, like LT69.
                        bool actualTurnoutFeedbackDifferent,     // True / False, in case feedback backwards but switch command above isn't!
                        NBHSensor dispatcherSensorUnlockedIndicator,   // Display unlocked status (when ACTIVE) back to the Dispatcher.
                        bool noDispatcherControlOfSwitch,        // Dispatcher doesn't control the switch.  If TRUE, then provide:
                        int ndcos_WhenLockedSwitchState,            // When Dispatcher does lock, switch should be set to: CLOSED/THROWN
                        CodeButtonHandlerData.LOCK_IMPLEMENTATION _mLockImplementation,  // Someday, choose which one to implement.  Right now, my own.
                        bool turnoutLocksEnabledAtStartup,
                        NBHTurnout additionalTurnout1,
                        bool additionalTurnout1FeebackReversed,
                        NBHTurnout additionalTurnout2,
                        bool additionalTurnout2FeebackReversed,
                        NBHTurnout additionalTurnout3,
                        bool additionalTurnout3FeebackReversed) {
        _mDispatcherSensorLockToggle = dispatcherSensorLockToggle;
        addTurnoutMonitored(userIdentifier, "actualTurnout", actualTurnout, actualTurnoutFeedbackDifferent, true);
        _mDispatcherSensorUnlockedIndicator = dispatcherSensorUnlockedIndicator;
        _mDispatcherSensorLockToggle.setKnownState(turnoutLocksEnabledAtStartup ? Sensor.INACTIVE : Sensor.ACTIVE);
        _mNoDispatcherControlOfSwitch = noDispatcherControlOfSwitch;
        _m_ndcos_WhenLockedSwitchState = ndcos_WhenLockedSwitchState;
        addTurnoutMonitored(userIdentifier, "additionalTurnout1", additionalTurnout1, additionalTurnout1FeebackReversed, false);    // NOI18N
        addTurnoutMonitored(userIdentifier, "additionalTurnout2", additionalTurnout2, additionalTurnout2FeebackReversed, false);    // NOI18N
        addTurnoutMonitored(userIdentifier, "additionalTurnout3", additionalTurnout3, additionalTurnout3FeebackReversed, false);    // NOI18N
        updateDispatcherSensorIndicator(turnoutLocksEnabledAtStartup);
        _mTurnoutsMonitoredPropertyChangeListener = (PropertyChangeEvent e) -> { handleTurnoutChange(e); };
        for (NBHTurnout tempTurnout : _mTurnoutsMonitored) {
            if (tempTurnout.getKnownState() == Turnout.UNKNOWN) {
                tempTurnout.setCommandedState(_mCommandedState);    // MUST be done before "addPropertyChangeListener":
            }
            tempTurnout.addPropertyChangeListener(_mTurnoutsMonitoredPropertyChangeListener);
        }
    }

    /*public*/ void removeAllListeners() {
        for (NBHTurnout tempTurnout : _mTurnoutsMonitored) {
            tempTurnout.removePropertyChangeListener(_mTurnoutsMonitoredPropertyChangeListener);
        }
    }

    /*public*/ NBHSensor getDispatcherSensorLockToggle() { return _mDispatcherSensorLockToggle; }

    /*private*/ void addTurnoutMonitored(String userIdentifier, String parameter, NBHTurnout actualTurnout, bool FeedbackDifferent, bool required) {
        bool actualTurnoutPresent = actualTurnout.valid();
        if (required && !actualTurnoutPresent) {
            (new CTCException("TurnoutLock", userIdentifier, parameter, Bundle.getMessage("RequiredTurnoutMissing"))).logError();   // NOI18N
            return;
        }
        if (actualTurnoutPresent) { // IF there is something there, try it:
            if (actualTurnout.valid()) _mTurnoutsMonitored.add(actualTurnout);
        }
    }

//  Was propertyChange:
    /*private*/ void handleTurnoutChange(PropertyChangeEvent e) {
        if (e.getPropertyName().equals("KnownState")) { // NOI18N
            if (_mLocked) {                                                 // Act on locked only!
                NBHTurnout turnout = null;  // Not found.
                for (int index = 0; index < _mTurnoutsMonitored.size(); index++) { // Find matching entry:
                    if (e.getSource() == _mTurnoutsMonitored.get(index).getBean()) { // Matched:
                        turnout = _mTurnoutsMonitored.get(index);
                        break;
                    }
                }
                if (turnout != null) { // Safety check:
                    if (_mCommandedState != turnout.getKnownState()) {      // Someone in the field messed with it:
                        turnoutSetCommandedState(turnout, _mCommandedState);       // Just directly restore it
                    }
                }
            }
        }
    }
#endif
/*
External software calls this from initialization code in order to lock the turnout.  When this code starts
up the lock status is UNLOCKED so that initialization code can do whatever to the turnout.
This routine DOES NOT modify the state of the switch, ONLY the lock!
*/
    /*public*/ void TurnoutLock::externalLockTurnout() {
        _mDispatcherSensorLockToggle.setKnownState(Sensor::INACTIVE);
        updateDispatcherSensorIndicator(true);
    }
#if 0
//  Ditto above routine, except opposite:
    /*public*/ void externalUnlockTurnout() {
        _mDispatcherSensorLockToggle.setKnownState(Sensor.ACTIVE);
        updateDispatcherSensorIndicator(false);
    }

//  External software calls this (from CodeButtonHandler typically) to inform us of a valid code button push:
    /*public*/ void codeButtonPressed() {
        bool newLockedState = getNewLockedState();
        if (newLockedState == _mLocked) return; // Nothing changed
//  The PROTOTYPE would not do this: Since the dispatcher CANNOT control the state of the switch, and
//  our operating crews (for example: "brains go dead going down the stairs") MAY forget to normalize the switch
//  for the main (for instance), we FORCE the state of the switch(s) to a known state (hopefully for the main)
        if (_mNoDispatcherControlOfSwitch && newLockedState == true) { // No dispatcher control of switch and LOCKING them, "normalize" the switch:
            for (NBHTurnout turnout : _mTurnoutsMonitored) {
                turnoutSetCommandedState(turnout, _m_ndcos_WhenLockedSwitchState);     // Make it so.
            }
        }
        updateDispatcherSensorIndicator(newLockedState);
    }

// External software calls this (from CodeButtonHandler typically) to tell us of the new state of the turnout:
    /*public*/ void dispatcherCommandedState(int commandedState) {
        if (commandedState == CTCConstants.SWITCHNORMAL) _mCommandedState = Turnout.CLOSED; else _mCommandedState = Turnout.THROWN;
    }

    /*public*/ bool turnoutPresentlyLocked() { return _mLocked; }

    /*public*/ bool getNewLockedState() {
        return _mDispatcherSensorLockToggle.getKnownState() == Sensor.INACTIVE;
    }

    /*public*/ bool tryingToChangeLockStatus() { return getNewLockedState() != _mLocked; }

    /*private*/ void turnoutSetCommandedState(NBHTurnout turnout, int state) {
        _mCommandedState = state;
        turnout.setCommandedState(state);
    }
#endif
    /*private*/ void TurnoutLock::updateDispatcherSensorIndicator(bool newLockedState) {
        _mLocked = newLockedState;
        _mDispatcherSensorUnlockedIndicator->setKnownState(_mLocked ? Sensor::INACTIVE : Sensor::ACTIVE);
    }
