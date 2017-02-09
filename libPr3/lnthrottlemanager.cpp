#include "lnthrottlemanager.h"
//#include "loconetthrottle"

/**
 * LocoNet implementation of a ThrottleManager.
 * <P>
 * Works in cooperation with the SlotManager, which actually
 * handles the communications.
 *
 * @see SlotManager
 * @author		Bob Jacobsen  Copyright (C) 2001
 * @version 		$Revision: 20637 $
 */

/**
 * Constructor. Gets a reference to the LocoNet SlotManager.
 */

LnThrottleManager::LnThrottleManager(LocoNetSystemConnectionMemo* memo, QObject *parent) :
    AbstractThrottleManager(memo, parent)
{
    setObjectName("LnThrottleManager");
    //super(memo);
    this->slotManager = memo->getSlotManager();//slotManager;
    this->tc = memo->getLnTrafficController();
}

//public class LnThrottleManager extends AbstractThrottleManager implements ThrottleManager, SlotListener {

//    /**
//     * Constructor. Gets a reference to the LocoNet SlotManager.
//     */
//    public LnThrottleManager(LocoNetSystemConnectionMemo memo) {
//    	super(memo);
//        this.slotManager = memo.getSlotManager();//slotManager;
//        this.tc = memo.getLnTrafficController();
//    }

/**
 * LocoNet allows multiple throttles for the same device
 */
bool LnThrottleManager::singleUse() { return false; }


/**
 * Start creating a Throttle object.
 *
 * This returns directly, having arranged for the Throttle
 * object to be delivered via callback
 */
/*public*/ void LnThrottleManager::requestThrottleSetup(LocoAddress* address, bool /*control*/)
{
 slotManager->slotFromLocoAddress(address->getNumber(), (SlotListener*)this);
}


/**
 * LocoNet does have a Dispatch function
 **/
/*public*/ bool LnThrottleManager::hasDispatchFunction(){ return true; }

/**
 * What speed modes are supported by this system?
 * value should be xor of possible modes specifed by the
 * DccThrottle interface
 */
/*public*/ int LnThrottleManager::supportedSpeedModes()
{
 return(DccThrottle::SpeedStepMode128|
           DccThrottle::SpeedStepMode28|
           DccThrottle::SpeedStepMode28Mot|
           DccThrottle::SpeedStepMode14);
}

/**
 * SlotListener contract. Get notification that an address has changed slot.
 * This method creates a throttle for all ThrottleListeners of that address
 * and notifies them via the ThrottleListener.notifyThrottleFound method.
 */
/*public*/ void  LnThrottleManager::notifyChangedSlot(LocoNetSlot* s)
{
 DccThrottle* throttle = (DccThrottle*)new LocoNetThrottle((LocoNetSystemConnectionMemo*)adapterMemo, s);
 notifyThrottleKnown(throttle, new DccLocoAddress(s->locoAddr(),isLongAddress(s->locoAddr()) ) );
}

/**
 * Address 128 and above is a long address
 **/
/*public*/ bool  LnThrottleManager::canBeLongAddress(int address) {
    return isLongAddress(address);
}

/**
 * Address 127 and below is a short address
 **/
/*public*/ bool LnThrottleManager::canBeShortAddress(int address) {
    return !isLongAddress(address);
}

/**
 * Are there any ambiguous addresses (short vs long) on this system?
 */
/*public*/ bool LnThrottleManager::addressTypeUnique() { return true; }

/*
 * Local method for deciding short/long address
 */
/*protected static*/ bool LnThrottleManager::isLongAddress(int num) {
    return (num>=128);
}

/*public*/ bool LnThrottleManager::disposeThrottle(DccThrottle* t, ThrottleListener* l){
    if(AbstractThrottleManager::disposeThrottle(t, l)){
#if 1 // TODO> define LocoNetThrottle
        LocoNetThrottle* lnt = (LocoNetThrottle*) t;
        lnt->throttleDispose();
#endif
        return true;
    }
    return false;
    //LocoNetSlot tSlot = lnt.getLocoNetSlot();
}

/*public*/ void LnThrottleManager::dispatchThrottle(DccThrottle* t, ThrottleListener* l) {
            // set status to common
#if 1 // TODO> define LocoNetThrottle
    LocoNetThrottle* lnt = (LocoNetThrottle*) t;
    LocoNetSlot* tSlot = lnt->getLocoNetSlot();

    tc->sendLocoNetMessage(
            tSlot->writeStatus(LnConstants::LOCO_COMMON));

    // and dispatch to slot 0
    tc->sendLocoNetMessage(tSlot->dispatchSlot());
#endif

    AbstractThrottleManager::releaseThrottle(t, l);
}

/*public*/ void LnThrottleManager::releaseThrottle(DccThrottle* t, ThrottleListener* l)
{
 if(t == NULL) return;
    LocoNetThrottle* lnt = (LocoNetThrottle*) t;
    LocoNetSlot* tSlot = lnt->getLocoNetSlot();
    if (tSlot != NULL)
        tc->sendLocoNetMessage(
                tSlot->writeStatus(LnConstants::LOCO_COMMON));
    AbstractThrottleManager::releaseThrottle(t, l);
}
