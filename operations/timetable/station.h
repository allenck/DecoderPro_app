#ifndef STATION_H
#define STATION_H

#include <QObject>
namespace TimeTable
{

class TimeTableDataManager;
class Station : public QObject
{
 Q_OBJECT
public:
 /*public*/ Station(int segmentId,QObject *parent = nullptr);
 /*public*/ Station(int stationId, int segmentId, QString stationName, double distance, bool doubleTrack, int sidings, int staging,QObject *parent= nullptr);
 /*public*/ int getStationId() ;
 /*public*/ int getSegmentId();
 /*public*/ QString getStationName();
 /*public*/ void setStationName(QString newName);
 /*public*/ double getDistance();
 /*public*/ void setDistance(double newDistance);
 /*public*/ bool getDoubleTrack();
 /*public*/ void setDoubleTrack(bool newDoubleTrack);
 /*public*/ int getSidings();
 /*public*/ void setSidings(int newSidings);
 /*public*/ int getStaging();
 /*public*/ void setStaging(int newStaging);
 /*public*/ QString toString();

signals:

public slots:
private:
 TimeTableDataManager* _dm;// = TimeTableDataManager::getDataManager();

 /*private*/ /*final*/ int _stationId;
 /*private*/ /*final*/ int _segmentId;
 /*private*/ QString _stationName = "New Station";  // NOI18N
 /*private*/ double _distance = 1.0;
 /*private*/ bool _doubleTrack = false;
 /*private*/ int _sidings = 0;
 /*private*/ int _staging = 0;

};
}
#endif // STATION_H
