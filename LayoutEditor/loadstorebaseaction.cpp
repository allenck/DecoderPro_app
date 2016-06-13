#include "loadstorebaseaction.h"
#include "instancemanager.h"
#include "configxmlmanager.h"
#include "fileutil.h"
#include "jfilechooser.h"

//LoadStoreBaseAction::LoadStoreBaseAction(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * Base implementation for the load and store actions.
 * <P>
 * Primarily provides file checking services to the
 * specific subclasses that load/store particular types of data.
 * <P>
 * Also used to
 * hold common information, specifically common instances of
 * the JFileChooser. These bring the user back to the same
 * place in the file system each time an action is invoked.
 *
 * @author	Bob Jacobsen   Copyright (C) 2004
 * @version	$Revision: 22530 $
 * @see         jmri.jmrit.XmlFile
 */
//// abstract /*public*/ class LoadStoreBaseAction extends AbstractAction
///*static*/ QFileDialog* LoadStoreBaseAction::allFileChooser = new QFileDialog(0, tr("Select  File"), FileUtil::getUserFilesPath(), tr("Xml files (*.xml)"));
///*static*/ QFileDialog* LoadStoreBaseAction::configFileChooser = new QFileDialog(0, tr("Select  File"),FileUtil::getUserFilesPath(), tr("Xml files (*.xml)"));
///*static*/ QFileDialog* LoadStoreBaseAction::userFileChooser = new QFileDialog(0, tr("Select  File"),FileUtil::getUserFilesPath(), tr("Xml files (*.xml)"));


/*public*/ LoadStoreBaseAction::LoadStoreBaseAction(QString s, QObject *parent)  : AbstractAction(s, parent)
{
 this->s = s;
 //super(s);
 // ensure that an XML config manager exists
 if (InstanceManager::configureManagerInstance()==NULL)
        InstanceManager::setConfigureManager((ConfigureManager*)new ConfigXmlManager());
}


//static {  // static class initialization
//    FileChooserFilter filt = new FileChooserFilter("XML files");
//    filt.addExtension("xml");
//    allFileChooser.setFileFilter(filt);
//    configFileChooser.setFileFilter(filt);
//    userFileChooser.setFileFilter(filt);
//}
/*
 * These JFileChoosers are retained so that multiple actions can all open
 * the JFileChoosers at the last used location for the context that the
 * action supports.
 */
/*private*/ /*static*/ JFileChooser* LoadStoreBaseAction::allFileChooser = NULL;
/*private*/ /*static*/ JFileChooser* LoadStoreBaseAction::configFileChooser = NULL;
/*private*/ /*static*/ JFileChooser* LoadStoreBaseAction::userFileChooser = NULL;

/*private*/ JFileChooser* LoadStoreBaseAction::getXmlFileChooser(QString path) {
//    FileChooserFilter xmlFilter = new FileChooserFilter("XML files");
//    xmlFilter.addExtension("xml"); // NOI18N
 QString xmlFilter = "Xml Files (*.xml)";

 JFileChooser* chooser = new JFileChooser(path);
 chooser->setFileFilter(xmlFilter);
 return chooser;
}

/*protected*/ JFileChooser* LoadStoreBaseAction::getAllFileChooser()
{
 if (allFileChooser == NULL)
 {
  allFileChooser = getXmlFileChooser(FileUtil::getUserFilesPath());
 }
 return allFileChooser;
}

/*protected*/ JFileChooser* LoadStoreBaseAction::getConfigFileChooser()
{
 if (configFileChooser == NULL)
 {
  configFileChooser = getXmlFileChooser(FileUtil::getUserFilesPath());
 }
return configFileChooser;
}

/*protected*/ JFileChooser* LoadStoreBaseAction::getUserFileChooser()
{
 if (userFileChooser == NULL)
 {
  userFileChooser = getXmlFileChooser(FileUtil::getUserFilesPath());
 }
 return userFileChooser;
}
