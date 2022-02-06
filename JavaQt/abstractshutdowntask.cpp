#include "abstractshutdowntask.h"
#include "loggerfactory.h"
#include "loggingutil.h"

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
 setObjectName(name);
}

/**
 * {@inheritDoc}
 */
//@Override
//@SuppressWarnings("deprecation")
/*public*/ bool AbstractShutDownTask::isShutdownAllowed() {
    LoggingUtil::deprecationWarning(log, "isShutdownAllowed");
    return call();
}

/**
 * {@inheritDoc}
 *
 * This implementation merely sets the "doRun" property to true, and should
 * be overridden for any real checking. Note that overriding implementations
 * should call {@link #setDoRun(boolean)} correctly.
 */
//@Override
/*public*/ bool AbstractShutDownTask::call() {
    doRun = true;
    return doRun;
}

/**
 * {@inheritDoc}
 */
//@Override
//@SuppressWarnings("deprecation")
/*public*/ /*final*/ bool AbstractShutDownTask::execute() {
    LoggingUtil::deprecationWarning(log, "execute");
    run();
    return true;
}

//@Override
/*public*/ QString AbstractShutDownTask::getName()
{
 return mName;
}

//@Override
//@SuppressWarnings("deprecation")
/*public*/ bool AbstractShutDownTask::isParallel() {
    LoggingUtil::deprecationWarning(log, "isParallel");
    return false;
}

//@Override
//@SuppressWarnings("deprecation")
/*public*/ bool AbstractShutDownTask::isComplete() {
    LoggingUtil::deprecationWarning(log, "isComplete");
    return !this->isParallel();
}

/**
 * {@inheritDoc}
 *
 * Note that overriding implementations should call this implementation to set
 * the doRun property correctly.
 */
//@OverridingMethodsMustInvokeSuper
//@Override
/*public*/ void AbstractShutDownTask::propertyChange(PropertyChangeEvent* evt) {
    if ("shuttingDown" == (evt->getPropertyName()) && (evt->getNewValue().toBool()== false)) {
        doRun = false;
    }
}

/**
 * Check if action should be taken in {@link #run()} method. This defaults
 * to false, although the default implementation of {@link #call()} sets
 * this to true.
 *
 * @return true if action should be taken; false otherwise
 */
/*public*/ bool AbstractShutDownTask::isDoRun() {
    return doRun;
}

/**
 * Set if action should be taken in {@link #run()} method. Overriding
 * implementations of {@link #call()} must call this to set
 * {@link #isDoRun()} to true.
   *
 * @param flag true if action should be taken; false otherwise
 */
/*public*/ void AbstractShutDownTask::setDoRun(bool flag) {
    doRun = flag;
}

/*private*/ /*final*/ Logger* AbstractShutDownTask::log = LoggerFactory::getLogger("AbstractShutDownTask");
