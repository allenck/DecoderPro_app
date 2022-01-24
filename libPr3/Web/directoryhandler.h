#ifndef DIRECTORYHANDLER_H
#define DIRECTORYHANDLER_H

#include <QObject>
#include "httpservletrequest.h"
#include "httpservletresponse.h"
#include "resourcehandler.h"

class Resource;
class DirectoryHandler : public ResourceHandler
{
 Q_OBJECT
public:
 /*public*/ DirectoryHandler(QObject *parent=nullptr);
 /*public*/ DirectoryHandler(QString resourceBase, QObject *parent = nullptr);
 /*public*/ DirectoryHandler(QString resourceBase, ResourceHandler* parentHandler,QObject *parent = nullptr);

signals:

public slots:
protected:
 /*protected*/ void doDirectory(HttpServletRequest* request, HttpServletResponse* response, Resource* resource) /*throw (IOException)*/;
friend class RequestHandler;
};

#endif // DIRECTORYHANDLER_H
