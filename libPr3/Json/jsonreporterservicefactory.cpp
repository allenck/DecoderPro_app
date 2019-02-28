#include "jsonreporterservicefactory.h"
#include "jsonreporter.h"
#include "jsonreporterhttpservice.h"
#include "jsonreportersocketservice.h"

JsonReporterServiceFactory::JsonReporterServiceFactory(QObject* parent)
{

}
/**
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ class JsonReporterServiceFactory implements JsonServiceFactory {

//@Override
/*public*/ QStringList JsonReporterServiceFactory::getTypes() {
    //return new String[]{REPORTER, REPORTERS};
 QStringList l = QStringList();
 l << JsonReporter::REPORTER, JsonReporter::REPORTERS;
 return l;
}

//@Override
/*public*/ JsonSocketService* JsonReporterServiceFactory::getSocketService(JsonConnection* connection) {
    return new JsonReporterSocketService(connection);
}

//@Override
/*public*/ JsonHttpService* JsonReporterServiceFactory::getHttpService(ObjectMapper mapper) {
    return new JsonReporterHttpService(mapper);
}
