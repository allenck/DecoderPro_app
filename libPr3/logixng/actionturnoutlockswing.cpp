#include "actionturnoutlockswing.h"
#include "beanselectpanel.h"
#include "jtabbedpane.h"
#include "jtextfield.h"
#include "logixng/actionturnoutlock.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/parserexception.h"
#include "proxyturnoutmanager.h"
#include "instancemanager.h"
#include "actionturnoutlock.h"

ActionTurnoutLockSwing::ActionTurnoutLockSwing(QObject *parent)
    : AbstractDigitalActionSwing(parent)
{

}

/**
 * Configures an ActionTurnoutLock object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/ class ActionTurnoutLockSwing extends AbstractDigitalActionSwing {



    //@Override
    /*protected*/ void ActionTurnoutLockSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
     ActionTurnoutLock* action = nullptr;
     if(object)
      action = (ActionTurnoutLock*)object->bself();

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

        turnoutBeanPanel = new BeanSelectPanel((AbstractManager*)InstanceManager::getDefault("TurnoutManager"), nullptr);
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


        _tabbedPaneTurnoutLock = new JTabbedPane();
        _panelTurnoutLockDirect = new JPanel(new FlowLayout);
        _panelTurnoutLockReference = new JPanel(new FlowLayout);
        _panelTurnoutLockLocalVariable = new JPanel(new FlowLayout);
        _panelTurnoutLockFormula = new JPanel(new FlowLayout);

        _tabbedPaneTurnoutLock->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelTurnoutLockDirect);
        _tabbedPaneTurnoutLock->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelTurnoutLockReference);
        _tabbedPaneTurnoutLock->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelTurnoutLockLocalVariable);
        _tabbedPaneTurnoutLock->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelTurnoutLockFormula);

        _stateComboBox = new JComboBox();
        for (ActionTurnoutLock::TurnoutLock::ACT e : ActionTurnoutLock::TurnoutLock::values()) {
            _stateComboBox->addItem(ActionTurnoutLock::TurnoutLock::toString(e),e);
        }
//        JComboBoxUtil.setupComboBoxMaxRows(_stateComboBox);

        _panelTurnoutLockDirect->layout()->addWidget(_stateComboBox);

        _turnoutLockReferenceTextField = new JTextField();
        _turnoutLockReferenceTextField->setColumns(30);
        _panelTurnoutLockReference->layout()->addWidget(_turnoutLockReferenceTextField);

        _turnoutLockLocalVariableTextField = new JTextField();
        _turnoutLockLocalVariableTextField->setColumns(30);
        _panelTurnoutLockLocalVariable->layout()->addWidget(_turnoutLockLocalVariableTextField);

        _turnoutLockFormulaTextField = new JTextField();
        _turnoutLockFormulaTextField->setColumns(30);
        _panelTurnoutLockFormula->layout()->addWidget(_turnoutLockFormulaTextField);


        if (action != nullptr) {
            switch (action->getAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneTurnout->setSelectedComponent(_panelTurnoutDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneTurnout->setSelectedComponent(_panelTurnoutReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneTurnout->setSelectedComponent(_panelTurnoutLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneTurnout->setSelectedComponent(_panelTurnoutFormula); break;
            default: throw new IllegalArgumentException("invalid _addressing state: " +NamedBeanAddressing::toString( action->getAddressing()));
            }
            if (action->getTurnout() != nullptr) {
                turnoutBeanPanel->setDefaultNamedBean(action->getTurnout()->getBean());
            }
            _turnoutReferenceTextField->setText(action->getReference());
            _turnoutLocalVariableTextField->setText(action->getLocalVariable());
            _turnoutFormulaTextField->setText(action->getFormula());

            switch (action->getLockAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneTurnoutLock->setSelectedComponent(_panelTurnoutLockDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneTurnoutLock->setSelectedComponent(_panelTurnoutLockReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneTurnoutLock->setSelectedComponent(_panelTurnoutLockLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneTurnoutLock->setSelectedComponent(_panelTurnoutLockFormula); break;
            default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            _stateComboBox->setSelectedItem(action->getTurnoutLock());
            _turnoutLockReferenceTextField->setText(action->getLockReference());
            _turnoutLockLocalVariableTextField->setText(action->getLockLocalVariable());
            _turnoutLockFormulaTextField->setText(action->getLockFormula());
        }

        QList<JComponent*> components =  QList<JComponent*>{
            _tabbedPaneTurnout,
            _tabbedPaneTurnoutLock};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Set turnout lock for {0} to {1}"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget((QWidget*)c->jself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ActionTurnoutLockSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionTurnoutLock* action = new ActionTurnoutLock("IQDA1", "");

        try {
            if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutReference) {
                action->setReference(_turnoutReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            if (_tabbedPaneTurnoutLock->getSelectedComponent() == _panelTurnoutLockReference) {
                action->setLockReference(_turnoutLockReferenceTextField->text());
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
    /*public*/ MaleSocket* ActionTurnoutLockSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ActionTurnoutLock* action = new ActionTurnoutLock(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionTurnoutLockSwing::updateObject(/*@Nonnull*/ Base* object) {
    if(!object) throw new NullPointerException("invalid Base pointer");
        if (! (qobject_cast<ActionTurnoutLock*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ActionTurnoutLock but is a: ")+object->bself()->metaObject()->className());
        }
        ActionTurnoutLock* action = (ActionTurnoutLock*)object->bself();
        if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutDirect) {
            NamedBean* nb = turnoutBeanPanel->getNamedBean();
            if (nb != nullptr) {
                Turnout* turnout = (Turnout*)nb->self();

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

            if (_tabbedPaneTurnoutLock->getSelectedComponent() == _panelTurnoutLockDirect) {
                action->setLockAddressing(NamedBeanAddressing::Direct);
                action->setTurnoutLock(ActionTurnoutLock::TurnoutLock::valueOf(_stateComboBox->currentText()));
            } else if (_tabbedPaneTurnoutLock->getSelectedComponent() == _panelTurnoutLockReference) {
                action->setLockAddressing(NamedBeanAddressing::Reference);
                action->setLockReference(_turnoutLockReferenceTextField->text());
            } else if (_tabbedPaneTurnoutLock->getSelectedComponent() == _panelTurnoutLockLocalVariable) {
                action->setLockAddressing(NamedBeanAddressing::LocalVariable);
                action->setLockLocalVariable(_turnoutLockLocalVariableTextField->text());
            } else if (_tabbedPaneTurnoutLock->getSelectedComponent() == _panelTurnoutLockFormula) {
                action->setLockAddressing(NamedBeanAddressing::Formula);
                action->setLockFormula(_turnoutLockFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneTurnoutLock has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ActionTurnoutLockSwing::toString() {
        return tr("TurnoutLock");
    }

    //@Override
    /*public*/ void ActionTurnoutLockSwing::dispose() {
        if (turnoutBeanPanel != nullptr) {
            turnoutBeanPanel->dispose();
        }
    }


