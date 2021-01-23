#include "loconetsystemconnectionmemo.h"
#include "lnthrottlemanager.h"
#include "locobufferadapter.h"
#include "instancemanager.h"
#include "lntrafficcontroller.h"
#include "slotmanager.h"
#include "lnpowermanager.h"
#include "throttlemanager.h"
#include "lnturnoutmanager.h"
#include "lnclockcontrol.h"
#include "lnreportermanager.h"
#include "lnsensormanager.h"
#include "lnlightmanager.h"
#include "loconetconsistmanager.h"
#include "loconetthrottledtransmitter.h"
#include "lnprogrammermanager.h"
#include "lnpowermanager.h"
#include "resourcebundle.h"
#include "loconet/HexFile/debugthrottlemanager.h"
#include "lnmessagemanager.h"
#include "lncomponentfactory.h"
#include "loggerfactory.h"
#include "transpondingtagmanager.h"
#include <QPointer>
#include "multimeter.h"
#include "lnmultimeter.h"
#include <QDebug>
#include "lncabsignalmanager.h"
#include "lnpredefinedmeters.h"
#include "lncvdevicesmanager.h"


LocoNetSystemConnectionMemo::LocoNetSystemConnectionMemo(LnTrafficController* lt, SlotManager* sm, QObject* parent)
 : DefaultSystemConnectionMemo("L","LocoNet", parent)
{
 //super("L", "LocoNet");
 common();
 this->lt = lt;
 this->sm = sm; // doesn't full register, but fine for this purpose.
}

LocoNetSystemConnectionMemo::LocoNetSystemConnectionMemo(QObject* parent)
 : DefaultSystemConnectionMemo("L","LocoNet", parent)
{
 common();
}
/*public*/ LocoNetSystemConnectionMemo::LocoNetSystemConnectionMemo(/*@Nonnull*/ QString prefix, /*@Nonnull*/ QString name)
 : DefaultSystemConnectionMemo(prefix, name)
{
 //super(prefix, name); // NOI18N
 common();

}

void LocoNetSystemConnectionMemo::common()
{
    this->lt = NULL;
    setObjectName("LocoNetSystemConnectionMemo");
    powerManager = NULL;
    turnoutManager = NULL;
    sensorManager = NULL;
    reporterManager = NULL;
    programmerManager = NULL;
    throttleManager = NULL;
    consistManager = NULL;
    lightManager = NULL;
    clockControl = NULL;
    mTurnoutNoRetry = false;
    mTurnoutExtraSpace = false;
    tm = NULL;
    lnm = NULL;
    cf = NULL;

    // self-registration is deferred until the command station type is set below

    // create and register the LnComponentFactory
    InstanceManager::store(cf = new LnComponentFactory(this),
                                   "ComponentFactory");
}

LocoNetSystemConnectionMemo::~LocoNetSystemConnectionMemo()
{
 dispose();
}

/**
 * Do both the default parent
 * {@link SystemConnectionMemo} registration,
 * and register this specific type.
 */
//@Override
/*public*/ void LocoNetSystemConnectionMemo::_register() {
    SystemConnectionMemo::_register(); // registers general type
    InstanceManager::store(this, "LocoNetSystemConnectionMemo"); // also register as specific type
}

/**
 * Provide access to the SlotManager for this particular connection.
 *
 * @return the slot manager or null if no valid slot manager is available
 */
/*public*/ SlotManager* LocoNetSystemConnectionMemo::getSlotManager() {
    if (sm == nullptr) {
        log->debug("slot manager is null, but there should always be a valid SlotManager",  Exception("Traceback"));
    }
    return sm;
}

/**
 * Provides access to the TrafficController for this
 * particular connection.
 */
LnTrafficController* LocoNetSystemConnectionMemo::getLnTrafficController() { return lt; }

void LocoNetSystemConnectionMemo::setLnTrafficController(LnTrafficController* lt)
{ this->lt = lt; }

/**
 * Configure the programming manager and "command station" objects
 * @param mCanRead
 * @param mProgPowersOff
 * @param name Command station type name
 */
//void LocoNetSystemConnectionMemo::configureCommandStation(bool mCanRead, bool mProgPowersOff,
// QString name, bool mTurnoutNoRetry, bool mTurnoutExtraSpace)
/**
 * Configure the programming manager and "command station" objects
 * @param type Command station type, used to configure various operations
 * @param mTurnoutNoRetry Is the user configuration set for no turnout operation retries?
 * @param mTurnoutExtraSpace Is the user configuration set for extra time between turnout operations?
 * @param mTranspondingAvailable    Is the layout configured to provide
 *                                  transopnding reports*/
/*public*/ void LocoNetSystemConnectionMemo::configureCommandStation(LnCommandStationType* type, bool mTurnoutNoRetry,
                                                                     bool mTurnoutExtraSpace, bool mTranspondingAvailable) {
    // store arguments
    this->mTurnoutNoRetry = mTurnoutNoRetry;
    this->mTurnoutExtraSpace = mTurnoutExtraSpace;

    // create and install SlotManager
    if (sm !=NULL) log->error("Installing SlotManager twice"/*, new Exception("TraceBack")*/);
    sm = type->getSlotManager(lt);
    if (sm != NULL)
    {
     sm->setThrottledTransmitter(tm, mTurnoutNoRetry);

     sm->setCommandStationType(type);
     sm->setSystemConnectionMemo(this);
     sm->setTranspondingAvailable(mTranspondingAvailable);

     // store as CommandStation object
     InstanceManager::store(sm, "CommandStation");
    }
//    _register();
}

/**
 * Provides access to the SlotManager for this
 * particular connection.
 */
//void LocoNetSystemConnectionMemo::setSlotManager(SlotManager* sm)
//{
// this->sm = sm;
// if (sm != NULL) sm->setThrottledTransmitter(tm, mTurnoutNoRetry);
//}

LnMessageManager* LocoNetSystemConnectionMemo::getLnMessageManager()
{
    // create when needed
    if (lnm == NULL)
        lnm = new LnMessageManager(getLnTrafficController());
    return lnm;
}


DefaultProgrammerManager* LocoNetSystemConnectionMemo::getProgrammerManager()
{
 if (programmerManager == NULL)
 {
     //programmerManager = new LnProgrammerManager( this);
  programmerManager = QPointer<LnProgrammerManager>(new LnProgrammerManager( this));
 }
 return programmerManager;
}

void LocoNetSystemConnectionMemo::setProgrammerManager(DefaultProgrammerManager* p) {
    programmerManager = p;
}

/*public*/ void LocoNetSystemConnectionMemo::setLncvDevicesManager(LncvDevicesManager* lncvdm) {
    this->lncvdm = lncvdm;
}

/**
 * Tells which managers this provides by class
 */
//@Override
/*public*/ bool LocoNetSystemConnectionMemo::provides(QString type)
{
 if (getDisabled())
  return false;
 if (type==("GlobalProgrammerManager"))
     return getProgrammerManager()->isGlobalProgrammerAvailable();
 if (type==("AddressedProgrammerManager"))
     return getProgrammerManager()->isAddressedModePossible();
 if (type == ("ThrottleManager"))
        return true;
 if (type == ("PowerManager"))
        return true;
 if (type == ("SensorManager"))
        return true;
 if (type == ("TurnoutManager"))
        return true;
 if (type == ("LightManager"))
        return true;
 if (type == ("ReporterManager"))
        return true;
 if (type == ("ConsistManager"))
        return true;
 if (type == ("ClockControl"))
        return true;
 if (type == ("CommandStation"))
        return true;
 if (type == ("MultiMeter")) {
        return true;
 }
 if (type == ("IdTagManager")) {
     return true;
 }
 if (type == ("CabSignalManager")) {
     return true;
 }
 return false; // nothing, by default
}
#if 0
//@SuppressWarnings("unchecked")
//@Override
/*public*/ Manager*  LocoNetSystemConnectionMemo::get(QString T)
{
 if (getDisabled())
  return NULL;
 if (T ==("GlobalProgrammerManager")) {
     log->trace(tr("get GlobalProgrammerManager is %1").arg(getProgrammerManager()->toString()));
     return (Manager*) getProgrammerManager();
 }
 if (T == ("AddressedProgrammerManager")) {
     log->trace(tr("get AddressedProgrammerManager is %1").arg(getProgrammerManager()->toString()));
     return (Manager*) getProgrammerManager();
 }
 if (T == ("ThrottleManager"))
  return (Manager*)getThrottleManager();
 if (T == ("PowerManager"))
  return (Manager*)getPowerManager();
 if (T == ("SensorManager"))
  return (Manager*)getSensorManager();
 if (T == ("TurnoutManager"))
  return (Manager*)getTurnoutManager();
 if (T == ("LightManager"))
  return (Manager*)getLightManager();
 if (T == ("ClockControl"))
  return (Manager*)getClockControl();
 if (T == ("ReporterManager"))
  return (Manager*)getReporterManager();
 if (T == ("ConsistManager"))
  return (Manager*)getConsistManager();
 if (T == ("CommandStation"))
  return (Manager*)getSlotManager();
 if (T ==("MultiMeter")) {
     return (Manager*) getMultiMeter();
 }
 if (T == ("IdTagManager")) {
     return (IdTagManager*) getIdTagManager();
 }
 if (T == ("CabSignalManager")) {
     return (Manager*) getCabSignalManager();
 }

 return NULL; // nothing, by default
}
#endif

/**
 * Configure the common managers for LocoNet connections.
 * This puts the common manager config in one
 * place.
 */
void LocoNetSystemConnectionMemo::configureManagers()
{
 tm = new LocoNetThrottledTransmitter(getLnTrafficController(), mTurnoutExtraSpace);
 log->debug(QString("ThrottleTransmitted configured with :")+(mTurnoutExtraSpace?"true":"false"));
 if (sm != NULL)
 {
  sm->setThrottledTransmitter(tm, mTurnoutNoRetry);
  log->debug("set turnout retry: "+mTurnoutNoRetry);
 }

 InstanceManager::store(getPowerManager(), "PowerManager");

 InstanceManager::setSensorManager(
  (SensorManager*)getSensorManager());

 InstanceManager::setTurnoutManager(
  (TurnoutManager*)getTurnoutManager());

 InstanceManager::setLightManager(
  (LightManager*)getLightManager());

 InstanceManager::setThrottleManager(
  getThrottleManager());

 if (getProgrammerManager()->isAddressedModePossible())
 {
  InstanceManager::store(getProgrammerManager(), "AddressedProgrammerManager");
 }
 if (getProgrammerManager()->isGlobalProgrammerAvailable())
 {
  InstanceManager::store(getProgrammerManager(), "GlobalProgrammerManager");
 }

 InstanceManager::setReporterManager((ReporterManager*)getReporterManager());

 InstanceManager::setDefault("CabSignalManager",getCabSignalManager());

 InstanceManager::setDefault("ConsistManager", new LocoNetConsistManager(this));

 ClockControl* cc = getClockControl();
 // make sure InstanceManager knows about that
 InstanceManager::setDefault("ClockControl", cc);

// //MultiMeter mm = getMultiMeter();
// InstanceManager::store(getMultiMeter(), "MultiMeter");

 getIdTagManager();

 // register this SystemConnectionMemo to connect to rest of system
 _register();

 // This must be done after the memo is registered
 getPredefinedMeters();
}

LnPowerManager* LocoNetSystemConnectionMemo::getPowerManager()
{
 if (getDisabled())
  return NULL;
 if (powerManager == NULL)
 {
  powerManager = new LnPowerManager(this);
 }
 return powerManager;
}


ThrottleManager* LocoNetSystemConnectionMemo::getThrottleManager() {
    if (getDisabled())
        return NULL;
    if (throttleManager == NULL)
        throttleManager = (ThrottleManager*)new LnThrottleManager(this);
    return throttleManager;
}

void LocoNetSystemConnectionMemo::setThrottleManager(ThrottleManager* t) {
    throttleManager = t;
}


LnTurnoutManager* LocoNetSystemConnectionMemo::getTurnoutManager()
{
 if (getDisabled())
  return NULL;
 if (turnoutManager == NULL)
  turnoutManager = new LnTurnoutManager(this, tm, mTurnoutNoRetry);
 return turnoutManager;
}


LnClockControl* LocoNetSystemConnectionMemo::getClockControl() {
    if (getDisabled())
        return NULL;
    if (clockControl == NULL)
        clockControl = new LnClockControl(this);
    return clockControl;
}

LnReporterManager* LocoNetSystemConnectionMemo::getReporterManager()
{
 if (getDisabled())
  return NULL;
 if (reporterManager == NULL)
  reporterManager = new LnReporterManager(this);
 return reporterManager;
}


LnSensorManager* LocoNetSystemConnectionMemo::getSensorManager()
{
 if (getDisabled())
  return NULL;
 if (sensorManager == NULL)
  sensorManager = new LnSensorManager(this);
 return sensorManager;
}


LnLightManager* LocoNetSystemConnectionMemo::getLightManager()
{
 if (getDisabled())
  return NULL;
 if (lightManager == NULL)
  lightManager = new LnLightManager(this);
 return lightManager;
}

/*public*/ LncvDevicesManager* LocoNetSystemConnectionMemo::getLncvDevicesManager() {
    if (getDisabled()) {
        return nullptr;
    }
    if (lncvdm == nullptr) {
        setLncvDevicesManager(new LncvDevicesManager(this));
        log->debug("Auto create of LncvDevicesManager for initial configuration");
    }
    return lncvdm;
}

/*public*/ LnPredefinedMeters* LocoNetSystemConnectionMemo::getPredefinedMeters() {
    if (getDisabled()) {
        log->warn("Aborting getPredefinedMeters account is disabled!");
        return nullptr;
    }
//        switch (getSlotManager().commandStationType) {
//            case COMMAND_STATION_USB_DCS240_ALONE:
//            case COMMAND_STATION_DCS240:
//            case COMMAND_STATION_DCS210:
//            case COMMAND_STATION_USB_DCS52_ALONE:
//            case COMMAND_STATION_DCS052:
//                break;
//            default:
//                // The command station does not support these meters
//                return null;
//        }
    if (predefinedMeters == nullptr) {
        predefinedMeters = new LnPredefinedMeters(this);
    }
    return predefinedMeters;
}

#if 0
LocoNetConsistManager* LocoNetSystemConnectionMemo::getConsistManager() {
    if (getDisabled())
        return NULL;
    if (consistManager == NULL)
        consistManager = new LocoNetConsistManager(this);
    return consistManager;
}

/*public*/ LnMultiMeter* LocoNetSystemConnectionMemo::getMultiMeter() {
    if (getDisabled()) {
        return nullptr;
    }
    if (multiMeter == nullptr) {
        multiMeter = new LnMultiMeter(this);
    }
    return multiMeter;
}
#endif
ResourceBundle* LocoNetSystemConnectionMemo::getActionModelResourceBundle()
{
 ResourceBundle* rb = new ResourceBundle;
 return rb->getBundle("src/jmri/jmrix/loconet/LocoNetActionListBundle.properties");
}

//@Override
///*public*/ <B extends NamedBean> Comparator<B> getNamedBeanComparator(Class<B> type) {
//    return new NamedBeanComparator<B>();
//}

// yes, tagManager is static.  Tags can move between system connections.
// when readers are not all on the same LocoNet
// this manager is loaded on demand.
/*protected*/ /*static*/ TranspondingTagManager* LocoNetSystemConnectionMemo::tagManager = nullptr;


/*static*/ /*public*/ TranspondingTagManager* LocoNetSystemConnectionMemo::getIdTagManager() {
    /*synchronized*/ /*(LocoNetSystemConnectionMemo.class)*/ { // since tagManager can be null, can't synch on that
        if (tagManager == nullptr) {
            tagManager = new TranspondingTagManager();
            InstanceManager::setIdTagManager(tagManager);
        }
        return tagManager;
    }
}
#if 0 // TOO

/*protected*/ LnCabSignalManager* cabSignalManager;

/*public*/ LnCabSignalManager getCabSignalManager() {
    if (cabSignalManager == null) {
        cabSignalManager = new LnCabSignalManager(this);
    }
    return cabSignalManager;
}
#endif

/*public*/ void LocoNetSystemConnectionMemo::resetProgrammer()
{
 oldMgr = programmerManager;
 programmerManager = new LnProgrammerManager(this);
 if (getProgrammerManager()->isAddressedModePossible())
 {
  InstanceManager::getDefault()-> remove(oldMgr, "AddressedProgrammerManager");
  InstanceManager::store(getProgrammerManager(), "AddressedProgrammerManager");
 }
 if (getProgrammerManager()->isGlobalProgrammerAvailable())
 {
  InstanceManager::getDefault()-> remove(oldMgr, "GlobalProgrammerManager");
  InstanceManager::store(getProgrammerManager(), "GlobalProgrammerManager");
 }
 //InstanceManager::store(oldMgr, "Garbage");
}

/*public*/ LnCabSignalManager* LocoNetSystemConnectionMemo::getCabSignalManager() {
    if (cabSignalManager == nullptr) {
        cabSignalManager = new LnCabSignalManager(this);
    }
    return cabSignalManager;
}

//@Override
/*public*/ void LocoNetSystemConnectionMemo::dispose() {
    InstanceManager::deregister(this, "LocoNetSystemConnectionMemo");
    if (cf != nullptr) {
        InstanceManager::deregister(cf, "ComponentFactory");
    }
    if (powerManager != nullptr) {
        powerManager->dispose();
        InstanceManager::deregister(powerManager, "LnPowerManager");
    }
    if (turnoutManager != nullptr) {
        turnoutManager->dispose();
        InstanceManager::deregister(turnoutManager, "LnTurnoutManager");
    }
    if (lightManager != nullptr) {
        lightManager->dispose();
        InstanceManager::deregister(lightManager, "LnLightManager");
    }
    if (sensorManager != nullptr) {
        sensorManager->dispose();
        InstanceManager::deregister(sensorManager, "LnSensorManager");
    }
    if (reporterManager != nullptr) {
        reporterManager->dispose();
        InstanceManager::deregister(reporterManager, "LnReporterManager");
    }
    if (throttleManager != nullptr) {
        if (qobject_cast<LnThrottleManager*>(throttleManager)) {
            InstanceManager::deregister(((LnThrottleManager*) throttleManager), "LnThrottleManager");
        } else if (qobject_cast<DebugThrottleManager*>(throttleManager)) {
            InstanceManager::deregister(((DebugThrottleManager*) throttleManager), "DebugThrottleManager");
        }
    }
    if (clockControl != nullptr) {
        InstanceManager::deregister(clockControl, "LnClockControl");
    }
    if (tm != nullptr){
        tm->dispose();
    }
    if (sm != nullptr){
        sm->dispose();
    }
    if (lt != nullptr){
        lt->dispose();
    }
    SystemConnectionMemo::dispose();
}

/*static*/ Logger* LocoNetSystemConnectionMemo::log = LoggerFactory::getLogger("LocoNetSystemConnectionMemo");

