#include "positionableroundrectxml.h"
#include "editor.h"
#include "positionableroundrect.h"

PositionableRoundRectXml::PositionableRoundRectXml(QObject *parent) :
    PositionableShapeXml(parent)
{
    log = new Logger("PositionableRoundRectXml");
}
/**
 * Handle configuration for display.PositionableShape objects
 *
 * @author Pete Cressman Copyright: Copyright (c) 2012
 * @version $Revision: 1 $
 */
///*public*/ class PositionableRoundRectXml extends PositionableShapeXml {

//    /*public*/ PositionableRoundRectXml() {
//    }

/**
 * Default implementation for storing the contents of a
 * PositionableShape
 * @param o Object to store, of type PositionableShape
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement PositionableRoundRectXml::store(QObject* o) {
    PositionableRoundRect* p = (PositionableRoundRect*)o;

    if (!p->isActive()) return QDomElement();  // if flagged as inactive, don't store

    QDomElement element = doc.createElement("positionableRoundRect");
    element.setAttribute("width", p->getWidth());
    element.setAttribute("height", p->getHeight());
    element.setAttribute("cornerRadius", p->getCornerRadius());
    storeCommonAttributes(p, element);

    QDomElement elem = doc.createElement("size");
    elem.setAttribute("width", p->getWidth());
    elem.setAttribute("height", p->getHeight());
    elem.setAttribute("cornerRadius", p->getCornerRadius());
    element.appendChild(elem);

    element.setAttribute("class", "jmri.jmrit.display.controlPanelEditor.shape.configurexml.PositionableRoundRectXml");
    return element;
}

/*public*/ bool PositionableRoundRectXml::load(QDomElement /*element*/) throw (Exception){
    log->error("Invalid method called");
    return false;
}

/**
 * Create a PositionableShape, then add to a target JLayeredPane
 * @param element Top level QDomElement to unpack.
 * @param o  Editor as an Object
 */
//@SuppressWarnings("unchecked")
/*public*/ void PositionableRoundRectXml::load(QDomElement element, QObject* o) throw (Exception){
    // create the objects
    Editor* ed = (Editor*)o;
    PositionableRoundRect* ps = new PositionableRoundRect(ed);

    QDomElement elem = element.firstChildElement("size");
    ps->setWidth(getInt(elem, "width"));
    ps->setHeight(getInt(elem, "height"));
    ps->setCornerRadius(getInt(elem, "cornerRadius"));

    // get object class and determine editor being used
    Editor* editor = (Editor*)o;
    //editor->putItem(ps);
    // load individual item's option settings after editor has set its global settings
    loadCommonAttributes(ps, Editor::MARKERS, element);
    ps->_itemGroup = NULL;
    editor->putItem(ps);
}
