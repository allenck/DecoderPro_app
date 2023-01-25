#include "actionpowerswing.h"
#include "instancemanager.h"
#include "actionpower.h"
#include "jcombobox.h"
#include "swingconfiguratorinterface.h"
#include "defaultdigitalactionmanager.h"

ActionPowerSwing::ActionPowerSwing(QObject *parent) : AbstractDigitalActionSwing(parent)
{
 setObjectName("ActionPowerSwing");
}

/**
 * Configures an ActionPower object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class ActionPowerSwing extends AbstractDigitalActionSwing {



    //@Override
    /*protected*/ void ActionPowerSwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ActionPower* action = nullptr;
        if(object) action = (ActionPower*)object->bself();

        panel = new JPanel(new FlowLayout());

        _stateComboBox = new JComboBox();
        for (ActionPower::PowerState::STATE e : ActionPower::PowerState::values()) {
            _stateComboBox->addItem(ActionPower::PowerState::toString(e), e);
        }
//        JComboBoxUtil.setupComboBoxMaxRows(_stateComboBox);

        if (action != nullptr) {
            _stateComboBox->setSelectedItem(action->getBeanState());
        }

        QList<JComponent*> components = QList<JComponent*>{
            _stateComboBox};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Turn power %1"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget(c->jself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ActionPowerSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ActionPowerSwing::getAutoSystemName() {
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->getAutoSystemName();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* ActionPowerSwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        ActionPower* action = new ActionPower(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionPowerSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ActionPower*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ActionPower but is a: ")+object->bself()->metaObject()->className());
        }
        ActionPower* action = (ActionPower*)object->bself();
        action->setBeanState((ActionPower::PowerState::STATE)_stateComboBox->getItemAt(_stateComboBox->getSelectedIndex()).toInt());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ActionPowerSwing::toString() {
        return tr("Power");
    }

    //@Override
    /*public*/  void ActionPowerSwing::dispose() {
    }
