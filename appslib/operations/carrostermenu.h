#ifndef CARROSTERMENU_H
#define CARROSTERMENU_H
#include <QMenu>
#include "appslib_global.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT CarRosterMenu : public QMenu
 {
 public:

  enum MENUTYPES
  {
  /**
   * Ctor argument defining that the menu object will be used as part of the
   * main menu of the program, away from any GUI that can select or use a
   * RosterEntry.
   */
  MAINMENU = 1,

  /**
   * Ctor argument defining that the menu object will be used as a menu on a
   * GUI object that can select a RosterEntry.
   */
  SELECTMENU = 2,

  /**
   * Ctor argument defining that the menu object will be used as a menu on a
   * GUI object that is dealing with a single RosterEntry.
   */
   ENTRYMENU = 3
  };
  /*public*/ CarRosterMenu(QString pMenuName, MENUTYPES pMenuType, QWidget* pWho);

 };
}
#endif // CARROSTERMENU_H
