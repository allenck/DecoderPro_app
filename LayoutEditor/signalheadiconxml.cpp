#include "signalheadiconxml.h"
#include "../LayoutEditor/signalheadicon.h"
#include "instancemanager.h"
#include "abstractsignalheadmanager.h"
#include "abstractsignalhead.h"
#include "editor.h"

//SignalHeadIconXml::SignalHeadIconXml(QObject *parent) :
//    PositionableLabelXml(parent)
//{
//}
/*static*/ /*final*/ QMap<QString,QString> SignalHeadIconXml::_nameMap =  QMap<QString,QString>();

/**
 * Handle configuration for display.SignalHeadIcon objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2002
 * @version $Revision: 18010 $
 */
///*public*/ class SignalHeadIconXml extends PositionableLabelXml {

//    static final java.util.ResourceBundle rbean = java.util.ResourceBundle.getBundle("jmri.NamedBeanBundle");
    static /*final*/ QMap<QString,QString> _nameMap =  QMap<QString,QString>();

/*public*/ SignalHeadIconXml::SignalHeadIconXml(QObject* parent) : PositionableLabelXml(parent)
    {
        log = new Logger("SignalHeadIconXml");
    // map previous store names to actual localized names
    _nameMap.insert("red", tr("Red"));
    _nameMap.insert("yellow", tr("Yellow"));
    _nameMap.insert("green", tr("Green"));
    _nameMap.insert("lunar", tr("Lunar"));
    _nameMap.insert("held", tr("Held"));
    _nameMap.insert("dark", tr("Dark"));
    _nameMap.insert("flashred", tr("Flashing Red"));
    _nameMap.insert("flashyellow", tr("Flashing Yellow"));
    _nameMap.insert("flashgreen", tr("Flashing Green"));
    _nameMap.insert("flashlunar", tr("Flashing Lunar"));
}

/**
 * Default implementation for storing the contents of a
 * SignalHeadIcon
 * @param o Object to store, of type SignalHeadIcon
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement SignalHeadIconXml::store(QObject* o)
{
 log = new Logger("SignalHeadIconXml");

 SignalHeadIcon* p = (SignalHeadIcon*)o;
 if (!p->isActive()) return QDomElement();  // if flagged as inactive, don't store

 QDomElement element = doc.createElement("signalheadicon");

 element.setAttribute("signalhead", p->getNamedSignalHead()->getName());
 storeCommonAttributes((Positionable*)p, element);
 element.setAttribute("clickmode", p->getClickMode());
 element.setAttribute("litmode", p->getLitMode());

 QDomElement elem = doc.createElement("icons");
 NamedIcon* icon = p->getIcon(tr("Held"));
 if (icon!=NULL) {
     elem.appendChild(storeIcon("held", icon));
 }
 icon = p->getIcon(tr("Dark"));
 if (icon!=NULL) {
     elem.appendChild(storeIcon("dark", icon));
 }
 icon = p->getIcon(tr("Red"));
 if (icon!=NULL) {
     elem.appendChild(storeIcon("red", icon));
 }
 icon = p->getIcon(tr("Yellow"));
 if (icon!=NULL) {
     elem.appendChild(storeIcon("yellow", icon));
 }
 icon = p->getIcon(tr("Green"));
 if (icon!=NULL) {
     elem.appendChild(storeIcon("green", icon));
 }
 icon = p->getIcon(tr("Lunar"));
 if (icon!=NULL) {
     elem.appendChild(storeIcon("lunar", icon));
 }
 icon = p->getIcon(tr("Flashing Red"));
 if (icon!=NULL) {
     elem.appendChild(storeIcon("flashred", icon));
 }
 icon = p->getIcon(tr("Flashing Yellow"));
 if (icon!=NULL) {
     elem.appendChild(storeIcon("flashyellow", icon));
 }
 icon = p->getIcon(tr("Flashing Green"));
 if (icon!=NULL) {
     elem.appendChild(storeIcon("flashgreen", icon));
 }
 icon = p->getIcon(tr("Flashing Lunar"));
 if (icon!=NULL) {
     elem.appendChild(storeIcon("flashlunar", icon));
 }
 element.appendChild(elem);
 elem = doc.createElement("iconmaps");
 QString family = p->getFamily();
 if (family!=NULL) {
     elem.setAttribute("family", family);
 }
 element.appendChild(elem);

 element.setAttribute("class", "jmri.jmrit.display.configurexml.SignalHeadIconXml");
 return element;
}

/*public*/ bool SignalHeadIconXml::load(QDomElement /*element*/) throw (Exception)
{
 log->error("Invalid method called");
 return false;
}

/**
 * Create a PositionableLabel, then add to a target JLayeredPane
 * @param element Top level QDomElement to unpack.
 * @param o  an Editor as an Object
 */
/*public*/ void SignalHeadIconXml::load(QDomElement element, QObject* o) throw (Exception)
{
 // create the objects
 Editor* ed = (Editor*)o;
 l = new SignalHeadIcon(ed);
 QString name;

 QString attr = element.attribute("signalhead");
 if (attr == NULL) {
     log->error("incorrect information for signal head; must use signalhead name");
     ed->loadFailed();
     return;
 } else {
     name = attr;
 }

 SignalHead* sh = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(name);
 if (sh != NULL)
 {
  l->setSignalHead(new NamedBeanHandle<SignalHead*>(name, (SignalHead*)sh));
 }
 else
 {
  log->error("SignalHead named '"+attr+"' not found.");
 //    ed.loadFailed();
  return;
 }
 int rotation = 0;
 try
 {
  attr = element.attribute("rotate");
  rotation = attr.toInt();
 }
 catch (DataConversionException* e)
 {
 }
 catch ( NullPointerException e)
 {  // considered normal if the attributes are not present
 }

 //@SuppressWarnings("unchecked")
 QDomNodeList aspects = element.childNodes();
 if (aspects.size()>0)
 {
  QDomElement icons = element.firstChildElement("icons");
  QDomElement elem = element;
  if (!icons.isNull())
  {
   // @SuppressWarnings("unchecked")
   QDomNodeList c = icons.childNodes();
   aspects = c;
   elem = icons;
  }
  for (int i=0; i<aspects.size(); i++)
  {
   QString aspect = aspects.at(i).toElement().tagName();
   NamedIcon* icon = loadIcon(l, aspect, elem, "SignalHead \""+name+"\": icon \""+aspect+"\" ", ed);
   if (icon!=NULL)
   {
    l->setIcon(_nameMap.value(aspect), icon);
   }
   else
   {
    log->info("SignalHead \""+name+"\": icon \""+aspect+"\" removed");
   }
  }
  log->debug(QString::number(aspects.size())+" icons loaded for "+l->getNameString());
 }
 else
 {
  // old style as attributes - somewhere around pre 2.5.4
  NamedIcon* icon = loadSignalIcon("red", rotation, l, element, name, ed);
  if (icon!=NULL)
  {
   l->setIcon(tr("Red"), icon);
  }
  icon = loadSignalIcon("yellow", rotation, l, element, name, ed);
  if (icon!=NULL)
  {
   l->setIcon(tr("Yellow"), icon);
  }
  icon = loadSignalIcon("green", rotation, l, element, name, ed);
  if (icon!=NULL)
  {
   l->setIcon(tr("Green"), icon);
  }
  icon = loadSignalIcon("lunar", rotation, l, element, name, ed);
  if (icon!=NULL)
  {
   l->setIcon(tr("Lunar"), icon);
  }
  icon = loadSignalIcon("held", rotation, l, element, name, ed);
  if (icon!=NULL)
  {
   l->setIcon(tr("Red"), icon);
  }
  icon = loadSignalIcon("dark", rotation, l, element, name, ed);
  if (icon!=NULL)
  {
   l->setIcon(tr("Dark"), icon);
  }
  icon = loadSignalIcon("flashred", rotation, l, element, name, ed);
  if (icon!=NULL)
  {
   l->setIcon(tr("Flashing Red"), icon);
  }
  icon = loadSignalIcon("flashyellow", rotation, l, element, name, ed);
  if (icon!=NULL)
  {
   l->setIcon(tr("Flashing Yellow"), icon);
  }
  icon = loadSignalIcon("flashgreen", rotation, l, element, name, ed);
  if (icon!=NULL)
  {
   l->setIcon(tr("Flashing Green"), icon);
  }
  icon = loadSignalIcon("flashlunar", rotation, l, element, name, ed);
  if (icon!=NULL)
  {
   l->setIcon(tr("Flashing Lunar"), icon);
  }
 }
 QDomElement elem = element.firstChildElement("iconmaps");
 if (!elem.isNull())
 {
  attr = elem.attribute("family");
  if (attr!=NULL)
  {
   l->setFamily(attr);
  }
 }
// try
// {
 bool bok;
  attr = element.attribute("clickmode");
  if (attr!="") {
      l->setClickMode(attr.toInt(&bok));
  }
// }
 if(!bok)
 {
  log->error("Failed on clickmode attribute: "/*+e->getMessage()*/);
 }

 try
 {
  attr = element.attribute("litmode");
  if (attr!=NULL)
  {
   l->setLitMode(attr=="yes"?true:false);
  }
 }
 catch (DataConversionException* e)
 {
  log->error("Failed on litmode attribute: "+e->getMessage());
 }
 // load individual item's option settings after editor has set its global settings
 loadCommonAttributes((Positionable*)l, Editor::SIGNALS, element);

 l->setDisplayLevel(Editor::SIGNALS);
 ed->putItem((Positionable*)l);
}

/*private*/ NamedIcon* SignalHeadIconXml::loadSignalIcon(QString aspect, int rotation, SignalHeadIcon* l, QDomElement element, QString name, Editor* ed) {
 QString msg = "SignalHead \""+name+"\": icon \""+aspect+"\" ";
 NamedIcon* icon = loadIcon(l, aspect, element, msg, ed);
 if (icon==NULL)
 {
  if (element.attribute(aspect) != NULL)
  {
   QString iconName = element.attribute(aspect);
   icon = NamedIcon::getIconByName(iconName);
   if (icon==NULL)
   {
    icon = ed->loadFailed(msg, iconName);
    if (icon==NULL)
    {
     log->info(msg+" removed for url= "+iconName);
    }
   }
   if (icon!=NULL)
   {
    icon->setRotation(rotation, (QObject*)l);
   }
  }
  else log->info("did not load file aspect "+aspect+" for SignalHead "+name);
 }
 if (icon==NULL)
 {
  log->info("SignalHead Icon \""+name+"\": icon \""+aspect+"\" removed");
 }
 return icon;
}

SignalHeadIcon* SignalHeadIconXml::getIcon() { return l;}
