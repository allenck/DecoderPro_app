#include "positionablepointviewxml.h"
#include "positionablepointview.h"
#include "positionablepoint.h"
#include "loggerfactory.h"
#include "hitpointtype.h"
#include "editormanager.h"
#include "layouteditor.h"

/**
 * This module handles configuration for display.PositionablePoint objects for a
 * LayoutEditor.
 *
 * @author David Duchamp Copyright (c) 2007
 * @author George Warner Copyright (c) 2017-2018
 */
///*public*/ class PositionablePointViewXml extends AbstractXmlAdapter {

    //static /*final*/ EnumIO<PositionablePoint.PointType> pTypeEnumMap = new EnumIoNamesNumbers<>(PositionablePoint::PointType::class);

    /*public*/ PositionablePointViewXml::PositionablePointViewXml(QObject *parent) {
    }

    /**
     * Default implementation for storing the contents of a PositionablePoint
     *
     * @param o Object to store, of type PositionablePoint
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement PositionablePointViewXml::store(QObject* o) {

        PositionablePointView* pv = (PositionablePointView*) o;
        PositionablePoint* p = pv->getPoint();

        QDomElement element = doc.createElement("positionablepoint");

        // include attributes
        element.setAttribute("ident", p->getId());
        QMetaEnum metaEnum = QMetaEnum::fromType<PositionablePoint::PointType>();
        element.setAttribute("type", /*pTypeEnumMap->outputFromEnum(p->getType()*/metaEnum.valueToKey(p->getType()));
        QPointF coords = pv->getCoordsCenter();
        element.setAttribute("x", coords.x());
        element.setAttribute("y", coords.y());
        if (p->getConnect1() != nullptr) {
            element.setAttribute("connect1name", p->getConnect1()->getId());
        }
        if (p->getConnect2() != nullptr) {
            element.setAttribute("connect2name", p->getConnect2()->getId());
        }
        if (!p->getEastBoundSignal().isEmpty()) {
            element.setAttribute("eastboundsignal", p->getEastBoundSignal());
        }
        if (!p->getWestBoundSignal().isEmpty()) {
            element.setAttribute("westboundsignal", p->getWestBoundSignal());
        }

        if (!p->getEastBoundSignalMastName().isEmpty()) {
            element.setAttribute("eastboundsignalmast", p->getEastBoundSignalMastName());
        }
        if (!p->getWestBoundSignalMastName().isEmpty()) {
            element.setAttribute("westboundsignalmast", p->getWestBoundSignalMastName());
        }

        if (!p->getEastBoundSensorName().isEmpty()) {
            element.setAttribute("eastboundsensor", p->getEastBoundSensorName());
        }
        if (!p->getWestBoundSensorName().isEmpty()) {
            element.setAttribute("westboundsensor", p->getWestBoundSensorName());
        }
        if (p->getType() == PositionablePoint::PointType::EDGE_CONNECTOR) {
            element.setAttribute("linkedpanel", p->getLinkedEditorName());
            element.setAttribute("linkpointid", p->getLinkedPointId());
        }

        element.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml->PositionablePointXml");
        return element;
    }

    //@Override
    /*public*/ bool PositionablePointViewXml::load(/*@Nonnull*/ QDomElement shared, QDomElement perNode) {
        log->error("Invalid method called");
        return false;
    }

    /**
     * Load, starting with the layoutblock element, then all the value-icon
     * pairs
     *
     * @param QDomElement Top level QDomElement to unpack.
     * @param o       LayoutEditor as an Object
     */
    //@Override
    /*public*/ void PositionablePointViewXml::load(QDomElement element, QObject* o) throw (Exception){
        // create the objects
        LayoutEditor* p = (LayoutEditor*) o;

        // get attributes
        QString name = element.attribute("ident");
        PositionablePoint::PointType type = PositionablePoint::PointType::ANCHOR;
        double x = 0.0;
        double y = 0.0;
        bool ok;
        QString ts;
        try {
            x = element.attribute("x").toFloat(&ok); if(!ok) throw DataConversionException();
            y = element.attribute("y").toFloat(&ok); if(!ok) throw DataConversionException();
            //type = pTypeEnumMap->inputFromAttribute(element.attribute("type"));
            QMetaEnum metaEnum = QMetaEnum::fromType<PositionablePoint::PointType>();
            type = (PositionablePoint::PointType)metaEnum.keyToValue((ts =element.attribute("type")).toLocal8Bit(), &ok);
            if(!ok)
            {
             int i = ts.toInt(&ok);
             if(ok)
              type = (PositionablePoint::PointType)i;
             else
              throw DataConversionException("invalid pointValue + ts");
            }
        } catch (DataConversionException e) {
            log->error("failed to convert positionablepoint attribute", e);
        }

        // create the new PositionablePoint
        PositionablePoint* l = new PositionablePoint(name, type, p);
        PositionablePointView* pv = new PositionablePointView(l,  QPointF(x, y), p);
        p->addLayoutTrack(l, pv);

        // get remaining attributes
        QString a = element.attribute("connect1name");
        if (!a.isNull()) {
            l->trackSegment1Name = a;
        }
        a = element.attribute("connect2name");
        if (!a.isNull()) {
            l->trackSegment2Name = a;
        }
        a = element.attribute("eastboundsignal");
        if (!a.isNull()) {
            l->setEastBoundSignal(a);
        }
        a = element.attribute("westboundsignal");
        if (!a.isNull()) {
            l->setWestBoundSignal(a);
        }
        a = element.attribute("eastboundsignalmast");
        if (!a.isNull()) {
            l->setEastBoundSignalMast(a);
        }
        a = element.attribute("westboundsignalmast");
        if (!a.isNull()) {
            l->setWestBoundSignalMast(a);
        }
        a = element.attribute("eastboundsensor");
        if (!a.isNull()) {
            l->setEastBoundSensor(a);
        }
        a = element.attribute("westboundsensor");
        if (!a.isNull()) {
            l->setWestBoundSensor(a);
        }

        if (type == PositionablePoint::PointType::EDGE_CONNECTOR && element.attribute("linkedpanel") != "" && element.attribute("linkpointid") != "") {
            QString linkedEditorName = element.attribute("linkedpanel");
            LayoutEditor* linkedEditor = (LayoutEditor*)((EditorManager*)InstanceManager::getDefault("EditorManager"))->get("LayoutEditor", linkedEditorName);
            if (linkedEditor != nullptr) {
                QString linkedPoint = element.attribute("linkpointid");
                for (PositionablePoint* point : linkedEditor->getPositionablePoints()) {
                    if (point->getType() == PositionablePoint::PointType::EDGE_CONNECTOR && point->getId() == (linkedPoint)) {
                        point->setLinkedPoint(l);
                        l->setLinkedPoint(point);
                        break;
                    }
                }
            }
        }

    }

    /*private*/ /*final*/ /*static*/ Logger* PositionablePointViewXml::log = LoggerFactory::getLogger("PositionablePointViewXml");
