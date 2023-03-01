#include "enablelogix.h"
#include "defaultlogixmanager.h"
#include "logix.h"
#include "logixng/conditionalng.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "instancemanager.h"
#include "logixng/recursivedescentparser.h"
#include "vptr.h"
#include "referenceutil.h"
#include "typeconversionutil.h"
#include "loggerfactory.h"
/**
 * This action enables/disables a Logix.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class EnableLogix extends AbstractDigitalAction implements VetoableChangeListener {


    /*public*/ EnableLogix::EnableLogix(QString sys, QString user, QObject* parent)
            /*throws BadUserNameException, BadSystemNameException*/ : AbstractDigitalAction(sys, user, parent){
        //super(sys, user);
    setObjectName("EnableLogix");
    }

    //@Override
    /*public*/ Base* EnableLogix::getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws ParserException*/ {
    DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        EnableLogix* copy = new EnableLogix(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_logixHandle != nullptr) copy->setLogix(_logixHandle);
        copy->setOperationDirect(_operationDirect);
        copy->setAddressing(_addressing);
        copy->setFormula(_formula);
        copy->setLocalVariable(_localVariable);
        copy->setReference(_reference);
        copy->setOperationAddressing(_operationAddressing);
        copy->setOperationFormula(_operationFormula);
        copy->setOperationLocalVariable(_operationLocalVariable);
        copy->setOperationReference(_operationReference);
        return manager->registerAction(copy);
    }

    /*public*/ void EnableLogix::setLogix(/*@Nonnull*/ QString logixName) {
        assertListenersAreNotRegistered(log, "setLogix");
        Logix* logix = ((DefaultLogixManager*)InstanceManager::getDefault("LogixManager"))->getLogix(logixName);
        if (logix != nullptr) {
            setLogix(logix);
        } else {
            removeLogix();
            log->error(tr("logix \"%1\" is not found").arg(logixName));
        }
    }

    /*public*/ void EnableLogix::setLogix(/*@Nonnull*/ NamedBeanHandle<Logix*>* handle) {
        assertListenersAreNotRegistered(log, "setLogix");
        _logixHandle = handle;
        ((DefaultLogixManager*)InstanceManager::getDefault("LogixManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/ void EnableLogix::setLogix(/*@Nonnull*/ Logix* logix) {
        assertListenersAreNotRegistered(log, "setLogix");
        setLogix(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->
                 getNamedBeanHandle(logix->getDisplayName(), logix));
    }

    /*public*/ void EnableLogix::removeLogix() {
        assertListenersAreNotRegistered(log, "removeLogix");
        if (_logixHandle != nullptr) {
            ((DefaultLogixManager*)InstanceManager::getDefault("LogixManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _logixHandle = nullptr;
        }
    }

    /*public*/ NamedBeanHandle<Logix*>* EnableLogix::getLogix() {
        return _logixHandle;
    }

    /*public*/ void EnableLogix::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE EnableLogix:: getAddressing() {
        return _addressing;
    }

    /*public*/ void EnableLogix::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/ QString EnableLogix::getReference() {
        return _reference;
    }

    /*public*/ void EnableLogix::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/ QString EnableLogix::getLocalVariable() {
        return _localVariable;
    }

    /*public*/ void EnableLogix::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _formula = formula;
        parseFormula();
    }

    /*public*/ QString EnableLogix::getFormula() {
        return _formula;
    }

    /*private*/ void EnableLogix::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*>  variables = QMap<QString, Variable*> ();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }

    /*public*/ void EnableLogix::setOperationAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _operationAddressing = addressing;
        parseLockFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE EnableLogix::getOperationAddressing() {
        return _operationAddressing;
    }

    /*public*/ void EnableLogix::setOperationDirect(Operation::TYPE state) {
        _operationDirect = state;
    }

    /*public*/ EnableLogix::Operation::TYPE EnableLogix::getOperationDirect() {
        return _operationDirect;
    }

    /*public*/ void EnableLogix::setOperationReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _operationReference = reference;
    }

    /*public*/ QString EnableLogix::getOperationReference() {
        return _operationReference;
    }

    /*public*/ void EnableLogix::setOperationLocalVariable(/*@Nonnull*/ QString localVariable) {
        _operationLocalVariable = localVariable;
    }

    /*public*/ QString EnableLogix::getOperationLocalVariable() {
        return _operationLocalVariable;
    }

    /*public*/ void EnableLogix::setOperationFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _operationFormula = formula;
        parseLockFormula();
    }

    /*public*/ QString EnableLogix::getLockFormula() {
        return _operationFormula;
    }

    /*private*/ void EnableLogix::parseLockFormula() /*throws ParserException*/ {
        if (_operationAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*>  variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _operationExpressionNode = parser->parseExpression(_operationFormula);
        } else {
            _operationExpressionNode = nullptr;
        }
    }

    //@Override
    /*public*/ void EnableLogix::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<Logix>::asPtr(evt->getOldValue())) {
                if (VPtr<Logix>::asPtr(evt->getOldValue())->equals(getLogix()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Logix is in use by Enable Logix action \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<Logix>::asPtr(evt->getOldValue())) {
                if (VPtr<Logix>::asPtr(evt->getOldValue())->equals(getLogix()->getBean())) {
                    removeLogix();
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category EnableLogix::getCategory() {
        return Category::ITEM;
    }

    /*private*/ QString EnableLogix::getNewLock() /*throws JmriException*/ {

        switch (_operationAddressing) {
            case NamedBeanAddressing::Reference:
                return ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _operationReference);

            case NamedBeanAddressing::LocalVariable:
            {
            SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                return TypeConversionUtil
                        ::convertToString(symbolTable->getValue(_operationLocalVariable), false);
            }
            case NamedBeanAddressing::Formula:
                return _operationExpressionNode != nullptr
                        ? TypeConversionUtil::convertToString(
                              _operationExpressionNode->calculate(
                                  getConditionalNG()->getSymbolTable()), false)
                        : nullptr;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_operationAddressing));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void EnableLogix::execute() /*throws JmriException*/ {
        Logix* logix;

//        System.out.format("ActionEnableLogix.execute: %s%n", getLongDescription());

        switch (_addressing) {
        case NamedBeanAddressing::Direct:
            logix = _logixHandle != nullptr ? _logixHandle->getBean() : nullptr;
                break;

        case NamedBeanAddressing::Reference:
        {
                QString ref = ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _reference);
                logix = (Logix*)((DefaultLogixManager*)InstanceManager::getDefault("LogixManager"))->
                        getNamedBean(ref)->self();
                break;
        }
        case NamedBeanAddressing::LocalVariable:
        {
            SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                logix = (Logix*)((DefaultLogixManager*)InstanceManager::getDefault("LogixManager"))->
                        getNamedBean(TypeConversionUtil
                                     ::convertToString(symbolTable->getValue(_localVariable), false))->self();
                break;
        }
            case NamedBeanAddressing::Formula:
                logix = _expressionNode != nullptr ?(Logix*)
                        ((DefaultLogixManager*)InstanceManager::getDefault("LogixManager"))->
                                getNamedBean(TypeConversionUtil
                                             ::convertToString(_expressionNode->calculate(
                                                              getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

//        System.out.format("ActionEnableLogix.execute: logix: %s%n", logix);

        if (logix == nullptr) {
//            log.error("logix is null");
            return;
        }

        QString name = (_operationAddressing != NamedBeanAddressing::Direct)
                ? getNewLock() : "";

        Operation::TYPE lock;
        if (_operationAddressing == NamedBeanAddressing::Direct) {
            lock = _operationDirect;
        } else {
            lock = EnableLogix::Operation::valueOf(name);
        }

        // Variables used in lambda must be effectively final
        EnableLogix::Operation::TYPE theLock = lock;

//        ThreadingUtil::runOnLayoutWithJmriException(() -> {
//            logix.setEnabled(theLock == Operation.Enable);
//        });
        EL_ThreadingUtil::runOnLayoutWithJmriException(logix, theLock);
    }

    //@Override
    /*public*/ FemaleSocket* EnableLogix::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/ int EnableLogix::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/ QString EnableLogix::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "EnableLogix_Short");
    }

    //@Override
    /*public*/ QString EnableLogix::getLongDescription(QLocale locale) {
        QString namedBean;
        QString state;

        switch (_addressing) {
        case NamedBeanAddressing::Direct:
        {
                QString logixName;
                if (_logixHandle != nullptr) {
                    logixName = _logixHandle->getBean()->getDisplayName();
                } else {
                    logixName = tr(/*locale,*/ "BeanNotSelected");
                }
                namedBean = tr(/*locale,*/ "%1").arg(logixName);
                break;
        }
            case NamedBeanAddressing::Reference:
                namedBean = tr(/*locale,*/ "by reference %1").arg(_reference);
                break;

            case NamedBeanAddressing::LocalVariable:
                namedBean = tr(/*locale,*/ "by local variable %1").arg(_localVariable);
                break;

            case NamedBeanAddressing::Formula:
                namedBean = tr(/*locale,*/ "by formulae %1").arg(_formula);
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        switch (_operationAddressing) {
        case NamedBeanAddressing::Direct:
                state = tr(/*locale,*/ "%1").arg(_operationDirect);
                break;

            case NamedBeanAddressing::Reference:
                state = tr(/*locale,*/ "by reference %1").arg(_operationReference);
                break;

            case NamedBeanAddressing::LocalVariable:
                state = tr(/*locale,*/ "by local variable %1").arg(_operationLocalVariable);
                break;

            case NamedBeanAddressing::Formula:
                state = tr(/*locale,*/ "by formulae %1").arg(_operationFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _stateAddressing state: " + NamedBeanAddressing::toString(_operationAddressing));
        }

        return tr(/*locale,*/ "Set Logix %1 to %2").arg(namedBean, state);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void EnableLogix::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void EnableLogix::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void EnableLogix::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void EnableLogix::disposeMe() {
    }


//    /*public*/ enum Operation {
//        Enable(Bundle.getMessage("EnableLogix_Enable")),
//        Disable(Bundle.getMessage("EnableLogix_Disable"));

//        /*private*/ final String _text;

//        /*private*/ Operation(String text) {
//            this._text = text;
//        }

//        //@Override
//        /*public*/ String toString() {
//            return _text;
//        }

//    }

    /*private*/ /*final*/ /*static*/ Logger* EnableLogix::log = LoggerFactory::getLogger("EnableLogix");
