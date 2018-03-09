#ifndef SPROGMENU_H
#define SPROGMENU_H
#include "menu.h"
#include "sprogsystemconnectionmemo.h"

namespace Sprog
{
 class SPROGMenu : public Menu
 {
 public:
  /*public*/ SPROGMenu(SprogSystemConnectionMemo* memo, QWidget* frame);

 };
}
#endif // SPROGMENU_H
