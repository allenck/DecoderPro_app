#include "actionsensor.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalactionmanager.h"
#include "recursivedescentparser.h"
#include "referenceutil.h"
#include "vptr.h"
#include "conditionalng.h"
#include "typeconversionutil.h"

/**
 * This action sets the state of a sensor.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class ActionSensor extends AbstractDigitalAction implements VetoableChangeListener {


/*public*/  ActionSensor::ActionSensor(QString sys, QString user, QObject* parent) : AbstractDigitalAction(sys, user, parent)
        /*throws BadUserNameException, BadSystemNameException */{
    //super(sys, user);
 setObjectName("ActionSensor");
}

//@Override
/*public*/  Base* ActionSensor::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throws ParserException */{
    DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
    ActionSensor* copy = new ActionSensor(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    if (_sensorHandle != nullptr) copy->setSensor(_sensorHandle);
    copy->setBeanState(_sensorState);
    copy->setAddressing(_addressing);
    copy->setFormula(_formula);
    copy->setLocalVariable(_localVariable);
    copy->setReference(_reference);
    copy->setStateAddressing(_stateAddressing);
    copy->setStateFormula(_stateFormula);
    copy->setStateLocalVariable(_stateLocalVariable);
    copy->setStateReference(_stateReference);
    return manager->registerAction(copy);
}

/*public*/  void ActionSensor::setSensor(/*@Nonnull*/ QString sensorName) {
    assertListenersAreNotRegistered(log, "setSensor");
    Sensor* sensor = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->getSensor(sensorName);
    if (sensor != nullptr) {
        setSensor(sensor);
    } else {
        removeSensor();
        log->warn(tr("sensor \"%1\" is not found").arg(sensorName));
    }
}

/*public*/  void ActionSensor::setSensor(/*@Nonnull*/ NamedBeanHandle<Sensor*>* handle) {
    assertListenersAreNotRegistered(log, "setSensor");
    _sensorHandle = handle;
    InstanceManager::sensorManagerInstance()->addVetoableChangeListener(this);
}

/*public*/  void ActionSensor::setSensor(/*@Nonnull*/ Sensor* sensor) {
    assertListenersAreNotRegistered(log, "setSensor");
    setSensor(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
            ->getNamedBeanHandle(sensor->getDisplayName(), sensor));
}

/*public*/  void ActionSensor::removeSensor() {
    assertListenersAreNotRegistered(log, "setSensor");
    if (_sensorHandle != nullptr) {
        InstanceManager::sensorManagerInstance()->removeVetoableChangeListener(this);
        _sensorHandle = nullptr;
    }
}

/*public*/  NamedBeanHandle<Sensor*>* ActionSensor::getSensor() {
    return _sensorHandle;
}

/*public*/  void ActionSensor::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException */{
    _addressing = addressing;
    parseFormula();
}

/*public*/  NamedBeanAddressing::TYPE ActionSensor::getAddressing() {
    return _addressing;
}

/*public*/  void ActionSensor::setReference(/*@Nonnull*/ QString reference) {
    if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
        throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
    }
    _reference = reference;
}

/*public*/  QString ActionSensor::getReference() {
    return _reference;
}

/*public*/  void ActionSensor::setLocalVariable(/*@Nonnull*/ QString localVariable) {
    _localVariable = localVariable;
}

/*public*/  QString ActionSensor::getLocalVariable() {
    return _localVariable;
}

/*public*/  void ActionSensor::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
    _formula = formula;
    parseFormula();
}

/*public*/  QString ActionSensor::getFormula() {
    return _formula;
}

/*private*/ void ActionSensor::parseFormula() /*throws ParserException*/ {
    if (_addressing == NamedBeanAddressing::Formula) {
        QMap<QString, Variable*> variables = QMap<QString, Variable*>();

        RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
        _expressionNode = parser->parseExpression(_formula);
    } else {
        _expressionNode = nullptr;
    }
}

/*public*/  void ActionSensor::setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
    _stateAddressing = addressing;
    parseStateFormula();
}

/*public*/  NamedBeanAddressing::TYPE ActionSensor::getStateAddressing() {
    return _stateAddressing;
}

/*public*/  void ActionSensor::setBeanState(SensorState::STATE state) {
    _sensorState = state;
}

/*public*/  ActionSensor::SensorState::STATE  ActionSensor::getBeanState() {
    return _sensorState;
}

/*public*/  void ActionSensor::setStateReference(/*@Nonnull*/ QString reference) {
    if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
        throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
    }
    _stateReference = reference;
}

/*public*/  QString ActionSensor::getStateReference() {
    return _stateReference;
}

/*public*/  void ActionSensor::setStateLocalVariable(/*@Nonnull*/ QString localVariable) {
    _stateLocalVariable = localVariable;
}

/*public*/  QString ActionSensor::getStateLocalVariable() {
    return _stateLocalVariable;
}

/*public*/  void ActionSensor::setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
    _stateFormula = formula;
    parseStateFormula();
}

/*public*/  QString ActionSensor::getStateFormula() {
    return _stateFormula;
}

/*private*/ void ActionSensor::parseStateFormula() /*throws ParserException*/ {
    if (_stateAddressing == NamedBeanAddressing::Formula) {
        QMap<QString, Variable*> variables = QMap<QString, Variable*>();

        RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
        _stateExpressionNode = parser->parseExpression(_stateFormula);
    } else {
        _stateExpressionNode = nullptr;
    }
}

//@Override
/*public*/  void ActionSensor::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
    if ("CanDelete" == (evt->getPropertyName())) { // No I18N
        if (VPtr<Sensor>::asPtr(evt->getOldValue()) ) {
            if (VPtr<Sensor>::asPtr(evt->getOldValue())->equals(getSensor()->getBean())) {
                PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                throw new PropertyVetoException(tr("Sensor is in use by Sensor action \"%1\"").arg(getDisplayName()), e); // NOI18N
            }
        }
    } else if ("DoDelete" ==(evt->getPropertyName())) { // No I18N
        if (VPtr<Sensor>::asPtr(evt->getOldValue())) {
            if (VPtr<Sensor>::asPtr(evt->getOldValue())->equals(getSensor()->getBean())) {
                removeSensor();
            }
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  Category* ActionSensor::getCategory() {
    return Category::ITEM;
}

/*private*/ QString ActionSensor::getNewState() /*throws JmriException*/ {

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
            throw new IllegalArgumentException("invalid _addressing state: " +  NamedBeanAddressing::toString(_stateAddressing));
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void ActionSensor::execute() /*throws JmriException*/ {
    Sensor* sensor;

//        System.out.format("ActionSensor.execute: %s%n", getLongDescription());

    switch (_addressing) {
        case NamedBeanAddressing::Direct:
            sensor = _sensorHandle != nullptr ? _sensorHandle->getBean() : nullptr;
            break;

        case NamedBeanAddressing::Reference:
        {
            QString ref = ReferenceUtil::getReference(
                    getConditionalNG()->getSymbolTable(), _reference);
            sensor = (Sensor*)((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))
                    ->AbstractProxyManager::getNamedBean(ref)->self();
            break;
        }
        case NamedBeanAddressing::LocalVariable:
        {
            SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
            sensor = (Sensor*)((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))
                    ->AbstractProxyManager::getNamedBean(TypeConversionUtil
                            ::convertToString(symbolTable->getValue(_localVariable), false))->self();
            break;
        }
        case NamedBeanAddressing::Formula:
            sensor = _expressionNode != nullptr ?
                   (Sensor*) ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))
                            ->AbstractProxyManager::getNamedBean(TypeConversionUtil
                                    ::convertToString(_expressionNode->calculate(
                                            getConditionalNG()->getSymbolTable()), false))->self()
                    : nullptr;
            break;

        default:
            throw new IllegalArgumentException("invalid _addressing state: " +  NamedBeanAddressing::toString(_addressing));
    }

//        System.out.format("ActionSensor.execute: sensor: %s%n", sensor);

    if (sensor == nullptr) {
//            log.warn("sensor is null");
        return;
    }

    QString name = (_stateAddressing != NamedBeanAddressing::Direct)
            ? getNewState() : "";

    SensorState::STATE state;
    if (_stateAddressing == NamedBeanAddressing::Direct) {
        state = _sensorState;
    } else {
        state = SensorState::valueOf(name);
    }

//    ThreadingUtil.runOnLayoutWithJmriException(() -> {
//        if (state == SensorState.Toggle) {
//            if (sensor.getKnownState() == Sensor.INACTIVE) {
//                sensor.setCommandedState(Sensor.ACTIVE);
//            } else {
//                sensor.setCommandedState(Sensor.INACTIVE);
//            }
//        } else {
//            sensor.setCommandedState(state.getID());
//        }
//    });
    ThreadingUtil::runOnLayoutWithJmriException(new ASRun(sensor, state));

}

void ASRun::run()
{
 if (state == ActionSensor::SensorState::Toggle) {
     if (sensor->getKnownState() == Sensor::INACTIVE) {
         sensor->setCommandedState(Sensor::ACTIVE);
     } else {
         sensor->setCommandedState(Sensor::INACTIVE);
     }
 } else {
     sensor->setCommandedState(ActionSensor::SensorState::getID(state));
 }

}
//@Override
/*public*/  FemaleSocket* ActionSensor::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    throw new UnsupportedOperationException("Not supported.");
}

//@Override
/*public*/  int ActionSensor::getChildCount() {
    return 0;
}

//@Override
/*public*/  QString ActionSensor::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "Sensor");
}

//@Override
/*public*/  QString ActionSensor::getLongDescription(QLocale locale) {
    QString namedBean;
    QString state;

    switch (_addressing) {
        case NamedBeanAddressing::Direct:
        {
            QString sensorName;
            if (_sensorHandle != nullptr) {
                sensorName = _sensorHandle->getBean()->getDisplayName();
            } else {
                sensorName = tr(/*locale,*/ "BeanNotSelected");
            }
            namedBean =tr(/*locale,*/ "%1").arg(sensorName);
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
            state = tr(/*locale,*/ "%1").arg(SensorState::toString(_sensorState));
            break;

        case NamedBeanAddressing::Reference:
            state = tr(/*locale,*/ "by reference %1").arg(_stateReference);
            break;

        case NamedBeanAddressing::LocalVariable:
            state = tr(/*locale,*/ "by lpcal variable %1").arg(_stateLocalVariable);
            break;

        case NamedBeanAddressing::Formula:
            state = tr(/*locale,*/ "by formula %1").arg(_stateFormula);
            break;

        default:
            throw new IllegalArgumentException("invalid _stateAddressing state: " +  NamedBeanAddressing::toString(_stateAddressing));
    }

    return tr(/*locale,*/ "Set sensor %1 to state %2").arg(namedBean, state);
}

/** {@inheritDoc} */
//@Override
/*public*/  void ActionSensor::setup() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void ActionSensor::registerListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void ActionSensor::unregisterListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void ActionSensor::disposeMe() {
}


// This constant is only used internally in SensorState but must be outside
// the enum.
/*private*/ static /*final*/ int TOGGLE_ID = -1;




/** {@inheritDoc} */
//@Override
/*public*/  void ActionSensor::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport *> *report, NamedBean* cdl) {
    log->debug(tr("getUsageReport :: ActionSensor: bean = %1, cdl = %2, report = %3").arg(bean->getDisplayName(), cdl->getDisplayName()).arg(report->size()));
    if (getSensor() != nullptr && bean->equals(getSensor()->getBean())) {
        report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
    }
}

/*private*/ /*final*/ /*static*/ Logger* ActionSensor::log = LoggerFactory::getLogger("ActionSensor");
