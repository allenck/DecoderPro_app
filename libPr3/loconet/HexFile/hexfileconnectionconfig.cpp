#include "hexfileconnectionconfig.h"
#include "lnhexfileport.h"

HexFileConnectionConfig::HexFileConnectionConfig(QObject *parent) :
    AbstractSimulatorConnectionConfig(parent)
{
 setObjectName("HexFileConnectionConfig");
}
/**
 * Definition of objects to handle configuring a layout connection
 * via a LocoNet hexfile emulator
 *
 * @author      Bob Jacobsen   Copyright (C) 2001, 2003
 * @version	$Revision: 17977 $
 */
///*public*/ class ConnectionConfig  extends jmri.jmrix.AbstractSimulatorConnectionConfig {

/**
 * Ctor for an object being created during load process;
 * Swing init is deferred.
 */
/*public*/ HexFileConnectionConfig::HexFileConnectionConfig(SerialPortAdapter* p, QObject *parent) :
    AbstractSimulatorConnectionConfig(p, parent){
    //super(p);
 setObjectName("HexFileConnectionConfig");
}
/**
 * Ctor for a functional Swing object with no prexisting adapter
 */
///*public*/ ConnectionConfig() {
//    super();
//}

/*public*/ QString HexFileConnectionConfig::name() { return "LocoNet Simulator"; }

/*protected*/ void HexFileConnectionConfig::setInstance() {
    if (adapter == NULL){
        adapter = new LnHexFilePort();
    }
}

/*public*/ void HexFileConnectionConfig::dispose() {
    if (adapter != NULL)
        adapter->dispose();
    AbstractSimulatorConnectionConfig::dispose();
}
