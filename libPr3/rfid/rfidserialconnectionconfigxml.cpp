#include "rfidserialconnectionconfigxml.h"
#include "loggerfactory.h"
#include "rfidserialdriveradapter.h"
#include "rfidserialconnectionconfig.h"

/**
 * Handle XML persistence of layout connections by persisting the
 * SerialDriverAdapter (and connections). Note this is named as the XML version
 * of a ConnectionConfig object, but it's actually persisting the
 * SerialDriverAdapter.
 * <P>
 * This class is invoked from jmrix.JmrixConfigPaneXml on write, as that class
 * is the one actually registered. Reads are brought here directly via the class
 * attribute in the XML.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003, 2006, 2007, 2008
 * @author Matthew Harris Copyright (C) 2011
 * @since 2.11.4
 */
// /*public*/ class ConnectionConfigXml extends AbstractSerialConnectionConfigXml {

    /*public*/ RfidSerialConnectionConfigXml::RfidSerialConnectionConfigXml(QObject* parent) : AbstractSerialConnectionConfigXml(parent) {
        //super();
    }

    //@Override
    /*protected*/ void RfidSerialConnectionConfigXml::getInstance() {
        log->debug("getInstance without parameter called");
        adapter = new RfidSerialDriverAdapter();
    }

    //@Override
    /*protected*/ void RfidSerialConnectionConfigXml::getInstance(QObject* object) {
        log->debug("getInstance with parameter called");
        adapter = (SerialPortAdapter*)((RfidSerialConnectionConfig*) object)->getAdapter();
    }

    //@Override
    /*protected*/ void RfidSerialConnectionConfigXml::_register() {
        AbstractSerialConnectionConfigXml::_register(new RfidSerialConnectionConfig(adapter));
    }

    /*private*/ /*final*/ /*static*/ Logger* RfidSerialConnectionConfigXml::log = LoggerFactory::getLogger("RfidSerialConnectionConfigXml");

