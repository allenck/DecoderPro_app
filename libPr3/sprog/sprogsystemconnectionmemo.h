#ifndef SPROGSYSTEMCONNECTIONMEMO_H
#define SPROGSYSTEMCONNECTIONMEMO_H
#include "defaultsystemconnectionmemo.h"
#include "sprogconstants.h"
#include "sprogtrafficcontroller.h"
#include "sprogtype.h"
#include "sprogcommandstation.h"
#include "sprogpowermanager.h"
#include "sprogprogrammermanager.h"
#include "sprogprogrammer.h"
#include "sprogversion.h"

class GlobalProgrammerManager;
class ThrottleManager;
class TurnoutManager;
class SystemConnectionMemo;
class ComponentFactory;
namespace Sprog
{
 class SprogPowerManager;
 class SprogProgrammerManager;
 class SprogTrafficController;
 class SprogVersionQuery;
 class SprogTurnoutManager;
 class SprogThrottleManager;
 class SprogCSThrottleManager;
 class SprogCommandStation;
 class SprogSystemConnectionMemo : public DefaultSystemConnectionMemo
 {
 public:
  SprogSystemConnectionMemo(QObject* parent = 0);
  /*public*/ SprogSystemConnectionMemo(SprogTrafficController* st, SprogConstants::SprogMode sm, QObject* parent = 0);
  /*public*/ SprogSystemConnectionMemo(SprogConstants::SprogMode sm, QObject* parent = 0);
  /*public*/ SprogSystemConnectionMemo(SprogConstants::SprogMode sm, SprogType* type,QObject* parent = 0);
  /*public*/ void setSprogMode(SprogConstants::SprogMode mode);
  /*public*/ SprogConstants::SprogMode getSprogMode();
  /*public*/ SprogVersion* getSprogVersion();
  /*public*/ void setSprogVersion(SprogVersion* version) ;
  /*public*/ SprogType* getSprogType();
  /*public*/ SprogTrafficController* getSprogTrafficController();
  /*public*/ void setSprogTrafficController(SprogTrafficController* st);
  /*public*/ QThread* getSlotThread();
  /*public*/ void configureCommandStation();
  /*public*/ SprogCommandStation* getCommandStation();
  /*public*/ bool provides(QString type);
  /*public*/ void configureManagers();
  /*public*/ SprogProgrammerManager* getProgrammerManager();
  /*public*/ void setProgrammerManager(SprogProgrammerManager* p) ;
  /*public*/ SprogPowerManager* getPowerManager() ;
  /*public*/ ThrottleManager* getThrottleManager();
  /*public*/ TurnoutManager* getTurnoutManager();
  /*public*/ void dispose();
  /*public*/ SprogVersionQuery* getSprogVersionQuery();
  /*public*/  Manager* get(QString t);

 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogSystemConnectionMemo");
void common(SprogConstants::SprogMode sm);
/*private*/ SprogConstants::SprogMode sprogMode;// = SprogMode.SERVICE;
ComponentFactory* cf;// = null;
/*private*/ SprogTrafficController* st;
/*private*/ SprogCommandStation* commandStation;

/*private*/ QThread* slotThread;
/*private*/ SprogProgrammerManager* programmerManager;
/*private*/ SprogCSThrottleManager* sprogCSThrottleManager;
/*private*/ SprogThrottleManager* sprogThrottleManager;
/*private*/ SprogTurnoutManager* sprogTurnoutManager;
/*private*/ SprogPowerManager* powerManager;
/*private*/ SprogVersionQuery* svq;// = null;
/*private*/ SprogVersion* sprogVersion;

 };
}
#endif // SPROGSYSTEMCONNECTIONMEMO_H
