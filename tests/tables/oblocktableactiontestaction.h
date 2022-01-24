#ifndef OBLOCKTABLEACTIONTESTACTION_H
#define OBLOCKTABLEACTIONTESTACTION_H
#include "abstractaction.h"

class Logger;
class OBlockTableActionTestAction : public AbstractAction
{Q_OBJECT
 public:
  OBlockTableActionTestAction(QWidget *parent);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // OBLOCKTABLEACTIONTESTACTION_H
