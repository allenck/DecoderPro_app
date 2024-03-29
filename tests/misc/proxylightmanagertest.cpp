#include "proxylightmanagertest.h"
#include "assert1.h"
#include "junitutil.h"
#include "proxylightmanager.h"
#include "instancemanager.h"
#include "internallightmanager.h"
#include "junitappender.h"
#include "internalsystemconnectionmemo.h"

ProxyLightManagerTest::ProxyLightManagerTest(QObject *parent) : QObject(parent)
{

}
/**
 * Test the ProxyLightManager.
 *
 * @author	Bob Jacobsen 2003, 2006, 2008
 */
// /*public*/ class ProxyLightManagerTest {

    /*public*/ QString ProxyLightManagerTest::getSystemName(int i) {
        return "JL" + QString::number(i);
    }


    /*static*/ /*protected*/ bool ProxyLightManagerTest::listenerResult = false;

//    protected class Listen implements PropertyChangeListener {

        //@Override
        /*public*/ void ListenO7::propertyChange(PropertyChangeEvent* /*e*/) {
            this->test->listenerResult = true;
        }
//    }

    //@Test
    /*public*/ void ProxyLightManagerTest::testDispose() {
        l->dispose();  // all we're really doing here is making sure the method exists
    }

    //@Test
    /*public*/ void ProxyLightManagerTest::testLightPutGet() {
        // create
        Light* t = l->newLight(getSystemName(getNumToTest1()), "mine");
        // check
        Assert::assertTrue("real object returned ", t != nullptr, __FILE__, __LINE__);
        Assert::assertTrue("user name correct ", t->self() == l->getByUserName("mine")->self(), __FILE__, __LINE__);
        Assert::assertTrue("system name correct ", ((AbstractNamedBean*)t->self()) == l->getBySystemName(getSystemName(getNumToTest1())), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxyLightManagerTest::testDefaultSystemName() {
        // create
        Light* t = l->provideLight("" + QString::number(getNumToTest1()));
        // check
        Assert::assertTrue("real object returned ", t != nullptr, __FILE__, __LINE__);
        Assert::assertTrue("system name correct ", t->self() == l->getBySystemName(getSystemName(getNumToTest1()))->self(), __FILE__, __LINE__);
    }

    //@Test(expected=IllegalArgumentException.class)
    /*public*/ void ProxyLightManagerTest::testProvideFailure() throw (IllegalAccessException){
        try {
            l->provideLight("");
            Assert::fail("didn't throw", __FILE__, __LINE__);
        } catch (IllegalArgumentException* ex) {
            JUnitAppender::assertErrorMessage("Invalid system name for Light: System name must start with \"" + l->getSystemNamePrefix() + "\".", __FILE__, __LINE__);
            throw ;
        }
    }

    //@Test
    /*public*/ void ProxyLightManagerTest::testSingleObject() {
        // test that you always get the same representation
        Light* t1 = l->newLight(getSystemName(getNumToTest1()), "mine");
        Assert::assertTrue("t1 real object returned ", t1 != nullptr, __FILE__, __LINE__);
        Assert::assertTrue("same by user ", t1 == (Light*)l->getByUserName("mine")->self(), __FILE__, __LINE__);
        Assert::assertTrue("same by system ", t1 ==(Light*) l->getBySystemName(getSystemName(getNumToTest1()))->self(), __FILE__, __LINE__);

        Light* t2 = l->newLight(getSystemName(getNumToTest1()), "mine");
        Assert::assertTrue("t2 real object returned ", t2 != nullptr, __FILE__, __LINE__);
        // check
        Assert::assertTrue("same new ", t1 == t2, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxyLightManagerTest::testMisses() {
        // try to get nonexistant lights
        Assert::assertTrue(nullptr == l->getByUserName("foo"), __FILE__, __LINE__);
        Assert::assertTrue(nullptr == l->getBySystemName("bar"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxyLightManagerTest::testUpperLower() {
        Light* t = l->provideLight(QString::number(getNumToTest2()));
        QString name = ((AbstractNamedBean*)t->self())->getSystemName();
        Assert::assertNull(l->getLight(name.toLower())->self(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxyLightManagerTest::testRename() {
        // get light
        Light* t1 = l->newLight(getSystemName(getNumToTest1()), "before");
        Assert::assertNotNull("t1 real object ", t1->self(), __FILE__, __LINE__);
        ((AbstractNamedBean*)t1->self())->setUserName("after");
        Light* t2 = (Light*)l->getByUserName("after")->self();
        Assert::assertEquals("same object", t1, t2, __FILE__, __LINE__);
        Assert::assertEquals("no old object", nullptr, l->getByUserName("before")->self(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxyLightManagerTest::testTwoNames() {
        Light* il211 = l->provideLight("IL211");
        Light* jl211 = l->provideLight("JL211");

        Assert::assertNotNull(il211->self(), __FILE__, __LINE__);
        Assert::assertNotNull(jl211->self(), __FILE__, __LINE__);
        Assert::assertTrue(il211 != jl211, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxyLightManagerTest::testDefaultNotInternal() {
        Light* lut = l->provideLight("211");

        Assert::assertNotNull(lut->self(), __FILE__, __LINE__);
        Assert::assertEquals("JL211", ((AbstractNamedBean*)lut->self())->getSystemName(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxyLightManagerTest::testProvideUser() {
        Light* l1 = l->provideLight("211");
        ((AbstractNamedBean*)l1->self())->setUserName("user 1");
        Light* l2 = l->provideLight("user 1");
        Light* l3 = l->getLight("user 1");

        Assert::assertNotNull(l1->self(), __FILE__, __LINE__);
        Assert::assertNotNull(l2->self(), __FILE__, __LINE__);
        Assert::assertNotNull(l3->self(), __FILE__, __LINE__);
        Assert::assertEquals(l1, l2, __FILE__, __LINE__);
        Assert::assertEquals(l3, l2, __FILE__, __LINE__);
        Assert::assertEquals(l1, l3, __FILE__, __LINE__);

        Light* l4 = l->getLight("JLuser 1");
        Assert::assertNull(l4->self(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxyLightManagerTest::testInstanceManagerIntegration() {
        JUnitUtil::resetInstanceManager();
        Assert::assertNotNull(InstanceManager::getDefault("LightManager"), __FILE__, __LINE__);

        JUnitUtil::initInternalLightManager();

        Assert::assertTrue(qobject_cast<LightManager*>(InstanceManager::getDefault("LightManager"))!=nullptr, __FILE__, __LINE__);

        Assert::assertNotNull(InstanceManager::getDefault("LightManager"), __FILE__, __LINE__);
        Assert::assertNotNull(((LightManager*)InstanceManager::getDefault("LightManager"))->provideLight("IL1")->self(), __FILE__, __LINE__);

        InternalLightManager* m = new InternalLightManager(new InternalSystemConnectionMemo("J", "Juliet"));
        InstanceManager::setLightManager(m);

        Assert::assertNotNull(((LightManager*)InstanceManager::getDefault("LightManager"))->provideLight("JL1")->self(), __FILE__, __LINE__);
        Assert::assertNotNull(((LightManager*)InstanceManager::getDefault("LightManager"))->provideLight("IL2")->self(), __FILE__, __LINE__);
    }

    /**
     * Number of Light* to test. Made a separate method so it can be overridden
     * in subclasses that do or don't support various numbers.
     *
     * @return the number to test
     */
    /*protected*/ int ProxyLightManagerTest::getNumToTest1() {
        return 9;
    }

    /*protected*/ int ProxyLightManagerTest::getNumToTest2() {
        return 7;
    }

    //@Before
    /*public*/ void ProxyLightManagerTest::setUp() {
        JUnitUtil::setUp();
        // create and register the manager object
        l = new InternalLightManager(new InternalSystemConnectionMemo("J", "Juliet"));
        InstanceManager::setLightManager((AbstractManager*)l->self());
    }

    //@After
    /*public*/ void ProxyLightManagerTest::tearDown() {
        JUnitUtil::tearDown();
    }
