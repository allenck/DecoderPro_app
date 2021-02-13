#ifndef ABSTRACTTHROTTLETEST_H
#define ABSTRACTTHROTTLETEST_H

#include <QObject>
#include "abstractthrottlemanager.h"
#include "abstractthrottle.h"

class AbstractThrottleTest : public QObject
{
    Q_OBJECT
public:
    explicit AbstractThrottleTest(QObject *parent = nullptr);
    Q_INVOKABLE virtual /*public*/ void setUp() throw (Exception);
    Q_INVOKABLE virtual /*public*/ void tearDown() throw (Exception);

public slots:
    /*public*/ void testGetSpeedSetting();
    /*public*/ void testSetSpeedSettingAgain();
    /*public*/ void testSetSpeedSetting();
    virtual /*public*/ void testGetIsForward();
    /*public*/ void testSetIsForward();
    /*public*/ void testGetF0();
    /*public*/ void testGetF1();
    /*public*/ void testGetF2();
    /*public*/ void testGetF3();
    /*public*/ void testGetF4();
    /*public*/ void testGetF5();
    /*public*/ void testGetF6();
    /*public*/ void testGetF7();
    /*public*/ void testGetF8();
    /*public*/ void testGetF9();
    /*public*/ void testGetF10();
    /*public*/ void testGetF11();
    /*public*/ void testGetF12();
    /*public*/ void testGetF13();
    /*public*/ void testGetF14();
    /*public*/ void testGetF15();
    /*public*/ void testGetF16();
    /*public*/ void testGetF17();
    /*public*/ void testGetF18();
    /*public*/ void testGetF19();
    /*public*/ void testGetF20();
    /*public*/ void testGetF21();
    /*public*/ void testGetF22();
    /*public*/ void testGetF23();
    /*public*/ void testGetF24();
    /*public*/ void testGetF25();
    /*public*/ void testGetF26();
    /*public*/ void testGetF27();
    /*public*/ void testGetF28();
    /*public*/ void testGetF0Momentary();
    /*public*/ void testGetF1Momentary();
    virtual /*public*/ void testGetF2Momentary();
    /*public*/ void testGetF3Momentary();
    /*public*/ void testGetF4Momentary();
    /*public*/ void testGetF5Momentary();
    /*public*/ void testGetF6Momentary();
    /*public*/ void testGetF7Momentary();
    /*public*/ void testGetF8Momentary();
    /*public*/ void testGetF9Momentary();
    /*public*/ void testGetF10Momentary();
    /*public*/ void testGetF11Momentary();
    /*public*/ void testGetF12Momentary();
    /*public*/ void testGetF13Momentary();
    /*public*/ void testGetF14Momentary();
    /*public*/ void testGetF15Momentary();
    /*public*/ void testGetF16Momentary();
    /*public*/ void testGetF17Momentary();
    /*public*/ void testGetF18Momentary();
    /*public*/ void testGetF19Momentary();
    /*public*/ void testGetF20Momentary();
    /*public*/ void testGetF21Momentary();
    /*public*/ void testGetF22Momentary();
    /*public*/ void testGetF23Momentary();
    /*public*/ void testGetF24Momentary();
    /*public*/ void testGetF25Momentary();
    /*public*/ void testGetF26Momentary();
    /*public*/ void testGetF27Momentary();
    /*public*/ void testGetF28Momentary();
    /*public*/ void testRemovePropertyChangeListener();
    /*public*/ void testAddPropertyChangeListener();
    /*public*/ void testNotifyPropertyChangeListener();
    /*public*/ void testGetListeners();
    /*public*/ void testDispose_ThrottleListener();
    /*public*/ void testDispatch_ThrottleListener();
    /*public*/ void testRelease_ThrottleListener();
    /*public*/ void testThrottleDispose();
    virtual /*public*/ void testGetSpeedIncrement();
    virtual /*public*/ void testSetF0();
    virtual /*public*/ void testSetF1();
    virtual /*public*/ void testSetF2();
    virtual /*public*/ void testSetF3();
    virtual /*public*/ void testSetF4();
    virtual /*public*/ void testSetF5();
    virtual /*public*/ void testSetF6();
    virtual /*public*/ void testSetF7();
    virtual /*public*/ void testSetF8();
    virtual /*public*/ void testSetF9();
    virtual /*public*/ void testSetF10();
    virtual /*public*/ void testSetF11();
    virtual /*public*/ void testSetF12();
    virtual /*public*/ void testSetF13();
    virtual /*public*/ void testSetF14();
    virtual /*public*/ void testSetF15();
    virtual /*public*/ void testSetF16();
    virtual /*public*/ void testSetF17();
    virtual /*public*/ void testSetF18();
    virtual /*public*/ void testSetF19();
    virtual /*public*/ void testSetF20();
    virtual /*public*/ void testSetF21();
    virtual /*public*/ void testSetF22();
    virtual /*public*/ void testSetF23();
    virtual /*public*/ void testSetF24();
    virtual /*public*/ void testSetF25();
    virtual /*public*/ void testSetF26();
    virtual /*public*/ void testSetF27();
    virtual /*public*/ void testSetF28();
    virtual /*public*/ void testSendFunctionGroup1();
    virtual /*public*/ void testSendFunctionGroup2();
    virtual /*public*/ void testSendFunctionGroup3();
    virtual /*public*/ void testSendFunctionGroup4();
    virtual /*public*/ void testSendFunctionGroup5();
    /*public*/ void testSetF0Momentary();
    /*public*/ void testSetF1Momentary();
    /*public*/ void testSetF2Momentary();
    /*public*/ void testSetF3Momentary();
    /*public*/ void testSetF4Momentary();
    /*public*/ void testSetF5Momentary();
    /*public*/ void testSetF6Momentary();
    /*public*/ void testSetF7Momentary();
    /*public*/ void testSetF8Momentary();
    /*public*/ void testSetF9Momentary();
    /*public*/ void testSetF10Momentary();
    /*public*/ void testSetF11Momentary();
    /*public*/ void testSetF12Momentary();
    /*public*/ void testSetF13Momentary();
    /*public*/ void testSetF14Momentary();
    /*public*/ void testSetF15Momentary();
    /*public*/ void testSetF16Momentary();
    /*public*/ void testSetF17Momentary();
    /*public*/ void testSetF18Momentary();
    /*public*/ void testSetF19Momentary();
    /*public*/ void testSetF20Momentary();
    /*public*/ void testSetF21Momentary();
    /*public*/ void testSetF22Momentary();
    /*public*/ void testSetF23Momentary();
    /*public*/ void testSetF24Momentary();
    /*public*/ void testSetF25Momentary();
    /*public*/ void testSetF26Momentary();
    /*public*/ void testSetF27Momentary();
    /*public*/ void testSetF28Momentary();
    /*public*/ void testSendMomentaryFunctionGroup1();
    /*public*/ void testSendMomentaryFunctionGroup2();
    /*public*/ void testSendMomentaryFunctionGroup3();
    /*public*/ void testSendMomentaryFunctionGroup4();
    /*public*/ void testSendMomentaryFunctionGroup5();
    virtual /*public*/ void testSetSpeedStepMode();
    virtual /*public*/ void testGetSpeedStepMode();
    /*public*/ void testRecord();
    /*public*/ void testStartClock();
    /*public*/ void testStopClock();
    /*public*/ void testFinishRecord();
    /*public*/ void testSetRosterEntry();
    /*public*/ void testGetRosterEntry();
    virtual /*public*/ void testGetSpeed_float();
    /*public*/ void testGetSpeed_float_int();

signals:

public slots:

private:
    static Logger* log;

protected:
    /*protected*/ AbstractThrottle* instance = nullptr;


};
class AbstractThrottleManagerO1 : public AbstractThrottleManager
{
    Q_OBJECT
public:
    //@Override
    /*public*/ void requestThrottleSetup(DccLocoAddress* /*a*/, bool /*control*/) {
    }

    //@Override
    /*public*/ bool canBeLongAddress(int /*address*/) {
        return true;
    }

    //@Override
    /*public*/ bool canBeShortAddress(int /*address*/) {
        return true;
    }

    //@Override
    /*public*/ bool addressTypeUnique() {
        return true;
    }
};
/*public*/ /*final*/ class AbstractThrottleImpl /*extends*/ : public AbstractThrottle
{
Q_OBJECT
    /*private*/ DccLocoAddress* locoAddress;
private:
    /*public*/ AbstractThrottleImpl() : AbstractThrottle(nullptr){
        //super(null);
        this->setLocoAddress(new DccLocoAddress(3, DccLocoAddress::Protocol::DCC_SHORT));
    }

    //@Override
    /*public*/ void throttleDispose() {
    }

    /*public*/ void setLocoAddress(DccLocoAddress* locoAddress) {
        this->locoAddress = locoAddress;
    }

    //@Override
    /*public*/ DccLocoAddress* getLocoAddress() {
        return this->locoAddress;
    }
  QObject* self() {return(QObject*)this;}
    friend class AbstractThrottleTest;
};
class PropertyChangeListenerO1  : public PropertyChangeListener
{
    Q_OBJECT
public slots:
    void propertyChange(PropertyChangeEvent* evt) {}
};

#endif // ABSTRACTTHROTTLETEST_H
