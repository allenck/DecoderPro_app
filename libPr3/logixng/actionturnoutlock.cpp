#include "actionturnoutlock.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalactionmanager.h"
#include "referenceutil.h"
#include "recursivedescentparser.h"
#include "vptr.h"
#include "conditionalng.h"
#include "typeconversionutil.h"

/**
 * This action sets the lock of a turnout.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class ActionTurnoutLock extends AbstractDigitalAction implements VetoableChangeListener {


/*public*/  ActionTurnoutLock::ActionTurnoutLock(QString sys, QString user, QObject* parent) : AbstractDigitalAction(sys, user, parent)
        /*throws BadUserNameException, BadSystemNameException*/ {
    //super(sys, user);
 setObjectName("ActionTurnoutLock");
}

//@Override
/*public*/  Base* ActionTurnoutLock::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throws ParserException*/ {
    DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
    ActionTurnoutLock* copy = new ActionTurnoutLock(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    if (_turnoutHandle != nullptr) copy->setTurnout(_turnoutHandle);
    copy->setTurnoutLock(_turnoutLock);
    copy->setAddressing(_addressing);
    copy->setFormula(_formula);
    copy->setLocalVariable(_localVariable);
    copy->setReference(_reference);
    copy->setLockAddressing(_lockAddressing);
    copy->setLockFormula(_stateFormula);
    copy->setLockLocalVariable(_stateLocalVariable);
    copy->setLockReference(_stateReference);
    return manager->registerAction(copy);
}

/*public*/  void ActionTurnoutLock::setTurnout(/*@Nonnull*/ QString turnoutName) {
    assertListenersAreNotRegistered(log, "setTurnout");
    Turnout* turnout = ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getTurnout(turnoutName);
    if (turnout != nullptr) {
        setTurnout(turnout);
    } else {
        removeTurnout();
        log->error(tr("turnout \"%1\" is not found").arg(turnoutName));
    }
}

/*public*/  void ActionTurnoutLock::setTurnout(/*@Nonnull*/ NamedBeanHandle<Turnout*>* handle) {
    assertListenersAreNotRegistered(log, "setTurnout");
    _turnoutHandle = handle;
    InstanceManager::turnoutManagerInstance()->addVetoableChangeListener(this);
}

/*public*/  void ActionTurnoutLock::setTurnout(/*@Nonnull*/ Turnout* turnout) {
    assertListenersAreNotRegistered(log, "setTurnout");
    setTurnout(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
            ->getNamedBeanHandle(turnout->getDisplayName(), turnout));
}

/*public*/  void ActionTurnoutLock::removeTurnout() {
    assertListenersAreNotRegistered(log, "setTurnout");
    if (_turnoutHandle != nullptr) {
        InstanceManager::turnoutManagerInstance()->removeVetoableChangeListener(this);
        _turnoutHandle = nullptr;
    }
}

/*public*/  NamedBeanHandle<Turnout*>* ActionTurnoutLock::getTurnout() {
    return _turnoutHandle;
}

/*public*/  void ActionTurnoutLock::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
    _addressing = addressing;
    parseFormula();
}

/*public*/  NamedBeanAddressing::TYPE ActionTurnoutLock::getAddressing() {
    return _addressing;
}

/*public*/  void ActionTurnoutLock::setReference(/*@Nonnull*/ QString reference) {
    if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
        throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
    }
    _reference = reference;
}

/*public*/  QString ActionTurnoutLock::getReference() {
    return _reference;
}

/*public*/  void ActionTurnoutLock::setLocalVariable(/*@Nonnull*/ QString localVariable) {
    _localVariable = localVariable;
}

/*public*/  QString ActionTurnoutLock::getLocalVariable() {
    return _localVariable;
}

/*public*/  void ActionTurnoutLock::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
    _formula = formula;
    parseFormula();
}

/*public*/  QString ActionTurnoutLock::getFormula() {
    return _formula;
}

/*private*/ void ActionTurnoutLock::parseFormula() /*throws ParserException*/ {
    if (_addressing == NamedBeanAddressing::Formula) {
        QMap<QString, Variable*> variables = QMap<QString, Variable*>();

        RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
        _expressionNode = parser->parseExpression(_formula);
    } else {
        _expressionNode = nullptr;
    }
}

/*public*/  void ActionTurnoutLock::setLockAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
    _lockAddressing = addressing;
    parseLockFormula();
}

/*public*/  NamedBeanAddressing::TYPE ActionTurnoutLock::getLockAddressing() {
    return _lockAddressing;
}

/*public*/  void ActionTurnoutLock::setTurnoutLock(TurnoutLock::ACT state) {
    _turnoutLock = state;
}

/*public*/  ActionTurnoutLock::TurnoutLock::ACT ActionTurnoutLock::getTurnoutLock() {
    return _turnoutLock;
}

/*public*/  void ActionTurnoutLock::setLockReference(/*@Nonnull*/ QString reference) {
    if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
        throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
    }
    _stateReference = reference;
}

/*public*/  QString ActionTurnoutLock::getLockReference() {
    return _stateReference;
}

/*public*/  void ActionTurnoutLock::setLockLocalVariable(/*@Nonnull*/ QString localVariable) {
    _stateLocalVariable = localVariable;
}

/*public*/  QString ActionTurnoutLock::getLockLocalVariable() {
    return _stateLocalVariable;
}

/*public*/  void ActionTurnoutLock::setLockFormula(/*Nonnull*/ QString formula) /*throws ParserException*/ {
    _stateFormula = formula;
    parseLockFormula();
}

/*public*/  QString ActionTurnoutLock::getLockFormula() {
    return _stateFormula;
}

/*private*/ void ActionTurnoutLock::parseLockFormula() /*throws ParserException*/ {
    if (_lockAddressing == NamedBeanAddressing::Formula) {
        QMap<QString, Variable*> variables = QMap<QString, Variable*>();

        RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
        _stateExpressionNode = parser->parseExpression(_stateFormula);
    } else {
        _stateExpressionNode = nullptr;
    }
}

//@Override
/*public*/  void ActionTurnoutLock::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
    if ("CanDelete" == (evt->getPropertyName())) { // No I18N
        if (VPtr<Turnout>::asPtr(evt->getOldValue())) {
            if (VPtr<Turnout>::asPtr(evt->getOldValue())->equals(getTurnout()->getBean())) {
                PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                throw new PropertyVetoException(tr("Turnout is in use by Turnout action \"%1\"").arg(getDisplayName()), e); // NOI18N
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
/*public*/  Category* ActionTurnoutLock::getCategory() {
    return Category::ITEM;
}

/*private*/ QString ActionTurnoutLock::getNewLock() /*throws JmriException*/ {

    switch (_lockAddressing) {
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
            throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_lockAddressing));
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void ActionTurnoutLock::execute() /*throws JmriException*/ {
    Turnout* turnout;

//        System.out.format("ActionTurnoutLock.execute: %s%n", getLongDescription());

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
            throw new IllegalArgumentException("invalid _addressing state: " +NamedBeanAddressing::toString( _addressing));
    }

//        System.out.format("ActionTurnoutLock.execute: turnout: %s%n", turnout);

    if (turnout == nullptr) {
//            log.error("turnout is null");
        return;
    }

    QString name = (_lockAddressing != NamedBeanAddressing::Direct)
            ? getNewLock() : nullptr;

    TurnoutLock::ACT lock;
    if (_lockAddressing == NamedBeanAddressing::Direct) {
        lock = _turnoutLock;
    } else {
        lock = TurnoutLock::valueOf(name);
    }

    if (lock == TurnoutLock::Toggle) {
        if (turnout->getLocked(Turnout::CABLOCKOUT)) {
            lock = TurnoutLock::Unlock;
        } else {
            lock = TurnoutLock::Lock;
        }
    }

    // Variables used in lambda must be effectively /*final*/
    TurnoutLock::ACT theLock = lock;

//    ThreadingUtil.runOnLayoutWithJmriException(() -> {
//        if (theLock == TurnoutLock.Lock) {
//            turnout.setLocked(Turnout.CABLOCKOUT + Turnout.PUSHBUTTONLOCKOUT, true);
//        } else if (theLock == TurnoutLock.Unlock) {
//            turnout.setLocked(Turnout.CABLOCKOUT + Turnout.PUSHBUTTONLOCKOUT, false);
//        }
//    });
    ThreadingUtil::runOnLayoutWithJmriException(new ATLRun(theLock, turnout));
}

//@Override
/*public*/  FemaleSocket* ActionTurnoutLock::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    throw new UnsupportedOperationException("Not supported.");
}

//@Override
/*public*/  int ActionTurnoutLock::getChildCount() {
    return 0;
}

//@Override
/*public*/  QString ActionTurnoutLock::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "Turnout, lock");
}

//@Override
/*public*/  QString ActionTurnoutLock::getLongDescription(QLocale locale) {
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
            namedBean = tr(/*locale,*/"by local ariable %1").arg(_localVariable);
            break;

        case NamedBeanAddressing::Formula:
            namedBean = tr(/*locale,*/ "by formula %1").arg(_formula);
            break;

        default:
            throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
    }

    switch (_lockAddressing) {
        case NamedBeanAddressing::Direct:
            state = tr(/*locale,*/ "%1").arg(TurnoutLock::toString(_turnoutLock));
            break;

        case NamedBeanAddressing::Reference:
            state = tr(/*locale,*/ "by reference %1").arg(_stateReference);
            break;

        case NamedBeanAddressing::LocalVariable:
            state = tr(/*locale,*/ "by local variable %1").arg(_stateLocalVariable);
            break;

        case NamedBeanAddressing::Formula:
            state = tr(/*locale,*/"by formula %1").arg(_stateFormula);
            break;

        default:
            throw new IllegalArgumentException("invalid _stateAddressing state: " + NamedBeanAddressing::toString(_lockAddressing));
    }

    return tr(/*locale,*/ "Set lock for turnout %1 to %2").arg( namedBean, state);
}

/** {@inheritDoc} */
//@Override
/*public*/  void ActionTurnoutLock::setup() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void ActionTurnoutLock::registerListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void ActionTurnoutLock::unregisterListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void ActionTurnoutLock::disposeMe() {
}



/** {@inheritDoc} */
//@Override
/*public*/  void ActionTurnoutLock::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl) {
    log->debug(tr("getUsageReport :: ActionTurnoutLock: bean = %1, report = %2").arg(cdl->getDisplayName()).arg(report.size()));
    if (getTurnout() != nullptr && bean->equals(getTurnout()->getBean())) {
        report.append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
    }
}

/*private*/ /*final*/ /*static*/ Logger* ActionTurnoutLock::log = LoggerFactory::getLogger("ActionTurnoutLock");

