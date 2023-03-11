#include "expressionsignalmastswing.h"
#include "beanselectpanel.h"
#include "defaultsignalmastmanager.h"
#include "jcombobox.h"
#include "jtabbedpane.h"
#include "logixng/defaultdigitalexpressionmanager.h"
#include "logixng/expressionsignalmast.h"
#include "borderfactory.h"
#include "jlabel.h"
#include "instancemanager.h"
#include "jtextfield.h"
#include "swingconfiguratorinterface.h"
#include "vptr.h"
#include "parserexception.h"

ExpressionSignalMastSwing::ExpressionSignalMastSwing(QObject *parent)
    : AbstractDigitalExpressionSwing{parent}
{

}
/**
 * Configures an ExpressionSignalMast object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class ExpressionSignalMastSwing extends AbstractDigitalExpressionSwing {

    /*public*/ /*static*/ /*final*/ int ExpressionSignalMastSwing::NUM_COLUMNS_TEXT_FIELDS = 20;



    //@Override
    /*protected*/ void ExpressionSignalMastSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ExpressionSignalMast* expression = nullptr;
        if(object) expression = (ExpressionSignalMast*)object->bself();

        panel = new JPanel();
        panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));

        JPanel* examplePanel = new JPanel(new FlowLayout);
        JPanel* innerExamplePanel = new JPanel(new FlowLayout);
        innerExamplePanel->setBorder(BorderFactory::createLineBorder(Qt::black));
        _exampleSignalMastBeanPanel = new BeanSelectPanel((DefaultSignalMastManager*)InstanceManager::getDefault("SignalMastManager"), nullptr);
        innerExamplePanel->layout()->addWidget(_exampleSignalMastBeanPanel);

        //_exampleSignalMastBeanPanel->getBeanCombo().addActionListener((java.awt.event.ActionEvent e) -> {
        connect(_exampleSignalMastBeanPanel->getBeanCombo(), &JComboBox::currentTextChanged, [=]{
            setAspectComboBox(nullptr);
        });


        JPanel* expressionPanel = new JPanel(new FlowLayout);


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
        connect(_signalMastBeanPanel->getBeanCombo(), &JComboBox::currentTextChanged, [=]{
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
        _tabbedPaneQueryType = new JTabbedPane();
        _panelQueryTypeDirect = new JPanel();
        _panelQueryTypeDirect->setLayout(new QVBoxLayout());//_panelQueryTypeDirect, BoxLayout.Y_AXIS));
        _panelQueryTypeReference = new JPanel();
        _panelQueryTypeReference->setLayout(new QVBoxLayout());//_panelQueryTypeReference, BoxLayout.Y_AXIS));
        _panelQueryTypeLocalVariable = new JPanel();
        _panelQueryTypeLocalVariable->setLayout(new QVBoxLayout());//_panelQueryTypeLocalVariable, BoxLayout.Y_AXIS));
        _panelQueryTypeFormula = new JPanel();
        _panelQueryTypeFormula->setLayout(new QVBoxLayout());//_panelQueryTypeFormula, BoxLayout.Y_AXIS));

        _tabbedPaneQueryType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelQueryTypeDirect);
        _tabbedPaneQueryType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelQueryTypeReference);
        _tabbedPaneQueryType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelQueryTypeLocalVariable);
        _tabbedPaneQueryType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelQueryTypeFormula);

        //_tabbedPaneQueryType.addChangeListener((ChangeEvent e) -> {
        connect(_tabbedPaneQueryType, &JTabbedPane::currentChanged, [=]{
            setGuiEnabledStates();
        });

        _operationComboBox = new JComboBox();
        for (ExpressionSignalMast::QueryType::TYPE e : ExpressionSignalMast::QueryType::values()) {
            _operationComboBox->addItem(ExpressionSignalMast::QueryType::toString(e), e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_operationComboBox);

        //_operationComboBox.addActionListener(e -> {
        connect(_operationComboBox, &JComboBox::currentTextChanged, [=]{
            setGuiEnabledStates();
        });

        _panelQueryTypeDirect->layout()->addWidget(new JLabel(tr("ExpressionSignalMast_Query")));
        _panelQueryTypeDirect->layout()->addWidget(_operationComboBox);

        _signalMastQueryReferenceTextField = new JTextField();
        _signalMastQueryReferenceTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelQueryTypeReference->layout()->addWidget(new JLabel(tr("ExpressionSignalMast_Query")));
        _panelQueryTypeReference->layout()->addWidget(_signalMastQueryReferenceTextField);

        _signalMastQueryLocalVariableTextField = new JTextField();
        _signalMastQueryLocalVariableTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelQueryTypeLocalVariable->layout()->addWidget(new JLabel(tr("ExpressionSignalMast_Query")));
        _panelQueryTypeLocalVariable->layout()->addWidget(_signalMastQueryLocalVariableTextField);

        _signalMastQueryFormulaTextField = new JTextField();
        _signalMastQueryFormulaTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelQueryTypeFormula->layout()->addWidget(new JLabel(tr("ExpressionSignalMast_Query")));
        _panelQueryTypeFormula->layout()->addWidget(_signalMastQueryFormulaTextField);


        // Set up the tabbed pane for selecting the aspect
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
        _panelAspectTypeDirect->layout()->addWidget(new JLabel(tr("Aspect")));
        _panelAspectTypeDirect->layout()->addWidget(_signalMastAspectComboBox);

        _signalMastAspectReferenceTextField = new JTextField();
        _signalMastAspectReferenceTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelAspectTypeReference->layout()->addWidget(new JLabel(tr("Aspect")));
        _panelAspectTypeReference->layout()->addWidget(_signalMastAspectReferenceTextField);

        _signalMastAspectLocalVariableTextField = new JTextField();
        _signalMastAspectLocalVariableTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelAspectTypeLocalVariable->layout()->addWidget(new JLabel(tr("Aspect")));
        _panelAspectTypeLocalVariable->layout()->addWidget(_signalMastAspectLocalVariableTextField);

        _signalMastAspectFormulaTextField = new JTextField();
        _signalMastAspectFormulaTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelAspectTypeFormula->layout()->addWidget(new JLabel(tr("Aspect")));
        _panelAspectTypeFormula->layout()->addWidget(_signalMastAspectFormulaTextField);


        JPanel* notePanel = new JPanel(new FlowLayout);
        notePanel->setBorder(BorderFactory::createMatteBorder(1, 0, 0, 0, Qt::white));
        examplePanel->setBorder(BorderFactory::createMatteBorder(0, 0, 1, 0, Qt::white));

        JLabel* noteLabel = new JLabel(tr("<html> \
                                          If you do not use Direct addressing of the signal %1 but are using Direct addressing<br> \
                                          of the %2, you need to select an example signal %1}. The example signal %1 is<br> \
                                          used to tell JMRI which %2 the indirect addressed signal %1 may show.</html>").arg(
                tr("mast"),
                tr("aspects")));
        notePanel->layout()->addWidget(noteLabel);


        examplePanel->layout()->addWidget(new JLabel(tr("Example signal mast")));
        examplePanel->layout()->addWidget(innerExamplePanel);


        if (expression != nullptr) {
            switch (expression->getAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneSignalMast->setSelectedComponent(_panelSignalMastDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneSignalMast->setSelectedComponent(_panelSignalMastReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneSignalMast->setSelectedComponent(_panelSignalMastLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneSignalMast->setSelectedComponent(_panelSignalMastFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getAddressing()));
            }
            if (expression->getSignalMast() != nullptr) {
                _signalMastBeanPanel->setDefaultNamedBean(expression->getSignalMast()->getBean());
            }
            if (expression->getExampleSignalMast() != nullptr) {
                _exampleSignalMastBeanPanel->setDefaultNamedBean(expression->getExampleSignalMast()->getBean());
            }
            _signalMastReferenceTextField->setText(expression->getReference());
            _signalMastLocalVariableTextField->setText(expression->getLocalVariable());
            _signalMastFormulaTextField->setText(expression->getFormula());


            switch (expression->getQueryAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneQueryType->setSelectedComponent(_panelQueryTypeDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneQueryType->setSelectedComponent(_panelQueryTypeReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneQueryType->setSelectedComponent(_panelQueryTypeLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneQueryType->setSelectedComponent(_panelQueryTypeFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getQueryAddressing()));
            }
            _operationComboBox->setSelectedItem(expression->getQueryType());
            _signalMastQueryReferenceTextField->setText(expression->getQueryReference());
            _signalMastQueryLocalVariableTextField->setText(expression->getQueryLocalVariable());
            _signalMastQueryFormulaTextField->setText(expression->getQueryFormula());



            switch (expression->getAspectAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneAspectType->setSelectedComponent(_panelAspectTypeDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneAspectType->setSelectedComponent(_panelAspectTypeReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneAspectType->setSelectedComponent(_panelAspectTypeLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneAspectType->setSelectedComponent(_panelAspectTypeFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getAspectAddressing()));
            }
            _signalMastAspectReferenceTextField->setText(expression->getAspectReference());
            _signalMastAspectLocalVariableTextField->setText(expression->getAspectLocalVariable());
            _signalMastAspectFormulaTextField->setText(expression->getAspectFormula());

 //           ThreadingUtil::runOnGUIEventually(() -> { setAspectComboBox(expression); });
            ThreadingUtil::runOnGUIEventually(new ESMS_ThreadingUtil( expression, this));
        }

        QList<JComponent*> components = {
            _tabbedPaneSignalMast,
            _tabbedPaneQueryType,
            _tabbedPaneAspectType
        };

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Set signal mast {0} to {1} {2}"),
                    components);

        for (JComponent* c : componentList) expressionPanel->layout()->addWidget((QWidget*)c->jself());

        panel->layout()->addWidget(expressionPanel);
        panel->layout()->addWidget(notePanel);
        panel->layout()->addWidget(examplePanel);

        setGuiEnabledStates();
    }


    /*private*/ void ExpressionSignalMastSwing::setGuiEnabledStates() {
        _tabbedPaneAspectType->setEnabled(false);
        _signalMastAspectComboBox->setEnabled(false);
        _signalMastAspectReferenceTextField->setEnabled(false);
        _signalMastAspectLocalVariableTextField->setEnabled(false);
        _signalMastAspectFormulaTextField->setEnabled(false);
        _exampleSignalMastBeanPanel->getBeanCombo()->setEnabled(false);

        if (_tabbedPaneQueryType->getSelectedComponent() == _panelQueryTypeDirect &&
                _operationComboBox->getSelectedItem() != ExpressionSignalMast::QueryType::Aspect &&
                _operationComboBox->getSelectedItem() != ExpressionSignalMast::QueryType::NotAspect) {
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

    /*private*/ void ExpressionSignalMastSwing::setAspectComboBox(ExpressionSignalMast* expression) {
        SignalMast* sm;
        if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastDirect) {
            sm = (SignalMast*) _signalMastBeanPanel->getBeanCombo()->getSelectedItem()->self();
        } else {
            sm = (SignalMast*) _exampleSignalMastBeanPanel->getBeanCombo()->getSelectedItem()->self();
        }

        if (sm != nullptr) {
            _signalMastAspectComboBox->clear();
            for (QString aspect : sm->getValidAspects()) {
                _signalMastAspectComboBox->addItem(aspect);
                if (expression != nullptr) {
                    if (aspect == (expression->getAspect())) _signalMastAspectComboBox->setSelectedItem(aspect);
                }
            }
//            JComboBoxUtil->setupComboBoxMaxRows(_signalMastAspectComboBox);
        }
    }


    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ExpressionSignalMastSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary expression to test formula
        ExpressionSignalMast* expression = new ExpressionSignalMast("IQDE1", "");

        try {
            if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastReference) {
                expression->setReference(_signalMastReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            if (_tabbedPaneQueryType->getSelectedComponent() == _panelQueryTypeReference) {
                expression->setQueryReference(_signalMastQueryReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            expression->setFormula(_signalMastFormulaTextField->text());
            if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastDirect) {
                expression->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastReference) {
                expression->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastLocalVariable) {
                expression->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastFormula) {
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
    /*public*/ MaleSocket* ExpressionSignalMastSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ExpressionSignalMast* expression = new ExpressionSignalMast(systemName, userName);
        updateObject(expression);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionSignalMastSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast< ExpressionSignalMast*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ExpressionSignalMast but is a: ")+object->bself()->metaObject()->className());
        }
        ExpressionSignalMast* expression = nullptr;
        if(object) expression =(ExpressionSignalMast*)object->bself();
        if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastDirect) {
            SignalMast* signalMast = (SignalMast*)_signalMastBeanPanel->getNamedBean()->self();
            if (signalMast != nullptr) {
                NamedBeanHandle<SignalMast*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(signalMast->getDisplayName(), signalMast);
                expression->setSignalMast(handle);
            } else {
                expression->removeSignalMast();
            }
        } else {
            expression->removeSignalMast();
        }

        if (!_exampleSignalMastBeanPanel->isEmpty()
                && (_tabbedPaneSignalMast->getSelectedComponent() != _panelSignalMastDirect)
                && (_tabbedPaneAspectType->getSelectedComponent() == _panelAspectTypeDirect)) {

            SignalMast* signalMast = (SignalMast*)_exampleSignalMastBeanPanel->getNamedBean()->self();
            if (signalMast != nullptr) {
                NamedBeanHandle<SignalMast*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(signalMast->getDisplayName(), signalMast);
                expression->setExampleSignalMast(handle);
            }
        } else {
            expression->removeExampleSignalMast();
        }

        try {
            if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastDirect) {
                expression->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastReference) {
                expression->setAddressing(NamedBeanAddressing::Reference);
                expression->setReference(_signalMastReferenceTextField->text());
            } else if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastLocalVariable) {
                expression->setAddressing(NamedBeanAddressing::LocalVariable);
                expression->setLocalVariable(_signalMastLocalVariableTextField->text());
            } else if (_tabbedPaneSignalMast->getSelectedComponent() == _panelSignalMastFormula) {
                expression->setAddressing(NamedBeanAddressing::Formula);
                expression->setFormula(_signalMastFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneSignalMast has unknown selection");
            }

            if (_tabbedPaneQueryType->getSelectedComponent() == _panelQueryTypeDirect) {
                expression->setQueryAddressing(NamedBeanAddressing::Direct);
                expression->setQueryType((ExpressionSignalMast::QueryType::TYPE)_operationComboBox->getSelectedItem().toInt());
            } else if (_tabbedPaneQueryType->getSelectedComponent() == _panelQueryTypeReference) {
                expression->setQueryAddressing(NamedBeanAddressing::Reference);
                expression->setQueryReference(_signalMastQueryReferenceTextField->text());
            } else if (_tabbedPaneQueryType->getSelectedComponent() == _panelQueryTypeLocalVariable) {
                expression->setQueryAddressing(NamedBeanAddressing::LocalVariable);
                expression->setQueryLocalVariable(_signalMastQueryLocalVariableTextField->text());
            } else if (_tabbedPaneQueryType->getSelectedComponent() == _panelQueryTypeFormula) {
                expression->setQueryAddressing(NamedBeanAddressing::Formula);
                expression->setQueryFormula(_signalMastQueryFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneQueryType has unknown selection");
            }

            if (_tabbedPaneAspectType->getSelectedComponent() == _panelAspectTypeDirect) {
                expression->setAspectAddressing(NamedBeanAddressing::Direct);

                if (_signalMastAspectComboBox->getItemCount() > 0) {
                    expression->setAspect(_signalMastAspectComboBox
                            ->itemText(_signalMastAspectComboBox->getSelectedIndex()));
                }
            } else if (_tabbedPaneAspectType->getSelectedComponent() == _panelAspectTypeReference) {
                expression->setAspectAddressing(NamedBeanAddressing::Reference);
                expression->setAspectReference(_signalMastAspectReferenceTextField->text());
            } else if (_tabbedPaneAspectType->getSelectedComponent() == _panelAspectTypeLocalVariable) {
                expression->setAspectAddressing(NamedBeanAddressing::LocalVariable);
                expression->setAspectLocalVariable(_signalMastAspectLocalVariableTextField->text());
            } else if (_tabbedPaneAspectType->getSelectedComponent() == _panelAspectTypeFormula) {
                expression->setAspectAddressing(NamedBeanAddressing::Formula);
                expression->setAspectFormula(_signalMastAspectFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneAspectType has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ExpressionSignalMastSwing::toString() {
        return tr("SignalMast");
    }

    //@Override
    /*public*/ void ExpressionSignalMastSwing::dispose() {
    }

