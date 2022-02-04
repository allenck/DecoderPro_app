#ifndef ANALOGEXPRESSION_H
#define ANALOGEXPRESSION_H
#include "base.h"

/**
 * Analog expression is used in LogixNG to answer a question that can give
 * an analog value as result.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class  AnalogExpression : public Base {

    Q_INTERFACES(Base)
    /**
     * Evaluate this expression.
     *
     * @return the result of the evaluation. The male socket that holds this
     * expression throws an exception if this value is a Double.NaN or an
     * infinite number.
     *
     * @throws jmri.JmriException when an exception occurs
     */
    /*public*/ virtual double evaluate() /*throws JmriException*/=0;

    /**
     * Set whenether this expression should trigger the ConditionalNG if the
     * named beans it listens to changes state.
     * @param triggerOnChange true if trigger on change, false otherwise
     */
    /*public*/ virtual void setTriggerOnChange(bool triggerOnChange) =0;

    /**
     * Get whenether this expression should trigger the ConditionalNG if the
     * named beans it listens to changes state.
     * @return true if trigger on change, false otherwise
     */
    /*public*/ virtual bool getTriggerOnChange()=0;

};
Q_DECLARE_INTERFACE(AnalogExpression, "AnalogExpression")
#endif // ANALOGEXPRESSION_H
