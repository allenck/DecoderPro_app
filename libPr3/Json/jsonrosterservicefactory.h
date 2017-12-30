#ifndef JSONROSTERSERVICEFACTORY_H
#define JSONROSTERSERVICEFACTORY_H
#include "jsonservicefactory.h"
#include "jsonroster.h"

class JsonRosterSocketService;
class JsonRosterServiceFactory : public JsonServiceFactory
{
public:
 JsonRosterServiceFactory(QObject* parent = 0);
 /*public*/ QStringList getTypes();
 /*public*/ JsonSocketService* getSocketService(JsonConnection* connection);
 /*public*/ JsonHttpService* getHttpService(ObjectMapper mapper);

};

#endif // JSONROSTERSERVICEFACTORY_H
