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
    NamedBeanHandle<Sensor*>* handle = p->getControlSensorHandle();
    if (handle != NULL) {
        element.setAttribute("controlSensor", handle->getName());
    }
    element.setAttribute("hideOnSensor", p->isHideOnSensor() ? "true" : "false");
    element.setAttribute("changeLevelOnSensor", (p->getChangeLevel()?"true":"false"));
}

/*public*/ QDomElement PositionableShapeXml::storeColor(QString name, QColor c) {
    if (!c.isValid()) {
        return QDomElement();
    }
    QDomElement elem = doc.createElement(name);
    elem.setAttribute("red", c.red());
    elem.setAttribute("green", c.green());
    elem.setAttribute("blue", c.blue());
    elem.setAttribute("alpha", c.alpha());
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

/*public*/ void PositionableShapeXml::loadCommonAttributes(PositionableShape* ps, int /*defaultLevel*/, QDomElement element)
{
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
 int alpha = -1;
 bool bOk;
 a = element.attribute("alpha");
 if (a != "")
 {
  alpha = a.toInt(&bOk);
 }
 if(!bOk)
 {
  log->warn("invalid 'alpha' value (non integer)");
 }
 ps->setLineColor(getColor(element, "lineColor", alpha));
 ps->setFillColor(getColor(element, "fillColor", alpha));

 ps->makeShape();
 ps->rotate(getInt(element, "degrees"));

 a = element.attribute("hideOnSensor");
 bool hide = false;
 if (a != "") {
     hide = (a == "true");
 }
 int changeLevel = -1;
 //try {
     changeLevel = getInt(element, "changeLevelOnSensor");
// } catch (Exception e) {
//     log.error("failed to get changeLevel attribute ex= " + e);
// }
// try {
     QString attr = element.attribute("controlSensor");
     if (attr != "") {
         ps->setControlSensor(attr, hide, changeLevel);
     }
 if(ps == NULL)
 {
     log->error("incorrect information for controlSensor of PositionableShape");
 }
 ps->updateSize();
}

/*public*/ QColor PositionableShapeXml::getColor(QDomElement element, QString name, int alpha)
{
    QDomElement elem = element.firstChildElement(name);
    bool bOk = true, ok1;
    int red = elem.attribute("red").toInt(&ok1);
    if(!ok1) bOk = false;
    int blue = elem.attribute("blue").toInt(&ok1);
    if(!ok1) bOk = false;
    int green = elem.attribute("green").toInt(&ok1);
    if(!ok1) bOk = false;
    if (alpha == -1)
    {
     alpha = elem.attribute("alpha").toInt(&ok1);
     if(!ok1) bOk = false;
     return QColor(red, green, blue, alpha);
    }
    else if (name == ("lineColor"))
    {
     return QColor(red, green, blue);
    }
    else
    {
     return QColor(red, green, blue, alpha);
    }
    if(!bOk)
    {
     log->warn("failed to convert color attribute for "+name+" - "/*+e.getMessage()*/);
    }
    return QColor();
}

/*public*/ int PositionableShapeXml::getInt(QDomElement element, QString name) {
    bool ok;
        int num  = element.attribute(name).toInt(&ok);
        return num;

    if(!ok) {
        log->error("failed to convert integer attribute for "+name+" - "/*+e.getMessage()*/);
    }
    return 0;
}

/*public*/ float PositionableShapeXml::getFloat(QDomElement element, QString name)
{
    bool bok;
        QString attr = element.attribute(name);
        if (attr != "") {
            float num = attr.toFloat(&bok);
            return num;
        }
    if(!bok) {
        log->error("failed to convert integer attribute for " + name + " - " /*+ e*/);
    }
    return 0;
}
