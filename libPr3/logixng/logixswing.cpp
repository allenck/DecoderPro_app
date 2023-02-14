#include "logixswing.h"
#include "actions/act_logix.h"
#include "instancemanager.h"
#include "defaultdigitalactionmanager.h"

LogixSwing::LogixSwing(QObject *parent)
{

}
/**
 * Configures an ActionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class LogixSwing extends AbstractDigitalActionSwing {

    //@Override
    /*protected*/ void LogixSwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        panel = new JPanel(new FlowLayout);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool LogixSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* LogixSwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        Actions::Logix* action = new Actions::Logix(systemName, userName);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void LogixSwing::updateObject(/*@Nonnull*/ Base* object) {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString LogixSwing::toString() {
        return tr("Logix");
    }

    //@Override
    /*public*/  void LogixSwing::dispose() {
    }
