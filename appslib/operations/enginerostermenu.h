#ifndef ENGINEROSTERMENU_H
#define ENGINEROSTERMENU_H
#include <QMenu>

class Logger;
namespace Operations
{
 class EngineRosterMenu : public QMenu
 {
  Q_OBJECT
 public:
  enum MENUTYPE
  {
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
  /*public*/ EngineRosterMenu(QString pMenuName, MENUTYPE pMenuType, QWidget* pWho);

  /**
   * Ctor argument defining that the menu object will be used as part of the
   * main menu of the program, away from any GUI that can select or use a
   * RosterEntry.
   */
 private:
  Logger* log;
 };
}
#endif // ENGINEROSTERMENU_H
