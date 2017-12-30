#ifndef JSONSENSORSERVICEFACTORY_H
#define JSONSENSORSERVICEFACTORY_H
#include "jsonservicefactory.h"
#include "json.h"
class JsonSensorServiceFactory : public JsonServiceFactory
{
public:
 JsonSensorServiceFactory();
 /*public*/ QStringList getTypes();
 /*public*/ JsonSocketService* getSocketService(JsonConnection* connection) ;
 /*public*/ JsonHttpService* getHttpService(ObjectMapper mapper);
};

#endif // JSONSENSORSERVICEFACTORY_H
