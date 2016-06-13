#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include "appslib_global.h"

class APPSLIBSHARED_EXPORT Application : public QObject
{
 Q_OBJECT
public:
 explicit Application(QObject *parent = 0);
 /*public*/ static QString getApplicationName();
 /*public*/ static void setApplicationName(QString applicationName)/* throws IllegalAccessException, IllegalArgumentException*/;
 /*public*/ static QString getLogo();
 /*public*/ static void setLogo(QString logo);
 /*public*/ static QString getURL();
 /*public*/ static void setURL(QString URL);

signals:

public slots:
private:
 /*private*/ static QString name;// = NULL;
 /*private*/ static QString logo;// = "resources/logo.gif";
 /*private*/ static QString URL;// = "http://jmri.org";

};

#endif // APPLICATION_H
