#ifndef SENSORTURNOUTOPERATOR_H
#define SENSORTURNOUTOPERATOR_H
#include "turnoutoperator.h"
#include "propertychangelistener.h"
#include <QMutex>
#include "logger.h"

class MyPropertyChangeListener;

class SensorTurnoutOperator : public TurnoutOperator
{
    Q_OBJECT
public:
    //explicit SensorTurnoutOperator(QObject *parent = 0);
    /*public*/ SensorTurnoutOperator(AbstractTurnout* t, long i, int mt, QObject *parent = 0);
    /*public*/ void run();

signals:

public slots:
private:
    long interval;
    int maxTries;
    int tries;// = 0;
    MyPropertyChangeListener* listener;
    friend class MyPropertyChangeListener;
    QMutex mutex;
    Logger* log;
};
class MyPropertyChangeListener : public PropertyChangeListener
{
 Q_OBJECT
 public:
    MyPropertyChangeListener(SensorTurnoutOperator* self)
    {
     this->self = self;
    }
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e)
    {
     if (e->getPropertyName()==("KnownState"))
     {
      /*synchronized(this) */
      {
       QMutexLocker locker(&mutex);
// TODO:                self->notify();
      }
     }
    }
private:
    SensorTurnoutOperator* self;
    QMutex mutex;
};

#endif // SENSORTURNOUTOPERATOR_H
