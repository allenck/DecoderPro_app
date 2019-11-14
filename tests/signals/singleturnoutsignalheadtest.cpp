#include "singleturnoutsignalheadtest.h"
#include "junitutil.h"
#include "assert1.h"
#include "turnout.h"
#include "singleturnoutsignalhead.h"
#include "instancemanager.h"

SingleTurnoutSignalHeadTest::SingleTurnoutSignalHeadTest()
{

}
/**
 * Tests for the SingleTurnoutSignalHead implementation
 *
 * @author	Bob Jacobsen Copyright (C) 2010
 */
///*public*/ class SingleTurnoutSignalHeadTest extends AbstractSignalHeadTestBase {

    //@Test
    /*public*/ void SingleTurnoutSignalHeadTest::testNoDarkValidTypes() {
        Turnout* t = InstanceManager::turnoutManagerInstance()->provideTurnout("IT1");
        SingleTurnoutSignalHead* h
                = new SingleTurnoutSignalHead("IH1",
                        new NamedBeanHandle<Turnout*>("IT1", t),
                        SignalHead::GREEN, SignalHead::RED);

        QVector<int> states = h->getValidStates();
        Assert::assertEquals(2, states.length(), __FILE__, __LINE__);
        Assert::assertEquals(SignalHead::GREEN, states[0], __FILE__, __LINE__);
        Assert::assertEquals(SignalHead::RED, states[1], __FILE__, __LINE__);

        QVector<QString> names = h->getValidStateNames();
        Assert::assertEquals(2, names.length(), __FILE__, __LINE__);
        Assert::assertEquals("Green", names[0], __FILE__, __LINE__);
        Assert::assertEquals("Red", names[1], __FILE__, __LINE__);

        h->setAppearance(SignalHead::GREEN);
        Assert::assertEquals(SignalHead::GREEN, h->getAppearance(), __FILE__, __LINE__);
        Assert::assertEquals("Green", h->getAppearanceName(), __FILE__, __LINE__);

        h->setAppearance(SignalHead::RED);
        Assert::assertEquals(SignalHead::RED, h->getAppearance(), __FILE__, __LINE__);
        Assert::assertEquals("Red", h->getAppearanceName(), __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void SingleTurnoutSignalHeadTest::testDarkValidTypes1() {
        Turnout* t = InstanceManager::turnoutManagerInstance()->provideTurnout("IT1");
        SingleTurnoutSignalHead* h
                = new SingleTurnoutSignalHead("IH1",
                        new NamedBeanHandle<Turnout*>("IT1", t),
                        SignalHead::DARK, SignalHead::RED);

        QVector<int> states = h->getValidStates();
        Assert::assertEquals(3, states.length(), __FILE__, __LINE__);
        Assert::assertEquals(SignalHead::DARK, states[0], __FILE__, __LINE__);
        Assert::assertEquals(SignalHead::RED, states[1], __FILE__, __LINE__);
        Assert::assertEquals(SignalHead::FLASHRED, states[2], __FILE__, __LINE__);

        QVector<QString> names = h->getValidStateNames();
        Assert::assertEquals(3, names.length(), __FILE__, __LINE__);
        Assert::assertEquals("Dark", names[0], __FILE__, __LINE__);
        Assert::assertEquals("Red", names[1], __FILE__, __LINE__);
        Assert::assertEquals("Flashing Red", names[2], __FILE__, __LINE__);

        h->setAppearance(SignalHead::DARK);
        Assert::assertEquals(SignalHead::DARK, h->getAppearance(), __FILE__, __LINE__);
        Assert::assertEquals("Dark", h->getAppearanceName(), __FILE__, __LINE__);

        h->setAppearance(SignalHead::FLASHRED);
        Assert::assertEquals(SignalHead::FLASHRED, h->getAppearance(), __FILE__, __LINE__);
        Assert::assertEquals("Flashing Red", h->getAppearanceName(), __FILE__, __LINE__);

        h->setAppearance(SignalHead::RED);   // stops flash timer
        Assert::assertEquals(SignalHead::RED, h->getAppearance(), __FILE__, __LINE__);
        Assert::assertEquals("Red", h->getAppearanceName(), __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void SingleTurnoutSignalHeadTest::testDarkValidTypes2() {
        Turnout* t = InstanceManager::turnoutManagerInstance()->provideTurnout("IT1");
        SingleTurnoutSignalHead* h
                = new SingleTurnoutSignalHead("IH1",
                        new NamedBeanHandle<Turnout*>("IT1", t),
                        SignalHead::GREEN, SignalHead::DARK);

        QVector<int> states = h->getValidStates();
        Assert::assertEquals(3, states.length(), __FILE__, __LINE__);
        Assert::assertEquals(SignalHead::GREEN, states[0], __FILE__, __LINE__);
        Assert::assertEquals(SignalHead::FLASHGREEN, states[1], __FILE__, __LINE__);
        Assert::assertEquals(SignalHead::DARK, states[2], __FILE__, __LINE__);

        QVector<QString> names = h->getValidStateNames();
        Assert::assertEquals(3, names.length(), __FILE__, __LINE__);
        Assert::assertEquals("Green", names[0], __FILE__, __LINE__);
        Assert::assertEquals("Flashing Green", names[1], __FILE__, __LINE__);
        Assert::assertEquals("Dark", names[2], __FILE__, __LINE__);

        h->setAppearance(SignalHead::DARK);
        Assert::assertEquals(SignalHead::DARK, h->getAppearance(), __FILE__, __LINE__);
        Assert::assertEquals("Dark", h->getAppearanceName(), __FILE__, __LINE__);

        h->setAppearance(SignalHead::FLASHGREEN);
        Assert::assertEquals(SignalHead::FLASHGREEN, h->getAppearance(), __FILE__, __LINE__);
        Assert::assertEquals("Flashing Green", h->getAppearanceName(), __FILE__, __LINE__);

        h->setAppearance(SignalHead::GREEN);   // stops flash timer
        Assert::assertEquals(SignalHead::GREEN, h->getAppearance(), __FILE__, __LINE__);
        Assert::assertEquals("Green", h->getAppearanceName(), __FILE__, __LINE__);

    }

    //@Override
    /*public*/ SignalHead* SingleTurnoutSignalHeadTest::getHeadToTest() {
        Turnout* t = InstanceManager::turnoutManagerInstance()->provideTurnout("IT1");
        return new SingleTurnoutSignalHead("IH1",
                        new NamedBeanHandle<Turnout*>("IT1", t),
                        SignalHead::GREEN, SignalHead::DARK);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/ void SingleTurnoutSignalHeadTest::setUp() {
        JUnitUtil::setUp();
    }

    //@After
    /*public*/ void SingleTurnoutSignalHeadTest::tearDown() {
        JUnitUtil::tearDown();
    }
