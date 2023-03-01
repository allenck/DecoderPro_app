#include "expressionconditionalswing.h"
#include "beanselectpanel.h"
#include "defaultconditionalmanager.h"
#include "jtabbedpane.h"
#include "jtextfield.h"
#include "logixng/defaultdigitalexpressionmanager.h"
#include "logixng/expressionconditional.h"
#include "instancemanager.h"
#include "logixng/parserexception.h"

ExpressionConditionalSwing::ExpressionConditionalSwing(QObject *parent)
    : AbstractDigitalExpressionSwing{parent}
{

}

/**
 * Configures an ExpressionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class ExpressionConditionalSwing extends AbstractDigitalExpressionSwing {



    //@Override
    /*protected*/ void ExpressionConditionalSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ExpressionConditional* expression = nullptr;
        if(object) expression =(ExpressionConditional*)object->bself();

        panel = new JPanel(new FlowLayout);

        _tabbedPaneConditional = new JTabbedPane();
        _panelConditionalDirect = new JPanel(new FlowLayout);
        _panelConditionalReference = new JPanel(new FlowLayout);
        _panelConditionalLocalVariable = new JPanel(new FlowLayout);
        _panelConditionalFormula = new JPanel(new FlowLayout);

        _tabbedPaneConditional->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelConditionalDirect);
        _tabbedPaneConditional->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelConditionalReference);
        _tabbedPaneConditional->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelConditionalLocalVariable);
        _tabbedPaneConditional->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelConditionalFormula);

        _conditionalBeanPanel = new BeanSelectPanel((DefaultConditionalManager*)InstanceManager::getDefault("ConditionalManager"), nullptr);
        _panelConditionalDirect->layout()->addWidget(_conditionalBeanPanel);

        _conditionalReferenceTextField = new JTextField();
        _conditionalReferenceTextField->setColumns(30);
        _panelConditionalReference->layout()->addWidget(_conditionalReferenceTextField);

        _conditionalLocalVariableTextField = new JTextField();
        _conditionalLocalVariableTextField->setColumns(30);
        _panelConditionalLocalVariable->layout()->addWidget(_conditionalLocalVariableTextField);

        _conditionalFormulaTextField = new JTextField();
        _conditionalFormulaTextField->setColumns(30);
        _panelConditionalFormula->layout()->addWidget(_conditionalFormulaTextField);


        _is_IsNot_ComboBox = new JComboBox();
        for (Is_IsNot_Enum::VAL e : Is_IsNot_Enum::values()) {
            _is_IsNot_ComboBox->addItem(Is_IsNot_Enum::toString(e),e);
        }
//        JComboBoxUtil.setupComboBoxMaxRows(_is_IsNot_ComboBox);


        _tabbedPaneConditionalState = new JTabbedPane();
        _panelConditionalStateDirect = new JPanel(new FlowLayout);
        _panelConditionalStateReference = new JPanel(new FlowLayout);
        _panelConditionalStateLocalVariable = new JPanel(new FlowLayout);
        _panelConditionalStateFormula = new JPanel(new FlowLayout);

        _tabbedPaneConditionalState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelConditionalStateDirect);
        _tabbedPaneConditionalState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelConditionalStateReference);
        _tabbedPaneConditionalState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelConditionalStateLocalVariable);
        _tabbedPaneConditionalState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelConditionalStateFormula);

        _stateComboBox = new JComboBox();
        for (ExpressionConditional::ConditionalState::VAL e : ExpressionConditional::ConditionalState::values()) {
            _stateComboBox->addItem(ExpressionConditional::ConditionalState::toString(e),e);
        }
//        JComboBoxUtil.setupComboBoxMaxRows(_stateComboBox);

        _panelConditionalStateDirect->layout()->addWidget(_stateComboBox);

        _conditionalStateReferenceTextField = new JTextField();
        _conditionalStateReferenceTextField->setColumns(30);
        _panelConditionalStateReference->layout()->addWidget(_conditionalStateReferenceTextField);

        _conditionalStateLocalVariableTextField = new JTextField();
        _conditionalStateLocalVariableTextField->setColumns(30);
        _panelConditionalStateLocalVariable->layout()->addWidget(_conditionalStateLocalVariableTextField);

        _conditionalStateFormulaTextField = new JTextField();
        _conditionalStateFormulaTextField->setColumns(30);
        _panelConditionalStateFormula->layout()->addWidget(_conditionalStateFormulaTextField);


        if (expression != nullptr) {
            switch (expression->getAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneConditional->setSelectedComponent(_panelConditionalDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneConditional->setSelectedComponent(_panelConditionalReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneConditional->setSelectedComponent(_panelConditionalLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneConditional->setSelectedComponent(_panelConditionalFormula); break;
            default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getAddressing()));
            }
            if (expression->getConditional() != nullptr) {
                _conditionalBeanPanel->setDefaultNamedBean(expression->getConditional()->getBean());
            }
            _conditionalReferenceTextField->setText(expression->getReference());
            _conditionalLocalVariableTextField->setText(expression->getLocalVariable());
            _conditionalFormulaTextField->setText(expression->getFormula());

            _is_IsNot_ComboBox->setSelectedItem(expression->get_Is_IsNot());

            switch (expression->getStateAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneConditionalState->setSelectedComponent(_panelConditionalStateDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneConditionalState->setSelectedComponent(_panelConditionalStateReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneConditionalState->setSelectedComponent(_panelConditionalStateLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneConditionalState->setSelectedComponent(_panelConditionalStateFormula); break;
            default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getAddressing()));
            }
            _stateComboBox->setSelectedItem(expression->getConditionalState());
            _conditionalStateReferenceTextField->setText(expression->getStateReference());
            _conditionalStateLocalVariableTextField->setText(expression->getStateLocalVariable());
            _conditionalStateFormulaTextField->setText(expression->getStateFormula());
        }

        QList<JComponent*> components = QList<JComponent*>{
            _tabbedPaneConditional,
            _is_IsNot_ComboBox,
            _tabbedPaneConditionalState};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Conditional {0} {1} {2}"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget((QWidget*)c->jself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ExpressionConditionalSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary expression to test formula
        ExpressionConditional* expression = new ExpressionConditional("IQDE1", "");

        try {
            if (_tabbedPaneConditional->getSelectedComponent() == _panelConditionalReference) {
                expression->setReference(_conditionalReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            if (_tabbedPaneConditionalState->getSelectedComponent() == _panelConditionalStateReference) {
                expression->setStateReference(_conditionalStateReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            expression->setFormula(_conditionalFormulaTextField->text());
            if (_tabbedPaneConditional->getSelectedComponent() == _panelConditionalDirect) {
                expression->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneConditional->getSelectedComponent() == _panelConditionalReference) {
                expression->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneConditional->getSelectedComponent() == _panelConditionalLocalVariable) {
                expression->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneConditional->getSelectedComponent() == _panelConditionalFormula) {
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
    /*public*/ MaleSocket* ExpressionConditionalSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ExpressionConditional* expression = new ExpressionConditional(systemName, userName);
        updateObject(expression);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionConditionalSwing::updateObject(/*@Nonnull*/ Base* object) {
     if(!object) throw new NullPointerException("null pointer");
        if (! (qobject_cast<ExpressionConditional*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ExpressionConditional but is a: ")+object->bself()->metaObject()->className());
        }
        ExpressionConditional* expression = (ExpressionConditional*)object->bself();
        if (_tabbedPaneConditional->getSelectedComponent() == _panelConditionalDirect) {
            NamedBean* nb = _conditionalBeanPanel->getNamedBean();
            Conditional* conditional = nullptr;
            if(nb) conditional = (Conditional*)nb->self();
            if (conditional != nullptr) {
                NamedBeanHandle<Conditional*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                        ->getNamedBeanHandle(conditional->getDisplayName(), conditional);
                expression->setConditional(handle);
            } else {
                expression->removeConditional();
            }
        } else {
            expression->removeConditional();
        }
        try {
            if (_tabbedPaneConditional->getSelectedComponent() == _panelConditionalDirect) {
                expression->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneConditional->getSelectedComponent() == _panelConditionalReference) {
                expression->setAddressing(NamedBeanAddressing::Reference);
                expression->setReference(_conditionalReferenceTextField->text());
            } else if (_tabbedPaneConditional->getSelectedComponent() == _panelConditionalLocalVariable) {
                expression->setAddressing(NamedBeanAddressing::LocalVariable);
                expression->setLocalVariable(_conditionalLocalVariableTextField->text());
            } else if (_tabbedPaneConditional->getSelectedComponent() == _panelConditionalFormula) {
                expression->setAddressing(NamedBeanAddressing::Formula);
                expression->setFormula(_conditionalFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneConditional has unknown selection");
            }

            expression->set_Is_IsNot(Is_IsNot_Enum::valueOf(_is_IsNot_ComboBox->currentText()));

            if (_tabbedPaneConditionalState->getSelectedComponent() == _panelConditionalStateDirect) {
                expression->setStateAddressing(NamedBeanAddressing::Direct);
                expression->setConditionalState(ExpressionConditional::ConditionalState::valueOf(_stateComboBox->currentText()));
            } else if (_tabbedPaneConditionalState->getSelectedComponent() == _panelConditionalStateReference) {
                expression->setStateAddressing(NamedBeanAddressing::Reference);
                expression->setStateReference(_conditionalStateReferenceTextField->text());
            } else if (_tabbedPaneConditionalState->getSelectedComponent() == _panelConditionalStateLocalVariable) {
                expression->setStateAddressing(NamedBeanAddressing::LocalVariable);
                expression->setStateLocalVariable(_conditionalStateLocalVariableTextField->text());
            } else if (_tabbedPaneConditionalState->getSelectedComponent() == _panelConditionalStateFormula) {
                expression->setStateAddressing(NamedBeanAddressing::Formula);
                expression->setStateFormula(_conditionalStateFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneConditionalState has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ExpressionConditionalSwing::toString() {
        return tr("Conditional");
    }

    //@Override
    /*public*/ void ExpressionConditionalSwing::dispose() {
    }


