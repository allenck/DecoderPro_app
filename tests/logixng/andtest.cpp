#include "andtest.h"
#include "logixng_thread.h"
#include "junitutil.h"
#include "assert1.h"
#include "instancemanager.h"
#include "and.h"
#include "defaultdigitalexpressionmanager.h"
#include "true.h"
#include "defaultlogixngmanager.h"
#include "defaultconditionalngscaffold.h"
#include "defaultconditionalngmanager.h"
#include "ifthenelse.h"
#include "defaultdigitalactionmanager.h"
#include "expressionmemory.h"
#include "junitappender.h"

AndTest::AndTest(QObject *parent) : AbstractDigitalExpressionTestBase(parent)
{

}

/**
 * Test And
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  class AndTest extends AbstractDigitalExpressionTestBase {



    //@Override
    /*public*/  ConditionalNG* AndTest::getConditionalNG() {
        return conditionalNG;
    }

    //@Override
    /*public*/  LogixNG* AndTest::getLogixNG() {
        return logixNG;
    }

    //@Override
    /*public*/  MaleSocket* AndTest::getConnectableChild() {
        DigitalExpressionBean* childExpression = new True("IQDE999", "");
        MaleSocket* maleSocketChild = ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(childExpression);
        return maleSocketChild;
    }

    //@Override
    /*public*/  QString AndTest::getExpectedPrintedTree() {
        return QString(
                "And ::: Use default\n" \
                "   ? E1\n" \
                "      Socket not connected\n");
    }

    //@Override
    /*public*/  QString AndTest::getExpectedPrintedTreeFromRoot() {
        return QString(
                "LogixNG: A new logix for test\n" \
                "   ConditionalNG: A conditionalNG\n" \
                "      ! A\n" \
                "         If Then Else. Execute on change ::: Use default\n" \
                "            ? If\n" \
                "               And ::: Use default\n" \
                "                  ? E1\n" \
                "                     Socket not connected\n" \
                "            ! Then\n" \
                "               Socket not connected\n" \
                "            ! Else\n" \
                "               Socket not connected\n");
    }

    //@Override
    /*public*/  NamedBean* AndTest::createNewBean(QString systemName) {
        return new And(systemName, "");
    }

    //@Override
    /*public*/  bool AndTest::addNewSocket() /*throws SocketAlreadyConnectedException*/ {
        int count = _base->getChildCount();
        for (int i=0; i < count; i++) {
            if (!_base->getChild(i)->isConnected()) {
                _base->getChild(i)->_connect(getConnectableChild());
            }
        }
        return true;
    }

    //@Test
    /*public*/  void AndTest::testCtor() {
        And* expression2;

        expression2 = new And("IQDE321", "");
        Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
        Assert::assertNull("Username matches", expression2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "And", expression2->getLongDescription(QLocale()), __FILE__, __LINE__);

        expression2 = new And("IQDE321", "My expression");
        Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
        Assert::assertEquals("Username matches", "My expression", expression2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "And", expression2->getLongDescription(QLocale()), __FILE__, __LINE__);

        bool thrown = false;
        try {
            // Illegal system name
            new And("IQE55:12:XY11", "");
        } catch (IllegalArgumentException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);

        thrown = false;
        try {
            // Illegal system name
            new And("IQE55:12:XY11", "A name");
        } catch (IllegalArgumentException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);
    }

    // Test action when at least one child socket is not connected
    //@Test
    /*public*/  void AndTest::testCtorAndSetup1() {
        DigitalExpressionManager* m = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");

        QList<MaleSocket*> maleSockets = QList<MaleSocket*>();
        maleSockets.append(m->registerExpression(new ExpressionMemory("IQDE52", "")));
        maleSockets.append(nullptr);  // This is null by purpose
        maleSockets.append(m->registerExpression(new ExpressionMemory("IQDE554", "")));
        maleSockets.append(nullptr);  // This is null by purpose
        maleSockets.append(m->registerExpression(new ExpressionMemory("IQDE3", "")));

        QList<QMap<QString, QString>> actionSystemNames = QList<QMap<QString, QString>>();
        actionSystemNames.append(QMap<QString, QString> {{"XYZ123", "IQDE52"}});
        actionSystemNames.append(QMap<QString, QString> {{"ZH12", ""}});   // This is null by purpose
        actionSystemNames.append(QMap<QString, QString> {{"Hello", "IQDE554"}});
        // IQDE61232 doesn't exist by purpose
        actionSystemNames.append(QMap<QString, QString> {{"SomethingElse", "IQDE61232"}});
        actionSystemNames.append(QMap<QString, QString> {{"Yes123", "IQDE3"}});

        And* expression = new And("IQDE321", "", actionSystemNames);
        Assert::assertNotNull("exists", expression, __FILE__, __LINE__);
        Assert::assertEquals("expression has 5 female sockets", 5, expression->getChildCount(), __FILE__, __LINE__);

        for (int i=0; i < 5; i++) {
            QMap<QString,QString> map = actionSystemNames.at(i);
            QMapIterator<QString,QString> entry(map);
            while (entry.hasNext()) {
             entry.next();

            Assert::assertEquals("expression female socket name is "+entry.key(),
                    entry.key(), expression->getChild(i)->getName(), __FILE__, __LINE__);
            Assert::assertEquals("expression female socket is of correct class",
//                    "jmri.jmrit.logixng.implementation.DefaultFemaleGenericExpressionSocket$DigitalSocket",
                "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalExpressionSocket",
                    expression->getChild(i)->getClassName(), __FILE__, __LINE__);
            Assert::assertFalse("expression female socket is not connected",
                    expression->getChild(i)->isConnected(), __FILE__, __LINE__);

            }
        }

        // Setup action. This connects the child actions to this action
        expression->setup();

        JUnitAppender::assertMessage("cannot load digital expression IQDE61232", __FILE__, __LINE__);

        for (int i=0; i < 5; i++) {
            QMap<QString,QString> map = actionSystemNames.at(i);
            QMapIterator<QString,QString> entry(map);
            while (entry.hasNext()) {
             entry.next();
            Assert::assertEquals("expression female socket name is "+entry.key(),
                    entry.key(), expression->getChild(i)->getName(), __FILE__, __LINE__);

            if (maleSockets.at(i) != nullptr) {
                Assert::assertTrue("expression female socket is connected",
                        expression->getChild(i)->isConnected(), __FILE__, __LINE__);
//                Assert::assertEquals("child is correct bean",
//                        maleSockets.get(i),
//                        expression->getChild(i).getConnectedSocket(), __FILE__, __LINE__);
            } else {
                Assert::assertFalse("expression female socket is not connected",
                        expression->getChild(i)->isConnected(), __FILE__, __LINE__);
            }
           }
        }

        Assert::assertEquals("expression has 5 female sockets", 5, expression->getChildCount(), __FILE__, __LINE__);
    }

    // Test action when at least one child socket is not connected.
    // This should never happen, but test it anyway.
    //@Test
    /*public*/  void AndTest::testCtorAndSetup2() {
     DigitalExpressionManager* m = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");

        QList<MaleSocket*> maleSockets = QList<MaleSocket*> ();
        maleSockets.append(m->registerExpression(new ExpressionMemory("IQDE52", "")));
        maleSockets.append(m->registerExpression(new ExpressionMemory("IQDE99", "")));
        maleSockets.append(m->registerExpression(new ExpressionMemory("IQDE554", "")));
        maleSockets.append(m->registerExpression(new ExpressionMemory("IQDE61232", "")));
        maleSockets.append(m->registerExpression(new ExpressionMemory("IQDE3", "")));

        QList<QMap<QString, QString>> actionSystemNames = QList<QMap<QString, QString>>();
        actionSystemNames.append(QMap<QString, QString> {{"XYZ123", "IQDE52"}});
        actionSystemNames.append(QMap<QString, QString> {{"ZH12", "IQDE99"}});
        actionSystemNames.append(QMap<QString, QString> {{"Hello", "IQDE554"}});
        actionSystemNames.append(QMap<QString, QString> {{"SomethingElse", "IQDE61232"}});
        actionSystemNames.append(QMap<QString, QString> {{"Yes123", "IQDE3"}});

        And* expression = new And("IQDE321", "", actionSystemNames);
        Assert::assertNotNull("exists", expression, __FILE__, __LINE__);
        Assert::assertEquals("expression has 5 female sockets", 5, expression->getChildCount(), __FILE__, __LINE__);

        for (int i=0; i < 5; i++) {
            QMap<QString,QString> map = actionSystemNames.at(i);
            QMapIterator<QString,QString> entry(map);
            while (entry.hasNext()) {
             entry.next();
             Assert::assertEquals("expression female socket name is "+entry.key(),
                    entry.key(), expression->getChild(i)->getName(), __FILE__, __LINE__);
            Assert::assertEquals("expression female socket is of correct class",
//                    "jmri.jmrit.logixng.implementation.DefaultFemaleGenericExpressionSocket$DigitalSocket",
                "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalExpressionSocket",
                    expression->getChild(i)->getClassName(), __FILE__, __LINE__);
            Assert::assertFalse("expression female socket is not connected",
                    expression->getChild(i)->isConnected(), __FILE__, __LINE__);
            }
        }

        // Setup action. This connects the child actions to this action
        expression->setup();

        for (int i=0; i < 5; i++) {
            QMap<QString,QString> map = actionSystemNames.at(i);
            QMapIterator<QString,QString> entry(map);
            while (entry.hasNext()) {
             entry.next();
             Assert::assertEquals("expression female socket name is "+entry.key(),
                    entry.key(), expression->getChild(i)->getName(), __FILE__, __LINE__);

            if (maleSockets.at(i) != nullptr) {
                Assert::assertTrue("expression female socket is connected",
                        expression->getChild(i)->isConnected(), __FILE__, __LINE__);
//                Assert::assertEquals("child is correct bean",
//                        maleSockets.get(i),
//                        expression->getChild(i).getConnectedSocket(), __FILE__, __LINE__);
            } else {
                Assert::assertFalse("expression female socket is not connected",
                        expression->getChild(i)->isConnected(), __FILE__, __LINE__);
            }
           }
        }

        // Since all the sockets are connected, a new socket must have been created.
        Assert::assertEquals("expression has 6 female sockets", 6, expression->getChildCount(), __FILE__, __LINE__);

        // Try run setup() again. That should not cause any problems.
        expression->setup();

        Assert::assertEquals("expression has 6 female sockets", 6, expression->getChildCount(), __FILE__, __LINE__);
    }

    // Test calling setActionSystemNames() twice
    //@Test
    /*public*/  void AndTest::testCtorAndSetup3() /*throws NoSuchMethodException, IllegalAccessException, IllegalArgumentException */{
        QList<QMap<QString, QString>> actionSystemNames = QList<QMap<QString, QString>>();
        actionSystemNames.append(QMap<QString, QString> {{"XYZ123", "IQDE52"}});

        And* expression = new And("IQDE321", "", actionSystemNames);
#if 0
        java.lang.reflect.Method method =
                expression->getClass().getDeclaredMethod("setExpressionSystemNames", new Class<?>[]{List.class});
        method.setAccessible(true);

        bool hasThrown = false;
        try {
            method.invoke(expression, new Object[]{null});
        } catch (InvocationTargetException* e) {
            if (e.getCause() instanceof RuntimeException) {
                hasThrown = true;
                Assert::assertEquals("Exception message is correct",
                        "expression system names cannot be set more than once",
                        e.getCause().getMessage());
            }
        }
        Assert::assertTrue("Exception thrown", hasThrown, __FILE__, __LINE__);
#endif
    }

    //@Test
    /*public*/  void AndTest::testGetChild() /*throws SocketAlreadyConnectedException */{
        And* expression2 = new And("IQDE321", "");

        for (int i=0; i < 3; i++) {
            Assert::assertTrue("getChildCount() returns "+i, i+1 == expression2->getChildCount(), __FILE__, __LINE__);

            Assert::assertNotNull("getChild(0) returns a non null value",
                    (QObject*)expression2->getChild(0), __FILE__, __LINE__);
#if 0 // TODO:
            assertIndexOutOfBoundsException(expression2::getChild, i+1, i+1);
#endif
            // Connect a new child expression
            True* expr = new True("IQDE"+QString::number(i), "");
            MaleSocket* maleSocket =
                    ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expr);
            expression2->getChild(i)->_connect(maleSocket);
        }
    }

    //@Test
    /*public*/  void AndTest::testCategory() {
        Assert::assertTrue("Category matches", Category::COMMON == _base->getCategory(), __FILE__, __LINE__);
    }

    // Test the methods connected(FemaleSocket) and getExpressionSystemName(int)
    //@Test
    /*public*/  void AndTest::testConnected_getExpressionSystemName() /*throws SocketAlreadyConnectedException*/ {
        And* expression = new And("IQDE121", "");

        ExpressionMemory* stringExpressionMemory = new ExpressionMemory("IQDE122", "");
        MaleSocket* maleSAMSocket =
                ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(stringExpressionMemory);

        Assert::assertEquals("Num children is correct", 1, expression->getChildCount(), __FILE__, __LINE__);

        // Test connect and disconnect
        expression->getChild(0)->_connect(maleSAMSocket);
        Assert::assertEquals("Num children is correct", 2, expression->getChildCount(), __FILE__, __LINE__);
        Assert::assertEquals("getExpressionSystemName(0) is correct", "IQDE122", expression->getExpressionSystemName(0), __FILE__, __LINE__);
        Assert::assertNull("getExpressionSystemName(1) is null", expression->getExpressionSystemName(1), __FILE__, __LINE__);
        expression->getChild(0)->_disconnect();
        Assert::assertEquals("Num children is correct", 2, expression->getChildCount(), __FILE__, __LINE__);
        Assert::assertNull("getExpressionSystemName(0) is null", expression->getExpressionSystemName(0), __FILE__, __LINE__);
        Assert::assertNull("getExpressionSystemName(1) is null", expression->getExpressionSystemName(1), __FILE__, __LINE__);

        expression->getChild(1)->_connect(maleSAMSocket);
        Assert::assertEquals("Num children is correct", 2, expression->getChildCount(), __FILE__, __LINE__);
        Assert::assertNull("getExpressionSystemName(0) is null", expression->getExpressionSystemName(0), __FILE__, __LINE__);
        Assert::assertEquals("getExpressionSystemName(1) is correct", "IQDE122", expression->getExpressionSystemName(1), __FILE__, __LINE__);
        expression->getChild(0)->_disconnect();    // Test removing child with the wrong index.
        Assert::assertEquals("Num children is correct", 2, expression->getChildCount(), __FILE__, __LINE__);
        Assert::assertNull("getExpressionSystemName(0) is null", expression->getExpressionSystemName(0), __FILE__, __LINE__);
        Assert::assertEquals("getExpressionSystemName(1) is correct", "IQDE122", expression->getExpressionSystemName(1), __FILE__, __LINE__);
        expression->getChild(1)->_disconnect();
        Assert::assertEquals("Num children is correct", 2, expression->getChildCount(), __FILE__, __LINE__);
        Assert::assertNull("getExpressionSystemName(0) is null", expression->getExpressionSystemName(0), __FILE__, __LINE__);
        Assert::assertNull("getExpressionSystemName(1) is null", expression->getExpressionSystemName(1), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AndTest::testDescription() {
        And* e1 = new And("IQDE321", "");
        Assert::assertEquals("And", (e1->getShortDescription(QLocale())), __FILE__, __LINE__);
        Assert::assertEquals("And", (e1->getLongDescription(QLocale())), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void AndTest::setUp() /*throws SocketAlreadyConnectedException*/ {
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

        DigitalExpressionBean* expression = new And("IQDE321", "");
        MaleSocket* maleSocket2 =
                ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
        ifThenElse->getChild(0)->_connect(maleSocket2);

        _base = expression;
        _baseMaleSocket = maleSocket2;

        if (! logixNG->setParentForAllChildren(new QList<QString>())) throw new RuntimeException();
        logixNG->setEnabled(true);
    }

    //@After
    /*public*/  void AndTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }

