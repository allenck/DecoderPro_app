#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QVariant>
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT Logger : public QObject
{
 Q_OBJECT
public:
 explicit Logger(QString name = "", QObject *parent = 0);
 Logger(const Logger&);
 static void error(QString s, QVariant ex = QVariant());
 void warn(QString s);
 void info(QString s);
 bool isDebugEnabled();
 bool isInfoEnabled();
 void debug(QString s);
 void setDebugEnabled(bool bState);
 void setInfoEnabled(bool bState);
 void sendError(QString s);

signals:

public slots:

private:
 bool bDebugEnabled;
 bool bInfoEnabled;
 QString name;
 QObject *parent;
};

#endif // LOGGER_H
