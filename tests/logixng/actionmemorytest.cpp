#include "actionmemorytest.h"
#include "actionmemory.h"
#include "instancemanager.h"
#include "logixng_thread.h"
#include "assert1.h"
#include "junitutil.h"
#include "defaultmemorymanager.h"
#include "defaultlogixngmanager.h"
#include "category.h"
#include "defaultconditionalngscaffold.h"
#include "defaultconditionalngmanager.h"
#include "defaultdigitalactionmanager.h"
#include "junitappender.h"
#include "vptr.h"

ActionMemoryTest::ActionMemoryTest(QObject *parent) : AbstractDigitalActionTestBase(parent)
{
 setObjectName("ActionMemoryTest");
}

/**
 * Test ActionMemory
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  class ActionMemoryTest extends AbstractDigitalActionTestBase {



    //@Override
    /*public*/  ConditionalNG* ActionMemoryTest::getConditionalNG() {
        return conditionalNG;
    }

    //@Override
    /*public*/  LogixNG* ActionMemoryTest::getLogixNG() {
        return logixNG;
    }

    //@Override
    /*public*/  MaleSocket* ActionMemoryTest::getConnectableChild() {
        return nullptr;
    }

    //@Override
    /*public*/  QString ActionMemoryTest::getExpectedPrintedTree() {
        return QString("Set memory IM1 to \"\" ::: Use default\n");
    }

    //@Override
    /*public*/  QString ActionMemoryTest::getExpectedPrintedTreeFromRoot() {
        return QString(
                "LogixNG: A logixNG\n" \
                "   ConditionalNG: A conditionalNG\n" \
                "      ! A\n" \
                "         Set memory IM1 to \"\" ::: Use default\n");
    }

    //@Override
    /*public*/  NamedBean* ActionMemoryTest::createNewBean(QString systemName) {
        return new ActionMemory(systemName, "");
    }

    //@Override
    /*public*/  bool ActionMemoryTest::addNewSocket() {
        return false;
    }

    //@Test
    /*public*/  void ActionMemoryTest::testCtor() /*throws JmriException*/ {
        Assert::assertTrue("object exists", _base != nullptr, __FILE__, __LINE__);

        ActionMemory* action2;
        Assert::assertNotNull("memory is not null", memory, __FILE__, __LINE__);
        memory->setValue("Old value");

        action2 = new ActionMemory("IQDA321", "");
        action2->setMemoryOperation(ActionMemory::MemoryOperation::SetToNull);
        Assert::assertNotNull("object exists", action2, __FILE__, __LINE__);
        Assert::assertNull("Username matches", action2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Set memory '' to null", action2->getLongDescription(QLocale()), __FILE__, __LINE__);

        action2 = new ActionMemory("IQDA321", "My memory");
        action2->setMemoryOperation(ActionMemory::MemoryOperation::SetToString);
        action2->setOtherConstantValue("New value");
        Assert::assertNotNull("object exists", action2, __FILE__, __LINE__);
        Assert::assertEquals("Username matches", "My memory", action2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Set memory '' to \"New value\"", action2->getLongDescription(QLocale()), __FILE__, __LINE__);

        action2 = new ActionMemory("IQDA321", "");
        action2->setMemoryOperation(ActionMemory::MemoryOperation::CopyMemoryToMemory);
        action2->setMemory(memory);
        Memory* otherMemory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM12");
        action2->setOtherMemory(otherMemory);
        Assert::assertTrue("memory is correct", memory == action2->getMemory()->getBean(), __FILE__, __LINE__);
        Assert::assertNotNull("object exists", action2, __FILE__, __LINE__);
        Assert::assertNull("Username matches", action2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Set memory IM1 to the value of memory IM12", action2->getLongDescription(QLocale()), __FILE__, __LINE__);

        bool thrown = false;
        try {
            // Illegal system name
            new ActionMemory("IQA55:12:XY11", "");
        } catch (IllegalArgumentException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);

        thrown = false;
        try {
            // Illegal system name
            new ActionMemory("IQA55:12:XY11", "A name");
        } catch (IllegalArgumentException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);

        // Test setup(). This method doesn't do anything, but execute it for coverage.
        _base->setup();
    }

    //@Test
    /*public*/  void ActionMemoryTest::testGetChild() {
        Assert::assertTrue("getChildCount() returns 0", 0 == actionMemory->getChildCount(), __FILE__, __LINE__);

        bool hasThrown = false;
        try {
            actionMemory->getChild(0);
        } catch (UnsupportedOperationException* ex) {
            hasThrown = true;
            Assert::assertEquals("Error message is correct", "Not supported.", ex->getMessage(), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception is thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ActionMemoryTest::testSetMemory() {
        actionMemory->unregisterListeners();

        Memory* memory11 = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM11");
        Memory* memory12 = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM12");
        NamedBeanHandle<Memory*>* memoryHandle12 = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(memory12->getDisplayName(), memory12);
        Memory* memory13 = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM13");
        Memory* memory14 = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM14");
        memory14->setUserName("Some user name");

        actionMemory->removeMemory();
        Assert::assertNull("memory handle is null", actionMemory->getMemory(), __FILE__, __LINE__);

        actionMemory->setMemory(memory11);
        Assert::assertTrue("memory is correct", memory11 == actionMemory->getMemory()->getBean(), __FILE__, __LINE__);

        actionMemory->removeMemory();
        Assert::assertNull("memory handle is null", actionMemory->getMemory(), __FILE__, __LINE__);

        actionMemory->setMemory(memoryHandle12);
        Assert::assertTrue("memory handle is correct", memoryHandle12 == actionMemory->getMemory(), __FILE__, __LINE__);

        actionMemory->setMemory("A non existent memory");
        Assert::assertNull("memory handle is null", actionMemory->getMemory(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("memory \"A non existent memory\" is not found", __FILE__, __LINE__);

        actionMemory->setMemory(memory13->getSystemName());
        Assert::assertTrue("memory is correct", memory13 == actionMemory->getMemory()->getBean(), __FILE__, __LINE__);

        actionMemory->setMemory(memory14->getUserName());
        Assert::assertTrue("memory is correct", memory14 == actionMemory->getMemory()->getBean(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ActionMemoryTest::testAction() /*throws SocketAlreadyConnectedException, JmriException */{
        // Set the memory
        memory->setValue("Old value");
        // The memory should have the value "Old value"
        Assert::assertEquals("memory has correct value", "Old value", memory->getValue(), __FILE__, __LINE__);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the memory should be set
        Assert::assertEquals("memory has correct value", "", memory->getValue(), __FILE__, __LINE__);

        // Test to set memory to null
        actionMemory->setMemoryOperation(ActionMemory::MemoryOperation::SetToNull);
        // Execute the setMemoryOperation
        conditionalNG->execute();
        // The action should now be executed so the memory should be set
        Assert::assertEquals("memory has correct value", QVariant(), memory->getValue(), __FILE__, __LINE__);

        // Test to set memory to string
        actionMemory->setMemoryOperation(ActionMemory::MemoryOperation::SetToString);
        actionMemory->setOtherConstantValue("New value");
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the memory should be thrown
        Assert::assertEquals("memory has correct value", "New value", memory->getValue(), __FILE__, __LINE__);

        // Test to copy memory to memory
        Memory* otherMemory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM2");
        memory->setValue("A value");
        otherMemory->setValue("Some other value");
        actionMemory->setMemoryOperation(ActionMemory::MemoryOperation::CopyMemoryToMemory);
        actionMemory->setOtherMemory(otherMemory);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the memory should been copied to the other memory
        Assert::assertEquals("memory has correct value", "Some other value", memory->getValue(), __FILE__, __LINE__);
        Assert::assertEquals("memory has correct value", "Some other value", otherMemory->getValue(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ActionMemoryTest::testVetoableChange() /*throws PropertyVetoException*/ {
        // Get the action and set the memory
        Memory* memory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM1");
        Assert::assertNotNull("Memory is not null", memory, __FILE__, __LINE__);
        ActionMemory* action = new ActionMemory(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->AbstractManager::getAutoSystemName(), "");
        action->setMemory(memory);

        // Get some other memory for later use
        Memory* otherMemory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM99");
        Assert::assertNotNull("Memory is not null", otherMemory, __FILE__, __LINE__);
        Assert::assertNotEquals("Memory is not equal", memory, otherMemory, __FILE__, __LINE__);

        // Test vetoableChange() for some other propery
        action->vetoableChange(new PropertyChangeEvent(this, "CanSomething", "test", ""));
        Assert::assertEquals("Memory matches", memory, action->getMemory()->getBean(), __FILE__, __LINE__);

        // Test vetoableChange() for a string
        action->vetoableChange(new PropertyChangeEvent(this, "CanDelete", "test", ""));
        Assert::assertEquals("Memory matches", memory, action->getMemory()->getBean(), __FILE__, __LINE__);
        action->vetoableChange(new PropertyChangeEvent(this, "DoDelete", "test", QVariant()));
        Assert::assertEquals("Memory matches", memory, action->getMemory()->getBean(), __FILE__, __LINE__);

        // Test vetoableChange() for another memory
        action->vetoableChange(new PropertyChangeEvent(this, "CanDelete", VPtr<Memory>::asQVariant(otherMemory), QVariant()));
        Assert::assertEquals("Memory matches", memory, action->getMemory()->getBean(), __FILE__, __LINE__);
        action->vetoableChange(new PropertyChangeEvent(this, "DoDelete", VPtr<Memory>::asQVariant(otherMemory), QVariant()));
        Assert::assertEquals("Memory matches", memory, action->getMemory()->getBean(), __FILE__, __LINE__);

        // Test vetoableChange() for its own memory
        bool thrown = false;
        try {
            action->vetoableChange(new PropertyChangeEvent(this, "CanDelete", VPtr<Memory>::asQVariant(memory), QVariant()));
        } catch (PropertyVetoException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);

        Assert::assertEquals("Memory matches", memory, action->getMemory()->getBean(), __FILE__, __LINE__);
        action->vetoableChange(new PropertyChangeEvent(this, "DoDelete", VPtr<Memory>::asQVariant(memory), QVariant()));
        Assert::assertEquals("Memory still matches", memory, action->getMemory()->getBean(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ActionMemoryTest::testCategory() {
        Assert::assertTrue("Category matches", Category::ITEM == _base->getCategory(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ActionMemoryTest::testShortDescription() {
        Assert::assertEquals("String matches", "Memory", _base->getShortDescription(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ActionMemoryTest::testLongDescription() /*throws ParserException*/ {
        actionMemory->unregisterListeners();

        actionMemory->setMemoryOperation(ActionMemory::MemoryOperation::SetToNull);
        Assert::assertEquals("String matches", "Set memory IM1 to null", _base->getLongDescription(), __FILE__, __LINE__);

        actionMemory->setMemoryOperation(ActionMemory::MemoryOperation::SetToString);
        actionMemory->setOtherConstantValue("Some new value");
        Assert::assertEquals("String matches", "Set memory IM1 to \"Some new value\"", _base->getLongDescription(), __FILE__, __LINE__);

        actionMemory->setMemoryOperation(ActionMemory::MemoryOperation::CopyMemoryToMemory);
        Memory* otherMemory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM99");
        actionMemory->setOtherMemory(otherMemory);
        Assert::assertEquals("String matches", "Set memory IM1 to the value of memory IM99", _base->getLongDescription(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ActionMemoryTest::testChild() {
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
    /*public*/  void ActionMemoryTest::setUp() /*throws SocketAlreadyConnectedException, ParserException*/ {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initMemoryManager();
        JUnitUtil::initLogixNGManager();

        _category = Category::ITEM;
        _isExternal = true;

        memory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM1");
        memory->setValue("Old value");
        logixNG = ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A logixNG");
        conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;
        ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->Register((AbstractNamedBean*)conditionalNG->bself());
        logixNG->addConditionalNG((DefaultConditionalNG*)conditionalNG);
        conditionalNG->setRunDelayed(false);
        conditionalNG->setEnabled(true);
        actionMemory = new ActionMemory(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->AbstractManager::getAutoSystemName(), "");
        actionMemory->setMemory(memory);
        actionMemory->setMemoryOperation(ActionMemory::MemoryOperation::SetToString);
        MaleSocket* socket = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(actionMemory);
        conditionalNG->getChild(0)->_connect(socket);

        _base = actionMemory;
        _baseMaleSocket = socket;

        if (! logixNG->setParentForAllChildren(new QStringList())) throw new RuntimeException();
        logixNG->setEnabled(true);
    }

    //@After
    /*public*/  void ActionMemoryTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }

