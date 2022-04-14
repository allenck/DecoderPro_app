#include "analogexpressionconstantswing.h"
#include "analogexpressionconstant.h"
#include "jlabel.h"
#include "jtextfield.h"
#include "defaultanalogexpressionmanager.h"
#include "instancemanager.h"

/**
 * Configures an ActionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class AnalogExpressionConstantSwing extends AbstractAnalogExpressionSwing {


//@Override
/*protected*/ void AnalogExpressionConstantSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
    AnalogExpressionConstant* expression = nullptr;
    if(object)
     expression = (AnalogExpressionConstant*)object->bself();
    panel = new JPanel(new FlowLayout);
    JLabel* label = new JLabel(tr("Constant"));
    _constant = new JTextField();
    _constant->setColumns(10);
    if (expression != nullptr) _constant->setText(QString("%1").arg(expression->getValue(),2,'g'));
    panel->layout()->addWidget(label);
    panel->layout()->addWidget(_constant);
}

/** {@inheritDoc} */
//@Override
/*public*/  bool AnalogExpressionConstantSwing::validate(/*@Nonnull*/ QList<QString> *errorMessages) {
    if (_constant->text().isEmpty()) return true;

    bool ok;
        _constant->text().toDouble(&ok);
    if(!ok) {
        errorMessages->append(tr("The value \"%1\" is not a number").arg(_constant->text()));
        return false;
    }
    return true;
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket* AnalogExpressionConstantSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
    AnalogExpressionConstant* expression = new AnalogExpressionConstant(systemName, userName);
    updateObject(expression);
    return ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(expression);
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogExpressionConstantSwing::updateObject(/*@Nonnull*/ Base* object) {
    if (!(qobject_cast<AnalogExpressionConstant*>(object->bself()))) {
        throw new IllegalArgumentException(QString("object must be an AnalogExpressionConstant but is a: ") + object->bself()->metaObject()->className());
    }

    AnalogExpressionConstant* expression = (AnalogExpressionConstant*)object->bself();

    if (!_constant->text().isEmpty()) {
        expression->setValue(_constant->text().toDouble());
    } else {
        expression->setValue(0.0);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  QString AnalogExpressionConstantSwing::toString() {
    return tr("Analog constant");
}

//@Override
/*public*/  void AnalogExpressionConstantSwing::dispose() {
}
