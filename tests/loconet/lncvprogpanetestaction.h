#ifndef LNCVPROGPANETESTACTION_H
#define LNCVPROGPANETESTACTION_H

#include "abstractaction.h"

class Logger;
class LncvProgPaneTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit LncvProgPaneTestAction(QObject *parent = nullptr);

 signals:

 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // LNCVPROGPANETESTACTION_H
