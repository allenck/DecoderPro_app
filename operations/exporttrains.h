#ifndef EXPORTTRAINS_H
#define EXPORTTRAINS_H

#include "xmlfile.h"
namespace Operations
{
 class ExportTrains : public XmlFile
 {
 public:
  ExportTrains();
  /*public*/ void setDeliminter(QString delimiter);
  /*public*/ void writeOperationsCarFile();
  /*public*/ void writeFile(QString name);
  /*public*/ static QString defaultOperationsFilename();
  /*public*/ static void setOperationsFileName(QString name);
  /*public*/ static QString getOperationsFileName();

 private:
  Logger* log;
  static /*final*/ QString ESC;// = "\""; // escape character NOI18N
  /*private*/ QString del;// = ","; // delimiter
  /*private*/ static QString OperationsFileName;// = "ExportOperationsTrainRoster.csv"; // NOI18N

 };
}
#endif // EXPORTTRAINS_H
