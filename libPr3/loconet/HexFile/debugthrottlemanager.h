#ifndef DEBUGTHROTTLEMANAGER_H
#define DEBUGTHROTTLEMANAGER_H
#include "abstractthrottlemanager.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT DebugThrottleManager : public AbstractThrottleManager
{
    Q_OBJECT
public:
    explicit DebugThrottleManager(QObject *parent = 0);
    /*public*/ DebugThrottleManager(SystemConnectionMemo* memo, QObject *parent = 0);
    /*public*/ void requestThrottleSetup(LocoAddress* a, bool control);
    /*public*/ bool canBeLongAddress(int address) ;
    /*public*/ bool canBeShortAddress(int address);
    /*public*/ bool addressTypeUnique();
    /*public*/ bool disposeThrottle(DccThrottle* t, ThrottleListener* l);
    /*public*/ QSet<SpeedStepMode::SSMODES> supportedSpeedModes();


signals:

public slots:
private:
    Logger* log;
protected:
};

#endif // DEBUGTHROTTLEMANAGER_H
