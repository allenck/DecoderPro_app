#include "abstractconnectionconfigxml.h"
#include "portadapter.h"
#include "systemconnectionmemo.h"
#include "connectionconfig.h"

AbstractConnectionConfigXml::AbstractConnectionConfigXml(QObject *parent)  : AbstractXmlAdapter(parent)
{
}
/**
 * Abstract base (and partial implementation) for
 * classes persisting the status of serial port adapters.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @version $Revision: 28190 $
 */
// abstract /*public*/ class AbstractConnectionConfigXml extends AbstractXmlAdapter {

///*public*/ AbstractConnectionConfigXml() {
//}

//static java.util.ResourceBundle rb =
//    java.util.ResourceBundle.getBundle("jmri.jmrix.JmrixBundle");

/*abstract*/ /*protected*/ void AbstractConnectionConfigXml::getInstance() {}
/*abstract*/ /*protected*/ void AbstractConnectionConfigXml::_register() {}

/*protected*/ void AbstractConnectionConfigXml::_register(ConnectionConfig* c)
{
 c->_register();
}

#if 0
/**
 * Default implementation for storing the static contents of the serial port implementation
 * @param o Object to store, of type PositionableLabel
 * @return QDomElement containing the complete info
 */
/*abstract*/ /*public*/ QDomElement AbstractConnectionConfigXml::store(QObject* o) {}
#endif

//@Override
/*public*/ QDomElement AbstractConnectionConfigXml::store(QObject* o, bool shared)
{
 Q_UNUSED (shared);
   //this->store(o);
 Q_ASSERT(false); // this doesn't work.
}

/*protected*/ void AbstractConnectionConfigXml::storeCommon(QDomElement e,  PortAdapter* adapter)
{
 if (adapter->getSystemConnectionMemo()!=NULL)
 {
  e.setAttribute("userName", adapter->getSystemConnectionMemo()->getUserName());
  e.setAttribute("systemPrefix", adapter->getSystemConnectionMemo()->getSystemPrefix());
 }
 if (adapter->getManufacturer()!=NULL)
  e.setAttribute("manufacturer", adapter->getManufacturer());

 if (adapter->getDisabled())
   e.setAttribute("disabled", "yes");
 else e.setAttribute("disabled", "no");

  saveOptions(e, adapter);
}


/**
 * Customizable method if you need to add anything more
 * @param e QDomElement being created, update as needed
 */
/*protected*/ void AbstractConnectionConfigXml::extendElement(QDomElement e) {}

/**
 * Update static data from XML file
 * @param e Top level QDomElement to unpack.
 * @return true if successful
  */
/*abstract*/ /*public*/ bool AbstractConnectionConfigXml::load(QDomElement e) throw (Exception) {}

/*protected*/ void AbstractConnectionConfigXml::loadCommon(QDomElement shared, QDomElement perNode, PortAdapter* adapter)
{
    if (perNode.attribute("option1") != "") {
        QString option1Setting = perNode.attribute("option1");
        adapter->configureOption1(option1Setting);
    }
    if (perNode.attribute("option2") != "") {
        QString option2Setting = perNode.attribute("option2");
        adapter->configureOption2(option2Setting);
    }
    if (perNode.attribute("option3") != "") {
        QString option3Setting = perNode.attribute("option3");
        adapter->configureOption3(option3Setting);
    }
    if (perNode.attribute("option4") != "") {
        QString option4Setting = perNode.attribute("option4");
        adapter->configureOption4(option4Setting);
    }

    loadOptions(perNode.firstChildElement("options"), perNode.firstChildElement("options"), adapter);

    try {
        adapter->setManufacturer(perNode.attribute("manufacturer"));
    } catch (NullPointerException ex) { //Considered normal if not present

    }

    if (adapter->getSystemConnectionMemo() != NULL) {
        if (shared.attribute("userName") != "") {
            adapter->getSystemConnectionMemo()->setUserName(shared.attribute("userName"));
        }

        if (shared.attribute("systemPrefix") != NULL) {
            adapter->getSystemConnectionMemo()->setSystemPrefix(shared.attribute("systemPrefix"));
        }
    }

    if (shared.attribute("disabled") != "") {
        QString yesno = shared.attribute("disabled");
        if ((yesno != NULL) && (!yesno.isEmpty())) {
            if (yesno == ("no")) {
                adapter->setDisabled(false);
            } else if (yesno == ("yes")) {
                adapter->setDisabled(true);
            }
        }
    }

}

/*protected*/ void AbstractConnectionConfigXml::saveOptions(QDomElement e, PortAdapter* adapter)
{
 QDomElement element = doc.createElement("options");
 QStringList options = adapter->getOptions();

 foreach(QString i, options)
 {
  QDomElement elem = doc.createElement("option");
  //elem.appendChild(doc.createElement("name").appendChild(doc.createTextNode(i)));
  QDomElement nameElem = doc.createElement("name");
  nameElem.appendChild(doc.createTextNode(i));
  elem.appendChild(nameElem);
  //elem.appendChild(doc.createElement("value").appendChild(doc.createTextNode(adapter->getOptionState(i))));
  QDomElement valueElem = doc.createElement("value");
  valueElem.appendChild(doc.createTextNode(adapter->getOptionState(i)));
  elem.appendChild(valueElem);
  element.appendChild(elem);
 }
 e.appendChild(element);
}

/*protected*/ void AbstractConnectionConfigXml::loadOptions(QDomElement shared, QDomElement perNode, PortAdapter* adapter) {
 if (perNode == QDomElement()) {
     return;
 }
 QDomNodeList optionList = perNode.elementsByTagName("option");
 for(int i = 0; i < optionList.size(); i++)
 {
  QDomElement so = optionList.at(i).toElement();
     adapter->setOptionState(so.firstChildElement("name").text(), so.firstChildElement("value").text());
 }
}

/**
 * Customizable method if you need to add anything more
 * @param e QDomElement being created, update as needed
 */
///*protected*/ void AbstractConnectionConfigXml::unpackElement(QDomElement /*e*/) {}

/**
 * Method to unpack additional XML structures after connection creation, but
 * before connection is usable.
 *
 * @param shared  connection information common to all nodes
 * @param perNode connection information unique to this node
 */
/*protected*/ void AbstractConnectionConfigXml::unpackElement(QDomElement /*shared*/, QDomElement /*perNode*/) {
}

/**
 * Update static data from XML file
 * @param element Top level QDomElement to unpack.
  */
/*public*/ void AbstractConnectionConfigXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception)
{
 Logger::error("method with two args invoked");
}
