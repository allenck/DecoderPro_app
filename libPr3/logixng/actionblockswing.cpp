#include "actionblockswing.h"
#include "actionblock.h"
#include "instancemanager.h"
#include "jtabbedpane.h"
#include "namedbeanaddressing.h"
#include "abstractblockmanager.h"
#include "beanselectpanel.h"
#include "jtextfield.h"
#include "swingconfiguratorinterface.h"
#include "parserexception.h"
#include "namedbeanhandlemanager.h"
#include "defaultdigitalactionmanager.h"


ActionBlockSwing::ActionBlockSwing(QObject *parent) : AbstractDigitalActionSwing(parent)
{
setObjectName("ActionBlockSwing");
}
/**
 * Configures an ActionBlock object with a Swing JPanel.
 *
 * @author Daniel Bergqvist  Copyright 2021
 * @author Dave Sand         Copyright 2021
 */
///*public*/  class ActionBlockSwing extends AbstractDigitalActionSwing {

    //@Override
    /*protected*/ void ActionBlockSwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ActionBlock* action = nullptr;
        if(object)
         action =(ActionBlock*)object->bself();

        panel = new JPanel(new FlowLayout());
        // Left section
        _tabbedPaneBlock = new JTabbedPane();
        _panelBlockDirect = new JPanel(new FlowLayout);
        _panelBlockReference = new JPanel(new FlowLayout);
        _panelBlockLocalVariable = new JPanel(new FlowLayout);
        _panelBlockFormula = new JPanel(new FlowLayout);

        _tabbedPaneBlock->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelBlockDirect);
        _tabbedPaneBlock->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelBlockReference);
        _tabbedPaneBlock->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelBlockLocalVariable);
        _tabbedPaneBlock->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelBlockFormula);

        _blockBeanPanel = new BeanSelectPanel((AbstractBlockManager*)InstanceManager::getDefault("BlockManager"), nullptr);
        _panelBlockDirect->layout()->addWidget(_blockBeanPanel);

//         _blockBeanPanel->getBeanCombo().addActionListener((java.awt.event.ActionEvent e) -> {
//             log.info("sample bean selection changed: {}", e);
//         });

        _blockReferenceTextField = new JTextField();
        _blockReferenceTextField->setColumns(30);
        _panelBlockReference->layout()->addWidget(_blockReferenceTextField);

        _blockLocalVariableTextField = new JTextField();
        _blockLocalVariableTextField->setColumns(30);
        _panelBlockLocalVariable->layout()->addWidget(_blockLocalVariableTextField);

        _blockFormulaTextField = new JTextField();
        _blockFormulaTextField->setColumns(30);
        _panelBlockFormula->layout()->addWidget(_blockFormulaTextField);

        // Center section
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
        for (ActionBlock::DirectOperation::TYPE e : ActionBlock::DirectOperation::values()) {
            _stateComboBox->addItem(ActionBlock::DirectOperation::toString(e), e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_stateComboBox);
        //_stateComboBox.addActionListener((java.awt.event.ActionEvent e) -> {
        connect(_stateComboBox, &JComboBox::currentIndexChanged, [=]{
            setDataPanelState();
        });
        _panelOperationDirect->layout()->addWidget(_stateComboBox);

        _blockOperReferenceTextField = new JTextField();
        _blockOperReferenceTextField->setColumns(30);
        _panelOperationReference->layout()->addWidget(_blockOperReferenceTextField);

        _blockOperLocalVariableTextField = new JTextField();
        _blockOperLocalVariableTextField->setColumns(30);
        _panelOperationLocalVariable->layout()->addWidget(_blockOperLocalVariableTextField);

        _blockOperFormulaTextField = new JTextField();
        _blockOperFormulaTextField->setColumns(30);
        _panelOperationFormula->layout()->addWidget(_blockOperFormulaTextField);

        // Right section
        _tabbedPaneData = new JTabbedPane();
        _panelDataDirect = new JPanel(new FlowLayout);
        _panelDataReference = new JPanel(new FlowLayout);
        _panelDataLocalVariable = new JPanel(new FlowLayout);
        _panelDataFormula = new JPanel(new FlowLayout);

        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelDataDirect);
        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelDataReference);
        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelDataLocalVariable);
        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelDataFormula);

        _blockDataDirectTextField = new JTextField();
        _blockDataDirectTextField->setColumns(30);
        _panelDataDirect->layout()->addWidget(_blockDataDirectTextField);

        _blockDataReferenceTextField = new JTextField();
        _blockDataReferenceTextField->setColumns(30);
        _panelDataReference->layout()->addWidget(_blockDataReferenceTextField);

        _blockDataLocalVariableTextField = new JTextField();
        _blockDataLocalVariableTextField->setColumns(30);
        _panelDataLocalVariable->layout()->addWidget(_blockDataLocalVariableTextField);

        _blockDataFormulaTextField = new JTextField();
        _blockDataFormulaTextField->setColumns(30);
        _panelDataFormula->layout()->addWidget(_blockDataFormulaTextField);

        setDataPanelState();

        if (action != nullptr) {
            switch (action->getAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneBlock->setSelectedComponent(_panelBlockDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneBlock->setSelectedComponent(_panelBlockReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneBlock->setSelectedComponent(_panelBlockLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneBlock->setSelectedComponent(_panelBlockFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            if (action->getBlock() != nullptr) {
                _blockBeanPanel->setDefaultNamedBean(action->getBlock()->getBean());
            }
            _blockReferenceTextField->setText(action->getReference());
            _blockLocalVariableTextField->setText(action->getLocalVariable());
            _blockFormulaTextField->setText(action->getFormula());

            switch (action->getOperationAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneOperation->setSelectedComponent(_panelOperationDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneOperation->setSelectedComponent(_panelOperationReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneOperation->setSelectedComponent(_panelOperationLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneOperation->setSelectedComponent(_panelOperationFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " +  NamedBeanAddressing::toString(action->getOperationAddressing()));
            }
            _stateComboBox->setSelectedItem(action->getOperationDirect());
            _blockOperReferenceTextField->setText(action->getOperationReference());
            _blockOperLocalVariableTextField->setText(action->getOperationLocalVariable());
            _blockOperFormulaTextField->setText(action->getOperationFormula());

            switch (action->getDataAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneData->setSelectedComponent(_panelDataDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneData->setSelectedComponent(_panelDataReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneData->setSelectedComponent(_panelDataLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneData->setSelectedComponent(_panelDataFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getDataAddressing()));
            }
            _blockDataReferenceTextField->setText(action->getDataReference());
            _blockDataLocalVariableTextField->setText(action->getDataLocalVariable());
            _blockDataFormulaTextField->setText(action->getDataFormula());

            _blockDataDirectTextField->setText(action->getBlockValue());
            setDataPanelState();
        }

        QList<JComponent*> components = QList<JComponent*>{
            _tabbedPaneBlock,
            _tabbedPaneOperation,
            _tabbedPaneData};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Set block {1} to {2}"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget(c->jself());
    }

    /*private*/ void ActionBlockSwing::setDataPanelState() {
        bool newState = _stateComboBox->getSelectedItem().toInt() == ActionBlock::DirectOperation::SetValue;
        _tabbedPaneData->QWidget::setEnabled(newState);
        _blockDataDirectTextField->setEnabled(newState);
        _blockDataReferenceTextField->setEnabled(newState);
        _blockDataLocalVariableTextField->setEnabled(newState);
        _blockDataFormulaTextField->setEnabled(newState);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ActionBlockSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        validateBlockSection(errorMessages);
        validateOperationSection(errorMessages);
        validateDataSection(errorMessages);
        return errorMessages->isEmpty();
    }

    /*private*/ void ActionBlockSwing::validateBlockSection(QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionBlock* action = new ActionBlock("IQDA1", "");

        try {
            if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockReference) {
                action->setReference(_blockReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return;
        }

        try {
            action->setFormula(_blockFormulaTextField->text());
            if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
            } else {
                throw new IllegalArgumentException("_tabbedPane has unknown selection");
            }
        } catch (ParserException* e) {
            errorMessages->append("Cannot parse formula: " + e->getMessage());
        }

        if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockDirect) {
            if (_blockBeanPanel->getNamedBean() == nullptr) {
                errorMessages->append(tr("A block was not selected"));
            }
        }
    }

    /*private*/ void ActionBlockSwing::validateOperationSection(QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionBlock* action = new ActionBlock("IQDA2", "");

        try {
            if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationReference) {
                action->setOperationReference(_blockOperReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return;
        }

        try {
            action->setOperationFormula(_blockOperFormulaTextField->text());
            if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationDirect) {
                action->setOperationAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationReference) {
                action->setOperationAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationLocalVariable) {
                action->setOperationAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationFormula) {
                action->setOperationAddressing(NamedBeanAddressing::Formula);
            } else {
                throw new IllegalArgumentException("_tabbedPane has unknown selection");
            }
        } catch (ParserException* e) {
            errorMessages->append("Cannot parse formula: " + e->getMessage());
        }
    }

    /*private*/ void ActionBlockSwing::validateDataSection(QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionBlock* action = new ActionBlock("IQDA3", "");

        try {
            if (_tabbedPaneData->getSelectedComponent() == _panelDataReference) {
                action->setDataReference(_blockDataReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return;
        }

        try {
            action->setDataFormula(_blockDataFormulaTextField->text());
            if (_tabbedPaneData->getSelectedComponent() == _panelDataDirect) {
                action->setDataAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataReference) {
                action->setDataAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataLocalVariable) {
                action->setDataAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataFormula) {
                action->setDataAddressing(NamedBeanAddressing::Formula);
            } else {
                throw new IllegalArgumentException("_tabbedPane has unknown selection");
            }
        } catch (ParserException* e) {
            errorMessages->append("Cannot parse formula: " + e->getMessage());
        }

        if (_tabbedPaneData->getSelectedComponent() == _panelDataDirect) {
            ActionBlock::DirectOperation::TYPE oper = (ActionBlock::DirectOperation::TYPE)_stateComboBox->getItemAt(_stateComboBox->getSelectedIndex()).toInt();
            if (oper ==ActionBlock:: DirectOperation::SetValue) {
                if (_blockDataDirectTextField->text().isEmpty()) {
                    errorMessages->append(tr("A block value was not entered"));
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* ActionBlockSwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        ActionBlock* action = new ActionBlock(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionBlockSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ActionBlock*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ActionBlock but is a: ").arg(+object->bself()->metaObject()->className()));
        }
        ActionBlock* action = (ActionBlock*) object->bself();

        if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockDirect) {
            //Block* block = (Block*)_blockBeanPanel->getNamedBean()->self();
            Block* block = nullptr;
            NamedBean* nb = _blockBeanPanel->getNamedBean();
            if (nb != nullptr) {
                NamedBeanHandle<Block*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(block->getDisplayName(), block);
                action->setBlock(handle);
            } else {
                action->removeBlock();
            }
        } else {
            action->removeBlock();
        }

        try {
            // Left section
            if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
                action->setReference(_blockReferenceTextField->text());
            } else if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
                action->setLocalVariable(_blockLocalVariableTextField->text());
            } else if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
                action->setFormula(_blockFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneBlock has unknown selection");
            }

            // Center section
            if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationDirect) {
                action->setOperationAddressing(NamedBeanAddressing::Direct);
                action->setOperationDirect((ActionBlock::DirectOperation::TYPE)_stateComboBox->getItemAt(_stateComboBox->getSelectedIndex()).toInt());
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationReference) {
                action->setOperationAddressing(NamedBeanAddressing::Reference);
                action->setOperationReference(_blockOperReferenceTextField->text());
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationLocalVariable) {
                action->setOperationAddressing(NamedBeanAddressing::LocalVariable);
                action->setOperationLocalVariable(_blockOperLocalVariableTextField->text());
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationFormula) {
                action->setOperationAddressing(NamedBeanAddressing::Formula);
                action->setOperationFormula(_blockOperFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneBlock has unknown selection");
            }

            // Right section
            if (_tabbedPaneData->getSelectedComponent() == _panelDataDirect) {
                action->setDataAddressing(NamedBeanAddressing::Direct);
                // Handle optional data field
                if (action->getOperationDirect() == ActionBlock::DirectOperation::SetValue) {
                    action->setBlockValue(_blockDataDirectTextField->text());
                }
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataReference) {
                action->setDataAddressing(NamedBeanAddressing::Reference);
                action->setDataReference(_blockDataReferenceTextField->text());
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataLocalVariable) {
                action->setDataAddressing(NamedBeanAddressing::LocalVariable);
                action->setDataLocalVariable(_blockDataLocalVariableTextField->text());
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataFormula) {
                action->setDataAddressing(NamedBeanAddressing::Formula);
                action->setDataFormula(_blockDataFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneBlock has unknown selection");
            }

        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ActionBlockSwing::toString() {
        return tr("ActionBlock");
    }

    //@Override
    /*public*/  void ActionBlockSwing::dispose() {
        if (_blockBeanPanel != nullptr) {
            _blockBeanPanel->dispose();
        }
    }
