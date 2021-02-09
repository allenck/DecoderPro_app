#ifndef ABSTRACTTHROTTLE_H
#define ABSTRACTTHROTTLE_H

#include <QObject>
#include "systemconnectionmemo.h"
#include "basicrosterentry.h"
#include "dccthrottle.h"
#include "libPr3_global.h"
#include "propertychangesupport.h"

class LIBPR3SHARED_EXPORT AbstractThrottle : public DccThrottle
{
    Q_OBJECT
public:
    explicit AbstractThrottle(SystemConnectionMemo* memo, QObject *parent = 0);
    /*public final*/ static float SPEED_STEP_14_INCREMENT;//=1.0f/14.0f;
    /*public final*/ static float SPEED_STEP_27_INCREMENT;//=1.0f/27.0f;
    /*public final*/ static float SPEED_STEP_28_INCREMENT;//=1.0f/28.0f;
    /*public final*/ static float SPEED_STEP_128_INCREMENT;//=1.0f/126.0f; // remember there are only 126 ;
    /*public*/ float getSpeedSetting() override;
    /*public*/ void setSpeedSetting(float speed) override;
    /*public*/ void setSpeedSetting(float speed, bool allowDuplicates, bool allowDuplicatesOnStop) override;
    /*public*/ void setSpeedSettingAgain(float speed) override;
    /*public*/ bool getIsForward() override;
    /*public*/ void setIsForward(bool forward) override;
    /*public*/ QVector<bool> getFunctions() override;
    /*public*/ QVector<bool> getFunctionsMomentary() override;
    /*public*/ bool getFunction(int fN) override;
    /*public*/ bool getFunctionMomentary(int fN) override;

    Q_INVOKABLE /*public*/ bool getF0() override;
    Q_INVOKABLE /*public*/ bool getF1() override;
    Q_INVOKABLE /*public*/ bool getF2() override;
    Q_INVOKABLE /*public*/ bool getF3() override;
    Q_INVOKABLE /*public*/ bool getF4() override;
    Q_INVOKABLE /*public*/ bool getF5() override;
    Q_INVOKABLE /*public*/ bool getF6() override;
    Q_INVOKABLE /*public*/ bool getF7() override;
    Q_INVOKABLE /*public*/ bool getF8() override;
    Q_INVOKABLE /*public*/ bool getF9() override;
    Q_INVOKABLE /*public*/ bool getF10() override;
    Q_INVOKABLE /*public*/ bool getF11() override;
    Q_INVOKABLE /*public*/ bool getF12() override;
    Q_INVOKABLE /*public*/ bool getF13() override;
    Q_INVOKABLE /*public*/ bool getF14() override;
    Q_INVOKABLE /*public*/ bool getF15() override;
    Q_INVOKABLE /*public*/ bool getF16() override;
    Q_INVOKABLE /*public*/ bool getF17() override;
    Q_INVOKABLE /*public*/ bool getF18() override;
    Q_INVOKABLE /*public*/ bool getF19() override;
    Q_INVOKABLE /*public*/ bool getF20() override;
    Q_INVOKABLE /*public*/ bool getF21() override;
    Q_INVOKABLE /*public*/ bool getF22() override;
    Q_INVOKABLE /*public*/ bool getF23() override;
    Q_INVOKABLE /*public*/ bool getF24() override;
    Q_INVOKABLE /*public*/ bool getF25() override;
    Q_INVOKABLE /*public*/ bool getF26() override;
    Q_INVOKABLE /*public*/ bool getF27() override;
    Q_INVOKABLE /*public*/ bool getF28() override;
    /*public*/ bool getF0Momentary() override;
    /*public*/ bool getF1Momentary() override;
    /*public*/ bool getF2Momentary() override;
    /*public*/ bool getF3Momentary() override;
    /*public*/ bool getF4Momentary() override;
    /*public*/ bool getF5Momentary() override;
    /*public*/ bool getF6Momentary() override;
    /*public*/ bool getF7Momentary() override;
    /*public*/ bool getF8Momentary() override;
    /*public*/ bool getF9Momentary() override;
    /*public*/ bool getF10Momentary() override;
    /*public*/ bool getF11Momentary() override;
    /*public*/ bool getF12Momentary() override;
    /*public*/ bool getF13Momentary() override;
    /*public*/ bool getF14Momentary() override;
    /*public*/ bool getF15Momentary() override;
    /*public*/ bool getF16Momentary() override;
    /*public*/ bool getF17Momentary() override;
    /*public*/ bool getF18Momentary() override;
    /*public*/ bool getF19Momentary() override;
    /*public*/ bool getF20Momentary() override;
    /*public*/ bool getF21Momentary() override;
    /*public*/ bool getF22Momentary() override;
    /*public*/ bool getF23Momentary() override;
    /*public*/ bool getF24Momentary() override;
    /*public*/ bool getF25Momentary() override;
    /*public*/ bool getF26Momentary() override;
    /*public*/ bool getF27Momentary() override;
    /*public*/ bool getF28Momentary() override;
    /*public*/ void removePropertyChangeListener(PropertyChangeListener* l) override;
    /*public*/ void addPropertyChangeListener(PropertyChangeListener* l) override;
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
    /*public*/ void setF0(bool f0) override;
    /*public*/ void setF1(bool f1) override;
    /*public*/ void setF2(bool f2) override;
    /*public*/ void setF3(bool f3) override;
    /*public*/ void setF4(bool f4) override;
    /*public*/ void setF5(bool f5) ;
    /*public*/ void setF6(bool f6) override;
    /*public*/ void setF7(bool f7) ;
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
    /*public*/ void setF18(bool f18) override;
    /*public*/ void setF19(bool f19) override;
    /*public*/ void setF20(bool f20) override;
    /*public*/ void setF21(bool f21) override;
    /*public*/ void setF22(bool f22) override;
    /*public*/ void setF23(bool f23) override;
    /*public*/ void setF24(bool f24) override;
    /*public*/ void setF25(bool f25) override;
    /*public*/ void setF26(bool f26) override;
    /*public*/ void setF27(bool f27) override;
    /*public*/ void setF28(bool f28) override;
    /*public*/ void setF0Momentary(bool f0Momentary) override;
    /*public*/ void setF1Momentary(bool f1Momentary) override;
    /*public*/ void setF2Momentary(bool f2Momentary) override;
    /*public*/ void setF3Momentary(bool f3Momentary) override;
    /*public*/ void setF4Momentary(bool f4Momentary) override;
    /*public*/ void setF5Momentary(bool f5Momentary) override;
    /*public*/ void setF6Momentary(bool f6Momentary) override;
    /*public*/ void setF7Momentary(bool f7Momentary) ;
    /*public*/ void setF8Momentary(bool f8Momentary) override;
    /*public*/ void setF9Momentary(bool f9Momentary) override;
    /*public*/ void setF10Momentary(bool f10Momentary) override;
    /*public*/ void setF11Momentary(bool f11Momentary) override;
    /*public*/ void setF12Momentary(bool f12Momentary) override;
    /*public*/ void setF13Momentary(bool f13Momentary) override;
    /*public*/ void setF14Momentary(bool f14Momentary) override;
    /*public*/ void setF15Momentary(bool f15Momentary) override;
    /*public*/ void setF16Momentary(bool f16Momentary) override;
    /*public*/ void setF17Momentary(bool f17Momentary) override;
    /*public*/ void setF18Momentary(bool f18Momentary) override;
    /*public*/ void setF19Momentary(bool f19Momentary) override;
    /*public*/ void setF20Momentary(bool f20Momentary) override;
    /*public*/ void setF21Momentary(bool f21Momentary) override;
    /*public*/ void setF22Momentary(bool f22Momentary) override;
    /*public*/ void setF23Momentary(bool f23Momentary) override;
    /*public*/ void setF24Momentary(bool f24Momentary) override;
    /*public*/ void setF25Momentary(bool f25Momentary) override;
    /*public*/ void setF26Momentary(bool f26Momentary) override;
    /*public*/ void setF27Momentary(bool f27Momentary) override;
    /*public*/ void setF28Momentary(bool f28Momentary) override;
    /*public*/ void setFunction(int functionNum, bool newState);
    /*public*/ void updateFunction(int fn, bool state);
    /*public*/ void updateFunctionMomentary(int fn, bool state);
    /*public*/ void setSpeedStepMode(SpeedStepMode::SSMODES newMode) override;
     /*public*/ SpeedStepMode::SSMODES getSpeedStepMode() override;
     /*public*/ void setRosterEntry(BasicRosterEntry* re) override;
     /*public*/ BasicRosterEntry* getRosterEntry() override;
     /*public*/ void setFunctionMomentary(int momFuncNum, bool state);

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
 /**
      * Array of Function values.
      * <p>
      * Contains current Boolean value for functions.
      * This array should not be accessed directly by Throttles,
      * use setFunction / getFunction / updateFunction.
      * Needs to be same length as FUNCTION_MOMENTARY_BOOLEAN_ARRAY.
      */
     /*private*/ /*final*/ QVector<bool> FUNCTION_BOOLEAN_ARRAY;

     /**
      * Array of Momentary Function values.
      * <p>
      * Contains current Boolean value for Momentary function settings.
      * Needs to be same length as FUNCTION_BOOLEAN_ARRAY.
      */
     /*private*/ /*final*/ QVector<bool> FUNCTION_MOMENTARY_BOOLEAN_ARRAY;

protected:
    /*protected*/ float speedSetting = 0.0;
    /**
     * Question: should we set a default speed step mode so it's never zero?
     */
    /*protected*/ SpeedStepMode::SSMODES speedStepMode;
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
     /*protected*/ void sendFunctionGroup(int functionNum, bool momentary);

 friend class AbstractThrottleTest;
};

#endif // ABSTRACTTHROTTLE_H
