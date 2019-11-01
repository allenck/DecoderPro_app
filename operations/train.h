#ifndef TRAIN_H
#define TRAIN_H

#include <QObject>
#include <QColor>
#include <QDomDocument>
#include "propertychangesupport.h"
#include "logger.h"
#include "propertychangeevent.h"
#include <QDomElement>
#include "consist.h"
#include "appslib_global.h"

class File;
class PrintWriter;
class Calendar;
class InstanceManager;
class TrainIcon;
namespace Operations
{
 class Car;
 class TrainIconAnimation;
 class RouteLocation;
 class Route;
 class Track;
 class Engine;
 class APPSLIBSHARED_EXPORT Train : public QObject
 {
  Q_OBJECT
 public:
  //explicit Train(QObject *parent = 0);
  /*public*/ Train(QString id, QString name,QObject *parent=0);
  /*public*/ static /*final*/ QString NONE;// = "";
  /*public*/ void dispose();
  /*public*/ Train(QDomElement e);
  /*public*/ Route* getRoute() ;
  /*public*/ QString getTrainRouteName();
  /*public*/ QString getRawDescription();
  /*public*/ QString getDescription();
  /*public*/ void replaceType(QString oldType, QString newType);
  /*public*/ void deleteTypeName(QString type);
  /*public*/ bool acceptsTypeName(QString type);
  /*public*/ void addTypeName(QString type);
  /*public*/ Track* getTerminationTrack();
  /*public*/ bool acceptsBuiltDate(QString date);
  /*public*/ bool acceptsOwnerName(QString owner);
  /*public*/ QString getRailroadName() ;
  /*public*/ void setRailroadName(QString name);
  /*public*/ bool printManifestIfBuilt();
  /*public*/ bool printManifest(bool isPreview);
  /*public*/ bool openFile();
  /*public*/ bool buildIfSelected();
  /*public*/ void build();
  /*public*/ QString getServiceStatus();
  /*public*/ bool services(PrintWriter* buildReport, Car* car);
  /*public*/ bool move(QString locationName);
  /*public*/ bool moveToNextLocation(QString locationName);

  enum OPTIONS
  {
   // engine change and helper options
   CHANGE_ENGINES = 1, // change engines
   HELPER_ENGINES = 2, // add helper engines
   ADD_CABOOSE = 4, // add caboose
   REMOVE_CABOOSE = 8 // remove caboose
  };
  Q_ENUMS(OPTIONS)
  // property change names
  /*public*/ static /*final*/ QString DISPOSE_CHANGED_PROPERTY ; //"TrainDispose"; // NOI18N
  /*public*/ static /*final*/ QString STOPS_CHANGED_PROPERTY ; //"TrainStops"; // NOI18N
  /*public*/ static /*final*/ QString TYPES_CHANGED_PROPERTY ; //"TrainTypes"; // NOI18N
  /*public*/ static /*final*/ QString BUILT_CHANGED_PROPERTY ; //"TrainBuilt"; // NOI18N
  /*public*/ static /*final*/ QString BUILT_YEAR_CHANGED_PROPERTY ; //"TrainBuiltYear"; // NOI18N
  /*public*/ static /*final*/ QString BUILD_CHANGED_PROPERTY ; //"TrainBuild"; // NOI18N
  /*public*/ static /*final*/ QString ROADS_CHANGED_PROPERTY ; //"TrainRoads"; // NOI18N
  /*public*/ static /*final*/ QString LOADS_CHANGED_PROPERTY ; //"TrainLoads"; // NOI18N
  /*public*/ static /*final*/ QString OWNERS_CHANGED_PROPERTY ; //"TrainOwners"; // NOI18N
  /*public*/ static /*final*/ QString NAME_CHANGED_PROPERTY ; //"TrainName"; // NOI18N
  /*public*/ static /*final*/ QString DESCRIPTION_CHANGED_PROPERTY ; //"TrainDescription"; // NOI18N
  /*public*/ static /*final*/ QString STATUS_CHANGED_PROPERTY ; //"TrainStatus"; // NOI18N
  /*public*/ static /*final*/ QString DEPARTURETIME_CHANGED_PROPERTY ; //"TrainDepartureTime"; // NOI18N
  /*public*/ static /*final*/ QString TRAIN_LOCATION_CHANGED_PROPERTY ; //"TrainLocation"; // NOI18N
  /*public*/ static /*final*/ QString TRAIN_ROUTE_CHANGED_PROPERTY ; //"TrainRoute"; // NOI18N
  /*public*/ static /*final*/ QString TRAIN_REQUIREMENTS_CHANGED_PROPERTY ; //"TrainRequirements"; // NOI18N
  /*public*/ static /*final*/ QString TRAIN_MOVE_COMPLETE_CHANGED_PROPERTY ; //"TrainMoveComplete"; // NOI18N
  /*public*/ static /*final*/ QString TRAIN_ROW_COLOR_CHANGED_PROPERTY ; //"TrianRowColor"; // NOI18N

  // Train status
  /*public*/ static /*final*/ QString TRAIN_RESET ; //Bundle.getMessage("TrainReset");
  /*public*/ static /*final*/ QString RUN_SCRIPTS ; //Bundle.getMessage("RunScripts");
  /*public*/ static /*final*/ QString BUILDING ; //Bundle.getMessage("Building");
  /*public*/ static /*final*/ QString BUILD_FAILED ; //Bundle.getMessage("BuildFailed");
  /*public*/ static /*final*/ QString BUILT ; //Bundle.getMessage("Built");
  /*public*/ static /*final*/ QString PARTIAL_BUILT ; //Bundle.getMessage("Partial");
  /*public*/ static /*final*/ QString TRAIN_IN_ROUTE ; //Bundle.getMessage("TrainInRoute");
  /*public*/ static /*final*/ QString TERMINATED ; //Bundle.getMessage("Terminated");

  // Train status codes
  enum STATUSCODES
  {
   CODE_TRAIN_RESET  = 0,
   CODE_RUN_SCRIPTS  = 0x100,
   CODE_BUILDING  = 0x01,
   CODE_BUILD_FAILED  = 0x02,
   CODE_BUILT  = 0x10,
   CODE_PARTIAL_BUILT  = CODE_BUILT + 0x04,
   CODE_TRAIN_EN_ROUTE  = CODE_BUILT + 0x08,
   CODE_TERMINATED  = 0x80,
   CODE_UNKNOWN = 0xFFFF
};
  // train requirements
  /*public*/ static /*final*/ int NO_CABOOSE_OR_FRED ; //0; // default
  /*public*/ static /*final*/ int CABOOSE ; //1;
  /*public*/ static /*final*/ int FRED ; //2;

  // road options
  /*public*/ static /*final*/ QString ALL_ROADS ; //Bundle.getMessage("All"); // train services all road names
  /*public*/ static /*final*/ QString INCLUDE_ROADS ; //Bundle.getMessage("Include");
  /*public*/ static /*final*/ QString EXCLUDE_ROADS ; //Bundle.getMessage("Exclude");

  // owner options
  /*public*/ static /*final*/ QString ALL_OWNERS ; //Bundle.getMessage("All"); // train services all owner names
  /*public*/ static /*final*/ QString INCLUDE_OWNERS ; //Bundle.getMessage("Include");
  /*public*/ static /*final*/ QString EXCLUDE_OWNERS ; //Bundle.getMessage("Exclude");

  // load options
  /*public*/ static /*final*/ QString ALL_LOADS ; //Bundle.getMessage("All"); // train services all loads
  /*public*/ static /*final*/ QString INCLUDE_LOADS ; //Bundle.getMessage("Include");
  /*public*/ static /*final*/ QString EXCLUDE_LOADS ; //Bundle.getMessage("Exclude");

  // Switch list status
  /*public*/ static /*final*/ QString UNKNOWN ; //"";
  /*public*/ static /*final*/ QString PRINTED ; //Bundle.getMessage("Printed");

  /*public*/ static /*final*/ QString AUTO ; //Bundle.getMessage("Auto"); // how engines are assigned to this train
  /*public*/ static /*final*/ QString AUTO_HPT ; //Bundle.getMessage("AutoHPT"); // how engines are assigned to this train
  /*public*/ QString getId();
  /*public*/ void setName(QString name);
  /*public*/ QString toString();
  /*public*/ QString getName();
  /*public*/ QString getTableRowColorName();
  /*public*/ void setTableRowColorName(QString colorName);
  /*public*/ QColor getTableRowColor();
  PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
  /*public*/ QDomElement store(QDomDocument doc);
  /*public*/ QString getLeadEngineNumber();
  /*public*/ void setRoute(Route* route);
  /*public*/ QString getIconName();
  /*public*/ void loadTrainIcon();
  /*public*/ QString getCurrentLocationName();
  /*public*/ RouteLocation* getCurrentLocation();
  /*public*/ QString getTrainDepartsName();
  /*public*/ void createTrainIcon();
  /*public*/ QString getLeadEngineRoadName();
  /*public*/ QString getLeadEngineRoadAndNumber();
  /*public*/ Engine* getLeadEngine();
  /*public*/ void setLeadEngine(Engine* engine);
  /*public*/ QString getTrainTerminatesName();
  /*public*/ QString getNextLocationName() ;
  /*public*/ QString getNextLocationName(int number);
  /*public*/ RouteLocation* getNextLocation(RouteLocation* currentRouteLocation);
  /*public*/ bool isBuilt();
  /*public*/ void setNumberEngines(QString number);
  /*public*/ QString getNumberEngines();
  /*public*/ QString getSecondLegNumberEngines();
  /*public*/ void setSecondLegNumberEngines(QString number);
  /*public*/ QString getThirdLegNumberEngines();
  /*public*/ void setThirdLegNumberEngines(QString number);
  /*public*/ void setEngineRoad(QString road);
  /*public*/ QString getEngineRoad() ;
  /*public*/ void setSecondLegEngineRoad(QString road) ;
  /*public*/ QString getSecondLegEngineRoad();
  /*public*/ void setThirdLegEngineRoad(QString road);
  /*public*/ QString getThirdLegEngineRoad();
  /*public*/ void setEngineModel(QString model) ;
  /*public*/ QString getEngineModel();
  /*public*/ void setSecondLegEngineModel(QString model) ;
  /*public*/ QString getSecondLegEngineModel();
  /*public*/ void setThirdLegEngineModel(QString model);
  /*public*/ QString getThirdLegEngineModel() ;
  /*public*/ void setCabooseRoad(QString road);
  /*public*/ QString getCabooseRoad();
  /*public*/ void setSecondLegCabooseRoad(QString road);
  /*public*/ QString getSecondLegCabooseRoad();
  /*public*/ void setThirdLegCabooseRoad(QString road);
  /*public*/ QString getThirdLegCabooseRoad();
  /*public*/ void setSecondLegStartLocation(RouteLocation* rl) ;
  /*public*/ RouteLocation* getSecondLegStartLocation();
  /*public*/ QString getSecondLegStartLocationName() ;
  /*public*/ void setThirdLegStartLocation(RouteLocation* rl) ;
  /*public*/ RouteLocation* getThirdLegStartLocation();
  /*public*/ QString getThirdLegStartLocationName();
  /*public*/ void setSecondLegEndLocation(RouteLocation* rl);
  /*public*/ QString getSecondLegEndLocationName() ;
  /*public*/ RouteLocation* getSecondLegEndLocation();
  /*public*/ void setThirdLegEndLocation(RouteLocation* rl);
  /*public*/ RouteLocation* getThirdLegEndLocation() ;
  /*public*/ QString getThirdLegEndLocationName();
  /*public*/ void setSecondLegOptions(int options) ;
  /*public*/ int getSecondLegOptions() ;
  /*public*/ void setThirdLegOptions(int options) ;
  /*public*/ int getThirdLegOptions();
  /*public*/ void setComment(QString comment);
  /*public*/ QString getComment(bool asText = true);
//  /*public*/ QString getComment();
  /*public*/ QString getRoadOption();
  /*public*/ void setRoadOption(QString option);
  /*public*/ QStringList getRoadNames();
  /*public*/ bool addRoadName(QString road);
  /*public*/ bool deleteRoadName(QString road);
  /*public*/ bool acceptsRoadName(QString road);
  /*public*/ bool services(Car* car);
  /*public*/ QString getBuiltStartYear();
  /*public*/ QString getBuiltEndYear();
  /*public*/ bool isTrainInRoute();
  /*public*/ void setModified(bool modified) ;
  /*public*/ bool isModified();
  /*public*/ static /*final*/ QString ALREADY_SERVICED;// = "-1"; // NOI18N
  /*public*/ int getNumberEmptyCarsInTrain(RouteLocation* routeLocation);
  /*public*/ int getTrainLength();
  /*public*/ int getNumberCarsInTrain();
  /*public*/ int getNumberCarsInTrain(RouteLocation* routeLocation);
  /*public*/ int getTrainLength(RouteLocation* routeLocation);
  /*public*/ int getTrainWeight();
  /*public*/ int getTrainWeight(RouteLocation* routeLocation);
  /*public*/ QString getExpectedArrivalTime(RouteLocation* routeLocation) ;
  /*public*/ QString getExpectedDepartureTime(RouteLocation* routeLocation);
  /*public*/ bool isBuildEnabled();
  /*public*/ QString getDepartureTime();
  /*public*/ Track* getDepartureTrack();
  /*public*/ int getStatusCode();
  /*public*/ QString getStatus();
  /*public*/ bool getBuildFailed();
  /*public*/ bool acceptsLoadName(QString load);
  /*public*/ bool acceptsLoad(QString load, QString type);
  /*public*/ QString getOwnerOption();
  /*public*/ void setOwnerOption(QString option);
  /*public*/ QStringList getLoadNames();
  /*public*/ bool addLoadName(QString load);
  /*public*/ bool deleteLoadName(QString load);
  /*public*/ bool isPrinted();
  /*public*/ void terminate();
  /*public*/ void move();
  /*public*/ void setStatus(int status);
  /*public*/ bool isLocalSwitcher();
  /*public*/ void addTrainSkipsLocation(QString locationId);
  /*public*/ void deleteTrainSkipsLocation(QString locationId);
  /*public*/ bool skipsLocation(QString locationId);
  /*public*/ QString getFormatedDepartureTime();
  /*public*/ int getDepartTimeMinutes();
  /*public*/ void setDepartureTime(QString hour, QString minute) ;
  /*public*/ QString getDepartureTimeHour() ;
  /*public*/ QString getDepartureTimeMinute();
  /*public*/ QString getLoadOption();
  /*public*/ void setLoadOption(QString option);
  /*public*/ void addBuildScript(QString pathname);
  /*public*/ void deleteBuildScript(QString pathname);
  /*public*/ QStringList getBuildScripts();
  /*public*/ void addAfterBuildScript(QString pathname);
  /*public*/ void deleteAfterBuildScript(QString pathname);
  /*public*/ QStringList getAfterBuildScripts();
  /*public*/ void addMoveScript(QString pathname);
  /*public*/ void deleteMoveScript(QString pathname);
  /*public*/ QStringList getMoveScripts();
  /*public*/ void addTerminationScript(QString pathname);
  /*public*/ void deleteTerminationScript(QString pathname);
  /*public*/ QStringList getTerminationScripts();
  /*public*/ QStringList getOwnerNames();
  /*public*/ bool addOwnerName(QString owner);
  /*public*/ bool deleteOwnerName(QString owner);
  /*public*/ void replaceOwner(QString oldName, QString newName);
  /*public*/ void setBuiltStartYear(QString year);
  /*public*/ void setBuiltEndYear(QString year);
  /*public*/ QString getManifestLogoURL();
  /*public*/ void setManifestLogoURL(QString pathName);
  /*public*/ bool isShowArrivalAndDepartureTimesEnabled();
  /*public*/ void setShowArrivalAndDepartureTimes(bool enable);
  /*public*/ bool isSendCarsToTerminalEnabled();
  /*public*/ void setSendCarsToTerminalEnabled(bool enable);
  /*public*/ bool isAllowLocalMovesEnabled();
  /*public*/ void setAllowLocalMovesEnabled(bool enable);
  /*public*/ bool isAllowThroughCarsEnabled() ;
  /*public*/ void setAllowThroughCarsEnabled(bool enable);
  /*public*/ bool isBuildTrainNormalEnabled();
  /*public*/ void setBuildTrainNormalEnabled(bool enable) ;
  /*public*/ bool isAllowReturnToStagingEnabled();
  /*public*/ void setAllowReturnToStagingEnabled(bool enable);
  /*public*/ bool isServiceAllCarsWithFinalDestinationsEnabled();
  /*public*/ void setServiceAllCarsWithFinalDestinationsEnabled(bool enable);
  /*public*/ bool isBuildConsistEnabled();
  /*public*/ void setBuildConsistEnabled(bool enable);
  /*public*/ bool isSendCarsWithCustomLoadsToStagingEnabled();
  /*public*/ void setSendCarsWithCustomLoadsToStagingEnabled(bool enable);
  /*public*/ void setRequirements(int requires);
  /*public*/ int getRequirements();
  /*public*/ void setSwitchListStatus(QString status);
  /*public*/ QString getSwitchListStatus();
  /*public*/ bool reset();
  /*public*/ void setDepartureTrack(Track* track);
  /*public*/ void setTerminationTrack(Track* track);
  /*public*/ QString getTerminationDate();
  /*public*/ int getNumberCarsRequested();
  /*public*/ void setTerminationDate(QString date);
  /*public*/ void setDescription(QString description);
  /*public*/ void setBuildEnabled(bool build);
  /*public*/ void setNumberCarsRequested(int number);
  /*public*/ TrainIcon* getTrainIcon();
  /*public*/ QString getTrainDepartsDirection();
  /*public*/ QString getCabooseRoadAndNumber();
  /*public*/ void printBuildReport();
  /*public*/ bool printBuildReport(bool isPreview);
  /*public*/ int getNumberCarsWorked();
  /*public*/ int getTrainHorsePower(RouteLocation* routeLocation);
  /*public*/ QString getStatus(QLocale locale);
  /*public*/ QString getStatus(QLocale locale, int code);
  /*public*/ bool setTrainIconCoordinates();
  /*public*/ File* createCSVManifestFile();
  /*public*/ bool runFile();

 signals:
  void error(QString, QString);
 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);
  void on_error(QString title, QString msg);

 private:
  Logger* log;
  void common();
  /*private*/ void addPropertyChangeListerners();
 QDomDocument doc;
 QStringList _skipLocationsList; // = new QStringList();
 /*private*/ bool animation;// = true; // when true use animation for icon moves
 TrainIconAnimation* _ta;
 /*private*/ void setTrainIconColor();
 QStringList _typeList;// = new QStringList();
 /*private*/ void replaceRoad(QString oldRoad, QString newRoad);
 /*private*/ void replaceModel(QString oldModel, QString newModel);
 QStringList _roadList;// = new QStringList();
 /*private*/ bool debugFlag;// = false;
 QStringList _ownerList;// = new QStringList();
 /*private*/ void setPrinted(bool printed);
 /*private*/ int calculateWorkTimeAtLocation(RouteLocation* routeLocation);
 /*private*/ QString parseTime(int minutes);
 QStringList _loadList;// = new ArrayList<String>();
 /*private*/ void updateStatus(RouteLocation* old, RouteLocation* next);
 /*private*/ /*synchronized*/ void runScripts(QStringList scripts);

 protected:

  /*protected*/ QString _id ; //NONE;
  /*protected*/ QString _name ; //NONE;
  /*protected*/ QString _description ; //NONE;
  /*protected*/RouteLocation* _current ; //null;// where the train is located in its route
  /*protected*/ QString _buildFailedMessage ; //NONE; // the build failed message for this train
  /*protected*/ bool _built ; //false; // when true, a train manifest has been built
  /*protected*/ bool _modified ; //false; // when true, user has modified train after being built
  /*protected*/ bool _build ; //true; // when true, build this train
  /*protected*/ bool _buildFailed ; //false; // when true, build for this train failed
  /*protected*/ bool _printed ; //false; // when true, manifest has been printed
  /*protected*/ bool _sendToTerminal ; //false; // when true, cars picked up by train only go to terminal
  /*protected*/ bool _allowLocalMoves ; //true; // when true, cars with custom loads can be moved locally
  /*protected*/ bool _allowThroughCars ; //true; // when true, cars from the origin can be sent to the terminal
  /*protected*/ bool _buildNormal ; //false; // when true build this train in normal mode
  /*protected*/ bool _allowCarsReturnStaging ; //false; // when true allow cars to return to staging if necessary
  /*protected*/ bool _serviceAllCarsWithFinalDestinations ; //false; // when true, service cars with /*final*/ destinations
  /*protected*/ bool _buildConsist ; //false; // when true, build a consist for this train using single locomotives
  /*protected*/ bool _sendCarsWithCustomLoadsToStaging ; //false; // when true, send cars to staging if spurs full
  /*protected*/ Route* _route ; //null;
  /*protected*/ Track* _departureTrack; // the departure track from staging
  /*protected*/ Track* _terminationTrack; // the termination track into staging
  /*protected*/ QString _roadOption ; //ALL_ROADS;// train road name restrictions
  /*protected*/ int _requires ; //0; // train requirements, caboose, FRED
  /*protected*/ QString _numberEngines ; //"0"; // number of engines this train requires
  /*protected*/ QString _engineRoad ; //NONE; // required road name for engines assigned to this train
  /*protected*/ QString _engineModel ; //NONE; // required model of engines assigned to this train
  /*protected*/ QString _cabooseRoad ; //NONE; // required road name for cabooses assigned to this train
  /*protected*/ Calendar* _departureTime ; //Calendar.getInstance(); // departure time for this train
  /*protected*/ QString _leadEngineId ; //NONE; // lead engine for train icon info
  /*protected*/ QString _builtStartYear ; //NONE; // built start year
  /*protected*/ QString _builtEndYear ; //NONE; // built end year
  /*protected*/ QString _loadOption ; //ALL_LOADS;// train load restrictions
  /*protected*/ QString _ownerOption ; //ALL_OWNERS;// train owner name restrictions
  /*protected*/ QStringList _buildScripts ; //new QStringList(); // list of script pathnames to run before train is
  // built
  /*protected*/ QStringList _afterBuildScripts ; //new QStringList(); // list of script pathnames to run after train
  // is built
  /*protected*/ QStringList _moveScripts ; //new QStringList(); // list of script pathnames to run when train is
  // moved
  /*protected*/ QStringList _terminationScripts ; //new QStringList(); // list of script pathnames to run when train
  // is terminated
  /*protected*/ QString _railroadName ; //NONE; // optional railroad name for this train
  /*protected*/ QString _logoURL ; //NONE; // optional manifest logo for this train
  /*protected*/ bool _showTimes ; //true; // when true, show arrival and departure times for this train
  /*protected*/ Engine* _leadEngine ; //null; // lead engine for icon
  /*protected*/ QString _switchListStatus ; //UNKNOWN; // print switch list status
  /*protected*/ QString _comment ; //NONE;
  /*protected*/ QString _serviceStatus ; //NONE; // status only if train is being built
  /*protected*/ int _statusCode ; //CODE_UNKNOWN;
  /*protected*/ QString _statusTerminatedDate ; //NONE;
  /*protected*/ int _statusCarsRequested ; //0;
  /*protected*/ QString _tableRowColorName ; //NONE; //color of row in Trains table

  // Engine change and helper engines
  /*protected*/ int _leg2Options ; //0; // options
  /*protected*/RouteLocation* _leg2Start ; //null; // route location when 2nd leg begins
  /*protected*/RouteLocation* _end2Leg ; //null; // route location where 2nd leg ends
  /*protected*/ QString _leg2Engines ; //"0"; // number of engines 2nd leg
  /*protected*/ QString _leg2Road ; //NONE; // engine road name 2nd leg
  /*protected*/ QString _leg2Model ; //NONE; // engine model 2nd leg
  /*protected*/ QString _leg2CabooseRoad ; //NONE; // road name for caboose 2nd leg

  /*protected*/ int _leg3Options ; //0; // options
  /*protected*/RouteLocation* _leg3Start ; //null; // route location when 3rd leg begins
  /*protected*/RouteLocation* _leg3End ; //null; // route location where 3rd leg ends
  /*protected*/ QString _leg3Engines ; //"0"; // number of engines 3rd leg
  /*protected*/ QString _leg3Road ; //NONE; // engine road name 3rd leg
  /*protected*/ QString _leg3Model ; //NONE; // engine model 3rd leg
  /*protected*/ QString _leg3CabooseRoad ; //NONE; // road name for caboose 3rd leg
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);
  /*protected*/ void moveTrainIcon(RouteLocation* rl);
  /*protected*/ RouteLocation* _trainIconRl;// = NULL; // saves the icon current route location
  /*protected*/ RouteLocation* getTrainDepartsRouteLocation();
  /*protected*/ TrainIcon* _trainIcon;// = NULL;
  /*protected*/ RouteLocation* getTrainTerminatesRouteLocation() ;
  /*protected*/ void setCurrentLocation(RouteLocation* location);
  /*protected*/ void setRoadNames(QStringList roads);
  /*protected*/ static /*final*/ QString SEVEN;// = Setup::BUILD_REPORT_VERY_DETAILED;
  /*protected*/ int getExpectedTravelTimeInMinutes(RouteLocation* routeLocation);
  /*protected*/ void setBuilt(bool built);
  /*protected*/ QStringList getTrainSkipsLocations();
  /*protected*/ void setTrainSkipsLocations(QStringList locationIds);
  /*protected*/ QStringList getTypeNames();
  /*protected*/ QStringList getCarTypeNames();
  /*protected*/ QStringList getLocoTypeNames();
  /*protected*/ void setTypeNames(QStringList types);
  /*protected*/ void setLoadNames(QStringList loads);
  /*protected*/ void setOwnerNames(QStringList owners);
  /*protected*/ void setBuildFailedMessage(QString message) ;
  /*protected*/ QString getBuildFailedMessage();
  /*protected*/ void setBuildFailed(bool status);
  /*protected*/ void setServiceStatus(QString status);

  friend class TrainManager;
  friend class TrainEditFrame;
  friend class TrainBuilder;
  friend class TrainEditBuildOptionsFrame;
 };
} // end operations
#endif // TRAIN_H
