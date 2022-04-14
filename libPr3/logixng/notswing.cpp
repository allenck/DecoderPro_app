#include "notswing.h"
#include "defaultdigitalexpressionmanager.h"
#include "not.h"
#include "instancemanager.h"

NotSwing::NotSwing(QObject *parent) : AbstractDigitalExpressionSwing(parent)
{
 setObjectName("NotSwing");
}

/**
 * Configures an Not object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright (C) 2021
 */
///*public*/  class NotSwing extends AbstractDigitalExpressionSwing {

    //@Override
    /*protected*/ void NotSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        panel = new JPanel(new FlowLayout());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool NotSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* NotSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        Not* expression = new Not(systemName, userName);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void NotSwing::updateObject(/*@Nonnull*/ Base* object) {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString NotSwing::toString() {
        return tr("Not");
    }

    //@Override
    /*public*/  void NotSwing::dispose() {
    }
