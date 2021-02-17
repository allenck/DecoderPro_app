#ifndef ABSTRACTPROGRAMMERTESTACTION_H
#define ABSTRACTPROGRAMMERTESTACTION_H
#include "abstractaction.h"

class Logger;
class AbstractProgrammerTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  AbstractProgrammerTestAction(QObject *parent);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // ABSTRACTPROGRAMMERTESTACTION_H
