#include "rostermenu.h"
#include "rosterframe.h"
#include "instancemanager.h"
#include "createrostergroupaction.h"
#include "instancemanager.h"
#include "panenewprogaction.h"
#include "paneeditaction.h"
#include "copyrosteritemaction.h"
#include "deleterosteritemaction.h"
#include "rosterframeaction.h"
#include "importrosteritemaction.h"
#include "exportrosteritemaction.h"
#include "deleterostergroupaction.h"
#include "rosterentrytogroupaction.h"
#include "removerosterentrytogroupaction.h"
#include "rostergrouptableaction.h"
#include "fullbackupexportaction.h"
#include "fullbackupimportaction.h"
#include "speedprofileaction.h"
#include "printrosteraction.h"

//RosterMenu::RosterMenu(QWidget *parent) :
//    QMenu(parent)
//{
//}

/**
 * Provides a context-specific menu for handling the Roster.
 * <P>
 *
 * @author	Bob Jacobsen   Copyright (C) 2001, 2002, 2008
 * @author  Dennis Miller  Copyright (C) 2005
 * @version	$Revision: 20080 $
 * @see jmri.jmrit.roster.RosterEntry
 * @see jmri.jmrit.roster.Roster
 */
// /*public*/ class RosterMenu extends JMenu {

    /**
     * Create a menu of Roster tools.
     * @param pMenuName Name for the menu
     * @param pMenuType Select where the menu will be used, hence the
     *                  right set of items to be enabled.
     * @param pWho      The Component using this menu, used to ensure that
     *                  dialog boxes will pop in the right place.
     */
/*public*/ RosterMenu::RosterMenu(QString pMenuName, int pMenuType, QWidget* pWho) : QMenu(pMenuName, pWho)
{
 //super(pMenuName);

//        ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle");

    // create the menu

    QAction* dp3Action = new RosterFrameAction(tr("Roster"),false, pWho);
    dp3Action->setEnabled(true);

    QAction* createAction = new PaneNewProgAction(tr("Create"),this);
    createAction->setEnabled(false);

    QAction* editAction = new PaneEditAction(tr("Edit"),this);
    editAction->setEnabled(false);

    QAction* importAction = new ImportRosterItemAction(tr("Import"), pWho);
    importAction->setEnabled(false);

    QAction* exportAction = new ExportRosterItemAction(tr("Export"), pWho);
    exportAction->setEnabled(false);

    QAction* copyAction = new CopyRosterItemAction(tr("Copy"), pWho);
    copyAction->setEnabled(false);

    QAction* deleteAction = new DeleteRosterItemAction(tr("Delete"), pWho);
    deleteAction->setEnabled(false);

    QAction* deleteGroupAction = new DeleteRosterGroupAction(tr("Delete Roster Group"), pWho);
    deleteGroupAction->setEnabled(false);

    QAction* createGroupAction = new CreateRosterGroupAction(tr("Group Create"), pWho);
    createGroupAction->setEnabled(false);

    QAction* rosterEntryToGroupAction = new RosterEntryToGroupAction(tr("Add Roster Entry to Group"), pWho);
    rosterEntryToGroupAction->setEnabled(false);

    QAction* removeRosterEntryToGroupAction = new RemoveRosterEntryToGroupAction(tr("Remove Roster Entry from Group"), pWho);
    removeRosterEntryToGroupAction->setEnabled(false);

    QAction* rosterGroupTableAction = new RosterGroupTableAction(tr("Table Association"),this);
    rosterGroupTableAction->setEnabled(false);

    QAction* rosterExportAction = new FullBackupExportAction(tr("Export Complete Roster..."), pWho);
    rosterExportAction->setEnabled(false);

    QAction* rosterImportAction = new FullBackupImportAction(tr("Import Exported Roster.."), pWho);
    rosterImportAction->setEnabled(false);

    QAction* speedProfileAction = new SpeedProfileAction(tr("Speed Profiling"),this);
    speedProfileAction->setEnabled(false);
#if 1
    // Need a frame here, but are not passed one
    JmriJFrame* newFrame = new JmriJFrame();
    QAction* printAction = new PrintRosterAction(tr("Print Summary..."), newFrame, false,this);
    printAction->setEnabled(false);
    QAction* previewAction = new PrintRosterAction(tr("Print Preview Summary..."), newFrame, true, this);
    printAction->setEnabled(false);
#endif
    QMenu* groupMenu = new QMenu(tr("Roster Groups"));
    groupMenu->addAction(createGroupAction);
    groupMenu->addAction(deleteGroupAction);
    groupMenu->addAction(rosterGroupTableAction);
    groupMenu->addAction(rosterEntryToGroupAction);
    groupMenu->addAction(removeRosterEntryToGroupAction);


    addAction(dp3Action);
    addSeparator();
    addAction(createAction);
    addAction(editAction);
    addAction(copyAction);
    addAction(importAction);
    addAction(exportAction);
    addAction(deleteAction);
    addAction(printAction);
    addAction(previewAction);
    addSeparator();
    addMenu(groupMenu);
    addSeparator();
    addAction(rosterExportAction);
    addAction(rosterImportAction);
    addAction(speedProfileAction);

    // activate the right items
    switch (pMenuType)
    {
     case MAINMENU:
         createAction->setEnabled(true);
         editAction->setEnabled(true);
         deleteAction->setEnabled(true);
         importAction->setEnabled(true);
         exportAction->setEnabled(true);
         copyAction->setEnabled(true);
         deleteGroupAction->setEnabled(true);
         createGroupAction->setEnabled(true);
         rosterEntryToGroupAction->setEnabled(true);
         removeRosterEntryToGroupAction->setEnabled(true);
         printAction->setEnabled(true);
         previewAction->setEnabled(true);
         rosterGroupTableAction->setEnabled(true);
         rosterExportAction->setEnabled(true);
         rosterImportAction->setEnabled(true);
         speedProfileAction->setEnabled(true);
     break;
     case SELECTMENU:
//            printAction.setEnabled(true);
//            previewAction.setEnabled(true);
         break;
     case ENTRYMENU:
//            printAction.setEnabled(true);
//            previewAction.setEnabled(true);
         break;
     default:
         log->error("RosterMenu constructed without a valid menuType parameter: " +QString::number(pMenuType));
 }
}
