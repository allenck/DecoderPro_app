#include "transitmanagerxml.h"
#include "transitmanager.h"
#include "transit.h"
#include "transitsection.h"
#include "section.h"
#include "instancemanager.h"
#include "transitsectionaction.h"

TransitManagerXml::TransitManagerXml()
{
 log = new Logger("TransitManagerXml");
}

/**
 * Provides the functionality for configuring a TransitManager
 * <P>
 *
 * @author Dave Duchamp Copyright (c) 2008
 */
///*public*/ class TransitManagerXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

//    /*public*/ TransitManagerXml() {
//    }

/**
 * Default implementation for storing the contents of a TransitManager
 *
 * @param o Object to store, of type TransitManager
 * @return QDomElement  containing the complete info
 */
/*public*/ QDomElement  TransitManagerXml::store(QObject* o) {
    QDomElement  transits = doc.createElement("transits");
    setStoreElementClass(transits);
    TransitManager* tm = (TransitManager*) o;
    if (tm != NULL) {
        QListIterator<QString> iter(tm->getSystemNameList());

        // don't return an element if there are not Transits to include
        if (!iter.hasNext()) {
            return QDomElement();
        }

        // store the Transit
        while (iter.hasNext()) {
            QString sname = iter.next();
            if (sname == NULL) {
                log->error("System name NULL during store");
            } else {
                log->debug("Transit system name is " + sname);
                Transit* x = tm->getBySystemName(sname);
                QDomElement  elem = doc.createElement("transit");
                        elem.setAttribute("systemName", sname);

                // store common part
                storeCommon(x, elem);

                // save child transitsection entries
                QList<TransitSection*>* tsList = x->getTransitSectionList();
                QDomElement  tsElem = QDomElement();
                for (int k = 0; k < tsList->size(); k++) {
                    TransitSection* ts = tsList->at(k);
                    if (ts != NULL && !ts->isTemporary()) {
                        tsElem = doc.createElement("transitsection");
                        Section* tSection = ts->getSection();
                        if (tSection != NULL) {
                            tsElem.setAttribute("sectionname", tSection->getSystemName());
                        } else {
                            tsElem.setAttribute("sectionname", "NULL");
                        }
                        tsElem.setAttribute("sequence", (ts->getSequenceNumber()));
                        tsElem.setAttribute("direction", (ts->getDirection()));
                        tsElem.setAttribute("alternate", (ts->isAlternate() ? "yes" : "no"));
                        // save child transitsectionaction entries if any
                        QList<TransitSectionAction*>* tsaList = ts->getTransitSectionActionList();
                        if (tsaList->size() > 0) {
                            QDomElement  tsaElem = QDomElement();
                            for (int m = 0; m < tsaList->size(); m++) {
                                TransitSectionAction* tsa = tsaList->at(m);
                                if (tsa != NULL) {
                                    tsaElem = doc.createElement("transitsectionaction");
                                    tsaElem.setAttribute("whencode", (tsa->getWhenCode()));
                                    tsaElem.setAttribute("whatcode", (tsa->getWhatCode()));
                                    tsaElem.setAttribute("whendata", (tsa->getDataWhen()));
                                    tsaElem.setAttribute("whenstring", tsa->getStringWhen());
                                    tsaElem.setAttribute("whatdata1", (tsa->getDataWhat1()));
                                    tsaElem.setAttribute("whatdata2", (tsa->getDataWhat2()));
                                    tsaElem.setAttribute("whatstring", tsa->getStringWhat());
                                    tsElem.appendChild(tsaElem);
                                }
                            }
                        }
                        elem.appendChild(tsElem);
                    }
                }

                transits.appendChild(elem);
            }
        }
    }
    return (transits);
}

/**
 * Subclass provides implementation to create the correct top element,
 * including the type information. Default implementation is to use the
 * local class here.
 *
 * @param transits The top-level element being created
 */
/*public*/ void TransitManagerXml::setStoreElementClass(QDomElement  transits) {
    transits.setAttribute("class", "jmri.configurexml.TransitManagerXml");
}

/*public*/ void TransitManagerXml::load(QDomElement  element, QObject* o) throw (Exception){
    log->error("Invalid method called");
}

/**
 * Create a TransitManager object of the correct class, then register and
 * fill it.
 *
 * @param sharedTransits  Top level QDomElement  to unpack.
 * @param perNodeTransits Per-node top level QDomElement  to unpack.
 * @return true if successful
 */
//@Override
/*public*/ bool TransitManagerXml::load(QDomElement  sharedTransits, QDomElement  perNodeTransits) {
    // load individual Transits
    loadTransits(sharedTransits, perNodeTransits);
    return true;
}
/*public*/ bool TransitManagerXml::load(QDomElement  sharedTransits) throw (Exception){
    // load individual Transits
    loadTransits(sharedTransits, sharedTransits);
    return true;
}

/**
 * Utility method to load the individual Transit objects. If there's no
 * additional info needed for a specific Transit type, invoke this with the
 * parent of the set of Transit elements.
 *
 * @param sharedTransits  QDomElement  containing the Transit elements to load.
 * @param perNodeTransits Per-node QDomElement  containing the Transit elements
 *                        to load.
 */
//@SuppressWarnings("NULL")
/*public*/ void TransitManagerXml::loadTransits(QDomElement  sharedTransits, QDomElement  perNodeTransits)
{
    QDomNodeList transitList = sharedTransits.elementsByTagName("transit");
    if (log->isDebugEnabled()) {
        log->debug("Found " + QString::number(transitList.size()) + " transits");
    }
    TransitManager* tm = (TransitManager*)InstanceManager::getNullableDefault("TransitManager");


    for (int i = 0; i < transitList.size(); i++) {
        if (transitList.at(i).toElement().attribute("systemName") == NULL) {
            log->warn("unexpected NULL in systemName " + transitList.at(i).toElement().tagName() /*+ " "
                    + transitList.at(i).toElement().attributes()*/);
            break;
        }
        QString sysName = transitList.at(i).toElement().attribute("systemName");
        QString userName = NULL;
        if (transitList.at(i).toElement().attribute("userName") != NULL) {
            userName = transitList.at(i).toElement().attribute("userName");
        }
        Transit* x = tm->createNewTransit(sysName, userName);
        if (x != NULL) {
            // load common part
            loadCommon(x, transitList.at(i).toElement());

            // load transitsection children
            QDomNodeList transitTransitSectionList = transitList.at(i).toElement().elementsByTagName("transitsection");
            for (int n = 0; n < transitTransitSectionList.size(); n++) {
                QDomElement  elem = transitTransitSectionList.at(n).toElement();
                int seq = 0;
                int dir = Section::UNKNOWN;
                bool alt = false;
                QString sectionName = elem.attribute("sectionname");
                if (sectionName == ("NULL")) {
                    log->warn("When loading configuration - missing Section in Transit " + sysName);
                }
                bool ok1;
                bool ok2;
                    seq = elem.attribute("sequence").toInt(&ok1);
                    dir = elem.attribute("direction").toInt(&ok2);
                if(!ok1 || !ok2) {
                    log->error("Data Conversion Exception when loading direction of entry point - " /*+ e*/);
                }
                if (elem.attribute("alternate") == ("yes")) {
                    alt = true;
                }
                TransitSection* ts = new TransitSection(sectionName, seq, dir, alt);
                x->addTransitSection(ts);
                // load transitsectionaction children, if any
                QDomNodeList transitTransitSectionActionList = transitTransitSectionList.at(n).toElement().
                        elementsByTagName("transitsectionaction");
                for (int m = 0; m < transitTransitSectionActionList.size(); m++) {
                    QDomElement  elemx = transitTransitSectionActionList.at(m).toElement();
                    int tWhen = 1;
                    int tWhat = 1;
                    int tWhenData = 0;
                    QString tWhenString = elemx.attribute("whenstring");
                    int tWhatData1 = 0;
                    int tWhatData2 = 0;
                    QString tWhatString = elemx.attribute("whatstring");
                    bool ok = true;
                    bool ok1;
                        tWhen = elemx.attribute("whencode").toInt(&ok1); if(!ok1) ok = false;
                        tWhat = elemx.attribute("whatcode").toInt(&ok1); if(!ok1) ok = false;
                        tWhenData = elemx.attribute("whendata").toInt(&ok1); if(!ok1) ok = false;
                        tWhatData1 = elemx.attribute("whatdata1").toInt(&ok1); if(!ok1) ok = false;
                        tWhatData2 = elemx.attribute("whatdata2").toInt(&ok1); if(!ok1) ok = false;
                    if(!ok) {
                        log->error("Data Conversion Exception when loading transit section action - "/*+  e*/);
                    }
                    TransitSectionAction* tsa = new TransitSectionAction(tWhen, tWhat, tWhenData,
                            tWhatData1, tWhatData2, tWhenString, tWhatString);
                    ts->addAction(tsa);
                }
            }
        }
    }
}

/*public*/ int TransitManagerXml::loadOrder() {
    return ((TransitManager*)InstanceManager::getNullableDefault("TransitManager"))->getXMLOrder();
}
