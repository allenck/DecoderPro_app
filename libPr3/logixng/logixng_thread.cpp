#include "logixng_thread.h"
#include "exceptions.h"
#include <QSet>
#include "timer.h"
#include "exceptions.h"
#include "loggingutil.h"
#include "loggerfactory.h"
#include "runtimeexception.h"
#include <QQueue>

/**
 * Utilities for handling JMRI's LogixNG threading conventions.
 * <p>
 * For background, see
 * <a href="http://jmri.org/help/en/html/doc/Technical/Threads.shtml">http://jmri.org/help/en/html/doc/Technical/Threads.shtml</a>
 * <p>
 * This is the ThreadingUtil class for LogixNG.
 *
 * @author Bob Jacobsen      Copyright 2015
 * @author Daniel Bergqvist  Copyright 2020
 */
//@ThreadSafe
// /*public*/ class LogixNG_Thread {

    /*public*/ /*static*/ /*final*/ const int LogixNG_Thread::DEFAULT_LOGIXNG_THREAD = 0;
    /*public*/ /*static*/ /*final*/ const int LogixNG_Thread::DEFAULT_LOGIXNG_DEBUG_THREAD = 1;

    /*private*/ /*static*/ /*final*/ QMap<int, LogixNG_Thread*> LogixNG_Thread::_threads = QMap<int, LogixNG_Thread*>();
    /*private*/ /*static*/ /*final*/ QMap<QString, LogixNG_Thread*> LogixNG_Thread::_threadNames = QMap<QString, LogixNG_Thread*>();
    /*private*/ /*static*/ int LogixNG_Thread::_highestThreadID = -1;



    /*public*/ /*static*/ LogixNG_Thread* LogixNG_Thread::createNewThread(/*@Nonnull*/  QString name) {
        return createNewThread(-1, name);
    }

    /*public*/ /*static*/ LogixNG_Thread* LogixNG_Thread::createNewThread(int threadID, /*@Nonnull*/  QString name) {
        /*synchronized (LogixNG_Thread.class)*/ {
            if (threadID == -1) {
                threadID = ++_highestThreadID;
            } else {
                if (threadID > _highestThreadID) _highestThreadID = threadID;
            }

            if (_threads.contains(threadID)) {
                throw new  IllegalArgumentException(tr("Thread ID %1 already exists").arg(threadID));
            }

            if (_threadNames.contains(name)) {
                throw new  IllegalArgumentException(tr("Thread name %s already exists").arg(name));
            }
            LogixNG_Thread* thread = new LogixNG_Thread(threadID, name);
            _threads.insert(threadID, thread);
            _threadNames.insert(name, thread);
            thread->_logixNGThread->start();

            return thread;
        }
    }

    /*public*/ /*static*/ bool LogixNG_Thread::validateNewThreadName(/*@Nonnull*/  QString name) {
        /*synchronized (LogixNG_Thread.class)*/ {
            return !_threadNames.contains(name);
        }
    }

    /*public*/ /*static*/ LogixNG_Thread* LogixNG_Thread::getThread(int threadID) {
        /*synchronized (LogixNG_Thread.class)*/ {
            LogixNG_Thread* thread = _threads.value(threadID);
            if (thread == nullptr) {
                switch (threadID) {
                    case DEFAULT_LOGIXNG_THREAD:
                        thread = createNewThread(DEFAULT_LOGIXNG_THREAD, tr("LogixNG_Thread"));
                        break;
                    case DEFAULT_LOGIXNG_DEBUG_THREAD:
                        thread = createNewThread(DEFAULT_LOGIXNG_DEBUG_THREAD, tr("LogixNG_DebugThread"));
                        break;
                    default:
                        throw new IllegalArgumentException(tr("Thread ID %d does not exists").arg(threadID));
                }
            }
            return thread;
        }
    }

    /*public*/ /*static*/ int LogixNG_Thread::getThreadID(QString name) {
        /*synchronized (LogixNG_Thread.class)*/ {
            for (LogixNG_Thread* t : _threads.values()) {
                if (name == (t->_name)) return t->_threadID;
            }
            throw new  IllegalArgumentException(tr("Thread name \"%s\" does not exists").arg(name));
        }
    }

    /*public*/ /*static*/ void LogixNG_Thread::deleteThread(LogixNG_Thread* thread) {
        /*synchronized (LogixNG_Thread.class)*/ {
            LogixNG_Thread* aThread = _threads.value(thread->_threadID);

            if (aThread == nullptr) throw new  IllegalArgumentException("Thread does not exists");
            if (aThread != thread) throw new  IllegalArgumentException("Thread ID does not match");
            if (aThread->_threadInUse) throw new  IllegalArgumentException("Thread is in use");

            _threads.remove(thread->_threadID);
            _threadNames.remove(thread->_name);
        }
    }

    /*public*/ /*static*/ QSet<LogixNG_Thread*> LogixNG_Thread::getThreads() {
        //return Collections.unmodifiableCollection(_threads.values());
     return QSet<LogixNG_Thread*>(_threads.values().toSet());
    }

    /*private*/ LogixNG_Thread::LogixNG_Thread(int threadID, QString name, QObject* parent) : QThread(parent){
        _threadID = threadID;
        _name = name;
#if 1
        /*synchronized(LogixNG_Thread.class)*/
        {

            _eventQueue = new QQueue<ThreadEvent*>(/*1024*/);
//            _logixNGThread = new Thread(() -> {
//                while (!_stopThread) {
//                    try {
//                        ThreadEvent event = _eventQueue.take();
//                        if (event._lock != null) {
//                            synchronized(event._lock) {
//                                if (!_stopThread) event._threadAction.run();
//                                event._lock.notify();
//                            }
//                        } else {
//                            event._threadAction.run();
//                        }
//                    } catch (InterruptedException ex) {
//                        Thread.currentThread().interrupt();
//                    }
//                }
//                _threadIsStopped = true;
//            }, "JMRI LogixNGThread");
            _logixNGThread = new Thread(new NGThread(this), "JMRI LogixNGThread");

            _logixNGThread->setTerminationEnabled(true);//setDaemon(true);
        }
#endif
    }

    /*public*/ QThread* LogixNG_Thread::getThread() {
        return _logixNGThread;
    }

    /*public*/ int LogixNG_Thread::getThreadId() {
        return _threadID;
    }

    /*public*/ QString LogixNG_Thread::getThreadName() {
        return _name;
    }

    /*public*/ void LogixNG_Thread::setThreadName(/*@Nonnull*/  QString name) {
        if (_name == (name)) return;

        /*synchronized (LogixNG_Thread.class)*/ {
            if (_threadNames.contains(name)) {
                throw new  IllegalArgumentException(tr("Thread name %s already exists").arg(name));
            }
            _threadNames.remove(_name);
            _threadNames.insert(name, this);
            _name = name;
        }
    }

    /*public*/ bool LogixNG_Thread::getThreadInUse() {
        return _threadInUse;
    }

    /**
     * Set the thread to "in use".
     * If a thread is in use, it cannot be unset as not in use.
     */
    /*public*/ void LogixNG_Thread::setThreadInUse() {
        _threadInUse = true;
    }

    /**
     * Run some LogixNG-specific code before returning.
     * <p>
     * Typical uses:
     * <p> {@code
     * ThreadingUtil.runOnLogixNG(() -> {
     *     logixNG.doSomething(value);
     * });
     * }
     *
     * @param ta What to run, usually as a lambda expression
     */
//    @edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = {"WA_NOT_IN_LOOP", "UW_UNCOND_WAIT"},
//            justification="Method runOnLogixNG() doesn't have a loop. Waiting for single possible event."+
//                    "The thread that is going to call notify() cannot get"+
//                    " it's hands on the lock until wait() is called, "+
//                    " since the caller must first fetch the event from the"+
//                    " event queue and the event is put on the event queue in"+
//                    " the synchronize block.")
    /*public*/ void LogixNG_Thread::runOnLogixNG(/*@Nonnull*/  ThreadAction* ta) {
#if 0
        if (_logixNGThread != nullptr) {

            Object lock = new Object();
            synchronized(lock) {
                _eventQueue.add(new ThreadEvent(ta, lock));
                try {
                    lock.wait();
                } catch (InterruptedException e) {
                    log.debug("Interrupted while running on LogixNG thread");
                    Thread.currentThread().interrupt();
                }
            }
        } else {
            throw new RuntimeException("LogixNG thread not started. ThreadID: "+Integer.toString(_threadID));
        }
#endif
    }

    /**
     * Run some LogixNG-specific code at some later point.
     * <p>
     * Please note the operation may have happened before this returns. Or
     * later. No long-term guarantees.
     * <p>
     * Typical uses:
     * <p> {@code
     * ThreadingUtil.runOnLogixNGEventually(() -> {
     *     sensor.setState(value);
     * });
     * }
     *
     * @param ta What to run, usually as a lambda expression
     */
    /*public*/ void LogixNG_Thread::runOnLogixNGEventually(/*@Nonnull*/  ThreadAction* ta) {
        if (_logixNGThread != nullptr) {
            _eventQueue->enqueue(new ThreadEvent(ta));
        } else {
            throw new RuntimeException("LogixNG thread not started");
        }
    }

    /**
     * Run some LogixNG-specific code at some later point, at least a known time
     * in the future.
     * <p>
     * There is no long-term guarantee about the accuracy of the interval.
     * <p>
     * Typical uses:
     * <p> {@code
     * ThreadingUtil.runOnLogixNGDelayed(() -> {
     *     sensor.setState(value);
     * }, 1000);
     * }
     *
     * @param ta    What to run, usually as a lambda expression
     * @param delay interval in milliseconds
     * @return reference to timer object handling delay so you can cancel if desired; note that operation may have already taken place.
     */
    /*@Nonnull*/
    /*public*/ Timer* LogixNG_Thread::runOnLogixNGDelayed(/*@Nonnull*/  ThreadAction* ta, int delay) {
        if (_logixNGThread != nullptr) {
            // dispatch to logixng thread via timer. We are forced to use a
            // Swing Timer since the method returns a Timer object and we don't
            // want to change the method interface.

            Timer* timer = new Timer(delay, new LNGTimerActionListener(ta, this));
//                                     (JActionEvent e) -> {
                // Dispatch the event to the LogixNG event handler once the time
                // has passed.
//                _eventQueue->enque(new ThreadEvent(ta));
//            });
            timer->setRepeats(false);
            timer->start();
            return timer;
        } else {
            throw new  RuntimeException("LogixNG thread not started");
        }
    }

    /**
     * Check if on the LogixNG-operation thread.
     *
     * @return true if on the LogixNG-operation thread
     */
    /*public*/ bool LogixNG_Thread::isLogixNGThread() {
        if (_logixNGThread != nullptr) {
            return _logixNGThread == QThread::currentThread();
        } else {
            throw new RuntimeException("LogixNG thread not started");
        }
    }

    /**
     * Checks if the the current thread is the LogixNG thread.
     * The check is only done if debug is enabled.
     */
    /*public*/ void LogixNG_Thread::checkIsLogixNGThread() {
        if (log->isDebugEnabled()) {
            if (!isLogixNGThread()) {
                LoggingUtil::warnOnce(log, "checkIsLogixNGThread() called on wrong thread"/*, new Exception()*/);
            }
        }
    }

//    static /*private*/ class ThreadEvent {
//        /*private*/ final ThreadAction _threadAction;
//        /*private*/ final Object _lock;

//        /*public*/ ThreadEvent(ThreadAction threadAction) {
//            _threadAction = threadAction;
//            _lock = null;
//        }

//        /*public*/ ThreadEvent(ThreadAction threadAction,
//                Object lock) {
//            _threadAction = threadAction;
//            _lock = lock;
//        }
//    }

    /*private*/ void LogixNG_Thread::stopLogixNGThread() {
        /*synchronized(LogixNG_Thread.class)*/ {
            if (_logixNGThread != nullptr) {
                _stopThread = true;
                _logixNGThread->quit();
#if 0
                try {
                    _logixNGThread->join(0);
                } catch (InterruptedException e) {
                    throw new RuntimeException("stopLogixNGThread() was interrupted");
                }
                if (_logixNGThread->getState() != Thread.State.TERMINATED) {
                    throw new RuntimeException("Could not stop logixNGThread. Current state: "+_logixNGThread.getState().name());
                }
#endif
                _threads.remove(_threadID);
                _threadNames.remove(_name);
                _stopThread = false;
            }
        }
    }

    /*public*/ /*static*/ void LogixNG_Thread::stopAllLogixNGThreads() {
        /*synchronized(LogixNG_Thread.class)*/ {
            QList<LogixNG_Thread*> list = QList<LogixNG_Thread*>(_threads.values());
            for (LogixNG_Thread* thread : list) {
                thread->stopLogixNGThread();
            }
        }
    }

    /*public*/ /*static*/ void LogixNG_Thread::assertLogixNGThreadNotRunning() {
        /*synchronized(LogixNG_Thread.class)*/ {
            bool aThreadIsRunning = false;
            for (LogixNG_Thread* thread : _threads.values()) {
                if (!thread->_threadIsStopped) {
                    aThreadIsRunning = true;
                    thread->stopLogixNGThread();
                }
            }
            if (aThreadIsRunning) {
                throw new  RuntimeException("logixNGThread is running");
            }
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* LogixNG_Thread::log = LoggerFactory::getLogger("LogixNG_Thread");
