#ifndef LOGIXNGMENU_H
#define LOGIXNGMENU_H

#include <QMenu>

class LogixNGMenu : public QMenu
{
 public:
  LogixNGMenu();
  /*public*/  LogixNGMenu(QString name);

 private:
  void common();
};

#endif // LOGIXNGMENU_H
