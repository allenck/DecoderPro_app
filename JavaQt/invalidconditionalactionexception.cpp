#include "invalidconditionalactionexception.h"

/**
 * Exception thrown when the ConditionalVariable has invalid data.
 *
 * @author Daniel Bergqvist Copyright (C) 2020
 */
// /*public*/ class InvalidConditionalActionException extends JmriException {

    /*public*/ InvalidConditionalActionException::InvalidConditionalActionException(QString s, Throwable* t) : JmriException(s,t){
        //super(s, t);
    }

    /*public*/ InvalidConditionalActionException::InvalidConditionalActionException(QString s) : JmriException(s){
        //super(s);
    }

    /*public*/ InvalidConditionalActionException::InvalidConditionalActionException(Throwable* t) : JmriException(t){
        //super(t);
    }

    /*public*/ InvalidConditionalActionException::InvalidConditionalActionException() {
    }
