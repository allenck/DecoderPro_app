#include "sprogcsconnectionconfigxml.h"
#include "sprogcsconnectionconfig.h"
#include "sprogcsserialdriveradapter.h"

using namespace Sprog;
/**
 * Handle XML persistance of layout connections by persistening the
 * SerialDriverAdapter (and connections). Note this is named as the XML version
 * of a ConnectionConfig object, but it's actually persisting the
 * SerialDriverAdapter.
 * <P>
 * This class is invoked from jmrix.JmrixConfigPaneXml on write, as that class
 * is the one actually registered. Reads are brought here directly via the class
 * attribute in the XML.
 *
 * @author Andrew Crosland Copyright: Copyright (c) 2006
 */
///*public*/ class ConnectionConfigXml extends AbstractSerialConnectionConfigXml {

    /*public*/ SprogCSConnectionConfigXml::SprogCSConnectionConfigXml(QObject* parent) : AbstractSerialConnectionConfigXml(parent) {
        //super();
    }

    //@Override
    /*protected*/ void SprogCSConnectionConfigXml::getInstance() {
        if (adapter == NULL) {
            adapter = new SprogCSSerialDriverAdapter();
        }
    }

    //@Override
    /*protected*/ void SprogCSConnectionConfigXml::getInstance(QObject* object) {
        adapter = (SerialPortAdapter*)((SprogCSConnectionConfig*) object)->getAdapter();
    }


    //@Override
    /*protected*/ void SprogCSConnectionConfigXml::_register()
    {
     ConnectionConfig* cfg = (ConnectionConfig*)(new SprogCSConnectionConfig(adapter));
     AbstractConnectionConfigXml::_register(cfg);
    }

/*protected*/ QString SprogCSConnectionConfigXml::javaClass()
{
 return "jmri.jmrix.sprog.sprogCS.configurexml.ConnectionConfigXml";
}
