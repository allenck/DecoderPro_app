#include "triggerroute.h"
#include "abstractroutemanager.h"
#include "defaultlogixmanager.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "logix.h"
#include "logixng/conditionalng.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/recursivedescentparser.h"
#include "logixng/variable.h"
#include "referenceutil.h"
#include "vptr.h"
#include "route.h"
#include "typeconversionutil.h"

/**
 * This action triggers a route.
 * <p>
 * This action has the Operation enum, similar to EnableLogix and other actions,
 * despite that's not needed since this action only has one option. But it's
 * here in case someone wants to add more options later.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class TriggerRoute extends AbstractDigitalAction implements VetoableChangeListener {


    /*public*/ TriggerRoute::TriggerRoute(QString sys, QString user, QObject* parent) : AbstractDigitalAction{sys, user, parent}
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
     setObjectName("TriggerRoute");
    }

    //@Override
    /*public*/ Base* TriggerRoute::getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws ParserException*/ {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        TriggerRoute* copy = new TriggerRoute(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_routeHandle != nullptr) copy->setRoute(_routeHandle);
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

    /*public*/ void TriggerRoute::setRoute(/*@Nonnull*/ QString routeName) {
        assertListenersAreNotRegistered(log, "setRoute");
        Route* route = ((AbstractRouteManager*)InstanceManager::getDefault("RouteManager"))->getRoute(routeName);
        if (route != nullptr) {
            setRoute(route);
        } else {
            removeRoute();
            log->error(tr("route \"%1\" is not found").arg(routeName));
        }
    }

    /*public*/ void TriggerRoute::setRoute(/*@Nonnull*/ NamedBeanHandle<Route*>* handle) {
        assertListenersAreNotRegistered(log, "setRoute");
        _routeHandle = handle;
        ((DefaultLogixManager*)InstanceManager::getDefault("LogixManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/ void TriggerRoute::setRoute(/*@Nonnull*/ Route* route) {
        assertListenersAreNotRegistered(log, "setRoute");
        setRoute(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                 ->getNamedBeanHandle(route->getDisplayName(), route));
    }

    /*public*/ void TriggerRoute::removeRoute() {
        assertListenersAreNotRegistered(log, "removeRoute");
        if (_routeHandle != nullptr) {
            ((DefaultLogixManager*)InstanceManager::getDefault("LogixManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _routeHandle = nullptr;
        }
    }

    /*public*/ NamedBeanHandle<Route*>* TriggerRoute::getRoute() {
        return _routeHandle;
    }

    /*public*/ void TriggerRoute::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE TriggerRoute::getAddressing() {
        return _addressing;
    }

    /*public*/ void TriggerRoute::setReference(/*@Nonnull*/ QString reference) {
    if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/ QString TriggerRoute::getReference() {
        return _reference;
    }

    /*public*/ void TriggerRoute::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/ QString TriggerRoute::getLocalVariable() {
        return _localVariable;
    }

    /*public*/ void TriggerRoute::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _formula = formula;
        parseFormula();
    }

    /*public*/ QString TriggerRoute::getFormula() {
        return _formula;
    }

    /*private*/ void TriggerRoute::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }

    /*public*/ void TriggerRoute::setOperationAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _operationAddressing = addressing;
        parseLockFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE TriggerRoute::getOperationAddressing() {
        return _operationAddressing;
    }

    /*public*/ void TriggerRoute::setOperationDirect(TriggerRoute::Operation::TYPE state) {
        _operationDirect = state;
    }

    /*public*/ TriggerRoute::Operation::TYPE TriggerRoute::getOperationDirect() {
        return _operationDirect;
    }

    /*public*/ void TriggerRoute::setOperationReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _operationReference = reference;
    }

    /*public*/ QString TriggerRoute::getOperationReference() {
        return _operationReference;
    }

    /*public*/ void TriggerRoute::setOperationLocalVariable(/*@Nonnull*/ QString localVariable) {
        _operationLocalVariable = localVariable;
    }

    /*public*/ QString TriggerRoute::getOperationLocalVariable() {
        return _operationLocalVariable;
    }

    /*public*/ void TriggerRoute::setOperationFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _operationFormula = formula;
        parseLockFormula();
    }

    /*public*/ QString TriggerRoute::getLockFormula() {
        return _operationFormula;
    }

    /*private*/ void TriggerRoute::parseLockFormula() /*throws ParserException*/ {
        if (_operationAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*> ();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _operationExpressionNode = parser->parseExpression(_operationFormula);
        } else {
            _operationExpressionNode = nullptr;
        }
    }

    //@Override
    /*public*/ void TriggerRoute::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<Logix>::asPtr(evt->getOldValue())) {
                if (VPtr<Logix>::asPtr(evt->getOldValue())->equals((Logix*)getRoute()->getBean()->self())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Route in use %1").arg(getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<Logix>::asPtr(evt->getOldValue())) {
                if (VPtr<Logix>::asPtr(evt->getOldValue())->equals((Logix*)getRoute()->getBean()->self())) {
                    removeRoute();
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category TriggerRoute::getCategory() {
        return Category::ITEM;
    }

    /*private*/ QString TriggerRoute::getNewLock() /*throws JmriException*/ {

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
    /*public*/ void TriggerRoute::execute() /*throws JmriException*/ {
        Route* route;

//        System.out.format("ActionEnableLogix.execute: %s%n", getLongDescription());

        switch (_addressing) {
        case NamedBeanAddressing::Direct:
            route = _routeHandle != nullptr ? _routeHandle->getBean() : nullptr;
                break;

        case NamedBeanAddressing::Reference:
        {
                QString ref = ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _reference);
                route = (Route*)((AbstractRouteManager*)InstanceManager::getDefault("RouteManager"))
                        ->getNamedBean(ref)->self();
                break;
        }
        case NamedBeanAddressing::LocalVariable:
        {
            SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                route = (Route*)((AbstractRouteManager*)InstanceManager::getDefault("RouteManager"))
                        ->getNamedBean(TypeConversionUtil
                                       ::convertToString(symbolTable->getValue(_localVariable), false))->self();
                break;
        }
        case NamedBeanAddressing::Formula:
                route = _expressionNode != nullptr ?
                       (Route*)((AbstractRouteManager*) InstanceManager::getDefault("RouteManager"))
                            ->getNamedBean(TypeConversionUtil
                                           ::convertToString(_expressionNode->calculate(
                                                                 getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

//        System.out.format("ActionEnableLogix.execute: route: %s%n", route);

        if (route == nullptr) {
//            log.error("route is null");
            return;
        }

        QString name = (_operationAddressing != NamedBeanAddressing::Direct)
                ? getNewLock() : nullptr;

        TriggerRoute::Operation::TYPE oper;
        if (_operationAddressing == NamedBeanAddressing::Direct) {
            oper = _operationDirect;
        } else {
            oper = Operation::valueOf(name);
        }

        // Variables used in lambda must be effectively final
        TriggerRoute::Operation::TYPE theOper = oper;
#if 0 // TODO:
        ThreadingUtil::runOnLayoutWithJmriException(() -> {
            if (theOper == Operation.TriggerRoute) {
                route.setRoute();
            } else {
                throw new IllegalArgumentException("invalid oper: " + oper.name());
            }
        });
#endif
    }

    //@Override
    /*public*/ FemaleSocket* TriggerRoute::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/ int TriggerRoute::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/ QString TriggerRoute::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "TriggerRoute_Short");
    }

    //@Override
    /*public*/ QString TriggerRoute::getLongDescription(QLocale locale) {
        QString namedBean;
        QString state;

        switch (_addressing) {
        case NamedBeanAddressing::Direct:
        {
                QString routeName;
                if (_routeHandle != nullptr) {
                    routeName = _routeHandle->getBean()->getDisplayName();
                } else {
                    routeName = tr(/*locale,*/ "BeanNotSelected");
                }
                namedBean = tr(/*locale,*/ "%1").arg(routeName);
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

        return tr(/*locale,*/ "Trigger route %1 to %2").arg(namedBean, state);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void TriggerRoute::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void TriggerRoute::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void TriggerRoute::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void TriggerRoute::disposeMe() {
    }


//    /*public*/ enum Operation {
//        TriggerRoute(Bundle.getMessage("TriggerRoute_TriggerRoute"));

//        /*private*/ /*final*/ QString _text;

//        /*private*/ Operation(String text) {
//            this._text = text;
//        }

//        //@Override
//        /*public*/ String toString() {
//            return _text;
//        }

//    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void TriggerRoute::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
    log->debug(tr("getUsageReport :: TriggerRoute: bean = %1, report = %2").arg(cdl->getDisplayName(), report->at(0)->usageData));
            if (getRoute() != nullptr && bean->equals((Logix*)getRoute()->getBean()->self())) {
        report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* TriggerRoute::log = LoggerFactory::getLogger("TriggerRoute");
