#ifndef OPERATIONS_EXPORTLOCATIONS_H
#define OPERATIONS_EXPORTLOCATIONS_H

#include <xmlfile.h>
#include <QObject>
#include "instancemanager.h"
#include "locationmanager.h"
#include "trainmanager.h"
#include "csvprinter.h"
#include "bufferedwriter.h"
#include "outputstreamwriter.h"
#include "fileoutputstream.h"
#include "csvformat.h"
#include "routemanager.h"

namespace Operations {

 class ExportLocations : public XmlFile
 {
  public:
   explicit ExportLocations(QObject *parent = nullptr) {}
   /*public*/  void writeOperationsLocationFile();
   /*public*/  static QString defaultOperationsFilename();
   /*public*/  static void setOperationsFileName(QString name);
   /*public*/  static QString getOperationsFileName();
   /*public*/  void writeFile(QString name);

  private:
   TrainManager* trainManager = (TrainManager*)InstanceManager::getDefault("Operations::TrainManager");
   RouteManager* routeManager = (RouteManager*)InstanceManager::getDefault("Operations::RouteManager");
   LocationManager* locationManager = (LocationManager*)InstanceManager::getDefault("Operations::LocationManager");
   static Logger* log;
   /*private*/ static QString operationsFileName;// = "ExportOperationsLocationRoster.csv"; // NOI18N

 };


 class EL_CSVPrinter : public CSVPrinter
 {
   Q_OBJECT
   ExportLocations* el;
  public:
   EL_CSVPrinter(QTextStream* w, CSVFormat* f, ExportLocations* el) : CSVPrinter(w, f) {this->el = el;}
 };
} // namespace Operations

#endif // OPERATIONS_EXPORTLOCATIONS_H
