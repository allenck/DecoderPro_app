#include "routemanager.h"
#include "propertychangesupport.h"
#include "logger.h"
#include "operationssetupxml.h"
#include "routemanagerxml.h"
#include "control.h"
#include "route.h"
#include "propertychangeevent.h"
#include <QComboBox>
#include "rosterentry.h"
#include "xml.h"
#include "routelocation.h"
#include "locationmanager.h"

namespace Operations
{
//RouteManager::RouteManager(QObject *parent) :
//  QObject(parent)
//{
//}
 /**
  * Manages the routes
  *
  * @author Bob Jacobsen Copyright (C) 2003
  * @author Daniel Boudreau Copyright (C) 2008, 2009, 2010
  * @version $Revision: 29493 $
  */
///*public*/ class RouteManager {

 /*public*/ /*static*/ /*final*/ QString RouteManager::LISTLENGTH_CHANGED_PROPERTY = "routesListLengthChanged"; // NOI18N

 /*public*/ RouteManager::RouteManager(QObject *parent)
   : QObject(parent)
 {
  pcs = new ::PropertyChangeSupport(this);
  log = new ::Logger("RouteManager");
 }

 /**
  * record the single instance *
  */
 /*private*/ /*static*/ RouteManager* RouteManager::_instance = NULL;

 /*public*/ /*static synchronized*/ RouteManager* RouteManager::instance()
{
 Logger* log = new Logger("RouteManager");
     if (_instance == NULL) {
         if (log->isDebugEnabled()) {
             log->debug("RouteManager creating instance");
         }
         // create and load
         _instance = new RouteManager();
         OperationsSetupXml::instance(); // load setup
         RouteManagerXml::instance(); // load routes
     }
     if (Control::showInstance) {
         log->debug(tr("RouteManager returns instance %1").arg(_instance->metaObject()->className()));
     }
     return _instance;
 }

 /*public*/ void RouteManager::dispose() {
     _routeHashTable.clear();
     _id = 0;
 }


 /**
  * @return requested Route object or NULL if none exists
  */
 /*public*/ Route* RouteManager::getRouteByName(QString name) {
     Route* l;
     //Enumeration<Route> en = _routeHashTable.elements();
     QListIterator<Route*> en(_routeHashTable.values());
     while (en.hasNext()) {
         l = en.next();
         if (l->getName()==(name)) {
             return l;
         }
     }
     return NULL;
 }

 /*public*/ Route* RouteManager::getRouteById(QString id) {
     return _routeHashTable.value(id);
 }

 /**
  * Finds an existing route or creates a new route if needed requires route's
  * name creates a unique id for this route
  *
  * @param name
  *
  * @return new route or existing route
  */
 /*public*/ Route* RouteManager::newRoute(QString name) {
     Route* route = getRouteByName(name);
     if (route == NULL) {
         _id++;
         route = new Route(QString::number(_id), name);
         int oldSize = (_routeHashTable.size());
         _routeHashTable.insert(route->getId(), route);
         setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, (_routeHashTable.size()));
     }
     return route;
 }

 /**
  * Remember a NamedBean Object created outside the manager.
  */
 /*public*/ void RouteManager::_register(Route* route) {
     int oldSize = (_routeHashTable.size());
     _routeHashTable.insert(route->getId(), route);
     // find last id created
     int id = route->getId().toInt();
     if (id > _id) {
         _id = id;
     }
     setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, (_routeHashTable.size()));
     // listen for name and state changes to forward
 }

 /**
  * Forget a NamedBean Object created outside the manager.
  */
 /*public*/ void RouteManager::deregister(Route* route) {
     if (route == NULL) {
         return;
     }
     route->dispose();
     int oldSize = (_routeHashTable.size());
     _routeHashTable.remove(route->getId());
     setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize, (_routeHashTable.size()));
 }

 /**
  * Sort by route name
  *
  * @return list of routes ordered by name
  */
 /*public*/ QList<Route*> RouteManager::getRoutesByNameList() {
     QList<Route*> sortList = getList();
     // now re-sort
     QList<Route*> out = QList<Route*>();
     foreach (Route* route, sortList) {
         for (int j = 0; j < out.size(); j++) {
             if (QString::compare(route->getName(),out.at(j)->getName(), Qt::CaseInsensitive) < 0) {
                 out.insert(j, route);
                 break;
             }
         }
         if (!out.contains(route)) {
             out.append(route);
         }
     }
     return out;

 }

 /**
  * Sort by route number, number can alpha numeric
  *
  * @return list of routes ordered by id numbers
  */
 /*public*/ QList<Route*> RouteManager::getRoutesByIdList() {
     QList<Route*> sortList = getList();
     // now re-sort
     QList<Route*> out =  QList<Route*>();
     foreach (Route* route, sortList) {
         for (int j = 0; j < out.size(); j++) {
             try {
                 if (route->getId().toInt() < out.at(j)->getId().toInt()) {
                     out.insert(j, route);
                     break;
                 }
             } catch (NumberFormatException e) {
                 log->error("list id number isn't a number");
             }
         }
         if (!out.contains(route)) {
             out.append(route);
         }
     }
     return out;
 }

 /*private*/ QList<Route*> RouteManager::getList() {
     QList<Route*> out =  QList<Route*>();
     //Enumeration<Route> en = _routeHashTable.elements();
     QListIterator<Route*> en(_routeHashTable.values());
     while (en.hasNext()) {
         out.append(en.next());
     }
     return out;
 }

 /*public*/ QComboBox* RouteManager::getComboBox() {
     QComboBox* box = new QComboBox();
     box->addItem(NULL);
     QList<Route*> routes = getRoutesByNameList();
     foreach (Route* route, routes) {
         box->addItem(route->getName(), VPtr<Route>::asQVariant(route));
     }
     return box;
 }

 /*public*/ void RouteManager::updateComboBox(QComboBox* box) {
     box->clear();
     box->addItem(NULL);
     QList<Route*> routes = getRoutesByNameList();
     foreach (Route* route, routes) {
         box->addItem(route->getName(), VPtr<Route>::asQVariant(route));
     }
 }

 /**
  * Copy route, returns a new route named routeName. If invert is true the
  * reverse of the route is returned.
  *
  * @param route     The route to be copied
  * @param routeName The name of the new route
  * @param invert    If true, return the inversion of route
  * @return A copy of the route
  */
 /*public*/ Route* RouteManager::copyRoute(Route* route, QString routeName, bool invert) {
     Route* _newRoute = newRoute(routeName);
     QList<RouteLocation*>* routeList = route->getLocationsBySequenceList();
     if (!invert) {
         foreach (RouteLocation* rl, *routeList) {
             copyRouteLocation(_newRoute, rl, NULL, invert);
         }
         // invert route order
     } else {
         for (int i = routeList->size() - 1; i >= 0; i--) {
             int y = i - 1;
             if (y < 0) {
                 y = 0;
             }
             copyRouteLocation(_newRoute, routeList->at(i), routeList->at(y), invert);
         }
     }
     _newRoute->setComment(route->getComment());
     return _newRoute;
 }

 /*private*/ void RouteManager::copyRouteLocation(Route* newRoute, RouteLocation* rl, RouteLocation* rlNext, bool invert)
 {
     Location* loc = LocationManager::instance()->getLocationByName(rl->getName());
     RouteLocation* rlNew = newRoute->addLocation(loc);
     // now copy the route location objects we want
     rlNew->setMaxCarMoves(rl->getMaxCarMoves());
     rlNew->setWait(rl->getWait());
     rlNew->setDepartureTime(rl->getDepartureTime());
     rlNew->setComment(rl->getComment());
     if (!invert) {
         rlNew->setDropAllowed(rl->isDropAllowed());
         rlNew->setPickUpAllowed(rl->isPickUpAllowed());
         rlNew->setGrade(rl->getGrade());
         rlNew->setTrainDirection(rl->getTrainDirection());
         rlNew->setMaxTrainLength(rl->getMaxTrainLength());
     } else {
         // flip set outs and pick ups
         rlNew->setDropAllowed(rl->isPickUpAllowed());
         rlNew->setPickUpAllowed(rl->isDropAllowed());
         // invert train directions
         int oldDirection = rl->getTrainDirection();
         if (oldDirection == RouteLocation::NORTH) {
             rlNew->setTrainDirection(RouteLocation::SOUTH);
         } else if (oldDirection == RouteLocation::SOUTH) {
             rlNew->setTrainDirection(RouteLocation::NORTH);
         } else if (oldDirection == RouteLocation::EAST) {
             rlNew->setTrainDirection(RouteLocation::WEST);
         } else if (oldDirection == RouteLocation::WEST) {
             rlNew->setTrainDirection(RouteLocation::EAST);
         }
         // get the max length between location
         if (rlNext == NULL) {
             log->error("Can not copy route, oldNextRl is NULL!");
             return;
         }
         rlNew->setMaxTrainLength(rlNext->getMaxTrainLength());
     }
     rlNew->setTrainIconX(rl->getTrainIconX());
     rlNew->setTrainIconY(rl->getTrainIconY());
 }

 /**
  * @return Number of routes
  */
 /*public*/ int RouteManager::numEntries() {
     return _routeHashTable.size();
 }

 /*public*/ void RouteManager::load(QDomElement root)
 {
  // decode type, invoke proper processing routine if a decoder file
  if (root.firstChildElement(Xml::ROUTES) != QDomElement())
  {
   // @SuppressWarnings("unchecked")
    QDomNodeList eRoutes = root.firstChildElement(Xml::ROUTES).elementsByTagName(Xml::ROUTE);
    if (log->isDebugEnabled())
    {
     log->debug(tr("readFile sees %1 routes").arg(eRoutes.size()));
    }
    //for (Element eRoute : eRoutes) {
    for(int i = 0; i < eRoutes.size(); i++)
    {
     _register(new Route(eRoutes.at(i).toElement()));
    }
  }
 }

 /*public*/ void RouteManager::store(QDomElement root, QDomDocument doc)
 {
     QDomElement values = doc.createElement(Xml::ROUTES);
     root.appendChild(values);
     foreach (Route* route, getRoutesByIdList()) {
         values.appendChild(route->store(doc));
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
 /*protected*/ void RouteManager::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     RouteManagerXml::instance()->setDirty(true);
     pcs->firePropertyChange(p, old, n);
 }
/**
 * Locate via user name, then system name if needed. Does not create a new
 * one if nothing found
 *
 * @param name User name or system name to match
 * @return null if no match found
 */
//@CheckForNull
/*public*/ Route* getRoute(/*@Nonnull*/ QString /*name*/) {return NULL;}

//@CheckForNull
/*public*/ Route* getByUserName(/*@Nonnull*/ QString /*s*/) {return NULL;}

//@CheckForNull
/*public*/ Route* getBySystemName(/*@Nonnull*/ QString /*s*/) {return NULL;}

/**
 * Get a list of all Route system names.
 *
 * @return the list of route system names or an empty list
 */
//@Nonnull
//@Override
/*public*/ QList<QString> getSystemNameList() {return QList<QString>();}

/**
 * Delete Route by removing it from the manager. The Route must first be
 * deactivated so it stops processing.
 *
 * @param r the route to remove
 */
void deleteRoute(/*@Nonnull*/ Route* /*r*/) {}
}
