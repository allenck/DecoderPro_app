#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include "javaqt_global.h"

class Logger;
class Properties;
class JAVAQTSHARED_EXPORT System : public QObject
{
 Q_OBJECT
public:
 explicit System(QObject *parent = 0);
 /*public*/ static QString getProperty(QString key, QString dft);
 /*public*/ static QString getProperty(QString key);
 /*public*/ static void setProperty(QString key, QVariant value);
 /*public*/ static Properties* getProperties();
 /*public*/ static QString checkDefault(QString key);
 /*public*/ static /*native*/ long currentTimeMillis();

 /*public*/ static void out(QString);
 /*public*/ static void err(QString);
signals:

public slots:
private:
 static Properties* props;
 static Logger* log;
};

#endif // SYSTEM_H
