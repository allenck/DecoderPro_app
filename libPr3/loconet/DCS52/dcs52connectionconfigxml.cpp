#include "dcs52connectionconfigxml.h"
#include "usbdcs52adapter.h"
#include "dcs52connectionconfig.h"

DCS52ConnectionConfigXml::DCS52ConnectionConfigXml(QObject* parent)
{

}
/**
 * Handle XML persistance of layout connections by persisting the UsbDcs52Adapter
 * (and connections). Note this is named as the XML version of a
 * ConnectionConfig object, but it's actually persisting the UsbDcs52Adapter.
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
//public class ConnectionConfigXml extends AbstractSerialConnectionConfigXml {

    //@Override
    /*protected*/ void DCS52ConnectionConfigXml::getInstance() {
        adapter = new UsbDcs52Adapter();
    }

    //@Override
    /*protected*/ void DCS52ConnectionConfigXml::getInstance(QObject* object) {
        adapter = (SerialPortAdapter*)((DCS52ConnectionConfig*) object)->getAdapter();
    }

    //@Override
    /*protected*/ void DCS52ConnectionConfigXml::_register() {
//        super.register(new ConnectionConfig(adapter));
     AbstractConnectionConfigXml::_register(new DCS52ConnectionConfig(adapter));
    }