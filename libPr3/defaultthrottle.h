#ifndef DEFAULTTHROTTLE_H
#define DEFAULTTHROTTLE_H

#include "abstractthrottle.h"
#include "commandstation.h"
#include "dcclocoaddress.h"

class DefaultThrottle : public AbstractThrottle
{
  Q_OBJECT
 public:
  /*public*/ DefaultThrottle(DccLocoAddress* address, CommandStation* tc, QObject* parent = 0);
  /*public*/ LocoAddress* getLocoAddress() override;
  /*public*/ /*synchronized*/ void setSpeedSetting(float speed) override;
  /*public*/ void setIsForward(bool forward) override;
  /*public*/ void throttleDispose() override;

  QObject*  self() override {return this;}

 private:
  /*private*/ CommandStation* tcl=nullptr;
  DccLocoAddress* address = nullptr;

 protected:
  /*protected*/ void sendFunctionGroup1() override;
  /*protected*/ void sendFunctionGroup2() override;
  /*protected*/ void sendFunctionGroup3() override;

};

#endif // DEFAULTTHROTTLE_H
