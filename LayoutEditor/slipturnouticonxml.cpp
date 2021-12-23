#include "slipturnouticonxml.h"
#include "slipturnouticon.h"
#include "editor.h"

SlipTurnoutIconXml::SlipTurnoutIconXml(QObject *parent) :
    PositionableLabelXml(parent)
{
    log = new Logger("SlipTurnoutIconXml");
}
/**
 * Handle configuration for display.TurnoutIcon objects.
 *
 * Based upon the TurnoutIconXml by Bob Jacobsen
 * @author Kevin Dickerson Copyright: Copyright (c) 2010
 * @version $Revision: 17977 $
 */
///*public*/ class SlipTurnoutIconXml extends PositionableLabelXml {

///*public*/ SlipTurnoutIconXml() {
//}

/**
 * Default implementation for storing the contents of a
 * TurnoutIcon
 * @param o Object to store, of type TurnoutIcon
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement SlipTurnoutIconXml::store(QObject* o) {

    SlipTurnoutIcon* p = (SlipTurnoutIcon*)o;
    if (!p->isActive()) return QDomElement();  // if flagged as inactive, don't store

    QDomElement element = doc.createElement("slipturnouticon");
    //element.setAttribute("turnoutEast", p.getNamedTurnout(SlipTurnoutIcon.WEST).getName());
    //element.setAttribute("turnoutWest", p.getNamedTurnout(SlipTurnoutIcon.EAST).getName());
    QDomElement elem;
    element.appendChild(elem = doc.createElement("turnoutEast"));
    elem.appendChild(doc.createTextNode(p->getNamedTurnout(SlipTurnoutIcon::EAST)->getName()));
    element.appendChild(elem = doc.createElement("turnoutWest"));
    elem.appendChild(doc.createTextNode(p->getNamedTurnout(SlipTurnoutIcon::WEST)->getName()));

    switch(p->getTurnoutType())
    {
    case SlipTurnoutIcon::DOUBLESLIP :
     element.appendChild(storeIcon("lowerWestToLowerEast", p->getLowerWestToLowerEastIcon(),p->getLWLEText()));
     element.appendChild(storeIcon("upperWestToUpperEast", p->getUpperWestToUpperEastIcon(),p->getUWUEText()));
     element.setAttribute("turnoutType", "doubleSlip");
     break;
    case SlipTurnoutIcon::SINGLESLIP:
     element.appendChild(storeIcon("lowerWestToLowerEast", p->getLowerWestToLowerEastIcon(),p->getLWLEText()));
     element.setAttribute("turnoutType", "singleSlip");
     element.setAttribute("singleSlipRoute", p->getSingleSlipRoute()?"upperWestToUpperEast":"lowerWestToLowerEast");
     break;
    case SlipTurnoutIcon::THREEWAY:
     element.appendChild(storeIcon("lowerWestToLowerEast", p->getLowerWestToLowerEastIcon(),p->getLWLEText()));
     element.setAttribute("turnoutType", "threeWay");
     element.setAttribute("firstTurnoutExit", p->getSingleSlipRoute()?"upper":"lower");
     break;
    case SlipTurnoutIcon::SCISSOR:
     if (!p->getSingleSlipRoute())
     {
      QDomElement elem;
      element.appendChild(elem = doc.createElement("turnoutLowerEast"));
      elem.appendChild(doc.createTextNode(p->getNamedTurnout(SlipTurnoutIcon::LOWEREAST)->getName()));
      element.appendChild(elem = doc.createElement("turnoutLowerWest"));
      elem.appendChild(doc.createTextNode(p->getNamedTurnout(SlipTurnoutIcon::LOWERWEST)->getName()));
     }
     element.appendChild(storeIcon("lowerWestToLowerEast", p->getLowerWestToLowerEastIcon(),p->getLWLEText()));
     element.setAttribute("turnoutType", "scissor");
    }

    storeCommonAttributes((Positionable*)p, element);

    // include contents
    element.setAttribute("tristate", p->getTristate()?"true":"false");
    //element.setAttribute("turnoutType", p.getTurnoutType()?"double":"single");

    // new style
    element.appendChild(storeIcon("lowerWestToUpperEast", p->getLowerWestToUpperEastIcon(), p->getLWUEText()));
    element.appendChild(storeIcon("upperWestToLowerEast", p->getUpperWestToLowerEastIcon(), p->getUWLEText()));
    element.appendChild(PositionableLabelXml::storeIcon("unknown", p->getUnknownIcon()));
    element.appendChild(PositionableLabelXml::storeIcon("inconsistent", p->getInconsistentIcon()));

    element.setAttribute("class", "jmri.jmrit.display.configurexml.SlipTurnoutIconXml");

    return element;
}

QDomElement SlipTurnoutIconXml::storeIcon(QString elemName, NamedIcon* icon, QString text){
    QDomElement element = PositionableLabelXml::storeIcon(elemName, icon);
    QDomElement e1;
    element.appendChild(e1=doc.createElement("text"));
    e1.appendChild(doc.createTextNode(text));
    return element;
}

/*public*/ bool SlipTurnoutIconXml::load(QDomElement element) throw (Exception){
    log->error("Invalid method called");
    return false;
}



/**
 * Create a PositionableLabel, then add to a target JLayeredPane
 * @param element Top level QDomElement to unpack.
 * @param o  Editor as an Object
 */
//@SuppressWarnings("NULL")
/*public*/ void SlipTurnoutIconXml::load(QDomElement element, QObject* o) throw (Exception)
{
 // create the objects
 Editor* p = (Editor*)o;

 SlipTurnoutIcon* l = new SlipTurnoutIcon(p);
 int rotation = 0;
 try
 {
  QString a = element.attribute("rotate");
  rotation = a.toInt();
 } catch (DataConversionException* e)
 {}
 catch ( NullPointerException e)
 {  // considered normal if the attributes are not present
 }

 QString nameEast = loadTurnout(element, "turnoutEast");
    /*try {
        nameEast=element.attribute("turnoutEast");
    } catch ( NullPointerException e) {
        log.error("incorrect information for turnout; must use turnout name");
        return;
    }*/
 QString nameWest = loadTurnout(element, "turnoutWest");
    /*try {
        nameWest=element.attribute("turnoutWest");
    } catch ( NullPointerException e) {
        log.error("incorrect information for turnout; must use turnout name");
        return;
    }*/

 QString a = element.attribute("turnoutType");
 if (a!=NULL)
 {
  if (a==("doubleSlip"))
  {
   l->setTurnoutType(SlipTurnoutIcon::DOUBLESLIP);
  }
  else if (a==("singleSlip"))
  {
   l->setTurnoutType(SlipTurnoutIcon::SINGLESLIP);
   a = element.attribute("singleSlipRoute");
   if ( (a==NULL) || ((a!=NULL) && a==("upperWestToUpperEast")))
    l->setSingleSlipRoute(true);
   else
    l->setSingleSlipRoute(false);
  }
  else if (a==("threeWay"))
  {
   l->setTurnoutType(SlipTurnoutIcon::THREEWAY);
   a = element.attribute("firstTurnoutExit");
   if ( (a==NULL) || ((a!=NULL) && a==("lower")))
    l->setSingleSlipRoute(false);
   else
    l->setSingleSlipRoute(true);
  }
  else if (a==("scissor"))
  {
   l->setTurnoutType(SlipTurnoutIcon::SCISSOR);
   if(loadTurnout(element, "turnoutLowerWest")==NULL)
    l->setSingleSlipRoute(true);
   else
   {
    //loadTurnout(element, "turnoutLowerEast");
    l->setSingleSlipRoute(false);
    l->setTurnout(loadTurnout(element, "turnoutLowerEast"), SlipTurnoutIcon::LOWEREAST);
    l->setTurnout(loadTurnout(element, "turnoutLowerWest"), SlipTurnoutIcon::LOWERWEST);
   }
  }
 }
 loadTurnoutIcon("lowerWestToUpperEast", rotation, l, element, p);
 loadTurnoutIcon("upperWestToLowerEast", rotation, l, element, p);
 switch(l->getTurnoutType())
 {
 case SlipTurnoutIcon::DOUBLESLIP :
  loadTurnoutIcon("lowerWestToLowerEast", rotation, l, element, p);
  loadTurnoutIcon("upperWestToUpperEast", rotation, l, element, p);
  break;
 default :
  loadTurnoutIcon("lowerWestToLowerEast", rotation, l, element, p);
  break;
 }

 loadTurnoutIcon("unknown", rotation, l, element, p);
 loadTurnoutIcon("inconsistent", rotation, l, element, p);

 a = element.attribute("tristate");
 if ( (a==NULL) || ((a!=NULL) && a==("true")))
  l->setTristate(true);
 else
  l->setTristate(false);

 l->setTurnout(nameEast, SlipTurnoutIcon::EAST);
 l->setTurnout(nameWest, SlipTurnoutIcon::WEST);

 // p->putItem((Positionable*)l);
 // load individual item's option settings after editor has set its global settings
 loadCommonAttributes((Positionable*)l, Editor::TURNOUTS, element);
 p->putItem((Positionable*)l);
}

/*private*/ QString SlipTurnoutIconXml::loadTurnout(QDomElement element, QString turn)
{
 if (!element.isNull())
 {
  QDomElement e = element.firstChildElement(turn);
  if (!e.isNull())
   return e.text();
 }
 return "";
}

/*private*/ void SlipTurnoutIconXml::loadTurnoutIcon(QString state, int rotation, SlipTurnoutIcon* l,
                             QDomElement element, Editor* ed)
{
 NamedIcon* icon = loadIcon(l, state, element, "SlipTurnout \""+l->getNameString()+"\" icon \""+state+"\" ", ed);
 QString textValue = NULL;

 if (icon!=NULL)
 {
  if(state==("lowerWestToUpperEast")) l->setLowerWestToUpperEastIcon(icon);
  else if (state==("upperWestToLowerEast")) l->setUpperWestToLowerEastIcon(icon);
  else if (state==("lowerWestToLowerEast")) l->setLowerWestToLowerEastIcon(icon);
  else if (state==("upperWestToUpperEast")) l->setUpperWestToUpperEastIcon(icon);
  else if (state==("unknown")) l->setUnknownIcon(icon);
  else if (state==("inconsistent")) l->setInconsistentIcon(icon);
 }
 else
 {
  return;
 }
 QDomElement elem = element.firstChildElement(state);
 if (!elem.isNull())
 {
  QDomElement e = elem.firstChildElement("text");
  if (!e.isNull())
   textValue = e.text();
 }
 if (textValue!=NULL)
 {
  if(state==("lowerWestToUpperEast")) l->setLWUEText(textValue);
  else if (state==("upperWestToLowerEast")) l->setUWLEText(textValue);
  else if (state==("lowerWestToLowerEast")) l->setLWLEText(textValue);
  else if (state==("upperWestToUpperEast")) l->setUWUEText(textValue);
 }
}
