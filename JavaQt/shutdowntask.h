#ifndef SHUTDOWNTASK_H
#define SHUTDOWNTASK_H
#include <QObject>

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
  //Q_OBJECT
 public:
    /**
     * Take the necessary action.
     * @return true if the shutdown should continue, false
     * to abort.
     */
    /*public*/ virtual bool execute() {return false;}

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
     /*public*/ virtual bool isParallel() {return false;}

     /**
      * Advise {@link jmri.ShutDownManager}s that the task is complete.
      *
      * @return true if the task is complete
      */
     /*public*/ virtual bool isComplete() {return false;}
};

#endif // SHUTDOWNTASK_H
