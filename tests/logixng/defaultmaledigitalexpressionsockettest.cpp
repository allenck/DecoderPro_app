#include "defaultmaledigitalexpressionsockettest.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "defaultmaledigitalexpressionsocket.h"
#include "assert1.h"
#include "junitutil.h"
#include "defaultdigitalexpressionmanager.h"
#include "logixng_thread.h"
#include "and.h"
#include "defaultconditionalngscaffold.h"
#include "malesocket.h"
#include "defaultmaledigitalexpressionsocket.h"
#include "expressionturnout.h"
#include "vptr.h"

/**
 * Test ExpressionTimer
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  class DefaultMaleDigitalExpressionSocketTest extends MaleSocketTestBase {

    //@Override
    /*protected*/ QString DefaultMaleDigitalExpressionSocketTest::getNewSystemName() {
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                ->AbstractManager::getAutoSystemName();
    }

    //@Test
    /*public*/  void DefaultMaleDigitalExpressionSocketTest::testCtor() {
        DigitalExpressionBean* expression = new And("IQDE321", "");
        Assert::assertNotNull("exists", new DefaultMaleDigitalExpressionSocket(manager, expression), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultMaleDigitalExpressionSocketTest::testEvaluate() /*throws JmriException*/ {
        ConditionalNG* conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;

        MyDigitalExpression* expression = new MyDigitalExpression("IQDE321");
        expression->setParent(conditionalNG);

        DefaultMaleDigitalExpressionSocket* socket = new DefaultMaleDigitalExpressionSocket(manager, expression);
        Assert::assertNotNull("exists", socket, __FILE__, __LINE__);

        socket->setParent(conditionalNG);
        socket->setEnabled(true);
        socket->setErrorHandlingType(ErrorHandlingType::ThrowException);

        expression->je = nullptr;
        expression->re = nullptr;
        expression->result = true;
        Assert::assertTrue(socket->evaluate(), __FILE__, __LINE__);
        expression->result = false;
        Assert::assertFalse(socket->evaluate(), __FILE__, __LINE__);

        expression->je = new JmriException("Test JmriException");
        expression->re = nullptr;
#if 0
        Throwable* thrown = catchThrowable( () -> socket.evaluate());
        assertThat(thrown)
                .withFailMessage("Evaluate throws an exception")
                .isNotNull()
                .isInstanceOf("JmriException")
                .hasMessage("Test JmriException");
#endif
        expression->je = nullptr;
        expression->re = new RuntimeException("Test RuntimeException");
#if 0
        thrown = catchThrowable( () -> socket.evaluate());
        assertThat(thrown)
                .withFailMessage("Evaluate throws an exception")
                .isNotNull()
                .isInstanceOf("RuntimeException")
                .hasMessage("Test RuntimeException");

        // If the socket is not enabled, it shouldn't do anything
        socket->setEnabled(false);
        expression->re = new RuntimeException("Test RuntimeException");
        thrown = catchThrowable( () -> socket.evaluate());
        assertThat(thrown)
                .withFailMessage("Evaluate does nothing")
                .isNull();
#endif
        // Test debug config
        socket->setEnabled(true);
        DefaultMaleDigitalExpressionSocket::DigitalExpressionDebugConfig* config = new DefaultMaleDigitalExpressionSocket::DigitalExpressionDebugConfig();
        socket->setDebugConfig(config);
        expression->je = nullptr;
        expression->re = nullptr;
        config->_forceResult = true;
        config->_result = true;
        expression->result = false;
        Assert::assertTrue(socket->evaluate(), __FILE__, __LINE__);
        config->_forceResult = false;
        Assert::assertFalse(socket->evaluate(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultMaleDigitalExpressionSocketTest::testVetoableChange() {
        MyDigitalExpression* action = new MyDigitalExpression("IQDE321");
        DefaultMaleDigitalExpressionSocket* socket = new DefaultMaleDigitalExpressionSocket(manager, action);
        Assert::assertNotNull("exists", socket, __FILE__, __LINE__);

        PropertyChangeEvent* evt = new PropertyChangeEvent(/*"Source"*/this, "Prop", QVariant(), QVariant());

        action->_vetoChange = true;
#if 0
        Throwable* thrown = catchThrowable( () -> socket.vetoableChange(evt));
        assertThat(thrown)
                .withFailMessage("vetoableChange() does throw")
                .isNotNull()
                .isInstanceOf(PropertyVetoException.class)
                .hasMessage("Veto change");
#endif
        action->_vetoChange = false;
#if 0
        thrown = catchThrowable( () -> socket.vetoableChange(evt));
        assertThat(thrown)
                .withFailMessage("vetoableChange() does not throw")
                .isNull();
#endif
    }

    //@Test
    /*public*/  void DefaultMaleDigitalExpressionSocketTest::testCompareSystemNameSuffix() {
        MyDigitalExpression* expression1 = new MyDigitalExpression("IQDE1");
        DefaultMaleDigitalExpressionSocket* socket1 = new DefaultMaleDigitalExpressionSocket(manager, expression1);

        MyDigitalExpression* expression2 = new MyDigitalExpression("IQDE01");
        DefaultMaleDigitalExpressionSocket* socket2 = new DefaultMaleDigitalExpressionSocket(manager, expression2);

        Assert::assertEquals("compareSystemNameSuffix returns correct value",
                -1, socket1->compareSystemNameSuffix("01", "1", (NamedBean*)socket2->self()), __FILE__, __LINE__);
        Assert::assertEquals("compareSystemNameSuffix returns correct value",
                0, socket1->compareSystemNameSuffix("1", "1", (NamedBean*)socket2->self()), __FILE__, __LINE__);
        Assert::assertEquals("compareSystemNameSuffix returns correct value",
                0, socket1->compareSystemNameSuffix("01", "01", (NamedBean*)socket2->self()), __FILE__, __LINE__);
        Assert::assertEquals("compareSystemNameSuffix returns correct value",
                +1, socket1->compareSystemNameSuffix("1", "01", (NamedBean*)socket2->self()), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@BeforeEach
    //@Override
    /*public*/  void DefaultMaleDigitalExpressionSocketTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        DigitalExpressionBean* expressionA = new ExpressionTurnout("IQDE321", "");
        Assert::assertNotNull("exists", VPtr<DigitalExpressionBean>::asQVariant(expressionA), __FILE__, __LINE__);
        DigitalExpressionBean* expressionB = new MyDigitalExpression("IQDE322");
        Assert::assertNotNull("exists", VPtr<DigitalExpressionBean>::asQVariant(expressionA), __FILE__, __LINE__);

        manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");

        maleSocketA =((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))
                        ->registerExpression(expressionA);
        Assert::assertNotNull("exists", VPtr<MaleSocket>::asQVariant(maleSocketA), __FILE__, __LINE__);

        maleSocketB =((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))
                        ->registerExpression(expressionB);
        Assert::assertNotNull("exists", VPtr<MaleSocket>::asQVariant(maleSocketB), __FILE__, __LINE__);
    }

    //@AfterEach
    //@Override
    /*public*/  void DefaultMaleDigitalExpressionSocketTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }



