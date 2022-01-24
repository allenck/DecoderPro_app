#ifndef TIMERTASK_H
#define TIMERTASK_H
#include "runnable.h"


class TimerTask : public Runnable
{
    Q_OBJECT
protected:
    explicit TimerTask(QObject *parent = nullptr);
public:
    enum STATE
    {
        /**
     * This task has not yet been scheduled.
     */
    VIRGIN = 0,

    /**
     * This task is scheduled for execution.  If it is a non-repeating task,
     * it has not yet been executed.
     */
    SCHEDULED   = 1,

    /**
     * This non-repeating task has already executed (or is currently
     * executing) and has not been cancelled.
     */
    EXECUTED    = 2,

    /**
     * This task has been cancelled (with a call to TimerTask.cancel).
     */
     CANCELLED   = 3
    };
    /*public*/ bool cancel();
    /*public*/ long scheduledExecutionTime();
    /*public*/ long getPeriod() {return period;}
signals:

public slots:
    /*public*/ /*abstract*/ virtual void run();

private:
    /**
     * This object is used to control access to the TimerTask internals.
     */
    /*final*/ QObject* lock;// = new QObject();

    /**
     * The state of this task, chosen from the constants below.
     */
    int state = VIRGIN;



    /**
     * Next execution time for this task in the format returned by
     * System.currentTimeMillis, assuming this task is scheduled for execution.
     * For repeating tasks, this field is updated prior to each task execution.
     */
    long nextExecutionTime;

    /**
     * Period in milliseconds for repeating tasks.  A positive value indicates
     * fixed-rate execution.  A negative value indicates fixed-delay execution.
     * A value of 0 indicates a non-repeating task.
     */
    long period = 0;
};

#endif // TIMERTASK_H
