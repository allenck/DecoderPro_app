#include "jsonlightservicefactory.h"
#include "json.h"
#include "jsonlightsocketservice.h"
#include "jsonlighthttpservice.h"

JsonLightServiceFactory::JsonLightServiceFactory(QObject* parent) : JsonServiceFactory(parent)
{

}
/**
 *
 * @author Randall Wood
 */
///*public*/ class JsonLightServiceFactory implements JsonServiceFactory {


//@Override
/*public*/ QStringList JsonLightServiceFactory::getTypes()
{
 QStringList l = QStringList();
 l << JSON::LIGHT << JSON::LIGHTS;
 return l;
}

//@Override
/*public*/ JsonSocketService* JsonLightServiceFactory::getSocketService(JsonConnection* connection) {
    return new JsonLightSocketService(connection);
}

//@Override
/*public*/ JsonHttpService* JsonLightServiceFactory::getHttpService(ObjectMapper mapper) {
    return new JsonLightHttpService(mapper);
}
