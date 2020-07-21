#include "layoutslipxml.h"
#include "layoutslip.h"
#include "tracksegment.h"
#include "layouteditor.h"

LayoutSlipXml::LayoutSlipXml(QObject *parent) :
  AbstractXmlAdapter(parent)
{
}
#if 1
/**
 * This module handles configuration for display.LayoutSlip objects for a
 * LayoutEditor.
 *
 * @author David Duchamp Copyright (c) 2007
 * @version $Revision: 17977 $
 */
///*public*/ class LayoutSlipXml extends AbstractXmlAdapter {

//    /*public*/ LayoutSlipXml() {
//    }

/**
 * Default implementation for storing the contents of a LayoutSlip
 *
 * @param o Object to store, of type LayoutSlip
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement LayoutSlipXml::store(QObject* o)
{
 LayoutSlip* p = (LayoutSlip*) o;

 QDomElement element = doc.createElement("layoutSlip");

 // include attributes
 element.setAttribute("ident", p->getName());

 element.setAttribute("slipType", p->getSlipType());
 if (p->getBlockName().length() > 0)
 {
  element.setAttribute("blockname", p->getBlockName());
 }

 if (p->getConnectA() != NULL)
 {
  element.setAttribute("connectaname", ((TrackSegment*) p->getConnectA())->getID());
 }
 if (p->getConnectB() != NULL)
 {
  element.setAttribute("connectbname", ((TrackSegment*) p->getConnectB())->getID());
 }
 if (p->getConnectC() != NULL)
 {
  element.setAttribute("connectcname", ((TrackSegment*) p->getConnectC())->getID());
 }
 if (p->getConnectD() != NULL)
 {
  element.setAttribute("connectdname", ((TrackSegment*) p->getConnectD())->getID());
 }
 if (p->getSignalA1Name().length() > 0)
 {
  //element.appendChild(doc.createElement("signala1name").appendChild(doc.createTextNode(p->getSignalA1Name())));
  QDomElement signalname = doc.createElement("signala1name");
  signalname.appendChild(doc.createTextNode(p->getSignalA1Name()));
  element.appendChild(signalname);
 }
 if (p->getSignalB1Name().length() > 0)
 {
  //element.appendChild(doc.createElement("signalb1name").appendChild(doc.createTextNode(p->getSignalB1Name())));
  QDomElement signalname = doc.createElement("signalb1name");
  signalname.appendChild(doc.createTextNode(p->getSignalB1Name()));
  element.appendChild(signalname);
 }
 if (p->getSignalC1Name().length() > 0)
 {
  //element.appendChild(doc.createElement("signalc1name").appendChild(doc.createTextNode(p->getSignalC1Name())));
  QDomElement signalname = doc.createElement("signalc1name");
  signalname.appendChild(doc.createTextNode(p->getSignalC1Name()));
  element.appendChild(signalname);
 }
 if (p->getSignalD1Name().length() > 0)
 {
  //element.appendChild(doc.createElement("signald1name").appendChild(doc.createTextNode(p->getSignalD1Name())));
  QDomElement signalname = doc.createElement("signald1name");
  signalname.appendChild(doc.createTextNode(p->getSignalD1Name()));
  element.appendChild(signalname);
 }
 if (p->getSignalA2Name().length() > 0)
 {
  //element.appendChild(doc.createElement("signala2name").appendChild(doc.createTextNode(p->getSignalA2Name())));
  QDomElement signalname = doc.createElement("signala2name");
  signalname.appendChild(doc.createTextNode(p->getSignalA2Name()));
  element.appendChild(signalname);
 }
 if (p->getSignalB2Name().length() > 0)
 {
  //element.appendChild(doc.createElement("signalb2name").appendChild(doc.createTextNode(p->getSignalB2Name())));
  QDomElement signalname = doc.createElement("signalb2name");
  signalname.appendChild(doc.createTextNode(p->getSignalB2Name()));
  element.appendChild(signalname);
 }
 if (p->getSignalC2Name().length() > 0)
 {
  //element.appendChild(doc.createElement("signalc2name").appendChild(doc.createTextNode(p->getSignalC2Name())));
  QDomElement signalname = doc.createElement("signalc2name");
  signalname.appendChild(doc.createTextNode(p->getSignalC2Name()));
  element.appendChild(signalname);
 }
 if (p->getSignalD2Name().length() > 0)
 {
  //element.appendChild(doc.createElement("signald2name").appendChild(doc.createTextNode(p->getSignalD2Name())));
  QDomElement signalname = doc.createElement("signald2name");
  signalname.appendChild(doc.createTextNode(p->getSignalD2Name()));
  element.appendChild(signalname);
 }
 QPointF coords = p->getCoordsCenter();
 element.setAttribute("xcen", coords.x());
 element.setAttribute("ycen", coords.y());
 coords = p->getCoordsA();
 element.setAttribute("xa", coords.x());
 element.setAttribute("ya", coords.y());
 coords = p->getCoordsB();
 element.setAttribute("xb", coords.x());
 element.setAttribute("yb", coords.y());

 if (p->getSignalAMastName().length() > 0)
 {
  //element.appendChild(doc.createElement("signalAMast").appendChild(doc.createTextNode(p->getSignalAMastName())));
  QDomElement signalMast = doc.createElement("signalAMast");
  signalMast.appendChild(doc.createTextNode(p->getSignalAMastName()));
  element.appendChild(signalMast);
 }

 if (p->getSignalBMastName().length() > 0)
 {
//  element.appendChild(doc.createElement("signalBMast").appendChild(doc.createTextNode(p->getSignalBMastName())));
  QDomElement signalMast = doc.createElement("signalBMast");
  signalMast.appendChild(doc.createTextNode(p->getSignalBMastName()));
  element.appendChild(signalMast);
 }
 if (p->getSignalCMastName().length() > 0)
 {
//  element.appendChild(doc.createElement("signalCMast").appendChild(doc.createTextNode(p->getSignalCMastName())));
  QDomElement signalMast = doc.createElement("signalCMast");
  signalMast.appendChild(doc.createTextNode(p->getSignalCMastName()));
  element.appendChild(signalMast);
 }
 if (p->getSignalDMastName().length() > 0)
 {
//  element.appendChild(doc.createElement("signalDMast").appendChild(doc.createTextNode(p->getSignalDMastName())));
  QDomElement signalMast = doc.createElement("signalDMast");
  signalMast.appendChild(doc.createTextNode(p->getSignalDMastName()));
  element.appendChild(signalMast);
 }

 if (p->getSensorAName().length() > 0)
 {
//  element.appendChild(doc.createElement("sensorA").appendChild(doc.createTextNode(p->getSensorAName())));
  QDomElement sensor = doc.createElement("sensorA");
  sensor.appendChild(doc.createTextNode(p->getSensorAName()));
  element.appendChild(sensor);
 }

 if (p->getSensorBName().length() > 0)
 {
//  element.appendChild(doc.createElement("sensorB").appendChild(doc.createTextNode(p->getSensorBName())));
  QDomElement sensor = doc.createElement("sensorB");
  sensor.appendChild(doc.createTextNode(p->getSensorBName()));
  element.appendChild(sensor);
 }
 if (p->getSensorCName().length() > 0)
 {
//  element.appendChild(doc.createElement("sensorC").appendChild(doc.createTextNode(p->getSensorCName())));
  QDomElement sensor = doc.createElement("sensorC");
  sensor.appendChild(doc.createTextNode(p->getSensorCName()));
  element.appendChild(sensor);
 }
 if (p->getSensorDName().length() > 0)
 {
//  element.appendChild(doc.createElement("sensorD").appendChild(doc.createTextNode(p->getSensorDName())));
  QDomElement sensor = doc.createElement("sensorD");
  sensor.appendChild(doc.createTextNode(p->getSensorDName()));
  element.appendChild(sensor);
 }

 if (p->getTurnoutName().length() > 0)
 {
  QDomElement turnout = doc.createElement("turnout");
  turnout.appendChild(doc.createTextNode(p->getTurnoutName()));
  element.appendChild(turnout);
 }

 if (p->getTurnoutBName().length() > 0)
 {
  QDomElement turnout = doc.createElement("turnoutB");
  turnout.appendChild(doc.createTextNode(p->getTurnoutBName()));
  element.appendChild(turnout);

 }
 QDomElement states = doc.createElement("states");
 QDomElement state = doc.createElement("A-C");
 //state.appendChild(doc.createElement("turnout").appendChild(doc.createTextNode(QString::number(p->getTurnoutState(LayoutSlip::STATE_AC)))));
 QDomElement turnout = doc.createElement("turnout");
 turnout.appendChild(doc.createTextNode(QString::number(p->getTurnoutState(LayoutSlip::STATE_AC))));
 state.appendChild(turnout);
// state.appendChild(doc.createElement("turnoutB").appendChild(doc.createTextNode(QString::number(p->getTurnoutBState(LayoutSlip::STATE_AC)))));
 QDomElement turnoutB = doc.createElement("turnoutB");
 turnoutB.appendChild(doc.createTextNode(QString::number(p->getTurnoutBState(LayoutSlip::STATE_AC))));
 state.appendChild(turnoutB);
 states.appendChild(state);

 state = doc.createElement("A-D");
 //state.appendChild(doc.createElement("turnout").appendChild(doc.createTextNode(QString::number(p->getTurnoutState(LayoutSlip::STATE_AD)))));
 turnout = doc.createElement("turnout");
 turnout.appendChild(doc.createTextNode(QString::number(p->getTurnoutState(LayoutSlip::STATE_AD))));
 state.appendChild(turnout);
 //state.appendChild(doc.createElement("turnoutB").appendChild(doc.createTextNode(QString::number(p->getTurnoutBState(LayoutSlip::STATE_AD)))));
 turnoutB = doc.createElement("turnoutB");
 turnoutB.appendChild(doc.createTextNode(QString::number(p->getTurnoutBState(LayoutSlip::STATE_AD))));
 state.appendChild(turnoutB);
 states.appendChild(state);

 state = doc.createElement("B-D");
 //state.appendChild(doc.createElement("turnout").appendChild(doc.createTextNode(QString::number(p->getTurnoutState(LayoutSlip::STATE_BD)))));
 turnout = doc.createElement("turnout");
 turnout.appendChild(doc.createTextNode(QString::number(p->getTurnoutState(LayoutSlip::STATE_BD))));
 state.appendChild(turnout);
 //state.appendChild(doc.createElement("turnoutB").appendChild(doc.createTextNode(QString::number(p->getTurnoutBState(LayoutSlip::STATE_BD)))));
 turnoutB = doc.createElement("turnoutB");
 turnoutB.appendChild(doc.createTextNode(QString::number(p->getTurnoutBState(LayoutSlip::STATE_BD))));
 state.appendChild(turnoutB);
 states.appendChild(state);

 if (p->getSlipType() == LayoutSlip::DOUBLE_SLIP)
 {
  state = doc.createElement("B-C");
  //state.appendChild(doc.createElement("turnout").appendChild(doc.createTextNode(QString::number(p->getTurnoutState(LayoutSlip::STATE_BC)))));
  QDomElement turnout = doc.createElement("turnout");
  turnout.appendChild(doc.createTextNode(QString::number(p->getTurnoutState(LayoutSlip::STATE_BC))));
  state.appendChild(turnout);
  //state.appendChild(doc.createElement("turnoutB").appendChild(doc.createTextNode(QString::number(p->getTurnoutBState(LayoutSlip::STATE_BC)))));
  QDomElement turnoutB = doc.createElement("turnoutB");
  turnoutB.appendChild(doc.createTextNode(QString::number(p->getTurnoutBState(LayoutSlip::STATE_BC))));
  state.appendChild(turnoutB);
  states.appendChild(state);
 }
 element.appendChild(states);
 element.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml.LayoutSlipXml");
 return element;
}

/*public*/ bool LayoutSlipXml::load(QDomElement /*element*/) throw (Exception) {
    Logger::error("Invalid method called");
    return false;
}

/**
 * Load, starting with the levelxing element, then all the other data
 *
 * @param element Top level QDomElement to unpack.
 * @param o       LayoutEditor as an Object
 */
/*public*/ void LayoutSlipXml::load(QDomElement element, QObject* o) throw (Exception)
{
 // create the objects
 LayoutEditor* p = (LayoutEditor*) o;

 // get center point
 QString name = element.attribute("ident");
 double x = 0.0;
 double y = 0.0;
 bool b1, b2;
 //try {
 x = element.attribute("xcen").toFloat(&b1);
 y = element.attribute("ycen").toFloat(&b2);
 //} catch (DataConversionException e) {
 if(!b1 || !b2)
 {
  Logger::error("failed to convert layoutslip center  attribute");
 }
 int type = LayoutSlip::SINGLE_SLIP;
 //try {
 type = element.attribute("slipType").toInt(&b1);
 //} catch (DataConversionException e) {
 if(!b1)
 {
  Logger::error("failed to convert layoutslip type attribute");
 }

 // create the new LayoutSlip
 LayoutSlip* l = new LayoutSlip(name,  QPointF(x, y), 0.0, p, type);

 // get remaining attributes
 QString a = element.attribute("blockname");
 if (a != NULL)
 {
  l->tBlockAName = a;
 }

 a = element.attribute("connectaname");
 if (a != NULL)
 {
  l->connectAName = a;
 }
 a = element.attribute("connectbname");
 if (a != NULL)
 {
  l->connectBName = a;
 }
 a = element.attribute("connectcname");
 if (a != NULL)
 {
  l->connectCName = a;
 }
 a = element.attribute("connectdname");
 if (a != NULL)
 {
  l->connectDName = a;
 }

 l->setSignalA1Name(getElement(element, "signala1name"));
 l->setSignalB1Name(getElement(element, "signalb1name"));
 l->setSignalC1Name(getElement(element, "signalc1name"));
 l->setSignalD1Name(getElement(element, "signald1name"));

 l->setSignalA2Name(getElement(element, "signala2name"));
 l->setSignalB2Name(getElement(element, "signalb2name"));
 l->setSignalC2Name(getElement(element, "signalc2name"));
 l->setSignalD2Name(getElement(element, "signald2name"));

 //try {
 x = element.attribute("xa").toFloat(&b1);
 y = element.attribute("ya").toFloat(&b2);
 //} catch (DataConversionException e) {
 if(!b1 || !b2)
 {
  Logger::error("failed to convert levelxing a coords attribute");
 }
 l->setCoordsA( QPointF(x, y));
 //try {
     x = element.attribute("xb").toFloat(&b1);
     y = element.attribute("yb").toFloat(&b2);
 //} catch (DataConversionException e) {
 if(!b1 || !b2)
 {
  Logger::error("failed to convert levelxing b coords attribute");
 }
 l->setCoordsB( QPointF(x, y));

 l->setSignalAMast(getElement(element, "signalAMast"));
 l->setSignalBMast(getElement(element, "signalBMast"));
 l->setSignalCMast(getElement(element, "signalCMast"));
 l->setSignalDMast(getElement(element, "signalDMast"));

 l->setSensorA(getElement(element, "sensorA"));
 l->setSensorB(getElement(element, "sensorB"));
 l->setSensorC(getElement(element, "sensorC"));
 l->setSensorD(getElement(element, "sensorD"));

 l->setTurnout(getElement(element, "turnout"));
 l->setTurnoutB(getElement(element, "turnoutB"));

 if (!element.firstChildElement("states") .isNull())
 {
  QDomElement state = element.firstChildElement("states");
  if (!state.firstChildElement("A-C").isNull())
  {
   QDomElement ac = state.firstChildElement("A-C");
   l->setTurnoutStates(LayoutSlip::STATE_AC,
           ac.firstChildElement("turnout").text(),
           ac.firstChildElement("turnoutB").text());
  }
  if (!state.firstChildElement("A-D").isNull())
  {
   QDomElement ad = state.firstChildElement("A-D");
   l->setTurnoutStates(LayoutSlip::STATE_AD,
           ad.firstChildElement("turnout").text(),
           ad.firstChildElement("turnoutB").text());
  }
  if (!state.firstChildElement("B-D").isNull())
  {
   QDomElement bd = state.firstChildElement("B-D");
   l->setTurnoutStates(LayoutSlip::STATE_BD,
           bd.firstChildElement("turnout").text(),
           bd.firstChildElement("turnoutB").text());
  }
  if (!state.firstChildElement("B-C").isNull())
  {
   QDomElement bc = state.firstChildElement("B-C");
   l->setTurnoutStates(LayoutSlip::STATE_BC,
           bc.firstChildElement("turnout").text(),
           bc.firstChildElement("turnoutB").text());
  }
 }
 p->addLayoutTrack(l);
}

QString LayoutSlipXml::getElement(QDomElement el, QString child) {
 if (!el.firstChildElement(child).isNull()) {
        return el.firstChildElement(child).text();
    }
    return "";
}
#endif
