#include "importcars.h"
#include "carmanager.h"
#include "file.h"
#include <QTextStream>
#include <QFile>
#include "logger.h"
#include "control.h"
#include "cartypes.h"
#include "car.h"
#include "carroads.h"
#include "cartypes.h"
#include "carcolors.h"
#include "carowners.h"
#include "location.h"
#include "track.h"
#include "locationmanager.h"
#include "kernel.h"
#include <QLabel>
#include "carloads.h"
#include <QMessageBox>
#include <QApplication>
#include "location.h"
#include "track.h"
#include "setup.h"
#include "kernel.h"
#include "carlengths.h"
#include "rollingstock.h"
#include "car.h"
#include "jmrijframe.h"
#include "instancemanager.h"

namespace Operations
{
 /**
  * This routine will import cars into the operation database.
  *
  * Each field is space or comma delimited. Field order: Number Road Type Length
  * Weight Color Owner Built Location - Track:: If a CSV file, the import will
  * accept these additional fields: Load Kernel Moves Value Comment Miscellaneous
  * Extensions
  *
  * @author Dan Boudreau Copyright (C) 2008 2010 2011, 2013, 2016
  * @version $Revision$
  */
 ///*public*/ class ImportCars extends ImportRollingStock {



 /*private*/ static /*final*/ QString LOCATION_TRACK_SEPARATOR = "-";

 ImportCars::ImportCars() : ImportRollingStock()
 {
  log = new Logger("ImportCars");
  manager = ((CarManager*)InstanceManager::getDefault("CarManager"));

  weightResults = QMessageBox::No; // Automatically calculate weight for car if weight entry is not
  // found
  autoCalculate = true;
  askAutoCreateTypes = true;
  askAutoCreateLocations = true;
  askAutoCreateTracks = true;
  askAutoLocationType = true;
  askAutoIncreaseTrackLength = true;
  askAutoForceCar = true;

  autoCreateTypes = false;
  autoCreateLocations = false;
  autoCreateTracks = false;
  autoAdjustLocationType = false;
  autoAdjustTrackLength = false;
  autoForceCar = false;

  autoCreateRoads = true;
  autoCreateLengths = true;
  autoCreateColors = true;
  autoCreateOwners = true;

 }



 // we use a thread so the status frame will work!
 //@Override
 /*public*/ void ImportCars::process()
 {
  File* file = getFile();
  if (file == NULL)
  {
   return;
  }
  QFile* qFile = new QFile(file->getPath());
  if(!qFile->open(QIODevice::ReadOnly))
   return;

  QTextStream* in = new QTextStream(qFile);
  if (in == NULL)
  {
      return;
  }

  createStatusFrame(tr("Import Cars"));

  // Now read the input file
  bool importOkay = false;
  bool comma = false;
  bool importKernel = false;
  int lineNum = 0;
  int carsAdded = 0;
  QString line = " ";
  QString carNumber;
  QString carRoad;
  QString carType;
  QString carLength;
  QString carWeight;
  QString carColor = "";
  QString carOwner = "";
  QString carBuilt = "";
  QString carLocation = "";
  QString carTrack = "";
  QString carLoad = "";
  QString carKernel = "";
  int carMoves = 0;
  QString carValue = "";
  QString carComment = "";
  QStringList inputLine;

  // does the file name end with .csv?
  if (file->getAbsolutePath().endsWith(".csv"))
  { // NOI18N
      log->info("Using comma as delimiter for import cars");
      comma = true;
  }
#if 1
  while (true)
  {
   lineNumber->setText(tr("LineNumber") + " " + QString::number(++lineNum));
   try {
       line = in->readLine();
   } catch (IOException* e) {
       break;
   }

   if (line == NULL) {
       importOkay = true;
       break;
   }

         // has user canceled import?
//            if (!fstatus.isShowing()) {
//                break;
//            }

   line = line.trimmed();
   if (log->isDebugEnabled())
   {
       log->debug(tr("Import: %1").arg(line));
   }
   importLine->setText(line);

   if (line.startsWith(tr("Number")))
   {
       continue; // skip header
   }
   if (line.compare("kernel", Qt::CaseInsensitive))
   { // NOI18N
       log->info("Importing kernel names");
       importKernel = true;
       continue;
   }
   if (line.compare("comma", Qt::CaseInsensitive))
   { // NOI18N
       log->info("Using comma as delimiter for import cars");
       comma = true;
       continue;
   }
   // use comma as delimiter if found otherwise use spaces
   if (comma)
   {
       inputLine = parseCommaLine(line, MAXIMUM_NUMBER_FIELDS);
   }
   else
   {
    inputLine = line.split(QRegExp("\\s+")); // NOI18N
   }
   if (inputLine.length() < 1 || line==(""))
   {
       log->debug("Skipping blank line");
       continue;
   }
   int base = 1;
   if (comma || inputLine[0]!=(""))
   {
       base--; // skip over any spaces at start of line
   }

   // The minimum import is car number, road, type and length
   if (inputLine.length() > base + 3)
   {
    carNumber = inputLine[base + CAR_NUMBER];
    carRoad = inputLine[base + CAR_ROAD];
    carType = inputLine[base + CAR_TYPE];
    carLength = inputLine[base + CAR_LENGTH];
    carWeight = "0";
    carColor = "";
    carOwner = "";
    carBuilt = "";
    carLocation = "";
    carTrack = "";
    carLoad = ((CarLoads*)InstanceManager::getDefault("CarLoads"))->getDefaultEmptyName();
    carKernel = "";
    carMoves = 0;
    carValue = "";
    carComment = "";

    if (inputLine.length() > base + CAR_WEIGHT)
    {
        carWeight = inputLine[base + CAR_WEIGHT];
    }
    if (inputLine.length() > base + CAR_COLOR)
    {
        carColor = inputLine[base + CAR_COLOR];
    }

    log->debug(tr("Checking car number (%1) road (%2) type (%3) length (%4) weight (%5) color (%6)").arg(carNumber).arg(
            carRoad).arg(carType).arg(carLength).arg(carWeight).arg(carColor)); // NOI18N
    if (carNumber.length() > Control::max_len_string_road_number)
    {
//                    JOptionPane.showMessageDialog(NULL, MessageFormat.format(tr("CarRoadNumberTooLong"),
//                            new Object[]{(carRoad + " " + carNumber), carNumber}), MessageFormat.format(Bundle
//                            .getMessage("carRoadNum"), new Object[]{Control::max_len_string_road_number + 1}),
//                            JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(NULL, tr("Car road number must be less than %1 characters").arg(Control::max_len_string_road_number + 1), tr("Car (%1) road number (%2) too long!").arg(carRoad + " " + carNumber).arg(carNumber));
     break;
    }
    if (carRoad.length() > Control::max_len_string_attibute)
    {
//                    JOptionPane.showMessageDialog(NULL, MessageFormat.format(tr("CarRoadNameTooLong"),
//                            new Object[]{(carRoad + " " + carNumber), carRoad}), MessageFormat.format(Bundle
//                            .getMessage("carAttribute"), new Object[]{Control::max_len_string_attibute}),
//                            JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(NULL, tr("Car attribute must be %1 characters or less").arg("Control::max_len_string_attibute"), tr("Car (%1) road name (%2) too long!").arg(carRoad + " " + carNumber).arg(carRoad));
        break;
    }
    if (carType.length() > Control::max_len_string_attibute)
    {
//                    JOptionPane.showMessageDialog(NULL, MessageFormat.format(tr("CarTypeNameTooLong"),
//                            new Object[]{(carRoad + " " + carNumber), carType}), MessageFormat.format(Bundle
//                            .getMessage("carAttribute"), new Object[]{Control::max_len_string_attibute}),
//                            JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(NULL, tr("Car attribute must be %1 characters or less").arg("Control::max_len_string_attibute"), tr("Car (%1) type name (%2) too long!").arg(carRoad + " " + carNumber).arg(carRoad));
        break;
    }

    if (!((CarTypes*)InstanceManager::getDefault("CarTypes"))->containsName(carType))
    {
     if (autoCreateTypes)
     {
      log->debug(tr("Adding car type (%1)").arg(carType));
      ((CarTypes*)InstanceManager::getDefault("CarTypes"))->addName(carType);
     }
     else
     {
//      int results = JOptionPane.showConfirmDialog(NULL, tr("Car")
//              + " (" + carRoad + " " + carNumber + ")"
//              + NEW_LINE
//              + MessageFormat.format(tr("typeNameNotExist"),
//                      new Object[]{carType}), tr("carAddType"),
//              JOptionPane.YES_NO_CANCEL_OPTION);
      int results = QMessageBox::question(NULL, tr("Add car type?"), tr("Car")+ " (" + carRoad + " " + carNumber + ")" + NEW_LINE + tr("Type \"%1\" does not exist in your roster, add?").arg(carType), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
      if (results == QMessageBox::Yes)
      {
       ((CarTypes*)InstanceManager::getDefault("CarTypes"))->addName(carType);
       if (askAutoCreateTypes)
       {
//        results = JOptionPane.showConfirmDialog(NULL, Bundle
//                .getMessage("DoYouWantToAutoAddCarTypes"), tr("OnlyAskedOnce"),
//                JOptionPane.YES_NO_OPTION);
        results = QMessageBox::question(NULL, tr("This question is only asked once per import!"), tr("Do you want the program to automatically add new car types?"), QMessageBox::Yes | QMessageBox::No |QMessageBox::Cancel);
        if (results == QMessageBox::Yes)
        {
            autoCreateTypes = true;
        }
       }
       askAutoCreateTypes = false;
      }
      else if (results == QMessageBox::Cancel)
      {
       break;
      }
     }
    }
    if (carLength.length() > Control::max_len_string_length_name)
    {
//      JOptionPane.showMessageDialog(NULL, MessageFormat.format(tr("CarLengthNameTooLong"),
//              new Object[]{(carRoad + " " + carNumber), carLength}), MessageFormat.format(Bundle
//              .getMessage("carAttribute"), new Object[]{Control::max_len_string_length_name}),
//              JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(NULL, tr("Car attribute must be %1 characters or less").arg(Control::max_len_string_length_name), tr("Car (%1) length field (%2) too long!").arg(carRoad + " " + carNumber).arg(carLength));
      break;
    }
    if (carLength==(""))
    {
     log->debug(tr("Car (%1 %2) length not specified").arg(carRoad).arg(carNumber));
//     JOptionPane.showMessageDialog(NULL, MessageFormat.format(
//             tr("CarLengthNotSpecified"), new Object[]{(carRoad + " " + carNumber)}),
//             tr("CarLengthMissing"), JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(NULL, tr("Car length missing!"), tr("Car (%1) length missing").arg(carRoad + " " + carNumber));
     break;
    }
    bool ok;
    {
      carLength.toInt((&ok));
    }
    if(!ok)
    {
//      JOptionPane.showMessageDialog(NULL, MessageFormat.format(Bundle
//              .getMessage("CarLengthNameNotNumber"), new Object[]{(carRoad + " " + carNumber),
//              carLength}), tr("CarLengthMissing"), JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(NULL, tr("Car length missing!"), tr("Car (%1) length (%2}) isn't a number!").arg(carRoad + " " + carNumber).arg(carLength));
      break;
    }
    if (carWeight.length() > Control::max_len_string_weight_name)
    {
//      JOptionPane.showMessageDialog(NULL, MessageFormat.format(tr("CarWeightNameTooLong"),
//              new Object[]{(carRoad + " " + carNumber), carWeight}), MessageFormat.format(Bundle
//              .getMessage("carAttribute"), new Object[]{Control::max_len_string_weight_name}),
//              JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(NULL, tr("Car attribute must be {0} characters or less").arg(Control::max_len_string_weight_name), tr("Car (%1) weight field (%2) too long!").arg(carRoad + " " + carNumber).arg(carWeight));
      break;
    }
    if (carColor.length() > Control::max_len_string_attibute)
    {
//     JOptionPane.showMessageDialog(NULL, MessageFormat.format(tr("CarColorNameTooLong"),
//             new Object[]{(carRoad + " " + carNumber), carColor}), MessageFormat.format(Bundle
//             .getMessage("carAttribute"), new Object[]{Control::max_len_string_attibute}),
//             JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(NULL, tr("Car attribute must be %1 characters or less").arg(Control::max_len_string_attibute), tr(""));
     break;
    }
    // calculate car weight if "0"
    if (carWeight==("0"))
    {
     bool ok;
        double doubleCarLength = carLength.toDouble(&ok) * 12 / Setup::getScaleRatio();
        double doubleCarWeight = (Setup::getInitalWeight() + doubleCarLength * Setup::getAddWeight()) / 1000;
//        NumberFormat nf = NumberFormat.getNumberInstance();
//        nf.setMaximumFractionDigits(1);
//        carWeight = nf.format(doubleCarWeight); // car weight in ounces.
        carWeight = QString("%1").arg(doubleCarWeight,0,'g',1);
//     }
     if(!ok)
     {
//        JOptionPane.showMessageDialog(NULL, tr("carLengthMustBe"), Bundle
//                 .getMessage("carWeigthCanNot"), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(NULL, tr("Can not calculate car weight!"), tr("Car length must be a number in feet"));
     }
    }
    Car* existingCar = manager->getByRoadAndNumber(carRoad, carNumber);
    if (existingCar != NULL)
    {
     log->info("Can not add, car number (" + carNumber + ") road (" + carRoad + ") already exists!"); // NOI18N
    }
    else
    {
      if (inputLine.length() > base + CAR_OWNER)
      {
       carOwner = inputLine[base + CAR_OWNER];
       if (carOwner.length() > Control::max_len_string_attibute)
       {
//           JOptionPane.showMessageDialog(NULL, MessageFormat.format(Bundle
//                   .getMessage("CarOwnerNameTooLong"), new Object[]{(carRoad + " " + carNumber),
//                   carOwner}), MessageFormat.format(tr("carAttribute"),
//                   new Object[]{Control::max_len_string_attibute}), JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(NULL, tr("Car attribute must be %1 characters or less").arg(Control::max_len_string_attibute), tr(""));
           break;
       }
      }
      if (inputLine.length() > base + CAR_BUILT)
      {
       carBuilt = inputLine[base + CAR_BUILT];
       if (carBuilt.length() > Control::max_len_string_built_name)
       {
//           JOptionPane.showMessageDialog(NULL, MessageFormat.format(Bundle
//                   .getMessage("CarBuiltNameTooLong"), new Object[]{(carRoad + " " + carNumber),
//                   carBuilt}), MessageFormat.format(tr("carAttribute"),
//                   new Object[]{Control::max_len_string_built_name}), JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(NULL, tr("Car attribute must be %1 characters or less").arg(Control::max_len_string_built_name), tr(""));
           break;
       }
      }
      if (inputLine.length() > base + CAR_LOCATION)
      {
       carLocation = inputLine[base + CAR_LOCATION];
      }
      // Location name can be one to three words
      if (inputLine.length() > base + CAR_LOCATION_TRACK_SEPARATOR)
      {
       if (inputLine[base + CAR_LOCATION_TRACK_SEPARATOR]!=(LOCATION_TRACK_SEPARATOR))
       {
        carLocation = carLocation + " " + inputLine[base + 9];
        if (inputLine.length() > base + 10)
        {
         if (inputLine[base + 10]!=(LOCATION_TRACK_SEPARATOR))
         {
          carLocation = carLocation + " " + inputLine[base + 10];
         }
        }
       }
       log->debug(tr("Car (%1 %2) has location (%3)").arg(carRoad).arg(carNumber).arg(carLocation));
       // now get the track name
       bool foundLocationTrackSeparator = false;
       for (int i = base + CAR_LOCATION_TRACK_SEPARATOR; i < inputLine.length(); i++)
       {
        if (inputLine[i]==(LOCATION_TRACK_SEPARATOR))
        {
            foundLocationTrackSeparator = true;
            if (inputLine.length() > i + 1)
            {
                carTrack = inputLine[++i];
            }
        }
        else if (foundLocationTrackSeparator && !comma)
        {
         carTrack = carTrack + " " + inputLine[i];
        }
       }
       if (carTrack == NULL)
       {
           carTrack = "";
       }
       log->debug(tr("Car (%1 %2) has track (%3)").arg(carRoad).arg(carNumber).arg(carTrack));
      }

      // is there a load name?
      if (comma && inputLine.length() > base + CAR_LOAD)
      {
          carLoad = inputLine[CAR_LOAD];
          log->debug(tr("Car (%1 %2) has load (%3)").arg(carRoad).arg(carNumber).arg(carLoad));
      }
      // is there a kernel name?
      if (comma && inputLine.length() > base + CAR_KERNEL)
      {
          carKernel = inputLine[CAR_KERNEL];
          log->debug(tr("Car (%1 %2) has kernel name (%3)").arg(carRoad).arg(carNumber).arg(carKernel));
      }
      // is the a move count?
      if (comma && inputLine.length() > base + CAR_MOVES)
      {
       bool ok;
       {
        carMoves = inputLine[CAR_MOVES].toInt(&ok);
        log->debug(tr("Car (%1 %2) has move count (%3)").arg(carRoad).arg(carNumber).arg(carMoves));
       }
       if(!ok)
       {
           log->error(tr("Car (%1 %2) has move count (%3) not a number").arg(carRoad).arg(carNumber).arg(carMoves));
       }
      }
      // is there a car value?
      if (comma && inputLine.length() > base + CAR_VALUE)
      {
          carValue = inputLine[CAR_VALUE];
      }
      // is there a car comment?
      if (comma && inputLine.length() > base + CAR_COMMENT) {
          carComment = inputLine[CAR_COMMENT];
      }

      if (carLocation.length() > Control::max_len_string_location_name)
      {
//       JOptionPane.showMessageDialog(NULL, MessageFormat.format(Bundle
//               .getMessage("CarLocationNameTooLong"), new Object[]{(carRoad + " " + carNumber),
//               carLocation}), MessageFormat.format(tr("carAttribute"),
//               new Object[]{Control::max_len_string_location_name}), JOptionPane.ERROR_MESSAGE);
       QMessageBox::critical(NULL, tr("Car attribute must be %1 characters or less").arg(Control::max_len_string_location_name), tr(""));
       break;
      }
      if (carTrack.length() > Control::max_len_string_track_name)
      {
//       JOptionPane.showMessageDialog(NULL, MessageFormat.format(Bundle
//               .getMessage("CarTrackNameTooLong"), new Object[]{(carRoad + " " + carNumber),
//               carTrack}), MessageFormat.format(tr("carAttribute"),
//               new Object[]{Control::max_len_string_track_name}), JOptionPane.ERROR_MESSAGE);
       QMessageBox::critical(NULL, tr("Car attribute must be %1 characters or less").arg(Control::max_len_string_track_name), tr(""));
       break;
      }
      Location* location = ((LocationManager*)InstanceManager::getDefault("LocationManager"))->getLocationByName(carLocation);
      Track* track = NULL;
      if (location == NULL && carLocation!=(""))
      {
       if (autoCreateLocations)
       {
        log->debug(tr("Create location (%1)").arg(carLocation));
        location = ((LocationManager*)InstanceManager::getDefault("LocationManager"))->newLocation(carLocation);
       }
       else
       {
//        JOptionPane.showMessageDialog(NULL, MessageFormat.format(Bundle
//                .getMessage("CarLocationDoesNotExist"), new Object[]{(carRoad + " " + carNumber),
//                carLocation}), tr("carLocation"), JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(NULL, tr("Location does not exist!"), tr("Car (%1) location (%2) does not exist!").arg(carRoad + " " + carNumber).arg(carLocation));
//        int results = JOptionPane.showConfirmDialog(NULL, MessageFormat.format(Bundle
//                .getMessage("DoYouWantToCreateLoc"), new Object[]{carLocation}), Bundle
//                .getMessage("carLocation"), JOptionPane.YES_NO_OPTION);
        int results = QMessageBox::question(NULL, tr("Location does not exist!"), tr("Do you want to create location (%1)?").arg(carLocation), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (results == QMessageBox::Yes) {
            log->debug(tr("Create location (%1)").arg(carLocation));
            location = ((LocationManager*)InstanceManager::getDefault("LocationManager"))->newLocation(carLocation);
            if (askAutoCreateLocations) {
//                results = JOptionPane.showConfirmDialog(NULL, Bundle
//                        .getMessage("DoYouWantToAutoCreateLoc"),
//                        tr("OnlyAskedOnce"), JOptionPane.YES_NO_OPTION);
              results = QMessageBox::question(NULL, tr("This question is only asked once per import!"), tr("Do you want the program to automatically create new locations?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
                if (results == QMessageBox::Yes) {
                    autoCreateLocations = true;
                }
            }
            askAutoCreateLocations = false;
        } else {
            break;
        }
       }
      }

      if (location != NULL && carTrack!=(""))
      {
       track = location->getTrackByName(carTrack, NULL);
       if (track == NULL)
       {
        if (autoCreateTracks) {
            if (location->getLocationOps() == Location::NORMAL)
            {
                log->debug(tr("Create 1000 foot yard track (%1)").arg(carTrack));
                track = location->addTrack(carTrack, Track::YARD);
            } else {
                log->debug(tr("Create 1000 foot staging track (%1)").arg(carTrack));
                track = location->addTrack(carTrack, Track::STAGING);
            }
            track->setLength(1000);
        }
        else
        {
//         JOptionPane.showMessageDialog(NULL, MessageFormat.format(Bundle
//                 .getMessage("CarTrackDoesNotExist"), new Object[]
//         {
//                 (carRoad + " " + carNumber), carTrack, carLocation}), Bundle
//                 .getMessage("carTrack"), JOptionPane.ERROR_MESSAGE);
         QMessageBox::critical(NULL, tr("Track does not exist!"), tr("Car (%1) track (%2) at location (%3) does not exist!").arg(carRoad + " " + carNumber).arg(carTrack).arg(carLocation));
//         int results = JOptionPane.showConfirmDialog(NULL, MessageFormat.format(Bundle
//                 .getMessage("DoYouWantToCreateTrack"), new Object[]{carTrack, carLocation}),
//                 tr("carTrack"), JOptionPane.YES_NO_OPTION);
         int results = QMessageBox::question(NULL, tr("Track does not exist!"), tr("Do you want to create track (%1) at location (%2)?").arg(carTrack).arg(carLocation), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
         if (results == QMessageBox::Yes)
         {
          if (location->getLocationOps() == Location::NORMAL)
          {
              log->debug(tr("Create 1000 foot yard track (%1)").arg(carTrack));
              track = location->addTrack(carTrack, Track::YARD);
          } else {
              log->debug(tr("Create 1000 foot staging track (%1)").arg(carTrack));
              track = location->addTrack(carTrack, Track::STAGING);
          }
          track->setLength(1000);
          if (askAutoCreateTracks) {
//           results = JOptionPane.showConfirmDialog(null, Bundle
//                   .getMessage("DoYouWantToAutoCreateTrack"), Bundle
//                   .getMessage("OnlyAskedOnce"), JOptionPane.YES_NO_OPTION);
            results = QMessageBox::question(NULL, tr("This question is only asked once per import!"), tr("Do you want the program to automatically create new tracks?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
              if (results == QMessageBox::Yes) {
                  autoCreateTracks = true;
              }
              askAutoCreateTracks = false;
          }
         }
         else
         {
          break;
         }
        }
       }
      }

      log->debug(tr("Add car (%1 %2) owner (%3) built (%4) location (%5, %6)").arg(carRoad).arg(carNumber).arg(carOwner).arg(
              carBuilt).arg(carLocation).arg(carTrack));
      Car* car = (Car*)manager->newRS(carRoad, carNumber);
      car->setTypeName(carType);
      car->setLength(carLength);
      car->setWeight(carWeight);
      car->setColor(carColor);
      car->setOwner(carOwner);
      car->setBuilt(carBuilt);
      car->setLoadName(carLoad);
      car->setKernel(manager->newKernel(carKernel));
      car->setMoves(carMoves);
      car->setValue(carValue);
      car->setComment(carComment);
      carsAdded++;

      // if the car's type name is "Caboose" then make it a caboose
      car->setCaboose(carType==("Caboose"));
      // determine if there are any car extensions
      if (comma && inputLine.length() > base + CAR_EXTENSIONS)
      {
       QString extensions = inputLine[CAR_EXTENSIONS];
       log->debug(tr("Car (%1 %2) has extension (%3)").arg(carRoad).arg(carNumber).arg(extensions));
       QStringList ext = extensions.split(Car::EXTENSION_REGEX);
       for (int i = 0; i < ext.length(); i++)
       {
        if (ext[i]==(Car::CABOOSE_EXTENSION))
        {
            car->setCaboose(true);
        }
        if (ext[i]==(Car::FRED_EXTENSION))
        {
            car->setFred(true);
        }
        if (ext[i]==(Car::PASSENGER_EXTENSION))
        {
            car->setPassenger(true);
            car->setBlocking(ext[i + 1].toInt());
        }
        if (ext[i]==(Car::UTILITY_EXTENSION))
        {
            car->setUtility(true);
        }
        if (ext[i]==(Car::HAZARDOUS_EXTENSION))
        {
            car->setHazardous(true);
        }
       }
      }

      // add new roads
      if (!((CarRoads*)InstanceManager::getDefault("CarRoads"))->containsName(carRoad))
      {
       if (autoCreateRoads)
       {
           log->debug(tr("add car road %1").arg(carRoad));
           ((CarRoads*)InstanceManager::getDefault("CarRoads"))->addName(carRoad);
       }
      }

      // add new lengths
      if (!((CarLengths*)InstanceManager::getDefault("CarLengths"))->containsName(carLength))
      {
       if (autoCreateLengths)
       {
        log->debug(tr("add car length %1").arg(carLength));
        ((CarLengths*)InstanceManager::getDefault("CarLengths"))->addName(carLength);
       }
      }

      // add new colors
      if (!((CarColors*)InstanceManager::getDefault("CarColors"))->containsName(carColor))
      {
       if (autoCreateColors)
       {
        log->debug(tr("add car color %1").arg(carColor));
        ((CarColors*)InstanceManager::getDefault("CarColors"))->addName(carColor);
       }
      }

      // add new owners
      if (!((CarOwners*)InstanceManager::getDefault("CarOwners"))->containsName(carOwner))
      {
       if (autoCreateOwners)
       {
        log->debug(tr("add car owner %1").arg(carOwner));
        ((CarOwners*)InstanceManager::getDefault("CarOwners"))->addName(carOwner);
       }
      }

      if (car->getWeight()==(""))
      {
       log->debug(tr("Car (%1 %2) weight not specified").arg(carRoad).arg(carNumber));
       if (weightResults != QMessageBox::Cancel)
       {
//        weightResults = JOptionPane.showOptionDialog(NULL, MessageFormat.format(Bundle
//                .getMessage("CarWeightNotFound"), new Object[]{(carRoad + " " + carNumber)}),
//                tr("CarWeightMissing"), JOptionPane.YES_NO_CANCEL_OPTION,
//                JOptionPane.INFORMATION_MESSAGE, NULL, new Object[]{
//                        tr("ButtonYes"), tr("ButtonNo"),
//                        tr("ButtonDontShow")}, autoCalculate ? Bundle
//                        .getMessage("ButtonYes") : tr("ButtonNo"));
        weightResults = QMessageBox::question(NULL, tr("Car weight missing!"), tr("Car (%1) weight not found, do you want the program to calculate it for you?").arg(carRoad + " " + carNumber), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
       }
       if (weightResults == QMessageBox::No) {
           autoCalculate = false;
       }
       if (weightResults == QMessageBox::Yes || autoCalculate == true
               && weightResults == QMessageBox::Cancel)
       {
           autoCalculate = true;
           bool ok;
               double carLen = car->getLength().toInt(&ok) * 12 / Setup::getScaleRatio();
               double carWght = (Setup::getInitalWeight() + carLen * Setup::getAddWeight()) / 1000;
//               NumberFormat nf = NumberFormat.getNumberInstance();
//               nf.setMaximumFractionDigits(1);
//               car->setWeight(nf.format(carWght)); // car weight in ounces.
               car->setWeight(QString("%1").arg(carWght,0,'g',1));
               int tons = (int) (carWght * Setup::getScaleTonRatio());
               // adjust weight for caboose
               if (car->isCaboose()) {
                   tons = (int) (car->getLength().toInt(&ok) * .9); // .9 tons/foot
               }
               car->setWeightTons(QString::number(tons));
           if(!ok)
           {
//               JOptionPane.showMessageDialog(NULL, tr("carLengthMustBe"), Bundle
//                       .getMessage("carWeigthCanNot"), JOptionPane.ERROR_MESSAGE);
            QMessageBox::critical(NULL, tr("Can not calculate car weight!"), tr("Car length must be a number in feet"));
           }
       }
      }
      if (location != NULL && track != NULL)
      {
       QString status = car->setLocation(location, track);
       if (status!=(Track::OKAY))
       {
        log->debug(tr("Can't set car's location because of %1").arg(status));
        if (status.startsWith(Track::TYPE))
        {
         if (autoAdjustLocationType)
         {
             location->addTypeName(carType);
             track->addTypeName(carType);
             status = car->setLocation(location, track);
         }
         else
         {
//          JOptionPane.showMessageDialog(NULL, MessageFormat.format(Bundle
//                  .getMessage("CanNotSetCarAtLocation"), new Object[]{
//                  (carRoad + " " + carNumber), carType, carLocation, carTrack, status}),
//                  tr("rsCanNotLoc"), JOptionPane.ERROR_MESSAGE);
          QMessageBox::critical(NULL, tr("Can not update car location"), tr("Can't set car (%1) type (%2) at location (%3) track (%4) due to %5").arg(carRoad + " " + carNumber).arg(carType).arg(carLocation).arg(carTrack).arg(status));
//          int results = JOptionPane.showConfirmDialog(NULL, MessageFormat.format(Bundle
//                  .getMessage("DoYouWantToAllowService"), new Object[]{carLocation,
//                  carTrack, (carRoad + " " + carNumber), carType}), Bundle
//                  .getMessage("ServiceCarType"), JOptionPane.YES_NO_OPTION);
          int results = QMessageBox::question(NULL, tr("Allow track to service car?"), tr("Do you want location (%1) and track (%2) to service (%3) type (%4)?").arg(carLocation).arg(carTrack).arg(carRoad + " " + carNumber).arg(carType), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
          if (results == QMessageBox::Yes)
          {
           location->addTypeName(carType);
           track->addTypeName(carType);
           status = car->setLocation(location, track);
           log->debug(tr("Set car's location status: %1").arg(status));
           if (askAutoLocationType) {
//               results = JOptionPane.showConfirmDialog(NULL, Bundle
//                       .getMessage("DoYouWantToAutoAdjustLocations"), Bundle
//                       .getMessage("OnlyAskedOnce"), JOptionPane.YES_NO_OPTION);
             results = QMessageBox::question(NULL, tr("This question is only asked once per import!"), tr("Do you want the program to automatically adjust locations and tracks to accept new car types?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
               if (results == QMessageBox::Yes) {
                   autoAdjustLocationType = true;
               }
               askAutoLocationType = false;
           }
          } else {
              break;
          }
         }
        }
        if (status.startsWith(Track::LENGTH))
        {
         if (autoAdjustTrackLength) {
             track->setLength(track->getLength() + 1000);
             status = car->setLocation(location, track);
             log->debug(tr("Set track length status: %1").arg(status));
         }
         else
         {
//          JOptionPane.showMessageDialog(NULL, MessageFormat.format(Bundle
//                  .getMessage("CanNotSetCarAtLocation"), new Object[]{
//                  (carRoad + " " + carNumber), carType, carLocation, carTrack, status}),
//                  tr("rsCanNotLoc"), JOptionPane.ERROR_MESSAGE);
          QMessageBox::critical(NULL, tr("Can not update car location"), tr("Can''t set car (%1) type (%2) at location (%3) track (%4) due to %5").arg(carRoad + " " + carNumber).arg(carType).arg(carLocation).arg(carTrack).arg(status));
//          int results = JOptionPane.showConfirmDialog(NULL, MessageFormat.format(Bundle
//                  .getMessage("DoYouWantIncreaseLength"), new Object[]{carTrack}), Bundle
//                  .getMessage("TrackLength"), JOptionPane.YES_NO_OPTION);
          int results = QMessageBox::question(NULL, tr("Change track length?"), tr("Do you want to increase the length of track (%1)?").arg(carTrack), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
          if (results == QMessageBox::Yes)
          {
           track->setLength(track->getLength() + 1000);
           status = car->setLocation(location, track);
           log->debug(tr("Set track length status: %1").arg(status));
           if (askAutoIncreaseTrackLength)
           {
//            results = JOptionPane.showConfirmDialog(NULL, Bundle
//                    .getMessage("DoYouWantToAutoAdjustTrackLength"), Bundle
//                    .getMessage("OnlyAskedOnce"), JOptionPane.YES_NO_OPTION);
            int results = QMessageBox::question(NULL, tr("This question is only asked once per import!"), tr("Do you want the program to automatically adjust tracks lengths to accept new cars?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
            if (results == QMessageBox::Yes) {
                autoAdjustTrackLength = true;
            }
            askAutoIncreaseTrackLength = false;
           }
          }
          else
          {
           break;
          }
         }
        }
        if (status!=(Track::OKAY))
        {
         if (autoForceCar) {
             car->setLocation(location, track, RollingStock::FORCE); // force car
         }
         else
         {
//          JOptionPane.showMessageDialog(NULL, MessageFormat.format(Bundle
//                  .getMessage("CanNotSetCarAtLocation"), new Object[]{
//                  (carRoad + " " + carNumber), carType, carLocation, carTrack, status}),
//                  tr("rsCanNotLoc"), JOptionPane.ERROR_MESSAGE);
          QMessageBox::critical(NULL, tr("Can not update car location"), tr("Can't set car (%1) type (%2) at location (%3) track (%4) due to %5").arg(carRoad + " " + carNumber).arg(carType).arg(carLocation).arg(carTrack).arg(status));
//          int results = JOptionPane.showConfirmDialog(NULL, MessageFormat.format(Bundle
//                  .getMessage("DoYouWantToForceCar"), new Object[]{
//                  (carRoad + " " + carNumber), carLocation, carTrack}), Bundle
//                  .getMessage("OverRide"), JOptionPane.YES_NO_OPTION);
          int results = QMessageBox::question(NULL, tr("Override track restriction?"), tr("Do you want to force car (%1) to location (%2) track (%3)?").arg(carRoad + " " + carNumber).arg(carLocation).arg(carTrack), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
          if (results == QMessageBox::Yes)
          {
           car->setLocation(location, track, true); // force car
           if (askAutoForceCar)
           {
//               results = JOptionPane.showConfirmDialog(NULL, Bundle
//                       .getMessage("DoYouWantToAutoForceCar"), Bundle
//                       .getMessage("OnlyAskedOnce"), JOptionPane.YES_NO_OPTION);
             results = QMessageBox::question(NULL, tr("This question is only asked once per import!"), tr("Do you want the program to automatically force your cars on to a track?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
               if (results == QMessageBox::Yes)
               {
                   autoForceCar = true;
               }
               askAutoForceCar = false;
           }
          }
          else
          {
           break;
          }
         }
        }
       }
      }
      else
      {
          // log->debug("No location for car ("+carRoad+" "+carNumber+")");
      }
     }
    }
   else if (importKernel && inputLine.length() == base + 3)
   {
    carNumber = inputLine[base + 0];
    carRoad = inputLine[base + 1];
    QString kernelName = inputLine[base + 2];
    Car* car = manager->getByRoadAndNumber(carRoad, carNumber);
    if (car != NULL)
    {
     Kernel* kernel = manager->newKernel(kernelName);
     car->setKernel(kernel);
     carsAdded++;
    }
    else
    {
     log->info("Car number (" + carNumber + ") road (" + carRoad + ") does not exist!"); // NOI18N
     break;
    }
   }
   else if (line!=(""))
   {
    log->info("Car import line " + QString::number(lineNum) + " missing attributes: " + line);
//    JOptionPane.showMessageDialog(NULL, MessageFormat.format(tr("ImportMissingAttributes"),
//            new Object[]{lineNum})
//            + NEW_LINE + line + NEW_LINE + tr("ImportMissingAttributes2"), Bundle
//            .getMessage("CarAttributeMissing"), JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(NULL, tr("Car attribute missing!"), tr("Import line number %1 missing one or more of the first four required car attributes").arg(lineNum)+ NEW_LINE + line + NEW_LINE + tr("Attribute order: Number, Road, Type, Length, Weight, Color, Owner, Built, Location,-,Track"));
    break;
   }
   qApp->processEvents();
  } // end while

  try
  {
     // in.close();
   in->device()->close();
  }
  catch (IOException* e)
  {
  }

  // kill status panel
  fstatus->dispose();

  if (importOkay)
  {
//      JOptionPane
//              .showMessageDialog(NULL, MessageFormat.format(tr("ImportCarsAdded"),
//                      new Object[]{carsAdded}), tr("SuccessfulImport"),
//                      JOptionPane.INFORMATION_MESSAGE);
   QMessageBox::information(NULL, tr("Successful import!"), tr("%1 cars added to operations roster").arg(carsAdded));
  }
  else
  {
//   JOptionPane.showMessageDialog(NULL, MessageFormat.format(tr("ImportCarsAdded"),
//           new Object[]{carsAdded}), tr("ImportFailed"), JOptionPane.ERROR_MESSAGE);
   QMessageBox::information(NULL, tr("Import failed!"), tr("%1 cars added to operations roster").arg(carsAdded));
  }
#endif
 }

}
