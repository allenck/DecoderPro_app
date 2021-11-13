#include "defaultthrottle.h"
#include "nmrapacket.h"
#include "abstractmessage.h"

/**
 * An implementation of DccThrottle with code specific to a Direct serial
 * connection.
 *
 * @author Bob Jacobsen Copyright (C) 2004
 */
// /*public*/ class Throttle extends AbstractThrottle {


    /**
     * Constructor.
     * @param address loco address.
     * @param tc system connection traffic controller.
     */
    /*public*/ DefaultThrottle::DefaultThrottle(DccLocoAddress* address, CommandStation* tc, QObject* parent) : AbstractThrottle(nullptr, parent){
        //super(null);
        tcl = tc;

        // cache settings.
        //synchronized(this) {
            this->speedSetting = 0;
        //}
        // Functions default to false
        this->address = address;
        this->isForward = true;
    }


    //@Override
    /*public*/ LocoAddress* DefaultThrottle::getLocoAddress() {
        return address;
    }

    /**
     * Send the message to set the state of functions F0, F1, F2, F3, F4.
     */
    //@Override
    /*protected*/ void DefaultThrottle::sendFunctionGroup1() {
        QByteArray result = NmraPacket::function0Through4Packet(address->getNumber(), address->isLongAddress(),
                getF0(), getF1(), getF2(), getF3(), getF4());

        tcl->sendPacket(result, 1);
    }

    /**
     * Send the message to set the state of functions F5, F6, F7, F8.
     */
    //@Override
    /*protected*/ void DefaultThrottle::sendFunctionGroup2() {

        QByteArray result = NmraPacket::function5Through8Packet(address->getNumber(), address->isLongAddress(),
                getF5(), getF6(), getF7(), getF8());

        tcl->sendPacket(result, 1);
    }

    /**
     * Send the message to set the state of functions F9, F10, F11, F12.
     */
    //@Override
    /*protected*/ void DefaultThrottle::sendFunctionGroup3() {

       QByteArray result = NmraPacket::function9Through12Packet(address->getNumber(), address->isLongAddress(),
                getF9(), getF10(), getF11(), getF12());

        tcl->sendPacket(result, 1);
    }

    /**
     * Set the speed and direction.
     * <p>
     * This intentionally skips the emergency stop value of 1.
     *
     * @param speed Number from 0 to 1; less than zero is emergency stop
     */
    //@SuppressFBWarnings(value = "FE_FLOATING_POINT_EQUALITY") // OK to compare floating point
    //@Override
    /*public*/ /*synchronized*/ void DefaultThrottle::setSpeedSetting(float speed) {
        float oldSpeed = this->speedSetting;
        this->speedSetting = speed;
        int value = (int) ((127 - 1) * speed); // -1 for rescale to avoid estop
        if (value > 0) {
            value = value + 1; // skip estop
        }
        if (value > 127) {
            value = 127;       // max possible speed
        }
        if (value < 0) {
            value = 1;         // emergency stop
        }
        QString step = "" + QString::number(value);

        AbstractMessage* m = new AbstractMessage(1 + step.length());
        int i = 0;  // message index counter
        if (isForward) {
            m->setElement(i++, '>');
        } else {
            m->setElement(i++, '<');
        }

        for (int j = 0; j < step.length(); j++) {
            m->setElement(i++, step.at(j).toLatin1());
        }
        firePropertyChange(SPEEDSETTING, oldSpeed, this->speedSetting);
        record(speed);
        // tcl.sendMessage(m, null);
    }

    //@Override
    /*public*/ void DefaultThrottle::setIsForward(bool forward) {
        bool old = isForward;
        isForward = forward;
//        synchronized(this) {
            setSpeedSetting(speedSetting);  // send the command
//        }
        firePropertyChange(ISFORWARD, old, isForward);
    }

    //@Override
    /*public*/ void DefaultThrottle::throttleDispose() {
        finishRecord();
    }
