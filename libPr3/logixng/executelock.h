#ifndef EXECUTELOCK_H
#define EXECUTELOCK_H

#include <QObject>
#include <QMutex>

class ExecuteLock : public QObject
{
  Q_OBJECT
 public:
  explicit ExecuteLock(QObject *parent = nullptr) : QObject(parent) {}
  /*public*/ bool once();
  /*public*/ bool loop();

 signals:

 private:
  /*private*/ bool lock = false;
  /*private*/ bool again = false;
  QMutex mutex;

};

#endif // EXECUTELOCK_H
