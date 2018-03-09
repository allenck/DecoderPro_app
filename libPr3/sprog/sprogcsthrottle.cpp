#include "sprogcsthrottle.h"
#include "sprogthrottle.h"
#include "instancemanager.h"

using namespace Sprog;

/**
 * An implementation of DccThrottle with code specific to a SPROG Command
 * Station connection.
 * <P>
 * Updated by Andrew Crosland February 2012 to enable 28 step speed packets</P>
 *
 * @author	Andrew Crosland Copyright (C) 2006, 2012
 */
///*public*/ class SprogCSThrottle extends AbstractThrottle {

/**
 * Constructor.
 */
/*public*/ SprogCSThrottle::SprogCSThrottle(SprogSystemConnectionMemo* memo, LocoAddress* address, QObject* parent) : AbstractThrottle(memo, parent){
    //super(memo);

    // cache settings.
    this->speedSetting = 0;
    this->f0 = false;
    this->f1 = false;
    this->f2 = false;
    this->f3 = false;
    this->f4 = false;
    this->f5 = false;
    this->f6 = false;
    this->f7 = false;
    this->f8 = false;
    this->f9 = false;
    this->f10 = false;
    this->f11 = false;
    this->f12 = false;
    this->address = ((DccLocoAddress*) address);
    this->isForward = true;

    //@TODO - this needs a little work. Current implementation looks like it
    //should support other modes, but doesn't in practice.
    //@see AbstractThrottleManager.supportedSpeedModes()
    // Find our command station
    if ((memo != NULL) && (memo->get("CommandStation") != NULL)) {
        commandStation = (SprogCommandStation*)memo->get("CommandStation");
    } else {
        commandStation = (SprogCommandStation*) InstanceManager::getNullableDefault("CommandStation");
    }

}


//@Override
/*public*/ LocoAddress* SprogCSThrottle::getLocoAddress() {
    return address;
}

/**
 * Send the message to set the state of functions F0, F1, F2, F3, F4 by
 * adding it to the S queue
 */
//@Override
/*protected*/ void SprogCSThrottle::sendFunctionGroup1() {
    commandStation->function0Through4Packet(address,
            getF0(), getF0Momentary(),
            getF1(), getF1Momentary(),
            getF2(), getF2Momentary(),
            getF3(), getF3Momentary(),
            getF4(), getF4Momentary());

}

/**
 * Send the message to set the state of functions F5, F6, F7, F8 by# adding
 * it to the S queue
 */
//@Override
/*protected*/ void SprogCSThrottle::sendFunctionGroup2() {
    commandStation->function5Through8Packet(address,
            getF5(), getF5Momentary(),
            getF6(), getF6Momentary(),
            getF7(), getF7Momentary(),
            getF8(), getF8Momentary());
}

/**
 * Send the message to set the state of functions F9, F10, F11, F12 by
 * adding it to the S queue
 */
//@Override
/*protected*/ void SprogCSThrottle::sendFunctionGroup3() {
    commandStation->function9Through12Packet(address,
            getF9(), getF9Momentary(),
            getF10(), getF10Momentary(),
            getF11(), getF11Momentary(),
            getF12(), getF12Momentary());
}

/**
 * Set the speed {@literal &} direction.
 * <P>
 * This intentionally skips the emergency stop value of 1 in 128 step mode
 * and the stop and estop values 1-3 in 28 step mode.
 *
 * @param speed Number from 0 to 1; less than zero is emergency stop
 */
//@Override
/*public*/ void SprogCSThrottle::setSpeedSetting(float speed) {
    int mode = getSpeedStepMode();
    if ((mode & DccThrottle::SpeedStepMode28) != 0) {
        // 28 step mode speed commands are
        // stop, estop, stop, estop, 4, 5, ..., 31
        float oldSpeed = this->speedSetting;
        this->speedSetting = speed;
        int value = (int) ((31 - 3) * speed);     // -1 for rescale to avoid estop
        if (value > 0) {
            value = value + 3;  // skip estopx2 and stop
        }
        if (value > 31) {
            value = 31;      // max possible speed
        }
        if (value < 0) {
            value = 1;        // emergency stop
        }
        commandStation->setSpeed(DccThrottle::SpeedStepMode28, address, value, isForward);
        if (qAbs(oldSpeed - this->speedSetting) > 0.0001) {
            notifyPropertyChangeListener("SpeedSetting", oldSpeed, this->speedSetting);
        }
    } else {
        // 128 step mode speed commands are
        // stop, estop, 2, 3, ..., 127
        float oldSpeed = this->speedSetting;
        this->speedSetting = speed;
        int value = (int) ((127 - 1) * speed);     // -1 for rescale to avoid estop
        if (value > 0) {
            value = value + 1;  // skip estop
        }
        if (value > 127) {
            value = 127;    // max possible speed
        }
        if (value < 0) {
            value = 1;        // emergency stop
        }
        commandStation->setSpeed(DccThrottle::SpeedStepMode128, address, value, isForward);
        if (qAbs(oldSpeed - this->speedSetting) > 0.0001) {
            notifyPropertyChangeListener("SpeedSetting", oldSpeed, this->speedSetting);
        }
    }
    record(speed);
}

//@Override
/*public*/ void SprogCSThrottle::setIsForward(bool forward) {
    bool old = isForward;
    isForward = forward;
    setSpeedSetting(speedSetting);  // Update the speed setting
    if (old != isForward) {
        notifyPropertyChangeListener("IsForward", old, isForward);
    }
}

//@Override
/*protected*/ void SprogCSThrottle::throttleDispose() {
    active = false;
    commandStation->release(address);
    finishRecord();
}
