#include "loadxmlconfigaction.h"
#include "instancemanager.h"
#include "jfilechooser.h"
#include "layoutblockmanager.h"
#include "defaultcatalogtreemanagerxml.h"
#include "logger.h"
#include "configxmlmanager.h"

//LoadXmlConfigAction::LoadXmlConfigAction(QObject *parent) :
//  LoadStoreBaseAction(parent)
//{
//}
/**
 * Load configuration information from an XML file.
 * <P>
 * The file context for this is the "config" file chooser.
 * <P>
 * This will load whatever information types are present in the file. See
 * {@link jmri.ConfigureManager} for information on the various types of
 * information stored in configuration files.
 *
 * @author	Bob Jacobsen Copyright (C) 2002
 * @version	$Revision: 29359 $
 * @see jmri.jmrit.XmlFile
 */
// /*public*/ class LoadXmlConfigAction extends LoadStoreBaseAction {

/**
 *
 */
//private static final long serialVersionUID = -6243836869038163553L;

/*public*/ LoadXmlConfigAction::LoadXmlConfigAction(QObject *parent) :
  LoadStoreBaseAction(tr("Open Panel File ..."), parent) {
    //this("Open Panel File ...");
 common();
}

/*public*/ LoadXmlConfigAction::LoadXmlConfigAction(QString s,QObject *parent) :
  LoadStoreBaseAction(s, parent)
{
 //super(s);
 common();
}

void LoadXmlConfigAction::common()
{
 log = new Logger("LoadXmlConfigAction");
}

/*public*/ void LoadXmlConfigAction::actionPerformed(ActionEvent* /*e*/)
{
 loadFile(this->getConfigFileChooser());
}

/**
 *
 * @param fileChooser
 * @return true if successful
 */
/*protected*/ bool LoadXmlConfigAction::loadFile(JFileChooser* fileChooser)
{
 bool results = false;
 File* file = getFile(fileChooser);
 if (file != NULL)
 {
//  try {
  ConfigureManager* cm = InstanceManager::configureManagerInstance();
  results = ((ConfigXmlManager*)cm)->load(file);
   if (results)
   {
    // insure logix etc fire up
    InstanceManager::logixManagerInstance()->activateAllLogixs();
    ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->initializeLayoutBlockPaths();
    (new DefaultCatalogTreeManagerXml())->readCatalogTrees();
   }
//     } catch (JmriException e) {
//         log.error("Unhandled problem in loadFile: " + e);
//     }
 }
 else
 {
  results = true;   // We assume that as the file is NULL then the user has clicked cancel.
 }
 return results;
}

/*static*/ /*public*/ File* LoadXmlConfigAction::getFile(JFileChooser* fileChooser)
{
 fileChooser->setDialogType(JFileChooser::OPEN_DIALOG);
 return getFileCustom(fileChooser);
}

/*static*/ /*public*/ File* LoadXmlConfigAction::getFileCustom(JFileChooser* fileChooser)
{
 Logger* log = new Logger("LoadXmlConfigAction");
 //fileChooser.rescanCurrentDirectory();
 int retVal = fileChooser->showDialog(NULL, "");
 if (retVal != JFileChooser::APPROVE_OPTION) {
     return NULL;  // give up if no file selected
 }
 if (log->isDebugEnabled()) {
     log->debug("Open file: " + fileChooser->getSelectedFile()->getPath());
 }
 return fileChooser->getSelectedFile();
}
