#include "traincommon.h"
#include <QDate>
#include "cartypes.h"
#include "carroads.h"
#include "car.h"
#include "engine.h"
#include "routelocation.h"
#include "carmanager.h"
#include "trainmanager.h"
#include "enginemanager.h"
#include "location.h"
#include "setup.h"
#include "enginemodels.h"
#include "locationmanager.h"
#include "carlengths.h"
#include "carloads.h"
#include "carowners.h"
#include "control.h"
#include "carcolors.h"
#include "trainmanifestheadertext.h"
#include "printwriter.h"
#include <QFont>
#include <QLabel>
#include <QFontMetrics>
#include "track.h"
#include "trainmanifesttext.h"
#include "kernel.h"
#include "carload.h"
#include "train.h"
#include "route.h"
#include "calendar.h"
#include "instancemanager.h"
#include "colorutil.h"

//TrainCommon::TrainCommon(QObject *parent) :
//  QObject(parent)
//{
//}
namespace Operations {
/**
 * Common routines for trains
 *
 * @author Daniel Boudreau (C) Copyright 2008, 2009, 2010, 2011, 2012, 2013
 * @version $Revision: 1 $
 */
///*public*/ class TrainCommon {

 /*public*/ /*static*/ /*final*/ QString TrainCommon::LENGTHABV = "'";//Setup::LENGTHABV; // Length symbol
 /*protected*/ /*static*/ /*final*/ QString TrainCommon::TAB = "    "; // NOI18N
 /*protected*/ /*static*/ /*final*/ QString TrainCommon::NEW_LINE = "\n"; // NOI18N
 /*protected*/ /*static*/ /*final*/ QString TrainCommon::SPACE = " ";
 /*protected*/ /*static*/ /*final*/ QString TrainCommon::BLANK_LINE = " ";
 /*protected*/ /*static*/ /*final*/ QString TrainCommon::HORIZONTAL_LINE_CHAR = "-";
 /*public*/ /*static*/ /*final*/ QString TrainCommon::HYPHEN = "-";
 /*protected*/ /*static*/ /*final*/ QString TrainCommon::VERTICAL_LINE_CHAR = "|";
 /*protected*/ /*static*/ /*final*/ QString TrainCommon::TEXT_COLOR_START = "<FONT color=\"";
 /*protected*/ /*static*/ /*final*/ QString TrainCommon::TEXT_COLOR_END = "</FONT>";
 // /*protected*/ static /*final*/ String ARROW = ">";

 /*protected*/ /*static*/ /*final*/ bool TrainCommon::PICKUP = true;
 /*protected*/ /*static*/ /*final*/ bool TrainCommon::IS_MANIFEST = true;
 /*public*/ /*static*/ /*final*/ bool TrainCommon::LOCAL = true;
 /*protected*/ /*static*/ /*final*/ bool TrainCommon::ENGINE = true;
 /*public*/ /*static*/ /*final*/ bool TrainCommon::IS_TWO_COLUMN_TRACK = true;
 TrainCommon::TrainCommon(QObject *parent) : QObject(parent)
 {
  carManager = ((CarManager*)InstanceManager::getDefault("CarManager"));
  engineManager = ((EngineManager*)InstanceManager::getDefault("EngineManager"));
  locationManager = ((LocationManager*)InstanceManager::getDefault("LocationManager"));
  cars = 0;
  emptyCars = 0;
  log = new Logger("TrainCommon");
  log->setDebugEnabled(true);
  printPickupHeader = true;
  printSetoutHeader = true;
  printLocalMoveHeader = true;
  doneCars = QList<Car*>();
  index = 0;
 }


 /*protected*/ void TrainCommon::blockLocosTwoColumn(PrintWriter* file, QList<Engine*>* engineList, RouteLocation* rl, bool isManifest) {
     if (isThereWorkAtLocation(NULL, engineList, rl)) {
         printEngineHeader(file, isManifest);
     }
     int lineLength = getLineLength(isManifest);
     foreach (Engine* engine, *engineList) {
         if (engine->getRouteLocation() == rl && engine->getTrackName()!=(Engine::NONE)) {
             QString s = padAndTruncateString(pickupEngine(engine).trimmed(), lineLength / 2, true);
             s = padAndTruncateString(s + VERTICAL_LINE_CHAR, lineLength, true);
             addLine(file, s);
         }
         if (engine->getRouteDestination() == rl) {
             QString s = padAndTruncateString(tabString("", lineLength / 2, true) + VERTICAL_LINE_CHAR
                     + dropEngine(engine).trimmed(), lineLength, true);
             addLine(file, s);
         }
     }
 }

 /**
  * Adds a list of locomotive pick ups for the route location to the output
  * file
  *
  * @param file
  * @param engineList
  * @param rl
  * @param isManifest
  */
 /*protected*/ void TrainCommon::pickupEngines(PrintWriter* file, QList<Engine*>* engineList, RouteLocation* rl, bool isManifest) {
     bool printHeader = Setup::isPrintHeadersEnabled();
     foreach (Engine* engine, *engineList) {
         if (engine->getRouteLocation() == rl && engine->getTrackName()!=(Engine::NONE)) {
             if (printHeader) {
                 printPickupEngineHeader(file, isManifest);
                 printHeader = false;
             }
             pickupEngine(file, engine, isManifest);
         }
     }
 }

 /*private*/ void TrainCommon::pickupEngine(PrintWriter* file, Engine* engine, bool isManifest)
 {
  QString buf = QString(padAndTruncateString(Setup::getPickupEnginePrefix(), isManifest ? Setup::getManifestPrefixLength() : Setup::getSwitchListPrefixLength()));
  QStringList format = Setup::getPickupEngineMessageFormat();
  foreach (QString attribute, format)
  {
   if(attribute.isEmpty())
    continue;
   QString s = getEngineAttribute(engine, attribute, PICKUP);
   if (!checkStringLength(buf/*.toString()*/ + s, isManifest)) {
       addLine(file, buf/*.toString()*/);
       buf =  QString(TAB);
   }
   buf.append(s);
  }
  addLine(file, buf/*.toString()*/);
 }

 /**
  * Adds a list of locomotive drops for the route location to the output file
  *
  * @param file
  * @param engineList
  * @param rl
  * @param isManifest
  */
 /*protected*/ void TrainCommon::dropEngines(PrintWriter* file, QList<Engine*>* engineList, RouteLocation* rl, bool isManifest)
 {
  bool printHeader = Setup::isPrintHeadersEnabled();
  foreach (Engine* engine, *engineList)
  {
   if (engine->getRouteDestination() == rl)
   {
    if (printHeader) {
        printDropEngineHeader(file, isManifest);
        printHeader = false;
    }
    dropEngine(file, engine, isManifest);
   }
  }
 }

 /*private*/ void TrainCommon::dropEngine(PrintWriter* file, Engine* engine, bool isManifest)
 {
  QString buf =  QString(padAndTruncateString(Setup::getDropEnginePrefix(), isManifest ? Setup::getManifestPrefixLength() : Setup::getSwitchListPrefixLength()));
  QStringList format = Setup::getDropEngineMessageFormat();
  foreach (QString attribute, format)
  {
   if(attribute.isEmpty())
    continue;
   QString s = getEngineAttribute(engine, attribute, !PICKUP);
   if (!checkStringLength(buf/*.toString()*/ + s, isManifest))
   {
    addLine(file, buf/*.toString()*/);
    buf =  QString(TAB);
   }
   buf.append(s);
  }
  addLine(file, buf/*.toString()*/);
 }

 /**
  * Returns the pick up string for a loco. Useful for frames like the train
  * conductor and yardmaster.
  *
  * @param engine
  * @return engine pick up string
  */
 /*public*/ QString TrainCommon::pickupEngine(Engine* engine) {
     QString builder = ""; //new StringBuilder();
     foreach (QString attribute, Setup::getPickupEngineMessageFormat()) {
         builder.append(getEngineAttribute(engine, attribute, PICKUP));
     }
     return builder/*.toString()*/;
 }

 /**
  * Returns the drop string for a loco. Useful for frames like the train
  * conductor and yardmaster.
  *
  * @param engine
  * @return engine drop string
  */
 /*public*/ QString TrainCommon::dropEngine(Engine* engine)
 {
  QString builder = ""; //new StringBuilder();
  foreach (QString attribute, Setup::getDropEngineMessageFormat()) {
      builder.append(getEngineAttribute(engine, attribute, !PICKUP));
  }
  return builder/*.toString()*/;
 }


 /**
  * Block cars by track, then pick up and set out for each location in a
  * train's route.
  */
 /*protected*/ void TrainCommon::blockCarsByTrack(PrintWriter* file, Train* /*train*/, QList<Car*>* carList, QList<RouteLocation*>* routeList,
         RouteLocation* rl, bool printHeader, bool isManifest)
 {
  if (printHeader) {
      printPickupHeader = true;
      printSetoutHeader = true;
      printLocalMoveHeader = true;
  }
  QList<Track*> tracks = rl->getLocation()->getTrackByNameList(NULL);
  QStringList trackNames = QStringList();
  clearUtilityCarTypes(); // list utility cars by quantity
  foreach (Track* track, tracks) {
      if (trackNames.contains(splitString(track->getName()))) {
          continue;
      }
      trackNames.append(splitString(track->getName())); // use a track name once
      // block pick up cars by destination
      bool found = false; // begin blocking at rl
      foreach (RouteLocation* rld, *routeList) {
          if (rld != rl && !found) {
              continue;
          }
          found = true;
          foreach (Car* car, *carList) {
              if (Setup::isSortByTrackEnabled()
                      && splitString(track->getName())!=(splitString(car->getTrackName()))) {
                  continue;
              }
              // note that a car in train doesn't have a track assignment
              if (car->getRouteLocation() == rl && car->getTrack() != NULL && car->getRouteDestination() == rld) {
                  // determine if header is to be printed
                  if (printPickupHeader && !isLocalMove(car)) {
                      printPickupCarHeader(file, isManifest, !IS_TWO_COLUMN_TRACK);
                      printPickupHeader = false;
                      // check to see if set out header is needed
                      if (getPickupCarHeader(isManifest, !IS_TWO_COLUMN_TRACK)==(
                              getDropCarHeader(isManifest, !IS_TWO_COLUMN_TRACK))) {
                          printSetoutHeader = false;
                      }
                      if (getPickupCarHeader(isManifest, !IS_TWO_COLUMN_TRACK)==(
                              getLocalMoveHeader(isManifest))) {
                          printLocalMoveHeader = false;
                      }
                  }
                  if (car->isUtility()) {
                      pickupUtilityCars(file, carList, car, isManifest);
                  } // use truncated format if there's a switch list
                  else if (isManifest && Setup::isTruncateManifestEnabled()
                          && rl->getLocation()->isSwitchListEnabled()) {
                      pickUpCarTruncated(file, car, isManifest);
                  } else {
                      pickUpCar(file, car, isManifest);
                  }
                  pickupCars = true;
                  cars++;
                  if (car->getLoadType()==(CarLoad::LOAD_TYPE_EMPTY)) {
                      emptyCars++;
                  }
              }
          }
      }
      // now do set outs and local moves
      foreach (Car* car, *carList) {
          if (Setup::isSortByTrackEnabled() && car->getRouteLocation() != NULL && car->getRouteDestination() == rl) {
              // sort local moves by the car's current track name
              if (isLocalMove(car)) {
                  if (splitString(track->getName())!=(splitString(car->getTrackName()))) {
                      continue;
                  }
              } else if (splitString(track->getName())!=(splitString(car->getDestinationTrackName()))) {
                  continue;
              }
          }
          if (car->getRouteDestination() == rl && car->getDestinationTrack() != NULL) {
              if (printSetoutHeader && !isLocalMove(car)) {
                  printDropCarHeader(file, isManifest, !IS_TWO_COLUMN_TRACK);
                  printSetoutHeader = false;
                  if (getPickupCarHeader(isManifest, !IS_TWO_COLUMN_TRACK)==(
                          getDropCarHeader(isManifest, !IS_TWO_COLUMN_TRACK))) {
                      printPickupHeader = false;
                  }
                  if (getDropCarHeader(isManifest, !IS_TWO_COLUMN_TRACK)==(getLocalMoveHeader(isManifest))) {
                      printLocalMoveHeader = false;
                  }
              }
              if (printLocalMoveHeader && isLocalMove(car)) {
                  printLocalCarMoveHeader(file, isManifest);
                  printLocalMoveHeader = false;
                  if (getPickupCarHeader(isManifest, !IS_TWO_COLUMN_TRACK)==(getLocalMoveHeader(isManifest))) {
                      printPickupHeader = false;
                  }
                  if (getDropCarHeader(isManifest, !IS_TWO_COLUMN_TRACK)==(getLocalMoveHeader(isManifest))) {
                      printSetoutHeader = false;
                  }
              }

              if (car->isUtility()) {
                  setoutUtilityCars(file, carList, car, isManifest);
              } // use truncated format if there's a switch list
              else if (isManifest && Setup::isTruncateManifestEnabled() && rl->getLocation()->isSwitchListEnabled()) {
                  truncatedDropCar(file, car, isManifest);
              } else {
                  dropCar(file, car, isManifest);
              }
              dropCars = true;
              cars--;
              if (((CarLoads*)InstanceManager::getDefault("CarLoads"))->getLoadType(car->getTypeName(), car->getLoadName())==(
                      CarLoad::LOAD_TYPE_EMPTY)) {
                  emptyCars--;
              }
          }
      }
      if (!Setup::isSortByTrackEnabled()) {
          break; // done
      }
  }
 }

 /**
  * Produces a two column format for car pick ups and set outs. Sorted by
  * track and then by destination.
  */
 /*protected*/ void TrainCommon::blockCarsByTrackTwoColumn(PrintWriter* file, Train* /*train*/, QList<Car*>* carList,
         QList<RouteLocation*>* routeList, RouteLocation* rl, bool printHeader, bool isManifest)
 {
  index = 0;
  int lineLength = getLineLength(isManifest);
  QList<Track*> tracks = rl->getLocation()->getTrackByNameList(NULL);
  QStringList trackNames = QStringList();
  clearUtilityCarTypes(); // list utility cars by quantity
  if (printHeader) {
      printCarHeader(file, isManifest, !IS_TWO_COLUMN_TRACK);
  }
  foreach (Track* track, tracks) {
      if (trackNames.contains(splitString(track->getName()))) {
          continue;
      }
      trackNames.append(splitString(track->getName())); // use a track name once
      // block car pick ups by destination
      bool found = false; // begin blocking at rl
      foreach (RouteLocation* rld, *routeList) {
          if (rld != rl && !found) {
              continue;
          }
          found = true;
          for (int k = 0; k < carList->size(); k++) {
              Car* car = carList->at(k);
              if (car->getRouteLocation() == rl && car->getTrackName()!=(Car::NONE)
                      && car->getRouteDestination() == rld) {
                  if (Setup::isSortByTrackEnabled()
                          && splitString(track->getName())!=(splitString(car->getTrackName()))) {
                      continue;
                  }
                  pickupCars = true;
                  cars++;
                  if (car->getLoadType()==(CarLoad::LOAD_TYPE_EMPTY)) {
                      emptyCars++;
                  }
                  QString s;
                  if (car->isUtility()) {
                      s = pickupUtilityCars(carList, car, isManifest, !IS_TWO_COLUMN_TRACK);
                      if (s == NULL) {
                          continue;
                      }
                      s = s.trimmed();
                  } else {
                      s = pickupCar(car, isManifest, !IS_TWO_COLUMN_TRACK).trimmed();
                  }
                  s = padAndTruncateString(s, lineLength / 2, true);
                  if (isLocalMove(car)) {
                      QString sl = appendSetoutString(s, carList, car->getRouteDestination(), car, isManifest,
                              !IS_TWO_COLUMN_TRACK);
                      // check for utility car, and local route with two or more locations
                      if (sl!=(s)) {
                          s = sl;
                          carList->removeOne(car); // done with this car, remove from list
                          k--;
                      } else {
                          s = padAndTruncateString(s + VERTICAL_LINE_CHAR, getLineLength(isManifest), true);
                      }
                  } else {
                      s = appendSetoutString(s, carList, rl, true, isManifest, !IS_TWO_COLUMN_TRACK);
                  }
                  addLine(file, s);
              }
          }
      }
      if (!Setup::isSortByTrackEnabled()) {
          break; // done
      }
  }
  while (index < carList->size()) {
      QString s = padString("", lineLength / 2);
      s = appendSetoutString(s, carList, rl, false, isManifest, !IS_TWO_COLUMN_TRACK);
      QString test = s.trimmed();
      if (test.length() > 1) // NULL line contains |
      {
          addLine(file, s);
      }
  }
 }


 /**
  * Produces a two column format for car pick ups and set outs. Sorted by
  * track and then by destination. Track name in header format, track name
  * removed from format.
  */
 /*protected*/ void TrainCommon::blockCarsByTrackNameTwoColumn(PrintWriter* file, Train* /*train*/, QList<Car*>* carList,
         QList<RouteLocation*>* routeList, RouteLocation* rl, bool printHeader, bool isManifest) {
     index = 0;
     int lineLength = getLineLength(isManifest);
     QList<Track*> tracks = rl->getLocation()->getTrackByNameList(NULL);
     QStringList trackNames = QStringList();
     doneCars.clear();
     clearUtilityCarTypes(); // list utility cars by quantity
     if (printHeader) {
         printCarHeader(file, isManifest, IS_TWO_COLUMN_TRACK);
     }
     foreach (Track* track, tracks) {
         QString trackName = splitString(track->getName());
         if (trackNames.contains(trackName)) {
             continue;
         }
         // block car pick ups by destination
         bool found = false; // begin blocking at rl
         foreach (RouteLocation* rld, *routeList) {
             if (rld != rl && !found) {
                 continue;
             }
             found = true;
             foreach (Car* car, *carList) {
                 if (car->getRouteLocation() == rl && car->getTrackName()!=(Car::NONE)
                         && car->getRouteDestination() == rld && trackName==(splitString(car->getTrackName()))) {
                     if (!trackNames.contains(trackName)) {
                         printTrackNameHeader(file, trackName, isManifest);
                     }
                     trackNames.append(trackName); // use a track name once
                     pickupCars = true;
                     cars++;
                     if (car->getLoadType()==(CarLoad::LOAD_TYPE_EMPTY)) {
                         emptyCars++;
                     }
                     QString s;
                     if (car->isUtility()) {
                         s = pickupUtilityCars(carList, car, isManifest, IS_TWO_COLUMN_TRACK);
                         if (s == NULL) {
                             continue;
                         }
                         s = s.trimmed();
                     } else {
                         s = pickupCar(car, isManifest, IS_TWO_COLUMN_TRACK).trimmed();
                     }
                     s = padAndTruncateString(s, lineLength / 2, true);
                     s = appendSetoutString(s, trackName, carList, rl, isManifest, IS_TWO_COLUMN_TRACK);
                     addLine(file, s);
                 }
             }
         }
         foreach (Car* car, *carList) {
             if (!doneCars.contains(car) && car->getRouteDestination() == rl
                     && trackName==(splitString(car->getDestinationTrackName()))) {
                 if (!trackNames.contains(trackName)) {
                     printTrackNameHeader(file, trackName, isManifest);
                 }
                 trackNames.append(trackName); // use a track name once
                 QString s = padString("", lineLength / 2);
                 QString so = appendSetoutString(s, carList, rl, car, isManifest, IS_TWO_COLUMN_TRACK);
                 // check for utility car
                 if (so==(s)) {
                     continue;
                 }
                 QString test = so.trimmed();
                 if (test.length() > 1) // NULL line contains |
                 {
                     addLine(file, so);
                 }
             }
         }
     }
 }

 /*protected*/ void TrainCommon::printTrackComments(PrintWriter* file, RouteLocation* rl, QList<Car*>* carList, bool isManifest) {
     Location* location = rl->getLocation();
     if (location != NULL) {
         QList<Track*> tracks = location->getTrackByNameList(NULL);
         foreach (Track* track, tracks) {
             // any pick ups or set outs to this track?
             bool pickup = false;
             bool setout = false;
             foreach (Car* car, *carList) {
                 if (car->getRouteLocation() == rl && car->getTrack() != NULL && car->getTrack() == track) {
                     pickup = true;
                 }
                 if (car->getRouteDestination() == rl && car->getDestinationTrack() != NULL
                         && car->getDestinationTrack() == track) {
                     setout = true;
                 }
             }
             // print the appropriate comment if there's one
             if (pickup && setout && track->getCommentBoth()!=(Track::NONE)) {
                 newLine(file, track->getCommentBoth(), isManifest);
             } else if (pickup && !setout && track->getCommentPickup()!=(Track::NONE)) {
                 newLine(file, track->getCommentPickup(), isManifest);
             } else if (!pickup && setout && track->getCommentSetout()!=(Track::NONE)) {
                 newLine(file, track->getCommentSetout(), isManifest);
             }
         }
     }
 }

 /*
  * Used by two column format. Local moves (pulls and spots) are lined up
  * when using this format,
  */
 /*private*/ QString TrainCommon::appendSetoutString(QString s, QList<Car*>* carList, RouteLocation* rl, bool local, bool isManifest,
         bool isTwoColumnTrack) {
     while (index < carList->size()) {
         Car* car = carList->at(index++);
         if (local && isLocalMove(car)) {
             continue; // skip local moves
         } // car list is already sorted by destination track
         if (car->getRouteDestination() == rl) {
             QString so = appendSetoutString(s, carList, rl, car, isManifest, isTwoColumnTrack);
             // check for utility car
             if (so!=(s)) {
                 return so;
             }
         }
     }
     return padAndTruncateString(s + VERTICAL_LINE_CHAR, getLineLength(isManifest), true);
 }

 /*
  * Used by two column track format.
  */
 /*private*/ QString TrainCommon::appendSetoutString(QString s, QString trackName, QList<Car*>* carList, RouteLocation* rl,
         bool isManifest, bool isTwoColumnTrack) {
     foreach (Car* car, *carList) {
         if (!doneCars.contains(car) && car->getRouteDestination() == rl
                 && trackName==(splitString(car->getDestinationTrackName()))) {
             doneCars.append(car);
             QString so = appendSetoutString(s, carList, rl, car, isManifest, isTwoColumnTrack);
             // check for utility car
             if (so!=(s)) {
                 return so;
             }
         }
     }
     return padAndTruncateString(s + VERTICAL_LINE_CHAR, getLineLength(isManifest), true);
 }

 /*
  * Appends to string the vertical line character, and the car set out
  * string. Used in two column format.
  */
 /*private*/ QString TrainCommon::appendSetoutString(QString s, QList<Car*>* carList, RouteLocation* rl, Car* car, bool isManifest,
         bool isTwoColumnTrack) {
     dropCars = true;
     cars--;
     if (car->getLoadType()==(CarLoad::LOAD_TYPE_EMPTY)) {
         emptyCars--;
     }
     QString newString;
     // use truncated format if there's a switch list
     // else if (Setup::isTruncateManifestEnabled() && rl.getLocation().isSwitchListEnabled())
     // truncatedDropCar(file, car);

     // if (isLocalMove(car))
     // newString = s + ARROW; // NOI18N
     // else
     newString = s + VERTICAL_LINE_CHAR;

     if (car->isUtility()) {
         QString so = setoutUtilityCars(carList, car, !LOCAL, isManifest, isTwoColumnTrack);
         if (so == NULL) {
             return s; // no changes to the input string
         }
         newString = newString + so.trimmed();
     } else {
         newString = newString + dropCar(car, isManifest, isTwoColumnTrack).trimmed();
     }
     return padAndTruncateString(newString, getLineLength(isManifest), true);
 }

 /**
  * Adds the car's pick up string to the output file using the truncated
  * manifest format
  *
  * @param file
  * @param car
  */
 /*protected*/ void TrainCommon::pickUpCarTruncated(PrintWriter* file, Car* car, bool isManifest) {
     pickUpCar(file, car, QString(padAndTruncateString(Setup::getPickupCarPrefix(), Setup
             ::getManifestPrefixLength())), Setup::getPickupTruncatedManifestMessageFormat(), isManifest);
 }

 /**
  * Adds the car's pick up string to the output file using the manifest or
  * switch list format
  *
  * @param file
  * @param car
  */
 /*protected*/ void TrainCommon::pickUpCar(PrintWriter* file, Car* car, bool isManifest) {
     if (isManifest) {
         pickUpCar(file, car, QString(padAndTruncateString(Setup::getPickupCarPrefix(), Setup
                 ::getManifestPrefixLength())), Setup::getPickupManifestMessageFormat(), isManifest);
     } else {
         pickUpCar(file, car, QString(padAndTruncateString(Setup::getSwitchListPickupCarPrefix(), Setup
                 ::getSwitchListPrefixLength())), Setup::getPickupSwitchListMessageFormat(), isManifest);
     }
 }

 /*private*/ void TrainCommon::pickUpCar(PrintWriter* file, Car* car, QString buf, QStringList format, bool isManifest) {
     if (isLocalMove(car)) {
         return; // print nothing local move, see dropCar
     }
     foreach (QString attribute, format) {
         QString s = getCarAttribute(car, attribute, PICKUP, !LOCAL);
         if (!checkStringLength(buf/*.toString()*/ + s, isManifest)) {
             addLine(file, buf/*.toString()*/);
             buf =  QString(TAB);
         }
         buf.append(s);
     }
     QString s = buf/*.toString()*/;
     if (s.trimmed().length() != 0) {
         addLine(file, s);
     }
 }

 /**
  * Returns the pick up car string. Useful for frames like train conductor
  * and yardmaster.
  *
  * @param isManifest when true use manifest format, when false use switch
  *            list format
  * @param car
  * @return pick up car string
  */
 /*public*/ QString TrainCommon::pickupCar(Car* car, bool isManifest, bool isTwoColumnTrack) {
     QString buf = "";//QString();
     QStringList format;
     if (isManifest && !isTwoColumnTrack) {
         format = Setup::getPickupManifestMessageFormat();
     } else if (!isManifest && !isTwoColumnTrack) {
         format = Setup::getPickupSwitchListMessageFormat();
     } else if (isManifest && isTwoColumnTrack) {
         format = Setup::getPickupTwoColumnByTrackManifestMessageFormat();
     } else {
         format = Setup::getPickupTwoColumnByTrackSwitchListMessageFormat();
     }
     foreach (QString attribute, format) {
         QString s = getCarAttribute(car, attribute, PICKUP, !LOCAL);
         buf.append(s);
     }
     return buf/*.toString()*/;
 }

 /**
  * Adds the car's set out string to the output file using the truncated
  * manifest format. Does not print out local moves. Local moves are only
  * shown on the switch list for that location.
  *
  * @param file
  * @param car
  */
 /*protected*/ void TrainCommon::truncatedDropCar(PrintWriter* file, Car* car, bool isManifest) {
     // local move?
     if (isLocalMove(car)) {
         return; // yes, don't print local moves on train manifest
     }
     dropCar(file, car, QString(Setup::getDropCarPrefix()), Setup::getDropTruncatedManifestMessageFormat(),
             false, isManifest);
 }

 /**
  * Adds the car's set out string to the output file using the manifest or
  * switch list format
  *
  * @param file
  * @param car
  * @param isManifest
  */
 /*protected*/ void TrainCommon::dropCar(PrintWriter* file, Car* car, bool isManifest) {
     if (isManifest) {
         QString buf = QString(padAndTruncateString(Setup::getDropCarPrefix(), Setup
                 ::getManifestPrefixLength()));
         QStringList format = Setup::getDropManifestMessageFormat();
         bool isLocal = isLocalMove(car);
         if (isLocal) {
             buf = QString(padAndTruncateString(Setup::getLocalPrefix(), Setup::getManifestPrefixLength()));
             format = Setup::getLocalManifestMessageFormat();
         }
         dropCar(file, car, buf, format, isLocal, isManifest);
     } else {
         QString buf = QString(padAndTruncateString(Setup::getSwitchListDropCarPrefix(), Setup
                 ::getSwitchListPrefixLength()));
         QStringList format = Setup::getDropSwitchListMessageFormat();
         bool isLocal = isLocalMove(car);
         if (isLocal) {
             buf = QString(padAndTruncateString(Setup::getSwitchListLocalPrefix(), Setup
                     ::getSwitchListPrefixLength()));
             format = Setup::getLocalSwitchListMessageFormat();
         }
         dropCar(file, car, buf, format, isLocal, isManifest);
     }
 }

 /*private*/ void TrainCommon::dropCar(PrintWriter* file, Car* car, QString buf, QStringList format, bool isLocal,
         bool isManifest) {
     foreach (QString attribute, format) {
         QString s = getCarAttribute(car, attribute, !PICKUP, isLocal);
         if (!checkStringLength(buf/*.toString()*/ + s, isManifest)) {
             addLine(file, buf/*.toString()*/);
             buf = QString(TAB);
         }
         buf.append(s);
     }
     QString s = buf;
     if (s.trimmed().length() != 0) {
         addLine(file, s);
     }
 }

 /**
  * Returns the drop car string. Useful for frames like train conductor and
  * yardmaster.
  *
  * @param car
  * @param isManifest when true use manifest format, when false use switch
  *            list format
  * @return drop car string
  */
 /*public*/ QString TrainCommon::dropCar(Car* car, bool isManifest, bool isTwoColumnTrack) {
     QString buf = "";//QString();
     QStringList format;
     if (isManifest && !isTwoColumnTrack) {
         format = Setup::getDropManifestMessageFormat();
     } else if (!isManifest && !isTwoColumnTrack) {
         format = Setup::getDropSwitchListMessageFormat();
     } else if (isManifest && isTwoColumnTrack) {
         format = Setup::getDropTwoColumnByTrackManifestMessageFormat();
     } else {
         format = Setup::getDropTwoColumnByTrackSwitchListMessageFormat();
     }
     // TODO the Setup::Location doesn't work correctly for the conductor
     // window due to the fact that the car can be in the train and not
     // at its starting location.
     // Therefore we use the local true to disable it.
     bool local = false;
     if (car->getTrack() == NULL) {
         local = true;
     }
     foreach (QString attribute, format) {
         QString s = getCarAttribute(car, attribute, !PICKUP, local);
         buf.append(s);
     }
     return buf/*.toString()*/;
 }

 /**
  * Returns the move car string. Useful for frames like train conductor and
  * yardmaster.
  *
  * @param isManifest when true use manifest format, when false use switch
  *            list format
  * @param car
  * @return move car string
  */
 /*public*/ QString TrainCommon::localMoveCar(Car* car, bool isManifest) {
     QString buf = "";// QString();
     QStringList format;
     if (isManifest) {
         format = Setup::getLocalManifestMessageFormat();
     } else {
         format = Setup::getLocalSwitchListMessageFormat();
     }
     foreach (QString attribute, format) {
         QString s = getCarAttribute(car, attribute, !PICKUP, LOCAL);
         buf.append(s);
     }
     return buf/*.toString()*/;
 }

 /*private*/ /*static*/ /*final*/ int TrainCommon::UTILITY_CAR_COUNT_FIELD_SIZE = 3;

 /**
  * Add a list of utility cars scheduled for pick up from the route location
  * to the output file. The cars are blocked by destination.
  *
  * @param file
  * @param carList
  * @param car
  * @param isManifest
  */
 /*protected*/ void TrainCommon::pickupUtilityCars(PrintWriter* file, QList<Car*>* carList, Car* car, bool isManifest) {
     // list utility cars by type, track, length, and load
     QStringList format;
     if (isManifest) {
         format = Setup::getPickupUtilityManifestMessageFormat();
     } else {
         format = Setup::getPickupUtilitySwitchListMessageFormat();
     }
     int count = countUtilityCars(format, carList, car, PICKUP);
     if (count == 0) {
         return; // already printed out this car type
     }
     pickUpCar(file, car, QString(padAndTruncateString(Setup::getPickupCarPrefix(), isManifest ? Setup
             ::getManifestPrefixLength() : Setup::getSwitchListPrefixLength())
             + " " + padString(QString::number(count), UTILITY_CAR_COUNT_FIELD_SIZE)), format, isManifest);
 }

 /**
  * Add a list of utility cars scheduled for drop at the route location to
  * the output file.
  *
  * @param file
  * @param carList
  * @param car
  * @param isManifest
  */
 /*protected*/ void TrainCommon::setoutUtilityCars(PrintWriter* file, QList<Car*>* carList, Car* car, bool isManifest) {
     bool isLocal = isLocalMove(car);
     QString buf;
     QStringList format;
     if (isLocal && isManifest) {
         buf = QString(padAndTruncateString(Setup::getLocalPrefix(), Setup::getManifestPrefixLength()));
         format = Setup::getLocalUtilityManifestMessageFormat();
     } else if (!isLocal && isManifest) {
         buf = QString(padAndTruncateString(Setup::getDropCarPrefix(), Setup::getManifestPrefixLength()));
         format = Setup::getDropUtilityManifestMessageFormat();
     } else if (isLocal && !isManifest) {
         buf = QString(padAndTruncateString(Setup::getSwitchListLocalPrefix(), Setup
                 ::getSwitchListPrefixLength()));
         format = Setup::getLocalUtilitySwitchListMessageFormat();
     } else {
         buf = QString(padAndTruncateString(Setup::getSwitchListDropCarPrefix(), Setup
                 ::getSwitchListPrefixLength()));
         format = Setup::getDropUtilitySwitchListMessageFormat();
     }
     int count = countUtilityCars(format, carList, car, !PICKUP);
     if (count == 0) {
         return; // already printed out this car type
     }
     buf.append(" " + padString(QString::number(count), UTILITY_CAR_COUNT_FIELD_SIZE));
     dropCar(file, car, buf, format, isLocal, isManifest);
 }

 /*public*/ QString TrainCommon::pickupUtilityCars(QList<Car*>* carList, Car* car, bool isManifest, bool isTwoColumnTrack) {
     int count = countPickupUtilityCars(carList, car, isManifest);
     if (count == 0) {
         return NULL;
     }
     QStringList format;
     if (isManifest && !isTwoColumnTrack) {
         format = Setup::getPickupUtilityManifestMessageFormat();
     } else if (!isManifest && !isTwoColumnTrack) {
         format = Setup::getPickupUtilitySwitchListMessageFormat();
     } else if (isManifest && isTwoColumnTrack) {
         format = Setup::getPickupTwoColumnByTrackUtilityManifestMessageFormat();
     } else {
         format = Setup::getPickupTwoColumnByTrackUtilitySwitchListMessageFormat();
     }
     QString buf =  QString(" " + padString(QString::number(count), UTILITY_CAR_COUNT_FIELD_SIZE));
     foreach (QString attribute, format) {
         QString s = getCarAttribute(car, attribute, PICKUP, !LOCAL);
         buf.append(s);
     }
     return buf/*.toString()*/;
 }

 /*public*/ int TrainCommon::countPickupUtilityCars(QList<Car*>* carList, Car* car, bool isManifest) {
     // list utility cars by type, track, length, and load
     QStringList format;
     if (isManifest) {
         format = Setup::getPickupUtilityManifestMessageFormat();
     } else {
         format = Setup::getPickupUtilitySwitchListMessageFormat();
     }
     return countUtilityCars(format, carList, car, PICKUP);
 }

 /**
  * For the Conductor and Yardmaster windows.
  */
 /*public*/ QString TrainCommon::setoutUtilityCars(QList<Car*> *carList, Car* car, bool isLocal, bool isManifest) {
     return setoutUtilityCars(carList, car, isLocal, isManifest, !IS_TWO_COLUMN_TRACK);
 }

 /*protected*/ QString TrainCommon::setoutUtilityCars(QList<Car*>* carList, Car* car, bool isLocal, bool isManifest,
         bool isTwoColumnTrack) {
     int count = countSetoutUtilityCars(carList, car, isLocal, isManifest);
     if (count == 0) {
         return NULL;
     }
     // list utility cars by type, track, length, and load
     QStringList format;
     if (isLocal && isManifest && !isTwoColumnTrack) {
         format = Setup::getLocalUtilityManifestMessageFormat();
     } else if (isLocal && !isManifest && !isTwoColumnTrack) {
         format = Setup::getLocalUtilitySwitchListMessageFormat();
     } else if (!isLocal && !isManifest && !isTwoColumnTrack) {
         format = Setup::getDropUtilitySwitchListMessageFormat();
     } else if (!isLocal && isManifest && !isTwoColumnTrack) {
         format = Setup::getDropUtilityManifestMessageFormat();
     } else if (isManifest && isTwoColumnTrack) {
         format = Setup::getDropTwoColumnByTrackUtilityManifestMessageFormat();
     } else {
         format = Setup::getDropTwoColumnByTrackUtilitySwitchListMessageFormat();
     }
     QString buf = QString(" " + padString(QString::number(count), UTILITY_CAR_COUNT_FIELD_SIZE));
     // TODO the Setup::Location doesn't work correctly for the conductor
     // window due to the fact that the car can be in the train and not
     // at its starting location.
     // Therefore we use the local true to disable it.
     if (car->getTrack() == NULL) {
         isLocal = true;
     }
     foreach (QString attribute, format) {
         QString s = getCarAttribute(car, attribute, !PICKUP, isLocal);
         buf.append(s);
     }
     return buf/*.toString()*/;
 }

 /*public*/ int TrainCommon::countSetoutUtilityCars(QList<Car*>* carList, Car* car, bool isLocal, bool isManifest) {
     // list utility cars by type, track, length, and load
     QStringList format;
     if (isLocal && isManifest) {
         format = Setup::getLocalUtilityManifestMessageFormat();
     } else if (isLocal && !isManifest) {
         format = Setup::getLocalUtilitySwitchListMessageFormat();
     } else if (!isLocal && !isManifest) {
         format = Setup::getDropUtilitySwitchListMessageFormat();
     } else {
         format = Setup::getDropUtilityManifestMessageFormat();
     }
     return countUtilityCars(format, carList, car, !PICKUP);
 }

 /**
  * Scans the car list for utility cars that have the same attributes as the
  * car provided. Returns 0 if this car type has already been processed,
  * otherwise the number of cars with the same attribute.
  *
  * @param format
  * @param carList
  * @param car
  * @param isPickup
  * @return 0 if the car type has already been processed
  */
 /*protected*/ int TrainCommon::countUtilityCars(QStringList format, QList<Car*>* carList, Car* car, bool isPickup) {
     int count = 0;
     // figure out if the user wants to show the car's length
     bool showLength = showUtilityCarLength(format);
     // figure out if the user want to show the car's loads
     bool showLoad = showUtilityCarLoad(format);
     bool showLocation = false;
     bool showDestination = false;
     QStringList carType = car->getTypeName().split("-");
     QString carAttributes;
     // Note for car pick up: type, id, track name. For set out type, track name, id (reversed).
     if (isPickup) {
         carAttributes = carType[0] + car->getRouteLocationId() + splitString(car->getTrackName());
         showDestination = showUtilityCarDestination(format);
         if (showDestination) {
             carAttributes = carAttributes + car->getRouteDestinationId();
         }
     } else {
         // set outs and local moves
         carAttributes = carType[0] + splitString(car->getDestinationTrackName()) + car->getRouteDestinationId();
         showLocation = showUtilityCarLocation(format);
         if (showLocation && car->getTrack() != NULL) {
             carAttributes = carAttributes + car->getRouteLocationId();
         }
         if (isLocalMove(car)) {
             carAttributes = carAttributes + splitString(car->getTrackName());
         }
     }
     if (showLength) {
         carAttributes = carAttributes + car->getLength();
     }
     if (showLoad) {
         carAttributes = carAttributes + car->getLoadName();
     }
     // have we already done this car type?
     if (!utilityCarTypes.contains(carAttributes)) {
         utilityCarTypes.append(carAttributes); // don't do this type again
         // determine how many cars of this type
         foreach (Car* c, *carList) {
             if (!c->isUtility()) {
                 continue;
             }
             QStringList cType = c->getTypeName().split("-");
             if (cType[0]!=(carType[0])) {
                 continue;
             }
             if (showLength && c->getLength()!=(car->getLength())) {
                 continue;
             }
             if (showLoad && c->getLoadName()!=(car->getLoadName())) {
                 continue;
             }
             if (showLocation && c->getRouteLocationId()!=(car->getRouteLocationId())) {
                 continue;
             }
             if (showDestination && c->getRouteDestinationId()!=(car->getRouteDestinationId())) {
                 continue;
             }
             if (isLocalMove(car) ^ isLocalMove(c)) {
                 continue;
             }
             if (isPickup && c->getRouteLocation() == car->getRouteLocation()
                     && splitString(c->getTrackName())==(splitString(car->getTrackName()))) {
                 count++;
             }
             if (!isPickup && c->getRouteDestination() == car->getRouteDestination()
                     && splitString(c->getDestinationTrackName())==(splitString(car->getDestinationTrackName()))
                     && (splitString(c->getTrackName())==(splitString(car->getTrackName())) || !isLocalMove(c))) {
                 count++;
             }
         }
     }
     return count;
 }

 /*public*/ void TrainCommon::clearUtilityCarTypes() {
     utilityCarTypes.clear();
 }

 /*private*/ bool TrainCommon::showUtilityCarLength(QStringList mFormat) {
     return showUtilityCarAttribute(Setup::LENGTH, mFormat);
 }

 /*private*/ bool TrainCommon::showUtilityCarLoad(QStringList mFormat) {
     return showUtilityCarAttribute(Setup::LOAD, mFormat);
 }

 /*private*/ bool TrainCommon::showUtilityCarLocation(QStringList mFormat) {
     return showUtilityCarAttribute(Setup::LOCATION, mFormat);
 }

 /*private*/ bool TrainCommon::showUtilityCarDestination(QStringList mFormat) {
     return showUtilityCarAttribute(Setup::DESTINATION, mFormat);
 }

 /*private*/ bool TrainCommon::showUtilityCarAttribute(QString string, QStringList mFormat) {
     foreach (QString s, mFormat) {
         if (s==(string)) {
             return true;
         }
     }
     return false;
 }

 /**
  * Writes a line to the build report file
  *
  * @param file build report file
  * @param level print level
  * @param string string to write
  */
 /*protected*/ /*static*/ void TrainCommon::addLine(PrintWriter* file, QString level, QString string)
 {
  Logger* log = new Logger("TrainCommon");
  if (log->isDebugEnabled())
  {
   log->debug(string);
  }
  if (file != NULL)
  {
   QStringList lines = string.split(NEW_LINE);
   foreach (QString line, lines)
   {
    printLine(file, level, line);
   }
  }
 }

 // only used by build report
 /*private*/ /*static*/ void TrainCommon::printLine(PrintWriter* file, QString level, QString string)
 {
  int lineLengthMax = getLineLength(Setup::PORTRAIT, Setup::getBuildReportFontSize(), Setup::MONOSPACED);
  if (string.length() > lineLengthMax)
  {
   QStringList words = string.split(SPACE);
   QString sb = ""; //QString();
   foreach (QString word, words)
   {
    if (sb.length() + word.length() < lineLengthMax)
    {
     sb.append(word + SPACE);
    }
    else
    {
     file->println(level + "- " + sb/*.toString()*/);
     sb = QString(word + SPACE);
    }
   }
   string = sb/*.toString()*/;
  }
  file->println(level + "- " + string);
 }

 /**
  * Used to determine if car is a local move
  *
  * @param car
  * @return true if the move is at the same location
  */
 /*protected*/ bool TrainCommon::isLocalMove(Car* car) {
     if (car->getRouteLocation() == NULL || car->getRouteDestination() == NULL) {
         return false;
     }
     if (car->getRouteLocation()==(car->getRouteDestination()) && car->getTrack() != NULL) {
         return true;
     }
     if (car->getTrain() != NULL
             && car->getTrain()->isLocalSwitcher()
             && splitString(car->getRouteLocation()->getName())==(
                     splitString(car->getRouteDestination()->getName())) && car->getTrack() != NULL) {
         return true;
     }
     // look for sequential locations with the "same" name
     if (splitString(car->getRouteLocation()->getName())==(splitString(car->getRouteDestination()->getName()))
             && car->getTrain() != NULL && car->getTrain()->getRoute() != NULL) {
         bool foundRl = false;
         foreach (RouteLocation* rl, *car->getTrain()->getRoute()->getLocationsBySequenceList()) {
             if (foundRl) {
                 if (splitString(car->getRouteDestination()->getName())==(splitString(rl->getName()))) {
                     // user can specify the "same" location two more more times in a row
                     if (car->getRouteDestination() != rl) {
                         continue;
                     } else {
                         return true;
                     }
                 } else {
                     return false;
                 }
             }
             if (car->getRouteLocation()==(rl)) {
                 foundRl = true;
             }
         }
     }
     return false;
 }

 /**
  * Writes string to file. No line length wrap or protection.
  *
  * @param file
  * @param string
  */
 /*protected*/ void TrainCommon::addLine(PrintWriter* file, QString string) {
     if (log->isDebugEnabled()) {
         log->debug(string);
     }
     if (file != NULL) {
         file->println(string);
     }
 }

 /**
  * Writes a string to a file. Checks for string length, and will
  * automatically wrap lines.
  *
  * @param file
  * @param string
  * @param isManifest set true for manifest page orientation, false for
  *            switch list orientation
  */
 /*protected*/ void TrainCommon::newLine(PrintWriter* file, QString string, bool isManifest) {
     QStringList lines = string.split(NEW_LINE);
     foreach (QString line, lines) {
         QStringList words = line.split(SPACE);
         QString sb = ""; //QString();
         foreach (QString word, words) {
             if (checkStringLength(sb/*.toString()*/ + word, isManifest)) {
                 sb.append(word + SPACE);
             } else {
                 //sb.setLength(sb.length() - 1); // remove last space added to string
              sb = sb.mid(0, sb.length()-1);
                 addLine(file, sb/*.toString()*/);
                 sb = QString(word + SPACE);
             }
         }
         if (sb.length() > 0) {
             //.setLength(sb.length() - 1); // remove last space added to string
          sb = sb.mid(0, sb.length()-1);
         }
         addLine(file, sb/*.toString()*/);
     }
 }

 /**
  * Adds a blank line to the file.
  *
  * @param file
  */
 /*protected*/ void TrainCommon::newLine(PrintWriter* file) {
     file->println(BLANK_LINE);
 }

 /**
  * Splits a string (example-number) as long as the second part of the string
  * is an integer or if the first character after the hyphen is a left
  * parenthesis "(".
  *
  * @param name
  * @return First half the string.
  */
 /*public*/ /*static*/ QString TrainCommon::splitString(QString name) {
     QStringList fullname = name.split("-");
     QString parsedName = fullname[0].trimmed();
     // is the hyphen followed by a number or left parenthesis?
     if (fullname.length() > 1 && !fullname[1].startsWith("(")) {
         //try {
      bool ok;
             fullname[1].toInt(&ok);
         if(!ok) {
             // no return full name
             parsedName = name.trimmed();
         }
     }
     return parsedName;
 }

 // returns true if there's work at location
 /*protected*/ bool TrainCommon::isThereWorkAtLocation(QList<Car*>* carList, QList<Engine*>* engList, RouteLocation* rl) {
     if (carList != NULL) {
         foreach (Car* car, *carList) {
             if (car->getRouteLocation() == rl || car->getRouteDestination() == rl) {
                 return true;
             }
         }
     }
     if (engList != NULL) {
         foreach (Engine* eng, *engList) {
             if (eng->getRouteLocation() == rl || eng->getRouteDestination() == rl) {
                 return true;
             }
         }
     }
     return false;
 }

 /**
  * returns true if the train has work at the location
  *
  * @param train
  * @param location
  * @return true if the train has work at the location
  */
 /*public*/ /*static*/  bool TrainCommon::isThereWorkAtLocation(Train* train, Location* location) {
     if (isThereWorkAtLocation(train, location, ((CarManager*)InstanceManager::getDefault("CarManager"))->getList(train))) {
         return true;
     }
     if (isThereWorkAtLocation(train, location, ((EngineManager*)InstanceManager::getDefault("EngineManager"))->getList(train))) {
         return true;
     }
     return false;
 }

 /*private*/ /*static*/ bool TrainCommon::isThereWorkAtLocation(Train* /*train*/, Location* location, QList<RollingStock*>* list) {
     foreach (RollingStock* rs, *list) {
         if ((rs->getRouteLocation() != NULL && rs->getTrack() != NULL && TrainCommon::splitString(
                 rs->getRouteLocation()->getName())==(TrainCommon::splitString(location->getName())))
                 || (rs->getRouteDestination() != NULL && TrainCommon::splitString(rs->getRouteDestination()->getName())
                         ==(TrainCommon::splitString(location->getName())))) {
             return true;
         }
     }
     return false;
 }

 /*protected*/ void TrainCommon::addCarsLocationUnknown(PrintWriter* file, bool isManifest) {
     CarManager* carManager = ((CarManager*)InstanceManager::getDefault("CarManager"));
     QList<Car*>* cars = carManager->getCarsLocationUnknown();
     if (cars->size() == 0) {
         return; // no cars to search for!
     }
     newLine(file);
     newLine(file, Setup::getMiaComment(), isManifest);
     foreach (Car* car, *cars) {
         addSearchForCar(file, car);
     }
 }

 /*private*/ void TrainCommon::addSearchForCar(PrintWriter* file, Car* car)
 {
  QString buf = ""; //QString();
  QStringList format = Setup::getMissingCarMessageFormat();
  foreach (QString attribute, format)
  {
   if(attribute.isEmpty())
    continue;
   buf.append(getCarAttribute(car, attribute, false, false));
  }
  addLine(file, buf/*.toString()*/);
 }

 // @param isPickup true when rolling stock is being picked up
 /*private*/ QString TrainCommon::getEngineAttribute(Engine* engine, QString attribute, bool isPickup) {
     if (attribute==(Setup::MODEL)) {
         return " " + padAndTruncateString(engine->getModel(), ((EngineModels*)InstanceManager::getDefault("EngineModels"))->getMaxNameLength());
     }
     if (attribute==(Setup::CONSIST)) {
         return " " + padAndTruncateString(engine->getConsistName(), engineManager->getConsistMaxNameLength());
     }
     return getRollingStockAttribute(engine, attribute, isPickup, false);
 }

 /*private*/ QString TrainCommon::getCarAttribute(Car* car, QString attribute, bool isPickup, bool isLocal)
 {
  if (attribute==(Setup::LOAD)) {
      return ((car->isCaboose() && !Setup::isPrintCabooseLoadEnabled()) || (car->isPassenger() && !Setup::isPrintPassengerLoadEnabled()))
              ? padAndTruncateString("", ((CarLoads*)InstanceManager::getDefault("CarLoads"))->getMaxNameLength() + 1) : " "
                      + padAndTruncateString(car->getLoadName(), ((CarLoads*)InstanceManager::getDefault("CarLoads"))->getMaxNameLength());
  } else if (attribute==(Setup::HAZARDOUS)) {
      return (car->isHazardous() ? " " + Setup::getHazardousMsg() : padAndTruncateString("", Setup
              ::getHazardousMsg().length() + 1));
  } else if (attribute==(Setup::DROP_COMMENT)) {
      return " " + car->getDropComment();
  } else if (attribute==(Setup::PICKUP_COMMENT)) {
      return " " + car->getPickupComment();
  } else if (attribute==(Setup::KERNEL)) {
      return " " + padAndTruncateString(car->getKernelName(), carManager->getKernelMaxNameLength());
  } else if (attribute==(Setup::KERNEL_SIZE)) {
      if (car->getKernel() != NULL && car->getKernel()->isLead(car)) {
          return " " + padAndTruncateString(QString::number(car->getKernel()->getSize()), 2);
      } else {
          return "   "; // assumes that kernel size is 99 or less
      }
  }
  else if (attribute==(Setup::RWE))
  {
   if (car->getReturnWhenEmptyDestName()!=(Car::NONE)) {
       return " "
               + padAndTruncateString(TrainManifestHeaderText::getStringHeader_RWE() + " "
                       + splitString(car->getReturnWhenEmptyDestinationName()) + " ,"
                       + splitString(car->getReturnWhenEmptyDestTrackName()), locationManager
                       ->getMaxLocationAndTrackNameLength()
                       + TrainManifestHeaderText::getStringHeader_RWE().length() + 3);
   }
   return "";
  }
  else if (attribute==(Setup::FINAL_DEST))
  {
   if (car->getFinalDestinationName()!=(Car::NONE))
   {
    return Setup::isPrintHeadersEnabled() ? " "
            + padAndTruncateString(splitString(car->getFinalDestinationName()), locationManager
                    ->getMaxLocationNameLength()) : " "
            + padAndTruncateString(TrainManifestText::getStringFinalDestination() + " "
                    + splitString(car->getFinalDestinationName()), locationManager
                    ->getMaxLocationNameLength()
                    + TrainManifestText::getStringFinalDestination().length() + 1);
   }
   return "";
  }
  else if (attribute==(Setup::FINAL_DEST_TRACK))
  {
   if (car->getFinalDestinationName()!=(Car::NONE))
   {
    return Setup::isPrintHeadersEnabled() ? " "
            + padAndTruncateString(splitString(car->getFinalDestinationName()) + ", "
                    + splitString(car->getFinalDestinationTrackName()), locationManager
                    ->getMaxLocationAndTrackNameLength() + 2) : " "
            + padAndTruncateString(TrainManifestText::getStringFinalDestination() + " "
                    + splitString(car->getFinalDestinationName()) + ", "
                    + splitString(car->getFinalDestinationTrackName()), locationManager
                    ->getMaxLocationAndTrackNameLength()
                    + TrainManifestText::getStringFinalDestination().length() + 3);
   }
   return "";
  }
  return getRollingStockAttribute(car, attribute, isPickup, isLocal);
 }

 /*private*/ QString TrainCommon::getRollingStockAttribute(RollingStock* rs, QString attribute, bool isPickup, bool isLocal)
 {
  if (attribute==(Setup::NUMBER)) {
      return " " + padAndTruncateString(splitString(rs->getNumber()), Control::max_len_string_print_road_number);
  } else if (attribute==(Setup::ROAD)) {
      QStringList road = rs->getRoadName().split("-"); // second half of string can be anything
      return " " + padAndTruncateString(road[0], ((CarRoads*)InstanceManager::getDefault("CarRoads"))->getMaxNameLength());
  } else if (attribute==(Setup::TYPE)) {
      QStringList type = rs->getTypeName().split("-"); // second half of string can be anything
      return " " + padAndTruncateString(type[0], ((CarTypes*)InstanceManager::getDefault("CarTypes"))->getMaxNameLength());
  } else if (attribute==(Setup::LENGTH)) {
      return " " + padAndTruncateString(rs->getLength() + LENGTHABV, ((CarLengths*)InstanceManager::getDefault("CarLengths"))->getMaxNameLength());
  }

  else if (attribute==(Setup::COLOR)) {
      return " " + padAndTruncateString(rs->getColor(), ((CarColors*)InstanceManager::getDefault("CarColors"))->getMaxNameLength());
  }
  else if (((attribute==(Setup::LOCATION)) && (isPickup || isLocal))
          || (attribute==(Setup::TRACK) && isPickup))
  {
   if (rs->getTrack() != NULL)
   {
    return Setup::isPrintHeadersEnabled() ? " "
            + padAndTruncateString(splitString(rs->getTrackName()), locationManager->getMaxTrackNameLength())
            : " "
                    + padAndTruncateString(TrainManifestText::getStringFrom() + " "
                            + splitString(rs->getTrackName()), TrainManifestText::getStringFrom().length()
                            + locationManager->getMaxTrackNameLength() + 1);
   }
   return "";
  }
  else if (attribute==(Setup::LOCATION) && !isPickup && !isLocal)
  {
   return Setup::isPrintHeadersEnabled() ? " "
           + padAndTruncateString(splitString(rs->getLocationName()), locationManager
                   ->getMaxLocationNameLength())
           : " "
                   + padAndTruncateString(TrainManifestText::getStringFrom() + " "
                           + splitString(rs->getLocationName()), locationManager->getMaxLocationNameLength()
                           + TrainManifestText::getStringFrom().length() + 1);
  }
  else if (attribute==(Setup::DESTINATION) && isPickup)
  {
   if (rs->getDestination() == NULL)
       return "";
   if (Setup::isPrintHeadersEnabled())
   {
    return " "
            + padAndTruncateString(splitString(rs->getDestinationName()), locationManager
                    ->getMaxLocationNameLength());
   }
   if (Setup::isTabEnabled())
   {
    return " "
            + padAndTruncateString(TrainManifestText::getStringDest() + " "
                    + splitString(rs->getDestinationName()), TrainManifestText::getStringDest().length()
                    + locationManager->getMaxLocationNameLength() + 1);
   }
   else
   {
    return " " + TrainManifestText::getStringDestination() + " " + splitString(rs->getDestinationName());
   }
  }
  else if ((attribute==(Setup::DESTINATION) || attribute==(Setup::TRACK)) && !isPickup)
  {
   return Setup::isPrintHeadersEnabled() ? " "
           + padAndTruncateString(splitString(rs->getDestinationTrackName()), locationManager
                   ->getMaxTrackNameLength()) : " "
           + padAndTruncateString(TrainManifestText::getStringTo() + " "
                   + splitString(rs->getDestinationTrackName()), locationManager->getMaxTrackNameLength()
                   + TrainManifestText::getStringTo().length() + 1);
  }
  else if (attribute==(Setup::DEST_TRACK))
  {
   return Setup::isPrintHeadersEnabled() ? " "
           + padAndTruncateString(splitString(rs->getDestinationName()) + ", "
                   + splitString(rs->getDestinationTrackName()), locationManager
                   ->getMaxLocationAndTrackNameLength() + 2) : " "
           + padAndTruncateString(TrainManifestText::getStringDest() + " "
                   + splitString(rs->getDestinationName()) + ", " + splitString(rs->getDestinationTrackName()),
                   locationManager->getMaxLocationAndTrackNameLength()
                           + TrainManifestText::getStringDest().length() + 3);
  }
  else if (attribute==(Setup::OWNER))
  {
      return " " + padAndTruncateString(rs->getOwner(), ((CarOwners*)InstanceManager::getDefault("CarOwners"))->getMaxNameLength());
  }
  else if (attribute==(Setup::COMMENT))
  {
      return " " + rs->getComment();
  }
  else if (attribute==(Setup::BLANK))
  {
      return "";
  } // the three utility attributes that don't get printed but need to be tabbed out
  else if (attribute==(Setup::NO_NUMBER))
  {
      return " "
              + padAndTruncateString("", Control::max_len_string_print_road_number
                      - (UTILITY_CAR_COUNT_FIELD_SIZE + 1));
  } else if (attribute==(Setup::NO_ROAD)) {
      return " " + padAndTruncateString("", ((CarRoads*)InstanceManager::getDefault("CarRoads"))->getMaxNameLength());
  } else if (attribute==(Setup::NO_COLOR)) {
      return " " + padAndTruncateString("", ((CarColors*)InstanceManager::getDefault("CarColors"))->getMaxNameLength());
  } // there are four truncated manifest attributes
  else if (attribute==(Setup::NO_DEST_TRACK))
  {
      return Setup::isPrintHeadersEnabled() ? padAndTruncateString("", locationManager
              ->getMaxLocationAndTrackNameLength() + 2) : "";
  }
  else if ((attribute==(Setup::NO_LOCATION) && !isPickup)
          || (attribute==(Setup::NO_DESTINATION) && isPickup)) {
      return Setup::isPrintHeadersEnabled() ? padAndTruncateString("",
              locationManager->getMaxLocationNameLength() + 1) : "";
  }
  else if (attribute==(Setup::NO_TRACK) || attribute==(Setup::NO_LOCATION)
          || attribute==(Setup::NO_DESTINATION)) {
      return Setup::isPrintHeadersEnabled() ? padAndTruncateString("", locationManager->getMaxTrackNameLength() + 1)
              : "";
  }
  else if (attribute==(Setup::TAB))
  {
      return tabString("", Setup::getTab1Length());
  }
  else if (attribute==(Setup::TAB2))
  {
      return tabString("", Setup::getTab2Length());
  }
  else if (attribute==(Setup::TAB3)) {
      return tabString("", Setup::getTab3Length());
  }
  return tr("Error attribute (%1) not found.").arg(attribute); // something
  // isn't
  // right!
 }

 /**
  * Two column header format. Left side pick ups, right side set outs
  *
  * @param file
  * @param isManifest
  */
 /*public*/ void TrainCommon::printEngineHeader(PrintWriter* file, bool isManifest) {
     int lineLength = getLineLength(isManifest);
     printHorizontalLine(file, 0, lineLength);
     if (!Setup::isPrintHeadersEnabled()) {
         return;
     }
     QString s = padAndTruncateString(getPickupEngineHeader(), lineLength / 2, true);
     s = padAndTruncateString(s + VERTICAL_LINE_CHAR + getDropEngineHeader(), lineLength, true);
     addLine(file, s);
     printHorizontalLine(file, 0, lineLength);
 }

 /*public*/ void TrainCommon::printPickupEngineHeader(PrintWriter* file, bool isManifest) {
     int lineLength = getLineLength(isManifest);
     printHorizontalLine(file, 0, lineLength);
     QString s = padAndTruncateString(tabString("", Setup::getManifestPrefixLength() + 1, true)
             + getPickupEngineHeader(), lineLength, true);
     addLine(file, s);
     printHorizontalLine(file, 0, lineLength);
 }

 /*public*/ void TrainCommon::printDropEngineHeader(PrintWriter* file, bool isManifest) {
     int lineLength = getLineLength(isManifest);
     printHorizontalLine(file, 0, lineLength);
     QString s = padAndTruncateString(tabString("", Setup::getManifestPrefixLength() + 1, true)
             + getDropEngineHeader(), lineLength, true);
     addLine(file, s);
     printHorizontalLine(file, 0, lineLength);
 }

 /**
  * Prints the two column header for cars. Left side pick ups, right side set
  * outs.
  *
  * @param file
  * @param isManifest
  */
 /*public*/ void TrainCommon::printCarHeader(PrintWriter* file, bool isManifest, bool isTwoColumnTrack) {
     int lineLength = getLineLength(isManifest);
     printHorizontalLine(file, 0, lineLength);
     if (!Setup::isPrintHeadersEnabled()) {
         return;
     }
     // center pick up and set out text
     QString s = padAndTruncateString(tabString(Setup::getPickupCarPrefix(), lineLength / 4
             - Setup::getPickupCarPrefix().length() / 2, true), lineLength / 2, true)
             + VERTICAL_LINE_CHAR
             + tabString(Setup::getDropCarPrefix(), lineLength / 4 - Setup::getDropCarPrefix().length() / 2, true);
     s = padAndTruncateString(s, lineLength, true);
     addLine(file, s);
     printHorizontalLine(file, 0, lineLength);

     s = padAndTruncateString(getPickupCarHeader(isManifest, isTwoColumnTrack), lineLength / 2, true);
     s = padAndTruncateString(s + VERTICAL_LINE_CHAR + getDropCarHeader(isManifest, isTwoColumnTrack), lineLength,
             true);
     addLine(file, s);
     printHorizontalLine(file, 0, lineLength);
 }

 /*public*/ void TrainCommon::printPickupCarHeader(PrintWriter* file, bool isManifest, bool isTwoColumnTrack) {
     if (!Setup::isPrintHeadersEnabled()) {
         return;
     }
     printHorizontalLine(file, isManifest);
     QString s = padAndTruncateString(tabString("", Setup::getManifestPrefixLength() + 1, true)
             + getPickupCarHeader(isManifest, isTwoColumnTrack), getLineLength(isManifest), true);
     addLine(file, s);
     printHorizontalLine(file, isManifest);
 }

 /*public*/ void TrainCommon::printDropCarHeader(PrintWriter* file, bool isManifest, bool isTwoColumnTrack) {
     if (!Setup::isPrintHeadersEnabled()) {
         return;
     }
     printHorizontalLine(file, isManifest);
     QString s = padAndTruncateString(tabString("", Setup::getManifestPrefixLength() + 1, true)
             + getDropCarHeader(isManifest, isTwoColumnTrack), getLineLength(isManifest), true);
     addLine(file, s);
     printHorizontalLine(file, isManifest);
 }

 /*public*/ void TrainCommon::printLocalCarMoveHeader(PrintWriter* file, bool isManifest) {
     if (!Setup::isPrintHeadersEnabled()) {
         return;
     }
     printHorizontalLine(file, isManifest);
     QString s = padAndTruncateString(tabString("", Setup::getManifestPrefixLength() + 1, true)
             + getLocalMoveHeader(isManifest), getLineLength(isManifest), true);
     addLine(file, s);
     printHorizontalLine(file, isManifest);
 }

 /*public*/ QString TrainCommon::getPickupEngineHeader() {
     return getHeader(Setup::getPickupEngineMessageFormat(), PICKUP, !LOCAL, ENGINE);
 }

 /*public*/ QString TrainCommon::getDropEngineHeader() {
     return getHeader(Setup::getDropEngineMessageFormat(), !PICKUP, !LOCAL, ENGINE);
 }

 /*public*/ QString TrainCommon::getPickupCarHeader(bool isManifest, bool isTwoColumnTrack) {
     if (isManifest && !isTwoColumnTrack) {
         return getHeader(Setup::getPickupManifestMessageFormat(), PICKUP, !LOCAL, !ENGINE);
     } else if (!isManifest && !isTwoColumnTrack) {
         return getHeader(Setup::getPickupSwitchListMessageFormat(), PICKUP, !LOCAL, !ENGINE);
     } else if (isManifest && isTwoColumnTrack) {
         return getHeader(Setup::getPickupTwoColumnByTrackManifestMessageFormat(), PICKUP, !LOCAL, !ENGINE);
     } else {
         return getHeader(Setup::getPickupTwoColumnByTrackSwitchListMessageFormat(), PICKUP, !LOCAL, !ENGINE);
     }
 }

 /*public*/ QString TrainCommon::getDropCarHeader(bool isManifest, bool isTwoColumnTrack) {
     if (isManifest && !isTwoColumnTrack) {
         return getHeader(Setup::getDropManifestMessageFormat(), !PICKUP, !LOCAL, !ENGINE);
     } else if (!isManifest && !isTwoColumnTrack) {
         return getHeader(Setup::getDropSwitchListMessageFormat(), !PICKUP, !LOCAL, !ENGINE);
     } else if (isManifest && isTwoColumnTrack) {
         return getHeader(Setup::getDropTwoColumnByTrackManifestMessageFormat(), !PICKUP, !LOCAL, !ENGINE);
     } else {
         return getHeader(Setup::getDropTwoColumnByTrackSwitchListMessageFormat(), !PICKUP, !LOCAL, !ENGINE);
     }
 }

 /*public*/ QString TrainCommon::getLocalMoveHeader(bool isManifest) {
     if (isManifest) {
         return getHeader(Setup::getLocalManifestMessageFormat(), !PICKUP, LOCAL, !ENGINE);
     } else {
         return getHeader(Setup::getLocalSwitchListMessageFormat(), !PICKUP, LOCAL, !ENGINE);
     }
 }

 /*private*/ QString TrainCommon::getHeader(QStringList format, bool isPickup, bool isLocal, bool isEngine)
 {
  QString buf = ""; //QString();

  foreach (QString attribute, format)
  {
   if(attribute.isEmpty())
    continue;
   if (attribute==(Setup::BLANK)) {
       continue;
   }
   if (attribute==(Setup::ROAD)) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Road(), ((CarRoads*)InstanceManager::getDefault("CarRoads"))
               ->getMaxNameLength())
               + " ");
   } else if (attribute==(Setup::NUMBER) && !isEngine) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Number(),
               Control::max_len_string_print_road_number)
               + " ");
   } else if (attribute==(Setup::NUMBER) && isEngine) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_EngineNumber(),
               Control::max_len_string_print_road_number)
               + " ");
   } else if (attribute==(Setup::TYPE)) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Type(), ((CarTypes*)InstanceManager::getDefault("CarTypes"))
               ->getMaxNameLength())
               + " ");
   } else if (attribute==(Setup::MODEL)) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Model(),
                                       ((EngineModels*)InstanceManager::getDefault("EngineModels"))->getMaxNameLength())
               + " ");
   } else if (attribute==(Setup::CONSIST)) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Consist(), engineManager
               ->getConsistMaxNameLength())
               + " ");
   } else if (attribute==(Setup::KERNEL)) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Kernel(), carManager
               ->getKernelMaxNameLength())
               + " ");
   } else if (attribute==(Setup::KERNEL_SIZE)) {
       buf.append("   "); // assume kernel size is 99 or less
   } else if (attribute==(Setup::LOAD)) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Load(), ((CarLoads*)InstanceManager::getDefault("CarLoads"))
               ->getMaxNameLength())
               + " ");
   } else if (attribute==(Setup::COLOR)) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Color(), ((CarColors*)InstanceManager::getDefault("CarColors"))
               ->getMaxNameLength())
               + " ");
   } else if (attribute==(Setup::OWNER)) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Owner(), ((CarOwners*)InstanceManager::getDefault("CarOwners"))
               ->getMaxNameLength())
               + " ");
   } else if (attribute==(Setup::LENGTH)) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Length(),
               Control::max_len_string_length_name)
               + " ");
   } else if (attribute==(Setup::TRACK)) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Track(), locationManager
               ->getMaxTrackNameLength())
               + " ");
   } else if (attribute==(Setup::LOCATION) && (isPickup || isLocal)) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Location(), locationManager
               ->getMaxTrackNameLength())
               + " ");
   } else if (attribute==(Setup::LOCATION) && !isPickup) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Location(), locationManager
               ->getMaxLocationNameLength())
               + " ");
   } else if (attribute==(Setup::DESTINATION) && !isPickup) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Destination(), locationManager
               ->getMaxTrackNameLength())
               + " ");
   } else if (attribute==(Setup::DESTINATION) && isPickup) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Destination(), locationManager
               ->getMaxLocationNameLength())
               + " ");
   } else if (attribute==(Setup::DEST_TRACK)) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Dest_Track(), locationManager
               ->getMaxLocationAndTrackNameLength() + 2)
               + " ");
   } else if (attribute==(Setup::FINAL_DEST)) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Final_Dest(), locationManager
               ->getMaxLocationNameLength())
               + " ");
   } else if (attribute==(Setup::FINAL_DEST_TRACK)) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Final_Dest_Track(),
               locationManager->getMaxLocationAndTrackNameLength() + 2)
               + " ");
   } else if (attribute==(Setup::HAZARDOUS)) {
       buf.append(padAndTruncateString(TrainManifestHeaderText::getStringHeader_Hazardous(), Setup
               ::getHazardousMsg().length())
               + " ");
   } else if (attribute==(Setup::RWE)) {
       buf.append(TrainManifestHeaderText::getStringHeader_RWE() + " ");
   } else if (attribute==(Setup::COMMENT)) {
       buf.append(TrainManifestHeaderText::getStringHeader_Comment() + " ");
   } else if (attribute==(Setup::TAB)) {
       buf.append(tabString("", Setup::getTab1Length()));
   } else if (attribute==(Setup::TAB2)) {
       buf.append(tabString("", Setup::getTab2Length()));
   } else if (attribute==(Setup::TAB3)) {
       buf.append(tabString("", Setup::getTab3Length()));
   } else {
       buf.append(attribute + " ");
   }
  }
  return buf/*.toString()*/;
 }

 /*protected*/ void TrainCommon::printTrackNameHeader(PrintWriter* file, QString trackName, bool isManifest) {
     printHorizontalLine(file, isManifest);
     int lineLength = getLineLength(isManifest);
     QString s = padAndTruncateString(tabString(trackName.trimmed(), lineLength / 4 - trackName.trimmed().length() / 2,
             true), lineLength / 2, true)
             + VERTICAL_LINE_CHAR
             + tabString(trackName.trimmed(), lineLength / 4 - trackName.trimmed().length() / 2, true);
     s = padAndTruncateString(s, lineLength, true);
     addLine(file, s);
     printHorizontalLine(file, isManifest);
 }

 /**
  * Prints a line across the entire page.
  *
  * @param file
  */
 /*public*/ void TrainCommon::printHorizontalLine(PrintWriter* file, bool isManifest) {
     printHorizontalLine(file, 0, getLineLength(isManifest));
 }

 /*public*/ void TrainCommon::printHorizontalLine(PrintWriter* file, int start, int end) {
     QString sb = ""; //QString();
     while (start-- > 0) {
         sb.append(SPACE);
     }
     while (end-- > 0) {
         sb.append(HORIZONTAL_LINE_CHAR);
     }
     addLine(file, sb/*.toString()*/);
 }

 /*public*/ /*static*/ QString TrainCommon::getISO8601Date(bool isModelYear) {
     Calendar* calendar = Calendar::getInstance();
     // use the JMRI timebase (which may be a fast clock).
     calendar->setTime(((Timebase*)InstanceManager::getDefault("Timebase"))->getTime());
     if (isModelYear && !Setup::getYearModeled().isEmpty()) {
         try {
       bool bok;
             calendar->set(Calendar::YEAR, (Setup::getYearModeled().trimmed()).toInt(&bok));
             if(!bok) throw NumberFormatException();
         } catch (NumberFormatException* e) {
             return Setup::getYearModeled();
         }
     }
     //return (new ISO8601DateFormat()).format(calendar.getTime());
     return calendar->getTime().toString(Qt::ISODate);
 }

/*public*/ /*static*/ QString TrainCommon::getDate(QDateTime date) {
#if 1
  Calendar* calendar = Calendar::getInstance();
  calendar->setTime(date);

  QString year = QString::number(calendar->get(Calendar::YEAR));
  year = year.trimmed();

  // Use 24 hour clock
  int hour = calendar->get(Calendar::HOUR_OF_DAY);

  if (Setup::is12hrFormatEnabled()) {
      hour = calendar->get(Calendar::HOUR);
      if (hour == 0) {
          hour = 12;
      }
  }

  QString h = QString::number(hour);
  if (hour < 10) {
      h = "0" + QString::number(hour);
  }

  int minute = calendar->get(Calendar::MINUTE);
  QString m = QString::number(minute);
  if (minute < 10) {
      m = "0" + QString::number(minute);
  }

  // AM_PM field
  QString AM_PM = "";
  if (Setup::is12hrFormatEnabled()) {
      AM_PM = (calendar->get(Calendar::AM_PM) == Calendar::AM) ? tr("AM") : tr("PM");
  }

  // Java 1.6 methods calendar.getDisplayName(Calendar.MONTH,
  // Calendar.LONG, Locale.getDefault()
  // Java 1.6 methods calendar.getDisplayName(Calendar.AM_PM,
  // Calendar.LONG, Locale.getDefault())
  return QString::number(calendar->get(Calendar::MONTH) + 1) + "/" + QString::number(calendar->get(Calendar::DAY_OF_MONTH)) + "/" + year + " " + h
          + ":" + m + " " + AM_PM;
#endif
}

/*public*/ /*static*/ QString TrainCommon::getDate(bool isModelYear) {
#if 0
  Calendar calendar = Calendar.getInstance();
  // use the JMRI timebase (which may be a fast clock).
  calendar.setTime(jmri.InstanceManager.timebaseinstance()->getTime());
  if (isModelYear && !Setup::getYearModeled()==(Setup::NONE)) {
      try {
          calendar.set(Calendar.YEAR, Integer.parseInt(Setup::getYearModeled().trimmed()));
      } catch (NumberFormatException* e) {
          return Setup::getYearModeled();
      }
  }
  return TrainCommon.getDate(calendar.getTime());
#else
  return "";
#endif
}
#if 0
 /**
  * Returns a double in minutes representing the string date. Date string has
  * to be in the order: Month / day / year hour:minute AM_PM
  *
  * @param date
  * @return double in minutes
  * @deprecated. Use date object comparisons instead.
  */
 @Deprecated
 /*public*/ double convertStringDateToDouble(String date) {
     double dateToDouble = 0;
     try {
         // log->debug("Convert date: " + date);
         QStringList breakdownDate = date.split("/");
         // log->debug("Month: " + breakdownDate[0]);
         // convert month to minutes
         dateToDouble += 60 * 24 * 31 * Integer.parseInt(breakdownDate[0]);
         // log->debug("Day: " + breakdownDate[1]);
         dateToDouble += 60 * 24 * Integer.parseInt(breakdownDate[1]);
         QStringList breakDownYear = breakdownDate[2].split(" ");
         // log->debug("Year: " + breakDownYear[0]);
         dateToDouble += 60 * 24 * 365 * Integer.parseInt(breakDownYear[0]);
         QStringList breakDownTime = breakDownYear[1].split(":");
         // log->debug("Hour: " + breakDownTime[0]);
         dateToDouble += 60 * Integer.parseInt(breakDownTime[0]);
         // log->debug("Minute: " + breakDownTime[1]);
         dateToDouble += Integer.parseInt(breakDownTime[1]);
         if (breakDownYear.length > 2) {
             log->debug("AM_PM: " + breakDownYear[2]);
             if (breakDownYear[2]==(Bundle.getMessage("PM"))) {
                 dateToDouble += 60 * 12;
             }
         }
     } catch (NumberFormatException* e) {
         log->error("Not able to convert date: " + date + " to double");
     }
     // log->debug("Double: "+dateToDouble);
     return dateToDouble;
 }
#endif
 /**
  * Will pad out a string by adding spaces to the end of the string, and will
  * remove characters from the end of the string if the string exceeds the
  * field size.
  *
  * @param s
  * @param fieldSize
  * @return A String the specified length
  */
 /*public*/ /*static*/ QString TrainCommon::padAndTruncateString(QString s, int fieldSize) {
     return padAndTruncateString(s, fieldSize, Setup::isTabEnabled());
 }

 /*public*/ /*static*/ QString TrainCommon::padAndTruncateString(QString s, int fieldSize, bool enabled) {
     if (!enabled) {
         return s;
     }
     s = padString(s, fieldSize);
     if (s.length() > fieldSize) {
         s = s.mid(0, fieldSize);
     }
     return s;
 }

 /**
  * Adjusts string to be a certain number of characters by adding spaces to
  * the end of the string.
  *
  * @param s
  * @param fieldSize
  * @return A String the specified length
  */
 /*public*/ /*static*/ QString TrainCommon::padString(QString s, int fieldSize) {
     QString buf = ""; //QString(s);
     while (buf.length() < fieldSize) {
         buf.append(" ");
     }
     return buf/*.toString()*/;
 }

 /**
  * Adds the requested number of spaces to the start of the string.
  *
  * @param s
  * @param tabSize
  * @return A String the specified length
  */
 /*public*/ /*static*/ QString TrainCommon::tabString(QString s, int tabSize) {
     return tabString(s, tabSize, Setup::isTabEnabled());
 }

 /*public*/ /*static*/ QString TrainCommon::tabString(QString s, int tabSize, bool enabled) {
     if (!enabled) {
         return s;
     }
     QString buf = ""; //QString();
     while (buf.length() < tabSize) {
         buf.append(" ");
     }
     buf.append(s);
     return buf/*.toString()*/;
 }

 /*protected*/ int TrainCommon::getLineLength(bool isManifest) {
     return getLineLength(isManifest ? Setup::getManifestOrientation() : Setup::getSwitchListOrientation(), Setup
             ::getManifestFontSize(), Setup::getFontName());
 }

 /*private*/ /*static*/ int TrainCommon::getLineLength(QString orientation, int fontSize, QString fontName) {
     // Metrics don't always work for the various font names, so use
     // Monospaced
     QFont font =  QFont(fontName, fontSize); //Font(fontName, Font.PLAIN, fontSize); // NOI18N
     QLabel* label = new QLabel();
     QFontMetrics metrics = label->fontMetrics();
     int charwidth = metrics.charWidth("m", 0);
     if (charwidth == 0) {
         Logger::error(tr("Line length charater width equal to zero. font size: %1, fontName: %2").arg(fontSize).arg(fontName));
         charwidth = fontSize / 2; // create a reasonable character width
     }
     // compute lines and columns within margins
     return getPageSize(orientation).width() / charwidth;
 }

 /*private*/ bool TrainCommon::checkStringLength(QString string, bool isManifest)
 {
  return checkStringLength(string,
   isManifest ? Setup::getManifestOrientation() : Setup::getSwitchListOrientation(), Setup::getFontName(),
   Setup::getManifestFontSize());
 }

 /**
  * Checks to see if the the string fits on the page.
  *
  * @param string
  * @param orientation
  * @param fontName
  * @param fontSize
  * @return false if string length is longer than page width.
  */
 /*private*/ bool TrainCommon::checkStringLength(QString string, QString orientation, QString fontName, int fontSize)
 {
     QFont font = QFont(fontName, fontSize); //new Font(fontName, Font.PLAIN, fontSize); // NOI18N
     QLabel* label = new QLabel();
     QFontMetrics metrics = label->fontMetrics();
     int stringWidth = metrics.width(string); // .stringWidth(string);
     return stringWidth <= getPageSize(orientation).width();
 }

 /*private*/ /*static*/ QSize TrainCommon::getPageSize(QString orientation) {
     // page size has been adjusted to account for margins of .5
     QSize pagesize = QSize(523, 720); // Portrait 8.5 x 11
     // landscape has a .65 margins
     if (orientation==(Setup::LANDSCAPE)) {
         pagesize = QSize(702, 523);
     }
     if (orientation==(Setup::HALFPAGE)) // 4.5 x 11
     {
         pagesize = QSize(261, 720);
     }
     if (orientation==(Setup::HANDHELD)) {
         pagesize = QSize(206, 720);
     }
     return pagesize;
 }
 /**
  * Produces a string using commas and spaces between the strings provided in
  * the array. Does not check for embedded commas in the string array.
  *
  * @param array
  * @return formated string using commas and spaces
  */
 /*public*/ /*static*/ QString TrainCommon::formatStringToCommaSeparated(QStringList array) {
     QString sbuf = ""; //QString("");
     foreach (QString s, array) {
         if (s != NULL) {
             sbuf = sbuf.append(s + ", ");
         }
     }
     if (sbuf.length() > 2) {
         //sbuf.setLength(sbuf.length() - 2); // remove trailing separators
      sbuf = sbuf.mid(0, sbuf.length()-2);
     }
     return sbuf/*.toString()*/;
 }
 /**
  * Adds HTML like color text control characters around a string. Note that
  * black is the standard text color, and if black is requested no control
  * characters are added.
  *
  * @param text  the text to be modified
  * @param color the color the text is to be printed
  * @return formated text with color modifiers
  */
 /*public*/ /*static*/ QString TrainCommon::formatColorString(QString text, QColor color) {
     QString s = text;
     if (color!= QColor(Qt::black)) {
         s = TEXT_COLOR_START + ColorUtil::colorToColorName(color) + "\">" + text + TEXT_COLOR_END;
     }
     return s;
 }

 /**
  * Removes the color text control characters around the desired string
  *
  * @param string the string with control characters
  * @return pure text
  */
 /*public*/ /*static*/ QString TrainCommon::getTextColorString(QString string) {
     QString text = string;
     if (string.contains(TEXT_COLOR_START)) {
         text = string.mid(0, string.indexOf(TEXT_COLOR_START)) + string.mid(string.indexOf(">") + 1);
     }
     if (text.contains(TEXT_COLOR_END)) {
         text = text.mid(0, text.indexOf(TEXT_COLOR_END)) +
                 string.mid(string.indexOf(TEXT_COLOR_END) + TEXT_COLOR_END.length());
     }
     return text;
 }

 /*public*/ /*static*/ QColor TrainCommon::getTextColor(QString string) {
     QColor color = QColor(Qt::black);
     if (string.contains(TEXT_COLOR_START)) {
         QString c = string.mid(string.indexOf("\"") + 1);
         c = c.mid(0, c.indexOf("\""));
         color = ColorUtil::stringToColor(c);
     }
     return color;
 }
}
