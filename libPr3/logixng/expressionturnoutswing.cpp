#include "expressionturnoutswing.h"
#include "abstractturnoutmanager.h"
#include "beanselectpanel.h"
#include "instancemanager.h"
#include "jtextfield.h"
#include "jtabbedpane.h"
#include "expressionturnout.h"
#include "vptr.h"
#include "defaultdigitalexpressionmanager.h"
#include "swingconfiguratorinterface.h"
#include "parserexception.h"


ExpressionTurnoutSwing::ExpressionTurnoutSwing(QObject* parent)
 : AbstractDigitalExpressionSwing(parent)
{

}

/**
 * Configures an ExpressionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class ExpressionTurnoutSwing extends AbstractDigitalExpressionSwing {

/**
 * Configures an ExpressionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class ExpressionTurnoutSwing extends AbstractDigitalExpressionSwing {




    //@Override
    /*protected*/ void ExpressionTurnoutSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ExpressionTurnout* expression = nullptr;
        if(object) expression = (ExpressionTurnout*)object->bself();

        panel = new JPanel(new QVBoxLayout);

        _tabbedPaneTurnout = new JTabbedPane();
        _panelTurnoutDirect = new JPanel();
        _panelTurnoutReference = new JPanel();
        _panelTurnoutLocalVariable = new JPanel();
        _panelTurnoutFormula = new JPanel();

        _tabbedPaneTurnout->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelTurnoutDirect);
        _tabbedPaneTurnout->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelTurnoutReference);
        _tabbedPaneTurnout->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelTurnoutLocalVariable);
        _tabbedPaneTurnout->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelTurnoutFormula);

        turnoutBeanPanel = new BeanSelectPanel((AbstractTurnoutManager*)InstanceManager::getDefault("TurnoutManager"), nullptr);
        _panelTurnoutDirect->layout()->addWidget(turnoutBeanPanel);

        _turnoutReferenceTextField = new JTextField();
        _turnoutReferenceTextField->setColumns(30);
        _panelTurnoutReference->layout()->addWidget(_turnoutReferenceTextField);

        _turnoutLocalVariableTextField = new JTextField();
        _turnoutLocalVariableTextField->setColumns(30);
        _panelTurnoutLocalVariable->layout()->addWidget(_turnoutLocalVariableTextField);

        _turnoutFormulaTextField = new JTextField();
        _turnoutFormulaTextField->setColumns(30);
        _panelTurnoutFormula->layout()->addWidget(_turnoutFormulaTextField);


        _is_IsNot_ComboBox = new JComboBox();
        for (Is_IsNot_Enum::VAL e : Is_IsNot_Enum::values()) {
            _is_IsNot_ComboBox->addItem(Is_IsNot_Enum::toString(e),e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_is_IsNot_ComboBox);


        _tabbedPaneTurnoutState = new JTabbedPane();
        _panelTurnoutStateDirect = new JPanel();
        _panelTurnoutStateReference = new JPanel();
        _panelTurnoutStateLocalVariable = new JPanel();
        _panelTurnoutStateFormula = new JPanel();

        _tabbedPaneTurnoutState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelTurnoutStateDirect);
        _tabbedPaneTurnoutState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelTurnoutStateReference);
        _tabbedPaneTurnoutState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelTurnoutStateLocalVariable);
        _tabbedPaneTurnoutState->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelTurnoutStateFormula);

        _stateComboBox = new JComboBox();
        for (ExpressionTurnout::TurnoutState::VAL e : ExpressionTurnout::TurnoutState::values()) {
            _stateComboBox->addItem(ExpressionTurnout::TurnoutState::toString(e),e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_stateComboBox);

        _panelTurnoutStateDirect->layout()->addWidget(_stateComboBox);

        _turnoutStateReferenceTextField = new JTextField();
        _turnoutStateReferenceTextField->setColumns(30);
        _panelTurnoutStateReference->layout()->addWidget(_turnoutStateReferenceTextField);

        _turnoutStateLocalVariableTextField = new JTextField();
        _turnoutStateLocalVariableTextField->setColumns(30);
        _panelTurnoutStateLocalVariable->layout()->addWidget(_turnoutStateLocalVariableTextField);

        _turnoutStateFormulaTextField = new JTextField();
        _turnoutStateFormulaTextField->setColumns(30);
        _panelTurnoutStateFormula->layout()->addWidget(_turnoutStateFormulaTextField);


        if (expression != nullptr) {
            switch (expression->getAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneTurnout->setSelectedComponent(_panelTurnoutDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneTurnout->setSelectedComponent(_panelTurnoutReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneTurnout->setSelectedComponent(_panelTurnoutLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneTurnout->setSelectedComponent(_panelTurnoutFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getAddressing()));
            }
            if (expression->getTurnout() != nullptr) {
                turnoutBeanPanel->setDefaultNamedBean(expression->getTurnout()->getBean());
            }
            _turnoutReferenceTextField->setText(expression->getReference());
            _turnoutLocalVariableTextField->setText(expression->getLocalVariable());
            _turnoutFormulaTextField->setText(expression->getFormula());

            _is_IsNot_ComboBox->setSelectedItem(expression->get_Is_IsNot());

            switch (expression->getStateAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneTurnoutState->setSelectedComponent(_panelTurnoutStateDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneTurnoutState->setSelectedComponent(_panelTurnoutStateReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneTurnoutState->setSelectedComponent(_panelTurnoutStateLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneTurnoutState->setSelectedComponent(_panelTurnoutStateFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getAddressing()));
            }
            _stateComboBox->setSelectedItem(expression->getBeanState());
            _turnoutStateReferenceTextField->setText(expression->getStateReference());
            _turnoutStateLocalVariableTextField->setText(expression->getStateLocalVariable());
            _turnoutStateFormulaTextField->setText(expression->getStateFormula());
        }

        QList<JComponent*> components = QList<JComponent*>{
            _tabbedPaneTurnout,
            _is_IsNot_ComboBox,
            _tabbedPaneTurnoutState};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Turnout {0} {1} {2}"), components);

        for (JComponent* c : /*componentList*/components) panel->layout()->addWidget((QWidget*)c->jself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ExpressionTurnoutSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary expression to test formula
        ExpressionTurnout* expression = new ExpressionTurnout("IQDE1", nullptr);

        try {
            if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutReference) {
                expression->setReference(_turnoutReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            if (_tabbedPaneTurnoutState->getSelectedComponent() == _panelTurnoutStateReference) {
                expression->setStateReference(_turnoutStateReferenceTextField->text());
            }
        } catch (IllegalArgumentException e) {
            errorMessages->append(e.getMessage());
            return false;
        }

        try {
            expression->setFormula(_turnoutFormulaTextField->text());
            if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutDirect) {
                expression->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutReference) {
                expression->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutLocalVariable) {
                expression->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutFormula) {
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
    /*public*/  MaleSocket* ExpressionTurnoutSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ExpressionTurnout* expression = new ExpressionTurnout(systemName, userName);
        updateObject(expression);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionTurnoutSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ExpressionTurnout*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object must be an ExpressionTurnout but is a: ")+object->bself()->metaObject()->className());
        }
        ExpressionTurnout* expression = (ExpressionTurnout*)object->bself();
        if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutDirect) {
         Turnout* turnout = nullptr;
         NamedBean* nb = turnoutBeanPanel->getNamedBean();
         if(nb)
            turnout = (Turnout*)nb->self();
         if (turnout != nullptr) {
                NamedBeanHandle<Turnout*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(turnout->getDisplayName(), turnout);
                expression->setTurnout(handle);
            } else {
                expression->removeTurnout();
            }
        } else {
            expression->removeTurnout();
        }
        try {
            if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutDirect) {
                expression->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutReference) {
                expression->setAddressing(NamedBeanAddressing::Reference);
                expression->setReference(_turnoutReferenceTextField->text());
            } else if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutLocalVariable) {
                expression->setAddressing(NamedBeanAddressing::LocalVariable);
                expression->setLocalVariable(_turnoutLocalVariableTextField->text());
            } else if (_tabbedPaneTurnout->getSelectedComponent() == _panelTurnoutFormula) {
                expression->setAddressing(NamedBeanAddressing::Formula);
                expression->setFormula(_turnoutFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneTurnout has unknown selection");
            }

            expression->set_Is_IsNot((Is_IsNot_Enum::VAL)_is_IsNot_ComboBox->getSelectedItem().toInt());

            if (_tabbedPaneTurnoutState->getSelectedComponent() == _panelTurnoutStateDirect) {
                expression->setStateAddressing(NamedBeanAddressing::Direct);
                expression->setBeanState((ExpressionTurnout::TurnoutState::VAL)_stateComboBox->getSelectedItem().toInt());
            } else if (_tabbedPaneTurnoutState->getSelectedComponent() == _panelTurnoutStateReference) {
                expression->setStateAddressing(NamedBeanAddressing::Reference);
                expression->setStateReference(_turnoutStateReferenceTextField->text());
            } else if (_tabbedPaneTurnoutState->getSelectedComponent() == _panelTurnoutStateLocalVariable) {
                expression->setStateAddressing(NamedBeanAddressing::LocalVariable);
                expression->setStateLocalVariable(_turnoutStateLocalVariableTextField->text());
            } else if (_tabbedPaneTurnoutState->getSelectedComponent() == _panelTurnoutStateFormula) {
                expression->setStateAddressing(NamedBeanAddressing::Formula);
                expression->setStateFormula(_turnoutStateFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneTurnoutState has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ExpressionTurnoutSwing::toString() {
        return tr("Turnout");
    }

    //@Override
    /*public*/  void ExpressionTurnoutSwing::dispose() {
        if (turnoutBeanPanel != nullptr) {
            turnoutBeanPanel->dispose();
        }
    }

