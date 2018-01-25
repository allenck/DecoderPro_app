#ifndef JSONCONSISTSERVICEFACTORY_H
#define JSONCONSISTSERVICEFACTORY_H
#include "jsonservicefactory.h"

class JsonConsistServiceFactory : public JsonServiceFactory
{
public:
 JsonConsistServiceFactory(QObject* parent = 0);
 /*public*/ QStringList getTypes();
 /*public*/ JsonSocketService* getSocketService(JsonConnection* connection);
 /*public*/ JsonHttpService* getHttpService(ObjectMapper mapper);
};

#endif // JSONCONSISTSERVICEFACTORY_H
