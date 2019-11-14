#include "dccsignalheadtest.h"
#include "assert1.h"
#include "junitutil.h"
#include "dccsignalhead.h"
#include "instancemanager.h"

DccSignalHeadTest::DccSignalHeadTest(QObject* parent)
{

}
/**
 * Tests for the DccSignalHead implementation
 *
 * @author	Bob Jacobsen Copyright (C) 2013
 */
///*public*/ class DccSignalHeadTest extends AbstractSignalHeadTestBase {

    //@Test
    /*public*/ void DccSignalHeadTest::testCtor1() {
        DccSignalHead* s = new DccSignalHead("IH$1");

        Assert::assertEquals("system name", "IH$1", s->getSystemName(), __FILE__, __LINE__);
        Assert::assertEquals("Send count", 0, sentPacketCount, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void DccSignalHeadTest::testRedAppearance() {
        DccSignalHead* s = new DccSignalHead("IH$1");

        s->setAppearance(SignalHead::RED);

        Assert::assertEquals("Send count", 1, sentPacketCount, __FILE__, __LINE__);
        Assert::assertEquals("Packet length", 4, lastSentPacket.length(), __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 0", 0x80, lastSentPacket[0] & 0xFF, __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 1", 0x71, lastSentPacket[1] & 0xFF, __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 2", 0x00, lastSentPacket[2] & 0xFF, __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void DccSignalHeadTest::testDarkAppearance() {
        DccSignalHead* s = new DccSignalHead("IH$1");

        s->setAppearance(SignalHead::RED);  // Default is DARK
        s->setAppearance(SignalHead::DARK);

        Assert::assertEquals("Send count", 2, sentPacketCount, __FILE__, __LINE__);
        Assert::assertEquals("Packet length", 4, lastSentPacket.length(), __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 0", 0x80, lastSentPacket[0] & 0xFF, __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 1", 0x71, lastSentPacket[1] & 0xFF, __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 2", 0x08, lastSentPacket[2] & 0xFF, __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void DccSignalHeadTest::testLunarAppearance() {
        DccSignalHead* s = new DccSignalHead("IH$1");

        s->setAppearance(SignalHead::LUNAR);

        Assert::assertEquals("Send count", 1, sentPacketCount, __FILE__, __LINE__);
        Assert::assertEquals("Packet length", 4, lastSentPacket.length(), __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 0", 0x80, lastSentPacket[0] & 0xFF, __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 1", 0x71, lastSentPacket[1] & 0xFF, __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 2", 0x03, lastSentPacket[2] & 0xFF, __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void DccSignalHeadTest::testYellowAppearance() {
        DccSignalHead* s = new DccSignalHead("IH$1");

        s->setAppearance(SignalHead::YELLOW);

        Assert::assertEquals("Send count", 1, sentPacketCount, __FILE__, __LINE__);
        Assert::assertEquals("Packet length", 4, lastSentPacket.length(), __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 0", 0x80, lastSentPacket[0] & 0xFF, __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 1", 0x71, lastSentPacket[1] & 0xFF, __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 2", 0x01, lastSentPacket[2] & 0xFF, __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void DccSignalHeadTest::testGreenAppearance() {
        DccSignalHead* s = new DccSignalHead("IH$1");

        s->setAppearance(SignalHead::GREEN);

        Assert::assertEquals("Send count", 1, sentPacketCount, __FILE__, __LINE__);
        Assert::assertEquals("Packet length", 4, lastSentPacket.length(), __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 0", 0x80, lastSentPacket[0] & 0xFF, __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 1", 0x71, lastSentPacket[1] & 0xFF, __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 2", 0x02, lastSentPacket[2] & 0xFF, __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void DccSignalHeadTest::testFlashRedAppearance() {
        DccSignalHead* s = new DccSignalHead("IH$1");

        s->setAppearance(SignalHead::FLASHRED);

        Assert::assertEquals("Send count", 1, sentPacketCount, __FILE__, __LINE__);
        Assert::assertEquals("Packet length", 4, lastSentPacket.length(), __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 0", 0x80, lastSentPacket[0] & 0xFF, __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 1", 0x71, lastSentPacket[1] & 0xFF, __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 2", 0x04, lastSentPacket[2] & 0xFF, __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void DccSignalHeadTest::testFlashLunarAppearance() {
        DccSignalHead* s = new DccSignalHead("IH$1");

        s->setAppearance(SignalHead::FLASHLUNAR);

        Assert::assertEquals("Send count", 1, sentPacketCount, __FILE__, __LINE__);
        Assert::assertEquals("Packet length", 4, lastSentPacket.length(), __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 0", 0x80, lastSentPacket[0] & 0xFF, __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 1", 0x71, lastSentPacket[1] & 0xFF, __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 2", 0x07, lastSentPacket[2] & 0xFF, __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void DccSignalHeadTest::testFlashYellowAppearance() {
        DccSignalHead* s = new DccSignalHead("IH$1");

        s->setAppearance(SignalHead::FLASHYELLOW);

        Assert::assertEquals("Send count", 1, sentPacketCount, __FILE__, __LINE__);
        Assert::assertEquals("Packet length", 4, lastSentPacket.length(), __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 0", 0x80, lastSentPacket[0] & 0xFF, __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 1", 0x71, lastSentPacket[1] & 0xFF, __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 2", 0x05, lastSentPacket[2] & 0xFF, __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void DccSignalHeadTest::testFlashGreenAppearance() {
        DccSignalHead* s = new DccSignalHead("IH$1");

        s->setAppearance(SignalHead::FLASHGREEN);

        Assert::assertEquals("Send count", 1, sentPacketCount, __FILE__, __LINE__);
        Assert::assertEquals("Packet length", 4, lastSentPacket.length(), __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 0", 0x80, lastSentPacket[0] & 0xFF, __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 1", 0x71, lastSentPacket[1] & 0xFF, __FILE__, __LINE__);
        Assert::assertEquals("Packet byte 2", 0x06, lastSentPacket[2] & 0xFF, __FILE__, __LINE__);

    }

    // from here down is testing infrastructure

    //@Override
    /*public*/ SignalHead* DccSignalHeadTest::getHeadToTest() {
        return new DccSignalHead("IH$1");
    }

    // The minimal setup for log4J
    //@Before
    /*public*/ void DccSignalHeadTest::setUp() throw (Exception) {
        JUnitUtil::setUp();
        JUnitUtil::initInternalTurnoutManager();

        CommandStation* c = new CommandStationO1(this);
//        {
//         @Override
//           /*public*/ boolean sendPacket(byte[] packet, int repeats) {
//          lastSentPacket = packet;
//          sentPacketCount++;
//          return true;
//         }

//         @Override
//           /*public*/ String getUserName() {
//          return null;
//         }

//         @Override
//           /*public*/ String getSystemPrefix() {
//          return "I";
//         }
//        };
        InstanceManager::store(c, "CommandStation");
        lastSentPacket = nullptr;
        sentPacketCount = 0;
    }

    //@After
    /*public*/ void DccSignalHeadTest::tearDown() throw (Exception) {
        JUnitUtil::tearDown();
    }
