#ifndef JSONTURNOUTSERVICEFACTORY_H
#define JSONTURNOUTSERVICEFACTORY_H
#include "jsonservicefactory.h"

class JsonConnection;
class JsonTurnoutServiceFactory : public JsonServiceFactory
{
public:
 JsonTurnoutServiceFactory(QObject* parent = 0);
 /*public*/ static /*final*/ QString TURNOUT;// = "turnout"; // NOI18N
 /*public*/ static /*final*/ QString TURNOUTS;// = "turnouts"; // NOI18N
 /*public*/ QStringList getTypes();
 /*public*/ JsonSocketService* getSocketService(JsonConnection* connection);
 /*public*/ JsonHttpService* getHttpService(ObjectMapper mapper);

};

#endif // JSONTURNOUTSERVICEFACTORY_H
