#include "layoutshapexml.h"
#include "loggerfactory.h"
#include "layoutshape.h"
#include "colorutil.h"
#include <QtXml>
#include "layouteditor.h"

LayoutShapeXml::LayoutShapeXml(QObject* parent)
{

}
/**
 * This module handles configuration for LayoutShape objects for a LayoutEditor.
 /**
 **
 * @author George Warner Copyright (c) 2017-2018
 */
// /*public*/ class LayoutShapeXml extends AbstractXmlAdapter {

//    /*public*/ LayoutShapeXml() {
//    }

    /**
     * Default implementation for storing the contents of a LayoutShape
     *
     * @param o Object to store, of type LayoutShape
     * @return Element containing the complete info
     */
    ////@Override
    /*public*/ QDomElement LayoutShapeXml::store(QObject* o) {
        LayoutShape* s = (LayoutShape*) o;
        QDomElement element = QDomElement();

        if (s->getNumberPoints() > 0) {
            element = doc.createElement("layoutShape");

            // include attributes
            element.setAttribute("ident", s->getName());
            element.setAttribute("type", s->getName());
            element.setAttribute("level", s->getLevel());
            element.setAttribute("linewidth", s->getLineWidth());
            element.setAttribute("lineColor", ColorUtil::colorToHexString(s->getLineColor()));
            element.setAttribute("fillColor", ColorUtil::colorToHexString(s->getFillColor()));

            QDomElement elementPoints = doc.createElement("points");
            QList<LayoutShapePoint*> shapePoints = s->getPoints();
            for (LayoutShapePoint* p : shapePoints) {
                QDomElement elementPoint = doc.createElement("point");

                elementPoint.setAttribute("type", p->getType());

                QPointF pt = p->getPoint();
                elementPoint.setAttribute("x",  pt.x());
                elementPoint.setAttribute("y",  pt.y());

                elementPoints.appendChild(elementPoint);
            }
            element.appendChild(elementPoints);

            element.setAttribute("class", "jmri.jmrit.display.layoutEditor.LayoutShape"); //().getName());
        }
        return element;
    }

    //@Override
    /*public*/ bool LayoutShapeXml::load(QDomElement shared, QDomElement perNode) {
        log->error("Invalid method called");
        return false;
    }

    /**
     * Load, starting with the LayoutShape element, then all the other data
     *
     * @param element Top level Element to unpack.
     * @param o       LayoutEditor as an Object
     */
    //@Override
    /*public*/ void LayoutShapeXml::load(QDomElement element, QObject* o) throw (Exception){
        // create the objects
        LayoutEditor* p = (LayoutEditor*) o;

        QString name = element.attribute("ident");

        LayoutShapeType::TYPES type = LayoutShapeType::eOpen;
        try {
            type = LayoutShapeType::getName(element.attribute("type"));
        } catch (NullPointerException e) {
            log->error("Layout Shape type attribute not found.");
        }

        // create the new LayoutShape
        LayoutShape* s = new LayoutShape(name, type, p);

        QString a = element.attribute("level");
        if (a != "") {
            bool bok;
                s->setLevel(a.toInt(&bok));
            if(!bok) {
                log->error("Layout Shape level attribute Conversion error.");
            }
        } else {
            log->error("Layout Shape level attribute not found.");
        }

        a = element.attribute("linewidth");
        if (a != "") {
            bool bok;
                s->setLineWidth(a.toInt(&bok));
            if(!bok)
            {
                log->error("Layout Shape line width attribute Conversion error.");
            }
        } else {
            log->error("Layout Shape line width attribute not found.");
        }

        a = element.attribute("lineColor");
        if (a != "") {
            try {
                s->setLineColor(ColorUtil::stringToColor(a));
            } catch (IllegalArgumentException e) {
                s->setLineColor(QColor(Qt::black));
                log->error(tr("Invalid lineColor %1; using black").arg(a));
            }
        }

        a = element.attribute("fillColor");
        if (a != "") {
            try {
                s->setFillColor(ColorUtil::stringToColor(a));
            } catch (IllegalArgumentException e) {
                s->setFillColor(QColor(Qt::black));
                log->error(tr("Invalid fillColor %1; using black").arg(a));
            }
        }

        QDomElement pointsElement = element.firstChildElement("points");
        if (!pointsElement.isNull()) {
            QDomNodeList elementList = pointsElement.elementsByTagName("point");
            if (!elementList.isEmpty()) {
                if (elementList.size() > 0) {
                    for (int i = 0; i < elementList.size(); i++) {
                        QDomElement relem = elementList.at(i).toElement();

                        LayoutShapePointType::TYPES pointType = LayoutShapePointType::eStraight;
                        try {
                            pointType = LayoutShapePointType::getName(relem.attribute("type"));
                        } catch (NullPointerException e) {
                            log->error("Layout Shape Point #" + QString::number(i) + "type attribute not found.");
                        }
                        double x = 0.0;
                        double y = 0.0;
                        try {
                         bool bok;
                            x = (relem.attribute("x")).toFloat(&bok);
                            if(!bok) throw DataConversionException();
                            y = (relem.attribute("y")).toFloat(&bok);
                            if(!bok) throw DataConversionException();
                        } catch (DataConversionException e) {
                            log->error("failed to convert Layout Shape point #" + QString::number(i) + "coordinates attributes");
                        }
                        s->addPoint(pointType,  QPointF(x, y));
                    }
                } else {
                    log->error("No Layout Shape point elements");
                }
            } else {
                log->error("Layout Shape point elements not found.");
            }
        } else {
            log->error("Layout Shape points element not found.");
        }
        p->getLayoutShapes()->append(s);
    }

    /*private*/ /*final*/ /*static*/ Logger* LayoutShapeXml::log = LoggerFactory::getLogger("LayoutShapeXml");

