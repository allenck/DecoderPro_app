#include "actionturnoutswing.h"
#include "beanselectpanel.h"
#include "jtabbedpane.h"
#include "jtextfield.h"
#include "logixng/actionturnout.h"
#include "instancemanager.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/parserexception.h"

ActionTurnoutSwing::ActionTurnoutSwing(QObject *parent)
    : AbstractDigitalActionSwing{parent}
{

}
/**
 * Configures an ActionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class ActionTurnoutSwing extends AbstractDigitalActionSwing {



    //@Override
    /*protected*/ void ActionTurnoutSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
    ActionTurnout* action = (ActionTurnout*)object->bself();

        panel = new JPanel(new FlowLayout);

        _tabbedPaneTurnout = new JTabbedPane();
        _panelTurnoutDirect = new JPanel(new FlowLayout);
        _panelTurnoutReference = new JPanel(new FlowLayout);
        _panelTurnoutLocalVariable = new JPanel(new FlowLayout);
        _panelTurnoutFormula = new JPanel(new FlowLayout);

        _tabbedPaneTurnout->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelTurnoutDirect);
        _tabbedPaneTurnout->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelTurnoutReference);
        _tabbedPaneTurnout->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelTurnoutLocalVariable);
        _tabbedPaneTurnout->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelTurnoutFormula);

        turnoutBeanPanel = new BeanSelectPanel(((AbstractTurnoutManager*)InstanceManager::getDefault("TurnoutManager")), nullptr);
        _panelTurnoutDirect->layout()->addWidget(turnoutBeanPanel);

        _turnoutReferenceTextField = new JTextField();
        _turnoutReferenceTextField->setColumns(30);
        _panelTurnoutReference->layout()->addWidget(_turnoutReferenceTextField);

        _turnoutLocalVariableTextField = new JTextField();
        _turnoutLocalVariableTextField->setColumns(30);
        _panelTurnoutLocalVariable->layout()->addWidget(_turnoutLocalVariableTextField);

        _turnoutFormulaTextField = new JTextField();
        _turnoutFormulaTextField->setColumns(30);
        _panelTurnoutFormula->layout()->addWidget(_turnoutFormulaTextField);


        _tabbedPaneTurnoutState = new JTabbedPane();
        _panelTurnoutStateDirect = new JPanel(new FlowLayout);
        _panelTurnoutStateReference = new JPanel(new FlowLayout);
        _panelTurnoutStateLocalVariable = new JPanel(new FlowLayout);
        _panelTurnoutStateFormula = new JPanel(new FlowLayout);

        _tabbedPaneTurnoutState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelTurnoutStateDirect);
        _tabbedPaneTurnoutState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelTurnoutStateReference);
        _tabbedPaneTurnoutState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelTurnoutStateLocalVariable);
        _tabbedPaneTurnoutState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelTurnoutStateFormula);

        _stateComboBox = new JComboBox();
        for ( ActionTurnout::TurnoutState::STATE e : ActionTurnout::TurnoutState::values()) {
            _stateComboBox->addItem(ActionTurnout::TurnoutState::toString(e),e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_stateComboBox);

        _panelTurnoutStateDirect->layout()->addWidget(_stateComboBox);

        _turnoutStateReferenceTextField = new JTextField();
        _turnoutStateReferenceTextField->setColumns(30);
        _panelTurnoutStateReference->layout()->addWidget(_turnoutStateReferenceTextField);

        _turnoutStateLocalVariableTextField = new JTextField();
        _turnoutStateLocalVariableTextField->setColumns(30);
        _panelTurnoutStateLocalVariable->layout()->addWidget(_turnoutStateLocalVariableTextField);

        _turnoutStateFormulaTextField = new JTextField();
        _turnoutStateFormulaTextField->setColumns(30);
        _panelTurnoutStateFormula->layout()->addWidget(_turnoutStateFormulaTextField);


        if (action != nullptr) {
            switch (action->getAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneTurnout->setSelectedComponent(_panelTurnoutDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneTurnout->setSelectedComponent(_panelTurnoutReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneTurnout->setSelectedComponent(_panelTurnoutLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneTurnout->setSelectedComponent(_panelTurnoutFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            if (action->getTurnout() != nullptr) {
                turnoutBeanPanel->setDefaultNamedBean(action->getTurnout()->getBean());
            }
            _turnoutReferenceTextField->setText(action->getReference());
            _turnoutLocalVariableTextField->setText(action->getLocalVariable());
            _turnoutFormulaTextField->setText(action->getFormula());

            switch (action->getStateAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneTurnoutState->setSelectedComponent(_panelTurnoutStateDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneTurnoutState->setSelectedComponent(_panelTurnoutStateReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneTurnoutState->setSelectedComponent(_panelTurnoutStateLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneTurnoutState->setSelectedComponent(_panelTurnoutStateFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            _stateComboBox->setSelectedItem(action->getBeanState());
            _turnoutStateReferenceTextField->setText(action->getStateReference());
            _turnoutStateLocalVariableTextField->setText(action->getStateLocalVariable());
            _turnoutStateFormulaTextField->setText(action->getStateFormula());
        }

        QList<JComponent*> components = QList<JComponent*>{
            _tabbedPaneTurnout,
            _tabbedPaneTurnoutState};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Set turnout {0} to {1}"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget((QWidget*)c->jself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ActionTurnoutSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionTurnout* action = new ActionTurnout("IQDA1", "");

        try {
            if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutReference) {
                action->setReference(_turnoutReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            if (_tabbedPaneTurnoutState->getSelectedComponent() == _panelTurnoutStateReference) {
                action->setStateReference(_turnoutStateReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            action->setFormula(_turnoutFormulaTextField->text());
            if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutFormula) {
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
    /*public*/ MaleSocket* ActionTurnoutSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ActionTurnout* action = new ActionTurnout(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionTurnoutSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ActionTurnout*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object must be an ActionTurnout but is a: ")+object->bself()->metaObject()->className());
        }
        ActionTurnout* action = (ActionTurnout*)object->bself();
        if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutDirect) {
            Turnout* turnout = (Turnout*)turnoutBeanPanel->getNamedBean()->self();
            if (turnout != nullptr) {
                NamedBeanHandle<Turnout*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(turnout->getDisplayName(), turnout);
                action->setTurnout(handle);
            } else {
                action->removeTurnout();
            }
        } else {
            action->removeTurnout();
        }
        try {
            if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
                action->setReference(_turnoutReferenceTextField->text());
            } else if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
                action->setLocalVariable(_turnoutLocalVariableTextField->text());
            } else if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
                action->setFormula(_turnoutFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneTurnout has unknown selection");
            }

            if (_tabbedPaneTurnoutState->getSelectedComponent() == _panelTurnoutStateDirect) {
                action->setStateAddressing(NamedBeanAddressing::Direct);
                action->setBeanState((ActionTurnout::TurnoutState::STATE)_stateComboBox->getItemAt(_stateComboBox->getSelectedIndex()).toInt());
            } else if (_tabbedPaneTurnoutState->getSelectedComponent() == _panelTurnoutStateReference) {
                action->setStateAddressing(NamedBeanAddressing::Reference);
                action->setStateReference(_turnoutStateReferenceTextField->text());
            } else if (_tabbedPaneTurnoutState->getSelectedComponent() == _panelTurnoutStateLocalVariable) {
                action->setStateAddressing(NamedBeanAddressing::LocalVariable);
                action->setStateLocalVariable(_turnoutStateLocalVariableTextField->text());
            } else if (_tabbedPaneTurnoutState->getSelectedComponent() == _panelTurnoutStateFormula) {
                action->setStateAddressing(NamedBeanAddressing::Formula);
                action->setStateFormula(_turnoutStateFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneTurnoutState has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ActionTurnoutSwing::toString() {
        return tr("Turnout");
    }

    //@Override
    /*public*/ void ActionTurnoutSwing::dispose() {
        if (turnoutBeanPanel != nullptr) {
            turnoutBeanPanel->dispose();
        }
    }
