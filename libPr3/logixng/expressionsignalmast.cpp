#include "expressionsignalmast.h"
#include "defaultsignalmastmanager.h"
#include "logixng/conditionalng.h"
#include "logixng/defaultdigitalexpressionmanager.h"
#include "instancemanager.h"
#include "recursivedescentparser.h"
#include "referenceutil.h"
#include "vptr.h"
#include "typeconversionutil.h"
#include "loggerfactory.h"

/**
 * Evaluates the state of a SignalMast.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
///*public*/ class ExpressionSignalMast extends AbstractDigitalExpression
//        implements PropertyChangeListener, VetoableChangeListener {



    /*public*/ ExpressionSignalMast::ExpressionSignalMast(QString sys, QString user, QObject* parent)
            /*throws BadUserNameException, BadSystemNameException*/
       : AbstractDigitalExpression(sys, user, parent){
        //super(sys, user);
    }

    //@Override
    /*public*/ Base* ExpressionSignalMast::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/ {
        DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == nullptr) sysName = manager->getAutoSystemName();
        ExpressionSignalMast* copy = new ExpressionSignalMast(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_signalMastHandle != nullptr) copy->setSignalMast(_signalMastHandle);
        copy->setAspect(_signalMastAspect);
        copy->setAddressing(_addressing);
        copy->setFormula(_formula);
        copy->setLocalVariable(_localVariable);
        copy->setReference(_reference);
        copy->setQueryAddressing(_queryAddressing);
        copy->setQueryType(_queryType);
        copy->setQueryFormula(_queryFormula);
        copy->setQueryLocalVariable(_queryLocalVariable);
        copy->setQueryReference(_queryReference);
        copy->setAspectAddressing(_aspectAddressing);
        copy->setAspectFormula(_aspectFormula);
        copy->setAspectLocalVariable(_aspectLocalVariable);
        copy->setAspectReference(_aspectReference);
        copy->setExampleSignalMast(_exampleSignalMastHandle);
        return manager->registerExpression(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /*public*/ void ExpressionSignalMast::setSignalMast(/*@Nonnull*/ QString signalMastName) {
        assertListenersAreNotRegistered(log, "setSignalMast");
        SignalMast* signalMast = (SignalMast*)((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signalMastName);
        if (signalMast != nullptr) {
            setSignalMast(signalMast);
        } else {
            removeSignalMast();
            log->error(tr("signalMast \"%1\" is not found").arg(signalMastName));
        }
    }

    /*public*/ void ExpressionSignalMast::setSignalMast(/*@Nonnull*/ NamedBeanHandle<SignalMast*>* handle) {
        assertListenersAreNotRegistered(log, "setSignalMast");
        _signalMastHandle = handle;
        ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/ void ExpressionSignalMast::setSignalMast(/*@Nonnull*/ SignalMast* signalMast) {
        assertListenersAreNotRegistered(log, "setSignalMast");
        setSignalMast(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(signalMast->getDisplayName(), signalMast));
    }

    /*public*/ void ExpressionSignalMast::removeSignalMast() {
        assertListenersAreNotRegistered(log, "setSignalMast");
        if (_signalMastHandle != nullptr) {
            ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _signalMastHandle = nullptr;
        }
    }

    /*public*/ NamedBeanHandle<SignalMast*>* ExpressionSignalMast::getSignalMast() {
        return _signalMastHandle;
    }

    /*public*/ void ExpressionSignalMast::setExampleSignalMast(/*@Nonnull*/ QString signalMastName) {
        assertListenersAreNotRegistered(log, "setExampleSignalMast");
        SignalMast* signalMast = ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signalMastName);
        if (signalMast != nullptr) {
            setExampleSignalMast(signalMast);
        } else {
            removeExampleSignalMast();
            log->error(tr("signalMast \"%1\" is not found").arg(signalMastName));
        }
    }

    /*public*/ void ExpressionSignalMast::setExampleSignalMast(/*@Nonnull*/ NamedBeanHandle<SignalMast*>* handle) {
        assertListenersAreNotRegistered(log, "setExampleSignalMast");
        _exampleSignalMastHandle = handle;
        ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/ void ExpressionSignalMast::setExampleSignalMast(/*@Nonnull*/ SignalMast* signalMast) {
        assertListenersAreNotRegistered(log, "setExampleSignalMast");
        setExampleSignalMast(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(signalMast->getDisplayName(), signalMast));
    }

    /*public*/ void ExpressionSignalMast::removeExampleSignalMast() {
        assertListenersAreNotRegistered(log, "removeExampleSignalMast");
        if (_exampleSignalMastHandle != nullptr) {
            ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _exampleSignalMastHandle = nullptr;
        }
    }

    /*public*/ NamedBeanHandle<SignalMast*>* ExpressionSignalMast::getExampleSignalMast() {
        return _exampleSignalMastHandle;
    }

    /*public*/ void ExpressionSignalMast::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ExpressionSignalMast::getAddressing() {
        return _addressing;
    }

    /*public*/ void ExpressionSignalMast::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/ QString ExpressionSignalMast::getReference() {
        return _reference;
    }

    /*public*/ void ExpressionSignalMast::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/ QString ExpressionSignalMast::getLocalVariable() {
        return _localVariable;
    }

    /*public*/ void ExpressionSignalMast::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _formula = formula;
        parseFormula();
    }

    /*public*/ QString ExpressionSignalMast::getFormula() {
        return _formula;
    }

    /*private*/ void ExpressionSignalMast::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }

    /*public*/ void ExpressionSignalMast::setQueryAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _queryAddressing = addressing;
        parseQueryFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ExpressionSignalMast::getQueryAddressing() {
        return _queryAddressing;
    }

    /*public*/ void ExpressionSignalMast::setQueryType(QueryType::TYPE queryType) {
        _queryType = queryType;
    }

    /*public*/ ExpressionSignalMast::QueryType::TYPE ExpressionSignalMast::getQueryType() {
        return _queryType;
    }

    /*public*/ void ExpressionSignalMast::setQueryReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _queryReference = reference;
    }

    /*public*/ QString ExpressionSignalMast::getQueryReference() {
        return _queryReference;
    }

    /*public*/ void ExpressionSignalMast::setQueryLocalVariable(/*@Nonnull*/ QString localVariable) {
        _queryLocalVariable = localVariable;
    }

    /*public*/ QString ExpressionSignalMast::getQueryLocalVariable() {
        return _queryLocalVariable;
    }

    /*public*/ void ExpressionSignalMast::setQueryFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _queryFormula = formula;
        parseQueryFormula();
    }

    /*public*/ QString ExpressionSignalMast::getQueryFormula() {
        return _queryFormula;
    }

    /*private*/ void ExpressionSignalMast::parseQueryFormula() /*throws ParserException*/ {
        if (_queryAddressing == NamedBeanAddressing::Formula) {
           QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _queryExpressionNode = parser->parseExpression(_queryFormula);
        } else {
            _queryExpressionNode = nullptr;
        }
    }

    /*public*/ void ExpressionSignalMast::setAspectAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _aspectAddressing = addressing;
        parseAspectFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ExpressionSignalMast::getAspectAddressing() {
        return _aspectAddressing;
    }

    /*public*/ void ExpressionSignalMast::setAspect(QString aspect) {
        if (aspect == "") _signalMastAspect = "";
        else _signalMastAspect = aspect;
    }

    /*public*/ QString ExpressionSignalMast::getAspect() {
        return _signalMastAspect;
    }

    /*public*/ void ExpressionSignalMast::setAspectReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _aspectReference = reference;
    }

    /*public*/ QString ExpressionSignalMast::getAspectReference() {
        return _aspectReference;
    }

    /*public*/ void ExpressionSignalMast::setAspectLocalVariable(/*@Nonnull*/ QString localVariable) {
        _aspectLocalVariable = localVariable;
    }

    /*public*/ QString ExpressionSignalMast::getAspectLocalVariable() {
        return _aspectLocalVariable;
    }

    /*public*/ void ExpressionSignalMast::setAspectFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _aspectFormula = formula;
        parseAspectFormula();
    }

    /*public*/ QString ExpressionSignalMast::getAspectFormula() {
        return _aspectFormula;
    }

    /*private*/ void ExpressionSignalMast::parseAspectFormula() /*throws ParserException*/ {
        if (_aspectAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _aspectExpressionNode = parser->parseExpression(_aspectFormula);
        } else {
            _aspectExpressionNode = nullptr;
        }
    }

    //@Override
    /*public*/ void ExpressionSignalMast::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<SignalMast>::asPtr(evt->getOldValue())) {
                if ((_signalMastHandle != nullptr)
                        && (VPtr<SignalMast>::asPtr(evt->getOldValue())->equals(_signalMastHandle->getBean()))) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("SignalMast is in use by SignalMast expression \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
                if ((_exampleSignalMastHandle != nullptr)
                        && (VPtr<SignalMast>::asPtr(evt->getOldValue())->equals(_exampleSignalMastHandle->getBean()))) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("SignalMast is in use by SignalMast expression \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<SignalMast>::asPtr(evt->getOldValue())) {
                if ((_signalMastHandle != nullptr)
                        && (VPtr<SignalMast>::asPtr(evt->getOldValue())->equals(_signalMastHandle->getBean()))) {
                    removeSignalMast();
                }
                if ((_exampleSignalMastHandle != nullptr)
                        && (VPtr<SignalMast>::asPtr(evt->getOldValue())->equals(_exampleSignalMastHandle->getBean()))) {
                    removeExampleSignalMast();
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category ExpressionSignalMast::getCategory() {
        return Category::ITEM;
    }

    /*private*/ QString ExpressionSignalMast::getNewAspect() /*throws JmriException*/ {

        switch (_aspectAddressing) {
        case NamedBeanAddressing::Direct:
                return _signalMastAspect;

            case NamedBeanAddressing::Reference:
                return ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _aspectReference);

            case NamedBeanAddressing::LocalVariable:
            {
            SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                return TypeConversionUtil
                        ::convertToString(symbolTable->getValue(_aspectLocalVariable), false);
            }
            case NamedBeanAddressing:: Formula:
                return _aspectExpressionNode != nullptr
                        ? TypeConversionUtil::convertToString(
                              _aspectExpressionNode->calculate(
                                  getConditionalNG()->getSymbolTable()), false)
                        : "";

            default:
                throw new IllegalArgumentException("invalid _aspectAddressing state: " + NamedBeanAddressing::toString(_aspectAddressing));
        }
    }

    /*private*/ ExpressionSignalMast::QueryType::TYPE ExpressionSignalMast::getQuery() /*throws JmriException*/ {

        QString oper = "";
        try {
            switch (_queryAddressing) {
            case NamedBeanAddressing::Direct:
                    return _queryType;

                case NamedBeanAddressing::Reference:
                    oper = ReferenceUtil::getReference(
                                getConditionalNG()->getSymbolTable(), _queryReference);
                    return QueryType::valueOf(oper);

                case NamedBeanAddressing::LocalVariable:
                {
                    SymbolTable* symbolTable =
                            getConditionalNG()->getSymbolTable();
                    oper = TypeConversionUtil
                            ::convertToString(symbolTable->getValue(_queryLocalVariable), false);
                    return QueryType::valueOf(oper);
                }
                case NamedBeanAddressing::Formula:
                    if (_aspectExpressionNode != nullptr) {
                        oper = TypeConversionUtil::convertToString(
                                    _queryExpressionNode->calculate(
                                        getConditionalNG()->getSymbolTable()), false);
                        return QueryType::valueOf(oper);
                    } else {
                        return QueryType::None;
                    }
                default:
                    throw new IllegalArgumentException("invalid _addressing state: " +NamedBeanAddressing::toString( _queryAddressing));
            }
        } catch (IllegalArgumentException* e) {
            throw new JmriException("Unknown query: "+oper, e);
        }
        return QueryType::None;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ExpressionSignalMast::evaluate() /*throws JmriException*/ {
        SignalMast* signalMast;

        switch (_addressing) {
        case NamedBeanAddressing::Direct:
            signalMast = _signalMastHandle != nullptr ? _signalMastHandle->getBean() : nullptr;
                break;

            case NamedBeanAddressing::Reference:
            {
                QString ref = ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _reference);
                signalMast = (SignalMast*)((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))
                        ->getNamedBean(ref)->self();
                break;
            }
            case NamedBeanAddressing::LocalVariable:
        {
            SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                signalMast = (SignalMast*)((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))
                        ->getNamedBean(TypeConversionUtil
                                      ::convertToString(symbolTable->getValue(_localVariable), false))->self();
                break;
}
            case NamedBeanAddressing::Formula:
                signalMast = _expressionNode != nullptr ?
                        (SignalMast*)((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))
                            ->getNamedBean(TypeConversionUtil
                                           ::convertToString(_expressionNode->calculate(
                                                              getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        if (signalMast == nullptr) {
//            log.error("signalMast is null");
            return false;
        }

        ExpressionSignalMast::QueryType::TYPE query = getQuery();

        bool result = false;

        switch (query) {
            case ExpressionSignalMast::QueryType::Aspect:
                if (signalMast->getAspect() != "") {
                    result = getNewAspect() ==(signalMast->getAspect());
                }
                break;
            case ExpressionSignalMast::QueryType::Lit:
            result = signalMast->getLit();
                break;
            case QueryType::NotLit:
            result = ! signalMast->getLit();
                break;
            case QueryType::Held:
            result = signalMast->getHeld();
                break;
            case QueryType::NotHeld:
            result = ! signalMast->getHeld();
                break;
        case QueryType::IsPermissiveSmlDisabled:
            result = signalMast->isPermissiveSmlDisabled();
                break;
        case QueryType::IsPermissiveSmlNotDisabled:
            result = ! signalMast->isPermissiveSmlDisabled();
                break;
            default:
                throw new RuntimeException("Unknown enum: "+ExpressionSignalMast::QueryType::toString(_queryType));
        }

        return result;
    }

    //@Override
    /*public*/ FemaleSocket* ExpressionSignalMast::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/ int ExpressionSignalMast::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/ QString ExpressionSignalMast::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "SignalMast");
    }

    //@Override
    /*public*/ QString ExpressionSignalMast::getLongDescription(QLocale locale) {
        QString namedBean;
        QString query;
        QString aspect;

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
            {
                QString sensorName;
                if (_signalMastHandle != nullptr) {
                    sensorName = _signalMastHandle->getBean()->getDisplayName();
                } else {
                    sensorName = tr(/*locale,*/ "BeanNotSelected");
                }
                namedBean = tr(/*locale,*/ "%1").arg(sensorName);
                break;
            }
            case NamedBeanAddressing::Reference:
                namedBean = tr(/*locale,*/ "by reference %1").arg(_reference);
                break;

            case NamedBeanAddressing::LocalVariable:
                namedBean = tr(/*locale,*/ "by local variable %1").arg(_localVariable);
                break;

            case NamedBeanAddressing::Formula:
                namedBean = tr(/*locale,*/ "by formula%1").arg(_formula);
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        switch (_queryAddressing) {
            case NamedBeanAddressing::Direct:
                query = tr(/*locale,*/ "%1").arg(QueryType::toString(_queryType));
                break;

            case NamedBeanAddressing::Reference:
                query = tr(/*locale,*/ "by reference %1").arg(_queryReference);
                break;

            case NamedBeanAddressing::LocalVariable:
                query = tr(/*locale,*/ "by local variable %1").arg(_queryLocalVariable);
                break;

            case NamedBeanAddressing::Formula:
                query = tr(/*locale,*/ "by formula%1").arg(_queryFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _queryAddressing state: " + NamedBeanAddressing::toString(_queryAddressing));
        }

        switch (_aspectAddressing) {
        case NamedBeanAddressing::Direct:
                aspect = tr(/*locale,*/ "%1").arg(_signalMastAspect);
                break;

            case NamedBeanAddressing::Reference:
                aspect = tr(/*locale,*/ "by reference %1").arg(_aspectReference);
                break;

            case NamedBeanAddressing::LocalVariable:
                aspect = tr(/*locale,*/ "by local variable %1").arg(_aspectLocalVariable);
                break;

            case NamedBeanAddressing::Formula:
                aspect = tr(/*locale,*/ "by formula%1").arg(_aspectFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _stateAddressing state: " + NamedBeanAddressing::toString(_aspectAddressing));
        }

        if (_queryAddressing == NamedBeanAddressing::Direct) {
            if (_queryType == QueryType::Aspect) {
                return tr(/*locale,*/ "SignalMast_LongAspect").arg(namedBean, aspect);
            } if (_queryType == QueryType::NotAspect) {
                return tr(/*locale,*/ "Signal mast %1 has not aspect %2").arg(namedBean, aspect);
            } else {
                return tr(/*locale,*/ "Signal mast %1 %2").arg(namedBean, query);
            }
        } else {
            return tr(/*locale,*/ "Signal mast %1 %2 with aspect %3").arg(namedBean, query, aspect);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionSignalMast::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionSignalMast::registerListenersForThisClass() {
        if (!_listenersAreRegistered && (_signalMastHandle != nullptr)) {

            switch (_queryType) {
                case QueryType::Aspect:
                case QueryType::NotAspect:
                _signalMastHandle->getBean()->addPropertyChangeListener("Aspect", this);
                    break;

                case QueryType::Lit:
                case QueryType::NotLit:
                _signalMastHandle->getBean()->addPropertyChangeListener("Lit", this);
                    break;

                case QueryType::Held:
                case QueryType::NotHeld:
                _signalMastHandle->getBean()->addPropertyChangeListener("Held", this);
                    break;

                case QueryType::IsPermissiveSmlDisabled:
                case QueryType::IsPermissiveSmlNotDisabled:
                    _signalMastHandle->getBean()->removePropertyChangeListener("PermissiveSmlDisabled", this);
                    break;

                default:
                    throw new RuntimeException("Unknown enum: "+QueryType::toString(_queryType));
            }
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionSignalMast::unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {

            switch (_queryType) {
                case QueryType::Aspect:
                case QueryType::NotAspect:
                _signalMastHandle->getBean()->removePropertyChangeListener("Aspect", this);
                    break;

                case QueryType::Lit:
                case QueryType::NotLit:
                _signalMastHandle->getBean()->removePropertyChangeListener("Lit", this);
                    break;

                case QueryType::Held:
                case QueryType::NotHeld:
                _signalMastHandle->getBean()->removePropertyChangeListener("Held", this);
                    break;

                case QueryType::IsPermissiveSmlDisabled:
                case QueryType::IsPermissiveSmlNotDisabled:
                _signalMastHandle->getBean()->removePropertyChangeListener("PermissiveSmlDisabled", this);
                    break;

                default:
                    throw new RuntimeException("Unknown enum: "+QueryType::toString(_queryType));
            }
            _listenersAreRegistered = false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionSignalMast::propertyChange(PropertyChangeEvent* evt) {
    getConditionalNG()->execute();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionSignalMast::disposeMe() {
    }



//    /*public*/ enum QueryType {
//        Aspect(tr("SignalMastQueryType_Aspect")),
//        NotAspect(tr("SignalMastQueryType_NotAspect")),
//        Lit(tr("SignalMastQueryType_Lit")),
//        NotLit(tr("SignalMastQueryType_NotLit")),
//        Held(tr("SignalMastQueryType_Held")),
//        NotHeld(tr("SignalMastQueryType_NotHeld")),
//        IsPermissiveSmlDisabled(tr("SignalMastQueryType_IsPermissiveSmlDisabled")),
//        IsPermissiveSmlNotDisabled(tr("SignalMastQueryType_IsPermissiveSmlNotDisabled"));

//        /*private*/ final String _text;

//        /*private*/ QueryType(String text) {
//            this._text = text;
//        }

//        //@Override
//        /*public*/ String toString() {
//            return _text;
//        }

//    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionSignalMast::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
        log->debug(tr("getUsageReport :: ExpressionSignalMast: bean = %1, report = %2").arg(cdl->getDisplayName(), report->at(0)->usageData));
                if (getSignalMast() != nullptr && bean->equals(getSignalMast()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription(QLocale())));
        }
        if (getExampleSignalMast() != nullptr && bean->equals(getExampleSignalMast()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* ExpressionSignalMast::log = LoggerFactory::getLogger("ExpressionSignalMast");
