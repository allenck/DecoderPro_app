#include "resetaction.h"
#include "operationsxml.h"
#include "operationsmanager.h"
#include "apps.h"
#include "joptionpane.h"
#include "autobackup.h"
#include "instancemanager.h"
#include "exceptiondisplayframe.h"
#include "unexpectedexceptioncontext.h"

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

 /*public*/ ResetAction::ResetAction(QObject* parent ) : AbstractAction(tr("Reset"), parent)
 {
     //super(s);
  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }

 /*public*/ void ResetAction::actionPerformed(JActionEvent* ) {
     // check to see if files are dirty
     if (OperationsXml::areFilesDirty()) {
       if (JOptionPane::showConfirmDialog(nullptr, tr("Operations files have been modified, do you want to save them?"),
               tr("Save operation files?"), JOptionPane::YES_NO_OPTION) == JOptionPane::YES_OPTION)
       {
             OperationsXml::save();
       }
     }

     int results = JOptionPane::showConfirmDialog(nullptr, tr("Are you sure you want to delete all operation files and databases?"),
             tr("Reset Databases"), JOptionPane::OK_CANCEL_OPTION);
     if (results != JOptionPane::OK_OPTION)
     {
         return;
     }

     AutoBackup* backup = new AutoBackup();

     try {
         backup->autoBackup();

         // now delete the operations files
         backup->deleteOperationsFiles();

         // now deregister shut down task
         // If Trains window was opened, then task is active
         // otherwise it is normal to not have the task running
         ((Operations::OperationsManager*)InstanceManager::getDefault("Operations::OperationsManager"))->setShutDownTask(NULL);

         JOptionPane::showMessageDialog(nullptr, tr("You must restart JMRI to complete the reset"),
                 tr("Reset successful!"), JOptionPane::INFORMATION_MESSAGE);
         Apps::handleRestart();

     } catch (Exception* ex) {
         UnexpectedExceptionContext* context = new UnexpectedExceptionContext(ex,
                 "Deleting Operations files",this); // NOI18N
         new ExceptionDisplayFrame(context);
     }
 }

}
