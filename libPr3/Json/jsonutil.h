#ifndef JSONUTIL_H
#define JSONUTIL_H

#include <QObject>
#include "logger.h"
#include "jsonexception.h"
#include "train.h"
#include "location.h"
class JsonUtil : public QObject
{
 Q_OBJECT
public:
 explicit JsonUtil(ObjectMapper mapper, QObject *parent = nullptr);
 static /*public*/ QJsonObject getTrain(QLocale locale, QString id) throw (JsonException);
 static /*public*/ QJsonArray getTrains(QLocale locale) throw (JsonException);
 static /*public*/ QJsonObject getLocation(QLocale locale, QString id) throw (JsonException);
 static /*public*/ QJsonArray getLocations(QLocale locale) throw (JsonException);
 static /*public*/ QJsonObject getEngine(Operations::Engine* engine);
 static /*public*/ QJsonObject getCar(Operations::Car* car);
 static /*public*/ QJsonObject getCar(QLocale locale, QString id);
 static /*public*/ QJsonObject getEngine(QLocale locale, QString id);

signals:

public slots:

private:
 ///*private*/ static /*final*/ ObjectMapper mapper = new ObjectMapper();
 /*private*/ static /*final*/ Logger* log;// = LoggerFactory.getLogger(JsonUtil.class);
 static /*private*/ QJsonArray getRouteLocationsForTrain(QLocale locale, Operations::Train* train) throw (JsonException);
 static /*private*/ QJsonArray getEnginesForTrain(QLocale locale, Operations::Train* train);
 static /*private*/ QJsonArray getCarsForTrain(QLocale locale, Operations::Train* train);
 static /*private*/ QJsonObject getRollingStock(Operations::RollingStock* rs);
 static /*private*/ QJsonObject getLocation(Operations::Location* location, Operations::RouteLocation* routeLocation);
 static /*private*/ QJsonObject getLocationAndTrack(Operations::Track* track, Operations::RouteLocation* routeLocation);
 static /*private*/ QJsonObject getTrack(Operations::Track* track);

 /*private*/ /*final*/ ObjectMapper mapper;
};

#endif // JSONUTIL_H
