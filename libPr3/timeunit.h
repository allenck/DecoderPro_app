#ifndef TIMEUNIT_H
#define TIMEUNIT_H

#include <QObject>

class TimeUnit : public QObject
{
    Q_OBJECT
public:
    //explicit TimeUnit(QObject *parent = 0);
    enum TIMEUNIT
    {
     NANOSECONDS,
     MICROSECONDS,
     MILLISECONDS,
     SECONDS,
     MINUTES,
     HOURS,
     DAYS
    };

signals:

public slots:

};

#endif // TIMEUNIT_H
