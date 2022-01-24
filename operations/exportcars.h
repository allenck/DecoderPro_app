#ifndef EXPORTCARS_H
#define EXPORTCARS_H

#include "xmlfile.h"
#include "csvformat.h"
#include "csvprinter.h"

namespace Operations
{
 class Car;
 class ExportCars : public XmlFile
 {
  Q_OBJECT
 public:
  ExportCars(QList<Car*> carList, QObject* parent= nullptr);
  /*public*/  void writeOperationsCarFile();
  /*public*/  static QString defaultOperationsFilename();
  /*public*/  static void setOperationsFileName(QString name);
  /*public*/  static QString getOperationsFileName();

 private:
  static Logger* log;
  /*private*/ static QString operationsFileName;// = "ExportOperationsCarRoster.csv"; // NOI18N
  QList<Car*> _carList;
  /*private*/ void writeFile(QString name);

  protected:
  /*protected*/ static /*final*/ QString LOCATION_TRACK_SEPARATOR;// = "-";

 };

 class EC_CSVPrinter : public CSVPrinter
 {
   Q_OBJECT
   ExportCars* ec;
  public:
   EC_CSVPrinter(QTextStream* w, CSVFormat* f, ExportCars* ec) : CSVPrinter(w, f) {this->ec = ec;}
 };
}
#endif // EXPORTCARS_H
