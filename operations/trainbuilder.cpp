#include "trainbuilder.h"
#include "carmanager.h"
#include "enginemanager.h"
#include "locationmanager.h"
#include "train.h"
#include "file.h"
#include "trainmanagerxml.h"
#include "printwriter.h"
#include "version.h"
#include "setup.h"
#include "track.h"
#include "routelocation.h"
#include "engine.h"
#include "route.h"
#include "trainmanager.h"
#include "location.h"
#include "control.h"
#include "writer.h"
#include "car.h"
#include <QMessageBox>
#include "kernel.h"
#include "trainmanifest.h"
#include "carroads.h"
#include "carloads.h"
#include "carload.h"
#include "router.h"
#include "scheduleitem.h"
#include "trainschedule.h"
#include "trainschedulemanager.h"
#include "schedule.h"
#include "track.h"
#include "jsonmanifest.h"
#include "traincsvmanifest.h"
#include "buildfailedexception.h"
#include "joptionpane.h"
#include "instancemanager.h"

namespace Operations
{
/**
 * Builds a train and creates the train's manifest.
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2009, 2010, 2011, 2012, 2013,
 *         2014, 2015
 * @version $Revision: 29871 $
 */
///*public*/ class TrainBuilder extends TrainCommon {

 // report levels
 /*protected*/ /*static*/ /*final*/ QString TrainBuilder::ONE = "1"; //Setup::BUILD_REPORT_MINIMAL;
 /*protected*/ /*static*/ /*final*/ QString TrainBuilder::THREE = "3"; //Setup::BUILD_REPORT_NORMAL;
 /*protected*/ /*static*/ /*final*/ QString TrainBuilder::FIVE = "5";//Setup::BUILD_REPORT_DETAILED;
 /*protected*/ /*static*/ /*final*/ QString TrainBuilder::SEVEN = "7"; //Setup::BUILD_REPORT_VERY_DETAILED;

 /*private*/ /*static*/ /*final*/ int TrainBuilder::DISPLAY_CAR_LIMIT_50 = 50;
 /*private*/ /*static*/ /*final*/ int TrainBuilder::DISPLAY_CAR_LIMIT_100 = 100;

 TrainBuilder::TrainBuilder() : TrainCommon()
 {
  // build variables shared between local routines
  _numberCars = 0; // how many cars are moved by this train
  _reqNumEngines = 0; // the number of engines required for this train
  _notRoutable = QList<Car*>();
  ignoreTrainDirectionIfLastLoc = false;
  multipass = false;

  // managers
  carManager = ((CarManager*)InstanceManager::getDefault("CarManager"));
  locationManager = ((LocationManager*)InstanceManager::getDefault("LocationManager"));
  engineManager = ((EngineManager*)InstanceManager::getDefault("EngineManager"));
  log = new Logger("TrainBuilder");
 }

 /**
  * Build rules:
  * <ul>
  * <li>1. Need at least one location in route to build train
  * <li>2. Select only locos and cars the that train can service
  * <li>3. Optional, train must depart with the required number of moves
  * (cars)
  * <li>4. If required, add caboose or car with FRED to train
  * <li>5. When departing staging find a track matching train requirements
  * <li>6. All cars and locos on one track must leave staging
  * <li>7. Service locations based on train direction, location car types and
  * roads
  * <li>8. Ignore track direction when train is a local (serves one location)
  *
  * @param train the train that is to be built
  *
  */
 /*public*/ void TrainBuilder::build(Train* train)
 {
  this->_train = train;
  connect(this, SIGNAL(buildException(QString, QString)), this, SLOT(buildFailed(QString, QString)));
  try
  {
   build();
  }
  catch (BuildFailedException e)
  {
   buildFailed(e);
  }
 }

 /*private*/ void TrainBuilder::build() //throws BuildFailedException
 {
  log->debug(tr("Building train (%1)").arg(_train->getName()));

   _train->setStatus(Train::CODE_BUILDING);
   _train->setBuilt(false);
   _train->setLeadEngine(NULL);

   // create build report file
   File* file = ((TrainManagerXml*)InstanceManager::getDefault("TrainManagerXml"))->createTrainBuildReportFile(_train->getName());
   try
   {
    QFile* qFile = new QFile(file->getPath());
    if(!qFile->open(QIODevice::WriteOnly))
    {
     log->error("Can not open build report file: '" + file->getName()+ "'");
     return;
    }
    log->info(tr("build report for train %1 will write to file %2").arg(_train->getName()).arg(file->getPath()));
    //_buildReport = new PrintWriter(new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file),
    //               "UTF-8")), true); // NOI18N
    _buildReport = new PrintWriter(new QTextStream(qFile),true);
   } catch (IOException e) {
      log->error("Can not open build report file: " + file->getName());
       return;
   }
   QDateTime startTime = QDateTime::currentDateTime();
   addLine(_buildReport, ONE, tr("Build Report for train (%1) built on %2").arg(
           _train->getName()).arg(startTime.toString()));
   addLine(_buildReport, ONE, QString("JMRI version %1").arg(Version::name()));
   // show the various build detail levels
   addLine(_buildReport, THREE, tr("Build report detail level: Normal"));
   addLine(_buildReport, FIVE, tr("Build report detail level: Detailed"));
   addLine(_buildReport, SEVEN, tr("Build report detail level: Very Detailed"));

   if (Setup::getRouterBuildReportLevel()==(Setup::BUILD_REPORT_DETAILED))
   {
    addLine(_buildReport, SEVEN, tr("Router build report level: Detailed"));
   }
   else if (Setup::getRouterBuildReportLevel()==(Setup::BUILD_REPORT_VERY_DETAILED))
   {
    addLine(_buildReport, SEVEN, tr("Router build report level: Very Detailed"));
   }

   if (!Setup::getComment().trimmed().isEmpty())
   {
    addLine(_buildReport, ONE, BLANK_LINE);
    addLine(_buildReport, ONE, Setup::getComment());
   }

   addLine(_buildReport, ONE, BLANK_LINE);

   if (_train->getRoute() == NULL)
   {
    throw BuildFailedException(tr("ERROR Can not build train (%1), needs a route").arg(
                    _train->getName()));
   }
   // get the train's route
   _routeList = _train->getRoute()->getLocationsBySequenceList();
   if (_routeList->size() < 1)
   {
    throw BuildFailedException(tr("ERROR Route needs at least one location to build train (%1)").arg(_train->getName()));
   }
   // train departs
   _departLocation = locationManager->getLocationByName(_train->getTrainDepartsName());
   if (_departLocation == NULL) {
    throw  BuildFailedException(tr("ERROR Route departure location missing for train (%1)").arg(_train->getName()));
   }
   // train terminates
   _terminateLocation = locationManager->getLocationByName(_train->getTrainTerminatesName());
   if (_terminateLocation == NULL) {
    throw  BuildFailedException(tr("ERROR Route terminate location missing for train (%1)").arg(_train->getName()));
   }

   // show train build options in detailed mode
   addLine(_buildReport, FIVE, tr("Train Build Options") + ":");
   if (Setup::isBuildAggressive())
   {
    addLine(_buildReport, FIVE, tr("Build option is set to aggressive"));
    addLine(_buildReport, FIVE, tr("Perform %1 passes").arg(Setup::getNumberPasses()));
   } else
   {
    addLine(_buildReport, FIVE, tr("Build option is set to normal"));
   }
   // warn if car routing is disabled
   if (!Setup::isCarRoutingEnabled())
   {
    addLine(_buildReport, FIVE, tr("WARNING car routing is disabled"));
   }
   else
   {
    if (Setup::isCarRoutingViaYardsEnabled())
    {
        addLine(_buildReport, FIVE, tr("Car routing via yards is enabled"));
    }
    if (Setup::isOnlyActiveTrainsEnabled())
    {
     addLine(_buildReport, FIVE, tr("WARNING only selected trains used for routing:"));
     // list the selected trains
     foreach (Train* train, ((TrainManager*)InstanceManager::getDefault("TrainManager"))->getTrainsByNameList())
     {
      if (train->isBuildEnabled())
      {
          addLine(_buildReport, SEVEN, tr("Train (%1) %2").arg(train->getName()).arg(train->getDescription()));
      }
     }
     if (!_train->isBuildEnabled()) {
         addLine(_buildReport, FIVE, tr("WARNING train (%1) is not selected for routing").arg(_train->getName()));
     }
    }
    if (Setup::isCheckCarDestinationEnabled()) {
        addLine(_buildReport, FIVE, tr("Track destination restrictions when routing is enabled"));
    }
   }
   if (_train->isBuildTrainNormalEnabled())
   {
       addLine(_buildReport, FIVE, tr("Use normal mode when building this train"));
   }
   if (_train->isSendCarsToTerminalEnabled())
   {
       addLine(_buildReport, FIVE, tr("Send all car pick ups to terminal (%1)").arg(_terminateLocation->getName()));
   }
   if ((_train->isAllowReturnToStagingEnabled() || Setup::isAllowReturnToStagingEnabled())
           && _departLocation->isStaging() && _departLocation == _terminateLocation)
   {
       addLine(_buildReport, FIVE, tr("Allow cars to return to staging"));
   }
   if (_train->isAllowLocalMovesEnabled())
   {
       addLine(_buildReport, FIVE, tr("Allow local moves if car has a custom load or FD"));
   }
   if (_train->isAllowThroughCarsEnabled())
   {
       addLine(_buildReport, FIVE, tr("Allow cars to travel from origin to terminal"));
   }
   if (_train->isServiceAllCarsWithFinalDestinationsEnabled()) {
       addLine(_buildReport, FIVE, tr("Service all cars with a final destination (FD)"));
   }
   if (_train->isSendCarsWithCustomLoadsToStagingEnabled()) {
       addLine(_buildReport, FIVE, tr("Send cars with custom loads to staging"));
   }
   if (_train->isBuildConsistEnabled()) {
       addLine(_buildReport, FIVE, tr("Build loco consist from single locos"));
   }
   addLine(_buildReport, ONE, BLANK_LINE); // add line
   // TODO: DAB control minimal build by each train
   if (_train->getTrainDepartsRouteLocation()->getMaxCarMoves() > _departLocation->getNumberRS()
           && Control::fullTrainOnly) {
//            emit buildException(tr("buildErrorCars").arg(
//                    Integer.toString(_departLocation->getNumberRS()), _train->getTrainDepartsName(), _train->getName()));
//    emit buildException(tr("Not enough cars (%1) at departure (%2) to build train (%3)").arg(
//        _departLocation->getNumberRS()).arg(_train->getTrainDepartsName()).arg(_train->getName()), "Normal");
//    return;
    throw BuildFailedException(tr("Not enough cars (%1) at departure (%2) to build train (%3)").arg(
        _departLocation->getNumberRS()).arg(_train->getTrainDepartsName()).arg(_train->getName()));

   }
   addLine(_buildReport, THREE, tr("Train (%1) route (%2):").arg(
           _train->getName()).arg(_train->getRoute()->getName()));
   // get the number of requested car moves for this train
   int requested = 0;
   foreach (RouteLocation* rl, *_routeList)
   {
    // check to see if there's a location for each stop in the route
    Location* location = locationManager->getLocationByName(rl->getName());
    if (location == NULL || rl->getLocation() == NULL)
    {
//                emit buildException(tr("buildErrorLocMissing"),
//                        _train->getRoute()->getName()));
//     emit buildException(tr("ERROR location missing in route (%1)").arg(_train->getRoute()->getName()), "Normal");
//     return;
     throw BuildFailedException(tr("ERROR location missing in route (%1)").arg(_train->getRoute()->getName()));

    }
    // train doesn't drop or pick up cars from staging locations found in middle of a route
    if (location->isStaging() && rl != _train->getTrainDepartsRouteLocation()
            && rl != _train->getTrainTerminatesRouteLocation())
    {
     addLine(_buildReport, ONE, tr("Location (%1) has only staging tracks").arg(rl
             ->getName()));
     rl->setCarMoves(rl->getMaxCarMoves()); // don't allow car moves for this location
     // if a location is skipped, no car drops or pick ups
    }
    else if (_train->skipsLocation(rl->getId()))
    {
        addLine(_buildReport, THREE, tr("Location (%1) is skipped by train (%2), maximum train length %3 %4").arg(rl->getName()).arg(_train->getName()).arg(rl->getMaxTrainLength()
                        ).arg(Setup::getLengthUnit().toLower()));
        rl->setCarMoves(rl->getMaxCarMoves()); // don't allow car moves for this location
    } else if (!rl->isDropAllowed() && !rl->isPickUpAllowed())
    {
        addLine(_buildReport, THREE, tr("Location (%1) no set outs or pick ups, maximum train length %2 %3").arg(
                rl->getName()).arg(rl->getMaxTrainLength()).arg(Setup::getLengthUnit().toLower()));
        rl->setCarMoves(rl->getMaxCarMoves()); // don't allow car moves for this location
    }
    else
    {
     // we're going to use this location, so initialize the location
     rl->setCarMoves(0); // clear the number of moves
     requested += rl->getMaxCarMoves(); // add up the total number of car moves requested
     // show the type of moves allowed at this location
     if (location->isStaging() && rl->isPickUpAllowed()
             && rl == _train->getTrainDepartsRouteLocation())
     {
         addLine(_buildReport, THREE, tr("Staging (%1) request %2 pick ups, maximum train length %3 %4").arg(
                 rl->getName()).arg(rl->getMaxCarMoves()).arg(rl->getMaxTrainLength()).arg(
                         Setup::getLengthUnit().toLower()));
     }
     else if (location->isStaging() && rl->isDropAllowed()
             && rl == _train->getTrainTerminatesRouteLocation())
     {
         addLine(_buildReport, THREE, tr("Staging (%1) requests %2 set outs").arg(
                 rl->getName()).arg(rl->getMaxCarMoves()));
     }
     else if (rl == _train->getTrainTerminatesRouteLocation() && rl->isDropAllowed() && rl->isPickUpAllowed())
     {
         addLine(_buildReport, THREE, tr("Location (%1) requests %2 moves").arg(
                 rl->getName()).arg(rl->getMaxCarMoves()));
     }
     else if (rl->isDropAllowed() && rl->isPickUpAllowed())
     {
         addLine(_buildReport, THREE, tr("Location (%1) requests %2 moves, maximum train length %3 %4").arg(
                 rl->getName()).arg(rl->getMaxCarMoves()).arg(rl->getMaxTrainLength()).arg(
                         Setup::getLengthUnit().toLower()));
     }
     if (!rl->isDropAllowed())
     {
         addLine(_buildReport, THREE, tr("Location (%1) requests %2 pick ups, maximum train length %3 %4").arg(
                 rl->getName()).arg(rl->getMaxCarMoves()).arg(rl->getMaxTrainLength()).arg(
                         Setup::getLengthUnit().toLower()));
     }
     else if (rl == _train->getTrainTerminatesRouteLocation())
     {
         addLine(_buildReport, THREE, tr("Location (%1) requests %2 set outs").arg(
                 rl->getName()).arg(rl->getMaxCarMoves()));
     }
     else
     {
         addLine(_buildReport, THREE, tr("Location (%1) requests %2 set outs, maximum train length %3 %4").arg(
                 rl->getName()).arg(rl->getMaxCarMoves()).arg(rl->getMaxTrainLength()).arg(
                         Setup::getLengthUnit().toLower()));
     }
    }
    rl->setTrainWeight(0); // clear the total train weight
    rl->setTrainLength(0); // and length
   }

   // check for random controls
   foreach (RouteLocation* rl, *_routeList)
   {
    if (rl->getRandomControl()==(RouteLocation::DISABLED))
    {
        continue;
    }
    if (rl->getCarMoves() == 0 && rl->getMaxCarMoves() > 0) {
       log->debug(tr("Location (%1) has random control value %2 and maximum moves %3").arg(rl->getName()).arg(rl
                ->getRandomControl()).arg(rl->getMaxCarMoves()));
        //try {
       bool ok;
            int value = rl->getRandomControl().toInt(&ok);
            // now adjust the number of available moves for this location
            double random = qrand();
           log->debug(tr("random %1").arg(random));
            int moves = (int) (random * ((rl->getMaxCarMoves() * value / 100) + 1));
           log->debug(tr("Reducing number of moves for location (%1) by %2").arg(rl->getName()).arg(moves));
            rl->setCarMoves(moves);
            requested = requested - moves;
            addLine(_buildReport, FIVE, tr("Route location (%1) id (%2) has random control of %3% reducing number of moves from %4 to %5").arg(rl->getName()).arg(rl->getId()).arg(rl->getRandomControl()).arg(rl->getMaxCarMoves()).arg( rl->getMaxCarMoves() - moves));
        if(!ok)
        {
//               emit buildException(tr("buildErrorRandomControl"),
//                       _train->getRoute()->getName(), rl->getName(), rl->getRandomControl()));
//         emit buildException(tr("Route (%1) location (%2) random control value (%3) is not an integer").arg(_train->getRoute()->getName()).arg(rl->getName()).arg(rl->getRandomControl()), "Normal");
//         return;
         throw BuildFailedException(tr("Route (%1) location (%2) random control value (%3) is not an integer").arg(_train->getRoute()->getName()).arg(rl->getName()).arg(rl->getRandomControl()));

        }
    }
   }

   int numMoves = requested; // number of car moves
   if (!_train->isLocalSwitcher()) {
       requested = requested / 2; // only need half as many cars to meet requests
   }
   addLine(_buildReport, ONE, tr("Route (%1) requests %2 cars and %3 moves").arg(
           _train->getRoute()->getName()).arg(requested).arg(numMoves));
   _train->setNumberCarsRequested(requested); // save number of car requested

   // is this train a switcher?
   if (_train->isLocalSwitcher()) {
       addLine(_buildReport, THREE, BLANK_LINE); // add line when in detailed report mode
       addLine(_buildReport, THREE, tr("Switcher (%1) services location (%2)").arg(
               _train->getName()).arg(TrainCommon::splitString(_train->getTrainDepartsName())));
   }

   // get engine requirements for this train
   if (_train->getNumberEngines()==(Train::AUTO)) {
       _reqNumEngines = getAutoEngines();
   } else if (_train->getNumberEngines()==(Train::AUTO_HPT)) {
       _reqNumEngines = 1; // get one loco for now, check HP requirements after train is built
   } else {
       _reqNumEngines = _train->getNumberEngines().toInt();
   }

   showTrainRequirements();

   // show road names that this train will service
   if (_train->getRoadOption()!=(Train::ALL_ROADS)) {
       addLine(_buildReport, FIVE, tr("Train (%1) %2 roads: %3").arg(
               _train->getName()).arg(_train->getRoadOption()).arg(formatStringToCommaSeparated(_train->getRoadNames())));
   }
   // show owner names that this train will service
   if (_train->getOwnerOption()!=(Train::ALL_OWNERS)) {
       addLine(_buildReport, FIVE, tr("Train (%1) %2 owners: %3").arg(
               _train->getName()).arg(_train->getOwnerOption()).arg(formatStringToCommaSeparated(_train->getOwnerNames())));
   }
   // show built date serviced
   if (_train->getBuiltStartYear()!=(Train::NONE)) {
       addLine(_buildReport, FIVE, tr("Train (%1) will service rolling stock built after %2").arg(
               _train->getName()).arg(_train->getBuiltStartYear()));
   }
   if (_train->getBuiltEndYear()!=(Train::NONE)) {
       addLine(_buildReport, FIVE, tr("Train (%1) will service rolling stock built before {%2").arg(
               _train->getName()).arg(_train->getBuiltEndYear()));
   }

   // show engine types that this train will service
   if (_reqNumEngines > 0) {
       addLine(_buildReport, FIVE, tr("Train (%1) services locomotive types:").arg(_train->getName()));
       addLine(_buildReport, FIVE, formatStringToCommaSeparated(_train->getLocoTypeNames()));
   }

   // allow up to two engine and caboose swaps in the train's route
   RouteLocation* engineTerminatesFirstLeg = _train->getTrainTerminatesRouteLocation();
   RouteLocation* cabooseOrFredTerminatesFirstLeg = _train->getTrainTerminatesRouteLocation();
   RouteLocation* engineTerminatesSecondLeg = _train->getTrainTerminatesRouteLocation();
   RouteLocation* cabooseOrFredTerminatesSecondLeg = _train->getTrainTerminatesRouteLocation();

   // Adjust where the locos will terminate
   if ((_train->getSecondLegOptions() & Train::CHANGE_ENGINES) == Train::CHANGE_ENGINES
           && _train->getSecondLegStartLocation() != NULL) {
       engineTerminatesFirstLeg = _train->getSecondLegStartLocation();
   }
   if ((_train->getThirdLegOptions() & Train::CHANGE_ENGINES) == Train::CHANGE_ENGINES
           && _train->getThirdLegStartLocation() != NULL) {
       engineTerminatesSecondLeg = _train->getThirdLegStartLocation();
       // No engine or caboose change at first leg?
       if ((_train->getSecondLegOptions() & Train::CHANGE_ENGINES) != Train::CHANGE_ENGINES) {
           engineTerminatesFirstLeg = _train->getThirdLegStartLocation();
       }
   }

   // make any caboose changes
   if ((_train->getSecondLegOptions() & Train::REMOVE_CABOOSE) == Train::REMOVE_CABOOSE
           || (_train->getSecondLegOptions() & Train::ADD_CABOOSE) == Train::ADD_CABOOSE) {
       cabooseOrFredTerminatesFirstLeg = _train->getSecondLegStartLocation();
   } else if ((_train->getThirdLegOptions() & Train::REMOVE_CABOOSE) == Train::REMOVE_CABOOSE
           || (_train->getThirdLegOptions() & Train::ADD_CABOOSE) == Train::ADD_CABOOSE) {
       cabooseOrFredTerminatesFirstLeg = _train->getThirdLegStartLocation();
   }
   if ((_train->getThirdLegOptions() & Train::REMOVE_CABOOSE) == Train::REMOVE_CABOOSE
           || (_train->getThirdLegOptions() & Train::ADD_CABOOSE) == Train::ADD_CABOOSE) {
       cabooseOrFredTerminatesSecondLeg = _train->getThirdLegStartLocation();
   }

   // does train terminate into staging?
   _terminateStageTrack = NULL;
   QList<Track*> stagingTracksTerminate = _terminateLocation->getTrackByMovesList(Track::STAGING);
   if (stagingTracksTerminate.size() > 0) {
       addLine(_buildReport, THREE, BLANK_LINE); // add line when in normal report mode
       addLine(_buildReport, ONE, tr("Train terminates into staging at (%1), there are %2 tracks").arg(
               _terminateLocation->getName()).arg(stagingTracksTerminate.size()));
       if (stagingTracksTerminate.size() > 1 && Setup::isPromptToStagingEnabled()) {
           _terminateStageTrack = PromptToStagingDialog();
           startTime = QDateTime::currentDateTime(); // reset build time
       } else {
           // is this train returning to the same staging in aggressive mode?
           if (_departLocation == _terminateLocation && Setup::isBuildAggressive()
                   && Setup::isStagingTrackImmediatelyAvail()) {
               addLine(_buildReport, ONE, tr("Train will return to staging (%1) reuse departure track").arg(
                       _terminateLocation->getName()));
           } else {
               foreach (Track* track, stagingTracksTerminate) {
                   _terminateStageTrack = track;
                   if (checkTerminateStagingTrack(_terminateStageTrack)) {
                       addLine(_buildReport, ONE, tr("Staging track (%1) is available at destination (%2)").arg(
                               _terminateStageTrack->getName()).arg(_terminateLocation->getName()));
                       break;
                   }
                   _terminateStageTrack = NULL;
               }
           }
       }
       if (_terminateStageTrack == NULL) {
           // is this train returning to the same staging in aggressive mode?
           if (_departLocation == _terminateLocation && Setup::isBuildAggressive()
                   && Setup::isStagingTrackImmediatelyAvail()) {
              log->debug("Train is returning to same track in staging");
           } else {
               addLine(_buildReport, ONE, tr("Note that the program requires an empty staging track for each train!"));
               throw BuildFailedException(tr("All staging tracks at %1 are occupied, reserved, or can not service the train").arg(
                       _terminateLocation->getName()));
               return;
           }
       }
   }

   // get list of engines for this route
   _engineList = engineManager->getAvailableTrainList(_train);

   // determine if train is departing staging
   _departStageTrack = NULL;
   QList<Track*> stagingTracks = _departLocation->getTrackByMovesList(Track::STAGING);
   if (stagingTracks.size() > 0)
   {
       addLine(_buildReport, THREE, BLANK_LINE); // add line when in normal report mode
       addLine(_buildReport, ONE, tr("Train will depart staging (%1), there are %2 tracks").arg(
               _departLocation->getName()).arg(stagingTracks.size()));
       if (stagingTracks.size() > 1 && Setup::isPromptFromStagingEnabled()) {
           _departStageTrack = PromptFromStagingDialog();
           startTime = QDateTime::currentDateTime(); // restart build timer
           if (_departStageTrack == NULL) {
               showTrainRequirements();
               throw BuildFailedException(tr("Could not find a departure staging track at %1 that meets the train requirements").arg(
                       _departLocation->getName()));
               return;
           }
           // load engines for this train
           if (!getEngines(_reqNumEngines, _train->getEngineModel(), _train->getEngineRoad(), _train
                   ->getTrainDepartsRouteLocation(), engineTerminatesFirstLeg)) {
               throw BuildFailedException(tr("Train requires %1 loco(s), could not pick up at departure (%2) or set out at (%3)").arg(_reqNumEngines).arg(_train->getTrainDepartsName()).arg(engineTerminatesFirstLeg->getName()));
            return;
           }
       } else {
           foreach (Track* track, stagingTracks) {
               addLine(_buildReport, THREE, tr("Staging track (%1) has %2 loco(s) and %3 cars").arg(
                       track->getName()).arg(track->getNumberEngines()).arg(track->getNumberCars()));
               // is the departure track available?
               if (!checkDepartureStagingTrack(track)) {
                   continue;
               }
               _departStageTrack = track;
               // try each departure track for the required engines
               if (getEngines(_reqNumEngines, _train->getEngineModel(), _train->getEngineRoad(), _train
                       ->getTrainDepartsRouteLocation(), engineTerminatesFirstLeg)) {
                   addLine(_buildReport, SEVEN, tr("Done assigning locomotives from staging"));
                   break; // done!
               }
               _departStageTrack = NULL;
           }
       }
       if (_departStageTrack == NULL) {
           showTrainRequirements();
           throw BuildFailedException(tr("Could not find a departure staging track at %1 that meets the train requirements").arg(
                   _departLocation->getName()));
           return;
           // departing staging and returning to same track?
       } else if (_terminateStageTrack == NULL && _departLocation == _terminateLocation
               && Setup::isBuildAggressive() && Setup::isStagingTrackImmediatelyAvail()) {
           _terminateStageTrack = _departStageTrack; // use the same track
       }
   } else {
       // no staging tracks at this location, load engines for this train
       if (_reqNumEngines > 0) {
           addLine(_buildReport, FIVE, BLANK_LINE); // add line when in detailed report mode
       }
       if (!getEngines(_reqNumEngines, _train->getEngineModel(), _train->getEngineRoad(), _train
               ->getTrainDepartsRouteLocation(), engineTerminatesFirstLeg)) {
           throw BuildFailedException(tr("Train requires %1 loco(s), could not pick up at departure (%2) or set out at (%3)").arg(_reqNumEngines).arg(
                           _train->getTrainDepartsName()).arg(engineTerminatesFirstLeg->getName()));
        return;
       }
   }

   // Save termination and departure tracks
   _train->setTerminationTrack(_terminateStageTrack);
   _train->setDepartureTrack(_departStageTrack);

   // First engine change in route?
   Engine* secondLeadEngine = NULL;
   if ((_train->getSecondLegOptions() & Train::CHANGE_ENGINES) == Train::CHANGE_ENGINES) {
       addLine(_buildReport, THREE, tr("Locomotive change at (%1), departs with %2 loco(s), model (%3) road (%4)").arg(_train->getSecondLegStartLocationName(), _train->getSecondLegNumberEngines()).arg(
                       _train->getSecondLegEngineModel()).arg(_train->getSecondLegEngineRoad()));
       if (getEngines(_train->getSecondLegNumberEngines().toInt(), _train->getSecondLegEngineModel(),
               _train->getSecondLegEngineRoad(), _train->getSecondLegStartLocation(), engineTerminatesSecondLeg)) {
           secondLeadEngine = _leadEngine;
       } else {
           throw BuildFailedException(tr("Train requires %1 loco(s), could not pick up at departure (%2) or set out at (%3)").arg(
                   _train->getSecondLegNumberEngines()).arg(
                           _train->getSecondLegStartLocation()->toString()).arg(engineTerminatesSecondLeg->toString()));
        return;
       }
   }
   // Second engine change in route?
   Engine* thirdLeadEngine = NULL;
   if ((_train->getThirdLegOptions() & Train::CHANGE_ENGINES) == Train::CHANGE_ENGINES) {
       addLine(_buildReport, THREE, tr("Locomotive change at (%1), departs with %2 loco(s), model (%3) road (%4)").arg(
               _train->getThirdLegStartLocationName()).arg(_train->getThirdLegNumberEngines()).arg(
                       _train->getThirdLegEngineModel()).arg(_train->getThirdLegEngineRoad()));
       if (getEngines((_train->getThirdLegNumberEngines().toInt()), _train->getThirdLegEngineModel(), _train
               ->getThirdLegEngineRoad(), _train->getThirdLegStartLocation(), _train
               ->getTrainTerminatesRouteLocation())) {
           thirdLeadEngine = _leadEngine;
       } else {
           throw BuildFailedException(tr("Train requires %1 loco(s), could not pick up at departure (%2) or set out at (%3)").arg(
                   _train->getThirdLegNumberEngines()).arg(
                           _train->getThirdLegStartLocation()->toString()).arg(_train->getTrainTerminatesRouteLocation()->toString()));
        return;
       }
   }
   if (_reqNumEngines > 0 && (!_train->isBuildConsistEnabled() || Setup::getHorsePowerPerTon() == 0)) {
       addLine(_buildReport, SEVEN, tr("Done assigning locomotives to train (%1)").arg(
               _train->getName()));
   }

   // show car types and loads that this train will service
   addLine(_buildReport, FIVE, BLANK_LINE); // add line when in detailed report mode
   addLine(_buildReport, FIVE, tr("Train (%1) services car types:").arg(
           _train->getName()));
   addLine(_buildReport, FIVE, formatStringToCommaSeparated(_train->getCarTypeNames()));
   // show load names that this train will service
   if (_train->getLoadOption()!=(Train::ALL_LOADS)) {
       addLine(_buildReport, FIVE, tr("Train (%1) %2 loads: %3").arg(
               _train->getName()).arg(_train->getLoadOption()).arg(formatStringToCommaSeparated(_train->getLoadNames())));
   }

   // get list of cars for this route
   _carList = carManager->getAvailableTrainList(_train);
   // TODO: DAB this needs to be controlled by each train
   if (requested > _carList->size() && Control::fullTrainOnly) {
       throw BuildFailedException(tr("The number of requested cars (%1) for train (%2) is greater than the number available (%3)").arg(
               requested).arg(_train->getName().arg(_carList->size())));
   }

   // remove unwanted cars
   removeCars();

   // Do caboose changes in reverse order in case there isn't enough track space
   // second caboose change?
   if ((_train->getThirdLegOptions() & Train::ADD_CABOOSE) > 0 && _train->getThirdLegStartLocation() != NULL
           && _train->getTrainTerminatesRouteLocation() != NULL) {
       getCaboose(_train->getThirdLegCabooseRoad(), thirdLeadEngine, _train->getThirdLegStartLocation(), _train
               ->getTrainTerminatesRouteLocation(), true);
   }

   // first caboose change?
   if ((_train->getSecondLegOptions() & Train::ADD_CABOOSE) > 0 && _train->getSecondLegStartLocation() != NULL
           && cabooseOrFredTerminatesSecondLeg != NULL) {
       getCaboose(_train->getSecondLegCabooseRoad(), secondLeadEngine, _train->getSecondLegStartLocation(),
               cabooseOrFredTerminatesSecondLeg, true);
   }

   // get caboose or car with FRED if needed for train
   getCaboose(_train->getCabooseRoad(), _train->getLeadEngine(), _train->getTrainDepartsRouteLocation(),
           cabooseOrFredTerminatesFirstLeg, (_train->getRequirements() & Train::CABOOSE) > 0);
   getCarWithFred(_train->getCabooseRoad(), _train->getTrainDepartsRouteLocation(), cabooseOrFredTerminatesFirstLeg);

   // done assigning cabooses and cars with FRED, remove the rest, and save /*final*/ destination
   removeCaboosesAndCarsWithFredAndSaveFinalDestination();

   blockCarsFromStaging(); // block cars from staging

   // now find destinations for cars
   addLine(_buildReport, THREE, BLANK_LINE); // add line when in normal report mode
   addLine(_buildReport, THREE, tr("Requested cars (%1) for train (%2) the number available (%3) building train!").arg(requested).arg(
           _train->getName()).arg(_carList->size()));

   if (Setup::isBuildAggressive() && !_train->isBuildTrainNormalEnabled()) {
       // perform a multiple pass build for this train, default is two passes
       int passes = 0;
       bool firstPass = true;
       while (passes++ < Setup::getNumberPasses()) {
           placeCars(100 * passes / Setup::getNumberPasses(), firstPass);
           firstPass = false;
       }
   } else {
       placeCars(100, false);
   }

   _train->setCurrentLocation(_train->getTrainDepartsRouteLocation());
   if (_numberCars < requested) {
       _train->setStatus(Train::CODE_PARTIAL_BUILT);
       addLine(_buildReport, ONE, Train::PARTIAL_BUILT + " " + _train->getNumberCarsWorked() + "/"
               + _train->getNumberCarsRequested() + " " + tr("cars"));
   } else {
       _train->setStatus(Train::CODE_BUILT);
       addLine(_buildReport, ONE, Train::BUILT + " " + _train->getNumberCarsWorked() + " "
               + tr("cars"));
   }

   // check that engine assigned to the train has the appropriate HP
   checkEngineHP();
   // check to see if additional engines are needed for this train
   checkNumnberOfEnginesNeeded();

   // any cars not able to route?
   if (_notRoutable.size() > 0)
   {
       addLine(_buildReport, ONE, BLANK_LINE);
       addLine(_buildReport, ONE, tr("WARNING! The program wasn't able to route the following cars:"));
       foreach (Car* car, _notRoutable) {
           addLine(_buildReport, ONE, tr("Car (%1) at (%2, %3) final destination (%4, %5)").arg(
                   car->toString()).arg(car->getLocationName()).arg(car->getTrackName()).arg(car->getFinalDestinationName()).arg(
                   car->getFinalDestinationTrackName()));
       }
       addLine(_buildReport, ONE, BLANK_LINE);
   }

   _train->setBuilt(true);
   addLine(_buildReport, FIVE, tr("Build for train (%1) took %2 mSec").arg(
           _train->getName()).arg( QDateTime().currentDateTime().msecsTo( startTime)));
   _buildReport->flush();
   _buildReport->close();

   // now make manifest
   new TrainManifest(_train);

   try {
       (new JsonManifest(_train))->build();
   } catch (IOException ex) {
      log->error(tr("Unable to create JSON manifest: %1").arg(ex.getLocalizedMessage()));
       //emit buildException(ex);
        throw BuildFailedException(ex);
   }
   if (Setup::isGenerateCsvManifestEnabled()) {
       new TrainCsvManifest(_train);
   }

   // now create and place train icon
   _train->moveTrainIcon(_train->getTrainDepartsRouteLocation());
  log->debug(tr("Done building train (%1)").arg(_train->getName()));
 }

 /*private*/ void TrainBuilder::showTrainRequirements()
 {
  addLine(_buildReport, ONE, BLANK_LINE); // add line
  addLine(_buildReport, ONE, tr("Train requirements:"));
  if (_train->getNumberEngines()==("0")) {
      addLine(_buildReport, ONE, tr("Train does not require any locomotives"));
  } else if (_train->getNumberEngines()==("1")) {
      addLine(_buildReport, ONE, tr("Train departs (%1) with a single locomotive, model (%2) road (%3)").arg(
              _train->getTrainDepartsName()).arg(_train->getEngineModel()).arg(_train->getEngineRoad()));
  } else {
      addLine(_buildReport, ONE, tr("Train departs (%1) with %2 consisted locomotives, model (%3) road (%4)").arg(
              _train->getTrainDepartsName()).arg(_train->getNumberEngines()).arg(_train->getEngineModel()).arg(
              _train->getEngineRoad()));
  }
  // show any required loco changes
  if ((_train->getSecondLegOptions() & Train::CHANGE_ENGINES) == Train::CHANGE_ENGINES) {
      addLine(_buildReport, ONE, tr("Locomotive change at (%1), departs with %2 loco(s), model (%3) road (%4)").arg(
              _train->getSecondLegStartLocationName()).arg(_train->getSecondLegNumberEngines().arg(
              _train->getSecondLegEngineModel()).arg(_train->getSecondLegEngineRoad())));
  }
  if ((_train->getSecondLegOptions() & Train::HELPER_ENGINES) == Train::HELPER_ENGINES) {
      addLine(_buildReport, ONE, tr("Train requests %1 helpers from (%2) to (%3), model (%4) road (%5)").arg(
              _train->getSecondLegNumberEngines()).arg(_train->getSecondLegStartLocationName()).arg(
              _train->getSecondLegEndLocationName()).arg(_train->getSecondLegEngineModel().arg(
              _train->getSecondLegEngineRoad())));
  }
  if ((_train->getThirdLegOptions() & Train::CHANGE_ENGINES) == Train::CHANGE_ENGINES) {
      addLine(_buildReport, ONE, tr("Locomotive change at (%1), departs with %2 loco(s), model (%3) road ({%4)").arg(
              _train->getThirdLegStartLocationName()).arg(_train->getThirdLegNumberEngines()).arg(
              _train->getThirdLegEngineModel()).arg(_train->getThirdLegEngineRoad()));
  }
  if ((_train->getThirdLegOptions() & Train::HELPER_ENGINES) == Train::HELPER_ENGINES) {
      addLine(_buildReport, ONE, tr("Train requests %1 helpers from ({%2) to (%3), model (%4) road (%5)").arg(
              _train->getThirdLegNumberEngines()).arg(_train->getThirdLegStartLocationName()).arg(
              _train->getThirdLegEndLocationName()).arg(_train->getThirdLegEngineModel()).arg(
              _train->getThirdLegEngineRoad()));
  }
  // show caboose or FRED requirements
  if ((_train->getRequirements() & Train::CABOOSE) > 0) {
      addLine(_buildReport, ONE, tr("Train must depart (%1) with caboose, road (%2)").arg(_train->getTrainDepartsName()).arg(_train->getCabooseRoad()));
  }
  // show any caboose changes in the train's route
  if ((_train->getSecondLegOptions() & Train::REMOVE_CABOOSE) == Train::REMOVE_CABOOSE
          || (_train->getSecondLegOptions() & Train::ADD_CABOOSE) == Train::ADD_CABOOSE) {
      addLine(_buildReport, ONE, tr("Caboose change at (%1)").arg(_train->getSecondLegStartLocation()->toString()));
  }
  if ((_train->getThirdLegOptions() & Train::REMOVE_CABOOSE) == Train::REMOVE_CABOOSE
          || (_train->getThirdLegOptions() & Train::ADD_CABOOSE) == Train::ADD_CABOOSE) {
      addLine(_buildReport, ONE, tr("Caboose change at (%1)").arg(_train->getThirdLegStartLocation()->toString()));
  }
  if ((_train->getRequirements() & Train::FRED) > 0) {
      addLine(_buildReport, ONE, tr("Train must depart (%1) with a car that has a FRED, road (%2)").arg(
              _train->getTrainDepartsName()).arg(_train->getCabooseRoad()));
  }
  addLine(_buildReport, ONE, BLANK_LINE); // add line
 }

 /**
  * Ask which staging track the train is to depart on.
  *
  * @return The departure track the user selected.
  */
 /*private*/ Track* TrainBuilder::PromptFromStagingDialog()
 {
     QList<Track*> tracksIn = _departLocation->getTrackList();
     QList<Track*> validTracks =QList<Track*>();
     // only show valid tracks
     foreach (Track* track, tracksIn) {
         if (checkDepartureStagingTrack(track)) {
             validTracks.append(track);
         }
     }
#if 0 // TODO:
     if (validTracks.size() > 1)
     {
         // need an object array for dialog window
         Object[] tracks = new Object[validTracks.size()];
         for (int i = 0; i < validTracks.size(); i++) {
             tracks[i] = validTracks->get(i);
         }

         Track* selected = (Track) JOptionPane.showInputDialog(NULL,
                 tr("TrainDepartingStaging").arg(_train->getName(),
                         _departLocation->getName()}), tr("SelectDepartureTrack"),
                 JOptionPane.QUESTION_MESSAGE, NULL, tracks, NULL);
         if (selected != NULL) {
             addLine(_buildReport, FIVE, tr("buildUserSelectedDeparture"),
                     selected->getName(), selected->getLocation()->getName()));
         }
         return selected;
     } else if (validTracks.size() == 1) {
         return validTracks->get(0);
     }
#endif
     return NULL; // no tracks available

 }

 /**
  * Ask which staging track the train is to terminate on.
  *
  * @return The arrival track selected by the user.
  */
 /*private*/ Track* TrainBuilder::PromptToStagingDialog()
 {
    QList<Track*> tracksIn = _terminateLocation->getTrackByNameList(NULL);
     QList<Track*> validTracks = QList<Track*>();
     // only show valid tracks
     foreach (Track* track, tracksIn)
     {
         if (checkTerminateStagingTrack(track))
         {
             validTracks.append(track);
         }
     }
#if 0 // TODO:
     if (validTracks.size() > 1) {
         // need an object array for dialog window
         Object[] tracks = new Object[validTracks.size()];
         for (int i = 0; i < validTracks.size(); i++) {
             tracks[i] = validTracks->get(i);
         }

         Track* selected = (Track) JOptionPane.showInputDialog(NULL, Bundle
                 ->getMessage("TrainTerminatingStaging").arg(_train->getName(),
                 _terminateLocation->getName()}), tr("SelectArrivalTrack"),
                 JOptionPane.QUESTION_MESSAGE, NULL, tracks, NULL);
         if (selected != NULL) {
             addLine(_buildReport, FIVE, tr("buildUserSelectedArrival"),
                     selected->getName(), selected->getLocation()->getName()));
         }
         return selected;
     } else if (validTracks.size() == 1) {
         return validTracks->get(0);
     }
#endif
     return NULL; // no tracks available
 }

 /**
  * Get the engines for this train. If departing from staging
  * (departStageTrack != NULL) engines must come from that track.
  *
  * @return true if correct number of engines found.
  * @throws BuildFailedException
  */
 /*private*/ bool TrainBuilder::getEngines(int numberOfEngines, QString model, QString road, RouteLocation* rl, RouteLocation* rld)
         //throws BuildFailedException
 {
     // load departure track if staging
     Track* departStageTrack = NULL;
     if (rl == _train->getTrainDepartsRouteLocation()) {
         departStageTrack = _departStageTrack; // get departure track from staging, could be NULL
     } // load termination track if staging
     Track* terminateStageTrack = NULL;
     if (rld == _train->getTrainTerminatesRouteLocation()) {
         terminateStageTrack = _terminateStageTrack; // get termination track to staging, could be NULL
     } // departing staging and returning to same track?
     if (_departStageTrack != NULL && terminateStageTrack == NULL && rld == _train->getTrainTerminatesRouteLocation()
             && _departLocation == _terminateLocation && Setup::isBuildAggressive()
             && Setup::isStagingTrackImmediatelyAvail()) {
         terminateStageTrack = _departStageTrack;
     }

     // if not departing staging track and engines aren't required done!
     if (departStageTrack == NULL && numberOfEngines == 0) {
         return true;
     }

     // if departing staging and no engines required and none available, we're done
     if (departStageTrack != NULL && numberOfEngines == 0 && departStageTrack->getNumberEngines() == 0) {
         return true;
     }

     // if leaving staging, use any number of engines if required number is 0
     if (departStageTrack != NULL && numberOfEngines != 0 && departStageTrack->getNumberEngines() != numberOfEngines) {
         addLine(_buildReport, THREE, tr("Staging track (%1) does not have the required number of locomotives").arg(
                 departStageTrack->getName()));
         return false; // done, wrong number of engines on staging track
     }

     // code check
     if (rl == NULL || rld == NULL) {
         throw BuildFailedException(tr("ERROR locomotive location not specified!"));
      return false;
     }

     addLine(_buildReport, FIVE, tr("Search for %1 loco(s), model (%2), road (%3), departing ({%4), destination (%5)").arg(
             numberOfEngines).arg(model).arg(road).arg(rl->getName()).arg(rld->getName()));

     // first remove any locos that the train can't use
     for (int indexEng = 0; indexEng < _engineList.size(); indexEng++) {
         Engine* engine = _engineList.at(indexEng);
         // remove engines types that train does not service
         if (!_train->acceptsTypeName(engine->getTypeName())) {
             addLine(_buildReport, SEVEN, tr("Exclude loco (%1) type ({%2) is not serviced by this train").arg(
                     engine->toString()).arg(engine->getTypeName()));
             _engineList.removeAt(indexEng--);
             continue;
         }
         // remove rolling stock with roads that train does not service
         if (road==(Train::NONE) && !_train->acceptsRoadName(engine->getRoadName())) {
             addLine(_buildReport, SEVEN, tr("Exclude loco (%1) road (%2) is not serviced by this train").arg(
                     engine->toString()).arg(engine->getRoadName()));
             _engineList.removeAt(indexEng--);
             continue;
         }
         // remove engines with owners that train does not service
         if (!_train->acceptsOwnerName(engine->getOwner())) {
             addLine(_buildReport, SEVEN, tr("Exclude loco (%1) owner (%2) is not serviced by this train").arg(
                     engine->toString(), engine->getOwner()));
             _engineList.removeAt(indexEng--);
             continue;
         }
         // remove engines with built dates that train does not service
         if (!_train->acceptsBuiltDate(engine->getBuilt())) {
             addLine(_buildReport, SEVEN, tr("Exclude loco (%1) built (%2) is not serviced by this train").arg(
                     engine->toString()).arg(engine->getBuilt()));
             _engineList.removeAt(indexEng--);
             continue;
         }
         // remove engines that are out of service
         if (engine->isOutOfService()) {
             addLine(_buildReport, SEVEN, tr("Exclude loco (%1) out of service, loco''s location (%2, %3)").arg(
                     engine->toString()).arg(engine->getLocationName()).arg(engine->getTrackName()));
             _engineList.removeAt(indexEng--);
             continue;
         }
     }

     bool foundLoco = false;
     QList<Engine*> singleLocos = QList<Engine*>();
     for (int indexEng = 0; indexEng < _engineList.size(); indexEng++) {
         Engine* engine = _engineList.at(indexEng);
        log->debug(tr("Engine (%1) at location (%2, %3)").arg(engine->toString()).arg(engine->getLocationName()).arg(engine
                 ->getTrackName()));

         // use engines that are departing from the selected staging track (departTrack != NULL if staging)
         if (departStageTrack != NULL && departStageTrack!=(engine->getTrack())) {
             continue;
         }
         // use engines that are departing from the correct location
         if (engine->getLocationName()!=(rl->getName())) {
            log->debug(tr("Skipping engine (%1) at location (%2)").arg(engine->toString()).arg(engine->getLocationName()));
             continue;
         }
         // skip engines models that train does not service
         if (model!=(Train::NONE) && engine->getModel()!=(model)) {
             addLine(_buildReport, SEVEN, tr("Skip loco (%1) model (%2) location ({%3)").arg(
                     engine->toString()).arg(engine->getModel()).arg(engine->getLocationName()));
             continue;
         }
         // Does the train have a very specific engine road name requirement?
         if (road!=(Train::NONE) && engine->getRoadName()!=(road)) {
             addLine(_buildReport, SEVEN, tr("Exclude loco ({%1) road ({%2) is not serviced by this train").arg(
                     engine->toString()).arg(engine->getRoadName()));
             continue;
         }
         // skip engines on tracks that don't service the train's departure direction
         if (!checkPickUpTrainDirection(engine, rl)) {
             continue;
         }
         // skip engines that have been assigned destinations that don't match the terminal
         if (engine->getDestination() != NULL && engine->getDestinationName()!=(rld->getName())) {
             addLine(_buildReport, SEVEN, tr("Exclude loco (%1) it has an assigned destination (%2)").arg(
                     engine->toString()).arg(engine->getDestinationName()));
             continue;
         }
         // don't use non lead locos in a consist
         if (engine->getConsist() != NULL && !engine->getConsist()->isLead(engine)) {
             addLine(_buildReport, SEVEN, tr("Loco (%1) is in consist (%2) and has %3 locomotives").arg(
                     engine->toString()).arg(engine->getConsist()->getName()).arg(
                             engine->getConsist()->getEngines().size()));
             continue;
         }
         // departing staging, then all locos must go!
         if (departStageTrack != NULL) {
             if (!setLocoDestination(engine, rl, rld, terminateStageTrack)) {
                 return false;
             }
             _engineList.removeAt(indexEng--);
             foundLoco = true;
             continue;
         }
         // is this engine part of a consist?
         if (engine->getConsist() == NULL) {
          // TODO Would be nice if blocking order was only set once for B unit engines.
          // today a B unit is associated with a modelc723@knobacres

          if (engine->isBunit())
              engine->setBlocking(Engine::B_UNIT_BLOCKING);
          else
              engine->setBlocking(Engine::DEFAULT_BLOCKING_ORDER);
          // single engine, but does the train require a consist?
             // single engine, but does the train require a consist?
             if (numberOfEngines > 1) {
                 addLine(_buildReport, SEVEN, tr("Skip single loco (%1) train requires %2 locomotives").arg(
                         engine->toString()).arg(numberOfEngines));
                 singleLocos.append(engine);
                 continue;
             }
             // engine is part of a consist
         } else if (engine->getConsist()->isLead(engine)) {
             addLine(_buildReport, SEVEN, tr("Loco (%1) is lead loco for consist (%2) and has %3 locomotives").arg(
                     engine->toString()).arg(engine->getConsist()->getName()).arg(
                             engine->getConsist()->getSize()));
             if (engine->getConsist()->getSize() == numberOfEngines) {
                log->debug(tr("Consist (%1) has the required number of engines").arg(engine->getConsist()->getName())); // NOI18N
             } else if (numberOfEngines != 0) {
                 addLine(_buildReport, SEVEN, tr("Exclude loco (%1) consist (%2) wrong number of locomotives (%3)").arg(engine->toString()).arg(
                         engine->getConsist()->getName()).arg(engine->getConsist()->getSize()));
                 continue;
             }
         }
         // found a loco!
         foundLoco = true;

         // now find terminal track for engine(s)
         addLine(_buildReport, FIVE, tr("Loco (%1) road (%2) model (%3) type (%4) at location (%5, %6) destination (%7)").arg(
                 engine->toString()).arg(engine->getRoadName()).arg(engine->getModel()).arg(engine->getTypeName()).arg(
                         engine->getLocationName()).arg(engine->getTrackName()).arg(rld->getName()));
         if (setLocoDestination(engine, rl, rld, terminateStageTrack)) {
             _engineList.removeAt(indexEng--);
             return true; // done
         }
     }
     // build a consist out of non-consisted locos
     if (!foundLoco && numberOfEngines > 1 && _train->isBuildConsistEnabled()) {
         addLine(_buildReport, FIVE, tr("Option to build consist with %1 locos departing (%2) is enabled").arg(
                 numberOfEngines).arg(rl->getName()));
         addLine(_buildReport, FIVE, tr("There are %1 single locomotives at (%2) that meet this train''s requirements").arg(
                 singleLocos.size()).arg(rl->getName()));
         if (singleLocos.size() >= numberOfEngines) {
             int locos = 0;
             foreach (Engine* engine, singleLocos) {
                 if (setLocoDestination(engine, rl, rld, terminateStageTrack)) {
                     _engineList.removeOne(engine);
                     locos++;
                 }
                 if (locos == numberOfEngines) {
                     return true; // done
                 }
             }
         }
     }
     if (!foundLoco) {
         QString locationName = rl->getName();
         if (departStageTrack != NULL) {
             locationName = locationName + ", " + departStageTrack->getName();
         }
         addLine(_buildReport, FIVE, tr("Requested locomotives not found at location (%1)").arg(
                 locationName));
     } else if (departStageTrack != NULL) {
         return true;
     }
     // not able to assign engines to train
     return false;
 }

 /*private*/ bool TrainBuilder::setLocoDestination(Engine* engine, RouteLocation* rl, RouteLocation* rld, Track* terminateTrack) {
     // is there a staging track?
     if (terminateTrack != NULL) {
         QString status = engine->testDestination(terminateTrack->getLocation(), terminateTrack);
         if (status==(Track::OKAY)) {
             addEngineToTrain(engine, rl, rld, terminateTrack);
             return true; // done
         }
         else
         {
          addLine(_buildReport, SEVEN, tr("Can't send loco (%1) to %4 (%2) due to %3")
                  .arg(engine->toString()).arg(terminateTrack->getName()).arg(status).arg(
                             terminateTrack->getTrackTypeName()));
         }
         // find a destination track for this engine
     } else {
         Location* destination = rld->getLocation();
         QList<Track*> destTracks = destination->getTrackByMovesList(NULL);
         if (destTracks.size() == 0) {
             addLine(_buildReport, THREE, tr("Error, no tracks at destination (%1)!").arg(
                     rld->getName()));
         }
         foreach (Track* track, destTracks) {
             if (!checkDropTrainDirection(engine, rld, track)) {
                 continue;
             }
             QString status = engine->testDestination(destination, track);
             if (status==(Track::OKAY)) {
                 addEngineToTrain(engine, rl, rld, track);
                 return true; // done
             } else {
                 addLine(_buildReport, SEVEN,
                         tr("Can't send loco (%1) to %4 (%2) due to %3").arg(engine->toString()).arg(
                                 track->getName()).arg(status).arg(track->getTrackTypeName()));
             }
         }
         addLine(_buildReport, FIVE, tr("Can't move locomotive (%1) to destination (%2)").arg(
                 engine->toString()).arg(rld->getName()));
     }
     return false; // not able to set loco's destination
 }

 /**
  * Returns the number of engines needed for this train, minimum 1, maximum
  * user specified in setup. Based on maximum allowable train length and
  * grade between locations, and the maximum cars that the train can have at
  * the maximum train length. One engine per sixteen 40' cars for 1% grade.
  * TODO Currently ignores the cars weight and engine horsepower
  *
  * @return The number of engines needed
  */
 /*private*/ int TrainBuilder::getAutoEngines() {
     double numberEngines = 1;
     int moves = 0;

     foreach (RouteLocation* rl, *_routeList) {
         moves += rl->getMaxCarMoves();
         double carDivisor = 16; // number of 40' cars per engine 1% grade
         // change engine requirements based on grade
         if (rl->getGrade() > 1) {
             double grade = rl->getGrade();
             carDivisor = carDivisor / grade;
         }
        log->debug(tr("Maximum train length %1 for location (%2)").arg(rl->getMaxTrainLength()).arg(rl->getName()));
         if (rl->getMaxTrainLength() / (carDivisor * 40) > numberEngines) {
             numberEngines = rl->getMaxTrainLength() / (carDivisor * (40 + Car::COUPLER));
             // round up to next whole integer
             numberEngines = qCeil(numberEngines);
             if (numberEngines > moves / carDivisor) {
                 numberEngines = qCeil(moves / carDivisor);
             }
             if (numberEngines < 1) {
                 numberEngines = 1;
             }
         }
     }
     int nE = (int) numberEngines;
     addLine(_buildReport, ONE, tr("Auto calculates that %1 locomotives are required for this train").arg(nE));
     if (nE > Setup::getMaxNumberEngines()) {
         addLine(_buildReport, THREE, tr("The maximum number of locomotives that can be assigned is {%1").arg(
                 Setup::getMaxNumberEngines()));
         nE = Setup::getMaxNumberEngines();
     }
     return nE;
 }

 /**
  * Find a car with FRED if needed at the correct location and add it to the
  * train. If departing staging, places car with FRED at the rear of the
  * train.
  *
  * @param road Optional road name for this car.
  * @param rl Where in the route to pick up this car.
  * @param rld Where in the route to set out this car.
  * @throws BuildFailedException If car not found.
  */
 /*private*/ void TrainBuilder::getCarWithFred(QString road, RouteLocation* rl, RouteLocation* rld) //throws BuildFailedException
{
     // load departure track if staging
     Track* departTrack = NULL;
     if (rl == _train->getTrainDepartsRouteLocation()) {
         departTrack = _departStageTrack;
     }
     bool foundCar = false;
     bool requiresCar = false;
     // Does this train require a car with FRED?
     if ((_train->getRequirements() & Train::FRED) == 0) {
         addLine(_buildReport, FIVE, tr("buildTrainNoFred"));
         if (departTrack == NULL) // if not departing staging we're done
         {
             return;
         }
     } else {
         addLine(_buildReport, ONE, tr("Train (%1) requires car with FRED, road (%2) departing (%3) destination (%4)").arg(
                 _train->getName()).arg(road).arg(rl->getName()).arg(rld->getName()));
         requiresCar = true;
     }
     for (_carIndex = 0; _carIndex < _carList->size(); _carIndex++) {
         Car* car = _carList->at(_carIndex);
         if (car->hasFred()) {
             addLine(_buildReport, SEVEN, tr("Car (%1) has a FRED, road (%2) at location (%3)").arg(
                     car->toString()).arg(car->getRoadName()).arg(car->getLocationName()));
             // car departing staging must leave with train
             if (car->getTrack() == departTrack) {
                 foundCar = false;
                 if (checkCarForDestinationAndTrack(car, rl, rld)) {
                     if (car->getTrain() == _train) {
                         foundCar = true;
                     }
                 } else if (findDestinationAndTrack(car, rl, rld)) {
                     foundCar = true;
                 }
                 if (!foundCar) {
                     throw BuildFailedException(
                             tr("BUILD FAILED car (%1) departing staging without a destination").arg(car->toString()));
                  return;
                 }
             } // is there a specific road requirement for the car with FRED?
             else if (road!=(Train::NONE) && road!=(car->getRoadName())) {
                 addLine(_buildReport, SEVEN, tr("Exclude car (%1) type (%2) train doesn''t service road (%3)").arg(
                         car->toString()).arg(car->getTypeName()).arg(car->getRoadName()));
                 _carList->removeOne(car); // remove this car from the list
                 _carIndex--;
                 continue;
             } else if (!foundCar && car->getLocationName()==(rl->getName())) {
                 // remove cars that can't be picked up due to train and track directions
                 if (!checkPickUpTrainDirection(car, rl)) {
                     addLine(_buildReport, SEVEN,
                             tr("Exclude car (%1) type (%2) at location (%3)").arg(car->toString()).arg(
                                     car->getTypeName()).arg((car->getLocationName() + " " + car->getTrackName())));
                     _carList->removeOne(car); // remove this car from the list
                     _carIndex--;
                     continue;
                 }
                 if (checkCarForDestinationAndTrack(car, rl, rld)) {
                     if (car->getTrain() == _train) {
                         foundCar = true;
                     }
                 } else if (findDestinationAndTrack(car, rl, rld)) {
                     foundCar = true;
                 }
                 if (foundCar && departTrack == NULL) {
                     break;
                 }
             }
         }
     }
     if (requiresCar && !foundCar) {
         throw BuildFailedException(tr("Train (%1) requires %2, can't meet requirements at departure (%3) and/or termination (%4)").arg(
                 _train->getName()).arg(tr("FRED")).arg(rl->getName()).arg(rld->getName()));
      return;
     }
 }

 /**
  * Find a caboose if needed at the correct location and add it to the train.
  * If departing staging, any caboose found is added to the train. If there
  * isn't a road name required for the caboose, tries to find a caboose with
  * the same road name as the lead engine->
  *
  * @param roadCaboose Optional road name for this car.
  * @param leadEngine The lead engine for this train. Used to find a caboose
  *            with the same road name as the the engine->
  * @param rl Where in the route to pick up this car.
  * @param rld Where in the route to set out this car.
  * @param requiresCaboose When true, the train requires a caboose.
  * @throws BuildFailedException If car not found.
  */
 /*private*/ void TrainBuilder::getCaboose(QString roadCaboose, Engine* leadEngine, RouteLocation* rl, RouteLocation* rld,
         bool requiresCaboose) //throws BuildFailedException
{
     if (rl == NULL) {
         throw BuildFailedException(tr("Caboose change requested for train (%1) departure location missing!").arg(
                 _train->getName()));
      return;
     }
     if (rld == NULL) {
         throw BuildFailedException(tr("Caboose change requested for train ({0}) departs ({1}) change location missing!").arg(
                 _train->getName()).arg(rl->getName()),"Normal");
      return;
     }
     // load departure track if staging
     Track* departTrack = NULL;
     if (rl == _train->getTrainDepartsRouteLocation()) {
         departTrack = _departStageTrack;
     }
     if (!requiresCaboose) {
         addLine(_buildReport, FIVE, tr("Train does not require caboose when departing (%1)").arg(
                 rl->getName()));
         if (departTrack == NULL) {
             return;
         }
     } else {
         addLine(_buildReport, ONE, tr("Train (%1) requires caboose, road (%2) departing (%3) destination (%4)").arg(
                 _train->getName()).arg(roadCaboose).arg(rl->getName()).arg(rld->getName()));
     }
     // Does the route have enough moves?
     // if (requiresCaboose && rl->getMaxCarMoves() - rl->getCarMoves() <= 0) {
     // emit buildException(tr("buildErrorNoMoves"), new Object[] {
     // rl->getName(), rl->getId(), tr("Caboose") ));
     // }
     // Now go through the car list looking for cabooses
     bool cabooseTip = true; // add a user tip to the build report about cabooses if none found
     bool cabooseAtDeparture = false; // set to true if caboose at departure location is found
     bool foundCaboose = false;
     for (_carIndex = 0; _carIndex < _carList->size(); _carIndex++)
     {
      Car* car = _carList->at(_carIndex);
      if (car->isCaboose())
      {
       cabooseTip = false; // found at least one caboose, so they exist!
       addLine(_buildReport, SEVEN, tr("Car (%1) is a caboose, road (%2) at location (%3, %4)").arg(
               car->toString()).arg(car->getRoadName()).arg(car->getLocationName()).arg(car->getTrackName()));
       // car departing staging must leave with train
       if (car->getTrack() == departTrack) {
           foundCaboose = false;
           if (checkCarForDestinationAndTrack(car, rl, rld)) {
               if (car->getTrain() == _train) {
                   foundCaboose = true;
               }
           } else if (findDestinationAndTrack(car, rl, rld)) {
               foundCaboose = true;
           }
           if (!foundCaboose) {
               throw BuildFailedException(
                       tr("BUILD FAILED car (%1) departing staging without a destination").arg(car->toString()));
            return;
           }
       } // is there a specific road requirement for the caboose?
       else if (roadCaboose!=(Train::NONE) && roadCaboose!=(car->getRoadName()))
       {
           continue;
       }
       else if (!foundCaboose && car->getLocationName()==(rl->getName()))
       {
        // remove cars that can't be picked up due to train and track directions
        if (!checkPickUpTrainDirection(car, rl)) {
            addLine(_buildReport, SEVEN,
                    tr("Exclude car (%1) type (%2) at location (%3)").arg(car->toString(),
                            car->getTypeName()).arg((car->getLocationName() + " " + car->getTrackName())));
            _carList->removeOne(car); // remove this car from the list
            _carIndex--;
            continue;
        }
        // first pass, take a caboose that matches the engine
        if (leadEngine != NULL && car->getRoadName()==(leadEngine->getRoadName())) {
            addLine(_buildReport, SEVEN, tr("Car (%1) road (%2) matches loco (%3)").arg(
                    car->toString()).arg(car->getRoadName()).arg(leadEngine->toString()));
            if (checkCarForDestinationAndTrack(car, rl, rld)) {
                if (car->getTrain() == _train) {
                    foundCaboose = true;
                }
            } else if (findDestinationAndTrack(car, rl, rld)) {
                foundCaboose = true;
            }
            if (!foundCaboose) {
                _carList->removeOne(car); // remove this car from the list
                _carIndex--;
                continue;
            }
        }
        // done if we found a caboose and not departing staging
        if (foundCaboose && departTrack == NULL) {
            break;
        }
       }
      }
     }
     if (requiresCaboose && !foundCaboose) {
        log->debug("Second pass looking for caboose");
         // second pass, take any caboose available
         for (_carIndex = 0; _carIndex < _carList->size(); _carIndex++) {
             Car* car = _carList->at(_carIndex);
             if (car->isCaboose() && car->getLocationName()==(rl->getName())) {
                 // is there a specific road requirement for the caboose?
                 if (roadCaboose!=(Train::NONE) && roadCaboose!=(car->getRoadName())) {
                     continue; // yes
                 }
                 // okay, we found a caboose at the departure location
                 cabooseAtDeparture = true;
                 if (checkCarForDestinationAndTrack(car, rl, rld)) {
                     if (car->getTrain() == _train) {
                         foundCaboose = true;
                         break;
                     }
                 } else if (findDestinationAndTrack(car, rl, rld)) {
                     foundCaboose = true;
                     break;
                 }
             }
         }
     }
     if (requiresCaboose && !foundCaboose) {
         if (cabooseTip) {
             addLine(_buildReport, ONE, tr("NOTE! To make a car a caboose you must select the caboose check box in the \"Edit Car\" window"));
             addLine(_buildReport, ONE, tr("NOTE! The train has to also service the car type (Caboose)"));
         }
         if (!cabooseAtDeparture) {
             throw BuildFailedException(tr("Train (%1) requires %2, can't find %2 at departure (%3)").arg( _train->getName()).arg(tr("Caboose").toLower()).arg(rl->getName()));
          return;
         }
         // we did find a caboose at departure that meet requirements, but couldn't place it at destination.
         throw BuildFailedException(tr("Train (%1) requires %2, can't set out %2 at destination (%3)").arg( _train->getName()).arg(tr("Caboose")).arg(rld->getName()));
         return;
     }
 }

 /**
  * Removes the remaining cabooses and cars with FRED from consideration.
  * Also saves a car's final destination in case of train reset.
  *
  * @throws BuildFailedException
  */
 /*private*/ void TrainBuilder::removeCaboosesAndCarsWithFredAndSaveFinalDestination() //throws BuildFailedException
{
     addLine(_buildReport, SEVEN, BLANK_LINE); // add line when in very detailed report mode
     addLine(_buildReport, SEVEN, tr("Remove cars not needed by this train:"));
     for (_carIndex = 0; _carIndex < _carList->size(); _carIndex++) {
         Car* car = _carList->at(_carIndex);
         if (car->isCaboose() || car->hasFred()) {
             addLine(_buildReport, SEVEN, tr("Exclude car (%1) type (%2) at location (%3)").arg(
                     car->toString()).arg(car->getTypeName()).arg(
                             (car->getLocationName() + ").arg(" + car->getTrackName())));
             if (car->getTrack() == _departStageTrack) {
                 throw BuildFailedException(tr("ERROR: Attempt to removed car with FRED or Caboose from staging")); // NOI18N
              return;
             }
             _carList->removeOne(car); // remove this car from the list
             _carIndex--;
         }
         // save /*final*/ destination and track values in case of train reset
         car->setPreviousFinalDestination(car->getFinalDestination());
         car->setPreviousFinalDestinationTrack(car->getFinalDestinationTrack());
         car->setPreviousScheduleId(car->getScheduleItemId());
     }
 }

 /**
  * Remove unwanted cars from the car list. Remove cars that don't have a
  * track assignment, and check that the car can be serviced by this train.
  * Lists all cars available to train by location.
  */
 /*private*/ void TrainBuilder::removeCars() //throws BuildFailedException
{
     addLine(_buildReport, SEVEN, BLANK_LINE); // add line when in very detailed report mode
     addLine(_buildReport, SEVEN, tr("Remove cars not serviced by this train:"));
     bool showCar = true;
     int carListSize = _carList->size();
     for (_carIndex = 0; _carIndex < _carList->size(); _carIndex++) {
         Car* car = _carList->at(_carIndex);
         // only show the first 100 cars removed
         if (showCar && carListSize - _carList->size() == DISPLAY_CAR_LIMIT_100) {
             showCar = false;
             addLine(_buildReport, FIVE, tr("********** Only the first %1 cars are shown for (%2) **********").arg(
                     DISPLAY_CAR_LIMIT_100).arg( tr("Type")));
         }
         // remove cars that don't have a track assignment
         if (car->getTrack() == NULL) {
             addLine(_buildReport, ONE, tr("buildErrorRsNoLoc").arg(
                     car->toString(), car->getLocationName()));
             _carList->removeOne(car);
             _carIndex--;
             continue;
         }
         // remove cars that have been reported as missing
         if (car->isLocationUnknown()) {
             addLine(_buildReport, SEVEN, tr("Exclude car (%1) location unknown, last known location (%2, %3)").arg(
                     car->toString()).arg(car->getLocationName()).arg(car->getTrackName()));
             if (car->getTrack()==(_departStageTrack)) {
                 throw BuildFailedException(tr("Staging (%1, %2) has a car (%3) with an unknown location").arg(
                         car->getLocationName()).arg(car->getTrackName()).arg(car->toString()));
              return;
             }
             _carList->removeOne(car);
             _carIndex--;
             continue;
         }
         // remove cars that are out of service
         if (car->isOutOfService()) {
             addLine(_buildReport, SEVEN, tr("Exclude car (%1) out of service, car''s location (%2, %3)").arg(
                     car->toString()).arg(car->getLocationName()).arg(car->getTrackName()));
             if (car->getTrack()==(_departStageTrack)) {
                 throw BuildFailedException(tr("Staging (%1, %2) has a car (%3) that is out of service").arg(car->getLocationName(),
                         car->getTrackName()).arg(car->toString()));
              return;
             }
             _carList->removeOne(car);
             _carIndex--;
             continue;
         }

         // remove cars with FRED that have a destination that isn't the terminal
         if (car->hasFred() && car->getDestination() != NULL && car->getDestination() != _terminateLocation) {
             addLine(_buildReport, FIVE, tr("Exclude car (%1) type (%2) wrong destination (%3) for this train").arg(
                     car->toString()).arg(car->getTypeName()).arg(car->getDestinationName()));
             _carList->removeOne(car);
             _carIndex--;
             continue;
         }

         // remove cabooses that have a destination that isn't the terminal, no caboose changes in the train's route
         if (car->isCaboose() && car->getDestination() != NULL && car->getDestination() != _terminateLocation
                 && _train->getSecondLegOptions() == Train::NO_CABOOSE_OR_FRED
                 && _train->getThirdLegOptions() == Train::NO_CABOOSE_OR_FRED) {
             addLine(_buildReport, FIVE, tr("Exclude car (%1) type (%2) wrong destination (%3) for this train").arg(
                     car->toString()).arg(car->getTypeName()).arg(car->getDestinationName()));
             _carList->removeOne(car);
             _carIndex--;
             continue;
         }

         // is car at interchange?
         if (car->getTrack()->getTrackType()==(Track::INTERCHANGE)) {
             // don't service a car at interchange and has been dropped off by this train
             if (car->getTrack()->getPickupOption()==(Track::ANY)
                     && car->getSavedRouteId()==(_train->getRoute()->getId())) {
                 addLine(_buildReport, SEVEN, tr("Exclude car (%1) previously set out by this train''s route (%2) at classification/interchange (%3, %4)").arg(
                         car->toString()).arg(_train->getRoute()->getName()).arg(car->getLocationName(),
                                 car->getTrackName()));
                 _carList->removeOne(car);
                 _carIndex--;
                 continue;
             }
         }
         if (car->getTrack()->getTrackType()==(Track::INTERCHANGE)
                 || car->getTrack()->getTrackType()==(Track::SPUR)) {
             if (car->getTrack()->getPickupOption()==(Track::TRAINS)
                     || car->getTrack()->getPickupOption()==(Track::EXCLUDE_TRAINS)) {
                 if (car->getTrack()->acceptsPickupTrain(_train)) {
                    log->debug(tr("Car (%1) can be picked up by this train").arg(car->toString()));
                 } else {
                     addLine(_buildReport, SEVEN, tr("Exclude car (%1) by train, no pick up from %2 (%3, %4)").arg(
                             car->toString()).arg(car->getTrack()->getTrackTypeName(),
                                     car->getLocationName()).arg(car->getTrackName()));
                     _carList->removeOne(car);
                     _carIndex--;
                     continue;
                 }
             } else if (car->getTrack()->getPickupOption()==(Track::ROUTES)
                     || car->getTrack()->getPickupOption()==(Track::EXCLUDE_ROUTES)) {
                 if (car->getTrack()->acceptsPickupRoute(_train->getRoute())) {
                    log->debug(tr("Car (%1) can be picked up by this route").arg(car->toString()));
                 } else {
                     addLine(_buildReport, SEVEN, tr("Exclude car (%1) by route, no pick up from %2 (%3, %4)").arg(
                             car->toString()).arg(car->getTrack()->getTrackTypeName()).arg(
                                     car->getLocationName()).arg(car->getTrackName()));
                     _carList->removeOne(car);
                     _carIndex--;
                     continue;
                 }
             }
         }

         // all cars in staging must be accepted, so don't exclude if in staging
         // note that for trains departing staging the engine and car roads and types were
         // checked in the routine checkDepartureStagingTrack().
         if (_departStageTrack == NULL || car->getTrack() != _departStageTrack) {
             if (!_train->acceptsRoadName(car->getRoadName())) {
                 addLine(_buildReport, SEVEN, tr("Exclude car (%1) type (%2) train doesn''t service road (%3)").arg(
                         car->toString()).arg(car->getTypeName()).arg(car->getRoadName()));
                 _carList->removeOne(car);
                 _carIndex--;
                 continue;
             }
             if (!_train->acceptsTypeName(car->getTypeName())) {
                 if (showCar) {
                     addLine(_buildReport, SEVEN, tr("Exclude car (%1) type (%2) train doesn''t service type (%2)").arg(
                             car->toString()).arg(car->getTypeName()));
                 }
                 _carList->removeOne(car);
                 _carIndex--;
                 continue;
             }
             if (!car->isCaboose() && !car->isPassenger() && !_train->acceptsLoad(car->getLoadName(), car->getTypeName())) {
                 addLine(_buildReport, SEVEN, tr("Exclude car (%1) type (%2) train doesn''t service load (%3)").arg(
                         car->toString()).arg(car->getTypeName()).arg(car->getLoadName()));
                 _carList->removeOne(car);
                 _carIndex--;
                 continue;
             }
             if (!_train->acceptsOwnerName(car->getOwner())) {
                 addLine(_buildReport, SEVEN, tr("Exclude car (%1) owner (%2) at location (%3)").arg(
                         car->toString(), car->getOwner(),
                                 (car->getLocationName() + ").arg(" + car->getTrackName())));
                 _carList->removeOne(car);
                 _carIndex--;
                 continue;
             }
             if (!_train->acceptsBuiltDate(car->getBuilt())) {
                 addLine(_buildReport, SEVEN, tr("Exclude car (%1) built (%2) at location (%3)").arg(
                         car->toString()).arg(car->getBuilt()).arg(
                                 (car->getLocationName() + ").arg(" + car->getTrackName())));
                 _carList->removeOne(car);
                 _carIndex--;
                 continue;
             }
             // remove cars with FRED if not needed by train
             if (car->hasFred() && (_train->getRequirements() & Train::FRED) == 0) {
                 addLine(_buildReport, SEVEN,
                         tr("Exclude car with FRED (%1) type (%2) at location (%3)").arg(car->toString()).arg(
                                 car->getTypeName()).arg((car->getLocationName() + ").arg(" + car->getTrackName())));
                 _carList->removeOne(car); // remove this car from the list
                 _carIndex--;
                 continue;
             }
             // does car have a wait count?
             if (car->getWait() > 0 && _train->services(car)) {
                 addLine(_buildReport, SEVEN, tr("Exclude car (%1) type (%2) at location (%3) wait (%4)").arg(
                         car->toString()).arg(car->getTypeName()).arg(
                                 (car->getLocationName() + ").arg(" + car->getTrackName()), car->getWait()));
                 car->setWait(car->getWait() - 1); // decrement wait count
                 car->updateLoad(); // has the wait count reached 0?
                 _carList->removeOne(car);
                 _carIndex--;
                 continue;
             }
             if (car->getPickupScheduleId()!=(Car::NONE)) {
                 if (car->getPickupScheduleId()==(((TrainManager*)InstanceManager::getDefault("TrainManager"))->getTrainScheduleActiveId())) {
                     car->setPickupScheduleId(Car::NONE);
                 } else {
                     TrainSchedule* sch = ((Operations::TrainScheduleManager*)InstanceManager::getDefault("TrainScheduleManager"))->getScheduleById(car->getPickupScheduleId());
                     if (sch != NULL) {
                         addLine(_buildReport, SEVEN, tr("Exclude car (%1) type (%2) at location (%3, %4) scheduled pickup on (%5)").arg(car->toString(),
                                 car->getTypeName()).arg(car->getLocationName()).arg(car->getTrackName()).arg(sch->getName()));
                         _carList->removeOne(car);
                         _carIndex--;
                         continue;
                     }
                 }
             }
         }
     }
     // adjust car list to only have cars from one staging track
     if (_departStageTrack != NULL) {
         // Make sure that all cars in staging are moved
         _train->getTrainDepartsRouteLocation()->setCarMoves(
                 _train->getTrainDepartsRouteLocation()->getMaxCarMoves() - _departStageTrack->getNumberCars());
         int numCarsFromStaging = 0;
         _numOfBlocks = QHash<QString, int>();
         addLine(_buildReport, SEVEN, BLANK_LINE); // add line when in very detailed report mode
         addLine(_buildReport, SEVEN, tr("Remove cars from the other staging tracks:"));
         for (_carIndex = 0; _carIndex < _carList->size(); _carIndex++)
         {
             Car* c = _carList->at(_carIndex);
             if (c->getLocationName()==(_departLocation->getName())) {
                 if (c->getTrackName()==(_departStageTrack->getName())) {
                     numCarsFromStaging++;
                     // populate car blocking hashtable
                     // don't block cabooses, cars with FRED, or passenger. Only block lead cars in kernel
                     if (!c->isCaboose() && !c->hasFred() && !c->isPassenger()
                             && (c->getKernel() == NULL || c->getKernel()->isLead(c))) {
                        log->debug(tr("Car %1 last location id: %2").arg(c->toString()).arg(c->getLastLocationId()));
                         int number = 1;
                         if (_numOfBlocks.contains(c->getLastLocationId())) {
                             number = _numOfBlocks.value(c->getLastLocationId()) + 1;
                             _numOfBlocks.remove(c->getLastLocationId());
                         }
                         _numOfBlocks.insert(c->getLastLocationId(), number);
                     }
                 } else {
                     addLine(_buildReport, SEVEN, tr("Exclude car (%1) from staging (%2)").arg(
                             c->toString()).arg((c->getLocationName() + ").arg(" + c->getTrackName())));
                     _carList->removeOne(c);
                     _carIndex--;
                 }
             }
         }
         // show how many cars are departing from staging
         addLine(_buildReport, FIVE, BLANK_LINE); // add line when in detailed report mode
         addLine(_buildReport, FIVE, tr("Departing staging (%1, %2) with %3 cars").arg(
                 _departStageTrack->getLocation()->getName()).arg(_departStageTrack->getName()).arg(
                         numCarsFromStaging));
         // and list them
         foreach (Car* c, *_carList) {
             if (c->getTrack() == _departStageTrack) {
                 addLine(_buildReport, SEVEN, tr("Staging car (%1) type (%2) load (%3)").arg(
                         c->toString()).arg(c->getTypeName()).arg(c->getLoadName()));
             }
         }
         // error if all of the cars and engines from staging aren't available
         if (numCarsFromStaging + _departStageTrack->getNumberEngines() != _departStageTrack->getNumberRS()) {
             throw BuildFailedException(tr("ERROR not all cars or locos in staging can be serviced by this train, %1 cars or locos can not be serviced").arg(
                     (_departStageTrack->getNumberRS()
                             - (numCarsFromStaging + _departStageTrack->getNumberEngines()))));
          return;
         }
        log->debug(tr("Staging departure track (%1) has %2 cars and %3 blocks").arg(_departStageTrack->getName()).arg(
                 numCarsFromStaging).arg(_numOfBlocks.size())); // NOI18N
     }

     // show how many cars were found
     addLine(_buildReport, FIVE, BLANK_LINE); // add line when in detailed report mode
     addLine(_buildReport, ONE, tr("Found %1 cars for train (%2)").arg(
             (_carList->size())).arg(_train->getName()));

     QStringList locationNames = QStringList(); // only show cars once using the train's route
     foreach (RouteLocation* rl, *_train->getRoute()->getLocationsBySequenceList()) {
         if (locationNames.contains(rl->getName())) {
             continue;
         }
         locationNames.append(rl->getName());
         if (rl->getLocation()->isStaging()) {
             addLine(_buildReport, SEVEN, tr("Cars in staging (%1):").arg(
                     rl->getName()));
         } else {
             addLine(_buildReport, SEVEN, tr("Cars at location (%1):").arg(
                     rl->getName()));
         }
         // now go through the car list and remove non-lead cars in kernels, destinations that aren't part of this
         // route
         int carCount = 0;
         for (_carIndex = 0; _carIndex < _carList->size(); _carIndex++) {
             Car* car = _carList->at(_carIndex);
             if (car->getLocationName()!=(rl->getName())) {
                 continue;
             }
             // only print out the first DISPLAY_CAR_LIMIT cars for each location
             if (carCount < DISPLAY_CAR_LIMIT_50) {
                 if (car->getLoadPriority()==(CarLoad::PRIORITY_LOW)) {
                     addLine(_buildReport, SEVEN, tr("Car (%1) type (%2) at (%3) %4 moves").arg(
                             car->toString(), car->getTypeName()).arg(
                                     (car->getLocationName() + ").arg(" + car->getTrackName())).arg(car->getMoves()));
                 } else {
                     addLine(_buildReport, SEVEN, tr("Car (%1) type (%2) at (%3) %4 moves, priority %5").arg(car->toString(),
                             car->getTypeName()).arg((car->getLocationName() + ").arg(" + car->getTrackName())).arg(car->getMoves()).arg(
                             car->getLoadPriority()));
                 }
             }
             if (carCount == DISPLAY_CAR_LIMIT_50) {
                 addLine(_buildReport, SEVEN, tr("********** Only the first %1 cars are shown for (%2) **********").arg(
                         carCount).arg(rl->getName()));
             }
             carCount++;
             // use only the lead car in a kernel for building trains
             if (car->getKernel() != NULL) {
                 if (car->getKernel()->isLead(car)) {
                     addLine(_buildReport, SEVEN, tr("Car (%1) is lead in kernel (%2) with %3 cars, %4 %5").arg(
                             car->toString()).arg(car->getKernelName()).arg(car->getKernel()->getSize(),
                                     car->getKernel()->getTotalLength()).arg(Setup::getLengthUnit().toLower()));
                 } else {
                     addLine(_buildReport, SEVEN, tr("Car (%1) is in kernel (%2) with %3 cars, %4 %5").arg(
                             car->toString()).arg(car->getKernelName()).arg(car->getKernel()->getSize(),
                                     car->getKernel()->getTotalLength()).arg(Setup::getLengthUnit().toLower()));
                 }
                 checkKernel(car);
                 if (!car->getKernel()->isLead(car)) {
                     _carList->removeOne(car); // remove this car from the list
                     _carIndex--;
                     continue;
                 }
             }
             if (_train==(car->getTrain())) {
                 addLine(_buildReport, FIVE, tr("Car (%1) already assigned to this train").arg(
                         car->toString()));
             }
             // does car have a destination that is part of this train's route?
             if (car->getDestination() != NULL) {
                 addLine(_buildReport, SEVEN, tr("Car (%1) has assigned destination (%2)").arg(
                         car->toString()).arg(
                                 (car->getDestinationName() + ").arg(" + car->getDestinationTrackName())));
                 RouteLocation* rld = _train->getRoute()->getLastLocationByName(car->getDestinationName());
                 if (rld == NULL) {
                     addLine(_buildReport, SEVEN, tr("Exclude car (%1) destination (%2) not part of this train''s route (%3)").arg(car->toString(),
                             car->getDestinationName()).arg(_train->getRoute()->getName()));
                     // build failure if car departing staging
                     if (car->getLocation()==(_departLocation) && _departStageTrack != NULL) {
                         // The following code should not be executed, departing staging tracks are checked before
                         // this
                         // routine.
                         throw BuildFailedException(tr("Car (%1) departing staging with destination that is not part of this train''s route").arg(car->toString()));
                      return;
                     }
                     _carList->removeOne(car); // remove this car from the list
                     _carIndex--;
                 }
             }
         }
         addLine(_buildReport, SEVEN, BLANK_LINE); // add line when in detailed report mode
     }
     return;
 }

 /**
  * Verifies that all cars in the kernel have the same departure track. Also
  * checks to see if the kernel has a lead car and the lead car is in
  * service.
  *
  * @param car
  * @throws BuildFailedException
  */
 /*private*/ void TrainBuilder::checkKernel(Car* car) //throws BuildFailedException
{
     bool foundLeadCar = false;
     foreach (Car* c, car->getKernel()->getCars()) {
         // check that lead car exists
         if (c->getKernel()->isLead(c) && !c->isOutOfService()) {
             foundLeadCar = true;
         }
         // check to see that all cars have the same location and track
         if (car->getLocation() != c->getLocation() || car->getTrack() != c->getTrack()) {
             throw BuildFailedException(tr("Car (%1) in kernel (%2) doesn''t match car (%3) location").arg(
                     c->toString()).arg(car->getKernelName()).arg(car->toString()));
          return;
         }
     }
     if (foundLeadCar == false) {
         throw BuildFailedException(tr("No lead car in kernel (%1)").arg(
                 car->getKernelName()));
     }
 }

 /**
  * Block cars departing staging. No guarantee that cars departing staging
  * can be blocked by destination. By using the pick up location id, this
  * routine tries to find destinations that are willing to accepts all of the
  * cars that were "blocked" together when they were picked up. Rules: The
  * route must allow set outs at the destination. The route must allow the
  * correct number of set outs. The destination must accept all cars in the
  * pick up block.
  *
  * @throws BuildFailedException
  */
 /*private*/ void TrainBuilder::blockCarsFromStaging() //throws BuildFailedException
{
     if (_departStageTrack == NULL || !_departStageTrack->isBlockCarsEnabled()) {
         return;
     }

     addLine(_buildReport, THREE, BLANK_LINE);
     addLine(_buildReport, THREE, tr("Departure staging track (%1) has %2 blocks of cars").arg(
             _departStageTrack->getName()).arg(_numOfBlocks.size()));

     QStringListIterator en(_numOfBlocks.keys());
     while (en.hasNext()) {
         QString locId = en.next();
         int numCars = _numOfBlocks.value(locId);
         QString locName = "";
         Location* l = locationManager->getLocationById(locId);
         if (l != NULL) {
             locName = l->getName();
         }
         addLine(_buildReport, SEVEN, tr("Block (%1) originally from (%2) has %3 cars").arg(
                 locId).arg(locName).arg(numCars));
         if (_numOfBlocks.size() < 2) {
             addLine(_buildReport, SEVEN, tr("Unable to block cars from staging only 1 block found"));
             return;
         }
     }
     blockByLocationMoves();
     addLine(_buildReport, SEVEN, tr("Done blocking cars from staging track (%1)").arg(
             _departStageTrack->getName()));
 }

 /**
  * Blocks cars out of staging by assigning the largest blocks of cars to
  * locations requesting the most moves.
  */
 /*private*/ void TrainBuilder::blockByLocationMoves() //throws BuildFailedException
{
     // start at the second location in the route to begin blocking
     QList<RouteLocation*>* routeList = _train->getRoute()->getLocationsBySequenceList();
     foreach(RouteLocation* rl, *routeList) {
         int possibleMoves = rl->getMaxCarMoves() - rl->getCarMoves();
         if (rl->isDropAllowed() && possibleMoves > 0) {
             addLine(_buildReport, SEVEN, tr("Location (%1) has %2 possible moves").arg(
                     rl->getName()).arg( possibleMoves));
         }
     }
     // now block out cars, send the largest block of cars to the locations requesting the greatest number of moves
     RouteLocation* rl = _train->getTrainDepartsRouteLocation();
     while (true) {
         QString blockId = getLargestBlock(); // get the id of the largest block of cars
         if (blockId==("") || _numOfBlocks.value(blockId) == 1) {
             break; // done
         }
         RouteLocation* rld = getLocationWithMaximumMoves(*routeList, blockId); // get the location with the greatest
         // number of moves
         if (rld == NULL) {
             break; // done
         } // check to see if there are enough moves for all of the cars departing staging
         if (rld->getMaxCarMoves() > _numOfBlocks.value(blockId)) {
             // remove the largest block and maximum moves RouteLocation from the lists
             _numOfBlocks.remove(blockId);
             // block 0 cars have never left staging.
             if (blockId==("0")) {
                 continue;
             }
             routeList->removeOne(rld);
             Location* loc = locationManager->getLocationById(blockId);
             Location* setOutLoc = rld->getLocation();
             if (loc != NULL && setOutLoc != NULL && checkDropTrainDirection(rld)) {
                 for (_carIndex = 0; _carIndex < _carList->size(); _carIndex++) {
                     Car* car = _carList->at(_carIndex);
                     if (car->getTrack() == _departStageTrack && car->getLastLocationId()==(blockId)) {
                         if (car->getDestination() != NULL) {
                             addLine(_buildReport, SEVEN,
                                     tr("Not able to block car (%1), it has destination (%2)").arg(car->toString()).arg(
                                             car->getDestinationName()));
                             continue;
                         }
                         if (car->getFinalDestination() != NULL) {
                             addLine(_buildReport, SEVEN, tr("Not able to block car (%1), it has final destination (%2)").arg(car->toString()).arg(
                                     car->getFinalDestination()->getName()));
                             continue;
                         }
                         if (car->getLoadName()!=(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultEmptyName())
                                 && car->getLoadName()!=(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultLoadName())) {
                             addLine(_buildReport, SEVEN, tr("Not able to block car (%1), it has custom load (%2)").arg(car->toString()).arg(
                                     car->getLoadName()));
                             continue;
                         }
                         if (car->getLoadName()==(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultEmptyName())
                                 && (_departStageTrack->isAddCustomLoadsEnabled()
                                         || _departStageTrack->isAddCustomLoadsAnySpurEnabled() || _departStageTrack
                                             ->isAddCustomLoadsAnyStagingTrackEnabled())) {
                             addLine(_buildReport, SEVEN, tr("Not able to block car (%1) load (%2) generate custom loads enabled").arg(car->toString()).arg(
                                     car->getLoadName()));
                             continue;
                         }
                         addLine(_buildReport, SEVEN, tr("Blocking car (%1) originally from (%2) to destination (%3)").arg(
                                 car->toString()).arg( loc->getName()).arg( rld->getName()));
                         if (!findDestinationAndTrack(car, rl, rld)) {
                             addLine(_buildReport, SEVEN, tr("Not able to block car (%1) type (%3) to destination (%2)").arg(car->toString()).arg(
                                     rld->getName()).arg( car->getTypeName()));
                         }
                     }
                 }
             }
         } else {
             addLine(_buildReport, SEVEN, tr("Destination (%1) doesn't have enough moves for block %2").arg(
                     rl->getName()).arg( blockId));
             _numOfBlocks.remove(blockId); // block is too large for any stop along this train's route
         }
     }
 }

 /*private*/ QString TrainBuilder::getLargestBlock() {
     QStringListIterator en(_numOfBlocks.keys());
     QString largestBlock = "";
     int maxCars = 0;
     while (en.hasNext()) {
         QString locId = en.next();
         if (_numOfBlocks.value(locId) > maxCars) {
             largestBlock = locId;
             maxCars = _numOfBlocks.value(locId);
         }
     }
     return largestBlock;
 }

 /**
  * Returns the routeLocation with the most available moves.
  *
  * @param routeList The route for this train.
  * @param blockId Where these cars were originally picked up from.
  * @return The location in the route with the most available moves.
  */
 /*private*/ RouteLocation* TrainBuilder::getLocationWithMaximumMoves(QList<RouteLocation*> routeList, QString blockId) {
     RouteLocation* rlMax = NULL;
     int maxMoves = 0;
     foreach (RouteLocation* rl, routeList) {
         if (rl->getMaxCarMoves() - rl->getCarMoves() > maxMoves) {
             maxMoves = rl->getMaxCarMoves() - rl->getCarMoves();
             rlMax = rl;
         }
         // if two locations have the same number of moves, return the one that doesn't match the block id
         if (rl->getMaxCarMoves() - rl->getCarMoves() == maxMoves && rl->getLocation()->getId()!=(blockId)) {
             rlMax = rl;
         }
     }
     return rlMax;
 }


 /**
  * Main routine to place cars into the train. Can be called multiple times,
  * percent controls how many cars are placed in any given pass.
  */
 /*private*/ void TrainBuilder::placeCars(int percent, bool firstPass) //throws BuildFailedException
{
     addLine(_buildReport, THREE, BLANK_LINE); // add line when in normal report mode
     if (percent < 100) {
         addLine(_buildReport, THREE, tr("Multiple pass build (Aggressive Mode), begin pass %1% pick ups").arg(
                 percent));
         multipass = true;
     }
     if (percent == 100 && multipass) {
         addLine(_buildReport, THREE, tr("Multiple pass build (Aggressive Mode), begin final pass"));
     }
     // now go through each location starting at departure and place cars as requested
     for (int routeIndex = 0; routeIndex < _routeList->size(); routeIndex++) {
         RouteLocation* rl = _routeList->at(routeIndex);
         if (_train->skipsLocation(rl->getId())) {
             addLine(_buildReport, ONE, tr("Route location (%1) id (%2) is skipped by train (%3)").arg(
                     rl->getName()).arg(rl->getId()).arg(_train->getName()));
             continue;
         }
         if (!rl->isPickUpAllowed()) {
             addLine(_buildReport, ONE, tr("Route location (%3) id (%2) no pick ups").arg(
                     _train->getRoute()->getName()).arg(rl->getId()).arg(rl->getName()));
             continue;
         }
         // no pick ups from staging unless at the start of the train's route
         if (routeIndex > 0 && rl->getLocation()->isStaging()) {
             addLine(_buildReport, ONE, tr("No pick ups from staging (%1)").arg(
                     rl->getName()));
             continue;
         }
         // the next check provides a build report message if there's an issue with the train direction
         if (!checkPickUpTrainDirection(rl)) {
             continue;
         }
         _completedMoves = 0; // the number of moves completed for this location
         _success = true; // true when done with this location
         _reqNumOfMoves = (rl->getMaxCarMoves() - rl->getCarMoves()) * percent / 99; // the number of moves requested
         // round up requested moves if less than half way through build. Improves pickups when the move count is small.
         int remainder = (rl->getMaxCarMoves() - rl->getCarMoves()) % (100 / percent);
         if (percent < 51 && remainder > 0) {
             _reqNumOfMoves++;
         }
         int saveReqMoves = _reqNumOfMoves; // save a copy for status message
         // multiple pass build?
         if (firstPass) {
             // Departing staging?
             if (routeIndex == 0 && _departStageTrack != NULL) {
                 _reqNumOfMoves = 0; // Move cars out of staging after working other locations
                 // if leaving and returning to staging on the same track temporary pull cars off the track
                 if (_departStageTrack == _terminateStageTrack && !_train->isAllowReturnToStagingEnabled()
                         && !Setup::isAllowReturnToStagingEnabled()) {
                     foreach (RollingStock* rs, *carManager->getList()) {
                         // don't remove caboose or car with FRED already assigned to train
                         if (rs->getTrack() == _departStageTrack && rs->getRouteDestination() == NULL) {
                             rs->setLocation(rs->getLocation(), NULL); // takes care of cars in a kernel
                         }
                     }
                 }
                 addLine(_buildReport, THREE,
                         tr("Departing staging in aggressive mode, find destinations from (%1) in next pass").arg(_departStageTrack
                                 ->getLocation()->getName()));
             }
         } else if (routeIndex == 0 && _departStageTrack != NULL && _departStageTrack == _terminateStageTrack
                 && !_train->isAllowReturnToStagingEnabled() && !Setup::isAllowReturnToStagingEnabled()) {
             // restore departure track for cars departing staging
             foreach (Car* car, *_carList) {
                 if (car->getLocation() == _departStageTrack->getLocation() && car->getTrack() == NULL) {
                     car->setLocation(_departStageTrack->getLocation(), _departStageTrack, true); // force
                     if (car->getKernel() != NULL) {
                         foreach (Car* k, car->getKernel()->getCars()) {
                             k->setLocation(_departStageTrack->getLocation(), _departStageTrack, true); // force
                         }
                     }
                 }
             }
         }
         addLine(_buildReport, ONE, tr("Route location (%1) id (%2) requests %3 pick ups, %4/%5 moves are available").arg(
                 rl->getName()).arg(rl->getId()).arg(_reqNumOfMoves).arg(rl->getMaxCarMoves() - rl->getCarMoves(),
                 rl->getMaxCarMoves()));
         addLine(_buildReport, FIVE, BLANK_LINE); // add line when in detailed report mode
         _carIndex = 0; // see reportCarsNotMoved(rl, percent) below

         if (routeIndex == 0
                 && _departStageTrack != NULL
                 && _reqNumOfMoves > 0
                 && (_departStageTrack->isAddCustomLoadsEnabled()
                         || _departStageTrack->isAddCustomLoadsAnySpurEnabled() || _departStageTrack
                             ->isAddCustomLoadsAnyStagingTrackEnabled())) {
             addLine(_buildReport, FIVE, tr("Staging track (%1) has the following options selected:").arg(
                     _departStageTrack->getName()));
             if (_departStageTrack->isAddCustomLoadsEnabled()) {
                 addLine(_buildReport, FIVE, tr("Generate custom loads for spurs serviced by this train"));
             }
             if (_departStageTrack->isAddCustomLoadsAnySpurEnabled()) {
                 addLine(_buildReport, FIVE, tr("Generate custom loads for any spur (multiple trains)"));
             }
             if (_departStageTrack->isAddCustomLoadsAnyStagingTrackEnabled()) {
                 addLine(_buildReport, FIVE, tr("Generate custom loads for any staging track"));
             }
             addLine(_buildReport, FIVE, BLANK_LINE); // add line when in detailed report mode
         }

         findDestinationsForCarsFromLocation(rl, routeIndex, false);
         // perform a another pass if aggressive and there are requested moves
         // this will perform local moves at this location, services off spot tracks
         // only in aggressive mode, and at least one car has a new destination
         if (Setup::isBuildAggressive() && saveReqMoves != _reqNumOfMoves) {
            log->debug(tr("Perform extra pass at location (%1)").arg(rl->getName()));
             // use up to half of the available moves left for this location
             if (_reqNumOfMoves < (rl->getMaxCarMoves() - rl->getCarMoves()) * percent / 200) {
                 _reqNumOfMoves = (rl->getMaxCarMoves() - rl->getCarMoves()) * percent / 200;
             }
             findDestinationsForCarsFromLocation(rl, routeIndex, true);
         }

         // we might have freed up space at a spur that has an alternate track
         if (redirectCarsFromAlternateTrack()) {
             addLine(_buildReport, SEVEN, BLANK_LINE); // add line when in very detailed report mode
         }
         if (routeIndex == 0) {
             checkDepartureForStaging(percent); // report ASAP that the build has failed
         }
         addLine(_buildReport, ONE, tr("%1 %2/%3 cars at location (%4) assigned to train (%5)").arg(
                         (saveReqMoves <= _completedMoves ? tr("Success") : tr("Partial"))).arg((_completedMoves)).arg
                         (saveReqMoves).arg(rl->getName()).arg(_train->getName()));

         reportCarsNotMoved(rl, percent);
     }
     checkDepartureForStaging(percent); // covers the cases: no pick ups, wrong train direction and train skips,
 }

 /**
  * Attempts to find a destinations for cars departing a specific route
  * location.
  *
  * @param rl The route location.
  * @param routeIndex Where in the route to add cars to this train.
  * @param isSecondPass When true this is the second time we've looked at
  *            these cars.
  * @throws BuildFailedException
  */
 /*private*/ void TrainBuilder::findDestinationsForCarsFromLocation(RouteLocation* rl, int routeIndex, bool isSecondPass)
         //throws BuildFailedException
 {
     if (_reqNumOfMoves <= 0) {
         return;
     }
     bool messageFlag = true;
     _success = false;
     for (_carIndex = 0; _carIndex < _carList->size(); _carIndex++) {
         Car* car = _carList->at(_carIndex);
         // second pass only cares about cars that have a /*final*/ destination equal to this location
         if (isSecondPass && car->getFinalDestinationName()!=(rl->getName())) {
             continue;
         }
         // find a car at this location
         if (car->getLocationName()!=(rl->getName())) {
             continue;
         }
         // add message that we're on the second pass for this location
         if (isSecondPass && messageFlag) {
             messageFlag = false;
             addLine(_buildReport, FIVE, tr("Extra pass for location (%1) only local moves").arg(
                     rl->getName()));
             addLine(_buildReport, SEVEN, BLANK_LINE); // add line when in very detailed report mode
         }
         // can this car be picked up?
         if (!checkPickUpTrainDirection(car, rl)) {
             addLine(_buildReport, FIVE, BLANK_LINE); // add line when in detailed report mode
             continue; // no
         }

         // check for car order?
         car = getCarOrder(car);

         // is car departing staging and generate custom load?
         if (!generateCarLoadFromStaging(car)) {
             if (generateCarLoadStagingToStaging(car) && car->getTrack() != _departStageTrack
                     && !_departStageTrack->shipsLoad(car->getLoadName(), car->getTypeName())) {
                 // report build failure car departing staging with a restricted load
                 addLine(_buildReport, ONE, tr("BUILD FAILED car (%1) departing staging with a load (%2) that is restricted by track (%3)").arg(
                         car->toString()).arg(car->getLoadName()).arg(_departStageTrack->getName()));
                 addLine(_buildReport, FIVE, BLANK_LINE); // add line when in detailed report mode
                 continue; // keep going and see if there are other cars with issues outs of staging
             }
         }
         // does car have a custom load without a destination?
         // If departing staging, a destination for this car is needed, so keep going
         if (findFinalDestinationForCarLoad(car) && car->getDestination() == NULL
                 && car->getTrack() != _departStageTrack) {
             // done with this car, it has a custom load, and there are spurs/schedules, but no destination found
             checkCarOrder(car);
             continue;
         }
         // does car have a /*final*/ destination, but no destination
         if (car->getFinalDestination() != NULL && car->getDestination() == NULL) {
             // no local moves for this train?
             if (!_train->isAllowLocalMovesEnabled()
                     && splitString(car->getLocationName())==(splitString(car->getFinalDestinationName()))
                     && car->getTrack() != _departStageTrack) {
                 addLine(_buildReport, FIVE, tr("Car (%1) final destination (%2) equal to car's location, local move is not allowed for this train").arg(
                         car->toString()).arg(car->getFinalDestinationName()));
                 addLine(_buildReport, FIVE, BLANK_LINE); // add line when in detailed report mode
                log->debug(tr("Removing car (%1) from list").arg(car->toString()));
                 _carList->removeOne(car);
                 _carIndex--;
                 continue;
             }
             // no through traffic from origin to terminal?
             if (!_train->isAllowThroughCarsEnabled() && !_train->isLocalSwitcher() && !car->isCaboose()
                     && !car->hasFred() && !car->isPassenger()
                     && splitString(car->getLocationName())==(splitString(_departLocation->getName()))
                     && splitString(car->getFinalDestinationName())==(splitString(_terminateLocation->getName()))
                     && splitString(car->getLocationName())!=(splitString(car->getFinalDestinationName()))) {
                 addLine(_buildReport, FIVE, tr("Car (%1) at location (%2) has final destination (%3)").arg(
                         car->toString()).arg(car->getLocationName()).arg(car->getFinalDestinationName()));
                 addLine(_buildReport, FIVE, tr("Through traffic not allowed from (%1) to terminal (%2)").arg(
                         _departLocation->getName()).arg(_terminateLocation->getName()));
                 // don't remove car from list if departing staging
                 if (car->getTrack() == _departStageTrack) {
                     addLine(_buildReport, ONE, tr("BUILD FAILED Car (%1) departing staging with a destination that can not be serviced").arg(
                             car->toString()));
                 } else {
                    log->debug(tr("Removing car (%1) from list").arg(car->toString()));
                     _carList->removeOne(car);
                     _carIndex--;
                 }
                 addLine(_buildReport, FIVE, BLANK_LINE); // add line when in detailed report mode
                 continue;
             }
             addLine(_buildReport, FIVE, tr("Car (%1) type (%2) load (%3) at (%4, %5) has final destination (%6, %7) routing begins").arg(car->toString(),
                             car->getTypeName()).arg(car->getLoadName()).arg(car->getLocationName()).arg(car->getTrackName()).arg(
                             car->getFinalDestinationName()).arg(car->getFinalDestinationTrackName()));
             // does the car have a /*final*/ destination track that is willing to service the car?
             // note the default mode for all track types is MATCH
             if (car->getFinalDestinationTrack() != NULL &&
                     car->getFinalDestinationTrack()->getScheduleMode() == Track::MATCH) {
                 QString status = car->testDestination(car->getFinalDestination(), car->getFinalDestinationTrack());
                 // keep going if the issue was track length and the track accepts the car's load
                 if (status!=(Track::OKAY) && !status.startsWith(Track::LENGTH)
                         && !(status.contains(Track::CUSTOM) && status.contains(Track::LOAD))) {
                     addLine(_buildReport, SEVEN, tr("buildNoDestTrackNewLoad").arg(
                             car->getFinalDestination()->getName()).arg(
                                     car->getFinalDestinationTrack()->getName()).arg(car->toString()).arg(car->getLoadName()).arg(
                                     status));
                     // is this car or kernel being sent to a track that is too short?
                     if (status.startsWith(Track::CAPACITY)) {
                         addLine(_buildReport, SEVEN, tr("Track (%1) is too short for car (%2), removing final destination (%3, %4)").arg(
                                 car->getFinalDestinationTrack()->getName()).arg(car->toString()).arg(
                                 car->getFinalDestination()->getName()).arg(car->getFinalDestinationTrack()->getName()));
                         car->setFinalDestination(NULL); // track is too short for this kernel, can never go there
                         car->setFinalDestinationTrack(NULL);
                     } else if (car->getTrack() == _departStageTrack) {
                         addLine(_buildReport, ONE,
                                 tr("BUILD FAILED Car (%1) departing staging with a destination that can not be serviced").arg(car->toString()));
                     } else {
                        log->debug(tr("Removing car (%1) from list").arg(car->toString()));
                         _carList->removeOne(car);
                         _carIndex--;
                     }
                     addLine(_buildReport, FIVE, BLANK_LINE); // add line when in detailed report mode
                     continue;
                 }
             }
             if (!Router::instance()->setDestination(car, _train, _buildReport)) {
                 addLine(_buildReport, SEVEN,
                         tr("Not able to set destination for car (%1) due to %2").arg(car->toString()).arg(
                                 Router::instance()->getStatus()));
                 // don't move car if routing issue was track space but not departing staging
                 if ((!Router::instance()->getStatus().startsWith(Track::LENGTH) && !_train->isServiceAllCarsWithFinalDestinationsEnabled())
                         ||
                         (car->getTrack() == _departStageTrack)) {
                     // add car to not able to route list
                     if (!_notRoutable.contains(car)) {
                         _notRoutable.append(car);
                     }
                     addLine(_buildReport, FIVE, BLANK_LINE); // add line when in detailed report mode
                     addLine(_buildReport, FIVE,
                             tr("buildWarningCarNotRoutable").arg(car->toString(), car->getLocationName()).arg(
                                 car->getTrackName()).arg(car->getFinalDestinationName()).arg(car->getFinalDestinationTrackName()));
                     addLine(_buildReport, FIVE, BLANK_LINE); // add line when in detailed report mode
                     // move this car, routing failed!
                     findDestinationAndTrack(car, rl, routeIndex, _routeList->size());
                     continue;
                 } else {
                     checkCarOrder(car);
                     continue;
                 }
             } else {
                 // did the router assign a destination?
                 if (!checkCarForDestinationAndTrack(car, rl, routeIndex) && car->getTrack() != _departStageTrack) {
                    log->debug(tr("Skipping car (%1) no car destination").arg(car->toString())); // NOI18N
                     checkCarOrder(car);
                     continue;
                 } else {
                     // if departing staging try and find a destination for this car
                     if (car->getDestination() == NULL &&
                             car->getTrack() == _departStageTrack &&
                             _terminateStageTrack != NULL) {
                        log->debug(tr("Car (%1) departing staging with final destination (%2) but no destination, try staging").arg( // NOI18N
                                 car->toString()).arg(car->getFinalDestinationName()));
                         findDestinationAndTrack(car, rl, _train->getTrainTerminatesRouteLocation());
                     }
                 }
             }
             // does car have a destination?
         } else if (checkCarForDestinationAndTrack(car, rl, routeIndex)) {
             // car does not have a destination, search for the best one
         } else {
             findDestinationAndTrack(car, rl, routeIndex, _routeList->size());
         }
         if (_success) {
             //log->debug("done with location ("+destinationSave->getName()+")");
             break;
         }
         // build failure if car departing staging without a destination and a train
         // we'll just put out a warning message here so we can find out how many cars have issues
         if (car->getTrack() == _departStageTrack
                 && (car->getDestination() == NULL || car->getDestinationTrack() == NULL || car->getTrain() == NULL)) {
             addLine(_buildReport, ONE, tr("Warning car (%1) departing staging without a destination").arg(
                     car->toString()));
             // does the car has a /*final*/ destination track going into staging? If so we need to reset this car
             if (car->getFinalDestinationTrack() != NULL && car->getFinalDestinationTrack() == _terminateStageTrack) {
                 addLine(_buildReport, THREE, tr("Car (%1) has a final destination of staging (%2, %3), restoring car''s final destination and load").arg(
                         car->toString()).arg(car->getFinalDestinationName()).arg(
                                 car->getFinalDestinationTrackName()));
                 car->reset();
             }
             addLine(_buildReport, SEVEN, BLANK_LINE); // add line when in very detailed report mode
         }
     }
 }

 /**
  * Checks to see if all cars on a staging track have been given a
  * destination. Throws exception if there's a car without a destination.
  */
 /*private*/ void TrainBuilder::checkDepartureForStaging(int percent) //throws BuildFailedException
 {
     if (percent != 100 || _departStageTrack == NULL) {
         return; // only check departure track after last pass is complete
     }
     int carCount = 0;
     QString buf = "";//new StringBuffer();
     // confirm that all cars in staging are departing
     foreach (Car* car, *_carList) {
         // build failur*e if car departing staging without a destination and a train
         if (car->getTrack() == _departStageTrack
                 && (car->getDestination() == NULL || car->getDestinationTrack() == NULL || car->getTrain() == NULL)) {
             if (car->getKernel() != NULL) {
                 foreach (Car* c, car->getKernel()->getCars()) {
                     carCount++;
                     if (carCount < 21) {
                         buf.append(NEW_LINE + " " + c->toString());
                     }
                 }
             } else {
                 carCount++;
                 if (carCount < 21) {
                     buf.append(NEW_LINE + " " + car->toString());
                 }
             }
         }
     }
     if (carCount > 0) {
        log->debug(tr("%1 cars stuck in staging").arg(carCount));
         QString msg = tr("BUILD FAILED could not find destinations for %1 car(s) departing from staging track (%2, %3)").arg(
                 carCount).arg(_departStageTrack->getLocation()->getName()).arg(_departStageTrack->getName());
         throw BuildFailedException(msg + buf/*.toString()*/, /*BuildFailedException::STAGING*/"Staging");
     }
 }

 /**
  *
  * @param engine
  * @param rl where in the train's route to pick up the engine
  * @param rld where in the train's route to set out the engine
  * @param track destination track for this engine
  */
 /*private*/ void TrainBuilder::addEngineToTrain(Engine* engine, RouteLocation* rl, RouteLocation* rld, Track* track) {
     _leadEngine = engine; // needed in case there's a engine change in the train's route
     if (_train->getLeadEngine() == NULL) {
         _train->setLeadEngine(engine); // load lead engine
     }
     addLine(_buildReport, ONE, tr("Loco (%1) assigned to train, destination (%2, %3)").arg(
             engine->toString()).arg(rld->getName()).arg(track->getName()));
     engine->setDestination(track->getLocation(), track);
     int length = engine->getTotalLength();
     int weightTons = engine->getAdjustedWeightTons();
     // engine in consist?
     if (engine->getConsist() != NULL) {
         length = engine->getConsist()->getTotalLength();
         weightTons = engine->getConsist()->getAdjustedWeightTons();
         foreach (Engine* cEngine, engine->getConsist()->getEngines()) {
             if (cEngine == engine) {
                 continue;
             }
             addLine(_buildReport, ONE, tr("Loco (%1) assigned to train, destination (%2, %3)").arg(
                     cEngine->toString()).arg(rld->getName()).arg(track->getName()));
             cEngine->setTrain(_train);
             cEngine->setRouteLocation(rl);
             cEngine->setRouteDestination(rld);
             cEngine->setDestination(track->getLocation(), track, true); // force destination
         }
     }
     // now adjust train length and weight for each location that engines are in the train
     addRsToTrain(engine, rl, rld, track, length, weightTons);
 }

 /**
  * Add car to train
  *
  * @param car The car!
  * @param rl the planned origin for this car
  * @param rld the planned destination for this car
  * @param track the final destination for car
  * @return true if car was successfully added to train. Also makes the
  *         bool "success" true if location doesn't need any more pick
  *         ups.
  */
 /*private*/ void TrainBuilder::addCarToTrain(Car* car, RouteLocation* rl, RouteLocation* rld, Track* track) {
     addLine(_buildReport, THREE, tr("buildCarAsCar (%1) assigned to train, destination (%2, %3)signedDest").arg(car->toString(), rld->getName(), track->getName()));
     car->setDestination(track->getLocation(), track);
     int length = car->getTotalLength();
     int weightTons = car->getAdjustedWeightTons();
     // car could be part of a kernel
     if (car->getKernel() != NULL) {
         length = car->getKernel()->getTotalLength(); // includes couplers
         weightTons = car->getKernel()->getAdjustedWeightTons();
         QList<Car*> kCars = car->getKernel()->getCars();
         addLine(_buildReport, THREE, tr("Car (%1) is in kernel (%2) with %3 cars, %4 %5").arg(car->toString()).arg(car->getKernelName()).arg(kCars.size()).arg(car->getKernel()->getTotalLength()).arg(Setup::getLengthUnit().toLower()));
         foreach (Car* kCar, kCars) {
             if (kCar == car) {
                 continue;
             }
             addLine(_buildReport, THREE, tr("Car (%1) kernel (%2) assigned to train, destination (%3, %4)").arg(
                     kCar->toString()).arg(kCar->getKernelName()).arg(rld->getName()).arg(track->getName()));
             kCar->setTrain(_train);
             kCar->setRouteLocation(rl);
             kCar->setRouteDestination(rld);
             kCar->setDestination(track->getLocation(), track, true); // force destination
             // save /*final*/ destination and track values in case of train reset
             kCar->setPreviousFinalDestination(car->getPreviousFinalDestination());
             kCar->setPreviousFinalDestinationTrack(car->getPreviousFinalDestinationTrack());
         }
         car->updateKernel();
     }
     // warn if car's load wasn't generated out of staging
     if (!_train->acceptsLoad(car->getLoadName(), car->getTypeName())) {
         addLine(_buildReport, SEVEN, tr("Warning car (%1) load (%2) not serviced by train!").arg(
                 car->toString()).arg(car->getLoadName()));
     }
     addLine(_buildReport, THREE, BLANK_LINE); // add line when in normal report mode
     _numberCars++; // bump number of cars moved by this train
     _completedMoves++; // bump number of car pick up moves for the location
     _reqNumOfMoves--; // decrement number of moves left for the location
     if (_reqNumOfMoves <= 0) {
         _success = true; // done with this location!
     }
     _carList->removeOne(car);
     _carIndex--; // removed car from list, so backup pointer

     rl->setCarMoves(rl->getCarMoves() + 1);
     if (rl != rld) {
         rld->setCarMoves(rld->getCarMoves() + 1);
     }
     // now adjust train length and weight for each location that car is in the train
     addRsToTrain(car, rl, rld, track, length, weightTons);
     return;
 }

 /*private*/ void TrainBuilder::addRsToTrain(RollingStock* rs, RouteLocation* rl, RouteLocation* rld, Track* track, int length,
         int weightTons) {
     rl->getLocation()->setStatusModified();
     rld->getLocation()->setStatusModified();
     rs->setTrain(_train);
     rs->setRouteLocation(rl);
     rs->setRouteDestination(rld);
     // now adjust train length and weight for each location that the rolling stock is in the train
     bool inTrain = false;
     foreach (RouteLocation* r, *_routeList) {
         if (rl == r) {
             inTrain = true;
         }
         if (rld == r) {
             break;
         }
         if (inTrain) {
             r->setTrainLength(r->getTrainLength() + length); // couplers are included
             r->setTrainWeight(r->getTrainWeight() + weightTons);
         }
     }
 }

 /*private*/ bool TrainBuilder::checkPickUpTrainDirection(RollingStock* rs, RouteLocation* rl) {
     // check that car or engine is located on a track
     if (rs->getTrack() == NULL) {
         addLine(_buildReport, ONE, tr("ERROR Exclude rs (%1) at location (%2) no track assignment").arg(
                 rs->toString()).arg(rs->getLocationName()));
         return false;
     }
     if (_train->isLocalSwitcher()) // ignore local switcher direction
     {
         return true;
     }
     if ((rl->getTrainDirection() & rs->getLocation()->getTrainDirections() & rs->getTrack()->getTrainDirections()) > 0) {
         return true;
     }

     // Only track direction can cause the following message. Location direction has already been checked
     addLine(_buildReport, FIVE, tr("Can't pick up (%1) using %2bound train, track (%3)").arg(
             rs->toString()).arg(rl->getTrainDirectionString()).arg(rs->getTrackName()));
     addLine(_buildReport, FIVE, tr("at location (%1) does not service this train''s direction").arg(
             rs->getLocationName()));
     return false;
 }

 /*private*/ bool TrainBuilder::checkPickUpTrainDirection(RouteLocation* rl) {
     if (_train->isLocalSwitcher()) // ignore local switcher direction
     {
         return true;
     }
     if ((rl->getTrainDirection() & rl->getLocation()->getTrainDirections()) > 0) {
         return true;
     }

     addLine(_buildReport, ONE, tr("Location (%1) can not be serviced by %2bound train").arg(
             rl->getName(), rl->getTrainDirectionString()));
     return false;
 }

 /**
  * Checks to see if train length would be exceeded if this car was added to
  * the train.
  *
  * @param car the car
  * @param rl the planned origin for this car
  * @param rld the planned destination for this car
  * @return true if car can be added to train
  */
 /*private*/ bool TrainBuilder::checkTrainLength(Car* car, RouteLocation* rl, RouteLocation* rld) {
     // car can be a kernel so get total length
     int length = car->getTotalLength();
     if (car->getKernel() != NULL) {
         length = car->getKernel()->getTotalLength();
     }
     bool carInTrain = false;
     foreach (RouteLocation* rlt, *_routeList) {
         if (rl == rlt) {
             carInTrain = true;
         }
         if (rld == rlt) {
             break;
         }
         if (carInTrain && rlt->getTrainLength() + length > rlt->getMaxTrainLength()) {
             addLine(_buildReport, FIVE, tr("Can't pick up (%1) length (%2) %3 using this route, it would exceed train''s").arg(
                     car->toString()).arg(length).arg(Setup::getLengthUnit().toLower()));
             addLine(_buildReport, FIVE, tr("maximum length (%1) %2 by %3 %2 when departing (%4) route id (%5)").arg(
                     rlt->getMaxTrainLength()).arg(Setup::getLengthUnit().toLower()).arg(
                             rlt->getTrainLength() + length - rlt->getMaxTrainLength()).arg(
                             rlt->getName()).arg(rlt->getId()));
             return false;
         }
     }
     return true;
 }


 /*private*/ bool TrainBuilder::checkDropTrainDirection(RollingStock* rs, RouteLocation* rld, Track* track) {
     // local?
     if (_train->isLocalSwitcher()) {
         return true;
     }
     // is the destination the last location on the route?
     if (ignoreTrainDirectionIfLastLoc && rld == _train->getTrainTerminatesRouteLocation()) {
         return true; // yes, ignore train direction
     }
     // this location only services trains with these directions
     int serviceTrainDir = rld->getLocation()->getTrainDirections();
     if (track != NULL) {
         serviceTrainDir = serviceTrainDir & track->getTrainDirections();
     }

     // is this a car going to alternate track? Check to see if direct move from alternate to FD track is possible
     if ((rld->getTrainDirection() & serviceTrainDir) > 0 && rs != NULL && track != NULL
             && (track->getTrainDirections() & serviceTrainDir) > 0 && qobject_cast<Car*>(rs)!= NULL) {
         Car* car = (Car*) rs;
         if (car->getFinalDestinationTrack() != NULL && track == car->getFinalDestinationTrack()->getAlternateTrack()
                 && (track->getTrainDirections() & car->getFinalDestinationTrack()->getTrainDirections()) == 0) {
             addLine(_buildReport, SEVEN, tr("Can't set out rolling stock (%1) using %2bound train,").arg(
                     rs->toString()).arg(rld->getTrainDirectionString()));
             addLine(_buildReport, SEVEN, tr("final destination track (%1) train direction (%2) and alternate track (%3) train direction (%4) aren''t compatible").arg(
                              car->getFinalDestinationTrack()->getName()).arg(
                             formatStringToCommaSeparated(Setup::getDirectionStrings(car->getFinalDestinationTrack()
                                     ->getTrainDirections()))).arg(
                             car->getFinalDestinationTrack()->getAlternateTrack()->getName()).arg(
                             formatStringToCommaSeparated(Setup::getDirectionStrings(car->getFinalDestinationTrack()
                                     ->getAlternateTrack()->getTrainDirections()))));
             return false;
         }
     }

     if ((rld->getTrainDirection() & serviceTrainDir) > 0) {
         return true;
     }
     if (rs == NULL) {
         addLine(_buildReport, SEVEN, tr("Destination (%1) does not service %2bound trains").arg(
                 rld->getName()).arg(rld->getTrainDirectionString()));
         return false;
     }
     addLine(_buildReport, SEVEN, tr("Can't set out rolling stock (%1) using %2bound train,").arg(
             rs->toString()).arg(rld->getTrainDirectionString()));
     if (track != NULL) {
         addLine(_buildReport, SEVEN, tr("destination track (%1) does not service this direction").arg(
                 track->getName()));
     } else {
         addLine(_buildReport, SEVEN, tr("destination (%1) does not service this direction").arg(
                 rld->getName()));
     }
     return false;
 }

 /*private*/ bool TrainBuilder::checkDropTrainDirection(RouteLocation* rld) {
     return (checkDropTrainDirection(NULL, rld, NULL));
 }

 /**
  * Determinate if car can be dropped by this train to the track specified.
  *
  * @param car the car.
  * @param track the destination track.
  * @return true if able to drop.
  */
 /*private*/ bool TrainBuilder::checkTrainCanDrop(Car* car, Track* track) {
     if (track->getTrackType()==(Track::INTERCHANGE) || track->getTrackType()==(Track::SPUR)) {
         if (track->getDropOption()==(Track::TRAINS) || track->getDropOption()==(Track::EXCLUDE_TRAINS)) {
             if (track->acceptsDropTrain(_train)) {
                log->debug(tr("Car (%1) can be dropped by train to track (%2)").arg(car->toString()).arg(track->getName()));
             } else {
                 addLine(_buildReport, SEVEN, tr("Can't set out (%1) by train (%2) to %3 (%4)").arg(car->toString()).arg(
                                 _train->getName()).arg(track->getTrackTypeName()).arg(track->getName()));
                 return false;
             }
         }
         if (track->getDropOption()==(Track::ROUTES) || track->getDropOption()==(Track::EXCLUDE_ROUTES)) {
             if (track->acceptsDropRoute(_train->getRoute())) {
                log->debug(tr("Car (%1) can be dropped by route to track (%2)").arg(car->toString()).arg(track->getName()));
             } else {
                 addLine(_buildReport, SEVEN, tr("Can't set out (%1) by route (%2) to %3 (%4)").arg(
                         car->toString()).arg(_train->getRoute()->getName()).arg(track->getTrackTypeName()).arg(
                                 track->getName()));
                 return false;
             }
         }
     }
     return true;
 }

 /**
  * Check departure staging track to see if engines and cars are available to
  * a new train. Also confirms that the engine and car type, load, road, etc.
  * are accepted by the train.
  *
  * @return true is there are engines and cars available.
  */
 /*private*/ bool TrainBuilder::checkDepartureStagingTrack(Track* departStageTrack) {
     // does this staging track service this train?
     if (!departStageTrack->acceptsPickupTrain(_train)) {
         addLine(_buildReport, THREE, tr("Staging track (%1) does not service this train").arg(
                 departStageTrack->getName()));
         return false;
     }
     if (departStageTrack->getNumberRS() == 0 && _train->getTrainDepartsRouteLocation()->getMaxCarMoves() > 0) {
         addLine(_buildReport, THREE, tr("Staging track (%1) is empty").arg(
                 departStageTrack->getName()));
         return false;
     }
     if (departStageTrack->getUsedLength() > _train->getTrainDepartsRouteLocation()->getMaxTrainLength()) {
         addLine(_buildReport, THREE, tr("Train on staging track (%1) is %2 %3 long and exceeds the route''s maximum departure length %4 %3").arg(
                 departStageTrack->getName()).arg(departStageTrack->getUsedLength()).arg(
                         Setup::getLengthUnit().toLower()).arg(
                         _train->getTrainDepartsRouteLocation()->getMaxTrainLength()));
         return false;
     }
     if (departStageTrack->getNumberCars() > _train->getTrainDepartsRouteLocation()->getMaxCarMoves()) {
         addLine(_buildReport, THREE, tr("Staging track (%1) has more cars (%2) than requested by train''s route (%3)").arg(
                 departStageTrack->getName()).arg(departStageTrack->getNumberCars()).arg(
                         _train->getTrainDepartsRouteLocation()->getMaxCarMoves()));
         return false;
     }
     // does the staging track have the right number of locomotives?
     if (_reqNumEngines > 0 && _reqNumEngines != departStageTrack->getNumberEngines()) {
         addLine(_buildReport, THREE, tr("Staging track (%1) does not have the required number of locomotives").arg(
                 departStageTrack->getName()));
         return false;
     }
     // is the staging track direction correct for this train?
     if ((departStageTrack->getTrainDirections() & _train->getTrainDepartsRouteLocation()->getTrainDirection()) == 0) {
         addLine(_buildReport, THREE, tr("Staging track (%1) does not service this train''s direction").arg(
                 departStageTrack->getName()));
         return false;
     }

     if (departStageTrack->getNumberEngines() > 0) {
         foreach (RollingStock* rs, *engineManager->getList()) {
             Engine* eng = (Engine*) rs;
             if (eng->getTrack() == departStageTrack) {
                 // has engine been assigned to another train?
                 if (eng->getRouteLocation() != NULL) {
                     addLine(_buildReport, THREE, tr("Staging track ({%1) is already assigned to train (%2)").arg(
                             departStageTrack->getName()).arg(eng->getTrainName()));
                     return false;
                 }
                 // does the train accept the engine type from the staging track?
                 if (!_train->acceptsTypeName(eng->getTypeName())) {
                     addLine(_buildReport, THREE, tr("Staging track (%1) has an loco (%2) type (%3) that is not serviced by train (%4)").arg(departStageTrack->getName(),
                             eng->toString()).arg(eng->getTypeName()).arg(_train->getName()));
                     return false;
                 }
                 // does the train accept the engine model from the staging track?
                 if (_train->getEngineModel()!=(Train::NONE) && _train->getEngineModel()!=(eng->getModel())) {
                     addLine(_buildReport, THREE, tr("Staging track (%1) has an loco (%2) model (%3) that doesn''t meet train (%4) requirements").arg(
                             departStageTrack->getName()).arg(eng->toString()).arg(eng->getModel()).arg(_train->getName()));
                     return false;
                 }
                 // does the engine road match the train requirements?
                 if (_train->getRoadOption()!=(Train::ALL_LOADS) && _train->getEngineRoad()!=(Train::NONE)
                         && _train->getEngineRoad()!=(eng->getRoadName())) {
                     addLine(_buildReport, THREE, tr("Staging track (%1) has an loco (%2) road (%3) that is not serviced by train (%4)").arg(departStageTrack->getName(),
                             eng->toString()).arg(eng->getRoadName()).arg(_train->getName()));
                     return false;
                 }
                 // does the train accept the engine road from the staging track?
                 if (_train->getEngineRoad()==(Train::NONE) && !_train->acceptsRoadName(eng->getRoadName())) {
                     addLine(_buildReport, THREE, tr("Staging track (%1) has an loco (%2) road (%3) that is not serviced by train (%4)").arg(departStageTrack->getName(),
                             eng->toString()).arg(eng->getRoadName()).arg(_train->getName()));
                     return false;
                 }
                 // does the train accept the engine owner from the staging track?
                 if (!_train->acceptsOwnerName(eng->getOwner())) {
                     addLine(_buildReport, THREE, tr("Staging track (%1) has an loco (%2) owner (%3) that is not serviced by train (%4)").arg(
                             departStageTrack->getName()).arg(eng->toString()).arg(eng->getOwner()).arg(_train->getName()));
                     return false;
                 }
                 // does the train accept the engine built date from the staging track?
                 if (!_train->acceptsBuiltDate(eng->getBuilt())) {
                     addLine(_buildReport, THREE, tr("buildStagingDepartEngineBuilt").arg(
                             departStageTrack->getName(), eng->toString(), eng->getBuilt(), _train->getName()));
                     return false;
                 }
             }
         }
     }
     bool foundCaboose = false;
     bool foundFRED = false;
     if (departStageTrack->getNumberCars() > 0) {
         foreach (RollingStock* rs, *carManager->getList()) {
             Car* car = (Car*) rs;
             if (car->getTrack() != departStageTrack) {
                 continue;
             }
             // ignore non-lead cars in kernels
             if (car->getKernel() != NULL && !car->getKernel()->isLead(car)) {
                 continue; // ignore non-lead cars
             }
             // has car been assigned to another train?
             if (car->getRouteLocation() != NULL) {
                log->debug(tr("Car (%1) has route location (%2").arg(car->toString()).arg(car->getRouteLocation()->getName()));
                 addLine(_buildReport, THREE, tr("Staging track (%1) is already assigned to train (%2)").arg(
                         departStageTrack->getName()).arg(car->getTrainName()));
                 return false;
             }
             // does the train accept the car type from the staging track?
             if (!_train->acceptsTypeName(car->getTypeName())) {
                 addLine(_buildReport, THREE, tr("Staging track (%1) has a car (%2) type (%3) that is not serviced by train (%4)").arg(
                         departStageTrack->getName()).arg(car->toString()).arg(car->getTypeName()).arg(
                                 _train->getName()));
                 return false;
             }
             // does the train accept the car road from the staging track?
             if (!_train->acceptsRoadName(car->getRoadName())) {
                 addLine(_buildReport, THREE, tr("Staging track (%1) has a car (%2) road (%3) that is not serviced by train (%4)").arg(
                         departStageTrack->getName()).arg(car->toString()).arg(car->getRoadName(),
                                 _train->getName()));
                 return false;
             }
             // does the train accept the car load from the staging track?
             if (!car->isCaboose()
                     && !car->isPassenger()
                     && (car->getLoadName()!=(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultEmptyName()) || !departStageTrack
                             ->isAddCustomLoadsEnabled()
                             && !departStageTrack->isAddCustomLoadsAnySpurEnabled()
                             && !departStageTrack->isAddCustomLoadsAnyStagingTrackEnabled())
                     && !_train->acceptsLoad(car->getLoadName(), car->getTypeName())) {
                 addLine(_buildReport, THREE, tr("Staging track (%1) has a car (%2) load (%3) that is not serviced by train (%4)").arg(
                         departStageTrack->getName()).arg(car->toString()).arg(car->getLoadName()).arg(
                                 _train->getName()));
                 return false;
             }
             // does the train accept the car owner from the staging track?
             if (!_train->acceptsOwnerName(car->getOwner())) {
                 addLine(_buildReport, THREE, tr("Staging track (%1) has a car (%2) owner (%3) that is not serviced by train (%4)").arg(
                                 departStageTrack->getName()).arg(car->toString()).arg(car->getOwner()).arg(_train->getName()));
                 return false;
             }
             // does the train accept the car built date from the staging track?
             if (!_train->acceptsBuiltDate(car->getBuilt())) {
                 addLine(_buildReport, THREE, tr("Staging track (%1) has a car (%2) built (%3) that is not serviced by train (%4)").arg(
                                 departStageTrack->getName()).arg(car->toString()).arg(car->getBuilt()).arg(_train->getName()));
                 return false;
             }
             // does the car have a destination serviced by this train?
             if (car->getDestination() != NULL) {
                log->debug(tr("Car (%1) has a destination (%2, %3)").arg(car->toString()).arg(car->getDestinationName()).arg(car
                         ->getDestinationTrackName()));
                 if (!_train->services(car)) {
                     addLine(_buildReport, THREE, tr("Staging track (%1) has a car (%2) destination (%3) that can not be serviced by train (%4)").arg(
                             departStageTrack->getName()).arg(car->toString()).arg(car->getDestinationName()).arg(
                                     _train->getName()));
                     return false;
                 }
             }
             // is this car a caboose with the correct road for this train?
             if (car->isCaboose()
                     &&
                     (_train->getCabooseRoad()==(Train::NONE) || _train->getCabooseRoad()==(car->getRoadName()))) {
                 foundCaboose = true;
             }
             // is this car have a FRED with the correct road for this train?
             if (car->hasFred()
                     &&
                     (_train->getCabooseRoad()==(Train::NONE) || _train->getCabooseRoad()==(car->getRoadName()))) {
                 foundFRED = true;
             }
         }
     }
     // does the train require a caboose and did we find one from staging?
     if ((_train->getRequirements() & Train::CABOOSE) == Train::CABOOSE && !foundCaboose) {
         addLine(_buildReport, THREE, tr("Staging track (%1) does not have a caboose with the correct road (%2)").arg(
                 departStageTrack->getName(), _train->getCabooseRoad()));
         return false;
     }
     // does the train require a car with FRED and did we find one from staging?
     if ((_train->getRequirements() & Train::FRED) == Train::FRED && !foundFRED) {
         addLine(_buildReport, THREE, tr("Staging track (%1) does not have a car with FRED road (%2)").arg(
                 departStageTrack->getName(), _train->getCabooseRoad()));
         return false;
     }
     addLine(_buildReport, SEVEN, tr("buildTrainCanDepartTrack").arg(
             _train->getName(), departStageTrack->getName()));
     return true;
 }

 /**
  * Checks to see if staging track can accept train.
  *
  * @return true if staging track is empty, not reserved, and accepts car and
  *         engine types, roads, and loads.
  */
 /*private*/ bool TrainBuilder::checkTerminateStagingTrack(Track* terminateStageTrack) {
     if (!terminateStageTrack->acceptsDropTrain(_train)) {
         addLine(_buildReport, FIVE, tr("Staging track ({%1) does not service this train").arg(terminateStageTrack->getName()));
         return false;
     }
     // In normal mode, find a completely empty track. In aggressive mode, a track that scheduled to depart is okay
     if (((!Setup::isBuildAggressive() || !Setup::isStagingTrackImmediatelyAvail()) && terminateStageTrack
             ->getNumberRS() != 0)
             || terminateStageTrack->getNumberRS() != terminateStageTrack->getPickupRS()) {
         addLine(_buildReport, FIVE, tr("Staging track (%1) is occupied, found %2 locomotive(s) and %3 cars").arg(
                 terminateStageTrack->getName()).arg(terminateStageTrack->getNumberEngines()).arg(
                         terminateStageTrack->getNumberCars()));
         return false;
     }
     if (terminateStageTrack->getDropRS() != 0) {
         addLine(_buildReport, FIVE, tr("Staging track (%1) is reserved, set out count: %2").arg(
                 terminateStageTrack->getName()).arg(terminateStageTrack->getDropRS()));
         return false;
     }
     if (terminateStageTrack->getPickupRS() > 0) {
         addLine(_buildReport, FIVE, tr("Train on staging track (%1) is scheduled to depart ").arg(
                 terminateStageTrack->getName()));
     }
     // if track is setup to accept a specific train or route, then ignore other track restrictions
     if (terminateStageTrack->getDropOption()==(Track::TRAINS)
             || terminateStageTrack->getDropOption()==(Track::ROUTES)) {
         addLine(_buildReport, SEVEN, tr("Train (%1) can terminate to staging track (%2)").arg(
                 _train->getName()).arg(terminateStageTrack->getName()));
         return true; // train can drop to this track, ignore other track restrictions
     }
     if (!Setup::isTrainIntoStagingCheckEnabled()) {
         addLine(_buildReport, SEVEN, tr("Train (%1) can terminate to staging track (%2)").arg(
                 _train->getName()).arg(terminateStageTrack->getName()));
         return true;
     }
     if (!checkTerminateStagingTrackRestrications(terminateStageTrack)) {
         addLine(_buildReport, SEVEN, tr("Option to restrict staging to the same car type, road, and load as train is enabled"));
         return false;
     }
     return true;
 }

 /*private*/ bool TrainBuilder::checkTerminateStagingTrackRestrications(Track* terminateStageTrack) {
     // check go see if location/track will accept the train's car and engine types
     foreach (QString name, _train->getTypeNames()) {
         if (!_terminateLocation->acceptsTypeName(name)) {
             addLine(_buildReport, FIVE, tr("Destination (%1) does not accept type (%2)").arg(_terminateLocation->getName()).arg(name));
             return false;
         }
         if (!terminateStageTrack->acceptsTypeName(name)) {
             addLine(_buildReport, FIVE, tr("Staging track (%1) does not accept type (%2)").arg(
                     terminateStageTrack->getName()).arg(name));
             return false;
         }
     }
     // check go see if track will accept the train's car and engine roads
     if (_train->getRoadOption()==(Train::ALL_ROADS)
             && terminateStageTrack->getRoadOption()!=(Track::ALL_ROADS)) {
         addLine(_buildReport, FIVE, tr("Staging track (%1) does not accept all roads").arg(
                 terminateStageTrack->getName()));
         return false;

     } else if (_train->getRoadOption()==(Train::INCLUDE_ROADS)) {
         foreach (QString name, _train->getRoadNames()) {
             if (!terminateStageTrack->acceptsRoadName(name)) {
                 addLine(_buildReport, FIVE, tr("Staging track (%1) does not accept road (%2)").arg(
                         terminateStageTrack->getName()).arg(name));
                 return false;
             }
         }
     } else if (_train->getRoadOption()==(Train::EXCLUDE_ROADS)) {
         QStringList roads = QStringList();
         foreach (QString road, ((CarRoads*)InstanceManager::getDefault("CarRoads"))->getNames()) {
             roads.append(road);
         }
         foreach (QString road, _train->getRoadNames()) {
             roads.removeOne(road);
         }
         foreach (QString road, roads) {
             if (!terminateStageTrack->acceptsRoadName(road)) {
                 addLine(_buildReport, FIVE, tr("Staging track (%1) does not accept road (%2)").arg(
                         terminateStageTrack->getName()).arg(road));
                 return false;
             }
         }
     }
     // check go see if track will accept the train's car loads
     if (_train->getLoadOption()==(Train::ALL_LOADS)
             && terminateStageTrack->getLoadOption()!=(Track::ALL_LOADS)) {
         addLine(_buildReport, FIVE, tr("Staging track (%1) does not accept all loads").arg(
                 terminateStageTrack->getName()));
         return false;

     } else if (_train->getLoadOption()==(Train::INCLUDE_LOADS)) {
         foreach (QString load, _train->getLoadNames()) {
             QStringList loadParts = load.split(CarLoad::SPLIT_CHAR); // split load name
             if (loadParts.length() > 1) {
                 if (!terminateStageTrack->acceptsLoad(loadParts[1], loadParts[0])) {
                     addLine(_buildReport, FIVE, tr("Staging track (%1) does not accept load (%2)").arg(
                             terminateStageTrack->getName()).arg(load));
                     return false;
                 }
             } else {
                 if (!terminateStageTrack->acceptsLoadName(load)) {
                     addLine(_buildReport, FIVE, tr("Staging track (%1) does not accept load (%2)").arg(
                             terminateStageTrack->getName()).arg(load));
                     return false;
                 }
             }
         }
     } else if (_train->getLoadOption()==(Train::EXCLUDE_LOADS)) {
         // build a list of loads that the staging track must accept
         QStringList loads = QStringList();
         foreach (QString type, _train->getTypeNames()) {
             foreach (QString load, ((CarLoads*)InstanceManager::getDefault("CarLoads"))->getNames(type)) {
                 if (!loads.contains(load)) {
                     loads.append(load);
                 }
             }
         }
         // remove the loads that the train won't carry
         foreach (QString load, _train->getLoadNames()) {
             loads.removeOne(load);
         }
         foreach (QString load, loads) {
             QStringList loadParts = load.split(CarLoad::SPLIT_CHAR); // split load name
             if (loadParts.length() > 1) {
                 if (!terminateStageTrack->acceptsLoad(loadParts[1], loadParts[0])) {
                     addLine(_buildReport, FIVE, tr("Staging track (%1) does not accept load (%2)").arg(
                             terminateStageTrack->getName()).arg(load));
                     return false;
                 }
             } else {
                 if (!terminateStageTrack->acceptsLoadName(load)) {
                     addLine(_buildReport, FIVE, tr("Staging track (%1) does not accept load (%2)").arg(
                             terminateStageTrack->getName()).arg(load));
                     return false;
                 }
             }
         }
     }
     addLine(_buildReport, SEVEN, tr("Train ({%1) can terminate to staging track ({%2)").arg(
             _train->getName()).arg(terminateStageTrack->getName()));
     return true;
 }

 /**
  * Find the final destination and track for a car with a custom load. Car
  * doesn't have a destination or final destination. There's a check to see
  * if there's a spur/ schedule for this car. Returns true if a schedule was
  * found. Hold car at current location if any of the spurs checked has an
  * alternate track.
  *
  * @param car the car with the load
  * @return true if there's a schedule that can be routed to for this car and
  *         load
  * @throws BuildFailedException
  */
 /*private*/ bool TrainBuilder::findFinalDestinationForCarLoad(Car* car) //throws BuildFailedException
                                        {
     bool routeToSpurFound = false;
     if (car->getLoadName()==(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultEmptyName())
             || car->getLoadName()==(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultLoadName()) || car->getDestination() != NULL
             || car->getFinalDestination() != NULL) {
         return false; // no schedule found for this car
     }
     addLine(_buildReport, FIVE, tr("Find spur for car (%1) type (%2) custom load (%3) at (%4)").arg(
             car->toString()).arg(car->getTypeName()).arg(car->getLoadName(),
                     car->getLocationName() + ").arg(" + car->getTrackName()));
     if (car->getKernel() != NULL) {
         addLine(_buildReport, SEVEN, tr("Car (%1) is lead in kernel (%2) with %3 cars, %4 %5").arg(
                 car->toString()).arg(car->getKernelName()).arg(car->getKernel()->getSize()).arg(car->getKernel()->getTotalLength()).arg(
                 Setup::getLengthUnit().toLower()));
     }
     QList<Track*> tracks = locationManager->getTracksByMoves(Track::SPUR);
    log->debug(tr("Found %1 spurs").arg(tracks.size()));
     QList<Location*> locations = QList<Location*>(); // locations not reachable
     foreach (Track* track, tracks) {
         if (car->getTrack() == track || track->getSchedule() == NULL) {
             continue;
         }
         if (locations.contains(track->getLocation())) {
             continue;
         }
         if (!car->getTrack()->acceptsDestination(track->getLocation())) {
             addLine(_buildReport, SEVEN, tr("Destination (%1) not serviced by departure track (%2)").arg(
                     track->getLocation()->getName()).arg(car->getTrackName()));
             locations.append(track->getLocation());
             continue;
         }
         if (!_train->isAllowThroughCarsEnabled() && !_train->isLocalSwitcher() && !car->isCaboose() && !car->hasFred()
                 && !car->isPassenger()
                 && splitString(car->getLocationName())==(splitString(_departLocation->getName()))
                 && splitString(track->getLocation()->getName())==(splitString(_terminateLocation->getName()))
                 && splitString(_departLocation->getName())!=(splitString(_terminateLocation->getName()))) {
            log->debug(tr("Skipping track ({}), through cars not allowed to terminal ({})").arg(track->getName()).arg(
                     _terminateLocation->getName()));
             continue;
         }

         QString status = car->testDestination(track->getLocation(), track);

         if (status==(Track::OKAY) && !_train->isAllowLocalMovesEnabled()
                 && splitString(car->getLocationName())==(splitString(track->getLocation()->getName()))) {
             addLine(_buildReport, SEVEN, tr("Local move for car with custom load by train (%1) to spur (%2, %3) disabled").arg(
                     _train->getName()).arg(track->getLocation()->getName()).arg(track->getName()));
             //log->debug(tr("Skipping track ({}), it would require a local move").arg(track->getName())); // NOI18N
             continue;
         }
         if (status!=(Track::OKAY)) {
             if (track->getScheduleMode() == Track::SEQUENTIAL && status.startsWith(Track::SCHEDULE)) {
                 addLine(_buildReport, SEVEN, tr("Track (%1) at (%2) is in sequential mode and %3").arg(
                         track->getName()).arg(track->getLocation()->getName()).arg(status));
             }
             // if the track has an alternate track don't abort if the issue was space
             if (!status.startsWith(Track::LENGTH) || track->checkSchedule(car)!=(Track::OKAY)) {
                 continue;
             }
             if (track->getAlternateTrack() == NULL) {
                 // report that the spur is full and no alternate
                 addLine(_buildReport, SEVEN, tr("Spur at (%1, %2) is full, no alternate track").arg(
                         track->getLocation()->getName()).arg(track->getName()));
                 continue;
             } else {
                 addLine(_buildReport, SEVEN, tr("Spur (%1, %2) full, has alternate track (%3)").arg(
                         track->getLocation()->getName()).arg(track->getName(),
                                 track->getAlternateTrack()->getName()));
                 // check to see if alternate and track are configured properly
                 if (!_train->isLocalSwitcher()
                         && (track->getTrainDirections() & track->getAlternateTrack()->getTrainDirections()) == 0) {
                     addLine(_buildReport, SEVEN, tr("final destination track (%1) train direction (%2) and alternate track (%3) train direction (%4) aren''t compatible").arg(
                             track->getName(),
                             formatStringToCommaSeparated(Setup::getDirectionStrings(track->getTrainDirections())),
                             track->getAlternateTrack()->getName()).arg(
                             formatStringToCommaSeparated(Setup::getDirectionStrings(track->getAlternateTrack()
                                     ->getTrainDirections()))));
                     continue;
                 }
             }
         }

         addLine(_buildReport, SEVEN, tr("Try destination (%3, %4) for car (%1) with load (%2) ").arg(
                 car->toString()).arg(car->getLoadName()).arg(track->getLocation()->getName()).arg(track->getName()));

         // show if track has an alternate
         if (track->getAlternateTrack() != NULL) {
             addLine(_buildReport, SEVEN, tr("Track (%1, %2) has alternate track (%3)").arg(
                     track->getLocation()->getName()).arg(track->getName()).arg(
                             track->getAlternateTrack()->getName()));
         }

         // check the number of in bound cars to this track
         if (!track->isSpaceAvailable(car)) {
             // Now determine if we should move the car or just leave it where it is
             QString id = track->getScheduleItemId(); // save the tracks schedule item id
             // determine if this car can be routed to the spur
             car->setFinalDestination(track->getLocation());
             car->setFinalDestinationTrack(track);
             // hold car if able to route and track has an alternate
             if (Router::instance()->setDestination(car, _train, _buildReport) && track->getAlternateTrack() != NULL) {
                 routeToSpurFound = true; // if we don't find another spur, keep the car here for now
             }
             car->setDestination(NULL, NULL);
             car->setFinalDestination(NULL);
             car->setFinalDestinationTrack(NULL);
             track->setScheduleItemId(id); // restore id
             addLine(_buildReport, SEVEN, tr("Car (%1) would overload track (%2, %3), currently %4 inbound cars, length (%5) %6, %7% loading from staging").arg(
                     car->toString(), track->getLocation()->getName(), track->getName()).arg(
                             track->getNumberOfCarsInRoute(), track->getReservedInRoute()).arg(
                             Setup::getLengthUnit().toLower()).arg(track->getReservationFactor()));
             continue;
         }
         // try to send car to this spur
         car->setFinalDestination(track->getLocation());
         car->setFinalDestinationTrack(track);
         // test to see if destination is reachable by this train
         if (Router::instance()->setDestination(car, _train, _buildReport) && track->getAlternateTrack() != NULL) {
             routeToSpurFound = true; // found a route to the spur
         }
         if (car->getDestination() != NULL) {
             // is car part of kernel?
             car->updateKernel();
             if (car->getDestinationTrack() != track) {
                 car->setScheduleItemId(track->getCurrentScheduleItem()->getId());
                 track->bumpSchedule();
             }
             return true; // done, car has a new destination
         }
         addLine(_buildReport, SEVEN, tr("Not able to set destination for car (%1) due to %2").arg(
                 car->toString()).arg(Router::instance()->getStatus()));
         car->setFinalDestination(NULL);
         car->setFinalDestinationTrack(NULL);
     }
     addLine(_buildReport, SEVEN, tr("Could not find a spur for car (%1) custom load (%2)").arg(
             car->toString(), car->getLoadName()));
     if (routeToSpurFound && !_train->isSendCarsWithCustomLoadsToStagingEnabled()
             && !car->getLocation()->isStaging()) {
         addLine(_buildReport, SEVEN, tr("Hold car (%1) at (%2, %3) found a route to a spur / schedule").arg(
                 car->toString()).arg(car->getLocationName()).arg(car->getTrackName()));
     } else {
         // try and send car to staging
         addLine(_buildReport, FIVE, tr("Try to send car (%1) custom load (%2) to staging").arg(
                 car->toString()).arg(car->getLoadName()));
         tracks = locationManager->getTracks(Track::STAGING);
        log->debug(tr("Found %1 staging tracks").arg(tracks.size()));
         while (tracks.size() > 0) {
             // pick a track randomly
             int rnd = (int) (qrand() % tracks.size());
             Track* track = tracks.at(rnd);
             tracks.removeOne(track);
            log->debug(tr("Staging track (%1, %2)").arg(track->getLocation()->getName()).arg(track->getName()));
             if (track->getLocation() == car->getLocation()) {
                 continue;
             }
             if (locations.contains(track->getLocation())) {
                 continue;
             }
             if (_terminateStageTrack != NULL && track->getLocation() == _terminateLocation
                     && track != _terminateStageTrack) {
                 continue; // ignore other staging tracks at terminus
             }
             if (!car->getTrack()->acceptsDestination(track->getLocation())) {
                 addLine(_buildReport, SEVEN, tr("Destination (%1) not serviced by departure track (%2)").arg(
                         track->getLocation()->getName()).arg(car->getTrackName()));
                 locations.append(track->getLocation());
                 continue;
             }
             QString status = track->accepts(car);
             if (status!=(Track::OKAY) && !status.startsWith(Track::LENGTH)) {
                log->debug(tr("Staging track (%1) can't accept car (%2)").arg(track->getName()).arg(car->toString()));
                 continue;
             }
             addLine(_buildReport, SEVEN, tr("Staging (%1, %2) can accept car''s load (%3)").arg(
                     track->getLocation()->toString()).arg(track->getName()).arg(car->getLoadName()));
             // try to send car to staging
             car->setFinalDestination(track->getLocation());
             // test to see if destination is reachable by this train
             if (Router::instance()->setDestination(car, _train, _buildReport)) {
                 routeToSpurFound = true; // found a route to staging
             }
             if (car->getDestination() != NULL) {
                 // is car part of kernel?
                 car->updateKernel();
                 return true;
             }
             locations.append(track->getLocation()); // couldn't route to this staging location
             car->setFinalDestination(NULL);
         }
         addLine(_buildReport, SEVEN, tr("Couldn''t find staging that would accept car (%1) and load (%2)").arg(
                 car->toString()).arg(car->getLoadName()));
     }
     return routeToSpurFound; // done
 }

 /**
  * Used to generate a car's load from staging. Search for a spur with a
  * schedule and load car if possible.
  *
  * @param car the car
  * @throws BuildFailedException
  */
 /*private*/ bool TrainBuilder::generateCarLoadFromStaging(Car* car) //throws BuildFailedException
{
     if (car->getTrack() == NULL || car->getTrack()->getTrackType()!=(Track::STAGING)
             || (!car->getTrack()->isAddCustomLoadsAnySpurEnabled() && !car->getTrack()->isAddCustomLoadsEnabled())
             || car->getLoadName()!=(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultEmptyName()) || car->getDestination() != NULL
             || car->getFinalDestination() != NULL) {
        log->debug(tr("No load generation for car (%1) isAddLoadsAnySpurEnabled: ").arg(car->toString()) // NOI18N
                 +
                 (car->getTrack()->isAddCustomLoadsAnySpurEnabled() ? "true" : "false") // NOI18N
                 +
                 tr(", car load (%1) destination (%2) final destination (%3)").arg(// NOI18N
                  car->getLoadName()).arg(car->getDestinationName()).arg(car->getFinalDestinationName())); // NOI18N
         // if car has a destination or /*final*/ destination add "no load generated" message to report
         if (car->getTrack() != NULL && car->getTrack()->getTrackType()==(Track::STAGING)
                 && car->getTrack()->isAddCustomLoadsAnySpurEnabled()
                 && car->getLoadName()==(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultEmptyName())) {
             addLine(_buildReport, FIVE, tr("Car (%1) departing staging with load (%2) has destination (%3) or final destination (%4) no load generated for this car").arg(
                     car->toString()).arg(car->getLoadName()).arg(car->getDestinationName()).arg(
                             car->getFinalDestinationName()));
         }
         return false; // no load generated for this car
     }
     addLine(_buildReport, FIVE, tr("Generate load for (%1) type (%2) load (%3) at (%4, %5)").arg(
             car->toString(), car->getTypeName(), car->getLoadName(), car->getLocationName(), car->getTrackName()));
     // check to see if car type has custom loads
     if (((CarLoads*)InstanceManager::getDefault("CarLoads"))->getNames(car->getTypeName()).size() == 2) {
         addLine(_buildReport, SEVEN, tr("Car (%1) type (%2) doesn''t have a custom load,").arg(
                 car->toString(), car->getTypeName()));
         return false;
     }
     if (car->getKernel() != NULL) {
         addLine(_buildReport, SEVEN, tr("Car (%1) is lead in kernel (%2) with %3 cars, %4 %5").arg(
                 car->toString()).arg(car->getKernelName()).arg(car->getKernel()->getSize()).arg(car->getKernel()->getTotalLength()).arg(
                 Setup::getLengthUnit().toLower()));
     }
     QList<Track*> tracks = locationManager->getTracksByMoves(Track::SPUR);
    log->debug(tr("Found %1 spurs").arg(tracks.size()));
     foreach (Track* track, tracks) {
         ScheduleItem* si = getScheduleItem(car, track);
         if (si == NULL) {
             continue; // no match
         } // only use tracks serviced by this train?
         if (car->getTrack()->isAddCustomLoadsEnabled()
                 && _train->getRoute()->getLastLocationByName(track->getLocation()->getName()) == NULL) {
             continue;
         }
         // need to set car load so testDestination will work properly
         QString oldCarLoad = car->getLoadName(); // should be the default empty
         car->setLoadName(si->getReceiveLoadName());
         QString status = car->testDestination(track->getLocation(), track);
         if (status!=(Track::OKAY) && !status.startsWith(Track::LENGTH)) {
             addLine(_buildReport, SEVEN, tr("Destination (%1, %2) can''t service car (%3) with load (%4) due to %5").arg(
                     track->getLocation()->getName()).arg(track->getName()).arg(car->toString()).arg(
                             si->getReceiveLoadName()).arg(status));
             // restore car's load
             car->setLoadName(oldCarLoad);
             continue;
         }
         addLine(_buildReport, SEVEN, tr("Try spur (%1, %2) custom load (%3)").arg(
                 track->getLocation()->getName()).arg(track->getName()).arg(car->getLoadName()));
         if (!car->getTrack()->acceptsDestination(track->getLocation())) {
             addLine(_buildReport, SEVEN, tr("Destination (%1) not serviced by departure track (%2)").arg(
                     track->getLocation()->getName()).arg(car->getTrackName()));
             // restore car's load
             car->setLoadName(oldCarLoad);
             continue;
         }
         if (!track->isSpaceAvailable(car)) {
             addLine(_buildReport, SEVEN, tr("Car (%1) would overload track (%2, %3), currently %4 inbound cars, length (%5) %6, %7% loading from staging").arg(
                     car->toString()).arg(track->getLocation()->getName()).arg(track->getName()).arg(
                             track->getNumberOfCarsInRoute()).arg(track->getReservedInRoute()).arg(
                             Setup::getLengthUnit().toLower()).arg(track->getReservationFactor()));
             // restore car's load
             car->setLoadName(oldCarLoad);
             continue;
         }
         car->setFinalDestination(track->getLocation());
         car->setFinalDestinationTrack(track);
         // try routing car
         if (Router::instance()->setDestination(car, _train, _buildReport) && car->getDestination() != NULL) {
             // return car with this custom load and destination
             addLine(_buildReport, FIVE, tr("Car (%1) custom load (%2) final destination (%3, %4)").arg(
                     car->toString()).arg(si->getReceiveLoadName()).arg(track->getLocation()->getName()).arg(
                             track->getName()));
             car->setLoadGeneratedFromStaging(true);
             // is car part of kernel?
             car->updateKernel();
             track->bumpSchedule();
             return true; // done, car now has a custom load
         }
         addLine(_buildReport, SEVEN, tr("Can't route car (%1) with load (%2) to (%3, %4)").arg(
                 car->toString()).arg(si->getReceiveLoadName()).arg(track->getLocation()->getName()).arg(track->getName()));
         car->setDestination(NULL, NULL);
         // restore load and /*final*/ destination and track
         car->setLoadName(oldCarLoad);
         car->setFinalDestination(NULL);
         car->setFinalDestinationTrack(NULL);
     }
     addLine(_buildReport, SEVEN, tr("Could not find a route to a spur that needs a custom load for car (%1)").arg(car
             ->toString()));
     return false; // done, no load generated for this car
 }

 /**
  * Tries to place a custom load in the car that is departing staging, and
  * may terminate to staging. Tries to create a custom load that will be
  * accepted by the train's terminal if the terminal is staging. Otherwise,
  * any staging track is searched for that will accept this car and a custom
  * load.
  *
  * @param car the car
  * @throws BuildFailedException
  */
 /*private*/ bool TrainBuilder::generateCarLoadStagingToStaging(Car* car) //throws BuildFailedException
{
     if (car->getTrack() == NULL || car->getTrack()->getTrackType()!=(Track::STAGING)
             || !car->getTrack()->isAddCustomLoadsAnyStagingTrackEnabled()
             || car->getLoadName()!=(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultEmptyName()) || car->getDestination() != NULL
             || car->getFinalDestination() != NULL) {
        log->debug(tr("No load generation for car (%1) isAddCustomLoadsAnyStagingTrackEnabled: ").arg(car->toString()) // NOI18N
                 +
                 (car->getTrack()->isAddCustomLoadsAnySpurEnabled() ? "true" : "false") // NOI18N
                 +
                 tr(", car load (%1) destination (%2) final destination (%3)").arg( // NOI18N
                  car->getLoadName()).arg(car->getDestinationName()).arg(car->getFinalDestinationName()));
         return false;
     }
     QList<Track*> tracks = locationManager->getTracks(Track::STAGING);
    log->debug(tr("Found %1 staging tracks for load generation").arg(tracks.size()));
     // list of locations that can't be reached by the router
    QList<Location*> locationsNotReachable = QList<Location*>();
     while (tracks.size() > 0) {
         // pick a track randomly
         int rnd = (int) (qrand() * tracks.size());
         Track* track = tracks.at(rnd);
         tracks.removeOne(track);
        log->debug(tr("Try staging track (%1, %2)").arg(track->getLocation()->getName()).arg(track->getName()));
         // find a staging track that isn't at the departure
         if (track->getLocation() == _departLocation) {
            log->debug(tr("Don't use departure location (%1)").arg(track->getLocation()->getName()));
             continue;
         }
         if (_train->isAllowThroughCarsEnabled() && track->getLocation() != _terminateLocation) {
            log->debug(tr("Through cars to location (%1) not allowed").arg(track->getLocation()->getName()));
             continue;
         }
         if (locationsNotReachable.contains(track->getLocation())) {
            log->debug(tr("Location (%1) not reachable").arg(track->getLocation()->getName()));
             continue;
         }
         if (!car->getTrack()->acceptsDestination(track->getLocation())) {
             addLine(_buildReport, SEVEN, tr("Destination (%1) not serviced by departure track (%2)").arg(
                     track->getLocation()->getName()).arg(car->getTrackName()));
             locationsNotReachable.append(track->getLocation());
             continue;
         }
         if (_terminateStageTrack != NULL && track->getLocation() == _terminateStageTrack->getLocation()) {
            log->debug(tr("Train doesn't terminate to staging track %1 at terminal {}").arg(track->getName()).arg(track
                     ->getLocation()->getName()));
             continue;
         }
         // the following method sets the load generated from staging bool
         if (generateLoadCarDepartingAndTerminatingIntoStaging(car, track)) {
             // test to see if destination is reachable by this train
             if (Router::instance()->setDestination(car, _train, _buildReport) && car->getDestination() != NULL) {
                 return true; // done, car has a custom load and a /*final*/ destination
             }
             addLine(_buildReport, SEVEN, tr("Staging track (%1, %2) not reachable with custom load (%3)").arg(
                     track->getLocation()->getName()).arg(track->getName()).arg(car->getLoadName()));
             // return car to original state
             car->setLoadName(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultEmptyName());
             car->setLoadGeneratedFromStaging(false);
             car->setFinalDestination(NULL);
             car->updateKernel();
             locationsNotReachable.append(track->getLocation()); // couldn't route to this staging location
         }
     }
     // No staging tracks reachable, try the track the train is terminating to
     if (_train->isAllowThroughCarsEnabled() && _terminateStageTrack != NULL
             && car->getTrack()->acceptsDestination(_terminateStageTrack->getLocation())
             && generateLoadCarDepartingAndTerminatingIntoStaging(car, _terminateStageTrack)) {
         return true;
     }

     return false;
 }

 /**
  * Used when generating a car load from staging.
  *
  * @param car the car.
  * @param track the car's destination track that has the schedule.
  * @return ScheduleItem si if match found, NULL otherwise.
  * @throws BuildFailedException
  */
 /*private*/ ScheduleItem* TrainBuilder::getScheduleItem(Car* car, Track* track) //throws BuildFailedException
{
     if (track->getSchedule() == NULL) {
         return NULL;
     }
     ScheduleItem* si = NULL;
     if (track->getScheduleMode() == Track::SEQUENTIAL) {
         si = track->getCurrentScheduleItem();
         if (si == NULL) {
             throw BuildFailedException(tr("ERROR Can''t find schedule item (%1) for schedule (%2) for track (%3) at location (%4)").arg(
                     track->getScheduleItemId()).arg(track->getScheduleName()).arg(track->getName()).arg(
                             track->getLocation()->getName()),"Normal");
          return NULL;
         }
         return checkScheduleItem(si, car, track);
     }
    log->debug(tr("Track (%1) in match mode").arg(track->getName()));
     for (int i = 0; i < track->getSchedule()->getSize(); i++) {
         si = track->getNextScheduleItem();
         if (si == NULL) {
             throw BuildFailedException(tr("ERROR Can't find schedule item (%1) for schedule (%2) for track (%3) at location (%4)").arg(
                     track->getScheduleItemId()).arg(track->getScheduleName()).arg(track->getName()).arg(
                             track->getLocation()->getName()));
          return NULL;
         }
         si = checkScheduleItem(si, car, track);
         if (si != NULL) {
             break;
         }
     }
     return si;
 }

 /**
  * Checks a schedule item to see if the car type matches, and the train and
  * track can service the schedule item's load. This code doesn't check to
  * see if the car's load can be serviced by the schedule. Instead a schedule
  * item is returned that allows the program to assign a custom load to the
  * car that matches a schedule item. Therefore, schedule items that request
  * don't request a custom load are ignored.
  *
  * @param si the schedule item
  * @param car the car to check
  * @param track the destination track
  * @return Schedule item si if okay, NULL otherwise.
  */
 /*private*/ ScheduleItem* TrainBuilder::checkScheduleItem(ScheduleItem* si, Car* car, Track* track) {
     if (car->getTypeName()!=(si->getTypeName()) || si->getReceiveLoadName()==(ScheduleItem::NONE)
             || si->getReceiveLoadName()==(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultEmptyName())
             || si->getReceiveLoadName()==(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultLoadName())) {
        log->debug(tr("Not using track (%1) schedule request type (%2) road (%3) load (%4)").arg(track->getName()).arg(si
                 ->getTypeName()).arg(si->getRoadName()).arg(si->getReceiveLoadName())); // NOI18N
         return NULL;
     }
     if (si->getRoadName()!=(ScheduleItem::NONE) && car->getRoadName()!=(si->getRoadName())) {
        log->debug(tr("Not using track (%1) schedule request type (%2) road (%3) load (%4)").arg(track->getName()).arg(si
                 ->getTypeName()).arg(si->getRoadName()).arg(si->getReceiveLoadName())); // NOI18N
         return NULL;
     }
     if (!_train->acceptsLoad(si->getReceiveLoadName(), si->getTypeName())) {
         addLine(_buildReport, SEVEN, tr("Train (%1) doesn''t service load (%2) destination (%3, %4)").arg(
                 _train->getName()).arg(si->getReceiveLoadName()).arg(track->getLocation()->getName()).arg(track->getName()));
         return NULL;
     }
     // does the departure track allow this load?
     if (!car->getTrack()->shipsLoad(si->getReceiveLoadName(), car->getTypeName())) {
         addLine(_buildReport, SEVEN, tr("Departure track (%1) can''t ship load (%2) to destination (%3, %4)").arg(
                 car->getTrackName()).arg(si->getReceiveLoadName()).arg(track->getLocation()->getName()).arg(track->getName()));
         return NULL;
     }
     if (si->getSetoutTrainScheduleId()!=(ScheduleItem::NONE)
             && ((TrainManager*)InstanceManager::getDefault("TrainManager"))->getTrainScheduleActiveId()!=(si->getSetoutTrainScheduleId())) {
        log->debug("Schedule item isn't active");
         // build the status message
         TrainSchedule* aSch = ((Operations::TrainScheduleManager*)InstanceManager::getDefault("TrainScheduleManager"))->getScheduleById(
                 ((TrainManager*)InstanceManager::getDefault("TrainManager"))->getTrainScheduleActiveId());
         TrainSchedule* tSch = ((Operations::TrainScheduleManager*)InstanceManager::getDefault("TrainScheduleManager"))->getScheduleById(si->getSetoutTrainScheduleId());
         QString aName = "";
         QString tName = "";
         if (aSch != NULL) {
             aName = aSch->getName();
         }
         if (tSch != NULL) {
             tName = tSch->getName();
         }
         addLine(_buildReport, SEVEN, tr("Track (%1) schedule id (%2) timetable (%3) not active for (%4)").arg(
                 track->getName()).arg(si->getId()).arg(tName).arg(aName));

         return NULL;
     }
     if (si->getRandom()!=(ScheduleItem::NONE)) {
         bool ok;
             int value = si->getRandom().toInt(&ok);
             double random = 100 * qrand();
            log->debug(tr("Selected random %1, created random %2").arg(si->getRandom()).arg(random));
             if (random > value) {
                 addLine(_buildReport, SEVEN, tr("Track (%1) schedule (%2) id (%3) random value %4 is less than generated %5").arg(
                         track->getName()).arg(track->getScheduleName()).arg(si->getId()).arg(value).arg(random));
                 return NULL;
             }
         if(!ok) {
            log->error(tr("Random value %1 isn't a number").arg(si->getRandom()));
         }
     }
    log->debug(tr("Found track (%1) schedule item id (%2) for car (%3)").arg(track->getName()).arg(si->getId()).arg(car->toString()));
     car->setScheduleItemId(si->getId());
     return si;
 }

 /**
  * Checks all of the cars on an interchange track and returns the oldest
  * (FIFO) or newest (LIFO) car residing on that track-> Note high priority
  * cars will be serviced first, then low.
  *
  * @param car the car being pulled from the interchange track
  * @return The FIFO car at this interchange
  */
 /*private*/ Car* TrainBuilder::getCarOrder(Car* car) {
     if (car->getTrack()->getServiceOrder()==(Track::NORMAL)) {
         return car;
     }
    log->debug(tr(
             "Get %1 car (%2) from %3 (%4), last moved date: %5").arg(// NOI18N
             car->getTrack()->getServiceOrder()).arg(car->toString()).arg(car->getTrack()->getTrackType()).arg(car->getTrackName()).arg(
             car->getLastDate()));
     Car* bestCar = car;
     for (int i = _carIndex; i < _carList->size(); i++) {
         Car* testCar = _carList->at(i);
         if (testCar->getTrack() == car->getTrack()) {
            log->debug(tr("%1 car (%2) last moved date: %3").arg(car->getTrack()->getTrackType()).arg(testCar->toString()).arg(testCar
                     ->getLastDate())); // NOI18N
             if (car->getTrack()->getServiceOrder()==(Track::FIFO)) {
                 if (bestCar->getLastMoveDate()/*.after*/ < (testCar->getLastMoveDate()) &&
                         bestCar->getLoadPriority()==(testCar->getLoadPriority())) {
                     bestCar = testCar;
                    log->debug(tr("New best car (%1)").arg(bestCar->toString()));
                 }
             } else if (car->getTrack()->getServiceOrder()==(Track::LIFO)) {
                 if (bestCar->getLastMoveDate()/*.before*/< (testCar->getLastMoveDate()) &&
                         bestCar->getLoadPriority()==(testCar->getLoadPriority())) {
                     bestCar = testCar;
                    log->debug(tr("New best car (%1").arg(bestCar->toString()));
                 }
             }
         }
     }
     if (car != bestCar) {
         addLine(_buildReport, SEVEN, tr("%1 track (%2) in mode %3, car (%4) last moved %5 has priority over car (%6) last moved %7").arg(
                 car->getTrack()->getTrackType()).arg(car->getTrackName()).arg(car->getTrack()->getServiceOrder()).arg(
                         bestCar->toString()).arg(bestCar->getLastDate()).arg(car->toString(), car->getLastDate()));
     }
     return bestCar;
 }

 /**
  * Determines if car was sitting on a FIFO or LIFO track, and if the car
  * wasn't given a destination, shifts the car's order earlier in the car
  * list so it won't be evaluated again.
  *
  * @param car
  */
 /*private*/ void TrainBuilder::checkCarOrder(Car* car) {
     // is car sitting on a FIFO or LIFO track?
     if (car->getTrack() != NULL && car->getTrack()->getServiceOrder()!=(Track::NORMAL) && _carList->contains(car)) {
         addLine(_buildReport, SEVEN, tr("Bypass car (%1) on track (%2) service order (%3)").arg(
                 car->toString()).arg(car->getTrackName()).arg(car->getTrack()->getServiceOrder()));
         // move car in front of current pointer so car is no longer used on this pass
         _carList->removeOne(car);
         _carList->insert(_carIndex, car);
     }
     addLine(_buildReport, FIVE, tr("Did not assign a destination for car (%1)").arg(
             car->toString()));
     addLine(_buildReport, FIVE, BLANK_LINE); // add line when in detailed report mode
 }

 /*private*/ bool TrainBuilder::checkCarForDestinationAndTrack(Car* car, RouteLocation* rl, RouteLocation* rld)
         //throws BuildFailedException
{
     int index;
     for (index = 0; index < _routeList->size(); index++) {
         if (rld == _routeList->at(index)) {
             break;
         }
     }
     return checkCarForDestinationAndTrack(car, rl, index - 1);
 }

 /**
  * Checks to see if car has a destination and tries to add car to train
  *
  * @param car
  * @param rl the car's route location
  * @param routeIndex where in the route the car pick up is
  * @return true if car has a destination.
  * @throws BuildFailedException if destination was staging and can't place
  *             car there
  */
 /*private*/ bool TrainBuilder::checkCarForDestinationAndTrack(Car* car, RouteLocation* rl, int routeIndex)
         //throws BuildFailedException
 {
     if (car->getDestination() == NULL) {
         return false;
     }
     addLine(_buildReport, SEVEN, tr("Car (%1) has assigned destination (%2)").arg(
             car->toString()).arg((car->getDestinationName() + ").arg(" + car->getDestinationTrackName())));
     RouteLocation* rld = _train->getRoute()->getLastLocationByName(car->getDestinationName());
     if (rld == NULL) {
         // car has a destination that isn't serviced by this train (destination loaded by router)
         addLine(_buildReport, FIVE, tr("Exclude car (%1) destination (%2) not part of this train''s route (%3)").arg(
                 car->toString()).arg(car->getDestinationName()).arg(_train->getRoute()->getName()));
         return true; // done
     }
     if (car->getRouteLocation() != NULL) {
         // The following code should never execute if train was reset before a build!
         addLine(_buildReport, THREE, tr("Car (%1) already assigned to this train").arg(
                 car->toString()));
     }
     // now go through the route and try and find a location with
     // the correct destination name
     int locCount = 0;
     for (int k = routeIndex; k < _routeList->size(); k++) {
         rld = _routeList->at(k);
         // if car can be picked up later at same location, skip
         if (checkForLaterPickUp(rl, rld, car)) {
             break;
         }
         if (rld->getName()!=(car->getDestinationName())) {
             continue;
         }
         // is the car's destination the terminal and is that allowed?
         if (!_train->isAllowThroughCarsEnabled() && !_train->isLocalSwitcher() && !car->isCaboose() && !car->hasFred()
                 && !car->isPassenger()
                 && splitString(car->getLocationName())==(splitString(_departLocation->getName()))
                 && splitString(car->getDestinationName())==(splitString(_terminateLocation->getName()))
                 && splitString(_departLocation->getName())!=(splitString(_terminateLocation->getName()))) {
             addLine(_buildReport, FIVE, tr("Car (%1) at location (%2) has destination (%3)").arg(
                     car->toString()).arg(_departLocation->getName()).arg(_terminateLocation->getName()));
             addLine(_buildReport, FIVE, tr("Through traffic not allowed from (%1) to terminal (%2)").arg(
                     _departLocation->getName()).arg(_terminateLocation->getName()));
             addLine(_buildReport, FIVE, BLANK_LINE); // add line when in detailed report mode
             return true; // done
         }
         locCount++; // show when this car would be dropped at location
        log->debug(tr("Car (%1) found a destination in train's route").arg(car->toString()));
         // are drops allows at this location?
         if (!rld->isDropAllowed()) {
             addLine(_buildReport, FIVE, tr("Route (%1) does not allow set outs at location (%2) id (%3) stop %4").arg(
                     _train->getRoute()->getName()).arg(rld->getName()).arg(rld->getId()).arg(locCount));
             continue;
         }
         if (rld->getCarMoves() >= rld->getMaxCarMoves()) {
             addLine(_buildReport, FIVE, tr("No moves left for route (%1) id (%2) destination (%3) stop %4").arg(
                     _train->getRoute()->getName()).arg(rld->getId()).arg(rld->getName()).arg(locCount));
             continue;
         }
         // is the train length okay?
         if (!checkTrainLength(car, rl, rld)) {
             continue;
         }
         // check for valid destination track
         if (car->getDestinationTrack() == NULL) {
             addLine(_buildReport, FIVE, tr("Car (%1) doesn''t have an assigned destination track").arg(
                     car->toString()));
             // is there a destination track assigned for staging cars?
             if (rld == _train->getTrainTerminatesRouteLocation() && _terminateStageTrack != NULL) {
                 QString status = car->testDestination(car->getDestination(), _terminateStageTrack);
                 if (status==(Track::OKAY)) {
                     addLine(_buildReport, FIVE,
                             tr("Car (%1) assigned to staging track (%2)").arg(car->toString()).arg(
                                     _terminateStageTrack->getName()));
                     addCarToTrain(car, rl, rld, _terminateStageTrack);
                     return true;
                 } else {
                     addLine(_buildReport, SEVEN, tr("Can't send (%1) to %4 (%2) due to %3").arg(car->toString()).arg(
                             _terminateStageTrack->getName()).arg(status).arg(_terminateStageTrack->getTrackTypeName()));
                     continue;
                 }
                 // no staging at this location, now find a destination track this this car
             } else {
                 QList<Track*> tracks = car->getDestination()->getTrackByMovesList(NULL);
                 addLine(_buildReport, SEVEN, tr("Found %1 tracks at destination (%2) for car (%3) load (%4)").arg(tracks.size()).arg(
                                 car->getDestinationName()).arg(car->toString()).arg(car->getLoadName()));
                 foreach (Track* testTrack, tracks) {
                     //log->debug("track (" +testTrack->getName()+ ") has "+ testTrack->getMoves() + " moves");
                     // dropping to the same track isn't allowed
                     if (testTrack == car->getTrack()) {
                         addLine(_buildReport, SEVEN, tr("Can't send car (%1) to same track (%2)").arg(car->toString()).arg(
                                 testTrack->getName()));
                         continue;
                     }
                     // is train direction correct?
                     if (!checkDropTrainDirection(car, rld, testTrack)) {
                         continue;
                     }
                     // drop to interchange or spur?
                     if (!checkTrainCanDrop(car, testTrack)) {
                         continue;
                     }
                     QString status = car->testDestination(car->getDestination(), testTrack);
                     // is the testTrack a spur with a schedule and alternate track?
                     if (status!=(Track::OKAY) && status.startsWith(Track::LENGTH)
                             && testTrack->checkSchedule(car)==(Track::OKAY)
                             && testTrack->getTrackType()==(Track::SPUR) && testTrack->getAlternateTrack() != NULL) {
                         addLine(_buildReport, SEVEN, tr("Spur (%1, %2) full, has alternate track (%3)").arg(
                                 testTrack->getLocation()->getName()).arg(testTrack->getName(),
                                 testTrack->getAlternateTrack()->getName()));
                         QString altStatus = car->testDestination(car->getDestination(), testTrack->getAlternateTrack());
                         // A car with a custom load sent to a spur will get a status with "CUSTOM" and "LOAD"
                         // embedded,
                         // if the spur doesn't have a schedule. Must use contains to determine if both are in the
                         // status message.
                         // The following code allows the alternate track to be a spur that doesn't have a schedule.
                         // TODO most of the other code only allows a yard or interchange track to be the alternate.
                         if (altStatus==(Track::OKAY)
                                 || (altStatus.contains(Track::CUSTOM) && altStatus.contains(Track::LOAD))) {
                             addLine(_buildReport, SEVEN, tr("Sending car (%1) to alternate track (%2)").arg(car->toString(),
                                     testTrack->getAlternateTrack()->getName()));
                             // forward the car to the original destination
                             car->setFinalDestination(car->getDestination());
                             car->setFinalDestinationTrack(testTrack);
                             car->setNextLoadName(car->getLoadName());
                             addCarToTrain(car, rl, rld, testTrack->getAlternateTrack());
                             testTrack->setMoves(testTrack->getMoves() + 1); // bump the number of moves
                             return true;
                         } else {
                             addLine(_buildReport, SEVEN, tr("Can't send (%1) to %4 (%2) due to %3").arg(car->toString()).arg(
                                     testTrack->getAlternateTrack()->getName()).arg(altStatus,
                                     testTrack->getTrackTypeName()));
                         }
                     }
                     if (status!=(Track::OKAY)) {
                         addLine(_buildReport, SEVEN, tr("Can''t send (%1) to %4 (%2) due to %3").arg(car->toString(),
                                 testTrack->getName()).arg(status).arg(testTrack->getTrackTypeName()));
                         continue;
                     }
                     addCarToTrain(car, rl, rld, testTrack);
                     return true;
                 }
             }
             // car has a destination track
         } else {
            log->debug(tr("Car (%1) has a destination track (%2)").arg(car->toString()).arg(car->getDestinationTrack()->getName()));
             // going into the correct staging track?
             if (rld==(_train->getTrainTerminatesRouteLocation()) && _terminateStageTrack != NULL
                     && _terminateStageTrack != car->getDestinationTrack()) {
                 // car going to wrong track in staging, change track
                 addLine(_buildReport, SEVEN, tr("Car (%1) has staging destination (%2, %3) wrong track").arg(
                         car->toString()).arg(car->getDestinationName()).arg(car->getDestinationTrackName()));
                 car->setDestination(_terminateStageTrack->getLocation(), _terminateStageTrack);
             }
             if (rld!=(_train->getTrainTerminatesRouteLocation()) || _terminateStageTrack == NULL
                     || _terminateStageTrack == car->getDestinationTrack()) {
                 // is train direction correct?
                 if (checkDropTrainDirection(car, rld, car->getDestinationTrack())) {
                     // drop to interchange or spur?
                     if (checkTrainCanDrop(car, car->getDestinationTrack())) {
                         QString status = car->testDestination(car->getDestination(), car->getDestinationTrack());
                         if (status==(Track::OKAY)
                                 && checkDropTrainDirection(car, rld, car->getDestinationTrack())) {
                             addCarToTrain(car, rl, rld, car->getDestinationTrack());
                             return true;
                         } else {
                             addLine(_buildReport, SEVEN, tr("Can't send (%1) to %4 (%2) due to %3").arg(car->toString(),
                                     car->getDestinationTrackName()).arg(status).arg(
                                     car->getDestinationTrack()->getTrackTypeName()));
                         }
                     }
                 }
             } else {
                 throw BuildFailedException(
                         tr("Car (%1) has staging destination (%2, %3) wrong track").arg(car->toString(),
                                 car->getDestinationName()).arg(car->getDestinationTrackName()));
              return false;
             }
         }
         addLine(_buildReport, FIVE, tr("Car (%1) can''t be delivered to (%2) id (%3) stop %4").arg(
                 car->toString()).arg(car->getDestinationName()).arg(rld->getId()).arg(locCount));
         if (car->getDestinationTrack() == NULL) {
            log->debug(tr("Could not find a destination track for location (%1)").arg(car->getDestinationName()));
         }
     }
    log->debug(tr("car (%1) not added to train").arg(car->toString()));
     addLine(_buildReport, FIVE, tr("Destination (%1) not reachable from location (%2) route id (%3)").arg(
             car->getDestinationName()).arg(rl->getName()).arg(rl->getId()));
     // remove destination and revert to /*final*/ destination
     if (car->getDestinationTrack() != NULL) {
         Track* destTrack = car->getDestinationTrack();
         // TODO should we leave the car's destination? The spur expects this car!
         if (destTrack->getSchedule() != NULL && destTrack->getScheduleMode() == Track::SEQUENTIAL) {
             //log->debug("Scheduled delivery to ("+destTrack->getName()+") cancelled");
             addLine(_buildReport, SEVEN, tr("Scheduled delivery to (%1, %2) cancelled").arg(
                     destTrack->getLocation()->getName()).arg(destTrack->getName()));
         }
     }
     car->setFinalDestination(car->getPreviousFinalDestination());
     car->setFinalDestinationTrack(car->getPreviousFinalDestinationTrack());
     car->setDestination(NULL, NULL);
     car->updateKernel();

     checkCarOrder(car);
     return true; // car no longer has a destination, but it had one.
 }

 /**
  * Find a destination for the car at a specified location.
  *
  * @param car the car!
  * @param rl The car's route location
  * @param rld The car's route destination
  * @return true if successful.
  * @throws BuildFailedException
  */
 /*private*/ bool TrainBuilder::findDestinationAndTrack(Car* car, RouteLocation* rl, RouteLocation* rld) //throws BuildFailedException
 {
     int index;
     for (index = 0; index < _routeList->size(); index++) {
         if (rld == _routeList->at(index)) {
             break;
         }
     }

     if (_routeList->size() == 1) {
         return findDestinationAndTrack(car, rl, index, index + 1);
     }
     return findDestinationAndTrack(car, rl, index - 1, index + 1);

 }

 /**
  * Find a destination and track for a car, and add the car to the train.
  *
  * @param car The car that is looking for a destination and destination
  *            track->
  * @param rl The current route location for this car.
  * @param routeIndex Where in the train's route to begin a search for a
  *            destination for this car.
  * @param routeEnd Where to stop looking for a destination.
  * @return true if successful, car has destination, track and a train.
  * @throws BuildFailedException
  */
 /*private*/ bool TrainBuilder::findDestinationAndTrack(Car* car, RouteLocation* rl, int routeIndex, int routeEnd)
         //throws BuildFailedException
 {
     if (routeIndex + 1 == routeEnd) {
        log->debug(tr("Car ({}) is at the last location in the train's route").arg(car->toString()));
     }
     addLine(_buildReport, FIVE, tr("Find destinations for (%1) type (%2) load (%3) at (%4)").arg(
             car->toString(), car->getTypeName(), car->getLoadName(),
             (car->getLocationName() + ", " + car->getTrackName())));
     if (car->getKernel() != NULL) {
         addLine(_buildReport, SEVEN, tr("Car (%1) is lead in kernel (%2) with %3 cars, %4 %5").arg(
                 car->toString()).arg(car->getKernelName()).arg(car->getKernel()->getSize()).arg(car->getKernel()->getTotalLength()).arg(
                 Setup::getLengthUnit().toLower()));
     }

     int start = routeIndex; // start looking after car's current location
     RouteLocation* rld = NULL; // the route location destination being checked for the car
     RouteLocation* rldSave = NULL; // holds the best route location destination for the car
     Track* trackSave = NULL; // holds the best track at destination for the car
     Track* finalDestinationTrackSave = NULL; // used when a spur has an alternate track and no schedule
     bool multiplePickup = false; // true when car can be picked up from two or more locations in the route

     // more than one location in this route?
     if (!_train->isLocalSwitcher()) {
         start++; // being looking for tracks at the next location
     } // all pick ups to terminal?
     if (_train->isSendCarsToTerminalEnabled()
             && splitString(rl->getName())!=(splitString(_departLocation->getName()))
             && routeEnd == _routeList->size()) {
         addLine(_buildReport, FIVE, tr("ending all car pick ups to terminal (%1)").arg(
                 _terminateLocation->getName()));
         // user could have specified several terminal locations with the "same" name
         start = routeEnd - 1;
         while (start > routeIndex) {
             if (splitString(_routeList->at(start - 1)->getName())!=(splitString(_terminateLocation->getName()))) {
                 break;
             }
             start--;
         }
     }
#if 1
     for (int k = start; k < routeEnd; k++) {
         rld = _routeList->at(k);
         // if car can be picked up later at same location, set flag
         if (checkForLaterPickUp(rl, rld, car)) {
             multiplePickup = true;
         }
         if (rld->isDropAllowed() || car->hasFred() || car->isCaboose()) {
             addLine(_buildReport, SEVEN, tr("Searching location (%1) for possible destination").arg(
                     rld->getName()));
         } else {
             addLine(_buildReport, SEVEN, tr("Route (%1) id (%2) no set outs at location (%3)").arg(
                     _train->getRoute()->getName()).arg(rld->getId()).arg(rld->getName()));
             continue;
         }
         if (_train->skipsLocation(rld->getId())) {
             addLine(_buildReport, FIVE, tr("Route location (%1) id (%2) is skipped by train (%3)").arg(
                     rld->getName()).arg(rld->getId()).arg(_train->getName()));
             continue;
         }
         // any moves left at this location?
         if (rld->getCarMoves() >= rld->getMaxCarMoves()) {
             addLine(_buildReport, FIVE, tr("No moves left for route (%1) id (%2) destination (%3)").arg(
                     _train->getRoute()->getName()).arg(rld->getId()).arg(rld->getName()));
             continue;
         }
         // get the destination
         Location* testDestination = rld->getLocation();
         if (testDestination == NULL) {
             // code check, should never throw, all locations in the route have been already checked
             throw BuildFailedException(tr("Route (%1) missing location (%2)").arg(
                     _train->getRoute()->getName()).arg(rld->getName()),"Normal");
          return false;
         }
         Track* trackTemp = NULL;
         Track* finalDestinationTrackTemp = NULL;

         // don't move car to same location unless the train is a switcher (local moves) or is passenger,
         // caboose or car with FRED
         if (splitString(rl->getName())==(splitString(rld->getName())) && !_train->isLocalSwitcher()
                 && !car->isPassenger() && !car->isCaboose() && !car->hasFred()) {
             // allow cars to return to the same staging location if no other options (tracks) are available
             if ((_train->isAllowReturnToStagingEnabled() || Setup::isAllowReturnToStagingEnabled())
                     && testDestination->isStaging() && trackSave == NULL) {
                 addLine(_buildReport, SEVEN, tr("Returning car (%1) to staging (%2), no other tracks available").arg(
                         car->toString()).arg(rld->getName()));
             } else {
                 addLine(_buildReport, SEVEN, tr("Car (%1) location is equal to destination (%2) skipping this destination").arg(
                         car->toString()).arg(rld->getName()));
                 continue;
             }
         }

         // check to see if departure track has any restrictions
         if (!car->getTrack()->acceptsDestination(testDestination)) {
             addLine(_buildReport, SEVEN, tr("Destination (%1) not serviced by departure track (%2)").arg(
                     testDestination->getName()).arg(car->getTrackName()));
             continue;
         }

         if (!testDestination->acceptsTypeName(car->getTypeName())) {
             addLine(_buildReport, SEVEN, tr("Can''t send (%1) type (%2) to destination (%3)").arg(
                     car->toString()).arg(car->getTypeName()).arg(testDestination->getName()));
             continue;
         }
         // can this location service this train's direction
         if (!checkDropTrainDirection(rld)) {
             continue;
         }
         // is the train length okay?
         if (!checkTrainLength(car, rl, rld)) {
             break; // done with this route
         }
         // no through traffic from origin to terminal?
         if (!_train->isAllowThroughCarsEnabled() && !_train->isLocalSwitcher() && !car->isCaboose() && !car->hasFred()
                 && !car->isPassenger()
                 && splitString(car->getLocationName())==(splitString(_departLocation->getName()))
                 && splitString(rld->getName())==(splitString(_terminateLocation->getName()))) {
             addLine(_buildReport, SEVEN, tr("Through traffic not allowed from (%1) to terminal (%2)").arg(
                     _departLocation->getName()).arg(_terminateLocation->getName()));
             continue;
         }
         // is there a track assigned for staging cars?
         if (rld == _train->getTrainTerminatesRouteLocation() && _terminateStageTrack != NULL) {
             // no need to check train and track direction into staging, already done
             QString status = car->testDestination(testDestination, _terminateStageTrack);
             if (status==(Track::OKAY)) {
                 trackTemp = _terminateStageTrack;
                 // only generate a new load if there aren't any other tracks available for this car
             } else if (status.startsWith(Track::LOAD)
                     && car->getTrack() == _departStageTrack
                     && car->getLoadName()==(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultEmptyName())
                     && rldSave == NULL
                     && (_departStageTrack->isAddCustomLoadsAnyStagingTrackEnabled()
                             || _departStageTrack->isAddCustomLoadsEnabled() || _departStageTrack
                                 ->isAddCustomLoadsAnySpurEnabled())) {
                 // try and generate a load for this car into staging
                 if (generateLoadCarDepartingAndTerminatingIntoStaging(car, _terminateStageTrack)) {
                     trackTemp = _terminateStageTrack;
                 } else {
                     addLine(_buildReport, SEVEN, tr("Can't send (%1) to %4 (%2) due to %3").arg(car->toString(),
                             _terminateStageTrack->getName()).arg(status).arg(_terminateStageTrack->getTrackTypeName()));
                     continue; // failed to create load
                 }
             } else {
                 addLine(_buildReport, SEVEN, tr("Can't send (%1) to %4 (%2) due to %3").arg(
                         car->toString()).arg(_terminateStageTrack->getName()).arg(status).arg(
                                 _terminateStageTrack->getTrackTypeName()));
                 continue;
             }
             // no staging track assigned, start track search
         } else {
             // first report if there are any alternate tracks
             foreach (Track* track, testDestination->getTrackByNameList(NULL)) {
                 if (track->isAlternate()) {
                     addLine(_buildReport, SEVEN, tr("Can''t send (%1) directly to alternate %2 (%3)").arg(
                             car->toString()).arg(track->getTrackTypeName()).arg(track->getName()));
                 }
             }
             foreach (Track* testTrack, testDestination->getTrackByMovesList(NULL)) {
                 //log->debug("track (" +testTrack->getName()+ ") has "+ testTrack->getMoves() + " moves");
                 // dropping to the same track isn't allowed
                 if (testTrack == car->getTrack() && !car->isPassenger() && !car->isCaboose() && !car->hasFred()) {
                     addLine(_buildReport, SEVEN, tr("Can't send car (%1) to same track (%2)").arg(car->toString()).arg(
                             testTrack->getName()));
                     continue;
                 }
                 // Can the train service this track?
                 if (!checkDropTrainDirection(car, rld, testTrack)) {
                     continue;
                 }
                 // drop to interchange or spur?
                 if (!checkTrainCanDrop(car, testTrack)) {
                     continue;
                 }
                 // report if track has planned pickups
                 if (testTrack->getIgnoreUsedLengthPercentage() > 0) {
                     // calculate the available space
                     int available = testTrack->getLength() - (testTrack->getUsedLength() + testTrack->getReserved());
                     int available2 = testTrack->getLength()
                             -
                             (testTrack->getUsedLength() * (100 - testTrack->getIgnoreUsedLengthPercentage()) / 100 + testTrack
                                     ->getReservedLengthDrops());
                     if (available2 > available) {
                         available = available2;
                     }
                     addLine(_buildReport, SEVEN, tr("Track (%1) planned pick ups %2%. Track length %3 %4, used %5 %4, reserved %6 %4, drops %7 %4, pulls %8 %4, available %9 %4").arg(testTrack->getName()).arg(
                             testTrack->getIgnoreUsedLengthPercentage()).arg(testTrack->getLength()).arg(
                             Setup::getLengthUnit().toLower()).arg(testTrack->getUsedLength()).arg(
                             testTrack->getReserved()).arg(testTrack->getReservedLengthDrops()).arg(
                             testTrack->getReservedLengthDrops() - testTrack->getReserved()).arg(available));
                 }
                 QString status = car->testDestination(testDestination, testTrack);
                 // Could be a caboose or car with FRED with a custom load
                 // is the destination a spur with a schedule demanding this car's custom load?
                 if (status==(Track::OKAY) && testTrack->getScheduleId()!=(Track::NONE)
                         && car->getLoadName()!=(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultEmptyName())
                         && car->getLoadName()!=(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultLoadName())) {
                     addLine(_buildReport, FIVE, tr("Spur (%1) has schedule requesting car load (%2)").arg(
                             testTrack->getName()).arg(car->getLoadName()));
                     addCarToTrain(car, rl, rld, testTrack);
                     return true;
                 }
                 // is the destination a spur with a Schedule?
                 // and is car departing a staging track that can generate schedule loads?
                 // alternate track isn't checked
                 if (status!=(Track::OKAY)
                         && !status.startsWith(Track::TYPE) // wrong car type for this spur
                         &&
                         !status.startsWith(Track::LENGTH) // can't generate load for spur that is full
                         &&
                         !status.startsWith(Track::CAPACITY) // can't use a spur that is too short
                         &&
                         testTrack->getTrackType()==(Track::SPUR)
                         &&
                         testTrack->getScheduleId()!=(Track::NONE)
                         &&
                         (car->getTrack()->isAddCustomLoadsEnabled() || car->getTrack()
                                 ->isAddCustomLoadsAnySpurEnabled())
                         &&
                         car->getLoadName()==(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultEmptyName())) {
                     // can we use this track?
                     if (!testTrack->isSpaceAvailable(car)) {
                         addLine(_buildReport, SEVEN, tr("Car (%1) would overload track (%2, %3), currently %4 inbound cars, length (%5) %6, %7% loading from staging").arg(car->toString()).arg(
                                 testTrack->getLocation()->getName()).arg(testTrack->getName()).arg(
                                 testTrack->getNumberOfCarsInRoute()).arg(testTrack->getReservedInRoute()).arg(
                                 Setup::getLengthUnit().toLower()).arg(testTrack->getReservationFactor()));
                         continue; // no
                     }
                     addLine(_buildReport, SEVEN, tr("Generate load for (%1) type (%2) destination (%3, %4)").arg(
                             car->toString()).arg(car->getTypeName()).arg(testDestination->getName(),
                                     testTrack->getName()));
                     QString carLoad = car->getLoadName(); // save the car's load
                     ScheduleItem* si = getScheduleItem(car, testTrack);
                     if (si != NULL) {
                         car->setLoadName(si->getReceiveLoadName());
                         if (car->testDestination(testDestination, testTrack)==(Track::OKAY)) {
                             addLine(_buildReport, FIVE, tr("Adding custom load (%1) to car (%2)").arg(si->getReceiveLoadName()).arg(
                                     car->toString()));
                             car->setLoadGeneratedFromStaging(true);
                             testTrack->bumpSchedule();
                             addCarToTrain(car, rl, rld, testTrack);
                             return true;
                         }
                     }
                     car->setLoadName(carLoad); // restore car's load (default empty)
                 }
                 // check to see if alternate track is available if track full and no schedule
                 if (status.startsWith(Track::LENGTH) && testTrack->getAlternateTrack() != NULL
                         && car->getFinalDestination() == NULL && testTrack->getScheduleId()==(Track::NONE)
                         && car->getTrack() != testTrack->getAlternateTrack()
                         && car->testDestination(testDestination, testTrack->getAlternateTrack())==(Track::OKAY)) {
                     addLine(_buildReport, SEVEN, tr("Spur (%1, %2) full, has alternate track (%3)").arg(testDestination->getName()).arg(
                             testTrack->getName(), testTrack->getAlternateTrack()->getName()));
                     finalDestinationTrackTemp = testTrack;
                     trackTemp = testTrack->getAlternateTrack(); // send car to alternate track
                     break;
                 }
                 // okay to drop car?
                 if (status!=(Track::OKAY)) {
                     addLine(_buildReport, SEVEN, tr("Can''t send (%1) to %4 (%2) due to %3").arg(car->toString()).arg(
                             testTrack->getName()).arg(status).arg(testTrack->getTrackTypeName()));
                     continue;
                 }
                 // No local moves from spur to spur
                 if (_train->isLocalSwitcher() && !Setup::isLocalSpurMovesEnabled()
                         && testTrack->getTrackType()==(Track::SPUR)
                         && car->getTrack()->getTrackType()==(Track::SPUR)) {
                     addLine(_buildReport, SEVEN, tr("Local spur (%1) to spur (%2) move not allowed ").arg(
                             car->getTrackName()).arg(testTrack->getName()));
                     continue;
                 }
                 // No local moves from yard to yard
                 if (_train->isLocalSwitcher() && !Setup::isLocalYardMovesEnabled()
                         && testTrack->getTrackType()==(Track::YARD)
                         && car->getTrack()->getTrackType()==(Track::YARD)
                         && !car->isCaboose()
                         && !car->hasFred()) {
                     addLine(_buildReport, SEVEN, tr("Local yard (%1) to yard (%2) move not allowed").arg(
                             car->getTrackName()).arg(testTrack->getName()));
                     continue;
                 }
                 // No local moves from interchange to interchange
                 if (_train->isLocalSwitcher() && !Setup::isLocalInterchangeMovesEnabled()
                         && testTrack->getTrackType()==(Track::INTERCHANGE)
                         && car->getTrack()->getTrackType()==(Track::INTERCHANGE)) {
                     addLine(_buildReport, SEVEN, tr("Local classification/interchange (%1) to C/I (%2) move not allowed").arg(car->getTrackName()).arg(
                             testTrack->getName()));
                     continue;
                 }

                 // not staging, then use (should never be staging TODO throw an exception)
                 if (testTrack->getTrackType()!=(Track::STAGING)) {
                     trackTemp = testTrack;
                     break;
                 }
             }
         }
         // did we find a new destination?
         if (trackTemp != NULL) {
             addLine(_buildReport, FIVE, tr("Car (%1) can go to %2 (%3, %4) %5/%6 moves used").arg(
                     car->toString()).arg(trackTemp->getTrackTypeName()).arg(trackTemp->getLocation()->getName()).arg(
                             trackTemp->getName()).arg(+rld->getCarMoves()).arg(rld->getMaxCarMoves()));
             if (rldSave == NULL && multiplePickup) {
                 addLine(_buildReport, FIVE, tr("Car (%1) can be picked up later from location (%2)").arg(
                         car->toString()).arg(car->getLocationName()));
                 trackSave = NULL;
                 break; // done
             }
             // if there's more than one available destination use the one with the least moves
             if (rldSave != NULL) {
                 double saveCarMoves = rldSave->getCarMoves();
                 double saveRatio = saveCarMoves / rldSave->getMaxCarMoves();
                 double nextCarMoves = rld->getCarMoves();
                 double nextRatio = nextCarMoves / rld->getMaxCarMoves();
                 // bias cars to the terminal
                 if (rld == _train->getTrainTerminatesRouteLocation()) {
                     nextRatio = nextRatio * nextRatio;
                    log->debug(tr("Location (%1) is terminate location, adjusted nextRatio %2").arg(rld->getName()).arg(nextRatio));
                 }
                 // bias cars with default loads to a track with a schedule
                 if (trackTemp->getScheduleId()!=(Track::NONE)) {
                     nextRatio = nextRatio * nextRatio;
                    log->debug(tr("Track (%1) has schedule (%2), adjusted nextRatio %3").arg(
                             trackTemp->getName()).arg(trackTemp->getScheduleName()).arg(nextRatio));
                 }
                 // check for an earlier drop in the route
                 for (int m = start; m < routeEnd; m++) {
                     RouteLocation* rle = _routeList->at(m);
                     if (rle == rld) {
                         break; // done
                     }
                     if (rle->getName()==(rld->getName()) && (rle->getMaxCarMoves() - rle->getCarMoves() > 0)
                             && rle->isDropAllowed() && checkDropTrainDirection(car, rle, trackTemp)) {
                        log->debug(tr("Found an earlier drop for car (%1) destination (%2)").arg(car->toString()).arg(rle
                                 ->getName())); // NOI18N
                         nextCarMoves = rle->getCarMoves();
                         nextRatio = nextCarMoves / rle->getMaxCarMoves();
                         rld = rle; // set car drop to earlier stop
                         break;
                     }
                 }
                log->debug(tr("%1 = %2, %3 = %4").arg(rldSave->getName()).arg(saveRatio).arg(rld->getName()).arg(nextRatio));
                 if (saveRatio < nextRatio) {
                     rld = rldSave; // the saved is better than the last found
                     trackTemp = trackSave;
                     finalDestinationTrackTemp = finalDestinationTrackSave;
                 } else if (multiplePickup) {
                     addLine(_buildReport, FIVE, tr("Car (%1) can be picked up later from location (%2)").arg(
                             car->toString()).arg(car->getLocationName()));
                     trackSave = NULL;
                     break; // done
                 }
             }
             // every time through, save the best route destination, and track
             rldSave = rld;
             trackSave = trackTemp;
             finalDestinationTrackSave = finalDestinationTrackTemp;
         } else {
             addLine(_buildReport, FIVE, tr("Could not find a track for (%1) at destination (%2)").arg(
                     car->toString()).arg(rld->getName()));
         }
     }
     // did we find a destination?
     if (trackSave != NULL) {
         if (finalDestinationTrackSave != NULL) {
             car->setFinalDestination(finalDestinationTrackSave->getLocation());
             car->setFinalDestinationTrack(finalDestinationTrackSave);
         }
         addCarToTrain(car, rl, rldSave, trackSave);
         return true;
     }
#endif
     checkCarOrder(car);
     return false; // no build errors, but car not given destination
 }

 /**
  * Returns true if car can be picked up later in a train's route
  */
 /*private*/ bool TrainBuilder::checkForLaterPickUp(RouteLocation* rl, RouteLocation* rld, Car* car)
 {
     if (rl != rld && rld->getName()==(car->getLocationName())) {
         // don't delay adding a caboose, passenger car, or car with FRED
         if (car->isCaboose() || car->isPassenger() || car->hasFred()) {
             return false;
         }
         // no later pick up if car is departing staging
         if (car->getLocation()->isStaging()) {
             return false;
         }
         if (!checkPickUpTrainDirection(car, rld)) {
             addLine(_buildReport, SEVEN, tr("Later pick up for car (%1) from location (%2) route id (%3) not possible due to train direction ").arg(
                     car->toString()).arg(rld->getName()).arg(rld->getId()));
             return false;
         }
         if (!rld->isPickUpAllowed()) {
             addLine(_buildReport, SEVEN, tr("Later pick up for car (%1) from location (%2) route id (%3) not possible, no pick ups allowed").arg(
                     car->toString()).arg(rld->getName()).arg(rld->getId()));
             return false;
         }
         if (rld->getMaxCarMoves() - rld->getCarMoves() <= 0) {
             addLine(_buildReport, SEVEN, tr("Later pick up for car (%1) from location (%2) route id (%3) not possible, no moves available").arg(
                     car->toString()).arg(rld->getName()).arg(rld->getId()));
             return false;
         }
         //log->debug("Car ({}) can be picked up later!", car->toString());
         addLine(_buildReport, SEVEN, tr("buildPickupLaterOkay").arg(
                 car->toString(), rld->getName(), rld->getId()));
         return true;
     }
     return false;
 }

 /**
  * Creates a car load for a car departing staging and terminating into
  * staging.
  *
  * @param car the car!
  * @param stageTrack the staging track the car will terminate to
  * @return true if a load was generated this this car.
  */
 /*private*/ bool TrainBuilder::generateLoadCarDepartingAndTerminatingIntoStaging(Car* car, Track* stageTrack) {
     if (stageTrack == NULL || stageTrack->getTrackType()!=(Track::STAGING)
             || !stageTrack->acceptsTypeName(car->getTypeName()) || !stageTrack->acceptsRoadName(car->getRoadName())) {
        log->debug("Track doesn't service car");
         return false;
     }
     // Departing and returning to same location in staging?
     if (!_train->isAllowReturnToStagingEnabled() && !Setup::isAllowReturnToStagingEnabled() && !car->isCaboose()
             && !car->hasFred() && !car->isPassenger()
             && splitString(car->getLocationName())==(splitString(stageTrack->getLocation()->getName()))) {
        log->debug("Returning car to staging not allowed");
         return false;
     }
     // figure out which loads the car can use
     QStringList loads = ((CarLoads*)InstanceManager::getDefault("CarLoads"))->getNames(car->getTypeName());
     // remove the default names
     loads.removeOne(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultEmptyName());
     loads.removeOne(((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultLoadName());
     if (loads.size() == 0) {
        log->debug(tr("No custom loads for car type (%1) ignoring staging track (%2)").arg(car->getTypeName()).arg(stageTrack
                 ->getName()));
         return false;
     }
     addLine(_buildReport, SEVEN, tr("Generate load for (%1) type (%2) load (%3) at (%4, %5) to staging (%6, %7)").arg(
             car->toString()).arg(car->getTypeName()).arg(car->getLoadName()).arg(car->getLocationName(),
                     car->getTrackName()).arg(stageTrack->getLocation()->getName()).arg(stageTrack->getName()));
     for (int i = loads.size() - 1; i >= 0; i--) {
         QString load = loads.at(i);
         if (!car->getTrack()->shipsLoad(load, car->getTypeName()) || !stageTrack->acceptsLoad(load, car->getTypeName())
                 || !_train->acceptsLoad(load, car->getTypeName())) {
             if (!car->getTrack()->shipsLoad(load, car->getTypeName())) {
                 addLine(_buildReport, SEVEN, tr("Departure track (%1) can't ship load (%2) to destination (%3, %4)").arg(
                         car->getTrackName()).arg(load).arg(stageTrack->getLocation()->getName(),
                                 stageTrack->getName()));
             }
             if (!stageTrack->acceptsLoad(load, car->getTypeName())) {
                 addLine(_buildReport, SEVEN, tr("Destination (%1, %2) will not accept car (%3) with load (%4)").arg(
                         stageTrack->getLocation()->getName()).arg(stageTrack->getName()).arg(car->toString()).arg(
                                 load));
             }
             if (!_train->acceptsLoad(load, car->getTypeName())) {
                 addLine(_buildReport, SEVEN, tr("Train (%1) doesn''t service load (%2) destination (%3, %4)").arg(
                         _train->getName()).arg(load).arg(stageTrack->getLocation()->getName(),
                                 stageTrack->getName()));

             }
             loads.removeAt(i);
         }
     }
     // Use random loads rather that the first one that works to create interesting loads
     if (loads.size() > 0) {
         QString oldLoad = car->getLoadName(); // save load in case we fail
         int rnd = (int) (qrand() * loads.size());
         car->setLoadName(loads.at(rnd));
         // check to see if car is now accepted by staging
         QString status = car->testDestination(stageTrack->getLocation(), stageTrack); // will staging accept this car?
         if (status==(Track::OKAY) || (status.startsWith(Track::LENGTH) && stageTrack != _terminateStageTrack)) {
             car->setLoadGeneratedFromStaging(true);
             car->setFinalDestination(stageTrack->getLocation());
             car->setFinalDestinationTrack(NULL); // don't assign the track, that will be done later
             car->updateKernel(); // is car part of kernel?
             addLine(_buildReport, SEVEN, tr("Adding custom load (%1) to car (%2)").arg(
                     car->getLoadName()).arg(car->toString()));
             return true;
         }
         car->setLoadName(oldLoad); // restore load and report failure
         addLine(_buildReport, SEVEN, tr("Can't send (%1) to %4 (%2) due to %3").arg(
                 car->toString()).arg(stageTrack->getName()).arg(status).arg(stageTrack->getTrackTypeName()));
     }
     addLine(_buildReport, SEVEN, tr("Could not generate a custom load for car (%1) departing (%2) to staging (%3, %4)").arg(
             car->toString()).arg(car->getTrackName()).arg(stageTrack->getLocation()->getName()).arg(stageTrack->getName()));
     return false;
 }

 /**
  * Checks to see if cars that are already in the train can be redirected
  * from the alternate track to the spur that really wants the car. Fixes the
  * issue of having cars placed at the alternate when the spur's cars get
  * pulled by this train, but cars were sent to the alternate because the
  * spur was full at the time it was tested.
  *
  * @param rl
  * @return true if one or more cars were redirected
  */
 /*private*/ bool TrainBuilder::redirectCarsFromAlternateTrack() {
     if (!Setup::isBuildAggressive()) {
         return false;
     }
     bool redirected = false;
     QList<RollingStock*>* cars = carManager->getByTrainList(_train);
     foreach (RollingStock* rs, *cars) {
         Car* car = (Car*) rs;
         // does the car have a /*final*/ destination and the destination is this one?
         if (car->getFinalDestination() == NULL || car->getFinalDestinationTrack() == NULL
                 || car->getFinalDestinationName()!=(car->getDestinationName())) {
             continue;
         }
        log->debug(tr("Car (%1) destination track (%2) has final destination track (%3) location (%4)").arg(car->toString(),
                 car->getDestinationTrackName()).arg(car->getFinalDestinationTrackName()).arg(car->getDestinationName())); // NOI18N
         // is the car in a kernel?
         if (car->getKernel() != NULL && !car->getKernel()->isLead(car)) {
             continue;
         }
         if (car->testDestination(car->getFinalDestination(), car->getFinalDestinationTrack())==(Track::OKAY)) {
             Track* alternate = car->getFinalDestinationTrack()->getAlternateTrack();
             if (alternate != NULL
                     && car->getDestinationTrack() == alternate
                     && (alternate->getTrackType()==(Track::YARD) || alternate->getTrackType()==(
                             Track::INTERCHANGE))
                     && checkDropTrainDirection(car, car->getRouteDestination(), car->getFinalDestinationTrack())
                     && checkTrainCanDrop(car, car->getFinalDestinationTrack())) {
                log->debug(tr("Car (%1) alternate track (%2) can be redirected to final destination track (%3)").arg(car
                         ->toString()).arg(car->getDestinationTrackName()).arg(car->getFinalDestinationTrackName()));
                 if (car->getKernel() != NULL) {
                     foreach (Car* k, car->getKernel()->getCars()) {
                         addLine(_buildReport, FIVE, tr("Spur (%1, %2) now has room, redirecting car (%3) from alternate (%4)").arg(
                                 car->getFinalDestinationName()).arg(car->getFinalDestinationTrackName()).arg(k->toString(),
                                 car->getDestinationTrackName()));
                         k->setDestination(car->getFinalDestination(),car->getFinalDestinationTrack());
                     }
                 } else {
                     addLine(_buildReport, FIVE, tr("Spur (%1, %2) now has room, redirecting car (%3) from alternate (%4)").arg(
                             car->getFinalDestinationName()).arg(car->getFinalDestinationTrackName()).arg(car->toString(),
                             car->getDestinationTrackName()));
                     car->setDestination(car->getFinalDestination(), car->getFinalDestinationTrack());
                 }
                 redirected = true;
             }
         }
     }
     return redirected;
 }

 // report any cars left at location
 /*private*/ void TrainBuilder::reportCarsNotMoved(RouteLocation* rl, int percent) {
     // only report if requested moves completed and /*final*/ pass
     if (!_success || percent != 100) {
         return;
     }
     if (_carIndex < 0) {
         _carIndex = 0;
     }
     // cars up this point have build report messages, only show the cars that aren't in the build report
     int numberCars = 0;
     for (int i = _carIndex; i < _carList->size(); i++) {
         if (numberCars == DISPLAY_CAR_LIMIT_100) {
             addLine(_buildReport, FIVE, tr("********** Only the first %1 cars are shown for (%2) **********").arg(
                     numberCars).arg(rl->getName()));
             break;
         }

         Car* car = _carList->at(i);
         // find a car at this location that hasn't been given a destination
         if (car->getLocationName()!=(rl->getName()) || car->getRouteDestination() != NULL) {
             continue;
         }
         if (numberCars == 0) {
             addLine(_buildReport, SEVEN, tr("The following cars were ignored, requested moves for location (%1) completed").arg(
                     rl->getName()));
         }
         addLine(_buildReport, SEVEN, tr("Car (%1) type (%2) load (%3) at (%4, %5)").arg(
                 car->toString()).arg(car->getTypeName()).arg(car->getLoadName()).arg(car->getLocationName()).arg(car->getTrackName()));
         numberCars++;
     }
     addLine(_buildReport, SEVEN, BLANK_LINE);
 }

 /**
  * Checks to see if the engine assigned to the train has the appropriate HP.
  * If the train's HP requirements are significantly higher or lower than the
  * engine that was assigned, the program will search for a more appropriate
  * engine, and assign that engine to the train.
  *
  * The HP calculation is based on a minimum train speed of 36 MPH. The
  * formula HPT x 12 / % Grade = Speed, is used to determine the horsepower
  * required. Speed is fixed at 36 MPH. For example a 1% grade requires a
  * minimum of 3 HPT.
  */
 /*private*/ void TrainBuilder::checkEngineHP() //throws BuildFailedException
 {
     if (_train->getNumberEngines()!=(Train::AUTO_HPT) ||
             Setup::getHorsePowerPerTon() == 0 ||
             _departStageTrack != NULL)
         return;
     // there should be at lease one engine assigned to this train
     Engine* leadEngine = _train->getLeadEngine();
     if (leadEngine == NULL)
         return; // TODO throw an exception
     addLine(_buildReport, ONE, BLANK_LINE);
     addLine(_buildReport, ONE, tr("Determine if assigned loco (%1) has the appropriate HP (%2) based on %3 HP per ton and the route grades").arg(
             leadEngine->toString()).arg(leadEngine->getHp()).arg(Setup::getHorsePowerPerTon()));
     // now determine the HP needed for this train
     int hpNeeded = 0;
     int hpAvailable = 0;
     Route* route = _train->getRoute();
     if (route != NULL) {
         bool helper = false;
         foreach (RouteLocation* rl, *route->getLocationsBySequenceList()) {
             if ((_train->getSecondLegOptions() == Train::HELPER_ENGINES && rl == _train->getSecondLegStartLocation())
                     || (_train->getThirdLegOptions() == Train::HELPER_ENGINES && rl == _train
                             ->getThirdLegStartLocation())) {
                 addLine(_buildReport, FIVE, tr("Add helpers at %1").arg(
                         rl->getName()));
                 helper = true;
             }
             if ((_train->getSecondLegOptions() == Train::HELPER_ENGINES && rl == _train->getSecondLegEndLocation())
                     || (_train->getThirdLegOptions() == Train::HELPER_ENGINES && rl == _train
                             ->getThirdLegEndLocation())) {
                 addLine(_buildReport, FIVE, tr("Remove helpers at %1").arg(
                         rl->getName()));
                 helper = false;
             }
             if (helper) {
                 continue; // ignore HP needed when helpers are assigned to the train
             }
             // check for a change of engines in the train's route
             if (((_train->getSecondLegOptions() & Train::CHANGE_ENGINES) == Train::CHANGE_ENGINES && rl == _train
                     ->getSecondLegStartLocation())
                     ||
                     ((_train->getThirdLegOptions() & Train::CHANGE_ENGINES) == Train::CHANGE_ENGINES && rl == _train
                             ->getThirdLegStartLocation())) {
                log->debug(tr("Loco change at (%1)").arg(rl->getName()));
                 break; // done
             }
             if (_train->getTrainHorsePower(rl) > hpAvailable)
                 hpAvailable = _train->getTrainHorsePower(rl);
             int weight = rl->getTrainWeight();
             int hpRequired = (int) ((36 * rl->getGrade() / 12) * weight);
             if (hpRequired < Setup::getHorsePowerPerTon() * weight)
                 hpRequired = Setup::getHorsePowerPerTon() * weight; // minimum HPT
             if (hpRequired > hpNeeded) {
                 addLine(_buildReport, SEVEN, tr("Train weight %1 tons, %2 cars, grade %3% departing (%4) id (%5) requires %6 HP").arg(
                         weight).arg(_train->getNumberCarsInTrain(rl)).arg(rl->getGrade()).arg(rl->getName()).arg(rl->getId()).arg(hpRequired));
                 hpNeeded = hpRequired;
             }
         }
     }
     if (hpNeeded > hpAvailable) {
         addLine(_buildReport, ONE, tr("Assigned loco (%1) HP (%2) doesn''t meet train requirements (%3) HP, removing loco from train").arg(
                 leadEngine->toString()).arg(hpAvailable).arg(hpNeeded));
         findNewEngine(hpNeeded, leadEngine);
     } else if (hpAvailable > 2 * hpNeeded) {
         addLine(_buildReport, ONE, tr("Assigned loco (%1) HP (%2) exceeds train requirements (%3) HP, removing loco from train").arg(
                 leadEngine->toString()).arg(hpAvailable).arg(hpNeeded));
         findNewEngine(hpNeeded, leadEngine);
     } else {
        log->debug(tr("Keeping engine (%1 it meets the train's HP requirement").arg(leadEngine->toString()));
     }
 }

 /*private*/ void TrainBuilder::findNewEngine(int hpNeeded, Engine* leadEngine) //throws BuildFailedException
{
     // save lead engine's rl, and rld
     RouteLocation* rl = leadEngine->getRouteLocation();
     RouteLocation* rld = leadEngine->getRouteDestination();
     leadEngine->reset(); // remove this engine from the train
     _engineList.insert(0, leadEngine); // put engine back into the pool
     _train->setLeadEngine(NULL);

     int hpMax = hpNeeded;
     // largest single engine HP known today is less than 15,000
     bool bRun = true;
     hpLoop: while (hpMax < 20000 && bRun)
     {
         hpMax += hpNeeded / 2; // start off looking for an engine with no more than 50% extra HP
        log->debug(tr("Max hp %1").arg(hpMax));
         foreach (Engine* engine, _engineList) {
             if (engine->getLocation() != _train->getTrainDepartsRouteLocation()->getLocation())
                 continue;
             int engineHp = engine->getHpInteger();
             if (engineHp > hpNeeded && engineHp <= hpMax) {
                log->debug(tr("Loco (%1) has the required HP (%2)").arg(engine->toString()).arg(engine->getHp()));
                 if (setLocoDestination(engine, rl, rld, NULL))
                     //break hpLoop;
                  bRun = false;
                  break;
             }
         }
     }
     if (_train->getLeadEngine() == NULL && !_train->isBuildConsistEnabled()) {
         throw BuildFailedException(tr("ERROR could not find a locomotive that meets the train's HP requirements"));
     }
 }

 /**
  * Checks to see if additional engines are needed for the train based on the
  * train's calculated tonnage. Minimum speed for the train is fixed at 36
  * MPH. The formula HPT x 12 / % Grade = Speed, is used to determine the
  * horsepower needed. For example a 1% grade requires a minimum of 3 HPT.
  *
  * @throws BuildFailedException
  */
 /*private*/ void TrainBuilder::checkNumnberOfEnginesNeeded() //throws BuildFailedException
{
     if (_reqNumEngines == 0 || !_train->isBuildConsistEnabled() || Setup::getHorsePowerPerTon() == 0) {
         return;
     }
     addLine(_buildReport, ONE, BLANK_LINE);
     addLine(_buildReport, ONE, tr("Determine if train requires additional locos based on %1 HP per ton and the route grades").arg(Setup
             ::getHorsePowerPerTon()));
     Route* route = _train->getRoute();
     int hpAvailable = 0;
     int extraHpNeeded = 0;
     RouteLocation* rlNeedHp = NULL;
     RouteLocation* rlStart = _train->getTrainDepartsRouteLocation();
     RouteLocation* rlEnd = _train->getTrainTerminatesRouteLocation();
     if (route != NULL) {
         bool helper = false;
         foreach (RouteLocation* rl, *route->getLocationsBySequenceList()) {
             if ((_train->getSecondLegOptions() == Train::HELPER_ENGINES && rl == _train->getSecondLegStartLocation())
                     || (_train->getThirdLegOptions() == Train::HELPER_ENGINES && rl == _train
                             ->getThirdLegStartLocation())) {
                 addLine(_buildReport, FIVE, tr("Add helpers at %1").arg(
                         rl->getName()));
                 helper = true;
             }
             if ((_train->getSecondLegOptions() == Train::HELPER_ENGINES && rl == _train->getSecondLegEndLocation())
                     || (_train->getThirdLegOptions() == Train::HELPER_ENGINES && rl == _train
                             ->getThirdLegEndLocation())) {
                 addLine(_buildReport, FIVE, tr("Remove helpers at %1").arg(
                         rl->getName()));
                 helper = false;
             }
             if (helper) {
                 continue;
             }
             // check for a change of engines in the train's route
             if (((_train->getSecondLegOptions() & Train::CHANGE_ENGINES) == Train::CHANGE_ENGINES && rl == _train
                     ->getSecondLegStartLocation())
                     ||
                     ((_train->getThirdLegOptions() & Train::CHANGE_ENGINES) == Train::CHANGE_ENGINES && rl == _train
                             ->getThirdLegStartLocation())) {
                log->debug(tr("Loco change at (%1)").arg(rl->getName()));
                 addLocos(hpAvailable, extraHpNeeded, rlNeedHp, rlStart, rl);
                 // reset for next leg of train's route
                 rlStart = rl;
                 rlNeedHp = NULL;
                 extraHpNeeded = 0;
             }
             int weight = rl->getTrainWeight();
             if (weight > 0) {
                 double hptMinimum = Setup::getHorsePowerPerTon();
                 double hptGrade = (36 * rl->getGrade() / 12);
                 int hp = _train->getTrainHorsePower(rl);
                 int hpt = hp / weight;
                 if (hptGrade > hptMinimum) {
                     hptMinimum = hptGrade;
                 }
                 if (hptMinimum > hpt) {
                     int addHp = (int) (hptMinimum * weight - hp);
                     if (addHp > extraHpNeeded) {
                         hpAvailable = hp;
                         extraHpNeeded = addHp;
                         rlNeedHp = rl;
                     }
                     addLine(_buildReport, SEVEN, tr("Train weight %1 tons, (%2) HP assigned, grade %3%, required HPT %5 at (%6) id (%7)").arg(
                             weight).arg(hp).arg(rl->getGrade()).arg(hpt).arg(hptMinimum).arg(rl->getName()).arg(rl->getId()));
                     addLine(_buildReport, FIVE, tr("Train requires %1 additional HP at (%2) to meet the requirement of %3 HPT").arg(
                             addHp).arg(rl->getName()).arg(hptMinimum));
                 }
             }
         }
     }
     addLocos(hpAvailable, extraHpNeeded, rlNeedHp, rlStart, rlEnd);
     addLine(_buildReport, SEVEN, tr("buildDoneAssingEnginesTrain").arg(
             _train->getName()));
     addLine(_buildReport, THREE, BLANK_LINE);
 }

 /*private*/ void TrainBuilder::addLocos(int hpAvailable, int extraHpNeeded, RouteLocation* rlNeedHp, RouteLocation* rl,
         RouteLocation* rld) //throws BuildFailedException
{
     if (rlNeedHp == NULL) {
         return;
     }
     int numberLocos = 0;
     // determine how many locos have already been assigned to the train
     QList<RollingStock*>* engines = ((EngineManager*)InstanceManager::getDefault("EngineManager"))->getList(_train);
     foreach (RollingStock* rs,  *engines) {
         if (rs->getRouteLocation() == rl) {
             numberLocos++;
         }
     }
     addLine(_buildReport, ONE, tr("Train requires %1 additional HP at (%2) destination (%3) %4 locos already assigned, add locos:").arg(
             extraHpNeeded).arg(rlNeedHp->getName()).arg(rld->getName()).arg(numberLocos));
     while (numberLocos < Setup::getMaxNumberEngines()) {
         if (!getEngines(1, _train->getEngineModel(), _train->getEngineRoad(), rl, rld)) {
             throw BuildFailedException(tr("Train requires %1 loco(s), could not pick up at departure (%2) or set out at (%3)").arg(
                     tr("additional")).arg(rl->getName()).arg(rld->getName()),"Normal");
         }
         numberLocos++;
         int currentHp = _train->getTrainHorsePower(rlNeedHp);
         if (currentHp > hpAvailable + extraHpNeeded) {
             break; // done
         }
         if (numberLocos < Setup::getMaxNumberEngines()) {
             addLine(_buildReport, SEVEN, tr("Train requires %1 additional HP at (%2) destination (%3) %4 locos in consist, continue adding locos:").arg(
                     (hpAvailable + extraHpNeeded - currentHp)).arg(rlNeedHp->getName()).arg(rld->getName()).arg(
                             numberLocos));
         } else {
             addLine(_buildReport, SEVEN, tr("The maximum number of locos allowed (%1) have been assigned to this train").arg(
                     Setup::getMaxNumberEngines()));
         }
     }
 }

 /*private*/ void TrainBuilder::buildFailed(/*BuildFailedException e*/QString msg, QString type)
 {
  //QString msg = e->getMessage();
  _train->setBuildFailedMessage(msg);
  _train->setStatus(Train::CODE_BUILD_FAILED);
  _train->setBuildFailed(true);
  if (log->isDebugEnabled()) {
     log->debug(msg);
  }
  if (((TrainManager*)InstanceManager::getDefault("TrainManager"))->isBuildMessagesEnabled()) {
//         if (e->getExceptionType()==(BuildFailedException.NORMAL)) {
//             JOptionPane.showMessageDialog(NULL, msg, tr("buildErrorMsg"),
//                     _train->getName(), _train->getDescription()}), JOptionPane.ERROR_MESSAGE);
   if(type == "Normal")
   {
    //QMessageBox::critical(NULL, tr("Can not build train (%1) %2").arg(_train->getName()).arg(_train->getDescription()), msg);
    emit error( tr("Can not build train (%1) %2").arg(_train->getName()).arg(_train->getDescription()), msg);
   }
   else
   {
    // build error, could not find destinations for cars departing staging
//             Object[] options = {tr("buttonRemoveCars"), "OK"};
//             int results = JOptionPane.showOptionDialog(NULL, msg, Bundle
//                     ->getMessage("buildErrorMsg").arg(_train->getName(), _train->getDescription()}),
//                     JOptionPane.DEFAULT_OPTION, JOptionPane.ERROR_MESSAGE, NULL, options, options[1]);
    int results = QMessageBox::critical(NULL, tr("Can not build train (%1) %2").arg(_train->getName()).arg(_train->getDescription()), tr("Remove Cars"), QMessageBox::Ok | QMessageBox::Cancel);
    if (results == QMessageBox::Ok) {
       log->debug("User requested that cars be removed from staging track");
        removeCarsFromStaging();
    }
   }
   int size = carManager->getList(_train)->size();
   if (size > 0)
   {
//             if (JOptionPane.showConfirmDialog(NULL, tr("buildCarsResetTrain"),
//                     size, _train->getName()}), tr("buildResetTrain"),
//                     JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
    if(QMessageBox::question(NULL, tr("Reset Train?"), tr("%1 cars have been assigned to train (%2), do you want to release the cars by reset?").arg(size).arg(_train->getName()), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
     _train->reset();
    }
   }
   else if ((size = engineManager->getList(_train)->size()) > 0)
   {
//             if (JOptionPane.showConfirmDialog(NULL, tr("buildEnginesResetTrain"),
//                     size, _train->getName()}), tr("buildResetTrain"),
//                     JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
    if(QMessageBox::question(NULL, tr("Reset Train?"), tr("%1 engines have been assigned to train (%2), do you want to release the engines by reset?").arg(size).arg(_train->getName()), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
     _train->reset();
    }
   }
  }
  if (_buildReport != NULL)
  {
   addLine(_buildReport, ONE, msg);
   // Write to disk and close buildReport
   addLine(_buildReport, ONE, tr("Build failed for train (%1)").arg(_train
           ->getName()));
   _buildReport->flush();
   _buildReport->close();
  }
 }

/*private*/ void TrainBuilder::buildFailed(BuildFailedException e)
{
 QString msg = e.getMessage();
 _train->setBuildFailedMessage(msg);
 _train->setStatus(Train::CODE_BUILD_FAILED);
 _train->setBuildFailed(true);
 log->debug(msg);

 if (((TrainManager*)InstanceManager::getDefault("TrainManager"))->isBuildMessagesEnabled())
 {
  if (e.getExceptionType() ==(BuildFailedException::NORMAL))
  {
   JOptionPane::showMessageDialog(NULL, msg, tr("Can not build train (%1) %2").arg(_train->getName()).arg(_train->getDescription()), JOptionPane::ERROR_MESSAGE);
} else {
   // build error, could not find destinations for cars departing staging
   //Object[] options = {Bundle.getMessage("buttonRemoveCars"), Bundle.getMessage("ButtonOK")};
QVariantList options = QVariantList();
options.append("Remove cars");
options.append("Ok");
   int results = JOptionPane::showOptionDialog(NULL, msg, tr("Can not build train (%1) %2").arg(_train->getName()).arg(_train->getDescription()),
           JOptionPane::DEFAULT_OPTION, JOptionPane::ERROR_MESSAGE, QIcon(), options, options.at(1));
   if (results == 0)
   {
       log->debug("User requested that cars be removed from staging track");
       removeCarsFromStaging();
   }
  }
  int size = carManager->getList(_train)->size();
  if (size > 0)
  {
   if (JOptionPane::showConfirmDialog(NULL, tr("%1 cars have been assigned to train (%2), do you want to release the cars by reset?").arg(size).arg(_train->getName()),  tr("Reset Train?"), JOptionPane::YES_NO_OPTION) == JOptionPane::YES_OPTION) {
       _train->reset();
   }
  }
  else if ((size = engineManager->getList(_train)->size()) > 0)
  {
   if (JOptionPane::showConfirmDialog(NULL,
           tr("%1 engines have been assigned to train (%2), do you want to release the engines by reset?").arg(size).arg(_train->getName()),
           tr("Reset Train?"),
           JOptionPane::YES_NO_OPTION) == JOptionPane::YES_OPTION) {
       _train->reset();
   }
  }
 }
 if (_buildReport != NULL)
 {
  addLine(_buildReport, ONE, msg);
  // Write to disk and close buildReport
  addLine(_buildReport, ONE, tr("Build failed for train (%1)").arg(_train
          ->getName()));
  _buildReport->flush();
  _buildReport->close();
 }
}

 /**
  * build has failed due to cars in staging not having destinations this
  * routine removes those cars from the staging track by user request.
  */
 /*private*/ void TrainBuilder::removeCarsFromStaging()
{
  if (_departStageTrack == NULL)
  {
      return;
  }
  foreach (Car* car, *_carList)
  {
   // remove cars from departure staging track that haven't been assigned to this train
   if (car->getTrack() == _departStageTrack && car->getTrain() == NULL)
   {
    // remove track from kernel
    if (car->getKernel() != NULL)
    {
     foreach (Car* c, car->getKernel()->getCars())
         c->setLocation(car->getLocation(), NULL);
    }
    else {
     car->setLocation(car->getLocation(), NULL);
    }
   }
  }
 }
}
