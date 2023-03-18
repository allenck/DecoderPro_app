#include "analogformulatest.h"
#include "logixng_thread.h"
#include "junitutil.h"
#include "instancemanager.h"
#include "assert1.h"
#include "analogexpressionconstant.h"
#include "defaultanalogexpressionmanager.h"
#include "analogformula.h"
#include "defaultanalogexpressionmanager.h"
#include "analogexpressionmemory.h"
#include "junitappender.h"
#include "defaultlogixngmanager.h"
#include "defaultconditionalngscaffold.h"
#include "defaultconditionalngmanager.h"
#include "doanalogaction.h"
#include "defaultdigitalactionmanager.h"
#include "defaultmemorymanager.h"
#include "analogactionmemory.h"
#include "defaultanalogactionmanager.h"

/**
 * Test And
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  class AnalogFormulaTest extends AbstractAnalogExpressionTestBase {



    //@Override
    /*public*/  ConditionalNG* AnalogFormulaTest::getConditionalNG() {
        return conditionalNG;
    }

    //@Override
    /*public*/  LogixNG* AnalogFormulaTest::getLogixNG() {
        return logixNG;
    }

    /*private*/ /*static*/ int AnalogFormulaTest::beanID = 901;

    //@Override
    /*public*/  MaleSocket* AnalogFormulaTest::getConnectableChild() {
        AnalogExpressionBean* childExpression = new AnalogExpressionConstant("IQAE"+QString::number(beanID++), "");
        MaleSocket* maleSocketChild = ((DefaultAnalogExpressionManager*)
                InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(childExpression);
        return maleSocketChild;
    }

    //@Override
    /*public*/  QString AnalogFormulaTest::getExpectedPrintedTree() {
        return QString(
                "Analog Formula: E1 ::: Use default\n" \
                "   ?* E1\n" \
                "      Get analog constant 1 ::: Use default\n" \
                "   ?* E2\n" \
                "      Socket not connected\n");
    }

    //@Override
    /*public*/  QString AnalogFormulaTest::getExpectedPrintedTreeFromRoot() {
        return QString(
                "LogixNG: A new logix for test\n" \
                "   ConditionalNG: A conditionalNG\n" \
                "      ! A\n" \
                "         Read analog E and set analog A ::: Use default\n" \
                "            ?~ E\n" \
                "               Analog Formula: E1 ::: Use default\n" \
                "                  ?* E1\n" \
                "                     Get analog constant 1 ::: Use default\n" \
                "                  ?* E2\n" \
                "                     Socket not connected\n" \
                "            !~ A\n" \
                "               Set memory IM2 ::: Use default%n");
    }

    //@Override
    /*public*/  NamedBean* AnalogFormulaTest::createNewBean(QString systemName) /*throws Exception*/ {
        AnalogFormula* a = new AnalogFormula(systemName, "");
//        a->setFormula("R1");
        return a;
    }

    //@Override
    /*public*/  bool AnalogFormulaTest::addNewSocket() /*throws SocketAlreadyConnectedException */{
        int count = _base->getChildCount();
        for (int i=0; i < count; i++) {
            if (!_base->getChild(i)->isConnected()) {
                _base->getChild(i)->_connect(getConnectableChild());
            }
        }
        return true;
    }

    //@Test
    /*public*/  void AnalogFormulaTest::testCtor() /*throws Exception*/ {
        AnalogFormula* expression2;

        expression2 = new AnalogFormula("IQAE321", "");
//        expression2.setFormula("R1");
        Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
        Assert::assertNull("Username matches", expression2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
//        Assert::assertEquals("String matches", "Formula: R1", expression2.getLongDescription());

        expression2 = new AnalogFormula("IQAE321", "My expression");
//        expression2.setFormula("R1");
        Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
        Assert::assertEquals("Username matches", "My expression", expression2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
//        Assert::assertEquals("String matches", "Formula: R1", expression2.getLongDescription());

        expression2 = new AnalogFormula("IQAE321", "");
//        expression2.setFormula("R1 and R2");
        Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
        Assert::assertNull("Username matches", expression2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
//        Assert::assertEquals("String matches", "Formula: R1 and R2", expression2.getLongDescription());

        expression2 = new AnalogFormula("IQAE321", "My expression");
//        expression2.setFormula("R1 or R2");
        Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
        Assert::assertEquals("Username matches", "My expression", expression2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
//        Assert::assertEquals("String matches", "Formula: R1 or R2", expression2.getLongDescription());

        bool thrown = false;
        try {
            // Illegal system name
            new AnalogFormula("IQE55:12:XY11", "");
        } catch (IllegalArgumentException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);

        thrown = false;
        try {
            // Illegal system name
            new AnalogFormula("IQE55:12:XY11", "A name");
        } catch (IllegalArgumentException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);
    }

    // Test action when at least one child socket is not connected
    //@Test
    /*public*/  void AnalogFormulaTest::testCtorAndSetup1() {
        AnalogExpressionManager* m = (DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
        QString managerName = m->getClassName();

        QList<MaleSocket*> maleSockets = QList<MaleSocket*>();
        maleSockets.append(m->registerExpression(new AnalogExpressionMemory("IQAE52", "")));
        maleSockets.append(nullptr);  // This is null by purpose
        maleSockets.append(m->registerExpression(new AnalogExpressionMemory("IQAE554", "")));
        maleSockets.append(nullptr);  // This is null by purpose
        maleSockets.append(m->registerExpression(new AnalogExpressionMemory("IQAE3", "")));

        QList<AnalogFormula::SocketData*> actionSystemNames = QList<AnalogFormula::SocketData*>();
        actionSystemNames.append(new AnalogFormula::SocketData("XYZ123", "IQAE52", managerName));
        actionSystemNames.append(new AnalogFormula::SocketData("ZH12", "", managerName));   // This is null by purpose
        actionSystemNames.append(new AnalogFormula::SocketData("Hello", "IQAE554", managerName));
        // IQAE61232 doesn't exist by purpose
        actionSystemNames.append(new AnalogFormula::SocketData("SomethingElse", "IQAE61232", managerName));
        actionSystemNames.append(new AnalogFormula::SocketData("Yes123", "IQAE3", managerName));

        AnalogFormula* expression = new AnalogFormula("IQAE321", "", actionSystemNames);
        Assert::assertNotNull("exists", expression, __FILE__, __LINE__);
        Assert::assertEquals("expression has 5 female sockets", 5, expression->getChildCount(), __FILE__, __LINE__);

        for (int i=0; i < 5; i++) {
            AnalogFormula::SocketData* socketData = actionSystemNames.at(i);
            Assert::assertEquals("expression female socket name is "+socketData->_socketName,
                    socketData->_socketName, expression->getChild(i)->getName(), __FILE__, __LINE__);
            Assert::assertEquals("expression female socket is of correct class",
                    "jmri.jmrit.logixng.implementation.DefaultFemaleGenericExpressionSocket",
                    expression->getChild(i)->getClassName(), __FILE__, __LINE__);
            Assert::assertFalse("expression female socket is not connected",
                    expression->getChild(i)->isConnected(), __FILE__, __LINE__);
        }

        // Setup action. This connects the child actions to this action
        expression->setup();

        JUnitAppender::assertMessage("cannot load analog expression IQAE61232", __FILE__, __LINE__);

        for (int i=0; i < 5; i++) {
            AnalogFormula::SocketData* socketName = actionSystemNames.at(i);
            Assert::assertEquals("expression female socket name is "+socketName->_socketName,
                    socketName->_socketName, expression->getChild(i)->getName(), __FILE__, __LINE__);

            if (maleSockets.at(i) != nullptr) {
                Assert::assertTrue("expression female socket is connected",
                        expression->getChild(i)->isConnected(), __FILE__, __LINE__);
//                Assert::assertEquals("child is correct bean",
//                        maleSockets.get(i),
//                        expression->getChild(i).getConnectedSocket());
            } else {
                Assert::assertFalse("expression female socket is not connected",
                        expression->getChild(i)->isConnected(), __FILE__, __LINE__);
            }
        }

        Assert::assertEquals("expression has 5 female sockets", 5, expression->getChildCount(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogFormulaTest::testCtorAndSetup2() {
        AnalogExpressionManager* m = (DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
        QString managerName = m->getClassName();

        QList<MaleSocket*> maleSockets = QList<MaleSocket*>();
        maleSockets.append(m->registerExpression(new AnalogExpressionMemory("IQAE52", "")));
        maleSockets.append(m->registerExpression(new AnalogExpressionMemory("IQAE99", "")));
        maleSockets.append(m->registerExpression(new AnalogExpressionMemory("IQAE554", "")));
        maleSockets.append(m->registerExpression(new AnalogExpressionMemory("IQAE61232", "")));
        maleSockets.append(m->registerExpression(new AnalogExpressionMemory("IQAE3", "")));

        QList<AnalogFormula::SocketData*> actionSystemNames = QList<AnalogFormula::SocketData*>();
        actionSystemNames.append(new AnalogFormula::SocketData("XYZ123", "IQAE52", managerName));
        actionSystemNames.append(new AnalogFormula::SocketData("ZH12", "IQAE99", managerName));
        actionSystemNames.append(new AnalogFormula::SocketData("Hello", "IQAE554", managerName));
        actionSystemNames.append(new AnalogFormula::SocketData("SomethingElse", "IQAE61232", managerName));
        actionSystemNames.append(new AnalogFormula::SocketData("Yes123", "IQAE3", managerName));

        AnalogFormula* expression = new AnalogFormula("IQAE321", "", actionSystemNames);
        Assert::assertNotNull("exists", expression, __FILE__, __LINE__);
        Assert::assertEquals("expression has 5 female sockets", 5, expression->getChildCount(), __FILE__, __LINE__);

        for (int i=0; i < 5; i++) {
            AnalogFormula::SocketData* socketData = actionSystemNames.at(i);
            Assert::assertEquals("expression female socket name is "+socketData->_socketName,
                    socketData->_socketName, expression->getChild(i)->getName(), __FILE__, __LINE__);
            Assert::assertEquals("expression female socket is of correct class",
                    "jmri.jmrit.logixng.implementation.DefaultFemaleGenericExpressionSocket",
                    expression->getChild(i)->getClassName(), __FILE__, __LINE__);
            Assert::assertFalse("expression female socket is not connected",
                    expression->getChild(i)->isConnected(), __FILE__, __LINE__);
        }

        // Setup action. This connects the child actions to this action
        expression->setup();

        for (int i=0; i < 5; i++) {
            AnalogFormula::SocketData* socketData = actionSystemNames.at(i);
            Assert::assertEquals("expression female socket name is "+socketData->_socketName,
                    socketData->_socketName, expression->getChild(i)->getName(), __FILE__, __LINE__);

            if (maleSockets.at(i) != nullptr) {
                Assert::assertTrue("expression female socket is connected",
                        expression->getChild(i)->isConnected(), __FILE__, __LINE__);
//                Assert::assertEquals("child is correct bean",
//                        maleSockets.get(i),
//                        expression->getChild(i).getConnectedSocket());
            } else {
                Assert::assertFalse("expression female socket is not connected",
                        expression->getChild(i)->isConnected(), __FILE__, __LINE__);
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
    /*public*/  void AnalogFormulaTest::testCtorAndSetup3() /*throws NoSuchMethodException, IllegalAccessException, IllegalArgumentException*/ {
        QList<AnalogFormula::SocketData*> actionSystemNames = QList<AnalogFormula::SocketData*>();
        actionSystemNames.append(new AnalogFormula::SocketData("XYZ123", "IQAE52", ""));

        AnalogFormula* expression = new AnalogFormula("IQAE321", "", actionSystemNames);
#if 0
        java.lang.reflect.Method method =
                expression->getClass().getDeclaredMethod("setExpressionSystemNames", new Class<?>[]{List.class});
        method.setAccessible(true);

        boolean hasThrown = false;
        try {
            method.invoke(expression, new Object[]{null});
        } catch (InvocationTargetException e) {
            if (e.getCause() instanceof RuntimeException) {
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
    /*public*/  void AnalogFormulaTest::testSetChildCount() /*throws SocketAlreadyConnectedException*/ {
        AnalogFormula* a = (AnalogFormula*)_base->bself();
        AtomicBoolean* ab = new AtomicBoolean(false);

//        _base.addPropertyChangeListener((PropertyChangeEvent evt) -> {
//            ab.set(true);
//        });
        ((AbstractBase* )_base->bself())->AbstractNamedBean::addPropertyChangeListener(new AFTPropertyChangeListener(ab));

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

        // Test setChildCount to same number of children as before
        ab->set(false);
        a->setChildCount(2);
        Assert::assertEquals("numChilds are correct", 2, a->getChildCount(), __FILE__, __LINE__);
        Assert::assertFalse("PropertyChangeEvent not fired", ab->get(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogFormulaTest::testFormula() /*throws ParserException, SocketAlreadyConnectedException*/ {
        AnalogFormula* a = (AnalogFormula*)_base->bself();

        a->getChild(0)->_disconnect();
        a->getChild(0)->_connect(getConnectableChild());
        a->getChild(0)->setName("Abc");
        a->getChild(1)->_disconnect();
        a->getChild(1)->_connect(getConnectableChild());
        a->getChild(1)->setName("Xyz");

        a->setFormula("Xyz + Abc");
        Assert::assertEquals("Formula is correct", "Xyz + Abc", a->getFormula(), __FILE__, __LINE__);

        a->setFormula("Abc - Xyz");
        Assert::assertEquals("Formula is correct", "Abc - Xyz", a->getFormula(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogFormulaTest::testGetChild() /*throws Exception*/ {
        AnalogFormula* expression2 = new AnalogFormula("IQAE321", "");
//        expression2.setFormula("R1");

        for (int i=0; i < 3; i++) {
            Assert::assertTrue("getChildCount() returns "+(i+1), i+1 == expression2->getChildCount(), __FILE__, __LINE__);

            Assert::assertNotNull("getChild(0) returns a non null value",
                   (QObject*) expression2->getChild(0), __FILE__, __LINE__);
#if 1
            //assertIndexOutOfBoundsException(expression2::getChild, i+1, i+1);
          assertIndexOutOfBoundsException(new RWI01(expression2), i+1, i+1);

#endif
            // Connect a new child expression
            AnalogExpressionConstant* expr = new AnalogExpressionConstant("IQAE"+i, "");
            MaleSocket* maleSocket = ((DefaultAnalogExpressionManager*)
                    InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(expr);
            expression2->getChild(i)->_connect(maleSocket);
        }
    }

    //@Test
    /*public*/  void AnalogFormulaTest::testCategory() {
        Assert::assertTrue("Category matches", Category::COMMON == _base->getCategory(), __FILE__, __LINE__);
    }

    // Test the methods connected(FemaleSocket) and getExpressionSystemName(int)
    //@Test
    /*public*/  void AnalogFormulaTest::testConnected_getExpressionSystemName() /*throws SocketAlreadyConnectedException */{
        AnalogFormula* expression = new AnalogFormula("IQAE121", "");

        AnalogExpressionMemory* analogExpressionMemory = new AnalogExpressionMemory("IQAE122", "");
        MaleSocket* maleSAMSocket =(MaleSocket*)((DefaultAnalogExpressionManager*)
                InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(analogExpressionMemory);

        Assert::assertEquals("Num children is correct", 1, expression->getChildCount(), __FILE__, __LINE__);

        // Test connect and disconnect
        expression->getChild(0)->_connect(maleSAMSocket);
        Assert::assertEquals("Num children is correct", 2, expression->getChildCount(), __FILE__, __LINE__);
        Assert::assertEquals("getExpressionSystemName(0) is correct", "IQAE122", expression->getExpressionSystemName(0), __FILE__, __LINE__);
        Assert::assertNull("getExpressionSystemName(1) is null", expression->getExpressionSystemName(1), __FILE__, __LINE__);
        expression->getChild(0)->_disconnect();
        Assert::assertEquals("Num children is correct", 2, expression->getChildCount(), __FILE__, __LINE__);
        Assert::assertNull("getExpressionSystemName(0) is null", expression->getExpressionSystemName(0), __FILE__, __LINE__);
        Assert::assertNull("getExpressionSystemName(1) is null", expression->getExpressionSystemName(1), __FILE__, __LINE__);

        expression->getChild(1)->_connect(maleSAMSocket);
        Assert::assertEquals("Num children is correct", 2, expression->getChildCount(), __FILE__, __LINE__);
        Assert::assertNull("getExpressionSystemName(0) is null", expression->getExpressionSystemName(0), __FILE__, __LINE__);
        Assert::assertEquals("getExpressionSystemName(1) is correct", "IQAE122", expression->getExpressionSystemName(1), __FILE__, __LINE__);
        expression->getChild(0)->_disconnect();    // Test removing child with the wrong index.
        Assert::assertEquals("Num children is correct", 2, expression->getChildCount(), __FILE__, __LINE__);
        Assert::assertNull("getExpressionSystemName(0) is null", expression->getExpressionSystemName(0), __FILE__, __LINE__);
        Assert::assertEquals("getExpressionSystemName(1) is correct", "IQAE122", expression->getExpressionSystemName(1), __FILE__, __LINE__);
        expression->getChild(1)->_disconnect();
        Assert::assertEquals("Num children is correct", 2, expression->getChildCount(), __FILE__, __LINE__);
        Assert::assertNull("getExpressionSystemName(0) is null", expression->getExpressionSystemName(0), __FILE__, __LINE__);
        Assert::assertNull("getExpressionSystemName(1) is null", expression->getExpressionSystemName(1), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogFormulaTest::testDescription() {
        AnalogFormula* expression = new AnalogFormula("IQAE321", "");
        Assert::assertEquals("strings matches", "Analog Formula", expression->getShortDescription(QLocale()), __FILE__, __LINE__);
        Assert::assertEquals("strings matches", "Analog Formula: empty", expression->getLongDescription(QLocale()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogFormulaTest::testEvaluateEmptyFormula() /*throws ParserException, JmriException */{
        AnalogFormula* expression = new AnalogFormula("IQAE321", "");
        expression->setFormula("");
        Assert::assertTrue("Empty formula returns 0.0", 0.0 == expression->evaluate(), __FILE__, __LINE__);
    }
/*
    private void testValidate(bool expectedResult, QString formula, QList<AnalogExpressionBean*> conditionalVariablesList) throws Exception {
        Formula ix1 = new Formula("IQDE321", "IXIC 1");
        ix1.setFormula("R1");

        int count = 0;
        List<ExpressionEntry> expressionEntryList = new ArrayList<>();
        for (AnalogExpressionBean expressionFormula : conditionalVariablesList) {
            String socketName = "E"+Integer.toString(count++);
            FemaleAnalogExpressionSocket socket =
                    InstanceManager.getDefault(AnalogExpressionManager.class)
                            .createFemaleSocket(null, this, socketName);
            socket.connect((MaleSocket) expressionFormula);
            expressionEntryList.add(new ExpressionEntry(socket, socketName));
        }

        if (expectedResult) {
            Assert::assertTrue("validateFormula() returns null for '"+formula+"'",
                    ix1.validateFormula(formula, expressionEntryList) == null);
        } else {
            Assert::assertTrue("validateFormula() returns error message for '"+formula+"'",
                    ix1.validateFormula(formula, expressionEntryList) != null);
        }
    }

    private void testCalculate(int expectedResult, String formula,
            List<AnalogExpressionBean> conditionalVariablesList, String errorMessage)
            throws Exception {

        Formula ix1 = new Formula("IQDE321", "IXIC 1");
        ix1.setFormula(formula);

//        for (int i=0; i < ix1.getChildCount(); i++) {
//            ix1.getChild(i).disconnect();
//        }

        ix1.setChildCount(conditionalVariablesList.size());

        for (int i=0; i < conditionalVariablesList.size(); i++) {
            ix1.getChild(i).connect((MaleSocket)conditionalVariablesList.get(i));
        }

        switch (expectedResult) {
            case Formula.FALSE:
                Assert::assertFalse("validateFormula() returns FALSE for '"+formula+"'",
                        ix1.evaluate());
                break;

            case Formula.TRUE:
//                System.err.format("formula: %s%n", formula);
//                System.err.format("variable: %b%n", conditionalVariablesList.get(0).evaluate(isCompleted));
                Assert::assertTrue("validateFormula() returns TRUE for '"+formula+"'",
                        ix1.evaluate());
                break;

            default:
                throw new RuntimeException(String.format("Unknown expected result: %d", expectedResult));
        }

        if (! errorMessage.isEmpty()) {
            jmri.util.JUnitAppender.assertErrorMessageStartsWith(errorMessage);
        }
    }

    @Test
    public  void testValidate() throws Exception {
        AnalogExpressionBean[] conditionalVariables_Empty = { };
        List<AnalogExpressionBean> conditionalVariablesList_Empty = Arrays.asList(conditionalVariables_Empty);

        AnalogExpressionBean trueExpression =
                InstanceManager.getDefault(
                        AnalogExpressionManager.class).registerExpression(
                                new True(InstanceManager.getDefault(AnalogExpressionManager.class).getAutoSystemName(), null));
//        AnalogExpressionBean falseExpression = InstanceManager.getDefault(AnalogExpressionManager.class).registerExpression(new False(conditionalNG));

        AnalogExpressionBean[] conditionalVariables_True
                = { trueExpression };
        List<AnalogExpressionBean> conditionalVariablesList_True = Arrays.asList(conditionalVariables_True);

        AnalogExpressionBean[] conditionalVariables_TrueTrueTrue
                = { trueExpression
                        , trueExpression
                        , trueExpression };
        List<AnalogExpressionBean> conditionalVariablesList_TrueTrueTrue = Arrays.asList(conditionalVariables_TrueTrueTrue);

        // Test empty formula string
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

    @Test
    @SuppressWarnings("unused") // test building in progress
    public  void testCalculate() throws Exception {
        AnalogExpressionBean[] conditionalVariables_Empty = { };
        List<AnalogExpressionBean> conditionalVariablesList_Empty = Arrays.asList(conditionalVariables_Empty);

        AnalogExpressionBean trueExpression =
                InstanceManager.getDefault(
                        AnalogExpressionManager.class).registerExpression(
                                new True(InstanceManager.getDefault(AnalogExpressionManager.class).getAutoSystemName(), null));
        AnalogExpressionBean falseExpression =
                InstanceManager.getDefault(
                        AnalogExpressionManager.class).registerExpression(
                                new False(InstanceManager.getDefault(AnalogExpressionManager.class).getAutoSystemName(), null));

        AnalogExpressionBean[] conditionalVariables_True
                = { trueExpression };
        List<AnalogExpressionBean> conditionalVariablesList_True = Arrays.asList(conditionalVariables_True);

        AnalogExpressionBean[] conditionalVariables_False
                = { falseExpression };
        List<AnalogExpressionBean> conditionalVariablesList_False = Arrays.asList(conditionalVariables_False);

        AnalogExpressionBean[] conditionalVariables_TrueTrueTrue
                = { trueExpression
                        , trueExpression
                        , trueExpression };
        List<AnalogExpressionBean> conditionalVariablesList_TrueTrueTrue = Arrays.asList(conditionalVariables_TrueTrueTrue);

        // Test with two digit variable numbers
        AnalogExpressionBean[] conditionalVariables_TrueTrueFalseTrueTrueFalseTrueTrueFalseTrueTrueFalse
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
        List<AnalogExpressionBean> conditionalVariablesList_TrueTrueFalseTrueTrueFalseTrueTrueFalseTrueTrueFalse =
                Arrays.asList(conditionalVariables_TrueTrueFalseTrueTrueFalseTrueTrueFalseTrueTrueFalse);


        // Test empty formula string
        testCalculate(Formula.FALSE, "", conditionalVariablesList_Empty, "");
//        testCalculate(Formula.FALSE, "", conditionalVariablesList_True,
//                "IXIC 1 parseCalculation error formula= , ex= java.lang.StringIndexOutOfBoundsException");
        testCalculate(Formula.FALSE, "", conditionalVariablesList_True, "");

        // Test illegal number
        testCalculate(Formula.FALSE, "R#", conditionalVariablesList_True,
                "IXIC 1 parseCalculation error formula= R#, ex= java.lang.NumberFormatException");
        testCalculate(Formula.FALSE, "R-", conditionalVariablesList_True,
                "IXIC 1 parseCalculation error formula= R-, ex= java.lang.NumberFormatException");
        testCalculate(Formula.FALSE, "Ra", conditionalVariablesList_True,
                "IXIC 1 parseCalculation error formula= Ra, ex= java.lang.NumberFormatException");

        // Test single condition
        testCalculate(Formula.TRUE, "R1", conditionalVariablesList_True, "");
        testCalculate(Formula.FALSE, "R1", conditionalVariablesList_False, "");
        testCalculate(Formula.FALSE, "not R1", conditionalVariablesList_True, "");
        testCalculate(Formula.TRUE, "not R1", conditionalVariablesList_False, "");

        // Test single item but wrong item (R2 instead of R1)
//        testCalculate(Formula.FALSE, "R2)", conditionalVariablesList_True,
//                "IXIC 1 parseCalculation error formula= R2), ex= java.lang.ArrayIndexOutOfBoundsException");

        // Test two digit variable numbers
        testCalculate(Formula.TRUE, "R3 and R12 or R5 and R10",
                conditionalVariablesList_TrueTrueFalseTrueTrueFalseTrueTrueFalseTrueTrueFalse, "");
        testCalculate(Formula.FALSE, "R3 and (R12 or R5) and R10",
                conditionalVariablesList_TrueTrueFalseTrueTrueFalseTrueTrueFalseTrueTrueFalse, "");
        testCalculate(Formula.FALSE, "R12 and R10",
                conditionalVariablesList_TrueTrueFalseTrueTrueFalseTrueTrueFalseTrueTrueFalse, "");
        testCalculate(Formula.TRUE, "R12 or R10",
                conditionalVariablesList_TrueTrueFalseTrueTrueFalseTrueTrueFalseTrueTrueFalse, "");
        testCalculate(Formula.FALSE, "not (R12 or R10)",
                conditionalVariablesList_TrueTrueFalseTrueTrueFalseTrueTrueFalseTrueTrueFalse, "");

        // Test parentheses
        testCalculate(Formula.TRUE, "([{R1)}]", conditionalVariablesList_True, "");
//        testCalculate(Formula.FALSE, "(R2", conditionalVariablesList_True,
//                "IXIC 1 parseCalculation error formula= (R2, ex= java.lang.ArrayIndexOutOfBoundsException");

        // Test several items
        testCalculate(Formula.FALSE, "R1 and R2 and R3", conditionalVariablesList_True,
                "IXIC 1 parseCalculation error formula= R1 and R2 and R3, ex= java.lang.IndexOutOfBoundsException");
        testCalculate(Formula.TRUE, "R1", conditionalVariablesList_TrueTrueTrue, "");
        testCalculate(Formula.TRUE, "R2", conditionalVariablesList_TrueTrueTrue, "");
        testCalculate(Formula.TRUE, "R3", conditionalVariablesList_TrueTrueTrue, "");
        testCalculate(Formula.TRUE, "R1 and R2 and R3", conditionalVariablesList_TrueTrueTrue, "");
        testCalculate(Formula.TRUE, "R2 AND R1 or R3", conditionalVariablesList_TrueTrueTrue, "");

        // Test invalid combinations of and, or, not
        testCalculate(Formula.FALSE, "R1 and or R3 and R2", conditionalVariablesList_TrueTrueTrue,
                "IXIC 1 parseCalculation error formula= R1 and or R3 and R2, ex= jmri.JmriException: Unexpected operator or characters < ORR3ANDR2 >");
        testCalculate(Formula.FALSE, "R1 or or R3 and R2", conditionalVariablesList_TrueTrueTrue,
                "IXIC 1 parseCalculation error formula= R1 or or R3 and R2, ex= jmri.JmriException: Unexpected operator or characters < ORR3ANDR2 >");
        testCalculate(Formula.FALSE, "R1 or and R3 and R2", conditionalVariablesList_TrueTrueTrue,
                "IXIC 1 parseCalculation error formula= R1 or and R3 and R2, ex= jmri.JmriException: Unexpected operator or characters < ANDR3ANDR2 >");
        testCalculate(Formula.FALSE, "R1 not R3 and R2", conditionalVariablesList_TrueTrueTrue,
                "IXIC 1 parseCalculation error formula= R1 not R3 and R2, ex= jmri.JmriException: Could not find expected operator < NOTR3ANDR2 >");
        testCalculate(Formula.FALSE, "and R1 not R3 and R2", conditionalVariablesList_TrueTrueTrue,
                "IXIC 1 parseCalculation error formula= and R1 not R3 and R2, ex= jmri.JmriException: Unexpected operator or characters < ANDR1NOTR3ANDR2 >");
        testCalculate(Formula.FALSE, "R1 or R3 and R2 or", conditionalVariablesList_TrueTrueTrue,
                "IXIC 1 parseCalculation error formula= R1 or R3 and R2 or, ex= java.lang.StringIndexOutOfBoundsException");

        // Test several items and parenthese
        testCalculate(Formula.TRUE, "(R1 and R3) and R2", conditionalVariablesList_TrueTrueTrue, "");
        testCalculate(Formula.FALSE, "(R1 and R3) and not R2", conditionalVariablesList_TrueTrueTrue, "");
        testCalculate(Formula.FALSE, "(R1 and) R3 and not R2", conditionalVariablesList_TrueTrueTrue,
                "IXIC 1 parseCalculation error formula= (R1 and) R3 and not R2, ex= jmri.JmriException: Unexpected operator or characters < )R3ANDNOTR2 >");
        testCalculate(Formula.FALSE, "R1( and R3) and not R2", conditionalVariablesList_TrueTrueTrue,
                "IXIC 1 parseCalculation error formula= R1( and R3) and not R2, ex= jmri.JmriException: Could not find expected operator < (ANDR3)ANDNOTR2 >");
        testCalculate(Formula.FALSE, "R1 (and R3 and) not R2", conditionalVariablesList_TrueTrueTrue,
                "IXIC 1 parseCalculation error formula= R1 (and R3 and) not R2, ex= jmri.JmriException: Could not find expected operator < (ANDR3AND)NOTR2 >");
        testCalculate(Formula.FALSE, "(R1 and R3) and not R2)", conditionalVariablesList_TrueTrueTrue, "");
        testCalculate(Formula.TRUE, "(R1 and (R3) and R2)", conditionalVariablesList_TrueTrueTrue, "");
        testCalculate(Formula.FALSE, "(R1 and (R3) and not R2)", conditionalVariablesList_TrueTrueTrue, "");
    }
*/

    // The minimal setup for log4J
    //@Before
    /*public*/  void AnalogFormulaTest::setUp() /*throws Exception*/ {
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
        DoAnalogAction* doAnalogAction = new DoAnalogAction("IQDA321", "");
        MaleSocket* maleSocket =((DefaultDigitalActionManager*)
                InstanceManager::getDefault("DigitalActionManager"))->registerAction(doAnalogAction);
        conditionalNG->getChild(0)->_connect(maleSocket);

        expressionFormula = new AnalogFormula("IQAE321", "");
//        expressionFormula.setFormula("1");
//        expressionFormula.setFormula("true");
        expressionFormula->setFormula("E1");
        MaleSocket* maleSocketExpressionFormula =((DefaultAnalogExpressionManager*)
                InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(expressionFormula);
        doAnalogAction->getChild(0)->_connect(maleSocketExpressionFormula);

        AnalogExpressionConstant* childExpression = new AnalogExpressionConstant("IQAE322", "");
        childExpression->setValue(1.0);
        MaleSocket* maleSocketChild =((DefaultAnalogExpressionManager*)
                InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(childExpression);
        maleSocketExpressionFormula->getChild(0)->_connect(maleSocketChild);

        _base = expressionFormula;
        _baseMaleSocket = maleSocketExpressionFormula;

        analogMemory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM2");
        analogActionMemory = new AnalogActionMemory("IQAA1", "");
        analogActionMemory->setMemory(analogMemory);
        MaleSocket* socketAnalogActionMemory = ((DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))->registerAction(analogActionMemory);
        doAnalogAction->getChild(1)->_connect(socketAnalogActionMemory);

        if (! logixNG->setParentForAllChildren(new QList<QString>())) throw new RuntimeException();
        logixNG->setEnabled(true);
    }

    //@After
    /*public*/  void AnalogFormulaTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }
