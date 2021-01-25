#ifndef LEARNFUNCTIONPANEL_H
#define LEARNFUNCTIONPANEL_H
#include "functionpanel.h"
#include "jpanel.h"
#include "jtogglebutton.h"
#include "functionbutton.h"
#include "functionlistener.h"

class DccThrottle;
class LearnThrottleFrame;
class Logger;
class LearnFunctionPanel : public FunctionPanel
{
  Q_OBJECT
  //Q_INTERFACES(FunctionListener)
 public:
  /*public*/ LearnFunctionPanel(LearnThrottleFrame* learnFrame);

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) /*override*/;

 private:
  static Logger* log;
  /*private*/ /*final*/ LearnThrottleFrame* _throttleFrame;
};

#endif // LEARNFUNCTIONPANEL_H
