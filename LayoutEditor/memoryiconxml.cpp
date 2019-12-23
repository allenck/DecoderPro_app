#include "memoryiconxml.h"
#include "lememoryicon.h"
#include "positionablepopuputil.h"
#include "instancemanager.h"
#include "editor.h"
#include "layouteditor.h"
#include "abstractmemory.h"

MemoryIconXml::MemoryIconXml(QObject *parent) :
    PositionableLabelXml(parent)
{
 log = new Logger("DisplayMemoryIconXml");
}
/**
 * Handle configuration for display.MemoryIcon objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004
 * @version $Revision: 21070 $
 */
//public class MemoryIconXml extends PositionableLabelXml {

//    public MemoryIconXml() {
//    }

/**
 * Default implementation for storing the contents of a
 * MemoryIcon
 * @param o Object to store, of type MemoryIcon
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement MemoryIconXml::store(QObject* o)
{

 MemoryIcon* p = (MemoryIcon*)o;

 QDomElement element = doc.createElement("memoryicon");

 // include attributes
 element.setAttribute("memory", p->getNamedMemory()->getName());
 storeCommonAttributes((Positionable*)p, element);
 storeTextInfo(p, element);

 //If the fixed width option is not set and the justification is not left
 //Then we need to replace the x, y values with the original ones.
 if (p->getPopupUtility()->getFixedWidth()==0 && p->getPopupUtility()->getJustification()!=0)
 {
  element.setAttribute("x", p->getOriginalX());
  element.setAttribute("y", p->getOriginalY());
 }
 element.setAttribute("selectable", (p->isSelectable()?"yes":"no"));
 if(p->updateBlockValueOnChange())
 {
  element.setAttribute("updateBlockValue", (p->updateBlockValueOnChange()?"yes":"no"));
 }

 element.setAttribute("class", "jmri.jmrit.display.configurexml.MemoryIconXml");
 if (p->getDefaultIcon()!=NULL)
  element.setAttribute("defaulticon", p->getDefaultIcon()->getURL());

 // include contents
 QMap<QString, NamedIcon*>* map = p->getMap();
 if (map!=NULL)
 {

  //java.util.Iterator<java.util.Map.Entry<String, NamedIcon>> iterator = map.entrySet().iterator();
  QMapIterator<QString, NamedIcon*> iterator(*map);

  while (iterator.hasNext())
  {
   //QMap<QString, NamedIcon*> mi = iterator.next();
   iterator.next();
   QString key = iterator.key();
   QString value = iterator.value()->getName();

   QDomElement e2 = doc.createElement("memorystate");
   e2.setAttribute("value", key);
   e2.setAttribute("icon", value);
   element.appendChild(e2);
  }
 }
 return element;
}


/*public*/ bool MemoryIconXml::load(QDomElement /*element*/) throw (Exception)
{
    log->error("Invalid method called");
    return false;
}

/**
 * Load, starting with the memoryicon element, then
 * all the value-icon pairs
 * @param element Top level QDomElement to unpack.
 * @param o an Editor as an Object
 */
//@SuppressWarnings("unchecked")
/*public*/ void MemoryIconXml::load(QDomElement element, QObject* o) throw (Exception)
{

 Editor* ed = NULL;
 //MemoryIcon* l;
 //if (o instanceof LayoutEditor)
 if(qobject_cast<LayoutEditor*>(o)!= NULL)
 {
  ed = (LayoutEditor*) o;
  l = new LEMemoryIcon(QString("   "), (LayoutEditor*)ed);
 }
 else
 //if (o instanceof jmri.jmrit.display.Editor)
 if(qobject_cast<Editor*>(o)!=NULL)
 {
  ed = (Editor*) o;
  l = new MemoryIcon("", ed);
 }
 else
 {
  log->error(tr("Unrecognizable class - ")+o->metaObject()->className());
  return;
 }

 QString name;
 QString attr = element.attribute("memory");
 if (attr == "")
 {
  log->error("incorrect information for a memory location; must use memory name");
  ed->loadFailed();
  return;
 }
 else
 {
  name = attr;
 }

 loadTextInfo((Positionable*)l, element);

 Memory* m = ((AbstractMemoryManager*)InstanceManager::memoryManagerInstance())->getMemory(name);
 if (m!=NULL)
 {
  l->setMemory(name);
 }
 else
 {
  log->error("Memory named '"+attr+"' not found.");
  ed->loadFailed();
 }

 QString a = element.attribute("selectable");
 if (a!="" && a==("yes")) l->setSelectable(true);
 else l->setSelectable(false);

 a = element.attribute("updateBlockValue");
 if(a!="" && a==("yes")) l->updateBlockValueOnChange(true);

 // get the icon pairs
 QDomNodeList items = element.elementsByTagName("memorystate");
 for (int i = 0; i<items.size(); i++)
 {
  // get the class, hence the adapter object to do loading
  QDomElement item = items.at(i).toElement();
  QString iconName = item.attribute("icon");
  NamedIcon* icon = NamedIcon::getIconByName(iconName);
  if (icon==NULL)
  {
   icon = ed->loadFailed("Memory "+name, iconName);
   if (icon==NULL)
   {
    log->info("Memory \""+name+"\" icon removed for url= "+iconName);
   }
  }
  if (icon!=NULL)
  {
   QString keyValue = item.attribute("value");
   l->addKeyAndIcon(icon, keyValue);
  }
 }
 //ed->putItem((Positionable*)l);
 // load individual item's option settings after editor has set its global settings
 loadCommonAttributes((Positionable*)l, Editor::MEMORIES, element);
 //ed->putItem((Positionable*)l);

 int x = 0;
 int y = 0;
// try
// {
 bool bOk = true;
 bool bOk1;
 x = element.attribute("x").toInt(&bOk1);
 if(!bOk1) bOk = false;
 y = element.attribute("y").toInt(&bOk1);
 if(!bOk1) bOk = false;
// }
// catch ( org.jdom.DataConversionException e) {
 if(!bOk)
 {
  log->error("failed to convert positional attribute");
 }
 l->setLocation(x,y);
 l->setOriginalLocation(x,y);
 ed->putItem((Positionable*)l);

 l->displayState();
 l->updateScene();
}
MemoryIcon* MemoryIconXml::getIcon() { return l;}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(MemoryIconXml.class.getName());
//}
