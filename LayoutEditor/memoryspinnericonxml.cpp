#include "memoryspinnericonxml.h"
#include "memoryspinnericon.h"
#include "editor.h"

MemorySpinnerIconXml::MemorySpinnerIconXml(QObject *parent) :
    PositionableLabelXml(parent)
{
    log = new Logger("MemorySpinnerIconXml");
}
/**
 * Handle configuration for display.MemorySpinnerIcon objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2009
 * @version $Revision: 18226 $
 */
///*public*/ class MemorySpinnerIconXml extends PositionableLabelXml {

//    /*public*/ MemorySpinnerIconXml() {
//    }

/**
 * Default implementation for storing the contents of a
 * MemorySpinnerIcon
 * @param o Object to store, of type MemorySpinnerIcon
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement MemorySpinnerIconXml::store(QObject* o) {

    MemorySpinnerIcon* p = (MemorySpinnerIcon*)o;

    QDomElement element = doc.createElement("memoryicon");

    // include attributes
    element.setAttribute("memory", p->getNamedMemory()->getName());
    storeCommonAttributes((Positionable*)p, element);
    storeTextInfo((Positionable*)p, element);

    element.setAttribute("class", "jmri.jmrit.display.configurexml.MemorySpinnerIconXml");
    return element;
}


/*public*/ bool MemorySpinnerIconXml::load(QDomElement /*element*/) throw (Exception){
    log->error("Invalid method called");
    return false;
}

/**
 * Load, starting with the memoryicon element, then
 * all the value-icon pairs
 * @param element Top level QDomElement to unpack.
 * @param o  Editor as an Object
 */
/*public*/ void MemorySpinnerIconXml::load(QDomElement element, QObject* o) throw (Exception)
{
 // create the objects
 Editor* p = (Editor*)o;
 l = new MemorySpinnerIcon(p);

 l->setMemory(element.attribute("memory"));

//    loadTextInfo((Positionable*)l, element);
 //p->putItem((Positionable*)l);
 // load individual item's option settings after editor has set its global settings
 loadCommonAttributes((Positionable*)l, Editor::MEMORIES, element);
 p->putItem((Positionable*)l);
}
MemorySpinnerIcon* MemorySpinnerIconXml::getIcon() { return l;}
