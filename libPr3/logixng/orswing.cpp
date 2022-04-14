#include "orswing.h"
#include "or.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"

/**
 * Configures an ExpressionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class OrSwing extends AbstractDigitalExpressionSwing {

    //@Override
    /*protected*/ void OrSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        panel = new JPanel();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool OrSwing::validate(/*@Nonnull*/ QList<QString> *errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* OrSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        Or* expression = new Or(systemName, userName);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void OrSwing::updateObject(/*@Nonnull*/ Base* object) {
        // Nothing to update
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString OrSwing::toString() {
        return tr("Or");
    }

    //@Override
    /*public*/  void OrSwing::dispose() {
    }
