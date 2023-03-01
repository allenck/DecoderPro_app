#include "actionthrottleswing.h"
#include "instancemanager.h"
#include "logixng/actionthrottle.h"
#include "logixng/defaultdigitalactionmanager.h"

ActionThrottleSwing::ActionThrottleSwing(QObject *parent)
    : AbstractDigitalActionSwing{parent}
{

}
/**
 * Configures an ActionThrottle object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class ActionThrottleSwing extends AbstractDigitalActionSwing {

    //@Override
    /*protected*/ void ActionThrottleSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        panel = new JPanel(new FlowLayout);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ActionThrottleSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ MaleSocket* ActionThrottleSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ActionThrottle* action = new ActionThrottle(systemName, userName);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionThrottleSwing::updateObject(/*@Nonnull*/ Base* object) {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ActionThrottleSwing::toString() {
        return ("ActionThrottle");
    }

    //@Override
    /*public*/ void ActionThrottleSwing::dispose() {
    }
