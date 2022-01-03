#include "trainmanifest.h"
#include "file.h"
#include "trainmanagerxml.h"
#include "train.h"
#include "printwriter.h"
#include "logger.h"
#include "setup.h"
#include "trainschedule.h"
#include "trainschedulemanager.h"
#include "trainmanager.h"
#include "engine.h"
#include "enginemanager.h"
#include "car.h"
#include "carmanager.h"
#include "route.h"
#include "trainmanifesttext.h"
#include "routelocation.h"
#include "location.h"
#include "instancemanager.h"

namespace Operations
{
/**
 * Builds a train's manifest.
 *
 * @author Daniel Boudreau Copyright (C) 2011, 2012, 2013, 2015
 * @version $Revision: 1 $
 */
///*public*/ class TrainManifest extends TrainCommon {

 //private static final Logger log = LoggerFactory.getLogger(TrainManifest.class);


 /*public*/ TrainManifest::TrainManifest(Train* train, QObject* parent) : TrainCommon(parent)
 {
  log = new Logger("TrainManifest");
  messageFormatText = "";
  // create manifest file
  File* file = ((TrainManagerXml*)InstanceManager::getDefault("TrainManagerXml"))->createTrainManifestFile(train->getName());

  PrintWriter* fileOut;

  //try {
  QFile* qFile = new QFile(file->getAbsolutePath());
  if(!qFile->open(QIODevice::WriteOnly))
  {
   log->error("Can not open train manifest file: " + file->getName());
     return;
  }
  log->info(tr("manifest for train %1 will be written to %2").arg(train->getName(), file->getPath()));
  QTextStream* stream = new QTextStream(qFile);
      //fileOut = new PrintWriter(new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file), "UTF-8")), // NOI18N
//      true);
  fileOut = new PrintWriter(stream, true);
//  } catch (IOException* e) {
//      log->error("Can not open train manifest file: " + file.getName());
//      return;
//  }
  //try {
      // build header
  if (train->getRailroadName()!=(Train::NONE)) {
      newLine(fileOut, train->getRailroadName());
  } else {
      newLine(fileOut, Setup::getRailroadName());
  }
  newLine(fileOut); // empty line
  newLine(fileOut, QString(messageFormatText = TrainManifestText::getStringManifestForTrain()).arg(train->getName()).arg(train->getDescription()));

  QString valid = QString(messageFormatText = TrainManifestText::getStringValid()).arg(getDate(true));

  if (Setup::isPrintTimetableNameEnabled())
  {
   TrainSchedule* sch = ((Operations::TrainScheduleManager*)InstanceManager::getDefault("Operations::TrainScheduleManager"))->getScheduleById(
           ((TrainManager*)InstanceManager::getDefault("OperationsTrainManager"))->getTrainScheduleActiveId());
   if (sch != NULL)
   {
    valid = valid + " (" + sch->getName() + ")";
   }
  }
  if (Setup::isPrintValidEnabled())
  {
   newLine(fileOut, valid);
  }

  if (train->getComment()!=(Train::NONE))
  {
   newLine(fileOut, train->getComment());
  }

  QList<Engine*>* engineList = engineManager->getByTrainBlockingList(train);

  if (Setup::isPrintRouteCommentsEnabled() && train->getRoute()->getComment()!=(Route::NONE))
  {
   newLine(fileOut, train->getRoute()->getComment());
  }

  QList<Car*>* carList = carManager->getByTrainDestinationList(train);
  log->debug(tr("Train has %1 cars assigned to it").arg(carList->size()));

  bool hasWork = false;
  bool hadWork = false;
  bool noWork = false;
  QString previousRouteLocationName = NULL;
  QList<RouteLocation*>* routeList = train->getRoute()->getLocationsBySequenceList();

  foreach (RouteLocation* rl, *routeList)
  {
   bool printHeader = false;
   hasWork = isThereWorkAtLocation(carList, engineList, rl);
   // print info only if new location
   QString routeLocationName = splitString(rl->getName());
   if (routeLocationName!=(previousRouteLocationName) || (hasWork && !hadWork))
   {
    if (hasWork)
    {
     newLine(fileOut);
     hadWork = true;
     noWork = false;
     printHeader = true;
     QString expectedArrivalTime = train->getExpectedArrivalTime(rl);
     QString workAt = QString(messageFormatText = TrainManifestText
             ::getStringScheduledWork()).arg(routeLocationName).arg(train->getName(),
             train->getDescription());
     if (!train->isShowArrivalAndDepartureTimesEnabled())
     {
      newLine(fileOut, workAt);
     }
     else if (rl == train->getRoute()->getDepartsRouteLocation())
     {
      newLine(fileOut, QString(messageFormatText = TrainManifestText
              ::getStringWorkDepartureTime()).arg(routeLocationName).arg(
              train->getFormatedDepartureTime()).arg(train->getName()).arg(train->getDescription()));
     }
     else if (rl->getDepartureTime()!=(RouteLocation::NONE))
     {
       newLine(fileOut, QString(messageFormatText = TrainManifestText
               ::getStringWorkDepartureTime()).arg(routeLocationName).arg(
               rl->getFormatedDepartureTime()).arg(train->getName()).arg(train->getDescription()));
     }
     else if (Setup::isUseDepartureTimeEnabled()
             && rl != train->getRoute()->getTerminatesRouteLocation())
     {
      newLine(fileOut, QString(messageFormatText = TrainManifestText
              ::getStringWorkDepartureTime()).arg(routeLocationName).arg(
              train->getExpectedDepartureTime(rl)).arg(train->getName()).arg(train->getDescription()));
     }
     else if (expectedArrivalTime!=(Train::ALREADY_SERVICED))
     {
      newLine(fileOut, QString(messageFormatText = TrainManifestText
              ::getStringWorkArrivalTime()).arg(routeLocationName).arg(expectedArrivalTime).arg(
              train->getName()).arg(train->getDescription()));
     }
     else
     {
      newLine(fileOut, workAt);
     }
     // add route location comment
     if (rl->getComment().trimmed()!=(RouteLocation::NONE))
     {
      newLine(fileOut, rl->getComment());
     }

     // add location comment
     if (Setup::isPrintLocationCommentsEnabled()
             && rl->getLocation()->getComment()!=(Location::NONE))
     {
      newLine(fileOut, rl->getLocation()->getComment());
     }
    }
   }
   // remember location name
   previousRouteLocationName = routeLocationName;

   // add track comments
   printTrackComments(fileOut, rl, carList, IS_MANIFEST);
#if 1
   // engine change or helper service?
   if (train->getSecondLegOptions() != Train::NO_CABOOSE_OR_FRED) {
       if (rl == train->getSecondLegStartLocation()) {
           printChange(fileOut, rl, train, train->getSecondLegOptions());
       }
       if (rl == train->getSecondLegEndLocation() && train->getSecondLegOptions() == Train::HELPER_ENGINES) {
           newLine(fileOut, QString(messageFormatText = TrainManifestText
                   ::getStringRemoveHelpers()).arg(splitString(rl->getName())).arg(train->getName(),
                   train->getDescription()));
       }
   }
   if (train->getThirdLegOptions() != Train::NO_CABOOSE_OR_FRED) {
       if (rl == train->getThirdLegStartLocation()) {
           printChange(fileOut, rl, train, train->getThirdLegOptions());
       }
       if (rl == train->getThirdLegEndLocation() && train->getThirdLegOptions() == Train::HELPER_ENGINES) {
           newLine(fileOut, QString(messageFormatText = TrainManifestText
                   ::getStringRemoveHelpers()).arg(splitString(rl->getName())).arg(train->getName(),
                   train->getDescription()));
       }
   }

   if (Setup::getManifestFormat()==(Setup::STANDARD_FORMAT)) {
       pickupEngines(fileOut, engineList, rl, IS_MANIFEST);
       dropEngines(fileOut, engineList, rl, IS_MANIFEST);
       blockCarsByTrack(fileOut, train, carList, routeList, rl, printHeader, IS_MANIFEST);
   } else if (Setup::getManifestFormat()==(Setup::TWO_COLUMN_FORMAT)) {
       blockLocosTwoColumn(fileOut, engineList, rl, IS_MANIFEST);
       blockCarsByTrackTwoColumn(fileOut, train, carList, routeList, rl, printHeader, IS_MANIFEST);
   } else {
       blockLocosTwoColumn(fileOut, engineList, rl, IS_MANIFEST);
       blockCarsByTrackNameTwoColumn(fileOut, train, carList, routeList, rl, printHeader, IS_MANIFEST);
   }

   if (rl != train->getRoute()->getTerminatesRouteLocation()) {
       // Is the next location the same as the current?
       RouteLocation* rlNext = train->getRoute()->getNextRouteLocation(rl);
       if (routeLocationName==(splitString(rlNext->getName()))) {
           continue;
       }
       if (hadWork) {
           hadWork = false;
           if (Setup::isPrintHeadersEnabled()
                   || Setup::getManifestFormat()!=(Setup::STANDARD_FORMAT)) {
               printHorizontalLine(fileOut, IS_MANIFEST);
           }
           QString trainDeparts = "";
           if (Setup::isPrintLoadsAndEmptiesEnabled()) {
               // Message format: Train departs Boston Westbound with 4 loads, 8 empties, 450 feet, 3000 tons
               trainDeparts = QString(messageFormatText = TrainManifestText
                       ::getStringTrainDepartsLoads()).arg(routeLocationName).arg(
                       rl->getTrainDirectionString()).arg(cars - emptyCars).arg(emptyCars).arg(
                       train->getTrainLength(rl)).arg(Setup::getLengthUnit().toLower()).arg(
                       train->getTrainWeight(rl)).arg(train->getTrainTerminatesName()).arg(train->getName());
           } else {
               // Message format: Train departs Boston Westbound with 12 cars, 450 feet, 3000 tons
               trainDeparts = QString(messageFormatText = TrainManifestText
                       ::getStringTrainDepartsCars()).arg(routeLocationName).arg(
                       rl->getTrainDirectionString()).arg(cars).arg(train->getTrainLength(rl)).arg(
                       Setup::getLengthUnit().toLower()).arg(train->getTrainWeight(rl)).arg(
                       train->getTrainTerminatesName()).arg(train->getName());
           }
           newLine(fileOut, trainDeparts);
       } else {
           // no work at this location
           if (!noWork)
               newLine(fileOut);
           noWork = true;
           QString s = QString(messageFormatText = TrainManifestText
                   ::getStringNoScheduledWork()).arg(routeLocationName, train->getName()),arg(
                   train->getDescription());
           // if a route comment, then only use location name and route comment, useful for passenger
           // trains
           if (rl->getComment()!=(RouteLocation::NONE)) {
               s = routeLocationName;
               if (rl->getComment().trimmed().length() > 0) {
                   s = QString(messageFormatText = TrainManifestText
                           ::getStringNoScheduledWorkWithRouteComment()).arg(
                           routeLocationName).arg(rl->getComment()).arg(train->getName()).arg(
                                   train->getDescription());
               }
           }
           if (train->isShowArrivalAndDepartureTimesEnabled()) {
               if (rl == train->getRoute()->getDepartsRouteLocation()) {
                   s += QString(messageFormatText = TrainManifestText
                           ::getStringDepartTime()).arg(train->getDepartureTime());
               } else if (rl->getDepartureTime()!=(RouteLocation::NONE)) {
                   s += QString(messageFormatText = TrainManifestText
                           ::getStringDepartTime()).arg(rl->getFormatedDepartureTime());
               } else if (Setup::isUseDepartureTimeEnabled()
                       && rl->getComment()!=(RouteLocation::NONE)) {
                   s += QString(messageFormatText = TrainManifestText::getStringDepartTime()).arg(
                                   train->getExpectedDepartureTime(rl));
               }
           }
           newLine(fileOut, s);

           // add location comment
           if (Setup::isPrintLocationCommentsEnabled()
                   && rl->getLocation()->getComment()!=(Location::NONE)) {
               newLine(fileOut, rl->getLocation()->getComment());
           }
       }
   } else {
       // last location in the train's route, print train terminates message
       if (Setup::isPrintHeadersEnabled() || Setup::getManifestFormat()!=(Setup::STANDARD_FORMAT)) {
           printHorizontalLine(fileOut, IS_MANIFEST);
       } else if (!noWork) {
           newLine(fileOut);
       }
       newLine(fileOut, QString(messageFormatText = TrainManifestText
               ::getStringTrainTerminates()).arg(routeLocationName, train->getName()).arg(
               train->getDescription()));
   }
#endif

  }
  // Are there any cars that need to be found?
  addCarsLocationUnknown(fileOut, IS_MANIFEST);
//  } catch (IllegalArgumentException e) {
//      newLine(fileOut, tr(Bundle.getMessage("ErrorIllegalArgument")).arg(
//              Bundle.getMessage("TitleManifestText"), e->getLocalizedMessage()}));
//      newLine(fileOut, messageFormatText);
//      e.printStackTrace();
//  }
  fileOut->flush();
  fileOut->close();

  train->setModified(false);
}

/*private*/ void TrainManifest::printChange(PrintWriter* fileOut, RouteLocation* rl, Train* train, int legOptions)
      //throws IllegalArgumentException
{
  if ((legOptions & Train::HELPER_ENGINES) == Train::HELPER_ENGINES) {
      newLine(fileOut, QString(messageFormatText = TrainManifestText::getStringAddHelpers()).arg(
              splitString(rl->getName())).arg(train->getName()).arg(train->getDescription()));
  } else if ((legOptions & Train::CHANGE_ENGINES) == Train::CHANGE_ENGINES
          &&
          ((legOptions & Train::REMOVE_CABOOSE) == Train::REMOVE_CABOOSE || (legOptions & Train::ADD_CABOOSE) == Train::ADD_CABOOSE)) {
      newLine(fileOut, QString(
              messageFormatText = TrainManifestText::getStringLocoAndCabooseChange()).arg(
                      splitString(rl->getName())).arg(train->getName()).arg(train->getDescription()));
  } else if ((legOptions & Train::CHANGE_ENGINES) == Train::CHANGE_ENGINES) {
      newLine(fileOut, QString(messageFormatText = TrainManifestText::getStringLocoChange()).arg(
              splitString(rl->getName())).arg(train->getName()).arg(train->getDescription()));
  } else if ((legOptions & Train::REMOVE_CABOOSE) == Train::REMOVE_CABOOSE
          || (legOptions & Train::ADD_CABOOSE) == Train::ADD_CABOOSE) {
      newLine(fileOut, QString(messageFormatText = TrainManifestText::getStringCabooseChange()).arg(
              splitString(rl->getName())).arg(train->getName()).arg(train->getDescription()));
  }
 }

 /*private*/ void TrainManifest::newLine(PrintWriter* file, QString string)
 {
        TrainCommon::newLine(file, string, IS_MANIFEST);
 }
 /*private*/ void TrainManifest::newLine(PrintWriter* file)
 {
  TrainCommon::newLine(file);
 }
}
