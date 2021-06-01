#include "lighticonxml.h"
#include "lighticon.h"
#include "editor.h"
#include "abstractlight.h"
#include "loggerfactory.h"

LightIconXml::LightIconXml(QObject *parent) :
    PositionableLabelXml(parent)
{

}
/**
 * Handle configuration for display.LightIcon objects.
 *
 * @author Pete Cressman Copyright: Copyright (c) 2011
 * @version $Revision: 17977 $
 */
//public class LightIconXml extends PositionableLabelXml {

//    public LightIconXml() {
//    }

/**
 * Default implementation for storing the contents of a LightIcon
 * @param o Object to store, of type LightIcon
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement LightIconXml::store(QObject* o)
{

 LightIcon* p = (LightIcon*)o;
    if (p->getLight() == nullptr || !p->isActive())
     return QDomElement();  // if flagged as inactive, don't store

    QDomElement element = doc.createElement("LightIcon");
    element.setAttribute("light", ((NamedBean*)p->getLight())->getSystemName());
    storeCommonAttributes((Positionable*)p, element);

    QDomElement elem =doc.createElement("icons");
    elem.appendChild(storeIcon("on", p->getOnIcon()));
    elem.appendChild(storeIcon("off", p->getOffIcon()));
    elem.appendChild(storeIcon("unknown", p->getUnknownIcon()));
    elem.appendChild(storeIcon("inconsistent", p->getInconsistentIcon()));
    element.appendChild(elem);

    element.setAttribute("class", "jmri.jmrit.display.configurexml.LightIconXml");

    return element;
}


/*public*/ bool LightIconXml::load(QDomElement /*element*/) throw (Exception){
    log->error("Invalid method called");
    return false;
}

/**
 * Create a PositionableLabel, then add to a target JLayeredPane
 * @param element Top level QDomElement to unpack.
 * @param o  Editor as an Object
 */
/*public*/ void LightIconXml::load(QDomElement element, QObject* o) throw (Exception)
{
 // create the objects
 Editor* p = (Editor*)o;

 l = new LightIcon(p, this);

 QString name;
 try
 {
  name=element.attribute("light");
 }
 catch ( NullPointerException e)
 {
  log->error("incorrect information for light; must use light name");
  p->loadFailed();
  return;
 }
 l->setLight(name);

 QDomElement icons = element.firstChildElement("icons");
 if (icons.isNull())
 {
  if (log->isDebugEnabled()) log->debug("Main element of Light "+name+"has no icons");
 }
 else
 {
  NamedIcon* icon = loadIcon(l, "on", icons, "LightIcon \""+name+"\": icon \"on\" ", p);
  if (icon!=NULL)
  {
   l->setOnIcon(icon);
  }
  else
  {
   log->info("LightIcon \""+name+"\": icon \"on\" removed");
   return;
  }
  icon = loadIcon(l, "off", icons, "LightIcon \""+name+"\": icon \"off\" ", p);
  if (icon!=NULL)
  {
   l->setOffIcon(icon);
  }
  else
  {
   log->info("LightIcon \""+name+"\": icon \"off\" removed");
   return;
  }
  icon = loadIcon(l, "unknown", icons, "LightIcon \""+name+"\": icon \"unknown\" ", p);
  if (icon!=NULL)
  {
   l->setUnknownIcon(icon);
  }
  else
  {
   log->info("LightIcon \""+name+"\": icon \"unknown\" removed");
   return;
  }
  icon = loadIcon(l, "inconsistent", icons, "LightIcon \""+name+"\": icon \"inconsistent\" ", p);
  if (icon!=NULL)
  {
   l->setInconsistentIcon(icon);
  }
  else
  {
   log->info("LightIcon \""+name+"\": icon \"inconsistent\" removed");
   return;
  }
 }
 loadCommonAttributes((Positionable*)l, Editor::LIGHTS, element);

 p->putItem((Positionable*)l);
 // load individual item's option settings after editor has set its global settings
 //Q_ASSERT(l->getLight()!=NULL);
}

LightIcon* LightIconXml::getIcon() { return l;}
/*static*/ Logger* LightIconXml::log = LoggerFactory::getLogger("LightIconXml");
//}

