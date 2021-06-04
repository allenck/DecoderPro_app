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

    /**
     * {@inheritDoc}
     * <p>
     * Must handle its own exceptions.
     */
    //@Override
    /*public*/ void run();
};
#endif // THREADINGUTIL_H
