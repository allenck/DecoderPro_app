#include "lncvdevicetest.h"
#include "junitutil.h"
#include "assert1.h"
#include "lncvdevice.h"
#include "loconetsystemconnectionmemo.h"
#include "instancemanager.h"

LncvDeviceTest::LncvDeviceTest(QObject *parent) : QObject(parent)
{

}
//class LncvDeviceTest {


    //@Test
    /*public*/ void LncvDeviceTest::testCTor() {
        LncvDevice* ld1 = new LncvDevice(5000, 1, 0, 1, "Test", "R_Test", 1);
        Assert::assertNotNull("LncvDeviceManager exists", ld1, __FILE__, __LINE__);
    }

    //@Test
    void LncvDeviceTest::testGetProductID() {
        Assert::assertEquals("get productID", 1111, lncvd->getProductID(), __FILE__, __LINE__);
    }

    //@Test
    void LncvDeviceTest::testGetDestAddr() {
        Assert::assertEquals("get module address", 8, lncvd->getDestAddr(), __FILE__, __LINE__);
    }

    //@Test
    void LncvDeviceTest::testSetDestAddr() {
        lncvd->setDestAddr(14);
        Assert::assertEquals("set module address", 14, lncvd->getDestAddr(), __FILE__, __LINE__);
    }

    //@Test
    void LncvDeviceTest::testGetCvNum() {
        Assert::assertEquals("get last cv num", 4, lncvd->getCvNum(), __FILE__, __LINE__);
    }

    //@Test
    void LncvDeviceTest::testSetCvNum() {
        lncvd->setCvNum(68);
        Assert::assertEquals("set last cv num", 68, lncvd->getCvNum(), __FILE__, __LINE__);
    }

    //@Test
    void LncvDeviceTest::testGetCvValue() {
        Assert::assertEquals("get cv value read", 16, lncvd->getCvValue(), __FILE__, __LINE__);
    }

    //@Test
    void LncvDeviceTest::testSetCvValue() {
        lncvd->setCvValue(33);
        Assert::assertEquals("get module address", 33, lncvd->getCvValue(), __FILE__, __LINE__);
    }

    //@BeforeEach
    /*public*/ void LncvDeviceTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        LocoNetSystemConnectionMemo* memo = new LocoNetSystemConnectionMemo();
        InstanceManager::setDefault("LocoNetSystemConnectionMemo", memo);
        lncvd = new LncvDevice(1111, 8, 4, 16, "LncvMod_8", "Decoder_8", 2);

    }

    //@AfterEach
    /*public*/ void LncvDeviceTest::tearDown() {
        JUnitUtil::tearDown();
    }
