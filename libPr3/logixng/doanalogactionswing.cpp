#include "doanalogactionswing.h"
#include "instancemanager.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/doanalogaction.h"

DoAnalogActionSwing::DoAnalogActionSwing(QObject *parent)
    : AbstractDigitalActionSwing{parent}
{

}
/**
 * Configures an ActionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class DoAnalogActionSwing extends AbstractDigitalActionSwing {

    //@Override
    /*protected*/ void DoAnalogActionSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        panel = new JPanel();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool DoAnalogActionSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ MaleSocket* DoAnalogActionSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        DoAnalogAction* action = new DoAnalogAction(systemName, userName);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DoAnalogActionSwing::updateObject(/*@Nonnull*/ Base* object) {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString DoAnalogActionSwing::toString() {
        return tr("DoAnalogAction");
    }

    //@Override
    /*public*/ void DoAnalogActionSwing::dispose() {
    }
