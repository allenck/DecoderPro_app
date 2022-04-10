#include "truetest.h"
#include "logixng_thread.h"
#include "instancemanager.h"
#include "assert1.h"
#include "junitutil.h"
#include "true.h"
#include "defaultlogixngmanager.h"
#include "ifthenelse.h"
#include "defaultdigitalactionmanager.h"
#include "atomicboolean.h"
#include "actionatomicboolean.h"
#include "defaultdigitalexpressionmanager.h"
#include "defaultconditionalngscaffold.h"
#include "defaultdigitalactionmanager.h"
#include "defaultconditionalngmanager.h"


TrueTest::TrueTest(QObject *parent) : AbstractDigitalExpressionTestBase(parent)
{
 setObjectName("TrueTest");
}

/**
 * Test True
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  class TrueTest extends AbstractDigitalExpressionTestBase {



    //@Override
    /*public*/  ConditionalNG* TrueTest::getConditionalNG() {
        return conditionalNG;
    }

    //@Override
    /*public*/  LogixNG* TrueTest::getLogixNG() {
        return logixNG;
    }

    //@Override
    /*public*/  MaleSocket* TrueTest::getConnectableChild() {
        return nullptr;
    }

    //@Override
    /*public*/  QString TrueTest::getExpectedPrintedTree() {
        return QString("Always true ::: Use default\n");
    }

    //@Override
    /*public*/  QString TrueTest::getExpectedPrintedTreeFromRoot() {
        return QString(
                "LogixNG: A new logix for test\n" \
                "   ConditionalNG: A conditionalNG\n" \
                "      ! A\n" \
                "         If Then Else. Execute on change ::: Use default\n" \
                "            ? If\n" \
                "               Always true ::: Use default\n" \
                "            ! Then\n" \
                "               Set the atomic boolean to true ::: Use default\n" \
                "            ! Else\n" \
                "               Socket not connected%n");
    }

    //@Override
    /*public*/  NamedBean* TrueTest::createNewBean(QString systemName) {
        return new True(systemName, "");
    }

    //@Override
    /*public*/  bool TrueTest::addNewSocket() {
        return false;
    }

    //@Test
    /*public*/  void TrueTest::testCtor() {
        True* expression2;

        expression2 = new True("IQDE321", "");
        Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
        Assert::assertNull("Username matches", expression2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Always true", expression2->getLongDescription(QLocale()), __FILE__, __LINE__);

        expression2 = new True("IQDE321", "My expression");
        Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
        Assert::assertEquals("Username matches", "My expression", expression2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Always true", expression2->getLongDescription(QLocale()), __FILE__, __LINE__);

        bool thrown = false;
        try {
            // Illegal system name
            new True("IQE55:12:XY11", "");
        } catch (IllegalArgumentException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);

        thrown = false;
        try {
            // Illegal system name
            new True("IQE55:12:XY11", "A name");
        } catch (IllegalArgumentException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void TrueTest::testGetChild() {
        Assert::assertTrue("getChildCount() returns 0", 0 == expressionTrue->getChildCount(), __FILE__, __LINE__);

        bool hasThrown = false;
        try {
            expressionTrue->getChild(0);
        } catch (UnsupportedOperationException* ex) {
            hasThrown = true;
            Assert::assertEquals("Error message is correct", "Not supported.", ex->getMessage(), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception is thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void TrueTest::testCategory() {
        Assert::assertTrue("Category matches", Category::OTHER == _base->getCategory(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void TrueTest::testDescription() {
        DigitalExpressionBean* e1 = new True("IQDE321", "");
        Assert::assertEquals("Always true",  (e1->getShortDescription()), __FILE__, __LINE__);
        Assert::assertEquals("Always true", (e1->getLongDescription()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void TrueTest::testExpression() /*throws Exception*/ {
        DigitalExpressionBean* t = new True("IQDE321", "");
        Assert::assertTrue("Expression is true",t->evaluate(), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void TrueTest::setUp() /*throws SocketAlreadyConnectedException*/ {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        _category = Category::COMMON;
        _isExternal = false;

        logixNG = ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;
        ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->Register((AbstractNamedBean*)conditionalNG->bself());
        conditionalNG->setRunDelayed(false);
        conditionalNG->setEnabled(true);
        logixNG->addConditionalNG((DefaultConditionalNG*)conditionalNG);
        IfThenElse* ifThenElse = new IfThenElse("IQDA321", "");
        MaleSocket* maleSocket = ((DefaultDigitalActionManager*)
                InstanceManager::getDefault("DigitalActionManager"))->registerAction(ifThenElse);
        conditionalNG->getChild(0)->_connect(maleSocket);

        expressionTrue = new True("IQDE321", "");
        MaleSocket* maleSocket2 = ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expressionTrue);
        ifThenElse->getChild(0)->_connect(maleSocket2);

        _base = expressionTrue;
        _baseMaleSocket = maleSocket2;

        atomicBoolean = new AtomicBoolean(false);
        actionAtomicBoolean = new ActionAtomicBoolean(atomicBoolean, true);
        MaleSocket* socketAtomicBoolean = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(actionAtomicBoolean);
        ifThenElse->getChild(1)->_connect(socketAtomicBoolean);

        if (! logixNG->setParentForAllChildren(new QList<QString>())) throw new RuntimeException();
        logixNG->setEnabled(true);
    }

    //@After
    /*public*/  void TrueTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }
