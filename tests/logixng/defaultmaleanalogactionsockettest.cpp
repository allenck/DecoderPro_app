#include "defaultmaleanalogactionsockettest.h"
#include "junitutil.h"
#include "instancemanager.h"
#include "defaultanalogactionmanager.h"
#include "analogactionmemory.h"
#include "assert1.h"
#include "defaultmaleanalogactionsocket.h"
#include "defaultconditionalngscaffold.h"
#include "logixng_thread.h"

DefaultMaleAnalogActionSocketTest::DefaultMaleAnalogActionSocketTest(QObject *parent) : MaleSocketTestBase(parent)
{

}

/**
 * Test DefaultMaleAnalogSocket
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  class DefaultMaleAnalogActionSocketTest extends MaleSocketTestBase {

    //@Override
    /*protected*/ QString DefaultMaleAnalogActionSocketTest::getNewSystemName() {
        return ((DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))
                ->AnalogActionManager::getAutoSystemName();
    }

    //@Test
    /*public*/  void DefaultMaleAnalogActionSocketTest::testCtor() {
        AnalogActionBean* action = new AnalogActionMemory("IQAA321", "");
        Assert::assertNotNull("object exists", new DefaultMaleAnalogActionSocket(manager, action), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultMaleAnalogActionSocketTest::testSetValue() /*throws JmriException*/ {
        ConditionalNG* conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;

        MyAnalogAction* action = new MyAnalogAction("IQAA321");
        action->setParent(conditionalNG);

        DefaultMaleAnalogActionSocket* socket = new DefaultMaleAnalogActionSocket(manager, action);
        Assert::assertNotNull("exists", socket, __FILE__, __LINE__);

        socket->setParent(conditionalNG);
        socket->setEnabled(true);
        socket->setErrorHandlingType(ErrorHandlingType::ThrowException);

        action->je = nullptr;
        action->re = nullptr;
        socket->setValue(9.121);
        Assert::assertTrue(9.121 == action->_value, __FILE__, __LINE__);
        socket->setValue(572.1);
        Assert::assertTrue(572.1 == action->_value, __FILE__, __LINE__);
        socket->setValue(0.0);
        Assert::assertTrue(0.0 == action->_value, __FILE__, __LINE__);

        action->je = new JmriException("Test JmriException");
        action->re = nullptr;
#if 0
        Throwable* thrown = catchThrowable( () -> socket->setValue(9.121));
        assertThat(thrown)
                .withFailMessage("Evaluate throws an exception")
                .isNotNull()
                .isInstanceOf("JmriException")
                .hasMessage("Test JmriException");
#endif
        action->je = nullptr;
        action->re = new RuntimeException("Test RuntimeException");
#if 0
        thrown = catchThrowable( () -> socket->setValue(32.11));
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
        thrown = catchThrowable( () -> socket->setValue(9.23));
        assertThat(thrown)
                .withFailMessage("Evaluate does nothing")
                .isNull();
#endif
        // Test debug config
        socket->setEnabled(true);
        DefaultMaleAnalogActionSocket::AnalogActionDebugConfig* config = new DefaultMaleAnalogActionSocket::AnalogActionDebugConfig();
        socket->setDebugConfig(config);
        action->je = nullptr;
        action->re = nullptr;
        config->_dontExecute = true;
        action->_value = 19.23;
        socket->setValue(32.11);
        Assert::assertTrue(19.23 == action->_value, __FILE__, __LINE__);
        config->_dontExecute = false;
        action->_value = 23.111;
        socket->setValue(9.23);
        Assert::assertTrue(9.23 == action->_value, __FILE__, __LINE__);
    }
    #if 0
    //@Test
    /*public*/  void testEvaluateErrors() {
        ConditionalNG conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;

        MyAnalogAction action = new MyAnalogAction("IQAA321");
        action->setParent(conditionalNG);

        DefaultMaleAnalogActionSocket socket = new DefaultMaleAnalogActionSocket(manager, action);
        Assert::assertNotNull("exists", socket);

        socket->setParent(conditionalNG);
        socket->setEnabled(true);
        socket->setErrorHandlingType(MaleSocket.ErrorHandlingType.ThrowException);

        Throwable thrown = catchThrowable( () -> socket->setValue(Double.NaN));
        assertThat(thrown)
                .withFailMessage("Evaluate throws an exception")
                .isNotNull()
                .isInstanceOf(IllegalArgumentException.class)
                .hasMessage("The value is NaN");

        thrown = catchThrowable( () -> socket->setValue(Double.NEGATIVE_INFINITY));
        assertThat(thrown)
                .withFailMessage("Evaluate throws an exception")
                .isNotNull()
                .isInstanceOf(IllegalArgumentException.class)
                .hasMessage("The value is negative infinity");

        thrown = catchThrowable( () -> socket->setValue(Double.POSITIVE_INFINITY));
        assertThat(thrown)
                .withFailMessage("Evaluate throws an exception")
                .isNotNull()
                .isInstanceOf(IllegalArgumentException.class)
                .hasMessage("The value is positive infinity");
    }

    //@Test
    /*public*/  void testVetoableChange() {
        MyAnalogAction action = new MyAnalogAction("IQAA321");
        DefaultMaleAnalogActionSocket socket = new DefaultMaleAnalogActionSocket(manager, action);
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
        MyAnalogAction action1 = new MyAnalogAction("IQAA1");
        DefaultMaleAnalogActionSocket socket1 = new DefaultMaleAnalogActionSocket(manager, action1);

        MyAnalogAction action2 = new MyAnalogAction("IQAA01");
        DefaultMaleAnalogActionSocket socket2 = new DefaultMaleAnalogActionSocket(manager, action2);

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
    /*public*/  void DefaultMaleAnalogActionSocketTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        AnalogActionMemory* actionA = new AnalogActionMemory("IQAA321", "");
        Assert::assertNotNull("exists", actionA, __FILE__, __LINE__);
        AnalogActionBean* actionB = new MyAnalogAction("IQAA322");
        Assert::assertNotNull("exists", actionA, __FILE__, __LINE__);

        manager = (DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager");

        maleSocketA =((DefaultAnalogActionManager*)
                InstanceManager::getDefault("AnalogActionManager"))
                        ->registerAction(actionA);
        Assert::assertNotNull("exists", (QObject*)maleSocketA, __FILE__, __LINE__);

        maleSocketB =((DefaultAnalogActionManager*)
                InstanceManager::getDefault("AnalogActionManager"))
                        ->registerAction(actionB);
        Assert::assertNotNull("exists", (QObject*)maleSocketB, __FILE__, __LINE__);
    }

    //@AfterEach
    //@Override
    /*public*/  void DefaultMaleAnalogActionSocketTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }


