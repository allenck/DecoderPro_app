#include "internalturnoutmanagertest.h"
#include "assert1.h"
#include "instancemanager.h"
#include "junitutil.h"

/**
 * Tests for the jmri.jmrix.interna_manager->InternalTurnoutManager class.
 *
 * @author Bob Jacobsen Copyright 2016
 */
// /*public*/  class InternalTurnoutManagerTest extends jmri.managers.AbstractTurnoutMgrTestBase {

    //@Override
    /*public*/  QString InternalTurnoutManagerTest::getSystemName(int i) {
        return "IT" + QString::number(i);
    }

    //@Override
    /*protected*/ QString InternalTurnoutManagerTest::getASystemNameWithNoPrefix() {
        return "My Turnout 6";
    }

    //@test
    /*public*/  void InternalTurnoutManagerTest::testAsAbstractFactory() {

        // ask for a Turnout, and check type
        Turnout* tl = l->newTurnout("IT21", "my name");

        Assert::assertNotNull(tl, __FILE__, __LINE__);

        // make sure loaded into tables
        Assert::assertNotNull((QObject*)l->getBySystemName("IT21"), __FILE__, __LINE__);
        Assert::assertNotNull((QObject*)l->getByUserName("my name"), __FILE__, __LINE__);
    }

    //@test
    /*public*/  void InternalTurnoutManagerTest::testCaseMatters() {
        QList<NamedBean*> list = QList<NamedBean*>();

        NamedBean* tn1a = l->provide("name1");
        Assert::assertNotNull((QObject*)tn1a, __FILE__, __LINE__);
        list.append(tn1a);

        // a test with specific system prefix attached (could get from this.getSystemName(1))
        NamedBean* tn1b = l->provide("ITname1"); // meant to be same, note type-specific
        Assert::assertNotNull((QObject*)tn1a, __FILE__, __LINE__);
        list.append(tn1b);
        Assert::assertEquals("tn1a and tn1b didn't match", tn1a, tn1b, __FILE__, __LINE__);

        // case is checked
        NamedBean* tN1 = l->provide("NAME1");
        Assert::assertNotNull((QObject*)tn1a, __FILE__, __LINE__);
        list.append(tN1);
// TODO       Assert::assertNotSame("tn1a doesn't match tN1, case not handled right", tn1a, tN1, __FILE__, __LINE__);

        // spaces fine, kept
        NamedBean* tSpaceM  = l->provide("NAME 1");
        Assert::assertFalse("tSPaceM not unique", list.contains(tSpaceM), __FILE__, __LINE__);
        Assert::assertNotNull((QObject*)tSpaceM, __FILE__, __LINE__);
        list.append(tSpaceM);

        NamedBean* tSpaceMM = l->provide("NAME  1");
        Assert::assertFalse("tSpaceMM not unique", list.contains(tSpaceMM), __FILE__, __LINE__);
        Assert::assertNotNull((QObject*)tSpaceMM, __FILE__, __LINE__);
        list.append(tSpaceMM);

        NamedBean* tSpaceE  = l->provide("NAME 1 ");
        Assert::assertFalse("tSpaceE not unique", list.contains(tSpaceE), __FILE__, __LINE__);
        Assert::assertNotNull((QObject*)tSpaceE, __FILE__, __LINE__);
        list.append(tSpaceE);

        NamedBean* tSpaceEE  = l->provide("NAME 1  ");
        Assert::assertFalse("tSpaceEE not unique", list.contains(tSpaceEE), __FILE__, __LINE__);
        Assert::assertNotNull((QObject*)tSpaceEE, __FILE__, __LINE__);
        list.append(tSpaceEE);

        NamedBean* tSpaceLEE  = l->provide(" NAME 1  ");
        Assert::assertFalse("tSpaceLEE not unique", list.contains(tSpaceLEE), __FILE__, __LINE__);
        Assert::assertNotNull((QObject*)tSpaceLEE, __FILE__, __LINE__);
        list.append(tSpaceLEE);

        NamedBean* tSpaceLLEE  = l->provide("  NAME 1  ");
        Assert::assertFalse("tSpaceLLEE not unique", list.contains(tSpaceLLEE), __FILE__, __LINE__);
        Assert::assertNotNull((QObject*)tSpaceLLEE, __FILE__, __LINE__);
        list.append(tSpaceLLEE);
    }

    //@test
    /*public*/  void InternalTurnoutManagerTest::testFollowingTurnouts() {
//        assumeThat(AbstractTurnout::DELAYED_FEEDBACK_INTERVAL)
//                .as("Turnout delay less than JUnitUnit waitfor max delay")
//                .isLessThan(JUnitUtil::WAITFOR_MAX_DELAY);
        Turnout* t1 = l->provideTurnout("IT1");
        Turnout* t2 = l->provideTurnout("IT2");

        Assert::assertEquals(t1->getKnownState(),Turnout::UNKNOWN, __FILE__, __LINE__);
        Assert::assertEquals(t2->getKnownState(), Turnout::UNKNOWN, __FILE__, __LINE__);
        Assert::assertEquals(t1->getFeedbackMode(), Turnout::DIRECT, __FILE__, __LINE__);
        Assert::assertEquals(t2->getFeedbackMode(), Turnout::DIRECT, __FILE__, __LINE__);
        Assert::assertNull(t1->getLeadingTurnout(), __FILE__, __LINE__);
        Assert::assertNull(t2->getLeadingTurnout(), __FILE__, __LINE__);
        Assert::assertTrue(t1->isFollowingCommandedState(), __FILE__, __LINE__);
        Assert::assertTrue(t2->isFollowingCommandedState(), __FILE__, __LINE__);

        t1->setCommandedState(Turnout::CLOSED);
        Assert::assertEquals(t1->getKnownState(), Turnout::CLOSED, __FILE__, __LINE__);
        Assert::assertEquals(t2->getKnownState(), Turnout::UNKNOWN, __FILE__, __LINE__);

        t2->setLeadingTurnout(t1);
        Assert::assertEquals(t1->getKnownState(), Turnout::CLOSED, __FILE__, __LINE__);
        Assert::assertEquals(t2->getKnownState(), Turnout::UNKNOWN, __FILE__, __LINE__);

        t1->setCommandedState(Turnout::THROWN);
        Assert::assertEquals(t1->getKnownState(), Turnout::THROWN, __FILE__, __LINE__);
        Assert::assertEquals(t2->getKnownState(), Turnout::THROWN, __FILE__, __LINE__);

        t1->setFeedbackMode(Turnout::DELAYED);
        t1->setCommandedState(Turnout::CLOSED);
        Assert::assertEquals(t1->getKnownState(), Turnout::INCONSISTENT, __FILE__, __LINE__);
        Assert::assertEquals(t2->getKnownState(), Turnout::INCONSISTENT, __FILE__, __LINE__);
#if 0
        JUnitUtil::waitFor(() -> t1->getKnownState() == Turnout::CLOSED, __FILE__, __LINE__);
        assertThat(t1->getKnownState(), Turnout::CLOSED/*);*/
        assertThat(t2->getKnownState(), Turnout::CLOSED);

        // verify no stack overflow when following in a circular pattern
        t1->setFeedbackMode(Turnout::DIRECT);
        t1->setLeadingTurnout(t2);
        assertThat(t1->getLeadingTurnout(), t2);
        assertThat(t2->getLeadingTurnout(), t1);
        // will throw stack overflow if not correctly implemented
        t1->setCommandedState(Turnout::THROWN);
        assertThat(t1->getKnownState(), Turnout::THROWN);
        assertThat(t2->getKnownState(), Turnout::THROWN);
        // will throw stack overflow if not correctly implemented
        t2->setCommandedState(Turnout::CLOSED);
        assertThat(t1->getKnownState(), Turnout::CLOSED);
        assertThat(t2->getKnownState(), Turnout::CLOSED);

        // verify
        t1->setFeedbackMode(Turnout::DELAYED);
        t1->setLeadingTurnout(null);
        t2->setFollowingCommandedState(false);
        assertThat(t1->getCommandedState(), Turnout::CLOSED);
        assertThat(t2->getCommandedState(), Turnout::CLOSED);
        t1->setCommandedState(Turnout::THROWN);
        assertThat(t1->getKnownState(), Turnout::INCONSISTENT);
        assertThat(t2->getKnownState(), Turnout::INCONSISTENT);
        JUnitUtil::waitFor(() -> t1->getKnownState() == Turnout::CLOSED);
        assertThat(t1->getKnownState(), Turnout::THROWN);
        assertThat(t2->getKnownState(), Turnout::CLOSED);
#endif
    }

    //@test
    //@Override
    /*public*/  void InternalTurnoutManagerTest::testSetAndGetOutputInterval() {
        Assert::assertEquals("default outputInterval", 250, l->getOutputInterval(), __FILE__, __LINE__);
        l->getMemo()->setOutputInterval(21);
        Assert::assertEquals("new outputInterval in memo", 21, l->getMemo()->getOutputInterval(), __FILE__, __LINE__); // set + get in memo
        Assert::assertEquals("new outputInterval via manager", 21, l->getOutputInterval(), __FILE__, __LINE__); // get via turnoutManager
        l->setOutputInterval(50); // interval set via ProxyTurnoutManager
        Assert::assertEquals("new outputInterval in memo", 50, l->getMemo()->getOutputInterval(), __FILE__, __LINE__); // get directly from memo
        Assert::assertEquals("new outputInterval from manager", 50, l->getOutputInterval(), __FILE__, __LINE__); // get via turnoutManager
    }

    // No manager-specific system name validation at present
    //@test
    //@Override
    /*public*/  void InternalTurnoutManagerTest::testMakeSystemNameWithNoPrefixNotASystemName() {}

    // No manager-specific system name validation at present
    //@test
    //@Override
    /*public*/  void InternalTurnoutManagerTest::testMakeSystemNameWithPrefixNotASystemName() {}

    // No manager-specific system name validation at present
    //@test
    //@Override
    /*public*/  void InternalTurnoutManagerTest::testIncorrectGetNextValidAddress() {}

    // from here down is testing infrastructure
    //@Override
    //@BeforeEach
    /*public*/  void InternalTurnoutManagerTest::setUp() {
        JUnitUtil::setUp();
        // create and register the manager object
        JUnitUtil::resetInstanceManager();
        JUnitUtil::initInternalTurnoutManager();
        _manager = InstanceManager::turnoutManagerInstance();
    }

    //@AfterEach
    /*public*/  void InternalTurnoutManagerTest::tearDown() {
        JUnitUtil::tearDown();
    }

