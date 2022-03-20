#ifndef INVALIDCONDITIONALVARIABLEEXCEPTION_H
#define INVALIDCONDITIONALVARIABLEEXCEPTION_H
#include "jmriexception.h"

/**
 * Exception thrown when the ConditionalVariable has invalid data.
 *
 * @author Daniel Bergqvist Copyright (C) 2020
 */
/*public*/ class InvalidConditionalVariableException : public JmriException {
public:
    /*public*/ InvalidConditionalVariableException(QString s, Throwable* t) : JmriException(s,t){
        //super(s, t);
    }

    /*public*/ InvalidConditionalVariableException(QString s): JmriException(s) {
        //super(s);
    }

    /*public*/ InvalidConditionalVariableException(Throwable* t) : JmriException(t){
        //super(t);
    }

    /*public*/ InvalidConditionalVariableException(): JmriException() {
    }

};
#endif // INVALIDCONDITIONALVARIABLEEXCEPTION_H
