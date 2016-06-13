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
 /*public*/ virtual QString name() { return "";}
};

#endif // SHUTDOWNTASK_H
