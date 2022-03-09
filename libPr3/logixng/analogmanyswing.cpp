#include "analogmanyswing.h"
#include "instancemanager.h"
#include "defaultanalogactionmanager.h"
#include "analogmany.h"

/**
 * Configures an ActionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
//public*/  class AnalogManySwing extends AbstractAnalogActionSwing {

    //@Override
    /*protected*/ void AnalogManySwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        panel = new JPanel();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool AnalogManySwing::validate(/*@Nonnull*/ QList<QString> errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* AnalogManySwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        AnalogMany* action = new AnalogMany(systemName, userName);
        return ((DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogManySwing::updateObject(/*@Nonnull*/ Base* object) {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AnalogManySwing::toString() {
        return tr("Many");
    }

    //@Override
    /*public*/  void AnalogManySwing::dispose() {
    }
