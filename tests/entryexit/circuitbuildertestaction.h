#ifndef CIRCUITBUILDERTESTACTION_H
#define CIRCUITBUILDERTESTACTION_H
#include "abstractaction.h"

class Logger;
class CircuitBuilderTestAction : public AbstractAction
{
 Q_OBJECT
public:
 CircuitBuilderTestAction(QObject *parent);
 public slots:
  void actionPerformed();

 private:
  static Logger* log;
};

#endif // CIRCUITBUILDERTESTACTION_H
