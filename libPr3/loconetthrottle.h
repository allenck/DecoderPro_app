#ifndef LOCONETTHROTTLE_H
#define LOCONETTHROTTLE_H
#include "abstractthrottle.h"

class LocoNetSlot;
class LocoNetInterface;
class LocoNetSystemConnectionMemo;
class LnThrottleManager;
class LIBPR3SHARED_EXPORT LocoNetThrottle : public AbstractThrottle
{
    Q_OBJECT
public:
    //explicit LocoNetThrottle(QObject *parent = 0);
    /*public*/ LocoNetThrottle(LocoNetSystemConnectionMemo* memo, LocoNetSlot* slot, QObject *parent = 0);
    /*public*/ void setSpeedSetting(float speed);
    /*public*/ void setSpeedSettingAgain(float speed);
    /*public*/ void setSpeedSetting(float speed, bool allowDuplicates, bool allowDuplicatesOnStop);
    /*public*/ void setIsForward(bool forward);
    /*public*/ LocoNetSlot* getLocoNetSlot();
    /*public*/ QString toString();
    /*public*/ void notifyChangedSlot(LocoNetSlot* pSlot);
    /*public*/ void setSpeedStepMode(SpeedStepMode *Mode);
    /*public*/ LocoAddress* getLocoAddress();
    /*public*/ void setF0(bool f0);
    /*public*/ void setF1(bool f1);
    /*public*/ void setF2(bool f2) ;
    /*public*/ void setF3(bool f3);
    /*public*/ void setF4(bool f4);
    /*public*/ void setF5(bool f5) ;
    /*public*/ void setF6(bool f6) ;
    /*public*/ void setF7(bool f7);
    /*public*/ void setF8(bool f8);
    /*public*/ void setF9(bool f9);
    /*public*/ void setF10(bool f10);
    /*public*/ void setF11(bool f11);
    /*public*/ void setF12(bool f12);
    /*public*/ void setF13(bool f13);
    /*public*/ void setF14(bool f14);
    /*public*/ void setF15(bool f15);
    /*public*/ void setF16(bool f16) ;
    /*public*/ void setF17(bool f17);
 /*public*/ void dispatchThrottle(DccThrottle* t, ThrottleListener* l);

signals:

public slots:
 /*public*/ void notifyRefused(int addr, QString s);

private:
 static Logger* log;

 QTimer* mRefreshTimer;
 QMutex mutex;
private slots:
 /*synchronized*/ /*protected*/ void timeout();


protected:
 /*protected*/ LocoNetSlot* slot;
 /*protected*/ LocoNetInterface* network;
 /*protected*/ LnThrottleManager* throttleManager;
 /*protected*/ int address;

 // members to record the last known spd/dirf/snd bytes AS READ FROM THE LAYOUT!!
 /*protected*/ int layout_spd;
 /*protected*/ int layout_dirf;
 /*protected*/ int layout_snd;
 /*protected*/ int layout_stat1 = 0;

 // slot status to be warned if slot released or dispatched
 /*protected*/ int slotStatus;
 /*protected*/ bool isDisposing = false;
 // set isInitialized to false to enable setting the throttle ID.
 /*protected*/ bool isInitialized = false;

 /*protected*/ float floatSpeed(int lSpeed);
 /*protected*/ int intSpeed(float fSpeed);
 /*protected*/ void sendFunctionGroup1();
 /*protected*/ void sendFunctionGroup2();
 /*protected*/ void sendFunctionGroup3();
 /*protected*/ void sendFunctionGroup4();
 /*protected*/ void sendFunctionGroup5();
 /*protected*/ void throttleDispose();
 /*protected*/ void startRefresh();

 friend class ThrottleWindow;
 friend class LnThrottleManager;
 friend class LocoNetThrottleTest;
};

#endif // LOCONETTHROTTLE_H
