#include "operationssetupframe.h"
#include "operationssetuppanel.h"
#include <qmenubar.h>
#include <QMenu>
#include "operationsmenu.h"
#include "control.h"
#include <QStatusBar>
#include "loaddemoaction.h"
#include "optionaction.h"
#include "backupfilesaction.h"
#include "restorefilesaction.h"
#include "printoptionaction.h"
#include "resetaction.h"
#include "buildreportoptionaction.h"
#include "managebackupsaction.h"

//OperationsSetupFrame::OperationsSetupFrame(QWidget *parent) :
//  OperationsFrame(parent)
//{
//}
namespace Operations
{
/**
 * Frame for user edit of operation parameters
 *
 * @author Dan Boudreau Copyright (C) 2008, 2010, 2011, 2012
 * @version $Revision: 28746 $
 */
///*public*/ class OperationsSetupFrame extends OperationsFrame {

 /**
  *
  */
 //private static final long serialVersionUID = 852682446088800323L;

 /*public*/ OperationsSetupFrame::OperationsSetupFrame(QWidget *parent)
   :  OperationsFrame(tr("Operations Setup"), /*new OperationsSetupPanel(),*/ parent)
 {
     //super(tr("TitleOperationsSetup"), new OperationsSetupPanel());
  setContentPane(new OperationsSetupPanel(this));
  QWidget* cp = centralWidget();
  setObjectName("OperationsSetupFrame");
  setStatusBar(new QStatusBar());
  statusBar()->setSizeGripEnabled(true);

  initComponents();

 }

 //@Override
 /*public*/ void OperationsSetupFrame::initComponents()
 {
   OperationsFrame::initComponents();
     // build menu
     QMenuBar* menuBar = new QMenuBar();
     QMenu* toolMenu = new QMenu(tr("Tools"));
     toolMenu->addAction(new OptionAction(tr("Options"),this));
     toolMenu->addAction(new PrintOptionAction(this));
     toolMenu->addAction(new BuildReportOptionAction(this));
     toolMenu->addAction(new BackupFilesAction(tr("Backup"),this));
     toolMenu->addAction(new RestoreFilesAction(tr("Restore"),this));
     toolMenu->addAction(new LoadDemoAction(tr("Load Demo"),this));
     toolMenu->addAction(new ResetAction(tr("Reset Operations"),this));
     toolMenu->addAction(new ManageBackupsAction(tr("Manage Auto Backups"),this));

     menuBar->addMenu(toolMenu);
     menuBar->addMenu(new OperationsMenu());
     setMenuBar(menuBar);
     addHelpMenu("package.jmri.jmrit.operations.Operations_Settings", true); // NOI18N

     initMinimumSize(QSize(Control::panelWidth700, Control::panelHeight500 +40));
 }
}
