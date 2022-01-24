#ifndef LEARNTHROTTLEFRAME_H
#define LEARNTHROTTLEFRAME_H
#include "jmrijframe.h"
#include "gridbagconstraints.h"
#include "gridbaglayout.h"
#include "jlabel.h"
#include "jbutton.h"
#include "namedicon.h"
#include "dccthrottle.h"
#include "box.h"
#include "windowlistener.h"
#include "warrantframe.h"

class LearnSpeedPanel;
class PowerPane;
class LearnControlPanel;
class LearnFunctionPanel;
class ButtonFrame;
class PowerManager;
class WarrantFrame;
class DccThrottle;
class LearnThrottleFrame : public JmriJFrame
{
    Q_OBJECT
public:
    //explicit LearnThrottleFrame(QWidget *parent = 0);
    static int STRUT_SIZE;// = 10;
    /*public*/ LearnThrottleFrame(WarrantFrame* warrantFrame, QWidget *parent = 0);

#if 0
    /*public*/ int accelerateKey = 107; // numpad +;
    /*public*/ int decelerateKey = 109; // numpad -;
    /*public*/ int accelerateKey1 = KeyEvent.VK_LEFT ; // Left Arrow
    /*public*/ int decelerateKey1 = KeyEvent.VK_RIGHT ; // Left Arrow
    /*public*/ int accelerateKey2 = KeyEvent.VK_PAGE_UP ; // Left Arrow
    /*public*/ int decelerateKey2 = KeyEvent.VK_PAGE_DOWN ; // Left Arrow
    /*public*/ int reverseKey = KeyEvent.VK_DOWN;
    /*public*/ int forwardKey = KeyEvent.VK_UP;
    /*public*/ int stopKey = 111; // numpad /
    /*public*/ int idleKey = 106; // numpad *
   #endif
    /*public*/ void notifyThrottleFound(DccThrottle* t);
    /*public*/ void dispose() override;
    /*pulic*/ QString getClassName() {return "LearnThrottleFrame";}

 public slots:

signals:
private:
    /*private*/ LearnControlPanel* _controlPanel;
    /*private*/ LearnFunctionPanel* _functionPanel;
    /*private*/ LearnSpeedPanel* _speedPanel;
    /*private*/ WarrantFrame* _warrantFrame;
    /*private*/ DccThrottle* _throttle;
    PowerManager* powerMgr = nullptr;
    static Logger* log;
    /*private*/ void initGUI();
    /*private*/ void initializeMenu();

public slots:
protected:
    /*protected*/ void setSpeedSetting(float speed);
    /*protected*/ void setSpeedStepMode(SpeedStepMode::SSMODES speedStep);
    /*protected*/ void setFunctionState(int num, bool isSet);
    /*protected*/ void setFunctionState(QString FNum, bool isSet);
    /*protected*/ void setFunctionLock(int num, bool isLockable);
    /*protected*/ void setFunctionLock(QString FMom, bool isLockable);
    /*protected*/ void setButtonForward(bool isForward);
    /*protected*/ void setIsForward(bool isForward);
    /*protected*/ void stopRunTrain();
     friend class WarrantFrame;
     friend class ButtonFrame;
     friend class LTFWindowListener;
     friend class LearnControlPanel;
     friend class LearnFunctionPanel;
};


class LTFWindowListener : public WindowListener
{
  Q_OBJECT
  LearnThrottleFrame* frame;
 public:
  LTFWindowListener(LearnThrottleFrame* frame) {this->frame = frame;}
  void windowClosing(QCloseEvent *) {
   frame->_warrantFrame->stopRunTrain();
   frame->dispose();

  }
};
#endif // LEARNTHROTTLEFRAME_H
