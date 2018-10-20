#include "abstractserialconnectionconfigxml.h"
#include "serialportadapter.h"

AbstractSerialConnectionConfigXml::AbstractSerialConnectionConfigXml(QObject *parent) :
    AbstractConnectionConfigXml(parent)
{
 log = new Logger("AbstractSerialConnectionConfigXml");
 adapter = NULL;
}
/**
 * Abstract base (and partial implementation) for
 * classes persisting the status of serial port adapters.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @version $Revision: 27930 $
 */
//abstract /*public*/ class AbstractSerialConnectionConfigXml extends AbstractConnectionConfigXml {

///*public*/ AbstractSerialConnectionConfigXml() {
//}

//final static /*protected*/ java.util.ResourceBundle rb =
//    java.util.ResourceBundle.getBundle("jmri.jmrix.JmrixBundle");

/*abstract*/ /*protected*/ void AbstractSerialConnectionConfigXml::getInstance() {}
/*abstract*/ /*protected*/ void AbstractSerialConnectionConfigXml::_register() {}
/*protected*/ void AbstractSerialConnectionConfigXml::getInstance(QObject* /*object*/)
{
 getInstance(); // over-ridden during migration
}
QDomElement AbstractSerialConnectionConfigXml::store(QObject* o, bool /*shared*/)
{
 return this->store(o);
}


/**
 * Default implementation for storing the static contents of the serial port implementation
 * @param object Object to store, of type PositionableLabel
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement AbstractSerialConnectionConfigXml::store(QObject* object)
{
 getInstance(object);
 QDomElement e = doc.createElement("connection");

 // many of the following are required by the DTD; failing to include
 // them makes the XML file unreadable, but at least the next
 // invocation of the program can then continue.
 storeCommon(e, adapter);

 if (adapter->getCurrentPortName()!=NULL)
  e.setAttribute("port", adapter->getCurrentPortName().trimmed());
 else e.setAttribute("port", tr("(none selected)"));

 if (adapter->getCurrentBaudRate()!=NULL)
  e.setAttribute("speed", adapter->getCurrentBaudRate());
 else e.setAttribute("speed", tr("(none selected)"));

 //e.setAttribute("class", /*this.getClass().getName()*/this->metaObject()->className());
 QString className = this->metaObject()->className();
 QString  javaClassName = javaClass();
 if(javaClassName == "")
 {
  // JMRI uses a className with the name "ConnectionConfigXml" for all adapters but stores them in
  // different directories. So, we have to restore the name that JMRI uses.
  if(className == "LnOverTcpConnectionConfigXml")
   javaClassName = "jmri.jmrix.loconet.loconetovertcp.configurexml.ConnectionConfigXml";
  else if(className == "HexFileConnectionConfigXml" )
   javaClassName = "jmri.jmrix.loconet.hexfile.configurexml.ConnectionConfigXml";
  else if(className == "LocobufferConnectionConfigXml" )
   javaClassName = "jmri.jmrix.loconet.locobuffer.configurexml.ConnectionConfigXml";
  else if(className == "LocobufferUsbConnectionConfigXml" )
   javaClassName = "jmri.jmrix.loconet.locobufferusb.configurexml.ConnectionConfigXml";
  else if(className == "ConnectionConfigXml" )
   javaClassName = "jmri.jmrix.loconet.pr3.configurexml.ConnectionConfigXml";
  else if(className == "SprogConnectionConfigXml" )
   javaClassName = "jmri.jmrix.sprog.sprog.configurexml.ConnectionConfigXml";
  else if(className == "SprogCSConnectionConfigXml" )
   javaClassName = "jmri.jmrix.sprog.sprogCS.configurexml.ConnectionConfigXml";
 }

 e.setAttribute("class", javaClassName);

 extendElement(e);

 return e;
}

/**
 * Customizable method if you need to add anything more
 * @param e QDomElement being created, update as needed
 */
/*protected*/ void AbstractSerialConnectionConfigXml::extendElement(QDomElement /*e*/) {}
//@Override
/*public*/ bool AbstractSerialConnectionConfigXml::load(QDomElement shared, QDomElement perNode) //throws Exception
{
    bool result = true;
    getInstance();
    // configure port name
    QString portName = perNode.attribute("port");
     adapter->setPort(portName);
    QString baudRate = perNode.attribute("speed");
     adapter->configureBaudRate(baudRate);
    QString manufacturer = perNode.attribute("manufacturer");
     adapter->setManufacturer(manufacturer);


    loadCommon(shared, perNode, adapter);
    // register, so can be picked up next time
    _register();
    // try to open the port
    if ( adapter->getDisabled()) {
        unpackElement(shared, perNode);
        return result;
    }
    QString status =  adapter->openPort(portName, "JMRI app");
    if (status != NULL)
    {
     // indicates an error, return it
     ConfigXmlManager::creationErrorEncountered(
             NULL, "opening connection",
             status,
             NULL, NULL, NULL
     );
     // now force end to operation
     log->debug("load failed");
     return false;
    }

    // if successful so far, go ahead and configure
     adapter->configure();

    // once all the configure processing has happened, do any
    // extra config
    unpackElement(shared, perNode);
    return result;
}
#if 0
/**
 * Customizable method if you need to add anything more
 * @param e QDomElement being created, update as needed
 */
/*protected*/ void AbstractSerialConnectionConfigXml::unpackElement(QDomElement e) {}
#endif
/**
 * Update static data from XML file
 * @param element Top level QDomElement to unpack.
  */
/*public*/ void AbstractSerialConnectionConfigXml::load(QDomElement element, QObject* o) throw (Exception)
{
 Logger::error("method with two args invoked");
}
