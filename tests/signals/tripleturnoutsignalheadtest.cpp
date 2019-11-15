#include "tripleturnoutsignalheadtest.h"
#include "junitutil.h"
#include "assert1.h"
#include "turnoutmanager.h"
#include "instancemanager.h"
#include "tripleturnoutsignalhead.h"

TripleTurnoutSignalHeadTest::TripleTurnoutSignalHeadTest()
{

}
/**
 *
 * @author Paul Bender Copyright (C) 2017
 */
///*public*/ class TripleTurnoutSignalHeadTest extends AbstractSignalHeadTestBase {

    //@Test
    /*public*/ void TripleTurnoutSignalHeadTest::testCTor() {
        Turnout*  it = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT1");
        NamedBeanHandle<Turnout*>* green = new NamedBeanHandle<Turnout*>("green handle",it);
        Turnout*  it2 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT3");
        NamedBeanHandle<Turnout*>* red = new NamedBeanHandle<Turnout*>("red handle",it2);
        Turnout*  it3 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT2");
        NamedBeanHandle<Turnout*>* yellow = new NamedBeanHandle<Turnout*>("yellow handle",it3);
        TripleTurnoutSignalHead* t = new TripleTurnoutSignalHead("Test Head",green,red,yellow);
        Assert::assertNotNull("exists",t, __FILE__, __LINE__);
    }

    //@Override
    /*public*/ SignalHead* TripleTurnoutSignalHeadTest::getHeadToTest() {
        Turnout*  it = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT1");
        NamedBeanHandle<Turnout*>* green = new NamedBeanHandle<Turnout*>("green handle",it);
        Turnout*  it2 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT3");
        NamedBeanHandle<Turnout*>* red = new NamedBeanHandle<Turnout*>("red handle",it2);
        Turnout*  it3 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT2");
        NamedBeanHandle<Turnout*>* yellow = new NamedBeanHandle<Turnout*>("yellow handle",it3);
        return new TripleTurnoutSignalHead("Test Head",green,red,yellow);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/ void TripleTurnoutSignalHeadTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::initInternalTurnoutManager();
    }

    //@After
    /*public*/ void TripleTurnoutSignalHeadTest::tearDown() {
        JUnitUtil::tearDown();
    }
