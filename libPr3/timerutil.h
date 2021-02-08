#ifndef TIMERUTIL_H
#define TIMERUTIL_H

#include <QObject>
#include <QTimer>
#include "timertask.h"
#include <QDebug>

class TUTimer;
class TimerUtil : public QObject
{
 Q_OBJECT
public:
 static /*public*/ void scheduleAtFixedRate(/*@Nonnull*/ TimerTask* task, long delay, long period);
 static /*public*/ void schedule(/*@Nonnull*/ TimerTask* task, long delay);
 static /*public*/ void schedule(/*@Nonnull*/ TimerTask* task, long delay, long period);

signals:

public slots:
protected:
 explicit TimerUtil(QObject *parent = nullptr);

private:
 /*final*/ static TUTimer* commonTimer;// = new QTimer("JMRI Common Timer", true);
};

class TUTimer : public QTimer
{
 Q_OBJECT
 TUTimer(QString name, bool isDaemon)
 {
  this->setObjectName(name);
 }

 /*public*/ void schedule(TimerTask* task, long delay, long period)
 {
  this->task = task;
  this->delay = delay;
  this->period = period;
  setSingleShot(false);
  setInterval(period);
  connect(this, SIGNAL(timeout()), task, SLOT(run()));
  start(delay);
  qDebug() << tr("timer %1 started").arg(objectName());
 }

 /*public*/ void schedule(TimerTask* task, long delay)
 {
  this->task = task;
  this->delay = delay;
  this->period = 0;
  setSingleShot(true);
  //setInterval(period);
  connect(this, SIGNAL(timeout()), task, SLOT(run()));
  start(delay);
  qDebug() << tr("timer %1 started").arg(objectName());
 }
private:
 TimerTask* task = nullptr;
 long delay;
 long period;

private slots:
 void timeout()
 {
  if(task)
   task->run();
 }
 friend class TimerUtil;
};
#endif // TIMERUTIL_H
