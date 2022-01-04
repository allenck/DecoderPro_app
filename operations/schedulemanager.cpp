#include "schedulemanager.h"
#include "propertychangesupport.h"
#include "propertychangeevent.h"
#include "cartypes.h"
#include "carroads.h"
#include "control.h"
#include "locationmanagerxml.h"
#include "logger.h"
#include "xml.h"
#include "schedule.h"
#include "scheduleitem.h"
#include "vptr.h"
#include "jcombobox.h"
#include "locationmanager.h"
#include "location.h"
#include "track.h"
#include "locationtrackpair.h"
#include "instancemanager.h"

namespace Operations
{
/**
 * Manages schedules.
 *
 * @author Bob Jacobsen Copyright (C) 2003
 * @author Daniel Boudreau Copyright (C) 2008, 2013
 * @version $Revision: 29644 $
 */
///*public*/ class ScheduleManager implements java.beans.PropertyChangeListener {

 /*public*/ /*static*/ /*final*/ QString ScheduleManager::LISTLENGTH_CHANGED_PROPERTY = "scheduleListLength"; // NOI18N

 /*public*/ ScheduleManager::ScheduleManager(QObject* parent)
   : QObject(parent)
 {
  log = new Logger("ScheduleManager");
  pcs = new PropertyChangeSupport(this);
  setProperty("InstanceManagerAutoDefault", "yes");


  //CarTypes::instance().addPropertyChangeListener(this);
  connect(((CarTypes*)InstanceManager::getDefault("CarTypes")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //CarRoads::instance().addPropertyChangeListener(this);
  connect(((CarRoads*)InstanceManager::getDefault("Operations::CarRoads")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  _id = 0;
  // stores known Schedule instances by id
  _scheduleHashTable = QHash<QString, Schedule*>();

  setProperty("InstanceManagerAutoDefault", "true");
  setProperty("InstanceManagerAutoInitialize", "true");

 }

 /**
  * record the single instance *
  */
// /*private*/ /*static*/ ScheduleManager* ScheduleManager::_instance = NULL;

// /*public*/ /*static*/ /*synchronized*/ ScheduleManager* ScheduleManager::instance()
// {
//  return static_cast<ScheduleManager*>(InstanceManager::getDefault("Operations::ScheduleManager"));
// }

 /*public*/ void ScheduleManager::dispose() {
     _scheduleHashTable.clear();
 }


 /**
  * @return Number of schedules
  */
 /*public*/ int ScheduleManager::numEntries() {
     return _scheduleHashTable.size();
 }

 /**
  * @return requested Schedule object or NULL if none exists
  */
 /*public*/ Schedule* ScheduleManager::getScheduleByName(QString name) {
     Schedule* s;
     QListIterator<Schedule*> en(_scheduleHashTable.values());
     while (en.hasNext()) {
         s = en.next();
         if (s->getName()==(name)) {
             return s;
         }
     }
     return NULL;
 }

 /*public*/ Schedule* ScheduleManager::getScheduleById(QString id) {
     return _scheduleHashTable.value(id);
 }

 /**
  * Finds an existing schedule or creates a new schedule if needed requires
  * schedule's name creates a unique id for this schedule
  *
  * @param name
  *
  * @return new schedule or existing schedule
  */
 /*public*/ Schedule* ScheduleManager::newSchedule(QString name) {
     Schedule* schedule = getScheduleByName(name);
     if (schedule == NULL) {
         _id++;
         schedule = new Schedule(QString::number(_id), name);
         int oldSize = (_scheduleHashTable.size());
         _scheduleHashTable.insert(schedule->getId(), schedule);
         setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, (_scheduleHashTable
                 .size()));
     }
     return schedule;
 }

 /**
  * Remember a NamedBean Object created outside the manager.
  */
 /*public*/ void ScheduleManager::_register(Schedule* schedule) {
     int oldSize = (_scheduleHashTable.size());
     _scheduleHashTable.insert(schedule->getId(), schedule);
     // find last id created
     int id = schedule->getId().toInt();
     if (id > _id) {
         _id = id;
     }
     setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, (_scheduleHashTable.size()));
 }

 /**
  * Forget a NamedBean Object created outside the manager.
  */
 /*public*/ void ScheduleManager::deregister(Schedule* schedule) {
     if (schedule == NULL) {
         return;
     }
     schedule->dispose();
     int oldSize = (_scheduleHashTable.size());
     _scheduleHashTable.remove(schedule->getId());
     setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, (_scheduleHashTable.size()));
 }

 /**
  * Sort by schedule name
  *
  * @return list of schedules ordered by name
  */
 /*public*/ QList<Schedule*> ScheduleManager::getSchedulesByNameList() {
     QList<Schedule*> sortList = getList();
     // now re-sort
     QList<Schedule*> out = QList<Schedule*>();
     foreach (Schedule* sch, sortList) {
         for (int j = 0; j < out.size(); j++) {
             //if (sch->getName().compareToIgnoreCase(out.at(j)->getName()) < 0) {
          if(QString::compare(sch->getName(),out.at(j)->getName(),Qt::CaseInsensitive))
          {
                 out.insert(j, sch);
                 break;
             }
         }
         if (!out.contains(sch)) {
             out.append(sch);
         }
     }
     return out;

 }

 /**
  * Sort by schedule id number
  *
  * @return list of schedules ordered by id number
  */
 /*public*/ QList<Schedule*> ScheduleManager::getSchedulesByIdList()
 {
  QList<Schedule*> sortList = getList();
  // now re-sort
  QList<Schedule*> out = QList<Schedule*>();
  foreach (Schedule* sch, sortList)
  {
   for (int j = 0; j < out.size(); j++)
   {
       //try {
    bool ok;
    if (sch->getId().toInt(&ok) < out.at(j)->getId().toInt()) {
        out.insert(j, sch);
        break;
    }
    if(!ok) {
        log->debug("list id number isn't a number");
    }
   }
   if (!out.contains(sch))
   {
    out.append(sch);
   }
  }
  return out;
 }

 /*private*/ QList<Schedule*> ScheduleManager::getList()
 {
  QList<Schedule*> out = QList<Schedule*>();
  QListIterator<Schedule*> en( _scheduleHashTable.values());
  while (en.hasNext()) {
      out.append(en.next());
  }
  return out;
 }

 /*public*/ Schedule* ScheduleManager::copySchedule (Schedule* schedule, QString newScheduleName) {
     Schedule* _newSchedule = newSchedule(newScheduleName);
     foreach (ScheduleItem* si, schedule->getItemsBySequenceList()) {
         ScheduleItem* newSi = _newSchedule->addItem(si->getTypeName());
         newSi->copyScheduleItem(si);
     }
     return _newSchedule;
 }

 /*public*/ void ScheduleManager::resetHitCounts() {
     foreach (Schedule* schedule, getList()) {
         schedule->resetHitCounts();
     }
 }

 /**
  * Gets a JComboBox loaded with schedules.
  *
  * @return JComboBox with a list of schedules.
  */
 /*public*/ JComboBox* ScheduleManager::getComboBox() {
     JComboBox* box = new JComboBox();
     updateComboBox(box);
     return box;
 }

 /**
  * Update a JComboBox with the latest schedules.
  *
  * @param box the JComboBox needing an update.
  */
 /*public*/ void ScheduleManager::updateComboBox(JComboBox* box) {
     box->clear();
     box->addItem(NULL);
     foreach (Schedule* schedule, getSchedulesByNameList()) {
         box->addItem(schedule->toString(), VPtr<Schedule>::asQVariant(schedule));
     }
 }

 /**
  * Replaces car type in all schedules.
  *
  * @param oldType car type to be replaced.
  * @param newType replacement car type.
  */
 /*public*/ void ScheduleManager::replaceType(QString oldType, QString newType) {
     foreach (Schedule* sch, getSchedulesByIdList()) {
         foreach (ScheduleItem* si, sch->getItemsBySequenceList()) {
             if (si->getTypeName()==(oldType)) {
                 si->setTypeName(newType);
             }
         }
     }
 }

 /**
  * Replaces car roads in all schedules.
  *
  * @param oldRoad car road to be replaced.
  * @param newRoad replacement car road.
  */
 /*public*/ void ScheduleManager::replaceRoad(QString oldRoad, QString newRoad) {
     if (newRoad == NULL) {
         return;
     }
     foreach (Schedule* sch, getSchedulesByIdList()) {
         foreach (ScheduleItem* si, sch->getItemsBySequenceList()) {
             if (si->getRoadName()==(oldRoad)) {
                 si->setRoadName(newRoad);
             }
         }
     }
 }

 /**
  * Replaces car loads in all schedules with specific car type.
  *
  * @param type car type.
  * @param oldLoad car load to be replaced.
  * @param newLoad replacement car load.
  */
 /*public*/ void ScheduleManager::replaceLoad(QString type, QString oldLoad, QString newLoad) {
     foreach (Schedule* sch, getSchedulesByIdList()) {
         foreach (ScheduleItem* si, sch->getItemsBySequenceList()) {
             if (si->getTypeName()==(type) && si->getReceiveLoadName()==(oldLoad)) {
                 if (newLoad != NULL) {
                     si->setReceiveLoadName(newLoad);
                 } else {
                     si->setReceiveLoadName(ScheduleItem::NONE);
                 }
             }
             if (si->getTypeName()==(type) && si->getShipLoadName()==(oldLoad)) {
                 if (newLoad != NULL) {
                     si->setShipLoadName(newLoad);
                 } else {
                     si->setShipLoadName(ScheduleItem::NONE);
                 }
             }
         }
     }
 }

 /**
  * Gets a JComboBox with a list of spurs that use this schedule.
  *
  * @param schedule The schedule for this JComboBox.
  * @return JComboBox with a list of spurs using schedule.
  */
 /*public*/ JComboBox* ScheduleManager::getSpursByScheduleComboBox(Schedule* schedule)
{
  JComboBox* box = new JComboBox();
  // search all spurs for that use schedule
  foreach (Location* location, ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"))->getLocationsByNameList())
  {
   foreach (Track* spur, location->getTracksByNameList(Track::SPUR))
   {
    if (spur->getScheduleId()==(schedule->getId()))
    {
     LocationTrackPair* ltp = new LocationTrackPair(location, spur);
     box->addItem(ltp->toString(), VPtr<Operations::LocationTrackPair>::asQVariant(ltp));
    }
   }
  }
  return box;
 }

 /*public*/ void ScheduleManager::load(QDomElement root)
 {
  if (root.firstChildElement(Xml::SCHEDULES) != QDomElement())
  {
   //@SuppressWarnings("unchecked")
   QDomNodeList eSchedules = root.firstChildElement(Xml::SCHEDULES).elementsByTagName(Xml::SCHEDULE);
   log->debug(tr("readFile sees %1 schedules").arg(eSchedules.size()));
   //for (Element eSchedule : eSchedules) {
   for(int i = 0; i <eSchedules.count(); i++)
   {
    QDomElement eSchedule = eSchedules.at(i).toElement();
       _register(new Schedule(eSchedule));
   }
  }
 }

 /*public*/ void ScheduleManager::store(QDomElement root, QDomDocument doc)
 {
  QDomElement values;
  root.appendChild(values = doc.createElement(Xml::SCHEDULES));
  // add entries
  foreach (Schedule* schedule, getSchedulesByIdList())
  {
   values.appendChild(schedule->store(doc));
  }
 }

 /**
  * Check for car type and road name changes.
  *
  */
 /*public*/ void ScheduleManager::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(CarTypes::CARTYPES_NAME_CHANGED_PROPERTY)) {
         replaceType(e->getOldValue().toString(),  e->getNewValue().toString());
     }
     if (e->getPropertyName()==(CarRoads::CARROADS_NAME_CHANGED_PROPERTY)) {
         replaceRoad( e->getOldValue().toString(), e->getNewValue().toString());
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
 /*protected*/ void ScheduleManager::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     // set dirty
     ((LocationManagerXml*)InstanceManager::getDefault("LocationManagerXml"))->setDirty(true);
     pcs->firePropertyChange(p, old, n);
 }

 //@Override
 /*public*/ void ScheduleManager::initialize() {
     //InstanceManager::getDefault("CarTypes").addPropertyChangeListener(this);
 connect(static_cast<CarTypes*>(InstanceManager::getDefault("CarTypes")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //InstanceManager::getDefault("Operations::CarRoads").addPropertyChangeListener(this);
 connect(static_cast<CarRoads*>(InstanceManager::getDefault("Operations::CarRoads")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

 }
}
