#include "matrixsignalmastxml.h"
#include "matrixsignalmast.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "signalmastmanager.h"
#include "signalappearancemap.h"

/**
 * Handle XML configuration for DefaultSignalMastManager objects.
 *
 * @author Bob Jacobsen Copyright: (C) 2009
 * @author Egbert Broerse Copyright: (C) 2016, 2017
 */
///*public*/ class MatrixSignalMastXml
//        extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

/*public*/ MatrixSignalMastXml::MatrixSignalMastXml(QObject *parent):AbstractNamedBeanManagerConfigXML(parent) {
}

/**
 * Default implementation for storing the contents of a
 * MatrixSignalMastManager
 *
 * @param o Object to store, of type MatrixSignalMast
 * @return e QDomElement containing the complete info
 */
//@Override
/*public*/ QDomElement MatrixSignalMastXml::store(QObject* o) { // from mast p to XML
    MatrixSignalMast* p = (MatrixSignalMast*) o;

    QDomElement e = doc.createElement("matrixsignalmast");
    e.setAttribute("class", /*this.getClass().getName()*/ "jmri.implementation.configurexml.MatrixSignalMastXml");

    // include content
    e.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(p->getSystemName())));

    storeCommon(p, e); // username, comment & properties

    // mast properties:
    QDomElement unlit = doc.createElement("unlit");
    if (p->allowUnLit()) {
        unlit.setAttribute("allowed", "yes");
        unlit.appendChild(doc.createElement("bitString").appendChild(doc.createTextNode(p->getUnLitChars())));
    } else {
        unlit.setAttribute("allowed", "no");
    }
    e.appendChild(unlit);

    QStringList outputs = p->getOutputs();
    // convert char[] to xml-storable simple String
    // max. 5 outputs (either: turnouts (bean names) [or ToDo: DCC addresses (numbers)]
    // spotted by SpotBugs as to never be null (check on creation of MatrixMast)
    QDomElement outps = doc.createElement("outputs");
    int i = 1;
    for (QString _output : outputs) {
        log->debug(tr("   handling %1").arg(_output));
        QString key = ("output" + i);
        QDomElement outp = doc.createElement("output");
        outp.setAttribute("matrixCol", key);
        outp.appendChild(doc.createTextNode(p->getOutputName(i))); // get name (Turnout)
        outps.appendChild(outp);
        i++;
    }
    if (outputs.size() != 0) {
        e.appendChild(outps);
    }

    // string of max. 6 chars "001010" describing matrix row per aspect
    SignalAppearanceMap* appMap = p->getAppearanceMap();
    if (appMap != nullptr) {
        QDomElement bss = doc.createElement("bitStrings");
        QStringListIterator aspects = appMap->getAspects();
        while (aspects.hasNext()) {
            QString key = aspects.next();
            QDomElement bs = doc.createElement("bitString");
            bs.setAttribute("aspect", key);
            bs.appendChild(doc.createTextNode(p->getBitstring(key)));
            bss.appendChild(bs);
        }
            e.appendChild(bss);

    }
    QStringList disabledAspects = *p->getDisabledAspects();
    if (!disabledAspects.isEmpty()) {
        QDomElement el = doc.createElement("disabledAspects");
        for (QString aspect : disabledAspects) {
            QDomElement ele = doc.createElement("disabledAspect");
            ele.appendChild(doc.createTextNode(aspect));
            el.appendChild(ele);
        }
        if (disabledAspects.size() != 0) {
            e.appendChild(el);
        }
    }
    return e;
}

//@Override
/*public*/ bool MatrixSignalMastXml::load(QDomElement shared, QDomElement perNode) throw (Exception)
{ // from XML to mast m
    MatrixSignalMast* m;
    QString sys = getSystemName(shared);
    try {
    m = new MatrixSignalMast(sys);
    } catch (Exception e) {
        log->error("An error occurred while trying to create the signal '" + sys + "' " + e.getMessage());
        return false;
    }
    if (getUserName(shared) != "") {
        m->setUserName(getUserName(shared));
    }

    loadCommon(m, shared); // username & comment

    if (!shared.firstChildElement("unlit").isNull()) {
        QDomElement unlit = shared.firstChildElement("unlit");
        if (unlit.attribute("allowed") != "") {
            if (unlit.attribute("allowed") == ("no")) {
                m->setAllowUnLit(false);
            } else {
                m->setAllowUnLit(true);
                QString bits = unlit.firstChildElement("bitString").text();
                m->setUnLitBits(bits);
            }
        }
    }

    QDomElement outps = shared.firstChildElement("outputs"); // multiple
    if (!outps.isNull()) {
        QDomNodeList list = outps.elementsByTagName("output"); // singular
        m->setBitNum(list.size()); // set char[] size before creating outputs
        for (int i =0; i <list.count(); i++) {
         QDomElement outp= list.at(i).toElement();
            QString outputname = outp.attribute("matrixCol");
            QString turnoutname = outp.text();
            m->setOutput(outputname, turnoutname);
        }
    }

    QDomElement bss = shared.firstChildElement("bitStrings"); // multiple
    if (!bss.isNull()) {
        QDomNodeList  list = bss.elementsByTagName("bitString"); // singular
        for (int i =0; i <list.count(); i++) {
         QDomElement bs= list.at(i).toElement();
            m->setBitstring(bs.attribute("aspect"), bs.text()); // OK if value is null
        }
    }

    QDomElement disabled = shared.firstChildElement("disabledAspects"); // multiple
    if (!disabled.isNull()) {
        QDomNodeList list= disabled.elementsByTagName("disabledAspect"); // singular
        for (int i =0; i <list.count(); i++) {
         QDomElement asp= list.at(i).toElement();
            m->setAspectDisabled(asp.text());
        }
    }
    static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->Register(m);
    return true;
}

//@Override
/*public*/ void MatrixSignalMastXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception){
    log->error("Invalid method called");
}

/*private*/ /*final*/ /*static*/ Logger* MatrixSignalMastXml::log = LoggerFactory::getLogger("MatrixSignalMastXml");
