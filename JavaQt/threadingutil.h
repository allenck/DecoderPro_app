#ifndef THREADINGUTIL_H
#define THREADINGUTIL_H

#include <QObject>
#include "runnable.h"

class Logger;
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

#endif // THREADINGUTIL_H
