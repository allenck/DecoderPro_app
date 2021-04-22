#include "levelxingviewxml.h"
#include "loggerfactory.h"
#include "layouteditor.h"
/**
 * This module handles configuration for display.LevelXing objects for a
 * LayoutEditor.
 *
 * @author David Duchamp Copyright (c) 2007
 * @author George Warner Copyright (c) 2017-2019
 */
///*public*/ class LevelXingViewXml extends AbstractXmlAdapter {

    /*public*/ LevelXingViewXml::LevelXingViewXml(QObject* parent) : AbstractXmlAdapter(parent) {
    }

    /**
     * Default implementation for storing the contents of a LevelXing
     *
     * @param o Object to store, of type LevelXing
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement LevelXingViewXml::store(QObject* o) {


        LevelXingView* lv = (LevelXingView*) o;
        LevelXing* lt = lv->getLevelXing();

        QDomElement element = doc.createElement("levelxing");

        // include attributes
        element.setAttribute("ident", lt->getId());
        if (!lt->getBlockNameAC().isEmpty()) {
            element.setAttribute("blocknameac", lt->getBlockNameAC());
        }
        if (!lt->getBlockNameBD().isEmpty()) {
            element.setAttribute("blocknamebd", lt->getBlockNameBD());
        }
        if (lt->getConnectA() != nullptr) {
            element.setAttribute("connectaname", ((TrackSegment*) lt->getConnectA())->getId());
        }
        if (lt->getConnectB() != nullptr) {
            element.setAttribute("connectbname", ((TrackSegment*) lt->getConnectB())->getId());
        }
        if (lt->getConnectC() != nullptr) {
            element.setAttribute("connectcname", ((TrackSegment*) lt->getConnectC())->getId());
        }
        if (lt->getConnectD() != nullptr) {
            element.setAttribute("connectdname", ((TrackSegment*) lt->getConnectD())->getId());
        }
        if (lv->isHidden()) {
            element.setAttribute("hidden", "yes");
        }
        if (!lt->getSignalAName().isEmpty()) {
            element.setAttribute("signalaname", lt->getSignalAName());
        }
        if (!lt->getSignalBName().isEmpty()) {
            element.setAttribute("signalbname", lt->getSignalBName());
        }
        if (!lt->getSignalCName().isEmpty()) {
            element.setAttribute("signalcname", lt->getSignalCName());
        }
        if (!lt->getSignalDName().isEmpty()) {
            element.setAttribute("signaldname", lt->getSignalDName());
        }
        QPointF coords = lv->getCoordsCenter();
        element.setAttribute("xcen", coords.x());
        element.setAttribute("ycen", coords.y());
        coords = lv->getCoordsA();
        element.setAttribute("xa", coords.x());
        element.setAttribute("ya", coords.y());
        coords = lv->getCoordsB();
        element.setAttribute("xb", coords.x());
        element.setAttribute("yb", coords.y());

        if (!lt->getSignalAMastName().isEmpty()) {
            element.appendChild(doc.createElement("signalAMast").appendChild(doc.createTextNode(lt->getSignalAMastName())));
        }

        if (!lt->getSignalBMastName().isEmpty()) {
            element.appendChild(doc.createElement("signalBMast").appendChild(doc.createTextNode(lt->getSignalBMastName())));
        }
        if (!lt->getSignalCMastName().isEmpty()) {
            element.appendChild(doc.createElement("signalCMast").appendChild(doc.createTextNode(lt->getSignalCMastName())));
        }
        if (!lt->getSignalDMastName().isEmpty()) {
            element.appendChild(doc.createElement("signalDMast").appendChild(doc.createTextNode(lt->getSignalDMastName())));
        }

        if (!lt->getSensorAName().isEmpty()) {
            element.appendChild(doc.createElement("sensorA").appendChild(doc.createTextNode(lt->getSensorAName())));
        }

        if (!lt->getSensorBName().isEmpty()) {
            element.appendChild(doc.createElement("sensorB").appendChild(doc.createTextNode(lt->getSensorBName())));
        }
        if (!lt->getSensorCName().isEmpty()) {
            element.appendChild(doc.createElement("sensorC").appendChild(doc.createTextNode(lt->getSensorCName())));
        }
        if (!lt->getSensorDName().isEmpty()) {
            element.appendChild(doc.createElement("sensorD").appendChild(doc.createTextNode(lt->getSensorDName())));
        }

        element.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml.LevelXingXml"); // temporary // getClass()->getName());
        return element;
    }

    //@Override
    /*public*/ bool LevelXingViewXml::load(QDomElement shared, QDomElement perNode) {
        log->error("Invalid method called");
        return false;
    }

    /**
     * Load, starting with the levelxing element, then all the other data
     *
     * @param QDomElement Top level QDomElement to unpack.
     * @param o       LayoutEditor as an Object
     */
    //@Override
    /*public*/ void LevelXingViewXml::load(QDomElement element, QObject* o) throw (Exception) {
        // create the objects
        LayoutEditor* p = (LayoutEditor*) o;

        // get center point
        QString name = element.attribute("ident");
        double x = 0.0;
        double y = 0.0;
        bool ok;
        try{
            x = element.attribute("xcen").toFloat(&ok);
            if(!ok)throw DataConversionException();
            y = element.attribute("ycen").toFloat(&ok);
            if(!ok)throw DataConversionException();
        } catch (DataConversionException e) {
            log->error("failed to convert levelxing center  attribute");
        }

        // create the new LevelXing
        LevelXing* lt = new LevelXing(name, p);
        LevelXingView* lv = new LevelXingView(lt, QPointF(x, y), p);

        // get remaining attributes
        QString a = element.attribute("blocknameac");
        if (a != nullptr) {
            lt->tLayoutBlockNameAC = a;
        }
        a = element.attribute("blocknamebd");
        if (a != nullptr) {
            lt->tLayoutBlockNameBD = a;
        }
        a = element.attribute("connectaname");
        if (a != nullptr) {
            lt->connectAName = a;
        }
        a = element.attribute("connectbname");
        if (a != nullptr) {
            lt->connectBName = a;
        }
        a = element.attribute("connectcname");
        if (a != nullptr) {
            lt->connectCName = a;
        }
        a = element.attribute("connectdname");
        if (a != nullptr) {
            lt->connectDName = a;
        }
        a = element.attribute("signalaname");
        if (a != nullptr) {
            lt->setSignalAName(a);
        }
        a = element.attribute("signalbname");
        if (a != nullptr) {
            lt->setSignalBName(a);
        }
        a = element.attribute("signalcname");
        if (a != nullptr) {
            lt->setSignalCName(a);
        }
        a = element.attribute("signaldname");
        if (a != nullptr) {
            lt->setSignalDName(a);
        }

        try {
            x = element.attribute("xa").toFloat(&ok);
            if(!ok)throw DataConversionException();
            y = element.attribute("ya").toFloat(&ok);
            if(!ok)throw DataConversionException();
        } catch (DataConversionException e) {
            log->error("failed to convert levelxing a coords attribute");
        }
        lv->setCoordsA( QPointF(x, y));

        try {
            x = element.attribute("xb").toFloat(&ok);
            if(!ok)throw DataConversionException();
            y = element.attribute("yb").toFloat(&ok);
            if(!ok)throw DataConversionException();
        } catch (DataConversionException e) {
            log->error("failed to convert levelxing b coords attribute");
        }
        lv->setCoordsB( QPointF(x, y));

        try {
            lv->setHidden(element.attribute("hidden") == "true");
            if(!ok)throw DataConversionException();
        } catch (DataConversionException e1) {
            log->warn("unable to convert levelxing hidden attribute");
        } catch (NullPointerException e) {  // considered normal if the attribute is not present
        }

        if (element.firstChildElement("signalAMast") != QDomElement()) {
            QString mast = element.firstChildElement("signalAMast").text();
            if (!mast.isNull() && !mast.isEmpty()) {
                lt->setSignalAMast(mast);
            }
        }

        if (element.firstChildElement("signalBMast") != QDomElement()) {
            QString mast = element.firstChildElement("signalBMast").text();
            if (!mast.isNull() && !mast.isEmpty()) {
                lt->setSignalBMast(mast);
            }
        }

        if (element.firstChildElement("signalCMast") != QDomElement()) {
            QString mast = element.firstChildElement("signalCMast").text();
            if (!mast.isNull() && !mast.isEmpty()) {
                lt->setSignalCMast(mast);
            }
        }

        if (element.firstChildElement("signalDMast") != QDomElement()) {
            QString mast = element.firstChildElement("signalDMast").text();
            if (!mast.isNull() && !mast.isEmpty()) {
                lt->setSignalDMast(mast);
            }
        }

        if (element.firstChildElement("sensorA") != QDomElement()) {
            QString sensor = element.firstChildElement("sensorA").text();
            if (!sensor.isNull() && !sensor.isEmpty()) {
                lt->setSensorAName(sensor);
            }
        }

        if (element.firstChildElement("sensorB") != QDomElement()) {
            QString sensor = element.firstChildElement("sensorB").text();
            if (!sensor.isNull() && !sensor.isEmpty()) {
                lt->setSensorBName(sensor);
            }
        }

        if (element.firstChildElement("sensorC") != QDomElement()) {
            QString sensor = element.firstChildElement("sensorC").text();
            if (!sensor.isNull() && !sensor.isEmpty()) {
                lt->setSensorCName(sensor);
            }
        }

        if (element.firstChildElement("sensorD") != QDomElement()) {
            QString sensor = element.firstChildElement("sensorD").text();
            if (!sensor.isNull() && !sensor.isEmpty()) {
                lt->setSensorDName(sensor);
            }
        }

        p->addLayoutTrack(lt, lv);
    }

    /*private*/ /*final*/ /*static*/ Logger* LevelXingViewXml::log = LoggerFactory::getLogger("LevelXingViewXml");
