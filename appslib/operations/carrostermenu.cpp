#include "carrostermenu.h"
#include "abstractaction.h"
#include "importrosterengineaction.h"
#include "logger.h"
#include "importcarrosteraction.h"

//CarRosterMenu::CarRosterMenu()
//{

//}
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
//*public*/ class CarRosterMenu extends JMenu {

    /**
     *
     */
    //private static final long serialVersionUID = -3092393314294283921L;


 /**
  * Create a
  *
  * @param pMenuName Name for the menu
  * @param pMenuType Select where the menu will be used, hence the right set
  *                  of items to be enabled.
  * @param pWho      The Component using this menu, used to ensure that
  *                  dialog boxes will pop in the right place.
  */
 /*public*/ CarRosterMenu::CarRosterMenu(QString pMenuName, MENUTYPES pMenuType, QWidget* pWho)
 : QMenu(pMenuName)
{
     //super(pMenuName);

     // create the menu
     AbstractAction* importAction = new ImportCarRosterAction(tr("MenuItemImport"),
             pWho);
#if 0
     importAction->setEnabled(false);
     AbstractAction exportAction = new ExportCarRosterAction(tr("MenuItemExport"),
             pWho);
     exportAction.setEnabled(false);
     AbstractAction deleteAction = new DeleteCarRosterAction(tr("MenuItemDelete"),
             pWho);
     deleteAction.setEnabled(false);
     AbstractAction resetMovesAction = new ResetCarMovesAction(
             tr("MenuItemResetMoves"), pWho);
     resetMovesAction.setEnabled(false);

     // Need a frame here, but are not passed one
     Frame newFrame = new Frame();
     AbstractAction printAction = new PrintCarRosterAction(tr("MenuItemPrint"),
             newFrame, false, pWho);
     printAction.setEnabled(false);
     AbstractAction previewAction = new PrintCarRosterAction(
             tr("MenuItemPreview"), newFrame, true, pWho);
     previewAction.setEnabled(false);
#endif
     addAction(importAction);
#if 0
     add(exportAction);
     add(deleteAction);
     add(resetMovesAction);
     add(printAction);
     add(previewAction);
#endif
     // activate the right items
     switch (pMenuType) {
         case MAINMENU:
             importAction->setEnabled(true);
#if 0
             exportAction.setEnabled(true);
             deleteAction.setEnabled(true);
             resetMovesAction.setEnabled(true);
             printAction.setEnabled(true);
             previewAction.setEnabled(true);
             break;
         case SELECTMENU:
             printAction.setEnabled(true);
             previewAction.setEnabled(true);
             break;
         case ENTRYMENU:
             printAction.setEnabled(true);
             previewAction.setEnabled(true);
             break;
#endif
         default:
             Logger::error("RosterMenu constructed without a valid menuType parameter: " + pMenuType);
     }
 }

}
