#include "jsonsignalheadservicefactory.h"
#include "jsonsignalheadsocketservice.h"
#include "jsonsignalheadhttpservice.h"
#include "jsonsignalhead.h"

JsonSignalHeadServiceFactory::JsonSignalHeadServiceFactory(QObject* parent) : JsonServiceFactory(parent)
{

}
/**
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ class JsonSignalHeadServiceFactory implements JsonServiceFactory {

//@Override
/*public*/ QStringList JsonSignalHeadServiceFactory::getTypes() {
    //return new String[]{SIGNAL_HEAD, SIGNAL_HEADS};
 QStringList l = QStringList();
 l << JsonSignalHead::SIGNAL_HEAD << JsonSignalHead::SIGNAL_HEADS;
 return l;
}

//@Override
/*public*/ JsonSocketService* JsonSignalHeadServiceFactory::getSocketService(JsonConnection* connection) {
    return new JsonSignalHeadSocketService(connection);
}

//@Override
/*public*/ JsonHttpService* JsonSignalHeadServiceFactory::getHttpService(ObjectMapper mapper) {
    return new JsonSignalHeadHttpService(mapper);
}
