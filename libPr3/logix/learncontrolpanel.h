#ifndef LEARNCONTROLPANEL_H
#define LEARNCONTROLPANEL_H
#include "controlpanel.h"
#include <QRadioButton>
#include "jpanel.h"
#include "dccthrottle.h"

class LearnThrottleFrame;
class JSlider;
class JSpinner;
class SpinnerNumberModel;
class LearnControlPanel : public ControlPanel
{
  Q_OBJECT
 public:
  LearnControlPanel(LearnThrottleFrame* ltf);

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  static Logger* log;
  /*private*/ LearnThrottleFrame* _throttleFrame;


};

#endif // LEARNCONTROLPANEL_H
