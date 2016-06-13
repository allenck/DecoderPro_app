#include "locobufferusbconnectionconfig.h"
#include "locobufferusbadapter.h"

LocobufferUsbConnectionConfig::LocobufferUsbConnectionConfig(QObject *parent) :
    AbstractSerialConnectionConfig(parent)
{
 //qRegisterMetaType<LocobufferUsbConnectionConfig>("LocobufferUsbConnectionConfig");
 adapter = NULL;
 setObjectName("LocobufferUsbConnectionConfig");
}
/**
 * Definition of objects to handle configuring an LocoBuffer-Usb layout connection
 * via a LocoBufferIIAdapter object.
 *
 * @author      Bob Jacobsen   Copyright (C) 2001, 2003
 * @version	$Revision: 21848 $
 */
 // /*public*/ class ConnectionConfig  extends jmri.jmrix.AbstractSerialConnectionConfig {

/**
 * Ctor for an object being created during load process;
 * Swing init is deferred.
 */
 /*public*/ LocobufferUsbConnectionConfig::LocobufferUsbConnectionConfig(SerialPortAdapter* p, QObject *parent)
    : AbstractSerialConnectionConfig((PortAdapter*)p, parent)
{
 //super(p);
    qRegisterMetaType<LocobufferUsbConnectionConfig>("LocobufferUsbConnectionConfig");

}
/**
 * Ctor for a functional Swing object with no prexisting adapter
 */
// /*public*/ ConnectionConfig() {
//    super();
//}

/*public*/ QString LocobufferUsbConnectionConfig::name() { return "LocoNet LocoBuffer-USB"; }

/*public*/ bool LocobufferUsbConnectionConfig::isOptList2Advanced() { return false; }

/*protected*/ void LocobufferUsbConnectionConfig::setInstance()
{
 if (adapter == NULL)
  adapter = new LocoBufferUsbAdapter();
}

//@Override
/*protected*/ QStringList LocobufferUsbConnectionConfig::getPortFriendlyNames() {
//    if(SystemType.isWindows()){
//        return new String[]{"LocoBuffer-USB","LocoBuffer"};
//    }
    return QStringList();
}

