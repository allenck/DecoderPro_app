#include "positionableellipsexml.h"
#include "positionableellipse.h"
#include "editor.h"

PositionableEllipseXml::PositionableEllipseXml(QObject *parent) :
    PositionableShapeXml(parent)
{
    log = new Logger("PositionableEllipseXml");
}

/**
 * Handle configuration for display.PositionableShape objects
 *
 * @author Pete Cressman Copyright: Copyright (c) 2012
 * @version $Revision: 1 $
 */
///*public*/ class PositionableEllipseXml extends PositionableShapeXml {

//    /*public*/ PositionableEllipseXml() {
//    }

/**
 * Default implementation for storing the contents of a
 * PositionableShape
 * @param o Object to store, of type PositionableShape
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement PositionableEllipseXml::store(QObject* o) {
    PositionableEllipse* p = (PositionableEllipse*)o;

    if (!p->isActive()) return QDomElement();  // if flagged as inactive, don't store

    QDomElement element = doc.createElement("positionableEllipse");
    storeCommonAttributes(p, element);

    QDomElement elem = doc.createElement("size");
    elem.setAttribute("width", p->getWidth());
    elem.setAttribute("height", p->getHeight());
    element.appendChild(elem);

    element.setAttribute("class", "jmri.jmrit.display.controlPanelEditor.shape.configurexml.PositionableEllipseXml");
    return element;
}

/*public*/ bool PositionableEllipseXml::load(QDomElement /*element*/)throw (Exception) {
    log->error("Invalid method called");
    return false;
}

/**
 * Create a PositionableShape, then add to a target JLayeredPane
 * @param element Top level QDomElement to unpack.
 * @param o  Editor as an Object
 */
//@SuppressWarnings("unchecked")
/*public*/ void PositionableEllipseXml::load(QDomElement element, QObject* o) throw (Exception){
    // create the objects
    Editor* ed = (Editor*)o;
    PositionableEllipse* ps = new PositionableEllipse(ed);

    QDomElement elem = element.firstChildElement("size");
    ps->setWidth(getInt(elem, "width"));
    ps->setHeight(getInt(elem, "height"));

    // get object class and determine editor being used
    Editor* editor = (Editor*)o;
    //editor->putItem(ps);
    // load individual item's option settings after editor has set its global settings
    loadCommonAttributes(ps, Editor::MARKERS, element);
    ps->_itemGroup = NULL;
    editor->putItem(ps);
}
