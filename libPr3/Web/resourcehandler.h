#ifndef RESOURCEHANDLER_H
#define RESOURCEHANDLER_H

#include <QObject>
#include "resource.h"

class ContextHandler;
class ResourceHandler : public QObject
{
 Q_OBJECT
public:
 explicit ResourceHandler(QObject *parent = nullptr);
 /*public*/ void setWelcomeFiles(QStringList welcomeFiles);
 /*public*/ void setResourceBase(QString resourceBase);
 /*public*/ bool isDirectoriesListed();
 /*public*/ void setDirectoriesListed(bool directory);
 /*public*/ void setBaseResource(Resource* base);

signals:

public slots:

private:
 /*private*/ static /*final*/ Logger* LOG;// = Log.getLogger(ResourceHandler.class);
 ContextHandler* _context;
 Resource* _baseResource;
 Resource* _defaultStylesheet;
 Resource* _stylesheet;
 QStringList _welcomeFiles;//={"index.html"};
 //MimeTypes _mimeTypes = new MimeTypes();
 QString _cacheControl;
 bool _directory;
 bool _etags;
 int _minMemoryMappedContentLength;//=-1;
 int _minAsyncContentLength;//=0;

};

#endif // RESOURCEHANDLER_H
