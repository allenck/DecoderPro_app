#ifndef JSONSIGNALMASTSERVICEFACTORY_H
#define JSONSIGNALMASTSERVICEFACTORY_H
#include "jsonservicefactory.h"

class JsonSignalMastServiceFactory : public JsonServiceFactory
{
public:
 JsonSignalMastServiceFactory(QObject* parent = 0);
 /*public*/ QStringList getTypes();
 /*public*/ JsonSocketService* getSocketService(JsonConnection* connection);
 /*public*/ JsonHttpService* getHttpService(ObjectMapper mapper);
};

#endif // JSONSIGNALMASTSERVICEFACTORY_H
