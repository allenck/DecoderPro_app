#include "debugthrottlemanager.h"
#include "debugthrottle.h"

DebugThrottleManager::DebugThrottleManager(QObject *parent) : AbstractThrottleManager(parent)
{
    log = new  Logger("DebugThrottleManager");
}
/**
 * Implementation of a ThrottleManager for debugging.
 * <P>
 * @author	    Bob Jacobsen  Copyright (C) 2003, 2005
 * @version         $Revision: 23516 $
 */
// /*public*/ class DebugThrottleManager extends AbstractThrottleManager {

///*public*/ DebugThrottleManager(){
//    super();
//}
/**
 * Constructor.
 */
/*public*/ DebugThrottleManager::DebugThrottleManager(SystemConnectionMemo* memo, QObject *parent) :  AbstractThrottleManager(memo, parent)
{
    //super(memo);
    log = new  Logger("DebugThrottleManager");
}

/*public*/ void DebugThrottleManager::requestThrottleSetup(LocoAddress* a, bool control) {
    // Immediately trigger the callback.
    DccLocoAddress* address = (DccLocoAddress*) a;
    log->debug("new debug throttle for "+address->toString());
    notifyThrottleKnown(new DebugThrottle(address, adapterMemo), a);
}

/**
 * Address 1 and above can be a long address
 **/
/*public*/ bool DebugThrottleManager::canBeLongAddress(int address) {
    return (address>=1);
}

/**
 * Address 127 and below can be a short address
 **/
/*public*/ bool DebugThrottleManager::canBeShortAddress(int address) {
    return (address<=127);
}

/**
 * Are there any ambiguous addresses (short vs long) on this system?
 */
/*public*/ bool DebugThrottleManager::addressTypeUnique() { return false; }

/*public*/ bool DebugThrottleManager::disposeThrottle(DccThrottle* t, ThrottleListener* l){
    log->debug("disposeThrottle called for " + t->objectName());
    if ( AbstractThrottleManager::disposeThrottle(t, l)){
        DebugThrottle* lnt = (DebugThrottle*) t;
        lnt->throttleDispose();
        return true;
    }
    return false;
}

    /**
 * What speed modes are supported by this system?
 * value should be xor of possible modes specifed by the
 * DccThrottle interface
 */
/*public*/ QSet<SpeedStepMode::SSMODES> DebugThrottleManager::supportedSpeedModes() {
 QSet<SpeedStepMode::SSMODES> modes = QSet<SpeedStepMode::SSMODES>();
    modes.insert(SpeedStepMode::NMRA_DCC_128);
    modes.insert(SpeedStepMode::NMRA_DCC_28);
    modes.insert(SpeedStepMode::NMRA_DCC_27);
    modes.insert(SpeedStepMode::NMRA_DCC_14);
    return modes;
}
