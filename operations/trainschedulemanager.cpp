#include "trainschedulemanager.h"
#include "control.h"
#include "propertychangesupport.h"
#include "trainmanagerxml.h"
#include "trainschedule.h"
#include "jcombobox.h"
#include <QDomDocument>
#include <QDomElement>
#include "xml.h"
#include "propertychangesupport.h"
#include "vptr.h"
#include "propertychangeevent.h"
#include "instancemanager.h"

namespace Operations
{
/**
 * Manages train schedules.  The default is the days of the week,
 * but can be anything the user wants when defining when trains will
 * run.
 *
 * @author Bob Jacobsen Copyright (C) 2003
 * @author Daniel Boudreau Copyright (C) 2010
 * @version $Revision: 29824 $
 */
///*public*/ class TrainScheduleManager implements java.beans.PropertyChangeListener {

 /*public*/ /*static*/ /*final*/ QString TrainScheduleManager::LISTLENGTH_CHANGED_PROPERTY = "trainScheduleListLength"; // NOI18N

 /*public*/ TrainScheduleManager::TrainScheduleManager(QObject* parent) : PropertyChangeSupport(this, parent) {
  log = new Logger("TrainScheduleManger");
  setObjectName("TrainScheduleManager");
  _id = 0;
  _scheduleHashTable = QHash<QString, TrainSchedule*>();
  pcs = new PropertyChangeSupport(this);
  setProperty("InstanceManagerAutoDefault", "true");
  setProperty("InstanceManagerAutoInitialize", "true");

 }

 /*public*/ void TrainScheduleManager::dispose() {
     _scheduleHashTable.clear();
 }


 /**
  * @return Number of schedules
  */
 /*public*/ int TrainScheduleManager::numEntries() {
     return _scheduleHashTable.size();
 }

 /**
  * @return requested TrainSchedule object or NULL if none exists
  */
 /*public*/ TrainSchedule* TrainScheduleManager::getScheduleByName(QString name) {
     TrainSchedule* s;
     QListIterator<TrainSchedule*> en(_scheduleHashTable.values());
     while (en.hasNext()) {
         s = en.next();
         if (s->getName()==(name)) {
             return s;
         }
     }
     return NULL;
 }

 /*public*/ TrainSchedule* TrainScheduleManager::getScheduleById(QString id) {
     return _scheduleHashTable.value(id);
 }

 /**
  * Finds an existing schedule or creates a new schedule if needed requires
  * schedule's name creates a unique id for this schedule
  *
  * @param name
  *
  * @return new TrainSchedule or existing TrainSchedule
  */
 /*public*/ TrainSchedule* TrainScheduleManager::newSchedule(QString name)
 {
  TrainSchedule* schedule = getScheduleByName(name);
  if (schedule == NULL)
  {
      _id++;
      schedule = new TrainSchedule(QString::number(_id), name);
      int oldSize = (_scheduleHashTable.size());
      _scheduleHashTable.insert(schedule->getId(), schedule);
      setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, (_scheduleHashTable.size()));
  }
  return schedule;
 }

 /**
  * Remember a NamedBean Object created outside the manager.
  */
 /*public*/ void TrainScheduleManager::_register(TrainSchedule* schedule) {
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
 /*public*/ void TrainScheduleManager::deregister(TrainSchedule* schedule) {
     if (schedule == NULL) {
         return;
     }
     int oldSize = (_scheduleHashTable.size());
     _scheduleHashTable.remove(schedule->getId());
     setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, (_scheduleHashTable.size()));
 }

 /**
  * Sort by train schedule (Timetable) name
  *
  * @return list of train schedules ordered by name
  */
 /*public*/ QList<TrainSchedule*> TrainScheduleManager::getSchedulesByNameList() {
     QList<TrainSchedule*> sortList = getList();
     // now re-sort
     QList<TrainSchedule*> out = QList<TrainSchedule*>();
     for (int i = 0; i < sortList.size(); i++) {
         for (int j = 0; j < out.size(); j++) {
             if (QString::compare(sortList.at(i)->getName(), out.at(j)->getName(),Qt::CaseInsensitive) < 0)
             {
                 out.insert(j, sortList.at(i));
                 break;
             }
         }
         if (!out.contains(sortList.at(i))) {
             out.append(sortList.at(i));
         }
     }
     return out;
 }

 /**
  * Sort by train schedule (Timetable) id numbers
  *
  * @return list of train schedules (Timetable) ordered by id numbers
  */
 /*public*/ QList<TrainSchedule*> TrainScheduleManager::getSchedulesByIdList() {
     QList<TrainSchedule*> sortList = getList();
     // now re-sort
     QList<TrainSchedule*> out = QList<TrainSchedule*>();
     for (int i = 0; i < sortList.size(); i++) {
         for (int j = 0; j < out.size(); j++) {
             bool ok;
                 if ((sortList.at(i)->getId()).toInt(&ok) < (out.at(j)->getId()).toInt()) {
                     out.insert(j, sortList.at(i));
                     break;
                 }
             if(!ok) {
                 log->debug("list id number isn't a number");
             }
         }
         if (!out.contains(sortList.at(i))) {
             out.append(sortList.at(i));
         }
     }
     return out;
 }

 /*private*/ QList<TrainSchedule*> TrainScheduleManager::getList() {
     // no schedules? then load defaults
     if (numEntries() == 0) {
         createDefaultSchedules();
     }
     QList<TrainSchedule*> out = QList<TrainSchedule*>();
     QListIterator<TrainSchedule*> en(_scheduleHashTable.values());
     while (en.hasNext()) {
         out.append(en.next());
     }
     return out;
 }

 /**
  * Gets a JComboBox loaded with schedules starting with NULL.
  *
  * @return JComboBox with a list of schedules.
  */
 /*public*/ JComboBox* TrainScheduleManager::getComboBox() {
     JComboBox* box = new JComboBox();
     updateComboBox(box);
     return box;
 }

 /**
  * Gets a JComboBox loaded with schedules starting with NULL.
  *
  * @return JComboBox with a list of schedules starting with NULL.
  */
 /*public*/ JComboBox* TrainScheduleManager::getSelectComboBox() {
     JComboBox* box = new JComboBox();
     box->addItem(NULL);
     foreach (TrainSchedule* sch, getSchedulesByIdList()) {
         box->addItem(sch->toString(), VPtr<TrainSchedule>::asQVariant(sch));
     }
     return box;
 }

 /**
  * Update a JComboBox with the latest schedules.
  *
  * @param box the JComboBox needing an update.
  */
 /*public*/ void TrainScheduleManager::updateComboBox(JComboBox* box) {
     box->clear();
     foreach (TrainSchedule* sch, getSchedulesByNameList()) {
         box->addItem(sch->toString(), VPtr<TrainSchedule>::asQVariant(sch));
     }
 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-trains.dtd.
  *
  */
 /*public*/ void TrainScheduleManager::store(QDomElement root, QDomDocument doc)
 {
  QDomElement values = doc.createElement(Xml::SCHEDULES);
  // add entries
  QList<TrainSchedule*> schedules = getSchedulesByIdList();
  foreach (TrainSchedule* schedule, schedules)
  {
   values.appendChild(schedule->store(doc));
  }
  root.appendChild(values);
 }

 /*public*/ void TrainScheduleManager::load(QDomElement root)
 {
  QDomElement e = root.firstChildElement(Xml::SCHEDULES);
  if (e != QDomElement())
  {
   //@SuppressWarnings("unchecked")
   QDomNodeList eSchedules = root.firstChildElement(Xml::SCHEDULES).elementsByTagName(Xml::SCHEDULE);
   if (log->isDebugEnabled())
   {
    log->debug("TrainScheduleManager sees " + QString::number(eSchedules.size()) + " train schedules");
   }
   //for (Element eSchedule : eSchedules) {
   for(int i=0; i < eSchedules.count(); i++)
   {
    QDomElement eSchedule = eSchedules.at(i).toElement();
    _register(new TrainSchedule(eSchedule));
   }
  }
 }

 /*public*/ void TrainScheduleManager::createDefaultSchedules() {
     log->debug("creating default schedules");
     newSchedule(tr("Sunday"));
     newSchedule(tr("Monday"));
     newSchedule(tr("Tuesday"));
     newSchedule(tr("Wednesday"));
     newSchedule(tr("Thursday"));
     newSchedule(tr("Friday"));
     newSchedule(tr("Saturday"));
 }

 /*public*/ void TrainScheduleManager::propertyChange(PropertyChangeEvent* e) {
 log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
         ->getNewValue().toString()));
 }

#if 0
 /*public*/ synchronized void addPropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.addPropertyChangeListener(l);
 }

 /*public*/ synchronized void removePropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.removePropertyChangeListener(l);
 }
#endif
 /*protected*/ void TrainScheduleManager::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     ((TrainManagerXml*)InstanceManager::getDefault("TrainManagerXml"))->setDirty(true);
     pcs->firePropertyChange(p, old, n);
 }

 //@Override
 /*public*/ void TrainScheduleManager::initialize() {
     InstanceManager::getDefault("TrainManagerXml"); // load trains
 }
}
