#include "loglocalvariablesswing.h"
#include "instancemanager.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/loglocalvariables.h"

LogLocalVariablesSwing::LogLocalVariablesSwing(QObject *parent)
    : AbstractDigitalActionSwing{parent}
{

}
/**
 * Configures an LogLocalVariables object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class LogLocalVariablesSwing extends AbstractDigitalActionSwing {

    //@Override
    /*protected*/ void LogLocalVariablesSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        panel = new JPanel();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool LogLocalVariablesSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ MaleSocket* LogLocalVariablesSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        LogLocalVariables* action = new LogLocalVariables(systemName, userName);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void LogLocalVariablesSwing::updateObject(/*@Nonnull*/ Base* object) {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString LogLocalVariablesSwing::toString() {
        return tr("LogLocalVariables");
    }

    //@Override
    /*public*/ void LogLocalVariablesSwing::dispose() {
    }
