#include "htmlconductor.h"
#include "loggerfactory.h"
#include "routelocation.h"
#include "fileutil.h"
#include "setup.h"
#include "../operations/route.h"
#include "track.h"
#include "car.h"
#include "carmanager.h"
#include "location.h"
#include "enginemanager.h"
#include "stringescapeutils.h"
#include "instancemanager.h"

using namespace Operations;
/**
 *
 * @author rhwood
 */
///*public*/ class HtmlConductor extends HtmlTrainCommon {

/*private*/ /*final*/ /*static*/ Logger* HtmlConductor::log = LoggerFactory::getLogger("HtmlConductor");

/*public*/ HtmlConductor::HtmlConductor(QLocale locale, Operations::Train* train, QObject* parent) /*throw (IOException)*/: HtmlTrainCommon(locale, train, parent){
    //super(locale, train);
    this->resourcePrefix = "Conductor";  // NOI18N
}
#if 1
/*public*/ QString HtmlConductor::getLocation() /*throw (IOException)*/
{
 Operations::RouteLocation* location = train->getCurrentLocation();
 if (location == NULL)
 {
  return String::format(locale, FileUtil::readURL(FileUtil::findURL(tr(
             "web/servlet/operations/ConductorSnippet.html"))), train->getIconName(), StringEscapeUtils::escapeHtml4(train->getDescription()), StringEscapeUtils::escapeHtml4(train->getComment(true)), Operations::Setup
             ::isPrintRouteCommentsEnabled() ? train->getRoute()->getComment() : "", strings
             ->getProperty("Terminated"), "", // terminated train has nothing to do // NOI18N
             "", // engines in separate section
             "", // pickup=true, local=false
             "", // pickup=false, local=false
             "", // pickup=false, local=true
             "", // engines in separate section
             "", // terminate with NULL string, use empty string to indicate terminated
             strings->getProperty("Terminated"),  // NOI18N
             QString::number(train->getStatusCode()));
    }

    QList<Engine*>* engineList = ((EngineManager*)InstanceManager::getDefault("EngineManager"))->getByTrainBlockingList(train);
    QList<Car*>* carList = ((CarManager*)InstanceManager::getDefault("CarManager"))->getByTrainDestinationList(train);
    log->debug(tr("Train has %1 cars assigned to it").arg(carList->size()));

    QString pickups = performWork(true, false); // pickup=true, local=false
    QString setouts = performWork(false, false); // pickup=false, local=false
    QString localMoves = performWork(false, true); // pickup=false, local=true

//    return String::format(locale, FileUtil::readURL(FileUtil::findURL(tr(
//            "web/servlet/operations/ConductorSnippet.html"))), train->getIconName(), QString(QUrl(train->getDescription()).toEncoded()),
//            QString(QUrl(train->getComment()).toEncoded()), Setup::isPrintRouteCommentsEnabled() ? train
//                    ->getRoute()->getComment() : "", getCurrentAndNextLocation(),
//            getLocationComments(),
//            pickupEngines(engineList, location), // engines in separate section
//            pickups, setouts, localMoves,
//            dropEngines(engineList, location), // engines in separate section
//            (train->getNextLocation(train->getCurrentLocation()) != NULL) ? train->getNextLocationName() : NULL,
//            getMoveButton(),
//            QString::number(train->getStatusCode()));
    QString html = FileUtil::readURL(FileUtil::findURL(tr("web/servlet/operations/ConductorSnippet.html")));
    html = html.replace("%1$s", train->getIconName());
    html = html.replace("%2$s", StringEscapeUtils::escapeHtml4(train->getDescription()));
    html = html.replace("%3$s", StringEscapeUtils::escapeHtml4(train->getComment(true)));
    html = html.replace("%4$s", Setup::isPrintRouteCommentsEnabled() ? train->getRoute()->getComment() : "");
    html = html.replace("%5$s", getCurrentAndNextLocation());
    html = html.replace("%6$s", getLocationComments());
    html = html.replace("%7$s", pickupEngines(engineList, location)); // engines in separate section
    html = html.replace("%8$s", pickups);
    html = html.replace("%9$s", setouts);
    html = html.replace("%10$s", localMoves);
    html = html.replace("%11$s", dropEngines(engineList, location)); // engines in separate section
    html = html.replace("%12$s",  (train->getNextLocation(train->getCurrentLocation()) != NULL) ? train->getNextLocationName() : NULL);
    html = html.replace("%13$s", getMoveButton());
    return html;
}

/*private*/ QString HtmlConductor::getCurrentAndNextLocation()
{
 if (train->getCurrentLocation() != NULL && train->getNextLocation(train->getCurrentLocation()) != NULL)
 {
  return String::format(locale, strings->getProperty("CurrentAndNextLocation"), StringEscapeUtils::escapeHtml4(train->getCurrentLocationName()), StringEscapeUtils::escapeHtml4(train
                     ->getNextLocationName()));
 }
 else if (train->getCurrentLocation() != NULL)
 {
     return StringEscapeUtils::escapeHtml4(train->getCurrentLocationName());
 }
 return strings->getProperty("Terminated");  // NOI18N
}

/*private*/ QString HtmlConductor::getMoveButton()
{
 if (train->getNextLocation(train->getCurrentLocation()) != NULL)
 {
     return String::format(locale, strings->getProperty("MoveTo"), StringEscapeUtils::escapeHtml4(train  // NOI18N
             ->getNextLocationName()));
 } else if (train->getCurrentLocation() != NULL) {
     return strings->getProperty("Terminate");  // NOI18N
 }
 return strings->getProperty("Terminated");  // NOI18N
}

// needed for location comments, not yet in formatter
/*private*/ QString HtmlConductor::getEngineChanges(RouteLocation* location)
{
 // engine change or helper service?
 if (train->getSecondLegOptions() != Train::NO_CABOOSE_OR_FRED) {
     if (location == train->getSecondLegStartLocation()) {
         return engineChange(location, train->getSecondLegOptions());
     }
     if (location == train->getSecondLegEndLocation() && train->getSecondLegOptions() == Train::HELPER_ENGINES) {
         return String::format(strings->getProperty("RemoveHelpersAt"), splitString(location->getName())); // NOI18N
     }
 }
 if (train->getThirdLegOptions() != Train::NO_CABOOSE_OR_FRED)
 {
  if (location == train->getThirdLegStartLocation())
  {
      return engineChange(location, train->getSecondLegOptions());
  }
  if (location == train->getThirdLegEndLocation() && train->getThirdLegOptions() == Train::HELPER_ENGINES) {
      return String::format(strings->getProperty("RemoveHelpersAt"), splitString(location->getName())); // NOI18N
  }
 }
 return "";
}

/*private*/ QString HtmlConductor::getLocationComments()
{
 QList<Car*>* carList = ((CarManager*)InstanceManager::getDefault("CarManager"))->getByTrainDestinationList(train);
 QString builder;// = new StringBuilder();
 RouteLocation* routeLocation = train->getCurrentLocation();
 bool work = isThereWorkAtLocation(train, routeLocation->getLocation());

 // print info only if new location
 QString routeLocationName = StringEscapeUtils::escapeHtml4(splitString(routeLocation->getName()));
 if (work)
 {
  if (!train->isShowArrivalAndDepartureTimesEnabled()) {
      builder.append(String::format(locale, strings->getProperty("ScheduledWorkAt"), routeLocationName)); // NOI18N
  } else if (routeLocation == train->getRoute()->getDepartsRouteLocation()) {
      builder.append(String::format(locale, strings->getProperty("WorkDepartureTime"), routeLocationName, train  // NOI18N
              ->getFormatedDepartureTime())); // NOI18N
  } else if (routeLocation->getDepartureTime() != ("")) {
      builder.append(String::format(locale, strings->getProperty("WorkDepartureTime"), routeLocationName,  // NOI18N
              routeLocation->getFormatedDepartureTime())); // NOI18N
  } else if (Setup::isUseDepartureTimeEnabled()
          && routeLocation != train->getRoute()->getTerminatesRouteLocation()
          && train->getExpectedDepartureTime(routeLocation) != (Train::ALREADY_SERVICED)) {
      builder.append(String::format(locale, strings->getProperty("WorkDepartureTime"), routeLocationName, train  // NOI18N
              ->getExpectedDepartureTime(routeLocation)));
  } else if (train->getExpectedArrivalTime(routeLocation) != (Train::ALREADY_SERVICED)) {
      builder.append(String::format(locale, strings->getProperty("WorkArrivalTime"), routeLocationName, train  // NOI18N
              ->getExpectedArrivalTime(routeLocation))); // NOI18N
  } else {
      builder.append(String::format(locale, strings->getProperty("ScheduledWorkAt"), routeLocationName)); // NOI18N
  }
  // add route comment
  if (routeLocation->getComment().trimmed() != ("")) {
      builder.append(String::format(locale, strings->getProperty("RouteLocationComment"), StringEscapeUtils::escapeHtml4(routeLocation->getComment())));
  }

  builder.append(getTrackComments(routeLocation, carList));

  // add location comment
  if (Setup::isPrintLocationCommentsEnabled() && !routeLocation->getLocation()->getComment().isEmpty()) {
      builder.append(String::format(locale, strings->getProperty("LocationComment"), StringEscapeUtils::escapeHtml4(routeLocation->getLocation()->getComment())));
  }
 }

 // engine change or helper service?
 builder.append(this->getEngineChanges(routeLocation));

 if (routeLocation != train->getRoute()->getTerminatesRouteLocation())
 {
  if (work)
  {
   if (!Setup::isPrintLoadsAndEmptiesEnabled())
   {
    // Message format: Train departs Boston Westbound with 12 cars, 450 feet, 3000 tons
    builder.append(String::format(strings->getProperty("TrainDepartsCars"), routeLocationName,  // NOI18N
            routeLocation->getTrainDirectionString(), QString::number(train->getTrainLength(routeLocation)), Setup::
            getLengthUnit().toLower(), QString::number(train->getTrainWeight(routeLocation)), QString::number(train
            ->getNumberCarsInTrain(routeLocation))));
   }
   else
   {
    // Message format: Train departs Boston Westbound with 4 loads, 8 empties, 450 feet, 3000 tons
    int emptyCars = train->getNumberEmptyCarsInTrain(routeLocation);
    builder.append(String::format(strings->getProperty("TrainDepartsLoads"), routeLocationName,  // NOI18N
            routeLocation->getTrainDirectionString(), QString::number(train->getTrainLength(routeLocation)), Setup::
            getLengthUnit().toLower(), QString::number(train->getTrainWeight(routeLocation)), QString::number(train
            ->getNumberCarsInTrain(routeLocation)
            - emptyCars), QString::number(emptyCars)));
   }
  } else {
      if (routeLocation->getComment().trimmed().isEmpty()) {
          // no route comment, no work at this location
          if (train->isShowArrivalAndDepartureTimesEnabled()) {
              if (routeLocation == train->getRoute()->getDepartsRouteLocation()) {
                  builder.append(String::format(locale, strings
                          ->getProperty("NoScheduledWorkAtWithDepartureTime"), routeLocationName, train  // NOI18N
                          ->getFormatedDepartureTime()));
              } else if (!routeLocation->getDepartureTime().isEmpty()) {
                  builder.append(String::format(locale, strings
                          ->getProperty("NoScheduledWorkAtWithDepartureTime"), routeLocationName,  // NOI18N
                          routeLocation->getFormatedDepartureTime()));
              } else {
                  builder.append(String::format(locale, strings->getProperty("NoScheduledWorkAt"),  // NOI18N
                          routeLocationName));
              }
          } else {
              builder.append(String::format(locale, strings->getProperty("NoScheduledWorkAt"),  // NOI18N
                      routeLocationName));
          }
      } else {
          // route comment, so only use location and route comment (for passenger trains)
          if (train->isShowArrivalAndDepartureTimesEnabled()) {
              if (routeLocation == train->getRoute()->getDepartsRouteLocation()) {
                  builder.append(String::format(locale, strings->getProperty("CommentAtWithDepartureTime"),  // NOI18N
                          routeLocationName, train->getFormatedDepartureTime(), StringEscapeUtils::escapeHtml4(routeLocation->getComment())));
              } else if (!routeLocation->getDepartureTime().isEmpty()) {
                  builder.append(String::format(locale, strings->getProperty("CommentAtWithDepartureTime"),  // NOI18N
                          routeLocationName, routeLocation->getFormatedDepartureTime(), StringEscapeUtils::escapeHtml4(routeLocation->getComment())));
              }
          } else {
              builder.append(String::format(locale, strings->getProperty("CommentAt"), routeLocationName, NULL,  // NOI18N
                      StringEscapeUtils::escapeHtml4(routeLocation->getComment())));
          }
      }
      // add location comment
      if (Setup::isPrintLocationCommentsEnabled() && !routeLocation->getLocation()->getComment().isEmpty()) {
          builder.append(String::format(locale, strings->getProperty("LocationComment"), StringEscapeUtils::escapeHtml4(routeLocation->getLocation()->getComment())));
      }
  }
 } else {
     builder.append(String::format(strings->getProperty("TrainTerminatesIn"), routeLocationName));  // NOI18N
 }
 return builder/*.toString()*/;
}

/*private*/ QString HtmlConductor::performWork(bool pickup, bool local) {
    if (pickup) {
       return pickupCars();
    } else {
        return dropCars(local);
    }
}
#endif
/*private*/ QString HtmlConductor::pickupCars() {
    QString builder;// = new StringBuilder();
    RouteLocation* location = train->getCurrentLocation();
    QList<Car*>* carList = ((CarManager*)InstanceManager::getDefault("CarManager"))->getByTrainDestinationList(train);
    QList<Track*> tracks = location->getLocation()->getTrackByNameList(NULL);
    QStringList trackNames = QStringList();
    QStringList pickedUp = QStringList();
    this->clearUtilityCarTypes();
    for (Track* track : tracks) {
        if (trackNames.contains(splitString(track->getName()))) {
            continue;
        }
        trackNames.append(splitString(track->getName())); // use a track name once
        // block cars by destination
        for (RouteLocation* rld : *train->getRoute()->getLocationsBySequenceList()) {
            for (Car* car : *carList) {
                if (pickedUp.contains(car->getId())
                        || (Setup::isSortByTrackEnabled() && splitString(track->getName()) != (
                                splitString(car->getTrackName())))) {
                    continue;
                }
                // note that a car in train doesn't have a track assignment
                if (car->getRouteLocation() == location && car->getTrack() != NULL
                        && car->getRouteDestination() == rld) {
                    pickedUp.append(car->getId());
                    if (car->isUtility()) {
                        builder.append(pickupUtilityCars(carList, car, TrainCommon::IS_MANIFEST));
                     // use truncated format if there's a switch list
                    } else if (Setup::isTruncateManifestEnabled() && location->getLocation()->isSwitchListEnabled()) {
                        builder.append(pickUpCar(car, Setup::getPickupTruncatedManifestMessageFormat()));
                    } else {
                        builder.append(pickUpCar(car, Setup::getPickupManifestMessageFormat()));
                    }
                }
            }
        }
    }
    return builder/*.toString()*/;
}

/*private*/ QString HtmlConductor::dropCars(bool local) {
    QString builder;// = new StringBuilder();
    Operations::RouteLocation* location = train->getCurrentLocation();
    QList<Operations::Car*>* carList = ((CarManager*)InstanceManager::getDefault("CarManager"))->getByTrainDestinationList(train);
    QList<Operations::Track*> tracks = location->getLocation()->getTrackByNameList(NULL);
    QStringList trackNames = QStringList();
    QStringList dropped = QStringList();
    for (Operations::Track* track : tracks) {
        if (trackNames.contains(splitString(track->getName()))) {
            continue;
        }
        trackNames.append(splitString(track->getName())); // use a track name once
        for (Operations::Car* car : *carList) {
            if (dropped.contains(car->getId())
                    || (Operations::Setup::isSortByTrackEnabled() && splitString(track->getName()) != (
                            splitString(car->getDestinationTrackName())))) {
                continue;
            }
            if (isLocalMove(car) == local
                    && (car->getRouteDestination() == location && car->getDestinationTrack() != NULL)) {
                dropped.append(car->getId());
                if (car->isUtility()) {
                    builder.append(setoutUtilityCars(carList, car, local));
                } else {
                     QStringList format = (!local) ? Operations::Setup::getDropManifestMessageFormat() : Operations::Setup
                            ::getLocalManifestMessageFormat();
                    builder.append(dropCar(car, format, local));
                }
            }
        }
    }
    return builder/*.toString()*/;
}

