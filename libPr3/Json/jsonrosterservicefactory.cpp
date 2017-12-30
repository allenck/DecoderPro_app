#include "jsonrosterservicefactory.h"
#include "jsonrosterhttpservice.h"
#include "jsonrostersocketservice.h"

JsonRosterServiceFactory::JsonRosterServiceFactory(QObject* parent) : JsonServiceFactory(parent)
{

}
/**
 *
 * @author Randall Wood
 */
///*public*/ class JsonRosterServiceFactory implements JsonServiceFactory {

//@Override
/*public*/ QStringList JsonRosterServiceFactory::getTypes() {
    QStringList types = QStringList() << JsonRoster::ROSTER << JsonRoster::ROSTER_ENTRY << JsonRoster::ROSTER_GROUPS << JsonRoster::ROSTER_GROUP;
    return types;
}

//@Override
/*public*/ JsonSocketService* JsonRosterServiceFactory::getSocketService(JsonConnection* connection) {
    return (JsonSocketService*)new JsonRosterSocketService(connection);
}

//@Override
/*public*/ JsonHttpService* JsonRosterServiceFactory::getHttpService(ObjectMapper mapper) {
    return (JsonHttpService*)new JsonRosterHttpService(mapper);
}
