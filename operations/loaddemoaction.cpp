#include "loaddemoaction.h"
#include "operationsxml.h"
#include <QMessageBox>
#include "autobackup.h"
#include "operationsmanager.h"
#include "apps.h"
/**
 * Swing action to load the operation demo files.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2008
 * @author Gregory Madsen Copyright(C) 2012
 * @version $Revision: 28746 $
 */
///*public*/ class LoadDemoAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 8904435442712923065L;
//static Logger log = LoggerFactory.getLogger(LoadDemoAction.class
//        .getName());

namespace Operations
{
 /*public*/ LoadDemoAction::LoadDemoAction(QString s, QObject* parent)  : AbstractAction(s, parent)
 {
     //super(s);
  backup = new Operations::AutoBackup();

  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }

 //@Override
 /*public*/ void LoadDemoAction::actionPerformed(ActionEvent* /*e*/)
 {
     // check to see if files are dirty
  if (OperationsXml::areFilesDirty())
  {
 //        if (JOptionPane.showConfirmDialog(null, Bundle.getMessage("OperationsFilesModified"),
 //                Bundle.getMessage("SaveOperationFiles"), JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION)
   if(QMessageBox::question(NULL, tr("Save operation files?"), tr("Operations files have been modified, do you want to save them?"), QMessageBox::Yes | QMessageBox::No)== QMessageBox::Yes)
   {
           OperationsXml::save();
   }
  }

 // int results = JOptionPane.showConfirmDialog(null, Bundle.getMessage("AreYouSureDemoFiles"),
 //         Bundle.getMessage("LoadDemo"), JOptionPane.OK_CANCEL_OPTION);
 // if (results != JOptionPane.OK_OPTION) {
  if(QMessageBox::question(NULL, tr("Load Demo Files"), tr("Are you sure you want to load the demo operation files?"), QMessageBox::Ok |QMessageBox::Cancel)!= QMessageBox::Ok)
  {
      return;
  }


  //try {
      backup->autoBackup();

      backup->loadDemoFiles();

      // now deregister shut down task
      // If Trains window was opened, then task is active
      // otherwise it is normal to not have the task running
      OperationsManager::getInstance()->setShutDownTask(NULL);

 //     JOptionPane.showMessageDialog(null, Bundle.getMessage("YouMustRestartAfterLoadDemo"),
 //             Bundle.getMessage("LoadDemoSuccessful"), JOptionPane.INFORMATION_MESSAGE);
      QMessageBox::information(NULL, tr("Demo load successful!"), tr("You must restart JMRI to complete the load demo operation"));
      Apps::handleRestart();

 // } catch (Exception ex) {
 //     ExceptionContext context = new ExceptionContext(ex, Bundle.getMessage("LoadingDemoFiles"),
 //             Bundle.getMessage("LoadingDemoMakeSure"));
 //     new ExceptionDisplayFrame(context);
 // }
 }
}
