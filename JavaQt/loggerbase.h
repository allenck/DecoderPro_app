#ifndef LOGGERBASE_H
#define LOGGERBASE_H

#include <QObject>
#include <QVariant>
#include "javaqt_global.h"
#include "exceptions.h"

class JAVAQTSHARED_EXPORT LoggerBase : public QObject
{
 Q_OBJECT
public:
 explicit LoggerBase(QString name = "", QObject *parent = 0);
 LoggerBase(const LoggerBase&);
 static void error(QString s, QVariant ex = QVariant());
 static void error(QString s, Throwable thrbl);
 static void warn(QString name,QString s);
 static void info(QString name,QString s);
 static void trace(QString name,QString s);
// bool isDebugEnabled();
// bool isInfoEnabled();
// bool isTraceEnabled();
 static void debug(QString name,QString s);
// void setDebugEnabled(bool bState);
// void setInfoEnabled(bool bState);
 static void sendError(QString name,QString s);

signals:

public slots:

private:
// bool bDebugEnabled;
// bool bInfoEnabled;
// bool bTraceEnabled;
// QString name;
 QObject *parent;
 };

#endif // LOGGERBASE_H
