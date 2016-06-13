#ifndef DEBUGTHROTTLE_H
#define DEBUGTHROTTLE_H
#include "abstractthrottle.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT DebugThrottle : public AbstractThrottle
{
    Q_OBJECT
public:
    //explicit DebugThrottle(QObject *parent = 0);
    /*public*/ DebugThrottle(DccLocoAddress* address, SystemConnectionMemo* memo,QObject *parent = 0);
    /*public*/ LocoAddress* getLocoAddress();
    /*public*/ QString toString();
    /*public*/ void setSpeedSetting(float speed);
    /*public*/ void setIsForward(bool forward);

signals:

public slots:
private:
    DccLocoAddress* address;
    Logger* log;
protected:

    /*protected*/ void sendFunctionGroup1();
    /*protected*/ void sendFunctionGroup2();
    /*protected*/ void sendFunctionGroup3();
    /*protected*/ void throttleDispose();
friend class DebugThrottleManager;
};

#endif // DEBUGTHROTTLE_H
