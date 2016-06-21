#ifndef ROUTER_H
#define ROUTER_H

#include "traincommon.h"
namespace Operations
{
 class Track;
 class Train;
 class Router : public TrainCommon
 {
 public:
  Router(QObject* parent = 0);
  /*public*/ static /*synchronized*/ Router* instance();
  /*public*/ QString getStatus();
  /*public*/ bool setDestination(Car* car, Train* train, PrintWriter* buildReport);

 private:
  /*private*/ QList<Track*> _nextLocationTracks;// = QList<Track>();
  /*private*/ QList<Track*> _lastLocationTracks;// = QList<Track>();
  /*private*/ QList<Track*> _otherLocationTracks;// = QList<Track>();

  /*private*/ QList<Train*> _nextLocationTrains;// = QList<Train>();
  /*private*/ QList<Train*> _lastLocationTrains;// = QList<Train>();
  /*private*/ QString _status;// = "";
  /*private*/ Train* _train;// = NULL;
  PrintWriter* _buildReport;// = NULL; // build report
  /*private*/ static bool debugFlag;// = false; // developer debug flag
  /*private*/ static /*final*/ QString SEVEN;// = Setup.BUILD_REPORT_VERY_DETAILED;
  /*private*/ bool _addtoReport;// = false;
  /*private*/ bool _addtoReportVeryDetailed;// = false;
  /*private*/ static Router* _instance;// = NULL;
  Logger* log;
  /*private*/ static /*final*/ QString NO;// = "no"; // NOI18N
  /*private*/ static /*final*/ QString YES;// = "yes"; // NOI18N
  /*private*/ static /*final*/ QString NOT_NOW;// = "not now"; // NOI18N
  /*private*/ static /*final*/ QString NO_SPECIFIC_TRAIN;// = "no specific train"; // NOI18N
  /*private*/ QString canSpecificTrainService(Car* car);
  /*private*/ bool checkForSingleTrain(Car* car, Car* clone);
  /*private*/ bool setCarDestinationInterchange(Car* car);
  /*private*/ bool routeUsingOneTrain(Train* testTrain, Car* car, Car* clone);
  /*private*/ bool setCarDestinationYard(Car* car);
  /*private*/ bool setCarDestinationMultipleTrains(Car* car, bool useStaging);
  /*private*/ bool setCarDestinationStaging(Car* car);
  /*private*/ Car* clone(Car* car);
  /*private*/ bool setCarDestinationTwoTrains(Car* car, QString trackType);
  /*private*/ void loadTracks(Car* car, Car* testCar, QList<Track*> tracks);
  /*private*/ bool finshSettingRouteFor(Car* car, Track* track);

 protected:
  /*protected*/ static /*final*/ QString STATUS_NOT_THIS_TRAIN;// = Bundle.getMessage("RouterTrain");
  /*protected*/ static /*final*/ QString STATUS_NOT_ABLE;// = Bundle.getMessage("RouterNotAble");
  /*protected*/ static /*final*/ QString STATUS_CAR_AT_DESINATION;// = Bundle.getMessage("RouterCarAtDestination");
  // /*protected*/ static final String STATUS_NO_TRAINS;// = Bundle.getMessage("RouterNoTrains");
  /*protected*/ static /*final*/ QString STATUS_ROUTER_DISABLED;// = Bundle.getMessage("RouterDisabled");

 };
}
#endif // ROUTER_H
