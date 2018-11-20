#include "router.h"
#include "track.h"
#include "train.h"
#include "printwriter.h"
#include "setup.h"
#include "logger.h"
#include "car.h"
#include "control.h"
#include "kernel.h"
#include "location.h"
#include "trainmanager.h"
#include "locationmanager.h"

namespace Operations
{
/**
 * Router for car movement. This code attempts to find a way (a route) to move a
 * car to its final destination through the use of two or more trains. First the
 * code tries to move car using a single train. If that fails, attempts are made
 * using two trains via a classification/interchange (C/I) tracks, then yard
 * tracks if enabled. Next attempts are made using three or more trains using
 * any combination of C/I and yard tracks. If that fails and routing via staging
 * is enabled, the code tries two trains using staging tracks, then multiple
 * trains using a combination of C/I, yards, and staging tracks. Currently the
 * router is limited to five trains.
 *
 * @author Daniel Boudreau Copyright (C) 2010, 2011, 2012, 2013, 2015
 * @version $Revision: 29493 $
 */
///*public*/ class Router extends TrainCommon {
    Router::Router(QObject *parent) : TrainCommon(parent)
    {
     log = new Logger("Router");
     _nextLocationTracks = QList<Track*>();
     _lastLocationTracks = QList<Track*>();
     _otherLocationTracks = QList<Track*>();

     _nextLocationTrains = QList<Train*>();
     _lastLocationTrains = QList<Train*>();
     _status = "";
     _train = NULL;
     _buildReport = NULL; // build report
     _addtoReport = false;
     _addtoReportVeryDetailed = false;
     setProperty("InstanceManagerAutoDefault", "yes");


    }

    /*protected*/ /*static*/ /*final*/ QString Router::STATUS_NOT_THIS_TRAIN = tr("RouterTrain");
    /*protected*/ /*static*/ /*final*/ QString Router::STATUS_NOT_ABLE = tr("RouterNotAble");
    /*protected*/ /*static*/ /*final*/ QString Router::STATUS_CAR_AT_DESINATION = tr("RouterCarAtDestination");
    // /*protected*/ static final String STATUS_NO_TRAINS = tr("RouterNoTrains");
    /*protected*/ /*static*/ /*final*/ QString Router::STATUS_ROUTER_DISABLED = tr("RouterDisabled");


    /*private*/ /*static*/ bool Router::debugFlag = false; // developer debug flag

    /*private*/ /*static*/ /*final*/ QString Router::SEVEN = "7"; //Setup::BUILD_REPORT_VERY_DETAILED;
    /**
     * record the single instance *
     */
    /*private*/ /*static*/ Router* Router::_instance = NULL;

    /*public*/ /*static*/ /*synchronized*/ Router* Router::instance()
    {
     Logger* log = new Logger("Router");
        if (_instance == NULL) {
            if (log->isDebugEnabled()) {
                log->debug("Router creating instance");
            }
            // create and load
            _instance = new Router();
        }
        if (Control::showInstance) {
            log->debug(tr("Router returns instance %1").arg(_instance->metaObject()->className()));
        }
        return _instance;
    }

    /**
     * Returns the status of the router when using the setDestination() for a
     * car->
     *
     * @return Track::OKAY, STATUS_NOT_THIS_TRAIN, STATUS_NOT_ABLE,
     *         STATUS_CAR_AT_DESINATION, or STATUS_ROUTER_DISABLED
     */
    /*public*/ QString Router::getStatus() {
        return _status;
    }

    /**
     * Attempts to set the car's destination if a final destination exists. Only
     * sets the car's destination if the train is part of the car's route.
     *
     * @param car the car to route
     * @param train the first train to carry this car, can be NULL
     * @param buildReport PrintWriter for build report, and can be NULL
     * @return true if car can be routed.
     */
    /*public*/ bool Router::setDestination(Car* car, Train* train, PrintWriter* buildReport)
    {
     if (car->getTrack() == NULL || car->getFinalDestination() == NULL)
     {
      return false;
     }
     _status = Track::OKAY;
     _train = train;
     _buildReport = buildReport;
     _addtoReport = Setup::getRouterBuildReportLevel()!=(Setup::BUILD_REPORT_NORMAL)
             && Setup::getRouterBuildReportLevel()!=(Setup::BUILD_REPORT_MINIMAL);
     _addtoReportVeryDetailed = Setup::getRouterBuildReportLevel()==(Setup::BUILD_REPORT_VERY_DETAILED);
     log->debug(tr("Car (%1) at location (%2, %3) final destination (%4, %5) car routing begins").arg(car->toString()).arg(car
             ->getLocationName()).arg(car->getTrackName()).arg(car->getFinalDestinationName()).arg(car
             ->getFinalDestinationTrackName()));
     if (_train != NULL)
     {
         log->debug(tr("Routing using train (%1)").arg(train->getName()));
     }
        // Has the car arrived at the car's final destination?
        if (car->getLocation() != NULL && car->getLocation()==(car->getFinalDestination())
                && (car->getTrack()==(car->getFinalDestinationTrack()) || car->getFinalDestinationTrack() == NULL))
        {
         log->debug(tr("Car (%1) has arrived at final destination").arg(car->toString()));
         _status = STATUS_CAR_AT_DESINATION;
         car->setFinalDestination(NULL);
         car->setFinalDestinationTrack(NULL);
         return false;
        }
        // is car part of kernel?
        if (car->getKernel() != NULL && !car->getKernel()->isLead(car))
        {
         return false;
        }
        // note clone car has the car's "final destination" as its destination
        Car* _clone = clone(car);
        // Note the following test doesn't check for car length which is what we want. Also ignores if track has a
        // schedule.
        _status = _clone->testDestination(_clone->getDestination(), _clone->getDestinationTrack());
        if (_status!=(Track::OKAY))
        {
         addLine(_buildReport, SEVEN, tr("Can't use %5 (%2, %3) for (%1) due to %4").arg(
                         car->toString()).arg(
                         car->getFinalDestinationName()).arg(
                         car->getFinalDestinationTrackName()).arg(
                         _status).arg
                         (car->getFinalDestinationTrack() == NULL ? tr("destination") : car
                                 ->getFinalDestinationTrack()->getTrackTypeName()));
         return false;
        }
        if (_clone->getDestination() != NULL && _clone->getDestinationTrack() == NULL)
        {
         // determine if there's a track that can service the car
         QString status = "";
         foreach (Track* track, _clone->getDestination()->getTrackList())
         {
          status = track->accepts(_clone);
          if (status==(Track::OKAY) || status.startsWith(Track::LENGTH))
          {
           log->debug(tr("Track* (%1) will accept car (%2)").arg(track->getName()).arg(car->toString()));
           break;
          }
         }
         if (status!=(Track::OKAY) && !status.startsWith(Track::LENGTH))
         {
          addLine(_buildReport, SEVEN, _status = tr("Could not find a track at (%1) able to service car (%2)").arg(
                  _clone->getDestinationName()).arg(car->toString()));
          return false;
         }
        }
        // check to see if car will move to destination using a single train
        if (checkForSingleTrain(car, _clone))
        {
         return true; // a single train can service this car
        }
        else if (Setup::isCarRoutingEnabled())
        {
         log->debug(tr("Car (%1) final destination (%2) is not served by a single train").arg(car->toString()).arg(car
                 ->getFinalDestinationName()));
         // was the request for a local move?
         if (car->getLocationName()==(car->getFinalDestinationName()))
         {
          addLine(_buildReport, SEVEN, tr("Could not find a train (single local move) to transport car directly from (%1, %2) to (%3, %4)").arg(
                  car->getLocationName()).arg(car->getTrackName()).arg(car->getFinalDestinationName()).arg(
                          car->getFinalDestinationTrackName()));
          // _status = STATUS_NO_TRAINS;
          // return false; // maybe next time
         }
         if (_addtoReport)
         {
          addLine(_buildReport, SEVEN, BLANK_LINE);
          addLine(_buildReport, SEVEN, tr("Router could not find a train able to transport car (%1) directly from (%2) to (%3) begin two train routing").arg(
                  car->toString()).arg(car->getLocationName()).arg(car->getFinalDestinationName()));
         }

         _nextLocationTracks.clear();
         _lastLocationTracks.clear();
         _otherLocationTracks.clear();
         _nextLocationTrains.clear();
         _lastLocationTrains.clear();

         // first try using 2 trains and an interchange track to route the car
         if (setCarDestinationInterchange(car))
         {
          if (car->getDestination() == NULL)
          {
           log->debug(tr("Was able to find a route via classification/interchange track, but not using train (%1)" \
                    " or car destination not set, try again using yard tracks").arg(_train->getName())); // NOI18N
           if (setCarDestinationYard(car))
           {
            log->debug(tr("Was able to find route via yard (%1, %2) for car (%3)").arg(car->getDestinationName()).arg(
                       car->getDestinationTrackName()).arg(car->toString()));
           }
          }
          else
          {
              log->debug(tr("Was able to find route via interchange (%1, %2) for car (%3)").arg(car->getDestinationName()).arg(
                      car->getDestinationTrackName()).arg(car->toString()));
          }
          // now try 2 trains and a yard track
         }
         else if (setCarDestinationYard(car))
         {
          log->debug(tr("Was able to find route via yard (%1, %2) for car (%3) using two trains").arg(car
                  ->getDestinationName()).arg(car->getDestinationTrackName()).arg(car->toString()));
          // now try 3 or more trains to route car, but not through staging
         }
         else if (setCarDestinationMultipleTrains(car, false))
         {
          log->debug(tr("Was able to find multiple train route for car (%1)").arg(car->toString()));
          // now try 2 trains and a staging track
         } else if (setCarDestinationStaging(car))
         {
          log->debug(tr("Was able to find route via staging (%1, %2) for car (%2) using two trains").arg(car
                  ->getDestinationName()).arg(car->getDestinationTrackName()).arg(car->toString()));
          // now try 3 or more trains to route car, include staging if enabled
         } else if (setCarDestinationMultipleTrains(car, true))
         {
          log->debug(tr("Was able to find multiple train route for car (%1) through staging").arg(car->toString()));
         }
         else
         {
          log->debug(tr("Wasn't able to set route for car (%1)").arg(car->toString()));
          _status = STATUS_NOT_ABLE;
          return false; // maybe next time
         }
        }
        else
        {
         log->debug(tr("Car* (%1) final destination (%2) is not served directly by any train").arg(car->toString()).arg(car
                 ->getFinalDestinationName())); // NOI18N
         _status = STATUS_ROUTER_DISABLED;
         car->setFinalDestination(NULL);
         car->setFinalDestinationTrack(NULL);
         return false;
        }
        return true; // car's destination has been set
    }

    /**
     * Checks to see if a single train can transport car to its final
     * destination.
     *
     * @param car
     * @param clone
     * @return true if single train can transport car to its final destination.
     */
    /*private*/ bool Router::checkForSingleTrain(Car* car, Car* _clone) {
        bool trainServicesCar = false; // specific train
        Train* testTrain = NULL;
        if (_train != NULL) {
            trainServicesCar = _train->services(_buildReport, _clone);
        }
        if (trainServicesCar) {
            testTrain = _train; // use the specific train
        } // can specific train can service car out of staging. Note that the router code will try to route the car using
        // two or more trains just to get the car out of staging.
        if (car->getTrack()->getTrackType()==(Track::STAGING) && _train != NULL && !trainServicesCar) {
            addLine(_buildReport, SEVEN, tr("Train (%1) can't transport car (%2) out of staging (%3) directly to (%4, %5)").arg(
                    _train->getName()).arg(car->toString()).arg(car->getLocationName()).arg(_clone->getDestinationName().arg(
                            _clone->getDestinationTrackName())));
            if (_train->getServiceStatus()!=(Train::NONE)) {
                addLine(_buildReport, SEVEN, _train->getServiceStatus());
            }
        } else if (!trainServicesCar) {
            testTrain = TrainManager::instance()->getTrainForCar(_clone, _train, _buildReport);
        }
        if (testTrain != NULL && _train != NULL && !trainServicesCar
                && _train->isServiceAllCarsWithFinalDestinationsEnabled()) {
            // log->debug("Option to service all cars with a final destination is enabled");
            addLine(_buildReport, SEVEN, tr("Option to service all cars with a final destination enabled, ignoring train (%1) ability to service car (%2) to (%3, %4)").arg(
                    testTrain->getName()).arg(car->toString()).arg(_clone->getDestinationName()).arg(_clone->getDestinationTrackName()));
            testTrain = NULL;
        }
        if (testTrain != NULL) {
            return routeUsingOneTrain(testTrain, car, _clone);
        }
        return false;
    }

    /**
     * A single train can service the car-> Provide various messages to build
     * report detailing which train can service the car-> Also checks to see if
     * the needs to go the alternate track or yard track if the car's final
     * destination track is full. Returns false if car is stuck in staging.
     *
     * @param testTrain
     * @param car
     * @param clone
     * @return true for all cases except if car is departing staging and is
     *         stuck there.
     */
    /*private*/ bool Router::routeUsingOneTrain(Train* testTrain, Car* car, Car* _clone) {
        addLine(_buildReport, SEVEN, tr("Train (%1) can transport car (%2) from %3 (%4, %5) to (%6, %7)").arg(
                testTrain->getName()).arg(car->toString()).arg(car->getTrack()->getTrackTypeName()).arg(car->getLocationName()).arg(car->getTrackName(),
                _clone->getDestinationName()).arg(_clone->getDestinationTrackName()));
        if (_addtoReport) {
            addLine(_buildReport, SEVEN, tr("Route for car (%1): (%2, %3)->(%4)->(%5, %6)").arg(
                    car->toString(), car->getLocationName()).arg(car->getTrackName()).arg(testTrain->getName(),
                            _clone->getDestinationName()).arg(_clone->getDestinationTrackName()));
        }
        // now check to see if specific train can service car directly
        if (_train != NULL && _train != testTrain) {
            addLine(_buildReport, SEVEN, tr("Train (%1) can't transport car (%2) directly to (%3, %4)").arg(
                    _train->getName()).arg(car->toString()).arg(_clone->getDestinationName()).arg(
                            _clone->getDestinationTrackName()));
            if (_train->getServiceStatus()!=(Train::NONE)) {
                addLine(_buildReport, SEVEN, _train->getServiceStatus());
            }
            _status = STATUS_NOT_THIS_TRAIN;
            return true; // car can be routed, but not by this train!
        }
        _status = car->setDestination(_clone->getDestination(), _clone->getDestinationTrack());
        if (_status==(Track::OKAY)) {
            return true; // done, car has new destination
        }
        addLine(_buildReport, SEVEN, tr("Can't use %5 (%2, %3) for (%1) due to %4").arg(
                car->toString()).arg(
                _clone->getDestinationName()).arg(
                _clone->getDestinationTrackName()).arg(
                _status).arg(
                (_clone->getDestinationTrack() == NULL ? tr("destination") : _clone
                        ->getDestinationTrack()->getTrackTypeName())));
        // check to see if an alternative track was specified
        if ((_status.startsWith(Track::LENGTH) || _status.startsWith(Track::SCHEDULE))
                && _clone->getDestinationTrack() != NULL && _clone->getDestinationTrack()->getAlternateTrack() != NULL
                && _clone->getDestinationTrack()->getAlternateTrack() != car->getTrack()) {
            QString status = car->setDestination(_clone->getDestination(), _clone->getDestinationTrack()->getAlternateTrack());
            if (status==(Track::OKAY)) {
                if (_train == NULL || _train->services(car)) {
                    addLine(_buildReport, SEVEN, tr("Delivering car (%1) to alternate track (%2) at destination (%3)").arg(
                            car->toString()).arg(_clone->getDestinationTrack()->getAlternateTrack()->getName()).arg(
                                    _clone->getDestination()->getName()));
                    return true; // car is going to alternate track
                }
                addLine(_buildReport, SEVEN, tr("Train (%1) can not deliver car (%2) to alternate track (%3) at destination (%4)").arg(
                        _train->getName(), car->toString()).arg(
                                _clone->getDestinationTrack()->getAlternateTrack()->getName()).arg(
                                _clone->getDestination()->getName()));
            } else {
                addLine(_buildReport, SEVEN, tr("Alternate track (%1) isn''t available due to %2").arg(
                        _clone->getDestinationTrack()->getAlternateTrack()->getName()).arg(status));
            }
        } else if (_clone->getDestinationTrack() != NULL && _clone->getDestinationTrack()->getAlternateTrack() != NULL
                && _clone->getDestinationTrack()->getAlternateTrack() == car->getTrack()) {
            // state that car is spotted at the alternative track
            addLine(_buildReport, SEVEN, tr("Hold car (%1) at alternate track (%2) final destination (%3, %4)").arg(
                    car->toString(), _clone->getDestinationTrack()->getAlternateTrack()->getName()).arg(_clone->getLocationName()).arg(
                    _clone->getDestinationTrackName()));
        } else if (car->getLocation() == _clone->getDestination()) {
            // state that alternative and yard track options are not available if car is at final destination
            addLine(_buildReport, SEVEN, tr("Car (%1) is at final destination (%2) alternate track and yard options are ignored").arg(
                    car->toString()).arg(car->getLocationName()));
        }
        // check to see if spur was full, if so, forward to yard if possible
        if (Setup::isForwardToYardEnabled() && _status.startsWith(Track::LENGTH)
                && car->getLocation() != _clone->getDestination()) {
            // log->debug("Spur full, searching for a yard at destination ("+_clone->getDestinationName()+")");
            addLine(_buildReport, SEVEN, tr("Track (%1) full, searching for a yard at destination (%2)").arg(
                    _clone->getDestinationTrackName()).arg(_clone->getDestinationName()));
            Location* dest = _clone->getDestination();
            QList<Track*> yards = dest->getTrackByMovesList(Track::YARD);
            log->debug(tr("Found %1 yard(s) at destination (%2)").arg(yards.size()).arg(_clone->getDestinationName()));
            foreach (Track* track, yards) {
                QString status = car->setDestination(dest, track);
                if (status==(Track::OKAY)) {
                    if (_train != NULL && !_train->services(car)) {
                        log->debug(tr("Train (%1) can not deliver car (%2) to yard (%3)").arg(_train->getName()).arg(car->toString()).arg(
                                track->getName()));
                        continue;
                    }
                    addLine(_buildReport, SEVEN, tr("Sending car (%1) to yard (%2) at destination (%3)").arg(
                            car->toString()).arg(track->getName()).arg(dest->getName()));
                    return true; // car is going to a yard
                } else {
                    addLine(_buildReport, SEVEN, tr("Can't use yard (%1) due to %2").arg(
                            track->getName()).arg(status));
                }
            }
            addLine(_buildReport, SEVEN, tr("Could not find a yard at (%1) for car (%2)").arg(
                    dest->getName()).arg(car->toString()));
        }
        car->setDestination(NULL, NULL);
        if (car->getTrack()->getTrackType()==(Track::STAGING)) {
            log->debug(tr("Car* (%1) departing staging, single train can't deliver car to (%2, %3)").arg(car->toString()).arg(_clone
                    ->getDestinationName()).arg(_clone->getDestinationTrackName()));
            return false; // try 2 or more trains
        }
        return true; // able to route, but not able to set the car's destination
    }

    /**
     * Sets a car's final destination to an interchange track if two trains can
     * route the car->
     *
     * @param car the car to be routed
     * @return true if car's destination has been modified to an interchange.
     *         False if an interchange track wasn't found that could service the
     *         car's final destination.
     */
    /*private*/ bool Router::setCarDestinationInterchange(Car* car) {
        return setCarDestinationTwoTrains(car, Track::INTERCHANGE);
    }

    /**
     * Sets a car's final destination to a yard track if two train can route the
     * car->
     *
     * @param car the car to be routed
     * @return true if car's destination has been modified to a yard. False if a
     *         yard track wasn't found that could service the car's final
     *         destination.
     */
    /*private*/ bool Router::setCarDestinationYard(Car* car) {
        if (Setup::isCarRoutingViaYardsEnabled()) {
            return setCarDestinationTwoTrains(car, Track::YARD);
        }
        return false;
    }

    /**
     * Sets a car's final destination to a staging track if two train can route
     * the car->
     *
     * @param car the car to be routed
     * @return true if car's destination has been modified to a staging track->
     *         False if a staging track wasn't found that could service the
     *         car's final destination.
     */
    /*private*/ bool Router::setCarDestinationStaging(Car* car) {
        if (Setup::isCarRoutingViaStagingEnabled()) {
            addLine(_buildReport, SEVEN, tr("Try to find a route for car (%1) through staging").arg(
                    car->toString()));
            return setCarDestinationTwoTrains(car, Track::STAGING);
        }
        return false;
    }

    /*private*/ bool Router::setCarDestinationTwoTrains(Car* car, QString trackType) {
        Car* testCar = clone(car); // reload
        log->debug(tr("Two train routing, find %1track for car (%2) final destination (%3, %4)").arg(trackType,
                car->toString()).arg(testCar->getDestinationName()).arg(testCar->getDestinationTrackName()));
        if (_addtoReport) {
            addLine(_buildReport, SEVEN, BLANK_LINE);
            addLine(_buildReport, SEVEN, tr("Router find %1 track for car (%2) final destination (%3, %4)").arg(
                    Track::getTrackTypeName(trackType)).arg(car->toString()).arg(testCar->getDestinationName()).arg(
                    testCar->getDestinationTrackName()));
        }
        bool foundRoute = false;
        // now search for a yard or interchange that a train can pick up and deliver the car to its destination
        QList<Track*> tracks = LocationManager::instance()->getTracksByMoves(trackType);
        foreach (Track* track, tracks) {
            if (car->getTrack() == track) {
                continue; // don't use car's current track
            }
            QString status = track->accepts(testCar);
            if (status!=(Track::OKAY) && !status.startsWith(Track::LENGTH)) {
                if (_addtoReportVeryDetailed) {
                    addLine(_buildReport, SEVEN, BLANK_LINE);
                    addLine(_buildReport, SEVEN, tr("Can't use %5 (%2, %3) for (%1) due to %4").arg(
                            car->toString()).arg(track->getLocation()->getName()).arg(track->getName()).arg(status,
                                    track->getTrackTypeName()));
                }
                continue;
            }
            if (debugFlag) {
                log->debug(tr("Found %1 track (%2, %3) for car (%4)").arg(trackType).arg(track->getLocation()->getName()).arg(track
                        ->getName()).arg(car->toString()));
            }
            if (_addtoReport) {
                addLine(_buildReport, SEVEN, BLANK_LINE);
                addLine(_buildReport, SEVEN, tr("Router found %1 track (%2, %3) for car (%4)").arg(
                        Track::getTrackTypeName(trackType)).arg(track->getLocation()->getName()).arg(track->getName(),
                        car->toString()));
            }
            // test to see if there's a train that can deliver the car to its final location
            testCar->setTrack(track);
            ((RollingStock*)testCar)->setDestination(car->getFinalDestination());
            testCar->setDestinationTrack(car->getFinalDestinationTrack());
            Train* secondTrain = TrainManager::instance()->getTrainForCar(testCar, _buildReport);
            if (secondTrain == NULL) {
                if (debugFlag) {
                    log->debug(tr("Could not find a train to service car from %1 (%2, %3) to destination (%4, %5)").arg(
                            trackType).arg( track->getLocation()->getName()).arg(track->getName()).arg(testCar->getDestinationName()).arg(
                            testCar->getDestinationTrackName())); // NOI18N
                }
                if (_addtoReport) {
                    addLine(_buildReport, SEVEN, tr("Router could not find a train to transport car from %1 (%2, %3) to (%4, %5)").arg(
                            Track::getTrackTypeName(trackType)).arg( track->getLocation()->getName()).arg(
                                    track->getName()).arg( testCar->getDestinationName()).arg( testCar->getDestinationTrackName()));
                }
                continue;
            }
            if (debugFlag) {
                log->debug(tr("Train (%1) can service car (%2 from %3 (%4, %5) to final destination (%6, %7)").arg(secondTrain
                        ->getName()).arg(car->toString()).arg(trackType).arg(testCar->getLocationName()).arg(testCar->getTrackName()).arg(
                        testCar->getDestinationName()).arg(testCar->getDestinationTrackName()));
            }
            if (_addtoReport) {
                addLine(_buildReport, SEVEN, tr("Train (%1) can transport car (%2) from %3 (%4, %5) to (%6, %7)").arg(
                        secondTrain->getName()).arg(car->toString()).arg(Track::getTrackTypeName(trackType)).arg(
                                testCar->getLocationName()).arg(testCar->getTrackName()).arg(testCar->getDestinationName(),
                                testCar->getDestinationTrackName()));
            }
            // Save the "last" tracks for later use
            _lastLocationTracks.append(track);
            _lastLocationTrains.append(secondTrain);
            // now try to forward car to this interim location
            testCar->setTrack(car->getTrack()); // restore test car's location and track
            ((RollingStock*)testCar)->setDestination(track->getLocation()); // forward test car to this interim destination and track
            testCar->setDestinationTrack(track);
            // determine if car can be transported from current location to this yard or interchange
            // find a train that will transport the car to the interim track
            Train* firstTrain = NULL;
            QString specific = canSpecificTrainService(testCar);
            if (specific==(YES)) {
                firstTrain = _train;
            } else if (specific==(NOT_NOW)) {
                addLine(_buildReport, SEVEN, tr("Train (%1) can't transport car (%2) to (%3, %4) due to %5").arg(
                        _train->getName()).arg(car->toString()).arg(track->getLocation()->getName()).arg(
                                track->getName()).arg(_train->getServiceStatus()));
                foundRoute = true; // however, the issue is route moves or train length
            } else {
                firstTrain = TrainManager::instance()->getTrainForCar(testCar, _buildReport);
            }
            if (firstTrain == NULL && _addtoReport) {
                addLine(_buildReport, SEVEN, tr("Router could not find a train to transport car from %1 (%2, %3) to (%4, %5)").arg(
                        testCar->getTrack()->getTrackTypeName()).arg(
                                testCar->getTrack()->getLocation()->getName()).arg(testCar->getTrack()->getName()).arg(
                                testCar->getDestinationName()).arg(testCar->getDestinationTrackName()));
            }
            // Can the specific train carry this car out of staging?
            if (_train != NULL && car->getTrack()->getTrackType()==(Track::STAGING) && specific!=(YES)) {
                if (debugFlag) {
                    log->debug(tr("Train (%1) can not deliver car to (%2 %3)").arg(_train->getName()).arg(track->getLocation()
                            ->getName()).arg(track->getName()));
                }
                if (_addtoReport) {
                    addLine(_buildReport, SEVEN, tr("Train (%1) can't transport car (%2) from (%3, %4) to (%5, %6)").arg(
                            _train->getName()).arg(car->toString()).arg(car->getLocationName()).arg(car->getTrackName(),
                                    track->getLocation()->getName()).arg(track->getName()));
                }
                continue; // can't use this train
            }
            // Is the option for the specific train carry this car?
            if (firstTrain != NULL && _train != NULL && _train->isServiceAllCarsWithFinalDestinationsEnabled()
                    && specific!=(YES)) {
                if (_addtoReport) {
                    addLine(_buildReport, SEVEN, tr("Option to service all cars with a final destination enabled, ignoring train (%1) ability to service car (%2) to (%3, %4)").arg(
                            firstTrain->getName()).arg(car->toString()).arg(track->getLocation()->getName()).arg(
                                    track->getName()));
                }
                continue; // can't use this train
            }
            if (firstTrain != NULL) {
                foundRoute = true; // found a route
                // found a two train route for this car, show the car's route
                if (_addtoReport) {
                    addLine(_buildReport, SEVEN, tr("Route for car (%1): (%2, %3)->(%4)->(%5, %6)->(%7)->(%8, %9)").arg(
                            car->toString()).arg(car->getLocationName()).arg(car->getTrackName()).arg(
                                    firstTrain->getName()).arg(
                                    testCar->getDestinationName()).arg(testCar->getDestinationTrackName()).arg(
                                    secondTrain->getName()).arg(
                                    car->getFinalDestinationName()).arg(car->getFinalDestinationTrackName()));
                } else {
                    addLine(_buildReport, SEVEN, tr("Route for car (%1): (%2, %3)->(%4, %5)->(%6, %7)").arg(
                            car->toString()).arg(car->getLocationName()).arg(car->getTrackName()).arg(
                                    testCar->getDestinationName()).arg(testCar->getDestinationTrackName()).arg(
                                    car->getFinalDestinationName()).arg(car->getFinalDestinationTrackName()));
                }
                _status = car->testDestination(track->getLocation(), track);
                if (_status.startsWith(Track::LENGTH)) {
                    // if the issue is length at the interim track, add message to build report
                    addLine(_buildReport, SEVEN, tr("Can't use %5 (%2, %3) for (%1) due to %4").arg(
                            car->toString()).arg(track->getLocation()->getName()).arg(track->getName()).arg(_status).arg(
                                    track->getTrackTypeName()));
                    continue;
                }
                if (_status==(Track::OKAY)) {
                    // only set car's destination if specific train can service car
                    if (_train != NULL && _train != firstTrain) {
                        addLine(_buildReport, SEVEN, tr("Train (%1) can't transport car (%2) directly to (%3, %4)").arg(
                                _train->getName()).arg(car->toString()).arg(testCar->getDestinationName()).arg(
                                        testCar->getDestinationTrackName()));
                        _status = STATUS_NOT_THIS_TRAIN;
                        continue;// found a route but it doesn't start with the specific train
                    }
                    if (track->getTrackType()==(Track::STAGING)) {
                        _status = car->setDestination(track->getLocation(), NULL); // don't specify which track in staging
                    } else {
                        _status = car->setDestination(track->getLocation(), track);
                    }
                    if (debugFlag) {
                        log->debug(tr("Train (%1) can service car (%2) from current location (%3, %4) to%5 (%6), %7)").arg(
                                firstTrain->getName()).arg(car->toString()).arg(car->getLocationName()).arg(car->getTrackName()).arg(
                                trackType).arg(track->getLocation()->getName()).arg(track->getName())); // NOI18N
                    }
                    if (_addtoReport) {
                        addLine(_buildReport, SEVEN, tr("Train (%1) can service car (%2) from (%3, %4) to %5 (%6, %7)").arg(
                                firstTrain->getName()).arg(car->toString()).arg(car->getLocationName()).arg(
                                        car->getTrackName()).arg(Track::getTrackTypeName(trackType)).arg(
                                        track->getLocation()->getName()).arg(track->getName()));
                    }
                    return true; // the specific train and another train can carry the car to its destination
                }
            }
        }
        if (foundRoute) {
            _status = STATUS_NOT_ABLE;
        }
        return foundRoute;
    }
#if 1
    /*
     * Note that "last" set of location/tracks was loaded by
     * setCarDestinationTwoTrains. The following code builds two additional sets
     * of location/tracks called "next" and "other". "next" is the next set of
     * location/tracks that the car can reach by a single train. "last" is the
     * last set of location/tracks that services the cars final destination. And
     * "other" is the remaining sets of location/tracks that are not "next" or
     * "last". The code then tries to connect the "next" and "last"
     * location/track sets with a train that can service the car-> If successful,
     * that would be a three train route for the car-> If not successful, the
     * code than tries combinations of "next", "other" and "last"
     * location/tracks to create a route for the car->
     */
    /*private*/ bool Router::setCarDestinationMultipleTrains(Car* car, bool useStaging) {
        if (useStaging && !Setup::isCarRoutingViaStagingEnabled())
            return false; // routing via staging is disabled
        bool foundRoute = false;
        if (_lastLocationTracks.size() == 0) {
            if (useStaging)
                addLine(_buildReport, SEVEN, tr("Could not find an interim C/I, yard, or staging track that can service car to destination (%1)").arg(
                        car->getFinalDestinationName()));
            else
                addLine(_buildReport, SEVEN, tr("Could not find an interim C/I or yard track that can service car to destination (%1)").arg(
                        car->getFinalDestinationName()));
            return false;
        }

        Car* testCar = clone(car); // reload
        // build the "next" and "other" location/tracks
        // start with interchanges
        QList<Track*> tracks;
        if (!useStaging) {
            tracks = LocationManager::instance()->getTracksByMoves(Track::INTERCHANGE);
            loadTracks(car, testCar, tracks);
        }
        // next load yards if enabled
        if (!useStaging && Setup::isCarRoutingViaYardsEnabled()) {
            tracks = LocationManager::instance()->getTracksByMoves(Track::YARD);
            loadTracks(car, testCar, tracks);
        }
        // now staging if enabled
        if (useStaging && Setup::isCarRoutingViaStagingEnabled()) {
            tracks = LocationManager::instance()->getTracksByMoves(Track::STAGING);
            loadTracks(car, testCar, tracks);
        }

        if (_nextLocationTracks.size() == 0) {
            addLine(_buildReport, SEVEN, tr("Could not find an interim C/I or yard track that can service car from location (%1)").arg(
                    car->getLocationName()));
            return false;
        }

        // state that routing begins using three trains
        if (_addtoReport)
            addLine(_buildReport, SEVEN, BLANK_LINE);
        addLine(_buildReport, SEVEN, tr("Routing using three trains destination (%1) begins").arg(car
                ->getFinalDestinationName()));

        if (log->isDebugEnabled()) {
            // tracks that could be the very next destination for the car
            foreach (Track* t, _nextLocationTracks) {
                log->debug(tr("Next location (%1, %2) can service car (%3) using train (%4)").arg(t->getLocation()->getName()).arg(
                        t->getName()).arg(car->toString()).arg(_nextLocationTrains.at(_nextLocationTracks.indexOf(t))->toString()));
            }
            // tracks that could be the next to last destination for the car
            foreach (Track* t, _lastLocationTracks) {
                log->debug(tr("Last location (%1, %2) can service car (%3) using train (%4)").arg(t->getLocation()->getName(),
                        t->getName()).arg(car->toString()).arg(_lastLocationTrains.at(_lastLocationTracks.indexOf(t))->toString()));
            }
            // tracks that are not the next or the last list
            foreach (Track* t, _otherLocationTracks) {
                log->debug(tr("Other location (%1, %2) may be needed to service car (%3)").arg(t->getLocation()->getName()).arg(t
                        ->getName()).arg(car->toString()));
            }
            log->debug("Try to find route using 3 trains");
        }
        foreach (Track* nlt, _nextLocationTracks) {
            testCar->setTrack(nlt); // set car to this location and track
            foreach (Track* llt, _lastLocationTracks) {
                testCar->setDestinationTrack(llt); // set car to this destination and track
                // does a train service these two locations?
                Train* middleTrain = TrainManager::instance()->getTrainForCar(testCar, NULL); // don't add to report
                if (middleTrain != NULL) {
                    log->debug(tr("Found 3 train route, setting car destination (%1, %2)").arg(testCar->getLocationName(),
                            testCar->getTrackName()));
                    foundRoute = true;
                    // show the route
                    if (_addtoReport) {
                        addLine(_buildReport, SEVEN, tr("Route for car (%1): (%2, %3)->(%4)->(%5, %6)->(%7)->(%8, %9)->(%10)->(%11, %12)").arg(
                                car->toString()).arg(car->getLocationName()).arg(car->getTrackName()).arg(
                                        _nextLocationTrains.at(_nextLocationTracks.indexOf(nlt))->getName()).arg(
                                        testCar->getLocationName()).arg(testCar->getTrackName()).arg(
                                        middleTrain->getName()).arg(
                                        testCar->getDestinationName()).arg(testCar->getDestinationTrackName()).arg(
                                        _lastLocationTrains.at(_lastLocationTracks.indexOf(llt))->getName()).arg(
                                        car->getFinalDestinationName()).arg(car->getFinalDestinationTrackName()));
                    } else {
                        addLine(_buildReport, SEVEN, tr("Route for car (%1): (%2, %3)->(%4, %5)->(%6, %7)->(%8, %9)").arg(
                                car->toString()).arg(car->getLocationName()).arg(car->getTrackName()).arg(
                                        testCar->getLocationName()).arg(testCar->getTrackName()).arg(testCar->getDestinationName()).arg(
                                        testCar->getDestinationTrackName()).arg(car->getFinalDestinationName()).arg(
                                        car->getFinalDestinationTrackName()));
                    }
                    if (finshSettingRouteFor(car, nlt)) {
                        return true; // done 3 train routing
                    }
                    break; // there was an issue with the first stop in the route
                }
            }
        }
        if (foundRoute) {
            return foundRoute; // 3 train route, but there was an issue with the first stop in the route
        }
        log->debug(tr("Using 3 trains to route car to (%1) was unsuccessful").arg(car->getFinalDestinationName()));
        addLine(_buildReport, SEVEN, tr("Routing using four trains destination (%1) begins").arg(car
                ->getFinalDestinationName()));
        bool loopOk = true;
        foreach (Track* nlt, _nextLocationTracks)
        {
         if(!loopOk)
          break;
            otherloop: foreach (Track* mlt, _otherLocationTracks) {
                testCar->setTrack(nlt); // set car to this location and track
                testCar->setDestinationTrack(mlt); // set car to this destination and track
                // does a train service these two locations?
                Train* middleTrain2 = TrainManager::instance()->getTrainForCar(testCar, NULL); // don't add to report
                if (middleTrain2 != NULL) {
                    if (debugFlag) {
                        log->debug(tr("Train 2 (%1) services car from (%2) to (%3, %4)").arg(middleTrain2->getName()).arg(testCar
                                ->getLocationName()).arg(testCar->getDestinationName()).arg(testCar->getDestinationTrackName()));
                    }
                    foreach (Track* llt, _lastLocationTracks) {
                        testCar->setTrack(mlt); // set car to this location and track
                        testCar->setDestinationTrack(llt); // set car to this destination and track
                        Train* middleTrain3 = TrainManager::instance()->getTrainForCar(testCar, NULL); // don't add to
                        // report
                        if (middleTrain3 != NULL) {
                            log->debug(tr("Found 4 train route, setting car destination (%1, %2)").arg(nlt->getLocation()
                                    ->getName()).arg(nlt->getName()));
                            foundRoute = true;
                            // show the route
                            if (_addtoReport) {
                                addLine(_buildReport, SEVEN, tr("Route for car ({0}): ({1}, {2})->({3})->({4}, {5})->({6})->({7}, {8})->({9})->({10}, {11})->({12})->({13}, {14})").arg(
                                        car->toString()).arg(car->getLocationName()).arg(car->getTrackName()).arg(
                                                _nextLocationTrains.at(_nextLocationTracks.indexOf(nlt))->getName()).arg(
                                                nlt->getLocation()->toString()).arg(nlt->getName()).arg(
                                                middleTrain2->getName()).arg(
                                                mlt->getLocation()->getName()).arg(mlt->getName()).arg(
                                                middleTrain3->getName()).arg(
                                                llt->getLocation()->getName()).arg(llt->getName()).arg(
                                                _lastLocationTrains.at(_lastLocationTracks.indexOf(llt))->getName()).arg(
                                                car->getFinalDestinationName()).arg(car->getFinalDestinationTrackName()));
                            } else {
                                addLine(_buildReport, SEVEN, tr("Route for car ({0}): ({1}, {2})->({3}, {4})->({5}, {6})->({7}, {8})->({9}, {10})").arg(
                                        car->toString()).arg(car->getLocationName()).arg(car->getTrackName()).arg(
                                                nlt->getLocation()->toString()).arg(nlt->getName()).arg(mlt->getLocation()->getName()).arg(
                                                mlt->getName()).arg(llt->getLocation()->getName()).arg(llt->getName()).arg(
                                                car->getFinalDestinationName()).arg(car->getFinalDestinationTrackName()));
                            }
                            if (finshSettingRouteFor(car, nlt)) {
                                return true; // done 4 train routing
                            }
                            //break otherloop; // there was an issue with the first stop in the route
                            loopOk = false;
                            break;
                        }
                    }
                }
            }
        }
        if (foundRoute) {
            return foundRoute; // 4 train route, but there was an issue with the first stop in the route
        }
        log->debug(tr("Using 4 trains to route car to (%1) was unsuccessful").arg(car->getFinalDestinationName()));
        addLine(_buildReport, SEVEN, tr("Routing using five trains destination (%1) begins").arg(car
                ->getFinalDestinationName()));
        loopOk = true;
        foreach (Track* nlt, _nextLocationTracks)
        {
         if(!loopOk)
          break;
            otherloop2: foreach (Track* mlt1, _otherLocationTracks) {
                testCar->setTrack(nlt); // set car to this location and track
                testCar->setDestinationTrack(mlt1); // set car to this destination and track
                // does a train service these two locations?
                Train* middleTrain2 = TrainManager::instance()->getTrainForCar(testCar, NULL); // don't add to report
                if (middleTrain2 != NULL) {
                    if (debugFlag) {
                        log->debug(tr("Train 2 (%1) services car from (%2) to (%3, %4)").arg(middleTrain2->getName()).arg(testCar
                                ->getLocationName()).arg(testCar->getDestinationName()).arg(testCar->getDestinationTrackName()));
                    }
                    foreach (Track* mlt2, _otherLocationTracks) {
                        if (mlt1 == mlt2) {
                            continue;
                        }
                        testCar->setTrack(mlt1); // set car to this location and track
                        testCar->setDestinationTrack(mlt2); // set car to this destination and track
                        // does a train service these two locations?
                        Train* middleTrain3 = TrainManager::instance()->getTrainForCar(testCar, NULL); // don't add to
                        // report
                        if (middleTrain3 != NULL) {
                            if (debugFlag) {
                                log->debug(tr("Train 3 (%1) services car from (%2) to (%3, %4)").arg(middleTrain3->getName()).arg(
                                        testCar->getLocationName()).arg(testCar->getDestinationName()).arg(testCar
                                                ->getDestinationTrackName()));
                            }
                            foreach (Track* llt, _lastLocationTracks) {
                                testCar->setTrack(mlt2); // set car to this location and track
                                testCar->setDestinationTrack(llt); // set car to this destination and track
                                // does a train service these two locations?
                                Train* middleTrain4 = TrainManager::instance()->getTrainForCar(testCar, NULL); // don't add
                                // to report
                                if (middleTrain4 != NULL) {
                                    log->debug(tr("Found 5 train route, setting car destination (%1, %2)").arg(nlt
                                            ->getLocation()->getName()).arg(nlt->getName()));
                                    foundRoute = true;
                                    // show the car's route
                                    if (_addtoReport) {
                                        addLine(_buildReport, SEVEN, tr("Route for car ({0}): ({1}, {2})->({3})->({4}, {5})->({6})->({7}, {8})->({9})->({10}, {11})->({12})->({13}, {14})->({15})->({16}, {17})").arg(
                                                car->toString()).arg(car->getLocationName()).arg(car->getTrackName()).arg( _nextLocationTrains.at(_nextLocationTracks.indexOf(nlt))->getName()).arg(
                                                        nlt->getLocation()->getName()).arg(nlt->getName()).arg(
                                                        middleTrain2->getName()).arg(
                                                        mlt1->getLocation()->getName()).arg(mlt1->getName()).arg(
                                                        middleTrain3->getName()).arg(
                                                        mlt2->getLocation()->getName()).arg(mlt2->getName()).arg(
                                                        middleTrain4->getName()).arg(
                                                        llt->getLocation()->getName()).arg(llt->getName()).arg(
                                                        _lastLocationTrains.at(_lastLocationTracks.indexOf(llt))->getName()).arg(
                                                        car->getFinalDestinationName()).arg(car->getFinalDestinationTrackName()));
                                    } else {
                                        addLine(_buildReport, SEVEN, tr("Route for car ({0}): ({1}, {2})->({3}, {4})->({5}, {6})->({7}, {8})->({9}, {10})->({11}, {12})").arg(
                                                car->toString()).arg(car->getLocationName()).arg(car->getTrackName()).arg(nlt->getLocation()->getName()).arg(
                                                        nlt->getName()).arg(mlt1->getLocation()->getName()).arg(mlt1->getName()).arg(
                                                        mlt2->getLocation()->getName()).arg(mlt2->getName()).arg(llt->getLocation()->getName()).arg(
                                                        llt->getName()).arg(car->getFinalDestinationName()).arg(
                                                        car->getFinalDestinationTrackName()));
                                    }
                                    // only set car's destination if specific train can service car
                                    if (finshSettingRouteFor(car, nlt)) {
                                        return true; // done 5 train routing
                                    }
                                    //break otherloop; // there was an issue with the first stop in the route
                                    loopOk = false;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
     log->debug(tr("Using 5 trains to route car to (%1) was unsuccessful").arg(car->getFinalDestinationName()));
        return foundRoute;
    }

    /*private*/ bool Router::finshSettingRouteFor(Car* car, Track* track) {
        // only set car's destination if specific train can service car
        Car* ts2 = clone(car);
        ts2->setDestinationTrack(track);
        QString specific = canSpecificTrainService(ts2);
        if (specific==(NO)) {
            addLine(_buildReport, SEVEN, tr("Train ({0}) can't transport car ({1}) directly to ({2}, {3})").arg(
                    _train->getName()).arg(car->toString()).arg(track->getLocation()->getName()).arg(track->getName()));
            _status = STATUS_NOT_THIS_TRAIN;
            return true;
        } else if (specific==(NOT_NOW)) {
            addLine(_buildReport, SEVEN, tr("Train ({0}) can't transport car ({1}) to ({2}, {3}) due to {4}").arg(
                    _train->getName()).arg(car->toString()).arg(track->getLocation()->getName()).arg(track->getName()).arg(
                            _train->getServiceStatus()));
            return true; // the issue is route moves or train length
        }
        // check to see if track is staging
        if (track->getTrackType()==(Track::STAGING)) {
            _status = car->setDestination(track->getLocation(), NULL);
        } else {
            _status = car->setDestination(track->getLocation(), track);
        }
        if (_status!=(Track::OKAY)) {
            addLine(_buildReport, SEVEN, tr("Can''t use {4} ({1}, {2}) for ({0}) due to {3}").arg(
                    car->toString()).arg(track->getLocation()->getName()).arg(track->getName()).arg(_status,
                            track->getTrackTypeName()));
            if (_status.startsWith(Track::LENGTH)) {
                return false;
            }
        }
        return true;
    }
#endif
    // sets clone car destination to final destination and track
    /*private*/ Car* Router::clone(Car* car) {
        Car* _clone = car->copy();
        // modify clone car length if car is part of kernel
        if (car->getKernel() != NULL) {
            _clone->setLength(QString::number(car->getKernel()->getTotalLength() - RollingStock::COUPLER));
        }
        _clone->setTrack(car->getTrack());
        _clone->setFinalDestination(car->getFinalDestination());
        // don't set the clone's final destination track, that will record the cars as being inbound
        // next two items is where the clone is different
        ((RollingStock*)_clone)->setDestination(car->getFinalDestination()); // note that final destination track can be NULL
        _clone->setDestinationTrack(car->getFinalDestinationTrack());
        return _clone;
    }

    /*private*/ void Router::loadTracks(Car* car, Car* testCar, QList<Track*> tracks)
    {
        foreach (Track* track, tracks)
        {
         if (track == car->getTrack())
         {
             continue; // don't use car's current track
         } // note that last could equal next if this routine was used for two train routing
         if (_lastLocationTracks.contains(track)) {
             continue;
         }
         QString status = track->accepts(testCar);
         if (status!=(Track::OKAY) && !status.startsWith(Track::LENGTH)) {
             continue; // track doesn't accept this car
         }
         if (debugFlag) {
             log->debug(tr("Found %1 track (%2) %3) for car (%4)").arg(track->getTrackType()).arg(track->getLocation()->getName(),
                     track->getName()).arg(car->toString()));
         }
         // test to see if there's a train that can deliver the car to this destination
         testCar->setDestinationTrack(track);
         Train* train = NULL;
         QString specific = canSpecificTrainService(testCar);
         if (specific==(YES) || specific==(NOT_NOW)) {
             train = _train;
         } else {
             train = TrainManager::instance()->getTrainForCar(testCar, NULL); // don't add to report
         }
         // Can specific train carry this car out of staging?
         if (car->getTrack()->getTrackType()==(Track::STAGING) && specific!=(YES)) {
             train = NULL;
         }
         // is the option to car by specific enabled?
         if (train != NULL && _train != NULL && _train->isServiceAllCarsWithFinalDestinationsEnabled()
                 && specific!=(YES)) {
             addLine(_buildReport, SEVEN, tr("Option to service all cars with a final destination enabled, ignoring train (%1) ability to service car (%2) to (%3), %4)").arg(train->getName()).arg(
                             car->toString()).arg(track->getLocation()->getName()).arg(track->getName()));
             train = NULL;
         }
         if (train != NULL) {
             if (debugFlag) {
                 log->debug(tr("Train (%1) can service car (%2) from %3 (%4, %5) to final destination (%6,%7)").arg(train
                         ->getName()).arg(car->toString()).arg(track->getTrackType()).arg(testCar->getLocationName()).arg(testCar
                         ->getTrackName()).arg(testCar->getDestinationName()).arg(testCar->getDestinationTrackName()));
             }
             _nextLocationTracks.append(track);
             _nextLocationTrains.append(train);
         } else {
             // don't add to other if already in last location list
             if (debugFlag) {
                 log->debug(tr("Adding location (%1, %2) to other locations").arg(track->getLocation()->getName()).arg(track
                         ->getName()));
             }
             _otherLocationTracks.append(track);
         }
        }
    }

    /*private*/ /*static*/ /*final*/ QString Router::NO = "no"; // NOI18N
    /*private*/ /*static*/ /*final*/ QString Router::YES = "yes"; // NOI18N
    /*private*/ /*static*/ /*final*/ QString Router::NOT_NOW = "not now"; // NOI18N
    /*private*/ /*static*/ /*final*/ QString Router::NO_SPECIFIC_TRAIN = "no specific train"; // NOI18

    /*private*/ QString Router::canSpecificTrainService(Car* car) {
        if (_train == NULL) {
            return NO_SPECIFIC_TRAIN;
        }
        if (_train->services(car)) {
            return YES;
        } // is the reason this train can't service route moves or train length?
        else if (_train->getServiceStatus()!=(Train::NONE)) {
            return NOT_NOW; // the issue is route moves or train length
        }
        return NO;
    }

}
