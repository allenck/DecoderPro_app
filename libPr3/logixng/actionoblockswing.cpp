#include "actionoblockswing.h"
#include "beanselectpanel.h"
#include "jtabbedpane.h"
#include "jtextfield.h"
#include "logixng/actionoblock.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/parserexception.h"
#include "oblockmanager.h"
#include "instancemanager.h"

ActionOBlockSwing::ActionOBlockSwing(QObject *parent)
    : AbstractDigitalActionSwing{parent}
{

}

/**
 * Configures an ActionOBlock object with a Swing JPanel.
 *
 * @author Daniel Bergqvist  Copyright 2021
 * @author Dave Sand         Copyright 2021
 */
// /*public*/ class ActionOBlockSwing extends AbstractDigitalActionSwing {



    //@Override
    /*protected*/ void ActionOBlockSwing::createPanel(/*@CheckForNulll*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ActionOBlock* action = nullptr;
        if(object) action= (ActionOBlock*)object->bself();

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

        _oblockBeanPanel = new BeanSelectPanel((OBlockManager*)InstanceManager::getDefault("OBlockManager"), nullptr);
        _panelOBlockDirect->layout()->addWidget(_oblockBeanPanel);

        _oblockReferenceTextField = new JTextField();
        _oblockReferenceTextField->setColumns(30);
        _panelOBlockReference->layout()->addWidget(_oblockReferenceTextField);

        _oblockLocalVariableTextField = new JTextField();
        _oblockLocalVariableTextField->setColumns(30);
        _panelOBlockLocalVariable->layout()->addWidget(_oblockLocalVariableTextField);

        _oblockFormulaTextField = new JTextField();
        _oblockFormulaTextField->setColumns(30);
        _panelOBlockFormula->layout()->addWidget(_oblockFormulaTextField);


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
        for (ActionOBlock::DirectOperation::TYPE e : ActionOBlock::DirectOperation::values()) {
            _stateComboBox->addItem(ActionOBlock::DirectOperation::toString(e),e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_stateComboBox);
        connect(_stateComboBox, &JComboBox::currentTextChanged,[=] {
            setDataPanelState();
        });
        _panelOperationDirect->layout()->addWidget(_stateComboBox);

        _oblockOperReferenceTextField = new JTextField();
        _oblockOperReferenceTextField->setColumns(30);
        _panelOperationReference->layout()->addWidget(_oblockOperReferenceTextField);

        _oblockOperLocalVariableTextField = new JTextField();
        _oblockOperLocalVariableTextField->setColumns(30);
        _panelOperationLocalVariable->layout()->addWidget(_oblockOperLocalVariableTextField);

        _oblockOperFormulaTextField = new JTextField();
        _oblockOperFormulaTextField->setColumns(30);
        _panelOperationFormula->layout()->addWidget(_oblockOperFormulaTextField);


        _tabbedPaneData = new JTabbedPane();
        _panelDataDirect = new JPanel(new FlowLayout);
        _panelDataReference = new JPanel(new FlowLayout);
        _panelDataLocalVariable = new JPanel(new FlowLayout);
        _panelDataFormula = new JPanel(new FlowLayout);

        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelDataDirect);
        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelDataReference);
        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelDataLocalVariable);
        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelDataFormula);

        _oblockDataDirectTextField = new JTextField();
        _oblockDataDirectTextField->setColumns(30);
        _panelDataDirect->layout()->addWidget(_oblockDataDirectTextField);

        _oblockDataReferenceTextField = new JTextField();
        _oblockDataReferenceTextField->setColumns(30);
        _panelDataReference->layout()->addWidget(_oblockDataReferenceTextField);

        _oblockDataLocalVariableTextField = new JTextField();
        _oblockDataLocalVariableTextField->setColumns(30);
        _panelDataLocalVariable->layout()->addWidget(_oblockDataLocalVariableTextField);

        _oblockDataFormulaTextField = new JTextField();
        _oblockDataFormulaTextField->setColumns(30);
        _panelDataFormula->layout()->addWidget(_oblockDataFormulaTextField);

        setDataPanelState();

        if (action != nullptr) {
            switch (action->getAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneOBlock->setSelectedComponent(_panelOBlockDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneOBlock->setSelectedComponent(_panelOBlockReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneOBlock->setSelectedComponent(_panelOBlockLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneOBlock->setSelectedComponent(_panelOBlockFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            if (action->getOBlock() != nullptr) {
                _oblockBeanPanel->setDefaultNamedBean(action->getOBlock()->getBean());
            }
            _oblockReferenceTextField->setText(action->getReference());
            _oblockLocalVariableTextField->setText(action->getLocalVariable());
            _oblockFormulaTextField->setText(action->getFormula());

            switch (action->getOperationAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneOperation->setSelectedComponent(_panelOperationDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneOperation->setSelectedComponent(_panelOperationReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneOperation->setSelectedComponent(_panelOperationLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneOperation->setSelectedComponent(_panelOperationFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            _stateComboBox->setSelectedItem(action->getOperationDirect());
            _oblockOperReferenceTextField->setText(action->getOperationReference());
            _oblockOperLocalVariableTextField->setText(action->getOperationLocalVariable());
            _oblockOperFormulaTextField->setText(action->getOperationFormula());

            switch (action->getDataAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneData->setSelectedComponent(_panelDataDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneData->setSelectedComponent(_panelDataReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneData->setSelectedComponent(_panelDataLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneData->setSelectedComponent(_panelDataFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getDataAddressing()));
            }
            _oblockDataReferenceTextField->setText(action->getDataReference());
            _oblockDataLocalVariableTextField->setText(action->getDataLocalVariable());
            _oblockDataFormulaTextField->setText(action->getDataFormula());

            _oblockDataDirectTextField->setText(action->getOBlockValue());
            setDataPanelState();
        }

        QList<JComponent*> components = QList<JComponent*>{
            _tabbedPaneOBlock,
            _tabbedPaneOperation,
            _tabbedPaneData};


        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Set oblock {0} to {1} {2}"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget((QWidget*)c->jself());
    }

    /*private*/ void ActionOBlockSwing::setDataPanelState() {
    bool newState = _stateComboBox->getSelectedItem() == ActionOBlock::DirectOperation::SetValue;
        _tabbedPaneData->setEnabled(newState);
        _oblockDataDirectTextField->setEnabled(newState);
        _oblockDataReferenceTextField->setEnabled(newState);
        _oblockDataLocalVariableTextField->setEnabled(newState);
        _oblockDataFormulaTextField->setEnabled(newState);
    }


    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ActionOBlockSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        validateBlockSection(errorMessages);
        validateOperationSection(errorMessages);
        validateDataSection(errorMessages);
        return errorMessages->isEmpty();
    }

    /*private*/ void ActionOBlockSwing::validateBlockSection(QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionOBlock* action = new ActionOBlock("IQDA1", "");

        try {
            if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockReference) {
                action->setReference(_oblockReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return;
        }

        try {
            action->setFormula(_oblockFormulaTextField->text());
            if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
            } else {
                throw new IllegalArgumentException("_tabbedPane has unknown selection");
            }
        } catch (ParserException* e) {
            errorMessages->append("Cannot parse formula: " + e->getMessage());
        }

        if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockDirect) {
            if (_oblockBeanPanel == nullptr || _oblockBeanPanel->getNamedBean() == nullptr) {
                errorMessages->append(tr("An oblock was not selected"));
            }
        }
    }

    /*private*/ void ActionOBlockSwing::validateOperationSection(QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionOBlock* action = new ActionOBlock("IQDA2", "");

        try {
            if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationReference) {
                action->setOperationReference(_oblockOperReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return;
        }

        try {
            action->setOperationFormula(_oblockOperFormulaTextField->text());
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

    /*private*/ void ActionOBlockSwing::validateDataSection(QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionOBlock* action = new ActionOBlock("IQDA3", "");

        try {
            if (_tabbedPaneData->getSelectedComponent() == _panelDataReference) {
                action->setDataReference(_oblockDataReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return;
        }

        try {
            action->setDataFormula(_oblockDataFormulaTextField->text());
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
            ActionOBlock::DirectOperation::TYPE oper = (ActionOBlock::DirectOperation::TYPE)_stateComboBox->getItemAt(_stateComboBox->getSelectedIndex()).toInt();
            if (oper == ActionOBlock::DirectOperation::SetValue) {
                if (_oblockDataDirectTextField->text().isEmpty()) {
                    errorMessages->append(tr("An oblock value was not entered"));
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ MaleSocket* ActionOBlockSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ActionOBlock* action = new ActionOBlock(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionOBlockSwing::updateObject(/*@Nonnull*/ Base* object) {
    if(!object) throw new NullPointerException();
        if (! (qobject_cast< ActionOBlock*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ActionOBlock but is a: ")+object->bself()->metaObject()->className());
        }
        ActionOBlock* action = (ActionOBlock*) object->bself();

        if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockDirect) {
            OBlock* oblock = (OBlock*)_oblockBeanPanel->getNamedBean()->self();
            if (oblock != nullptr) {
                NamedBeanHandle<OBlock*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(oblock->getDisplayName(), oblock);
                action->setOBlock(handle);
            } else {
                action->removeOBlock();
            }
        } else {
            action->removeOBlock();
        }

        try {
            // Left section
            if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
                action->setReference(_oblockReferenceTextField->text());
            } else if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
                action->setLocalVariable(_oblockLocalVariableTextField->text());
            } else if (_tabbedPaneOBlock->getSelectedComponent() == _panelOBlockFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
                action->setFormula(_oblockFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneOBlock has unknown selection");
            }

            // Center section
            if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationDirect) {
                action->setOperationAddressing(NamedBeanAddressing::Direct);
                action->setOperationDirect((ActionOBlock::DirectOperation::TYPE)_stateComboBox->getItemAt(_stateComboBox->getSelectedIndex()).toInt());
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationReference) {
                action->setOperationAddressing(NamedBeanAddressing::Reference);
                action->setOperationReference(_oblockOperReferenceTextField->text());
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationLocalVariable) {
                action->setOperationAddressing(NamedBeanAddressing::LocalVariable);
                action->setOperationLocalVariable(_oblockOperLocalVariableTextField->text());
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationFormula) {
                action->setOperationAddressing(NamedBeanAddressing::Formula);
                action->setOperationFormula(_oblockOperFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneOBlock has unknown selection");
            }

            // Right section
            if (_tabbedPaneData->getSelectedComponent() == _panelDataDirect) {
                action->setDataAddressing(NamedBeanAddressing::Direct);
                // Handle optional data field
                if (action->getOperationDirect() == ActionOBlock::DirectOperation::SetValue) {
                    action->setOBlockValue(_oblockDataDirectTextField->text());
                }
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataReference) {
                action->setDataAddressing(NamedBeanAddressing::Reference);
                action->setDataReference(_oblockDataReferenceTextField->text());
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataLocalVariable) {
                action->setDataAddressing(NamedBeanAddressing::LocalVariable);
                action->setDataLocalVariable(_oblockDataLocalVariableTextField->text());
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataFormula) {
                action->setDataAddressing(NamedBeanAddressing::Formula);
                action->setDataFormula(_oblockDataFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneBlock has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ActionOBlockSwing::toString() {
        return tr("ActionOBlock");
    }

    //@Override
    /*public*/ void ActionOBlockSwing::dispose() {
        if (_oblockBeanPanel != nullptr) {
            _oblockBeanPanel->dispose();
        }
    }

