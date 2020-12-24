#ifndef SHUTDOWNTASK_H
#define SHUTDOWNTASK_H
#include <QObject>
#include "exceptions.h"

/**
 * Execute a specific task before the program terminates.
 * <p>
 * Tasks should leave the system in a state that can continue, in
 * case a later task aborts the shutdown.
 *
 * @author      Bob Jacobsen Copyright (C) 2008
 * @version	$Revision: 17977 $
 */
/*public*/ /*interface*/ class ShutDownTask : public QObject
{
  Q_OBJECT
 public:
  /**
   * Ask if shut down is allowed.
   * <p>
   * The shut down manager must call this method first on all the tasks before
   * starting to execute the method execute() on the tasks.
   * <p>
   * If this method returns false on any task, the shut down process must be
   * aborted.
   *
   * @return true if it is OK to shut down, false to abort shut down.
   * @deprecated since 4.21.1; use {@link #call()} instead
   */
  //@Deprecated
  QT_DEPRECATED/*public*/  virtual bool isShutdownAllowed() {return false;}

  /**
   * Ask if shut down is allowed.
   * <p>
   * The shut down manager calls this method first on all the tasks before
   * starting to execute the method {@link #run()} on the tasks.
   * <p>
   * If this method returns false on any task, the shut down process must be
   * aborted.
   *
   * @return true if it is OK to shut down, false to abort shut down.
   * @throws Exception if there is an exception
   */
  //@Override
  /*public*/ virtual bool call() throw (Exception) {return false;}

  /**
     * Take the necessary action.
     * @return true if the shutdown should continue, false
     * to abort.
     */
    QT_DEPRECATED/*public*/ virtual bool execute() {return false;}

    /**
     * Name to be provided to the user
     * when information about this task is presented.
     */
    /*public*/ virtual QString getName() { return "";}

    /**
     * Advise {@link jmri.ShutDownManager}s if {@link #execute()} may return
     * before the task is complete.
     * <p>
     * <strong>Note</strong> if a task is parallel, {@link #execute()} should
     * return <em>after</em> any tests that might cause the shutdown to be
     * aborted.
     *
     * @return true if the task is run within its own Thread
     */
    QT_DEPRECATED/*public*/ virtual bool isParallel() {return false;}

    /**
     * Advise {@link jmri.ShutDownManager}s that the task is complete.
     *
     * @return true if the task is complete
     */
    QT_DEPRECATED/*public*/ virtual bool isComplete() {return false;}

  /**
   * Take the necessary action. This method cannot abort the shutdown, and
   * must not require user interaction to complete successfully. This method
   * will be run in parallel to other ShutDownTasks.
   */
  //@Override
  /*public*/ virtual void run() {}

  //virtual QObject* self() =0;
};

Q_DECLARE_INTERFACE(ShutDownTask, "ShutDownTask")
#endif // SHUTDOWNTASK_H
