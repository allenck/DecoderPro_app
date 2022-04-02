#include "defaultmalestringexpressionsockettest.h"
#include "instancemanager.h"
#include "defaultstringexpressionmanager.h"
#include "junitutil.h"
#include "assert1.h"
#include "logixng_thread.h"
#include "stringexpressionmemory.h"
#include "defaultmalestringexpressionsocket.h"
#include "defaultconditionalngscaffold.h"
#include "malesocket.h"

DefaultMaleStringExpressionSocketTest::DefaultMaleStringExpressionSocketTest(QObject *parent) : MaleSocketTestBase(parent)
{

}
/**
 * Test ExpressionTimer
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  class DefaultMaleStringExpressionSocketTest extends MaleSocketTestBase {

    //@Override
    /*protected*/ QString DefaultMaleStringExpressionSocketTest::getNewSystemName() {
        return ((DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))
                ->AbstractManager::getAutoSystemName();
    }

    //@Test
    /*public*/  void DefaultMaleStringExpressionSocketTest::testCtor() {
        StringExpressionBean* expression = new StringExpressionMemory("IQSE321", "");
        Assert::assertNotNull("exists", new DefaultMaleStringExpressionSocket(manager, expression), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultMaleStringExpressionSocketTest::testEvaluate() /*throws JmriException*/ {
        ConditionalNG* conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;

        MyStringExpression* expression = new MyStringExpression("IQSE321");
        expression->setParent(conditionalNG);

        DefaultMaleStringExpressionSocket* socket = new DefaultMaleStringExpressionSocket(manager, expression);
        Assert::assertNotNull("exists", (QObject*)socket, __FILE__, __LINE__);

        socket->setParent(conditionalNG);
        socket->setEnabled(true);
        socket->setErrorHandlingType(ErrorHandlingType::ThrowException);

        expression->je = nullptr;
        expression->re = nullptr;
        expression->result = "Something";
        Assert::assertEquals("Something", socket->evaluate(), __FILE__, __LINE__);
        expression->result = "Something else";
        Assert::assertEquals("Something else", socket->evaluate(), __FILE__, __LINE__);
        expression->result = "";
        Assert::assertEquals("", socket->evaluate(), __FILE__, __LINE__);
        expression->result = nullptr;
        Assert::assertNull(socket->evaluate(), __FILE__, __LINE__);

        expression->je = new JmriException("Test JmriException");
        expression->re = nullptr;
#if 0
        Throwable* thrown = catchThrowable( () -> socket->evaluate());
        assertThat(thrown)
                .withFailMessage("Evaluate throws an exception")
                .isNotNull()
                .isInstanceOf(JmriException.class)
                .hasMessage("Test JmriException");
#else
        Throwable* thrown = nullptr;
        try{
         socket->evaluate();
        }
        catch(Throwable* e)
        {
         Assert::assertEquals("Fail message correct", "Evaluate throws an exception", thrown->getMessage(), __FILE__, __LINE__);
         Assert::assertNotNull("Test JmriException", (QObject*)static_cast<JmriException*>(thrown), __FILE__, __LINE__);
        }

#endif
        expression->je = nullptr;
        expression->re = new RuntimeException("Test RuntimeException");
#if 0
        thrown = catchThrowable( () -> socket->evaluate());
        assertThat(thrown)
                .withFailMessage("Evaluate throws an exception")
                .isNotNull()
                .isInstanceOf(RuntimeException.class)
                .hasMessage("Test RuntimeException");
#else
        thrown = nullptr;
        try{
         socket->evaluate();
        }
        catch(Throwable* e)
        {
         thrown = e;
         Assert::assertEquals("Fail message correct", "Evaluate throws an exception", e->getMessage(), __FILE__, __LINE__);
         Assert::assertNotNull("Test RuntimeException", (QObject*)static_cast<RuntimeException*>(thrown), __FILE__, __LINE__);
        }

#endif

        // If the socket is not enabled, it shouldn't do anything
        socket->setEnabled(false);
        expression->re = new RuntimeException("Test RuntimeException");
 #if 0
        thrown = catchThrowable( () -> socket->evaluate());
        assertThat(thrown)
                .withFailMessage("Evaluate does nothing")
                .isNull();
#else
        thrown = nullptr;
        try{
         socket->evaluate();
        }
        catch(Throwable* e)
        {
         thrown = e;
        }
        Assert::assertTrue("Evaluate does nothing", thrown == nullptr, __FILE__, __LINE__);
#endif

        // Test debug config
        socket->setEnabled(true);
        DefaultMaleStringExpressionSocket::StringExpressionDebugConfig* config = new DefaultMaleStringExpressionSocket::StringExpressionDebugConfig();
        socket->setDebugConfig(config);
        expression->je = nullptr;
        expression->re = nullptr;
        config->_forceResult = true;
        config->_result = "Hello";
        expression->result = "Something";
        Assert::assertEquals("Hello", socket->evaluate(), __FILE__, __LINE__);
        config->_forceResult = false;
        Assert::assertEquals("Something", socket->evaluate(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultMaleStringExpressionSocketTest::testVetoableChange() {
        MyStringExpression* action = new MyStringExpression("IQSE321");
        DefaultMaleStringExpressionSocket* socket = new DefaultMaleStringExpressionSocket(manager, action);
        Assert::assertNotNull("exists", socket, __FILE__, __LINE__);

        PropertyChangeEvent* evt = new PropertyChangeEvent(/*"Source"*/this, "Prop", QVariant(), QVariant());

        action->_vetoChange = true;
#if 0
        Throwable thrown = catchThrowable( () -> socket->vetoableChange(evt));
        assertThat(thrown)
                .withFailMessage("vetoableChange() does throw")
                .isNotNull()
                .isInstanceOf(PropertyVetoException.class)
                .hasMessage("Veto change");
#else
        Throwable* thrown = nullptr;
        try{
         socket->vetoableChange(evt);
        }
        catch(Throwable* e)
        {
         thrown = e;
         Assert::assertTrue("vetoableChange() does throw", "Veto change" == e->getMessage(), __FILE__, __LINE__);
        }
        Assert::assertNotNull("Thrown not null", (QObject*)thrown, __FILE__, __LINE__);
#endif
        action->_vetoChange = false;
#if 0
        thrown = catchThrowable( () -> socket->vetoableChange(evt));
        assertThat(thrown)
                .withFailMessage("vetoableChange() does not throw")
                .isNull();
#else
        thrown = nullptr;
        try{
         socket->vetoableChange(evt);
        }
        catch(Throwable* e)
        {
         thrown = e;
        }
        Assert::assertNull("vetoableChange() does not throw", (QObject*)thrown, __FILE__, __LINE__);
#endif

    }

    //@Test
    /*public*/  void DefaultMaleStringExpressionSocketTest::testCompareSystemNameSuffix() {
        MyStringExpression* expression1 = new MyStringExpression("IQSE1");
        DefaultMaleStringExpressionSocket* socket1 = new DefaultMaleStringExpressionSocket(manager, expression1);

        MyStringExpression* expression2 = new MyStringExpression("IQSE01");
        DefaultMaleStringExpressionSocket* socket2 = new DefaultMaleStringExpressionSocket(manager, expression2);

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
    /*public*/  void DefaultMaleStringExpressionSocketTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        StringExpressionBean* actionA = new StringExpressionMemory("IQSE321", "");
        Assert::assertNotNull("exists", (QObject*)actionA, __FILE__, __LINE__);
        StringExpressionBean* actionB = new MyStringExpression("IQSE322");
        Assert::assertNotNull("exists", (QObject*)actionA, __FILE__, __LINE__);

        manager = (DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager");

        maleSocketA =((DefaultStringExpressionManager*)
                InstanceManager::getDefault("StringExpressionManager"))
                        ->registerExpression(actionA);
        Assert::assertNotNull("exists", (QObject*)maleSocketA, __FILE__, __LINE__);

        maleSocketB =((DefaultStringExpressionManager*)
                InstanceManager::getDefault("StringExpressionManager"))
                        ->registerExpression(actionB);
        Assert::assertNotNull("exists", (QObject*)maleSocketB, __FILE__, __LINE__);
    }

    //@AfterEach
    //@Override
    /*public*/  void DefaultMaleStringExpressionSocketTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }



