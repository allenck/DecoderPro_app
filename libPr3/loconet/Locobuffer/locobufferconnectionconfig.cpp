#include "locobufferconnectionconfig.h"
#include "locobufferadapter.h"

LocobufferConnectionConfig::LocobufferConnectionConfig(QObject *parent) :
    AbstractSerialConnectionConfig(parent)
{
 setObjectName("LocobufferConnectionConfig");
}
/**
 * Definition of objects to handle configuring an LocoBuffer layout connection
 * via a LocoBufferAdapter object.
 *
 * @author      Bob Jacobsen   Copyright (C) 2001, 2003, 2010
 * @version	$Revision: 17977 $
 */
// /*public*/ class ConnectionConfig  extends jmri.jmrix.AbstractSerialConnectionConfig {

/**
 * Ctor for an object being created during load process;
 * Swing init is deferred.
 */
/*public*/ LocobufferConnectionConfig::LocobufferConnectionConfig(SerialPortAdapter* p, QObject *parent)
    : AbstractSerialConnectionConfig((PortAdapter*)p, parent)
{
    //super(p);
 setObjectName("LocobufferConnectionConfig");
}
///**
// * Ctor for a functional Swing object with no prexisting adapter
// */
///*public*/ ConnectionConfig() {
//    super();
//}
LocobufferConnectionConfig::LocobufferConnectionConfig(const LocobufferConnectionConfig &other) : AbstractSerialConnectionConfig()
{
 this->p = other.p;
}

/*public*/ bool LocobufferConnectionConfig::isOptList2Advanced() { return false; }

/*public*/ QString LocobufferConnectionConfig::name() { return "LocoNet LocoBuffer"; }

/*protected*/ void LocobufferConnectionConfig::setInstance()
{
 if (adapter == NULL)
 {
   adapter = new LocoBufferAdapter();
 }
}
