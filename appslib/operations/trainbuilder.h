#ifndef TRAINBUILDER_H
#define TRAINBUILDER_H

#include "traincommon.h"
#include <QHash>

namespace Operations
{
 class ScheduleItem;
 class EngineManager;
 class Track;
 class TrainBuilder : public TrainCommon
 {
  Q_OBJECT
 public:
  TrainBuilder();
  /*public*/ void build(Train* train);
 signals:
  void buildException(QString, QString);
  void error(QString title, QString msg);

 private:
  /*private*/ static /*final*/ int DISPLAY_CAR_LIMIT_50;//= 50;
  /*private*/ static /*final*/ int DISPLAY_CAR_LIMIT_100;//= 100;
  // build variables shared between local routines
  Train* _train; // the train being built
  int _numberCars;//= 0; // how many cars are moved by this train
  int _reqNumEngines;//= 0; // the number of engines required for this train
  QList<Engine*> _engineList; // list of engines available for this train
  Engine* _leadEngine; // last lead engine found from getEngine
  int _carIndex; // index for carList
  QList<Car*>* _carList; // list of cars available for this train
  QList<RouteLocation*>* _routeList; // list of locations from departure to termination served by this train
  QHash<QString, int> _numOfBlocks; // Number of blocks of cars departing staging.
  int _completedMoves; // the number of pick up car moves for a location
  int _reqNumOfMoves; // the requested number of car moves for a location
  Location* _departLocation; // train departs this location
  Track* _departStageTrack; // departure staging track (null if not staging)
  Location* _terminateLocation; // train terminate at this location
  Track* _terminateStageTrack; // terminate staging track (null if not staging)
  bool _success; // true when enough cars have been picked up from a location
  PrintWriter* _buildReport; // build report for this train
  QList<Car*> _notRoutable;//= new ArrayList<Car>();

  // managers
  CarManager* carManager;//= CarManager.instance();
  LocationManager* locationManager;//= LocationManager.instance();
  EngineManager* engineManager;//= EngineManager.instance()
  /*private*/ void build(); //throws BuildFailedException
  Logger* log;
  /*private*/ int getAutoEngines();
  /*private*/ void removeCarsFromStaging();
  /*private*/ bool checkTerminateStagingTrack(Track* terminateStageTrack);
  /*private*/ void showTrainRequirements();
  /*private*/ Track* PromptToStagingDialog();
  /*private*/ bool checkDepartureStagingTrack(Track* departStageTrack);
  /*private*/ Track* PromptFromStagingDialog();
  /*private*/ bool getEngines(int numberOfEngines, QString model, QString road, RouteLocation* rl, RouteLocation* rld);
  /*private*/ bool checkTerminateStagingTrackRestrications(Track* terminateStageTrack);
  /*private*/ bool checkPickUpTrainDirection(RollingStock* rs, RouteLocation* rl);
  /*private*/ bool checkPickUpTrainDirection(RouteLocation* rl);
  /*private*/ bool setLocoDestination(Engine* engine, RouteLocation* rl, RouteLocation* rld, Track* terminateTrack);
  /*private*/ void addEngineToTrain(Engine* engine, RouteLocation* rl, RouteLocation* rld, Track* track);
  /*private*/ /*final*/ bool ignoreTrainDirectionIfLastLoc;// = false;
  /*private*/ bool checkDropTrainDirection(RollingStock* rs, RouteLocation* rld, Track* track);
  /*private*/ void addRsToTrain(RollingStock* rs, RouteLocation* rl, RouteLocation* rld, Track* track, int length,
          int weightTons);
  /*private*/ bool checkDropTrainDirection(RouteLocation* rld);
  bool multipass;// = false;
  /*private*/ bool checkTrainLength(Car* car, RouteLocation* rl, RouteLocation* rld);
  /*private*/ bool checkTrainCanDrop(Car* car, Track* track);
  /*private*/ bool findFinalDestinationForCarLoad(Car* car); //throws BuildFailedException
  /*private*/ void removeCars();// //throws BuildFailedException
  /*private*/ void checkKernel(Car* car);
  /*private*/ void removeCaboosesAndCarsWithFredAndSaveFinalDestination();// //throws BuildFailedException
  /*private*/ void getCaboose(QString roadCaboose, Engine* leadEngine, RouteLocation* rl, RouteLocation* rld,
          bool requiresCaboose);// //throws BuildFailedException
  /*private*/ void getCarWithFred(QString road, RouteLocation* rl, RouteLocation* rld);// //throws BuildFailedException
  /*private*/ bool checkCarForDestinationAndTrack(Car* car, RouteLocation* rl, RouteLocation* rld);
  /*private*/ bool checkCarForDestinationAndTrack(Car* car, RouteLocation* rl, int routeIndex);
  /*private*/ void checkCarOrder(Car* car);
  /*private*/ void addCarToTrain(Car* car, RouteLocation* rl, RouteLocation* rld, Track* track);
  /*private*/ bool checkForLaterPickUp(RouteLocation* rl, RouteLocation* rld, Car* car);
  /*private*/ bool findDestinationAndTrack(Car* car, RouteLocation* rl, RouteLocation* rld); //throws BuildFailedException
  /*private*/ bool findDestinationAndTrack(Car* car, RouteLocation* rl, int routeIndex, int routeEnd);
  /*private*/ ScheduleItem* getScheduleItem(Car* car, Track* track); //throws BuildFailedException
  /*private*/ ScheduleItem* checkScheduleItem(ScheduleItem* si, Car* car, Track* track);
  /*private*/ Car* getCarOrder(Car* car);
  /*private*/ bool generateLoadCarDepartingAndTerminatingIntoStaging(Car* car, Track* stageTrack);
  /*private*/ bool redirectCarsFromAlternateTrack();
  ///*private*/ void reportCarsNotMoved(RouteLocation* rl, int percent);
  /*private*/ void blockCarsFromStaging();// //throws BuildFailedException
  /*private*/ void blockByLocationMoves(); //throws BuildFailedException
  /*private*/ void checkEngineHP();// //throws BuildFailedException
  /*private*/ void findNewEngine(int hpNeeded, Engine* leadEngine);// //throws BuildFailedException
  /*private*/ void checkNumnberOfEnginesNeeded();// throws BuildFailedException
  /*private*/ void addLocos(int hpAvailable, int extraHpNeeded, RouteLocation* rlNeedHp, RouteLocation* rl,
          RouteLocation* rld); //throws BuildFailedException
  /*private*/ void placeCars(int percent, bool firstPass);// //throws BuildFailedException
  /*private*/ void findDestinationsForCarsFromLocation(RouteLocation* rl, int routeIndex, bool isSecondPass);
  /*private*/ void checkDepartureForStaging(int percent);// //throws BuildFailedException
  /*private*/ RouteLocation* getLocationWithMaximumMoves(QList<RouteLocation*> routeList, QString blockId);
  /*private*/ QString getLargestBlock();
  /*private*/ void reportCarsNotMoved(RouteLocation* rl, int percent);
  /*private*/ bool generateCarLoadFromStaging(Car* car); //throws BuildFailedException
  /*private*/ bool generateCarLoadStagingToStaging(Car* car); //throws BuildFailedException

 private slots:
  /*private*/ void buildFailed(/*BuildFailedException e*/QString msg, QString type = "Normal");

 protected:
  /*protected*/ static /*final*/ QString ONE;//= Setup.BUILD_REPORT_MINIMAL;
  /*protected*/ static /*final*/ QString THREE;//= Setup.BUILD_REPORT_NORMAL;
  /*protected*/ static /*final*/ QString FIVE;//= Setup.BUILD_REPORT_DETAILED;
  /*protected*/ static /*final*/ QString SEVEN;//= Setup.BUILD_REPORT_VERY_DETAILED;


 };
}
#endif // TRAINBUILDER_H
