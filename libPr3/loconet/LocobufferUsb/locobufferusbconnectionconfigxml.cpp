#include "locobufferusbconnectionconfigxml.h"
#include "instancemanager.h"
#include "locobufferusbconnectionconfig.h"
#include "locobufferusbadapter.h"

LocobufferUsbConnectionConfigXml::LocobufferUsbConnectionConfigXml(QObject *parent) :
    AbstractSerialConnectionConfigXml(parent)
{
}
/**
 * Handle XML persistance of layout connections by persisting
 * the LocoBufferUSBAdapter (and connections). Note this is
 * named as the XML version of a ConnectionConfig object,
 * but it's actually persisting the LocoBufferAdapterUSB.
 * <P>
 * This class is invoked from jmrix.JmrixConfigPaneXml on write,
 * as that class is the one actually registered. Reads are brought
 * here directly via the class attribute in the XML.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003, 2005, 2006
 * @version $Revision: 22821 $
 */
 // /*public*/ class ConnectionConfigXml extends AbstractSerialConnectionConfigXml {

// /*public*/ ConnectionConfigXml() {
//    super();
//}

/*protected*/ void LocobufferUsbConnectionConfigXml::getInstance() {
 adapter = new LocoBufferUsbAdapter();
}
/*protected*/ void LocobufferUsbConnectionConfigXml::getInstance(QObject* object) {
 adapter = (SerialPortAdapter*)((LocobufferUsbConnectionConfig*)object)->getAdapter();
}

/*protected*/ void LocobufferUsbConnectionConfigXml::_register()
{
 InstanceManager::configureManagerInstance()->registerPref(new LocobufferUsbConnectionConfig(adapter));
}
