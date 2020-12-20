#include "switchdirectionlever.h"
#include "ctcconstants.h"

//*public*/ class SwitchDirectionLever {
/*public*/ SwitchDirectionLever::SwitchDirectionLever(QString userIdentifier,
                            NBHSensor* switchLeverSensor, QObject *parent) : QObject(parent) {
    _mSwitchLeverSensor = switchLeverSensor;
    if (_mSwitchLeverSensor->getKnownState() == Sensor::UNKNOWN) {
        _mSwitchLeverSensor->setKnownState(Sensor::ACTIVE);
    }
}

/*public*/ void SwitchDirectionLever::removeAllListeners() {}   // None done.
/*public*/ NBHSensor* SwitchDirectionLever::getSwitchLeverSensor() { return _mSwitchLeverSensor; }

/*public*/ int SwitchDirectionLever::getPresentState() {
    int presentState =  _mSwitchLeverSensor->getKnownState();
    if (presentState == Sensor::ACTIVE) return CTCConstants::SWITCHNORMAL;
    if (presentState == Sensor::INACTIVE) return CTCConstants::SWITCHREVERSED;
    return CTCConstants::OUTOFCORRESPONDENCE;    // HUH?
}

