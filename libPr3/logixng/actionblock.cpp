#include "actionblock.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalactionmanager.h"
#include "abstractblockmanager.h"
#include "referenceutil.h"
#include "recursivedescentparser.h"
#include "namedbeanhandlemanager.h"
#include "vptr.h"
#include "defaultconditionalng.h"
#include "typeconversionutil.h"

/**
 * This action triggers a block.
 *
 * @author Daniel Bergqvist Copyright 2021
 * @author Dave Sand Copyright 2021
 */
///*public*/  class ActionBlock extends AbstractDigitalAction implements VetoableChangeListener {



    /*public*/  ActionBlock::ActionBlock(QString sys, QString user, QObject *parent) : AbstractDigitalAction(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
     setObjectName("ActionBlock");
    }

    //@Override
    /*public*/  Base* ActionBlock::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/ {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ActionBlock* copy = new ActionBlock(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->setAddressing(_addressing);
        if (_blockHandle != nullptr) copy->setBlock(_blockHandle);
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
        copy->setBlockValue(_blockValue);

        return manager->registerAction(copy);
    }

    /*public*/  void ActionBlock::setBlock(/*@Nonnull*/ QString blockName) {
     if(blockName.isEmpty()) throw new NullPointerException("block name is null!");
        assertListenersAreNotRegistered(log, "setBlock");
        Block* block = (Block*)((AbstractBlockManager*)InstanceManager::getDefault("BlockManager"))->getNamedBean(blockName)->self();
        if (block != nullptr) {
            this->setBlock(block);
        } else {
            removeBlock();
            log->error(tr("Block \"%1\" is not found").arg(blockName));
        }
    }

    /*public*/  void ActionBlock::setBlock(/*@Nonnull*/ Block* block) {
        assertListenersAreNotRegistered(log, "setBlock");
        this->setBlock(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(block->getDisplayName(), block));
    }

    /*public*/  void ActionBlock::setBlock(/*@Nonnull*/ NamedBeanHandle<Block*>* handle) {
        assertListenersAreNotRegistered(log, "setBlock");
        _blockHandle = handle;
        ((AbstractBlockManager*)InstanceManager::getDefault("BlockManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/  void ActionBlock::removeBlock() {
        assertListenersAreNotRegistered(log, "removeBlock");
        if (_blockHandle != nullptr) {
            ((AbstractBlockManager*)InstanceManager::getDefault("BlockManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _blockHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<Block*>* ActionBlock::getBlock() {
        return _blockHandle;
    }

    /*public*/  void ActionBlock::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException */{
        _addressing = addressing;
        parseFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ActionBlock::getAddressing() {
        return _addressing;
    }

    /*public*/  void ActionBlock::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/  QString ActionBlock::getReference() {
        return _reference;
    }

    /*public*/  void ActionBlock::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/  QString ActionBlock::getLocalVariable() {
        return _localVariable;
    }

    /*public*/  void ActionBlock::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException */{
        _formula = formula;
        parseFormula();
    }

    /*public*/  QString ActionBlock::getFormula() {
        return _formula;
    }

    /*private*/ void ActionBlock::parseFormula() /*throws ParserException */{
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }


    /*public*/  void ActionBlock::setOperationAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _operationAddressing = addressing;
        parseOperationFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ActionBlock::getOperationAddressing() {
        return _operationAddressing;
    }

    /*public*/  void ActionBlock::setOperationDirect(DirectOperation::TYPE state) {
        _operationDirect = state;
    }

    /*public*/  ActionBlock::DirectOperation::TYPE ActionBlock::getOperationDirect() {
        return _operationDirect;
    }

    /*public*/  void ActionBlock::setOperationReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _operationReference = reference;
    }

    /*public*/  QString ActionBlock::getOperationReference() {
        return _operationReference;
    }

    /*public*/  void ActionBlock::setOperationLocalVariable(/*@Nonnull*/ QString localVariable) {
        _operationLocalVariable = localVariable;
    }

    /*public*/  QString ActionBlock::getOperationLocalVariable() {
        return _operationLocalVariable;
    }

    /*public*/  void ActionBlock::setOperationFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _operationFormula = formula;
        parseOperationFormula();
    }

     /*public*/  QString ActionBlock::getOperationFormula() {
        return _operationFormula;
    }

    /*private*/ void ActionBlock::parseOperationFormula() /*throws ParserException*/ {
        if (_operationAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _operationExpressionNode = parser->parseExpression(_operationFormula);
        } else {
            _operationExpressionNode = nullptr;
        }
    }


     /*public*/  void ActionBlock::setDataAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _dataAddressing = addressing;
        parseDataFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ActionBlock::getDataAddressing() {
        return _dataAddressing;
    }

    /*public*/  void ActionBlock::setDataReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _dataReference = reference;
    }

    /*public*/  QString ActionBlock::getDataReference() {
        return _dataReference;
    }

    /*public*/  void ActionBlock::setDataLocalVariable(/*@Nonnull*/ QString localVariable) {
        _dataLocalVariable = localVariable;
    }

    /*public*/  QString ActionBlock::getDataLocalVariable() {
        return _dataLocalVariable;
    }

    /*public*/  void ActionBlock::setDataFormula(/*@Nonnull*/ QString formula) /*throws ParserException */{
        _dataFormula = formula;
        parseDataFormula();
    }

    /*public*/  QString ActionBlock::getDataFormula() {
        return _dataFormula;
    }

    /*private*/ void ActionBlock::parseDataFormula() /*throws ParserException*/ {
        if (_dataAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _dataExpressionNode = parser->parseExpression(_dataFormula);
        } else {
            _dataExpressionNode = nullptr;
        }
    }


    /*public*/  void ActionBlock::setBlockValue(/*@Nonnull*/ QString value) {
        _blockValue = value;
    }

    /*public*/  QString ActionBlock::getBlockValue() {
        return _blockValue;
    }


    //@Override
    /*public*/  void ActionBlock::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == evt->getPropertyName()) { // No I18N
            if (qobject_cast<Block*>(VPtr<Block>::asPtr(evt->getOldValue()))) {
                if (VPtr<Block>::asPtr(evt->getOldValue())->equals(getBlock()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Block is in use by Block action \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category ActionBlock::getCategory() {
        return Category::ITEM;
    }

    /*private*/ QString ActionBlock::getNewOperation() /*throws JmriException*/ {

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

    /*private*/ QString ActionBlock::getNewData() /*throws JmriException*/ {

        switch (_dataAddressing) {
            case NamedBeanAddressing::Direct:
                return _blockValue;

            case NamedBeanAddressing::Reference:
                return ReferenceUtil::getReference(
                        getConditionalNG()->getSymbolTable(), _dataReference);

            case NamedBeanAddressing::LocalVariable:
            {
                SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                return TypeConversionUtil
                        ::convertToString(symbolTable->getValue(_dataLocalVariable), false);
            }
            case NamedBeanAddressing::Formula:
                return _dataExpressionNode != nullptr
                        ? TypeConversionUtil::convertToString(
                                _dataExpressionNode->calculate(
                                        getConditionalNG()->getSymbolTable()), false)
                        : nullptr;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_dataAddressing));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionBlock::execute() /*throws JmriException*/ {
        Block* block;

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
                block = _blockHandle != nullptr ? _blockHandle->getBean() : nullptr;
                break;

            case NamedBeanAddressing::Reference:
            {
                QString ref = ReferenceUtil::getReference(
                        getConditionalNG()->getSymbolTable(), _reference);
                block = (Block*)((AbstractBlockManager*)InstanceManager::getDefault("BlockManager"))
                        ->getNamedBean(ref)->self();
                break;
            }
            case NamedBeanAddressing::LocalVariable:
            {
                SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                block = (Block*)((AbstractBlockManager*)InstanceManager::getDefault("BlockManager"))
                        ->getNamedBean(TypeConversionUtil
                                ::convertToString(symbolTable->getValue(_localVariable), false))->self();
                break;
            }
            case NamedBeanAddressing::Formula:
                block = _expressionNode != nullptr ?
                        (Block*)((AbstractBlockManager*)InstanceManager::getDefault("BlockManager"))
                                ->getNamedBean(TypeConversionUtil
                                        ::convertToString(_expressionNode->calculate(
                                                getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        if (block == nullptr) {
            return;
        }

        QString name = (_operationAddressing != NamedBeanAddressing::Direct)
                ? getNewOperation() : "";

        DirectOperation::TYPE oper;
        if ((_operationAddressing == NamedBeanAddressing::Direct)) {
            oper = _operationDirect;
        } else {
            oper = DirectOperation::valueOf(name);
        }


        // Variables used in lambda must be effectively final
        DirectOperation::TYPE theOper = oper;

//        ThreadingUtil.runOnLayoutWithJmriException(() -> {
//            Sensor sensor;
//            LayoutBlock lblk;

//            switch (theOper) {
//                case SetOccupied:
//                    sensor = block.getSensor();
//                    if (sensor != null) {
//                        try {
//                            sensor.setKnownState(Sensor.ACTIVE);
//                        } catch (JmriException ex) {
//                            log->debug("Exception setting sensor active");
//                        }
//                    } else {
//                        throw new JmriException(Bundle.getMessage("ActionBlock_ErrorSensor", block.getDisplayName()));
//                    }
//                    break;
//                case SetNotOccupied:
//                    sensor = block.getSensor();
//                    if (sensor != null) {
//                        try {
//                            sensor.setKnownState(Sensor.INACTIVE);
//                        } catch (JmriException ex) {
//                            log->debug("Exception setting sensor inactive");
//                        }
//                    } else {
//                        throw new JmriException(Bundle.getMessage("ActionBlock_ErrorSensor", block.getDisplayName()));
//                    }
//                    break;
//                case SetAltColorOn:
//                    lblk = InstanceManager.getDefault(LayoutBlockManager.class).getLayoutBlock(block);
//                    if (lblk != null) {
//                        lblk.setUseExtraColor(true);
//                    } else {
//                        throw new JmriException(Bundle.getMessage("ActionBlock_ErrorLayoutBlock", block.getDisplayName()));
//                    }
//                    break;
//                case SetAltColorOff:
//                    lblk = InstanceManager.getDefault(LayoutBlockManager.class).getLayoutBlock(block);
//                    if (lblk != null) {
//                        lblk.setUseExtraColor(false);
//                    } else {
//                        throw new JmriException(Bundle.getMessage("ActionBlock_ErrorLayoutBlock", block.getDisplayName()));
//                    }
//                    break;
//                case SetNullValue:
//                    block.setValue(null);
//                    break;
//                case SetValue:
//                    block.setValue(getNewData());
//                    break;
//                default:
//                    throw new IllegalArgumentException("invalid oper state: " + theOper.name());
//            }
//        });
        ThreadingUtil::runOnLayout(new ActionBlock_run(block,theOper, this));
    }

    //@Override
    /*public*/  FemaleSocket* ActionBlock::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int ActionBlock::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString ActionBlock::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "ActionBlock");
    }

    //@Override
    /*public*/  QString ActionBlock::getLongDescription(QLocale locale) {
        QString namedBean;
        QString state = "";

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
            {
                QString blockName;
                if (_blockHandle != nullptr) {
                  Block* b = _blockHandle->getBean();
                    blockName = _blockHandle->getBean()->getDisplayName();
                } else {
                    blockName = tr(/*locale,*/ "''");
                }
                namedBean = tr(/*locale,*/ "by address %1").arg(blockName);
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
            {
                if (_operationDirect == DirectOperation::SetValue) {
                    //QString bundleKey = "ActionBlock_Long_Value";
                    switch (_dataAddressing) {
                        case NamedBeanAddressing::Direct:
                            return tr(/*locale,*/ "Set block \"%1\" value to \"%2\"").arg(namedBean, _blockValue);
                        case NamedBeanAddressing::Reference:
                            return tr(/*locale,*/ "Set block \"%1\" value to \"%2\"").arg(namedBean, tr("by reference %1").arg(_dataReference));
                        case NamedBeanAddressing::LocalVariable:
                            return tr(/*locale,*/ "Set block \"%1\" value to \"%2\"").arg(namedBean, tr("by local variable %1").arg(_dataLocalVariable));
                        case NamedBeanAddressing::Formula:
                            return tr(/*locale,*/ "Set block \"%1\" value to \"%2\"").arg(namedBean, tr("by formula %1").arg(_dataFormula));
                        default:
                            throw new IllegalArgumentException("invalid _dataAddressing state: " + NamedBeanAddressing::toString(_dataAddressing));
                    }
                } else {
                    state = tr(/*locale,*/ "%1").arg(ActionBlock::DirectOperation::toString(_operationDirect));
                }
                break;
}
            case NamedBeanAddressing::Reference:
                state = tr(/*locale,*/ "by reference %1").arg(_operationReference);
                break;

            case NamedBeanAddressing::LocalVariable:
                state = tr(/*locale,*/ "y local variable %1").arg(_operationLocalVariable);
                break;

            case NamedBeanAddressing::Formula:
                state = tr(/*locale,*/ "by formula").arg(_operationFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _stateAddressing state: " + NamedBeanAddressing::toString(_operationAddressing));
        }

        return tr(/*locale,*/ "Set block \"%1\" to %2").arg(namedBean, state);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionBlock::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionBlock::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionBlock::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionBlock::disposeMe() {
    }



    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionBlock::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport *> *report, NamedBean* cdl) {
        log->debug(tr("getUsageReport :: ActionBlock: bean = %1, report = %2").arg(cdl->getDisplayName()).arg(report->size()));
        if (getBlock() != nullptr && bean->equals(getBlock()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* ActionBlock::log = LoggerFactory::getLogger("ActionBlock");

