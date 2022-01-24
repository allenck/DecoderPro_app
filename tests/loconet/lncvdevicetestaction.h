#ifndef LNCVDEVICETESTACTION_H
#define LNCVDEVICETESTACTION_H
#include "abstractaction.h"

class Logger;
class LncvDeviceTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  LncvDeviceTestAction(QObject* parent);

 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // LNCVDEVICETESTACTION_H
