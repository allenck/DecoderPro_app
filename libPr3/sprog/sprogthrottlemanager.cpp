#include "sprogthrottlemanager.h"
#include "sprogthrottle.h"
#include "loggerfactory.h"


using namespace Sprog;

/**
 * SPROG implementation of a ThrottleManager.
 * <p>
 * Updated by Andrew Crosland February 2012 to enable 28 step speed packets
 *
 * @author	Bob Jacobsen Copyright (C) 2001
 */
///*public*/ class SprogThrottleManager extends AbstractThrottleManager {

/**
 * Constructor.
 */
/*public*/ SprogThrottleManager::SprogThrottleManager(SprogSystemConnectionMemo* memo, QObject* parent) : AbstractThrottleManager(memo, parent)
{
    //super(memo);
 throttleInUse = false;

}

/**
 * @deprecated JMRI Since 4.4 instance() shouldn't be used, convert to JMRI multi-system support structure
 */
//@Deprecated
/*static*/ /*public*/ SprogThrottleManager* SprogThrottleManager::instance() {
    return NULL;
}


void SprogThrottleManager::release() {
    throttleInUse = false;
}

//@Override
/*public*/ void SprogThrottleManager::requestThrottleSetup(LocoAddress* a, bool control) {
    // The SPROG protocol doesn't require an interaction with the command
    // station for this, so set the address and immediately trigger the callback
    // if a throttle is not in use.
        DccLocoAddress* address = (DccLocoAddress*) a;
    if (!throttleInUse) {
        throttleInUse = true;
        log->debug("new SprogThrottle for " + address->toString());
        QString addr = "" + QString::number(address->getNumber()) + ( address->isLongAddress() ? " 0" : "");
        SprogMessage* m = new SprogMessage(2 + addr.length());
        int i = 0;
        m->setElement(i++, 'A');
        m->setElement(i++, ' ');
        for (int j = 0; j < addr.length(); j++) {
            m->setElement(i++, addr.toLocal8Bit().at(j));
        }
        ((SprogSystemConnectionMemo*) adapterMemo)->getSprogTrafficController()->sendSprogMessage(m, NULL);
        notifyThrottleKnown(new SprogThrottle((SprogSystemConnectionMemo*) adapterMemo, address), address);
    } else {
        failedThrottleRequest(address, "Only one Throttle can be in use at anyone time with the Sprog.");
        //javax.swing.JOptionPane.showMessageDialog(NULL,"Only one Throttle can be in use at anyone time with the Sprog.","Sprog Throttle",javax.swing.JOptionPane.WARNING_MESSAGE);
        log->warn("Single SPROG Throttle already in use");
    }
}

/**
 * What speed modes are supported by this system? Value should be one of
 * possible modes specified by the DccThrottle interface.
 */
//@Override
/*public*/ QSet<SpeedStepMode::SSMODES> SprogThrottleManager::supportedSpeedModes() {
 QSet<SpeedStepMode::SSMODES> modes = QSet<SpeedStepMode::SSMODES>();
    modes.insert(SpeedStepMode::NMRA_DCC_128);
    modes.insert(SpeedStepMode::NMRA_DCC_28);
    return modes;
}

/**
 * Addresses 0-10239 can be long.
 */
//@Override
/*public*/ bool SprogThrottleManager::canBeLongAddress(int address) {
    return ((address >= 0) && (address <= 10239));
}

/**
 * The short addresses 1-127 are available.
 */
//@Override
/*public*/ bool SprogThrottleManager::canBeShortAddress(int address) {
    return ((address >= 1) && (address <= 127));
}

/**
 * Are there any ambiguous addresses (short vs long) on this system?
 */
//@Override
/*public*/ bool SprogThrottleManager::addressTypeUnique() {
    return false;
}

//@Override
/*public*/ bool SprogThrottleManager::disposeThrottle(DccThrottle* t, ThrottleListener* l) {
    if (AbstractThrottleManager::disposeThrottle(t, l)) {
        throttleInUse = false;
        return true;
    }
    return false;
}

/*private*/ /*final*/ /*static*/ Logger* SprogThrottleManager::log = LoggerFactory::getLogger("SprogThrottleManager");


