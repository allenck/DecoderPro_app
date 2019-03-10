#include "layoutturnoutxml.h"
#include "layoutturnout.h"
#include "tracksegment.h"

LayoutTurnoutXml::LayoutTurnoutXml(QObject *parent) :
  AbstractXmlAdapter(parent)
{
}
/**
 * This module handles configuration for display.LayoutTurnout objects for a
 * LayoutEditor.
 *
 * @author David Duchamp Copyright (c) 2007
 * @version $Revision: 29001 $
 */
// /*public*/ class LayoutTurnoutXml extends AbstractXmlAdapter {

///*public*/ LayoutTurnoutXml() {
//}

/**
 * Default implementation for storing the contents of a LayoutTurnout
 *
 * @param o Object to store, of type LayoutTurnout
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement LayoutTurnoutXml::store(QObject* o) {

    LayoutTurnout* p = (LayoutTurnout*) o;

    QDomElement element = doc.createElement("layoutturnout");

    // include attributes
    element.setAttribute("ident", p->getName());
    if (p->getTurnoutName().length() > 0) {
        element.setAttribute("turnoutname", p->getTurnoutName());
    }
    if (p->getSecondTurnoutName().length() > 0) {
        element.setAttribute("secondturnoutname", p->getSecondTurnoutName());
    }
    if (p->getBlockName().length() > 0) {
        element.setAttribute("blockname", p->getBlockName());
    }
    if (p->getBlockBName().length() > 0) {
        element.setAttribute("blockbname", p->getBlockBName());
    }
    if (p->getBlockCName().length() > 0) {
        element.setAttribute("blockcname", p->getBlockCName());
    }
    if (p->getBlockDName().length() > 0) {
        element.setAttribute("blockdname", p->getBlockDName());
    }
    element.setAttribute("type",  p->getTurnoutType());
    if (p->getHidden()) {
        element.setAttribute("hidden",  (p->getHidden() ? "yes" : "no"));
    }
    if (p->getConnectA() != NULL) {
        element.setAttribute("connectaname", ((TrackSegment*) p->getConnectA())->getID());
    }
    if (p->getConnectB() != NULL) {
        element.setAttribute("connectbname", ((TrackSegment*) p->getConnectB())->getID());
    }
    if (p->getConnectC() != NULL) {
        element.setAttribute("connectcname", ((TrackSegment*) p->getConnectC())->getID());
    }
    if (p->getConnectD() != NULL) {
        element.setAttribute("connectdname", ((TrackSegment*) p->getConnectD())->getID());
    }
    if (p->getSignalA1Name().length() > 0) {
        element.setAttribute("signala1name", p->getSignalA1Name());
    }
    if (p->getSignalA2Name().length() > 0) {
        element.setAttribute("signala2name", p->getSignalA2Name());
    }
    if (p->getSignalA3Name().length() > 0) {
        element.setAttribute("signala3name", p->getSignalA3Name());
    }
    if (p->getSignalB1Name().length() > 0) {
        element.setAttribute("signalb1name", p->getSignalB1Name());
    }
    if (p->getSignalB2Name().length() > 0) {
        element.setAttribute("signalb2name", p->getSignalB2Name());
    }
    if (p->getSignalC1Name().length() > 0) {
        element.setAttribute("signalc1name", p->getSignalC1Name());
    }
    if (p->getSignalC2Name().length() > 0) {
        element.setAttribute("signalc2name", p->getSignalC2Name());
    }
    if (p->getSignalD1Name().length() > 0) {
        element.setAttribute("signald1name", p->getSignalD1Name());
    }
    if (p->getSignalD2Name().length() > 0) {
        element.setAttribute("signald2name", p->getSignalD2Name());
    }
    if (p->getLinkedTurnoutName().length() > 0) {
        element.setAttribute("linkedturnoutname", p->getLinkedTurnoutName());
        element.setAttribute("linktype",  p->getLinkType());
    }

    if (p->getSignalAMastName().length() > 0)
    {
      //element.appendChild(doc.createElement("signalAMast").appendChild(doc.createTextNode(p->getSignalAMastName())));
     QDomElement signalMast = doc.createElement("signalAMast");
     signalMast.appendChild(doc.createTextNode(p->getSignalAMastName()));
     element.appendChild(signalMast);
    }

    if (p->getSignalBMastName().length() > 0) {
        //element.appendChild(doc.createElement("signalBMast").appendChild(doc.createTextNode(p->getSignalBMastName())));
     QDomElement signalMast = doc.createElement("signalBMast");
     signalMast.appendChild(doc.createTextNode(p->getSignalBMastName()));
     element.appendChild(signalMast);
    }
    if (p->getSignalCMastName().length() > 0) {
        //element.appendChild(doc.createElement("signalCMast").appendChild(doc.createTextNode(p->getSignalCMastName())));
     QDomElement signalMast = doc.createElement("signalCMast");
     signalMast.appendChild(doc.createTextNode(p->getSignalCMastName()));
     element.appendChild(signalMast);
    }
    if (p->getSignalDMastName().length() > 0) {
       // element.appendChild(doc.createElement("signalDMast").appendChild(doc.createTextNode(p->getSignalDMastName())));
     QDomElement signalMast = doc.createElement("signalDMast");
     signalMast.appendChild(doc.createTextNode(p->getSignalDMastName()));
     element.appendChild(signalMast);

    }

    if (p->getSensorAName().length() > 0)
    {
     //element.appendChild(doc.createElement("sensorA").appendChild(doc.createTextNode(p->getSensorAName())));
     QDomElement sensor = doc.createElement("sensorA");
     sensor.appendChild(doc.createTextNode(p->getSensorAName()));
     element.appendChild(sensor);
    }

    if (p->getSensorBName().length() > 0) {
        //element.appendChild(doc.createElement("sensorB").appendChild(doc.createTextNode(p->getSensorBName())));
     QDomElement sensor = doc.createElement("sensorB");
     sensor.appendChild(doc.createTextNode(p->getSensorBName()));
     element.appendChild(sensor);
    }
    if (p->getSensorCName().length() > 0) {
        //element.appendChild(doc.createElement("sensorC").appendChild(doc.createTextNode(p->getSensorCName())));
     QDomElement sensor = doc.createElement("sensorC");
     sensor.appendChild(doc.createTextNode(p->getSensorCName()));
     element.appendChild(sensor);
    }
    if (p->getSensorDName().length() > 0) {
        //element.appendChild(doc.createElement("sensorD").appendChild(doc.createTextNode(p->getSensorDName())));
     QDomElement sensor = doc.createElement("sensorD");
     sensor.appendChild(doc.createTextNode(p->getSensorDName()));
     element.appendChild(sensor);
    }

    element.setAttribute("continuing",  p->getContinuingSense());
    element.setAttribute("disabled",  (p->isDisabled() ? "yes" : "no"));
    element.setAttribute("disableWhenOccupied",  (p->isDisabledWhenOccupied() ? "yes" : "no"));
    QPointF coords = p->getCoordsCenter();
    element.setAttribute("xcen",  coords.x());
    element.setAttribute("ycen",  coords.y());
    coords = p->getCoordsA();
    element.setAttribute("xa",  coords.x());
    element.setAttribute("ya",  coords.y());
    coords = p->getCoordsB();
    element.setAttribute("xb",  coords.x());
    element.setAttribute("yb",  coords.y());
    coords = p->getCoordsC();
    element.setAttribute("xc",  coords.x());
    element.setAttribute("yc",  coords.y());
    coords = p->getCoordsD();
    element.setAttribute("xd",  coords.x());
    element.setAttribute("yd",  coords.y());
    element.setAttribute("ver",  p->getVersion());
    element.setAttribute("class", "jmri.jmrit.display.configurexml.LayoutTurnoutXml");
    return element;
}

/*public*/ bool LayoutTurnoutXml::load(QDomElement /*element*/) throw (Exception){
    Logger::error("Invalid method called");
    return false;
}

/**
 * Load, starting with the levelxing element, then all the other data
 *
 * @param element Top level QDomElement to unpack.
 * @param o       LayoutEditor as an Object
 */
/*public*/ void LayoutTurnoutXml::load(QDomElement element, QObject* o) throw (Exception){
    // create the objects
   LayoutEditor* p = (LayoutEditor*) o;

    // get center point
    QString name = element.attribute("ident");
    double x = 0.0;
    double y = 0.0;
    int tType = LayoutTurnout::RH_TURNOUT;
    try {
        x = element.attribute("xcen").toFloat();
        y = element.attribute("ycen").toFloat();
        tType = element.attribute("type").toInt();
    } catch (DataConversionException e) {
        Logger::error("failed to convert layoutturnout attribute");
    }

    int version = 1;
    bool bOk;
        version = element.attribute("ver").toInt(&bOk);
    if(!bOk) {
        Logger::error("failed to convert layoutturnout b coords attribute");

    }
//    } catch (NullPointerException e) {
//        //can be ignored as panel file may not support method
//    }

    // create the new LayoutTurnout
    LayoutTurnout* l = new LayoutTurnout(name, tType,
            QPointF(x, y), 0.0, 1.0, 1.0, p, version);

    // get remaining attributes
    QString a = element.attribute("blockname");
    if (a != NULL) {
        l->tBlockName = a;
    }
    a = element.attribute("blockbname");
    if (a != NULL) {
        l->tBlockBName = a;
    }
    a = element.attribute("blockcname");
    if (a != NULL) {
        l->tBlockCName = a;
    }
    a = element.attribute("blockdname");
    if (a != NULL) {
        l->tBlockDName = a;
    }
    a = element.attribute("turnoutname");
    if (a != NULL) {
        l->tTurnoutName = a;
    }
    a = element.attribute("secondturnoutname");
    if (a != NULL) {
        l->tSecondTurnoutName = a;
    }
    a = element.attribute("connectaname");
    if (a != NULL) {
        l->connectAName = a;
    }
    a = element.attribute("connectbname");
    if (a != NULL) {
        l->connectBName = a;
    }
    a = element.attribute("connectcname");
    if (a != NULL) {
        l->connectCName = a;
    }
    a = element.attribute("connectdname");
    if (a != NULL) {
        l->connectDName = a;
    }
    a = element.attribute("signala1name");
    if (a != NULL) {
        l->setSignalA1Name(a);
    }
    a = element.attribute("signala2name");
    if (a != NULL) {
        l->setSignalA2Name(a);
    }
    a = element.attribute("signala3name");
    if (a != NULL) {
        l->setSignalA3Name(a);
    }
    a = element.attribute("signalb1name");
    if (a != NULL) {
        l->setSignalB1Name(a);
    }
    a = element.attribute("signalb2name");
    if (a != NULL) {
        l->setSignalB2Name(a);
    }
    a = element.attribute("signalc1name");
    if (a != NULL) {
        l->setSignalC1Name(a);
    }
    a = element.attribute("signalc2name");
    if (a != NULL) {
        l->setSignalC2Name(a);
    }
    a = element.attribute("signald1name");
    if (a != NULL) {
        l->setSignalD1Name(a);
    }
    a = element.attribute("signald2name");
    if (a != NULL) {
        l->setSignalD2Name(a);
    }
    a = element.attribute("linkedturnoutname");
    if (a != NULL) {
        l->linkedTurnoutName = a;
        bool bOk;
            l->linkType = element.attribute("linktype").toInt(&bOk);
        if(!bOk) {
            Logger::error("failed to convert linked layout turnout type");
        }
    }
    a = element.attribute("continuing");
    if (a != NULL) {
        int continuing = Turnout::CLOSED;
        bool bOk;
            continuing = element.attribute("continuing").toInt(&bOk);
        if(!bOk) {
            Logger::error("failed to convert continuingsense attribute");
        }
        l->setContinuingSense(continuing);
    }
    bool value = false;
    if ((a = element.attribute("disabled")) != NULL && a==("yes")) {
        value = true;
    }
    l->setDisabled(value);
    value = false;
    if ((a = element.attribute("disableWhenOccupied")) != NULL && a==("yes")) {
        value = true;
    }
    l->setDisableWhenOccupied(value);
    bool hide = false;
    if (element.attribute("hidden") != NULL) {
        if (element.attribute("hidden")==("yes")) {
            hide = true;
        }
    }
    l->setHidden(hide);
    if(version==2){
        try {
            x = element.attribute("xa").toFloat();
            y = element.attribute("ya").toFloat();
            l->setCoordsA(QPointF(x, y));
        } catch (DataConversionException e) {
            Logger::error("failed to convert layoutturnout b coords attribute");
        } catch (NullPointerException e) {
            //can be ignored as panel file may not support method
        }
    }
    try {
        x = element.attribute("xb").toFloat();
        y = element.attribute("yb").toFloat();
    } catch (DataConversionException e) {
        Logger::error("failed to convert layoutturnout b coords attribute");
    }
    l->setCoordsB(QPointF(x, y));
    try {
        x = element.attribute("xc").toFloat();
        y = element.attribute("yc").toFloat();
    } catch (DataConversionException e) {
        Logger::error("failed to convert layoutturnout c coords attribute");
    }
    l->setCoordsC(QPointF(x, y));
    if(version==2){
        try {
            x = element.attribute("xd").toFloat();
            y = element.attribute("yd").toFloat();
            l->setCoordsD(QPointF(x, y));
        } catch (DataConversionException e) {
            Logger::error("failed to convert layoutturnout c coords attribute");
        } catch (NullPointerException e) {
            //can be ignored as panel file may not support method
        }
    }
    if (!element.firstChildElement("signalAMast").isNull()) {
        QString mast = element.firstChildElement("signalAMast").text();
        if (mast != NULL && mast!=("")) {
            l->setSignalAMast(mast);
        }
    }

    if (!element.firstChildElement("signalBMast").isNull()) {
        QString mast = element.firstChildElement("signalBMast").text();
        if (mast != NULL && mast!=("")) {
            l->setSignalBMast(mast);
        }
    }

    if (!element.firstChildElement("signalCMast").isNull()) {
        QString mast = element.firstChildElement("signalCMast").text();
        if (mast != NULL && mast!=("")) {
            l->setSignalCMast(mast);
        }
    }

    if (!element.firstChildElement("signalDMast").isNull()) {
        QString mast = element.firstChildElement("signalDMast").text();
        if (mast != NULL && mast!=("")) {
            l->setSignalDMast(mast);
        }
    }

    if (!element.firstChildElement("sensorA").isNull()) {
        QString sensor = element.firstChildElement("sensorA").text();
        if (sensor != NULL && sensor!=("")) {
            l->setSensorA(sensor);
        }
    }

    if (!element.firstChildElement("sensorB").isNull()) {
        QString sensor = element.firstChildElement("sensorB").text();
        if (sensor != NULL && sensor!=("")) {
            l->setSensorB(sensor);
        }
    }

    if (!element.firstChildElement("sensorC").isNull()) {
        QString sensor = element.firstChildElement("sensorC").text();
        if (sensor != NULL && sensor!=("")) {
            l->setSensorC(sensor);
        }
    }

    if (!element.firstChildElement("sensorD").isNull()) {
        QString sensor = element.firstChildElement("sensorD").text();
        if (sensor != NULL && sensor!=("")) {
            l->setSensorD(sensor);
        }
    }

    p->getLayoutTracks()->append(l);
}

QString LayoutTurnoutXml::getElement(QDomElement el, QString child) {
        if (!el.firstChildElement(child).isNull()) {
            return el.firstChildElement(child).text();
        }
        return "";
    }
