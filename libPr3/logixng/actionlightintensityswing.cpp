#include "actionlightintensityswing.h"
#include "beanselectpanel.h"
#include "jlabel.h"
#include "jtabbedpane.h"
#include "jtextfield.h"
#include "logixng/actionlightintensity.h"
#include "box.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/parserexception.h"


ActionLightIntensitySwing::ActionLightIntensitySwing(QObject *parent)
    : AbstractDigitalActionSwing{parent}
{

}
/**
 * Configures an ActionLightIntensity object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class ActionLightIntensitySwing extends AbstractDigitalActionSwing {



    //@Override
    /*protected*/ void ActionLightIntensitySwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ActionLightIntensity* action = nullptr;
        if(object) action = (ActionLightIntensity*)object->bself();

        panel = new JPanel(new FlowLayout);
        panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));

        _tabbedPaneLight = new JTabbedPane();
        _panelLightDirect = new JPanel(new FlowLayout);
        _panelLightReference = new JPanel(new FlowLayout);
        _panelLightLocalVariable = new JPanel(new FlowLayout);
        _panelLightFormula = new JPanel(new FlowLayout);

        _tabbedPaneLight->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelLightDirect);
        _tabbedPaneLight->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelLightReference);
        _tabbedPaneLight->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelLightLocalVariable);
        _tabbedPaneLight->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelLightFormula);

        lightBeanPanel = new BeanSelectPanel((AbstractManager*)InstanceManager::getDefault("VariableLightManager"), nullptr);
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
                default: throw new IllegalArgumentException(tr("invalid _addressing state: ") + NamedBeanAddressing::toString(action->getAddressing()));
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

        JPanel* labelPanel = new JPanel();
        labelPanel->layout()->addWidget(new JLabel(tr("       </td></tr></table></html>")));
        panel->layout()->addWidget(labelPanel);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ActionLightIntensitySwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionLightIntensity* action = new ActionLightIntensity("IQDA1", "");

        try {
            if (_tabbedPaneLight->getSelectedComponent() == _panelLightReference) {
                action->setReference(_lightReferenceTextField->text());
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
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ MaleSocket* ActionLightIntensitySwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ActionLightIntensity* action = new ActionLightIntensity(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionLightIntensitySwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ActionLightIntensity*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object must be an ActionLightIntensity but is a: ")+object->bself()->metaObject()->className());
        }
        ActionLightIntensity* action = (ActionLightIntensity*)object->bself();
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
        } catch (ParseException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ActionLightIntensitySwing::toString() {
        return tr("ActionLightIntensity");
    }

    //@Override
    /*public*/ void ActionLightIntensitySwing::dispose() {
    }
