#include "jsonutilservicefactory.h"
#include "json.h"
#include "jsonutilsocketservice.h"
#include "jsonutilhttpservice.h"

JsonUtilServiceFactory::JsonUtilServiceFactory(QObject* parent) : JsonServiceFactory(parent)
{

}

/**
 *
 * @author Randall Wood
 */
// /*public*/ class JsonUtilServiceFactory implements JsonServiceFactory {

//@Override
/*public*/ QStringList JsonUtilServiceFactory::getTypes() {
    return QStringList() << JSON::GOODBYE <<
        JSON::HELLO <<
        JSON::LOCALE <<
        JSON::METADATA <<
        JSON::NETWORK_SERVICES <<
        JSON::NODE <<
        JSON::PANELS <<
        JSON::PING <<
        JSON::RAILROAD <<
        JSON::SYSTEM_CONNECTIONS;
}

//@Override
/*public*/ JsonSocketService* JsonUtilServiceFactory::getSocketService(JsonConnection* connection) {
    return new JsonUtilSocketService(connection);
}

//@Override
/*public*/ JsonHttpService* JsonUtilServiceFactory::getHttpService(ObjectMapper mapper) {
    return new JsonUtilHttpService(mapper);
}
