#include "analogactionmanagertest.h"
#include "logixng_thread.h"
#include "instancemanager.h"
#include "junitutil.h"
#include "assert1.h"
#include "defaultanalogactionmanager.h"
#include "junitappender.h"
#include "analogactionmemory.h"

AnalogActionManagerTest::AnalogActionManagerTest(QObject *parent) : AbstractManagerTestBase(parent)
{
 setObjectName("AnalogActionManagerTest");
}


/**
 * Test AnalogActionManager
 *
 * @author Daniel Bergqvist 2020
 */
///*public*/  class AnalogActionManagerTest extends AbstractManagerTestBase {


    //@Test
    /*public*/  void AnalogActionManagerTest::testRegisterAction() {
        MyAction* myAction = new MyAction(_m->getSystemNamePrefix()+"BadSystemName");

        bool hasThrown = false;
        try {
            _m->registerAction(myAction);
        } catch (IllegalArgumentException* e) {
            hasThrown = true;
            Assert::assertEquals("Error message is correct", "System name is invalid: IQBadSystemName", e->getMessage(), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception thrown", hasThrown, __FILE__, __LINE__);


        // We need a male socket to test with, so we register the action and then unregister the socket
        AnalogActionBean* action = new AnalogActionMemory("IQAA321", "");
        MaleAnalogActionSocket* maleSocket = _m->registerAction(action);
        _m->deregister(maleSocket);

        hasThrown = false;
        try {
            _m->registerAction(maleSocket);
        } catch (IllegalArgumentException e) {
            hasThrown = true;
            Assert::assertEquals("Error message is correct", "registerAction() cannot register a MaleAnalogActionSocket. Use the method register() instead.", e.getMessage(), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogActionManagerTest::testGetBeanTypeHandled() {
        Assert::assertEquals("getBeanTypeHandled() returns correct value", "Analog action", _m->getBeanTypeHandled(), __FILE__, __LINE__);
        Assert::assertEquals("getBeanTypeHandled() returns correct value", "Analog action", _m->getBeanTypeHandled(false), __FILE__, __LINE__);
        Assert::assertEquals("getBeanTypeHandled() returns correct value", "Analog actions", _m->getBeanTypeHandled(true), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogActionManagerTest::testInstance() {
        Assert::assertNotNull("instance() is not null", DefaultAnalogActionManager::instance(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("instance() called on wrong thread", __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void AnalogActionManagerTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        _m = (DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager");
        _manager = _m;
    }

    //@After
    /*public*/  void AnalogActionManagerTest::tearDown() {
        _m = nullptr;
        _manager = nullptr;
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }

