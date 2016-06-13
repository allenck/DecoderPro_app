#include "memoryinputiconxml.h"
#include "editor.h"
#include "memoryinputicon.h"
#include "instancemanager.h"
#include "abstractmemorymanager.h"

MemoryInputIconXml::MemoryInputIconXml(QObject *parent) :
    PositionableLabelXml(parent)
{
    log = new Logger("MemoryInputIconXml");
}
/**
 * Handle configuration for display.MemorySpinnerIcon objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2009
 * @version $Revision: 21255 $
 */
///*public*/ class MemoryInputIconXml extends PositionableLabelXml {

//    /*public*/ MemoryInputIconXml() {
//    }

/**
 * Default implementation for storing the contents of a
 * MemorySpinnerIcon
 * @param o Object to store, of type MemorySpinnerIcon
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement MemoryInputIconXml::store(QObject* o) {

    MemoryInputIcon* p = (MemoryInputIcon*)o;

    QDomElement element = doc.createElement("memoryInputIcon");

    // include attributes
    element.setAttribute("colWidth", p->getNumColumns());
    element.setAttribute("memory", p->getNamedMemory()->getName());
    storeCommonAttributes((Positionable*)p, element);
    storeTextInfo((Positionable*)p, element);

    element.setAttribute("class", "jmri.jmrit.display.configurexml.MemoryInputIconXml");
    return element;
}


/*public*/ bool MemoryInputIconXml::load(QDomElement /*element*/) throw (Exception){
    log->error("Invalid method called");
    return false;
}

/**
 * Load, starting with the memoryInputIcon element, then
 * all the value-icon pairs
 * @param element Top level QDomElement to unpack.
 * @param o  an Editor as an Object
 */
/*public*/ void MemoryInputIconXml::load(QDomElement element, QObject* o)throw (Exception)
{
 // create the objects
 Editor* p = (Editor*)o;

 int nCol = 2;
 try {
     nCol = element.attribute("colWidth").toInt();
 } catch ( DataConversionException e) {
     log->error("failed to convert colWidth attribute");
 }

 l = new MemoryInputIcon(nCol, p);

 loadTextInfo((Positionable*)l, element);
 QString name;
 QString attr = element.attribute("memory");
 if (attr == NULL) {
     log->error("incorrect information for a memory location; must use memory name");
     p->loadFailed();
     return;
 } else {
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

 // load individual item's option settings after editor has set its global settings
 loadCommonAttributes((Positionable*)l, Editor::MEMORIES, element);
 p->putItem((Positionable*)l);
}

MemoryInputIcon* MemoryInputIconXml::getIcon() { return l;}
