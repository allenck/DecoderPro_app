#ifndef ABSTRACTMULTIMETER_H
#define ABSTRACTMULTIMETER_H

#include <QObject>
#include "multimeter.h"
#include "timertask.h"
#include "bean.h"
#include <QTimer>

class UpdateTask;
class Logger;
class AbstractMultiMeter : public Bean, public MultiMeter
{
 Q_OBJECT
 Q_INTERFACES(MultiMeter)
public:
 explicit AbstractMultiMeter(int interval, QObject *parent = nullptr);
 /*public*/ void enable();
 /*public*/ void disable();
 /*public*/ void setCurrent(float c);
 /*public*/ float getCurrent();
 /*public*/ CurrentUnits getCurrentUnits();
 /*public*/ void setVoltage(float v);
 /*public*/ float getVoltage();
 /*public*/ void dispose();
signals:

public slots:
 void on_timeout();

private:
 static Logger* log;
 QTimer* timer = nullptr;

 //private boolean is_enabled = false;
 /*private*/ UpdateTask* intervalTask = nullptr;
 /*private*/ int sleepInterval = 10000; // default to 10 second sleep interval.

protected:
 /*protected*/ float current_float = 0.0f;
 /*protected*/ float voltage_float = 0.0f;
 /*protected*/ CurrentUnits currentUnits = CurrentUnits::CURRENT_UNITS_PERCENTAGE;
 /*abstract*/ /*protected*/ virtual void requestUpdateFromLayout() =0;
 /*protected*/ void initTimer();

 friend class UpdateTask;
};

/*private*/ class UpdateTask : public TimerTask
{
 Q_OBJECT
    /*private*/ bool is_enabled = false;
 AbstractMultiMeter* amm;

public:
    /*public*/ UpdateTask(AbstractMultiMeter* amm) ;
    /*public*/ void enable();
    /*public*/ void disable();
public slots:
    /*public*/ void run();
    void timeout();
signals:
 void finished();
private:
 static Logger* log;
};

#endif // ABSTRACTMULTIMETER_H
