#ifndef JSONSERVICEFACTORY_H
#define JSONSERVICEFACTORY_H
#include "jmriserviceproviderinterface.h"
#include "jsonqt.h"

class JsonSocketService;
class JsonConnection;
class JsonHttpService;
class /*interface*/ JsonServiceFactory : public JmriServiceProviderInterface
{
public:
 JsonServiceFactory(QObject* parent = 0) : JmriServiceProviderInterface(parent) {}
 /**
  * Get the service type(s) for services created by this factory respond to.
  *
  * Types should be single words, in camelCase if needed, unless supporting a
  * plural noun exposed in the JSON 3.0 protocol.
  *
  * If a service returns no types, it will never be used.
  *
  * @return An array of types this service responds to.
  */
 /*public*/ virtual QStringList getTypes() {return QStringList();}

 /**
  * Create a JSON service for the given connection. This connection can be a
  * WebSocket or raw socket.
  *
  * @param connection The connection for this service to respond to.
  * @return A service or null if the service does not support sockets.
  */
 /*public*/ virtual JsonSocketService* getSocketService(JsonConnection* /*connection*/) {return NULL;}

 /**
  * Create a JSON HTTP service.
  *
  * @param mapper The object mapper for the HTTP service to use.
  * @return A servlet or null if the service does not support HTTP.
  */
 /*public*/ virtual JsonHttpService* getHttpService(ObjectMapper /*mapper*/) {return NULL;}
};

#endif // JSONSERVICEFACTORY_H
