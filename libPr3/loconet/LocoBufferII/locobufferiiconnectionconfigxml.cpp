#include "locobufferiiconnectionconfigxml.h"
#include "locobufferiiadapter.h"
#include "connectionconfig.h"
#include "locobufferiiconnectionconfig.h"
#include "instancemanager.h"
#include "appsconfigurationmanager.h"

/**
 * Handle XML persistance of layout connections by persisting the
 * LocoBufferAdapter (and connections). Note this is named as the XML version of
 * a ConnectionConfig object, but it's actually persisting the
 * LocoBufferAdapter.
 * <p>
 * This class is invoked from jmrix.JmrixConfigPaneXml on write, as that class
 * is the one actually registered. Reads are brought here directly via the class
 * attribute in the XML.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 */
// public class ConnectionConfigXml extends AbstractSerialConnectionConfigXml {

    /*public*/ LocoBufferIIConnectionConfigXml::LocoBufferIIConnectionConfigXml(QObject* parent)
     : AbstractSerialConnectionConfigXml(parent){
       // super();
    }

    //@Override
    /*protected*/ void LocoBufferIIConnectionConfigXml::getInstance() {
        adapter = new LocoBufferIIAdapter();
    }

    //@Override
    /*protected*/ void LocoBufferIIConnectionConfigXml::getInstance(QObject* object) {
        adapter = (SerialPortAdapter*)((LocoBufferIIConnectionConfig*) object)->getAdapter();
    }

    //@Override
    /*protected*/ void LocoBufferIIConnectionConfigXml::_register() {
        //this->_register(new LocoBufferIIConnectionConfig(adapter));
     ConnectionConfig* c;
     qobject_cast<AppsConfigurationManager*>(InstanceManager::getDefault("ConfigureManager"))->registerPref(c = (ConnectionConfig*)new LocoBufferIIConnectionConfig((LocoBufferIIAdapter*)adapter, NULL));
     AbstractConnectionConfigXml::_register(c);

    }


