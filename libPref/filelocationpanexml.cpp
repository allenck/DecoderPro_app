#include "filelocationpanexml.h"
#include "filelocationpane.h"
#include "fileutil.h"
#include "configuremanager.h"
#include "instancemanager.h"

FileLocationPaneXml::FileLocationPaneXml(QObject* parent) :
    AbstractXmlAdapter(parent)
{
 log = new Logger("FileLocationPaneXml");
}
/**
 * Handle XML persistence of directory locations.
 * <P>
 *
 * @author Kevin Dickerson Copyright: Copyright (c) 2010
 * @version $Revision: 28188 $
 */
///*public*/ class FileLocationPaneXml extends jmri.configurexml.AbstractXmlAdapter {

///*public*/ FileLocationPaneXml() {
//}

/**
 * Default implementation for storing the static contents of the Swing LAF
 *
 * @param o QObject* to store, of type FileLocationPane
 * @return QDomElement containing the complete info
 */
//@Override
/*public*/ QDomElement FileLocationPaneXml::store(QObject* o) {
    QDomElement e = doc.createElement("fileLocations");
    /*e.setAttribute("defaultScriptLocation", FileUtil.getPythonScriptsPath());
     e.setAttribute("defaultUserLocation", FileUtil.getUserFilesPath());
     e.setAttribute("defaultThrottleLocation", jmri.jmrit.throttle.ThrottleFrame.getDefaultThrottleFolder());*/
    storeLocation(e, "defaultScriptLocation", FileUtil::getScriptsPath());
    storeUserFilesLocation(e, FileUtil::getUserFilesPath());
    e.setAttribute("class", /*this.getClass().getName()*/ "aps.configurexml.FileLocationPaneXml");
    return e;
}

/*private*/ void FileLocationPaneXml::storeLocation(QDomElement locations, QString attr, QString value) {
    QDomElement userLocation = doc.createElement("fileLocation");
    userLocation.setAttribute(attr, FileUtil::getPortableFilename(value));
    locations.appendChild(userLocation);
}

/*private*/ void FileLocationPaneXml::storeUserFilesLocation(QDomElement locations, QString value) {
    QDomElement userLocation = doc.createElement("fileLocation");
    userLocation.setAttribute("defaultUserLocation", FileUtil::getPortableFilename(value, true, false));
    locations.appendChild(userLocation);
}

/**
 * Update static data from XML file
 *
 * @param e Top level QDomElement to unpack.
 * @return true if successful
 */
//@Override
/*public*/ bool FileLocationPaneXml::load(QDomElement e)  throw (Exception)
{
 bool result = true;
    //Attribute scriptLocation = e.getAttribute("defaultScriptLocation");
    //if (scriptLocation!=null)
    //FileUtil.setPythonScriptsPath(scriptLocation.getValue());
    /*Attribute userLocation = e.getAttribute("defaultUserLocation");
     if (userLocation!=null)
     FileUtil.setUserFilesPath(userLocation.getValue());*/
 QString value = loadUserLocations(e, "defaultUserLocation");
 if (value != "")
 {
  FileUtil::setUserFilesPath(value);
 }
 value = loadUserLocations(e, "defaultScriptLocation");
 if (value != "")
 {
  FileUtil::setScriptsPath(value);
 }
 InstanceManager::configureManagerInstance()->registerPref(new FileLocationPane());
 return result;
}

/*private*/ QString FileLocationPaneXml::loadUserLocations(QDomElement messages, QString attr)
{
 QDomNodeList messageList = messages.elementsByTagName("fileLocation");
 for (int i=0; i < messageList.count(); i++)
 {
  QDomElement message =  messageList.at(i).toElement();
  if (message.attribute(attr) != "")
  {
   return FileUtil::getAbsoluteFilename(message.attribute(attr));
  }
 }
 return "";
}

/**
 * Update static data from XML file
 *
 * @param element Top level QDomElement to unpack.
 * @param o ignored
 */
//@Override
/*public*/ void FileLocationPaneXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception)
{
    log->error("Unexpected call of load(Element, Object)");
}
