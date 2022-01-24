#ifndef HTMLMANIFEST_H
#define HTMLMANIFEST_H
#include "htmltraincommon.h"
#include "jsonqt.h"
namespace Operations {

class HtmlManifest : public HtmlTrainCommon
{
public:
 /*public*/ HtmlManifest(QLocale locale, Operations::Train* train, QObject* parent = 0) /*throw (IOException)*/;
 /*public*/ QString getLocations() /*throw (IOException)*/;
 /*public*/ QString getValidity();

private:
 /*private*/ QJsonObject jsonManifest;// = null;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(HtmlManifest.class);
 /*protected*/ QString blockCars(QJsonObject cars, Operations::RouteLocation* location,  bool isManifest);
 /*protected*/ QString pickupUtilityCars(QJsonObject cars, QJsonObject car, Operations::RouteLocation* location,  bool isManifest);
 /*protected*/ QString setoutUtilityCars(QJsonObject cars, QJsonObject car, Operations::RouteLocation* location,  bool isManifest);
 /*protected*/ QString pickUpCar(QJsonObject car, QStringList format);
 /*protected*/ QString dropCar(QJsonObject car, QStringList format,  bool isLocal);
 /*protected*/ QString dropEngines(QJsonObject engines);
 /*protected*/ QString dropEngine(QJsonObject engine);
 /*protected*/ QString pickupEngines(QJsonObject engines);
 /*protected*/ QString pickupEngine(QJsonObject engine);
 /*protected*/ QString getDropLocation(QJsonObject location, HtmlTrainCommon::ShowLocation show);
 /*protected*/ QString getPickupLocation(QJsonObject location, HtmlTrainCommon::ShowLocation show);
 /*protected*/ QString getTextAttribute(QString attribute, QJsonObject rollingStock);
 /*protected*/ QString getFormattedAttribute(QString attribute, QString value);
 /*protected*/ QString getFormattedLocation(QJsonObject location, HtmlTrainCommon::ShowLocation show, QString prefix);
 /*private*/ QString getTrackComments(QJsonObject tracks, QJsonObject cars);

protected:
 /*protected*/ ObjectMapper mapper;
 /*protected*/  bool isLocalMove(QJsonObject car);
 /*protected*/  bool isUtilityCar(QJsonObject car);
 /*protected*/ QJsonObject getJsonManifest() /*throw (IOException)*/;

};
}
#endif // HTMLMANIFEST_H
