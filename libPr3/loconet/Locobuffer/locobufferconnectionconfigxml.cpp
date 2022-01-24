#include "locobufferconnectionconfigxml.h"
#include "locobufferadapter.h"
#include "locobufferconnectionconfig.h"
#include "instancemanager.h"
#include "appsconfigurationmanager.h"

LocobufferConnectionConfigXml::LocobufferConnectionConfigXml(QObject *parent) :
    AbstractSerialConnectionConfigXml(parent)
{
}
/**
 * Handle XML persistance of layout connections by persistening
 * the LocoBufferAdapter (and connections). Note this is
 * named as the XML version of a ConnectionConfig object,
 * but it's actually persisting the LocoBufferAdapter.
 * <P>
 * This class is invoked from jmrix.JmrixConfigPaneXml on write,
 * as that class is the one actually registered. Reads are brought
 * here directly via the class attribute in the XML.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @version $Revision: 22821 $
 */
 // /*public*/ class ConnectionConfigXml extends AbstractSerialConnectionConfigXml {

// /*public*/ ConnectionConfigXml() {
//    super();
//}

/*protected*/ void LocobufferConnectionConfigXml::getInstance() {
    adapter = new LocoBufferAdapter();
}
/*protected*/ void LocobufferConnectionConfigXml::getInstance(QObject* object) {
    adapter = (SerialPortAdapter*)((LocobufferConnectionConfig*)object)->getAdapter();
}

/*protected*/ void LocobufferConnectionConfigXml::_register() {
    qobject_cast<AppsConfigurationManager*>(InstanceManager::getDefault("ConfigureManager"))->registerPref(new LocobufferConnectionConfig(adapter));
}
