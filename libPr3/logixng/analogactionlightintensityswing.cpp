#include "analogactionlightintensityswing.h"
#include "jtabbedpane.h"
#include "jtextfield.h"
#include "jlabel.h"
#include "analogactionlightintensity.h"
#include "variablelightmanager.h"
#include "beanselectpanel.h"
#include "box.h"
#include "parserexception.h"
#include "defaultanalogactionmanager.h"

/**
 * Configures an AnalogActionLightIntensity object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class AnalogActionLightIntensitySwing extends AbstractAnalogActionSwing {



    //@Override
    /*protected*/ void AnalogActionLightIntensitySwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        AnalogActionLightIntensity* action = (AnalogActionLightIntensity*)object->bself();

        panel = new JPanel();
        panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));

        _tabbedPaneLight = new JTabbedPane();
        _panelLightDirect = new JPanel();
        _panelLightReference = new JPanel();
        _panelLightLocalVariable = new JPanel();
        _panelLightFormula = new JPanel();

        _tabbedPaneLight->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelLightDirect);
        _tabbedPaneLight->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelLightReference);
        _tabbedPaneLight->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelLightLocalVariable);
        _tabbedPaneLight->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelLightFormula);

        lightBeanPanel = new BeanSelectPanel((VariableLightManager*)InstanceManager::getDefault("VariableLightManager"), nullptr);
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


        if (action != nullptr) {
            switch (action->getAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneLight->setSelectedComponent(_panelLightDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneLight->setSelectedComponent(_panelLightReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneLight->setSelectedComponent(_panelLightLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneLight->setSelectedComponent(_panelLightFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            if (action->getLight() != nullptr) {
                lightBeanPanel->setDefaultNamedBean(action->getLight()->getBean());
            }
            _lightReferenceTextField->setText(action->getReference());
            _lightLocalVariableTextField->setText(action->getLocalVariable());
            _lightFormulaTextField->setText(action->getFormula());
        }

        panel->layout()->addWidget(_tabbedPaneLight);

        panel->layout()->addWidget(Box::createVerticalStrut(10));

        JPanel* labelPanel = new JPanel(new FlowLayout());
        labelPanel->layout()->addWidget(new JLabel(tr(" <html>                    \
<table width=\"400\"><tr><td>                                         \
The light intensity is in percent, between 0 and 100.<p>            \
This differs from the Light table, where the intensity is given     \
between 0.0 and 1.0.                                                \
</td></tr></table>                                                  \
</html>")));
        panel->layout()->addWidget(labelPanel);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool AnalogActionLightIntensitySwing::validate(/*@Nonnull*/ QList<QString> errorMessages) {
        // Create a temporary action to test formula
        AnalogActionLightIntensity* action = new AnalogActionLightIntensity("IQAA1", "");

        try {
            if (_tabbedPaneLight->getSelectedComponent() == _panelLightReference) {
                action->setReference(_lightReferenceTextField->toString());
           }
        } catch (IllegalArgumentException* e) {
            errorMessages.append(e->getMessage());
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
            errorMessages.append("Cannot parse formula: " + e->getMessage());
        }
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* AnalogActionLightIntensitySwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        AnalogActionLightIntensity* action = new AnalogActionLightIntensity(systemName, userName);
        updateObject(action);
        return ((DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogActionLightIntensitySwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<AnalogActionLightIntensity*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an AnalogActionLightIntensity but is a: ")+object->bself()->metaObject()->className());
        }
        AnalogActionLightIntensity* action = (AnalogActionLightIntensity*)object->bself();
        if (_tabbedPaneLight->getSelectedComponent() == _panelLightDirect) {
            VariableLight* light = (VariableLight*)lightBeanPanel->getNamedBean()->self();
            if (light != nullptr) {
                NamedBeanHandle<VariableLight*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(light->getDisplayName(), light);
                action->setLight(handle);
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
        } catch (ParserException* e) {
            throw new RuntimeException(QString("ParserException: ")+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AnalogActionLightIntensitySwing::toString() {
        return tr("Light intensity");
    }

    //@Override
    /*public*/  void AnalogActionLightIntensitySwing::dispose() {
    }
