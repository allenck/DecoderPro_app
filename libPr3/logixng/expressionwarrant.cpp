#include "expressionwarrant.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "logixng/conditionalng.h"
#include "logixng/defaultdigitalexpressionmanager.h"
#include "logixng/recursivedescentparser.h"
#include "logixng/variable.h"
#include "warrant.h"
#include "warrantmanager.h"
#include "referenceutil.h"
#include "vptr.h"
#include "typeconversionutil.h"
#include "is_isnot_enum.h"

/**
 * This expression sets the state of a warrant.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/ class ExpressionWarrant extends AbstractDigitalExpression
//        implements PropertyChangeListener, VetoableChangeListener {


    /*public*/ ExpressionWarrant::ExpressionWarrant(QString sys, QString user, QObject* parent)
     : AbstractDigitalExpression(sys,user,parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
    setObjectName("ExpressionWarrant");
    }

    //@Override
    /*public*/ Base* ExpressionWarrant::getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws ParserException*/ {
        DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ExpressionWarrant* copy = new ExpressionWarrant(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_warrantHandle != nullptr) copy->setWarrant(_warrantHandle);
        copy->setBeanState(_warrantState);
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

    /*public*/ void ExpressionWarrant::setWarrant(/*@Nonnull*/ QString warrantName) {
        assertListenersAreNotRegistered(log, "setWarrant");
        Warrant* warrant = (Warrant*)((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getWarrant(warrantName)->self();
        if (warrant != nullptr) {
            setWarrant(warrant);
        } else {
            removeWarrant();
            log->warn(tr("warrant \"%1\" is not found").arg(warrantName));
        }
    }

    /*public*/ void ExpressionWarrant::setWarrant(/*@Nonnull*/ NamedBeanHandle<Warrant*>* handle) {
        assertListenersAreNotRegistered(log, "setWarrant");
        _warrantHandle = handle;
        ((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/ void ExpressionWarrant::setWarrant(/*@Nonnull*/ Warrant* warrant) {
        assertListenersAreNotRegistered(log, "setWarrant");
        setWarrant(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->
                   getNamedBeanHandle(warrant->getDisplayName(), warrant));
    }

    /*public*/ void ExpressionWarrant::removeWarrant() {
        assertListenersAreNotRegistered(log, "setWarrant");
        if (_warrantHandle != nullptr) {
            ((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _warrantHandle = nullptr;
        }
    }

    /*public*/ NamedBeanHandle<Warrant*>* ExpressionWarrant::getWarrant() {
        return _warrantHandle;
    }

    /*public*/ void ExpressionWarrant::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ExpressionWarrant::getAddressing() {
        return _addressing;
    }

    /*public*/ void ExpressionWarrant::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/ QString ExpressionWarrant::getReference() {
        return _reference;
    }

    /*public*/ void ExpressionWarrant::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/ QString ExpressionWarrant::getLocalVariable() {
        return _localVariable;
    }

    /*public*/ void ExpressionWarrant::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _formula = formula;
        parseFormula();
    }

    /*public*/ QString ExpressionWarrant::getFormula() {
        return _formula;
    }

    /*private*/ void ExpressionWarrant::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*>  variables =  QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }

    /*public*/ void ExpressionWarrant::set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot) {
        _is_IsNot = is_IsNot;
    }

    /*public*/ Is_IsNot_Enum::VAL ExpressionWarrant::get_Is_IsNot() {
        return _is_IsNot;
    }

    /*public*/ void ExpressionWarrant::setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _stateAddressing = addressing;
        parseStateFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ExpressionWarrant::getStateAddressing() {
        return _stateAddressing;
    }

    /*public*/ void ExpressionWarrant::setBeanState(WarrantState::TYPE state) {
        _warrantState = state;
    }

    /*public*/ ExpressionWarrant::WarrantState::TYPE ExpressionWarrant::getBeanState() {
        return _warrantState;
    }

    /*public*/ void ExpressionWarrant::setStateReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _stateReference = reference;
    }

    /*public*/ QString ExpressionWarrant::getStateReference() {
        return _stateReference;
    }

    /*public*/ void ExpressionWarrant::setStateLocalVariable(/*@Nonnull*/ QString localVariable) {
        _stateLocalVariable = localVariable;
    }

    /*public*/ QString ExpressionWarrant::getStateLocalVariable() {
        return _stateLocalVariable;
    }

    /*public*/ void ExpressionWarrant::setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _stateFormula = formula;
        parseStateFormula();
    }

    /*public*/ QString ExpressionWarrant::getStateFormula() {
        return _stateFormula;
    }

    /*private*/ void ExpressionWarrant::parseStateFormula() /*throws ParserException*/ {
        if (_stateAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*>  variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _stateExpressionNode = parser->parseExpression(_stateFormula);
        } else {
            _stateExpressionNode = nullptr;
        }
    }

    //@Override
    /*public*/ void ExpressionWarrant::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<Warrant>::asPtr(evt->getOldValue())) {
                if (VPtr<Warrant>::asPtr(evt->getOldValue())->equals(getWarrant()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Warrant is in use by Warrant expression \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<Warrant>::asPtr(evt->getOldValue() )) {
                if (VPtr<Warrant>::asPtr(evt->getOldValue())->equals(getWarrant()->getBean())) {
                    removeWarrant();
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category ExpressionWarrant::getCategory() {
        return Category::ITEM;
    }

    /*private*/ QString ExpressionWarrant::getNewState() /*throws JmriException*/ {

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
    /*public*/ bool ExpressionWarrant::evaluate() /*throws JmriException*/ {
        Warrant* warrant;

//        System.out.format("ExpressionWarrant.execute: %s%n", getLongDescription());

        switch (_addressing) {
        case NamedBeanAddressing::Direct:
            warrant = _warrantHandle != nullptr ? _warrantHandle->getBean() : nullptr;
                break;

        case NamedBeanAddressing::Reference:
        {
                QString ref = ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _reference);
                warrant = (Warrant*)((WarrantManager*)InstanceManager::getDefault("WarrantManager"))
                        ->getNamedBean(ref)->self();
                break;
        }
        case NamedBeanAddressing::LocalVariable:
        {
            SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                warrant = (Warrant*)((WarrantManager*)InstanceManager::getDefault("WarrantManager"))
                        ->getNamedBean(TypeConversionUtil
                                       ::convertToString(symbolTable->getValue(_localVariable), false))->self();
                break;
        }
        case NamedBeanAddressing::Formula:
                warrant = _expressionNode != nullptr ?
                        (Warrant*)((WarrantManager*)InstanceManager::getDefault("WarrantManager"))
                            ->getNamedBean(TypeConversionUtil
                                           ::convertToString(_expressionNode->calculate(
                                                              getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " +NamedBeanAddressing::toString( _addressing));
        }

//        System.out.format("ExpressionWarrant.execute: warrant: %s%n", warrant);

        if (warrant == nullptr) {
//            log.warn("warrant is null");
            return false;
        }

        WarrantState::TYPE checkWarrantState;

        if (_stateAddressing == NamedBeanAddressing::Direct) {
            checkWarrantState = _warrantState;
        } else {
            checkWarrantState = WarrantState::valueOf(getNewState());
        }

        bool result;

        switch (checkWarrantState) {
        case WarrantState::RouteFree:
            result = warrant->routeIsFree();
                break;
        case WarrantState::RouteOccupied:
            result = warrant->routeIsOccupied();
                break;
        case WarrantState::RouteAllocated:
            result = warrant->isAllocated();
                break;
        case WarrantState::RouteSet:
            result = warrant->hasRouteSet();
                break;
        case WarrantState::TrainRunning:
            result = ! (warrant->getRunMode() == Warrant::MODE_NONE);
                break;
            default:
                throw new UnsupportedOperationException("checkWarrantState has unknown value: " + WarrantState::toString(checkWarrantState));
        }
        if (_is_IsNot == Is_IsNot_Enum::Is) {
            return result;
        } else {
            return !result;
        }
    }

    //@Override
    /*public*/ FemaleSocket* ExpressionWarrant::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/ int ExpressionWarrant::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/ QString ExpressionWarrant::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Warrant_Short");
    }

    //@Override
    /*public*/ QString ExpressionWarrant::getLongDescription(QLocale locale) {
        QString namedBean;
        QString state;

        switch (_addressing) {
        case NamedBeanAddressing::Direct:
        {
                QString warrantName;
                if (_warrantHandle != nullptr) {
                    warrantName = _warrantHandle->getBean()->getDisplayName();
                } else {
                    warrantName = tr(/*locale,*/ "");
                }
                namedBean = tr(/*locale,*/ "%1").arg(warrantName);
                break;
        }
        case NamedBeanAddressing::Reference:
                namedBean = tr(/*locale,*/ "by reference %1").arg(_reference);
                break;

        case NamedBeanAddressing::LocalVariable:
                namedBean = tr(/*locale,*/ "by local variable %1").arg( _localVariable);
                break;

        case NamedBeanAddressing::Formula:
                namedBean = tr(/*locale,*/ "by formulae %1").arg(_formula);
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        switch (_stateAddressing) {
        case NamedBeanAddressing::Direct:
                state = tr(/*locale,*/ "%1").arg(WarrantState::toString(_warrantState));
                break;

        case NamedBeanAddressing::Reference:
                state = tr(/*locale,*/ "by reference %1").arg(_stateReference);
                break;

        case NamedBeanAddressing::LocalVariable:
                state = tr(/*locale,*/ "by local variable %1").arg( _stateLocalVariable);
                break;

        case NamedBeanAddressing::Formula:
                state = tr(/*locale,*/ "by formulae %1").arg(_stateFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _stateAddressing state: " + NamedBeanAddressing::toString(_stateAddressing));
        }

        return tr(/*locale,*/ "Warrant %1 %2").arg(namedBean, state);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionWarrant::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionWarrant::registerListenersForThisClass() {
        if (!_listenersAreRegistered && (_warrantHandle != nullptr)) {
            _warrantHandle->getBean()->addPropertyChangeListener("KnownState", this);
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionWarrant::unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {
            _warrantHandle->getBean()->removePropertyChangeListener("KnownState", this);
            _listenersAreRegistered = false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionWarrant::propertyChange(PropertyChangeEvent* evt) {
    getConditionalNG()->execute();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionWarrant::disposeMe() {
    }

#if 0
    /*public*/ enum WarrantState {
        RouteFree(Bundle.getMessage("WarrantTypeRouteFree")),
        RouteOccupied(Bundle.getMessage("WarrantTypeOccupied")),
        RouteAllocated(Bundle.getMessage("WarrantTypeAllocated")),
        RouteSet(Bundle.getMessage("WarrantTypeRouteSet")),
        TrainRunning(Bundle.getMessage("WarrantTypeTrainRunning"));

        /*private*/ final String _text;

        /*private*/ WarrantState(String text) {
            this._text = text;
        }

        //@Override
        /*public*/ String toString() {
            return _text;
        }

    }
#endif
    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionWarrant::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
    log->debug(tr("getUsageReport :: ExpressionWarrant: bean = %1, report = %2").arg(cdl->getDisplayName(), report->at(0)->usageData));
            if (getWarrant() != nullptr && bean->equals(getWarrant()->getBean())) {
        report->append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* ExpressionWarrant::log = LoggerFactory::getLogger("ExpressionWarrant");
