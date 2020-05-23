#ifndef TIMETABLECSVIMPORT_H
#define TIMETABLECSVIMPORT_H

#include <QObject>
#include "timetabledatamanager.h"

class Logger;
class File;
namespace TimeTable
{
 class TimeTableCsvImport : public QObject
 {
  Q_OBJECT
 public:
  TimeTableCsvImport(QObject *parent= nullptr);
  /*public*/ QList<QString> importCsv(File* file, QObject* parent = nullptr) throw (IOException);


 signals:

 public slots:

 private:
  static Logger* log;
  TimeTableDataManager* tdm = TimeTableDataManager::getDataManager();
  bool errorOccurred;
  QList<QString> importFeedback = QList<QString>();
  FileReader fileReader;
  BufferedReader bufferedReader;
  CSVParser csvFile;

  int recordNumber = 0;
  int layoutId = 0;       //Current layout object id
  int segmentId = 0;      //Current segment object id
  int scheduleId = 0;     //Current schedule object id
  int trainId = 0;        //Current train object id
  List<Integer> trainTypes = new ArrayList<>();    //List of train type ids, translates the relative type occurrence to a type id
  List<Integer> stations = new ArrayList<>();      //List of stations ids, translates the relative station occurence to a station id

 };
}
#endif // TIMETABLECSVIMPORT_H
