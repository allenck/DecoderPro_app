#ifndef JSONLAYOUTBLOCKSERVICEFACTORY_H
#define JSONLAYOUTBLOCKSERVICEFACTORY_H
#include "jsonsensorservicefactory.h"

class JsonLayoutBlockServiceFactory : public JsonServiceFactory
{
public:
 JsonLayoutBlockServiceFactory(QObject* parent = 0);
 /*public*/ QStringList getTypes();
 /*public*/ JsonSocketService* getSocketService(JsonConnection*        connection);
 /*public*/ JsonHttpService* getHttpService(ObjectMapper mapper);

};

#endif // JSONLAYOUTBLOCKSERVICEFACTORY_H
