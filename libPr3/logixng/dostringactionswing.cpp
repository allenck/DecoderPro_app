#include "dostringactionswing.h"
#include "instancemanager.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/dostringaction.h"

DoStringActionSwing::DoStringActionSwing(QObject *parent)
    : AbstractDigitalActionSwing{parent}
{
 setObjectName("DoStringActionSwing");
}
/**
 * Configures an ActionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class DoStringActionSwing extends AbstractDigitalActionSwing {

    //@Override
    /*protected*/ void DoStringActionSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        panel = new JPanel();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool DoStringActionSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ MaleSocket* DoStringActionSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        DoStringAction* action = new DoStringAction(systemName, userName);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DoStringActionSwing::updateObject(/*@Nonnull*/ Base* object) {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString DoStringActionSwing::toString() {
        return tr("DoStringAction");
    }

    //@Override
    /*public*/ void DoStringActionSwing::dispose() {
    }
