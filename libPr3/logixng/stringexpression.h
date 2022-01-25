#ifndef STRINGEXPRESSION_H
#define STRINGEXPRESSION_H
#include "base.h"

/**
 * String expression is used in LogixNG to answer a question that can give
 * a string value as result.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class  StringExpression : public Base {

  Q_INTERFACES(Base)
 public:
    /**
     * Evaluate this expression.
     *
     * @return the result of the evaluation
     * @throws JmriException when an exception occurs
     */
    /*public*/ virtual QString evaluate() /*throws JmriException*/=0;

    /**
     * Set whenether this expression should trigger the ConditionalNG if the
     * named beans it listens to changes state.
     * @param triggerOnChange true if trigger on change, false otherwise
     */
    /*public*/ virtual void setTriggerOnChange(bool triggerOnChange)=0;

    /**
     * Get whenether this expression should trigger the ConditionalNG if the
     * named beans it listens to changes state.
     * @return true if trigger on change, false otherwise
     */
    /*public*/virtual bool getTriggerOnChange()=0;

};
Q_DECLARE_INTERFACE(StringExpression, "StringExpression")
#endif // STRINGEXPRESSION_H
