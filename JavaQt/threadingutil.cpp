#include "threadingutil.h"
#include "loggerfactory.h"
#include "jmriexception.h"
#include "runtimeexception.h"
#include "reference.h"
#include <QApplication>

ThreadingUtil::ThreadingUtil(QObject *parent) : QObject(parent)
{

}
/**
 * Utilities for handling JMRI's threading conventions.
 * <p>
 * For background, see
 * <a href="http://jmri.org/help/en/html/doc/Technical/Threads.shtml">http://jmri.org/help/en/html/doc/Technical/Threads.shtml</a>
 * <p>
 * Note this distinguishes "on layout", for example, Setting a sensor, from "on
 * GUI", for example, manipulating the Swing GUI. That may not be an important
 * distinction now, but it might be later, so we build it into the calls.
 *
 * @author Bob Jacobsen Copyright 2015
 */

////@ThreadSafe
///*public*/ class ThreadingUtil {

    /**
     * Run some layout-specific code before returning.
     * <p>
     * Typical uses:
     * <p> {@code
     * ThreadingUtil.runOnLayout(() -> {
     *     sensor.setState(value);
     * });
     * }
     *
     * @param ta What to run, usually as a lambda expression
     */
    /*static*/ /*public*/ void ThreadingUtil::runOnLayout(/*@Nonnull*/ ThreadAction* ta) {
        runOnGUI(ta);
    }
/**
 * Run some layout-specific code before returning.
 * This method catches and rethrows JmriException and RuntimeException.
 * <p>
 * Typical uses:
 * <p> {@code
 * ThreadingUtil.runOnLayout(() -> {
 *     sensor.setState(value);
 * });
 * }
 *
 * @param ta What to run, usually as a lambda expression
 * @throws JmriException when an exception occurs
 * @throws RuntimeException when an exception occurs
 */
/*static*/ /*public*/ void ThreadingUtil::runOnLayoutWithJmriException(
        /*@Nonnull*/ ThreadActionWithJmriException* ta)
        /*throws JmriException, RuntimeException*/ {
    runOnGUIWithJmriException(ta);
}
#if 0
    /**
     * Run some layout-specific code at some later point.
     * <p>
     * Please note the operation may have happened before this returns. Or
     * later. No long-term guarantees.
     * <p>
     * Typical uses:
     * <p> {@code
     * ThreadingUtil.runOnLayoutEventually(() -> {
     *     sensor.setState(value);
     * });
     * }
     *
     * @param ta What to run, usually as a lambda expression
     */
    static /*public*/ void runOnLayoutEventually(@Nonnull ThreadAction ta) {
        runOnGUIEventually(ta);
    }

    /**
     * Run some layout-specific code at some later point, at least a known time
     * in the future.
     * <p>
     * There is no long-term guarantee about the accuracy of the interval.
     * <p>
     * Typical uses:
     * <p> {@code
     * ThreadingUtil.runOnLayoutDelayed(() -> {
     *     sensor.setState(value);
     * }, 1000);
     * }
     *
     * @param ta    what to run, usually as a lambda expression
     * @param delay interval in milliseconds
     * @return reference to timer object handling delay so you can cancel if desired; note that operation may have already taken place.
     */
    @Nonnull
    static /*public*/ Timer runOnLayoutDelayed(@Nonnull ThreadAction ta, int delay) {
        return runOnGUIDelayed(ta, delay);
    }
#endif
    /**
     * Check if on the layout-operation thread.
     *
     * @return true if on the layout-operation thread
     */
    /*static*/ /*public*/ bool ThreadingUtil::isLayoutThread() {
        return isGUIThread();
    }

    /**
     * Run some GUI-specific code before returning
     * <p>
     * Typical uses:
     * <p> {@code
     * ThreadingUtil.runOnGUI(() -> {
     *     mine.setVisible();
     * });
     * }
     * <p>
     * If an InterruptedException is encountered, it'll be deferred to the
     * next blocking call via Thread.currentThread().interrupt()
     *
     * @param ta What to run, usually as a lambda expression
     */
    /*static*/ /*public*/ void ThreadingUtil::runOnGUI(/*@Nonnull*/ ThreadAction* ta) {
//        if (isGUIThread()) {
            // run now
            ta->run();
//        }
//        else {
//            // dispatch to Swing
//            warnLocks();
//            try {
//                SwingUtilities.invokeAndWait(ta);
//            } catch (InterruptedException e) {
//                log.debug("Interrupted while running on GUI thread");
//                Thread.currentThread().interrupt();
//            } catch (InvocationTargetException e) {
//                log.error("Error while on GUI thread", e.getCause());
//                log.error("   Came from call to runOnGUI:", e);
//                // should have been handled inside the ThreadAction
//            }
//        }
    }
    /**
     * Run some GUI-specific code before returning.
     * This method catches and rethrows JmriException and RuntimeException.
     * <p>
     * Typical uses:
     * <p> {@code
     * ThreadingUtil.runOnGUI(() -> {
     *     mine.setVisible();
     * });
     * }
     * <p>
     * If an InterruptedException is encountered, it'll be deferred to the
     * next blocking call via Thread.currentThread().interrupt()
     *
     * @param ta What to run, usually as a lambda expression
     * @throws JmriException when an exception occurs
     * @throws RuntimeException when an exception occurs
     */
    /*static*/ /*public*/ void ThreadingUtil::runOnGUIWithJmriException(
            /*@Nonnull*/ ThreadActionWithJmriException* ta)
            /*throws JmriException, RuntimeException*/ {

        if (isGUIThread()) {
            // run now
            ta->run();
        } else {
            // dispatch to Swing
//            warnLocks();
            try {
                Reference<JmriException*>* jmriException = new Reference<JmriException*>();
                Reference<RuntimeException*>* runtimeException = new Reference<RuntimeException*>();
//                SwingUtilities.invokeAndWait(() ->
                {
                    try {
                        ta->run();
                    } catch (JmriException* e) {
                        jmriException->set(e);
                    } catch (RuntimeException* e) {
                        runtimeException->set(e);
                    }
                }//);
                JmriException* je = jmriException->get();
                if (je != nullptr) throw je;
                RuntimeException* re = runtimeException->get();
                if (re != nullptr) throw re;
            } catch (InterruptedException* e) {
                log->debug("Interrupted while running on GUI thread");
                QThread::currentThread()->quit();
            } catch (InvocationTargetException* e) {
                log->error("Error while on GUI thread", e->getCause());
                log->error("   Came from call to runOnGUI:", e);
                // should have been handled inside the ThreadAction
            }
        }
    }
#if 0
    /**
     * Run some GUI-specific code before returning a value.
     * <p>
     * Typical uses:
     * <p>
     * {@code
     * bool retval = ThreadingUtil.runOnGUIwithReturn(() -> {
     *     return mine.isVisible();
     * });
     * }
     * <p>
     * If an InterruptedException is encountered, it'll be deferred to the next
     * blocking call via Thread.currentThread().interrupt()
     *
     * @param <E> generic
     * @param ta What to run, usually as a lambda expression
     * @return the value returned by ta
     */
    template<class E>
    /*static*/ /*public*/ /*<E>*/ int ThreadingUtil::runOnGUIwithReturn(/*@Nonnull*/ ReturningThreadAction<E>* ta) {
#if 1 // TODO:
        if (isGUIThread()) {
            // run now
            /*return*/ ta->run();
        }
//        else {
//            warnLocks();
//            // dispatch to Swing
//            final AtomicReference<E> result = new AtomicReference<>();
//            try {
//                SwingUtilities.invokeAndWait(() -> {
//                    result.set(ta.run());
//                });
//            } catch (InterruptedException* e) {
//                log->debug("Interrupted while running on GUI thread");
//                Thread.currentThread().interrupt();
//            } catch (InvocationTargetException* e) {
//                log.error("Error while on GUI thread", e.getCause());
//                log.error("   Came from call to runOnGUIwithReturn:", e);
//                // should have been handled inside the ThreadAction
//            }
//            return result.get();
//        }
#endif
    }
#endif
    /**
     * Run some GUI-specific code at some later point.
     * <p>
     * If invoked from the GUI thread, the work is guaranteed to happen only
     * after the current routine has returned.
     * <p>
     * Typical uses:
     * <p> {@code
     * ThreadingUtil.runOnGUIEventually( ()->{
     *      mine.setVisible();
     * } );
     * }
     *
     * @param ta What to run, usually as a lambda expression
     */
    /*static*/ /*public*/ void ThreadingUtil::runOnGUIEventually(/*@Nonnull*/ ThreadAction* ta) {
        // dispatch to Swing
#if 1
        //SwingUtilities.invokeLater(ta);
        qApp->processEvents();
        runOnGUI(ta);
#endif
    }
#if 0
    /**
     * Run some GUI-specific code at some later point, at least a known time in
     * the future.
     * <p>
     * There is no long-term guarantee about the accuracy of the interval.
     * <p>
     * Typical uses:
     * <p>
     * {@code
     * ThreadingUtil.runOnGUIDelayed( ()->{
     *  mine.setVisible();
     * }, 1000);
     * }
     *
     * @param ta    What to run, usually as a lambda expression
     * @param delay interval in milliseconds
     * @return reference to timer object handling delay so you can cancel if desired; note that operation may have already taken place.
     */
    @Nonnull
    static /*public*/ Timer runOnGUIDelayed(@Nonnull ThreadAction ta, int delay) {
        // dispatch to Swing via timer
        Timer timer = new Timer(delay, (ActionEvent e) -> {
            ta.run();
        });
        timer.setRepeats(false);
        timer.start();
        return timer;
    }
#endif
    /**
     * Check if on the GUI event dispatch thread.
     *
     * @return true if on the event dispatch thread
     */
    /*static*/ /*public*/ bool ThreadingUtil::isGUIThread() {
        //return SwingUtilities.isEventDispatchThread();
     return QThread::currentThread() == QCoreApplication::instance()->thread();
    }

    /**
     * Create a new thread in the JMRI group
     * @param runner Runnable.
     * @return new Thread.
     */
    /*static*/ /*public*/ QThread* ThreadingUtil::newThread(Runnable* runner) {
        //return new Thread(getJmriThreadGroup(), runner);
     return runner;
    }

    /**
     * Create a new thread in the JMRI group.
     * @param runner Thread runnable.
     * @param name Thread name.
     * @return New Thread.
     */
    /*static*/ /*public*/ QThread* ThreadingUtil::newThread(Runnable* runner, QString name) {
        //return new Thread(getJmriThreadGroup(), runner, name);
     runner->setObjectName(name);
     return runner;
    }
#if 0
    /**
     * Get the JMRI default thread group.
     * This should be passed to as the first argument to the {@link Thread}
     * constructor so we can track JMRI-created threads.
     * @return JMRI default thread group.
     */
    static /*public*/ ThreadGroup getJmriThreadGroup() {
        // we access this dynamically instead of keeping it in a static

        ThreadGroup main = Thread.currentThread().getThreadGroup();
        while (main.getParent() != null ) {main = main.getParent(); }
        ThreadGroup[] list = new ThreadGroup[main.activeGroupCount()+2];  // space on end
        int max = main.enumerate(list);

        for (int i = 0; i<max; i++) { // usually just 2 or 3, quite quick
            if (list[i].getName().equals("JMRI")) return list[i];
        }
        return new ThreadGroup(main, "JMRI");
    }

    /**
     * Check whether a specific thread is running (or able to run) right now.
     *
     * @param t the thread to check
     * @return true is the specified thread is or could be running right now
     */
    static /*public*/ bool canThreadRun(@Nonnull Thread t) {
        Thread.State s = t.getState();
        return s.equals(Thread.State.RUNNABLE);
    }

    /**
     * Check whether a specific thread is currently waiting.
     * <p>
     * Note: This includes both waiting due to an explicit wait() call, and due
     * to being blocked attempting to synchronize.
     * <p>
     * Note: {@link #canThreadRun(Thread)} and {@link #isThreadWaiting(Thread)}
     * should never simultaneously be true, but it might look that way due to
     * sampling delays when checking on another thread.
     *
     * @param t the thread to check
     * @return true is the specified thread is or could be running right now
     */
    static /*public*/ bool isThreadWaiting(@Nonnull Thread t) {
        Thread.State s = t.getState();
        return s.equals(Thread.State.BLOCKED) || s.equals(Thread.State.WAITING) || s.equals(Thread.State.TIMED_WAITING);
    }

    /**
     * Check that a call is on the GUI thread. Warns (once) if not.
     * Intended to be the run-time check mechanism for {@code @InvokeOnGuiThread}
     * <p>
     * In this implementation, this is the same as {@link #requireLayoutThread(org.slf4j.Logger)}
     * @param logger The logger object from the calling class, usually "log"
     */
    static /*public*/ void requireGuiThread(org.slf4j.Logger logger) {
        if (!isGUIThread()) {
            // fail, which can be a bit slow to do the right thing
            LoggingUtil.warnOnce(logger, "Call not on GUI thread", new Exception("traceback"));
        }
    }

    /**
     * Check that a call is on the Layout thread. Warns (once) if not.
     * Intended to be the run-time check mechanism for {@code @InvokeOnLayoutThread}
     * <p>
     * In this implementation, this is the same as {@link #requireGuiThread(org.slf4j.Logger)}
     * @param logger The logger object from the calling class, usually "log"
     */
    static /*public*/ void requireLayoutThread(org.slf4j.Logger logger) {
        if (!isLayoutThread()) {
            // fail, which can be a bit slow to do the right thing
            LoggingUtil.warnOnce(logger, "Call not on Layout thread", new Exception("traceback"));
        }
    }

    /**
     * Interface for use in ThreadingUtil's lambda interfaces
     */
    @FunctionalInterface
    static /*public*/ interface ThreadAction extends Runnable {

        /**
         * {@inheritDoc}
         * <p>
         * Must handle its own exceptions.
         */
        @Override
        /*public*/ void run();
    }

    /**
     * Interface for use in ThreadingUtil's lambda interfaces
     *
     * @param <E> the type returned
     */
    //@FunctionalInterface
    template<class E>
    /*static*/ /*public*/ class ReturningThreadAction : public ThreadAction
    {
      Q_OBJECT
      ReturningThreadAction() : ThreadAction() {}
     public slots:
        /*public*/ E run();
    };

    /**
     * Warn if a thread is holding locks. Used when transitioning to another context.
     */
    static /*public*/ void warnLocks() {
        if ( log.isDebugEnabled() ) {
            try {
                java.lang.management.ThreadInfo threadInfo = java.lang.management.ManagementFactory
                                                    .getThreadMXBean()
                                                        .getThreadInfo(new long[]{Thread.currentThread().getId()}, true, true)[0];

                java.lang.management.MonitorInfo[] monitors = threadInfo.getLockedMonitors();
                for (java.lang.management.MonitorInfo mon : monitors) {
                    log.warn("Thread was holding monitor {} from {}", mon, mon.getLockedStackFrame(), LoggingUtil.shortenStacktrace(new Exception("traceback"))); // yes, warn - for re-enable later
                }

                java.lang.management.LockInfo[] locks = threadInfo.getLockedSynchronizers();
                for (java.lang.management.LockInfo lock : locks) {
                    // certain locks are part of routine Java API operations
                    if (lock.toString().startsWith("java.util.concurrent.ThreadPoolExecutor$Worker") ) {
                        log.debug("Thread was holding java lock {}", lock, LoggingUtil.shortenStacktrace(new Exception("traceback")));  // yes, warn - for re-enable later
                    } else {
                        log.warn("Thread was holding lock {}", lock, LoggingUtil.shortenStacktrace(new Exception("traceback")));  // yes, warn - for re-enable later
                    }
                }
            } catch (RuntimeException ex) {
                // just record exceptions for later pick up during debugging
                if (!lastWarnLocksLimit) log.warn("Exception in warnLocks", ex);
                lastWarnLocksLimit = true;
                lastWarnLocksException = ex;
            }
        }
    }
    /*private*/ static bool lastWarnLocksLimit = false;
    /*private*/ static RuntimeException lastWarnLocksException = null;
    /*public*/ RuntimeException getlastWarnLocksException() { // /*public*/ for script and test access
        return lastWarnLocksException;
    }
#endif
    /*private*/ /*final*/ /*static*/ Logger* ThreadingUtil::log = LoggerFactory::getLogger("ThreadingUtil");
