#ifndef LOCONETSYSTEMCONNECTIONMEMO_H
#define LOCONETSYSTEMCONNECTIONMEMO_H


#include "defaultsystemconnectionmemo.h"
//#include "lnmessagemanager.h"
#include "lnsensormanager.h"
#include "lnreportermanager.h"
#include "throttlemanager.h"
#include "componentfactory.h"
#include "defaultprogrammermanager.h"
#include "comparator.h"

/**
 * Lightweight class to denote that a system is active,
 * and provide general information.
 * <p>
 * Objects of specific subtypes are registered
 * in the instance manager to activate their
 * particular system.
 *
 * @author		Bob Jacobsen  Copyright (C) 2010
 * @version             $Revision: 20788 $
 */

class LncvDevicesManager;
class LnPredefinedMeters;
class LnCabSignalManager;
class LnMultiMeter;
class TranspondingTagManager;
class LnComponentFactory;
class ResourceBundle;
class LnCommandStationType;
class LnMessageManager;
class LocoNetThrottledTransmitter;
class LnLightManager;
class LnReporterManager;
class LnTurnoutManager;
class ThrottleManager;
class LnTrafficController;
//class ProgrammerManager;
class SlotManager;
class LnPowerManager;
class LnSensorManager;
class LocoNetConsistManager;
class LnClockControl;
class LIBPR3SHARED_EXPORT  LocoNetSystemConnectionMemo : public  DefaultSystemConnectionMemo
{
 Q_OBJECT
public:
 LocoNetSystemConnectionMemo(LnTrafficController* lt, SlotManager* sm, QObject* parent=0);
 LocoNetSystemConnectionMemo(QObject* parent=0);
 /*public*/ LocoNetSystemConnectionMemo(/*@Nonnull*/ QString prefix, /*@Nonnull*/ QString name);
 ~LocoNetSystemConnectionMemo();
 /*public*/ void _register();

 /**
  * Provides access to the TrafficController for this
  * particular connection.
  */
 LnTrafficController* getLnTrafficController();
 void setLnTrafficController(LnTrafficController* lt);
// void configureCommandStation(bool mCanRead, bool mProgPowersOff,
//  QString name, bool mTurnoutNoRetry, bool mTurnoutExtraSpace);
 /*public*/ void configureCommandStation(LnCommandStationType* type, bool mTurnoutNoRetry, bool mTurnoutExtraSpace, bool mTranspondingAvailable);
 /**
  * Provides access to the SlotManager for this
  * particular connection.
  */
 SlotManager* getSlotManager();
// void setSlotManager(SlotManager* sm);
 LnMessageManager* getLnMessageManager();
 DefaultProgrammerManager *getProgrammerManager();
 void setProgrammerManager(DefaultProgrammerManager* p);
 /*public*/ void setLncvDevicesManager(LncvDevicesManager* lncvdm);
 /*public*/ bool provides(QString type)override;
// /*public*/ Manager*  get(QString T) override;
 void configureManagers();
 LnPowerManager* getPowerManager();

 ThrottleManager* getThrottleManager();
 void setThrottleManager(ThrottleManager* t);

 LnTurnoutManager* getTurnoutManager();
 LnClockControl* getClockControl();
 LnReporterManager* getReporterManager();
 virtual LnSensorManager* getSensorManager();
 LnLightManager* getLightManager();
 /*public*/ LncvDevicesManager* getLncvDevicesManager();
 /*public*/ LnPredefinedMeters* getPredefinedMeters();

// LocoNetConsistManager* getConsistManager();
 static /*public*/ TranspondingTagManager* getIdTagManager();
// /*public*/ LnMultiMeter* getMultiMeter();
 /*public*/ void resetProgrammer();
 /*public*/ LnCabSignalManager* getCabSignalManager();
 /*public*/ void dispose()override;

private:
 LnComponentFactory* cf = nullptr;
 LnTrafficController* lt = nullptr;
 LnMessageManager* lnm = nullptr;
 SlotManager* sm = nullptr;
 /*private*/ LncvDevicesManager* lncvdm = nullptr;
 static Logger* log;
 LocoNetConsistManager* consistManager = nullptr;
 void common();

protected:
 bool mTurnoutNoRetry;
 bool mTurnoutExtraSpace;
 LocoNetThrottledTransmitter* tm = nullptr;
 LnPowerManager* powerManager = nullptr;
 ThrottleManager* throttleManager = nullptr;
 LnTurnoutManager* turnoutManager = nullptr;
 LnClockControl* clockControl = nullptr;
 LnReporterManager* reporterManager = nullptr;
 LnSensorManager* sensorManager = nullptr;
 LnLightManager* lightManager = nullptr;
 /*protected*/ LnMultiMeter* multiMeter = nullptr;
 LnCabSignalManager* cabSignalManager = nullptr;

 //ResourceBundle* getActionModelResourceBundle();
 /*protected*/ ResourceBundle* getActionModelResourceBundle() override;
#if 0
 template<class B>
 /*public*/ /*<B extends NamedBean>*/ Comparator<B> getNamedBeanComparator(/*Class<B>*/QString type) {
     return new NamedBeanComparator<B>();
 }
#endif
 /*protected*/ DefaultProgrammerManager* programmerManager = nullptr;
  DefaultProgrammerManager* oldMgr = nullptr;
 // yes, tagManager is static.  Tags can move between system connections.
 // when readers are not all on the same LocoNet
 // this manager is loaded on demand.
 /*protected*/ static TranspondingTagManager* tagManager;
 /*protected*/ LnPredefinedMeters* predefinedMeters = nullptr;

  friend class ManagerDefaultsConfigPane;
};
Q_DECLARE_METATYPE(LocoNetSystemConnectionMemo)
#endif // LOCONETSYSTEMCONNECTIONMEMO_H
