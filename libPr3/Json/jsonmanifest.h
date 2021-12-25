#ifndef JSOMMANIFEST_H
#define JSOMMANIFEST_H
#include "traincommon.h"
#include "jsonqt.h"
#include "file.h"
#include "exceptions.h"

namespace Operations {


class JsonManifest : public TrainCommon
{
public:
 //JsonManifest(QObject* parent = 0);
 /*public*/ JsonManifest(Train* train, QObject* parent = 0);
 /*public*/ File* getFile();
 /*public*/ void build() /*throw (IOException)*/;
 /*public*/ QJsonArray getLocations();

private:
 /*private*/ /*final*/ ObjectMapper mapper;// = new ObjectMapper();
 ///*private*/ /*final*/ JsonUtil utilities = new JsonUtil(mapper);
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(JsonManifest.class);
 /*private*/ QJsonObject getTrackComments(RouteLocation* routeLocation, QList<Car*>* cars);

protected:
 /*protected*/ /*final*/ QLocale locale;// = Locale.getDefault();
 /*protected*/ /*final*/ Train* train;
 /*protected*/ QJsonArray dropEngines(QList<Engine*>* engines, RouteLocation* routeLocation);
 /*protected*/ QJsonArray pickupEngines(QList<Engine*>* engines, RouteLocation* routeLocation);

};
}
#endif // JSOMMANIFEST_H
