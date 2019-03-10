#include "positionablepointxml.h"
#include "positionablepoint.h"
#include "panelmenu.h"

PositionablePointXml::PositionablePointXml(QObject *parent) :
  AbstractXmlAdapter(parent)
{
}
/**
 * This module handles configuration for display.PositionablePoint objects for a
 * LayoutEditor.
 *
 * @author David Duchamp Copyright (c) 2007
 * @version $Revision: 28771 $
 */
// /*public*/ class PositionablePointXml extends AbstractXmlAdapter {

///*public*/ PositionablePointXml() {
//}

/**
 * Default implementation for storing the contents of a PositionablePoint
 *
 * @param o Object to store, of type PositionablePoint
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement PositionablePointXml::store(QObject* o)
{
 PositionablePoint* p = (PositionablePoint*) o;

 QDomElement element = doc.createElement("positionablepoint");

 // include attributes
 element.setAttribute("ident", p->getID());
 element.setAttribute("type",  p->getType());
 QPointF coords = p->getCoordsCenter();
 element.setAttribute("x",  coords.x());
 element.setAttribute("y",  coords.y());
 if (p->getConnect1() != NULL)
 {
  element.setAttribute("connect1name", p->getConnect1()->getID());
 }
 if (p->getConnect2() != NULL)
 {
  element.setAttribute("connect2name", p->getConnect2()->getID());
 }
 if ((p->getEastBoundSignal() != NULL) && (p->getEastBoundSignal().length() > 0))
 {
  element.setAttribute("eastboundsignal", p->getEastBoundSignal());
 }
 if ((p->getWestBoundSignal() != NULL) && (p->getWestBoundSignal().length() > 0))
 {
  element.setAttribute("westboundsignal", p->getWestBoundSignal());
 }

 if ((p->getEastBoundSignalMastName() != NULL) && (p->getEastBoundSignalMastName().length() > 0))
 {
  element.setAttribute("eastboundsignalmast", p->getEastBoundSignalMastName());
 }
 if ((p->getWestBoundSignalMastName() != NULL) && (p->getWestBoundSignalMastName().length() > 0))
 {
  element.setAttribute("westboundsignalmast", p->getWestBoundSignalMastName());
 }

 if ((p->getEastBoundSensorName() != NULL) && (p->getEastBoundSensorName().length() > 0))
 {
  element.setAttribute("eastboundsensor", p->getEastBoundSensorName());
 }
 if ((p->getWestBoundSensorName() != NULL) && (p->getWestBoundSensorName().length() > 0))
 {
  element.setAttribute("westboundsensor", p->getWestBoundSensorName());
 }
 if (p->getType() == PositionablePoint::EDGE_CONNECTOR)
 {
  element.setAttribute("linkedpanel", p->getLinkEditorName());
  element.setAttribute("linkpointid", p->getLinkedPointId());
 }

 element.setAttribute("class", "jmri.jmrit.display.configurexml.PositionablePointXml");
 return element;
}

/*public*/ bool PositionablePointXml::load(QDomElement /*element*/) throw (Exception)
{
 Logger::error("Invalid method called");
 return false;
}

/**
 * Load, starting with the layoutblock element, then all the value-icon
 * pairs
 *
 * @param element Top level QDomElement to unpack.
 * @param o       LayoutEditor as an Object
 */
/*public*/ void PositionablePointXml::load(QDomElement element, QObject* o) throw (Exception)
{
 // create the objects
 LayoutEditor* p = (LayoutEditor*) o;

 // get attributes
 QString name = element.attribute("ident");
 int type = PositionablePoint::ANCHOR;
 double x = 0.0;
 double y = 0.0;
 try {
     x = element.attribute("x").toFloat();
     y = element.attribute("y").toFloat();
     type = element.attribute("type").toInt();
 } catch (DataConversionException e) {
     Logger::error("failed to convert positionablepoint attribute");
 }

 // create the new PositionablePoint
 PositionablePoint* l = new PositionablePoint(name, type,  QPointF(x, y), p);

 // get remaining attributes
 QString a = element.attribute("connect1name");
 if (!a.isNull())
 {
  l->trackSegment1Name = a;
 }
 a = element.attribute("connect2name");
 if (a != NULL)
 {
  l->trackSegment2Name = a;
 }
 a = element.attribute("eastboundsignal");
 if (a != NULL)
 {
  l->setEastBoundSignal(a);
 }
 a = element.attribute("westboundsignal");
 if (a != NULL)
 {
  l->setWestBoundSignal(a);
 }
 a = element.attribute("eastboundsignalmast");
 if (a != NULL)
 {
  l->setEastBoundSignalMast(a);
 }
 a = element.attribute("westboundsignalmast");
 if (a != NULL)
 {
  l->setWestBoundSignalMast(a);
 }
 a = element.attribute("eastboundsensor");
 if (a != NULL)
 {
  l->setEastBoundSensor(a);
 }
 a = element.attribute("westboundsensor");
 if (a != NULL)
 {
  l->setWestBoundSensor(a);
 }

 if (type == PositionablePoint::EDGE_CONNECTOR && element.attribute("linkedpanel") != NULL && element.attribute("linkpointid") != NULL)
 {
  QString linkedEditorName = element.attribute("linkedpanel");
  LayoutEditor* linkedEditor = (LayoutEditor*) PanelMenu::instance()->getEditorByName(linkedEditorName);
  if (linkedEditor != NULL)
  {
   QString linkedPoint = element.attribute("linkpointid");
   for (PositionablePoint* point : linkedEditor->getPositionablePoints())
   {
    if (point->getType() == PositionablePoint::EDGE_CONNECTOR && point->getId() == (linkedPoint))
    {
     point->setLinkedPoint(l);
     l->setLinkedPoint(point);
     break;
    }
   }
  }
 }

 p->getLayoutTracks()->append(l);
}
