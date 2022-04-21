#include "actionsensorswing.h"
#include "actionsensor.h"
#include "jtabbedpane.h"
#include "namedbeanaddressing.h"
#include "proxysensormanagerxml.h"
#include "instancemanager.h"
#include "beanselectpanel.h"
#include "jtextfield.h"
#include "swingconfiguratorinterface.h"
#include "parserexception.h"
#include "defaultdigitalactionmanager.h"

ActionSensorSwing::ActionSensorSwing(QObject *parent) : AbstractDigitalActionSwing(parent)
{
 setObjectName("ActionSensorSwing");
}
/**
 * Configures an ActionSensor object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class ActionSensorSwing extends AbstractDigitalActionSwing {



    //@Override
    /*protected*/ void ActionSensorSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ActionSensor* action = (ActionSensor*)object->bself();

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

        sensorBeanPanel = new BeanSelectPanel((Manager*)InstanceManager::getDefault("SensorManager"), nullptr);
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
        for (ActionSensor::SensorState::STATE e : ActionSensor::SensorState::values()) {
            _stateComboBox->addItem(e);
        }
//        JComboBoxUtil::setupComboBoxMaxRows(_stateComboBox);

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


        if (action != nullptr) {
            switch (action->getAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneSensor->setSelectedComponent(_panelSensorDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneSensor->setSelectedComponent(_panelSensorReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneSensor->setSelectedComponent(_panelSensorLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneSensor->setSelectedComponent(_panelSensorFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            if (action->getSensor() != nullptr) {
                sensorBeanPanel->setDefaultNamedBean(action->getSensor()->getBean());
            }
            _sensorReferenceTextField->setText(action->getReference());
            _sensorLocalVariableTextField->setText(action->getLocalVariable());
            _sensorFormulaTextField->setText(action->getFormula());

            switch (action->getStateAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneSensorState->setSelectedComponent(_panelSensorStateDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneSensorState->setSelectedComponent(_panelSensorStateReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneSensorState->setSelectedComponent(_panelSensorStateLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneSensorState->setSelectedComponent(_panelSensorStateFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getStateAddressing()));
            }
            _stateComboBox->setSelectedItem(action->getBeanState());
            _sensorStateReferenceTextField->setText(action->getStateReference());
            _sensorStateLocalVariableTextField->setText(action->getStateLocalVariable());
            _sensorStateFormulaTextField->setText(action->getStateFormula());
        }

        QList<JComponent*> components = QList<JComponent*>{
            _tabbedPaneSensor,
            _tabbedPaneSensorState};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Set sensor %1 to %2"),components);

        for (JComponent* c : componentList) panel->layout()->addWidget(c->jself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ActionSensorSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionSensor* action = new ActionSensor("IQDA1", "");

        try {
            if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorReference) {
                action->setReference(_sensorReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            if (_tabbedPaneSensorState->getSelectedComponent() == _panelSensorStateReference) {
                action->setStateReference(_sensorStateReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            action->setFormula(_sensorFormulaTextField->text());
            if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
            } else {
                throw new IllegalArgumentException("_tabbedPane has unknown selection");
            }
        } catch (ParserException* e) {
            errorMessages->append("Cannot parse formula: " + e->getMessage());
        }
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ActionSensorSwing::getAutoSystemName() {
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->getAutoSystemName();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* ActionSensorSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ActionSensor* action = new ActionSensor(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionSensorSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ActionSensor*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ActionSensor but is a: ")+object->bself()->metaObject()->className());
        }
        ActionSensor* action = (ActionSensor*)object->bself();
        if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorDirect) {
            Sensor* sensor = (Sensor*)sensorBeanPanel->getNamedBean()->self();
            if (sensor != nullptr) {
                NamedBeanHandle<Sensor*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(sensor->getDisplayName(), sensor);
                action->setSensor(handle);
            } else {
                action->removeSensor();
            }
        } else {
            action->removeSensor();
        }
        try {
            if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
                action->setReference(_sensorReferenceTextField->text());
            } else if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
                action->setLocalVariable(_sensorLocalVariableTextField->text());
            } else if (_tabbedPaneSensor->getSelectedComponent() == _panelSensorFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
                action->setFormula(_sensorFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneSensor has unknown selection");
            }

            if (_tabbedPaneSensorState->getSelectedComponent() == _panelSensorStateDirect) {
                action->setStateAddressing(NamedBeanAddressing::Direct);
                action->setBeanState((ActionSensor::SensorState::STATE)_stateComboBox->getItemAt(_stateComboBox->getSelectedIndex()).toInt());
            } else if (_tabbedPaneSensorState->getSelectedComponent() == _panelSensorStateReference) {
                action->setStateAddressing(NamedBeanAddressing::Reference);
                action->setStateReference(_sensorStateReferenceTextField->text());
            } else if (_tabbedPaneSensorState->getSelectedComponent() == _panelSensorStateLocalVariable) {
                action->setStateAddressing(NamedBeanAddressing::LocalVariable);
                action->setStateLocalVariable(_sensorStateLocalVariableTextField->text());
            } else if (_tabbedPaneSensorState->getSelectedComponent() == _panelSensorStateFormula) {
                action->setStateAddressing(NamedBeanAddressing::Formula);
                action->setStateFormula(_sensorStateFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneSensorState has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ActionSensorSwing::toString() {
        return tr("Sensor");
    }

    //@Override
    /*public*/  void ActionSensorSwing::dispose() {
        if (sensorBeanPanel != nullptr) {
            sensorBeanPanel->dispose();
        }
    }

