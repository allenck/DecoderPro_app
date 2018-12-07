#include "pr2systemconnectionmemo.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "lnpr2powermanager.h"
#include "lnpr2throttlemanager.h"

/**
 * Lightweight class to denote that a PR2 is active
 *
 * @author Bob Jacobsen Copyright (C) 2010
 */
// /*public*/ class PR2SystemConnectionMemo extends LocoNetSystemConnectionMemo {

/*public*/ PR2SystemConnectionMemo::PR2SystemConnectionMemo(LnTrafficController* lt,
        SlotManager* sm, QObject* parent) : LocoNetSystemConnectionMemo(lt, sm, parent) {
    //super(lt, sm);
}

/*public*/ PR2SystemConnectionMemo::PR2SystemConnectionMemo(QObject* parent) : LocoNetSystemConnectionMemo(parent){
    //super();
}

/**
 * Configure the subset of LocoNet managers valid for the PR2.
 */
//@Override
/*public*/ void PR2SystemConnectionMemo::configureManagers() {
    InstanceManager::store(getPowerPr2Manager(), "PowerManager");

    // jmri.InstanceManager.setTurnoutManager(new jmri.jmrix.loconet.LnTurnoutManager());

    // jmri.InstanceManager.setLightManager(new jmri.jmrix.loconet.LnLightManager());

    // jmri.InstanceManager.setSensorManager(new jmri.jmrix.loconet.LnSensorManager());
    InstanceManager::setThrottleManager(getPr2ThrottleManager());

    if (getProgrammerManager()->isAddressedModePossible()) {
        InstanceManager::store(getProgrammerManager(), "AddressedProgrammerManager");
    }
    if (getProgrammerManager()->isGlobalProgrammerAvailable()) {
        InstanceManager::store(getProgrammerManager(), "GlobalProgrammerManager");
    }

    // jmri.InstanceManager.setReporterManager(new jmri.jmrix.loconet.LnReporterManager());
}


/*public*/ LnPr2PowerManager* PR2SystemConnectionMemo::getPowerPr2Manager() {
    if (getDisabled()) {
        return nullptr;
    }
    if (powerPr2Manager == nullptr) {
        powerPr2Manager = new LnPr2PowerManager(this);
    }
    return powerPr2Manager;
}


/*public*/ LnPr2ThrottleManager* PR2SystemConnectionMemo::getPr2ThrottleManager() {
    if (getDisabled()) {
        return nullptr;
    }
    if (throttlePr2Manager == nullptr) {
        throttlePr2Manager = new LnPr2ThrottleManager(this);
    }
    return throttlePr2Manager;
}

//@Override
//@SuppressWarnings("unchecked")
/*public*/ /*<T>*/ Manager* PR2SystemConnectionMemo::get(/*Class<?>*/QString type) {
    if (getDisabled()) {
        return nullptr;
    }
    if (type ==("PowerManager")) {
        return /*(T)*/(Manager*) getPowerPr2Manager();
    }
    if (type == ("ThrottleManager")) {
        return /*(T)*/ (Manager*)getPr2ThrottleManager();
    }
    if (type == ("GlobalProgrammerManager")) {
        return /*(T)*/ (Manager*)getProgrammerManager();
    }
    if (type == ("AddressedProgrammerManager")) {
        return /*(T)*/ (Manager*)getProgrammerManager();
    }
    if(type == ("ConsistManager")){
       return /*(T)*/ (Manager*)getConsistManager();
    }
    return nullptr;
}

//@Override
/*public*/ bool PR2SystemConnectionMemo::provides(/*Class<?>*/QString type) {
    if (getDisabled()) {
        return false;
    }
    if (type == "PowerManager") {
        return true;
    }
    if (type == "ThrottleManager") {
        return true;
    }
    if (type == "GlobalProgrammerManager") {
        return getProgrammerManager()->isGlobalProgrammerAvailable();
    }
    if (type == "AddressedProgrammerManager") {
        return getProgrammerManager()->isAddressedModePossible();
    }
    if(type == "ConsistManager"){
       return(getConsistManager()!=nullptr);
    }
    return false;
}

//@Override
/*public*/ void PR2SystemConnectionMemo::dispose() {
    InstanceManager::deregister(this, "PR2SystemConnectionMemo");
    LocoNetSystemConnectionMemo::dispose();
}


