#include "expressionreporterswing.h"
#include "swingconfiguratorinterface.h"
#include "expressionreporter.h"
#include "jcheckbox.h"
#include "jcombobox.h"
#include "jtabbedpane.h"
#include "abstractreportermanager.h"
#include "instancemanager.h"
#include "beanselectpanel.h"
#include "jtextfield.h"
#include "abstractmemorymanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "abstractreporter.h"
#include "abstractmemory.h"

/**
 * Configures an ExpressionReporter object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 * @author Dave Sand Copyright 2021
 */
// /*public*/  class ExpressionReporterSwing extends AbstractDigitalExpressionSwing {

    /*private*/ void ExpressionReporterSwing::enableDisableCompareTo() {
        ExpressionReporter::ReporterOperation::RO mo = (ExpressionReporter::ReporterOperation::RO )_reporterOperationComboBox->getItemAt(
                        _reporterOperationComboBox->getSelectedIndex()).toInt();
        bool enable =ExpressionReporter::ReporterOperation::hasExtraValue(mo);
        _tabbedPaneCompareTo->setEnabled(enable);
        ((JPanel*)_tabbedPaneCompareTo->getSelectedComponent())
                ->getComponent(0)->setEnabled(enable);

        bool regEx = (mo == ExpressionReporter::ReporterOperation::MatchRegex)
                || (mo == ExpressionReporter::ReporterOperation::NotMatchRegex);
        _tabbedPane->setEnabledAt(0, !regEx);
        _tabbedPane->setEnabledAt(1, regEx);
        _tabbedPane->setSelectedIndex(regEx ? 1 : 0);
    }

    //@Override
    /*protected*/ void ExpressionReporterSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ExpressionReporter* expression = nullptr;
        if(object) expression =(ExpressionReporter*)object->bself();

        panel = new JPanel(new FlowLayout);

        _reporterBeanPanel = new BeanSelectPanel((AbstractReporterManager*)InstanceManager::getDefault("ReporterManager"), nullptr);

        _reporterValuePanel = new JPanel(new FlowLayout);
        _reporterValueComboBox = new JComboBox();
        for (ExpressionReporter::ReporterValue::RV e : ExpressionReporter::ReporterValue::values) {
            _reporterValueComboBox->addItem(ExpressionReporter::ReporterValue::toString(e), e);
        }
//        JComboBoxUtil.setupComboBoxMaxRows(_reporterValueComboBox);
        _reporterValuePanel->layout()->addWidget(_reporterValueComboBox);

        JPanel* operationAndCasePanel = new JPanel();
        operationAndCasePanel->setLayout(new QVBoxLayout());//operationAndCasePanel, BoxLayout.Y_AXIS));

        _reporterOperationComboBox = new JComboBox();
        for (ExpressionReporter::ReporterOperation::RO e : ExpressionReporter::ReporterOperation::values) {
            _reporterOperationComboBox->addItem(ExpressionReporter::ReporterOperation::toString(e),e);
        }
//        JComboBoxUtil.setupComboBoxMaxRows(_reporterOperationComboBox);
        if (expression == nullptr) {
            _reporterOperationComboBox->setSelectedItem(ExpressionReporter::ReporterOperation::Equal);
        }
        operationAndCasePanel->layout()->addWidget(_reporterOperationComboBox);

        connect(_reporterOperationComboBox, &JComboBox::currentTextChanged, [=] { enableDisableCompareTo(); });

        _caseInsensitiveCheckBox = new JCheckBox(tr("Case insensitive"));
        operationAndCasePanel->layout()->addWidget(_caseInsensitiveCheckBox);

        _tabbedPane = new JTabbedPane();

        _tabbedPaneCompareTo = new JTabbedPane();
        _tabbedPane->addTab("", _tabbedPaneCompareTo);

        _compareToConstant = new JPanel(new FlowLayout);
        _compareToMemory = new JPanel(new FlowLayout);
        _compareToLocalVariable = new JPanel(new FlowLayout);
        _compareToRegEx = new JPanel(new FlowLayout);

        _tabbedPaneCompareTo->addTab(ExpressionReporter::CompareTo::toString(ExpressionReporter::CompareTo::Value), _compareToConstant);
        _tabbedPaneCompareTo->addTab(ExpressionReporter::CompareTo::toString(ExpressionReporter::CompareTo::Memory), _compareToMemory);
        _tabbedPaneCompareTo->addTab(ExpressionReporter::CompareTo::toString(ExpressionReporter::CompareTo::LocalVariable), _compareToLocalVariable);

        _tabbedPane->addTab(ExpressionReporter::CompareTo::toString(ExpressionReporter::CompareTo::RegEx), _compareToRegEx);

        _compareToConstantTextField = new JTextField(30);
        _compareToConstant->layout()->addWidget(_compareToConstantTextField);

        _compareToMemoryBeanPanel = new BeanSelectPanel((AbstractMemoryManager*)InstanceManager::getDefault("MemoryManager"), nullptr);
        _compareToMemory->layout()->addWidget(_compareToMemoryBeanPanel);

        _compareToLocalVariableTextField = new JTextField(30);
        _compareToLocalVariable->layout()->addWidget(_compareToLocalVariableTextField);

        _compareToRegExTextField = new JTextField(30);
        _compareToRegEx->layout()->addWidget(_compareToRegExTextField);


        if (expression != nullptr) {
            if (expression->getReporter() != nullptr) {
                _reporterBeanPanel->setDefaultNamedBean((NamedBean*)expression->getReporter()->getBean());
            }
            if (expression->getMemory() != nullptr) {
                _compareToMemoryBeanPanel->setDefaultNamedBean(expression->getMemory()->getBean());
            }
            switch (expression->getCompareTo()) {
                case ExpressionReporter::CompareTo::RegEx:
                case ExpressionReporter::CompareTo::Value: _tabbedPaneCompareTo->setSelectedComponent(_compareToConstant); break;
                case ExpressionReporter::CompareTo::Memory: _tabbedPaneCompareTo->setSelectedComponent(_compareToMemory); break;
                case ExpressionReporter::CompareTo::LocalVariable: _tabbedPaneCompareTo->setSelectedComponent(_compareToLocalVariable); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + ExpressionReporter::CompareTo::toString(expression->getCompareTo()));
            }
            _reporterValueComboBox->setSelectedItem(expression->getReporterValue());
            _reporterOperationComboBox->setSelectedItem(expression->getReporterOperation());
            _caseInsensitiveCheckBox->setSelected(expression->getCaseInsensitive());
            _compareToConstantTextField->setText(expression->getConstantValue());
            _compareToLocalVariableTextField->setText(expression->getLocalVariable());
            _compareToRegExTextField->setText(expression->getRegEx());
        }

        //JComponent[] components = new JComponent[]{
        QList<QWidget*> components = {
            _reporterBeanPanel,
            _reporterValuePanel,
            operationAndCasePanel,
            _tabbedPane
        };
#if 0 // TODO:
        QList<QWidget*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Reporter %1 %2 %3 %4").arg(components.at(0),components.at(1),components.at(2),components.at(3)));

        for (QWidget* c : componentList) panel->layout()->addWidget(c);
#endif
        enableDisableCompareTo();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ExpressionReporterSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        if (_reporterBeanPanel->getNamedBean() == nullptr) {
            errorMessages->append(tr("A reporter was not selected"));
        }
        return errorMessages->isEmpty();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* ExpressionReporterSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ExpressionReporter* expression = new ExpressionReporter(systemName, userName);
        updateObject(expression);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionReporterSwing::updateObject(/*@Nonnull*/ Base* object) {
        //if (! (object instanceof ExpressionReporter)) {
        if(!object || !qobject_cast<ExpressionReporter*>(object->bself())){
            throw new IllegalArgumentException(QString("object must be an ExpressionReporter but is a: ")+ (object?object->bself()->metaObject()->className():"null"));
        }
        ExpressionReporter* expression = (ExpressionReporter*)object->bself();
        Reporter* reporter = (AbstractReporter*)_reporterBeanPanel->getNamedBean()->self();

        if (reporter != nullptr) {
            NamedBeanHandle<Reporter*>* handle
                    = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                            ->getNamedBeanHandle(reporter->getDisplayName(), reporter);
            expression->setReporter(handle);
        } else {
            expression->removeReporter();
        }

        expression->setReporterValue((ExpressionReporter::ReporterValue::RV)_reporterValueComboBox->getItemAt(_reporterValueComboBox->getSelectedIndex()).toUInt());
        expression->setReporterOperation((ExpressionReporter::ReporterOperation::RO)_reporterOperationComboBox->getItemAt(_reporterOperationComboBox->getSelectedIndex()).toInt());
        expression->setCaseInsensitive(_caseInsensitiveCheckBox->isSelected());


        if (!_compareToMemoryBeanPanel->isEmpty()
                && (_tabbedPane->getSelectedComponent() == _tabbedPaneCompareTo)
                && (_tabbedPaneCompareTo->getSelectedComponent() == _compareToMemory)) {
            Memory* memory = (AbstractMemory*)_compareToMemoryBeanPanel->getNamedBean()->self();
            if (memory != nullptr) {
                NamedBeanHandle<Memory*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(memory->getDisplayName(), memory);
                expression->setMemory(handle);
            } else {
                expression->removeMemory();
            }
        } else {
            expression->removeMemory();
        }

        if (_tabbedPane->getSelectedComponent() == _tabbedPaneCompareTo) {
            if (_tabbedPaneCompareTo->getSelectedComponent() == _compareToConstant) {
                expression->setCompareTo(ExpressionReporter::CompareTo::Value);
                expression->setConstantValue(_compareToConstantTextField->text());
            } else if (_tabbedPaneCompareTo->getSelectedComponent() == _compareToMemory) {
                expression->setCompareTo(ExpressionReporter::CompareTo::Memory);
            } else if (_tabbedPaneCompareTo->getSelectedComponent() == _compareToLocalVariable) {
                expression->setCompareTo(ExpressionReporter::CompareTo::LocalVariable);
                expression->setLocalVariable(_compareToLocalVariableTextField->text());
//            } else if (_tabbedPaneCompareTo.getSelectedComponent() == _compareToRegEx) {
//                expression.setCompareTo(CompareTo.RegEx);
//                expression.setRegEx(_compareToRegExTextField.getText());
            } else {
                throw new IllegalArgumentException("_tabbedPaneLight has unknown selection");
            }
        } else {
            expression->setCompareTo(ExpressionReporter::CompareTo::RegEx);
            expression->setRegEx(_compareToRegExTextField->text());
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ExpressionReporterSwing::toString() {
        return tr("Reporte");
    }

    //@Override
    /*public*/  void ExpressionReporterSwing::dispose() {
    }
