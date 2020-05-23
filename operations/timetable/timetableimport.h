#ifndef TIMETABLEIMPORT_H
#define TIMETABLEIMPORT_H

#include <QObject>
#include "exceptions.h"
#include <QTextStream>

class QFile;
class File;
//class BufferedReader;
//class FileReader;
class Logger;
namespace TimeTable
{
 class TimeTableDataManager;

 class TimeTableImport : public QObject
 {
  Q_OBJECT
 public:
  explicit TimeTableImport(QObject *parent = nullptr);
  /*public*/ void importSgn(TimeTableDataManager* dm, File* file) throw (IOException);

 signals:

 public slots:

 private:
  static Logger* log;
//  BufferedReader* bufferedReader;
//  FileReader* fileReader;
  QFile* f;
  QTextStream* in =nullptr;
  QString line;
  TimeTableDataManager* _dm;
  int _layoutId = 0;
  int _segmentId = 0;
  int _scheduleId = 0;
  int _trainId = 0;
  int _routeFirst = 0;
  int _routeLast = 0;
  QList<int> _stationIds = QList<int>();
  QMap<QString, int> _typeIds = QMap<QString, int>();

  void createLayout(QStringList lineStrings);
  void createSegment(QStringList lineStrings);
  void createTrainType(QStringList lineStrings);
  void createStation(QStringList lineStrings);
  void createSchedule(QStringList lineStrings);
  void createTrain(QStringList lineStrings);
  void createStop(QStringList lineStrings, int seq);

 };
}
#endif // TIMETABLEIMPORT_H
