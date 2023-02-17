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
#include "logix_emulator.h"
#include "digitalbooleanonchange.h"
#include "lastresultofdigitalexpression.h"
#include "abstractdebuggermalesocket.h"
#include "defaultmaledigitalactionsocket.h"
#include "defaultlogixng.h"
#include "defaultmaleanalogactionsocket.h"
#include "defaultmaleanalogexpressionsocket.h"
#include "defaultmalestringactionsocket.h"
#include "defaultmaledigitalbooleanactionsocket.h"
#include "debuggermaledigitalactionsocket.h"
#include "actions/act_logix.h"
#include "defaultfemalesocketmanager.h"
#include "defaultmodulemanager.h"

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
    Assert::assertNotNull("exists", logixNG?logixNG->self():nullptr, __FILE__, __LINE__);
    LogixNG* logixNG_2 = manager->getLogixNG("IQ1");
    Assert::assertEquals("logixNGs are the same", logixNG, logixNG_2, __FILE__, __LINE__);
    logixNG_2 = (LogixNG*)manager->getBySystemName("IQ1")->self();
    Assert::assertEquals("logixNGs are the same", logixNG, logixNG_2, __FILE__, __LINE__);
    logixNG_2 = manager->getLogixNG("Some name");
    Assert::assertEquals("logixNGs are the same", logixNG, logixNG_2, __FILE__, __LINE__);
    logixNG_2 = (LogixNG*)manager->getByUserName("Some name")->self();
    Assert::assertEquals("logixNGs are the same", logixNG, logixNG_2, __FILE__, __LINE__);
    logixNG_2 = manager->getLogixNG("Some other name");
    Assert::assertNull("logixNG not found", logixNG_2?logixNG_2->self():nullptr, __FILE__, __LINE__);

    // Correct system name. Neither system name or user name exists already
    logixNG = manager->createLogixNG("IQ2", "Other LogixNG");
    Assert::assertNotNull("exists", logixNG?logixNG->self():nullptr, __FILE__, __LINE__);

    // System name exists
    logixNG = manager->createLogixNG("IQ1", "Another name");
    Assert::assertNull("cannot create new", logixNG?logixNG->self():nullptr, __FILE__, __LINE__);

    // User name exists
    logixNG = manager->createLogixNG("IQ3", "Other LogixNG");
    Assert::assertNull("cannot create new", logixNG?logixNG->self():nullptr, __FILE__, __LINE__);

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
    Assert::assertNotNull("exists", logixNG?logixNG->self():nullptr, __FILE__, __LINE__);
    Assert::assertEquals("user name is correct", "Only user name", ((DefaultLogixNG*)logixNG)->AbstractNamedBean::getUserName(), __FILE__, __LINE__);

}

/*public*/  void DefaultLogixNGManagerTest::setupInitialConditionalNGTree(ConditionalNG* conditionalNG) {
    try {
      DigitalActionManager* digitalActionManager = (DefaultDigitalActionManager*)
              InstanceManager::getDefault("DigitalActionManager");

      FemaleSocket* femaleSocket = conditionalNG->getFemaleSocket();
      MaleDigitalActionSocket* actionManySocket = ((DefaultDigitalActionManager*)
              InstanceManager::getDefault("DigitalActionManager"))
                      ->registerAction(new DigitalMany(digitalActionManager->getAutoSystemName(), ""));
      femaleSocket->_connect(actionManySocket);
//            femaleSocket.setLock(Base.Lock.HARD_LOCK);

      femaleSocket = actionManySocket->getChild(0);
      MaleDigitalActionSocket* actionIfThenSocket = ((DefaultDigitalActionManager*)
              InstanceManager::getDefault("DigitalActionManager"))
                      ->registerAction(new IfThenElse(digitalActionManager->getAutoSystemName(), ""));
      femaleSocket->_connect(actionIfThenSocket);
  } catch (SocketAlreadyConnectedException* e) {
      // This should never be able to happen.
      throw new RuntimeException(e);
  }
}

//@Test
/*public*/  void DefaultLogixNGManagerTest::testSetupInitialConditionalNGTree() {
    // Correct system name
    DefaultLogixNG* logixNG = (DefaultLogixNG*)((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))
            ->createLogixNG("IQ1", "Some name");
    Assert::assertNotNull("exists", logixNG?logixNG->self():nullptr, __FILE__, __LINE__);

    DefaultConditionalNG* conditionalNG = (DefaultConditionalNG*)((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))
            ->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
    Assert::assertNotNull("exists", conditionalNG?conditionalNG->self():nullptr, __FILE__, __LINE__);
    setupInitialConditionalNGTree(conditionalNG);

    FemaleSocket* child = conditionalNG->getChild(0);
    Assert::assertEquals("action is of correct class",
            "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalActionSocket",
            child->getClassName(), __FILE__, __LINE__);
    MaleSocket* maleSocket = child->getConnectedSocket();
    QString s = ((AbstractMaleSocket*)maleSocket->bself())->getClassName();
    Assert::assertEquals("action is of correct class",
            "jmri.jmrit.logixng.tools.debugger.DebuggerMaleDigitalActionSocket",
            ((AbstractMaleSocket*)maleSocket->bself())->getClassName(), __FILE__, __LINE__);
    Assert::assertEquals("action is of correct class",
            "Many",
            ((AbstractBase*)maleSocket->bself())->getLongDescription(), __FILE__, __LINE__);
    MaleSocket* maleSocket2 = maleSocket->getChild(0)->getConnectedSocket();
    Assert::assertEquals("action is of correct class",
            "jmri.jmrit.logixng.tools.debugger.DebuggerMaleDigitalActionSocket",
            ((AbstractMaleSocket*)maleSocket2->bself())->getClassName(), __FILE__, __LINE__);
    Assert::assertEquals("action is of correct class",
            "If Then Else. Execute on change",
            ((AbstractBase*)maleSocket2->bself())->getLongDescription(), __FILE__, __LINE__);
}

//@Test
/*public*/  void DefaultLogixNGManagerTest::testDeleteLogixNG() /*throws SocketAlreadyConnectedException, PropertyVetoException*/ {
    LogixNG_Manager* logixNG_Manager = (DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager");
    DefaultConditionalNGManager* conditionalNG_Manager = (DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager");
    DefaultAnalogActionManager* analogActionManager = (DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager");
    DefaultAnalogExpressionManager* analogExpressionManager = (DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
    DefaultDigitalActionManager* digitalActionManager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
    DefaultDigitalBooleanActionManager* digitalBooleanActionManager = (DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager");
    DefaultDigitalExpressionManager* digitalExpressionManager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
    DefaultStringActionManager* stringActionManager = (DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager");
    DefaultStringExpressionManager* stringExpressionManager = (DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager");

    DefaultLogixNG* logixNG = (DefaultLogixNG*)logixNG_Manager->createLogixNG("IQ1", "Some name");
    Assert::assertNotNull("exists", logixNG?logixNG->self():nullptr, __FILE__, __LINE__);

    DefaultConditionalNG* conditionalNG = (DefaultConditionalNG*)conditionalNG_Manager
            ->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
    Assert::assertNotNull("exists", conditionalNG->self(), __FILE__, __LINE__);

    FemaleSocket* femaleSocket = conditionalNG->getFemaleSocket();
    MaleDigitalActionSocket* actionManySocket = digitalActionManager
                    ->registerAction(new DigitalMany(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionManySocket);

    femaleSocket = actionManySocket->getChild(0);
    MaleDigitalActionSocket* actionIfThenSocket = digitalActionManager
                    ->registerAction(new IfThenElse(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionIfThenSocket);

    femaleSocket = actionIfThenSocket->getChild(0);
    MaleDigitalExpressionSocket* expressionOrSocket = ((DefaultDigitalExpressionManager*)
            InstanceManager::getDefault("DigitalExpressionManager"))
                    ->registerExpression(new Or(digitalExpressionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(expressionOrSocket);

    femaleSocket = actionManySocket->getChild(1);
    MaleDigitalActionSocket* actionDoAnalogActionSocket = digitalActionManager
                    ->registerAction(new DoAnalogAction(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionDoAnalogActionSocket);

    femaleSocket = actionDoAnalogActionSocket->getChild(0);
    MaleAnalogExpressionSocket* expressionAnalogExpressionConstantSocket = analogExpressionManager
                    ->registerExpression(new AnalogExpressionConstant(analogExpressionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(expressionAnalogExpressionConstantSocket);

    femaleSocket = actionDoAnalogActionSocket->getChild(1);
    MaleAnalogActionSocket* actionAnalogManySocket = ((DefaultAnalogActionManager*)
            InstanceManager::getDefault("AnalogActionManager"))
                    ->registerAction(new AnalogMany(analogActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionAnalogManySocket);

    femaleSocket = actionManySocket->getChild(2);
    MaleDigitalActionSocket* actionDoStringActionSocket = ((DefaultDigitalActionManager*)
            InstanceManager::getDefault("DigitalActionManager"))
                    ->registerAction(new DoStringAction(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionDoStringActionSocket);

    femaleSocket = actionDoStringActionSocket->getChild(0);
    MaleStringExpressionSocket* expressionStringExpressionConstantSocket = stringExpressionManager
                    ->registerExpression(new StringExpressionConstant(stringExpressionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(expressionStringExpressionConstantSocket);

    femaleSocket = actionDoStringActionSocket->getChild(1);
    MaleStringActionSocket* actionStringManySocket = stringActionManager
                    ->registerAction(new StringMany(stringActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionStringManySocket);

    femaleSocket = actionManySocket->getChild(3);
    MaleDigitalActionSocket* logix = digitalActionManager
                    ->registerAction(new Logix_Emulator(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(logix);

    femaleSocket = logix->getChild(1);
    MaleDigitalBooleanActionSocket* onChange = digitalBooleanActionManager
                    ->registerAction(new DigitalBooleanOnChange(
                            digitalBooleanActionManager->getAutoSystemName(),
                            "",
                            DigitalBooleanOnChange::Trigger::CHANGE));
    femaleSocket->_connect(onChange);


    LastResultOfDigitalExpression* lastResultOfDigitalExpression =
            new LastResultOfDigitalExpression(
                            digitalExpressionManager->getAutoSystemName(), "");
    lastResultOfDigitalExpression->setDigitalExpression(expressionOrSocket);

    QString sn = ((DefaultLogixNG*)logixNG->bself())->AbstractNamedBean::getSystemName();
    Assert::assertNotNull(logixNG_Manager->getBySystemName(sn)->self(), __FILE__, __LINE__);
    Assert::assertNotNull(conditionalNG_Manager->getBySystemName(((DefaultConditionalNG*)conditionalNG->bself())->AbstractNamedBean::getSystemName())->self(), __FILE__, __LINE__);
    Assert::assertNotNull(analogActionManager->getBySystemName(((DefaultMaleAnalogActionSocket*)actionAnalogManySocket->bself())->AbstractNamedBean::getSystemName())->self(), __FILE__, __LINE__);
    Assert::assertNotNull(analogExpressionManager->getBySystemName(((DefaultMaleAnalogExpressionSocket*)expressionAnalogExpressionConstantSocket->bself())->AbstractNamedBean::getSystemName())->self(), __FILE__, __LINE__);
    sn = ((AbstractNamedBean*)actionManySocket)->AbstractNamedBean::getSystemName();
    Assert::assertNotNull(digitalActionManager->getBySystemName(((AbstractNamedBean*)actionManySocket)->AbstractNamedBean::getSystemName())->self(), __FILE__, __LINE__);
    Assert::assertNotNull(digitalExpressionManager->getBySystemName(((AbstractNamedBean*)expressionOrSocket->bself())->AbstractNamedBean::getSystemName())->self(), __FILE__, __LINE__);
    Assert::assertNotNull(stringActionManager->getBySystemName(((AbstractNamedBean*)actionStringManySocket->bself())->AbstractNamedBean::getSystemName())->self(), __FILE__, __LINE__);
    Assert::assertNotNull(stringExpressionManager->getBySystemName(((AbstractNamedBean*)expressionStringExpressionConstantSocket->bself())->AbstractNamedBean::getSystemName())->self(), __FILE__, __LINE__);
    Assert::assertNotNull(digitalBooleanActionManager->getBySystemName(((AbstractNamedBean*)onChange->bself())->AbstractNamedBean::getSystemName())->self(), __FILE__, __LINE__);

    try {
        logixNG_Manager->deleteBean((AbstractNamedBean*)logixNG, "CanDelete");
    } catch (PropertyVetoException* e) {
        Assert::assertEquals("DoNotDelete", e->getPropertyChangeEvent()->getPropertyName(), __FILE__, __LINE__);
        Assert::assertEquals("Expression is in use by \"IQDE:AUTO:0002\"", e->getMessage(), __FILE__, __LINE__);
    }
    lastResultOfDigitalExpression->removeDigitalExpression();

    try {
        logixNG_Manager->deleteBean((AbstractNamedBean*)logixNG, "CanDelete");
    } catch (PropertyVetoException* e) {
        Assert::assertEquals("CanDelete", e->getPropertyChangeEvent()->getPropertyName(), __FILE__, __LINE__);
        Assert::assertEquals("", e->getMessage(), __FILE__, __LINE__);
    }
#if 0
    logixNG_Manager->deleteBean((AbstractNamedBean*)logixNG, "DoDelete");
#endif
    Assert::assertNull((QObject*)logixNG_Manager->getBySystemName(logixNG->AbstractNamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)conditionalNG_Manager->getBySystemName(conditionalNG->AbstractNamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)analogActionManager->getBySystemName(((DefaultMaleAnalogActionSocket*)actionAnalogManySocket->bself())->AbstractNamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)analogExpressionManager->getBySystemName(((DefaultMaleAnalogExpressionSocket*)expressionAnalogExpressionConstantSocket->bself())->AbstractNamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)digitalActionManager->getBySystemName(((DefaultMaleDigitalActionSocket*)actionManySocket->bself())->AbstractNamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)digitalExpressionManager->getBySystemName(((DefaultMaleDigitalExpressionSocket*)expressionOrSocket->bself())->AbstractNamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)stringActionManager->getBySystemName(((DefaultMaleStringActionSocket*)actionStringManySocket->bself())->AbstractNamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)stringExpressionManager->getBySystemName(((DefaultMaleStringExpressionSocket*)expressionStringExpressionConstantSocket->bself())->AbstractNamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)digitalBooleanActionManager->getBySystemName(((DefaultMaleDigitalBooleanActionSocket*)onChange->bself())->AbstractNamedBean::getSystemName()), __FILE__, __LINE__);

}

//@Test
/*public*/  void DefaultLogixNGManagerTest::testDeleteConditionalNG() /*throws SocketAlreadyConnectedException, PropertyVetoException*/ {
 LogixNG_Manager* logixNG_Manager = (DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager");
 ConditionalNG_Manager* conditionalNG_Manager = (DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager");
 AnalogActionManager* analogActionManager = (DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager");
 AnalogExpressionManager* analogExpressionManager = (DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
 DigitalActionManager* digitalActionManager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
 DigitalBooleanActionManager* digitalBooleanActionManager = (DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager");
 DigitalExpressionManager* digitalExpressionManager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
 StringActionManager* stringActionManager = (DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager");
 StringExpressionManager* stringExpressionManager = (DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager");

 DefaultLogixNG* logixNG = (DefaultLogixNG*)logixNG_Manager->createLogixNG("IQ1", "Some name");
    Assert::assertNotNull("exists", logixNG?logixNG->self():nullptr, __FILE__, __LINE__);

    DefaultConditionalNG* conditionalNG = (DefaultConditionalNG*)conditionalNG_Manager
            ->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
    Assert::assertNotNull("exists", (QObject*)conditionalNG, __FILE__, __LINE__);

    FemaleSocket* femaleSocket = conditionalNG->getFemaleSocket();
    MaleDigitalActionSocket* actionManySocket = digitalActionManager
                    ->registerAction(new DigitalMany(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionManySocket);

    femaleSocket = actionManySocket->getChild(0);
    MaleDigitalActionSocket* actionIfThenSocket = digitalActionManager
                    ->registerAction(new IfThenElse(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionIfThenSocket);

    femaleSocket = actionIfThenSocket->getChild(0);
    MaleDigitalExpressionSocket* expressionOrSocket = ((DefaultDigitalExpressionManager*)
            InstanceManager::getDefault("DigitalExpressionManager"))
                    ->registerExpression(new Or(digitalExpressionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(expressionOrSocket);

    femaleSocket = actionManySocket->getChild(1);
    MaleDigitalActionSocket* actionDoAnalogActionSocket = digitalActionManager
                    ->registerAction(new DoAnalogAction(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionDoAnalogActionSocket);

    femaleSocket = actionDoAnalogActionSocket->getChild(0);
    MaleAnalogExpressionSocket* expressionAnalogExpressionConstantSocket =
            analogExpressionManager
                    ->registerExpression(new AnalogExpressionConstant(analogExpressionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(expressionAnalogExpressionConstantSocket);

    femaleSocket = actionDoAnalogActionSocket->getChild(1);
    MaleAnalogActionSocket* actionAnalogManySocket = ((DefaultAnalogActionManager*)
            InstanceManager::getDefault("AnalogActionManager"))
                    ->registerAction(new AnalogMany(analogActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionAnalogManySocket);

    femaleSocket = actionManySocket->getChild(2);
    MaleDigitalActionSocket* actionDoStringActionSocket = ((DefaultDigitalActionManager*)
            InstanceManager::getDefault("DigitalActionManager"))
                    ->registerAction(new DoStringAction(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionDoStringActionSocket);

    femaleSocket = actionDoStringActionSocket->getChild(0);
    MaleStringExpressionSocket* expressionStringExpressionConstantSocket =
            stringExpressionManager
                    ->registerExpression(new StringExpressionConstant(stringExpressionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(expressionStringExpressionConstantSocket);

    femaleSocket = actionDoStringActionSocket->getChild(1);
    MaleStringActionSocket* actionStringManySocket = stringActionManager
                    ->registerAction(new StringMany(stringActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionStringManySocket);

    femaleSocket = actionManySocket->getChild(3);
    MaleDigitalActionSocket* logix = digitalActionManager
                    ->registerAction(new Actions::Logix(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(logix);

    femaleSocket = logix->getChild(1);
    MaleDigitalBooleanActionSocket* onChange = digitalBooleanActionManager
                    ->registerAction(new DigitalBooleanOnChange(
                            digitalBooleanActionManager->getAutoSystemName(),
                            "",
                            DigitalBooleanOnChange::Trigger::CHANGE));
    femaleSocket->_connect(onChange);


    LastResultOfDigitalExpression* lastResultOfDigitalExpression =
            new LastResultOfDigitalExpression(
                            digitalExpressionManager->getAutoSystemName(), "");
    lastResultOfDigitalExpression->setDigitalExpression(expressionOrSocket);


    Assert::assertNotNull((QObject*)logixNG_Manager->getBySystemName(logixNG->AbstractNamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)conditionalNG_Manager->getBySystemName(conditionalNG->AbstractNamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)analogActionManager->getBySystemName(actionAnalogManySocket->Base::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)analogExpressionManager->getBySystemName(expressionAnalogExpressionConstantSocket->Base::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)digitalActionManager->getBySystemName(actionManySocket->Base::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)digitalExpressionManager->getBySystemName(expressionOrSocket->Base::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)stringActionManager->getBySystemName(actionStringManySocket->Base::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)stringExpressionManager->getBySystemName(expressionStringExpressionConstantSocket->Base::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)digitalBooleanActionManager->getBySystemName(onChange->Base::getSystemName()), __FILE__, __LINE__);

    try {
        conditionalNG_Manager->deleteBean((AbstractNamedBean*)conditionalNG, "CanDelete");
    } catch (PropertyVetoException* e) {
        Assert::assertEquals("DoNotDelete", e->getPropertyChangeEvent()->getPropertyName(), __FILE__, __LINE__);
        Assert::assertEquals("Expression is in use by \"IQDE:AUTO:0002\"", e->getMessage(), __FILE__, __LINE__);
    }
    lastResultOfDigitalExpression->removeDigitalExpression();

    try {
        conditionalNG_Manager->deleteBean((AbstractNamedBean*)conditionalNG, "CanDelete");
    } catch (PropertyVetoException* e) {
        Assert::assertEquals("CanDelete", e->getPropertyChangeEvent()->getPropertyName(), __FILE__, __LINE__);
        Assert::assertEquals("", e->getMessage(), __FILE__, __LINE__);
    }
    conditionalNG_Manager->deleteBean((AbstractNamedBean*)conditionalNG, "DoDelete");

    Assert::assertNotNull((QObject*)logixNG_Manager->getBySystemName(logixNG->AbstractNamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)conditionalNG_Manager->getBySystemName(conditionalNG->AbstractNamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)analogActionManager->getBySystemName(actionAnalogManySocket->Base::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)analogExpressionManager->getBySystemName(expressionAnalogExpressionConstantSocket->Base::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)digitalActionManager->getBySystemName(actionManySocket->Base::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)digitalExpressionManager->getBySystemName(expressionOrSocket->Base::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)stringActionManager->getBySystemName(actionStringManySocket->Base::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)stringExpressionManager->getBySystemName(expressionStringExpressionConstantSocket->Base::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)digitalBooleanActionManager->getBySystemName(onChange->Base::getSystemName()), __FILE__, __LINE__);
}

//@Test
/*public*/  void DefaultLogixNGManagerTest::testDeleteModule() /*throws SocketAlreadyConnectedException, PropertyVetoException*/ {
 FemaleSocketManager* femaleSocketManager = ((DefaultFemaleSocketManager*)InstanceManager::getDefault("FemaleSocketManager"));
 ModuleManager* moduleManager = ((DefaultModuleManager*)InstanceManager::getDefault("ModuleManager"));
 AnalogActionManager* analogActionManager = (DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager");
 AnalogExpressionManager* analogExpressionManager = (DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
 DigitalActionManager* digitalActionManager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
 DigitalBooleanActionManager* digitalBooleanActionManager = (DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager");
 DigitalExpressionManager* digitalExpressionManager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
 StringActionManager* stringActionManager = (DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager");
 StringExpressionManager* stringExpressionManager = (DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager");

    Module* module = (DefaultModule*)moduleManager
            ->createModule("A module", femaleSocketManager->getSocketTypeByType("DefaultFemaleDigitalActionSocket"))->self();  // NOI18N
    Assert::assertNotNull("exists", module->self(), __FILE__, __LINE__);

    FemaleSocket* femaleSocket = module->getRootSocket();
    MaleDigitalActionSocket* actionManySocket = digitalActionManager
                    ->registerAction(new DigitalMany(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionManySocket);

    femaleSocket = actionManySocket->getChild(0);
    MaleDigitalActionSocket* actionIfThenSocket = digitalActionManager
                    ->registerAction(new IfThenElse(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionIfThenSocket);

    femaleSocket = actionIfThenSocket->getChild(0);
    MaleDigitalExpressionSocket* expressionOrSocket = ((DefaultDigitalExpressionManager*)
            InstanceManager::getDefault("DigitalExpressionManager"))
                    ->registerExpression(new Or(digitalExpressionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(expressionOrSocket);

    femaleSocket = actionManySocket->getChild(1);
    MaleDigitalActionSocket* actionDoAnalogActionSocket = digitalActionManager
                    ->registerAction(new DoAnalogAction(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionDoAnalogActionSocket);

    femaleSocket = actionDoAnalogActionSocket->getChild(0);
    MaleAnalogExpressionSocket* expressionAnalogExpressionConstantSocket =
            analogExpressionManager
                    ->registerExpression(new AnalogExpressionConstant(analogExpressionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(expressionAnalogExpressionConstantSocket);

    femaleSocket = actionDoAnalogActionSocket->getChild(1);
    MaleAnalogActionSocket* actionAnalogManySocket = ((DefaultAnalogActionManager*)
            InstanceManager::getDefault("AnalogActionManager"))
                    ->registerAction(new AnalogMany(analogActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionAnalogManySocket);

    femaleSocket = actionManySocket->getChild(2);
    MaleDigitalActionSocket* actionDoStringActionSocket = ((DefaultDigitalActionManager*)
            InstanceManager::getDefault("DigitalActionManager"))
                    ->registerAction(new DoStringAction(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionDoStringActionSocket);

    femaleSocket = actionDoStringActionSocket->getChild(0);
    MaleStringExpressionSocket* expressionStringExpressionConstantSocket =
            stringExpressionManager
                    ->registerExpression(new StringExpressionConstant(stringExpressionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(expressionStringExpressionConstantSocket);

    femaleSocket = actionDoStringActionSocket->getChild(1);
    MaleStringActionSocket* actionStringManySocket = stringActionManager
                    ->registerAction(new StringMany(stringActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionStringManySocket);

    femaleSocket = actionManySocket->getChild(3);
    MaleDigitalActionSocket* logix = digitalActionManager
                    ->registerAction(new Actions::Logix(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(logix);

    femaleSocket = logix->getChild(1);
    MaleDigitalBooleanActionSocket* onChange = digitalBooleanActionManager
                    ->registerAction(new DigitalBooleanOnChange(
                            digitalBooleanActionManager->getAutoSystemName(),
                            "",
                            DigitalBooleanOnChange::Trigger::CHANGE));
    femaleSocket->_connect(onChange);


    LastResultOfDigitalExpression* lastResultOfDigitalExpression =
            new LastResultOfDigitalExpression(
                            digitalExpressionManager->getAutoSystemName(), "null");
    lastResultOfDigitalExpression->setDigitalExpression(expressionOrSocket);


    Assert::assertNotNull((QObject*)moduleManager->getBySystemName(module->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)analogActionManager->getBySystemName(actionAnalogManySocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)analogExpressionManager->getBySystemName(expressionAnalogExpressionConstantSocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)digitalActionManager->getBySystemName(actionManySocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)digitalExpressionManager->getBySystemName(expressionOrSocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)stringActionManager->getBySystemName(actionStringManySocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)stringExpressionManager->getBySystemName(expressionStringExpressionConstantSocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)digitalBooleanActionManager->getBySystemName(onChange->NamedBean::getSystemName()), __FILE__, __LINE__);

    try {
        moduleManager->deleteBean(module, "CanDelete");
    } catch (PropertyVetoException* e) {
        Assert::assertEquals("DoNotDelete", e->getPropertyChangeEvent()->getPropertyName(), __FILE__, __LINE__);
        Assert::assertEquals("Expression is in use by \"IQDE:AUTO:0002\"", e->getMessage(), __FILE__, __LINE__);
    }
    lastResultOfDigitalExpression->removeDigitalExpression();

    try {
        moduleManager->deleteBean(module, "CanDelete");
    } catch (PropertyVetoException* e) {
        Assert::assertEquals("CanDelete", e->getPropertyChangeEvent()->getPropertyName(), __FILE__, __LINE__);
        Assert::assertEquals("", e->getMessage(), __FILE__, __LINE__);
    }
    moduleManager->deleteBean(module, "DoDelete");

    Assert::assertNull((QObject*)moduleManager->getBySystemName(module->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)analogActionManager->getBySystemName(actionAnalogManySocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)analogExpressionManager->getBySystemName(expressionAnalogExpressionConstantSocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)digitalActionManager->getBySystemName(actionManySocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)digitalExpressionManager->getBySystemName(expressionOrSocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)stringActionManager->getBySystemName(actionStringManySocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)stringExpressionManager->getBySystemName(expressionStringExpressionConstantSocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)digitalBooleanActionManager->getBySystemName(onChange->NamedBean::getSystemName()), __FILE__, __LINE__);
}

//@Test
/*public*/  void DefaultLogixNGManagerTest::testDeleteAction() /*throws SocketAlreadyConnectedException, PropertyVetoException*/ {
//        LogixNG_Manager logixNG_Manager = InstanceManager::getDefault(LogixNG_Manager->class);
//        ConditionalNG_Manager conditionalNG_Manager = InstanceManager::getDefault(ConditionalNG_Manager->class);
 AnalogActionManager* analogActionManager = (DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager");
 AnalogExpressionManager* analogExpressionManager = (DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
 DigitalActionManager* digitalActionManager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
 DigitalBooleanActionManager* digitalBooleanActionManager = (DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager");
 DigitalExpressionManager* digitalExpressionManager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
 StringActionManager* stringActionManager = (DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager");
 StringExpressionManager* stringExpressionManager = (DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager");

//        LogixNG logixNG = logixNG_Manager->createLogixNG("IQ1", "Some name");
//        Assert::assertNotNull("exists", logixNG);

//        ConditionalNG conditionalNG = conditionalNG_Manager
//                .createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
//        Assert::assertNotNull("exists", conditionalNG);

//        FemaleSocket femaleSocket = conditionalNG.getFemaleSocket();
    MaleDigitalActionSocket* actionManySocket = digitalActionManager
                    ->registerAction(new DigitalMany(digitalActionManager->getAutoSystemName(), ""));
//        femaleSocket->_connect(actionManySocket);

    FemaleSocket* femaleSocket = actionManySocket->getChild(0);
    MaleDigitalActionSocket* actionIfThenSocket = digitalActionManager
                    ->registerAction(new IfThenElse(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionIfThenSocket);

    femaleSocket = actionIfThenSocket->getChild(0);
    MaleDigitalExpressionSocket* expressionOrSocket = ((DefaultDigitalExpressionManager*)
            InstanceManager::getDefault("DigitalExpressionManager"))
                    ->registerExpression(new Or(digitalExpressionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(expressionOrSocket);

    femaleSocket = actionManySocket->getChild(1);
    MaleDigitalActionSocket* actionDoAnalogActionSocket = digitalActionManager
                    ->registerAction(new DoAnalogAction(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionDoAnalogActionSocket);

    femaleSocket = actionDoAnalogActionSocket->getChild(0);
    MaleAnalogExpressionSocket* expressionAnalogExpressionConstantSocket =
            analogExpressionManager
                    ->registerExpression(new AnalogExpressionConstant(analogExpressionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(expressionAnalogExpressionConstantSocket);

    femaleSocket = actionDoAnalogActionSocket->getChild(1);
    MaleAnalogActionSocket* actionAnalogManySocket = ((DefaultAnalogActionManager*)
            InstanceManager::getDefault("AnalogActionManager"))
                    ->registerAction(new AnalogMany(analogActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionAnalogManySocket);

    femaleSocket = actionManySocket->getChild(2);
    MaleDigitalActionSocket* actionDoStringActionSocket = ((DefaultDigitalActionManager*)
            InstanceManager::getDefault("DigitalActionManager"))
                    ->registerAction(new DoStringAction(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionDoStringActionSocket);

    femaleSocket = actionDoStringActionSocket->getChild(0);
    MaleStringExpressionSocket* expressionStringExpressionConstantSocket =
            stringExpressionManager
                    ->registerExpression(new StringExpressionConstant(stringExpressionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(expressionStringExpressionConstantSocket);

    femaleSocket = actionDoStringActionSocket->getChild(1);
    MaleStringActionSocket* actionStringManySocket = stringActionManager
                    ->registerAction(new StringMany(stringActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(actionStringManySocket);

    femaleSocket = actionManySocket->getChild(3);
    MaleDigitalActionSocket* logix = digitalActionManager
                    ->registerAction(new Actions::Logix(digitalActionManager->getAutoSystemName(), ""));
    femaleSocket->_connect(logix);

    femaleSocket = logix->getChild(1);
    MaleDigitalBooleanActionSocket* onChange = digitalBooleanActionManager
                    ->registerAction(new DigitalBooleanOnChange(
                            digitalBooleanActionManager->getAutoSystemName(),
                            "",
                            DigitalBooleanOnChange::Trigger::CHANGE));
    femaleSocket->_connect(onChange);


    LastResultOfDigitalExpression* lastResultOfDigitalExpression =
            new LastResultOfDigitalExpression(
                            digitalExpressionManager->getAutoSystemName(), "");
    lastResultOfDigitalExpression->setDigitalExpression(expressionOrSocket);


//        Assert::assertNotNull(logixNG_Manager->getBySystemName(logixNG->getSystemName()));
//        Assert::assertNotNull(conditionalNG_Manager->getBySystemName(conditionalNG->getSystemName()));
    Assert::assertNotNull((QObject*)analogActionManager->getBySystemName(actionAnalogManySocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)analogExpressionManager->getBySystemName(expressionAnalogExpressionConstantSocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)digitalActionManager->getBySystemName(actionManySocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)digitalExpressionManager->getBySystemName(expressionOrSocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)stringActionManager->getBySystemName(actionStringManySocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)stringExpressionManager->getBySystemName(expressionStringExpressionConstantSocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)digitalBooleanActionManager->getBySystemName(onChange->NamedBean::getSystemName()), __FILE__, __LINE__);

    try {
        digitalActionManager->deleteBean(actionManySocket, "CanDelete");
    } catch (PropertyVetoException* e) {
        Assert::assertEquals("DoNotDelete", e->getPropertyChangeEvent()->getPropertyName(), __FILE__, __LINE__);
        Assert::assertEquals("Expression is in use by \"IQDE:AUTO:0002\"", e->getMessage(), __FILE__, __LINE__);
    }
    lastResultOfDigitalExpression->removeDigitalExpression();

    try {
        digitalActionManager->deleteBean(actionManySocket, "CanDelete");
    } catch (PropertyVetoException* e) {
        Assert::assertEquals("CanDelete", e->getPropertyChangeEvent()->getPropertyName(), __FILE__, __LINE__);
        Assert::assertEquals("", e->getMessage(), __FILE__, __LINE__);
    }
    digitalActionManager->deleteBean(actionManySocket, "DoDelete");

//        Assert::assertNotNull(logixNG_Manager->getBySystemName(logixNG->getSystemName()));
//        Assert::assertNull(conditionalNG_Manager->getBySystemName(conditionalNG->getSystemName()));
    Assert::assertNull((QObject*)analogActionManager->getBySystemName(actionAnalogManySocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)analogExpressionManager->getBySystemName(expressionAnalogExpressionConstantSocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)digitalActionManager->getBySystemName(actionManySocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)digitalExpressionManager->getBySystemName(expressionOrSocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)stringActionManager->getBySystemName(actionStringManySocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)stringExpressionManager->getBySystemName(expressionStringExpressionConstantSocket->NamedBean::getSystemName()), __FILE__, __LINE__);
    Assert::assertNull((QObject*)digitalBooleanActionManager->getBySystemName(onChange->NamedBean::getSystemName()), __FILE__, __LINE__);
}

//@Test
/*public*/  void DefaultLogixNGManagerTest::testDeleteTable() /*throws SocketAlreadyConnectedException*/ {
//        Assert::fail("Not implemented yet");
}

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
