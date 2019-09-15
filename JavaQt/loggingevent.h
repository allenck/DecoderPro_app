#ifndef LOGGINGEVENT_H
#define LOGGINGEVENT_H

#include <QObject>
#include "loglevel.h"

class LoggingEvent : public QObject
{
 Q_OBJECT
public:
 explicit LoggingEvent(QObject *parent = nullptr);
 /*public*/ LoggingEvent(/*QString fqnOfCategoryClass, Category logger, */Priority* level, QString message, /*Throwable throwable*/QObject *parent = nullptr);
 /*public*/ QString getMessage();
 /*public*/ LogLevel::PVAL getLevel();

signals:

public slots:
private:
 /*private*/ /*transient*/ QString message;
 LogLevel* logLevel;
 LogLevel::PVAL level;
 /*private*/ static qint64 startTime;


};

#endif // LOGGINGEVENT_H
