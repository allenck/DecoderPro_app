#include "actionlight.h"
#include "loggerfactory.h"
#include "defaultdigitalactionmanager.h"
#include "instancemanager.h"
#include "proxylightmanager.h"
#include "recursivedescentparser.h"
#include "referenceutil.h"
#include "vptr.h"
#include "defaultconditionalng.h"
#include "typeconversionutil.h"

/**
 * This action sets the state of a light.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
// /*public*/  class ActionLight extends AbstractDigitalAction implements VetoableChangeListener {

    /*public*/  ActionLight::ActionLight(QString sys, QString user, QObject *parent) : AbstractDigitalAction(sys, user, parent)
//            throws BadUserNameException, BadSystemNameException
    {
//      super(sys, user);
     setObjectName("ActionLight");
    }
#if 1
    //@Override
    /*public*/  Base* ActionLight::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/ {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ActionLight* copy = new ActionLight(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_lightHandle != nullptr) copy->setLight(_lightHandle);
        copy->setBeanState(_lightState);
        copy->setAddressing(_addressing);
        copy->setFormula(_formula);
        copy->setLocalVariable(_localVariable);
        copy->setReference(_reference);

        copy->setStateAddressing(_stateAddressing);
        copy->setStateFormula(_stateFormula);
        copy->setStateLocalVariable(_stateLocalVariable);
        copy->setStateReference(_stateReference);

        copy->setDataAddressing(_dataAddressing);
        copy->setDataReference(_dataReference);
        copy->setDataLocalVariable(_dataLocalVariable);
        copy->setDataFormula(_dataFormula);

        copy->setLightValue(_lightValue);

        return manager->registerAction(copy);
    }

    /*public*/  void ActionLight::setLight(/*@Nonnull*/ QString lightName) {
        assertListenersAreNotRegistered(log, "setLight");
        Light* light = ((ProxyLightManager*)InstanceManager::getDefault("LightManager"))->getLight(lightName);
        if (light != nullptr) {
            setLight(light);
        } else {
            removeLight();
            log->warn(tr("light \"%1\" is not found").arg(lightName));
        }
    }

    /*public*/  void ActionLight::setLight(/*@Nonnull*/ NamedBeanHandle<Light*>* handle) {
        assertListenersAreNotRegistered(log, "setLight");
        _lightHandle = handle;
        ((ProxyLightManager*)InstanceManager::getDefault("LightManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/  void ActionLight::setLight(/*@Nonnull*/ Light* light) {
        assertListenersAreNotRegistered(log, "setLight");
        setLight(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(light->getDisplayName(), light));
    }

    /*public*/  void ActionLight::removeLight() {
        assertListenersAreNotRegistered(log, "setLight");
        if (_lightHandle != nullptr) {
            ((ProxyLightManager*)InstanceManager::getDefault("LightManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _lightHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<Light*>* ActionLight::getLight() {
        return _lightHandle;
    }

    /*public*/  void ActionLight::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException */{
        _addressing = addressing;
        parseFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ActionLight::getAddressing() {
        return _addressing;
    }

    /*public*/  void ActionLight::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/  QString ActionLight::getReference() {
        return _reference;
    }

    /*public*/  void ActionLight::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/  QString ActionLight::getLocalVariable() {
        return _localVariable;
    }

    /*public*/  void ActionLight::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _formula = formula;
        parseFormula();
    }

    /*public*/  QString ActionLight::getFormula() {
        return _formula;
    }

    /*private*/ void ActionLight::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }


    /*public*/  void ActionLight::setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _stateAddressing = addressing;
        parseStateFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ActionLight::getStateAddressing() {
        return _stateAddressing;
    }

    /*public*/  void ActionLight::setBeanState(ActionLight::LightState::STATE state) {
        _lightState = state;
    }

    /*public*/  ActionLight::LightState::STATE ActionLight::getBeanState() {
        return _lightState;
    }

    /*public*/  void ActionLight::setStateReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _stateReference = reference;
    }

    /*public*/  QString ActionLight::getStateReference() {
        return _stateReference;
    }

    /*public*/  void ActionLight::setStateLocalVariable(/*@Nonnull*/ QString localVariable) {
        _stateLocalVariable = localVariable;
    }

    /*public*/  QString ActionLight::getStateLocalVariable() {
        return _stateLocalVariable;
    }

    /*public*/  void ActionLight::setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _stateFormula = formula;
        parseStateFormula();
    }

    /*public*/  QString ActionLight::getStateFormula() {
        return _stateFormula;
    }

    /*private*/ void ActionLight::parseStateFormula() /*throws ParserException*/ {
        if (_stateAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _stateExpressionNode = parser->parseExpression(_stateFormula);
        } else {
            _stateExpressionNode = nullptr;
        }
    }


    /*public*/  void ActionLight::setDataAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _dataAddressing = addressing;
        parseDataFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ActionLight::getDataAddressing() {
        return _dataAddressing;
    }

    /*public*/  void ActionLight::setDataReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _dataReference = reference;
    }

    /*public*/  QString ActionLight::getDataReference() {
        return _dataReference;
    }

    /*public*/  void ActionLight::setDataLocalVariable(/*@Nonnull*/ QString localVariable) {
        _dataLocalVariable = localVariable;
    }

    /*public*/  QString ActionLight::getDataLocalVariable() {
        return _dataLocalVariable;
    }

    /*public*/  void ActionLight::setDataFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _dataFormula = formula;
        parseDataFormula();
    }

    /*public*/  QString ActionLight::getDataFormula() {
        return _dataFormula;
    }

    /*private*/ void ActionLight::parseDataFormula() /*throws ParserException*/ {
        if (_dataAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _dataExpressionNode = parser->parseExpression(_dataFormula);
        } else {
            _dataExpressionNode = nullptr;
        }
    }


    /*public*/  void ActionLight::setLightValue(int value) {
        _lightValue = value;
    }

    /*public*/  int ActionLight::getLightValue() {
        return _lightValue;
    }


    //@Override
    /*public*/  void ActionLight::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<Light>::asPtr(evt->getOldValue())) {
                if (VPtr<Light>::asPtr(evt->getOldValue())->equals(getLight()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Light is in use by Light action \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete"==(evt->getPropertyName())) { // No I18N
            if (VPtr<Light>::asPtr(evt->getOldValue())) {
                if (VPtr<Light>::asPtr(evt->getOldValue())->equals(getLight()->getBean())) {
                    removeLight();
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category* ActionLight::getCategory() {
        return Category::ITEM;
    }

    /*private*/ QString ActionLight::getNewState() /*throws JmriException*/ {

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

    /*private*/ int ActionLight::getNewData() /*throws JmriException*/ {
        QString newValue = "";

        switch (_dataAddressing) {
            case NamedBeanAddressing::Direct:
                return _lightValue;

            case NamedBeanAddressing::Reference:
                newValue = ReferenceUtil::getReference(
                        getConditionalNG()->getSymbolTable(), _dataReference);
                break;

            case NamedBeanAddressing::LocalVariable:
            {
                SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                newValue = TypeConversionUtil
                        ::convertToString(symbolTable->getValue(_dataLocalVariable), false);
                break;
            }
            case NamedBeanAddressing::Formula:
                newValue = _dataExpressionNode != nullptr
                        ? TypeConversionUtil::convertToString(
                                _dataExpressionNode->calculate(
                                        getConditionalNG()->getSymbolTable()), false)
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_dataAddressing));
        }
        try {
         bool ok;
            int newInt = newValue.toInt(&ok); if(!ok) throw new NumberFormatException()
;            if (newInt < 0) newInt = 0;
            if (newInt > 100) newInt = 100;
            return newInt;
        } catch (NumberFormatException* ex) {
            return 0;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionLight::execute() /*throws JmriException*/ {
        Light* light;

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
                light = _lightHandle != nullptr ? _lightHandle->getBean() : nullptr;
                break;

            case NamedBeanAddressing::Reference:
            {
                QString ref = ReferenceUtil::getReference(
                        getConditionalNG()->getSymbolTable(), _reference);
                light = (Light*)((ProxyLightManager*)InstanceManager::getDefault("LightManager"))
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
                light = _expressionNode != nullptr ?
                        (Light*)((ProxyLightManager*)InstanceManager::getDefault("LightManager"))
                                ->AbstractProxyManager::getNamedBean(TypeConversionUtil
                                        ::convertToString(_expressionNode->calculate(
                                                getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " +NamedBeanAddressing::toString( _addressing));
        }

        if (light == nullptr) {
//            log.warn("light is null");
            return;
        }

        QString name = (_stateAddressing != NamedBeanAddressing::Direct)
                ? getNewState() : nullptr;

        ActionLight::LightState::STATE state;
        if ((_stateAddressing == NamedBeanAddressing::Direct)) {
            state = _lightState;
        } else {
            state = ActionLight::LightState::valueOf(name);
        }
#if 0
        ThreadingUtil.runOnLayoutWithJmriException(() -> {
            if (state == LightState.Toggle) {
                if (light.getKnownState() == Turnout.CLOSED) {
                    light.setCommandedState(Turnout.THROWN);
                } else {
                    light.setCommandedState(Turnout.CLOSED);
                }

            } else if (state == LightState.Intensity) {
                if (light instanceof VariableLight) {
                    ((VariableLight)light).setTargetIntensity(getNewData() / 100.0);
                } else {
                    light.setCommandedState(getNewData() > 50 ? Light.ON : Light.OFF);
                }
            } else if (state == LightState.Interval) {
                if (light instanceof VariableLight) {
                    ((VariableLight)light).setTransitionTime(getNewData());
                }
            } else {
                light.setCommandedState(state.getID());
            }
        });
#endif
        ThreadingUtil::runOnLayoutWithJmriException(new ActionLight_Run(state, light, this));
    }

    //@Override
    /*public*/  FemaleSocket* ActionLight::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int ActionLight::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString ActionLight::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Light_Short");
    }

    //@Override
    /*public*/  QString ActionLight::getLongDescription(QLocale locale) {
        QString namedBean;
        QString state;

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
            {
                QString lightName;
                if (_lightHandle != nullptr) {
                    lightName = _lightHandle->getBean()->getDisplayName();
                } else {
                    lightName = tr(/*locale,*/ "");
                }
                namedBean =  tr(/*locale,*/ "%1").arg(lightName);
                break;
            }
            case NamedBeanAddressing::Reference:
                namedBean =  tr(/*locale,*/ "by reference %1").arg(_reference);
                break;

            case NamedBeanAddressing::LocalVariable:
                namedBean =  tr(/*locale,*/ "by local variable %1").arg(_localVariable);
                break;

            case NamedBeanAddressing::Formula:
                namedBean =  tr(/*locale,*/ "by formula %1").arg(_formula);
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        switch (_stateAddressing) {
            case NamedBeanAddressing::Direct:
                if (_lightState == ActionLight::LightState::Intensity || _lightState == ActionLight::LightState::Interval) {
                    QString bundleKey = "Set light \"%1\" %2 to %3";
                    switch (_dataAddressing) {
                        case NamedBeanAddressing::Direct:
                        {
                            QString type = _lightState == ActionLight::LightState::Intensity ?
                                     tr("intensity") :
                                     tr("interval");
                             return tr(/*locale,*/ "Set light \"%1\" %2 to %3").arg(namedBean, type).arg(_lightValue);
                        }
                        case NamedBeanAddressing::Reference:
                             return tr(/*locale,*/"Set light \"%1\" %2 to %3").arg(namedBean, "", tr("by reference %1").arg(_dataReference));
                        case NamedBeanAddressing::LocalVariable:
                             return tr(/*locale,*/ "Set light \"%1\" %2 to %3").arg(namedBean, "", tr("by local variable %1").arg(_dataLocalVariable));
                        case NamedBeanAddressing::Formula:
                             return tr(/*locale,*/ "Set light \"%1\" %2 to %3").arg(namedBean, "", tr("by formula %1").arg(_dataFormula));
                        default:
                            throw new IllegalArgumentException("invalid _dataAddressing state: " + NamedBeanAddressing::toString(_dataAddressing));
                    }
                } else {
                    state = tr(/*locale,*/ "%1").arg(ActionLight::LightState::toString(_lightState));
                }
                break;

            case NamedBeanAddressing::Reference:
                state =  tr(/*locale,*/ "by reference %1").arg(_stateReference);
                break;

            case NamedBeanAddressing::LocalVariable:
                state = tr(/*locale,*/ "by local variable %1").arg(_stateLocalVariable);
                break;

            case NamedBeanAddressing::Formula:
                state =  tr(/*locale,*/ "by formula %1").arg(_stateFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _stateAddressing state: " + NamedBeanAddressing::toString(_stateAddressing));
        }

        return  tr(/*locale,*/ "Set light %1 to state %2").arg(namedBean, state);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionLight::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionLight::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionLight::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionLight::disposeMe() {
    }
#endif

    // This constant is only used internally in LightState but must be outside
    // the enum.
    /*private*/ /*static*/ /*final*/ int ActionLight::TOGGLE_ID = -1;
    /*private*/ /*static*/ /*final*/ int ActionLight::INTENSITY_ID = -2;
    /*private*/ /*static*/ /*final*/ int ActionLight::INTERVAL_ID = -3;

#if 0
    /*public*/  enum LightState {
        Off(Light.OFF, Bundle.getMessage("StateOff")),
        On(Light.ON, Bundle.getMessage("StateOn")),
        Toggle(TOGGLE_ID, Bundle.getMessage("LightToggleStatus")),
        Intensity(INTENSITY_ID, Bundle.getMessage("LightIntensity")),
        Interval(INTERVAL_ID, Bundle.getMessage("LightInterval"));

        /*private*/ final int _id;
        /*private*/ final String _text;

        /*private*/ LightState(int id, QString text) {
            this._id = id;
            this._text = text;
        }

        static /*public*/  LightState::STATES get(int id) {
            switch (id) {
                case Light.OFF:
                    return Off;

                case Light.ON:
                    return On;

                case TOGGLE_ID:
                    return Toggle;

                default:
                    throw new IllegalArgumentException("invalid light state");
            }
        }

        /*public*/  int getID() {
            return _id;
        }

        //@Override
        /*public*/  QString toString() {
            return _text;
        }

    }
#endif
    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionLight::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
        log->debug(tr("getUsageReport :: ActionLight: bean = %1, report = %2").arg(cdl->getDisplayName()).arg(report->size()));
        if (getLight() != nullptr && bean->equals(getLight()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* ActionLight::log = LoggerFactory::getLogger("ActionLight");

