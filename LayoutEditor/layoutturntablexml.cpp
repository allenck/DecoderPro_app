#include "layoutturntablexml.h"
#include "layoutturntable.h"
#include "tracksegment.h"
#include "layouteditor.h"
/**
 * This module handles configuration for display.LayoutTurntable objects for a
 * LayoutEditor.
 *
 * @author David Duchamp Copyright (c) 2007
 * @version $Revision: 28771 $
 */
// /*public*/ class LayoutTurntableXml extends AbstractXmlAdapter {

/*public*/ LayoutTurntableXml::LayoutTurntableXml() {
 log = new Logger("LayoutTurntable");
}

/**
 * Default implementation for storing the contents of a LayoutTurntable
 *
 * @param o Object to store, of type LayoutTurntable
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement LayoutTurntableXml::store(QObject* o)
{
 LayoutTurntable* p = (LayoutTurntable*) o;

 QDomElement element = doc.createElement("layoutturntable");
 bool turnoutControl = p->isTurnoutControlled();
 // include attributes
 element.setAttribute("ident", p->getID());
 element.setAttribute("radius", p->getRadius());
 QPointF coords = p->getCoordsCenter();
 element.setAttribute("xcen", coords.x());
 element.setAttribute("ycen", coords.y());
 element.setAttribute("turnoutControlled", (turnoutControl ? "yes" : "no"));
 element.setAttribute("class", "jmri.jmrit.display.configurexml.LayoutTurntableXml");
 // add ray tracks
 for (int i = 0; i < p->getNumberRays(); i++)
 {
  QDomElement rElem = doc.createElement("raytrack");
  rElem.setAttribute("angle", p->getRayAngle(i));
  TrackSegment* t = p->getRayConnectOrdered(i);
  if (t != NULL) {
      rElem.setAttribute("connectname", t->getID());
  }
  rElem.setAttribute("index", p->getRayIndex(i));
  if (turnoutControl && p->getRayTurnoutName(i) != NULL)
  {
   rElem.setAttribute("turnout", p->getRayTurnoutName(i));
   if (p->getRayTurnoutState(i) == Turnout::THROWN)
   {
    rElem.setAttribute("turnoutstate", "thrown");
   }
   else
   {
    rElem.setAttribute("turnoutstate", "closed");
   }
  }
  element.appendChild(rElem);
 }
 return element;
}

/*public*/ bool LayoutTurntableXml::load(QDomElement element) throw (Exception)
{
    log->error("Invalid method called");
    return false;
}

/**
 * Load, starting with the layoutturntable element, then all the other data
 *
 * @param element Top level QDomElement to unpack.
 * @param o       LayoutEditor as an Object
 */
/*public*/ void LayoutTurntableXml::load(QDomElement element, QObject* o) throw (Exception)
{
    // create the objects
    LayoutEditor* p = (LayoutEditor*) o;

    // get center point
    QString name = element.attribute("ident");
    double x = 0.0;
    double y = 0.0;
    double radius = 25.0;
    //try {
        x = element.attribute("xcen").toFloat();
        y = element.attribute("ycen").toFloat();
        radius = element.attribute("radius").toFloat();
//    } catch (org.jdom2.DataConversionException e) {
//        log->error("failed to convert layoutturntable center or radius attributes");
//    }
    // create the new LayoutTurntable
    LayoutTurntable* l = new LayoutTurntable(name, QPointF(x, y), p);
    l->setRadius(radius);

    bool turnoutControl = false;
    if (element.attribute("turnoutControlled") != NULL) {
        if (element.attribute("turnoutControlled")==("yes")) {
            turnoutControl = true;
        }
    }
    l->setTurnoutControlled(turnoutControl);

    // load ray tracks
    QDomNodeList rayTrackList = element.elementsByTagName("raytrack");
    if (rayTrackList.size() > 0) {
        for (int i = 0; i < rayTrackList.size(); i++) {
            double angle = 0.0;
            int index = 0;
            QDomElement relem = rayTrackList.at(i).toElement();
            //try {
                angle = (relem.attribute("angle")).toFloat();
                index = (relem.attribute("index")).toInt();
//            } catch (org.jdom2.DataConversionException e) {
//                log->error("failed to convert ray track angle or index attributes");
//            }
            QString connectName = "";
            QString a = relem.attribute("connectname");
            if (a != NULL) {
                connectName = a;
            }
            l->addRayTrack(angle, index, connectName);
            if (turnoutControl && relem.attribute("turnout") != NULL) {
                //Turnout t = jmri.InstanceManager.turnoutManagerInstance().getTurnout();
                if (relem.attribute("turnoutstate")==("thrown")) {
                    l->setRayTurnout(index, relem.attribute("turnout"), Turnout::THROWN);
                } else {
                    l->setRayTurnout(index, relem.attribute("turnout"), Turnout::CLOSED);
                }
            }
        }
    }
    p->turntableList->append(l);
}
