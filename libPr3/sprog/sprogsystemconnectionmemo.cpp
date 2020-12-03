#include "sprogsystemconnectionmemo.h"
#include "loggerfactory.h"
#include "sprogconnectiontypelist.h"
#include "instancemanager.h"
#include "serialdriveradapter.h"
#include "globalprogrammermanager.h"
#include "sprogversionquery.h"
#include "sprogversion.h"
#include "sprogcomponentfactory.h"
#include "sprogprogrammer.h"
#include "sprogprogrammermanager.h"
#include "sprogturnout.h"
#include "sprogthrottlemanager.h"
#include "sprogturnoutmanager.h"
#include "sprogcsthrottlemanager.h"

using namespace Sprog;
/**
 * Lightweight class to denote that a system is active, and provide general
 * information.
 * <p>
 * Objects of specific subtypes are registered in the instance manager to
 * activate their particular system.
 *
 * @author Bob Jacobsen Copyright (C) 2010
 */
// /*public*/ class SprogSystemConnectionMemo extends jmrix.SystemConnectionMemo {

/*public*/ SprogSystemConnectionMemo::SprogSystemConnectionMemo(SprogTrafficController* st, SprogConstants::SprogMode sm, QObject* parent)
 : DefaultSystemConnectionMemo(st->getController()->getSystemConnectionMemo()->getSystemPrefix(), SprogConnectionTypeList::SPROG, parent)
{
    //super(st.getController().getSystemConnectionMemo().getSystemPrefix(), SprogConnectionTypeList.SPROG);
    if (log->isDebugEnabled()) {
        log->debug(tr("SprogSystemConnectionMemo, prefix='%1'").arg(st->getController()->getSystemConnectionMemo()->getSystemPrefix()));
    }
    common(sm);
    this->st = st;
}

/*public*/ SprogSystemConnectionMemo::SprogSystemConnectionMemo(SprogConstants::SprogMode sm, QObject* parent)
 : DefaultSystemConnectionMemo("S", SprogConnectionTypeList::SPROG, parent)
{
    //super("S", SprogConnectionTypeList::SPROG); // default to S
 common(sm);
}

void SprogSystemConnectionMemo::common(SprogConstants::SprogMode sm)
{
 cf = NULL;
 svq = NULL;
 programmerManager = NULL;
 sprogCSThrottleManager = NULL;
 sprogThrottleManager = NULL;
 sprogTurnoutManager = NULL;
 powerManager = NULL;
 //setDisabled(true);

 sprogMode = sm;  // static
 sprogVersion = new SprogVersion(new SprogType(SprogType::UNKNOWN));
 _register();
 InstanceManager::store(this, "SprogSystemConnectionMemo"); // also register as specific type
 InstanceManager::store(cf = new SprogComponentFactory(this), "ComponentFactory");
}

/*public*/ SprogSystemConnectionMemo::SprogSystemConnectionMemo(SprogConstants::SprogMode sm, SprogType* type, QObject* parent)
 : DefaultSystemConnectionMemo("S", SprogConnectionTypeList::SPROG, parent)
{
    //super("S", SprogConnectionTypeList::SPROG); // default to S
    common(sm);
}

/*public*/ SprogSystemConnectionMemo::SprogSystemConnectionMemo(QObject* parent) {
    common(SprogConstants::SprogMode::OPS);
}

/**
 * Set the SPROG mode for this connection.
 *
 * @param mode selected mode
 */
/*public*/ void SprogSystemConnectionMemo::setSprogMode(SprogConstants::SprogMode mode) {
    sprogMode = mode;
}

/**
 * Return the SPROG mode for this connection.
 *
 * @return SprogMode
 */
/*public*/ SprogConstants::SprogMode SprogSystemConnectionMemo::getSprogMode() {
    return sprogMode;
}

/**
 * Return the SPROG version object for this connection.
 *
 * @return SprogVersion
 */
/*public*/ SprogVersion* SprogSystemConnectionMemo::getSprogVersion() {
    return sprogVersion;
}

/**
 * Set the SPROG version object for this connection.
 *
 * @param version type and version class
 */
/*public*/ void SprogSystemConnectionMemo::setSprogVersion(SprogVersion* version) {
    sprogVersion = version;
}


/**
 * Return the type of SPROG connected.
 *
 * @return SprogType set
 */
/*public*/ SprogType* SprogSystemConnectionMemo::getSprogType() {
    return sprogVersion->sprogType;
}


/**
 * Provide access to the TrafficController for this particular connection.
 *
 * @return current tc for this connection
 */
/*public*/ SprogTrafficController* SprogSystemConnectionMemo::getSprogTrafficController() {
    return st;
}

/*public*/ void SprogSystemConnectionMemo::setSprogTrafficController(SprogTrafficController* st) {
    this->st = st;
}


/*public*/ QThread* SprogSystemConnectionMemo::getSlotThread() {
    return slotThread;
}

/**
 * Configure the programming manager and "command station" objects.
 */
/*public*/ void SprogSystemConnectionMemo::configureCommandStation()
{
 log->debug("start command station queuing thread");
 commandStation = new SprogCommandStation(st);
 commandStation->setSystemConnectionMemo(this);
 InstanceManager::store(commandStation, "CommandStation");
 switch (sprogMode)
 {
  case SprogConstants::OPS:
//            slotThread = new Thread(commandStation);
   slotThread = new QThread();
   commandStation->moveToThread(slotThread);
   connect(slotThread, SIGNAL(started()), commandStation, SLOT(run()));
   connect(commandStation, SIGNAL(finished()), slotThread, SLOT(quit()));
   slotThread->setObjectName("SPROG slot thread");
   slotThread->start();
   break;
  case SprogConstants::SERVICE:
   break;
  default:
   log->error("Unhandled sprogMode: {}", sprogMode);
   break;
 }
}

/**
 * Get the command station object associated with this connection.
 */
/*public*/ SprogCommandStation* SprogSystemConnectionMemo::getCommandStation() {
    return commandStation;
}

//@Override
/*public*/ bool SprogSystemConnectionMemo::provides(QString type) {
    if (getDisabled()) {
        return false;
    }
    if (type == ("GlobalProgrammerManager")) {
         return getProgrammerManager()->isGlobalProgrammerAvailable();
    }
    if (type == ("AddressedProgrammerManager")) {
        return getProgrammerManager()->isAddressedModePossible();
    }

    if (type == ("PowerManager")) {
        return true;
    }
    if (type == ("ThrottleManager")) {
        log->debug(tr("SPROG provides throttle. sprogMode: %1").arg(sprogMode));
        return true;
    }
    if (type == ("TurnoutManager")) {
        return true;
    }
    if ((type == ("CommandStation"))) {
        if (sprogMode == 0) {
            return false;
        }
        switch (sprogMode) {
            case SprogConstants::OPS:
                return true;
            case SprogConstants::SERVICE:
                return false;
            default:
                log->error(tr("Unhandled sprogMode: %1").arg(sprogMode));
                break;
        }
    }
    return SystemConnectionMemo::provides(type);
}

//@Override
//@SuppressWarnings("unchecked")
/*public*/  Manager *SprogSystemConnectionMemo::get(QString t) {
    if (getDisabled()) {
        return NULL;
    }
    if (t == ("GlobalProgrammerManager")) {
        return  (Manager*)getProgrammerManager();
    }
    if (t == ("AddressedProgrammerManager")) {
        return  (Manager*)getProgrammerManager();
    }
    if (t == ("PowerManager")) {
        return  (Manager*)getPowerManager();
    }
    if (t == ("ThrottleManager")) {
        return  (Manager*)getThrottleManager();
    }
    if (t == ("TurnoutManager")) {
        return  getTurnoutManager();
    }
    if (t == ("CommandStation")) {
        return (Manager*) getCommandStation();
    }
    return SystemConnectionMemo::get(t);
}

/**
 * Configure the common managers for Sprog connections.
 * <p>
 * This puts the common manager config in one place. This method is static
 * so that it can be referenced from classes that don't inherit, including
 * hexfile.HexFileFrame and locormi.LnMessageClient.
 */
/*public*/ void SprogSystemConnectionMemo::configureManagers() {

    if (getProgrammerManager()->isAddressedModePossible()) {
        //InstanceManager::setAddressedProgrammerManager(getProgrammerManager());
     InstanceManager::store(getProgrammerManager(), "AddressedProgrammerManager");
    }
    if (getProgrammerManager()->isGlobalProgrammerAvailable()) {
        InstanceManager::store(getProgrammerManager(), "GlobalProgrammerManager");
    }

    powerManager = new SprogPowerManager(this);
    InstanceManager::store(powerManager, "PowerManager");

    sprogTurnoutManager = new SprogTurnoutManager(this);
    InstanceManager::setTurnoutManager(sprogTurnoutManager);

    switch (sprogMode) {
        case SprogConstants::OPS:
            sprogCSThrottleManager = new SprogCSThrottleManager(this);
            InstanceManager::setThrottleManager(sprogCSThrottleManager);
            break;
        case SprogConstants::SERVICE:
            sprogThrottleManager = new SprogThrottleManager(this);
            InstanceManager::setThrottleManager(sprogThrottleManager);
            break;
        default:
            log->warn(tr("Unhandled programming mode: %1").arg(sprogMode));
            break;
    }

}


/*public*/ SprogProgrammerManager* SprogSystemConnectionMemo::getProgrammerManager() {
    if (programmerManager == NULL) {
        programmerManager = new SprogProgrammerManager(new SprogProgrammer(this), sprogMode, this);
    }
    return programmerManager;
}

/*public*/ void SprogSystemConnectionMemo::setProgrammerManager(SprogProgrammerManager* p) {
    programmerManager = p;
}

/*public*/ SprogPowerManager* SprogSystemConnectionMemo::getPowerManager() {
    return powerManager;
}

/*public*/ ThrottleManager* SprogSystemConnectionMemo::getThrottleManager() {
    if (sprogMode == NULL) {
        log->error("Sprog Mode not set");
        return NULL;
    }

    switch (sprogMode) {
        case SprogConstants::OPS:
            return sprogCSThrottleManager;
        case SprogConstants::SERVICE:
            return sprogThrottleManager;
        default:
            log->warn(tr("Unhandled programming mode: %1").arg(sprogMode));
            break;
    }

    return NULL;
}

/*public*/ TurnoutManager* SprogSystemConnectionMemo::getTurnoutManager() {
    return sprogTurnoutManager;
}
#if 0
@Override
protected ResourceBundle getActionModelResourceBundle() {
    //No actions that can be loaded at startup
    return NULL;
}
#endif
//@Override
/*public*/ void SprogSystemConnectionMemo::dispose() {
    st = NULL;
    InstanceManager::deregister(this, "SprogSystemConnectionMemo");
    if (cf != NULL) {
        InstanceManager::deregister(cf, "ComponentFactory");
    }
    SystemConnectionMemo::dispose();
}


/**
 * Return an SprogVersionQuery object for this connection.
 */
/*public*/ SprogVersionQuery* SprogSystemConnectionMemo::getSprogVersionQuery() {
    if (svq == NULL) {
        svq = new SprogVersionQuery(this);
    }
    return svq;
}

/*private*/ /*final*/ /*static*/ Logger* SprogSystemConnectionMemo::log = LoggerFactory::getLogger("SprogSystemConnectionMemo");
