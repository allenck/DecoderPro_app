#include "defaultsignalgroupmanagerxml.h"
#include "signalgroup.h"
#include "signalhead.h"
#include "signalgroupmanager.h"
#include "instancemanager.h"
#include "signalheadmanager.h"
#include "defaultsignalgroupmanager.h"
#include "abstractsignalheadmanager.h"
#include "proxyturnoutmanager.h"
#include "proxysensormanager.h"
#include "defaultsignalgroup.h"

DefaultSignalGroupManagerXml::DefaultSignalGroupManagerXml(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("DefaultSignalGroupManagerXml");
 setObjectName("DefaultSignalGroupManagerXml");
}
/**
 * Handle XML configuration for a DefaultSignalGroupManager objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2009
 * @version $Revision: 18962 $
 */
// /*public*/ class DefaultSignalGroupManagerXml
//            extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

//    /*public*/ DefaultSignalGroupManagerXml() {}

/**
 * Default implementation for storing the contents of a
 * DefaultSignalGroupManager
 * @param o Object to store, of type TripleTurnoutSignalHead
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement DefaultSignalGroupManagerXml::store(QObject* o)
{
 SignalGroupManager* m = (SignalGroupManager*)o;

 QDomElement element = doc.createElement("signalgroups");
 element.setAttribute("class", "jmri.managers.configurexml.DefaultSignalGroupManagerXml");

 // include contents
 QStringList names = m->getSystemNameList();
 for (int i = 0; i < names.size(); i++)
 {
  QDomElement e = doc.createElement("signalgroup");
  SignalGroup* p = m->getSignalGroup(names.at(i));
  e.setAttribute("systemName", p->getSystemName()); // deprecated for 2.9.* series
  e.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(p->getSystemName())));
  e.setAttribute("userName", p->getUserName());
  //storeCommon(p, e);
  element.appendChild(e);
  for (int x=0; x < p->getNumSignalMastAppearances(); x++)
  {
   QDomElement app = doc.createElement("appearance");
   app.setAttribute("valid", p->getSignalMastAppearanceByIndex(x));
   e.appendChild(app);
  }
  e.setAttribute("signalMast", p->getSignalMastName());

  for (int x=0; x<p->getNumSignalHeadItems(); x++)
  {
    storeSignalHead(e, p, x);
  }
 }
 return element;
}

/*private*/ void DefaultSignalGroupManagerXml::storeSignalHead(QDomElement element, SignalGroup* _group, int x){
    QDomElement group = doc.createElement("signalHead");
    QString name = _group->getSignalHeadItemNameByIndex(x);
    group.setAttribute("name", name);
    group.setAttribute("onAppearance", getSignalColour(_group->getSignalHeadOnStateByIndex(x)));
    group.setAttribute("offAppearance", getSignalColour(_group->getSignalHeadOffStateByIndex(x)));
    if(_group->getSensorTurnoutOperByIndex(x))
        group.setAttribute("sensorTurnoutLogic", "AND");
    else
        group.setAttribute("sensorTurnoutLogic", "OR");

    for (int i = 0; i<_group->getNumSignalHeadTurnoutsByIndex(x); i++){
        storeTurnout(group, _group, x, i);
    }
    for (int i = 0; i<_group->getNumSignalHeadSensorsByIndex(x); i++){
        storeSensor(group, _group, x, i);
    }

    element.appendChild(group);
}

/*private*/ void DefaultSignalGroupManagerXml::storeTurnout(QDomElement element, SignalGroup* _group, int x, int turn){
    QDomElement turnout = doc.createElement("turnout");
    turnout.setAttribute("name", _group->getTurnoutNameByIndex(x, turn));
    turnout.setAttribute("state", _group->getTurnoutStateByIndex(x, turn));
    element.appendChild(turnout);
}

/*private*/ void DefaultSignalGroupManagerXml::storeSensor(QDomElement element, SignalGroup* _group, int x, int sensor){
    QDomElement Sensor = doc.createElement("sensor");
    Sensor.setAttribute("name", _group->getSensorNameByIndex(x, sensor));
    Sensor.setAttribute("state", _group->getSensorStateByIndex(x, sensor));
    element.appendChild(Sensor);
}

/*public*/ void DefaultSignalGroupManagerXml::setStoreElementClass(QDomElement signalGroup) {
    signalGroup.setAttribute("class","jmri.managers.configurexml.DefaultSignalGroupManagerXml");
}

/*private*/ QString DefaultSignalGroupManagerXml::getSignalColour(int mAppearance){
    switch(mAppearance){
        case SignalHead::RED:
                return "RED";
        case SignalHead::FLASHRED:
                return "FLASHRED";
        case SignalHead::YELLOW:
                return "YELLOW";
        case SignalHead::FLASHYELLOW:
                return "FLASHYELLOW";
        case SignalHead::GREEN:
                return "GREEN";
        case SignalHead::FLASHGREEN:
                return "FLASHGREEN";
        case SignalHead::LUNAR:
                return "LUNAR";
        case SignalHead::FLASHLUNAR:
                return "FLASHLUNAR";
        case SignalHead::DARK:
                return "DARK";
        default:
                log->warn("Unexpected appearance: "+mAppearance);
            // go dark
                return "DARK";
    }
}
/**
 * Create a DefaultSignalGroupManager
 * @param element Top level QDomElement to unpack.
 * @return true if successful
 */
 //@SuppressWarnings("unchecked")
/*public*/ bool DefaultSignalGroupManagerXml::load(QDomElement element) throw (Exception)
{
 // loop over contained signalgroup elements
 QDomNodeList list = element.elementsByTagName("signalgroup");

 DefaultSignalGroupManager* sgm = (DefaultSignalGroupManager*)InstanceManager::signalGroupManagerInstance();

 for (int i = 0; i < list.size(); i++)
 {
  DefaultSignalGroup* m;
  QDomElement e = list.at(i).toElement();
  QString primary;
  QString yesno;
  bool inverse =false;
  int state =0x00;

  QString sys = getSystemName(e);

  m = (DefaultSignalGroup*)sgm->newSignalGroup(sys);

  if (getUserName(e) != "")
   m->setUserName(getUserName(e));

  primary = e.attribute("signalMast");
  m->setSignalMast(primary);

  QDomNodeList appList = e.elementsByTagName("appearance");
  for(int y = 0; y<appList.size(); y++)
  {
   QString value = appList.at(y).toElement().attribute("valid");
   m->addSignalMastAppearance(value);
  }
  //loadCommon(m, e);
  QDomNodeList signalHeadList = list.at(i).toElement().elementsByTagName("signalHead");
  if (signalHeadList.size() > 0)
  {
   for (int y = 0; y<signalHeadList.size(); y++)
   {
    QString head = signalHeadList.at(y).toElement().attribute("name");
    SignalHead* sigHead = ((AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance())->getSignalHead(head);
    m->addSignalHead(sigHead);
    yesno = signalHeadList.at(y).toElement().attribute("sensorTurnoutLogic");
    inverse = false;
    if ( (yesno !=("")) )
    {
     if (yesno==("AND")) inverse=true;
      else if (yesno==("OR")) inverse=false;
    }
    m->setSensorTurnoutOper(sigHead, inverse);

    try
    {
     m->setSignalHeadOnState(sigHead, getIntFromColour(signalHeadList.at(y).toElement().attribute("onAppearance")));
    }
     catch ( NullPointerException ex) {  // considered normal if the attributes are not present
    }
    try
    {
     m->setSignalHeadOffState(sigHead, getIntFromColour(signalHeadList.at(y).toElement().attribute("offAppearance")));
    }
    catch ( NullPointerException ex) {  // considered normal if the attributes are not present
    }
    QDomNodeList signalTurnoutList = signalHeadList.at(y).toElement().elementsByTagName("turnout");
    if (signalTurnoutList.size() > 0)
    {
     for(int k = 0; k<signalTurnoutList.size(); k++)
     {
      QString tName = signalTurnoutList.at(k).toElement().attribute("name");
      Turnout* turnout = ((AbstractTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(tName);
      state = 0;
      try
      {
       state = signalTurnoutList.at(k).toElement().attribute("state").toInt();
      }
      catch (DataConversionException ex)
      {
       log->warn("invalid state attribute value");
      }
      m->setSignalHeadAlignTurnout(sigHead, turnout, state);
     }
    }
    QDomNodeList signalSensorList = signalHeadList.at(y).toElement().elementsByTagName("sensor");
    if (signalSensorList.size() > 0)
    {
     for(int k = 0; k<signalSensorList.size(); k++)
     {
      QString sName = signalSensorList.at(k).toElement().attribute("name");
      Sensor* sensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(sName);
      state = 0;
      try
      {
       state = signalSensorList.at(k).toElement().attribute("state").toInt();
      }
      catch (DataConversionException ex)
      {
       log->warn("invalid style attribute value");
      }
      m->setSignalHeadAlignSensor(sigHead, sensor, state);
     }
    }
   }
  }
 }
 return true;
}

/*public*/ void DefaultSignalGroupManagerXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception){
    log->error("Invalid method called");
}

/*private*/ int DefaultSignalGroupManagerXml::getIntFromColour(QString colour){
    if (colour==("RED")) return SignalHead::RED;
    else if (colour==("YELLOW")) return SignalHead::YELLOW;
    else if (colour==("GREEN")) return SignalHead::GREEN;
    else if (colour==("LUNAR")) return SignalHead::LUNAR;
    else if (colour==("DARK")) return SignalHead::DARK;
    else if (colour==("FLASHRED")) return SignalHead::FLASHRED;
    else if (colour==("FLASHYELLOW")) return SignalHead::FLASHYELLOW;
    else if (colour==("FLASHGREEN")) return SignalHead::FLASHGREEN;
    else if (colour==("FLASHLUNAR")) return SignalHead::FLASHLUNAR;
    else log->warn("Unexpected appearance: "+colour);
    return SignalHead::DARK;
}

/*public*/ int DefaultSignalGroupManagerXml::loadOrder(){
    return InstanceManager::signalGroupManagerInstance()->getXMLOrder();
}
