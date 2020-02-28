#include "lnturnoutmanagertest.h"
#include "junitutil.h"
#include "assert1.h"
#include "loconetsystemconnectionmemo.h"
#include "turnout.h"
#include "proxyturnoutmanager.h"
#include "loconetinterfacescaffold.h"
#include "lnturnoutmanager.h"
#include "instancemanager.h"
#include "loggerfactory.h"

LnTurnoutManagerTest::LnTurnoutManagerTest(QObject *parent)
{

}
/**
 * Tests for the jmri.jmrix.loconet.LnTurnoutManager class.
 *
 * @author	Bob Jacobsen Copyright 2005
 */
// /*public*/ class LnTurnoutManagerTest extends jmri.managers.AbstractTurnoutMgrTestBase {

    //@Override
    /*public*/ QString LnTurnoutManagerTest::getSystemName(int i) {
        return "LT" + QString::number(i);
    }

    //@Test
    //@Override
    /*public*/ void LnTurnoutManagerTest::testMisses() {
        // try to get nonexistant turnouts
        Assert::assertTrue(nullptr == l->getByUserName("foo"), __FILE__, __LINE__);
        Assert::assertTrue(nullptr == l->getBySystemName("bar"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutManagerTest::testLocoNetMessages() {
        // send messages for 21, 22
        // notify the Ln that somebody else changed it...
        LocoNetMessage* m1 = new LocoNetMessage(4);
        m1->setOpCode(0xb1);
        m1->setElement(1, 0x14);     // set CLOSED
        m1->setElement(2, 0x20);
        m1->setElement(3, 0x7b);
        lnis->sendTestMessage(m1);

        // notify the Ln that somebody else changed it...
        LocoNetMessage* m2 = new LocoNetMessage(4);
        m2->setOpCode(0xb0);
        m2->setElement(1, 0x15);     // set CLOSED
        m2->setElement(2, 0x20);
        m2->setElement(3, 0x7a);
        lnis->sendTestMessage(m2);

        // try to get turnouts to see if they exist
        Assert::assertNotNull(l->getBySystemName("LT21"), __FILE__, __LINE__);
        Assert::assertNotNull(l->getBySystemName("LT22"), __FILE__, __LINE__);

        // check the list
        QStringList testList = QStringList();
        testList.append("LT21");
        testList.append("LT22");
        Assert::assertEquals("system name list", testList, l->getSystemNameList(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutManagerTest::testCreateFromMessage1 () {
        // Turnout LT61 () Switch input is Closed (input off).
        LocoNetMessage* m = new LocoNetMessage(QVector<int>()<<0xb1<< 0x3C<< 0x70<< 0x02);
        lnis->sendTestMessage(m);
        Assert::assertNotNull(l->getBySystemName("LT61"), __FILE__, __LINE__);
        Assert::assertEquals(Turnout::CLOSED, ((Turnout*)l->getBySystemName("LT61"))->getKnownState(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutManagerTest::testCreateFromMessage2 () {
        // Turnout LT62 () Switch input is Thrown (input on).
        LocoNetMessage* m = new LocoNetMessage(QVector<int>()<<0xb1<< 0x3D<< 0x60<< 0x13);
        lnis->sendTestMessage(m);
        Assert::assertNotNull(l->getBySystemName("LT62"), __FILE__, __LINE__);
        Assert::assertEquals(Turnout::THROWN, ((Turnout*)l->getBySystemName("LT62"))->getKnownState(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutManagerTest::testCreateFromMessage3 () {
        // Turnout LT63 () Aux input is Thrown (input ).
        LocoNetMessage* m = new LocoNetMessage(QVector<int>()<<0xb1<< 0x3E<< 0x40<< 0x30);
        lnis->sendTestMessage(m);
        Assert::assertNotNull(l->getBySystemName("LT63"), __FILE__, __LINE__);
        Assert::assertEquals("EXACT", ((Turnout*)l->getBySystemName("LT63"))->getFeedbackModeName(), __FILE__, __LINE__);
        Assert::assertEquals(Turnout::INCONSISTENT, ((Turnout*)l->getBySystemName("LT63"))->getKnownState(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutManagerTest::testCreateFromMessage4 () {
        // Turnout LT64 () Aux input is Closed (input off).
        LocoNetMessage* m = new LocoNetMessage(QVector<int>()<<0xb1<< 0x3F<< 0x50<< 0x21);
        lnis->sendTestMessage(m);
        Assert::assertNotNull(l->getBySystemName("LT64"), __FILE__, __LINE__);
        Assert::assertEquals("EXACT", ((Turnout*)l->getBySystemName("LT64"))->getFeedbackModeName(), __FILE__, __LINE__);
        Assert::assertEquals(Turnout::THROWN,((Turnout*) l->getBySystemName("LT64"))->getKnownState(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void LnTurnoutManagerTest::testAsAbstractFactory() {
        // ask for a Turnout, and check type
        Turnout* o = l->newTurnout("LT21", "my name");

        log->debug(tr("received turnout value %1").arg(o->getDisplayName()));
        Assert::assertNotNull(o, __FILE__, __LINE__);

        // make sure loaded into tables
        if (log->isDebugEnabled()) {
            log->debug(tr("by system name: %1").arg(l->getBySystemName("LT21")->getDisplayName()));
        }
        if (log->isDebugEnabled()) {
            log->debug(tr("by user name:   %1").arg(l->getByUserName("my name")->getDisplayName()));
        }

        Assert::assertNotNull(l->getBySystemName("LT21"), __FILE__, __LINE__);
        Assert::assertNotNull(l->getByUserName("my name"), __FILE__, __LINE__);
    }

        //@Test
    /*public*/ void LnTurnoutManagerTest::testOpcLongAck() {
        Assert::assertEquals("Check no outbound messages", 0, lnis->outbound.size(), __FILE__, __LINE__);
        ((LnTurnoutManager*)l)->mTurnoutNoRetry=false;

        Turnout* t = ((LnTurnoutManager*)l)->provideTurnout("LT1");   // createNewTurnout does not register it.
        LocoNetMessage* m = new LocoNetMessage(QVector<int>()<<0xb0<< 0x00<< 0x20<< 0x6f);
        lnis->sendTestMessage(m);
        Assert::assertEquals("check now closed", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);
        Assert::assertEquals("Check no outbound messages", 0, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertNotNull(((LnTurnoutManager*)l)->lastSWREQ, __FILE__, __LINE__);
        Assert::assertEquals(LnConstants::OPC_SW_REQ, ((LnTurnoutManager*)l)->lastSWREQ->getOpCode(), __FILE__, __LINE__);
        Assert::assertEquals(0x00, ((LnTurnoutManager*)l)->lastSWREQ->getElement(1), __FILE__, __LINE__);
        Assert::assertEquals(0x20, ((LnTurnoutManager*)l)->lastSWREQ->getElement(2), __FILE__, __LINE__);

        Assert::assertEquals("Check no outbound messages", 0, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("Check that the turnout message was saved as 'last'",
                m, ((LnTurnoutManager*)l)->lastSWREQ, __FILE__, __LINE__);
        lnis->sendTestMessage(m);    // command station rejection of turnout command
        m->setOpCode(0xB4);
        m->setElement(1, 0x30);
        m->setElement(2, 0x00);
        m->setElement(3, 0x7b);
        Assert::assertEquals("check sent message opcode", 0xb4, m->getOpCode(), __FILE__, __LINE__);
        lnis->sendTestMessage(m);    // command station rejection of turnout command
        Assert::assertEquals("Check one outbound messages", 1, lnis->outbound.size(), __FILE__, __LINE__);
        Assert::assertEquals("check now closed (2)", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        Assert::assertFalse("check turnout manager retry mechanism setting", ((LnTurnoutManager*)l)->mTurnoutNoRetry, __FILE__, __LINE__);

//        jmri.util.JUnitUtil.fasterWaitFor(() -> {return 1 < lnis->outbound.size();});
        Assert::assertEquals("Check an outbound message", 1, lnis->outbound.size(), __FILE__, __LINE__);

        Assert::assertEquals("Check outbound message opcode", LnConstants::OPC_SW_REQ, lnis->outbound.at(0)->getOpCode(), __FILE__, __LINE__);
        Assert::assertEquals("Check outbound message byte 1", 0x00, lnis->outbound.at(0)->getElement(1), __FILE__, __LINE__);
        Assert::assertEquals("Check outbound message byte 2", 0x20, lnis->outbound.at(0)->getElement(2), __FILE__, __LINE__);
    }

    ////@Override
    //@Before
    /*public*/ void LnTurnoutManagerTest::setUp(){
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        // prepare an interface, register
        memo = new LocoNetSystemConnectionMemo();
        lnis = new LocoNetInterfaceScaffold(memo);
        memo->setLnTrafficController(lnis);
        // create and register the manager object
#if 1
        l = new LnTurnoutManager(memo, lnis, false);
        InstanceManager::setTurnoutManager(l);
#endif
    }

    //@After
    /*public*/ void LnTurnoutManagerTest::tearDown() {
        memo->dispose();
        lnis = nullptr;
        l = nullptr;
        JUnitUtil::tearDown();
    }

   /*private*/ /*final*/ /*static*/ Logger* LnTurnoutManagerTest::log = LoggerFactory::getLogger("LnTurnoutManagerTest");
