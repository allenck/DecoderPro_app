#include "storexmluseraction.h"
#include "instancemanager.h"
#include "configxmlmanager.h"
#include "joptionpane.h"
#include "fileutil.h"
#include "jfilechooser.h"

//StoreXmlUserAction::StoreXmlUserAction(QObject *parent) :
//    StoreXmlConfigAction(parent)
//{
//}
/**
 * Store the JMRI user-level information as XML.
 * <P>
 * Note that this does not store preferences, configuration, or tool information
 * in the file.  This is not a complete store!
 * See {@link jmri.ConfigureManager} for information on the various
 * types of information stored in configuration files.
 *
 * @author	Bob Jacobsen   Copyright (C) 2002
 * @version	$Revision: 19797 $
 * @see         jmri.jmrit.XmlFile
 */
///*public*/ class StoreXmlUserAction extends StoreXmlConfigAction {

//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.DisplayBundle");

/*public*/ StoreXmlUserAction::StoreXmlUserAction(QObject *parent) : StoreXmlConfigAction(parent)
{
//    this(
//        java.util.ResourceBundle.getBundle("jmri.jmrit.display.DisplayBundle")
//            .getString("MenuItemStore"));
 s = tr("Save Panels...");
 log = new Logger("StoreXmlUserAction");
 disconnect((this, SIGNAL(triggered())));
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ StoreXmlUserAction::StoreXmlUserAction(QString s, QObject *parent) : StoreXmlConfigAction(s, parent)
{
 //super(s);
 log = new Logger("StoreXmlUserAction");
 disconnect((this, SIGNAL(triggered())));
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void StoreXmlUserAction::actionPerformed(/*ActionEvent e*/)
{
 JFileChooser* userFileChooser = getUserFileChooser();
 userFileChooser->setDialogType(JFileChooser::SAVE_DIALOG);
 userFileChooser->setApproveButtonText(tr("Save")); // is in jmri.NBBundle
 userFileChooser->setDialogTitle(tr("Store Panels"));
 File* file = getFileCustom(userFileChooser);

 if (file == nullptr)
     return;

 saveFile(file->absoluteFilePath());
}

void StoreXmlUserAction::saveFile(QString selectedFile)
{
 // make a backup file
 ConfigureManager* cm = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
 cm->makeBackup(new File(selectedFile));
 // and finally store
 bool results = cm->storeUser(new File(selectedFile));
 log->debug(results?"store was successful":"store failed");
 if (!results)
 {
  JOptionPane::showMessageDialog(NULL,
          tr("Errors experienced during store.")+"\n"
          +tr("The storing of your information is incomplete and may result in missing items")+"\n"
          +tr("The Console window contains error details."),
          tr("Error Storing Information!"),	JOptionPane::ERROR_MESSAGE);

 }

//    // The last thing we do is restore the Approve button text.
//userFileChooser.setDialogType(oldDialogType);
//    userFileChooser.setApproveButtonText(oldButtonText);
//userFileChooser.setDialogTitle(oldDialogTitle);
}
