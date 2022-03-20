#include "protectedtimertask.h"
#include "runtimeexception.h"

/**
 * A timer task that can be stopped, and there the stop method waits until the
 * task is finished.
 * <p>
 * Note that this class does [u]not[/u] work for repeating timers. The class
 * can be used for tasks that are scheduled over and over again, but only works
 * for one shoot timer.
 * <p>
 * In other words, the class works for TimerUtil.schedule(@Nonnull TimerTask task, long delay)
 * but not for TimerUtil.schedule(@Nonnull TimerTask task, long delay, long period).
 * This is due to how the method TimerTask.cancel() works.
 */
///*public*/  abstract class ProtectedTimerTask extends TimerTask {



    //@Override
    /*public*/  /*final*/ void ProtectedTimerTask::run() {
        /*synchronized(_lock)*/ {
        QMutexLocker locker(&mutex1);
            if (_stopTimer) return;
            _timerIsRunning = true;
        }

        // Execute the task
        execute();

        /*synchronized(_lock) */{
         QMutexLocker locker(&mutex1);
            _timerIsRunning = false;
        }
    }

    /**
     * Stop the timer.
     * This method will not return until the timer task is cancelled and stopped.
     * This code ensures that we don't return from this method until the timer
     * task is cancelled and that it's not running any more.
     */
    //@SuppressWarnings(value = "SleepWhileInLoop")
    /*public*/  void ProtectedTimerTask::stopTimer() {
        /*synchronized (_lock)*/ {
        QMutexLocker locker(&mutex1);

            _stopTimer = true;
            // If cancel() returns true, the task will never be
            // executed and we are done.
            if (cancel()) return;
            // If the timer task is not running, we don't have
            // to wait for it to finish.
            if (!_timerIsRunning) {
                return;
            }
        }
        // Try max 50 times
        for (int count=0; count <= 50; count++) {
            /*synchronized (_lock)*/ {
          QMutexLocker locker(&mutex1);

                if (!_timerIsRunning) return;
            }
            try {
                sleep(20);
            } catch (InterruptedException* e) {
                Thread::currentThread()->quit();
            }
        }
        throw new RuntimeException("Cannot stop timer");
    }
