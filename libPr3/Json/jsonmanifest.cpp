#include "jsonmanifest.h"
#include "loggerfactory.h"
#include "jsonutil.h"
#include "trainmanagerxml.h"
#include "json.h"
#include "train.h"
#include "jsonoperations.h"
#include "setup.h"
#include "trainmanagerxml.h"
#include "../operations/engine.h"
#include "enginemanager.h"
#include "car.h"
#include "carmanager.h"
#include "../operations/route.h"
#include "routelocation.h"
#include "track.h"
#include "fileutil.h"
#include "stringescapeutils.h"
#include "instancemanager.h"
using namespace Operations;

//JsonManifest::JsonManifest(QObject* parent) : TrainCommon(parent)
//{
// locale = QLocale();
// mapper = ObjectMapper();
// train = NULL;
//}

/**
 * A minimal manifest in  JSON::
 *
 * This manifest is intended to be read by machines for building manifests in
 * other, human-readable outputs. This manifest is retained at build time so
 * that manifests can be endlessly recreated in other formats, even if the
 * operations database state has changed. It is expected that the parsers for
 * this manifest will be capable of querying operations for more specific
 * information while transforming this manifest into other formats.
 *
 * @author Randall Wood
 * @author Daniel Boudreau 1/26/2015 Load all cars including utility cars into
 * the JSON file, and tidied up the code a bit.
 *
 */
///*public*/ class JsonManifest extends TrainCommon {


/*private*/ /*final*/ /*static*/ Logger* JsonManifest::log = LoggerFactory::getLogger("JsonManifest");

/*public*/ JsonManifest::JsonManifest(Train* train, QObject* parent) : TrainCommon(parent)
{
 locale = QLocale();
 mapper = ObjectMapper();

 this->train = train;
 //this->mapper.enable(SerializationFeature.INDENT_OUTPUT);
}

/*public*/ File* JsonManifest::getFile()
{
 QString trainName = this->train->getName();
 return ((TrainManagerXml*)InstanceManager::getDefault("TrainManagerXml"))->getManifestFile(trainName, JSON::_JSON);
}

/*public*/ void JsonManifest::build() /*throw (IOException)*/
{
 QJsonObject root = QJsonObject();//this->mapper.createQJsonObject();
 if (this->train->getRailroadName() != (Train::NONE)) {
     root.insert( JSON::RAILROAD, QString(QUrl(this->train->getRailroadName()).toEncoded()));
 } else {
     root.insert( JSON::RAILROAD, QString(QUrl(Setup::getRailroadName()).toEncoded()));
 }
 root.insert( JSON::NAME, QString(QUrl(this->train->getName()).toEncoded()));
 root.insert( JSON::DESCRIPTION, QString(QUrl(this->train->getDescription()).toEncoded()));
 root.insert(JSON::LOCATIONS, this->getLocations());
 if (this->train->getManifestLogoURL() != (Train::NONE))
 {
  // The operationsServlet will need to change this to a usable URL
  root.insert( JSON::IMAGE, this->train->getManifestLogoURL());
 }
 root.insert(JSON::DATE, TrainCommon::getISO8601Date(true)); // Validity
#if 0 // TODO
 this->mapper.writeValue(TrainManagerXml::instance()->createManifestFile(this->train->getName(),  JSON::_JSON), root);
#else
 File* file = ((TrainManagerXml*)InstanceManager::getDefault("TrainManagerXml"))->createManifestFile(this->train->getName(),  JSON::_JSON);

 QFile f(file->getPath());
 if(f.open(QIODevice::WriteOnly))
 {
  QTextStream stream(&f);
  stream << QJsonDocument(root).toJson();
  f.close();
 }
 else throw new IOException("error writing file:" + file->getPath());
#endif
}

/*public*/ QJsonArray JsonManifest::getLocations()
{
 // get engine and car lists
 QList<Engine*>* engineList = engineManager->getByTrainBlockingList(train);
 QList<Car*>* carList = carManager->getByTrainDestinationList(train);
 QJsonArray locations = QJsonArray();//this->mapper.createArrayNode();
 QList<RouteLocation*>* route = train->getRoute()->getLocationsBySequenceList();
 for (RouteLocation* routeLocation : *route)
 {
  QString locationName = splitString(routeLocation->getName());
  QJsonObject jsonLocation = QJsonObject();//this->mapper.createQJsonObject();
  QJsonObject jsonCars = QJsonObject();//this->mapper.createQJsonObject();
  jsonLocation.insert(JSON::NAME, QString(QUrl(locationName).toEncoded()));
  jsonLocation.insert(JSON::ID, routeLocation->getId());
  if (routeLocation != train->getRoute()->getDepartsRouteLocation()) {
      jsonLocation.insert( JSON::ARRIVAL_TIME, train->getExpectedArrivalTime(routeLocation));
  }
  if (routeLocation == train->getRoute()->getDepartsRouteLocation()) {
      jsonLocation.insert( JSON::DEPARTURE_TIME, train->getDepartureTime());
  } else if (routeLocation->getDepartureTime() != (RouteLocation::NONE)) {
      jsonLocation.insert(JSON::DEPARTURE_TIME, routeLocation->getDepartureTime());
  } else {
      jsonLocation.insert(JSON::EXPECTED_DEPARTURE, train->getExpectedDepartureTime(routeLocation));
  }
  // add location comment and id
  QJsonObject locationNode = QJsonObject();//this->mapper.createQJsonObject();
  locationNode.insert( JSON::COMMENT, StringEscapeUtils::escapeHtml4(routeLocation->getLocation()->getComment()));
  locationNode.insert( JSON::ID, routeLocation->getLocation()->getId());
  jsonLocation.insert(JSON::LOCATION, locationNode);
  jsonLocation.insert( JSON::COMMENT, StringEscapeUtils::escapeHtml4(routeLocation->getComment()));
  // engine change or helper service?
  if (train->getSecondLegOptions() != Train::NO_CABOOSE_OR_FRED)
  {
   QJsonArray options = QJsonArray();//this->mapper.createArrayNode();
   if (routeLocation == train->getSecondLegStartLocation())
   {
    if ((train->getSecondLegOptions() & Train::HELPER_ENGINES) == Train::HELPER_ENGINES) {
        options.append(JSON::ADD_HELPERS);
    } else if ((train->getSecondLegOptions() & Train::REMOVE_CABOOSE) == Train::REMOVE_CABOOSE
            || (train->getSecondLegOptions() & Train::ADD_CABOOSE) == Train::ADD_CABOOSE) {
        options.append( JSON::CHANGE_CABOOSE);
    } else if ((train->getSecondLegOptions() & Train::CHANGE_ENGINES) == Train::CHANGE_ENGINES) {
        options.append( JSON::CHANGE_ENGINES);
    }
   }
   if (routeLocation == train->getSecondLegEndLocation()) {
       options.append( JSON::REMOVE_HELPERS);
   }
   jsonLocation.insert(JSON::OPTIONS, options);
  }
  if (train->getThirdLegOptions() != Train::NO_CABOOSE_OR_FRED)
  {
   QJsonArray options = QJsonArray();//this->mapper.createArrayNode();
   if (routeLocation == train->getThirdLegStartLocation())
   {
    if ((train->getThirdLegOptions() & Train::HELPER_ENGINES) == Train::HELPER_ENGINES) {
        options.append( JSON::ADD_HELPERS);
    } else if ((train->getThirdLegOptions() & Train::REMOVE_CABOOSE) == Train::REMOVE_CABOOSE
            || (train->getThirdLegOptions() & Train::ADD_CABOOSE) == Train::ADD_CABOOSE) {
        options.append( JSON::CHANGE_CABOOSE);
    } else if ((train->getThirdLegOptions() & Train::CHANGE_ENGINES) == Train::CHANGE_ENGINES) {
        options.append( JSON::CHANGE_ENGINES);
    }
   }
   if (routeLocation == train->getThirdLegEndLocation()) {
       options.append( JSON::ADD_HELPERS);
   }
   jsonLocation.insert(JSON::OPTIONS, options);
  }

  QJsonObject engines = QJsonObject();//this->mapper.createQJsonObject();
  engines.insert( JSON::ADD, pickupEngines(engineList, routeLocation));
  engines.insert( JSON::REMOVE, dropEngines(engineList, routeLocation));
  jsonLocation.insert( JSON::ENGINES, engines);

  // block cars by destination
  QJsonArray pickups = QJsonArray();//this->mapper.createArrayNode();
  for (RouteLocation* destination : *route)
  {
   for (Car* car : *carList)
   {
    if (car->getRouteLocation() == routeLocation && car->getRouteDestination() == destination) {
        pickups.append(JsonUtil::getCar(car));
    }
   }
  }
  jsonCars.insert( JSON::ADD, pickups);
  // car set outs
  QJsonArray setouts = QJsonArray();//this->mapper.createArrayNode();
  for (Car* car : *carList)
  {
   if (car->getRouteDestination() == routeLocation) {
       setouts.append(JsonUtil::getCar(car));
   }
  }
  jsonCars.insert( JSON::REMOVE, setouts);

  if (routeLocation != train->getRoute()->getTerminatesRouteLocation())
  {
   jsonLocation.insert(JSON::TRACK, this->getTrackComments(routeLocation, carList));
   jsonLocation.insert( JSON::DIRECTION, routeLocation->getTrainDirection());
   QJsonObject length = QJsonObject();//this->mapper.createQJsonObject();
   length.insert( JSON::LENGTH, train->getTrainLength(routeLocation));
   length.insert( JSON::UNIT, Setup::getLengthUnit());
   jsonLocation.insert( JSON::LENGTH, length);
   jsonLocation.insert(JSON::WEIGHT, train->getTrainWeight(routeLocation));
   int cars = train->getNumberCarsInTrain(routeLocation);
   int emptyCars = train->getNumberEmptyCarsInTrain(routeLocation);
   jsonCars.insert( JSON::TOTAL, cars);
   jsonCars.insert( JSON::LOADS, cars - emptyCars);
   jsonCars.insert( JSON::EMPTIES, emptyCars);
  }
  else
  {
   log->debug(tr("Train terminates in %1").arg(locationName));
   jsonLocation.insert("TrainTerminatesIn", StringEscapeUtils::escapeHtml4(locationName));
  }
  jsonLocation.insert(JSON::CARS, jsonCars);
  locations.append(jsonLocation);
 }
 return locations;
}

/*protected*/ QJsonArray JsonManifest::dropEngines(QList<Engine*>* engines, RouteLocation* routeLocation)
{
 QJsonArray node = QJsonArray();//this->mapper.createArrayNode();
 for (Engine* engine : *engines)
 {
  if (engine->getRouteDestination() != NULL && engine->getRouteDestination() == (routeLocation)) {
      node.append(JsonUtil::getEngine(engine));
  }
 }
 return node;
}

/*protected*/ QJsonArray JsonManifest::pickupEngines(QList<Engine*>* engines, RouteLocation* routeLocation)
{
 QJsonArray node = QJsonArray();//this->mapper.createArrayNode();
 for (Engine* engine : *engines) {
     if (engine->getRouteLocation() != NULL && engine->getRouteLocation() == (routeLocation)) {
         node.append(JsonUtil::getEngine(engine));
     }
 }
 return node;
}

// TODO: migrate comments into actual setout/pickup track location spaces
/*private*/ QJsonObject JsonManifest::getTrackComments(RouteLocation* routeLocation, QList<Car*>* cars)
{
 QJsonObject comments = QJsonObject();//this->mapper.createQJsonObject();
 if (routeLocation->getLocation() != NULL)
 {
  QList<Track*> tracks = routeLocation->getLocation()->getTracksByNameList(NULL);
  for (Track* track : tracks)
  {
   QJsonObject jsonTrack = QJsonObject();//this->mapper.createQJsonObject();
   // any pick ups or set outs to this track?
   bool pickup = false;
   bool setout = false;
   for (Car* car : *cars)
   {
    if (car->getRouteLocation() == routeLocation && car->getTrack() != NULL && car->getTrack() == track) {
        pickup = true;
    }
    if (car->getRouteDestination() == routeLocation && car->getDestinationTrack() != NULL
            && car->getDestinationTrack() == track) {
        setout = true;
    }
   }
   if (pickup) {
       jsonTrack.insert( JSON::ADD, StringEscapeUtils::escapeHtml4(track->getCommentPickup()));
   }
   if (setout) {
       jsonTrack.insert( JSON::REMOVE, StringEscapeUtils::escapeHtml4(track->getCommentSetout()));
   }
   if (pickup && setout) {
       jsonTrack.insert( JSON::ADD_AND_REMOVE, StringEscapeUtils::escapeHtml4(track->getCommentBoth()));
   }
   if (pickup || setout) {
       jsonTrack.insert( JSON::COMMENT, StringEscapeUtils::escapeHtml4(track->getComment()));
       comments.insert(track->getId(), jsonTrack);
   }
  }
 }
 return comments;
}

