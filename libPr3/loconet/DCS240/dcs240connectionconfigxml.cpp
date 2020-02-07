#include "dcs240connectionconfigxml.h"
#include "dcs240connectionconfig.h"
#include "usbdcs240adapter.h"

/**
 * Handle XML persistance of layout connections by persisting the UsbDcs240Adapter
 * (and connections). Note this is named as the XML version of a
 * ConnectionConfig object, but it's actually persisting the UsbDcs240Adapter.
 * <p>
 * This class is invoked from jmrix.JmrixConfigPaneXml on write, as that class
 * is the one actually registered. Reads are brought here directly via the class
 * attribute in the XML.
 *
 * Based on loconet.pr3.configurexml.ConnectionConfigXml.java
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003, 2005, 2006, 2008
 * @author B. Milhaupt Copyright (C) 2019
 */
// /*public*/ class ConnectionConfigXml extends AbstractSerialConnectionConfigXml {

/*public*/ DCS240ConnectionConfigXml::DCS240ConnectionConfigXml(QObject *parent)
 : AbstractSerialConnectionConfigXml(parent)
{
    //super();
}

//@Override
/*protected*/ void DCS240ConnectionConfigXml::getInstance() {
    adapter = new UsbDcs240Adapter();
}

//@Override
/*protected*/ void DCS240ConnectionConfigXml::getInstance(QObject* object) {
    adapter = (SerialPortAdapter*)((DCS240ConnectionConfig*) object)->getAdapter();
}

//@Override
/*protected*/ void DCS240ConnectionConfigXml::_register() {
    AbstractConnectionConfigXml::_register(new DCS240ConnectionConfig(adapter));
}
