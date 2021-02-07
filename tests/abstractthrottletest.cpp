#include "abstractthrottletest.h"
#include "loggerfactory.h"
#include "locoaddress.h"
#include "assert1.h"
#include "instancemanager.h"
#include "junitutil.h"
#include "junitappender.h"
#include "speedstepmode.h"

AbstractThrottleTest::AbstractThrottleTest(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author Randall Wood 2015
 */
///*public*/ class AbstractThrottleTest {


//@Before
/*public*/ void AbstractThrottleTest::AbstractThrottleTest::setUp() throw (Exception) {
    JUnitUtil::setUp();
    InstanceManager::setThrottleManager(new AbstractThrottleManagerO1());
//        {

//            @Override
//            /*public*/ void AbstractThrottleTest::requestThrottleSetup(LocoAddress a, bool control) {
//            }

//            @Override
//            /*public*/ bool canBeLongAddress(int address) {
//                return true;
//            }

//            @Override
//            /*public*/ bool canBeShortAddress(int address) {
//                return true;
//            }

//            @Override
//            /*public*/ bool addressTypeUnique() {
//                return true;
//            }
//        });
    instance = new AbstractThrottleImpl();
}

//@After
/*public*/ void AbstractThrottleTest::AbstractThrottleTest::tearDown() throw (Exception) {
    JUnitUtil::tearDown();
}

/**
 * Test of getSpeedSetting method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::AbstractThrottleTest::testGetSpeedSetting() {
    float expResult = 0.0F;
    float result = instance->getSpeedSetting();
    Assert::assertEquals(expResult, result, 0.0f, __FILE__, __LINE__);
}

/**
 * Test of setSpeedSettingAgain method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::AbstractThrottleTest::testSetSpeedSettingAgain() {
    float speed = 1.0F;
    instance->setSpeedSettingAgain(speed);
    Assert::assertEquals(speed, instance->getSpeedSetting(), 0.0f, __FILE__, __LINE__);
}

/**
 * Test of setSpeedSetting method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::AbstractThrottleTest::testSetSpeedSetting() {
    float speed = 1.0F;
    instance->setSpeedSetting(speed);
    Assert::assertEquals(speed, instance->getSpeedSetting(), 0.0f, __FILE__, __LINE__);
}

/**
 * Test of getIsForward method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::AbstractThrottleTest::testGetIsForward() {
    bool expResult = false;
    bool result = instance->getIsForward();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of setIsForward method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::AbstractThrottleTest::testSetIsForward() {
    bool forward = false;
    instance->setIsForward(forward);
}

/**
 * Test of getF0 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::AbstractThrottleTest::testGetF0() {
    bool expResult = false;
    bool result = instance->getF0();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF1 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::AbstractThrottleTest::testGetF1() {
    bool expResult = false;
    bool result = instance->getF1();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF2 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF2() {
    bool expResult = false;
    bool result = instance->getF2();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF3 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF3() {
    bool expResult = false;
    bool result = instance->getF3();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF4 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF4() {
    bool expResult = false;
    bool result = instance->getF4();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF5 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF5() {
    bool expResult = false;
    bool result = instance->getF5();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF6 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF6() {
    bool expResult = false;
    bool result = instance->getF6();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF7 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF7() {
    bool expResult = false;
    bool result = instance->getF7();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF8 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF8() {
    bool expResult = false;
    bool result = instance->getF8();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF9 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF9() {
    bool expResult = false;
    bool result = instance->getF9();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF10 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF10() {
    bool expResult = false;
    bool result = instance->getF10();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF11 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF11() {
    bool expResult = false;
    bool result = instance->getF11();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF12 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF12() {
    bool expResult = false;
    bool result = instance->getF12();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF13 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF13() {
    bool expResult = false;
    bool result = instance->getF13();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF14 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF14() {
    bool expResult = false;
    bool result = instance->getF14();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF15 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF15() {
    bool expResult = false;
    bool result = instance->getF15();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF16 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF16() {
    bool expResult = false;
    bool result = instance->getF16();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF17 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF17() {
    bool expResult = false;
    bool result = instance->getF17();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF18 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF18() {
    bool expResult = false;
    bool result = instance->getF18();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF19 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF19() {
    bool expResult = false;
    bool result = instance->getF19();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF20 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF20() {
    bool expResult = false;
    bool result = instance->getF20();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF21 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF21() {
    bool expResult = false;
    bool result = instance->getF21();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF22 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF22() {
    bool expResult = false;
    bool result = instance->getF22();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF23 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF23() {
    bool expResult = false;
    bool result = instance->getF23();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF24 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF24() {
    bool expResult = false;
    bool result = instance->getF24();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF25 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF25() {
    bool expResult = false;
    bool result = instance->getF25();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF26 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF26() {
    bool expResult = false;
    bool result = instance->getF26();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF27 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF27() {
    bool expResult = false;
    bool result = instance->getF27();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF28 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF28() {
    bool expResult = false;
    bool result = instance->getF28();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF0Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF0Momentary() {
    bool expResult = false;
    bool result = instance->getF0Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF1Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF1Momentary() {
    bool expResult = false;
    bool result = instance->getF1Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF2Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF2Momentary() {
    bool expResult = false;
    bool result = instance->getF2Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF3Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF3Momentary() {
    bool expResult = false;
    bool result = instance->getF3Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF4Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF4Momentary() {
    bool expResult = false;
    bool result = instance->getF4Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF5Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF5Momentary() {
    bool expResult = false;
    bool result = instance->getF5Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF6Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF6Momentary() {
    bool expResult = false;
    bool result = instance->getF6Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF7Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF7Momentary() {
    bool expResult = false;
    bool result = instance->getF7Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF8Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF8Momentary() {
    bool expResult = false;
    bool result = instance->getF8Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF9Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF9Momentary() {
    bool expResult = false;
    bool result = instance->getF9Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF10Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF10Momentary() {
    bool expResult = false;
    bool result = instance->getF10Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF11Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF11Momentary() {
    bool expResult = false;
    bool result = instance->getF11Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF12Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF12Momentary() {
    bool expResult = false;
    bool result = instance->getF12Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF13Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF13Momentary() {
    bool expResult = false;
    bool result = instance->getF13Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF14Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF14Momentary() {
    bool expResult = false;
    bool result = instance->getF14Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF15Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF15Momentary() {
    bool expResult = false;
    bool result = instance->getF15Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF16Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF16Momentary() {
    bool expResult = false;
    bool result = instance->getF16Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF17Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF17Momentary() {
    bool expResult = false;
    bool result = instance->getF17Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF18Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF18Momentary() {
    bool expResult = false;
    bool result = instance->getF18Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF19Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF19Momentary() {
    bool expResult = false;
    bool result = instance->getF19Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF20Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF20Momentary() {
    bool expResult = false;
    bool result = instance->getF20Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF21Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF21Momentary() {
    bool expResult = false;
    bool result = instance->getF21Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF22Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF22Momentary() {
    bool expResult = false;
    bool result = instance->getF22Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF23Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF23Momentary() {
    bool expResult = false;
    bool result = instance->getF23Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF24Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF24Momentary() {
    bool expResult = false;
    bool result = instance->getF24Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF25Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF25Momentary() {
    bool expResult = false;
    bool result = instance->getF25Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF26Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF26Momentary() {
    bool expResult = false;
    bool result = instance->getF26Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF27Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF27Momentary() {
    bool expResult = false;
    bool result = instance->getF27Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getF28Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetF28Momentary() {
    bool expResult = false;
    bool result = instance->getF28Momentary();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of removePropertyChangeListener method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testRemovePropertyChangeListener() {
//    PropertyChangeListener l = (PropertyChangeEvent evt) -> {
//    };
    PropertyChangeListenerO1* l = new PropertyChangeListenerO1();
    instance->removePropertyChangeListener(l);
}

/**
 * Test of addPropertyChangeListener method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testAddPropertyChangeListener() {
    PropertyChangeListener* l = nullptr;
    instance->addPropertyChangeListener(l);
}

/**
 * Test of notifyPropertyChangeListener method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testNotifyPropertyChangeListener() {
    QString property = "";
    QVariant oldValue = QVariant();
    QVariant newValue = QVariant();
    instance->notifyPropertyChangeListener(property, oldValue, newValue);
    JUnitAppender::assertErrorMessage("notifyPropertyChangeListener without change",__FILE__, __LINE__);
}

/**
 * Test of getListeners method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetListeners() {
    QVector<PropertyChangeListener*>* expResult = new QVector<PropertyChangeListener*>();
    QVector<PropertyChangeListener*>* result = instance->getListeners();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of dispose method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testDispose_ThrottleListener() {
    ThrottleListener* l = nullptr;
    instance->dispose(l);
}

/**
 * Test of dispatch method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testDispatch_ThrottleListener() {
    ThrottleListener* l = nullptr;
    instance->dispatch(l);
}

/**
 * Test of release method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testRelease_ThrottleListener() {
    ThrottleListener* l = nullptr;
    instance->release(l);
}

/**
 * Test of throttleDispose method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testThrottleDispose() {
    instance->throttleDispose();
}

/**
 * Test of getSpeedIncrement method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetSpeedIncrement() {
    float expResult = 0.0F;
    float result = instance->getSpeedIncrement();
    Assert::assertEquals(expResult, result, 0.0f, __FILE__, __LINE__);
}

/**
 * Test of setF0 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF0() {
    bool f0 = false;
    instance->setF0(f0);
    JUnitAppender::assertErrorMessage("sendFunctionGroup1 needs to be implemented if invoked",__FILE__, __LINE__);
}

/**
 * Test of setF1 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF1() {
    bool f1 = false;
    instance->setF1(f1);
    JUnitAppender::assertErrorMessage("sendFunctionGroup1 needs to be implemented if invoked",__FILE__, __LINE__);
}

/**
 * Test of setF2 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF2() {
    bool f2 = false;
    instance->setF2(f2);
    JUnitAppender::assertErrorMessage("sendFunctionGroup1 needs to be implemented if invoked",__FILE__, __LINE__);
}

/**
 * Test of setF3 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF3() {
    bool f3 = false;
    instance->setF3(f3);
    JUnitAppender::assertErrorMessage("sendFunctionGroup1 needs to be implemented if invoked",__FILE__, __LINE__);
}

/**
 * Test of setF4 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF4() {
    bool f4 = false;
    instance->setF4(f4);
    JUnitAppender::assertErrorMessage("sendFunctionGroup1 needs to be implemented if invoked",__FILE__, __LINE__);
}

/**
 * Test of setF5 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF5() {
    bool f5 = false;
    instance->setF5(f5);
    JUnitAppender::assertErrorMessage("sendFunctionGroup2 needs to be implemented if invoked",__FILE__, __LINE__);
}

/**
 * Test of setF6 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF6() {
    bool f6 = false;
    instance->setF6(f6);
    JUnitAppender::assertErrorMessage("sendFunctionGroup2 needs to be implemented if invoked",__FILE__, __LINE__);
}

/**
 * Test of setF7 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF7() {
    bool f7 = false;
    instance->setF7(f7);
    JUnitAppender::assertErrorMessage("sendFunctionGroup2 needs to be implemented if invoked",__FILE__, __LINE__);
}

/**
 * Test of setF8 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF8() {
    bool f8 = false;
    instance->setF8(f8);
    JUnitAppender::assertErrorMessage("sendFunctionGroup2 needs to be implemented if invoked",__FILE__, __LINE__);
}

/**
 * Test of setF9 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF9() {
    bool f9 = false;
    instance->setF9(f9);
    JUnitAppender::assertErrorMessage("sendFunctionGroup3 needs to be implemented if invoked",__FILE__, __LINE__);
}

/**
 * Test of setF10 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF10() {
    bool f10 = false;
    instance->setF10(f10);
    JUnitAppender::assertErrorMessage("sendFunctionGroup3 needs to be implemented if invoked",__FILE__, __LINE__);
}

/**
 * Test of setF11 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF11() {
    bool f11 = false;
    instance->setF11(f11);
    JUnitAppender::assertErrorMessage("sendFunctionGroup3 needs to be implemented if invoked",__FILE__, __LINE__);
}

/**
 * Test of setF12 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF12() {
    bool f12 = false;
    instance->setF12(f12);
    JUnitAppender::assertErrorMessage("sendFunctionGroup3 needs to be implemented if invoked",__FILE__, __LINE__);
}

/**
 * Test of setF13 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF13() {
    bool f13 = false;
    instance->setF13(f13);
    JUnitAppender::assertErrorMessage("Can't send F13-F20 since no command station defined",__FILE__, __LINE__);
}

/**
 * Test of setF14 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF14() {
    bool f14 = false;
    instance->setF14(f14);
    JUnitAppender::assertErrorMessage("Can't send F13-F20 since no command station defined",__FILE__, __LINE__);
}

/**
 * Test of setF15 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF15() {
    bool f15 = false;
    instance->setF15(f15);
    JUnitAppender::assertErrorMessage("Can't send F13-F20 since no command station defined",__FILE__, __LINE__);
}

/**
 * Test of setF16 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF16() {
    bool f16 = false;
    instance->setF16(f16);
    JUnitAppender::assertErrorMessage("Can't send F13-F20 since no command station defined",__FILE__, __LINE__);
}

/**
 * Test of setF17 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF17() {
    bool f17 = false;
    instance->setF17(f17);
    JUnitAppender::assertErrorMessage("Can't send F13-F20 since no command station defined",__FILE__, __LINE__);
}

/**
 * Test of setF18 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF18() {
    bool f18 = false;
    instance->setF18(f18);
    JUnitAppender::assertErrorMessage("Can't send F13-F20 since no command station defined",__FILE__, __LINE__);
}

/**
 * Test of setF19 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF19() {
    bool f19 = false;
    instance->setF19(f19);
    JUnitAppender::assertErrorMessage("Can't send F13-F20 since no command station defined",__FILE__, __LINE__);
}

/**
 * Test of setF20 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF20() {
    bool f20 = false;
    instance->setF20(f20);
    JUnitAppender::assertErrorMessage("Can't send F13-F20 since no command station defined",__FILE__, __LINE__);
}

/**
 * Test of setF21 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF21() {
    bool f21 = false;
    instance->setF21(f21);
    JUnitAppender::assertErrorMessage("Can't send F21-F28 since no command station defined",__FILE__, __LINE__);
}

/**
 * Test of setF22 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF22() {
    bool f22 = false;
    instance->setF22(f22);
    JUnitAppender::assertErrorMessage("Can't send F21-F28 since no command station defined",__FILE__, __LINE__);
}

/**
 * Test of setF23 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF23() {
    bool f23 = false;
    instance->setF23(f23);
    JUnitAppender::assertErrorMessage("Can't send F21-F28 since no command station defined",__FILE__, __LINE__);
}

/**
 * Test of setF24 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF24() {
    bool f24 = false;
    instance->setF24(f24);
    JUnitAppender::assertErrorMessage("Can't send F21-F28 since no command station defined",__FILE__, __LINE__);
}

/**
 * Test of setF25 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF25() {
    bool f25 = false;
    instance->setF25(f25);
    JUnitAppender::assertErrorMessage("Can't send F21-F28 since no command station defined",__FILE__, __LINE__);
}

/**
 * Test of setF26 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF26() {
    bool f26 = false;
    instance->setF26(f26);
    JUnitAppender::assertErrorMessage("Can't send F21-F28 since no command station defined",__FILE__, __LINE__);
}

/**
 * Test of setF27 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF27() {
    bool f27 = false;
    instance->setF27(f27);
    JUnitAppender::assertErrorMessage("Can't send F21-F28 since no command station defined",__FILE__, __LINE__);
}

/**
 * Test of setF28 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF28() {
    bool f28 = false;
    instance->setF28(f28);
    JUnitAppender::assertErrorMessage("Can't send F21-F28 since no command station defined",__FILE__, __LINE__);
}

/**
 * Test of sendFunctionGroup1 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSendFunctionGroup1() {
    instance->sendFunctionGroup1();
    JUnitAppender::assertErrorMessage("sendFunctionGroup1 needs to be implemented if invoked",__FILE__, __LINE__);
}

/**
 * Test of sendFunctionGroup2 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSendFunctionGroup2() {
    instance->sendFunctionGroup2();
    JUnitAppender::assertErrorMessage("sendFunctionGroup2 needs to be implemented if invoked",__FILE__, __LINE__);
}

/**
 * Test of sendFunctionGroup3 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSendFunctionGroup3() {
    instance->sendFunctionGroup3();
    JUnitAppender::assertErrorMessage("sendFunctionGroup3 needs to be implemented if invoked",__FILE__, __LINE__);
}

/**
 * Test of sendFunctionGroup4 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSendFunctionGroup4() {
    instance->sendFunctionGroup4();
    JUnitAppender::assertErrorMessage("Can't send F13-F20 since no command station defined",__FILE__, __LINE__);
}

/**
 * Test of sendFunctionGroup5 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSendFunctionGroup5() {
    instance->sendFunctionGroup5();
    JUnitAppender::assertErrorMessage("Can't send F21-F28 since no command station defined",__FILE__, __LINE__);
}

/**
 * Test of setF0Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF0Momentary() {
    bool f0Momentary = false;
    instance->setF0Momentary(f0Momentary);
}

/**
 * Test of setF1Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF1Momentary() {
    bool f1Momentary = false;
    instance->setF1Momentary(f1Momentary);
}

/**
 * Test of setF2Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF2Momentary() {
    bool f2Momentary = false;
    instance->setF2Momentary(f2Momentary);
}

/**
 * Test of setF3Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF3Momentary() {
    bool f3Momentary = false;
    instance->setF3Momentary(f3Momentary);
}

/**
 * Test of setF4Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF4Momentary() {
    bool f4Momentary = false;
    instance->setF4Momentary(f4Momentary);
}

/**
 * Test of setF5Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF5Momentary() {
    bool f5Momentary = false;
    instance->setF5Momentary(f5Momentary);
}

/**
 * Test of setF6Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF6Momentary() {
    bool f6Momentary = false;
    instance->setF6Momentary(f6Momentary);
}

/**
 * Test of setF7Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF7Momentary() {
    bool f7Momentary = false;
    instance->setF7Momentary(f7Momentary);
}

/**
 * Test of setF8Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF8Momentary() {
    bool f8Momentary = false;
    instance->setF8Momentary(f8Momentary);
}

/**
 * Test of setF9Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF9Momentary() {
    bool f9Momentary = false;
    instance->setF9Momentary(f9Momentary);
}

/**
 * Test of setF10Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF10Momentary() {
    bool f10Momentary = false;
    instance->setF10Momentary(f10Momentary);
}

/**
 * Test of setF11Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF11Momentary() {
    bool f11Momentary = false;
    instance->setF11Momentary(f11Momentary);
}

/**
 * Test of setF12Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF12Momentary() {
    bool f12Momentary = false;
    instance->setF12Momentary(f12Momentary);
}

/**
 * Test of setF13Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF13Momentary() {
    bool f13Momentary = false;
    instance->setF13Momentary(f13Momentary);
}

/**
 * Test of setF14Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF14Momentary() {
    bool f14Momentary = false;
    instance->setF14Momentary(f14Momentary);
}

/**
 * Test of setF15Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF15Momentary() {
    bool f15Momentary = false;
    instance->setF15Momentary(f15Momentary);
}

/**
 * Test of setF16Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF16Momentary() {
    bool f16Momentary = false;
    instance->setF16Momentary(f16Momentary);
}

/**
 * Test of setF17Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF17Momentary() {
    bool f17Momentary = false;
    instance->setF17Momentary(f17Momentary);
}

/**
 * Test of setF18Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF18Momentary() {
    bool f18Momentary = false;
    instance->setF18Momentary(f18Momentary);
}

/**
 * Test of setF19Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF19Momentary() {
    bool f19Momentary = false;
    instance->setF19Momentary(f19Momentary);
}

/**
 * Test of setF20Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF20Momentary() {
    bool f20Momentary = false;
    instance->setF20Momentary(f20Momentary);
}

/**
 * Test of setF21Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF21Momentary() {
    bool f21Momentary = false;
    instance->setF21Momentary(f21Momentary);
}

/**
 * Test of setF22Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF22Momentary() {
    bool f22Momentary = false;
    instance->setF22Momentary(f22Momentary);
}

/**
 * Test of setF23Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF23Momentary() {
    bool f23Momentary = false;
    instance->setF23Momentary(f23Momentary);
}

/**
 * Test of setF24Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF24Momentary() {
    bool f24Momentary = false;
    instance->setF24Momentary(f24Momentary);
}

/**
 * Test of setF25Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF25Momentary() {
    bool f25Momentary = false;
    instance->setF25Momentary(f25Momentary);
}

/**
 * Test of setF26Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF26Momentary() {
    bool f26Momentary = false;
    instance->setF26Momentary(f26Momentary);
}

/**
 * Test of setF27Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF27Momentary() {
    bool f27Momentary = false;
    instance->setF27Momentary(f27Momentary);
}

/**
 * Test of setF28Momentary method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetF28Momentary() {
    bool f28Momentary = false;
    instance->setF28Momentary(f28Momentary);
}

/**
 * Test of sendMomentaryFunctionGroup1 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSendMomentaryFunctionGroup1() {
    instance->sendMomentaryFunctionGroup1();
}

/**
 * Test of sendMomentaryFunctionGroup2 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSendMomentaryFunctionGroup2() {
    instance->sendMomentaryFunctionGroup2();
}

/**
 * Test of sendMomentaryFunctionGroup3 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSendMomentaryFunctionGroup3() {
    instance->sendMomentaryFunctionGroup3();
}

/**
 * Test of sendMomentaryFunctionGroup4 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSendMomentaryFunctionGroup4() {
    instance->sendMomentaryFunctionGroup4();
}

/**
 * Test of sendMomentaryFunctionGroup5 method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSendMomentaryFunctionGroup5() {
    instance->sendMomentaryFunctionGroup5();
}

/**
 * Test of setSpeedStepMode method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetSpeedStepMode() {
    instance->setSpeedStepMode(SpeedStepMode::NMRA_DCC_128);
}

/**
 * Test of getSpeedStepMode method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetSpeedStepMode() {
    SpeedStepMode::SSMODES expResult = SpeedStepMode::UNKNOWN;
    SpeedStepMode::SSMODES result = instance->getSpeedStepMode();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of record method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testRecord() {
    float speed = 0.0F;
    instance->record(speed);
}

/**
 * Test of startClock method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testStartClock() {
    instance->startClock();
}

/**
 * Test of stopClock method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testStopClock() {
    instance->stopClock();
}

/**
 * Test of finishRecord method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testFinishRecord() {
    instance->finishRecord();
}

/**
 * Test of setRosterEntry method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testSetRosterEntry() {
    BasicRosterEntry* re = nullptr;
    instance->setRosterEntry(re);
}

/**
 * Test of getRosterEntry method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetRosterEntry() {
    BasicRosterEntry* expResult = nullptr;
    BasicRosterEntry* result = instance->getRosterEntry();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of intSpeed method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetSpeed_float() {
    Assert::assertEquals("Full Speed", 127, instance->intSpeed(1.0F), __FILE__, __LINE__);
    float incre = 0.007874016f;
    float speed = incre;
    // Cannot get speeedStep 1. range is 2 to 127
    int i = 2;
    while (speed < 0.999f) {
        int result = instance->intSpeed(speed);
        log->debug(tr("speed= %1 step= %2").arg(speed).arg(result));
        Assert::assertEquals("speed step ", i++, result, __FILE__, __LINE__);
        speed += incre;
    }
}

/**
 * Test of intSpeed method, of class AbstractThrottle.
 */
//@Test
/*public*/ void AbstractThrottleTest::testGetSpeed_float_int() {
    float speed = 0.001F;
    int maxStepHi = 127;
    int maxStepLo = 28;
    Assert::assertEquals("Idle", 0, instance->intSpeed(0.0F, maxStepHi), __FILE__, __LINE__);
    Assert::assertEquals("Idle", 0, instance->intSpeed(0.0F, maxStepLo), __FILE__, __LINE__);
    Assert::assertEquals("Emergency", 1, instance->intSpeed(-1.0F, maxStepHi), __FILE__, __LINE__);
    Assert::assertEquals("Emergency", 1, instance->intSpeed(-1.0F, maxStepLo), __FILE__, __LINE__);
    Assert::assertEquals("Emergency", 1, instance->intSpeed(-0.001F, maxStepHi), __FILE__, __LINE__);
    Assert::assertEquals("Emergency", 1, instance->intSpeed(-0.001F, maxStepLo), __FILE__, __LINE__);
    Assert::assertEquals("Full Speed", maxStepHi, instance->intSpeed(1.0F, maxStepHi), __FILE__, __LINE__);
    Assert::assertEquals("Full Speed", maxStepLo, instance->intSpeed(1.0F, maxStepLo), __FILE__, __LINE__);
    while (speed < 1.1F) { // loop ~ 1100 times
        int result = instance->intSpeed(speed, maxStepHi);
        Assert::assertNotSame(QString::number(speed) + "(" + QString::number(maxStepHi) + " steps) should not idle", 0, result, __FILE__, __LINE__);
        Assert::assertNotSame(QString::number(speed) + "(" + QString::number(maxStepHi) + " steps) should not eStop", 1, result, __FILE__, __LINE__);
        Assert::assertTrue(QString::number(speed) + "(" + QString::number(maxStepHi) + " steps) should not exceed " + QString::number(maxStepHi), result <= 127, __FILE__, __LINE__);
        result = instance->intSpeed(speed, maxStepLo);
        Assert::assertNotSame(QString::number(speed) + "(" + QString::number(maxStepLo) + " steps) should not idle", 0, result, __FILE__, __LINE__);
        Assert::assertNotSame(QString::number(speed) + "(" + QString::number(maxStepLo) + " steps) should not eStop", 1, result, __FILE__, __LINE__);
        Assert::assertTrue(QString::number(speed) + "(" + QString::number(maxStepLo) + " steps) should not exceed " + QString::number(maxStepLo), result <= 127, __FILE__, __LINE__);
        speed = speed + 0.001F;
    }
}


/*private*/ /*final*/ /*static*/ Logger* AbstractThrottleTest::log = LoggerFactory::getLogger("AbstractThrottleTest");


