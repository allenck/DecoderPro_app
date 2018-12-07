#ifndef LNPR2THROTTLEMANAGER_H
#define LNPR2THROTTLEMANAGER_H
#include "abstractthrottlemanager.h"

class LnPr2ThrottleManager : public AbstractThrottleManager
{
public:
 /*public*/ LnPr2ThrottleManager(LocoNetSystemConnectionMemo* memo, QObject* parent = nullptr);
 /*public*/ void requestThrottleSetup(LocoAddress* address, bool control);
 /*public*/ bool hasDispatchFunction();
 /*public*/ bool canBeLongAddress(int address);
 /*public*/ bool canBeShortAddress(int address);
 /*public*/ bool addressTypeUnique();
 /*public*/ DccLocoAddress* getActiveAddress();

private:
 static Logger* log;
 static bool isLongAddress(int num);
 DccLocoAddress* activeAddress = nullptr;


protected:
 /*protected*/ bool singleUse();

};

#endif // LNPR2THROTTLEMANAGER_H
