#include "htmlmanifest.h"
#include "loggerfactory.h"
#include "setup.h"
#include "jsonoperations.h"
#include "trainschedulemanager.h"
#include "../operations/route.h"
#include "json.h"
#include "routelocation.h"
#include "jsonmanifest.h"
#include "trainschedule.h"
#include "routelocation.h"
#include "location.h"
#include "stringescapeutils.h"
#include "instancemanager.h"

using namespace Operations;
/**
 *
 * @author rhwood
 */
///*public*/ class HtmlManifest extends HtmlTrainCommon {

/*private*/ /*final*/ /*static*/ Logger* HtmlManifest::log = LoggerFactory::getLogger("HtmlManifest");

/*public*/ HtmlManifest::HtmlManifest(QLocale locale, Operations::Train* train, QObject* parent) throw (IOException) : HtmlTrainCommon(locale, train, parent){
    //super(locale, train);
    this->mapper = ObjectMapper();
    this->resourcePrefix = "Manifest";
}

// TODO cache the results so a quick check that if the JsonManifest file is not
// newer than the Html manifest, the cached copy is returned instead.
/*public*/ QString HtmlManifest::getLocations() throw (IOException)
{
 // build manifest from JSON manifest
 if (this->getJsonManifest().isEmpty()) {
     return "Error manifest file not found for this train";
 }
 QString builder;// = new StringBuilder();
 QJsonArray locations =  this->getJsonManifest().value(JsonOperations::LOCATIONS).toArray();
 QString previousLocationName = NULL;
 bool hasWork;
 foreach (QJsonValue value,  locations)
 {
  QJsonObject location = value.toObject();
  Operations::RouteLocation* routeLocation = train->getRoute()->getLocationById(location.value(JSON::ID).toString());
  log->debug(tr("Processing %1 (%2)").arg(routeLocation->getName()).arg( location.value(JSON::ID).toString()));
  QString routeLocationName = location.value(JSON::NAME).toString();
//#if 1
  builder.append(String::format(locale, strings->getProperty("LocationStart"), routeLocation->getId())); // NOI18N
  hasWork = (location.value(JsonOperations::CARS).toObject().value(JSON::ADD).toObject().size() > 0
          || location.value(JsonOperations::CARS).toObject().value(JSON::REMOVE).toObject().size() > 0
          || location.value(JSON::ENGINES).toObject().value(JSON::ADD).toObject().size() > 0 || location.value(JSON::ENGINES).toObject().value(
                  JSON::REMOVE).toObject().size() > 0);
  if (hasWork && routeLocationName != (previousLocationName))
  {
   if (!train->isShowArrivalAndDepartureTimesEnabled())
   {
       builder.append(String::format(locale, strings->getProperty("ScheduledWorkAt"), routeLocationName)); // NOI18N
   } else if (routeLocation == train->getRoute()->getDepartsRouteLocation()) {
       builder.append(String::format(locale, strings->getProperty("WorkDepartureTime"), routeLocationName,
               train->getFormatedDepartureTime())); // NOI18N
   } else if (routeLocation->getDepartureTime() != (Operations::RouteLocation::NONE)) {
       builder.append(String::format(locale, strings->getProperty("WorkDepartureTime"), routeLocationName,
               routeLocation->getFormatedDepartureTime())); // NOI18N
   } else if (Operations::Setup::isUseDepartureTimeEnabled()
           && routeLocation != train->getRoute()->getTerminatesRouteLocation()) {
       builder.append(String::format(locale, strings->getProperty("WorkDepartureTime"), routeLocationName,
               train->getExpectedDepartureTime(routeLocation))); // NOI18N
   } else if (train->getExpectedArrivalTime(routeLocation) != (Operations::Train::ALREADY_SERVICED)) { // NOI18N
       builder.append(String::format(locale, strings->getProperty("WorkArrivalTime"), routeLocationName,
               train->getExpectedArrivalTime(routeLocation))); // NOI18N
   } else {
       builder.append(String::format(locale, strings->getProperty("ScheduledWorkAt"), routeLocationName)); // NOI18N
   }
   // add route comment
   if (!location.value(JSON::COMMENT).toString().trimmed().isEmpty()) {
       builder.append(String::format(locale, strings->getProperty("RouteLocationComment"), location.value(JSON::COMMENT).toString()));
   }

   builder.append(getTrackComments(location.value(JsonOperations::TRACK).toObject(), location.value(JsonOperations::CARS).toObject()));

   // add location comment
   if (Operations::Setup::isPrintLocationCommentsEnabled()
           && !location.value(JsonOperations::LOCATION).toObject().value(JSON::COMMENT).toString().trimmed().isEmpty()) {
       builder.append(String::format(locale, strings->getProperty("LocationComment"), location.value(
               JsonOperations::LOCATION).toObject().value(JSON::COMMENT).toString()));
   }
  }

  previousLocationName = routeLocationName;
#if 1
  // engine change or helper service?
  if (location.value(JSON::OPTIONS).toArray().size() > 0)
  {
   //Iterator<QJsonObject> options = location.value(JSON::OPTIONS).elements();
   QVariantList list = location.value(JSON::OPTIONS).toArray().toVariantList();
   QListIterator<QVariant> options(list);
    bool changeEngines = false;
    bool changeCaboose = false;
   while (options.hasNext()) {
       QString option = options.next().toString();
       if (option == (JSON::CHANGE_ENGINES)) {
           changeEngines = true;
       } else if (option == (JSON::CHANGE_CABOOSE)) {
           changeCaboose = true;
       } else if (option == (JSON::ADD_HELPERS)) {
           builder.append(String::format(strings->getProperty("AddHelpersAt"), routeLocationName));
       } else if (option == (JSON::REMOVE_HELPERS)) {
           builder.append(String::format(strings->getProperty("RemoveHelpersAt"), routeLocationName));
       }
   }
   if (changeEngines && changeCaboose) {
       builder.append(String::format(strings->getProperty("LocoAndCabooseChangeAt"), routeLocationName)); // NOI18N
   } else if (changeEngines) {
       builder.append(String::format(strings->getProperty("LocoChangeAt"), routeLocationName)); // NOI18N
   } else if (changeCaboose) {
       builder.append(String::format(strings->getProperty("CabooseChangeAt"), routeLocationName)); // NOI18N
   }
  }

  builder.append(pickupEngines(location.value(JSON::ENGINES).toObject().value(JSON::ADD).toObject()));
  builder.append(blockCars(location.value(JsonOperations::CARS).toObject(), routeLocation, true));
  builder.append(dropEngines(location.value(JSON::ENGINES).toObject().value(JSON::REMOVE).toObject()));

  if (routeLocation != train->getRoute()->getTerminatesRouteLocation())
  {
   // Is the next location the same as the current?
   Operations::RouteLocation* rlNext = train->getRoute()->getNextRouteLocation(routeLocation);
   if (routeLocationName != (splitString(rlNext->getName())))
   {
    if (hasWork)
    {
     if (!Operations::Setup::isPrintLoadsAndEmptiesEnabled())
     {
      // Message format: Train departs Boston Westbound with 12 cars, 450 feet, 3000 tons
      builder.append(String::format(strings->getProperty("TrainDepartsCars"), routeLocationName,
              strings->getProperty("Heading"
                      + Operations::Setup::getDirectionString(location.value(JSON::DIRECTION).toInt())),
                                    QString::number(location.value(JSON::LENGTH).toObject().value(JSON::LENGTH).toInt()),
                                    location.value(JSON::LENGTH).toObject().value(JSON::UNIT).toString().toLower(),
                                    QString::number(location.value(JsonOperations::WEIGHT).toString().toInt()),
                                    QString::number(location.value(JsonOperations::CARS).toObject().value(JSON::TOTAL).toInt())));
     }
     else
     {
      // Message format: Train departs Boston Westbound with 4 loads, 8 empties, 450 feet, 3000
      // tons
      builder.append(String::format(strings->getProperty("TrainDepartsLoads"), routeLocationName,
              strings->getProperty("Heading"
                      + Operations::Setup::getDirectionString(location.value(JSON::DIRECTION).toInt())),
              QString::number(location.value(JSON::LENGTH).toObject().value(JSON::LENGTH).toInt()), location.value(JSON::LENGTH).toObject()
              .value(JSON::UNIT).toString().toLower(), QString::number(location.value(JsonOperations::WEIGHT)
              .toInt()),
                                    QString::number(location.value(JsonOperations::CARS).toObject().value(JSON::LOADS).toInt()),
                                    QString::number(location             .value(JsonOperations::CARS).toObject().value(JSON::EMPTIES).toInt())));
     }
    }
    else
    {
     log->debug(tr("No work (%1)").arg(routeLocation->getComment()));
     if (routeLocation->getComment().trimmed().isEmpty())
     {
      // no route comment, no work at this location
      if (train->isShowArrivalAndDepartureTimesEnabled())
      {
          if (routeLocation == train->getRoute()->getDepartsRouteLocation()) {
              builder.append(String::format(locale, strings
                      ->getProperty("NoScheduledWorkAtWithDepartureTime"), routeLocationName,
                      train->getFormatedDepartureTime()));
          } else if (!routeLocation->getDepartureTime().isEmpty()) {
              builder.append(String::format(locale, strings
                      ->getProperty("NoScheduledWorkAtWithDepartureTime"), routeLocationName,
                      routeLocation->getFormatedDepartureTime()));
          } else if (Operations::Setup::isUseDepartureTimeEnabled()) {
              builder.append(String::format(locale, strings
                      ->getProperty("NoScheduledWorkAtWithDepartureTime"), routeLocationName,
                      location.value(JSON::EXPECTED_DEPARTURE).toString()));
          } else { // fall back to generic no scheduled work message
              builder.append(String::format(locale, strings->getProperty("NoScheduledWorkAt"),
                      routeLocationName));
          }
      } else {
          builder.append(String::format(locale, strings->getProperty("NoScheduledWorkAt"),
                  routeLocationName));
      }
  } else {
      // route comment, so only use location and route comment (for passenger trains)
      if (train->isShowArrivalAndDepartureTimesEnabled()) {
          if (routeLocation == train->getRoute()->getDepartsRouteLocation()) {
              builder.append(String::format(locale, strings
                      ->getProperty("CommentAtWithDepartureTime"), routeLocationName, train
                      ->getFormatedDepartureTime(), routeLocation->getComment()));
          } else if (!routeLocation->getDepartureTime().isEmpty()) {
              builder.append(String::format(locale, strings
                      ->getProperty("CommentAtWithDepartureTime"), routeLocationName,
                      routeLocation->getFormatedDepartureTime(), routeLocation->getComment()));
          }
      } else {
          builder.append(String::format(locale, strings->getProperty("CommentAt"),
                  routeLocationName, NULL, routeLocation->getComment()));
      }
     }
     // add location comment
     if (Operations::Setup::isPrintLocationCommentsEnabled()
             && !routeLocation->getLocation()->getComment().isEmpty()) {
         builder.append(String::format(locale, strings->getProperty("LocationComment"), routeLocation
                 ->getLocation()->getComment()));
     }
    }
   }
  }
  else
  {
   builder.append(String::format(strings->getProperty("TrainTerminatesIn"), routeLocationName));
  }
#endif
 }
 return builder/*.toString()*/;
}
#if 1
/*protected*/ QString HtmlManifest::blockCars(QJsonObject cars, Operations::RouteLocation* location,  bool isManifest)
{
 QString builder;// = new StringBuilder();
 if (cars.value(JSON::ADD).toObject().size() > 0 || cars.value(JSON::REMOVE).toObject().size() > 0)
 {
  if (cars.value(JSON::ADD).toObject().size() > 0)
  {
   for (QJsonValue car : cars.value(JSON::ADD).toObject())
   {
    if (!this->isLocalMove(car.toObject()))
    {
     // TODO utility format not quite ready, so display each car in manifest for now.
     // if (this->isUtilityCar(car)) {
     // builder.append(pickupUtilityCars(cars, car, location, isManifest));
     // } // use truncated format if there's a switch list
     // else
     if (isManifest && Operations::Setup::isTruncateManifestEnabled()
             && location->getLocation()->isSwitchListEnabled()) {
         builder.append(pickUpCar(car.toObject(), Operations::Setup::getPickupTruncatedManifestMessageFormat()));
     } else {
         builder.append(pickUpCar(car.toObject(), Operations::Setup::getPickupManifestMessageFormat()));
     }
    }
   }
  }
  if (cars.value(JSON::REMOVE).toObject().size() > 0)
  {
   for (QJsonValue car : cars.value(JSON::REMOVE).toObject())
   {
     bool local = isLocalMove(car.toObject());
    // TODO utility format not quite ready, so display each car in manifest for now.
    // if (this->isUtilityCar(car)) {
    // builder.append(setoutUtilityCars(cars, car, location, isManifest));
    // } else
    if (isManifest && Operations::Setup::isTruncateManifestEnabled() && location->getLocation()->isSwitchListEnabled() && !train->isLocalSwitcher()) {
        // use truncated format if there's a switch list
        builder.append(dropCar(car.toObject(), Operations::Setup::getDropTruncatedManifestMessageFormat(), local));
    }
    else
    {
     QStringList format;
     if (isManifest)
     {
         format = (!local) ? Operations::Setup::getDropManifestMessageFormat() : Operations::Setup::getLocalManifestMessageFormat();
     } else {
         format = (!local) ? Operations::Setup::getDropSwitchListMessageFormat() : Operations::Setup::getLocalSwitchListMessageFormat();
     }
     builder.append(dropCar(car.toObject(), format, local));
    }
   }
  }
 }
 return String::format(locale, strings->getProperty("CarsList"), builder/*.toString()*/);
}
#endif
/*protected*/ QString HtmlManifest::pickupUtilityCars(QJsonObject cars, QJsonObject car, Operations::RouteLocation* location,  bool isManifest) {
    // list utility cars by type, track, length, and load
    QStringList messageFormat;
    if (isManifest) {
        messageFormat = Operations::Setup::getPickupUtilityManifestMessageFormat();
    } else {
        messageFormat = Operations::Setup::getPickupUtilitySwitchListMessageFormat();
    }
    // TODO: reimplement following commented out code
    // if (this->countUtilityCars(messageFormat, carList, car, location, rld, PICKUP) == 0) {
    // return ""; // already printed out this car type
    // }
    return this->pickUpCar(car, messageFormat);
}

/*protected*/ QString HtmlManifest::setoutUtilityCars(QJsonObject cars, QJsonObject car, Operations::RouteLocation* location,  bool isManifest) {
     bool isLocal = isLocalMove(car);
    QStringList messageFormat;
    if (isLocal && isManifest) {
        messageFormat = Operations::Setup::getLocalUtilityManifestMessageFormat();
    } else if (isLocal && !isManifest) {
        messageFormat = Operations::Setup::getLocalUtilitySwitchListMessageFormat();
    } else if (!isLocal && !isManifest) {
        messageFormat = Operations::Setup::getDropUtilitySwitchListMessageFormat();
    } else {
        messageFormat = Operations::Setup::getDropUtilityManifestMessageFormat();
    }
    // TODO: reimplement following commented out code
    // if (countUtilityCars(messageFormat, carList, car, location, NULL, !PICKUP) == 0) {
    // return ""; // already printed out this car type
    // }
    return dropCar(car, messageFormat, isLocal);
}

/*protected*/ QString HtmlManifest::pickUpCar(QJsonObject car, QStringList format) {
    if (isLocalMove(car)) {
        return ""; // print nothing for local move, see dropCar()
    }
    QString builder;// = new StringBuilder();
    for (QString attribute : format) {
        if (attribute.trimmed() != ("")) {
            attribute = attribute.toLower();
            log->debug(tr("Adding car with attribute %1").arg(attribute));
            if (attribute == (JsonOperations::LOCATION) || attribute == (JsonOperations::TRACK)) {
                attribute = JsonOperations::LOCATION; // treat "track" as "location"
                builder.append(
                        this->getFormattedAttribute(attribute, this->getPickupLocation(car.value(attribute).toObject(),
                                        ShowLocation::track))).append(" "); // NOI18N
            } else if (attribute == (JsonOperations::DESTINATION)) {
                builder.append(
                        this->getFormattedAttribute(attribute, this->getDropLocation(car.value(attribute).toObject(),
                                        ShowLocation::location))).append(" "); // NOI18N
            } else if (attribute == (JsonOperations::DESTINATION_TRACK)) {
                builder.append(
                        this->getFormattedAttribute(attribute, this->getDropLocation(car.value(JsonOperations::LOCATION).toObject(),
                                        ShowLocation::both))).append(" "); // NOI18N
            } else {
                builder.append(this->getTextAttribute(attribute, car)).append(" "); // NOI18N
            }
        }
    }
    log->debug(tr("Picking up car %1").arg(builder));
    return String::format(locale, strings->getProperty(this->resourcePrefix + "PickUpCar"), builder/*.toString()*/); // NOI18N
}

/*protected*/ QString HtmlManifest::dropCar(QJsonObject car, QStringList format,  bool isLocal) {
    QString builder;// = new StringBuilder();
    for (QString attribute : format) {
        if (attribute.trimmed() != ("")) {
            attribute = attribute.toLower();
            log->debug(tr("Removing car with attribute %1").arg(attribute));
            if (attribute == (JsonOperations::DESTINATION) || attribute == (JsonOperations::TRACK)) {
                attribute = JsonOperations::DESTINATION; // treat "track" as "destination"
                builder.append(
                        this->getFormattedAttribute(attribute, this->getDropLocation(car.value(attribute).toObject(),
                                        ShowLocation::track))).append(" "); // NOI18N
            } else if (attribute == (JsonOperations::LOCATION) && isLocal) {
                builder.append(
                        this->getFormattedAttribute(attribute, this->getPickupLocation(car.value(attribute).toObject(),
                                        ShowLocation::track))).append(" "); // NOI18N
            } else if (attribute == (JsonOperations::LOCATION)) {
                builder.append(
                        this->getFormattedAttribute(attribute, this->getPickupLocation(car.value(attribute).toObject(),
                                        ShowLocation::location))).append(" "); // NOI18N
            } else {
                builder.append(this->getTextAttribute(attribute, car)).append(" "); // NOI18N
            }
        }
    }
    log->debug(tr("Dropping %1car %2").arg((isLocal) ? "local " : "").arg(builder));
    if (!isLocal) {
        return String::format(locale, strings->getProperty(this->resourcePrefix + QString("DropCar")), builder/*.toString()*/); // NOI18N
    } else {
        return String::format(locale, strings->getProperty(this->resourcePrefix + "LocalCar"), builder/*.toString()*/); // NOI18N
    }
}

/*protected*/ QString HtmlManifest::dropEngines(QJsonObject engines)
{
 QString builder;// = new StringBuilder();
 if (engines.size() > 0)
 {
  for (QJsonValue engine : engines)
  {
   builder.append(this->dropEngine(engine.toObject()));
  }
 }
 return String::format(locale, strings->getProperty("EnginesList"), builder/*.toString()*/);
}

/*protected*/ QString HtmlManifest::dropEngine(QJsonObject engine) {
    QString builder;// = new StringBuilder();
    for (QString attribute : Operations::Setup::getDropEngineMessageFormat()) {
        if (attribute.trimmed() != ("")) {
            attribute = attribute.toLower();
            if (attribute == (JsonOperations::DESTINATION) || attribute == (JsonOperations::TRACK)) {
                attribute = JsonOperations::DESTINATION; // treat "track" as "destination"
                builder.append(
                        this->getFormattedAttribute(attribute, this->getDropLocation(engine.value(attribute).toObject(),
                                        ShowLocation::track))).append(" "); // NOI18N
            } else {
                builder.append(this->getTextAttribute(attribute, engine)).append(" "); // NOI18N
            }
        }
    }
    log->debug(tr("Drop engine: %1").arg(builder));
    return String::format(locale, strings->getProperty(this->resourcePrefix + "DropEngine"), builder/*.toString()*/);
}

/*protected*/ QString HtmlManifest::pickupEngines(QJsonObject engines) {
    QString builder;// = new StringBuilder();
    if (engines.size() > 0) {
        for (QJsonValue engine : engines) {
            builder.append(this->pickupEngine(engine.toObject()));
        }
    }
    return String::format(locale, strings->getProperty("EnginesList"), builder/*.toString()*/);
}

/*protected*/ QString HtmlManifest::pickupEngine(QJsonObject engine) {
    QString builder;// = new StringBuilder();
    log->debug(tr("PickupEngineMessageFormat: %1").arg( Operations::Setup::getPickupEngineMessageFormat().at(0)));
    for (QString attribute : Operations::Setup::getPickupEngineMessageFormat()) {
        if (attribute.trimmed() != ("")) {
            attribute = attribute.toLower();
            if (attribute == (JsonOperations::LOCATION) || attribute == (JsonOperations::TRACK)) {
                attribute = JsonOperations::LOCATION; // treat "track" as "location"
                builder.append(
                        this->getFormattedAttribute(attribute, this->getPickupLocation(engine.value(attribute).toObject(),
                                        HtmlTrainCommon::ShowLocation::track))).append(" "); // NOI18N
            } else {
                builder.append(this->getTextAttribute(attribute, engine)).append(" "); // NOI18N
            }
        }
    }
    log->debug(tr("Picking up engine: %1").arg(builder));
    return String::format(locale, strings->getProperty(this->resourcePrefix + "PickUpEngine"), builder/*.toString()*/);
}

/*protected*/ QString HtmlManifest::getDropLocation(QJsonObject location, HtmlTrainCommon::ShowLocation show) {
    return this->getFormattedLocation(location, show, "To"); // NOI18N
}

/*protected*/ QString HtmlManifest::getPickupLocation(QJsonObject location, HtmlTrainCommon::ShowLocation show) {
    return this->getFormattedLocation(location, show, "From"); // NOI18N
}

/*protected*/ QString HtmlManifest::getTextAttribute(QString attribute, QJsonObject rollingStock) {
    if (attribute == (JSON::HAZARDOUS)) {
        return this->getFormattedAttribute(attribute, (rollingStock.value(attribute).toBool() ? Operations::Setup
                ::getHazardousMsg() : "")); // NOI18N
    } else if (attribute == (Operations::Setup::PICKUP_COMMENT.toLower())) { // NOI18N
        return this->getFormattedAttribute(JSON::ADD_COMMENT, rollingStock.value(JSON::ADD_COMMENT).toString());
    } else if (attribute == (Operations::Setup::DROP_COMMENT.toLower())) { // NOI18N
        return this->getFormattedAttribute(JSON::ADD_COMMENT, rollingStock.value(JSON::ADD_COMMENT).toString());
    } else if (attribute == (Operations::Setup::RWE.toLower())) {
        return this->getFormattedAttribute(JSON::RETURN_WHEN_EMPTY, this->getFormattedLocation(rollingStock
                .value(JSON::RETURN_WHEN_EMPTY).toObject(), HtmlTrainCommon::ShowLocation::both, QString("RWE"))); // NOI18N
    } else if (attribute == (Operations::Setup::FINAL_DEST.toLower())) {
        return this->getFormattedAttribute(JSON::FINAL_DESTINATION, this->getFormattedLocation(rollingStock
                .value(JSON::FINAL_DESTINATION).toObject(), HtmlTrainCommon::ShowLocation::location, QString("FinalDestination"))); // NOI18N
    } else if (attribute == (Operations::Setup::FINAL_DEST_TRACK.toLower())) {
        return this->getFormattedAttribute(JSON::FINAL_DESTINATION, this->getFormattedLocation(rollingStock
                .value(JSON::FINAL_DESTINATION).toObject(), HtmlTrainCommon::ShowLocation::track, "FinalDestination")); // NOI18N
    }
    return this->getFormattedAttribute(attribute, rollingStock.value(attribute).toString());
}

/*protected*/ QString HtmlManifest::getFormattedAttribute(QString attribute, QString value) {
    return String::format(locale, strings->getProperty("Attribute"), StringEscapeUtils::escapeHtml4(value), attribute);
}

/*protected*/ QString HtmlManifest::getFormattedLocation(QJsonObject location, HtmlTrainCommon::ShowLocation show, QString prefix) {
    // TODO handle tracks without names
    switch (show) {
        case HtmlTrainCommon::ShowLocation::location:
            return String::format(locale, strings->getProperty(prefix + "Location"), location.value(JSON::NAME).toString());
        case track:
            return String::format(locale, strings->getProperty(prefix + "Track"), location.value(JsonOperations::TRACK).toObject().value(JSON::NAME).toString());
        case both:
        default: // default here ensures the method always returns
            return String::format(locale, strings->getProperty(prefix + "LocationAndTrack"), location.value(JSON::NAME).toString(), location.value(JsonOperations::TRACK).toObject().value(JSON::NAME).toString());
    }
}

/*private*/ QString HtmlManifest::getTrackComments(QJsonObject tracks, QJsonObject cars)
{
 QString builder;// = new StringBuilder();
 if (tracks.size() > 0)
 {
#if 1
     //Iterator<Entry<String, QJsonObject>> iterator = tracks.fields();
//   while (iterator.hasNext()) {
//   Entry<String, QJsonObject> track = iterator.next();
  foreach(const QString& key, tracks.keys())
  {
   bool pickup = false;
   bool setout = false;
   if (cars.value(JSON::ADD).toArray().size() > 0)
   {
    foreach (QJsonValue value, cars.value(JSON::ADD).toArray())
    {
     QJsonObject car = value.toObject();
        if (/*track.key_type()*/ key == (car.value(JsonOperations::TRACK).toObject().value(JSON::ID).toString())) {
            pickup = true;
            break; // we do not need to iterate all cars
        }
    }
   }
   if (cars.value(JSON::REMOVE).toArray().size() > 0)
   {
    foreach (QJsonValue value, cars.value(JSON::REMOVE).toArray())
    {
     QJsonObject car = value.toObject();
     if (/*track.key_type()*/key == (car.value(JsonOperations::TRACK).toObject().value(JSON::ID).toString())) {
         setout = true;
         break; // we do not need to iterate all cars
     }
    }
   }
   if (pickup && setout)
   {
      builder.append(String::format(locale, strings->getProperty("TrackComments"), /*track.*/tracks.value(key).toObject().value(
              JSON::ADD_AND_REMOVE).toString()));
   }
   else if (pickup) {
      builder.append(String::format(locale, strings->getProperty("TrackComments"), /*track.*/tracks.value(key).toObject().value(
              JSON::ADD).toString()));
   }
   else if (setout) {
      builder.append(String::format(locale, strings->getProperty("TrackComments"), /*track.*/tracks.value(key).toObject().value(
              JSON::REMOVE).toString()));
   }
  }
#endif
 }
 return builder/*.toString()*/;
}

/*protected*/  bool HtmlManifest::isLocalMove(QJsonObject car) {
    if (car.value(JsonOperations::LOCATION).toObject().value(JSON::ROUTE).isUndefined()
            || car.value(JsonOperations::DESTINATION).toObject().value(JSON::ROUTE).isUndefined()) {
        return false;
    }
    return car.value(JsonOperations::LOCATION).toObject().value(JSON::ROUTE) == (car.value(JsonOperations::DESTINATION).toObject().value(JSON::ROUTE));
}

/*protected*/  bool HtmlManifest::isUtilityCar(QJsonObject car) {
    return car.value(JSON::UTILITY). toBool();
}

/*protected*/ QJsonObject HtmlManifest::getJsonManifest() throw (IOException)
{
 if (this->jsonManifest.isEmpty())
 {
  try
  {
   //this->jsonManifest = this->mapper.readTree((new JsonManifest(this->train)).getFile());
   JsonManifest* manifest = new JsonManifest(this->train);
   File* file = manifest->getFile();
   QFile f(file->getPath());
   if(!f.open(QIODevice::ReadOnly))
    throw IOException(f.fileName());
   QTextStream is(&f);
   this->jsonManifest =  QJsonDocument::fromJson(is.readAll().toLocal8Bit()).object();
  }
  catch (IOException e)
  {
   log->error(tr("Json manifest file not found for train (%1)").arg(this->train->getName()));
   throw e;
  }
 }
 return this->jsonManifest;
}

//@Override
/*public*/ QString HtmlManifest::getValidity()
{
 try
 {
  if (Operations::Setup::isPrintTimetableNameEnabled())
  {
   return String::format(locale, strings->getProperty(this->resourcePrefix + "ValidityWithSchedule"),
//              getDate((new ISO8601DateFormat()).parse(this->getJsonManifest().value(JsonOperations::DATE).toString())),
                getDate(QDateTime::fromString(this->getJsonManifest().value(JsonOperations::DATE).toString(),Qt::ISODate)),
              ((Operations::TrainScheduleManager*)InstanceManager::getDefault("TrainScheduleManager"))->getScheduleById(train->getId())->toString());
  }
  else
  {
   return String::format(locale, strings->getProperty(this->resourcePrefix + "Validity"), getDate(QDateTime::fromString(this->getJsonManifest().value(JsonOperations::DATE).toString(), Qt::ISODate)));
  }
 }
 catch (NullPointerException ex)
 {
  log->warn(tr("Manifest for train %1 (id %2) does not have any validity.").arg(this->train->getIconName()).arg(this->train->getId()));
 }
 catch (ParseException ex)
 {
  log->error("Date of JSON manifest could not be parsed as a Date.");
 }
 catch (IOException ex)
 {
  log->error("JSON manifest could not be read.");
 }
 return "";
}

