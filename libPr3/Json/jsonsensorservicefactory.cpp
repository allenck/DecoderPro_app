#include "jsonsensorservicefactory.h"
#include "jsonsensorsocketservice.h"
#include "jsonsensorhttpservice.h"

JsonSensorServiceFactory::JsonSensorServiceFactory()
{

}
/**
 * Factory for JSON services for {@link jmri.Sensor}s.
 *
 * @author Randall Wood
 */
// /*public*/ class JsonSensorServiceFactory implements JsonServiceFactory {


//@Override
/*public*/ QStringList JsonSensorServiceFactory::getTypes() {
 QStringList l = QStringList();
 l << JSON::SENSOR << JSON::SENSORS;
    //return new String[]{SENSOR, SENSORS};
 return l;
}


//@Override
/*public*/ JsonSocketService* JsonSensorServiceFactory::getSocketService(JsonConnection* connection) {
    return new JsonSensorSocketService(connection);
}

//@Override
/*public*/ JsonHttpService* JsonSensorServiceFactory::getHttpService(ObjectMapper mapper) {
    return new JsonSensorHttpService(mapper);
}
