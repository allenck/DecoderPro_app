#ifndef JSONLIGHTSERVICEFACTORY_H
#define JSONLIGHTSERVICEFACTORY_H
#include "jsonservicefactory.h"

class JsonLightServiceFactory : public JsonServiceFactory
{
public:
 JsonLightServiceFactory(QObject* parent = 0);
 /*public*/ QStringList getTypes();
 /*public*/ JsonSocketService* getSocketService(JsonConnection* connection);
 /*public*/ JsonHttpService* getHttpService(ObjectMapper mapper);
};

#endif // JSONLIGHTSERVICEFACTORY_H
