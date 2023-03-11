#include "actionwarrantswing.h"
#include "jtabbedpane.h"
#include "jtextfield.h"
#include "logixng/actionwarrant.h"
#include "instancemanager.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/parserexception.h"
#include "warrantmanager.h"
#include "beanselectpanel.h"
#include "warrant.h"

ActionWarrantSwing::ActionWarrantSwing(QObject *parent)
    : AbstractDigitalActionSwing{parent}
{

}
/**
 * Configures an ActionWarrant object with a Swing JPanel.
 *
 * @author Daniel Bergqvist  Copyright 2021
 * @author Dave Sand         Copyright 2021
 */
// /*public*/ class ActionWarrantSwing extends AbstractDigitalActionSwing {



    //@Override
/*protected*/ void ActionWarrantSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel){
    ActionWarrant* action = (ActionWarrant*)object->bself();

        panel = new JPanel(new FlowLayout);

        // Left section
        _tabbedPaneWarrant = new JTabbedPane();
        _panelWarrantDirect = new JPanel(new FlowLayout);
        _panelWarrantReference = new JPanel(new FlowLayout);
        _panelWarrantLocalVariable = new JPanel(new FlowLayout);
        _panelWarrantFormula = new JPanel(new FlowLayout);

        _tabbedPaneWarrant->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelWarrantDirect);
        _tabbedPaneWarrant->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelWarrantReference);
        _tabbedPaneWarrant->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelWarrantLocalVariable);
        _tabbedPaneWarrant->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelWarrantFormula);

        _warrantBeanPanel = new BeanSelectPanel((WarrantManager*)InstanceManager::getDefault("WarrantManager"), nullptr);
        _panelWarrantDirect->layout()->addWidget(_warrantBeanPanel);

        _warrantReferenceTextField = new JTextField();
        _warrantReferenceTextField->setColumns(30);
        _panelWarrantReference->layout()->addWidget(_warrantReferenceTextField);

        _warrantLocalVariableTextField = new JTextField();
        _warrantLocalVariableTextField->setColumns(30);
        _panelWarrantLocalVariable->layout()->addWidget(_warrantLocalVariableTextField);

        _warrantFormulaTextField = new JTextField();
        _warrantFormulaTextField->setColumns(30);
        _panelWarrantFormula->layout()->addWidget(_warrantFormulaTextField);


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
        for (ActionWarrant::DirectOperation::TYPE e : ActionWarrant::DirectOperation::values()) {
            _stateComboBox->addItem(ActionWarrant::DirectOperation::toString(e),e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_stateComboBox);
        connect(_stateComboBox, &JComboBox::currentTextChanged,[=] {
            setDataPanelState();
        });
        _panelOperationDirect->layout()->addWidget(_stateComboBox);

        _warrantOperReferenceTextField = new JTextField();
        _warrantOperReferenceTextField->setColumns(30);
        _panelOperationReference->layout()->addWidget(_warrantOperReferenceTextField);

        _warrantOperLocalVariableTextField = new JTextField();
        _warrantOperLocalVariableTextField->setColumns(30);
        _panelOperationLocalVariable->layout()->addWidget(_warrantOperLocalVariableTextField);

        _warrantOperFormulaTextField = new JTextField();
        _warrantOperFormulaTextField->setColumns(30);
        _panelOperationFormula->layout()->addWidget(_warrantOperFormulaTextField);


        // Right section
        _tabbedPaneData = new JTabbedPane();
        _panelDataDirect = new JPanel(new FlowLayout);
        _panelDataDirect->setLayout(new QVBoxLayout());//_panelDataDirect, BoxLayout.Y_AXIS));
        _panelDataReference = new JPanel(new FlowLayout);
        _panelDataLocalVariable = new JPanel(new FlowLayout);
        _panelDataFormula = new JPanel(new FlowLayout);

        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelDataDirect);
        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelDataReference);
        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelDataLocalVariable);
        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelDataFormula);

        _trainIdNameTextField = new JTextField();
        _trainIdNameTextField->setColumns(30);
        _panelDataDirect->layout()->addWidget(_trainIdNameTextField);

        _controlTrainComboBox = new JComboBox();
        for (ActionWarrant::ControlAutoTrain::TYPE e : ActionWarrant::ControlAutoTrain::values()) {
            _controlTrainComboBox->addItem(ActionWarrant::ControlAutoTrain::toString(e),e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_controlTrainComboBox);
        _panelControlTrainCombo = new JPanel();
        _panelControlTrainCombo->layout()->addWidget(_controlTrainComboBox);
        _panelDataDirect->layout()->addWidget(_panelControlTrainCombo);

        _warrantDataReferenceTextField = new JTextField();
        _warrantDataReferenceTextField->setColumns(30);
        _panelDataReference->layout()->addWidget(_warrantDataReferenceTextField);

        _warrantDataLocalVariableTextField = new JTextField();
        _warrantDataLocalVariableTextField->setColumns(30);
        _panelDataLocalVariable->layout()->addWidget(_warrantDataLocalVariableTextField);

        _warrantDataFormulaTextField = new JTextField();
        _warrantDataFormulaTextField->setColumns(30);
        _panelDataFormula->layout()->addWidget(_warrantDataFormulaTextField);

        setDataPanelState();


        if (action != nullptr) {
            switch (action->getAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneWarrant->setSelectedComponent(_panelWarrantDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneWarrant->setSelectedComponent(_panelWarrantReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneWarrant->setSelectedComponent(_panelWarrantLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneWarrant->setSelectedComponent(_panelWarrantFormula); break;
            default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            if (action->getWarrant() != nullptr) {
                _warrantBeanPanel->setDefaultNamedBean((NamedBean*)action->getWarrant()->getBean());
            }
            _warrantReferenceTextField->setText(action->getReference());
            _warrantLocalVariableTextField->setText(action->getLocalVariable());
            _warrantFormulaTextField->setText(action->getFormula());

            switch (action->getOperationAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneOperation->setSelectedComponent(_panelOperationDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneOperation->setSelectedComponent(_panelOperationReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneOperation->setSelectedComponent(_panelOperationLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneOperation->setSelectedComponent(_panelOperationFormula); break;
            default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            _stateComboBox->setSelectedItem(action->getOperationDirect());
            setDataPanelState();
            _warrantOperReferenceTextField->setText(action->getOperationReference());
            _warrantOperLocalVariableTextField->setText(action->getOperationLocalVariable());
            _warrantOperFormulaTextField->setText(action->getOperFormula());

            switch (action->getDataAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneData->setSelectedComponent(_panelDataDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneData->setSelectedComponent(_panelDataReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneData->setSelectedComponent(_panelDataLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneData->setSelectedComponent(_panelDataFormula); break;
            default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getDataAddressing()));
            }
            _warrantDataReferenceTextField->setText(action->getDataReference());
            _warrantDataLocalVariableTextField->setText(action->getDataLocalVariable());
            _warrantDataFormulaTextField->setText(action->getDataFormula());

            _trainIdNameTextField->setText(action->getTrainIdName());
            _controlTrainComboBox->setSelectedItem(action->getControlAutoTrain());
        }

        QList<JComponent*> components =  QList<JComponent*>{
            _tabbedPaneWarrant,
            _tabbedPaneOperation,
            _tabbedPaneData};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Set warrant {0} to {1} {2}"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget((QWidget*)c->jself());
    }

    /*private*/ void ActionWarrantSwing::setDataPanelState() {
        ActionWarrant::DirectOperation::TYPE oper = (ActionWarrant::DirectOperation::TYPE)_stateComboBox->getSelectedIndex();
        bool newState =
                oper == ActionWarrant::DirectOperation::SetTrainId ||
                oper == ActionWarrant::DirectOperation::SetTrainName ||
                oper == ActionWarrant::DirectOperation::ControlAutoTrain;
        _tabbedPaneData->setEnabled(newState);
        _warrantDataReferenceTextField->setEnabled(newState);
        _warrantDataLocalVariableTextField->setEnabled(newState);
        _warrantDataFormulaTextField->setEnabled(newState);

        _controlTrainComboBox->setEnabled(newState);
        _trainIdNameTextField->setEnabled(newState);

        if (oper == ActionWarrant::DirectOperation::ControlAutoTrain) {
            _controlTrainComboBox->setVisible(true);
            _trainIdNameTextField->setVisible(false);
        } else {
            _controlTrainComboBox->setVisible(false);
            _trainIdNameTextField->setVisible(true);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ActionWarrantSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        validateWarrantSection(errorMessages);
        validateOperationSection(errorMessages);
        validateDataSection(errorMessages);
        return errorMessages->isEmpty();
    }

    /*private*/ void ActionWarrantSwing::validateWarrantSection(QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionWarrant* action = new ActionWarrant("IQDA1", "");

        try {
            if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantReference) {
                action->setReference(_warrantReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return;
        }

        try {
            action->setFormula(_warrantFormulaTextField->text());
            if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
            } else {
                throw new IllegalArgumentException("_tabbedPane has unknown selection");
            }
        } catch (ParserException* e) {
            errorMessages->append("Cannot parse formula: " + e->getMessage());
        }

        if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantDirect) {
            if (_warrantBeanPanel == nullptr || _warrantBeanPanel->getNamedBean() == nullptr) {
                errorMessages->append(tr("A warrant was not selected"));
            }
        }
    }

    /*private*/ void ActionWarrantSwing::validateOperationSection(QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionWarrant* action = new ActionWarrant("IQDA2", "");

        try {
            if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationReference) {
                action->setOperationReference(_warrantOperReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return;
        }

        try {
            action->setOperationFormula(_warrantOperFormulaTextField->text());
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

    /*private*/ void ActionWarrantSwing::validateDataSection(QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionWarrant* action = new ActionWarrant("IQDA3", "");

        try {
            if (_tabbedPaneData->getSelectedComponent() == _panelDataReference) {
                action->setDataReference(_warrantDataReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return;
        }

        try {
            action->setDataFormula(_warrantDataFormulaTextField->text());
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
            ActionWarrant::DirectOperation::TYPE oper = (ActionWarrant::DirectOperation::TYPE)_stateComboBox->getSelectedIndex();
            if (oper == ActionWarrant::DirectOperation::SetTrainId || oper == ActionWarrant::DirectOperation::SetTrainName) {
                if (_trainIdNameTextField->text().isEmpty()) {
                    errorMessages->append(tr("A train id or train name was not entered"));
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ MaleSocket* ActionWarrantSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ActionWarrant* action = new ActionWarrant(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionWarrantSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ActionWarrant*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object must be an ActionWarrant but is a: ")+object->bself()->metaObject()->className());
        }
        ActionWarrant* action = (ActionWarrant*) object->bself();

        if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantDirect) {
            Warrant* warrant = (Warrant*)_warrantBeanPanel->getNamedBean()->self();
            if (warrant != nullptr) {
                NamedBeanHandle<Warrant*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                        ->getNamedBeanHandle(warrant->getDisplayName(), warrant);
                action->setWarrant(handle);
            } else {
                action->removeWarrant();
            }
        } else {
            action->removeWarrant();
        }

        try {
            // Left section
            if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
                action->setReference(_warrantReferenceTextField->text());
            } else if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
                action->setLocalVariable(_warrantLocalVariableTextField->text());
            } else if (_tabbedPaneWarrant->getSelectedComponent() == _panelWarrantFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
                action->setFormula(_warrantFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneWarrant has unknown selection");
            }

            // Center section
            if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationDirect) {
                action->setOperationAddressing(NamedBeanAddressing::Direct);
                action->setOperationDirect((ActionWarrant::DirectOperation::TYPE)_stateComboBox->getSelectedIndex());
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationReference) {
                action->setOperationAddressing(NamedBeanAddressing::Reference);
                action->setOperationReference(_warrantOperReferenceTextField->text());
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationLocalVariable) {
                action->setOperationAddressing(NamedBeanAddressing::LocalVariable);
                action->setOperationLocalVariable(_warrantOperLocalVariableTextField->text());
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationFormula) {
                action->setOperationAddressing(NamedBeanAddressing::Formula);
                action->setOperationFormula(_warrantOperFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneOperation has unknown selection");
            }

            // Right section
            if (_tabbedPaneData->getSelectedComponent() == _panelDataDirect) {
                action->setDataAddressing(NamedBeanAddressing::Direct);
                // Handle optional data field
                if (action->getOperationDirect() == ActionWarrant::DirectOperation::SetTrainId
                        || action->getOperationDirect() == ActionWarrant::DirectOperation::SetTrainName) {
                    action->setTrainIdName(_trainIdNameTextField->text());
                } else if (action->getOperationDirect() == ActionWarrant::DirectOperation::ControlAutoTrain) {
                    action->setControlAutoTrain((ActionWarrant::ControlAutoTrain::TYPE) _controlTrainComboBox->currentIndex());
                }
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataReference) {
                action->setDataAddressing(NamedBeanAddressing::Reference);
                action->setDataReference(_warrantDataReferenceTextField->text());
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataLocalVariable) {
                action->setDataAddressing(NamedBeanAddressing::LocalVariable);
                action->setDataLocalVariable(_warrantDataLocalVariableTextField->text());
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataFormula) {
                action->setDataAddressing(NamedBeanAddressing::Formula);
                action->setDataFormula(_warrantDataFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneData has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ActionWarrantSwing::toString() {
        return tr("ActionWarrant");
    }

    //@Override
    /*public*/ void ActionWarrantSwing::dispose() {
        if (_warrantBeanPanel != nullptr) {
            _warrantBeanPanel->dispose();
        }
    }

