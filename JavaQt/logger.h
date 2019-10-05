#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QVariant>
#include "javaqt_global.h"
#include "exceptions.h"

class LoggingEvent;
class JAVAQTSHARED_EXPORT Logger : public QObject
{
 Q_OBJECT
public:
 explicit Logger(QString name = "", QObject *parent = 0);
 Logger(const Logger&);
 static void error(QString s, QVariant ex = QVariant());
 static void error(QString s, Throwable ex);
 void warn(QString s);
 void info(QString s);
 void trace(QString s);
 bool isDebugEnabled();
 bool isInfoEnabled();
 bool isTraceEnabled();
 void debug(QString s);
 void debug(QString s, Throwable throwable);
 void setDebugEnabled(bool bState);
 void setInfoEnabled(bool bState);
 void setTraceEnabled(bool bState);

 void sendError(QString /*s*/) {}

signals:

public slots:

private:
 bool bDebugEnabled;
 bool bInfoEnabled;
 bool bTraceEnabled;
 QString name;
 QObject *parent;
};

#endif // LOGGER_H
