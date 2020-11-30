#include "abstractnetworkconnectionconfigxml.h"
#include "loconet/networkportadapter.h"
#include "abstractnetworkportcontroller.h"

AbstractNetworkConnectionConfigXml::AbstractNetworkConnectionConfigXml(QObject *parent) :
  AbstractConnectionConfigXml(parent)
{
 log = new Logger("AbstractNetworkConnectionConfigXml");
}
/**
 * Abstract base (and partial implementation) for classes persisting the status
 * of Network port adapters.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @version $Revision: 28746 $
 */
///*abstract*/ /*public*/ class AbstractNetworkConnectionConfigXml extends AbstractConnectionConfigXml {

///*public*/ AbstractNetworkConnectionConfigXml() {
//}

//final static protected java.util.ResourceBundle rb
//        = java.util.ResourceBundle.getBundle("jmri.jmrix.JmrixBundle");


/*abstract*/ /*protected*/ void AbstractNetworkConnectionConfigXml::getInstance() {}

/*abstract*/ /*protected*/ void AbstractNetworkConnectionConfigXml::_register() {}

/*protected*/ void AbstractNetworkConnectionConfigXml::getInstance(QObject* object) {
 getInstance(); // over-ridden during migration
}

/*public*/ QDomElement AbstractNetworkConnectionConfigXml::store(QObject* o, bool /*shared*/)
{
 return this->store(o);
}

/**
 * Default implementation for storing the static contents of the Network
 * port implementation
 *
 * @param o Object to store, of type PositionableLabel
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement AbstractNetworkConnectionConfigXml::store(QObject* o) //throw (Exception)
{
 getInstance(o);

 QDomElement e = doc.createElement("connection");
 // many of the following are required by the DTD; failing to include
 // them makes the XML file unreadable, but at least the next
 // invocation of the program can then continue.
 e.setAttribute("xmlns", "");

 storeCommon(e, adapter);

 if (adapter->getMdnsConfigure() == true)
 {
  // if we are using mDNS for configuration, only save
  // the hostname if it was specified.
  if (adapter->getHostName() != "" && adapter->getHostName()!=(""))
  {
   e.setAttribute("address", adapter->getHostName());
  }

  e.setAttribute("mdnsConfigure", "true");
  if (adapter->getAdvertisementName() != "")
  {
   e.setAttribute("advertisementName", adapter->getAdvertisementName());
  }
  if (adapter->getServiceType() != "")
  {
   e.setAttribute("serviceType", adapter->getServiceType()); // e.g. "_loconetovertcpserver._tcp"
  }

 }
 else
 {
  e.setAttribute("mdnsConfigure", "false");

  // require a value for the address if we are not using mDNS.
  if (adapter->getHostName() != "")
  {
   e.setAttribute("address", adapter->getHostName());
  }
  else
  {
   e.setAttribute("address", tr("(none selected)"));
  }

  // write the port only if we are not using automatic configuration.
  if (adapter->getPort() != 0)
  {
   e.setAttribute("port",  adapter->getPort());
  }
  else
  {
   e.setAttribute("port", tr("(none selected)"));
  }
 }

 QString className = this->metaObject()->className();
 QString  javaClassName = javaClass();
 // JMRI uses a className with the name "ConnectionConfigXml" for all adapters but stores them in
 // different directories. So, we have to retore the name that JMRI uses.
 if(className == "LnOverTcpConnectionConfigXml")
  javaClassName = "jmri.jmrix.loconet.loconetovertcp.configurexml.ConnectionConfigXml";
 else if(className == "HexFileConnectionConfigXml" )
  javaClassName = "jmri.jmrix.loconet.hexfile.configurexml.ConnectionConfigXml";
 else if(className == "LocobufferUsbConnectionConfigXml" )
  javaClassName = "jmri.jmrix.loconet.pr3.configurexml.ConnectionConfigXml";
 else if(className == "ConnectionConfigXml" )
  javaClassName = "jmri.jmrix.loconet.pr3.configurexml.ConnectionConfigXml";
 else if(className == "LocobufferUsbConnectionConfigXml" )
  javaClassName = "jmri.jmrix.loconet.locobufferusb.configurexml.ConnectionConfigXml";
 e.setAttribute("class", javaClassName);

 extendElement(e);

 return e;
}

/**
 * Customizable method if you need to add anything more
 *
 * @param e QDomElement being created, update as needed
 */
/*protected*/ void AbstractNetworkConnectionConfigXml::extendElement(QDomElement e) {
}

//@Override
/*public*/ bool AbstractNetworkConnectionConfigXml::load(QDomElement shared, QDomElement perNode) //throws Exception
{
 bool result = true;
 getInstance();

 bool mdnsConfig = false;
 try {
     mdnsConfig = (shared.attribute("mdnsConfigure") == ("true"));
  }
  catch (NullPointerException ex) {  // considered normal if the attributes are not present
 }
 adapter->setMdnsConfigure(mdnsConfig);

 if (mdnsConfig)
 {

  // configure host name
  QString hostName = NULL;
  try {
      hostName = shared.attribute("address");
      // the hostname is optional when mDNS is being used.
      adapter->setHostName(hostName);
  } catch (NullPointerException ex) {  // considered normal if the attributes are not present
  }

  // configure the Service Type
  QString serviceType = NULL;
  try {
      serviceType = shared.attribute("serviceType");
      // the Service Type is optional when mDNS is being used.
      adapter->setServiceType(serviceType);
  } catch (NullPointerException ex) {  // considered normal if the attributes are not present
  }

  // configure the advertisement name
  QString advertisementName = "";
  try {
      advertisementName = shared.attribute("advertisementName");
      // the Advertisement Name is optional when mDNS is being used.
      adapter->setAdvertisementName(advertisementName);
  } catch (NullPointerException ex) {  // considered normal if the attributes are not present
  }

  // get the host IP and port number
  // via mdns
   adapter->autoConfigure();

 }
 else
 {
  // get the host name and port number via parameters.

  // configure host name
  QString hostName = NULL;
  try
  {
      hostName = shared.attribute("address");
  }
  catch (NullPointerException ex) {  // considered normal if the attributes are not present
  }
  adapter->setHostName(hostName);

  bool ok;
  int port = shared.attribute("port").toInt(&ok);
  adapter->setPort(port);
  if(!ok) {
  log->warn("Could not parse port attribute");
  }
//   catch (NullPointerException ex) {  // considered normal if the attributes are not present
//   }
 }

 loadCommon(shared, perNode, adapter);
 // register, so can be picked up next time
 this->_register();

 if (adapter->getDisabled()) {
     unpackElement(shared, perNode);
     return result;
 }
 try {
  if(this->adapter->getMdnsConfigure())
  {
   this->adapter->autoConfigure();
  }
  ((PortAdapter*)this->adapter)->_connect();
 }
 catch (Exception ex) {
     ConfigXmlManager::creationErrorEncountered(
             NULL, "opening connection",
             ex.getMessage(),
             NULL, NULL, NULL
     );
     return false;
 }

 // if successful so far, go ahead and configure
 adapter->configure();

 // once all the configure processing has happened, do any
 // extra config
 unpackElement(shared, perNode);
 return result;
}

/**
 * Update static data from XML file
 *
 * @param element Top level QDomElement to unpack.
 */
/*public*/ void AbstractNetworkConnectionConfigXml::load(QDomElement element, QObject* o) throw (Exception) {
    log->error("method with two args invoked");
}
