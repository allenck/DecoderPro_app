#include "tracksegmentviewxml.h"
#include "tracksegmentview.h"
#include "loggerfactory.h"
#include "tracksegment.h"
#include "colorutil.h"
#include <QMetaEnum>

/**
 * This module handles configuration for display.TrackSegment objects for a
 * LayoutEditor.
 *
 * @author Bob Jacobsen Copyright (c) 2020
 * @author David Duchamp Copyright (c) 2007
 * @author George Warner Copyright (c) 2017-2019
 */
// /*public*/ class TrackSegmentViewXml extends AbstractXmlAdapter {

/*public*/ TrackSegmentViewXml::TrackSegmentViewXml(QObject *parent) : AbstractXmlAdapter((parent)){
}

/**
 * Default implementation for storing the contents of a TrackSegment
 *
 * @param o Object to store, of type TrackSegment
 * @return QDomElement containing the complete info
 */
//@Override
/*public*/ QDomElement TrackSegmentViewXml::store(QObject* o) {

    TrackSegmentView* view = (TrackSegmentView*) o;
    TrackSegment* trk = view->getTrackSegment();

    QDomElement element = doc.createElement("tracksegment"); // NOI18N

    // include attributes
    element.setAttribute("ident", trk->getId());
    if (!trk->getBlockName().isEmpty()) {
        element.setAttribute("blockname", trk->getBlockName());
    }

    element.setAttribute("connect1name", trk->getConnect1Name());
    //element.setAttribute("type1", "" + htpMap.outputFromEnum(trk->getType1()) );
    QMetaEnum metaEnum = QMetaEnum::fromType<HitPointType::TYPES>();
    element.setAttribute("type1", metaEnum.valueToKey(trk->getType1()));
    element.setAttribute("connect2name", trk->getConnect2Name());
    //element.setAttribute("type2", "" + htpMap.outputFromEnum(trk->getType2()) );
    element.setAttribute("type2", metaEnum.valueToKey(trk->getType2()));

    element.setAttribute("dashed",      (view->isDashed() ? "yes" : "no"));
    element.setAttribute("mainline",    (trk->isMainline() ? "yes" : "no"));
    element.setAttribute("hidden",      (view->isHidden() ? "yes" : "no"));

    if (view->isArc()) {
        element.setAttribute("arc",         "yes");
        element.setAttribute("flip",        (view->isFlip() ? "yes" : "no"));
        element.setAttribute("circle",      (view->isCircle() ? "yes" : "no"));
        if (view->isCircle()) {
            element.setAttribute("angle",   (view->getAngle()));
            element.setAttribute("hideConLines", (view->hideConstructionLines() ? "yes" : "no"));
        }
    }

    if (view->isBezier()) {
        element.setAttribute("bezier", "yes");
        element.setAttribute("hideConLines", (view->hideConstructionLines() ? "yes" : "no"));
        // add control points
        QDomElement elementControlpoints = doc.createElement("controlpoints");
        for (int i = 0; i < view->getNumberOfBezierControlPoints(); i++) {
            QDomElement elementControlpoint = doc.createElement("controlpoint");

            elementControlpoint.setAttribute("index", "" + i);

            QPointF pt = view->getBezierControlPoint(i);
            elementControlpoint.setAttribute("x", QString::asprintf("%.1f", pt.x()));
            elementControlpoint.setAttribute("y", QString::asprintf("%.1f", pt.y()));

            elementControlpoints.appendChild(elementControlpoint);
        }
        element.appendChild(elementControlpoints);
    }

    // store decorations
    QMap<QString, QString>* decorations = view->getDecorations();
    if (decorations->size() > 0) {
        QDomElement decorationsQDomElement = doc.createElement("decorations");
        //for (Map.Entry<String, String> entry : decorations.entrySet())
        QMapIterator<QString, QString> entry(*decorations);
        QDomElement  decorationElement;
        while(entry.hasNext())
        {
         entry.next();
            QString name = entry.key();
            if (name != ("arrow") && name != ("bridge")
                    && name != ("bumper") && name != ("tunnel"))
            {
                 decorationElement = doc.createElement("decoration");
                 decorationElement.setAttribute("name", name);
                QString value = entry.value();
                if (!value.isEmpty()) {
                     decorationElement.setAttribute("value", value);
                }
                 decorationElement.appendChild( decorationElement);
            }
        }
        element.appendChild( decorationElement);

        if (view->getArrowStyle() > 0) {
            QDomElement  decorationElement = doc.createElement("arrow");
             decorationElement.setAttribute("style", QString::number(view->getArrowStyle()));
            if (view->isArrowEndStart() && view->isArrowEndStop()) {
                 decorationElement.setAttribute("end", "both");
            } else if (view->isArrowEndStop()) {
                 decorationElement.setAttribute("end", "stop");
            } else {
                 decorationElement.setAttribute("end", "start");
            }
            if (view->isArrowDirIn() && view->isArrowDirOut()) {
                 decorationElement.setAttribute("direction", "both");
            } else if (view->isArrowDirOut()) {
                 decorationElement.setAttribute("direction", "out");
            } else {
                 decorationElement.setAttribute("direction", "in");
            }
             decorationElement.setAttribute("color", ColorUtil::colorToHexString(view->getArrowColor()));
             decorationElement.setAttribute("linewidth", QString::number(view->getArrowLineWidth()));
             decorationElement.setAttribute("length", QString::number(view->getArrowLength()));
             decorationElement.setAttribute("gap", QString::number(view->getArrowGap()));
             decorationElement.appendChild( decorationElement);
        }
        if (view->isBridgeSideLeft() || view->isBridgeSideRight()) {
            QDomElement  decorationElement = doc.createElement("bridge");
            if (view->isBridgeSideLeft() && view->isBridgeSideRight()) {
                 decorationElement.setAttribute("side", "both");
            } else if (view->isBridgeSideLeft()) {
                 decorationElement.setAttribute("side", "left");
            } else {
                 decorationElement.setAttribute("side", "right");
            }
            if (view->isBridgeHasEntry() && view->isBridgeHasExit()) {
                 decorationElement.setAttribute("end", "both");
            } else if (view->isBridgeHasEntry()) {
                 decorationElement.setAttribute("end", "entry");
            } else if (view->isBridgeHasExit()) {
                 decorationElement.setAttribute("end", "exit");
            }
             decorationElement.setAttribute("color", ColorUtil::colorToHexString(view->getBridgeColor()));
             decorationElement.setAttribute("linewidth", QString::number(view->getBridgeLineWidth()));
             decorationElement.setAttribute("approachwidth", QString::number(view->getBridgeApproachWidth()));
             decorationElement.setAttribute("deckwidth", QString::number(view->getBridgeDeckWidth()));
             decorationElement.appendChild( decorationElement);
        }
        if (view->isBumperEndStart() || view->isBumperEndStop()) {
            QDomElement  decorationElement = doc.createElement("bumper");
            if (view->isBumperEndStart() && view->isBumperEndStop()) {
                 decorationElement.setAttribute("end", "both");
            } else if (view->isBumperEndStop()) {
                 decorationElement.setAttribute("end", "stop");
            } else {
                 decorationElement.setAttribute("end", "start");
            }
             decorationElement.setAttribute("color", ColorUtil::colorToHexString(view->getBumperColor()));
             decorationElement.setAttribute("linewidth", QString::number(view->getBumperLineWidth()));
             decorationElement.setAttribute("length", QString::number(view->getBumperLength()));
            if (view->isBumperFlipped()) {
                 decorationElement.setAttribute("flip", "true");
            }
             decorationElement.appendChild( decorationElement);
        }

        if (view->isTunnelSideLeft() || view->isTunnelSideRight()) {
            QDomElement  decorationElement = doc.createElement("tunnel");
            if (view->isTunnelSideLeft() && view->isTunnelSideRight()) {
                 decorationElement.setAttribute("side", "both");
            } else if (view->isTunnelSideLeft()) {
                 decorationElement.setAttribute("side", "left");
            } else {
                 decorationElement.setAttribute("side", "right");
            }
            if (view->isTunnelHasEntry() && view->isTunnelHasExit()) {
                 decorationElement.setAttribute("end", "both");
            } else if (view->isTunnelHasEntry()) {
                 decorationElement.setAttribute("end", "entry");
            } else if (view->isTunnelHasExit()) {
                 decorationElement.setAttribute("end", "exit");
            }
             decorationElement.setAttribute("color", ColorUtil::colorToHexString(view->getTunnelColor()));
             decorationElement.setAttribute("linewidth", QString::number(view->getTunnelLineWidth()));
             decorationElement.setAttribute("entrancewidth", QString::number(view->getTunnelEntranceWidth()));
             decorationElement.setAttribute("floorwidth", QString::number(view->getTunnelFloorWidth()));
             decorationElement.appendChild( decorationElement);
        }
    }

    //element.setAttribute("class", getClass().getName());
    log->info("storing old fixed class name for TrackSegment");
    element.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml.TrackSegmentXml");

    return element;
}   // store

//@Override
/*public*/ bool TrackSegmentViewXml::load(QDomElement shared, QDomElement perNode) {
    log->error("Invalid method called");
    return false;
}

/**
 * Load, starting with the track segment element, then all all attributes
 *
 * @param QDomElement Top level QDomElement to unpack.
 * @param o       LayoutEditor as an Object
 */
//@Override
/*public*/ void TrackSegmentViewXml::load(QDomElement element, QObject* o) throw (Exception){
    // create the objects
    LayoutEditor* p = (LayoutEditor*) o;

    // get attributes
    QString name = element.attribute("ident") ;

    bool dash = getAttributeBooleanValue(element, "dashed", true);
    bool main = getAttributeBooleanValue(element, "mainline", true);
    bool hide = getAttributeBooleanValue(element, "hidden", false);

    QString con1Name = element.attribute("connect1name") ;
    QString con2Name = element.attribute("connect2name") ;

    QMetaEnum metaEnum = QMetaEnum::fromType<HitPointType::TYPES>();

    bool ok;
    QString ts;
    HitPointType::TYPES type1 = (HitPointType::TYPES)metaEnum.keyToValue((ts = element.attribute("type1")).toLocal8Bit(), &ok);//htpMap.inputFromAttribute(element.attribute("type1"));
    if(!ok)
    {
     int i = ts.toInt(&ok);
     {
       type1 = (HitPointType::TYPES)i;
     }
    }
    HitPointType::TYPES type2 = (HitPointType::TYPES)metaEnum.keyToValue((ts =  element.attribute("type2")).toLocal8Bit(), &ok);
    if(!ok)
    {
     int i = ts.toInt(&ok);
     {
       type2 = (HitPointType::TYPES)i;
     }
    }

    // create the new TrackSegment and view
    TrackSegment* lt = new TrackSegment(name,
            con1Name, type1, con2Name, type2,
            main, p);
    TrackSegmentView* lv = new TrackSegmentView(lt, p);
    lv->setHidden(hide);

    lv->setDashed(dash);
    lv->setArc( getAttributeBooleanValue(element, "arc", false) );

    if (lv->isArc()) {
        lv->setFlip( getAttributeBooleanValue(element, "flip", false) );
        lv->setCircle( getAttributeBooleanValue(element, "circle", false) );
        if (lv->isCircle()) {
            lv->setAngle( getAttributeDoubleValue(element, "angle", 0.0) );
        }
    }

    if ( getAttributeBooleanValue(element, "bezier", false)) {
        // load control points
        QDomElement controlpointsElement = element.firstChildElement("controlpoints");
        if (controlpointsElement != QDomElement()) {
            QDomNodeList elementList = controlpointsElement.elementsByTagName("controlpoint");
            if (!elementList.isEmpty()) {
                if (elementList.size() >= 2) {
                    //for (QDomElement value : elementList)
                 for(int i=0; i < elementList.size(); i++)
                 {
                  QDomElement value = elementList.at(i).toElement();
                        double x = 0.0;
                        double y = 0.0;
                        int index = 0;
                        try {
                         bool ok;
                            index = (value.attribute("index")).toInt(&ok);
                            if(!ok) throw new DataConversionException();
                            x = (value.attribute("x")).toFloat(&ok);
                            if(!ok) throw new DataConversionException();
                            y = (value.attribute("y")).toFloat(&ok);
                            if(!ok) throw new DataConversionException();
                        } catch (DataConversionException* e) {
                            log->error("failed to convert controlpoint coordinates or index attributes");
                        }
                        lv->setBezierControlPoint(QPointF(x, y), index);
                    }
                } else {
                    log->error(tr("Track segment Bezier two controlpoint elements not found. (found %1)").arg(elementList.size()));
                }
            } else {
                log->error("Track segment Bezier controlpoint elements not found.");
            }
        } else {
            log->error("Track segment Bezier controlpoints QDomElement not found.");
        }
        // NOTE: do this LAST (so reCenter won't be called yet)
        lv->setBezier(true);
    }

    if ( getAttributeBooleanValue(element, "hideConLines", false) ) {
        lv->hideConstructionLines(TrackSegmentView::HIDECON);
    }
    // load decorations
    QDomElement decorationsElement = element.firstChildElement("decorations");
    if (decorationsElement != QDomElement()) {
        QDomNodeList  decorationElementList = decorationsElement.childNodes();
        if (! decorationElementList.isEmpty()) {
            QMap<QString, QString> decorations = QMap<QString, QString>();
            //for (QDomElement  decorationElement :  decorationElementList)
            for(int i=0; i <  decorationElementList.size(); i++)
            {
             QDomElement  decorationElement =  decorationElementList.at(i).toElement();
                QString decorationName =  decorationElement.tagName();
                if (decorationName == ("arrow")) {
                    QString a =  decorationElement.attribute("style");
                    if (a != "") {
                        bool ok;
                            lv->setArrowStyle(a.toInt(&ok));
                        if(!ok) {
                        }
                    }
                    // assume both ends
                    lv->setArrowEndStart(true);
                    lv->setArrowEndStop(true);
                    a =  decorationElement.attribute("end");
                    if (a != "") {
                        QString value = a ;
                        if (value == ("start")) {
                            lv->setArrowEndStop(false);
                        } else if (value == ("stop")) {
                            lv->setArrowEndStart(false);
                        }
                    }
                    // assume both directions
                    lv->setArrowDirIn(true);
                    lv->setArrowDirOut(true);
                    a =  decorationElement.attribute("direction");
                    if (a != "") {
                        QString value = a ;
                        if (value == ("in")) {
                            lv->setArrowDirOut(false);
                        } else if (value == ("out")) {
                            lv->setArrowDirIn(false);
                        }
                    }
                    a =  decorationElement.attribute("color");
                    if ( !a.isEmpty()) {
                        try {
                            lv->setArrowColor(ColorUtil::stringToColor(a ));
                        } catch (IllegalArgumentException e) {
                            lv->setArrowColor(Qt::black);
                            log->error(tr("Invalid color %1; using black").arg(a ));
                        }
                    }
                    a =  decorationElement.attribute("linewidth");
                    if ( !a.isEmpty()) {
                        bool ok;
                            lv->setArrowLineWidth(a.toInt(&ok));
                        if(!ok) {
                        }
                    }
                    a =  decorationElement.attribute("length");
                    if ( !a.isEmpty()) {
                        bool ok;
                            lv->setArrowLength(a.toInt(&ok));
                        if(!ok) {
                        }
                    }
                    a =  decorationElement.attribute("gap");
                    if ( !a.isEmpty()) {
                        bool ok;
                            lv->setArrowGap(a.toInt(&ok));
                        if(!ok) {
                        }
                    }
                } else if (decorationName == ("bridge")) {
                    // assume both sides
                    lv->setBridgeSideLeft(true);
                    lv->setBridgeSideRight(true);
                    QString a =  decorationElement.attribute("side");
                    if ( !a.isEmpty()) {
                        QString value = a ;
                        if (value == ("right")) {
                            lv->setBridgeSideLeft(false);
                        } else if (value == ("left")) {
                            lv->setBridgeSideRight(false);
                        }
                    }
                    // assume neither end
                    lv->setBridgeHasEntry(false);
                    lv->setBridgeHasExit(false);
                    a =  decorationElement.attribute("end");
                    if ( !a.isEmpty()) {
                        QString value = a ;
                        if (value == ("both")) {
                            lv->setBridgeHasEntry(true);
                            lv->setBridgeHasExit(true);
                        } else if (value == ("entry")) {
                            lv->setBridgeHasEntry(true);
                            lv->setBridgeHasExit(false);
                        } else if (value == ("exit")) {
                            lv->setBridgeHasEntry(false);
                            lv->setBridgeHasExit(true);
                        }
                    }

                    a =  decorationElement.attribute("color");
                    if ( !a.isEmpty()) {
                        try {
                            lv->setBridgeColor(ColorUtil::stringToColor(a ));
                        } catch (IllegalArgumentException e) {
                            lv->setBridgeColor(Qt::black);
                            log->error(tr("Invalid color %1; using black").arg(a));
                        }
                    }

                    a =  decorationElement.attribute("linewidth");
                    if ( !a.isEmpty()) {
                        bool ok;
                            lv->setBridgeLineWidth(a.toInt(&ok));
                        if(!ok) {
                        }
                    }

                    a =  decorationElement.attribute("approachwidth");
                    if ( !a.isEmpty()) {
                       bool ok;
                            lv->setBridgeApproachWidth(a.toInt(&ok));
                        if(!ok) {
                        }
                    }

                    a =  decorationElement.attribute("deckwidth");
                    if ( !a.isEmpty()) {
                        bool ok;
                            lv->setBridgeDeckWidth(a.toInt(&ok));
                        if(!ok) {
                        }
                    }
                } else if (decorationName == ("bumper")) {
                    // assume both ends
                    lv->setBumperEndStart(true);
                    lv->setBumperEndStop(true);
                    QString a =  decorationElement.attribute("end");
                    if ( !a.isEmpty()) {
                        QString value = a ;
                        if (value == ("start")) {
                            lv->setBumperEndStop(false);
                        } else if (value == ("stop")) {
                            lv->setBumperEndStart(false);
                        }
                    }

                    a =  decorationElement.attribute("color");
                    if ( !a.isEmpty()) {
                        try {
                            lv->setBumperColor(ColorUtil::stringToColor(a ));
                        } catch (IllegalArgumentException e) {
                            lv->setBumperColor(Qt::black);
                            log->error(tr("Invalid color %1; using black").arg(a));
                        }
                    }

                    a =  decorationElement.attribute("linewidth");
                    if ( !a.isEmpty()) {
                        bool ok;
                            lv->setBumperLineWidth(a.toInt(&ok));
                        if(!ok) {
                        }
                    }

                    a =  decorationElement.attribute("length");
                    if ( !a.isEmpty()) {
                        bool ok;
                            lv->setBumperLength(a.toInt(&ok));
                        if(!ok) {
                        }
                    }

                    a =  decorationElement.attribute("flip");
                    if ( !a.isEmpty()) {
                            lv->setBumperFlipped(a == "true");
                    }
                } else if (decorationName == ("tunnel")) {
                    // assume both sides
                    lv->setTunnelSideLeft(true);
                    lv->setTunnelSideRight(true);
                    QString a =  decorationElement.attribute("side");
                    if ( !a.isEmpty()) {
                        QString value = a ;
                        if (value == ("right")) {
                            lv->setTunnelSideLeft(false);
                        } else if (value == ("left")) {
                            lv->setTunnelSideRight(false);
                        }
                    }
                    // assume neither end
                    lv->setTunnelHasEntry(false);
                    lv->setTunnelHasExit(false);
                    a =  decorationElement.attribute("end");
                    if ( !a.isEmpty()) {
                        QString value = a ;
                        if (value == ("both")) {
                            lv->setTunnelHasEntry(true);
                            lv->setTunnelHasExit(true);
                        } else if (value == ("entry")) {
                            lv->setTunnelHasEntry(true);
                            lv->setTunnelHasExit(false);
                        } else if (value == ("exit")) {
                            lv->setTunnelHasEntry(false);
                            lv->setTunnelHasExit(true);
                        }
                    }

                    a =  decorationElement.attribute("color");
                    if ( !a.isEmpty()) {
                        try {
                            lv->setTunnelColor(ColorUtil::stringToColor(a ));
                        } catch (IllegalArgumentException e) {
                            lv->setTunnelColor(Qt::black);
                            log->error(tr("Invalid color %1; using black").arg(a));
                        }
                    }

                    a =  decorationElement.attribute("linewidth");
                    if ( !a.isEmpty()) {
                        bool ok;
                            lv->setTunnelLineWidth(a.toInt(&ok));
                        if(!ok) {
                        }
                    }

                    a =  decorationElement.attribute("entrancewidth");
                    if ( !a.isEmpty()) {
                        bool ok;
                            lv->setTunnelEntranceWidth(a.toInt(&ok));
                        if(!ok) {
                        }
                    }

                    a =  decorationElement.attribute("floorwidth");
                    if ( !a.isEmpty()) {
                        bool ok;
                            lv->setTunnelFloorWidth(a.toInt(&ok));
                        if(!ok) {
                        }
                    }
                } else {
                    try {
                        QString eName =  decorationElement.attribute("name");
                        QString a =  decorationElement.attribute("value");
                        QString eValue = (a != "") ? a : "";
                        decorations.insert(eName, eValue);
                    } catch (NullPointerException* e) {  // considered normal if the attribute is not present
                    }
                }
            }
            lv->setDecorations(&decorations);
        }
    }

    // get remaining attribute
    QString a = element.attribute("blockname");
    if ( !a.isEmpty()) {
        lt->tLayoutBlockName = a ;
    }

    p->addLayoutTrack(lt, lv);
}

// /*static*/ final EnumIO<HitPointType> htpMap = new EnumIoNamesNumbers<>(HitPointType.class);

/*private*/ /*final*/ /*static*/ Logger* TrackSegmentViewXml::log = LoggerFactory::getLogger("TrackSegmentViewXml");
