#include "expressionmemoryswing.h"
#include "jcombobox.h"
#include "expressionmemory.h"
#include "jtabbedpane.h"
#include "beanselectpanel.h"
#include "jcheckbox.h"
#include "jtextfield.h"
#include "defaultmemorymanager.h"
#include "instancemanager.h"
#include "swingconfiguratorinterface.h"
#include "expressionmemory.h"
#include "defaultdigitalexpressionmanager.h"

/**
 * Configures an ExpressionMemory object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
//*public*/  class ExpressionMemorySwing extends AbstractDigitalExpressionSwing {

ExpressionMemorySwing::ExpressionMemorySwing(QObject *parent) : AbstractDigitalExpressionSwing(parent)
{
 setObjectName("ExpressionMemorySwing");
}



    /*private*/ void ExpressionMemorySwing::enableDisableCompareTo() {
        ExpressionMemory::MemoryOperation::TYPE mo = (ExpressionMemory::MemoryOperation::TYPE)_memoryOperationComboBox->getItemAt(
                        _memoryOperationComboBox->getSelectedIndex()).toInt();
        bool enable = ExpressionMemory::MemoryOperation::hasExtraValue(mo);
        _tabbedPaneCompareTo->QWidget::setEnabled(enable);
        ((JPanel*)_tabbedPaneCompareTo->getSelectedComponent())
                ->getComponent(0)->setEnabled(enable);

        bool regEx = (mo == ExpressionMemory::MemoryOperation::MatchRegex)
                || (mo == ExpressionMemory::MemoryOperation::NotMatchRegex);
        _tabbedPane->setEnabledAt(0, !regEx);
        _tabbedPane->setEnabledAt(1, regEx);
        _tabbedPane->setSelectedIndex(regEx ? 1 : 0);
    }

    //@Override
    /*protected*/ void ExpressionMemorySwing::createPanel(/*CheckForNull*/ Base* object,/*@Nonnull*/ JPanel* buttonPanel) {
        ExpressionMemory* expression = (ExpressionMemory*)object->bself();

        panel = new JPanel(new FlowLayout());

        _memoryBeanPanel = new BeanSelectPanel((AbstractManager*)InstanceManager::getDefault("MemoryManager"), nullptr);

        JPanel* operationAndCasePanel = new JPanel();
        operationAndCasePanel->setLayout(new QVBoxLayout());//operationAndCasePanel, BoxLayout.Y_AXIS));

        _memoryOperationComboBox = new JComboBox();
        for (ExpressionMemory::MemoryOperation::TYPE e : ExpressionMemory::MemoryOperation::values()) {
            _memoryOperationComboBox->addItem(ExpressionMemory::MemoryOperation::toString(e),e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_memoryOperationComboBox);
        operationAndCasePanel->layout()->addWidget(_memoryOperationComboBox);

        connect(_memoryOperationComboBox, &JComboBox::currentIndexChanged, [=]{ enableDisableCompareTo(); });

        _caseInsensitiveCheckBox = new JCheckBox(tr("CaseInsensitive"));
        operationAndCasePanel->layout()->addWidget(_caseInsensitiveCheckBox);

        _tabbedPane = new JTabbedPane();

        _tabbedPaneCompareTo = new JTabbedPane();
        _tabbedPane->addTab("", _tabbedPaneCompareTo);

        _compareToConstant = new JPanel();
        _compareToMemory = new JPanel();
        _compareToLocalVariable = new JPanel();
        _compareToRegEx = new JPanel();

        _tabbedPaneCompareTo->addTab(ExpressionMemory::CompareTo::toString(ExpressionMemory::CompareTo::Value), _compareToConstant);
        _tabbedPaneCompareTo->addTab(ExpressionMemory::CompareTo::toString(ExpressionMemory::CompareTo::Memory), _compareToMemory);
        _tabbedPaneCompareTo->addTab(ExpressionMemory::CompareTo::toString(ExpressionMemory::CompareTo::LocalVariable), _compareToLocalVariable);

        _tabbedPane->addTab(ExpressionMemory::CompareTo::toString(ExpressionMemory::CompareTo::RegEx), _compareToRegEx);

        _compareToConstantTextField = new JTextField(30);
        _compareToConstant->layout()->addWidget(_compareToConstantTextField);

        _compareToMemoryBeanPanel = new BeanSelectPanel((AbstractMemoryManager*)InstanceManager::getDefault("MemoryManager"), nullptr);
        _compareToMemory->layout()->addWidget(_compareToMemoryBeanPanel);

        _compareToLocalVariableTextField = new JTextField(30);
        _compareToLocalVariable->layout()->addWidget(_compareToLocalVariableTextField);

        _compareToRegExTextField = new JTextField(30);
        _compareToRegEx->layout()->addWidget(_compareToRegExTextField);


        if (expression != nullptr) {
            if (expression->getMemory() != nullptr) {
                _memoryBeanPanel->setDefaultNamedBean(expression->getMemory()->getBean());
            }
            if (expression->getOtherMemory() != nullptr) {
                _compareToMemoryBeanPanel->setDefaultNamedBean(expression->getOtherMemory()->getBean());
            }
            switch (expression->getCompareTo()) {
                case ExpressionMemory::CompareTo::RegEx:
                case ExpressionMemory::CompareTo::Value: _tabbedPaneCompareTo->setSelectedComponent(_compareToConstant); break;
                case ExpressionMemory::CompareTo::Memory: _tabbedPaneCompareTo->setSelectedComponent(_compareToMemory); break;
                case ExpressionMemory::CompareTo::LocalVariable: _tabbedPaneCompareTo->setSelectedComponent(_compareToLocalVariable); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + ExpressionMemory::CompareTo::toString(expression->getCompareTo()));
            }
            _memoryOperationComboBox->setSelectedItem(expression->getMemoryOperation());
            _caseInsensitiveCheckBox->setSelected(expression->getCaseInsensitive());
            _compareToConstantTextField->setText(expression->getConstantValue());
            _compareToLocalVariableTextField->setText(expression->getLocalVariable());
            _compareToRegExTextField->setText(expression->getRegEx());
        }

        QList<JComponent*> components = QList<JComponent*>{
            _memoryBeanPanel,
            operationAndCasePanel,
            _tabbedPane
        };

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Memory %1 %2 %3"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget(c->jself());

        enableDisableCompareTo();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ExpressionMemorySwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* ExpressionMemorySwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        ExpressionMemory* expression = new ExpressionMemory(systemName, userName);
        updateObject(expression);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionMemorySwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ExpressionMemory*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ExpressionMemory but is a: ")+object->bself()->metaObject()->className());
        }
        ExpressionMemory* expression = (ExpressionMemory*)object->bself();
        Memory* memory =(Memory*) _memoryBeanPanel->getNamedBean()->self();
        if (memory != nullptr) {
            NamedBeanHandle<Memory*>* handle
                    = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                            ->getNamedBeanHandle(memory->getDisplayName(), memory);
            expression->setMemory(handle);
        } else {
            expression->removeMemory();
        }
        expression->setMemoryOperation((ExpressionMemory::MemoryOperation::TYPE)_memoryOperationComboBox->getItemAt(_memoryOperationComboBox->getSelectedIndex()).toInt());
        expression->setCaseInsensitive(_caseInsensitiveCheckBox->isSelected());


        if (!_compareToMemoryBeanPanel->isEmpty()
                && (_tabbedPane->getSelectedComponent() == _tabbedPaneCompareTo)
                && (_tabbedPaneCompareTo->getSelectedComponent() == _compareToMemory)) {
            Memory* otherMemory = (Memory*)_compareToMemoryBeanPanel->getNamedBean()->self();
            if (otherMemory != nullptr) {
                NamedBeanHandle<Memory*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(otherMemory->getDisplayName(), otherMemory);
                expression->setOtherMemory(handle);
            } else {
                expression->removeOtherMemory();
            }
        } else {
            expression->removeOtherMemory();
        }

        if (_tabbedPane->getSelectedComponent() == _tabbedPaneCompareTo) {
            if (_tabbedPaneCompareTo->getSelectedComponent() == _compareToConstant) {
                expression->setCompareTo(ExpressionMemory::CompareTo::Value);
                expression->setConstantValue(_compareToConstantTextField->text());
            } else if (_tabbedPaneCompareTo->getSelectedComponent() == _compareToMemory) {
                expression->setCompareTo(ExpressionMemory::CompareTo::Memory);
            } else if (_tabbedPaneCompareTo->getSelectedComponent() == _compareToLocalVariable) {
                expression->setCompareTo(ExpressionMemory::CompareTo::LocalVariable);
                expression->setLocalVariable(_compareToLocalVariableTextField->text());
//            } else if (_tabbedPaneCompareTo->getSelectedComponent() == _compareToRegEx) {
//                expression->setCompareTo(CompareTo.RegEx);
//                expression->setRegEx(_compareToRegExTextField->getText());
            } else {
                throw new IllegalArgumentException("_tabbedPaneLight has unknown selection");
            }
        } else {
            expression->setCompareTo(ExpressionMemory::CompareTo::RegEx);
            expression->setRegEx(_compareToRegExTextField->text());
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ExpressionMemorySwing::toString() {
        return tr("Memory");
    }

    //@Override
    /*public*/  void ExpressionMemorySwing::dispose() {
    }
