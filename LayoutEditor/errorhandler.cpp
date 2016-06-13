#include "errorhandler.h"

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
    if (e->exception!=NULL) m += " Exception: "+e->exception->getMessage();

//    if (e->exception != NULL) log.log(e->level, m, e->exception);
//    else log.log(e->level, m);
}

/**
 * Invoked when operation complete.
 *<p>
 * Default implementation doesn't do anything
 * here, everything already logged above.
 */
/*public*/ void ErrorHandler::done() {}

//    // initialize logging
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(ErrorHandler.class.getName());
//}
