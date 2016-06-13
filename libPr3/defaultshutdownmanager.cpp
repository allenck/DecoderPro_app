#include "defaultshutdownmanager.h"
#include "Roster/paneprogframe.h"
#include "defaultidtagmanager.h"
#include "defaultusermessagepreferences.h"
#include "apps.h"
#include "defaultaudiomanager.h"
#include "appsbase.h"

/*static*/ bool DefaultShutDownManager::shuttingDown = false;

DefaultShutDownManager::DefaultShutDownManager(QObject *parent) :
    ShutDownManager(parent)
{
 tasks = new QVector<ShutDownTask*>();

}
/**
 * Manage tasks to be completed when the
 * program shuts down normally.
 * Specifically, allows other object to
 * register and deregister {@link ShutDownTask} objects,
 * which are invoked in an orderly way when the program is
 * is commanded to terminate.
 * <p>
 * Operations:
 * <ol>
 * <li>Execute each {@link ShutDownTask} in order,
 *     allowing it to abort the shutdown if needed.
 * <li>If not aborted, terminate the program.
 * </ol>
 * <p>
 * There can only be one instance of this operating,
 * and it is generally obtained via the instance manager.
 * <p>
 * To avoid being unable to quit the program, which annoys people,
 * an exception in a ShutDownTask is treated as permission to continue after
 * logging.
 *
 * @author      Bob Jacobsen Copyright (C) 2008
 * @version	$Revision: 21009 $
 */
///*public*/ class DefaultShutDownManager implements ShutDownManager {


///*public*/ DefaultShutDownManager() {}

/**
 * Register a task object for later execution.
 */
//@Override
/*public*/ void DefaultShutDownManager::_register(ShutDownTask* s)
{
 if (!tasks->contains(s))
 {
  if(s->objectName() == "")
   s->setObjectName(QString(s->metaObject()->className()));
  tasks->append(s);
 }
 else
 {
  log.error(tr("already contains ")+s->metaObject()->className());
 }
}

/**
 * Deregister a task object.
 * @throws IllegalArgumentException if task object not currently registered
 */
//@Override
/*public*/ void DefaultShutDownManager::deregister(ShutDownTask* s)
{
 if (tasks->contains(s))
 {
  tasks->remove(tasks->indexOf(s));
 }
 else
 {
  //throw new IllegalArgumentException("task not registered");
  Logger::error("task not registered");
 }
}

/**
 * Run the shutdown tasks, and
 * then terminate the program with status 0 if not aborted.
 * Does not return under normal circumstances.
 * Does return if the shutdown was aborted by the user,
 * in which case the program should continue to operate.
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="DM_EXIT") // OK to directly exit standalone main
//@Override
/*public*/ bool DefaultShutDownManager::shutdown()
{
 return shutdown(0, true);
}

/**
 * Run the shutdown tasks, and
 * then terminate the program with status 100 if not aborted.
 * Does not return under normal circumstances.
 * Does return if the shutdown was aborted by the user,
 * in which case the program should continue to operate.
 *
 * By exiting the program with status 100, the batch file (MS Windows)
 * or shell script (Linux/Mac OS X/UNIX) can catch the exit status and
 * restart the java program.
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="DM_EXIT") // OK to directly exit standalone main
//@Override
/*public*/ bool DefaultShutDownManager::restart() {
    return shutdown(100, true);
}


/**
 * Run the shutdown tasks, and
 * then terminate the program if not aborted.
 * Does not return under normal circumstances.
 * Does return if the shutdown was aborted by the user,
 * in which case the program should continue to operate.
 *
 * @param status Integer status returned on program exit
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="DM_EXIT") // OK to directly exit standalone main
/*protected*/ bool DefaultShutDownManager::shutdown(int status, bool _exit)
{
 if (!shuttingDown)
 {
  shuttingDown = true;
  for (int i = tasks->size() - 1; i >= 0; i--)
  {
   try
   {
    ShutDownTask* t = tasks->at(i);
//    if(qobject_cast<FileDirtyTask*>(t)!= NULL)
//     shuttingDown = ((FileDirtyTask*)t)->execute();
//    else if(qobject_cast<DecoderDirtyTask*>(t)!= NULL)
//     shuttingDown = ((DecoderDirtyTask*)t)->execute();
//    else if(qobject_cast<DefaultIdTagShutdownTask*>(t)!= NULL)
//     shuttingDown = ((DefaultIdTagShutdownTask*)t)->execute();
//    else if(qobject_cast<UserPreferencesShutDownTask*>(t)!= NULL)
//     shuttingDown = ((UserPreferencesShutDownTask*)t)->execute();
//    else if(qobject_cast<WriteBlocksShutdownTask*>(t)!= NULL)
//     shuttingDown = ((WriteBlocksShutdownTask*)t)->execute();
//    else if(qobject_cast<AudioShutDownTask*>(t)!= NULL)
//     shuttingDown = ((AudioShutDownTask*)t)->execute();
//    else if(qobject_cast<WriteBlocksShutDownTask*>(t)!= NULL)
//     shuttingDown = ((WriteBlocksShutDownTask*)t)->execute();
//    else
//    {
//     log.error(tr("Missing cast: ")+t->metaObject()->className());
//     Q_ASSERT(false);
//      //shuttingDown = t->execute(); // if a task aborts the shutdown, stop shutting down
//    }
    shuttingDown= t->execute();
    if (!shuttingDown)
    {
     log.info("Program termination aborted by " + t->name());
     return false;  // abort early
    }
   }
   catch (Throwable e)
   {
    log.error(tr("Error during processing of ShutDownTask ") + i + ": " + e.getMessage());
   }
  }

  // success
  log.info("Normal termination complete");
  // and now terminate forcefully
  if(_exit)
   exit(status);
 }
 return false;
}


//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(DefaultShutDownManager.class.getName());
//}
