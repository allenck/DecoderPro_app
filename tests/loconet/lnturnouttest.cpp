#include "lnturnouttest.h"
#include "loggerfactory.h"
#include "junitutil.h"
#include "assert1.h"
#include "loconetmessage.h"
#include "lnturnout.h"
#include "loconetsystemconnectionmemo.h"
#include "lnturnout.h"
#include "junitappender.h"
#include "lnturnoutmanager.h"

LnTurnoutTest::LnTurnoutTest(QObject *parent)
{

}
/**
 * Tests for the jmri.jmrix.loconet.LnTurnout class
 *
 * @author	Bob Jacobsen
 */
// /*public*/ class LnTurnoutTest extends jmri.implementation.AbstractTurnoutTestBase {

    //@Override
    /*public*/ int LnTurnoutTest::numListeners() {
        return lnis->numListeners();
    }

    /**
     * Check that last two messages correspond to Turnout::CLOSED/on, then Turnout::CLOSED/off.
     * Why last two? For Turnout::UNKNOWN reason(s), this test gets _three_ messages,
     * with the first one being a set 21 Turnout::CLOSED and off. Is it left over from
     * some previous test?
     */
    //@Override
    /*public*/ void LnTurnoutTest::checkClosedMsgSent() throw (InterruptedException) {
        // Make sure that timed message has fired by waiting
//        /*synchronized (this)*/ {
           this->wait(LnTurnout::METERINTERVAL + 25);
//        }

        // check results
        Assert::assertTrue("at least two messages", lnis->outbound.size() >= 2, __FILE__, __LINE__);
        Assert::assertEquals(lnis->outbound.at(lnis->outbound.size() - 2)->toString().toUpper(),
                "B0 14 30 00", __FILE__, __LINE__);  // Turnout::CLOSED/ON loconet message
        Assert::assertEquals(lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(),
                "B0 14 20 00", __FILE__, __LINE__);  // Turnout::CLOSED/OFF loconet message
    }

    /**
     * Check that last two messages correspond to thrown/on, then thrown/off
     */
    //@Override
    /*public*/ void LnTurnoutTest::checkThrownMsgSent() throw (InterruptedException) {
        // Make sure that timed message has fired by waiting
        /*synchronized (this)*/ {
            this->wait(LnTurnout::METERINTERVAL + 25);
        }

        // check for messages
        Assert::assertTrue("just two messages", lnis->outbound.size() == 2, __FILE__, __LINE__);
        Assert::assertEquals(lnis->outbound.at(lnis->outbound.size() - 2)->toString().toUpper(),
                "B0 14 10 00", __FILE__, __LINE__);  // THROWN/ON loconet message
        Assert::assertEquals(lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(),
                "B0 14 00 00", __FILE__, __LINE__);  // THROWN/OFF loconet message
    }

    //@Test
    /*public*/ void LnTurnoutTest::checkIncoming() {
        // notify the Ln that somebody else changed it...
        LocoNetMessage* m = new LocoNetMessage(4);
        m->setOpCode(0xb0);
        m->setElement(1, 0x14);     // set Turnout::CLOSED
        m->setElement(2, 0x30);
        m->setElement(3, 0x00);
        lnt->messageFromManager(m);
        Assert::assertTrue(t->getCommandedState() == Turnout::CLOSED, __FILE__, __LINE__);

        m = new LocoNetMessage(4);
        m->setOpCode(0xb0);
        m->setElement(1, 0x14);     // set THROWN
        m->setElement(2, 0x10);
        m->setElement(3, 0x00);
        lnt->messageFromManager(m);
        Assert::assertTrue(t->getCommandedState() == Turnout::THROWN, __FILE__, __LINE__);
    }
    //@Test
    /*public*/ void LnTurnoutTest::checkIncomingWithAck() {
        // notify the Ln that somebody else changed it...using OPC_SW_ACK
        LocoNetMessage* m = new LocoNetMessage(4);
        m->setOpCode(0xbd);
        m->setElement(1, 0x14);     // set Turnout::CLOSED
        m->setElement(2, 0x30);
        m->setElement(3, 0x00);
        lnt->messageFromManager(m);
        Assert::assertTrue(t->getCommandedState() == Turnout::CLOSED, __FILE__, __LINE__);

        m = new LocoNetMessage(4);
        m->setOpCode(0xbd);
        m->setElement(1, 0x14);     // set THROWN
        m->setElement(2, 0x10);
        m->setElement(3, 0x00);
        lnt->messageFromManager(m);
        Assert::assertTrue(t->getCommandedState() == Turnout::THROWN, __FILE__, __LINE__);
    }

    // LnTurnout test for incoming status message
    //@Test
    /*public*/ void LnTurnoutTest::testLnTurnoutStatusMsg() {
        // prepare an interface
        // set Turnout::CLOSED
        try {
            t->setCommandedState(Turnout::CLOSED);
        } catch (Exception* e) {
            log->error("TO exception: " + e->getMessage());
        }
        Assert::assertTrue(lnis->outbound.at(0)
                ->toString().toUpper() == ("B0 14 30 00"), __FILE__, __LINE__);  // Turnout::CLOSED loconet message
        Assert::assertTrue(t->getCommandedState() == Turnout::CLOSED, __FILE__, __LINE__);

        // notify the Ln that somebody else changed it...
        LocoNetMessage* m = new LocoNetMessage(4);
        m->setOpCode(0xb1);
        m->setElement(1, 0x14);     // set Turnout::CLOSED
        m->setElement(2, 0x20);
        m->setElement(3, 0x7b);
        lnt->messageFromManager(m);
        Assert::assertTrue(t->getCommandedState() == Turnout::CLOSED, __FILE__, __LINE__);

    }

    // LnTurnout test for incoming status message
    //@Test
    /*public*/ void LnTurnoutTest::testLnTurnoutStatusMsgAck() {
        // prepare an interface
        // set Turnout::CLOSED
        try {
            t->setProperty(LnTurnoutManager::BYPASSBUSHBYBITKEY, true);
            t->setCommandedState(Turnout::THROWN);
        } catch (Exception* e) {
            log->error("TO exception: " + e->getMessage());
        }
        Assert::assertTrue(lnis->outbound.at(0)
                ->toString().toUpper() == ("B0 14 10 00"), __FILE__, __LINE__);  // thrown loconet message
        Assert::assertTrue(t->getCommandedState() == Turnout::THROWN, __FILE__, __LINE__);

        // notify the Ln that somebody else changed it...
        LocoNetMessage* m = new LocoNetMessage(4);
        m->setOpCode(0xb1);
        m->setElement(1, 0x14);     // set thrown
        m->setElement(2, 0x10);
        m->setElement(3, 0x7b);
        lnt->messageFromManager(m);
        Assert::assertTrue(t->getCommandedState() == Turnout::THROWN, __FILE__, __LINE__);

    }

    // LnTurnout test for exact feedback
    //@Test
    /*public*/ void LnTurnoutTest::testLnTurnoutExactFeedback() {
        LocoNetMessage* m;
        // prepare a specific test
        t->setBinaryOutput(true);
        t->setCommandedState(Turnout::CLOSED);
        t->setFeedbackMode(Turnout::EXACT);
        Assert::assertEquals("CommandedState after set Turnout::CLOSED is Turnout::CLOSED", Turnout::CLOSED,t->getCommandedState(), __FILE__, __LINE__);
        // because this is the first time, the state is Turnout::UNKNOWN; never goes back to that (in this test)
        Assert::assertEquals("KnownState after set Turnout::CLOSED is Turnout::UNKNOWN", Turnout::UNKNOWN,t->getKnownState(), __FILE__, __LINE__);

        // notify the Ln of first feedback - AUX is thrown, so moved off
        log->debug("notify of 1st feedback");
        m = new LocoNetMessage(4);
        m->setOpCode(0xb1);
        m->setElement(1, 0x14);
        m->setElement(2, 0x40);
        m->setElement(3, 0x1A);     // AUX reports THROWN\

        lnt->messageFromManager(m);
        Assert::assertEquals("CommandedState after AUX report THROWN is Turnout::CLOSED", Turnout::CLOSED,t->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("KnownState after AUX report THROWN is Turnout::INCONSISTENT", Turnout::INCONSISTENT,t->getKnownState(), __FILE__, __LINE__);

        // notify the Ln of second feedback - SWITCH is Turnout::CLOSED, so moved on
        log->debug("notify of 2nd feedback");
        m = new LocoNetMessage(4);
        m->setOpCode(0xb1);
        m->setElement(1, 0x14);
        m->setElement(2, 0x70);
        m->setElement(3, 0x2A);     // SWITCH reports Turnout::CLOSED
        lnt->messageFromManager(m);
        Assert::assertEquals("CommandedState after SWITCH report Turnout::CLOSED is Turnout::CLOSED", Turnout::CLOSED, t->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("KnownState after SWITCH report Turnout::CLOSED is Turnout::CLOSED", Turnout::CLOSED,t->getKnownState(), __FILE__, __LINE__);

        // test transition to THROWN
       t->setCommandedState(Turnout::THROWN);
        Assert::assertEquals("CommandedState after set THROWN is THROWN", Turnout::THROWN, t->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("KnownState after set THROWN is Turnout::UNKNOWN", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        // notify the Ln of first feedback - SWITCH is thrown, so moved off
        m = new LocoNetMessage(4);
        m->setOpCode(0xb1);
        m->setElement(1, 0x14);
        m->setElement(2, 0x60);
        m->setElement(3, 0x3A);     // AUX reports THROWN
        lnt->messageFromManager(m);
        Assert::assertEquals("CommandedState after SWITCH report THROWN is THROWN", Turnout::THROWN, t->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("KnownState after SWITCH report THROWN is Turnout::INCONSISTENT", Turnout::INCONSISTENT, t->getKnownState(), __FILE__, __LINE__);

        // notify the Ln of second feedback - AUX is Turnout::CLOSED, so moved on
        m = new LocoNetMessage(4);
        m->setOpCode(0xb1);
        m->setElement(1, 0x14);
        m->setElement(2, 0x50);
        m->setElement(3, 0x0A);     // SWITCH reports Turnout::CLOSED
        lnt->messageFromManager(m);
        Assert::assertEquals("CommandedState after AUX report Turnout::CLOSED is THROWN", Turnout::THROWN, t->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("KnownState after AUX report Turnout::CLOSED is THROWN", Turnout::THROWN, t->getKnownState(), __FILE__, __LINE__);

        // test transition back to Turnout::CLOSED
        t->setCommandedState(LnTurnout::CLOSED);
        Assert::assertEquals("CommandedState after 2nd set Turnout::CLOSED is Turnout::CLOSED", Turnout::CLOSED, t->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("KnownState after 2nd set Turnout::CLOSED is THROWN", Turnout::THROWN, t->getKnownState(), __FILE__, __LINE__);

        // notify the Ln of first feedback - AUX is thrown, so moved off
        m = new LocoNetMessage(4);
        m->setOpCode(0xb1);
        m->setElement(1, 0x14);
        m->setElement(2, 0x40);
        m->setElement(3, 0x1A);     // AUX reports THROWN
        lnt->messageFromManager(m);
        Assert::assertEquals("CommandedState after AUX report THROWN is Turnout::CLOSED", Turnout::CLOSED, t->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("KnownState after AUX report THROWN is Turnout::INCONSISTENT", Turnout::INCONSISTENT, t->getKnownState(), __FILE__, __LINE__);

        // notify the Ln of second feedback - SWITCH is Turnout::CLOSED, so moved on
        m = new LocoNetMessage(4);
        m->setOpCode(0xb1);
        m->setElement(1, 0x14);
        m->setElement(2, 0x70);
        m->setElement(3, 0x2A);     // SWITCH reports Turnout::CLOSED
        lnt->messageFromManager(m);
        Assert::assertEquals("CommandedState after SWITCH report Turnout::CLOSED is Turnout::CLOSED", Turnout::CLOSED, t->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("KnownState after SWITCH report Turnout::CLOSED is Turnout::CLOSED", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        // test transition to back to THROWN in wrong order
       t->setCommandedState(Turnout::THROWN);
        Assert::assertEquals("CommandedState after 2nd set THROWN is THROWN", Turnout::THROWN,t->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("KnownState after 2nd set THROWN is Turnout::CLOSED", Turnout::CLOSED,t->getKnownState(), __FILE__, __LINE__);

        // notify the Ln of second feedback (out of order) - AUX is Turnout::CLOSED, so moved on
        m = new LocoNetMessage(4);
        m->setOpCode(0xb1);
        m->setElement(1, 0x14);
        m->setElement(2, 0x50);
        m->setElement(3, 0x0A);     // SWITCH reports Turnout::CLOSED
        lnt->messageFromManager(m);
        Assert::assertEquals("CommandedState after AUX report Turnout::CLOSED is THROWN", Turnout::THROWN,t->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("KnownState after AUX report Turnout::CLOSED is THROWN", Turnout::THROWN,t->getKnownState(), __FILE__, __LINE__);

        // notify the Ln of first feedback (out of order) - SWITCH is thrown, so moved off - ignored
        m = new LocoNetMessage(4);
        m->setOpCode(0xb1);
        m->setElement(1, 0x14);
        m->setElement(2, 0x60);
        m->setElement(3, 0x3A);     // AUX reports THROWN
        lnt->messageFromManager(m);
        Assert::assertEquals("CommandedState after SWITCH report THROWN is THROWN", Turnout::THROWN,t->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("KnownState after SWITCH report THROWN is THROWN", Turnout::THROWN,t->getKnownState(), __FILE__, __LINE__);

        // test transition back to Turnout::CLOSED in wrong order
       t->setCommandedState(Turnout::CLOSED);
        Assert::assertEquals("CommandedState after 2nd set Turnout::CLOSED is Turnout::CLOSED", Turnout::CLOSED,t->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("KnownState after 2nd set Turnout::CLOSED is THROWN", Turnout::THROWN,t->getKnownState(), __FILE__, __LINE__);

        // notify the Ln of second feedback (out of order) - SWITCH is Turnout::CLOSED, so moved on
        m = new LocoNetMessage(4);
        m->setOpCode(0xb1);
        m->setElement(1, 0x14);
        m->setElement(2, 0x70);
        m->setElement(3, 0x2A);     // SWITCH reports Turnout::CLOSED
        lnt->messageFromManager(m);
        Assert::assertEquals("CommandedState after SWITCH report Turnout::CLOSED is Turnout::CLOSED", Turnout::CLOSED,t->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("KnownState after SWITCH report Turnout::CLOSED is Turnout::CLOSED", Turnout::CLOSED,t->getKnownState(), __FILE__, __LINE__);

        // notify the Ln of first feedback (out of order) - AUX is thrown, so moved off
        m = new LocoNetMessage(4);
        m->setOpCode(0xb1);
        m->setElement(1, 0x14);
        m->setElement(2, 0x40);
        m->setElement(3, 0x1A);     // AUX reports THROWN
        lnt->messageFromManager(m);
        Assert::assertEquals("CommandedState after AUX report THROWN is Turnout::CLOSED", Turnout::CLOSED,t->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("KnownState after AUX report THROWN is Turnout::CLOSED", Turnout::CLOSED,t->getKnownState(), __FILE__, __LINE__);

    }

    // test that only one message is sent when binaryOutput is set
    //@Test
    /*public*/ void LnTurnoutTest::testBasicSet() throw (InterruptedException) {
       t->setBinaryOutput(true);
       t->setCommandedState(Turnout::THROWN);

        // Make sure that timed message has fired by waiting
        //synchronized (this) {
            this->wait(LnTurnout::METERINTERVAL + 25);
        //}

        // check for messages
        Assert::assertTrue("just one messages", lnis->outbound.size() == 1, __FILE__, __LINE__);
        Assert::assertEquals(lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(),
                "B0 14 10 00", __FILE__, __LINE__);  // THROWN/ON loconet message
        Assert::assertTrue(t->getCommandedState() == Turnout::THROWN, __FILE__, __LINE__);
    }

    // test that only one message is sent when property SendOnAndOff is false.
    //@Test
    /*public*/ void LnTurnoutTest::testPropertySet() throw (InterruptedException) {
       t->setBinaryOutput(false);
       t->setProperty(LnTurnoutManager::SENDONANDOFFKEY, false);
       t->setCommandedState(Turnout::THROWN);

        // Make sure that timed message has fired by waiting
        //synchronized (this) {
            this->wait(LnTurnout::METERINTERVAL + 25);
        //}

        // check for messages
        Assert::assertTrue("just one messages", lnis->outbound.size() == 1, __FILE__, __LINE__);
        Assert::assertEquals(lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(),
                "B0 14 10 00", __FILE__, __LINE__);  // THROWN/ON loconet message
        Assert::assertTrue(t->getCommandedState() == Turnout::THROWN, __FILE__, __LINE__);
    }

    // test that only two messages are sent when property SendOnAndOff is true.
    //@Test
    /*public*/ void LnTurnoutTest::testPropertySet1() throw (InterruptedException) {
       t->setBinaryOutput(false);
       t->setProperty(LnTurnoutManager::SENDONANDOFFKEY, true);
       t->setCommandedState(Turnout::THROWN);

        // Make sure that timed message has fired by waiting
        //synchronized (this) {
            this->wait(LnTurnout::METERINTERVAL + 25);
        //}

        // check for messages
        Assert::assertTrue("just two messages", lnis->outbound.size() == 2, __FILE__, __LINE__);
        Assert::assertEquals(lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(),
                "B0 14 00 00", __FILE__, __LINE__);  // THROWN/OFF loconet message
        Assert::assertTrue(t->getCommandedState() == Turnout::THROWN, __FILE__, __LINE__);
    }

    // test that only two messages are sent when property SendOnAndOff is true, even if (ulenbook) binary set.
    //@Test
    /*public*/ void LnTurnoutTest::testPropertySet2() throw (InterruptedException) {
       t->setBinaryOutput(true);
       t->setProperty(LnTurnoutManager::SENDONANDOFFKEY, true);
       t->setCommandedState(Turnout::THROWN);

        // Make sure that timed message has fired by waiting
        //synchronized (this) {
            this->wait(LnTurnout::METERINTERVAL + 25);
        //}

        // check for messages
        Assert::assertTrue("just two messages", lnis->outbound.size() == 2, __FILE__, __LINE__);
        Assert::assertEquals(lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(),
                "B0 14 00 00", __FILE__, __LINE__);  // THROWN/OFF loconet message
        Assert::assertTrue(t->getCommandedState() == Turnout::THROWN, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutTest::testTurnoutLocks() {
        Assert::assertFalse("check t.canLock (Turnout::CABLOCKOUT)",t->canLock(Turnout::CABLOCKOUT), __FILE__, __LINE__);
        Assert::assertFalse("check t.canLock (Turnout::PUSHBUTTONLOCKOUT)",t->canLock(Turnout::PUSHBUTTONLOCKOUT), __FILE__, __LINE__);

        Assert::assertFalse("check turnoutPushbuttonLockout(false) is false 1", lnt->getLocked(Turnout::PUSHBUTTONLOCKOUT), __FILE__, __LINE__);
        Assert::assertFalse("check turnoutPushbuttonLockout(false) is false 2", lnt->getLocked (Turnout::CABLOCKOUT), __FILE__, __LINE__);
        Assert::assertFalse("check turnoutPushbuttonLockout(false) is false 3", lnt->getLocked (Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT), __FILE__, __LINE__);
        lnt->turnoutPushbuttonLockout(false);
        Assert::assertFalse("check turnoutPushbuttonLockout(false) is false 4", lnt->getLocked (Turnout::PUSHBUTTONLOCKOUT), __FILE__, __LINE__);
        Assert::assertFalse("check turnoutPushbuttonLockout(false) is false 5", lnt->getLocked (Turnout::CABLOCKOUT), __FILE__, __LINE__);
        Assert::assertFalse("check turnoutPushbuttonLockout(false) is false 6", lnt->getLocked (Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT), __FILE__, __LINE__);
        lnt->turnoutPushbuttonLockout(true);
        Assert::assertFalse("check turnoutPushbuttonLockout(false) is false 7", lnt->getLocked (Turnout::PUSHBUTTONLOCKOUT), __FILE__, __LINE__);
        Assert::assertFalse("check turnoutPushbuttonLockout(false) is false 8", lnt->getLocked (Turnout::CABLOCKOUT), __FILE__, __LINE__);
        Assert::assertFalse("check turnoutPushbuttonLockout(false) is false 9", lnt->getLocked (Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutTest::testMessageFromManagerWrongType() {
        Assert::assertEquals("check default known state", Turnout::UNKNOWN, t->getKnownState(), __FILE__, __LINE__);
        Assert::assertEquals("check default commanded state", Turnout::UNKNOWN, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xd0<< 0x00<< 0x00<< 0x00<< 0x00<< 0x00));
        Assert::assertEquals("check default known state", Turnout::UNKNOWN, t->getKnownState(), __FILE__, __LINE__);
        Assert::assertEquals("check default commanded state", Turnout::UNKNOWN, t->getKnownState(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutTest::testMyAddress() {
        LocoNetMessage* m;
        Assert::assertEquals("get initial turnout 21 known state as Turnout::UNKNOWN", Turnout::UNKNOWN, lnt->getKnownState(), __FILE__, __LINE__);
        Assert::assertEquals("get initial turnout 21 commanded state as Turnout::UNKNOWN", Turnout::UNKNOWN, lnt->getCommandedState(), __FILE__, __LINE__);

        m = new LocoNetMessage(QVector<int>()<<0xb0<< 0x0<< 0x30<< 00);
        for (int i=0; i < 2048; ++i) {
            if (i != 20) {
            m->setElement(1, i&0x7f); m->setElement(2, ((i>>7)&0xf)+0x30);
            lnt->messageFromManager(m);
            Assert::assertEquals("check turnout 21 known state after message turnout "+QString::number(i)+" Turnout::UNKNOWN.", Turnout::UNKNOWN, lnt->getKnownState(), __FILE__, __LINE__);
            Assert::assertEquals("check turnout 21 commanded state after message turnout "+QString::number(i)+" Turnout::UNKNOWN.", Turnout::UNKNOWN, lnt->getCommandedState(), __FILE__, __LINE__);
            }
        }
        Assert::assertEquals("get final turnout 21 known state after bunch of opc_sw_req messages", Turnout::UNKNOWN, lnt->getKnownState(), __FILE__, __LINE__);
        Assert::assertEquals("get final turnout 21 commanded state after bunch of opc_sw_req messages", Turnout::UNKNOWN, lnt->getCommandedState(), __FILE__, __LINE__);

        m->setElement(1, 20&0x7f); m->setElement(2, ((20>>7)&0xf)+0x30);
        lnt->messageFromManager(m);
        Assert::assertEquals("check turnout 21 known state Turnout::CLOSED after opc_sw_req message turnout 20 Turnout::CLOSED.", Turnout::CLOSED, lnt->getKnownState(), __FILE__, __LINE__);
        Assert::assertEquals("check turnout 21 commanded state Turnout::CLOSED after opc_sw_req message turnout 20 Turnout::CLOSED.", Turnout::CLOSED, lnt->getCommandedState(), __FILE__, __LINE__);

        // same basic test using OPC_SW_REQ (output report form)

        m = new LocoNetMessage(QVector<int>()<<0xb1<< 0x0<< 0x00<< 00);
        for (int i=0; i < 2048; ++i) {
            if (i != 20) {
            m->setElement(1, i&0x7f); m->setElement(2, ((i>>7)&0xf)+0x10);
            lnt->messageFromManager(m);
            Assert::assertEquals("check turnout 21 known state after opc_sw_rep (output rep) message turnout "+QString::number(i)+" thrown.", Turnout::CLOSED, lnt->getKnownState(), __FILE__, __LINE__);
            Assert::assertEquals("check turnout 21 commanded state after opc_sw_rep (output rep) message turnout "+QString::number(i)+" thrown.", Turnout::CLOSED, lnt->getCommandedState(), __FILE__, __LINE__);
            }
        }
        Assert::assertEquals("get turnout 21 known state after bunch of opc_sw_rep (output rep) messages", Turnout::CLOSED, lnt->getKnownState(), __FILE__, __LINE__);
        Assert::assertEquals("get turnout 21 commanded state after bunch of opc_sw_rep (output rep) messages", Turnout::CLOSED, lnt->getCommandedState(), __FILE__, __LINE__);

        m->setElement(1, 20&0x7f); m->setElement(2, ((20>>7)&0xf)+0x10);
        lnt->messageFromManager(m);
        Assert::assertEquals("check turnout 21 known state Turnout::CLOSED after opc_sw_req message turnout 21 thrown.", Turnout::THROWN, lnt->getKnownState(), __FILE__, __LINE__);
        Assert::assertEquals("check turnout 21 commanded state Turnout::CLOSED after opc_sw_req message turnout 21 thrown.", Turnout::THROWN, lnt->getCommandedState(), __FILE__, __LINE__);

        m->setElement(1, 20&0x7f); m->setElement(2, ((20>>7)&0xf)+0x30);
        lnt->messageFromManager(m);
        Assert::assertEquals("check turnout 21 known state Turnout::CLOSED after opc_sw_req message turnout 21 Turnout::CLOSED+thrown.", Turnout::THROWN + Turnout::CLOSED, lnt->getKnownState(), __FILE__, __LINE__);
        Assert::assertEquals("check turnout 21 commanded state Turnout::CLOSED+thrown after opc_sw_req message turnout 21 Turnout::CLOSED+thrown.", Turnout::THROWN + Turnout::CLOSED, lnt->getCommandedState(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutTest::testCtorNumberOutOfBounds() {
        LnTurnout* t;
        bool excep = false;
        try {
            t = new LnTurnout("L", 0, lnis);
        } catch (IllegalArgumentException e) {
            excep = true;
        }
        Assert::assertTrue("expected exception happened (1)", excep, __FILE__, __LINE__);

        excep = false;
        try {
            t = new LnTurnout("L", 2049, lnis);
        } catch (IllegalArgumentException e) {
            excep = true;
        }
        Assert::assertTrue("expected exception happened (2)", excep, __FILE__, __LINE__);

        excep = false;
        int value = -999;
        try {
            t = new LnTurnout("L", 2048, lnis);
            value = t->_number;
        } catch (IllegalArgumentException e) {
            excep = true;
        }
        Assert::assertFalse("exception did not happen (3)", excep, __FILE__, __LINE__);
        Assert::assertEquals("check t has number", 2048, value, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutTest::testSetFeedback() {
        bool excep = false;
        try {
            t->setFeedbackMode("poSitive");
        } catch (IllegalArgumentException e) {
            excep = true;
        }
        Assert::assertTrue("expected illegal argument exception happened (1)", excep, __FILE__, __LINE__);

        excep = false;
        try {
            t->setFeedbackMode("NEGATIVE");
        } catch (IllegalArgumentException e) {
            excep = true;
        }
        Assert::assertTrue("expected illegal argument exception happened (2)", excep, __FILE__, __LINE__);

        excep = false;
        try {
            t->setFeedbackMode("DIRECT");
        } catch (IllegalArgumentException e) {
            excep = true;
        }
        Assert::assertFalse("Did not expect or get an exception (3)", excep, __FILE__, __LINE__);
        Assert::assertEquals("Check direct feedback mode set (3)", "DIRECT", t->getFeedbackModeName(), __FILE__, __LINE__);

        try {
            t->setFeedbackMode("MONITORING");
        } catch (IllegalArgumentException e) {
            excep = true;
        }
        Assert::assertFalse("Did not expect or get an exception (4)", excep, __FILE__, __LINE__);
        Assert::assertEquals("Check direct feedback mode set (4)", "MONITORING", t->getFeedbackModeName(), __FILE__, __LINE__);

        try {
            t->setFeedbackMode("EXACT");
        } catch (IllegalArgumentException e) {
            excep = true;
        }
        Assert::assertFalse("Did not expect or get an exception (5)", excep, __FILE__, __LINE__);
        Assert::assertEquals("Check direct feedback mode set (5)", "EXACT", t->getFeedbackModeName(), __FILE__, __LINE__);

        try {
            t->setFeedbackMode("INDIRECT");
        } catch (IllegalArgumentException e) {
            excep = true;
        }
        Assert::assertFalse("Did not expect or get an exception (6)", excep, __FILE__, __LINE__);
        Assert::assertEquals("Check direct feedback mode set (6)", "INDIRECT", t->getFeedbackModeName(), __FILE__, __LINE__);

        try {
            t->setFeedbackMode("ONESENSOR");
        } catch (IllegalArgumentException e) {
            excep = true;
        }
        Assert::assertFalse("Did not expect or get an exception (7)", excep, __FILE__, __LINE__);
        Assert::assertEquals("Check direct feedback mode set (7)", "ONESENSOR", t->getFeedbackModeName(), __FILE__, __LINE__);

        JUnitAppender::assertWarnMessage("expected Sensor 1 not defined - LT21",__FILE__, __LINE__);


        try {
            t->setFeedbackMode("TWOSENSOR");
        } catch (IllegalArgumentException e) {
            excep = true;
        }
        Assert::assertFalse("Did not expect or get an exception (8)", excep, __FILE__, __LINE__);
        Assert::assertEquals("Check direct feedback mode set (8)", "TWOSENSOR", t->getFeedbackModeName(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("expected Sensor 1 not defined - LT21",__FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("expected Sensor 2 not defined - LT21",__FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutTest::testGetNumber() {
        Assert::assertEquals("check test's default turnout address nubmer", 21, lnt->getNumber(), __FILE__, __LINE__);
        LnTurnout* t2 = new LnTurnout("L", 5, lnis);
        Assert::assertEquals("check test's default turnout address nubmer", 5, t2->getNumber(), __FILE__, __LINE__);
        t2 = new LnTurnout("L", 2047, lnis);
        Assert::assertEquals("check test's default turnout address nubmer", 2047, t2->getNumber(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutTest::testSetUseOffSwReqAsConfirmation() {
        Assert::assertFalse("check default offSwReqAsConfirmation", lnt->_useOffSwReqAsConfirmation, __FILE__, __LINE__);
        lnt->setUseOffSwReqAsConfirmation(true);
        Assert::assertTrue("check first offSwReqAsConfirmation", lnt->_useOffSwReqAsConfirmation, __FILE__, __LINE__);
        lnt->setUseOffSwReqAsConfirmation(false);
        Assert::assertFalse("check first offSwReqAsConfirmation", lnt->_useOffSwReqAsConfirmation, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutTest::testSetStateClosedAndThrown() {
        Assert::assertEquals("checking initial known state", Turnout::UNKNOWN, t->getKnownState(), __FILE__, __LINE__);
        t->setCommandedState(Turnout::CLOSED + Turnout::THROWN);
        JUnitAppender::assertErrorMessage("LocoNet turnout logic can't handle both THROWN and CLOSED yet",__FILE__, __LINE__);
        Assert::assertEquals("checking commanded state is Turnout::UNKNOWN after trying to send THROWN AND Turnout::CLOSED", Turnout::UNKNOWN, t->getKnownState(), __FILE__, __LINE__);
        Assert::assertEquals("checking known state is Turnout::UNKNOWN after trying to send THROWN AND Turnout::CLOSED", Turnout::UNKNOWN, t->getKnownState(), __FILE__, __LINE__);
        Assert::assertEquals("Checking to see if a LocoNet message was generated", 1, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("Check OpCode", 0xb0, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
        Assert::assertEquals("Check byte 1", 0x14, lnis->outbound.at(0)->getElement(1), __FILE__, __LINE__);
        Assert::assertEquals("Check byte 2", 0x30, lnis->outbound.at(0)->getElement(2), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutTest::testWarningSendingOffWhenUsingOffAsConfirmation() {
        lnt->_useOffSwReqAsConfirmation = true;
        lnt->sendOpcSwReqMessage(Turnout::CLOSED, false);
        JUnitAppender::assertWarnMessage("Turnout 21 is using OPC_SWREQ off as confirmation, but is sending OFF commands itself anyway",__FILE__, __LINE__);
        Assert::assertEquals("check message sent", 1, lnis->outbound.size(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutTest::testFeedbackLateResend() {
        lnt->setFeedbackMode("INDIRECT");
        lnt->_useOffSwReqAsConfirmation=true;
        lnt->setCommandedState(Turnout::CLOSED);
        Assert::assertEquals("check message sent", 1, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check known state before feedback received", Turnout::UNKNOWN, t->getKnownState(), __FILE__, __LINE__);
        Assert::assertEquals("check initial message Opcode", 0xB0, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
        Assert::assertEquals("check initial message element 1", 20, lnis->outbound.at(0)->getElement(1), __FILE__, __LINE__);
        Assert::assertEquals("check initial message element 2", 0x30, lnis->outbound.at(0)->getElement(2), __FILE__, __LINE__);
        //JUnitUtil.waitFor(()->{return lnis->outbound.size()==2;},"2nd message not received");
        ReleaseUntilO7* r07 = new ReleaseUntilO7(2, this);
        JUnitUtil::waitFor(r07, "2nd message not received", __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Turnout 21 is using OPC_SWREQ off as confirmation, but is sending OFF commands itself anyway",__FILE__, __LINE__);
        Assert::assertEquals("check second message Opcode", 0xB0, lnis->outbound.at(1)->getOpCode(), __FILE__, __LINE__);
        Assert::assertEquals("check second message element 1", 20, lnis->outbound.at(1)->getElement(1), __FILE__, __LINE__);
        Assert::assertEquals("check second message element 2", 0x20, lnis->outbound.at(1)->getElement(2), __FILE__, __LINE__);
        //JUnitUtil.waitFor(()->{return lnis->outbound.size()==3;},"3rd message not received");
        r07 = new ReleaseUntilO7(3, this);
        JUnitUtil::waitFor(r07, "2nd message not received", __FILE__, __LINE__);
        // check for resend of original message
        Assert::assertEquals("check second message Opcode", 0xB0, lnis->outbound.at(2)->getOpCode(), __FILE__, __LINE__);
        Assert::assertEquals("check second message element 1", 20, lnis->outbound.at(2)->getElement(1), __FILE__, __LINE__);
        Assert::assertEquals("check second message element 2", 0x30, lnis->outbound.at(2)->getElement(2), __FILE__, __LINE__);
        Assert::assertEquals("check known state got updated", Turnout::UNKNOWN, t->getKnownState(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutTest::testFeedbackLateResendAborted() {
        lnt->setFeedbackMode("INDIRECT");
        lnt->_useOffSwReqAsConfirmation=true;
        lnt->setCommandedState(Turnout::CLOSED);
        Assert::assertEquals("check message sent (2)", 1, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check known state before feedback received (2)", Turnout::UNKNOWN, t->getKnownState(), __FILE__, __LINE__);
        Assert::assertEquals("check initial message Opcode (2)", 0xB0, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
        Assert::assertEquals("check initial message element 1 (2)", 20, lnis->outbound.at(0)->getElement(1), __FILE__, __LINE__);
        Assert::assertEquals("check initial message element 2 (2)", 0x30, lnis->outbound.at(0)->getElement(2), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xB1<< 0x14<< 0x60<< 0x00));
        Assert::assertEquals("check known state got updated", Turnout::THROWN, t->getKnownState(), __FILE__, __LINE__);
        //JUnitUtil.waitFor(()->{return lnis->outbound.size()==2;},"2nd message not received (2)");
        ReleaseUntilO7* r07 = new ReleaseUntilO7(2, this);
        JUnitUtil::waitFor(r07,"2nd message not received (2)", __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Turnout 21 is using OPC_SWREQ off as confirmation, but is sending OFF commands itself anyway",__FILE__, __LINE__);
        Assert::assertEquals("check second message Opcode", 0xB0, lnis->outbound.at(1)->getOpCode(), __FILE__, __LINE__);
        Assert::assertEquals("check second message element 1", 20, lnis->outbound.at(1)->getElement(1), __FILE__, __LINE__);
        Assert::assertEquals("check second message element 2", 0x20, lnis->outbound.at(1)->getElement(2), __FILE__, __LINE__);
        JUnitUtil::waitFor(3500);
        Assert::assertEquals("still only 2 sent messages", 2, lnis->outbound.size(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutTest::testComputeKnownStateOpSwAckReq() {
        lnt->setFeedbackMode("DIRECT");
        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb0<< 0x14<< 0x20<< 0x00));
        Assert::assertEquals("check message sent(1)", 0, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check known state after echoed (1)", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb0<< 0x14<< 0x00<< 0x00));
        Assert::assertEquals("check message sent(2)", 0, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check known state after echoed (2)", Turnout::THROWN, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb0<< 0x14<< 0x30<< 0x00));
        Assert::assertEquals("check message sent(3)", 0, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check known state after echoed (3)", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb0<< 0x14<< 0x10<< 0x00));
        Assert::assertEquals("check message sent(4)", 0, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check known state after echoed (4)", Turnout::THROWN, t->getKnownState(), __FILE__, __LINE__);

        lnt->setFeedbackMode("MONITORING");
        lnt->_useOffSwReqAsConfirmation = true;
        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb0<< 0x14<< 0x30<< 0x00));
        Assert::assertEquals("check message sent(5)", 0, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check known state after echoed (5)", Turnout::THROWN, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb0<< 0x14<< 0x20<< 0x00));
        Assert::assertEquals("check message sent(6)", 0, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check known state after echoed (6)", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb0<< 0x14<< 0x10<< 0x00));
        Assert::assertEquals("check message sent(7)", 0, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check known state after echoed (7)", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb0<< 0x14<< 0x00<< 0x00));
        Assert::assertEquals("check message sent(8)", 0, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check known state after echoed (8)", Turnout::THROWN, t->getKnownState(), __FILE__, __LINE__);

        lnt->setFeedbackMode("INDIRECT");
        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb0<< 0x14<< 0x10<< 0x00));
        Assert::assertEquals("check message sent(9)", 0, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check known state after echoed (9)", Turnout::THROWN, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb0<< 0x14<< 0x00<< 0x00));
        Assert::assertEquals("check message sent(10)", 0, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check known state after echoed (10)", Turnout::THROWN, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb0<< 0x14<< 0x10<< 0x00));
        Assert::assertEquals("check message sent(11)", 0, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check known state after echoed (11)", Turnout::THROWN, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb0<< 0x14<< 0x00<< 0x00));
        Assert::assertEquals("check message sent(12)", 0, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check known state after echoed (12)", Turnout::THROWN, t->getKnownState(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutTest::testSetKnownStateFromOutputStateReport() {
        lnt->setFeedbackMode("DIRECT");
        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x00<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", 0, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x10<< 0x00));
        Assert::assertEquals("check known state after message (1)", Turnout::THROWN, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x20<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x30<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", Turnout::THROWN+Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt->setFeedbackMode("INDIRECT");
        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x00<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", Turnout::THROWN+Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x10<< 0x00));
        Assert::assertEquals("check known state after message (1)", Turnout::THROWN+Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x20<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", Turnout::THROWN+Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x30<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", Turnout::THROWN+Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt->setFeedbackMode("MONITORING");
        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x00<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", 0, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x10<< 0x00));
        Assert::assertEquals("check known state after message (1)", Turnout::THROWN, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x20<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x30<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", Turnout::THROWN+Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void LnTurnoutTest::testComputeFeedbackFromSwitchOffReport() {
        lnt->setFeedbackMode("INDIRECT");
        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x40<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", Turnout::UNKNOWN, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x50<< 0x00));
        Assert::assertEquals("check known state after message (1)", Turnout::UNKNOWN, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x60<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", Turnout::THROWN, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x70<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x40<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x50<< 0x00));
        Assert::assertEquals("check known state after message (1)", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt->setFeedbackMode("EXACT");
        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x60<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", Turnout::INCONSISTENT, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x40<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", Turnout::INCONSISTENT, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x50<< 0x00));
        Assert::assertEquals("check known state after message (1)", Turnout::THROWN, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x14<< 0x70<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt = new LnTurnout("L", 22, lnis);
        lnt->setFeedbackMode("MONITORING");
        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x15<< 0x60<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x15<< 0x40<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x15<< 0x50<< 0x00));
        Assert::assertEquals("check known state after message (1)", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x15<< 0x70<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        lnt = new LnTurnout("L", 23, lnis);
        lnt->messageFromManager(new LocoNetMessage(QVector<int>()<<0xb1<< 0x16<< 0x60<< 0x00 ));
        Assert::assertEquals("check known state after message (1)", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutTest::testAdjustStateForInversion() {
        Assert::assertFalse("check default inversion", lnt->getInverted(), __FILE__, __LINE__);
        lnt->setBinaryOutput(true);
        lnt->setUseOffSwReqAsConfirmation(false);
        lnt->setCommandedState(Turnout::CLOSED);
        Assert::assertEquals("check commanded state after forward Turnout::CLOSED to layout (1)", Turnout::CLOSED, t->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("check num messages sent after forward Turnout::CLOSED to layout (1)",1, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check byte 2 of message (1)", 0x30, lnis->outbound.at(0)->getElement(2), __FILE__, __LINE__);

        lnt->setCommandedState(Turnout::THROWN);
        Assert::assertEquals("check commanded state after forward thrown to layout (2)", Turnout::THROWN, t->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("check num messages sent after forward thrown to layout (2)",2, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check byte 2 of message (2)", 0x10, lnis->outbound.at(1)->getElement(2), __FILE__, __LINE__);

        lnt->setInverted(true);
        // when inverted, the commanded state remains unmodified; only the LocoNet
        // message sent gets state inverted.
        lnt->setCommandedState(Turnout::THROWN);
        Assert::assertEquals("check commanded state after forward Turnout::CLOSED to layout (3)", Turnout::THROWN, t->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("check num messages sent after forward Turnout::CLOSED to layout (3)",3, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check byte 2 of message (1)", 0x30, lnis->outbound.at(2)->getElement(2), __FILE__, __LINE__);

        lnt->setCommandedState(Turnout::CLOSED);
        Assert::assertEquals("check commanded state after forward thrown to layout (4)", Turnout::CLOSED, t->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("check num messages sent after forward thrown to layout (4)",4, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check byte 2 of message (2)", 0x10, lnis->outbound.at(3)->getElement(2), __FILE__, __LINE__);

    }

    //@Override
    //@Before
    /*public*/ void LnTurnoutTest::setUp() {
        JUnitUtil::setUp();
        // prepare an interface
        memo = new LocoNetSystemConnectionMemo("L", "LocoNet");
        lnis = new LocoNetInterfaceScaffold(memo);
        memo->setLnTrafficController(lnis);

        // outwait any pending delayed sends
//        try {
//            synchronized (this) {
                this->wait(LnTurnout::METERINTERVAL + 25);
//            }
//        } catch (InterruptedException e) {
//        }

        // create object under test
        t = new LnTurnout("L", 21, lnis);
        lnt=(LnTurnout*) t;
    }

    //@After
    /*public*/ void LnTurnoutTest::tearDown(){
        t->dispose();
        JUnitUtil::tearDown();
    }

    /*private*/
    void LnTurnoutTest::wait(int msecs)
    {
        QTime dieTime= QTime::currentTime().addMSecs(msecs);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    /*private*/ /*final*/ /*static*/ Logger* LnTurnoutTest::log = LoggerFactory::getLogger("LnTurnoutTest");
