#include "actionoblock.h"
#include "instancemanager.h"
#include "logixng/conditionalng.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "loggerfactory.h"
#include "logixng/recursivedescentparser.h"
#include "logixng/variable.h"
#include "oblockmanager.h"
#include "referenceutil.h"
#include "vptr.h"
#include "typeconversionutil.h"

/**
 * This action triggers an OBlock.
 *
 * @author Daniel Bergqvist Copyright 2021
 * @author Dave Sand Copyright 2021
 */
// /*public*/ class ActionOBlock extends AbstractDigitalAction implements VetoableChangeListener {


    /*public*/ ActionOBlock::ActionOBlock(QString sys, QString user, QObject* parent): AbstractDigitalAction{sys,user,parent}
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
    setObjectName("ActionOBlock");
    }

    //@Override
    /*public*/ Base* ActionOBlock::getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws ParserException*/ {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ActionOBlock* copy = new ActionOBlock(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->setAddressing(_addressing);
        if (_oblockHandle != nullptr) copy->setOBlock(_oblockHandle);
        copy->setReference(_reference);
        copy->setLocalVariable(_localVariable);
        copy->setFormula(_formula);

        copy->setOperationAddressing(_operationAddressing);
        copy->setOperationDirect(_operationDirect);
        copy->setOperationReference(_operationReference);
        copy->setOperationLocalVariable(_operationLocalVariable);
        copy->setOperationFormula(_operationFormula);

        copy->setDataAddressing(_dataAddressing);
        copy->setDataReference(_dataReference);
        copy->setDataLocalVariable(_dataLocalVariable);
        copy->setDataFormula(_dataFormula);
        copy->setOBlockValue(_oblockValue);

        return manager->registerAction(copy);
    }

    /*public*/ void ActionOBlock::setOBlock(/*@Nonnull*/ QString oblockName) {
        assertListenersAreNotRegistered(log, "setOBlock");
        OBlock* oblock = (OBlock*)((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getNamedBean(oblockName)->self();
        if (oblock != nullptr) {
            setOBlock(oblock);
        } else {
            removeOBlock();
            log->error(tr("OBlock \"%1\" is not found").arg(oblockName));
        }
    }

    /*public*/ void ActionOBlock::setOBlock(/*@Nonnull*/ OBlock* oblock) {
        assertListenersAreNotRegistered(log, "setOBlock");
        setOBlock(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                  ->getNamedBeanHandle(oblock->getDisplayName(), oblock));
    }

    /*public*/ void ActionOBlock::setOBlock(/*@Nonnull*/ NamedBeanHandle<OBlock*>* handle) {
        assertListenersAreNotRegistered(log, "setOBlock");
        _oblockHandle = handle;
        ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/ void ActionOBlock::removeOBlock() {
        assertListenersAreNotRegistered(log, "removeOBlock");
        if (_oblockHandle != nullptr) {
            ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _oblockHandle = nullptr;
        }
    }

    /*public*/ NamedBeanHandle<OBlock*>* ActionOBlock::getOBlock() {
        return _oblockHandle;
    }

    /*public*/ void ActionOBlock::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ActionOBlock::getAddressing() {
        return _addressing;
    }

    /*public*/ void ActionOBlock::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/ QString ActionOBlock::getReference() {
        return _reference;
    }

    /*public*/ void ActionOBlock::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/ QString ActionOBlock::getLocalVariable() {
        return _localVariable;
    }

    /*public*/ void ActionOBlock::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _formula = formula;
        parseFormula();
    }

    /*public*/ QString ActionOBlock::getFormula() {
        return _formula;
    }

    /*private*/ void ActionOBlock::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*>  variables = QMap<QString, Variable*> ();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }


    /*public*/ void ActionOBlock::setOperationAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _operationAddressing = addressing;
        parseOperationFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ActionOBlock::getOperationAddressing() {
        return _operationAddressing;
    }

    /*public*/ void ActionOBlock::setOperationDirect(DirectOperation::TYPE state) {
        _operationDirect = state;
    }

/*public*/ ActionOBlock::DirectOperation::TYPE ActionOBlock::getOperationDirect() {
        return _operationDirect;
    }

    /*public*/ void ActionOBlock::setOperationReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _operationReference = reference;
    }

    /*public*/ QString ActionOBlock::getOperationReference() {
        return _operationReference;
    }

    /*public*/ void ActionOBlock::setOperationLocalVariable(/*@Nonnull*/ QString localVariable) {
        _operationLocalVariable = localVariable;
    }

    /*public*/ QString ActionOBlock::getOperationLocalVariable() {
        return _operationLocalVariable;
    }

    /*public*/ void ActionOBlock::setOperationFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _operationFormula = formula;
        parseOperationFormula();
    }

    /*public*/ QString ActionOBlock::getOperationFormula() {
        return _operationFormula;
    }

    /*private*/ void ActionOBlock::parseOperationFormula() /*throws ParserException*/ {
        if (_operationAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*> ();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _operationExpressionNode = parser->parseExpression(_operationFormula);
        } else {
            _operationExpressionNode = nullptr;
        }
    }


     /*public*/ void ActionOBlock::setDataAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _dataAddressing = addressing;
        parseDataFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ActionOBlock::getDataAddressing() {
        return _dataAddressing;
    }

    /*public*/ void ActionOBlock::setDataReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _dataReference = reference;
    }

    /*public*/ QString ActionOBlock::getDataReference() {
        return _dataReference;
    }

    /*public*/ void ActionOBlock::setDataLocalVariable(/*@Nonnull*/ QString localVariable) {
        _dataLocalVariable = localVariable;
    }

    /*public*/ QString ActionOBlock::getDataLocalVariable() {
        return _dataLocalVariable;
    }

    /*public*/ void ActionOBlock::setDataFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _dataFormula = formula;
        parseDataFormula();
    }

    /*public*/ QString ActionOBlock::getDataFormula() {
        return _dataFormula;
    }

    /*private*/ void ActionOBlock::parseDataFormula() /*throws ParserException*/ {
        if (_dataAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*>  variables = QMap<QString, Variable*> ();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _dataExpressionNode = parser->parseExpression(_dataFormula);
        } else {
            _dataExpressionNode = nullptr;
        }
    }

    /*public*/ void ActionOBlock::setOBlockValue(/*@Nonnull*/ QString value) {
        _oblockValue = value;
    }

    /*public*/ QString ActionOBlock::getOBlockValue() {
        return _oblockValue;
    }


    //@Override
    /*public*/ void ActionOBlock::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<OBlock>::asPtr(evt->getOldValue())) {
                if (VPtr<OBlock>::asPtr(evt->getOldValue())->equals(getOBlock()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("OBlock %1 in use").arg(getDisplayName()), e); // NOI18N
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category ActionOBlock::getCategory() {
        return Category::ITEM;
    }

    /*private*/ QString ActionOBlock::getNewOperation() /*throws JmriException */{

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

    /*private*/ QString ActionOBlock::getNewData(ConditionalNG* conditionalNG) /*throws JmriException*/ {

        switch (_dataAddressing) {
            case NamedBeanAddressing::Direct:
                return _oblockValue;

            case NamedBeanAddressing::Reference:
                return ReferenceUtil::getReference(
                            conditionalNG->getSymbolTable(), _dataReference);

            case NamedBeanAddressing::LocalVariable:
            {
            SymbolTable* symbolTable = conditionalNG->getSymbolTable();
                return TypeConversionUtil
                        ::convertToString(symbolTable->getValue(_dataLocalVariable), false);
            }
            case NamedBeanAddressing::Formula:
                return _operationExpressionNode != nullptr
                        ? TypeConversionUtil::convertToString(
                              _dataExpressionNode->calculate(
                                  conditionalNG->getSymbolTable()), false)
                        : nullptr;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_dataAddressing));
        }
    }


    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionOBlock::execute() /*throws JmriException*/ {
        OBlock* oblock;

        switch (_addressing) {
        case NamedBeanAddressing::Direct:
            oblock = _oblockHandle != nullptr ? _oblockHandle->getBean() : nullptr;
                break;

            case NamedBeanAddressing::Reference:
            {
                QString ref = ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _reference);
                oblock = (OBlock*)((OBlockManager*)InstanceManager::getDefault("OBlockManager"))
                        ->getNamedBean(ref)->self();
                break;
            }
            case NamedBeanAddressing::LocalVariable:
            {
            SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                oblock = (OBlock*)((OBlockManager*)InstanceManager::getDefault("OBlockManager"))
                        ->getNamedBean(TypeConversionUtil
                                       ::convertToString(symbolTable->getValue(_localVariable), false))->self();
                break;
            }
            case NamedBeanAddressing::Formula:
                oblock = _expressionNode != nullptr ?
                        (OBlock*)((OBlockManager*)InstanceManager::getDefault("OBlockManager"))
                            ->getNamedBean(TypeConversionUtil
                                           ::convertToString(_expressionNode->calculate(
                                                                 getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        if (oblock == nullptr) {
            return;
        }

        QString name = (_operationAddressing != NamedBeanAddressing::Direct)
                ? getNewOperation() : nullptr;

        DirectOperation::TYPE oper;
        if (_operationAddressing == NamedBeanAddressing::Direct) {
            oper = _operationDirect;
        } else {
            oper = DirectOperation::valueOf(name);
        }


        // Variables used in lambda must be effectively final
        DirectOperation::TYPE theOper = oper;

        /*final*/ ConditionalNG* conditionalNG = getConditionalNG();
#if 0
        ThreadingUtil.runOnLayoutWithJmriException(() -> {
            switch (theOper) {
                case Deallocate:
                    oblock.deAllocate(null);
                    break;
                case SetValue:
                    oblock.setValue(getNewData(conditionalNG));
                    break;
                case SetError:
                    oblock.setError(true);
                    break;
                case ClearError:
                    oblock.setError(false);
                    break;
                case SetOutOfService:
                    oblock.setOutOfService(true);
                    break;
                case ClearOutOfService:
                    oblock.setOutOfService(false);
                    break;
                default:
                    throw new IllegalArgumentException("invalid oper state: " + theOper.name());
            }
        });
#endif
    }

    //@Override
    /*public*/ FemaleSocket* ActionOBlock::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/ int ActionOBlock::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/ QString ActionOBlock::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "ActionOBlock");
    }

    //@Override
    /*public*/ QString ActionOBlock::getLongDescription(QLocale locale) {
        QString namedBean;
        QString state = "";

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
            {
                QString oblockName;
                if (_oblockHandle != nullptr) {
                    oblockName = _oblockHandle->getBean()->getDisplayName();
                } else {
                    oblockName = tr(/*locale,*/ "");
                }
                namedBean = tr(/*locale,*/ "%1").arg(oblockName);
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
                if (_operationDirect == DirectOperation::SetValue) {
                    //QString bundleKey = "ActionOBlock_Long_Value";
                    switch (_dataAddressing) {
                        case NamedBeanAddressing::Direct:
                            return tr(/*locale,*/ "Set oblock \"%1\" value to \"%1\"").arg(namedBean, _oblockValue);
                        case NamedBeanAddressing::Reference:
                            return tr(/*locale,*/ "Set oblock \"%1\" value to \"%1\"").arg(namedBean, tr("by reference %1").arg(_dataReference));
                        case NamedBeanAddressing::LocalVariable:
                            return tr(/*locale,*/ "Set oblock \"%1\" value to \"%1\"").arg(namedBean, tr("by local variable %1").arg(_dataLocalVariable));
                        case NamedBeanAddressing::Formula:
                            return tr(/*locale,*/ "Set oblock \"%1\" value to \"%1\"").arg(namedBean, tr("by formulae %1").arg(_dataFormula));
                        default:
                            throw new IllegalArgumentException("invalid _dataAddressing state: " + NamedBeanAddressing::toString(_dataAddressing));
                    }
                } else {
                    state = tr(/*locale,*/ "%1").arg(DirectOperation::toString(_operationDirect));
                }
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

        return tr(/*locale,*/ "Set oblock \"%1\" to %1").arg(namedBean, state);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionOBlock::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionOBlock::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionOBlock::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionOBlock::disposeMe() {
    }

//    /*public*/ enum DirectOperation {
//        Deallocate(tr("ActionOBlock_Deallocate")),
//        SetValue(tr("ActionOBlock_SetValue")),
//        SetError(tr("ActionOBlock_SetError")),
//        ClearError(tr("ActionOBlock_ClearError")),
//        SetOutOfService(tr("ActionOBlock_SetOutOfService")),
//        ClearOutOfService(tr("ActionOBlock_ClearOutOfService"));

//        /*private*/ final QString _text;

//        /*private*/ DirectOperation(QString text) {
//            this._text = text;
//        }

//        //@Override
//        /*public*/ QString toString() {
//            return _text;
//        }

//    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionOBlock::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
    log->debug(tr("getUsageReport :: ActionOBlock: bean = %1, report = %2").arg(cdl->getDisplayName(), report->at(0)->usageData));
                if (getOBlock() != nullptr && bean->equals(getOBlock()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* ActionOBlock::log = LoggerFactory::getLogger("ActionOBlock");
