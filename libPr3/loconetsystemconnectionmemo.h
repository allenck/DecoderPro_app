#ifndef LOCONETSYSTEMCONNECTIONMEMO_H
#define LOCONETSYSTEMCONNECTIONMEMO_H


#include "systemconnectionmemo.h"
//#include "lnmessagemanager.h"
#include "lnsensormanager.h"
#include "lnreportermanager.h"
#include "throttlemanager.h"
#include "componentfactory.h"
#include "defaultprogrammermanager.h"

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
class ProgrammerManager;
class SlotManager;
class LnPowerManager;
class LnSensorManager;
class LocoNetConsistManager;
class LnClockControl;
class LIBPR3SHARED_EXPORT  LocoNetSystemConnectionMemo : public  SystemConnectionMemo
{
 Q_OBJECT
public:
 LocoNetSystemConnectionMemo(LnTrafficController* lt, SlotManager* sm, QObject* parent=0);
 LocoNetSystemConnectionMemo(QObject* parent=0);
 ~LocoNetSystemConnectionMemo();
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
 SlotManager* getSlotManager() { return sm; }
 void setSlotManager(SlotManager* sm);
 LnMessageManager* getLnMessageManager();
 DefaultProgrammerManager* getProgrammerManager();
 void setProgrammerManager(DefaultProgrammerManager* p);
 /*public*/ bool provides(QString type);
 /*public*/ Manager*  get(QString T);
 virtual void configureManagers();
 LnPowerManager* getPowerManager();

 ThrottleManager* getThrottleManager();
 void setThrottleManager(ThrottleManager* t);

 LnTurnoutManager* getTurnoutManager();
 LnClockControl* getClockControl();
 LnReporterManager* getReporterManager();
 LnSensorManager* getSensorManager();
 LnLightManager* getLightManager();
 LocoNetConsistManager* getConsistManager();
 void dispose();


private:
 LnComponentFactory* cf;// = null;
 LnTrafficController* lt;
 LnMessageManager* lnm;
 SlotManager* sm;
 Logger* log;
 LocoNetConsistManager* consistManager;

protected:
 bool mTurnoutNoRetry;
 bool mTurnoutExtraSpace;
 LocoNetThrottledTransmitter* tm;
 LnPowerManager* powerManager;
 ThrottleManager* throttleManager;
 LnTurnoutManager* turnoutManager;
 LnClockControl* clockControl;
 LnReporterManager* reporterManager;
 LnSensorManager* sensorManager;
 LnLightManager* lightManager;
 //ResourceBundle* getActionModelResourceBundle();
 /*protected*/ ResourceBundle* getActionModelResourceBundle();
 /*protected*/ DefaultProgrammerManager* programmerManager;

};

#endif // LOCONETSYSTEMCONNECTIONMEMO_H
