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
 element.setAttribute("dashed",  (p->getDashed() ? "yes" : "no"));
 element.setAttribute("mainline",  (p->getMainline() ? "yes" : "no"));
 element.setAttribute("hidden",  (p->getHidden() ? "yes" : "no"));
 element.setAttribute("arc",  (p->getArc() ? "yes" : "no"));
 if (p->getArc())
 {
  element.setAttribute("flip",  (p->getFlip() ? "yes" : "no"));
  element.setAttribute("circle",  (p->getCircle() ? "yes" : "no"));
  if ((p->getCircle()) && (p->getAngle() != 0.0))
  {
   element.setAttribute("angle",  (p->getAngle()));
   element.setAttribute("hideConLines",  (p->hideConstructionLines() ? "yes" : "no"));
  }
  else
   element.setAttribute("angle",  (p->getTmpAngle())); // ACK add this

 }
 element.setAttribute("class", "jmri.jmrit.display.configurexml.TrackSegmentXml");
 return element;
}

/*public*/ bool TrackSegmentXml::load(QDomElement /*element*/) throw (Exception){
    Logger::error("Invalid method called");
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
  Logger::error("failed to convert tracksegment attribute");
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
 if (l->getArc())
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
  if (l->getCircle()) {
      try {
          l->setAngle(element.attribute("angle").toDouble());
      } catch (DataConversionException e) {
          Logger::error("failed to convert tracksegment attribute");
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
 // get remaining attribute
 QString a = element.attribute("blockname");
 if (a != "") {
     l->tBlockName = a;
 }
 p->trackList->append(l);
}
