#include "logixngtest.h"
#include "instancemanager.h"
#include "assert1.h"
#include "logixng_thread.h"
#include "defaultlogixngmanager.h"
#include "junitappender.h"
#include "defaultconditionalngmanager.h"
#include "junitutil.h"
#include "defaultlogixng.h"

/**
 * Test LogixNG
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  class LogixNGTest {

    //@Test
    /*public*/  void LogixNGTest::testContains() {
        QSet<LogixNG*> set = QSet<LogixNG*>();

        DefaultLogixNG* logixNG1 = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix1 for test");  // NOI18N
        DefaultLogixNG* logixNG2 = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix2 for test");  // NOI18N
        LogixNG* logixNG3 = ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix3 for test");  // NOI18N
        DefaultLogixNG* logixNG4 = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix4 for test");  // NOI18N
        DefaultLogixNG* logixNG5 = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix5 for test");  // NOI18N

        set.insert(logixNG1);
        set.insert(logixNG3);
        set.insert(logixNG5);
        Assert::assertTrue("set size = 3", set.size() == 3,__FILE__, __LINE__);
        Assert::assertTrue("contains is true", set.contains(logixNG1),__FILE__, __LINE__);
        Assert::assertTrue("contains is true", set.contains(logixNG3),__FILE__, __LINE__);
        Assert::assertTrue("contains is true", set.contains(logixNG5),__FILE__, __LINE__);
        Assert::assertFalse("contains is false", set.contains(logixNG2),__FILE__, __LINE__);

    }

    //@Test
    /*public*/  void LogixNGTest::testSetParent() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        bool hasThrown = false;
        try {
            logixNG->setParent(nullptr);
        } catch (UnsupportedOperationException* e) {
            hasThrown = true;
        }
        Assert::assertTrue("exception thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void LogixNGTest::testGetParent() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        Assert::assertNull("getParent() returns null", (QObject*)logixNG->getParent(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void LogixNGTest::testState() /*throws JmriException*/ {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        Assert::assertTrue("getState() returns UNKNOWN", logixNG->getState() == LogixNG::UNKNOWN, __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Unexpected call to getState in DefaultLogixNG.", __FILE__, __LINE__);
        logixNG->setState(LogixNG::INCONSISTENT);
        JUnitAppender::assertWarnMessage("Unexpected call to setState in DefaultLogixNG.", __FILE__, __LINE__);
        Assert::assertTrue("getState() returns UNKNOWN", logixNG->getState() == LogixNG::UNKNOWN, __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Unexpected call to getState in DefaultLogixNG.", __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void LogixNGTest::testShortDescription() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        Assert::assertEquals("getShortDescription() returns correct value",
                "LogixNG", logixNG->getShortDescription(QLocale()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void LogixNGTest::testLongDescription() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        Assert::assertEquals("getLongDescription() returns correct value",
                "LogixNG: A new logix for test", logixNG->getLongDescription(QLocale()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void LogixNGTest::testGetChild() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        bool hasThrown = false;
        try {
            logixNG->getChild(0);
        } catch (UnsupportedOperationException* e) {
            hasThrown = true;
        }
        Assert::assertTrue("exception thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void LogixNGTest::testGetChildCount() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        bool hasThrown = false;
        try {
            logixNG->getChildCount();
        } catch (UnsupportedOperationException* e) {
            hasThrown = true;
        }
        Assert::assertTrue("exception thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void LogixNGTest::testGetCategory() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        bool hasThrown = false;
        try {
            logixNG->getCategory();
        } catch (UnsupportedOperationException* e) {
            hasThrown = true;
        }
        Assert::assertTrue("exception thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void LogixNGTest::testSwapConditionalNG() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        ConditionalNG* conditionalNG_1 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
        ConditionalNG* conditionalNG_2 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A second conditionalNG");  // NOI18N
        ConditionalNG* conditionalNG_3 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A third conditionalNG");  // NOI18N
        ConditionalNG* conditionalNG_4 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A forth conditionalNG");  // NOI18N

        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_1 == logixNG->getConditionalNG(0), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_2 == logixNG->getConditionalNG(1), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_3 == logixNG->getConditionalNG(2), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_4 == logixNG->getConditionalNG(3), __FILE__, __LINE__);

        logixNG->swapConditionalNG(0, 0);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_1 == logixNG->getConditionalNG(0), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_2 == logixNG->getConditionalNG(1), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_3 == logixNG->getConditionalNG(2), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_4 == logixNG->getConditionalNG(3), __FILE__, __LINE__);

        logixNG->swapConditionalNG(1, 0);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_1 == logixNG->getConditionalNG(0), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_2 == logixNG->getConditionalNG(1), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_3 == logixNG->getConditionalNG(2), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_4 == logixNG->getConditionalNG(3), __FILE__, __LINE__);

        logixNG->swapConditionalNG(0, 1);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_2 == logixNG->getConditionalNG(0), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_1 == logixNG->getConditionalNG(1), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_3 == logixNG->getConditionalNG(2), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_4 == logixNG->getConditionalNG(3), __FILE__, __LINE__);

        logixNG->swapConditionalNG(0, 2);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_3 == logixNG->getConditionalNG(0), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_2 == logixNG->getConditionalNG(1), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_1 == logixNG->getConditionalNG(2), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_4 == logixNG->getConditionalNG(3), __FILE__, __LINE__);

        logixNG->swapConditionalNG(2, 3);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_3 == logixNG->getConditionalNG(0), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_2 == logixNG->getConditionalNG(1), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_4 == logixNG->getConditionalNG(2), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_1 == logixNG->getConditionalNG(3), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void LogixNGTest::testGetConditionalNG() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        ConditionalNG* conditionalNG_1 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
        ConditionalNG* conditionalNG_2 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A second conditionalNG");  // NOI18N
        ConditionalNG* conditionalNG_3 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A third conditionalNG");  // NOI18N
        ConditionalNG* conditionalNG_4 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A forth conditionalNG");  // NOI18N

        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_1 == logixNG->getConditionalNG(0), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_2 == logixNG->getConditionalNG(1), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_3 == logixNG->getConditionalNG(2), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_4 == logixNG->getConditionalNG(3), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", nullptr == logixNG->getConditionalNG(-1), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", nullptr == logixNG->getConditionalNG(4), __FILE__, __LINE__);
    }

//     //@Test
//     /*public*/  void testAddConditionalNG() {
//         LogixNG logixNG = ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
//         ConditionalNG* conditionalNG_1 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, null);
// //         Assert::assertTrue("conditionalNG added", logixNG->addConditionalNG(conditionalNG_1));
//         ConditionalNG* conditionalNG_2 =
//                 new DefaultConditionalNG(conditionalNG_1.getSystemName(), null);
//         Assert::assertFalse("conditionalNG not added", logixNG->addConditionalNG(conditionalNG_2));
//         JUnitAppender::.assertWarnMessage("ConditionalNG* 'IQC:AUTO:0001' has already been added to LogixNG 'IQ:AUTO:0001'");
//         ConditionalNG* conditionalNG_3 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, null);
//         Assert::assertTrue("conditionalNG added", logixNG->addConditionalNG(conditionalNG_3));
//     }

    //@Test
    /*public*/  void LogixNGTest::testGetConditionalNGByUserName() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        ConditionalNG* conditionalNG_1 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "Abc");  // NOI18N
        ConditionalNG* conditionalNG_2 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "Def");  // NOI18N
        ConditionalNG* conditionalNG_3 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "Ghi");  // NOI18N
        ConditionalNG* conditionalNG_4 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "Jkl");  // NOI18N

        Assert::assertTrue("ConditionalNG* is correct",
                conditionalNG_1 == logixNG->getConditionalNGByUserName("Abc"), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct",
                conditionalNG_2 == logixNG->getConditionalNGByUserName("Def"), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct",
                conditionalNG_3 == logixNG->getConditionalNGByUserName("Ghi"), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct",
                conditionalNG_4 == logixNG->getConditionalNGByUserName("Jkl"), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct",
                nullptr == logixNG->getConditionalNGByUserName("Non existing bean"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void LogixNGTest::testDeleteConditionalNG() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        ConditionalNG* conditionalNG_1 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A first conditionalNG");  // NOI18N
        ConditionalNG* conditionalNG_2 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A second conditionalNG");  // NOI18N
        ConditionalNG* conditionalNG_3 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A third conditionalNG");  // NOI18N
        ConditionalNG* conditionalNG_4 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A forth conditionalNG");  // NOI18N
        ConditionalNG* conditionalNG_5 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A fifth conditionalNG");  // NOI18N
        ConditionalNG* conditionalNG_6 = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A sixth conditionalNG");  // NOI18N

        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_1 == logixNG->getConditionalNG(0), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_2 == logixNG->getConditionalNG(1), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_3 == logixNG->getConditionalNG(2), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_4 == logixNG->getConditionalNG(3), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_5 == logixNG->getConditionalNG(4), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_6 == logixNG->getConditionalNG(5), __FILE__, __LINE__);

        logixNG->deleteConditionalNG(conditionalNG_1);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_2 == logixNG->getConditionalNG(0), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_3 == logixNG->getConditionalNG(1), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_4 == logixNG->getConditionalNG(2), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_5 == logixNG->getConditionalNG(3), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_6 == logixNG->getConditionalNG(4), __FILE__, __LINE__);

        logixNG->deleteConditionalNG(conditionalNG_1);
        JUnitAppender::assertErrorMessage("attempt to delete ConditionalNG not in LogixNG: IQC:AUTO:0001", __FILE__, __LINE__);

        logixNG->deleteConditionalNG(conditionalNG_6);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_2 == logixNG->getConditionalNG(0), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_3 == logixNG->getConditionalNG(1), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_4 == logixNG->getConditionalNG(2), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_5 == logixNG->getConditionalNG(3), __FILE__, __LINE__);

        logixNG->deleteConditionalNG(conditionalNG_3);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_2 == logixNG->getConditionalNG(0), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_4 == logixNG->getConditionalNG(1), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_5 == logixNG->getConditionalNG(2), __FILE__, __LINE__);

        logixNG->deleteConditionalNG(conditionalNG_4);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_2 == logixNG->getConditionalNG(0), __FILE__, __LINE__);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_5 == logixNG->getConditionalNG(1), __FILE__, __LINE__);

        logixNG->deleteConditionalNG(conditionalNG_2);
        Assert::assertTrue("ConditionalNG* is correct", conditionalNG_5 == logixNG->getConditionalNG(0), __FILE__, __LINE__);

        logixNG->deleteConditionalNG(conditionalNG_5);
        Assert::assertTrue("LogixNG has no more conditionalNGs", 0 == logixNG->getNumConditionalNGs(), __FILE__, __LINE__);

        logixNG->deleteConditionalNG(conditionalNG_5);
        JUnitAppender::assertErrorMessage("attempt to delete ConditionalNG not in LogixNG: IQC:AUTO:0005", __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void LogixNGTest::testActivateLogixNG() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        MyConditionalNG* conditionalNG_1 = new MyConditionalNG("IQC1", "");
        logixNG->addConditionalNG(conditionalNG_1);
        conditionalNG_1->setEnabled(false);
        MyConditionalNG* conditionalNG_2 = new MyConditionalNG("IQC2", "");
        logixNG->addConditionalNG(conditionalNG_2);
        conditionalNG_2->setEnabled(true);
        MyConditionalNG* conditionalNG_3 = new MyConditionalNG("IQC3", "");
        logixNG->addConditionalNG(conditionalNG_3);
        conditionalNG_3->setEnabled(false);
        if (! logixNG->setParentForAllChildren(new QList<QString>())) throw new RuntimeException();

        Assert::assertFalse("conditionalNG_1 is enabled", conditionalNG_1->isEnabled(), __FILE__, __LINE__);
        Assert::assertTrue("conditionalNG_2 is enabled", conditionalNG_2->isEnabled(), __FILE__, __LINE__);
        Assert::assertFalse("conditionalNG_3 is enabled", conditionalNG_3->isEnabled(), __FILE__, __LINE__);

        Assert::assertFalse("listeners for conditionalNG_1 are not registered", conditionalNG_1->listenersAreRegistered, __FILE__, __LINE__);
        Assert::assertFalse("listeners for conditionalNG_2 are not registered", conditionalNG_2->listenersAreRegistered, __FILE__, __LINE__);
        Assert::assertFalse("listeners for conditionalNG_3 are not registered", conditionalNG_3->listenersAreRegistered, __FILE__, __LINE__);

        logixNG->setEnabled(true);
        Assert::assertFalse("listeners for conditionalNG_1 are not registered", conditionalNG_1->listenersAreRegistered, __FILE__, __LINE__);
        Assert::assertTrue("listeners for conditionalNG_2 are registered", conditionalNG_2->listenersAreRegistered, __FILE__, __LINE__);
        Assert::assertFalse("listeners for conditionalNG_3 are not registered", conditionalNG_3->listenersAreRegistered, __FILE__, __LINE__);

        // Activate LogixNG multiple times should not be a problem
        logixNG->setEnabled(true);
        Assert::assertFalse("listeners for conditionalNG_1 are not registered", conditionalNG_1->listenersAreRegistered, __FILE__, __LINE__);
        Assert::assertTrue("listeners for conditionalNG_2 are registered", conditionalNG_2->listenersAreRegistered, __FILE__, __LINE__);
        Assert::assertFalse("listeners for conditionalNG_3 are not registered", conditionalNG_3->listenersAreRegistered, __FILE__, __LINE__);

        logixNG->setEnabled(false);
        Assert::assertFalse("listeners for conditionalNG_1 are not registered", conditionalNG_1->listenersAreRegistered, __FILE__, __LINE__);
        Assert::assertFalse("listeners for conditionalNG_2 are not registered", conditionalNG_2->listenersAreRegistered, __FILE__, __LINE__);
        Assert::assertFalse("listeners for conditionalNG_3 are not registered", conditionalNG_3->listenersAreRegistered, __FILE__, __LINE__);

        // DeActivate LogixNG multiple times should not be a problem
        logixNG->setEnabled(false);
        Assert::assertFalse("listeners for conditionalNG_1 are not registered", conditionalNG_1->listenersAreRegistered, __FILE__, __LINE__);
        Assert::assertFalse("listeners for conditionalNG_2 are not registered", conditionalNG_2->listenersAreRegistered, __FILE__, __LINE__);
        Assert::assertFalse("listeners for conditionalNG_3 are not registered", conditionalNG_3->listenersAreRegistered, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void LogixNGTest::testGetConditionalNG_WithoutParameters() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        bool hasThrown = false;
        try {
            ((AbstractBase*)logixNG->bself())->getConditionalNG();
        } catch (UnsupportedOperationException* e) {
            hasThrown = true;
        }
        Assert::assertTrue("exception thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void LogixNGTest::testGetLogixNG() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        Assert::assertTrue("logixNG is correct", logixNG == logixNG->getLogixNG(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void LogixNGTest::testGetRoot() {
        DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        Assert::assertTrue("root is correct", logixNG == logixNG->getRoot(), __FILE__, __LINE__);
    }
#if 0
    //@Test
    /*public*/  void testPrintTree() {
        final String newLine = System.lineSeparator();
        StringBuilder expectedResult = new StringBuilder();
        expectedResult
                .append("LogixNG: A new logix for test").append(newLine)
                .append("...ConditionalNG: A conditionalNG").append(newLine)
                .append("......! A").append(newLine)
                .append(".........Many ::: Use default").append(newLine)
                .append("............! A1").append(newLine)
                .append("...............If Then Else. Execute on change ::: Use default").append(newLine)
                .append("..................? If").append(newLine)
                .append(".....................Socket not connected").append(newLine)
                .append("..................! Then").append(newLine)
                .append(".....................Socket not connected").append(newLine)
                .append("..................! Else").append(newLine)
                .append(".....................Socket not connected").append(newLine)
                .append("............! A2").append(newLine)
                .append("...............Socket not connected").append(newLine);

        StringWriter writer = new StringWriter();
        LogixNG logixNG = ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        ConditionalNG* conditionalNG = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
        setupInitialConditionalNGTree(conditionalNG);
        logixNG->printTree(new PrintWriter(writer), "...", new MutableInt(0));
        String resultStr = writer.toString();
/*
        System.err.format("=======================================%n");
        System.err.format("=======================================%n");
        System.err.format("=======================================%n");
        System.err.format("=======================================%n");
        System.err.format(expectedResult.toString());
        System.err.format("=======================================%n");
        System.err.format("=======================================%n");
        System.err.format(resultStr);
        System.err.format("=======================================%n");
        System.err.format("=======================================%n");
        System.err.format("=======================================%n");
*/
        Assert::assertEquals("Strings matches", expectedResult.toString(), resultStr);
    }

    //@Test
    /*public*/  void testBundleClass() {
        Assert::assertTrue("bundle is correct", "Test Bundle bb aa cc".equals(Bundle.getMessage("TestBundle", "aa", "bb", "cc")));
        Assert::assertTrue("bundle is correct", "Generic".equals(Bundle.getMessage(Locale.US, "SocketTypeGeneric")));
        Assert::assertTrue("bundle is correct", "Test Bundle bb aa cc".equals(Bundle.getMessage(Locale.US, "TestBundle", "aa", "bb", "cc")));
    }

    //@Test
    /*public*/  void testCategory() {
        Assert::assertTrue("isChangeableByUser is correct", "Item".equals(Category.ITEM.toString()));
        Assert::assertTrue("isChangeableByUser is correct", "Common".equals(Category.COMMON.toString()));
        Assert::assertTrue("isChangeableByUser is correct", "Other".equals(Category.OTHER.toString()));
    }

    /*public*/  void setupInitialConditionalNGTree(ConditionalNG* conditionalNG) {
        try {
            DigitalActionManager digitalActionManager =
                    InstanceManager::getDefault(DigitalActionManager.class);

            FemaleSocket femaleSocket = conditionalNG.getFemaleSocket();
            MaleDigitalActionSocket actionManySocket =
                    InstanceManager::getDefault(DigitalActionManager.class)
                            .registerAction(new DigitalMany(digitalActionManager.getAutoSystemName(), null));
            femaleSocket.connect(actionManySocket);
//            femaleSocket.setLock(Base.Lock.HARD_LOCK);

            femaleSocket = actionManySocket.getChild(0);
            MaleDigitalActionSocket actionIfThenSocket =
                    InstanceManager::getDefault(DigitalActionManager.class)
                            .registerAction(new IfThenElse(digitalActionManager.getAutoSystemName(), null));
            femaleSocket.connect(actionIfThenSocket);
        } catch (SocketAlreadyConnectedException e) {
            // This should never be able to happen.
            throw new RuntimeException(e);
        }
    }

    //@Test
    /*public*/  void testManagers() throws SocketAlreadyConnectedException {
        String systemName;
        LogixNG logixNG = ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        ConditionalNG* conditionalNG = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
        setupInitialConditionalNGTree(conditionalNG);
        MaleSocket many = conditionalNG.getChild(0).getConnectedSocket();
//        System.err.format("aa: %s%n", many.getLongDescription());
        Assert::assertTrue("description is correct", "Many".equals(many.getLongDescription()));
        MaleSocket ifThen = many.getChild(0).getConnectedSocket();
//        System.err.format("aa: %s%n", ifThen.getLongDescription());
        Assert::assertTrue("description is correct", "If Then Else. Execute on change".equals(ifThen.getLongDescription()));
        systemName = InstanceManager::getDefault(DigitalExpressionManager.class).getAutoSystemName();
        DigitalExpressionBean expression = new ExpressionTurnout(systemName, "An expression for test");  // NOI18N
        MaleSocket digitalExpressionBean = InstanceManager::getDefault(DigitalExpressionManager.class).registerExpression(expression);
        ifThen.getChild(0).connect(digitalExpressionBean);
//        InstanceManager::getDefault(jmri.DigitalExpressionManager.class).addExpression(new ExpressionTurnout(systemName, "LogixNG 102, DigitalExpressionBean 26"));  // NOI18N
        systemName = InstanceManager::getDefault(DigitalActionManager.class).getAutoSystemName();
        DigitalActionBean action = new ActionTurnout(systemName, "An action for test");  // NOI18N
        MaleSocket digitalActionBean = InstanceManager::getDefault(DigitalActionManager.class).registerAction(action);
        ifThen.getChild(1).connect(digitalActionBean);

        if (! logixNG->setParentForAllChildren(new ArrayList<>())) throw new RuntimeException();

        Assert::assertTrue("conditionalng is correct", conditionalNG == digitalActionBean.getConditionalNG());
        Assert::assertTrue("conditionalng is correct", conditionalNG == conditionalNG.getConditionalNG());
        Assert::assertTrue("logixlng is correct", logixNG == digitalActionBean.getLogixNG());
        Assert::assertTrue("logixlng is correct", logixNG == logixNG->getLogixNG());
    }

    //@Test
    /*public*/  void testSetup() throws SocketAlreadyConnectedException {

        LogixNG logixNG = InstanceManager::getDefault(LogixNG_Manager.class)
                .createLogixNG("A new logix for test");  // NOI18N
        DefaultConditionalNG* conditionalNG =
                (DefaultConditionalNG) InstanceManager::getDefault(ConditionalNG_Manager.class)
                        .createConditionalNG(logixNG, "A conditionalNG");  // NOI18N

        String systemName = InstanceManager::getDefault(DigitalActionManager.class).getAutoSystemName();
        DigitalActionBean action = new ActionTurnout(systemName, "An action for test");  // NOI18N
        MaleSocket digitalActionBean = InstanceManager::getDefault(DigitalActionManager.class).registerAction(action);

        conditionalNG.setSocketSystemName(systemName);
        logixNG->setup();

        if (! logixNG->setParentForAllChildren(new ArrayList<>())) throw new RuntimeException();

        Assert::assertTrue("conditionalng child is correct",
                "Set turnout '' to state Thrown"
                        .equals(conditionalNG.getChild(0).getConnectedSocket().getLongDescription()));
        Assert::assertEquals("conditionalng is correct", conditionalNG, digitalActionBean.getConditionalNG());
        Assert::assertEquals("logixlng is correct", logixNG, digitalActionBean.getLogixNG());
    }

    //@Test
    /*public*/  void testExceptions() {
        new SocketAlreadyConnectedException().getMessage();
    }

    //@Test
    /*public*/  void testBundle() {
        Assert::assertTrue("bean type is correct", "LogixNG".equals(new DefaultLogixNG("IQ55", null).getBeanType()));
        Assert::assertTrue("bean type is correct", "Digital action".equals(new IfThenElse("IQDA321", null).getBeanType()));
        Assert::assertTrue("bean type is correct", "Digital expression".equals(new And("IQDE321", null).getBeanType()));
    }
#endif
    // The minimal setup for log4J
    //@Before
    /*public*/  void LogixNGTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();
    }

    //@After
    /*public*/  void LogixNGTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }
