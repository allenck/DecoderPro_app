#ifndef DIGITALEXPRESSIONBEAN_H
#define DIGITALEXPRESSIONBEAN_H
#include "namedbean.h"
#include "digitalexpression.h"

/**
 * DigitalExpressionBean is a DigitalExpression that also implements NamedBean.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class DigitalExpressionBean : public NamedBean, public DigitalExpression {
    Q_OBJECT
  Q_INTERFACES(DigitalExpression)
    /**
     * Constant representing an "false" state. It's returned from the method
     * getState() if the method evaluate() returned false the last time it was
     * called.
     */
    /*public*/ static /*final*/const  int FALSE = 0x02;

    /**
     * Constant representing an "false" state. It's returned from the method
     * getState() if the method evaluate() returned false the last time it was
     * called.
     */
    /*public*/ static /*final*/const int TRUE = 0x04;

    /**
     * Notify property change listeners that the result of the expression
     * has changed.
     * @param oldResult the old last result
     * @param newResult the new last result
     */
    /*public*/ virtual void notifyChangedResult(bool oldResult, bool newResult)=0;

};

#endif // DIGITALEXPRESSIONBEAN_H
