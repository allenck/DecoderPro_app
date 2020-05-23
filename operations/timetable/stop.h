#ifndef STOP_H
#define STOP_H

#include <QObject>
namespace TimeTable
{

class TimeTableDataManager;
class Stop : public QObject
{
 Q_OBJECT
public:
 /*public*/ Stop(int trainId, int seq, QObject* parent = nullptr);
 /*public*/ Stop(int stopId, int trainId, int stationId, int seq, int duration,
         int nextSpeed, int arriveTime, int departTime, int stagingTrack, QString stopNotes, QObject* parent = nullptr) ;
 /*public*/ int getStopId();
 /*public*/ int getTrainId() ;
 /*public*/ int getStationId();
 /*public*/ void setStationId(int newStationId);
 /*public*/ int getSeq();
 /*public*/ void setSeq(int newSeq);
 /*public*/ int getDuration();
 /*public*/ void setDuration(int newDuration);
 /*public*/ int getNextSpeed();
 /*public*/ void setNextSpeed(int newNextSpeed);
 /*public*/ int getArriveTime();
 /*public*/ void setArriveTime(int newArriveTime);
 /*public*/ int getDepartTime();
 /*public*/ void setDepartTime(int newDepartTime);
 /*public*/ int getStagingTrack();
 /*public*/ void setStagingTrack(int newStagingTrack);
 /*public*/ QString getStopNotes();
 /*public*/ void setStopNotes(QString newNotes);
 /*public*/ QString toString();

signals:

public slots:

private:
 TimeTableDataManager* _dm;// = TimeTableDataManager::getDataManager();

 /*private*/ /*final*/ int _stopId;
 /*private*/ /*final*/ int _trainId;
 /*private*/ int _stationId = 0;
 /*private*/ int _seq = 0;
 /*private*/ int _duration = 0;
 /*private*/ int _nextSpeed = 0;
 /*private*/ int _arriveTime = 0;
 /*private*/ int _departTime = 0;
 /*private*/ int _stagingTrack = 0;
 /*private*/ QString _stopNotes = "";
};
}
#endif // STOP_H
