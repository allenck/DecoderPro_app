#include "positionablepolygonxml.h"
#include "positionablepolygon.h"
#include "pathiterator.h"
#include "editor.h"
#include "generalpath.h"
#include "limits.h"


/**
 * Handle configuration for display.PositionableShape objects
 *
 * @author Pete Cressman Copyright: Copyright (c) 2012
 * @version $Revision: 1 $
 */
///*public*/ class PositionablePolygonXml extends PositionableShapeXml {

/*public*/ PositionablePolygonXml::PositionablePolygonXml() : PositionableShapeXml()
{
}

/**
 * Default implementation for storing the contents of a PositionableShape
 *
 * @param o Object to store, of type PositionableShape
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement PositionablePolygonXml::store(QObject* o) {
    PositionablePolygon* p = (PositionablePolygon*) o;

    if (!p->isActive()) {
        return QDomElement();  // if flagged as inactive, don't store
    }
    QDomElement element = doc.createElement("positionablePolygon");
    storeCommonAttributes(p, element);
    element.appendChild(storePath(p));

    element.setAttribute("class", "jmri.jmrit.display.controlPanelEditor.shape.configurexml.PositionablePolygonXml");
    return element;
}

/*protected*/ QDomElement PositionablePolygonXml::storePath(PositionablePolygon* p) {
    QDomElement elem = doc.createElement("path");
    PathIterator* iter = p->getPathIterator(NULL);
    QVector<float>* coord = new QVector<float>(6);
    while (!iter->isDone()) {
        int type = iter->currentSegment(coord);
        elem.appendChild(storeVertex(type, coord));
        iter->next();
    }
    return elem;
}

/*private*/ QDomElement PositionablePolygonXml::storeVertex(int type, QVector<float>* coord) {
    QDomElement elem = doc.createElement("vertex");
    elem.setAttribute("type", type);
    for (int i = 0; i < coord->length(); i++) {
        elem.setAttribute("idx" + QString::number(i), coord->at(i));
    }
    return elem;
}

/**
 * Create a PositionableShape, then add to a target JLayeredPane
 *
 * @param element Top level QDomElement to unpack.
 * @param o       Editor as an Object
 */
/*public*/ void PositionablePolygonXml::load(QDomElement element, QObject* o)  throw (Exception)
{
    // create the objects
    Editor* ed = (Editor*) o;
    GeneralPath* path = new GeneralPath(Path2D::WIND_EVEN_ODD);
    QDomElement elem = element.firstChildElement("path");

    int top = INT_MAX, bottom =INT_MIN, left= INT_MAX, right =INT_MIN;
    QVector<float>* coord = new QVector<float>(6);
    QDomNodeList list = elem.elementsByTagName("vertex");
    for (int j = 0; j < list.size(); j++)
    {
        QDomElement e = list.at(j).toElement();
        int type = getInt(e, "type");
        for (int i = 0; i < coord->length(); i++) {
            coord->replace(i, getFloat(e, "idx" + QString::number(i)));
        }
        switch (type) {
            case PathIterator::SEG_MOVETO:
                path->moveTo(coord->at(0), coord->at(1));
                break;
            case PathIterator::SEG_LINETO:
                path->lineTo(coord->at(0), coord->at(1));
                break;
            case PathIterator::SEG_QUADTO:
                path->quadTo(coord->at(0), coord->at(1), coord->at(2), coord->at(3));
                break;
            case PathIterator::SEG_CUBICTO:
                path->curveTo(coord->at(0), coord->at(1), coord->at(2), coord->at(3), coord->at(4), coord->at(5));
                break;
            case PathIterator::SEG_CLOSE:
                path->closePath();
                break;
        }
        if(coord->at(0)< left) left = coord->at(0);
        if(coord->at(0)> right) right = coord->at(0);
        if(coord->at(1)< top) top = coord->at(1);
        if(coord->at(1)> bottom) bottom = coord->at(1);
    }


    PositionablePolygon* ps = new PositionablePolygon(ed, (JShape*)path);
    // get object class and determine editor being used
    // load individual item's option settings after editor has set its global settings
    loadCommonAttributes(ps, Editor::MARKERS, element);
    ps->setWidth(right-left);
    ps->setHeight(bottom-top);
    ed->putItem(ps);
}

