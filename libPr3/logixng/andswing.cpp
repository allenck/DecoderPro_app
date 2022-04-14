#include "andswing.h"
#include "defaultdigitalexpressionmanager.h"
#include "and.h"
#include "instancemanager.h"
/**
 * Configures an ExpressionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class AndSwing extends AbstractDigitalExpressionSwing {

    //@Override
    /*protected*/ void AndSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        panel = new JPanel();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool AndSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* AndSwing::createNewObject(/*@Nonnull */QString systemName, /*@CheckForNull*/ QString userName) {
        And* expression = new And(systemName, userName);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AndSwing::updateObject(/*@Nonnull*/ Base* object) {
        // Nothing to update
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AndSwing::toString() {
        return tr("And");
    }

    //@Override
    /*public*/  void AndSwing::dispose() {
    }
