#include "actionsensortest.h"
#include "actionsensor.h"
#include "instancemanager.h"
#include "junitutil.h"
#include "assert1.h"
#include "junitappender.h"
#include "defaultconditionalng.h"
#include "defaultmemorymanager.h"
#include "defaultdigitalactionmanager.h"
#include "defaultlogixngmanager.h"
#include "defaultconditionalngmanager.h"
#include "defaultconditionalngscaffold.h"
#include "logixng_thread.h"
#include "vptr.h"

/**
 * Test ActionSensor
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  class ActionSensorTest extends AbstractDigitalActionTestBase {



    //@Test
    /*public*/  void ActionSensorTest::testSensorState() {
        Assert::assertEquals("String matches", "Inactive", ActionSensor::SensorState::toString(ActionSensor::SensorState::Inactive), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Active", ActionSensor::SensorState::toString(ActionSensor::SensorState::Active), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Toggle", ActionSensor::SensorState::toString(ActionSensor::SensorState::Toggle), __FILE__, __LINE__);

        Assert::assertTrue("objects are equal", ActionSensor::SensorState::Inactive == ActionSensor::SensorState::get(Sensor::INACTIVE), __FILE__, __LINE__);
        Assert::assertTrue("objects are equal", ActionSensor::SensorState::Active == ActionSensor::SensorState::get(Sensor::ACTIVE), __FILE__, __LINE__);
        Assert::assertTrue("objects are equal", ActionSensor::SensorState::Toggle == ActionSensor::SensorState::get(-1), __FILE__, __LINE__);

        bool hasThrown = false;
        try {
            ActionSensor::SensorState::get(Sensor::UNKNOWN);
        } catch (IllegalArgumentException ex) {
            hasThrown = true;
            Assert::assertTrue("Error message is correct", "invalid sensor state" == (ex.getMessage()), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception is thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Override
    /*public*/  ConditionalNG* ActionSensorTest::getConditionalNG() {
        return conditionalNG;
    }

    //@Override
    /*public*/  LogixNG* ActionSensorTest::getLogixNG() {
        return logixNG;
    }

    //@Override
    /*public*/  MaleSocket* ActionSensorTest::getConnectableChild() {
        return nullptr;
    }

    //@Override
    /*public*/  QString ActionSensorTest::getExpectedPrintedTree() {
        return QString("Set sensor IS1 to state Active ::: Use default\n");
    }

    //@Override
    /*public*/  QString ActionSensorTest::getExpectedPrintedTreeFromRoot() {
        return QString(
                "LogixNG: A logixNG\n" \
                "   ConditionalNG: A conditionalNG\n" \
                "      ! A\n" \
                "         Set sensor IS1 to state Active ::: Use default\n");
    }

    //@Override
    /*public*/  NamedBean* ActionSensorTest::createNewBean(QString systemName) {
        return new ActionSensor(systemName, "");
    }

    //@Override
    /*public*/  bool ActionSensorTest::addNewSocket() {
        return false;
    }

    //@Test
    /*public*/  void ActionSensorTest::testCtor() /*throws JmriException*/ {
        Assert::assertTrue("object exists", _base != nullptr, __FILE__, __LINE__);

        ActionSensor* action2;
        Assert::assertNotNull("sensor is not null", sensor, __FILE__, __LINE__);
        sensor->setState(Sensor::ON);

        action2 = new ActionSensor("IQDA321", "");
        Assert::assertNotNull("object exists", action2, __FILE__, __LINE__);
        Assert::assertNull("Username matches", action2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Set sensor '' to state Active", action2->getLongDescription(QLocale()), __FILE__, __LINE__);

        action2 = new ActionSensor("IQDA321", "My sensor");
        Assert::assertNotNull("object exists", action2, __FILE__, __LINE__);
        Assert::assertEquals("Username matches", "My sensor", action2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Set sensor '' to state Active", action2->getLongDescription(QLocale()), __FILE__, __LINE__);

        action2 = new ActionSensor("IQDA321", "");
        action2->setSensor(sensor);
        Assert::assertTrue("sensor is correct", sensor == action2->getSensor()->getBean(), __FILE__, __LINE__);
        Assert::assertNotNull("object exists", action2, __FILE__, __LINE__);
        Assert::assertNull("Username matches", action2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Set sensor IS1 to state Active", action2->getLongDescription(QLocale()), __FILE__, __LINE__);

        Sensor* l = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provide("IS1");
        action2 = new ActionSensor("IQDA321", "My sensor");
        action2->setSensor(l);
        Assert::assertTrue("sensor is correct", l == action2->getSensor()->getBean(), __FILE__, __LINE__);
        Assert::assertNotNull("object exists", action2, __FILE__, __LINE__);
        Assert::assertEquals("Username matches", "My sensor", action2->AbstractNamedBean::getUserName(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "Set sensor IS1 to state Active", action2->getLongDescription(QLocale()), __FILE__, __LINE__);

        bool thrown = false;
        try {
            // Illegal system name
            new ActionSensor("IQA55:12:XY11", "");
        } catch (IllegalArgumentException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);

        thrown = false;
        try {
            // Illegal system name
            new ActionSensor("IQA55:12:XY11", "A name");
        } catch (IllegalArgumentException ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);

        // Test setup(). This method doesn't do anything, but execute it for coverage.
        _base->setup();
    }

    //@Test
    /*public*/  void ActionSensorTest::testGetChild() {
        Assert::assertTrue("getChildCount() returns 0", 0 == actionSensor->getChildCount(), __FILE__, __LINE__);

        bool hasThrown = false;
        try {
            actionSensor->getChild(0);
        } catch (UnsupportedOperationException* ex) {
            hasThrown = true;
            Assert::assertEquals("Error message is correct", "Not supported.", ex->getMessage(), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception is thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ActionSensorTest::testSetSensor() {
        Sensor* sensor11 = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provide("IS11");
        Sensor* sensor12 = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provide("IS12");
        NamedBeanHandle<Sensor*>* sensorHandle12 = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensor12->getDisplayName(), sensor12);
        Sensor* sensor13 = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provide("IS13");
        Sensor* sensor14 = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provide("IS14");
        sensor14->setUserName("Some user name");

        actionSensor->removeSensor();
        Assert::assertNull("sensor handle is null", actionSensor->getSensor(), __FILE__, __LINE__);

        actionSensor->setSensor(sensor11);
        Assert::assertTrue("sensor is correct", sensor11 == actionSensor->getSensor()->getBean(), __FILE__, __LINE__);

        actionSensor->removeSensor();
        Assert::assertNull("sensor handle is null", actionSensor->getSensor(), __FILE__, __LINE__);

        actionSensor->setSensor(sensorHandle12);
        Assert::assertTrue("sensor handle is correct", sensorHandle12 == actionSensor->getSensor(), __FILE__, __LINE__);

        actionSensor->setSensor("A non existent sensor");
        Assert::assertNull("sensor handle is null", actionSensor->getSensor(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("sensor \"A non existent sensor\" is not found", __FILE__, __LINE__);

        actionSensor->setSensor(sensor13->getSystemName());
        Assert::assertTrue("sensor is correct", sensor13 == actionSensor->getSensor()->getBean(), __FILE__, __LINE__);

        actionSensor->setSensor(sensor14->getUserName());
        Assert::assertTrue("sensor is correct", sensor14 == actionSensor->getSensor()->getBean(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ActionSensorTest::testAction() /*throws SocketAlreadyConnectedException, JmriException*/ {
        // Set the light
        sensor->setCommandedState(Sensor::INACTIVE);
        // The sensor should be inactive
        Assert::assertTrue("sensor is inactive",sensor->getCommandedState() == Sensor::INACTIVE, __FILE__, __LINE__);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the sensor should be active
        Assert::assertTrue("sensor is active",sensor->getCommandedState() == Sensor::ACTIVE, __FILE__, __LINE__);

        // Test to set sensor to inactive
        actionSensor->setBeanState(ActionSensor::SensorState::Inactive);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the sensor should be active
        Assert::assertTrue("sensor is active",sensor->getCommandedState() == Sensor::INACTIVE, __FILE__, __LINE__);

        // Test to set sensor to toggle
        actionSensor->setBeanState(ActionSensor::SensorState::Toggle);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the sensor should be active
        Assert::assertTrue("sensor is active",sensor->getCommandedState() == Sensor::ACTIVE, __FILE__, __LINE__);

        // Test to set sensor to toggle
        actionSensor->setBeanState(ActionSensor::SensorState::Toggle);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the sensor should be active
        Assert::assertTrue("sensor is active",sensor->getCommandedState() == Sensor::INACTIVE, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ActionSensorTest::testIndirectAddressing() /*throws JmriException*/ {

        Memory* m1 = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM1");
        m1->setValue("IS102");

        Assert::assertTrue(conditionalNG->isActive(), __FILE__, __LINE__);
        Sensor* t1 = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provide("IS101");
        Sensor* t2 = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provide("IS102");
        Sensor* t3 = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provide("IS103");
        Sensor* t4 = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provide("IS104");
        Sensor* t5 = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provide("IS105");

        actionSensor->setBeanState(ActionSensor::SensorState::Active);
        actionSensor->setSensor(t1->getSystemName());
        actionSensor->setReference("{IM1}");    // Points to "IS102"
        actionSensor->setLocalVariable("mySensor");
        actionSensor->setFormula("\"IS10\" + str(index)");
        _baseMaleSocket->addLocalVariable("refSensor", InitialValueType::String, "IS103");
        _baseMaleSocket->addLocalVariable("mySensor", InitialValueType::String, "IS104");
        _baseMaleSocket->addLocalVariable("index", InitialValueType::Integer, "5");

        // Test direct addressing
        actionSensor->setAddressing(NamedBeanAddressing::Direct);
        t1->setState(Sensor::INACTIVE);
        t2->setState(Sensor::INACTIVE);
        t3->setState(Sensor::INACTIVE);
        t4->setState(Sensor::INACTIVE);
        t5->setState(Sensor::INACTIVE);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the correct sensor should be thrown
        Assert::assertEquals(Sensor::ACTIVE, t1->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::INACTIVE, t2->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::INACTIVE, t3->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::INACTIVE, t4->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::INACTIVE, t5->getCommandedState(), __FILE__, __LINE__);

        // Test reference by memory addressing
        actionSensor->setAddressing(NamedBeanAddressing::Reference);
        t1->setState(Sensor::INACTIVE);
        t2->setState(Sensor::INACTIVE);
        t3->setState(Sensor::INACTIVE);
        t4->setState(Sensor::INACTIVE);
        t5->setState(Sensor::INACTIVE);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the correct sensor should be thrown
        Assert::assertEquals(Sensor::INACTIVE, t1->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::ACTIVE, t2->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::INACTIVE, t3->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::INACTIVE, t4->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::INACTIVE, t5->getCommandedState(), __FILE__, __LINE__);

        // Test reference by local variable addressing
        actionSensor->setReference("{refSensor}");    // Points to "IS103"
        actionSensor->setAddressing(NamedBeanAddressing::Reference);
        t1->setState(Sensor::INACTIVE);
        t2->setState(Sensor::INACTIVE);
        t3->setState(Sensor::INACTIVE);
        t4->setState(Sensor::INACTIVE);
        t5->setState(Sensor::INACTIVE);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the correct sensor should be thrown
        Assert::assertEquals(Sensor::INACTIVE, t1->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::INACTIVE, t2->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::ACTIVE, t3->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::INACTIVE, t4->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::INACTIVE, t5->getCommandedState(), __FILE__, __LINE__);

        // Test local variable addressing
        actionSensor->setAddressing(NamedBeanAddressing::LocalVariable);
        t1->setState(Sensor::INACTIVE);
        t2->setState(Sensor::INACTIVE);
        t3->setState(Sensor::INACTIVE);
        t4->setState(Sensor::INACTIVE);
        t5->setState(Sensor::INACTIVE);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the correct sensor should be thrown
        Assert::assertEquals(Sensor::INACTIVE, t1->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::INACTIVE, t2->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::INACTIVE, t3->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::ACTIVE, t4->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::INACTIVE, t5->getCommandedState(), __FILE__, __LINE__);

        // Test formula addressing
        actionSensor->setAddressing(NamedBeanAddressing::Formula);
        t1->setState(Sensor::INACTIVE);
        t2->setState(Sensor::INACTIVE);
        t3->setState(Sensor::INACTIVE);
        t4->setState(Sensor::INACTIVE);
        t5->setState(Sensor::INACTIVE);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the correct sensor should be thrown
        Assert::assertEquals(Sensor::INACTIVE, t1->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::INACTIVE, t2->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::INACTIVE, t3->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::INACTIVE, t4->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals(Sensor::ACTIVE, t5->getCommandedState(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ActionSensorTest::testIndirectStateAddressing() /*throws JmriException*/ {

        Memory* m1 = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM1");
        m1->setValue("IS102");

        Assert::assertTrue(conditionalNG->isActive(), __FILE__, __LINE__);


        // Test direct addressing
        actionSensor->setStateAddressing(NamedBeanAddressing::Direct);
        // Test Inactive
        sensor->setState(Sensor::ACTIVE);
        actionSensor->setBeanState(ActionSensor::SensorState::Inactive);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the correct sensor should be thrown
        Assert::assertEquals(Sensor::INACTIVE, sensor->getCommandedState(), __FILE__, __LINE__);
        // Test Inactive
        sensor->setState(Sensor::INACTIVE);
        actionSensor->setBeanState(ActionSensor::SensorState::Active);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the correct sensor should be thrown
        Assert::assertEquals(Sensor::ACTIVE, sensor->getCommandedState(), __FILE__, __LINE__);


        // Test reference by memory addressing
        actionSensor->setStateAddressing(NamedBeanAddressing::Reference);
        actionSensor->setStateReference("{IM1}");
        // Test Inactive
        m1->setValue("Inactive");
        sensor->setState(Sensor::ACTIVE);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the correct sensor should be thrown
        Assert::assertEquals(Sensor::INACTIVE, sensor->getCommandedState(), __FILE__, __LINE__);
        // Test Active
        m1->setValue("Active");
        sensor->setState(Sensor::INACTIVE);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the correct sensor should be thrown
        Assert::assertEquals(Sensor::ACTIVE, sensor->getCommandedState(), __FILE__, __LINE__);


        // Test reference by local variable addressing
        actionSensor->setStateAddressing(NamedBeanAddressing::Reference);
        actionSensor->setStateReference("{refVariable}");
        // Test Inactive
        _baseMaleSocket->clearLocalVariables();
        _baseMaleSocket->addLocalVariable("refVariable", InitialValueType::String, "Inactive");
        sensor->setState(Sensor::ACTIVE);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the correct sensor should be thrown
        Assert::assertEquals(Sensor::INACTIVE, sensor->getCommandedState(), __FILE__, __LINE__);
        // Test Active
        _baseMaleSocket->clearLocalVariables();
        _baseMaleSocket->addLocalVariable("refVariable", InitialValueType::String, "Active");
        sensor->setState(Sensor::INACTIVE);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the correct sensor should be thrown
        Assert::assertEquals(Sensor::ACTIVE, sensor->getCommandedState(), __FILE__, __LINE__);


        // Test local variable addressing
        actionSensor->setStateAddressing(NamedBeanAddressing::Reference);
        actionSensor->setStateLocalVariable("myVariable");
        // Test Inactive
        _baseMaleSocket->clearLocalVariables();
        _baseMaleSocket->addLocalVariable("refVariable", InitialValueType::String, "Inactive");
        sensor->setState(Sensor::ACTIVE);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the correct sensor should be thrown
        Assert::assertEquals(Sensor::INACTIVE, sensor->getCommandedState(), __FILE__, __LINE__);
        // Test Active
        _baseMaleSocket->clearLocalVariables();
        _baseMaleSocket->addLocalVariable("refVariable", InitialValueType::String, "Active");
        sensor->setState(Sensor::INACTIVE);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the correct sensor should be thrown
        Assert::assertEquals(Sensor::ACTIVE, sensor->getCommandedState(), __FILE__, __LINE__);


        // Test formula addressing
        actionSensor->setStateAddressing(NamedBeanAddressing::Formula);
        actionSensor->setStateFormula("refVariable + myVariable");
        // Test Inactive
        _baseMaleSocket->clearLocalVariables();
        _baseMaleSocket->addLocalVariable("refVariable", InitialValueType::String, "Ina");
        _baseMaleSocket->addLocalVariable("myVariable", InitialValueType::String, "ctive");
        sensor->setState(Sensor::ACTIVE);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the correct sensor should be thrown
        Assert::assertEquals(Sensor::INACTIVE, sensor->getCommandedState(), __FILE__, __LINE__);
        // Test Active
        _baseMaleSocket->clearLocalVariables();
        _baseMaleSocket->addLocalVariable("refVariable", InitialValueType::String, "Act");
        _baseMaleSocket->addLocalVariable("myVariable", InitialValueType::String, "ive");
        sensor->setState(Sensor::INACTIVE);
        // Execute the conditional
        conditionalNG->execute();
        // The action should now be executed so the correct sensor should be thrown
        Assert::assertEquals(Sensor::ACTIVE, sensor->getCommandedState(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ActionSensorTest::testVetoableChange() /*throws PropertyVetoException*/ {
        // Get the action and set the sensor
        Sensor* sensor = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provide("IS1");
        Assert::assertNotNull("Sensor* is not null", sensor, __FILE__, __LINE__);
        ActionSensor* action = new ActionSensor(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->AbstractManager::getAutoSystemName(), "");
        action->setSensor(sensor);

        // Get some other sensor for later use
        Sensor* otherSensor = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provide("IM99");
        Assert::assertNotNull("Sensor* is not null", otherSensor, __FILE__, __LINE__);
        Assert::assertNotEquals("Sensor* is not equal", sensor, otherSensor, __FILE__, __LINE__);

        // Test vetoableChange() for some other propery
        action->vetoableChange(new PropertyChangeEvent(this, "CanSomething", "test", QVariant()));
        Assert::assertEquals("Sensor* matches", sensor, action->getSensor()->getBean(), __FILE__, __LINE__);

        // Test vetoableChange() for a string
        action->vetoableChange(new PropertyChangeEvent(this, "CanDelete", "test", QVariant()));
        Assert::assertEquals("Sensor* matches", sensor, action->getSensor()->getBean(), __FILE__, __LINE__);
        action->vetoableChange(new PropertyChangeEvent(this, "DoDelete", "test", QVariant()));
        Assert::assertEquals("Sensor* matches", sensor, action->getSensor()->getBean(), __FILE__, __LINE__);

        // Test vetoableChange() for another sensor
        action->vetoableChange(new PropertyChangeEvent(this, "CanDelete", VPtr<Sensor>::asQVariant(otherSensor), QVariant()));
        Assert::assertEquals("Sensor* matches", sensor, action->getSensor()->getBean(), __FILE__, __LINE__);
        action->vetoableChange(new PropertyChangeEvent(this, "DoDelete", VPtr<Sensor>::asQVariant(otherSensor), QVariant()));
        Assert::assertEquals("Sensor* matches", sensor, action->getSensor()->getBean(), __FILE__, __LINE__);

        // Test vetoableChange() for its own sensor
        bool thrown = false;
        try {
            action->vetoableChange(new PropertyChangeEvent(this, "CanDelete", VPtr<Sensor>::asQVariant(sensor), QVariant()));
        } catch (PropertyVetoException ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);

        Assert::assertEquals("Sensor* matches", sensor, action->getSensor()->getBean(), __FILE__, __LINE__);
        action->vetoableChange(new PropertyChangeEvent(this, "DoDelete", VPtr<Sensor>::asQVariant(sensor), QVariant()));
        Assert::assertNull("Sensor* is null", action->getSensor(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ActionSensorTest::testCategory() {
        Assert::assertTrue("Category matches", Category::ITEM == _base->getCategory(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ActionSensorTest::testShortDescription() {
        Assert::assertEquals("String matches", "Sensor", _base->getShortDescription(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ActionSensorTest::testLongDescription() {
        Assert::assertEquals("String matches", "Set sensor IS1 to state Active", _base->getLongDescription(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void ActionSensorTest::testChild() {
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
    /*public*/  void ActionSensorTest::setUp() /*throws SocketAlreadyConnectedException */{
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initLogixNGManager();

        _category = Category::ITEM;
        _isExternal = true;

        sensor = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provide("IS1");
        sensor->setCommandedState(Sensor::INACTIVE);
        logixNG = ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A logixNG");
        conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;
        ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->Register(conditionalNG);
        logixNG->addConditionalNG((DefaultConditionalNG*)conditionalNG);
        conditionalNG->setEnabled(true);
        conditionalNG->setRunDelayed(false);
        actionSensor = new ActionSensor(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->AbstractManager::getAutoSystemName(), "");
        actionSensor->setSensor(sensor);
        actionSensor->setBeanState(ActionSensor::SensorState::Active);
        MaleSocket* socket = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(actionSensor);
        conditionalNG->getChild(0)->_connect(socket);

        _base = actionSensor;
        _baseMaleSocket = socket;

        if (! logixNG->setParentForAllChildren(new QList<QString>())) throw new RuntimeException();
        logixNG->setEnabled(true);
    }

    //@After
    /*public*/  void ActionSensorTest::tearDown() {
        // JUnitAppender.clearBacklog();    REMOVE THIS!!!
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }
