#include "defaultmalestringactionsockettest.h"
#include "assert1.h"
#include "junitutil.h"
#include "instancemanager.h"
#include "defaultstringactionmanager.h"
#include "stringactionmemory.h"
#include "defaultmalestringactionsocket.h"
#include "logixng_thread.h"
#include "stringactionmemory.h"
#include "defaultconditionalngscaffold.h"


DefaultMaleStringActionSocketTest::DefaultMaleStringActionSocketTest(QObject *parent) : MaleSocketTestBase(parent)
{

}
/**
 * Test ExpressionTimer
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  class DefaultMaleStringActionSocketTest extends MaleSocketTestBase {

    //@Override
    /*protected*/  QString DefaultMaleStringActionSocketTest::getNewSystemName() {
        return ((DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager"))
                ->AbstractManager::getAutoSystemName();
    }

    //@Test
    /*public*/  void DefaultMaleStringActionSocketTest::testCtor() {
        StringActionBean* action = new StringActionMemory("IQSA321", "");
        Assert::assertNotNull("exists", new DefaultMaleStringActionSocket(manager, action), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultMaleStringActionSocketTest::testEvaluate() /*throws JmriException*/ {
        ConditionalNG* conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;

        MyStringAction* action = new MyStringAction("IQSA321");
        action->setParent(conditionalNG);

        DefaultMaleStringActionSocket* socket = new DefaultMaleStringActionSocket(manager, action);
        Assert::assertNotNull("exists", socket, __FILE__, __LINE__);

        socket->setParent(conditionalNG);
        socket->setEnabled(true);
        socket->setErrorHandlingType(ErrorHandlingType::ThrowException);

        action->je = nullptr;
        action->re = nullptr;
        socket->setValue("Something");
        Assert::assertEquals("Something", action->_value, __FILE__, __LINE__);
        socket->setValue("Something else");
        Assert::assertEquals("Something else", action->_value, __FILE__, __LINE__);
        socket->setValue("");
        Assert::assertEquals("", action->_value, __FILE__, __LINE__);
        socket->setValue("");
        Assert::assertNull(action->_value, __FILE__, __LINE__);

        action->je = new JmriException("Test JmriException");
        action->re = nullptr;
#if 0
        Throwable* thrown = catchThrowable( () -> socket->setValue("Something"));
        assertThat(thrown)
                .withFailMessage("Evaluate throws an exception")
                .isNotNull()
                .isInstanceOf(JmriException.class)
                .hasMessage("Test JmriException");
#endif
        action->je = nullptr;
        action->re = new RuntimeException("Test RuntimeException");
#if 0
        thrown = catchThrowable( () -> socket->setValue("Something"));
        assertThat(thrown)
                .withFailMessage("Evaluate throws an exception")
                .isNotNull()
                .isInstanceOf(RuntimeException.class)
                .hasMessage("Test RuntimeException");
#endif
        // If the socket is not enabled, it shouldn't do anything
        socket->setEnabled(false);
        action->re = new RuntimeException("Test RuntimeException");
#if 0
        thrown = catchThrowable( () -> socket->setValue("Something"));
        assertThat(thrown)
                .withFailMessage("Evaluate does nothing")
                .isNull();
#endif
        // Test debug config
        socket->setEnabled(true);
        DefaultMaleStringActionSocket::StringActionDebugConfig* config = new DefaultMaleStringActionSocket::StringActionDebugConfig();
        socket->setDebugConfig(config);
        action->je = nullptr;
        action->re = nullptr;
        config->_dontExecute = true;
        action->_value = "Hello";
        socket->setValue("Something");
        Assert::assertEquals("Hello", action->_value, __FILE__, __LINE__);
        config->_dontExecute = false;
        action->_value = "Hello";
        socket->setValue("Something else");
        Assert::assertEquals("Something else", action->_value, __FILE__, __LINE__);
    }
#if 0
    //@Test
    /*public*/  void testVetoableChange() {
        MyStringAction action = new MyStringAction("IQSA321");
        DefaultMaleStringActionSocket socket = new DefaultMaleStringActionSocket(manager, action);
        Assert::assertNotNull("exists", socket);

        PropertyChangeEvent evt = new PropertyChangeEvent("Source", "Prop", null, null);

        action->_vetoChange = true;
        Throwable thrown = catchThrowable( () -> socket->vetoableChange(evt));
        assertThat(thrown)
                .withFailMessage("vetoableChange() does throw")
                .isNotNull()
                .isInstanceOf(PropertyVetoException.class)
                .hasMessage("Veto change");

        action->_vetoChange = false;
        thrown = catchThrowable( () -> socket->vetoableChange(evt));
        assertThat(thrown)
                .withFailMessage("vetoableChange() does not throw")
                .isNull();
    }

    //@Test
    /*public*/  void testCompareSystemNameSuffix() {
        MyStringAction action1 = new MyStringAction("IQSA1");
        DefaultMaleStringActionSocket socket1 = new DefaultMaleStringActionSocket(manager, action1);

        MyStringAction action2 = new MyStringAction("IQSA01");
        DefaultMaleStringActionSocket socket2 = new DefaultMaleStringActionSocket(manager, action2);

        Assert::assertEquals("compareSystemNameSuffix returns correct value",
                -1, socket1.compareSystemNameSuffix("01", "1", socket2));
        Assert::assertEquals("compareSystemNameSuffix returns correct value",
                0, socket1.compareSystemNameSuffix("1", "1", socket2));
        Assert::assertEquals("compareSystemNameSuffix returns correct value",
                0, socket1.compareSystemNameSuffix("01", "01", socket2));
        Assert::assertEquals("compareSystemNameSuffix returns correct value",
                +1, socket1.compareSystemNameSuffix("1", "01", socket2));
    }
#endif
    // The minimal setup for log4J
    //@BeforeEach
    //@Override
    /*public*/  void DefaultMaleStringActionSocketTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        StringActionBean* actionA = new StringActionMemory("IQSA321", "");
        Assert::assertNotNull("exists", (QObject*)actionA, __FILE__, __LINE__);
        StringActionBean* actionB = new MyStringAction("IQSA322");
        Assert::assertNotNull("exists", (QObject*)actionA, __FILE__, __LINE__);

        manager = (DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager");

        maleSocketA = ((DefaultStringActionManager*)
                InstanceManager::getDefault("StringActionManager"))
                        ->registerAction(actionA);
        Assert::assertNotNull("exists", (QObject*)maleSocketA, __FILE__, __LINE__);

        maleSocketB = ((DefaultStringActionManager*)
                InstanceManager::getDefault("StringActionManager"))
                        ->registerAction(actionB);
        Assert::assertNotNull("exists", (QObject*)maleSocketB, __FILE__, __LINE__);
    }

    //@AfterEach
    //@Override
    /*public*/  void DefaultMaleStringActionSocketTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }



