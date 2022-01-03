#include "scheduleitem.h"
#include "propertychangesupport.h"
#include "control.h"
#include "propertychangeevent.h"
#include "logger.h"
#include "track.h"
#include "location.h"
#include "xml.h"
#include "locationmanager.h"
#include "instancemanager.h"

namespace Operations
{
/**
 * Represents one schedule item of a schedule
 *
 * @author Daniel Boudreau Copyright (C) 2009, 2010, 2013, 2014
 * @version $Revision: 29636 $
 */
///*public*/ class ScheduleItem implements java.beans.PropertyChangeListener {

 /*public*/ /*static*/ /*final*/ QString ScheduleItem::NONE = ""; // NOI18N


 /*public*/ /*static*/ /*final*/ QString ScheduleItem::TRAIN_SCHEDULE_CHANGED_PROPERTY = "trainScheduleId"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString ScheduleItem::COUNT_CHANGED_PROPERTY = "scheduleItemCount"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString ScheduleItem::TYPE_CHANGED_PROPERTY = "scheduleItemType"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString ScheduleItem::ROAD_CHANGED_PROPERTY = "scheduleItemRoad"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString ScheduleItem::LOAD_CHANGED_PROPERTY = "scheduleItemLoad"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString ScheduleItem::DESTINATION_CHANGED_PROPERTY = "scheduleItemDestination"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString ScheduleItem::DESTINATION_TRACK_CHANGED_PROPERTY = "scheduleItemDestinationTrack"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString ScheduleItem::WAIT_CHANGED_PROPERTY = "scheduleItemWait"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString ScheduleItem::HITS_CHANGED_PROPERTY = "scheduleItemHits"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString ScheduleItem::DISPOSE = "scheduleItemDispose"; // NOI18N

 /**
  *
  * @param id
  * @param type car type for schedule
  */
 /*public*/ ScheduleItem::ScheduleItem(QString id, QString type, QObject* /*parent*/ ) {
  common();
     log->debug(tr("New schedule item, car type (%1) id: %2").arg(type).arg(id));
     _type = type;
     _id = id;
 }
 void ScheduleItem::common()
 {
  log = new Logger("ScheduleItem");
  pcs = new PropertyChangeSupport(this);
   _id = NONE;
  _sequenceId = 0; // used to determine order in schedule
   _random = NONE; // used to determine if random set out is needed
   _setoutTrainScheduleId = NONE; // which day of the week to deliver car
   _type = NONE; // the type of car
   _road = NONE; // the car road
   _load = NONE; // the car load requested
   _ship = NONE; // the car load shipped
   _destination = NULL; // car destination after load
  _trackDestination = NULL;// car destination track after load
   _pickupTrainScheduleId = NONE; // which day of the week to pickup car
   _count = 1; // the number of times this type of car must be dropped
   _wait = 0; // how many trains this car must wait before being picked up
   _hits = 0; // how many times this schedule item has been used
   _comment = NONE;
 }

 /*public*/ QString ScheduleItem::getId() {
     return _id;
 }

 /*public*/ QString ScheduleItem::getTypeName() {
     return _type;
 }

 /**
  * Sets the type of car requested.
  *
  * @param type The car type requested.
  */
 /*public*/ void ScheduleItem::setTypeName(QString type) {
     QString old = _type;
     _type = type;
     firePropertyChange(TYPE_CHANGED_PROPERTY, old, type);
 }

 /*public*/ QString ScheduleItem::getRandom() {
     return _random;
 }

 /*public*/ void ScheduleItem::setRandom(QString value) {
     QString old = _random;
     _random = value;
     firePropertyChange("scheduleItemRandomValueChanged", old, value); // NOI18N
 }

 /*public*/ QString ScheduleItem::getSetoutTrainScheduleId() {
     return _setoutTrainScheduleId;
 }

 /*public*/ void ScheduleItem::setSetoutTrainScheduleId(QString id) {
     QString old = _setoutTrainScheduleId;
     _setoutTrainScheduleId = id;
     firePropertyChange(TRAIN_SCHEDULE_CHANGED_PROPERTY, old, id);
 }

 /*public*/ QString ScheduleItem::getPickupTrainScheduleId() {
     return _pickupTrainScheduleId;
 }

 /*public*/ void ScheduleItem::setPickupTrainScheduleId(QString id) {
     QString old = _pickupTrainScheduleId;
     _pickupTrainScheduleId = id;
     firePropertyChange(TRAIN_SCHEDULE_CHANGED_PROPERTY, old, id);
 }

 /*public*/ QString ScheduleItem::getRoadName() {
     return _road;
 }

 /**
  * Sets the requested car road name.
  *
  * @param road The car road requested.
  */
 /*public*/ void ScheduleItem::setRoadName(QString road) {
     QString old = _road;
     _road = road;
     firePropertyChange(ROAD_CHANGED_PROPERTY, old, road);
 }

 /**
  * Sets the car load requested.
  *
  * @param load The load name requested.
  */
 /*public*/ void ScheduleItem::setReceiveLoadName(QString load) {
     QString old = _load;
     _load = load;
     firePropertyChange(LOAD_CHANGED_PROPERTY, old, load);
 }

 /*public*/ QString ScheduleItem::getReceiveLoadName() {
     return _load;
 }

 /**
  * Sets the car load that will ship.
  *
  * @param load The car load shipped.
  */
 /*public*/ void ScheduleItem::setShipLoadName(QString load) {
     QString old = _ship;
     _ship = load;
     firePropertyChange(LOAD_CHANGED_PROPERTY, old, load);
 }

 /*public*/ QString ScheduleItem::getShipLoadName() {
     return _ship;
 }

 /*public*/ int ScheduleItem::getSequenceId() {
     return _sequenceId;
 }

 /*public*/ void ScheduleItem::setSequenceId(int sequence) {
     // property change not needed
     _sequenceId = sequence;
 }

 /*public*/ int ScheduleItem::getCount() {
     return _count;
 }

 /*public*/ void ScheduleItem::setCount(int count) {
     int old = _count;
     _count = count;
     firePropertyChange(COUNT_CHANGED_PROPERTY, old, count);
 }

 /*public*/ int ScheduleItem::getWait() {
     return _wait;
 }

 /*public*/ void ScheduleItem::setWait(int wait) {
     int old = _wait;
     _wait = wait;
     firePropertyChange(WAIT_CHANGED_PROPERTY, old, wait);
 }

 /*public*/ int ScheduleItem::getHits() {
     return _hits;
 }

 /*public*/ void ScheduleItem::setHits(int hit) {
     int old = _hits;
     _hits = hit;
     firePropertyChange(HITS_CHANGED_PROPERTY, old, hit);
 }

 /*public*/ Location* ScheduleItem::getDestination() {
     return _destination;
 }

 /*public*/ void ScheduleItem::setDestination(Location* destination) {
     Location* old = _destination;
     _destination = destination;
     QString oldName = "NULL"; // NOI18N
     if (old != NULL) {
         oldName = old->getName();
     }
     QString newName = "NULL"; // NOI18N
     if (_destination != NULL) {
         newName = _destination->getName();
     }
     firePropertyChange(DESTINATION_CHANGED_PROPERTY, oldName, newName);
 }

 /*public*/ QString ScheduleItem::getDestinationName() {
     if (_destination != NULL) {
         return _destination->getName();
     }
     return NONE;
 }

 /*public*/ QString ScheduleItem::getDestinationId() {
     if (_destination != NULL) {
         return _destination->getId();
     }
     return NONE;
 }

 /*public*/ Track* ScheduleItem::getDestinationTrack() {
     return _trackDestination;
 }

 /*public*/ void ScheduleItem::setDestinationTrack(Track* track) {
     Track* old = _trackDestination;
     _trackDestination = track;
     QString oldName = "NULL"; // NOI18N
     if (old != NULL) {
         oldName = old->getName();
     }
     QString newName = "NULL"; // NOI18N
     if (_trackDestination != NULL) {
         newName = _trackDestination->getName();
     }
     firePropertyChange(DESTINATION_TRACK_CHANGED_PROPERTY, oldName, newName);
 }

 /*public*/ QString ScheduleItem::getDestinationTrackName() {
     if (_trackDestination != NULL) {
         return _trackDestination->getName();
     }
     return NONE;
 }

 /*public*/ QString ScheduleItem::getDestinationTrackId() {
     if (_trackDestination != NULL) {
         return _trackDestination->getId();
     }
     return NONE;
 }

 /*public*/ void ScheduleItem::setComment(QString comment) {
     _comment = comment;
 }

 /*public*/ QString ScheduleItem::getComment() {
     return _comment;
 }

 /*public*/ void ScheduleItem::copyScheduleItem (ScheduleItem* si) {
     setComment(si->getComment());
     setCount(si->getCount());
     setDestination(si->getDestination());
     setDestinationTrack(si->getDestinationTrack());
     setPickupTrainScheduleId(si->getPickupTrainScheduleId());
     setRandom(si->getRandom());
     setReceiveLoadName(si->getReceiveLoadName());
     setRoadName(si->getRoadName());
     setSetoutTrainScheduleId(si->getSetoutTrainScheduleId());
     setShipLoadName(si->getShipLoadName());
     setWait(si->getWait());
 }

 /*public*/ void ScheduleItem::dispose() {
     firePropertyChange(DISPOSE, QVariant(), DISPOSE);
 }

 /**
  * Construct this Entry from Xml:: This member has to remain synchronized
  * with the detailed DTD in operations-config.xml
  *
  * @param e Consist XML element
  */
 /*public*/ ScheduleItem::ScheduleItem(QDomElement e)
 {
  common();
     // if (log->isDebugEnabled()) log->debug("ctor from element "+e);
     QString a;
     if ((a = e.attribute(Xml::ID)) != NULL) {
         _id = a;
     } else {
         log->warn("no id attribute in Schedule Item element when reading operations");
     }
     if ((a = e.attribute(Xml::SEQUENCE_ID)) != NULL) {
         _sequenceId = a.toInt();;
     }
     if ((a = e.attribute(Xml::RANDOM)) != NULL) {
         _random = a;
     }
     if ((a = e.attribute(Xml::TRAIN_SCHEDULE_ID)) != NULL) {
         _setoutTrainScheduleId = a;
     }
     if ((a = e.attribute(Xml::PICKUP_TRAIN_SCHEDULE_ID)) != NULL) {
         _pickupTrainScheduleId = a;
     }
     if ((a = e.attribute(Xml::COUNT)) != NULL) {
         _count = a.toInt();;
     }
     if ((a = e.attribute(Xml::WAIT)) != NULL) {
         _wait = a.toInt();;
     }
     if ((a = e.attribute(Xml::TYPE)) != NULL) {
         _type = a;
     }
     if ((a = e.attribute(Xml::ROAD)) != NULL) {
         _road = a;
     }
     if ((a = e.attribute(Xml::LOAD)) != NULL) {
         _load = a;
     }
     if ((a = e.attribute(Xml::SHIP)) != NULL) {
         _ship = a;
     }
     if ((a = e.attribute(Xml::DESTINATION_ID)) != NULL) {
         _destination = ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"))->getLocationById(a);
     }
     if ((a = e.attribute(Xml::DEST_TRACK_ID)) != NULL && _destination != NULL) {
         _trackDestination = _destination->getTrackById(a);
     }
     if ((a = e.attribute(Xml::COMMENT)) != NULL) {
         _comment = a;
     }
     if ((a = e.attribute(Xml::HITS)) != NULL) {
         _hits = a.toInt();;
     }
 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-config.Xml::
  *
  * @return Contents in a JDOM Element
  */
 /*public*/ QDomElement ScheduleItem::store(QDomDocument doc) {
     QDomElement e = doc.createElement(Xml::ITEM);
     e.setAttribute(Xml::ID, getId());
     e.setAttribute(Xml::SEQUENCE_ID, (getSequenceId()));
     e.setAttribute(Xml::RANDOM, getRandom());
     e.setAttribute(Xml::TRAIN_SCHEDULE_ID, getSetoutTrainScheduleId());
     e.setAttribute(Xml::PICKUP_TRAIN_SCHEDULE_ID, getPickupTrainScheduleId());
     e.setAttribute(Xml::COUNT, (getCount()));
     e.setAttribute(Xml::WAIT, (getWait()));
     e.setAttribute(Xml::TYPE, getTypeName());
     e.setAttribute(Xml::ROAD, getRoadName());
     e.setAttribute(Xml::LOAD, getReceiveLoadName());
     e.setAttribute(Xml::SHIP, getShipLoadName());
     if (getDestinationId()!=(NONE)) {
         e.setAttribute(Xml::DESTINATION_ID, getDestinationId());
     }
     if (getDestinationTrackId()!=(NONE)) {
         e.setAttribute(Xml::DEST_TRACK_ID, getDestinationTrackId());
     }
     e.setAttribute(Xml::COMMENT, getComment());
     e.setAttribute(Xml::HITS, (getHits()));
     return e;
 }

 /*public*/ void ScheduleItem::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
      ->getNewValue().toString()));
     }
 }
#if 0

 /*public*/ synchronized void addPropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.addPropertyChangeListener(l);
 }

 /*public*/ synchronized void removePropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.removePropertyChangeListener(l);
 }
#endif
 /*protected*/ void ScheduleItem::firePropertyChange(QString p, QVariant old, QVariant n) {
     pcs->firePropertyChange(p, old, n);
 }

}
