#include "slotmanagertest.h"
#include "loconetslot.h"
#include "loggerfactory.h"
#include "assert1.h"
#include "loconetinterfacescaffold.h"
#include "slotlistener.h"
#include "addressedhighcvprogrammerfacade.h"
#include "multiindexprogrammerfacade.h"
#include "nmrapacket.h"
#include "junitappender.h"

SlotManagerTest::SlotManagerTest(QObject *parent) : QObject(parent)
{

}
/**
 * @author B. Milhaupt, Copyright (C) 2018
 */

///*public*/ class SlotManagerTest {


//@Test
/*public*/ void SlotManagerTest::testGetDirectFunctionAddressOK() {
    LocoNetMessage* m1;

    m1 = new LocoNetMessage(11);
    m1->setElement(0, 0xED);  // short 03 sets F9
    m1->setElement(1, 0x0B);
    m1->setElement(2, 0x7F);
    m1->setElement(3, 0x24);
    m1->setElement(4, 0x02);
    m1->setElement(5, 0x03);
    m1->setElement(6, 0x21);
    m1->setElement(7, 0x00);
    m1->setElement(8, 0x00);
    m1->setElement(9, 0x00);
    m1->setElement(10, 0x62);
    Assert::assertEquals("short 3 sets F9", 3,
            slotmanager->getDirectFunctionAddress(m1), __FILE__, __LINE__);

    m1 = new LocoNetMessage(11);
    m1->setElement(0, 0xED);  // long 513 sets F9
    m1->setElement(1, 0x0B);
    m1->setElement(2, 0x7F);
    m1->setElement(3, 0x34);
    m1->setElement(4, 0x05);
    m1->setElement(5, 0x42);
    m1->setElement(6, 0x01);
    m1->setElement(7, 0x21);
    m1->setElement(8, 0x00);
    m1->setElement(9, 0x00);
    m1->setElement(10, 0x35);
    Assert::assertEquals("long 513 sets F9", 513,
            slotmanager->getDirectFunctionAddress(m1), __FILE__, __LINE__);
}

//@Test
/*public*/ void SlotManagerTest::testGetDirectDccPacketOK() {
    LocoNetMessage* m1;

    m1 = new LocoNetMessage(11);
    m1->setElement(0, 0xED);  // short 03 sets F9
    m1->setElement(1, 0x0B);
    m1->setElement(2, 0x7F);
    m1->setElement(3, 0x24);
    m1->setElement(4, 0x02);
    m1->setElement(5, 0x03);
    m1->setElement(6, 0x21);
    m1->setElement(7, 0x00);
    m1->setElement(8, 0x00);
    m1->setElement(9, 0x00);
    m1->setElement(10, 0x62);
    Assert::assertEquals("short 3 sets F9", 0xA1,
            slotmanager->getDirectDccPacket(m1), __FILE__, __LINE__);

    m1 = new LocoNetMessage(11);
    m1->setElement(0, 0xED);  // long 513 sets F9
    m1->setElement(1, 0x0B);
    m1->setElement(2, 0x7F);
    m1->setElement(3, 0x34);
    m1->setElement(4, 0x05);
    m1->setElement(5, 0x42);
    m1->setElement(6, 0x01);
    m1->setElement(7, 0x21);
    m1->setElement(8, 0x00);
    m1->setElement(9, 0x00);
    m1->setElement(10, 0x35);
    Assert::assertEquals("long 513 sets F9", 0xA1,
            slotmanager->getDirectDccPacket(m1), __FILE__, __LINE__);
}

//@Test
/*public*/ void SlotManagerTest::testGetSlotSend() {
    testSlot = nullptr;
//    SlotListener p2 = new SlotListener() {
//        @Override
//        /*public*/ void notifyChangedSlot(LocoNetSlot l) {
//            testSlot = l;
//        }
//    };
    SlotListenerO1* p2 = new SlotListenerO1(this);
    slotmanager->slotFromLocoAddress(0x2134, p2);
    Assert::assertEquals("slot request message",
            "BF 42 34 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
    Assert::assertEquals("hash length", 1, slotmanager->mLocoAddrHash.size(), __FILE__, __LINE__);
    Assert::assertEquals("key present", true,
            slotmanager->mLocoAddrHash.contains((0x2134)), __FILE__, __LINE__);
    Assert::assertEquals("value present", true,
            slotmanager->mLocoAddrHash.values().contains(p2), __FILE__, __LINE__);
}

/*public*/ void SlotListenerO1::notifyChangedSlot(LocoNetSlot* l) {
    smt->testSlot = l;
}

//@Test
/*public*/ void SlotManagerTest::testGetSlotRcv() {
    testSlot = nullptr;
//    SlotListener p2 = new SlotListener() {
//        @Override
//        /*public*/ void notifyChangedSlot(LocoNetSlot l) {
//            testSlot = l;
//        }
//    };
    SlotListenerO1* p2 = new SlotListenerO1(this);
    slotmanager->slotFromLocoAddress(0x2134, p2);
    // echo of the original message
    LocoNetMessage* m1 = new LocoNetMessage(4);
    m1->setOpCode(0xBF);
    m1->setElement(1, 0x42);
    m1->setElement(2, 0x34);
    slotmanager->message(m1);
    // reply says its in slot 4
    LocoNetMessage* m2 = new LocoNetMessage(14);
    m2->setElement(0, 0xE7);
    m2->setElement(1, 0xE);
    m2->setElement(2, 0xB);
    m2->setElement(3, 3);
    m2->setElement(4, 0x34);
    m2->setElement(5, 0);
    m2->setElement(6, 0);
    m2->setElement(7, 4);
    m2->setElement(8, 0);
    m2->setElement(9, 0x42);
    m2->setElement(10, 0);
    m2->setElement(11, 0);
    m2->setElement(12, 0);
    m2->setElement(13, 0x6c);
    slotmanager->message(m2);
    Assert::assertEquals("returned slot", slotmanager->slot(11), testSlot, __FILE__, __LINE__);
    // and make sure it forgets
    testSlot = nullptr;
    slotmanager->message(m1);
    slotmanager->message(m2);
    Assert::assertEquals("returned slot", nullptr, testSlot, __FILE__, __LINE__);
}

//@Test
/*public*/ void SlotManagerTest::testReadCVPaged() throw (ProgrammerException) {
    QString CV1 = "12";
    ProgListener* p2 = nullptr;
    slotmanager->setMode(ProgrammingMode::PAGEMODE);
    slotmanager->readCV(CV1, p2);
    log->debug("msg = " + lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper());
    Assert::assertEquals("read message",
            "EF 0E 7C 23 00 00 00 00 00 0B 00 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
}

//@Test
/*public*/ void SlotManagerTest::testReadCVRegister() throw (ProgrammerException) {
    QString CV1 = "2";
    ProgListener* p2 = nullptr;
    slotmanager->setMode(ProgrammingMode::REGISTERMODE);
    slotmanager->readCV(CV1, p2);
    Assert::assertEquals("read message",
            "EF 0E 7C 13 00 00 00 00 00 01 00 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
}

//@Test
/*public*/ void SlotManagerTest::testReadCVDirect() throw (ProgrammerException)  {
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
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xB4<< 0x6F<< 0x01<< 0x25));
    //JUnitUtil::waitFor(()->{return startedLongTimer;},"startedLongTimer not set");
    ReleaseUntil01* r01 = new ReleaseUntil01(this);
    JUnitUtil::waitFor(r01, "startedLongTimer not set", __FILE__, __LINE__);
    Assert::assertEquals("post-LACK status", -999, status, __FILE__, __LINE__);
    Assert::assertTrue("started long timer", startedLongTimer, __FILE__, __LINE__);
    Assert::assertFalse("didn't start short timer", startedShortTimer, __FILE__, __LINE__);

    // read received back (DCS240 sequence)
    value = 0;
    log->debug("send E7 reply back");
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xE7<< 0x0E<< 0x7C<< 0x2B<< 0x00<< 0x00<< 0x02<< 0x47<< 0x00<< 0x1C<< 0x23<< 0x7F<< 0x7F<< 0x3B));
    //JUnitUtil::waitFor(()->{return value == 35;},"value == 35 not set");
    ReleaseUntil02* r02 = new ReleaseUntil02(this);
    JUnitUtil::waitFor(r02, "value == 35 not set", __FILE__, __LINE__);
    log->debug("checking..");
    Assert::assertEquals("reply status", 0, status, __FILE__, __LINE__);
    Assert::assertEquals("reply value", 35, value, __FILE__, __LINE__);
    log->debug(".... end testReadCVDirect ...");
}


//@Test
/*public*/ void SlotManagerTest::testReadCVOpsModeLong() throw (ProgrammerException)  {
    QString CV1 = "12";
    ProgListener* p2 = nullptr;
    slotmanager->readCVOpsMode(CV1, p2, 4 * 128 + 0x23, true);
    Assert::assertEquals("read message",
            "EF 0E 7C 2F 00 04 23 00 00 0B 00 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
}

//@Test
/*public*/ void SlotManagerTest::testReadCVOpsModeShort() throw (ProgrammerException)  {
    QString CV1 = "12";
    ProgListener* p2 = nullptr;
    slotmanager->readCVOpsMode(CV1, p2, 22, false);
    Assert::assertEquals("read message",
            "EF 0E 7C 2F 00 00 16 00 00 0B 00 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
}

//@Test
/*public*/ void SlotManagerTest::testWriteCVPaged() throw (ProgrammerException)  {
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
/*public*/ void SlotManagerTest::testWriteCVRegister() throw (ProgrammerException)  {
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
/*public*/ void SlotManagerTest::testWriteCVDirect() throw (ProgrammerException)  {
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
/*public*/ void SlotManagerTest::testWriteCVDirectStringDCS240() throw (ProgrammerException)  {
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
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xB4<< 0x6F<< 0x01<< 0x25));
    //JUnitUtil::waitFor(()->{return startedShortTimer;},"startedShortTimer not set");
    ReleaseUntil03* r03 = new ReleaseUntil03(this);
    JUnitUtil::waitFor(r03, "startedShortTimer not set", __FILE__, __LINE__);
    Assert::assertEquals("post-LACK status", -999, status, __FILE__, __LINE__);
    Assert::assertTrue("started short timer", startedShortTimer, __FILE__, __LINE__);
    Assert::assertFalse("didn't start long timer", startedLongTimer, __FILE__, __LINE__);

    // read received back (DCS240 sequence)
    value = -15;
    log->debug("send E7 reply back");
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xE7<< 0x0E<< 0x7C<< 0x6B<< 0x00<< 0x00<< 0x02<< 0x47<< 0x00<< 0x1E<< 0x10<< 0x7F<< 0x7F<< 0x4A));
    Assert::assertEquals("no immediate reply", -999, status, __FILE__, __LINE__);
    //JUnitUtil::waitFor(()->{return value == -1;},"value == -1 not set");
    ReleaseUntil04* r04 = new ReleaseUntil04(this);
    JUnitUtil::waitFor(r04, "value == -1 not set", __FILE__, __LINE__);
    log->debug("checking..");
    Assert::assertEquals("reply status", 0, status, __FILE__, __LINE__);
    Assert::assertEquals("reply value", -1, value, __FILE__, __LINE__);

    log->debug(".... end testWriteCVDirectStringDCS240 ...");
}

//@Test
/*public*/ void SlotManagerTest::testLackLogic() {
    LocoNetMessage* m = new LocoNetMessage(QVector<int>() <<0xB4<< 0x6F<< 0x01<< 0x25);
    Assert::assertTrue("checkLackTaskAccepted(m.getElement(2))", slotmanager->checkLackTaskAccepted(m->getElement(2)), __FILE__, __LINE__);
    Assert::assertFalse("checkLackProgrammerBusy(m.getElement(2))", slotmanager->checkLackProgrammerBusy(m->getElement(2)), __FILE__, __LINE__);
    Assert::assertFalse("checkLackAcceptedBlind(m.getElement(2))", slotmanager->checkLackAcceptedBlind(m->getElement(2)), __FILE__, __LINE__);
}

//@Test
/*public*/ void SlotManagerTest::testWriteCVDirectStringDCS240Interrupted() throw (ProgrammerException)  {
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

    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xB4<< 0x6F<< 0x01<< 0x25));
    //JUnitUtil::waitFor(()->{return startedShortTimer;},"startedShortTimer not set");
    ReleaseUntil03* r03 = new ReleaseUntil03(this);
    JUnitUtil::waitFor(r03, "startedShortTimer not set", __FILE__, __LINE__);
    Assert::assertEquals("post-LACK status", -999, status, __FILE__, __LINE__);
    Assert::assertTrue("started short timer", startedShortTimer, __FILE__, __LINE__);
    Assert::assertFalse("didn't start long timer", startedLongTimer, __FILE__, __LINE__);

    // CS check received back (DCS240 sequence)
    log->debug("send CS check back");
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xBB<< 0x7F<< 0x00<< 0x3B));
    // not clear what to wait for here; status doesn't change
    //util.JUnitUtil::releaseThread(this, releaseTestDelay);
    Assert::assertEquals("post-CS-check status", -999, status, __FILE__, __LINE__);

    // read received back (DCS240 sequence)
    log->debug("send E7 reply back");
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xE7<< 0x0E<< 0x7C<< 0x6B<< 0x00<< 0x00<< 0x02<< 0x47<< 0x00<< 0x1E<< 0x10<< 0x7F<< 0x7F<< 0x4A));
    Assert::assertEquals("no immediate reply", -999, status, __FILE__, __LINE__);
    // not clear what to wait for here; content doesn't change
//    JUnitUtil::releaseThread(this, releaseTestDelay);
    JUnitUtil::waitFor(releaseTestDelay);
    log->debug("checking..");
    Assert::assertEquals("reply status", 0, status, __FILE__, __LINE__);
    Assert::assertEquals("reply value", -1, value, __FILE__, __LINE__);

    log->debug(".... end testWriteCVDirectStringDCS240 ...");
}

//@Test
/*public*/ void SlotManagerTest::testWriteCVOpsLongAddr() throw (ProgrammerException)  {
    QString CV1 = "12";
    int val2 = 34;
    ProgListener* p3 = nullptr;
    slotmanager->writeCVOpsMode(CV1, val2, p3, 4 * 128 + 0x23, true);
    Assert::assertEquals("one message sent", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);
    Assert::assertEquals("write message",
            "EF 0E 7C 67 00 04 23 00 00 0B 22 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
}

//@Test
/*public*/ void SlotManagerTest::testWriteCVOpsShortAddr() throw (ProgrammerException)  {
    QString CV1 = "12";
    int val2 = 34;
    ProgListener* p3 = nullptr;
    slotmanager->writeCVOpsMode(CV1, val2, p3, 22, false);
    Assert::assertEquals("write message",
            "EF 0E 7C 67 00 00 16 00 00 0B 22 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
}

//@Test
/*public*/ void SlotManagerTest::testWriteThroughFacade() throw (ProgrammerException)  {
    log->debug(".... start testWriteThroughFacade ...");
    slotmanager->setMode(ProgrammingMode::DIRECTBYTEMODE);

    // install Facades from ESU_LokSoundV4_0.xml

    // <name>High Access via Double Index</name>
    QString top = "256";
    QString addrCVhigh = "96";
    QString addrCVlow = "97";
    QString valueCV = "99";
    QString modulo = "100";
    AddressedHighCvProgrammerFacade* pf1
            = new AddressedHighCvProgrammerFacade(slotmanager, top, addrCVhigh, addrCVlow, valueCV, modulo);

    // <name>Indexed CV access</name>
    QString PI = "31";
    QString SI = "16";
    bool cvFirst = false;
    MultiIndexProgrammerFacade* pf2
            = new MultiIndexProgrammerFacade(pf1, PI, SI, cvFirst, false);

    QString CV1 = "16.2.257";
    int val2 = 55;

    // Start overall sequence
    pf2->writeCV(CV1, val2, lstn);

    // Check for PI write
    Assert::assertEquals("one message sent", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);
    Assert::assertEquals("write PI message",
            "EF 0E 7C 6B 00 00 00 00 00 1E 10 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
    Assert::assertEquals("one message sent", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);

    // LACK received back (DCS240 sequence) to PI write
    log->debug("send LACK back");
    startedShortTimer = false;
    startedLongTimer = false;
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xB4<< 0x6F<< 0x01<< 0x25));
    //JUnitUtil::waitFor(()->{return startedShortTimer;},"startedShortTimer not set");
    ReleaseUntil03* r03 = new ReleaseUntil03(this);
    JUnitUtil::waitFor(r03, "startedShortTimer not set", __FILE__, __LINE__);
    Assert::assertEquals("post-LACK status", -999, status, __FILE__, __LINE__);
    Assert::assertTrue("started short timer", startedShortTimer, __FILE__, __LINE__);
    Assert::assertFalse("didn't start long timer", startedLongTimer, __FILE__, __LINE__);
//    util.JUnitUtil::releaseThread(this, releaseTestDelay);  // wait for slow reply
    Assert::assertEquals("still one message sent", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);

    // completion received back (DCS240 sequence) to PI write
    log->debug("send E7 reply back");
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xE7<< 0x0E<< 0x7C<< 0x6B<< 0x00<< 0x00<< 0x02<< 0x47<< 0x00<< 0x1E<< 0x10<< 0x7F<< 0x7F<< 0x4A));
    Assert::assertEquals("no immediate reply", -999, status, __FILE__, __LINE__);
//    util.JUnitUtil::releaseThread(this, releaseTestDelay);
    JUnitUtil::waitFor(releaseTestDelay);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);

    // check that SI write happened
    Assert::assertEquals("two messages sent", 2, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("write SI message",
            "EF 0E 7C 6B 00 00 00 00 00 0F 02 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);

    // LACK received back (DCS240 sequence) to SI write
    log->debug("send LACK back");
    startedShortTimer = false;
    startedLongTimer = false;
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xB4<< 0x6F<< 0x01<< 0x25));
    //JUnitUtil::waitFor(()->{return startedShortTimer;},"startedShortTimer not set");
    //ReleaseUntil03* r03 = new ReleaseUntil03(this);
    JUnitUtil::waitFor(r03, "startedShortTimer not set", __FILE__, __LINE__);
    Assert::assertEquals("post-LACK status", -999, status, __FILE__, __LINE__);
    Assert::assertTrue("started short timer", startedShortTimer, __FILE__, __LINE__);
    Assert::assertFalse("didn't start long timer", startedLongTimer, __FILE__, __LINE__);
//    util.JUnitUtil::releaseThread(this, releaseTestDelay);  // wait for slow reply
    Assert::assertEquals("still two messages sent", 2, lnis->outbound.size(), __FILE__, __LINE__);

    // completion received back (DCS240 sequence) to SI write
    log->debug("send E7 reply back");
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xE7<< 0x0E<< 0x7C<< 0x6B<< 0x00<< 0x00<< 0x02<< 0x47<< 0x00<< 0x0F<< 0x02<< 0x7F<< 0x7F<< 0x4A));
    Assert::assertEquals("no immediate reply", -999, status, __FILE__, __LINE__);
//    util.JUnitUtil::releaseThread(this, releaseTestDelay);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);

    // check that final CV write happened
    Assert::assertEquals("three messages sent", 3, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("write final CV message",
            "EF 0E 7C 6B 00 00 00 00 10 00 37 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);

    // LACK received back (DCS240 sequence) to final CV write
    log->debug("send LACK back");
    startedShortTimer = false;
    startedLongTimer = false;
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xB4<< 0x6F<< 0x01<< 0x25));
    //JUnitUtil::waitFor(()->{return startedShortTimer;},"startedShortTimer not set");
    r03 = new ReleaseUntil03(this);
    JUnitUtil::waitFor(r03, "startedShortTimer not set", __FILE__, __LINE__);
    Assert::assertEquals("post-LACK status", -999, status, __FILE__, __LINE__);
    Assert::assertTrue("started short timer", startedShortTimer, __FILE__, __LINE__);
    Assert::assertFalse("didn't start long timer", startedLongTimer, __FILE__, __LINE__);
//    util.JUnitUtil::releaseThread(this, releaseTestDelay);  // wait for slow reply
    Assert::assertEquals("three messages sent", 3, lnis->outbound.size(), __FILE__, __LINE__);

    // completion received back (DCS240 sequence)
    log->debug("send E7 reply back");
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xE7<< 0x0E<< 0x7C<< 0x6B<< 0x00<< 0x00<< 0x02<< 0x47<< 0x10<< 0x00<< 0x37<< 0x7F<< 0x7F<< 0x4A));
    Assert::assertEquals("no immediate reply", -999, status, __FILE__, __LINE__);
//    util.JUnitUtil::releaseThread(this, releaseTestDelay);
    log->debug("checking..");
    Assert::assertEquals("reply status", 0, status, __FILE__, __LINE__);
    Assert::assertEquals("reply value", -1, value, __FILE__, __LINE__);
    Assert::assertEquals("three messages sent", 3, lnis->outbound.size(), __FILE__, __LINE__);

    log->debug(".... end testWriteThroughFacade ...");
}

//@Test
/*public*/ void SlotManagerTest::testReadThroughFacade() throw (ProgrammerException)  {
    log->debug(".... start testReadThroughFacade ...");
    slotmanager->setMode(ProgrammingMode::DIRECTBYTEMODE);

    // install Facades from ESU_LokSoundV4_0.xml

    // <name>High Access via Double Index</name>
    QString top = "256";
    QString addrCVhigh = "96";
    QString addrCVlow = "97";
    QString valueCV = "99";
    QString modulo = "100";
    AddressedHighCvProgrammerFacade* pf1
            = new AddressedHighCvProgrammerFacade(slotmanager, top, addrCVhigh, addrCVlow, valueCV, modulo);

    // <name>Indexed CV access</name>
    QString PI = "31";
    QString SI = "16";
    bool cvFirst = false;
    MultiIndexProgrammerFacade* pf2
            = new MultiIndexProgrammerFacade(pf1, PI, SI, cvFirst, false);

    QString CV1 = "16.2.257";
    // Start overall sequence
    pf2->readCV(CV1, lstn);

    // Check for PI write
    Assert::assertEquals("one message sent", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);
    Assert::assertEquals("write PI message",
            "EF 0E 7C 6B 00 00 00 00 00 1E 10 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
    Assert::assertEquals("one message sent", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);

    // LACK received back (DCS240 sequence) to PI write
    log->debug("send LACK back");
    startedShortTimer = false;
    startedLongTimer = false;
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xB4<< 0x6F<< 0x01<< 0x25));
//    JUnitUtil::releaseThread(this, releaseTestDelay);
    Assert::assertEquals("post-LACK status", -999, status, __FILE__, __LINE__);
    Assert::assertTrue("started short timer", startedShortTimer, __FILE__, __LINE__);
    Assert::assertFalse("didn't start long timer", startedLongTimer, __FILE__, __LINE__);
//    util.JUnitUtil::releaseThread(this, releaseTestDelay);  // wait for slow reply
    Assert::assertEquals("still one message sent", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);

    // completion received back (DCS240 sequence) to PI write
    log->debug("send E7 reply back");
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xE7<< 0x0E<< 0x7C<< 0x6B<< 0x00<< 0x00<< 0x02<< 0x47<< 0x00<< 0x1E<< 0x10<< 0x7F<< 0x7F<< 0x4A));
    Assert::assertEquals("no immediate reply", -999, status, __FILE__, __LINE__);
//    util.JUnitUtil::releaseThread(this, releaseTestDelay);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);

    // check that SI write happened
    Assert::assertEquals("two messages sent", 2, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("write SI message",
            "EF 0E 7C 6B 00 00 00 00 00 0F 02 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);

    // LACK received back (DCS240 sequence) to SI write
    log->debug("send LACK back");
    startedShortTimer = false;
    startedLongTimer = false;
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xB4<< 0x6F<< 0x01<< 0x25));
//    util.JUnitUtil::releaseThread(this, releaseTestDelay);
    Assert::assertEquals("post-LACK status", -999, status, __FILE__, __LINE__);
    Assert::assertTrue("started short timer", startedShortTimer, __FILE__, __LINE__);
    Assert::assertFalse("didn't start long timer", startedLongTimer, __FILE__, __LINE__);
//    util.JUnitUtil::releaseThread(this, releaseTestDelay);  // wait for slow reply
    Assert::assertEquals("still two messages sent", 2, lnis->outbound.size(), __FILE__, __LINE__);

    // completion received back (DCS240 sequence) to SI write
    log->debug("send E7 reply back");
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xE7<< 0x0E<< 0x7C<< 0x6B<< 0x00<< 0x00<< 0x02<< 0x47<< 0x00<< 0x0F<< 0x02<< 0x7F<< 0x7F<< 0x4A));
    Assert::assertEquals("no immediate reply", -999, status, __FILE__, __LINE__);
//    util.JUnitUtil::releaseThread(this, releaseTestDelay);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);

    // check that final CV write happened
    Assert::assertEquals("three messages sent", 3, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("write final CV message",
            "EF 0E 7C 2B 00 00 00 00 10 00 00 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);

    // LACK received back (DCS240 sequence) to final CV write
    log->debug("send LACK back");
    startedShortTimer = false;
    startedLongTimer = false;
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xB4<< 0x6F<< 0x01<< 0x25));
//    util.JUnitUtil::releaseThread(this, releaseTestDelay);
    Assert::assertEquals("post-LACK status", -999, status, __FILE__, __LINE__);
    Assert::assertTrue("started long timer", startedLongTimer, __FILE__, __LINE__);
    Assert::assertFalse("didn't start short timer", startedShortTimer, __FILE__, __LINE__);
//    util.JUnitUtil::releaseThread(this, releaseTestDelay);  // wait for slow reply
    Assert::assertEquals("three messages sent", 3, lnis->outbound.size(), __FILE__, __LINE__);

    // completion received back (DCS240 sequence)
    log->debug("send E7 reply back");
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xE7<< 0x0E<< 0x7C<< 0x6B<< 0x00<< 0x00<< 0x02<< 0x47<< 0x10<< 0x00<< 0x37<< 0x7F<< 0x7F<< 0x4A));
    Assert::assertEquals("no immediate reply", -999, status, __FILE__, __LINE__);
//    util.JUnitUtil::releaseThread(this, releaseTestDelay);
    log->debug("checking..");
    Assert::assertEquals("reply status", 0, status, __FILE__, __LINE__);
    Assert::assertEquals("reply value", 55, value, __FILE__, __LINE__);
    Assert::assertEquals("three messages sent", 3, lnis->outbound.size(), __FILE__, __LINE__);

    log->debug(".... end testReadThroughFacade ...");
}

//@Test
/*public*/ void SlotManagerTest::testReadThroughFacadeFail() throw (ProgrammerException)  {
    log->debug(".... start testReadThroughFacadeFail ...");
    slotmanager->setMode(ProgrammingMode::DIRECTBYTEMODE);

    // install Facades from ESU_LokSoundV4_0.xml

    // <name>High Access via Double Index</name>
    QString top = "256";
    QString addrCVhigh = "96";
    QString addrCVlow = "97";
    QString valueCV = "99";
    QString modulo = "100";
    AddressedHighCvProgrammerFacade* pf1
            = new AddressedHighCvProgrammerFacade(slotmanager, top, addrCVhigh, addrCVlow, valueCV, modulo);

    // <name>Indexed CV access</name>
    QString PI = "31";
    QString SI = "16";
    bool cvFirst = false;
    MultiIndexProgrammerFacade* pf2
            = new MultiIndexProgrammerFacade(pf1, PI, SI, cvFirst, false);

    QString CV1 = "16.2.257";
    // Start overall sequence
    pf2->readCV(CV1, lstn);

    // Check for PI write
    Assert::assertEquals("one message sent", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);
    Assert::assertEquals("write PI message",
            "EF 0E 7C 6B 00 00 00 00 00 1E 10 7F 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
    Assert::assertEquals("one message sent", 1, lnis->outbound.size(), __FILE__, __LINE__);
    Assert::assertEquals("initial status", -999, status, __FILE__, __LINE__);

    // LACK received back (DCS240 sequence) to PI write: rejected
    log->debug("send LACK back");
    startedShortTimer = false;
    startedLongTimer = false;
    slotmanager->message(new LocoNetMessage(QVector<int>() <<0xB4<< 0x6F<< 0x0<< 0x24));
//    util.JUnitUtil::releaseThread(this, releaseTestDelay);
    Assert::assertEquals("post-LACK status is fail", 4, status, __FILE__, __LINE__);
    Assert::assertFalse("didn't start short timer", startedShortTimer, __FILE__, __LINE__);
    Assert::assertFalse("didn't start long timer", startedLongTimer, __FILE__, __LINE__);
//    util.JUnitUtil::releaseThread(this, releaseTestDelay);  // wait for slow reply
    Assert::assertEquals("still one message sent", 1, lnis->outbound.size(), __FILE__, __LINE__);

    log->debug(".... end testReadThroughFacadeFail ...");
}

//@Test
/*public*/ void SlotManagerTest::testGetProgrammingModes() {
    QList<QString> l = slotmanager->getSupportedModes();
    Assert::assertEquals("programming mode list length ok", 5, l.size(), __FILE__, __LINE__);
    Assert::assertEquals("programming mode 0", "DIRECTBYTEMODE", l.at(0), __FILE__, __LINE__);
    Assert::assertEquals("programming mode 1", "PAGEMODE", l.at(1), __FILE__, __LINE__);
    Assert::assertEquals("programming mode 2", "REGISTERMODE", l.at(2), __FILE__, __LINE__);
    Assert::assertEquals("programming mode 3", "ADDRESSMODE", l.at(3), __FILE__, __LINE__);
    Assert::assertEquals("programming mode 4", "LOCONETCSOPSWMODE", l.at(4), __FILE__, __LINE__);
}

//@Test
/*public*/ void SlotManagerTest::testSendPacket() {
    QByteArray msg = NmraPacket::accDecPktOpsMode(1, 4, 53);
    slotmanager->sendPacket(msg, 1);
    Assert::assertEquals("nmra packet 1",
            "ED 0B 7F 50 07 01 70 6C 03 35 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accDecPktOpsMode(128, 4, 53);
    slotmanager->sendPacket(msg, 2);
    Assert::assertEquals("nmra packet 2",
            "ED 0B 7F 51 07 00 50 6C 03 35 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg= NmraPacket::accDecPktOpsMode(256, 4, 53);
    slotmanager->sendPacket(msg, 3);
    Assert::assertEquals("nmra packet 3",
            "ED 0B 7F 52 07 00 30 6C 03 35 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accDecPktOpsMode(1, 37, 53);
    slotmanager->sendPacket(msg, 4);
    Assert::assertEquals("nmra packet 4",
            "ED 0B 7F 53 07 01 70 6C 24 35 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accDecPktOpsMode(1, 129, 53);
    slotmanager->sendPacket(msg, 5);
    Assert::assertEquals("nmra packet 5",
            "ED 0B 7F 54 0F 01 70 6C 00 35 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accDecPktOpsMode(1, 10, 0);
    slotmanager->sendPacket(msg, 6);
    Assert::assertEquals("nmra packet 6",
            "ED 0B 7F 55 07 01 70 6C 09 00 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accDecPktOpsMode(1, 10, 128);
    slotmanager->sendPacket(msg, 7);
    Assert::assertEquals("nmra packet 7",
            "ED 0B 7F 56 17 01 70 6C 09 00 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accDecPktOpsMode(1, 10, 255);
    slotmanager->sendPacket(msg, 8);
    Assert::assertEquals("nmra packet 8",
            "ED 0B 7F 57 17 01 70 6C 09 7F 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accDecPktOpsMode(511, 255, 0);
    slotmanager->sendPacket(msg, 9);
    JUnitAppender::assertWarnMessage("Ops Mode Accessory Packet 'Send count' reduced from 9 to 8.",__FILE__, __LINE__);
    Assert::assertEquals("nmra packet 9",
            "ED 0B 7F 57 0F 3F 00 6C 7E 00 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accSignalDecoderPkt(1, 31);
    slotmanager->sendPacket(msg, 0);
    JUnitAppender::assertWarnMessage("Ops Mode Accessory Packet 'Send count' of 0 is illegal and is forced to 1.",__FILE__, __LINE__);
    Assert::assertEquals("nmra packet 10",
            "ED 0B 7F 30 01 01 71 1F 00 00 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accSignalDecoderPkt(2, 30);
    slotmanager->sendPacket(msg, -1);
    JUnitAppender::assertWarnMessage("Ops Mode Accessory Packet 'Send count' of -1 is illegal and is forced to 1.",__FILE__, __LINE__);
    Assert::assertEquals("nmra packet 10",
            "ED 0B 7F 30 01 01 73 1E 00 00 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accSignalDecoderPkt(4, 29);
    slotmanager->sendPacket(msg, 3);
    Assert::assertEquals("nmra packet 10",
            "ED 0B 7F 32 01 01 77 1D 00 00 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accSignalDecoderPkt(8, 27);
    slotmanager->sendPacket(msg, 2);
    Assert::assertEquals("nmra packet 10",
            "ED 0B 7F 31 01 02 77 1B 00 00 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accSignalDecoderPkt(16, 23);
    slotmanager->sendPacket(msg, 2);
    Assert::assertEquals("nmra packet 10",
            "ED 0B 7F 31 01 04 77 17 00 00 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accSignalDecoderPkt(32, 15);
    slotmanager->sendPacket(msg, 2);
    Assert::assertEquals("nmra packet 10",
            "ED 0B 7F 31 01 08 77 0F 00 00 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accSignalDecoderPkt(64, 1);
    slotmanager->sendPacket(msg, 2);
    Assert::assertEquals("nmra packet 10",
            "ED 0B 7F 31 01 10 77 01 00 00 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accSignalDecoderPkt(128, 0);
    slotmanager->sendPacket(msg, 2);
    Assert::assertEquals("nmra packet 10",
            "ED 0B 7F 31 01 20 77 00 00 00 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accSignalDecoderPkt(256, 2);
    slotmanager->sendPacket(msg, 2);
    Assert::assertEquals("nmra packet 10",
            "ED 0B 7F 31 01 00 67 02 00 00 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accSignalDecoderPkt(512, 4);
    slotmanager->sendPacket(msg, 2);
    Assert::assertEquals("nmra packet 10",
            "ED 0B 7F 31 01 00 57 04 00 00 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accSignalDecoderPkt(1024, 8);
    slotmanager->sendPacket(msg, 2);
    Assert::assertEquals("nmra packet 10",
            "ED 0B 7F 31 01 00 37 08 00 00 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);

    msg = NmraPacket::accSignalDecoderPkt(511, 16);
    slotmanager->sendPacket(msg, 2);
    Assert::assertEquals("nmra packet 10",
            "ED 0B 7F 31 01 00 55 10 00 00 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
}


//@Before
/*public*/ void SlotManagerTest::setUp() {
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
    slotmanager = new SlotManagerO1(lnis, this);

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
    lstn = new ProgListenerO1(this);
}

/*protected*/ void SlotManagerO1::startLongTimer() {
    SlotManager::startLongTimer();
    smt->startedLongTimer = true;
}
//@Override
/*protected*/ void SlotManagerO1::startShortTimer() {
    SlotManager::startShortTimer();
    smt->startedShortTimer = true;
}
//@Override
/*protected*/ void SlotManagerO1::stopTimer() {
    SlotManager::stopTimer();
    smt->stoppedTimer = true;
}

/*public*/ void ProgListenerO1::programmingOpReply(int val, int stat) {
    smt->log->debug(tr("   reply val: %1 status: %2").arg(val).arg(stat));
    smt->status = stat;
    smt->value = val;

}

//@After
/*public*/ void SlotManagerTest::tearDown() {
    JUnitUtil::tearDown();
}

/*private*/ /*final*/ /*static*/ Logger* SlotManagerTest::log = LoggerFactory::getLogger("SlotManager");


