#include "managebackupsaction.h"
#include "managebackupsdialog.h"



namespace Operations
{
/**
 * Swing action to show a dialog to allow the user to delete Automatic backups.
 *
 * For now, at least, this is needed as it is used by the menu system on the
 * OperationsSetup frame.
 *
 *
 * @author Gregory Madsen Copyright (C) 2012
 */
///*public*/ class ManageBackupsAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -5177110637357504582L;
// static Logger log = LoggerFactory
//   .getLogger(ManageBackupsAction.class.getName());

 /*public*/ ManageBackupsAction::ManageBackupsAction(QString s, QObject* parent) : AbstractAction(s, parent) {
     //super(s);
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }

 /*public*/ void ManageBackupsAction::actionPerformed(ActionEvent* /*e*/) {
     ManageBackupsDialog* dlg = new ManageBackupsDialog();
     //dlg->setLocationRelativeTo(null);
     dlg->setVisible(true);
 }
}
