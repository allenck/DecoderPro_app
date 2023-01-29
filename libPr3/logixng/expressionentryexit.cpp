#include "expressionentryexit.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "entryexitpairs.h"
#include "loggerfactory.h"
#include "referenceutil.h"
#include "conditionalng.h"
#include "recursivedescentparser.h"
#include "vptr.h"
#include "typeconversionutil.h"
#include "is_isnot_enum.h"
/**
 * This expression sets the state of a DestinationPoints.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class ExpressionEntryExit extends AbstractDigitalExpression
//        implements PropertyChangeListener, VetoableChangeListener {



/*public*/  ExpressionEntryExit::ExpressionEntryExit(QString sys, QString user, QObject* parent)
 : AbstractDigitalExpression(sys, user, parent)
        /*throws BadUserNameException, BadSystemNameException */{
    //super(sys, user);
}

//@Override
/*public*/  Base* ExpressionEntryExit::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/ {
    DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = manager->getAutoSystemName();
    ExpressionEntryExit* copy = new ExpressionEntryExit(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    if (_entryDestinationPoints != nullptr) copy->setDestinationPoints(_entryDestinationPoints);
    copy->setBeanState(_entryExitState);
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

/*public*/  void ExpressionEntryExit::setDestinationPoints(/*@Nonnull*/ QString entryExitName) {
    assertListenersAreNotRegistered(log, "setEntryExit");
    DestinationPoints* destinationPoints = (DestinationPoints*)
            ((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))->getNamedBean(entryExitName)->self();
    if (destinationPoints != nullptr) {
        setDestinationPoints(destinationPoints);
    } else {
        removeDestinationPoints();
        log->warn(tr("destinationPoints \"%1\" is not found").arg(entryExitName));
    }
}

/*public*/  void ExpressionEntryExit::setDestinationPoints(/*@Nonnull*/ NamedBeanHandle<DestinationPoints*>* handle) {
    assertListenersAreNotRegistered(log, "setEntryExit");
    _entryDestinationPoints = handle;
    ((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))->VetoableChangeSupport::addVetoableChangeListener(this);
}

/*public*/  void ExpressionEntryExit::setDestinationPoints(/*@Nonnull*/ DestinationPoints* destinationPoints) {
    assertListenersAreNotRegistered(log, "setEntryExit");
    setDestinationPoints(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
            ->getNamedBeanHandle(destinationPoints->getDisplayName(), destinationPoints));
}

/*public*/  void ExpressionEntryExit::removeDestinationPoints() {
    assertListenersAreNotRegistered(log, "setEntryExit");
    if (_entryDestinationPoints != nullptr) {
        ((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))->VetoableChangeSupport::removeVetoableChangeListener(this);
        _entryDestinationPoints = nullptr;
    }
}

/*public*/  NamedBeanHandle<DestinationPoints*>* ExpressionEntryExit::getEntryExit() {
    return _entryDestinationPoints;
}

/*public*/  void ExpressionEntryExit::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
    _addressing = addressing;
    parseFormula();
}

/*public*/  NamedBeanAddressing::TYPE ExpressionEntryExit::getAddressing() {
    return _addressing;
}

/*public*/  void ExpressionEntryExit::setReference(/*@Nonnull*/ QString reference) {
    if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
        throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
    }
    _reference = reference;
}

/*public*/  QString ExpressionEntryExit::getReference() {
    return _reference;
}

/*public*/  void ExpressionEntryExit::setLocalVariable(/*@Nonnull*/ QString localVariable) {
    _localVariable = localVariable;
}

/*public*/  QString ExpressionEntryExit::getLocalVariable() {
    return _localVariable;
}

/*public*/  void ExpressionEntryExit::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
    _formula = formula;
    parseFormula();
}

/*public*/  QString ExpressionEntryExit::getFormula() {
    return _formula;
}

/*private*/ void ExpressionEntryExit::parseFormula() /*throws ParserException*/ {
    if (_addressing == NamedBeanAddressing::Formula) {
        QMap<QString, Variable*> variables = QMap<QString, Variable*>();

        RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
        _expressionNode = parser->parseExpression(_formula);
    } else {
        _expressionNode = nullptr;
    }
}

/*public*/  void ExpressionEntryExit::set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot) {
    _is_IsNot = is_IsNot;
}

/*public*/  Is_IsNot_Enum::VAL ExpressionEntryExit::get_Is_IsNot() {
    return _is_IsNot;
}

/*public*/  void ExpressionEntryExit::setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
    _stateAddressing = addressing;
    parseStateFormula();
}

/*public*/  NamedBeanAddressing::TYPE ExpressionEntryExit::getStateAddressing() {
    return _stateAddressing;
}

/*public*/  void ExpressionEntryExit::setBeanState(EntryExitState::STATE state) {
    _entryExitState = state;
}

/*public*/  ExpressionEntryExit::EntryExitState::STATE ExpressionEntryExit::getBeanState() {
    return _entryExitState;
}

/*public*/  void ExpressionEntryExit::setStateReference(/*@Nonnull*/ QString reference) {
    if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
        throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
    }
    _stateReference = reference;
}

/*public*/  QString ExpressionEntryExit::getStateReference() {
    return _stateReference;
}

/*public*/  void ExpressionEntryExit::setStateLocalVariable(/*@Nonnull*/ QString localVariable) {
    _stateLocalVariable = localVariable;
}

/*public*/  QString ExpressionEntryExit::getStateLocalVariable() {
    return _stateLocalVariable;
}

/*public*/  void ExpressionEntryExit::setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
    _stateFormula = formula;
    parseStateFormula();
}

/*public*/  QString ExpressionEntryExit::getStateFormula() {
    return _stateFormula;
}

/*private*/ void ExpressionEntryExit::parseStateFormula() /*throws ParserException*/ {
    if (_stateAddressing == NamedBeanAddressing::Formula) {
        QMap<QString, Variable*> variables = QMap<QString, Variable*>();

        RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
        _stateExpressionNode = parser->parseExpression(_stateFormula);
    } else {
        _stateExpressionNode = nullptr;
    }
}

//@Override
/*public*/  void ExpressionEntryExit::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
    if ("CanDelete" == (evt->getPropertyName())) { // No I18N
        if (VPtr<DestinationPoints>::asPtr(evt->getOldValue() ) ) {
            if (VPtr<DestinationPoints>::asPtr(evt->getOldValue())->equals(getEntryExit()->getBean())) {
                PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                throw new PropertyVetoException(tr("The EntryExit s in use by %1").arg(getDisplayName()), e); // NOI18N
            }
        }
    } else if ("DoDelete" == (evt->getPropertyName())) { // No I18N
        if (VPtr<DestinationPoints>::asPtr(evt->getOldValue())) {
            if (VPtr<DestinationPoints>::asPtr(evt->getOldValue())->equals(getEntryExit()->getBean())) {
                removeDestinationPoints();
            }
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  Category ExpressionEntryExit::getCategory() {
    return Category::ITEM;
}

/*private*/ QString ExpressionEntryExit::getNewState() /*throws JmriException*/ {

    switch (_stateAddressing) {
        case NamedBeanAddressing::Reference:
            return ReferenceUtil::getReference(
                    getConditionalNG()->getSymbolTable(), _stateReference);

        case NamedBeanAddressing::LocalVariable:
        {
            SymbolTable* symbolTable =
                    getConditionalNG()->getSymbolTable();
            return TypeConversionUtil::
                    convertToString(symbolTable->getValue(_stateLocalVariable), false);
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
/*public*/  bool ExpressionEntryExit::evaluate() /*throws JmriException*/ {
    DestinationPoints* destinationPoints;

//        System.out.format("ExpressionEntryExit.execute: %s%n", getLongDescription());

    switch (_addressing) {
        case NamedBeanAddressing::Direct:
            destinationPoints = _entryDestinationPoints != nullptr ? _entryDestinationPoints->getBean() : nullptr;
            break;

        case NamedBeanAddressing::Reference:
        {
            QString ref = ReferenceUtil::getReference(
                    getConditionalNG()->getSymbolTable(), _reference);
            destinationPoints = (DestinationPoints*)((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))
                    ->getNamedBean(ref)->self();
            break;
        }
        case NamedBeanAddressing::LocalVariable:
        {
            SymbolTable* symbolTable =
                    getConditionalNG()->getSymbolTable();
            destinationPoints = (DestinationPoints*)((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))
                    ->getNamedBean(TypeConversionUtil::
                            convertToString(symbolTable->getValue(_localVariable), false))->self();
            break;
        }
        case NamedBeanAddressing::Formula:
            destinationPoints = _expressionNode != nullptr ?
                    (DestinationPoints*)((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))
                            ->getNamedBean(TypeConversionUtil::
                                    convertToString(_expressionNode->calculate(
                                            getConditionalNG()->getSymbolTable()), false))->self()
                    : nullptr;
            break;

        default:
            throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
    }

//        System.out.format("ExpressionEntryExit.execute: destinationPoints: %s%n", destinationPoints);

    if (destinationPoints == nullptr) {
//            log.warn("destinationPoints is null");
        return false;
    }

    EntryExitState::STATE checkEntryExitState;

    if (_stateAddressing == NamedBeanAddressing::Direct) {
        checkEntryExitState = _entryExitState;
    } else {
        checkEntryExitState = (EntryExitState::fromString(getNewState()));
    }

    EntryExitState::STATE currentEntryExitState = (EntryExitState::STATE)destinationPoints->getState();
    if (_is_IsNot == Is_IsNot_Enum::Is) {
        return currentEntryExitState == checkEntryExitState;
    } else {
        return currentEntryExitState != checkEntryExitState;
    }
}

//@Override
/*public*/  FemaleSocket* ExpressionEntryExit::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    throw new UnsupportedOperationException("Not supported.");
}

//@Override
/*public*/  int ExpressionEntryExit::getChildCount() {
    return 0;
}

//@Override
/*public*/  QString ExpressionEntryExit::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "EntryExit");
}

//@Override
/*public*/  QString ExpressionEntryExit::getLongDescription(QLocale locale) {
    QString namedBean;
    QString state;

    switch (_addressing) {
        case NamedBeanAddressing::Direct:
        {
            QString entryExitName;
            if (_entryDestinationPoints != nullptr) {
                entryExitName = _entryDestinationPoints->getBean()->getDisplayName();
            } else {
                entryExitName = tr(/*locale,*/ "");
            }
            namedBean = tr(/*locale,*/ "%1").arg(entryExitName);
            break;
        }
        case NamedBeanAddressing::Reference:
            namedBean = tr(/*locale, */"by reference %1").arg(_reference);
            break;

        case NamedBeanAddressing::LocalVariable:
            namedBean = tr(/*locale,*/ "by local variable %1").arg(_localVariable);
            break;

        case NamedBeanAddressing::Formula:
            namedBean = tr(/*locale, */"by formua %1").arg(_formula);
            break;

        default:
            throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
    }

    switch (_stateAddressing) {
        case NamedBeanAddressing::Direct:
            state = tr(/*locale, */ "%1").arg(tr("Direct"));
            break;

        case NamedBeanAddressing::Reference:
            state = tr(/*locale, */ "by reference %1").arg(_stateReference);
            break;

        case NamedBeanAddressing::LocalVariable:
            state = tr(/*locale, */ "by local variable %1").arg(_stateLocalVariable);
            break;

        case NamedBeanAddressing::Formula:
            state = tr(/*locale, */ "by formula %1").arg(_stateFormula);
            break;

        default:
            throw new IllegalArgumentException("invalid _stateAddressing state: " + NamedBeanAddressing::toString(_stateAddressing));
    }

    return tr(/*locale, */ "EntryExit %1 %2 ").arg(namedBean, state);
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionEntryExit::setup() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionEntryExit::registerListenersForThisClass() {
    if (!_listenersAreRegistered && (_entryDestinationPoints != nullptr)) {
        _entryDestinationPoints->getBean()->addPropertyChangeListener("active", this);
        _listenersAreRegistered = true;
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionEntryExit::unregisterListenersForThisClass() {
    if (_listenersAreRegistered) {
        _entryDestinationPoints->getBean()->removePropertyChangeListener("active", this);
        _listenersAreRegistered = false;
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionEntryExit::propertyChange(PropertyChangeEvent* evt) {
    getConditionalNG()->execute();
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionEntryExit::disposeMe() {
}
#if 0
/*public*/  enum EntryExitState {
    Inactive(0x04, Bundle.getMessage("EntryExitStateInactive")),
    Active(0x02, Bundle.getMessage("EntryExitStateActive")),
    Other(-1, Bundle.getMessage("EntryExitOtherStatus"));

    /*private*/ final int _id;
    /*private*/ final String _text;

    /*private*/ EntryExitState(int id, String text) {
        this._id = id;
        this._text = text;
    }

    static /*public*/  EntryExitState get(int id) {
        switch (id) {
            case 0x04:
                return Inactive;

            case 0x02:
                return Active;

            default:
                return Other;
        }
    }

    /*public*/  int getID() {
        return _id;
    }

    //@Override
    /*public*/  String toString() {
        return _text;
    }

}
#endif
/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionEntryExit::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
 //   log->debug(tr("getUsageReport :: ExpressionEntryExit: bean = %1, report = %2").arg(((AbstractNamedBean*)cdl->self())->getDisplayName(), report.));
    if (getEntryExit() != nullptr && bean->equals(getEntryExit()->getBean())) {
        report->append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription(QLocale())));
    }
}

/*private*/ /*final*/ /*static*/ Logger* ExpressionEntryExit::log = LoggerFactory::getLogger("ExpressionEntryExit");
