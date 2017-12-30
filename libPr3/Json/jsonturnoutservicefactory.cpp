#include "jsonturnoutservicefactory.h"
#include "jsonturnoutsocketservice.h"
#include "jsonturnouthttpservice.h"
/**
 *
 * @author Randall Wood
 */
// /*public*/ class JsonTurnoutServiceFactory implements JsonServiceFactory {

JsonTurnoutServiceFactory::JsonTurnoutServiceFactory(QObject* parent) : JsonServiceFactory(parent)
{

}

/*public*/ /*static*/ /*final*/ QString JsonTurnoutServiceFactory::TURNOUT = "turnout"; // NOI18N
/*public*/ /*static*/ /*final*/ QString JsonTurnoutServiceFactory::TURNOUTS = "turnouts"; // NOI18N

//@Override
/*public*/ QStringList JsonTurnoutServiceFactory::getTypes() {
    return  QStringList() << TURNOUT << TURNOUTS;
}

//@Override
/*public*/ JsonSocketService* JsonTurnoutServiceFactory::getSocketService(JsonConnection* connection) {
    return new JsonTurnoutSocketService(connection);
}

//@Override
/*public*/ JsonHttpService* JsonTurnoutServiceFactory::getHttpService(ObjectMapper mapper) {
    return new JsonTurnoutHttpService(mapper);
}
