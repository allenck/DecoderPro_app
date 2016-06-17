#include "carrostermenu.h"
#include "abstractaction.h"
#include "importrosterengineaction.h"
#include "logger.h"
#include "importcarrosteraction.h"
#include "exportcarrosteraction.h"
#include "printcarrosteraction.h"
#include "jframe.h"
#include "deletecarrosteraction.h"
#include "resetcarmovesaction.h"

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
  AbstractAction* importAction = new ImportCarRosterAction(tr("Import"),
          pWho);

  importAction->setEnabled(false);
  AbstractAction* exportAction = new ExportCarRosterAction(tr("Export"),
          pWho);
  exportAction->setEnabled(false);
  AbstractAction* deleteAction = new DeleteCarRosterAction(tr("Delete"),
          pWho);
  deleteAction->setEnabled(false);
  AbstractAction* resetMovesAction = new ResetCarMovesAction(
          tr("Reset Moves"), pWho);
  resetMovesAction->setEnabled(false);
  // Need a frame here, but are not passed one
  JFrame* newFrame = new JFrame();
  AbstractAction* printAction = new PrintCarRosterAction(tr("Print"),
          newFrame, false, pWho);
  printAction->setEnabled(false);
  AbstractAction* previewAction = new PrintCarRosterAction(
          tr("Preview"), newFrame, true, pWho);
  previewAction->setEnabled(false);
  addAction(importAction);
  addAction(exportAction);
  addAction(deleteAction);
  addAction(resetMovesAction);
  addAction(printAction);
  addAction(previewAction);
  // activate the right items
  switch (pMenuType)
  {
   case MAINMENU:
       importAction->setEnabled(true);
       exportAction->setEnabled(true);
       deleteAction->setEnabled(true);
       resetMovesAction->setEnabled(true);
       printAction->setEnabled(true);
       previewAction->setEnabled(true);
       break;
   case SELECTMENU:
       printAction->setEnabled(true);
       previewAction->setEnabled(true);
       break;
   case ENTRYMENU:
       printAction->setEnabled(true);
       previewAction->setEnabled(true);
       break;
   default:
       Logger::error("RosterMenu constructed without a valid menuType parameter: " + pMenuType);
  }
 }

}
