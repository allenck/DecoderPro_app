#include "actionentryexit.h"
#include "conditionalng.h"
#include "defaultdigitalactionmanager.h"
#include "defaultlogixmanager.h"
#include "destinationpoints.h"
#include "entryexitpairs.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "recursivedescentparser.h"
#include "referenceutil.h"
#include "variable.h"
#include "vptr.h"
#include "typeconversionutil.h"

/**
 * This action triggers a entryExit.
 * <p>
 * This action has the Operation enum, similar to EnableLogix and other actions,
 * despite that's not needed since this action only has one option. But it's
 * here in case someone wants to add more options later.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class ActionEntryExit extends AbstractDigitalAction implements VetoableChangeListener {


    /*public*/ ActionEntryExit::ActionEntryExit(QString sys, QString user, QObject* parent) :AbstractDigitalAction(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
    }

    //@Override
    /*public*/ Base* ActionEntryExit::getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws ParserException*/ {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ActionEntryExit* copy = new ActionEntryExit(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_destinationPointsHandle != nullptr) copy->setDestinationPoints(_destinationPointsHandle);
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

    /*public*/ void ActionEntryExit::setDestinationPoints(/*@Nonnull*/ QString entryExitName) {
        assertListenersAreNotRegistered(log, "setDestinationPoints");
        DestinationPoints* entryExit = (DestinationPoints*)((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))->getNamedBean(entryExitName)->self();
        if (entryExit != nullptr) {
            setDestinationPoints(entryExit);
        } else {
            removeDestinationPoints();
            log->error(tr("DestinationPoints \"%1\" is not found").arg(entryExitName));
        }
    }

    /*public*/ void ActionEntryExit::setDestinationPoints(/*@Nonnull*/ NamedBeanHandle<DestinationPoints*>* handle) {
        assertListenersAreNotRegistered(log, "setDestinationPoints");
        _destinationPointsHandle = handle;
        ((DefaultLogixManager*)InstanceManager::getDefault("LogixManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/ void ActionEntryExit::setDestinationPoints(/*@Nonnull*/ DestinationPoints* entryExit) {
        assertListenersAreNotRegistered(log, "setDestinationPoints");
        setDestinationPoints(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                             ->getNamedBeanHandle(entryExit->getDisplayName(), entryExit));
    }

    /*public*/ void ActionEntryExit::removeDestinationPoints() {
        assertListenersAreNotRegistered(log, "removeEntryExit");
        if (_destinationPointsHandle != nullptr) {
            ((DefaultLogixManager*)InstanceManager::getDefault("LogixManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _destinationPointsHandle = nullptr;
        }
    }

    /*public*/ NamedBeanHandle<DestinationPoints*>* ActionEntryExit::getDestinationPoints() {
        return _destinationPointsHandle;
    }

    /*public*/ void ActionEntryExit::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ActionEntryExit::getAddressing() {
        return _addressing;
    }

    /*public*/ void ActionEntryExit::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/ QString ActionEntryExit::getReference() {
        return _reference;
    }

    /*public*/ void ActionEntryExit::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/ QString ActionEntryExit::getLocalVariable() {
        return _localVariable;
    }

    /*public*/ void ActionEntryExit::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _formula = formula;
        parseFormula();
    }

    /*public*/ QString ActionEntryExit::getFormula() {
        return _formula;
    }

    /*private*/ void ActionEntryExit::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*>  variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }

    /*public*/ void ActionEntryExit::setOperationAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _operationAddressing = addressing;
        parseLockFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ActionEntryExit::getOperationAddressing() {
        return _operationAddressing;
    }

    /*public*/ void ActionEntryExit::setOperationDirect(Operation::TYPE state) {
        _operationDirect = state;
    }

    /*public*/ ActionEntryExit::Operation::TYPE ActionEntryExit::getOperationDirect() {
    return _operationDirect;
    }

    /*public*/ void ActionEntryExit::setOperationReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _operationReference = reference;
    }

    /*public*/ QString ActionEntryExit::getOperationReference() {
        return _operationReference;
    }

    /*public*/ void ActionEntryExit::setOperationLocalVariable(/*@Nonnull*/ QString localVariable) {
        _operationLocalVariable = localVariable;
    }

    /*public*/ QString ActionEntryExit::getOperationLocalVariable() {
        return _operationLocalVariable;
    }

    /*public*/ void ActionEntryExit::setOperationFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _operationFormula = formula;
        parseLockFormula();
    }

    /*public*/ QString ActionEntryExit::getLockFormula() {
        return _operationFormula;
    }

    /*private*/ void ActionEntryExit::parseLockFormula() /*throws ParserException*/ {
        if (_operationAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*>  variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _operationExpressionNode = parser->parseExpression(_operationFormula);
        } else {
            _operationExpressionNode = nullptr;
        }
    }

    //@Override
    /*public*/ void ActionEntryExit::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<DestinationPoints>::asPtr(evt->getOldValue() )) {
                if (VPtr<DestinationPoints>::asPtr(evt->getOldValue())->equals(getDestinationPoints()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Destination points is in use by Set Entry/Exit action \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<DestinationPoints>::asPtr(evt->getOldValue())) {
                if (VPtr<DestinationPoints>::asPtr(evt->getOldValue())->equals(getDestinationPoints()->getBean())) {
                    removeDestinationPoints();
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category ActionEntryExit::getCategory() {
        return Category::ITEM;
    }

    /*private*/ QString ActionEntryExit::getNewLock() /*throws JmriException*/ {

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
    /*public*/ void ActionEntryExit::execute() /*throws JmriException*/ {
        DestinationPoints* entryExit;

//        System.out.format("ActionEnableLogix.execute: %s%n", getLongDescription());

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
            entryExit = _destinationPointsHandle != nullptr ? _destinationPointsHandle->getBean() : nullptr;
                break;

            case NamedBeanAddressing::Reference:
            {
                QString ref = ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _reference);
                entryExit = (DestinationPoints*) ((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))
                             ->getNamedBean(ref)->self();
                break;
            }
            case NamedBeanAddressing::LocalVariable:
            {
                SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                entryExit = (DestinationPoints*) ((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))
                        ->getNamedBean(TypeConversionUtil
                                      ::convertToString(symbolTable->getValue(_localVariable), false))->self();
                break;
            }
            case NamedBeanAddressing::Formula:
                entryExit = _expressionNode != nullptr ?
                        (DestinationPoints*) ((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))
                            ->getNamedBean(TypeConversionUtil
                                           ::convertToString(_expressionNode->calculate(
                                                              getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

//        System.out.format("ActionEnableLogix.execute: entryExit: %s%n", entryExit);

        if (entryExit == nullptr) {
//            log.error("entryExit is null");
            return;
        }

        QString name = (_operationAddressing != NamedBeanAddressing::Direct)
                ? getNewLock() : nullptr;

        Operation::TYPE oper;
        if (_operationAddressing == NamedBeanAddressing::Direct) {
            oper = _operationDirect;
        } else {
            oper = Operation::valueOf(name);
        }

        // Variables used in lambda must be effectively final
        Operation::TYPE theOper = oper;
#if 0
        ThreadingUtil.runOnLayoutWithJmriException(() -> {
            switch (theOper) {
                case SetNXPairEnabled:
                    entryExit.setEnabled(true);
                    break;
                case SetNXPairDisabled:
                    entryExit.setEnabled(false);
                    break;
                case SetNXPairSegment:
                    jmri.InstanceManager.getDefault(jmri.jmrit.entryexit.EntryExitPairs.class).
                            setSingleSegmentRoute(entryExit.getSystemName());
                    break;
                default:
                    throw new IllegalArgumentException("invalid oper state: " + theOper.name());
            }
        });
#endif
    }

    //@Override
    /*public*/ FemaleSocket* ActionEntryExit::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/ int ActionEntryExit::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/ QString ActionEntryExit::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "ActionEntryExit");
    }

    //@Override
    /*public*/ QString ActionEntryExit::getLongDescription(QLocale locale) {
        QString namedBean;
        QString state;

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
        {
                QString entryExitName;
                if (_destinationPointsHandle != nullptr) {
                    entryExitName = _destinationPointsHandle->getBean()->getDisplayName();
                } else {
                    entryExitName = tr(/*locale,*/ "BeanNotSelected");
                }
                namedBean = tr(/*locale,*/ "%1").arg(entryExitName);
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
                state = tr(/*locale,*/ "%1").arg(Operation::toString(_operationDirect));
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

        return tr(/*locale,*/ "Set Entry/Exit %1 to %2").arg(namedBean, state);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionEntryExit::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionEntryExit::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionEntryExit::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionEntryExit::disposeMe() {
    }


//    /*public*/ enum Operation {
//        SetNXPairEnabled(Bundle.getMessage("ActionEntryExit_SetNXPairEnabled")),
//        SetNXPairDisabled(Bundle.getMessage("ActionEntryExit_SetNXPairDisabled")),
//        SetNXPairSegment(Bundle.getMessage("ActionEntryExit_SetNXPairSegment"));

//        /*private*/ final QString _text;

//        /*private*/ Operation(QString text) {
//            this._text = text;
//        }

//        //@Override
//        /*public*/ QString toString() {
//            return _text;
//        }

//    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionEntryExit::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
    log->debug(tr("getUsageReport :: ActionEntryExit: bean = %1, report = %2").arg(cdl->getComment(), report->at(0)->usageData));
            if (getDestinationPoints() != nullptr && bean->equals(getDestinationPoints()->getBean())) {
        report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* ActionEntryExit::log = LoggerFactory::getLogger("ActionEntryExit");

