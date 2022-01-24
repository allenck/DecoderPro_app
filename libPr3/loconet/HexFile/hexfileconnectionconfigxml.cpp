#include "hexfileconnectionconfigxml.h"
#include "hexfileframe.h"
#include "hexfileserver.h"
#include "serialportadapter.h"
#include "defaultsystemconnectionmemo.h"
#include "connectionconfig.h"
#include "instancemanager.h"
#include "lnhexfileport.h"
#include "hexfileconnectionconfig.h"

HexFileConnectionConfigXml::HexFileConnectionConfigXml(QObject *parent) :
    AbstractSerialConnectionConfigXml(parent)
{
}
/**
 * Handle XML persistance of layout connections by persistening
 * the HexFIle LocoNet emuilator (and connections). Note this is
 * named as the XML version of a ConnectionConfig object,
 * but it's actually persisting the HexFile info.
 * <P>
 * This class is invoked from jmrix.JmrixConfigPaneXml on write,
 * as that class is the one actually registered. Reads are brought
 * here directly via the class attribute in the XML.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @version $Revision: 27930 $
 */
// /*public*/ class ConnectionConfigXml extends AbstractSerialConnectionConfigXml {

///*public*/ ConnectionConfigXml() {
//    super();
//}

/**
 * A HexFile connection needs no extra information, so
 * we reimplement the superclass method to just write the
 * necessary parts.
 * @param o
 * @return Formatted element containing no attributes except the class name
 */
//@Override
/*public*/ QDomElement HexFileConnectionConfigXml::store(QObject* o)
{
 getInstance(o);
 doc = QDomDocument("JmriXml");
 QDomElement e = doc.createElement("connection");
 if (adapter->getSystemConnectionMemo()!=NULL)
 {
  e.setAttribute("userName", adapter->getSystemConnectionMemo()->getUserName());
  e.setAttribute("systemPrefix", adapter->getSystemConnectionMemo()->getSystemPrefix());
 }
 if (adapter->getManufacturer()!="")
     e.setAttribute("manufacturer", adapter->getManufacturer());
 saveOptions(e, adapter);

 if (adapter->getDisabled())
     e.setAttribute("disabled", "yes");
 else e.setAttribute("disabled", "no");

 e.setAttribute("class", /*this.getClass().getName()*/ "jmri.jmrix.loconet.hexfile.ConnectionConfigXml");

 return e;
}
#if 0
/**
 * Update instance data from XML file
 * @param e Top level QDomElement to unpack.
 * @return true if successful
  */
/*public*/ bool HexFileConnectionConfigXml::load(QDomElement e) throw (Exception)
{
 HexFileFrame* f = NULL;
 HexFileServer* hfs = NULL;

 getInstance();
 // hex file has no options in the XML

 //GraphicsEnvironment.getLocalGraphicsEnvironment();
 // create GUI, unless running in headless mode
//    if (!GraphicsEnvironment.isHeadless())
 {
  f = new HexFileFrame();
  f->setAdapter((LnHexFilePort*)adapter);
  try
  {
   f->initComponents();
  }
  catch (Exception* ex)
  {
   //log.error("starting HexFileFrame exception: "+ex.toString());
  }
  f->pack();
  f->setVisible(true);
 }
//    else {  // create and configure the headless server
//        hfs = new HexFileServer();
//        hfs->setAdapter((LnHexFilePort*)adapter);
//    }

 if (e.attribute("option1")!="")
 {
  QString option1Setting = e.attribute("option1");
  adapter->configureOption1(option1Setting);
 }
 if (e.attribute("option2")!="")
 {
  QString option2Setting = e.attribute("option2");
  adapter->configureOption2(option2Setting);
 }
 if (e.attribute("option3")!="")
 {
  QString option3Setting = e.attribute("option3");
  adapter->configureOption3(option3Setting);
 }
 if (e.attribute("option4")!="")
 {
  QString option4Setting = e.attribute("option4");
  adapter->configureOption4(option4Setting);
 }
 loadOptions(e.firstChildElement("options"), adapter);
 QString manufacturer;
 try
 {
  manufacturer = e.attribute("manufacturer");
  adapter->setManufacturer(manufacturer);
 } catch ( NullPointerException ex)
 { //Considered normal if not present

 }
 if (adapter->getSystemConnectionMemo()!=NULL)
 {
  if (e.attribute("userName")!="")
  {
   adapter->getSystemConnectionMemo()->setUserName(e.attribute("userName"));
  }

  if (e.attribute("systemPrefix")!=NULL)
  {
   adapter->getSystemConnectionMemo()->setSystemPrefix(e.attribute("systemPrefix"));
  }
 }
 if (e.attribute("disabled")!="")
 {
  QString yesno = e.attribute("disabled");
  if ( (yesno!="") && (yesno!=("")) )
  {
   if (yesno==("no")) adapter->setDisabled(false);
   else if (yesno==("yes")) adapter->setDisabled(true);
  }
 }

 // register, so can be picked up
 _register();
 if (adapter->getDisabled())
 {
//        if (!GraphicsEnvironment.isHeadless() && f!=NULL)
  {
   f->setVisible(false);
  }
  return true;
 }
 //if (!GraphicsEnvironment.isHeadless() && f!=NULL)
 {
  f->configure();
 }
//      else if (hfs!=NULL){
//        hfs->configure();
//    }
 return true;
}
#endif
//@Override
/*public*/ bool HexFileConnectionConfigXml::load(QDomElement shared, QDomElement perNode) {
    HexFileFrame* f = NULL;
    HexFileServer* hfs = NULL;

    getInstance();
    // hex file has no options in the XML

//    GraphicsEnvironment::getLocalGraphicsEnvironment();
    // create GUI, unless running in headless mode
//    if (!GraphicsEnvironment.isHeadless())
//    {
        f = new HexFileFrame();
        f->setAdapter((LnHexFilePort*) adapter);
        try {
            f->initComponents();
        } catch (Exception* ex) {
            //log.error("starting HexFileFrame exception: "+ex.toString());
        }
        f->pack();
        f->setVisible(true);
//    } else {  // create and configure the headless server
//        hfs = new jmri.jmrix.loconet.hexfile.HexFileServer();
//        hfs.setAdapter((LnHexFilePort) adapter);
//    }

    if (shared.attribute("option1") != NULL) { // NOI18N
        QString option1Setting = shared.attribute("option1"); // NOI18N
        adapter->configureOption1(option1Setting);
    }
    if (shared.attribute("option2") != NULL) { // NOI18N
        QString option2Setting = shared.attribute("option2"); // NOI18N
        adapter->configureOption2(option2Setting);
    }
    if (shared.attribute("option3") != NULL) { // NOI18N
        QString option3Setting = shared.attribute("option3"); // NOI18N
        adapter->configureOption3(option3Setting);
    }
    if (shared.attribute("option4") != NULL) { // NOI18N
        QString option4Setting = shared.attribute("option4"); // NOI18N
        adapter->configureOption4(option4Setting);
    }
    loadOptions(shared.firstChildElement("options"), perNode.firstChildElement("options"), adapter); // NOI18N
    QString manufacturer;
    try {
        manufacturer = shared.attribute("manufacturer"); // NOI18N
        adapter->setManufacturer(manufacturer);
    } catch (NullPointerException* ex) { //Considered normal if not present

    }
    if (adapter->getSystemConnectionMemo() != NULL) {
        if (shared.attribute("userName") != NULL) { // NOI18N
            adapter->getSystemConnectionMemo()->setUserName(shared.attribute("userName")); // NOI18N
        }

        if (shared.attribute("systemPrefix") != NULL) { // NOI18N
            ((DefaultSystemConnectionMemo*)adapter->getSystemConnectionMemo())->setSystemPrefix(shared.attribute("systemPrefix")); // NOI18N
        }
    }
    if (shared.attribute("disabled") != NULL) { // NOI18N
        QString yesno = shared.attribute("disabled"); // NOI18N
        if ((yesno != NULL) && (yesno != (""))) {
            if (yesno == ("no")) { // NOI18N
                adapter->setDisabled(false);
            } else if (yesno == ("yes")) { // NOI18N
                adapter->setDisabled(true);
            }
        }
    }

    // register, so can be picked up
    _register();

    if (adapter->getDisabled()) {
//        if (!GraphicsEnvironment.isHeadless() && f != NULL) {
            f->setVisible(false);
//        }
        return true;
    }
//    if (!GraphicsEnvironment.isHeadless() && f != NULL) {
        f->configure();
//    } else if (hfs != NULL) {
//        hfs.configure();
//    }
    return true;
}

/*protected*/ void HexFileConnectionConfigXml::getInstance(QObject* object) {
    adapter = (SerialPortAdapter*)((ConnectionConfig*)object)->getAdapter();
}

/*protected*/ void HexFileConnectionConfigXml::getInstance() {
    adapter = new LnHexFilePort();
}

/*protected*/ void HexFileConnectionConfigXml::_register() {
    //InstanceManager::configureManagerInstance()->_register(new HexFileConnectionConfig(adapter,NULL));
 AbstractConnectionConfigXml::_register((ConnectionConfig*)new HexFileConnectionConfig(adapter,NULL));
}
