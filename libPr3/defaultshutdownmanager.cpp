#include "defaultshutdownmanager.h"
#include "Roster/paneprogframe.h"
#include "defaultidtagmanager.h"
#include "jmriuserpreferencesmanager.h"
#include "apps.h"
#include "defaultaudiomanager.h"
#include "appsbase.h"
#include <QGuiApplication>
#include <QWindow>
#include <QApplication>
#include <QProcess>

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
 * Run the shutdown tasks, and then terminate the program if not aborted.
 * Does not return under normal circumstances. Does return if the shutdown
 * was aborted by the user, in which case the program should continue to
 * operate.
 * <p>
 * Executes all registered {@link jmri.ShutDownTask}s before closing any
 * displayable windows.
 *
 * @param status Integer status returned on program exit
 * @param exit   True if System.exit() should be called if all tasks are
 *               executed correctly.
 * @return false if shutdown or restart failed.
 */
//@SuppressFBWarnings(value = "DM_EXIT", justification = "OK to directly exit standalone main")
/*protected*/ bool DefaultShutDownManager::shutdown(int status, bool _exit)
{
 if (!shuttingDown)
 {
  QDateTime start =  QDateTime::currentDateTime();
  long timeout = 30; // all shut down tasks must complete within n seconds
  setShuttingDown(true);
  // trigger parallel tasks (see jmri.ShutDownTask#isParallel())
  if (!this->runShutDownTasks(true)) {
      return false;
  }
  log.debug(tr("parallel tasks completed executing %1 milliseconds after starting shutdown").arg( /*QDateTime::currentDateTime() - start.getTime()*/start.msecsTo(QDateTime::currentDateTime())));
  // trigger non-parallel tasks
  if (!this->runShutDownTasks(false)) {
      return false;
  }
  log.debug(tr("sequential tasks completed executing %1 milliseconds after starting shutdown").arg(start.msecsTo(QDateTime::currentDateTime()))); //new Date().getTime() - start.getTime());

  // close any open windows by triggering a closing event
  // this gives open windows a final chance to perform any cleanup
//        if (!GraphicsEnvironment.isHeadless())
//        {
//            Arrays.asList(Frame.getFrames()).stream().forEach((frame) ->
   foreach(QWindow* frame, QGuiApplication::allWindows())
   {
    // do not run on thread, or in parallel, as System.exit()
    // will get called before windows can close
    if (frame->isActive())
    { // dispose() has not been called
     log.debug(tr("Closing frame \"%1\", title: \"%2\"").arg(frame->metaObject()->className(), frame->title()));
     QDateTime timer = QDateTime::currentDateTime();
     //frame.dispatchEvent(new WindowEvent(frame, WindowEvent.WINDOW_CLOSING));
     frame->close();
     log.debug(tr("Frame \"%1\" took %2 milliseconds to close").arg(frame->metaObject()->className()).arg(timer.msecsTo(QDateTime::currentDateTime()))); // new Date().getTime() - timer.getTime());
    }
   } //);
//        }

  log.debug(tr("windows completed closing %1 milliseconds after starting shutdown").arg(start.msecsTo(QDateTime::currentDateTime()))); //new Date().getTime() - start.getTime());
#if 0
  // wait for parallel tasks to complete
  /*synchronized (start)*/ {
      while (new ArrayList<>(this.tasks).stream().anyMatch((task) -> (task.isParallel() && !task.isComplete())))
      {
          try {
              start.wait(100);
          } catch (InterruptedException ex) {
              // do nothing
          }
          if ((new Date().getTime() - start.getTime()) > (timeout * 1000)) { // milliseconds
              log.warn("Terminating without waiting for all tasks to complete");
              break;
          }
      }
  }
#endif
  // success
  log.debug(tr("Shutdown took %1 milliseconds.").arg(start.msecsTo(QDateTime::currentDateTime()))); //new Date().getTime() - start.getTime());
  log.info("Normal termination complete");
  // and now terminate forcefully
  if (_exit) {
   if(status == 100)
   {
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
      exit(status);
   }
  }
 }
 return false;
}

/*private*/ bool DefaultShutDownManager::runShutDownTasks(bool isParallel) {
    // can't return out of a stream or forEach loop
    foreach (ShutDownTask* task,  QVector<ShutDownTask*>(*tasks))
    {
        if (task->isParallel() == isParallel) {
            log.debug(tr("Calling task \"%1\"").arg(task->getName()));
            QDateTime timer = QDateTime::currentDateTime();
            try {
                setShuttingDown(task->execute()); // if a task aborts the shutdown, stop shutting down
                if (!shuttingDown) {
                    log.info(tr("Program termination aborted by \"%1\"").arg(task->getName()));
                    return false;  // abort early
                }
            } catch (Exception e) {
                log.error(tr("Error during processing of ShutDownTask \"%1\"").arg(task->getName()+ e.getMessage()));
            } catch (Throwable e) {
                // try logging the error
                log.error("Unrecoverable error during processing of ShutDownTask \"{}\"", task->getName() + e.getMessage());
                log.error("Terminating abnormally");
                // also dump error directly to System.err in hopes its more observable
#if 0
                System.err.println("Unrecoverable error during processing of ShutDownTask \"" + task.getName() + "\"");
                System.err.println(e);
                System.err.println("Terminating abnormally");
                // forcably halt, do not restart, even if requested
#endif
                exit(1);
            }
            log.debug(tr("Task \"%1\" took %2 milliseconds to execute").arg(task->getName()).arg(timer.msecsTo(QDateTime::currentDateTime()))); //new Date().getTime() - timer.getTime());
        }
    }
    return true;
}

//@Override
/*public*/ bool DefaultShutDownManager::isShuttingDown() {
    return shuttingDown;
}

/**
 * This method is static so that if multiple DefaultShutDownManagers are
 * registered, they are all aware of this state.
 *
 */
/*private*/ /*static*/ void DefaultShutDownManager::setShuttingDown(bool state) {
    shuttingDown = state;
}

