#ifndef SPROGCSTHROTTLE_H
#define SPROGCSTHROTTLE_H
#include "abstractthrottle.h"
#include "sprogsystemconnectionmemo.h"

namespace Sprog
{

 class SprogCSThrottle : public AbstractThrottle
 {
 public:
  /*public*/ SprogCSThrottle(SprogSystemConnectionMemo* memo, LocoAddress* address, QObject* parent = 0);
  /*public*/ LocoAddress* getLocoAddress();
  /*public*/ void setSpeedSetting(float speed);
  /*public*/ void setIsForward(bool forward);
   QObject* self() {return(QObject*)this;}

 private:
  /*private*/ SprogCommandStation* commandStation;

  DccLocoAddress* address;

 protected:
  /*protected*/ void sendFunctionGroup1();
  /*protected*/ void sendFunctionGroup2();
  /*protected*/ void sendFunctionGroup3();
  /*protected*/ void throttleDispose();

  friend class SprogCSThrottleManager;
 };
}
#endif // SPROGCSTHROTTLE_H
