#ifndef REENTRANTLOCK_H
#define REENTRANTLOCK_H

#include <QObject>
#include "lock.h"

class ReentrantLock : public QObject, public Lock
{
  Q_OBJECT
  Q_INTERFACES(Lock)
 public:
  explicit ReentrantLock(QObject *parent = nullptr);
  void lock() {}
  void unlock() {}
 signals:

 public slots:
  friend class CountedSensor;
};
#endif // REENTRANTLOCK_H
