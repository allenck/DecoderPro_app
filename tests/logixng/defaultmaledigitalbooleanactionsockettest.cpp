#include "defaultmaledigitalbooleanactionsockettest.h"
#include "junitutil.h"
#include "instancemanager.h"
#include "assert1.h"
#include "defaultdigitalbooleanactionmanager.h"
#include "logixng_thread.h"
#include "defaultmaledigitalbooleanactionsocket.h"
#include "digitalbooleanonchange.h"
#include "defaultconditionalngscaffold.h"
#include "runtimeexception.h"


DefaultMaleDigitalBooleanActionSocketTest::DefaultMaleDigitalBooleanActionSocketTest(QObject *parent) : MaleSocketTestBase(parent)
{

}
/**
 * Test ExpressionTimer
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  class DefaultMaleDigitalBooleanActionSocketTest extends MaleSocketTestBase{

    //@Override
    /*protected*/ QString DefaultMaleDigitalBooleanActionSocketTest::getNewSystemName() {
        return ((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))
                ->AbstractManager::getAutoSystemName();
    }

    //@Test
    /*public*/  void DefaultMaleDigitalBooleanActionSocketTest::testCtor() {
        DigitalBooleanActionBean* action = new DigitalBooleanOnChange("IQDB321", "", DigitalBooleanOnChange::Trigger::CHANGE);
        Assert::assertNotNull("exists", new DefaultMaleDigitalBooleanActionSocket(manager, action), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultMaleDigitalBooleanActionSocketTest::testEvaluate() /*throws JmriException*/ {
        ConditionalNG* conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;

        MyDigitalBooleanAction* action = new MyDigitalBooleanAction("IQDB321");
        action->setParent(conditionalNG);

        DefaultMaleDigitalBooleanActionSocket* socket = new DefaultMaleDigitalBooleanActionSocket(manager, action);
        Assert::assertNotNull("exists", socket, __FILE__, __LINE__);

        socket->setParent(conditionalNG);
        socket->setEnabled(true);
        socket->setErrorHandlingType(ErrorHandlingType::ThrowException);

        action->je = nullptr;
        action->re = nullptr;
        socket->execute(false, false);
        Assert::assertFalse(action->_hasChangedToTrue, __FILE__, __LINE__);
        Assert::assertFalse(action->_hasChangedToFalse, __FILE__, __LINE__);
        socket->execute(true, false);
        Assert::assertTrue(action->_hasChangedToTrue, __FILE__, __LINE__);
        Assert::assertFalse(action->_hasChangedToFalse, __FILE__, __LINE__);
        socket->execute(false, true);
        Assert::assertFalse(action->_hasChangedToTrue, __FILE__, __LINE__);
        Assert::assertTrue(action->_hasChangedToFalse, __FILE__, __LINE__);

        action->je = new JmriException("Test JmriException");
        action->re = nullptr;
        Throwable* thrown = nullptr;
//          catchThrowable( () -> socket->execute(false, false));
//        assertThat(thrown)
//                .withFailMessage("Evaluate throws an exception")
//                .isNotNull()
//                .isInstanceOf(JmriException.class)
//                .hasMessage("Test JmriException");
        try{
         socket->execute(false, false);
        } catch (Throwable* thrown)
        {
         if(static_cast<JmriException*>(thrown))
          Assert::assertTrue("Evaluate throws an exception", thrown->getMessage() == "Test JmriException", __FILE__, __LINE__);
        }

        action->je = nullptr;
        action->re = new RuntimeException("Test RuntimeException");
//        thrown = catchThrowable( () -> socket->execute(false, false));
//        assertThat(thrown)
//                .withFailMessage("Evaluate throws an exception")
//                .isNotNull()
//                .isInstanceOf(RuntimeException.class)
//                .hasMessage("Test RuntimeException");
        thrown = nullptr;
        try{
         socket->execute(false, false);
        }
        catch(Throwable* thrown)
        {

        }
        if(thrown && static_cast<RuntimeException*>(thrown))
        {
         Assert::assertTrue("Evaluate throws an exception", thrown->getMessage() =="Test RuntimeException" , __FILE__, __LINE__);
        }
        // If the socket is not enabled, it shouldn't do anything
        socket->setEnabled(false);
        action->re = new RuntimeException("Test RuntimeException");
//        thrown = catchThrowable( () -> socket->execute(false, false));
//        assertThat(thrown)
//                .withFailMessage("Evaluate does nothing")
//                .isNull();
        thrown = nullptr;
        try{
         socket->execute(false, false);
        }catch(Throwable* thrown){}
        Assert::assertNull("Evaluate does nothing",  (QObject*)thrown, __FILE__, __LINE__);

        // Test debug config
        socket->setEnabled(true);
        DefaultMaleDigitalBooleanActionSocket::DigitalBooleanActionDebugConfig* config = new DefaultMaleDigitalBooleanActionSocket::DigitalBooleanActionDebugConfig();
        socket->setDebugConfig(config);
        action->je = nullptr;
        action->re = nullptr;
        config->_dontExecute = true;
        action->_hasChangedToTrue = false;
        action->_hasChangedToFalse = false;
        socket->execute(true, false);
        Assert::assertFalse(action->_hasChangedToTrue, __FILE__, __LINE__);
        Assert::assertFalse(action->_hasChangedToFalse, __FILE__, __LINE__);
        action->_hasChangedToTrue = false;
        action->_hasChangedToFalse = false;
        socket->execute(false, false);
        Assert::assertFalse(action->_hasChangedToTrue, __FILE__, __LINE__);
        Assert::assertFalse(action->_hasChangedToFalse, __FILE__, __LINE__);
        config->_dontExecute = false;
        action->_hasChangedToTrue = false;
        action->_hasChangedToFalse = false;
        socket->execute(true, false);
        Assert::assertTrue(action->_hasChangedToTrue, __FILE__, __LINE__);
        Assert::assertFalse(action->_hasChangedToFalse, __FILE__, __LINE__);
        action->_hasChangedToTrue = false;
        action->_hasChangedToFalse = false;
        socket->execute(false, true);
        Assert::assertFalse(action->_hasChangedToTrue, __FILE__, __LINE__);
        Assert::assertTrue(action->_hasChangedToFalse, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultMaleDigitalBooleanActionSocketTest::testVetoableChange() {
        MyDigitalBooleanAction* action = new MyDigitalBooleanAction("IQDB321");
        DefaultMaleDigitalBooleanActionSocket* socket = new DefaultMaleDigitalBooleanActionSocket(manager, action);
        Assert::assertNotNull("exists", socket, __FILE__, __LINE__);

        PropertyChangeEvent* evt = new PropertyChangeEvent(/*"Source"*/this, "Prop", QVariant(), QVariant());

        action->_vetoChange = true;
//        Throwable thrown = catchThrowable( () -> socket->vetoableChange(evt));
//        assertThat(thrown)
//                .withFailMessage("vetoableChange() does throw")
//                .isNotNull()
//                .isInstanceOf(PropertyVetoException.class)
//                .hasMessage("Veto change");
        Throwable* thrown = nullptr;
        try{
         socket->vetoableChange(evt);
        }catch(Throwable* thrown) {}
        bool b = thrown && static_cast<Throwable*>(thrown) && (thrown->getMessage() == "Veto change");
        Assert::assertTrue("vetoableChange() does throw", (QObject*)thrown, __FILE__, __LINE__);
        action->_vetoChange = false;
//        thrown = catchThrowable( () -> socket->vetoableChange(evt));
//        assertThat(thrown)
//                .withFailMessage("vetoableChange() does not throw")
//                .isNull();
        thrown = nullptr;
        try{
         socket->vetoableChange(evt);
        } catch(Throwable* thrown){}
        Assert::assertTrue("vetoableChange() does not throw", thrown == nullptr, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultMaleDigitalBooleanActionSocketTest::testCompareSystemNameSuffix() {
        MyDigitalBooleanAction* action1 = new MyDigitalBooleanAction("IQDB1");
        DefaultMaleDigitalBooleanActionSocket* socket1 = new DefaultMaleDigitalBooleanActionSocket(manager, action1);

        MyDigitalBooleanAction* action2 = new MyDigitalBooleanAction("IQDB01");
        DefaultMaleDigitalBooleanActionSocket* socket2 = new DefaultMaleDigitalBooleanActionSocket(manager, action2);

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
    /*public*/  void DefaultMaleDigitalBooleanActionSocketTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        DigitalBooleanActionBean* actionA = new DigitalBooleanOnChange("IQDB321", "", DigitalBooleanOnChange::Trigger::CHANGE);
        Assert::assertNotNull("exists", (QObject*)actionA, __FILE__, __LINE__);
        DigitalBooleanActionBean* actionB = new MyDigitalBooleanAction("IQDB322");
        Assert::assertNotNull("exists", (QObject*)actionA, __FILE__, __LINE__);

        manager = (DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager");

        maleSocketA =
                ((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))
                        ->registerAction(actionA);
        Assert::assertNotNull("exists", (QObject*)maleSocketA, __FILE__, __LINE__);

        maleSocketB =
                ((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))
                        ->registerAction(actionB);
        Assert::assertNotNull("exists", (QObject*)maleSocketB, __FILE__, __LINE__);
    }

    //@AfterEach
    //@Override
    /*public*/  void DefaultMaleDigitalBooleanActionSocketTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }


