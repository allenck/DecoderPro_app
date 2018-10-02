#include "loconetconsist.h"
#include "loggerfactory.h"
#include "throttlemanager.h"
#include <QList>
#include "exceptions.h"
#include "abstractthrottlemanager.h"
/**
 * LocoNetConsist.java
 *
 * This is the Consist definition for a consist on a LocoNet system. it uses the
 * LocoNet specific commands to build a consist.
 *
 * @author Paul Bender Copyright (C) 2011
 */

// /*public*/ class LocoNetConsist extends jmri.implementation.DccConsist implements SlotListener, ThrottleListener {



// Initialize a consist for the specific address
// the Default consist type for loconet is a Command
// Station Consist.
/*public*/ LocoNetConsist::LocoNetConsist(int address, LocoNetSystemConnectionMemo* lm, QObject* parent) : DccConsist(address, parent)
{
   // super(address);
 common();
    this->slotManager = lm->getSlotManager();
    this->trafficController = lm->getLnTrafficController();
    this->throttleManager = (AbstractThrottleManager*) lm->getThrottleManager();
    consistRequestState = LEADREQUESTSTATE;
    consistType = Consist::CS_CONSIST;
    needToWrite = QList<DccLocoAddress*>();
    throttleManager->requestThrottle(consistAddress, (ThrottleListener*)this);
}

// Initialize a consist for the specific address
// the Default consist type for loconet is a Command
// Station Consist.
/*public*/ LocoNetConsist::LocoNetConsist(DccLocoAddress* address, LocoNetSystemConnectionMemo* lm, QObject* parent) : DccConsist(address, parent)
{
 common();
    this->slotManager = lm->getSlotManager();
    this->trafficController = lm->getLnTrafficController();
    this->throttleManager = (AbstractThrottleManager*) lm->getThrottleManager();
    consistRequestState = LEADREQUESTSTATE;
    consistType = Consist::CS_CONSIST;
    needToWrite = QList<DccLocoAddress*>();
    throttleManager->requestThrottle(consistAddress, (ThrottleListener*)this);
}

void LocoNetConsist::common()
{
 slotManager = NULL;
 trafficController = NULL;
 throttleManager = NULL;
 leadSlot = NULL;
 needToWrite = QList<DccLocoAddress*>();

}

// Clean Up local storage
//@Override
/*public*/ void LocoNetConsist::dispose()  {
    DccConsist::dispose();
}

// Set the Consist Type
//@Override
/*public*/ void LocoNetConsist::setConsistType(int consist_type)
{
    if (consist_type == Consist::ADVANCED_CONSIST) {
        consistType = consist_type;
        return;
    } else if (consist_type == Consist::CS_CONSIST) {
        consistType = consist_type;
    } else {
        log->error("Consist Type Not Supported");
        notifyConsistListeners(new DccLocoAddress(0, false), ConsistListener::NotImplemented);
    }
}

/* is this address allowed?
 * On LocoNet systems, All addresses can be used in a Universal Consist
 * and only 0 is not allowed in Advanced Consists.
 */
//@Override
/*public*/ bool LocoNetConsist::isAddressAllowed(DccLocoAddress* address)  {
    if (consistType == Consist::CS_CONSIST) {
        return true;
    } else if (address->getNumber() != 0) {
        return (true);
    }
    else
    return (false);
}

/* is there a size limit for this consist?
 * For LocoNet returns -1 (no limit) for
 * both CS and Advanced Consists
 * return 0 for any other consist type.
 */
//@Override
/*public*/ int LocoNetConsist::sizeLimit() const
{
    if (consistType == ADVANCED_CONSIST) {
        return -1;
    } else if (consistType == CS_CONSIST) {
        return -1;
    } else {
        return 0;
    }
}

// does the consist contain the specified address?
//@Override
/*public*/ bool LocoNetConsist::contains(DccLocoAddress* address)
{
    if (consistType == ADVANCED_CONSIST || consistType == CS_CONSIST) {
        return consistList->contains(address);
    } else {
        log->error("Consist Type Not Supported");
        notifyConsistListeners(address, ConsistListener::NotImplemented);
    }
    return false;
}

// get the relative direction setting for a specific
// locomotive in the consist
//@Override
/*public*/ bool LocoNetConsist::getLocoDirection(DccLocoAddress* address)  {
    log->debug("consist " + consistAddress->toString() + " obtaining direction for " + address->toString() + " Consist List Size " + QString::number(consistList->size()));
    if (consistType == ADVANCED_CONSIST || consistType == CS_CONSIST) {
        if (address == consistAddress) {
            return true;
        }
        if (consistList->contains(address)) {
            bool Direction = consistDir->value(address);
            return (Direction);
        } else {
            return (true);
        }
    } else {
        log->error("Consist Type Not Supported");
        notifyConsistListeners(address, ConsistListener::NotImplemented);
    }
    return false;
}

/*
 * Method for adding an Address to the internal consist list object.
 */
/*private*/ /*synchronized*/ void LocoNetConsist::addToConsistList(DccLocoAddress* LocoAddress, bool directionNormal) {
    bool Direction = (directionNormal);
    if (!(consistList->contains(LocoAddress))) {
        consistList->append(LocoAddress);
    }
    if (consistDir->contains(LocoAddress)) {
        consistDir->remove(LocoAddress);
    }
    consistDir->insert(LocoAddress, Direction);
}

/*
 * Method for removing an address from the internal consist list object.
 */
/*private*/ /*synchronized*/ void LocoNetConsist::removeFromConsistList(DccLocoAddress* LocoAddress) {
    consistDir->remove(LocoAddress);
    consistList->removeOne(LocoAddress);
}

/*
 * Add a Locomotive to a Consist
 *  @param address is the Locomotive address to add to the locomotive
 *  @param directionNormal is True if the locomotive is traveling
 *        the same direction as the consist, or false otherwise.
 */
//@Override
/*public*/ /*synchronized*/ void LocoNetConsist::add(DccLocoAddress* LocoAddress, bool directionNormal)
{
    if (LocoAddress == consistAddress) {
        // this is required for command station consists on LocoNet.
        addToConsistList(LocoAddress, directionNormal);
        notifyConsistListeners(LocoAddress, ConsistListener::OPERATION_SUCCESS);
    } else if (consistType == ADVANCED_CONSIST) {
        if (consistList->contains(LocoAddress)) {
            // we are changing the direction, so remove first,
            // then add
            removeFromAdvancedConsist(LocoAddress);
        }
        addToConsistList(LocoAddress, directionNormal);
        if (leadSlot == NULL || consistRequestState != IDLESTATE) {
            needToWrite.append(LocoAddress);
        } else {
            addToAdvancedConsist(LocoAddress, directionNormal);
        }
    } else if (consistType == CS_CONSIST) {
        if (consistList->contains(LocoAddress)) {
            // we are changing the direction, so remove first,
            // then add
            removeFromCSConsist(LocoAddress);
        }
        addToConsistList(LocoAddress, directionNormal);
        if (leadSlot == NULL || consistRequestState != IDLESTATE) {
            needToWrite.append(LocoAddress);
        } else {
            addToCSConsist(LocoAddress, directionNormal);
        }
    } else {
        log->error("Consist Type Not Supported");
        notifyConsistListeners(LocoAddress, ConsistListener::NotImplemented);
    }
}

/*private*/ /*synchronized*/ void LocoNetConsist::delayedAdd() {
    DccLocoAddress* LocoAddress = needToWrite.value(0);
    if (consistType == ADVANCED_CONSIST) {
        addToAdvancedConsist(LocoAddress, getLocoDirection(LocoAddress));
    } else if (consistType == CS_CONSIST) {
        addToCSConsist(LocoAddress, getLocoDirection(LocoAddress));
    }
    needToWrite.removeOne(LocoAddress);
}

/*
 * Restore a Locomotive to a Consist, but don't write to
 * the command station.  This is used for restoring the consist
 * from a file or adding a consist read from the command station.
 *  @param address is the Locomotive address to add to the locomotive
 *  @param directionNormal is True if the locomotive is traveling
 *        the same direction as the consist, or false otherwise.
 */
//@Override
/*public*/ /*synchronized*/ void LocoNetConsist::restore(DccLocoAddress* LocoAddress, bool directionNormal)
{
    if (consistType == ADVANCED_CONSIST) {
        addToConsistList(LocoAddress, directionNormal);
    } else if (consistType == CS_CONSIST) {
        addToConsistList(LocoAddress, directionNormal);
    } else {
        log->error("Consist Type Not Supported");
        notifyConsistListeners(LocoAddress, ConsistListener::NotImplemented);
    }
}

/*
 *  Remove a Locomotive from this Consist
 *  @param address is the Locomotive address to add to the locomotive
 */
//@Override
/*public*/ /*synchronized*/ void LocoNetConsist::remove(DccLocoAddress* LocoAddress)
{
    if (consistType == ADVANCED_CONSIST) {
        removeFromAdvancedConsist(LocoAddress);
        removeFromConsistList(LocoAddress);
    } else if (consistType == CS_CONSIST) {
        removeFromCSConsist(LocoAddress);
        removeFromConsistList(LocoAddress);
    } else {
        log->error("Consist Type Not Supported");
        notifyConsistListeners(LocoAddress, ConsistListener::NotImplemented);
    }
}

/*
 *  Add a Locomotive to an Advanced Consist
 *  @param address is the Locomotive address to add to the locomotive
 *  @param directionNormal is True if the locomotive is traveling
 *        the same direction as the consist, or false otherwise.
 */
//@Override
/*protected*/ /*synchronized*/ void LocoNetConsist::addToAdvancedConsist(DccLocoAddress* LocoAddress, bool directionNormal) {
    if (log->isDebugEnabled()) {
        log->debug("Add Locomotive " // NOI18N
                + LocoAddress->toString()
                + " to advanced consist " // NOI18N
                + consistAddress->toString()
                + " With Direction Normal " // NOI18N
                + directionNormal + ".");
    }
    consistRequestState = LINKSTAGEONESTATE;
    throttleManager->requestThrottle(LocoAddress, (ThrottleListener*)this);
}

/*
 *  Remove a Locomotive from an Advanced Consist
 *  @param address is the Locomotive address to add to the locomotive
 */
//@Override
/*protected*/ /*synchronized*/ void LocoNetConsist::removeFromAdvancedConsist(DccLocoAddress* LocoAddress) {
    if (log->isDebugEnabled()) {
        log->debug(" Remove Locomotive " // NOI18N
                + LocoAddress->toString()
                + " from advanced consist " // NOI18N
                + consistAddress->toString());
    }
    slotManager->slotFromLocoAddress(LocoAddress->getNumber(), (SlotListener*)this);
    consistRequestState = UNLINKSTAGEONESTATE;
}

/*
 *  Add a Locomotive to a LocoNet Universal Consist.
 *  @param address is the Locomotive address to add to the locomotive
 *  @param directionNormal is True if the locomotive is traveling
 *        the same direction as the consist, or false otherwise.
 */
/*private*/ /*synchronized*/ void LocoNetConsist::addToCSConsist(DccLocoAddress* LocoAddress, bool directionNormal) {
    if (log->isDebugEnabled()) {
        log->debug("Add Locomotive " // NOI18N
                + LocoAddress->toString()
                + " to Standard Consist " // NOI18N
                + consistAddress->toString()
                + " With Direction Normal " // NOI18N
                + directionNormal + ".");
    }
    if(consistList->size()<=1 && LocoAddress == (consistAddress)){
      // there is only one address in this consist, no reason to link.
      notifyConsistListeners(LocoAddress,ConsistListener::OPERATION_SUCCESS);
      return;
    }
    throttleManager->requestThrottle(LocoAddress, (ThrottleListener*)this);
    // skip right to stage 2, we do not need to status edit.
    consistRequestState = LINKSTAGETWOSTATE;
}

/*
 *  Remove a Locomotive from a LocoNet Universal Consist.
 *  @param address is the Locomotive address to add to the locomotive
 */
/*public*/ /*synchronized*/ void LocoNetConsist::removeFromCSConsist(DccLocoAddress* LocoAddress) {
    if (log->isDebugEnabled()) {
        log->debug("Remove Locomotive " // NOI18N
                + LocoAddress->toString()
                + " from Standard Consist " // NOI18N
                + consistAddress->toString()
                + ".");
    }
    if(consistList->size()==1 && LocoAddress == (consistAddress)){
      // there is only one address in this consist, no reason to link.
      notifyConsistListeners(LocoAddress,ConsistListener::OPERATION_SUCCESS);
      return;
    }
    slotManager->slotFromLocoAddress(LocoAddress->getNumber(), (SlotListener*)this);
    consistRequestState = UNLINKSTAGEONESTATE;
}

/*
 * create and send a message to link two slots
 * @param lead is the slot which is the leader
 * @param follow is the slot which will follow the leader
 */
/*private*/ void LocoNetConsist::linkSlots(LocoNetSlot* lead, LocoNetSlot* follow) {
    if (lead != follow) {
        LocoNetMessage* msg = new LocoNetMessage(4);
        msg->setOpCode(LnConstants::OPC_LINK_SLOTS);
        msg->setElement(1, follow->getSlot());
        msg->setElement(2, lead->getSlot());
        trafficController->sendLocoNetMessage(msg);
    } else {
      // lead == follow
      // this is an error, notify the consist listeners.
      follow->removeSlotListener((SlotListener*)this);
      notifyConsistListeners(new DccLocoAddress(follow->locoAddr(),
            throttleManager->canBeLongAddress(follow->locoAddr())),
            ConsistListener::CONSIST_ERROR);
    }
    consistRequestState = IDLESTATE;
    if (needToWrite.size() != 0) {
        delayedAdd();
    }
}

/*
 * create and send a message to unlink two slots
 * @param lead is the slot which is the leader
 * @param follow is the slot which was following the leader
 */
/*private*/ void LocoNetConsist::unlinkSlots(LocoNetSlot* lead, LocoNetSlot* follow) {
    if (lead != follow) {
        LocoNetMessage* msg = new LocoNetMessage(4);
        msg->setOpCode(LnConstants::OPC_UNLINK_SLOTS);
        msg->setElement(1, follow->getSlot());
        msg->setElement(2, lead->getSlot());
        trafficController->sendLocoNetMessage(msg);
    } else {
      // lead == follow
      // this is an error, notify the consist listeners.
      follow->removeSlotListener((SlotListener*)this);
      notifyConsistListeners(new DccLocoAddress(follow->locoAddr(),
            throttleManager->canBeLongAddress(follow->locoAddr())),
            ConsistListener::CONSIST_ERROR | ConsistListener::DELETE_ERROR );
    }
    consistRequestState = IDLESTATE;
    if (needToWrite.size() != 0) {
        delayedAdd();
    }
}

/*private*/ void LocoNetConsist::setDirection(LocoNetThrottle* t) {
    log->debug("consist " + consistAddress->toString() + " set direction for " + t->getLocoAddress()->toString());
    // send a command to set the direction
    // of the locomotive in the slot.
    bool directionNormal = getLocoDirection((DccLocoAddress*) t->getLocoAddress());
    if (directionNormal) {
        t->setIsForward(leadSlot->isForward());
    } else {
        t->setIsForward(!leadSlot->isForward());
    }

    consistRequestState = LINKSTAGETWOSTATE;
}

/*private*/ void LocoNetConsist::setSlotModeAdvanced(LocoNetSlot* s) {
    // set the slot so that it can be an advanced consist
    int oldstatus = s->slotStatus();
    int newstatus = oldstatus | LnConstants::STAT1_SL_SPDEX;
    trafficController->sendLocoNetMessage(s->writeStatus(newstatus));
}

// slot listener interface functions
//@Override
/*public*/ void LocoNetConsist::notifyChangedSlot(LocoNetSlot* s) {
    log->debug(tr("Notified slot ") + s->getSlot() // NOI18N
            + " changed with mode " + QString::number(consistRequestState) // NOI18N
            + " slot consist state: " // NOI18N
            + LnConstants::CONSIST_STAT(s->consistStatus()));
    switch (consistRequestState) {
        case LEADREQUESTSTATE:
            leadSlot = s;
            consistRequestState = IDLESTATE;
            break;
        case LINKSTAGEONESTATE:
            s->addSlotListener((SlotListener*)this);
            setSlotModeAdvanced(s);
            consistRequestState = LINKSTAGETWOSTATE;
            break;
        case LINKSTAGETWOSTATE:
            linkSlots(leadSlot, s);
            break;
        case UNLINKSTAGEONESTATE:
            unlinkSlots(leadSlot, s);
            break;
        default:
            s->removeSlotListener((SlotListener*)this);
            notifyConsistListeners(new DccLocoAddress(s->locoAddr(),
                    throttleManager->canBeLongAddress(s->locoAddr())),
                    ConsistListener::OPERATION_SUCCESS);
            if (needToWrite.size() != 0) {
                delayedAdd();
            } else {
                consistRequestState = IDLESTATE;
            }
    }
}

// Throttle listener interface functions
//@Override
/*public*/ void LocoNetConsist::notifyThrottleFound(DccThrottle* t) {
    log->debug("notified Throttle " + t->getLocoAddress()->toString() + " found with mode " + QString::number(consistRequestState));
    try {
        if (consistRequestState == LEADREQUESTSTATE) {
            ((LocoNetThrottle*) t)->setIsForward(true);
            leadSlot = ((LocoNetThrottle*) t)->getLocoNetSlot();
            consistRequestState = IDLESTATE;
            if (needToWrite.size() != 0) {
                delayedAdd();
            }
        } else {
            LocoNetSlot* tempSlot = ((LocoNetThrottle*) t)->getLocoNetSlot();
            tempSlot->addSlotListener((SlotListener*)this);
            if (consistRequestState == LINKSTAGEONESTATE) {
                notifyChangedSlot(tempSlot);
                setDirection(((LocoNetThrottle*) t));
                consistRequestState = LINKSTAGETWOSTATE;
            } else {
                setDirection(((LocoNetThrottle*) t));
            }
        }
    } catch (/*ClassCastException*/ Exception cce) {
        // if the simulator is in use, we will
        // get a ClassCastException.
        if (consistRequestState == LEADREQUESTSTATE) {
            t->setIsForward(true);
            consistRequestState = IDLESTATE;
            if (needToWrite.size() != 0) {
                delayedAdd();
            }
        } else {
            setDirection(((LocoNetThrottle*) t));
        }

    }
}

//@Override
/*public*/ void LocoNetConsist::notifyFailedThrottleRequest(LocoAddress* address, QString reason) {
    //if (! (address instanceof DccLocoAddress))
    if(qobject_cast<DccLocoAddress*>(address) == NULL)
    {
        throw new IllegalArgumentException("address is not a DccLocoAddress object " + reason);
    }
    notifyConsistListeners((DccLocoAddress*) address,
            ConsistListener::CONSIST_ERROR);
    removeFromConsistList((DccLocoAddress*) address);
    consistRequestState = IDLESTATE;
}

//@Override
/*public*/ void LocoNetConsist::notifyStealThrottleRequired(LocoAddress* address){
    // this is an automatically stealing impelementation.
    throttleManager->stealThrottleRequest(address, (ThrottleListener*)this, true);
}

/*private*/ /*final*/ /*static*/ Logger* LocoNetConsist::log = LoggerFactory::getLogger("LocoNetConsist");
