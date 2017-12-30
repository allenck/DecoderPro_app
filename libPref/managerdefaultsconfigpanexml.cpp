#include "managerdefaultsconfigpanexml.h"
#include "instancemanager.h"
#include "managerdefaultsconfigpane.h"
#include "managerdefaultselector.h"

ManagerDefaultsConfigPaneXml::ManagerDefaultsConfigPaneXml(QObject *parent) :
    AbstractXmlAdapter(parent)
{
}
/**
 * Handle XML persistence of ManagerDefaultsConfigPane objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2010
 * @version $Revision: 27930 $
 */
///*public*/ class ManagerDefaultsConfigPaneXml extends jmri.configurexml.AbstractXmlAdapter {

///*public*/ ManagerDefaultsConfigPaneXml() {
//}

/**
 * Arrange for ManagerDefaultSelector to be stored
 * @param o Object to store, ignored
 * @return NULL after others arranged
 */
/*public*/ QDomElement ManagerDefaultsConfigPaneXml::store(QObject* /*o*/) {
 ConfigureManager* cm = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
         if (cm != NULL) {
             cm->registerPref(InstanceManager::getDefault("ManagerDefaultSelector"));
         }
    return QDomElement();
}

/**
 * Create object from XML file
 * @param e Top level QDomElement to unpack.
  */
/*public*/ bool ManagerDefaultsConfigPaneXml::load(QDomElement /*e*/) throw (Exception)
{
    Logger::error("load(QDomElement) should not have been invoked");
    return false;
}

/**
 * Update static data from XML file
 * @param QDomElement Top level QDomElement to unpack.
 * @param o  ignored
 */
/*public*/ void ManagerDefaultsConfigPaneXml::load(QDomElement /*e*/, QObject* /*o*/) throw (Exception){
    Logger::error("Unexpected call of load(QDomElement, Object)");
}
// initialize logging
//static Logger log = LoggerFactory.getLogger(ManagerDefaultsConfigPaneXml.class.getName());
