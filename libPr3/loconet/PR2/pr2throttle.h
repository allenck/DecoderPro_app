#ifndef PR2THROTTLE_H
#define PR2THROTTLE_H
#include "abstractthrottle.h"

class LocoNetSystemConnectionMemo;
class Pr2Throttle : public AbstractThrottle
{
public:
 /*public*/ Pr2Throttle(LocoNetSystemConnectionMemo* memo, DccLocoAddress* address, QObject *parent = nullptr);
 /*public*/ void writeData();
 /*public*/ void setSpeedSetting(float speed);
 /*public*/ void setIsForward(bool forward);
 /*public*/ QString toString();
 /*public*/ LocoAddress* getLocoAddress();


private:
 static Logger* log;
 /*private*/ int addr;
 DccLocoAddress* address;

protected:
 /*protected*/ float floatSpeed(int lSpeed);
 /*protected*/ int intSpeed(float fSpeed);
 /*protected*/ void sendFunctionGroup1();
 /*protected*/ void sendFunctionGroup2();
 /*protected*/ void sendFunctionGroup3();
 /*protected*/ void throttleDispose();

};

#endif // PR2THROTTLE_H
