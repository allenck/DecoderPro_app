#ifndef LEARNTHROTTLEFRAME_H
#define LEARNTHROTTLEFRAME_H
#include "../LayoutEditor/jmrijframe.h"

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

signals:
private:
#if 0
    /*private*/ ControlPanel _controlPanel;
    /*private*/ FunctionPanel _functionPanel;
    /*private*/ ButtonFrame _buttonPanel;
#endif
    /*private*/ WarrantFrame* _warrantFrame;
    /*private*/ DccThrottle* _throttle;
#if 0
    PowerPane powerControl  = new PowerPane();
#endif
    PowerManager* powerMgr;// = null;
#if 0
    JButton powerLight;
    // Load the power lights as icons to be placed in an invisible JButton so the light
    // can be clicked to change the power status
    NamedIcon powerOnIcon = new NamedIcon("resources/GreenPowerLED.gif", "resources/GreenPowerLED.gif");
    NamedIcon powerOffIcon = new NamedIcon("resources/RedPowerLED.gif", "resources/RedPowerLED.gif");
    NamedIcon powerXIcon = new NamedIcon("resources/YellowPowerLED.gif", "resources/YellowPowerLED.gif");
    NamedIcon directionOnIcon = new NamedIcon("resources/icons/USS/sensor/amber-on.gif", "amber-on");
    NamedIcon directionOffIcon = new NamedIcon("resources/icons/USS/sensor/amber-off.gif", "amber-off");
    NamedIcon stopIcon = new NamedIcon("resources/icons/USS/sensor/red-on.gif", "red-on");
#endif
    Logger* log;
public slots:

};

#endif // LEARNTHROTTLEFRAME_H
