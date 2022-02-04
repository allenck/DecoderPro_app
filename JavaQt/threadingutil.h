#ifndef THREADINGUTIL_H
#define THREADINGUTIL_H

#include <QObject>
#include "runnable.h"

class Logger;
class ThreadAction;
class ThreadingUtil : public QObject
{
  Q_OBJECT
 public:
  explicit ThreadingUtil(QObject *parent = nullptr);
  static /*public*/ QThread* newThread(Runnable* runner);
  static /*public*/ QThread* newThread(Runnable* runner, QString name);
  static /*public*/ void runOnGUI(/*@Nonnull*/ ThreadAction* ta);
  template<class E>
  static /*public*/ /*<E>*/ E runOnGUIwithReturn(/*@Nonnull*/ /*ReturningThreadAction<E>*/ThreadAction* ta);
  static /*public*/ void runOnGUIEventually(/*@Nonnull*/ ThreadAction* ta) ;
  static /*public*/ void runOnLayout(/*@Nonnull*/ ThreadAction* ta);

 signals:

 public slots:

 private:
  static Logger* log;
};
/**
 * Interface for use in ThreadingUtil's lambda interfaces
 */
//@FunctionalInterface
/*static*/ /*public*/ /*interface*/ class ThreadAction : public Runnable {
  Q_OBJECT
 public:
    /**
     * {@inheritDoc}
     * <p>
     * Must handle its own exceptions.
     */
    //@Override
  /*public*/ void run() {}
};
#endif // THREADINGUTIL_H
