#ifndef JSONREPORTERSERVICEFACTORY_H
#define JSONREPORTERSERVICEFACTORY_H
#include "jsonservicefactory.h"

class JsonReporterServiceFactory : public JsonServiceFactory
{
public:
 JsonReporterServiceFactory(QObject* parent = 0);
 /*public*/ QStringList getTypes();
 /*public*/ JsonSocketService* getSocketService(JsonConnection* connection);
 /*public*/ JsonHttpService* getHttpService(ObjectMapper mapper);
};

#endif // JSONREPORTERSERVICEFACTORY_H
