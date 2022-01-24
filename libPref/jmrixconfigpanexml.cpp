#include "jmrixconfigpanexml.h"
#include "jmrixconfigpane.h"

#include "metatypes.h"
#include "progdefault.h"
#include "class.h"

JmrixConfigPaneXml::JmrixConfigPaneXml(QObject *parent) :
  AbstractXmlAdapter(parent)
{
 log = new Logger("JmrixConfigPaneXml");
}
/**
 * Handle XML persistance of layout connections.
 * <P>
 * This class is named as being the persistant form of the JmrixConfigPane
 * class, but there's no object of that form created or used. Instead, this
 * interacts forwards to a similar class in one of the protocol-specific
 * packages, e.g. jmrix.easydcc.serialdriver.configurexml
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @version $Revision: 28771 $
 */
///*public*/ class JmrixConfigPaneXml extends AbstractXmlAdapter {

///*public*/ JmrixConfigPaneXml() {
//}

/**
 * Forward to the configurexml class for the specific object type.
 */
/*public*/ QDomElement JmrixConfigPaneXml::store(QObject* o)
{
 QObject* oprime = ((JmrixConfigPane*) o)->getCurrentObject();
 if (oprime == NULL)
 {
  return QDomElement();
 }
 QString adapter = ConfigXmlManager::adapterName(oprime);
 log->debug("forward to " + adapter);
 try {
     XmlAdapter* x = (XmlAdapter*) Class::forName(adapter)/*.newInstance()*/;
     return x->store(oprime);
 } catch (Exception* e) {
     Logger::error("Exception: " /*+ e*/);
     //e.printStackTrace();
     return QDomElement();
 }
}

/**
 * Update static data from XML file
 *
 * @param e Top level QDomElement to unpack.
 * @return true if successful
 */
/*public*/ bool JmrixConfigPaneXml::load(QDomElement e)  throw (Exception){
    bool result = true;
//    UIManager.LookAndFeelInfo[] plafs = UIManager.getInstalledLookAndFeels();
//    java.util.Hashtable<String, String> installedLAFs = new java.util.Hashtable<String, String>(plafs.length);
//    for (int i = 0; i < plafs.length; i++) {
//        installedLAFs.put(plafs[i].getName(), plafs[i].getClassName());
//    }
//    QString name = e.getAttribute("LAFclass").getValue();
//    QString className = installedLAFs.get(name);
//    log->debug("GUI selection: " + name + " class name: " + className);
//    // set the GUI
//    if (className != NULL) {
//        try {
//            if (!className.equals(UIManager.getLookAndFeel().getClass().getName())) {
//                log->debug("set GUI to " + name + "," + className);
//                updateLookAndFeel(name, className);
//            } else {
//                log->debug("skip updateLAF as already has className==" + className);
//            }
//        } catch (Exception* ex) {
//            Logger::error("Exception while setting GUI look & feel: " + ex);
//            result = false;
//        }
//    }
    return result;
}
#if 0
/**
 * Change the look-and-feel to the specified class. Alert the user if there
 * were problems loading the PLAF.
 *
 * @param name      (String) the presentable name for the class
 * @param className (String) the className to be fed to the UIManager
 */
/*public*/ void updateLookAndFeel(QString name, QString className) {
    try {
        // Set the new look and feel, and update the sample message to reflect it.
        UIManager.setLookAndFeel(className);
    } catch (Exception* e) {
        String errMsg = "The " + name + " look-and-feel ";
        if (e instanceof UnsupportedLookAndFeelException) {
            errMsg += "is not supported on this platform.";
        } else if (e instanceof ClassNotFoundException) {
            errMsg += "could not be found.";
        } else {
            errMsg += "could not be loaded.";
        }

        Logger::error(errMsg);

    }
}
#endif
/**
 * Update static data from XML file
 *
 * @param element Top level QDomElement to unpack.
 * @param o       ignored
 */
/*public*/ void JmrixConfigPaneXml::load(QDomElement element, QObject* o) throw (Exception)
{
 ProgDefault::setDefaultProgFile(element.attribute("defaultFile"));
}
