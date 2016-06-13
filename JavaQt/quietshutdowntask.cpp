#include "quietshutdowntask.h"


//QuietShutDownTask::QuietShutDownTask(QObject *parent) :
//    AbstractShtDownTask(parent)
//{
//}
/**
 * Provides a base to perform a shutdown task without user-intervention.
 *
 * @author      Matthew Harris Copyright (c) 2008
 * @version     $Revision: 17977 $
 */
// /*public*/ class QuietShutDownTask extends AbstractShutDownTask {

/**
 * Constructor specifies the shutdown task name
 */
/*public*/ QuietShutDownTask::QuietShutDownTask(QString name, QObject *parent) : AbstractShutDownTask(name, parent)
{
 //super(name);
}

/**
 * Take the necessary action.
 * @return true if the shutdown should continue, false
 * to abort.
 */
/*public*/ bool QuietShutDownTask::execute() {
    return doAction();
}

/**
 * Provide a subclass-specific method to handle the
 * request to fix the problem. This is a dummy implementation,
 * intended to be overloaded.
 * @return true if ready to shutdown, false to end shutdown
 */
/*protected*/ bool QuietShutDownTask::doAction() {
    return true;
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(QuietShutDownTask.class.getName());

//}
