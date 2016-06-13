#include "abstractshutdowntask.h"

//AbstractShutDownTask::AbstractShutDownTask(QObject *parent) :
//    ShutdownTask(parent)
//{
//}
/**
 * Handle name for ShutDownTask implementations.
 *
 * @author      Bob Jacobsen Copyright (C) 2008
 * @version	$Revision: 17977 $
 */
//public abstract class AbstractShutDownTask implements ShutDownTask {

    /**
     * Constructor specifies the name
     */
/*public*/ AbstractShutDownTask::AbstractShutDownTask(QString name, QObject *parent)
{
 this->mName = name;
 this->parent = parent;
}


/*public*/ QString AbstractShutDownTask::name()
{
 return mName;
}
