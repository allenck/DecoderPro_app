#include "defaultroutemanagerxml.h"
#include "routemanager.h"
#include "instancemanager.h"
#include "route.h"
#include "fileutil.h"
#include "defaultroutemanager.h"
#include "joptionpane.h"

DefaultRouteManagerXml::DefaultRouteManagerXml(QObject *parent) :
  AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("DefaultRouteManagerXml");
 setObjectName("DefaultRouteManagerXml");
}
/**
 * Provides the functionality for configuring RouteManagers
 * <P>
 *
 * @author Dave Duchamp Copyright (c) 2004
 * @author Daniel Boudreau Copyright (c) 2007
 * @author Simon Reader Copyright (C) 2008
 *
 * @version $Revision: 28746 $
 */
///*public*/ class DefaultRouteManagerXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

///*public*/ DefaultRouteManagerXml() {
//}

/**
 * Default implementation for storing the contents of a RouteManager
 *
 * @param o Object to store, of type RouteManager
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement DefaultRouteManagerXml::store(QObject* o)
{
 QDomElement routes = doc.createElement("routes");
 setStoreElementClass(routes);
 RouteManager* tm = (RouteManager*) o;
 if (tm != NULL)
 {
  QStringListIterator iter(tm->getSystemNameList());

  // don't return an element if there are not routes to include
  if (!iter.hasNext()) {
   return QDomElement();
  }

  // store the routes
  while (iter.hasNext()) {
      QString sname = iter.next();
      if (sname == NULL) {
          Logger::error("System name NULL during store");
      }
      log->debug("system name is " + sname);
      Route* r = (Route*)tm->getBySystemName(sname);
      QString cTurnout = r->getControlTurnout();
      int addedDelay = r->getRouteCommandDelay();
      bool routeLocked = r->getLocked();
      QString cLockTurnout = r->getLockControlTurnout();

      QDomElement elem = doc.createElement("route");
//              elem.setAttribute("systemName", sname);
      QDomElement e1 = doc.createElement("systemName");
      e1.appendChild(doc.createTextNode(sname));
      elem.appendChild(e1);

      // store common parts
      storeCommon((NamedBean*)r, elem);

      if (cTurnout != NULL && cTurnout != "") {
          elem.setAttribute("controlTurnout", cTurnout);
          int state = r->getControlTurnoutState();
          if (state == Route::ONTHROWN) {
              elem.setAttribute("controlTurnoutState", "THROWN");
          } else if (state == Route::ONCHANGE) {
              elem.setAttribute("controlTurnoutState", "CHANGE");
          } else if (state == Route::VETOCLOSED) {
              elem.setAttribute("controlTurnoutState", "VETOCLOSED");
          } else if (state == Route::VETOTHROWN) {
              elem.setAttribute("controlTurnoutState", "VETOTHROWN");
          } else {
              elem.setAttribute("controlTurnoutState", "CLOSED");
          }
      }
      if (cLockTurnout != NULL && cLockTurnout != "") {
          elem.setAttribute("controlLockTurnout", cLockTurnout);
          int state = r->getLockControlTurnoutState();
          if (state == Route::ONTHROWN) {
              elem.setAttribute("controlLockTurnoutState", "THROWN");
          } else if (state == Route::ONCHANGE) {
              elem.setAttribute("controlLockTurnoutState", "CHANGE");
          } else {
              elem.setAttribute("controlLockTurnoutState", "CLOSED");
          }
      }
      if (addedDelay > 0) {
          elem.setAttribute("addedDelay", (addedDelay));
      }

      if (routeLocked) {
          elem.setAttribute("routeLocked", "True");
      }
      // add route output Turnouts, if any
      int index = 0;
      QString rTurnout = NULL;
      while ((rTurnout = r->getOutputTurnoutByIndex(index)) != NULL) {
          QDomElement rElem = doc.createElement("routeOutputTurnout");
                  rElem.setAttribute("systemName", rTurnout);
          QString sState = "CLOSED";
          if (r->getOutputTurnoutSetState(rTurnout) == Turnout::THROWN) {
              sState = "THROWN";
          } else if (r->getOutputTurnoutSetState(rTurnout) == Route::TOGGLE) {
              sState = "TOGGLE";
          }
          rElem.setAttribute("state", sState);
          elem.appendChild(rElem);
          index++;
      }
      // add route output Sensors, if any
      index = 0;
      QString rSensor = NULL;
      while ((rSensor = r->getOutputSensorByIndex(index)) != NULL) {
          QDomElement rElem = doc.createElement("routeOutputSensor");
                  rElem.setAttribute("systemName", rSensor);
          QString sState = "INACTIVE";
          if (r->getOutputSensorSetState(rSensor) == Sensor::ACTIVE) {
              sState = "ACTIVE";
          } else if (r->getOutputSensorSetState(rSensor) == Route::TOGGLE) {
              sState = "TOGGLE";
          }
          rElem.setAttribute("state", sState);
          elem.appendChild(rElem);
          index++;
      }
      // add route control Sensors, if any
      index = 0;
      //rSensor = NULL;	// previous while forces rSensor to NULL
      while ((rSensor = r->getRouteSensorName(index)) != NULL) {
          QDomElement rsElem = doc.createElement("routeSensor");
                  rsElem.setAttribute("systemName", rSensor);
          int mode = r->getRouteSensorMode(index);
          QString modeName;
          switch (mode) {
              case Route::ONACTIVE:
                  modeName = "onActive";
                  break;
              case Route::ONINACTIVE:
                  modeName = "onInactive";
                  break;
              case Route::ONCHANGE:
                  modeName = "onChange";
                  break;
              case Route::VETOACTIVE:
                  modeName = "vetoActive";
                  break;
              case Route::VETOINACTIVE:
                  modeName = "vetoInactive";
                  break;
              default:
           modeName = "";
          }
          if (modeName != NULL) {
              rsElem.setAttribute("mode", modeName);
          }
          elem.appendChild(rsElem);
          index++;
      }
      // add sound and script file elements if needed
      if (r->getOutputSoundName() != NULL && r->getOutputSoundName()!=("")) {
          QDomElement rsElem = doc.createElement("routeSoundFile");
                  rsElem.setAttribute("name",
                          FileUtil::getPortableFilename(
                                  new File(r->getOutputSoundName()))
                  );
          elem.appendChild(rsElem);
      }
      if (r->getOutputScriptName() != NULL && r->getOutputScriptName()!=("")) {
          QDomElement rsElem = doc.createElement("routeScriptFile");
                  rsElem.setAttribute("name",
                          FileUtil::getPortableFilename(
                                  new File(r->getOutputScriptName()))
                  );
          elem.appendChild(rsElem);
      }

      // add turnouts aligned sensor if there is one
      if (r->getTurnoutsAlignedSensor()!=("")) {
          QDomElement rsElem = doc.createElement("turnoutsAlignedSensor");
                  rsElem.setAttribute("name", r->getTurnoutsAlignedSensor());
          elem.appendChild(rsElem);
      }

      log->debug("store route " + sname);
      routes.appendChild(elem);
  }
}
return routes;
}

/**
* Subclass provides implementation to create the correct top element,
* including the type information. Default implementation is to use the
* local class here.
*
* @param routes The top-level element being created
*/
/*public*/ void DefaultRouteManagerXml::setStoreElementClass(QDomElement routes) {
 routes.setAttribute("class", "jmri.managers.configurexml.DefaultRouteManagerXml");
}

///*public*/ void DefaultRouteManagerXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception)
//{
// Logger::error("Invalid method called");
//}

/**
* Create a RouteManager object of the correct class, then register and fill
* it.
*
* @param routes Top level QDomElement to unpack.
* @return true if successful
*/
/*public*/ bool DefaultRouteManagerXml::load(QDomElement sharedRoutes, QDomElement perNodeRoutes ) throw (JmriConfigureXmlException) {
 // create the master object
 replaceRouteManager();
 // load individual routes
 loadRoutes(sharedRoutes);
 return true;
}

/**
* Utility method to load the individual Route objects. If there's no
* additional info needed for a specific route type, invoke this with the
* parent of the set of Route elements.
*
* @param routes QDomElement containing the Route elements to load.
*/
/*public*/ void DefaultRouteManagerXml::loadRoutes(QDomElement routes)
{
 QDomNodeList routeList = routes.elementsByTagName("route");
 if (log->isDebugEnabled()) {
  log->debug("Found " + QString::number(routeList.size()) + " routes");
 }
 RouteManager* tm = (RouteManager*)InstanceManager::getDefault("RouteManager");
 int namesChanged = 0;

 for (int i = 0; i < routeList.size(); i++)
 {
  QDomElement el = routeList.at(i).toElement();
  QString sysName = getSystemName(el);
  if (sysName.isNull())
  {
   log->warn("unexpected NULL in systemName " + el.tagName());
      break;
  }
  // convert typeLetter from R to tm.typeLetter()
  QString s = tm->getSystemPrefix() + 'R';
  if (sysName.startsWith(tm->getSystemPrefix() + 'R')) {
      QString old = sysName;
      sysName = tm->getSystemNamePrefix() + sysName.mid(tm->getSystemNamePrefix().length());
      if(sysName != old)
      {
       log->warn(tr("Converting route system name %1 to %2").arg(old).arg(sysName));
       namesChanged++;
      }
  }
  // prepend systemNamePrefix if missing
  if (!sysName.startsWith(tm->getSystemNamePrefix())) {
      QString old = sysName;
      sysName = tm->getSystemNamePrefix() + sysName;
      if(sysName != old)
      {
       log->warn(tr("Converting route system name %1 to %2").arg(old).arg(sysName));
       namesChanged++;
      }
  }

  QString userName = getUserName(el);
  QString cTurnout = NULL;
  QString cTurnoutState = NULL;
  QString addedDelayTxt = NULL;
  QString routeLockedTxt = NULL;
  QString cLockTurnout = NULL;
  QString cLockTurnoutState = NULL;
  int addedDelay = 0;
  if (el.attribute("userName") != NULL) {
      userName = el.attribute("userName");
  }

  if (el.attribute("controlTurnout") != NULL) {
      cTurnout = el.attribute("controlTurnout");
  }
  if (el.attribute("controlTurnoutState") != NULL) {
      cTurnoutState = el.attribute("controlTurnoutState");
  }
  if (el.attribute("controlLockTurnout") != NULL) {
      cLockTurnout = el.attribute("controlLockTurnout");
  }
  if (el.attribute("controlLockTurnoutState") != NULL) {
      cLockTurnoutState = el.attribute("controlLockTurnoutState");
  }
  if (el.attribute("addedDelay") != NULL) {
      addedDelayTxt = el.attribute("addedDelay");
      if (addedDelayTxt != NULL) {
          addedDelay =addedDelayTxt.toInt();
      }
  }
  if (el.attribute("routeLocked") != NULL) {
      routeLockedTxt = el.attribute("routeLocked");
  }

  if (log->isDebugEnabled()) {
      log->debug("create route: (" + sysName + ")("
              + (userName == NULL ? "<NULL>" : userName) + ")");
  }
  Route* r;
  try
  {
   r = tm->provideRoute(sysName, userName);
  } catch (IllegalArgumentException ex) {
      log->error(tr("failed to create Route: %1").arg(sysName));
      return;
  }
  // load common parts
  loadCommon((NamedBean*)r, el);

  if (r != NULL)
  {
   // add control turnout if there is one
   if (cTurnout != NULL)
   {
    r->setControlTurnout(cTurnout);
    if (cTurnoutState != NULL)
    {
     if (cTurnoutState==("THROWN"))
     {
      r->setControlTurnoutState(Route::ONTHROWN);
     } else if (cTurnoutState==("CHANGE"))
     {
      r->setControlTurnoutState(Route::ONCHANGE);
     } else if (cTurnoutState==("VETOCLOSED"))
     {
      r->setControlTurnoutState(Route::VETOCLOSED);
     } else if (cTurnoutState==("VETOTHROWN"))
     {
      r->setControlTurnoutState(Route::VETOTHROWN);
     } else
     {
      r->setControlTurnoutState(Route::ONCLOSED);
     }
    } else
    {
     Logger::error("cTurnoutState was NULL!");
    }
   }
   // set added delay
   r->setRouteCommandDelay(addedDelay);

   // determine if route locked
   if (routeLockedTxt != NULL && routeLockedTxt==("True")) {
       r->setLocked(true);
   }

   //add lock control turout if there is one
   if (cLockTurnout != NULL) {
       r->setLockControlTurnout(cLockTurnout);
       if (cLockTurnoutState != NULL) {
           if (cLockTurnoutState==("THROWN")) {
               r->setLockControlTurnoutState(Route::ONTHROWN);
           } else if (cLockTurnoutState==("CHANGE")) {
               r->setLockControlTurnoutState(Route::ONCHANGE);
           } else {
               r->setLockControlTurnoutState(Route::ONCLOSED);
           }
       } else {
           Logger::error("cLockTurnoutState was NULL!");
       }
   }

   // load output turnouts if there are any - old format first (1.7.6 and before)
   QDomNodeList routeTurnoutList = el.elementsByTagName("routeTurnout");
   if (routeTurnoutList.size() > 0) {
       // This route has turnouts
       for (int k = 0; k < routeTurnoutList.size(); k++) {
           if (((routeTurnoutList.at(k).toElement())).attribute("systemName") == NULL) {
               log->warn("unexpected NULL in systemName " + ((routeTurnoutList.at(k).toElement().tagName()))
                       /*+ " " + ((routeTurnoutList.at(k).toElement())).attributes()*/);
               break;
           }
           QString tSysName = ((routeTurnoutList.at(k).toElement()))
                   .attribute("systemName");
           QString rState = ((routeTurnoutList.at(k).toElement()))
                   .attribute("state");
           int tSetState = Turnout::CLOSED;
           if (rState==("THROWN")) {
               tSetState = Turnout::THROWN;
           } else if (rState==("TOGGLE")) {
               tSetState = Route::TOGGLE;
           }
           // Add turnout to route
           r->addOutputTurnout(tSysName, tSetState);
       }
   }
   // load output turnouts if there are any - new format
   routeTurnoutList = el.elementsByTagName("routeOutputTurnout");
   if (routeTurnoutList.size() > 0) {
       // This route has turnouts
       for (int k = 0; k < routeTurnoutList.size(); k++) {
           if (routeTurnoutList.at(k).toElement().attribute("systemName") == NULL) {
               log->warn("unexpected NULL in systemName " + routeTurnoutList.at(k).toElement().tagName()
                       /*+ " " + routeTurnoutList.at(k).toElement().attributes()*/);
               break;
           }
           QString tSysName = routeTurnoutList.at(k).toElement()
                   .attribute("systemName");
           QString rState = routeTurnoutList.at(k).toElement()
                   .attribute("state");
           int tSetState = Turnout::CLOSED;
           if (rState==("THROWN")) {
               tSetState = Turnout::THROWN;
           } else if (rState==("TOGGLE")) {
               tSetState = Route::TOGGLE;
           }
           // If the Turnout has already been added to the route and is the same as that loaded,
           // we will not re add the turnout.
           if (!r->isOutputTurnoutIncluded(tSysName)) {

               // Add turnout to route
               r->addOutputTurnout(tSysName, tSetState);

               // determine if turnout should be locked
               Turnout* t = r->getOutputTurnout(k);
               if (r->getLocked()) {
                   t->setLocked(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT, true);
               }
           }
       }
   }
   // load output sensors if there are any - new format
   routeTurnoutList = el.elementsByTagName("routeOutputSensor");
   if (routeTurnoutList.size() > 0) {
       // This route has turnouts
       for (int k = 0; k < routeTurnoutList.size(); k++) {
           if (routeTurnoutList.at(k).toElement().attribute("systemName") == NULL) {
               log->warn("unexpected NULL in systemName " + routeTurnoutList.at(k).toElement().tagName()
                       /*+ " " + routeTurnoutList.at(k).toElement().attributes()*/);
               break;
           }
           QString tSysName = routeTurnoutList.at(k).toElement()
                   .attribute("systemName");
           QString rState = routeTurnoutList.at(k).toElement()
                   .attribute("state");
           int tSetState = Sensor::INACTIVE;
           if (rState==("ACTIVE")) {
               tSetState = Sensor::ACTIVE;
           } else if (rState==("TOGGLE")) {
               tSetState = Route::TOGGLE;
           }
           // If the Turnout has already been added to the route and is the same as that loaded,
           // we will not re add the turnout.
           if (r->isOutputSensorIncluded(tSysName)) {
               break;
           }
           // Add turnout to route
           r->addOutputSensor(tSysName, tSetState);
       }
   }
   // load sound, script files if present
   QDomElement fileElement = el.firstChildElement("routeSoundFile");
   if (!fileElement.isNull()) {
       // convert to absolute path name
       r->setOutputSoundName(
               FileUtil::getExternalFilename(fileElement.attribute("name"))
       );
   }
   fileElement = el.firstChildElement("routeScriptFile");
   if (!fileElement.isNull())
   {
       r->setOutputScriptName(
               FileUtil::getExternalFilename(fileElement.attribute("name"))
       );
   }
   // load turnouts aligned sensor if there is one
   fileElement = el.firstChildElement("turnoutsAlignedSensor");
   if (!fileElement.isNull()) {
       r->setTurnoutsAlignedSensor(fileElement.attribute("name"));
   }

   // load route control sensors, if there are any
   QDomNodeList routeSensorList = el.elementsByTagName("routeSensor");
   if (routeSensorList.size() > 0) {
       // This route has sensors
       for (int k = 0; k < routeSensorList.size(); k++) {
           if (routeSensorList.at(k).toElement().attribute("systemName") == NULL) {
               log->warn("unexpected NULL in systemName " + routeSensorList.at(k).toElement().tagName()
                       /*+ " " + routeSensorList.at(k).toElement().attributes()*/);
               break;
           }
           int mode = Route::ONACTIVE;  // default mode
           if (routeSensorList.at(k).toElement().attribute("mode") != NULL) {
               QString sm = routeSensorList.at(k).toElement().attribute("mode");
               if (sm==("onActive")) {
                   mode = Route::ONACTIVE;
               } else if (sm==("onInactive")) {
                   mode = Route::ONINACTIVE;
               } else if (sm==("onChange")) {
                   mode = Route::ONCHANGE;
               } else if (sm==("vetoActive")) {
                   mode = Route::VETOACTIVE;
               } else if (sm==("vetoInactive")) {
                   mode = Route::VETOINACTIVE;
               } else {
                   log->warn("unexpected sensor mode in route " + sysName + " was " + sm);
               }
           }

           // Add Sensor to route
           r->addSensorToRoute(routeSensorList.at(k).toElement()
                   .attribute("systemName"), mode);
       }
   }

   // and start it working
   r->activateRoute();

  }
  if (namesChanged > 0) {
   // TODO: replace the System property check with an in-application mechanism
   // for notifying users of multiple changes that can be silenced as part of
   // normal operations
//   if (!GraphicsEnvironment.isHeadless() && !Boolean.getBoolean("jmri.test.no-dialogs"))
   {
    JOptionPane::showMessageDialog(nullptr,
       namesChanged > 1 ? tr("<html>The System Name of %1 routes were changed.<br><br>Please verify that references to these routes still work.<br>Review the logs to which routes were renamed.</html>").arg(namesChanged) : tr("<html>The System Name of %1 route was changed.<br><br>Please verify that references to this route still work.<br>Review the logs to see how the route was renamed.</html>").arg(namesChanged),
       tr("Changed System Name of %1 %2").arg(namesChanged).arg(tm->getBeanTypeHandled(namesChanged )),
       JOptionPane::WARNING_MESSAGE);
   }
   log->warn(tr("System names for %1 Routes changed; this may have operational impacts.").arg(namesChanged));
  }
 }
}

/**
 * Replace the current RouteManager, if there is one, with one newly created
 * during a load operation. This is skipped if the present one is already of
 * the right type
 */
/*protected*/ void DefaultRouteManagerXml::replaceRouteManager()
{
 RouteManager* current = (RouteManager*)InstanceManager::getNullableDefault("RouteManager");
 if (current != NULL && current->metaObject()->className()
     ==("DefaultRouteManager")) {
     return;
 }
 // if old manager exists, remove it from configuration process
 if (current != NULL)
 {
  ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->deregister(current);
  InstanceManager::deregister(current, "RouteManager");
 }

 // register new one with InstanceManager
 DefaultRouteManager* pManager = (DefaultRouteManager*)InstanceManager::getDefault("DefaultRouteManager");
 InstanceManager::store((QObject*)pManager, "RouteManager");
 // register new one for configuration
 static_cast<ConfigureManager*>(InstanceManager::getDefault("ConfigureManager"))->registerConfig((QObject*)pManager, Manager::ROUTES);
}

/*public*/ int DefaultRouteManagerXml::loadOrder() const {
    return ((RouteManager*)InstanceManager::getDefault("RouteManager"))->getXMLOrder();
}

