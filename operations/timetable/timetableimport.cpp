#include "timetableimport.h"
#include "loggerfactory.h"
#include "file.h"
#include "timetabledatamanager.h"
#include "filereader.h"
#include <QTextStream>
#include <QFile>
#include <QStringList>
#include "layout.h"
#include "station.h"
#include "segment.h"
#include "ttschedule.h"
#include "tttrain.h"
#include <QString>

namespace TimeTable
{
 TimeTableImport::TimeTableImport(QObject *parent) : QObject(parent)
 {

 }
 // /*public*/ class TimeTableImport {

 /*public*/ void TimeTableImport::importSgn(TimeTableDataManager* dm, File* file) /*throw (IOException)*/ {
  _dm = dm;
  _dm->setLockCalculate(true);
  try {
      //fileReader = new FileReader(file);
   f = new QFile(file->getPath());
   if(f->open(QFile::ReadOnly)) {
       in = new QTextStream(f);
   }
   else throw  new FileNotFoundException();

   //bufferedReader = new BufferedReader(fileReader);

   int row = 1;
   QString currType = "";
   int stationCount = 0;
   int typeCount = 0;
   int trainCount = 0;
   int stopCount = 0;
   int stopSeq = 0;

   while ((line =/* bufferedReader*/in->readLine()) != "") {
       // Split line and remove double quotes
       QStringList lineStrings = line.split(QRegExp(",(?=([^\"]*\"[^\"]*\")*[^\"]*$)"));  // NOI18N
       for (int i = 0; i < lineStrings.length(); i++) {
           lineStrings[i] = lineStrings[i].replace("\"", "");
       }

       switch (row) {
           case 1:
               log->info(tr("SchedGen Import, version: %1").arg(lineStrings[0]));  // NOI18N
               break;

           case 2:
               createLayout(lineStrings);
               createSegment(lineStrings);
               createSchedule(lineStrings);
               break;

           case 3:
               stationCount = lineStrings.at(0).toInt();
               currType = "Station";  // NOI18N
               break;

           default:
               if (stationCount > 0) {
                   createStation(lineStrings);
                   stationCount--;
                   break;
               }

               if (currType == ("Station")) {  // NOI18N
                   currType = "Type";  // NOI18N
                   typeCount = lineStrings.at(0).toInt() + 1;
                   break;
               }
               if (typeCount > 0) {
                   createTrainType(lineStrings);
                   typeCount--;
                   break;
               }

               if (currType == ("Type")) {  // NOI18N
                   currType = "Train";  // NOI18N
                   trainCount = lineStrings[0].toInt() + 1;
                   stopCount = 0;
                   break;
               }
               if (trainCount > 0) {
                   if (stopCount == 0) {
                       // Create train record
                       createTrain(lineStrings);

                       stopCount = -1;
                       break;
                   }
                   if (stopCount == -1) {
                       stopCount = lineStrings[0].toInt();
                       stopSeq = 1;
                       _routeFirst = 0;
                       _routeLast = 0;
                       break;

                   }
                   if (stopCount > 0) {
                       // create stop record
                       createStop(lineStrings, stopSeq);

                       stopCount--;
                       stopSeq++;
                       if (stopCount == 0) {
                           int routeDur;
                           if (_routeLast > _routeFirst) {
                               routeDur = _routeLast - _routeFirst;
                           } else {
                               routeDur = 1440 - _routeFirst + _routeLast;
                           }
                           _dm->getTrain(_trainId)->setRouteDuration(routeDur);

                           trainCount--;
                       }
                       break;
                   }
               }
       }
       row++;
   }
  } catch (IOException* e) {
      log->error("Error reading file: " + e->getMessage());  // NOI18N
  }
//        finally {
//            if(bufferedReader != null) {
//               bufferedReader.close();
//            }
//            if(fileReader != null) {
//               fileReader.close();
//            }
//        }
  f->close();
  _dm->setLockCalculate(false);
 }

 void TimeTableImport::createLayout(QStringList lineStrings) {
// "Sierra Western","Default","08/01/11",0,24,"5:1","HO",5
//         _layoutId = layoutId;
//         _layoutName = layoutName;
//         _scale = scale;
//         _fastClock = fastClock;
//         _throttles = throttles;
//         _metric = metric;
//         String clockString = lineStrings[5].replace("\"", "");
     QStringList clockComp = lineStrings[5].split(":");  // NOI18N
     int clock = clockComp[0].toInt();
     int throttles = lineStrings[7].toInt();
     _layoutId = _dm->getNextId("Layout");  // NOI18N
     Layout* layout = new Layout(_layoutId,
             lineStrings[0],
             ScaleManager::getScale(lineStrings[6]),
             clock,
             throttles,
             false);
     _dm->addLayout(_layoutId, layout);
 }

 void TimeTableImport::createTrainType(QStringList lineStrings) {
// for (int i = 0; i < lineStrings.length; i++) {
//     log.info("@@ type: {}", lineStrings[i]);
// }
// "Freight, general",32768
//         _typeId = typeId;
//         _layoutId = layoutId;
//         _typeName = typeName;
//          typeColor

     int colorInt = lineStrings.at(lineStrings.length() - 1).toInt();
     QString colorStr = QString::asprintf("#%06X", colorInt);  // NOI18N
     QString typeName = lineStrings[0];
     int typeId = _dm->getNextId("TrainType");  // NOI18N
     TrainType* trainType = new TrainType(typeId,
             _layoutId,
             typeName,
             colorStr);
     _dm->addTrainType(typeId, trainType);
     _typeIds.insert(typeName, typeId);
 }

 void TimeTableImport::createSegment(QStringList /*lineStrings*/) {
//         _segmentId = segmentId;
//         _layoutId = layoutId;
//         _segmentName = segmentName;
     _segmentId = _dm->getNextId("Segment");  // NOI18N
     Segment* segment = new Segment(_segmentId,
             _layoutId,
             "Mainline");  // NOI18N
     _dm->addSegment(_segmentId, segment);
 }

 void TimeTableImport::createStation(QStringList lineStrings) {
// "Butte",0,0,9,"N"
//         D S St Dbl
//         _stationId = stationId;
//         _segmentId = segmentId;
//         _stationName = stationName;
//         _distance = distance;
//         _doubleTrack = doubleTrack;
//         _sidings = sidings;
//         _staging = staging;
     int stationId = _dm->getNextId("Station");  // NOI18N
     Station* station = new Station(stationId,
             _segmentId,
             lineStrings[0],
             lineStrings.at(1).toDouble(),
             (lineStrings[4] == ("N")) ? false : true,
             lineStrings[2].toInt(),
             lineStrings[3].toInt());
     _dm->addStation(stationId, station);
     _stationIds.append(stationId);
 }

 void TimeTableImport::createSchedule(QStringList lineStrings) {
// "Sierra Western","Default","08/01/11",0,24,"5:1","HO",5

//          _scheduleId = scheduleId;
//         _layoutId = layoutId;
//         _scheduleName = scheduleName;
//         _effDate = effDate;
//         _startHour = startHour;
//         _duration = duration;
     _scheduleId = _dm->getNextId("Schedule");  // NOI18N
     TTSchedule* schedule = new TTSchedule(_scheduleId,
             _layoutId,
             lineStrings[1],
             lineStrings[2],
             lineStrings[3].toInt(),
             lineStrings[4].toInt());
     _dm->addSchedule(_scheduleId, schedule);
 }

 void TimeTableImport::createTrain(QStringList lineStrings) {
// "201","Expediter","Freight,priority",0,740,0,""
//  name  desc        type              speed start throttle notes
//         _trainId = trainId;
//         _scheduleId = scheduleId;
//         _typeId = typeId;
//         _trainName = trainName;
//         _trainDesc = trainDesc;
//         _defaultSpeed = defaultSpeed;
//         _startTime = startTime;
//         _throttle = throttle;
//         _routeDuration = routeDuration;
//         _trainNotes = trainNotes;
     QString notes = lineStrings[6];

     int typeId = _typeIds.value(lineStrings[2]);
     _trainId = _dm->getNextId("Train");  // NOI18N
     TTTrain* train = new TTTrain(_trainId,
             _scheduleId,
             typeId,
             lineStrings[0],
             lineStrings[1],
             lineStrings[3].toInt(),
             lineStrings[4].toInt(),
             lineStrings[5].toInt(),
             0,
             notes);
     _dm->addTrain(_trainId, train);
 }

 void TimeTableImport::createStop(QStringList lineStrings, int seq) {
// 13,0,30,555,555,0,""
// ST D NX  A   D  T  N
//         _trainId = trainId;
//         _stationId = stationId;
//         _seq = seq;
//         _duration = duration;
//         _nextSpeed = nextSpeed;
//         _arriveTime = arriveTime;
//         _departTime = departTime;
//         _stagingTrack = stagingTrack;
//         _stopNotes = stopNotes;


     int _stopId = _dm->getNextId("Stop");  // NOI18N
     Stop* stop = new Stop(_stopId,
             _trainId,
             _stationIds.value(lineStrings[0].toInt() - 1),
             seq,
             lineStrings[1].toInt(),
             lineStrings[2].toInt(),
             lineStrings[3].toInt(),
             lineStrings[4].toInt(),
             lineStrings[5].toInt(),
             lineStrings[6]);
     _dm->addStop(_stopId, stop);

     if (seq == 1) {
         _routeFirst = lineStrings[3].toInt();
     }
     _routeLast = lineStrings[4].toInt();
 }

 /*private*/ /*final*/ /*static*/ Logger* TimeTableImport::log = LoggerFactory::getLogger("TimeTableImport");

}
