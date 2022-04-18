#include "stringexpressionconstantswing.h"
#include "stringexpressionconstant.h"
#include "jlabel.h"
#include "instancemanager.h"
#include "defaultstringexpressionmanager.h"

StringExpressionConstantSwing::StringExpressionConstantSwing(QObject *parent) : AbstractStringExpressionSwing(parent)
{
 setObjectName("StringExpressionConstantSwing");
}

/**
 * Configures an StringExpressionConstant object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class StringExpressionConstantSwing extends AbstractStringExpressionSwing {


    //@Override
    /*protected*/ void StringExpressionConstantSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        StringExpressionConstant* expression = (StringExpressionConstant*)object->bself();
        panel = new JPanel();
        JLabel* label = new JLabel(tr("Constant"));
        _constant = new JTextField();
        _constant->setColumns(20);
        if (expression != nullptr) _constant->setText(expression->getValue());
        panel->layout()->addWidget(label);
        panel->layout()->addWidget(_constant);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool StringExpressionConstantSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* StringExpressionConstantSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        StringExpressionConstant* expression = new StringExpressionConstant(systemName, userName);
        updateObject(expression);
        return ((DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void StringExpressionConstantSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (!(qobject_cast<StringExpressionConstant*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object must be an StringExpressionConstant but is a: ")+object->bself()->metaObject()->className());
        }

        StringExpressionConstant* expression = (StringExpressionConstant*)object->bself();

        if (!_constant->text().isEmpty()) {
            expression->setValue(_constant->text());
        } else {
            expression->setValue("");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString StringExpressionConstantSwing::toString() {
        return tr("String constant");
    }

    //@Override
    /*public*/  void StringExpressionConstantSwing::dispose() {
    }
