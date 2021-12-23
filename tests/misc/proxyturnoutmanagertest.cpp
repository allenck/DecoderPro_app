#include "proxyturnoutmanagertest.h"
#include "junitutil.h"
#include"instancemanager.h"
#include "turnoutmanager.h"
#include "assert1.h"
#include "junitappender.h"
#include "proxyturnoutmanager.h"
#include "internalsystemconnectionmemo.h"
#ifdef QT_DEBUG
#include "systemconnectionmemomanager.h"
#endif

ProxyTurnoutManagerTest::ProxyTurnoutManagerTest(QObject *parent) : QObject(parent)
{

}
/**
 * Tests the ProxyTurnoutManager.
 *
 * @author	Bob Jacobsen 2003, 2006, 2008, 2014, 2018
 */
///*public*/ class ProxyTurnoutManagerTest {

/*public*/ QString ProxyTurnoutManagerTest::getSystemName(int i) {
    return "JT" + QString::number(i);
}


/*static*/ /*protected*/ bool ProxyTurnoutManagerTest::listenerResult = false;

///*protected*/ class Listen implements PropertyChangeListener {

    //@Override
    /*public*/ void ListenO5::propertyChange(PropertyChangeEvent* /*e*/) {
        test->listenerResult = true;
    }


//@Test
/*public*/ void ProxyTurnoutManagerTest::testDispose() {
    l->dispose();  // all we're really doing here is making sure the method exists
}

//@Test
/*public*/ void ProxyTurnoutManagerTest::testPutGet() {
    // create
    Turnout* t = l->newTurnout(getSystemName(getNumToTest1()), "mine");
    // check
    Assert::assertTrue("real object returned ", t != nullptr, __FILE__, __LINE__);
    Assert::assertTrue("user name correct ", t == l->getByUserName("mine"), __FILE__, __LINE__);
    Assert::assertTrue("system name correct ", t == l->getBySystemName(getSystemName(getNumToTest1())), __FILE__, __LINE__);
}

//@Test
/*public*/ void ProxyTurnoutManagerTest::testDefaultSystemName() {
    // create
    Turnout* t = l->provideTurnout("" + QString::number(getNumToTest1()));
    // check
    Assert::assertTrue("real object returned ", t != nullptr, __FILE__, __LINE__);
    Assert::assertTrue("system name correct ", t == l->getBySystemName(getSystemName(getNumToTest1())), __FILE__, __LINE__);
}

//@Test(expected=IllegalArgumentException.class)
/*public*/ void ProxyTurnoutManagerTest::testProvideFailure() {
    try {
        l->provideTurnout("");
        Assert::fail("didn't throw", __FILE__, __LINE__);
    } catch (IllegalArgumentException* ex) {
        //JUnitAppender::assertErrorMessage("Invalid system name for Turnout: System name must start with \"" + l->getSystemNamePrefix() + "\".", __FILE__, __LINE__);
        JUnitAppender::assertErrorMessage("Invalid system name for Turnout: System name must start with JT", __FILE__, __LINE__);
     //throw ex;
    }
}

//@Test
/*public*/ void ProxyTurnoutManagerTest::testSingleObject() {
    // test that you always get the same representation
    Turnout* t1 = l->newTurnout(getSystemName(getNumToTest1()), "mine");
    Assert::assertTrue("t1 real object returned ", t1 != nullptr, __FILE__, __LINE__);
    Assert::assertTrue("same by user ", t1 == l->getByUserName("mine"), __FILE__, __LINE__);
    Assert::assertTrue("same by system ", t1 == l->getBySystemName(getSystemName(getNumToTest1())), __FILE__, __LINE__);

    Turnout* t2 = l->newTurnout(getSystemName(getNumToTest1()), "mine");
    Assert::assertTrue("t2 real object returned ", t2 != nullptr, __FILE__, __LINE__);
    // check
    Assert::assertTrue("same new ", t1 == t2, __FILE__, __LINE__);
}

//@Test
/*public*/ void ProxyTurnoutManagerTest::testMisses() {
    // try to get nonexistant objects
    Assert::assertTrue(nullptr == l->getByUserName("foo"), __FILE__, __LINE__);
    Assert::assertTrue(nullptr == l->getBySystemName("bar"), __FILE__, __LINE__);
}

//@Test
/*public*/ void ProxyTurnoutManagerTest::testUpperLower() {
    Turnout* t = l->provideTurnout("" + getNumToTest2());
    QString name = t->getSystemName();
    Assert::assertNull(l->getTurnout(name.toLower()), __FILE__, __LINE__);
}

//@Test
/*public*/ void ProxyTurnoutManagerTest::testRename() {
    // get
    Turnout* t1 = l->newTurnout(getSystemName(getNumToTest1()), "before");
    Assert::assertNotNull("t1 real object ", t1, __FILE__, __LINE__);
    t1->setUserName("after");
    Turnout* t2 = (Turnout*)l->getByUserName("after");
    Assert::assertEquals("same object", t1, t2, __FILE__, __LINE__);
    Assert::assertEquals("no old object", nullptr, l->getByUserName("before"), __FILE__, __LINE__);
}

//@Test
/*public*/ void ProxyTurnoutManagerTest::testTwoNames() {
    Turnout* jl212 = l->provideTurnout("JT212");
    Turnout* jl211 = l->provideTurnout("JT211");

    Assert::assertNotNull(jl212, __FILE__, __LINE__);
    Assert::assertNotNull(jl211, __FILE__, __LINE__);
    Assert::assertTrue(jl212 != jl211, __FILE__, __LINE__);
}

//@Test
/*public*/ void ProxyTurnoutManagerTest::testDefaultNotInternal() {
    Turnout* lut = l->provideTurnout("211");

    Assert::assertNotNull(lut, __FILE__, __LINE__);
    Assert::assertEquals("JT211", lut->getSystemName(), __FILE__, __LINE__);
}

//@Test
/*public*/ void ProxyTurnoutManagerTest::testProvideUser() {
    Turnout* l1 = l->provideTurnout("211");
    l1->setUserName("user 1");
    Turnout* l2 = l->provideTurnout("user 1");
    Turnout* l3 = l->getTurnout("user 1");

    Assert::assertNotNull(l1, __FILE__, __LINE__);
    Assert::assertNotNull(l2, __FILE__, __LINE__);
    Assert::assertNotNull(l3, __FILE__, __LINE__);
    Assert::assertEquals(l1, l2, __FILE__, __LINE__);
    Assert::assertEquals(l3, l2, __FILE__, __LINE__);
    Assert::assertEquals(l1, l3, __FILE__, __LINE__);

    Turnout* l4 = l->getTurnout("JLuser 1");
    Assert::assertNull(l4, __FILE__, __LINE__);
}

//@Test
/*public*/ void ProxyTurnoutManagerTest::testInstanceManagerIntegration() {
    JUnitUtil::resetInstanceManager();
    Assert::assertNotNull(InstanceManager::getDefault("TurnoutManager"), __FILE__, __LINE__);

    JUnitUtil::initInternalTurnoutManager();

    Assert::assertTrue((qobject_cast<ProxyTurnoutManager*> (InstanceManager::getDefault("TurnoutManager")) != nullptr) , __FILE__, __LINE__);

    Assert::assertNotNull(InstanceManager::getDefault("TurnoutManager"), __FILE__, __LINE__);
    Assert::assertNotNull(((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IS1"), __FILE__, __LINE__);

    InternalTurnoutManager* m = new InternalTurnoutManager(new InternalSystemConnectionMemo("J", "Juliet"));
    InstanceManager::setTurnoutManager(m);

    Assert::assertNotNull(((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("JS1"), __FILE__, __LINE__);
    Assert::assertNotNull(((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IS2"), __FILE__, __LINE__);
}

/**
 * Number of unit to test. Made a separate method so it can be overridden in
 * subclasses that do or don't support various numbers
 */
/*protected*/ int ProxyTurnoutManagerTest::getNumToTest1() {
    return 9;
}

/*protected*/ int ProxyTurnoutManagerTest::getNumToTest2() {
    return 7;
}

//@Before
/*public*/ void ProxyTurnoutManagerTest::setUp()
{
 JUnitUtil::setUp();
 // create and register the manager object
 l = new InternalTurnoutManager(new InternalSystemConnectionMemo("J", "Juliet"));
 InstanceManager::setTurnoutManager(l);
}

//@After
/*public*/ void ProxyTurnoutManagerTest::tearDown() {
    JUnitUtil::tearDown();
}


