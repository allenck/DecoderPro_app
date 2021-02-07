#ifndef SPROGTHROTTLE_H
#define SPROGTHROTTLE_H
#include "abstractthrottle.h"
#include"sprogcommandstation.h"
#include "sprogslot.h"

namespace Sprog
{
 class SprogThrottle : public AbstractThrottle
 {
 public:
  /*public*/ SprogThrottle(SprogSystemConnectionMemo* memo, DccLocoAddress* address, QObject* parent = 0);
  /*public*/ LocoAddress* getLocoAddress();
  /*public*/ void setSpeedStepMode(SpeedStepMode::SSMODES Mode);
  /*public*/ void setSpeedSetting(float speed);
  /*public*/ void setIsForward(bool forward);

 private:
  SprogCommandStation* station;// = null;
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogThrottle");

  DccLocoAddress* address;

 protected:
  /*protected*/ void sendFunctionGroup1();
  /*protected*/ void sendFunctionGroup2();
  /*protected*/ void sendFunctionGroup3();
  /*protected*/ void sendFunctionGroup4();
  /*protected*/ void sendFunctionGroup5();
  /*protected*/ void throttleDispose();

 };
}
#endif // SPROGTHROTTLE_H
