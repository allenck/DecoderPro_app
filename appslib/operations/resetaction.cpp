#include "resetaction.h"
#include "operationsxml.h"
#include "operationsmanager.h"
#include "apps.h"
#include <QMessageBox>
#include "autobackup.h"

namespace Operations
{
 /**
  * Swing action to load the operation demo files.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2010
  * @author Gregory Madsen Copyright (C) 2012
  * @version $Revision: 28746 $
  */
 ///*public*/ class ResetAction extends AbstractAction {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = -3591765950664839428L;

 /*public*/ ResetAction::ResetAction(QString s, QObject* parent ) : AbstractAction(s, parent)
 {
     //super(s);
  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }

 /*public*/ void ResetAction::actionPerformed(ActionEvent* /*e*/) {
     // check to see if files are dirty
     if (OperationsXml::areFilesDirty()) {
//         if (JOptionPane.showConfirmDialog(null, Bundle.getMessage("OperationsFilesModified"),
//                 Bundle.getMessage("SaveOperationFiles"), JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
      if(QMessageBox::question(NULL, tr("Save operation files?"), tr("Operations files have been modified, do you want to save them?"),QMessageBox::Yes | QMessageBox::No)== QMessageBox::Yes)
      {
             OperationsXml::save();
         }
     }

//     int results = JOptionPane.showConfirmDialog(null, Bundle.getMessage("AreYouSureDeleteAll"),
//             Bundle.getMessage("ResetOperations"), JOptionPane.OK_CANCEL_OPTION);
//     if (results != JOptionPane.OK_OPTION) {
     if(QMessageBox::question(NULL, tr("Reset Databases"), tr("Are you sure you want to delete all operation files and databases?"),QMessageBox::Ok | QMessageBox::Cancel)!=QMessageBox::Ok)
     {
         return;
     }

     AutoBackup* backup = new AutoBackup();

     //try {
         backup->autoBackup();

         // now delete the operations files
         backup->deleteOperationsFiles();

         // now deregister shut down task
         // If Trains window was opened, then task is active
         // otherwise it is normal to not have the task running
         OperationsManager::getInstance()->setShutDownTask(NULL);

//         JOptionPane.showMessageDialog(null, Bundle.getMessage("YouMustRestartAfterReset"),
//                 Bundle.getMessage("ResetSuccessful"), JOptionPane.INFORMATION_MESSAGE);
         QMessageBox::information(NULL, tr("Reset successful!"), tr("You must restart JMRI to complete the reset"));
         Apps::handleRestart();

//     } catch (Exception ex) {
//         UnexpectedExceptionContext context = new UnexpectedExceptionContext(ex,
//                 "Deleting Operations files"); // NOI18N
//         new ExceptionDisplayFrame(context);
//     }
 }

}
