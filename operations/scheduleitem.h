#ifndef SCHEDULEITEM_H
#define SCHEDULEITEM_H

#include <QObject>

class QDomElement;
class QDomDocument;
class Logger;
class SwingPropertyChangeSupport;
class PropertyChangeEvent;
namespace Operations
{
 class Location;
 class Track;
 class ScheduleItem : public QObject
 {
  Q_OBJECT
 public:
  explicit ScheduleItem(QString id, QString type, QObject *parent = 0);
  SwingPropertyChangeSupport* pcs;// = new java.beans.SwingPropertyChangeSupport(this,this);
  /*public*/ static /*final*/ QString NONE;//= ""; // NOI18N
  /*public*/ static /*final*/ QString TRAIN_SCHEDULE_CHANGED_PROPERTY;//= "trainScheduleId"; // NOI18N
  /*public*/ static /*final*/ QString COUNT_CHANGED_PROPERTY;//= "scheduleItemCount"; // NOI18N
  /*public*/ static /*final*/ QString TYPE_CHANGED_PROPERTY;//= "scheduleItemType"; // NOI18N
  /*public*/ static /*final*/ QString ROAD_CHANGED_PROPERTY;//= "scheduleItemRoad"; // NOI18N
  /*public*/ static /*final*/ QString LOAD_CHANGED_PROPERTY;//= "scheduleItemLoad"; // NOI18N
  /*public*/ static /*final*/ QString DESTINATION_CHANGED_PROPERTY;//= "scheduleItemDestination"; // NOI18N
  /*public*/ static /*final*/ QString DESTINATION_TRACK_CHANGED_PROPERTY;//= "scheduleItemDestinationTrack"; // NOI18N
  /*public*/ static /*final*/ QString WAIT_CHANGED_PROPERTY;//= "scheduleItemWait"; // NOI18N
  /*public*/ static /*final*/ QString HITS_CHANGED_PROPERTY;//= "scheduleItemHits"; // NOI18N
  /*public*/ static /*final*/ QString DISPOSE;//= "scheduleItemDispose"; // NOI18N
  /*public*/ QString getId();
  /*public*/ QString getTypeName();
  /*public*/ void setTypeName(QString type);
  /*public*/ QString getRandom();
  /*public*/ void setRandom(QString value);
  /*public*/ QString getSetoutTrainScheduleId();
  /*public*/ void setSetoutTrainScheduleId(QString id);
  /*public*/ QString getPickupTrainScheduleId() ;
  /*public*/ void setPickupTrainScheduleId(QString id);
  /*public*/ QString getRoadName();
  /*public*/ void setRoadName(QString road) ;
  /*public*/ void setReceiveLoadName(QString load);
  /*public*/ QString getReceiveLoadName();
  /*public*/ void setShipLoadName(QString load);
  /*public*/ QString getShipLoadName();
  /*public*/ int getSequenceId();
  /*public*/ void setSequenceId(int sequence);
  /*public*/ int getCount() ;
  /*public*/ void setCount(int count) ;
  /*public*/ int getWait() ;
  /*public*/ void setWait(int wait) ;
  /*public*/ int getHits() ;
  /*public*/ void setHits(int hit);
  /*public*/ Location* getDestination() ;
  /*public*/ void setDestination(Location* destination);
  /*public*/ QString getDestinationName();
  /*public*/ QString getDestinationId();
  /*public*/ Track* getDestinationTrack();
  /*public*/ void setDestinationTrack(Track* track);
  /*public*/ QString getDestinationTrackName();
  /*public*/ QString getDestinationTrackId() ;
  /*public*/ void setComment(QString comment);
  /*public*/ QString getComment();
  /*public*/ void copyScheduleItem (ScheduleItem* si);
  /*public*/ void dispose() ;
  /*public*/ ScheduleItem(QDomElement e);
  /*public*/ QDomElement store(QDomDocument doc);

 signals:

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

   private:
   Logger* log;
   void common();

   protected:
   /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);
  /*protected*/ QString _id;//= NONE;
  /*protected*/ int _sequenceId;//= 0; // used to determine order in schedule
  /*protected*/ QString _random;//= NONE; // used to determine if random set out is needed
  /*protected*/ QString _setoutTrainScheduleId;//= NONE; // which day of the week to deliver car
  /*protected*/ QString _type;//= NONE; // the type of car
  /*protected*/ QString _road;//= NONE; // the car road
  /*protected*/ QString _load;//= NONE; // the car load requested
  /*protected*/ QString _ship;//= NONE; // the car load shipped
  /*protected*/ Location* _destination;//= null; // car destination after load
  /*protected*/ Track* _trackDestination;//= null;// car destination track after load
  /*protected*/ QString _pickupTrainScheduleId;//= NONE; // which day of the week to pickup car
  /*protected*/ int _count;//= 1; // the number of times this type of car must be dropped
  /*protected*/ int _wait;//= 0; // how many trains this car must wait before being picked up
  /*protected*/ int _hits;//= 0; // how many times this schedule item has been used
  /*protected*/ QString _comment;//= NONE;

 };
}
#endif // SCHEDULEITEM_H
