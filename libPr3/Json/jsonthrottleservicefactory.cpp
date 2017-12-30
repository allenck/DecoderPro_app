#include "jsonthrottleservicefactory.h"
#include "json.h"
#include "jsonthrottlesocketservice.h"

JsonThrottleServiceFactory::JsonThrottleServiceFactory(QObject* parent) : JsonServiceFactory(parent)
{

}
/**
 *
 * @author Randall Wood
 */
///*public*/ class JsonThrottleServiceFactory implements JsonServiceFactory {

//@Override
/*public*/ QStringList JsonThrottleServiceFactory::getTypes() {
    QStringList types = QStringList() << JSON::THROTTLE;
    return types;
}

//@Override
/*public*/ JsonSocketService* JsonThrottleServiceFactory::getSocketService(JsonConnection* connection) {
    return new JsonThrottleSocketService(connection);
}

//@Override
/*public*/ JsonHttpService* JsonThrottleServiceFactory::getHttpService(ObjectMapper mapper) {
    return NULL;
}
