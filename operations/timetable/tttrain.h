#ifndef TRAIN_H
#define TRAIN_H

#include <QObject>
#include "timetabledatamanager.h"

namespace TimeTable
{
class TimeTableDataManager;
class TTTrain : public QObject
{
 Q_OBJECT
public:
 /*public*/ TTTrain(int scheduleId,QObject *parent = nullptr);
 /*public*/ TTTrain(int trainId, int scheduleId, int typeId, QString trainName, QString trainDesc,
             int defaultSpeed, int startTime, int throttle, int routeDuration, QString trainNotes, QObject *parent=nullptr);
 /*public*/ int getTrainId();
 /*public*/ int getScheduleId() ;
 /*public*/ int getTypeId();
 /*public*/ void setTypeId(int newType);
 /*public*/ QString getTrainName() ;
 /*public*/ void setTrainName(QString newName);
 /*public*/ QString getTrainDesc();
 /*public*/ void setTrainDesc(QString newDesc);
 /*public*/ int getDefaultSpeed();
 /*public*/ void setDefaultSpeed(int newSpeed);
 /*public*/ int getStartTime();
 /*public*/ void setStartTime(int newStartTime);
 /*public*/ int getThrottle();
 /*public*/ void setThrottle(int newThrottle);
 /*public*/ int getRouteDuration();
 /*public*/ void setRouteDuration(int newRouteDuration);
 /*public*/ QString getTrainNotes();
 /*public*/ void setTrainNotes(QString newNotes);
 /*public*/ QString toString();

signals:

public slots:

private:
 /*private*/    TimeTableDataManager* _dm;// = TimeTableDataManager::getDataManager();

 /*private*/ /*final*/ int _trainId;
 /*private*/ /*final*/ int _scheduleId;
 /*private*/ int _typeId = 0;
 /*private*/ QString _trainName = "NT";  // NOI18N
 /*private*/ QString _trainDesc = "New Train";  // NOI18N
 /*private*/ int _defaultSpeed = 1;
 /*private*/ int _startTime = 0;
 /*private*/ int _throttle = 0;
 /*private*/ int _routeDuration = 0;
 /*private*/ QString _trainNotes = "";

};
}
#endif // TRAIN_H
