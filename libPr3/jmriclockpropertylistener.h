#ifndef JMRICLOCKPROPERTYLISTENER_H
#define JMRICLOCKPROPERTYLISTENER_H
#include "jmrisimplepropertylistener.h"

class Timebase;
class JmriClockPropertyListener : public JmriSimplePropertyListener
{
    Q_OBJECT
public:
    //explicit JmriClockPropertyListener(QObject *parent = 0);
    JmriClockPropertyListener(QString propName, int type, QString name, int varType,
                              Conditional* client, int beginTime, int endTime, QObject *parent = 0);
    /*public*/ void setRange(int beginTime, int endTime);

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt);
private:
    static int SIZE;// = 10;
    int numRanges;// = 0;
    QList<int>* _beginTimes;// = new int[SIZE];
    QList<int>* _endTimes;// = new int[SIZE];
    QList<bool>* _rangeList;// = new boolean[SIZE];
    Timebase* _fastClock;
    int _currentMinutes;
    /*private*/ int fixMidnight(int time);

};

#endif // JMRICLOCKPROPERTYLISTENER_H
