#include "layoutturnoutviewxml.h"
#include "layoutturnoutview.h"
#include "layoutturnout.h"
#include "tracksegment.h"
#include "loggerfactory.h"
#include "layoutrhturnout.h"
#include "layoutrhturnoutview.h"
#include "layoutlhturnout.h"
#include "layoutlhturnoutview.h"
#include "layoutwyeview.h"
#include "layoutdoublexoverview.h"
#include "layoutrhxoverview.h"
#include "layoutlhxoverview.h"
#include "layoutdoubleslipview.h"
#include "layoutsingleslipview.h"
#include "layouteditor.h"

/**
 * This module handles configuration for display.LayoutTurnout objects for a
 * LayoutEditor.
 *
 * @author David Duchamp Copyright (c) 2007
 * @author George Warner Copyright (c) 2017-2019
 * @author Bob Jacobsen Copyright (c) 2020
 */
///*public*/ class LayoutTurnoutViewXml extends AbstractXmlAdapter {

//    static final EnumIO<LayoutTurnout.LinkType> linkEnumMap = new EnumIoNamesNumbers<>(LayoutTurnout.LinkType.class);
//    static final EnumIO<LayoutTurnout.TurnoutType> tTypeEnumMap = new EnumIoNamesNumbers<>(LayoutTurnout.TurnoutType.class);

    /*public*/ LayoutTurnoutViewXml::LayoutTurnoutViewXml(QObject *parent) {
    }

    /*protected*/ void LayoutTurnoutViewXml::addClass(QDomElement element) {
        element.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml->LayoutTurnoutXml");
    }

    /**
     * Default implementation for storing the contents of a LayoutTurnout
     *
     * @param o Object to store, of type LayoutTurnout
     * @return Element containing the complete info
     */
    //@Override
    /*public*/ QDomElement LayoutTurnoutViewXml::store(QObject* o) {

        LayoutTurnoutView* pv = (LayoutTurnoutView*) o;
        LayoutTurnout* p = pv->getLayoutTurnout();

        QDomElement element = doc.createElement("layoutturnout");

        // include attributes
        element.setAttribute("ident", p->getName());
        //element.setAttribute("type", tTypeEnumMap->outputFromEnum(p->getTurnoutType()));
        QMetaEnum mett = QMetaEnum::fromType<LayoutTurnout::TurnoutType>();
        element.setAttribute("type", mett.valueToKey(p->getTurnoutType()));

        element.setAttribute("hidden", (pv->isHidden() ? "yes" : "no"));
        element.setAttribute("disabled", (p->isDisabled() ? "yes" : "no"));
        element.setAttribute("disableWhenOccupied", (p->isDisabledWhenOccupied() ? "yes" : "no"));

        element.setAttribute("continuing", p->getContinuingSense());

        QPointF coords = pv->getCoordsCenter();
        element.setAttribute("xcen", coords.x());
        element.setAttribute("ycen", coords.y());

        coords = pv->getCoordsA();
        element.setAttribute("xa", coords.x());
        element.setAttribute("ya", coords.y());

        coords = pv->getCoordsB();
        element.setAttribute("xb", coords.x());
        element.setAttribute("yb", coords.y());

        coords = pv->getCoordsC();
        element.setAttribute("xc", coords.x());
        element.setAttribute("yc", coords.y());

        coords = pv->getCoordsD();
        element.setAttribute("xd", coords.x());
        element.setAttribute("yd", coords.y());

        element.setAttribute("ver", p->getVersion());

        addClass(element);

        if (!p->getTurnoutName().isEmpty()) {
            element.setAttribute("turnoutname", p->getTurnoutName());
        }
        if (!p->getSecondTurnoutName().isEmpty()) {
            element.setAttribute("secondturnoutname", p->getSecondTurnoutName());
            if (p->isSecondTurnoutInverted()) {
                element.setAttribute("secondturnoutinverted", "true");
            }
        }

        if (!p->getLinkedTurnoutName().isEmpty()) {
            element.setAttribute("linkedturnoutname", p->getLinkedTurnoutName());
            //element.setAttribute("linktype", linkEnumMap->outputFromEnum(p->getLinkType()));
            QMetaEnum melt = QMetaEnum::fromType<LayoutTurnout::LinkType>();
            element.setAttribute("linktype", melt.valueToKey(p->getLinkType()));
        }

        if (!p->getBlockName().isEmpty()) {
            element.setAttribute("blockname", p->getBlockName());
        }
        // Only save these if they're different from block A
        if (!p->getBlockBName().isEmpty() && (p->getBlockBName() != (p->getBlockName()))) {
            element.setAttribute("blockbname", p->getBlockBName());
        }
        if (!p->getBlockCName().isEmpty() && (p->getBlockCName() != (p->getBlockName()))) {
            element.setAttribute("blockcname", p->getBlockCName());
        }
        if (!p->getBlockDName().isEmpty() && (p->getBlockDName() != (p->getBlockName()))) {
            element.setAttribute("blockdname", p->getBlockDName());
        }

        if (p->getConnectA() != nullptr) {
            element.setAttribute("connectaname", ((TrackSegment*) p->getConnectA())->getId());
        }
        if (p->getConnectB() != nullptr) {
            element.setAttribute("connectbname", ((TrackSegment*) p->getConnectB())->getId());
        }
        if (p->getConnectC() != nullptr) {
            element.setAttribute("connectcname", ((TrackSegment*) p->getConnectC())->getId());
        }
        if (p->getConnectD() != nullptr) {
            element.setAttribute("connectdname", ((TrackSegment*) p->getConnectD())->getId());
        }

        if (!p->getSignalA1Name().isEmpty()) {
            element.setAttribute("signala1name", p->getSignalA1Name());
        }
        if (!p->getSignalA2Name().isEmpty()) {
            element.setAttribute("signala2name", p->getSignalA2Name());
        }
        if (!p->getSignalA3Name().isEmpty()) {
            element.setAttribute("signala3name", p->getSignalA3Name());
        }
        if (!p->getSignalB1Name().isEmpty()) {
            element.setAttribute("signalb1name", p->getSignalB1Name());
        }
        if (!p->getSignalB2Name().isEmpty()) {
            element.setAttribute("signalb2name", p->getSignalB2Name());
        }
        if (!p->getSignalC1Name().isEmpty()) {
            element.setAttribute("signalc1name", p->getSignalC1Name());
        }
        if (!p->getSignalC2Name().isEmpty()) {
            element.setAttribute("signalc2name", p->getSignalC2Name());
        }
        if (!p->getSignalD1Name().isEmpty()) {
            element.setAttribute("signald1name", p->getSignalD1Name());
        }
        if (!p->getSignalD2Name().isEmpty()) {
            element.setAttribute("signald2name", p->getSignalD2Name());
        }

        if (!p->getSignalAMastName().isEmpty()) {
            element.appendChild(doc.createElement("signalAMast").appendChild(doc.createTextNode(p->getSignalAMastName())));
        }

        if (!p->getSignalBMastName().isEmpty()) {
            element.appendChild(doc.createElement("signalBMast").appendChild(doc.createTextNode(p->getSignalBMastName())));
        }
        if (!p->getSignalCMastName().isEmpty()) {
            element.appendChild(doc.createElement("signalCMast").appendChild(doc.createTextNode(p->getSignalCMastName())));
        }
        if (!p->getSignalDMastName().isEmpty()) {
            element.appendChild(doc.createElement("signalDMast").appendChild(doc.createTextNode(p->getSignalDMastName())));
        }

        if (!p->getSensorAName().isEmpty()) {
            element.appendChild(doc.createElement("sensorA").appendChild(doc.createTextNode(p->getSensorAName())));
        }

        if (!p->getSensorBName().isEmpty()) {
            element.appendChild(doc.createElement("sensorB").appendChild(doc.createTextNode(p->getSensorBName())));
        }
        if (!p->getSensorCName().isEmpty()) {
            element.appendChild(doc.createElement("sensorC").appendChild(doc.createTextNode(p->getSensorCName())));
        }
        if (!p->getSensorDName().isEmpty()) {
            element.appendChild(doc.createElement("sensorD").appendChild(doc.createTextNode(p->getSensorDName())));
        }
        return element;
    }

    //@Override
    /*public*/ bool LayoutTurnoutViewXml::load(QDomElement shared, QDomElement perNode) {
        log->error("Invalid method called");
        return false;
    }

    /**
     * Load, starting with the levelxing element, then all the other data
     *
     * @param element Top level Element to unpack.
     * @param o       LayoutEditor as an Object
     */
    //@Override
    /*public*/ void LayoutTurnoutViewXml::load(QDomElement element, QObject* o) throw (Exception) {
        // create the objects
        LayoutEditor* p = (LayoutEditor*) o;

        // get center point
        QString name = element.attribute("ident");
        double x = 0.0;
        double y = 0.0;
        LayoutTurnout::TurnoutType type = LayoutTurnout::TurnoutType::NONE;
        bool ok;
        try {
            x = element.attribute("xcen").toFloat(&ok); if(!ok) throw DataConversionException();;
            y = element.attribute("ycen").toFloat(&ok); if(!ok) throw DataConversionException();;
            //type = tTypeEnumMap->inputFromAttribute(element.attribute("type"));
            QMetaEnum mett = QMetaEnum::fromType<LayoutTurnout::TurnoutType>();
            QString ts = element.attribute("type");
            type = (LayoutTurnout::TurnoutType)mett.keyToValue(ts.toLocal8Bit(), &ok);
            if(!ok)
            {
             type  = (LayoutTurnout::TurnoutType)ts.toInt(&ok);
             if(!ok) throw DataConversionException();
            }
        } catch (DataConversionException e) {
            log->error("failed to convert layoutturnout attribute");
        }

        int version = 1;
        try {
            if (element.attribute("ver", "1") != nullptr) {
                version = element.attribute("ver").toInt(&ok); if(!ok) throw DataConversionException();;
            }
        } catch (DataConversionException e) {
            log->error("failed to convert layoutturnout version attribute");
        }

        // create the new LayoutTurnout of the correct type
        LayoutTurnoutView* lv;
        LayoutTurnout* l;

        switch(type)
        {
         case LayoutTurnout::RH_TURNOUT :
         {
          LayoutRHTurnout* lrht = new LayoutRHTurnout(name, p, version);
          l = lrht;
          lv = new LayoutRHTurnoutView(lrht, QPointF(x, y), 0.0, 1.0, 1.0, p);
          break;
         }
         case LayoutTurnout::LH_TURNOUT :
         {
          LayoutLHTurnout* llht = new LayoutLHTurnout(name, p, version);
          l = llht;
          lv = new LayoutLHTurnoutView(llht, QPointF(x, y), 0.0, 1.0, 1.0, p);
          break;
         }
         case LayoutTurnout::WYE_TURNOUT :
         {
          LayoutWye* lwt = new LayoutWye(name, p, version);
          l = lwt;
          lv = new LayoutWyeView(lwt, QPointF(x, y), 0.0, 1.0, 1.0, p);
          break;
         }
         case LayoutTurnout::DOUBLE_XOVER :
         {
          LayoutDoubleXOver* ldx = new LayoutDoubleXOver(name, p, version);
          l = ldx;
          lv = new LayoutDoubleXOverView(ldx, QPointF(x, y), 0.0, 1.0, 1.0, p);
          break;
         }
         case LayoutTurnout::RH_XOVER :
         {
          LayoutRHXOver* lrx = new LayoutRHXOver(name, p, version);
          l = lrx;
          lv = new LayoutRHXOverView(lrx, QPointF(x, y), 0.0, 1.0, 1.0, p);
          break;
         }
         case LayoutTurnout::LH_XOVER :
         {
          LayoutLHXOver* llx = new LayoutLHXOver(name, p, version);
          l = llx;
          lv = new LayoutLHXOverView(llx, QPointF(x, y), 0.0, 1.0, 1.0, p);
          break;
         }
         case LayoutTurnout::DOUBLE_SLIP :
         {
             LayoutDoubleSlip* lds = new LayoutDoubleSlip(name, p);
             l = lds;
             lv = new LayoutDoubleSlipView(lds, QPointF(x, y), 0.0, p);
             log->error(tr("Found DOUBLE_SLIP in LayoutTrack ctor for element %1").arg(name));
             break;
         }
         case LayoutTurnout::SINGLE_SLIP :
         {
             LayoutSingleSlip* lss = new LayoutSingleSlip(name, p);
             l = lss;
             lv = new LayoutSingleSlipView(lss, QPointF(x, y), 0.0, p);
             log->error(tr("Found SINGLE_SLIP in LayoutTrack ctor for element %1").arg(name));
             break;
         }
         default:
             log->error(tr("can't create LayoutTrack %1 with type $2").arg(name, type));
             return; // without creating
        }

        p->addLayoutTrack(l, lv);

        // get remaining attributes
        QString a = element.attribute("turnoutname");
        if (a != "") {
            l->setTurnout(a);
        }
        a = element.attribute("secondturnoutname");
        if (a != nullptr) {
            l->setSecondTurnout(a);
            try {
                l->setSecondTurnoutInverted(element.attribute("secondturnoutinverted")=="true");
            } catch (DataConversionException e1) {
                log->warn("unable to convert layout turnout secondturnoutinverted attribute");
            } catch (NullPointerException e) {  // considered normal if the attribute is not present
            }
        }

        a = element.attribute("blockname");
        if (a != nullptr) {
            l->tBlockAName = a;
        }
        a = element.attribute("blockbname");
        if (a != nullptr) {
            l->tBlockBName = a;
        }
        a = element.attribute("blockcname");
        if (a != nullptr) {
            l->tBlockCName = a;
        }
        a = element.attribute("blockdname");
        if (a != nullptr) {
            l->tBlockDName = a;
        }

        a = element.attribute("connectaname");
        if (a != nullptr) {
            l->connectAName = a;
        }
        a = element.attribute("connectbname");
        if (a != nullptr) {
            l->connectBName = a;
        }
        a = element.attribute("connectcname");
        if (a != nullptr) {
            l->connectCName = a;
        }
        a = element.attribute("connectdname");
        if (a != nullptr) {
            l->connectDName = a;
        }

        a = element.attribute("signala1name");
        if (a != nullptr) {
            l->setSignalA1Name(a);
        }
        a = element.attribute("signala2name");
        if (a != nullptr) {
            l->setSignalA2Name(a);
        }
        a = element.attribute("signala3name");
        if (a != nullptr) {
            l->setSignalA3Name(a);
        }
        a = element.attribute("signalb1name");
        if (a != nullptr) {
            l->setSignalB1Name(a);
        }
        a = element.attribute("signalb2name");
        if (a != nullptr) {
            l->setSignalB2Name(a);
        }
        a = element.attribute("signalc1name");
        if (a != nullptr) {
            l->setSignalC1Name(a);
        }
        a = element.attribute("signalc2name");
        if (a != nullptr) {
            l->setSignalC2Name(a);
        }
        a = element.attribute("signald1name");
        if (a != nullptr) {
            l->setSignalD1Name(a);
        }
        a = element.attribute("signald2name");
        if (a != nullptr) {
            l->setSignalD2Name(a);
        }
        a = element.attribute("linkedturnoutname");
        if (a != nullptr) {
            l->linkedTurnoutName = a;
            //l->linkType = linkEnumMap->inputFromAttribute(element.attribute("linktype"));
            QMetaEnum melt = QMetaEnum::fromType<LayoutTurnout::LinkType>();
            l->linkType = (LayoutTurnout::LinkType)melt.keyToValue(element.attribute("linktype").toLocal8Bit());
        }
        a = element.attribute("continuing");
        if (a != nullptr) {
            int continuing = Turnout::CLOSED;
            try {
                continuing = element.attribute("continuing").toInt(&ok); if(!ok) throw DataConversionException();;
            } catch (DataConversionException e) {
                log->error("failed to convert continuingsense attribute");
            }
            l->setContinuingSense(continuing);
        }
        try {
            l->setDisabled(element.attribute("disabled")=="true");
        } catch (DataConversionException e1) {
            log->warn("unable to convert layout turnout disabled attribute");
        } catch (NullPointerException e) {  // considered normal if the attribute is not present
        }
        try {
            l->setDisableWhenOccupied(element.attribute("disableWhenOccupied")=="true");
        } catch (DataConversionException e1) {
            log->warn("unable to convert layout turnout disableWhenOccupied attribute");
        } catch (NullPointerException e) {  // considered normal if the attribute is not present
        }
        try {
            lv->setHidden(element.attribute("hidden")== "true");
        } catch (DataConversionException e1) {
            log->warn("unable to convert layout turnout hidden attribute");
        } catch (NullPointerException e) {  // considered normal if the attribute is not present
        }

        if (version == 2) {
            try {
                x = element.attribute("xa").toFloat(&ok); if(!ok) throw DataConversionException();;
                y = element.attribute("ya").toFloat(&ok); if(!ok) throw DataConversionException();;
                lv->setCoordsA(QPointF(x, y));
            } catch (DataConversionException e) {
                log->error("failed to convert layoutturnout b coords attribute");
            } catch (NullPointerException e) {
                //can be ignored as panel file may not support method
            }
        }
        try {
            x = element.attribute("xb").toFloat(&ok); if(!ok) throw DataConversionException();;
            y = element.attribute("yb").toFloat(&ok); if(!ok) throw DataConversionException();;
            lv->setCoordsB(QPointF(x, y));
        } catch (DataConversionException e) {
            log->error("failed to convert layoutturnout b coords attribute");
        }
        try {
            x = element.attribute("xc").toFloat(&ok); if(!ok) throw DataConversionException();;
            y = element.attribute("yc").toFloat(&ok); if(!ok) throw DataConversionException();;
            lv->setCoordsC(QPointF(x, y));
        } catch (DataConversionException e) {
            log->error("failed to convert layoutturnout c coords attribute");
        }
        if (version == 2) {
            try {
                x = element.attribute("xd").toFloat(&ok); if(!ok) throw DataConversionException();;
                y = element.attribute("yd").toFloat(&ok); if(!ok) throw DataConversionException();;
                lv->setCoordsD(QPointF(x, y));
            } catch (DataConversionException e) {
                log->error("failed to convert layoutturnout c coords attribute");
            } catch (NullPointerException e) {
                //can be ignored as panel file may not support method
            }
        }

        l->setSignalAMast(getElement(element, "signalAMast"));
        l->setSignalBMast(getElement(element, "signalBMast"));
        l->setSignalCMast(getElement(element, "signalCMast"));
        l->setSignalDMast(getElement(element, "signalDMast"));

        l->setSensorA(getElement(element, "sensorA"));
        l->setSensorB(getElement(element, "sensorB"));
        l->setSensorC(getElement(element, "sensorC"));
        l->setSensorD(getElement(element, "sensorD"));
    }

    QString LayoutTurnoutViewXml::getElement(QDomElement el, QString child) {
        if (el.firstChildElement(child) != QDomElement()) {
            return el.firstChildElement(child).text();
        }
        return "";
    }

    /*private*/ /*final*/ /*static*/ Logger* LayoutTurnoutViewXml::log = LoggerFactory::getLogger("LayoutTurnoutViewXml");
