#include "traincsvmanifest.h"
#include "loggerfactory.h"
#include "trainmanagerxml.h"
#include "train.h"
#include "printwriter.h"
#include "file.h"
#include "enginemanager.h"
#include "carmanager.h"
#include "locationmanager.h"
#include "setup.h"
#include "fileutil.h"
#include "route.h"
#include "routelocation.h"
#include "location.h"
#include "carload.h"
#include "engine.h"
#include "car.h"
#include "track.h"
#include "carloads.h"
#include "instancemanager.h"

using namespace Operations;
TrainCsvManifest::TrainCsvManifest()
{
 engineManager = ((EngineManager*)InstanceManager::getDefault("Operations::EngineManager"));
 carManager = ((CarManager*)InstanceManager::getDefault("Operations::CarManager"));
 locationManager = ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"));

}
/**
 * Builds a train's manifest using Comma Separated Values (csv).
 *
 * @author Daniel Boudreau Copyright (C) 2011, 2015
 *
 */
///*public*/ class TrainCsvManifest extends TrainCsvCommon {


/*private*/ /*final*/ /*static*/ Logger* TrainCsvManifest::log = LoggerFactory::getLogger("TrainCsvManifest");

//@SuppressFBWarnings(value = "BC_UNCONFIRMED_CAST_OF_RETURN_VALUE", justification = "CarManager only provides Car Objects")
/*public*/ TrainCsvManifest::TrainCsvManifest(Train* train)
{
 // create comma separated value manifest file
 File* file = ((TrainManagerXml*)InstanceManager::getDefault("TrainManagerXml"))->createTrainCsvManifestFile(train->getName());

 PrintWriter* fileOut;

 try {
     //fileOut = new PrintWriter(new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file), "UTF-8")),// NOI18N
//            true); // NOI18N
  QFile f(file->getPath());
  if(!f.open(QIODevice::WriteOnly)) throw new IOException("Error opening file");
  QTextStream os(&f);
  os.setCodec("UTF-8");
  fileOut = new PrintWriter(&os);
 } catch (IOException* e) {
     log->error(tr("Can not open CSV manifest file: %1").arg(file->getName()));
     return;
 }

 // build header
 addLine(fileOut, HEADER);
 addLine(fileOut, RN + ESC + Setup::getRailroadName() + ESC);
 addLine(fileOut, TN + train->getName());
 addLine(fileOut, TM + ESC + train->getDescription() + ESC);
 addLine(fileOut, PRNTR + ESC
+ locationManager->getLocationByName(train->getTrainDepartsName())->getDefaultPrinterName() + ESC);

 // add logo
 QString logoURL = FileUtil::getExternalFilename(Setup::getManifestLogoURL());
 if (train->getManifestLogoURL() != (Train::NONE)) {
     logoURL = FileUtil::getExternalFilename( train->getManifestLogoURL());
 }
 if (logoURL != ("")) {
     addLine(fileOut, LOGO + logoURL);
 }

 addLine(fileOut, VT + getDate(true));
 // train comment can have multiple lines
 if ( train->getComment() != (Train::NONE)) {
     QStringList comments =  train->getComment().split(NEW_LINE); // NOI18N
     for (QString comment : comments) {
         addLine(fileOut, TC + ESC + comment + ESC);
     }
 }
 if (Setup::isPrintRouteCommentsEnabled()) {
     addLine(fileOut, RC + ESC +  train->getRoute()->getComment() + ESC);
 }

 // get engine and car lists
 QList<Engine*>* engineList = engineManager->getByTrainBlockingList(train);
 QList<Car*>* carList = carManager->getByTrainDestinationList(train);

 int cars = 0;
 int emptyCars = 0;
 bool newWork = false;
 QString previousRouteLocationName = NULL;
 QList<RouteLocation*>* routeList =  train->getRoute()->getLocationsBySequenceList();

 for (RouteLocation* rl : *routeList)
 {
  // print info only if new location
  QString routeLocationName = splitString(rl->getName());
  QString locationName = routeLocationName;
  if (locationName.contains(DEL))
  {
   log->debug("location name has delimiter: " + locationName);
   locationName = ESC + routeLocationName + ESC;
  }
  if (routeLocationName != (previousRouteLocationName))
  {
   addLine(fileOut, LN + locationName);
   if (rl !=  train->getRoute()->getDepartsRouteLocation()) {
       addLine(fileOut, AT +  train->getExpectedArrivalTime(rl));
   }
   if (rl ==  train->getRoute()->getDepartsRouteLocation()) {
       addLine(fileOut, DT +  train->getDepartureTime());
   } else if (rl->getDepartureTime() != (RouteLocation::NONE)) {
       addLine(fileOut, DTR + rl->getDepartureTime());
   } else {
       addLine(fileOut, EDT +  train->getExpectedDepartureTime(rl));
   }

   Location* location = rl->getLocation();
   // add location comment
   if (Setup::isPrintLocationCommentsEnabled() && location->getComment() != (Location::NONE))
   {
    // location comment can have multiple lines
    QStringList comments = location->getComment().split(NEW_LINE); // NOI18N
    for (QString comment : comments) {
        addLine(fileOut, LC + ESC + comment + ESC);
    }
   }
   if (Setup::isTruncateManifestEnabled() && location->isSwitchListEnabled()) {
       addLine(fileOut, TRUN);
   }
  }
  // add route comment
  if (rl->getComment() != (RouteLocation::NONE)) {
      addLine(fileOut, RLC + ESC + rl->getComment() + ESC);
  }

  printTrackComments(fileOut, rl, carList);

  // engine change or helper service?
  checkForEngineOrCabooseChange(fileOut, train, rl);

  for (Engine* engine : *engineList) {
      if (engine->getRouteLocation() == rl) {
          fileOutCsvEngine(fileOut, engine, PL);
      }
  }
  for (Engine* engine : *engineList) {
      if (engine->getRouteDestination() == rl) {
          fileOutCsvEngine(fileOut, engine, SL);
      }
  }

  // block pick up cars by destination
  bool found = false; // begin blocking at rl
  for (RouteLocation* rld : *routeList)
  {
   if (rld != rl && !found) {
       continue;
   }
   found = true;
   for (Car* car : *carList)
   {
    if (car->getRouteLocation() == rl && car->getRouteDestination() == rld)
    {
     cars++;
     newWork = true;
     if (car->getLoadType() == (CarLoad::LOAD_TYPE_EMPTY)) {
         emptyCars++;
     }
     int count = 0;
     if (car->isUtility()) {
         count = countPickupUtilityCars(carList, car, IS_MANIFEST);
         if (count == 0) {
             continue; // already done this set of utility cars
         }
     }
     fileOutCsvCar(fileOut, car, PC, count);
    }
   }
  }
  // car set outs
  for (Car* car : *carList)
  {
   if (car->getRouteDestination() == rl)
   {
    cars--;
    newWork = true;
    if (((CarLoads*)InstanceManager::getDefault("Operations::CarLoads"))->getLoadType(car->getTypeName(), car->getLoadName()) == (
            CarLoad::LOAD_TYPE_EMPTY)) {
        emptyCars--;
    }
    int count = 0;
    if (car->isUtility()) {
        count = countSetoutUtilityCars(carList, car, false, IS_MANIFEST);
        if (count == 0) {
            continue; // already done this set of utility cars
        }
    }
    fileOutCsvCar(fileOut, car, SC, count);
   }
  }
  // car holds
  QList<RollingStock*>* rsByLocation = ((CarManager*)InstanceManager::getDefault("Operations::CarManager"))->getByLocationList();
  QList<Car*> cList = QList<Car*>();
  for (RollingStock* rs : *rsByLocation) {
      if (rs->getLocation() == rl->getLocation() && rs->getRouteLocation() == NULL && rs->getTrack() != NULL) {
          cList.append((Car*) rs);
      }
  }
  clearUtilityCarTypes(); // list utility cars by quantity
  for (Car* car : cList)
  {
   // list cars on tracks that only this train can service
   if (!car->getTrack()->getLocation()->isStaging()
           && car->getTrack()->acceptsPickupTrain(train) && car->getTrack()->getPickupIds().length() == 1
           && car->getTrack()->getPickupOption() == (Track::TRAINS)) {
       int count = 0;
       if (car->isUtility()) {
           count = countPickupUtilityCars(&cList, car, !IS_MANIFEST);
           if (count == 0) {
               continue; // already done this set of utility cars
           }
       }
       fileOutCsvCar(fileOut, car, HOLD, count);
   }
  }
  if (rl !=  train->getRoute()->getTerminatesRouteLocation())
  {
   // Is the next location the same as the previous?
   RouteLocation* rlNext =  train->getRoute()->getNextRouteLocation(rl);
   QString nextRouteLocationName = splitString(rlNext->getName());
   if (routeLocationName != (nextRouteLocationName))
   {
    if (newWork) {
        addLine(fileOut, TD + locationName + DEL + rl->getTrainDirectionString());
        addLine(fileOut, TL +  train->getTrainLength(rl) + DEL + emptyCars + DEL + cars);
        addLine(fileOut, TW +  train->getTrainWeight(rl));
        newWork = false;
    } else {
        addLine(fileOut, NW);
    }
   }
  }
  else {
      addLine(fileOut, TT + locationName);
  }
  previousRouteLocationName = routeLocationName;
 }
 // Are there any cars that need to be found?
 listCarsLocationUnknown(fileOut);

 fileOut->flush();
 fileOut->close();

}
