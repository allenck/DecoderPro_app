#include "defaultmaleanalogexpressionsockettest.h"
#include "junitutil.h"
#include "assert1.h"
#include "instancemanager.h"
#include "defaultanalogexpressionmanager.h"
#include "analogexpressionmemory.h"
#include "defaultanalogexpressionmanager.h"
#include "defaultconditionalngscaffold.h"
#include "logixng_thread.h"
#include "defaultmaleanalogexpressionsocket.h"
#include <math.h>

/**
 * Test ExpressionTimer
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  class DefaultMaleAnalogExpressionSocketTest extends MaleSocketTestBase {

    //@Override
    /*protected*/ QString DefaultMaleAnalogExpressionSocketTest::getNewSystemName() {
        return ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))
                ->AnalogExpressionManager::getAutoSystemName();
    }

    //@Test
    /*public*/  void DefaultMaleAnalogExpressionSocketTest::testCtor() {
        AnalogExpressionBean* expression = new AnalogExpressionMemory("IQAE321", nullptr);
        MaleSocket* maleSocket = ((DefaultAnalogExpressionManager*)manager->mself())->registerExpression(expression);
        Assert::assertNotNull("object exists", (QObject*)maleSocket, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultMaleAnalogExpressionSocketTest::testEvaluate() /*throws JmriException*/ {
        ConditionalNG* conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;

        MyAnalogExpression* expression = new MyAnalogExpression("IQAE321");
        expression->setParent(conditionalNG);

        DefaultMaleAnalogExpressionSocket* socket = new DefaultMaleAnalogExpressionSocket(manager, expression);
        Assert::assertNotNull("exists", socket, __FILE__, __LINE__);

        socket->setParent(conditionalNG);
        socket->setEnabled(true);
        socket->setErrorHandlingType(ErrorHandlingType::ThrowException);

        expression->je = nullptr;
        expression->re = nullptr;
        expression->result = 94.27;
        Assert::assertTrue(94.27 == socket->evaluate(), __FILE__, __LINE__);
        expression->result = 12.92;
        Assert::assertTrue(12.92 == socket->evaluate(), __FILE__, __LINE__);
        expression->result = 0.0;
        Assert::assertTrue(0.0 == socket->evaluate(), __FILE__, __LINE__);

        expression->je = new JmriException("Test JmriException");
        expression->re = nullptr;
#if 0
        Throwable* thrown = catchThrowable( () -> socket->evaluate());
        assertThat(thrown)
                .withFailMessage("Evaluate throws an exception")
                .isNotNull()
                .isInstanceOf("JmriException")
                .hasMessage("Test JmriException");
#endif
        expression->je = nullptr;
        expression->re = new RuntimeException("Test RuntimeException");
#if 0
        thrown = catchThrowable( () -> socket->evaluate());
        assertThat(thrown)
                .withFailMessage("Evaluate throws an exception")
                .isNotNull()
                .isInstanceOf("RuntimeException")
                .hasMessage("Test RuntimeException");
#endif
        // If the socket is not enabled, it shouldn't do anything
        socket->setEnabled(false);
        expression->re = new RuntimeException("Test RuntimeException");
#if 0
        thrown = catchThrowable( () -> socket->evaluate());
        assertThat(thrown)
                .withFailMessage("Evaluate does nothing")
                .isNull();
#endif
        // Test debug config
        socket->setEnabled(true);
        AnalogExpressionDebugConfig* config = new AnalogExpressionDebugConfig();
        socket->setDebugConfig(config);
        expression->je = nullptr;
        expression->re = nullptr;
        config->_forceResult = true;
        config->_result = 12.34;
        expression->result = 93.23;
        Assert::assertTrue(12.34 == socket->evaluate(), __FILE__, __LINE__);
        config->_forceResult = false;
        Assert::assertTrue(93.23 == socket->evaluate(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultMaleAnalogExpressionSocketTest::testEvaluateErrors() {
        ConditionalNG* conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;

        MyAnalogExpression* expression = new MyAnalogExpression("IQAE321");
        expression->setParent(conditionalNG);

        DefaultMaleAnalogExpressionSocket* socket = new DefaultMaleAnalogExpressionSocket(manager, expression);
        Assert::assertNotNull("exists", socket, __FILE__, __LINE__);

        socket->setParent(conditionalNG);
        socket->setEnabled(true);
        socket->setErrorHandlingType(ErrorHandlingType::ThrowException);

        expression->result = nan("0x12345");
#if 0
        Throwable* thrown = catchThrowable( () -> socket->evaluate());
        assertThat(thrown)
                .withFailMessage("Evaluate throws an exception")
                .isNotNull()
                .isInstanceOf("IllegalArgumentException")
                .hasMessage("The result is NaN");
#endif
        expression->result = -INFINITY;
#if 0
        thrown = catchThrowable( () -> socket->evaluate());
        assertThat(thrown)
                .withFailMessage("Evaluate throws an exception")
                .isNotNull()
                .isInstanceOf("IllegalArgumentException")
                .hasMessage("The result is negative infinity");
#endif
        expression->result =INFINITY;
#if 0
        thrown = catchThrowable( () -> socket->evaluate());
        assertThat(thrown)
                .withFailMessage("Evaluate throws an exception")
                .isNotNull()
                .isInstanceOf("IllegalArgumentException")
                .hasMessage("The result is positive infinity");
#endif
    }

    //@Test
    /*public*/  void DefaultMaleAnalogExpressionSocketTest::testVetoableChange() {
        ConditionalNG* conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;

        MyAnalogExpression* expression = new MyAnalogExpression("IQAE321");
        expression->setParent(conditionalNG);

        MaleSocket* socket = ((DefaultAnalogExpressionManager*)manager->mself())->registerExpression(expression);
        Assert::assertNotNull("exists", (QObject*)socket, __FILE__, __LINE__);

        PropertyChangeEvent* evt = new PropertyChangeEvent(/*"Source"*/this, "Prop", QVariant(), QVariant());

        expression->_vetoChange = true;
#if 0
        Throwable* thrown = catchThrowable( () -> socket->vetoableChange(evt));
        assertThat(thrown)
                .withFailMessage("vetoableChange() does throw")
                .isNotNull()
                .isInstanceOf(PropertyVetoException.class)
                .hasMessage("Veto change");
#endif
        expression->_vetoChange = false;
#if 0
        thrown = catchThrowable( () -> socket->vetoableChange(evt));
        assertThat(thrown)
                .withFailMessage("vetoableChange() does not throw")
                .isNull();
#endif
    }

    //@Test
    /*public*/  void DefaultMaleAnalogExpressionSocketTest::testCompareSystemNameSuffix() {
        MyAnalogExpression* expression1 = new MyAnalogExpression("IQAE1");
        MaleAnalogExpressionSocket* socket1 = ((DefaultAnalogExpressionManager*)manager->mself())->registerExpression(expression1);

        MyAnalogExpression* expression2 = new MyAnalogExpression("IQAE01");
        MaleAnalogExpressionSocket* socket2 = ((DefaultAnalogExpressionManager*)manager->mself())->registerExpression(expression2);

        Assert::assertEquals("compareSystemNameSuffix returns correct value",
                -1, socket1->compareSystemNameSuffix("01", "1", socket2), __FILE__, __LINE__);
        Assert::assertEquals("compareSystemNameSuffix returns correct value",
                0, socket1->compareSystemNameSuffix("1", "1", socket2), __FILE__, __LINE__);
        Assert::assertEquals("compareSystemNameSuffix returns correct value",
                0, socket1->compareSystemNameSuffix("01", "01", socket2), __FILE__, __LINE__);
        Assert::assertEquals("compareSystemNameSuffix returns correct value",
                +1, socket1->compareSystemNameSuffix("1", "01", socket2), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@BeforeEach
    //@Override
    /*public*/  void DefaultMaleAnalogExpressionSocketTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        AnalogExpressionBean* expressionA = new AnalogExpressionMemory("IQAE999", "");
        Assert::assertNotNull("exists", (QObject*)expressionA, __FILE__, __LINE__);
        AnalogExpressionBean* expressionB = new MyAnalogExpression("IQAE322");
        Assert::assertNotNull("exists", (QObject*) expressionA, __FILE__, __LINE__);

        manager = (DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");

        maleSocketA =((DefaultAnalogExpressionManager*)
                InstanceManager::getDefault("AnalogExpressionManager"))
                        ->registerExpression(expressionA);
        Assert::assertNotNull("exists", (QObject*)maleSocketA, __FILE__, __LINE__);

        maleSocketB =((DefaultAnalogExpressionManager*)
                InstanceManager::getDefault("AnalogExpressionManager"))
                        ->registerExpression(expressionB);
        Assert::assertNotNull("exists", (QObject*)maleSocketB, __FILE__, __LINE__);
    }

    //@AfterEach
    //@Override
    /*public*/  void DefaultMaleAnalogExpressionSocketTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }


