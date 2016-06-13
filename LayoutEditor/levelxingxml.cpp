#include "levelxingxml.h"
#include "levelxing.h"

LevelXingXml::LevelXingXml(QObject *parent) :
  AbstractXmlAdapter(parent)
{
}

/**
 * This module handles configuration for display.LevelXing objects for a
 * LayoutEditor.
 *
 * @author David Duchamp Copyright (c) 2007
 * @version $Revision: 28771 $
 */
///*public*/ class LevelXingXml extends AbstractXmlAdapter {

///*public*/ LevelXingXml() {
//}

/**
 * Default implementation for storing the contents of a LevelXing
 *
 * @param o Object to store, of type LevelXing
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement LevelXingXml::store(QObject* o) {

    LevelXing* p = (LevelXing*) o;

    QDomElement element = doc.createElement ("levelxing");

    // include attributes
    element.setAttribute("ident", p->getID());
    if (p->getBlockNameAC().length() > 0) {
        element.setAttribute("blocknameac", p->getBlockNameAC());
    }
    if (p->getBlockNameBD().length() > 0) {
        element.setAttribute("blocknamebd", p->getBlockNameBD());
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
    if (p->getSignalAName().length() > 0) {
        element.setAttribute("signalaname", p->getSignalAName());
    }
    if (p->getSignalBName().length() > 0) {
        element.setAttribute("signalbname", p->getSignalBName());
    }
    if (p->getSignalCName().length() > 0) {
        element.setAttribute("signalcname", p->getSignalCName());
    }
    if (p->getSignalDName().length() > 0) {
        element.setAttribute("signaldname", p->getSignalDName());
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

    if (p->getSignalAMastName().length() > 0) {
        element.appendChild(doc.createElement ("signalAMast").appendChild(doc.createTextNode(p->getSignalAMastName())));
    }

    if (p->getSignalBMastName().length() > 0) {
        element.appendChild(doc.createElement ("signalBMast").appendChild(doc.createTextNode(p->getSignalBMastName())));
    }
    if (p->getSignalCMastName().length() > 0) {
        element.appendChild(doc.createElement ("signalCMast").appendChild(doc.createTextNode(p->getSignalCMastName())));
    }
    if (p->getSignalDMastName().length() > 0) {
        element.appendChild(doc.createElement ("signalDMast").appendChild(doc.createTextNode(p->getSignalDMastName())));
    }

    if (p->getSensorAName().length() > 0) {
        element.appendChild(doc.createElement ("sensorA").appendChild(doc.createTextNode(p->getSensorAName())));
    }

    if (p->getSensorBName().length() > 0) {
        element.appendChild(doc.createElement ("sensorB").appendChild(doc.createTextNode(p->getSensorBName())));
    }
    if (p->getSensorCName().length() > 0) {
        element.appendChild(doc.createElement ("sensorC").appendChild(doc.createTextNode(p->getSensorCName())));
    }
    if (p->getSensorDName().length() > 0) {
        element.appendChild(doc.createElement ("sensorD").appendChild(doc.createTextNode(p->getSensorDName())));
    }

    element.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml.LevelXingXml");
    return element;
}

/*public*/ bool LevelXingXml::load(QDomElement /*element*/)  throw (Exception){
    Logger::error("Invalid method called");
    return false;
}

/**
 * Load, starting with the levelxing element, then all the other data
 *
 * @param element Top level QDomElement to unpack.
 * @param o       LayoutEditor as an Object
 */
/*public*/ void LevelXingXml::load(QDomElement element, QObject* o) throw(Exception) {
    // create the objects
    LayoutEditor* p = (LayoutEditor*) o;

    // get center point
    QString name = element.attribute("ident");
    double x = 0.0;
    double y = 0.0;
    try {
        x = element.attribute("xcen").toFloat();
        y = element.attribute("ycen").toFloat();
    } catch (DataConversionException e) {
        Logger::error("failed to convert levelxing center  attribute");
    }

    // create the new LevelXing
    LevelXing* l = new LevelXing(name, QPointF(x, y), p);

    // get remaining attributes
    QString a = element.attribute("blocknameac");
    if (a != NULL) {
        l->tBlockNameAC = a;
    }
    a = element.attribute("blocknamebd");
    if (a != NULL) {
        l->tBlockNameBD = a;
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
    a = element.attribute("signalaname");
    if (a != NULL) {
        l->setSignalAName(a);
    }
    a = element.attribute("signalbname");
    if (a != NULL) {
        l->setSignalBName(a);
    }
    a = element.attribute("signalcname");
    if (a != NULL) {
        l->setSignalCName(a);
    }
    a = element.attribute("signaldname");
    if (a != NULL) {
        l->setSignalDName(a);
    }
    try {
        x = element.attribute("xa").toFloat();
        y = element.attribute("ya").toFloat();
    } catch (DataConversionException e) {
        Logger::error("failed to convert levelxing a coords attribute");
    }
    l->setCoordsA(QPointF(x, y));
    try {
        x = element.attribute("xb").toFloat();
        y = element.attribute("yb").toFloat();
    } catch (DataConversionException e) {
        Logger::error("failed to convert levelxing b coords attribute");
    }
    l->setCoordsB(QPointF(x, y));

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
            l->setSensorAName(sensor);
        }
    }

    if (!element.firstChildElement("sensorB").isNull()) {
        QString sensor = element.firstChildElement("sensorB").text();
        if (sensor != NULL && sensor!=("")) {
            l->setSensorBName(sensor);
        }
    }

    if (!element.firstChildElement("sensorC").isNull()) {
        QString sensor = element.firstChildElement("sensorC").text();
        if (sensor != NULL && sensor!=("")) {
            l->setSensorCName(sensor);
        }
    }

    if (!element.firstChildElement("sensorD").isNull()) {
        QString sensor = element.firstChildElement("sensorD").text();
        if (sensor != NULL && sensor!=("")) {
            l->setSensorDName(sensor);
        }
    }

    p->xingList->append(l);
}

