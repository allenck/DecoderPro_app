#include "jsonoperationsservicefactory.h"
#include "jsonoperations.h"
#include "json.h"
#include "jsonoperationssocketservice.h"
#include "jsonoperationshttpservice.h"

JsonOperationsServiceFactory::JsonOperationsServiceFactory(QObject* parent) : JsonServiceFactory(parent)
{

}
/**
 * Service factory for the JSON Operations services.
 *
 * @author Randall Wood (c) 2016
 */
///*public*/ class JsonOperationsServiceFactory implements JsonServiceFactory {

//@Override
/*public*/ QStringList JsonOperationsServiceFactory::getTypes() {
    //return new String[]{CARS, ENGINES, LOCATIONS, TRAIN, TRAINS};
    QStringList l = QStringList();
    l << JSON::CARS << JSON::ENGINES<< JSON::LOCATIONS << JSON::TRAIN << JSON::TRAINS;
    return l;
}

//@Override
/*public*/ JsonSocketService* JsonOperationsServiceFactory::getSocketService(JsonConnection* connection) {
    return new JsonOperationsSocketService(connection);
}

//@Override
/*public*/ JsonHttpService* JsonOperationsServiceFactory::getHttpService(ObjectMapper mapper) {
    return (JsonHttpService*)(new JsonOperationsHttpService(mapper));
}
