#include "executedelayedswing.h"
#include "executedelayed.h"
#include "jtabbedpane.h"
#include "namedbeanaddressing.h"
#include "jformattedtextfield.h"
#include "instancemanager.h"
#include "defaultdigitalactionmanager.h"
#include "jcombobox.h"
#include "jcheckbox.h"
#include "timerunit.h"
#include "parserexception.h"

ExecuteDelayedSwing::ExecuteDelayedSwing(QObject* parent)
{

}
/**
 * Configures an ExecuteDelayed object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright (C) 2021
 */
// /*public*/  class ExecuteDelayedSwing extends AbstractDigitalActionSwing {


    //@Override
    /*protected*/ void ExecuteDelayedSwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        if ((object != nullptr) && !(qobject_cast<ExecuteDelayed*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ExecuteDelayed but is a: ")+object->bself()->metaObject()->className());
        }

        ExecuteDelayed* action = nullptr;
        if(object) action =(ExecuteDelayed*)object->bself();

        panel = new JPanel();
        panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));

        _tabbedPaneDelay = new JTabbedPane();
        _panelDelayDirect = new JPanel(new FlowLayout);
        _panelDelayReference = new JPanel(new FlowLayout);
        _panelDelayLocalVariable = new JPanel(new FlowLayout);
        _panelDelayFormula = new JPanel(new FlowLayout);

        _tabbedPaneDelay->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelDelayDirect);
        _tabbedPaneDelay->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelDelayReference);
        _tabbedPaneDelay->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelDelayLocalVariable);
        _tabbedPaneDelay->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelDelayFormula);

        _timerDelay = new JFormattedTextField(/*"0"*/);
        _timerDelay->setValidator(new QIntValidator());
        _timerDelay->setColumns(7);

        _panelDelayDirect->layout()->addWidget(_timerDelay);

        _delayReferenceTextField = new JTextField();
        _delayReferenceTextField->setColumns(30);
        _panelDelayReference->layout()->addWidget(_delayReferenceTextField);

        _delayLocalVariableTextField = new JTextField();
        _delayLocalVariableTextField->setColumns(30);
        _panelDelayLocalVariable->layout()->addWidget(_delayLocalVariableTextField);

        _delayFormulaTextField = new JTextField();
        _delayFormulaTextField->setColumns(30);
        _panelDelayFormula->layout()->addWidget(_delayFormulaTextField);


        if (action != nullptr) {
            switch (action->getDelayAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneDelay->setSelectedComponent(_panelDelayDirect); break;
                case NamedBeanAddressing::Reference: _tabbedPaneDelay->setSelectedComponent(_panelDelayReference); break;
                case NamedBeanAddressing::LocalVariable: _tabbedPaneDelay->setSelectedComponent(_panelDelayLocalVariable); break;
                case NamedBeanAddressing::Formula: _tabbedPaneDelay->setSelectedComponent(_panelDelayFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getDelayAddressing()));
            }
            _timerDelay->setText(QString::number(action->getDelay()));
            _delayReferenceTextField->setText(action->getDelayReference());
            _delayLocalVariableTextField->setText(action->getDelayLocalVariable());
            _delayFormulaTextField->setText(action->getDelayFormula());
        }

        QList<JComponent*> components = {
            _tabbedPaneDelay};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Execute delay {1}"),components);

        JPanel* delayPanel = new JPanel(new FlowLayout);
        for (JComponent* c : /*componentList*/components) delayPanel->layout()->addWidget((QWidget*)c->jself());

        panel->layout()->addWidget(delayPanel);


        JPanel* unitPanel = new JPanel(new FlowLayout);
        unitPanel->layout()->addWidget(_unitLabel);

        _unitComboBox = new JComboBox();
        for (TimerUnit::VAL u : TimerUnit::values()) _unitComboBox->addItem(TimerUnit::toString(u), u);
//        JComboBoxUtil->setupComboBoxMaxRows(_unitComboBox);
        if (action != nullptr) _unitComboBox->setSelectedItem(action->getUnit());
        unitPanel->layout()->addWidget(_unitComboBox);

        panel->layout()->addWidget(unitPanel);

        _resetIfAlreadyStarted = new JCheckBox(tr("Reset timer if already started"));
        if (action != nullptr) _resetIfAlreadyStarted->setSelected(action->getResetIfAlreadyStarted());
        panel->layout()->addWidget(_resetIfAlreadyStarted);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ExecuteDelayedSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        ExecuteDelayed* action = new ExecuteDelayed("IQDA1", "");

        try {
            if (_tabbedPaneDelay->getSelectedComponent() == _panelDelayReference) {
                action->setDelayReference(_delayReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            action->setDelayFormula(_delayFormulaTextField->text());
            if (_tabbedPaneDelay->getSelectedComponent() == _panelDelayDirect) {
                action->setDelayAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneDelay->getSelectedComponent() == _panelDelayReference) {
                action->setDelayAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneDelay->getSelectedComponent() == _panelDelayLocalVariable) {
                action->setDelayAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneDelay->getSelectedComponent() == _panelDelayFormula) {
                action->setDelayAddressing(NamedBeanAddressing::Formula);
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
    /*public*/  MaleSocket* ExecuteDelayedSwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        ExecuteDelayed* action = new ExecuteDelayed(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExecuteDelayedSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (!(qobject_cast<ExecuteDelayed*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ExecuteDelayed but is a: ")+object->bself()->metaObject()->className());
        }

        ExecuteDelayed* action = (ExecuteDelayed*)object->bself();

        action->setUnit((TimerUnit::VAL)_unitComboBox->getItemAt(_unitComboBox->getSelectedIndex()).toInt());
        action->setResetIfAlreadyStarted(_resetIfAlreadyStarted->isSelected());



        try {
            if (_tabbedPaneDelay->getSelectedComponent() == _panelDelayDirect) {
                action->setDelayAddressing(NamedBeanAddressing::Direct);
                action->setDelay(_timerDelay->text().toUInt());
            } else if (_tabbedPaneDelay->getSelectedComponent() == _panelDelayReference) {
                action->setDelayAddressing(NamedBeanAddressing::Reference);
                action->setDelayReference(_delayReferenceTextField->text());
            } else if (_tabbedPaneDelay->getSelectedComponent() == _panelDelayLocalVariable) {
                action->setDelayAddressing(NamedBeanAddressing::LocalVariable);
                action->setDelayLocalVariable(_delayLocalVariableTextField->text());
            } else if (_tabbedPaneDelay->getSelectedComponent() == _panelDelayFormula) {
                action->setDelayAddressing(NamedBeanAddressing::Formula);
                action->setDelayFormula(_delayFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneDelay has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ExecuteDelayedSwing::toString() {
        return tr("ExecuteDelayed");
    }

    //@Override
    /*public*/  void ExecuteDelayedSwing::dispose() {
    }

