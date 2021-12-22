#include "schedule.h"
#include "propertychangeevent.h"
#include "propertychangesupport.h"
#include "control.h"
#include "logger.h"
#include "locationmanagerxml.h"
#include "stringutil.h"
#include "scheduleitem.h"
#include "xml.h"
#include "instancemanager.h"

namespace Operations
{
/**
 * Represents a car delivery schedule for a location
 *
 * @author Daniel Boudreau Copyright (C) 2009, 2011, 2013
 * @version $Revision: 29493 $
 */
///*public*/ class Schedule implements java.beans.PropertyChangeListener {


 /*public*/ /*static*/ /*final*/ QString Schedule::LISTCHANGE_CHANGED_PROPERTY = "scheduleListChange"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Schedule::DISPOSE = "scheduleDispose"; // NOI18N

 /*public*/ Schedule::Schedule(QString id, QString name, QObject*parent) : QObject(parent)
{
 common();
 _name = name;
 _id = id;
 log->debug(tr("New schedule (%1) id: %2").arg(name).arg(id));

 }
 void Schedule:: common()
 {
  log = new Logger("Schedule");
  pcs = new PropertyChangeSupport(this);
  _comment = "";

 // stores ScheduleItems for this schedule
  _scheduleHashTable = QHash<QString, ScheduleItem*>();
  _IdNumber = 0; // each item in a schedule gets its own id
  _sequenceNum = 0; // each item has a unique sequence number

 }

 /*public*/ QString Schedule::getId() {
     return _id;
 }

 /*public*/ void Schedule::setName(QString name) {
     QString old = _name;
     _name = name;
     if (old!=(name)) {
         setDirtyAndFirePropertyChange("ScheduleName", old, name); // NOI18N
     }
 }

 // for combo boxes
 /*public*/ QString Schedule::toString() {
     return _name;
 }

 /*public*/ QString Schedule::getName() {
     return _name;
 }

 /*public*/ int Schedule::getSize() {
     return _scheduleHashTable.size();
 }

 /*public*/ void Schedule::setComment(QString comment) {
     QString old = _comment;
     _comment = comment;
     if (old!=(comment)) {
         setDirtyAndFirePropertyChange("ScheduleComment", old, comment); // NOI18N
     }
 }

 /*public*/ QString Schedule::getComment() {
     return _comment;
 }

 /*public*/ void Schedule::dispose() {
     setDirtyAndFirePropertyChange(DISPOSE, QVariant(), DISPOSE);
 }

 /*public*/ void Schedule::resetHitCounts() {
     foreach (ScheduleItem* si, getItemsByIdList()) {
         si->setHits(0);
     }
 }

 /**
  * Adds a car type to the end of this schedule
  *
  * @param type
  * @return ScheduleItem created for the car type added
  */
 /*public*/ ScheduleItem* Schedule::addItem(QString type) {
     _IdNumber++;
     _sequenceNum++;
     QString id = _id + "c" + QString::number(_IdNumber);
     log->debug(tr("Adding new item to (%1) id: %2").arg(getName()).arg(id));
     ScheduleItem* si = new ScheduleItem(id, type);
     si->setSequenceId(_sequenceNum);
     int old = (_scheduleHashTable.size());
     _scheduleHashTable.insert(si->getId(), si);

     setDirtyAndFirePropertyChange(LISTCHANGE_CHANGED_PROPERTY, old, (_scheduleHashTable.size()));
     // listen for set out and pick up changes to forward
     //si->PropertyChangeSupport::addPropertyChangeListener(this);
     connect(si->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     return si;
 }

 /**
  * Add a schedule item at a specific place (sequence) in the schedule
  * Allowable sequence numbers are 0 to max size of schedule. 0 = start of
  * list.
  *
  * @param item
  * @param sequence
  * @return schedule item
  */
 /*public*/ ScheduleItem* Schedule::addItem(QString item, int sequence) {
     ScheduleItem* si = addItem(item);
     if (sequence < 0 || sequence > _scheduleHashTable.size()) {
         return si;
     }
     for (int i = 0; i < _scheduleHashTable.size() - sequence - 1; i++) {
         moveItemUp(si);
     }
     return si;
 }

 /**
  * Remember a NamedBean Object created outside the manager.
  */
 /*public*/ void Schedule::_register(ScheduleItem* si)
 {
  int old = (_scheduleHashTable.size());
  _scheduleHashTable.insert(si->getId(), si);

  // find last id created
  QStringList getId = si->getId().split("c");
  int id = (getId[1].toInt());
  if (id > _IdNumber) {
      _IdNumber = id;
  }
  // find highest sequence number
  if (si->getSequenceId() > _sequenceNum) {
      _sequenceNum = si->getSequenceId();
  }
  setDirtyAndFirePropertyChange(LISTCHANGE_CHANGED_PROPERTY, old, _scheduleHashTable.size());
  // listen for set out and pick up changes to forward
  //si.addPropertyChangeListener(this);
  connect(si->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

 /**
  * Delete a ScheduleItem
  *
  * @param si
  */
 /*public*/ void Schedule::deleteItem(ScheduleItem* si) {
     if (si != NULL) {
         //si.removePropertyChangeListener(this);
      disconnect(si->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         // subtract from the items's available track length
         QString id = si->getId();
         si->dispose();
         int old = (_scheduleHashTable.size());
         _scheduleHashTable.remove(id);
         resequenceIds();
         setDirtyAndFirePropertyChange(LISTCHANGE_CHANGED_PROPERTY, old, (_scheduleHashTable.size()));
     }
 }

 /**
  * Reorder the item sequence numbers for this schedule
  */
 /*private*/ void Schedule::resequenceIds() {
     QList<ScheduleItem*> scheduleItems = getItemsBySequenceList();
     int i;
     for (i = 0; i < scheduleItems.size(); i++) {
         scheduleItems.at(i)->setSequenceId(i + 1); // start sequence numbers at 1
     }
     _sequenceNum = i;
 }
#if 0
 /**
  * Get item by car type (gets last schedule item with this type)
  *
  * @param type
  * @return schedule item
  */
 /*public*/ ScheduleItem getItemByType(String type) {
     List<ScheduleItem> scheduleSequenceList = getItemsBySequenceList();
     ScheduleItem si;

     for (int i = scheduleSequenceList.size() - 1; i >= 0; i--) {
         si = scheduleSequenceList.get(i);
         if (si.getTypeName().equals(type)) {
             return si;
         }
     }
     return NULL;
 }
#endif
 /**
  * Get a ScheduleItem by id
  *
  * @param id
  * @return schedule item
  */
 /*public*/ ScheduleItem*  Schedule::getItemById(QString id) {
     return _scheduleHashTable.value(id);
 }

 /*private*/ QList<ScheduleItem*> Schedule::getItemsByIdList() {
     QVector<QString> arr = QVector<QString>(_scheduleHashTable.size());
     QList<ScheduleItem*> out = QList<ScheduleItem*>();
     QStringListIterator en(_scheduleHashTable.keys());
     int i = 0;
     while (en.hasNext()) {
         arr.replace(i++, en.next());
     }
     StringUtil::sort(arr.toList());
     for (i = 0; i < arr.length(); i++) {
         out.append(getItemById(arr[i]));
     }
     return out;
 }

 /**
  * Get a list of ScheduleItems sorted by schedule order
  *
  * @return list of ScheduleItems ordered by sequence
  */
 /*public*/ QList<ScheduleItem*> Schedule::getItemsBySequenceList() {
     // first get id list
     QList<ScheduleItem*> sortList = getItemsByIdList();
     // now re-sort
     QList<ScheduleItem*> out = QList<ScheduleItem*>();

     foreach (ScheduleItem* si, sortList) {
         for (int j = 0; j < out.size(); j++) {
             if (si->getSequenceId() < out.at(j)->getSequenceId()) {
                 out.insert(j, si);
                 break;
             }
         }
         if (!out.contains(si)) {
             out.append(si);
         }
     }
     return out;
 }

 /**
  * Places a ScheduleItem earlier in the schedule
  *
  * @param si
  */
 /*public*/ void Schedule::moveItemUp(ScheduleItem* si) {
     int sequenceId = si->getSequenceId();
     if (sequenceId - 1 <= 0) {
         si->setSequenceId(_sequenceNum + 1); // move to the end of the list
         resequenceIds();
     } else {
         // adjust the other item taken by this one
         ScheduleItem* replaceSi = getItemBySequenceId(sequenceId - 1);
         if (replaceSi != NULL) {
             replaceSi->setSequenceId(sequenceId);
             si->setSequenceId(sequenceId - 1);
         } else {
             resequenceIds(); // error the sequence number is missing
         }
     }
     setDirtyAndFirePropertyChange(LISTCHANGE_CHANGED_PROPERTY, QVariant(), (sequenceId));
 }

 /**
  * Places a ScheduleItem later in the schedule
  *
  * @param si
  */
 /*public*/ void Schedule::moveItemDown(ScheduleItem* si) {
     int sequenceId = si->getSequenceId();
     if (sequenceId + 1 > _sequenceNum) {
         si->setSequenceId(0); // move to the start of the list
         resequenceIds();
     } else {
         // adjust the other item taken by this one
         ScheduleItem* replaceSi = getItemBySequenceId(sequenceId + 1);
         if (replaceSi != NULL) {
             replaceSi->setSequenceId(sequenceId);
             si->setSequenceId(sequenceId + 1);
         } else {
             resequenceIds();	// error the sequence number is missing
         }
     }
     setDirtyAndFirePropertyChange(LISTCHANGE_CHANGED_PROPERTY, QVariant(), (sequenceId));
 }

 /*public*/ ScheduleItem* Schedule::getItemBySequenceId(int sequenceId) {
     foreach (ScheduleItem* si, getItemsByIdList()) {
         if (si->getSequenceId() == sequenceId) {
             return si;
         }
     }
     return NULL;
 }

 /**
  * Construct this Entry from Xml:: This member has to remain synchronized
  * with the detailed DTD in operations-config.xml
  *
  * @param e Consist XML element
  */
 /*public*/ Schedule::Schedule(QDomElement e) {
  common();
     QString a;
     if ((a = e.attribute(Xml::ID)) != NULL) {
         _id = a;
     } else {
         log->warn("no id attribute in schedule element when reading operations");
     }
     if ((a = e.attribute(Xml::NAME)) != NULL) {
         _name = a;
     }
     if ((a = e.attribute(Xml::COMMENT)) != NULL) {
         _comment = a;
     }
     if (!e.elementsByTagName(Xml::ITEM).isEmpty()) {
         //@SuppressWarnings("unchecked")
         QDomNodeList eScheduleItems = e.elementsByTagName(Xml::ITEM);
         if (log->isDebugEnabled()) {
             log->debug(tr("schedule: %1 has %2 items").arg(getName()).arg(eScheduleItems.size()));
         }
         // (Element eScheduleItem : eScheduleItems) {
         for(int i=0; i < eScheduleItems.count(); i++)
         {
             _register(new ScheduleItem(eScheduleItems.at(i).toElement()));
         }
     }
 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-config.Xml::
  *
  * @return Contents in a JDOM Element
  */
 /*public*/ QDomElement Schedule::store(QDomDocument doc)
 {
  QDomElement e = doc.createElement(Xml::SCHEDULE);
  e.setAttribute(Xml::ID, getId());
  e.setAttribute(Xml::NAME, getName());
  e.setAttribute(Xml::COMMENT, getComment());
  foreach (ScheduleItem* si, getItemsBySequenceList())
  {
   e.appendChild(si->store(doc));
  }

  return e;
 }

 /*public*/ void Schedule::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     // forward all schedule item changes
     setDirtyAndFirePropertyChange(e->getPropertyName(), e->getOldValue(), e->getNewValue());
 }

#if 0
 /*public*/ synchronized void addPropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.addPropertyChangeListener(l);
 }

 /*public*/ synchronized void removePropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.removePropertyChangeListener(l);
 }
#endif
 /*protected*/ void Schedule::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     // set dirty
     ((LocationManagerXml*)InstanceManager::getDefault("LocationManagerXml"))->setDirty(true);
     pcs->firePropertyChange(p, old, n);
 }
}
