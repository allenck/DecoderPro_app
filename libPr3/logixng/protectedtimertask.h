#ifndef PROTECTEDTIMERTASK_H
#define PROTECTEDTIMERTASK_H

#include <timertask.h>

class ProtectedTimerTask : public TimerTask
{
  Q_OBJECT

 public:
  explicit ProtectedTimerTask(QObject *parent = nullptr) : TimerTask(parent) {setObjectName("ProtectedTimerTask");}
  /*public*/  /*abstract*/ virtual void execute()=0;
  /*public*/  /*final*/ void run()override;
  /*public*/  void stopTimer();

 private:
  /*private*/ /*final*/ QObject* _lock = new QObject();
  /*private*/ bool _timerIsRunning = false;
  /*private*/ bool _stopTimer = false;
  QMutex mutex1;
};

#endif // PROTECTEDTIMERTASK_H
