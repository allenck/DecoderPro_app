#include "digitalactionmanagertest.h"
#include "instancemanager.h"
#include "junitutil.h"
#include "assert1.h"
#include "maledigitalactionsocket.h"
#include "junitappender.h"
#include "defaultdigitalactionmanager.h"
#include "defaultmaledigitalactionsocket.h"
#include "actionmemory.h"
#include "logixng_thread.h"

/**
 * Test DigitalActionManager
 *
 * @author Daniel Bergqvist 2020
 */
// /*public*/  class DigitalActionManagerTest extends AbstractManagerTestBase {


    //@Test
    /*public*/  void DigitalActionManagerTest::testRegisterAction() {
        MyAction03* myAction = new MyAction03(_m->getSystemNamePrefix()+"BadSystemName");

        bool hasThrown = false;
        try {
            _m->registerAction(myAction);
        } catch (IllegalArgumentException* e) {
            hasThrown = true;
            Assert::assertEquals("Error message is correct", "System name is invalid: IQBadSystemName", e->getMessage(), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception thrown", hasThrown, __FILE__, __LINE__);


        // We need a male socket to test with, so we register the action and then unregister the socket
        DigitalActionBean* action = new ActionMemory("IQDA321", "");
        MaleDigitalActionSocket* maleSocket = _m->registerAction(action);
        NamedBean* nb = (NamedBean*)maleSocket;
        _m->deregister((NamedBean*)maleSocket);

        hasThrown = false;
        try {
            _m->registerAction(maleSocket);
        } catch (IllegalArgumentException* e) {
            hasThrown = true;
            Assert::assertEquals("Error message is correct", "registerAction() cannot register a MaleDigitalActionSocket. Use the method register() instead.", e->getMessage(), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DigitalActionManagerTest::testGetBeanTypeHandled() {
        Assert::assertEquals("getBeanTypeHandled() returns correct value", "Digital action", _m->getBeanTypeHandled(), __FILE__, __LINE__);
        Assert::assertEquals("getBeanTypeHandled() returns correct value", "Digital action", _m->getBeanTypeHandled(false), __FILE__, __LINE__);
        Assert::assertEquals("getBeanTypeHandled() returns correct value", "Digital actions", _m->getBeanTypeHandled(true), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DigitalActionManagerTest::testInstance() {
        Assert::assertNotNull("instance() is not null", DefaultDigitalActionManager::instance(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("instance() called on wrong thread", __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void DigitalActionManagerTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        _m = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        _manager = _m;
    }

    //@After
    /*public*/  void DigitalActionManagerTest::tearDown() {
        _m = nullptr;
        _manager = nullptr;
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }


