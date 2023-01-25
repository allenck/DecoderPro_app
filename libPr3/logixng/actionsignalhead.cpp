#include "actionsignalhead.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalactionmanager.h"
#include "abstractsignalheadmanager.h"
#include "recursivedescentparser.h"
#include "defaultconditionalng.h"
#include "vptr.h"
#include "referenceutil.h"
#include "typeconversionutil.h"

/**
 * Evaluates the state of a SignalHead.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
///*public*/  class ActionSignalHead extends AbstractDigitalAction
//        implements VetoableChangeListener {



    /*public*/  ActionSignalHead::ActionSignalHead(QString sys, QString user, QObject *parent) : AbstractDigitalAction(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException */{
        //super(sys, user);
     setObjectName("ActionSignalHead");
    }

    //@Override
    /*public*/  Base* ActionSignalHead::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/ {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ActionSignalHead* copy = new ActionSignalHead(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_signalHeadHandle != nullptr) copy->setSignalHead(_signalHeadHandle);
        copy->setAppearance(_signalHeadAppearance);
        copy->setAddressing(_addressing);
        copy->setFormula(_formula);
        copy->setLocalVariable(_localVariable);
        copy->setReference(_reference);
        copy->setOperationAddressing(_operationAddressing);
        copy->setOperationType(_operationType);
        copy->setOperationFormula(_operationFormula);
        copy->setOperationLocalVariable(_operationLocalVariable);
        copy->setOperationReference(_operationReference);
        copy->setAppearanceAddressing(_appearanceAddressing);
        copy->setAppearanceFormula(_appearanceFormula);
        copy->setAppearanceLocalVariable(_appearanceLocalVariable);
        copy->setAppearanceReference(_appearanceReference);
        copy->setExampleSignalHead(_exampleSignalHeadHandle);
        return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /*public*/  void ActionSignalHead::setSignalHead(/*@Nonnull*/ QString signalHeadName) {
    if(signalHeadName.isEmpty()) throw new NullPointerException("required SignalHean name is null");
        assertListenersAreNotRegistered(log, "setSignalHead");
        SignalHead* signalHead = ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHeadName);
        if (signalHead != nullptr) {
            setSignalHead(signalHead);
        } else {
            removeSignalHead();
            log->warn(tr("signalHead \"%1\" is not found").arg(signalHeadName));
        }
    }

    /*public*/  void ActionSignalHead::setSignalHead(/*@Nonnull*/ NamedBeanHandle<SignalHead*>* handle) {
        assertListenersAreNotRegistered(log, "setSignalHead");
        _signalHeadHandle = handle;
        ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/  void ActionSignalHead::setSignalHead(/*@Nonnull*/ SignalHead *signalHead) {
        assertListenersAreNotRegistered(log, "setSignalHead");
        setSignalHead(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(signalHead->getDisplayName(), signalHead));
    }

    /*public*/  void ActionSignalHead::removeSignalHead() {
        assertListenersAreNotRegistered(log, "setSignalHead");
        if (_signalHeadHandle != nullptr) {
            ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _signalHeadHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<SignalHead*>* ActionSignalHead::getSignalHead() {
        return _signalHeadHandle;
    }

    /*public*/  void ActionSignalHead::setExampleSignalHead(/*@Nonnull*/ QString signalHeadName) {
 if(signalHeadName.isEmpty()) throw new NullPointerException("required SignalHean name is null");
        assertListenersAreNotRegistered(log, "setExampleSignalHead");
        SignalHead* signalHead = ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHeadName);
        if (signalHead != nullptr) {
            setExampleSignalHead(signalHead);
        } else {
            removeExampleSignalHead();
            log->warn(tr("signalHead \"%1\" is not found").arg(signalHeadName));
        }
    }

    /*public*/  void ActionSignalHead::setExampleSignalHead(/*@Nonnull*/ NamedBeanHandle<SignalHead*>* handle) {
        assertListenersAreNotRegistered(log, "setExampleSignalHead");
        _exampleSignalHeadHandle = handle;
        ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/  void ActionSignalHead::setExampleSignalHead(/*@Nonnull*/ SignalHead* signalHead) {
        assertListenersAreNotRegistered(log, "setExampleSignalHead");
        setExampleSignalHead(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(signalHead->getDisplayName(), signalHead));
    }

    /*public*/  void ActionSignalHead::removeExampleSignalHead() {
        assertListenersAreNotRegistered(log, "removeExampleSignalHead");
        if (_exampleSignalHeadHandle != nullptr) {
            ((AbstractSignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _exampleSignalHeadHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<SignalHead*>* ActionSignalHead::getExampleSignalHead() {
        return _exampleSignalHeadHandle;
    }

    /*public*/  void ActionSignalHead::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ActionSignalHead::getAddressing() {
        return _addressing;
    }

    /*public*/  void ActionSignalHead::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/  QString ActionSignalHead::getReference() {
        return _reference;
    }

    /*public*/  void ActionSignalHead::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/  QString ActionSignalHead::getLocalVariable() {
        return _localVariable;
    }

    /*public*/  void ActionSignalHead::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _formula = formula;
        parseFormula();
    }

    /*public*/  QString ActionSignalHead::getFormula() {
        return _formula;
    }

    /*private*/ void ActionSignalHead::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }

    /*public*/  void ActionSignalHead::setOperationAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _operationAddressing = addressing;
        parseOperationFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ActionSignalHead::getOperationAddressing() {
        return _operationAddressing;
    }

    /*public*/  void ActionSignalHead::setOperationType(OperationType::TYPE operationType) {
        _operationType = operationType;
    }

    /*public*/  ActionSignalHead::OperationType::TYPE ActionSignalHead::getOperationType() {
        return _operationType;
    }

    /*public*/  void ActionSignalHead::setOperationReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _operationReference = reference;
    }

    /*public*/  QString ActionSignalHead::getOperationReference() {
        return _operationReference;
    }

    /*public*/  void ActionSignalHead::setOperationLocalVariable(/*@Nonnull*/ QString localVariable) {
        _operationLocalVariable = localVariable;
    }

    /*public*/  QString ActionSignalHead::getOperationLocalVariable() {
        return _operationLocalVariable;
    }

    /*public*/  void ActionSignalHead::setOperationFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _operationFormula = formula;
        parseOperationFormula();
    }

    /*public*/  QString ActionSignalHead::getOperationFormula() {
        return _operationFormula;
    }

    /*private*/ void ActionSignalHead::parseOperationFormula() /*throws ParserException*/ {
        if (_operationAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _operationExpressionNode = parser->parseExpression(_operationFormula);
        } else {
            _operationExpressionNode = nullptr;
        }
    }

    /*public*/  void ActionSignalHead::setAppearanceAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _appearanceAddressing = addressing;
        parseAppearanceFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ActionSignalHead::getAppearanceAddressing() {
        return _appearanceAddressing;
    }

    /*public*/  void ActionSignalHead::setAppearance(int appearance) {
        _signalHeadAppearance = appearance;
    }

    /*public*/  int ActionSignalHead::getAppearance() {
        return _signalHeadAppearance;
    }

    /*public*/  void ActionSignalHead::setAppearanceReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _appearanceReference = reference;
    }

    /*public*/  QString ActionSignalHead::getAppearanceReference() {
        return _appearanceReference;
    }

    /*public*/  void ActionSignalHead::setAppearanceLocalVariable(/*@Nonnull*/ QString localVariable) {
        _appearanceLocalVariable = localVariable;
    }

    /*public*/  QString ActionSignalHead::getAppearanceLocalVariable() {
        return _appearanceLocalVariable;
    }

    /*public*/  void ActionSignalHead::setAppearanceFormula(/*@Nonnull*/ QString formula)/* throws ParserException*/ {
        _appearanceFormula = formula;
        parseAppearanceFormula();
    }

    /*public*/  QString ActionSignalHead::getAppearanceFormula() {
        return _appearanceFormula;
    }

    /*private*/ void ActionSignalHead::parseAppearanceFormula() /*throws ParserException*/ {
        if (_appearanceAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _appearanceExpressionNode = parser->parseExpression(_appearanceFormula);
        } else {
            _appearanceExpressionNode = nullptr;
        }
    }

    //@Override
    /*public*/  void ActionSignalHead::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<SignalHead>::asPtr(evt->getOldValue())) {
                if ((_signalHeadHandle != nullptr)
                        && (VPtr<SignalHead>::asPtr(evt->getOldValue())->equals(_signalHeadHandle->getBean()))) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("SignalHead is in use by SignalHead action \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
                if ((_exampleSignalHeadHandle != nullptr)
                        && (VPtr<SignalHead>::asPtr(evt->getOldValue())->equals(_exampleSignalHeadHandle->getBean()))) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("SignalHead is in use by SignalHead action \"%1\"").arg(getDisplayName()), e); // NOI18N
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
    /*public*/  Category ActionSignalHead::getCategory() {
        return Category::ITEM;
    }

    /*private*/ int ActionSignalHead::getAppearanceFromName(QString name) {
        if (_signalHeadHandle == nullptr) throw new UnsupportedOperationException("_signalHeadHandle is null");

        SignalHead* sh = _signalHeadHandle->getBean();
        QVector<QString> keys = sh->getValidStateKeys();
        for (int i=0; i < keys.length(); i++) {
            if (name == (keys[i])) return sh->getValidStates()[i];
        }

        throw new IllegalArgumentException("Appearance "+name+" is not valid for signal head "+sh->getSystemName());
    }

    /*private*/ int ActionSignalHead::getNewAppearance(ConditionalNG* conditionalNG) /*throws JmriException*/ {

        switch (_appearanceAddressing) {
            case NamedBeanAddressing::Direct:
                return _signalHeadAppearance;

            case NamedBeanAddressing::Reference:
                return getAppearanceFromName(ReferenceUtil::getReference(
                        conditionalNG->getSymbolTable(), _appearanceReference));

            case NamedBeanAddressing::LocalVariable:
            {
                SymbolTable* symbolTable = conditionalNG->getSymbolTable();
                return getAppearanceFromName(TypeConversionUtil
                        ::convertToString(symbolTable->getValue(_appearanceLocalVariable), false));
            }
            case NamedBeanAddressing::Formula:
                return _appearanceExpressionNode != nullptr
                        ? getAppearanceFromName(TypeConversionUtil::convertToString(
                                _appearanceExpressionNode->calculate(
                                        conditionalNG->getSymbolTable()), false))
                        : -1;

            default:
                throw new IllegalArgumentException("invalid _aspectAddressing state: " + NamedBeanAddressing::toString(_appearanceAddressing));
        }
    }

    /*private*/ ActionSignalHead::OperationType::TYPE ActionSignalHead::getOperation() /*throws JmriException*/ {

        QString oper = "";
        try {
            switch (_operationAddressing) {
                case NamedBeanAddressing::Direct:
                    return _operationType;

                case NamedBeanAddressing::Reference:
                    oper = ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _operationReference);
                    return OperationType::valueOf(oper);

                case NamedBeanAddressing::LocalVariable:
                {
                    SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                    oper = TypeConversionUtil
                            ::convertToString(symbolTable->getValue(_operationLocalVariable), false);
                    return OperationType::valueOf(oper);
                }
                case NamedBeanAddressing::Formula:
                    if (_appearanceExpressionNode != nullptr) {
                        oper = TypeConversionUtil::convertToString(
                                _operationExpressionNode->calculate(
                                        getConditionalNG()->getSymbolTable()), false);
                        return OperationType::valueOf(oper);
                    } else {
                        return OperationType::Appearance;
                    }
                default:
                    throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_operationAddressing));
            }
        } catch (IllegalArgumentException* e) {
            throw new JmriException("Unknown operation: "+oper, e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionSignalHead::execute() /*throws JmriException*/ {
        SignalHead* signalHead;

//        System.out.format("ActionSignalHead.execute: %s%n", getLongDescription());

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
                throw new IllegalArgumentException("invalid _addressing state: " +NamedBeanAddressing::toString( _addressing));
        }

//        System.out.format("ActionSignalHead.execute: sensor: %s%n", sensor);

        if (signalHead == nullptr) {
//            log.warn("signalHead is null");
            return;
        }


        ActionSignalHead::OperationType::TYPE operation = getOperation();

        /*final*/ ConditionalNG* conditionalNG = getConditionalNG();

#if 0

        AtomicReference<JmriException> ref = new AtomicReference<>();
        jmri.util.ThreadingUtil.runOnLayoutWithJmriException(() -> {
            try {
                switch (operation) {
                    case Appearance:
                        int newAppearance = getNewAppearance(conditionalNG);
                        if (newAppearance != -1) {
                            signalHead->setAppearance(newAppearance);
                        }
                        break;
                    case Lit:
                        signalHead->setLit(true);
                        break;
                    case NotLit:
                        signalHead->setLit(false);
                        break;
                    case Held:
                        signalHead->setHeld(true);
                        break;
                    case NotHeld:
                        signalHead->setHeld(false);
                        break;
        //            case PermissiveSmlDisabled:
        //                signalHead->setPermissiveSmlDisabled(true);
        //                break;
        //            case PermissiveSmlNotDisabled:
        //                signalHead->setPermissiveSmlDisabled(false);
        //                break;
                    default:
                        throw new JmriException("Unknown enum: "+_operationType.name());
                }
            } catch (JmriException e) {
                ref->set(e);
            }
        });
        if (ref->get() != nullptr) throw ref->get();
#endif
        AtomicReference<JmriException*>* ref = new AtomicReference<JmriException*>();
        ThreadingUtil::runOnLayoutWithJmriException(new ActionSignalHead_Run(ref, operation, conditionalNG, signalHead, this));
}

    //@Override
    /*public*/  FemaleSocket* ActionSignalHead::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int ActionSignalHead::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString ActionSignalHead::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "SignalHead");
    }

    //@Override
    /*public*/  QString ActionSignalHead::getLongDescription(QLocale locale) {
        QString namedBean;
        QString operation;
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
                namedBean = tr(/*locale,*/ "by formula %1").arg(_formula);
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        switch (_operationAddressing) {
            case NamedBeanAddressing::Direct:
                operation = tr(/*locale,*/ "%1").arg(OperationType::toString(_operationType));
                break;

            case NamedBeanAddressing::Reference:
                operation = tr(/*locale,*/ "by reference %1").arg(_operationReference);
                break;

            case NamedBeanAddressing::LocalVariable:
                operation = tr(/*locale,*/ "by local variable %1").arg(_operationLocalVariable);
                break;

            case NamedBeanAddressing::Formula:
                operation = tr(/*locale,*/ "by formula %1").arg(_operationFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _operationAddressing state: " + NamedBeanAddressing::toString(_operationAddressing));
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
                appearance = tr(/*locale,*/ "by formula %1").arg( _appearanceFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _stateAddressing state: " + NamedBeanAddressing::toString(_appearanceAddressing));
        }

        if (_operationAddressing == NamedBeanAddressing::Direct) {
            if (_operationType == OperationType::Appearance) {
                return tr(/*locale,*/ "Set signal head %1 to appearance %2").arg(namedBean, appearance);
            } else {
                return tr(/*locale,*/ "Set signal head %1 to %2").arg(namedBean, operation);
            }
        } else {
            return tr(/*locale,*/ "Set signal head %1 to %2 with appearance %3").arg(namedBean, operation, appearance);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionSignalHead::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionSignalHead::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionSignalHead::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionSignalHead::disposeMe() {
    }





    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionSignalHead::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
        log->debug(tr("getUsageReport :: ActionSignalHead: bean = %1, report = %2").arg(cdl->getDisplayName()).arg(report->size()));
        if (getSignalHead() != nullptr && bean->equals(getSignalHead()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
        }
        if (getExampleSignalHead() != nullptr && bean->equals(getExampleSignalHead()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* ActionSignalHead::log = LoggerFactory::getLogger("ActionSignalHead");
