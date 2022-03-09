#include "analogactionlightintensity.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultanalogactionmanager.h"
#include "recursivedescentparser.h"
#include "variablelightmanager.h"
#include "referenceutil.h"
#include "vptr.h"
#include "conditionalng.h"
#include "typeconversionutil.h"

/**
 * Sets the light intensity.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class AnalogActionLightIntensity extends AbstractAnalogAction
//        implements VetoableChangeListener {

/*public*/  /*static*/ /*final*/ int AnalogActionLightIntensity::INTENSITY_SOCKET = 0;


/*public*/  AnalogActionLightIntensity::AnalogActionLightIntensity(QString sys, QString user, QObject *parent)
: AbstractAnalogAction(sys, user, parent) {
    //super(sys, user);
}

//@Override
/*public*/  Base* AnalogActionLightIntensity::getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException*/ {
    AnalogActionManager* manager = (DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager");
    QString sysName = systemNames.value(getSystemName());
    QString userName = userNames.value(getSystemName());
    if (sysName == "") sysName = manager->getAutoSystemName();
    AnalogActionLightIntensity* copy = new AnalogActionLightIntensity(sysName, userName);
    copy->setComment(getComment());
    if (_lightHandle != nullptr) copy->setLight(_lightHandle);
    copy->setAddressing(_addressing);
    copy->setFormula(_formula);
    copy->setLocalVariable(_localVariable);
    copy->setReference(_reference);
    return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
}

/*public*/  void AnalogActionLightIntensity::setLight(/*@Nonnull*/ QString lightName) {
    assertListenersAreNotRegistered(log, "setLight");
    VariableLight* light = (VariableLight*)((VariableLightManager*)InstanceManager::getDefault("VariableLightManager"))->getNamedBean(lightName)->self();
    if (light != nullptr) {
        setLight(light);
    } else {
        removeLight();
        log->warn(tr("light \"%1\" is not found").arg(lightName));
    }
}

/*public*/  void AnalogActionLightIntensity::setLight(/*@Nonnull*/ NamedBeanHandle<VariableLight*>* handle) {
    assertListenersAreNotRegistered(log, "setLight");
    _lightHandle = handle;
    InstanceManager::lightManagerInstance()->addVetoableChangeListener(this);
}

/*public*/  void AnalogActionLightIntensity::setLight(/*@Nonnull*/ VariableLight* light) {
    assertListenersAreNotRegistered(log, "setLight");
    setLight(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
            ->getNamedBeanHandle(light->getDisplayName(), light));
}

/*public*/  void AnalogActionLightIntensity::removeLight() {
    assertListenersAreNotRegistered(log, "setLight");
    if (_lightHandle != nullptr) {
        InstanceManager::lightManagerInstance()->removeVetoableChangeListener(this);
        _lightHandle = nullptr;
    }
}

/*public*/  NamedBeanHandle<VariableLight*>* AnalogActionLightIntensity::getLight() {
    return _lightHandle;
}

/*public*/  void AnalogActionLightIntensity::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
    _addressing = addressing;
    parseFormula();
}

/*public*/  NamedBeanAddressing::TYPE AnalogActionLightIntensity::getAddressing() {
    return _addressing;
}

/*public*/  void AnalogActionLightIntensity::setReference(/*@Nonnull*/ QString reference) {
    if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
        throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
    }
    _reference = reference;
}

/*public*/  QString AnalogActionLightIntensity::getReference() {
    return _reference;
}

/*public*/  void AnalogActionLightIntensity::setLocalVariable(/*@Nonnull*/ QString localVariable) {
    _localVariable = localVariable;
}

/*public*/  QString AnalogActionLightIntensity::getLocalVariable() {
    return _localVariable;
}

/*public*/  void AnalogActionLightIntensity::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
    _formula = formula;
    parseFormula();
}

/*public*/  QString AnalogActionLightIntensity::getFormula() {
    return _formula;
}

/*private*/ void AnalogActionLightIntensity::parseFormula() /*throws ParserException*/ {
    if (_addressing == NamedBeanAddressing::Formula) {
        QMap<QString, Variable*> variables = QMap<QString, Variable*>();

        RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
        _expressionNode = parser->parseExpression(_formula);
    } else {
        _expressionNode = nullptr;
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  Category* AnalogActionLightIntensity::getCategory() {
    return Category::ITEM;
}

//@Override
/*public*/  void AnalogActionLightIntensity::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
    if ("CanDelete" == (evt->getPropertyName())) { // No I18N
        if (VPtr<VariableLight>::asPtr(evt->getOldValue())) {
            if (VPtr<VariableLight>::asPtr(evt->getOldValue())->equals(getLight()->getBean()->self())) {
                PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                throw new PropertyVetoException(tr("Light is in use by Light intensity action \"%1\"").arg(getDisplayName()), e); // NOI18N
            }
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogActionLightIntensity::setValue(double value) /*throws JmriException*/ {
    VariableLight* light;

    switch (_addressing) {
        case NamedBeanAddressing::Direct:
            light = _lightHandle != nullptr ? _lightHandle->getBean() : nullptr;
            break;

        case NamedBeanAddressing::Reference:
        {
            QString ref = ReferenceUtil::getReference(
                    getConditionalNG()->getSymbolTable(), _reference);
            light =(VariableLight*) (VariableLight*)((VariableLightManager*)InstanceManager::getDefault("VariableLightManager"))
                    ->getNamedBean(ref)->self();
            break;
        }
        case NamedBeanAddressing::LocalVariable:
        {
            SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
            light = (VariableLight*)((VariableLightManager*)InstanceManager::getDefault("VariableLightManager"))
                    ->getNamedBean(TypeConversionUtil
                            ::convertToString(symbolTable->getValue(_localVariable), false))->self();
            break;
        }
        case NamedBeanAddressing::Formula:
            light = _expressionNode != nullptr ?
                   (VariableLight*) ((VariableLightManager*)InstanceManager::getDefault("VariableLightManager"))
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

    double intensity = value;

    if (intensity < 0.0) intensity = 0.0;
    if (intensity > 100.0) intensity = 100.0;

    light->setTargetIntensity(intensity/100.0);
}

//@Override
/*public*/  FemaleSocket* AnalogActionLightIntensity::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */{
    throw new UnsupportedOperationException("Not supported.");
}

//@Override
/*public*/  int AnalogActionLightIntensity::getChildCount() {
    return 0;
}

//@Override
/*public*/  QString AnalogActionLightIntensity::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "Light intensity");
}

//@Override
/*public*/  QString AnalogActionLightIntensity::getLongDescription(QLocale locale) {
    QString namedBean;

    switch (_addressing) {
        case NamedBeanAddressing::Direct:
         {
            QString lightName;
            if (_lightHandle != nullptr) {
                lightName = _lightHandle->getBean()->getDisplayName();
            } else {
                lightName = tr(/*locale,*/ "''");
            }
            namedBean = tr(/*locale,*/ "%1").arg(lightName);
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

    return tr(/*locale,*/ "Set light intensity for %1").arg(namedBean);
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogActionLightIntensity::setup() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogActionLightIntensity::registerListenersForThisClass() {
    _listenersAreRegistered = true;
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogActionLightIntensity::unregisterListenersForThisClass() {
    _listenersAreRegistered = false;
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogActionLightIntensity::disposeMe() {
}

/*private*/ /*final*/ /*static*/ Logger* AnalogActionLightIntensity::log = LoggerFactory::getLogger("AnalogActionLightIntensity");
