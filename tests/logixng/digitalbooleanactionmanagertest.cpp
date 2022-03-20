#include "digitalbooleanactionmanagertest.h"
#include "logixng_thread.h"
#include "instancemanager.h"
#include "defaultdigitalbooleanactionmanager.h"
#include "assert1.h"
#include "junitutil.h"
#include "junitappender.h"
#include "digitalbooleanonchange.h"

/**
 * Test DigitalActionManager
 *
 * @author Daniel Bergqvist 2020
 */
///*public*/  class DigitalBooleanActionManagerTest extends AbstractManagerTestBase {


    //@Test
    /*public*/  void DigitalBooleanActionManagerTest::testRegisterAction() {
        MyAction02* myAction = new MyAction02(_m->getSystemNamePrefix()+"BadSystemName");

        bool hasThrown = false;
        try {
           _m->registerAction(myAction);
        } catch (IllegalArgumentException* e) {
            hasThrown = true;
            Assert::assertEquals("Error message is correct", "System name is invalid: IQBadSystemName", e->getMessage(), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception thrown", hasThrown, __FILE__, __LINE__);


        // We need a male socket to test with, so we register the action and then unregister the socket
        DigitalBooleanActionBean* action = new DigitalBooleanOnChange("IQDB321", "", DigitalBooleanOnChange::Trigger::CHANGE);
        MaleDigitalBooleanActionSocket* maleSocket =_m->registerAction(action);
       _m->deregister(maleSocket);

        hasThrown = false;
        try {
           _m->registerAction(maleSocket);
        } catch (IllegalArgumentException* e) {
            hasThrown = true;
            Assert::assertEquals("Error message is correct", "registerAction() cannot register a MaleDigitalBooleanActionSocket. Use the method register() instead.", e->getMessage(), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DigitalBooleanActionManagerTest::testGetBeanTypeHandled() {
        Assert::assertEquals("getBeanTypeHandled() returns correct value", "Digital bool action",_m->getBeanTypeHandled(), __FILE__, __LINE__);
        Assert::assertEquals("getBeanTypeHandled() returns correct value", "Digital bool action",_m->getBeanTypeHandled(false), __FILE__, __LINE__);
        Assert::assertEquals("getBeanTypeHandled() returns correct value", "Digital bool actions",_m->getBeanTypeHandled(true), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DigitalBooleanActionManagerTest::testInstance() {
        Assert::assertNotNull("instance() is not null", DefaultDigitalBooleanActionManager::instance(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("instance() called on wrong thread", __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void DigitalBooleanActionManagerTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        _m = (DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager");
        _manager = _m;
    }

    //@After
    /*public*/  void DigitalBooleanActionManagerTest::tearDown() {
        _m = nullptr;
        _manager = nullptr;
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }


