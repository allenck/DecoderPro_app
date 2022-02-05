#include "actionpositionableswing.h"
#include "parserexception.h"
#include "actionpositionable.h"
#include "editormanager.h"
#include "instancemanager.h"
#include "vptr.h"
#include "jtextfield.h"
#include "digitalactionmanager.h"
#include "runtimeexception.h"
/**
 * Configures an ActionPositionable object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright (C) 2021
 */
///*public*/  class ActionPositionableSwing extends AbstractDigitalActionSwing {




    //@Override
    /*protected*/ void ActionPositionableSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ActionPositionable* action = (ActionPositionable*)object;

        panel = new JPanel();

        _selectedEditor = action != nullptr ? action->getEditorName() : nullptr;

        _editorComboBox = new JComboBox();
        for (Editor* editor : ((EditorManager*)InstanceManager::getDefault("EditorManager"))->getAll()) {
            ActionPositionableSwing::EditorItem* item = new EditorItem(editor);
            _editorComboBox->addItem(VPtr<ActionPositionableSwing::EditorItem>::asQVariant(item));
            if (editor->getName() == (_selectedEditor)) _editorComboBox->setSelectedItem(VPtr<ActionPositionableSwing::EditorItem>::asQVariant(item));
        }
        connect(_editorComboBox, &JComboBox::currentTextChanged, [=] { updatePositionables();});

        _tabbedPanePositionable = new JTabbedPane();
        _panelPositionableDirect = new JPanel();
        _panelPositionableReference = new JPanel();
        _panelPositionableLocalVariable = new JPanel();
        _panelPositionableFormula = new JPanel();

        _tabbedPanePositionable->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelPositionableDirect);
        _tabbedPanePositionable->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelPositionableReference);
        _tabbedPanePositionable->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelPositionableLocalVariable);
        _tabbedPanePositionable->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelPositionableFormula);

        _positionableComboBox = new JComboBox();
        updatePositionables(nullptr);
        _panelPositionableDirect->layout()->addWidget(_positionableComboBox);

        _positionableReferenceTextField = new JTextField();
        _positionableReferenceTextField->setColumns(30);
        _panelPositionableReference->layout()->addWidget(_positionableReferenceTextField);

        _positionableLocalVariableTextField = new JTextField();
        _positionableLocalVariableTextField->setColumns(30);
        _panelPositionableLocalVariable->layout()->addWidget(_positionableLocalVariableTextField);

        _positionableFormulaTextField = new JTextField();
        _positionableFormulaTextField->setColumns(30);
        _panelPositionableFormula->layout()->addWidget(_positionableFormulaTextField);


        _tabbedPanePositionableState = new JTabbedPane();
        _panelPositionableStateDirect = new JPanel();
        _panelPositionableStateReference = new JPanel();
        _panelPositionableStateLocalVariable = new JPanel();
        _panelPositionableStateFormula = new JPanel();

        _tabbedPanePositionableState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelPositionableStateDirect);
        _tabbedPanePositionableState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelPositionableStateReference);
        _tabbedPanePositionableState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelPositionableStateLocalVariable);
        _tabbedPanePositionableState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelPositionableStateFormula);

        _isControllingComboBox = new JComboBox();
        foreach (QString e, ActionPositionable::Operation::values()) {
            _isControllingComboBox->addItem((e));
        }
//        JComboBoxUtil::setupComboBoxMaxRows(_isControllingComboBox);

        _panelPositionableStateDirect->layout()->addWidget(_isControllingComboBox);

        _positionableStateReferenceTextField = new JTextField();
        _positionableStateReferenceTextField->setColumns(30);
        _panelPositionableStateReference->layout()->addWidget(_positionableStateReferenceTextField);

        _positionableStateLocalVariableTextField = new JTextField();
        _positionableStateLocalVariableTextField->setColumns(30);
        _panelPositionableStateLocalVariable->layout()->addWidget(_positionableStateLocalVariableTextField);

        _positionableStateFormulaTextField = new JTextField();
        _positionableStateFormulaTextField->setColumns(30);
        _panelPositionableStateFormula->layout()->addWidget(_positionableStateFormulaTextField);


        if (action != nullptr) {
            switch (action->getAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPanePositionable->setSelectedComponent(_panelPositionableDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPanePositionable->setSelectedComponent(_panelPositionableReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPanePositionable->setSelectedComponent(_panelPositionableLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPanePositionable->setSelectedComponent(_panelPositionableFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            if (action->getPositionableName() != nullptr) {
                _positionableComboBox->setSelectedItem(action->getPositionableName());
            }
            _positionableReferenceTextField->setText(action->getReference());
            _positionableLocalVariableTextField->setText(action->getLocalVariable());
            _positionableFormulaTextField->setText(action->getFormula());

            switch (action->getStateAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPanePositionableState->setSelectedComponent(_panelPositionableStateDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPanePositionableState->setSelectedComponent(_panelPositionableStateReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPanePositionableState->setSelectedComponent(_panelPositionableStateLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPanePositionableState->setSelectedComponent(_panelPositionableStateFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            _isControllingComboBox->setSelectedItem(action->getOperation());
            _positionableStateReferenceTextField->setText(action->getStateReference());
            _positionableStateLocalVariableTextField->setText(action->getStateLocalVariable());
            _positionableStateFormulaTextField->setText(action->getStateFormula());
        }

        QList<JComponent*> components = {
            _editorComboBox,
            (JComponent*)_tabbedPanePositionable,
            (JComponent*)_tabbedPanePositionableState};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
//                tr("For panel %1, set positionable %2 to %3").arg(components[0]->toString(), components[1]->toString(),components[2]->toString()));
        tr("For panel %1, set positionable %2 to %3"), components);
        for (JComponent* c : componentList) panel->layout()->addWidget(c->jself());
    }

    /*private*/ void ActionPositionableSwing::updatePositionables(JActionEvent* e) {
        _positionableComboBox->clear();
        if (_editorComboBox->getSelectedIndex() == -1) return;

        EditorItem* item = VPtr<EditorItem>::asPtr(_editorComboBox->getItemAt(_editorComboBox->getSelectedIndex()));
        QList<QString> list = QList<QString>();
        for (Positionable* positionable : item->_editor->getContents()) {
            if (positionable->getId() != nullptr) {
                list.append(positionable->getId());
            }
        }
//        Collections.sort(list);
        for (QString s : list) {
            _positionableComboBox->addItem(s);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ActionPositionableSwing::validate(/*@Nonnull*/ QList<QString> errorMessages) {
        // Create a temporary action to test formula
        ActionPositionable* action = new ActionPositionable("IQDA1", nullptr);

        try {
            if (_tabbedPanePositionable->getSelectedComponent() == _panelPositionableReference) {
                action->setReference(_positionableReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages.append(e->getMessage());
            return false;
        }

        try {
            if (_tabbedPanePositionableState->getSelectedComponent() == _panelPositionableStateReference) {
                action->setStateReference(_positionableStateReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages.append(e->getMessage());
            return false;
        }

        try {
            action->setFormula(_positionableFormulaTextField->text());
            if (_tabbedPanePositionable->getSelectedComponent() == _panelPositionableDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPanePositionable->getSelectedComponent() == _panelPositionableReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPanePositionable->getSelectedComponent() == _panelPositionableLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPanePositionable->getSelectedComponent() == _panelPositionableFormula) {
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
    /*public*/  MaleSocket* ActionPositionableSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ActionPositionable* action = new ActionPositionable(systemName, userName);
        updateObject(action);
        return ((DigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionPositionableSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ActionPositionable*>(object->self()))) {
            throw new IllegalArgumentException(QString("object must be an ActionPositionable but is a: ")+object->self()->metaObject()->className());
        }
        ActionPositionable* action = (ActionPositionable*)object;
        if (_editorComboBox->getSelectedIndex() != -1) {
            action->setEditor(VPtr<Editor>::asPtr(_editorComboBox->getItemAt(_editorComboBox->getSelectedIndex()))->getName());
        }
        if (_tabbedPanePositionable->getSelectedComponent() == _panelPositionableDirect) {
            action->setPositionable(_positionableComboBox->getItemAt(_positionableComboBox->getSelectedIndex()).toString());
        }
        try {
            if (_tabbedPanePositionable->getSelectedComponent() == _panelPositionableDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPanePositionable->getSelectedComponent() == _panelPositionableReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
                action->setReference(_positionableReferenceTextField->text());
            } else if (_tabbedPanePositionable->getSelectedComponent() == _panelPositionableLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
                action->setLocalVariable(_positionableLocalVariableTextField->text());
            } else if (_tabbedPanePositionable->getSelectedComponent() == _panelPositionableFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
                action->setFormula(_positionableFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPanePositionable has unknown selection");
            }

            if (_tabbedPanePositionableState->getSelectedComponent() == _panelPositionableStateDirect) {
                action->setStateAddressing(NamedBeanAddressing::Direct);
                action->setOperation(ActionPositionable::Operation::valueOf(_isControllingComboBox->getItemAt(_isControllingComboBox->getSelectedIndex()).toString()));
            } else if (_tabbedPanePositionableState->getSelectedComponent() == _panelPositionableStateReference) {
                action->setStateAddressing(NamedBeanAddressing::Reference);
                action->setStateReference(_positionableStateReferenceTextField->text());
            } else if (_tabbedPanePositionableState->getSelectedComponent() == _panelPositionableStateLocalVariable) {
                action->setStateAddressing(NamedBeanAddressing::LocalVariable);
                action->setStateLocalVariable(_positionableStateLocalVariableTextField->text());
            } else if (_tabbedPanePositionableState->getSelectedComponent() == _panelPositionableStateFormula) {
                action->setStateAddressing(NamedBeanAddressing::Formula);
                action->setStateFormula(_positionableStateFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPanePositionableState has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException(QString("ParserException: ")+e->getMessage()/*, e*/);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ActionPositionableSwing::toString() {
        return tr("Icon/Label on panel");
    }

    //@Override
    /*public*/  void ActionPositionableSwing::dispose() {
        // Do nothing
    }


//    /*private*/ static class EditorItem {

//        /*private*/ final Editor _editor;

//        /*public*/  EditorItem(Editor editor) {
//            this._editor = editor;
//        }

//        //@Override
//        /*public*/  String toString() {
//            return _editor->getName();
//        }
//    }
