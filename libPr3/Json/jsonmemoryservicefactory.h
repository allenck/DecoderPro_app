#ifndef JSONMEMORYSERVICEFACTORY_H
#define JSONMEMORYSERVICEFACTORY_H
#include "jsonservicefactory.h"

class JsonMemoryServiceFactory : public JsonServiceFactory
{
 Q_OBJECT
public:
 JsonMemoryServiceFactory(QObject* parent = 0);
 /*public*/ QStringList getTypes();
 /*public*/ JsonSocketService* getSocketService(JsonConnection* connection);
 /*public*/ JsonHttpService* getHttpService(ObjectMapper mapper);

};

#endif // JSONMEMORYSERVICEFACTORY_H
