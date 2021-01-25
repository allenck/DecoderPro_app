#ifndef LEARNSPEEDPANEL_H
#define LEARNSPEEDPANEL_H
#include "jinternalframe.h"
#include "warrant.h"
#include "jlabel.h"

class LearnSpeedPanel : public JInternalFrame
{
  Q_OBJECT

 public:
  LearnSpeedPanel(Warrant* w, QObject* parent = nullptr);
  /*public*/ void notifyAddressThrottleFound(DccThrottle* t);
  /*public*/ void destroy();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  static Logger* log;
  /*private*/ Warrant* _warrant;
  /*private*/ DccThrottle* _throttle;
  /*private*/ float _currentThrottleValue = 0.0;
  /*private*/ JLabel* _scaleSpeed;
  /*private*/ void initGUI();
  /*private*/ QString setSpeed();

};

#endif // LEARNSPEEDPANEL_H
