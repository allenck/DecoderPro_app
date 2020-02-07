#include "abstractconnectionconfigxml.h"
#include "portadapter.h"
#include "systemconnectionmemo.h"
#include "connectionconfig.h"
#include "stringutils.h"
#include "loggerfactory.h"
#include "joptionpane.h"
#include <QLabel>

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
///*abstract*/ /*protected*/ void AbstractConnectionConfigXml::_register() {}

/*protected*/ void AbstractConnectionConfigXml::_register(ConnectionConfig* c)
{
 c->_register();
}


//@Override
/*public*/ QDomElement AbstractConnectionConfigXml::store(QObject* o, bool shared)
{
 Q_UNUSED (shared);
   //this->store(o);
 Q_ASSERT(false); // this doesn't work.
}

/*protected*/ void AbstractConnectionConfigXml::storeCommon(QDomElement e,  PortAdapter* adapter)
{
 e.setAttribute("xmlns", "");
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

    if (adapter->getSystemConnectionMemo() != NULL)
    {
     if (shared.attribute("userName") != "") {
         adapter->getSystemConnectionMemo()->setUserName(shared.attribute("userName"));
     }

     if (shared.attribute("systemPrefix") != NULL) {
         adapter->getSystemConnectionMemo()->setSystemPrefix(shared.attribute("systemPrefix"));
         checkAndWarnPrefix(shared.attribute("systemPrefix")); // for removal after #4670 resolved

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
/**
 * Check for a deprecated system prefix and warn if found
 * @deprecated 4.15.3  part of #4670 migration to parsable prefixes
 */
//@Deprecated // part of #4670 migration to parsable prefixes
/*protected*/ void AbstractConnectionConfigXml::checkAndWarnPrefix(QString prefix) {
    if (prefix.length() == 1 && ! StringUtils::isNumeric(prefix) ) return;
    if (prefix.length() > 1
            && ! StringUtils::isNumeric(prefix.mid(0,1))
            && StringUtils::isNumeric(prefix.mid(1)) ) return;

    // No longer checking jmri.Manager.isLegacySystemPrefix(prefix)) as this is more rigorous


    // unparsable, so warn
    log->warn(tr("Connection is using a prefix that needs to be migrated: %1").arg(prefix));
    log->warn("See http://jmri.org/help/en/html/setup/MigrateSystemPrefixes.shtml for more information");

    // and show clickable dialog
//    if (!java.awt.GraphicsEnvironment.isHeadless())
    {
        QLabel* message = new QLabel("<html><body>You have a connection with prefix \""
                                                    +prefix+"\" that needs to migrated.<br>"
                                                    +"See <a href=\"http://jmri.org/help/en/html/setup/MigrateSystemPrefixes.shtml\">"
                                                        +"http://jmri.org/help/en/html/setup/MigrateSystemPrefixes.shtml</a>"
                                                    +"<br>for more information.</body></html>"
            );
//        message.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
//        message.addMouseListener(new java.awt.event.MouseAdapter() {
//            @Override
//            public void mouseClicked(java.awt.event.MouseEvent e) {
//                try {
//                    java.awt.Desktop.getDesktop().browse(new java.net.URI("http://jmri.org/help/en/html/setup/MigrateSystemPrefixes.shtml"));
//                } catch (java.net.URISyntaxException | java.io.IOException ex) {
//                    log.error("couldn't open JMRI web site", ex);
//                }
//            }
//         });
        JOptionPane::showMessageDialog(nullptr, message->text(), "Migration Required", JOptionPane::WARNING_MESSAGE);
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
 log->error("method with two args invoked");
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* AbstractConnectionConfigXml::log = LoggerFactory::getLogger("AbstractConnectionConfigXml");
