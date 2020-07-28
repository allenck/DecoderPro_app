#ifndef TRAINCOMMON_H
#define TRAINCOMMON_H

#include <QObject>
#include <QStringList>
#include "appslib_global.h"

class Logger;
class PrintWriter;
class QDate;
namespace Operations
{
 class CarManager;
 class EngineManager;
 class LocationManager;
 class RollingStock;
 class Location;
 class Train;
 class Engine;
 class Car;
 class Engine;
 class RouteLocation;
 class APPSLIBSHARED_EXPORT TrainCommon : public QObject
 {
  Q_OBJECT
 public:
  explicit TrainCommon(QObject *parent = 0);
  /*public*/ static QString getDate(QDateTime date);
  /*public*/ static QString getDate(bool isModelYear);
  /*public*/ static bool isThereWorkAtLocation(Train* train, Location* location);
  /*public*/ static QString splitString(QString name);
  /*public*/ QString getPickupEngineHeader();
  /*public*/ QString getDropEngineHeader() ;
  /*public*/ QString getPickupCarHeader(bool isManifest, bool isTwoColumnTrack);
  /*public*/ QString getDropCarHeader(bool isManifest, bool isTwoColumnTrack);
  /*public*/ static /*final*/ QString LENGTHABV;// = Setup.LENGTHABV; // Length symbol
  /*public*/ virtual QString pickupEngine(Engine* engine);
  /*public*/ virtual QString dropEngine(Engine* engine);
  /*public*/ static QString padString(QString s, int fieldSize);
  /*public*/ static /*final*/ bool LOCAL;//= true;
  /*public*/ static /*final*/ bool IS_TWO_COLUMN_TRACK;//= true;
  /*public*/ static QString padAndTruncateString(QString s, int fieldSize);
  /*public*/ static QString padAndTruncateString(QString s, int fieldSize, bool enabled);
  /*public*/ QString getLocalMoveHeader(bool isManifest);
  /*public*/ static QString tabString(QString s, int tabSize);
  /*public*/ static QString tabString(QString s, int tabSize, bool enabled);
  /*public*/ void clearUtilityCarTypes();
  /*public*/ static QString formatStringToCommaSeparated(QStringList array);
  /*public*/ void printPickupEngineHeader(PrintWriter* file, bool isManifest);
  /*public*/ void printDropEngineHeader(PrintWriter* file, bool isManifest);
  /*public*/ void printHorizontalLine(PrintWriter* file, bool isManifest);
  /*public*/ void printHorizontalLine(PrintWriter* file, int start, int end);
  /*public*/ void printPickupCarHeader(PrintWriter* file, bool isManifest, bool isTwoColumnTrack);
  /*public*/ void printDropCarHeader(PrintWriter* file, bool isManifest, bool isTwoColumnTrack);
  /*public*/ void printLocalCarMoveHeader(PrintWriter* file, bool isManifest);
  /*public*/ QString pickupUtilityCars(QList<Car*>* carList, Car* car, bool isManifest, bool isTwoColumnTrack);
  /*public*/ int countPickupUtilityCars(QList<Car*>* carList, Car* car, bool isManifest);
  /*public*/ QString pickupCar(Car* car, bool isManifest, bool isTwoColumnTrack);
  /*public*/ QString dropCar(Car* car, bool isManifest, bool isTwoColumnTrack);
  /*public*/ QString localMoveCar(Car* car, bool isManifest);
  /*public*/ void printEngineHeader(PrintWriter* file, bool isManifest);
  /*public*/ void printCarHeader(PrintWriter* file, bool isManifest, bool isTwoColumnTrack);
  /*public*/ QString setoutUtilityCars(QList<Car*>* carList, Car* car, bool isLocal, bool isManifest);
  /*public*/ int countSetoutUtilityCars(QList<Car*>* carList, Car* car, bool isLocal, bool isManifest);
  /*public*/ static QString getISO8601Date(bool isModelYear);
  /*public*/ static QString formatColorString(QString text, QColor color);
  /*public*/ static QString getTextColorString(QString string);
  /*public*/ static QColor getTextColor(QString string);
  /*public*/ static /*final*/ QString HYPHEN;// = "-";

 signals:

 public slots:
 private:
  /*private*/ static bool isThereWorkAtLocation(Train* train, Location* location, QList<RollingStock*>* list);
  /*private*/ QString getHeader(QStringList format, bool isPickup, bool isLocal, bool isEngine);
  /*private*/ QString getEngineAttribute(Engine* engine, QString attribute, bool isPickup);
  QStringList utilityCarTypes;// = QStringList();
  /*private*/ static /*final*/ int UTILITY_CAR_COUNT_FIELD_SIZE;// = 3;
  CarManager* carManager;// = CarManager.instance();
  EngineManager* engineManager;// = EngineManager.instance();
  LocationManager* locationManager;// = LocationManager.instance();
  /*private*/ QString getRollingStockAttribute(RollingStock* rs, QString attribute, bool isPickup, bool isLocal);
  /*private*/ bool checkStringLength(QString string, bool isManifest);
  /*private*/ static void printLine(PrintWriter* file, QString level, QString string);
  /*private*/ static int getLineLength(QString orientation, int fontSize, QString fontName);
  /*private*/ static QSize getPageSize(QString orientation);
  Logger* log;
  /*private*/ bool checkStringLength(QString string, QString orientation, QString fontName, int fontSize);
  /*private*/ void addSearchForCar(PrintWriter* file, Car* car);
  /*private*/ QString getCarAttribute(Car* car, QString attribute, bool isPickup, bool isLocal);
  /*private*/ void pickupEngine(PrintWriter* file, Engine* engine, bool isManifest);
  /*private*/ void dropEngine(PrintWriter* file, Engine* engine, bool isManifest);
  bool printPickupHeader;// = true;
  bool printSetoutHeader;// = true;
  bool printLocalMoveHeader;// = true;
  /*private*/ void pickUpCar(PrintWriter* file, Car* car, QString buf, QStringList format, bool isManifest);
  /*private*/ void dropCar(PrintWriter* file, Car* car, QString buf, QStringList format, bool isLocal,
          bool isManifest);
  /*private*/ bool showUtilityCarLength(QStringList mFormat);
  /*private*/ bool showUtilityCarLoad(QStringList mFormat);
  /*private*/ bool showUtilityCarLocation(QStringList mFormat);
  /*private*/ bool showUtilityCarDestination(QStringList mFormat);
  /*private*/ bool showUtilityCarAttribute(QString string, QStringList mFormat);
  QList<Car*> doneCars;// = new ArrayList<Car>();
 int index;// = 0;
 /*private*/ QString appendSetoutString(QString s, QList<Car*>* carList, RouteLocation* rl, bool local, bool isManifest,
                                        bool isTwoColumnTrack);
 /*private*/ QString appendSetoutString(QString s, QString trackName, QList<Car*>* carList, RouteLocation* rl,
                                       bool isManifest, bool isTwoColumnTrack);
 /*private*/ QString appendSetoutString(QString s, QList<Car*>* carList, RouteLocation* rl, Car* car, bool isManifest,
                                        bool isTwoColumnTrack);

protected:
  /*protected*/ bool isThereWorkAtLocation(QList<Car*>* carList, QList<Engine*>* engList, RouteLocation* rl);
  /*protected*/ static /*final*/ QString TAB;//= "    "; // NOI18N
  /*protected*/ static /*final*/ QString NEW_LINE;//= "\n"; // NOI18N
  /*protected*/ static /*final*/ QString SPACE;//= " ";
  /*protected*/ static /*final*/ QString BLANK_LINE;//= " ";
  /*protected*/ static /*final*/ QString HORIZONTAL_LINE_CHAR;//= "-";
  /*protected*/ static /*final*/ QString VERTICAL_LINE_CHAR;//= "|";
  /*protected*/ static /*final*/ QString TEXT_COLOR_START;// = "<FONT color=\"";
  /*protected*/ static /*final*/ QString TEXT_COLOR_END;// = "</FONT>";
  // /*protected*/ static /*final*/ String ARROW = ">";

  /*protected*/ static /*final*/ bool PICKUP;//= true;
  /*protected*/ static /*final*/ bool IS_MANIFEST;//= true;
  /*protected*/ static /*final*/ bool ENGINE;//= true;
  // for manifests
  /*protected*/ int cars;// = 0;
  /*protected*/ int emptyCars;// = 0;

  // for switch lists
  /*protected*/ bool pickupCars;
  /*protected*/ bool dropCars;
  /*protected*/ void newLine(PrintWriter* file, QString string, bool isManifest);
  /*protected*/ void newLine(PrintWriter* file);
  /*protected*/ static void addLine(PrintWriter* file, QString level, QString string);
  /*protected*/ int getLineLength(bool isManifest);
  /*protected*/ void addLine(PrintWriter* file, QString string);
  /*protected*/ void printTrackComments(PrintWriter* file, RouteLocation* rl, QList<Car*>* carList, bool isManifest);
  /*protected*/ void addCarsLocationUnknown(PrintWriter* file, bool isManifest);
  /*protected*/ void pickupEngines(PrintWriter* file, QList<Engine*>* engineList, RouteLocation* rl, bool isManifest);
  /*protected*/ void dropEngines(PrintWriter* file, QList<Engine*>* engineList, RouteLocation* rl, bool isManifest);
  /*protected*/ void pickupUtilityCars(PrintWriter* file, QList<Car*>* carList, Car* car, bool isManifest);
  /*protected*/ void pickUpCar(PrintWriter* file, Car* car, bool isManifest);
  /*protected*/ void setoutUtilityCars(PrintWriter* file, QList<Car*>* carList, Car* car, bool isManifest);
  /*protected*/ void blockCarsByTrack(PrintWriter* file, Train* train, QList<Car*>* carList, QList<RouteLocation*>* routeList,
          RouteLocation* rl, bool printHeader, bool isManifest);
  /*protected*/ bool isLocalMove(Car* car);
  /*protected*/ void pickUpCarTruncated(PrintWriter* file, Car* car, bool isManifest);
  /*protected*/ void truncatedDropCar(PrintWriter* file, Car* car, bool isManifest);
  /*protected*/ void dropCar(PrintWriter* file, Car* car, bool isManifest);
  /*protected*/ int countUtilityCars(QStringList format, QList<Car*>* carList, Car* car, bool isPickup);
  /*protected*/ void blockLocosTwoColumn(PrintWriter* file, QList<Engine*>* engineList, RouteLocation* rl, bool isManifest);
  /*protected*/ void blockCarsByTrackTwoColumn(PrintWriter* file, Train* train, QList<Car*>* carList,
          QList<RouteLocation*>* routeList, RouteLocation* rl, bool printHeader, bool isManifest);
  /*protected*/ void blockCarsByTrackNameTwoColumn(PrintWriter* file, Train* train,QList<Car*> *carList,
                      QList<RouteLocation*>* routeList, RouteLocation* rl, bool printHeader, bool isManifest);
 /*protected*/ void printTrackNameHeader(PrintWriter* file, QString trackName, bool isManifest);
 /*protected*/ QString setoutUtilityCars(QList<Car*>* carList, Car* car, bool isLocal, bool isManifest,
         bool isTwoColumnTrack);


 friend class CommonConductorYardmasterPanel;
 friend class TrainManifest;
 friend class TrainPrintUtilities;
 friend class TrainSwitchLists;
 friend class Train;
 friend class TrainManager;
 friend class HtmlTrainCommon;
 friend class JsonManifest;
 };
}
#endif // TRAINCOMMON_H
