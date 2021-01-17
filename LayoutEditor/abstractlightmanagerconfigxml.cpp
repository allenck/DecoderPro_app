#include "abstractlightmanagerconfigxml.h"
#include "instancemanager.h"
#include "internallightmanager.h"
#include "proxylightmanager.h"


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
   Light* lgt = (Light*)nb;
   QString sname = lgt->getSystemName();
   log->debug("system name is "+sname);
   QDomElement elem = doc.createElement("light");
   //elem.setAttribute("systemName", sname);
   QDomElement e1;
   elem.appendChild(e1=doc.createElement("systemName"));
   e1.appendChild(doc.createTextNode(sname));

   // store common parts
   storeCommon(lgt, elem);

   // write variable intensity attributes
   elem.setAttribute("minIntensity", lgt->getMinIntensity());
   elem.setAttribute("maxIntensity", lgt->getMaxIntensity());

   // write transition attribute
   elem.setAttribute("transitionTime", lgt->getTransitionTime());

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
 ProxyLightManager* tm = (ProxyLightManager*)InstanceManager::lightManagerInstance();

 for (int i=0; i<lightList.size(); i++)
 {

  QString sysName = getSystemName(lightList.at(i).toElement());
  if (sysName.isNull())
  {
   log->warn("unexpected NULL in systemName "+ lightList.at(i).toElement().tagName());
   result = false;
   break;
  }

  QString userName = getUserName(lightList.at(i).toElement());

 if (log->isDebugEnabled()) log->debug("create light: ("+sysName+")("+
                                                   (userName==NULL?"<NULL>":userName)+")");
 AbstractLight* lgt = (AbstractLight*)tm->newLight(sysName, userName);
 if (lgt!=NULL)
 {
  // load common parts
  loadCommon(lgt, lightList.at(i).toElement());

  // variable intensity, transition attributes
  double value;
  value = lightList.at(i).toElement().attribute("minIntensity").toDouble();
  lgt->setMinIntensity(value);

  value = lightList.at(i).toElement().attribute("maxIntensity").toDouble();
  lgt->setMaxIntensity(value);

  value = lightList.at(i).toElement().attribute("transitionTime").toDouble();
  lgt->setTransitionTime(value);

  // provide for legacy light control - panel files written by 2.9.5 or before
  if (lightList.at(i).toElement().attribute("controlType")!=NULL)
  {
   // this is a legacy Light - create a LightControl from the input
   QString temString = lightList.at(i).toElement().attribute("controlType");
   int type = Light::NO_CONTROL;
   bool bOk;
   type = temString.toInt(&bOk);
   if(!bOk)
   {
    log->error("error when converting control type in legacy Light load support");
    type = Light::NO_CONTROL;
   }
   if (type!=Light::NO_CONTROL)
   {
    // this legacy light has a control - capture it
    LightControl* lc = new LightControl(lgt);
    lc->setControlType(type);
    if (type==Light::SENSOR_CONTROL)
    {
     lc->setControlSensorName(lightList.at(i).toElement().attribute("controlSensor") );
     lc->setControlSensorSense( lightList.at(i).toElement().attribute("sensorSense").toInt(&bOk));
     if(!bOk)
     {
      log->error("error when converting control sensor sense in legacy Light load");
     }
    }
    else if (type==Light::FAST_CLOCK_CONTROL)
    {
     int onHour = 0;
     int onMin = 0;
     int offHour = 0;
     int offMin = 0;
     bOk=true;
     bool bOk1;
     onHour = lightList.at(i).toElement().attribute("fastClockOnHour").toInt(&bOk1);
     if(!bOk1) bOk = false;
     onMin = lightList.at(i).toElement().attribute("fastClockOnMin").toInt(&bOk1);
     if(!bOk1) bOk = false;
     offHour = lightList.at(i).toElement().attribute("fastClockOffHour").toInt(&bOk1);
     if(!bOk1) bOk = false;
     offMin = lightList.at(i).toElement().attribute("fastClockOffMin").toInt(&bOk1);
     if(!bOk1) bOk = false;
     if(!bOk)
     {
      log->error("error when converting fast clock items in legacy Light load");
     }
     lc->setFastClockControlSchedule(onHour,onMin,offHour,offMin);
    }
    else if (type==Light::TURNOUT_STATUS_CONTROL)
    {
     lc->setControlTurnout(lightList.at(i).toElement().attribute("controlTurnout"));
     bool bOk;
     lc->setControlTurnoutState(lightList.at(i).toElement().attribute("turnoutState").toInt(&bOk));
     if(!bOk)
     {
      log->error("error when converting turnout state in legacy Light load");
      }
    }
    else if (type==Light::TIMED_ON_CONTROL)
    {
     lc->setControlTimedOnSensorName(lightList.at(i).toElement().attribute("timedControlSensor"));
     bool bOk;
     lc->setTimedOnDuration( lightList.at(i).toElement().attribute("duration").toInt(&bOk));
     if(!bOk)
     {
      log->error("error when converting timed sensor items in legacy Light load");
     }
    }
    lgt->addLightControl(lc);
   }
  }

  // load lightcontrol children, if any
  QDomNodeList lightControlList = lightList.at(i).toElement().elementsByTagName("lightcontrol");
  for (int n = 0; n<lightControlList.size(); n++)
  {
   bool noErrors = true;
   QDomElement elem = lightControlList.at(n).toElement();
   LightControl* lc = new LightControl(lgt);
   QString tem = elem.attribute("controlType");
   int type = Light::NO_CONTROL;
   bool bOk;
   type = tem.toInt(&bOk);
   lc->setControlType(type);
   if(!bOk)
   {
    log->error("error when converting control type while loading light "+sysName);
    noErrors = false;
   }
   if (type==Light::SENSOR_CONTROL)
   {
    lc->setControlSensorName(elem.attribute("controlSensor") );
    lc->setControlSensorSense( elem.attribute("sensorSense").toInt(&bOk));
    if(!bOk)
    {
     log->error("error when converting control sensor sense while loading light "+sysName);
     noErrors = false;
    }
   }
   else if (type==Light::FAST_CLOCK_CONTROL)
   {
    int onHour = 0;
    int onMin = 0;
    int offHour = 0;
    int offMin = 0;
    bool bOk = true;
    bool bOk1;
    onHour = elem.attribute("fastClockOnHour").toInt(&bOk1);
    if(!bOk1) bOk = false;
    onMin =elem.attribute("fastClockOnMin").toInt(&bOk1);
    if(!bOk1) bOk = false;
    offHour = elem.attribute("fastClockOffHour").toInt(&bOk1);
    if(!bOk1) bOk = false;
    offMin = elem.attribute("fastClockOffMin").toInt(&bOk1);
    if(!bOk)
    {
     log->error("error when converting fast clock items while loading light "+sysName);
     noErrors = false;
    }
    else
     lc->setFastClockControlSchedule(onHour,onMin,offHour,offMin);

   }
   else if (type==Light::TURNOUT_STATUS_CONTROL)
   {
    lc->setControlTurnout(elem.attribute("controlTurnout"));
    bool bOk;
    lc->setControlTurnoutState(elem.attribute("turnoutState").toInt(&bOk));
    if(!bOk)
    {
     log->error("error when converting turnout state while loading light "+sysName);
     noErrors = false;
    }
   }
   else if (type==Light::TIMED_ON_CONTROL)
   {
    lc->setControlTimedOnSensorName(elem.attribute("timedControlSensor"));
    bool bOk;
    lc->setTimedOnDuration( elem.attribute("duration").toInt(&bOk));
    if(!bOk)
    {
     log->error("error when converting timed sensor items while loading light "+sysName);
     noErrors = false;
    }
   }
   else if (type==Light::TWO_SENSOR_CONTROL)
   {
    lc->setControlSensorName(elem.attribute("controlSensor") );
    lc->setControlSensor2Name(elem.attribute("controlSensor2") );
    bool bOk;
    lc->setControlSensorSense( elem.attribute("sensorSense").toInt(&bOk));
    if(!bOk)
    {
     log->error("error when converting control sensor2 sense while loading light "+sysName);
     noErrors = false;
    }
   }
   if (noErrors)
   {
    lgt->addLightControl(lc);
   }
  }

  // done, start it working
  lgt->activateLight();
 }
 else
  {
   log->error ("failed to create Light: "+sysName);
   result = false;
  }
 }
 return result;
}

/*public*/ int AbstractLightManagerConfigXML::loadOrder() const{
    return ((InternalLightManager*)InstanceManager::lightManagerInstance())->getXMLOrder();
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractLightManagerConfigXML.class.getName());
//}
void AbstractLightManagerConfigXML::setDoc(QDomDocument doc)
{
 this->doc = doc;
}
