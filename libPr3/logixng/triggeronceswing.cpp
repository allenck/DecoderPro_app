#include "triggeronceswing.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "triggeronce.h"

/**
 * Configures an ExpressionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class TriggerOnceSwing extends AbstractDigitalExpressionSwing {

    //@Override
    /*protected*/ void TriggerOnceSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        panel = new JPanel(new FlowLayout);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool TriggerOnceSwing::validate(/*@Nonnull*/ QList<QString> errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* TriggerOnceSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        TriggerOnce* expression = new TriggerOnce(systemName, "");
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void TriggerOnceSwing::updateObject(/*@Nonnull*/ Base* object) {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString TriggerOnceSwing::toString() {
        return tr("TriggerOnce");
    }

    //@Override
    /*public*/  void TriggerOnceSwing::dispose() {
    }
