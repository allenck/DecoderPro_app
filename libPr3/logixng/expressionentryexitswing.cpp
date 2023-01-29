#include "expressionentryexitswing.h"
#include "parserexception.h"
#include "expressionentryexit.h"
#include "jtabbedpane.h"
#include "namedbeanaddressing.h"
#include "defaultdigitalexpressionmanager.h"
#include "instancemanager.h"
#include "beanselectpanel.h"
#include "entryexitpairs.h"
#include "jtextfield.h"
#include "is_isnot_enum.h"
#include "jcombobox.h"
#include "swingconfiguratorinterface.h"

/**
 * Configures an ExpressionEntryExit object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class ExpressionEntryExitSwing extends AbstractDigitalExpressionSwing {



//@Override
/*protected*/ void ExpressionEntryExitSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
    ExpressionEntryExit* expression = nullptr;
    if(object) expression = (ExpressionEntryExit*)object->bself();

    panel = new JPanel(new QVBoxLayout);

    _tabbedPaneEntryExit = new JTabbedPane();
    _panelEntryExitDirect = new JPanel(new FlowLayout);
    _panelEntryExitReference = new JPanel(new FlowLayout);
    _panelEntryExitLocalVariable = new JPanel(new FlowLayout);
    _panelEntryExitFormula = new JPanel(new FlowLayout);

    _tabbedPaneEntryExit->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelEntryExitDirect);
    _tabbedPaneEntryExit->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelEntryExitReference);
    _tabbedPaneEntryExit->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelEntryExitLocalVariable);
    _tabbedPaneEntryExit->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelEntryExitFormula);

    destinationPointsBeanPanel = new BeanSelectPanel((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"), nullptr);
    _panelEntryExitDirect->layout()->addWidget(destinationPointsBeanPanel);

    _entryExitReferenceTextField = new JTextField();
    _entryExitReferenceTextField->setColumns(30);
    _panelEntryExitReference->layout()->addWidget(_entryExitReferenceTextField);

    _entryExitLocalVariableTextField = new JTextField();
    _entryExitLocalVariableTextField->setColumns(30);
    _panelEntryExitLocalVariable->layout()->addWidget(_entryExitLocalVariableTextField);

    _entryExitFormulaTextField = new JTextField();
    _entryExitFormulaTextField->setColumns(30);
    _panelEntryExitFormula->layout()->addWidget(_entryExitFormulaTextField);


    _is_IsNot_ComboBox = new JComboBox();
    for (Is_IsNot_Enum::VAL e : Is_IsNot_Enum::values()) {
        _is_IsNot_ComboBox->addItem(Is_IsNot_Enum::toString(e),e);
    }
    //JComboBoxUtil.setupComboBoxMaxRows(_is_IsNot_ComboBox);


    _tabbedPaneEntryExitState = new JTabbedPane();
    _panelEntryExitStateDirect = new JPanel(new FlowLayout);
    _panelEntryExitStateReference = new JPanel(new FlowLayout);
    _panelEntryExitStateLocalVariable = new JPanel(new FlowLayout);
    _panelEntryExitStateFormula = new JPanel(new FlowLayout);

    _tabbedPaneEntryExitState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelEntryExitStateDirect);
    _tabbedPaneEntryExitState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelEntryExitStateReference);
    _tabbedPaneEntryExitState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelEntryExitStateLocalVariable);
    _tabbedPaneEntryExitState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelEntryExitStateFormula);

    _stateComboBox = new JComboBox();
    for (ExpressionEntryExit::EntryExitState::STATE e : ExpressionEntryExit::EntryExitState::values()) {
        _stateComboBox->addItem(ExpressionEntryExit::EntryExitState::toString(e), e);
    }
//    JComboBoxUtil.setupComboBoxMaxRows(_stateComboBox);

    _panelEntryExitStateDirect->layout()->addWidget(_stateComboBox);

    _entryExitStateReferenceTextField = new JTextField();
    _entryExitStateReferenceTextField->setColumns(30);
    _panelEntryExitStateReference->layout()->addWidget(_entryExitStateReferenceTextField);

    _entryExitStateLocalVariableTextField = new JTextField();
    _entryExitStateLocalVariableTextField->setColumns(30);
    _panelEntryExitStateLocalVariable->layout()->addWidget(_entryExitStateLocalVariableTextField);

    _entryExitStateFormulaTextField = new JTextField();
    _entryExitStateFormulaTextField->setColumns(30);
    _panelEntryExitStateFormula->layout()->addWidget(_entryExitStateFormulaTextField);


    if (expression != nullptr) {
        switch (expression->getAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneEntryExit->setSelectedComponent(_panelEntryExitDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneEntryExit->setSelectedComponent(_panelEntryExitReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneEntryExit->setSelectedComponent(_panelEntryExitLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneEntryExit->setSelectedComponent(_panelEntryExitFormula); break;
            default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getAddressing()));
        }
        if (expression->getEntryExit() != nullptr) {
            destinationPointsBeanPanel->setDefaultNamedBean(expression->getEntryExit()->getBean());
        }
        _entryExitReferenceTextField->setText(expression->getReference());
        _entryExitLocalVariableTextField->setText(expression->getLocalVariable());
        _entryExitFormulaTextField->setText(expression->getFormula());

        _is_IsNot_ComboBox->setSelectedItem(expression->get_Is_IsNot());

        switch (expression->getStateAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneEntryExitState->setSelectedComponent(_panelEntryExitStateDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneEntryExitState->setSelectedComponent(_panelEntryExitStateReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneEntryExitState->setSelectedComponent(_panelEntryExitStateLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneEntryExitState->setSelectedComponent(_panelEntryExitStateFormula); break;
            default: throw new IllegalArgumentException(tr("invalid _addressing state: ") + NamedBeanAddressing::toString(expression->getAddressing()));
        }
        _stateComboBox->setSelectedItem(expression->getBeanState());
        _entryExitStateReferenceTextField->setText(expression->getStateReference());
        _entryExitStateLocalVariableTextField->setText(expression->getStateLocalVariable());
        _entryExitStateFormulaTextField->setText(expression->getStateFormula());
    }

    //JComponent[] components = new JComponent[]{
    QList<QWidget*> components = {
        _tabbedPaneEntryExit,
        _is_IsNot_ComboBox,
        _tabbedPaneEntryExitState};

//    QList<QWidget*> componentList = SwingConfiguratorInterface::parseMessage(
//            tr("Entry exit %1 %2 %3"), components);

    for (QWidget* c : /*componentList*/components) panel->layout()->addWidget(c);
}

/** {@inheritDoc} */
//@Override
/*public*/  bool ExpressionEntryExitSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
    // Create a temporary expression to test formula
    ExpressionEntryExit* expression = new ExpressionEntryExit("IQDE1", nullptr);

    try {
        if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitReference) {
            expression->setReference(_entryExitReferenceTextField->text());
        }
    } catch (IllegalArgumentException* e) {
        errorMessages->append(e->getMessage());
        return false;
    }

    try {
        if (_tabbedPaneEntryExitState->getSelectedComponent() == _panelEntryExitStateReference) {
            expression->setStateReference(_entryExitStateReferenceTextField->text());
        }
    } catch (IllegalArgumentException* e) {
        errorMessages->append(e->getMessage());
        return false;
    }

    try {
        expression->setFormula(_entryExitFormulaTextField->text());
        if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitDirect) {
            expression->setAddressing(NamedBeanAddressing::Direct);
        } else if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitReference) {
            expression->setAddressing(NamedBeanAddressing::Reference);
        } else if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitLocalVariable) {
            expression->setAddressing(NamedBeanAddressing::LocalVariable);
        } else if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitFormula) {
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
/*public*/  QString ExpressionEntryExitSwing::getAutoSystemName() {
    return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->getAutoSystemName();
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket* ExpressionEntryExitSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
    ExpressionEntryExit* expression = new ExpressionEntryExit(systemName, userName);
    updateObject(expression);
    return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionEntryExitSwing::updateObject(/*@Nonnull*/ Base* object) {
    if (! (qobject_cast< ExpressionEntryExit*>(object->bself()))) {
        throw new IllegalArgumentException(tr("object must be an ExpressionEntryExit but is a: ")+object->bself()->metaObject()->className());
    }
    ExpressionEntryExit* expression = (ExpressionEntryExit*)object->bself();
    if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitDirect) {
        DestinationPoints* entryExit = nullptr;
        NamedBean* nb = destinationPointsBeanPanel->getNamedBean();
        if(nb)
         entryExit = (DestinationPoints*)nb->self();
        if (entryExit != nullptr) {
            NamedBeanHandle<DestinationPoints*>* handle
                    = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                            ->getNamedBeanHandle(entryExit->getDisplayName(), entryExit);
            expression->setDestinationPoints(handle);
        } else {
            expression->removeDestinationPoints();
        }
    } else {
        expression->removeDestinationPoints();
    }
    try {
        if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitDirect) {
            expression->setAddressing(NamedBeanAddressing::Direct);
        } else if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitReference) {
            expression->setAddressing(NamedBeanAddressing::Reference);
            expression->setReference(_entryExitReferenceTextField->text());
        } else if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitLocalVariable) {
            expression->setAddressing(NamedBeanAddressing::LocalVariable);
            expression->setLocalVariable(_entryExitLocalVariableTextField->text());
        } else if (_tabbedPaneEntryExit->getSelectedComponent() == _panelEntryExitFormula) {
            expression->setAddressing(NamedBeanAddressing::Formula);
            expression->setFormula(_entryExitFormulaTextField->text());
        } else {
            throw new IllegalArgumentException("_tabbedPaneEntryExit has unknown selection");
        }

        expression->set_Is_IsNot((Is_IsNot_Enum::VAL)_is_IsNot_ComboBox->currentData().toInt());

        if (_tabbedPaneEntryExitState->getSelectedComponent() == _panelEntryExitStateDirect) {
            expression->setStateAddressing(NamedBeanAddressing::Direct);
            expression->setBeanState((ExpressionEntryExit::EntryExitState::STATE)_stateComboBox->currentData().toInt());
        } else if (_tabbedPaneEntryExitState->getSelectedComponent() == _panelEntryExitStateReference) {
            expression->setStateAddressing(NamedBeanAddressing::Reference);
            expression->setStateReference(_entryExitStateReferenceTextField->text());
        } else if (_tabbedPaneEntryExitState->getSelectedComponent() == _panelEntryExitStateLocalVariable) {
            expression->setStateAddressing(NamedBeanAddressing::LocalVariable);
            expression->setStateLocalVariable(_entryExitStateLocalVariableTextField->text());
        } else if (_tabbedPaneEntryExitState->getSelectedComponent() == _panelEntryExitStateFormula) {
            expression->setStateAddressing(NamedBeanAddressing::Formula);
            expression->setStateFormula(_entryExitStateFormulaTextField->text());
        } else {
            throw new IllegalArgumentException("_tabbedPaneEntryExitState has unknown selection");
        }
    } catch (ParserException* e) {
        throw new RuntimeException("ParserException: "+e->getMessage(), e);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  QString ExpressionEntryExitSwing::toString() {
    return tr("EntryExit");
}

//@Override
/*public*/  void ExpressionEntryExitSwing::dispose() {
    if (destinationPointsBeanPanel != nullptr) {
        destinationPointsBeanPanel->dispose();
    }
}
