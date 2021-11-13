#ifndef DIRECTMENU_H
#define DIRECTMENU_H

#include <QMenu>
#include "directsystemconnectionmemo.h"
class DirectMenu : public QMenu
{
 public:
  /*public*/ DirectMenu(QString name, DirectSystemConnectionMemo* memo);
  /*public*/ DirectMenu(DirectSystemConnectionMemo* memo);

 private:
  void common(DirectSystemConnectionMemo* memo);
};

#endif // DIRECTMENU_H
