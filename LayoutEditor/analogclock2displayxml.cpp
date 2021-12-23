#include "analogclock2displayxml.h"
#include "editor.h"
#include "analogclock2display.h"

AnalogClock2DisplayXml::AnalogClock2DisplayXml(QObject *parent) :
    AbstractXmlAdapter(parent)
{
 log = new Logger("AnalogClock2DisplayXml");
}
AnalogClock2DisplayXml::~AnalogClock2DisplayXml()
{
 delete log;
}

/**
 * Handle configuration for display.AnalogClock2Display objects.
 *
 * @author  Howard G. Penny  Copyright (c) 2005
 * @version $Revision: 17977 $
 */
///*public*/ class AnalogClock2DisplayXml
//    extends AbstractXmlAdapter {

//    /*public*/ AnalogClock2DisplayXml() {
//    }

/**
 * Default implementation for storing the contents of an
 * AnalogClock2Display
 * @param o Object to store, of type TurnoutIcon
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement AnalogClock2DisplayXml::store(QObject* o)
{

 AnalogClock2Display* p = (AnalogClock2Display*) o;
 if (!p->isActive())
 {
  return QDomElement(); // if flagged as inactive, don't store
 }

 QDomElement element = doc.createElement("fastclock");

 // include contents
 if (p->getId() != "") element.setAttribute("id", p->getId());
 element.setAttribute("x", p->getX());
 element.setAttribute("y", p->getY());
 element.setAttribute("scale",  p->getScale());
 QString link = p->getURL();
 if (link != "" && link.trimmed().length() > 0) {
  element.setAttribute("link", link);
}

 element.setAttribute("class",
        "jmri.jmrit.display.configurexml.AnalogClock2DisplayXml");

 return element;
}

/*public*/ bool AnalogClock2DisplayXml::load(QDomElement /*element*/) throw (Exception){
    log->error("Invalid method called");
    return false;
}

/**
 * Create an AnalogClock2Display, then add to a target JLayeredPane
 * @param element Top level QDomElement to unpack.
 * @param o an Editor as an Object
 */
/*public*/ void AnalogClock2DisplayXml::load(QDomElement element, QObject* o) throw (Exception)
{
 // get object class and create the clock object
 Editor* ed = (Editor*)o;
 AnalogClock2Display* l = new AnalogClock2Display(ed);

 // find coordinates
 int x = 0;
 int y = 0;
 double scale = 1.0;
// try {
 bool bOk=true;
 bool bOk1;
 if (element.attribute("id") != "") {
  try {
      l->setId(element.attribute("id"));
  } catch (Positionable::DuplicateIdException* e) {
      throw  JmriConfigureXmlException("Positionable id is not unique", e);
  }
 }
 x = element.attribute("x").toInt(&bOk1);
 if(!bOk1) bOk = false;
 y = element.attribute("y").toInt(&bOk1);
 if(!bOk1) bOk = false;
 if (element.attribute("scale")!=NULL)
 {
   scale = element.attribute("scale").toDouble(&bOk1);;
   if(!bOk1) bOk = false;
 }
//    }
//  catch (DataConversionException* e) {
 if(!bOk)
 {
  log->error("failed to convert positional attribute");
 }
 if (element.attribute("link") != "") {
     l->setULRL(element.attribute("link"));
 }
 l->setOpaque(false);
 l->update();
 l->setLocation(x, y);
 if (scale != 1.0 && 10.0>scale && scale>0.1) { l->setScale(scale);  }

 // add the clock to the panel
 l->setDisplayLevel(Editor::CLOCK);
 ed->putItem((Positionable*)l);
 l->paint(ed->getTargetPanel());
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger
//.getLogger(AnalogClock2DisplayXml.class.getName());
//}
