#include "actionentryexitswing.h"
#include "beanselectpanel.h"
#include "destinationpoints.h"
#include "jtabbedpane.h"
#include "jtextfield.h"
#include "logixng/actionentryexit.h"
#include "instancemanager.h"
#include "beanselectpanel.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/parserexception.h"

ActionEntryExitSwing::ActionEntryExitSwing(QObject *parent)
    : AbstractDigitalActionSwing{parent}
{

}
/**
 * Configures an EntryExit object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class ActionEntryExitSwing extends AbstractDigitalActionSwing {



    //@Override
    /*protected*/ void ActionEntryExitSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ActionEntryExit* action = nullptr;
        if(object) action = (ActionEntryExit*)object->bself();

        panel = new JPanel(new FlowLayout);

        _tabbedPaneEntryExit = new JTabbedPane();
        _panelEntryExitDirect = new JPanel(new FlowLayout);
        _panelEntryExitReference = new JPanel(new FlowLayout);
        _panelEntryExitLocalVariable = new JPanel(new FlowLayout);
        _panelEntryExitFormula = new JPanel(new FlowLayout);

        _tabbedPaneEntryExit->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelEntryExitDirect);
        _tabbedPaneEntryExit->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelEntryExitReference);
        _tabbedPaneEntryExit->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelEntryExitLocalVariable);
        _tabbedPaneEntryExit->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelEntryExitFormula);

        entryExitBeanPanel = new BeanSelectPanel((AbstractManager*)InstanceManager::getDefault("EntryExitPairs"), nullptr);
        _panelEntryExitDirect->layout()->addWidget(entryExitBeanPanel);

        _entryExitReferenceTextField = new JTextField();
        _entryExitReferenceTextField->setColumns(30);
        _panelEntryExitReference->layout()->addWidget(_entryExitReferenceTextField);

        _entryExitLocalVariableTextField = new JTextField();
        _entryExitLocalVariableTextField->setColumns(30);
        _panelEntryExitLocalVariable->layout()->addWidget(_entryExitLocalVariableTextField);

        _entryExitFormulaTextField = new JTextField();
        _entryExitFormulaTextField->setColumns(30);
        _panelEntryExitFormula->layout()->addWidget(_entryExitFormulaTextField);


        _tabbedPaneOperation = new JTabbedPane();
        _panelOperationDirect = new JPanel(new FlowLayout);
        _panelOperationReference = new JPanel(new FlowLayout);
        _panelOperationLocalVariable = new JPanel(new FlowLayout);
        _panelOperationFormula = new JPanel(new FlowLayout);

        _tabbedPaneOperation->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelOperationDirect);
        _tabbedPaneOperation->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelOperationReference);
        _tabbedPaneOperation->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelOperationLocalVariable);
        _tabbedPaneOperation->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelOperationFormula);

        _stateComboBox = new JComboBox();
        for (ActionEntryExit::Operation::TYPE e : ActionEntryExit::Operation::values()) {
            _stateComboBox->addItem(ActionEntryExit::Operation::toString(e), e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_stateComboBox);

        _panelOperationDirect->layout()->addWidget(_stateComboBox);

        _entryExitLockReferenceTextField = new JTextField();
        _entryExitLockReferenceTextField->setColumns(30);
        _panelOperationReference->layout()->addWidget(_entryExitLockReferenceTextField);

        _entryExitLockLocalVariableTextField = new JTextField();
        _entryExitLockLocalVariableTextField->setColumns(30);
        _panelOperationLocalVariable->layout()->addWidget(_entryExitLockLocalVariableTextField);

        _entryExitLockFormulaTextField = new JTextField();
        _entryExitLockFormulaTextField->setColumns(30);
        _panelOperationFormula->layout()->addWidget(_entryExitLockFormulaTextField);


        if (action != nullptr) {
            switch (action->getAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneEntryExit->setSelectedComponent(_panelEntryExitDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneEntryExit->setSelectedComponent(_panelEntryExitReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneEntryExit->setSelectedComponent(_panelEntryExitLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneEntryExit->setSelectedComponent(_panelEntryExitFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            if (action->getDestinationPoints() != nullptr) {
                entryExitBeanPanel->setDefaultNamedBean((NamedBean*)action->getDestinationPoints()->getBean());
            }
            _entryExitReferenceTextField->setText(action->getReference());
            _entryExitLocalVariableTextField->setText(action->getLocalVariable());
            _entryExitFormulaTextField->setText(action->getFormula());

            switch (action->getOperationAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneOperation->setSelectedComponent(_panelOperationDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneOperation->setSelectedComponent(_panelOperationReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneOperation->setSelectedComponent(_panelOperationLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneOperation->setSelectedComponent(_panelOperationFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            _stateComboBox->setSelectedItem(action->getOperationDirect());
            _entryExitLockReferenceTextField->setText(action->getOperationReference());
            _entryExitLockLocalVariableTextField->setText(action->getOperationLocalVariable());
            _entryExitLockFormulaTextField->setText(action->getLockFormula());
        }

        QList<JComponent*> components =  QList<JComponent*>{
            _tabbedPaneEntryExit,
            _tabbedPaneOperation};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Set entry exit {0} to {1}"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget((QWidget*)c->jself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ActionEntryExitSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionEntryExit* action = new ActionEntryExit("IQDA1", "");

        try {
            if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitReference) {
                action->setReference(_entryExitReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationReference) {
                action->setOperationReference(_entryExitLockReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            action->setFormula(_entryExitFormulaTextField->text());
            if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitFormula) {
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
    /*public*/ MaleSocket* ActionEntryExitSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ActionEntryExit* action = new ActionEntryExit(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionEntryExitSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ActionEntryExit*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object must be an TriggerEntryExit but is a: ")+object->bself()->metaObject()->className());
        }
        ActionEntryExit* action = (ActionEntryExit*)object->bself();
        if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitDirect) {
            DestinationPoints* entryExit = (DestinationPoints*)entryExitBeanPanel->getNamedBean()->self();
            if (entryExit != nullptr) {
                NamedBeanHandle<DestinationPoints*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(entryExit->getDisplayName(), entryExit);
                action->setDestinationPoints(handle);
            } else {
                action->removeDestinationPoints();
            }
        } else {
            action->removeDestinationPoints();
        }
        try {
            if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
                action->setReference(_entryExitReferenceTextField->text());
            } else if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
                action->setLocalVariable(_entryExitLocalVariableTextField->text());
            } else if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
                action->setFormula(_entryExitFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneEntryExit has unknown selection");
            }

            if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationDirect) {
                action->setOperationAddressing(NamedBeanAddressing::Direct);
                action->setOperationDirect((ActionEntryExit::Operation::TYPE)_stateComboBox->getSelectedIndex());
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationReference) {
                action->setOperationAddressing(NamedBeanAddressing::Reference);
                action->setOperationReference(_entryExitLockReferenceTextField->text());
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationLocalVariable) {
                action->setOperationAddressing(NamedBeanAddressing::LocalVariable);
                action->setOperationLocalVariable(_entryExitLockLocalVariableTextField->text());
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationFormula) {
                action->setOperationAddressing(NamedBeanAddressing::Formula);
                action->setOperationFormula(_entryExitLockFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneEntryExit has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ActionEntryExitSwing::toString() {
        return tr("ActionEntryExit_Short");
    }

    //@Override
    /*public*/ void ActionEntryExitSwing::dispose() {
        if (entryExitBeanPanel != nullptr) {
            entryExitBeanPanel->dispose();
        }
    }

