#include "sprogconnectionconfigxml.h"
#include "sprogserialdriveradapter.h"
#include "sprogconnectionconfig.h"

using namespace Sprog;
/**
 * Handle XML persistence of layout connections by persistening the
 * SerialDriverAdapter (and connections). Note this is named as the XML version
 * of a ConnectionConfig object, but it's actually persisting the
 * SerialDriverAdapter.
 * <P>
 * This class is invoked from jmrix.JmrixConfigPaneXml on write, as that class
 * is the one actually registered. Reads are brought here directly via the class
 * attribute in the XML.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 */
///*public*/ class ConnectionConfigXml extends AbstractSerialConnectionConfigXml {

    /*public*/ SprogConnectionConfigXml::SprogConnectionConfigXml(QObject* parent) : AbstractSerialConnectionConfigXml(parent){
        //super();
    }

    //@Override
    /*protected*/ void SprogConnectionConfigXml::getInstance() {
        if (adapter == NULL) {
            adapter = new SprogSerialDriverAdapter();
        }
    }

    //@Override
    /*protected*/ void SprogConnectionConfigXml::getInstance(QObject* object) {
        adapter = (SerialPortAdapter*)((SprogConnectionConfig*) object)->getAdapter();
    }


    //@Override
    /*protected*/ void SprogConnectionConfigXml::_register() {
        AbstractConnectionConfigXml::_register((ConnectionConfig*)(new SprogConnectionConfig(adapter)));
    }

/*protected*/ QString SprogConnectionConfigXml::javaClass()
{
 return "jmri.jmrix.sprog.sprog.configurexml.ConnectionConfigXml";
}
