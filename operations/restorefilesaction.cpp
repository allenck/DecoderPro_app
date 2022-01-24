#include "restorefilesaction.h"
#include "operationsxml.h"
#include <QMessageBox>
#include "apps.h"
#include "autobackup.h"
#include "file.h"
#include "jfilechooser.h"
#include "operationsmanager.h"
#include "defaultbackup.h"
#include "instancemanager.h"
#include "exceptiondisplayframe.h"

namespace Operations
{
 /**
  * Swing action to backup operation files to a directory selected by the user.
  *
  * @author Daniel Boudreau Copyright (C) 2011
  * @author Gregory Madsen Copyright (C) 2012
  * @version $Revision: 28746 $
  */
 ///*public*/ class RestoreFilesAction extends AbstractAction {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = -4848726844188320052L;
// static Logger log = LoggerFactory
//         .getLogger(RestoreFilesAction.class.getName());

 /*public*/ RestoreFilesAction::RestoreFilesAction(QObject* parent)
     : AbstractAction(tr("Restore"), parent)
 {
  //super(s);
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void RestoreFilesAction::actionPerformed(JActionEvent * /*e*/) {
     restore();
 }

 /*private*/ void RestoreFilesAction::restore()
 {
// This method can restore files from any directory selected by the File
  // Chooser.

  // check to see if files are dirty
  if (OperationsXml::areFilesDirty())
  {
//      if (JOptionPane
//              .showConfirmDialog(
//                      null,
//                      tr("OperationsFilesModified"),
//                      tr("SaveOperationFiles"),
//                      JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
   if(QMessageBox::question(NULL, tr("Save operation files?"), tr("Operations files have been modified, do you want to save them?"), QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes)
   {
    OperationsXml::save();
   }
  }

  // first backup the users data in case they forgot
  BackupBase* backup = new DefaultBackup();

  // get file to write to
  JFileChooser* fc = new JFileChooser(backup->getBackupRoot());
  //fc->addChoosableFileFilter(/*new fileFilter()*/"xml files (*.xml)");
  fc->setFileFilter("xml files (*.xml)");
  fc->setFileSelectionMode(JFileChooser::DIRECTORIES_ONLY);

  int retVal = fc->showOpenDialog(NULL);
  if (retVal != JFileChooser::APPROVE_OPTION) {
      return; // Canceled
  }
  if (fc->getSelectedFile() == NULL) {
      return; // Canceled
  }
  // now backup files
  AutoBackup* autoBackup = new AutoBackup();

  try {
      autoBackup->autoBackup();

      File* directory = fc->getSelectedFile();

      // now delete the current operations files in case the restore isn't a full set of files
      backup->deleteOperationsFiles();

      backup->restoreFilesFromDirectory(directory);

//      JOptionPane.showMessageDialog(null,
//              tr("YouMustRestartAfterRestore"),
//              tr("RestoreSuccessful"), JOptionPane.INFORMATION_MESSAGE);
      QMessageBox::information(NULL, tr("Restore successful!"), tr("You must restart JMRI to complete the restore operation"));

      // now deregister shut down task
      // If Trains window was opened, then task is active
      // otherwise it is normal to not have the task running
      ((Operations::OperationsManager*)InstanceManager::getDefault("Operations::OperationsManager"))->setShutDownTask(NULL);

      Apps::handleRestart();

  } catch (Exception* ex) {
      ExceptionContext* context = new ExceptionContext(ex,
              tr("RestoreDialog.restore.files"),
              tr("RestoreDialog.makeSure"));
      new ExceptionDisplayFrame(context);
  }
 }
#if 0
 /*private*/ static class fileFilter extends javax.swing.filechooser.FileFilter {

     /*public*/ bool accept(File f) {
         if (f.isDirectory()) {
             return true;
         }
         QString name = f.getName();
         if (name.matches(".*\\.xml")) // NOI18N
         {
             return true;
         } else {
             return false;
         }
     }

     /*public*/ QString getDescription() {
         return tr("BackupFolders");
     }
 }
#endif
}
