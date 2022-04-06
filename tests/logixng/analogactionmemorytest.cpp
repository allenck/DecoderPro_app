#include "analogactionmemorytest.h"
#include "instancemanager.h"
#include "logixng_thread.h"
#include "analogmany.h"
#include "junitutil.h"
#include "assert1.h"
#include "analogactionmemory.h"
#include "junitappender.h"
#include "defaultmemorymanager.h"
#include "vptr.h"
#include "defaultlogixngmanager.h"
#include "defaultconditionalngscaffold.h"
#include "defaultconditionalngmanager.h"
#include "doanalogaction.h"
#include "defaultdigitalactionmanager.h"
#include "defaultanalogactionmanager.h"

/**
 * Test AnalogActionMemory
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  class AnalogActionMemoryTest extends AbstractAnalogActionTestBase {


    //@Override
    /*public*/  ConditionalNG* AnalogActionMemoryTest::getConditionalNG() {
        return conditionalNG;
    }

    //@Override
    /*public*/  LogixNG* AnalogActionMemoryTest::getLogixNG() {
        return logixNG;
    }

    //@Override
    /*public*/  MaleSocket* AnalogActionMemoryTest::getConnectableChild() {
        return nullptr;
    }

    //@Override
    /*public*/  QString AnalogActionMemoryTest::getExpectedPrintedTree() {
        return QString("Set memory IM1 ::: Use default\n");
    }

    //@Override
    /*public*/  QString AnalogActionMemoryTest::getExpectedPrintedTreeFromRoot() {
        return QString(
                "LogixNG: A new logix for test\n" \
                "   ConditionalNG: A conditionalNG\n" \
                "      ! A\n" \
                "         Read analog E and set analog A ::: Use default\n" \
                "            ?~ E\n" \
                "               Socket not connected\n" \
                "            !~ A\n" \
                "               Set memory IM1 ::: Use default%n");
    }

    //@Override
    /*public*/  NamedBean* AnalogActionMemoryTest::createNewBean(QString systemName) {
        return new AnalogMany(systemName, "");
    }

    //@Override
    /*public*/  bool AnalogActionMemoryTest::addNewSocket() {
        return false;
    }

    //@Test
    /*public*/  void AnalogActionMemoryTest::testCtor() {
        Assert::assertTrue("object exists", _base != nullptr, __FILE__, __LINE__);

        AnalogActionMemory* action2;
        Assert::assertNotNull("memory is not null", _memory, __FILE__, __LINE__);
        _memory->setValue(10.2);

        action2 = new AnalogActionMemory("IQAA11", "");
        Assert::assertNotNull("object exists", action2, __FILE__, __LINE__);
        Assert::assertTrue("Username matches", "" == action2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Set memory none", action2->getLongDescription(QLocale()), __FILE__, __LINE__);

        action2 = new AnalogActionMemory("IQAA11", "My memory");
        Assert::assertNotNull("object exists", action2, __FILE__, __LINE__);
        Assert::assertTrue("Username matches", "My memory" == (action2->AbstractNamedBean::getUserName()), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Set memory none", action2->getLongDescription(QLocale()), __FILE__, __LINE__);

        action2 = new AnalogActionMemory("IQAA11", "");
        action2->setMemory(_memory);
        Assert::assertNotNull("object exists", action2, __FILE__, __LINE__);
        Assert::assertTrue("Username matches", "" == action2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Set memory IM1", action2->getLongDescription(QLocale()), __FILE__, __LINE__);

        action2 = new AnalogActionMemory("IQAA11", "My memory");
        action2->setMemory(_memory);
        Assert::assertNotNull("object exists", action2, __FILE__, __LINE__);
        Assert::assertTrue("Username matches", "My memory" == (action2->AbstractNamedBean::getUserName()), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Set memory IM1", action2->getLongDescription(QLocale()), __FILE__, __LINE__);

        bool thrown = false;
        try {
            // Illegal system name
            new AnalogActionMemory("IQA55:12:XY11", "");
        } catch (IllegalArgumentException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);

        thrown = false;
        try {
            // Illegal system name
            new AnalogActionMemory("IQA55:12:XY11", "A name");
        } catch (IllegalArgumentException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogActionMemoryTest::testAction() /*throws SocketAlreadyConnectedException, SocketAlreadyConnectedException, JmriException*/ {
        AnalogActionMemory* action = (AnalogActionMemory*)_base->bself();
        action->setValue(0.0);
        Assert::assertTrue("Memory has correct value", 0.0 == _memory->getValue().toDouble(), __FILE__, __LINE__);
        action->setValue(1.0);
        Assert::assertTrue("Memory has correct value", 1.0 == _memory->getValue(), __FILE__, __LINE__);
        action->removeMemory();
        action->setValue(2.0);
        Assert::assertTrue("Memory has correct value", 1.0 == _memory->getValue(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogActionMemoryTest::testMemory() {
        AnalogActionMemory* action = (AnalogActionMemory*)_base->bself();
        action->removeMemory();
        Assert::assertNull("Memory is null", action->getMemory(), __FILE__, __LINE__);
        ((AnalogActionMemory*)_base->bself())->setMemory(_memory);
        Assert::assertTrue("Memory matches", _memory == action->getMemory()->getBean(), __FILE__, __LINE__);

        action->removeMemory();
        Assert::assertNull("Memory is null", action->getMemory(), __FILE__, __LINE__);
        Memory* otherMemory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM99");
        Assert::assertNotNull("memory is not null", otherMemory, __FILE__, __LINE__);
        NamedBeanHandle<Memory*>* memoryHandle = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(otherMemory->getDisplayName(), otherMemory);
        ((AnalogActionMemory*)_base->bself())->setMemory(memoryHandle);
        Assert::assertTrue("Memory matches", memoryHandle == action->getMemory(), __FILE__, __LINE__);
        Assert::assertTrue("Memory matches", otherMemory == action->getMemory()->getBean(), __FILE__, __LINE__);

        action->removeMemory();
        Assert::assertNull("Memory is null", action->getMemory(), __FILE__, __LINE__);
        action->setMemory(memoryHandle->getName());
        Assert::assertTrue("Memory matches", memoryHandle == action->getMemory(), __FILE__, __LINE__);

        // Test setMemory with a memory name that doesn't exists
        action->setMemory("Non existent memory");
        Assert::assertNull("Memory is null", action->getMemory(), __FILE__, __LINE__);
        JUnitAppender::assertErrorMessage("memory \"Non existent memory\" is not found", __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogActionMemoryTest::testVetoableChange() /*throws PropertyVetoException*/ {
        // Get some other memory for later use
        Memory* otherMemory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM99");
        Assert::assertNotNull("Memory is not null", otherMemory, __FILE__, __LINE__);
        Assert::assertNotEquals("Memory is not equal", _memory, otherMemory, __FILE__, __LINE__);

        // Get the expression and set the memory
        AnalogActionMemory* action = (AnalogActionMemory*)_base->bself();
        action->setMemory(_memory);
        Assert::assertEquals("Memory matches", _memory, action->getMemory()->getBean(), __FILE__, __LINE__);

        // Test vetoableChange() for some other propery
        action->vetoableChange(new PropertyChangeEvent(this, "CanSomething", "test", QVariant()));
        Assert::assertEquals("Memory matches", _memory, action->getMemory()->getBean(), __FILE__, __LINE__);

        // Test vetoableChange() for a string
        action->vetoableChange(new PropertyChangeEvent(this, "CanDelete", "test", QVariant()));
        Assert::assertEquals("Memory matches", _memory, action->getMemory()->getBean(), __FILE__, __LINE__);
        action->vetoableChange(new PropertyChangeEvent(this, "DoDelete", "test", QVariant()));
        Assert::assertEquals("Memory matches", _memory, action->getMemory()->getBean(), __FILE__, __LINE__);

        // Test vetoableChange() for another memory
        action->vetoableChange(new PropertyChangeEvent(this, "CanDelete", VPtr<Memory>::asQVariant(otherMemory), QVariant()));
        Assert::assertEquals("Memory matches", _memory, action->getMemory()->getBean(), __FILE__, __LINE__);
        action->vetoableChange(new PropertyChangeEvent(this, "DoDelete", VPtr<Memory>::asQVariant(otherMemory), QVariant()));
        Assert::assertEquals("Memory matches", _memory, action->getMemory()->getBean(), __FILE__, __LINE__);

        // Test vetoableChange() for its own memory
        bool thrown = false;
        try {
            action->vetoableChange(new PropertyChangeEvent(this, "CanDelete", VPtr<Memory>::asQVariant(_memory), QVariant()));
        } catch (PropertyVetoException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);

        Assert::assertEquals("Memory matches", _memory, action->getMemory()->getBean(), __FILE__, __LINE__);
        action->vetoableChange(new PropertyChangeEvent(this, "DoDelete", VPtr<Memory>::asQVariant(_memory), QVariant()));
        Assert::assertNull("Memory is null", action->getMemory(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogActionMemoryTest::testCategory() {
        Assert::assertTrue("Category matches", Category::ITEM == _base->getCategory(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogActionMemoryTest::testShortDescription() {
        Assert::assertEquals("String matches", "Memory", _base->getShortDescription(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogActionMemoryTest::testLongDescription() {
        Assert::assertEquals("String matches", "Set memory IM1", _base->getLongDescription(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AnalogActionMemoryTest::testChild() {
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
    /*public*/  void AnalogActionMemoryTest::setUp() /*throws SocketAlreadyConnectedException*/ {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initMemoryManager();
//        JUnitUtil::initLogixNGManager();

        logixNG = ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))
                ->createLogixNG("A new logix for test");  // NOI18N
        conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;
        ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->Register((AbstractNamedBean*)conditionalNG->self());
        conditionalNG->setEnabled(true);
        conditionalNG->setRunDelayed(false);
        logixNG->addConditionalNG((DefaultConditionalNG*)conditionalNG);

        DoAnalogAction* doAnalogAction = new DoAnalogAction("IQDA321", "");
        MaleSocket* maleSocketDoAnalogAction = ((DefaultDigitalActionManager*)
                InstanceManager::getDefault("DigitalActionManager"))
                        ->registerAction(doAnalogAction);
        conditionalNG->getChild(0)->_connect(maleSocketDoAnalogAction);
        _memory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM1");
        AnalogActionMemory* analogActionMemory =
                new AnalogActionMemory("IQAA321", "");
        MaleSocket* maleSocketAnalogActionMemory = ((DefaultAnalogActionManager*)
                InstanceManager::getDefault("AnalogActionManager"))
                        ->registerAction(analogActionMemory);
        doAnalogAction->getChild(1)->_connect(maleSocketAnalogActionMemory);
        analogActionMemory->setMemory(_memory);
        _base = analogActionMemory;
        _baseMaleSocket = maleSocketAnalogActionMemory;

        if (! logixNG->setParentForAllChildren(QList<QString>())) throw new RuntimeException();
        logixNG->setEnabled(true);

        ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))
                ->activateAllLogixNGs(false, false);
    }

    //@After
    /*public*/  void AnalogActionMemoryTest::tearDown() {
        _base->dispose();
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }
