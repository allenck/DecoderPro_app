#include "expressionconditional.h"
#include "defaultconditionalmanager.h"
#include "instancemanager.h"
#include "logixng/defaultdigitalexpressionmanager.h"
#include "loggerfactory.h"
#include "logixng/recursivedescentparser.h"
#include "logixng/variable.h"
#include "referenceutil.h"
#include "defaultconditionalng.h"
#include "vptr.h"
#include "typeconversionutil.h"

/**
 * Evaluates the state of a Conditional.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/ class ExpressionConditional extends AbstractDigitalExpression
//        implements PropertyChangeListener, VetoableChangeListener {



    /*public*/ ExpressionConditional::ExpressionConditional(QString sys, QString user, QObject* parent)
            /*throws BadUserNameException, BadSystemNameException*/ : AbstractDigitalExpression(sys, user, parent){
        //super(sys, user);
    }

    //@Override
    /*public*/ Base* ExpressionConditional::getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws JmriException*/ {
        DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ExpressionConditional* copy = new ExpressionConditional(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->set_Is_IsNot(_is_IsNot);
//        if (_conditional != null) copy.setConditional(_conditional);
        if (_conditionalHandle != nullptr) copy->setConditional(_conditionalHandle);
        copy->setConditionalState(_conditionalState);
        return manager->registerExpression(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /*public*/ void ExpressionConditional::setConditional(/*@Nonnull*/ QString conditionalName) {
        assertListenersAreNotRegistered(log, "setConditional");
        Conditional* conditional = ((DefaultConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->getConditional(conditionalName);
        if (conditional != nullptr) {
            setConditional(conditional);
        } else {
            removeConditional();
            log->error(tr("conditional \"%1\" is not found").arg(conditionalName));
        }
    }

    /*public*/ void ExpressionConditional::setConditional(/*@Nonnull*/ NamedBeanHandle<Conditional*>* handle) {
        assertListenersAreNotRegistered(log, "setConditional");
        _conditionalHandle = handle;
        ((DefaultConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/ void ExpressionConditional::setConditional(/*@Nonnull*/ Conditional* conditional) {
        assertListenersAreNotRegistered(log, "setConditional");
        setConditional(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                       ->getNamedBeanHandle(conditional->getDisplayName(), conditional));
    }

    /*public*/ void ExpressionConditional::removeConditional() {
        assertListenersAreNotRegistered(log, "setConditional");
        if (_conditionalHandle != nullptr) {
            ((DefaultConditionalManager*)InstanceManager::getDefault("ConditionalManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _conditionalHandle = nullptr;
        }
    }

    /*public*/ NamedBeanHandle<Conditional*>* ExpressionConditional::getConditional() {
        return _conditionalHandle;
    }

    /*public*/ void ExpressionConditional::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ExpressionConditional::getAddressing() {
        return _addressing;
    }

    /*public*/ void ExpressionConditional::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/ QString ExpressionConditional::getReference() {
        return _reference;
    }

    /*public*/ void ExpressionConditional::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/ QString ExpressionConditional::getLocalVariable() {
        return _localVariable;
    }

    /*public*/ void ExpressionConditional::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _formula = formula;
        parseFormula();
    }

    /*public*/ QString ExpressionConditional::getFormula() {
        return _formula;
    }

    /*private*/ void ExpressionConditional::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }

    /*public*/ void ExpressionConditional::set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot) {
        _is_IsNot = is_IsNot;
    }

    /*public*/ Is_IsNot_Enum::VAL ExpressionConditional::get_Is_IsNot() {
        return _is_IsNot;
    }

    /*public*/ void ExpressionConditional::setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _stateAddressing = addressing;
        parseStateFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ExpressionConditional::getStateAddressing() {
        return _stateAddressing;
    }

    /*public*/ void ExpressionConditional::setConditionalState(ConditionalState::VAL state) {
        _conditionalState = state;
    }

    /*public*/ ExpressionConditional::ConditionalState::VAL ExpressionConditional::getConditionalState() {
        return _conditionalState;
    }

    /*public*/ void ExpressionConditional::setStateReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _stateReference = reference;
    }

    /*public*/ QString ExpressionConditional::getStateReference() {
        return _stateReference;
    }

    /*public*/ void ExpressionConditional::setStateLocalVariable(/*@Nonnull*/ QString localVariable) {
        _stateLocalVariable = localVariable;
    }

    /*public*/ QString ExpressionConditional::getStateLocalVariable() {
        return _stateLocalVariable;
    }

    /*public*/ void ExpressionConditional::setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _stateFormula = formula;
        parseStateFormula();
    }

    /*public*/ QString ExpressionConditional::getStateFormula() {
        return _stateFormula;
    }

    /*private*/ void ExpressionConditional::parseStateFormula() /*throws ParserException*/ {
        if (_stateAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*>  variables = QMap<QString, Variable*> ();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _stateExpressionNode = parser->parseExpression(_stateFormula);
        } else {
            _stateExpressionNode = nullptr;
        }
    }

    //@Override
    /*public*/ void ExpressionConditional::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<Conditional>::asPtr(evt->getOldValue())) {
                if (VPtr<Conditional>::asPtr(evt->getOldValue())->equals(getConditional())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Conditional is in use by Conditional expression \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete" ==(evt->getPropertyName())) { // No I18N
            if (VPtr<Conditional>::asPtr(evt->getOldValue())) {
                if (VPtr<Conditional>::asPtr(evt->getOldValue())->equals(getConditional())) {
                    removeConditional();
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category ExpressionConditional::getCategory() {
        return Category::ITEM;
    }

    /*private*/ QString ExpressionConditional::getNewState() /*throws JmriException*/ {

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
    /*public*/ bool ExpressionConditional::evaluate() /*throws JmriException*/ {
        Conditional* conditional;

//        System.out.format("ExpressionConditional.execute: %s%n", getLongDescription());

        switch (_addressing) {
        case NamedBeanAddressing::Direct:
            conditional = _conditionalHandle != nullptr ? _conditionalHandle->getBean() : nullptr;
                break;

            case NamedBeanAddressing::Reference:
            {
                QString ref = ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _reference);
                conditional = (Conditional*)((DefaultConditionalManager*)InstanceManager::getDefault("ConditionalManager"))
                        ->getNamedBean(ref)->self();
                break;
            }
            case NamedBeanAddressing::LocalVariable:
            {
            SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                conditional = (Conditional*)((DefaultConditionalManager*)InstanceManager::getDefault("ConditionalManager"))
                        ->getNamedBean(TypeConversionUtil
                                      ::convertToString(symbolTable->getValue(_localVariable), false))->self();
                break;
            }
            case NamedBeanAddressing::Formula:
                conditional = _expressionNode != nullptr ?
                        (Conditional*)((DefaultConditionalManager*)InstanceManager::getDefault("ConditionalManager"))
                            ->getNamedBean(TypeConversionUtil
                                           ::convertToString(_expressionNode->calculate(
                                                                 getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

//        System.out.format("ExpressionConditional.execute: conditional: %s%n", conditional);

        if (conditional == nullptr) {
//            log.warn("conditional is null");
            return false;
        }

        ConditionalState::VAL checkConditionalState;

        if (_stateAddressing == NamedBeanAddressing::Direct) {
            checkConditionalState = _conditionalState;
        } else {
            checkConditionalState = ConditionalState::valueOf(getNewState());
        }

        if (_is_IsNot == Is_IsNot_Enum::Is) {
            return conditional->getState() == checkConditionalState;
        } else {
            return conditional->getState() != checkConditionalState;
        }
    }

    //@Override
    /*public*/ FemaleSocket* ExpressionConditional::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/ int ExpressionConditional::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/ QString ExpressionConditional::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Conditional");
    }

    //@Override
    /*public*/ QString ExpressionConditional::getLongDescription(QLocale locale) {
        QString namedBean;
        QString state;

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
            {
                QString conditionalName;
                if (_conditionalHandle != nullptr) {
                    conditionalName = _conditionalHandle->getBean()->getDisplayName();
                } else {
                    conditionalName = tr(/*locale,*/ "BeanNotSelected");
                }
                namedBean = tr(/*locale,*/ "%1").arg(conditionalName);
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

        switch (_stateAddressing) {
            case NamedBeanAddressing::Direct:
                state = tr(/*locale,*/ "%1").arg(ExpressionConditional::ConditionalState::toString(_conditionalState));
                break;

            case NamedBeanAddressing::Reference:
                state = tr(/*locale,*/ "by reference %1").arg(_stateReference);
                break;

            case NamedBeanAddressing::LocalVariable:
                state = tr(/*locale,*/ "by local variable %1").arg(_stateLocalVariable);
                break;

            case NamedBeanAddressing::Formula:
                state = tr(/*locale,*/ "by formula %1").arg(_stateFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _stateAddressing state: " + NamedBeanAddressing::toString(_stateAddressing));
        }

        return tr(/*locale,*/ "Conditional {0} {1} {2}").arg(namedBean, Is_IsNot_Enum::toString(_is_IsNot), state);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionConditional::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionConditional::registerListenersForThisClass() {
        if (!_listenersAreRegistered && (_conditionalHandle != nullptr)) {
            _conditionalHandle->getBean()->addPropertyChangeListener("KnownState", this);
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionConditional::unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {
            _conditionalHandle->getBean()->removePropertyChangeListener("KnownState", this);
            _listenersAreRegistered = false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionConditional::propertyChange(PropertyChangeEvent* evt) {
    getConditionalNG()->execute();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionConditional::disposeMe() {
    }



//    /*public*/ enum ConditionalState {
//        False(Conditional.FALSE, Bundle.getMessage("ConditionalStateFalse")),
//        True(Conditional.TRUE, Bundle.getMessage("ConditionalStateTrue")),
//        Other(-1, Bundle.getMessage("ConditionalOtherStatus"));

//        /*private*/ final int _id;
//        /*private*/ final String _text;

//        /*private*/ ConditionalState(int id, String text) {
//            this._id = id;
//            this._text = text;
//        }

//        static /*public*/ ConditionalState get(int id) {
//            switch (id) {
//                case Conditional.FALSE:
//                    return False;

//                case Conditional.TRUE:
//                    return True;

//                default:
//                    return Other;
//            }
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
    /*public*/ void ExpressionConditional::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
    log->debug(tr("getUsageReport :: ExpressionConditional: bean = %1, report = %2").arg(cdl->getDisplayName(), report->at(0)->usageData));
    if (getConditional() != nullptr && bean->equals(getConditional()->getBean())) {
        report->append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* ExpressionConditional::log = LoggerFactory::getLogger("ExpressionConditional");
