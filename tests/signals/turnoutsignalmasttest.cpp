#include "turnoutsignalmasttest.h"
#include "junitutil.h"
#include "assert1.h"
#include "turnoutsignalmast.h"
#include "junitappender.h"
#include "turnout.h"

TurnoutSignalMastTest::TurnoutSignalMastTest(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author Paul Bender Copyright (C) 2017
 */
///*public*/ class TurnoutSignalMastTest {

    //@Test
    /*public*/ void TurnoutSignalMastTest::testCTor() {
        TurnoutSignalMast* t = new TurnoutSignalMast("IF$tsm:basic:one-searchlight($1)");
        Assert::assertNotNull("exists",t, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void TurnoutSignalMastTest::testSetAspect() {
        Turnout*  it1 = InstanceManager::turnoutManagerInstance()->provideTurnout("IT1");
        Turnout*  it2 = InstanceManager::turnoutManagerInstance()->provideTurnout("IT2");
        TurnoutSignalMast* t = new TurnoutSignalMast("IF$tsm:basic:one-searchlight($1)");
        t->resetPreviousStates(false);

        t->setTurnout("Stop", "IT1", Turnout::THROWN);
        t->setTurnout("Clear", "IT2", Turnout::CLOSED);

        t->setAspect("Clear");
        Assert::assertEquals("Clear", t->getAspect(), __FILE__, __LINE__);
        Assert::assertEquals(Turnout::UNKNOWN, it1->getCommandedState(), __FILE__, __LINE__); // not thrown
        Assert::assertEquals(Turnout::CLOSED, it2->getCommandedState(), __FILE__, __LINE__);

        t->setAspect("Stop");
        Assert::assertEquals("Stop", t->getAspect(), __FILE__, __LINE__);
        Assert::assertEquals(Turnout::THROWN, it1->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Turnout::CLOSED, it2->getCommandedState(), __FILE__, __LINE__); // unchanged

        // try an unconfigured one
        t->setAspect("Approach");
        JUnitAppender::assertErrorMessage("Trying to set \"Approach\" on signal mast \"IF$tsm:basic:one-searchlight($1)\" which has not been configured", __FILE__, __LINE__);

        try {
            t->setAspect("Marblesnarb");
        } catch (IllegalArgumentException ex) {
            JUnitAppender::assertWarnMessage("attempting to set invalid aspect: Marblesnarb on mast: IF$tsm:basic:one-searchlight($1)", __FILE__, __LINE__);
            return;
        }

        Assert::fail("should have thrown", __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void TurnoutSignalMastTest::testSetAspectResetOthers() {
        Turnout*  it1 = InstanceManager::turnoutManagerInstance()->provideTurnout("IT1");
        Turnout*  it2 = InstanceManager::turnoutManagerInstance()->provideTurnout("IT2");
        TurnoutSignalMast* t = new TurnoutSignalMast("IF$tsm:basic:one-searchlight($1)");
        t->resetPreviousStates(true);

        t->setTurnout("Stop", "IT1", Turnout::THROWN);
        t->setTurnout("Clear", "IT2", Turnout::CLOSED);

        t->setAspect("Clear");
        Assert::assertEquals("Clear", t->getAspect(), __FILE__, __LINE__);
        Assert::assertEquals(Turnout::CLOSED, it1->getCommandedState(), __FILE__, __LINE__); // reset
        Assert::assertEquals(Turnout::CLOSED, it2->getCommandedState(), __FILE__, __LINE__);

        t->setAspect("Stop");
        Assert::assertEquals("Stop", t->getAspect(), __FILE__, __LINE__);
        Assert::assertEquals(Turnout::THROWN, it1->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Turnout::THROWN, it2->getCommandedState(), __FILE__, __LINE__); // reset

        // try an unconfigured but valid one
        t->setAspect("Approach");
        JUnitAppender::assertErrorMessage("Trying to set \"Approach\" on signal mast \"IF$tsm:basic:one-searchlight($1)\" which has not been configured", __FILE__, __LINE__);

        try {
            t->setAspect("Marblesnarb");
        } catch (IllegalArgumentException ex) {
            JUnitAppender::assertWarnMessage("attempting to set invalid aspect: Marblesnarb on mast: IF$tsm:basic:one-searchlight($1)", __FILE__, __LINE__);
            return;
        }

        Assert::fail("should have thrown", __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void TurnoutSignalMastTest::testUnLitNoTurnout() {
        Turnout*  it1 = InstanceManager::turnoutManagerInstance()->provideTurnout("IT1");
        Turnout*  it2 = InstanceManager::turnoutManagerInstance()->provideTurnout("IT2");
        TurnoutSignalMast* t = new TurnoutSignalMast("IF$tsm:basic:one-searchlight($1)");
        t->setTurnout("Stop", "IT1", Turnout::THROWN);
        t->setTurnout("Clear", "IT2", Turnout::THROWN);

        t->setAspect("Clear");
        Assert::assertEquals(true, t->getLit(), __FILE__, __LINE__);

        t->setLit(false);
        Assert::assertEquals(false, t->getLit(), __FILE__, __LINE__);
        Assert::assertEquals("Clear", t->getAspect(), __FILE__, __LINE__);
        Assert::assertEquals(Turnout::CLOSED, it1->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Turnout::CLOSED, it2->getCommandedState(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void TurnoutSignalMastTest::testUnLitWithTurnout() {
        Turnout*  it1 = InstanceManager::turnoutManagerInstance()->provideTurnout("IT1");
        Turnout*  it2 = InstanceManager::turnoutManagerInstance()->provideTurnout("IT2");
        Turnout*  it3 = InstanceManager::turnoutManagerInstance()->provideTurnout("IT3");
        TurnoutSignalMast* t = new TurnoutSignalMast("IF$tsm:basic:one-searchlight($1)");
        t->setTurnout("Stop", "IT1", Turnout::THROWN);
        t->setTurnout("Clear", "IT2", Turnout::THROWN);
        t->setTurnout("Unlit", "IT3", Turnout::THROWN);
        t->setUnLitTurnout("IT3",Turnout::THROWN );

        t->setAspect("Clear");
        Assert::assertEquals(true, t->getLit(), __FILE__, __LINE__);
        Assert::assertEquals(Turnout::UNKNOWN, it1->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Turnout::THROWN, it2->getCommandedState(), __FILE__, __LINE__);

        t->setLit(false);
        Assert::assertEquals(false, t->getLit(), __FILE__, __LINE__);
        Assert::assertEquals("Clear", t->getAspect(), __FILE__, __LINE__);
        Assert::assertEquals(Turnout::UNKNOWN, it1->getCommandedState(), __FILE__, __LINE__);  // Unchanged
        Assert::assertEquals(Turnout::THROWN, it2->getCommandedState(), __FILE__, __LINE__);  // Unchanged
        Assert::assertEquals(Turnout::THROWN, it3->getCommandedState(), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/ void TurnoutSignalMastTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::initInternalTurnoutManager();
    }

    //@After
    /*public*/ void TurnoutSignalMastTest::tearDown() {
        JUnitUtil::tearDown();
    }
