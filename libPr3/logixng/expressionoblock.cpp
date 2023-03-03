#include "expressionoblock.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "logixng/conditionalng.h"
#include "logixng/defaultdigitalexpressionmanager.h"
#include "logixng/recursivedescentparser.h"
#include "logixng/referenceutil.h"
#include "oblockmanager.h"
#include "vptr.h"
#include "typeconversionutil.h"

/**
 * This expression sets the state of a oblock.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/ class ExpressionOBlock extends AbstractDigitalExpression
//        implements PropertyChangeListener, VetoableChangeListener {


    /*public*/ ExpressionOBlock::ExpressionOBlock(QString sys, QString user, QObject *parent)
     : AbstractDigitalExpression(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
     this->setObjectName("ExpressionOBlock");
    }

    //@Override
    /*public*/ Base* ExpressionOBlock::getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws ParserException*/ {
        DigitalExpressionManager* manager = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"));
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ExpressionOBlock* copy = new ExpressionOBlock(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_oblockHandle != nullptr) copy->setOBlock(_oblockHandle);
        copy->setBeanState(_oblockState);
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

    /*public*/ void ExpressionOBlock::setOBlock(/*@Nonnull*/ QString oblockName) {
        assertListenersAreNotRegistered(log, "setOBlock");
        OBlock* oblock = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock(oblockName);
        if (oblock != nullptr) {
            setOBlock(oblock);
        } else {
            removeOBlock();
            log->error(tr("oblock \"%1\" is not found").arg(oblockName));
        }
    }

    /*public*/ void ExpressionOBlock::setOBlock(/*@Nonnull*/ NamedBeanHandle<OBlock *> *handle) {
        assertListenersAreNotRegistered(log, "setOBlock");
        _oblockHandle = handle;
        ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/ void ExpressionOBlock::setOBlock(/*@Nonnull*/ OBlock* oblock) {
        assertListenersAreNotRegistered(log, "setOBlock");
        setOBlock(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                  ->getNamedBeanHandle(oblock->getDisplayName(), oblock));
    }

    /*public*/ void ExpressionOBlock::removeOBlock() {
        assertListenersAreNotRegistered(log, "setOBlock");
        if (_oblockHandle != nullptr) {
            ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _oblockHandle = nullptr;
        }
    }

    /*public*/ NamedBeanHandle<OBlock*>* ExpressionOBlock::getOBlock() {
        return _oblockHandle;
    }

    /*public*/ void ExpressionOBlock::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ExpressionOBlock::getAddressing() {
        return _addressing;
    }

    /*public*/ void ExpressionOBlock::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/ QString ExpressionOBlock::getReference() {
        return _reference;
    }

    /*public*/ void ExpressionOBlock::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/ QString ExpressionOBlock::getLocalVariable() {
        return _localVariable;
    }

    /*public*/ void ExpressionOBlock::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _formula = formula;
        parseFormula();
    }

    /*public*/ QString ExpressionOBlock::getFormula() {
        return _formula;
    }

    /*private*/ void ExpressionOBlock::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*>  variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }

    /*public*/ void ExpressionOBlock::set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot) {
        _is_IsNot = is_IsNot;
    }

    /*public*/ Is_IsNot_Enum::VAL ExpressionOBlock::get_Is_IsNot() {
        return _is_IsNot;
    }

    /*public*/ void ExpressionOBlock::setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _stateAddressing = addressing;
        parseStateFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ExpressionOBlock::getStateAddressing() {
        return _stateAddressing;
    }

    /*public*/ void ExpressionOBlock::setBeanState(OBlock::OBlockStatus::STATES state) {
        _oblockState = state;
    }

    /*public*/ OBlock::OBlockStatus::STATES ExpressionOBlock::getBeanState() {
        return _oblockState;
    }

    /*public*/ void ExpressionOBlock::setStateReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _stateReference = reference;
    }

    /*public*/ QString ExpressionOBlock::getStateReference() {
        return _stateReference;
    }

    /*public*/ void ExpressionOBlock::setStateLocalVariable(/*@Nonnull*/ QString localVariable) {
        _stateLocalVariable = localVariable;
    }

    /*public*/ QString ExpressionOBlock::getStateLocalVariable() {
        return _stateLocalVariable;
    }

    /*public*/ void ExpressionOBlock::setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _stateFormula = formula;
        parseStateFormula();
    }

    /*public*/ QString ExpressionOBlock::getStateFormula() {
        return _stateFormula;
    }

    /*private*/ void ExpressionOBlock::parseStateFormula() /*throws ParserException*/ {
        if (_stateAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*>  variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _stateExpressionNode = parser->parseExpression(_stateFormula);
        } else {
            _stateExpressionNode = nullptr;
        }
    }

    //@Override
    /*public*/ void ExpressionOBlock::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<OBlock>::asPtr(evt->getOldValue() )) {
                if (VPtr<OBlock>::asPtr(evt->getOldValue())->equals(getOBlock()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("OBlock is in use by OBlock expression \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<OBlock>::asPtr(evt->getOldValue() )) {
                if (VPtr<OBlock>::asPtr(evt->getOldValue())->equals(getOBlock()->getBean())) {
                    removeOBlock();
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category ExpressionOBlock::getCategory() {
        return Category::ITEM;
    }

    /*private*/ QString ExpressionOBlock::getNewState() /*throws JmriException*/ {

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
    /*public*/ bool ExpressionOBlock::evaluate() /*throws JmriException*/ {
        OBlock* oblock;

        switch (_addressing) {
        case NamedBeanAddressing::Direct:
            oblock = _oblockHandle != nullptr ? _oblockHandle->getBean() : nullptr;
                break;

            case NamedBeanAddressing::Reference:
            {
                QString ref = ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _reference);
                oblock = (OBlock*)((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->
                        getNamedBean(ref)->self();
                break;
            }
            case NamedBeanAddressing::LocalVariable:
            {
            SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                oblock = (OBlock*)((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->
                        getNamedBean(TypeConversionUtil
                                     ::convertToString(symbolTable->getValue(_localVariable), false))->self();
                break;
            }
            case NamedBeanAddressing::Formula:
                oblock = _expressionNode != nullptr ?
                        (OBlock*)((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->
                                getNamedBean(TypeConversionUtil
                                             ::convertToString(_expressionNode->calculate(
                                                              getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        if (oblock == nullptr) {
//            log.warn("oblock is null");
            return false;
        }

        OBlock::OBlockStatus::STATES checkOBlockState;

        if (_stateAddressing == NamedBeanAddressing::Direct) {
            checkOBlockState = _oblockState;
        } else {
            checkOBlockState = OBlock::OBlockStatus::valueOf(getNewState());
        }

        int result = OBlock::OBlockStatus::getStatus((OBlock::OBlockStatus::STATES)((int)checkOBlockState & oblock->getState()));
        if (_is_IsNot == Is_IsNot_Enum::Is) {
            return result != 0;
        } else {
            return result == 0;
        }
    }

    //@Override
    /*public*/ FemaleSocket* ExpressionOBlock::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/ int ExpressionOBlock::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/ QString ExpressionOBlock::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "OBlock_Short");
    }

    //@Override
    /*public*/ QString ExpressionOBlock::getLongDescription(QLocale locale) {
        QString namedBean;
        QString state;

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
                throw new IllegalArgumentException("invalid _addressing state: " +NamedBeanAddressing::toString( _addressing));
        }

        switch (_stateAddressing) {
            case NamedBeanAddressing::Direct:
                state = tr(/*locale,*/ "%1").arg(OBlock::OBlockStatus::toString(_oblockState));
                break;

            case NamedBeanAddressing::Reference:
                state = tr(/*locale,*/ "by reference %1").arg(_stateReference);
                break;

            case NamedBeanAddressing::LocalVariable:
                state = tr(/*locale,*/ "by local variable %1").arg(_stateLocalVariable);
                break;

            case NamedBeanAddressing::Formula:
                state = tr(/*locale,*/ "by formulae %1").arg(_stateFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _stateAddressing state: " + NamedBeanAddressing::toString(_stateAddressing));
        }

        return tr(/*locale,*/ "OBlock %1 %2 %3").arg(namedBean, Is_IsNot_Enum::toString( _is_IsNot), state);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionOBlock::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionOBlock::registerListenersForThisClass() {
        if (!_listenersAreRegistered && (_oblockHandle != nullptr)) {
            _oblockHandle->getBean()->addPropertyChangeListener("state", this);
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionOBlock::unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {
            _oblockHandle->getBean()->removePropertyChangeListener("state", this);
            _listenersAreRegistered = false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionOBlock::propertyChange(PropertyChangeEvent* evt) {
    getConditionalNG()->execute();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionOBlock::disposeMe() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionOBlock::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
        log->debug(tr("getUsageReport :: ExpressionOBlock: bean = %1, report = %2").arg(cdl->getDisplayName(), report->at(0)->usageData));
                if (getOBlock() != nullptr && bean->equals(getOBlock()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* ExpressionOBlock::log = LoggerFactory::getLogger("ExpressionOBlock");
