#include "actionsignalmast.h"
#include "defaultsignalmastmanager.h"
#include "logixng/conditionalng.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/digitalactionmanager.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "logixng/recursivedescentparser.h"
#include "logixng/typeconversionutil.h"
#include "logixng/variable.h"
#include "referenceutil.h"
#include "vptr.h"

ActionSignalMast::ActionSignalMast(QObject *parent)
    : AbstractDigitalAction{parent}
{

}
/**
 * Evaluates the state of a SignalMast.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
// /*public*/ class ActionSignalMast extends AbstractDigitalAction
//        implements VetoableChangeListener {




    /*public*/ ActionSignalMast::ActionSignalMast(QString sys, QString user, QObject* parent)
    : AbstractDigitalAction(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
     setObjectName("ActionSignalMast");
    }

    //@Override
    /*public*/ Base* ActionSignalMast::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/ {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ActionSignalMast* copy = new ActionSignalMast(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_signalMastHandle != nullptr) copy->setSignalMast(_signalMastHandle);
        copy->setAspect(_signalMastAspect);
        copy->setAddressing(_addressing);
        copy->setFormula(_formula);
        copy->setLocalVariable(_localVariable);
        copy->setReference(_reference);
        copy->setOperationAddressing(_operationAddressing);
        copy->setOperationType(_operationType);
        copy->setOperationFormula(_operationFormula);
        copy->setOperationLocalVariable(_operationLocalVariable);
        copy->setOperationReference(_operationReference);
        copy->setAspectAddressing(_aspectAddressing);
        copy->setAspectFormula(_aspectFormula);
        copy->setAspectLocalVariable(_aspectLocalVariable);
        copy->setAspectReference(_aspectReference);
        copy->setExampleSignalMast(_exampleSignalMastHandle);
        return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /*public*/ void ActionSignalMast::setSignalMast(/*@Nonnull*/ QString signalMastName) {
        assertListenersAreNotRegistered(log, "setSignalMast");
        SignalMast* signalMast = ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signalMastName);
        if (signalMast != nullptr) {
            setSignalMast(signalMast);
        } else {
            removeSignalMast();
            log->warn(tr("signalMast \"%1\" is not found").arg(signalMastName));
        }
    }

    /*public*/ void ActionSignalMast::setSignalMast(/*@Nonnull*/ NamedBeanHandle<SignalMast*>* handle) {
        assertListenersAreNotRegistered(log, "setSignalMast");
        _signalMastHandle = handle;
        ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/ void ActionSignalMast::setSignalMast(/*@Nonnull*/ SignalMast* signalMast) {
        assertListenersAreNotRegistered(log, "setSignalMast");
        setSignalMast(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                      ->getNamedBeanHandle(signalMast->getDisplayName(), signalMast));
    }

    /*public*/ void ActionSignalMast::removeSignalMast() {
        assertListenersAreNotRegistered(log, "setSignalMast");
        if (_signalMastHandle != nullptr) {
            ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _signalMastHandle = nullptr;
        }
    }

    /*public*/ NamedBeanHandle<SignalMast*>* ActionSignalMast::getSignalMast() {
        return _signalMastHandle;
    }

    /*public*/ void ActionSignalMast::setExampleSignalMast(/*@Nonnull*/ QString signalMastName) {
        assertListenersAreNotRegistered(log, "setExampleSignalMast");
        SignalMast* signalMast = ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signalMastName);
        if (signalMast != nullptr) {
            setExampleSignalMast(signalMast);
        } else {
            removeExampleSignalMast();
            log->warn(tr("signalMast \"%1\" is not found").arg(signalMastName));
        }
    }

    /*public*/ void ActionSignalMast::setExampleSignalMast(/*@Nonnull*/ NamedBeanHandle<SignalMast*>* handle) {
        assertListenersAreNotRegistered(log, "setExampleSignalMast");
        _exampleSignalMastHandle = handle;
        ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/ void ActionSignalMast::setExampleSignalMast(/*@Nonnull*/ SignalMast* signalMast) {
        assertListenersAreNotRegistered(log, "setExampleSignalMast");
        setExampleSignalMast(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                             ->getNamedBeanHandle(signalMast->getDisplayName(), signalMast));
    }

    /*public*/ void ActionSignalMast::removeExampleSignalMast() {
        assertListenersAreNotRegistered(log, "removeExampleSignalMast");
        if (_exampleSignalMastHandle != nullptr) {
            ((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _exampleSignalMastHandle = nullptr;
        }
    }

    /*public*/ NamedBeanHandle<SignalMast*>* ActionSignalMast::getExampleSignalMast() {
        return _exampleSignalMastHandle;
    }

    /*public*/ void ActionSignalMast::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ActionSignalMast::getAddressing() {
        return _addressing;
    }

    /*public*/ void ActionSignalMast::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/ QString ActionSignalMast::getReference() {
        return _reference;
    }

    /*public*/ void ActionSignalMast::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/ QString ActionSignalMast::getLocalVariable() {
        return _localVariable;
    }

    /*public*/ void ActionSignalMast::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _formula = formula;
        parseFormula();
    }

    /*public*/ QString ActionSignalMast::getFormula() {
        return _formula;
    }

    /*private*/ void ActionSignalMast::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }

    /*public*/ void ActionSignalMast::setOperationAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _operationAddressing = addressing;
        parseOperationFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ActionSignalMast::getOperationAddressing() {
        return _operationAddressing;
    }

    /*public*/ void ActionSignalMast::setOperationType(OperationType::TYPE operationType) {
        _operationType = operationType;
    }

    /*public*/ ActionSignalMast::OperationType::TYPE ActionSignalMast::getOperationType() {
        return _operationType;
    }

    /*public*/ void ActionSignalMast::setOperationReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _operationReference = reference;
    }

    /*public*/ QString ActionSignalMast::getOperationReference() {
        return _operationReference;
    }

    /*public*/ void ActionSignalMast::setOperationLocalVariable(/*@Nonnull*/ QString localVariable) {
        _operationLocalVariable = localVariable;
    }

    /*public*/ QString ActionSignalMast::getOperationLocalVariable() {
        return _operationLocalVariable;
    }

    /*public*/ void ActionSignalMast::setOperationFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _operationFormula = formula;
        parseOperationFormula();
    }

    /*public*/ QString ActionSignalMast::getOperationFormula() {
        return _operationFormula;
    }

    /*private*/ void ActionSignalMast::parseOperationFormula() /*throws ParserException*/ {
        if (_operationAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _operationExpressionNode = parser->parseExpression(_operationFormula);
        } else {
            _operationExpressionNode = nullptr;
        }
    }

    /*public*/ void ActionSignalMast::setAspectAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _aspectAddressing = addressing;
        parseAspectFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ActionSignalMast::getAspectAddressing() {
        return _aspectAddressing;
    }

    /*public*/ void ActionSignalMast::setAspect(QString aspect) {
        if (aspect == "") _signalMastAspect = "";
        else _signalMastAspect = aspect;
    }

    /*public*/ QString ActionSignalMast::getAspect() {
        return _signalMastAspect;
    }

    /*public*/ void ActionSignalMast::setAspectReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _aspectReference = reference;
    }

    /*public*/ QString ActionSignalMast::getAspectReference() {
        return _aspectReference;
    }

    /*public*/ void ActionSignalMast::setAspectLocalVariable(/*@Nonnull*/ QString localVariable) {
        _aspectLocalVariable = localVariable;
    }

    /*public*/ QString ActionSignalMast::getAspectLocalVariable() {
        return _aspectLocalVariable;
    }

    /*public*/ void ActionSignalMast::setAspectFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _aspectFormula = formula;
        parseAspectFormula();
    }

    /*public*/ QString ActionSignalMast::getAspectFormula() {
        return _aspectFormula;
    }

    /*private*/ void ActionSignalMast::parseAspectFormula() /*throws ParserException*/ {
        if (_aspectAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _aspectExpressionNode = parser->parseExpression(_aspectFormula);
        } else {
            _aspectExpressionNode = nullptr;
        }
    }

    //@Override
    /*public*/ void ActionSignalMast::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<SignalMast>::asPtr(evt->getOldValue())) {
                if (_signalMastHandle != nullptr
                        && (VPtr<SignalMast>::asPtr(evt->getOldValue())->equals(_signalMastHandle->getBean()))) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("SignalMast is in use by SignalMast action \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
                if (_exampleSignalMastHandle != nullptr
                        && (VPtr<SignalMast>::asPtr(evt->getOldValue())->equals(_exampleSignalMastHandle->getBean()))) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("SignalMast is in use by SignalMast action \"%1\"").arg(getDisplayName()), e); // NOI18N
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
    /*public*/ Category ActionSignalMast::getCategory() {
        return Category::ITEM;
    }

    /*private*/ QString ActionSignalMast::getNewAspect(ConditionalNG* conditionalNG) /*throws JmriException*/ {

        switch (_aspectAddressing) {
        case NamedBeanAddressing::Direct:
                return _signalMastAspect;

            case NamedBeanAddressing::Reference:
                return ReferenceUtil::getReference(
                            conditionalNG->getSymbolTable(), _aspectReference);

            case NamedBeanAddressing::LocalVariable:
            {
             SymbolTable* symbolTable = conditionalNG->getSymbolTable();
                return TypeConversionUtil
                        ::convertToString(symbolTable->getValue(_aspectLocalVariable), false);
            }
            case NamedBeanAddressing::Formula:
                return _aspectExpressionNode != nullptr
                        ? TypeConversionUtil::convertToString(
                                _aspectExpressionNode->calculate(
                                        conditionalNG->getSymbolTable()), false)
                        : "";

            default:
                throw new IllegalArgumentException("invalid _aspectAddressing state: " + NamedBeanAddressing::toString(_aspectAddressing));
        }
    }

    /*private*/ ActionSignalMast::OperationType::TYPE ActionSignalMast::getOperation() /*throws JmriException*/ {

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
                    if (_aspectExpressionNode != nullptr) {
                        oper = TypeConversionUtil::convertToString(
                                _operationExpressionNode->calculate(
                                        getConditionalNG()->getSymbolTable()), false);
                        return OperationType::valueOf(oper);
                    } else {
                        return OperationType::None;
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
    /*public*/ void ActionSignalMast::execute() /*throws JmriException*/ {
        SignalMast* signalMast;

//        System.out.format("ActionSignalMast.execute: %s%n", getLongDescription());

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

//        System.out.format("ActionSignalMast.execute: sensor: %s%n", sensor);

        if (signalMast == nullptr) {
//            log.warn("signalMast is null");
            return;
        }

        OperationType::TYPE operation = getOperation();

        /*final*/ ConditionalNG* conditionalNG = getConditionalNG();
#if 0
        AtomicReference<JmriException> ref = new AtomicReference<>();
        jmri.util.ThreadingUtil.runOnLayoutWithJmriException(() -> {
            try {
                switch (operation) {
                    case Aspect:
                        String newAspect = getNewAspect(conditionalNG);
                        if (!newAspect.isEmpty()) {
                            signalMast.setAspect(newAspect);
                        }
                        break;
                    case Lit:
                        signalMast.setLit(true);
                        break;
                    case NotLit:
                        signalMast.setLit(false);
                        break;
                    case Held:
                        signalMast.setHeld(true);
                        break;
                    case NotHeld:
                        signalMast.setHeld(false);
                        break;
                    case PermissiveSmlDisabled:
                        signalMast.setPermissiveSmlDisabled(true);
                        break;
                    case PermissiveSmlNotDisabled:
                        signalMast.setPermissiveSmlDisabled(false);
                        break;
                    default:
                        throw new JmriException("Unknown enum: "+_operationType.name());
                }
            } catch (JmriException e) {
                ref.set(e);
            }
        });
        if (ref.get() != nullptr) throw ref.get();
#endif
        QAtomicPointer<JmriException> ref;
        ThreadingUtil::runOnLayoutWithJmriException(new ASM_ThreadingUtil(signalMast, conditionalNG, ref, operation,this));
        if (ref.loadAcquire() != nullptr) throw ref.loadAcquire();
    }

    //@Override
    /*public*/ FemaleSocket* ActionSignalMast::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/ int ActionSignalMast::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/ QString ActionSignalMast::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "SignalMast");
    }

    //@Override
    /*public*/ QString ActionSignalMast::getLongDescription(QLocale locale) {
        QString namedBean;
        QString operation;
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
                throw new IllegalArgumentException(QString("invalid _operationAddressing state: ") + NamedBeanAddressing::toString(_operationAddressing));
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
                aspect = tr(/*locale,*/ "by formula %1").arg(_aspectFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _stateAddressing state: " + NamedBeanAddressing::toString(_aspectAddressing));
        }

        if (_operationAddressing == NamedBeanAddressing::Direct) {
            if (_operationType == OperationType::Aspect) {
                return tr(/*locale,*/ "Set signal mast %1 to aspect %2").arg(namedBean, aspect);
            } else {
                return tr(/*locale,*/ "Set signal mast %1 to {%2").arg(namedBean, operation);
            }
        } else {
            return tr(/*locale,*/ "Set signal mast %1 to %2 with aspect %3").arg(namedBean, operation, aspect);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionSignalMast::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionSignalMast::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionSignalMast::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionSignalMast::disposeMe() {
    }



//    /*public*/ enum OperationType {
//        Aspect(tr("SignalMastOperationType_Aspect")),
//        Lit(tr("SignalMastOperationType_Lit")),
//        NotLit(tr("SignalMastOperationType_NotLit")),
//        Held(tr("SignalMastOperationType_Held")),
//        NotHeld(tr("SignalMastOperationType_NotHeld")),
//        PermissiveSmlDisabled(tr("SignalMastOperationType_PermissiveSmlDisabled")),
//        PermissiveSmlNotDisabled(tr("SignalMastOperationType_PermissiveSmlNotDisabled"));

//        /*private*/ final String _text;

//        /*private*/ OperationType(String text) {
//            this._text = text;
//        }

//        //@Override
//        /*public*/ String toString() {
//            return _text;
//        }

//    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionSignalMast::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
        log->debug(tr("getUsageReport :: ActionSignalMast: bean = %1, report = %2").arg(cdl->getDisplayName(), report->at(0)->usageData));
        if (getSignalMast() != nullptr && bean->equals(getSignalMast()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
        }
        if (getExampleSignalMast() != nullptr && bean->equals(getExampleSignalMast()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* ActionSignalMast::log = LoggerFactory::getLogger("ActionSignalMast");
