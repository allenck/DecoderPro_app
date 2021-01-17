#include "defaultsignalmastmanagerxml.h"
#include "instancemanager.h"
#include "defaultsignalmastmanager.h"
#include "signalmastmanager.h"
#include "signalmastrepeater.h"
#include "signalheadsignalmastxml.h"
#include "turnoutsignalmast.h"
#include "turnoutsignalmastxml.h"
#include "virtualsignalmast.h"
#include "virtualsignalmastxml.h"
#include "dccsignalmastxml.h"
#include "class.h"

DefaultSignalMastManagerXml::DefaultSignalMastManagerXml(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("DefaultSignalMastManagerXml");
 setObjectName("DefaultSignalMastManagerXml");
}

/**
 * Handle XML configuration for a DefaultSignalMastManager objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2009
 * @version $Revision: 21890 $
 */
///*public*/ class DefaultSignalMastManagerXml
//            extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

// /*public*/ DefaultSignalMastManagerXml() {}

/**
 * Default implementation for storing the contents of a
 * DefaultSignalMastManager
 * @param o Object to store, of type TripleTurnoutSignalHead
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement DefaultSignalMastManagerXml::store(QObject* o)
{
    DefaultSignalMastManager* smm = (DefaultSignalMastManager*)o;

    QDomElement signalmasts = doc.createElement("signalmasts");
    signalmasts.setAttribute("class", "jmri.managers.configurexml.DefaultSignalMastManagerXml");
    if(smm!=nullptr)
    {
     QSet<NamedBean*> smList = smm->getNamedBeanSet();
     // don't return an element if there are no SignalMasts to include
     if (smList.isEmpty()) {
         return QDomElement();
     }
     // include contents
     for (NamedBean* nb : smList)
     {
       SignalMast* sm = (SignalMast*)nb;
       QDomElement e = ConfigXmlManager::elementFromObject(sm);
       if (!e.isNull()) {
           signalmasts.appendChild(e);
       }
     }

     QList<SignalMastRepeater*>* repeaterList = smm->getRepeaterList();
     if(repeaterList->size()>0)
     {
      //QDomElement repeatElem= doc.createElement("signalmastrepeaters");
      foreach(SignalMastRepeater* smr, *repeaterList)
      {
        QDomElement e = doc.createElement("signalmastrepeater");
        QDomElement e1;
        e.appendChild(e1=doc.createElement("masterMast"));
        e1.appendChild(doc.createTextNode(smr->getMasterMastName()));
        QDomElement e2;
        e.appendChild(e2=doc.createElement("slaveMast"));
        e2.appendChild(doc.createTextNode(smr->getSlaveMastName()));
        QDomElement e3;
        e.appendChild(e3=doc.createElement("enabled"));
        e3.appendChild(doc.createTextNode(smr->getEnabled()?"true":"false"));
        QDomElement e4;
        switch (smr->getDirection())
        {
         case 1 : e.appendChild(e4=doc.createElement("update"));
            e4.appendChild(doc.createTextNode("MasterToSlave"));
            break;
         case 2 : e.appendChild(e4=doc.createElement("update"));
            e4.appendChild(doc.createTextNode("SlaveToMaster"));
            break;
         default : e.appendChild(e4=doc.createElement("update"));
            e4.appendChild(doc.createTextNode("BothWay"));
            break;
        }
        signalmasts.appendChild(e);
       }
      }
     }
    return signalmasts;
}

/**
 * Create a DefaultSignalMastManager
 * @param QDomElement Top level QDomElement to unpack.
 * @return true if successful
 */
//@SuppressWarnings("unchecked")
/*public*/ bool DefaultSignalMastManagerXml::load(QDomElement shared, QDomElement perNode)
{
 // loop over contained signalmast elements
 QDomNodeList list = shared.elementsByTagName("signalmast");

 for (int i = 0; i < list.size(); i++)
 {
  QDomElement e = list.at(i).toElement();
  if (e.attribute("class") == "")
  {
   SignalMast* m;
   QString sys = getSystemName(e);
   try
   {
    m = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))
            ->provideSignalMast(sys);

    if (getUserName(e) != "") {
        m->setUserName(getUserName(e));
    }

    loadCommon(m, e);
   }
   catch (IllegalArgumentException ex) {
       log->warn(tr("Failed to provide SignalMast \"%1\" in load").arg(sys));
   }
  }
  else {
   QString adapterName = e.attribute("class");
   log->debug("load via " + adapterName);
   try {
       XmlAdapter* adapter = (XmlAdapter*) Class::forName(adapterName)->newInstance();
       // and do it
       adapter->load(e, QDomElement());
   } catch (Exception ex) {
       log->error(tr("Exception while loading %1: %2").arg(e.tagName()).arg(ex.getMessage()), ex);
   }
  }
 }

 list = shared.elementsByTagName("turnoutsignalmast");
 if (!list.isEmpty())
 {
  for (int i = 0; i < list.size(); i++)
  {
   QDomElement e = list.at(i).toElement();
   QString adapterName = e.attribute("class");
   log->debug("load via " + adapterName);
   try {
       XmlAdapter* adapter = (XmlAdapter*) Class::forName(adapterName)->newInstance();
       // and do it
       adapter->load(e, QDomElement());
   } catch (Exception ex) {
       log->error(tr("Exception while loading %1: %2").arg(e.tagName()).arg(ex.getMessage()), ex);
   }
  }
 }

 list = shared.elementsByTagName("virtualsignalmast");
 if (!list.isEmpty())
 {
  for (int i = 0; i < list.size(); i++)
  {
   QDomElement e = list.at(i).toElement();
   QString adapterName = e.attribute("class");
    log->debug("load via " + adapterName);
    try {
        XmlAdapter* adapter = (XmlAdapter*) Class::forName(adapterName)->newInstance();
        // and do it
        adapter->load(e, QDomElement());
    } catch (Exception ex) {
     log->error(tr("Exception while loading %1: %2").arg(e.tagName()).arg(ex.getMessage()), ex);
    }
  }
 }

 list = shared.elementsByTagName("matrixsignalmast");
 if (!list .isEmpty()) {
     for (int i = 0; i < list.size(); i++) {
         QDomElement e = list.at(i).toElement();
         QString adapterName = e.attribute("class");
         log->debug("load via " + adapterName);
         try {
             XmlAdapter* adapter = (XmlAdapter*) Class::forName(adapterName)->newInstance();
             // and do it
             adapter->load(e, QDomElement());
         } catch (Exception ex) {
          log->error(tr("Exception while loading %1: %2").arg(e.tagName()).arg(ex.getMessage()), ex);
         }
     }
 }

 list = shared.elementsByTagName("dccsignalmast");
 if (!list.isEmpty()) {
     for (int i = 0; i < list.size(); i++) {
         QDomElement e = list.at(i).toElement();
         QString adapterName = e.attribute("class");
         log->debug("load via " + adapterName);
         try {
             XmlAdapter* adapter = (XmlAdapter*) Class::forName(adapterName)->newInstance();
             // and do it
             adapter->load(e, QDomElement());
         } catch (Exception ex) {
          log->error(tr("Exception while loading %1: %2").arg(e.tagName()).arg(ex.getMessage()), ex);
         }
     }
 }

 list = shared.elementsByTagName("olcbsignalmast");
 if (!list.isEmpty()) {
     for (int i = 0; i < list.size(); i++) {
         QDomElement e = list.at(i).toElement();
         QString adapterName = e.attribute("class");
         log->debug("load via " + adapterName);
         try {
             XmlAdapter* adapter = (XmlAdapter*) Class::forName(adapterName)->newInstance();
             // and do it
             adapter->load(e, QDomElement());
         } catch (Exception ex) {
          log->error(tr("Exception while loading %1: %2").arg(e.tagName()).arg(ex.getMessage()), ex);
         }
     }
 }

 list = shared.elementsByTagName("signalmastrepeater");
 if (!list.isEmpty()) {
     DefaultSignalMastManager* m = (DefaultSignalMastManager*) InstanceManager::getDefault("SignalMastManager");
     for (int i = 0; i < list.size(); i++) {
         QDomElement e = list.at(i).toElement();
         QString masterName = e.firstChildElement("masterMast").text();
         QString slaveName = e.firstChildElement("slaveMast").text();
         SignalMastRepeater* smr = new SignalMastRepeater(masterName, slaveName);
         if (e.firstChildElement("enabled") != QDomElement() && e.firstChildElement("enabled").text()==("false")) {
             smr->setEnabled(false);
         }
         if (e.firstChildElement("update") != QDomElement()) {
             if (e.firstChildElement("update").text() == ("MasterToSlave")) {
                 smr->setDirection(SignalMastRepeater::MASTERTOSLAVE);
             } else if (e.firstChildElement("update").text() == ("SlaveToMaster")) {
                 smr->setDirection(SignalMastRepeater::SLAVETOMASTER);
             }
         }
         try {
             m->addRepeater(smr);
         } catch (JmriException ex) {
             log->error("Unable to add mast repeater " + masterName + " : " + slaveName);
         }
     }
     m->initialiseRepeaters();
 }
 return true;
}

/*public*/ void DefaultSignalMastManagerXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception) {
    log->error("Invalid method called");
}

/*public*/ int DefaultSignalMastManagerXml::loadOrder()const{
    return static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getXMLOrder();
}
