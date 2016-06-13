#include "route.h"
#include "routemanagerxml.h"
#include "routelocation.h"
#include "xml.h"
#include "train.h"
#include "trainmanager.h"
#include "location.h"
#include "control.h"
#include <QComboBox>
#include <vptr.h>

namespace Operations
{
// Route::Route(QObject *parent) :
//  QObject(parent)
// {

// }

 /**
  * Represents a route on the layout
  *
  * @author Daniel Boudreau Copyright (C) 2008, 2010
  * @version $Revision: 29493 $
  */
// /*public*/ class Route implements java.beans.PropertyChangeListener {

 /*public*/ /*static*/ /*final*/ QString Route::NONE = "";



 /*public*/ /*static*/ /*final*/ int Route::EAST = 1; // train direction
 /*public*/ /*static*/ /*final*/ int Route::WEST = 2;
 /*public*/ /*static*/ /*final*/ int Route::NORTH = 4;
 /*public*/ /*static*/ /*final*/ int Route::SOUTH = 8;

 /*public*/ /*static*/ /*final*/ QString Route::LISTCHANGE_CHANGED_PROPERTY = "routeListChange"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Route::DISPOSE = "routeDispose"; // NOI18N

 /*public*/ /*static*/ /*final*/ QString Route::OKAY = tr("Okay");
 /*public*/ /*static*/ /*final*/ QString Route::ORPHAN = tr("Orphan");
 /*public*/ /*static*/ /*final*/ QString Route::ERROR = tr("Error");

 /*public*/ Route::Route(QString id, QString name, QObject *parent):
                  QObject(parent)
 {
  common();
  log->debug(tr("New route (%1) id: %2").arg(name).arg(id));
  _name = name;
  _id = id;

 }
 void Route::common()
 {
  log = new Logger("Route");
  pcs = new PropertyChangeSupport(this);
  _id = NONE;
  _name = NONE;
  _comment = NONE;

  // stores location names for this route
  _routeHashTable =  QHash<QString, RouteLocation*>();
  _IdNumber = 0; // each location in a route gets its own id
  _sequenceNum = 0; // each location has a unique sequence number
 }

 /*public*/ QString Route::getId() {
     return _id;
 }

 /*public*/ void Route::setName(QString name) {
     QString old = _name;
     _name = name;
     if (old!=(name)) {
         setDirtyAndFirePropertyChange("nameChange", old, name); // NOI18N
     }
 }

 // for combo boxes
 /*public*/ QString Route::toString() {
     return _name;
 }

 /*public*/ QString Route::getName() {
     return _name;
 }

 /*public*/ void Route::setComment(QString comment) {
     QString old = _comment;
     _comment = comment;
     if (old!=(comment)) {
         setDirtyAndFirePropertyChange("commentChange", old, comment); // NOI18N
     }
 }

 /*public*/ QString Route::getComment() {
     return _comment;
 }

 /*public*/ void Route::dispose() {
 setDirtyAndFirePropertyChange(DISPOSE, QVariant(), DISPOSE);
 }

 /**
  * Adds a location to the end of this route
  *
  * @param location
  * @return RouteLocation created for the location added
  */
 /*public*/ RouteLocation* Route::addLocation(Location* location) {
     _IdNumber++;
     _sequenceNum++;
     QString id = _id + "r" + QString::number(_IdNumber);
     log->debug(tr("adding new location to (%1) id: %2").arg(getName()).arg(id));
     RouteLocation* rl = new RouteLocation(id, location);
     rl->setSequenceId(_sequenceNum);
     int old = _routeHashTable.size();
     _routeHashTable.insert(rl->getId(), rl);

     setDirtyAndFirePropertyChange(LISTCHANGE_CHANGED_PROPERTY, old, (_routeHashTable.size()));
     // listen for drop and pick up changes to forward
     //rl.addPropertyChangeListener(this);
     connect(rl->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     return rl;
 }

 /**
  * Add a route location at a specific place (sequence) in the route
  * Allowable sequence numbers are 0 to max size of route;
  *
  * @param location
  * @param sequence
  * @return route location
  */
 /*public*/ RouteLocation* Route::addLocation(Location* location, int sequence) {
     RouteLocation* rl = addLocation(location);
     if (sequence < 0 || sequence > _routeHashTable.size()) {
         return rl;
     }
     for (int i = 0; i < _routeHashTable.size() - sequence - 1; i++) {
         moveLocationUp(rl);
     }
     return rl;
 }

 /**
  * Remember a NamedBean Object created outside the manager.
  */
 /*public*/ void Route::_register(RouteLocation* rl)
 {
  int old = (_routeHashTable.size());
  _routeHashTable.insert(rl->getId(), rl);

  // find last id created
  QStringList getId = rl->getId().split("r");
  int id = (getId[1].toInt());
  if (id > _IdNumber) {
      _IdNumber = id;
  }
  // find highest sequence number
  if (rl->getSequenceId() > _sequenceNum) {
      _sequenceNum = rl->getSequenceId();
  }
  setDirtyAndFirePropertyChange(LISTCHANGE_CHANGED_PROPERTY, old, (_routeHashTable.size()));
  // listen for drop and pick up changes to forward
  //rl.addPropertyChangeListener(this);
  connect(rl->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

 /**
  * Delete a RouteLocation
  *
  * @param rl
  */
 /*public*/ void Route::deleteLocation(RouteLocation* rl) {
     if (rl != NULL) {
         //rl.removePropertyChangeListener(this);
      disconnect(rl->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         // subtract from the locations's available track length
         QString id = rl->getId();
         rl->dispose();
         int old = (_routeHashTable.size());
         _routeHashTable.remove(id);
         resequenceIds();
         setDirtyAndFirePropertyChange(LISTCHANGE_CHANGED_PROPERTY, old, (_routeHashTable.size()));
     }
 }

 /*public*/ int Route::size() {
     return _routeHashTable.size();
 }

 /**
  * Reorder the location sequence numbers for this route
  */
 /*private*/ void Route::resequenceIds() {
     QList<RouteLocation*>* routeList = getLocationsBySequenceList();
     int i;
     for (i = 0; i < routeList->size(); i++) {
         routeList->at(i)->setSequenceId(i + 1); // start sequence numbers at 1
     }
     _sequenceNum = i;
 }

 /**
  * Get the first location in a route
  *
  * @return the first route location
  */
 /*public*/ RouteLocation* Route::getDepartsRouteLocation() {
     QList<RouteLocation*>* list = getLocationsBySequenceList();
     if (list->size() > 0) {
         return list->at(0);
     }
     return NULL;
 }

 /**
  * Get the last location in a route
  *
  * @return the last route location
  */
 /*public*/ RouteLocation* Route::getTerminatesRouteLocation()
 {
  QList<RouteLocation*>* list = getLocationsBySequenceList();
  if (list->size() > 0) {
     return list->value(list->size() - 1);
  }
  return NULL;
 }

 /**
  * Gets the next route location in a route
  *
  * @param rl the current route location
  * @return the next route location, NULL if rl is the last location in a
  *         route.
  */
 /*public*/ RouteLocation* Route::getNextRouteLocation(RouteLocation* rl) {
     QList<RouteLocation*>* list = getLocationsBySequenceList();
     for (int i = 0; i < list->size() - 1; i++) {
         if (rl == list->at(i)) {
             return list->at(i + 1);
         }
     }
     return NULL;
 }

 /**
  * Get location by name (gets last route location with name)
  *
  * @param name
  * @return route location
  */
 /*public*/ RouteLocation* Route::getLastLocationByName(QString name) {
     QList<RouteLocation*>* routeList = getLocationsBySequenceList();
     RouteLocation* rl;

     for (int i = routeList->size() - 1; i >= 0; i--) {
         rl = routeList->at(i);
         if (rl->getName()==(name)) {
             return rl;
         }
     }
     return NULL;
 }

/**
* Get a RouteLocation by id
*
* @param id
* @return route location
*/
/*public*/ RouteLocation* Route::getLocationById(QString id) {
return _routeHashTable.value(id);
}

/*private*/ QList<RouteLocation*> Route::getLocationsByIdList() {
QList<RouteLocation*> out = QList<RouteLocation*>();
QListIterator<RouteLocation*> en(_routeHashTable.values());
//Enumeration<RouteLocation> en = _routeHashTable.elements();
while (en.hasNext()) {
    out.append(en.next());
}
return out;
}

/**
* Get a list of RouteLocations sorted by route order
*
* @return list of RouteLocations ordered by sequence
*/
/*public*/ QList<RouteLocation*>* Route::getLocationsBySequenceList() {
// now re-sort
QList<RouteLocation*>* out = new QList<RouteLocation*>();
foreach (RouteLocation* rl, getLocationsByIdList()) {
    for (int j = 0; j < out->size(); j++) {
        if (rl->getSequenceId() < out->value(j)->getSequenceId()) {
            out->insert(j, rl);
            break;
        }
    }
    if (!out->contains(rl)) {
        out->append(rl);
    }
}
return out;
}

 /**
  * Places a RouteLocation earlier in the route.
  *
  * @param rl
  */
 /*public*/ void Route::moveLocationUp(RouteLocation* rl) {
     int sequenceId = rl->getSequenceId();
     if (sequenceId - 1 <= 0) {
         rl->setSequenceId(_sequenceNum + 1); // move to the end of the list
         resequenceIds();
     } else {
         // adjust the other item taken by this one
         RouteLocation* replaceRl = getItemBySequenceId(sequenceId - 1);
         if (replaceRl != NULL) {
             replaceRl->setSequenceId(sequenceId);
             rl->setSequenceId(sequenceId - 1);
         } else {
             resequenceIds(); // error the sequence number is missing
         }
     }
     setDirtyAndFirePropertyChange(LISTCHANGE_CHANGED_PROPERTY, QVariant(), (sequenceId));
 }

 /**
  * Moves a RouteLocation later in the route.
  *
  * @param rl
  */
 /*public*/ void Route::moveLocationDown(RouteLocation* rl) {
     int sequenceId = rl->getSequenceId();
     if (sequenceId + 1 > _sequenceNum) {
         rl->setSequenceId(0); // move to the start of the list
         resequenceIds();
     } else {
         // adjust the other item taken by this one
         RouteLocation* replaceRl = getItemBySequenceId(sequenceId + 1);
         if (replaceRl != NULL) {
             replaceRl->setSequenceId(sequenceId);
             rl->setSequenceId(sequenceId + 1);
         } else {
             resequenceIds(); // error the sequence number is missing
         }
     }
     setDirtyAndFirePropertyChange(LISTCHANGE_CHANGED_PROPERTY, QVariant(), (sequenceId));
 }

 /*public*/ RouteLocation* Route::getItemBySequenceId(int sequenceId) {
     foreach (RouteLocation* rl, getLocationsByIdList()) {
         if (rl->getSequenceId() == sequenceId) {
             return rl;
         }
     }
     return NULL;
 }

 /**
  * Gets the status of the route: OKAY ORPHAN ERROR
  *
  * @return string with status of route.
  */
 /*public*/ QString Route::getStatus() {
     QList<RouteLocation*> routeList = getLocationsByIdList();
     if (routeList.size() == 0) {
         return ERROR;
     }
     foreach (RouteLocation* rl, routeList) {
         if (rl->getName()==(RouteLocation::DELETED)) {
             return ERROR;
         }
     }
     // check to see if this route is used by a train
     foreach (Train* train, TrainManager::instance()->getTrainsByIdList()) {
         if (train->getRoute() == this) {
             return OKAY;
         }
     }
     return ORPHAN;
 }

 /*public*/ QComboBox* Route::getComboBox() {
     QComboBox* box = new QComboBox();
     foreach (RouteLocation* rl, *getLocationsBySequenceList()) {
         box->addItem(rl->toString(), VPtr<RouteLocation>::asQVariant(rl));
     }
     return box;
 }

 /*public*/ void Route::updateComboBox(QComboBox* box) {
     box->clear();
     box->addItem(NULL);
     foreach (RouteLocation* rl, *getLocationsBySequenceList()) {
         box->addItem(rl->toString(), VPtr<RouteLocation>::asQVariant(rl));
     }
 }

 /**
  * Construct this Entry from Xml:: This member has to remain synchronized
  * with the detailed DTD in operations-config.xml
  *
  * @param e Consist XML element
  */
 /*public*/ Route::Route(QDomElement e)
 {
  common();
  // if (log->isDebugEnabled()) log->debug("ctor from element "+e);
  QString a;
  if ((a = e.attribute(Xml::ID)) != NULL) {
      _id = a;
  } else {
      log->warn("no id attribute in route element when reading operations");
  }
  if ((a = e.attribute(Xml::NAME)) != NULL) {
      _name = a;
  }
  if ((a = e.attribute(Xml::COMMENT)) != NULL) {
      _comment = a;
  }
  if (e.elementsByTagName(Xml::LOCATION) != QDomNodeList())
  {
   //@SuppressWarnings("unchecked")
   QDomNodeList eRouteLocations = e.elementsByTagName(Xml::LOCATION);
   if (log->isDebugEnabled()) {
       log->debug(tr("route: (%1) has %2 locations").arg(getName()).arg(eRouteLocations.size()));
   }
   //for (Element eRouteLocation : eRouteLocations) {
   for(int i = 0; i < eRouteLocations.size(); i++)
   {
    _register(new RouteLocation(eRouteLocations.at(i).toElement()));
   }
  }
 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-config.Xml::
  *
  * @return Contents in a JDOM Element
  */
 /*public*/ QDomElement Route::store(QDomDocument doc)
 {
     QDomElement e = doc.createElement(Xml::ROUTE);
     e.setAttribute(Xml::ID, getId());
     e.setAttribute(Xml::NAME, getName());
     e.setAttribute(Xml::COMMENT, getComment());
     foreach (RouteLocation* rl, *getLocationsBySequenceList())
     {
      e.appendChild(rl->store(doc));
     }
     return e;
 }

 /*public*/ void Route::propertyChange(PropertyChangeEvent* e)
 {
  if (Control::showProperty) {
   log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
           ->getNewValue().toString()));
  }
  // forward drops, pick ups, train direction, and max moves as a list change
  if (e->getPropertyName()==(RouteLocation::DROP_CHANGED_PROPERTY)
          || e->getPropertyName()==(RouteLocation::PICKUP_CHANGED_PROPERTY)
          || e->getPropertyName()==(RouteLocation::TRAIN_DIRECTION_CHANGED_PROPERTY)
          || e->getPropertyName()==(RouteLocation::MAXMOVES_CHANGED_PROPERTY)) {
      setDirtyAndFirePropertyChange(LISTCHANGE_CHANGED_PROPERTY, QVariant(), "RouteLocation"); // NOI18N
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
 /*protected*/ void Route::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     RouteManagerXml::instance()->setDirty(true);
     pcs->firePropertyChange(p, old, n);
 }

} // end namespace
