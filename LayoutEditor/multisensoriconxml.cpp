#include "multisensoriconxml.h"
#include "multisensoricon.h"
#include "namedicon.h"
#include "editor.h"

MultiSensorIconXml::MultiSensorIconXml(QObject *parent) :
    PositionableLabelXml(parent)
{
 log = new Logger("MultiSensorIconXml");
 setObjectName("MultiSensorIconXml");
}
/**
 * Handle configuration for display.MultiSensorIcon objects
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2002
 * @version $Revision: 17977 $
 */
// /*public*/ class MultiSensorIconXml extends PositionableLabelXml {

///*public*/ MultiSensorIconXml() {
//}

/**
 * Default implementation for storing the contents of a
 * MultiSensorIcon
 * @param o Object to store, of type MultiSensorIcon
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement MultiSensorIconXml::store(QObject* o)
{

 MultiSensorIcon* p = (MultiSensorIcon*)o;
 if (!p->isActive()) return QDomElement();  // if flagged as inactive, don't store

 QDomElement element = doc.createElement("multisensoricon");
 storeCommonAttributes((Positionable*)p, element);

 element.setAttribute("updown", p->getUpDown()?"true":"false");

 for (int i = 0; i < p->getNumEntries(); i++)
 {
  QDomElement e = storeIcon("active", p->getSensorIcon(i));
  e.setAttribute("sensor", p->getSensorName(i));
  element.appendChild(e);
 }
 element.appendChild(storeIcon("inactive", p->getInactiveIcon()));
 element.appendChild(storeIcon("unknown", p->getUnknownIcon()));
 element.appendChild(storeIcon("inconsistent", p->getInconsistentIcon()));

 element.setAttribute("class", "jmri.jmrit.display.configurexml.MultiSensorIconXml");
 return element;
}


/*public*/ bool MultiSensorIconXml::load(QDomElement element) throw (Exception)
{
 log->error("Invalid method called");
 return false;
}

/**
 * Create a PositionableLabel, then add to a target JLayeredPane
 * @param element Top level QDomElement to unpack.
 * @param o  an Editor an Object
 */
//@SuppressWarnings("unchecked")
/*public*/ void MultiSensorIconXml::load(QDomElement element, QObject* o) throw (Exception)
{
 Editor* pe = (Editor*)o;
 l = new MultiSensorIcon(pe);
 // create the objects
 int rotation = 0;
 try
 {
  rotation = element.attribute("rotate").toInt();
 }
 catch (DataConversionException e)
 {    }
 catch ( NullPointerException e)
 {  // considered normal if the attributes are not present
 }

 NamedIcon* icon = loadSensorIcon("inactive", rotation, l, element, pe);
 if (icon!=NULL)
 {
  l->setInactiveIcon(icon);
 }
 else { return; }
 icon = loadSensorIcon("unknown", rotation, l,element, pe);
 if (icon!=NULL)
 {
  l->setUnknownIcon(icon);
 }
 else { return; }
 icon = loadSensorIcon("inconsistent", rotation, l,element, pe);
 if (icon!=NULL)
 {
  l->setInconsistentIcon(icon);
 }
 else { return; }

 QString a = element.attribute("updown");
 if ( (a!="") && a==("true"))
   l->setUpDown(true);
 else
  l->setUpDown(false);

 // get the icon pairs & load
 QDomNodeList  items = element.childNodes();
 for (int i = 0; i<items.size(); i++)
 {
  // get the class, hence the adapter object to do loading
  QDomElement item = items.at(i).toElement();
  if (item.attribute("sensor")!="")
  {
   QString sensor = item.attribute("sensor");
   if (item.attribute("url")!="")
   {
    QString name = item.attribute("url");
    icon = NamedIcon::getIconByName(name);
    if (icon==NULL)
    {
     icon = pe->loadFailed("MultiSensor \""+l->getNameString()+"\" ", name);
     if (icon==NULL)
     {
      log->error("MultiSensor \""+l->getNameString()+"\" removed for url= "+name);
      return;
     }
    }
    try
    {
     int deg = 0;
     a = item.attribute("degrees");
     if (a!="")
     {
      deg = a.toInt();
      double scale = 1.0;
      a =  item.attribute("scale");
      if (a!="")
      {
       scale = item.attribute("scale").toDouble();
      }
      icon->setLoad(deg, scale, l);
     }
     if (deg==0)
     {
      a = item.attribute("rotate");
      if (a!="")
      {
       rotation = a.toInt();
       icon->setRotation(rotation, l);
      }
     }
    }
    catch (DataConversionException dce) {}
   }
   else
   {
    QString name = item.attribute("icon");
    icon = NamedIcon::getIconByName(name);
    if (icon==NULL)
    {
     icon = pe->loadFailed("MultiSensor \""+l->getNameString(), name);
     if (icon==NULL)
     {
      log->info("MultiSensor \""+l->getNameString()+" removed for url= "+name);
      return;
     }
    }
    if (rotation!=0) icon->setRotation(rotation, l);
   }

   l->addEntry(sensor, icon);
  }
 }
 // load individual item's option settings after editor has set its global settings
 loadCommonAttributes((Positionable*)l, Editor::SENSORS, element);

 pe->putItem((Positionable*)l);

}

/*private*/ NamedIcon* MultiSensorIconXml::loadSensorIcon(QString state, int rotation, MultiSensorIcon* l, QDomElement element, Editor* ed)
{
 QString msg = "MultiSensor \""+l->getNameString()+"\": icon \""+state+"\" ";
 NamedIcon* icon = loadIcon(l,state, element, msg, ed);
 if (icon==NULL)
 {
  if (element.attribute(state) != "")
  {
   QString iconName = element.attribute(state);
   icon = NamedIcon::getIconByName(iconName);
   if (icon==NULL)
   {
    icon = ed->loadFailed(msg, iconName);
    if (icon==NULL)
    {
     log->info(msg+" removed for url= "+iconName);
    }
   }
   else
   {
    icon->setRotation(rotation, l);
   }
  }
  else log->warn("did not locate " + state + " for Multisensor icon file");
 }
 if (icon==NULL)
 {
  log->info("MultiSensor Icon \""+l->getNameString()+"\": icon \""+state+"\" removed");
 }
 return icon;
}
MultiSensorIcon* MultiSensorIconXml::getIcon() { return l;}
