#include "abstractsignalheadmanagerxml.h"
#include "signalheadmanager.h"
#include "instancemanager.h"
#include "abstractsignalhead.h"
#include "signalhead.h"
#include "virtualsignalheadxml.h"
#include "doubleturnoutsignalheadxml.h"
#include "singleturnoutsignalheadxml.h"
#include "../LayoutEditor/configxmlmanager.h"
#include "abstractsignalheadmanager.h"
#include "tripleturnoutsignalheadxml.h"
#include "quadoutputsignalheadxml.h"
#include "se8csignalhead.h"
#include "se8csignalheadxml.h"

AbstractSignalHeadManagerXml::AbstractSignalHeadManagerXml(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("AbstractSignalHeadManagerXml");
 setObjectName("AbstractSignalHeadManagerXml");
}
AbstractSignalHeadManagerXml::~AbstractSignalHeadManagerXml()
{
 delete log;
}

/**
* Default implementation for storing the contents of a
* SignalHeadManager.
* <P>
* Unlike most other managers, the individual
* SignalHead objects are stored separately via the
* configuration system so they can have separate type
* information.
* @param o Object to store, of type SignalHeadManager
* @return Element containing the complete info
*/
/*public*/ QDomElement AbstractSignalHeadManagerXml::store(QObject* o) {
   QDomElement signalheads = doc.createElement("signalheads");
   setStoreElementClass(signalheads);
   SignalHeadManager* sm = (SignalHeadManager*) o;
   if (sm!=NULL)
   {
    QStringListIterator iter (((AbstractSignalHeadManager*)sm)->getSystemNameList());

    // don't return an element if there are not signalheads to include
    if (!iter.hasNext()) return QDomElement();

    // store the signalheads
    while (iter.hasNext())
    {
     QString sname = iter.next();
     if (sname=="") log->error("System name NULL during store");
     log->debug("system name is "+sname);
     SignalHead* sub = ((AbstractSignalHeadManager*)sm)->getBySystemName(sname);
     try
     {
      QDomElement e = ConfigXmlManager::elementFromObject(sub);
      if (!e.isNull())
       signalheads.appendChild(e);
     }
     catch (Exception ex)
     {
      log->error("Error storing signalhead: "+ex.getMessage());
               //e.printStackTrace();
     }
    }
   }
   return signalheads;
}

/**
* Subclass provides implementation to create the correct top
* element, includingh the type information.
* Default implementation is to use the local class here.
* @param turnouts The top-level element being created
*/
/*public*/ void AbstractSignalHeadManagerXml::setStoreElementClass(QDomElement turnouts)
{
 turnouts.setAttribute("class","jmri.managers.configurexml.AbstractSignalHeadManagerXml");
}

/**
* Create a SignalHeadManager object of the correct class, then
* register and fill it.
* @param signalheads Top level Element to unpack.
* @return true if successful
*/
/*public*/ bool AbstractSignalHeadManagerXml::load(QDomElement signalheads) throw (Exception)
{
   // create the master object
   replaceSignalHeadManager();

   // load individuahl turnouts
   loadSignalHeads(signalheads);
   return true;
}

/*public*/ void AbstractSignalHeadManagerXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception){
   log->error("Invalid method called");
}


/**
* Utility method to load the individual SignalHead objects.
* If there's no additional info needed for a specific signal head type,
* invoke this with the parent of the set of SignalHead elements.
* @param signalheads Element containing the SignalHead elements to load.
*/
//@SuppressWarnings("unchecked")
/*public*/ void AbstractSignalHeadManagerXml::loadSignalHeads(QDomElement signalheads)
{
   InstanceManager::signalHeadManagerInstance();

   // load the contents
   QDomNodeList items = signalheads.childNodes();
   if (log->isDebugEnabled()) log->debug("Found "+QString::number(items.size())+" signal heads");
   for (int i = 0; i<items.size(); i++) {
       // get the class, hence the adapter object to do loading
       QDomElement item = items.at(i).toElement();
       QString adapterName = item.attribute("class");
       log->debug("load via "+adapterName);
       //try {
//           XmlAdapter* adapter = (XmlAdapter*)Class.forName(adapterName).newInstance();
//           // and do it
//           adapter->load(item);
           if(adapterName == "jmri.implementation.configurexml.VirtualSignalHeadXml")
           {
               VirtualSignalHeadXml* adapter = new VirtualSignalHeadXml();
               adapter->load(item);
           }
           else if(adapterName == "jmri.implementation.configurexml.DoubleTurnoutSignalHeadXml")
           {
               DoubleTurnoutSignalHeadXml* adapter = new DoubleTurnoutSignalHeadXml();
               adapter->load(item);
           }
           else if(adapterName == "jmri.implementation.configurexml.SingleTurnoutSignalHeadXml")
           {
               SingleTurnoutSignalHeadXML* adapter = new SingleTurnoutSignalHeadXML();
               adapter->load(item);
           }
           else if(adapterName == "jmri.implementation.configurexml.SingleTurnoutSignalHeadXml")
           {
               TripleTurnoutSignalHeadXml* adapter = new TripleTurnoutSignalHeadXml();
               adapter->load(item);
           }
           else if(adapterName == "jmri.implementation.configurexml.QuadOutputSignalHeadXml")
           {
               QuadOutputSignalHeadXml* adapter = new QuadOutputSignalHeadXml();
               adapter->load(item);
           }
           else if(adapterName == "jmri.jmrix.loconet.configurexml.SE8cSignalHeadXml")
           {
               SE8cSignalHeadXml* adapter = new SE8cSignalHeadXml();
               adapter->load(item);
           }
           else
//       } catch (Exception e) {
           /*public*/log->error("Exception while loading "+item.tagName()/*+":"+e.getMessage()*/);
           //e.printStackTrace();
 }
}

/**
* Replace the current signal head manager, if there is one, with
* one newly created during a load operation. This is skipped
* if they are of the same absolute type.
*/
/*protected*/ void AbstractSignalHeadManagerXml::replaceSignalHeadManager()
{
 if (InstanceManager::signalHeadManagerInstance() != NULL && QString(InstanceManager::signalHeadManagerInstance()->metaObject()->className())
           ==("AbstractSignalHeadManager"))
  return;
 // if old manager exists, remove it from configuration process
 if (InstanceManager::signalHeadManagerInstance() != NULL)
 {
  if(InstanceManager::configureManagerInstance() == NULL)
      InstanceManager::setConfigureManager((ConfigureManager*)new ConfigXmlManager);
  ((ConfigXmlManager*) InstanceManager::configureManagerInstance())->deregister(InstanceManager::signalHeadManagerInstance() );
 }

 // register new one with InstanceManager
 AbstractSignalHeadManager* pManager = new AbstractSignalHeadManager();
 InstanceManager::setSignalHeadManager((SignalHeadManager*)pManager);
 // register new one for configuration
 ((ConfigXmlManager*)InstanceManager::configureManagerInstance())->registerConfig(pManager, Manager::SIGNALHEADS);
}

/*public*/ int AbstractSignalHeadManagerXml::loadOrder()
{
 return ((AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance())->getXMLOrder();
}
