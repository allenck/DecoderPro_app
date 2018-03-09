#include "sprogslot.h"
#include "loggerfactory.h"
#include "dccthrottle.h"
#include "sprogconstants.h"

using namespace Sprog;

/**
 * Represent information for a DCC Command Station Queue entry where each entry
 * is a DCC packet to be transmitted to the rails.
 * <p>
 * A SlotListener can be registered to hear of changes in this slot. All changes
 * in values will result in notification.
 * <p>
 * Updated by Andrew Crosland February 2012 to allow slots to hold 28 step speed
 * packets
 *
 * @author	Andrew Crosland Copyright (C) 2006, 2012
 * @author	Andrew Berridge 2010
 */
///*public*/ class SprogSlot {


/*public*/ SprogSlot::SprogSlot(int num, QObject* parent) : QObject(parent) {
 speedPacket = false;
 speedMode = DccThrottle::SpeedStepMode128;
 f0to4Packet = false;
 f5to8Packet = false;
 f9to12Packet = false;

 repeatF0 = false;
 repeatF1 = false;
 repeatF2 = false;
 repeatF3 = false;
 repeatF4 = false;
 repeatF5 = false;
 repeatF6 = false;
 repeatF7 = false;
 repeatF8 = false;
 repeatF9 = false;
 repeatF10 = false;
 repeatF11 = false;
 repeatF12 = false;

    payload = QByteArray(SprogConstants::MAX_PACKET_LENGTH,0);
    payload[0] = 0;
    payload[1] = 0;
    payload[2] = 0;
    repeat = -1;
    addr = 0;
    isLong = false;
    spd = 0;
    forward = true;
    status = SprogConstants::SLOT_FREE;
    slot = num;
    opsPkt = false;
}


/*public*/ bool SprogSlot::isF0to4Packet() {
    return f0to4Packet;
}

/*public*/ bool SprogSlot::isF5to8Packet() {
    return f5to8Packet;
}

/*public*/ bool SprogSlot::isF9to12Packet() {
    return f9to12Packet;
}


/**
 * Set the contents of the slot. Intended for accessory packets.
 *
 * @param address int
 * @param payload byte[]
 * @param repeat  int
 */
/*public*/ void SprogSlot::set(int address, QByteArray payload, int repeat) {
    addr = address;

//  ??:  Arrays.copyOf(payload, payload.length());

    this->setRepeat(repeat);
    status = SprogConstants::SLOT_IN_USE;
}

/*public*/ void SprogSlot::setAccessoryPacket(int address, bool closed, int repeats) {
    this->payload = NmraPacket::accDecoderPkt(address, closed);
    this->addr = address + 10000;
    this->repeat = repeats;
    status = SprogConstants::SLOT_IN_USE;
}

/*public*/ bool SprogSlot::isSpeedPacket() {
    return speedPacket;
}

/*public*/ void SprogSlot::setSpeed(int mode, int address, bool isLongAddress, int speed, bool forward) {
    addr = address;
    isLong = isLongAddress;
    spd = speed;
    this->speedPacket = true;
    this->speedMode = mode;
    this->f0to4Packet = false;
    this->forward = forward;
    if ((mode & DccThrottle::SpeedStepMode28) != 0) {
        this->payload = NmraPacket::speedStep28Packet(true, addr,
                isLong, spd, forward);
    } else {
        this->payload = NmraPacket::speedStep128Packet(addr,
                isLong, spd, forward);
    }
    status = SprogConstants::SLOT_IN_USE;
}

/*public*/ void SprogSlot::setOps(int address, bool longAddr, int cv, int val) {
    payload = NmraPacket::opsCvWriteByte(address, longAddr, cv, val);
    this->repeat = SprogConstants::OPS_REPEATS;
    this->opsPkt = true;
    status = SprogConstants::SLOT_IN_USE;
}

/*public*/ void SprogSlot::f5to8packet(int address, bool isLongAddress,
        bool f5, bool f5Momentary,
        bool f6, bool f6Momentary,
        bool f7, bool f7Momentary,
        bool f8, bool f8Momentary) {

    this->f5to8Packet = true;
    this->addr = address;
    this->isLong = isLongAddress;

    //Were we repeating any functions which we are now not?
    if ((this->repeatF5 && !f5)
            || (this->repeatF6 && !f6)
            || (this->repeatF7 && !f7)
            || (this->repeatF8 && !f8)) {
        this->repeat = 3; //Then repeat 3 times
    }

    if (!f5Momentary && f5) {
        this->repeatF5 = true;
    } else {
        this->repeatF5 = false;
    }
    if (!f6Momentary && f6) {
        this->repeatF6 = true;
    } else {
        this->repeatF6 = false;
    }
    if (!f7Momentary && f7) {
        this->repeatF7 = true;
    } else {
        this->repeatF7 = false;
    }
    if (!f8Momentary && f8) {
        this->repeatF8 = true;
    } else {
        this->repeatF8 = false;
    }

    this->payload = NmraPacket::function5Through8Packet(address,
            isLongAddress,
            f5, f6, f7, f8);
    this->status = SprogConstants::SLOT_IN_USE;

}

/*public*/ void SprogSlot::f9to12packet(int address, bool isLongAddress,
        bool f9, bool f9Momentary,
        bool f10, bool f10Momentary,
        bool f11, bool f11Momentary,
        bool f12, bool f12Momentary) {

    this->f9to12Packet = true;
    this->addr = address;
    this->isLong = isLongAddress;

    //Were we repeating any functions which we are now not?
    if ((this->repeatF9 && !f9)
            || (this->repeatF10 && !f10)
            || (this->repeatF11 && !f11)
            || (this->repeatF12 && !f12)) {
        this->repeat = 3; //Then repeat 3 times
    }

    if (!f9Momentary && f9) {
        this->repeatF9 = true;
    } else {
        this->repeatF9 = false;
    }
    if (!f10Momentary && f10) {
        this->repeatF10 = true;
    } else {
        this->repeatF10 = false;
    }
    if (!f11Momentary && f11) {
        this->repeatF11 = true;
    } else {
        this->repeatF11 = false;
    }
    if (!f12Momentary && f12) {
        this->repeatF12 = true;
    } else {
        this->repeatF12 = false;
    }

    this->payload = NmraPacket::function9Through12Packet(address,
            isLongAddress,
            f9, f10, f11, f12);
    this->status = SprogConstants::SLOT_IN_USE;

}

/*public*/ void SprogSlot::f0to4packet(int address, bool isLongAddress,
        bool f0, bool f0Momentary,
        bool f1, bool f1Momentary,
        bool f2, bool f2Momentary,
        bool f3, bool f3Momentary,
        bool f4, bool f4Momentary) {

    this->f0to4Packet = true;
    this->addr = address;
    this->isLong = isLongAddress;

    //Were we repeating any functions which we are now not?
    if ((this->repeatF0 && !f0)
            || (this->repeatF1 && !f1)
            || (this->repeatF2 && !f2)
            || (this->repeatF3 && !f3)
            || (this->repeatF4 && !f4)) {
        this->repeat = 3; //Then repeat 3 times
    }

    if (!f0Momentary && f0) {
        this->repeatF0 = true;
    } else {
        this->repeatF0 = false;
    }
    if (!f1Momentary && f1) {
        this->repeatF1 = true;
    } else {
        this->repeatF1 = false;
    }
    if (!f2Momentary && f2) {
        this->repeatF2 = true;
    } else {
        this->repeatF2 = false;
    }
    if (!f3Momentary && f3) {
        this->repeatF3 = true;
    } else {
        this->repeatF3 = false;
    }
    if (!f4Momentary && f4) {
        this->repeatF4 = true;
    } else {
        this->repeatF4 = false;
    }
    this->payload = NmraPacket::function0Through4Packet(address,
            isLongAddress,
            f0, f1, f2, f3, f4);
    this->status = SprogConstants::SLOT_IN_USE;

}

/*public*/ bool SprogSlot::isFinished() {
    if (this->isF0to4Packet()) {
        if ((this->repeatF0 || this->repeatF1 || this->repeatF2 || this->repeatF3 || this->repeatF4)) {
            return false;
        }
    }
    if (this->isF5to8Packet()) {
        if ((this->repeatF5 || this->repeatF6 || this->repeatF7 || this->repeatF8)) {
            return false;
        }
    }
    if (this->isF9to12Packet()) {
        if ((this->repeatF9 || this->repeatF10 || this->repeatF11 || this->repeatF12)) {
            return false;
        }
    }
    if (this->isSpeedPacket() && this->status == SprogConstants::SLOT_IN_USE) {
        return false;
    }
    if (this->repeat > 0 && this->status == SprogConstants::SLOT_IN_USE) {
        return false;
    }
    /* Finished - clear and return true */
    this->clear();
    return true;
}

/*public*/ void SprogSlot::eStop() {
    this->setSpeed(this->speedMode, this->addr, this->isLong, 1, this->forward);
}

// Access methods

/*public*/ void SprogSlot::clear() {
    status = SprogConstants::SLOT_FREE;
    addr = 0;
    spd = 0;
    speedPacket = false;
    f0to4Packet = false;
    if (payload != NULL) {
        payload[0] = 0;
        payload[1] = 0;
        payload[2] = 0;
    }
    opsPkt = false;
}

/*public*/ bool SprogSlot::isLongAddress() {
    return isLong;
}

/*public*/ bool SprogSlot::isFree() {
    return (status == SprogConstants::SLOT_FREE);
}

/*public*/ int SprogSlot::slotStatus() {
    return status;
}

/*public*/ int SprogSlot::getRepeat() {
    return repeat;
}

/*public*/ void SprogSlot::setRepeat(int r) {
    repeat = r;
}

/*private*/ int SprogSlot::doRepeat() {
    if (repeat > 0) {
        log->debug("Slot " + QString::number(slot) + " repeats");
        repeat--;
        if (repeat == 0) {
            log->debug(tr("Clear slot ") + QString::number(slot) + " due to repeats exhausted");
            this->clear();
        }
    }
    return repeat;
}

/*public*/ int SprogSlot::speed() {
    return spd;
}

//@SuppressWarnings("unused")
/*public*/ int SprogSlot::locoAddr() {
    return addr;
}

/*public*/ int SprogSlot::getAddr() {
    if (opsPkt == false) {
        return addr;
    } else {
        return addressFromPacket();
    }
}

/*public*/ void SprogSlot::setAddr(int a) {
    addr = a;
}

/*public*/ bool SprogSlot::getIsLong() {
    if (opsPkt == false) {
        return isLong;
    } else {
        return ((payload[0] & 0xC0) >= 0xC0);
    }
}

/*public*/ void SprogSlot::setIsLong(bool a) {
    isLong = a;
}

/*public*/ bool SprogSlot::isForward() {
    return forward;
}

/*public*/ bool SprogSlot::isOpsPkt() {
    return opsPkt;
}

/*public*/ bool SprogSlot::isActiveAddressMatch(DccLocoAddress* address) {
    return ( status == SprogConstants::SLOT_IN_USE && getAddr() == address->getNumber() && getIsLong() == address->isLongAddress() );
}

/**
 * Get the payload of this slot. Note - if this slot has a number of
 * repeats, calling this method will also decrement the internal repeat
 * counter.
 *
 * @return a byte array containing the payload of this slot
 */
/*public*/QByteArray SprogSlot::getPayload() {

    QByteArray p;
    if (payload != NULL) {
        //p = Arrays.copyOf(payload, getPayloadLength());//, a Java 1.6 construct
     p = QByteArray(payload);
    } else {
        p = QByteArray();
    }
    /*byte [] p = new byte[getPayloadLength()];
     for (int i = 0; i<getPayloadLength(); i++) p[i] = payload[i];*/

    //decrement repeat counter if appropriate
    doRepeat();
    return p;

}

/*public*/ int SprogSlot::getSlotNumber() {
    return slot;
}

/*private*/ int SprogSlot::getPayloadLength() {
    return this->payload.length();
}


/*public*/ long SprogSlot::getLastUpdateTime() {
    return lastUpdateTime;
}

/**
 * Get the address from the packet.
 *
 * @return int address from payload
 */
/*private*/ int SprogSlot::addressFromPacket() {
    if (isFree()) {
        return -1;
    }
    // First deal with possible extended address
    if ((payload[0] & 0xC0) == 0xC0) {
        return ((payload[0] & 0x3F) << 8 | (payload[1] & 0xFF));
    }
    return payload[0];
}

/*private*/ /*final*/ /*static*/ Logger* SprogSlot::log = LoggerFactory::getLogger("SprogSlot");
