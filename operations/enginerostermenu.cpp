#include "enginerostermenu.h"
#include "logger.h"
#include "importrosterengineaction.h"
namespace Operations
{
/**
 * Provides a context-specific menu for handling the Roster.
 * <P>
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2002
 * @author Dennis Miller Copyright (C) 2005
 * @author Daniel Boudreau Copyright (C) 2007, 2012
 * @version $Revision: 28771 $
 *
 */
///*public*/ class EngineRosterMenu extends JMenu {

  /**
   *
   */
  //private static final long serialVersionUID = -2345195873048319343L;


  /**
   * Create a
   *
   * @param pMenuName Name for the menu
   * @param pMenuType Select where the menu will be used, hence the right set
   *                  of items to be enabled.
   * @param pWho      The Component using this menu, used to ensure that
   *                  dialog boxes will pop in the right place.
   */
  /*public*/ EngineRosterMenu::EngineRosterMenu(QString pMenuName, MENUTYPE pMenuType, QWidget* pWho)
   : QMenu(pMenuName)
{
      //super(pMenuName);

      // create the menu
      AbstractAction* importRosterAction = new ImportRosterEngineAction(
              tr("Import from JMRI roster"), pWho);
#if 0
      importRosterAction.setEnabled(false);
      AbstractAction exportAction = new ExportEngineRosterAction(
              tr("MenuItemExport"), pWho);
      exportAction.setEnabled(false);
      AbstractAction importAction = new ImportEngineAction(tr("MenuItemImport"),
              pWho);
      importAction.setEnabled(false);
      AbstractAction deleteAction = new DeleteEngineRosterAction(
              tr("MenuItemDelete"), pWho);
      deleteAction.setEnabled(false);
      AbstractAction resetMovesAction = new ResetEngineMovesAction(
              tr("MenuItemResetMoves"), pWho);
      resetMovesAction.setEnabled(false);

      // Need a frame here, but are not passed one
      Frame newFrame = new Frame();
      AbstractAction printAction = new PrintEngineRosterAction(tr("MenuItemPrint"),
              newFrame, false, pWho);
      printAction.setEnabled(false);
      AbstractAction previewAction = new PrintEngineRosterAction(
              tr("MenuItemPreview"), newFrame, true, pWho);
      printAction.setEnabled(false);
#endif
      addAction(importRosterAction);
#if 0
      add(importAction);
      add(exportAction);
      add(deleteAction);
      add(resetMovesAction);
      add(printAction);
      add(previewAction);
#endif
      // activate the right items
      switch (pMenuType) {
          case MAINMENU:
              importRosterAction->setEnabled(true);
#if 0
              exportAction.setEnabled(true);
              importAction.setEnabled(true);
              deleteAction.setEnabled(true);
              resetMovesAction.setEnabled(true);
              printAction.setEnabled(true);
              previewAction.setEnabled(true);
#endif
              break;
          case SELECTMENU:
#if 0
              printAction.setEnabled(true);
              previewAction.setEnabled(true);
#endif
              break;
          case ENTRYMENU:
#if 0
              printAction.setEnabled(true);
              previewAction.setEnabled(true);
#endif
              break;
          default:
              log->error("RosterMenu constructed without a valid menuType parameter: " + QString::number(pMenuType));
      }
  }

}
