#include "actionlightintensity.h"
#include "defaultvariablelightmanager.h"
#include "instancemanager.h"
#include "logixng/conditionalng.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "loggerfactory.h"
#include "logixng/recursivedescentparser.h"
#include "logixng/typeconversionutil.h"
#include "variablelightmanager.h"
#include "referenceutil.h"
#include "defaultanalogexpressionmanager.h"
#include "vptr.h"

/**
 * Runs an engine.
 * This action reads an analog expression with the loco address and sets its
 * speed according to an alaog expression and the direction according to a
 * digital expression.
 *
 * @author Daniel Bergqvist Copyright 2019
 */
// /*public*/ class ActionLightIntensity extends AbstractDigitalAction
//        implements FemaleSocketListener, VetoableChangeListener {

    ///*public*/ static final int INTENSITY_SOCKET = 0;




    /*public*/ ActionLightIntensity::ActionLightIntensity(QString sys, QString user, QObject *parent)
    : AbstractDigitalAction{sys, user, parent}{
        //super(sys, user);
     setObjectName("ActionLightIntensity");
        _intensitySocket = ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))
                ->createFemaleSocket(this, this, tr("Intensity"));
    }

    //@Override
    /*public*/ Base* ActionLightIntensity::getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws JmriException*/ {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ActionLightIntensity* copy = new ActionLightIntensity(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_lightHandle != nullptr) copy->setLight(_lightHandle);
        copy->setAddressing(_addressing);
        copy->setFormula(_formula);
        copy->setLocalVariable(_localVariable);
        copy->setReference(_reference);
        return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /*public*/ void ActionLightIntensity::setLight(/*@Nonnull*/ QString lightName) {
        assertListenersAreNotRegistered(log, "setLight");
        VariableLight* light = (VariableLight*)((DefaultVariableLightManager*)InstanceManager::getDefault("VariableLightManager"))->getNamedBean(lightName)->self();
        if (light != nullptr) {
            setLight(light);
        } else {
            removeLight();
            log->warn(tr("light \"%1\" is not found").arg(lightName));
        }
    }

    /*public*/ void ActionLightIntensity::setLight(/*@Nonnull*/ NamedBeanHandle<VariableLight*>* handle) {
        assertListenersAreNotRegistered(log, "setLight");
        _lightHandle = handle;
        InstanceManager::lightManagerInstance()->addVetoableChangeListener(this);
    }

    /*public*/ void ActionLightIntensity::setLight(/*@Nonnull*/ VariableLight* light) {
        assertListenersAreNotRegistered(log, "setLight");
        setLight(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                 ->getNamedBeanHandle(light->getDisplayName(), light));
    }

    /*public*/ void ActionLightIntensity::removeLight() {
        assertListenersAreNotRegistered(log, "setLight");
        if (_lightHandle != nullptr) {
            InstanceManager::lightManagerInstance()->removeVetoableChangeListener(this);
            _lightHandle = nullptr;
        }
    }

    /*public*/ NamedBeanHandle<VariableLight*>* ActionLightIntensity::getLight() {
        return _lightHandle;
    }

    /*public*/ void ActionLightIntensity::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ActionLightIntensity::getAddressing() {
        return _addressing;
    }

    /*public*/ void ActionLightIntensity::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/ QString ActionLightIntensity::getReference() {
        return _reference;
    }

    /*public*/ void ActionLightIntensity::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/ QString ActionLightIntensity::getLocalVariable() {
        return _localVariable;
    }

    /*public*/ void ActionLightIntensity::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _formula = formula;
        parseFormula();
    }

    /*public*/ QString ActionLightIntensity::getFormula() {
        return _formula;
    }

    /*private*/ void ActionLightIntensity::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*>  variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category ActionLightIntensity::getCategory() {
        return Category::ITEM;
    }

    //@Override
    /*public*/ void ActionLightIntensity::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<VariableLight>::asPtr(evt->getOldValue())) {
                if (VPtr<VariableLight>::asPtr(evt->getOldValue())->equals(getLight()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Light is in use by Light intensity action \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionLightIntensity::execute() /*throws JmriException*/ {
        VariableLight* light;

        switch (_addressing) {
        case NamedBeanAddressing::Direct:
            light = _lightHandle != nullptr ? _lightHandle->getBean() : nullptr;
                break;

        case NamedBeanAddressing::Reference:
        {
                QString ref = ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _reference);
                light = (VariableLight*)((DefaultVariableLightManager*)InstanceManager::getDefault("VariableLightManager"))
                        ->getNamedBean(ref)->self();
                break;
        }
        case NamedBeanAddressing::LocalVariable:
        {
            SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                light = (VariableLight*)((DefaultVariableLightManager*)InstanceManager::getDefault("VariableLightManager"))
                        ->getNamedBean(TypeConversionUtil
                                       ::convertToString(symbolTable->getValue(_localVariable), false))->self();
                break;
        }
        case NamedBeanAddressing::Formula:
                light = _expressionNode != nullptr ?
                        (VariableLight*)((DefaultVariableLightManager*)InstanceManager::getDefault("VariableLightManager"))
                            ->getNamedBean(TypeConversionUtil
                                           ::convertToString(_expressionNode->calculate(
                                                                 getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        if (light == nullptr) {
//            log.warn("light is null");
            return;
        }

        double intensity = 0.0;

        if (_intensitySocket->isConnected()) {
            intensity =
                    ((MaleAnalogExpressionSocket*)_intensitySocket->getConnectedSocket()->bself())
                    ->evaluate();
        }

        if (intensity < 0.0) intensity = 0.0;
        if (intensity > 100.0) intensity = 100.0;

        light->setTargetIntensity(intensity/100.0);
    }

    //@Override
    /*public*/ FemaleSocket*ActionLightIntensity:: getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */{
        switch (index) {
            case INTENSITY_SOCKET:
                return _intensitySocket;

            default:
                throw new IllegalArgumentException(
                        tr("index has invalid value: %1").arg(index));
        }
    }

    //@Override
    /*public*/ int ActionLightIntensity::getChildCount() {
        return 1;
    }

    //@Override
    /*public*/ void ActionLightIntensity::connected(FemaleSocket* socket) {
        if (socket == _intensitySocket) {
            _intensitySocketSystemName = socket->getConnectedSocket()->getSystemName();
        } else {
            throw new IllegalArgumentException("unkown socket");
        }
    }

    //@Override
    /*public*/ void ActionLightIntensity::disconnected(FemaleSocket* socket) {
        if (socket == _intensitySocket) {
            _intensitySocketSystemName = nullptr;
        } else {
            throw new IllegalArgumentException("unkown socket");
        }
    }

    //@Override
    /*public*/ QString ActionLightIntensity::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "ActionLightIntensity");
    }

    //@Override
    /*public*/ QString ActionLightIntensity::getLongDescription(QLocale locale) {
        QString namedBean;

        switch (_addressing) {
        case NamedBeanAddressing::Direct:
        {
                QString lightName;
                if (_lightHandle != nullptr) {
                    lightName = _lightHandle->getBean()->getDisplayName();
                } else {
                    lightName = tr(/*locale,*/ "BeanNotSelected");
                }
                namedBean = tr(/*locale,*/"%1").arg(lightName);
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

        return tr(/*locale,*/ "Set light intensity for %1").arg(namedBean);
    }

    /*public*/ FemaleAnalogExpressionSocket* ActionLightIntensity::getIntensitySocket() {
        return _intensitySocket;
    }

    /*public*/ QString ActionLightIntensity::getIntensitySocketSystemName() {
        return _intensitySocketSystemName;
    }

    /*public*/ void ActionLightIntensity::setIntensitySystemName(QString systemName) {
        _intensitySocketSystemName = systemName;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionLightIntensity::setup() {
        try {
        if ( !_intensitySocket->isConnected()
             || _intensitySocket->getConnectedSocket()->getSystemName()
                            !=(_intensitySocketSystemName)) {

                QString socketSystemName = _intensitySocketSystemName;
                _intensitySocket->_disconnect();
                if (socketSystemName != "") {
                    MaleSocket* maleSocket = (AbstractMaleSocket*)
                            ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))
                            ->getBySystemName(socketSystemName)->self();
                    _intensitySocket->_disconnect();
                    if (maleSocket != nullptr) {
                        _intensitySocket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("cannot load analog expression " + socketSystemName);
                    }
                }
            } else {
            _intensitySocket->getConnectedSocket()->setup();
            }
        } catch (SocketAlreadyConnectedException* ex) {
            // This shouldn't happen and is a runtime error if it does.
            throw new RuntimeException("socket is already connected");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionLightIntensity::registerListenersForThisClass() {
        _listenersAreRegistered = true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionLightIntensity::unregisterListenersForThisClass() {
        _listenersAreRegistered = false;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionLightIntensity::disposeMe() {
    }

    /*private*/ /*final*/ /*static*/ Logger* ActionLightIntensity::log = LoggerFactory::getLogger("ActionLightIntensity");
