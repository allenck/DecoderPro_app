#include "expressionsignalheadswing.h"
#include "expressionsignalhead.h"
#include "beanselectpanel.h"
#include "borderfactory.h"
#include "abstractsignalheadmanager.h"
#include "instancemanager.h"
#include "jtabbedpane.h"
#include "jtextfield.h"
#include "swingconfiguratorinterface.h"
#include "parserexception.h"
#include "defaultdigitalexpressionmanager.h"
#include "vptr.h"

ExpressionSignalHeadSwing::ExpressionSignalHeadSwing(QObject *parent) : AbstractDigitalExpressionSwing(parent)
{
 setObjectName("ExpressionSignalHeadSwing");
}
/**
 * Configures an ExpressionSignalHead object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class ExpressionSignalHeadSwing extends AbstractDigitalExpressionSwing {

    /*public*/  /*static*/ /*final*/ int ExpressionSignalHeadSwing::NUM_COLUMNS_TEXT_FIELDS = 20;



    //@Override
    /*protected*/ void ExpressionSignalHeadSwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ExpressionSignalHead* expression = nullptr;
        if(object) expression = (ExpressionSignalHead*)object->bself();

        panel = new JPanel();
        panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));

        JPanel* examplePanel = new JPanel(new FlowLayout());
        JPanel* innerExamplePanel = new JPanel(new FlowLayout());
        innerExamplePanel->setBorder(BorderFactory::createLineBorder(Qt::black));
        _exampleSignalHeadBeanPanel = new BeanSelectPanel((AbstractManager*)InstanceManager::getDefault("SignalHeadManager"), nullptr);
        innerExamplePanel->layout()->addWidget(_exampleSignalHeadBeanPanel);

        connect(_exampleSignalHeadBeanPanel->getBeanCombo(), &JComboBox::currentIndexChanged, [=] {
            setAppearanceComboBox(nullptr);
        });


        JPanel* expressionPanel = new JPanel(new FlowLayout());


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

        _signalHeadBeanPanel =  new BeanSelectPanel((AbstractManager*)InstanceManager::getDefault("SignalHeadManager"), nullptr);
        _panelSignalHeadDirect->layout()->addWidget(_signalHeadBeanPanel);

        connect(_signalHeadBeanPanel->getBeanCombo(), &JComboBox::currentIndexChanged, [=] {
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
        _tabbedPaneQueryType = new JTabbedPane();
        _panelQueryTypeDirect = new JPanel(new FlowLayout());
        _panelQueryTypeDirect->setLayout(new QVBoxLayout());//_panelQueryTypeDirect, BoxLayout.Y_AXIS));
        _panelQueryTypeReference = new JPanel(new FlowLayout());
        _panelQueryTypeReference->setLayout(new QVBoxLayout());//_panelQueryTypeReference, BoxLayout.Y_AXIS));
        _panelQueryTypeLocalVariable = new JPanel(new FlowLayout());
        _panelQueryTypeLocalVariable->setLayout(new QVBoxLayout());//_panelQueryTypeLocalVariable, BoxLayout.Y_AXIS));
        _panelQueryTypeFormula = new JPanel(new FlowLayout());
        _panelQueryTypeFormula->setLayout(new QVBoxLayout());//_panelQueryTypeFormula, BoxLayout.Y_AXIS));

        _tabbedPaneQueryType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelQueryTypeDirect);
        _tabbedPaneQueryType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelQueryTypeReference);
        _tabbedPaneQueryType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelQueryTypeLocalVariable);
        _tabbedPaneQueryType->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelQueryTypeFormula);

        connect(_tabbedPaneQueryType, &JTabbedPane::currentChanged, [=]{
            setGuiEnabledStates();
        });

        _operationComboBox = new JComboBox();
        for (ExpressionSignalHead::QueryType::TYPE e : ExpressionSignalHead::QueryType::values()) {
            _operationComboBox->addItem(ExpressionSignalHead::QueryType::toString(e),e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_operationComboBox);

        connect(_operationComboBox, &JComboBox::currentIndexChanged, [=] {
            setGuiEnabledStates();
        });

        _panelQueryTypeDirect->layout()->addWidget(new JLabel(tr("Query")));
        _panelQueryTypeDirect->layout()->addWidget(_operationComboBox);

        _signalHeadQueryReferenceTextField = new JTextField();
        _signalHeadQueryReferenceTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelQueryTypeReference->layout()->addWidget(new JLabel(tr("Query")));
        _panelQueryTypeReference->layout()->addWidget(_signalHeadQueryReferenceTextField);

        _signalHeadQueryLocalVariableTextField = new JTextField();
        _signalHeadQueryLocalVariableTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelQueryTypeLocalVariable->layout()->addWidget(new JLabel(tr("Query")));
        _panelQueryTypeLocalVariable->layout()->addWidget(_signalHeadQueryLocalVariableTextField);

        _signalHeadQueryFormulaTextField = new JTextField();
        _signalHeadQueryFormulaTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelQueryTypeFormula->layout()->addWidget(new JLabel(tr("Query")));
        _panelQueryTypeFormula->layout()->addWidget(_signalHeadQueryFormulaTextField);


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

        connect(_tabbedPaneAppearanceType, &JTabbedPane::currentChanged, [=]{
            setGuiEnabledStates();
        });

        _signalHeadAppearanceComboBox = new JComboBox();
        _panelAppearanceTypeDirect->layout()->addWidget(new JLabel(tr("Appearence")));
        _panelAppearanceTypeDirect->layout()->addWidget(_signalHeadAppearanceComboBox);

        _signalHeadAppearanceReferenceTextField = new JTextField();
        _signalHeadAppearanceReferenceTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelAppearanceTypeReference->layout()->addWidget(new JLabel(tr("Appearence")));
        _panelAppearanceTypeReference->layout()->addWidget(_signalHeadAppearanceReferenceTextField);

        _signalHeadAppearanceLocalVariableTextField = new JTextField();
        _signalHeadAppearanceLocalVariableTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelAppearanceTypeLocalVariable->layout()->addWidget(new JLabel(tr("Appearence")));
        _panelAppearanceTypeLocalVariable->layout()->addWidget(_signalHeadAppearanceLocalVariableTextField);

        _signalHeadAppearanceFormulaTextField = new JTextField();
        _signalHeadAppearanceFormulaTextField->setColumns(NUM_COLUMNS_TEXT_FIELDS);
        _panelAppearanceTypeFormula->layout()->addWidget(new JLabel(tr("Appearence")));
        _panelAppearanceTypeFormula->layout()->addWidget(_signalHeadAppearanceFormulaTextField);


        JPanel* notePanel = new JPanel(new FlowLayout());
        notePanel->setBorder(BorderFactory::createMatteBorder(1, 0, 0, 0, Qt::white));
        examplePanel->setBorder(BorderFactory::createMatteBorder(0, 0, 1, 0, Qt::white));

        JLabel* noteLabel = new JLabel(tr("<html> \
If you do not use Direct addressing of the signal %1 but are using Direct addressing<br> \
of the %2, you need to select an example signal %1. The example signal %1 is<br> \
used to tell JMRI which %2 the indirect addressed signal %1 may show.</html>").arg(
                tr("head"),
                tr("appearences")));
        notePanel->layout()->addWidget(noteLabel);


        examplePanel->layout()->addWidget(new JLabel(tr("Example Bean")));
        examplePanel->layout()->addWidget(innerExamplePanel);


        if (expression != nullptr) {
            switch (expression->getAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneSignalHead->setSelectedComponent(_panelSignalHeadDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneSignalHead->setSelectedComponent(_panelSignalHeadReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneSignalHead->setSelectedComponent(_panelSignalHeadLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneSignalHead->setSelectedComponent(_panelSignalHeadFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getAddressing()));
            }
            if (expression->getSignalHead() != nullptr) {
                _signalHeadBeanPanel->setDefaultNamedBean(expression->getSignalHead()->getBean());
            }
            if (expression->getExampleSignalHead() != nullptr) {
                _exampleSignalHeadBeanPanel->setDefaultNamedBean(expression->getExampleSignalHead()->getBean());
            }
            _signalHeadReferenceTextField->setText(expression->getReference());
            _signalHeadLocalVariableTextField->setText(expression->getLocalVariable());
            _signalHeadFormulaTextField->setText(expression->getFormula());


            switch (expression->getQueryAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneQueryType->setSelectedComponent(_panelQueryTypeDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneQueryType->setSelectedComponent(_panelQueryTypeReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneQueryType->setSelectedComponent(_panelQueryTypeLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneQueryType->setSelectedComponent(_panelQueryTypeFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getQueryAddressing()));
            }
            _operationComboBox->setSelectedItem(expression->getQueryType());
            _signalHeadQueryReferenceTextField->setText(expression->getQueryReference());
            _signalHeadQueryLocalVariableTextField->setText(expression->getQueryLocalVariable());
            _signalHeadQueryFormulaTextField->setText(expression->getQueryFormula());


            switch (expression->getAppearanceAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneAppearanceType->setSelectedComponent(_panelAppearanceTypeDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneAppearanceType->setSelectedComponent(_panelAppearanceTypeReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneAppearanceType->setSelectedComponent(_panelAppearanceTypeLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneAppearanceType->setSelectedComponent(_panelAppearanceTypeFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(expression->getAppearanceAddressing()));
            }
            _signalHeadAppearanceReferenceTextField->setText(expression->getAppearanceReference());
            _signalHeadAppearanceLocalVariableTextField->setText(expression->getAppearanceLocalVariable());
            _signalHeadAppearanceFormulaTextField->setText(expression->getAppearanceFormula());
#if 0
            jmri.util.ThreadingUtil.runOnGUIEventually(() -> { setAppearanceComboBox(expression); });
#endif
        }

        QList<JComponent*> components = QList<JComponent*>{
            _tabbedPaneSignalHead,
            _tabbedPaneQueryType,
            _tabbedPaneAppearanceType
        };

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Set signal head %1 to %2 %3"), components);

        for (JComponent* c : componentList) expressionPanel->layout()->addWidget(c->jself());

        panel->layout()->addWidget(expressionPanel);
        panel->layout()->addWidget(notePanel);
        panel->layout()->addWidget(examplePanel);

        setGuiEnabledStates();
    }


    /*private*/ void ExpressionSignalHeadSwing::setGuiEnabledStates() {
        _tabbedPaneAppearanceType->QWidget::setEnabled(false);
        _signalHeadAppearanceComboBox->setEnabled(false);
        _signalHeadAppearanceReferenceTextField->setEnabled(false);
        _signalHeadAppearanceLocalVariableTextField->setEnabled(false);
        _signalHeadAppearanceFormulaTextField->setEnabled(false);
        _exampleSignalHeadBeanPanel->getBeanCombo()->setEnabled(false);

        if (_tabbedPaneQueryType->getSelectedComponent() == _panelQueryTypeDirect &&
                _operationComboBox->getSelectedItem() != ExpressionSignalHead::QueryType::Appearance &&
                _operationComboBox->getSelectedItem() != ExpressionSignalHead::QueryType::NotAppearance) {
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

    /*private*/ void ExpressionSignalHeadSwing::setAppearanceComboBox(ExpressionSignalHead* expression) {
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
                if (expression != nullptr) {
                    if (expression->getAppearance() == s) _signalHeadAppearanceComboBox->setSelectedItem(sha->_name);
                }
            }
//            JComboBoxUtil->setupComboBoxMaxRows(_signalHeadAppearanceComboBox);
        }
    }


    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ExpressionSignalHeadSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary expression to test formula
        ExpressionSignalHead* expression = new ExpressionSignalHead("IQDE1", "");

        try {
            if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadReference) {
                expression->setReference(_signalHeadReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            if (_tabbedPaneQueryType->getSelectedComponent() == _panelQueryTypeReference) {
                expression->setQueryReference(_signalHeadQueryReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            expression->setFormula(_signalHeadFormulaTextField->text());
            if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadDirect) {
                expression->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadReference) {
                expression->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadLocalVariable) {
                expression->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadFormula) {
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
    /*public*/  MaleSocket* ExpressionSignalHeadSwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        ExpressionSignalHead* expression = new ExpressionSignalHead(systemName, userName);
        updateObject(expression);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionSignalHeadSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ExpressionSignalHead*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ExpressionSignalHead but is a: ")+object->bself()->metaObject()->className());
        }
        ExpressionSignalHead* expression = (ExpressionSignalHead*)object->bself();
        if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadDirect) {
            SignalHead* signalHead = (SignalHead*)_signalHeadBeanPanel->getNamedBean()->self();
            if (signalHead != nullptr) {
                NamedBeanHandle<SignalHead*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(signalHead->getDisplayName(), signalHead);
                expression->setSignalHead(handle);
            } else {
                expression->removeSignalHead();
            }
        } else {
            expression->removeSignalHead();
        }

        if (!_exampleSignalHeadBeanPanel->isEmpty()
                && (_tabbedPaneSignalHead->getSelectedComponent() != _panelSignalHeadDirect)
                && (_tabbedPaneAppearanceType->getSelectedComponent() == _panelAppearanceTypeDirect)) {

            SignalHead* signalHead = (SignalHead*)_exampleSignalHeadBeanPanel->getNamedBean()->self();
            if (signalHead != nullptr) {
                NamedBeanHandle<SignalHead*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(signalHead->getDisplayName(), signalHead);
                expression->setExampleSignalHead(handle);
            }
        } else {
            expression->removeExampleSignalHead();
        }

        try {
            if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadDirect) {
                expression->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadReference) {
                expression->setAddressing(NamedBeanAddressing::Reference);
                expression->setReference(_signalHeadReferenceTextField->text());
            } else if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadLocalVariable) {
                expression->setAddressing(NamedBeanAddressing::LocalVariable);
                expression->setLocalVariable(_signalHeadLocalVariableTextField->text());
            } else if (_tabbedPaneSignalHead->getSelectedComponent() == _panelSignalHeadFormula) {
                expression->setAddressing(NamedBeanAddressing::Formula);
                expression->setFormula(_signalHeadFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneSignalHead has unknown selection");
            }

            if (_tabbedPaneQueryType->getSelectedComponent() == _panelQueryTypeDirect) {
                expression->setQueryAddressing(NamedBeanAddressing::Direct);
                expression->setQueryType((ExpressionSignalHead::QueryType::TYPE)_operationComboBox->getSelectedItem().toInt());
            } else if (_tabbedPaneQueryType->getSelectedComponent() == _panelQueryTypeReference) {
                expression->setQueryAddressing(NamedBeanAddressing::Reference);
                expression->setQueryReference(_signalHeadQueryReferenceTextField->text());
            } else if (_tabbedPaneQueryType->getSelectedComponent() == _panelQueryTypeLocalVariable) {
                expression->setQueryAddressing(NamedBeanAddressing::LocalVariable);
                expression->setQueryLocalVariable(_signalHeadQueryLocalVariableTextField->text());
            } else if (_tabbedPaneQueryType->getSelectedComponent() == _panelQueryTypeFormula) {
                expression->setQueryAddressing(NamedBeanAddressing::Formula);
                expression->setQueryFormula(_signalHeadQueryFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneQueryType has unknown selection");
            }

            if (_tabbedPaneAppearanceType->getSelectedComponent() == _panelAppearanceTypeDirect) {
                expression->setAppearanceAddressing(NamedBeanAddressing::Direct);

                if (_signalHeadAppearanceComboBox->getItemCount() > 0) {
                    expression->setAppearance(VPtr<SignalHeadAppearance>::asPtr(_signalHeadAppearanceComboBox
                            ->getItemAt(_signalHeadAppearanceComboBox->getSelectedIndex()))->_state);
                }
            } else if (_tabbedPaneAppearanceType->getSelectedComponent() == _panelAppearanceTypeReference) {
                expression->setAppearanceAddressing(NamedBeanAddressing::Reference);
                expression->setAppearanceReference(_signalHeadAppearanceReferenceTextField->text());
            } else if (_tabbedPaneAppearanceType->getSelectedComponent() == _panelAppearanceTypeLocalVariable) {
                expression->setAppearanceAddressing(NamedBeanAddressing::LocalVariable);
                expression->setAppearanceLocalVariable(_signalHeadAppearanceLocalVariableTextField->text());
            } else if (_tabbedPaneAppearanceType->getSelectedComponent() == _panelAppearanceTypeFormula) {
                expression->setAppearanceAddressing(NamedBeanAddressing::Formula);
                expression->setAppearanceFormula(_signalHeadAppearanceFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneAppearanceType has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ExpressionSignalHeadSwing::toString() {
        return tr("SignalHead");
    }

    //@Override
    /*public*/  void ExpressionSignalHeadSwing::dispose() {
    }


