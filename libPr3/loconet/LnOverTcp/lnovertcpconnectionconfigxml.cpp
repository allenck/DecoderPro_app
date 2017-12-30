#include "lnovertcpconnectionconfigxml.h"
#include "instancemanager.h"
#include "lnovertcpconnectionconfig.h"
#include "../lntcpdriveradapter.h"
#include "connectionconfigmanager.h"

LnOverTcpConnectionConfigXml::LnOverTcpConnectionConfigXml(QObject *parent) :
  AbstractNetworkConnectionConfigXml(parent)
{
}
/**
 * Handle XML persistance of layout connections by persistening the
 * LnTcpDriverAdapter (and connections).
 * <P>
 * Note this is named as the XML version of a ConnectionConfig object, but it's
 * actually persisting the LnTcpDriverAdapter.
 * <P>
 * This class is invoked from jmrix.JmrixConfigPaneXml on write, as that class
 * is the one actually registered. Reads are brought here directly via the class
 * attribute in the XML.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @version $Revision: 28746 $
 */
///*public*/ class ConnectionConfigXml extends AbstractNetworkConnectionConfigXml {

///*public*/ ConnectionConfigXml() {
//    super();
//}

/*protected*/ void LnOverTcpConnectionConfigXml::getInstance()
{
 adapter = (NetworkPortAdapter*)new LnTcpDriverAdapter();
}

/*protected*/ void LnOverTcpConnectionConfigXml::getInstance(QObject* object)
{
 adapter =  (NetworkPortAdapter*)((LnOverTcpConnectionConfig*) object)->getAdapter();
}

/*protected*/ void LnOverTcpConnectionConfigXml::_register()
{
 // begin dups fix to prevent connection from being duplicated.
  ConnectionConfigManager* ccm = (ConnectionConfigManager*)InstanceManager::getNullableDefault("ConnectionConfigManager");
  foreach (ConnectionConfig* c, *ccm->getConnections())
  {
   if(qobject_cast<LnOverTcpConnectionConfig*>(c) != NULL)
   {
    NetworkPortAdapter* adapter1 = ((NetworkPortAdapter*)((LnOverTcpConnectionConfig*)c)->getAdapter());
    if(adapter->getHostName() == adapter1->getHostName()  && adapter ->getCurrentPortName() == adapter1->getCurrentPortName())
     return;  //already is registered.
   }
  }
  //end dups fix
 ConnectionConfig* c = (ConnectionConfig*)new LnOverTcpConnectionConfig(adapter);
 AbstractConnectionConfigXml::_register(c);
}
