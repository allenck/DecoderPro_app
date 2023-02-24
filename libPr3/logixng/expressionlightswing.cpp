#include "expressionlightswing.h"
#include "abstractlightmanager.h"
#include "beanselectpanel.h"
#include "jtabbedpane.h"
#include "jtextfield.h"
#include "logixng/defaultdigitalexpressionmanager.h"
#include "logixng/expressionlight.h"
#include "parserexception.h"

ExpressionLightSwing::ExpressionLightSwing(QObject *parent)
    : AbstractDigitalExpressionSwing{parent}
{

}
/**
 * Configures an ExpressionLight object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/ class ExpressionLightSwing extends AbstractDigitalExpressionSwing {




    //@Override
    /*protected*/ void ExpressionLightSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ExpressionLight* expression = (ExpressionLight*)object->bself();

        panel = new JPanel(new FlowLayout);

        _tabbedPaneLight = new JTabbedPane();
        _panelLightDirect = new JPanel(new FlowLayout());
        _panelLightReference = new JPanel(new FlowLayout());
        _panelLightLocalVariable = new JPanel(new FlowLayout());
        _panelLightFormula = new JPanel(new FlowLayout());

        _tabbedPaneLight->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelLightDirect);
        _tabbedPaneLight->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelLightReference);
        _tabbedPaneLight->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelLightLocalVariable);
        _tabbedPaneLight->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelLightFormula);

        _lightBeanPanel = new BeanSelectPanel(((AbstractLightManager*)InstanceManager::getDefault("LightManager")), nullptr);
        _panelLightDirect->layout()->addWidget(_lightBeanPanel);

        _lightReferenceTextField = new JTextField();
        _lightReferenceTextField->setColumns(30);
        _panelLightReference->layout()->addWidget(_lightReferenceTextField);

        _lightLocalVariableTextField = new JTextField();
        _lightLocalVariableTextField->setColumns(30);
        _panelLightLocalVariable->layout()->addWidget(_lightLocalVariableTextField);

        _lightFormulaTextField = new JTextField();
        _lightFormulaTextField->setColumns(30);
        _panelLightFormula->layout()->addWidget(_lightFormulaTextField);


        _is_IsNot_ComboBox = new JComboBox();
        for (Is_IsNot_Enum::VAL e : Is_IsNot_Enum::values()) {
            _is_IsNot_ComboBox->addItem(Is_IsNot_Enum::toString(e), e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_is_IsNot_ComboBox);


        _tabbedPaneLightState = new JTabbedPane();
        _panelLightStateDirect = new JPanel(new FlowLayout);
        _panelLightStateReference = new JPanel(new FlowLayout);
        _panelLightStateLocalVariable = new JPanel(new FlowLayout);
        _panelLightStateFormula = new JPanel(new FlowLayout);

        _tabbedPaneLightState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelLightStateDirect);
        _tabbedPaneLightState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelLightStateReference);
        _tabbedPaneLightState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelLightStateLocalVariable);
        _tabbedPaneLightState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelLightStateFormula);

        _stateComboBox = new JComboBox();
        for (ExpressionLight::LightState::VALS e : ExpressionLight::LightState::values()) {
            _stateComboBox->addItem(ExpressionLight::LightState::toString(e), e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_stateComboBox);

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


        if (expression != nullptr) {
            switch (expression->getAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneLight->setSelectedComponent(_panelLightDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneLight->setSelectedComponent(_panelLightReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneLight->setSelectedComponent(_panelLightLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneLight->setSelectedComponent(_panelLightFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getAddressing()));
            }
            if (expression->getLight() != nullptr) {
                _lightBeanPanel->setDefaultNamedBean(expression->getLight()->getBean());
            }
            _lightReferenceTextField->setText(expression->getReference());
            _lightLocalVariableTextField->setText(expression->getLocalVariable());
            _lightFormulaTextField->setText(expression->getFormula());

            _is_IsNot_ComboBox->setSelectedItem(expression->get_Is_IsNot());

            switch (expression->getStateAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneLightState->setSelectedComponent(_panelLightStateDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneLightState->setSelectedComponent(_panelLightStateReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneLightState->setSelectedComponent(_panelLightStateLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneLightState->setSelectedComponent(_panelLightStateFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " +NamedBeanAddressing::toString( expression->getAddressing()));
            }
            _stateComboBox->setSelectedItem(expression->getBeanState());
            _lightStateReferenceTextField->setText(expression->getStateReference());
            _lightStateLocalVariableTextField->setText(expression->getStateLocalVariable());
            _lightStateFormulaTextField->setText(expression->getStateFormula());
        }

        QList<JComponent*> components = QList<JComponent*>{
            _tabbedPaneLight,
            _is_IsNot_ComboBox,
            _tabbedPaneLightState};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Light {0} {1} {2}"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget((QWidget*)c->jself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ExpressionLightSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary expression to test formula
        ExpressionLight* expression = new ExpressionLight("IQDE1", "");

        try {
            if (_tabbedPaneLight->getSelectedComponent() == _panelLightReference) {
                expression->setReference(_lightReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            if (_tabbedPaneLightState->getSelectedComponent() == _panelLightStateReference) {
                expression->setStateReference(_lightStateReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            expression->setFormula(_lightFormulaTextField->text());
            if (_tabbedPaneLight->getSelectedComponent() == _panelLightDirect) {
                expression->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneLight->getSelectedComponent() == _panelLightReference) {
                expression->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneLight->getSelectedComponent() == _panelLightLocalVariable) {
                expression->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneLight->getSelectedComponent() == _panelLightFormula) {
                expression->setAddressing(NamedBeanAddressing::Formula);
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
    /*public*/ MaleSocket* ExpressionLightSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ExpressionLight* expression = new ExpressionLight(systemName, userName);
        updateObject(expression);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionLightSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ExpressionLight*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ExpressionLight but is a: ")+object->bself()->metaObject()->className());
        }
        ExpressionLight* expression = (ExpressionLight*)object->bself();
        if (_tabbedPaneLight->getSelectedComponent() == _panelLightDirect) {
            Light* light = (Light*)_lightBeanPanel->getNamedBean()->self();
            if (light != nullptr) {
                NamedBeanHandle<Light*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(light->getDisplayName(), light);
                expression->setLight(handle);
            } else {
                expression->removeLight();
            }
        } else {
            expression->removeLight();
        }
        try {
            if (_tabbedPaneLight->getSelectedComponent() == _panelLightDirect) {
                expression->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneLight->getSelectedComponent() == _panelLightReference) {
                expression->setAddressing(NamedBeanAddressing::Reference);
                expression->setReference(_lightReferenceTextField->text());
            } else if (_tabbedPaneLight->getSelectedComponent() == _panelLightLocalVariable) {
                expression->setAddressing(NamedBeanAddressing::LocalVariable);
                expression->setLocalVariable(_lightLocalVariableTextField->text());
            } else if (_tabbedPaneLight->getSelectedComponent() == _panelLightFormula) {
                expression->setAddressing(NamedBeanAddressing::Formula);
                expression->setFormula(_lightFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneLight has unknown selection");
            }

            expression->set_Is_IsNot((Is_IsNot_Enum::VAL)_is_IsNot_ComboBox->getSelectedItem().toInt());

            if (_tabbedPaneLightState->getSelectedComponent() == _panelLightStateDirect) {
                expression->setStateAddressing(NamedBeanAddressing::Direct);
                expression->setBeanState((ExpressionLight::LightState::VALS)_stateComboBox->getSelectedItem().toInt());
            } else if (_tabbedPaneLightState->getSelectedComponent() == _panelLightStateReference) {
                expression->setStateAddressing(NamedBeanAddressing::Reference);
                expression->setStateReference(_lightStateReferenceTextField->text());
            } else if (_tabbedPaneLightState->getSelectedComponent() == _panelLightStateLocalVariable) {
                expression->setStateAddressing(NamedBeanAddressing::LocalVariable);
                expression->setStateLocalVariable(_lightStateLocalVariableTextField->text());
            } else if (_tabbedPaneLightState->getSelectedComponent() == _panelLightStateFormula) {
                expression->setStateAddressing(NamedBeanAddressing::Formula);
                expression->setStateFormula(_lightStateFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneLightState has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ExpressionLightSwing::toString() {
        return tr("Light");
    }

    //@Override
    /*public*/ void ExpressionLightSwing::dispose() {
        if (_lightBeanPanel != nullptr) {
            _lightBeanPanel->dispose();
        }
    }
