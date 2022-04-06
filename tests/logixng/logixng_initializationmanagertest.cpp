#include "logixng_initializationmanagertest.h"
#include "printwriter.h"
#include "logixng_thread.h"
#include "logixng.h"
#include "junitutil.h"
#include "logixng_initializationmanager.h"
#include "stringwriter.h"
#include "defaultlogixngmanager.h"
#include "instancemanager.h"
#include "defaultconditionalngmanager.h"
#include "defaultconditionalngscaffold.h"
#include "assert1.h"
#include "sleeperthread.h"
#include "defaultdigitalactionmanager.h"

/**
 * Test LogixNG_InitializationManager
 *
 * @author Daniel Bergqvist 2021
 */
///*public*/  class LogixNG_InitializationManagerTest {


    /*private*/ AtomicBoolean *LogixNG_InitializationManagerTest::getAB() {
        AtomicBoolean* ab =new AtomicBoolean();
        abList.append(ab);
        return ab;
    }

    /*private*/ bool LogixNG_InitializationManagerTest::checkAB() {
        for (AtomicBoolean* ab : abList) {
            if (!ab->get()) return false;
        }
        return true;
    }

    //@Test
    /*public*/  void LogixNG_InitializationManagerTest::testInitialization() /*throws SocketAlreadyConnectedException */{
        StringWriter* stringWriter = new StringWriter();
        PrintWriter* printWriter = new PrintWriter(stringWriter);

        LogixNG_Thread* threadL2 = LogixNG_Thread::createNewThread("Another thread");
        LogixNG_Thread* threadL7 = LogixNG_Thread::createNewThread("Some other thread");
        LogixNG_Thread* threadL5 = LogixNG_Thread::createNewThread("A different thread");

        MyAction::getLogixNG("IQ4", "LogixNG* 4", getAB(), printWriter, 0, LogixNG_Thread::DEFAULT_LOGIXNG_THREAD);
        MyAction::getLogixNG("IQ5", "LogixNG* 5", getAB(), printWriter, 100, threadL5->getThreadId());   // Long delay on separate thread
        MyAction::getLogixNG("IQ2", "LogixNG* 2", getAB(), printWriter, 500, threadL2->getThreadId());   // Long delay on separate thread
        MyAction::getLogixNG("IQ6", "LogixNG* 6", getAB(), printWriter, 0, LogixNG_Thread::DEFAULT_LOGIXNG_THREAD);
        MyAction::getLogixNG("IQ7", "LogixNG* 7", getAB(), printWriter, 100, threadL7->getThreadId());   // Long delay on separate thread
        MyAction::getLogixNG("IQ1", "LogixNG* 1", getAB(), printWriter, 0, LogixNG_Thread::DEFAULT_LOGIXNG_THREAD);
        MyAction::getLogixNG("IQ9", "LogixNG* 9", getAB(), printWriter, 100, LogixNG_Thread::DEFAULT_LOGIXNG_THREAD);
        MyAction::getLogixNG("IQ8", "LogixNG* 8", getAB(), printWriter, 0, LogixNG_Thread::DEFAULT_LOGIXNG_THREAD);
        MyAction::getLogixNG("IQ3", "LogixNG* 3", getAB(), printWriter, 0, LogixNG_Thread::DEFAULT_LOGIXNG_THREAD);

        LogixNG* l2 = (LogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->getBySystemName("IQ2")->self();
        LogixNG* l7 = (LogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->getBySystemName("IQ7")->self();
        LogixNG* l8 = (LogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->getBySystemName("IQ8")->self();

        LogixNG_InitializationManager* initManager = (LogixNG_InitializationManager*)
                InstanceManager::getDefault("LogixNG_InitializationManager");

        initManager->add(l7);
        initManager->add(l2);
        initManager->add(l8);
#if 1
        // No LogixNG* has been executed yet.
        Assert::assertEquals("Strings are equal", "", stringWriter->toString(), __FILE__, __LINE__);

        ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))
                ->activateAllLogixNGs(true, true);

        //boolean result = JUnitUtil.waitFor(() -> {return checkAB();});
        ReleaseUntil_LNGI* r1 = new ReleaseUntil_LNGI(this);
        bool result = JUnitUtil::waitFor(r1, __FILE__, __LINE__);
        Assert::assertTrue(result, __FILE__, __LINE__);

        QString expectedResult =
                // These are registered in the init manager
                "LogixNG* 7: start\n" \
                "LogixNG* 7: end\n" \
                "LogixNG* 2: start\n" \
                "LogixNG* 2: end\n" \
                "LogixNG* 8: start\n" \
                "LogixNG* 8: end\n";
        Assert::assertTrue(stringWriter->toString().startsWith(expectedResult), __FILE__, __LINE__);
 #endif
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void LogixNG_InitializationManagerTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager(false);
    }

    //@After
    /*public*/  void LogixNG_InitializationManagerTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }



//    /*private*/ /*static*/ /*final*/ class MyAction extends ActionAtomicBoolean {

//        /*private*/ final AtomicBoolean _ab;
//        /*private*/ final PrintWriter _printWriter;
//        /*private*/ final long _delay;

        /*public*/  MyAction::MyAction(
                QString userName,
                AtomicBoolean* ab,
                PrintWriter* printWriter,
                long delay) : ActionAtomicBoolean(ab, false){

            //super(ab, false);
            AbstractNamedBean::setUserName(userName);
            _ab = ab;
            _printWriter = printWriter;
            _delay = delay;
        }

        //@Override
        /*public*/  void MyAction::execute() {
//            System.out.format("%s: start\n", getUserName());
            _printWriter->format("%s: start\n", AbstractNamedBean::getUserName().toStdString().c_str());
            try {
                SleeperThread::msleep(_delay);
            } catch (InterruptedException* ex) {
//                ex.printStackTrace(_printWriter);
            }
//            System.out.format("%s: end\n", getUserName());
            _printWriter->format("%s: end\n", AbstractNamedBean::getUserName().toStdString().c_str());
            _printWriter->flush();
            _ab->set(true);
        }

        /*public*/  /*static*/ LogixNG* MyAction::getLogixNG(
                QString systemName,
                QString userName,
                AtomicBoolean* ab,
                PrintWriter* printWriter,
                long delay,
                int threadID)
                /*throws SocketAlreadyConnectedException*/ {

            LogixNG* logixNG =
                    ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))
                            ->createLogixNG(systemName, nullptr);

            systemName =
                    ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))
                            ->AbstractManager::getAutoSystemName();
            DefaultConditionalNG* conditionalNG =
                    new DefaultConditionalNGScaffold(systemName, "", threadID);
            ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->Register((AbstractNamedBean*)conditionalNG->self());
            conditionalNG->setEnabled(true);
            logixNG->addConditionalNG(conditionalNG);

            MyAction* action = new MyAction(userName, ab, printWriter, delay);
            MaleSocket* socket = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
            conditionalNG->getChild(0)->_connect(socket);

            logixNG->setEnabled(true);

            return logixNG;
        }


