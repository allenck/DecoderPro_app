#include "actionsignalheadswing.h"
#include "instancemanager.h"
#include "actionsignalhead.h"
#include "borderfactory.h"
#include "beanselectpanel.h"
#include "abstractsignalheadmanager.h"
#include "swingconfiguratorinterface.h"
#include "defaultdigitalactionmanager.h"
#include "parserexception.h"
#include "vptr.h"

/**
 * Configures an ActionSignalHead object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class ActionSignalHeadSwing extends AbstractDigitalActionSwing {

    /*public*/  /*static*/ /*final*/ int ActionSignalHeadSwing::NUM_COLUMNS_TEXT_FIELDS = 20;



    //@Override
    /*protected*/ void ActionSignalHeadSwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ActionSignalHead* action = (ActionSignalHead*)object->bself();

        panel = new JPanel();
        panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));

        JPanel* examplePanel = new JPanel(new FlowLayout());
        JPanel* innerExamplePanel = new JPanel(new FlowLayout());
        innerExamplePanel->setBorder(BorderFactory::createLineBorder(Qt::black));
        _exampleSignalHeadBeanPanel = new BeanSelectPanel((AbstractManager*)InstanceManager::getDefault("SignalHeadManager"), nullptr);
        innerExamplePanel->layout()->addWidget(_exampleSignalHeadBeanPanel);

        connect(_exampleSignalHeadBeanPanel->getBeanCombo(), &NamedBeanComboBox::currentIndexChanged, [=] {
            setAppearanceComboBox(nullptr);
        });


        JPanel* actionPanel = new JPanel(new FlowLayout());


        // Set up tabbed pane for selecting the signal head
        _tabbedPaneSignalHead = new JTabbedPane();
        _panelSignalHeadDirect = new JPanel(new FlowLayout());
        _panelSignalHeadReference = new JPanel(new FlowLayout());
        _panelSignalHeadLocalVariable = new JPanel(new FlowLayout());
        _panelSignalHeadFormula = new JPanel(new FlowLayout());

        _tabbedPaneSignalHead->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelSignalHeadDirect);
        _tabbedPaneSignalHead->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelSignalHeadReference);
        _tabbedPaneSignalHead->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelSignalHeadLocalVariable);
        _tabbedPaneSignalHead->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelSignalHeadFormula);

        connect(_tabbedPaneSignalHead, &JTabbedPane::currentChanged, [=] {
            setGuiEnabledStates();
        });

        _signalHeadBeanPanel = new BeanSelectPanel((AbstractManager*)InstanceManager::getDefault("SignalHeadManager"), nullptr);
        _panelSignalHeadDirect->layout()->addWidget(_signalHeadBeanPanel);

        connect(_signalHeadBeanPanel->getBeanCombo(), &JComboBox::currentTextChanged, [=]{
            setAppearanceComboBox(nullptr);
        });


        _signalHeadReferenceTextField = new JTextField();
        _signalHeadReferenceTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelSignalHeadReference->layout()->addWidget(_signalHeadReferenceTextField);

        _signalHeadLocalVariableTextField = new JTextField();
        _signalHeadLocalVariableTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelSignalHeadLocalVariable->layout()->addWidget(_signalHeadLocalVariableTextField);

        _signalHeadFormulaTextField = new JTextField();
        _signalHeadFormulaTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelSignalHeadFormula->layout()->addWidget(_signalHeadFormulaTextField);


        // Set up the tabbed pane for selecting the operation
        _tabbedPaneOperationType = new JTabbedPane();
        _panelOperationTypeDirect = new JPanel(new FlowLayout());
        _panelOperationTypeDirect->setLayout(new QVBoxLayout());//_panelOperationTypeDirect, BoxLayout.Y_AXIS));
        _panelOperationTypeReference = new JPanel(new FlowLayout());
        _panelOperationTypeReference->setLayout(new QVBoxLayout());//_panelOperationTypeReference, BoxLayout.Y_AXIS));
        _panelOperationTypeLocalVariable = new JPanel(new FlowLayout());
        _panelOperationTypeLocalVariable->setLayout(new QVBoxLayout());//_panelOperationTypeLocalVariable, BoxLayout.Y_AXIS));
        _panelOperationTypeFormula = new JPanel(new FlowLayout());
        _panelOperationTypeFormula->setLayout(new QVBoxLayout());//_panelOperationTypeFormula, BoxLayout.Y_AXIS));

        _tabbedPaneOperationType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelOperationTypeDirect);
        _tabbedPaneOperationType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelOperationTypeReference);
        _tabbedPaneOperationType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelOperationTypeLocalVariable);
        _tabbedPaneOperationType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelOperationTypeFormula);

        connect(_tabbedPaneOperationType, &JTabbedPane::currentChanged, [=]{
            setGuiEnabledStates();
        });

        _operationComboBox = new JComboBox();
        for (ActionSignalHead::OperationType::TYPE e : ActionSignalHead::OperationType::values()) {
            _operationComboBox->addItem(ActionSignalHead::OperationType::toString(e), e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_operationComboBox);
        connect(_operationComboBox, &JComboBox::currentIndexChanged, [=] {
            setGuiEnabledStates();
        });

        _panelOperationTypeDirect->layout()->addWidget(new JLabel(tr("ActionSignalHead_Operation")));
        _panelOperationTypeDirect->layout()->addWidget(_operationComboBox);

        _signalHeadOperationReferenceTextField = new JTextField();
        _signalHeadOperationReferenceTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelOperationTypeReference->layout()->addWidget(new JLabel(tr("Operation")));
        _panelOperationTypeReference->layout()->addWidget(_signalHeadOperationReferenceTextField);

        _signalHeadOperationLocalVariableTextField = new JTextField();
        _signalHeadOperationLocalVariableTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelOperationTypeLocalVariable->layout()->addWidget(new JLabel(tr("Operation")));
        _panelOperationTypeLocalVariable->layout()->addWidget(_signalHeadOperationLocalVariableTextField);

        _signalHeadOperationFormulaTextField = new JTextField();
        _signalHeadOperationFormulaTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelOperationTypeFormula->layout()->addWidget(new JLabel(tr("Operation")));
        _panelOperationTypeFormula->layout()->addWidget(_signalHeadOperationFormulaTextField);


        // Set up the tabbed pane for selecting the appearance
        _tabbedPaneAppearanceType = new JTabbedPane();
        _panelAppearanceTypeDirect = new JPanel(new FlowLayout());
        _panelAppearanceTypeDirect->setLayout(new QVBoxLayout());//_panelAppearanceTypeDirect, BoxLayout.Y_AXIS));
        _panelAppearanceTypeReference = new JPanel(new FlowLayout());
        _panelAppearanceTypeReference->setLayout(new QVBoxLayout());//_panelAppearanceTypeReference, BoxLayout.Y_AXIS));
        _panelAppearanceTypeLocalVariable = new JPanel(new FlowLayout());
        _panelAppearanceTypeLocalVariable->setLayout(new QVBoxLayout());//_panelAppearanceTypeLocalVariable, BoxLayout.Y_AXIS));
        _panelAppearanceTypeFormula = new JPanel(new FlowLayout());
        _panelAppearanceTypeFormula->setLayout(new QVBoxLayout());//_panelAppearanceTypeFormula, BoxLayout.Y_AXIS));

        _tabbedPaneAppearanceType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelAppearanceTypeDirect);
        _tabbedPaneAppearanceType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelAppearanceTypeReference);
        _tabbedPaneAppearanceType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelAppearanceTypeLocalVariable);
        _tabbedPaneAppearanceType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelAppearanceTypeFormula);

        connect(_tabbedPaneAppearanceType, &JTabbedPane::currentChanged, [=] {
            setGuiEnabledStates();
        });

        _signalHeadAppearanceComboBox = new JComboBox();
        _panelAppearanceTypeDirect->layout()->addWidget(new JLabel(tr("Appearance")));
        _panelAppearanceTypeDirect->layout()->addWidget(_signalHeadAppearanceComboBox);

        _signalHeadAppearanceReferenceTextField = new JTextField();
        _signalHeadAppearanceReferenceTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelAppearanceTypeReference->layout()->addWidget(new JLabel(tr("Appearance")));
        _panelAppearanceTypeReference->layout()->addWidget(_signalHeadAppearanceReferenceTextField);

        _signalHeadAppearanceLocalVariableTextField = new JTextField();
        _signalHeadAppearanceLocalVariableTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelAppearanceTypeLocalVariable->layout()->addWidget(new JLabel(tr("Appearance")));
        _panelAppearanceTypeLocalVariable->layout()->addWidget(_signalHeadAppearanceLocalVariableTextField);

        _signalHeadAppearanceFormulaTextField = new JTextField();
        _signalHeadAppearanceFormulaTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelAppearanceTypeFormula->layout()->addWidget(new JLabel(tr("Appearance")));
        _panelAppearanceTypeFormula->layout()->addWidget(_signalHeadAppearanceFormulaTextField);


        JPanel* notePanel = new JPanel(new FlowLayout());
        notePanel->setBorder(BorderFactory::createMatteBorder(1, 0, 0, 0, Qt::white));
        examplePanel->setBorder(BorderFactory::createMatteBorder(0, 0, 1, 0, Qt::white));

        JLabel* noteLabel = new JLabel(tr("<html> \
If you do not use Direct addressing of the signal %1 but are using Direct addressing<br> \
of the %2, you need to select an example signal %1. The example signal %1} is<br> \
used to tell JMRI which %2 the indirect addressed signal %1 may show.</html>").arg(
                tr("head"),
                tr("appearances")));
        notePanel->layout()->addWidget(noteLabel);


        examplePanel->layout()->addWidget(new JLabel(tr("Example signal head")));
        examplePanel->layout()->addWidget(innerExamplePanel);


        if (action != nullptr) {
            switch (action->getAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneSignalHead->setSelectedComponent(_panelSignalHeadDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneSignalHead->setSelectedComponent(_panelSignalHeadReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneSignalHead->setSelectedComponent(_panelSignalHeadLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneSignalHead->setSelectedComponent(_panelSignalHeadFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            if (action->getSignalHead() != nullptr) {
                _signalHeadBeanPanel->setDefaultNamedBean(action->getSignalHead()->getBean());
            }
            if (action->getExampleSignalHead() != nullptr) {
                _exampleSignalHeadBeanPanel->setDefaultNamedBean(action->getExampleSignalHead()->getBean());
            }
            _signalHeadReferenceTextField->setText(action->getReference());
            _signalHeadLocalVariableTextField->setText(action->getLocalVariable());
            _signalHeadFormulaTextField->setText(action->getFormula());


            switch (action->getOperationAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneOperationType->setSelectedComponent(_panelOperationTypeDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneOperationType->setSelectedComponent(_panelOperationTypeReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneOperationType->setSelectedComponent(_panelOperationTypeLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneOperationType->setSelectedComponent(_panelOperationTypeFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getOperationAddressing()));
            }
            _operationComboBox->setSelectedItem(action->getOperationType());
            _signalHeadOperationReferenceTextField->setText(action->getOperationReference());
            _signalHeadOperationLocalVariableTextField->setText(action->getOperationLocalVariable());
            _signalHeadOperationFormulaTextField->setText(action->getOperationFormula());


            switch (action->getAppearanceAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneAppearanceType->setSelectedComponent(_panelAppearanceTypeDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneAppearanceType->setSelectedComponent(_panelAppearanceTypeReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneAppearanceType->setSelectedComponent(_panelAppearanceTypeLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneAppearanceType->setSelectedComponent(_panelAppearanceTypeFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAppearanceAddressing()));
            }
            _signalHeadAppearanceReferenceTextField->setText(action->getAppearanceReference());
            _signalHeadAppearanceLocalVariableTextField->setText(action->getAppearanceLocalVariable());
            _signalHeadAppearanceFormulaTextField->setText(action->getAppearanceFormula());

            //jmri.util.ThreadingUtil.runOnGUIEventually(() -> { setAppearanceComboBox(action); });
            ThreadingUtil::runOnGUIEventually(new ActionSignalHeadSwing_run(action, this));
        }

        QList<JComponent*> components = QList<JComponent*>{
            _tabbedPaneSignalHead,
            _tabbedPaneOperationType,
            _tabbedPaneAppearanceType
        };

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Set signal head %1 to %2 %3"), components);

        for (JComponent* c : componentList) actionPanel->layout()->addWidget(c->jself());

        panel->layout()->addWidget(actionPanel);
        panel->layout()->addWidget(notePanel);
        panel->layout()->addWidget(examplePanel);

        setGuiEnabledStates();
    }


    /*private*/ void ActionSignalHeadSwing::setGuiEnabledStates() {
        _tabbedPaneAppearanceType->QWidget::setEnabled(false);
        _signalHeadAppearanceComboBox->setEnabled(false);
        _signalHeadAppearanceReferenceTextField->setEnabled(false);
        _signalHeadAppearanceLocalVariableTextField->setEnabled(false);
        _signalHeadAppearanceFormulaTextField->setEnabled(false);
        _exampleSignalHeadBeanPanel->getBeanCombo()->setEnabled(false);

        if (_tabbedPaneOperationType->getSelectedComponent() == _panelOperationTypeDirect &&
                _operationComboBox->getSelectedItem() != ActionSignalHead::OperationType::Appearance) {
            return;
        }

        _tabbedPaneAppearanceType->QWidget::setEnabled(true);

        if (_tabbedPaneSignalHead->getSelectedComponent() != _panelSignalHeadDirect &&
                _tabbedPaneAppearanceType->getSelectedComponent() == _panelAppearanceTypeDirect) {
            _exampleSignalHeadBeanPanel->getBeanCombo()->setEnabled(true);
        }

        if (_tabbedPaneAppearanceType->getSelectedComponent() == _panelAppearanceTypeDirect) {
            _signalHeadAppearanceComboBox->setEnabled(true);
        }
        if (_tabbedPaneAppearanceType->getSelectedComponent() == _panelAppearanceTypeReference) {
            _signalHeadAppearanceReferenceTextField->setEnabled(true);
        }
        if (_tabbedPaneAppearanceType->getSelectedComponent() == _panelAppearanceTypeLocalVariable) {
            _signalHeadAppearanceLocalVariableTextField->setEnabled(true);
        }
        if (_tabbedPaneAppearanceType->getSelectedComponent() == _panelAppearanceTypeFormula) {
            _signalHeadAppearanceFormulaTextField->setEnabled(true);
        }
    }

    /*private*/ void ActionSignalHeadSwing::setAppearanceComboBox(ActionSignalHead* action) {
        SignalHead* sh;
        if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadDirect) {
            sh = (SignalHead*) _signalHeadBeanPanel->getBeanCombo()->getSelectedItem()->self();
        } else {
            sh = (SignalHead*) _exampleSignalHeadBeanPanel->getBeanCombo()->getSelectedItem()->self();
        }

        if (sh != nullptr) {
            _signalHeadAppearanceComboBox->clear();
            QVector<int> states = sh->getValidStates();
            for (int s : states) {
                SignalHeadAppearance* sha = new SignalHeadAppearance();
                sha->_state = s;
                sha->_name = sh->getAppearanceName(s);
                _signalHeadAppearanceComboBox->addItem(sha->_name, VPtr<SignalHeadAppearance>::asQVariant(sha));
                if (action != nullptr) {
                    if (action->getAppearance() == s) _signalHeadAppearanceComboBox->setSelectedItem(sha->toString());
                }
            }
//            JComboBoxUtil->setupComboBoxMaxRows(_signalHeadAppearanceComboBox);
        }
    }


    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ActionSignalHeadSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionSignalHead* action = new ActionSignalHead("IQDA1", "");

        try {
            if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadReference) {
                action->setReference(_signalHeadReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            if (_tabbedPaneOperationType->getSelectedComponent() == _panelOperationTypeReference) {
                action->setOperationReference(_signalHeadOperationReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            action->setFormula(_signalHeadFormulaTextField->text());
            if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
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
    /*public*/  MaleSocket* ActionSignalHeadSwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        ActionSignalHead* action = new ActionSignalHead(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionSignalHeadSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ActionSignalHead*>(object->bself()))) {
            throw new IllegalArgumentException(QString(QString("object must be an ActionSignalHead but is a: ")+object->bself()->metaObject()->className()));
        }
        ActionSignalHead* action = (ActionSignalHead*)object->bself();
        if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadDirect) {
            SignalHead* signalHead = (SignalHead*)_signalHeadBeanPanel->getNamedBean()->self();
            if (signalHead != nullptr) {
                NamedBeanHandle<SignalHead*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(signalHead->getDisplayName(), signalHead);
                action->setSignalHead(handle);
            } else {
                action->removeSignalHead();
            }
        } else {
            action->removeSignalHead();
        }

        if (!_exampleSignalHeadBeanPanel->isEmpty()
                && (_tabbedPaneSignalHead->getSelectedComponent() != _panelSignalHeadDirect)
                && (_tabbedPaneAppearanceType->getSelectedComponent() == _panelAppearanceTypeDirect)) {

            SignalHead* signalHead = (SignalHead*)_exampleSignalHeadBeanPanel->getNamedBean()->self();
            if (signalHead != nullptr) {
                NamedBeanHandle<SignalHead*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(signalHead->getDisplayName(), signalHead);
                action->setExampleSignalHead(handle);
            }
        } else {
            action->removeExampleSignalHead();
        }

        try {
            if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
                action->setReference(_signalHeadReferenceTextField->text());
            } else if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
                action->setLocalVariable(_signalHeadLocalVariableTextField->text());
            } else if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
                action->setFormula(_signalHeadFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneSignalHead has unknown selection");
            }

            if (_tabbedPaneOperationType->getSelectedComponent() == _panelOperationTypeDirect) {
                action->setOperationAddressing(NamedBeanAddressing::Direct);
                action->setOperationType((ActionSignalHead::OperationType::TYPE)_operationComboBox->getSelectedItem().toInt());
            } else if (_tabbedPaneOperationType->getSelectedComponent() == _panelOperationTypeReference) {
                action->setOperationAddressing(NamedBeanAddressing::Reference);
                action->setOperationReference(_signalHeadOperationReferenceTextField->text());
            } else if (_tabbedPaneOperationType->getSelectedComponent() == _panelOperationTypeLocalVariable) {
                action->setOperationAddressing(NamedBeanAddressing::LocalVariable);
                action->setOperationLocalVariable(_signalHeadOperationLocalVariableTextField->text());
            } else if (_tabbedPaneOperationType->getSelectedComponent() == _panelOperationTypeFormula) {
                action->setOperationAddressing(NamedBeanAddressing::Formula);
                action->setOperationFormula(_signalHeadOperationFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneOperationType has unknown selection");
            }

            if (_tabbedPaneAppearanceType->getSelectedComponent() == _panelAppearanceTypeDirect) {
                action->setAppearanceAddressing(NamedBeanAddressing::Direct);

                if (_signalHeadAppearanceComboBox->getItemCount() > 0) {
                    action->setAppearance(VPtr<SignalHeadAppearance>::asPtr(_signalHeadAppearanceComboBox
                            ->getItemAt(_signalHeadAppearanceComboBox->getSelectedIndex()))->_state);
                }
            } else if (_tabbedPaneAppearanceType->getSelectedComponent() == _panelAppearanceTypeReference) {
                action->setAppearanceAddressing(NamedBeanAddressing::Reference);
                action->setAppearanceReference(_signalHeadAppearanceReferenceTextField->text());
            } else if (_tabbedPaneAppearanceType->getSelectedComponent() == _panelAppearanceTypeLocalVariable) {
                action->setAppearanceAddressing(NamedBeanAddressing::LocalVariable);
                action->setAppearanceLocalVariable(_signalHeadAppearanceLocalVariableTextField->text());
            } else if (_tabbedPaneAppearanceType->getSelectedComponent() == _panelAppearanceTypeFormula) {
                action->setAppearanceAddressing(NamedBeanAddressing::Formula);
                action->setAppearanceFormula(_signalHeadAppearanceFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneAppearanceType has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ActionSignalHeadSwing::toString() {
        return tr("SignalHead");
    }

    //@Override
    /*public*/  void ActionSignalHeadSwing::dispose() {
    }




