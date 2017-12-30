#include "jsonsignalmastservicefactory.h"
#include "jsonsignalmast.h"
#include "jsonsignalmasthttpservice.h"
#include "jsonsignalmastsocketservice.h"

JsonSignalMastServiceFactory::JsonSignalMastServiceFactory(QObject* parent) : JsonServiceFactory(parent)
{

}
/**
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ class JsonSignalMastServiceFactory implements JsonServiceFactory {

//@Override
/*public*/ QStringList JsonSignalMastServiceFactory::getTypes() {
    //return new String[]{SIGNAL_MAST, SIGNAL_MASTS};
 QStringList l = QStringList();
 l << JsonSignalMast::SIGNAL_MAST << JsonSignalMast::SIGNAL_MASTS;
 return l;
}

//@Override
/*public*/ JsonSocketService* JsonSignalMastServiceFactory::getSocketService(JsonConnection* connection) {
    return new JsonSignalMastSocketService(connection);
}

//@Override
/*public*/ JsonHttpService* JsonSignalMastServiceFactory::getHttpService(ObjectMapper mapper) {
    return new JsonSignalMastHttpService(mapper);
}
