#include "actionsensorswingtest.h"
#include "abstractsensormanager.h"
#include "actionsensor.h"
#include "defaultconditionalngmanager.h"
#include "defaultdigitalactionmanager.h"
#include "defaultlogixngmanager.h"
#include "defaultlogixngpreferences.h"
#include "jpanel.h"
#include "junitutil.h"
#include "instancemanager.h"
#include "assert1.h"
#include "actionsensorswing.h"
#include "jframeoperator.h"
#include "logixng_thread.h"

ActionSensorSwingTest::ActionSensorSwingTest(QObject *parent)
    : SwingConfiguratorInterfaceTestBase(parent)
{

}

/**
 * Test ActionSensorSwing
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/ class ActionSensorSwingTest extends SwingConfiguratorInterfaceTestBase {

    //@Test
    /*public*/ void ActionSensorSwingTest::testCtor() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());

    ActionSensorSwingTest* t = new ActionSensorSwingTest();
        Assert::assertNotNull("exists",t, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ActionSensorSwingTest::testCreatePanel() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());

        Assert::assertTrue("panel is not null",
                           nullptr != (new ActionSensorSwing())->getConfigPanel(new JPanel()), __FILE__, __LINE__);
        Assert::assertTrue("panel is not null",
                           nullptr != (new ActionSensorSwing())->getConfigPanel(new ActionSensor("IQDA1", ""), new JPanel()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ActionSensorSwingTest::testDialogUseExistingSensor() /*throws SocketAlreadyConnectedException*/ {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());

        Sensor* s1 = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provide("IS1");
        ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provide("IS2");

        LogixNG* logixNG = ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))
                ->createLogixNG("A logixNG with an empty conditionlNG");
        DefaultConditionalNG* conditionalNG = (DefaultConditionalNG*)((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "IQC1", "")->bself();

        ActionSensor* action = new ActionSensor("IQDA1", "");
        MaleSocket* maleSocket = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
        conditionalNG->getChild(0)->_connect(maleSocket);

        JDialogOperator* jdo = editItem(conditionalNG, "Edit ConditionalNG IQC1", "Edit ! ", 0);

        (new JComboBoxOperator(jdo, 0))->setSelectedItem(s1->getDisplayName());
        (new JComboBoxOperator(jdo, 1))->setSelectedItem(ActionSensor::SensorState::toString(ActionSensor::SensorState::Inactive));
        (new JButtonOperator(jdo, "OK"))->push();  // NOI18N

//        JUnitUtil::waitFor(() -> {return action->getSensor() != nullptr;});
        JUnitUtil::waitFor(new SensorWait(action));

        Assert::assertEquals("IS1", action->getSensor()->getBean()->getSystemName(), __FILE__, __LINE__);
        Assert::assertEquals(ActionSensor::SensorState::Inactive, action->getBeanState(), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/ void ActionSensorSwingTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalSensorManager();
        ((DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->setShowSystemUserNames(true);
        JUnitUtil::initLogixNGManager();
    }

    //@After
    /*public*/ void ActionSensorSwingTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }
