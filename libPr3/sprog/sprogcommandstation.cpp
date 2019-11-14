#include "sprogcommandstation.h"
#include "loggerfactory.h"
#include "sprogslot.h"
#include <QQueue>
#include "sprogmessage.h"
#include <QDateTime>
#include "sleeperthread.h"
#include "sprogreply.h"


using namespace Sprog;

/**
 * Controls a collection of slots, acting as a soft command station for SPROG
 * <P>
 * A SlotListener can register to hear changes. By registering here, the
 * SlotListener is saying that it wants to be notified of a change in any slot.
 * Alternately, the SlotListener can register with some specific slot, done via
 * the SprogSlot object itself.
 * <P>
 * This Programmer implementation is single-user only. It's not clear whether
 * the command stations can have multiple programming requests outstanding (e.g.
 * service mode and ops mode, or two ops mode) at the same time, but this code
 * definitely can't.
 * <P>
 * Updated by Andrew Berridge, January 2010 - state management code now safer,
 * uses enum, etc. Amalgamated with Sprog Slot Manager into a single class -
 * reduces code duplication </P>
 * <P>
 * Updated by Andrew Crosland February 2012 to allow slots to hold 28 step speed
 * packets</P>
 * <P>
 * Re-written by Andrew Crosland to send the next packet as soon as a reply is
 * notified. This removes a race between the old state machine running before
 * the traffic controller despatches a reply, missing the opportunity to send a
 * new packet to the layout until the next JVM time slot, which can be 15ms on
 * Windows platforms.</P>
 * <P>
 * May-17 Moved status reply handling to the slot monitor. Monitor messages from
 * other sources and suppress messages from here to prevent queueing messages in
 * the traffic controller.</P>
 * <P>
 * Jan-18 Re-written again due to threading issues. Previous changes removed
 * activity from the slot thread, which could result in loading the swing thread
 * to the extent that the gui becomes very slow to respond.
 * Moved status message generation to the slot monitor.</P>
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2003
 * @author Andrew Crosland (C) 2006 ported to SPROG, 2012, 2016, 2018
 */
///*public*/ class SprogCommandStation implements CommandStation, SprogListener, Runnable {
/*final*/ /*static*/ int SprogCommandStation::MAX_PACKET_DELAY;// = 25;

/*public*/ SprogCommandStation::SprogCommandStation(SprogTrafficController* controller, QObject* parent) {

 currentSlot = 0;
 currentSprogAddress = -1;

 tc = NULL;

 lock = new QObject();
 lock2 = new QObject();
 waitingForReply = false;
 replyAvailable = false;
 sendSprogAddress = false;
 MAX_PACKET_DELAY = 25;
 slotListeners = new QVector<SprogSlotListener*>();
 statusDue = 0;


    sendNow = new QQueue<SprogSlot*>();
    /**
     * Create a default length queue
     */
    _slots = new QLinkedList<SprogSlot*>();
    for (int i = 0; i < SprogConstants::MAX_SLOTS; i++) {
        _slots->append(new SprogSlot(i));
    }
    tc = controller;
    tc->addSprogListener((SprogListener*)this);
}

/**
 * Send a specific packet as a SprogMessage.
 *
 * @param packet  Byte array representing the packet, including the
 *                error-correction byte. Must not be NULL.
 * @param repeats number of times to repeat the packet
 */
//@Override
/*public*/ bool SprogCommandStation::sendPacket(QByteArray packet, int repeats) {
    if (packet.length() <= 1) {
        log->error(tr("Invalid DCC packet length: %1").arg(packet.length()));
    }
    if (packet.length() >= 7) {
        log->error(tr("Maximum 6-byte packets accepted: %1").arg(packet.length()));
    }
    /*final*/ SprogMessage* m = new SprogMessage(packet);
    sendMessage(m);
    return true;
}

/**
 * Send the SprogMessage to the hardware.
 * <p>
 * sendSprogMessage will block until the message can be sent. When it returns
 * we set the reply status for the message just sent.
 *
 * @param m       The message to be sent
 */
/*protected*/ void SprogCommandStation::sendMessage(SprogMessage* m) {
    // Limit to one message in flight from the command station
    while (waitingForReply) {
        try {
            log->debug("Waiting for a reply");
//                synchronized (lock2) {
//                    lock2.wait(100); // Will wait until notify()ed or 100ms timeout
//                }
        } catch (InterruptedException e) {
            log->debug("waitingForReply interrupted");
            // Save the interrupted status for anyone who may be interested
//                Thread.currentThread().interrupt();
            return;
        }
        if (waitingForReply) {
            log->warn("Timeout Waiting for reply");
        }
    }
    waitingForReply = true;
    log->debug(tr("Sending message [%1] id %2").arg(m->toString(tc->isSIIBootMode())).arg(m->getId()));
    lastId = m->getId();
    tc->sendSprogMessage(m, (SprogListener*)this);
}

/**
 * Return contents of Queue slot i.
 *
 * @param i int of slot requested
 * @return SprogSlot slot i
 */
/*public*/ SprogSlot* SprogCommandStation::slot(const int i) {
    //return _slots->at(i);
 QLinkedList<SprogSlot*> cpy = QLinkedList<SprogSlot*>(*_slots);
 int j = 0;
 while(cpy.count() > 0)
 {
  SprogSlot* s = cpy.takeFirst();
  if(j++ == i)
   return s;
 }
 return NULL;
}

/**
 * Clear all slots.
 */
//@SuppressWarnings("unused")
/*private*/ void SprogCommandStation::clearAllSlots() {
//        slots.stream().forEach((s) -> {
 foreach(SprogSlot*s, *_slots)
 {
        s->clear();
    }//);
}

/**
 * Find a free slot entry.
 *
 * @return SprogSlot the next free Slot or NULL if all slots are full
 */
/*protected*/ SprogSlot* SprogCommandStation::findFree() {
    for (SprogSlot* s : *_slots) {
        if (s->isFree()) {
            if (log->isDebugEnabled()) {
                log->debug(tr("Found free slot %1").arg(s->getSlotNumber()));
            }
            return s;
        }
    }
    return (NULL);
}

/**
 * Find a queue entry matching the address.
 *
 * @param a int
 * @return the slot or NULL if the address is not in the queue
 */
/*private*/ SprogSlot* SprogCommandStation::findAddress(DccLocoAddress* address) {
    for (SprogSlot* s : *_slots) {
        if ( s->isActiveAddressMatch(address) ) {
            return s;
        }
    }
    return (NULL);
}

/*private*/ SprogSlot* SprogCommandStation::findAddressSpeedPacket(DccLocoAddress* address) {
    // SPROG doesn't use IDLE packets but sends speed commands to last address selected by "A" command.
    // We may need to move these pseudo-idle packets to an unused long address so locos will not receive conflicting speed commands.
    // Some short-address-only decoders may also respond to same-numbered long address so we avoid any number match irrespective of type
    // We need to find a suitable free long address, save (currentSprogAddress) and use it for pseudo-idle packets
    int lastSprogAddress = currentSprogAddress;
    while ( (currentSprogAddress <= 0) || // initialisation || avoid address 0 for reason above
                ( (address->getNumber() == currentSprogAddress ) ) || // avoid this address (slot may not exist but we will be creating one)
                ( findAddress(new DccLocoAddress(currentSprogAddress,true)) != NULL) || ( findAddress(new DccLocoAddress(currentSprogAddress,false)) != NULL) // avoid in-use (both long or short versions of) address
                ) {
                currentSprogAddress++;
                currentSprogAddress = currentSprogAddress % 10240;
        }
    if (currentSprogAddress != lastSprogAddress) {
        log->info(tr("Changing currentSprogAddress (for pseudo-idle packets) to %1(L)").arg( currentSprogAddress));
        // We want to ignore the reply to this message so it does not trigger an extra packet
        // Set a flag to send this from the slot thread and avoid swing thread waiting
        //sendMessage(new SprogMessage("A " + currentSprogAddress + " 0"));
        sendSprogAddress = true;
    }
    for (SprogSlot* s : *_slots) {
        if (s->isActiveAddressMatch(address) && s->isSpeedPacket()) {
            return s;
        }
    }
    if (getInUseCount() < SprogConstants::MAX_SLOTS) {
        return findFree();
    }
    return (NULL);
}

/*private*/ SprogSlot* SprogCommandStation::findF0to4Packet(DccLocoAddress* address) {
    for (SprogSlot* s : *_slots) {
        if (s->isActiveAddressMatch(address) && s->isF0to4Packet()) {
            return s;
        }
    }
    if (getInUseCount() < SprogConstants::MAX_SLOTS) {
        return findFree();
    }
    return (NULL);
}

/*private*/ SprogSlot* SprogCommandStation::findF5to8Packet(DccLocoAddress* address) {
    for (SprogSlot* s : *_slots) {
        if (s->isActiveAddressMatch(address) && s->isF5to8Packet()) {
            return s;
        }
    }
    if (getInUseCount() < SprogConstants::MAX_SLOTS) {
        return findFree();
    }
    return (NULL);
}

/*private*/ SprogSlot* SprogCommandStation::findF9to12Packet(DccLocoAddress* address) {
    for (SprogSlot* s : *_slots) {
        if (s->isActiveAddressMatch(address) && s->isF9to12Packet()) {
            return s;
        }
    }
    if (getInUseCount() < SprogConstants::MAX_SLOTS) {
        return findFree();
    }
    return (NULL);
}

/*public*/ void SprogCommandStation::forwardCommandChangeToLayout(int address, bool closed) {

    SprogSlot* s = this->findFree();
    if (s != NULL) {
        s->setAccessoryPacket(address, closed, SprogConstants::S_REPEATS);
        notifySlotListeners(s);
    }
}

/*public*/ void SprogCommandStation::function0Through4Packet(DccLocoAddress* address,
        bool f0, bool f0Momentary,
        bool f1, bool f1Momentary,
        bool f2, bool f2Momentary,
        bool f3, bool f3Momentary,
        bool f4, bool f4Momentary) {
    SprogSlot* s = this->findF0to4Packet(address);
    s->f0to4packet(address->getNumber(), address->isLongAddress(), f0, f0Momentary,
            f1, f1Momentary,
            f2, f2Momentary,
            f3, f3Momentary,
            f4, f4Momentary);
    notifySlotListeners(s);
}

/*public*/ void SprogCommandStation::function5Through8Packet(DccLocoAddress* address,
        bool f5, bool f5Momentary,
        bool f6, bool f6Momentary,
        bool f7, bool f7Momentary,
        bool f8, bool f8Momentary) {
    SprogSlot* s = this->findF5to8Packet(address);
    s->f5to8packet(address->getNumber(), address->isLongAddress(), f5, f5Momentary, f6, f6Momentary, f7, f7Momentary, f8, f8Momentary);
    notifySlotListeners(s);
}

/*public*/ void SprogCommandStation::function9Through12Packet(DccLocoAddress* address,
        bool f9, bool f9Momentary,
        bool f10, bool f10Momentary,
        bool f11, bool f11Momentary,
        bool f12, bool f12Momentary) {
    SprogSlot* s = this->findF9to12Packet(address);
    s->f9to12packet(address->getNumber(), address->isLongAddress(), f9, f9Momentary, f10, f10Momentary, f11, f11Momentary, f12, f12Momentary);
    notifySlotListeners(s);
}

/**
 * Handle speed changes from throttle. As well as updating an existing slot,
 * or creating a new on where necessary, the speed command is added to the
 * queue of packets to be sent immediately. This ensures minimum latency
 * between the user adjusting the throttle and a loco responding, rather
 * than possibly waiting for a complete traversal of all slots before the
 * new speed is actually sent to the hardware.
 *
 */
/*public*/ void SprogCommandStation::setSpeed(int mode, DccLocoAddress* address, int spd, bool isForward) {
    SprogSlot* s = this->findAddressSpeedPacket(address);
    if (s != NULL) { // May need an error here - if all slots are full!
        s->setSpeed(mode, address->getNumber(), address->isLongAddress(), spd, isForward);
        notifySlotListeners(s);
        log->debug("Registering new speed");
        sendNow->append(s);
    }
}

/*public*/ SprogSlot* SprogCommandStation::opsModepacket(int address, bool longAddr, int cv, int val) {
    SprogSlot* s = findFree();
    if (s != NULL) {
        s->setOps(address, longAddr, cv, val);
        if (log->isDebugEnabled()) {
            log->debug(tr("opsModePacket() Notify ops mode packet for address %1").arg( address));
        }
        notifySlotListeners(s);
        return (s);
    } else {
         return (NULL);
    }
}

/*public*/ void SprogCommandStation::release(DccLocoAddress* address) {
    SprogSlot* s;
    while ((s = findAddress(address)) != NULL) {
        s->clear();
        notifySlotListeners(s);
    }
}

/**
 * Send emergency stop to all slots.
 */
/*public*/ void SprogCommandStation::estopAll()
{
    //slots.stream().filter((s) ->
 foreach(SprogSlot* s, *_slots)
 {
  if(                       ((s->getRepeat() == -1)
            && s->slotStatus() != SprogConstants::SLOT_FREE
            && s->speed() != 1))//.forEach((s) -> {
                eStopSlot(s);
            }//);
}

/**
 * Send emergency stop to a slot.
 *
 * @param s SprogSlot to eStop
 */
/*protected*/ void SprogCommandStation::eStopSlot(SprogSlot* s) {
    log->debug(tr("Estop slot: %1 for address: %2").arg(s->getSlotNumber()).arg(s->getAddr()));
    s->eStop();
    notifySlotListeners(s);
}

/**
 * Method to find the existing SlotManager object, if need be creating one.
 *
 * @return the SlotManager object
 * @deprecated JMRI Since 4.4 instance() shouldn't be used, convert to JMRI multi-system support structure
 */
//@Deprecated
/*public*/ /*final*/ SprogCommandStation* SprogCommandStation::instance() {
    return NULL;
}


/*public*/ /*synchronized*/ void SprogCommandStation::addSlotListener(SprogSlotListener* l) {
    // add only if not already registered
    slotListeners->append(l);
}

/*public*/ /*synchronized*/ void SprogCommandStation::removeSlotListener(SprogSlotListener* l) {
    slotListeners->removeOne(l);
    disconnect(this, SIGNAL(notifyChangedSlot(SProgSlot*)), l, SLOT(notifyChangedSlot(SprogSlot*)));
}

/**
 * Trigger the notification of all SlotListeners.
 *
 * @param s The changed slot to notify.
 */
/*private*/ /*synchronized*/ void SprogCommandStation::notifySlotListeners(SprogSlot* s) {
    log->debug(tr("notifySlotListeners() notify %1 SlotListeners about slot for address %2").arg(slotListeners->size()).arg(s->getAddr()));

    // forward to all listeners
//    slotListeners.stream().forEach((client) -> {
//        client.notifyChangedSlot(s);
//    });
    emit notifyChangedSlot(s);
}

//@Override
/**
 * The run() method will only be called (from SprogSystemConnectionMemo
 * ConfigureCommandStation()) if the connected SPROG is in Command Station mode.
 *
 */
/*public*/ void SprogCommandStation::run() {
    time = QDateTime::currentDateTime().toMSecsSinceEpoch();//System.currentTimeMillis();
    if(log->isDebugEnabled()) log->debug(tr("Slot thread starts at time %1").arg(time));
    // Send a decoder idle packet to prompt a reply from hardware and set things running
    sendPacket(NmraPacket::idlePacket(), SprogConstants::S_REPEATS);
    while(true) {
        try {
//            synchronized(lock) {
//               lock.wait(1000);
//            }
      SleeperThread::msleep(1000);
        } catch (InterruptedException e) {
           log->debug("Slot thread interrupted");
           // We'll loop around if there's no reply available yet
           // Save the interrupted status for anyone who may be interested
//TODO:           Thread.currentThread().interrupt();
           // and exit
           return;
        }
        if(log->isDebugEnabled()) log->debug(tr("Slot thread wakes at time %1").arg(QDateTime::currentDateTime().toMSecsSinceEpoch()));

        // If we need to change the SPROGs default address, do that immediately.
        // Reply to that will
        if (sendSprogAddress) {
            sendMessage(new SprogMessage("A " + QString::number(currentSprogAddress) + " 0"));
            replyAvailable = false;
            sendSprogAddress = false;
        } else if (replyAvailable) {
            if (reply->isUnsolicited() && reply->isOverload()) {
                log->error("Overload");

                // *** turn power off
            }

            // Get next packet to send
            QByteArray p;
            SprogSlot* s = sendNow->takeFirst(); // poll()
            if (s != NULL) {
                // New throttle action to be sent immediately
                p = s->getPayload();
                log->debug("Packet from immediate send queue");
            } else {
                // Or take the next one from the stack
                p = getNextPacket();
                if (p != NULL) {
                    log->debug("Packet from stack");
                }
            }
            replyAvailable = false;
            if (p != NULL) {
                // Send the packet
                sendPacket(p, SprogConstants::S_REPEATS);
                log->debug("Packet sent");
            } else {
                // Send a decoder idle packet to prompt a reply from hardware and keep things running
                sendPacket(NmraPacket::idlePacket(), SprogConstants::S_REPEATS);
            }
            timeNow = QDateTime::currentDateTime().toMSecsSinceEpoch();
            packetDelay = timeNow - time;
            time = timeNow;
            // Useful for debug if packets are being delayed; Set to trace level to be able to debug other stuff
            if (packetDelay > MAX_PACKET_DELAY) {
                log->trace(tr("Packet delay was %1 ms time now %2").arg(packetDelay).arg(time));
            }
        } else {
            if(log->isDebugEnabled()) log->warn("Slot thread wait timeout");
        }
    }
}

/**
 * Get the next packet to be transmitted.
 *
 * @return byte[] NULL if no packet
 */
/*private*/ QByteArray SprogCommandStation::getNextPacket() {
    SprogSlot* s;

    if (!isBusy()) {
        return NULL;
    }
#if 1 // TODO: C++ has no equivalent to find a particular linked list entry
    //while (_slots->get(currentSlot).isFree())
    QLinkedList<SprogSlot*>::iterator it;
    int ix = 0;
    for(it = _slots->begin(); it != _slots->end(); it++, ix++)
    {
     if(ix < currentSlot)
      continue;
     s = *it;
     if(!s->isFree())
       break;
     currentSlot++;
     currentSlot = currentSlot % SprogConstants::MAX_SLOTS;
    }
    //s = _slots->get(currentSlot);
#endif
    QByteArray ret = s->getPayload();
    // Resend ops packets until repeat count is exhausted so that
    // decoder receives contiguous identical packets, otherwsie find
    // next packet to send
    if (!s->isOpsPkt() || (s->getRepeat() == 0)) {
        currentSlot++;
        currentSlot = currentSlot % SprogConstants::MAX_SLOTS;
    }

    if (s->isFinished()) {
        notifySlotListeners(s);
        //return NULL;
        emit finished();
    }

    return ret;
}

/*
 *
 * @param m the sprog message received
 */
//@Override
/*public*/ void SprogCommandStation::notifyMessage(SprogMessage* /*m*/) {
}

/**
 * Handle replies.
 * <p>
 * Handle replies from the hardware, ignoring those that were not sent from
 * the command station.
 *
 * @param m The SprogReply to be handled
 */
//@Override
/*public*/ void SprogCommandStation::notifyReply(SprogReply* m) {
    if (m->getId() != lastId) {
        // Not my id, so not interested, message send still locked
        log->debug("Ignore reply with mismatched id");
        return;
    } else {
        // Unblock sending messages
        waitingForReply = false;
        reply = new SprogReply(m);
//        synchronized (lock2) {
//            lock2.notifyAll();
//        }
        log->debug(tr("Reply received [%1]").arg(m->toString()));
        // Log the reply and wake the slot thread
        replyAvailable = true;
//        synchronized (lock) {
//            lock.notifyAll();
//        }
    }
}


/**
 * Provide a count of the slots in use.
 *
 * @return the number of slots in use
 */
/*public*/ int SprogCommandStation::getInUseCount() {
    int result = 0;
    for (SprogSlot* s : *_slots) {
        if (!s->isFree()) {
            result++;
        }
    }
    return result;
}

/**
 *
 * @return a bool if the command station is busy - i.e. it has at least
 *         one occupied slot
 */
/*public*/ bool SprogCommandStation::isBusy()
{
   // return slots.stream().anyMatch((s) -> (!s.isFree()));
 foreach (SprogSlot* s, *_slots) {
  if(!s->isFree())
   return true;
 }

 return false;
}

/*public*/ void SprogCommandStation::setSystemConnectionMemo(SprogSystemConnectionMemo* memo) {
    adaptermemo = memo;
}


/**
 * Get user name.
 *
 * @return the user name
 */
//@Override
/*public*/ QString SprogCommandStation::getUserName() {
    if (adaptermemo == NULL) {
        return "Sprog";
    }
    return adaptermemo->getUserName();
}

/**
 * Get system prefix.
 *
 * @return the system prefix
 */
//@Override
/*public*/ QString SprogCommandStation::getSystemPrefix() {
    if (adaptermemo == NULL) {
        return "S";
    }
    return adaptermemo->getSystemPrefix();
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* SprogCommandStation::log = LoggerFactory::getLogger("SprogCommandStation");
