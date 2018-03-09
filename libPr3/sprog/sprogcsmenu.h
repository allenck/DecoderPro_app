#ifndef SPROGCSMENU_H
#define SPROGCSMENU_H
#include "menu.h"
#include "sprogsystemconnectionmemo.h"

namespace Sprog
{
 class SPROGCSMenu : public Menu
 {
 public:
  SPROGCSMenu(SprogSystemConnectionMemo* memo, QWidget* frame = 0);

 private:
  /*private*/ SprogSystemConnectionMemo* _memo;// = null;

 };
}
#endif // SPROGCSMENU_H
