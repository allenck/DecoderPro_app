#include "positionableshapexml.h"
#include "positionableshape.h"
#include "editor.h"

PositionableShapeXml::PositionableShapeXml(QObject *parent) :
    AbstractXmlAdapter(parent)
{
    log = new Logger("PositionableShapeXml");
}
/**
 * Handle configuration for display.PositionableShape objects
 *
 * @author Pete Cressman Copyright: Copyright (c) 2012
 * @version $Revision: 1 $
 */
///*public*/ class PositionableShapeXml extends AbstractXmlAdapter {

//    /*public*/ PositionableShapeXml() {
//    }

/**
 * Default implementation for storing the contents of a
 * PositionableShape
 * @param o Object to store, of type PositionableShape
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement PositionableShapeXml::store(QObject* o) {
    PositionableShape* p = (PositionableShape*)o;

    if (!p->isActive()) return QDomElement();  // if flagged as inactive, don't store

    QDomElement element = doc.createElement("PositionableShape");
    storeCommonAttributes(p, element);

    element.setAttribute("class", "jmri.jmrit.display.controlPanelEditor.shape.configurexml.PositionableShapeXml");
    return element;
}

/**
 * Default implementation for storing the common contents
 * @param element QDomElement in which contents are stored
 */
/*public*/ void PositionableShapeXml::storeCommonAttributes(PositionableShape* p, QDomElement element) {
    element.setAttribute("x", p->getX());
    element.setAttribute("y", p->getY());
    element.setAttribute("level", p->getDisplayLevel());
    element.setAttribute("forcecontroloff", !p->isControlling()?"true":"false");
    element.setAttribute("hidden", p->isHidden()?"yes":"no");
    element.setAttribute("positionable", p->isPositionable()?"true":"false");
    element.setAttribute("showtooltip", p->showTooltip()?"true":"false");
    element.setAttribute("editable", p->isEditable()?"true":"false");
    QString tip = p->getTooltip();
    QString txt = tip;
    if (txt!="") {
        QDomElement elem = doc.createElement("toolTip");
        elem.appendChild(doc.createTextNode(txt));
        element.appendChild(elem);
    }
    if (p->getDegrees()!=0) {
        element.setAttribute("degrees", p->getDegrees());
    }

    QDomElement elem = storeColor("lineColor", p->getLineColor());
    if (!elem.isNull()) {
        element.appendChild(elem);
    }
    elem = storeColor("fillColor", p->getFillColor());
    if (!elem.isNull()) {
        element.appendChild(elem);
    }
    element.setAttribute("lineWidth", p->getLineWidth());
    element.setAttribute("alpha", p->getAlpha());
}

/*public*/ QDomElement PositionableShapeXml::storeColor(QString name, QColor c) {
    if (!c.isValid()) {
        return QDomElement();
    }
    QDomElement elem = doc.createElement(name);
    elem.setAttribute("red", c.red());
    elem.setAttribute("green", c.green());
    elem.setAttribute("blue", c.blue());
    return elem;
}

/*public*/ bool PositionableShapeXml::load(QDomElement /*element*/) throw (Exception) {
    log->error("Invalid method called");
    return false;
}

/**
 * Create a PositionableShape, then add to a target JLayeredPane
 * @param element Top level QDomElement to unpack.
 * @param o  Editor as an Object
 */
//@SuppressWarnings("unchecked")
/*public*/ void PositionableShapeXml::load(QDomElement element, QObject* o) throw (Exception){
    // create the objects
    Editor* ed = (Editor*)o;
    PositionableShape* ps = new PositionableShape(ed);

    // get object class and determine editor being used
    Editor* editor = (Editor*)o;
    editor->putItem(ps);
    // load individual item's option settings after editor has set its global settings
    loadCommonAttributes(ps, Editor::MARKERS, element);
}

/*public*/ void PositionableShapeXml::loadCommonAttributes(PositionableShape* ps, int /*defaultLevel*/, QDomElement element) {
    // find coordinates
    int x = getInt(element, "x");
    int y = getInt(element, "y");
    ps->setLocation(x,y);

    // find display psevel
    ps->setLevel(getInt(element, "level"));

    QString a = element.attribute("hidden");
    if ( (a!="") && a==("yes")){
        ps->setHidden(true);
        ps->setVisible(false);
    }
    a = element.attribute("positionable");
    if ( (a!="") && a==("true"))
        ps->setPositionable(true);
    else
        ps->setPositionable(false);

    a = element.attribute("showtooltip");
    if ( (a!="") && a==("true"))
        ps->setShowTooltip(true);
    else
        ps->setShowTooltip(false);

    a = element.attribute("editable");
    if ( (a!="") && a==("true"))
        ps->setEditable(true);
    else
        ps->setEditable(false);

    QDomElement elem = element.firstChildElement("toolTip");
    if (!elem.isNull()) {
        QString tip = ps->getTooltip();
        if (tip!="") {
            tip=(elem.text());
        }
    }
    ps->setLineWidth(getInt(element, "lineWidth"));
    ps->setAlpha(getInt(element, "alpha"));
    ps->setLineColor(getColor(element, "lineColor"));
    ps->setFillColor(getColor(element, "fillColor"));

    ps->setLocation(x,y);
    ps->makeShape();
    ps->_itemGroup->setPos(x,y);
    ps->updateSize();
}

/*public*/ QColor PositionableShapeXml::getColor(QDomElement element, QString name) {
    QDomElement elem = element.firstChildElement(name);
    try {
        int red = elem.attribute("red").toInt();
        int blue = elem.attribute("blue").toInt();
        int green = elem.attribute("green").toInt();
        return  QColor(red, green, blue);
    } catch (Exception e) {
        log->warn("failed to convert color attribute for "+name+" - "+e.getMessage());
    }
    return QColor();
}

/*public*/ int PositionableShapeXml::getInt(QDomElement element, QString name) {
    try {
        int num  = element.attribute(name).toInt();
        return num;

    } catch (Exception e) {
        log->error("failed to convert integer attribute for "+name+" - "+e.getMessage());
    }
    return 0;
}
