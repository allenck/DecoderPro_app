#include "falseswing.h"
#include "false.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"

/**
 * Configures an ExpressionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class FalseSwing extends AbstractDigitalExpressionSwing {

    //@Override
    /*protected*/ void FalseSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        panel = new JPanel(new FlowLayout());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool FalseSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* FalseSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        False* expression = new False(systemName, userName);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void FalseSwing::updateObject(/*@Nonnull*/ Base* object) {
        // Nothing to update
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString FalseSwing::toString() {
        return tr("False");
    }

    //@Override
    /*public*/  void FalseSwing::dispose() {
    }
