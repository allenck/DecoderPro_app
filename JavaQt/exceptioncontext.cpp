#include "exceptioncontext.h"

/**
 * Wraps an Exception and allows extra contextual information to be added, such
 * as what was happening at the time of the Exception, and a hint as to what the
 * user might do to correct the problem. Also implements a number of methods to
 * format the data of an Exception.
 *
 * @author Gregory Madsen Copyright (C) 2012
 *
 */
// /*public*/  class ExceptionContext {


    // The Exception being wrapped
    /*public*/  Exception* ExceptionContext::getException() {
        return _exception;
    }

    /*public*/  QString ExceptionContext::getPreface() {
        return _preface;
    }

    /*public*/  QString ExceptionContext::getOperation() {
        return _operation;
    }

    /*public*/  QString ExceptionContext::getHint() {
        return _hint;
    }

    /*public*/  QString ExceptionContext::getTitle() {
        // May be overridden in derived classes
        return _exception->name;//getClass().getSimpleName();
    }

    /**
     * Returns a user friendly summary of the Exception. Empty parts are not
     * included. (Maybe later?)
     * @return A string summary.
     */
    /*public*/  QString ExceptionContext::getSummary() {
        return _preface + _nl + _operation + _nl + _exception->getMessage() + _nl + _hint;
    }

    /*public*/  ExceptionContext::ExceptionContext(Exception* ex, QString operation, QString hint, QObject* parent) : QObject(parent) {
        this->_exception = ex;
        this->_operation = operation;
        this->_hint = hint;
    }
#if 0
    /**
     * Returns up to the given number of stack trace elements concatenated into
     * one string.
     * @param maxLevels The number of stack trace elements to return.
     * @return A string stack trace.
     *
     */
    /*public*/  QString getStackTraceAsString(int maxLevels) {
        QString eol = System.getProperty("line.separator"); // NOI18N
        StringBuilder sb = new StringBuilder();

        StackTraceElement[] stElements = _exception.getStackTrace();

        int limit = Math.min(maxLevels, stElements.length);
        for (int i = 0; i < limit; i++) {
            sb.append(" at "); // NOI18N
            sb.append(stElements[i].toString());
            sb.append(eol);
        }

        // If there are more levels than included, add a note to the end
        if (stElements.length > limit) {
            sb.append(" plus "); // NOI18N
            sb.append(stElements.length - limit);
            sb.append(" more."); // NOI18N
        }
        return sb.toString();
    }

    /*public*/  String getStackTraceString() {
        return getStackTraceAsString(Integer.MAX_VALUE);
    }
#endif

