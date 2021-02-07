#include "debugthrottle.h"

//DebugThrottle::DebugThrottle(QObject *parent) :
//    AbstractThrottle(parent)
//{
//}
/**
 * An implementation of DccThrottle for debugging use.
 *
 * @author	Bob Jacobsen  Copyright (C) 2003
 * @version     $Revision: 23322 $
 */
///*public*/ class DebugThrottle extends AbstractThrottle
//{
/**
 * Constructor
 */
/*public*/ DebugThrottle::DebugThrottle(DccLocoAddress* address, SystemConnectionMemo* memo, QObject *parent) :
    AbstractThrottle(memo, parent)
{
    //super(memo);
    log = new Logger("DebugThrottle");

    // cache settings. It would be better to read the
    // actual state, but I don't know how to do this
    this->speedSetting = 0;
    this->f0           = false;
    this->f1           = false;
    this->f2           = false;
    this->f3           = false;
    this->f4           = false;
    this->f5           = false;
    this->f6           = false;
    this->f7           = false;
    this->f8           = false;
    this->f9           = false;
    this->f10           = false;
    this->f11           = false;
    this->f12           = false;
    this->isForward    = true;

    this->address      = address;
    setSpeedStepMode( SpeedStepMode::NMRA_DCC_128);
}


/*public*/ LocoAddress* DebugThrottle::getLocoAddress() { return address; }

/*public*/ QString DebugThrottle::toString() {
    return QString::number(getLocoAddress()->getNumber());
}

/**
 * Send the message to set the state of functions F0, F1, F2, F3, F4
 */
/*protected*/ void DebugThrottle::sendFunctionGroup1() {
}

/**
 * Send the message to set the state of
 * functions F5, F6, F7, F8
 */
/*protected*/ void DebugThrottle::sendFunctionGroup2() {

}

/**
 * Send the message to set the state of
 * functions F9, F10, F11, F12
 */
/*protected*/ void DebugThrottle::sendFunctionGroup3() {
}

/**
 * Set the speed & direction
 * <P>
 * This intentionally skips the emergency stop value of 1.
 * @param speed Number from 0 to 1; less than zero is emergency stop
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="FE_FLOATING_POINT_EQUALITY") // OK to compare floating point, notify on any change
/*public*/ void DebugThrottle::setSpeedSetting(float speed) {
    float oldSpeed = this->speedSetting;
    if (speed>1.0) {
        log->warn("Speed was set too high: " +QString::number(speed));
    }
    this->speedSetting = speed;
    if (oldSpeed != this->speedSetting)
        notifyPropertyChangeListener("SpeedSetting", oldSpeed, this->speedSetting );
    record(speed);
}

/*public*/ void DebugThrottle::setIsForward(bool forward) {
    bool old = isForward;
    isForward = forward;
    setSpeedSetting(speedSetting);  // send the command
    if (old != isForward)
        notifyPropertyChangeListener("IsForward", old, isForward );
}

/*protected*/ void DebugThrottle::throttleDispose(){
    log->debug("throttleDispose() called");
    finishRecord();
}
