#ifndef ANALOGACTION_H
#define ANALOGACTION_H
#include "base.h"

/**
 * A LogixNG analog action.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/ class AnalogAction : public virtual Base {
public:
  Q_INTERFACES()
    /**
     * Set an analog value.
     *
     * @param value the value. The male socket that holds this action ensures
     * that this value is not Double.NaN or an infinite value.
     * @thrBaseows JmriException when an exception occurs
     */
    /*public*/ virtual void setValue(double value) /*throws JmriException*/=0;

};
Q_DECLARE_INTERFACE(AnalogAction, "AnalogAction")
#endif // ANALOGACTION_H
