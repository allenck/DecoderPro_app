#include "jmriexception.h"

/**
 * Base for JMRI-specific exceptions. No functionality, just used to confirm
 * type-safety.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2008, 2010
 */
// /*public*/  class JmriException extends Exception {


    /*public*/  JmriException::JmriException(QString s, Throwable* t) : Exception(s, t) {
        //super(s, t);
        errors = QList<QString>();
        name = "JmriException";
    }

    /*public*/  JmriException::JmriException(QString s) : Exception(s){
        //super(s);
        errors = QList<QString>();
        name = "JmriException";
    }

    /*public*/  JmriException::JmriException(Throwable* t) : Exception(t){
        //super(t);
        errors = QList<QString>();
        name = "JmriException";
    }

    /*public*/  JmriException::JmriException() {
        errors = QList<QString>();
        name = "JmriException";
    }

    /*public*/  JmriException::JmriException(QString s, QList<QString> errors) : Exception(s){
        //super(s);
        this->errors =QList<QString>(errors);
        name = "JmriException";
    }

    /*public*/  JmriException::JmriException(QString s, QList<QString> errors, Throwable* t): Exception(s, t) {
        //super(s, t);
        this->errors =QList<QString>(errors);
        name = "JmriException";
    }

    /*public*/  QList<QString> JmriException::getErrors() {
        return errors;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString JmriException::getMessage() {
        if (!errors.isEmpty()) {
            return Exception::getMessage() + ": " + errors.join(", ");
        } else {
            return Exception::getMessage();
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString JmriException::getLocalizedMessage() {
        if (!errors.isEmpty()) {
            return Exception::getLocalizedMessage() + ": " + errors.join(", ");
        } else {
            return Exception::getLocalizedMessage();
        }
    }
