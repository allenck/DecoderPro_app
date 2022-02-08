#ifndef TIMESINCEMIDNIGHT_H
#define TIMESINCEMIDNIGHT_H

#include "abstractanalogexpression.h"
#include "timebase.h"
#include "timertask.h"

class TYpe;
class TimeSinceMidnight : public AbstractAnalogExpression
{
 public:
  explicit TimeSinceMidnight(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException*/override;

 private:
  /*private*/ Type _type = Type::FastClock;
  /*private*/ Timebase* _fastClock;

  TimerTask* timerTask = nullpt;
  /*private*/ /*final*/ int millisInAMinute = 60000;

};

#endif // TIMESINCEMIDNIGHT_H
