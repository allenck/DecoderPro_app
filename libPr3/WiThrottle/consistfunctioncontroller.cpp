#include "consistfunctioncontroller.h"
#include "loggerfactory.h"
#include "throttlecontroller.h"
#include "instancemanager.h"
/**
 *
 * @author Brett Hoffman Copyright (C) 2010, 2011
 */
// /*public*/ class ConsistFunctionController implements ThrottleListener {


/*public*/ ConsistFunctionController::ConsistFunctionController(ThrottleController* tc) {
common();
    throttleController = tc;
}

/*public*/ ConsistFunctionController::ConsistFunctionController(ThrottleController* tc, RosterEntry* re) {
 common();
    throttleController = tc;
    rosterLoco = re;
}
void ConsistFunctionController::common()
{
rosterLoco = NULL;
}

//@Override
/*public*/ void ConsistFunctionController::notifyThrottleFound(DccThrottle* t) {
    if (log->isDebugEnabled()) {
        log->debug(tr("Lead Loco throttle found: ") + t->getLocoAddress()->toString()
                + ", for consist: " + throttleController->getCurrentAddressString());
    }
    throttle = t;

    if (rosterLoco == NULL) {
        rosterLoco = throttleController->findRosterEntry(throttle);
    }

    throttleController->syncThrottleFunctions(throttle, rosterLoco);
    throttleController->setFunctionThrottle(t);
    throttleController->sendFunctionLabels(rosterLoco);
    throttleController->sendAllFunctionStates(throttle);
}

//@Override
/*public*/ void ConsistFunctionController::notifyFailedThrottleRequest(DccLocoAddress* address, QString reason) {
    log->error("Throttle request failed for " + address->toString() + " because " + reason);
}

/*public*/ void ConsistFunctionController::dispose() {
    InstanceManager::throttleManagerInstance()->releaseThrottle(throttle, this);
}

/*public*/ DccThrottle* ConsistFunctionController::getThrottle() {
    return throttle;
}

bool ConsistFunctionController::requestThrottle(DccLocoAddress* loco) {
    return InstanceManager::throttleManagerInstance()->requestThrottle(loco->getNumber(), loco->isLongAddress(), (ThrottleListener*)this);
}

/*private*/ /*final*/ /*static*/ Logger* ConsistFunctionController::log = LoggerFactory::getLogger("ConsistFunctionController");
