#include "lnpr2throttlemanager.h"
#include "loggerfactory.h"
#include "dcclocoaddress.h"
#include "pr2throttle.h"

/**
 * LocoNet implementation of a ThrottleManager for the PR2.
 * <p>
 * Does direct "push" writes to the extended slot in the PR2.
 * <p>
 * The PR2 only allows a single locomotive address to be active, because it
 * implements a single-slot command station.
 *
 * @see AbstractThrottleManager
 * @author Bob Jacobsen Copyright (C) 2001, 2006
 */
///*public*/ class LnPr2ThrottleManager extends AbstractThrottleManager {

/**
 * Constructor, works via superclass.
 */
/*public*/ LnPr2ThrottleManager::LnPr2ThrottleManager(LocoNetSystemConnectionMemo* memo, QObject* parent) : AbstractThrottleManager((SystemConnectionMemo*)memo, parent) {
    //super(memo);
}

/**
 * PR2 allows only one throttle
 */
//@Override
/*protected*/ bool LnPr2ThrottleManager::singleUse() {
    return true;
}

/**
 * Get a new Throttle object.
 *
 * This immediately invokes the callback with the a new throttle object.
 */
//@Override
/*public*/ void LnPr2ThrottleManager::requestThrottleSetup(LocoAddress* address, bool control) {
    // The PR2 has only one slot, hence
    // doesn't require an interaction with the command
    // station to allocate slot, so immediately trigger the callback.
    if (qobject_cast<DccLocoAddress*>(address)) {
        activeAddress = (DccLocoAddress*) address;
    } else {
        log->error("cannot cast the passed address to DccLocoAddress.");
    }
    log->debug("new Pr2Throttle for " + activeAddress->toString());
    notifyThrottleKnown(new Pr2Throttle((LocoNetSystemConnectionMemo*) adapterMemo, activeAddress), activeAddress);
}


/**
 * PR2 does not have a Dispatch function
 *
 */
//@Override
/*public*/ bool LnPr2ThrottleManager::hasDispatchFunction() {
    return false;
}

/**
 * Address 128 and above is a long address
 *
 */
//@Override
/*public*/ bool LnPr2ThrottleManager::canBeLongAddress(int address) {
    return isLongAddress(address);
}

/**
 * Address 127 and below is a short address
 *
 */
//@Override
/*public*/ bool LnPr2ThrottleManager::canBeShortAddress(int address) {
    return !isLongAddress(address);
}

/**
 * Are there any ambiguous addresses (short vs long) on this system?
 */
//@Override
/*public*/ bool LnPr2ThrottleManager::addressTypeUnique() {
    return true;
}

/*
 * Local method for deciding short/long address
 */
/*static*/ bool LnPr2ThrottleManager::isLongAddress(int num) {
    return (num >= 128);
}

/**
 * Make the active address available to the power manager, which needs it to
 * turn on and off "neutral mode" in the locomotive
 */
/*public*/ DccLocoAddress* LnPr2ThrottleManager::getActiveAddress() {
    return activeAddress;
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* LnPr2ThrottleManager::log = LoggerFactory::getLogger("LnPr2ThrottleManager");

