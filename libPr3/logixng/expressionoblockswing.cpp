#include "expressionoblockswing.h"
#include "beanselectpanel.h"
#include "instancemanager.h"
#include "jtabbedpane.h"
#include "jtextfield.h"
#include "logixng/defaultdigitalexpressionmanager.h"
#include "logixng/expressionoblock.h"
#include "logixng/parserexception.h"
#include "namedbeanaddressing.h"
#include "oblockmanager.h"
#include "oblock.h"

ExpressionOBlockSwing::ExpressionOBlockSwing(QObject *parent)
    : AbstractDigitalExpressionSwing{parent}
{

}
/**
 * Configures an ExpressionOBlock object with a Swing JPanel* .
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/ class ExpressionOBlockSwing extends AbstractDigitalExpressionSwing {



    //@Override
    /*protected*/ void ExpressionOBlockSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel*  buttonPanel) {
        ExpressionOBlock* expression = (ExpressionOBlock*)object->bself();

        panel = new JPanel(new FlowLayout);

        _tabbedPaneOBlock = new JTabbedPane();
        _panelOBlockDirect = new JPanel(new FlowLayout);
        _panelOBlockReference = new JPanel(new FlowLayout);
        _panelOBlockLocalVariable = new JPanel(new FlowLayout);
        _panelOBlockFormula = new JPanel(new FlowLayout);

        _tabbedPaneOBlock->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelOBlockDirect);
        _tabbedPaneOBlock->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelOBlockReference);
        _tabbedPaneOBlock->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelOBlockLocalVariable);
        _tabbedPaneOBlock->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelOBlockFormula);

        oblockBeanPanel = new BeanSelectPanel((AbstractManager*)InstanceManager::getDefault("OBlockManager"), nullptr);
        _panelOBlockDirect->layout()->addWidget(oblockBeanPanel);

        _oblockReferenceTextField = new JTextField();
        _oblockReferenceTextField->setColumns(30);
        _panelOBlockReference->layout()->addWidget(_oblockReferenceTextField);

        _oblockLocalVariableTextField = new JTextField();
        _oblockLocalVariableTextField->setColumns(30);
        _panelOBlockLocalVariable->layout()->addWidget(_oblockLocalVariableTextField);

        _oblockFormulaTextField = new JTextField();
        _oblockFormulaTextField->setColumns(30);
        _panelOBlockFormula->layout()->addWidget(_oblockFormulaTextField);


        _is_IsNot_ComboBox = new JComboBox();
        for (Is_IsNot_Enum::VAL e : Is_IsNot_Enum::values()) {
            _is_IsNot_ComboBox->addItem(Is_IsNot_Enum::toString(e), e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_is_IsNot_ComboBox);


        _tabbedPaneOBlockState = new JTabbedPane();
        _panelOBlockStateDirect = new JPanel(new FlowLayout);
        _panelOBlockStateReference = new JPanel(new FlowLayout);
        _panelOBlockStateLocalVariable = new JPanel(new FlowLayout);
        _panelOBlockStateFormula = new JPanel(new FlowLayout);

        _tabbedPaneOBlockState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelOBlockStateDirect);
        _tabbedPaneOBlockState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelOBlockStateReference);
        _tabbedPaneOBlockState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelOBlockStateLocalVariable);
        _tabbedPaneOBlockState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelOBlockStateFormula);

        _stateComboBox = new JComboBox();
        for (OBlock::OBlockStatus::STATES e : OBlock::OBlockStatus::values()) {
            _stateComboBox->addItem(OBlock::OBlockStatus::toString(e), e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_stateComboBox);

        _panelOBlockStateDirect->layout()->addWidget(_stateComboBox);

        _oblockStateReferenceTextField = new JTextField();
        _oblockStateReferenceTextField->setColumns(30);
        _panelOBlockStateReference->layout()->addWidget(_oblockStateReferenceTextField);

        _oblockStateLocalVariableTextField = new JTextField();
        _oblockStateLocalVariableTextField->setColumns(30);
        _panelOBlockStateLocalVariable->layout()->addWidget(_oblockStateLocalVariableTextField);

        _oblockStateFormulaTextField = new JTextField();
        _oblockStateFormulaTextField->setColumns(30);
        _panelOBlockStateFormula->layout()->addWidget(_oblockStateFormulaTextField);


        if (expression != nullptr) {
            switch (expression->getAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneOBlock->setSelectedComponent(_panelOBlockDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneOBlock->setSelectedComponent(_panelOBlockReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneOBlock->setSelectedComponent(_panelOBlockLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneOBlock->setSelectedComponent(_panelOBlockFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " +NamedBeanAddressing::toString( expression->getAddressing()));
            }
            if (expression->getOBlock() != nullptr) {
                oblockBeanPanel->setDefaultNamedBean(expression->getOBlock()->getBean());
            }
            _oblockReferenceTextField->setText(expression->getReference());
            _oblockLocalVariableTextField->setText(expression->getLocalVariable());
            _oblockFormulaTextField->setText(expression->getFormula());

            _is_IsNot_ComboBox->setSelectedItem(expression->get_Is_IsNot());

            switch (expression->getStateAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneOBlockState->setSelectedComponent(_panelOBlockStateDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneOBlockState->setSelectedComponent(_panelOBlockStateReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneOBlockState->setSelectedComponent(_panelOBlockStateLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneOBlockState->setSelectedComponent(_panelOBlockStateFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString( expression->getAddressing()));
            }
            _stateComboBox->setSelectedItem(expression->getBeanState());
            _oblockStateReferenceTextField->setText(expression->getStateReference());
            _oblockStateLocalVariableTextField->setText(expression->getStateLocalVariable());
            _oblockStateFormulaTextField->setText(expression->getStateFormula());
        }

        QList<JComponent*> components = QList<JComponent*>{
            _tabbedPaneOBlock,
            _is_IsNot_ComboBox,
            _tabbedPaneOBlockState};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("OBlock {0} {1} {2}"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget((QWidget*)c->jself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ExpressionOBlockSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary expression to test formula
        ExpressionOBlock* expression = new ExpressionOBlock("IQDE1", "");

        try {
            if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockReference) {
                expression->setReference(_oblockReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            if (_tabbedPaneOBlockState->getSelectedComponent() == _panelOBlockStateReference) {
                expression->setStateReference(_oblockStateReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            expression->setFormula(_oblockFormulaTextField->text());
            if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockDirect) {
                expression->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockReference) {
                expression->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockLocalVariable) {
                expression->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockFormula) {
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
    /*public*/ QString ExpressionOBlockSwing::getAutoSystemName() {
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->getAutoSystemName();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ MaleSocket* ExpressionOBlockSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ExpressionOBlock* expression = new ExpressionOBlock(systemName, userName);
        updateObject(expression);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionOBlockSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ExpressionOBlock*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object must be an ExpressionOBlock but is a: ")+object->bself()->metaObject()->className());
        }
        ExpressionOBlock* expression = (ExpressionOBlock*)object->bself();
        if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockDirect) {
            OBlock* oblock = (OBlock*)oblockBeanPanel->getNamedBean()->self();
            if (oblock != nullptr) {
                NamedBeanHandle<OBlock*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(oblock->getDisplayName(), oblock);
                expression->setOBlock(handle);
            } else {
                expression->removeOBlock();
            }
        } else {
            expression->removeOBlock();
        }
        try {
            if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockDirect) {
                expression->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockReference) {
                expression->setAddressing(NamedBeanAddressing::Reference);
                expression->setReference(_oblockReferenceTextField->text());
            } else if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockLocalVariable) {
                expression->setAddressing(NamedBeanAddressing::LocalVariable);
                expression->setLocalVariable(_oblockLocalVariableTextField->text());
            } else if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockFormula) {
                expression->setAddressing(NamedBeanAddressing::Formula);
                expression->setFormula(_oblockFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneOBlock has unknown selection");
            }

            expression->set_Is_IsNot((Is_IsNot_Enum::VAL)_is_IsNot_ComboBox->getSelectedItem().toInt());

            if (_tabbedPaneOBlockState->getSelectedComponent() == _panelOBlockStateDirect) {
                expression->setStateAddressing(NamedBeanAddressing::Direct);
                expression->setBeanState((OBlock::OBlockStatus::STATES)_stateComboBox->getSelectedItem().toInt());
            } else if (_tabbedPaneOBlockState->getSelectedComponent() == _panelOBlockStateReference) {
                expression->setStateAddressing(NamedBeanAddressing::Reference);
                expression->setStateReference(_oblockStateReferenceTextField->text());
            } else if (_tabbedPaneOBlockState->getSelectedComponent() == _panelOBlockStateLocalVariable) {
                expression->setStateAddressing(NamedBeanAddressing::LocalVariable);
                expression->setStateLocalVariable(_oblockStateLocalVariableTextField->text());
            } else if (_tabbedPaneOBlockState->getSelectedComponent() == _panelOBlockStateFormula) {
                expression->setStateAddressing(NamedBeanAddressing::Formula);
                expression->setStateFormula(_oblockStateFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneOBlockState has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ExpressionOBlockSwing::toString() {
        return tr("OBlock");
    }

    //@Override
    /*public*/ void ExpressionOBlockSwing::dispose() {
        if (oblockBeanPanel != nullptr) {
            oblockBeanPanel->dispose();
        }
    }
