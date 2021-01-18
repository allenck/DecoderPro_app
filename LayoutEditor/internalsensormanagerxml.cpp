#include "internalsensormanagerxml.h"
#include "sensor.h"
#include "internalsensormanager.h"
InternalSensorManagerXml::InternalSensorManagerXml(QObject *parent) :
    AbstractSensorManagerConfigXML(parent)
{
 log = new Logger("InternalSensorManagerXml");
 setObjectName("InternalSensorManagerXml");
}
/**
 * Provides load and store functionality for
 * configuring InternalSensorManagers.
 * <P>
 * Uses the store method from the abstract base class, but
 * provides a load method here.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2006
 * @version $Revision: 17977 $
 */
///*public*/ class InternalSensorManagerXml extends jmri.managers.configurexml.AbstractSensorManagerConfigXML {

//    /*public*/ InternalSensorManagerXml() {
//        super();
//    }

/*public*/ void InternalSensorManagerXml::setStoreElementClass(QDomElement sensors) {
 sensors.setAttribute("class","jmri.managers.configurexml.InternalSensorManagerXml");
}

/*public*/ void InternalSensorManagerXml::load(QDomElement element, QObject* o) throw (Exception){
    log->error("Invalid method called");
}

/*public*/ QDomElement InternalSensorManagerXml::store(QObject* o)
{
 QDomElement sensors = doc.createElement("sensors");

 QString defaultState;
 switch (InternalSensorManager::getDefaultStateForNewSensors()) {
     case Sensor::ACTIVE:
         defaultState = "active";
         break;
     case Sensor::INACTIVE:
         defaultState = "inactive";
         break;
     case Sensor::INCONSISTENT:
         defaultState = "inconsistent";
         break;
     default:
         defaultState = "unknown";
 }

 QDomElement s1;
 sensors.appendChild(s1 = doc.createElement("defaultInitialState"));
 s1.appendChild(doc.createTextNode(defaultState));

 return AbstractSensorManagerConfigXML::store(o, sensors);
}

/*public*/ bool InternalSensorManagerXml::load(QDomElement sharedSensors, QDomElement perNodeSensors) throw (JmriConfigureXmlException) {
 // load individual sensors
 if (sharedSensors.firstChildElement("defaultInitialState") != QDomElement())
 {
  int defaultState = Sensor::UNKNOWN;
  QString state = sharedSensors.firstChildElement("defaultInitialState").text();
  if (state==("active"))
  {
   defaultState = Sensor::ACTIVE;
  }
  else if (state==("inactive"))
  {
   defaultState = Sensor::INACTIVE;
  }
  else if (state==("inconsistent"))
  {
   defaultState = Sensor::INCONSISTENT;
  }
  InternalSensorManager::setDefaultStateForNewSensors(defaultState);
 }
 return loadSensors(sharedSensors);
}
