#include "sectionmanagerxml.h"
#include "sectionmanager.h"
#include "section.h"
#include "instancemanager.h"
#include "block.h"
#include "entrypoint.h"

SectionManagerXml::SectionManagerXml(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("SectionManagerXml");
 setObjectName("SectionManagerXml");
}
/**
 * Provides the functionality for
 * persistence of a SectionManager
 * <P>
 *
 * @author Dave Duchamp Copyright (c) 2008
 * @version $Revision: 18102 $
 */
///*public*/ class SectionManagerXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

//    /*public*/ SectionManagerXml() {
//    }

/**
 * Implementation for storing the contents of a
 * SectionManager
 * @param o Object to store, of type SectionManager
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement SectionManagerXml::store(QObject* o)
{
    QDomElement sections = doc.createElement("sections");
    setStoreElementClass(sections);
    SectionManager* tm = (SectionManager*) o;
    if (tm!=NULL) {
        QStringListIterator iter(tm->getSystemNameList());

        // don't return an element if there are not Sections to include
                if (!iter.hasNext()) return QDomElement();

        // store the Section
        while (iter.hasNext()) {
            QString sname = iter.next();
            if (sname==NULL) log->error("System name NULL during store");
            log->debug("Section system name is "+sname);
            Section* x = (Section*)tm->getBySystemName(sname);
            QDomElement elem = doc.createElement("section");
            //elem.setAttribute("systemName", sname);
            QDomElement e1;
            elem.appendChild(e1 = doc.createElement("systemName"));
            e1.appendChild(doc.createTextNode(sname));

            // store common part
            storeCommon(x, elem);

            QString txt = x->getForwardBlockingSensorName();
            if ( (txt!=NULL) && (txt!=("")) )
                elem.setAttribute("fsensorname",txt);
            txt = x->getReverseBlockingSensorName();
            if ( (txt!=NULL) && (txt!=("")) )
                elem.setAttribute("rsensorname",txt);
            txt = x->getForwardStoppingSensorName();
            if ( (txt!=NULL) && (txt!=("")) )
                elem.setAttribute("fstopsensorname",txt);
            txt = x->getReverseStoppingSensorName();
            if ( (txt!=NULL) && (txt!=("")) )
                elem.setAttribute("rstopsensorname",txt);

            // save child block entries
            int index = 0;
            Block* b = x->getBlockBySequenceNumber(index);
            QDomElement bElem = QDomElement();
            while (b!=NULL) {
                bElem = doc.createElement("blockentry");
                bElem.setAttribute("sName",b->getSystemName());
                bElem.setAttribute("order",(index));
                elem.appendChild(bElem);
                index ++;
                b = x->getBlockBySequenceNumber(index);
            }
            // save child entry points
            QList<EntryPoint*>* epList = x->getEntryPointList();
            QDomElement epElem = QDomElement();
            EntryPoint* ep = NULL;
            for (int i = 0; i<epList->size(); i++) {
                ep = epList->at(i);
                if (ep!=NULL) {
                    epElem = doc.createElement("entrypoint");
                    // add some protection against a reading problem
                    if (ep->getFromBlock() == NULL) {
                        log->error("Unexpected NULL getFromBlock while storing ep "+QString::number(i)+" in Section "+sname+", skipped");
                        break;
                    }
                    if (ep->getFromBlock()->getSystemName() == NULL) {
                        log->error("Unexpected NULL in FromBlock systemName while storing ep "+QString::number(i)+" in Section "+sname+", skipped");
                        break;
                    }
                    epElem.setAttribute("fromblock",ep->getFromBlock()->getSystemName());
                    if (ep->getBlock() == NULL) {
                        log->error("Unexpected NULL getBlock while storing ep "+QString::number(i)+" in Section "+sname+", skipped");
                        break;
                    }
                    if (ep->getBlock()->getSystemName() == NULL) {
                        log->error("Unexpected NULL in Block systemName while storing ep "+QString::number(i)+" in Section "+sname+", skipped");
                        break;
                    }
                    epElem.setAttribute("toblock",ep->getBlock()->getSystemName());
                    epElem.setAttribute("direction",(ep->getDirection()));
                    epElem.setAttribute("fixed",(ep->isFixed()?"yes":"no"));
                    epElem.setAttribute("fromblockdirection",ep->getFromBlockDirection());
                    elem.appendChild(epElem);
                }
            }

            sections.appendChild(elem);
        }
    }
    return (sections);
}

/**
 * Subclass provides implementation to create the correct top
 * element, including the type information.
 * Default implementation is to use the local class here.
 * @param sections The top-level element being created
 */
/*public*/ void SectionManagerXml::setStoreElementClass(QDomElement sections)
{
    sections.setAttribute("class","jmri.configurexml.SectionManagerXml");
}

/*public*/ void SectionManagerXml::load(QDomElement /*element*/, QObject* /*o*/)  throw (Exception){
    log->error("Invalid method called");
}

/**
 * Create a SectionManager object of the correct class, then
 * register and fill it.
 * @param sections Top level QDomElement to unpack.
 * @return true if successful
 */
/*public*/ bool SectionManagerXml::load(QDomElement sections) throw (Exception)
{
    // load individual Sections
    loadSections(sections);
    return true;
}

/**
 * Utility method to load the individual Section objects.
 * If there's no additional info needed for a specific Section type,
 * invoke this with the parent of the set of Section elements.
 * @param sections QDomElement containing the Section elements to load.
 */
//@SuppressWarnings("unchecked")
/*public*/ void SectionManagerXml::loadSections(QDomElement sections) {
    QDomNodeList  sectionList = sections.toElement().elementsByTagName("section");
    if (log->isDebugEnabled()) log->debug("Found "+QString::number(sectionList.size())+" sections");
    SectionManager* tm = ((SectionManager*)InstanceManager::getDefault("SectionManager"));

    for (int i=0; i<sectionList.size(); i++) {
        if (sectionList.at(i).toElement().toElement().attribute("systemName") == NULL) {
            log->warn("unexpected NULL in systemName "+sectionList.at(i).toElement().tagName()+" "/*+
                                    (sectionList.at(i)).toElement().attributes()*/);
            break;
        }
        QString sysName = (sectionList.at(i)).toElement().toElement().attribute("systemName");
        QString userName = NULL;
        if (sectionList.at(i).toElement().toElement().attribute("userName") != NULL) {
            userName = (sectionList.at(i).toElement()).toElement().attribute("userName");
        }
        Section* x = tm->createNewSection(sysName, userName);
        if (x!=NULL) {
            // load common part
            loadCommon(x, (sectionList.at(i).toElement()));

            if (sectionList.at(i).toElement().toElement().attribute("fsensorname") != NULL) {
                QString forName = (sectionList.at(i)).toElement().attribute("fsensorname");
                x->delayedSetForwardBlockingSensorName(forName);
            }
            if (sectionList.at(i).toElement().attribute("rsensorname") != NULL) {
                QString revName = sectionList.at(i).toElement().attribute("rsensorname");
                x->delayedSetReverseBlockingSensorName(revName);
            }
            if (sectionList.at(i).toElement().attribute("fstopsensorname") != NULL) {
                QString forName = sectionList.at(i).toElement().attribute("fstopsensorname");
                x->delayedSetForwardStoppingSensorName(forName);
            }
            if (sectionList.at(i).toElement().attribute("rstopsensorname") != NULL) {
                QString revName = sectionList.at(i).toElement().attribute("rstopsensorname");
                x->delayedSetReverseStoppingSensorName(revName);
            }

            // load block entry children
            QDomNodeList  sectionBlockList = sectionList.at(i).toElement().elementsByTagName("blockentry");
            for (int n = 0; n<sectionBlockList.size(); n++) {
                QDomElement elem = sectionBlockList.at(n).toElement();
                x->delayedAddBlock(elem.attribute("sName"));
// insert code here to verify sequence number if needed in the future
            }

            // load entry point children
           QDomNodeList  sectionEntryPointList = sectionList.at(i).toElement().elementsByTagName("entrypoint");
            for (int n = 0; n<sectionEntryPointList.size(); n++) {
                QDomElement elem = sectionEntryPointList.at(n).toElement();
                QString blockName = elem.attribute("toblock");
                QString fromBlockName = elem.attribute("fromblock");
                QString fromBlockDirection = "";
                if (elem.attribute("fromblockdirection")!=NULL)
                    fromBlockDirection = elem.attribute("fromblockdirection");
                EntryPoint* ep = new EntryPoint(blockName, fromBlockName, fromBlockDirection);
                //if (ep!=NULL) {
                    bool ok;
                        ep->setDirection(elem.attribute("direction").toInt(&ok));
                    if(!ok) {
                        log->error("Data Conversion Exception when loading direction of entry point - "+sysName);
                    }
                    bool fixed = true;
                    if (elem.attribute("fixed")==("no")) fixed = false;
                    ep->setFixed(fixed);
                    if (ep->isForwardType()) x->addToForwardList(ep);
                    else if (ep->isReverseType()) x->addToReverseList(ep);
                //}
            }
        }
    }
}

/*public*/ int SectionManagerXml::loadOrder(){
    return ((SectionManager*)InstanceManager::getDefault("SectionManager"))->getXMLOrder();
}
