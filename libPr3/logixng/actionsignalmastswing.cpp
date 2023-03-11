#include "actionsignalmastswing.h"
#include "beanselectpanel.h"
#include "defaultsignalmastmanager.h"
#include "jcombobox.h"
#include "jtabbedpane.h"
#include "jtextfield.h"
#include "logixng/actionsignalmast.h"
#include <QBoxLayout>
#include "borderfactory.h"
#include "instancemanager.h"
#include "vptr.h"
#include "defaultdigitalactionmanager.h"
#include "parserexception.h"

ActionSignalMastSwing::ActionSignalMastSwing(QObject *parent)
    : AbstractDigitalActionSwing{parent}
{

}
/**
 * Configures an ActionSignalMast object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class ActionSignalMastSwing extends AbstractDigitalActionSwing {

    /*public*/ /*static*/ /*final*/ int ActionSignalMastSwing::NUM_COLUMNS_TEXT_FIELDS = 20;


    //@Override
    /*protected*/ void ActionSignalMastSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ActionSignalMast* action = nullptr;
        if(action) action = (ActionSignalMast*)object->bself();

        panel = new JPanel();
        panel->setLayout(new QVBoxLayout());//panel, BoxLayout));//.Y_AXIS));

        JPanel* examplePanel = new JPanel(new FlowLayout);
        JPanel* innerExamplePanel = new JPanel(new FlowLayout);
        innerExamplePanel->setBorder(BorderFactory::createLineBorder(Qt::black));
        _exampleSignalMastBeanPanel = new BeanSelectPanel(((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager")), nullptr);
        innerExamplePanel->layout()->addWidget(_exampleSignalMastBeanPanel);

        //_exampleSignalMastBeanPanel->getBeanCombo()->addActionListener((java.awt.event.ActionEvent e) -> {
        connect(_exampleSignalMastBeanPanel->getBeanCombo(), &NamedBeanComboBox::currentTextChanged, [=]{
            setAspectComboBox(nullptr);
        });


        JPanel* actionPanel = new JPanel();


        // Set up tabbed pane for selecting the signal head
        _tabbedPaneSignalMast = new JTabbedPane();
        _panelSignalMastDirect = new JPanel(new FlowLayout);
        _panelSignalMastReference = new JPanel(new FlowLayout);
        _panelSignalMastLocalVariable = new JPanel(new FlowLayout);
        _panelSignalMastFormula = new JPanel(new FlowLayout);

        _tabbedPaneSignalMast->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelSignalMastDirect);
        _tabbedPaneSignalMast->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelSignalMastReference);
        _tabbedPaneSignalMast->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelSignalMastLocalVariable);
        _tabbedPaneSignalMast->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelSignalMastFormula);

        //_tabbedPaneSignalMast.addChangeListener((ChangeEvent e) -> {
        connect(_tabbedPaneSignalMast, &JTabbedPane::currentChanged, [=]{
            setGuiEnabledStates();
        });

        _signalMastBeanPanel = new BeanSelectPanel((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"), nullptr);
        _panelSignalMastDirect->layout()->addWidget(_signalMastBeanPanel);

        //_signalMastBeanPanel->getBeanCombo().addActionListener((java.awt.event.ActionEvent e) -> {
        connect(_signalMastBeanPanel->getBeanCombo(), &NamedBeanComboBox::currentTextChanged, [=] {
            setAspectComboBox(nullptr);
        });

        _signalMastReferenceTextField = new JTextField();
        _signalMastReferenceTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelSignalMastReference->layout()->addWidget(_signalMastReferenceTextField);

        _signalMastLocalVariableTextField = new JTextField();
        _signalMastLocalVariableTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelSignalMastLocalVariable->layout()->addWidget(_signalMastLocalVariableTextField);

        _signalMastFormulaTextField = new JTextField();
        _signalMastFormulaTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelSignalMastFormula->layout()->addWidget(_signalMastFormulaTextField);


        // Set up the tabbed pane for selecting the operation
        _tabbedPaneOperationType = new JTabbedPane();
        _panelOperationTypeDirect = new JPanel();
        _panelOperationTypeDirect->setLayout(new QVBoxLayout());//_panelOperationTypeDirect, BoxLayout.Y_AXIS));
        _panelOperationTypeReference = new JPanel();
        _panelOperationTypeReference->setLayout(new QVBoxLayout());//_panelOperationTypeReference, BoxLayout.Y_AXIS));
        _panelOperationTypeLocalVariable = new JPanel();
        _panelOperationTypeLocalVariable->setLayout(new QVBoxLayout());//_panelOperationTypeLocalVariable, BoxLayout.Y_AXIS));
        _panelOperationTypeFormula = new JPanel();
        _panelOperationTypeFormula->setLayout(new QVBoxLayout());//_panelOperationTypeFormula, BoxLayout.Y_AXIS));

        _tabbedPaneOperationType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelOperationTypeDirect);
        _tabbedPaneOperationType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelOperationTypeReference);
        _tabbedPaneOperationType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelOperationTypeLocalVariable);
        _tabbedPaneOperationType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelOperationTypeFormula);

        //_tabbedPaneOperationType.addChangeListener((ChangeEvent e) -> {
        connect(_tabbedPaneOperationType, &JTabbedPane::currentChanged, [=]{
            setGuiEnabledStates();
        });

        _operationComboBox = new JComboBox();
        for (ActionSignalMast::OperationType::TYPE e : ActionSignalMast::OperationType::values()) {
            _operationComboBox->addItem(ActionSignalMast::OperationType::toString(e),e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_operationComboBox);

        //_operationComboBox.addActionListener(e -> {
        connect(_operationComboBox, &JComboBox::currentTextChanged, [=]{
            setGuiEnabledStates();
        });

        _panelOperationTypeDirect->layout()->addWidget(new JLabel(tr("ActionSignalMast_Operation")));
        _panelOperationTypeDirect->layout()->addWidget(_operationComboBox);

        _signalMastOperationReferenceTextField = new JTextField();
        _signalMastOperationReferenceTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelOperationTypeReference->layout()->addWidget(new JLabel(tr("ActionSignalMast_Operation")));
        _panelOperationTypeReference->layout()->addWidget(_signalMastOperationReferenceTextField);

        _signalMastOperationLocalVariableTextField = new JTextField();
        _signalMastOperationLocalVariableTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelOperationTypeLocalVariable->layout()->addWidget(new JLabel(tr("ActionSignalMast_Operation")));
        _panelOperationTypeLocalVariable->layout()->addWidget(_signalMastOperationLocalVariableTextField);

        _signalMastOperationFormulaTextField = new JTextField();
        _signalMastOperationFormulaTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelOperationTypeFormula->layout()->addWidget(new JLabel(tr("ActionSignalMast_Operation")));
        _panelOperationTypeFormula->layout()->addWidget(_signalMastOperationFormulaTextField);


        // Set up the tabbed pane for selecting the appearance
        _tabbedPaneAspectType = new JTabbedPane();
        _panelAspectTypeDirect = new JPanel();
        _panelAspectTypeDirect->setLayout(new QVBoxLayout());//_panelAspectTypeDirect, BoxLayout.Y_AXIS));
        _panelAspectTypeReference = new JPanel();
        _panelAspectTypeReference->setLayout(new QVBoxLayout());//_panelAspectTypeReference, BoxLayout.Y_AXIS));
        _panelAspectTypeLocalVariable = new JPanel();
        _panelAspectTypeLocalVariable->setLayout(new QVBoxLayout());//_panelAspectTypeLocalVariable, BoxLayout.Y_AXIS));
        _panelAspectTypeFormula = new JPanel();
        _panelAspectTypeFormula->setLayout(new QVBoxLayout());//_panelAspectTypeFormula, BoxLayout.Y_AXIS));

        _tabbedPaneAspectType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelAspectTypeDirect);
        _tabbedPaneAspectType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelAspectTypeReference);
        _tabbedPaneAspectType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelAspectTypeLocalVariable);
        _tabbedPaneAspectType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelAspectTypeFormula);

        //_tabbedPaneAspectType.addChangeListener((ChangeEvent e) -> {
        connect(_tabbedPaneAspectType, &JTabbedPane::currentChanged, [=]{
            setGuiEnabledStates();
        });

        _signalMastAspectComboBox = new JComboBox();
        _panelAspectTypeDirect->layout()->addWidget(new JLabel(tr("ActionSignalMast_Aspect")));
        _panelAspectTypeDirect->layout()->addWidget(_signalMastAspectComboBox);

        _signalMastAspectReferenceTextField = new JTextField();
        _signalMastAspectReferenceTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelAspectTypeReference->layout()->addWidget(new JLabel(tr("ActionSignalMast_Aspect")));
        _panelAspectTypeReference->layout()->addWidget(_signalMastAspectReferenceTextField);

        _signalMastAspectLocalVariableTextField = new JTextField();
        _signalMastAspectLocalVariableTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelAspectTypeLocalVariable->layout()->addWidget(new JLabel(tr("ActionSignalMast_Aspect")));
        _panelAspectTypeLocalVariable->layout()->addWidget(_signalMastAspectLocalVariableTextField);

        _signalMastAspectFormulaTextField = new JTextField();
        _signalMastAspectFormulaTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelAspectTypeFormula->layout()->addWidget(new JLabel(tr("ActionSignalMast_Aspect")));
        _panelAspectTypeFormula->layout()->addWidget(_signalMastAspectFormulaTextField);


        JPanel* notePanel = new JPanel();
        notePanel->setBorder(BorderFactory::createMatteBorder(1, 0, 0, 0, Qt::white));
        examplePanel->setBorder(BorderFactory::createMatteBorder(0, 0, 1, 0, Qt::white));

        JLabel* noteLabel = new JLabel(tr("<html> If you do not use Direct addressing of the signal %1 but are using Direct addressing<br> of the %2, you need to select an example signal %1. The example signal %1 is<br> used to tell JMRI which %2 the indirect addressed signal %1 may show.</html>").arg(
                tr("SignalExampleMast"),
                tr("SignalExampleAspects")));
        notePanel->layout()->addWidget(noteLabel);


        examplePanel->layout()->addWidget(new JLabel(tr("ActionSignalMast_ExampleBean")));
        examplePanel->layout()->addWidget(innerExamplePanel);


        if (action != nullptr) {
            switch (action->getAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneSignalMast->setSelectedComponent(_panelSignalMastDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneSignalMast->setSelectedComponent(_panelSignalMastReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneSignalMast->setSelectedComponent(_panelSignalMastLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneSignalMast->setSelectedComponent(_panelSignalMastFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            if (action->getSignalMast() != nullptr) {
                _signalMastBeanPanel->setDefaultNamedBean(action->getSignalMast()->getBean());
            }
            if (action->getExampleSignalMast() != nullptr) {
                _exampleSignalMastBeanPanel->setDefaultNamedBean(action->getExampleSignalMast()->getBean());
            }
            _signalMastReferenceTextField->setText(action->getReference());
            _signalMastLocalVariableTextField->setText(action->getLocalVariable());
            _signalMastFormulaTextField->setText(action->getFormula());


            switch (action->getOperationAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneOperationType->setSelectedComponent(_panelOperationTypeDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneOperationType->setSelectedComponent(_panelOperationTypeReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneOperationType->setSelectedComponent(_panelOperationTypeLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneOperationType->setSelectedComponent(_panelOperationTypeFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getOperationAddressing()));
            }
            _operationComboBox->setSelectedItem(action->getOperationType());
            _signalMastOperationReferenceTextField->setText(action->getOperationReference());
            _signalMastOperationLocalVariableTextField->setText(action->getOperationLocalVariable());
            _signalMastOperationFormulaTextField->setText(action->getOperationFormula());


            switch (action->getAspectAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneAspectType->setSelectedComponent(_panelAspectTypeDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneAspectType->setSelectedComponent(_panelAspectTypeReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneAspectType->setSelectedComponent(_panelAspectTypeLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneAspectType->setSelectedComponent(_panelAspectTypeFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAspectAddressing()));
            }
            _signalMastAspectReferenceTextField->setText(action->getAspectReference());
            _signalMastAspectLocalVariableTextField->setText(action->getAspectLocalVariable());
            _signalMastAspectFormulaTextField->setText(action->getAspectFormula());
#if 0 // TODO
            ThreadingUtil::runOnGUIEventually(() -> { setAspectComboBox(action); });
#endif
            ThreadingUtil::runOnGUIEventually(new ASMS_ThreaingUtil(action, this));
        }

        QList<JComponent*> components = QList<JComponent*>{
            _tabbedPaneSignalMast,
            _tabbedPaneOperationType,
            _tabbedPaneAspectType
        };

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Set signal mast {0} to {1} {2}"), components);

        for (JComponent* c : componentList) actionPanel->layout()->addWidget(c->jself());

        panel->layout()->addWidget(actionPanel);
        panel->layout()->addWidget(notePanel);
        panel->layout()->addWidget(examplePanel);

        setGuiEnabledStates();
    }

    /*private*/ void ActionSignalMastSwing::setGuiEnabledStates() {
        _tabbedPaneAspectType->setEnabled(false);
        _signalMastAspectComboBox->setEnabled(false);
        _signalMastAspectReferenceTextField->setEnabled(false);
        _signalMastAspectLocalVariableTextField->setEnabled(false);
        _signalMastAspectFormulaTextField->setEnabled(false);
        _exampleSignalMastBeanPanel->getBeanCombo()->setEnabled(false);

        if (_tabbedPaneOperationType->getSelectedComponent() == _panelOperationTypeDirect &&
                _operationComboBox->getSelectedItem() != ActionSignalMast::OperationType::Aspect) {
            return;
        }

        _tabbedPaneAspectType->setEnabled(true);

        if (_tabbedPaneSignalMast->getSelectedComponent() != _panelSignalMastDirect &&
                _tabbedPaneAspectType->getSelectedComponent() == _panelAspectTypeDirect) {
            _exampleSignalMastBeanPanel->getBeanCombo()->setEnabled(true);
        }

        if (_tabbedPaneAspectType->getSelectedComponent() == _panelAspectTypeDirect) {
            _signalMastAspectComboBox->setEnabled(true);
        }
        if (_tabbedPaneAspectType->getSelectedComponent() == _panelAspectTypeReference) {
            _signalMastAspectReferenceTextField->setEnabled(true);
        }
        if (_tabbedPaneAspectType->getSelectedComponent() == _panelAspectTypeLocalVariable) {
            _signalMastAspectLocalVariableTextField->setEnabled(true);
        }
        if (_tabbedPaneAspectType->getSelectedComponent() == _panelAspectTypeFormula) {
            _signalMastAspectFormulaTextField->setEnabled(true);
        }
    }

    /*private*/ void ActionSignalMastSwing::setAspectComboBox(ActionSignalMast* action) {
        SignalMast* sm;
        if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastDirect) {
            sm = (SignalMast*)_signalMastBeanPanel->getBeanCombo()->getSelectedItem()->self();
        } else {
            sm = (SignalMast*) _exampleSignalMastBeanPanel->getBeanCombo()->getSelectedItem()->self();
        }

        if (sm != nullptr) {
            _signalMastAspectComboBox->clear();
            for (QString aspect : sm->getValidAspects()) {
                _signalMastAspectComboBox->addItem(aspect);
                if (action != nullptr) {
                    if (aspect == (action->getAspect())) _signalMastAspectComboBox->setSelectedItem(aspect);
                }
            }
//            JComboBoxUtil->setupComboBoxMaxRows(_signalMastAspectComboBox);
        }
    }


    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ActionSignalMastSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionSignalMast* action = new ActionSignalMast("IQDA1", "null");

        try {
            if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastReference) {
                action->setReference(_signalMastReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            if (_tabbedPaneOperationType->getSelectedComponent() == _panelOperationTypeReference) {
                action->setOperationReference(_signalMastOperationReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            action->setFormula(_signalMastFormulaTextField->text());
            if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastFormula) {
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
    /*public*/ MaleSocket* ActionSignalMastSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ActionSignalMast* action = new ActionSignalMast(systemName, userName);
        updateObject(action);
        return (AbstractMaleSocket*)((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionSignalMastSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ActionSignalMast*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ActionSignalMast but is a: ")+object->bself()->metaObject()->className());
        }
        ActionSignalMast* action = (ActionSignalMast*)object->bself();
        if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastDirect) {
            SignalMast* signalMast = (SignalMast*)_signalMastBeanPanel->getNamedBean()->self();
            if (signalMast != nullptr) {
                NamedBeanHandle<SignalMast*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(signalMast->getDisplayName(), signalMast);
                action->setSignalMast(handle);
            } else {
                action->removeSignalMast();
            }
        } else {
            action->removeSignalMast();
        }

        if (!_exampleSignalMastBeanPanel->isEmpty()
                && (_tabbedPaneSignalMast->getSelectedComponent() != _panelSignalMastDirect)
                && (_tabbedPaneAspectType->getSelectedComponent() == _panelAspectTypeDirect)) {

            SignalMast* signalMast = (SignalMast*)_exampleSignalMastBeanPanel->getNamedBean()->self();
            if (signalMast != nullptr) {
                NamedBeanHandle<SignalMast*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(signalMast->getDisplayName(), signalMast);
                action->setExampleSignalMast(handle);
            }
        } else {
            action->removeExampleSignalMast();
        }

        try {
            if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
                action->setReference(_signalMastReferenceTextField->text());
            } else if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
                action->setLocalVariable(_signalMastLocalVariableTextField->text());
            } else if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
                action->setFormula(_signalMastFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneSignalMast has unknown selection");
            }

            if (_tabbedPaneOperationType->getSelectedComponent() == _panelOperationTypeDirect) {
                action->setOperationAddressing(NamedBeanAddressing::Direct);
                action->setOperationType((ActionSignalMast::OperationType::TYPE)_operationComboBox->getSelectedItem().toInt());
            } else if (_tabbedPaneOperationType->getSelectedComponent() == _panelOperationTypeReference) {
                action->setOperationAddressing(NamedBeanAddressing::Reference);
                action->setOperationReference(_signalMastOperationReferenceTextField->text());
            } else if (_tabbedPaneOperationType->getSelectedComponent() == _panelOperationTypeLocalVariable) {
                action->setOperationAddressing(NamedBeanAddressing::LocalVariable);
                action->setOperationLocalVariable(_signalMastOperationLocalVariableTextField->text());
            } else if (_tabbedPaneOperationType->getSelectedComponent() == _panelOperationTypeFormula) {
                action->setOperationAddressing(NamedBeanAddressing::Formula);
                action->setOperationFormula(_signalMastOperationFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneOperationType has unknown selection");
            }

            if (_tabbedPaneAspectType->getSelectedComponent() == _panelAspectTypeDirect) {
                action->setAspectAddressing(NamedBeanAddressing::Direct);

                if (_signalMastAspectComboBox->getItemCount() > 0) {
                    action->setAspect(_signalMastAspectComboBox
                            ->getItemAt(_signalMastAspectComboBox->getSelectedIndex()).toString());
                }
            } else if (_tabbedPaneAspectType->getSelectedComponent() == _panelAspectTypeReference) {
                action->setAspectAddressing(NamedBeanAddressing::Reference);
                action->setAspectReference(_signalMastAspectReferenceTextField->text());
            } else if (_tabbedPaneAspectType->getSelectedComponent() == _panelAspectTypeLocalVariable) {
                action->setAspectAddressing(NamedBeanAddressing::LocalVariable);
                action->setAspectLocalVariable(_signalMastAspectLocalVariableTextField->text());
            } else if (_tabbedPaneAspectType->getSelectedComponent() == _panelAspectTypeFormula) {
                action->setAspectAddressing(NamedBeanAddressing::Formula);
                action->setAspectFormula(_signalMastAspectFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneAspectType has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ActionSignalMastSwing::toString() {
        return tr("SignalMast");
    }

    //@Override
    /*public*/ void ActionSignalMastSwing::dispose() {
    }

