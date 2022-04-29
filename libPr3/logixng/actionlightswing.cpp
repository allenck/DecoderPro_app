#include "actionlightswing.h"
#include "instancemanager.h"
#include "actionlight.h"
#include "jtabbedpane.h"
#include "jcombobox.h"
#include "beanselectpanel.h"
#include "proxylightmanager.h"
#include "jtextfield.h"
#include "swingconfiguratorinterface.h"
#include "parserexception.h"
#include "defaultdigitalactionmanager.h"


ActionLightSwing::ActionLightSwing(QObject *parent) : AbstractDigitalActionSwing(parent)
{
 setObjectName("ActionLightSwing");
}

/**
 * Configures an ActionLight object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class ActionLightSwing extends AbstractDigitalActionSwing {




    //@Override
    /*protected*/ void ActionLightSwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ActionLight* action = (ActionLight*)object->bself();

        panel = new JPanel(new FlowLayout());

        _tabbedPaneLight = new JTabbedPane();
        _panelLightDirect = new JPanel(new FlowLayout());
        _panelLightReference = new JPanel(new FlowLayout());
        _panelLightLocalVariable = new JPanel(new FlowLayout());
        _panelLightFormula = new JPanel(new FlowLayout());

        _tabbedPaneLight->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelLightDirect);
        _tabbedPaneLight->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelLightReference);
        _tabbedPaneLight->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelLightLocalVariable);
        _tabbedPaneLight->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelLightFormula);

        lightBeanPanel = new BeanSelectPanel((AbstractProxyManager*)InstanceManager::getDefault("LightManager"), nullptr);
        _panelLightDirect->layout()->addWidget(lightBeanPanel);

        _lightReferenceTextField = new JTextField();
        _lightReferenceTextField->setColumns(30);
        _panelLightReference->layout()->addWidget(_lightReferenceTextField);

        _lightLocalVariableTextField = new JTextField();
        _lightLocalVariableTextField->setColumns(30);
        _panelLightLocalVariable->layout()->addWidget(_lightLocalVariableTextField);

        _lightFormulaTextField = new JTextField();
        _lightFormulaTextField->setColumns(30);
        _panelLightFormula->layout()->addWidget(_lightFormulaTextField);


        _tabbedPaneLightState = new JTabbedPane();
        _panelLightStateDirect = new JPanel(new FlowLayout());
        _panelLightStateReference = new JPanel(new FlowLayout());
        _panelLightStateLocalVariable = new JPanel(new FlowLayout());
        _panelLightStateFormula = new JPanel(new FlowLayout());

        _tabbedPaneLightState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelLightStateDirect);
        _tabbedPaneLightState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelLightStateReference);
        _tabbedPaneLightState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelLightStateLocalVariable);
        _tabbedPaneLightState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelLightStateFormula);

        _stateComboBox = new JComboBox();
        for (ActionLight::LightState::STATE e : ActionLight::LightState::values()) {
            _stateComboBox->addItem(ActionLight::LightState::toString(e), e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_stateComboBox);
        connect(_stateComboBox, &JComboBox::currentIndexChanged, [=] {
            setDataPanelState();
        });

        _panelLightStateDirect->layout()->addWidget(_stateComboBox);

        _lightStateReferenceTextField = new JTextField();
        _lightStateReferenceTextField->setColumns(30);
        _panelLightStateReference->layout()->addWidget(_lightStateReferenceTextField);

        _lightStateLocalVariableTextField = new JTextField();
        _lightStateLocalVariableTextField->setColumns(30);
        _panelLightStateLocalVariable->layout()->addWidget(_lightStateLocalVariableTextField);

        _lightStateFormulaTextField = new JTextField();
        _lightStateFormulaTextField->setColumns(30);
        _panelLightStateFormula->layout()->addWidget(_lightStateFormulaTextField);


        // Right section
        _tabbedPaneData = new JTabbedPane();
        _panelDataDirect = new JPanel(new FlowLayout());
        _panelDataReference = new JPanel(new FlowLayout());
        _panelDataLocalVariable = new JPanel(new FlowLayout());
        _panelDataFormula = new JPanel(new FlowLayout());

        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelDataDirect);
        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelDataReference);
        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelDataLocalVariable);
        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelDataFormula);

        _lightDataDirectTextField = new JTextField();
        _lightDataDirectTextField->setColumns(30);
        _panelDataDirect->layout()->addWidget(_lightDataDirectTextField);

        _lightDataReferenceTextField = new JTextField();
        _lightDataReferenceTextField->setColumns(30);
        _panelDataReference->layout()->addWidget(_lightDataReferenceTextField);

        _lightDataLocalVariableTextField = new JTextField();
        _lightDataLocalVariableTextField->setColumns(30);
        _panelDataLocalVariable->layout()->addWidget(_lightDataLocalVariableTextField);

        _lightDataFormulaTextField = new JTextField();
        _lightDataFormulaTextField->setColumns(30);
        _panelDataFormula->layout()->addWidget(_lightDataFormulaTextField);

        setDataPanelState();

        if (action != nullptr) {
            switch (action->getAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneLight->setSelectedComponent(_panelLightDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneLight->setSelectedComponent(_panelLightReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneLight->setSelectedComponent(_panelLightLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneLight->setSelectedComponent(_panelLightFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " +NamedBeanAddressing::toString( action->getAddressing()));
            }
            if (action->getLight() != nullptr) {
                lightBeanPanel->setDefaultNamedBean(action->getLight()->getBean());
            }
            _lightReferenceTextField->setText(action->getReference());
            _lightLocalVariableTextField->setText(action->getLocalVariable());
            _lightFormulaTextField->setText(action->getFormula());

            switch (action->getStateAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneLightState->setSelectedComponent(_panelLightStateDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneLightState->setSelectedComponent(_panelLightStateReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneLightState->setSelectedComponent(_panelLightStateLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneLightState->setSelectedComponent(_panelLightStateFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            _stateComboBox->setSelectedItem(action->getBeanState());
            _lightStateReferenceTextField->setText(action->getStateReference());
            _lightStateLocalVariableTextField->setText(action->getStateLocalVariable());
            _lightStateFormulaTextField->setText(action->getStateFormula());

            switch (action->getDataAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneData->setSelectedComponent(_panelDataDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneData->setSelectedComponent(_panelDataReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneData->setSelectedComponent(_panelDataLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneData->setSelectedComponent(_panelDataFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getDataAddressing()));
            }
            _lightDataReferenceTextField->setText(action->getDataReference());
            _lightDataLocalVariableTextField->setText(action->getDataLocalVariable());
            _lightDataFormulaTextField->setText(action->getDataFormula());

            _lightDataDirectTextField->setText(QString::number(action->getLightValue()));
            setDataPanelState();
        }

        QList<JComponent*> components = QList<JComponent*>{
            _tabbedPaneLight,
            _tabbedPaneLightState,
            _tabbedPaneData};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Set light %1 to %2 %3"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget(c->jself());
    }

    /*private*/ void ActionLightSwing::setDataPanelState() {
        bool newState = _stateComboBox->getSelectedItem().toInt() == ActionLight::LightState::Intensity ||
                _stateComboBox->getSelectedItem().toInt() == ActionLight::LightState::Interval;
        _tabbedPaneData->QWidget::setEnabled(newState);
        _lightDataDirectTextField->setEnabled(newState);
        _lightDataReferenceTextField->setEnabled(newState);
        _lightDataLocalVariableTextField->setEnabled(newState);
        _lightDataFormulaTextField->setEnabled(newState);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ActionLightSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionLight* action = new ActionLight("IQDA1", "");

        try {
            if (_tabbedPaneLight->getSelectedComponent() == _panelLightReference) {
                action->setReference(_lightReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            if (_tabbedPaneLightState->getSelectedComponent() == _panelLightStateReference) {
                action->setStateReference(_lightStateReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            action->setFormula(_lightFormulaTextField->text());
            if (_tabbedPaneLight->getSelectedComponent() == _panelLightDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneLight->getSelectedComponent() == _panelLightReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneLight->getSelectedComponent() == _panelLightLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneLight->getSelectedComponent() == _panelLightFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
            } else {
                throw new IllegalArgumentException("_tabbedPane has unknown selection");
            }
        } catch (ParserException* e) {
            errorMessages->append("Cannot parse formula: " + e->getMessage());
        }


        try {
            if (_tabbedPaneData->getSelectedComponent() == _panelDataReference) {
                action->setDataReference(_lightDataReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            action->setDataFormula(_lightDataFormulaTextField->text());
            if (_tabbedPaneData->getSelectedComponent() == _panelDataDirect) {
                action->setDataAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataReference) {
                action->setDataAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataLocalVariable) {
                action->setDataAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataFormula) {
                action->setDataAddressing(NamedBeanAddressing::Formula);
            } else {
                throw new IllegalArgumentException("_tabbedPane has unknown selection");
            }
        } catch (ParserException* e) {
            errorMessages->append("Cannot parse formula: " + e->getMessage());
        }

        if (_tabbedPaneData->getSelectedComponent() == _panelDataDirect) {
            ActionLight::LightState::STATE oper = (ActionLight::LightState::STATE)_stateComboBox->getItemAt(_stateComboBox->getSelectedIndex()).toInt();

            if (oper == ActionLight::LightState::Intensity) {
                bool result = true;
                try {
                 bool ok;
                    int value = _lightDataDirectTextField->text().toInt(&ok); if(!ok) throw new NumberFormatException();
                    if (value < 0 || value > 100) {
                        result = false;
                    }
                } catch (NumberFormatException* ex) {
                    result = false;
                }
                if (!result) {
                    errorMessages->append(tr("The light intensity range is 0 (dark) to 100 (full brightness)"));
                    return false;
                }
            }

            if (oper == ActionLight::LightState::Interval) {
                bool result = true;
                try {
                 bool ok;
                    int value = _lightDataDirectTextField->text().toInt(&ok); if(!ok) throw new NumberFormatException();
                    if (value < 0) {
                        result = false;
                    }
                } catch (NumberFormatException* ex) {
                    result = false;
                }
                if (!result) {
                    errorMessages->append(tr("The transition time is zero (instantaneous) or greater"));
                    return false;
                }
            }
        }

        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* ActionLightSwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        ActionLight* action = new ActionLight(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionLightSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ActionLight*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ActionLight but is a: ")+object->bself()->metaObject()->className());
        }
        ActionLight* action = (ActionLight*)object->bself();
        if (_tabbedPaneLight->getSelectedComponent() == _panelLightDirect) {
            if (lightBeanPanel != nullptr) {
                Light* light = (Light* )lightBeanPanel->getNamedBean()->self();
                if (light != nullptr) {
                    NamedBeanHandle<Light*>* handle
                            = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                    ->getNamedBeanHandle(light->getDisplayName(), light);
                    action->setLight(handle);
                } else {
                    action->removeLight();
                }
            } else {
                action->removeLight();
            }
        } else {
            action->removeLight();
        }
        try {
            if (_tabbedPaneLight->getSelectedComponent() == _panelLightDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneLight->getSelectedComponent() == _panelLightReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
                action->setReference(_lightReferenceTextField->text());
            } else if (_tabbedPaneLight->getSelectedComponent() == _panelLightLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
                action->setLocalVariable(_lightLocalVariableTextField->text());
            } else if (_tabbedPaneLight->getSelectedComponent() == _panelLightFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
                action->setFormula(_lightFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneLight has unknown selection");
            }

            if (_tabbedPaneLightState->getSelectedComponent() == _panelLightStateDirect) {
                action->setStateAddressing(NamedBeanAddressing::Direct);
                action->setBeanState((ActionLight::LightState::STATE)_stateComboBox->getItemAt(_stateComboBox->getSelectedIndex()).toInt());
            } else if (_tabbedPaneLightState->getSelectedComponent() == _panelLightStateReference) {
                action->setStateAddressing(NamedBeanAddressing::Reference);
                action->setStateReference(_lightStateReferenceTextField->text());
            } else if (_tabbedPaneLightState->getSelectedComponent() == _panelLightStateLocalVariable) {
                action->setStateAddressing(NamedBeanAddressing::LocalVariable);
                action->setStateLocalVariable(_lightStateLocalVariableTextField->text());
            } else if (_tabbedPaneLightState->getSelectedComponent() == _panelLightStateFormula) {
                action->setStateAddressing(NamedBeanAddressing::Formula);
                action->setStateFormula(_lightStateFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneLightState has unknown selection");
            }

            // Right section
            if (_tabbedPaneData->getSelectedComponent() == _panelDataDirect) {
                action->setDataAddressing(NamedBeanAddressing::Direct);
                // Handle optional data field
                if (action->getBeanState() == ActionLight::LightState::Intensity ||
                        action->getBeanState() == ActionLight::LightState::Interval) {
                    int value;
                    try {
                     bool ok;
                        value = _lightDataDirectTextField->text().toInt(&ok); if(!ok) throw new NumberFormatException();
                    } catch (NumberFormatException* ex) {
                        value = 0;
                    }
                    action->setLightValue(value);
                }
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataReference) {
                action->setDataAddressing(NamedBeanAddressing::Reference);
                action->setDataReference(_lightDataReferenceTextField->text());
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataLocalVariable) {
                action->setDataAddressing(NamedBeanAddressing::LocalVariable);
                action->setDataLocalVariable(_lightDataLocalVariableTextField->text());
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataFormula) {
                action->setDataAddressing(NamedBeanAddressing::Formula);
                action->setDataFormula(_lightDataFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneData has unknown selection");
            }

        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ActionLightSwing::toString() {
        return tr("Light");
    }

    //@Override
    /*public*/  void ActionLightSwing::dispose() {
        if (lightBeanPanel != nullptr) {
            lightBeanPanel->dispose();
        }
    }
