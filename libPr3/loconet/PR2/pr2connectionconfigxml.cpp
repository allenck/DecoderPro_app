#include "pr2connectionconfigxml.h"
#include "pr2connectionconfig.h"
#include "pr2adapter.h"

/**
 * Handle XML persistance of layout connections by persisting the PR2Adapter
 * (and connections). Note this is named as the XML version of a
 * ConnectionConfig object, but it's actually persisting the PR2Adapter.
 * <p>
 * This class is invoked from jmrix.JmrixConfigPaneXml on write, as that class
 * is the one actually registered. Reads are brought here directly via the class
 * attribute in the XML.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003, 2005, 2006
 */
///*public*/ class ConnectionConfigXml extends AbstractSerialConnectionConfigXml {

/*public*/ Pr2ConnectionConfigXml::Pr2ConnectionConfigXml(QObject* parent) : AbstractSerialConnectionConfigXml(parent) {
    //super();
}

//@Override
/*protected*/ void Pr2ConnectionConfigXml::getInstance() {
    adapter = new PR2Adapter();
}

//@Override
/*protected*/ void Pr2ConnectionConfigXml::getInstance(QObject* object) {
    adapter = (SerialPortAdapter*) ((Pr2ConnectionConfig*) object)->getAdapter();
}

//@Override
/*protected*/ void Pr2ConnectionConfigXml::_register() {
    AbstractSerialConnectionConfigXml::_register((ConnectionConfig*)(new Pr2ConnectionConfig(adapter)));
}

