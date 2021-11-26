#include "operationssettingsframe.h"
#include "operationssettingspanel.h"
#include <QMenu>
#include "optionaction.h"
#include <QMenuBar>
#include "printoptionaction.h"
#include "buildreportoptionaction.h"
#include "backupfilesaction.h"
#include "restorefilesaction.h"
#include "loaddemoaction.h"
#include "resetaction.h"
#include "managebackupsaction.h"
#include "operationsmenu.h"
#include "control.h"

namespace Operations
{

 /**
  * Frame for user edit of operation parameters
 *
 * @author Dan Boudreau Copyright (C) 2008, 2010, 2011, 2012
 */
///*public*/ class OperationsSettingsFrame extends OperationsFrame {

    /*public*/ OperationsSettingsFrame::OperationsSettingsFrame(QWidget* parent) : OperationsFrame(tr("OperationsPro Settings"), new OperationsSettingsPanel(), parent) {
        //super(Bundle.getMessage("TitleOperationsSetup"), new OperationsSettingsPanel());
    }

    //@Override
    /*public*/ void OperationsSettingsFrame::initComponents() {
        OperationsFrame::initComponents();
        // build menu
        QMenuBar* menuBar = new QMenuBar();
        QMenu* toolMenu = new QMenu(tr("Tools"));
        toolMenu->addAction(new OptionAction(this));
        toolMenu->addAction(new PrintOptionAction(this));
        toolMenu->addAction(new BuildReportOptionAction(this));
        toolMenu->addAction(new BackupFilesAction(this));
        toolMenu->addAction(new RestoreFilesAction(this));
        toolMenu->addAction(new LoadDemoAction(this));
        toolMenu->addAction(new ResetAction(this));
        toolMenu->addAction(new ManageBackupsAction(this));

        menuBar->addMenu(toolMenu);
        menuBar->addMenu(new OperationsMenu());
        setMenuBar(menuBar);
        addHelpMenu("package.jmri.jmrit.operations.Operations_Settings", true); // NOI18N

        initMinimumSize(QSize(Control::panelWidth700, Control::panelHeight500));
    }
}
