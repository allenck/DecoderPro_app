#include "digitalexpressionmanagertest.h"
#include "assert1.h"
#include "junitappender.h"
#include "junitutil.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "digitalexpression.h"
#include "logixng_thread.h"
#include "expressionmemory.h"

/**
 * Test DigitalExpressionManager
 *
 * @author Daniel Bergqvist 2020
 */
///*public*/  class DigitalExpressionManagerTest extends AbstractManagerTestBase {


    //@Test
    /*public*/  void DigitalExpressionManagerTest::testRegisterExpression() {
        MyExpression* myExpression = new MyExpression(_m->getSystemNamePrefix()+"BadSystemName");

        bool hasThrown = false;
        try {
            _m->registerExpression(myExpression);
        } catch (IllegalArgumentException* e) {
            hasThrown = true;
            Assert::assertEquals("Error message is correct", "System name is invalid: IQBadSystemName", e->getMessage(), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception thrown", hasThrown, __FILE__, __LINE__);


        // We need a male socket to test with, so we register the action and then unregister the socket
        DigitalExpressionBean* action = new ExpressionMemory("IQDE321", "");
        QString sn = ((AbstractNamedBean*)action->self())->getSystemName();
        MaleDigitalExpressionSocket* maleSocket = _m->registerExpression(action);
        _m->deregister(maleSocket);

        hasThrown = false;
        try {
            _m->registerExpression(maleSocket);
        } catch (IllegalArgumentException* e) {
            hasThrown = true;
            Assert::assertEquals("Error message is correct",
                  "registerExpression() cannot register a MaleDigitalExpressionSocket. Use the method register() instead.",
                                 e->getMessage(), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DigitalExpressionManagerTest::testCreateFemaleSocket() {
        FemaleSocket* socket;
        MyExpression* myExpression = new MyExpression("IQSA1");
        FemaleSocketListener* listener = new MyFemaleSocketListener11();

        socket = _m->createFemaleSocket(myExpression, listener, "E1");
        Assert::assertEquals("Class is correct", "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalExpressionSocket",
                             socket->getClassName(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DigitalExpressionManagerTest::testGetBeanTypeHandled() {
        Assert::assertEquals("getBeanTypeHandled() returns correct value", "Digital expression", _m->getBeanTypeHandled(), __FILE__, __LINE__);
        Assert::assertEquals("getBeanTypeHandled() returns correct value", "Digital expression", _m->getBeanTypeHandled(false), __FILE__, __LINE__);
        Assert::assertEquals("getBeanTypeHandled() returns correct value", "Digital expressions", _m->getBeanTypeHandled(true), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DigitalExpressionManagerTest::testInstance() {
        Assert::assertNotNull("instance() is not null", DefaultDigitalExpressionManager::instance(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("instance() called on wrong thread");
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void DigitalExpressionManagerTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        _m = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        _manager = _m;
    }

    //@After
    /*public*/  void DigitalExpressionManagerTest::tearDown() {
        _m = nullptr;
        _manager = nullptr;
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }


