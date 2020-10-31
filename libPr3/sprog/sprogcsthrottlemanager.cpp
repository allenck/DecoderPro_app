#include "sprogcsthrottlemanager.h"
#include "loggerfactory.h"
#include "sprogcsthrottle.h"
using namespace Sprog;

/**
 * SPROG Command Station implementation of a ThrottleManager.
 * <P>
 * Updated by Andrew Crosland February 2012 to enable 28 step speed packets</P>
 *
 * @author	Andrew Crosland Copyright (C) 2006, 2012
 */
///*public*/ class SprogCSThrottleManager extends AbstractThrottleManager {

/**
 * Constructor.
 */
/*public*/ SprogCSThrottleManager::SprogCSThrottleManager(SprogSystemConnectionMemo* memo, QObject* parent) : AbstractThrottleManager(memo, parent) {
    //super(memo);
}

//@Override
/*public*/ void SprogCSThrottleManager::requestThrottleSetup(LocoAddress* a, bool control) {
    // The SPROG protocol doesn't require an interaction with the command
    // station for this, so immediately trigger the callback
    DccLocoAddress* address = (DccLocoAddress*) a;
    log->debug("new SprogThrottle for " + address->toString());
    notifyThrottleKnown(new SprogCSThrottle((SprogSystemConnectionMemo*) adapterMemo, address), address);
}

/**
 * What speed modes are supported by this system? value should be or of
 * possible modes specified by the DccThrottle interface
 */
//@Override
/*public*/ QSet<SpeedStepMode::SSMODES> SprogCSThrottleManager::supportedSpeedModes() {
 QSet<SpeedStepMode::SSMODES> modes = QSet<SpeedStepMode::SSMODES>();
    modes.insert(SpeedStepMode::NMRA_DCC_128);
    modes.insert(SpeedStepMode::NMRA_DCC_28);
    return modes;
}

/**
 * Addresses 0-10239 can be long
 *
 */
//@Override
/*public*/ bool SprogCSThrottleManager::canBeLongAddress(int address) {
    return ((address >= 0) && (address <= 10239));
}

/**
 * The short addresses 1-127 are available
 *
 */
//@Override
/*public*/ bool SprogCSThrottleManager::canBeShortAddress(int address) {
    return ((address >= 1) && (address <= 127));
}

/**
 * Are there any ambiguous addresses (short vs long) on this system?
 */
//@Override
/*public*/ bool SprogCSThrottleManager::addressTypeUnique() {
    return false;
}

//@Override
/*public*/ bool SprogCSThrottleManager::disposeThrottle(DccThrottle* t, ThrottleListener* l) {
    if (AbstractThrottleManager::disposeThrottle(t, l)) {
        SprogCSThrottle* lnt = (SprogCSThrottle*) t;
        lnt->throttleDispose();
        return true;
    }
    return false;
}

/*private*/ /*final*/ /*static*/ Logger* SprogCSThrottleManager::log = LoggerFactory::getLogger("SprogCSThrottleManager");
