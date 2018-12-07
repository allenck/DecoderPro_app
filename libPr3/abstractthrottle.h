#ifndef ABSTRACTTHROTTLE_H
#define ABSTRACTTHROTTLE_H

#include <QObject>
#include "systemconnectionmemo.h"
#include "basicrosterentry.h"
#include "dccthrottle.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT AbstractThrottle : public DccThrottle
{
    Q_OBJECT
public:
    explicit AbstractThrottle(SystemConnectionMemo* memo, QObject *parent = 0);
    /*public final*/ static float SPEED_STEP_14_INCREMENT;//=1.0f/14.0f;
    /*public final*/ static float SPEED_STEP_27_INCREMENT;//=1.0f/27.0f;
    /*public final*/ static float SPEED_STEP_28_INCREMENT;//=1.0f/28.0f;
    /*public final*/ static float SPEED_STEP_128_INCREMENT;//=1.0f/126.0f; // remember there are only 126 ;
    /*public*/ float getSpeedSetting();
    /*public*/ void setSpeedSetting(float speed);
    /*public*/ void setSpeedSetting(float speed, bool allowDuplicates, bool allowDuplicatesOnStop);
    /*public*/ void setSpeedSettingAgain(float speed);
    /*public*/ bool getIsForward();
    /*public*/ void setIsForward(bool forward);
    /*public*/ bool getF0();
    /*public*/ bool getF1();
    /*public*/ bool getF2();
    /*public*/ bool getF3();
    /*public*/ bool getF4();
    /*public*/ bool getF5();
    /*public*/ bool getF6() ;
    /*public*/ bool getF7();
    /*public*/ bool getF8();
    /*public*/ bool getF9();
    /*public*/ bool getF10();
    /*public*/ bool getF11();
    /*public*/ bool getF12();
    /*public*/ bool getF13();
    /*public*/ bool getF14();
    /*public*/ bool getF15();
    /*public*/ bool getF16();
    /*public*/ bool getF17();
    /*public*/ bool getF18();
    /*public*/ bool getF19();
    /*public*/ bool getF20();
    /*public*/ bool getF21();
    /*public*/ bool getF22();
    /*public*/ bool getF23();
    /*public*/ bool getF24();
    /*public*/ bool getF25();
    /*public*/ bool getF26();
    /*public*/ bool getF27();
    /*public*/ bool getF28();
    /*public*/ bool getF0Momentary();
    /*public*/ bool getF1Momentary();
    /*public*/ bool getF2Momentary();
    /*public*/ bool getF3Momentary();
    /*public*/ bool getF4Momentary();
    /*public*/ bool getF5Momentary();
    /*public*/ bool getF6Momentary();
    /*public*/ bool getF7Momentary();
    /*public*/ bool getF8Momentary();
    /*public*/ bool getF9Momentary();
    /*public*/ bool getF10Momentary();
    /*public*/ bool getF11Momentary();
    /*public*/ bool getF12Momentary();
    /*public*/ bool getF13Momentary();
    /*public*/ bool getF14Momentary();
    /*public*/ bool getF15Momentary();
    /*public*/ bool getF16Momentary();
    /*public*/ bool getF17Momentary();
    /*public*/ bool getF18Momentary();
    /*public*/ bool getF19Momentary();
    /*public*/ bool getF20Momentary();
    /*public*/ bool getF21Momentary();
    /*public*/ bool getF22Momentary();
    /*public*/ bool getF23Momentary();
    /*public*/ bool getF24Momentary();
    /*public*/ bool getF25Momentary();
    /*public*/ bool getF26Momentary();
    /*public*/ bool getF27Momentary();
    /*public*/ bool getF28Momentary();
    /*public*/ void removePropertyChangeListener(PropertyChangeListener* l);
    /*public*/ void addPropertyChangeListener(PropertyChangeListener* l);
    /*protected*/ void notifyPropertyChangeListener(QString property, QVariant oldValue, QVariant newValue);
    /*public*/ QVector<PropertyChangeListener*>* getListeners();
//    /*public*/ void dispose();
    /*public*/ void dispose(ThrottleListener* l);
//    /*public*/ void dispatch();
    /*public*/ void dispatch(ThrottleListener* l) ;
//    /*public*/ void release();
    /*public*/ void release(ThrottleListener* l);
    /*abstract*/ virtual /*protected*/ void throttleDispose() {}
    /*public*/ float getSpeedIncrement();
    /*public*/ void setF0(bool f0);
    /*public*/ void setF1(bool f1);
    /*public*/ void setF2(bool f2);
    /*public*/ void setF3(bool f3);
    /*public*/ void setF4(bool f4);
    /*public*/ void setF5(bool f5) ;
    /*public*/ void setF6(bool f6);
    /*public*/ void setF7(bool f7) ;
    /*public*/ void setF8(bool f8);
    /*public*/ void setF9(bool f9);
    /*public*/ void setF10(bool f10);
    /*public*/ void setF11(bool f11);
    /*public*/ void setF12(bool f12);
    /*public*/ void setF13(bool f13);
    /*public*/ void setF14(bool f14);
    /*public*/ void setF15(bool f15);
    /*public*/ void setF16(bool f16);
    /*public*/ void setF17(bool f17);
    /*public*/ void setF18(bool f18);
    /*public*/ void setF19(bool f19);
    /*public*/ void setF20(bool f20);
    /*public*/ void setF21(bool f21);
    /*public*/ void setF22(bool f22);
    /*public*/ void setF23(bool f23);
    /*public*/ void setF24(bool f24);
    /*public*/ void setF25(bool f25);
    /*public*/ void setF26(bool f26);
    /*public*/ void setF27(bool f27);
    /*public*/ void setF28(bool f28);
    /*public*/ void setF0Momentary(bool f0Momentary);
    /*public*/ void setF1Momentary(bool f1Momentary);
    /*public*/ void setF2Momentary(bool f2Momentary);
    /*public*/ void setF3Momentary(bool f3Momentary);
    /*public*/ void setF4Momentary(bool f4Momentary);
    /*public*/ void setF5Momentary(bool f5Momentary);
    /*public*/ void setF6Momentary(bool f6Momentary);
    /*public*/ void setF7Momentary(bool f7Momentary) ;
    /*public*/ void setF8Momentary(bool f8Momentary);
    /*public*/ void setF9Momentary(bool f9Momentary);
    /*public*/ void setF10Momentary(bool f10Momentary);
    /*public*/ void setF11Momentary(bool f11Momentary);
    /*public*/ void setF12Momentary(bool f12Momentary);
    /*public*/ void setF13Momentary(bool f13Momentary);
    /*public*/ void setF14Momentary(bool f14Momentary);
    /*public*/ void setF15Momentary(bool f15Momentary);
    /*public*/ void setF16Momentary(bool f16Momentary);
    /*public*/ void setF17Momentary(bool f17Momentary);
    /*public*/ void setF18Momentary(bool f18Momentary);
    /*public*/ void setF19Momentary(bool f19Momentary);
    /*public*/ void setF20Momentary(bool f20Momentary);
    /*public*/ void setF21Momentary(bool f21Momentary);
    /*public*/ void setF22Momentary(bool f22Momentary);
    /*public*/ void setF23Momentary(bool f23Momentary);
    /*public*/ void setF24Momentary(bool f24Momentary);
    /*public*/ void setF25Momentary(bool f25Momentary);
    /*public*/ void setF26Momentary(bool f26Momentary);
    /*public*/ void setF27Momentary(bool f27Momentary);
    /*public*/ void setF28Momentary(bool f28Momentary);
    /*public*/ void setSpeedStepMode(int Mode);
     /*public*/ int getSpeedStepMode();
     /*public*/ void setRosterEntry(BasicRosterEntry* re);
     /*public*/ BasicRosterEntry* getRosterEntry();

signals:
    void propertyChange(PropertyChangeEvent*);

public slots:
 private:
  BasicRosterEntry* re;// = NULL;
  // data members to hold contact with the property listeners
  /*final private*/ QVector<PropertyChangeListener*>* listeners;// = new QVector<PropertyChangeListener*>();
      Logger* log;

      qint64 durationRunning;// = 0;
      qint64 start;
 QMutex mutex;
 QObject *parent;

protected:
    /*protected*/ float speedSetting;
    /*protected*/ float speedIncrement;
    /**
     * Question: should we set a default speed step mode so it's never zero?
     */
    /*protected*/ int speedStepMode;
    /*protected*/ bool isForward;
    /*protected*/ bool f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12;
    /*protected*/ bool f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23,
            f24, f25, f26, f27, f28;
    /*protected*/ bool f0Momentary, f1Momentary, f2Momentary, f3Momentary,
            f4Momentary, f5Momentary, f6Momentary, f7Momentary, f8Momentary,
            f9Momentary, f10Momentary, f11Momentary, f12Momentary;
    /*protected*/ bool f13Momentary, f14Momentary, f15Momentary, f16Momentary,
            f17Momentary, f18Momentary, f19Momentary, f20Momentary,
            f21Momentary, f22Momentary, f23Momentary, f24Momentary,
            f25Momentary, f26Momentary, f27Momentary, f28Momentary;

    /**
     * Is this object still usable?  Set false after dispose, this
     * variable is used to check for incorrect usage.
     */
    /*protected*/ bool active;
    /*protected*/ SystemConnectionMemo* adapterMemo;
    /*protected*/ virtual void sendFunctionGroup1();
    /*protected*/ virtual void sendFunctionGroup2();
    /*protected*/ virtual void sendFunctionGroup3();
    /*protected*/ virtual void sendFunctionGroup4();
    /*protected*/ virtual void sendFunctionGroup5();
    /*protected*/ virtual void sendMomentaryFunctionGroup1();
    /*protected*/ virtual void sendMomentaryFunctionGroup2();
    /*protected*/ virtual void sendMomentaryFunctionGroup3();
    /*protected*/ virtual void sendMomentaryFunctionGroup4() ;
    /*protected*/ virtual void sendMomentaryFunctionGroup5();
     /*protected*/ void record(float speed);
     /*protected*/ void startClock();
     void stopClock();
     /*protected*/ void finishRecord();
     /*protected*/ int intSpeed(float speed);     // non-stop values in 128 speed
     /*protected*/ int intSpeed(float speed, int steps);


};

#endif // ABSTRACTTHROTTLE_H
