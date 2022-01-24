#include "loaddemoaction.h"
#include "operationsxml.h"
#include "joptionpane.h"
#include "autobackup.h"
#include "operationsmanager.h"
#include "apps.h"
#include "instancemanager.h"
#include "exceptioncontext.h"
#include "exceptiondisplayframe.h"

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
 /*public*/ LoadDemoAction::LoadDemoAction(QObject* parent)  : AbstractAction(tr("Load Demo"), parent)
 {
     //super(s);
  backup = new Operations::AutoBackup();

  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }

 //@Override
 /*public*/ void LoadDemoAction::actionPerformed(JActionEvent * /*e*/)
 {
     // check to see if files are dirty
  if (OperationsXml::areFilesDirty())
  {
   if (JOptionPane::showConfirmDialog(nullptr, tr("Operations files have been modified, do you want to save them?"),
           tr("Save operation files?"), JOptionPane::YES_NO_OPTION) == JOptionPane::YES_OPTION)
   {
           OperationsXml::save();
   }
  }

  int results = JOptionPane::showConfirmDialog(nullptr, tr("Are you sure you want to load the demo operation files?"),
          tr("Load Demo Files"), JOptionPane::OK_CANCEL_OPTION);
  if (results != JOptionPane::OK_OPTION)
  {
      return;
  }


  try {
      backup->autoBackup();

      backup->loadDemoFiles();

      // now deregister shut down task
      // If Trains window was opened, then task is active
      // otherwise it is normal to not have the task running
      ((Operations::OperationsManager*)InstanceManager::getDefault("Operations::OperationsManager"))->setShutDownTask(NULL);

      JOptionPane::showMessageDialog(nullptr, tr("You must restart JMRI to complete the load demo operation"),
              tr("Demo load successful!"), JOptionPane::INFORMATION_MESSAGE);
      Apps::handleRestart();

  } catch (Exception* ex) {
      ExceptionContext* context = new ExceptionContext(ex, tr("Loading Demo Files"),
              tr("Make sure that all of the demo files exist and can be read."));
      new ExceptionDisplayFrame(context);
  }
 }
}
