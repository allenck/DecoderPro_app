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

DefaultSignalMastManagerXml::DefaultSignalMastManagerXml(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("DefaultSignalMastManagerXML");
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
 * @return Element containing the complete info
 */
/*public*/ QDomElement DefaultSignalMastManagerXml::store(QObject* o)
{
    DefaultSignalMastManager* m = (DefaultSignalMastManager*)o;

    QDomElement element = doc.createElement("signalmasts");
    element.setAttribute("class", "jmri.managers.configurexml.DefaultSignalMastManagerXml");
    if(m!=NULL){
        // include contents
        QStringList names = m->getSystemNameList();
        for (int i = 0; i < names.size(); i++) {
            //QDomElement e = doc.createElement("signalmast");
            SignalMast* p = m->getSignalMast(names.at(i));
            try {
                QDomElement e = ConfigXmlManager::elementFromObject(p);
                if (!e.isNull()) element.appendChild(e);
            } catch (Exception e) {
                log->error("Error storing signalmast: "+e.getMessage());
                //e.printStackTrace();
            }


            /*e.setAttribute("systemName", p.getSystemName()); // deprecated for 2.9.* series
            e.appendChild(doc.createElement("systemName").appendChild(p.getSystemName()));
            storeCommon(p, e);
            element.appendChild(e);*/
        }
#if 1
        QList<SignalMastRepeater*>* repeaterList = m->getRepeaterList();
        if(repeaterList->size()>0){
            //Element repeatElem= doc.createElement("signalmastrepeaters");
            foreach(SignalMastRepeater* smr, *repeaterList){
                if(smr->getMasterMast()!=NULL && smr->getSlaveMast()!=NULL){
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
                    element.appendChild(e);
                }
            }
            //element.add(repeatElem);
        }
#endif
    }
    return element;
}

/**
 * Create a DefaultSignalMastManager
 * @param element Top level Element to unpack.
 * @return true if successful
 */
//@SuppressWarnings("unchecked")
/*public*/ bool DefaultSignalMastManagerXml::load(QDomElement element) throw (Exception)
{
 // loop over contained signalmast elements
 QDomNodeList list = element.elementsByTagName("signalmast");

 for (int i = 0; i < list.size(); i++)
 {
  QDomElement e = list.at(i).toElement();
  if(e.attribute("class")==NULL)
  {
   SignalMast* m;
   QString sys = getSystemName(e);
   m = ((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())
                ->provideSignalMast(sys);

    if (getUserName(e) != NULL)
        m->setUserName(getUserName(e));

    loadCommon(m, e);
  }
  else
  {
   QString adapterName = e.attribute("class");
   log->debug("load via "+adapterName);
   try
   {
//                XmlAdapter* adapter = (XmlAdapter*)Class.forName(adapterName).newInstance();
//                // and do it
//                adapter.load(e);
     if(adapterName =="jmri.implementation.configurexml.SignalHeadSignalMastXml")
     {
      SignalHeadSignalMastXml* xml = new SignalHeadSignalMastXml();
      xml->load(e);
     }
     else if(adapterName =="jmri.implementation.configurexml.TurnoutSignalMastXml")
     {
      TurnoutSignalMastXml* xml = new TurnoutSignalMastXml();
      xml->load(e);
     }
     else if(adapterName =="jmri.implementation.configurexml.VirtualSignalMastXml")
     {
      VirtualSignalMastXml* xml = new VirtualSignalMastXml();
      xml->load(e);
     }
     else
     throw Exception(tr("Adapter name %1 not found").arg(adapterName));
    }
    catch (Exception ex)
    {
        log->error("Exception while loading "+e.tagName()+":"+ex.getMessage());
        //ex.printStackTrace();
    }
   }
  }


  list = element.elementsByTagName("turnoutsignalmast");
  if(!list.isEmpty())
  {
   for (int i = 0; i < list.size(); i++)
   {
    QDomElement e = list.at(i).toElement();
    QString adapterName = e.attribute("class");
    log->debug("load via "+adapterName);
    try
    {
//                XmlAdapter adapter = (XmlAdapter)Class.forName(adapterName).newInstance();
//                // and do it
//                adapter.load(e);
     if(adapterName == "jmri.implementation.configurexml.SignalHeadSignalMastXml")
     {
        SignalHeadSignalMastXml* xml = new SignalHeadSignalMastXml();
        xml->load(e);
     }
     else
     if(adapterName == "jmri.implementation.configurexml.TurnoutSignalMastXml")
     {
        TurnoutSignalMastXml* xml = new TurnoutSignalMastXml();
        xml->load(e);
     }
     else
     if(adapterName == "jmri.implementation.configurexml.VirtualSignalMastXml")
     {
        VirtualSignalMastXml* xml = new VirtualSignalMastXml();
        xml->load(e);
     }
    }
    catch (Exception ex)
    {
     log->error("Exception while loading "+e.tagName()+":"+ex.getMessage());
    //ex.printStackTrace();
    }
   }
  }

  list = element.elementsByTagName("virtualsignalmast");
  if(!list.isEmpty()){
        for (int i = 0; i < list.size(); i++) {
            QDomElement e = list.at(i).toElement();
            QString adapterName = e.attribute("class");
            log->debug("load via "+adapterName);
            try {
//                XmlAdapter adapter = (XmlAdapter)Class.forName(adapterName).newInstance();
//                // and do it
//                adapter.load(e);
                if(adapterName == "jmri.implementation.configurexml.VirtualSignalMastXml")
                {
                    VirtualSignalMastXml* xml = new VirtualSignalMastXml();
                    xml->load(e);
                }
            } catch (Exception ex) {
                log->error("Exception while loading "+e.tagName()+":"+ex.getMessage());
                //ex.printStackTrace();
            }
        }
    }

    list = element.elementsByTagName("dccsignalmast");
    if(!list.isEmpty()){
        for (int i = 0; i < list.size(); i++) {
            QDomElement e = list.at(i).toElement();
            QString adapterName = e.attribute("class");
            log->debug("load via "+adapterName);
            try {
//                XmlAdapter adapter = (XmlAdapter)Class.forName(adapterName).newInstance();
//                // and do it
//                adapter.load(e);
             if(adapterName == "jmri.implementation.configurexml.DccSignalMastXml")
             {
                 DccSignalMastXml* xml = new DccSignalMastXml();
                 xml->load(e);
             }
            } catch (Exception ex) {
                log->error("Exception while loading "+e.tagName()+":"+ex.getMessage());
                //ex.printStackTrace();
            }
        }
    }
#if 1
    list = element.elementsByTagName("signalmastrepeater");
    if(!list.isEmpty())
    {
     DefaultSignalMastManager* m = (DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance();
     for (int i = 0; i < list.size(); i++)
     {
      QDomElement e = list.at(i).toElement();
      QString masterName = e.firstChildElement("masterMast").text();
      QString slaveName = e.firstChildElement("slaveMast").text();
      SignalMastRepeater* smr = new SignalMastRepeater(masterName, slaveName);
      if(!e.firstChildElement("enabled").isNull() && e.firstChildElement("enabled").text()==("false"))
        smr->setEnabled(false);
    if(!e.firstChildElement("update").isNull()){
        if(e.firstChildElement("update").text()==("MasterToSlave"))
            smr->setDirection(SignalMastRepeater::MASTERTOSLAVE);
        else if (e.firstChildElement("update").text()==("SlaveToMaster"))
            smr->setDirection(SignalMastRepeater::SLAVETOMASTER);
    }
    try
    {
        m->addRepeater(smr);
    } catch (JmriException ex)
    {
        log->error("Unable to add mast repeater " + masterName + " : " + slaveName);
    }
   }
  m->initialiseRepeaters();
 }
#endif
    return true;
}

/*public*/ void DefaultSignalMastManagerXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception) {
    log->error("Invalid method called");
}

/*public*/ int DefaultSignalMastManagerXml::loadOrder(){
    return InstanceManager::signalMastManagerInstance()->getXMLOrder();
}
