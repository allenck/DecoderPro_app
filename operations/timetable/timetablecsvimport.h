#ifndef TIMETABLECSVIMPORT_H
#define TIMETABLECSVIMPORT_H

#include <QObject>
#include "timetabledatamanager.h"


class CSVParser;
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
  //FileReader fileReader;
  QTextStream* bufferedReader = nullptr;
  CSVParser* csvFile;

  int recordNumber = 0;
  int layoutId = 0;       //Current layout object id
  int segmentId = 0;      //Current segment object id
  int scheduleId = 0;     //Current schedule object id
  int trainId = 0;        //Current train object id
  QList<int> trainTypes = QList<int>();    //List of train type ids, translates the relative type occurrence to a type id
  QList<int> stations = QList<int>();      //List of stations ids, translates the relative station occurence to a station id

  void doLayout(QStringList values);
  void doTrainType(QStringList values);
  void doTrainType(QStringList values);
  void doSegment(QStringList values);
  void doStation(QStringList values);
  void doSchedule(QStringList values);
  void doTrain(QStringList values);
  void doStop(QStringList values);
  int convertToInteger(QString number);
  double convertToDouble(QString number);
  QString pack(QStringList const& list);

 };
}
#endif // TIMETABLECSVIMPORT_H
