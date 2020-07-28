#include "trainschedule.h"
#include "logger.h"
#include "propertychangesupport.h"
#include "trainmanagerxml.h"
#include <QtXml>
#include "control.h"
#include "xml.h"
#include <QStringList>

namespace Operations
{
/**
 * Represents a schedule for trains. For example, can be a day of the week. Useful when
 * determining which trains to build and run.
 *
 * @author Daniel Boudreau Copyright (C) 2010
 * @version $Revision: 29824 $
 */
 ///*public*/ class TrainSchedule {


  /*public*/ /*static*/ /*final*/ QString TrainSchedule::NAME_CHANGED_PROPERTY = "trainScheduleName"; // NOI18N
  /*public*/ /*static*/ /*final*/ QString TrainSchedule::SCHEDULE_CHANGED_PROPERTY = "trainScheduleChanged"; // NOI18N


  /*public*/ TrainSchedule::TrainSchedule(QString id, QString name, QObject *parent)
    : QObject(parent) {
   log = new Logger("TrainSchedule");
     log->debug(tr("New train schedule (%1) id: %2").arg(name).arg(id));
     NONE = "";
//     _id = NONE;
//      _name = NONE;
      _comment = NONE;
     _trainIds = QStringList();
     pcs = new PropertyChangeSupport(this);

     _name = name;
     _id = id;
 }

  /*public*/ QString TrainSchedule::getId() {
     return _id;
 }

  /*public*/ void TrainSchedule::setName(QString name) {
     QString old = _name;
     _name = name;
     if (old != (name)) {
         setDirtyAndFirePropertyChange(NAME_CHANGED_PROPERTY, old, name);
     }
 }

 // for combo boxes
  /*public*/ QString TrainSchedule::toString() {
     return _name;
 }

  /*public*/ QString TrainSchedule::getName() {
     return _name;
 }

  /*public*/ void TrainSchedule::setComment(QString comment) {
     QString old = _comment;
     _comment = comment;
     if (old != (comment)) {
         setDirtyAndFirePropertyChange("AddTrainScheduleComment", old, comment); // NOI18N
     }
 }

  /*public*/ QString TrainSchedule::getComment() {
     return _comment;
 }

  /*public*/ void TrainSchedule::addTrainId(QString id) {
     if (!_trainIds.contains(id)) {
         _trainIds.append(id);
         setDirtyAndFirePropertyChange(SCHEDULE_CHANGED_PROPERTY, QVariant(), id);
     }
 }

  /*public*/ void TrainSchedule::removeTrainId(QString id) {
     _trainIds.removeOne(id);
     setDirtyAndFirePropertyChange(SCHEDULE_CHANGED_PROPERTY, id, QVariant());
 }

  /*public*/ bool TrainSchedule::containsTrainId(QString id) {
     return _trainIds.contains(id);
 }

 /**
  * Construct this Entry from Xml:: This member has to remain synchronized
  * with the detailed DTD in operations-trains.xml
  *
  * @param e Consist XML element
  */
  /*public*/ TrainSchedule::TrainSchedule(QDomElement e) {
     // if (log.isDebugEnabled()) log.debug("ctor from element "+e);
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
     if ((a = e.attribute(Xml::TRAIN_IDS)) != NULL) {
         QString ids = a;
         QStringList trainIds = ids.split(",");
         foreach (QString id, trainIds) {
             _trainIds.append(id);
         }
//			if (log.isDebugEnabled())
//				log.debug("Train schedule " + getName() + " trainIds: " + ids);
     }
 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-config.Xml::
  *
  * @return Contents in a JDOM Element
  */
  /*public*/ QDomElement TrainSchedule::store(QDomDocument doc) {
     QDomElement e = doc.createElement(Xml::SCHEDULE);
     e.setAttribute(Xml::ID, getId());
     e.setAttribute(Xml::NAME, getName());
     if (getComment()!=(NONE)) {
         e.setAttribute(Xml::COMMENT, getComment());
     }
     // store train ids
     QString buf = ""; //new StringBuilder();
     foreach (QString id, _trainIds) {
         buf.append(id + ",");
     }
     e.setAttribute(Xml::TRAIN_IDS, buf/*.toString()*/);
     return e;
 }

  /*public*/ void TrainSchedule::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("PropertyChange (%1) new (%2)").arg(e->getPropertyName()).arg(e->getNewValue().toString()));
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
 /*protected*/ void TrainSchedule::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     TrainManagerXml::instance()->setDirty(true);
     pcs->firePropertyChange(p, old, n);
 }

}
