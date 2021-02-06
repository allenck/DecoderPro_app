#include "lnthrottlemanager.h"
//#include "loconetthrottle"
#include "loggerfactory.h"
#include "speedstepmode.h"
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
    waitingForNotification = QHash<int, QThread*>();
    //waitingForNotification.insert(0, nullptr);

    //super(memo);
    this->slotManager = memo->getSlotManager();//slotManager;
    this->tc = memo->getLnTrafficController();
    requestList = QLinkedList<ThrottleRequest*>();
    slotForAddress = QHash<int, LocoNetSlot*>();

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
* This returns directly, having arranged for the Throttle object to be
* delivered via callback since there are situations where the command
* station does not respond, (slots full, command station powered off,
* others?) this code will retry and then fail the request if no response
* occurs.
*
* @param address locomotive address to be controlled
* @param control true if throttle wishes to control the speed and direction
* of the loco.
*/
//@Override
/*public*/ void LnThrottleManager::requestThrottleSetup(LocoAddress* address, bool control) {
   log->debug(tr("requestThrottleSetup: address %1, control %2").arg(address->toString()).arg(control?"true":"false"));
   if(requestOutstanding) {
      try {
         // queue this request for later.
         requestList.append(new ThrottleRequest(address,control));
      } catch(InterruptedException ie){
         log->error("Interrupted while trying to store throttle request");
         requestOutstanding = false;
         return;
      }
   } else {
      // handle this now
      requestOutstanding = true;
      processThrottleSetupRequest(address, control);
   }
}

/**
* Processes the next loco from the queue of requested locos for which to get
* a LocoNetThrottle.
*/
/*protected*/ void LnThrottleManager::processQueuedThrottleSetupRequest(){
   if(requestOutstanding) {
      return;
   } else if(requestList.size() != 0 ){
      requestOutstanding = true;
      try {
         ThrottleRequest* tr = requestList.first();
         processThrottleSetupRequest(tr->getAddress(),tr->getControl());
      } catch(InterruptedException ie){
         log->error("Interrupted while trying to process process throttle request");
         requestOutstanding = false;
         return;
      }
   }
}

/**
 * Begin the processing of a Throttle Request.
 *
 * @param address Loco address
 * @param control whether the throttle object wants to control the loco
 */
/*private*/ void LnThrottleManager::processThrottleSetupRequest(LocoAddress* address, bool control)
{
 slotManager->slotFromLocoAddress(address->getNumber(), (SlotListener*)this);  //first try

//    class RetrySetup implements Runnable {  //setup for retries and failure check

//        DccLocoAddress address;
//        SlotListener list;

//        RetrySetup(DccLocoAddress address, SlotListener list) {
//            this.address = address;
//            this.list = list;
//        }

//        @Override
//        public void run() {
//            int attempts = 1; // already tried once above
//            int maxAttempts = 10;
//            while (attempts <= maxAttempts) {
//                try {
//                    Thread.sleep(1000); // wait one second
//                } catch (InterruptedException ex) {
//                    return; // stop waiting if slot is found or error occurs
//                }
//                String msg = "No response to slot request for {}, attempt {}"; // NOI18N
//                if (attempts < maxAttempts) {
//                    slotManager.slotFromLocoAddress(address.getNumber(), list);
//                    msg += ", trying again."; // NOI18N
//                }
//                log->debug(msg, address, attempts);
//                attempts++;
//            }
//            log->error("No response to slot request for {} after {} attempts.", address, attempts - 1); // NOI18N
//            failedThrottleRequest(address, "Failed to get response from command station");
//            requestOutstanding = false;
//            processQueuedThrottleSetupRequest();
//        }
//    }
#if 1
    retrySetupThread = new QThread();
    RetrySetup* retrySetup = new RetrySetup(new DccLocoAddress(address->getNumber(),
                    isLongAddress(address->getNumber())), this);
    retrySetupThread->setObjectName("LnThrottleManager RetrySetup "+address->toString());
    connect(retrySetupThread, SIGNAL(started()), retrySetup, SLOT(process()));
    connect(retrySetup, SIGNAL(finished()), retrySetupThread, SLOT(quit()));
    connect(retrySetup, SIGNAL(finished()), retrySetupThread, SLOT(deleteLater()));
    retrySetup->moveToThread(retrySetupThread);
    retrySetupThread->start();
    waitingForNotification.insert(address->getNumber(), retrySetupThread);
#endif
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
/*public*/ QSet<SpeedStepMode::SSMODES> LnThrottleManager::supportedSpeedModes()
{
 QSet<SpeedStepMode::SSMODES> modes = QSet<SpeedStepMode::SSMODES>();
 modes.insert(SpeedStepMode::NMRA_DCC_128);
 modes.insert(SpeedStepMode::NMRA_DCC_28);
 modes.insert(SpeedStepMode::MOTOROLA_28);
 modes.insert(SpeedStepMode::NMRA_DCC_14);
 return modes;
}

/**
 * Get notification that an address has changed slot. This method creates a
 * throttle for all ThrottleListeners of that address and notifies them via
 * the ThrottleListener.notifyThrottleFound method.
 *
 * @param s LocoNet slot which has been changed
 */
//@Override
/*public*/ void LnThrottleManager::notifyChangedSlot(LocoNetSlot* s) {
    log->debug(tr("notifyChangedSlot - slot %1, slotStatus %2").arg(s->getSlot()).arg(QString::number(s->slotStatus(),16)));
    // This is invoked only if the SlotManager knows that the LnThrottleManager is
    // interested in the address associated with this slot.

    // need to check to see if the slot is in a suitable state for creating a throttle.
    if (s->slotStatus() == LnConstants::LOCO_IN_USE) {
        // loco is already in-use
        log->warn(tr("slot %1 address %2 is already in-use.").arg(
                s->getSlot()).arg(s->locoAddr()));
        // is the throttle ID the same as for this JMRI instance?  If not, do not accept the slot.
        if ((s->id() != 0) && s->id() != throttleID) {
            // notify the LnThrottleManager about failure of acquisition.
            // NEED TO TRIGGER THE NEW "STEAL REQUIRED" FUNCITONALITY HERE
            //note: throttle listener expects to have "callback" method notifyDecisionRequired
            //invoked if a "steal" is required.  Make that happen as part of the "acquisition" process
            slotForAddress.insert(s->locoAddr(),s);
            notifyStealRequest(s->locoAddr());
            return;
        }
    }
    commitToAcquireThrottle(s);
}

/**
 * Making progress in the process of acquiring a throttle.
 *
 * @param s slot to be acquired
 */
/*private*/ void LnThrottleManager::commitToAcquireThrottle(LocoNetSlot* s) {
    // haven't identified a particular reason to refuse throttle acquisition at this time...
    DccThrottle* throttle = createThrottle((LocoNetSystemConnectionMemo*) adapterMemo, s);
    s->notifySlotListeners();    // make sure other listeners for this slot know about what's going on!
    notifyThrottleKnown(throttle, new DccLocoAddress(s->locoAddr(), isLongAddress(s->locoAddr())));
    //end the waiting thread since we got a response
    if (waitingForNotification.contains(s->locoAddr())) {
        log->debug(tr("LnThrottleManager.notifyChangedSlot() - removing throttle acquisition notification flagging for address %1").arg(s->locoAddr() ));
        waitingForNotification.value(s->locoAddr())->exit();
        waitingForNotification.remove(s->locoAddr());
    }
    else {
        log->debug(tr("LnThrottleManager.notifyChangedSlot() - ignoring slot notification for slot %1, address %2 account not attempting to acquire that address").arg(s->getSlot()).arg(s->locoAddr() ));
    }
    if (slotForAddress.contains(s->locoAddr())) {
        slotForAddress.remove(s->locoAddr());
    }
    requestOutstanding = false;
    processQueuedThrottleSetupRequest();
}
/**
 * Loco acquisition failed. Propagate the failure message to the (GUI)
 * throttle.
 *
 * @param address of the loco which could not be acquired
 * @param cause reason for the failure
 */
/*public*/ void LnThrottleManager::notifyRefused(int address, QString cause) {
    //end the waiting thread since we got a failure response
    if (waitingForNotification.contains(address)) {
        waitingForNotification.value(address)->exit();
        waitingForNotification.remove(address);
        // notify the throttle - in some other thread!

//        class InformRejection implements Runnable {
//            // inform the throttle from a new thread, so that
//            // the modal dialog box doesn't block other LocoNet
//            // message handling

//            int address;
//            String cause;

//            InformRejection(int address, String s) {
//                this.address = address;
//                this.cause = s;
//            }

//            @Override
//            public void run() {

//                log->debug("New thread launched to inform throttle user of failure to acquire loco {} - {}", address, cause);
//                failedThrottleRequest(new DccLocoAddress(address, isLongAddress(address)), cause);
//            }
//        }
        QThread* thr = new QThread(new InformRejection( address, cause,this));
        thr->start();
    }
    if (slotForAddress.contains(address)) {
        slotForAddress.remove(address);
    }
    requestOutstanding = false;
    processQueuedThrottleSetupRequest();
}


/**
 * Create a LocoNet Throttle to control a loco.
 * <p>
 * This is called during the loco acquisition process by logic within
 * LnThrottleManager.  Generally, it should not be directly called by other
 * methods.
 *
 * @param memo connection memo used by the throttle for communications
 * @param s slot holding an acquired loco
 * @return throttle holding an acquired loco
 */
DccThrottle* LnThrottleManager::createThrottle(LocoNetSystemConnectionMemo* memo, LocoNetSlot* s) {
    log->debug(tr("createThrottle: slot %1").arg(s->getSlot()));
    return new LocoNetThrottle(memo, s);
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
 if(t == NULL) 
  return;
 LocoNetThrottle* lnt = (LocoNetThrottle*) t;
 LocoNetSlot* tSlot = lnt->getLocoNetSlot();
 if (tSlot != NULL)
     tc->sendLocoNetMessage(tSlot->writeStatus(LnConstants::LOCO_COMMON));
 AbstractThrottleManager::releaseThrottle(t, l);
}
/**
 * Cancels the loco acquisition process when throttle acquisition of a loco
 * fails.
 *
 * @param address loco address which could not be acquired
 * @param reason for the failure
 */
//@Override
/*public*/ void LnThrottleManager::failedThrottleRequest(LocoAddress* address, QString reason) {
    AbstractThrottleManager::failedThrottleRequest(address, reason);
    log->debug(tr("failedThrottleRequest - address %1, reason %2").arg(address->toString()).arg(reason));
    //now end and remove any waiting thread
    if (waitingForNotification.contains(address->getNumber())) {
        waitingForNotification.value(address->getNumber())->exit();
        waitingForNotification.remove(address->getNumber());
    }
    if (slotForAddress.contains(address->getNumber())) {
        slotForAddress.remove(address->getNumber());
    }
    requestOutstanding = false;
    processQueuedThrottleSetupRequest();
}

/**
 * Cancel a request for a throttle.
 *
 * @param address The decoder address desired.
 *                address.
 * @param l       The ThrottleListener cancelling request for a throttle.
 */
//@Override
/*public*/ void LnThrottleManager::cancelThrottleRequest(LocoAddress* address, ThrottleListener* l) {

    // calling super removes the ThrottleListener from the callback list,
    // The listener which has just sent the cancel doesn't need notification
    // of the cancel but other listeners might
    AbstractThrottleManager::cancelThrottleRequest(address, l);

    failedThrottleRequest(address, "Throttle Request " + address->toString() + " Cancelled.");

    int loconumber = address->getNumber();
    log->debug(tr("cancelThrottleRequest - loconumber %1").arg(loconumber));
    if (waitingForNotification.contains(loconumber)) {
        waitingForNotification.value(loconumber)->exit();
        waitingForNotification.remove(loconumber);
    }
    if (slotForAddress.contains(loconumber)) {
        slotForAddress.remove(loconumber);
    }
    requestOutstanding = false;
    processQueuedThrottleSetupRequest();
}


/**
 * Get the ThrottleID value for this throttle.
 *
 * @return the ThrottleID value
 */
/*public*/ int LnThrottleManager::getThrottleID(){
    return throttleID;
}

/**
 * Dispose of this manager, typically for testing.
 */
void LnThrottleManager::dispose() {
#if 1
    if (retrySetupThread != nullptr) {
        try {
            retrySetupThread->exit();
//            retrySetupThread->join();
        } catch (InterruptedException ex) {
            log->warn("dispose interrupted");
        }
    }
#endif
}

/**
 * Inform the requesting throttle object (not the connection-specific throttle
 * implementation!)  that the address is in-use and the throttle user may
 * either choose to "steal" the address, or quit the acquisition process.
 * The LocoNet acquisition process "retry" timer is stopped as part of this
 * process, since a positive response has been received from the command station
 * and since user intervention is required.
 *
 * Reminder: for LocoNet throttles which are not using "expanded slot"
 * functionality, "steal" really means "share".  For those LocoNet throttles
 * which are using "expanded slots", "steal" really means take control and
 * let the command station issue a "StealZap" LocoNet message to the other throttle.
 *
 * @param locoAddr address of DCC loco or consist
 */
/*public*/ void LnThrottleManager::notifyStealRequest(int locoAddr) {
    // need to find the "throttleListener" associated with the request for locoAddr, and
    // send that "throttleListener" a notification that the command station needs
    // permission to "steal" the loco address.
    if (waitingForNotification.contains(locoAddr)) {
        waitingForNotification.value(locoAddr)->quit();
        waitingForNotification.remove(locoAddr);

        notifyDecisionRequest(new DccLocoAddress(locoAddr, isLongAddress(locoAddr)),ThrottleListener::DecisionType::STEAL);
    }
}

/**
 * Perform the actual "Steal" of the requested throttle.
 * <p>
 * This is a call-back, as a result of the throttle user's agreement to
 * "steal" the locomotive.
 * <p>
 * Reminder: for LocoNet throttles which are not using "expanded slot"
 * functionality, "steal" really means "share".  For those LocoNet throttles
 * which are using "expanded slots", "steal" really means "force any other
 * throttle running that address to drop the loco".
 *
 * @param address desired DccLocoAddress
 * @param decision made by the ThrottleListener, only listening for STEAL
 * @since 4.9.2
 */
//@Override
/*public*/ void LnThrottleManager::responseThrottleDecision(LocoAddress* address, ThrottleListener* l, ThrottleListener::DecisionType decision){

    log->debug(tr("%1 decision invoked for address %2").arg(decision).arg(address->getNumber() ));

    if ( decision == ThrottleListener::DecisionType::STEAL ) {
        // Steal is currently implemented by using the same method
        // we used to aquire the slot prior to the release of
        // Digitrax command stations with expanded slots.
        LocoNetSlot* slot = slotForAddress.value(address->getNumber());
        // Only continue if address is found in a slot
        if (slot != nullptr) {
            commitToAcquireThrottle(slot);
        } else {
            log->error(tr("Address %1 not found in list of slots").arg(address->getNumber()));
        }
    } else {
        log->error(tr("Invalid DecisionType %1 for LnThrottleManager.").arg(decision));
    }
}
/*private*/ /*final*/ /*static*/ Logger* LnThrottleManager::log = LoggerFactory::getLogger("LnThrottleManager");
