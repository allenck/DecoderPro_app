#include "backupfilesaction.h"
#include "operationsxml.h"
#include "apps.h"
#include "logger.h"
#include "backupbase.h"
#include "jfilechooser.h"
#include "file.h"
#include "defaultbackup.h"
#include "joptionpane.h"

namespace Operations
{
 /**
  * Swing action to backup operation files to a directory selected by the user.
  *
  * @author Daniel Boudreau Copyright (C) 2011
  * @author Gregory Madsen Copyright (C) 2012
  * @version $Revision: 28746 $
  */
 ///*public*/ class BackupFilesAction extends AbstractAction {

 /**
  *
  */
// /*private*/ static final long serialVersionUID = 2252745243582800660L;
// static Logger log = LoggerFactory
//         .getLogger(BackupFilesAction.class.getName());

 /*public*/ BackupFilesAction::BackupFilesAction(QObject* parent)
     : AbstractAction(tr("Backup"), parent)
 {
  //super(s);
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void BackupFilesAction::actionPerformed(JActionEvent * /*e*/) {
     backUp();
 }

 /*private*/ void BackupFilesAction::backUp() {
     // check to see if files are dirty
     if (OperationsXml::areFilesDirty())
     {
      if (JOptionPane::showConfirmDialog(nullptr,
              tr("Operations files have been modified, do you want to save them?"),
              tr("Save operation files?"),
              JOptionPane::YES_NO_OPTION) == JOptionPane::YES_OPTION)
      {
       OperationsXml::save();
      }
     }
     BackupBase* backup = new DefaultBackup();

     // get directory to write to
     JFileChooser* fc = new JFileChooser(backup->getBackupRoot(), this->parent());
     //fc->addChoosableFileFilter(/*new fileFilter()*/"xml files(*.xml)");
     fc->setFileFilter("xml files (*.xml);;all files (*.*);");
     fc->setDialogTitle(tr("Select backup directory name"));
     fc->setApproveButtonText(tr("&B Backup"));
     fc->setApproveButtonToolTipText(tr("Click to save files to the backup folder."));
     fc->setFileNameToolTipText(tr("Enter the new backup directory name. "));

     File* fs = new File(backup->getBackupRoot()->getPath() + File::separator + backup->suggestBackupSetName());
     fc->setSelectedFile(fs);

     int retVal = fc->showSaveDialog(NULL);
     if (retVal != JFileChooser::APPROVE_OPTION) {
         return; // Canceled
     }
     if (fc->getSelectedFile() == NULL) {
         return; // Canceled
     }
     File* directory = fc->getSelectedFile();

     // Fix this later....... UGH!!
     try {
         backup->backupFilesToDirectory(directory);
     } catch (Exception ex) {
  }
 }
#if 0
 /*private*/ static class fileFilter extends javax.swing.filechooser.FileFilter {

     /*public*/ bool accept(File f) {
         if (f.isDirectory()) {
             return true;
         }
         String name = f.getName();
         if (name.matches(".*\\.xml")) // NOI18N
         {
             return true;
         } else {
             return false;
         }
     }

     /*public*/ String getDescription() {
         return Bundle.getMessage("BackupFolders");
     }
 }
#endif
}
