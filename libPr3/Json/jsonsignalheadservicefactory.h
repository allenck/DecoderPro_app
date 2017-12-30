#ifndef JSONSIGNALHEADSERVICEFACTORY_H
#define JSONSIGNALHEADSERVICEFACTORY_H
#include "jsonservicefactory.h"

class JsonSignalHeadServiceFactory : public JsonServiceFactory
{
public:
 JsonSignalHeadServiceFactory(QObject* parent = 0);
 /*public*/ QStringList getTypes();
 /*public*/ JsonSocketService* getSocketService(JsonConnection* connection);
 /*public*/ JsonHttpService* getHttpService(ObjectMapper mapper);
};
#endif // JSONSIGNALHEADSERVICEFACTORY_H
