#include "errorhandler.h"
#include "errormemo.h"
#include "loggerfactory.h"
#include "exceptions.h"

ErrorHandler::ErrorHandler(QObject *parent) :
    QObject(parent)
{
}
/**
 * Default operation for reporting errors while loading.
 *
 * @author Bob Jacobsen  Copyright (c) 2010
 * @version $Revision: 17977 $
 */

//public class ErrorHandler {

/**
 * Handle an error.
 * <p>
 * Default implementation formats and puts in log.
 */

/*public*/ void ErrorHandler::handle(ErrorMemo* e) {
    QString m = e->description;
    if (e->systemName!=NULL) m += " System name \""+e->systemName+"\"";
    if (e->userName!=NULL && e->userName!=("")) m += " User name \""+e->userName+"\"";
    if (e->operation!=NULL) m += " while "+e->operation;
    if (e->adapter!=NULL) m += tr(" in adaptor of type ")+e->adapter->metaObject()->className();
     m += " Exception: "+e->exception.getMessage();

//    if (e->exception != Throwable())
//    {
//     log->error(m, e->exception);
//    }
//    else {
     log->error(m);
//    }
}

/**
 * Invoked when operation complete.
 *<p>
 * Default implementation doesn't do anything
 * here, everything already logged above.
 */
/*public*/ void ErrorHandler::done() {}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* ErrorHandler::log = LoggerFactory::getLogger("ErrorHandler");
