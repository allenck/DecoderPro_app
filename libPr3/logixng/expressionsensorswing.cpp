#include "expressionsensorswing.h"
#include "expressionsensor.h"
#include "namedbeanaddressing.h"
#include "instancemanager.h"
#include "proxysensormanager.h"
#include "is_isnot_enum.h"
#include "defaultdigitalexpressionmanager.h"
#include "parserexception.h"

/**
 * Configures an ExpressionSensor object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class ExpressionSensorSwing extends AbstractDigitalExpressionSwing {



//@Override
/*protected*/ void ExpressionSensorSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
    ExpressionSensor* expression = nullptr;
    if(object)
      expression = (ExpressionSensor*)object->bself();

    panel = new JPanel(new FlowLayout());

    _tabbedPaneSensor = new JTabbedPane();
    _panelSensorDirect = new JPanel(new FlowLayout());
    _panelSensorReference = new JPanel(new FlowLayout());
    _panelSensorLocalVariable = new JPanel(new FlowLayout());
    _panelSensorFormula = new JPanel(new FlowLayout());

    _tabbedPaneSensor->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelSensorDirect);
    _tabbedPaneSensor->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelSensorReference);
    _tabbedPaneSensor->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelSensorLocalVariable);
    _tabbedPaneSensor->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelSensorFormula);

    sensorBeanPanel = new BeanSelectPanel((AbstractManager*)((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->mself(), nullptr);
    _panelSensorDirect->layout()->addWidget(sensorBeanPanel);

    _sensorReferenceTextField = new JTextField();
    _sensorReferenceTextField->setColumns(30);
    _panelSensorReference->layout()->addWidget(_sensorReferenceTextField);

    _sensorLocalVariableTextField = new JTextField();
    _sensorLocalVariableTextField->setColumns(30);
    _panelSensorLocalVariable->layout()->addWidget(_sensorLocalVariableTextField);

    _sensorFormulaTextField = new JTextField();
    _sensorFormulaTextField->setColumns(30);
    _panelSensorFormula->layout()->addWidget(_sensorFormulaTextField);


    _is_IsNot_ComboBox = new JComboBox();
    for (Is_IsNot_Enum::VAL e : Is_IsNot_Enum::values()) {
        _is_IsNot_ComboBox->addItem(Is_IsNot_Enum::toString(e),e);
    }
//        JComboBoxUtil->setupComboBoxMaxRows(_is_IsNot_ComboBox);


    _tabbedPaneSensorState = new JTabbedPane();
    _panelSensorStateDirect = new JPanel(new FlowLayout());
    _panelSensorStateReference = new JPanel(new FlowLayout());
    _panelSensorStateLocalVariable = new JPanel(new FlowLayout());
    _panelSensorStateFormula = new JPanel(new FlowLayout());

    _tabbedPaneSensorState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelSensorStateDirect);
    _tabbedPaneSensorState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelSensorStateReference);
    _tabbedPaneSensorState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelSensorStateLocalVariable);
    _tabbedPaneSensorState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelSensorStateFormula);

    _stateComboBox = new JComboBox();
    for (ExpressionSensor::SensorState::STATE e : ExpressionSensor::SensorState::values()) {
        _stateComboBox->addItem(ExpressionSensor::SensorState::toString(e), e);
    }
//        JComboBoxUtil->setupComboBoxMaxRows(_stateComboBox);

    _panelSensorStateDirect->layout()->addWidget(_stateComboBox);

    _sensorStateReferenceTextField = new JTextField();
    _sensorStateReferenceTextField->setColumns(30);
    _panelSensorStateReference->layout()->addWidget(_sensorStateReferenceTextField);

    _sensorStateLocalVariableTextField = new JTextField();
    _sensorStateLocalVariableTextField->setColumns(30);
    _panelSensorStateLocalVariable->layout()->addWidget(_sensorStateLocalVariableTextField);

    _sensorStateFormulaTextField = new JTextField();
    _sensorStateFormulaTextField->setColumns(30);
    _panelSensorStateFormula->layout()->addWidget(_sensorStateFormulaTextField);


    if (expression != nullptr) {
        switch (expression->getAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneSensor->setSelectedComponent(_panelSensorDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneSensor->setSelectedComponent(_panelSensorReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneSensor->setSelectedComponent(_panelSensorLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneSensor->setSelectedComponent(_panelSensorFormula); break;
            default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getAddressing()));
        }
        if (expression->getSensor() != nullptr) {
            sensorBeanPanel->setDefaultNamedBean(expression->getSensor()->getBean());
        }
        _sensorReferenceTextField->setText(expression->getReference());
        _sensorLocalVariableTextField->setText(expression->getLocalVariable());
        _sensorFormulaTextField->setText(expression->getFormula());

        _is_IsNot_ComboBox->setSelectedItem(expression->get_Is_IsNot());

        switch (expression->getStateAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneSensorState->setSelectedComponent(_panelSensorStateDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneSensorState->setSelectedComponent(_panelSensorStateReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneSensorState->setSelectedComponent(_panelSensorStateLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneSensorState->setSelectedComponent(_panelSensorStateFormula); break;
            default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getAddressing()));
        }
        _stateComboBox->setSelectedItem(expression->getBeanState());
        _sensorStateReferenceTextField->setText(expression->getStateReference());
        _sensorStateLocalVariableTextField->setText(expression->getStateLocalVariable());
        _sensorStateFormulaTextField->setText(expression->getStateFormula());
    }

    QList<JComponent*> components = QList<JComponent*>{
        _tabbedPaneSensor,
        _is_IsNot_ComboBox,
        _tabbedPaneSensorState};

    QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
            tr("Sensor %1 %2 %3"), components);

    if(panel->layout())
    for (JComponent* c : componentList) panel->layout()->addWidget((QWidget*)c);
}

/** {@inheritDoc} */
//@Override
/*public*/  bool ExpressionSensorSwing::validate(/*@Nonnull*/ QList<QString> errorMessages) {
    // Create a temporary expression to test formula
    ExpressionSensor* expression = new ExpressionSensor("IQDE1", "");

    try {
        if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorReference) {
            expression->setReference(_sensorReferenceTextField->text());
        }
    } catch (IllegalArgumentException* e) {
        errorMessages.append(e->getMessage());
        return false;
    }

    try {
        if (_tabbedPaneSensorState->getSelectedComponent() == _panelSensorStateReference) {
            expression->setStateReference(_sensorStateReferenceTextField->text());
        }
    } catch (IllegalArgumentException* e) {
        errorMessages.append(e->getMessage());
        return false;
    }

    try {
        expression->setFormula(_sensorFormulaTextField->text());
        if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorDirect) {
            expression->setAddressing(NamedBeanAddressing::Direct);
        } else if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorReference) {
            expression->setAddressing(NamedBeanAddressing::Reference);
        } else if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorLocalVariable) {
            expression->setAddressing(NamedBeanAddressing::LocalVariable);
        } else if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorFormula) {
            expression->setAddressing(NamedBeanAddressing::Formula);
        } else {
            throw new IllegalArgumentException("_tabbedPane has unknown selection");
        }
    } catch (ParserException* e) {
        errorMessages.append("Cannot parse formula: " + e->getMessage());
    }
    return true;
}

/** {@inheritDoc} */
//@Override
/*public*/  QString ExpressionSensorSwing::getAutoSystemName() {
    return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->AbstractManager::getAutoSystemName();
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket* ExpressionSensorSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
    ExpressionSensor* expression = new ExpressionSensor(systemName, userName);
    updateObject(expression);
    return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionSensorSwing::updateObject(/*@Nonnull*/ Base* object) {
    if (! (qobject_cast<ExpressionSensor*>(object->bself()))) {
        throw new IllegalArgumentException(QString("object must be an ExpressionSensor but is a: ")+object->bself()->metaObject()->className());
    }
    ExpressionSensor* expression = (ExpressionSensor*)object->bself();
    if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorDirect) {
        Sensor* sensor = (Sensor*)sensorBeanPanel->getNamedBean()->self();
        if (sensor != nullptr) {
            NamedBeanHandle<Sensor*>* handle
                    = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                            ->getNamedBeanHandle(sensor->getDisplayName(), sensor);
            expression->setSensor(handle);
        } else {
            expression->removeSensor();
        }
    } else {
        expression->removeSensor();
    }
    try {
        if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorDirect) {
            expression->setAddressing(NamedBeanAddressing::Direct);
        } else if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorReference) {
            expression->setAddressing(NamedBeanAddressing::Reference);
            expression->setReference(_sensorReferenceTextField->text());
        } else if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorLocalVariable) {
            expression->setAddressing(NamedBeanAddressing::LocalVariable);
            expression->setLocalVariable(_sensorLocalVariableTextField->text());
        } else if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorFormula) {
            expression->setAddressing(NamedBeanAddressing::Formula);
            expression->setFormula(_sensorFormulaTextField->text());
        } else {
            throw new IllegalArgumentException("_tabbedPaneSensor has unknown selection");
        }

        expression->set_Is_IsNot(Is_IsNot_Enum::get(_is_IsNot_ComboBox->getSelectedItem()));

        if (_tabbedPaneSensorState->getSelectedComponent() == _panelSensorStateDirect) {
            expression->setStateAddressing(NamedBeanAddressing::Direct);
            expression->setBeanState(ExpressionSensor::SensorState::valueOf(_stateComboBox->getSelectedItem()));
        } else if (_tabbedPaneSensorState->getSelectedComponent() == _panelSensorStateReference) {
            expression->setStateAddressing(NamedBeanAddressing::Reference);
            expression->setStateReference(_sensorStateReferenceTextField->text());
        } else if (_tabbedPaneSensorState->getSelectedComponent() == _panelSensorStateLocalVariable) {
            expression->setStateAddressing(NamedBeanAddressing::LocalVariable);
            expression->setStateLocalVariable(_sensorStateLocalVariableTextField->text());
        } else if (_tabbedPaneSensorState->getSelectedComponent() == _panelSensorStateFormula) {
            expression->setStateAddressing(NamedBeanAddressing::Formula);
            expression->setStateFormula(_sensorStateFormulaTextField->text());
        } else {
            throw new IllegalArgumentException("_tabbedPaneSensorState has unknown selection");
        }
    } catch (ParserException* e) {
        throw new RuntimeException("ParserException: "+e->getMessage(), e);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  QString ExpressionSensorSwing::toString() {
    return tr("Sensor");
}

//@Override
/*public*/  void ExpressionSensorSwing::dispose() {
    if (sensorBeanPanel != nullptr) {
        sensorBeanPanel->dispose();
    }
}
