#include "digitalbooleanonchangetest.h"
#include "digitalbooleanonchange.h"
#include "instancemanager.h"
#include "assert1.h"
#include "junitutil.h"
#include "conditionalng.h"
#include "digitalactionbean.h"
#include "digitalmany.h"
#include "defaultdigitalactionmanager.h"
#include "digitalbooleanonchange.h"
#include "actionmemory.h"
#include "turnout.h"
#include "actionturnout.h"
#include "defaultlogixngpreferences.h"
#include "defaultlogixngmanager.h"
#include "defaultconditionalngscaffold.h"
#include "defaultconditionalngmanager.h"
#include "logixng/logix.h"
#include "expressionsensor.h"
#include "junitappender.h"
#include "defaultdigitalexpressionmanager.h"
#include "defaultdigitalbooleanactionmanager.h"
#include "logixng_thread.h"

/**
 * Test OnChange
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  class DigitalBooleanOnChangeTest extends AbstractDigitalBooleanActionTestBase {


    //@Override
    /*public*/  ConditionalNG* DigitalBooleanOnChangeTest::getConditionalNG() {
        return conditionalNG;
    }

    //@Override
    /*public*/  LogixNG* DigitalBooleanOnChangeTest::getLogixNG() {
        return logixNG;
    }

    //@Override
    /*public*/  MaleSocket* DigitalBooleanOnChangeTest::getConnectableChild() {
        DigitalActionBean* childAction =
                new DigitalMany("IQDA999", "");
        MaleSocket* maleSocketChild = ((DefaultDigitalActionManager*)
                InstanceManager::getDefault("DigitalActionManager"))->registerAction(childAction);
        return maleSocketChild;
    }

    //@Override
    /*public*/  NamedBean* DigitalBooleanOnChangeTest::createNewBean(QString systemName) {
        return new DigitalBooleanOnChange(systemName, "", DigitalBooleanOnChange::Trigger::CHANGE);
    }

    //@Override
    /*public*/  QString DigitalBooleanOnChangeTest::getExpectedPrintedTree() {
        return QString(
                "On change to true ::: Use default%1" \
                "   ! A%2" \
                "      Set turnout '' to state Thrown ::: Use default%3");
    }

    //@Override
    /*public*/  QString DigitalBooleanOnChangeTest::getExpectedPrintedTreeFromRoot() {
        return QString(
                "LogixNG: A new logix for test%1" \
                "   ConditionalNG: A conditionalNG%2" \
                "      ! A%3" \
                "         Logix ::: Use default%4" \
                "            ? E%5" \
                "               Sensor '' is Active ::: Use default%6" \
                "            !b A%7" \
                "               On change to true ::: Use default%8" \
                "                  ! A%9" \
                "                     Set turnout '' to state Thrown ::: Use default%n");
    }

    //@Override
    /*public*/  bool DigitalBooleanOnChangeTest::addNewSocket() {
        return false;
    }

    //@Test
    /*public*/  void DigitalBooleanOnChangeTest::testCtor() {
        DigitalBooleanActionBean* t = new DigitalBooleanOnChange("IQDB321", "", DigitalBooleanOnChange::DigitalBooleanOnChange::Trigger::CHANGE);
        Assert::assertNotNull("exists",t->bself(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DigitalBooleanOnChangeTest::testCtorAndSetup1() {
        DigitalBooleanOnChange* action = new DigitalBooleanOnChange("IQDB321", "", DigitalBooleanOnChange::DigitalBooleanOnChange::Trigger::CHANGE);
        Assert::assertNotNull("exists", action, __FILE__, __LINE__);
        Assert::assertEquals("action has 1 female socket", 1, action->getChildCount(), __FILE__, __LINE__);
        action->getChild(0)->setName("ZH12");
        action->setActionSocketSystemName("IQDA554");

        Assert::assertEquals("action female socket name is ZH12",
                "ZH12", action->getChild(0)->getName(), __FILE__, __LINE__);
        Assert::assertEquals("action female socket is of correct class",
                "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalActionSocket",
                action->getChild(0)->getClassName(), __FILE__, __LINE__);
        Assert::assertFalse("action female socket is not connected",
                action->getChild(0)->isConnected(), __FILE__, __LINE__);

        // Setup action-> This connects the child actions to this action
        action->setup();

        JUnitAppender::assertMessage("cannot load digital action IQDA554", __FILE__, __LINE__);

        Assert::assertEquals("action female socket name is ZH12",
                "ZH12", action->getChild(0)->getName(), __FILE__, __LINE__);
        Assert::assertEquals("action female socket is of correct class",
                "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalActionSocket",
                action->getChild(0)->getClassName(), __FILE__, __LINE__);
        Assert::assertFalse("action female socket is not connected",
                action->getChild(0)->isConnected(), __FILE__, __LINE__);

        Assert::assertEquals("action has 1 female socket", 1, action->getChildCount(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DigitalBooleanOnChangeTest::testCtorAndSetup2() {
        DigitalBooleanOnChange* action = new DigitalBooleanOnChange("IQDB321", "", DigitalBooleanOnChange::Trigger::CHANGE);
        Assert::assertNotNull("exists", action, __FILE__, __LINE__);
        Assert::assertEquals("action has 1 female socket", 1, action->getChildCount(), __FILE__, __LINE__);
        action->getChild(0)->setName("ZH12");
        action->setActionSocketSystemName("");

        Assert::assertEquals("action female socket name is ZH12",
                "ZH12", action->getChild(0)->getName(), __FILE__, __LINE__);
        Assert::assertEquals("action female socket is of correct class",
                "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalActionSocket",
                action->getChild(0)->getClassName(), __FILE__, __LINE__);
        Assert::assertFalse("action female socket is not connected",
                action->getChild(0)->isConnected(), __FILE__, __LINE__);

        // Setup action-> This connects the child actions to this action
        action->setup();

        Assert::assertEquals("action female socket name is ZH12",
                "ZH12", action->getChild(0)->getName(), __FILE__, __LINE__);
        Assert::assertEquals("action female socket is of correct class",
                "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalActionSocket",
                action->getChild(0)->getClassName(), __FILE__, __LINE__);
        Assert::assertFalse("action female socket is not connected",
                action->getChild(0)->isConnected(), __FILE__, __LINE__);

        Assert::assertEquals("action has 1 female socket", 1, action->getChildCount(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DigitalBooleanOnChangeTest::testCtorAndSetup3() {
        DigitalActionManager* m1 = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");

        MaleSocket* childSocket0 = m1->registerAction(new ActionMemory("IQDA554", ""));

        DigitalBooleanOnChange* action = new DigitalBooleanOnChange("IQDB321", "", DigitalBooleanOnChange::DigitalBooleanOnChange::Trigger::CHANGE);
        Assert::assertNotNull("exists", action, __FILE__, __LINE__);
        Assert::assertEquals("action has 1 female socket", 1, action->getChildCount(), __FILE__, __LINE__);
        action->getChild(0)->setName("ZH12");
        action->setActionSocketSystemName("IQDA554");

        Assert::assertEquals("action female socket name is ZH12",
                "ZH12", action->getChild(0)->getName(), __FILE__, __LINE__);
        Assert::assertEquals("action female socket is of correct class",
                "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalActionSocket",
                action->getChild(0)->getClassName(), __FILE__, __LINE__);
        Assert::assertFalse("action female socket is not connected",
                action->getChild(0)->isConnected(), __FILE__, __LINE__);

        // Setup action-> This connects the child actions to this action
        action->setup();

        Assert::assertTrue("action female socket is connected",
                action->getChild(0)->isConnected(), __FILE__, __LINE__);
        Assert::assertEquals("child is correct bean",
                childSocket0,
                action->getChild(0)->getConnectedSocket(), __FILE__, __LINE__);

        Assert::assertEquals("action has 1 female sockets", 1, action->getChildCount(), __FILE__, __LINE__);

        // Try run setup() again. That should not cause any problems.
        action->setup();

        Assert::assertEquals("action has 1 female sockets", 1, action->getChildCount(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DigitalBooleanOnChangeTest::testGetChild() {
        Assert::assertTrue("getChildCount() returns 1", 1 == _actionOnChange->getChildCount(), __FILE__, __LINE__);

        Assert::assertNotNull("getChild(0) returns a non null value",
                _actionOnChange->getChild(0)->bself(), __FILE__, __LINE__);

        bool hasThrown = false;
        try {
            _actionOnChange->getChild(1);
        } catch (IllegalArgumentException* ex) {
            hasThrown = true;
            Assert::assertEquals("Error message is correct", "index has invalid value: 1", ex->getMessage(), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception is thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DigitalBooleanOnChangeTest::testCategory() {
        Assert::assertTrue("Category matches", Category::COMMON == _base->getCategory(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DigitalBooleanOnChangeTest::testGetShortDescription() {
        DigitalBooleanActionBean* a1 = new DigitalBooleanOnChange("IQDB321", "", DigitalBooleanOnChange::DigitalBooleanOnChange::Trigger::CHANGE_TO_TRUE);
        Assert::assertEquals("strings are equal", "On change", a1->getShortDescription(), __FILE__, __LINE__);
        DigitalBooleanActionBean* a2 = new DigitalBooleanOnChange("IQDB322", "", DigitalBooleanOnChange::DigitalBooleanOnChange::Trigger::CHANGE_TO_FALSE);
        Assert::assertEquals("strings are equal", "On change", a2->getShortDescription(), __FILE__, __LINE__);
        DigitalBooleanActionBean* a3 = new DigitalBooleanOnChange("IQDB323", "", DigitalBooleanOnChange::DigitalBooleanOnChange::Trigger::CHANGE);
        Assert::assertEquals("strings are equal", "On change", a3->getShortDescription(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void testGetLongDescription() {
        DigitalBooleanActionBean* a1 = new DigitalBooleanOnChange("IQDB321", "", DigitalBooleanOnChange::DigitalBooleanOnChange::Trigger::CHANGE_TO_TRUE);
        Assert::assertEquals("strings are equal", "On change to true", a1->getLongDescription(), __FILE__, __LINE__);
        DigitalBooleanActionBean* a2 = new DigitalBooleanOnChange("IQDB322", "", DigitalBooleanOnChange::DigitalBooleanOnChange::Trigger::CHANGE_TO_FALSE);
        Assert::assertEquals("strings are equal", "On change to false", a2->getLongDescription(), __FILE__, __LINE__);
        DigitalBooleanActionBean* a3 = new DigitalBooleanOnChange("IQDB323", "", DigitalBooleanOnChange::DigitalBooleanOnChange::Trigger::CHANGE);
        Assert::assertEquals("strings are equal", "On change", a3->getLongDescription(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DigitalBooleanOnChangeTest::testTrigger() {
        _actionOnChange->setTrigger(DigitalBooleanOnChange::Trigger::CHANGE);
        Assert::assertEquals(DigitalBooleanOnChange::Trigger::CHANGE, _actionOnChange->getTrigger(), __FILE__, __LINE__);

        _actionOnChange->setTrigger(DigitalBooleanOnChange::Trigger::CHANGE_TO_FALSE);
        Assert::assertEquals(DigitalBooleanOnChange::DigitalBooleanOnChange::Trigger::CHANGE_TO_FALSE, _actionOnChange->getTrigger(), __FILE__, __LINE__);

        _actionOnChange->setTrigger(DigitalBooleanOnChange::DigitalBooleanOnChange::Trigger::CHANGE_TO_TRUE);
        Assert::assertEquals(DigitalBooleanOnChange::Trigger::CHANGE_TO_TRUE, _actionOnChange->getTrigger(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DigitalBooleanOnChangeTest::testExecute() /*throws JmriException*/ {

        Turnout* turnout = ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provide("IT1");
        _actionTurnout->setTurnout(turnout);
        _actionTurnout->setBeanState(ActionTurnout::TurnoutState::Thrown);

        // Ensure last execute is false
        _actionOnChange->execute(false, false);

        // Test DigitalBooleanOnChange::Trigger::CHANGE
        _actionOnChange->setTrigger(DigitalBooleanOnChange::Trigger::CHANGE);
        turnout->setState(Turnout::CLOSED);
        _actionOnChange->execute(true, false);
        Assert::assertEquals(Turnout::THROWN, turnout->getState(), __FILE__, __LINE__);
        turnout->setState(Turnout::CLOSED);
        _actionOnChange->execute(false, false);
        Assert::assertEquals(Turnout::THROWN, turnout->getState(), __FILE__, __LINE__);
        turnout->setState(Turnout::CLOSED);
        _actionOnChange->execute(true, false);
        Assert::assertEquals(Turnout::THROWN, turnout->getState(), __FILE__, __LINE__);

        // Ensure last execute is false
        _actionOnChange->execute(false, false);

        // Test DigitalBooleanOnChange::Trigger::CHANGE_TO_FALSE
        _actionOnChange->setTrigger(DigitalBooleanOnChange::Trigger::CHANGE_TO_FALSE);
        turnout->setState(Turnout::CLOSED);
        _actionOnChange->execute(true, false);
        Assert::assertEquals(Turnout::CLOSED, turnout->getState(), __FILE__, __LINE__);
        turnout->setState(Turnout::CLOSED);
        _actionOnChange->execute(false, true);
        Assert::assertEquals(Turnout::THROWN, turnout->getState(), __FILE__, __LINE__);
        turnout->setState(Turnout::CLOSED);
        _actionOnChange->execute(true, false);
        Assert::assertEquals(Turnout::CLOSED, turnout->getState(), __FILE__, __LINE__);

        // Ensure last execute is false
        _actionOnChange->execute(false, false);

        // Test DigitalBooleanOnChange::Trigger::CHANGE_TO_TRUE
        _actionOnChange->setTrigger(DigitalBooleanOnChange::Trigger::CHANGE_TO_TRUE);
        turnout->setState(Turnout::CLOSED);
        _actionOnChange->execute(true, false);
        Assert::assertEquals(Turnout::THROWN, turnout->getState(), __FILE__, __LINE__);
        turnout->setState(Turnout::CLOSED);
        _actionOnChange->execute(false, false);
        Assert::assertEquals(Turnout::CLOSED, turnout->getState(), __FILE__, __LINE__);
        turnout->setState(Turnout::CLOSED);
        _actionOnChange->execute(true, false);
        Assert::assertEquals(Turnout::THROWN, turnout->getState(), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void DigitalBooleanOnChangeTest::setUp() /*throws SocketAlreadyConnectedException*/ {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();

        ((DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->setInstallDebugger(false);
        JUnitUtil::initLogixNGManager();

        _category = Category::COMMON;
        _isExternal = false;

        logixNG = ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;
        ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->Register((NamedBean*)conditionalNG->self());
        conditionalNG->setEnabled(true);
        conditionalNG->setRunDelayed(false);
        logixNG->addConditionalNG(conditionalNG);
        Logix* action = new Logix("IQDA321", "");
        MaleSocket* maleSocket = (MaleSocket*)((DefaultDigitalActionManager*)
                InstanceManager::getDefault("DigitalActionManager"))->registerAction(action)->self();
        conditionalNG->getChild(0)->_connect(maleSocket);

        ExpressionSensor* expressionSensor = new ExpressionSensor("IQDE321", "");
        MaleSocket* maleSocket2 =((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expressionSensor);
        action->getChild(0)->_connect(maleSocket2);

        _actionOnChange = new DigitalBooleanOnChange("IQDB322", "", DigitalBooleanOnChange::DigitalBooleanOnChange::Trigger::CHANGE_TO_TRUE);
        MaleSocket* maleSocketActionOnChange =((DefaultDigitalBooleanActionManager*)
                InstanceManager::getDefault("DigitalBooleanActionManager"))->registerAction(_actionOnChange);
        action->getChild(1)->_connect(maleSocketActionOnChange);

        _actionTurnout = new ActionTurnout("IQDA322", "");
        maleSocket2 = (MaleSocket*)((DefaultDigitalActionManager*)
                InstanceManager::getDefault("DigitalActionManager"))->registerAction(_actionTurnout)->bself();
        _actionOnChange->getChild(0)->_connect(maleSocket2);

        _base = _actionOnChange;
        _baseMaleSocket = maleSocketActionOnChange;

        if (! logixNG->setParentForAllChildren(QList<QString>())) throw new RuntimeException();
        logixNG->setEnabled(true);
    }

    //@After
    /*public*/  void DigitalBooleanOnChangeTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }
