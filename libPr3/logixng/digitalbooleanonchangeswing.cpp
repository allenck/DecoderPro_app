#include "digitalbooleanonchangeswing.h"
#include "digitalbooleanonchange.h"
#include "defaultdigitalbooleanactionmanager.h"
#include "instancemanager.h"

/**
 * Configures an ActionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class DigitalBooleanOnChangeSwing extends AbstractBooleanActionSwing {


    //@Override
    /*protected*/ void DigitalBooleanOnChangeSwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        DigitalBooleanOnChange* action = (DigitalBooleanOnChange*)object->bself();

        panel = new JPanel(new FlowLayout());
        _triggerComboBox = new JComboBox();
        for (DigitalBooleanOnChange::Trigger::TargetAction e : DigitalBooleanOnChange::Trigger::values()) {
            _triggerComboBox->addItem(DigitalBooleanOnChange::Trigger::toString(e), e);
        }
//        JComboBoxUtil.setupComboBoxMaxRows(_triggerComboBox);
        panel->layout()->addWidget(_triggerComboBox);
        if (action != nullptr) {
            _triggerComboBox->setSelectedItem(action->getTrigger());
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DigitalBooleanOnChangeSwing::validate(/*@Nonnull*/ QList<QString> errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* DigitalBooleanOnChangeSwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        DigitalBooleanOnChange* action = new DigitalBooleanOnChange(systemName, userName, type);
        updateObject(action);
        return ((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DigitalBooleanOnChangeSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<DigitalBooleanOnChange*>(object->bself())) ){
            throw new IllegalArgumentException(QString("object must be an DigitalBooleanOnChange but is a: ")+object->bself()->metaObject()->className());
        }
        DigitalBooleanOnChange* action = (DigitalBooleanOnChange*)object->bself();
        //action->setTrigger(_triggerComboBox->getItemAt(_triggerComboBox->getSelectedIndex()).toInt());
        action->setTrigger(DigitalBooleanOnChange::Trigger::toTargetAction(_triggerComboBox->currentText()));
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DigitalBooleanOnChangeSwing::toString() {
        return tr("On change");
    }

    //@Override
    /*public*/  void DigitalBooleanOnChangeSwing::dispose() {
    }