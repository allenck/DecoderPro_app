#ifndef LNCVPROGTABLEMODELTESTACTION_H
#define LNCVPROGTABLEMODELTESTACTION_H
#include "abstractaction.h"

class Logger;
class LncvProgTableModelTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  LncvProgTableModelTestAction(QObject* parent);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // LNCVPROGTABLEMODELTESTACTION_H
