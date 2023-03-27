#include "actionreporterswing.h"
#include "instancemanager.h"
#include "actionreporter.h"
#include "jtabbedpane.h"
#include "jcombobox.h"
#include "proxyreportermanager.h"
#include "namedbeanaddressing.h"
#include "beanselectpanel.h"
#include "jtextfield.h"
#include "parserexception.h"
#include "abstractmemorymanager.h"
#include "defaultdigitalactionmanager.h"

ActionReporterSwing::ActionReporterSwing(QObject* parent)
{
 setObjectName("ActionReporterSwing");
}
/**
 * Configures an ActionReporter object with a Swing JPanel.
 *
 * @author Daniel Bergqvist  Copyright 2021
 * @author Dave Sand         Copyright 2021
 */
///*public*/  class ActionReporterSwing extends AbstractDigitalActionSwing {



    //@Override
    /*protected*/ void ActionReporterSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ActionReporter* action = nullptr;
        if(object) action = (ActionReporter*)object->bself();

        panel = new JPanel(new FlowLayout);

        // Left section
        _panelReporterValue = new JPanel(new FlowLayout);
        _reporterValueComboBox = new JComboBox();
        for (ActionReporter::ReporterValue::VAL e : ActionReporter::ReporterValue::values()) {
            _reporterValueComboBox->addItem(ActionReporter::ReporterValue::toString(e),e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_reporterValueComboBox);
        _panelReporterValue->layout()->addWidget(_reporterValueComboBox);

        // Center section
        _tabbedPaneBean = new JTabbedPane();
        _panelBeanDirect = new JPanel(new FlowLayout);
        _panelBeanReference = new JPanel(new FlowLayout);
        _panelBeanLocalVariable = new JPanel(new FlowLayout);
        _panelBeanFormula = new JPanel(new FlowLayout);

        _tabbedPaneBean->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelBeanDirect);
        _tabbedPaneBean->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelBeanReference);
        _tabbedPaneBean->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelBeanLocalVariable);
        _tabbedPaneBean->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelBeanFormula);

        _beanSelectPanel = new BeanSelectPanel(((AbstractManager*)InstanceManager::getDefault("ReporterManager")), nullptr);
        _panelBeanDirect->layout()->addWidget(_beanSelectPanel);

        _beanReferenceTextField = new JTextField();
        _beanReferenceTextField->setColumns(30);
        _panelBeanReference->layout()->addWidget(_beanReferenceTextField);

        _beanLocalVariableTextField = new JTextField();
        _beanLocalVariableTextField->setColumns(30);
        _panelBeanLocalVariable->layout()->addWidget(_beanLocalVariableTextField);

        _beanFormulaTextField = new JTextField();
        _beanFormulaTextField->setColumns(30);
        _panelBeanFormula->layout()->addWidget(_beanFormulaTextField);

        // Right section
        _tabbedPaneData = new JTabbedPane();
        _panelDataDirect = new JPanel(new FlowLayout);
        _panelDataReference = new JPanel(new FlowLayout);
        _panelDataLocalVariable = new JPanel(new FlowLayout);
        _panelDataFormula = new JPanel(new FlowLayout);

        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelDataDirect);
        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelDataReference);
        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelDataLocalVariable);
        _tabbedPaneData->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelDataFormula);

        _memorySelectPanel = new BeanSelectPanel((AbstractMemoryManager*)InstanceManager::getDefault("MemoryManager"), nullptr);
        _panelDataDirect->layout()->addWidget(_memorySelectPanel);

        _dataReferenceTextField = new JTextField();
        _dataReferenceTextField->setColumns(30);
        _panelDataReference->layout()->addWidget(_dataReferenceTextField);

        _dataLocalVariableTextField = new JTextField();
        _dataLocalVariableTextField->setColumns(30);
        _panelDataLocalVariable->layout()->addWidget(_dataLocalVariableTextField);

        _dataFormulaTextField = new JTextField();
        _dataFormulaTextField->setColumns(30);
        _panelDataFormula->layout()->addWidget(_dataFormulaTextField);


        if (action != nullptr) {
            switch (action->getAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneBean->setSelectedComponent(_panelBeanDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneBean->setSelectedComponent(_panelBeanReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneBean->setSelectedComponent(_panelBeanLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneBean->setSelectedComponent(_panelBeanFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            if (action->getReporter() != nullptr) {
                _beanSelectPanel->setDefaultNamedBean(action->getReporter()->getBean());
            }
            _beanReferenceTextField->setText(action->getReference());
            _beanLocalVariableTextField->setText(action->getLocalVariable());
            _beanFormulaTextField->setText(action->getFormula());

            _reporterValueComboBox->setSelectedItem(action->getReporterValue());

            switch (action->getDataAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneData->setSelectedComponent(_panelDataDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneData->setSelectedComponent(_panelDataReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneData->setSelectedComponent(_panelDataLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneData->setSelectedComponent(_panelDataFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getDataAddressing()));
            }
            if (action->getMemory() != nullptr) {
                _memorySelectPanel->setDefaultNamedBean(action->getMemory()->getBean());
            }
            _dataReferenceTextField->setText(action->getDataReference());
            _dataLocalVariableTextField->setText(action->getDataLocalVariable());
            _dataFormulaTextField->setText(action->getDataFormula());
        }

        QList<JComponent*> components =  QList<JComponent*>{
            _panelReporterValue,
            _tabbedPaneBean,
            _tabbedPaneData};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Copy the {0} for reporter {1} to {2}"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget((QWidget*)c->jself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ActionReporterSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        validateBeanSection(errorMessages);
        validateDataSection(errorMessages);
        return errorMessages->isEmpty();
    }

    /*private*/ void ActionReporterSwing::validateBeanSection(QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionReporter* action = new ActionReporter("IQDA1", "");

        try {
            if (_tabbedPaneBean->getSelectedComponent() == _panelBeanReference) {
                action->setReference(_beanReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return;
        }

        try {
            action->setFormula(_beanFormulaTextField->text());
            if (_tabbedPaneBean->getSelectedComponent() == _panelBeanDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneBean->getSelectedComponent() == _panelBeanReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneBean->getSelectedComponent() == _panelBeanLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneBean->getSelectedComponent() == _panelBeanFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
            } else {
                throw new IllegalArgumentException("_tabbedPane has unknown selection");
            }
        } catch (ParserException* e) {
            errorMessages->append("Cannot parse formula: " + e->getMessage());
        }

        if (_tabbedPaneBean->getSelectedComponent() == _panelBeanDirect) {
            if (_beanSelectPanel->getNamedBean() == nullptr) {
                errorMessages->append(tr("A reporter was not selected"));
            }
        }
    }

    /*private*/ void ActionReporterSwing::validateDataSection(QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ActionReporter* action = new ActionReporter("IQDA3", "");

        try {
            if (_tabbedPaneData->getSelectedComponent() == _panelDataReference) {
                action->setDataReference(_dataReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return;
        }

        try {
            action->setDataFormula(_dataFormulaTextField->text());
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
            if (_memorySelectPanel->getNamedBean() == nullptr) {
                errorMessages->append(tr("A memory was not selected"));
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* ActionReporterSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ActionReporter* action = new ActionReporter(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionReporterSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ActionReporter*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object must be an ActionReporter but is a: ")+object->bself()->metaObject()->className());
        }
        ActionReporter* action = (ActionReporter*) object->bself();

        if (_tabbedPaneBean->getSelectedComponent() == _panelBeanDirect) {
            Reporter* reporter = (Reporter*)_beanSelectPanel->getNamedBean()->self();
            if (reporter != nullptr) {
                NamedBeanHandle<Reporter*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(reporter->getDisplayName(), reporter);
                action->setReporter(handle);
            } else {
                action->removeReporter();
            }
        } else {
            action->removeReporter();
        }

        try {
            // Left section
            action->setReporterValue((ActionReporter::ReporterValue::VAL)_reporterValueComboBox->getItemAt(_reporterValueComboBox->getSelectedIndex()).toInt());

            // Center section
            if (_tabbedPaneBean->getSelectedComponent() == _panelBeanDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneBean->getSelectedComponent() == _panelBeanReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
                action->setReference(_beanReferenceTextField->text());
            } else if (_tabbedPaneBean->getSelectedComponent() == _panelBeanLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
                action->setLocalVariable(_beanLocalVariableTextField->text());
            } else if (_tabbedPaneBean->getSelectedComponent() == _panelBeanFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
                action->setFormula(_beanFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneBean has unknown selection");
            }

            // Right section
            action->removeMemory();
            if (_tabbedPaneData->getSelectedComponent() == _panelDataDirect) {
                action->setDataAddressing(NamedBeanAddressing::Direct);
                Memory* memory = (Memory*)_memorySelectPanel->getNamedBean()->self();
                if (memory != nullptr) {
                    NamedBeanHandle<Memory*>* handle
                            = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                    ->getNamedBeanHandle(memory->getDisplayName(), memory);
                    action->setMemory(handle);
                }
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataReference) {
                action->setDataAddressing(NamedBeanAddressing::Reference);
                action->setDataReference(_dataReferenceTextField->text());
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataLocalVariable) {
                action->setDataAddressing(NamedBeanAddressing::LocalVariable);
                action->setDataLocalVariable(_dataLocalVariableTextField->text());
            } else if (_tabbedPaneData->getSelectedComponent() == _panelDataFormula) {
                action->setDataAddressing(NamedBeanAddressing::Formula);
                action->setDataFormula(_dataFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneBean has unknown selection");
            }

        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ActionReporterSwing::toString() {
        return tr("ActionReporter");
    }

    //@Override
    /*public*/  void ActionReporterSwing::dispose() {
        if (_beanSelectPanel != nullptr) {
            _beanSelectPanel->dispose();
        }
        if (_memorySelectPanel != nullptr) {
            _memorySelectPanel->dispose();
        }
    }
