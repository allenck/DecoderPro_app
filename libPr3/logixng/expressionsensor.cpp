#include "expressionsensor.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "referenceutil.h"
#include "recursivedescentparser.h"
#include "conditionalng.h"
#include "vptr.h"
#include "typeconversionutil.h"

/**
 * This expression sets the state of a sensor.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class ExpressionSensor extends AbstractDigitalExpression
//        implements PropertyChangeListener, VetoableChangeListener {


    /*public*/  ExpressionSensor::ExpressionSensor(QString sys, QString user, QObject *parent) : AbstractDigitalExpression(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
     setObjectName("ExpressionSensor");
    }

    //@Override
    /*public*/  Base* ExpressionSensor::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throws ParserException */{
        DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
        ExpressionSensor* copy = new ExpressionSensor(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_sensorHandle != nullptr) copy->setSensor(_sensorHandle);
        copy->setBeanState(_sensorState);
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

    /*public*/  void ExpressionSensor::setSensor(/*@Nonnull*/ QString sensorName) {
        assertListenersAreNotRegistered(log, "setSensor");
        Sensor* sensor = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->getSensor(sensorName);
        if (sensor != nullptr) {
            setSensor(sensor);
        } else {
            removeSensor();
            log->error(tr("sensor \"%1\" is not found").arg(sensorName));
        }
    }

    /*public*/  void ExpressionSensor::setSensor(/*@Nonnull*/ NamedBeanHandle<Sensor*>* handle) {
        assertListenersAreNotRegistered(log, "setSensor");
        _sensorHandle = handle;
        InstanceManager::sensorManagerInstance()->addVetoableChangeListener(this);
    }

    /*public*/  void ExpressionSensor::setSensor(/*@Nonnull*/ Sensor* sensor) {
        assertListenersAreNotRegistered(log, "setSensor");
        setSensor(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(sensor->getDisplayName(), sensor));
    }

    /*public*/  void ExpressionSensor::removeSensor() {
        assertListenersAreNotRegistered(log, "setSensor");
        if (_sensorHandle != nullptr) {
            InstanceManager::sensorManagerInstance()->removeVetoableChangeListener(this);
            _sensorHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<Sensor*>* ExpressionSensor::getSensor() {
        return _sensorHandle;
    }

    /*public*/  void ExpressionSensor::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ExpressionSensor::getAddressing() {
        return _addressing;
    }

    /*public*/  void ExpressionSensor::setReference(/*@Nonnull */QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/  QString ExpressionSensor::getReference() {
        return _reference;
    }

    /*public*/  void ExpressionSensor::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/  QString ExpressionSensor::getLocalVariable() {
        return _localVariable;
    }

    /*public*/  void ExpressionSensor::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException */{
        _formula = formula;
        parseFormula();
    }

    /*public*/  QString ExpressionSensor::getFormula() {
        return _formula;
    }

    /*private*/ void ExpressionSensor::parseFormula() /*throws ParserException */{
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }

    /*public*/  void ExpressionSensor::set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot) {
        _is_IsNot = is_IsNot;
    }

    /*public*/  Is_IsNot_Enum::VAL ExpressionSensor::get_Is_IsNot() {
        return _is_IsNot;
    }

    /*public*/  void ExpressionSensor::setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException */{
        _stateAddressing = addressing;
        parseStateFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ExpressionSensor::getStateAddressing() {
        return _stateAddressing;
    }

    /*public*/  void ExpressionSensor::setBeanState(ExpressionSensor::SensorState::STATE state) {
        _sensorState = state;
    }

    /*public*/  ExpressionSensor::SensorState::STATE ExpressionSensor::getBeanState() {
        return _sensorState;
    }

    /*public*/  void ExpressionSensor::setStateReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _stateReference = reference;
    }

    /*public*/  QString ExpressionSensor::getStateReference() {
        return _stateReference;
    }

    /*public*/  void ExpressionSensor::setStateLocalVariable(/*@Nonnull*/ QString localVariable) {
        _stateLocalVariable = localVariable;
    }

    /*public*/  QString ExpressionSensor::getStateLocalVariable() {
        return _stateLocalVariable;
    }

    /*public*/  void ExpressionSensor::setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _stateFormula = formula;
        parseStateFormula();
    }

    /*public*/  QString ExpressionSensor::getStateFormula() {
        return _stateFormula;
    }

    /*private*/ void ExpressionSensor::parseStateFormula() /*throws ParserException*/ {
        if (_stateAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _stateExpressionNode = parser->parseExpression(_stateFormula);
        } else {
            _stateExpressionNode = nullptr;
        }
    }

    //@Override
    /*public*/  void ExpressionSensor::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<Sensor>::asPtr(evt->getOldValue())) {
                if (VPtr<Sensor>::asPtr(evt->getOldValue())->equals(getSensor()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Sensor is in use by Sensor expression \"%1\"").arg(AbstractNamedBean::getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<Sensor>::asPtr(evt->getOldValue())) {
                if (VPtr<Sensor>::asPtr(evt->getOldValue())->equals(getSensor()->getBean())) {
                    removeSensor();
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category* ExpressionSensor::getCategory() {
        return Category::ITEM;
    }

    /*private*/ QString ExpressionSensor::getNewState() /*throws JmriException*/ {

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
                throw new IllegalArgumentException("invalid _addressing state: " +NamedBeanAddressing::toString(_stateAddressing));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ExpressionSensor::evaluate() /*throws JmriException*/ {
        Sensor* sensor;

//        System.out.format("ExpressionSensor.execute: %s%n", getLongDescription());

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
                        (Sensor*)((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))
                                ->AbstractProxyManager::getNamedBean(TypeConversionUtil
                                        ::convertToString(_expressionNode->calculate(
                                                getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

//        System.out.format("ExpressionSensor.execute: sensor: %s%n", sensor);

        if (sensor == nullptr) {
//            log.warn("sensor is null");
            return false;
        }

        SensorState::STATE checkSensorState;

        if (_stateAddressing == NamedBeanAddressing::Direct) {
            checkSensorState = _sensorState;
        } else {
            checkSensorState = SensorState::valueOf(getNewState());
        }

        SensorState::STATE currentSensorState = SensorState::get(sensor->getKnownState());
        if (_is_IsNot == Is_IsNot_Enum::Is) {
            return currentSensorState == checkSensorState;
        } else {
            return currentSensorState != checkSensorState;
        }
    }

    //@Override
    /*public*/  FemaleSocket* ExpressionSensor::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int ExpressionSensor::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString ExpressionSensor::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Sensor");
    }

    //@Override
    /*public*/  QString ExpressionSensor::getLongDescription(QLocale locale) {
        QString namedBean;
        QString state;

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
            {
                QString sensorName;
                if (_sensorHandle != nullptr) {
                    sensorName = _sensorHandle->getBean()->getDisplayName();
                } else {
                    sensorName = tr(/*locale,*/ "''");
                }
                namedBean = tr(/*locale,*/ "%1").arg(sensorName);
                break;
            }
            case NamedBeanAddressing::Reference:
                namedBean =tr(/*locale, */"by reference %1").arg(_reference);
                break;

            case NamedBeanAddressing::LocalVariable:
                namedBean = tr(/*locale, */"by local variable %1").arg(_localVariable);
                break;

            case NamedBeanAddressing::Formula:
                namedBean = tr(/*locale,*/ "by formula %1").arg(_formula);
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        switch (_stateAddressing) {
            case NamedBeanAddressing::Direct:
                state = tr(/*locale, */"%1").arg(SensorState::toString(_sensorState));
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

        return tr(/*locale,*/ "Sensor %1 %2 %3").arg(namedBean, Is_IsNot_Enum::toString(_is_IsNot), state);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionSensor::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionSensor::registerListenersForThisClass() {
        if (!_listenersAreRegistered && (_sensorHandle != nullptr)) {
            _sensorHandle->getBean()->addPropertyChangeListener("KnownState", this);
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionSensor::unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {
            _sensorHandle->getBean()->removePropertyChangeListener("KnownState", this);
            _listenersAreRegistered = false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionSensor::propertyChange(PropertyChangeEvent* evt) {
        getConditionalNG()->execute();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionSensor::disposeMe() {
    }



    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionSensor::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport *> *report, NamedBean* cdl) {
        log->debug(tr("getUsageReport :: ExpressionBlock: bean = %1, report = %2").arg(cdl->getSystemName()).arg(report->size()));
        if (getSensor() != nullptr && bean->equals(getSensor()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* ExpressionSensor::log = LoggerFactory::getLogger("ExpressionSensor");
