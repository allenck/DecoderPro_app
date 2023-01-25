#include "actionlocalvariableswing.h"
#include "instancemanager.h"
#include "actionlocalvariable.h"
#include "jtextfield.h"
#include "jtabbedpane.h"
#include "jlabel.h"
#include "defaultdigitalactionmanager.h"
#include "beanselectpanel.h"
#include "parserexception.h"
#include "defaultmemorymanager.h"

ActionLocalVariableSwing::ActionLocalVariableSwing(QObject *parent) : AbstractDigitalActionSwing(parent)
{
 setObjectName("ActionLocalVariableSwing");
}

/**
 * Configures an ActionLocalVariable object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class ActionLocalVariableSwing extends AbstractDigitalActionSwing {




    //@Override
    /*protected*/ void ActionLocalVariableSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ActionLocalVariable* action = nullptr;
        if(object)
         action = (ActionLocalVariable*)object->bself();

        panel = new JPanel(new FlowLayout());

        _localVariableTextField = new JTextField(20);

        _tabbedPaneVariableOperation = new JTabbedPane();

        _setToNull = new JPanel(new FlowLayout());
        _setToConstant = new JPanel(new FlowLayout());
        _copyMemory = new JPanel(new FlowLayout());
        _copyTableCell = new JPanel(new FlowLayout());
        _copyVariable = new JPanel(new FlowLayout());
        _calculateFormula = new JPanel(new FlowLayout());

        _tabbedPaneVariableOperation->addTab(ActionLocalVariable::VariableOperation::toString(ActionLocalVariable::VariableOperation::SetToNull), _setToNull);
        _tabbedPaneVariableOperation->addTab(ActionLocalVariable::VariableOperation::toString(ActionLocalVariable::VariableOperation::SetToString), _setToConstant);
        _tabbedPaneVariableOperation->addTab(ActionLocalVariable::VariableOperation::toString(ActionLocalVariable::VariableOperation::CopyMemoryToVariable), _copyMemory);
        _tabbedPaneVariableOperation->addTab(ActionLocalVariable::VariableOperation::toString(ActionLocalVariable::VariableOperation::CopyTableCellToVariable), _copyTableCell);
        _tabbedPaneVariableOperation->addTab(ActionLocalVariable::VariableOperation::toString(ActionLocalVariable::VariableOperation::CopyVariableToVariable), _copyVariable);
        _tabbedPaneVariableOperation->addTab(ActionLocalVariable::VariableOperation::toString(ActionLocalVariable::VariableOperation::CalculateFormula), _calculateFormula);

        _setToNull->layout()->addWidget(new JLabel("Null"));     // No I18N

        _setToConstantTextField = new JTextField(30);
        _setToConstant->layout()->addWidget(_setToConstantTextField);

        _copyMemoryBeanPanel = new BeanSelectPanel((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"), nullptr);
        _copyMemory->layout()->addWidget(_copyMemoryBeanPanel);

        _copyTableCellTextField = new JTextField(30);
        _copyTableCell->layout()->addWidget(_copyTableCellTextField);

        _copyLocalVariableTextField = new JTextField(30);
        _copyVariable->layout()->addWidget(_copyLocalVariableTextField);

        _calculateFormulaTextField = new JTextField(30);
        _calculateFormula->layout()->addWidget(_calculateFormulaTextField);


        if (action != nullptr) {
            if (action->getLocalVariable() != nullptr) {
                _localVariableTextField->setText(action->getLocalVariable());
            }
            if (action->getMemory() != nullptr) {
                _copyMemoryBeanPanel->setDefaultNamedBean(action->getMemory()->getBean());
            }
            switch (action->getVariableOperation()) {
                case ActionLocalVariable::VariableOperation::SetToNull: _tabbedPaneVariableOperation->setSelectedComponent(_setToNull); break;
                case ActionLocalVariable::VariableOperation::SetToString: _tabbedPaneVariableOperation->setSelectedComponent(_setToConstant); break;
                case ActionLocalVariable::VariableOperation::CopyMemoryToVariable: _tabbedPaneVariableOperation->setSelectedComponent(_copyMemory); break;
                case ActionLocalVariable::VariableOperation::CopyTableCellToVariable: _tabbedPaneVariableOperation->setSelectedComponent(_copyTableCell); break;
                case ActionLocalVariable::VariableOperation::CopyVariableToVariable: _tabbedPaneVariableOperation->setSelectedComponent(_copyVariable); break;
                case ActionLocalVariable::VariableOperation::CalculateFormula: _tabbedPaneVariableOperation->setSelectedComponent(_calculateFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + ActionLocalVariable::VariableOperation::toString(action->getVariableOperation()));
            }
            _setToConstantTextField->setText(action->getConstantValue());
            _copyTableCellTextField->setText(ActionLocalVariable::convertTableReference(action->getOtherTableCell(), false));
            _copyLocalVariableTextField->setText(action->getOtherLocalVariable());
            _calculateFormulaTextField->setText(action->getFormula());
        }

        QList<JComponent*> components = QList<JComponent*>{
            _localVariableTextField,
            _tabbedPaneVariableOperation
        };

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Set the local variable %1 to %2"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget(c->jself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ActionLocalVariableSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        ActionLocalVariable* action = new ActionLocalVariable("IQDA1", "");

         // If using the Memory tab, validate the memory variable selection.
        if (_tabbedPaneVariableOperation->getSelectedComponent() == _copyMemory) {
            if (_copyMemoryBeanPanel->getNamedBean() == nullptr) {
                errorMessages->append(tr("A memory variable was not selected"));
            }
        }

        // If using the Table tab, validate the table reference content via setOtherTableCell.
        try {
            if (_tabbedPaneVariableOperation->getSelectedComponent() == _copyTableCell) {
                action->setOtherTableCell(ActionLocalVariable::convertTableReference(_copyTableCellTextField->text(), true));
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
        }

        return errorMessages->isEmpty();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* ActionLocalVariableSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ActionLocalVariable* action = new ActionLocalVariable(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionLocalVariableSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ActionLocalVariable*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ActionLocalVariable but is a: ")+object->bself()->metaObject()->className());
        }
        ActionLocalVariable* action = (ActionLocalVariable*)object->bself();

        action->setLocalVariable(_localVariableTextField->text());


        if (!_copyMemoryBeanPanel->isEmpty()
                && (_tabbedPaneVariableOperation->getSelectedComponent() == _copyMemory)) {
            Memory* otherMemory = (Memory*)_copyMemoryBeanPanel->getNamedBean()->self();
            if (otherMemory != nullptr) {
                NamedBeanHandle<Memory*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(otherMemory->getDisplayName(), otherMemory);
                action->setMemory(handle);
            }
        }

        try {
            if (_tabbedPaneVariableOperation->getSelectedComponent() == _setToNull) {
                action->setVariableOperation(ActionLocalVariable::VariableOperation::SetToNull);
            } else if (_tabbedPaneVariableOperation->getSelectedComponent() == _setToConstant) {
                action->setVariableOperation(ActionLocalVariable::VariableOperation::SetToString);
                action->setConstantValue(_setToConstantTextField->text());
            } else if (_tabbedPaneVariableOperation->getSelectedComponent() == _copyMemory) {
                action->setVariableOperation(ActionLocalVariable::VariableOperation::CopyMemoryToVariable);
            } else if (_tabbedPaneVariableOperation->getSelectedComponent() == _copyTableCell) {
                action->setVariableOperation(ActionLocalVariable::VariableOperation::CopyTableCellToVariable);
                action->setOtherTableCell(ActionLocalVariable::convertTableReference(_copyTableCellTextField->text(), true));
            } else if (_tabbedPaneVariableOperation->getSelectedComponent() == _copyVariable) {
                action->setVariableOperation(ActionLocalVariable::VariableOperation::CopyVariableToVariable);
                action->setOtherLocalVariable(_copyLocalVariableTextField->text());
            } else if (_tabbedPaneVariableOperation->getSelectedComponent() == _calculateFormula) {
                action->setVariableOperation(ActionLocalVariable::VariableOperation::CalculateFormula);
                action->setFormula(_calculateFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneVariableOperation has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ActionLocalVariableSwing::toString() {
        return tr("ActionLocalVariable");
    }

    //@Override
    /*public*/  void ActionLocalVariableSwing::dispose() {
    }

