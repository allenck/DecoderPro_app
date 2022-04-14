#include "digitalmanyswing.h"
#include "defaultdigitalactionmanager.h"
#include "instancemanager.h"
#include "digitalmany.h"

/**
 * Configures an ActionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class DigitalManySwing extends AbstractDigitalActionSwing {

    //@Override
    /*protected*/ void DigitalManySwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        panel = new JPanel(new FlowLayout());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DigitalManySwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* DigitalManySwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        DigitalMany* action = new DigitalMany(systemName, userName);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DigitalManySwing::updateObject(/*@Nonnull*/ Base* object) {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DigitalManySwing::toString() {
        return tr("Many");
    }

    //@Override
    /*public*/  void DigitalManySwing::dispose() {
    }
