#ifndef JSONUTILSERVICEFACTORY_H
#define JSONUTILSERVICEFACTORY_H
#include "jsonservicefactory.h"

class JsonUtilHttpService;
class JsonUtilSocketService;
class JsonUtilServiceFactory : public JsonServiceFactory
{
public:
 JsonUtilServiceFactory(QObject* parent = 0);
 /*public*/ JsonSocketService* getSocketService(JsonConnection* connection);
 /*public*/ JsonHttpService* getHttpService(ObjectMapper mapper);
 /*public*/ QStringList getTypes();

};

#endif // JSONUTILSERVICEFACTORY_H
