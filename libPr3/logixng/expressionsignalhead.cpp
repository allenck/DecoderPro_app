#include "expressionsignalhead.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalexpressionmanager.h"
#include "referenceutil.h"
#include "recursivedescentparser.h"
#include "abstractsignalheadmanager.h"
#include "vptr.h"
#include "typeconversionutil.h"
#include "defaultconditionalng.h"

/**
 * Evaluates the state of a SignalHead.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
///*public*/  class ExpressionSignalHead extends AbstractDigitalExpression
//        implements PropertyChangeListener, VetoableChangeListener {


    /*public*/  ExpressionSignalHead::ExpressionSignalHead(QString sys, QString user, QObject* parent)
     : AbstractDigitalExpression(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
     setObjectName("ExpressionSignalHead");
    }

    //@Override
    /*public*/  Base* ExpressionSignalHead::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/ {
        DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ExpressionSignalHead* copy = new ExpressionSignalHead(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_signalHeadHandle != nullptr) copy->setSignalHead(_signalHeadHandle);
        copy->setAppearance(_signalHeadAppearance);
        copy->setAddressing(_addressing);
        copy->setFormula(_formula);
        copy->setLocalVariable(_localVariable);
        copy->setReference(_reference);
        copy->setQueryAddressing(_queryAddressing);
        copy->setQueryType(_queryType);
        copy->setQueryFormula(_queryFormula);
        copy->setQueryLocalVariable(_queryLocalVariable);
        copy->setQueryReference(_queryReference);
        copy->setAppearanceAddressing(_appearanceAddressing);
        copy->setAppearanceFormula(_appearanceFormula);
        copy->setAppearanceLocalVariable(_appearanceLocalVariable);
        copy->setAppearanceReference(_appearanceReference);
        copy->setExampleSignalHead(_exampleSignalHeadHandle);
        return manager->registerExpression(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /*public*/  void ExpressionSignalHead::setSignalHead(/*@Nonnull*/ QString signalHeadName) {
        assertListenersAreNotRegistered(log, "setSignalHead");
        SignalHead* signalHead = ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHeadName);
        if (signalHead != nullptr) {
            setSignalHead(signalHead);
        } else {
            removeSignalHead();
            log->error(tr("signalHead \"%1\" is not found").arg(signalHeadName));
        }
    }

    /*public*/  void ExpressionSignalHead::setSignalHead(/*@Nonnull*/ NamedBeanHandle<SignalHead*>* handle) {
        assertListenersAreNotRegistered(log, "setSignalHead");
        _signalHeadHandle = handle;
        ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/  void ExpressionSignalHead::setSignalHead(/*@Nonnull*/ SignalHead* signalHead) {
        assertListenersAreNotRegistered(log, "setSignalHead");
        setSignalHead(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(signalHead->getDisplayName(), signalHead));
    }

    /*public*/  void ExpressionSignalHead::removeSignalHead() {
        assertListenersAreNotRegistered(log, "setSignalHead");
        if (_signalHeadHandle != nullptr) {
            ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _signalHeadHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<SignalHead*>* ExpressionSignalHead::getSignalHead() {
        return _signalHeadHandle;
    }

    /*public*/  void ExpressionSignalHead::setExampleSignalHead(/*@Nonnull*/ QString signalHeadName) {
        assertListenersAreNotRegistered(log, "setExampleSignalHead");
        SignalHead* signalHead = ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHeadName);
        if (signalHead != nullptr) {
            setExampleSignalHead(signalHead);
        } else {
            removeExampleSignalHead();
            log->error(tr("signalHead \"%1\" is not found").arg(signalHeadName));
        }
    }

    /*public*/  void ExpressionSignalHead::setExampleSignalHead(/*@Nonnull*/ NamedBeanHandle<SignalHead*>* handle) {
        assertListenersAreNotRegistered(log, "setExampleSignalHead");
        _exampleSignalHeadHandle = handle;
        ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/  void ExpressionSignalHead::setExampleSignalHead(/*@Nonnull*/ SignalHead* signalHead) {
        assertListenersAreNotRegistered(log, "setExampleSignalHead");
        setExampleSignalHead(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(signalHead->getDisplayName(), signalHead));
    }

    /*public*/  void ExpressionSignalHead::removeExampleSignalHead() {
        assertListenersAreNotRegistered(log, "removeExampleSignalHead");
        if (_exampleSignalHeadHandle != nullptr) {
            ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _exampleSignalHeadHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<SignalHead*>* ExpressionSignalHead::getExampleSignalHead() {
        return _exampleSignalHeadHandle;
    }

    /*public*/  void ExpressionSignalHead::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ExpressionSignalHead::getAddressing() {
        return _addressing;
    }

    /*public*/  void ExpressionSignalHead::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/  QString ExpressionSignalHead::getReference() {
        return _reference;
    }

    /*public*/  void ExpressionSignalHead::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/  QString ExpressionSignalHead::getLocalVariable() {
        return _localVariable;
    }

    /*public*/  void ExpressionSignalHead::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _formula = formula;
        parseFormula();
    }

    /*public*/  QString ExpressionSignalHead::getFormula() {
        return _formula;
    }

    /*private*/ void ExpressionSignalHead::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }

    /*public*/  void ExpressionSignalHead::setQueryAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _queryAddressing = addressing;
        parseQueryFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ExpressionSignalHead::getQueryAddressing() {
        return _queryAddressing;
    }

    /*public*/  void ExpressionSignalHead::setQueryType(QueryType::TYPE queryType) {
        _queryType = queryType;
    }

    /*public*/  ExpressionSignalHead::QueryType::TYPE ExpressionSignalHead::getQueryType() {
        return _queryType;
    }

    /*public*/  void ExpressionSignalHead::setQueryReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _queryReference = reference;
    }

    /*public*/  QString ExpressionSignalHead::getQueryReference() {
        return _queryReference;
    }

    /*public*/  void ExpressionSignalHead::setQueryLocalVariable(/*@Nonnull*/ QString localVariable) {
        _queryLocalVariable = localVariable;
    }

    /*public*/  QString ExpressionSignalHead::getQueryLocalVariable() {
        return _queryLocalVariable;
    }

    /*public*/  void ExpressionSignalHead::setQueryFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _queryFormula = formula;
        parseQueryFormula();
    }

    /*public*/  QString ExpressionSignalHead::getQueryFormula() {
        return _queryFormula;
    }

    /*private*/ void ExpressionSignalHead::parseQueryFormula() /*throws ParserException*/ {
        if (_queryAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _queryExpressionNode = parser->parseExpression(_queryFormula);
        } else {
            _queryExpressionNode = nullptr;
        }
    }

    /*public*/  void ExpressionSignalHead::setAppearanceAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _appearanceAddressing = addressing;
        parseAppearanceFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ExpressionSignalHead::getAppearanceAddressing() {
        return _appearanceAddressing;
    }

    /*public*/  void ExpressionSignalHead::setAppearance(int appearance) {
        _signalHeadAppearance = appearance;
    }

    /*public*/  int ExpressionSignalHead::getAppearance() {
        return _signalHeadAppearance;
    }

    /*public*/  void ExpressionSignalHead::setAppearanceReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _appearanceReference = reference;
    }

    /*public*/  QString ExpressionSignalHead::getAppearanceReference() {
        return _appearanceReference;
    }

    /*public*/  void ExpressionSignalHead::setAppearanceLocalVariable(/*@Nonnull*/ QString localVariable) {
        _appearanceLocalVariable = localVariable;
    }

    /*public*/  QString ExpressionSignalHead::getAppearanceLocalVariable() {
        return _appearanceLocalVariable;
    }

    /*public*/  void ExpressionSignalHead::setAppearanceFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _appearanceFormula = formula;
        parseAppearanceFormula();
    }

    /*public*/  QString ExpressionSignalHead::getAppearanceFormula() {
        return _appearanceFormula;
    }

    /*private*/ void ExpressionSignalHead::parseAppearanceFormula() /*throws ParserException*/ {
        if (_appearanceAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _appearanceExpressionNode = parser->parseExpression(_appearanceFormula);
        } else {
            _appearanceExpressionNode = nullptr;
        }
    }

    //@Override
    /*public*/  void ExpressionSignalHead::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<SignalHead>::asPtr(evt->getOldValue())) {
                if ((_signalHeadHandle != nullptr)
                        && (VPtr<SignalHead>::asPtr(evt->getOldValue())->equals(_signalHeadHandle->getBean()))) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("SignalHead is in use by SignalHead expression \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
                if ((_exampleSignalHeadHandle != nullptr)
                        && (VPtr<SignalHead>::asPtr(evt->getOldValue())->equals(_exampleSignalHeadHandle->getBean()))) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("SignalHead is in use by SignalHead expression \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<SignalHead>::asPtr(evt->getOldValue())) {
                if ((_signalHeadHandle != nullptr)
                        && (VPtr<SignalHead>::asPtr(evt->getOldValue())->equals(_signalHeadHandle->getBean()))) {
                    removeSignalHead();
                }
                if ((_exampleSignalHeadHandle != nullptr)
                        && (VPtr<SignalHead>::asPtr(evt->getOldValue())->equals(_exampleSignalHeadHandle->getBean()))) {
                    removeExampleSignalHead();
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category ExpressionSignalHead::getCategory() {
        return Category::ITEM;
    }

    /*private*/ int ExpressionSignalHead::getAppearanceFromName(QString name) {
        if (_signalHeadHandle == nullptr) throw new UnsupportedOperationException("_signalHeadHandle is null");

        SignalHead* sh = _signalHeadHandle->getBean();
        QVector<QString> keys = sh->getValidStateKeys();
        for (int i=0; i < keys.length(); i++) {
            if (name ==(keys[i])) return sh->getValidStates()[i];
        }

        throw new IllegalArgumentException("Appearance "+name+" is not valid for signal head "+sh->getSystemName());
    }

    /*private*/ int ExpressionSignalHead::getNewAppearance() /*throws JmriException*/ {

        switch (_appearanceAddressing) {
            case NamedBeanAddressing::Direct:
                return _signalHeadAppearance;

            case NamedBeanAddressing::Reference:
                return getAppearanceFromName(ReferenceUtil::getReference(
                        getConditionalNG()->getSymbolTable(), _appearanceReference));

            case NamedBeanAddressing::LocalVariable:
            {
                SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                return getAppearanceFromName(TypeConversionUtil
                        ::convertToString(symbolTable->getValue(_appearanceLocalVariable), false));
            }
            case NamedBeanAddressing::Formula:
                return _appearanceExpressionNode != nullptr
                        ? getAppearanceFromName(TypeConversionUtil::convertToString(
                                _appearanceExpressionNode->calculate(
                                        getConditionalNG()->getSymbolTable()), false))
                        : -1;

            default:
                throw new IllegalArgumentException("invalid _aspectAddressing state: " + NamedBeanAddressing::toString(_appearanceAddressing));
        }
    }

    /*private*/ ExpressionSignalHead::QueryType::TYPE ExpressionSignalHead::getQuery() /*throws JmriException*/ {

        QString oper = "";
        try {
            switch (_queryAddressing) {
                case NamedBeanAddressing::Direct:
                    return _queryType;

                case NamedBeanAddressing::Reference:
                    oper = ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _queryReference);
                    return ExpressionSignalHead::QueryType::valueOf(oper);

                case NamedBeanAddressing::LocalVariable:
                {
                    SymbolTable* symbolTable =
                            getConditionalNG()->getSymbolTable();
                    oper = TypeConversionUtil
                            ::convertToString(symbolTable->getValue(_queryLocalVariable), false);
                    return QueryType::valueOf(oper);
                }
                case NamedBeanAddressing::Formula:
                    if (_appearanceExpressionNode != nullptr) {
                        oper = TypeConversionUtil::convertToString(
                                _queryExpressionNode->calculate(
                                        getConditionalNG()->getSymbolTable()), false);
                        return ExpressionSignalHead::QueryType::valueOf(oper);
                    } else {
                        return QueryType::Appearance;
                    }
                default:
                    throw new IllegalArgumentException(QString("invalid _addressing state: ") + NamedBeanAddressing::toString(_queryAddressing));
            }
        } catch (IllegalArgumentException* e) {
            throw new JmriException("Unknown query: "+oper, e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ExpressionSignalHead::evaluate() /*throws JmriException*/ {
        SignalHead* signalHead;

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
                signalHead = _signalHeadHandle != nullptr ? _signalHeadHandle->getBean() : nullptr;
                break;

            case NamedBeanAddressing::Reference:
            {
                QString ref = ReferenceUtil::getReference(
                        getConditionalNG()->getSymbolTable(), _reference);
                signalHead = (SignalHead*)((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))
                        ->AbstractManager::getNamedBean(ref)->self();
                break;
            }
            case NamedBeanAddressing::LocalVariable:
            {
                SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                signalHead = (SignalHead*)((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))
                        ->AbstractManager::getNamedBean(TypeConversionUtil
                                ::convertToString(symbolTable->getValue(_localVariable), false))->self();
                break;
            }
            case NamedBeanAddressing::Formula:
                signalHead = _expressionNode != nullptr ?
                        (SignalHead*)((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))
                                ->AbstractManager::getNamedBean(TypeConversionUtil
                                        ::convertToString(_expressionNode->calculate(
                                                getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        if (signalHead == nullptr) {
//            log.error("signalHead is null");
            return false;
        }

        QueryType::TYPE query = getQuery();

        bool result = false;
        int queryAppearance;

        switch (query) {
            case QueryType::Appearance:
                queryAppearance = getNewAppearance();
                if (queryAppearance != -1) {
                    result = signalHead->getAppearance() == queryAppearance;
                }
                break;
            case QueryType::NotAppearance:
                queryAppearance = getNewAppearance();
                if (queryAppearance != -1) {
                    result = ! (signalHead->getAppearance() == queryAppearance);
                }
                break;
            case QueryType::Lit:
                result = signalHead->getLit();
                break;
            case QueryType::NotLit:
                result = ! signalHead->getLit();
                break;
            case QueryType::Held:
                result = signalHead->getHeld();
                break;
            case QueryType::NotHeld:
                result = ! signalHead->getHeld();
                break;
            default:
                throw new RuntimeException("Unknown enum: "+QueryType::toString(_queryType));
        }

        return result;
    }

    //@Override
    /*public*/  FemaleSocket* ExpressionSignalHead::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int ExpressionSignalHead::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString ExpressionSignalHead::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "SignalHead_Short");
    }

    //@Override
    /*public*/  QString ExpressionSignalHead::getLongDescription(QLocale locale) {
        QString namedBean;
        QString query;
        QString appearance;

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
            {
                QString sensorName;
                if (_signalHeadHandle != nullptr) {
                    sensorName = _signalHeadHandle->getBean()->getDisplayName();
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
                namedBean = tr(/*locale,*/  "by formula %1").arg(_formula);
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
                query = tr(/*locale,*/ "by formula %1").arg(_queryFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _queryAddressing state: " + NamedBeanAddressing::toString(_queryAddressing));
        }

        switch (_appearanceAddressing) {
            case NamedBeanAddressing::Direct:
            {
                QString a = "";
                if ((_signalHeadHandle != nullptr) && (_signalHeadHandle->getBean() != nullptr)) {
                    a = _signalHeadHandle->getBean()->getAppearanceName(_signalHeadAppearance);
                }
                appearance = tr(/*locale,*/ "%1").arg(a);
                break;
            }
            case NamedBeanAddressing::Reference:
                appearance = tr(/*locale,*/ "by reference %1").arg(_appearanceReference);
                break;

            case NamedBeanAddressing::LocalVariable:
                appearance = tr(/*locale,*/ "by local variable %1").arg(_appearanceLocalVariable);
                break;

            case NamedBeanAddressing::Formula:
                appearance = tr(/*locale,*/ "by formula %1").arg(_appearanceFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _stateAddressing state: " + NamedBeanAddressing::toString(_appearanceAddressing));
        }

        if (_queryAddressing == NamedBeanAddressing::Direct) {
            if (_queryType == QueryType::Appearance) {
                return tr(/*locale,*/ "Signal head %1 has appearance %2").arg(namedBean, appearance);
            } else if (_queryType == QueryType::NotAppearance) {
                return tr(/*locale,*/ "Signal head %1 has not appearance %2").arg(namedBean, appearance);
            } else {
                return tr(/*locale,*/ "Signal head %1 %2").arg(namedBean, query);
            }
        } else {
            return tr(/*locale,*/ "Signal head %1 %2 with appearance %3").arg(namedBean, query, appearance);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionSignalHead::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionSignalHead::registerListenersForThisClass() {
        if (!_listenersAreRegistered && (_signalHeadHandle != nullptr)) {

            switch (_queryType) {
                case QueryType::Appearance:
                case QueryType::NotAppearance:
                    _signalHeadHandle->getBean()->addPropertyChangeListener("Appearance", this);
                    break;

                case QueryType::Lit:
                case QueryType::NotLit:
                    _signalHeadHandle->getBean()->addPropertyChangeListener("Lit", this);
                    break;

                case QueryType::Held:
                case QueryType::NotHeld:
                    _signalHeadHandle->getBean()->addPropertyChangeListener("Held", this);
                    break;

                default:
                    throw new RuntimeException("Unknown enum: "+QueryType::toString(_queryType));
            }
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionSignalHead::unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {

            switch (_queryType) {
                case QueryType::Appearance:
                case QueryType::NotAppearance:
                    _signalHeadHandle->getBean()->removePropertyChangeListener("Appearance", this);
                    break;

                case QueryType::Lit:
                case QueryType::NotLit:
                    _signalHeadHandle->getBean()->removePropertyChangeListener("Lit", this);
                    break;

                case QueryType::Held:
                case QueryType::NotHeld:
                    _signalHeadHandle->getBean()->removePropertyChangeListener("Held", this);
                    break;

                default:
                    throw new RuntimeException("Unknown enum: "+QueryType::toString(_queryType));
            }
            _listenersAreRegistered = false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionSignalHead::propertyChange(PropertyChangeEvent* evt) {
        getConditionalNG()->execute();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionSignalHead::disposeMe(){
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionSignalHead::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
        log->debug(tr("getUsageReport :: ExpressionSignalHead: bean = %1, report = %2").arg(cdl->getDisplayName()).arg(report->size()));
        if (getSignalHead() != nullptr && bean->equals(getSignalHead()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription(QLocale())));
        }
        if (getExampleSignalHead() != nullptr && bean->equals(getExampleSignalHead()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* ExpressionSignalHead::log = LoggerFactory::getLogger("ExpressionSignalHead");

