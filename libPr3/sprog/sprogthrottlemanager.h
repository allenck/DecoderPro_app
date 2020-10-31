#ifndef SPROGTHROTTLEMANAGER_H
#define SPROGTHROTTLEMANAGER_H
#include "abstractthrottlemanager.h"
#include "sprogsystemconnectionmemo.h"

namespace Sprog
{
 class SprogThrottleManager : public AbstractThrottleManager
 {
 public:
  SprogThrottleManager(SprogSystemConnectionMemo* memo, QObject* parent = 0);
  QT_DEPRECATED static /*public*/ SprogThrottleManager* instance();
  /*public*/ void requestThrottleSetup(LocoAddress* a, bool control);
  /*public*/ QSet<SpeedStepMode::SSMODES> supportedSpeedModes();
  /*public*/ bool canBeLongAddress(int address);
  /*public*/ bool canBeShortAddress(int address);
  /*public*/ bool addressTypeUnique();
  /*public*/ bool disposeThrottle(DccThrottle* t, ThrottleListener* l);

 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogThrottleManager");
  bool throttleInUse;// = false;
  void release();

 };
}
#endif // SPROGTHROTTLEMANAGER_H
