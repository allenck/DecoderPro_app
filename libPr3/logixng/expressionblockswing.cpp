#include "expressionblockswing.h"
#include "expressionblock.h"
#include "jtabbedpane.h"
#include "blockmanager.h"
#include "instancemanager.h"
#include "beanselectpanel.h"
#include "jcombobox.h"
#include "jtextfield.h"
#include "logixng/defaultdigitalexpressionmanager.h"
#include "parserexception.h"
#include "block.h"

ExpressionBlockSwing::ExpressionBlockSwing(QObject *parent)
    : AbstractDigitalExpressionSwing{parent}
{

}
/**
 * Configures an ExpressionBlock object with a Swing JPanel.
 *
 * @author Daniel Bergqvist  Copyright 2021
 * @author Dave Sand         Copyright 2021
 */
// /*public*/ class ExpressionBlockSwing extends AbstractDigitalExpressionSwing {


    //@Override
    /*protected*/ void ExpressionBlockSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ExpressionBlock* expression = nullptr;
        if(object) expression = (ExpressionBlock*)object->bself();

        panel = new JPanel(new FlowLayout);

        _tabbedPaneBlock = new JTabbedPane();
        _panelBlockDirect = new JPanel(new FlowLayout);
        _panelBlockReference = new JPanel(new FlowLayout);
        _panelBlockLocalVariable = new JPanel(new FlowLayout);
        _panelBlockFormula = new JPanel(new FlowLayout);

        _tabbedPaneBlock->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelBlockDirect);
        _tabbedPaneBlock->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelBlockReference);
        _tabbedPaneBlock->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelBlockLocalVariable);
        _tabbedPaneBlock->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelBlockFormula);

        _blockBeanPanel = new BeanSelectPanel((BlockManager*)InstanceManager::getDefault("BlockManager"), nullptr);
        _panelBlockDirect->layout()->addWidget(_blockBeanPanel);

        _blockReferenceTextField = new JTextField();
        _blockReferenceTextField->setColumns(30);
        _panelBlockReference->layout()->addWidget(_blockReferenceTextField);

        _blockLocalVariableTextField = new JTextField();
        _blockLocalVariableTextField->setColumns(30);
        _panelBlockLocalVariable->layout()->addWidget(_blockLocalVariableTextField);

        _blockFormulaTextField = new JTextField();
        _blockFormulaTextField->setColumns(30);
        _panelBlockFormula->layout()->addWidget(_blockFormulaTextField);


        _is_IsNot_ComboBox = new JComboBox();
        for (Is_IsNot_Enum::VAL e : Is_IsNot_Enum::values()) {
            _is_IsNot_ComboBox->addItem(Is_IsNot_Enum::toString(e), e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_is_IsNot_ComboBox);


        _tabbedPaneBlockState = new JTabbedPane();
        _panelBlockStateDirect = new JPanel(new FlowLayout);
        _panelBlockStateReference = new JPanel(new FlowLayout);
        _panelBlockStateLocalVariable = new JPanel(new FlowLayout);
        _panelBlockStateFormula = new JPanel(new FlowLayout);

        _tabbedPaneBlockState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelBlockStateDirect);
        _tabbedPaneBlockState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelBlockStateReference);
        _tabbedPaneBlockState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelBlockStateLocalVariable);
        _tabbedPaneBlockState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelBlockStateFormula);

        _stateComboBox = new JComboBox();
        for (ExpressionBlock::BlockState::VAL e : ExpressionBlock::BlockState::values()) {
            _stateComboBox->addItem(ExpressionBlock::BlockState::toString(e), e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_stateComboBox);

        //_stateComboBox.addActionListener((java.awt.event.ActionEvent e) -> {
        connect(_stateComboBox, &JComboBox::currentTextChanged, [=]{
            setDataPanelState();
        });
        _panelBlockStateDirect->layout()->addWidget(_stateComboBox);

        _blockStateReferenceTextField = new JTextField();
        _blockStateReferenceTextField->setColumns(30);
        _panelBlockStateReference->layout()->addWidget(_blockStateReferenceTextField);

        _blockStateLocalVariableTextField = new JTextField();
        _blockStateLocalVariableTextField->setColumns(30);
        _panelBlockStateLocalVariable->layout()->addWidget(_blockStateLocalVariableTextField);

        _blockStateFormulaTextField = new JTextField();
        _blockStateFormulaTextField->setColumns(30);
        _panelBlockStateFormula->layout()->addWidget(_blockStateFormulaTextField);


        _tabbedPaneBlockData = new JTabbedPane();
        _panelBlockDataDirect = new JPanel(new FlowLayout);
        _panelBlockDataReference = new JPanel(new FlowLayout);
        _panelBlockDataLocalVariable = new JPanel(new FlowLayout);
        _panelBlockDataFormula = new JPanel(new FlowLayout);

        _tabbedPaneBlockData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelBlockDataDirect);
        _tabbedPaneBlockData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelBlockDataReference);
        _tabbedPaneBlockData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelBlockDataLocalVariable);
        _tabbedPaneBlockData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelBlockDataFormula);

        _blockDataDirectTextField = new JTextField();
        _blockDataDirectTextField->setColumns(30);
        _panelBlockDataDirect->layout()->addWidget(_blockDataDirectTextField);

        _blockDataReferenceTextField = new JTextField();
        _blockDataReferenceTextField->setColumns(30);
        _panelBlockDataReference->layout()->addWidget(_blockDataReferenceTextField);

        _blockDataLocalVariableTextField = new JTextField();
        _blockDataLocalVariableTextField->setColumns(30);
        _panelBlockDataLocalVariable->layout()->addWidget(_blockDataLocalVariableTextField);

        _blockDataFormulaTextField = new JTextField();
        _blockDataFormulaTextField->setColumns(30);
        _panelBlockDataFormula->layout()->addWidget(_blockDataFormulaTextField);


        setDataPanelState();

        if (expression != nullptr) {
            switch (expression->getAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneBlock->setSelectedComponent(_panelBlockDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneBlock->setSelectedComponent(_panelBlockReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneBlock->setSelectedComponent(_panelBlockLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneBlock->setSelectedComponent(_panelBlockFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getAddressing()));
            }
            if (expression->getBlock() != nullptr) {
                _blockBeanPanel->setDefaultNamedBean(expression->getBlock()->getBean());
            }
            _blockReferenceTextField->setText(expression->getReference());
            _blockLocalVariableTextField->setText(expression->getLocalVariable());
            _blockFormulaTextField->setText(expression->getFormula());

            _is_IsNot_ComboBox->setSelectedItem(expression->get_Is_IsNot());

            switch (expression->getStateAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneBlockState->setSelectedComponent(_panelBlockStateDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneBlockState->setSelectedComponent(_panelBlockStateReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneBlockState->setSelectedComponent(_panelBlockStateLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneBlockState->setSelectedComponent(_panelBlockStateFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getStateAddressing()));
            }
            _stateComboBox->setSelectedItem(expression->getBeanState());
            _blockStateReferenceTextField->setText(expression->getStateReference());
            _blockStateLocalVariableTextField->setText(expression->getStateLocalVariable());
            _blockStateFormulaTextField->setText(expression->getStateFormula());

            switch (expression->getDataAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneBlockData->setSelectedComponent(_panelBlockDataDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneBlockData->setSelectedComponent(_panelBlockDataReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneBlockData->setSelectedComponent(_panelBlockDataLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneBlockData->setSelectedComponent(_panelBlockDataFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getDataAddressing()));
            }
            _blockDataDirectTextField->setText(expression->getBlockValue());
            _blockDataReferenceTextField->setText(expression->getDataReference());
            _blockDataLocalVariableTextField->setText(expression->getDataLocalVariable());
            _blockDataFormulaTextField->setText(expression->getDataFormula());

            setDataPanelState();
        }

        QList<JComponent*> components = QList<JComponent*>{
            _tabbedPaneBlock,
            _is_IsNot_ComboBox,
            _tabbedPaneBlockState,
            _tabbedPaneBlockData};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Block {0} {1} {2} {3}"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget((QWidget*)c->jself());
    }

    /*private*/ void ExpressionBlockSwing::setDataPanelState() {
        bool newState = _stateComboBox->getSelectedItem() == ExpressionBlock::BlockState::ValueMatches;
        _tabbedPaneBlockData->setEnabled(newState);
        _blockDataDirectTextField->setEnabled(newState);
        _blockDataReferenceTextField->setEnabled(newState);
        _blockDataLocalVariableTextField->setEnabled(newState);
        _blockDataFormulaTextField->setEnabled(newState);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ExpressionBlockSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        validateBlockSection(errorMessages);
        validateStateSection(errorMessages);
        validateDataSection(errorMessages);
        return errorMessages->isEmpty();
    }

    /*private*/ void ExpressionBlockSwing::validateBlockSection(QList<QString>* errorMessages) {
        // Create a temporary expression to test formula
    ExpressionBlock* expression = new ExpressionBlock("IQDE1", "");

        try {
            if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockReference) {
                expression->setReference(_blockReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return;
        }

        try {
            expression->setFormula(_blockFormulaTextField->text());
            if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockDirect) {
                expression->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockReference) {
                expression->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockLocalVariable) {
                expression->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockFormula) {
                expression->setAddressing(NamedBeanAddressing::Formula);
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

    /*private*/ void ExpressionBlockSwing::validateStateSection(QList<QString>* errorMessages) {
        // Create a temporary expression to test formula
        ExpressionBlock* expression = new ExpressionBlock("IQDE2", "");

        try {
            if (_tabbedPaneBlockState->getSelectedComponent() == _panelBlockStateReference) {
                expression->setStateReference(_blockStateReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return;
        }

        try {
            expression->setStateFormula(_blockStateFormulaTextField->text());
            if (_tabbedPaneBlockState->getSelectedComponent() == _panelBlockStateDirect) {
                expression->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneBlockState->getSelectedComponent() == _panelBlockStateReference) {
                expression->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneBlockState->getSelectedComponent() == _panelBlockStateLocalVariable) {
                expression->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneBlockState->getSelectedComponent() == _panelBlockStateFormula) {
                expression->setAddressing(NamedBeanAddressing::Formula);
            } else {
                throw new IllegalArgumentException("_tabbedPane has unknown selection");
            }
        } catch (ParserException* e) {
            errorMessages->append("Cannot parse formula: " + e->getMessage());
        }
    }

    /*private*/ void ExpressionBlockSwing::validateDataSection(QList<QString>* errorMessages) {
        // Create a temporary expression to test formula
        ExpressionBlock* expression = new ExpressionBlock("IQDE3", "");

        try {
            if (_tabbedPaneBlockData->getSelectedComponent() == _panelBlockDataReference) {
                expression->setDataReference(_blockDataReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return;
        }

        try {
            expression->setDataFormula(_blockDataFormulaTextField->text());
            if (_tabbedPaneBlockData->getSelectedComponent() == _panelBlockDataDirect) {
                expression->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneBlockData->getSelectedComponent() == _panelBlockDataReference) {
                expression->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneBlockData->getSelectedComponent() == _panelBlockDataLocalVariable) {
                expression->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneBlockData->getSelectedComponent() == _panelBlockDataFormula) {
                expression->setAddressing(NamedBeanAddressing::Formula);
            } else {
                throw new IllegalArgumentException("_tabbedPane has unknown selection");
            }
        } catch (ParserException* e) {
            errorMessages->append("Cannot parse formula: " + e->getMessage());
        }

        if (_tabbedPaneBlockData->getSelectedComponent() == _panelBlockDataDirect) {
            ExpressionBlock::BlockState::VAL state = (ExpressionBlock::BlockState::VAL)_stateComboBox->getItemAt(_stateComboBox->getSelectedIndex()).toInt();
            if (state == ExpressionBlock::BlockState::ValueMatches) {
                if (_blockDataDirectTextField->text().isEmpty()) {
                    errorMessages->append(tr("Block_ErrorValue"));
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ExpressionBlockSwing::getAutoSystemName() {
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->getAutoSystemName();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ MaleSocket* ExpressionBlockSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ExpressionBlock* expression = new ExpressionBlock(systemName, userName);
        updateObject(expression);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionBlockSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast< ExpressionBlock*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ExpressionBlock but is a: ")+object->bself()->metaObject()->className());
        }

        ExpressionBlock* expression = (ExpressionBlock*) object->bself();
        if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockDirect) {
            Block* block = (Block*)_blockBeanPanel->getNamedBean()->self();
            if (block != nullptr) {
                NamedBeanHandle<Block*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(block->getDisplayName(), block);
                expression->setBlock(handle);
            } else {
                expression->removeBlock();
            }
        } else {
            expression->removeBlock();
        }

        try {
            if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockDirect) {
                expression->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockReference) {
                expression->setAddressing(NamedBeanAddressing::Reference);
                expression->setReference(_blockReferenceTextField->text());
            } else if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockLocalVariable) {
                expression->setAddressing(NamedBeanAddressing::LocalVariable);
                expression->setLocalVariable(_blockLocalVariableTextField->text());
            } else if (_tabbedPaneBlock->getSelectedComponent() == _panelBlockFormula) {
                expression->setAddressing(NamedBeanAddressing::Formula);
                expression->setFormula(_blockFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneBlock has unknown selection");
            }

            expression->set_Is_IsNot((Is_IsNot_Enum::VAL)_is_IsNot_ComboBox->getSelectedItem().toInt());

            if (_tabbedPaneBlockState->getSelectedComponent() == _panelBlockStateDirect) {
                expression->setStateAddressing(NamedBeanAddressing::Direct);
                expression->setBeanState((ExpressionBlock::BlockState::VAL)_stateComboBox->getSelectedItem().toInt());
            } else if (_tabbedPaneBlockState->getSelectedComponent() == _panelBlockStateReference) {
                expression->setStateAddressing(NamedBeanAddressing::Reference);
                expression->setStateReference(_blockStateReferenceTextField->text());
            } else if (_tabbedPaneBlockState->getSelectedComponent() == _panelBlockStateLocalVariable) {
                expression->setStateAddressing(NamedBeanAddressing::LocalVariable);
                expression->setStateLocalVariable(_blockStateLocalVariableTextField->text());
            } else if (_tabbedPaneBlockState->getSelectedComponent() == _panelBlockStateFormula) {
                expression->setStateAddressing(NamedBeanAddressing::Formula);
                expression->setStateFormula(_blockStateFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneBlockState has unknown selection");
            }

            if (_tabbedPaneBlockData->getSelectedComponent() == _panelBlockDataDirect) {
                expression->setDataAddressing(NamedBeanAddressing::Direct);
                // Handle optional data field
                if (expression->getBeanState() == ExpressionBlock::BlockState::ValueMatches) {
                    expression->setBlockValue(_blockDataDirectTextField->text());
                }
            } else if (_tabbedPaneBlockData->getSelectedComponent() == _panelBlockDataReference) {
                expression->setDataAddressing(NamedBeanAddressing::Reference);
                expression->setDataReference(_blockDataReferenceTextField->text());
            } else if (_tabbedPaneBlockData->getSelectedComponent() == _panelBlockDataLocalVariable) {
                expression->setDataAddressing(NamedBeanAddressing::LocalVariable);
                expression->setDataLocalVariable(_blockDataLocalVariableTextField->text());
            } else if (_tabbedPaneBlockData->getSelectedComponent() == _panelBlockDataFormula) {
                expression->setDataAddressing(NamedBeanAddressing::Formula);
                expression->setDataFormula(_blockDataFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneBlockData has unknown selection");
            }

        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ExpressionBlockSwing::toString() {
        return tr("Block");
    }

    //@Override
    /*public*/ void ExpressionBlockSwing::dispose() {
        if (_blockBeanPanel != nullptr) {
            _blockBeanPanel->dispose();
        }
    }
