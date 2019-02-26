#include "lnovertcpconnectionconfig.h"
#include "../lntcpdriveradapter.h"
#include "../networkportadapter.h"

LnOverTcpConnectionConfig::LnOverTcpConnectionConfig(QObject *parent) :
  AbstractNetworkConnectionConfig(parent)
{
 setObjectName("LnOverTcpConnectionConfig");
}
/**
 * Definition of objects to handle configuring a LocoNetOverTcp layout
 * connection via a LnTcpDriverAdapter object.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2003
 * @author Stephen Williams Copyright (C) 2008
 *
 * @version $Revision: 28746 $
 */
// /*public*/ class ConnectionConfig extends jmri.jmrix.AbstractNetworkConnectionConfig {

/**
 * Ctor for an object being created during load process; Swing init is
 * deferred.
 */
/*public*/ LnOverTcpConnectionConfig::LnOverTcpConnectionConfig(NetworkPortAdapter* p, QObject *parent) :
  AbstractNetworkConnectionConfig(p, parent)
{
 //super(p);
 setObjectName("LnOverTcpConnectionConfig");
 setProperty("JavaClassName", "jmri.jmrix.loconet.loconetovertcp.ConnectionConfig");
}
/**
 * Ctor for a functional Swing object with no prexisting adapter
 */
///*public*/ ConnectionConfig() {
//    super();
//}

/*public*/ QString LnOverTcpConnectionConfig::name()
{
 return "LocoNetOverTcp LbServer";
}

/*public*/ bool LnOverTcpConnectionConfig::isOptList1Advanced()
{
 return false;
}

/*protected*/ void LnOverTcpConnectionConfig::setInstance()
{
 if (adapter == NULL)
 {
  adapter = (NetworkPortAdapter*)new LnTcpDriverAdapter();
  adapter->setPort(1234);
 }
}
