#ifndef JSONTHROTTLESERVICEFACTORY_H
#define JSONTHROTTLESERVICEFACTORY_H
#include "jsonservicefactory.h"

class JsonThrottleServiceFactory : public JsonServiceFactory
{
public:
 JsonThrottleServiceFactory(QObject* parent = 0);
 /*public*/ QStringList getTypes();
 /*public*/ JsonSocketService* getSocketService(JsonConnection* connection) ;
 /*public*/ JsonHttpService* getHttpService(ObjectMapper mapper);

};

#endif // JSONTHROTTLESERVICEFACTORY_H
