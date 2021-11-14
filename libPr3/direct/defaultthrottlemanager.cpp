#include "defaultthrottlemanager.h"
#include "loggerfactory.h"
#include "directsystemconnectionmemo.h"
#include "instancemanager.h"
#include "defaultthrottle.h"
/**
 * Direct DCC implementation of a ThrottleManager.
 * <p>
 * When the traffic manager doesn't have anything else to do, it comes here to
 * get a command to send.
 * <p>
 * This is a partial implementation, which can only handle one Throttle at a
 * time. It also is missing logic to alternate sending speed and function
 * commands; right now it only sends the first group of function packets.
 *
 * @author Bob Jacobsen Copyright (C) 2004
 */
// /*public*/ class ThrottleManager extends AbstractThrottleManager {

    /**
     * Constructor for a Direct ThrottleManager.
     * @param memo system connection.
     */
    /*public*/ DefaultThrottleManager::DefaultThrottleManager(DirectSystemConnectionMemo* memo, QObject *parent): AbstractThrottleManager(memo, parent){
        //super(memo);
        tc = memo->getTrafficController();
        InstanceManager::setDefault("DefaultThrottleManager", this);
    }


    /**
     * Create throttle data structures.
     */
    //@Override
    /*public*/ void DefaultThrottleManager::requestThrottleSetup(LocoAddress* address, bool control) {
        if (currentThrottle != nullptr) {
            log->error(tr("DCC Direct cannot handle more than one throttle %1").arg(address->toString()));
            failedThrottleRequest(address, "DCC direct cannot handle more than one throttle "+ address->toString());
            return;
        }
        if (qobject_cast<DccLocoAddress*>(address)) {
            currentThrottle = new DefaultThrottle(((DccLocoAddress*) address), tc); // uses address object
            notifyThrottleKnown(currentThrottle, currentThrottle->getLocoAddress());
        }
        else {
            log->error(tr("LocoAddress %1 is not a DccLocoAddress").arg(address->toString()));
            failedThrottleRequest(address, "LocoAddress is not a DccLocoAddress " +address->toString());
        }
    }

    //@Override
    /*public*/ bool DefaultThrottleManager::addressTypeUnique() {
        return false;
    }

    //@Override
    /*public*/ bool DefaultThrottleManager::canBeShortAddress(int a) {
        return a < 128;
    }

    //@Override
    /*public*/ bool DefaultThrottleManager::canBeLongAddress(int a) {
        return a > 0;
    }

    /**
     * Invoked when a throttle is released, this updates the local data
     * structures.
     */
    //@Override
    /*public*/ bool DefaultThrottleManager::disposeThrottle(DccThrottle* t, ThrottleListener* l) {
        if (AbstractThrottleManager::disposeThrottle(t, l)) {
            currentThrottle = nullptr;
            return true;
        }
        return false;
    }

    /*private*/ /*final*/ /*static*/ Logger* DefaultThrottleManager::log = LoggerFactory::getLogger("ThrottleManager");
