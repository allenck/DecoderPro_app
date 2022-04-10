#include "actionturnout.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "defaultdigitalactionmanager.h"
#include "referenceutil.h"
#include "recursivedescentparser.h"
#include "vptr.h"
#include "typeconversionutil.h"
#include "conditionalng.h"

/**
 * This action sets the state of a turnout.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class ActionTurnout extends AbstractDigitalAction implements VetoableChangeListener {


    /*public*/  ActionTurnout::ActionTurnout(QString sys, QString user, QObject *parent) : AbstractDigitalAction(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
     setObjectName("ActionTurnout");
    }

    //@Override
    /*public*/  Base* ActionTurnout::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throws ParserException*/ {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
        ActionTurnout* copy = new ActionTurnout(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_turnoutHandle != nullptr) copy->setTurnout(_turnoutHandle);
        copy->setBeanState(_turnoutState);
        copy->setAddressing(_addressing);
        copy->setFormula(_formula);
        copy->setLocalVariable(_localVariable);
        copy->setReference(_reference);
        copy->setStateAddressing(_stateAddressing);
        copy->setStateFormula(_stateFormula);
        copy->setStateLocalVariable(_stateLocalVariable);
        copy->setStateReference(_stateReference);
        return manager->registerAction(copy);
    }

    /*public*/  void ActionTurnout::setTurnout(/*@Nonnull*/ QString turnoutName) {
        assertListenersAreNotRegistered(log, "setTurnout");
        Turnout* turnout = ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getTurnout(turnoutName);
        if (turnout != nullptr) {
            setTurnout(turnout);
        } else {
            removeTurnout();
            log->error(tr("turnout \"%1\" is not found").arg(turnoutName));
        }
    }

    /*public*/  void ActionTurnout::setTurnout(/*@Nonnull*/ NamedBeanHandle<Turnout*>* handle) {
        assertListenersAreNotRegistered(log, "setTurnout");
        _turnoutHandle = handle;
        InstanceManager::turnoutManagerInstance()->addVetoableChangeListener(this);
    }

    /*public*/  void ActionTurnout::setTurnout(/*@Nonnull*/ Turnout* turnout) {
        assertListenersAreNotRegistered(log, "setTurnout");
        setTurnout(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(turnout->getDisplayName(), turnout));
    }

    /*public*/  void ActionTurnout::removeTurnout() {
        assertListenersAreNotRegistered(log, "setTurnout");
        if (_turnoutHandle != nullptr) {
            InstanceManager::turnoutManagerInstance()->removeVetoableChangeListener(this);
            _turnoutHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<Turnout*>* ActionTurnout::getTurnout() {
        return _turnoutHandle;
    }

    /*public*/  void ActionTurnout::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ActionTurnout::getAddressing() {
        return _addressing;
    }

    /*public*/  void ActionTurnout::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/  QString ActionTurnout::getReference() {
        return _reference;
    }

    /*public*/  void ActionTurnout::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/  QString ActionTurnout::getLocalVariable() {
        return _localVariable;
    }

    /*public*/  void ActionTurnout::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _formula = formula;
        parseFormula();
    }

    /*public*/  QString ActionTurnout::getFormula() {
        return _formula;
    }

    /*private*/ void ActionTurnout::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }

    /*public*/  void ActionTurnout::setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _stateAddressing = addressing;
        parseStateFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ActionTurnout::getStateAddressing() {
        return _stateAddressing;
    }

    /*public*/  void ActionTurnout::setBeanState(TurnoutState::STATE state) {
        _turnoutState = state;
    }

    /*public*/  ActionTurnout::TurnoutState::STATE ActionTurnout::getBeanState() {
        return _turnoutState;
    }

    /*public*/  void ActionTurnout::setStateReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _stateReference = reference;
    }

    /*public*/  QString ActionTurnout::getStateReference() {
        return _stateReference;
    }

    /*public*/  void ActionTurnout::setStateLocalVariable(/*@Nonnull*/ QString localVariable) {
        _stateLocalVariable = localVariable;
    }

    /*public*/  QString ActionTurnout::getStateLocalVariable() {
        return _stateLocalVariable;
    }

    /*public*/  void ActionTurnout::setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _stateFormula = formula;
        parseStateFormula();
    }

    /*public*/  QString ActionTurnout::getStateFormula() {
        return _stateFormula;
    }

    /*private*/ void ActionTurnout::parseStateFormula() /*throws ParserException*/ {
        if (_stateAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _stateExpressionNode = parser->parseExpression(_stateFormula);
        } else {
            _stateExpressionNode = nullptr;
        }
    }

    //@Override
    /*public*/  void ActionTurnout::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<Turnout>::asPtr(evt->getOldValue())) {
                if (VPtr<Turnout>::asPtr(evt->getOldValue())->equals(getTurnout()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Turnout is in use by Turnout action \"%1\"").arg(AbstractNamedBean::getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete" ==(evt->getPropertyName())) { // No I18N
            if (VPtr<Turnout>::asPtr(evt->getOldValue())) {
                if (VPtr<Turnout>::asPtr(evt->getOldValue())->equals(getTurnout()->getBean())) {
                    removeTurnout();
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category* ActionTurnout::getCategory() {
        return Category::ITEM;
    }

    /*private*/ QString ActionTurnout::getNewState() /*throws JmriException*/ {

        switch (_stateAddressing) {
            case NamedBeanAddressing::Reference:
                return ReferenceUtil::getReference(
                        getConditionalNG()->getSymbolTable(), _stateReference);

            case NamedBeanAddressing::LocalVariable:
            {
                SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                return TypeConversionUtil
                        ::convertToString(symbolTable->getValue(_stateLocalVariable), false);
            }
            case NamedBeanAddressing::Formula:
                return _stateExpressionNode != nullptr
                        ? TypeConversionUtil::convertToString(
                                _stateExpressionNode->calculate(
                                        getConditionalNG()->getSymbolTable()), false)
                        : nullptr;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_stateAddressing));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionTurnout::execute() /*throws JmriException*/ {
        Turnout* turnout;

//        System.out.format("ActionTurnout.execute: %s%n", getLongDescription());

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
                turnout = _turnoutHandle != nullptr ? _turnoutHandle->getBean() : nullptr;
                break;

            case NamedBeanAddressing::Reference:
            {
                QString ref = ReferenceUtil::getReference(
                        getConditionalNG()->getSymbolTable(), _reference);
                turnout = (Turnout*)((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))
                        ->AbstractProxyManager::getNamedBean(ref)->self();
                break;
            }
            case NamedBeanAddressing::LocalVariable:
            {
                SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                turnout = (Turnout*)((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))
                        ->AbstractProxyManager::getNamedBean(TypeConversionUtil
                                ::convertToString(symbolTable->getValue(_localVariable), false))->self();
                break;
            }
            case NamedBeanAddressing::Formula:
                turnout = _expressionNode != nullptr ?
                        (Turnout*)((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))
                                ->AbstractProxyManager::getNamedBean(TypeConversionUtil
                                        ::convertToString(_expressionNode->calculate(
                                                getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

//        System.out.format("ActionTurnout.execute: turnout: %s%n", turnout);

        if (turnout == nullptr) {
//            log.error("turnout is null");
            return;
        }

        QString name = (_stateAddressing != NamedBeanAddressing::Direct)
                ? getNewState() : nullptr;

        TurnoutState::STATE state;
        if ((_stateAddressing == NamedBeanAddressing::Direct)) {
            state = _turnoutState;
        } else {
            state = TurnoutState::valueOf(name);
        }

//        ThreadingUtil::runOnLayoutWithJmriException(() -> {
//            if (state == TurnoutState.Toggle) {
//                if (turnout.getKnownState() == Turnout.CLOSED) {
//                    turnout.setCommandedState(Turnout.THROWN);
//                } else {
//                    turnout.setCommandedState(Turnout.CLOSED);
//                }
//            } else {
//                turnout.setCommandedState(state.getID());
//            }
//        });
        ThreadingUtil::runOnLayoutWithJmriException(new ToggleTurnout(turnout, state));
    }

    //@Override
    /*public*/  FemaleSocket* ActionTurnout::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int ActionTurnout::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString ActionTurnout::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Turnout");
    }

    //@Override
    /*public*/  QString ActionTurnout::getLongDescription(QLocale locale) {
        QString namedBean;
        QString state;

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
            {
                QString turnoutName;
                if (_turnoutHandle != nullptr) {
                    turnoutName = _turnoutHandle->getBean()->getDisplayName();
                } else {
                    turnoutName = tr(/*locale, */"''");
                }
                namedBean = tr(/*locale, */"%1").arg(turnoutName);
                break;
            }
            case NamedBeanAddressing::Reference:
                namedBean = tr(/*locale,*/ "by reference %1").arg(_reference);
                break;

            case NamedBeanAddressing::LocalVariable:
                namedBean = tr(/*locale,*/ "by local variable %1").arg(_localVariable);
                break;

            case NamedBeanAddressing::Formula:
                namedBean = tr(/*locale, */"by formula %1").arg(_formula);
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        switch (_stateAddressing) {
            case NamedBeanAddressing::Direct:
                state = tr(/*locale,*/ "%1").arg(TurnoutState::toString(_turnoutState));
                break;

            case NamedBeanAddressing::Reference:
                state = tr(/*locale,*/ "by reference %1").arg(_stateReference);
                break;

            case NamedBeanAddressing::LocalVariable:
                state = tr(/*locale,*/ "by local variable %1").arg(_stateLocalVariable);
                break;

            case NamedBeanAddressing::Formula:
                state = tr(/*locale,*/ "by formula %1").arg(_stateFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _stateAddressing state: " + NamedBeanAddressing::toString(_stateAddressing));
        }

        return tr(/*locale,*/ "Set turnout %1 to state %2").arg(namedBean, state);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionTurnout::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionTurnout::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionTurnout::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionTurnout::disposeMe() {
    }


    // This constant is only used internally in TurnoutState but must be outside
    // the enum.
    /*private*/ /*static*/ /*final*/ int ActionTurnout::TOGGLE_ID = -1;


    /*private*/ /*final*/ /*static*/ Logger* ActionTurnout::log = LoggerFactory::getLogger("ActionTurnout");


