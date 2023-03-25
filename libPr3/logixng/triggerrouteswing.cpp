#include "triggerrouteswing.h"
#include "abstractroutemanager.h"
#include "beanselectpanel.h"
#include "jtabbedpane.h"
#include "jtextfield.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/parserexception.h"
#include "triggerroute.h"
#include "instancemanager.h"


TriggerRouteSwing::TriggerRouteSwing(QObject *parent)
    : AbstractDigitalActionSwing{parent}
{

}
/**
 * Configures an TriggerRoute object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class TriggerRouteSwing extends AbstractDigitalActionSwing {


    //@Override
    /*protected*/ void TriggerRouteSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
    TriggerRoute* action = (TriggerRoute*)object->bself();

        panel = new JPanel(new FlowLayout);

        _tabbedPaneRoute = new JTabbedPane();
        _panelRouteDirect = new JPanel(new FlowLayout);
        _panelRouteReference = new JPanel(new FlowLayout);
        _panelRouteLocalVariable = new JPanel(new FlowLayout);
        _panelRouteFormula = new JPanel(new FlowLayout);

        _tabbedPaneRoute->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Direct), _panelRouteDirect);
        _tabbedPaneRoute->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Reference), _panelRouteReference);
        _tabbedPaneRoute->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::LocalVariable), _panelRouteLocalVariable);
        _tabbedPaneRoute->addTab(NamedBeanAddressing::toString(NamedBeanAddressing::Formula), _panelRouteFormula);

        routeBeanPanel = new BeanSelectPanel(((AbstractRouteManager*)InstanceManager::getDefault("RouteManager")), nullptr);
        _panelRouteDirect->layout()->addWidget(routeBeanPanel);

        _routeReferenceTextField = new JTextField();
        _routeReferenceTextField->setColumns(30);
        _panelRouteReference->layout()->addWidget(_routeReferenceTextField);

        _routeLocalVariableTextField = new JTextField();
        _routeLocalVariableTextField->setColumns(30);
        _panelRouteLocalVariable->layout()->addWidget(_routeLocalVariableTextField);

        _routeFormulaTextField = new JTextField();
        _routeFormulaTextField->setColumns(30);
        _panelRouteFormula->layout()->addWidget(_routeFormulaTextField);


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
        for (TriggerRoute::Operation::TYPE e : TriggerRoute::Operation::values()) {
            _stateComboBox->addItem(TriggerRoute::Operation::toString(e),e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_stateComboBox);

        _panelOperationDirect->layout()->addWidget(_stateComboBox);

        _routeLockReferenceTextField = new JTextField();
        _routeLockReferenceTextField->setColumns(30);
        _panelOperationReference->layout()->addWidget(_routeLockReferenceTextField);

        _routeLockLocalVariableTextField = new JTextField();
        _routeLockLocalVariableTextField->setColumns(30);
        _panelOperationLocalVariable->layout()->addWidget(_routeLockLocalVariableTextField);

        _routeLockFormulaTextField = new JTextField();
        _routeLockFormulaTextField->setColumns(30);
        _panelOperationFormula->layout()->addWidget(_routeLockFormulaTextField);


        if (action != nullptr) {
            switch (action->getAddressing()) {
            case NamedBeanAddressing::Direct: _tabbedPaneRoute->setSelectedComponent(_panelRouteDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneRoute->setSelectedComponent(_panelRouteReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneRoute->setSelectedComponent(_panelRouteLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneRoute->setSelectedComponent(_panelRouteFormula); break;
            default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            if (action->getRoute() != nullptr) {
                routeBeanPanel->setDefaultNamedBean(action->getRoute()->getBean());
            }
            _routeReferenceTextField->setText(action->getReference());
            _routeLocalVariableTextField->setText(action->getLocalVariable());
            _routeFormulaTextField->setText(action->getFormula());

            switch (action->getOperationAddressing()) {
                case NamedBeanAddressing::Direct: _tabbedPaneOperation->setSelectedComponent(_panelOperationDirect); break;
            case NamedBeanAddressing::Reference: _tabbedPaneOperation->setSelectedComponent(_panelOperationReference); break;
            case NamedBeanAddressing::LocalVariable: _tabbedPaneOperation->setSelectedComponent(_panelOperationLocalVariable); break;
            case NamedBeanAddressing::Formula: _tabbedPaneOperation->setSelectedComponent(_panelOperationFormula); break;
                default: throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(action->getAddressing()));
            }
            _stateComboBox->setSelectedItem(action->getOperationDirect());
            _routeLockReferenceTextField->setText(action->getOperationReference());
            _routeLockLocalVariableTextField->setText(action->getOperationLocalVariable());
            _routeLockFormulaTextField->setText(action->getLockFormula());
        }

        QList<JComponent*> components =  QList<JComponent*>{
            _tabbedPaneRoute,
            _tabbedPaneOperation};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Trigger route {0} to {1}"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget((QWidget*)c->jself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool TriggerRouteSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary action to test formula
        TriggerRoute* action = new TriggerRoute("IQDA1", "");

        try {
            if (_tabbedPaneRoute->getSelectedComponent() == _panelRouteReference) {
                action->setReference(_routeReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationReference) {
                action->setOperationReference(_routeLockReferenceTextField->text());
            }
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        try {
            action->setFormula(_routeFormulaTextField->text());
            if (_tabbedPaneRoute->getSelectedComponent() == _panelRouteDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneRoute->getSelectedComponent() == _panelRouteReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
            } else if (_tabbedPaneRoute->getSelectedComponent() == _panelRouteLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
            } else if (_tabbedPaneRoute->getSelectedComponent() == _panelRouteFormula) {
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
    /*public*/ MaleSocket*TriggerRouteSwing:: createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        TriggerRoute* action = new TriggerRoute(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void TriggerRouteSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<TriggerRoute*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object must be an TriggerRoute but is a: ")+object->bself()->metaObject()->className());
        }
        TriggerRoute* action = (TriggerRoute*)object->bself();
        if (_tabbedPaneRoute->getSelectedComponent() == _panelRouteDirect) {
            Route* route = (Route*)routeBeanPanel->getNamedBean()->self();
            if (route != nullptr) {
                NamedBeanHandle<Route*>* handle
                        = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                                ->getNamedBeanHandle(route->getDisplayName(), route);
                action->setRoute(handle);
            } else {
                action->removeRoute();
            }
        } else {
            action->removeRoute();
        }
        try {
            if (_tabbedPaneRoute->getSelectedComponent() == _panelRouteDirect) {
                action->setAddressing(NamedBeanAddressing::Direct);
            } else if (_tabbedPaneRoute->getSelectedComponent() == _panelRouteReference) {
                action->setAddressing(NamedBeanAddressing::Reference);
                action->setReference(_routeReferenceTextField->text());
            } else if (_tabbedPaneRoute->getSelectedComponent() == _panelRouteLocalVariable) {
                action->setAddressing(NamedBeanAddressing::LocalVariable);
                action->setLocalVariable(_routeLocalVariableTextField->text());
            } else if (_tabbedPaneRoute->getSelectedComponent() == _panelRouteFormula) {
                action->setAddressing(NamedBeanAddressing::Formula);
                action->setFormula(_routeFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneRoute has unknown selection");
            }

            if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationDirect) {
                action->setOperationAddressing(NamedBeanAddressing::Direct);
                action->setOperationDirect((TriggerRoute::Operation::TYPE)_stateComboBox->getItemAt(_stateComboBox->getSelectedIndex()).toInt());
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationReference) {
                action->setOperationAddressing(NamedBeanAddressing::Reference);
                action->setOperationReference(_routeLockReferenceTextField->text());
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationLocalVariable) {
                action->setOperationAddressing(NamedBeanAddressing::LocalVariable);
                action->setOperationLocalVariable(_routeLockLocalVariableTextField->text());
            } else if (_tabbedPaneOperation->getSelectedComponent() == _panelOperationFormula) {
                action->setOperationAddressing(NamedBeanAddressing::Formula);
                action->setOperationFormula(_routeLockFormulaTextField->text());
            } else {
                throw new IllegalArgumentException("_tabbedPaneRoute has unknown selection");
            }
        } catch (ParserException* e) {
            throw new RuntimeException("ParserException: "+e->getMessage(), e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString TriggerRouteSwing::toString() {
        return tr("TriggerRoute");
    }

    //@Override
    /*public*/ void TriggerRouteSwing::dispose() {
        if (routeBeanPanel != nullptr) {
            routeBeanPanel->dispose();
        }
    }

