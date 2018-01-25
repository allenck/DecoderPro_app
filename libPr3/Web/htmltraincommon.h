#ifndef HTMLTRAINCOMMON_H
#define HTMLTRAINCOMMON_H
#include "traincommon.h"
#include "properties.h"
#include "train.h"
namespace  Operations {


class HtmlTrainCommon : public TrainCommon
{
public:
 /*public*/ HtmlTrainCommon(QLocale locale, Operations::Train* train, QObject* parent = 0) throw (IOException);
 /*public*/ QString pickupUtilityCars(QList<Operations::Car*>* carList, Operations::Car* car,  bool isManifest);
 /*public*/ QString pickupEngine(Engine* engine);
 /*public*/ QString dropEngine(Engine* engine);
 /*public*/ QString getValidity();

private:
 static /*private*/ /*final*/ Logger* log;// = LoggerFactory.getLogger(HtmlTrainCommon.class);

protected:
 /*protected*/ /*final*/ Properties* strings = new Properties();
 /*protected*/ /*final*/ QLocale locale;
 /*protected*/ /*final*/ Operations::Train* train;
 /*protected*/ QString resourcePrefix;

 /*protected*/ enum ShowLocation {

     location, track, both
 };
 /*protected*/ QString setoutUtilityCars(QList<Operations::Car*>* carList, Operations::Car* car,  bool isManifest);
 /*protected*/ QString pickUpCar(Operations::Car* car,  QStringList format);
 /*protected*/ QString pickUpCar(Operations::Car* car, int count,  QStringList format);
 /*protected*/ QString dropCar(Operations::Car* car,  QStringList format,  bool isLocal);
 /*protected*/ QString dropCar(Operations::Car* car, int count,  QStringList format,  bool isLocal);
 /*protected*/ QString pickupEngines(QList<Engine*>* engines, RouteLocation* location);
 /*protected*/ QString dropEngines(QList<Engine*>* engines, RouteLocation* location);
 /*protected*/ QString engineChange(RouteLocation* location, int legOptions);
 /*protected*/ QString getTrackComments(RouteLocation* location, QList<Car*>* cars);
 /*protected*/ QString getCarAttribute(Car* car, QString attribute,  bool isPickup,  bool isLocal);
 /*protected*/ QString getEngineAttribute(Engine* engine, QString attribute,  bool isPickup);
 /*protected*/ QString getRollingStockAttribute(RollingStock* rs, QString attribute,  bool isPickup,  bool isLocal);

};
}
class String
{

public:
 static QString format(QString format, QString arg0, QString arg1="", QString arg2= "", QString arg3 = "", QString arg4 = "", QString arg5 = "", QString arg6 = "", QString arg7 = "", QString arg8 = "", QString arg9 = "", QString arg10 = "", QString arg11 = "", QString arg12 = "", QString arg13 = "", QString arg14 = "", QString arg15 = "");

 static QString format(QLocale, QString format, QString arg0, QString arg1="", QString arg2= "", QString arg3 = "", QString arg4 = "", QString arg5 = "", QString arg6 = "", QString arg7 = "", QString arg8 = "", QString arg9 = "", QString arg10 = "", QString arg11 = "", QString arg12 = "", QString arg13 = "", QString arg14 = "", QString arg15 = "");
};

#endif // HTMLTRAINCOMMON_H
