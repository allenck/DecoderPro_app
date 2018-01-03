#ifndef EXPORTCARS_H
#define EXPORTCARS_H

#include "xmlfile.h"
namespace Operations
{
 class ExportCars : public XmlFile
 {
  Q_OBJECT
 public:
  ExportCars();
  /*public*/ void setDeliminter(QString delimiter);
  /*public*/ void writeOperationsCarFile();
  /*public*/ void writeFile(QString name);
  /*public*/ static QString defaultOperationsFilename();
  /*public*/ static void setOperationsFileName(QString name);
  /*public*/ static QString getOperationsFileName();
 private:
  Logger* log;
  /*private*/ static QString OperationsFileName;// = "ExportOperationsCarRoster.csv"; // NOI18N
  static /*final*/ QString ESC;// = "\""; // escape character NOI18N
  /*private*/ QString del;// = ","; // delimiter

 };
}
#endif // EXPORTCARS_H
