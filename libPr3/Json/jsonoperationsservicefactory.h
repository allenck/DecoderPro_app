#ifndef JSONOPERATIONSSERVICEFACTORY_H
#define JSONOPERATIONSSERVICEFACTORY_H
#include "jsonservicefactory.h"

class JsonOperationsServiceFactory : public JsonServiceFactory
{
public:
 JsonOperationsServiceFactory(QObject* parent = 0);
 /*public*/ QStringList getTypes();
 /*public*/ JsonSocketService* getSocketService(JsonConnection* connection);
 /*public*/ JsonHttpService* getHttpService(ObjectMapper mapper);

};

#endif // JSONOPERATIONSSERVICEFACTORY_H
