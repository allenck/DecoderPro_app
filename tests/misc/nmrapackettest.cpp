#include "nmrapackettest.h"
#include "junitutil.h"
#include "assert1.h"
#include "nmrapacket.h"
#include "junitappender.h"

NmraPacketTest::NmraPacketTest(QObject *parent) : QObject(parent)
{

}
///*public*/ class NmraPacketTest {

// output values for some of these tests were provided by Bob Scheffler
// create an accessory decoder packet
//@Test
/*public*/ void NmraPacketTest::testAccDecoderPacket1() {
    // test fixed bits
    QByteArray ba = NmraPacket::accDecoderPkt(1, 0, 0);
    Assert::assertEquals("first byte ", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0xF0, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x71, ba[2] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPacket2() {
    // test C bit
    QByteArray ba = NmraPacket::accDecoderPkt(1, 1, 0);
    Assert::assertEquals("first byte ", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0xF8, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x79, ba[2] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPacket3() {
    // test D bits
    QByteArray ba = NmraPacket::accDecoderPkt(1, 0, 7);
    Assert::assertEquals("first byte ", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0xF7, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x76, ba[2] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPacket4() {
    // test short part of address
    QByteArray ba = NmraPacket::accDecoderPkt(3, 0, 0);
    Assert::assertEquals("first byte ", 0x83, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0xF0, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x73, ba[2] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPacket5() {
    // test top part of address
    QByteArray ba = NmraPacket::accDecoderPkt(128, 0, 0);
    Assert::assertEquals("first byte ", 0x80, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0xD0, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x50, ba[2] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPacket6() {
    // "typical packet" test
    QByteArray ba = NmraPacket::accDecoderPkt(33, 1, 5);
    Assert::assertEquals("first byte ", 0xA1, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0xFD, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x5C, ba[2] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPacket7() {
    // address 256
    QByteArray ba = NmraPacket::accDecoderPkt(256, true);
    Assert::assertEquals("first byte ", 0x80, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0xEF, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x6F, ba[2] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPacket8() {
    // address 257
    QByteArray ba = NmraPacket::accDecoderPkt(257, true);
    Assert::assertEquals("first byte ", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0xE9, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x68, ba[2] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPacket9() {
    // address 512
    QByteArray ba = NmraPacket::accDecoderPkt(512, true);
    Assert::assertEquals("first byte ", 0x80, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0xDF, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x5F, ba[2] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPacket10() {
    // address 513
    QByteArray ba = NmraPacket::accDecoderPkt(513, true);
    Assert::assertEquals("first byte ", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0xD9, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x58, ba[2] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPacket11() {
    // address 1024
    QByteArray ba = NmraPacket::accDecoderPkt(1024, true);
    Assert::assertEquals("first byte ", 0x80, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0xBF, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x3F, ba[2] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPacket12() {
    // address 1025
    QByteArray ba = NmraPacket::accDecoderPkt(1025, true);
    Assert::assertEquals("first byte ", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0xB9, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x38, ba[2] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPacket13() {
    // invalid address (0)
    int addr = 0;
    // expect this to throw exception
    bool threw = false;
    try {
        NmraPacket::accDecoderPkt(addr, 0, 0);
        Assert::fail("Expected IllegalArgumentException not thrown", __FILE__, __LINE__);
    } catch (IllegalArgumentException ex) {
        threw = true;
    }
//    finally {
//        JUnitAppender::assertErrorMessage("invalid address " + addr, __FILE__, __LINE__);
//    }
    Assert::assertTrue("Expected exception", threw, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testOpsModeLong() {
    // "typical packet" test
    QByteArray ba = NmraPacket::opsCvWriteByte(2065, true, 21, 75);
    Assert::assertEquals("first byte ", 0xC8, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0x11, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0xEC, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fourth byte ", 0x14, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fifth byte ", 0x4B, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("sixth byte ", 0x6A, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testOpsModeShort() {
    // "typical packet" test
    QByteArray ba = NmraPacket::opsCvWriteByte(65, false, 21, 75);
    Assert::assertEquals("first byte ", 0x41, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0xEC, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x14, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fourth byte ", 0x4B, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fifth byte ", 0xF2, ba[4] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAnalog1() {
    // "typical packet" test
    QByteArray ba = NmraPacket::analogControl(60, false, 1, 00);
    Assert::assertEquals("first byte ", 0x3C, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0x3D, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x01, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fourth byte ", 0x00, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fifth byte ", 0x3C ^ 0x3D ^ 0x01, ba[4] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAnalog2() {
    // "typical packet" test
    QByteArray ba = NmraPacket::analogControl(60, false, 1, 12);
    Assert::assertEquals("first byte ", 0x3C, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0x3D, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x01, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fourth byte ", 0x0C, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fifth byte ", 0x3C ^ 0x3D ^ 0x01 ^ 0x0C, ba[4] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testF13F20A() {
    // "typical packet" test, short address
    QByteArray ba = NmraPacket::function13Through20Packet(60, false, true, false, true, false, true, false, true, false);
    Assert::assertEquals("first byte ", 0x3C, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0xDE, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x55, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fourth byte ", 0x3C ^ 0xDE ^ 0x55, ba[3] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testF13F20B() {
    // "typical packet" test, long address
    QByteArray ba = NmraPacket::function13Through20Packet(2065, true, true, false, true, false, true, false, true, false);
    Assert::assertEquals("first byte ", 0xC8, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0x11, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0xDE, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fourth byte ", 0x55, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fifth byte ", 0xC8 ^ 0x11 ^ 0xDE ^ 0x55, ba[4] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testF21F28A() {
    // "typical packet" test, short address
    QByteArray ba = NmraPacket::function21Through28Packet(60, false, true, false, true, false, true, false, true, false);
    Assert::assertEquals("first byte ", 0x3C, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0xDF, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x55, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fourth byte ", 0x3C ^ 0xDF ^ 0x55, ba[3] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testF21F28B() {
    // "typical packet" test, long address
    QByteArray ba = NmraPacket::function21Through28Packet(2065, true, true, false, true, false, true, false, true, false);
    Assert::assertEquals("first byte ", 0xC8, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0x11, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0xDF, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fourth byte ", 0x55, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fifth byte ", 0xC8 ^ 0x11 ^ 0xDF ^ 0x55, ba[4] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testConsist1() {
    // "typical packet" test
    QByteArray ba = NmraPacket::consistControl(60, false, 1, true);
    Assert::assertEquals("first byte ", 0x3C, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0x12, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x01, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fourth byte ", 0x3C ^ 0x12 ^ 0x01, ba[3] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testConsist2() {
    // "typical packet" test
    QByteArray ba = NmraPacket::consistControl(2065, true, 12, false);
    Assert::assertEquals("first byte ", 0xC8, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0x11, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x13, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fourth byte ", 0x0C, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fifth byte ", 0xC8 ^ 0x11 ^ 0x13 ^ 0x0C, ba[4] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testConsist3() {
    // "typical packet" test
    QByteArray ba = NmraPacket::consistControl(2065, true, 0, false);
    Assert::assertEquals("first byte ", 0xC8, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("second byte ", 0x11, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("third byte ", 0x13, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fourth byte ", 0x00, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("fifth byte ", 0xC8 ^ 0x11 ^ 0x13 ^ 0x00, ba[4] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccSignalDecoderPktOK() {
    QByteArray ba = NmraPacket::accSignalDecoderPkt(123, 12);
    Assert::assertTrue(NmraPacket::isAccSignalDecoderPkt(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccSignalDecoderPktFalseConsist() {
    QByteArray ba = NmraPacket::consistControl(2065, true, 0, false);
    Assert::assertFalse(NmraPacket::isAccSignalDecoderPkt(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccSignalDecoderPktFalseFunction() {
    QByteArray ba = NmraPacket::function21Through28Packet(2065, true, true, false, true, false, true, false, true, false);
    Assert::assertFalse(NmraPacket::isAccSignalDecoderPkt(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccSignalDecoderPktFalseAnalog() {
    QByteArray ba = NmraPacket::analogControl(60, false, 1, 12);
    Assert::assertFalse(NmraPacket::isAccSignalDecoderPkt(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccSignalDecoderPktFalseOpsWrite() {
    QByteArray ba = NmraPacket::opsCvWriteByte(65, false, 21, 75);
    Assert::assertFalse(NmraPacket::isAccSignalDecoderPkt(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccSignalDecoderPktFalseAccDecoder() {
    QByteArray ba = NmraPacket::accDecoderPkt(257, true);
    Assert::assertFalse(NmraPacket::isAccSignalDecoderPkt(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccSignalDecoderPktFalseAccDecoderPktOpsMode() {
    QByteArray ba = NmraPacket::accDecoderPktOpsMode(257, 33, 5);
    Assert::assertFalse(NmraPacket::isAccSignalDecoderPkt(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccSignalDecoderPktFalseAccDecoderPktOpsModeLegacy() {
    QByteArray ba = NmraPacket::accDecoderPktOpsModeLegacy(1843, 384, 255);
    Assert::assertFalse(NmraPacket::isAccSignalDecoderPkt(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccDecoderPktOpsModeFalseSignalDecoderPkt() {
    QByteArray ba = NmraPacket::accSignalDecoderPkt(123, 12);
    Assert::assertFalse(NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccDecoderPktOpsModeFalseConsist() {
    QByteArray ba = NmraPacket::consistControl(2065, true, 0, false);
    Assert::assertFalse(NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccDecoderPktOpsModeFalseFunction() {
    QByteArray ba = NmraPacket::function21Through28Packet(2065, true, true, false, true, false, true, false, true, false);
    Assert::assertFalse(NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccDecoderPktOpsModeFalseAnalog() {
    QByteArray ba = NmraPacket::analogControl(60, false, 1, 12);
    Assert::assertFalse(NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccDecoderPktOpsModeFalseOpsWrite() {
    QByteArray ba = NmraPacket::opsCvWriteByte(65, false, 21, 75);
    Assert::assertFalse(NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccDecoderPktOpsModeFalseAccDecoder() {
    QByteArray ba = NmraPacket::accDecoderPkt(257, true);
    Assert::assertFalse(NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccDecoderPktOpsModeOK() {
    QByteArray ba = NmraPacket::accDecoderPktOpsMode(257, 33, 5);
    Assert::assertTrue(NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccDecoderPktOpsModeFalseAccDecoderPktOpsModeLegacy() {
    QByteArray ba = NmraPacket::accDecoderPktOpsModeLegacy(1843, 384, 255);
    Assert::assertFalse(NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccDecoderPktOpsModeLegacyFalseSignalDecoderPkt() {
    QByteArray ba = NmraPacket::accSignalDecoderPkt(123, 12);
    Assert::assertFalse(NmraPacket::isAccDecoderPktOpsModeLegacy(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccDecoderPktOpsModeLegacyFalseConsist() {
    QByteArray ba = NmraPacket::consistControl(2065, true, 0, false);
    Assert::assertFalse(NmraPacket::isAccDecoderPktOpsModeLegacy(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccDecoderPktOpsModeLegacyFalseFunction() {
    QByteArray ba = NmraPacket::function21Through28Packet(2065, true, true, false, true, false, true, false, true, false);
    Assert::assertFalse(NmraPacket::isAccDecoderPktOpsModeLegacy(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccDecoderPktOpsModeLegacyFalseAnalog() {
    QByteArray ba = NmraPacket::analogControl(60, false, 1, 12);
    Assert::assertFalse(NmraPacket::isAccDecoderPktOpsModeLegacy(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccDecoderPktOpsModeLegacyFalseOpsWrite() {
    QByteArray ba = NmraPacket::opsCvWriteByte(65, false, 21, 75);
    Assert::assertFalse(NmraPacket::isAccDecoderPktOpsModeLegacy(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccDecoderPktOpsModeLegacyFalseAccDecoder() {
    QByteArray ba = NmraPacket::accDecoderPkt(257, true);
    Assert::assertFalse(NmraPacket::isAccDecoderPktOpsModeLegacy(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccDecoderPktOpsModeLegacyFalseAccDecoderPktOpsMode() {
    QByteArray ba = NmraPacket::accDecoderPktOpsMode(257, 33, 5);
    Assert::assertFalse(NmraPacket::isAccDecoderPktOpsModeLegacy(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testIsAccDecoderPktOpsModeLegacyOK() {
    QByteArray ba = NmraPacket::accDecoderPktOpsModeLegacy(1843, 384, 255);
    Assert::assertTrue(NmraPacket::isAccDecoderPktOpsModeLegacy(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testGetAccSignalDecoderPktAddr1() {
    int addr = 1;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(addr, 12);
    Assert::assertEquals(addr, NmraPacket::getAccSignalDecoderPktAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testGetAccSignalDecoderPktAddr2() {
    int addr = 2;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(addr, 12);
    Assert::assertEquals(addr, NmraPacket::getAccSignalDecoderPktAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testGetAccSignalDecoderPktAddr4() {
    int addr = 4;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(addr, 12);
    Assert::assertEquals(addr, NmraPacket::getAccSignalDecoderPktAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testGetAccSignalDecoderPktAddr8() {
    int addr = 8;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(addr, 12);
    Assert::assertEquals(addr, NmraPacket::getAccSignalDecoderPktAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testGetAccSignalDecoderPktAddr16() {
    int addr = 16;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(addr, 12);
    Assert::assertEquals(addr, NmraPacket::getAccSignalDecoderPktAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testGetAccSignalDecoderPktAddr32() {
    int addr = 32;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(addr, 12);
    Assert::assertEquals(addr, NmraPacket::getAccSignalDecoderPktAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testGetAccSignalDecoderPktAddr64() {
    int addr = 64;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(addr, 12);
    Assert::assertEquals(addr, NmraPacket::getAccSignalDecoderPktAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testGetAccSignalDecoderPktAddr128() {
    int addr = 128;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(addr, 12);
    Assert::assertEquals(addr, NmraPacket::getAccSignalDecoderPktAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testGetAccSignalDecoderPktAddr256() {
    int addr = 256;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(addr, 12);
    Assert::assertEquals(addr, NmraPacket::getAccSignalDecoderPktAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testGetAccSignalDecoderPktAddr512() {
    int addr = 512;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(addr, 12);
    Assert::assertEquals(addr, NmraPacket::getAccSignalDecoderPktAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testGetAccSignalDecoderPktAddr1024() {
    int addr = 1024;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(addr, 12);
    Assert::assertEquals(addr, NmraPacket::getAccSignalDecoderPktAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testGetAccSignalDecoderPktAddr2044() { // max valid value
    int addr = 2044;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(addr, 12);
    Assert::assertEquals(addr, NmraPacket::getAccSignalDecoderPktAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecPktOpsModeLegacy1() {
    int address = 1;
    int cv = 29;
    int data = 136;
    QByteArray ba = NmraPacket::accDecPktOpsModeLegacy(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 5, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x7C, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x1C, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x88, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x69, ba[4] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsModeLegacy(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of decoder address", address, NmraPacket::getAccDecPktOpsModeLegacyAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecPktOpsMode1() {
    int address = 1;
    int cv = 29;
    int data = 136;
    QByteArray ba = NmraPacket::accDecPktOpsMode(address, cv, data);

    // the following values based on NCE Power Pro output adjusted for CDDD=0000
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0xF0, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEC, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x1C, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x88, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x09, ba[5] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of decoder address", address, NmraPacket::getAccDecPktOpsModeAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecPktOpsModeLegacy2() {
    int address = 2;
    int cv = 41;
    int data = 24;
    QByteArray ba = NmraPacket::accDecPktOpsModeLegacy(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 5, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x82, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x7C, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x28, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x18, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xCE, ba[4] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsModeLegacy(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of decoder address", address, NmraPacket::getAccDecPktOpsModeLegacyAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecPktOpsMode2() {
    int address = 2;
    int cv = 41;
    int data = 24;
    QByteArray ba = NmraPacket::accDecPktOpsMode(address, cv, data);

    // the following values based on NCE Power Pro output adjusted for CDDD=0000
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x82, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0xF0, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEC, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x28, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x18, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0xAE, ba[5] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of decoder address", address, NmraPacket::getAccDecPktOpsModeAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecPktOpsModeLegacy510() {
    int address = 510;
    int cv = 892;
    int data = 135;
    QByteArray ba = NmraPacket::accDecPktOpsModeLegacy(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 5, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBE, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x0F, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x7B, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x87, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x4D, ba[4] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecPktOpsMode510() {
    int address = 510;
    int cv = 892;
    int data = 135;
    QByteArray ba = NmraPacket::accDecPktOpsMode(address, cv, data);

    // the following values based on NCE Power Pro output adjusted for CDDD=0000
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBE, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x80, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEF, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x7B, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x87, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x2D, ba[5] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of decoder address", address, NmraPacket::getAccDecPktOpsModeAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecPktOpsModeLegacy511() {
    int address = 511;
    int cv = 275;
    int data = 198;
    QByteArray ba = NmraPacket::accDecPktOpsModeLegacy(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 5, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBF, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x0D, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x12, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xC6, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x66, ba[4] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsModeLegacy(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of decoder address", address, NmraPacket::getAccDecPktOpsModeLegacyAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecPktOpsMode511() {
    int address = 511;
    int cv = 275;
    int data = 198;
    QByteArray ba = NmraPacket::accDecPktOpsMode(address, cv, data);

    // the following values based on NCE Power Pro output adjusted for CDDD=0000
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBF, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x80, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xED, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x12, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xC6, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x6, ba[5] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of decoder address", address, NmraPacket::getAccDecPktOpsModeAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPktOpsModeLegacy1() {
    int address = 1;
    int cv = 384;
    int data = 255;
    QByteArray ba = NmraPacket::accDecoderPktOpsModeLegacy(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 5, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x7D, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x7F, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xFF, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x7C, ba[4] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsModeLegacy(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of decoder address", decAddr(address), NmraPacket::getAccDecoderPktOpsModeLegacyAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPktOpsMode1() {
    int address = 1;
    int cv = 384;
    int data = 255;
    QByteArray ba = NmraPacket::accDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0xF9, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xED, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x7F, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xFF, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x15, ba[5] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of address", address, NmraPacket::getAccDecoderPktOpsModeAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPktOpsModeLegacy4() {
    int address = 4;
    int cv = 56;
    int data = 0;
    QByteArray ba = NmraPacket::accDecoderPktOpsModeLegacy(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 5, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x7C, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x37, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x00, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xCA, ba[4] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsModeLegacy(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of decoder address", decAddr(address), NmraPacket::getAccDecoderPktOpsModeLegacyAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPktOpsMode4() {
    int address = 4;
    int cv = 56;
    int data = 0;
    QByteArray ba = NmraPacket::accDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0xFF, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEC, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x37, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x00, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0xA5, ba[5] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of address", address, NmraPacket::getAccDecoderPktOpsModeAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPktOpsModeLegacy5() {
    int address = 5;
    int cv = 1;
    int data = 30;
    QByteArray ba = NmraPacket::accDecoderPktOpsModeLegacy(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 5, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x82, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x7C, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x00, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x1E, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xE0, ba[4] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsModeLegacy(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of decoder address", decAddr(address), NmraPacket::getAccDecoderPktOpsModeLegacyAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPktOpsMode5() {
    int address = 5;
    int cv = 1;
    int data = 30;
    QByteArray ba = NmraPacket::accDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x82, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0xF9, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEC, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x00, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x1E, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x89, ba[5] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of address", address, NmraPacket::getAccDecoderPktOpsModeAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPktOpsMode252() {
    int address = 252;
    int cv = 999;
    int data = 179;
    QByteArray ba = NmraPacket::accDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBF, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0xFF, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEF, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xE6, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xB3, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0xFA, ba[5] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of address", address, NmraPacket::getAccDecoderPktOpsModeAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPktOpsMode253() {
    int address = 253;
    int cv = 1;
    int data = 241;
    QByteArray ba = NmraPacket::accDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x80, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0xE9, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEC, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x00, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xF1, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x74, ba[5] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of address", address, NmraPacket::getAccDecoderPktOpsModeAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPktOpsMode256() {
    int address = 256;
    int cv = 55;
    int data = 127;
    QByteArray ba = NmraPacket::accDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x80, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0xEF, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEC, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x36, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x7F, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0xCA, ba[5] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of address", address, NmraPacket::getAccDecoderPktOpsModeAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPktOpsMode257() {
    int address = 257;
    int cv = 55;
    int data = 99;
    QByteArray ba = NmraPacket::accDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0xE9, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEC, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x36, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x63, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0xD1, ba[5] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of address", address, NmraPacket::getAccDecoderPktOpsModeAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPktOpsModeLegacy2037() {
    int address = 2037;
    int cv = 556;
    int data = 175;
    QByteArray ba = NmraPacket::accDecoderPktOpsModeLegacy(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 5, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBE, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x0E, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x2B, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xAF, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x34, ba[4] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsModeLegacy(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of decoder address", decAddr(address), NmraPacket::getAccDecoderPktOpsModeLegacyAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPktOpsMode2037() {
    int address = 2037;
    int cv = 556;
    int data = 175;
    QByteArray ba = NmraPacket::accDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBE, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x89, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEE, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x2B, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xAF, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x5D, ba[5] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of address", address, NmraPacket::getAccDecoderPktOpsModeAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPktOpsModeLegacy2040() {
    int address = 2040;
    int cv = 771;
    int data = 102;
    QByteArray ba = NmraPacket::accDecoderPktOpsModeLegacy(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 5, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBE, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x0F, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x02, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x66, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xD5, ba[4] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsModeLegacy(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of decoder address", decAddr(address), NmraPacket::getAccDecoderPktOpsModeLegacyAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPktOpsMode2040() {
    int address = 2040;
    int cv = 771;
    int data = 102;
    QByteArray ba = NmraPacket::accDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBE, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x8F, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEF, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x02, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x66, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0xBA, ba[5] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of address", address, NmraPacket::getAccDecoderPktOpsModeAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPktOpsModeLegacy2044() {
    int address = 2044;
    int cv = 1024;
    int data = 151;
    QByteArray ba = NmraPacket::accDecoderPktOpsModeLegacy(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 5, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBF, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x0F, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xFF, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x97, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xD8, ba[4] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsModeLegacy(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of decoder address", decAddr(address), NmraPacket::getAccDecoderPktOpsModeLegacyAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccDecoderPktOpsMode2044() {
    int address = 2044;
    int cv = 1024;
    int data = 151;
    QByteArray ba = NmraPacket::accDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBF, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x8F, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEF, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xFF, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x97, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0xB7, ba[5] & 0xFF, __FILE__, __LINE__);

    // check packet type and reverse address lookup
    Assert::assertTrue("verify packet type", NmraPacket::isAccDecoderPktOpsMode(ba), __FILE__, __LINE__);
    Assert::assertEquals("reverse lookup of address", address, NmraPacket::getAccDecoderPktOpsModeAddress(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPktOpsMode1() {
    int address = 1;
    int cv = 384;
    int data = 255;
    QByteArray ba = NmraPacket::accSignalDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x71, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xED, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x7F, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xFF, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x9D, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPktOpsMode4() {
    int address = 4;
    int cv = 56;
    int data = 0;
    QByteArray ba = NmraPacket::accSignalDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x77, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEC, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x37, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x00, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x2D, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPktOpsMode5() {
    int address = 5;
    int cv = 1;
    int data = 30;
    QByteArray ba = NmraPacket::accSignalDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x82, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x71, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEC, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x00, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x1E, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x01, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPktOpsMode252() {
    int address = 252;
    int cv = 999;
    int data = 179;
    QByteArray ba = NmraPacket::accSignalDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBF, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x77, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEF, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xE6, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xB3, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x72, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPktOpsMode253() {
    int address = 253;
    int cv = 1;
    int data = 241;
    QByteArray ba = NmraPacket::accSignalDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x80, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x61, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEC, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x00, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xF1, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0xFC, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPktOpsMode256() {
    int address = 256;
    int cv = 55;
    int data = 127;
    QByteArray ba = NmraPacket::accSignalDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x80, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x67, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEC, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x36, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x7F, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x42, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPktOpsMode257() {
    int address = 257;
    int cv = 55;
    int data = 99;
    QByteArray ba = NmraPacket::accSignalDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x61, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEC, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x36, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x63, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x59, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPktOpsMode2037() {
    int address = 2037;
    int cv = 556;
    int data = 175;
    QByteArray ba = NmraPacket::accSignalDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBE, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x01, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEE, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x2B, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xAF, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0xD5, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPktOpsMode2040() {
    int address = 2040;
    int cv = 771;
    int data = 102;
    QByteArray ba = NmraPacket::accSignalDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBE, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x07, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEF, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x02, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x66, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x32, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPktOpsMode2044() {
    int address = 2044;
    int cv = 1024;
    int data = 151;
    QByteArray ba = NmraPacket::accSignalDecoderPktOpsMode(address, cv, data);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBF, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x07, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEF, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xFF, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x97, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x3F, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPkt1Aspect23() {
    int address = 1;
    int aspect = 23;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(address, aspect);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 4, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x71, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x17, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xE7, ba[3] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPkt2Aspect5() {
    int address = 2;
    int aspect = 5;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(address, aspect);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 4, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x73, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x05, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xF7, ba[3] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPkt3Aspect9() {
    int address = 3;
    int aspect = 9;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(address, aspect);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 4, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x75, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x09, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xFD, ba[3] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPkt4Aspect11() {
    int address = 4;
    int aspect = 11;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(address, aspect);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 4, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x77, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x0B, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xFD, ba[3] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPkt5Aspect15() {
    int address = 5;
    int aspect = 15;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(address, aspect);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 4, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x82, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x71, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x0F, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xFC, ba[3] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPkt6Aspect28() {
    int address = 6;
    int aspect = 28;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(address, aspect);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 4, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x82, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x73, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x1C, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xED, ba[3] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPkt7Aspect10() {
    int address = 7;
    int aspect = 10;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(address, aspect);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 4, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x82, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x75, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x0A, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xFD, ba[3] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPkt8Aspect11() {
    int address = 8;
    int aspect = 11;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(address, aspect);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 4, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x82, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x77, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x0B, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xFE, ba[3] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPkt252Aspect13() {
    int address = 252;
    int aspect = 13;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(address, aspect);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 4, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBF, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x77, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x0D, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xC5, ba[3] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPkt253Aspect19() {
    int address = 253;
    int aspect = 19;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(address, aspect);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 4, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x80, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x61, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x13, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xF2, ba[3] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPkt254Aspect2() {
    int address = 254;
    int aspect = 2;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(address, aspect);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 4, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x80, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x63, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x02, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xE1, ba[3] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPkt255Aspect3() {
    int address = 255;
    int aspect = 3;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(address, aspect);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 4, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x80, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x65, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x3, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xE6, ba[3] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPkt256Aspect7() {
    int address = 256;
    int aspect = 7;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(address, aspect);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 4, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x80, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x67, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x07, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xE0, ba[3] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPkt2044Aspect0() {
    int address = 2044;
    int aspect = 0;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(address, aspect);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 4, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBF, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x07, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x00, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xB8, ba[3] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAccSignalDecoderPkt2044Aspect31() {
    int address = 2044;
    int aspect = 31;
    QByteArray ba = NmraPacket::accSignalDecoderPkt(address, aspect);

    // the following values validated against NCE Power Pro output
    Assert::assertEquals("length", 4, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBF, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x07, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0x1F, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xA7, ba[3] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAltAccSignalDecoderPktOpsMode1() {
    int address = 1;
    int cv = 384;
    int data = 255;
    QByteArray ba = NmraPacket::altAccSignalDecoderPktOpsMode(address, cv, data);

    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x80, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x71, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xED, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x7F, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xFF, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x9C, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAltAccSignalDecoderPktOpsMode4() {
    int address = 4;
    int cv = 384;
    int data = 255;
    QByteArray ba = NmraPacket::altAccSignalDecoderPktOpsMode(address, cv, data);

    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x77, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xED, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x7F, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xFF, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x9A, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAltAccSignalDecoderPktOpsMode5() {
    int address = 5;
    int cv = 384;
    int data = 255;
    QByteArray ba = NmraPacket::altAccSignalDecoderPktOpsMode(address, cv, data);

    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x71, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xED, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x7F, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xFF, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x9D, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAltAccSignalDecoderPktOpsMode8() {
    int address = 8;
    int cv = 56;
    int data = 0;
    QByteArray ba = NmraPacket::altAccSignalDecoderPktOpsMode(address, cv, data);

    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x77, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEC, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x37, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x00, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x2D, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAltAccSignalDecoderPktOpsMode9() {
    int address = 9;
    int cv = 1;
    int data = 30;
    QByteArray ba = NmraPacket::altAccSignalDecoderPktOpsMode(address, cv, data);

    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x82, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x71, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEC, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x00, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x1E, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x01, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAltAccSignalDecoderPktOpsMode256() {
    int address = 256;
    int cv = 999;
    int data = 179;
    QByteArray ba = NmraPacket::altAccSignalDecoderPktOpsMode(address, cv, data);

    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBF, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x77, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEF, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0xE6, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xB3, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x72, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAltAccSignalDecoderPktOpsMode257() {
    int address = 257;
    int cv = 1;
    int data = 241;
    QByteArray ba = NmraPacket::altAccSignalDecoderPktOpsMode(address, cv, data);

    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x80, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x61, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEC, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x00, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xF1, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0xFC, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAltAccSignalDecoderPktOpsMode260() {
    int address = 260;
    int cv = 55;
    int data = 127;
    QByteArray ba = NmraPacket::altAccSignalDecoderPktOpsMode(address, cv, data);

    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x80, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x67, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEC, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x36, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x7F, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x42, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAltAccSignalDecoderPktOpsMode261() {
    int address = 261;
    int cv = 55;
    int data = 99;
    QByteArray ba = NmraPacket::altAccSignalDecoderPktOpsMode(address, cv, data);

    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0x81, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x61, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEC, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x36, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x63, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x59, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAltAccSignalDecoderPktOpsMode2041() {
    int address = 2041;
    int cv = 556;
    int data = 175;
    QByteArray ba = NmraPacket::altAccSignalDecoderPktOpsMode(address, cv, data);

    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBE, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x01, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEE, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x2B, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0xAF, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0xD5, ba[5] & 0xFF, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testAltAccSignalDecoderPktOpsMode2044() {
    int address = 2044;
    int cv = 771;
    int data = 102;
    QByteArray ba = NmraPacket::altAccSignalDecoderPktOpsMode(address, cv, data);

    Assert::assertEquals("length", 6, ba.length(), __FILE__, __LINE__);
    Assert::assertEquals("byte 0", 0xBE, ba[0] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 1", 0x07, ba[1] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 2", 0xEF, ba[2] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 3", 0x02, ba[3] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 4", 0x66, ba[4] & 0xFF, __FILE__, __LINE__);
    Assert::assertEquals("byte 5", 0x32, ba[5] & 0xFF, __FILE__, __LINE__);
}


//@Test
/*public*/ void NmraPacketTest::testExtractAddressTypeAcc() {
    QByteArray ba = NmraPacket::accSignalDecoderPkt(123, 12);
    Assert::assertEquals("Accessory", NmraPacket::DccAddressType::ACCESSORY_ADDRESS, NmraPacket::extractAddressType(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressTypeShort() {
    QByteArray bs = NmraPacket::function13Through20Packet(60, false, true, false, true, false, true, false, true, false);
    Assert::assertEquals("Short Loco", NmraPacket::DccAddressType::LOCO_SHORT_ADDRESS, NmraPacket::extractAddressType(bs), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressTypeLong() {
    QByteArray bl = NmraPacket::function13Through20Packet(2060, true, true, false, true, false, true, false, true, false);
    Assert::assertEquals("Long Loco", NmraPacket::DccAddressType::LOCO_LONG_ADDRESS, NmraPacket::extractAddressType(bl), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAccSignal1() {
    QByteArray ba = NmraPacket::accSignalDecoderPkt(1, 12);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(1, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAccSignal2() {
    QByteArray ba = NmraPacket::accSignalDecoderPkt(2, 12);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(2, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAccSignal4() {
    QByteArray ba = NmraPacket::accSignalDecoderPkt(4, 12);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(4, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAccSignal8() {
    QByteArray ba = NmraPacket::accSignalDecoderPkt(8, 12);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(8, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAccSignal16() {
    QByteArray ba = NmraPacket::accSignalDecoderPkt(16, 12);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(16, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAccSignal32() {
    QByteArray ba = NmraPacket::accSignalDecoderPkt(32, 12);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(32, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAccSignal64() {
    QByteArray ba = NmraPacket::accSignalDecoderPkt(64, 12);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(64, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAccSignal128() {
    QByteArray ba = NmraPacket::accSignalDecoderPkt(128, 12);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(128, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAccSignal256() {
    QByteArray ba = NmraPacket::accSignalDecoderPkt(256, 12);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(256, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAcc1() {
    QByteArray ba = NmraPacket::accDecoderPkt(1, true);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(1, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAcc2() {
    QByteArray ba = NmraPacket::accDecoderPkt(2, true);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(2, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAcc4() {
    QByteArray ba = NmraPacket::accDecoderPkt(4, true);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(4, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAcc8() {
    QByteArray ba = NmraPacket::accDecoderPkt(8, true);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(8, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAcc16() {
    QByteArray ba = NmraPacket::accDecoderPkt(16, true);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(16, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAcc32() {
    QByteArray ba = NmraPacket::accDecoderPkt(32, true);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(32, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAcc64() {
    QByteArray ba = NmraPacket::accDecoderPkt(64, true);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(64, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAcc128() {
    QByteArray ba = NmraPacket::accDecoderPkt(128, true);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(128, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAcc256() {
    QByteArray ba = NmraPacket::accDecoderPkt(256, true);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(256, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberAcc512() {
    QByteArray ba = NmraPacket::accDecoderPkt(512, true);
    NmraPacket::extractAddressNumber(ba);
    Assert::assertEquals(512, NmraPacket::extractAddressNumber(ba), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberShort() {
    QByteArray bs = NmraPacket::function13Through20Packet(60, false, true, false, true, false, true, false, true, false);
    Assert::assertEquals("Short Loco", 60, NmraPacket::extractAddressNumber(bs), __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testExtractAddressNumberLong() {
    QByteArray bl = NmraPacket::function13Through20Packet(2060, true, true, false, true, false, true, false, true, false);
    Assert::assertEquals("Long Loco", 2060, NmraPacket::extractAddressNumber(bl), __FILE__, __LINE__);
}

/**
 * Test the 28 speed step forward throttle Note that this has not been
 * independently verified
 */
//@Test
/*public*/ void NmraPacketTest::testSpeedStep28PacketOld() {
    int address = 100;
    // results for speed steps 0-28 when forward
    QVector<QVector<int> > speeds = {
        {-64, 100, 96, -60}, //   0
        {-64, 100, 113, -43}, //  1
        {-64, 100, 98, -58}, //   2
        {-64, 100, 114, -42}, //  3
        {-64, 100, 99, -57}, //   4
        {-64, 100, 115, -41}, //  5
        {-64, 100, 100, -64}, //  6
        {-64, 100, 116, -48}, //  7
        {-64, 100, 101, -63}, //  8
        {-64, 100, 117, -47}, //  9
        {-64, 100, 102, -62}, // 10
        {-64, 100, 118, -46}, // 11
        {-64, 100, 103, -61}, // 12
        {-64, 100, 119, -45}, // 13
        {-64, 100, 104, -52}, // 14
        {-64, 100, 120, -36}, // 15
        {-64, 100, 105, -51}, // 16
        {-64, 100, 121, -35}, // 17
        {-64, 100, 106, -50}, // 18
        {-64, 100, 122, -34}, // 19
        {-64, 100, 107, -49}, // 20
        {-64, 100, 123, -33}, // 21
        {-64, 100, 108, -56}, // 22
        {-64, 100, 124, -40}, // 23
        {-64, 100, 109, -55}, // 24
        {-64, 100, 125, -39}, // 25
        {-64, 100, 110, -54}, // 26
        {-64, 100, 126, -38}, // 27
        {-64, 100, 111, -53} //  28
    };
    for (int speed = 0; speed < 29; speed++) {
        QByteArray packet = NmraPacket::speedStep28Packet(address, true, speed, true);
        Assert::assertNotNull(packet, __FILE__, __LINE__);
        QVector<int> packetVector;
        foreach(char c, packet)
        {
         packetVector.append((int) c);
        }
        Assert::assertArrayEquals("Speed step " + QString::number(speed), speeds[speed], packetVector, __FILE__, __LINE__);
    }
    // invalid inputs should result in null output
    Assert::assertNull("Speed step -1", NmraPacket::speedStep28Packet(address, true, -1, true), __FILE__, __LINE__);
    JUnitAppender::assertErrorMessage("invalid speed -1", __FILE__, __LINE__);
    Assert::assertNull("Speed step 29", NmraPacket::speedStep28Packet(address, true, 29, true), __FILE__, __LINE__);
    JUnitAppender::assertErrorMessage("invalid speed 29", __FILE__, __LINE__);
}

/**
 * Test the 28 speed step forward throttle Note that this has not been
 * independently verified
 */
//@Test
/*public*/ void NmraPacketTest::testSpeedStep28Packet() {
    int address = 100;
    // results for speed steps 0-31 when forward
    QVector<QVector<int> > forward = {
        {-64, 100, 96, -60}, //   0
        {-64, 100, 112, -44}, //  1
        {-64, 100, 97, -59}, //   2
        {-64, 100, 113, -43}, //  3
        {-64, 100, 98, -58}, //   4
        {-64, 100, 114, -42}, //  5
        {-64, 100, 99, -57}, //   6
        {-64, 100, 115, -41}, //  7
        {-64, 100, 100, -64}, //  8
        {-64, 100, 116, -48}, //  9
        {-64, 100, 101, -63}, // 10
        {-64, 100, 117, -47}, // 11
        {-64, 100, 102, -62}, // 12
        {-64, 100, 118, -46}, // 13
        {-64, 100, 103, -61}, // 14
        {-64, 100, 119, -45}, // 15
        {-64, 100, 104, -52}, // 16
        {-64, 100, 120, -36}, // 17
        {-64, 100, 105, -51}, // 18
        {-64, 100, 121, -35}, // 19
        {-64, 100, 106, -50}, // 20
        {-64, 100, 122, -34}, // 21
        {-64, 100, 107, -49}, // 22
        {-64, 100, 123, -33}, // 23
        {-64, 100, 108, -56}, // 24
        {-64, 100, 124, -40}, // 25
        {-64, 100, 109, -55}, // 26
        {-64, 100, 125, -39}, // 27
        {-64, 100, 110, -54}, // 28
        {-64, 100, 126, -38}, // 29
        {-64, 100, 111, -53}, // 30
        {-64, 100, 127, -37} //  31
    };
    for (int speed = 0; speed < 32; speed++) {
        QByteArray packet = NmraPacket::speedStep28Packet(true, address, true, speed, true);
        Assert::assertNotNull(packet, __FILE__, __LINE__);
        QVector<int> packetVector;
        foreach(char c, packet)
        {
         packetVector.append((int) c);
        }
        Assert::assertArrayEquals("Speed step " + QString::number(speed), forward[speed], packetVector, __FILE__, __LINE__);
    }
    // results for speed steps 0-31 when reversed
    QVector<QVector<int> > reverse = {
        {-64, 100, 64, -28}, //  0
        {-64, 100, 80, -12}, //  1
        {-64, 100, 65, -27}, //  2
        {-64, 100, 81, -11}, //  3
        {-64, 100, 66, -26}, //  4
        {-64, 100, 82, -10}, //  5
        {-64, 100, 67, -25}, //  6
        {-64, 100, 83, -9}, //   7
        {-64, 100, 68, -32}, //  8
        {-64, 100, 84, -16}, //  9
        {-64, 100, 69, -31}, // 10
        {-64, 100, 85, -15}, // 11
        {-64, 100, 70, -30}, // 12
        {-64, 100, 86, -14}, // 13
        {-64, 100, 71, -29}, // 14
        {-64, 100, 87, -13}, // 15
        {-64, 100, 72, -20}, // 16
        {-64, 100, 88, -4}, //  17
        {-64, 100, 73, -19}, // 18
        {-64, 100, 89, -3}, //  19
        {-64, 100, 74, -18}, // 20
        {-64, 100, 90, -2}, //  21
        {-64, 100, 75, -17}, // 22
        {-64, 100, 91, -1}, //  23
        {-64, 100, 76, -24}, // 24
        {-64, 100, 92, -8}, //  25
        {-64, 100, 77, -23}, // 26
        {-64, 100, 93, -7}, //  27
        {-64, 100, 78, -22}, // 28
        {-64, 100, 94, -6}, //  29
        {-64, 100, 79, -21}, // 30
        {-64, 100, 95, -5} //   31
    };
    for (int speed = 0; speed < 32; speed++) {
        QByteArray packet = NmraPacket::speedStep28Packet(true, address, true, speed, false);
        Assert::assertNotNull(packet, __FILE__, __LINE__);
        QVector<int> packetVector;
        foreach(char c, packet)
        {
         packetVector.append((int) c);
        }
        Assert::assertArrayEquals("Speed step " + QString::number(speed), reverse[speed], packetVector, __FILE__, __LINE__);
    }
    // invalid inputs should result in null output
    Assert::assertNull("Speed step -1", NmraPacket::speedStep28Packet(true, address, true, -1, true), __FILE__, __LINE__);
    JUnitAppender::assertErrorMessage("invalid speed -1", __FILE__, __LINE__);
    Assert::assertNull("Speed step 32", NmraPacket::speedStep28Packet(true, address, true, 32, true), __FILE__, __LINE__);
    JUnitAppender::assertErrorMessage("invalid speed 32", __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testToStringNoPacket() {
    bool thrown = false;
    try {
        NmraPacket::toString(QByteArray{});
    } catch (IllegalArgumentException e) {
        thrown = true;
    }

    Assert::assertTrue(thrown, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testToStringShortLocoPacket() {
    // short address function set
    QString display = NmraPacket::toString(QByteArrayLiteral("\x3C\xDE\x55\x00"));
    Assert::assertEquals("LOCO_SHORT_ADDRESS type: 222 to addr 60", display, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testToStringAccessoryPacket1() {
    QString display = NmraPacket::toString(NmraPacket::accDecoderPkt(1, true));
    Assert::assertEquals("ACCESSORY_ADDRESS type: 120 to addr 1", display, __FILE__, __LINE__);
}

//@Test
/*public*/ void NmraPacketTest::testToStringAccessoryPacket257() {
    QString display = NmraPacket::toString(NmraPacket::accDecoderPkt(257, true));
    Assert::assertEquals("ACCESSORY_ADDRESS type: 104 to addr 257", display, __FILE__, __LINE__);
}

//@Before
/*public*/ void NmraPacketTest::setUp() {
    JUnitUtil::setUp();
}

//@After
/*public*/ void NmraPacketTest::tearDown() {
    JUnitUtil::tearDown();
}

/*private*/ /*static*/ int NmraPacketTest::decAddr(int accyAddr) {
    return (((accyAddr - 1) >> 2) << 2) + 1;
}
