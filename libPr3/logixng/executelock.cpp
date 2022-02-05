#include "executelock.h"

/**
 * Protect the DefaultConditionalNG.execute() method.
 * That method may be called recursively from different threads.
 */
// /*public*/ class ExecuteLock {


    /**
     * Get the status of the lock.
     * If the call succeeds, the caller is responsible to loop while the method
     * loop() returns true.
     * @return true if the caller gets the lock.
     */
    /*public*/ bool ExecuteLock::once() {
        /*synchronized(this)*/ {
        QMutexLocker locker(&mutex);
            again = true;
            if (! lock) {
                lock = true;
                return true;
            } else {
                return false;
            }
        }
    }

    /**
     * Get the status of the lock during loop.
     * The caller is responsible to loop while the method returns true.
     * @return true if the caller still has the lock.
     */
    /*public*/ bool ExecuteLock::loop() {
        /*synchronized(this)*/ {
        QMutexLocker locker(&mutex);
            if (again) {
                again = false;
                return true;
            } else {
                lock = false;
                return false;
            }
        }
    }
