#ifndef LNCVMESSAGECONTENTSCLASSTESTACTION_H
#define LNCVMESSAGECONTENTSCLASSTESTACTION_H
#include "abstractaction.h"

class Logger;
class LncvMessageContentsClassTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  LncvMessageContentsClassTestAction(QObject* parent);

 public slots:
  void actionPerformed();
 private:
  static Logger* log;

};

#endif // LNCVMESSAGECONTENTSCLASSTESTACTION_H
