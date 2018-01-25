#include "jsonconsistservicefactory.h"
#include "json.h"
#include "jsonconsisthttpservice.h"
#include "jsonconsistsocketservice.h"

JsonConsistServiceFactory::JsonConsistServiceFactory(QObject* parent) : JsonServiceFactory(parent)
{

}
/**
 *
 * @author Randall Wood Copyright (C) 2016
 */
///*public*/ class JsonConsistServiceFactory implements JsonServiceFactory {


//@Override
/*public*/ QStringList JsonConsistServiceFactory::getTypes() {
    //return new String[]{JsonConsist.CONSIST, JsonConsist.CONSISTS};
 QStringList l = QStringList();
 l << JSON::CONSIST << JSON::CONSISTS;
 return l;
}

//@Override
/*public*/ JsonSocketService* JsonConsistServiceFactory::getSocketService(JsonConnection* connection) {
    return (JsonSocketService*)new JsonConsistSocketService(connection);
}

//@Override
/*public*/ JsonHttpService* JsonConsistServiceFactory::getHttpService(ObjectMapper mapper) {
    return (JsonHttpService*)new JsonConsistHttpService(mapper);
}
