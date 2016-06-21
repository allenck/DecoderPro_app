#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include "appslib_global.h"

class Properties;
class APPSLIBSHARED_EXPORT System : public QObject
{
 Q_OBJECT
public:
 explicit System(QObject *parent = 0);
 /*public*/ static QString getProperty(QString key);
 /*public*/ static void setProperty(QString key, QVariant value);
 /*public*/ static Properties* getProperties();

signals:

public slots:
private:
 static Properties* props;
};

#endif // SYSTEM_H
