#include "abstractlightmanagerconfigxml.h"
#include "instancemanager.h"
#include "internallightmanager.h"
#include "proxylightmanager.h"
#include "defaultlightcontrol.h"

AbstractLightManagerConfigXML::AbstractLightManagerConfigXML(QObject* parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("AbstractLightManagerConfigXML");
}
AbstractLightManagerConfigXML::~AbstractLightManagerConfigXML()
{
 delete log;
}

/**
 * Provides the abstract base and store functionality for
 * configuring LightManagers, working with
 * AbstractLightManagers.
 * <P>
 * Typically, a subclass will just implement the load(QDomElement sensors)
 * class, relying on implementation here to load the individual lights.
 * Note that these are stored explicitly, so the
 * resolution mechanism doesn't need to see *Xml classes for each
 * specific Light or AbstractLight subclass at store time.
 * <P>
 * Based on AbstractSensorManagerConfigXML.java
 *
 * @author Dave Duchamp Copyright (c) 2004, 2008, 2010
 * @version $Revision: 18102 $
 */
///*public*/ abstract class AbstractLightManagerConfigXML extends AbstractNamedBeanManagerConfigXML {

//    /*public*/ AbstractLightManagerConfigXML() {
//    }

/**
 * Default implementation for storing the contents of a
 * LightManager
 * @param o QObject* to store, of type LightManager
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement AbstractLightManagerConfigXML::store(QObject* o)
{
 QDomElement lights = doc.createElement("lights");
 setStoreElementClass(lights);
 LightManager* lm = (LightManager*) o;
 if (lm!=NULL)
 {
  QSet<NamedBean*> lightList = lm->getNamedBeanSet();

  // don't return an element if there are not lights to include
  if (lightList.isEmpty()) return QDomElement();

  // store the lights
  for (NamedBean* nb : lightList)
  {
   Light* lgt = (Light*)nb->self();
   QString sname = nb->getSystemName();
   log->debug("system name is "+sname);
   QDomElement elem = doc.createElement("light");
   //elem.setAttribute("systemName", sname);
   QDomElement e1;
   elem.appendChild(e1=doc.createElement("systemName"));
   e1.appendChild(doc.createTextNode(sname));

   // store common parts
   storeCommon(nb, elem);

   if (qobject_cast<VariableLight*>(lgt)) {
       elem.setAttribute("minIntensity",  QString::number(((VariableLight*)lgt)->getMinIntensity()));
       elem.setAttribute("maxIntensity", QString::number(((VariableLight*)lgt->self())->getMaxIntensity()));

       // write transition attribute
       elem.setAttribute("transitionTime", QString::number(((VariableLight*)lgt->self())->getTransitionTime()));
   } else {
       elem.setAttribute("minIntensity", "0.0");
       elem.setAttribute("maxIntensity", "1.0");

       // write transition attribute
       elem.setAttribute("transitionTime", "0.0");
   }

   // save child lightcontrol entries
   QList<LightControl*> lcList = lgt->getLightControlList();
   QDomElement lcElem = QDomElement();
   for (int i=0; i<lcList.size(); i++)
   {
    LightControl* lc = lcList.at(i);
    if (lc!=NULL)
    {
     lcElem = doc.createElement("lightcontrol");
     int type = lc->getControlType();
     lcElem.setAttribute("controlType", type);
     if (type==Light::SENSOR_CONTROL)
     {
      lcElem.setAttribute("controlSensor", lc->getControlSensorName() );
      lcElem.setAttribute("sensorSense", lc->getControlSensorSense() );
     }
     else if (type==Light::FAST_CLOCK_CONTROL)
     {
      lcElem.setAttribute("fastClockOnHour", lc->getFastClockOnHour() );
      lcElem.setAttribute("fastClockOnMin", lc->getFastClockOnMin() );
      lcElem.setAttribute("fastClockOffHour", lc->getFastClockOffHour() );
      lcElem.setAttribute("fastClockOffMin", lc->getFastClockOffMin() );
     }
     else if (type==Light::TURNOUT_STATUS_CONTROL)
     {
      lcElem.setAttribute("controlTurnout", lc->getControlTurnoutName() );
      lcElem.setAttribute("turnoutState", lc->getControlTurnoutState() );
     }
     else if (type==Light::TIMED_ON_CONTROL)
     {
      lcElem.setAttribute("timedControlSensor", lc->getControlTimedOnSensorName() );
      lcElem.setAttribute("duration", lc->getTimedOnDuration() );
     }
     if (type==Light::TWO_SENSOR_CONTROL)
     {
      lcElem.setAttribute("controlSensor", lc->getControlSensorName() );
      lcElem.setAttribute("controlSensor2", lc->getControlSensor2Name() );
      lcElem.setAttribute("sensorSense", lc->getControlSensorSense() );
     }
     elem.appendChild(lcElem);
    }
   }
   lights.appendChild(elem);
  }
 }
 return lights;
}

/**
 * Subclass provides implementation to create the correct top
 * element, including the type information.
 * Default implementation is to use the local class here.
 * @param lights The top-level element being created
 */
/*abstract*/ /*public*/ void AbstractLightManagerConfigXML::setStoreElementClass(QDomElement /*lights*/){}

/**
 * Create a LightManager object of the correct class, then
 * register and fill it.
 * @param lights Top level QDomElement to unpack.
 * @return true if successful
 */
/*abstract*/ /*public*/ bool AbstractLightManagerConfigXML::load(QDomElement /*lights*/) throw (Exception) {return false;}

/**
 * Utility method to load the individual Light objects.
 * If there's no additional info needed for a specific light type,
 * invoke this with the parent of the set of Light elements.
 * @param lights QDomElement containing the Light elements to load.
 */
//@SuppressWarnings("unchecked")
/*public*/ bool AbstractLightManagerConfigXML::loadLights(QDomElement lights)
{
 bool result = true;
 QDomNodeList lightList = lights.elementsByTagName("light");
 if (log->isDebugEnabled()) log->debug(tr("Found ")+QString("%1").arg(lightList.size())+" lights");
 LightManager* lm = InstanceManager::lightManagerInstance();
 lm->setPropertyChangesSilenced("beans", true);

 for (int i=0; i< lightList.count(); i++) {
  QDomElement el = lightList.at(i).toElement();
     QString sysName = getSystemName(el);
     if (sysName == "") {
         log->warn(tr("unexpected null in systemName %1 %2").arg(el.tagName()).arg(el.childNodes().count()));
         result = false;
         break;
     }

     QString userName = getUserName(el);

     checkNameNormalization(sysName, userName, lm);

     log->debug(tr("create light: (%1)(%2)").arg(sysName, (userName == "" ? "<null>" : userName)));

     Light* lgt = nullptr;
     try {
         lgt = lm->newLight(sysName, userName);
     } catch (IllegalArgumentException* e) {
         log->error(tr("failed to create Light: %1").arg(sysName));
         return false;
     }

     // load common parts
     loadCommon((NamedBean*)lgt, el);

     if (qobject_cast<VariableLight*>(lgt->self())) {
         // variable intensity, transition attributes
         double value;
         value = el.attribute("minIntensity").toDouble();
         ((VariableLight*)lgt->self())->setMinIntensity(value);

         value = el.attribute("maxIntensity").toDouble();
         ((VariableLight*)lgt->self())->setMaxIntensity(value);

         value = el.attribute("transitionTime").toDouble();
         ((VariableLight*)lgt->self())->setTransitionTime(value);
     }

     // provide for legacy light control - panel files written by 2.9.5 or before
     if (el.attribute("controlType") != "") {
         // this is a legacy Light - create a LightControl from the input
         QString temString = el.attribute("controlType");
         int type;
         bool ok;
             type = temString.toInt(&ok);
         if(!ok) {
             log->error("error when converting control type in legacy Light load support");
             type = Light::NO_CONTROL;
         }
         if (type != Light::NO_CONTROL) {
             // this legacy light has a control - capture it
             LightControl* lc = new DefaultLightControl(lgt);
             lc->setControlType(type);
             if (type == Light::SENSOR_CONTROL) {
                 lc->setControlSensorName(el.attribute("controlSensor"));
                 bool ok;
                     lc->setControlSensorSense(el.
                             attribute("sensorSense").toInt(&ok));
                 if(!ok) {
                     log->error("error when converting control sensor sense in legacy Light load");
                 }
             } else if (type == Light::FAST_CLOCK_CONTROL) {
                 int onHour = 0;
                 int onMin = 0;
                 int offHour = 0;
                 int offMin = 0;
                 try {
                  bool ok;
                     onHour = el.attribute("fastClockOnHour").toInt(&ok); if(!ok) throw new NumberFormatException();
                     onMin = el.attribute("fastClockOnMin").toInt(&ok); if(!ok) throw new NumberFormatException();
                     offHour = el.attribute("fastClockOffHour").toInt(&ok); if(!ok) throw new NumberFormatException();
                     offMin = el.attribute("fastClockOffMin").toInt(&ok); if(!ok) throw new NumberFormatException();
                 } catch (NumberFormatException* e) {
                     log->error("error when converting fast clock items in legacy Light load");
                 }
                 lc->setFastClockControlSchedule(onHour, onMin, offHour, offMin);
             } else if (type == Light::TURNOUT_STATUS_CONTROL) {
                 lc->setControlTurnout(el.attribute("controlTurnout"));
                 try {
                  bool ok;
                     lc->setControlTurnoutState(el.attribute("turnoutState").toInt(&ok)); if(!ok) throw new NumberFormatException();
                 } catch (NumberFormatException* e) {
                     log->error("error when converting turnout state in legacy Light load");
                 }
             } else if (type == Light::TIMED_ON_CONTROL) {
                 lc->setControlTimedOnSensorName(el.attribute("timedControlSensor"));
                 bool ok;
                     lc->setTimedOnDuration(el.attribute("duration").toInt(&ok));
                 if(!ok) {
                     log->error("error when converting timed sensor items in legacy Light load");
                 }

             }
             lgt->addLightControl(lc);
         }
     }

     // load lightcontrol children, if any
     QDomNodeList lightControlList = el.elementsByTagName("lightcontrol");
     for (int i=0; i < lightControlList.count(); i++) {
      QDomElement elem = lightControlList.at(i).toElement();
         bool noErrors = true;
         LightControl* lc = new DefaultLightControl(lgt);
         QString tem = elem.attribute("controlType");
         int type = Light::NO_CONTROL;
         bool ok;
             type = tem.toInt(&ok);
             lc->setControlType(type);
         if(!ok) {
             log->error(tr("error when converting control type while loading light %1").arg(sysName));
             noErrors = false;
         }
         if (type == Light::SENSOR_CONTROL) {
             lc->setControlSensorName(elem.attribute("controlSensor"));
             bool ok;
                 lc->setControlSensorSense(elem.attribute("sensorSense").toInt(&ok));
             if(!ok) {
                 log->error(tr("error when converting control sensor sense while loading light %1").arg(sysName));
                 noErrors = false;
             }
         } else if (type == Light::FAST_CLOCK_CONTROL) {
             int onHour = 0;
             int onMin = 0;
             int offHour = 0;
             int offMin = 0;
             try {
                 onHour = elem.attribute("fastClockOnHour").toInt(&ok); if(!ok) throw new NumberFormatException();
                 onMin = elem.attribute("fastClockOnMin").toInt(&ok); if(!ok) throw new NumberFormatException();
                 offHour = elem.attribute("fastClockOffHour").toInt(&ok); if(!ok) throw new NumberFormatException();
                 offMin = elem.attribute("fastClockOffMin").toInt(&ok); if(!ok) throw new NumberFormatException();
                 lc->setFastClockControlSchedule(onHour, onMin, offHour, offMin);
             } catch (NumberFormatException* e) {
                 log->error(tr("error when converting fast clock items while loading light %1").arg(sysName));
                 noErrors = false;
             }
         } else if (type == Light::TURNOUT_STATUS_CONTROL) {
             lc->setControlTurnout(elem.attribute("controlTurnout"));
             bool ok;
                 lc->setControlTurnoutState(elem.attribute("turnoutState").toInt(&ok)); if(!ok) throw new NumberFormatException();
             if(!ok) {
                 log->error(tr("error when converting turnout state while loading light %1").arg(sysName));
                 noErrors = false;
             }
         } else if (type == Light::TIMED_ON_CONTROL) {
             lc->setControlTimedOnSensorName(elem.attribute("timedControlSensor"));
             bool ok;
                 lc->setTimedOnDuration(elem.attribute("duration").toInt(&ok)); if(!ok) throw new NumberFormatException();
             if(!ok) {
                 log->error(tr("error when converting timed sensor items while loading light %1").arg(sysName));
                 noErrors = false;
             }
         } else if (type == Light::TWO_SENSOR_CONTROL) {
             lc->setControlSensorName(elem.attribute("controlSensor"));
             lc->setControlSensor2Name(elem.attribute("controlSensor2"));
             bool ok;
                 lc->setControlSensorSense(elem.attribute("sensorSense").toInt(&ok));
             if(!ok) {
                 log->error(tr("error when converting control sensor2 sense while loading light %1").arg(sysName));
                 noErrors = false;
             }
         }
         if (noErrors) {
             lgt->addLightControl(lc);
         }
     }

     // done, start it working
     lgt->activateLight();
 }

 lm->setPropertyChangesSilenced("beans", false);
 return result;
}

/*public*/ int AbstractLightManagerConfigXML::loadOrder() const{
    return /*((InternalLightManager*)*/InstanceManager::lightManagerInstance()->getXMLOrder();
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractLightManagerConfigXML.class.getName());
//}
void AbstractLightManagerConfigXML::setDoc(QDomDocument doc)
{
 this->doc = doc;
}
