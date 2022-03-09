#include "digitalbooleanmanyswing.h"
#include "instancemanager.h"
#include "defaultdigitalbooleanactionmanager.h"
#include "digitalbooleanmany.h"

/**
 * Configures an ActionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class DigitalBooleanManySwing extends AbstractBooleanActionSwing {

    //@Override
    /*protected*/ void DigitalBooleanManySwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        panel = new JPanel();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DigitalBooleanManySwing::validate(/*@Nonnull*/ QList<QString> errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* DigitalBooleanManySwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        DigitalBooleanMany* action = new DigitalBooleanMany(systemName, userName);
        return ((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DigitalBooleanManySwing::updateObject(/*@Nonnull*/ Base* object) {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DigitalBooleanManySwing::toString() {
        return tr("Many");
    }

    //@Override
    /*public*/  void DigitalBooleanManySwing::dispose() {
    }
