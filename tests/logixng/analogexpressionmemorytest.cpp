#include "analogexpressionmemorytest.h"
#include "logixng_thread.h"
#include "instancemanager.h"
#include "assert1.h"
#include "junitutil.h"
#include "analogexpressionmemory.h"
#include "defaultconditionalng.h"
#include "logixng.h"
#include "defaultmemorymanager.h"
#include "junitappender.h"
#include "runtimeexception.h"
#include "vptr.h"
#include "defaultlogixngmanager.h"
#include "defaultconditionalngscaffold.h"
#include "defaultconditionalngmanager.h"
#include "doanalogaction.h"
#include "defaultdigitalactionmanager.h"
#include "defaultanalogexpressionmanager.h"
#include "analogactionmemory.h"
#include "defaultanalogactionmanager.h"

AnalogExpressionMemoryTest::AnalogExpressionMemoryTest(QObject *parent) : AbstractAnalogExpressionTestBase(parent)
{
 setObjectName("AnalogExpressionMemoryTest");
}
/**
 * Test AnalogExpressionMemory
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  class AnalogExpressionMemoryTest extends AbstractAnalogExpressionTestBase {



    //@Override
    /*public*/  ConditionalNG* AnalogExpressionMemoryTest::getConditionalNG() {
        return conditionalNG;
    }

    //@Override
    /*public*/  LogixNG* AnalogExpressionMemoryTest::getLogixNG() {
        return logixNG;
    }

    //@Override
    /*public*/  MaleSocket* AnalogExpressionMemoryTest::getConnectableChild() {
        return nullptr;
    }

    //@Override
    /*public*/  QString AnalogExpressionMemoryTest::getExpectedPrintedTree() {
        return QString("Get memory IM1 as analog value ::: Use default\n");
    }

    //@Override
    /*public*/  QString AnalogExpressionMemoryTest::getExpectedPrintedTreeFromRoot() {
        return QString(
                "LogixNG: A logixNG\n" \
                "   ConditionalNG: A conditionalNG\n" \
                "      ! A\n" \
                "         Read analog E and set analog A ::: Use default\n" \
                "            ?~ E\n" \
                "               Get memory IM1 as analog value ::: Use default\n" \
                "            !~ A\n" \
                "               Set memory IM2 ::: Use default\n");
    }

    //@Override
    /*public*/  NamedBean* AnalogExpressionMemoryTest::createNewBean(QString systemName) {
        return new AnalogExpressionMemory(systemName, nullptr);
    }

    //@Override
    /*public*/  bool AnalogExpressionMemoryTest::addNewSocket() {
        return false;
    }

    //@Test
    /*public*/  void AnalogExpressionMemoryTest::testCtor() {
        Assert::assertTrue("object exists", _base != nullptr, __FILE__, __LINE__);

        AnalogExpressionMemory* expression2;
        Assert::assertNotNull("memory is not null", _memory, __FILE__, __LINE__);
        _memory->setValue(10.2);

        expression2 = new AnalogExpressionMemory("IQAE11", "");
        Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
        Assert::assertTrue("Username matches", "" == expression2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Get memory none as analog value", expression2->getLongDescription(QLocale()), __FILE__, __LINE__);

        expression2 = new AnalogExpressionMemory("IQAE11", "My memory");
        Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
        Assert::assertTrue("Username matches", "My memory" == (expression2->AbstractNamedBean::getUserName()), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Get memory none as analog value", expression2->getLongDescription(QLocale()), __FILE__, __LINE__);

        expression2 = new AnalogExpressionMemory("IQAE11", "");
        expression2->setMemory(_memory);
        Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
        Assert::assertTrue("Username matches", "" == expression2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Get memory IM1 as analog value", expression2->getLongDescription(QLocale()), __FILE__, __LINE__);

        expression2 = new AnalogExpressionMemory("IQAE11", "My memory");
        expression2->setMemory(_memory);
        Assert::assertNotNull("object exists", expression2, __FILE__, __LINE__);
        Assert::assertTrue("Username matches", "My memory" == (expression2->AbstractNamedBean::getUserName()), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Get memory IM1 as analog value", expression2->getLongDescription(QLocale()), __FILE__, __LINE__);

        bool thrown = false;
        try {
            // Illegal system name
            new AnalogExpressionMemory("IQA55:12:XY11", "");
        } catch (IllegalArgumentException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);

        thrown = false;
        try {
            // Illegal system name
            new AnalogExpressionMemory("IQA55:12:XY11", "A name");
        } catch (IllegalArgumentException ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogExpressionMemoryTest::testEvaluate() /*throws SocketAlreadyConnectedException, SocketAlreadyConnectedException*/ {
        // Disable the conditionalNG. This will unregister the listeners
        conditionalNG->setEnabled(false);
        AnalogExpressionMemory* expression = (AnalogExpressionMemory*)_base->bself();
        _memory->setValue(0.0);
        Assert::assertTrue("Evaluate matches", 0.0 == expression->evaluate(), __FILE__, __LINE__);
        _memory->setValue(10.0);
        Assert::assertTrue("Evaluate matches", 10.0 == expression->evaluate(), __FILE__, __LINE__);
        expression->removeMemory();
        Assert::assertTrue("Evaluate matches", 0.0 == expression->evaluate(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogExpressionMemoryTest::testEvaluateAndAction() /*throws SocketAlreadyConnectedException, SocketAlreadyConnectedException*/ {
        // Disable the conditionalNG. This will unregister the listeners
        conditionalNG->setEnabled(false);
        // Set the memory
        _memoryOut->setValue(0.0);
        // The double should be 0.0
        Assert::assertTrue("memory is 0.0", 0.0 == _memoryOut->getValue().toDouble(), __FILE__, __LINE__);
        // Set the value of the memory. This should not execute the conditional.
        _memory->setValue(1.0);
        // The conditionalNG is not yet enabled so it shouldn't be executed.
        // So the memory should be 0.0
        Assert::assertTrue("memory is 0.0", 0.0 == _memoryOut->getValue().toDouble(), __FILE__, __LINE__);
        // Set the value of the memory. This should not execute the conditional.
        _memory->setValue(2.0);
        // The action is not yet executed so the memory should be 0.0
        Assert::assertTrue("memory is 0.0", 0.0 == _memoryOut->getValue().toDouble(), __FILE__, __LINE__);
        // Enable the conditionalNG and all its children.
        conditionalNG->setEnabled(true);
        // Set the value of the memory. This should execute the conditional.
        _memory->setValue(3.0);
        // The action should now be executed so the memory should be 3.0
        Assert::assertTrue("memory is 3.0", 3.0 == _memoryOut->getValue().toDouble(), __FILE__, __LINE__);
        // Disable the conditionalNG and all its children.
        conditionalNG->setEnabled(false);
        // The action is not yet executed so the memory should be 0.0
        Assert::assertTrue("memory is 0.0", 3.0 == _memoryOut->getValue().toDouble(), __FILE__, __LINE__);
        // Set the value of the memory. This should not execute the conditional.
        _memory->setValue(4.0);
        // The action should not be executed so the memory should still be 3.0
        Assert::assertTrue("memory is 3.0", 3.0 == _memoryOut->getValue().toDouble(), __FILE__, __LINE__);
        // Unregister listeners. This should do nothing since the listeners are
        // already unregistered.
        expressionMemory->unregisterListeners();
        // The memory should be 3.0
        Assert::assertTrue("memory is 0.0", 3.0 == _memoryOut->getValue().toDouble(), __FILE__, __LINE__);
        // Set the value of the memory. This should not execute the conditional.
        _memory->setValue(5.0);
        // The action should not be executed so the memory should still be 3.0
        Assert::assertTrue("memory is 3.0", 3.0 == _memoryOut->getValue().toDouble(), __FILE__, __LINE__);

        // Test register listeners when there is no memory.
        expressionMemory->removeMemory();
        expressionMemory->registerListeners();
    }

    //@Test
    /*public*/  void AnalogExpressionMemoryTest::testMemory() {
        // Disable the conditionalNG. This will unregister the listeners
        conditionalNG->setEnabled(false);

        AnalogExpressionMemory* expressionMemory = (AnalogExpressionMemory*)_base->bself();
        expressionMemory->removeMemory();
        Assert::assertNull("Memory is null", expressionMemory->getMemory(), __FILE__, __LINE__);
        expressionMemory->setMemory(_memory);
        Assert::assertTrue("Memory matches", _memory == expressionMemory->getMemory()->getBean(), __FILE__, __LINE__);

        expressionMemory->removeMemory();
        Assert::assertNull("Memory is null", expressionMemory->getMemory(), __FILE__, __LINE__);
        Memory* otherMemory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM99");
        Assert::assertNotNull("memory is not null", otherMemory, __FILE__, __LINE__);
        NamedBeanHandle<Memory*>* memoryHandle = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(otherMemory->getDisplayName(), otherMemory);
        expressionMemory->setMemory(memoryHandle);
        Assert::assertTrue("Memory matches", memoryHandle == expressionMemory->getMemory(), __FILE__, __LINE__);
        Assert::assertTrue("Memory matches", otherMemory == expressionMemory->getMemory()->getBean(), __FILE__, __LINE__);

        expressionMemory->removeMemory();
        Assert::assertNull("Memory is null", expressionMemory->getMemory(), __FILE__, __LINE__);
        expressionMemory->setMemory(memoryHandle->getName());
        Assert::assertTrue("Memory matches", memoryHandle == expressionMemory->getMemory(), __FILE__, __LINE__);

        // Test setMemory with a memory name that doesn't exists
        expressionMemory->setMemory("Non existent memory");
        Assert::assertNull("Memory is null", expressionMemory->getMemory(), __FILE__, __LINE__);
        JUnitAppender::assertErrorMessage("memory \"Non existent memory\" is not found", __FILE__, __LINE__);

        // Test setMemory() when listeners are registered
        expressionMemory->setMemory(_memory);
        Assert::assertNotNull("Memory is null", expressionMemory->getMemory(), __FILE__, __LINE__);
        // Enable the conditionalNG. This will register the listeners
        conditionalNG->setEnabled(true);
        bool thrown = false;
        try {
            expressionMemory->setMemory(otherMemory);
        } catch (RuntimeException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);
        JUnitAppender::assertErrorMessage("setMemory must not be called when listeners are registered", __FILE__, __LINE__);

        thrown = false;
        try {
            expressionMemory->removeMemory();
        } catch (RuntimeException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);
        JUnitAppender::assertErrorMessage("setMemory must not be called when listeners are registered", __FILE__, __LINE__);

        thrown = false;
        try {
            expressionMemory->removeMemory();
        } catch (RuntimeException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);
        JUnitAppender::assertErrorMessage("setMemory must not be called when listeners are registered", __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogExpressionMemoryTest::testRegisterListeners() {
        // Test registerListeners() when the ExpressionMemory has no memory
        conditionalNG->setEnabled(false);
        expressionMemory->removeMemory();
        conditionalNG->setEnabled(true);
    }

    //@Test
    /*public*/  void AnalogExpressionMemoryTest::testVetoableChange() /*throws PropertyVetoException*/ {
        // Disable the conditionalNG. This will unregister the listeners
        conditionalNG->setEnabled(false);

        // Get some other memory for later use
        Memory* otherMemory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM99");
        Assert::assertNotNull("Memory is not null", otherMemory, __FILE__, __LINE__);
        Assert::assertNotEquals("Memory is not equal", _memory, otherMemory, __FILE__, __LINE__);

        // Get the expression and set the memory
        AnalogExpressionMemory* expression = (AnalogExpressionMemory*)_base->bself();
        expression->setMemory(_memory);
        Assert::assertEquals("Memory matches", _memory, expression->getMemory()->getBean(), __FILE__, __LINE__);

        // Test vetoableChange() for some other propery
        expression->vetoableChange(new PropertyChangeEvent(this, "CanSomething", "test", QVariant()));
        Assert::assertEquals("Memory matches", _memory, expression->getMemory()->getBean(), __FILE__, __LINE__);

        // Test vetoableChange() for a string
        expression->vetoableChange(new PropertyChangeEvent(this, "CanDelete", "test", QVariant()));
        Assert::assertEquals("Memory matches", _memory, expression->getMemory()->getBean(), __FILE__, __LINE__);
        expression->vetoableChange(new PropertyChangeEvent(this, "DoDelete", "test", QVariant()));
        Assert::assertEquals("Memory matches", _memory, expression->getMemory()->getBean(), __FILE__, __LINE__);

        // Test vetoableChange() for another memory
        expression->vetoableChange(new PropertyChangeEvent(this, "CanDelete", VPtr<Memory>::asQVariant(otherMemory), QVariant()));
        Assert::assertEquals("Memory matches", _memory, expression->getMemory()->getBean(), __FILE__, __LINE__);
        expression->vetoableChange(new PropertyChangeEvent(this, "DoDelete", VPtr<Memory>::asQVariant(otherMemory), QVariant()));
        Assert::assertEquals("Memory matches", _memory, expression->getMemory()->getBean(), __FILE__, __LINE__);

        // Test vetoableChange() for its own memory
        bool thrown = false;
        try {
            expression->vetoableChange(new PropertyChangeEvent(this, "CanDelete", VPtr<Memory>::asQVariant(_memory), QVariant()));
        } catch (PropertyVetoException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);

        Assert::assertEquals("Memory matches", _memory, expression->getMemory()->getBean(), __FILE__, __LINE__);
        expression->vetoableChange(new PropertyChangeEvent(this, "DoDelete", VPtr<Memory>::asQVariant(_memory), QVariant()));
        Assert::assertNull("Memory is null", expression->getMemory(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogExpressionMemoryTest::testCategory() {
        Assert::assertTrue("Category matches", Category::ITEM == _base->getCategory(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogExpressionMemoryTest::testShortDescription() {
        Assert::assertEquals("String matches", "Memory as analog value", _base->getShortDescription(QLocale()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogExpressionMemoryTest::testLongDescription() {
        Assert::assertEquals("Get memory IM1 as analog value", _base->getLongDescription(QLocale()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogExpressionMemoryTest::testChild() {
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
    /*public*/  void AnalogExpressionMemoryTest::setUp() /*throws SocketAlreadyConnectedException*/ {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        QObject* obj = InstanceManager::getNullableDefault("ConfigureManager");
        JUnitUtil::initInternalSensorManager();
        obj = InstanceManager::getNullableDefault("ConfigureManager");
        JUnitUtil::initInternalTurnoutManager();
        obj = InstanceManager::getNullableDefault("ConfigureManager");
        JUnitUtil::initMemoryManager();
        obj = InstanceManager::getNullableDefault("ConfigureManager");
        JUnitUtil::initLogixNGManager();

        _memory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM1");
        Assert::assertNotNull("memory is not null", _memory, __FILE__, __LINE__);
        _memory->setValue(10.2);
        expressionMemory = new AnalogExpressionMemory("IQAE321", "");
        expressionMemory->setMemory(_memory);

        logixNG = ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A logixNG");
        conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;
        ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->Register((AbstractNamedBean*)conditionalNG->self());
        conditionalNG->setRunDelayed(false);
        conditionalNG->setEnabled(true);

        logixNG->addConditionalNG((DefaultConditionalNG*)conditionalNG);

        DigitalActionBean* actionDoAnalog =
                new DoAnalogAction(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->getAutoSystemName(), "");
        MaleSocket* socketDoAnalog = ((DefaultDigitalActionManager*)
                InstanceManager::getDefault("DigitalActionManager"))->registerAction(actionDoAnalog);
        conditionalNG->getChild(0)->_connect(socketDoAnalog);

        MaleSocket* socketExpression = ((DefaultAnalogExpressionManager*)
                InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(expressionMemory);
        socketDoAnalog->getChild(0)->_connect(socketExpression);

        _memoryOut = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM2");
        _memoryOut->setValue(0.0);
        actionMemory = new AnalogActionMemory("IQAA1", "");
        actionMemory->setMemory(_memoryOut);
        MaleSocket* socketAction = ((DefaultAnalogActionManager*)
                InstanceManager::getDefault("AnalogActionManager"))->registerAction(actionMemory);
        socketDoAnalog->getChild(1)->_connect(socketAction);

        _base = expressionMemory;
        _baseMaleSocket = socketExpression;

        if (! logixNG->setParentForAllChildren(new QStringList())) throw new RuntimeException();
        logixNG->setEnabled(true);
    }

    //@After
    /*public*/  void AnalogExpressionMemoryTest::tearDown() {
        _base->dispose();
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }
