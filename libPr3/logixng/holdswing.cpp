#include "holdswing.h"
#include "hold.h"
#include "defaultdigitalexpressionmanager.h"
#include "instancemanager.h"

HoldSwing::HoldSwing(QObject *parent) : AbstractDigitalExpressionSwing(parent)
{
 setObjectName("HoldSwing");
}
/**
 * Configures an ExpressionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class HoldSwing extends AbstractDigitalExpressionSwing {

    //@Override
    /*protected*/ void HoldSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        panel = new JPanel(new FlowLayout());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool HoldSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* HoldSwing::createNewObject(/*@Nonnull */QString systemName, /*@CheckForNull*/ QString userName) {
        Hold* expression = new Hold(systemName, userName);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void HoldSwing::updateObject(/*@Nonnull*/ Base* object) {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString HoldSwing::toString() {
        return tr("Hold");
    }

    //@Override
    /*public*/  void HoldSwing::dispose() {
    }
