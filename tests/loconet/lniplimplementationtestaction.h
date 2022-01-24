#ifndef LNIPLIMPLEMENTATIONTESTACTION_H
#define LNIPLIMPLEMENTATIONTESTACTION_H
#include "abstractaction.h"
class Logger;
class LnIplImplementationTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  LnIplImplementationTestAction(QObject* parent);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // LNIPLIMPLEMENTATIONTESTACTION_H
