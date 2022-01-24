#include "exportlocations.h"
#include "loggerfactory.h"
#include "file.h"
#include "operationssetupxml.h"
#include "joptionpane.h"
#include "exceptions.h"
#include "track.h"
#include "location.h"
#include "setup.h"
#include "route.h"
#include "division.h"

namespace Operations {

 /**
  * Exports the location roster into a comma delimited file (CSV).
  *
  * @author Daniel Boudreau Copyright (C) 2018
  *
  */
 ///*public*/  class ExportLocations extends XmlFile {


     /*public*/  void ExportLocations::writeOperationsLocationFile() {
         makeBackupFile(defaultOperationsFilename());
         try {
             if (!checkFile(defaultOperationsFilename())) {
                 // The file does not exist, create it before writing
                 File* file = new File(defaultOperationsFilename());
                 File* parentDir = file->getParentFile();
                 if (!parentDir->exists()) {
                     if (!parentDir->mkdir()) {
                         log->error("Directory wasn't created");
                     }
                 }
                 if (file->createNewFile()) {
                     log->debug("File created");
                 }
             }
             writeFile(defaultOperationsFilename());
         } catch (IOException* e) {
             log->error(tr("Exception while writing the new CSV operations file, may not be complete: %1").arg(e->getMessage()));
         }
     }

     /*public*/  void ExportLocations::writeFile(QString name) {
         log->debug(tr("writeFile %1").arg(name));
         File* file = findFile(name);
         if (file == nullptr) {
             file = new File(name);
         }

         QFile *qf = file->toQfile();
         if(!qf->open(QIODevice::Truncate|QIODevice::WriteOnly ))
          throw new IOException(tr("Can't open foroutput: %s").arg(qf->fileName()));
         QTextStream* stream = new QTextStream(qf);

         try {
          CSVPrinter* fileOut = new EL_CSVPrinter(stream,
             CSVFormat::DEFAULT, this);//

          // create header
          fileOut->printRecord(QVariantList {tr("Location"),
                 tr("Track"),
                 tr("Type"),
                 tr("Length"),
                 tr("Division"),
                 tr("ServicedByTrains"),
                 tr("RollingStock"),
                 tr("ServiceOrder"),
                 tr("RoadOption"),
                 tr("Roads"),
                 tr("LoadOption"),
                 tr("Loads"),
                 tr("ShipLoadOption"),
                 tr("Ships"),
                 tr("SetOutRestrictions"),
                 tr("Restrictions"),
                 tr("PickUpRestrictions"),
                 tr("Restrictions"),
                 tr("ScheduleName"),
                 tr("ScheduleMode"),
                 tr("AlternateTrack"),
                 tr("PoolName"),
                 tr("Minimum"),
                 tr("TitleTrackBlockingOrder"),
                 tr("MenuItemPlannedPickups"),
                 tr("MenuItemDestinations"),
                 tr("Destinations"),
                 tr("SwapCarLoads"),
                 tr("EmptyDefaultCarLoads"),
                 tr("EmptyCarLoads"),
                 tr("LoadCarLoads"),
                 tr("LoadAnyCarLoads"),
                 tr("LoadsStaging"),
                 tr("BlockCars"),
                 tr("Comment"),
                 tr("CommentBoth"),
                 tr("CommentPickup"),
                 tr("CommentSetout")});

         QList<Location*> locations = locationManager->getLocationsByNameList();
         for (Location* location : locations) {
             for (Track* track : location->getTracksByNameList("")) {

                 QString trainDirections;// = new QString();
                 QStringList directions = Setup::getDirectionStrings(
                         Setup::getTrainDirection() & location->getTrainDirections() & track->getTrainDirections());
                 for (QString dir : directions) {
                     if (dir != "") {
                         trainDirections.append(dir).append("; ");
                     }
                 }

                 QString rollingStockNames;// = new QString();
                 for (QString rollingStockName : track->getTypeNames()) {
                     rollingStockNames.append(rollingStockName).append("; ");
                 }

                 QString roadNames;// = new QString();
                 if (track->getRoadOption() != (Track::ALL_ROADS)) {
                     for (QString roadName : track->getRoadNames()) {
                         roadNames.append(roadName).append("; ");
                     }
                 }

                 QString loadNames;// = new QString();
                 if (track->getLoadOption() != (Track::ALL_LOADS)) {
                     for (QString loadName : track->getLoadNames()) {
                         loadNames.append(loadName).append("; ");
                     }
                 }

                 QString shipNames;// = new QString();
                 if (track->getShipLoadOption() != (Track::ALL_LOADS)) {
                     for (QString shipName : track->getShipLoadNames()) {
                         shipNames.append(shipName).append("; ");
                     }
                 }

                 QString setOutRestriction = tr("None");
                 if(track->getDropOption()== Track::TRAINS)
                         setOutRestriction = tr("Trains");
                 else if(track->getDropOption()==Track::ROUTES)
                         setOutRestriction = tr("Routes");
                 else if(track->getDropOption()==Track::EXCLUDE_TRAINS)
                         setOutRestriction = tr("ExcludeTrains");
                 else if(track->getDropOption()==Track::EXCLUDE_ROUTES)
                         setOutRestriction = tr("ExcludeRoutes");

                 QString setOutRestrictions;// = new QString();
                 if (track->getDropOption() == (Track::TRAINS) || track->getDropOption() == (track->EXCLUDE_TRAINS)) {
                     for (QString id : track->getDropIds()) {
                         Train* train = trainManager->getTrainById(id);
                         if (train != nullptr) {
                             setOutRestrictions.append(train->getName()).append("; ");
                         }
                     }
                 }
                 if (track->getDropOption() == (Track::ROUTES) || track->getDropOption() == (track->EXCLUDE_ROUTES)) {
                     for (QString id : track->getDropIds()) {
                         Route* route = routeManager->getRouteById(id);
                         if (route != nullptr) {
                             setOutRestrictions.append(route->getName()).append("; ");
                         }
                     }
                 }

                 QString pickUpRestriction = tr("None");
                 if(track->getPickupOption()== Track::TRAINS)
                         pickUpRestriction = tr("Trains");
                 else if(track->getPickupOption()== Track::ROUTES)
                         pickUpRestriction = tr("Routes");
                 else if(track->getPickupOption()== Track::EXCLUDE_TRAINS)
                         pickUpRestriction = tr("ExcludeTrains");
                 else if(track->getPickupOption()== Track::EXCLUDE_ROUTES)
                         pickUpRestriction = tr("ExcludeRoutes");

                 QString pickUpRestrictions;// = new QString();
                 if (track->getPickupOption() == Track::TRAINS
                         || track->getPickupOption() == (Track::EXCLUDE_TRAINS)) {
                     for (QString id : track->getPickupIds()) {
                         Train* train = trainManager->getTrainById(id);
                         if (train != nullptr) {
                             pickUpRestrictions.append(train->getName()).append("; ");
                         }
                     }
                 }
                 if (track->getPickupOption() == (track->ROUTES)
                         || track->getPickupOption() == (track->EXCLUDE_ROUTES)) {
                     for (QString id : track->getPickupIds()) {
                         Route* route = routeManager->getRouteById(id);
                         if (route != nullptr) {
                             pickUpRestrictions.append(route->getName()).append("; ");
                         }
                     }
                 }

                 QString alternateTrackName = "";
                 if (track->getAlternateTrack() != nullptr) {
                     alternateTrackName = track->getAlternateTrack()->getName();
                 }
                 if (track->isAlternate()) {
                     alternateTrackName = tr("Yes");
                 }

                 QString destinationNames;// = new QString();
                 for (QString id : track->getDestinationIds()) {
                     Location* destination = locationManager->getLocationById(id);
                     if (destination != nullptr) {
                         destinationNames.append(destination->getName()).append("; ");
                     }
                 }

                 fileOut->printRecord(QVariantList{location->getName(),
                          track->getName(),
                          track->getTrackTypeName(),
                          track->getLength(),
                          track->getDivisionName(),
                          trainDirections,
                          rollingStockNames,
                          track->getServiceOrder(),
                          track->getRoadOptionString(),
                          roadNames,
                          track->getLoadOptionString(),
                          loadNames,
                          track->getShipLoadOptionString(),
                          shipNames,
                          setOutRestriction,
                          setOutRestrictions,
                          pickUpRestriction,
                          pickUpRestrictions,
                          track->getScheduleName(),
                          track->getScheduleModeName(),
                          alternateTrackName,
                          track->getPoolName(),
                          track->getMinimumLength(),
                          track->getBlockingOrder(),
                          track->getIgnoreUsedLengthPercentage(),
                         tr(track->getDestinationOption() == (track->ALL_DESTINATIONS) ? "All" : "Include"),
                         destinationNames ,
                         (track->isLoadSwapEnabled() ? tr("ButtonYes") : ""),
                         (track->isLoadEmptyEnabled() ? tr("ButtonYes") : ""),
                         (track->isRemoveCustomLoadsEnabled() ? tr("ButtonYes") : ""),
                         (track->isAddCustomLoadsEnabled() ? tr("ButtonYes") : ""),
                         (track->isAddCustomLoadsAnySpurEnabled() ? tr("ButtonYes") : ""),
                         (track->isAddCustomLoadsAnyStagingTrackEnabled() ? tr("ButtonYes") : ""),
                         (track->isBlockCarsEnabled() ? tr("ButtonYes") : ""),
                         track->getComment(),
                         track->getCommentBoth(),
                         track->getCommentPickup(),
                         track->getCommentSetout()});
             }
            }

            fileOut->flush();
            fileOut->close();
            log->info(tr("Exported %1 locations to file %2").arg(locations.size()).arg(defaultOperationsFilename()));
            JOptionPane::showMessageDialog(nullptr,
                    tr("Exported %1 locations to file: %2").arg(locations.size()).arg(defaultOperationsFilename()),
                    tr("Export Complete"),
                    JOptionPane::INFORMATION_MESSAGE);

         } catch (IOException* e) {
             log->error(tr("Can not open export locations CSV file: %1").arg(file->getName()));
             JOptionPane::showMessageDialog(nullptr,
                     tr("Exported %1 locations to file: %2").arg(0).arg(defaultOperationsFilename()),
                     tr("Export Failed"),
                     JOptionPane::ERROR_MESSAGE);
         }

      }

     // Operation files always use the same directory
     /*public*/  /*static*/ QString ExportLocations::defaultOperationsFilename() {
         return OperationsSetupXml::getFileLocation()
                 + OperationsSetupXml::getOperationsDirectoryName()
                 + File::separator
                 + getOperationsFileName();
     }

     /*public*/  /*static*/ void ExportLocations::setOperationsFileName(QString name) {
         operationsFileName = name;
     }

     /*public*/  /*static*/ QString ExportLocations::getOperationsFileName() {
         return operationsFileName;
     }

     /*private*/ /*static*/ QString ExportLocations::operationsFileName = "ExportOperationsLocationRoster.csv"; // NOI18N

     /*private*/ /*final*/ /*static*/ Logger* ExportLocations::log = LoggerFactory::getLogger("ExportLocations");



} // namespace Operations
