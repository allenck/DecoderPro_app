#include "trueswing.h"
#include "defaultdigitalexpressionmanager.h"
#include "instancemanager.h"
#include "true.h"

/**
 * Configures an ExpressionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class TrueSwing extends AbstractDigitalExpressionSwing {

    //@Override
    /*protected*/ void TrueSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        panel = new JPanel();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool TrueSwing::validate(/*@Nonnull*/ QList<QString> *errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* TrueSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        True* expression = new True(systemName, userName);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void TrueSwing::updateObject(/*@Nonnull*/ Base* object) {
        // Nothing to update
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString TrueSwing::toString() {
        return tr("True");
    }

    //@Override
    /*public*/  void TrueSwing::dispose() {
    }
