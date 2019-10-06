#ifndef LOGGINGEVENT_H
#define LOGGINGEVENT_H

#include <QObject>
#include "loglevel.h"
#include "exceptions.h"

class Logger;
class LoggingEvent : public QObject
{
 Q_OBJECT
public:
 explicit LoggingEvent(QObject *parent = nullptr);
 /*public*/ LoggingEvent(/*QString fqnOfCategoryClass,*/ /*Category*/QString loggerName, LogLevel* level, QString message, Throwable* throwable, QObject *parent = nullptr);
 /*public*/ QString getMessage();
 /*public*/ LogLevel* getLevel();
 /*public*/ QString getLoggerName();
 /*public*/ /*final*/ QString categoryName;

signals:

public slots:
private:
 /*private*/ /*transient*/ QString message;
 LogLevel* logLevel;
 int level;
 /*private*/ static qint64 startTime;

 /*private*/ /*transient*/ QString loggerName;
 Throwable* throwable;
};

#endif // LOGGINGEVENT_H
