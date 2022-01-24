#include "signaldirectionlever.h"
#include "ctcconstants.h"

/*
 *  @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */

// /*public*/ class SignalDirectionLever {


/*public*/ SignalDirectionLever::SignalDirectionLever(QString userIdentifier, NBHSensor* leftSensor, NBHSensor* normalSensor, NBHSensor* rightSensor, QObject *parent) : QObject(parent) {
    _mLeftSensor = leftSensor;
    _mNormalSensor = normalSensor;
    _mRightSensor = rightSensor;
    if (!_mLeftSensor->valid() && !_mRightSensor->valid()) {
         CTCException("SignalDirectionLever", userIdentifier, tr("must have one"), tr("One or both leftSensor and rightSensor must exist")).logError();
    }
    _mLeftSensor->setKnownState(Sensor::INACTIVE);
    _mNormalSensor->setKnownState(Sensor::ACTIVE);
    _mRightSensor->setKnownState(Sensor::INACTIVE);
}

/*public*/ void SignalDirectionLever::removeAllListeners() {}   // None done.
/*public*/ SignalDirectionLever::LNR_NBHSensors* SignalDirectionLever::getLevers() { return new LNR_NBHSensors(_mLeftSensor, _mNormalSensor, _mRightSensor); }

/*public*/ int SignalDirectionLever::getPresentSignalDirectionLeverState() {
    if (_mLeftSensor->getKnownState() == Sensor::ACTIVE) return CTCConstants::LEFTTRAFFIC;
    if (_mNormalSensor->getKnownState() == Sensor::ACTIVE) return CTCConstants::SIGNALSNORMAL;
    if (_mRightSensor->getKnownState() == Sensor::ACTIVE) return CTCConstants::RIGHTTRAFFIC;
    return CTCConstants::OUTOFCORRESPONDENCE;    // Huh?
}
