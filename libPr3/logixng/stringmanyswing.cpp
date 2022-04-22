#include "stringmanyswing.h"
#include "instancemanager.h"
#include "defaultstringactionmanager.h"
#include "stringmany.h"

StringManySwing::StringManySwing(QObject *parent) : AbstractStringActionSwing(parent)
{
 setObjectName("StringMany");
}
/**
 * Configures an ActionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class StringManySwing extends AbstractStringActionSwing {

    //@Override
    /*protected*/ void StringManySwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        panel = new JPanel(new FlowLayout);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool StringManySwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@OverrideQ
    /*public*/  MaleSocket* StringManySwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        StringMany* action = new StringMany(systemName, userName);
        return ((DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void StringManySwing::updateObject(/*@Nonnull*/ Base* object) {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString StringManySwing::toString() {
        return tr("Many");
    }

    //@Override
    /*public*/  void StringManySwing::dispose() {
    }
