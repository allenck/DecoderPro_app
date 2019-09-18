#include "loconetsystemconnectionmemo.h"
#include "lnthrottlemanager.h"
#include "locobufferadapter.h"
#include "instancemanager.h"
#include "lntrafficcontroller.h"
#include "slotmanager.h"
#include "programmermanager.h"
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

LocoNetSystemConnectionMemo::LocoNetSystemConnectionMemo(LnTrafficController* lt, SlotManager* sm, QObject* parent)
 : SystemConnectionMemo("L","LocoNet", parent)
{
 //super("L", "LocoNet");
 common();
 this->lt = lt;
 this->sm = sm; // doesn't full register, but fine for this purpose.
 _register(); // registers general type
 InstanceManager::store(this, "LocoNetSystemConnectionMemo"); // also register as specific type

 // create and register the LnComponentFactory
 InstanceManager::store(cf = new LnComponentFactory(this),
                                "ComponentFactory");
 lnm = NULL;

}

LocoNetSystemConnectionMemo::LocoNetSystemConnectionMemo(QObject* parent)
 : SystemConnectionMemo("L","LocoNet", parent)
{
 common();

 //setSlotManager(sm);
 this->sm = NULL;
 _register(); // registers general type
 InstanceManager::store(this, "LocoNetSystemConnectionMemo"); // also register as specific type

 // create and register the LnComponentFactory
 InstanceManager::store(cf = new LnComponentFactory(this),
                                "ComponentFactory");
}
/*public*/ LocoNetSystemConnectionMemo::LocoNetSystemConnectionMemo(/*@Nonnull*/ QString prefix, /*@Nonnull*/ QString name)
 : SystemConnectionMemo(prefix, name)
{
       //super(prefix, name); // NOI18N
common();
       // create and register the ComponentFactory for the GUI
       InstanceManager::store(cf = new LnComponentFactory(this),
               "ComponentFactory");
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
}

LocoNetSystemConnectionMemo::~LocoNetSystemConnectionMemo()
{
 dispose();
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
 */
/*public*/ void LocoNetSystemConnectionMemo::configureCommandStation(LnCommandStationType* type, bool mTurnoutNoRetry, bool mTurnoutExtraSpace, bool mTranspondingAvailable) {
    // store arguments
    this->mTurnoutNoRetry = mTurnoutNoRetry;
    this->mTurnoutExtraSpace = mTurnoutExtraSpace;

    // create and install SlotManager
    if (sm !=NULL) log->error("Installing SlotManager twice"/*, new Exception("TraceBack")*/);
    sm = type->getSlotManager(lt);
    if (sm != NULL) sm->setThrottledTransmitter(tm, mTurnoutNoRetry);

    sm->setCommandStationType(type);
    sm->setSystemConnectionMemo(this);
    sm->setTranspondingAvailable(mTranspondingAvailable);

    // store as CommandStation object
    InstanceManager::setCommandStation((CommandStation*)sm);

}
/**
 * Provides access to the SlotManager for this
 * particular connection.
 */
void LocoNetSystemConnectionMemo::setSlotManager(SlotManager* sm)
{
 this->sm = sm;
 if (sm != NULL) sm->setThrottledTransmitter(tm, mTurnoutNoRetry);
}

LnMessageManager* LocoNetSystemConnectionMemo::getLnMessageManager()
{
    // create when needed
    if (lnm == NULL)
        lnm = new LnMessageManager(getLnTrafficController());
    return lnm;
}


DefaultProgrammerManager* LocoNetSystemConnectionMemo::getProgrammerManager() {
    if (programmerManager == NULL)
    {
        programmerManager = new LnProgrammerManager(getSlotManager(), this);
    }
    return programmerManager;
}
void LocoNetSystemConnectionMemo::setProgrammerManager(DefaultProgrammerManager* p) {
    programmerManager = p;
}


/**
 * Tells which managers this provides by class
 */
//@Override
/*public*/ bool LocoNetSystemConnectionMemo::provides(QString type)
{
 if (getDisabled())
  return false;
 if (type==("ProgrammerManager"))
  return true;
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
// if (type == ("LightManager"))
//        return true;
 if (type == ("ReporterManager"))
        return true;
 if (type == ("ConsistManager"))
        return true;
 if (type == ("ClockControl"))
        return true;
 if (type == ("CommandStation"))
        return true;
 return false; // nothing, by default
}

//@SuppressWarnings("unchecked")
//@Override
/*public*/ Manager*  LocoNetSystemConnectionMemo::get(QString T)
{
 if (getDisabled())
  return NULL;
 if (T == ("ProgrammerManager"))
  return (Manager*)getProgrammerManager();
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
 return NULL; // nothing, by default
}


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
  InstanceManager::setAddressedProgrammerManager(getProgrammerManager());
 }
 if (getProgrammerManager()->isGlobalProgrammerAvailable())
 {
  InstanceManager::store(getProgrammerManager(), "GlobalProgrammerManager");
 }

 InstanceManager::setReporterManager(
  (ReporterManager*)getReporterManager());

 InstanceManager::setConsistManager(new LocoNetConsistManager(this));

 ClockControl* cc = getClockControl();
 // make sure InstanceManager knows about that
 InstanceManager::setDefault("ClockControl", cc);
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
  reporterManager = new LnReporterManager(getLnTrafficController(), getSystemPrefix());
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
  lightManager = new LnLightManager(getLnTrafficController(), getSystemPrefix());
 return lightManager;
}

LocoNetConsistManager* LocoNetSystemConnectionMemo::getConsistManager() {
    if (getDisabled())
        return NULL;
    if (consistManager == NULL)
        consistManager = new LocoNetConsistManager(this);
    return consistManager;
}

ResourceBundle* LocoNetSystemConnectionMemo::getActionModelResourceBundle()
{
 ResourceBundle* rb = new ResourceBundle;
 return rb->getBundle("src/jmri/jmrix/loconet/LocoNetActionListBundle.properties");
}

void  LocoNetSystemConnectionMemo::dispose()
{
 lt = NULL;
 sm = NULL;
 InstanceManager::deregister(this,"LocoNetSystemConnectionMemo");
// if (cf != NULL)
//  InstanceManager::deregister(cf, jmri.jmrix.swing.ComponentFactory.class);
 if (powerManager != NULL)
     InstanceManager::deregister(powerManager, "LnPowerManager");
 if (turnoutManager != NULL)
  InstanceManager::deregister(turnoutManager,"LnTurnoutManager");
 if (lightManager != NULL)
  InstanceManager::deregister(lightManager, "LnLightManager");
 if (sensorManager != NULL)
  InstanceManager::deregister(sensorManager, "LnSensorManager");
 if (reporterManager != NULL)
  InstanceManager::deregister(reporterManager, "LnReporterManager");
 if (throttleManager != NULL)
 {
  //if (throttleManager instanceof LnThrottleManager)
  if(qobject_cast<LnThrottleManager*>(throttleManager)!= NULL)
   InstanceManager::deregister(((LnThrottleManager*)throttleManager), "LnThrottleManager");
  else
  if (qobject_cast<DebugThrottleManager*>(throttleManager) != NULL)
   InstanceManager::deregister(((DebugThrottleManager*)throttleManager), "DebugThrottleManager");
 }
 if (consistManager != NULL)
  InstanceManager::deregister(consistManager, "LocoNetConsistManager");
 if (clockControl != NULL)
  InstanceManager::deregister(clockControl, "LnClockControl");
 SystemConnectionMemo::dispose();
}

/*static*/ Logger* LocoNetSystemConnectionMemo::log = LoggerFactory::getLogger("LocoNetSystemConnectionMemo");

