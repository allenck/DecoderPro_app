#ifndef JSONBLOCKSERVICEFACTORY_H
#define JSONBLOCKSERVICEFACTORY_H
#include "jsonservicefactory.h"

class JsonBlockServiceFactory : public JsonServiceFactory
{
public:
 JsonBlockServiceFactory(QObject* parent = 0);
 /*public*/ QStringList getTypes();
 /*public*/ JsonSocketService* getSocketService(JsonConnection* connection);
 /*public*/ JsonHttpService* getHttpService(ObjectMapper mapper);
};

#endif // JSONBLOCKSERVICEFACTORY_H
