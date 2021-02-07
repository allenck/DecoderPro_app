#include "pr2throttle.h"
#include "loggerfactory.h"
#include "loconetsystemconnectionmemo.h"

/**
 * An implementation of DccThrottle via AbstractThrottle with code specific to a
 * PR2 connection.
 * <p>
 * Speed in the Throttle interfaces and AbstractThrottle is a float, but in
 * LocoNet is an int with values from 0 to 127.
 *
 * @author Bob Jacobsen Copyright (C) 2006
 */
// /*public*/ class Pr2Throttle extends AbstractThrottle {


/**
 * Constructor
 */
/*public*/ Pr2Throttle::Pr2Throttle(LocoNetSystemConnectionMemo* memo, DccLocoAddress* address, QObject* parent) : AbstractThrottle(memo, parent)                                                                                                                           {
    //super(memo);
    this->address = address;
    addr = address->getNumber();
    setSpeedStepMode(SpeedStepMode::NMRA_DCC_28);
    //this->speedIncrement = 1;  // 128 step mode only
}

/**
 * Convert a LocoNet speed integer to a float speed value.
 *
 * @param lSpeed loconet speed value
 * @return speed as float 0-&gt;1.0
 */
/*protected*/ float Pr2Throttle::floatSpeed(int lSpeed) {
    if (lSpeed == 0) {
        return 0.f;
    } else if (lSpeed == 1) {
        return -1.f;   // estop
    }
    if (getSpeedStepMode() == DccThrottle::SpeedStepMode28) {
        if (lSpeed <= 15) //Value less than 15 is in the stop/estop range bracket
        {
            return 0.f;
        }
        return (((lSpeed - 12) / 4.f) / 28.f);
    } else if (getSpeedStepMode() == DccThrottle::SpeedStepMode14) {
        if (lSpeed <= 15) //Value less than 15 is in the stop/estop range bracket
        {
            return 0.f;
        }
        return ((lSpeed - 8) / 8.f) / 14.f;
    } else {
        return ((lSpeed - 1) / 126.f);
    }
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ int Pr2Throttle::intSpeed(float fSpeed) {
    int speed = AbstractThrottle::intSpeed(fSpeed);
    if (speed <= 0) {
        return speed; // return idle and emergency stop
    }
    switch (this->getSpeedStepMode()) {
        case DccThrottle::SpeedStepMode28:
        case DccThrottle::SpeedStepMode28Mot:
            return (int) ((fSpeed * 28) * 4) + 12;
        case DccThrottle::SpeedStepMode14:
            return (int) ((fSpeed * 14) * 8) + 8;
        default:
            log->warn(tr("Unhandled speed step mode: %1").arg(SpeedStepMode(this->getSpeedStepMode()).name));
            break;
    }
    return speed;
}

/*public*/ void Pr2Throttle::writeData() {
    // convert contents
    int stat = 0;

    int speed = intSpeed(speedSetting);

    int dirf = 0; // contains dir, f0, f4-1
    if (getF0()) {
        dirf |= (1 << 4);
    }
    if (getF1()) {
        dirf |= (1 << 0);
    }
    if (getF2()) {
        dirf |= (1 << 1);
    }
    if (getF3()) {
        dirf |= (1 << 2);
    }
    if (getF4()) {
        dirf |= (1 << 3);
    }
    if (!getIsForward()) {
        dirf |= (1 << 5);  // note sign of bit
    }
    // contains f11-5
    int f11 = 0;
    if (getF5()) {
        f11 |= (1 << 0);
    }
    if (getF6()) {
        f11 |= (1 << 1);
    }
    if (getF7()) {
        f11 |= (1 << 2);
    }
    if (getF8()) {
        f11 |= (1 << 3);
    }
    if (getF9()) {
        f11 |= (1 << 4);
    }
    if (getF10()) {
        f11 |= (1 << 5);
    }
    if (getF11()) {
        f11 |= (1 << 6);
    }

    // contains F19-F13
    int f19 = 0;

    // contains F27-F21
    int f27 = 0;

    // contains F28, F20, F12
    int f28 = 0;
    if (getF12()) {
        f28 |= (1 << 4);
    }

    LocoNetMessage* l = new LocoNetMessage(21);
    l->setOpCode(LnConstants::OPC_WR_SL_DATA_EXP);
    int i = 1;
    l->setElement(i++, 21);      // length
    l->setElement(i++, 0);       // EXP_MAST
    l->setElement(i++, 1);       // EXP_SLOT
    l->setElement(i++, stat & 0x7F);     // EXPD_STAT
    l->setElement(i++, addr & 0x7F);     // EXPD_ADRL
    l->setElement(i++, (addr / 128) & 0x7F); // EXPD_ADRH
    l->setElement(i++, 0);               // EXPD_FLAGS
    l->setElement(i++, speed & 0x7F);    // EXPD_SPD
    l->setElement(i++, f28 & 0x7F);      // EXPD_F28F20F12
    l->setElement(i++, dirf & 0x7F);     // EXPD_DIR_F0F4_F1
    l->setElement(i++, f11 & 0x7F);      // EXPD_F11_F5
    l->setElement(i++, f19 & 0x7F);      // EXPD_F19_F13
    l->setElement(i++, f27 & 0x7F);      // EXPD_F27_F21
    // rest are zero

    ((LocoNetSystemConnectionMemo*) adapterMemo)->getLnTrafficController()->sendLocoNetMessage(l);
}

/**
 * Send the LocoNet message to set the state of locomotive direction and
 * functions F0, F1, F2, F3, F4. Invoked by AbstractThrottle when needed.
 */
//@Override
/*protected*/ void Pr2Throttle::sendFunctionGroup1() {
    writeData();
}

/**
 * Send the LocoNet message to set the state of functions F5, F6, F7, F8.
 * Invoked by AbstractThrottle when needed.
 */
//@Override
/*protected*/ void Pr2Throttle::sendFunctionGroup2() {
    writeData();
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void Pr2Throttle::sendFunctionGroup3() {
    writeData();
}

/**
 * Set the speed.
 * <p>
 * This intentionally skips the emergency stop value of 1.
 *
 * @param speed Number from 0 to 1; less than zero is emergency stop
 */
//@SuppressFBWarnings(value = "FE_FLOATING_POINT_EQUALITY") // OK to compare floating point, notify on any change
//@Override
/*public*/ void Pr2Throttle::setSpeedSetting(float speed) {
    float oldSpeed = this->speedSetting;
    this->speedSetting = speed;
    if (speed < 0) {
        this->speedSetting = -1.f;
    }

    writeData();
    if (oldSpeed != this->speedSetting) {
        notifyPropertyChangeListener("SpeedSetting", oldSpeed, this->speedSetting); // NOI18N
    }
    record(speed);
}

/**
 * LocoNet actually puts forward and backward in the same message as the
 * first function group.
 */
//@Override
/*public*/ void Pr2Throttle::setIsForward(bool forward) {
    bool old = isForward;
    isForward = forward;
    sendFunctionGroup1();
    if (old != isForward) {
        notifyPropertyChangeListener("IsForward", old, isForward); // NOI18N
    }
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString Pr2Throttle::toString() {
    return getLocoAddress()->toString();
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ LocoAddress* Pr2Throttle::getLocoAddress() {
    return address;
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void Pr2Throttle::throttleDispose() {
    finishRecord();
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* Pr2Throttle::log = LoggerFactory::getLogger("Pr2Throttle");


