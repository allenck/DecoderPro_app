#ifndef JSONPOWERSERVICEFACTORY_H
#define JSONPOWERSERVICEFACTORY_H
#include "jsonservicefactory.h"

class JsonPowerServiceFactory : public JsonServiceFactory
{
public:
 JsonPowerServiceFactory(QObject* parent = 0);
 /*public*/ static /*final*/ QString POWER;// = "power";
 /*public*/ QStringList getTypes();
 /*public*/ JsonSocketService* getSocketService(JsonConnection* connection);
 /*public*/ JsonHttpService* getHttpService(ObjectMapper mapper);

};

#endif // JSONPOWERSERVICEFACTORY_H
