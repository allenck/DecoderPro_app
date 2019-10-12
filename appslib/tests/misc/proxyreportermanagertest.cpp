#include "proxyreportermanagertest.h"
#include "junitutil.h"
#include "assert1.h"
#include "reportermanager.h"
#include "instancemanager.h"
#include "internalreportermanager.h"
#include "internalsystemconnectionmemo.h"

ProxyReporterManagerTest::ProxyReporterManagerTest(QObject* parent)
{

}

/**
 * Test the ProxyReporterManager
 *
 * @author	Bob Jacobsen 2003, 2006, 2008
 * @author	Mark Underwood 2012
 * @author	Paul Bender 2016
 */
// /*public*/ class ProxyReporterManagerTest extends AbstractReporterMgrTestBase {

    //@Override
    /*public*/ QString ProxyReporterManagerTest::getSystemName(QString i) {
        return "IR" +i;
    }

    //@Test
    /*public*/ void ProxyReporterManagerTest::testReporterPutGet() {
        // create
        Reporter* t = ((ProxyReporterManager*)l)->newReporter(getSystemName(getNameToTest1()), "mine");
        // check
        Assert::assertTrue("real object returned ", t != nullptr, __FILE__, __LINE__);
        Assert::assertTrue("user name correct ", t == ((ProxyReporterManager*)l)->getByUserName("mine"), __FILE__, __LINE__);
        Assert::assertTrue("system name correct ", t == ((ProxyReporterManager*)l)->getBySystemName(getSystemName(getNameToTest1())), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxyReporterManagerTest::testTwoNames() {
        Reporter* ir211 = ((ProxyReporterManager*)l)->provideReporter("LR211");
        Reporter* lr211 = ((ProxyReporterManager*)l)->provideReporter("IR211");

        Assert::assertNotNull(ir211, __FILE__, __LINE__);
        Assert::assertNotNull(lr211, __FILE__, __LINE__);
        Assert::assertTrue(ir211 != lr211, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxyReporterManagerTest::testDefaultNotInternal() {
        Reporter* lut = ((ProxyReporterManager*)l)->provideReporter("211");

        Assert::assertNotNull(lut, __FILE__, __LINE__);
        Assert::assertEquals("IR211", lut->getSystemName(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxyReporterManagerTest::testProvideUser() {
        Reporter* l1 = ((ProxyReporterManager*)l)->provideReporter("211");
        l1->setUserName("user 1");
        Reporter* l2 = ((ProxyReporterManager*)l)->provideReporter("user 1");
        Reporter* l3 = ((ProxyReporterManager*)l)->getReporter("user 1");

        Assert::assertNotNull(l1, __FILE__, __LINE__);
        Assert::assertNotNull(l2, __FILE__, __LINE__);
        Assert::assertNotNull(l3, __FILE__, __LINE__);
        Assert::assertEquals(l1, l2, __FILE__, __LINE__);
        Assert::assertEquals(l3, l2, __FILE__, __LINE__);
        Assert::assertEquals(l1, l3, __FILE__, __LINE__);

        Reporter* l4 = ((ProxyReporterManager*)l)->getReporter("JLuser 1");
        Assert::assertNull(l4, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxyReporterManagerTest::testInstanceManagerIntegration() {
        JUnitUtil::resetInstanceManager();
        Assert::assertNotNull(InstanceManager::getDefault("ReporterManager"), __FILE__, __LINE__);

        JUnitUtil::initReporterManager();

        Assert::assertTrue(qobject_cast<ProxyReporterManager*>(InstanceManager::getDefault("ReporterManager")), __FILE__, __LINE__);

        Assert::assertNotNull(InstanceManager::getDefault("ReporterManager"), __FILE__, __LINE__);
        Assert::assertNotNull(((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->provideReporter("IR1"), __FILE__, __LINE__);

        ReporterManager* m = new InternalReporterManager(new InternalSystemConnectionMemo("J", "Juliet"));
        InstanceManager::setReporterManager(m);

        Assert::assertNotNull(((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->provideReporter("JR1"), __FILE__, __LINE__);
        Assert::assertNotNull(((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->provideReporter("IR2"), __FILE__, __LINE__);
    }


    // The minimal setup for log4J
    //@Before
    //@Override
    /*public*/ void ProxyReporterManagerTest::setUp() {
        JUnitUtil::setUp();
        // create and register the manager object
        l = (ReporterManager*)InstanceManager::getDefault("ReporterManager");
    }

    //@After
    /*public*/ void ProxyReporterManagerTest::tearDown() {
        JUnitUtil::tearDown();
    }

