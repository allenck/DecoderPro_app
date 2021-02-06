#include "loadxmlconfigaction.h"
#include "instancemanager.h"
#include "jfilechooser.h"
#include "layoutblockmanager.h"
#include "defaultcatalogtreemanagerxml.h"
#include "logger.h"
#include "configxmlmanager.h"
#include "jmriconfigurationmanager.h"
#include "loggerfactory.h"

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

/*public*/ QString LoadXmlConfigAction::currentFile = "";

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

/*public*/ void LoadXmlConfigAction::actionPerformed(JActionEvent* /*e*/)
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
 fileChooser->settimeout(15); // 15 sec timeout
 File* file = getFile(fileChooser);
 if (file != nullptr)
 {
  try
  {
   ConfigureManager* cm = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
   if (cm == nullptr)
   {
       log->error("Failed to get default configure manager");
   }
   else
   {
    currentFile = file->getPath();
    results = cm->load(file);
    if (results)
    {
     // insure logix etc fire up
     ((LogixManager*)InstanceManager::getDefault("LogixManager"))->activateAllLogixs();
     ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->initializeLayoutBlockPaths();
     (new DefaultCatalogTreeManagerXml())->readCatalogTrees();
    }
    currentFile = "";
   }
  } catch (JmriException e) {
         log->error("Unhandled problem in loadFile: " + e.getMessage());
  }
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
 fileChooser->setApproveButtonText(tr("Open Panel File ..."));
 return getFileCustom(fileChooser);
}

/*static*/ /*public*/ File* LoadXmlConfigAction::getFileCustom(JFileChooser* fileChooser)
{
 //fileChooser.rescanCurrentDirectory();
 int retVal = fileChooser->showDialog(nullptr, "");
 if (retVal != JFileChooser::APPROVE_OPTION) {
     return nullptr;  // give up if no file selected
 }
 if (log->isDebugEnabled()) {
     log->debug("Open file: " + fileChooser->getSelectedFile()->getPath());
 }
 return fileChooser->getSelectedFile();
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* LoadXmlConfigAction::log = LoggerFactory::getLogger("LoadXmlConfigAction");
