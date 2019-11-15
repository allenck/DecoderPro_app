#include "tripleoutputsignalheadtest.h"
#include "assert1.h"
#include "junitutil.h"
#include "turnout.h"
#include "instancemanager.h"
#include "tripleoutputsignalhead.h"

TripleOutputSignalHeadTest::TripleOutputSignalHeadTest()
{

}
/**
 *
 * @author Paul Bender Copyright (C) 2017
 */
// /*public*/ class TripleOutputSignalHeadTest extends AbstractSignalHeadTestBase {

    //@Test
    /*public*/ void TripleOutputSignalHeadTest::testCTor() {
        Turnout*  it = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT1");
        NamedBeanHandle<Turnout*>* green = new NamedBeanHandle<Turnout*>("green handle",it);
        Turnout*  it2 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT3");
        NamedBeanHandle<Turnout*>* red = new NamedBeanHandle<Turnout*>("red handle",it2);
        Turnout*  it3 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT2");
        NamedBeanHandle<Turnout*>* yellow = new NamedBeanHandle<Turnout*>("yellow handle",it3);
        TripleOutputSignalHead* t = new TripleOutputSignalHead("Test Head",green,red,yellow);
        Assert::assertNotNull("exists",t, __FILE__, __LINE__);
    }

    //@Override
    /*public*/ SignalHead* TripleOutputSignalHeadTest::getHeadToTest() {
        Turnout*  it = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT1");
        NamedBeanHandle<Turnout*>* green = new NamedBeanHandle<Turnout*>("green handle",it);
        Turnout*  it2 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT3");
        NamedBeanHandle<Turnout*>* red = new NamedBeanHandle<Turnout*>("red handle",it2);
        Turnout*  it3 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT2");
        NamedBeanHandle<Turnout*>* yellow = new NamedBeanHandle<Turnout*>("yellow handle",it3);
        return new TripleOutputSignalHead("Test Head",green,red,yellow);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/ void TripleOutputSignalHeadTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::initInternalTurnoutManager();
    }

    //@After
    /*public*/ void TripleOutputSignalHeadTest::tearDown() {
        JUnitUtil::tearDown();
    }
