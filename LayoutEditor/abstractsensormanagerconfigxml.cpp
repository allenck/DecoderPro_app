#include "abstractsensormanagerconfigxml.h"
#include "sensormanager.h"
#include "instancemanager.h"
#include "abstractsensormanager.h"
#include "abstractsensor.h"
#include "level.h"

AbstractSensorManagerConfigXML::AbstractSensorManagerConfigXML(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("AbstractSensorManagerConfigXML");
}
AbstractSensorManagerConfigXML::~AbstractSensorManagerConfigXML()
{
 delete log;
}

/**
 * Provides the abstract base and store functionality for
 * configuring SensorManagers, working with
 * AbstractSensorManagers.
 * <P>
 * Typically, a subclass will just implement the load(QDomElement sensors)
 * class, relying on implementation here to load the individual sensors.
 * Note that these are stored explicitly, so the
 * resolution mechanism doesn't need to see *Xml classes for each
 * specific Sensor or AbstractSensor subclass at store time.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2002, 2008
 * @version $Revision: 18102 $
 */
///*public*/ abstract class AbstractSensorManagerConfigXML extends AbstractNamedBeanManagerConfigXML {

//    /*public*/ AbstractSensorManagerConfigXML() {
//    }

/**
 * Default implementation for storing the contents of a
 * SensorManager
 * @param o Object to store, of type SensorManager
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement AbstractSensorManagerConfigXML::store(QObject* o)
{
 QDomElement sensors = doc.createElement("sensors");
 return store(o, sensors);
}

/*public*/ QDomElement AbstractSensorManagerConfigXML::store(QObject* o, QDomElement sensors) {
 setStoreElementClass(sensors);
 SensorManager* tm = (SensorManager*) o;
 if(((AbstractSensorManager*)tm)->getDefaultSensorDebounceGoingActive()>0 || ((AbstractSensorManager*)tm)->getDefaultSensorDebounceGoingInActive()>0)
 {
  QDomElement elem = doc.createElement("globalDebounceTimers");
  QDomElement e1;
  elem.appendChild(e1=doc.createElement("goingActive"));
  e1.appendChild(doc.createTextNode(QString::number(((AbstractSensorManager*)tm)->getDefaultSensorDebounceGoingActive())));
  QDomElement e2;
  elem.appendChild(e2 = doc.createElement("goingInActive"));
  e2.appendChild(doc.createTextNode(QString::number(((AbstractSensorManager*)tm)->getDefaultSensorDebounceGoingInActive())));
  sensors.appendChild(elem);
 }
 QStringListIterator iter(((AbstractSensorManager*)tm)->getSystemNameList());

 // don't return an element if there are not sensors to include
 if (!iter.hasNext()) return QDomElement();
 // store the sensors
 while (iter.hasNext())
 {
  QString sname = iter.next();
  if (sname=="") log->error("System name NULL during store");
  log->debug("system name is "+sname);
  Sensor* s = ((AbstractSensorManager*)tm)->getBySystemName(sname);

  QString inverted = ((AbstractSensor*)s)->getInverted() ? "true" : "false";

  QDomElement elem = doc.createElement("sensor");
  elem.setAttribute("systemName", sname); // deprecated for 2.9.* series
  elem.setAttribute("inverted", inverted);
  QDomElement e1;
  elem.appendChild(e1 = doc.createElement("systemName"));
  e1.appendChild(doc.createTextNode(sname));
  log->debug("store sensor "+sname);
  if(((AbstractSensor*)s)->useDefaultTimerSettings())
  {
   QDomElement e1;
   elem.appendChild(e1=doc.createElement("useGlobalDebounceTimer"));
   e1.appendChild(doc.createTextNode("yes"));
  }
  else
  {
   if(((AbstractSensor*)s)->getSensorDebounceGoingActiveTimer()>0 || ((AbstractSensor*)s)->getSensorDebounceGoingInActiveTimer()>0)
   {
    QDomElement timer = doc.createElement("debounceTimers");
    QDomElement e1;
    timer.appendChild(e1 = doc.createElement("goingActive"));
    e1.appendChild(doc.createTextNode(QString::number(((AbstractSensor*)s)->getSensorDebounceGoingActiveTimer())));
    QDomElement e2;
    timer.appendChild(e2 =doc.createElement("goingInActive"));
    e2.appendChild(doc.createTextNode(QString::number(((AbstractSensor*)s)->getSensorDebounceGoingInActiveTimer())));
    elem.appendChild(timer);
   }
  }
  // store common part
  storeCommon(s, elem);

  sensors.appendChild(elem);

 }
 return sensors;
}

/**
 * Subclass provides implementation to create the correct top
 * element, including the type information.
 * Default implementation is to use the local class here.
 * @param sensors The top-level element being created
 */
// /*abstract*/ /*public*/ void setStoreElementClass(QDomElement sensors);

/**
 * Create a SensorManager object of the correct class, then
 * register and fill it.
 * @param sensors Top level QDomElement to unpack.
 */
// /*abstract*/ /*public*/ boolean load(QDomElement sensors) throw (JmriConfigureXmlException);

/**
 * Utility method to load the individual Sensor objects.
 * If there's no additional info needed for a specific sensor type,
 * invoke this with the parent of the set of Sensor elements.
 * @param sensors QDomElement containing the Sensor elements to load.
 * @return true if succeeded
 */
//@SuppressWarnings("unchecked")
/*public*/ bool AbstractSensorManagerConfigXML::loadSensors(QDomElement sensors) throw (JmriConfigureXmlException)
{
 bool result = true;
 QDomNodeList sensorList = sensors.elementsByTagName("sensor");
 if (log->isDebugEnabled()) log->debug("Found "+QString::number(sensorList.size())+" sensors");
 SensorManager* tm = InstanceManager::sensorManagerInstance();
 long goingActive = 0L;
 long goingInActive = 0L;
 if (!sensors.firstChildElement("globalDebounceTimers").isNull())
 {
  QDomElement timer = sensors.firstChildElement("globalDebounceTimers");
  try
  {
   if(!timer.firstChildElement("goingActive").isNull())
   {
    QString active = timer.firstChildElement("goingActive").text();
    goingActive = active.toLong();
    ((AbstractSensorManager*)tm)->setDefaultSensorDebounceGoingActive(goingActive);
   }
  }
  catch (NumberFormatException ex)
  {
   log->error(ex.getMessage());
  }

  try
  {
   if(!timer.firstChildElement("goingInActive").isNull())
   {
    QString inActive = timer.firstChildElement("goingInActive").text();
    goingInActive = inActive.toLong();
    ((AbstractSensorManager*)tm)->setDefaultSensorDebounceGoingInActive(goingInActive);
   }
  }
  catch (NumberFormatException ex)
  {
   log->error(ex.getMessage());
  }

 }

 for (int i=0; i<sensorList.size(); i++)
 {
  QString sysName = getSystemName(sensorList.at(i).toElement());
  if (sysName == NULL)
  {
   creationErrorEncountered (
                                  "Unexpected missing system name while loading sensors",
                                  NULL,NULL,NULL);
   result = false;
   break;
  }
  bool inverted = false;

  QString userName = getUserName(sensorList.at(i).toElement());

  if (sensorList.at(i).toElement().attribute("inverted") != NULL)
  if (sensorList.at(i).toElement().attribute("inverted")==("true"))
   inverted = true;

  if (log->isDebugEnabled()) log->debug("create sensor: ("+sysName+")");
  Sensor* s = ((ProxySensorManager*)tm)->newSensor(sysName, userName);

  if (s==NULL)
  {
   creationErrorEncountered (
                                  "Could not create sensor",
                                  sysName,userName,NULL);
   result = false;
   continue;
  }

  // load common parts
  loadCommon(s, sensorList.at(i).toElement());

  if(!sensorList.at(i).toElement().firstChildElement("debounceTimers").isNull())
  {
   QDomElement timer = sensorList.at(i).toElement().firstChildElement("debounceTimers");
   try
   {
    if(!timer.firstChildElement("goingActive").isNull())
    {
     QString active = timer.firstChildElement("goingActive").text();
     ((AbstractSensor*)s)->setSensorDebounceGoingActiveTimer(active.toLong());
    }
   }
   catch (NumberFormatException ex)
   {
    log->error(ex.getMessage());
   }

   try
   {
    if(!timer.firstChildElement("goingInActive").isNull())
    {
     QString inActive = timer.firstChildElement("goingInActive").text();
     ((AbstractSensor*)s)->setSensorDebounceGoingInActiveTimer(inActive.toLong());
    }
   }
   catch (NumberFormatException ex)
   {
    log->error(ex.getMessage());
   }
  }

  if (!sensorList.at(i).toElement().firstChildElement("useGlobalDebounceTimer").isNull())
  {
   if(sensorList.at(i).toElement().firstChildElement("useGlobalDebounceTimer").text()==("yes"))
   {
    ((AbstractSensor*)s)->useDefaultTimerSettings(true);
   }
  }
  ((AbstractSensor*)s)->setInverted(inverted);
 }
 return result;
}

/*public*/ int AbstractSensorManagerConfigXML::loadOrder(){
    return InstanceManager::sensorManagerInstance()->getXMLOrder();
}
