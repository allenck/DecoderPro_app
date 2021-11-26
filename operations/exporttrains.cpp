#include "exporttrains.h"
#include "operationssetupxml.h"
#include "setup.h"
#include "file.h"
#include "logger.h"
#include "printwriter.h"
#include "trainmanager.h"
#include "train.h"
#include "route.h"
#include "routelocation.h"
#include <QMessageBox>
#include "instancemanager.h"

namespace Operations
{
 /**
  * Exports the car roster into a comma delimited file (CSV).
  *
  * @author Daniel Boudreau Copyright (C) 2010, 2011
  * @version $Revision: 29118 $
  *
  */
 ///*public*/ class ExportTrains extends XmlFile {

 /*static*/ /*final*/ QString ExportTrains::ESC = "\""; // escape character NOI18N

 /*public*/ ExportTrains::ExportTrains() : XmlFile()
 {
  del = ","; // delimiter
  log = new Logger("ExportTrains");
 }

 /*public*/ void ExportTrains::setDeliminter(QString delimiter) {
     del = delimiter;
 }

 /**
  * Store the all of the operation car objects in the default place,
  * including making a backup if needed
  */
 /*public*/ void ExportTrains::writeOperationsCarFile()
 {
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
  } catch (Exception e) {
      log->error("Exception while writing the new CSV operations file, may not be complete: " /*+ e*/);
  }
 }

 /*public*/ void ExportTrains::writeFile(QString name) {
     if (log->isDebugEnabled()) {
         log->debug(tr("writeFile %1").arg(name));
     }
     // This is taken in large part from "Java and XML" page 368
     QFile* file = findFile(name)->toQfile();
     if (file == NULL) {
         file = new QFile(name);
     }

     PrintWriter* fileOut = NULL;

     //try {
         //fileOut = new PrintWriter(new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file), "UTF-8")), // NOI18N
     if(!file->open(QIODevice::WriteOnly))
     {
      log->error("Can not open export cars CSV file: " + file->fileName());
      return;
     }
     QTextStream* stream = new QTextStream(file);
     stream->setCodec("UTF-8");
     fileOut = new PrintWriter(stream);
//         true); // NOI18N
//     } catch (IOException e) {
//         log->error("Can not open export cars CSV file: " + file.getName());
//         return;
//     }

     // create header
     QString header = tr("Name") +
             del + tr("Description") +
             del + tr("Time") +
             del + tr("Route") +
             del + tr("Departs") +
             del + tr("Terminates") +
             del + tr("Status") +
             del + tr("Comment");
     fileOut->println(header);

     int count = 0;

     foreach (Train* train, ((TrainManager*)InstanceManager::getDefault("TrainManager"))->getTrainsByTimeList()) {
         if (!train->isBuildEnabled())
             continue;
         count++;
         QString routeName = "";
         if (train->getRoute() != NULL)
             routeName = train->getRoute()->getName();
         QString line = ESC + train->getName() + ESC +
                 del + ESC + train->getDescription() + ESC +
                 del + ESC + train->getDepartureTime() + ESC +
                 del + ESC + routeName + ESC +
                 del + ESC + train->getTrainDepartsName() + ESC +
                 del + ESC + train->getTrainTerminatesName() + ESC +
                 del + ESC + train->getStatus() + ESC +
                 del + ESC + train->getComment() + ESC;
         fileOut->println(line);
     }

     fileOut->println();
     // second create header for built trains
     header = tr("Name") +
             del + tr("csvParameters") +
             del + tr("Attributes");
     fileOut->println(header);

     foreach (Train* train, ((TrainManager*)InstanceManager::getDefault("TrainManager"))->getTrainsByTimeList()) {
         if (!train->isBuildEnabled())
             continue;

         if (train->isBuilt() && train->getRoute() != NULL) {
             QString line = ESC + train->getName() + ESC + del + tr("Route");
             foreach (RouteLocation* rl, *train->getRoute()->getLocationsBySequenceList()) {
                 line = line + del + ESC +rl->getName() + ESC;
             }
             fileOut->println(line);

             line = ESC + train->getName() + ESC + del + tr("Arrival Time");
             foreach (RouteLocation* rl, *train->getRoute()->getLocationsBySequenceList()) {
                 line = line + del + ESC + train->getExpectedArrivalTime(rl) + ESC;
             }
             fileOut->println(line);

             line = ESC + train->getName() + ESC + del + tr("Departure Time");
             foreach (RouteLocation* rl, *train->getRoute()->getLocationsBySequenceList()) {
                 line = line + del + ESC + train->getExpectedDepartureTime(rl) + ESC;
             }
             fileOut->println(line);

             line = ESC + train->getName() + ESC + del + tr("Train Direction");
             foreach (RouteLocation* rl, *train->getRoute()->getLocationsBySequenceList()) {
                 line = line + del + ESC +rl->getTrainDirectionString() + ESC;
             }
             fileOut->println(line);

             line = ESC + train->getName() + ESC + del + tr("Train Weight");
             foreach (RouteLocation* rl, *train->getRoute()->getLocationsBySequenceList()) {
                 line = line + del + ESC + train->getTrainWeight(rl) + ESC;
             }
             fileOut->println(line);

             line = ESC + train->getName() + ESC + del + tr("Train Length");
             foreach (RouteLocation* rl, *train->getRoute()->getLocationsBySequenceList()) {
                 line = line + del + ESC + train->getTrainLength(rl) + ESC;
             }
             fileOut->println(line);

             line = ESC + train->getName() + ESC + del + tr("Cars");
             foreach (RouteLocation* rl, *train->getRoute()->getLocationsBySequenceList()) {
                 line = line + del + ESC + train->getNumberCarsInTrain(rl) + ESC;
             }
             fileOut->println(line);

             line = ESC + train->getName() + ESC + del + tr("Empties");
             foreach (RouteLocation* rl, *train->getRoute()->getLocationsBySequenceList()) {
                 line = line + del + ESC + train->getNumberEmptyCarsInTrain(rl) + ESC;
             }
             fileOut->println(line);
             fileOut->println();
         }
     }

     fileOut->flush();
     fileOut->close();
     log->info(tr("Exported %1 trains to file %2").arg(count).arg(defaultOperationsFilename()));
//     JOptionPane.showMessageDialog(NULL, MessageFormat.format(tr("ExportedTrainsToFile"), new Object[]{
//             count, defaultOperationsFilename()}), tr("Export complete"),
//             JOptionPane.INFORMATION_MESSAGE);
     QMessageBox::information(NULL, tr(""), tr("Exported %1 trains to file: %2").arg(count).arg(defaultOperationsFilename()));
 }

 // Operation files always use the same directory
 /*public*/ /*static*/ QString ExportTrains::defaultOperationsFilename() {
     return OperationsSetupXml::getFileLocation() + OperationsSetupXml::getOperationsDirectoryName() + File::separator
             + getOperationsFileName();
 }

 /*public*/ /*static*/ void ExportTrains::setOperationsFileName(QString name) {
     OperationsFileName = name;
 }

 /*public*/ /*static*/ QString ExportTrains::getOperationsFileName() {
     return OperationsFileName;
 }

 /*private*/ /*static*/ QString ExportTrains::OperationsFileName = "ExportOperationsTrainRoster.csv"; // NOI18N
}
