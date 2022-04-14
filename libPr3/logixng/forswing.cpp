#include "forswing.h"
#include "instancemanager.h"
#include "defaultdigitalactionmanager.h"
#include "for.h"

/**
 * Configures an ActionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class ForSwing extends AbstractDigitalActionSwing {

    //@Override
    /*protected*/ void ForSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        panel = new JPanel(new FlowLayout());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ForSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* ForSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        For* action = new For(systemName, userName);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ForSwing::updateObject(/*@Nonnull*/ Base* object) {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ForSwing::toString() {
        return tr("For");
    }

    //@Override
    /*public*/  void ForSwing::dispose() {
    }
