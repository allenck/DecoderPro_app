#include "trainswitchlists.h"
#include "trainmanager.h"
#include "location.h"
#include "setup.h"
#include "file.h"
#include "printwriter.h"
#include "trainmanagerxml.h"
#include "trainswitchlisttext.h"
#include "trainprintutilities.h"
#include "fileutil.h"
#include "trainmanifesttext.h"
#include "trainschedule.h"
#include "trainschedulemanager.h"
#include "train.h"
#include "route.h"
#include "enginemanager.h"
#include "car.h"
#include "engine.h"
#include "routelocation.h"
#include "carmanager.h"
#include "locationmanager.h"
#include "track.h"
#include "carroads.h"
#include "carloads.h"
#include "control.h"
#include "carcolors.h"
#include "cartypes.h"
#include "instancemanager.h"

namespace Operations
{
/**
 * Builds a switch list for a location on the railroad
 *
 * @author Daniel Boudreau (C) Copyright 2008, 2011, 2012, 2013, 2015
 * @version $Revision: 21846 $
 *
 */
///*public*/ class TrainSwitchLists extends TrainCommon {

    /*private*/ /*static*/ /*final*/ const char TrainSwitchLists::FORM_FEED = '\f';
    /*private*/ /*static*/ /*final*/ bool TrainSwitchLists::IS_PRINT_HEADER = true;

 TrainSwitchLists::TrainSwitchLists(QObject* parent) : TrainCommon(parent)
 {
  messageFormatText = ""; // the text being formated in case there's an exception
  trainManager = ((TrainManager*)InstanceManager::getDefault("OperationsTrainManager"));
  log = new Logger("TrainSwitchLists");
 }
 /**
  * builds a switch list for a location
  *
  * @param location The Location needing a switch list
  */
 /*public*/ void TrainSwitchLists::buildSwitchList(Location* location) {
     // Append switch list data if not operating in real time
     bool newTrainsOnly = !Setup::isSwitchListRealTime();
     bool append = false;
     bool checkFormFeed = true; // used to determine if FF needed between trains
     if (newTrainsOnly) {
         if (location->getStatus()!=(Location::MODIFIED) && !Setup::isSwitchListAllTrainsEnabled()) {
             return; // nothing to add
         }
         append = location->getSwitchListState() == Location::SW_APPEND;
         if (location->getSwitchListState() != Location::SW_APPEND) {
             location->setSwitchListState(Location::SW_APPEND);
         }
         location->setStatus(Location::UPDATED);
     }

     log->debug(tr("Append: %1 for location (%2)").arg(append).arg(location->getName()));

     // create switch list file
     File* file = ((TrainManagerXml*)InstanceManager::getDefault("TrainManagerXml"))->createSwitchListFile(location->getName());

     PrintWriter* fileOut = NULL;
     //try {
         //fileOut = new PrintWriter(new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file, append),
     //                 "UTF-8")), true); // NOI18N
     QFile* qFile = new QFile(file->getPath());
     if(!qFile->open(QIODevice::ReadWrite))
     {
        log->error(tr("Can not open switchlist file: %1").arg(file->getName()));
        return;
     }

     QTextStream* stream =  new QTextStream(qFile);
//     } catch (IOException* e) {
//         log->error("Can not open switchlist file: {}", file.getName());
//         return;
//     }
      fileOut = new PrintWriter(stream,true);
     //try {
         // build header
         if (!append) {
             newLine(fileOut, Setup::getRailroadName());
             newLine(fileOut);
             newLine(fileOut, QString(messageFormatText = TrainSwitchListText::getStringSwitchListFor().arg(
                     splitString(location->getName()))));
             if (location->getSwitchListComment()!=(Location::NONE)) {
                 newLine(fileOut, location->getSwitchListComment());
             }
         }

         QString valid = QString(messageFormatText = TrainManifestText::getStringValid()).arg(
                 getDate(true));
         if (Setup::isPrintTimetableNameEnabled()) {
             TrainSchedule* sch = ((Operations::TrainScheduleManager*)InstanceManager::getDefault("Operations::TrainScheduleManager"))->getScheduleById(
                     trainManager->getTrainScheduleActiveId());
             if (sch != NULL) {
                 valid = valid + " (" + sch->getName() + ")";
             }
         }

         // get a list of trains sorted by arrival time
         QList<Train*> trains = trainManager->getTrainsArrivingThisLocationList(location);
         foreach (Train* train, trains) {
             if (!train->isBuilt()) {
                 continue; // train wasn't built so skip
             }
             if (newTrainsOnly && train->getSwitchListStatus()==(Train::PRINTED)) {
                 continue; // already printed this train
             }
             Route* route = train->getRoute();
             if (route == NULL) {
                 continue; // no route for this train
             } // determine if train works this location
             bool works = isThereWorkAtLocation(train, location);
             if (!works && !Setup::isSwitchListAllTrainsEnabled()) {
                 log->debug(tr("No work for train (%1) at location (%2)").arg(train->getName()).arg(location->getName()));
                 continue;
             }
             // we're now going to add to the switch list
             if (checkFormFeed) {
                 if (append && Setup::getSwitchListPageFormat()!=(Setup::PAGE_NORMAL)) {
                     fileOut->write(QString(FORM_FEED));
                 }
                 if (Setup::isPrintValidEnabled()) {
                     newLine(fileOut, valid);
                 }
             } else if (Setup::getSwitchListPageFormat()!=(Setup::PAGE_NORMAL)) {
                 fileOut->write(QString(FORM_FEED));
             }
             checkFormFeed = false; // done with FF for this train
             // some cars bools and the number of times this location get's serviced
             pickupCars = false; // when true there was a car pick up
             dropCars = false; // when true there was a car set out
             int stops = 1;
             bool trainDone = false;
             // get engine and car lists
             QList<Engine*>* engineList = engineManager->getByTrainBlockingList(train);
             QList<Car*>* carList = carManager->getByTrainDestinationList(train);
             QList<RouteLocation*>* routeList = route->getLocationsBySequenceList();
             RouteLocation* rlPrevious = NULL;
             // does the train stop once or more at this location?
             foreach (RouteLocation* rl, *routeList) {
                 if (splitString(rl->getName())!=(splitString(location->getName()))) {
                     rlPrevious = rl;
                     continue;
                 }
                 QString expectedArrivalTime = train->getExpectedArrivalTime(rl);
                 if (expectedArrivalTime==(Train::ALREADY_SERVICED)) {
                     trainDone = true;
                 }
                 // first time at this location?
                 if (stops == 1) {
                     newLine(fileOut);
                     newLine(fileOut, QString(messageFormatText = TrainSwitchListText
                             ::getStringScheduledWork().arg(train->getName()).arg(train->getDescription())));
                     if (train->isTrainInRoute()) {
                         if (!trainDone) {
                             newLine(fileOut, QString(messageFormatText = TrainSwitchListText
                                     ::getStringDepartedExpected().arg(
                                     splitString(train->getTrainDepartsName())).arg(expectedArrivalTime,
                                     rl->getTrainDirectionString())));
                         }
                     } else if (!train->isLocalSwitcher()) {
                         if (rl == train->getRoute()->getDepartsRouteLocation()) {
                             newLine(fileOut, QString(messageFormatText = TrainSwitchListText
                                     ::getStringDepartsAt().arg(splitString(train->getTrainDepartsName()),
                                     rl->getTrainDirectionString()).arg(train->getFormatedDepartureTime())));
                         } else {
                             newLine(fileOut, QString(messageFormatText = TrainSwitchListText
                                     ::getStringDepartsAtExpectedArrival().arg(
                                     splitString(train->getTrainDepartsName()), train->getFormatedDepartureTime()).arg(
                                     expectedArrivalTime).arg(rl->getTrainDirectionString())));
                         }
                     }
                 } else {
                     // multiple visits to this location
                     // Print visit number only if previous location wasn't the same
                     if (rlPrevious == NULL || splitString(rl->getName())!=(splitString(rlPrevious->getName()))) {
                         if (Setup::getSwitchListPageFormat()==(Setup::PAGE_PER_VISIT)) {
                             fileOut->write(QString(FORM_FEED));
                         }
                         newLine(fileOut);
                         if (train->isTrainInRoute()) {
                             if (expectedArrivalTime==(Train::ALREADY_SERVICED)) {
                                 newLine(fileOut, QString(messageFormatText = TrainSwitchListText
                                         ::getStringVisitNumberDone()).arg(stops).arg(train->getName()).arg(
                                         train->getDescription()));
                             } else if (rl != train->getRoute()->getTerminatesRouteLocation()) {
                                 newLine(fileOut, QString(messageFormatText = TrainSwitchListText
                                                 ::getStringVisitNumberDeparted()).arg(stops).arg(
                                                 train->getName()).arg(expectedArrivalTime).arg(rl->getTrainDirectionString(),
                                                 train->getDescription()));
                             } else {
                                 newLine(fileOut, QString(messageFormatText = TrainSwitchListText
                                         ::getStringVisitNumberTerminatesDeparted().arg(stops).arg(
                                         train->getName()).arg(expectedArrivalTime).arg(splitString(rl->getName()),
                                         train->getDescription())));
                             }
                         } else {
                             // train hasn't departed
                             if (rl != train->getRoute()->getTerminatesRouteLocation()) {
                                 newLine(fileOut, QString(messageFormatText = TrainSwitchListText::getStringVisitNumber()).arg(
                                                 stops).arg(train->getName()).arg(expectedArrivalTime).arg(
                                                         rl->getTrainDirectionString()).arg(train->getDescription()));
                             } else {
                                 newLine(fileOut, QString(messageFormatText = TrainSwitchListText
                                         ::getStringVisitNumberTerminates()).arg(stops).arg(train->getName()).arg(
                                         expectedArrivalTime).arg(splitString(rl->getName())).arg(train->getDescription()));
                             }
                         }
                     } else {
                         stops--; // don't bump stop count, same location
                         // Does the train reverse direction?
                         if (rl->getTrainDirection() != rlPrevious->getTrainDirection()
                                 && TrainSwitchListText::getStringTrainDirectionChange()!=("")) {
                             newLine(fileOut, QString(messageFormatText = TrainSwitchListText
                                     ::getStringTrainDirectionChange()).arg(train->getName(),
                                     rl->getTrainDirectionString()).arg(train->getDescription(),
                                     train->getTrainTerminatesName()));
                         }
                     }
                 }

                 rlPrevious = rl; // save current location in case there's back to back location with the same name

                 // add route comment
                 if (Setup::isSwitchListRouteLocationCommentEnabled() && rl->getComment().trimmed()!=("")) {
                     newLine(fileOut, rl->getComment());
                 }

                 if (Setup::getManifestFormat()==(Setup::STANDARD_FORMAT)) {
                     pickupEngines(fileOut, engineList, rl, !IS_MANIFEST);
                     dropEngines(fileOut, engineList, rl, !IS_MANIFEST);
                     blockCarsByTrack(fileOut, train, carList, routeList, rl, IS_PRINT_HEADER, !IS_MANIFEST);
                 }
#if 0
                 else if (Setup::getManifestFormat()==(Setup::TWO_COLUMN_FORMAT)) {
                     blockLocosTwoColumn(fileOut, engineList, rl, !IS_MANIFEST);
                     blockCarsByTrackTwoColumn(fileOut, train, carList, routeList, rl, IS_PRINT_HEADER, !IS_MANIFEST);
                 } else {
                     blockLocosTwoColumn(fileOut, engineList, rl, !IS_MANIFEST);
                     blockCarsByTrackNameTwoColumn(fileOut, train, carList, routeList, rl, IS_PRINT_HEADER,
                             !IS_MANIFEST);
                 }
#endif
                 if (Setup::isPrintHeadersEnabled() || Setup::getManifestFormat()!=(Setup::STANDARD_FORMAT)) {
                     printHorizontalLine(fileOut, !IS_MANIFEST);
                 }

                 stops++;

                 if (rl != train->getRoute()->getTerminatesRouteLocation()) {
                     RouteLocation* nextRl = train->getRoute()->getNextRouteLocation(rl);
                     if (splitString(rl->getName())==(splitString(nextRl->getName()))) {
                         continue; // the current location name is the "same" as the next
                     } // print departure text if not a switcher and not the last location in the route
                     if (!train->isLocalSwitcher()) {
                         QString trainDeparts = "";
                         if (Setup::isPrintLoadsAndEmptiesEnabled()) {
                             int emptyCars = train->getNumberEmptyCarsInTrain(rl);
                             // Message format: Train departs Boston Westbound with 4 loads, 8 empties, 450 feet,
                             // 3000 tons
                             trainDeparts = QString(TrainSwitchListText::getStringTrainDepartsLoads()).arg(
                                     TrainCommon::splitString(rl->getName())).arg(
                                             rl->getTrainDirectionString()).arg(
                                             train->getNumberCarsInTrain(rl) - emptyCars, emptyCars).arg(
                                             train->getTrainLength(rl)).arg(Setup::getLengthUnit().toLower()).arg(
                                             train->getTrainWeight(rl)).arg(train->getTrainTerminatesName()).arg(
                                             train->getName());
                         } else {
                             // Message format: Train departs Boston Westbound with 12 cars, 450 feet, 3000 tons
                             trainDeparts = QString(TrainSwitchListText::getStringTrainDepartsCars()).arg(
                                     TrainCommon::splitString(rl->getName())).arg(
                                             rl->getTrainDirectionString()).arg(train->getNumberCarsInTrain(rl)).arg(
                                             train->getTrainLength(rl)).arg(Setup::getLengthUnit().toLower()).arg(
                                             train->getTrainWeight(rl)).arg(train->getTrainTerminatesName()).arg(
                                             train->getName());
                         }
                         newLine(fileOut, trainDeparts);
                     }
                 }
             }
             if (trainDone && !pickupCars && !dropCars) {
                 newLine(fileOut, QString(messageFormatText = TrainSwitchListText::getStringTrainDone()).arg(
                         train->getName()).arg(train->getDescription()).arg(splitString(location->getName())));
             } else {
                 if (stops > 1 && !pickupCars) {
                     newLine(fileOut, QString(messageFormatText = TrainSwitchListText
                             ::getStringNoCarPickUps()).arg(train->getName()).arg(train->getDescription()).arg(
                             splitString(location->getName())));
                 }
                 if (stops > 1 && !dropCars) {
                     newLine(fileOut, QString(messageFormatText = TrainSwitchListText
                            ::getStringNoCarDrops()).arg(train->getName()).arg(train->getDescription()).arg(
                             splitString(location->getName())));
                 }
             }
         }
         // now report car movement by tracks at location
         if (Setup::isTrackSummaryEnabled() && !newTrainsOnly) {
             clearUtilityCarTypes(); // list utility cars by quantity
             if (Setup::getSwitchListPageFormat()==(Setup::PAGE_NORMAL)) {
                 newLine(fileOut);
                 newLine(fileOut);
             } else {
                 fileOut->write(QString(FORM_FEED));
             }
             newLine(fileOut, QString(messageFormatText = TrainSwitchListText
                     ::getStringSwitchListByTrack()).arg(splitString(location->getName())));
             // we only need the cars at this location
             QList<RollingStock*>* rsList = carManager->getByTrainList();
             QList<Car*>* carList = new QList<Car*>();
             foreach (RollingStock* rs, *rsList) {
                 if ((rs->getLocation() != NULL && splitString(rs->getLocation()->getName())==(splitString(location->getName())))
                         ||
                         (rs->getDestination() != NULL && splitString(rs->getDestination()->getName())==(splitString(location->getName()))))
                     carList->append((Car*) rs);
             }
             QString trackName = "";
             foreach (Location* loc, locationManager->getLocationsByNameList()) {
                 if (splitString(loc->getName())!=(splitString(location->getName())))
                     continue;
                 foreach (Track* track, loc->getTracksByNameList(NULL)) {
                     if (trackName==(splitString(track->getName())))
                         continue;
                     QString trainName = "";
                     trackName = splitString(track->getName());
                     newLine(fileOut);
                     newLine(fileOut, trackName);
                     foreach (Car* car, *carList) {
                         if (splitString(car->getTrackName())==(trackName)) {
                             if (car->getRouteLocation() != NULL) {
                                 if (splitString(car->getRouteLocation()->getLocation()->getName())==(splitString(location->getName()))) {
                                     if (trainName!=(car->getTrainName())) {
                                         trainName = car->getTrainName();
                                         newLine(fileOut, QString(messageFormatText = TrainSwitchListText
                                                 ::getStringScheduledWork()).arg(car->getTrainName()).arg(car->getTrain()->getDescription()));
                                         printPickupCarHeader(fileOut, !IS_MANIFEST, !IS_TWO_COLUMN_TRACK);
                                     }
                                     if (car->isUtility()) {
                                         pickupUtilityCars(fileOut, carList, car, !IS_MANIFEST);
                                     } else {
                                         pickUpCar(fileOut, car, !IS_MANIFEST);
                                     }
                                 }
                                 // car holds
                             } else if (car->isUtility()) {
                                 QString s = pickupUtilityCars(carList, car, !IS_MANIFEST, !IS_TWO_COLUMN_TRACK);
                                 if (s != NULL) {
                                     newLine(fileOut, TrainSwitchListText::getStringHoldCar().split(QRegExp("\\{"))[0] + s.trimmed());
                                 }
                             } else {
                                 newLine(fileOut, QString(messageFormatText = TrainSwitchListText::getStringHoldCar()).arg(
                                         padAndTruncateString(car->getRoadName(), ((CarRoads*)InstanceManager::getDefault("CarRoads"))->getMaxNameLength())).arg(
                                                 padAndTruncateString(car->getNumber(), Control::max_len_string_print_road_number)).arg(
                                                 padAndTruncateString(car->getTypeName().split("-")[0], ((CarTypes*)InstanceManager::getDefault("CarTypes"))->getMaxNameLength())).arg(
                                                 padAndTruncateString(car->getLength() + LENGTHABV, Control::max_len_string_length_name)).arg(
                                                 padAndTruncateString(car->getLoadName(), ((CarLoads*)InstanceManager::getDefault("CarLoads"))->getMaxNameLength())).arg(
                                                 padAndTruncateString(trackName, locationManager->getMaxTrackNameLength())).arg(
                                                 padAndTruncateString(car->getColor(), ((CarColors*)InstanceManager::getDefault("CarColors"))->getMaxNameLength())));
                             }
                         }
                     }
                     foreach (Car* car, *carList) {
                         if (splitString(car->getDestinationTrackName())==(trackName)) {
                             if (car->getRouteDestination() != NULL &&
                                     splitString(car->getRouteDestination()->getLocation()->getName())==(splitString(location->getName()))) {
                                 if (trainName != car->getTrainName()) {
                                     trainName = car->getTrainName();
                                     newLine(fileOut, QString(messageFormatText = TrainSwitchListText
                                             ::getStringScheduledWork()).arg(car->getTrainName()).arg(car->getTrain()->getDescription()));
                                     printDropCarHeader(fileOut, !IS_MANIFEST, !IS_TWO_COLUMN_TRACK);
                                 }
                                 if (car->isUtility()) {
                                     setoutUtilityCars(fileOut, carList, car, !IS_MANIFEST);
                                 } else {
                                     dropCar(fileOut, car, !IS_MANIFEST);
                                 }
                             }
                         }
                     }
                 }
             }
         }

//     } catch (IllegalArgumentException e) {
//         newLine(fileOut, QString(tr("ERROR! Window \"%1\" has an illegal argument. %2").arg(
//                 tr("Edit Switch List Text")).arg(e->getLocalizedMessage()));
//         newLine(fileOut, messageFormatText);
//         //e.printStackTrace();
//     }

     // Are there any cars that need to be found?
     addCarsLocationUnknown(fileOut, !IS_MANIFEST);
     fileOut->flush();
     fileOut->close();
 }

 /*public*/ void TrainSwitchLists::printSwitchList(Location* location, bool isPreview) {
     File* buildFile = ((TrainManagerXml*)InstanceManager::getDefault("TrainManagerXml"))->getSwitchListFile(location->getName());
     if (!buildFile->exists()) {
         log->warn(tr("Switch list file missing for location (%1)").arg(location->getName()));
         return;
     }
//     if (isPreview && Setup::isManifestEditorEnabled()) {
//         TrainPrintUtilities::openDesktopEditor(buildFile);
//     }
//     else
     {
         TrainPrintUtilities::printReport(buildFile, location->getName(), isPreview, Setup::getFontName(), false,
                 FileUtil::getExternalFilename(Setup::getManifestLogoURL()), location->getDefaultPrinterName(), Setup
                         ::getSwitchListOrientation(), Setup::getManifestFontSize());
     }
     if (!isPreview) {
         location->setStatus(Location::PRINTED);
         location->setSwitchListState(Location::SW_PRINTED);
     }
 }

 /*protected*/ void TrainSwitchLists::newLine(PrintWriter* file, QString string) {
     TrainCommon::newLine(file, string, !IS_MANIFEST);
 }
 /*protected*/ void TrainSwitchLists::newLine(PrintWriter* file) {
     TrainCommon::newLine(file);
 }

}
