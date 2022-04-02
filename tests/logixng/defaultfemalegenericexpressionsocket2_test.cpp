#include "defaultfemalegenericexpressionsocket2_test.h"
#include "assert1.h"
#include "junitutil.h"
#include "defaultconditionalngscaffold.h"
#include "defaultfemalegenericexpressionsocket.h"
#include "logixng_thread.h"
#include "instancemanager.h"
#include "defaultanalogexpressionmanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "defaultstringexpressionmanager.h"


DefaultFemaleGenericExpressionSocket2_Test::DefaultFemaleGenericExpressionSocket2_Test(QObject *parent) : QObject(parent)
{

}

/**
 * Test DefaultFemaleGenericExpressionSocket
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  class DefaultFemaleGenericExpressionSocket2_Test {


    //@Test
    /*public*/  void DefaultFemaleGenericExpressionSocket2_Test::testEvaluateGeneric() /*throws JmriException*/ {
        DefaultFemaleGenericExpressionSocket* socket;

        MyAnalogExpression* analogExpression = new MyAnalogExpression("IQAE351", "");
        MaleSocket* analogMaleSocket = ((DefaultAnalogExpressionManager*)
                InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(analogExpression);

        MyDigitalExpression* digitalExpression = new MyDigitalExpression("IQDE351", "");
        MaleSocket* digitalMaleSocket = ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(digitalExpression);

        MyStringExpression* stringExpression = new MyStringExpression("IQSE351", "");
        MaleSocket* stringMaleSocket = ((DefaultStringExpressionManager*)
                InstanceManager::getDefault("StringExpressionManager"))->registerExpression(stringExpression);

        socket = new DefaultFemaleGenericExpressionSocket(FemaleGenericExpressionSocket::SocketType::GENERIC, _conditionalNG, _listener, "E");

        Assert::assertEquals("evaluateGeneric() returns correct value", QVariant(), socket->evaluateGeneric(), __FILE__, __LINE__);

        socket->_connect(analogMaleSocket);
        analogExpression->_value = 0.0;
        Assert::assertTrue("evaluateGeneric() returns correct value", 0.0 == socket->evaluateGeneric().toDouble(), __FILE__, __LINE__);
        analogExpression->_value = 1.0;
        Assert::assertTrue("evaluateGeneric() returns correct value", 1.0 == socket->evaluateGeneric().toDouble(), __FILE__, __LINE__);
        analogExpression->_value = -1.0;
        Assert::assertTrue("evaluateGeneric() returns correct value", -1.0 == socket->evaluateGeneric().toDouble(), __FILE__, __LINE__);
        socket->disconnect();


        socket = new DefaultFemaleGenericExpressionSocket(FemaleGenericExpressionSocket::SocketType::GENERIC, _conditionalNG, _listener, "E");

        Assert::assertEquals("evaluateGeneric() returns correct value", QVariant(), socket->evaluateGeneric(), __FILE__, __LINE__);

        socket->_connect(digitalMaleSocket);
        digitalExpression->_value = false;
        Assert::assertFalse("evaluateGeneric() returns correct value", socket->evaluateGeneric().toBool(), __FILE__, __LINE__);
        digitalExpression->_value = true;
        Assert::assertTrue("evaluateGeneric() returns correct value", socket->evaluateGeneric().toBool(), __FILE__, __LINE__);
        socket->_disconnect();


        socket = new DefaultFemaleGenericExpressionSocket(FemaleGenericExpressionSocket::SocketType::GENERIC, _conditionalNG, _listener, "E");

        Assert::assertEquals("evaluateGeneric() returns correct value", QVariant(), socket->evaluateGeneric(), __FILE__, __LINE__);

        socket->_connect(stringMaleSocket);
        stringExpression->_value = "";
        Assert::assertEquals("evaluateGeneric() returns correct value", "", socket->evaluateGeneric(), __FILE__, __LINE__);
        stringExpression->_value = "Hello";
        Assert::assertEquals("evaluateGeneric() returns correct value", "Hello", socket->evaluateGeneric(), __FILE__, __LINE__);
        stringExpression->_value = "1.0";
        Assert::assertEquals("evaluateGeneric() returns correct value", "1.0", socket->evaluateGeneric(), __FILE__, __LINE__);
        socket->disconnect();
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void DefaultFemaleGenericExpressionSocket2_Test::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        _conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;

        _listener = new MyFemaleSocketListener();
//        {
//            //@Override
//            /*public*/  void connected(FemaleSocket socket) {
//                // Do nothing
//            }

//            //@Override
//            /*public*/  void disconnected(FemaleSocket socket) {
//                // Do nothing
//            }
//        };
    }

    //@After
    /*public*/  void DefaultFemaleGenericExpressionSocket2_Test::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }




