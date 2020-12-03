#ifndef TIMER_H
#define TIMER_H
#include <QTimer>
#include "actionlistener.h"

class Timer : public QTimer
{
 Q_OBJECT
public:
 Timer(QObject* parent= nullptr);
 /*public*/ Timer(int delay, ActionListener* listener, QObject* parent= nullptr);
 /*public*/ void setDelay(int delay);
 /*public*/ int getDelay();
 /*public*/ void setInitialDelay(int initialDelay);
 /*public*/ int getInitialDelay();
 /*public*/ void setRepeats(bool flag);
 /*public*/ bool isRepeats();
 /*public*/ bool start();
 /*public*/ bool reStart();
 /*public*/ bool stop();
 /*public*/ bool isRunning();
   private:
 int initialDelay;
};

#endif // TIMER_H
