#include "internalsystemconnectionmemo.h"
#include "instancemanager.h"
#include "loconet/HexFile/debugprogrammermanager.h"
#include "defaultpowermanager.h"
#include "loconet/HexFile/debugthrottlemanager.h"
#include "internalturnoutmanager.h"
#include "internalsensormanager.h"
#include "internalreportermanager.h"
#include "internallightmanager.h"
#include "loggerfactory.h"
#include "internalconsistmanager.h"
#include "internalmetermanager.h"
#include "defaultpowermanager.h"

//InternalSystemConnectionMemo::InternalSystemConnectionMemo()
//{

//}
/**
 * Lightweight class to denote that a system is active, and provide general
 * information.
 * <p>
 * Things this needed to do:
 * <ul>
 * <li>One of these must be automatically, transparently available - this is done by
 *      inheriting from InstanceManagerAutoDefault
 * <li>It must be possible to have more than one of these, so you can have
 *      multiple internal systems defined - each one keeps internal references
 *      to its objects
 * <li>It must make sure that its objects are available individually through the instance manager.
 * <li>But it also has to handle the ProxyManager special cases in the InstanceManager
 * </ul>
 * <p>
 *
 * @author	Bob Jacobsen Copyright (C) 2010, 2016
 */
// /*public*/ class InternalSystemConnectionMemo extends jmrix.SystemConnectionMemo implements InstanceManagerAutoDefault {

/*public*/ InternalSystemConnectionMemo::InternalSystemConnectionMemo(QString prefix, QString name, bool defaultInstanceType, QObject *parent)
 : DefaultSystemConnectionMemo(prefix, name, parent)
{
 common(prefix, name, defaultInstanceType);
}

/*public*/ InternalSystemConnectionMemo::InternalSystemConnectionMemo(QString prefix, QString name,QObject* parent)
 : DefaultSystemConnectionMemo(prefix, name, parent)
{
 common(prefix, name, true);
}

/*public*/ InternalSystemConnectionMemo::InternalSystemConnectionMemo(bool defaultInstanceType,QObject* parent)
 : DefaultSystemConnectionMemo("I", "Internal", parent)
{
 common("I", "Internal", defaultInstanceType);
}

// invoked by i.e. InstanceManager via the InstanceManagerAutoDefault
// mechanism, this creates a partial system
/*public*/ InternalSystemConnectionMemo::InternalSystemConnectionMemo(QObject* parent)
 : DefaultSystemConnectionMemo("I", "Internal", parent)
{
    //this(true);
 common("I", "Internal", true);
}

void InternalSystemConnectionMemo::common(QString prefix, QString name, bool defaultInstanceType)
{
 setObjectName("InternalSystemConnectionMemo");
 if(log == nullptr)
  log = LoggerFactory::getLogger("InternalSystemConnectionMemo");

 InstanceManager::store(this, "InternalSystemConnectionMemo"); // also register as specific type
 _register();
 this->defaultInstanceType = defaultInstanceType;
}

/**
 * Configure the common managers for Internal connections. This puts the
 * common manager config in one place.
 * <p> Note: The Proxy system can cause some managers to be created early.
 * We don't call configureManagers in that case, as it causes an infinite loop.
 */
/*public*/ void InternalSystemConnectionMemo::configureManagers() {
    log->debug("Do configureManagers - doesn't pre-build anything");
    if (configured)
     log->warn("configureManagers called for a second time"/*, new Exception("traceback")*/);
    configured = true;

}

//@Override
/*public*/ InternalConsistManager* InternalSystemConnectionMemo::getConsistManager()
{
 if (defaultInstanceType) {
     return nullptr;
 }
// return (InternalConsistManager*) classObjectMap.computeIfAbsent(("ConsistManager"), (Class c) -> {
  InternalConsistManager* cm = (InternalConsistManager*)classObjectMap.value("ConsistManager", nullptr);
  if(cm == nullptr)
  {
   log->debug("Create InternalConsistManager by request");
     InternalConsistManager* consistManager = new InternalConsistManager();
     InstanceManager::store((QObject*)consistManager, "ConsistManager");
     return consistManager;
  }
  return cm;
}

/*public*/ InternalSensorManager* InternalSystemConnectionMemo::getSensorManager()
{
 Manager* m = classObjectMap.value("SensorManager");
 InternalSensorManager* sensorManager= nullptr;// = (InternalSensorManager*)m->self();
 if (m == nullptr) {
     log->debug(tr("Create InternalSensorManager \"%1\" by request").arg(getSystemPrefix()));
     sensorManager = new InternalSensorManager(this);
     store((AbstractManager*)sensorManager->self(), "SensorManager");
     // special due to ProxyManager support
     InstanceManager::setSensorManager(sensorManager);
 }
 return sensorManager;
}

/*public*/ InternalLightManager* InternalSystemConnectionMemo::getLightManager()
{
 InternalLightManager* lightManager = (InternalLightManager*) classObjectMap.value("LightManager");
 if (lightManager == nullptr)
 {
     log->debug("Create InternalLightManager by request");
     lightManager = new InternalLightManager(this);
     // special due to ProxyManager support
     InstanceManager::setLightManager(lightManager);
 }
 return lightManager;
}

/*public*/ InternalReporterManager* InternalSystemConnectionMemo::getReporterManager() {
 InternalReporterManager* reporterManager = (InternalReporterManager*) classObjectMap.value("ReporterManager");
    if (reporterManager == nullptr) {
        log->debug("Create InternalReporterManager by request");
        reporterManager = new InternalReporterManager(this);
        store((AbstractManager*)reporterManager->self(), "ReporterManager");
        // special due to ProxyManager support
        InstanceManager::setReporterManager(reporterManager);
    }
    return reporterManager;
}

/*public*/ InternalTurnoutManager* InternalSystemConnectionMemo::getTurnoutManager() {
 AbstractManager* manager = classObjectMap.value("TurnoutManager");
 InternalTurnoutManager* turnoutManager;
 if (manager == nullptr) {
     log->debug(tr("Create InternalTurnoutManager \"%1\" by request").arg(getSystemPrefix()));
     turnoutManager = new InternalTurnoutManager(this);
     store((AbstractManager*)turnoutManager->self(), "TurnoutManager");
     // special due to ProxyManager support
     InstanceManager::setTurnoutManager(turnoutManager);
    }
 else
  turnoutManager =(InternalTurnoutManager*) manager;
 return turnoutManager;
}

/*public*/ InternalMeterManager* InternalSystemConnectionMemo::getMeterManager() {
    InternalMeterManager* meterManager = (InternalMeterManager*) classObjectMap.value("MeterManager");
    if (meterManager == nullptr) {
        log->debug(tr("Create InternalMeterManager %1 by request").arg(getSystemPrefix()));
        meterManager = new InternalMeterManager(this);
        // special due to ProxyManager support
        InstanceManager::setMeterManager((AbstractMeterManager*)meterManager);
    }
    return meterManager;
}

/*public*/ DebugThrottleManager* InternalSystemConnectionMemo::getThrottleManager() {
 if (defaultInstanceType) {
     return nullptr;
 }
// return (InternalConsistManager*) classObjectMap.computeIfAbsent(("ConsistManager"), (Class c) -> {
  DebugThrottleManager* dtm = (DebugThrottleManager*)classObjectMap.value("ThrottleManager", nullptr);
  if(dtm == nullptr)
  {
   log->debug("Create DebugThrottleManager by request");
     DebugThrottleManager* throttleManager = new DebugThrottleManager();
     InstanceManager::store((QObject*)throttleManager, "DebugThrottleManager");
     return throttleManager;
  }
  return dtm;
}

/*public*/ DefaultPowerManager* InternalSystemConnectionMemo::getPowerManager() {
 //return (DefaultPowerManager) classObjectMap.computeIfAbsent(PowerManager.class, (Class c) -> {
 PowerManager* pm = (PowerManager*)classObjectMap.value("PowerManager");
 if(pm == nullptr)
 {
     log->debug("Create DefaultPowerManager by request");
     PowerManager* powerManager = new DefaultPowerManager(this);
     InstanceManager::store(powerManager, "PowerManager");
     return (DefaultPowerManager*)powerManager;
 }
 return (DefaultPowerManager*)pm;
}

/*public*/ DebugProgrammerManager* InternalSystemConnectionMemo::getProgrammerManager() {
 if (defaultInstanceType) {
     return nullptr;
 }
 //return (DebugProgrammerManager) classObjectMap.computeIfAbsent(DefaultProgrammerManager.class,
//         (Class c) -> {
 DebugProgrammerManager* dpm = (DebugProgrammerManager*)classObjectMap.value("DefaultProgrammerManager");
 if(dpm == nullptr)
 {
      // Install a debug programmer
      log->debug("Create DebugProgrammerManager by request");
      return new DebugProgrammerManager(this);
  }
 return dpm;
}

//@Override
/*public*/ bool InternalSystemConnectionMemo::provides(/*Class<?>*/QString type) {
    if (getDisabled()) {
        return false;
    }

    if (!configured)
     configureManagers();

    if (type == ("SensorManager")) {
     return true;
 }
 if (type == ("LightManager")) {
     return true;
 }
 if (type == ("ReporterManager")) {
     return true;
 }
 if (type == ("TurnoutManager")) {
     return true;
 }

 if (!defaultInstanceType) {
     if (type == ("PowerManager")) {
         return true;
     }

     if (type == ("GlobalProgrammerManager")) {
         return getProgrammerManager()->isGlobalProgrammerAvailable();
     }
     if (type == ("AddressedProgrammerManager")) {
         return getProgrammerManager()->isAddressedModePossible();
     }

     if (type == ("ThrottleManager")) {
         return true;
     }
     if (type == ("ConsistManager")) {
         return true;
     }
 }

 return DefaultSystemConnectionMemo::provides(type);
}

//@SuppressWarnings("unchecked")
//@Override
/*public*/ Manager *InternalSystemConnectionMemo::get(/*Class<?>*/ QString type) {
    if (getDisabled()) {
        return nullptr;
    }

    if (!configured) configureManagers();

    if (type == ("SensorManager")) {
     return (Manager*) getSensorManager()->self();
 }
 if (type == ("LightManager")) {
     return (Manager*) getLightManager()->self();
 }
 if (type == ("ReporterManager")) {
     return (Manager*) getReporterManager()->self();
 }
 if (type == ("TurnoutManager")) {
     return (Manager*) getTurnoutManager()->self();
 }

 if (!defaultInstanceType) {
     if (type == ("PowerManager")) {
         return (Manager*) getPowerManager();
     }

     if (type == ("GlobalProgrammerManager")) {
         return (Manager*) getProgrammerManager();
     }
     if (type == ("AddressedProgrammerManager")) {
         return (Manager*) getProgrammerManager();
     }

     if (type == ("ThrottleManager")) {
         return (Manager*) getThrottleManager();
     }
     if (type == ("ConsistManager")) {
         return (Manager*) getConsistManager();
     }
 }

 return DefaultSystemConnectionMemo::get(type);
}

//@Override
///*protected*/ ResourceBundle getActionModelResourceBundle() {
//    //No actions to add at start up
//    return nullptr;
//}

//@Override
/*public*/ void InternalSystemConnectionMemo::dispose() {
 SensorManager* sensorManager = (SensorManager*) classObjectMap.value("SensorManager");
    if (sensorManager != nullptr) {
        sensorManager->dispose();
    }

    TurnoutManager* turnoutManager = (TurnoutManager*) classObjectMap.value("TurnoutManager");
    if (turnoutManager != nullptr) {
        turnoutManager->dispose();
    }
    SystemConnectionMemo::dispose();
}

/*private*/ /*static*/ /*final*/ Logger* InternalSystemConnectionMemo::log = LoggerFactory::getLogger("InternalSystemConnectionMemo");
