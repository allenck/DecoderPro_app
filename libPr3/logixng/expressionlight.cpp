#include "expressionlight.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "proxylightmanager.h"
#include "conditionalng.h"
#include "namedbeanhandlemanager.h"
#include "referenceutil.h"
#include "recursivedescentparser.h"
#include "vptr.h"
#include "typeconversionutil.h"

/**
 * This expression sets the state of a light.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class ExpressionLight extends AbstractDigitalExpression
//        implements PropertyChangeListener, VetoableChangeListener {


    /*public*/  ExpressionLight::ExpressionLight(QString sys, QString user, QObject *parent) : AbstractDigitalExpression(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
      setObjectName("ExpressionLight");
    }

    //@Override
    /*public*/  Base* ExpressionLight::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/ {
        DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ExpressionLight* copy = new ExpressionLight(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_lightHandle != nullptr) copy->setLight(_lightHandle);
        copy->setBeanState(_lightState);
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

    /*public*/  void ExpressionLight::setLight(/*@Nonnull*/ QString lightName) {
        assertListenersAreNotRegistered(log, "setLight");
        Light* light = ((ProxyLightManager*)InstanceManager::getDefault("LightManager"))->getLight(lightName);
        if (light != nullptr) {
            setLight(light);
        } else {
            removeLight();
            log->error(tr("light \"%1\" is not found").arg(lightName));
        }
    }

    /*public*/  void ExpressionLight::setLight(/*@Nonnull*/ NamedBeanHandle<Light*>* handle) {
        assertListenersAreNotRegistered(log, "setLight");
        _lightHandle = handle;
        InstanceManager::lightManagerInstance()->addVetoableChangeListener(this);
    }

    /*public*/  void ExpressionLight::setLight(/*@Nonnull*/ Light* light) {
        assertListenersAreNotRegistered(log, "setLight");
        setLight(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(light->getDisplayName(), light));
    }

    /*public*/  void ExpressionLight::removeLight() {
        assertListenersAreNotRegistered(log, "setLight");
        if (_lightHandle != nullptr) {
            InstanceManager::lightManagerInstance()->removeVetoableChangeListener(this);
            _lightHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<Light*>* ExpressionLight::getLight() {
        return _lightHandle;
    }

    /*public*/  void ExpressionLight::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ExpressionLight::getAddressing() {
        return _addressing;
    }

    /*public*/  void ExpressionLight::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/  QString ExpressionLight::getReference() {
        return _reference;
    }

    /*public*/  void ExpressionLight::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/  QString ExpressionLight::getLocalVariable() {
        return _localVariable;
    }

    /*public*/  void ExpressionLight::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException */{
        _formula = formula;
        parseFormula();
    }

    /*public*/  QString ExpressionLight::getFormula() {
        return _formula;
    }

    /*private*/ void ExpressionLight::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }

    /*public*/  void ExpressionLight::set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot) {
        _is_IsNot = is_IsNot;
    }

    /*public*/  Is_IsNot_Enum::VAL ExpressionLight::get_Is_IsNot() {
        return _is_IsNot;
    }

    /*public*/  void ExpressionLight::setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _stateAddressing = addressing;
        parseStateFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ExpressionLight::getStateAddressing() {
        return _stateAddressing;
    }

    /*public*/  void ExpressionLight::setBeanState(LightState::VALS state) {
        _lightState = state;
    }

    /*public*/  ExpressionLight::LightState::VALS ExpressionLight::getBeanState() {
        return _lightState;
    }

    /*public*/  void ExpressionLight::setStateReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _stateReference = reference;
    }

    /*public*/  QString ExpressionLight::getStateReference() {
        return _stateReference;
    }

    /*public*/  void ExpressionLight::setStateLocalVariable(/*@Nonnull*/ QString localVariable) {
        _stateLocalVariable = localVariable;
    }

    /*public*/  QString ExpressionLight::getStateLocalVariable() {
        return _stateLocalVariable;
    }

    /*public*/  void ExpressionLight::setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _stateFormula = formula;
        parseStateFormula();
    }

    /*public*/  QString ExpressionLight::getStateFormula() {
        return _stateFormula;
    }

    /*private*/ void ExpressionLight::parseStateFormula() /*throws ParserException*/ {
        if (_stateAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _stateExpressionNode = parser->parseExpression(_stateFormula);
        } else {
            _stateExpressionNode = nullptr;
        }
    }

    //@Override
    /*public*/  void ExpressionLight::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<Light>::asPtr(evt->getOldValue())) {
                if (VPtr<Light>::asPtr(evt->getOldValue())->equals( (getLight()->getBean()->self()))) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Light is in use by Light expression \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<Light>::asPtr(evt->getOldValue())) {
                if (VPtr<Light>::asPtr(evt->getOldValue())->equals(getLight()->getBean()->self())) {
                    removeLight();
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category ExpressionLight::getCategory() {
        return Category::ITEM;
    }

    /*private*/ QString ExpressionLight::getNewState() /*throws JmriException*/ {

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
    /*public*/  bool ExpressionLight::evaluate() /*throws JmriException*/ {
        Light* light;

//        System.out.format("ExpressionLight.execute: %s%n", getLongDescription());

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
                light = _lightHandle != nullptr ? _lightHandle->getBean() : nullptr;
                break;

            case NamedBeanAddressing::Reference:
           {
                QString ref = ReferenceUtil::getReference(
                        getConditionalNG()->getSymbolTable(), _reference);
                light =(Light*) ((ProxyLightManager*)InstanceManager::getDefault("LightManager"))
                        ->AbstractProxyManager::getNamedBean(ref)->self();
                break;
            }
            case NamedBeanAddressing::LocalVariable:
            {
                SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                light = (Light*)((ProxyLightManager*)InstanceManager::getDefault("LightManager"))
                        ->AbstractProxyManager::getNamedBean(TypeConversionUtil
                                ::convertToString(symbolTable->getValue(_localVariable), false))->self();
                break;
            }
            case NamedBeanAddressing::Formula:
                light = _expressionNode != nullptr ?(Light*)
                        ((ProxyLightManager*)InstanceManager::getDefault("LightManager"))
                                ->AbstractProxyManager::getNamedBean(TypeConversionUtil
                                        ::convertToString(_expressionNode->calculate(
                                                getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

//        System.out.format("ExpressionLight.execute: light: %s%n", light);

        if (light == nullptr) {
//            log.warn("light is null");
            return false;
        }

        LightState::VALS checkLightState;

        if (_stateAddressing == NamedBeanAddressing::Direct) {
            checkLightState = _lightState;
        } else {
            checkLightState = LightState::valueOf(getNewState());
        }

        LightState::VALS currentLightState = LightState::get((Light::STATES)light->getKnownState());
        if (_is_IsNot == Is_IsNot_Enum::Is) {
            return currentLightState == checkLightState;
        } else {
            return currentLightState != checkLightState;
        }
    }

    //@Override
    /*public*/  FemaleSocket* ExpressionLight::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */{
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int ExpressionLight::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString ExpressionLight::getShortDescription(QLocale locale) {
        return  tr(/*locale,*/ "Light");
    }

    //@Override
    /*public*/  QString ExpressionLight::getLongDescription(QLocale locale) {
        QString namedBean;
        QString state;

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
            {
                QString lightName;
                if (_lightHandle != nullptr) {
                    lightName = _lightHandle->getBean()->getDisplayName();
                } else {
                    lightName = tr( "''");
                }
                namedBean =  tr(/*locale,*/ "%1").arg(lightName);
                break;
}
            case NamedBeanAddressing::Reference:
                namedBean =  tr(/*locale,*/ "by reference %1").arg(_reference);
                break;/*locale,*/

            case NamedBeanAddressing::LocalVariable:
                namedBean =  tr(/*locale,*/  "by local variable %1").arg(_localVariable);
                break;

            case NamedBeanAddressing::Formula:
                namedBean =  tr(/*locale,*/ "by formula %1").arg(_formula);
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        switch (_stateAddressing) {
            case NamedBeanAddressing::Direct:
                state =  tr(/*locale,*/ "%1").arg(LightState::toString(_lightState));
                break;

            case NamedBeanAddressing::Reference:
                state =  tr(/*locale,*/ "by reference %1").arg(_stateReference);
                break;

            case NamedBeanAddressing::LocalVariable:
                state =  tr(/*locale,*/  "by local variable %1").arg(_stateLocalVariable);
                break;

            case NamedBeanAddressing::Formula:
                state =  tr(/*locale,*/  "by formula %1").arg(_stateFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _stateAddressing state: " + NamedBeanAddressing::toString(_stateAddressing));
        }

        return  tr(/*locale,*/ "Light %1 %2 %3").arg(namedBean, Is_IsNot_Enum::toString(_is_IsNot), state);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionLight::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionLight::registerListenersForThisClass() {
        if (!_listenersAreRegistered && (_lightHandle != nullptr)) {
            _lightHandle->getBean()->addPropertyChangeListener("KnownState", this);
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionLight::unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {
            _lightHandle->getBean()->removePropertyChangeListener("KnownState", this);
            _listenersAreRegistered = false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionLight::propertyChange(PropertyChangeEvent* evt) {
        getConditionalNG()->execute();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionLight::disposeMe() {
    }



    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionLight::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport *> *report, NamedBean* cdl) {
        log->debug(tr("getUsageReport :: ExpressionLight: bean = %1, report = %2").arg(cdl->getDisplayName()).arg(report->size()));
        if (getLight() != nullptr && bean->equals(getLight()->getBean()->self())) {
            report->append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription(QLocale())));
        }
    }
    /*private*/ /*final*/ /*static*/ Logger* ExpressionLight::log = LoggerFactory::getLogger("ExpressionLight");
