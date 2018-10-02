#include "systemconsoleconfigpanelxml.h"
#include "instancemanager.h"
#include "systemconsole.h"
#include "systemconsoleconfigpanel.h"

SystemConsoleConfigPanelXml::SystemConsoleConfigPanelXml(QObject *parent) :
  AbstractXmlAdapter(parent)
{
 log = new Logger("SystemConsoleConfigPanelXml");
}
/**
 * Handle XML persistence of SystemConsoleConfigPanel objects.
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author Matthew Harris copyright (c) 2010
 * @version $Revision: 28771 $
 * @see apps.SystemConsoleConfigPanel
 */
///*public*/  class SystemConsoleConfigPanelXml extends jmri.configurexml.AbstractXmlAdapter {

///*public*/  SystemConsoleConfigPanelXml() {
//}

/**
 * Arrange for console settings to be stored
 *
 * @param o Object to store, of type SystemConsole
 * @return QDomElement containing the complete info
 */
//@Override
/*public*/  QDomElement SystemConsoleConfigPanelXml::store(QObject* o)
{

 QDomElement e = doc.createElement("console");
 e.setAttribute("class", "jmri.java.src.apps.configurexml.SystemConsoleConfigPanelXml");
 e.setAttribute("scheme", SystemConsole::getInstance()->getScheme());
 e.setAttribute("fontfamily", SystemConsole::getInstance()->getFontFamily());
 e.setAttribute("fontsize", SystemConsole::getInstance()->getFontSize());
 e.setAttribute("fontstyle", SystemConsole::getInstance()->getFontStyle());
 e.setAttribute("wrapstyle", SystemConsole::getInstance()->getWrapStyle());

 return e;
}

/**
 * Object should be loaded after basic GUI constructed
 *
 * @return true to defer loading
 * @see jmri.configurexml.AbstractXmlAdapter#loadDeferred()
 * @see jmri.configurexml.XmlAdapter#loadDeferred()
 */
//@Override
/*public*/  bool SystemConsoleConfigPanelXml::loadDeferred() {
    return true;
}

/**
 * Update static data from XML file
 *
 * @param e Top level QDomElement to unpack.
 * @return true if successful
 */
//@Override
/*public*/  bool SystemConsoleConfigPanelXml::load(QDomElement e) throw(Exception)
{
 bool result = true;
 QString value;

 try
 {
  if ((value = e.attribute("scheme")) != "")
  {
   SystemConsole::getInstance()->setScheme(value.toInt());
  }

  if ((value = e.attribute("fontfamily")) != "")
  {
   // Check if stored font family exists
//   if (!FontComboUtil.getFonts(FontComboUtil.MONOSPACED).contains(value)) {

//       // No - reset to default
//       log.warn("Stored console font is not compatible (" + value + ") - reset to default (Monospaced)");
//       value = "Monospaced";
//   }

   // Finally, set the font family
   SystemConsole::getInstance()->setFontFamily(value);
  }

  if ((value = e.attribute("fontsize")) != "") {
      SystemConsole::getInstance()->setFontSize(value.toInt());
  }

  if ((value = e.attribute("fontstyle")) != "") {
      SystemConsole::getInstance()->setFontStyle(value.toInt());
  }

  if ((value = e.attribute("wrapstyle")) != "") {
      SystemConsole::getInstance()->setWrapStyle(value.toInt());
  }

 } catch (NumberFormatException ex) {
     Logger::error("NumberFormatException while setting System Console parameters: " + ex.getMessage());
     result = false;
 }


 // As we've had a load request, register the system console with the
 // preference manager
 ConfigureManager* cm = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
         if (cm != NULL) {
             cm->registerPref(new SystemConsoleConfigPanel());
         }

 return result;
}

/**
 * Update static data from XML file
 *
 * @param element Top level QDomElement to unpack.
 * @param o       ignored
 */
//@Override
/*public*/  void SystemConsoleConfigPanelXml::load(QDomElement /*element*/, QObject* /*o*/) throw(Exception){
    Logger::error("Unexpected call of load(Element, Object)");
}
