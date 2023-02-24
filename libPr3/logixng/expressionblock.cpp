#include "expressionblock.h"
#include "blockmanager.h"
#include "layoutblockmanager.h"
#include "logixng/defaultdigitalexpressionmanager.h"
#include "logixng/digitalexpressionmanager.h"
#include "referenceutil.h"
#include "parserexception.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "recursivedescentparser.h"
#include "defaultconditionalng.h"
#include "typeconversionutil.h"

/**
 * This expression evaluates the state of a Block.
 * The supported characteristics are:
 * <ul>
 *   <li>Is [not] Occupied (based on occupancy sensor state)</li>
 *   <li>Is [not] Unoccupied (based on occupancy sensor state)</li>
 *   <li>Is [not] Other (UNKNOWN, INCONSISTENT, UNDETECTED)</li>
 *   <li>Is [not] Allocated (based on the LayoutBlock useAlternateColor)</li>
 *   <li>Value [not] equals string</li>
 * </ul>
 * @author Daniel Bergqvist Copyright 2021
 * @author Dave Sand Copyright 2021
 */
///*public*/ class ExpressionBlock extends AbstractDigitalExpression
//        implements PropertyChangeListener, VetoableChangeListener {


    /*public*/ ExpressionBlock::ExpressionBlock(QString sys, QString user,QObject *parent)
        : AbstractDigitalExpression(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
    setObjectName("ExpressionBlock");
    }

    //@Override
    /*public*/ Base* ExpressionBlock::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/ {
    DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ExpressionBlock* copy = new ExpressionBlock(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->setAddressing(_addressing);
        if (_blockHandle != nullptr) copy->setBlock(_blockHandle);
        copy->setReference(_reference);
        copy->setLocalVariable(_localVariable);
        copy->setFormula(_formula);

        copy->set_Is_IsNot(_is_IsNot);

        copy->setStateAddressing(_stateAddressing);
        copy->setBeanState(_blockState);
        copy->setStateReference(_stateReference);
        copy->setStateLocalVariable(_stateLocalVariable);
        copy->setStateFormula(_stateFormula);

        copy->setDataAddressing(_dataAddressing);
        copy->setDataReference(_dataReference);
        copy->setDataLocalVariable(_dataLocalVariable);
        copy->setDataFormula(_dataFormula);
        copy->setBlockValue(_blockValue);
        return manager->registerExpression(copy);
    }

    /*public*/ void ExpressionBlock::setBlock(/*@Nonnull*/ QString blockName) {
        assertListenersAreNotRegistered(log, "setBlock");
        Block* block = (Block*)
                ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getNamedBean(blockName)->self();
        if (block != nullptr) {
            this->setBlock(block);
        } else {
            removeBlock();
            log->warn(tr("block \"$1\" is not found").arg(blockName));
        }
    }

    /*public*/ void ExpressionBlock::setBlock(/*@Nonnull*/ Block* block) {
        assertListenersAreNotRegistered(log, "setBlock");
        this->setBlock(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                       ->getNamedBeanHandle(block->getDisplayName(), block));
    }

    /*public*/ void ExpressionBlock::setBlock(/*@Nonnull*/ NamedBeanHandle<Block*>* handle) {
        assertListenersAreNotRegistered(log, "setBlock");
        _blockHandle = handle;
        ((BlockManager*)InstanceManager::getDefault("BlockManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/ void ExpressionBlock::removeBlock() {
        assertListenersAreNotRegistered(log, "removeBlock");
        if (_blockHandle != nullptr) {
            ((BlockManager*)InstanceManager::getDefault("BlockManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _blockHandle = nullptr;
        }
    }

    /*public*/ NamedBeanHandle<Block*>* ExpressionBlock::getBlock() {
        return _blockHandle;
    }

    /*public*/ void ExpressionBlock::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ExpressionBlock::getAddressing() {
        return _addressing;
    }

    /*public*/ void ExpressionBlock::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/ QString ExpressionBlock::getReference() {
        return _reference;
    }

    /*public*/ void ExpressionBlock::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/ QString ExpressionBlock::getLocalVariable() {
        return _localVariable;
    }

    /*public*/ void ExpressionBlock::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _formula = formula;
        parseFormula();
    }

    /*public*/ QString ExpressionBlock::getFormula() {
        return _formula;
    }

    /*private*/ void ExpressionBlock::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*>  variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }


    /*public*/ void ExpressionBlock::set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot) {
        _is_IsNot = is_IsNot;
    }

    /*public*/ Is_IsNot_Enum::VAL ExpressionBlock::get_Is_IsNot() {
        return _is_IsNot;
    }


    /*public*/ void ExpressionBlock::setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _stateAddressing = addressing;
        parseStateFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ExpressionBlock::getStateAddressing() {
        return _stateAddressing;
    }

    /*public*/ void ExpressionBlock::setBeanState(BlockState::VAL state) {
        _blockState = state;
    }

    /*public*/ ExpressionBlock::BlockState::VAL ExpressionBlock::getBeanState() {
        return _blockState;
    }

    /*public*/ void ExpressionBlock::setStateReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _stateReference = reference;
    }

    /*public*/ QString ExpressionBlock::getStateReference() {
        return _stateReference;
    }

    /*public*/ void ExpressionBlock::setStateLocalVariable(/*@Nonnull*/ QString localVariable) {
        _stateLocalVariable = localVariable;
    }

    /*public*/ QString ExpressionBlock::getStateLocalVariable() {
        return _stateLocalVariable;
    }

    /*public*/ void ExpressionBlock::setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _stateFormula = formula;
        parseStateFormula();
    }

    /*public*/ QString ExpressionBlock::getStateFormula() {
        return _stateFormula;
    }

    /*private*/ void ExpressionBlock::parseStateFormula() /*throws ParserException*/ {
        if (_stateAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*>  variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _stateExpressionNode = parser->parseExpression(_stateFormula);
        } else {
            _stateExpressionNode = nullptr;
        }
    }


    /*public*/ void ExpressionBlock::setDataAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _dataAddressing = addressing;
        parseDataFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ExpressionBlock::getDataAddressing() {
        return _dataAddressing;
    }

    /*public*/ void ExpressionBlock::setDataReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _dataReference = reference;
    }

    /*public*/ QString ExpressionBlock::getDataReference() {
        return _dataReference;
    }

    /*public*/ void ExpressionBlock::setDataLocalVariable(/*@Nonnull*/ QString localVariable) {
        _dataLocalVariable = localVariable;
    }

    /*public*/ QString ExpressionBlock::getDataLocalVariable() {
        return _dataLocalVariable;
    }

    /*public*/ void ExpressionBlock::setDataFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _dataFormula = formula;
        parseDataFormula();
    }

    /*public*/ QString ExpressionBlock::getDataFormula() {
        return _dataFormula;
    }

    /*private*/ void ExpressionBlock::parseDataFormula() /*throws ParserException*/ {
        if (_dataAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*>  variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _dataExpressionNode = parser->parseExpression(_dataFormula);
        } else {
            _dataExpressionNode = nullptr;
        }
    }


    /*public*/ void ExpressionBlock::setBlockValue(/*@Nonnull*/ QString value) {
        _blockValue = value;
    }

    /*public*/ QString ExpressionBlock::getBlockValue() {
        return _blockValue;
    }


    //@Override
    /*public*/ void ExpressionBlock::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // NOI18N
            if (VPtr<Block>::asPtr(evt->getOldValue())) {
                if (VPtr<Block>::asPtr(evt->getOldValue())->equals(getBlock()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Block is in use by Block expression \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category ExpressionBlock::getCategory() {
        return Category::ITEM;
    }

    /*private*/ QString ExpressionBlock::getNewState() /*throws JmriException*/ {

        switch (_stateAddressing) {
            case NamedBeanAddressing::Reference:
                return ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _stateReference);

        case NamedBeanAddressing::LocalVariable:
        {
                SymbolTable* symbolTable =
                        getConditionalNG()->getSymbolTable();
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
                throw new IllegalArgumentException("invalid _addressing state: " +NamedBeanAddressing::toString( _stateAddressing));
        }
    }

    /*private*/ QString ExpressionBlock::getNewData() /*throws JmriException*/ {

        switch (_dataAddressing) {
            case NamedBeanAddressing::Reference:
                return ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _dataReference);

            case NamedBeanAddressing::LocalVariable:
            {
                SymbolTable* symbolTable =
                        getConditionalNG()->getSymbolTable();
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

    /**
     * A block is considered to be allocated if the related layout block has use extra color enabled.
     * @param block The block whose allocation state is requested.
     * @return true if the layout block is using the extra color.
     */
    /*public*/ bool ExpressionBlock::isBlockAllocated(Block* block) {
        bool result = false;
        LayoutBlock* layoutBlock = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(block);
        if (layoutBlock != nullptr) {
            result = layoutBlock->getUseExtraColor();
        }
        return result;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ExpressionBlock::evaluate() /*throws JmriException*/ {
        Block* block;

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
            block = _blockHandle != nullptr ? _blockHandle->getBean() : nullptr;
                break;

            case NamedBeanAddressing::Reference:
            {
                QString ref = ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _reference);
                block = (Block*)((BlockManager*)InstanceManager::getDefault("BlockManager"))
                        ->getNamedBean(ref)->self();
                break;
            }
            case NamedBeanAddressing::LocalVariable:
            {
                SymbolTable* symbolTable =
                        getConditionalNG()->getSymbolTable();
                block = (Block*)((BlockManager*)InstanceManager::getDefault("BlockManager"))
                        ->getNamedBean(TypeConversionUtil
                                      ::convertToString(symbolTable->getValue(_localVariable), false))->self();
                break;
            }
            case NamedBeanAddressing::Formula:
                block = _expressionNode != nullptr ?
                        (Block*)((BlockManager*)InstanceManager::getDefault("BlockManager"))
                            ->getNamedBean(TypeConversionUtil
                                              ::convertToString(_expressionNode->calculate(
                                                                    getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        if (block == nullptr) {
            return false;
        }

        BlockState::VAL checkBlockState;

        if (_stateAddressing == NamedBeanAddressing::Direct) {
            checkBlockState = _blockState;
        } else {
            checkBlockState = ExpressionBlock::BlockState::valueOf(getNewState());
        }

        int currentState = block->getState();
        QVariant currentValue = QVariant();

        switch (checkBlockState) {
            case ExpressionBlock::BlockState::Other:
                if (currentState != Block::OCCUPIED && currentState != Block::UNOCCUPIED) {
                    currentState = BlockState::Other/*.getID()*/;
                } else {
                    currentState = 0;
                }
                break;

            case ExpressionBlock::BlockState::Allocated:
            {
                bool cuurrentAllocation = isBlockAllocated(block);
                currentState = cuurrentAllocation ? ExpressionBlock::BlockState::Allocated/*.getID()*/ : 0;
                break;
            }
            case ExpressionBlock::BlockState::ValueMatches:
            currentValue = block->getValue();
                if (_dataAddressing == NamedBeanAddressing::Direct) {
                    currentState = _blockValue ==(currentValue) ? ExpressionBlock::BlockState::ValueMatches/*.getID()*/ : 0;
                } else {
                    currentState = getNewData() == (currentValue) ? ExpressionBlock::BlockState::ValueMatches/*.getID()*/ : 0;
                }
                break;

            default:
                break;
        }

        if (_is_IsNot == Is_IsNot_Enum::Is) {
            return currentState == checkBlockState/*.getID()*/;
        } else {
            return currentState != checkBlockState/*.getID()*/;
        }
    }

    //@Override
    /*public*/ FemaleSocket* ExpressionBlock::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/ int ExpressionBlock::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/ QString ExpressionBlock::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Block");
    }

    //@Override
    /*public*/ QString ExpressionBlock::getLongDescription(QLocale locale) {
        QString namedBean;
        QString state;

        switch (_addressing) {
        case NamedBeanAddressing::Direct:
        {
                QString blockName;
                if (_blockHandle != nullptr) {
                    blockName = _blockHandle->getBean()->getDisplayName();
                } else {
                    blockName = tr(/*locale,*/"%1").arg("");
                }
                namedBean = tr(/*locale,*/ "%1").arg(blockName);
                break;
            }
            case NamedBeanAddressing::Reference:
                namedBean = tr(/*locale,*/"by reference %1").arg(_reference);
                break;

            case NamedBeanAddressing::LocalVariable:
                namedBean = tr(/*locale,*/"by local variable %1").arg(_localVariable);
                break;

            case NamedBeanAddressing::Formula:
                namedBean = tr(/*locale,*/"by formulae %1").arg(_formula);
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        switch (_stateAddressing) {
        case NamedBeanAddressing::Direct:
                if (_blockState == ExpressionBlock::BlockState::ValueMatches) {
                    QString bundleKey = "Block \"%1\" value %2 to \"$3\"";
                    QString equalsString = _is_IsNot == Is_IsNot_Enum::Is ? tr("Block_Equal") : tr("is not equal");
                    switch (_dataAddressing) {
                        case NamedBeanAddressing::Direct:
                            return tr(/*locale,*/ "Block \"%1\" value %2 to \"$3\"").arg( namedBean, equalsString, _blockValue);
                        case NamedBeanAddressing::Reference:
                            return tr(/*locale,*/ "Block \"%1\" value %2 to \"$3\"").arg(namedBean, equalsString, tr("by reference %1").arg(_dataReference));
                        case NamedBeanAddressing::LocalVariable:
                            return tr(/*locale,*/ "Block \"%1\" value %2 to \"$3\"").arg(namedBean, equalsString, tr("by local variable %1").arg(_dataLocalVariable));
                        case NamedBeanAddressing::Formula:
                            return tr(/*locale,*/ "Block \"%1\" value %2 to \"$3\"").arg(namedBean, equalsString, tr("by formula %1").arg(_dataFormula));
                        default:
                            throw new IllegalArgumentException("invalid _dataAddressing state: " + NamedBeanAddressing::toString(_dataAddressing));
                    }
                } else if (_blockState == BlockState::Other) {
                    state = tr(/*locale,*/ "%1").arg(BlockState::toString(_blockState));
                    return tr(/*locale,*/ "Block \"%1\" %2 %3").arg(namedBean, "", state);
                } else {
                    state = tr(/*locale,*/"%1").arg(BlockState::toString(_blockState));
                }
               break;

            case NamedBeanAddressing::Reference:
                state = tr(/*locale,*/"by reference %1").arg(_stateReference);
                break;

            case NamedBeanAddressing::LocalVariable:
                state = tr(/*locale,*/"by local variable %1").arg( _stateLocalVariable);
                break;

            case NamedBeanAddressing::Formula:
                state = tr(/*locale,*/"by formulae %1").arg(_stateFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _stateAddressing state: " + NamedBeanAddressing::toString(_stateAddressing));
        }


        return tr(/*locale,*/ "Block \"%1\" %2 %3").arg(namedBean, Is_IsNot_Enum::toString(_is_IsNot), state);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionBlock::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionBlock::registerListenersForThisClass() {
        if (!_listenersAreRegistered && (_blockHandle != nullptr)) {
            _blockHandle->getBean()->addPropertyChangeListener(this);
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionBlock::unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {
            _blockHandle->getBean()->removePropertyChangeListener(this);
            _listenersAreRegistered = false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionBlock::propertyChange(PropertyChangeEvent* evt) {
    getConditionalNG()->execute();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionBlock::disposeMe() {
    }

//    /*public*/ enum BlockState {
//        Occupied(2, tr("Block_StateOccupied")),
//        NotOccupied(4, tr("Block_StateNotOccupied")),
//        Other(-1, tr("Block_StateOther")),
//        Allocated(-2, tr("Block_Allocated")),
//        ValueMatches(-3, tr("Block_ValueMatches"));

//        /*private*/ final int _id;
//        /*private*/ final String _text;

//        /*private*/ BlockState(int id, String text) {
//            this._id = id;
//            this._text = text;
//        }

//        /*public*/ int getID() {
//            return _id;
//        }

//        //@Override
//        /*public*/ String toString() {
//            return _text;
//        }
//    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionBlock::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
    log->debug(tr("getUsageReport :: ExpressionBlock: bean =%1, report = %2").arg(cdl->getDisplayName(), report->at(0)->usageData));
                if (getBlock() != nullptr && bean->equals(getBlock()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* ExpressionBlock::log = LoggerFactory::getLogger("ExpressionBlock");
