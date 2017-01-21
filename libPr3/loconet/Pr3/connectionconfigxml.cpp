#include "connectionconfigxml.h"
#include "pr3adapter.h"
#include "instancemanager.h"
#include "pr3connectionconfig.h"

ConnectionConfigXml::ConnectionConfigXml(QObject *parent) :
    AbstractSerialConnectionConfigXml(parent)
{
 setObjectName("ConnectionConfigXml(Pr3)");
}
/**
 * Handle XML persistance of layout connections by persisting
 * the PR3Adapter (and connections). Note this is
 * named as the XML version of a ConnectionConfig object,
 * but it's actually persisting the PR3Adapter.
 * <P>
 * This class is invoked from jmrix.JmrixConfigPaneXml on write,
 * as that class is the one actually registered. Reads are brought
 * here directly via the class attribute in the XML.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003, 2005, 2006, 2008
 * @version $Revision: 22821 $
 */
// /*public*/ class ConnectionConfigXml extends AbstractSerialConnectionConfigXml {

///*public*/ ConnectionConfigXml::ConnectionConfigXml() {
//    //super();
//}

/*protected*/ void ConnectionConfigXml::getInstance()
{
 adapter = /*(SerialPortAdapter*)*/new PR3Adapter();
}

/*protected*/ void ConnectionConfigXml::getInstance(QObject* object)
{
 adapter = (SerialPortAdapter*)((ConnectionConfig*)object)->getAdapter();
}

/*protected*/ void ConnectionConfigXml::_register()
{
 InstanceManager::configureManagerInstance()->registerPref(new Pr3ConnectionConfig((PR3Adapter*)adapter, NULL));
}
