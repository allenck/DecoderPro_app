#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H
#include "jinternalframe.h"
#include <QRadioButton>
#include "jpanel.h"
#include "dccthrottle.h"

class LearnThrottleFrame;
class JSlider;
class JSpinner;
class SpinnerNumberModel;
class LTFControlPanel : public JInternalFrame
{
  Q_OBJECT
 public:
  LTFControlPanel(LearnThrottleFrame* ltf);
  /*public*/ void notifyThrottleFound(DccThrottle* t);
  /*public*/ void dispose() override;
  /*public*/ void setEnabled(bool isEnabled) override;
  /*public*/ void setSpeedSteps(SpeedStepMode *steps);
  /*public*/ void setSpeedController(bool displaySlider);
  /*public*/ void setSpeedValues(int speedIncrement, int speed);
  /*public*/ void accelerate1();
  /*public*/ void accelerate10();
  /*public*/ void decelerate1();
  /*public*/ void decelerate10();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  static Logger* log;
  /*private*/ LearnThrottleFrame* _throttleFrame;

  /*private*/ JSlider* speedSlider;
  /*private*/ JSpinner* speedSpinner;
  /*private*/ SpinnerNumberModel* speedSpinnerModel;
  /*private*/ QRadioButton* speedStep128Button;
  /*private*/ QRadioButton* speedStep28Button;
  /*private*/ QRadioButton* speedStep27Button;
  /*private*/ QRadioButton* speedStep14Button;

  /*private*/ JPanel* spinnerPanel;
  /*private*/ JPanel* sliderPanel;

  /*private*/ bool _displaySlider = true;
  /*private*/ bool speedControllerEnable;

  /*private*/ DccThrottle* _throttle;
  /*private*/ bool internalAdjust = false;

  /*private*/ long trackSliderMinInterval = 500;          // milliseconds
  /*private*/ long lastTrackedSliderMovementTime = 0;

  // DCC really only has 126 speed steps i.e. 0..127 - 1 for em stop
  /*private*/ int MAX_SPEED = 126;
  /*private*/ void initGUI();
  /*private*/ void configureAvailableSpeedStepModes();

};

#endif // CONTROLPANEL_H
