#include "lnsensoraddresstest.h"
#include "assert1.h"
#include "lnsensoraddress.h"
#include "loggerfactory.h"
#include "junitutil.h"

LnSensorAddressTest::LnSensorAddressTest(QObject *parent) : QObject(parent)
{

}

/**
* Tests for the jmri.jmrix.loconet.LnSensorAddress* class.
*
* @author	Bob Jacobsen Copyright 2001, 2002
*/
///*public*/ class LnSensorAddressTest {

 //@Test
 /*public*/ void LnSensorAddressTest::testLnSensorAddressCreate() {
     LnSensorAddress* a1 = new LnSensorAddress("LS001", "L");
     LnSensorAddress* a2 = new LnSensorAddress("LS001A", "L");
     LnSensorAddress* a3 = new LnSensorAddress("LS001C3", "L");
     LnSensorAddress* a4 = new LnSensorAddress(0x15, 0x60, "L"); // LS043
     Assert::assertNotNull("exists", a1, __FILE__, __LINE__);
     Assert::assertNotNull("exists", a2, __FILE__, __LINE__);
     Assert::assertNotNull("exists", a3, __FILE__, __LINE__);
     Assert::assertNotNull("exists", a4, __FILE__, __LINE__);
 }

 //@Test
 /*public*/ void LnSensorAddressTest::testLnSensorInvalid() {
     LnSensorAddress* a;
     a = new LnSensorAddressO1("foo", "L", this);
//     {
//         @Override
//         void reportParseError(String s) {
//         }
//     };
     Assert::assertTrue(!a->isValid(), __FILE__, __LINE__);
 }

 //@Test
 /*public*/ void LnSensorAddressTest::testLnSensorAddressASmode() {
     LnSensorAddress* a;

     a = new LnSensorAddress("LS130A", "L");
     Assert::assertTrue(a->getLowBits() == 2, __FILE__, __LINE__);
     Assert::assertTrue(a->getHighBits() == 1, __FILE__, __LINE__);
     Assert::assertEquals("AS bit from LS130A", 0x20, a->getASBit(), __FILE__, __LINE__);
     Assert::assertTrue(a->isValid(), __FILE__, __LINE__);

     a = new LnSensorAddress("LS257S", "L");
     Assert::assertTrue(a->getLowBits() == 1, __FILE__, __LINE__);
     Assert::assertTrue(a->getHighBits() == 2, __FILE__, __LINE__);
     Assert::assertTrue(a->getASBit() == 0x00, __FILE__, __LINE__);
     Assert::assertTrue(a->isValid(), __FILE__, __LINE__);
 }

 //@Test
 /*public*/ void LnSensorAddressTest::testLnSensorAddressNumericMode() {
     LnSensorAddress* a;

     a = new LnSensorAddress("LS130A2", "L"); // 0x0822
     Assert::assertTrue(a->getLowBits() == 17, __FILE__, __LINE__);
     Assert::assertTrue(a->getHighBits() == 16, __FILE__, __LINE__);
     Assert::assertTrue(a->getASBit() == 0x00, __FILE__, __LINE__);
     Assert::assertTrue(a->isValid(), __FILE__, __LINE__);

     a = new LnSensorAddress("LS257D3", "L");  // 0x101F
     Assert::assertTrue(a->getLowBits() == 15, __FILE__, __LINE__);
     Assert::assertTrue(a->getHighBits() == 32, __FILE__, __LINE__);
     Assert::assertEquals("AS bit from LS257D3", 0x20, a->getASBit(), __FILE__, __LINE__);
     Assert::assertTrue(a->isValid(), __FILE__, __LINE__);
 }

 //@Test
 /*public*/ void LnSensorAddressTest::testLnSensorAddressBDL16Mode() {
     LnSensorAddress* a;

     a = new LnSensorAddress("LS131", "L");
     Assert::assertTrue(a->getLowBits() == 65, __FILE__, __LINE__);
     Assert::assertTrue(a->getHighBits() == 0, __FILE__, __LINE__);
     Assert::assertTrue(a->getASBit() == 0x00, __FILE__, __LINE__);
     Assert::assertTrue(a->isValid(), __FILE__, __LINE__);

     a = new LnSensorAddress("LS258", "L");
     Assert::assertTrue(a->getLowBits() == 0, __FILE__, __LINE__);
     Assert::assertTrue(a->getHighBits() == 1, __FILE__, __LINE__);
     Assert::assertEquals("AS bit from LS258", 0x20, a->getASBit(), __FILE__, __LINE__);
     Assert::assertTrue(a->isValid(), __FILE__, __LINE__);
 }

 //@Test
 /*public*/ void LnSensorAddressTest::testLnSensorAddressFromPacket() {
     LnSensorAddress* a;

     a = new LnSensorAddress(0x15, 0x60, "L"); // LS044
     log->debug("0x15, 0x60 shows as " + a->getNumericAddress() + " "
             + a->getDS54Address() + " " + a->getBDL16Address());
     Assert::assertTrue(a->getNumericAddress() == ("LS44"), __FILE__, __LINE__);
     Assert::assertTrue(a->getDS54Address()== ("LS21A"), __FILE__, __LINE__);
     Assert::assertTrue(a->getBDL16Address() ==("LS2C3"), __FILE__, __LINE__);

 }

 // The minimal setup for log4J
 //@Before
 /*public*/ void LnSensorAddressTest::setUp() {
     JUnitUtil::setUp();
 }

 //@After
 /*public*/ void LnSensorAddressTest::tearDown() {
     JUnitUtil::tearDown();
 }


/*private*/ /*final*/ /*static*/ Logger* LnSensorAddressTest::log = LoggerFactory::getLogger("LnSensorAddressTest");
