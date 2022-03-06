#include "defaultmaledigitalactionsockettest.h"
#include "logixng_thread.h"
#include "junitutil.h"
#include "assert1.h"
#include "defaultdigitalactionmanager.h"
#include "instancemanager.h"
#include "digitalmany.h"
#include "defaultmaledigitalactionsocket.h"
#include "defaultconditionalngscaffold.h"
#include "actionturnout.h"


DefaultMaleDigitalActionSocketTest::DefaultMaleDigitalActionSocketTest(QObject *parent) : MaleSocketTestBase(parent)
{

}

/**
 * Test ExpressionTimer
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  class DefaultMaleDigitalActionSocketTest extends MaleSocketTestBase{

    //@Override
    /*protected*/ QString DefaultMaleDigitalActionSocketTest::getNewSystemName() {
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                ->AbstractManager::getAutoSystemName();
    }

    ////@Test
    /*public*/  void DefaultMaleDigitalActionSocketTest::testCtor() {
        DigitalActionBean* action = new DigitalMany("IQDA321", "");
        Assert::assertNotNull("exists", new DefaultMaleDigitalActionSocket(manager, action), __FILE__, __LINE__);
    }

    ////@Test
    /*public*/  void DefaultMaleDigitalActionSocketTest::testExecute() /*throws JmriException*/ {
        ConditionalNG* conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;

        MyDigitalAction* action = new MyDigitalAction("IQDA321");
        action->setParent(conditionalNG);

        DefaultMaleDigitalActionSocket* socket = new DefaultMaleDigitalActionSocket(manager, action);
        Assert::assertNotNull("exists", socket, __FILE__, __LINE__);

        socket->setParent(conditionalNG);
        socket->setEnabled(true);
        socket->setErrorHandlingType(ErrorHandlingType::ThrowException);

        action->je = nullptr;
        action->re = nullptr;
        action->_hasExecuted = false;
        socket->execute();
        Assert::assertTrue(action->_hasExecuted, __FILE__, __LINE__);

        action->je = new JmriException("Test JmriException");
        action->re = nullptr;
#if 0
        Throwable* thrown = catchThrowable( () -> socket->execute());
        assertThat(thrown)
                .withFailMessage("Evaluate throws an exception")
                .isNotNull()
                .isInstanceOf(JmriException.class)
                .hasMessage("Test JmriException");
#endif
        action->je = nullptr;
        action->re = new RuntimeException("Test RuntimeException");
#if 0
        thrown = catchThrowable( () -> socket->execute());
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
        thrown = catchThrowable( () -> socket->execute());
        assertThat(thrown)
                .withFailMessage("Evaluate does nothing")
                .isNull();
#endif
        // Test debug config
        socket->setEnabled(true);
        DefaultMaleDigitalActionSocket::DigitalActionDebugConfig* config = new DefaultMaleDigitalActionSocket::DigitalActionDebugConfig();
        socket->setDebugConfig(config);
        action->je = nullptr;
        action->re = nullptr;
        config->_dontExecute = true;
        action->_hasExecuted = false;
        socket->execute();
        Assert::assertFalse(action->_hasExecuted, __FILE__, __LINE__);
        config->_dontExecute = false;
        action->_hasExecuted = false;
        socket->execute();
        Assert::assertTrue(action->_hasExecuted, __FILE__, __LINE__);
    }

    ////@Test
    /*public*/  void DefaultMaleDigitalActionSocketTest::testVetoableChange() {
        MyDigitalAction* action = new MyDigitalAction("IQDA321");
        DefaultMaleDigitalActionSocket* socket = new DefaultMaleDigitalActionSocket(manager, action);
        Assert::assertNotNull("exists", socket, __FILE__, __LINE__);

        PropertyChangeEvent* evt = new PropertyChangeEvent(/*"Source"*/this, "Prop", QVariant(), QVariant());

        action->_vetoChange = true;
#if 0
        Throwable* thrown = catchThrowable( () -> socket->vetoableChange(evt));
        assertThat(thrown)
                .withFailMessage("vetoableChange() does throw")
                .isNotNull()
                .isInstanceOf(PropertyVetoException.class)
                .hasMessage("Veto change");
#endif
        action->_vetoChange = false;
#if 0
        thrown = catchThrowable( () -> socket->vetoableChange(evt));
        assertThat(thrown)
                .withFailMessage("vetoableChange() does not throw")
                .isNull();
#endif
    }

    ////@Test
    /*public*/  void DefaultMaleDigitalActionSocketTest::testCompareSystemNameSuffix() {
        MyDigitalAction* action1 = new MyDigitalAction("IQDA1");
        DefaultMaleDigitalActionSocket* socket1 = new DefaultMaleDigitalActionSocket(manager, action1);

        MyDigitalAction* action2 = new MyDigitalAction("IQDA01");
        DefaultMaleDigitalActionSocket* socket2 = new DefaultMaleDigitalActionSocket(manager, action2);

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
    /*public*/  void DefaultMaleDigitalActionSocketTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        DigitalActionBean* actionA = new ActionTurnout("IQDA321", "");
        Assert::assertNotNull("exists", (QObject*)actionA, __FILE__, __LINE__);
        DigitalActionBean* actionB = new MyDigitalAction("IQDA322");
        Assert::assertNotNull("exists", (QObject*)actionA, __FILE__, __LINE__);

        manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");

        maleSocketA = ((DefaultDigitalActionManager*)
                InstanceManager::getDefault("DigitalActionManager"))
                        ->registerAction(actionA);
        Assert::assertNotNull("exists", (QObject*)maleSocketA, __FILE__, __LINE__);

        maleSocketB =((DefaultDigitalActionManager*)
                InstanceManager::getDefault("DigitalActionManager"))
                        ->registerAction(actionB);
        Assert::assertNotNull("exists", (QObject*)maleSocketB, __FILE__, __LINE__);
    }

    //@AfterEach
    //@Override
    /*public*/  void DefaultMaleDigitalActionSocketTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }


