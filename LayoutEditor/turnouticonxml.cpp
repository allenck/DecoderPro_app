#include "turnouticonxml.h"
#include "turnouticon.h"
#include "editor.h"
#include "level.h"

/*static*/ /*final*/ QMap<QString,QString>* TurnoutIconXml::_nameMap = new QMap<QString,QString>();

TurnoutIconXml::TurnoutIconXml(QObject *parent) :
    PositionableLabelXml(parent)
{
 log = new Logger("TurnoutIconXml");
 _nameMap = new QMap<QString,QString>();
 _nameMap->insert("closed", "TurnoutStateClosed");
 _nameMap->insert("thrown", "TurnoutStateThrown");
 _nameMap->insert("unknown", "BeanStateUnknown");
 _nameMap->insert("inconsistent", "BeanStateInconsistent");
}
/**
 * Handle configuration for display.TurnoutIcon objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2002
 * @version $Revision: 17977 $
 */
//public class TurnoutIconXml extends PositionableLabelXml {


//    public TurnoutIconXml() {
//        // map previous store names to actual localized names
//        _nameMap.put("closed", "TurnoutStateClosed");
//        _nameMap.put("thrown", "TurnoutStateThrown");
//        _nameMap.put("unknown", "BeanStateUnknown");
//        _nameMap.put("inconsistent", "BeanStateInconsistent");
//    }

/**
 * Default implementation for storing the contents of a
 * TurnoutIcon
 * @param o Object to store, of type TurnoutIcon
 * @return Element containing the complete info
 */
/*public*/ QDomElement TurnoutIconXml::store(QObject* o)
{

 TurnoutIcon* p = (TurnoutIcon*)o;
 if (!p->isActive()) return QDomElement();  // if flagged as inactive, don't store
 if(p->getNamedTurnout() == NULL) return QDomElement(); // TODO: figure out why namedTurnout is NULL
 QDomElement element = doc.createElement("turnouticon");
 element.setAttribute("turnout", p->getNamedTurnout()->getName());
 storeCommonAttributes((Positionable*)p, element);

 element.setAttribute("tristate", p->getTristate()?"true":"false");

 QDomElement elem = doc.createElement("icons");
#if 1
 elem.appendChild(storeIcon("closed", p->getIcon("TurnoutStateClosed")));
 elem.appendChild(storeIcon("thrown",p->getIcon("TurnoutStateThrown")));
 elem.appendChild(storeIcon("unknown", p->getIcon("BeanStateUnknown")));
 elem.appendChild(storeIcon("inconsistent", p->getIcon("BeanStateInconsistent")));
 element.appendChild(elem);
#else
 // TODO:
#endif
 elem = doc.createElement("iconmaps");
 QString family = p->getFamily();
 if (family!="")
 {
  elem.setAttribute("family", family);
 }
 element.appendChild(elem);

 element.setAttribute("class", "jmri.jmrit.display.configurexml.TurnoutIconXml");

 return element;
}


/*public*/ bool TurnoutIconXml::load(QDomElement /*element*/) throw (Exception)
{
 log->error("Invalid method called");
 return false;
}

/**
 * Create a PositionableLabel, then add to a target JLayeredPane
 * @param element Top level Element to unpack.
 * @param o  Editor as an Object
 */
//@SuppressWarnings("NULL")
/*public*/ void TurnoutIconXml::load(QDomElement element, QObject* o) throw (Exception)
{
 // create the objects
 Editor* p = (Editor*)o;

 l = new TurnoutIcon(p);

 QString name;
// try {
 name=element.attribute("turnout");
//    } catch ( NullPointerException e) {
 if(name == "")
 {
  log->error("incorrect information for turnout; must use turnout name");
  p->loadFailed();
  return;
 }
 l->setTurnout(name);

 QString a = element.attribute("tristate");
 if ( (a=="") || ((a!="") && a==("true")))
  l->setTristate(true);
 else
  l->setTristate(false);

 //@SuppressWarnings("unchecked")
 QDomNodeList states = element.childNodes();
 if (states.size()>0)
 {
  if (log->isDebugEnabled()) log->debug("Main element has"+QString("%1").arg(states.size())+" items");
  QDomElement elem = element;     // the element containing the icons
  QDomElement icons = element.firstChildElement("icons");
  if (!icons.isNull())
  {
   //@SuppressWarnings("unchecked")
   QDomNodeList s = icons.childNodes();
   states = s;
   elem = icons;          // the element containing the icons
   if (log->isDebugEnabled()) log->debug("icons element has"+QString("%1").arg(states.size())+" items");
  }
  for (int i=0; i<states.size(); i++)
  {
   QString state = states.at(i).toElement().tagName();
   if (log->isDebugEnabled()) log->debug("setIcon for state \""+state+ "\" and "+_nameMap->value(state));
   NamedIcon* icon = loadIcon(l, state, elem, "TurnoutIcon \""+name+"\": icon \""+state+"\" ", p);
   if (icon!=NULL)
   {
    l->setIcon(_nameMap->value(state), icon);
   }
   else
   {
    log->info("TurnoutIcon \""+name+"\": icon \""+state+"\" removed");
    return;
   }
  }
  log->debug(QString("%1").arg(states.size())+" icons loaded for "+l->getNameString());
 }
 else
 { // case when everything was attributes
  int rotation = 0;
  //try {
  bool bOk;
  rotation = element.attribute("rotate", "0").toInt(&bOk);
//        } catch (org.jdom.DataConversionException e) {
//        } catch ( NullPointerException e) {  // considered normal if the attributes are not present
//        }
  if (loadTurnoutIcon("thrown", rotation, l, element, name, p)==NULL)
  {
   return;
  }
  if (loadTurnoutIcon("closed", rotation, l, element, name, p)==NULL)
  {
   return;
  }
  if (loadTurnoutIcon("unknown", rotation, l,element, name, p)==NULL)
  {
   return;
  }
  if (loadTurnoutIcon("inconsistent", rotation, l,element, name, p)==NULL)
  {
   return;
  }
 }
 QDomElement elem = element.firstChildElement("iconmaps");
 if (!elem.isNull())
 {
  QString attr = elem.attribute("family");
  if (attr!="")
  {
   l->setFamily(attr);
  }
 }
 loadCommonAttributes((Positionable*)l, Editor::TURNOUTS, element);
 l->setDisplayLevel(Editor::TURNOUTS);
 p->putItem((Positionable*)l);
 // load individual item's option settings after editor has set its global settings
 //loadCommonAttributes((Positionable*)l, Editor::TURNOUTS, element);
}

/*private*/ NamedIcon* TurnoutIconXml::loadTurnoutIcon(QString state, int rotation, TurnoutIcon* l, QDomElement element, QString name, Editor* ed)
{
 NamedIcon* icon = NULL;
 if (element.attribute(state) != "")
 {
  QString iconName = element.attribute(state);
  icon = NamedIcon::getIconByName(iconName);
  if (icon==NULL)
  {
   icon = ed->loadFailed("Turnout \""+name+"\" icon \""+state+"\" ", iconName);
   if (icon==NULL)
   {
    log->info("Turnout \""+name+"\" icon \""+state+"\" removed for url= "+iconName);
   }
  }
  else
  {
   icon->setRotation(rotation, l);
  }
 }
 else log->warn("did not locate " + state + " icon file for Turnout "+name);
 if (icon==NULL)
 {
  log->info("Turnout Icon \""+name+"\": icon \""+state+"\" removed");
 }
 else
 {
  l->setIcon(_nameMap->value(state), icon);
 }
 return icon;
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(TurnoutIconXml.class.getName());
//}
TurnoutIcon* TurnoutIconXml::getIcon() { return l;}
