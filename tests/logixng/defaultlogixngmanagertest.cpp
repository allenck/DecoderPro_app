#include "defaultlogixngmanagertest.h"
#include "junitutil.h"
#include "assert1.h"
#include "instancemanager.h"
#include "logixng_manager.h"
#include "defaultlogixngmanager.h"
#include "logixng_thread.h"
#include "digitalactionmanager.h"
#include "defaultdigitalactionmanager.h"
#include "conditionalng.h"
#include "digitalmany.h"
#include "ifthenelse.h"
#include "runtimeexception.h"
#include "defaultlogixng.h"
#include "defaultconditionalngmanager.h"
#include "defaultconditionalng.h"
#include "defaultanalogactionmanager.h"
#include "defaultanalogexpressionmanager.h"
#include "defaultdigitalbooleanactionmanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "defaultstringactionmanager.h"
#include "defaultstringexpressionmanager.h"
#include "or.h"
#include "doanalogaction.h"
#include "analogexpressionconstant.h"
#include "defaultanalogactionmanager.h"
#include "defaultdigitalactionmanager.h"
#include "analogmany.h"
#include "dostringaction.h"
#include "stringexpressionconstant.h"
#include "stringmany.h"
#include "logix.h"
#include "digitalbooleanonchange.h"
#include "lastresultofdigitalexpression.h"
#include "abstractdebuggermalesocket.h"

/**
 * Test DefaultLogixNG
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  class DefaultLogixNGManagerTest {

    //@Test
    /*public*/  void DefaultLogixNGManagerTest::testManager() {
        DefaultLogixNGManager* manager = (DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager");

        Assert::assertEquals("getXMLOrder() is correct", Manager::LOGIXNGS, manager->getXMLOrder(), __FILE__, __LINE__);
        Assert::assertEquals("getBeanTypeHandled() is correct", tr("LogixNG"), manager->getBeanTypeHandled(), __FILE__, __LINE__);
        Assert::assertEquals("getSystemPrefix() is correct", "I", manager->AbstractManager::getSystemPrefix(), __FILE__, __LINE__);
        Assert::assertEquals("typeLetter() is correct", 'Q', manager->typeLetter(), __FILE__, __LINE__);

        Assert::assertEquals("bean type is correct", tr("LogixNG"), manager->getBeanTypeHandled(false), __FILE__, __LINE__);
        Assert::assertEquals("bean type is correct", tr("LogixNGs"), manager->getBeanTypeHandled(true), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultLogixNGManagerTest::testValidSystemNameFormat() {
        DefaultLogixNGManager* manager = (DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager");

        Assert::assertEquals("validSystemNameFormat()", Manager::NameValidity::INVALID, manager->validSystemNameFormat(""), __FILE__, __LINE__);
        Assert::assertEquals("validSystemNameFormat()", Manager::NameValidity::INVALID, manager->validSystemNameFormat("IQ"), __FILE__, __LINE__);
        Assert::assertEquals("validSystemNameFormat()", Manager::NameValidity::VALID, manager->validSystemNameFormat("IQ1"), __FILE__, __LINE__);
        Assert::assertEquals("validSystemNameFormat()", Manager::NameValidity::INVALID, manager->validSystemNameFormat("iQ1"), __FILE__, __LINE__);
        Assert::assertEquals("validSystemNameFormat()", Manager::NameValidity::INVALID, manager->validSystemNameFormat("Iq1"), __FILE__, __LINE__);
        Assert::assertEquals("validSystemNameFormat()", Manager::NameValidity::INVALID, manager->validSystemNameFormat("iq1"), __FILE__, __LINE__);
        Assert::assertEquals("validSystemNameFormat()", Manager::NameValidity::VALID, manager->validSystemNameFormat("IQ:AUTO:1"), __FILE__, __LINE__);
        Assert::assertEquals("validSystemNameFormat()", Manager::NameValidity::INVALID, manager->validSystemNameFormat("IQ1A"), __FILE__, __LINE__);
        Assert::assertEquals("validSystemNameFormat()", Manager::NameValidity::INVALID, manager->validSystemNameFormat("IQA"), __FILE__, __LINE__);
        Assert::assertEquals("validSystemNameFormat()", Manager::NameValidity::INVALID, manager->validSystemNameFormat("IQ1 "), __FILE__, __LINE__);
        Assert::assertEquals("validSystemNameFormat()", Manager::NameValidity::VALID, manager->validSystemNameFormat("IQ11111"), __FILE__, __LINE__);
        Assert::assertEquals("validSystemNameFormat()", Manager::NameValidity::INVALID, manager->validSystemNameFormat("IQ1AA"), __FILE__, __LINE__);
        Assert::assertEquals("validSystemNameFormat()", Manager::NameValidity::INVALID, manager->validSystemNameFormat("IQ1X"), __FILE__, __LINE__);
        Assert::assertEquals("validSystemNameFormat()", Manager::NameValidity::INVALID, manager->validSystemNameFormat("IQX1"), __FILE__, __LINE__);
        Assert::assertEquals("validSystemNameFormat()", Manager::NameValidity::INVALID, manager->validSystemNameFormat("IQX1X"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultLogixNGManagerTest::testCreateNewLogixNG() {
    DefaultLogixNGManager* manager = (DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager");

        // Correct system name
        LogixNG* logixNG = manager->createLogixNG("IQ1", "Some name");
        Assert::assertNotNull("exists", logixNG, __FILE__, __LINE__);
        LogixNG* logixNG_2 = manager->getLogixNG("IQ1");
        Assert::assertEquals("logixNGs are the same", logixNG, logixNG_2, __FILE__, __LINE__);
        logixNG_2 = (LogixNG*)manager->getBySystemName("IQ1")->self();
        Assert::assertEquals("logixNGs are the same", logixNG, logixNG_2, __FILE__, __LINE__);
        logixNG_2 = manager->getLogixNG("Some name");
        Assert::assertEquals("logixNGs are the same", logixNG, logixNG_2, __FILE__, __LINE__);
        logixNG_2 = (LogixNG*)manager->getByUserName("Some name")->self();
        Assert::assertEquals("logixNGs are the same", logixNG, logixNG_2, __FILE__, __LINE__);
        logixNG_2 = manager->getLogixNG("Some other name");
        Assert::assertNull("logixNG not found", logixNG_2, __FILE__, __LINE__);

        // Correct system name. Neither system name or user name exists already
        logixNG = manager->createLogixNG("IQ2", "Other LogixNG");
        Assert::assertNotNull("exists", logixNG, __FILE__, __LINE__);

        // System name exists
        logixNG = manager->createLogixNG("IQ1", "Another name");
        Assert::assertNull("cannot create new", logixNG, __FILE__, __LINE__);

        // User name exists
        logixNG = manager->createLogixNG("IQ3", "Other LogixNG");
        Assert::assertNull("cannot create new", logixNG, __FILE__, __LINE__);

        // Bad system name
        bool thrown = false;
        try {
            manager->createLogixNG("IQ4A", "Different name");
        } catch (IllegalArgumentException* ex) {
            thrown = true;
        }
        Assert::assertTrue("Expected exception thrown", thrown, __FILE__, __LINE__);


        // Create LogixNG with user name
        logixNG = manager->createLogixNG("Only user name");
        Assert::assertNotNull("exists", logixNG, __FILE__, __LINE__);
        Assert::assertEquals("user name is correct", "Only user name", logixNG->AbstractNamedBean::getUserName(), __FILE__, __LINE__);

}

    /*public*/  void DefaultLogixNGManagerTest::setupInitialConditionalNGTree(ConditionalNG* conditionalNG) {
        try {
            DefaultDigitalActionManager* digitalActionManager = (DefaultDigitalActionManager*)
                    InstanceManager::getDefault("DigitalActionManager");

            FemaleSocket* femaleSocket = conditionalNG->getFemaleSocket();
            MaleDigitalActionSocket* actionManySocket = ((DefaultDigitalActionManager*)
                    InstanceManager::getDefault("DigitalActionManager"))
                            ->registerAction(new DigitalMany(digitalActionManager->AbstractManager::getAutoSystemName(), nullptr));
            femaleSocket->_connect(actionManySocket);
//            femaleSocket->setLock(Base.Lock.HARD_LOCK);

            QObject* o = (QObject*)actionManySocket;
            //femaleSocket = actionManySocket->getChild(0);
            femaleSocket = ((AbstractDebuggerMaleSocket*)(o))->getChild(0);
            MaleDigitalActionSocket* actionIfThenSocket = (MaleDigitalActionSocket*)((DefaultDigitalActionManager*)
                    InstanceManager::getDefault("DigitalActionManager"))
                            ->registerAction(new IfThenElse(digitalActionManager->AbstractManager::getAutoSystemName(), nullptr));
            femaleSocket->_connect(actionIfThenSocket);
        } catch (SocketAlreadyConnectedException* e) {
            // This should never be able to happen.
            throw new RuntimeException(e->getMessage());
        }
    }

    //@Test
    /*public*/  void DefaultLogixNGManagerTest::testSetupInitialConditionalNGTree() {
        // Correct system name
        LogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))
                ->createLogixNG("IQ1", "Some name");
        Assert::assertNotNull("exists", logixNG, __FILE__, __LINE__);

        ConditionalNG* conditionalNG = (DefaultConditionalNG*)((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))
                ->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
        Assert::assertNotNull("exists", conditionalNG->self(), __FILE__, __LINE__);
        setupInitialConditionalNGTree(conditionalNG);

        FemaleSocket* child = conditionalNG->getChild(0);
        Assert::assertEquals("action is of correct class",
                "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalActionSocket",
                child->getClassName(), __FILE__, __LINE__);
        MaleSocket* maleSocket = child->getConnectedSocket();
        QObject* obj = (QObject*)maleSocket;
        //QString s = ((AbstractMaleSocket*)obj)->getClassName();
        if(static_cast<AbstractDebuggerMaleSocket*>(obj))
         maleSocket = ((AbstractDebuggerMaleSocket*)obj);
        else
         maleSocket = ((AbstractMaleSocket*)obj);
        Assert::assertEquals("action is of correct class",
                "jmri.jmrit.logixng.tools.debugger.DebuggerMaleDigitalActionSocket",
                maleSocket->getClassName(), __FILE__, __LINE__);
        Assert::assertEquals("action is of correct class",
                "Many",
                maleSocket->getLongDescription(), __FILE__, __LINE__);
        MaleSocket* maleSocket2 = maleSocket->getChild(0)->getConnectedSocket();
        Assert::assertEquals("action is of correct class",
                "jmri.jmrit.logixng.tools.debugger.DebuggerMaleDigitalActionSocket",
                maleSocket2->getClassName(), __FILE__, __LINE__);
        Assert::assertEquals("action is of correct class",
                "If Then Else. Execute on change",
                maleSocket2->getLongDescription(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultLogixNGManagerTest::testDeleteLogixNG() /*throws SocketAlreadyConnectedException, PropertyVetoException*/ {
        LogixNG_Manager* logixNG_Manager = (DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager");
        ConditionalNG_Manager* conditionalNG_Manager = (DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager");
        AnalogActionManager* analogActionManager = (DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager");
        AnalogExpressionManager* analogExpressionManager = (DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
        DigitalActionManager* digitalActionManager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        DigitalBooleanActionManager* digitalBooleanActionManager = (DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager");
        DigitalExpressionManager* digitalExpressionManager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        StringActionManager* stringActionManager = (DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager");
        StringExpressionManager* stringExpressionManager = (DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager");

        LogixNG* logixNG = logixNG_Manager->createLogixNG("IQ1", "Some name");
        Assert::assertNotNull("exists", logixNG, __FILE__, __LINE__);

        ConditionalNG* conditionalNG = conditionalNG_Manager
                ->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
        Assert::assertNotNull("exists", conditionalNG->self(), __FILE__, __LINE__);

        FemaleSocket* femaleSocket = conditionalNG->getFemaleSocket();
        MaleDigitalActionSocket* actionManySocket = digitalActionManager
                        ->registerAction(new DigitalMany(digitalActionManager->getAutoSystemName(), nullptr));
        femaleSocket->_connect(actionManySocket);

        femaleSocket = actionManySocket->getChild(0);
        MaleDigitalActionSocket* actionIfThenSocket = digitalActionManager
                        ->registerAction(new IfThenElse(digitalActionManager->getAutoSystemName(), nullptr));
        femaleSocket->_connect(actionIfThenSocket);

        femaleSocket = actionIfThenSocket->getChild(0);
        MaleDigitalExpressionSocket* expressionOrSocket =((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))
                        ->registerExpression(new Or(digitalExpressionManager->getAutoSystemName(), nullptr));
        femaleSocket->_connect(expressionOrSocket);

        femaleSocket = actionManySocket->getChild(1);
        MaleDigitalActionSocket* actionDoAnalogActionSocket = digitalActionManager
                        ->registerAction(new DoAnalogAction(digitalActionManager->getAutoSystemName(), nullptr));
        femaleSocket->_connect(actionDoAnalogActionSocket);

        femaleSocket = actionDoAnalogActionSocket->getChild(0);
        MaleAnalogExpressionSocket* expressionAnalogExpressionConstantSocket =
                analogExpressionManager
                        ->registerExpression(new AnalogExpressionConstant(analogExpressionManager->getAutoSystemName(), nullptr));
        femaleSocket->_connect(expressionAnalogExpressionConstantSocket);

        femaleSocket = actionDoAnalogActionSocket->getChild(1);
        MaleAnalogActionSocket* actionAnalogManySocket = ((DefaultAnalogActionManager*)
                InstanceManager::getDefault("AnalogActionManager"))
                        ->registerAction(new AnalogMany(analogActionManager->getAutoSystemName(), nullptr));
        femaleSocket->_connect(actionAnalogManySocket);

        femaleSocket = actionManySocket->getChild(2);
        MaleDigitalActionSocket* actionDoStringActionSocket = ((DefaultDigitalActionManager*)
                InstanceManager::getDefault("DigitalActionManager"))
                        ->registerAction(new DoStringAction(digitalActionManager->getAutoSystemName(), nullptr));
        femaleSocket->_connect(actionDoStringActionSocket);

        femaleSocket = actionDoStringActionSocket->getChild(0);
        MaleStringExpressionSocket* expressionStringExpressionConstantSocket =
                stringExpressionManager
                        ->registerExpression(new StringExpressionConstant(stringExpressionManager->getAutoSystemName(), nullptr));
        femaleSocket->_connect(expressionStringExpressionConstantSocket);

        femaleSocket = actionDoStringActionSocket->getChild(1);
        MaleStringActionSocket* actionStringManySocket = stringActionManager
                        ->registerAction(new StringMany(stringActionManager->getAutoSystemName(), nullptr));
        femaleSocket->_connect(actionStringManySocket);

        femaleSocket = actionManySocket->getChild(3);
        MaleDigitalActionSocket* logix = (MaleDigitalActionSocket*)digitalActionManager
                        ->registerAction((MaleDigitalActionSocket*)new Logix(digitalActionManager->getAutoSystemName(), nullptr));
        femaleSocket->_connect(logix);

        femaleSocket = logix->getChild(1);
        MaleDigitalBooleanActionSocket* onChange = digitalBooleanActionManager
                        ->registerAction(new DigitalBooleanOnChange(
                                digitalBooleanActionManager->getAutoSystemName(),
                                nullptr,
                                DigitalBooleanOnChange::Trigger::CHANGE));
        femaleSocket->_connect(onChange);


        LastResultOfDigitalExpression* lastResultOfDigitalExpression =
                new LastResultOfDigitalExpression(
                                digitalExpressionManager->getAutoSystemName(), nullptr);
        lastResultOfDigitalExpression->setDigitalExpression(expressionOrSocket);


        Assert::assertNotNull(logixNG_Manager->getBySystemName(logixNG->AbstractNamedBean::getSystemName())->self(), __FILE__, __LINE__);
        Assert::assertNotNull(conditionalNG_Manager->getBySystemName(conditionalNG->NamedBean::getSystemName())->self(), __FILE__, __LINE__);
        Assert::assertNotNull(analogActionManager->getBySystemName(actionAnalogManySocket->NamedBean::getSystemName())->self(), __FILE__, __LINE__);
        Assert::assertNotNull(analogExpressionManager->getBySystemName(expressionAnalogExpressionConstantSocket->NamedBean::getSystemName())->self(), __FILE__, __LINE__);
        Assert::assertNotNull(digitalActionManager->getBySystemName(actionManySocket->NamedBean::getSystemName())->self(), __FILE__, __LINE__);
        Assert::assertNotNull(digitalExpressionManager->getBySystemName(expressionOrSocket->NamedBean::getSystemName())->self(), __FILE__, __LINE__);
        Assert::assertNotNull(stringActionManager->getBySystemName(actionStringManySocket->NamedBean::getSystemName())->self(), __FILE__, __LINE__);
        Assert::assertNotNull(stringExpressionManager->getBySystemName(expressionStringExpressionConstantSocket->NamedBean::getSystemName())->self(), __FILE__, __LINE__);
        Assert::assertNotNull(digitalBooleanActionManager->getBySystemName(onChange->NamedBean::getSystemName())->self(), __FILE__, __LINE__);

        try {
            logixNG_Manager->deleteBean(logixNG, "CanDelete");
        } catch (PropertyVetoException* e) {
            Assert::assertEquals("DoNotDelete", e->getPropertyChangeEvent()->getPropertyName(), __FILE__, __LINE__);
            Assert::assertEquals("Expression is in use by \"IQDE:AUTO:0002\"", e->getMessage(), __FILE__, __LINE__);
        }
        lastResultOfDigitalExpression->removeDigitalExpression();

        try {
            logixNG_Manager->deleteBean(logixNG, "CanDelete");
        } catch (PropertyVetoException* e) {
            Assert::assertEquals("CanDelete", e->getPropertyChangeEvent()->getPropertyName(), __FILE__, __LINE__);
            Assert::assertEquals("", e->getMessage(), __FILE__, __LINE__);
        }
        logixNG_Manager->deleteBean(logixNG, "DoDelete");

        Assert::assertNull(logixNG_Manager->getBySystemName(logixNG->AbstractNamedBean::getSystemName())->self(), __FILE__, __LINE__);
        Assert::assertNull(conditionalNG_Manager->getBySystemName(conditionalNG->Base::getSystemName())->self(), __FILE__, __LINE__);
        Assert::assertNull(analogActionManager->getBySystemName(actionAnalogManySocket->NamedBean::getSystemName())->self(), __FILE__, __LINE__);
        Assert::assertNull(analogExpressionManager->getBySystemName(expressionAnalogExpressionConstantSocket->Base::getSystemName())->self(), __FILE__, __LINE__);
        Assert::assertNull(digitalActionManager->getBySystemName(actionManySocket->Base::getSystemName())->self(), __FILE__, __LINE__);
        Assert::assertNull(digitalExpressionManager->getBySystemName(expressionOrSocket->NamedBean::getSystemName())->self(), __FILE__, __LINE__);
        Assert::assertNull(stringActionManager->getBySystemName(actionStringManySocket->Base::getSystemName())->self(), __FILE__, __LINE__);
        Assert::assertNull(stringExpressionManager->getBySystemName(expressionStringExpressionConstantSocket->Base::getSystemName())->self(), __FILE__, __LINE__);
        Assert::assertNull(digitalBooleanActionManager->getBySystemName(onChange->Base::getSystemName())->self(), __FILE__, __LINE__);

    }
#if 0
    //@Test
    /*public*/  void testDeleteConditionalNG() throws SocketAlreadyConnectedException, PropertyVetoException {
        LogixNG_Manager logixNG_Manager = InstanceManager::getDefault(LogixNG_Manager->class);
        ConditionalNG_Manager conditionalNG_Manager = InstanceManager::getDefault(ConditionalNG_Manager->class);
        AnalogActionManager analogActionManager = InstanceManager::getDefault(AnalogActionManager->class);
        AnalogExpressionManager analogExpressionManager = InstanceManager::getDefault(AnalogExpressionManager->class);
        DigitalActionManager digitalActionManager = InstanceManager::getDefault(DigitalActionManager->class);
        DigitalBooleanActionManager digitalBooleanActionManager = InstanceManager::getDefault(DigitalBooleanActionManager->class);
        DigitalExpressionManager digitalExpressionManager = InstanceManager::getDefault(DigitalExpressionManager->class);
        StringActionManager stringActionManager = InstanceManager::getDefault(StringActionManager->class);
        StringExpressionManager stringExpressionManager = InstanceManager::getDefault(StringExpressionManager->class);

        LogixNG logixNG = logixNG_Manager->createLogixNG("IQ1", "Some name");
        Assert::assertNotNull("exists", logixNG);

        ConditionalNG conditionalNG = conditionalNG_Manager
                .createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
        Assert::assertNotNull("exists", conditionalNG);

        FemaleSocket femaleSocket = conditionalNG.getFemaleSocket();
        MaleDigitalActionSocket actionManySocket = digitalActionManager
                        .registerAction(new DigitalMany(digitalActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(actionManySocket);

        femaleSocket = actionManySocket->getChild(0);
        MaleDigitalActionSocket actionIfThenSocket = digitalActionManager
                        .registerAction(new IfThenElse(digitalActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(actionIfThenSocket);

        femaleSocket = actionIfThenSocket->getChild(0);
        MaleDigitalExpressionSocket expressionOrSocket =
                InstanceManager::getDefault(DigitalExpressionManager->class)
                        .registerExpression(new Or(digitalExpressionManager->getAutoSystemName(), null));
        femaleSocket->_connect(expressionOrSocket);

        femaleSocket = actionManySocket->getChild(1);
        MaleDigitalActionSocket actionDoAnalogActionSocket = digitalActionManager
                        .registerAction(new DoAnalogAction(digitalActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(actionDoAnalogActionSocket);

        femaleSocket = actionDoAnalogActionSocket->getChild(0);
        MaleAnalogExpressionSocket expressionAnalogExpressionConstantSocket =
                analogExpressionManager
                        .registerExpression(new AnalogExpressionConstant(analogExpressionManager->getAutoSystemName(), null));
        femaleSocket->_connect(expressionAnalogExpressionConstantSocket);

        femaleSocket = actionDoAnalogActionSocket->getChild(1);
        MaleAnalogActionSocket actionAnalogManySocket =
                InstanceManager::getDefault(AnalogActionManager->class)
                        .registerAction(new AnalogMany(analogActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(actionAnalogManySocket);

        femaleSocket = actionManySocket->getChild(2);
        MaleDigitalActionSocket actionDoStringActionSocket =
                InstanceManager::getDefault(DigitalActionManager->class)
                        .registerAction(new DoStringAction(digitalActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(actionDoStringActionSocket);

        femaleSocket = actionDoStringActionSocket->getChild(0);
        MaleStringExpressionSocket expressionStringExpressionConstantSocket =
                stringExpressionManager
                        .registerExpression(new StringExpressionConstant(stringExpressionManager->getAutoSystemName(), null));
        femaleSocket->_connect(expressionStringExpressionConstantSocket);

        femaleSocket = actionDoStringActionSocket->getChild(1);
        MaleStringActionSocket actionStringManySocket = stringActionManager
                        .registerAction(new StringMany(stringActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(actionStringManySocket);

        femaleSocket = actionManySocket->getChild(3);
        MaleDigitalActionSocket logix = digitalActionManager
                        .registerAction(new Logix(digitalActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(logix);

        femaleSocket = logix->getChild(1);
        MaleDigitalBooleanActionSocket onChange = digitalBooleanActionManager
                        .registerAction(new DigitalBooleanOnChange(
                                digitalBooleanActionManager->getAutoSystemName(),
                                null,
                                DigitalBooleanOnChange.Trigger.CHANGE));
        femaleSocket->_connect(onChange);


        LastResultOfDigitalExpression lastResultOfDigitalExpression =
                new LastResultOfDigitalExpression(
                                digitalExpressionManager->getAutoSystemName(), null);
        lastResultOfDigitalExpression.setDigitalExpression(expressionOrSocket);


        Assert::assertNotNull(logixNG_Manager->getBySystemName(logixNG->getSystemName()));
        Assert::assertNotNull(conditionalNG_Manager->getBySystemName(conditionalNG->getSystemName()));
        Assert::assertNotNull(analogActionManager->getBySystemName(actionAnalogManySocket->getSystemName()));
        Assert::assertNotNull(analogExpressionManager->getBySystemName(expressionAnalogExpressionConstantSocket->getSystemName()));
        Assert::assertNotNull(digitalActionManager->getBySystemName(actionManySocket->getSystemName()));
        Assert::assertNotNull(digitalExpressionManager->getBySystemName(expressionOrSocket->getSystemName()));
        Assert::assertNotNull(stringActionManager->getBySystemName(actionStringManySocket->getSystemName()));
        Assert::assertNotNull(stringExpressionManager->getBySystemName(expressionStringExpressionConstantSocket->getSystemName()));
        Assert::assertNotNull(digitalBooleanActionManager->getBySystemName(onChange->getSystemName()));

        try {
            conditionalNG_Manager->deleteBean(conditionalNG, "CanDelete");
        } catch (PropertyVetoException e) {
            Assert::assertEquals("DoNotDelete", e.getPropertyChangeEvent().getPropertyName());
            Assert::assertEquals("Expression is in use by \"IQDE:AUTO:0002\"", e.getMessage());
        }
        lastResultOfDigitalExpression.removeDigitalExpression();

        try {
            conditionalNG_Manager->deleteBean(conditionalNG, "CanDelete");
        } catch (PropertyVetoException e) {
            Assert::assertEquals("CanDelete", e.getPropertyChangeEvent().getPropertyName());
            Assert::assertEquals("", e.getMessage());
        }
        conditionalNG_Manager->deleteBean(conditionalNG, "DoDelete");

        Assert::assertNotNull(logixNG_Manager->getBySystemName(logixNG->getSystemName()));
        Assert::assertNull(conditionalNG_Manager->getBySystemName(conditionalNG->getSystemName()));
        Assert::assertNull(analogActionManager->getBySystemName(actionAnalogManySocket->getSystemName()));
        Assert::assertNull(analogExpressionManager->getBySystemName(expressionAnalogExpressionConstantSocket->getSystemName()));
        Assert::assertNull(digitalActionManager->getBySystemName(actionManySocket->getSystemName()));
        Assert::assertNull(digitalExpressionManager->getBySystemName(expressionOrSocket->getSystemName()));
        Assert::assertNull(stringActionManager->getBySystemName(actionStringManySocket->getSystemName()));
        Assert::assertNull(stringExpressionManager->getBySystemName(expressionStringExpressionConstantSocket->getSystemName()));
        Assert::assertNull(digitalBooleanActionManager->getBySystemName(onChange->getSystemName()));
    }

    //@Test
    /*public*/  void testDeleteModule() throws SocketAlreadyConnectedException, PropertyVetoException {
        FemaleSocketManager femaleSocketManager = InstanceManager::getDefault(FemaleSocketManager->class);
        ModuleManager moduleManager = InstanceManager::getDefault(ModuleManager->class);
        AnalogActionManager analogActionManager = InstanceManager::getDefault(AnalogActionManager->class);
        AnalogExpressionManager analogExpressionManager = InstanceManager::getDefault(AnalogExpressionManager->class);
        DigitalActionManager digitalActionManager = InstanceManager::getDefault(DigitalActionManager->class);
        DigitalBooleanActionManager digitalBooleanActionManager = InstanceManager::getDefault(DigitalBooleanActionManager->class);
        DigitalExpressionManager digitalExpressionManager = InstanceManager::getDefault(DigitalExpressionManager->class);
        StringActionManager stringActionManager = InstanceManager::getDefault(StringActionManager->class);
        StringExpressionManager stringExpressionManager = InstanceManager::getDefault(StringExpressionManager->class);

        jmri.jmrit.logixng.Module module = moduleManager
                .createModule("A module", femaleSocketManager->getSocketTypeByType("DefaultFemaleDigitalActionSocket"));  // NOI18N
        Assert::assertNotNull("exists", module);

        FemaleSocket femaleSocket = module.getRootSocket();
        MaleDigitalActionSocket actionManySocket = digitalActionManager
                        .registerAction(new DigitalMany(digitalActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(actionManySocket);

        femaleSocket = actionManySocket->getChild(0);
        MaleDigitalActionSocket actionIfThenSocket = digitalActionManager
                        .registerAction(new IfThenElse(digitalActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(actionIfThenSocket);

        femaleSocket = actionIfThenSocket->getChild(0);
        MaleDigitalExpressionSocket expressionOrSocket =
                InstanceManager::getDefault(DigitalExpressionManager->class)
                        .registerExpression(new Or(digitalExpressionManager->getAutoSystemName(), null));
        femaleSocket->_connect(expressionOrSocket);

        femaleSocket = actionManySocket->getChild(1);
        MaleDigitalActionSocket actionDoAnalogActionSocket = digitalActionManager
                        .registerAction(new DoAnalogAction(digitalActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(actionDoAnalogActionSocket);

        femaleSocket = actionDoAnalogActionSocket->getChild(0);
        MaleAnalogExpressionSocket expressionAnalogExpressionConstantSocket =
                analogExpressionManager
                        .registerExpression(new AnalogExpressionConstant(analogExpressionManager->getAutoSystemName(), null));
        femaleSocket->_connect(expressionAnalogExpressionConstantSocket);

        femaleSocket = actionDoAnalogActionSocket->getChild(1);
        MaleAnalogActionSocket actionAnalogManySocket =
                InstanceManager::getDefault(AnalogActionManager->class)
                        .registerAction(new AnalogMany(analogActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(actionAnalogManySocket);

        femaleSocket = actionManySocket->getChild(2);
        MaleDigitalActionSocket actionDoStringActionSocket =
                InstanceManager::getDefault(DigitalActionManager->class)
                        .registerAction(new DoStringAction(digitalActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(actionDoStringActionSocket);

        femaleSocket = actionDoStringActionSocket->getChild(0);
        MaleStringExpressionSocket expressionStringExpressionConstantSocket =
                stringExpressionManager
                        .registerExpression(new StringExpressionConstant(stringExpressionManager->getAutoSystemName(), null));
        femaleSocket->_connect(expressionStringExpressionConstantSocket);

        femaleSocket = actionDoStringActionSocket->getChild(1);
        MaleStringActionSocket actionStringManySocket = stringActionManager
                        .registerAction(new StringMany(stringActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(actionStringManySocket);

        femaleSocket = actionManySocket->getChild(3);
        MaleDigitalActionSocket logix = digitalActionManager
                        .registerAction(new Logix(digitalActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(logix);

        femaleSocket = logix->getChild(1);
        MaleDigitalBooleanActionSocket onChange = digitalBooleanActionManager
                        .registerAction(new DigitalBooleanOnChange(
                                digitalBooleanActionManager->getAutoSystemName(),
                                null,
                                DigitalBooleanOnChange.Trigger.CHANGE));
        femaleSocket->_connect(onChange);


        LastResultOfDigitalExpression lastResultOfDigitalExpression =
                new LastResultOfDigitalExpression(
                                digitalExpressionManager->getAutoSystemName(), null);
        lastResultOfDigitalExpression.setDigitalExpression(expressionOrSocket);


        Assert::assertNotNull(moduleManager->getBySystemName(module->getSystemName()));
        Assert::assertNotNull(analogActionManager->getBySystemName(actionAnalogManySocket->getSystemName()));
        Assert::assertNotNull(analogExpressionManager->getBySystemName(expressionAnalogExpressionConstantSocket->getSystemName()));
        Assert::assertNotNull(digitalActionManager->getBySystemName(actionManySocket->getSystemName()));
        Assert::assertNotNull(digitalExpressionManager->getBySystemName(expressionOrSocket->getSystemName()));
        Assert::assertNotNull(stringActionManager->getBySystemName(actionStringManySocket->getSystemName()));
        Assert::assertNotNull(stringExpressionManager->getBySystemName(expressionStringExpressionConstantSocket->getSystemName()));
        Assert::assertNotNull(digitalBooleanActionManager->getBySystemName(onChange->getSystemName()));

        try {
            moduleManager->deleteBean(module, "CanDelete");
        } catch (PropertyVetoException e) {
            Assert::assertEquals("DoNotDelete", e.getPropertyChangeEvent().getPropertyName());
            Assert::assertEquals("Expression is in use by \"IQDE:AUTO:0002\"", e.getMessage());
        }
        lastResultOfDigitalExpression.removeDigitalExpression();

        try {
            moduleManager->deleteBean(module, "CanDelete");
        } catch (PropertyVetoException e) {
            Assert::assertEquals("CanDelete", e.getPropertyChangeEvent().getPropertyName());
            Assert::assertEquals("", e.getMessage());
        }
        moduleManager->deleteBean(module, "DoDelete");

        Assert::assertNull(moduleManager->getBySystemName(module->getSystemName()));
        Assert::assertNull(analogActionManager->getBySystemName(actionAnalogManySocket->getSystemName()));
        Assert::assertNull(analogExpressionManager->getBySystemName(expressionAnalogExpressionConstantSocket->getSystemName()));
        Assert::assertNull(digitalActionManager->getBySystemName(actionManySocket->getSystemName()));
        Assert::assertNull(digitalExpressionManager->getBySystemName(expressionOrSocket->getSystemName()));
        Assert::assertNull(stringActionManager->getBySystemName(actionStringManySocket->getSystemName()));
        Assert::assertNull(stringExpressionManager->getBySystemName(expressionStringExpressionConstantSocket->getSystemName()));
        Assert::assertNull(digitalBooleanActionManager->getBySystemName(onChange->getSystemName()));
    }

    //@Test
    /*public*/  void testDeleteAction() throws SocketAlreadyConnectedException, PropertyVetoException {
//        LogixNG_Manager logixNG_Manager = InstanceManager::getDefault(LogixNG_Manager->class);
//        ConditionalNG_Manager conditionalNG_Manager = InstanceManager::getDefault(ConditionalNG_Manager->class);
        AnalogActionManager analogActionManager = InstanceManager::getDefault(AnalogActionManager->class);
        AnalogExpressionManager analogExpressionManager = InstanceManager::getDefault(AnalogExpressionManager->class);
        DigitalActionManager digitalActionManager = InstanceManager::getDefault(DigitalActionManager->class);
        DigitalBooleanActionManager digitalBooleanActionManager = InstanceManager::getDefault(DigitalBooleanActionManager->class);
        DigitalExpressionManager digitalExpressionManager = InstanceManager::getDefault(DigitalExpressionManager->class);
        StringActionManager stringActionManager = InstanceManager::getDefault(StringActionManager->class);
        StringExpressionManager stringExpressionManager = InstanceManager::getDefault(StringExpressionManager->class);

//        LogixNG logixNG = logixNG_Manager->createLogixNG("IQ1", "Some name");
//        Assert::assertNotNull("exists", logixNG);

//        ConditionalNG conditionalNG = conditionalNG_Manager
//                .createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
//        Assert::assertNotNull("exists", conditionalNG);

//        FemaleSocket femaleSocket = conditionalNG.getFemaleSocket();
        MaleDigitalActionSocket actionManySocket = digitalActionManager
                        .registerAction(new DigitalMany(digitalActionManager->getAutoSystemName(), null));
//        femaleSocket->_connect(actionManySocket);

        FemaleSocket femaleSocket = actionManySocket->getChild(0);
        MaleDigitalActionSocket actionIfThenSocket = digitalActionManager
                        .registerAction(new IfThenElse(digitalActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(actionIfThenSocket);

        femaleSocket = actionIfThenSocket->getChild(0);
        MaleDigitalExpressionSocket expressionOrSocket =
                InstanceManager::getDefault(DigitalExpressionManager->class)
                        .registerExpression(new Or(digitalExpressionManager->getAutoSystemName(), null));
        femaleSocket->_connect(expressionOrSocket);

        femaleSocket = actionManySocket->getChild(1);
        MaleDigitalActionSocket actionDoAnalogActionSocket = digitalActionManager
                        .registerAction(new DoAnalogAction(digitalActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(actionDoAnalogActionSocket);

        femaleSocket = actionDoAnalogActionSocket->getChild(0);
        MaleAnalogExpressionSocket expressionAnalogExpressionConstantSocket =
                analogExpressionManager
                        .registerExpression(new AnalogExpressionConstant(analogExpressionManager->getAutoSystemName(), null));
        femaleSocket->_connect(expressionAnalogExpressionConstantSocket);

        femaleSocket = actionDoAnalogActionSocket->getChild(1);
        MaleAnalogActionSocket actionAnalogManySocket =
                InstanceManager::getDefault(AnalogActionManager->class)
                        .registerAction(new AnalogMany(analogActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(actionAnalogManySocket);

        femaleSocket = actionManySocket->getChild(2);
        MaleDigitalActionSocket actionDoStringActionSocket =
                InstanceManager::getDefault(DigitalActionManager->class)
                        .registerAction(new DoStringAction(digitalActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(actionDoStringActionSocket);

        femaleSocket = actionDoStringActionSocket->getChild(0);
        MaleStringExpressionSocket expressionStringExpressionConstantSocket =
                stringExpressionManager
                        .registerExpression(new StringExpressionConstant(stringExpressionManager->getAutoSystemName(), null));
        femaleSocket->_connect(expressionStringExpressionConstantSocket);

        femaleSocket = actionDoStringActionSocket->getChild(1);
        MaleStringActionSocket actionStringManySocket = stringActionManager
                        .registerAction(new StringMany(stringActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(actionStringManySocket);

        femaleSocket = actionManySocket->getChild(3);
        MaleDigitalActionSocket logix = digitalActionManager
                        .registerAction(new Logix(digitalActionManager->getAutoSystemName(), null));
        femaleSocket->_connect(logix);

        femaleSocket = logix->getChild(1);
        MaleDigitalBooleanActionSocket onChange = digitalBooleanActionManager
                        .registerAction(new DigitalBooleanOnChange(
                                digitalBooleanActionManager->getAutoSystemName(),
                                null,
                                DigitalBooleanOnChange.Trigger.CHANGE));
        femaleSocket->_connect(onChange);


        LastResultOfDigitalExpression lastResultOfDigitalExpression =
                new LastResultOfDigitalExpression(
                                digitalExpressionManager->getAutoSystemName(), null);
        lastResultOfDigitalExpression.setDigitalExpression(expressionOrSocket);


//        Assert::assertNotNull(logixNG_Manager->getBySystemName(logixNG->getSystemName()));
//        Assert::assertNotNull(conditionalNG_Manager->getBySystemName(conditionalNG->getSystemName()));
        Assert::assertNotNull(analogActionManager->getBySystemName(actionAnalogManySocket->getSystemName()));
        Assert::assertNotNull(analogExpressionManager->getBySystemName(expressionAnalogExpressionConstantSocket->getSystemName()));
        Assert::assertNotNull(digitalActionManager->getBySystemName(actionManySocket->getSystemName()));
        Assert::assertNotNull(digitalExpressionManager->getBySystemName(expressionOrSocket->getSystemName()));
        Assert::assertNotNull(stringActionManager->getBySystemName(actionStringManySocket->getSystemName()));
        Assert::assertNotNull(stringExpressionManager->getBySystemName(expressionStringExpressionConstantSocket->getSystemName()));
        Assert::assertNotNull(digitalBooleanActionManager->getBySystemName(onChange->getSystemName()));

        try {
            digitalActionManager->deleteBean(actionManySocket, "CanDelete");
        } catch (PropertyVetoException e) {
            Assert::assertEquals("DoNotDelete", e.getPropertyChangeEvent().getPropertyName());
            Assert::assertEquals("Expression is in use by \"IQDE:AUTO:0002\"", e.getMessage());
        }
        lastResultOfDigitalExpression.removeDigitalExpression();

        try {
            digitalActionManager->deleteBean(actionManySocket, "CanDelete");
        } catch (PropertyVetoException e) {
            Assert::assertEquals("CanDelete", e.getPropertyChangeEvent().getPropertyName());
            Assert::assertEquals("", e.getMessage());
        }
        digitalActionManager->deleteBean(actionManySocket, "DoDelete");

//        Assert::assertNotNull(logixNG_Manager->getBySystemName(logixNG->getSystemName()));
//        Assert::assertNull(conditionalNG_Manager->getBySystemName(conditionalNG->getSystemName()));
        Assert::assertNull(analogActionManager->getBySystemName(actionAnalogManySocket->getSystemName()));
        Assert::assertNull(analogExpressionManager->getBySystemName(expressionAnalogExpressionConstantSocket->getSystemName()));
        Assert::assertNull(digitalActionManager->getBySystemName(actionManySocket->getSystemName()));
        Assert::assertNull(digitalExpressionManager->getBySystemName(expressionOrSocket->getSystemName()));
        Assert::assertNull(stringActionManager->getBySystemName(actionStringManySocket->getSystemName()));
        Assert::assertNull(stringExpressionManager->getBySystemName(expressionStringExpressionConstantSocket->getSystemName()));
        Assert::assertNull(digitalBooleanActionManager->getBySystemName(onChange->getSystemName()));
    }

    //@Test
    /*public*/  void testDeleteTable() throws SocketAlreadyConnectedException {
//        Assert::fail("Not implemented yet");
    }

#endif
    // The minimal setup for log4J
    //@BeforeEach
    /*public*/  void DefaultLogixNGManagerTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();
    }

    //@AfterEach
    /*public*/  void DefaultLogixNGManagerTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }
