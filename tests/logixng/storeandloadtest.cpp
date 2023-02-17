#include "storeandloadtest.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "junitappender.h"
#include "junitutil.h"
#include "assert1.h"
#include "logixng_thread.h"
#include "blockmanager.h"
#include "proxylightmanager.h"
#include "variablelight.h"
#include "proxysensormanager.h"
#include "proxyturnoutmanager.h"
#include "defaultmemorymanager.h"
#include "defaultlogixmanager.h"
#include "defaultconditionalmanager.h"
#include "../../libPr3/logix.h"
#include "abstractsignalheadmanager.h"
#include "virtualsignalhead.h"
#include "defaultsignalmastmanager.h"
#include "oblockmanager.h"
#include "oblock.h"
#include "conditional.h"
#include "warrantmanager.h"
#include "warrant.h"
#include "blockorder.h"
#include "defaultlogixngmanager.h"
#include "defaultconditionalngmanager.h"
#include "defaultanalogactionmanager.h"
#include "defaultanalogexpressionmanager.h"
#include "defaultdigitalactionmanager.h"
#include "defaultdigitalbooleanactionmanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "defaultstringactionmanager.h"
#include "defaultstringexpressionmanager.h"
#include "defaultlogixnginitializationmanager.h"
#include "defaultnamedtablemanager.h"
#include "defaultmodulemanager.h"
#include "defaultfemalesocketmanager.h"
#include "digitalmany.h"
#include "actionmemory.h"
#include "dostringaction.h"
#include "digitalbooleanmany.h"
#include "and.h"
#include "digitalmany.h"
#include "actionturnout.h"
#include "logix_emulator.h"
#include "digitalbooleanonchange.h"
#include "stringexpressionconstant.h"
#include "stringactionmemory.h"
#include "stringexpressionmemory.h"
#include "stringmany.h"
#include "stringexpressionmemory.h"
#include "stringformula.h"
#include "appsconfigurationmanager.h"
#include "fileutil.h"
#include "stringwriter.h"
#include "printwriter.h"
#include "system.h"
#include "actiontimer.h"
#include "doanalogaction.h"
#include "analogexpressionconstant.h"
#include "analogactionmemory.h"
#include "analogexpressionmemory.h"
#include "analogmany.h"
#include "analogformula.h"
#include "timesincemidnight.h"
#include "symboltable.h"
#include "defaultmaleanalogactionsocket.h"
#include "defaultnamedtablemanager.h"
#include "abstractnamedtable.h"
#include "defaultlogixng.h"
#include "defaultmaleanalogexpressionsocket.h"
#include "defaultmaledigitalbooleanactionsocket.h"
#include "defaultmaledigitalexpressionsocket.h"
#include "defaultmalestringactionsocket.h"
#include "defaultmalestringexpressionsocket.h"
#include "defaultmodule.h"
#include "defaultmaledigitalactionsocket.h"
#include "actionsensor.h"
#include "ifthenelse.h"
#include "expressionturnout.h"
#include "antecedent.h"
#include "false.h"
#include "or.h"
#include "triggeronce.h"
#include "true.h"
#include "not.h"
#include "digitalformula.h"
#include "hold.h"
#include "actionblock.h"
#include "actionclock.h"
#include "actionlistenonbeans.h"
#include "actionlocalvariable.h"
#include "actionsignalhead.h"
#include "actionpositionable.h"
#include "expressionsensor.h"
#include "expressionlight.h"
#include "lastresultofdigitalexpression.h"
#include "expressionsignalhead.h"
#include "expressionmemory.h"
#include "expressionlocalvariable.h"
#include "actionpower.h"
#include "expressionpower.h"
#include "for.h"
#include "actionlight.h"
#include "tableforeach.h"
#include "expressionreference.h"
#include "actions/logdata.h"
#include "expressions/ex_logdata.h"
#include "sequence.h"
#include "executedelayed.h"
#include "analogactionlightintensity.h"
#include "actions/digitalcallmodule.h"
#include "symboltable.h"
#include "module.h"
#include "loggingevent.h"
#include "expressions/ex_digitalcallmodule.h"

StoreAndLoadTest::StoreAndLoadTest(QObject *parent) : QObject(parent)
{
// setObjectName("StoreAndLoadTest");
}

/**
 * Creates a LogixNG with all actions and expressions to test store and load.
 * <P>
 * It uses the Base.printTree(PrintWriter writer, String indent) method to
 * compare the LogixNGs before and after store and load.
 */
///*public*/  class StoreAndLoadTest {

//    /*private*/ AudioManager audioManager;

    //@Test
    /*public*/  void StoreAndLoadTest::testLogixNGs() /*throws PropertyVetoException, Exception*/ {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    ConfigureManager* cm1 = (JmriConfigurationManager*)InstanceManager::getNullableDefault("ConfigureManager");
/*
        audioManager = new jmri.jmrit.audio.DefaultAudioManager(
                InstanceManager::getDefault(jmri.jmrix.internal.InternalSystemConnectionMemo.class));
        audioManager.init();
        JUnitUtil::waitFor(()->{return audioManager.isInitialised();});

        audioManager.provideAudio("IAB1");
        AudioSource audioSource = (AudioSource) audioManager.provideAudio("IAS1");
        audioSource.setAssignedBuffer((AudioBuffer) audioManager.getNamedBean("IAB1"));
*/
        Block* block1 = (Block*)((BlockManager*)InstanceManager::getDefault("BlockManager"))->provide("IB1")->self();
        block1->setValue("Block 1 Value");
        Block* block2 = (Block*)((BlockManager*)InstanceManager::getDefault("BlockManager"))->provide("IB2")->self();
        block2->setUserName("Some block");
        block1->setValue("Block 2 Value");
        Light* light1 = ((ProxyLightManager*)InstanceManager::getDefault("LightManager"))->provide("IL1");
        light1->setCommandedState(Light::OFF);
        Light* light2 = ((ProxyLightManager*)InstanceManager::getDefault("LightManager"))->provide("IL2");
        light2->setUserName("Some light");
        light2->setCommandedState(Light::OFF);
        VariableLight* variableLight1 = (VariableLight*)((ProxyLightManager*)InstanceManager::getDefault("LightManager"))->provide("ILVariable")->self();
        variableLight1->setCommandedState(Light::OFF);
        Sensor* sensor1 = (Sensor*)((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provide("IS1")->self();
        sensor1->setCommandedState(Sensor::INACTIVE);
        Sensor* sensor2 = (Sensor*)((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provide("IS2");
        sensor2->setCommandedState(Sensor::INACTIVE);
        sensor2->setUserName("Some sensor");
        Turnout* turnout1 = (AbstractTurnout*)((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provide("IT1")->self();
        turnout1->setCommandedState(Turnout::CLOSED);
        Turnout* turnout2 = (AbstractTurnout*)((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provide("IT2")->self();
        turnout2->setCommandedState(Turnout::CLOSED);
        turnout2->setUserName("Some turnout");
        Turnout* turnout3 = (Turnout*)((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provide("IT3")->self();
        turnout3->setCommandedState(Turnout::CLOSED);
        Turnout* turnout4 = (Turnout*)((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provide("IT4")->self();
        turnout4->setCommandedState(Turnout::CLOSED);
        Turnout* turnout5 = (Turnout*)((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provide("IT5")->self();
        turnout5->setCommandedState(Turnout::CLOSED);

        Memory* memory1 = (Memory*)((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM1")->self();
        Memory* memory2 = (Memory*)((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM2")->self();
        memory2->setUserName("Some memory");
        Memory* memory3 = (Memory*)((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide("IM3")->self();

        LogixManager* logixManager = (DefaultLogixManager*)InstanceManager::getDefault("LogixManager");
        ConditionalManager* conditionalManager = (DefaultConditionalManager*)InstanceManager::getDefault("ConditionalManager");

        Logix* logixIX1 = logixManager->createNewLogix("IX1", "");
        logixIX1->setEnabled(true);

        Conditional* conditionalIX1C1 = conditionalManager->createNewConditional("IX1C1", "First conditional");
        logixIX1->addConditional(conditionalIX1C1->getSystemName(), 0);

        ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))
                ->AbstractManager::Register(new VirtualSignalHead("IH1"));
        ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))
                ->AbstractManager::Register(new VirtualSignalHead("IH2"));

        // The signal head IH1 created above is also used here in signal mast IF$shsm:AAR-1946:CPL(IH1)
        ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))
                ->provideSignalMast("IF$shsm:AAR-1946:CPL(IH1)");

        ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))
                ->Register(new OBlock("OB98"));
        ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))
                ->Register(new OBlock("OB99"));

        ((WarrantManager*)InstanceManager::getDefault("WarrantManager"))
                ->Register(new Warrant("IW99", "Test Warrant"));
        Warrant* warrant = ((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getWarrant("IW99");
        warrant->addBlockOrder(new BlockOrder(((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock("OB98")));
        warrant->addBlockOrder(new BlockOrder(((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock("OB99")));

        LogixNG_Manager* logixNG_Manager = (DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager");
        ConditionalNG_Manager* conditionalNGManager = (DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager");
        AnalogActionManager* analogActionManager = (DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager");
        DefaultAnalogExpressionManager* analogExpressionManager = (DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
        DigitalActionManager* digitalActionManager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        DigitalBooleanActionManager* digitalBooleanActionManager = (DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager");
        DigitalExpressionManager* digitalExpressionManager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        StringActionManager* stringActionManager = (DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager");
        StringExpressionManager* stringExpressionManager = (DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager");
        LogixNG_InitializationManager* logixNG_InitializationManager = (DefaultLogixNGInitializationManager*)InstanceManager::getDefault("LogixNG_InitializationManager");

        // Load table turnout_and_signals.csv
        NamedTable* csvTable =
                ((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"))
                        ->loadTableFromCSV("IQT1", "", "program:java/test/jmri/jmrit/logixng/panel_and_data_files/turnout_and_signals.csv");
        Assert::assertNotNull(csvTable, __FILE__, __LINE__);

        // Create module IQM1
        Module* module = ((DefaultModuleManager*)
                InstanceManager::getDefault("ModuleManager"))->createModule("IQM1", "",
                        ((DefaultFemaleSocketManager*)InstanceManager::getDefault("FemaleSocketManager"))
                                ->getSocketTypeByType("DefaultFemaleDigitalActionSocket"));

        module->addParameter("other", true, true);
        module->addParameter("n", true, false);
        module->addParameter("result", false, true);
        module->addLocalVariable("temp1", InitialValueType::None, nullptr);
        module->addLocalVariable("temp2", InitialValueType::None, nullptr);

        DigitalMany* many901 = new DigitalMany("IQDA901", "");
        MaleSocket* manySocket901 = ((DefaultDigitalActionManager*)
                InstanceManager::getDefault("DigitalActionManager"))->registerAction(many901);
        module->getRootSocket()->_connect(manySocket901);




        // Create an empty LogixNG
        logixNG_Manager->createLogixNG("An empty logixNG");

        // Create a LogixNG with an empty ConditionalNG
        LogixNG* logixNG = logixNG_Manager->createLogixNG("A logixNG with an empty conditionlNG");
        ConditionalNG* conditionalNG =
                conditionalNGManager->createConditionalNG(logixNG, "An empty conditionalNG");
        logixNG->setEnabled(false);
        conditionalNG->setEnabled(false);


        // Create an empty ConditionalNG on the debug thread
        conditionalNG =
                conditionalNGManager->createConditionalNG(
                        logixNG, "A second empty conditionalNG", LogixNG_Thread::DEFAULT_LOGIXNG_THREAD);
        conditionalNG->setEnabled(false);


        // Create an empty ConditionalNG on another thread
        LogixNG_Thread::createNewThread(53, "My logixng thread");
        conditionalNG =
                conditionalNGManager->createConditionalNG(logixNG, "A third empty conditionalNG", 53);
        conditionalNG->setEnabled(false);


        // Create an empty ConditionalNG on another thread
        LogixNG_Thread::createNewThread("My other logixng thread");
        conditionalNG = conditionalNGManager->createConditionalNG(
                logixNG, "A fourth empty conditionalNG", LogixNG_Thread::getThreadID("My other logixng thread"));
        conditionalNG->setEnabled(false);


        logixNG = logixNG_Manager->createLogixNG("A logixNG in the initialization table");
        conditionalNGManager->createConditionalNG(logixNG, "Yet another another conditionalNG");
        logixNG_InitializationManager->add(logixNG);


        logixNG = logixNG_Manager->createLogixNG("Another logixNG in the initialization table");
        conditionalNGManager->createConditionalNG(logixNG, "Yet another another another conditionalNG");
        logixNG_InitializationManager->add(logixNG);


        logixNG = logixNG_Manager->createLogixNG("A logixNG");
        conditionalNG =
                conditionalNGManager->createConditionalNG(logixNG, "Yet another conditionalNG");
        logixNG->setEnabled(false);
        conditionalNG->setEnabled(true);

        FemaleSocket* femaleRootSocket = conditionalNG->getFemaleSocket();
        MaleDigitalActionSocket* actionManySocket =
                digitalActionManager->registerAction(new DigitalMany(
                                        ((DefaultDigitalActionManager*)digitalActionManager)->AbstractManager::getAutoSystemName(), ""));
        femaleRootSocket->_connect(actionManySocket);



        int indexAction = 0;

        MaleSocket* maleSocket;
#if 0 //Audio functions not yet implemented
        ActionAudio actionAudio = new ActionAudio(digitalActionManager->getAutoSystemName(), "");
        /*MaleSocket*/ maleSocket = digitalActionManager->registerAction(actionAudio);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionAudio = new ActionAudio(digitalActionManager->getAutoSystemName(), "");
        actionAudio->AbstractNamedBean::setComment("A comment");
//        actionAudio.setAudio(audioSource);
        actionAudio.setOperation(ActionAudio.Operation.Play);
        actionAudio.setAddressing(NamedBeanAddressing::Direct);
        actionAudio.setFormula("\"IT\"+index");
        actionAudio.setLocalVariable("index");
        actionAudio.setReference("{IM1}");
        actionAudio.setOperationAddressing(NamedBeanAddressing::LocalVariable);
        actionAudio.setOperationFormula("\"IT\"+index2");
        actionAudio.setOperationLocalVariable("index2");
        actionAudio.setOperationReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(actionAudio);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionAudio = new ActionAudio(digitalActionManager->getAutoSystemName(), "");
        actionAudio->AbstractNamedBean::setComment("A comment");
//        actionAudio.setAudio(audioSource);
        actionAudio.setOperation(ActionAudio.Operation.PlayToggle);
        actionAudio.setAddressing(NamedBeanAddressing::LocalVariable);
        actionAudio.setFormula("\"IT\"+index");
        actionAudio.setLocalVariable("index");
        actionAudio.setReference("{IM1}");
        actionAudio.setOperationAddressing(NamedBeanAddressing::Formula);
        actionAudio.setOperationFormula("\"IT\"+index2");
        actionAudio.setOperationLocalVariable("index2");
        actionAudio.setOperationReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(actionAudio);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionAudio = new ActionAudio(digitalActionManager->getAutoSystemName(), "");
        actionAudio->AbstractNamedBean::setComment("A comment");
//        actionAudio.setAudio(audioSource);
        actionAudio.setOperation(ActionAudio.Operation.Pause);
        actionAudio.setAddressing(NamedBeanAddressing::Formula);
        actionAudio.setFormula("\"IT\"+index");
        actionAudio.setLocalVariable("index");
        actionAudio.setReference("{IM1}");
        actionAudio.setOperationAddressing(NamedBeanAddressing::Reference);
        actionAudio.setOperationFormula("\"IT\"+index2");
        actionAudio.setOperationLocalVariable("index2");
        actionAudio.setOperationReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(actionAudio);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionAudio = new ActionAudio(digitalActionManager->getAutoSystemName(), "");
        actionAudio->AbstractNamedBean::setComment("A comment");
//        actionAudio.setAudio(audioSource);
        actionAudio.setOperation(ActionAudio.Operation.PauseToggle);
        actionAudio.setAddressing(NamedBeanAddressing::Reference);
        actionAudio.setFormula("\"IT\"+index");
        actionAudio.setLocalVariable("index");
        actionAudio.setReference("{IM1}");
        actionAudio.setOperationAddressing(NamedBeanAddressing::Direct);
        actionAudio.setOperationFormula("\"IT\"+index2");
        actionAudio.setOperationLocalVariable("index2");
        actionAudio.setOperationReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(actionAudio);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionAudio = new ActionAudio(digitalActionManager->getAutoSystemName(), "");
        actionAudio.setOperation(ActionAudio.Operation.Stop);

        actionAudio = new ActionAudio(digitalActionManager->getAutoSystemName(), "");
        actionAudio.setOperation(ActionAudio.Operation.FadeIn);

        actionAudio = new ActionAudio(digitalActionManager->getAutoSystemName(), "");
        actionAudio.setOperation(ActionAudio.Operation.FadeOut);

        actionAudio = new ActionAudio(digitalActionManager->getAutoSystemName(), "");
        actionAudio.setOperation(ActionAudio.Operation.Rewind);

        actionAudio = new ActionAudio(digitalActionManager->getAutoSystemName(), "");
        actionAudio.setOperation(ActionAudio.Operation.ResetPosition);
#endif

        ActionBlock* actionBlock = new ActionBlock(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionBlock);
        maleSocket->setEnabled(false);
        maleSocket->setLocked(true);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionBlock = new ActionBlock(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionBlock);
        maleSocket->setErrorHandlingType(ErrorHandlingType::Default);
        maleSocket->setLocked(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionBlock = new ActionBlock(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionBlock);
        maleSocket->setErrorHandlingType(ErrorHandlingType::ThrowException);
        maleSocket->setSystem(true);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// Direct / Direct / Direct :: SetValue
        actionBlock = new ActionBlock(digitalActionManager->getAutoSystemName(), "");
        actionBlock->AbstractNamedBean::setComment("Direct / Direct / Direct :: SetValue");
        maleSocket->setLocked(false);

        actionBlock->setAddressing(NamedBeanAddressing::Direct);
        actionBlock->setBlock(block1);

        actionBlock->setOperationAddressing(NamedBeanAddressing::Direct);
        actionBlock->setOperationDirect(ActionBlock::DirectOperation::SetValue);

        actionBlock->setDataAddressing(NamedBeanAddressing::Direct);
        actionBlock->setBlockValue("ABC");

        maleSocket = digitalActionManager->registerAction(actionBlock);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// Direct / Direct :: SetOccupied
        actionBlock = new ActionBlock(digitalActionManager->getAutoSystemName(), "");
        actionBlock->AbstractNamedBean::setComment("Direct / Direct :: SetOccupied");

        actionBlock->setAddressing(NamedBeanAddressing::Direct);
        actionBlock->setBlock(block1);

        actionBlock->setOperationAddressing(NamedBeanAddressing::Direct);
        actionBlock->setOperationDirect(ActionBlock::DirectOperation::SetOccupied);

        maleSocket = digitalActionManager->registerAction(actionBlock);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// Direct / LocalVariable
        actionBlock = new ActionBlock(digitalActionManager->getAutoSystemName(), "");
        actionBlock->AbstractNamedBean::setComment("Direct / LocalVariable");

        actionBlock->setAddressing(NamedBeanAddressing::Direct);
        actionBlock->setBlock(block1);

        actionBlock->setOperationAddressing(NamedBeanAddressing::LocalVariable);
        actionBlock->setOperationLocalVariable("index2");

        maleSocket = digitalActionManager->registerAction(actionBlock);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// LocalVariable / Formula
        actionBlock = new ActionBlock(digitalActionManager->getAutoSystemName(), "");
        actionBlock->AbstractNamedBean::setComment("LocalVariable / Formula");

        actionBlock->setAddressing(NamedBeanAddressing::LocalVariable);
        actionBlock->setLocalVariable("index");

        actionBlock->setOperationAddressing(NamedBeanAddressing::Formula);
        actionBlock->setOperationFormula("\"IT\"+index2");

        maleSocket = digitalActionManager->registerAction(actionBlock);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// Formula / Reference
        actionBlock = new ActionBlock(digitalActionManager->getAutoSystemName(), "");
        actionBlock->AbstractNamedBean::setComment("Formula / Reference");

        actionBlock->setAddressing(NamedBeanAddressing::Formula);
        actionBlock->setFormula("\"IT\"+index");

        actionBlock->setOperationAddressing(NamedBeanAddressing::Reference);
        actionBlock->setOperationReference("{IM2}");

        maleSocket = digitalActionManager->registerAction(actionBlock);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// Reference / Direct :: SetNullValue
        actionBlock = new ActionBlock(digitalActionManager->getAutoSystemName(), "");
        actionBlock->AbstractNamedBean::setComment("Reference / Direct :: SetAltColorOn");

        actionBlock->setAddressing(NamedBeanAddressing::Reference);
        actionBlock->setReference("{IM1}");

        actionBlock->setOperationAddressing(NamedBeanAddressing::Direct);
        actionBlock->setOperationDirect(ActionBlock::DirectOperation::SetNullValue);

        maleSocket = digitalActionManager->registerAction(actionBlock);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);


        ActionClock* actionClock = new ActionClock(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionClock);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// StartClock
        actionClock = new ActionClock(digitalActionManager->getAutoSystemName(), "");
        actionClock->AbstractNamedBean::setComment("StartClock");
        actionClock->setBeanState(ActionClock::ClockState::StartClock);

        maleSocket = digitalActionManager->registerAction(actionClock);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// StopClock
        actionClock = new ActionClock(digitalActionManager->getAutoSystemName(), "");
        actionClock->AbstractNamedBean::setComment("StopClock");
        actionClock->setBeanState(ActionClock::ClockState::StopClock);

        maleSocket = digitalActionManager->registerAction(actionClock);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// SetClock
        actionClock = new ActionClock(digitalActionManager->getAutoSystemName(), "");
        actionClock->AbstractNamedBean::setComment("SetClock");
        actionClock->setBeanState(ActionClock::ClockState::SetClock);
        actionClock->setClockTime(720);

        maleSocket = digitalActionManager->registerAction(actionClock);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);


        ActionLight* actionLight = new ActionLight(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionLight);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionLight = new ActionLight(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionLight);
        maleSocket->setErrorHandlingType(ErrorHandlingType::Default);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionLight = new ActionLight(digitalActionManager->getAutoSystemName(), "");
        actionLight->AbstractNamedBean::setComment("A comment");
        actionLight->setLight(light1);
        actionLight->setBeanState(ActionLight::LightState::Off);
        actionLight->setAddressing(NamedBeanAddressing::Direct);
        actionLight->setFormula("\"IT\"+index");
        actionLight->setLocalVariable("index");
        actionLight->setReference("{IM1}");
        actionLight->setStateAddressing(NamedBeanAddressing::LocalVariable);
        actionLight->setStateFormula("\"IT\"+index2");
        actionLight->setStateLocalVariable("index2");
        actionLight->setStateReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(actionLight);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionLight = new ActionLight(digitalActionManager->getAutoSystemName(), "");
        actionLight->AbstractNamedBean::setComment("A comment");
        actionLight->setLight(light1);
        actionLight->setBeanState(ActionLight::LightState::Off);
        actionLight->setAddressing(NamedBeanAddressing::LocalVariable);
        actionLight->setFormula("\"IT\"+index");
        actionLight->setLocalVariable("index");
        actionLight->setReference("{IM1}");
        actionLight->setStateAddressing(NamedBeanAddressing::Formula);
        actionLight->setStateFormula("\"IT\"+index2");
        actionLight->setStateLocalVariable("index2");
        actionLight->setStateReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(actionLight);
        maleSocket->setErrorHandlingType(ErrorHandlingType::LogError);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionLight = new ActionLight(digitalActionManager->getAutoSystemName(), "");
        actionLight->AbstractNamedBean::setComment("A comment");
        actionLight->setLight(light1);
        actionLight->setBeanState(ActionLight::LightState::Off);
        actionLight->setAddressing(NamedBeanAddressing::Formula);
        actionLight->setFormula("\"IT\"+index");
        actionLight->setLocalVariable("index");
        actionLight->setReference("{IM1}");
        actionLight->setStateAddressing(NamedBeanAddressing::Reference);
        actionLight->setStateFormula("\"IT\"+index2");
        actionLight->setStateLocalVariable("index2");
        actionLight->setStateReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(actionLight);
        maleSocket->setErrorHandlingType(ErrorHandlingType::LogErrorOnce);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionLight = new ActionLight(digitalActionManager->getAutoSystemName(), "");
        actionLight->AbstractNamedBean::setComment("A comment");
        actionLight->setLight(light1);
        actionLight->setBeanState(ActionLight::LightState::Off);
        actionLight->setAddressing(NamedBeanAddressing::Reference);
        actionLight->setFormula("\"IT\"+index");
        actionLight->setLocalVariable("index");
        actionLight->setReference("{IM1}");
        actionLight->setStateAddressing(NamedBeanAddressing::Direct);
        actionLight->setStateFormula("\"IT\"+index2");
        actionLight->setStateLocalVariable("index2");
        actionLight->setStateReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(actionLight);
        maleSocket->setErrorHandlingType(ErrorHandlingType::ShowDialogBox);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);


        actionLight = new ActionLight(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionLight);
        maleSocket->setErrorHandlingType(ErrorHandlingType::ThrowException);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

#if 0 // ActionLightIntensity not yet implemented
        ActionLightIntensity* actionLightIntensity = new ActionLightIntensity(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionLightIntensity);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionLightIntensity = new ActionLightIntensity(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionLightIntensity);
        maleSocket->setErrorHandlingType(ErrorHandlingType::Default);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionLightIntensity = new ActionLightIntensity(digitalActionManager->getAutoSystemName(), "");
        actionLightIntensity->AbstractNamedBean::setComment("A comment");
        actionLightIntensity.setLight(variableLight1);
        actionLightIntensity.setAddressing(NamedBeanAddressing::Direct);
        actionLightIntensity.setFormula("\"IT\"+index");
        actionLightIntensity.setLocalVariable("index");
        actionLightIntensity.setReference("{IM1}");
        maleSocket = digitalActionManager->registerAction(actionLightIntensity);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionLightIntensity = new ActionLightIntensity(digitalActionManager->getAutoSystemName(), "");
        actionLightIntensity->AbstractNamedBean::setComment("A comment");
        actionLightIntensity.setLight(variableLight1);
        actionLightIntensity.setAddressing(NamedBeanAddressing::LocalVariable);
        actionLightIntensity.setFormula("\"IT\"+index");
        actionLightIntensity.setLocalVariable("index");
        actionLightIntensity.setReference("{IM1}");
        maleSocket = digitalActionManager->registerAction(actionLightIntensity);
        maleSocket->setErrorHandlingType(ErrorHandlingType::LogError);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionLightIntensity = new ActionLightIntensity(digitalActionManager->getAutoSystemName(), "");
        actionLightIntensity->AbstractNamedBean::setComment("A comment");
        actionLightIntensity.setLight(variableLight1);
        actionLightIntensity.setAddressing(NamedBeanAddressing::Formula);
        actionLightIntensity.setFormula("\"IT\"+index");
        actionLightIntensity.setLocalVariable("index");
        actionLightIntensity.setReference("{IM1}");
        maleSocket = digitalActionManager->registerAction(actionLightIntensity);
        maleSocket->setErrorHandlingType(ErrorHandlingType::LogErrorOnce);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionLightIntensity = new ActionLightIntensity(digitalActionManager->getAutoSystemName(), "");
        actionLightIntensity->AbstractNamedBean::setComment("A comment");
        actionLightIntensity.setLight(variableLight1);
        actionLightIntensity.setAddressing(NamedBeanAddressing::Reference);
        actionLightIntensity.setFormula("\"IT\"+index");
        actionLightIntensity.setLocalVariable("index");
        actionLightIntensity.setReference("{IM1}");
        maleSocket = digitalActionManager->registerAction(actionLightIntensity);
        maleSocket->setErrorHandlingType(ErrorHandlingType::ShowDialogBox);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

#endif
#if 1
        ActionListenOnBeans* actionListenOnBeans = new ActionListenOnBeans(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionListenOnBeans);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionListenOnBeans = new ActionListenOnBeans(digitalActionManager->getAutoSystemName(), "");
        actionListenOnBeans->AbstractNamedBean::setComment("A comment");
        actionListenOnBeans->addReference("Light:"+light1->getSystemName());
        maleSocket = digitalActionManager->registerAction(actionListenOnBeans);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionListenOnBeans = new ActionListenOnBeans(digitalActionManager->getAutoSystemName(), "");
        actionListenOnBeans->AbstractNamedBean::setComment("A comment");
        actionListenOnBeans->addReference("Light:"+light2->getUserName());
        maleSocket = digitalActionManager->registerAction(actionListenOnBeans);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionListenOnBeans = new ActionListenOnBeans(digitalActionManager->getAutoSystemName(), "");
        actionListenOnBeans->AbstractNamedBean::setComment("A comment");
        actionListenOnBeans->addReference("Memory:"+memory1->getSystemName());
        maleSocket = digitalActionManager->registerAction(actionListenOnBeans);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionListenOnBeans = new ActionListenOnBeans(digitalActionManager->getAutoSystemName(), "");
        actionListenOnBeans->AbstractNamedBean::setComment("A comment");
        actionListenOnBeans->addReference("Memory:"+memory2->getUserName());
        maleSocket = digitalActionManager->registerAction(actionListenOnBeans);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionListenOnBeans = new ActionListenOnBeans(digitalActionManager->getAutoSystemName(), "");
        actionListenOnBeans->AbstractNamedBean::setComment("A comment");
        actionListenOnBeans->addReference("Sensor:"+sensor1->getSystemName());
        maleSocket = digitalActionManager->registerAction(actionListenOnBeans);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionListenOnBeans = new ActionListenOnBeans(digitalActionManager->getAutoSystemName(), "");
        actionListenOnBeans->AbstractNamedBean::setComment("A comment");
        actionListenOnBeans->addReference("Sensor:"+sensor2->getUserName());
        maleSocket = digitalActionManager->registerAction(actionListenOnBeans);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionListenOnBeans = new ActionListenOnBeans(digitalActionManager->getAutoSystemName(), "");
        actionListenOnBeans->AbstractNamedBean::setComment("A comment");
        actionListenOnBeans->addReference("Turnout:"+turnout1->getSystemName());
        maleSocket = digitalActionManager->registerAction(actionListenOnBeans);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);
        actionListenOnBeans = new ActionListenOnBeans(digitalActionManager->getAutoSystemName(), "");
        actionListenOnBeans->AbstractNamedBean::setComment("A comment");
        actionListenOnBeans->addReference("Turnout:"+turnout2->getUserName());
        maleSocket = digitalActionManager->registerAction(actionListenOnBeans);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        ActionLocalVariable* actionLocalVariable = new ActionLocalVariable(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionLocalVariable);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionLocalVariable = new ActionLocalVariable(digitalActionManager->getAutoSystemName(), "");
        actionLocalVariable->AbstractNamedBean::setComment("A comment");
        actionLocalVariable->setLocalVariable("result");
        actionLocalVariable->setVariableOperation(ActionLocalVariable::VariableOperation::CalculateFormula);
        actionLocalVariable->setConstantValue("1");
        actionLocalVariable->setOtherLocalVariable("SomeVar");
        actionLocalVariable->setMemory(memory3);
        actionLocalVariable->setFormula("a+b");
        maleSocket = digitalActionManager->registerAction(actionLocalVariable);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionLocalVariable = new ActionLocalVariable(digitalActionManager->getAutoSystemName(), "");
        actionLocalVariable->AbstractNamedBean::setComment("A comment");
        actionLocalVariable->setLocalVariable("result");
        actionLocalVariable->setVariableOperation(ActionLocalVariable::VariableOperation::CopyMemoryToVariable);
        actionLocalVariable->setConstantValue("1");
        actionLocalVariable->setOtherLocalVariable("SomeVar");
        actionLocalVariable->setMemory(memory3);
        actionLocalVariable->setFormula("a+b");
        maleSocket = digitalActionManager->registerAction(actionLocalVariable);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionLocalVariable = new ActionLocalVariable(digitalActionManager->getAutoSystemName(), "");
        actionLocalVariable->AbstractNamedBean::setComment("A comment");
        actionLocalVariable->setLocalVariable("result");
        actionLocalVariable->setVariableOperation(ActionLocalVariable::VariableOperation::CopyVariableToVariable);
        actionLocalVariable->setConstantValue("1");
        actionLocalVariable->setOtherLocalVariable("SomeVar");
        actionLocalVariable->setMemory(memory3);
        actionLocalVariable->setFormula("a+b");
        maleSocket = digitalActionManager->registerAction(actionLocalVariable);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionLocalVariable = new ActionLocalVariable(digitalActionManager->getAutoSystemName(), "");
        actionLocalVariable->AbstractNamedBean::setComment("A comment");
        actionLocalVariable->setLocalVariable("result");
        actionLocalVariable->setVariableOperation(ActionLocalVariable::VariableOperation::SetToNull);
        actionLocalVariable->setConstantValue("1");
        actionLocalVariable->setOtherLocalVariable("SomeVar");
        actionLocalVariable->setMemory(memory3);
        actionLocalVariable->setFormula("a+b");
        maleSocket = digitalActionManager->registerAction(actionLocalVariable);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionLocalVariable = new ActionLocalVariable(digitalActionManager->getAutoSystemName(), "");
        actionLocalVariable->AbstractNamedBean::setComment("A comment");
        actionLocalVariable->setLocalVariable("result");
        actionLocalVariable->setVariableOperation(ActionLocalVariable::VariableOperation::SetToString);
        actionLocalVariable->setConstantValue("1");
        actionLocalVariable->setOtherLocalVariable("SomeVar");
        actionLocalVariable->setMemory(memory3);
        actionLocalVariable->setFormula("a+b");
        maleSocket = digitalActionManager->registerAction(actionLocalVariable);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

#endif
        ActionMemory* actionMemory = new ActionMemory(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionMemory);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionMemory = new ActionMemory(digitalActionManager->getAutoSystemName(), "");
        actionMemory->AbstractNamedBean::setComment("A comment");
        actionMemory->setMemory(memory1);
        actionMemory->setAddressing(NamedBeanAddressing::Direct);
        actionMemory->setFormula("\"IT\"+index");
        actionMemory->setLocalVariable("index");
        actionMemory->setReference("{IM1}");
        actionMemory->setMemoryOperation(ActionMemory::MemoryOperation::CalculateFormula);
        actionMemory->setOtherMemory(memory3);
        actionMemory->setOtherConstantValue("Some string");
        actionMemory->setOtherFormula("n + 3");
        actionMemory->setOtherLocalVariable("Somevar");
        maleSocket = digitalActionManager->registerAction(actionMemory);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionMemory = new ActionMemory(digitalActionManager->getAutoSystemName(), "");
        actionMemory->AbstractNamedBean::setComment("A comment");
        actionMemory->setMemory(memory1);
        actionMemory->setAddressing(NamedBeanAddressing::Formula);
        actionMemory->setFormula("\"IT\"+index");
        actionMemory->setLocalVariable("index");
        actionMemory->setReference("{IM1}");
        actionMemory->setMemoryOperation(ActionMemory::MemoryOperation::CopyMemoryToMemory);
        actionMemory->setOtherMemory(memory3);
        actionMemory->setOtherConstantValue("Some string");
        actionMemory->setOtherFormula("n + 3");
        actionMemory->setOtherLocalVariable("Somevar");
        maleSocket = digitalActionManager->registerAction(actionMemory);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionMemory = new ActionMemory(digitalActionManager->getAutoSystemName(), "");
        actionMemory->AbstractNamedBean::setComment("A comment");
        actionMemory->setMemory(memory1);
        actionMemory->setAddressing(NamedBeanAddressing::LocalVariable);
        actionMemory->setFormula("\"IT\"+index");
        actionMemory->setLocalVariable("index");
        actionMemory->setReference("{IM1}");
        actionMemory->setMemoryOperation(ActionMemory::MemoryOperation::CopyVariableToMemory);
        actionMemory->setOtherMemory(memory3);
        actionMemory->setOtherConstantValue("Some string");
        actionMemory->setOtherFormula("n + 3");
        actionMemory->setOtherLocalVariable("Somevar");
        maleSocket = digitalActionManager->registerAction(actionMemory);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionMemory = new ActionMemory(digitalActionManager->getAutoSystemName(), "");
        actionMemory->AbstractNamedBean::setComment("A comment");
        actionMemory->setMemory(memory1);
        actionMemory->setAddressing(NamedBeanAddressing::Reference);
        actionMemory->setFormula("\"IT\"+index");
        actionMemory->setLocalVariable("index");
        actionMemory->setReference("{IM1}");
        actionMemory->setMemoryOperation(ActionMemory::MemoryOperation::SetToNull);
        actionMemory->setOtherMemory(memory3);
        actionMemory->setOtherConstantValue("Some string");
        actionMemory->setOtherFormula("n + 3");
        actionMemory->setOtherLocalVariable("Somevar");
        maleSocket = digitalActionManager->registerAction(actionMemory);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionMemory = new ActionMemory(digitalActionManager->getAutoSystemName(), "");
        actionMemory->AbstractNamedBean::setComment("A comment");
        actionMemory->setMemory(memory1);
        actionMemory->setAddressing(NamedBeanAddressing::Direct);
        actionMemory->setFormula("\"IT\"+index");
        actionMemory->setLocalVariable("index");
        actionMemory->setReference("{IM1}");
        actionMemory->setMemoryOperation(ActionMemory::MemoryOperation::SetToString);
        actionMemory->setOtherMemory(memory3);
        actionMemory->setOtherConstantValue("Some string");
        actionMemory->setOtherFormula("n + 3");
        actionMemory->setOtherLocalVariable("Somevar");
        maleSocket = digitalActionManager->registerAction(actionMemory);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);
#if 0 // not yet implemented

        ActionOBlock actionOBlock = new ActionOBlock(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionOBlock);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionOBlock = new ActionOBlock(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionOBlock);
        maleSocket->setErrorHandlingType(ErrorHandlingType::Default);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionOBlock = new ActionOBlock(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionOBlock);
        maleSocket->setErrorHandlingType(ErrorHandlingType::ThrowException);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// Direct / Direct / Direct :: SetValue
        actionOBlock = new ActionOBlock(digitalActionManager->getAutoSystemName(), "");
        actionOBlock->AbstractNamedBean::setComment("Direct / Direct / Direct :: SetValue");

        actionOBlock.setAddressing(NamedBeanAddressing::Direct);
        actionOBlock.setOBlock("OB99");

        actionOBlock.setOperationAddressing(NamedBeanAddressing::Direct);
        actionOBlock.setOperationDirect(ActionOBlock.DirectOperation.SetValue);

        actionOBlock.setDataAddressing(NamedBeanAddressing::Direct);
        actionOBlock.setOBlockValue("ABC");

        maleSocket = digitalActionManager->registerAction(actionOBlock);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// Direct / Direct :: ClearError
        actionOBlock = new ActionOBlock(digitalActionManager->getAutoSystemName(), "");
        actionOBlock->AbstractNamedBean::setComment("Direct / Direct :: ClearError");

        actionOBlock.setAddressing(NamedBeanAddressing::Direct);
        actionOBlock.setOBlock("OB99");

        actionOBlock.setOperationAddressing(NamedBeanAddressing::Direct);
        actionOBlock.setOperationDirect(ActionOBlock.DirectOperation.ClearError);

        maleSocket = digitalActionManager->registerAction(actionOBlock);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// Direct / LocalVariable
        actionOBlock = new ActionOBlock(digitalActionManager->getAutoSystemName(), "");
        actionOBlock->AbstractNamedBean::setComment("Direct / LocalVariable");

        actionOBlock.setAddressing(NamedBeanAddressing::Direct);
        actionOBlock.setOBlock("OB99");

        actionOBlock.setOperationAddressing(NamedBeanAddressing::LocalVariable);
        actionOBlock.setOperationLocalVariable("index2");

        maleSocket = digitalActionManager->registerAction(actionOBlock);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// LocalVariable / Formula
        actionOBlock = new ActionOBlock(digitalActionManager->getAutoSystemName(), "");
        actionOBlock->AbstractNamedBean::setComment("LocalVariable / Formula");

        actionOBlock.setAddressing(NamedBeanAddressing::LocalVariable);
        actionOBlock.setLocalVariable("index");

        actionOBlock.setOperationAddressing(NamedBeanAddressing::Formula);
        actionOBlock.setOperationFormula("\"IT\"+index2");

        maleSocket = digitalActionManager->registerAction(actionOBlock);
        maleSocket->setErrorHandlingType(ErrorHandlingType::LogError);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// Formula / Reference
        actionOBlock = new ActionOBlock(digitalActionManager->getAutoSystemName(), "");
        actionOBlock->AbstractNamedBean::setComment("Formula / Reference");

        actionOBlock.setAddressing(NamedBeanAddressing::Formula);
        actionOBlock.setFormula("\"IT\"+index");

        actionOBlock.setOperationAddressing(NamedBeanAddressing::Reference);
        actionOBlock.setOperationReference("{IM2}");

        maleSocket = digitalActionManager->registerAction(actionOBlock);
        maleSocket->setErrorHandlingType(ErrorHandlingType::LogErrorOnce);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// Reference / Direct :: SetOutOfService
        actionOBlock = new ActionOBlock(digitalActionManager->getAutoSystemName(), "");
        actionOBlock->AbstractNamedBean::setComment("Reference / Direct :: SetOutOfService");

        actionOBlock.setAddressing(NamedBeanAddressing::Reference);
        actionOBlock.setReference("{IM1}");

        actionOBlock.setOperationAddressing(NamedBeanAddressing::Direct);
        actionOBlock.setOperationDirect(ActionOBlock.DirectOperation.SetOutOfService);

        maleSocket = digitalActionManager->registerAction(actionOBlock);
        maleSocket->setErrorHandlingType(ErrorHandlingType::ShowDialogBox);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

#endif
        ActionPower* actionPower = new ActionPower(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionPower);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionPower = new ActionPower(digitalActionManager->getAutoSystemName(), "");
        actionPower->AbstractNamedBean::setComment("A comment");
        actionPower->setBeanState(ActionPower::PowerState::Off);
        maleSocket = digitalActionManager->registerAction(actionPower);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionPower = new ActionPower(digitalActionManager->getAutoSystemName(), "");
        actionPower->AbstractNamedBean::setComment("A comment");
        actionPower->setBeanState(ActionPower::PowerState::On);
        maleSocket = digitalActionManager->registerAction(actionPower);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

#if 0 // not yet implemented
#ifdef SCRIPTING_ENABLED
        ActionScript simpleScript = new ActionScript(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(simpleScript);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        simpleScript = new ActionScript(digitalActionManager->getAutoSystemName(), "");
        simpleScript->AbstractNamedBean::setComment("A comment");
        simpleScript.setScript("import java\n");
        simpleScript.setOperationAddressing(NamedBeanAddressing::Direct);
        simpleScript.setOperationFormula("a+b");
        simpleScript.setOperationLocalVariable("myVar");
        simpleScript.setOperationReference("{M1}");
        simpleScript.setScriptAddressing(NamedBeanAddressing::Formula);
        simpleScript.setScriptFormula("c+d");
        simpleScript.setScriptLocalVariable("myOtherVar");
        simpleScript.setScriptReference("{M2}");
        maleSocket = digitalActionManager->registerAction(simpleScript);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        simpleScript = new ActionScript(digitalActionManager->getAutoSystemName(), "");
        simpleScript->AbstractNamedBean::setComment("A comment");
        simpleScript.setScript("myFile.py");
        simpleScript.setOperationAddressing(NamedBeanAddressing::Formula);
        simpleScript.setOperationFormula("a+b");
        simpleScript.setOperationLocalVariable("myVar");
        simpleScript.setOperationReference("{M1}");
        simpleScript.setScriptAddressing(NamedBeanAddressing::LocalVariable);
        simpleScript.setScriptFormula("c+d");
        simpleScript.setScriptLocalVariable("myOtherVar");
        simpleScript.setScriptReference("{M2}");
        maleSocket = digitalActionManager->registerAction(simpleScript);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        simpleScript = new ActionScript(digitalActionManager->getAutoSystemName(), "");
        simpleScript->AbstractNamedBean::setComment("A comment");
        simpleScript.setScript("import java\n");
        simpleScript.setOperationAddressing(NamedBeanAddressing::LocalVariable);
        simpleScript.setOperationFormula("a+b");
        simpleScript.setOperationLocalVariable("myVar");
        simpleScript.setOperationReference("{M1}");
        simpleScript.setScriptAddressing(NamedBeanAddressing::Reference);
        simpleScript.setScriptFormula("c+d");
        simpleScript.setScriptLocalVariable("myOtherVar");
        simpleScript.setScriptReference("{M2}");
        maleSocket = digitalActionManager->registerAction(simpleScript);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        simpleScript = new ActionScript(digitalActionManager->getAutoSystemName(), "");
        simpleScript->AbstractNamedBean::setComment("A comment");
        simpleScript.setScript("import java\n");
        simpleScript.setOperationAddressing(NamedBeanAddressing::Reference);
        simpleScript.setOperationFormula("a+b");
        simpleScript.setOperationLocalVariable("myVar");
        simpleScript.setOperationReference("{M1}");
        simpleScript.setScriptAddressing(NamedBeanAddressing::Direct);
        simpleScript.setScriptFormula("c+d");
        simpleScript.setScriptLocalVariable("myOtherVar");
        simpleScript.setScriptReference("{M2}");
        maleSocket = digitalActionManager->registerAction(simpleScript);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);
#endif
#endif
        ActionSensor* actionSensor = new ActionSensor(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionSensor);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionSensor = new ActionSensor(digitalActionManager->getAutoSystemName(), "");
        actionSensor->AbstractNamedBean::setComment("A comment");
        actionSensor->setSensor(sensor1);
        actionSensor->setBeanState(ActionSensor::SensorState::Inactive);
        actionSensor->setAddressing(NamedBeanAddressing::Direct);
        actionSensor->setFormula("\"IT\"+index");
        actionSensor->setLocalVariable("index");
        actionSensor->setReference("{IM1}");
        actionSensor->setStateAddressing(NamedBeanAddressing::LocalVariable);
        actionSensor->setStateFormula("\"IT\"+index2");
        actionSensor->setStateLocalVariable("index2");
        actionSensor->setStateReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(actionSensor);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionSensor = new ActionSensor(digitalActionManager->getAutoSystemName(), "");
        actionSensor->AbstractNamedBean::setComment("A comment");
        actionSensor->setSensor(sensor1);
        actionSensor->setBeanState(ActionSensor::SensorState::Inactive);
        actionSensor->setAddressing(NamedBeanAddressing::LocalVariable);
        actionSensor->setFormula("\"IT\"+index");
        actionSensor->setLocalVariable("index");
        actionSensor->setReference("{IM1}");
        actionSensor->setStateAddressing(NamedBeanAddressing::Formula);
        actionSensor->setStateFormula("\"IT\"+index2");
        actionSensor->setStateLocalVariable("index2");
        actionSensor->setStateReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(actionSensor);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionSensor = new ActionSensor(digitalActionManager->getAutoSystemName(), "");
        actionSensor->AbstractNamedBean::setComment("A comment");
        actionSensor->setSensor(sensor1);
        actionSensor->setBeanState(ActionSensor::SensorState::Inactive);
        actionSensor->setAddressing(NamedBeanAddressing::Formula);
        actionSensor->setFormula("\"IT\"+index");
        actionSensor->setLocalVariable("index");
        actionSensor->setReference("{IM1}");
        actionSensor->setStateAddressing(NamedBeanAddressing::Reference);
        actionSensor->setStateFormula("\"IT\"+index2");
        actionSensor->setStateLocalVariable("index2");
        actionSensor->setStateReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(actionSensor);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionSensor = new ActionSensor(digitalActionManager->getAutoSystemName(), "");
        actionSensor->AbstractNamedBean::setComment("A comment");
        actionSensor->setSensor(sensor1);
        actionSensor->setBeanState(ActionSensor::SensorState::Inactive);
        actionSensor->setAddressing(NamedBeanAddressing::Reference);
        actionSensor->setFormula("\"IT\"+index");
        actionSensor->setLocalVariable("index");
        actionSensor->setReference("{IM1}");
        actionSensor->setStateAddressing(NamedBeanAddressing::Direct);
        actionSensor->setStateFormula("\"IT\"+index2");
        actionSensor->setStateLocalVariable("index2");
        actionSensor->setStateReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(actionSensor);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);


        ActionSignalHead* actionSignalHead = new ActionSignalHead(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionSignalHead);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionSignalHead = new ActionSignalHead(digitalActionManager->getAutoSystemName(), "");
        actionSignalHead->AbstractNamedBean::setComment("A comment");
        actionSignalHead->setSignalHead("IH1");
        actionSignalHead->setAddressing(NamedBeanAddressing::Direct);
        actionSignalHead->setFormula("\"IT\"+index");
        actionSignalHead->setLocalVariable("index");
        actionSignalHead->setReference("{IM1}");
        actionSignalHead->setOperationAddressing(NamedBeanAddressing::LocalVariable);
        actionSignalHead->setOperationFormula("\"IT\"+index2");
        actionSignalHead->setOperationLocalVariable("index2");
        actionSignalHead->setOperationReference("{IM2}");
        actionSignalHead->setAppearanceAddressing(NamedBeanAddressing::Formula);
        actionSignalHead->setAppearance(SignalHead::FLASHGREEN);
        actionSignalHead->setAppearanceFormula("\"IT\"+index3");
        actionSignalHead->setAppearanceLocalVariable("index3");
        actionSignalHead->setAppearanceReference("{IM3}");
        actionSignalHead->setExampleSignalHead("IH2");
        maleSocket = digitalActionManager->registerAction(actionSignalHead);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionSignalHead = new ActionSignalHead(digitalActionManager->getAutoSystemName(), "");
        actionSignalHead->AbstractNamedBean::setComment("A comment");
        actionSignalHead->setSignalHead("IH1");
        actionSignalHead->setAddressing(NamedBeanAddressing::LocalVariable);
        actionSignalHead->setFormula("\"IT\"+index");
        actionSignalHead->setLocalVariable("index");
        actionSignalHead->setReference("{IM1}");
        actionSignalHead->setOperationAddressing(NamedBeanAddressing::Formula);
        actionSignalHead->setOperationFormula("\"IT\"+index2");
        actionSignalHead->setOperationLocalVariable("index2");
        actionSignalHead->setOperationReference("{IM2}");
        actionSignalHead->setAppearanceAddressing(NamedBeanAddressing::Reference);
        actionSignalHead->setAppearance(SignalHead::FLASHLUNAR);
        actionSignalHead->setAppearanceFormula("\"IT\"+index3");
        actionSignalHead->setAppearanceLocalVariable("index3");
        actionSignalHead->setAppearanceReference("{IM3}");
        maleSocket = digitalActionManager->registerAction(actionSignalHead);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionSignalHead = new ActionSignalHead(digitalActionManager->getAutoSystemName(), "");
        actionSignalHead->AbstractNamedBean::setComment("A comment");
        actionSignalHead->setSignalHead("IH1");
        actionSignalHead->setAddressing(NamedBeanAddressing::Formula);
        actionSignalHead->setFormula("\"IT\"+index");
        actionSignalHead->setLocalVariable("index");
        actionSignalHead->setReference("{IM1}");
        actionSignalHead->setOperationAddressing(NamedBeanAddressing::Reference);
        actionSignalHead->setOperationFormula("\"IT\"+index2");
        actionSignalHead->setOperationLocalVariable("index2");
        actionSignalHead->setOperationReference("{IM2}");
        actionSignalHead->setAppearanceAddressing(NamedBeanAddressing::Direct);
        actionSignalHead->setAppearance(SignalHead::FLASHRED);
        actionSignalHead->setAppearanceFormula("\"IT\"+index3");
        actionSignalHead->setAppearanceLocalVariable("index3");
        actionSignalHead->setAppearanceReference("{IM3}");
        maleSocket = digitalActionManager->registerAction(actionSignalHead);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionSignalHead = new ActionSignalHead(digitalActionManager->getAutoSystemName(), "");
        actionSignalHead->AbstractNamedBean::setComment("A comment");
        actionSignalHead->setSignalHead("IH1");
        actionSignalHead->setAddressing(NamedBeanAddressing::Reference);
        actionSignalHead->setFormula("\"IT\"+index");
        actionSignalHead->setLocalVariable("index");
        actionSignalHead->setReference("{IM1}");
        actionSignalHead->setOperationAddressing(NamedBeanAddressing::Direct);
        actionSignalHead->setOperationFormula("\"IT\"+index2");
        actionSignalHead->setOperationLocalVariable("index2");
        actionSignalHead->setOperationReference("{IM2}");
        actionSignalHead->setAppearanceAddressing(NamedBeanAddressing::LocalVariable);
        actionSignalHead->setAppearance(SignalHead::FLASHYELLOW);
        actionSignalHead->setAppearanceFormula("\"IT\"+index3");
        actionSignalHead->setAppearanceLocalVariable("index3");
        actionSignalHead->setAppearanceReference("{IM3}");
        maleSocket = digitalActionManager->registerAction(actionSignalHead);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

#if 0 // not yet implemented
        ActionSignalMast actionSignalMast = new ActionSignalMast(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionSignalMast);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionSignalMast = new ActionSignalMast(digitalActionManager->getAutoSystemName(), "");
        actionSignalMast->AbstractNamedBean::setComment("A comment");
        actionSignalMast.setSignalMast("IF$shsm:AAR-1946:CPL(IH1)");
        actionSignalMast.setAddressing(NamedBeanAddressing::Direct);
        actionSignalMast.setFormula("\"IT\"+index");
        actionSignalMast.setLocalVariable("index");
        actionSignalMast.setReference("{IM1}");
        actionSignalMast.setOperationAddressing(NamedBeanAddressing::LocalVariable);
        actionSignalMast.setOperationFormula("\"IT\"+index2");
        actionSignalMast.setOperationLocalVariable("index2");
        actionSignalMast.setOperationReference("{IM2}");
        actionSignalMast.setAspectAddressing(NamedBeanAddressing::Formula);
        actionSignalMast.setAspect("Medium Approach Slow");
        actionSignalMast.setAspectFormula("\"IT\"+index3");
        actionSignalMast.setAspectLocalVariable("index3");
        actionSignalMast.setAspectReference("{IM3}");
        actionSignalMast.setExampleSignalMast("IF$shsm:AAR-1946:CPL(IH1)");
        maleSocket = digitalActionManager->registerAction(actionSignalMast);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionSignalMast = new ActionSignalMast(digitalActionManager->getAutoSystemName(), "");
        actionSignalMast->AbstractNamedBean::setComment("A comment");
        actionSignalMast.setSignalMast("IF$shsm:AAR-1946:CPL(IH1)");
        actionSignalMast.setAddressing(NamedBeanAddressing::LocalVariable);
        actionSignalMast.setFormula("\"IT\"+index");
        actionSignalMast.setLocalVariable("index");
        actionSignalMast.setReference("{IM1}");
        actionSignalMast.setOperationAddressing(NamedBeanAddressing::Formula);
        actionSignalMast.setOperationFormula("\"IT\"+index2");
        actionSignalMast.setOperationLocalVariable("index2");
        actionSignalMast.setOperationReference("{IM2}");
        actionSignalMast.setAspectAddressing(NamedBeanAddressing::Reference);
        actionSignalMast.setAspect("Medium Approach");
        actionSignalMast.setAspectFormula("\"IT\"+index3");
        actionSignalMast.setAspectLocalVariable("index3");
        actionSignalMast.setAspectReference("{IM3}");
        maleSocket = digitalActionManager->registerAction(actionSignalMast);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionSignalMast = new ActionSignalMast(digitalActionManager->getAutoSystemName(), "");
        actionSignalMast->AbstractNamedBean::setComment("A comment");
        actionSignalMast.setSignalMast("IF$shsm:AAR-1946:CPL(IH1)");
        actionSignalMast.setAddressing(NamedBeanAddressing::Formula);
        actionSignalMast.setFormula("\"IT\"+index");
        actionSignalMast.setLocalVariable("index");
        actionSignalMast.setReference("{IM1}");
        actionSignalMast.setOperationAddressing(NamedBeanAddressing::Reference);
        actionSignalMast.setOperationFormula("\"IT\"+index2");
        actionSignalMast.setOperationLocalVariable("index2");
        actionSignalMast.setOperationReference("{IM2}");
        actionSignalMast.setAspectAddressing(NamedBeanAddressing::Direct);
        actionSignalMast.setAspect("Approach");
        actionSignalMast.setAspectFormula("\"IT\"+index3");
        actionSignalMast.setAspectLocalVariable("index3");
        actionSignalMast.setAspectReference("{IM3}");
        maleSocket = digitalActionManager->registerAction(actionSignalMast);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionSignalMast = new ActionSignalMast(digitalActionManager->getAutoSystemName(), "");
        actionSignalMast->AbstractNamedBean::setComment("A comment");
        actionSignalMast.setSignalMast("IF$shsm:AAR-1946:CPL(IH1)");
        actionSignalMast.setAddressing(NamedBeanAddressing::Reference);
        actionSignalMast.setFormula("\"IT\"+index");
        actionSignalMast.setLocalVariable("index");
        actionSignalMast.setReference("{IM1}");
        actionSignalMast.setOperationAddressing(NamedBeanAddressing::Direct);
        actionSignalMast.setOperationFormula("\"IT\"+index2");
        actionSignalMast.setOperationLocalVariable("index2");
        actionSignalMast.setOperationReference("{IM2}");
        actionSignalMast.setAspectAddressing(NamedBeanAddressing::LocalVariable);
        actionSignalMast.setAspect("Medium Approach Slow");
        actionSignalMast.setAspectFormula("\"IT\"+index3");
        actionSignalMast.setAspectLocalVariable("index3");
        actionSignalMast.setAspectReference("{IM3}");
        maleSocket = digitalActionManager->registerAction(actionSignalMast);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);


        ActionSound simpleSound = new ActionSound(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(simpleSound);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        simpleSound = new ActionSound(digitalActionManager->getAutoSystemName(), "");
        simpleSound->AbstractNamedBean::setComment("A comment");
        simpleSound.setSound("bell.wav\n");
        simpleSound.setOperationAddressing(NamedBeanAddressing::Direct);
        simpleSound.setOperationFormula("a+b");
        simpleSound.setOperationLocalVariable("myVar");
        simpleSound.setOperationReference("{M1}");
        simpleSound.setSoundAddressing(NamedBeanAddressing::Formula);
        simpleSound.setSoundFormula("c+d");
        simpleSound.setSoundLocalVariable("myOtherVar");
        simpleSound.setSoundReference("{M2}");
        maleSocket = digitalActionManager->registerAction(simpleSound);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        simpleSound = new ActionSound(digitalActionManager->getAutoSystemName(), "");
        simpleSound->AbstractNamedBean::setComment("A comment");
        simpleSound.setSound("bell.wav\n");
        simpleSound.setOperationAddressing(NamedBeanAddressing::Formula);
        simpleSound.setOperationFormula("a+b");
        simpleSound.setOperationLocalVariable("myVar");
        simpleSound.setOperationReference("{M1}");
        simpleSound.setSoundAddressing(NamedBeanAddressing::LocalVariable);
        simpleSound.setSoundFormula("c+d");
        simpleSound.setSoundLocalVariable("myOtherVar");
        simpleSound.setSoundReference("{M2}");
        maleSocket = digitalActionManager->registerAction(simpleSound);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        simpleSound = new ActionSound(digitalActionManager->getAutoSystemName(), "");
        simpleSound->AbstractNamedBean::setComment("A comment");
        simpleSound.setSound("bell.wav\n");
        simpleSound.setOperationAddressing(NamedBeanAddressing::LocalVariable);
        simpleSound.setOperationFormula("a+b");
        simpleSound.setOperationLocalVariable("myVar");
        simpleSound.setOperationReference("{M1}");
        simpleSound.setSoundAddressing(NamedBeanAddressing::Reference);
        simpleSound.setSoundFormula("c+d");
        simpleSound.setSoundLocalVariable("myOtherVar");
        simpleSound.setSoundReference("{M2}");
        maleSocket = digitalActionManager->registerAction(simpleSound);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        simpleSound = new ActionSound(digitalActionManager->getAutoSystemName(), "");
        simpleSound->AbstractNamedBean::setComment("A comment");
        simpleSound.setSound("bell.wav\n");
        simpleSound.setOperationAddressing(NamedBeanAddressing::Reference);
        simpleSound.setOperationFormula("a+b");
        simpleSound.setOperationLocalVariable("myVar");
        simpleSound.setOperationReference("{M1}");
        simpleSound.setSoundAddressing(NamedBeanAddressing::Direct);
        simpleSound.setSoundFormula("c+d");
        simpleSound.setSoundLocalVariable("myOtherVar");
        simpleSound.setSoundReference("{M2}");
        maleSocket = digitalActionManager->registerAction(simpleSound);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);


        ActionThrottle actionThrottle = new ActionThrottle(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionThrottle);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionThrottle = new ActionThrottle(digitalActionManager->getAutoSystemName(), "");
        actionThrottle->AbstractNamedBean::setComment("A comment");
        maleSocket = digitalActionManager->registerAction(actionThrottle);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

#endif

        ActionTimer* actionTimer = new ActionTimer(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionTimer);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionTimer = new ActionTimer(digitalActionManager->getAutoSystemName(), "");
        actionTimer->AbstractNamedBean::setComment("A comment");
        actionTimer->setDelay(0, 100);
        actionTimer->setStartImmediately(false);
        actionTimer->setRunContinuously(true);
        maleSocket = digitalActionManager->registerAction(actionTimer);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionTimer = new ActionTimer(digitalActionManager->getAutoSystemName(), "");
        actionTimer->AbstractNamedBean::setComment("A comment");
        actionTimer->setNumActions(3);
        actionTimer->setDelay(0, 2400);
        actionTimer->setDelay(1, 10);
        actionTimer->setDelay(2, 500);
        actionTimer->setStartImmediately(true);
        actionTimer->setRunContinuously(false);
        actionTimer->setNumActions(2);
        maleSocket = digitalActionManager->registerAction(actionTimer);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);


        And* andTemp1 = new And(digitalExpressionManager->getAutoSystemName(), "");
        andTemp1->AbstractNamedBean::setComment("Start expression");
        maleSocket = digitalExpressionManager->registerExpression(andTemp1);
        maleSocket->setEnabled(false);
        actionTimer->getChild(0)->_connect(maleSocket);

        andTemp1 = new And(digitalExpressionManager->getAutoSystemName(), "");
        andTemp1->AbstractNamedBean::setComment("Stop expression");
        maleSocket = digitalExpressionManager->registerExpression(andTemp1);
        actionTimer->getChild(1)->_connect(maleSocket);

        DigitalMany* manyTemp1 = new DigitalMany(digitalActionManager->getAutoSystemName(), "");
        manyTemp1->AbstractNamedBean::setComment("Action socket 1");
        maleSocket = digitalActionManager->registerAction(manyTemp1);
        maleSocket->setEnabled(false);
        actionTimer->getChild(2)->_connect(maleSocket);

        manyTemp1 = new DigitalMany(digitalActionManager->getAutoSystemName(), "");
        manyTemp1->AbstractNamedBean::setComment("Action socket 2");
        maleSocket = digitalActionManager->registerAction(manyTemp1);
        actionTimer->getChild(3)->_connect(maleSocket);


        ActionTurnout* actionTurnout = new ActionTurnout(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionTurnout);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionTurnout = new ActionTurnout(digitalActionManager->getAutoSystemName(), "");
        actionTurnout->AbstractNamedBean::setComment("A comment");
        actionTurnout->setTurnout(turnout1);
        actionTurnout->setBeanState(ActionTurnout::TurnoutState::Closed);
        actionTurnout->setAddressing(NamedBeanAddressing::Direct);
        actionTurnout->setFormula("\"IT\"+index");
        actionTurnout->setLocalVariable("index");
        actionTurnout->setReference("{IM1}");
        actionTurnout->setStateAddressing(NamedBeanAddressing::LocalVariable);
        actionTurnout->setStateFormula("\"IT\"+index2");
        actionTurnout->setStateLocalVariable("index2");
        actionTurnout->setStateReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(actionTurnout);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionTurnout = new ActionTurnout(digitalActionManager->getAutoSystemName(), "");
        actionTurnout->AbstractNamedBean::setComment("A comment");
        actionTurnout->setTurnout(turnout1);
        actionTurnout->setBeanState(ActionTurnout::TurnoutState::Closed);
        actionTurnout->setAddressing(NamedBeanAddressing::LocalVariable);
        actionTurnout->setFormula("\"IT\"+index");
        actionTurnout->setLocalVariable("index");
        actionTurnout->setReference("{IM1}");
        actionTurnout->setStateAddressing(NamedBeanAddressing::Formula);
        actionTurnout->setStateFormula("\"IT\"+index2");
        actionTurnout->setStateLocalVariable("index2");
        actionTurnout->setStateReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(actionTurnout);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionTurnout = new ActionTurnout(digitalActionManager->getAutoSystemName(), "");
        actionTurnout->AbstractNamedBean::setComment("A comment");
        actionTurnout->setTurnout(turnout1);
        actionTurnout->setBeanState(ActionTurnout::TurnoutState::Closed);
        actionTurnout->setAddressing(NamedBeanAddressing::Formula);
        actionTurnout->setFormula("\"IT\"+index");
        actionTurnout->setLocalVariable("index");
        actionTurnout->setReference("{IM1}");
        actionTurnout->setStateAddressing(NamedBeanAddressing::Reference);
        actionTurnout->setStateFormula("\"IT\"+index2");
        actionTurnout->setStateLocalVariable("index2");
        actionTurnout->setStateReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(actionTurnout);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionTurnout = new ActionTurnout(digitalActionManager->getAutoSystemName(), "");
        actionTurnout->AbstractNamedBean::setComment("A comment");
        actionTurnout->setTurnout(turnout1);
        actionTurnout->setBeanState(ActionTurnout::TurnoutState::Closed);
        actionTurnout->setAddressing(NamedBeanAddressing::Reference);
        actionTurnout->setFormula("\"IT\"+index");
        actionTurnout->setLocalVariable("index");
        actionTurnout->setReference("{IM1}");
        actionTurnout->setStateAddressing(NamedBeanAddressing::Direct);
        actionTurnout->setStateFormula("\"IT\"+index2");
        actionTurnout->setStateLocalVariable("index2");
        actionTurnout->setStateReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(actionTurnout);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

#if 0 // not yet implemented
        ActionWarrant actionWarrant = new ActionWarrant(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionWarrant);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionWarrant = new ActionWarrant(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionWarrant);
        maleSocket->setErrorHandlingType(ErrorHandlingType::Default);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionWarrant = new ActionWarrant(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionWarrant);
        maleSocket->setErrorHandlingType(ErrorHandlingType::ThrowException);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// Direct / Direct / Direct :: SetTrainName
        actionWarrant = new ActionWarrant(digitalActionManager->getAutoSystemName(), "");
        actionWarrant->AbstractNamedBean::setComment("Direct / Direct / Direct :: SetTrainName");

        actionWarrant.setAddressing(NamedBeanAddressing::Direct);
        actionWarrant.setWarrant("IW99");

        actionWarrant.setOperationAddressing(NamedBeanAddressing::Direct);
        actionWarrant.setOperationDirect(ActionWarrant.DirectOperation.SetTrainName);

        actionWarrant.setDataAddressing(NamedBeanAddressing::Direct);
        actionWarrant.setTrainIdName("ABC");

        maleSocket = digitalActionManager->registerAction(actionWarrant);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// Direct / Direct / Direct :: ControlAutoTrain - Resume
        actionWarrant = new ActionWarrant(digitalActionManager->getAutoSystemName(), "");
        actionWarrant->AbstractNamedBean::setComment("Direct / Direct / Direct :: ControlAutoTrain - Resume");

        actionWarrant.setAddressing(NamedBeanAddressing::Direct);
        actionWarrant.setWarrant("IW99");

        actionWarrant.setOperationAddressing(NamedBeanAddressing::Direct);
        actionWarrant.setOperationDirect(ActionWarrant.DirectOperation.ControlAutoTrain);

        actionWarrant.setDataAddressing(NamedBeanAddressing::Direct);
        actionWarrant.setControlAutoTrain(ActionWarrant.ControlAutoTrain.Resume);

        maleSocket = digitalActionManager->registerAction(actionWarrant);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// Direct / Direct :: AllocateWarrantRoute
        actionWarrant = new ActionWarrant(digitalActionManager->getAutoSystemName(), "");
        actionWarrant->AbstractNamedBean::setComment("Direct / Direct :: AllocateWarrantRoute");

        actionWarrant.setAddressing(NamedBeanAddressing::Direct);
        actionWarrant.setWarrant("IW99");

        actionWarrant.setOperationAddressing(NamedBeanAddressing::Direct);
        actionWarrant.setOperationDirect(ActionWarrant.DirectOperation.AllocateWarrantRoute);

        maleSocket = digitalActionManager->registerAction(actionWarrant);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// Direct / LocalVariable
        actionWarrant = new ActionWarrant(digitalActionManager->getAutoSystemName(), "");
        actionWarrant->AbstractNamedBean::setComment("Direct / LocalVariable");

        actionWarrant.setAddressing(NamedBeanAddressing::Direct);
        actionWarrant.setWarrant("IW99");

        actionWarrant.setOperationAddressing(NamedBeanAddressing::LocalVariable);
        actionWarrant.setOperationLocalVariable("index2");

        maleSocket = digitalActionManager->registerAction(actionWarrant);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// LocalVariable / Formula
        actionWarrant = new ActionWarrant(digitalActionManager->getAutoSystemName(), "");
        actionWarrant->AbstractNamedBean::setComment("LocalVariable / Formula");

        actionWarrant.setAddressing(NamedBeanAddressing::LocalVariable);
        actionWarrant.setLocalVariable("index");

        actionWarrant.setOperationAddressing(NamedBeanAddressing::Formula);
        actionWarrant.setOperationFormula("\"IT\"+index2");

        maleSocket = digitalActionManager->registerAction(actionWarrant);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// Formula / Reference
        actionWarrant = new ActionWarrant(digitalActionManager->getAutoSystemName(), "");
        actionWarrant->AbstractNamedBean::setComment("Formula / Reference");

        actionWarrant.setAddressing(NamedBeanAddressing::Formula);
        actionWarrant.setFormula("\"IT\"+index");

        actionWarrant.setOperationAddressing(NamedBeanAddressing::Reference);
        actionWarrant.setOperationReference("{IM2}");

        maleSocket = digitalActionManager->registerAction(actionWarrant);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

// Reference / Direct :: DeallocateWarrant
        actionWarrant = new ActionWarrant(digitalActionManager->getAutoSystemName(), "");
        actionWarrant->AbstractNamedBean::setComment("Reference / Direct :: DeallocateWarrant");

        actionWarrant.setAddressing(NamedBeanAddressing::Reference);
        actionWarrant.setReference("{IM1}");

        actionWarrant.setOperationAddressing(NamedBeanAddressing::Direct);
        actionWarrant.setOperationDirect(ActionWarrant.DirectOperation.DeallocateWarrant);

        maleSocket = digitalActionManager->registerAction(actionWarrant);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);
#endif
        Actions::DigitalCallModule* callModule = new Actions::DigitalCallModule(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(callModule);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        callModule = new Actions::DigitalCallModule(digitalActionManager->getAutoSystemName(), "");
        callModule->AbstractNamedBean::setComment("A comment");
        callModule->setModule("IQM1");
        callModule->addParameter("Abc", InitialValueType::FloatingNumber, "12.32", ReturnValueType::LocalVariable, "SomeVar");
        callModule->addParameter("Def", InitialValueType::Formula, "12 + 32", ReturnValueType::Memory, "M1");
        callModule->addParameter("Ghi", InitialValueType::Integer, "21", ReturnValueType::None, "");
        callModule->addParameter("Jkl", InitialValueType::LocalVariable, "MyVar", ReturnValueType::Memory, "M34");
        callModule->addParameter("Mno", InitialValueType::Memory, "M2", ReturnValueType::LocalVariable, "SomeVar");
        callModule->addParameter("Pqr", InitialValueType::None, "", ReturnValueType::LocalVariable, "SomeVar");
        callModule->addParameter("Stu", InitialValueType::Reference, "{MyVar}", ReturnValueType::LocalVariable, "SomeVar");
        callModule->addParameter("Vxy", InitialValueType::String, "Some string", ReturnValueType::LocalVariable, "SomeVar");
        maleSocket = digitalActionManager->registerAction(callModule);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        DoAnalogAction* doAnalogAction = new DoAnalogAction(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(doAnalogAction);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        doAnalogAction = new DoAnalogAction(digitalActionManager->getAutoSystemName(), "");
        doAnalogAction->AbstractNamedBean::setComment("A comment");
        maleSocket = digitalActionManager->registerAction(doAnalogAction);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);


        DoStringAction* doStringAction = new DoStringAction(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(doStringAction);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        doStringAction = new DoStringAction(digitalActionManager->getAutoSystemName(), "");
        doStringAction->AbstractNamedBean::setComment("A comment");
        maleSocket = digitalActionManager->registerAction(doStringAction);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

#if 0 // not yet implemented
        EnableLogix enableLogix = new EnableLogix(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(enableLogix);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        enableLogix = new EnableLogix(digitalActionManager->getAutoSystemName(), "");
        enableLogix->AbstractNamedBean::setComment("A comment");
        enableLogix.setLogix(logixIX1);
        enableLogix.setOperationDirect(EnableLogix.Operation.Enable);
        enableLogix.setAddressing(NamedBeanAddressing::Direct);
        enableLogix.setFormula("\"IT\"+index");
        enableLogix.setLocalVariable("index");
        enableLogix.setReference("{IM1}");
        enableLogix.setOperationAddressing(NamedBeanAddressing::LocalVariable);
        enableLogix.setOperationFormula("\"IT\"+index2");
        enableLogix.setOperationLocalVariable("index2");
        enableLogix.setOperationReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(enableLogix);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        enableLogix = new EnableLogix(digitalActionManager->getAutoSystemName(), "");
        enableLogix->AbstractNamedBean::setComment("A comment");
        enableLogix.setLogix(logixIX1);
        enableLogix.setOperationDirect(EnableLogix.Operation.Disable);
        enableLogix.setAddressing(NamedBeanAddressing::LocalVariable);
        enableLogix.setFormula("\"IT\"+index");
        enableLogix.setLocalVariable("index");
        enableLogix.setReference("{IM1}");
        enableLogix.setOperationAddressing(NamedBeanAddressing::Formula);
        enableLogix.setOperationFormula("\"IT\"+index2");
        enableLogix.setOperationLocalVariable("index2");
        enableLogix.setOperationReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(enableLogix);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        enableLogix = new EnableLogix(digitalActionManager->getAutoSystemName(), "");
        enableLogix->AbstractNamedBean::setComment("A comment");
        enableLogix.setLogix(logixIX1);
        enableLogix.setOperationDirect(EnableLogix.Operation.Enable);
        enableLogix.setAddressing(NamedBeanAddressing::Formula);
        enableLogix.setFormula("\"IT\"+index");
        enableLogix.setLocalVariable("index");
        enableLogix.setReference("{IM1}");
        enableLogix.setOperationAddressing(NamedBeanAddressing::Reference);
        enableLogix.setOperationFormula("\"IT\"+index2");
        enableLogix.setOperationLocalVariable("index2");
        enableLogix.setOperationReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(enableLogix);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        enableLogix = new EnableLogix(digitalActionManager->getAutoSystemName(), "");
        enableLogix->AbstractNamedBean::setComment("A comment");
        enableLogix.setLogix(logixIX1);
        enableLogix.setOperationDirect(EnableLogix.Operation.Enable);
        enableLogix.setAddressing(NamedBeanAddressing::Reference);
        enableLogix.setFormula("\"IT\"+index");
        enableLogix.setLocalVariable("index");
        enableLogix.setReference("{IM1}");
        enableLogix.setOperationAddressing(NamedBeanAddressing::Direct);
        enableLogix.setOperationFormula("\"IT\"+index2");
        enableLogix.setOperationLocalVariable("index2");
        enableLogix.setOperationReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(enableLogix);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);


        ActionEntryExit entryExit = new ActionEntryExit(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(entryExit);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        entryExit = new ActionEntryExit(digitalActionManager->getAutoSystemName(), "");
        entryExit->AbstractNamedBean::setComment("A comment");
        entryExit.setOperationDirect(ActionEntryExit.Operation.SetNXPairDisabled);
        entryExit.setAddressing(NamedBeanAddressing::Direct);
        entryExit.setFormula("\"IT\"+index");
        entryExit.setLocalVariable("index");
        entryExit.setReference("{IM1}");
        entryExit.setOperationAddressing(NamedBeanAddressing::LocalVariable);
        entryExit.setOperationFormula("\"IT\"+index2");
        entryExit.setOperationLocalVariable("index2");
        entryExit.setOperationReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(entryExit);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        entryExit = new ActionEntryExit(digitalActionManager->getAutoSystemName(), "");
        entryExit->AbstractNamedBean::setComment("A comment");
        entryExit.setOperationDirect(ActionEntryExit.Operation.SetNXPairEnabled);
        entryExit.setAddressing(NamedBeanAddressing::LocalVariable);
        entryExit.setFormula("\"IT\"+index");
        entryExit.setLocalVariable("index");
        entryExit.setReference("{IM1}");
        entryExit.setOperationAddressing(NamedBeanAddressing::Formula);
        entryExit.setOperationFormula("\"IT\"+index2");
        entryExit.setOperationLocalVariable("index2");
        entryExit.setOperationReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(entryExit);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        entryExit = new ActionEntryExit(digitalActionManager->getAutoSystemName(), "");
        entryExit->AbstractNamedBean::setComment("A comment");
        entryExit.setOperationDirect(ActionEntryExit.Operation.SetNXPairSegment);
        entryExit.setAddressing(NamedBeanAddressing::Formula);
        entryExit.setFormula("\"IT\"+index");
        entryExit.setLocalVariable("index");
        entryExit.setReference("{IM1}");
        entryExit.setOperationAddressing(NamedBeanAddressing::Reference);
        entryExit.setOperationFormula("\"IT\"+index2");
        entryExit.setOperationLocalVariable("index2");
        entryExit.setOperationReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(entryExit);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        entryExit = new ActionEntryExit(digitalActionManager->getAutoSystemName(), "");
        entryExit->AbstractNamedBean::setComment("A comment");
        entryExit.setOperationDirect(ActionEntryExit.Operation.SetNXPairDisabled);
        entryExit.setAddressing(NamedBeanAddressing::Reference);
        entryExit.setFormula("\"IT\"+index");
        entryExit.setLocalVariable("index");
        entryExit.setReference("{IM1}");
        entryExit.setOperationAddressing(NamedBeanAddressing::Direct);
        entryExit.setOperationFormula("\"IT\"+index2");
        entryExit.setOperationLocalVariable("index2");
        entryExit.setOperationReference("{IM2}");
        maleSocket = digitalActionManager->registerAction(entryExit);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);
#endif
        ExecuteDelayed* executeDelayed = new ExecuteDelayed(digitalActionManager->getAutoSystemName(), "");
        executeDelayed->setResetIfAlreadyStarted(false);
        maleSocket = digitalActionManager->registerAction(executeDelayed);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        executeDelayed = new ExecuteDelayed(digitalActionManager->getAutoSystemName(), "");
        executeDelayed->AbstractNamedBean::setComment("A comment");
        executeDelayed->setDelayAddressing(NamedBeanAddressing::Direct);
        executeDelayed->setDelay(100);
        executeDelayed->setResetIfAlreadyStarted(true);
        maleSocket = digitalActionManager->registerAction(executeDelayed);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        executeDelayed = new ExecuteDelayed(digitalActionManager->getAutoSystemName(), "");
        executeDelayed->AbstractNamedBean::setComment("A comment");
        executeDelayed->setDelayAddressing(NamedBeanAddressing::LocalVariable);
        executeDelayed->setDelayLocalVariable("MyVar");
        executeDelayed->setResetIfAlreadyStarted(true);
        maleSocket = digitalActionManager->registerAction(executeDelayed);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        executeDelayed = new ExecuteDelayed(digitalActionManager->getAutoSystemName(), "");
        executeDelayed->AbstractNamedBean::setComment("A comment");
        executeDelayed->setDelayAddressing(NamedBeanAddressing::Reference);
        executeDelayed->setDelayReference("{MyMemory}");
        executeDelayed->setResetIfAlreadyStarted(true);
        maleSocket = digitalActionManager->registerAction(executeDelayed);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        executeDelayed = new ExecuteDelayed(digitalActionManager->getAutoSystemName(), "");
        executeDelayed->AbstractNamedBean::setComment("A comment");
        executeDelayed->setDelayAddressing(NamedBeanAddressing::Formula);
        executeDelayed->setDelayFormula("MyVar + 10");
        executeDelayed->setResetIfAlreadyStarted(true);
        maleSocket = digitalActionManager->registerAction(executeDelayed);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        For* actionFor =
                new For(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(actionFor);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        actionFor = new For(digitalActionManager->getAutoSystemName(), "");
        actionFor->AbstractNamedBean::setComment("A comment");
        maleSocket = digitalActionManager->registerAction(actionFor);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);


        IfThenElse* ifThenElse = new IfThenElse(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(ifThenElse);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        ifThenElse = new IfThenElse(digitalActionManager->getAutoSystemName(), "");
        ifThenElse->AbstractNamedBean::setComment("A comment");
        ifThenElse->setType(IfThenElse::Type::ExecuteOnChange);
        maleSocket = digitalActionManager->registerAction(ifThenElse);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        ifThenElse = new IfThenElse(digitalActionManager->getAutoSystemName(), "");
        ifThenElse->AbstractNamedBean::setComment("A comment");
        ifThenElse->setType(IfThenElse::Type::AlwaysExecute);
        maleSocket = digitalActionManager->registerAction(ifThenElse);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);


        Logix_Emulator* logix =
                new Logix_Emulator(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(logix);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        logix = new Logix_Emulator(digitalActionManager->getAutoSystemName(), "");
        logix->AbstractNamedBean::setComment("A comment");
        maleSocket = digitalActionManager->registerAction(logix);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        DigitalBooleanMany* booleanMany =
                new DigitalBooleanMany(digitalBooleanActionManager->getAutoSystemName(), "");
        maleSocket = digitalBooleanActionManager->registerAction(booleanMany);
        maleSocket->setEnabled(false);
        logix->getChild(1)->_connect(maleSocket);

        DigitalBooleanMany* booleanMany2 =
                new DigitalBooleanMany(digitalBooleanActionManager->getAutoSystemName(), "");
        booleanMany2->AbstractNamedBean::setComment("A comment");
        maleSocket = digitalBooleanActionManager->registerAction(booleanMany2);
        booleanMany->getChild(0)->_connect(maleSocket);

        DigitalBooleanOnChange* onChange =
                new DigitalBooleanOnChange(digitalBooleanActionManager->getAutoSystemName(),
                        "", DigitalBooleanOnChange::Trigger::CHANGE);
        maleSocket = digitalBooleanActionManager->registerAction(onChange);
        maleSocket->setEnabled(false);
        booleanMany->getChild(1)->_connect(maleSocket);

        onChange = new DigitalBooleanOnChange(digitalBooleanActionManager->getAutoSystemName(),
                "", DigitalBooleanOnChange::Trigger::CHANGE_TO_FALSE);
        onChange->AbstractNamedBean::setComment("A comment");
        maleSocket = digitalBooleanActionManager->registerAction(onChange);
        booleanMany->getChild(2)->_connect(maleSocket);

        Actions::LogData* logData = new Actions::LogData(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(logData);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        logData = new Actions::LogData(digitalActionManager->getAutoSystemName(), "");
        logData->AbstractNamedBean::setComment("A comment");
        logData->setLogToLog(true);
#ifdef ENABLE_SCRIPTING
        logData->setLogToScriptOutput(true);
#endif
        logData->setFormat("Some text");
        logData->setFormatType(Actions::LogData::FormatType::OnlyText);
        logData->getDataList()->append(Actions::LogData::Data(Actions::LogData::DataType::LocalVariable, "MyVar"));
        maleSocket = digitalActionManager->registerAction(logData);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        logData = new Actions::LogData(digitalActionManager->getAutoSystemName(), "");
        logData->AbstractNamedBean::setComment("A comment");
        logData->setLogToLog(true);
#ifdef ENABLE_SCRIPTING
        logData->setLogToScriptOutput(true);
#endif
        logData->setFormat("");
        logData->setFormatType(Actions::LogData::FormatType::CommaSeparatedList);
        logData->getDataList()->append(Actions::LogData::Data(Actions::LogData::DataType::Memory, "IM1"));
        maleSocket = digitalActionManager->registerAction(logData);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        logData = new Actions::LogData(digitalActionManager->getAutoSystemName(), "");
        logData->AbstractNamedBean::setComment("A comment");
        logData->setLogToLog(true);
#ifdef ENABLE_SCRIPTING
        logData->setLogToScriptOutput(true);
#endif
        logData->setFormat("MyVar has the value %s");
        logData->setFormatType(Actions::LogData::FormatType::StringFormat);
        logData->getDataList()->append(Actions::LogData::Data(Actions::LogData::DataType::Reference, "{MyVar}"));
        maleSocket = digitalActionManager->registerAction(logData);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        logData = new Actions::LogData(digitalActionManager->getAutoSystemName(), "");
        logData->AbstractNamedBean::setComment("A comment");
        logData->setLogToLog(true);
#ifdef ENABLE_SCRIPTING
        logData->setLogToScriptOutput(true);
#endif
        logData->setFormat("str(10): %s, 25: %d, IM1: %s, MyVar: %s");
        logData->setFormatType(Actions::LogData::FormatType::StringFormat);
        logData->getDataList()->append(Actions::LogData::Data(Actions::LogData::DataType::Formula, "str(10)"));
        logData->getDataList()->append(Actions::LogData::Data(Actions::LogData::DataType::Formula, "25"));
        logData->getDataList()->append(Actions::LogData::Data(Actions::LogData::DataType::Memory, "IM1"));
        logData->getDataList()->append(Actions::LogData::Data(Actions::LogData::DataType::LocalVariable, "MyVar"));
        maleSocket = digitalActionManager->registerAction(logData);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

#if 0 // not yet implemented
        LogLocalVariables logLocalVariables = new LogLocalVariables(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(logLocalVariables);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        logLocalVariables = new LogLocalVariables(digitalActionManager->getAutoSystemName(), "");
        logLocalVariables->AbstractNamedBean::setComment("A comment");
        maleSocket = digitalActionManager->registerAction(logLocalVariables);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);
#endif

        DigitalMany* many = new DigitalMany(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(many);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        many = new DigitalMany(digitalActionManager->getAutoSystemName(), "");
        many->AbstractNamedBean::setComment("A comment");
        maleSocket = digitalActionManager->registerAction(many);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        Sequence* sequence =
                new Sequence(digitalActionManager->getAutoSystemName(), "");
        sequence->setRunContinuously(false);
        sequence->setStartImmediately(true);
        maleSocket = digitalActionManager->registerAction(sequence);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        sequence = new Sequence(digitalActionManager->getAutoSystemName(), "");
        sequence->AbstractNamedBean::setComment("A comment");
        sequence->setRunContinuously(true);
        sequence->setStartImmediately(false);
        maleSocket = digitalActionManager->registerAction(sequence);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        And* andTemp = new And(digitalExpressionManager->getAutoSystemName(), "");
        andTemp->AbstractNamedBean::setComment("Start expression");
        maleSocket = digitalExpressionManager->registerExpression(andTemp);
        maleSocket->setEnabled(false);
        sequence->getChild(0)->_connect(maleSocket);

        andTemp = new And(digitalExpressionManager->getAutoSystemName(), "");
        andTemp->AbstractNamedBean::setComment("Stop expression");
        maleSocket = digitalExpressionManager->registerExpression(andTemp);
        sequence->getChild(1)->_connect(maleSocket);

        andTemp = new And(digitalExpressionManager->getAutoSystemName(), "");
        andTemp->AbstractNamedBean::setComment("Reset expression");
        maleSocket = digitalExpressionManager->registerExpression(andTemp);
        sequence->getChild(2)->_connect(maleSocket);

        DigitalMany* manyTemp = new DigitalMany(digitalActionManager->getAutoSystemName(), "");
        manyTemp->AbstractNamedBean::setComment("Action socket 1");
        maleSocket = digitalActionManager->registerAction(manyTemp);
        maleSocket->setEnabled(false);
        sequence->getChild(3)->_connect(maleSocket);

        andTemp = new And(digitalExpressionManager->getAutoSystemName(), "");
        andTemp->AbstractNamedBean::setComment("Expression socket 1");
        maleSocket = digitalExpressionManager->registerExpression(andTemp);
        sequence->getChild(4)->_connect(maleSocket);

        sequence->doSocketOperation(4, FemaleSocketOperation::InsertAfter);

        manyTemp = new DigitalMany(digitalActionManager->getAutoSystemName(), "");
        manyTemp->AbstractNamedBean::setComment("Action socket 2");
        maleSocket = digitalActionManager->registerAction(manyTemp);
        sequence->getChild(5)->_connect(maleSocket);

        andTemp = new And(digitalExpressionManager->getAutoSystemName(), "");
        andTemp->AbstractNamedBean::setComment("Expression socket 2");
        maleSocket = digitalExpressionManager->registerExpression(andTemp);
        sequence->getChild(6)->_connect(maleSocket);

#if 0 // not yet implemented
        ShutdownComputer shutdownComputer =
                new ShutdownComputer(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(shutdownComputer);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        shutdownComputer = new ShutdownComputer(digitalActionManager->getAutoSystemName(), "");
        shutdownComputer->AbstractNamedBean::setComment("A comment");
        shutdownComputer.setOperation(ShutdownComputer.Operation.ShutdownComputer);
        maleSocket = digitalActionManager->registerAction(shutdownComputer);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        shutdownComputer = new ShutdownComputer(digitalActionManager->getAutoSystemName(), "");
        shutdownComputer->AbstractNamedBean::setComment("A comment");
        shutdownComputer.setOperation(ShutdownComputer.Operation.RebootComputer);
        maleSocket = digitalActionManager->registerAction(shutdownComputer);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        shutdownComputer = new ShutdownComputer(digitalActionManager->getAutoSystemName(), "");
        shutdownComputer->AbstractNamedBean::setComment("A comment");
        shutdownComputer.setOperation(ShutdownComputer.Operation.ShutdownJMRI);
        maleSocket = digitalActionManager->registerAction(shutdownComputer);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        shutdownComputer = new ShutdownComputer(digitalActionManager->getAutoSystemName(), "");
        shutdownComputer->AbstractNamedBean::setComment("A comment");
        shutdownComputer.setOperation(ShutdownComputer.Operation.RebootJMRI);
        maleSocket = digitalActionManager->registerAction(shutdownComputer);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

#endif
        TableForEach* tableForEach = new TableForEach(digitalActionManager->getAutoSystemName(), "");
        tableForEach->setRowOrColumn(TableRowOrColumn::Column);
        maleSocket = digitalActionManager->registerAction(tableForEach);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        tableForEach = new TableForEach(digitalActionManager->getAutoSystemName(), "");
        tableForEach->AbstractNamedBean::setComment("A comment");
        tableForEach->setLocalVariableName("MyLocalVariable");
        tableForEach->setTable(csvTable);
        tableForEach->setRowOrColumn(TableRowOrColumn::Row);
        tableForEach->setRowOrColumnName("North yard");
        maleSocket = digitalActionManager->registerAction(tableForEach);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);
        maleSocket->getChild(0)->_connect(
                digitalActionManager->registerAction(
                        new DigitalMany(digitalActionManager->getAutoSystemName(), "")));

        tableForEach = new TableForEach(digitalActionManager->getAutoSystemName(), "");
        tableForEach->AbstractNamedBean::setComment("A comment");
        tableForEach->setLocalVariableName("MyLocalVariable");
        tableForEach->setRowOrColumn(TableRowOrColumn::Column);
        tableForEach->setTable(csvTable);
        tableForEach->setTableReference("{MyTableRef}");
        tableForEach->setTableLocalVariable("MyTableVar");
        tableForEach->setTableFormula("MyTableFormula");
        tableForEach->setRowOrColumnName("Second turnout");
        tableForEach->setRowOrColumnReference("{MyRowOrColumnRef}");
        tableForEach->setRowOrColumnLocalVariable("MyRowOrColumnVar");
        tableForEach->setRowOrColumnFormula("MyRowOrColumnFormula");
        maleSocket = digitalActionManager->registerAction(tableForEach);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);
        maleSocket->getChild(0)->_connect(
                digitalActionManager->registerAction(
                        new DigitalMany(digitalActionManager->getAutoSystemName(), "")));

#if 0 // not yet implemented
        actionThrottle = new ActionThrottle(digitalActionManager->getAutoSystemName(), "");
        actionThrottle->AbstractNamedBean::setComment("A comment");
        maleSocket = digitalActionManager->registerAction(actionThrottle);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        maleSocket->getChild(0)->_connect(
                analogExpressionManager->registerExpression(
                        new AnalogExpressionMemory(analogExpressionManager->getAutoSystemName(), null)));

        maleSocket->getChild(1)->_connect(
                analogExpressionManager->registerExpression(
                        new AnalogExpressionMemory(analogExpressionManager->getAutoSystemName(), null)));

        maleSocket->getChild(2)->_connect(
                digitalExpressionManager->registerExpression(
                        new ExpressionMemory(digitalExpressionManager->getAutoSystemName(), null)));



        TriggerRoute triggerRoute =
                new TriggerRoute(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(triggerRoute);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        triggerRoute = new TriggerRoute(digitalActionManager->getAutoSystemName(), "");
        triggerRoute->AbstractNamedBean::setComment("A comment");
        triggerRoute.setOperationDirect(TriggerRoute.Operation.TriggerRoute);
        maleSocket = digitalActionManager->registerAction(triggerRoute);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);
#endif


        ifThenElse = new IfThenElse(digitalActionManager->getAutoSystemName(), "");
        ifThenElse->AbstractNamedBean::setComment("A comment");
        ifThenElse->setType(IfThenElse::Type::ExecuteOnChange);
        maleSocket = digitalActionManager->registerAction(ifThenElse);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);


        And* and1 = new And(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(and1);
        maleSocket->setEnabled(false);
        ifThenElse->getChild(0)->_connect(maleSocket);

        And* _and = new And(digitalExpressionManager->getAutoSystemName(), "");
        _and->AbstractNamedBean::setComment("A comment");
        maleSocket = digitalExpressionManager->registerExpression(_and);
        and1->getChild(0)->_connect(maleSocket);


        int indexExpr = 0;


        Antecedent* antecedent = new Antecedent(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(antecedent);
        maleSocket->setEnabled(false);
        maleSocket->setErrorHandlingType(ErrorHandlingType::AbortExecution);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        antecedent = new Antecedent(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(antecedent);
        maleSocket->setErrorHandlingType(ErrorHandlingType::Default);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        antecedent = new Antecedent(digitalExpressionManager->getAutoSystemName(), "");
        antecedent->AbstractNamedBean::setComment("A comment");
        antecedent->setAntecedent("R1 or R2");
        maleSocket = digitalExpressionManager->registerExpression(antecedent);
        maleSocket->setErrorHandlingType(ErrorHandlingType::LogError);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        antecedent = new Antecedent(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(antecedent);
        maleSocket->setErrorHandlingType(ErrorHandlingType::LogErrorOnce);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        antecedent = new Antecedent(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(antecedent);
        maleSocket->setErrorHandlingType(ErrorHandlingType::ShowDialogBox);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        antecedent = new Antecedent(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(antecedent);
        maleSocket->setErrorHandlingType(ErrorHandlingType::ThrowException);
        _and->getChild(indexExpr++)->_connect(maleSocket);


        Expressions::DigitalCallModule* expressionCallModule = new Expressions::DigitalCallModule(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(expressionCallModule);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionCallModule = new Expressions::DigitalCallModule(digitalExpressionManager->getAutoSystemName(), "");
        expressionCallModule->AbstractNamedBean::setComment("A comment");
        expressionCallModule->setModule("IQM1");
        expressionCallModule->addParameter("Abc", InitialValueType::FloatingNumber, "12.32", ReturnValueType::LocalVariable, "SomeVar");
        expressionCallModule->addParameter("Def", InitialValueType::Formula, "12 + 32", ReturnValueType::Memory, "M1");
        expressionCallModule->addParameter("Ghi", InitialValueType::Integer, "21", ReturnValueType::None, "");
        expressionCallModule->addParameter("Jkl", InitialValueType::LocalVariable, "MyVar", ReturnValueType::Memory, "M34");
        expressionCallModule->addParameter("Mno", InitialValueType::Memory, "M2", ReturnValueType::LocalVariable, "SomeVar");
        expressionCallModule->addParameter("Pqr", InitialValueType::None, "", ReturnValueType::LocalVariable, "SomeVar");
        expressionCallModule->addParameter("Stu", InitialValueType::Reference, "{MyVar}", ReturnValueType::LocalVariable, "SomeVar");
        expressionCallModule->addParameter("Vxy", InitialValueType::String, "Some string", ReturnValueType::LocalVariable, "SomeVar");
        maleSocket = digitalExpressionManager->registerExpression(expressionCallModule);
        _and->getChild(indexExpr++)->_connect(maleSocket);

#if 0 // not yet implemented
        ExpressionBlock expressionBlock = new ExpressionBlock(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(expressionBlock);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);
// Direct / Direct / Direct :: ValueMatches
        expressionBlock = new ExpressionBlock(digitalExpressionManager->getAutoSystemName(), "");
        expressionBlock->AbstractNamedBean::setComment("Direct / Direct / Direct :: ValueMatches");

        expressionBlock.setAddressing(NamedBeanAddressing::Direct);
        expressionBlock.setBlock(block1);

        expressionBlock.set_Is_IsNot(Is_IsNot_Enum.Is);

        expressionBlock.setStateAddressing(NamedBeanAddressing::Direct);
        expressionBlock.setBeanState(ExpressionBlock.BlockState.ValueMatches);

        expressionBlock.setDataAddressing(NamedBeanAddressing::Direct);
        expressionBlock.setBlockValue("XYZ");

        maleSocket = digitalExpressionManager->registerExpression(expressionBlock);
        _and->getChild(indexExpr++)->_connect(maleSocket);

// Direct / Direct :: Occupied
        expressionBlock = new ExpressionBlock(digitalExpressionManager->getAutoSystemName(), "");
        expressionBlock->AbstractNamedBean::setComment("Direct / Direct :: Occupied");

        expressionBlock.setAddressing(NamedBeanAddressing::Direct);
        expressionBlock.setBlock(block1);

        expressionBlock.set_Is_IsNot(Is_IsNot_Enum.Is);

        expressionBlock.setStateAddressing(NamedBeanAddressing::Direct);
        expressionBlock.setBeanState(ExpressionBlock.BlockState.Occupied);

        maleSocket = digitalExpressionManager->registerExpression(expressionBlock);
        _and->getChild(indexExpr++)->_connect(maleSocket);

// Direct / LocalVariable
        expressionBlock = new ExpressionBlock(digitalExpressionManager->getAutoSystemName(), "");
        expressionBlock->AbstractNamedBean::setComment("Direct / LocalVariable");

        expressionBlock.setAddressing(NamedBeanAddressing::Direct);
        expressionBlock.setBlock(block1);

        expressionBlock.set_Is_IsNot(Is_IsNot_Enum.IsNot);

        expressionBlock.setStateAddressing(NamedBeanAddressing::LocalVariable);
        expressionBlock.setStateLocalVariable("index2");

        maleSocket = digitalExpressionManager->registerExpression(expressionBlock);
        _and->getChild(indexExpr++)->_connect(maleSocket);

// LocalVariable / Formula
        expressionBlock = new ExpressionBlock(digitalExpressionManager->getAutoSystemName(), "");
        expressionBlock->AbstractNamedBean::setComment("LocalVariable / Formula");

        expressionBlock.setAddressing(NamedBeanAddressing::LocalVariable);
        expressionBlock.setLocalVariable("index");

        expressionBlock.set_Is_IsNot(Is_IsNot_Enum.Is);

        expressionBlock.setStateAddressing(NamedBeanAddressing::Formula);
        expressionBlock.setStateFormula("\"IT\"+index2");

        maleSocket = digitalExpressionManager->registerExpression(expressionBlock);
        _and->getChild(indexExpr++)->_connect(maleSocket);

// Formula / Reference
        expressionBlock = new ExpressionBlock(digitalExpressionManager->getAutoSystemName(), "");
        expressionBlock->AbstractNamedBean::setComment("Formula / Reference");

        expressionBlock.setAddressing(NamedBeanAddressing::Formula);
        expressionBlock.setFormula("\"IT\"+index");

        expressionBlock.set_Is_IsNot(Is_IsNot_Enum.IsNot);

        expressionBlock.setStateAddressing(NamedBeanAddressing::Reference);
        expressionBlock.setStateReference("{IM2}");

        maleSocket = digitalExpressionManager->registerExpression(expressionBlock);
        _and->getChild(indexExpr++)->_connect(maleSocket);

// Reference / Direct :: Allocated
        expressionBlock = new ExpressionBlock(digitalExpressionManager->getAutoSystemName(), "");
        expressionBlock->AbstractNamedBean::setComment("Reference / Direct :: Allocated");

        expressionBlock.setAddressing(NamedBeanAddressing::Reference);
        expressionBlock.setReference("{IM1}");

        expressionBlock.set_Is_IsNot(Is_IsNot_Enum.Is);

        expressionBlock.setStateAddressing(NamedBeanAddressing::Direct);
        expressionBlock.setBeanState(ExpressionBlock.BlockState.Allocated);

        maleSocket = digitalExpressionManager->registerExpression(expressionBlock);
        _and->getChild(indexExpr++)->_connect(maleSocket);


        ExpressionClock expressionClock = new ExpressionClock(digitalExpressionManager->getAutoSystemName(), "");
        expressionClock.setType(ExpressionClock.Type.SystemClock);
        expressionClock.set_Is_IsNot(Is_IsNot_Enum.Is);
        maleSocket = digitalExpressionManager->registerExpression(expressionClock);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionClock = new ExpressionClock(digitalExpressionManager->getAutoSystemName(), "");
        expressionClock->AbstractNamedBean::setComment("A comment");
        expressionClock.setRange(10, 20);
        expressionClock.setType(ExpressionClock.Type.FastClock);
        expressionClock.set_Is_IsNot(Is_IsNot_Enum.IsNot);
        maleSocket = digitalExpressionManager->registerExpression(expressionClock);
        _and->getChild(indexExpr++)->_connect(maleSocket);


        ExpressionConditional expressionConditional = new ExpressionConditional(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(expressionConditional);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionConditional = new ExpressionConditional(digitalExpressionManager->getAutoSystemName(), "");
        expressionConditional->AbstractNamedBean::setComment("A comment");
        expressionConditional.setConditional("IX1C1");
        expressionConditional.setConditionalState(ExpressionConditional.ConditionalState.False);
        expressionConditional.setAddressing(NamedBeanAddressing::Direct);
        expressionConditional.setFormula("\"IT\"+index");
        expressionConditional.setLocalVariable("index");
        expressionConditional.setReference("{IM1}");
        expressionConditional.set_Is_IsNot(Is_IsNot_Enum.IsNot);
        expressionConditional.setStateAddressing(NamedBeanAddressing::LocalVariable);
        expressionConditional.setStateFormula("\"IT\"+index2");
        expressionConditional.setStateLocalVariable("index2");
        expressionConditional.setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionConditional);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionConditional = new ExpressionConditional(digitalExpressionManager->getAutoSystemName(), "");
        expressionConditional->AbstractNamedBean::setComment("A comment");
        expressionConditional.setConditional("IX1C1");
        expressionConditional.setConditionalState(ExpressionConditional.ConditionalState.True);
        expressionConditional.setAddressing(NamedBeanAddressing::LocalVariable);
        expressionConditional.setFormula("\"IT\"+index");
        expressionConditional.setLocalVariable("index");
        expressionConditional.setReference("{IM1}");
        expressionConditional.set_Is_IsNot(Is_IsNot_Enum.Is);
        expressionConditional.setStateAddressing(NamedBeanAddressing::Formula);
        expressionConditional.setStateFormula("\"IT\"+index2");
        expressionConditional.setStateLocalVariable("index2");
        expressionConditional.setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionConditional);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionConditional = new ExpressionConditional(digitalExpressionManager->getAutoSystemName(), "");
        expressionConditional->AbstractNamedBean::setComment("A comment");
        expressionConditional.setConditional("IX1C1");
        expressionConditional.setConditionalState(ExpressionConditional.ConditionalState.Other);
        expressionConditional.setAddressing(NamedBeanAddressing::Formula);
        expressionConditional.setFormula("\"IT\"+index");
        expressionConditional.setLocalVariable("index");
        expressionConditional.setReference("{IM1}");
        expressionConditional.set_Is_IsNot(Is_IsNot_Enum.IsNot);
        expressionConditional.setStateAddressing(NamedBeanAddressing::Reference);
        expressionConditional.setStateFormula("\"IT\"+index2");
        expressionConditional.setStateLocalVariable("index2");
        expressionConditional.setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionConditional);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionConditional = new ExpressionConditional(digitalExpressionManager->getAutoSystemName(), "");
        expressionConditional->AbstractNamedBean::setComment("A comment");
        expressionConditional.setConditional("IX1C1");
        expressionConditional.setConditionalState(ExpressionConditional.ConditionalState.False);
        expressionConditional.setAddressing(NamedBeanAddressing::Reference);
        expressionConditional.setFormula("\"IT\"+index");
        expressionConditional.setLocalVariable("index");
        expressionConditional.setReference("{IM1}");
        expressionConditional.set_Is_IsNot(Is_IsNot_Enum.Is);
        expressionConditional.setStateAddressing(NamedBeanAddressing::Direct);
        expressionConditional.setStateFormula("\"IT\"+index2");
        expressionConditional.setStateLocalVariable("index2");
        expressionConditional.setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionConditional);
        _and->getChild(indexExpr++)->_connect(maleSocket);


        ExpressionEntryExit expressionEntryExit = new ExpressionEntryExit(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(expressionEntryExit);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionEntryExit = new ExpressionEntryExit(digitalExpressionManager->getAutoSystemName(), "");
        expressionEntryExit->AbstractNamedBean::setComment("A comment");
        expressionEntryExit.setBeanState(ExpressionEntryExit.EntryExitState.Inactive);
        expressionEntryExit.setAddressing(NamedBeanAddressing::Direct);
        expressionEntryExit.setFormula("\"IT\"+index");
        expressionEntryExit.setLocalVariable("index");
        expressionEntryExit.setReference("{IM1}");
        expressionEntryExit.set_Is_IsNot(Is_IsNot_Enum.IsNot);
        expressionEntryExit.setStateAddressing(NamedBeanAddressing::LocalVariable);
        expressionEntryExit.setStateFormula("\"IT\"+index2");
        expressionEntryExit.setStateLocalVariable("index2");
        expressionEntryExit.setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionEntryExit);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionEntryExit = new ExpressionEntryExit(digitalExpressionManager->getAutoSystemName(), "");
        expressionEntryExit->AbstractNamedBean::setComment("A comment");
        expressionEntryExit.setBeanState(ExpressionEntryExit.EntryExitState.Inactive);
        expressionEntryExit.setAddressing(NamedBeanAddressing::LocalVariable);
        expressionEntryExit.setFormula("\"IT\"+index");
        expressionEntryExit.setLocalVariable("index");
        expressionEntryExit.setReference("{IM1}");
        expressionEntryExit.set_Is_IsNot(Is_IsNot_Enum.Is);
        expressionEntryExit.setStateAddressing(NamedBeanAddressing::Formula);
        expressionEntryExit.setStateFormula("\"IT\"+index2");
        expressionEntryExit.setStateLocalVariable("index2");
        expressionEntryExit.setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionEntryExit);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionEntryExit = new ExpressionEntryExit(digitalExpressionManager->getAutoSystemName(), "");
        expressionEntryExit->AbstractNamedBean::setComment("A comment");
        expressionEntryExit.setBeanState(ExpressionEntryExit.EntryExitState.Inactive);
        expressionEntryExit.setAddressing(NamedBeanAddressing::Formula);
        expressionEntryExit.setFormula("\"IT\"+index");
        expressionEntryExit.setLocalVariable("index");
        expressionEntryExit.setReference("{IM1}");
        expressionEntryExit.set_Is_IsNot(Is_IsNot_Enum.IsNot);
        expressionEntryExit.setStateAddressing(NamedBeanAddressing::Reference);
        expressionEntryExit.setStateFormula("\"IT\"+index2");
        expressionEntryExit.setStateLocalVariable("index2");
        expressionEntryExit.setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionEntryExit);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionEntryExit = new ExpressionEntryExit(digitalExpressionManager->getAutoSystemName(), "");
        expressionEntryExit->AbstractNamedBean::setComment("A comment");
        expressionEntryExit.setBeanState(ExpressionEntryExit.EntryExitState.Inactive);
        expressionEntryExit.setAddressing(NamedBeanAddressing::Reference);
        expressionEntryExit.setFormula("\"IT\"+index");
        expressionEntryExit.setLocalVariable("index");
        expressionEntryExit.setReference("{IM1}");
        expressionEntryExit.set_Is_IsNot(Is_IsNot_Enum.Is);
        expressionEntryExit.setStateAddressing(NamedBeanAddressing::Direct);
        expressionEntryExit.setStateFormula("\"IT\"+index2");
        expressionEntryExit.setStateLocalVariable("index2");
        expressionEntryExit.setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionEntryExit);
        _and->getChild(indexExpr++)->_connect(maleSocket);
#endif

        ExpressionLight* expressionLight = new ExpressionLight(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(expressionLight);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionLight = new ExpressionLight(digitalExpressionManager->getAutoSystemName(), "");
        expressionLight->AbstractNamedBean::setComment("A comment");
        expressionLight->setLight(light1);
        expressionLight->setBeanState(ExpressionLight::LightState::Off);
        expressionLight->setAddressing(NamedBeanAddressing::Direct);
        expressionLight->setFormula("\"IT\"+index");
        expressionLight->setLocalVariable("index");
        expressionLight->setReference("{IM1}");
        expressionLight->set_Is_IsNot(Is_IsNot_Enum::IsNot);
        expressionLight->setStateAddressing(NamedBeanAddressing::LocalVariable);
        expressionLight->setStateFormula("\"IT\"+index2");
        expressionLight->setStateLocalVariable("index2");
        expressionLight->setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionLight);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionLight = new ExpressionLight(digitalExpressionManager->getAutoSystemName(), "");
        expressionLight->AbstractNamedBean::setComment("A comment");
        expressionLight->setLight(light1);
        expressionLight->setBeanState(ExpressionLight::LightState::On);
        expressionLight->setAddressing(NamedBeanAddressing::LocalVariable);
        expressionLight->setFormula("\"IT\"+index");
        expressionLight->setLocalVariable("index");
        expressionLight->setReference("{IM1}");
        expressionLight->set_Is_IsNot(Is_IsNot_Enum::Is);
        expressionLight->setStateAddressing(NamedBeanAddressing::Formula);
        expressionLight->setStateFormula("\"IT\"+index2");
        expressionLight->setStateLocalVariable("index2");
        expressionLight->setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionLight);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionLight = new ExpressionLight(digitalExpressionManager->getAutoSystemName(), "");
        expressionLight->AbstractNamedBean::setComment("A comment");
        expressionLight->setLight(light1);
        expressionLight->setBeanState(ExpressionLight::LightState::Other);
        expressionLight->setAddressing(NamedBeanAddressing::Formula);
        expressionLight->setFormula("\"IT\"+index");
        expressionLight->setLocalVariable("index");
        expressionLight->setReference("{IM1}");
        expressionLight->set_Is_IsNot(Is_IsNot_Enum::IsNot);
        expressionLight->setStateAddressing(NamedBeanAddressing::Reference);
        expressionLight->setStateFormula("\"IT\"+index2");
        expressionLight->setStateLocalVariable("index2");
        expressionLight->setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionLight);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionLight = new ExpressionLight(digitalExpressionManager->getAutoSystemName(), "");
        expressionLight->AbstractNamedBean::setComment("A comment");
        expressionLight->setLight(light1);
        expressionLight->setBeanState(ExpressionLight::LightState::Off);
        expressionLight->setAddressing(NamedBeanAddressing::Reference);
        expressionLight->setFormula("\"IT\"+index");
        expressionLight->setLocalVariable("index");
        expressionLight->setReference("{IM1}");
        expressionLight->set_Is_IsNot(Is_IsNot_Enum::Is);
        expressionLight->setStateAddressing(NamedBeanAddressing::Direct);
        expressionLight->setStateFormula("\"IT\"+index2");
        expressionLight->setStateLocalVariable("index2");
        expressionLight->setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionLight);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        ExpressionLocalVariable* expressionLocalVariable = new ExpressionLocalVariable(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(expressionLocalVariable);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionLocalVariable = new ExpressionLocalVariable(digitalExpressionManager->getAutoSystemName(), "");
        expressionLocalVariable->AbstractNamedBean::setComment("A comment");
        expressionLocalVariable->setConstantValue("10");
        expressionLocalVariable->setCaseInsensitive(true);
        expressionLocalVariable->setCompareTo(ExpressionLocalVariable::CompareTo::Value);
        expressionLocalVariable->setVariableOperation(ExpressionLocalVariable::VariableOperation::GreaterThan);
        maleSocket = digitalExpressionManager->registerExpression(expressionLocalVariable);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionLocalVariable = new ExpressionLocalVariable(digitalExpressionManager->getAutoSystemName(), "");
        expressionLocalVariable->AbstractNamedBean::setComment("A comment");
        expressionLocalVariable->setLocalVariable("MyVar");
        expressionLocalVariable->setMemory(memory2);
        expressionLocalVariable->setCaseInsensitive(false);
        expressionLocalVariable->setCompareTo(ExpressionLocalVariable::CompareTo::Memory);
        expressionLocalVariable->setVariableOperation(ExpressionLocalVariable::VariableOperation::LessThan);
        maleSocket = digitalExpressionManager->registerExpression(expressionLocalVariable);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionLocalVariable = new ExpressionLocalVariable(digitalExpressionManager->getAutoSystemName(), "");
        expressionLocalVariable->AbstractNamedBean::setComment("A comment");
        expressionLocalVariable->setLocalVariable("MyVar");
        expressionLocalVariable->setMemory(memory2);
        expressionLocalVariable->setOtherLocalVariable("MyOtherVar");
        expressionLocalVariable->setCaseInsensitive(false);
        expressionLocalVariable->setCompareTo(ExpressionLocalVariable::CompareTo::LocalVariable);
        expressionLocalVariable->setVariableOperation(ExpressionLocalVariable::VariableOperation::LessThan);
        maleSocket = digitalExpressionManager->registerExpression(expressionLocalVariable);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionLocalVariable = new ExpressionLocalVariable(digitalExpressionManager->getAutoSystemName(), "");
        expressionLocalVariable->AbstractNamedBean::setComment("A comment");
        expressionLocalVariable->setLocalVariable("MyVar");
        expressionLocalVariable->setRegEx("/^Test$/");
        expressionLocalVariable->setMemory(memory2);
        expressionLocalVariable->setCaseInsensitive(false);
        expressionLocalVariable->setCompareTo(ExpressionLocalVariable::CompareTo::RegEx);
        expressionLocalVariable->setVariableOperation(ExpressionLocalVariable::VariableOperation::LessThan);
        maleSocket = digitalExpressionManager->registerExpression(expressionLocalVariable);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        ExpressionMemory* expressionMemory = new ExpressionMemory(digitalExpressionManager->getAutoSystemName(), "");
        expressionMemory->setMemoryOperation(ExpressionMemory::MemoryOperation::GreaterThan);
        expressionMemory->setCompareTo(ExpressionMemory::CompareTo::Memory);
        maleSocket = digitalExpressionManager->registerExpression(expressionMemory);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionMemory = new ExpressionMemory(digitalExpressionManager->getAutoSystemName(), "");
        expressionMemory->AbstractNamedBean::setComment("A comment");
        expressionMemory->setMemory(memory1);
        expressionMemory->setConstantValue("10");
        expressionMemory->setMemoryOperation(ExpressionMemory::MemoryOperation::LessThan);
        expressionMemory->setCompareTo(ExpressionMemory::CompareTo::Value);
        maleSocket = digitalExpressionManager->registerExpression(expressionMemory);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionMemory = new ExpressionMemory(digitalExpressionManager->getAutoSystemName(), "");
        expressionMemory->AbstractNamedBean::setComment("A comment");
        expressionMemory->setMemory(memory2);
        expressionMemory->setOtherMemory(memory3);
        expressionMemory->setMemoryOperation(ExpressionMemory::MemoryOperation::GreaterThan);
        expressionMemory->setCompareTo(ExpressionMemory::CompareTo::Memory);
        maleSocket = digitalExpressionManager->registerExpression(expressionMemory);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionMemory = new ExpressionMemory(digitalExpressionManager->getAutoSystemName(), "");
        expressionMemory->AbstractNamedBean::setComment("A comment");
        expressionMemory->setMemory(memory2);
        expressionMemory->setOtherMemory(memory3);
        expressionMemory->setLocalVariable("MyVar");
        expressionMemory->setMemoryOperation(ExpressionMemory::MemoryOperation::GreaterThan);
        expressionMemory->setCompareTo(ExpressionMemory::CompareTo::LocalVariable);
        maleSocket = digitalExpressionManager->registerExpression(expressionMemory);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionMemory = new ExpressionMemory(digitalExpressionManager->getAutoSystemName(), "");
        expressionMemory->AbstractNamedBean::setComment("A comment");
        expressionMemory->setMemory(memory2);
        expressionMemory->setOtherMemory(memory3);
        expressionMemory->setRegEx("/^Hello$/");
        expressionMemory->setMemoryOperation(ExpressionMemory::MemoryOperation::GreaterThan);
        expressionMemory->setCompareTo(ExpressionMemory::CompareTo::RegEx);
        maleSocket = digitalExpressionManager->registerExpression(expressionMemory);
        _and->getChild(indexExpr++)->_connect(maleSocket);

#if 0 // not yet implemented
        ExpressionOBlock expressionOBlock = new ExpressionOBlock(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(expressionOBlock);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionOBlock = new ExpressionOBlock(digitalExpressionManager->getAutoSystemName(), "");
        expressionOBlock->AbstractNamedBean::setComment("A comment");
        expressionOBlock.setOBlock("OB99");
        expressionOBlock.setBeanState(OBlock.OBlockStatus.Dark);
        expressionOBlock.setAddressing(NamedBeanAddressing::Direct);
        expressionOBlock.setFormula("\"IT\"+index");
        expressionOBlock.setLocalVariable("index");
        expressionOBlock.setReference("{IM1}");
        expressionOBlock.set_Is_IsNot(Is_IsNot_Enum.IsNot);
        expressionOBlock.setStateAddressing(NamedBeanAddressing::LocalVariable);
        expressionOBlock.setStateFormula("\"IT\"+index2");
        expressionOBlock.setStateLocalVariable("index2");
        expressionOBlock.setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionOBlock);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionOBlock = new ExpressionOBlock(digitalExpressionManager->getAutoSystemName(), "");
        expressionOBlock->AbstractNamedBean::setComment("A comment");
        expressionOBlock.setOBlock("OB99");
        expressionOBlock.setBeanState(OBlock.OBlockStatus.Allocated);
        expressionOBlock.setAddressing(NamedBeanAddressing::LocalVariable);
        expressionOBlock.setFormula("\"IT\"+index");
        expressionOBlock.setLocalVariable("index");
        expressionOBlock.setReference("{IM1}");
        expressionOBlock.set_Is_IsNot(Is_IsNot_Enum.Is);
        expressionOBlock.setStateAddressing(NamedBeanAddressing::Formula);
        expressionOBlock.setStateFormula("\"IT\"+index2");
        expressionOBlock.setStateLocalVariable("index2");
        expressionOBlock.setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionOBlock);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionOBlock = new ExpressionOBlock(digitalExpressionManager->getAutoSystemName(), "");
        expressionOBlock->AbstractNamedBean::setComment("A comment");
        expressionOBlock.setOBlock("OB99");
        expressionOBlock.setBeanState(OBlock.OBlockStatus.Occupied);
        expressionOBlock.setAddressing(NamedBeanAddressing::Formula);
        expressionOBlock.setFormula("\"IT\"+index");
        expressionOBlock.setLocalVariable("index");
        expressionOBlock.setReference("{IM1}");
        expressionOBlock.set_Is_IsNot(Is_IsNot_Enum.IsNot);
        expressionOBlock.setStateAddressing(NamedBeanAddressing::Reference);
        expressionOBlock.setStateFormula("\"IT\"+index2");
        expressionOBlock.setStateLocalVariable("index2");
        expressionOBlock.setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionOBlock);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionOBlock = new ExpressionOBlock(digitalExpressionManager->getAutoSystemName(), "");
        expressionOBlock->AbstractNamedBean::setComment("A comment");
        expressionOBlock.setOBlock("OB99");
        expressionOBlock.setBeanState(OBlock.OBlockStatus.OutOfService);
        expressionOBlock.setAddressing(NamedBeanAddressing::Reference);
        expressionOBlock.setFormula("\"IT\"+index");
        expressionOBlock.setLocalVariable("index");
        expressionOBlock.setReference("{IM1}");
        expressionOBlock.set_Is_IsNot(Is_IsNot_Enum.Is);
        expressionOBlock.setStateAddressing(NamedBeanAddressing::Direct);
        expressionOBlock.setStateFormula("\"IT\"+index2");
        expressionOBlock.setStateLocalVariable("index2");
        expressionOBlock.setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionOBlock);
        _and->getChild(indexExpr++)->_connect(maleSocket);
#endif

        ExpressionPower* expressionPower = new ExpressionPower(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(expressionPower);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionPower = new ExpressionPower(digitalExpressionManager->getAutoSystemName(), "");
        expressionPower->AbstractNamedBean::setComment("A comment");
        expressionPower->setBeanState(ExpressionPower::PowerState::Off);
        expressionPower->set_Is_IsNot(Is_IsNot_Enum::IsNot);
        maleSocket = digitalExpressionManager->registerExpression(expressionPower);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionPower = new ExpressionPower(digitalExpressionManager->getAutoSystemName(), "");
        expressionPower->AbstractNamedBean::setComment("A comment");
        expressionPower->setBeanState(ExpressionPower::PowerState::On);
        expressionPower->set_Is_IsNot(Is_IsNot_Enum::IsNot);
        maleSocket = digitalExpressionManager->registerExpression(expressionPower);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionPower = new ExpressionPower(digitalExpressionManager->getAutoSystemName(), "");
        expressionPower->AbstractNamedBean::setComment("A comment");
        expressionPower->setBeanState(ExpressionPower::PowerState::Other);
        expressionPower->set_Is_IsNot(Is_IsNot_Enum::IsNot);
        maleSocket = digitalExpressionManager->registerExpression(expressionPower);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        ExpressionReference* expressionReference = new ExpressionReference(digitalExpressionManager->getAutoSystemName(), "");
        expressionReference->setPointsTo(ExpressionReference::PointsTo::LogixNGTable);
        expressionReference->set_Is_IsNot(Is_IsNot_Enum::Is);
        maleSocket = digitalExpressionManager->registerExpression(expressionReference);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionReference = new ExpressionReference(digitalExpressionManager->getAutoSystemName(), "");
        expressionReference->AbstractNamedBean::setComment("A comment");
        expressionReference->setReference("IL1");
        expressionReference->setPointsTo(ExpressionReference::PointsTo::Light);
        expressionReference->set_Is_IsNot(Is_IsNot_Enum::IsNot);
        maleSocket = digitalExpressionManager->registerExpression(expressionReference);
        _and->getChild(indexExpr++)->_connect(maleSocket);

#if 0 // not yet implemented
#ifdef SCRIPTING_ENABLED
        ExpressionScript expressionScript = new ExpressionScript(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(expressionScript);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionScript = new ExpressionScript(digitalExpressionManager->getAutoSystemName(), "");
        expressionScript->AbstractNamedBean::setComment("A comment");
        expressionScript.setScript("result.setValue( sensors.provideSensor(\"IS1\").getState() == ACTIVE )");
        expressionScript.setRegisterListenerScript("sensors.provideSensor(\"IS1\").addPropertyChangeListener(self)");
        expressionScript.setUnregisterListenerScript("sensors.provideSensor(\"IS1\").removePropertyChangeListener(self)");
        maleSocket = digitalExpressionManager->registerExpression(expressionScript);
        _and->getChild(indexExpr++)->_connect(maleSocket);
#endif
#endif

        ExpressionSensor* expressionSensor = new ExpressionSensor(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(expressionSensor);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionSensor = new ExpressionSensor(digitalExpressionManager->getAutoSystemName(), "");
        expressionSensor->AbstractNamedBean::setComment("A comment");
        expressionSensor->setSensor(sensor1);
        expressionSensor->setBeanState(ExpressionSensor::SensorState::Inactive);
        expressionSensor->setAddressing(NamedBeanAddressing::Direct);
        expressionSensor->setFormula("\"IT\"+index");
        expressionSensor->setLocalVariable("index");
        expressionSensor->setReference("{IM1}");
        expressionSensor->set_Is_IsNot(Is_IsNot_Enum::IsNot);
        expressionSensor->setStateAddressing(NamedBeanAddressing::LocalVariable);
        expressionSensor->setStateFormula("\"IT\"+index2");
        expressionSensor->setStateLocalVariable("index2");
        expressionSensor->setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionSensor);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionSensor = new ExpressionSensor(digitalExpressionManager->getAutoSystemName(), "");
        expressionSensor->AbstractNamedBean::setComment("A comment");
        expressionSensor->setSensor(sensor1);
        expressionSensor->setBeanState(ExpressionSensor::SensorState::Inactive);
        expressionSensor->setAddressing(NamedBeanAddressing::LocalVariable);
        expressionSensor->setFormula("\"IT\"+index");
        expressionSensor->setLocalVariable("index");
        expressionSensor->setReference("{IM1}");
        expressionSensor->set_Is_IsNot(Is_IsNot_Enum::Is);
        expressionSensor->setStateAddressing(NamedBeanAddressing::Formula);
        expressionSensor->setStateFormula("\"IT\"+index2");
        expressionSensor->setStateLocalVariable("index2");
        expressionSensor->setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionSensor);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionSensor = new ExpressionSensor(digitalExpressionManager->getAutoSystemName(), "");
        expressionSensor->AbstractNamedBean::setComment("A comment");
        expressionSensor->setSensor(sensor1);
        expressionSensor->setBeanState(ExpressionSensor::SensorState::Inactive);
        expressionSensor->setAddressing(NamedBeanAddressing::Formula);
        expressionSensor->setFormula("\"IT\"+index");
        expressionSensor->setLocalVariable("index");
        expressionSensor->setReference("{IM1}");
        expressionSensor->set_Is_IsNot(Is_IsNot_Enum::IsNot);
        expressionSensor->setStateAddressing(NamedBeanAddressing::Reference);
        expressionSensor->setStateFormula("\"IT\"+index2");
        expressionSensor->setStateLocalVariable("index2");
        expressionSensor->setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionSensor);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionSensor = new ExpressionSensor(digitalExpressionManager->getAutoSystemName(), "");
        expressionSensor->AbstractNamedBean::setComment("A comment");
        expressionSensor->setSensor(sensor1);
        expressionSensor->setBeanState(ExpressionSensor::SensorState::Inactive);
        expressionSensor->setAddressing(NamedBeanAddressing::Reference);
        expressionSensor->setFormula("\"IT\"+index");
        expressionSensor->setLocalVariable("index");
        expressionSensor->setReference("{IM1}");
        expressionSensor->set_Is_IsNot(Is_IsNot_Enum::Is);
        expressionSensor->setStateAddressing(NamedBeanAddressing::Direct);
        expressionSensor->setStateFormula("\"IT\"+index2");
        expressionSensor->setStateLocalVariable("index2");
        expressionSensor->setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionSensor);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        ExpressionSignalHead* expressionSignalHead = new ExpressionSignalHead(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(expressionSignalHead);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionSignalHead = new ExpressionSignalHead(digitalExpressionManager->getAutoSystemName(), "");
        expressionSignalHead->AbstractNamedBean::setComment("A comment");
        expressionSignalHead->setSignalHead("IH1");
        expressionSignalHead->setAddressing(NamedBeanAddressing::Direct);
        expressionSignalHead->setFormula("\"IT\"+index");
        expressionSignalHead->setLocalVariable("index");
        expressionSignalHead->setReference("{IM1}");
        expressionSignalHead->setQueryAddressing(NamedBeanAddressing::LocalVariable);
        expressionSignalHead->setQueryFormula("\"IT\"+index2");
        expressionSignalHead->setQueryLocalVariable("index2");
        expressionSignalHead->setQueryReference("{IM2}");
        expressionSignalHead->setAppearanceAddressing(NamedBeanAddressing::Formula);
        expressionSignalHead->setAppearance(SignalHead::FLASHGREEN);
        expressionSignalHead->setAppearanceFormula("\"IT\"+index3");
        expressionSignalHead->setAppearanceLocalVariable("index3");
        expressionSignalHead->setAppearanceReference("{IM3}");
        expressionSignalHead->setExampleSignalHead("IH2");
        maleSocket = digitalExpressionManager->registerExpression(expressionSignalHead);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionSignalHead = new ExpressionSignalHead(digitalExpressionManager->getAutoSystemName(), "");
        expressionSignalHead->AbstractNamedBean::setComment("A comment");
        expressionSignalHead->setSignalHead("IH1");
        expressionSignalHead->setAddressing(NamedBeanAddressing::LocalVariable);
        expressionSignalHead->setFormula("\"IT\"+index");
        expressionSignalHead->setLocalVariable("index");
        expressionSignalHead->setReference("{IM1}");
        expressionSignalHead->setQueryAddressing(NamedBeanAddressing::Formula);
        expressionSignalHead->setQueryFormula("\"IT\"+index2");
        expressionSignalHead->setQueryLocalVariable("index2");
        expressionSignalHead->setQueryReference("{IM2}");
        expressionSignalHead->setAppearanceAddressing(NamedBeanAddressing::Reference);
        expressionSignalHead->setAppearance(SignalHead::FLASHLUNAR);
        expressionSignalHead->setAppearanceFormula("\"IT\"+index3");
        expressionSignalHead->setAppearanceLocalVariable("index3");
        expressionSignalHead->setAppearanceReference("{IM3}");
        maleSocket = digitalExpressionManager->registerExpression(expressionSignalHead);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionSignalHead = new ExpressionSignalHead(digitalExpressionManager->getAutoSystemName(), "");
        expressionSignalHead->AbstractNamedBean::setComment("A comment");
        expressionSignalHead->setSignalHead("IH1");
        expressionSignalHead->setAddressing(NamedBeanAddressing::Formula);
        expressionSignalHead->setFormula("\"IT\"+index");
        expressionSignalHead->setLocalVariable("index");
        expressionSignalHead->setReference("{IM1}");
        expressionSignalHead->setQueryAddressing(NamedBeanAddressing::Reference);
        expressionSignalHead->setQueryFormula("\"IT\"+index2");
        expressionSignalHead->setQueryLocalVariable("index2");
        expressionSignalHead->setQueryReference("{IM2}");
        expressionSignalHead->setAppearanceAddressing(NamedBeanAddressing::Direct);
        expressionSignalHead->setAppearance(SignalHead::FLASHRED);
        expressionSignalHead->setAppearanceFormula("\"IT\"+index3");
        expressionSignalHead->setAppearanceLocalVariable("index3");
        expressionSignalHead->setAppearanceReference("{IM3}");
        maleSocket = digitalExpressionManager->registerExpression(expressionSignalHead);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionSignalHead = new ExpressionSignalHead(digitalExpressionManager->getAutoSystemName(), "");
        expressionSignalHead->AbstractNamedBean::setComment("A comment");
        expressionSignalHead->setSignalHead("IH1");
        expressionSignalHead->setAddressing(NamedBeanAddressing::Reference);
        expressionSignalHead->setFormula("\"IT\"+index");
        expressionSignalHead->setLocalVariable("index");
        expressionSignalHead->setReference("{IM1}");
        expressionSignalHead->setQueryAddressing(NamedBeanAddressing::Direct);
        expressionSignalHead->setQueryFormula("\"IT\"+index2");
        expressionSignalHead->setQueryLocalVariable("index2");
        expressionSignalHead->setQueryReference("{IM2}");
        expressionSignalHead->setAppearanceAddressing(NamedBeanAddressing::LocalVariable);
        expressionSignalHead->setAppearance(SignalHead::FLASHYELLOW);
        expressionSignalHead->setAppearanceFormula("\"IT\"+index3");
        expressionSignalHead->setAppearanceLocalVariable("index3");
        expressionSignalHead->setAppearanceReference("{IM3}");
        maleSocket = digitalExpressionManager->registerExpression(expressionSignalHead);
        _and->getChild(indexExpr++)->_connect(maleSocket);

#if 0 // not yet implemented
        ExpressionSignalMast expressionSignalMast = new ExpressionSignalMast(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(expressionSignalMast);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionSignalMast = new ExpressionSignalMast(digitalExpressionManager->getAutoSystemName(), "");
        expressionSignalMast->AbstractNamedBean::setComment("A comment");
        expressionSignalMast.setSignalMast("IF$shsm:AAR-1946:CPL(IH1)");
        expressionSignalMast.setAddressing(NamedBeanAddressing::Direct);
        expressionSignalMast.setFormula("\"IT\"+index");
        expressionSignalMast.setLocalVariable("index");
        expressionSignalMast.setReference("{IM1}");
        expressionSignalMast.setQueryAddressing(NamedBeanAddressing::LocalVariable);
        expressionSignalMast.setQueryFormula("\"IT\"+index2");
        expressionSignalMast.setQueryLocalVariable("index2");
        expressionSignalMast.setQueryReference("{IM2}");
        expressionSignalMast.setAspectAddressing(NamedBeanAddressing::Formula);
        expressionSignalMast.setAspect("Medium Approach Slow");
        expressionSignalMast.setAspectFormula("\"IT\"+index3");
        expressionSignalMast.setAspectLocalVariable("index3");
        expressionSignalMast.setAspectReference("{IM3}");
        expressionSignalMast.setExampleSignalMast("IF$shsm:AAR-1946:CPL(IH1)");
        maleSocket = digitalExpressionManager->registerExpression(expressionSignalMast);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionSignalMast = new ExpressionSignalMast(digitalExpressionManager->getAutoSystemName(), "");
        expressionSignalMast->AbstractNamedBean::setComment("A comment");
        expressionSignalMast.setSignalMast("IF$shsm:AAR-1946:CPL(IH1)");
        expressionSignalMast.setAddressing(NamedBeanAddressing::LocalVariable);
        expressionSignalMast.setFormula("\"IT\"+index");
        expressionSignalMast.setLocalVariable("index");
        expressionSignalMast.setReference("{IM1}");
        expressionSignalMast.setQueryAddressing(NamedBeanAddressing::Formula);
        expressionSignalMast.setQueryFormula("\"IT\"+index2");
        expressionSignalMast.setQueryLocalVariable("index2");
        expressionSignalMast.setQueryReference("{IM2}");
        expressionSignalMast.setAspectAddressing(NamedBeanAddressing::Reference);
        expressionSignalMast.setAspect("Medium Approach");
        expressionSignalMast.setAspectFormula("\"IT\"+index3");
        expressionSignalMast.setAspectLocalVariable("index3");
        expressionSignalMast.setAspectReference("{IM3}");
        maleSocket = digitalExpressionManager->registerExpression(expressionSignalMast);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionSignalMast = new ExpressionSignalMast(digitalExpressionManager->getAutoSystemName(), "");
        expressionSignalMast->AbstractNamedBean::setComment("A comment");
        expressionSignalMast.setSignalMast("IF$shsm:AAR-1946:CPL(IH1)");
        expressionSignalMast.setAddressing(NamedBeanAddressing::Formula);
        expressionSignalMast.setFormula("\"IT\"+index");
        expressionSignalMast.setLocalVariable("index");
        expressionSignalMast.setReference("{IM1}");
        expressionSignalMast.setQueryAddressing(NamedBeanAddressing::Reference);
        expressionSignalMast.setQueryFormula("\"IT\"+index2");
        expressionSignalMast.setQueryLocalVariable("index2");
        expressionSignalMast.setQueryReference("{IM2}");
        expressionSignalMast.setAspectAddressing(NamedBeanAddressing::Direct);
        expressionSignalMast.setAspect("Approach");
        expressionSignalMast.setAspectFormula("\"IT\"+index3");
        expressionSignalMast.setAspectLocalVariable("index3");
        expressionSignalMast.setAspectReference("{IM3}");
        maleSocket = digitalExpressionManager->registerExpression(expressionSignalMast);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionSignalMast = new ExpressionSignalMast(digitalExpressionManager->getAutoSystemName(), "");
        expressionSignalMast->AbstractNamedBean::setComment("A comment");
        expressionSignalMast.setSignalMast("IF$shsm:AAR-1946:CPL(IH1)");
        expressionSignalMast.setAddressing(NamedBeanAddressing::Reference);
        expressionSignalMast.setFormula("\"IT\"+index");
        expressionSignalMast.setLocalVariable("index");
        expressionSignalMast.setReference("{IM1}");
        expressionSignalMast.setQueryAddressing(NamedBeanAddressing::Direct);
        expressionSignalMast.setQueryFormula("\"IT\"+index2");
        expressionSignalMast.setQueryLocalVariable("index2");
        expressionSignalMast.setQueryReference("{IM2}");
        expressionSignalMast.setAspectAddressing(NamedBeanAddressing::LocalVariable);
        expressionSignalMast.setAspect("Medium Approach Slow");
        expressionSignalMast.setAspectFormula("\"IT\"+index3");
        expressionSignalMast.setAspectLocalVariable("index3");
        expressionSignalMast.setAspectReference("{IM3}");
        maleSocket = digitalExpressionManager->registerExpression(expressionSignalMast);
        _and->getChild(indexExpr++)->_connect(maleSocket);
#endif

        ExpressionTurnout* expressionTurnout = new ExpressionTurnout(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(expressionTurnout);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionTurnout = new ExpressionTurnout(digitalExpressionManager->getAutoSystemName(), "");
        expressionTurnout->AbstractNamedBean::setComment("A comment");
        expressionTurnout->setTurnout(turnout1);
        expressionTurnout->setBeanState(ExpressionTurnout::TurnoutState::Closed);
        expressionTurnout->setAddressing(NamedBeanAddressing::Direct);
        expressionTurnout->setFormula("\"IT\"+index");
        expressionTurnout->setLocalVariable("index");
        expressionTurnout->setReference("{IM1}");
        expressionTurnout->set_Is_IsNot(Is_IsNot_Enum::IsNot);
        expressionTurnout->setStateAddressing(NamedBeanAddressing::LocalVariable);
        expressionTurnout->setStateFormula("\"IT\"+index2");
        expressionTurnout->setStateLocalVariable("index2");
        expressionTurnout->setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionTurnout);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionTurnout = new ExpressionTurnout(digitalExpressionManager->getAutoSystemName(), "");
        expressionTurnout->AbstractNamedBean::setComment("A comment");
        expressionTurnout->setTurnout(turnout1);
        expressionTurnout->setBeanState(ExpressionTurnout::TurnoutState::Thrown);
        expressionTurnout->setAddressing(NamedBeanAddressing::LocalVariable);
        expressionTurnout->setFormula("\"IT\"+index");
        expressionTurnout->setLocalVariable("index");
        expressionTurnout->setReference("{IM1}");
        expressionTurnout->set_Is_IsNot(Is_IsNot_Enum::Is);
        expressionTurnout->setStateAddressing(NamedBeanAddressing::Formula);
        expressionTurnout->setStateFormula("\"IT\"+index2");
        expressionTurnout->setStateLocalVariable("index2");
        expressionTurnout->setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionTurnout);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionTurnout = new ExpressionTurnout(digitalExpressionManager->getAutoSystemName(), "");
        expressionTurnout->AbstractNamedBean::setComment("A comment");
        expressionTurnout->setTurnout(turnout1);
        expressionTurnout->setBeanState(ExpressionTurnout::TurnoutState::Other);
        expressionTurnout->setAddressing(NamedBeanAddressing::Formula);
        expressionTurnout->setFormula("\"IT\"+index");
        expressionTurnout->setLocalVariable("index");
        expressionTurnout->setReference("{IM1}");
        expressionTurnout->set_Is_IsNot(Is_IsNot_Enum::IsNot);
        expressionTurnout->setStateAddressing(NamedBeanAddressing::Reference);
        expressionTurnout->setStateFormula("\"IT\"+index2");
        expressionTurnout->setStateLocalVariable("index2");
        expressionTurnout->setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionTurnout);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionTurnout = new ExpressionTurnout(digitalExpressionManager->getAutoSystemName(), "");
        expressionTurnout->AbstractNamedBean::setComment("A comment");
        expressionTurnout->setTurnout(turnout1);
        expressionTurnout->setBeanState(ExpressionTurnout::TurnoutState::Closed);
        expressionTurnout->setAddressing(NamedBeanAddressing::Reference);
        expressionTurnout->setFormula("\"IT\"+index");
        expressionTurnout->setLocalVariable("index");
        expressionTurnout->setReference("{IM1}");
        expressionTurnout->set_Is_IsNot(Is_IsNot_Enum::Is);
        expressionTurnout->setStateAddressing(NamedBeanAddressing::Direct);
        expressionTurnout->setStateFormula("\"IT\"+index2");
        expressionTurnout->setStateLocalVariable("index2");
        expressionTurnout->setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionTurnout);
        _and->getChild(indexExpr++)->_connect(maleSocket);

#if 0 // not yet implemented
        ExpressionWarrant expressionWarrant = new ExpressionWarrant(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(expressionWarrant);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionWarrant = new ExpressionWarrant(digitalExpressionManager->getAutoSystemName(), "");
        expressionWarrant->AbstractNamedBean::setComment("A comment");
        expressionWarrant.setWarrant("IW99");
        expressionWarrant.setBeanState(ExpressionWarrant.WarrantState.RouteAllocated);
        expressionWarrant.setAddressing(NamedBeanAddressing::Direct);
        expressionWarrant.setFormula("\"IT\"+index");
        expressionWarrant.setLocalVariable("index");
        expressionWarrant.setReference("{IM1}");
        expressionWarrant.set_Is_IsNot(Is_IsNot_Enum.IsNot);
        expressionWarrant.setStateAddressing(NamedBeanAddressing::LocalVariable);
        expressionWarrant.setStateFormula("\"IT\"+index2");
        expressionWarrant.setStateLocalVariable("index2");
        expressionWarrant.setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionWarrant);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionWarrant = new ExpressionWarrant(digitalExpressionManager->getAutoSystemName(), "");
        expressionWarrant->AbstractNamedBean::setComment("A comment");
        expressionWarrant.setWarrant("IW99");
        expressionWarrant.setBeanState(ExpressionWarrant.WarrantState.RouteFree);
        expressionWarrant.setAddressing(NamedBeanAddressing::LocalVariable);
        expressionWarrant.setFormula("\"IT\"+index");
        expressionWarrant.setLocalVariable("index");
        expressionWarrant.setReference("{IM1}");
        expressionWarrant.set_Is_IsNot(Is_IsNot_Enum.Is);
        expressionWarrant.setStateAddressing(NamedBeanAddressing::Formula);
        expressionWarrant.setStateFormula("\"IT\"+index2");
        expressionWarrant.setStateLocalVariable("index2");
        expressionWarrant.setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionWarrant);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionWarrant = new ExpressionWarrant(digitalExpressionManager->getAutoSystemName(), "");
        expressionWarrant->AbstractNamedBean::setComment("A comment");
        expressionWarrant.setWarrant("IW99");
        expressionWarrant.setBeanState(ExpressionWarrant.WarrantState.RouteOccupied);
        expressionWarrant.setAddressing(NamedBeanAddressing::Formula);
        expressionWarrant.setFormula("\"IT\"+index");
        expressionWarrant.setLocalVariable("index");
        expressionWarrant.setReference("{IM1}");
        expressionWarrant.set_Is_IsNot(Is_IsNot_Enum.IsNot);
        expressionWarrant.setStateAddressing(NamedBeanAddressing::Reference);
        expressionWarrant.setStateFormula("\"IT\"+index2");
        expressionWarrant.setStateLocalVariable("index2");
        expressionWarrant.setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionWarrant);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        expressionWarrant = new ExpressionWarrant(digitalExpressionManager->getAutoSystemName(), "");
        expressionWarrant->AbstractNamedBean::setComment("A comment");
        expressionWarrant.setWarrant("IW99");
        expressionWarrant.setBeanState(ExpressionWarrant.WarrantState.RouteSet);
        expressionWarrant.setAddressing(NamedBeanAddressing::Reference);
        expressionWarrant.setFormula("\"IT\"+index");
        expressionWarrant.setLocalVariable("index");
        expressionWarrant.setReference("{IM1}");
        expressionWarrant.set_Is_IsNot(Is_IsNot_Enum.Is);
        expressionWarrant.setStateAddressing(NamedBeanAddressing::Direct);
        expressionWarrant.setStateFormula("\"IT\"+index2");
        expressionWarrant.setStateLocalVariable("index2");
        expressionWarrant.setStateReference("{IM2}");
        maleSocket = digitalExpressionManager->registerExpression(expressionWarrant);
        _and->getChild(indexExpr++)->_connect(maleSocket);

#endif
        False* false1 = new False(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(false1);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        false1 = new False(digitalExpressionManager->getAutoSystemName(), "");
        false1->AbstractNamedBean::setComment("A comment");
        maleSocket = digitalExpressionManager->registerExpression(false1);
        _and->getChild(indexExpr++)->_connect(maleSocket);


        DigitalFormula* formula =
                new DigitalFormula(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(formula);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        formula = new DigitalFormula(digitalExpressionManager->getAutoSystemName(), "");
        formula->AbstractNamedBean::setComment("A comment");
        formula->setFormula("n + 1");
        maleSocket = digitalExpressionManager->registerExpression(formula);
        _and->getChild(indexExpr++)->_connect(maleSocket);


        Hold* hold = new Hold(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(hold);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        hold = new Hold(digitalExpressionManager->getAutoSystemName(), "");
        hold->AbstractNamedBean::setUserName("A hold expression");
        hold->AbstractNamedBean::setComment("A comment");
        maleSocket = digitalExpressionManager->registerExpression(hold);
        _and->getChild(indexExpr++)->_connect(maleSocket);


        LastResultOfDigitalExpression* lastResultOfDigitalExpression =
                new LastResultOfDigitalExpression(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(lastResultOfDigitalExpression);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        lastResultOfDigitalExpression = new LastResultOfDigitalExpression(digitalExpressionManager->getAutoSystemName(), "");
        lastResultOfDigitalExpression->AbstractNamedBean::setComment("A comment");
        lastResultOfDigitalExpression->setDigitalExpression("A hold expression");
        maleSocket = digitalExpressionManager->registerExpression(lastResultOfDigitalExpression);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        Expressions::LogData* logDataExpr = new Expressions::LogData(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(logDataExpr);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        logDataExpr = new Expressions::LogData(digitalExpressionManager->getAutoSystemName(), "");
        logDataExpr->AbstractNamedBean::setComment("A comment");
        logDataExpr->setLogToLog(true);
#ifdef ENABLE_SCRIPTING
        logData->setLogToScriptOutput(true);
#endif
        logDataExpr->setFormat("Some text");
        logDataExpr->setFormatType(Expressions::LogData::FormatType::OnlyText);
        logDataExpr->getDataList().append( Expressions::LogData::Data(Expressions::LogData::DataType::LocalVariable, "MyVar"));
        maleSocket = digitalExpressionManager->registerExpression(logDataExpr);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        logDataExpr = new Expressions::LogData(digitalExpressionManager->getAutoSystemName(), "");
        logDataExpr->AbstractNamedBean::setComment("A comment");
        logDataExpr->setLogToLog(true);
#ifdef ENABLE_SCRIPTING
        logData->setLogToScriptOutput(true);
#endif
        logDataExpr->setFormat("");
        logDataExpr->setFormatType(Expressions::LogData::FormatType::CommaSeparatedList);
        logDataExpr->getDataList().append( Expressions::LogData::Data(Expressions::LogData::DataType::Memory, "IM1"));
        maleSocket = digitalExpressionManager->registerExpression(logDataExpr);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        logDataExpr = new Expressions::LogData(digitalExpressionManager->getAutoSystemName(), "");
        logDataExpr->AbstractNamedBean::setComment("A comment");
        logDataExpr->setLogToLog(true);
#ifdef ENABLE_SCRIPTING
        logData->setLogToScriptOutput(true);
#endif
        logDataExpr->setFormat("MyVar has the value %s");
        logDataExpr->setFormatType(Expressions::LogData::FormatType::StringFormat);
        logDataExpr->getDataList().append( Expressions::LogData::Data(Expressions::LogData::DataType::Reference, "{MyVar}"));
        maleSocket = digitalExpressionManager->registerExpression(logDataExpr);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        logDataExpr = new Expressions::LogData(digitalExpressionManager->getAutoSystemName(), "");
        logDataExpr->AbstractNamedBean::setComment("A comment");
        logDataExpr->setLogToLog(true);
#ifdef ENABLE_SCRIPTING
        logData->setLogToScriptOutput(true);
#endif
        logDataExpr->setFormat("str(10): %s, 25: %d, IM1: %s, MyVar: %s");
        logDataExpr->setFormatType(Expressions::LogData::FormatType::StringFormat);
        logDataExpr->getDataList().append( Expressions::LogData::Data(Expressions::LogData::DataType::Formula, "str(10)"));
        logDataExpr->getDataList().append( Expressions::LogData::Data(Expressions::LogData::DataType::Formula, "25"));
        logDataExpr->getDataList().append( Expressions::LogData::Data(Expressions::LogData::DataType::Memory, "IM1"));
        logDataExpr->getDataList().append( Expressions::LogData::Data(Expressions::LogData::DataType::LocalVariable, "MyVar"));
        maleSocket = digitalExpressionManager->registerExpression(logDataExpr);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        Not* _not = new Not(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(_not);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        _not = new Not(digitalExpressionManager->getAutoSystemName(), "");
        _not->AbstractNamedBean::setComment("A comment");
        maleSocket = digitalExpressionManager->registerExpression(_not);
        _and->getChild(indexExpr++)->_connect(maleSocket);


        Or* _or = new Or(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(_or);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        _or = new Or(digitalExpressionManager->getAutoSystemName(), "");
        _or->AbstractNamedBean::setComment("A comment");
        maleSocket = digitalExpressionManager->registerExpression(_or);
        _and->getChild(indexExpr++)->_connect(maleSocket);


        TriggerOnce* triggerOnce = new TriggerOnce(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(triggerOnce);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        triggerOnce = new TriggerOnce(digitalExpressionManager->getAutoSystemName(), "");
        triggerOnce->AbstractNamedBean::setComment("A comment");
        maleSocket = digitalExpressionManager->registerExpression(triggerOnce);
        _and->getChild(indexExpr++)->_connect(maleSocket);


        True* true1 = new True(digitalExpressionManager->getAutoSystemName(), "");
        maleSocket = digitalExpressionManager->registerExpression(true1);
        maleSocket->setEnabled(false);
        _and->getChild(indexExpr++)->_connect(maleSocket);

        true1 = new True(digitalExpressionManager->getAutoSystemName(), "");
        true1->AbstractNamedBean::setComment("A comment");
        maleSocket = digitalExpressionManager->registerExpression(true1);
        _and->getChild(indexExpr++)->_connect(maleSocket);


        doAnalogAction = new DoAnalogAction(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(doAnalogAction);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        AnalogExpressionConstant* analogExpressionConstant = new AnalogExpressionConstant(analogExpressionManager->getAutoSystemName(), "");
        maleSocket = analogExpressionManager->registerExpression(analogExpressionConstant);
        maleSocket->setEnabled(false);
        doAnalogAction->getChild(0)->_connect(maleSocket);

        AnalogActionMemory* analogActionMemory = new AnalogActionMemory(analogActionManager->getAutoSystemName(), "");
        maleSocket = analogActionManager->registerAction(analogActionMemory);
        maleSocket->setEnabled(false);
        doAnalogAction->getChild(1)->_connect(maleSocket);


        doAnalogAction = new DoAnalogAction(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(doAnalogAction);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        analogExpressionConstant = new AnalogExpressionConstant(analogExpressionManager->getAutoSystemName(), "");
        analogExpressionConstant->AbstractNamedBean::setComment("A comment");
        analogExpressionConstant->setValue(12.44);
        maleSocket = analogExpressionManager->registerExpression(analogExpressionConstant);
        doAnalogAction->getChild(0)->_connect(maleSocket);

        analogActionMemory = new AnalogActionMemory(analogActionManager->getAutoSystemName(), "");
        analogActionMemory->AbstractNamedBean::setComment("A comment");
        analogActionMemory->setMemory(memory2);
        analogActionMemory->setValue(10.22);
        maleSocket = analogActionManager->registerAction(analogActionMemory);
        doAnalogAction->getChild(1)->_connect(maleSocket);


        doAnalogAction = new DoAnalogAction(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(doAnalogAction);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        AnalogExpressionMemory* analogExpressionMemory = new AnalogExpressionMemory(analogExpressionManager->getAutoSystemName(), "");
        maleSocket = analogExpressionManager->registerExpression(analogExpressionMemory);
        maleSocket->setEnabled(false);
        doAnalogAction->getChild(0)->_connect(maleSocket);

        AnalogMany* analogMany = new AnalogMany(analogActionManager->getAutoSystemName(), "");
        maleSocket = analogActionManager->registerAction(analogMany);
        maleSocket->setEnabled(false);
        doAnalogAction->getChild(1)->_connect(maleSocket);


        doAnalogAction = new DoAnalogAction(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(doAnalogAction);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        analogExpressionMemory = new AnalogExpressionMemory(analogExpressionManager->getAutoSystemName(), "");
        analogExpressionMemory->AbstractNamedBean::setComment("A comment");
        analogExpressionMemory->setMemory(memory1);
        maleSocket = analogExpressionManager->registerExpression(analogExpressionMemory);
        doAnalogAction->getChild(0)->_connect(maleSocket);

        analogMany = new AnalogMany(analogActionManager->getAutoSystemName(), "");
        analogMany->AbstractNamedBean::setComment("A comment");
        maleSocket = analogActionManager->registerAction(analogMany);
        doAnalogAction->getChild(1)->_connect(maleSocket);


        doAnalogAction = new DoAnalogAction(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(doAnalogAction);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        AnalogFormula* analogFormula = new AnalogFormula(analogExpressionManager->getAutoSystemName(), "");
        maleSocket = analogExpressionManager->registerExpression(analogFormula);
        maleSocket->setEnabled(false);
        doAnalogAction->getChild(0)->_connect(maleSocket);


        doAnalogAction = new DoAnalogAction(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(doAnalogAction);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        analogFormula = new AnalogFormula(analogExpressionManager->getAutoSystemName(), "");
        analogFormula->AbstractNamedBean::setComment("A comment");
        analogFormula->setFormula("sin(a)*2 + 14");
        maleSocket = analogExpressionManager->registerExpression(analogFormula);
        doAnalogAction->getChild(0)->_connect(maleSocket);


        doAnalogAction = new DoAnalogAction(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(doAnalogAction);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        TimeSinceMidnight* timeSinceMidnight = new TimeSinceMidnight(analogExpressionManager->getAutoSystemName(), "");
        maleSocket = analogExpressionManager->registerExpression(timeSinceMidnight);
        maleSocket->setEnabled(false);
        timeSinceMidnight->setType(TimeSinceMidnight::Type::SystemClock);
        doAnalogAction->getChild(0)->_connect(maleSocket);


        doAnalogAction = new DoAnalogAction(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(doAnalogAction);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        timeSinceMidnight = new TimeSinceMidnight(analogExpressionManager->getAutoSystemName(), "");
        timeSinceMidnight->AbstractNamedBean::setComment("A comment");
        timeSinceMidnight->setType(TimeSinceMidnight::Type::FastClock);
        maleSocket = analogExpressionManager->registerExpression(timeSinceMidnight);
        doAnalogAction->getChild(0)->_connect(maleSocket);



        doStringAction = new DoStringAction(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(doStringAction);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        StringExpressionConstant* stringExpressionConstant = new StringExpressionConstant(stringExpressionManager->getAutoSystemName(), "");
        maleSocket = stringExpressionManager->registerExpression(stringExpressionConstant);
        maleSocket->setEnabled(false);
        doStringAction->getChild(0)->_connect(maleSocket);

        StringActionMemory* stringActionMemory = new StringActionMemory(stringActionManager->getAutoSystemName(), "");
        maleSocket = stringActionManager->registerAction(stringActionMemory);
        maleSocket->setEnabled(false);
        doStringAction->getChild(1)->_connect(maleSocket);


        doStringAction = new DoStringAction(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(doStringAction);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        stringExpressionConstant = new StringExpressionConstant(stringExpressionManager->getAutoSystemName(), "");
        stringExpressionConstant->AbstractNamedBean::setComment("A comment");
        stringExpressionConstant->setValue("Some string");
        maleSocket = stringExpressionManager->registerExpression(stringExpressionConstant);
        doStringAction->getChild(0)->_connect(maleSocket);

        stringActionMemory = new StringActionMemory(stringActionManager->getAutoSystemName(), "");
        stringActionMemory->AbstractNamedBean::setComment("A comment");
        stringActionMemory->setMemory(memory2);
        stringActionMemory->setValue("Hello");
        maleSocket = stringActionManager->registerAction(stringActionMemory);
        doStringAction->getChild(1)->_connect(maleSocket);


        doStringAction = new DoStringAction(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(doStringAction);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        StringExpressionMemory* stringExpressionMemory = new StringExpressionMemory(stringExpressionManager->getAutoSystemName(), "");
        maleSocket = stringExpressionManager->registerExpression(stringExpressionMemory);
        maleSocket->setEnabled(false);
        doStringAction->getChild(0)->_connect(maleSocket);

        StringMany* stringMany = new StringMany(stringActionManager->getAutoSystemName(), "");
        maleSocket = stringActionManager->registerAction(stringMany);
        maleSocket->setEnabled(false);
        doStringAction->getChild(1)->_connect(maleSocket);


        doStringAction = new DoStringAction(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(doStringAction);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        stringExpressionMemory = new StringExpressionMemory(stringExpressionManager->getAutoSystemName(), "");
        stringExpressionMemory->AbstractNamedBean::setComment("A comment");
        stringExpressionMemory->setMemory(memory1);
        maleSocket = stringExpressionManager->registerExpression(stringExpressionMemory);
        doStringAction->getChild(0)->_connect(maleSocket);

        stringMany = new StringMany(stringActionManager->getAutoSystemName(), "");
        stringMany->AbstractNamedBean::setComment("A comment");
        maleSocket = stringActionManager->registerAction(stringMany);
        doStringAction->getChild(1)->_connect(maleSocket);


        doStringAction = new DoStringAction(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(doStringAction);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        StringFormula* stringFormula = new StringFormula(stringExpressionManager->getAutoSystemName(), "");
        maleSocket = stringExpressionManager->registerExpression(stringFormula);
        maleSocket->setEnabled(false);
        doStringAction->getChild(0)->_connect(maleSocket);


        doStringAction = new DoStringAction(digitalActionManager->getAutoSystemName(), "");
        maleSocket = digitalActionManager->registerAction(doStringAction);
        maleSocket->setEnabled(false);
        actionManySocket->getChild(indexAction++)->_connect(maleSocket);

        stringFormula = new StringFormula(stringExpressionManager->getAutoSystemName(), "");
        stringFormula->AbstractNamedBean::setComment("A comment");
        stringFormula->setFormula("sin(a)*2 + 14");
        maleSocket = stringExpressionManager->registerExpression(stringFormula);
        doStringAction->getChild(0)->_connect(maleSocket);




        // Check that we have actions/expressions in every managers
        Assert::assertNotEquals(0, ((DefaultLogixNGManager*)logixNG_Manager)->AbstractManager::getNamedBeanSet().size(), __FILE__, __LINE__);
        Assert::assertNotEquals(0, analogActionManager->getNamedBeanSet().size(), __FILE__, __LINE__);
        Assert::assertNotEquals(0, analogExpressionManager->getNamedBeanSet().size(), __FILE__, __LINE__);
        Assert::assertNotEquals(0, digitalActionManager->getNamedBeanSet().size(), __FILE__, __LINE__);
        Assert::assertNotEquals(0, digitalExpressionManager->getNamedBeanSet().size(), __FILE__, __LINE__);
        Assert::assertNotEquals(0, stringActionManager->getNamedBeanSet().size(), __FILE__, __LINE__);
        Assert::assertNotEquals(0, stringExpressionManager->getNamedBeanSet().size(), __FILE__, __LINE__);
        Assert::assertNotEquals(0, ((DefaultModuleManager*)InstanceManager::getDefault("ModuleManager"))->getNamedBeanSet().size(), __FILE__, __LINE__);
        Assert::assertNotEquals(0, ((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"))->getNamedBeanSet().size(), __FILE__, __LINE__);


#if 0 //TODO:
        // Check that we can add variables to all actions/expressions and that
        // the variables are stored in the panel file
//        femaleRootSocket.forEntireTree((Base b) -> {
//            if (b instanceof MaleSocket) {
//                addVariables((MaleSocket) b);
//            }
//        });
        femaleRootSocket->forEntireTree(new StoreAndLoadTest_run1(this));

        // Check that we can rename the female sockets and that the names
        // are stored in the panel file.
//        femaleRootSocket.forEntireTree((Base b) -> {
//            if (b instanceof FemaleSocket) {
//                ((FemaleSocket)b).setName(getRandomString(10));
//            }
//        });
#endif

/*
        if (1==1) {
            final String treeIndent = "   ";
            StringWriter stringWriter = new StringWriter();
            PrintWriter printWriter = new PrintWriter(stringWriter);
            logixNG_Manager.printTree(Locale.ENGLISH, printWriter, treeIndent);

            System.out.println("--------------------------------------------");
            System.out.println("The current tree:");
            System.out.println("XXX"+stringWriter.toString()+"XXX");
            System.out.println("--------------------------------------------");
            System.out.println("--------------------------------------------");
            System.out.println("--------------------------------------------");
            System.out.println("--------------------------------------------");
            System.out.println("--------------------------------------------");
            System.out.println("--------------------------------------------");
            System.out.println("--------------------------------------------");
            System.out.println("--------------------------------------------");
            System.out.println("--------------------------------------------");
            System.out.println("--------------------------------------------");

            log->error("--------------------------------------------");
            log->error("The current tree:");
            log->error("XXX"+stringWriter.toString()+"XXX");
            log->error("--------------------------------------------");
            log->error("--------------------------------------------");
            log->error("--------------------------------------------");
            log->error("--------------------------------------------");
            log->error("--------------------------------------------");
            log->error("--------------------------------------------");
            log->error("--------------------------------------------");
            log->error("--------------------------------------------");
            log->error("--------------------------------------------");
            log->error("--------------------------------------------");
            log->error("--------------------------------------------");
//            return;
        }
*/



        // Store panels
        ConfigureManager* cm = (JmriConfigurationManager*)InstanceManager::getNullableDefault("ConfigureManager");
        if (cm == nullptr) {
            log->error("Unable to get default configure manager");
        } else {
            FileUtil::createDirectory(FileUtil::getUserFilesPath() + "temp");
            File* firstFile = new File(FileUtil::getUserFilesPath() + "temp/" + "LogixNG_temp.xml");
            File* secondFile = new File(FileUtil::getUserFilesPath() + "temp/" + "LogixNG.xml");
            log->info(tr("Temporary first file: %1\n").arg(firstFile->getAbsoluteFile()->toString()));
            log->info(tr("Temporary second file: %1\n").arg(secondFile->getAbsoluteFile()->toString()));

            /*final*/ QString treeIndent = "   ";
            StringWriter* stringWriter = new StringWriter();
            PrintWriter* printWriter = new PrintWriter(stringWriter);
            int mutableInt = 0;
            logixNG_Manager->printTree(QLocale(), printWriter, treeIndent, &mutableInt);
            /*final*/ QString originalTree = stringWriter->toString();

            bool results = cm->storeUser(firstFile);
            log->debug(results ? "store was successful" : "store failed");
            if (!results) {
                log->error("Failed to store panel");
                throw new RuntimeException("Failed to store panel");
            }

            // Add the header comment to the xml file
            addHeader(firstFile, secondFile);


            //**********************************
            // Delete all the LogixNGs, ConditionalNGs, and so on before reading the file.
            //**********************************

            QSet</*LogixNG*/NamedBean*> logixNG_Set = QSet</*LogixNG*/NamedBean*>(logixNG_Manager->getNamedBeanSet());
            for (NamedBean* nb : logixNG_Set) {
             LogixNG* aLogixNG = (DefaultLogixNG*)nb->self();
                logixNG_Manager->deleteLogixNG(aLogixNG);
            }

            QSet</*ConditionalNG*/NamedBean*> conditionalNGSet = QSet</*ConditionalNG*/NamedBean*> (conditionalNGManager->getNamedBeanSet());
            for (NamedBean* nb  : conditionalNGSet) {
             ConditionalNG* aConditionalNG = (DefaultConditionalNG*)nb->self();
                conditionalNGManager->deleteConditionalNG(aConditionalNG);
            }

            QSet</*MaleAnalogActionSocket*/NamedBean*> analogActionSet = QSet</*MaleAnalogActionSocket*/NamedBean*>(analogActionManager->getNamedBeanSet());
            for (NamedBean* nb : analogActionSet) {
            AbstractAnalogAction*  aaa = (AbstractAnalogAction*)nb->self();
            DefaultMaleAnalogActionSocket* dmas = (DefaultMaleAnalogActionSocket*)aaa->getParent()->bself();
             //MaleAnalogActionSocket* aAnalogAction = (DefaultMaleAnalogActionSocket*)nb->self();
                analogActionManager->deleteAnalogAction(/*aAnalogAction*/dmas);
            }
#if 1
            QSet</*MaleAnalogExpressionSocket*/NamedBean*> analogExpressionSet = QSet</*MaleAnalogExpressionSocket*/NamedBean*>(analogExpressionManager->getNamedBeanSet());
            for (NamedBean* nb : analogExpressionSet) {
             QString sn = nb->getSystemName();
             //MaleAnalogExpressionSocket* aAnalogExpression = (DefaultMaleAnalogExpressionSocket*)nb->self();
             AbstractAnalogExpression* aae= (AbstractAnalogExpression*)nb->self();
             Base* b = aae->getParent();
             QObject* bo = (QObject*)aae->getParent();
             DefaultMaleAnalogExpressionSocket* aAnalogExpression = (DefaultMaleAnalogExpressionSocket*)aae->getParent()->bself();
             //DefaultMaleAnalogExpressionSocket* aAnalogExpression = (DefaultMaleAnalogExpressionSocket*)bo;
             analogExpressionManager->deleteAnalogExpression(aAnalogExpression);
            }
#endif
            QSet</*MaleDigitalActionSocket*/NamedBean*> digitalActionSet = QSet</*MaleDigitalActionSocket*/NamedBean*>(digitalActionManager->getNamedBeanSet());
            for (NamedBean* nb: digitalActionSet) {
             //MaleDigitalActionSocket* aDigitalActionSocket = (DefaultMaleDigitalActionSocket*)nb->self();
             AbstractDigitalAction* ada = (AbstractDigitalAction*)nb->self();
             DefaultMaleDigitalActionSocket* aDigitalActionSocket = (DefaultMaleDigitalActionSocket*)ada->getParent()->bself();
             digitalActionManager->deleteDigitalAction(aDigitalActionSocket);
            }

            QSet</*MaleDigitalBooleanActionSocket*/NamedBean*> digitalBooleanActionSet =QSet</*MaleDigitalBooleanActionSocket*/NamedBean*>(digitalBooleanActionManager->getNamedBeanSet());
            for (NamedBean* nb : digitalBooleanActionSet) {
              DefaultMaleDigitalBooleanActionSocket* aDigitalBooleanAction =   (DefaultMaleDigitalBooleanActionSocket*)nb->self();
//             AbstractDigitalBooleanAction* adba = (AbstractDigitalBooleanAction*)nb->self();
//             DefaultMaleDigitalBooleanActionSocket* aDigitalBooleanAction = (DefaultMaleDigitalBooleanActionSocket*)adba->getParent()->bself();
             digitalBooleanActionManager->deleteDigitalBooleanAction(aDigitalBooleanAction);
            }

            QSet</*MaleDigitalExpressionSocket*/NamedBean*> digitalExpressionSet = QSet</*MaleDigitalExpressionSocket*/NamedBean*>(digitalExpressionManager->getNamedBeanSet());
            for (NamedBean* nb : digitalExpressionSet) {
             DefaultMaleDigitalExpressionSocket* aDigitalExpression = (DefaultMaleDigitalExpressionSocket*)nb->self();
//             AbstractDigitalExpression* ade = (AbstractDigitalExpression*)nb->self();
//             MaleDigitalExpressionSocket* aDigitalExpression = (DefaultMaleDigitalExpressionSocket*)ade->getParent()->bself();
             digitalExpressionManager->deleteDigitalExpression(aDigitalExpression);
            }

            QSet</*MaleStringActionSocket*/NamedBean*> stringActionSet = QSet</*MaleStringActionSocket*/NamedBean*>(stringActionManager->getNamedBeanSet());
            for (NamedBean* nb : stringActionSet) {
             //MaleStringActionSocket* aStringAction = (DefaultMaleStringActionSocket*)nb->self();
             AbstractStringAction* asa = (AbstractStringAction*)nb->self();
             MaleStringActionSocket* aStringAction = (DefaultMaleStringActionSocket*)asa->getParent()->bself();
             stringActionManager->deleteStringAction(aStringAction);
            }

            QSet</*MaleStringExpressionSocket*/NamedBean*> stringExpressionSet = QSet</*MaleStringExpressionSocket*/NamedBean*> (stringExpressionManager->getNamedBeanSet());
            for (NamedBean* nb : stringExpressionSet) {
             DefaultMaleStringExpressionSocket* aStringExpression = (DefaultMaleStringExpressionSocket*)nb->self();
//             AbstractStringExpression* ase = (AbstractStringExpression*)nb->self();
//             QObject* obj = (QObject*)ase->getParent();
//             //DefaultMaleStringExpressionSocket* aStringExpression = (DefaultMaleStringExpressionSocket*)ase->AbstractStringExpression::getParent()->bself();
//             DefaultMaleStringExpressionSocket* aStringExpression = (DefaultMaleStringExpressionSocket*)obj;
             stringExpressionManager->deleteStringExpression(aStringExpression);
            }

            QSet</*Module*/NamedBean*> moduleSet = QSet</*Module*/NamedBean*>(((DefaultModuleManager*)InstanceManager::getDefault("ModuleManager"))->getNamedBeanSet());
            for (NamedBean* nb : moduleSet) {
             Module* aModule = (DefaultModule*)nb->self();
                ((DefaultModuleManager*)InstanceManager::getDefault("ModuleManager"))->deleteModule(aModule);
            }

            QSet</*NamedTable*/NamedBean*> tableSet = QSet<NamedBean*>(((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"))->getNamedBeanSet());
            for (NamedBean* nb : tableSet) {
             NamedTable* aTable = (AbstractNamedTable*)nb->self();
                ((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"))->deleteNamedTable(aTable);
            }

            while (! logixNG_InitializationManager->getList().isEmpty()) {
                logixNG_InitializationManager->_delete(0);
            }

            Assert::assertEquals(0, logixNG_Manager->getNamedBeanSet().size(), __FILE__, __LINE__);
            Assert::assertEquals(0, analogActionManager->getNamedBeanSet().size(), __FILE__, __LINE__);
            Assert::assertEquals(0, (int)analogExpressionManager->getNamedBeanSet().size(), __FILE__, __LINE__);
            Assert::assertEquals(0, digitalActionManager->getNamedBeanSet().size(), __FILE__, __LINE__);
            Assert::assertEquals(0, digitalExpressionManager->getNamedBeanSet().size(), __FILE__, __LINE__);
            Assert::assertEquals(0, stringActionManager->getNamedBeanSet().size(), __FILE__, __LINE__);
            Assert::assertEquals(0, stringExpressionManager->getNamedBeanSet().size(), __FILE__, __LINE__);
            Assert::assertEquals(0, ((DefaultModuleManager*)InstanceManager::getDefault("ModuleManager"))->getNamedBeanSet().size(), __FILE__, __LINE__);
            Assert::assertEquals(0, ((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"))->getNamedBeanSet().size(), __FILE__, __LINE__);
            Assert::assertEquals(0, logixNG_InitializationManager->getList().size(), __FILE__, __LINE__);

            LogixNG_Thread::stopAllLogixNGThreads();
            LogixNG_Thread::assertLogixNGThreadNotRunning();

/*
            audioManager.cleanup();
            JUnitUtil::waitFor(()->{return !audioManager.isInitialised();});

            audioManager = new jmri.jmrit.audio.DefaultAudioManager(
                    InstanceManager::getDefault(jmri.jmrix.internal.InternalSystemConnectionMemo.class));
            audioManager.init();
            JUnitUtil::waitFor(()->{return audioManager.isInitialised();});
*/

            //**********************************
            // Try to load file
            //**********************************

            JUnitUtil::initConfigureManager();
            cm = (JmriConfigurationManager*)InstanceManager::getNullableDefault("ConfigureManager");
            if (cm == nullptr) {
                log->error("Unable to get default configure manager");
            } else {
             results = cm->load(secondFile);
            }
            log->debug(results ? "load was successful" : "store failed");
            if (results) {
                logixNG_Manager->setupAllLogixNGs();

                stringWriter = new StringWriter();
                printWriter = new PrintWriter(stringWriter);
                int mutableInt = 0;
                logixNG_Manager->printTree(QLocale(), printWriter, treeIndent, &mutableInt);

                if (originalTree !=(stringWriter->toString())) {
                    log->error("--------------------------------------------");
                    log->error("Old tree:");
                    log->error("XXX"+originalTree+"XXX");
                    log->error("--------------------------------------------");
                    log->error("New tree:");
                    log->error("XXX"+stringWriter->toString()+"XXX");
                    log->error("--------------------------------------------");
#if 1//TODO:
                    System::out("--------------------------------------------");
                    System::out("Old tree:");
                    System::out("XXX"+originalTree+"XXX");
                    System::out("--------------------------------------------");
                    System::out("New tree:");
                    System::out("XXX"+stringWriter->toString()+"XXX");
                    System::out("--------------------------------------------");
#endif
//                    log->error(conditionalNGManager.getBySystemName(originalTree)->getChild(0).getConnectedSocket().getSystemName());

                    Assert::fail("tree has changed", __FILE__, __LINE__);
//                    throw new RuntimeException("tree has changed");
                }
            } else {
                Assert::fail("Failed to load panel", __FILE__, __LINE__);
//                throw new RuntimeException("Failed to load panel", __FILE__, __LINE__);
            }
        }


        for (LoggingEvent* evt : JUnitAppender::getBacklog()) {
            System::out(QString("Log: %1, %2\n").arg(evt->getLevel()->toString(), evt->getMessage()));
        }


        JUnitAppender::assertErrorMessage("systemName is already registered: IH1", __FILE__, __LINE__);
        JUnitAppender::assertErrorMessage("systemName is already registered: IH2", __FILE__, __LINE__);

    }


    /*private*/ void StoreAndLoadTest::addHeader(File* inFile, File* outFile) /*throws FileNotFoundException, IOException */{
      #if 1
//     try (BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(inFile), StandardCharsets.UTF_8));
//                PrintWriter* writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outFile), StandardCharsets.UTF_8)))) {
       QFile* f1 = new QFile(inFile->getAbsolutePath());
       if(!f1->open(QIODevice::ReadOnly))
        throw new IOException();
       QTextStream* reader = new QTextStream(f1);

       QFile* f2 = new QFile(outFile->getAbsolutePath());
       if(!f2->open(QIODevice::WriteOnly | QIODevice::Truncate))
        throw new IOException();
       QTextStream* stream = new QTextStream(f2);
       PrintWriter* writer = new PrintWriter(stream);

            QString line = reader->readLine();
            writer->println(line);

            writer->println("<!--");
            writer->println("*****************************************************************************");
            writer->println();
            writer->println("DO NOT EDIT THIS FILE!!!");
            writer->println();
            writer->println("This file is created by jmri.jmrit.logixng.configurexml.StoreAndLoadTest");
            writer->println("and put in the temp/temp folder. LogixNG uses both the standard JMRI load");
            writer->println("and store test, and a LogixNG specific store and load test.");
            writer->println();
            writer->println("After adding new stuff to StoreAndLoadTest, copy the file temp/temp/LogixNG.xml");
            writer->println("to the folder java/test/jmri/jmrit/logixng/configurexml/load");
            writer->println();
            writer->println("******************************************************************************");
            writer->println("-->");

            while ((line = reader->readLine()) != "") {
                writer->println(line);
            }
            f2->flush();
            f2->close();
        }
#endif



    //@Before
    /*public*/  void StoreAndLoadTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initInternalLightManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initDebugPowerManager();

        JUnitUtil::initInternalSignalHeadManager();
        JUnitUtil::initDefaultSignalMastManager();
//        JUnitUtil::initSignalMastLogicManager();
        JUnitUtil::initOBlockManager();
        JUnitUtil::initWarrantManager();

//        JUnitUtil::initLogixNGManager();
    }

    //@After
    /*public*/  void StoreAndLoadTest::tearDown() {
//        JUnitAppender::clearBacklog();    // REMOVE THIS!!!
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::deregisterBlockManagerShutdownTask();
        JUnitUtil::tearDown();
    }



    /*private*/ /*static*/ /*final*/ QStringList StoreAndLoadTest::initValues = {
        "",             // None
        "32",           // Integer
        "41.429",       // FloatingNumber
        "My string",    // String
        "index",        //
        "IM2",          // Memory
        "{IM3}",        // Reference
        "index * 2",    // Formula
    };


    /*private*/ void StoreAndLoadTest::addVariables(MaleSocket* maleSocket) {
        int i = 0;
        for (InitialValueType::TYPES type : InitialValueType::values()) {
            maleSocket->addLocalVariable(QString("A%d").arg(i+1), type, initValues[i]);
            i++;
        }
    }
#if 0

    /*private*/ static /*final*/ PrimitiveIterator.OfInt iterator =
            new Random(215).ints('a', 'z'+10).iterator();

    /*private*/ String getRandomString(int count) {
        StringBuilder s = new StringBuilder();
        for (int i=0; i < count; i++) {
            int r = iterator.nextInt();
            if (i == 0 && r > 'z') r -= 10;     // The first char must be a character, not a digit.
            char c = (char) (r > 'z' ? r-'z'+'0' : r);
            s.append(c);
        }
        return s.toString();
    }

#endif
    /*private*/ /*final*/ /*static*/ Logger* StoreAndLoadTest::log = LoggerFactory::getLogger("StoreAndLoadTest");
