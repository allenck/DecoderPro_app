#ifndef EXPORTTIMETABLE_H
#define EXPORTTIMETABLE_H

#include "xmlfile.h"

class Logger;
namespace TimeTable
{

 class ExportTimetable : public XmlFile
 {
  Q_OBJECT
 public:
  explicit ExportTimetable(QObject *parent = nullptr);
  /*public*/ void writeOperationsTimetableFile();

  /*public*/ File* getExportFile();
  /*public*/ static QString defaultOperationsFilename();
  /*public*/ static void setOperationsFileName(QString name);
  /*public*/ static QString getOperationsFileName();

 signals:

 public slots:

 private:
  static Logger* log;
  /*private*/ static QString operationsFileName;// = "ExportOperationsTimetable.csv"; // NOI18N

 };
}
#endif // EXPORTTIMETABLE_H
