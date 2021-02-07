#include "loconetthrottletest.h"
#include "junitutil.h"
#include "assert1.h"
#include "instancemanager.h"
#include "loconetinterfacescaffold.h"
#include "slotmanager.h"
#include "loconetsystemconnectionmemo.h"
#include "lnthrottlemanager.h"

LocoNetThrottleTest::LocoNetThrottleTest()
{

}
///*public*/ class LocoNetThrottleTest extends jmri.jmrix.AbstractThrottleTest {

//@Test
/*public*/ void LocoNetThrottleTest::testCTor() {
    Assert::assertNotNull(instance, __FILE__, __LINE__);
}

// test the speed setting code.
//@Test
/*public*/ void LocoNetThrottleTest::testSpeedSetting() {
    // we have 4 cases to check
    // Case 1: The locomotive is not consisted.
//    LocoNetSlot s1 = new LocoNetSlot(0) {
//        @Override
//        /*public*/ int consistStatus() {
//            return LnConstants::CONSIST_NO;
//        }

//        @Override
//        /*public*/ int speed() {
//            return 0;
//        }
//    };
    LocoNetSlot* s1 = new LocoNetSlotO1(0);
    LocoNetThrottle* t1 = new LocoNetThrottle(memo, s1);
    Assert::assertEquals(0.0f, t1->getSpeedSetting(), 0.0f, __FILE__, __LINE__);
    t1->setSpeedSetting(0.5f);
    // the speed change SHOULD be changed.
    Assert::assertEquals(0.5f, t1->getSpeedSetting(), 0.0f, __FILE__, __LINE__);

    // Case 2: The locomotive is a consist top.
//    LocoNetSlot s2 = new LocoNetSlot(1) {
//        @Override
//        /*public*/ int consistStatus() {
//            return LnConstants::CONSIST_TOP;
//        }

//        @Override
//        /*public*/ int speed() {
//            return 0;
//        }
//    };
    LocoNetSlot* s2 = new LocoNetSlotO2(0);

    LocoNetThrottle* t2 = new LocoNetThrottle(memo, s2);
    Assert::assertEquals(0.0f, t2->getSpeedSetting(), 0.0f, __FILE__, __LINE__);
    t2->setSpeedSetting(0.5f);
    // the speed change SHOULD be changed.
    Assert::assertEquals(0.5f, t2->getSpeedSetting(), 0.0f, __FILE__, __LINE__);

    // Case 3: The locomotive is a consist mid.
//    LocoNetSlot s3 = new LocoNetSlot(2) {
//        @Override
//        /*public*/ int consistStatus() {
//            return LnConstants::CONSIST_MID;
//        }

//        @Override
//        /*public*/ int speed() {
//            return 0;
//        }
//    };
    LocoNetSlot* s3 = new LocoNetSlotO3(0);

    LocoNetThrottle* t3 = new LocoNetThrottle(memo, s3);
    Assert::assertEquals(0.0f, t3->getSpeedSetting(), 0.0F, __FILE__, __LINE__);
    t3->setSpeedSetting(0.5f);
    // the speed change SHOULD NOT be changed.
    Assert::assertEquals(0.0f, t3->getSpeedSetting(), 0.0f, __FILE__, __LINE__);

    // Case 3: The locomotive is a consist mid.
    // make sure the speed does NOT change for a consist sub
//    LocoNetSlot s4 = new LocoNetSlot(3) {
//        @Override
//        /*public*/ int consistStatus() {
//            return LnConstants::CONSIST_SUB;
//        }

//        @Override
//        /*public*/ int speed() {
//            return 0;
//        }
//    };
    LocoNetSlot* s4 = new LocoNetSlotO4(0);

    LocoNetThrottle* t4 = new LocoNetThrottle(memo, s4);
    Assert::assertEquals(0.0f, t4->getSpeedSetting(), 0.0f, __FILE__, __LINE__);
    t4->setSpeedSetting(0.5f);
    // the speed change SHOULD be ignored.
    Assert::assertEquals(0.0f, t4->getSpeedSetting(), 0.0f, __FILE__, __LINE__);
}

/**
 * Test of getIsForward method, of class AbstractThrottle.
 */
//@Test
//@Override
/*public*/ void LocoNetThrottleTest::testGetIsForward() {
    bool expResult = true;
    bool result = instance->getIsForward();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}
/**
 * Test of getSpeedStepMode method, of class AbstractThrottle.
 */
//@Test
//@Override
/*public*/ void LocoNetThrottleTest::testGetSpeedStepMode() {
    SpeedStepMode* expResult = new SpeedStepMode("28", SpeedStepMode::NMRA_DCC_28);
    SpeedStepMode* result =  new SpeedStepMode();//instance->getSpeedStepMode();
    Assert::assertEquals(expResult, result, __FILE__, __LINE__);
}

/**
 * Test of getSpeedIncrement method, of class AbstractThrottle.
 */
//@Test
//@Override
/*public*/ void LocoNetThrottleTest::testGetSpeedIncrement() {
    float expResult = 1.0F/28.0F;
    float result = instance->getSpeedIncrement();
    Assert::assertEquals(expResult, result, 0.0f, __FILE__, __LINE__);
}

/**
 * Test of intSpeed method, of class AbstractThrottle.
 */
//@Test
//@Override
/*public*/ void LocoNetThrottleTest::testGetSpeed_float() {
    // set speed step mode to 128.
    instance->setSpeedStepMode(SpeedStepMode::NMRA_DCC_128);
    Assert::assertEquals("Full Speed", 127, ((LocoNetThrottle*)instance)->intSpeed(1.0F), __FILE__, __LINE__);
    float incre = 0.007874016f;
    float speed = incre;
    // Cannot get speeedStep 1. range is 2 to 127
    int i = 2;
    while (speed < 0.999f) {
        int result = ((LocoNetThrottle*)instance)->intSpeed(speed);
        Assert::assertEquals("speed step ", i++, result, __FILE__, __LINE__);
        speed += incre;
    }
}

/**
 * Test of setF0 method, of class AbstractThrottle.
 */
//@Test
//@Override
/*public*/ void LocoNetThrottleTest::testSetF0() {
    lnis->outbound.clear();
    lnis->resetStatistics();
    bool f0 = false;
    instance->setF0(f0);
    Assert::assertEquals(f0, instance->getF0(), __FILE__, __LINE__);
    Assert::assertEquals("number of messages is 1", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("opcode is OPC_LOCO_DIRF", LnConstants::OPC_LOCO_DIRF, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("sent f0 in correct state", 0, lnis->outbound.at(0)->getElement(2) & 0x10, __FILE__, __LINE__);
    f0 = true;
    instance->setF0(f0);
    Assert::assertEquals(f0, instance->getF0(), __FILE__, __LINE__);
    Assert::assertEquals("number of messages is 2", 2, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("opcode is OPC_LOCO_DIRF", LnConstants::OPC_LOCO_DIRF, lnis->outbound.at(1)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("sent f0 in correct state", 0x10, lnis->outbound.at(1)->getElement(2) & 0x10, __FILE__, __LINE__);
}

/**
 * Test of setF1 method, of class AbstractThrottle.
 */
//@Test
//@Override
/*public*/ void LocoNetThrottleTest::testSetF1() {
    lnis->outbound.clear();
    lnis->resetStatistics();
    bool f1 = false;
    instance->setF1(f1);
    Assert::assertEquals(f1, instance->getF1(), __FILE__, __LINE__);
    Assert::assertEquals("number of messages is 1", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("opcode is OPC_LOCO_DIRF", LnConstants::OPC_LOCO_DIRF, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("sent f1 in correct state", 0, lnis->outbound.at(0)->getElement(2) & 1, __FILE__, __LINE__);
    f1 = true;
    instance->setF1(f1);
    Assert::assertEquals(f1, instance->getF1(), __FILE__, __LINE__);
    Assert::assertEquals("number of messages is 2", 2, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("opcode is OPC_LOCO_DIRF", LnConstants::OPC_LOCO_DIRF, lnis->outbound.at(1)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("sent f1 in correct state", 1, lnis->outbound.at(1)->getElement(2) & 1, __FILE__, __LINE__);
}

/**
 * Test of setF2 method, of class AbstractThrottle.
 */
//@Test
//@Override
/*public*/ void LocoNetThrottleTest::testSetF2() {
    lnis->outbound.clear();
    lnis->resetStatistics();
    bool f2 = false;
    instance->setF2(f2);
    Assert::assertEquals(f2, instance->getF2(), __FILE__, __LINE__);
    Assert::assertEquals("number of messages is 1", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("opcode is OPC_LOCO_DIRF", LnConstants::OPC_LOCO_DIRF, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("sent f2 in correct state", 0, lnis->outbound.at(0)->getElement(2) & 2, __FILE__, __LINE__);
    f2 = true;
    instance->setF2(f2);
    Assert::assertEquals(f2, instance->getF2(), __FILE__, __LINE__);
    Assert::assertEquals("number of messages is 2", 2, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("opcode is OPC_LOCO_DIRF", LnConstants::OPC_LOCO_DIRF, lnis->outbound.at(1)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("sent f2 in correct state", 2, lnis->outbound.at(1)->getElement(2) & 2, __FILE__, __LINE__);
}

/**
 * Test of setF3 method, of class AbstractThrottle.
 */
//@Test
//@Override
/*public*/ void LocoNetThrottleTest::testSetF3() {
    lnis->outbound.clear();
    lnis->resetStatistics();
    bool f3 = false;
    instance->setF3(f3);
    Assert::assertEquals(f3, instance->getF3(), __FILE__, __LINE__);
    Assert::assertEquals("number of messages is 1", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("opcode is OPC_LOCO_DIRF", LnConstants::OPC_LOCO_DIRF, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("sent f2 in correct state", 0, lnis->outbound.at(0)->getElement(2) & 4, __FILE__, __LINE__);
    f3 = true;
    instance->setF3(f3);
    Assert::assertEquals(f3, instance->getF3(), __FILE__, __LINE__);
    Assert::assertEquals("number of messages is 2", 2, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("opcode is OPC_LOCO_DIRF", LnConstants::OPC_LOCO_DIRF, lnis->outbound.at(1)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("sent f3 in correct state", 4, lnis->outbound.at(1)->getElement(2) & 4, __FILE__, __LINE__);
}

/**
 * Test of setF4 method, of class AbstractThrottle.
 */
//@Test
//@Override
/*public*/ void LocoNetThrottleTest::testSetF4() {
    lnis->outbound.clear();
    lnis->resetStatistics();
    bool f4 = false;
    instance->setF4(f4);
    Assert::assertEquals(f4, instance->getF4(), __FILE__, __LINE__);
    Assert::assertEquals("number of messages is 1", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("opcode is OPC_LOCO_DIRF", LnConstants::OPC_LOCO_DIRF, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("sent f4 in correct state", 0, lnis->outbound.at(0)->getElement(2) & 8, __FILE__, __LINE__);
    f4 = true;
    instance->setF4(f4);
    Assert::assertEquals(f4, instance->getF4(), __FILE__, __LINE__);
    Assert::assertEquals("number of messages is 2", 2, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("opcode is OPC_LOCO_DIRF", LnConstants::OPC_LOCO_DIRF, lnis->outbound.at(1)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("sent f4 in correct state", 8, lnis->outbound.at(1)->getElement(2) & 8, __FILE__, __LINE__);
}

/**
 * Test of setF5 method, of class AbstractThrottle.
 */
//@Test
//@Override
/*public*/ void LocoNetThrottleTest::testSetF5() {
    lnis->outbound.clear();
    lnis->resetStatistics();
    bool f5 = false;
    instance->setF5(f5);
    Assert::assertEquals(f5, instance->getF5(), __FILE__, __LINE__);
    Assert::assertEquals("number of messages is 1", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("opcode is OPC_LOCO_SND", LnConstants::OPC_LOCO_SND, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("sent f5 in correct state", 0, lnis->outbound.at(0)->getElement(2) & 1, __FILE__, __LINE__);
    f5 = true;
    instance->setF5(f5);
    Assert::assertEquals(f5, instance->getF5(), __FILE__, __LINE__);
    Assert::assertEquals("number of messages is 2", 2, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("opcode is OPC_LOCO_SND", LnConstants::OPC_LOCO_SND, lnis->outbound.at(1)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("sent f5 in correct state", 1, lnis->outbound.at(1)->getElement(2) & 1, __FILE__, __LINE__);
}

/**
 * Test of setF6 method, of class AbstractThrottle.
 */
//@Test
//@Override
/*public*/ void LocoNetThrottleTest::testSetF6() {
    lnis->outbound.clear();
    lnis->resetStatistics();
    bool f6 = false;
    instance->setF6(f6);
    Assert::assertEquals(f6, instance->getF6(), __FILE__, __LINE__);
    Assert::assertEquals("number of messages is 1", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("opcode is OPC_LOCO_SND", LnConstants::OPC_LOCO_SND, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("sent f6 in correct state", 0, lnis->outbound.at(0)->getElement(2) & 2, __FILE__, __LINE__);
    f6 = true;
    instance->setF6(f6);
    Assert::assertEquals(f6, instance->getF6(), __FILE__, __LINE__);
    Assert::assertEquals("number of messages is 2", 2, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("opcode is OPC_LOCO_SND", LnConstants::OPC_LOCO_SND, lnis->outbound.at(1)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("sent f6 in correct state", 2, lnis->outbound.at(1)->getElement(2) & 2, __FILE__, __LINE__);
}

/**
 * Test of setF7 method, of class AbstractThrottle.
 */
//@Test
//@Override
/*public*/ void LocoNetThrottleTest::testSetF7() {
    lnis->outbound.clear();
    lnis->resetStatistics();
    bool f7 = false;
    instance->setF7(f7);
    Assert::assertEquals(f7, instance->getF7(), __FILE__, __LINE__);
    Assert::assertEquals("number of messages is 1", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("opcode is OPC_LOCO_SND", LnConstants::OPC_LOCO_SND, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("sent f7 in correct state", 0, lnis->outbound.at(0)->getElement(2) & 4, __FILE__, __LINE__);
    f7 = true;
    instance->setF7(f7);
    Assert::assertEquals(f7, instance->getF7(), __FILE__, __LINE__);
    Assert::assertEquals("number of messages is 2", 2, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("opcode is OPC_LOCO_SND", LnConstants::OPC_LOCO_SND, lnis->outbound.at(1)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("sent f7 in correct state", 4, lnis->outbound.at(1)->getElement(2) & 4, __FILE__, __LINE__);
}

/**
 * Test of setF8 method, of class AbstractThrottle.
 */
//@Test
//@Override
/*public*/ void LocoNetThrottleTest::testSetF8() {
    lnis->outbound.clear();
    lnis->resetStatistics();
    bool f8 = false;
    instance->setF8(f8);
    Assert::assertEquals(f8, instance->getF8(), __FILE__, __LINE__);
    Assert::assertEquals("number of messages is 1", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("opcode is OPC_LOCO_SND", LnConstants::OPC_LOCO_SND, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("sent f8 in correct state", 0, lnis->outbound.at(0)->getElement(2) & 8, __FILE__, __LINE__);
    f8 = true;
    instance->setF8(f8);
    Assert::assertEquals(f8, instance->getF8(), __FILE__, __LINE__);
    Assert::assertEquals("number of messages is 2", 2, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("opcode is OPC_LOCO_SND", LnConstants::OPC_LOCO_SND, lnis->outbound.at(1)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("sent f8 in correct state", 8, lnis->outbound.at(1)->getElement(2) & 8, __FILE__, __LINE__);
}

/**
 * Test of setF9 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF9() {
    bool f9 = false;
    instance->setF9(f9);
    Assert::assertEquals(f9, instance->getF9(), __FILE__, __LINE__);
    f9 = true;
    instance->setF9(f9);
    Assert::assertEquals(f9, instance->getF9(), __FILE__, __LINE__);
}

/**
 * Test of setF10 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF10() {
    bool f10 = false;
    instance->setF10(f10);
    Assert::assertEquals(f10, instance->getF10(), __FILE__, __LINE__);
    f10 = true;
    instance->setF10(f10);
    Assert::assertEquals(f10, instance->getF10(), __FILE__, __LINE__);
}

/**
 * Test of setF11 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF11() {
    bool f11 = false;
    instance->setF11(f11);
    Assert::assertEquals(f11, instance->getF11(), __FILE__, __LINE__);
    f11 = true;
    instance->setF11(f11);
    Assert::assertEquals(f11, instance->getF11(), __FILE__, __LINE__);
}

/**
 * Test of setF12 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF12() {
    bool f12 = false;
    instance->setF12(f12);
    Assert::assertEquals(f12, instance->getF12(), __FILE__, __LINE__);
    f12 = true;
    instance->setF12(f12);
    Assert::assertEquals(f12, instance->getF12(), __FILE__, __LINE__);
}

/**
 * Test of setF13 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF13() {
    bool f13 = false;
    instance->setF13(f13);
    Assert::assertEquals(f13, instance->getF13(), __FILE__, __LINE__);
    f13 = true;
    instance->setF13(f13);
    Assert::assertEquals(f13, instance->getF13(), __FILE__, __LINE__);
}

/**
 * Test of setF14 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF14() {
    bool f14 = false;
    instance->setF14(f14);
    Assert::assertEquals(f14, instance->getF14(), __FILE__, __LINE__);
    f14 = true;
    instance->setF14(f14);
    Assert::assertEquals(f14, instance->getF14(), __FILE__, __LINE__);
}

/**
 * Test of setF15 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF15() {
    bool f15 = false;
    instance->setF15(f15);
    Assert::assertEquals(f15, instance->getF15(), __FILE__, __LINE__);
    f15 = true;
    instance->setF15(f15);
    Assert::assertEquals(f15, instance->getF15(), __FILE__, __LINE__);
}

/**
 * Test of setF16 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF16() {
    bool f16 = false;
    instance->setF16(f16);
    Assert::assertEquals(f16, instance->getF16(), __FILE__, __LINE__);
    f16 = true;
    instance->setF16(f16);
    Assert::assertEquals(f16, instance->getF16(), __FILE__, __LINE__);
}

/**
 * Test of setF17 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF17() {
    bool f17 = false;
    instance->setF17(f17);
    Assert::assertEquals(f17, instance->getF17(), __FILE__, __LINE__);
    f17 = true;
    instance->setF17(f17);
    Assert::assertEquals(f17, instance->getF17(), __FILE__, __LINE__);
}

/**
 * Test of setF18 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF18() {
    bool f18 = false;
    instance->setF18(f18);
    Assert::assertEquals(f18, instance->getF18(), __FILE__, __LINE__);
    f18 = true;
    instance->setF18(f18);
    Assert::assertEquals(f18, instance->getF18(), __FILE__, __LINE__);
}

/**
 * Test of setF19 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF19() {
    bool f19 = false;
    instance->setF19(f19);
    Assert::assertEquals(f19, instance->getF19(), __FILE__, __LINE__);
    f19 = true;
    instance->setF19(f19);
    Assert::assertEquals(f19, instance->getF19(), __FILE__, __LINE__);
}

/**
 * Test of setF20 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF20() {
    bool f20 = false;
    instance->setF20(f20);
    Assert::assertEquals(f20, instance->getF20(), __FILE__, __LINE__);
    f20 = true;
    instance->setF20(f20);
    Assert::assertEquals(f20, instance->getF20(), __FILE__, __LINE__);
}

/**
 * Test of setF21 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF21() {
    bool f21 = false;
    instance->setF21(f21);
    Assert::assertEquals(f21, instance->getF21(), __FILE__, __LINE__);
    f21 = true;
    instance->setF21(f21);
    Assert::assertEquals(f21, instance->getF21(), __FILE__, __LINE__);
}

/**
 * Test of setF22 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF22() {
    bool f22 = false;
    instance->setF22(f22);
    Assert::assertEquals(f22, instance->getF22(), __FILE__, __LINE__);
    f22 = true;
    instance->setF22(f22);
    Assert::assertEquals(f22, instance->getF22(), __FILE__, __LINE__);
}

/**
 * Test of setF23 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF23() {
    bool f23 = false;
    instance->setF23(f23);
    Assert::assertEquals(f23, instance->getF23(), __FILE__, __LINE__);
    f23 = true;
    instance->setF23(f23);
    Assert::assertEquals(f23, instance->getF23(), __FILE__, __LINE__);
}

/**
 * Test of setF24 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF24() {
    bool f24 = false;
    instance->setF24(f24);
    Assert::assertEquals(f24, instance->getF24(), __FILE__, __LINE__);
    f24 = true;
    instance->setF24(f24);
    Assert::assertEquals(f24, instance->getF24(), __FILE__, __LINE__);
}

/**
 * Test of setF25 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF25() {
    bool f25 = false;
    instance->setF25(f25);
    Assert::assertEquals(f25, instance->getF25(), __FILE__, __LINE__);
    f25 = true;
    instance->setF25(f25);
    Assert::assertEquals(f25, instance->getF25(), __FILE__, __LINE__);
}

/**
 * Test of setF26 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF26() {
    bool f26 = false;
    instance->setF26(f26);
    Assert::assertEquals(f26, instance->getF26(), __FILE__, __LINE__);
    f26 = true;
    instance->setF26(f26);
    Assert::assertEquals(f26, instance->getF26(), __FILE__, __LINE__);
}

/**
 * Test of setF27 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF27() {
    bool f27 = false;
    instance->setF27(f27);
    Assert::assertEquals(f27, instance->getF27(), __FILE__, __LINE__);
    f27 = true;
    instance->setF27(f27);
    Assert::assertEquals(f27, instance->getF27(), __FILE__, __LINE__);
}

/**
 * Test of setF28 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSetF28() {
    bool f28 = false;
    instance->setF28(f28);
    Assert::assertEquals(f28, instance->getF28(), __FILE__, __LINE__);
    f28 = true;
    instance->setF28(f28);
    Assert::assertEquals(f28, instance->getF28(), __FILE__, __LINE__);
}

/**
 * Test of sendFunctionGroup1 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSendFunctionGroup1() {
    lnis->outbound.clear();
    lnis->resetStatistics();
    instance->setF0(false);
    instance->setF1(true);
    instance->setF2(true);
    instance->setF3(false);
    instance->setIsForward(true);
    lnis->outbound.clear();
    lnis->resetStatistics();
    Assert::assertEquals("check send of function group 1 (0)", 0, lnis->outbound.size(), __FILE__, __LINE__);
    ((LocoNetThrottle*)instance)->sendFunctionGroup1();
    Assert::assertEquals("check send of function group 1 (1)", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("check opcode",LnConstants::OPC_LOCO_DIRF, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("check dirf byte", 0x03, lnis->outbound.at(0)->getElement(2), __FILE__, __LINE__);

    lnis->outbound.clear();
    lnis->resetStatistics();
    instance->setIsForward(false);
    Assert::assertEquals("check send of function group 1 (2)", 1, lnis->outbound.size(), __FILE__, __LINE__);
    ((LocoNetThrottle*)instance)->sendFunctionGroup1();
    Assert::assertEquals("check send of function group 1 (3)", 2, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("check opcode",LnConstants::OPC_LOCO_DIRF, lnis->outbound.at(1)->getOpCode(), __FILE__, __LINE__);
    Assert::assertEquals("check dirf byte {4}", 0x023, lnis->outbound.at(1)->getElement(2), __FILE__, __LINE__);

}

/**
 * Test of sendFunctionGroup2 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSendFunctionGroup2() {

    for (int i = 5; i <9; ++i ) {
        instance->setF5(i==5);
        instance->setF6(i==6);
        instance->setF7(i==7);
        instance->setF8(i==8);
        lnis->outbound.clear();
        lnis->resetStatistics();
        ((LocoNetThrottle*)instance)->sendFunctionGroup2();

        Assert::assertEquals("check send of function group 2 for F"+QString::number(i)+" (0)", 1, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check opcode is OPC_LOCO_SND for F"+QString::number(i)+"",LnConstants::OPC_LOCO_SND, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
        Assert::assertEquals("check byte 2 for F"+QString::number(i)+"{0}", 1<<(i-5), lnis->outbound.at(0)->getElement(2), __FILE__, __LINE__);

        instance->setF5(!(i==5));
        instance->setF6(!(i==6));
        instance->setF7(!(i==7));
        instance->setF8(!(i==8));
        lnis->outbound.clear();
        lnis->resetStatistics();
        ((LocoNetThrottle*)instance)->sendFunctionGroup2();

        Assert::assertEquals("check send of function group 2 for !F"+QString::number(i)+"(1)", 1, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check opcode is OPC_LOCO_SND for F"+QString::number(i)+"",LnConstants::OPC_LOCO_SND, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
        Assert::assertEquals("check byte 2 for !F"+QString::number(i)+"{1}", 0x0f - (1<<(i-5)), lnis->outbound.at(0)->getElement(2), __FILE__, __LINE__);
    }
}

/**
 * Test of sendFunctionGroup3 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSendFunctionGroup3()
{

 for (int i = 9; i <13; ++i )
 {
  instance->setF9(i==9);
  instance->setF10(i==10);
  instance->setF11(i==11);
  instance->setF12(i==12);
  lnis->outbound.clear();
  lnis->resetStatistics();
  ((LocoNetThrottle*)instance)->sendFunctionGroup3();

  Assert::assertEquals("check send of function group 3 for F"+QString::number(i)+" (0)", 1, lnis->outbound.size(), __FILE__, __LINE__);
  Assert::assertEquals("check opcode is OPC_IMM_PACKET for F"+QString::number(i)+"",LnConstants::OPC_IMM_PACKET, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
  Assert::assertEquals("check byte 1 for F"+QString::number(i)+"{0}", 0x0b, lnis->outbound.at(0)->getElement(1), __FILE__, __LINE__);
  Assert::assertEquals("check byte 2 for F"+QString::number(i)+"{0}", 0x7f, lnis->outbound.at(0)->getElement(2), __FILE__, __LINE__);
  Assert::assertEquals("check byte 3 for F"+QString::number(i)+"{0}", 0x23, lnis->outbound.at(0)->getElement(3), __FILE__, __LINE__);
  Assert::assertEquals("check byte 4 for F"+QString::number(i)+"{0}", 0x02, lnis->outbound.at(0)->getElement(4), __FILE__, __LINE__);
  Assert::assertEquals("check byte 5 for F"+QString::number(i)+"{0}", 0x00, lnis->outbound.at(0)->getElement(5), __FILE__, __LINE__);
  Assert::assertEquals("check byte 6 for F"+QString::number(i)+"{0}", 0x20+(1<<(i-9)), lnis->outbound.at(0)->getElement(6), __FILE__, __LINE__);
  Assert::assertEquals("check byte 7 for F"+QString::number(i)+"{0}", 0x00, lnis->outbound.at(0)->getElement(7), __FILE__, __LINE__);
  Assert::assertEquals("check byte 8 for F"+QString::number(i)+"{0}", 0x00, lnis->outbound.at(0)->getElement(8), __FILE__, __LINE__);
  Assert::assertEquals("check byte 9 for F"+QString::number(i)+"{0}", 0x00, lnis->outbound.at(0)->getElement(9), __FILE__, __LINE__);

  instance->setF9(!(i==9));
  instance->setF10(!(i==10));
  instance->setF11(!(i==11));
  instance->setF12(!(i==12));
  lnis->outbound.clear();
  lnis->resetStatistics();
  ((LocoNetThrottle*)instance)->sendFunctionGroup3();

  Assert::assertEquals("check send of function group 3 for !F"+QString::number(i)+"(1)", 1, lnis->outbound.size(), __FILE__, __LINE__);
  Assert::assertEquals("check opcode is OPC_IMM_PACKET for !F"+QString::number(i)+"{1}",LnConstants::OPC_IMM_PACKET, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
  Assert::assertEquals("check byte 1 for !F"+QString::number(i)+"{1}", 0x0b, lnis->outbound.at(0)->getElement(1), __FILE__, __LINE__);
  Assert::assertEquals("check byte 2 for !F"+QString::number(i)+"{1}", 0x7f, lnis->outbound.at(0)->getElement(2), __FILE__, __LINE__);
  Assert::assertEquals("check byte 3 for !F"+QString::number(i)+"{1}", 0x23, lnis->outbound.at(0)->getElement(3), __FILE__, __LINE__);
  Assert::assertEquals("check byte 4 for !F"+QString::number(i)+"{1}", 0x02, lnis->outbound.at(0)->getElement(4), __FILE__, __LINE__);
  Assert::assertEquals("check byte 5 for !F"+QString::number(i)+"{1}", 0x00, lnis->outbound.at(0)->getElement(5), __FILE__, __LINE__);
  Assert::assertEquals("check byte 6 for !F"+QString::number(i)+"{1}", 0x2F-(1<<(i-9)), lnis->outbound.at(0)->getElement(6), __FILE__, __LINE__);
  Assert::assertEquals("check byte 7 for !F"+QString::number(i)+"{1}", 0x00, lnis->outbound.at(0)->getElement(7), __FILE__, __LINE__);
  Assert::assertEquals("check byte 8 for !F"+QString::number(i)+"{1}", 0x00, lnis->outbound.at(0)->getElement(8), __FILE__, __LINE__);
  Assert::assertEquals("check byte 9 for 1F"+QString::number(i)+"{1}", 0x00, lnis->outbound.at(0)->getElement(9), __FILE__, __LINE__);
 }
}

/**
 * Test of sendFunctionGroup4 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSendFunctionGroup4() {
    for (int i = 13; i <21; ++i ) {
        instance->setF13(i==13);
        instance->setF14(i==14);
        instance->setF15(i==15);
        instance->setF16(i==16);
        instance->setF17(i==17);
        instance->setF18(i==18);
        instance->setF19(i==19);
        instance->setF20(i==20);
        lnis->outbound.clear();
        lnis->resetStatistics();
        ((LocoNetThrottle*)instance)->sendFunctionGroup4();

        Assert::assertEquals("check send of function group 4 for F"+QString::number(i)+" (0)", 1, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check opcode is OPC_IMM_PACKET for F"+QString::number(i)+"",LnConstants::OPC_IMM_PACKET, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
        Assert::assertEquals("check byte 1 for F"+QString::number(i)+"{0}", 0x0b, lnis->outbound.at(0)->getElement(1), __FILE__, __LINE__);
        Assert::assertEquals("check byte 2 for F"+QString::number(i)+"{0}", 0x7f, lnis->outbound.at(0)->getElement(2), __FILE__, __LINE__);
        Assert::assertEquals("check byte 3 for F"+QString::number(i)+"{0}", 0x33, lnis->outbound.at(0)->getElement(3), __FILE__, __LINE__);
        Assert::assertEquals("check byte 4 for F"+QString::number(i)+"{0}", (i==20)?0x06:0x02, lnis->outbound.at(0)->getElement(4), __FILE__, __LINE__);
        Assert::assertEquals("check byte 5 for F"+QString::number(i)+"{0}", 0x00, lnis->outbound.at(0)->getElement(5), __FILE__, __LINE__);
        Assert::assertEquals("check byte 6 for F"+QString::number(i)+"{0}", 0x5e, lnis->outbound.at(0)->getElement(6), __FILE__, __LINE__);
        Assert::assertEquals("check byte 7 for F"+QString::number(i)+"{0}", (i < 20)?(1<<(i-13)):0, lnis->outbound.at(0)->getElement(7), __FILE__, __LINE__);
        Assert::assertEquals("check byte 8 for F"+QString::number(i)+"{0}", 0x00, lnis->outbound.at(0)->getElement(8), __FILE__, __LINE__);
        Assert::assertEquals("check byte 9 for F"+QString::number(i)+"{0}", 0x00, lnis->outbound.at(0)->getElement(9), __FILE__, __LINE__);

        instance->setF13(!(i==13));
        instance->setF14(!(i==14));
        instance->setF15(!(i==15));
        instance->setF16(!(i==16));
        instance->setF17(!(i==17));
        instance->setF18(!(i==18));
        instance->setF19(!(i==19));
        instance->setF20(!(i==20));
        lnis->outbound.clear();
        lnis->resetStatistics();
        ((LocoNetThrottle*)instance)->sendFunctionGroup4();

        Assert::assertEquals("check send of function group 4 for !F"+QString::number(i)+"(1)", 1, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check opcode is OPC_IMM_PACKET for !F"+QString::number(i)+"{1}",LnConstants::OPC_IMM_PACKET, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
        Assert::assertEquals("check byte 1 for !F"+QString::number(i)+"{1}", 0x0b, lnis->outbound.at(0)->getElement(1), __FILE__, __LINE__);
        Assert::assertEquals("check byte 2 for !F"+QString::number(i)+"{1}", 0x7f, lnis->outbound.at(0)->getElement(2), __FILE__, __LINE__);
        Assert::assertEquals("check byte 3 for !F"+QString::number(i)+"{1}", 0x33, lnis->outbound.at(0)->getElement(3), __FILE__, __LINE__);
        Assert::assertEquals("check byte 4 for !F"+QString::number(i)+"{1}", (i==20)?0x02:0x06, lnis->outbound.at(0)->getElement(4), __FILE__, __LINE__);
        Assert::assertEquals("check byte 5 for !F"+QString::number(i)+"{1}", 0x00, lnis->outbound.at(0)->getElement(5), __FILE__, __LINE__);
        Assert::assertEquals("check byte 6 for !F"+QString::number(i)+"{1}", 0x5e, lnis->outbound.at(0)->getElement(6), __FILE__, __LINE__);
        Assert::assertEquals("check byte 7 for !F"+QString::number(i)+"{1}", (i < 20)?(127-(1<<(i-13))):0x7f, lnis->outbound.at(0)->getElement(7), __FILE__, __LINE__);
        Assert::assertEquals("check byte 8 for !F"+QString::number(i)+"{1}", 0x00, lnis->outbound.at(0)->getElement(8), __FILE__, __LINE__);
        Assert::assertEquals("check byte 9 for 1F"+QString::number(i)+"{1}", 0x00, lnis->outbound.at(0)->getElement(9), __FILE__, __LINE__);
    }
}

/**
 * Test of sendFunctionGroup5 method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testSendFunctionGroup5() {
    for (int i = 21; i <29; ++i ) {
        instance->setF21(i==21);
        instance->setF22(i==22);
        instance->setF23(i==23);
        instance->setF24(i==24);
        instance->setF25(i==25);
        instance->setF26(i==26);
        instance->setF27(i==27);
        instance->setF28(i==28);
        lnis->outbound.clear();
        lnis->resetStatistics();
        ((LocoNetThrottle*)instance)->sendFunctionGroup5();

        Assert::assertEquals("check send of function group 5 for F"+QString::number(i)+" (0)", 1, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check opcode is OPC_IMM_PACKET for F"+QString::number(i)+"",LnConstants::OPC_IMM_PACKET, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
        Assert::assertEquals("check byte 1 for F"+QString::number(i)+"{0}", 0x0b, lnis->outbound.at(0)->getElement(1), __FILE__, __LINE__);
        Assert::assertEquals("check byte 2 for F"+QString::number(i)+"{0}", 0x7f, lnis->outbound.at(0)->getElement(2), __FILE__, __LINE__);
        Assert::assertEquals("check byte 3 for F"+QString::number(i)+"{0}", 0x33, lnis->outbound.at(0)->getElement(3), __FILE__, __LINE__);
        Assert::assertEquals("check byte 4 for F"+QString::number(i)+"{0}", (i==28)?0x06:0x02, lnis->outbound.at(0)->getElement(4), __FILE__, __LINE__);
        Assert::assertEquals("check byte 5 for F"+QString::number(i)+"{0}", 0x00, lnis->outbound.at(0)->getElement(5), __FILE__, __LINE__);
        Assert::assertEquals("check byte 6 for F"+QString::number(i)+"{0}", 0x5f, lnis->outbound.at(0)->getElement(6), __FILE__, __LINE__);
        Assert::assertEquals("check byte 7 for F"+QString::number(i)+"{0}", (i < 28)?(1<<(i-21)):0, lnis->outbound.at(0)->getElement(7), __FILE__, __LINE__);
        Assert::assertEquals("check byte 8 for F"+QString::number(i)+"{0}", 0x00, lnis->outbound.at(0)->getElement(8), __FILE__, __LINE__);
        Assert::assertEquals("check byte 9 for F"+QString::number(i)+"{0}", 0x00, lnis->outbound.at(0)->getElement(9), __FILE__, __LINE__);

        instance->setF21(!(i==21));
        instance->setF22(!(i==22));
        instance->setF23(!(i==23));
        instance->setF24(!(i==24));
        instance->setF25(!(i==25));
        instance->setF26(!(i==26));
        instance->setF27(!(i==27));
        instance->setF28(!(i==28));
        lnis->outbound.clear();
        lnis->resetStatistics();
        ((LocoNetThrottle*)instance)->sendFunctionGroup5();

        Assert::assertEquals("check send of function group 5 for !F"+QString::number(i)+"(1)", 1, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check opcode is OPC_IMM_PACKET for !F"+QString::number(i)+"{1}",LnConstants::OPC_IMM_PACKET, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
        Assert::assertEquals("check byte 1 for !F"+QString::number(i)+"{1}", 0x0b, lnis->outbound.at(0)->getElement(1), __FILE__, __LINE__);
        Assert::assertEquals("check byte 2 for !F"+QString::number(i)+"{1}", 0x7f, lnis->outbound.at(0)->getElement(2), __FILE__, __LINE__);
        Assert::assertEquals("check byte 3 for !F"+QString::number(i)+"{1}", 0x33, lnis->outbound.at(0)->getElement(3), __FILE__, __LINE__);
        Assert::assertEquals("check byte 4 for !F"+QString::number(i)+"{1}", (i==28)?0x02:0x06, lnis->outbound.at(0)->getElement(4), __FILE__, __LINE__);
        Assert::assertEquals("check byte 5 for !F"+QString::number(i)+"{1}", 0x00, lnis->outbound.at(0)->getElement(5), __FILE__, __LINE__);
        Assert::assertEquals("check byte 6 for !F"+QString::number(i)+"{1}", 0x5f, lnis->outbound.at(0)->getElement(6), __FILE__, __LINE__);
        Assert::assertEquals("check byte 7 for !F"+QString::number(i)+"{1}", (i < 28)?(127-(1<<(i-21))):0x7f, lnis->outbound.at(0)->getElement(7), __FILE__, __LINE__);
        Assert::assertEquals("check byte 8 for !F"+QString::number(i)+"{1}", 0x00, lnis->outbound.at(0)->getElement(8), __FILE__, __LINE__);
        Assert::assertEquals("check byte 9 for 1F"+QString::number(i)+"{1}", 0x00, lnis->outbound.at(0)->getElement(9), __FILE__, __LINE__);

    }
}

/**
 * Test of getF2Momentary method, of class AbstractThrottle.
 */
//@Test
//@Overide
/*public*/ void LocoNetThrottleTest::testGetF2Momentary() {
    bool expResult = true;
    bool result = instance->getF2Momentary();
    Assert::assertEquals("Check F2 Momentary true", expResult, result, __FILE__, __LINE__);

    expResult = false;
    instance->setF2Momentary(false);
    result = instance->getF2Momentary();
    Assert::assertEquals("Check F2 Momentary false", expResult, result, __FILE__, __LINE__);

}


// The minimal setup for log4J
//@Before
//@Overide
/*public*/ void LocoNetThrottleTest::setUp() throw (Exception) {
    JUnitUtil::setUp();
    // prepare an interface
    lnis = new LocoNetInterfaceScaffold();
    slotmanager = new SlotManager(lnis);

    // set slot 3 to address 3
    LocoNetMessage* m = new LocoNetMessage(13);
    m->setOpCode(LnConstants::OPC_WR_SL_DATA);
    m->setElement(1, 0x0E);
    m->setElement(2, 0x03);
    m->setElement(4, 0x03);
    slotmanager->slot(3)->setSlot(m);

    // set slot 4 to address 255
    m->setElement(2, 0x04);
    m->setElement(4, 0x7F);
    m->setElement(9, 0x01);
    slotmanager->slot(4)->setSlot(m);

    memo = new LocoNetSystemConnectionMemo(lnis, slotmanager);
    memo->setThrottleManager(new LnThrottleManager(memo));
    InstanceManager::setDefault("ThrottleManager", memo->getThrottleManager());

    instance = new LocoNetThrottle(memo, new LocoNetSlot(0));
}

//@After
//@Override
/*public*/ void LocoNetThrottleTest::tearDown() throw (Exception){
    ((LnThrottleManager*)memo->getThrottleManager())->dispose();
    memo->dispose();
    lnis = nullptr;
    JUnitUtil::tearDown();
}
