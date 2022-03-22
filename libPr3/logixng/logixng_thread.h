#ifndef LOGIXNG_THREAD_H
#define LOGIXNG_THREAD_H

#include <QObject>
#include <QThread>
#include <QQueue>
#include "actionlistener.h"
#include "exceptions.h"
#include "threadingutil.h"

class Timer;
class ThreadEvent;
class ThreadAction;
class Logger;
class LogixNG_Thread : public QThread
{
  Q_OBJECT
 public:
  //explicit LogixNG_Thread(QObject *parent = nullptr);
  /*public*/ static /*final*/ const int DEFAULT_LOGIXNG_THREAD;// = 0;
  /*public*/ static /*final*/ const int DEFAULT_LOGIXNG_DEBUG_THREAD;// = 1;
  /*public*/ static LogixNG_Thread* createNewThread(/*@Nonnull*/  QString name);
  /*public*/ static LogixNG_Thread* createNewThread(int threadID, /*@Nonnull*/  QString name);
  /*public*/ static bool validateNewThreadName(/*@Nonnull*/  QString name);
  /*public*/ static LogixNG_Thread* getThread(int threadID);
  /*public*/ static int getThreadID(QString name);
  /*public*/ static void deleteThread(LogixNG_Thread* thread);
  /*public*/ static QSet<LogixNG_Thread*> getThreads();
  /*public*/ QThread* getThread();
  /*public*/ int getThreadId();
  /*public*/ QString getThreadName();
  /*public*/ void setThreadName(/*@Nonnull*/  QString name);
  /*public*/ bool getThreadInUse();
  /*public*/ void setThreadInUse();
  /*public*/ void runOnLogixNG(/*@Nonnull*/  ThreadAction* ta);
  /*public*/ void runOnLogixNGEventually(/*@Nonnull*/  ThreadAction* ta);
  /*public*/ Timer* runOnLogixNGDelayed(/*@Nonnull*/  ThreadAction* ta, int delay);
  /*public*/ bool isLogixNGThread();
  /*public*/ void checkIsLogixNGThread();
  /*public*/ static void stopAllLogixNGThreads();
  /*public*/ static void assertLogixNGThreadNotRunning();

 signals:

 private:
  static Logger* log;
  /*private*/ static /*final*/ QMap<int, LogixNG_Thread*> _threads;// = new HashMap<>();
  /*private*/ static /*final*/ QMap<QString, LogixNG_Thread*> _threadNames;// = new HashMap<>();
  /*private*/ static int _highestThreadID;// = -1;
  /*private*/ /*final*/ int _threadID;
  /*private*/ QString _name;
  /*private*/ volatile bool _stopThread = false;
  /*private*/ volatile bool _threadIsStopped = false;

  /*private*/ /*final*/ /*Thread*/QThread* _logixNGThread;
  /*private*/ bool _threadInUse = false;
  /*private*/ /*final*/ /*BlockingQueue*/QQueue<ThreadEvent*>* _eventQueue=nullptr;
  /*private*/ LogixNG_Thread(int threadID, QString name, QObject* parent= nullptr);
  /*private*/ void stopLogixNGThread();
  QMutex mutex;
  QMutex mutex1;

  friend class LNGTimerActionListener;
  friend class NGThread;
};

/*static*/ /*private*/ class ThreadEvent : public QObject{
  Q_OBJECT
    /*private*/ /*final*/ ThreadAction* _threadAction;
    /*private*/ /*final*/ QObject* _lock;
public:
    /*public*/ ThreadEvent(ThreadAction* threadAction) {
        _threadAction = threadAction;
        _lock = nullptr;
    }

    /*public*/ ThreadEvent(ThreadAction* threadAction,
            QObject* lock) {
        _threadAction = threadAction;
        _lock = lock;
    }
  friend class NGThread;
};

class LNGTimerActionListener: public QObject, public ActionListener
{
  Q_OBJECT
  Q_INTERFACES(ActionListener)
  LogixNG_Thread* thr;
  ThreadAction* ta;
 public:
  LNGTimerActionListener(ThreadAction* ta, LogixNG_Thread* thr) {this->ta = ta; this->thr = thr;}
  QObject* self() override {return (QObject*)this;}
 public slots:
  void actionPerformed(JActionEvent */*e*/ = 0)override
  {
   thr->_eventQueue->enqueue(new ThreadEvent(ta));
 }
};

class NGThread : public Runnable
{
  Q_OBJECT
  LogixNG_Thread* thread;
 public:
  NGThread(LogixNG_Thread* thread) {
   if(!thread)
    throw new NullPointerException("LogixNG_Thread is null!");
   this->thread = thread;
   setObjectName("NGThtread");
  }

 public slots:
  void run()
  {
   while (!thread->_stopThread) {
       try {
           if(thread->_eventQueue->isEmpty())
            continue;
           ThreadEvent* event = thread->_eventQueue->dequeue();
           if (event->_lock != nullptr) {
              /* synchronized(event->_lock)*/ {
                   if (!thread->_stopThread) event->_threadAction->run();
//                   event->_lock->notify();
               }
           } else {
               event->_threadAction->run();
           }
       } catch (InterruptedException* ex) {
           QThread::currentThread()->quit();
       }
   }
   thread->_threadIsStopped = true;
  }
};

#endif // LOGIXNG_THREAD_H
