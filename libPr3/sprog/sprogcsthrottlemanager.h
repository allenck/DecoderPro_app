#ifndef SPROGCSTHROTTLEMANAGER_H
#define SPROGCSTHROTTLEMANAGER_H
#include "abstractthrottlemanager.h"
#include "sprogsystemconnectionmemo.h"

namespace Sprog
{
class SprogCSThrottle;
 class SprogCSThrottleManager : public AbstractThrottleManager
 {
 public:
  /*public*/ SprogCSThrottleManager(SprogSystemConnectionMemo* memo, QObject* parent = 0);
  /*public*/ void requestThrottleSetup(LocoAddress* a, bool control) ;
  /*public*/ QSet<SpeedStepMode::SSMODES> supportedSpeedModes();
  /*public*/ bool canBeLongAddress(int address);
  /*public*/ bool canBeShortAddress(int address);
  /*public*/ bool addressTypeUnique() ;
  /*public*/ bool disposeThrottle(DccThrottle* t, ThrottleListener* l);


 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogCSThrottleManager");

 };
}
#endif // SPROGCSTHROTTLEMANAGER_H
