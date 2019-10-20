#include "lndeferprogranmmertest.h"
#include "loggerfactory.h"
#include "junitutil.h"
#include "assert1.h"
#include "loconetinterfacescaffold.h"
#include "slotmanager.h"
#include "loconetsystemconnectionmemo.h"
#include "lndeferprogrammer.h"
#include "assert1.h"
#include "programmingmode.h"
#include "lntrafficcontroller.h"

LnDeferProgrammerTest::LnDeferProgrammerTest(QObject *parent) : QObject(parent)
{

}
/**
 * Large parts are copied from SlotManagerTest; combining these would be good.
 *
 * @author Bob Jacobsen Copyright (C) 2018
 */
///*public*/ class LnDeferProgrammerTest {

//@Test
/*public*/ void LnDeferProgrammerTest::testCTor() {
    LnTrafficController* lnis = new LocoNetInterfaceScaffold();
    SlotManager* slotmanager = new SlotManager(lnis);
    LocoNetSystemConnectionMemo* memo = new LocoNetSystemConnectionMemo(lnis, slotmanager);
    LnDeferProgrammer* t = new LnDeferProgrammer(memo);
    Assert::assertNotNull("exists", t, __FILE__, __LINE__);
    memo->dispose();
}


//@Test
/*public*/ void LnDeferProgrammerTest::testReadCVPaged() throw (ProgrammerException) {
    QString CV1 = "12";
    ProgListener* p2 = nullptr;
    slotmanager->setMode(ProgrammingMode::PAGEMODE);
    slotmanager->readCV(CV1, p2);
    Assert::assertEquals("read message",
            "EF 0E 7C 23 00 00 00 00 00 0B 00 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LnDeferProgrammerTest::testReadCVRegister() throw (ProgrammerException) {
    QString CV1 = "2";
    ProgListener* p2 = nullptr;
    slotmanager->setMode(ProgrammingMode::REGISTERMODE);
    slotmanager->readCV(CV1, p2);
    Assert::assertEquals("read message",
            "EF 0E 7C 13 00 00 00 00 00 01 00 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LnDeferProgrammerTest::testReadCVDirect() throw (ProgrammerException) {
    log->debug(".... start testReadCVDirect ...");
    QString CV1 = "29";
    slotmanager->setMode(ProgrammingMode::DIRECTBYTEMODE);
    slotmanager->readCV(CV1, lstn);
    Assert::assertEquals("read message",
            "EF 0E 7C 2B 00 00 00 00 00 1C 00 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
    Assert::assertEquals("one message sent", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);

    // LACK received back (DCS240 sequence)
    log->debug("send LACK back");
    startedShortTimer = false;
    startedLongTimer = false;

    slotmanager->message(new LocoNetMessage(QVector<int>()<<0xB4<< 0x6F<< 0x01<< 0x25));
//    JUnitUtil.waitFor(()->{return startedLongTimer;},"startedLongTimer not set");
    ReleaseUntilO12* r12 = new ReleaseUntilO12(this);
    JUnitUtil::waitFor(r12, "startedLongTimer not set", __FILE__, __LINE__);
    Assert::assertEquals("post-LACK status", -999, status, __FILE__, __LINE__);
    Assert::assertTrue("started long timer", startedLongTimer, __FILE__, __LINE__);
    Assert::assertFalse("didn't start short timer", startedShortTimer, __FILE__, __LINE__);

    // read received back (DCS240 sequence)
    value = 0;
    log->debug("send E7 reply back");
    slotmanager->message(new LocoNetMessage(QVector<int>()<<0xE7<< 0x0E<< 0x7C<< 0x2B<< 0x00<< 0x00<< 0x02<< 0x47<< 0x00<< 0x1C<< 0x23<< 0x7F<< 0x7F<< 0x3B));
//    JUnitUtil.waitFor(()->{return value == 35;},"value == 35 not set");
    ReleaseUntilO11* r11 = new ReleaseUntilO11(this);
    JUnitUtil::waitFor(r11, "value == 35 not set", __FILE__, __LINE__);
    log->debug("checking..");
    Assert::assertEquals("reply status", 0, status, __FILE__, __LINE__);
    Assert::assertEquals("reply value", 35, value, __FILE__, __LINE__);

    log->debug(".... end testReadCVDirect ...");
}

//@Test
/*public*/ void LnDeferProgrammerTest::testReadCVOpsModeLong() throw (ProgrammerException) {
    QString CV1 = "12";
    ProgListener* p2 = nullptr;
    slotmanager->readCVOpsMode(CV1, p2, 4 * 128 + 0x23, true);
    Assert::assertEquals("read message",
            "EF 0E 7C 2F 00 04 23 00 00 0B 00 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LnDeferProgrammerTest::testReadCVOpsModeShort() throw (ProgrammerException) {
    QString CV1 = "12";
    ProgListener* p2 = nullptr;
    slotmanager->readCVOpsMode(CV1, p2, 22, false);
    Assert::assertEquals("read message",
            "EF 0E 7C 2F 00 00 16 00 00 0B 00 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LnDeferProgrammerTest::testWriteCVPaged() throw (ProgrammerException) {
    QString CV1 = "12";
    int val2 = 34;
    ProgListener* p3 = nullptr;
    slotmanager->setMode(ProgrammingMode::PAGEMODE);
    slotmanager->writeCV(CV1, val2, p3);
    Assert::assertEquals("write message",
            "EF 0E 7C 63 00 00 00 00 00 0B 22 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LnDeferProgrammerTest::testWriteCVPagedString() throw (ProgrammerException) {
    QString CV1 = "12";
    int val2 = 34;
    ProgListener* p3 = nullptr;
    slotmanager->setMode(ProgrammingMode::PAGEMODE);
    slotmanager->writeCV(CV1, val2, p3);
    Assert::assertEquals("write message",
            "EF 0E 7C 63 00 00 00 00 00 0B 22 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LnDeferProgrammerTest::testWriteCVRegister() throw (ProgrammerException) {
    QString CV1 = "2";
    int val2 = 34;
    ProgListener* p3 = nullptr;
    slotmanager->setMode(ProgrammingMode::REGISTERMODE);
    slotmanager->writeCV(CV1, val2, p3);
    Assert::assertEquals("write message",
            "EF 0E 7C 53 00 00 00 00 00 01 22 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LnDeferProgrammerTest::testWriteCVDirect() throw (ProgrammerException) {
    QString CV1 = "12";
    int val2 = 34;
    ProgListener* p3 = nullptr;
    slotmanager->setMode(ProgrammingMode::DIRECTBYTEMODE);
    slotmanager->writeCV(CV1, val2, p3);
    Assert::assertEquals("write message",
            "EF 0E 7C 6B 00 00 00 00 00 0B 22 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LnDeferProgrammerTest::testWriteCVDirectStringDCS240() throw (ProgrammerException) {
    log->debug(".... start testWriteCVDirectStringDCS240 ...");
    QString CV1 = "31";
    int val2 = 16;
    slotmanager->setMode(ProgrammingMode::DIRECTBYTEMODE);
    slotmanager->writeCV(CV1, val2, lstn);
    Assert::assertEquals("one message sent", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);
    Assert::assertEquals("write message",
            "EF 0E 7C 6B 00 00 00 00 00 1E 10 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
    Assert::assertEquals("one message sent", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);

    // LACK received back (DCS240 sequence)
    log->debug("send LACK back");
    startedShortTimer = false;
    startedLongTimer = false;
    slotmanager->message(new LocoNetMessage(QVector<int>()<<0xB4<< 0x6F<< 0x01<< 0x25));
//    JUnitUtil.waitFor(()->{return startedShortTimer;},"startedShortTimer not set");
    ReleaseUntilO10* r10 = new ReleaseUntilO10(this);
    JUnitUtil::waitFor(r10, "startedShortTimer not set", __FILE__, __LINE__);
    Assert::assertEquals("post-LACK status", -999, status, __FILE__, __LINE__);
    Assert::assertTrue("started short timer", startedShortTimer, __FILE__, __LINE__);
    Assert::assertFalse("didn't start long timer", startedLongTimer, __FILE__, __LINE__);

    // read received back (DCS240 sequence)
    value = -15;
    log->debug("send E7 reply back");
    slotmanager->message(new LocoNetMessage(QVector<int>()<<0xE7<< 0x0E<< 0x7C<< 0x6B<< 0x00<< 0x00<< 0x02<< 0x47<< 0x00<< 0x1E<< 0x10<< 0x7F<< 0x7F<< 0x4A));
    Assert::assertEquals("no immediate reply", -999, status, __FILE__, __LINE__);
//    JUnitUtil.waitFor(()->{return value == -1;},"value == -1 not set");
    ReleaseUntilO13* r13 = new ReleaseUntilO13(this);
    JUnitUtil::waitFor(r13, "value == -1 not set", __FILE__, __LINE__);
    log->debug("checking..");
    Assert::assertEquals("reply status", 0, status, __FILE__, __LINE__);
    Assert::assertEquals("reply value", -1, value, __FILE__, __LINE__);

    log->debug(".... end testWriteCVDirectStringDCS240 ...");
}



// The minimal setup for log4J
//@Before
/*public*/ void LnDeferProgrammerTest::setUp() {
    JUnitUtil::setUp();

    // prepare an interface
    lnis = new LocoNetInterfaceScaffold();

//    slotmanager = new SlotManager(lnis) {
//        @Override
//        protected void startLongTimer() {
//            super.startLongTimer();
//            startedLongTimer = true;
//        }
//        @Override
//        protected void startShortTimer() {
//            super.startShortTimer();
//            startedShortTimer = true;
//        }
//        @Override
//        protected void stopTimer() {
//            super.stopTimer();
//            stoppedTimer = true;
//        }
//    };
    slotmanager = new SlotManagerO3(lnis, this);

    status = -999;
    value = -999;
    startedShortTimer = false;
    startedLongTimer = false;

//    lstn = new ProgListener(){
//        @Override
//        /*public*/ void programmingOpReply(int val, int stat) {
//            log->debug("   reply val: {} status: {}", val, stat);
//            status = stat;
//            value = val;
//        }
//    };
  lstn = new ProgListenerO4(this);
}

//@After
/*public*/ void LnDeferProgrammerTest::tearDown() {
    JUnitUtil::tearDown();
}

/*private*/ /*final*/ /*static*/ Logger* LnDeferProgrammerTest::log = LoggerFactory::getLogger("LnDeferProgrammerTest");
