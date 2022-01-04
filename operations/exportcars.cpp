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
#include "instancemanager.h"
#include <QFile>
#include "joptionpane.h"
#include "loggerfactory.h"
#include "division.h"

namespace Operations
{
 /**
  * Exports the car roster into a comma delimitated file (CSV).
  *
  * @author Daniel Boudreau Copyright (C) 2010, 2011
  * @version $Revision: 29118 $
  *
  */
 ///*/*public*/ */ class ExportCars extends XmlFile {

 /*protected*/ /*static*/ /*final*/ QString ExportCars::LOCATION_TRACK_SEPARATOR = "-";

 /*public*/  ExportCars::ExportCars(QList<Car*> carList, QObject* parent) : XmlFile(parent){
        _carList = carList;
 }

 /**
  * Create CSV file based on the car list.
  */
 /*public*/  void ExportCars::writeOperationsCarFile() {
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

 /**
  * Any changes to the column order should also be made to the ImportCars.java
  * file.
  *
  * @param name file name
  */
 /*private*/ void ExportCars::writeFile(QString name) {
   log->debug(tr("writeFile %1").arg(name));
   // This is taken in large part from "Java and XML" page 368
   File* file = findFile(name);
   if (file == nullptr) {
       file = new File(name);
   }

     QFile *qf = file->toQfile();
     if(!qf->open(QIODevice::Truncate|QIODevice::WriteOnly ))
      throw new IOException(tr("Can't open foroutput: %s").arg(qf->fileName()));
     QTextStream* stream = new QTextStream(qf);
    try
    {
     CSVPrinter* fileOut = new EC_CSVPrinter(stream,
             CSVFormat::DEFAULT, this);

         // create header
         fileOut->printRecord(QVariantList {tr("Number"),
                 tr("Road"),
                 tr("Type"),
                 tr("Length"),
                 tr("Weight"),
                 tr("Color"),
                 tr("Owner"),
                 tr("Built"),
                 tr("Location"),
                 LOCATION_TRACK_SEPARATOR,
                 tr("Track"),
                 tr("Load"),
                 tr("Kernel"),
                 tr("Moves"),
                 Setup::getValueLabel(),
                 tr("Comment"),
                 tr("Miscellaneous"),
                 tr("Extensions"),
                 tr("Wait"),
                 tr("Pickup"),
                 tr("Last"),
                 tr("RWELocation"),
                 LOCATION_TRACK_SEPARATOR,
                 tr("Track"),
                 tr("RWELoad"),
                 tr("RWLLocation"),
                 LOCATION_TRACK_SEPARATOR,
                 tr("Track"),
                 tr("RWLLoad"),
                 tr("Division"),
                 tr("Train"),
                 tr("Destination"),
                 LOCATION_TRACK_SEPARATOR,
                 tr("Track"),
                 tr("FinalDestination"),
                 LOCATION_TRACK_SEPARATOR,
                 tr("Track"),
                 tr( "RFID_Tag")});

         // store car attributes
         for (Car* car : _carList) {
             fileOut->printRecord(QVariantList {car->getNumber(),
                     car->getRoadName(),
                     car->getTypeName(),
                     car->getLength(),
                     car->getWeight(),
                     car->getColor(),
                     car->getOwner(),
                     car->getBuilt(),
                     car->getLocationName(),
                     LOCATION_TRACK_SEPARATOR,
                     car->getTrackName(),
                     car->getLoadName(),
                     car->getKernelName(),
                     car->getMoves(),
                     car->getValue(),
                     car->getComment(),
                     car->isOutOfService() ? tr("OutOfService") : "",
                     car->getTypeExtensions(),
                     car->getWait(),
                     car->getPickupScheduleName(),
                     car->getLastDate(),
                     car->getReturnWhenEmptyDestinationName(),
                     LOCATION_TRACK_SEPARATOR,
                     car->getReturnWhenEmptyDestTrackName(),
                     car->getReturnWhenEmptyLoadName(),
                     car->getReturnWhenLoadedDestinationName(),
                     LOCATION_TRACK_SEPARATOR,
                     car->getReturnWhenLoadedDestTrackName(),
                     car->getReturnWhenLoadedLoadName(),
                     car->getDivision()->getName(),
                     car->getTrainName(),
                     car->getDestinationName(),
                     LOCATION_TRACK_SEPARATOR,
                     car->getDestinationTrackName(),
                     car->getFinalDestinationName(),
                     LOCATION_TRACK_SEPARATOR,
                     car->getFinalDestinationTrackName(),
                     car->getRfid()});
         }
         fileOut->flush();
         fileOut->close();
         log->info(tr("Exported %1} cars to file %2").arg(_carList.size()).arg(defaultOperationsFilename()));
         JOptionPane::showMessageDialog(nullptr, tr("Exported %1 cars to file: %2").arg(_carList.size()).arg(defaultOperationsFilename()),
                                        tr("Export Complete"),
                 JOptionPane::INFORMATION_MESSAGE);
     } catch (IOException* e) {
         log->error(tr("Can not open export cars CSV file: %1").arg(file->getName()));
         JOptionPane::showMessageDialog(nullptr,
                tr("Exported %1 cars to file: %2").arg( 0).arg(defaultOperationsFilename() ),
                 tr("Export Failed"), JOptionPane::ERROR_MESSAGE);
     }
 }

 // Operation files always use the same directory
 /*public*/  /*static*/ QString ExportCars::defaultOperationsFilename() {
     return OperationsSetupXml::getFileLocation()
             + OperationsSetupXml::getOperationsDirectoryName()
             + File::separator
             + getOperationsFileName();
 }

 /*public*/  /*static*/ void ExportCars::setOperationsFileName(QString name) {
     operationsFileName = name;
 }

 /*public*/  /*static*/ QString ExportCars::getOperationsFileName() {
     return operationsFileName;
 }
 /*private*/ /*static*/ QString ExportCars::operationsFileName = "ExportOperationsCarRoster.csv"; // NOI18N
 /*private*/ /*final*/ /*static*/ Logger* ExportCars::log = LoggerFactory::getLogger("ExportCars");

}
