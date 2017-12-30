#include "jsonpowerservicefactory.h"
#include "jsonpowersocketservice.h"
#include "jsonpowerhttpservice.h"

JsonPowerServiceFactory::JsonPowerServiceFactory(QObject* parent) : JsonServiceFactory(parent)
{

}
/**
 *
 * @author Randall Wood
 */
// /*public*/ class JsonPowerServiceFactory implements JsonServiceFactory {

/**
 * Token for type and name for power status messages.
 *
 * {@value #POWER}
 */
/*public*/ /*static*/ /*final*/ QString JsonPowerServiceFactory::POWER = "power";

//@Override
/*public*/ QStringList JsonPowerServiceFactory::getTypes() {
    QStringList types = QStringList() << POWER;
    return types;
}

//@Override
/*public*/ JsonSocketService* JsonPowerServiceFactory::getSocketService(JsonConnection* connection) {
    return new JsonPowerSocketService(connection);
}

//@Override
/*public*/ JsonHttpService* JsonPowerServiceFactory::getHttpService(ObjectMapper mapper) {
    return new JsonPowerHttpService(mapper);
}
