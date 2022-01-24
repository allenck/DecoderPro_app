#ifndef RESOURCE_H
#define RESOURCE_H

#include <QObject>
#include "exceptions.h"

class Logger;
class Resource : public QObject
{
 Q_OBJECT
public:
 explicit Resource(QObject *parent = nullptr);
 /*public*/ static bool __defaultUseCaches;// = true;
 /*public*/ virtual QString getListHTML(QString base, bool parent) /*throw (IOException)*/;
 /*public*/ static Resource* newResource(QString resource)
     /*throw (MalformedURLException)*/;
 /*public*/ static Resource* newResource(QString resource, bool useCaches)
     /*throw (MalformedURLException)*/;
 /*public*/ static Resource* newResource(QUrl url);
 /*public*/ QString getResourceString();

signals:

public slots:

private:
 /*private*/ static /*final*/ Logger* log;// = LoggerFactory::getLogger("Resource");
 /*private*/ static QString hrefEncodeURI(QString raw);
 /*private*/ static QString deTag(QString raw);
 static Resource* newResource(QUrl url, bool useCaches);
 static QString stringResource;
 friend class DirectoryResource;
};

#endif // RESOURCE_H
