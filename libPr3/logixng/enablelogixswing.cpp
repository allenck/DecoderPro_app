#include "enablelogixswing.h"
#include "beanselectpanel.h"
#include "defaultlogixmanager.h"
#include "jtabbedpane.h"
#include "jtextfield.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/enablelogix.h"
#include "instancemanager.h"
#include "logixng/parserexception.h"

EnableLogixSwing::EnableLogixSwing(QObject *parent)
    : AbstractDigitalActionSwing{parent}
{

}
/**
 * Configures an EnableLogix object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class EnableLogixSwing extends AbstractDigitalActionSwing {



    //@Override
    /*protected*/ void EnableLogixSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        EnableLogix* action = nullptr;
        if(object) action =(EnableLogix*)object->bself();

        panel = new JPanel(new FlowLayout);

        _tabbedPaneLogix = new JTabbedPane();
        _panelLogixDirect = new JPanel(new FlowLayout);
        _panelLogixReference = new JPanel(new FlowLayout);
        _panelLogixLocalVariable = new JPanel(new FlowLayout);
        _panelLogixFormula = new JPanel(new FlowLayout);

        _tabbedPaneLogix->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelLogixDirect);
        _tabbedPaneLogix->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelLogixReference);
        _tabbedPaneLogix->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelLogixLocalVariable);
        _tabbedPaneLogix->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelLogixFormula);

        logixBeanPanel = new BeanSelectPanel((DefaultLogixManager*)InstanceManager::getDefault("LogixManager"), nullptr);
        _panelLogixDirect->layout()->addWidget(logixBeanPanel);

        _logixReferenceTextField = new JTextField();
        _logixReferenceTextField->setColumns(30);
        _panelLogixReference->layout()->addWidget(_logixReferenceTextField);

        _logixLocalVariableTextField = new JTextField();
        _logixLocalVariableTextField->setColumns(30);
        _panelLogixLocalVariable->layout()->addWidget(_logixLocalVariableTextField);

        _logixFormulaTextField = new JTextField();
        _logixFormulaTextField->setColumns(30);
        _panelLogixFormula->layout()->addWidget(_logixFormulaTextField);


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
        for (EnableLogix::Operation::TYPE e : EnableLogix::Operation::values()) {
            _stateComboBox->addItem(EnableLogix::Operation::toString(e),e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_stateComboBox);

        _panelOperationDirect->layout()->addWidget(_stateComboBox);

        _logixLockReferenceTextField = new JTextField();
        _logixLockReferenceTextField->setColumns(30);
        _panelOperationReference->layout()->addWidget(_logixLockReferenceTextField);

        _logixLockLocalVariableTextField = new JTextField();
        _logixLockLocalVariableTextField->setColumns(30);
        _panelOperationLocalVariable->layout()->addWidget(_logixLockLocalVariableTextField);

        _logixLockFormulaTextField = new JTextField();
        _logixLockFormulaTextField->setColumns(30);
        _panelOperationFormula->layout()->addWidget(_logixLockFormulaTextField);


        if (action != nullptr) {
            switch (action->getAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneLogix->setSelectedComponent(_panelLogixDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneLogix->setSelectedComponent(_panelLogixReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneLogix->setSelectedComponent(_panelLogixLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneLogix->setSelectedComponent(_panelLogixFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            if (action->getLogix() != nullptr) {
                logixBeanPanel->setDefaultNamedBean(action->getLogix()->getBean());
            }
            _logixReferenceTextField->setText(action->getReference());
            _logixLocalVariableTextField->setText(action->getLocalVariable());
            _logixFormulaTextField->setText(action->getFormula());

            switch (action->getOperationAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneOperation->setSelectedComponent(_panelOperationDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneOperation->setSelectedComponent(_panelOperationReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneOperation->setSelectedComponent(_panelOperationLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneOperation->setSelectedComponent(_panelOperationFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            _stateComboBox->setSelectedItem(action->getOperationDirect());
            _logixLockReferenceTextField->setText(action->getOperationReference());
            _logixLockLocalVariableTextField->setText(action->getOperationLocalVariable());
            _logixLockFormulaTextField->setText(action->getLockFormula());
        }

        QList<JComponent*> components = QList<JComponent*>{
            _tabbedPaneLogix,
            _tabbedPaneOperation};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                    tr("Set Logix {0} to {1}"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget((QWidget*)c->jself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool EnableLogixSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        EnableLogix* action = new EnableLogix("IQDA1", "");

        try {
            if (_tabbedPaneLogix->getSelectedComponent() == _panelLogixReference) {
                action->setReference(_logixReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationReference) {
                action->setOperationReference(_logixLockReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            action->setFormula(_logixFormulaTextField->text());
            if (_tabbedPaneLogix->getSelectedComponent() == _panelLogixDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneLogix->getSelectedComponent() == _panelLogixReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneLogix->getSelectedComponent() == _panelLogixLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneLogix->getSelectedComponent() == _panelLogixFormula) {
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
    /*public*/ MaleSocket* EnableLogixSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        EnableLogix* action = new EnableLogix(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void EnableLogixSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<EnableLogix*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an EnableLogix but is a: ")+object->bself()->metaObject()->className());
        }
        EnableLogix* action = (EnableLogix*)object->bself();
        if (_tabbedPaneLogix->getSelectedComponent() == _panelLogixDirect) {
            Logix* logix = (Logix*)logixBeanPanel->getNamedBean()->self();
            if (logix != nullptr) {
                NamedBeanHandle<Logix*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(logix->getDisplayName(), logix);
                action->setLogix(handle);
            } else {
                action->removeLogix();
            }
        } else {
            action->removeLogix();
        }
        try {
            if (_tabbedPaneLogix->getSelectedComponent() == _panelLogixDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneLogix->getSelectedComponent() == _panelLogixReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
                action->setReference(_logixReferenceTextField->text());
            } else if (_tabbedPaneLogix->getSelectedComponent() == _panelLogixLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
                action->setLocalVariable(_logixLocalVariableTextField->text());
            } else if (_tabbedPaneLogix->getSelectedComponent() == _panelLogixFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
                action->setFormula(_logixFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneLogix has unknown selection");
            }

            if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationDirect) {
                action->setOperationAddressing(NamedBeanAddressing::Direct);
                action->setOperationDirect((EnableLogix::Operation::TYPE)_stateComboBox->getSelectedIndex());
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationReference) {
                action->setOperationAddressing(NamedBeanAddressing::Reference);
                action->setOperationReference(_logixLockReferenceTextField->text());
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationLocalVariable) {
                action->setOperationAddressing(NamedBeanAddressing::LocalVariable);
                action->setOperationLocalVariable(_logixLockLocalVariableTextField->text());
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationFormula) {
                action->setOperationAddressing(NamedBeanAddressing::Formula);
                action->setOperationFormula(_logixLockFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneLogix has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString EnableLogixSwing::toString() {
        return tr("EnableLogix");
    }

    //@Override
    /*public*/ void EnableLogixSwing::dispose() {
        if (logixBeanPanel != nullptr) {
            logixBeanPanel->dispose();
        }
    }


//    /*private*/ final static org.slf4j.Logger log = org.slf4j.LoggerFactory->getLogger(EnableLogixSwing.class);
