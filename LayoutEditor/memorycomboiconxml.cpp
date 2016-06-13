#include "memorycomboiconxml.h"
#include "memorycomboicon.h"
#include "abstractmemorymanager.h"
#include "instancemanager.h"
#include "editor.h"

MemoryComboIconXml::MemoryComboIconXml(QObject *parent) :
    PositionableLabelXml(parent)
{
 log = new Logger("MemoryComboIconXml");
}
/**
 * Handle configuration for display.MemorySpinnerIcon objects.
 *
 * @author Pete Cressman  Copyright (c) 2012
 * @version $Revision: 1 $
 */
///*public*/ class MemoryComboIconXml extends PositionableLabelXml {

//    /*public*/ MemoryComboIconXml() {
//    }

/**
 * Default implementation for storing the contents of a
 * MemorySpinnerIcon
 * @param o Object to store, of type MemorySpinnerIcon
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement MemoryComboIconXml::store(QObject* o)
{
 MemoryComboIcon* p = (MemoryComboIcon*)o;

 QDomElement element = doc.createElement("memoryComboIcon");

 QDomElement elem = doc.createElement("itemList");

 //DefaultComboBoxModel model = p->getComboModel();
 QStringList model = p->getComboModel();
 for(int i=0; i<model.size(); i++) {
     QDomElement e = doc.createElement("item");
     e.setAttribute("index", i);
     e.appendChild(doc.createTextNode(model.at(i)));
     elem.appendChild(e);
 }
 element.appendChild(elem);

 // include attributes
 element.setAttribute("memory", p->getNamedMemory()->getName());
 storeCommonAttributes((Positionable*)p, element);
 storeTextInfo((Positionable*)p, element);

 element.setAttribute("class", "jmri.jmrit.display.configurexml.MemoryComboIconXml");
 return element;
}


/*public*/ bool MemoryComboIconXml::load(QDomElement /*element*/) throw (Exception){
    log->error("Invalid method called");
    return false;
}

/**
 * Load, starting with the memoryComboIcon element, then
 * all the value-icon pairs
 * @param element Top level QDomElement to unpack.
 * @param o  an Editor as an Object
 */
/*public*/ void MemoryComboIconXml::load(QDomElement element, QObject* o) throw (Exception)
{
 // create the objects
 Editor* p = (Editor*)o;

 QDomElement elem = element.firstChildElement("itemList");
 //@SuppressWarnings("unchecked")
 QDomNodeList list = elem.elementsByTagName("item");
 QStringList items =  QStringList(); //[list.size()];
 for (int i=0; i<list.size(); i++) {
     QDomElement e = list.at(i).toElement();
     QString item = e.text();
//            int idx = 0;
//            try {
//                idx = e.getAttribute("index").getIntValue();
//            } catch ( org.jdom.DataConversionException ex) {
//                log.error("failed to convert ComboBoxIcon index attribute");
//                idx = i;
//            }
     //items[i] = item;
     items.append(item);
 }

 l = new MemoryComboIcon(p, items);

 loadTextInfo((Positionable*)l, element);
 QString name;
 QString attr = element.attribute("memory");
 if (attr == "")
 {
  log->error("incorrect information for a memory location; must use memory name");
  p->loadFailed();
  return;
 }
 else
 {
  name = attr;
 }

 Memory* m = ((AbstractMemoryManager*)InstanceManager::memoryManagerInstance())->getMemory(name);

 if (m!=NULL) {
     l->setMemory(name);
 } else {
     log->error("Memory named '"+attr+"' not found.");
     p->loadFailed();
     return;
 }

 //p->putItem((Positionable*)l);
 // load individual item's option settings after editor has set its global settings
 loadCommonAttributes((Positionable*)l, Editor::MEMORIES, element);
 p->putItem((Positionable*)l);

}

MemoryComboIcon* MemoryComboIconXml::getIcon() {return l;}
