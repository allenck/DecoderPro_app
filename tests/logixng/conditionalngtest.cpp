#include "conditionalngtest.h"
#include "junitutil.h"
#include "assert1.h"
#include "instancemanager.h"
#include "conditionalng.h"
#include "defaultlogixng.h"
#include "defaultlogixngmanager.h"
#include "defaultconditionalngmanager.h"
#include "junitappender.h"
#include "maledigitalactionsocket.h"
#include "defaultdigitalactionmanager.h"
#include "digitalmany.h"
#include "runtimeexception.h"
#include "defaultconditionalng.h"
#include "logixng_thread.h"

/**
 * Test ConditionalNG
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  class ConditionalNGTest {

    //@Test
    /*public*/  void ConditionalNGTest::testGetBeanType() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        ConditionalNG* conditionalNG =(DefaultConditionalNG*) ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
        Assert::assertEquals("beanType is correct", "ConditionalNG", conditionalNG->getBeanType(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ConditionalNGTest::testGetParent() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        ConditionalNG* conditionalNG_1 = (DefaultConditionalNG*)((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
        Assert::assertTrue("getParent() returns correct value", logixNG == conditionalNG_1->getParent(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ConditionalNGTest::testGetLogixNG() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        DefaultConditionalNG* conditionalNG_1 = (DefaultConditionalNG*)((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
        Assert::assertTrue("getLogixNG() returns correct value", logixNG == ((AbstractBase*)conditionalNG_1->bself())->getLogixNG(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ConditionalNGTest::testGetRoot() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        DefaultConditionalNG* conditionalNG_1 = (DefaultConditionalNG*)((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
        Assert::assertTrue("getRoot() returns correct value", logixNG == ((AbstractBase*)conditionalNG_1->bself())->getRoot(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ConditionalNGTest::testState() /*throws JmriException*/ {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->
                createLogixNG("A new logix for test");  // NOI18N
        Assert::assertTrue("getState() returns UNKNOWN", logixNG->getState() == LogixNG::UNKNOWN, __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Unexpected call to getState in DefaultLogixNG.");
        logixNG->setState(LogixNG::INCONSISTENT);
        JUnitAppender::assertWarnMessage("Unexpected call to setState in DefaultLogixNG.");
        Assert::assertTrue("getState() returns UNKNOWN", logixNG->getState() == LogixNG::UNKNOWN, __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Unexpected call to getState in DefaultLogixNG.");
    }

    /*public*/  void ConditionalNGTest::setupInitialConditionalNGTree(ConditionalNG* conditionalNG) {
        try {
            DigitalActionManager* digitalActionManager =((DefaultDigitalActionManager*)
                    InstanceManager::getDefault("DigitalActionManager"));

            FemaleSocket* femaleSocket = conditionalNG->getFemaleSocket();
            MaleDigitalActionSocket* actionManySocket = ((DefaultDigitalActionManager*)
                    InstanceManager::getDefault("DigitalActionManager"))
                            ->registerAction(new DigitalMany(((AbstractManager*)digitalActionManager->mself())->getAutoSystemName(), nullptr));
            femaleSocket->_connect(actionManySocket);
//            femaleSocket.setLock(Base.Lock.HARD_LOCK);

//            femaleSocket = actionManySocket.getChild(0);
//            MaleDigitalActionSocket actionIfThenSocket =
//                    InstanceManager::getDefault(DigitalActionManager.class)
//                            .registerAction(new IfThenElse(digitalActionManager.getAutoSystemName(), null, IfThenElse.Type.TRIGGER_ACTION));
//            femaleSocket.connect(actionIfThenSocket);
        } catch (SocketAlreadyConnectedException* e) {
            // This should never be able to happen.
            throw new RuntimeException(e->getMessage());
        }
    }

    //@Test
    /*public*/  void ConditionalNGTest::testConnectDisconnect() /*throws SocketAlreadyConnectedException*/ {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->
                createLogixNG("A new logix for test");  // NOI18N
        DefaultConditionalNG* conditionalNG = (DefaultConditionalNG*)
                ((DefaultConditionalNGManager*) InstanceManager::getDefault("ConditionalNG_Manager"))
                        ->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
        Assert::assertEquals("socket name is correct", nullptr, conditionalNG->getSocketSystemName(), __FILE__, __LINE__);
        setupInitialConditionalNGTree(conditionalNG);
        MaleSocket* many = conditionalNG->getChild(0)->getConnectedSocket();
        Assert::assertTrue("description is correct", "Many" == (many->getLongDescription()), __FILE__, __LINE__);
        Assert::assertEquals("socket name is correct", many->getSystemName(), conditionalNG->getSocketSystemName(), __FILE__, __LINE__);
        conditionalNG->getChild(0)->_disconnect();
        Assert::assertEquals("socket name is correct", nullptr, conditionalNG->getSocketSystemName(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ConditionalNGTest::testSetSocketName() /*throws SocketAlreadyConnectedException */{
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->
                createLogixNG("A new logix for test");  // NOI18N
        DefaultConditionalNG* conditionalNG = (DefaultConditionalNG*)
                ((DefaultConditionalNGManager*) InstanceManager::getDefault("ConditionalNG_Manager"))
                        ->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N

        DefaultDigitalActionManager* digitalActionManager =
                (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");

        MaleDigitalActionSocket* actionManySocket =
                ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                        ->registerAction(new DigitalMany(((AbstractManager*)digitalActionManager->mself())->getAutoSystemName(), ""));


        Assert::assertEquals("socket name is correct", nullptr, conditionalNG->getSocketSystemName(), __FILE__, __LINE__);
        conditionalNG->setSocketSystemName("Abc");
        Assert::assertEquals("socket name is correct", "Abc", conditionalNG->getSocketSystemName(), __FILE__, __LINE__);
        conditionalNG->setSocketSystemName("Def");
        Assert::assertEquals("socket name is correct", "Def", conditionalNG->getSocketSystemName(), __FILE__, __LINE__);
        conditionalNG->getFemaleSocket()->_connect(actionManySocket);
        Assert::assertEquals("socket name is correct",
                ((NamedBean*)actionManySocket)->getSystemName(),
                conditionalNG->getSocketSystemName(), __FILE__, __LINE__);
        conditionalNG->setSocketSystemName("");
        Assert::assertEquals("socket name is correct", "", conditionalNG->getSocketSystemName(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ConditionalNGTest::testShortDescription() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->
                createLogixNG("A new logix for test");  // NOI18N
        ConditionalNG* conditionalNG_1 =(DefaultConditionalNG*) ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
        Assert::assertEquals("getLongDescription() returns correct value",
                "ConditionalNG: A conditionalNG", conditionalNG_1->getLongDescription(QLocale()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ConditionalNGTest::testLongDescription() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->
                createLogixNG("A new logix for test");  // NOI18N
        DefaultConditionalNG* conditionalNG_1 =(DefaultConditionalNG*) ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
        Assert::assertEquals("getLongDescription() returns correct value",
                "ConditionalNG: A conditionalNG", conditionalNG_1->getLongDescription(QLocale()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ConditionalNGTest::testGetChild() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->
                createLogixNG("A new logix for test");  // NOI18N
        DefaultConditionalNG* conditionalNG = (DefaultConditionalNG*)((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A new conditionalng for test");  // NOI18N

        Assert::assertNotNull("child(0) is not null", (QObject*)conditionalNG->getChild(0), __FILE__, __LINE__);

        bool hasThrown = false;
        try {
            conditionalNG->getChild(1);
        } catch (IllegalArgumentException* e) {
            hasThrown = true;
        }
        Assert::assertTrue("exception thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ConditionalNGTest::testGetChildCount() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->
                createLogixNG("A new logix for test");  // NOI18N
        DefaultConditionalNG* conditionalNG =(DefaultConditionalNG*) ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A new conditionalng for test");  // NOI18N
        Assert::assertEquals("conditionalNG has one child", 1, conditionalNG->getChildCount(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ConditionalNGTest::testGetCategory() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->
                createLogixNG("A new logix for test");  // NOI18N
        DefaultConditionalNG* conditionalNG = (DefaultConditionalNG*)((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A new conditionalng for test");  // NOI18N
        bool hasThrown = false;
        try {
            conditionalNG->getCategory();
        } catch (UnsupportedOperationException* e) {
            hasThrown = true;
        }
        Assert::assertTrue("exception thrown", hasThrown, __FILE__, __LINE__);
    }
#if 0
/*
    @Test
    public  void testSetLock() {
        ConditionalNG conditionalNG = InstanceManager::getDefault(ConditionalNG_Manager.class).createConditionalNG("A new conditionalng for test");  // NOI18N
        boolean hasThrown = false;
        try {
            conditionalNG.setLock(Lock.NONE);
        } catch (UnsupportedOperationException e) {
            hasThrown = true;
        }
        Assert::assertTrue("exception thrown", hasThrown);
    }
*/
#endif
    // The minimal setup for log4J
    //@Before
    /*public*/  void ConditionalNGTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();
    }

    //@After
    /*public*/  void ConditionalNGTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }
