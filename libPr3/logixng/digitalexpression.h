#ifndef DIGITALEXPRESSION_H
#define DIGITALEXPRESSION_H
#include "base.h"

/**
 * DigitalExpressionBean is used in LogixNG to answer a question that can give
 * the answers 'true' or 'false'.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class DigitalExpression : public Base {
public:
    /**
     * Evaluate this expression.
     *
     * @return the result of the evaluation
     * @throws JmriException when an exception occurs
     */
    /*public*/virtual  bool evaluate() /*throws JmriException*/=0;

};
Q_DECLARE_INTERFACE(DigitalExpression, "DigitalExpression")
#endif // DIGITALEXPRESSION_H
