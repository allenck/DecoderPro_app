#include "antecedenttest.h"
#include "logixng_thread.h"
#include "instancemanager.h"
#include "junitutil.h"
#include "assert1.h"
#include "true.h"
#include "defaultdigitalexpressionmanager.h"
#include "antecedent.h"
#include "defaultlogixngmanager.h"
#include "defaultconditionalngscaffold.h"
#include "defaultconditionalngmanager.h"
#include "ifthenelse.h"
#include "defaultdigitalactionmanager.h"
#include "actionatomicboolean.h"
#include "junitappender.h"
#include "expressionmemory.h"
#include "false.h"


AntecedentTest::AntecedentTest(QObject *parent) : AbstractDigitalExpressionTestBase(parent)
{
 setObjectName("AntecedentTest");
}

/**
 * Test Antecedent
 *
 * @author Daniel Bergqvist 2018
 */
//*public*/  class AntecedentTest extends AbstractDigitalExpressionTestBase implements FemaleSocketListener {

    /*private*/ /*static*/ /*final*/ bool AntecedentTest::EXPECT_SUCCESS = true;
    /*private*/ /*static*/ /*final*/ bool AntecedentTest::EXPECT_FAILURE = false;


    //@Override
    /*public*/  ConditionalNG* AntecedentTest::getConditionalNG() {
        return conditionalNG;
    }

    //@Override
    /*public*/  LogixNG* AntecedentTest::getLogixNG() {
        return logixNG;
    }

    /*private*/ /*static*/ int AntecedentTest::beanID = 901;

    //@Override
    /*public*/  MaleSocket* AntecedentTest::getConnectableChild() {
        DigitalExpressionBean* childExpression = new True("IQDE"+QString::number(beanID++), "");
        MaleSocket* maleSocketChild = ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(childExpression);
        return maleSocketChild;
    }

    //@Override
    /*public*/  QString AntecedentTest::getExpectedPrintedTree() {
        return QString(
                "Antecedent: R1 ::: Use default\n" \
                "   ? E1\n" \
                "      Always true ::: Use default\n" \
                "   ? E2\n" \
                "      Socket not connected\n");
    }

    //@Override
    /*public*/  QString AntecedentTest::getExpectedPrintedTreeFromRoot() {
        return QString(
                "LogixNG: A new logix for test\n" \
                "   ConditionalNG: A conditionalNG\n" \
                "      ! A\n" \
                "         If Then Else. Execute on change ::: Use default\n" \
                "            ? If\n" \
                "               Antecedent: R1 ::: Use default\n" \
                "                  ? E1\n" \
                "                     Always true ::: Use default\n" \
                "                  ? E2\n" \
                "                     Socket not connected\n" \
                "            ! Then\n" \
                "               Set the atomic boolean to true ::: Use default\n" \
                "            ! Else\n" \
                "               Socket not connected\n");
    }

    //@Override
    /*public*/  NamedBean* AntecedentTest::createNewBean(QString systemName) /*throws Exception*/ {
        Antecedent* a = new Antecedent(systemName, "");
        a->setAntecedent("R1");
        return a;
    }

    //@Override
    /*public*/  bool AntecedentTest::addNewSocket() /*throws SocketAlreadyConnectedException*/ {
        int count = _base->getChildCount();
        for (int i=0; i < count; i++) {
            if (!_base->getChild(i)->isConnected()) {
                _base->getChild(i)->_connect(getConnectableChild());
            }
        }
        return true;
    }
#if 1
    //@Test
    /*public*/  void AntecedentTest::testCtor() /*throws Exception*/ {
        Antecedent* expression2;

        expression2 = new Antecedent("IQDE321", "");
        expression2->setAntecedent("R1");
        Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
        Assert::assertNull("Username matches", expression2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Antecedent: R1", expression2->getLongDescription(QLocale()), __FILE__, __LINE__);

        expression2 = new Antecedent("IQDE321", "My expression");
        expression2->setAntecedent("R1");
        Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
        Assert::assertEquals("Username matches", "My expression", expression2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Antecedent: R1", expression2->getLongDescription(QLocale()), __FILE__, __LINE__);

        expression2 = new Antecedent("IQDE321", "");
        expression2->setAntecedent("R1 and R2");
        Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
        Assert::assertNull("Username matches", expression2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Antecedent: R1 and R2", expression2->getLongDescription(QLocale()), __FILE__, __LINE__);

        expression2 = new Antecedent("IQDE321", "My expression");
        expression2->setAntecedent("R1 or R2");
        Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
        Assert::assertEquals("Username matches", "My expression", expression2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Antecedent: R1 or R2", expression2->getLongDescription(QLocale()), __FILE__, __LINE__);

        bool thrown = false;
        try {
            // Illegal system name
            new Antecedent("IQE55:12:XY11", "");
        } catch (IllegalArgumentException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);

        thrown = false;
        try {
            // Illegal system name
            new Antecedent("IQE55:12:XY11", "A name");
        } catch (IllegalArgumentException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);
    }

    // Test action when at least one child socket is not connected
    //@Test
    /*public*/  void AntecedentTest::testCtorAndSetup1() {
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

        Antecedent* expression = new Antecedent("IQDE321", "", actionSystemNames);
        Assert::assertNotNull("exists", expression, __FILE__, __LINE__);
        Assert::assertEquals("expression has 5 female sockets", 5, expression->getChildCount(), __FILE__, __LINE__);

        for (int i=0; i < 5; i++) {
            QMap<QString,QString> map = actionSystemNames.at(i);
            QMapIterator<QString,QString> entry(map);
            while(entry.hasNext())
            {
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
         while(entry.hasNext())
         {
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
    /*public*/  void AntecedentTest::testCtorAndSetup2() {
        DigitalExpressionManager* m = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");

        QList<MaleSocket*> maleSockets = QList<MaleSocket*>();
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

        Antecedent* expression = new Antecedent("IQDE321", "", actionSystemNames);
        Assert::assertNotNull("exists", expression, __FILE__, __LINE__);
        Assert::assertEquals("expression has 5 female sockets", 5, expression->getChildCount(), __FILE__, __LINE__);

        for (int i=0; i < 5; i++) {
         QMap<QString,QString> map = actionSystemNames.at(i);
         QMapIterator<QString,QString> entry(map);
         while(entry.hasNext())
         {
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
         while(entry.hasNext())
         {
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
    /*public*/  void AntecedentTest::testCtorAndSetup3() /*throws NoSuchMethodException, IllegalAccessException, IllegalArgumentException */{
        QList<QMap<QString, QString>> actionSystemNames = QList<QMap<QString, QString>>();
        actionSystemNames.append(QMap<QString, QString> {{"XYZ123", "IQDE52"}});

        Antecedent* expression = new Antecedent("IQDE321", "", actionSystemNames);
#if 0
        Method method =
                expression->getClass().getDeclaredMethod("setExpressionSystemNames", new Class<?>[]{List.class});
        method.setAccessible(true);

        bool hasThrown = false;
        try {
            method.invoke(expression, new Object[]{null});
        } catch (InvocationTargetException* e) {
            if (e->getCause() instanceof RuntimeException) {
                hasThrown = true;
                Assert::assertEquals("Exception message is correct",
                        "expression system names cannot be set more than once",
                        e.getCause().getMessage(), __FILE__, __LINE__);
            }
        }
        Assert::assertTrue("Exception thrown", hasThrown, __FILE__, __LINE__);
#endif
    }

    //@Test
    /*public*/  void AntecedentTest::testSetChildCount() /*throws SocketAlreadyConnectedException*/ {
//        _baseMaleSocket.setEnabled(false);

        Antecedent* a = (Antecedent*)_base->bself();
        AtomicBoolean* ab = new AtomicBoolean(false);

//        _base->addPropertyChangeListener((PropertyChangeEvent evt) -> {
//            ab.set(true);
//        });
        ((AbstractBase* )_base->bself())->AbstractNamedBean::addPropertyChangeListener(new AntecedentTest_PropertyChangeListener(ab));

        a->setChildCount(1);
        Assert::assertEquals("numChilds are correct", 1, a->getChildCount(), __FILE__, __LINE__);

        // Test increase num children
        ab->set(false);
        a->setChildCount(a->getChildCount()+1);
        Assert::assertEquals("numChilds are correct", 2, a->getChildCount(), __FILE__, __LINE__);
        Assert::assertTrue("PropertyChangeEvent fired", ab->get(), __FILE__, __LINE__);

        // Test decrease num children
        ab->set(false);
        Assert::assertTrue("We have least two children", a->getChildCount() > 1, __FILE__, __LINE__);
        a->setChildCount(1);
        Assert::assertEquals("numChilds are correct", 1, a->getChildCount(), __FILE__, __LINE__);
        Assert::assertTrue("PropertyChangeEvent fired", ab->get(), __FILE__, __LINE__);

        // Test decrease num children when all children are connected
        ab->set(false);
        a->getChild(0)->_disconnect();
        a->getChild(0)->_connect(getConnectableChild());
        a->getChild(1)->_disconnect();
        a->getChild(1)->_connect(getConnectableChild());
        a->getChild(2)->_disconnect();
        a->getChild(2)->_connect(getConnectableChild());
        Assert::assertEquals("numChilds are correct", 4, a->getChildCount(), __FILE__, __LINE__);
        a->setChildCount(2);
        Assert::assertEquals("numChilds are correct", 2, a->getChildCount(), __FILE__, __LINE__);
        Assert::assertTrue("PropertyChangeEvent fired", ab->get(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AntecedentTest::testGetChild() /*throws Exception*/ {
        Antecedent* expression2 = new Antecedent("IQDE321", "");
        expression2->setAntecedent("R1");

        for (int i=0; i < 3; i++) {
            Assert::assertTrue("getChildCount() returns "+QString::number(i), i+1 == expression2->getChildCount(), __FILE__, __LINE__);

            Assert::assertNotNull("getChild(0) returns a non null value",
                    (QObject*)expression2->getChild(0), __FILE__, __LINE__);
#if 0
            assertIndexOutOfBoundsException(expression2::getChild, i+1, i+1);
#endif

            // Connect a new child expression
            True* expr = new True("IQDE"+QString::number(i), "");
            MaleSocket* maleSocket = ((DefaultDigitalExpressionManager*)
                    InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expr);
            expression2->getChild(i)->_connect(maleSocket);
        }
    }

    //@Test
    /*public*/  void AntecedentTest::testCategory() {
        Assert::assertTrue("Category matches", Category::COMMON == _base->getCategory(), __FILE__, __LINE__);
    }

    // Test the methods connected(FemaleSocket) and getExpressionSystemName(int)
    //@Test
    /*public*/  void AntecedentTest::testConnected_getExpressionSystemName() /*throws SocketAlreadyConnectedException */{
        Antecedent* expression = new Antecedent("IQDE121", "");

        ExpressionMemory* stringExpressionMemory = new ExpressionMemory("IQDE122", "");
        MaleSocket* maleSAMSocket =((DefaultDigitalExpressionManager*)
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
    /*public*/  void AntecedentTest::testDescription() {
        Antecedent* e1 = new Antecedent("IQDE321", "");
        Assert::assertEquals("strings matches", "Antecedent", e1->getShortDescription(QLocale()), __FILE__, __LINE__);
        Assert::assertEquals("strings matches", "Antecedent: empty", e1->getLongDescription(QLocale()), __FILE__, __LINE__);
    }

    /*private*/ void AntecedentTest::testValidate(bool expectedResult, QString antecedent, QList<DigitalExpressionBean*> conditionalVariablesList) /*throws Exception */{
        Antecedent* ix1 = new Antecedent("IQDE321", "IXIC 1");
        ix1->setAntecedent("R1");

        int count = 0;
        QList<Antecedent::ExpressionEntry*> expressionEntryList =QList<Antecedent::ExpressionEntry*>();
        for (DigitalExpressionBean* expressionAntecedent : conditionalVariablesList) {
            QString socketName = "E"+QString::number(count++);
            FemaleDigitalExpressionSocket* socket = ((DefaultDigitalExpressionManager*)
                    InstanceManager::getDefault("DigitalExpressionManager"))
                            ->createFemaleSocket(conditionalNG, this, socketName);
            socket->_connect((MaleSocket*) expressionAntecedent);
            expressionEntryList.append(new Antecedent::ExpressionEntry(socket, socketName));
        }

        if (expectedResult) {
            Assert::assertTrue("validateAntecedent() returns null for '"+antecedent+"'",
                    ix1->validateAntecedent(antecedent, expressionEntryList) == nullptr, __FILE__, __LINE__);
        } else {
            Assert::assertTrue("validateAntecedent() returns error message for '"+antecedent+"'",
                    ix1->validateAntecedent(antecedent, expressionEntryList) != nullptr, __FILE__, __LINE__);
        }
    }

    /*private*/ void AntecedentTest::testCalculate(int expectedResult, QString antecedent,
            QList<DigitalExpressionBean*> conditionalVariablesList, QString errorMessage)
            /*throws Exception*/ {

        Antecedent* ix1 = new Antecedent("IQDE321", "IXIC 1");
        ix1->setParent(conditionalNG);
        ix1->setAntecedent(antecedent);

//        for (int i=0; i < ix1.getChildCount(); i++) {
//            ix1.getChild(i)->_disconnect();
//        }

        ix1->setChildCount(conditionalVariablesList.size());

        for (int i=0; i < conditionalVariablesList.size(); i++) {
            ix1->getChild(i)->_connect((MaleSocket*)conditionalVariablesList.at(i));
        }

        switch (expectedResult) {
            case Antecedent::FALSE:
                Assert::assertFalse("validateAntecedent() returns FALSE for '"+antecedent+"'",
                        ix1->evaluate(), __FILE__, __LINE__);
                break;

            case Antecedent::TRUE:
//                System.err.format("antecedent: %s%n", antecedent);
//                System.err.format("variable: %b%n", conditionalVariablesList.get(0).evaluate(isCompleted));
                Assert::assertTrue("validateAntecedent() returns TRUE for '"+antecedent+"'",
                        ix1->evaluate(), __FILE__, __LINE__);
                break;

            default:
                throw new RuntimeException(QString("Unknown expected result: %1").arg(expectedResult));
        }

        if (! errorMessage.isEmpty()) {
            JUnitAppender::assertErrorMessageStartsWith(errorMessage, __FILE__, __LINE__);
        }
    }

    //@Test
    /*public*/  void AntecedentTest::testValidate() /*throws Exception*/ {
        QList<DigitalExpressionBean*> conditionalVariables_Empty = { };
        QList<DigitalExpressionBean*> conditionalVariablesList_Empty = QList<DigitalExpressionBean*>(conditionalVariables_Empty);

        DigitalExpressionBean* trueExpression = ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault(
                        "DigitalExpressionManager"))->registerExpression(
                                new True(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->getAutoSystemName(), ""));
//        DigitalExpressionBean falseExpression = InstanceManager::getDefault(DigitalExpressionManager.class).registerExpression(new False(conditionalNG));

        QList<DigitalExpressionBean*> conditionalVariables_True
                = { trueExpression };
        QList<DigitalExpressionBean*> conditionalVariablesList_True = QList<DigitalExpressionBean*>(conditionalVariables_True);

        QList<DigitalExpressionBean*> conditionalVariables_TrueTrueTrue
                = { trueExpression
                        , trueExpression
                        , trueExpression };
        QList<DigitalExpressionBean*> conditionalVariablesList_TrueTrueTrue = QList<DigitalExpressionBean*>(conditionalVariables_TrueTrueTrue);

        // Test empty antecedent string
        testValidate(EXPECT_FAILURE, "", conditionalVariablesList_Empty);

        testValidate(EXPECT_SUCCESS, "R1", conditionalVariablesList_True);
        testValidate(EXPECT_FAILURE, "R2", conditionalVariablesList_True);

        // Test parentheses
        testValidate(EXPECT_SUCCESS, "([{R1)}]", conditionalVariablesList_True);
        testValidate(EXPECT_FAILURE, "(R2", conditionalVariablesList_True);
        testValidate(EXPECT_FAILURE, "R2)", conditionalVariablesList_True);

        // Test several items
        testValidate(EXPECT_FAILURE, "R1 and R2 and R3", conditionalVariablesList_True);
        testValidate(EXPECT_FAILURE, "R1", conditionalVariablesList_TrueTrueTrue);
        testValidate(EXPECT_SUCCESS, "R1 and R2 and R3", conditionalVariablesList_TrueTrueTrue);

        // Test uppercase and lowercase
        testValidate(EXPECT_SUCCESS, "R2 AND R1 or R3", conditionalVariablesList_TrueTrueTrue);

        // Test several items and parenthese
        testValidate(EXPECT_SUCCESS, "(R1 and R3) and not R2", conditionalVariablesList_TrueTrueTrue);
        testValidate(EXPECT_FAILURE, "(R1 and) R3 and not R2", conditionalVariablesList_TrueTrueTrue);
        testValidate(EXPECT_FAILURE, "R1( and R3) and not R2", conditionalVariablesList_TrueTrueTrue);
        testValidate(EXPECT_FAILURE, "R1 (and R3 and) not R2", conditionalVariablesList_TrueTrueTrue);
        testValidate(EXPECT_FAILURE, "(R1 and R3) and not R2)", conditionalVariablesList_TrueTrueTrue);
        testValidate(EXPECT_SUCCESS, "(R1 and (R3) and not R2)", conditionalVariablesList_TrueTrueTrue);

        // Test invalid combinations
        testValidate(EXPECT_FAILURE, "R1 and or R3 and R2", conditionalVariablesList_TrueTrueTrue);
        testValidate(EXPECT_FAILURE, "R1 or or R3 and R2", conditionalVariablesList_TrueTrueTrue);
        testValidate(EXPECT_FAILURE, "R1 or and R3 and R2", conditionalVariablesList_TrueTrueTrue);
        testValidate(EXPECT_FAILURE, "R1 not R3 and R2", conditionalVariablesList_TrueTrueTrue);
        testValidate(EXPECT_FAILURE, "and R1 not R3 and R2", conditionalVariablesList_TrueTrueTrue);
        testValidate(EXPECT_FAILURE, "R1 or R3 and R2 or", conditionalVariablesList_TrueTrueTrue);
    }

    //@Test
    //@SuppressWarnings("unused") // test building in progress
    /*public*/  void AntecedentTest::testCalculate() /*throws Exception*/ {
        QList<DigitalExpressionBean*> conditionalVariables_Empty = { };
        QList<DigitalExpressionBean*> conditionalVariablesList_Empty = QList<DigitalExpressionBean*>(conditionalVariables_Empty);

        DigitalExpressionBean* trueExpression = ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault(
                        "DigitalExpressionManager"))->registerExpression(
                                new True(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->getAutoSystemName(), ""));
        DigitalExpressionBean* falseExpression = ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault(
                        "DigitalExpressionManager"))->registerExpression(
                                new False(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->getAutoSystemName(), ""));

        QList<DigitalExpressionBean*> conditionalVariables_True
                = { trueExpression };
        QList<DigitalExpressionBean*> conditionalVariablesList_True = QList<DigitalExpressionBean*>(conditionalVariables_True);

        QList<DigitalExpressionBean*> conditionalVariables_False
                = { falseExpression };
        QList<DigitalExpressionBean*> conditionalVariablesList_False = QList<DigitalExpressionBean*>(conditionalVariables_False);

        QList<DigitalExpressionBean*> conditionalVariables_TrueTrueTrue
                = { trueExpression
                        , trueExpression
                        , trueExpression };
        QList<DigitalExpressionBean*> conditionalVariablesList_TrueTrueTrue = QList<DigitalExpressionBean*>(conditionalVariables_TrueTrueTrue);

        // Test with two digit variable numbers
        QList<DigitalExpressionBean*> conditionalVariables_TrueTrueFalseTrueTrueFalseTrueTrueFalseTrueTrueFalse
                = {trueExpression
                        , trueExpression
                        , falseExpression
                        , trueExpression
                        , trueExpression
                        , falseExpression
                        , trueExpression
                        , trueExpression
                        , falseExpression
                        , trueExpression
                        , trueExpression
                        , falseExpression };
        QList<DigitalExpressionBean*> conditionalVariablesList_TrueTrueFalseTrueTrueFalseTrueTrueFalseTrueTrueFalse =
                QList<DigitalExpressionBean*>(conditionalVariables_TrueTrueFalseTrueTrueFalseTrueTrueFalseTrueTrueFalse);


        // Test empty antecedent string
        testCalculate(Antecedent::FALSE, "", conditionalVariablesList_Empty, "");
//        testCalculate(Antecedent::FALSE, "", conditionalVariablesList_True,
//                "IXIC 1 parseCalculation error antecedent= , ex= java.lang.StringIndexOutOfBoundsException");
        testCalculate(Antecedent::FALSE, "", conditionalVariablesList_True, "");

        // Test illegal number
        testCalculate(Antecedent::FALSE, "R#", conditionalVariablesList_True,
                "IXIC 1 parseCalculation error antecedent= R#, ex= java.lang.NumberFormatException");
        testCalculate(Antecedent::FALSE, "R-", conditionalVariablesList_True,
                "IXIC 1 parseCalculation error antecedent= R-, ex= java.lang.NumberFormatException");
        testCalculate(Antecedent::FALSE, "Ra", conditionalVariablesList_True,
                "IXIC 1 parseCalculation error antecedent= Ra, ex= java.lang.NumberFormatException");

        // Test single condition
        testCalculate(Antecedent::TRUE, "R1", conditionalVariablesList_True, "");
        testCalculate(Antecedent::FALSE, "R1", conditionalVariablesList_False, "");
        testCalculate(Antecedent::FALSE, "not R1", conditionalVariablesList_True, "");
        testCalculate(Antecedent::TRUE, "not R1", conditionalVariablesList_False, "");

        // Test single item but wrong item (R2 instead of R1)
//        testCalculate(Antecedent::FALSE, "R2)", conditionalVariablesList_True,
//                "IXIC 1 parseCalculation error antecedent= R2), ex= java.lang.ArrayIndexOutOfBoundsException");

        // Test two digit variable numbers
        testCalculate(Antecedent::TRUE, "R3 and R12 or R5 and R10",
                conditionalVariablesList_TrueTrueFalseTrueTrueFalseTrueTrueFalseTrueTrueFalse, "");
        testCalculate(Antecedent::FALSE, "R3 and (R12 or R5) and R10",
                conditionalVariablesList_TrueTrueFalseTrueTrueFalseTrueTrueFalseTrueTrueFalse, "");
        testCalculate(Antecedent::FALSE, "R12 and R10",
                conditionalVariablesList_TrueTrueFalseTrueTrueFalseTrueTrueFalseTrueTrueFalse, "");
        testCalculate(Antecedent::TRUE, "R12 or R10",
                conditionalVariablesList_TrueTrueFalseTrueTrueFalseTrueTrueFalseTrueTrueFalse, "");
        testCalculate(Antecedent::FALSE, "not (R12 or R10)",
                conditionalVariablesList_TrueTrueFalseTrueTrueFalseTrueTrueFalseTrueTrueFalse, "");

        // Test parentheses
        testCalculate(Antecedent::TRUE, "([{R1)}]", conditionalVariablesList_True, "");
//        testCalculate(Antecedent::FALSE, "(R2", conditionalVariablesList_True,
//                "IXIC 1 parseCalculation error antecedent= (R2, ex= java.lang.ArrayIndexOutOfBoundsException");

        // Test several items
        testCalculate(Antecedent::FALSE, "R1 and R2 and R3", conditionalVariablesList_True,
                "IXIC 1 parseCalculation error antecedent= R1 and R2 and R3, ex= java.lang.IndexOutOfBoundsException");
        testCalculate(Antecedent::TRUE, "R1", conditionalVariablesList_TrueTrueTrue, "");
        testCalculate(Antecedent::TRUE, "R2", conditionalVariablesList_TrueTrueTrue, "");
        testCalculate(Antecedent::TRUE, "R3", conditionalVariablesList_TrueTrueTrue, "");
        testCalculate(Antecedent::TRUE, "R1 and R2 and R3", conditionalVariablesList_TrueTrueTrue, "");
        testCalculate(Antecedent::TRUE, "R2 AND R1 or R3", conditionalVariablesList_TrueTrueTrue, "");

        // Test invalid combinations of and, or, not
        testCalculate(Antecedent::FALSE, "R1 and or R3 and R2", conditionalVariablesList_TrueTrueTrue,
                "IXIC 1 parseCalculation error antecedent= R1 and or R3 and R2, ex= jmri.JmriException: Unexpected operator or characters < ORR3ANDR2 >");
        testCalculate(Antecedent::FALSE, "R1 or or R3 and R2", conditionalVariablesList_TrueTrueTrue,
                "IXIC 1 parseCalculation error antecedent= R1 or or R3 and R2, ex= jmri.JmriException: Unexpected operator or characters < ORR3ANDR2 >");
        testCalculate(Antecedent::FALSE, "R1 or and R3 and R2", conditionalVariablesList_TrueTrueTrue,
                "IXIC 1 parseCalculation error antecedent= R1 or and R3 and R2, ex= jmri.JmriException: Unexpected operator or characters < ANDR3ANDR2 >");
        testCalculate(Antecedent::FALSE, "R1 not R3 and R2", conditionalVariablesList_TrueTrueTrue,
                "IXIC 1 parseCalculation error antecedent= R1 not R3 and R2, ex= jmri.JmriException: Could not find expected operator < NOTR3ANDR2 >");
        testCalculate(Antecedent::FALSE, "and R1 not R3 and R2", conditionalVariablesList_TrueTrueTrue,
                "IXIC 1 parseCalculation error antecedent= and R1 not R3 and R2, ex= jmri.JmriException: Unexpected operator or characters < ANDR1NOTR3ANDR2 >");
        testCalculate(Antecedent::FALSE, "R1 or R3 and R2 or", conditionalVariablesList_TrueTrueTrue,
                "IXIC 1 parseCalculation error antecedent= R1 or R3 and R2 or, ex= java.lang.StringIndexOutOfBoundsException");

        // Test several items and parenthese
        testCalculate(Antecedent::TRUE, "(R1 and R3) and R2", conditionalVariablesList_TrueTrueTrue, "");
        testCalculate(Antecedent::FALSE, "(R1 and R3) and not R2", conditionalVariablesList_TrueTrueTrue, "");
        testCalculate(Antecedent::FALSE, "(R1 and) R3 and not R2", conditionalVariablesList_TrueTrueTrue,
                "IXIC 1 parseCalculation error antecedent= (R1 and) R3 and not R2, ex= jmri.JmriException: Unexpected operator or characters < )R3ANDNOTR2 >");
        testCalculate(Antecedent::FALSE, "R1( and R3) and not R2", conditionalVariablesList_TrueTrueTrue,
                "IXIC 1 parseCalculation error antecedent= R1( and R3) and not R2, ex= jmri.JmriException: Could not find expected operator < (ANDR3)ANDNOTR2 >");
        testCalculate(Antecedent::FALSE, "R1 (and R3 and) not R2", conditionalVariablesList_TrueTrueTrue,
                "IXIC 1 parseCalculation error antecedent= R1 (and R3 and) not R2, ex= jmri.JmriException: Could not find expected operator < (ANDR3AND)NOTR2 >");
        testCalculate(Antecedent::FALSE, "(R1 and R3) and not R2)", conditionalVariablesList_TrueTrueTrue, "");
        testCalculate(Antecedent::TRUE, "(R1 and (R3) and R2)", conditionalVariablesList_TrueTrueTrue, "");
        testCalculate(Antecedent::FALSE, "(R1 and (R3) and not R2)", conditionalVariablesList_TrueTrueTrue, "");
    }
#endif

    // The minimal setup for log4J
    //@Before
    /*public*/  void AntecedentTest::setUp() /*throws Exception*/ {
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
        ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->Register((AbstractNamedBean*)conditionalNG->self());
        conditionalNG->setRunDelayed(false);
        conditionalNG->setEnabled(true);
        logixNG->addConditionalNG((DefaultConditionalNG*)conditionalNG);
        IfThenElse* ifThenElse = new IfThenElse("IQDA321", "");
        MaleSocket* maleSocket = ((DefaultDigitalActionManager*)
                InstanceManager::getDefault("DigitalActionManager"))->registerAction(ifThenElse);
        conditionalNG->getChild(0)->_connect(maleSocket);

        expressionAntecedent = new Antecedent("IQDE321", "");
        expressionAntecedent->setAntecedent("R1");
        MaleSocket* maleSocket2 = ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expressionAntecedent);
        ifThenElse->getChild(0)->_connect(maleSocket2);

        DigitalExpressionBean* childExpression = new True("IQDE322", "");
        MaleSocket* maleSocketChild = ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(childExpression);
        maleSocket2->getChild(0)->_connect(maleSocketChild);

        _base = expressionAntecedent;
        _baseMaleSocket = maleSocket2;

        atomicBoolean = new AtomicBoolean(false);
        actionAtomicBoolean = new ActionAtomicBoolean(atomicBoolean, true);
        MaleSocket* socketAtomicBoolean = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(actionAtomicBoolean);
        ifThenElse->getChild(1)->_connect(socketAtomicBoolean);

        if (! logixNG->setParentForAllChildren(new QStringList())) throw new RuntimeException();
        logixNG->setEnabled(true);
    }

    //@After
    /*public*/  void AntecedentTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }

    //@Override
    /*public*/  void AntecedentTest::connected(FemaleSocket* socket) {
        // Do nothing
    }

    //@Override
    /*public*/  void AntecedentTest::disconnected(FemaleSocket* socket) {
        // Do nothing
    }

