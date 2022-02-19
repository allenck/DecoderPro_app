#ifndef STRINGACTION_H
#define STRINGACTION_H
#include "base.h"

/**
 * A LogixNG string action.
 *
 * @author Daniel Bergqvist Copyright 2019
 */
/*public*/ /*interface*/class StringAction : public virtual Base {
 public:
Q_INTERFACES(Base)
    /**
     * Set a string value.
     *
     * @param value the value.
     * @throws JmriException when an exception occurs
     */
    /*public*/ virtual void setValue(/*@Nonnull*/ QString value) /*throws JmriException*/=0;

};
Q_DECLARE_INTERFACE(StringAction, "StringAction")
#endif // STRINGACTION_H
