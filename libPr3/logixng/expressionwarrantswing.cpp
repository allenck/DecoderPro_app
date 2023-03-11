#include "expressionwarrantswing.h"
#include "beanselectpanel.h"
#include "jtabbedpane.h"
#include "jtextfield.h"
#include "logixng/defaultdigitalexpressionmanager.h"
#include "logixng/expressionwarrant.h"
#include "instancemanager.h"
#include "logixng/parserexception.h"
#include "warrant.h"
#include "warrantmanager.h"

ExpressionWarrantSwing::ExpressionWarrantSwing(QObject *parent)
    : AbstractDigitalExpressionSwing{parent}
{

}
/**
 * Configures an ExpressionWarrant object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/ class ExpressionWarrantSwing extends AbstractDigitalExpressionSwing {



    //@Override
    /*protected*/ void ExpressionWarrantSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
    ExpressionWarrant* expression = (ExpressionWarrant*)object->bself();

        panel = new JPanel(new FlowLayout);

        _tabbedPaneWarrant = new JTabbedPane();
        _panelWarrantDirect = new JPanel(new FlowLayout);
        _panelWarrantReference = new JPanel(new FlowLayout);
        _panelWarrantLocalVariable = new JPanel(new FlowLayout);
        _panelWarrantFormula = new JPanel(new FlowLayout);

        _tabbedPaneWarrant->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelWarrantDirect);
        _tabbedPaneWarrant->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelWarrantReference);
        _tabbedPaneWarrant->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelWarrantLocalVariable);
        _tabbedPaneWarrant->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelWarrantFormula);

        warrantBeanPanel = new BeanSelectPanel((WarrantManager*)InstanceManager::getDefault("WarrantManager"), nullptr);
        _panelWarrantDirect->layout()->addWidget(warrantBeanPanel);

        _warrantReferenceTextField = new JTextField();
        _warrantReferenceTextField->setColumns(30);
        _panelWarrantReference->layout()->addWidget(_warrantReferenceTextField);

        _warrantLocalVariableTextField = new JTextField();
        _warrantLocalVariableTextField->setColumns(30);
        _panelWarrantLocalVariable->layout()->addWidget(_warrantLocalVariableTextField);

        _warrantFormulaTextField = new JTextField();
        _warrantFormulaTextField->setColumns(30);
        _panelWarrantFormula->layout()->addWidget(_warrantFormulaTextField);


        _is_IsNot_ComboBox = new JComboBox();
        for (Is_IsNot_Enum::VAL e : Is_IsNot_Enum::values()) {
            _is_IsNot_ComboBox->addItem(Is_IsNot_Enum::toString(e), e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_is_IsNot_ComboBox);


        _tabbedPaneWarrantState = new JTabbedPane();
        _panelWarrantStateDirect = new JPanel(new FlowLayout);
        _panelWarrantStateReference = new JPanel(new FlowLayout);
        _panelWarrantStateLocalVariable = new JPanel(new FlowLayout);
        _panelWarrantStateFormula = new JPanel(new FlowLayout);

        _tabbedPaneWarrantState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelWarrantStateDirect);
        _tabbedPaneWarrantState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelWarrantStateReference);
        _tabbedPaneWarrantState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelWarrantStateLocalVariable);
        _tabbedPaneWarrantState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelWarrantStateFormula);

        _stateComboBox = new JComboBox();
        for (ExpressionWarrant::WarrantState::TYPE e : ExpressionWarrant::WarrantState::values()) {
            _stateComboBox->addItem(ExpressionWarrant::WarrantState::toString(e),e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_stateComboBox);

        _panelWarrantStateDirect->layout()->addWidget(_stateComboBox);

        _warrantStateReferenceTextField = new JTextField();
        _warrantStateReferenceTextField->setColumns(30);
        _panelWarrantStateReference->layout()->addWidget(_warrantStateReferenceTextField);

        _warrantStateLocalVariableTextField = new JTextField();
        _warrantStateLocalVariableTextField->setColumns(30);
        _panelWarrantStateLocalVariable->layout()->addWidget(_warrantStateLocalVariableTextField);

        _warrantStateFormulaTextField = new JTextField();
        _warrantStateFormulaTextField->setColumns(30);
        _panelWarrantStateFormula->layout()->addWidget(_warrantStateFormulaTextField);


        if (expression != nullptr) {
            switch (expression->getAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneWarrant->setSelectedComponent(_panelWarrantDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneWarrant->setSelectedComponent(_panelWarrantReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneWarrant->setSelectedComponent(_panelWarrantLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneWarrant->setSelectedComponent(_panelWarrantFormula); break;
            default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getAddressing()));
            }
            if (expression->getWarrant() != nullptr) {
                warrantBeanPanel->setDefaultNamedBean((NamedBean*)expression->getWarrant()->getBean());
            }
            _warrantReferenceTextField->setText(expression->getReference());
            _warrantLocalVariableTextField->setText(expression->getLocalVariable());
            _warrantFormulaTextField->setText(expression->getFormula());

            _is_IsNot_ComboBox->setSelectedItem(expression->get_Is_IsNot());

            switch (expression->getStateAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneWarrantState->setSelectedComponent(_panelWarrantStateDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneWarrantState->setSelectedComponent(_panelWarrantStateReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneWarrantState->setSelectedComponent(_panelWarrantStateLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneWarrantState->setSelectedComponent(_panelWarrantStateFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getAddressing()));
            }
            _stateComboBox->setSelectedItem(expression->getBeanState());
            _warrantStateReferenceTextField->setText(expression->getStateReference());
            _warrantStateLocalVariableTextField->setText(expression->getStateLocalVariable());
            _warrantStateFormulaTextField->setText(expression->getStateFormula());
        }

        QList<JComponent*> components = QList<JComponent*>{
            _tabbedPaneWarrant,
            _is_IsNot_ComboBox,
            _tabbedPaneWarrantState};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Warrant {0} {1} {2}"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget((QWidget*)c->jself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ExpressionWarrantSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary expression to test formula
        ExpressionWarrant* expression = new ExpressionWarrant("IQDE1", "");

        try {
            if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantReference) {
                expression->setReference(_warrantReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            if (_tabbedPaneWarrantState->getSelectedComponent() == _panelWarrantStateReference) {
                expression->setStateReference(_warrantStateReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            expression->setFormula(_warrantFormulaTextField->text());
            if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantDirect) {
                expression->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantReference) {
                expression->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantLocalVariable) {
                expression->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantFormula) {
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
    /*public*/ QString ExpressionWarrantSwing::getAutoSystemName() {
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->getAutoSystemName();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ MaleSocket* ExpressionWarrantSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ExpressionWarrant* expression = new ExpressionWarrant(systemName, userName);
        updateObject(expression);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionWarrantSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast< ExpressionWarrant*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object must be an ExpressionWarrant but is a: ")+object->bself()->metaObject()->className());
        }
        ExpressionWarrant* expression = (ExpressionWarrant*)object->bself();
        if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantDirect) {
            Warrant* warrant = (Warrant*)warrantBeanPanel->getNamedBean()->self();
            if (warrant != nullptr) {
                NamedBeanHandle<Warrant*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(warrant->getDisplayName(), warrant);
                expression->setWarrant(handle);
            } else {
                expression->removeWarrant();
            }
        } else {
            expression->removeWarrant();
        }
        try {
            if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantDirect) {
                expression->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantReference) {
                expression->setAddressing(NamedBeanAddressing::Reference);
                expression->setReference(_warrantReferenceTextField->text());
            } else if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantLocalVariable) {
                expression->setAddressing(NamedBeanAddressing::LocalVariable);
                expression->setLocalVariable(_warrantLocalVariableTextField->text());
            } else if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantFormula) {
                expression->setAddressing(NamedBeanAddressing::Formula);
                expression->setFormula(_warrantFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneWarrant has unknown selection");
            }

            expression->set_Is_IsNot((Is_IsNot_Enum::VAL)_is_IsNot_ComboBox->currentIndex());

            if (_tabbedPaneWarrantState->getSelectedComponent() == _panelWarrantStateDirect) {
                expression->setStateAddressing(NamedBeanAddressing::Direct);
                expression->setBeanState((ExpressionWarrant::WarrantState::TYPE)_stateComboBox->currentIndex());
            } else if (_tabbedPaneWarrantState->getSelectedComponent() == _panelWarrantStateReference) {
                expression->setStateAddressing(NamedBeanAddressing::Reference);
                expression->setStateReference(_warrantStateReferenceTextField->text());
            } else if (_tabbedPaneWarrantState->getSelectedComponent() == _panelWarrantStateLocalVariable) {
                expression->setStateAddressing(NamedBeanAddressing::LocalVariable);
                expression->setStateLocalVariable(_warrantStateLocalVariableTextField->text());
            } else if (_tabbedPaneWarrantState->getSelectedComponent() == _panelWarrantStateFormula) {
                expression->setStateAddressing(NamedBeanAddressing::Formula);
                expression->setStateFormula(_warrantStateFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneWarrantState has unknown selection");
            }
        } catch (ParseException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ExpressionWarrantSwing::toString() {
        return tr("Warrant");
    }

    //@Override
    /*public*/ void ExpressionWarrantSwing::dispose() {
        if (warrantBeanPanel != nullptr) {
            warrantBeanPanel->dispose();
        }
    }
