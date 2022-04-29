#include "analogexpressionmanagertest.h"
#include "instancemanager.h"
#include "assert1.h"
#include "junitappender.h"
#include "junitutil.h"
#include "defaultanalogexpressionmanager.h"
#include "analogexpressionmemory.h"
#include "logixng_thread.h"

AnalogExpressionManagerTest::AnalogExpressionManagerTest(QObject *parent) : AbstractManagerTestBase(parent)
{
 setObjectName("AnalogExpressionManagerTest");
}
/**
 * Test AnalogExpressionManager
 *
 * @author Daniel Bergqvist 2020
 */
///*public*/  class AnalogExpressionManagerTest extends AbstractManagerTestBase {


    //@Test
    /*public*/  void AnalogExpressionManagerTest::testRegisterExpression() {
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
        AnalogExpressionBean* action = new AnalogExpressionMemory("IQAE321", "");
        MaleAnalogExpressionSocket* maleSocket = _m->registerExpression(action);
        _m->deregister(maleSocket);

        hasThrown = false;
        try {
            _m->registerExpression(maleSocket);
        } catch (IllegalArgumentException* e) {
            hasThrown = true;
            Assert::assertEquals("Error message is correct", "registerExpression() cannot register a MaleAnalogExpressionSocket. Use the method register() instead.", e->getMessage(), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogExpressionManagerTest::testCreateFemaleSocket() {
        FemaleSocket* socket;
        AnalogExpressionManagerTest::MyExpression* myExpression = new AnalogExpressionManagerTest::MyExpression("IQSA1");
        FemaleSocketListener* listener = new AnalogExpressionManagerTest_MyFemaleSocketListener();

        socket = _m->createFemaleSocket(myExpression, listener, "E1");
        Assert::assertEquals("Class is correct", "jmri.jmrit.logixng.implementation.DefaultFemaleAnalogExpressionSocket", socket->getClassName(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogExpressionManagerTest::testGetBeanTypeHandled() {
        Assert::assertEquals("getBeanTypeHandled() returns correct value", "Analog expression", _m->getBeanTypeHandled(), __FILE__, __LINE__);
        Assert::assertEquals("getBeanTypeHandled() returns correct value", "Analog expression", _m->getBeanTypeHandled(false), __FILE__, __LINE__);
        Assert::assertEquals("getBeanTypeHandled() returns correct value", "Analog expressions", _m->getBeanTypeHandled(true), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogExpressionManagerTest::testInstance() {
        Assert::assertNotNull("instance() is not null", DefaultAnalogExpressionManager::instance(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("instance() called on wrong thread", __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void AnalogExpressionManagerTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        _m = (DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
        _manager = _m;
    }

    //@After
    /*public*/  void AnalogExpressionManagerTest::tearDown() {
        _m = nullptr;
        _manager = nullptr;
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }


