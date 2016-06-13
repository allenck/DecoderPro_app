#include "positionablecirclexml.h"
#include "editor.h"
#include "positionablecircle.h"

PositionableCircleXml::PositionableCircleXml(QObject *parent) :
    PositionableShapeXml(parent)
{
    log = new Logger("PositionableCircleXml");
}
/**
 * Handle configuration for display.PositionableShape objects
 *
 * @author Pete Cressman Copyright: Copyright (c) 2012
 * @version $Revision: 1 $
 */
///*public*/ class PositionableCircleXml extends PositionableShapeXml {

//    /*public*/ PositionableCircleXml() {
//    }

/**
 * Default implementation for storing the contents of a
 * PositionableShape
 * @param o Object to store, of type PositionableShape
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement PositionableCircleXml::store(QObject* o) {
    PositionableCircle* p = (PositionableCircle*)o;

    if (!p->isActive()) return QDomElement();  // if flagged as inactive, don't store

    QDomElement element = doc.createElement("positionableCircle");
    storeCommonAttributes(p, element);

    QDomElement elem = doc.createElement("size");
    elem.setAttribute("radius", p->getRadius());
    element.appendChild(elem);

    element.setAttribute("class", "jmri.jmrit.display.controlPanelEditor.shape.configurexml.PositionableCircleXml");
    return element;
}

/*public*/ bool PositionableCircleXml::load(QDomElement /*element*/) throw (Exception){
    log->error("Invalid method called");
    return false;
}

/**
 * Create a PositionableShape, then add to a target JLayeredPane
 * @param element Top level QDomElement to unpack.
 * @param o  Editor as an Object
 */
//@SuppressWarnings("unchecked")
/*public*/ void PositionableCircleXml::load(QDomElement element, QObject* o) throw (Exception) {
    // create the objects
    Editor* ed = (Editor*)o;
    PositionableCircle* ps = new PositionableCircle(ed);

    QDomElement elem = element.firstChildElement("size");
    ps->setRadius(getInt(elem, "radius"));

    // get object class and determine editor being used
    Editor* editor = (Editor*)o;
    //editor->putItem(ps);
    // load individual item's option settings after editor has set its global settings
    loadCommonAttributes(ps, Editor::MARKERS, element);
 ps->_itemGroup = NULL;
 editor->putItem(ps);
}
