#include "jmriclientconnectionconfigxml.h"
#include "networkdriveradapter.h"
#include "jmriclientconnectionconfig.h"
#include "jmriclientsystemconnectionmemo.h"

/**
 * Handle XML persistance of layout connections by persistening the
 * NetworkDriverAdapter (and connections).
 * <P>
 * Note this is named as the XML version of a ConnectionConfig object, but it's
 * actually persisting the NetworkDriverAdapter.
 * <P>
 * This class is invoked from jmrix.JmrixConfigPaneXml on write, as that class
 * is the one actually registered. Reads are brought here directly via the class
 * attribute in the XML.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @author Paul Bender Copyright: Copyright (c) 2010
 */
// /*public*/ class ConnectionConfigXml extends AbstractNetworkConnectionConfigXml {

/*public*/ JMRIClientConnectionConfigXml::JMRIClientConnectionConfigXml(QObject* parent) : AbstractNetworkConnectionConfigXml(parent){
   //super();
 setProperty("javaClassName", "jmri.jmrix.jmriclient.networkdriver.configurexml.ConnectionConfigXml");
}

//@Override
/*protected*/ void JMRIClientConnectionConfigXml::getInstance() {
    if (adapter == nullptr) {
        adapter = new NetworkDriverAdapter();
    }
}

//@Override
/*protected*/ void JMRIClientConnectionConfigXml::getInstance(QObject* object) {
    adapter = (NetworkPortAdapter*)((JMRIClientConnectionConfig*) object)->getAdapter();
}

//@Override
/*protected*/ void JMRIClientConnectionConfigXml::_register() {
    AbstractConnectionConfigXml::_register((ConnectionConfig*)new JMRIClientConnectionConfig(adapter));
}

/**
 * Customizable method if you need to add anything more
 *
 * @param e Element being created, update as needed
 */
//@Override
/*protected*/ void JMRIClientConnectionConfigXml::extendElement(QDomElement e) {
    if (adapter->getSystemConnectionMemo() != nullptr) {
        e.setAttribute("transmitPrefix", ((JMRIClientSystemConnectionMemo*) adapter->getSystemConnectionMemo())->getTransmitPrefix());
    }
}

//@Override
/*protected*/ void JMRIClientConnectionConfigXml::unpackElement(QDomElement shared, QDomElement perNode) {
    if (shared.attribute("transmitPrefix") != "") {
        ((JMRIClientSystemConnectionMemo*) adapter->getSystemConnectionMemo())->setTransmitPrefix(shared.attribute("transmitPrefix"));
    }
}

/*protected*/ QString JMRIClientConnectionConfigXml::javaClass()
{
 return "jmri.jmrix.jmriclient.networkdriver.configurexml.ConnectionConfigXml";
}


