#include "actionmemoryswing.h"
#include "actionmemory.h"
#include "instancemanager.h"
#include "jtabbedpane.h"
#include "beanselectpanel.h"
#include "defaultmemorymanager.h"
#include "jtextfield.h"
#include "jlabel.h"
#include "swingconfiguratorinterface.h"
#include "parserexception.h"
#include "defaultdigitalactionmanager.h"
#include "defaultmemory.h"
#include "jcomponent.h"

ActionMemorySwing::ActionMemorySwing(QObject* parent) :AbstractDigitalActionSwing(parent)
{

}
/**
 * Configures an ActionMemory object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class ActionMemorySwing extends AbstractDigitalActionSwing {



    //@Override
    /*protected*/ void ActionMemorySwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ActionMemory* action = nullptr;
        if(object) action = (ActionMemory*)object->bself();

        panel = new JPanel(new FlowLayout);

        _tabbedPaneMemory = new JTabbedPane();
        _panelMemoryDirect = new JPanel(new FlowLayout);
        _panelMemoryReference = new JPanel(new FlowLayout);
        _panelMemoryLocalVariable = new JPanel(new FlowLayout);
        _panelMemoryFormula = new JPanel(new FlowLayout);

        _tabbedPaneMemory->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelMemoryDirect);
        _tabbedPaneMemory->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelMemoryReference);
        _tabbedPaneMemory->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelMemoryLocalVariable);
        _tabbedPaneMemory->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelMemoryFormula);

        _memoryBeanPanel = new BeanSelectPanel((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"), nullptr);
        _panelMemoryDirect->layout()->addWidget(_memoryBeanPanel);

        _memoryReferenceTextField = new JTextField();
        _memoryReferenceTextField->setColumns(30);
        _panelMemoryReference->layout()->addWidget(_memoryReferenceTextField);

        _memoryLocalVariableTextField = new JTextField();
        _memoryLocalVariableTextField->setColumns(30);
        _panelMemoryLocalVariable->layout()->addWidget(_memoryLocalVariableTextField);

        _memoryFormulaTextField = new JTextField();
        _memoryFormulaTextField->setColumns(30);
        _panelMemoryFormula->layout()->addWidget(_memoryFormulaTextField);

        _tabbedPaneMemoryOperation = new JTabbedPane();

        _setToNull = new JPanel(new FlowLayout);
        _setToConstant = new JPanel(new FlowLayout);
        _copyMemory = new JPanel(new FlowLayout);
        _copyTableCell = new JPanel(new FlowLayout);
        _copyVariable = new JPanel(new FlowLayout);
        _calculateFormula = new JPanel(new FlowLayout);

        _tabbedPaneMemoryOperation->addTab(ActionMemory::MemoryOperation::toString(ActionMemory::MemoryOperation::SetToNull), _setToNull);
        _tabbedPaneMemoryOperation->addTab(ActionMemory::MemoryOperation::toString(ActionMemory::MemoryOperation::SetToString), _setToConstant);
        _tabbedPaneMemoryOperation->addTab(ActionMemory::MemoryOperation::toString(ActionMemory::MemoryOperation::CopyMemoryToMemory), _copyMemory);
        _tabbedPaneMemoryOperation->addTab(ActionMemory::MemoryOperation::toString(ActionMemory::MemoryOperation::CopyTableCellToMemory), _copyTableCell);
        _tabbedPaneMemoryOperation->addTab(ActionMemory::MemoryOperation::toString(ActionMemory::MemoryOperation::CopyVariableToMemory), _copyVariable);
        _tabbedPaneMemoryOperation->addTab(ActionMemory::MemoryOperation::toString(ActionMemory::MemoryOperation::CalculateFormula), _calculateFormula);

        _setToNull->layout()->addWidget(new JLabel("Null"));     // No I18N

        _setToConstantTextField = new JTextField(30);
        _setToConstant->layout()->addWidget(_setToConstantTextField);

        _copyMemoryBeanPanel = new BeanSelectPanel((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"), nullptr);
        _copyMemory->layout()->addWidget(_copyMemoryBeanPanel);

        _copyLocalVariableTextField = new JTextField(30);
        _copyVariable->layout()->addWidget(_copyLocalVariableTextField);

        _copyTableCellTextField = new JTextField(30);
        _copyTableCell->layout()->addWidget(_copyTableCellTextField);

        _calculateFormulaTextField = new JTextField(30);
        _calculateFormula->layout()->addWidget(_calculateFormulaTextField);


        if (action != nullptr) {
            switch (action->getAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneMemory->setSelectedComponent(_panelMemoryDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneMemory->setSelectedComponent(_panelMemoryReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneMemory->setSelectedComponent(_panelMemoryLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneMemory->setSelectedComponent(_panelMemoryFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            if (action->getMemory() != nullptr) {
                _memoryBeanPanel->setDefaultNamedBean(action->getMemory()->getBean());
            }
            _memoryReferenceTextField->setText(action->getReference());
            _memoryLocalVariableTextField->setText(action->getLocalVariable());
            _memoryFormulaTextField->setText(action->getFormula());

            if (action->getOtherMemory() != nullptr) {
                _copyMemoryBeanPanel->setDefaultNamedBean(action->getOtherMemory()->getBean());
            }
            switch (action->getMemoryOperation()) {
                case ActionMemory::MemoryOperation::SetToNull: _tabbedPaneMemoryOperation->setSelectedComponent(_setToNull); break;
                case ActionMemory::MemoryOperation::SetToString: _tabbedPaneMemoryOperation->setSelectedComponent(_setToConstant); break;
                case ActionMemory::MemoryOperation::CopyMemoryToMemory: _tabbedPaneMemoryOperation->setSelectedComponent(_copyMemory); break;
                case ActionMemory::MemoryOperation::CopyTableCellToMemory: _tabbedPaneMemoryOperation->setSelectedComponent(_copyTableCell); break;
                case ActionMemory::MemoryOperation::CopyVariableToMemory: _tabbedPaneMemoryOperation->setSelectedComponent(_copyVariable); break;
                case ActionMemory::MemoryOperation::CalculateFormula: _tabbedPaneMemoryOperation->setSelectedComponent(_calculateFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + ActionMemory::MemoryOperation::toString(action->getMemoryOperation()));
            }
            _setToConstantTextField->setText(action->getConstantValue());
            _copyTableCellTextField->setText(ActionMemory::convertTableReference(action->getOtherTableCell(), false));
            _copyLocalVariableTextField->setText(action->getOtherLocalVariable());
            _calculateFormulaTextField->setText(action->getOtherFormula());
        }

        QList<JComponent*> components =  QList<JComponent*>{
            _tabbedPaneMemory,
            _tabbedPaneMemoryOperation
        };

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Set the memory %1 to %2").arg(_tabbedPaneMemory->toString(),_tabbedPaneMemoryOperation->toString() ),components);

        for (JComponent* c : componentList) panel->layout()->addWidget((QWidget*)c);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ActionMemorySwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        validateMemorySection(errorMessages);
        validateDataSection(errorMessages);
        return errorMessages->isEmpty();
    }

    /*private*/ void ActionMemorySwing::validateMemorySection(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionMemory* action = new ActionMemory("IQDA1", "");

        // If using the Direct tab, validate the memory variable selection.
        if (_tabbedPaneMemory->getSelectedComponent() == _panelMemoryDirect) {
            if (_memoryBeanPanel->getNamedBean() == nullptr) {
                errorMessages->append(tr("A memory variable was not selected"));
            }
        }

        // If using the Reference tab, validate the reference content via setReference.
        try {
            if (_tabbedPaneMemory->getSelectedComponent() == _panelMemoryReference) {
                action->setReference(_memoryReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
        }

        // Validate formula parsing via setFormula and tab selections.
        try {
            action->setFormula(_memoryFormulaTextField->text());
            if (_tabbedPaneMemory->getSelectedComponent() == _panelMemoryDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneMemory->getSelectedComponent() == _panelMemoryReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneMemory->getSelectedComponent() == _panelMemoryLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneMemory->getSelectedComponent() == _panelMemoryFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
            } else {
                throw new IllegalArgumentException("_tabbedPane has unknown selection");
            }
        } catch (ParserException* e) {
            errorMessages->append("Cannot parse formula: " + e->getMessage());
        }
    }

    /*public*/  void ActionMemorySwing::validateDataSection(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionMemory* action = new ActionMemory("IQDA2", "");

        // If using the Memory tab, validate the memory variable selection.
        if (_tabbedPaneMemoryOperation->getSelectedComponent() == _copyMemory) {
            if (_copyMemoryBeanPanel->getNamedBean() == nullptr) {
                errorMessages->append(tr("A memory variable was not selected for copy from"));
            }
        }

        // If using the Table tab, validate the table reference content via setOtherTableCell.
        try {
            if (_tabbedPaneMemoryOperation->getSelectedComponent() == _copyTableCell) {
                action->setOtherTableCell(ActionMemory::convertTableReference(_copyTableCellTextField->text(), true));
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return;
        }

        // Validate formula parsing via setFormula and tab selection.
        try {
            action->setOtherFormula(_calculateFormulaTextField->text());
            if (_tabbedPaneMemoryOperation->getSelectedComponent() == _calculateFormula) {
                action->setMemoryOperation(ActionMemory::MemoryOperation::CalculateFormula);
            }
        } catch (ParserException* e) {
            errorMessages->append("Cannot parse formula: " + e->getMessage());
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* ActionMemorySwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
      if(systemName.isEmpty()) throw new NullPointerException("systemname is empty!");
      ActionMemory* action = new ActionMemory(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionMemorySwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ActionMemory*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object must be an ActionMemory but is a: ")+object->bself()->metaObject()->className());
        }
        ActionMemory* action = (ActionMemory*)object->bself();

        Memory* memory = (DefaultMemory*)_memoryBeanPanel->getNamedBean()->self();
        if (memory != nullptr) {
            NamedBeanHandle<Memory*>* handle
                    = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                            ->getNamedBeanHandle(memory->getDisplayName(), memory);
            action->setMemory(handle);
        } else {
            action->removeMemory();
        }

        if (_tabbedPaneMemoryOperation->getSelectedComponent() == _copyMemory) {
            Memory* otherMemory = (DefaultMemory*)_copyMemoryBeanPanel->getNamedBean()->self();
            if (otherMemory != nullptr) {
                NamedBeanHandle<Memory*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(otherMemory->getDisplayName(), otherMemory);
                action->setOtherMemory(handle);
            } else {
                action->removeOtherMemory();
            }
        } else {
            action->removeOtherMemory();
        }

        try {
            if (_tabbedPaneMemory->getSelectedComponent() == _panelMemoryDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneMemory->getSelectedComponent() == _panelMemoryReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
                action->setReference(_memoryReferenceTextField->text());
            } else if (_tabbedPaneMemory->getSelectedComponent() == _panelMemoryLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
                action->setLocalVariable(_memoryLocalVariableTextField->text());
            } else if (_tabbedPaneMemory->getSelectedComponent() == _panelMemoryFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
                action->setFormula(_memoryFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneMemory has unknown selection");
            }

            if (_tabbedPaneMemoryOperation->getSelectedComponent() == _setToNull) {
                action->setMemoryOperation(ActionMemory::MemoryOperation::SetToNull);
            } else if (_tabbedPaneMemoryOperation->getSelectedComponent() == _setToConstant) {
                action->setMemoryOperation(ActionMemory::MemoryOperation::SetToString);
                action->setOtherConstantValue(_setToConstantTextField->text());
            } else if (_tabbedPaneMemoryOperation->getSelectedComponent() == _copyMemory) {
                action->setMemoryOperation(ActionMemory::MemoryOperation::CopyMemoryToMemory);
            } else if (_tabbedPaneMemoryOperation->getSelectedComponent() == _copyTableCell) {
                action->setMemoryOperation(ActionMemory::MemoryOperation::CopyTableCellToMemory);
                action->setOtherTableCell(ActionMemory::convertTableReference(_copyTableCellTextField->text(), true));
            } else if (_tabbedPaneMemoryOperation->getSelectedComponent() == _copyVariable) {
                action->setMemoryOperation(ActionMemory::MemoryOperation::CopyVariableToMemory);
                action->setOtherLocalVariable(_copyLocalVariableTextField->text());
            } else if (_tabbedPaneMemoryOperation->getSelectedComponent() == _calculateFormula) {
                action->setMemoryOperation(ActionMemory::MemoryOperation::CalculateFormula);
                action->setOtherFormula(_calculateFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneMemoryOperation has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ActionMemorySwing::toString() {
        return tr("Memory");
    }

    //@Override
    /*public*/  void ActionMemorySwing::dispose() {
    }

