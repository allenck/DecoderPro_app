#include "expressionturnout.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalexpressionmanager.h"
#include "parserexception.h"
#include "recursivedescentparser.h"
#include "conditionalng.h"
#include "referenceutil.h"
#include "vptr.h"
#include "typeconversionutil.h"

/**
 * This expression sets the state of a turnout->
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class ExpressionTurnout extends AbstractDigitalExpression
//        implements PropertyChangeListener, VetoableChangeListener {


/*public*/  ExpressionTurnout::ExpressionTurnout(QString sys, QString user, QObject* parent)
 : AbstractDigitalExpression(sys, user, parent)
        /*throws BadUserNameException, BadSystemNameException*/ {
    //super(sys, user);
    setObjectName("ExpressionTurnout");
}

//@Override
/*public*/  Base* ExpressionTurnout::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/ {
    DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == nullptr) sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
    ExpressionTurnout* copy = new ExpressionTurnout(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    if (_turnoutHandle != nullptr) copy->setTurnout(_turnoutHandle);
    copy->setBeanState(_turnoutState);
    copy->setAddressing(_addressing);
    copy->setFormula(_formula);
    copy->setLocalVariable(_localVariable);
    copy->setReference(_reference);
    copy->set_Is_IsNot(_is_IsNot);
    copy->setStateAddressing(_stateAddressing);
    copy->setStateFormula(_stateFormula);
    copy->setStateLocalVariable(_stateLocalVariable);
    copy->setStateReference(_stateReference);
    return manager->registerExpression(copy);
}

/*public*/  void ExpressionTurnout::setTurnout(/*@Nonnull*/ QString turnoutName) {
    assertListenersAreNotRegistered(log, "setTurnout");
    Turnout* turnout = ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getTurnout(turnoutName);
    if (turnout != nullptr) {
        setTurnout(turnout);
    } else {
        removeTurnout();
        log->error(tr("turnout \"%1\" is not found").arg(turnoutName));
    }
}

/*public*/  void ExpressionTurnout::setTurnout(/*@Nonnull*/ NamedBeanHandle<Turnout*>* handle) {
    assertListenersAreNotRegistered(log, "setTurnout");
    _turnoutHandle = handle;
    InstanceManager::turnoutManagerInstance()->addVetoableChangeListener(this);
}

/*public*/  void ExpressionTurnout::setTurnout(/*@Nonnull*/ Turnout* turnout) {
    assertListenersAreNotRegistered(log, "setTurnout");
    setTurnout(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
            ->getNamedBeanHandle(turnout->getDisplayName(), turnout));
}

/*public*/  void ExpressionTurnout::removeTurnout() {
    assertListenersAreNotRegistered(log, "setTurnout");
    if (_turnoutHandle != nullptr) {
        InstanceManager::turnoutManagerInstance()->removeVetoableChangeListener(this);
        _turnoutHandle = nullptr;
    }
}

/*public*/  NamedBeanHandle<Turnout*>* ExpressionTurnout::getTurnout() {
    return _turnoutHandle;
}

/*public*/  void ExpressionTurnout::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
    _addressing = addressing;
    parseFormula();
}

/*public*/  NamedBeanAddressing::TYPE ExpressionTurnout::getAddressing() {
    return _addressing;
}

/*public*/  void ExpressionTurnout::setReference(/*@Nonnull*/ QString reference) {
    if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
        throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
    }
    _reference = reference;
}

/*public*/  QString ExpressionTurnout::getReference() {
    return _reference;
}

/*public*/  void ExpressionTurnout::setLocalVariable(/*@Nonnull*/ QString localVariable) {
    _localVariable = localVariable;
}

/*public*/  QString ExpressionTurnout::getLocalVariable() {
    return _localVariable;
}

/*public*/  void ExpressionTurnout::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException */{
    _formula = formula;
    parseFormula();
}

/*public*/  QString ExpressionTurnout::getFormula() {
    return _formula;
}

/*private*/ void ExpressionTurnout::parseFormula() /*throws ParserException*/ {
    if (_addressing == NamedBeanAddressing::Formula) {
        QMap<QString, Variable*> variables = QMap<QString, Variable*>();

        RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
        _expressionNode = parser->parseExpression(_formula);
    } else {
        _expressionNode = nullptr;
    }
}

/*public*/  void ExpressionTurnout::set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot) {
    _is_IsNot = is_IsNot;
}

/*public*/  Is_IsNot_Enum::VAL ExpressionTurnout::get_Is_IsNot() {
    return _is_IsNot;
}

/*public*/  void ExpressionTurnout::setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException */{
    _stateAddressing = addressing;
    parseStateFormula();
}

/*public*/  NamedBeanAddressing::TYPE ExpressionTurnout::getStateAddressing() {
    return _stateAddressing;
}

/*public*/  void ExpressionTurnout::setBeanState(TurnoutState::VAL state) {
    _turnoutState = state;
}

/*public*/  ExpressionTurnout::TurnoutState::VAL ExpressionTurnout::getBeanState() {
    return _turnoutState;
}

/*public*/  void ExpressionTurnout::setStateReference(/*@Nonnull*/ QString reference) {
    if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
        throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
    }
    _stateReference = reference;
}

/*public*/  QString ExpressionTurnout::getStateReference() {
    return _stateReference;
}

/*public*/  void ExpressionTurnout::setStateLocalVariable(/*@Nonnull*/ QString localVariable) {
    _stateLocalVariable = localVariable;
}

/*public*/  QString ExpressionTurnout::getStateLocalVariable() {
    return _stateLocalVariable;
}

/*public*/  void ExpressionTurnout::setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
    _stateFormula = formula;
    parseStateFormula();
}

/*public*/  QString ExpressionTurnout::getStateFormula() {
    return _stateFormula;
}

/*private*/ void ExpressionTurnout::parseStateFormula() /*throws ParserException*/ {
    if (_stateAddressing == NamedBeanAddressing::Formula) {
        QMap<QString, Variable*> variables = QMap<QString, Variable*>();

        RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
        _stateExpressionNode = parser->parseExpression(_stateFormula);
    } else {
        _stateExpressionNode = nullptr;
    }
}

//@Override
/*public*/  void ExpressionTurnout::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException */{
    if ("CanDelete" == (evt->getPropertyName())) { // No I18N
        if (VPtr<Turnout>::asPtr(evt->getOldValue())) {
            if (VPtr<Turnout>::asPtr(evt->getOldValue())->equals(getTurnout()->getBean())) {
                PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                throw new PropertyVetoException(tr("Turnout is in use by Turnout expression \"%1\"").arg(AbstractNamedBean::getDisplayName()), e); // NOI18N
            }
        }
    } else if ("DoDelete" == (evt->getPropertyName())) { // No I18N
        if (VPtr<Turnout>::asPtr(evt->getOldValue())) {
            if (VPtr<Turnout>::asPtr(evt->getOldValue())->equals(getTurnout()->getBean())) {
                removeTurnout();
            }
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  Category* ExpressionTurnout::getCategory() {
    return Category::ITEM;
}

/*private*/ QString ExpressionTurnout::getNewState() /*throws JmriException*/ {

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
/*public*/  bool ExpressionTurnout::evaluate() /*throws JmriException*/ {
    Turnout* turnout;

//        System.out.format("ExpressionTurnout.evaluate: %s%n", getLongDescription());

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

//        System.out.format("ExpressionTurnout.evaluate: turnout: %s%n", turnout);

    if (turnout == nullptr) {
//            log.warn("turnout is null");
        return false;
    }

    TurnoutState::VAL checkTurnoutState;

    if (_stateAddressing == NamedBeanAddressing::Direct) {
        checkTurnoutState = _turnoutState;
    } else {
        checkTurnoutState = TurnoutState::valueOf(getNewState());
    }

    TurnoutState::VAL currentTurnoutState = TurnoutState::get(turnout->getKnownState());
    if (_is_IsNot == Is_IsNot_Enum::Is) {
        return currentTurnoutState == checkTurnoutState;
    } else {
        return currentTurnoutState != checkTurnoutState;
    }
}

//@Override
/*public*/  FemaleSocket* ExpressionTurnout::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */{
    throw new UnsupportedOperationException("Not supported.");
}

//@Override
/*public*/  int ExpressionTurnout::getChildCount() {
    return 0;
}

//@Override
/*public*/  QString ExpressionTurnout::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "Turnout");
}

//@Override
/*public*/  QString ExpressionTurnout::getLongDescription(QLocale locale) {
    QString namedBean;
    QString state;

    switch (_addressing) {
        case NamedBeanAddressing::Direct:
        {
            QString turnoutName;
            if (_turnoutHandle != nullptr) {
                turnoutName = _turnoutHandle->getBean()->getDisplayName();
            } else {
                turnoutName = tr(/*locale,*/ "''");
            }
            namedBean = tr(/*locale,*/ "%1").arg(turnoutName);
            break;
        }
        case NamedBeanAddressing::Reference:
            namedBean = tr(/*locale,*/ "by reference %1").arg(_reference);
            break;

        case NamedBeanAddressing::LocalVariable:
            namedBean = tr(/*locale, */"by local variable %1").arg(_localVariable);
            break;

        case NamedBeanAddressing::Formula:
            namedBean = tr(/*locale,*/ "by formula %1").arg(_formula);
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

    return tr(/*locale,*/ "Turnout %1 %2 %3").arg(namedBean, Is_IsNot_Enum::toString(_is_IsNot), state);
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionTurnout::setup() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionTurnout::registerListenersForThisClass() {
    if (!_listenersAreRegistered && (_turnoutHandle != nullptr)) {
        _turnoutHandle->getBean()->addPropertyChangeListener("KnownState", this);
        _listenersAreRegistered = true;
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionTurnout::unregisterListenersForThisClass() {
    if (_listenersAreRegistered) {
        _turnoutHandle->getBean()->removePropertyChangeListener("KnownState", this);
        _listenersAreRegistered = false;
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionTurnout::propertyChange(PropertyChangeEvent* evt) {
    getConditionalNG()->execute();
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionTurnout::disposeMe() {
}



/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionTurnout::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl) {
    log->debug(tr("getUsageReport :: ExpressionTurnout: bean = %1, report = %2").arg(cdl->getDisplayName()).arg(report.size()));
    if (getTurnout() != nullptr && bean->equals(getTurnout()->getBean())) {
        report.append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription(QLocale())));
    }
}

/*private*/ /*final*/ /*static*/ Logger* ExpressionTurnout::log = LoggerFactory::getLogger("ExpressionTurnout");
