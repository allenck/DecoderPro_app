#ifndef FUNCTIONPANEL_H
#define FUNCTIONPANEL_H
#include "jinternalframe.h"
#include "jpanel.h"
#include "jtogglebutton.h"
#include "functionbutton.h"
#include "functionlistener.h"

class DccThrottle;
class LearnThrottleFrame;
class Logger;
class LTFFunctionPanel : public JInternalFrame, public FunctionListener
{
  Q_OBJECT
  Q_INTERFACES(FunctionListener)
 public:
  /*public*/ LTFFunctionPanel(RosterEntry* rosterEntry, LearnThrottleFrame* learnFrame);

  /*public*/ static /*final*/ int NUM_FUNCTION_BUTTONS;// = 29;
  /*public*/ static /*final*/ int NUM_FUNC_BUTTONS_INIT;// = 16; //only show 16 function buttons at start
  /*public*/ void notifyThrottleFound(DccThrottle* t);
  /*public*/ void dispose() override;
  /*public*/ void notifyFunctionStateChanged(int functionNumber, bool isSet) override;
  /*public*/ void notifyFunctionLockableChanged(int functionNumber, bool isLockable) override;
  /*public*/ void setEnabled(bool isEnabled) override;
  /*public*/ void initGUI();
  /*public*/ void buttonActionCmdPerformed();
  /*public*/ void showAllFnButtons();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) /*override*/;

 private:
  static Logger* log;
  /*private*/ DccThrottle* _throttle;
  /*private*/ /*final*/ RosterEntry* _rosterEntry;
  /*private*/ /*final*/ LearnThrottleFrame* _throttleFrame;
  /*private*/ /*final*/ JPanel* mainPanel;

  /*private*/ QVector<FunctionButton*> functionButton;
  /*private*/ /*final*/ JToggleButton* alt1Button;
  /*private*/ /*final*/ JToggleButton* alt2Button;
};

#endif // FUNCTIONPANEL_H
