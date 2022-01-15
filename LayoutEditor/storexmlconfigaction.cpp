#include "storexmlconfigaction.h"
#include <QMessageBox>
#include <QFileDialog>
#include "instancemanager.h"
#include "configxmlmanager.h"
#include "fileutil.h"
#include "jfilechooser.h"


//StoreXmlConfigAction::StoreXmlConfigAction(QObject *parent) :
//    LoadStoreBaseAction(parent)
//{
//}
/**
 * Store the JMRI configuration information as XML.
 * <P>
 * Note that this does not store preferences, tools or user information
 * in the file.  This is not a complete store!
 * See {@link jmri.ConfigureManager} for information on the various
 * types of information stored in configuration files.
 *
 * @author	Bob Jacobsen   Copyright (C) 2002
 * @version	$Revision: 19797 $
 * @see         jmri.jmrit.XmlFile
 */
///*public*/ class StoreXmlConfigAction extends LoadStoreBaseAction {

//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.DisplayBundle");

/*public*/ StoreXmlConfigAction::StoreXmlConfigAction(QObject *parent) : LoadStoreBaseAction("Store configuration ...", parent){
    //this("Store configuration ...");
 common();
}

/*public*/ StoreXmlConfigAction::StoreXmlConfigAction(QString s, QObject *parent) : LoadStoreBaseAction(s, parent) {
    //super(s);
 common();
}

void StoreXmlConfigAction::common()
{
 log = new Logger("StoreXmlConfigAction");

 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}

/*static*/ /*public*/ File* StoreXmlConfigAction::getFileName(JFileChooser* fileChooser)
{
 fileChooser->setDialogType(JFileChooser::SAVE_DIALOG);
 return getFileCustom(fileChooser);
}

/**
 * Do the filename handling:
 *<OL>
 *<LI>rescan directory to see any new files
 *<LI>Prompt user to select a file
 *<LI>adds .xml extension if needed
 *<LI>if that file exists, check with user
 *</OL>
 * Returns nullptr if selection failed for any reason
 */
/*public*/ /*static*/ File* StoreXmlConfigAction::getFileCustom(JFileChooser* fileChooser)
{
 Logger* log = new Logger("StoreXmlConfigAction");
 //fileChooser.rescanCurrentDirectory();
 int retVal = fileChooser->showDialog(nullptr, nullptr);
 if (retVal != JFileChooser::APPROVE_OPTION)
 {
  return nullptr;  // give up if no file selected
 }
 File* file = fileChooser->getSelectedFile();
 if (fileChooser->getFileFilter() != fileChooser->getAcceptAllFileFilter())
 {
  // append .xml to file name if needed
  QString fileName = file->getAbsolutePath();
  QString fileNameLC = fileName.toLower();
  if (!fileNameLC.endsWith(".xml"))
  {
   fileName = fileName + ".xml";
   file = new File(fileName);
  }
 }
 if (log->isDebugEnabled())
 {
  log->debug("Save file: " + file->getPath());
 }
 //        if (selectedValue != JOptionPane.OK_OPTION) return nullptr;
#if 0 // Not necessary since QFileDialog also does this.
        switch(QMessageBox::question(0, tr("Overwrite file?"), tr("File ")+fileName+tr(" already exists, overwrite it?"),QMessageBox::Save | QMessageBox::Cancel ))
        {
        case QMessageBox::Cancel:
            return nullptr;
        default:
         break;
        }
#endif
 return file;
// }
}

/*public*/ void StoreXmlConfigAction::actionPerformed(/*ActionEvent* e*/)
{
 File* file = getFileName(this->getConfigFileChooser());
 if (file==nullptr) return;

 // and finally store
 bool results = qobject_cast<ConfigureManager*>(InstanceManager::getDefault("ConfigureManager"))->storeConfig(file);
 //System.out.println(results);
 log->debug(results?"store was successful":"Error Storing Information!");
 if (!results)
 {
  QMessageBox::information(nullptr,   tr("Errors experienced during store."),
             tr("The storing of your information is incomplete and may result in missing items")+"\n"
             +tr("The console window contains error details."));
 }
}
