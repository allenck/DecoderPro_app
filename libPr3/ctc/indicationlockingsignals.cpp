#include "indicationlockingsignals.h"
#include "signalmast.h"
#include "signalmastlogic.h"
#include "instancemanager.h"
#include "signalmastlogicmanager.h"
/*
 *  @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
//package jmri.jmrit.ctc;

//import java.util.ArrayList;
//import jmri.InstanceManager;
//import jmri.SignalMast;
//import jmri.SignalMastLogic;
//import jmri.SignalMastLogicManager;
//import jmri.Turnout;
//import jmri.TurnoutManager;
//import jmri.jmrit.ctc.ctcserialdata.OtherData;
//import jmri.jmrit.ctc.ctcserialdata.ProjectsCommonSubs;

// /*public*/ class IndicationLockingSignals {

/*public*/ IndicationLockingSignals::IndicationLockingSignals(QString userIdentifier, QList<NBHSignal*> _signals, NBHTurnout* nbhTurnout,
        OtherData::SIGNAL_SYSTEM_TYPE signalSystemType, QObject *parent) : QObject(parent) {
    turnout = nbhTurnout->getBean();
    signalType = signalSystemType;
    _mListOfSignals = _signals;
}

/*public*/ void IndicationLockingSignals::removeAllListeners() {}   // None done.

/*public*/ bool IndicationLockingSignals::routeClearedAcross() {
    if (signalType == OtherData::SIGNAL_SYSTEM_TYPE::SIGNALHEAD) {
        return checkSignalHeads();
    } else if (signalType == OtherData::SIGNAL_SYSTEM_TYPE::SIGNALMAST) {
        return checkSignalMasts();
    }
    return false;
}

/*public*/ bool IndicationLockingSignals::checkSignalHeads() {
    for (NBHSignal* signal : _mListOfSignals) {
        if (!signal->isDanger()) return true;
    }
    return false;
}

/*public*/ bool IndicationLockingSignals::checkSignalMasts() {
    for (NBHSignal* signal : _mListOfSignals) {
        if (checkMast((SignalMast*) signal->getBean(), turnout)) return true;
    }
    return false;
}

/*public*/ bool IndicationLockingSignals::checkMast(SignalMast* mast, Turnout* turnout) {
    if (mast->getHeld()) return false;

    // Get the SML for the mast and check for an active destination
    SignalMastLogic* sml = ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->getSignalMastLogic(mast);
    // It is possible if the user put in (for example) a "bumper signal" (end of track signal)
    // either accidentally or purposefully for there to be no logic at all.
    if (sml == nullptr) return false;
    SignalMast* activeDest = sml->getActiveDestination();
    if (activeDest == nullptr) return false;

    // Check the auto turnouts for a match
    for (Turnout* autoTurnout : sml->getAutoTurnouts(activeDest)) {
        if (autoTurnout == turnout) return true;
    }

    // Check the manual turnouts for a match
    for (Turnout* manualTurnout : sml->getTurnouts(activeDest)) {
        if (manualTurnout == turnout) return true;
    }

    return false;
}
