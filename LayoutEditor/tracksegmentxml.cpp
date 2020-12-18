#include "tracksegmentxml.h"
#include "tracksegment.h"
#include "layouteditor.h"

TrackSegmentXml::TrackSegmentXml(QObject *parent) :
  AbstractXmlAdapter(parent)
{
}
/**
 * This module handles configuration for display.TrackSegment objects for a
 * LayoutEditor.
 *
 * @author David Duchamp Copyright (c) 2007
 * @version $Revision: 28771 $
 */
///*public*/ class TrackSegmentXml extends AbstractXmlAdapter {

///*public*/ TrackSegmentXml() {
//}

/**
 * Default implementation for storing the contents of a TrackSegment
 *
 * @param o Object to store, of type TrackSegment
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement TrackSegmentXml::store(QObject* o) {

 TrackSegment* p = (TrackSegment*) o;

 QDomElement element = doc.createElement("tracksegment");

 // include attributes
 element.setAttribute("ident", p->getID());
 if (p->getBlockName().length() > 0)
 {
     element.setAttribute("blockname", p->getBlockName());
 }
 element.setAttribute("connect1name", p->getConnect1Name());
 element.setAttribute("type1",  p->getType1());
 element.setAttribute("connect2name", p->getConnect2Name());
 element.setAttribute("type2",  p->getType2());
 element.setAttribute("dashed",  (p->isDashed() ? "yes" : "no"));
 element.setAttribute("mainline",  (p->isMainline() ? "yes" : "no"));
 element.setAttribute("hidden",  (p->getHidden() ? "yes" : "no"));
 if (p->isArc())
 {
  element.setAttribute("arc", "yes");
  element.setAttribute("flip",  (p->isFlip() ? "yes" : "no"));
  element.setAttribute("circle",  (p->isCircle() ? "yes" : "no"));
  if ((p->isCircle()) && (p->getAngle() != 0.0))
  {
   element.setAttribute("angle",  (p->getAngle()));
   element.setAttribute("hideConLines",  (p->hideConstructionLines() ? "yes" : "no"));
  }
 }
 if ( p->isBezier())
 {
     element.setAttribute("bezier", "yes");
     element.setAttribute("hideConLines", ( p->hideConstructionLines() ? "yes" : "no"));
     // add control points
     QDomElement elementControlpoints = doc.createElement("controlpoints");
     for (int i = 0; i < p->getNumberOfBezierControlPoints(); i++) {
         QDomElement elementControlpoint = doc.createElement("controlpoint");

         elementControlpoint.setAttribute("index", i);

         QPointF pt = p->getBezierControlPoint(i);
         elementControlpoint.setAttribute("x",  pt.x());
         elementControlpoint.setAttribute("y",  pt.y());

         elementControlpoints.appendChild(elementControlpoint);
     }
     element.appendChild(elementControlpoints);
 }

 // store decorations
 QMap<QString, QString>* decorations = p->getDecorations();
 if ((decorations != nullptr) && (decorations->size() > 0)) {
     QDomElement decorationsElement = doc.createElement("decorations");
     //for (Map.Entry<String, String> entry : decorations.entrySet())
     QMapIterator<QString, QString> entry(*decorations);
     while(entry.hasNext())
     {
      entry.next();
         QString name = entry.key();
         if (name != ("arrow") && name !=("bridge")
                 && name != ("bumper") && name != ("tunnel")) {
             QDomElement decorationElement = doc.createElement("decoration");
             decorationElement.setAttribute("name", name);
             QString value = entry.value();
             if (!value.isEmpty()) {
                 decorationElement.setAttribute("value", value);
             }
             decorationsElement.appendChild(decorationElement);
         }
     }
     element.appendChild(decorationsElement);

     if (p->getArrowStyle() > 0) {
         QDomElement decorationElement = doc.createElement("arrow");
         decorationElement.setAttribute("style", ( p->getArrowStyle()));
         if (p->isArrowEndStart() &&  p->isArrowEndStop()) {
             decorationElement.setAttribute("end", "both");
         } else if ( p->isArrowEndStop()) {
             decorationElement.setAttribute("end", "stop");
         } else {
             decorationElement.setAttribute("end", "start");
         }
         if (p->isArrowDirIn() && p->isArrowDirOut()) {
             decorationElement.setAttribute("direction", "both");
         } else if (p->isArrowDirOut()) {
             decorationElement.setAttribute("direction", "out");
         } else {
             decorationElement.setAttribute("direction", "in");
         }
         decorationElement.setAttribute("color", ColorUtil::colorToHexString(p->getArrowColor()));
         decorationElement.setAttribute("linewidth", (p->getArrowLineWidth()));
         decorationElement.setAttribute("length", (p->getArrowLength()));
         decorationElement.setAttribute("gap", (p->getArrowGap()));
         decorationsElement.appendChild(decorationElement);
     }
     if ( p->isBridgeSideLeft() ||  p->isBridgeSideRight()) {
         QDomElement decorationElement = doc.createElement("bridge");
         if ( p->isBridgeSideLeft() &&  p->isBridgeSideRight()) {
             decorationElement.setAttribute("side", "both");
         } else if ( p->isBridgeSideLeft()) {
             decorationElement.setAttribute("side", "left");
         } else {
             decorationElement.setAttribute("side", "right");
         }
         if ( p->isBridgeHasEntry() &&  p->isBridgeHasExit()) {
             decorationElement.setAttribute("end", "both");
         } else if ( p->isBridgeHasEntry()) {
             decorationElement.setAttribute("end", "entry");
         } else if ( p->isBridgeHasExit()) {
             decorationElement.setAttribute("end", "exit");
         }
         decorationElement.setAttribute("color", ColorUtil::colorToHexString( p->getBridgeColor()));
         decorationElement.setAttribute("linewidth", ( p->getBridgeLineWidth()));
         decorationElement.setAttribute("approachwidth", ( p->getBridgeApproachWidth()));
         decorationElement.setAttribute("deckwidth", ( p->getBridgeDeckWidth()));
         decorationsElement.appendChild(decorationElement);
     }
     if ( p->isBumperEndStart() ||  p->isBumperEndStop()) {
         QDomElement decorationElement =doc.createElement("bumper");
         if ( p->isBumperEndStart() &&  p->isBumperEndStop()) {
             decorationElement.setAttribute("end", "both");
         } else if ( p->isBumperEndStop()) {
             decorationElement.setAttribute("end", "stop");
         } else {
             decorationElement.setAttribute("end", "start");
         }
         decorationElement.setAttribute("color", ColorUtil::colorToHexString( p->getBumperColor()));
         decorationElement.setAttribute("linewidth", ( p->getBumperLineWidth()));
         decorationElement.setAttribute("length", ( p->getBumperLength()));
         if ( p->isBumperFlipped()) {
             decorationElement.setAttribute("flip", "true");
         }
         decorationsElement.appendChild(decorationElement);
     }

     if ( p->isTunnelSideLeft() ||  p->isTunnelSideRight()) {
         QDomElement decorationElement = doc.createElement("tunnel");
         if ( p->isTunnelSideLeft() &&  p->isTunnelSideRight()) {
             decorationElement.setAttribute("side", "both");
         } else if ( p->isTunnelSideLeft()) {
             decorationElement.setAttribute("side", "left");
         } else {
             decorationElement.setAttribute("side", "right");
         }
         if ( p->isTunnelHasEntry() &&  p->isTunnelHasExit()) {
             decorationElement.setAttribute("end", "both");
         } else if ( p->isTunnelHasEntry()) {
             decorationElement.setAttribute("end", "entry");
         } else if ( p->isTunnelHasExit()) {
             decorationElement.setAttribute("end", "exit");
         }
         decorationElement.setAttribute("color", ColorUtil::colorToHexString( p->getTunnelColor()));
         decorationElement.setAttribute("linewidth", ( p->getTunnelLineWidth()));
         decorationElement.setAttribute("entrancewidth", ( p->getTunnelEntranceWidth()));
         decorationElement.setAttribute("floorwidth", ( p->getTunnelFloorWidth()));
         decorationsElement.appendChild(decorationElement);
     }
 }
 element.setAttribute("class", "jmri.jmrit.display.configurexml.TrackSegmentXml");
 return element;
}

/*public*/ bool TrackSegmentXml::load(QDomElement /*shared*/, QDomElement /*perNode*/) throw (Exception){
    log->error("Invalid method called");
    return false;
}

/**
 * Load, starting with the tracksegment element, then all all attributes
 *
 * @param element Top level QDomElement to unpack.
 * @param o       LayoutEditor as an Object
 */
/*public*/ void TrackSegmentXml::load(QDomElement element, QObject* o) throw (Exception)
{
 // create the objects
 LayoutEditor* p = (LayoutEditor*) o;

 // get attributes
 QString name = element.attribute("ident");
 int type1 = LayoutEditor::NONE;
 int type2 = LayoutEditor::NONE;
 //try {
 bool bOk=true, bOk1;
 type1 = element.attribute("type1").toInt(&bOk1);
 if(!bOk1) bOk = false;
 type2 = element.attribute("type2").toInt(&bOk1);
 if(!bOk1) bOk = false;
 //} catch (DataConversionException e) {
 if(!bOk)
 {
  log->error("failed to convert tracksegment attribute");
 }
 bool dash = true;
 if (element.attribute("dashed")==("no")) {
     dash = false;
 }
 bool main = true;
 if (element.attribute("mainline")==("no")) {
     main = false;
 }
 bool hide = true;
 if (element.attribute("hidden")==("no")) {
     hide = false;
 }
 QString con1Name = element.attribute("connect1name");
 QString con2Name = element.attribute("connect2name");

 // create the new TrackSegment
 TrackSegment* l = new TrackSegment(name, con1Name, type1, con2Name, type2,
         dash, main, hide, p);
 try
 {
  if (element.attribute("arc")==("yes"))
  {
   l->setArc(true);
  }
 }
 catch (NullPointerException e)
 {
 }//considered normal if the attribute is not present }
 if (l->isArc())
 {
  //int angle = 0;
  //int startangle = 0;
  try {
      if (element.attribute("flip")==("yes")) {
          l->setFlip(true);
      }
  } catch (NullPointerException e) {
  }//considered normal if the attribute is not present }
  try {
      if (element.attribute("circle")==("yes")) {
          l->setCircle(true);
      }
  } catch (NullPointerException e) {
  }
  if (l->isCircle()) {
      try {
          l->setAngle(element.attribute("angle").toDouble());
      } catch (DataConversionException e) {
          log->error("failed to convert tracksegment attribute");
      } catch (NullPointerException e) {  // considered normal if the attribute not present
      }
  }
  try {
      if (element.attribute("hideConLines")==("yes")) {
          l->hideConstructionLines(TrackSegment::HIDECON);
      }
  } catch (NullPointerException e) {
  }//considered normal if the attribute is not present }
 }
 try {
             if (element.attribute("bezier")== "true") {
                 // load control points
                 QDomElement controlpointsElement = doc.createElement("controlpoints");
                 if (!controlpointsElement.isNull()) {
                     QDomNodeList elementList = controlpointsElement.elementsByTagName("controlpoint");
                     if (!elementList.isEmpty()) {
                         if (elementList.size() >= 2) {
                             for (int i = 0; i < elementList.size(); i++) {
                                 double x = 0.0;
                                 double y = 0.0;
                                 int index = 0;
                                 QDomElement relem = elementList.at(i).toElement();
                                 try
                                 {
                                  bool bok;
                                     index = (relem.attribute("index")).toInt(&bok);
                                     if(!bok) throw DataConversionException();
                                     x = (relem.attribute("x")).toFloat(&bok);
                                     if(!bok) throw DataConversionException();
                                     y = (relem.attribute("y")).toFloat(&bok);
                                     if(!bok) throw DataConversionException();

                                 } catch(DataConversionException ex) {
                                     log->error("failed to convert controlpoint coordinates or index attributes");
                                 }
                                 l->setBezierControlPoint(QPointF(x, y), index);
                             }
                         } else {
                             log->error("Track segment Bezier two controlpoint elements not found. (found " + QString::number(elementList.size()) + ")");
                         }
                     } else {
                         log->error("Track segment Bezier controlpoint elements not found.");
                     }
                 } else {
                     log->error("Track segment Bezier controlpoints element not found.");
                 }
                 // NOTE: do this LAST (so reCenter won't be called yet)
                 l->setBezier(true);
             }
         } catch (DataConversionException e) {
             log->error("failed to convert tracksegment attribute");
         } catch (NullPointerException e) {  // considered normal if the attribute is not present
         }

         //if (l.getName() == ("T31")) {
         //    log.debug("Stop");
         //}
         // load decorations
         QDomElement decorationsElement = element.firstChildElement("decorations");
         if (!decorationsElement.isNull()) {
             QDomNodeList decorationElementList = decorationsElement.childNodes();
             if (!decorationElementList.isEmpty()) {
                 QMap<QString, QString>* decorations = new QMap<QString, QString>();
                 //for (Element decorationElement : decorationElementList)
                 for(int i=0; i < decorationElementList.size(); i++)
                 {
                  QDomElement decorationElement= decorationElementList.at(i).toElement();
                     QString decorationName = decorationElement.tagName();
                     if (decorationName == ("arrow")) {
                         QString a = decorationElement.attribute("style");
                         if (a != "") {
                             bool bok;
                                 l->setArrowStyle(a.toInt(&bok));
                             if(!bok) {
                             }
                         }
                         // assume both ends
                         l->setArrowEndStart(true);
                         l->setArrowEndStop(true);
                         a = decorationElement.attribute("end");
                         if (a != "") {
                             QString value = a ;
                             if (value == ("start")) {
                                 l->setArrowEndStop(false);
                             } else if (value == ("stop")) {
                                 l->setArrowEndStart(false);
                             }
                         }
                         // assume both directions
                         l->setArrowDirIn(true);
                         l->setArrowDirOut(true);
                         a = decorationElement.attribute("direction");
                         if (a != "") {
                             QString value = a ;
                             if (value == ("in")) {
                                 l->setArrowDirOut(false);
                             } else if (value == ("out")) {
                                 l->setArrowDirIn(false);
                             }
                         }
                         a = decorationElement.attribute("color");
                         if (a != "") {
                             l->setArrowColor(ColorUtil::stringToColor(a ));
                         }
                         a = decorationElement.attribute("linewidth");
                         if (a != "") {
                             try
                          {
                                 l->setArrowLineWidth(a.toInt());
                             } catch (DataConversionException e) {
                             }
                         }
                         a = decorationElement.attribute("length");
                         if (a != "") {
                             try {
                                 l->setArrowLength(a.toInt());
                             } catch (DataConversionException e) {
                             }
                         }
                         a = decorationElement.attribute("gap");
                         if (a != "") {
                             try {
                                 l->setArrowGap(a.toInt());
                             } catch (DataConversionException e) {
                             }
                         }
                     } else if (decorationName == ("bridge")) {
                         // assume both sides
                         l->setBridgeSideLeft(true);
                         l->setBridgeSideRight(true);
                         QString a = decorationElement.attribute("side");
                         if (a != "") {
                             QString value = a ;
                             if (value == ("right")) {
                                 l->setBridgeSideLeft(false);
                             } else if (value == ("left")) {
                                 l->setBridgeSideRight(false);
                             }
                         }
                         // assume neither end
                         l->setBridgeHasEntry(false);
                         l->setBridgeHasExit(false);
                         a = decorationElement.attribute("end");
                         if (a != "") {
                             QString value = a ;
                             if (value == ("both")) {
                                 l->setBridgeHasEntry(true);
                                 l->setBridgeHasExit(true);
                             } else if (value == ("entry")) {
                                 l->setBridgeHasEntry(true);
                                 l->setBridgeHasExit(false);
                             } else if (value == ("exit")) {
                                 l->setBridgeHasEntry(false);
                                 l->setBridgeHasExit(true);
                             }
                         }

                         a = decorationElement.attribute("color");
                         if (a != "") {
                             l->setBridgeColor(ColorUtil::stringToColor(a ));
                         }

                         a = decorationElement.attribute("linewidth");
                         if (a != "") {
                             try {
                                 l->setBridgeLineWidth(a.toInt());
                             } catch (DataConversionException e) {
                             }
                         }

                         a = decorationElement.attribute("approachwidth");
                         if (a != "") {
                             try {
                                 l->setBridgeApproachWidth(a.toInt());
                             } catch (DataConversionException e) {
                             }
                         }

                         a = decorationElement.attribute("deckwidth");
                         if (a != "") {
                             try {
                                 l->setBridgeDeckWidth(a.toInt());
                             } catch (DataConversionException e) {
                             }
                         }
                     } else if (decorationName == ("bumper")) {
                         // assume both ends
                         l->setBumperEndStart(true);
                         l->setBumperEndStop(true);
                         QString a = decorationElement.attribute("end");
                         if (a != "") {
                             QString value = a ;
                             if (value == ("start")) {
                                 l->setBumperEndStop(false);
                             } else if (value == ("stop")) {
                                 l->setBumperEndStart(false);
                             }
                         }

                         a = decorationElement.attribute("color");
                         if (a != "") {
                             l->setBumperColor(ColorUtil::stringToColor(a ));
                         }

                         a = decorationElement.attribute("linewidth");
                         if (a != "") {
                             try {
                                 l->setBumperLineWidth(a.toInt());
                             } catch (DataConversionException e) {
                             }
                         }

                         a = decorationElement.attribute("length");
                         if (a != "") {
                             try {
                                 l->setBumperLength(a.toInt());
                             } catch (DataConversionException e) {
                             }
                         }

                         a = decorationElement.attribute("flip");
                         if (a != "") {
                             try {
                                 l->setBumperFlipped(a == "true");
                             } catch (DataConversionException e) {
                             }
                         }
                     } else if (decorationName == ("tunnel")) {
                         // assume both sides
                         l->setTunnelSideLeft(true);
                         l->setTunnelSideRight(true);
                         QString a = decorationElement.attribute("side");
                         if (a != "") {
                             QString value = a ;
                             if (value == ("right")) {
                                 l->setTunnelSideLeft(false);
                             } else if (value == ("left")) {
                                 l->setTunnelSideRight(false);
                             }
                         }
                         // assume neither end
                         l->setTunnelHasEntry(false);
                         l->setTunnelHasExit(false);
                         a = decorationElement.attribute("end");
                         if (a != "") {
                             QString value = a ;
                             if (value == ("both")) {
                                 l->setTunnelHasEntry(true);
                                 l->setTunnelHasExit(true);
                             } else if (value == ("entry")) {
                                 l->setTunnelHasEntry(true);
                                 l->setTunnelHasExit(false);
                             } else if (value == ("exit")) {
                                 l->setTunnelHasEntry(false);
                                 l->setTunnelHasExit(true);
                             }
                         }

                         a = decorationElement.attribute("color");
                         if (a != "") {
                             l->setTunnelColor(ColorUtil::stringToColor(a ));
                         }

                         a = decorationElement.attribute("linewidth");
                         if (a != "") {
                             try {
                                 l->setTunnelLineWidth(a.toInt());
                             } catch (DataConversionException e) {
                             }
                         }

                         a = decorationElement.attribute("entrancewidth");
                         if (a != "") {
                             try {
                                 l->setTunnelEntranceWidth(a.toInt());
                             } catch (DataConversionException e) {
                             }
                         }

                         a = decorationElement.attribute("floorwidth");
                         if (a != "") {
                             try {
                                 l->setTunnelFloorWidth(a.toInt());
                             } catch (DataConversionException e) {
                             }
                         }
                     } else {
                         try {
                             QString eName = decorationElement.attribute("name") ;
                             QString a = decorationElement.attribute("value");
                             QString eValue = (a != "") ? a  : "";
                             decorations->insert(eName, eValue);
                         } catch (NullPointerException e) {  // considered normal if the attribute is not present
                             continue;
                         }
                     }
                 }
                 l->setDecorations(decorations);
             }
         }
 // get remaining attribute
 QString a = element.attribute("blockname");
 if (a != "") {
     l->tLayoutBlockName = a;
 }
 p->addLayoutTrack(l);

}

/*private*/ /*final*/ /*static*/ Logger* TrackSegmentXml::log
           = LoggerFactory::getLogger("TrackSegmentXml");
