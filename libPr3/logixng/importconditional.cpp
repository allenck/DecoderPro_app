#include "importconditional.h"
#include "loggerfactory.h"
#include "conditional.h"
#include "conditionalng.h"
#include "defaultconditionalngmanager.h"
#include "instancemanager.h"
#include "runtimeexception.h"
#include "defaultdigitalactionmanager.h"
#include "logix_emulator.h"
#include "digitalexpressionbean.h"
#include "defaultdigitalexpressionmanager.h"
#include "and.h"
#include "or.h"
#include "antecedent.h"
#include "true.h"
#include "triggeronce.h"
#include "conditionalvariable.h"
#include "digitalbooleanmany.h"
#include "defaultdigitalbooleanactionmanager.h"
#include "atomicboolean.h"
#include "signalhead.h"
#include "signalmast.h"
#include "destinationpoints.h"
#include "warrant.h"
#include "oblock.h"
#include "not.h"
#include "digitalbooleanonchange.h"
#include "conditionalaction.h"
#include "expressionsensor.h"
#include "expressionturnout.h"
#include "expressionmemory.h"
#include "is_isnot_enum.h"
#include "invalidconditionalactionexception.h"
#include "actionturnout.h"
#include "actionsensor.h"
#include "actionmemory.h"
#include "invalidconditionalactionexception.h"
#include "defaultdigitalactionmanager.h"
#include "is_isnot_enum.h"
#include "invalidconditionalvariableexception.h"
#include "defaultmemorymanager.h"
#include "defaultdigitalactionmanager.h"
#include "defaultconditionalaction.h"
#include "executedelayed.h"
#include "timerunit.h"
#include "actionturnoutlock.h"

/**
 * Imports Logixs to LogixNG
 *
 * @author Daniel Bergqvist 2019
 */
// /*public*/  class ImportConditional {



    /**
     * Create instance of ImportConditional
     * @param logix         the parent Logix of the conditional to import
     * @param conditional   the Conditional to import
     * @param logixNG       the parent LogixNG that the new ConditionalNG will be added to
     * @param sysName       the system name of the new ConditionalNG
     * @param dryRun        true if import without creating any new beans,
     *                      false if to create new beans
     */
    /*public*/  ImportConditional::ImportConditional(
            Logix* logix,
            Conditional* conditional,
            LogixNG* logixNG,
            QString sysName,
            bool dryRun, QObject* parent) : QObject(parent){

        _dryRun = dryRun;
        _conditional = conditional;
        QString userName = conditional->getSystemName();
        if (conditional->getUserName() != nullptr) {
            userName += ": " + conditional->getUserName();
        }

        if (!_dryRun) {
            ConditionalNG* conditionalNG = nullptr;
            int counter = 0;
            while ((conditionalNG == nullptr) && counter < 100) {
                QString name = counter > 0 ? " - " + QString::number(counter) : "";
                conditionalNG = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))
                        ->createConditionalNG(logixNG, sysName, userName + name);
                counter++;
            }

            if (conditionalNG == nullptr) throw new RuntimeException("Cannot create new ConditionalNG with name: \"" + userName + "\"");

            _conditionalNG = conditionalNG;
        } else {
            _conditionalNG = nullptr;
        }
    }

    /*public*/  ConditionalNG* ImportConditional::getConditionalNG() {
        return _conditionalNG;
    }

    /*public*/  void ImportConditional::doImport() /*throws SocketAlreadyConnectedException, JmriException*/ {
/*
        // This is only to remember to test everything Logix and Conditional supports
        String systemName = "";
        jmri.Logix l = null;

        java.beans.PropertyChangeEvent evt = null;
        jmri.Conditional c = null;

        l.getConditional(systemName);
        l.getConditionalByNumberOrder(0);
        l.getEnabled();

        c.cancelSensorTimer(systemName);
        c.cancelTurnoutTimer(systemName);
        c.getAntecedentExpression();        // Tested
        c.getCopyOfActions();
        c.getCopyOfStateVariables();
        c.getLogicType();                   // Tested
        c.getTriggerOnChange();             // Tested
*/







//        boolean triggerOnChange = _conditional.getTriggerOnChange();
//        IfThenElse.Type type = triggerOnChange ? IfThenElse.Type.TRIGGER_ACTION : IfThenElse.Type.CONTINOUS_ACTION;

//        IfThenElse ifThen = new IfThenElse(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager")).getAutoSystemName(), null, type);
        Logix_Emulator* logix = new Logix_Emulator(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->AbstractManager::getAutoSystemName(), nullptr);

        logix->setExecuteOnChange(_conditional->getTriggerOnChange());

        Conditional::AntecedentOperator::VALS ao = Conditional::AntecedentOperator::fromInt(_conditional->getLogicType());
        QString antecedentExpression = _conditional->getAntecedentExpression();
        QList<ConditionalVariable*> *conditionalVariables = _conditional->getCopyOfStateVariables();
        QList<ConditionalAction*> *conditionalActions = _conditional->getCopyOfActions();
        DigitalExpressionBean* expression;
        switch (ao) {
            case Conditional::AntecedentOperator::ALL_AND:
                expression = new And(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->AbstractManager::getAutoSystemName(), "");
                break;
            case Conditional::AntecedentOperator::ALL_OR:
                expression = new Or(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->AbstractManager::getAutoSystemName(), "");
                break;
            case Conditional::AntecedentOperator::MIXED:
                expression = new Antecedent(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->AbstractManager::getAutoSystemName(), "");
                ((Antecedent*)expression)->setAntecedent(antecedentExpression);
                break;
            default:
                return;
        }
#if 1 // TODO:

        // Is the Conditional a RTXINITIALIZER?
        if ((conditionalVariables->size() == 1) && (Conditional::Type::getItemType(conditionalVariables->at(0)->getType()) == Conditional::ItemType::NONE)){
            expression =
                    new TriggerOnce(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                            ->AbstractManager::getAutoSystemName(), "");

            True* trueExpression =
                    new True(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                            ->AbstractManager::getAutoSystemName(), "");
            if (!_dryRun) {
                MaleSocket* socket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                        ->registerExpression(trueExpression);
                expression->getChild(0)->_connect(socket);
            }
        } else {
            buildExpression(expression, conditionalVariables);
        }

        DigitalBooleanMany* many =
                new DigitalBooleanMany(((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault(
                        "DigitalBooleanActionManager"))->AbstractManager::getAutoSystemName(), "");

        buildAction(many, conditionalActions);

        if (!_dryRun) {
            MaleSocket* expressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
            logix->getExpressionSocket()->_connect(expressionSocket);

            MaleSocket* manySocket = ((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))->registerAction(many);
            logix->getActionSocket()->_connect(manySocket);

            MaleSocket* logixAction = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(logix);
            _conditionalNG->getChild(0)->_connect(logixAction);
        }
#endif
    }

    /*private*/ void ImportConditional::buildExpression(DigitalExpressionBean* expression, QList<ConditionalVariable*>* conditionalVariables)
            /*throws SocketAlreadyConnectedException, JmriException*/ {

        for (int i=0; i < conditionalVariables->size(); i++) {
            ConditionalVariable* cv = conditionalVariables->at(i);
            NamedBean* nb = cv->getBean();
            AtomicBoolean* isNegated = new AtomicBoolean(cv->isNegated());
            DigitalExpressionBean* newExpression;
            switch (cv->getType()/*.getItemType()*/) {
                case Conditional::ItemType::SENSOR:
                {
                    Sensor* sn = (Sensor*)nb->self();
                    newExpression = getSensorExpression(cv, sn, isNegated);
                    break;
                }
                case Conditional::ItemType::TURNOUT:
                {
                    Turnout* tn = (Turnout*)nb->self();
                    newExpression = getTurnoutExpression(cv, tn, isNegated);
                    break;
                }
                case Conditional::ItemType::MEMORY:
                {
                    Memory* my = (Memory*)nb->self();
                    newExpression = getMemoryExpression(cv, my);
                    break;
                }
#if 0
                case LIGHT:
                    Light* l = (Light*)nb->self;
                    newExpression = getLightExpression(cv, l, isNegated);
                    break;
                case SIGNALHEAD:
                    SignalHead* s = (SignalHead*)nb-self;
                    newExpression = getSignalHeadExpression(cv, s, isNegated);
                    break;
                case SIGNALMAST:
                    SignalMast sm = (SignalMast*)nb->self();
                    newExpression = getSignalMastExpression(cv, sm, isNegated);
                    break;
                case ENTRYEXIT:
                    DestinationPoints* dp = (DestinationPoints*)nb->self());
                    newExpression = getEntryExitExpression(cv, dp, isNegated);
                    break;
                case CONDITIONAL:
                    Conditional* c = (Conditional*)nb->self());
                    newExpression = getConditionalExpression(cv, c, isNegated);
                    break;
                case CLOCK:
                    newExpression = getFastClockExpression(cv, isNegated);
                    break;
                case WARRANT:
                    Warrant* w = (Warrant*)nb->self());
                    newExpression = getWarrantExpression(cv, w, isNegated);
                    break;
                case OBLOCK:
                    OBlock* b = (OBlock*)nb->self());
                    newExpression = getOBlockExpression(cv, b, isNegated);
                    break;
#endif
                default:
                    newExpression = nullptr;
                    log->error(tr("Unexpected type in ImportConditional.doImport(): %1 -> %2").arg(Conditional::Type::toString(cv->getType()), Conditional::Type::toString(cv->getType())));
                    break;
            }

            if (newExpression != nullptr) {

                bool doTriggerActions = cv->doTriggerActions();

                if (isNegated->get()) {  // Some expressions have already handled Not
                    Not* notExpression = new Not(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                            ->AbstractManager::getAutoSystemName(), "");

                    if (!_dryRun) {
                        MaleSocket* newExpressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(newExpression);
                        newExpressionSocket->setListen(doTriggerActions);
                        doTriggerActions = true;    // We don't want the Not expression to disable listen.
                        notExpression->getChild(0)->_connect(newExpressionSocket);
                    }
                    newExpression = notExpression;
                }

                if (!_dryRun) {
                    MaleSocket* newExpressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(newExpression);
                    newExpressionSocket->setListen(doTriggerActions);
                    expression->getChild(i)->_connect(newExpressionSocket);
                }
            } else {
             // log.error("ImportConditional.doImport() did not created an expression for type: {} -> {}", cv.getType().name(), cv.getType().getItemType().name());

                log->error(tr("ImportConditional.doImport() did not created an expression for type: %1 -> %2").arg(Conditional::Type::toString(cv->getType()), Conditional::Type::getItemTypeName(cv->getType())));
            }
        }
    }


    /*private*/ void ImportConditional::buildAction(DigitalBooleanMany* many, QList<ConditionalAction*>* conditionalActions)
            /*throws SocketAlreadyConnectedException, JmriException*/ {

        for (int i=0; i < conditionalActions->size(); i++) {
            ConditionalAction* ca = conditionalActions->at(i);

            DigitalBooleanOnChange::Trigger::TargetAction trigger;
            switch (ca->getOption()) {
                case Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE:
                    trigger = DigitalBooleanOnChange::Trigger::CHANGE_TO_TRUE;
                    break;

                case Conditional::ACTION_OPTION_ON_CHANGE_TO_FALSE:
                    trigger = DigitalBooleanOnChange::Trigger::CHANGE_TO_FALSE;
                    break;

                case Conditional::ACTION_OPTION_ON_CHANGE:
                    trigger = DigitalBooleanOnChange::Trigger::CHANGE;
                    break;

                default:
                    throw new InvalidConditionalActionException(
                            tr("The conditional action has unknown trigger: %1").arg(ca->getOption()));
            }

            DigitalBooleanActionBean* booleanAction =
                    new DigitalBooleanOnChange(((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))->AbstractManager::getAutoSystemName(), "", trigger);

            buildAction(booleanAction, ca);

            if (!_dryRun) {
                MaleSocket* newBooleanActionSocket = ((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))->registerAction(booleanAction);
                many->getChild(i)->_connect(newBooleanActionSocket);
            }
        }
    }

    /*private*/ void ImportConditional::buildAction(DigitalBooleanActionBean* action, ConditionalAction* conditionalAction)
            /*throws SocketAlreadyConnectedException, JmriException*/ {


        QString reference = "";
        QString devName = conditionalAction->getDeviceName();
        if (devName != "" && devName.length() > 0 && devName.at(0) == '@') {
            reference = "{"+devName.mid(1)+"}";
        }

        NamedBean* nb = conditionalAction->getBean();
//        System.err.format("nb: %s%n", nb == null ? null : nb.getSystemName());
        DigitalActionBean* newAction;
        switch (conditionalAction->getType()/*->getItemType()*/) {
            case Conditional::ItemType::SENSOR:
        {
                Sensor* sn = (Sensor*)nb->self();
                newAction = getSensorAction(conditionalAction, sn, reference);
                break;
        }
            case Conditional::ItemType::TURNOUT:
        {
                Turnout* tn = (Turnout*)nb->self();
                newAction = getTurnoutAction(conditionalAction, tn, reference);
                break;
        }
            case Conditional::ItemType::MEMORY:
        {
                Memory* my = (Memory*)nb->self();
                newAction = getMemoryAction(conditionalAction, my, reference);
                break;
        }
#if 0
            case LIGHT:
                Light* l = (Light*)nb->self());
                newAction = getLightAction(conditionalAction, l, reference);
                break;
            case SIGNALHEAD:
                SignalHead* s = (SignalHead*)nb->self());
                newAction = getSignalHeadAction(conditionalAction, s, reference);
                break;
            case SIGNALMAST:
                SignalMast* sm = (SignalMast*)nb->self());
                newAction = getSignalMastAction(conditionalAction, sm, reference);
                break;
            case ENTRYEXIT:
                DestinationPoints dp = (DestinationPoints*)nb->self());
                newAction = getEntryExitAction(conditionalAction, dp, reference);
                break;
            case WARRANT:
                Warrant* w = (Warrant*)nb->self());
                newAction = getWarrantAction(conditionalAction, w, reference);
                break;
            case OBLOCK:
                OBlock* b = (OBlock*)nb->self());
                newAction = getOBlockAction(conditionalAction, b, reference);
                break;

            case LOGIX:
                newAction = getEnableLogixAction(conditionalAction);
                break;

            case CLOCK:
                newAction = getClockAction(conditionalAction);
                break;

            case AUDIO:
                newAction = getAudioOrSoundAction(conditionalAction);
                break;

            case SCRIPT:
                newAction = getScriptAction(conditionalAction);
                break;

            case OTHER:
                Route* r = (Route*) nb->self();
                newAction = getRouteAction(conditionalAction, r, reference);
                break;
#endif
            default:
                newAction = nullptr;
                log->warn(tr("Unexpected type in ImportConditional.doImport(): %1 -> %2").arg(Conditional::Action::toString(conditionalAction->getType()), Conditional::Action::getItemTypeName( conditionalAction->getType())));
                break;
        }

        if (newAction != nullptr) {
            if (!_dryRun) {
                MaleSocket* newActionSocket = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(newAction);
                action->getChild(0)->_connect(newActionSocket);
            }
        } else {
            log->error(tr("ImportConditional.doImport() did not created an action for type: %1 -> %2").arg(Conditional::Action::toString(conditionalAction->getType()),Conditional::Action::getItemTypeName( conditionalAction->getType())));
        }
    }


    /*private*/ DigitalExpressionBean* ImportConditional::getSensorExpression(
            /*@Nonnull*/ ConditionalVariable* cv,
            Sensor* sn,
            AtomicBoolean* isNegated)
            /*throws JmriException*/ {

        ExpressionSensor* expression =
                new ExpressionSensor(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                        ->AbstractManager::getAutoSystemName(), "");

//        System.err.format("Sensor: %s%n", sn == null ? null : sn.getSystemName());

        expression->setSensor(sn);

        if (isNegated->get()) {
            expression->set_Is_IsNot(Is_IsNot_Enum::IsNot);
            isNegated->set(false);
        }

        switch (cv->getType()) {
            case Conditional::Type::SENSOR_ACTIVE:
                expression->setBeanState(ExpressionSensor::SensorState::Active);
                break;
            case Conditional::Type::SENSOR_INACTIVE:
                expression->setBeanState(ExpressionSensor::SensorState::Inactive);
                break;
            default:
                throw new InvalidConditionalVariableException(
                        tr("The conditional variable for a sensor has unknown type %1").arg(Conditional::Type::toString(cv->getType())));
        }

        return expression;
    }


    /*private*/ DigitalExpressionBean* ImportConditional::getTurnoutExpression(
            /*@Nonnull*/ ConditionalVariable* cv,
            Turnout* tn,
            AtomicBoolean* isNegated)
            /*throws JmriException*/ {

        ExpressionTurnout* expression =
                new ExpressionTurnout(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                        ->AbstractManager::getAutoSystemName(), "");

        expression->setTurnout(tn);

        if (isNegated->get()) {
            expression->set_Is_IsNot(Is_IsNot_Enum::IsNot);
            isNegated->set(false);
        }

        switch (cv->getType()) {
            case Conditional::Type::TURNOUT_CLOSED:
                expression->setBeanState(ExpressionTurnout::TurnoutState::Closed);
                break;
            case Conditional::Type::TURNOUT_THROWN:
                expression->setBeanState(ExpressionTurnout::TurnoutState::Thrown);
                break;
            default:
                throw new InvalidConditionalVariableException(
                        tr("The conditional variable for a turnout has unknown type %1").arg(Conditional::Type::toString(cv->getType())));
        }

        return expression;
    }


    /*private*/ DigitalExpressionBean* ImportConditional::getMemoryExpression(
            /*@Nonnull*/ ConditionalVariable* cv, Memory* my)
            /*throws JmriException*/ {

        ExpressionMemory* expression =
                new ExpressionMemory(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                        ->AbstractManager::getAutoSystemName(), "");

        expression->setMemory(my);

        switch (cv->getNum1()) {
            case ConditionalVariable::EQUAL:
                expression->setMemoryOperation(ExpressionMemory::MemoryOperation::Equal);
                break;
            case ConditionalVariable::LESS_THAN:
                expression->setMemoryOperation(ExpressionMemory::MemoryOperation::LessThan);
                break;
            case ConditionalVariable::LESS_THAN_OR_EQUAL:
                expression->setMemoryOperation(ExpressionMemory::MemoryOperation::LessThanOrEqual);
                break;
            case ConditionalVariable::GREATER_THAN:
                expression->setMemoryOperation(ExpressionMemory::MemoryOperation::GreaterThan);
                break;
            case ConditionalVariable::GREATER_THAN_OR_EQUAL:
                expression->setMemoryOperation(ExpressionMemory::MemoryOperation::GreaterThanOrEqual);
                break;
            default:
                throw new InvalidConditionalVariableException(
                        tr("The conditional variable for memory has unknown num1 %1").arg(Conditional::Type::toString( cv->getType())));
        }

        Memory* memory;
        switch (cv->getType()) {
            case Conditional::Type::MEMORY_EQUALS:
                expression->setCompareTo(ExpressionMemory::CompareTo::Value);
                expression->setCaseInsensitive(false);
                expression->setConstantValue(cv->getDataString());
                break;
            case Conditional::Type::MEMORY_EQUALS_INSENSITIVE:
                expression->setCompareTo(ExpressionMemory::CompareTo::Value);
                expression->setCaseInsensitive(true);
                expression->setConstantValue(cv->getDataString());
                break;
            case Conditional::Type::MEMORY_COMPARE:
                expression->setCompareTo(ExpressionMemory::CompareTo::Memory);
                expression->setCaseInsensitive(false);
                expression->setOtherMemory(cv->getDataString());
                memory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(cv->getDataString());
                if (memory == nullptr) {   // Logix allows the memory name in cv->getDataString() to be a system name without system prefix
                    memory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide(cv->getDataString());
                    expression->setOtherMemory(memory->getSystemName());
                }
                break;
            case Conditional::Type::MEMORY_COMPARE_INSENSITIVE:
                expression->setCompareTo(ExpressionMemory::CompareTo::Memory);
                expression->setCaseInsensitive(true);
                expression->setOtherMemory(cv->getDataString());
                memory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(cv->getDataString());
                if (memory == nullptr) {   // Logix allows the memory name in cv->getDataString() to be a system name without system prefix
                    memory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide(cv->getDataString());
                    expression->setOtherMemory(memory->getSystemName());
                }
                break;
            default:
                throw new InvalidConditionalVariableException(
                        tr("The conditional variable for memory has unknown type %1").arg(Conditional::Type::toString(cv->getType())));
        }

        expression->setListenToOtherMemory(false);

        return expression;
    }
#if 0 //TODO:

    /*private*/ DigitalExpressionBean getLightExpression(
            @Nonnull ConditionalVariable cv,
            Light ln,
            AtomicBoolean isNegated)
            throws JmriException {

        ExpressionLight expression =
                new ExpressionLight(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                        .getAutoSystemName(), null);

        expression->setLight(ln);

        if (isNegated->get()) {
            expression->set_Is_IsNot(Is_IsNot_Enum.IsNot);
            isNegated->set(false);
        }

        switch (cv->getType()) {
            case LIGHT_ON:
                expression->setBeanState(ExpressionLight.LightState.On);
                break;
            case LIGHT_OFF:
                expression->setBeanState(ExpressionLight.LightState.Off);
                break;
            default:
                throw new InvalidConditionalVariableException(
                        Bundle.getMessage("ConditionalBadLightType", cv->getType().toString()));
        }

        return expression;
    }


    /*private*/ DigitalExpressionBean getSignalHeadExpression(
            @Nonnull ConditionalVariable cv,
            SignalHead s,
            AtomicBoolean isNegated)
            throws JmriException {

        ExpressionSignalHead expression =
                new ExpressionSignalHead(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                        .getAutoSystemName(), null);

        expression->setSignalHead(s);

        ExpressionSignalHead.QueryType appearence =
                isNegated->get() ? ExpressionSignalHead.QueryType.NotAppearance
                : ExpressionSignalHead.QueryType.Appearance;

        switch (cv->getType()) {
            case SIGNAL_HEAD_RED:
                expression->setQueryType(appearence);
                expression->setAppearance(SignalHead.RED);
                break;
            case SIGNAL_HEAD_YELLOW:
                expression->setQueryType(appearence);
                expression->setAppearance(SignalHead.YELLOW);
                break;
            case SIGNAL_HEAD_GREEN:
                expression->setQueryType(appearence);
                expression->setAppearance(SignalHead.GREEN);
                break;
            case SIGNAL_HEAD_DARK:
                expression->setQueryType(appearence);
                expression->setAppearance(SignalHead.DARK);
                break;
            case SIGNAL_HEAD_FLASHRED:
                expression->setQueryType(appearence);
                expression->setAppearance(SignalHead.FLASHRED);
                break;
            case SIGNAL_HEAD_FLASHYELLOW:
                expression->setQueryType(appearence);
                expression->setAppearance(SignalHead.FLASHYELLOW);
                break;
            case SIGNAL_HEAD_FLASHGREEN:
                expression->setQueryType(appearence);
                expression->setAppearance(SignalHead.FLASHGREEN);
                break;
            case SIGNAL_HEAD_LUNAR:
                expression->setQueryType(appearence);
                expression->setAppearance(SignalHead.LUNAR);
                break;
            case SIGNAL_HEAD_FLASHLUNAR:
                expression->setQueryType(appearence);
                expression->setAppearance(SignalHead.FLASHLUNAR);
                break;
            case SIGNAL_HEAD_LIT:
                expression->setQueryType(isNegated->get() ? ExpressionSignalHead.QueryType.NotLit : ExpressionSignalHead.QueryType.Lit);
                break;
            case SIGNAL_HEAD_HELD:
                expression->setQueryType(isNegated->get() ? ExpressionSignalHead.QueryType.NotHeld : ExpressionSignalHead.QueryType.Held);
                break;
            default:
                throw new InvalidConditionalVariableException(
                        Bundle.getMessage("ConditionalBadSignalHeadType", cv->getType().toString()));
        }

        isNegated->set(false);   // We have already handled this

        return expression;
    }


    /*private*/ DigitalExpressionBean getSignalMastExpression(
            @Nonnull ConditionalVariable cv,
            SignalMast sm,
            AtomicBoolean isNegated)
            throws JmriException {

        ExpressionSignalMast expression =
                new ExpressionSignalMast(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                        .getAutoSystemName(), null);

        expression->setSignalMast(sm);

        ExpressionSignalMast.QueryType aspect =
                isNegated->get() ? ExpressionSignalMast.QueryType.NotAspect
                : ExpressionSignalMast.QueryType.Aspect;

        switch (cv->getType()) {
            case SIGNAL_MAST_ASPECT_EQUALS:
                expression->setQueryType(aspect);
                expression->setAspect(cv->getDataString());
                break;
            case SIGNAL_MAST_LIT:
                expression->setQueryType(isNegated->get() ? ExpressionSignalMast.QueryType.NotLit : ExpressionSignalMast.QueryType.Lit);
                break;
            case SIGNAL_MAST_HELD:
                expression->setQueryType(isNegated->get() ? ExpressionSignalMast.QueryType.NotHeld : ExpressionSignalMast.QueryType.Held);
                break;
            default:
                throw new InvalidConditionalVariableException(
                        Bundle.getMessage("ConditionalBadSignalMastType", cv->getType().toString()));
        }

        isNegated->set(false);   // We have already handled this

        return expression;
    }


    /*private*/ DigitalExpressionBean getEntryExitExpression(
            @Nonnull ConditionalVariable cv,
            DestinationPoints dp,
            AtomicBoolean isNegated)
            throws JmriException {

        ExpressionEntryExit expression =
                new ExpressionEntryExit(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                        .getAutoSystemName(), null);

        expression->setDestinationPoints(dp);

        if (isNegated->get()) {
            expression->set_Is_IsNot(Is_IsNot_Enum.IsNot);
            isNegated->set(false);
        }

        switch (cv->getType()) {
            case ENTRYEXIT_ACTIVE:
                expression->setBeanState(ExpressionEntryExit.EntryExitState.Active);
                break;
            case ENTRYEXIT_INACTIVE:
                expression->setBeanState(ExpressionEntryExit.EntryExitState.Inactive);
                break;
            default:
                throw new InvalidConditionalVariableException(
                        Bundle.getMessage("ConditionalBadEntryExitType", cv->getType().toString()));
        }

        return expression;
    }


    /*private*/ DigitalExpressionBean getConditionalExpression(
            @Nonnull ConditionalVariable cv,
            Conditional cn,
            AtomicBoolean isNegated)
            throws JmriException {

        ExpressionConditional expression =
                new ExpressionConditional(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                        .getAutoSystemName(), null);

        expression->setConditional(cn);

        if (isNegated->get()) {
            expression->set_Is_IsNot(Is_IsNot_Enum.IsNot);
            isNegated->set(false);
        }

        switch (cv->getType()) {
            case CONDITIONAL_TRUE:
                expression->setConditionalState(ExpressionConditional.ConditionalState.True);
                break;
            case CONDITIONAL_FALSE:
                expression->setConditionalState(ExpressionConditional.ConditionalState.False);
                break;
            default:
                throw new InvalidConditionalVariableException(
                        Bundle.getMessage("ConditionalBadConditionalType", cv->getType().toString()));
        }

        return expression;
    }


    /*private*/ DigitalExpressionBean getFastClockExpression(
            @Nonnull ConditionalVariable cv,
            AtomicBoolean isNegated)
            throws JmriException {

        ExpressionClock expression =
                new ExpressionClock(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                        .getAutoSystemName(), null);

        if (isNegated->get()) {
            expression->set_Is_IsNot(Is_IsNot_Enum.IsNot);
            isNegated->set(false);
        }

        if (cv->getType() != Conditional.Type.FAST_CLOCK_RANGE) {
            throw new InvalidConditionalVariableException(
                    Bundle.getMessage("ConditionalBadFastClockType", cv->getType().toString()));
        }
                log.info("Found a clock range");

        expression->setType(ExpressionClock.Type.FastClock);
        expression->setRange(ConditionalVariable.fixMidnight(cv->getNum1()), ConditionalVariable.fixMidnight(cv->getNum2()));

        return expression;
    }


    /*private*/ DigitalExpressionBean getWarrantExpression(
            @Nonnull ConditionalVariable cv,
            Warrant w,
            AtomicBoolean isNegated)
            throws JmriException {

        ExpressionWarrant expression =
                new ExpressionWarrant(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                        .getAutoSystemName(), null);

        expression->setWarrant(w);

        if (isNegated->get()) {
            expression->set_Is_IsNot(Is_IsNot_Enum.IsNot);
            isNegated->set(false);
        }

        switch (cv->getType()) {
            case ROUTE_FREE:
                expression->setBeanState(ExpressionWarrant.WarrantState.RouteFree);
                break;
            case ROUTE_OCCUPIED:
                expression->setBeanState(ExpressionWarrant.WarrantState.RouteOccupied);
                break;
            case ROUTE_ALLOCATED:
                expression->setBeanState(ExpressionWarrant.WarrantState.RouteAllocated);
                break;
            case ROUTE_SET:
                expression->setBeanState(ExpressionWarrant.WarrantState.RouteSet);
                break;
            case TRAIN_RUNNING:
                expression->setBeanState(ExpressionWarrant.WarrantState.TrainRunning);
                break;
            default:
                throw new InvalidConditionalVariableException(
                        Bundle.getMessage("ConditionalBadWarrantType", cv->getType().toString()));
        }

        return expression;
    }


    /*private*/ DigitalExpressionBean getOBlockExpression(
            @Nonnull ConditionalVariable cv,
            OBlock b,
            AtomicBoolean isNegated)
            throws JmriException {

        ExpressionOBlock expression =
                new ExpressionOBlock(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                        .getAutoSystemName(), null);

        if (isNegated->get()) {
            expression->set_Is_IsNot(Is_IsNot_Enum.IsNot);
            isNegated->set(false);
        }

        OBlock.OBlockStatus oblockStatus = OBlock.OBlockStatus.getByName(cv->getDataString());

        if (oblockStatus == null) {
            throw new InvalidConditionalVariableException(
                    Bundle.getMessage("ConditionalBadOBlockDataString", cv->getDataString()));
        }

        expression->setOBlock(b);
        expression->setBeanState(oblockStatus);

        return expression;
    }
#endif

    /*private*/ DigitalActionBean* ImportConditional::getSensorAction(/*@Nonnull*/ ConditionalAction* ca, Sensor* sn, QString reference)/* throws JmriException*/ {

        switch (ca->getType()) {
            case Conditional::Action::SET_SENSOR:
            {
                ActionSensor* action =
                        new ActionSensor(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                                ->AbstractManager::getAutoSystemName(), "");

                if (reference != nullptr) {
                    action->setAddressing(NamedBeanAddressing::Reference);
                    action->setReference(reference);
                } else {
                    action->setAddressing(NamedBeanAddressing::Direct);
                    action->setSensor(sn);
                }

                switch (ca->getActionData()) {
                    case Route::TOGGLE:
                        action->setBeanState(ActionSensor::SensorState::Toggle);
                        break;

                    case Sensor::INACTIVE:
                        action->setBeanState(ActionSensor::SensorState::Inactive);
                        break;

                    case Sensor::ACTIVE:
                        action->setBeanState(ActionSensor::SensorState::Active);
                        break;

                    default:
                        throw new InvalidConditionalVariableException(
                                tr("The conditional action for a sensor has unknown state %1").arg(ca->getActionData()));
                }
                return action;
            }
            case Conditional::Action::RESET_DELAYED_SENSOR:
            case Conditional::Action::DELAYED_SENSOR:
            {
                ConditionalAction* caTemp = new DefaultConditionalAction();
                caTemp->setType(Conditional::Action::SET_SENSOR);
                caTemp->setActionData(ca->getActionData());
                DigitalActionBean* subAction = getSensorAction(caTemp, sn, reference);
                ExecuteDelayed* delayedAction =
                        new ExecuteDelayed(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                                ->AbstractManager::getAutoSystemName(), "");

                QString sNumber = ca->getActionString();
                try {
                    bool ok;
                    int time = sNumber.toInt(&ok); if(!ok) throw new NumberFormatException();
                    delayedAction->setDelay(time);
                    delayedAction->setUnit(TimerUnit::Seconds);
                } catch (NumberFormatException* e) {
                    try {
                        bool ok;
                        float time = sNumber.toFloat(&ok); if(!ok) throw new NumberFormatException();
                        delayedAction->setDelay((int) (time * 1000));
                        delayedAction->setUnit(TimerUnit::MilliSeconds);
                    } catch (NumberFormatException* e2) {
                        // If here, assume that sNumber has the name of a memory.
                        // Logix supports this memory to have a floating point value
                        // but LogixNG requires this memory to have an integer value.
                        if (sNumber.at(0) == '@') {
                            sNumber = sNumber.mid(1);
                        }
                        delayedAction->setDelayAddressing(NamedBeanAddressing::Reference);
                        delayedAction->setDelayReference("{" + sNumber + "}");
                        delayedAction->setUnit(TimerUnit::Seconds);
                    }
                }

                delayedAction->setResetIfAlreadyStarted(ca->getType() == Conditional::Action::RESET_DELAYED_SENSOR);
                if (!_dryRun) {
                    MaleSocket* subActionSocket = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                            ->registerAction(subAction);
                    delayedAction->getChild(0)->_connect(subActionSocket);
                }
                return delayedAction;
            }
            case Conditional::Action::CANCEL_SENSOR_TIMERS:
            default:
                throw new InvalidConditionalVariableException(
                        tr("The conditional action for a sensor has unknown type %1").arg(Conditional::Action::toString(ca->getType())));
        }
    }


    /*private*/ DigitalActionBean* ImportConditional::getTurnoutAction(/*@Nonnull*/ ConditionalAction* ca, Turnout* tn, QString reference) /*throws JmriException*/ {
//        System.err.format("Turnout: %s%n", tn == null ? null : tn.getSystemName());

        ActionTurnout* action;

//        cv->getDataString();     // SignalMast, Memory, OBlock
//        cv->getNamedBeanData();  // Only for memory
//        cv->getNum1();   // Clock, Memory
//        cv->getNum2();   // Clock, Memory

        switch (ca->getType()) {
            case Conditional::Action::SET_TURNOUT:
                action = new ActionTurnout(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                                ->AbstractManager::getAutoSystemName(), "");

                if (reference != nullptr) {
                    action->setAddressing(NamedBeanAddressing::Reference);
                    action->setReference(reference);
                } else {
                    action->setAddressing(NamedBeanAddressing::Direct);
                    action->setTurnout(tn);
                }

                switch (ca->getActionData()) {
                    case Route::TOGGLE:
                        action->setBeanState(ActionTurnout::TurnoutState::Toggle);
                        break;

                    case Turnout::CLOSED:
                        action->setBeanState(ActionTurnout::TurnoutState::Closed);
                        break;

                    case Turnout::THROWN:
                        action->setBeanState(ActionTurnout::TurnoutState::Thrown);
                        break;

                    default:
                        throw new InvalidConditionalVariableException(
                                tr("ActionBadThe conditional action for a turnout has unknown state {%1TurnoutState").arg(ca->getActionData()));
                }
                break;

            case Conditional::Action::RESET_DELAYED_TURNOUT:
            case Conditional::Action::DELAYED_TURNOUT:
            {
                ConditionalAction* caTemp = new DefaultConditionalAction();
                caTemp->setType(Conditional::Action::SET_TURNOUT);
                caTemp->setActionData(ca->getActionData());
                DigitalActionBean* subAction = getTurnoutAction(caTemp, tn, reference);
                ExecuteDelayed* delayedAction =
                        new ExecuteDelayed(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                                ->AbstractManager::getAutoSystemName(), "");

                QString sNumber = ca->getActionString();
                try {
                 bool ok;
                    int time = sNumber.toInt(&ok); if(!ok) throw new NumberFormatException();
                    delayedAction->setDelay(time);
                    delayedAction->setUnit(TimerUnit::Seconds);
                } catch (NumberFormatException* e) {
                    try {
                  bool ok;
                        float time = sNumber.toFloat(&ok); if(!ok) throw new NumberFormatException();
                        delayedAction->setDelay((int) (time * 1000));
                        delayedAction->setUnit(TimerUnit::MilliSeconds);
                    } catch (NumberFormatException* e2) {
                        // If here, assume that sNumber has the name of a memory.
                        // Logix supports this memory to have a floating point value
                        // but LogixNG requires this memory to have an integer value.
                        if (sNumber.at(0) == '@') {
                            sNumber = sNumber.mid(1);
                        }
                        delayedAction->setDelayAddressing(NamedBeanAddressing::Reference);
                        delayedAction->setDelayReference("{" + sNumber + "}");
                        delayedAction->setUnit(TimerUnit::Seconds);
                    }
                }

                delayedAction->setResetIfAlreadyStarted(ca->getType() == Conditional::Action::RESET_DELAYED_TURNOUT);
                if (!_dryRun) {
                    MaleSocket* subActionSocket = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                            ->registerAction(subAction);
                    delayedAction->getChild(0)->_connect(subActionSocket);
                }
                return delayedAction;
            }
            case Conditional::Action::LOCK_TURNOUT:
            {
                ActionTurnoutLock* action2 = new ActionTurnoutLock(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                                ->AbstractManager::getAutoSystemName(), "");

                if (reference != nullptr) {
                    action2->setAddressing(NamedBeanAddressing::Reference);
                    action2->setReference(reference);
                } else {
                    action2->setAddressing(NamedBeanAddressing::Direct);
                    action2->setTurnout(tn);
                }

                switch (ca->getActionData()) {
                    case Route::TOGGLE:
                        action2->setTurnoutLock(ActionTurnoutLock::TurnoutLock::Toggle);
                        break;

                    case Turnout::LOCKED:
                        action2->setTurnoutLock(ActionTurnoutLock::TurnoutLock::Lock);
                        break;

                    case Turnout::UNLOCKED:
                        action2->setTurnoutLock(ActionTurnoutLock::TurnoutLock::Unlock);
                        break;

                    default:
                        throw new InvalidConditionalVariableException(
                                tr("The conditional action for a turnout has unknown lock type %1").arg(ca->getActionData()));
                }
                return action2;
            }
            case Conditional::Action::CANCEL_TURNOUT_TIMERS:
            default:
                throw new InvalidConditionalVariableException(
                        tr("The conditional action for a turnout has unknown type %1").arg(Conditional::Action::toString(ca->getType())));
        }

        return action;
    }


    /*private*/ DigitalActionBean* ImportConditional::getMemoryAction(/*@Nonnull*/ ConditionalAction* ca, Memory* my, QString reference) /*throws JmriException */{

        ActionMemory* action;

        action = new ActionMemory(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                        ->AbstractManager::getAutoSystemName(), "");

        if (reference != nullptr) {
            action->setAddressing(NamedBeanAddressing::Reference);
            action->setReference(reference);
        } else {
            action->setAddressing(NamedBeanAddressing::Direct);
            action->setMemory(my);
        }

        switch (ca->getType()) {
            case Conditional::Action::SET_MEMORY:
                action->setMemoryOperation(ActionMemory::MemoryOperation::SetToString);
                action->setOtherConstantValue(ca->getActionString());
                break;

            case Conditional::Action::COPY_MEMORY:
                action->setMemoryOperation(ActionMemory::MemoryOperation::CopyMemoryToMemory);
                action->setOtherMemory(ca->getActionString());
                break;

            default:
                throw new InvalidConditionalVariableException(
                        tr("ActionBadMemoryType %1").arg(ca->getActionData()));
        }

        return action;
    }
#if 0

    /*private*/ DigitalActionBean getLightAction(@Nonnull ConditionalAction ca, Light l, String reference) throws JmriException {

        ActionLight action = new ActionLight(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                .getAutoSystemName(), null);

        if (reference != null) {
            action->setAddressing(NamedBeanAddressing.Reference);
            action->setReference(reference);
        } else {
            action->setAddressing(NamedBeanAddressing.Direct);
            action->setLight(l);
        }

        switch (ca->getType()) {
            case SET_LIGHT:
                switch (ca->getActionData()) {
                    case jmri.Route.TOGGLE:
                        action->setBeanState(ActionLight.LightState.Toggle);
                        break;

                    case Light.OFF:
                        action->setBeanState(ActionLight.LightState.Off);
                        break;

                    case Light.ON:
                        action->setBeanState(ActionLight.LightState.On);
                        break;

                    default:
                        throw new InvalidConditionalVariableException(
                                Bundle.getMessage("ActionBadLightState", ca->getActionData()));
                }
                break;

            case SET_LIGHT_INTENSITY:
                int intensity = 0;
                try {
                    intensity = Integer.parseInt(ca->getActionString());
                    if (intensity < 0 || intensity > 100) {
                        intensity = 0;
                    }
                } catch (NumberFormatException ex) {
                    intensity = 0;
                }
                action->setLightValue(intensity);
                action->setBeanState(ActionLight.LightState.Intensity);
                break;

            case SET_LIGHT_TRANSITION_TIME:
                int interval = 0;
                try {
                    interval = Integer.parseInt(ca->getActionString());
                    if (interval < 0) {
                        interval = 0;
                    }
                } catch (NumberFormatException ex) {
                    interval = 0;
                }
                action->setLightValue(interval);
                action->setBeanState(ActionLight.LightState.Interval);
                break;

            default:
                throw new InvalidConditionalVariableException(
                        Bundle.getMessage("ActionBadLightType", ca->getType().toString()));
        }

        return action;
    }


    /*private*/ DigitalActionBean getSignalHeadAction(@Nonnull ConditionalAction ca, SignalHead sh, String reference) throws JmriException {
        ActionSignalHead action =
                new ActionSignalHead(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                        .getAutoSystemName(), null);

        if (reference != null) {
            action->setAddressing(NamedBeanAddressing.Reference);
            action->setReference(reference);
        } else {
            action->setAddressing(NamedBeanAddressing.Direct);
            action->setSignalHead(sh);
        }
        action->setOperationAddressing(NamedBeanAddressing.Direct);
        action->setAppearanceAddressing(NamedBeanAddressing.Direct);

        action->setSignalHead(sh);

        switch (ca->getType()) {
            case SET_SIGNAL_APPEARANCE:
                action->setOperationType(ActionSignalHead.OperationType.Appearance);
                action->setAppearance(ca->getActionData());
                break;

            case SET_SIGNAL_HELD:
                action->setOperationType(ActionSignalHead.OperationType.Held);
                break;

            case CLEAR_SIGNAL_HELD:
                action->setOperationType(ActionSignalHead.OperationType.NotHeld);
                break;

            case SET_SIGNAL_LIT:
                action->setOperationType(ActionSignalHead.OperationType.Lit);
                break;

            case SET_SIGNAL_DARK:
                action->setOperationType(ActionSignalHead.OperationType.NotLit);
                break;

            default:
                throw new InvalidConditionalVariableException(
                        Bundle.getMessage("ActionBadSignalHeadType", ca->getType().toString()));
        }

        return action;
    }


    /*private*/ DigitalActionBean getSignalMastAction(@Nonnull ConditionalAction ca, SignalMast sm, String reference) throws JmriException {
        ActionSignalMast action =
                new ActionSignalMast(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                        .getAutoSystemName(), null);

        if (reference != null) {
            action->setAddressing(NamedBeanAddressing.Reference);
            action->setReference(reference);
        } else {
            action->setAddressing(NamedBeanAddressing.Direct);
            action->setSignalMast(sm);
        }
        action->setOperationAddressing(NamedBeanAddressing.Direct);
        action->setAspectAddressing(NamedBeanAddressing.Direct);

        switch (ca->getType()) {
            case SET_SIGNALMAST_ASPECT:
                action->setOperationType(ActionSignalMast.OperationType.Aspect);
                String aspect = ca->getActionString();
                if (aspect != null && aspect.length() > 0 && aspect.charAt(0) == '@') {
                    String memName = aspect.substring(1);
                    action->setAspectAddressing(NamedBeanAddressing.Reference);
                    action->setAspectReference("{" + memName + "}");
                } else {
                    action->setAspect(aspect);
                }
                break;

            case SET_SIGNALMAST_HELD:
                action->setOperationType(ActionSignalMast.OperationType.Held);
                break;

            case CLEAR_SIGNALMAST_HELD:
                action->setOperationType(ActionSignalMast.OperationType.NotHeld);
                break;

            case SET_SIGNALMAST_LIT:
                action->setOperationType(ActionSignalMast.OperationType.Lit);
                break;

            case SET_SIGNALMAST_DARK:
                action->setOperationType(ActionSignalMast.OperationType.NotLit);
                break;

            default:
                throw new InvalidConditionalVariableException(
                        Bundle.getMessage("ActionBadSignalMastType", ca->getType().toString()));
        }

        return action;
    }


    /*private*/ DigitalActionBean getEntryExitAction(@Nonnull ConditionalAction ca, DestinationPoints dp, String reference) throws JmriException {
        ActionEntryExit action =
                new ActionEntryExit(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                        .getAutoSystemName(), null);

        if (reference != null) {
            action->setAddressing(NamedBeanAddressing.Reference);
            action->setReference(reference);
        } else {
            action->setAddressing(NamedBeanAddressing.Direct);
            action->setDestinationPoints(dp);
        }
        action->setOperationAddressing(NamedBeanAddressing.Direct);

        switch (ca->getType()) {
            case SET_NXPAIR_ENABLED:
                action->setOperationDirect(ActionEntryExit.Operation.SetNXPairEnabled);
                break;
            case SET_NXPAIR_DISABLED:
                action->setOperationDirect(ActionEntryExit.Operation.SetNXPairDisabled);
                break;
            case SET_NXPAIR_SEGMENT:
                action->setOperationDirect(ActionEntryExit.Operation.SetNXPairSegment);
                break;
            default:
                throw new InvalidConditionalVariableException(
                        Bundle.getMessage("ActionBadEntryExitType", ca->getType().toString()));
        }

        return action;
    }


    /*private*/ DigitalActionBean getWarrantAction(@Nonnull ConditionalAction ca, Warrant w, String reference) throws JmriException {
        ActionWarrant action =
                new ActionWarrant(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                        .getAutoSystemName(), null);

        if (reference != null) {
            action->setAddressing(NamedBeanAddressing.Reference);
            action->setReference(reference);
        } else {
            action->setAddressing(NamedBeanAddressing.Direct);
            action->setWarrant(w);
        }
        action->setOperationAddressing(NamedBeanAddressing.Direct);

        switch (ca->getType()) {
            case ALLOCATE_WARRANT_ROUTE:
                action->setOperationDirect(ActionWarrant.DirectOperation.AllocateWarrantRoute);
                break;

            case DEALLOCATE_WARRANT_ROUTE:
                action->setOperationDirect(ActionWarrant.DirectOperation.DeallocateWarrant);
                break;

            case SET_ROUTE_TURNOUTS:
                action->setOperationDirect(ActionWarrant.DirectOperation.SetRouteTurnouts);
                break;

            case AUTO_RUN_WARRANT:
                action->setOperationDirect(ActionWarrant.DirectOperation.AutoRunTrain);
                break;

            case MANUAL_RUN_WARRANT:
                action->setOperationDirect(ActionWarrant.DirectOperation.ManuallyRunTrain);
                break;

            case CONTROL_TRAIN:
                action->setOperationDirect(ActionWarrant.DirectOperation.ControlAutoTrain);
                action->setControlAutoTrain(ActionWarrant.ControlAutoTrain.values()[ca->getActionData() - 1]);
                break;

            case SET_TRAIN_ID:
                action->setOperationDirect(ActionWarrant.DirectOperation.SetTrainId);
                String idData = ca->getActionString();
                if (idData == null || idData.isEmpty()) {
                    throw new InvalidConditionalActionException(
                            Bundle.getMessage("ActionBadWarrantValue", ca->getType().toString()));
                }
                if (idData.startsWith("@")) {
                    // indirect
                    String ref = "{" + idData.substring(1) + "}";
                    action->setDataAddressing(NamedBeanAddressing.Reference);
                    action->setDataReference(ref);
                } else {
                    action->setDataAddressing(NamedBeanAddressing.Direct);
                    action->setTrainIdName(idData);
                }
                break;

            case SET_TRAIN_NAME:
                action->setOperationDirect(ActionWarrant.DirectOperation.SetTrainName);
                String nameData = ca->getActionString();
                if (nameData == null || nameData.isEmpty()) {
                    throw new InvalidConditionalActionException(
                            Bundle.getMessage("ActionBadWarrantValue", ca->getType().toString()));
                }
                if (nameData.startsWith("@")) {
                    // indirect
                    String ref = "{" + nameData.substring(1) + "}";
                    action->setDataAddressing(NamedBeanAddressing.Reference);
                    action->setDataReference(ref);
                } else {
                    action->setDataAddressing(NamedBeanAddressing.Direct);
                    action->setTrainIdName(nameData);
                }
                break;

            default:
                throw new InvalidConditionalVariableException(
                        Bundle.getMessage("ActionBadwarrantType", ca->getType().toString()));
        }

        return action;
    }


    /*private*/ DigitalActionBean getOBlockAction(@Nonnull ConditionalAction ca, OBlock b, String reference) throws JmriException {

        ActionOBlock action =
                new ActionOBlock(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                        .getAutoSystemName(), null);

        if (reference != null) {
            action->setAddressing(NamedBeanAddressing.Reference);
            action->setReference(reference);
        } else {
            action->setAddressing(NamedBeanAddressing.Direct);
            action->setOBlock(b);
        }
        action->setOperationAddressing(NamedBeanAddressing.Direct);

        switch (ca->getType()) {
            case DEALLOCATE_BLOCK:
                action->setOperationDirect(ActionOBlock.DirectOperation.Deallocate);
                break;

            case SET_BLOCK_VALUE:
                action->setOperationDirect(ActionOBlock.DirectOperation.SetValue);
                String oblockData = ca->getActionString();
                if (oblockData == null || oblockData.isEmpty()) {
                    throw new InvalidConditionalActionException(
                            Bundle.getMessage("ActionBadOBlockValue", ca->getType().toString()));
                }
                if (oblockData.startsWith("@")) {
                    // indirect
                    String ref = "{" + oblockData.substring(1) + "}";
                    action->setDataAddressing(NamedBeanAddressing.Reference);
                    action->setDataReference(ref);
                } else {
                    action->setDataAddressing(NamedBeanAddressing.Direct);
                    action->setOBlockValue(oblockData);
                }
                break;

            case SET_BLOCK_ERROR:
                action->setOperationDirect(ActionOBlock.DirectOperation.SetError);
                break;

            case CLEAR_BLOCK_ERROR:
                action->setOperationDirect(ActionOBlock.DirectOperation.ClearError);
                break;

            case SET_BLOCK_OUT_OF_SERVICE:
                action->setOperationDirect(ActionOBlock.DirectOperation.SetOutOfService);
                break;

            case SET_BLOCK_IN_SERVICE:
                action->setOperationDirect(ActionOBlock.DirectOperation.ClearOutOfService);
                break;

            default:
                throw new InvalidConditionalVariableException(
                        Bundle.getMessage("ActionBadOBlockType", ca->getType().toString()));
        }

        return action;
    }


    /*private*/ DigitalActionBean getEnableLogixAction(@Nonnull ConditionalAction ca) throws JmriException {
        EnableLogix action =
                new EnableLogix(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                        .getAutoSystemName(), null);

        action->setAddressing(NamedBeanAddressing.Direct);
        action->setOperationAddressing(NamedBeanAddressing.Direct);

        String devName = ca->getDeviceName();
        if (devName != null) {
            if (devName.length() > 0 && devName.charAt(0) == '@') {
                String memName = devName.substring(1);
                action->setOperationAddressing(NamedBeanAddressing.Reference);
                action->setOperationReference("{" + memName + "}");
            } else {
                action->setLogix(devName);
            }
        }

        switch (ca->getType()) {
            case ENABLE_LOGIX:
                action->setOperationDirect(EnableLogix.Operation.Enable);
                break;

            case DISABLE_LOGIX:
                action->setOperationDirect(EnableLogix.Operation.Disable);
                break;

            default:
                throw new InvalidConditionalVariableException(
                        Bundle.getMessage("ActionBadEnableLogixType", ca->getType().toString()));
        }

        return action;
    }


    /*private*/ DigitalActionBean getClockAction(@Nonnull ConditionalAction ca) throws JmriException {
        ActionClock action =
                new ActionClock(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                        .getAutoSystemName(), null);

        switch (ca->getType()) {
            case START_FAST_CLOCK:
                action->setBeanState(ActionClock.ClockState.StartClock);
                break;

            case STOP_FAST_CLOCK:
                action->setBeanState(ActionClock.ClockState.StopClock);
                break;

            case SET_FAST_CLOCK_TIME:
                action->setBeanState(ActionClock.ClockState.SetClock);
                action->setClockTime(ca->getActionData());
                break;

            default:
                throw new InvalidConditionalVariableException(
                        Bundle.getMessage("ActionBadSensorType", ca->getType().toString()));
        }

        return action;
    }


    /*private*/ DigitalActionBean getAudioAction(@Nonnull ConditionalAction ca) throws JmriException {
        ActionAudio action =
                new ActionAudio(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                        .getAutoSystemName(), null);

        action->setOperationAddressing(NamedBeanAddressing.Direct);
        action->setAddressing(NamedBeanAddressing.Direct);

        String sound = ca->getActionString();
        if (sound != null && sound.length() > 0 && sound.charAt(0) == '@') {
            action->setAddressing(NamedBeanAddressing.Reference);
            action->setReference(sound.substring(1));
        } else {
            Audio audio = InstanceManager::getDefault(jmri.AudioManager.class).getAudio(ca->getDeviceName());
            if (audio != null) action->setAudio(audio);
        }

        switch (ca->getActionData()) {
            case Audio.CMD_PLAY:
                action->setOperation(ActionAudio.Operation.Play);
                break;
            case Audio.CMD_STOP:
                action->setOperation(ActionAudio.Operation.Stop);
                break;
            case Audio.CMD_PLAY_TOGGLE:
                action->setOperation(ActionAudio.Operation.PlayToggle);
                break;
            case Audio.CMD_PAUSE:
                action->setOperation(ActionAudio.Operation.Pause);
                break;
            case Audio.CMD_RESUME:
                action->setOperation(ActionAudio.Operation.Resume);
                break;
            case Audio.CMD_PAUSE_TOGGLE:
                action->setOperation(ActionAudio.Operation.PauseToggle);
                break;
            case Audio.CMD_REWIND:
                action->setOperation(ActionAudio.Operation.Rewind);
                break;
            case Audio.CMD_FADE_IN:
                action->setOperation(ActionAudio.Operation.FadeIn);
                break;
            case Audio.CMD_FADE_OUT:
                action->setOperation(ActionAudio.Operation.FadeOut);
                break;
            case Audio.CMD_RESET_POSITION:
                action->setOperation(ActionAudio.Operation.ResetPosition);
                break;
            default:
                break;
        }

        return action;
    }

    /*private*/ DigitalActionBean getSoundAction(@Nonnull ConditionalAction ca) throws JmriException {
        ActionSound action =
                new ActionSound(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                        .getAutoSystemName(), null);

        action->setOperationAddressing(NamedBeanAddressing.Direct);
        action->setSoundAddressing(NamedBeanAddressing.Direct);

        String sound = ca->getActionString();
        if (sound != null && sound.length() > 0 && sound.charAt(0) == '@') {
            action->setSoundAddressing(NamedBeanAddressing.Reference);
            action->setSoundReference(sound.substring(1));
        } else {
            action->setSound(sound);
        }

        return action;
    }

    /*private*/ DigitalActionBean getAudioOrSoundAction(@Nonnull ConditionalAction ca) throws JmriException {
        switch (ca->getType()) {
            case CONTROL_AUDIO:
                return getAudioAction(ca);

            case PLAY_SOUND:
                return getSoundAction(ca);

            default:
                throw new InvalidConditionalVariableException(
                        Bundle.getMessage("ConditionalBadAudioOrSoundType", ca->getType().toString()));
        }
    }


    /*private*/ DigitalActionBean getScriptAction(@Nonnull ConditionalAction ca) throws JmriException {
        ActionScript action =
                new ActionScript(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                        .getAutoSystemName(), null);

        action->setOperationAddressing(NamedBeanAddressing.Direct);
        action->setScriptAddressing(NamedBeanAddressing.Direct);

        String script = ca->getActionString();
        if (script != null && script.length() > 0 && script.charAt(0) == '@') {
            action->setScriptAddressing(NamedBeanAddressing.Reference);
            action->setScriptReference(script.substring(1));
        } else {
            action->setScript(script);
        }

        switch (ca->getType()) {
            case RUN_SCRIPT:
                action->setOperationType(ActionScript.OperationType.RunScript);
                break;

            case JYTHON_COMMAND:
                action->setOperationType(ActionScript.OperationType.JythonCommand);
                break;

            default:
                throw new InvalidConditionalVariableException(
                        Bundle.getMessage("ActionBadScriptType", ca->getType().toString()));
        }

        return action;
    }


    /*private*/ DigitalActionBean getRouteAction(@Nonnull ConditionalAction ca, Route b, String reference) throws JmriException {
        TriggerRoute action =
                new TriggerRoute(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                        .getAutoSystemName(), null);

        action->setAddressing(NamedBeanAddressing.Direct);
        action->setOperationAddressing(NamedBeanAddressing.Direct);

        String devName = ca->getDeviceName();
        if (devName != null) {
            if (devName.length() > 0 && devName.charAt(0) == '@') {
                String memName = devName.substring(1);
                action->setOperationAddressing(NamedBeanAddressing.Reference);
                action->setOperationReference("{" + memName + "}");
            } else {
                action->setRoute(devName);
            }
        }

        switch (ca->getType()) {
            case TRIGGER_ROUTE:
                action->setOperationDirect(TriggerRoute.Operation.TriggerRoute);
                break;

            default:
                throw new InvalidConditionalVariableException(
                        Bundle.getMessage("ActionBadRouteType", ca->getType().toString()));
        }

        return action;
    }

#endif
    /*private*/ /*final*/ /*static*/ Logger* ImportConditional::log = LoggerFactory::getLogger("ImportConditional");
