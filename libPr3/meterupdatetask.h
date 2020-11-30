#ifndef METERUPDATETASK_H
#define METERUPDATETASK_H

#include <QObject>
#include "timertask.h"
#include "logger.h"

class UpdateTask02;
class Meter;
class MeterUpdateTask : public QObject
{
  Q_OBJECT
 public:
  explicit MeterUpdateTask(QObject *parent = nullptr);
  /*public*/ MeterUpdateTask(int interval, QObject *parent = nullptr);
  /*public*/ void addMeter(Meter* m);
  /*public*/ void removeMeter(Meter* m);
  /*public*/ void enable(Meter* m);
  /*public*/ void disable(Meter* m);
  /*public*/ void initTimer();
  /*public*/ /*abstract*/ virtual void requestUpdateFromLayout() {}
  /*public*/ void dispose(Meter* m);

 signals:

 public slots:
 private:
  static Logger* log;
  QMap<Meter*, bool> meters = QMap<Meter*, bool>();
  bool _enabled = false;
  /*private*/ UpdateTask02* _intervalTask = nullptr;
  /*private*/ /*final*/ int _sleepInterval;

 protected:
  /*protected*/ void enable();
  /*protected*/ void disable();

  friend class UpdateTask02;
};

// Timer task for periodic updates...
/*private*/ class UpdateTask02 : public TimerTask
{
  Q_OBJECT
    /*private*/ bool _isEnabled = false;
  MeterUpdateTask* task;
 public:
    /*public*/ UpdateTask02(MeterUpdateTask* task) {
        //super();
   this->task = task;
    }

    /*public*/ void enable() {
        _isEnabled = true;
    }

    /*public*/ void disable() {
        _isEnabled = false;
    }

    //@Override
    /*public*/ void run() {
        if (_isEnabled) {
            task->log->debug("Timer Pop");
            task->requestUpdateFromLayout();
        }
    }
};

#endif // METERUPDATETASK_H
