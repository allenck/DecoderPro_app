#include "unexpectedexceptioncontext.h"

/**
 * Extends ExceptionContext class for exceptions that are not expected, and
 * therefore have no suggestions for the user.
 *
 * @author Gregory Madsen Copyright (C) 2012
 *
 */
// /*public*/ class UnexpectedExceptionContext extends ExceptionContext {

    //@Override
    /*public*/ QString UnexpectedExceptionContext::getTitle() {
        return tr("\"%1 (Unexpected)\"").arg(ExceptionContext::getTitle());
    }

    /*public*/ UnexpectedExceptionContext::UnexpectedExceptionContext(Exception* ex, QString operation, QObject* parent): ExceptionContext(ex, operation, tr("This exception was unexpected and is probably a bug in the code."), parent) {
        //super(ex, operation, Bundle.getMessage("UnexpectedExceptionOperationHint"));
        this->_preface = tr("An unexpected error occurred during the following operation.");
    }
