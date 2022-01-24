#include "sectionmanagerxml.h"
#include "sectionmanager.h"
#include "section.h"
#include "instancemanager.h"
#include "block.h"
#include "entrypoint.h"
#include "loggerfactory.h"

SectionManagerXml::SectionManagerXml(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
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
    SectionManager* sctm = (SectionManager*) o;
    if (sctm!=NULL) {
     QSet<NamedBean*> sctList = sctm->getNamedBeanSet();
     // don't return an element if there are no Sections to include
     if (sctList.isEmpty()) {
         return QDomElement();
     }

     // store the Section
     for(NamedBean* bean : sctList)
     {
      Section* x = (Section*)bean;
      QString sName = x->getSystemName();
      log->debug(tr("Section system name is %1").arg(sName));


      if (x->getSectionType() != Section::DYNAMICADHOC)
      {
       QDomElement elem = doc.createElement("section");
       elem.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(sName)));

       // As a work-around for backward compatibility, store systemName and username as attribute.
       // TODO Remove this in e.g. JMRI 4.11.1 and then update all the loadref comparison files
       elem.setAttribute("systemName", sName);
       QString uname = x->getUserName();
       if (uname != "" && !uname.isEmpty()) {
           elem.setAttribute("userName", uname);
       }
      // store common part
      storeCommon(x, elem);

      QString txt = "userdefined";
      if (x->getSectionType() == Section::SIGNALMASTLOGIC) {
          txt = "signalmastlogic";
      }
      elem.setAttribute("creationtype", txt);
      txt = x->getForwardStoppingSensorName();
      if ((txt != "") && (!txt.isEmpty())) {
          elem.setAttribute("fstopsensorname", txt);
      }
      txt = x->getReverseStoppingSensorName();
      if ((txt != "") && (!txt.isEmpty())) {
          elem.setAttribute("rstopsensorname", txt);
      }
      txt = x->getForwardBlockingSensorName();
      if ((txt != "") && (!txt.isEmpty())) {
          elem.setAttribute("fsensorname", txt);
      }
      txt = x->getReverseBlockingSensorName();
      if ((txt != "") && (!txt.isEmpty())) {
          elem.setAttribute("rsensorname", txt);
      }
      if (x->getSectionType() == Section::USERDEFINED) {
       // save child block entries
       int index = 0;
       Block* b = x->getBlockBySequenceNumber(index);
       QDomElement bElem;
       while (b != nullptr) {
           bElem = doc.createElement("blockentry");
           bElem.setAttribute("sName", b->getSystemName());
           bElem.setAttribute("order", (index));
           elem.appendChild(bElem);
           index++;
           b = x->getBlockBySequenceNumber(index);
       }
       // save child entry points
       QList<EntryPoint*>* epList = x->getEntryPointList();
       QDomElement epElem;
       int i = 0;
       for (EntryPoint* ep : *epList) {
           if (ep != nullptr) {
               epElem = doc.createElement("entrypoint");
               // add some protection against a reading problem
               if (ep->getFromBlock() == nullptr) {
                   log->error(tr("Unexpected null getFromBlock while storing ep %1 in Section %2, skipped").arg(i).arg(sName));
                   break;
               }
               epElem.setAttribute("fromblock", ep->getFromBlock()->getSystemName());
               if (ep->getBlock() == nullptr) {
                   log->error(tr("Unexpected null getBlock while storing ep %1 in Section %2, skipped").arg(i).arg(sName));
                   break;
               }
               epElem.setAttribute("toblock", ep->getBlock()->getSystemName());
               epElem.setAttribute("direction", (ep->getDirection()));
               epElem.setAttribute("fixed", (ep->isFixed() ? "yes" : "no"));
               epElem.setAttribute("fromblockdirection", "" + ep->getFromBlockDirection());
               elem.appendChild(epElem);
               i++;
           }
       }
   }
   sections.appendChild(elem);
   }
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
/*public*/ bool SectionManagerXml::load(QDomElement sharedSections, QDomElement perNodeSections) throw (Exception)
{
    // load individual Sections
    loadSections(sharedSections, perNodeSections);
    return true;
}

/**
 * Utility method to load the individual Section objects.
 * If there's no additional info needed for a specific Section type,
 * invoke this with the parent of the set of Section elements.
 * @param sections QDomElement containing the Section elements to load.
 */
//@SuppressWarnings("unchecked")
/*public*/ void SectionManagerXml::loadSections(QDomElement sharedSections, QDomElement /*perNodeSections*/) {
    QDomNodeList  sectionList = sharedSections.toElement().elementsByTagName("section");
    if (log->isDebugEnabled()) log->debug("Found "+QString::number(sectionList.size())+" sections");
    SectionManager* sctm = ((SectionManager*)InstanceManager::getDefault("SectionManager"));
    sctm->setPropertyChangesSilenced("beans", true);

    for(int i=0; i < sectionList.count(); i++)
    {
     QDomElement s = sectionList.at(i).toElement();
     QString sysName = getSystemName(s);
     QString userName = getUserName(s);
     Section* x;
     try {
         x = sctm->createNewSection(sysName, userName);
     }
     catch (IllegalArgumentException* ex){
         log->error(tr("Unable to create Section %1 %2").arg(sysName,ex->getMessage()));
         continue;
     }
     // load common part
     loadCommon(x, (s));

     if (s.attribute("creationtype") != nullptr) {
         QString creationType = s.attribute("creationtype");
         if (creationType ==("userdefined")) {
             x->setSectionType(Section::USERDEFINED);
         } else if (creationType ==("signalmastlogic")) {
             x->setSectionType(Section::SIGNALMASTLOGIC);
         }
     }
     if (s.attribute("fsensorname") != "") {
         QString forName = s.attribute("fsensorname");
         x->delayedSetForwardBlockingSensorName(forName);
     }
     if (s.attribute("rsensorname") != "") {
         QString revName = s.attribute("rsensorname");
         x->delayedSetReverseBlockingSensorName(revName);
     }
     if (s.attribute("fstopsensorname") != "") {
         QString forName = s.attribute("fstopsensorname");
         x->delayedSetForwardStoppingSensorName(forName);
     }
     if (s.attribute("rstopsensorname") != "") {
         QString revName = s.attribute("rstopsensorname");
         x->delayedSetReverseStoppingSensorName(revName);
     }

     // load block entry children
     QDomNodeList sectionBlockList = s.elementsByTagName("blockentry");
     for (i = 0; i < sectionBlockList.count(); i++)
     {
      QDomElement elem = sectionBlockList.at(i).toElement();
         x->delayedAddBlock(elem.attribute("sName"));
         // insert code here to verify sequence number if needed in the future
     }

     // load entry point children
     QDomNodeList sectionEntryPointList = s.elementsByTagName("entrypoint");
     for (i = 0; i < sectionEntryPointList.count(); i++)  {
      QDomElement elem = sectionEntryPointList.at(i).toElement();
         QString blockName = elem.attribute("toblock");
         QString fromBlockName = elem.attribute("fromblock");
         QString fromBlockDirection = "";
         if (elem.attribute("fromblockdirection") != "") {
             fromBlockDirection = elem.attribute("fromblockdirection");
         }
         EntryPoint* ep = new EntryPoint(blockName, fromBlockName, fromBlockDirection);
         bool bok;
             ep->setDirection(elem.attribute("direction").toInt(&bok));
         if(!bok) {
             log->error("Data Conversion Exception when loading direction of entry point - "/*, e*/);
         }
         bool fixed = true;
         if (elem.attribute("fixed") ==("no")) {
             fixed = false;
         }
         ep->setFixed(fixed);
         if (ep->isForwardType()) {
             x->addToForwardList(ep);
         } else if (ep->isReverseType()) {
             x->addToReverseList(ep);
         }
     }
 }
 sctm->setPropertyChangesSilenced("beans", false);
}

/*public*/ int SectionManagerXml::loadOrder()const{
    return ((SectionManager*)InstanceManager::getDefault("SectionManager"))->getXMLOrder();
}

/*private*/ /*final*/ /*static*/ Logger* SectionManagerXml::log = LoggerFactory::getLogger("SectionManagerXml");
