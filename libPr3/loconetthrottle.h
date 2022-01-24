#ifndef LOCONETTHROTTLE_H
#define LOCONETTHROTTLE_H
#include "abstractthrottle.h"
#include "slotlistener.h"

class LocoNetSlot;
class LocoNetInterface;
class LocoNetSystemConnectionMemo;
class LnThrottleManager;
class LIBPR3SHARED_EXPORT LocoNetThrottle : public AbstractThrottle, SlotListener
{
    Q_OBJECT
 Q_INTERFACES(SlotListener)
public:
    //explicit LocoNetThrottle(QObject *parent = 0);
    /*public*/ LocoNetThrottle(LocoNetSystemConnectionMemo* memo, LocoNetSlot* slot, QObject *parent = 0);
    /*public*/ void setSpeedSetting(float speed) override;
    /*public*/ void setSpeedSettingAgain(float speed) override;
    /*public*/ void setSpeedSetting(float speed, bool allowDuplicates, bool allowDuplicatesOnStop) override;
    /*public*/ void setIsForward(bool forward) override;
    /*public*/ LocoNetSlot* getLocoNetSlot();
    /*public*/ QString toString();
    /*public*/ void notifyChangedSlot(LocoNetSlot* pSlot) override;
    /*public*/ void setSpeedStepMode(SpeedStepMode::SSMODES Mode) override;
    /*public*/ LocoAddress* getLocoAddress() override;
#if 0
    /*public*/ void setF0(bool f0) override;
    /*public*/ void setF1(bool f1) override;
    /*public*/ void setF2(bool f2) override;
    /*public*/ void setF3(bool f3) override;
    /*public*/ void setF4(bool f4) override;
    /*public*/ void setF5(bool f5) override;
    /*public*/ void setF6(bool f6) override;
    /*public*/ void setF7(bool f7) override;
    /*public*/ void setF8(bool f8) override;
    /*public*/ void setF9(bool f9) override;
    /*public*/ void setF10(bool f10) override;
    /*public*/ void setF11(bool f11) override;
    /*public*/ void setF12(bool f12) override;
    /*public*/ void setF13(bool f13) override;
    /*public*/ void setF14(bool f14) override;
    /*public*/ void setF15(bool f15) override;
    /*public*/ void setF16(bool f16) override;
    /*public*/ void setF17(bool f17) override;
#endif
    /*public*/ void dispatchThrottle(DccThrottle* t, ThrottleListener* l);
    QObject* self() {return (QObject*)this;}

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
 /*protected*/ void sendFunctionGroup1() override;
 /*protected*/ void sendFunctionGroup2() override;
 /*protected*/ void sendFunctionGroup3() override;
 /*protected*/ void sendFunctionGroup4() override;
 /*protected*/ void sendFunctionGroup5() override;
 /*protected*/ void throttleDispose() override;
 /*protected*/ void startRefresh();

 friend class ThrottleWindow;
 friend class LnThrottleManager;
 friend class LocoNetThrottleTest;
};

#endif // LOCONETTHROTTLE_H
