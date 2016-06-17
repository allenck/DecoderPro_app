#include "exportcars.h"
#include "carmanager.h"
#include "rollingstock.h"
#include "car.h"
#include "file.h"
#include "logger.h"
#include "printwriter.h"
#include "qmessagebox.h"
#include "operationssetupxml.h"
#include "setup.h"

namespace Operations
{
 /**
  * Exports the car roster into a comma delimitated file (CSV).
  *
  * @author Daniel Boudreau Copyright (C) 2010, 2011
  * @version $Revision: 29118 $
  *
  */
 ///*public*/ class ExportCars extends XmlFile {

 /*static*/ /*final*/ QString ExportCars::ESC = "\""; // escape character NOI18N

 /*public*/ ExportCars::ExportCars() : XmlFile()
 {
 log = new Logger("ExportCars");
  del = ","; // delimiter
 }

 /*public*/ void ExportCars::setDeliminter(QString delimiter) {
     del = delimiter;
 }

 /**
  * Store the all of the operation car objects in the default place,
  * including making a backup if needed
  */
 /*public*/ void ExportCars::writeOperationsCarFile() {
     makeBackupFile(defaultOperationsFilename());
     //try {
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
//     } catch (Exception e) {
//         log->error("Exception while writing the new CSV operations file, may not be complete: " + e);
//     }
 }

 /*public*/ void ExportCars::writeFile(QString name)
 {
     if (log->isDebugEnabled()) {
         log->debug(tr("writeFile %1").arg(name));
     }
     // This is taken in large part from "Java and XML" page 368
     QFile* file = findFile(name);
     if (file == NULL) {
         file = new QFile(name);
     }

     PrintWriter* fileOut = NULL;

     //try {
     if(!file->open(QIODevice::WriteOnly))
     {
      log->error("Can not open export cars CSV file: " + file->fileName());
      return;
     }
     QTextStream* stream = new QTextStream(file);
     stream->setCodec("UTF-8");
         //fileOut = new PrintWriter(new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file), "UTF-8")), // NOI18N
//                 true); // NOI18N
     fileOut = new PrintWriter(stream);
//     } catch (IOException e) {
//         log->error("Can not open export cars CSV file: " + file.getName());
//         return;
//     }

     CarManager* manager = CarManager::instance();
     QList<RollingStock*>* carList = manager->getByNumberList();
     QString line = "";
     // check for delimiter in the following car fields
     QString carType;
     QString carLocationName;
     QString carTrackName;
     // assume delimiter in the value field
     QString value;
     QString comment;
     // create header
     QString header = tr("Number") + del + tr("Road") + del + tr("Type")
             + del + tr("Length") + del + tr("Weight") + del
             + tr("Color") + del + tr("Owner") + del + tr("Built")
             + del + tr("Location") + del + "-" + del + tr("Track") + del
             + tr("Load") + del + tr("Kernel")
             + del + tr("Moves") + del + Setup::getValueLabel() + del + tr("Comment");
     fileOut->println(header);

     // store car number, road, type, length, weight, color, owner, built date, location and track
     foreach (RollingStock* rs, *carList) {
         Car* car = (Car*) rs;
         carType = car->getTypeName();
         if (carType.contains(del)) {
//				log->debug("Car (" + car->getRoadName() + " " + car->getNumber() + ") has delimiter in type field: "
//						+ carType); // NOI18N
             carType = ESC + car->getTypeName() + ESC;
         }
         carLocationName = car->getLocationName();
         if (carLocationName.contains(del)) {
//				log->debug("Car (" + car->getRoadName() + " " + car->getNumber() + ") has delimiter in location field: "
//						+ carLocationName); // NOI18N
             carLocationName = ESC + car->getLocationName() + ESC;
         }
         carTrackName = car->getTrackName();
         if (carTrackName.contains(del)) {
//				log->debug("Car (" + car->getRoadName() + " " + car->getNumber() + ") has delimiter in track field: "
//						+ carTrackName); // NOI18N
             carTrackName = ESC + car->getTrackName() + ESC;
         }
         // only export value field if value has been set.
         value = "";
         if (car->getValue()!=(Car::NONE)) {
             value = ESC + car->getValue() + ESC;
         }
         comment = "";
         if (car->getComment()!=(Car::NONE)) {
             comment = ESC + car->getComment() + ESC;
         }
         line = car->getNumber() + del + car->getRoadName() + del + carType + del + car->getLength() + del
                 + car->getWeight() + del + car->getColor() + del + car->getOwner() + del + car->getBuilt() + del
                 + carLocationName + ",-," + carTrackName + del + car->getLoadName() + del + car->getKernelName()
                 + del + car->getMoves() + del + value + del + comment; // NOI18N
         fileOut->println(line);
     }
     fileOut->flush();
     fileOut->close();
     log->info("Exported " + QString::number(carList->size()) + " cars to file " + defaultOperationsFilename());
//     JOptionPane.showMessageDialog(NULL, MessageFormat.format(tr("ExportedCarsToFile"), new Object[]{
//         carList.size(), defaultOperationsFilename()}), tr("ExportComplete"),
//             JOptionPane.INFORMATION_MESSAGE);
     QMessageBox::information(NULL, tr("Export complete"), tr("Exported %1 cars to file: %2").arg(carList->size()).arg(defaultOperationsFilename()));
 }

 // Operation files always use the same directory
 /*public*/ /*static*/ QString ExportCars::defaultOperationsFilename() {
     return OperationsSetupXml::getFileLocation() + OperationsSetupXml::getOperationsDirectoryName() + File::separator
             + getOperationsFileName();
 }

 /*public*/ /*static*/ void ExportCars::setOperationsFileName(QString name) {
     OperationsFileName = name;
 }

 /*public*/ /*static*/ QString ExportCars::getOperationsFileName() {
     return OperationsFileName;
 }

 /*private*/ /*static*/ QString ExportCars::OperationsFileName = "ExportOperationsCarRoster.csv"; // NOI18N
}
