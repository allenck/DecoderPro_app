#ifndef DEFAULTTHROTTLEMANAGER_H
#define DEFAULTTHROTTLEMANAGER_H

#include "abstractthrottlemanager.h"
#include "trafficcontroller.h"

class DefaultThrottle;
class DirectSystemConnectionMemo;
class DefaultThrottleManager : public AbstractThrottleManager
{
  Q_OBJECT
 public:
  explicit DefaultThrottleManager(DirectSystemConnectionMemo* memo=0, QObject *parent = nullptr);
  ~DefaultThrottleManager(){}
  DefaultThrottleManager(const DefaultThrottleManager&) : AbstractThrottleManager() {}
  /*public*/ void requestThrottleSetup(LocoAddress* address, bool control) override;
  /*public*/ bool addressTypeUnique() override;
  /*public*/ bool canBeShortAddress(int a) override;
  /*public*/ bool canBeLongAddress(int a)override;
  /*public*/ bool disposeThrottle(DccThrottle* t, ThrottleListener* l) override;

 private:
  /*private*/ TrafficController* tc = nullptr;
  DefaultThrottle* currentThrottle = nullptr;
  static Logger* log;
};
Q_DECLARE_METATYPE(DefaultThrottleManager)
#endif // DEFAULTTHROTTLEMANAGER_H
