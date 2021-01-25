#include "meterframemanagerxml.h"
#include "meterframemanager.h"
#include "loggerfactory.h"
#include "meterframe.h"
#include "defaultmeter.h"
#include "instancemanager.h"
/**
 * Stores MeterFrames to the panel file.
 * @author Daniel Bergqvist Copyright (c) 2020
 */
// /*public*/ class MeterFrameManagerXml extends jmri.configurexml.AbstractXmlAdapter {

//    /*private*/ EnumIO<MeterFrame::Unit> unitEnumMap = new EnumIoNames<>("MeterFrame.Unit");

    /*public*/ MeterFrameManagerXml::MeterFrameManagerXml(QObject* parent) : AbstractXmlAdapter(parent){
    }

    //@Override
    /*public*/ QDomElement MeterFrameManagerXml::store(QObject* o) {
        QDomElement meterFrames = doc.createElement("meterFrames");
        setStoreElementClass(meterFrames);

        for (MeterFrame* frame : MeterFrameManager::getInstance()->getMeterFrames()) {
            meterFrames.appendChild(storeMeterFrame(frame));
        }

        return meterFrames;
    }

    /*public*/ QDomElement MeterFrameManagerXml::storeMeterFrame(MeterFrame* frame) {
        QDomElement e = doc.createElement("meterFrame");

        QDomElement e2 = doc.createElement("uuid");
        e2.appendChild(doc.createTextNode(frame->getUUID().toString(QUuid::WithoutBraces)));
        e.appendChild(e2);

        e2 = doc.createElement("meter");
        e2.appendChild(doc.createTextNode(((DefaultMeter*)frame->getMeter())->getSystemName()));    // This should be a NamedBeanHandle
        e.appendChild(e2);

        //e.setAttribute("unit", unitEnumMap.outputFromEnum(frame->getUnit()));
        e.setAttribute("unit", frame->getUnit().name);
        e.setAttribute("integer-digits", (frame->getNumIntegerDigits()));
        e.setAttribute("decimal-digits", (frame->getNumDecimalDigits()));
        e.setAttribute("x", (frame->pos().x()));
        e.setAttribute("y", (frame->pos().y()));
        e.setAttribute("width", (frame->width()));
        e.setAttribute("height", (frame->height()));

        return e;
    }

    /**
     * Subclass provides implementation to create the correct top element,
     * including the type information. Default implementation is to use the
     * local class here.
     *
     * @param meterFrames The top-level QDomElement being created
     */
    /*public*/ void MeterFrameManagerXml::setStoreElementClass(QDomElement meterFrames) {
        meterFrames.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.swing.meter.configurexml.MeterFrameManagerXml");  // NOI18N
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool MeterFrameManagerXml::load(QDomElement shared, QDomElement perNode) throw (JmriConfigureXmlException) {
        // Don't create frames if headless
        //if (GraphicsEnvironment.isHeadless()) return true;

        QDomNodeList frames = shared.elementsByTagName("meterFrame");
        for(int i=0; i < frames.count(); i++) {
         QDomElement elem = frames.at(i).toElement();
            QString uuidStr = elem.firstChildElement("uuid").text();
            QString meterSystemName = elem.firstChildElement("meter").text();      // This should be a NamedBeanHandle
            DefaultMeter* meter = (DefaultMeter*)((MeterManager*)InstanceManager::getDefault("MeterManager"))->getBySystemName(meterSystemName);
            QUuid uuid = QUuid::fromString(tr("{%1}").arg(uuidStr));
            MeterFrame* frame = MeterFrameManager::getInstance()->getByUUID(uuid);
            if (frame == nullptr) {
                frame = new MeterFrame(uuid);
                frame->initComponents();
                if(meter)
                 log->error(tr("uuid: %1, meter: %2, meter: %3, systemName: %4")
                           .arg(frame->getUUID().toString())
                           .arg(((DefaultMeter*)meter)->getDisplayName())
                           .arg(((DefaultMeter*)frame->getMeter())->getSystemName())
                           .arg(meterSystemName));
            }
            if (meter != nullptr) frame->setMeter(meter);

            QString a = elem.attribute("unit");
            if (a != "")
             //frame->setUnit(unitEnumMap.inputFromAttribute(a));
             frame->setUnit(MeterFrame::Unit(a));

            frame->setNumIntegerDigits(getAttributeIntegerValue(elem, "integer-digits", 3));
            frame->setNumDecimalDigits(getAttributeIntegerValue(elem, "decimal-digits", 0));

            frame->setLocation(
                    elem. attribute("x").toInt(),
                    elem. attribute("y").toInt());
//            frame->setSize(
//                    elem. attribute("width").toInt(),
//                    elem. attribute("height").toInt());
            frame->resize(QSize(elem. attribute("width").toInt(), elem. attribute("height").toInt()));
            frame->setVisible(true);
        }

        return true;
    }

    /*private*/ /*final*/ /*static*/ Logger* MeterFrameManagerXml::log = LoggerFactory::getLogger("MeterFrameManagerXml");
