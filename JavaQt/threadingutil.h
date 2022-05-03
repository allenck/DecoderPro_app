#ifndef THREADINGUTIL_H
#define THREADINGUTIL_H

#include <QObject>
#include "runnable.h"

class Logger;
/**
 * Interface for use in ThreadingUtil's lambda interfaces
 */
//@FunctionalInterface
/*static*/ /*public*/ /*interface*/ class ThreadAction : public Runnable {
  Q_OBJECT
 public:
  ThreadAction() : Runnable() {}

    /**
     * {@inheritDoc}
     * <p>
     * Must handle its own exceptions.
     */
    //@Override
  /*public*/ void run() {}
};

/**
 * Interface for use in ThreadingUtil's lambda interfaces
 */
//@FunctionalInterface
/*static*/ /*public*/ /*interface*/class ThreadActionWithJmriException : public Runnable{
  Q_OBJECT
 public:
    /**
     * When an object implementing interface <code>ThreadActionWithJmriException</code>
     * is used to create a thread, starting the thread causes the object's
     * <code>run</code> method to be called in that separately executing
     * thread.
     * <p>
     * The general contract of the method <code>run</code> is that it may
     * take any action whatsoever.
     *
     * @throws JmriException when an exception occurs
     * @throws RuntimeException when an exception occurs
     * @see     java.lang.Thread#run()
     */
  /*public*/ void run() /*throws JmriException, RuntimeException*/{}
};
template <class E>
/*static*/ /*public*/ class ReturningThreadAction : public ThreadAction
{
  //Q_OBJECT
 public:
  ReturningThreadAction() : ThreadAction() {}
 public:
  /*public*/ void run() {}
};

class ThreadingUtil : public QObject
{
  Q_OBJECT
 public:

  explicit ThreadingUtil(QObject *parent = nullptr);
  static /*public*/ QThread* newThread(Runnable* runner);
  static /*public*/ QThread* newThread(Runnable* runner, QString name);
  static /*public*/ void runOnGUI(/*@Nonnull*/ ThreadAction* ta);
  static /*public*/ void runOnGUIEventually(/*@Nonnull*/ ThreadAction* ta) ;
  static /*public*/ void runOnLayout(/*@Nonnull*/ ThreadAction* ta);
  static /*public*/ bool isLayoutThread();
  static /*public*/ bool isGUIThread();
  static /*public*/ void runOnLayoutWithJmriException(ThreadActionWithJmriException* ta);
  static /*public*/ void runOnGUIWithJmriException(/*@Nonnull*/ ThreadActionWithJmriException* ta);
  /**
   * Interface for use in ThreadingUtil's lambda interfaces
   *
   * @param <E> the type returned
   */
  //@FunctionalInterface
  //template<class E>
  template<class E>
  static /*public*/ /*<E>*/ int runOnGUIwithReturn(/*@Nonnull*/ ReturningThreadAction<E>* ta){
   if (isGUIThread()) {
       // run now
       /*return*/ ta->run();
   }
  }
 signals:

 public slots:

 private:
  static Logger* log;
};




#endif // THREADINGUTIL_H
