#include "layoutslipviewxml.h"
#include "loggerfactory.h"
#include "layoutslipview.h"
#include "layoutslip.h"
#include "tracksegment.h"
#include "layoutdoubleslipview.h"
#include "layoutsingleslipview.h"
#include "layouteditor.h"

/**
 * This module handles configuration for display.LayoutSlipView objects for a
 * LayoutEditor.
 *
 * @author David Duchamp Copyright (c) 2007
 * @author George Warner Copyright (c) 2017-2018
 * @author Bob Jacobsen Copyright (c) 2020
 */
///*public*/ class LayoutSlipViewXml extends AbstractXmlAdapter {

    /*public*/ LayoutSlipViewXml::LayoutSlipViewXml(QObject* parent) {
    }

    //final static EnumIO<LayoutSlip->TurnoutType> tTypeEnumMap = new EnumIoNamesNumbers<>(LayoutSlip->TurnoutType.class);

    /*protected*/ void LayoutSlipViewXml::addClass(QDomElement element) {
        element.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml->LayoutSlipXml");
    }

    /**
     * Default implementation for storing the contents of a LayoutSlip
     *
     * @param o Object to store, of type LayoutSlip
     * @return Element containing the complete info
     */
    //@Override
    /*public*/ QDomElement LayoutSlipViewXml::store(QObject* o) {

        LayoutSlipView* pv = (LayoutSlipView*) o;
        LayoutSlip* p = pv->getSlip();

        QDomElement element = doc.createElement("layoutSlip");

        // include attributes
        element.setAttribute("ident", p->getName());
        QMetaEnum metaEnum = QMetaEnum::fromType<LayoutTurnout::TurnoutType>();
        //element.setAttribute("slipType", tTypeEnumMap->outputFromEnum(p->getTurnoutType()));
        element.setAttribute("slipType", metaEnum.valueToKey(p->getTurnoutType()));

        element.setAttribute("hidden", (pv->isHidden() ? "yes" : "no"));
        element.setAttribute("disabled", (p->isDisabled() ? "yes" : "no"));
        element.setAttribute("disableWhenOccupied", (p->isDisabledWhenOccupied() ? "yes" : "no"));

        QPointF coords = pv->getCoordsCenter();
        element.setAttribute("xcen", coords.x());
        element.setAttribute("ycen", coords.y());
        coords = pv->getCoordsA();
        element.setAttribute("xa", coords.x());
        element.setAttribute("ya", coords.y());
        coords = pv->getCoordsB();
        element.setAttribute("xb", coords.x());
        element.setAttribute("yb", coords.y());

        if (!p->getTurnoutName().isEmpty()) {
            element.appendChild(doc.createElement("turnout").appendChild(doc.createTextNode(p->getTurnoutName())));
        }

        if (!p->getTurnoutBName().isEmpty()) {
            element.appendChild(doc.createElement("turnoutB").appendChild(doc.createTextNode(p->getTurnoutBName())));
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

        if (p->getConnectA() !=  nullptr) {
            element.setAttribute("connectaname", ((TrackSegment*) p->getConnectA())->getId());
        }
        if (p->getConnectB() !=  nullptr) {
            element.setAttribute("connectbname", ((TrackSegment*) p->getConnectB())->getId());
        }
        if (p->getConnectC() !=  nullptr) {
            element.setAttribute("connectcname", ((TrackSegment*) p->getConnectC())->getId());
        }
        if (p->getConnectD() !=  nullptr) {
            element.setAttribute("connectdname", ((TrackSegment*) p->getConnectD())->getId());
        }

        if (!p->getSignalA1Name().isEmpty()) {
            element.appendChild(doc.createElement("signala1name").appendChild(doc.createTextNode(p->getSignalA1Name())));
        }
        if (!p->getSignalB1Name().isEmpty()) {
            element.appendChild(doc.createElement("signalb1name").appendChild(doc.createTextNode(p->getSignalB1Name())));
        }
        if (!p->getSignalC1Name().isEmpty()) {
            element.appendChild(doc.createElement("signalc1name").appendChild(doc.createTextNode(p->getSignalC1Name())));
        }
        if (!p->getSignalD1Name().isEmpty()) {
            element.appendChild(doc.createElement("signald1name").appendChild(doc.createTextNode(p->getSignalD1Name())));
        }
        if (!p->getSignalA2Name().isEmpty()) {
            element.appendChild(doc.createElement("signala2name").appendChild(doc.createTextNode(p->getSignalA2Name())));
        }
        if (!p->getSignalB2Name().isEmpty()) {
            element.appendChild(doc.createElement("signalb2name").appendChild(doc.createTextNode(p->getSignalB2Name())));
        }
        if (!p->getSignalC2Name().isEmpty()) {
            element.appendChild(doc.createElement("signalc2name").appendChild(doc.createTextNode(p->getSignalC2Name())));
        }
        if (!p->getSignalD2Name().isEmpty()) {
            element.appendChild(doc.createElement("signald2name").appendChild(doc.createTextNode(p->getSignalD2Name())));
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

        QDomElement states = doc.createElement("states");
        QDomElement state = doc.createElement("A-C");
        QMetaEnum me = QMetaEnum::fromType<LayoutSlip::TurnoutType>();
        state.appendChild(doc.createElement("turnout").appendChild(doc.createTextNode(me.valueToKey(p->getTurnoutState(LayoutSlip::STATE_AC)))));
        state.appendChild(doc.createElement("turnoutB").appendChild(doc.createTextNode(me.valueToKey(p->getTurnoutBState(LayoutSlip::STATE_AC)))));
        states.appendChild(state);

        state = doc.createElement("A-D");
        state.appendChild(doc.createElement("turnout").appendChild(doc.createTextNode(me.valueToKey(p->getTurnoutState(LayoutSlip::STATE_AD)))));
        state.appendChild(doc.createElement("turnoutB").appendChild(doc.createTextNode(me.valueToKey(p->getTurnoutBState(LayoutSlip::STATE_AD)))));
        states.appendChild(state);

        state = doc.createElement("B-D");
        state.appendChild(doc.createElement("turnout").appendChild(doc.createTextNode(me.valueToKey(p->getTurnoutState(LayoutSlip::STATE_BD)))));
        state.appendChild(doc.createElement("turnoutB").appendChild(doc.createTextNode(me.valueToKey(p->getTurnoutBState(LayoutSlip::STATE_BD)))));
        states.appendChild(state);

        if (p->getSlipType() == LayoutSlip::TurnoutType::DOUBLE_SLIP) {
            state = doc.createElement("B-C");
            state.appendChild(doc.createElement("turnout").appendChild(doc.createTextNode(me.valueToKey(p->getTurnoutState(LayoutSlip::STATE_BC)))));
            state.appendChild(doc.createElement("turnoutB").appendChild(doc.createTextNode(me.valueToKey(p->getTurnoutBState(LayoutSlip::STATE_BC)))));
            states.appendChild(state);
        }
        element.appendChild(states);
        addClass(element);
        return element;
    }

    //@Override
    /*public*/ bool LayoutSlipViewXml::load(QDomElement shared, QDomElement perNode) {
        log->error("Invalid method called");
        return false;
    }

    /**
     * Load, starting with the LayoutSlip element, then all the other data
     *
     * @param element Top level Element to unpack.
     * @param o       LayoutEditor as an Object
     */
    //@Override
    /*public*/ void LayoutSlipViewXml::load(QDomElement element, QObject* o) throw (Exception){
        // create the objects
        LayoutEditor* p = (LayoutEditor*) o;

        // get center point
        QString name = element.attribute("ident");
        double x = 0.0;
        double y = 0.0;
        bool ok;
        try {
            x = element.attribute("xcen").toFloat(&ok); if(!ok) throw DataConversionException();;
            y = element.attribute("ycen").toFloat(&ok); if(!ok) throw DataConversionException();;
        } catch (DataConversionException e) {
            log->error("failed to convert layoutslip center  attribute");
        }
        LayoutSlip::TurnoutType type;
        QMetaEnum metaEnum = QMetaEnum::fromType<LayoutTurnout::TurnoutType>();
        try{
//        LayoutSlip::TurnoutType type =
//                tTypeEnumMap->inputFromAttribute(element.attribute("slipType"));

         QString ts;
          type = (LayoutSlip::TurnoutType)metaEnum.keyToValue((ts = element.attribute("slipType")).toLocal8Bit(),&ok);
         if(!ok)
         {
           type = (LayoutSlip::TurnoutType)ts.toInt(&ok);
          if(!ok)
           throw DataConversionException();
         }
        }
        catch (DataConversionException e) {
            log->error("failed to convert layoutslip hitpoint type  attribute");
        }

        // create the new LayoutSlip
        LayoutSlip* l;
        LayoutSlipView* lv;

        switch(type) {
            case LayoutSlip::DOUBLE_SLIP :
        {
                LayoutDoubleSlip* lds = new LayoutDoubleSlip(name, p);
                l = lds;
                lv = new LayoutDoubleSlipView(lds, QPointF(x, y), 0.0, p);
                break;
        }
            case LayoutSlip::SINGLE_SLIP :
        {
                LayoutSingleSlip* lss = new LayoutSingleSlip(name, p);
                l = lss;
                lv = new LayoutSingleSlipView(lss, QPointF(x, y), 0.0, p);
                break;
        }
            default:
                log->error(tr("can't create slip %1 with type %2").arg(name, metaEnum.valueToKey( type)));
                return; // without creating
        }

        p->addLayoutTrack(l, lv);

        // get remaining attributes
        l->setTurnout(getElement(element, "turnout"));
        l->setTurnoutB(getElement(element, "turnoutB"));

        QString a = element.attribute("blockname");
        if (a !=  nullptr) {
            l->tBlockAName = a;
        }
        a = element.attribute("blockbname");
        if (a !=  nullptr) {
            l->tBlockBName = a;
        }
        a = element.attribute("blockcname");
        if (a !=  nullptr) {
            l->tBlockCName = a;
        }
        a = element.attribute("blockdname");
        if (a !=  nullptr) {
            l->tBlockDName = a;
        }

        a = element.attribute("connectaname");
        if (a !=  nullptr) {
            l->connectAName = a;
        }
        a = element.attribute("connectbname");
        if (a !=  nullptr) {
            l->connectBName = a;
        }
        a = element.attribute("connectcname");
        if (a !=  nullptr) {
            l->connectCName = a;
        }
        a = element.attribute("connectdname");
        if (a !=  nullptr) {
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

        try {
            l->setDisabled(element.attribute("disabled") == "true");
        } catch (DataConversionException e1) {
            log->warn("unable to convert layout turnout disabled attribute");
        } catch (NullPointerException e) {  // considered normal if the attribute is not present
        }
        try {
            l->setDisableWhenOccupied(element.attribute("disableWhenOccupied")== "true");
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

        try {
            x = element.attribute("xa").toFloat(&ok); if(!ok) throw DataConversionException();;
            y = element.attribute("ya").toFloat(&ok); if(!ok) throw DataConversionException();;
            lv->setCoordsA(QPointF(x, y));
        } catch (DataConversionException e) {
            log->error("failed to convert LayoutSlip a coords attribute");
        }
        try {
            x = element.attribute("xb").toFloat(&ok); if(!ok) throw DataConversionException();;
            y = element.attribute("yb").toFloat(&ok); if(!ok) throw DataConversionException();;
            lv->setCoordsB(QPointF(x, y));
        } catch (DataConversionException e) {
            log->error("failed to convert LayoutSlip b coords attribute");
        }

        l->setSignalAMast(getElement(element, "signalAMast"));
        l->setSignalBMast(getElement(element, "signalBMast"));
        l->setSignalCMast(getElement(element, "signalCMast"));
        l->setSignalDMast(getElement(element, "signalDMast"));

        l->setSensorA(getElement(element, "sensorA"));
        l->setSensorB(getElement(element, "sensorB"));
        l->setSensorC(getElement(element, "sensorC"));
        l->setSensorD(getElement(element, "sensorD"));

        if (element.firstChildElement("states") !=  QDomElement()) {
            QDomElement state = element.firstChildElement("states");
            if (state.firstChildElement("A-C") !=  QDomElement()) {
                QDomElement ac = state.firstChildElement("A-C");
                l->setTurnoutStates(LayoutSlip::STATE_AC,
                        ac.firstChildElement("turnout").text(),
                        ac.firstChildElement("turnoutB").text());
            }
            if (state.firstChildElement("A-D") !=  QDomElement()) {
                QDomElement ad = state.firstChildElement("A-D");
                l->setTurnoutStates(LayoutSlip::STATE_AD,
                        ad.firstChildElement("turnout").text(),
                        ad.firstChildElement("turnoutB").text());
            }
            if (state.firstChildElement("B-D") !=  QDomElement()) {
                QDomElement bd = state.firstChildElement("B-D");
                l->setTurnoutStates(LayoutSlip::STATE_BD,
                        bd.firstChildElement("turnout").text(),
                        bd.firstChildElement("turnoutB").text());
            }
            if (state.firstChildElement("B-C") !=  QDomElement()) {
                QDomElement bc = state.firstChildElement("B-C");
                l->setTurnoutStates(LayoutSlip::STATE_BC,
                        bc.firstChildElement("turnout").text(),
                        bc.firstChildElement("turnoutB").text());
            }
        }
    }

    QString LayoutSlipViewXml::getElement(QDomElement el, QString child) {
        if (el.firstChildElement(child) !=  QDomElement()) {
            return el.firstChildElement(child).text();
        }
        return "";
    }

    /*private*/ /*final*/ /*static*/ Logger* LayoutSlipViewXml::log = LoggerFactory::getLogger("LayoutSlipViewXml");
