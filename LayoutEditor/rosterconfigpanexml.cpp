#include "rosterconfigpanexml.h"
#include "rosterconfigpane.h"
#include "roster.h"
#include "instancemanager.h"
#include "rosterentry.h"
#include "rosterconfigmanager.h"
#include "profilemanager.h"

RosterConfigPaneXml::RosterConfigPaneXml(QObject *parent) :
  AbstractXmlAdapter(parent)
{
 log = new Logger("RosterConfigPaneXml");
}
/**
 * Handle XML persistance of Roster default values.
 * <P>
 * This class is named as being the persistant form of the RosterConfigPane
 * class, but there's no object of that form created when this is read back.
 * Instead, this persists static members of the roster.Roster class.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @version $Revision: 28771 $
 */
///*public*/ class RosterConfigPaneXml extends jmri.configurexml.AbstractXmlAdapter {

///*public*/ RosterConfigPaneXml() {
//}

/**
 * Default implementation for storing the static contents
 *
 * @param o Object to store
 * @return Element containing the complete info
 */
/*public*/ QDomElement RosterConfigPaneXml::store(QObject* o)
{

 RosterConfigPane* p = (RosterConfigPane*) o;
 // any reason to write?
 if ((p->getSelectedItem() == "" )
         && p->getDefaultOwner()==(""))
 {
  return QDomElement();
 }

 // create and write element
 QDomElement roster = doc.createElement("roster");
 if (p->getSelectedItem() != "" ) {
     roster.setAttribute("directory", p->getSelectedItem());
 }
 roster.setAttribute("class", "jmri.jmrit.roster.configurexml.RosterConfigPaneXml");
 roster.setAttribute("ownerDefault", p->getDefaultOwner());
 return roster;
}

/**
 * Update static data from XML file
 *
 * @param element Top level Element to unpack.
 * @return true if successful
 */
/*public*/ bool RosterConfigPaneXml::load(QDomElement shared, QDomElement /*perNode*/)
{
 bool result = true;
 Profile* project = ProfileManager::getDefault()->getActiveProfile();
 if (shared.attribute("directory") != "")
 {
  static_cast<RosterConfigManager*>(InstanceManager::getDefault("RosterConfigManager"))->setDirectory(project, shared.attribute("directory"));
  if (log->isDebugEnabled()) {
      log->debug("set roster location (1): " + shared.attribute("directory"));
  }
 }
 if (shared.attribute("ownerDefault") != "")
 {
  static_cast<RosterConfigManager*>(InstanceManager::getDefault("RosterConfigManager"))->setDefaultOwner(project, shared.attribute("ownerDefault"));

 }
 static_cast<ConfigureManager*>(InstanceManager::getDefault("ConfigureManager"))->registerPref(new RosterConfigPane());
 return result;
}

/**
 * Update static data from XML file
 *
 * @param element Top level Element to unpack.
 * @param o       ignored
 */
/*public*/ void RosterConfigPaneXml::load(QDomElement element, QObject* o) throw (Exception){
    if (log->isDebugEnabled()) {
        log->debug("set roster location (2): " + element.attribute("directory"));
    }
    if (element.attribute("directory") != "") {
        Roster::getDefault()->setRosterLocation(element.attribute("directory"));
    }
    static_cast<ConfigureManager*>(InstanceManager::getDefault("ConfigureManager"))->registerPref(new RosterConfigPane());
}
