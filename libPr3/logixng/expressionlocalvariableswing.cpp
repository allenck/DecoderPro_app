#include "expressionlocalvariableswing.h"
#include "expressionlocalvariable.h"
#include "vptr.h"
#include "jtabbedpane.h"
#include "jcombobox.h"
#include "jtabbedpane.h"
#include "instancemanager.h"
#include "jtextfield.h"
#include "swingconfiguratorinterface.h"
#include "defaultdigitalexpressionmanager.h"
#include "instancemanager.h"
#include "jcheckbox.h"
#include "abstractmemorymanager.h"
#include "beanselectpanel.h"

ExpressionLocalVariableSwing::ExpressionLocalVariableSwing(QObject *parent) : AbstractDigitalExpressionSwing(parent)
{
 setObjectName("ExpressionLocalVariableSwing");
}
/**
 * Configures an ExpressionLocalVariable object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class ExpressionLocalVariableSwing extends AbstractDigitalExpressionSwing {




    /*private*/ void ExpressionLocalVariableSwing::enableDisableCompareTo() {
        ExpressionLocalVariable::VariableOperation::TYPE vo = (ExpressionLocalVariable::VariableOperation::TYPE)_variableOperationComboBox->getItemAt(
                        _variableOperationComboBox->getSelectedIndex()).toInt();
        bool enable = ExpressionLocalVariable::VariableOperation::hasExtraValue(vo);
        _tabbedPaneCompareTo->QWidget::setEnabled(enable);
        ((JPanel*)_tabbedPaneCompareTo->getSelectedComponent())
                ->getComponent(0)->setEnabled(enable);

        bool regEx = (vo == ExpressionLocalVariable::VariableOperation::MatchRegex)
                || (vo == ExpressionLocalVariable::VariableOperation::NotMatchRegex);
        _tabbedPane->setEnabledAt(0, !regEx);
        _tabbedPane->setEnabledAt(1, regEx);
        _tabbedPane->setSelectedIndex(regEx ? 1 : 0);
    }

    //@Override
    /*protected*/ void ExpressionLocalVariableSwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ExpressionLocalVariable* expression = nullptr;
        if(object) expression = (ExpressionLocalVariable*)object->bself();

        panel = new JPanel(new FlowLayout());

        _localVariableTextField = new JTextField(30);

        JPanel* operationAndCasePanel = new JPanel();
        operationAndCasePanel->setLayout(new QVBoxLayout());//operationAndCasePanel, BoxLayout.Y_AXIS));

        _variableOperationComboBox = new JComboBox();
        for (ExpressionLocalVariable::VariableOperation::TYPE e : ExpressionLocalVariable::VariableOperation::values()) {
            _variableOperationComboBox->addItem(ExpressionLocalVariable::VariableOperation::toString(e), e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_variableOperationComboBox);
        operationAndCasePanel->layout()->addWidget(_variableOperationComboBox);

        connect(_variableOperationComboBox, &JComboBox::currentIndexChanged, [=] { enableDisableCompareTo(); });

        _caseInsensitiveCheckBox = new JCheckBox(tr("CaseInsensitive"));
        operationAndCasePanel->layout()->addWidget(_caseInsensitiveCheckBox);

        _tabbedPane = new JTabbedPane();

        _tabbedPaneCompareTo = new JTabbedPane();
        _tabbedPane->addTab("", _tabbedPaneCompareTo);

        _compareToConstant = new JPanel(new FlowLayout());
        _compareToMemory = new JPanel(new FlowLayout);
        _compareToLocalVariable = new JPanel(new FlowLayout);
        _compareToRegEx = new JPanel(new FlowLayout());

        _tabbedPaneCompareTo->addTab(ExpressionLocalVariable::CompareTo::toString(ExpressionLocalVariable::CompareTo::Value), _compareToConstant);
        _tabbedPaneCompareTo->addTab(ExpressionLocalVariable::CompareTo::toString(ExpressionLocalVariable::CompareTo::Memory), _compareToMemory);
        _tabbedPaneCompareTo->addTab(ExpressionLocalVariable::CompareTo::toString(ExpressionLocalVariable::CompareTo::LocalVariable), _compareToLocalVariable);

        _tabbedPane->addTab(ExpressionLocalVariable::CompareTo::toString(ExpressionLocalVariable::CompareTo::RegEx), _compareToRegEx);

        _compareToConstantTextField = new JTextField(30);
        _compareToConstant->layout()->addWidget(_compareToConstantTextField);

        _compareToMemoryBeanPanel = new BeanSelectPanel((AbstractMemoryManager*)InstanceManager::getDefault("MemoryManager"), nullptr);
        _compareToMemory->layout()->addWidget(_compareToMemoryBeanPanel);

        _compareToLocalVariableTextField = new JTextField(30);
        _compareToLocalVariable->layout()->addWidget(_compareToLocalVariableTextField);

        _compareToRegExTextField = new JTextField(30);
        _compareToRegEx->layout()->addWidget(_compareToRegExTextField);


        if (expression != nullptr) {
            if (expression->getLocalVariable() != nullptr) {
                _localVariableTextField->setText(expression->getLocalVariable());
            }
            if (expression->getMemory() != nullptr) {
                _compareToMemoryBeanPanel->setDefaultNamedBean(expression->getMemory()->getBean());
            }
            switch (expression->getCompareTo()) {
                case ExpressionLocalVariable::CompareTo::RegEx:
                case ExpressionLocalVariable::CompareTo::Value: _tabbedPaneCompareTo->setSelectedComponent(_compareToConstant); break;
                case ExpressionLocalVariable::CompareTo::Memory: _tabbedPaneCompareTo->setSelectedComponent(_compareToMemory); break;
                case ExpressionLocalVariable::CompareTo::LocalVariable: _tabbedPaneCompareTo->setSelectedComponent(_compareToLocalVariable); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + ExpressionLocalVariable::CompareTo::toString(expression->getCompareTo()));
            }
            _variableOperationComboBox->setSelectedItem(expression->getVariableOperation());
            _caseInsensitiveCheckBox->setSelected(expression->getCaseInsensitive());
            _compareToConstantTextField->setText(expression->getConstantValue());
            _compareToLocalVariableTextField->setText(expression->getOtherLocalVariable());
            _compareToRegExTextField->setText(expression->getRegEx());
        }

        QList<JComponent*> components = QList<JComponent*>{
            _localVariableTextField,
            operationAndCasePanel,
            _tabbedPane
        };

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Local variable{0} {1} %{2}"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget((QWidget*)c->jself());

        enableDisableCompareTo();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ExpressionLocalVariableSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* ExpressionLocalVariableSwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        ExpressionLocalVariable* expression = new ExpressionLocalVariable(systemName, userName);
        updateObject(expression);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionLocalVariableSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ExpressionLocalVariable*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ExpressionLocalVariable but is a: ")+object->bself()->metaObject()->className());
        }
        ExpressionLocalVariable* expression = (ExpressionLocalVariable*)object->bself();

        expression->setLocalVariable(_localVariableTextField->text());
        expression->setVariableOperation((ExpressionLocalVariable::VariableOperation::TYPE)_variableOperationComboBox->getItemAt(_variableOperationComboBox->getSelectedIndex()).toInt());
        expression->setCaseInsensitive(_caseInsensitiveCheckBox->isSelected());


        if (!_compareToMemoryBeanPanel->isEmpty()
                && (_tabbedPane->getSelectedComponent() == _tabbedPaneCompareTo)
                && (_tabbedPaneCompareTo->getSelectedComponent() == _compareToMemory)) {
            Memory* otherMemory = (Memory*)_compareToMemoryBeanPanel->getNamedBean()->self();
            if (otherMemory != nullptr) {
                NamedBeanHandle<Memory*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(otherMemory->getDisplayName(), otherMemory);
                expression->setMemory(handle);
            } else {
                expression->removeMemory();
            }
        } else {
            expression->removeMemory();
        }

        if (_tabbedPane->getSelectedComponent() == _tabbedPaneCompareTo) {
            if (_tabbedPaneCompareTo->getSelectedComponent() == _compareToConstant) {
                expression->setCompareTo(ExpressionLocalVariable::CompareTo::Value);
                expression->setConstantValue(_compareToConstantTextField->text());
            } else if (_tabbedPaneCompareTo->getSelectedComponent() == _compareToMemory) {
                expression->setCompareTo(ExpressionLocalVariable::CompareTo::Memory);
            } else if (_tabbedPaneCompareTo->getSelectedComponent() == _compareToLocalVariable) {
                expression->setCompareTo(ExpressionLocalVariable::CompareTo::LocalVariable);
                expression->setOtherLocalVariable(_compareToLocalVariableTextField->text());
//            } else if (_tabbedPaneCompareTo->getSelectedComponent() == _compareToRegEx) {
//                expression->setCompareTo(CompareTo.RegEx);
//                expression->setRegEx(_compareToRegExTextField->getText());
            } else {
                throw new IllegalArgumentException("_tabbedPaneLight has unknown selection");
            }
        } else {
            expression->setCompareTo(ExpressionLocalVariable::CompareTo::RegEx);
            expression->setRegEx(_compareToRegExTextField->text());
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ExpressionLocalVariableSwing::toString() {
        return tr("LocalVariable");
    }

    //@Override
    /*public*/  void ExpressionLocalVariableSwing::dispose() {
    }

