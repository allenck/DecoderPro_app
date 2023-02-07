#include "analogexpressionconstanttest.h"
#include "assert1.h"
#include "junitutil.h"
#include "analogexpressionconstant.h"
#include "logixng_thread.h"
#include "runtimeexception.h"
#include "junitappender.h"
#include "conditionalng.h"
#include "memory.h"
#include "logixng.h"
#include "instancemanager.h"
#include "defaultlogixngmanager.h"
#include "defaultconditionalngscaffold.h"
#include "defaultconditionalngmanager.h"
#include "defaultdigitalactionmanager.h"
#include "doanalogaction.h"
#include "defaultanalogexpressionmanager.h"
#include "defaultmemorymanager.h"
#include "analogactionmemory.h"
#include "defaultanalogactionmanager.h"
#include "defaultlogixng.h"

AnalogExpressionConstantTest::AnalogExpressionConstantTest()
{

}

/**
 * Test AnalogExpressionConstant
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  class AnalogExpressionConstantTest extends AbstractAnalogExpressionTestBase {



//@Override
/*public*/  ConditionalNG* AnalogExpressionConstantTest::getConditionalNG() {
    return conditionalNG;
}

//@Override
/*public*/  LogixNG* AnalogExpressionConstantTest::getLogixNG() {
    return logixNG;
}

//@Override
/*public*/  MaleSocket* AnalogExpressionConstantTest::getConnectableChild() {
    return nullptr;
}

//@Override
/*public*/  QString AnalogExpressionConstantTest::getExpectedPrintedTree() {
    return QString("Get analog constant 10.2 ::: Use default\n");
}

//@Override
/*public*/  QString AnalogExpressionConstantTest::getExpectedPrintedTreeFromRoot() {
    return QString(
            "LogixNG: A logixNG%n") +
            "   ConditionalNG: A conditionalNG%n" +
            "      ! A%n" +
            "         Read analog E and set analog A ::: Use default%n" +
            "            ?~ E%n" +
            "               Get analog constant 10.2 ::: Use default%n" +
            "            !~ A%n" +
            "               Set memory IM2 ::: Use default%n";
}

//@Override
/*public*/  NamedBean* AnalogExpressionConstantTest::createNewBean(QString systemName) {
    return new AnalogExpressionConstant(systemName, "");
}

//@Override
/*public*/  bool AnalogExpressionConstantTest::addNewSocket() {
    return false;
}

//@Test
/*public*/  void AnalogExpressionConstantTest::testCtor() {
    Assert::assertTrue("object exists", _base != nullptr, __FILE__, __LINE__);

    AnalogExpressionConstant* expression2;

    expression2 = new AnalogExpressionConstant("IQAE11", "");
    Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
    Assert::assertEquals("Username matches", "", expression2->getUserName(), __FILE__, __LINE__);
    Assert::assertEquals("String matches", "Get analog constant 0", expression2->getLongDescription(QLocale()), __FILE__, __LINE__);

    expression2 = new AnalogExpressionConstant("IQAE11", "My constant value");
    Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
    Assert::assertEquals("Username matches", "My constant value", expression2->getUserName(), __FILE__, __LINE__);
    Assert::assertEquals("String matches", "Get analog constant 0", expression2->getLongDescription(QLocale()), __FILE__, __LINE__);

    expression2 = new AnalogExpressionConstant("IQAE11", "");
    expression2->setValue(12.34);
    Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
    Assert::assertEquals("Username matches", "", expression2->getUserName(), __FILE__, __LINE__);
    Assert::assertEquals("String matches", "Get analog constant 12.34", expression2->getLongDescription(QLocale()), __FILE__, __LINE__);

    expression2 = new AnalogExpressionConstant("IQAE11", "My constant");
    expression2->setValue(98.76);
    Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
    Assert::assertEquals("Username matches", "My constant", expression2->getUserName(), __FILE__, __LINE__);
    Assert::assertEquals("String matches", "Get analog constant 98.76", expression2->getLongDescription(QLocale()), __FILE__, __LINE__);

    // Call setup(). It doesn't do anything, but we call it for coverage
    expression2->setup();

    bool thrown = false;
    try {
        // Illegal system name
        new AnalogExpressionConstant("IQA55:12:XY11", "");
    } catch (IllegalArgumentException* ex) {
        thrown = true;
    }
    Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);

    thrown = false;
    try {
        // Illegal system name
        new AnalogExpressionConstant("IQA55:12:XY11", "A name");
    } catch (IllegalArgumentException* ex) {
        thrown = true;
    }
    Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);
}

//@Test
/*public*/  void AnalogExpressionConstantTest::testSetValueWithListenersRegistered() {
    bool exceptionThrown = false;
    try {
        AnalogExpressionConstant* expression = (AnalogExpressionConstant*)_base->bself();
        expression->registerListeners();
        expression->setValue(1.2);
    } catch (RuntimeException* e) {
        exceptionThrown = true;
    }
    Assert::assertTrue("Exception thrown", exceptionThrown, __FILE__, __LINE__);
    JUnitAppender::assertErrorMessage("setValue must not be called when listeners are registered", __FILE__, __LINE__);
}

//@Test
/*public*/  void AnalogExpressionConstantTest::testEvaluate() /*throws SocketAlreadyConnectedException, SocketAlreadyConnectedException*/ {
    // Disable the conditionalNG. This will unregister the listeners
    conditionalNG->setEnabled(false);
    AnalogExpressionConstant* expression = (AnalogExpressionConstant*)_base->bself();
    expression->setValue(0.0);
    Assert::assertTrue("Evaluate matches", 0.0 == expression->evaluate(), __FILE__, __LINE__);
    expression->setValue(10.0);
    Assert::assertTrue("Evaluate matches", 10.0 == expression->evaluate(), __FILE__, __LINE__);
}

//@Test
/*public*/  void AnalogExpressionConstantTest::testEvaluateAndAction() /*throws SocketAlreadyConnectedException, SocketAlreadyConnectedException*/ {

    // Set the memory
    _memoryOut->setValue(0.0);
    // The double should be 0.0
    Assert::assertTrue("memory is 0.0", 0.0 == (double)_memoryOut->getValue().toDouble(), __FILE__, __LINE__);
    // Execute the logixNG
    logixNG->execute();
    // The action is executed so the double should be 10.2
    Assert::assertTrue("memory is 10.2", 10.2 == _memoryOut->getValue().toDouble(), __FILE__, __LINE__);

    // Disable the conditionalNG
    conditionalNG->setEnabled(false);
    // Set the value of the constant.
    expressionConstant->setValue(1.0);
    // Enable the conditionalNG
    conditionalNG->setEnabled(true);
    // Execute the logixNG
    logixNG->execute();
    conditionalNG->setEnabled(false);
    // The action is executed so the double should be 1.0
    Assert::assertTrue("memory is 1.0", 1.0 == _memoryOut->getValue().toDouble(), __FILE__, __LINE__);
}

//@Test
/*public*/  void AnalogExpressionConstantTest::testCategory() {
    Assert::assertTrue("Category matches", Category::ITEM == _base->getCategory(), __FILE__, __LINE__);
}

//@Test
/*public*/  void AnalogExpressionConstantTest::testShortDescription() {
    Assert::assertEquals("String matches", "Analog constant", _base->getShortDescription(), __FILE__, __LINE__);
}

//@Test
/*public*/  void AnalogExpressionConstantTest::testLongDescription() {
    Assert::assertEquals("String matches", "Get analog constant 10.2", _base->getLongDescription(QLocale()), __FILE__, __LINE__);
}

//@Test
/*public*/  void AnalogExpressionConstantTest::testChild() {
    Assert::assertTrue("Num children is zero", 0 == _base->getChildCount(), __FILE__, __LINE__);
    bool hasThrown = false;
    try {
        _base->getChild(0);
    } catch (UnsupportedOperationException* ex) {
        hasThrown = true;
        Assert::assertTrue("Error message is correct", "Not supported." == (ex->getMessage()), __FILE__, __LINE__);
    }
    Assert::assertTrue("Exception is thrown", hasThrown, __FILE__, __LINE__);
}

// The minimal setup for log4J
//@Before
/*public*/  void AnalogExpressionConstantTest::setUp() /*throws SocketAlreadyConnectedException */{
    JUnitUtil::setUp();
    JUnitUtil::resetInstanceManager();
    JUnitUtil::resetProfileManager();
    JUnitUtil::initConfigureManager();
    JUnitUtil::initInternalSensorManager();
    JUnitUtil::initInternalTurnoutManager();
    JUnitUtil::initMemoryManager();
    JUnitUtil::initLogixNGManager();

    expressionConstant = new AnalogExpressionConstant("IQAE321", "");
    expressionConstant->setValue(10.2);

    logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A logixNG");
    conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;
    NamedBean* nb = (AbstractNamedBean*)conditionalNG->self();
    ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->Register(/*conditionalNG*/nb);
    conditionalNG->setRunDelayed(false);
    conditionalNG->setEnabled(true);

    logixNG->addConditionalNG((DefaultConditionalNG*)conditionalNG);

    DigitalActionBean* actionDoAnalog =
            new DoAnalogAction(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->getAutoSystemName(), "");
    MaleSocket* socketDoAnalog = ((DefaultDigitalActionManager*)
            InstanceManager::getDefault("DigitalActionManager"))->registerAction(actionDoAnalog);
    conditionalNG->getChild(0)->_connect(socketDoAnalog);

    MaleSocket* socketExpression = ((DefaultAnalogExpressionManager*)
            InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(expressionConstant);
    socketDoAnalog->getChild(0)->_connect(socketExpression);

    _memoryOut = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM2");
    _memoryOut->setValue(0.0);
    actionMemory = new AnalogActionMemory("IQAA1", "");
    actionMemory->setMemory(_memoryOut);
    MaleSocket* socketAction = ((DefaultAnalogActionManager*)
            InstanceManager::getDefault("AnalogActionManager"))->registerAction(actionMemory);
    socketDoAnalog->getChild(1)->_connect(socketAction);

    _base = expressionConstant;
    _baseMaleSocket = socketExpression;

    if (! logixNG->setParentForAllChildren(new QStringList())) throw new RuntimeException();
    logixNG->setEnabled(true);
}

//@After
/*public*/  void AnalogExpressionConstantTest::tearDown() {
//        JUnitAppender.clearBacklog();
    _base->dispose();
    LogixNG_Thread::stopAllLogixNGThreads();
    JUnitUtil::tearDown();
}
