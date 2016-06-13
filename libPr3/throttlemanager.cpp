#include "throttlemanager.h"
#include "abstractthrottlemanager.h"

/*static*/ /*private*/ ThrottleManager* ThrottleManager::mInstance = NULL;

ThrottleManager::ThrottleManager(QObject* parent ) : QObject(parent)
{
 setObjectName("ThrottleManager");
 log = new Logger("ThrottleManager");
 if (mInstance!=NULL) log->warn("Creating too many objects");
    mInstance = this;
    currentThrottle = NULL;
}
/**
 * Direct DCC implementation of a ThrottleManager.
 * <P>
 * When the traffic manager doesn't have anything else to
 * do, it comes here to get a command to send.
 * <P>
 * This is a partial implementation, which can only handle one
 * Throttle at a time. It also is missing logic to alternate
 * sending speed and function commands; right now it only
 * sends the first group of function packets.
 *
 * @author	    Bob Jacobsen  Copyright (C) 2004
 * @version         $Revision: 17977 $
 */
//public class ThrottleManager extends AbstractThrottleManager {

    /**
     * Constructor.
     */
//    /*public*/ ThrottleManager() {
//        super();
//        if (mInstance!=null) log.warn("Creating too many objects");
//        mInstance = this;
//    }

/*static*/ /*public*/ ThrottleManager* ThrottleManager::instance() {
    return mInstance;
}


/**
 * Create throttle data structures.
 */
///*public*/ void ThrottleManager::requestThrottleSetup(LocoAddress* address, bool control)
//{
// if (currentThrottle != NULL)
// {
//  log->error("DCC direct cannot handle more than one throttle now");
//  failedThrottleRequest((DccLocoAddress*) address, "DCC direct cannot handle more than one throttle " + (QString("%1").arg(address->getNumber())));
//  return;
// }
//  log->warn("requestThrottleSetup should preserve actual address object, not use ints");
//  //currentThrottle = (Throttle*)new AbstractThrottle(((DccLocoAddress*)address)->getNumber());
//  notifyThrottleKnown((DccThrottle*)currentThrottle, currentThrottle->getLocoAddress());
//}

///*public*/ bool ThrottleManager::addressTypeUnique() { return false; }
///*public*/ bool ThrottleManager::canBeShortAddress(int a) { return a<128; }
///*public*/ bool ThrottleManager::canBeLongAddress(int a) { return a>0; }

/**
 * Invoked when a throttle is released, this updates
 * the local data structures
 */
///*public*/ bool ThrottleManager::disposeThrottle(DccThrottle* t, ThrottleListener* l)
//{
// //if (super.disposeThrottle(t, l))
// if(AbstractThrottleManager::disposeThrottle(t, l))
// {
//  currentThrottle = NULL;
//  return true;
// }
// return false;
//}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(ThrottleManager.class.getName());

//}
