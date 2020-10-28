#ifndef LEARNTHROTTLEFRAME_H
#define LEARNTHROTTLEFRAME_H
#include "../LayoutEditor/jmrijframe.h"
#include "gridbagconstraints.h"
#include "gridbaglayout.h"
#include "jlabel.h"
#include "jbutton.h"
#include "namedicon.h"
#include "dccthrottle.h"
#include "box.h"
#include "windowlistener.h"
#include "warrantframe.h"

class PowerPane;
class LTFControlPanel;
class LTFFunctionPanel;
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
    /*public*/ void setPowerIcons();
    /*pulic*/ QString getClassName() {return "LearnThrottleFrame";}
 public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt);

signals:
private:
    /*private*/ LTFControlPanel* _controlPanel;
    /*private*/ LTFFunctionPanel* _functionPanel;
    /*private*/ ButtonFrame* _buttonPanel;
    /*private*/ WarrantFrame* _warrantFrame;
    /*private*/ DccThrottle* _throttle;
    PowerPane* powerControl;//  = new PowerPane();
    PowerManager* powerMgr = nullptr;
    QAction* powerLight = nullptr;
#if 1
    // Load the power lights as icons to be placed in an invisible JButton so the light
    // can be clicked to change the power status
    NamedIcon* powerOnIcon = new NamedIcon("resources/GreenPowerLED.gif", "resources/GreenPowerLED.gif");
    NamedIcon* powerOffIcon = new NamedIcon("resources/RedPowerLED.gif", "resources/RedPowerLED.gif");
    NamedIcon* powerXIcon = new NamedIcon("resources/YellowPowerLED.gif", "resources/YellowPowerLED.gif");
    NamedIcon* directionOnIcon = new NamedIcon("resources/icons/USS/sensor/amber-on.gif", "amber-on");
    NamedIcon* directionOffIcon = new NamedIcon("resources/icons/USS/sensor/amber-off.gif", "amber-off");
    NamedIcon* stopIcon = new NamedIcon("resources/icons/USS/sensor/red-on.gif", "red-on");
#endif
    Logger* log;
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
     friend class LTFControlPanel;
     friend class LTFFunctionPanel;
};

class ButtonFrame : public JPanel
{
  Q_OBJECT
    //private GridBagConstraints sliderConstraints;
    /*private*/ JButton *forwardButton, *reverseButton;
    /*private*/ JLabel *forwardLight, *reverseLight, *stopLabel;
    /*private*/ JButton* stopButton;
    /*private*/ int _gap;
    LearnThrottleFrame* frame;

public:
    ButtonFrame(LearnThrottleFrame* frame) {
     this->frame = frame;
        //super();
        forwardButton = new JButton(tr("Forward"));
        reverseButton = new JButton(tr("Reverse"));
        initGUI();
    }
private:
    /*private*/ void initGUI() {
        JPanel* _buttonPanel = new JPanel();
        _buttonPanel->setLayout(new QHBoxLayout());//_buttonPanel, BoxLayout.X_AXIS));
        layout()->addWidget(_buttonPanel);

        GridBagConstraints constraints = GridBagConstraints();
        constraints.anchor = GridBagConstraints::CENTER;
        //constraints.fill = GridBagConstraints.BOTH;
        constraints.gridheight = 1;
        constraints.gridwidth = 1;
        constraints.ipadx = 0;
        constraints.ipady = 0;
        Insets* insets = new Insets(2, 2, 2, 2);
        constraints.insets = insets;
        constraints.weightx = 1;
        constraints.weighty = 1;
        constraints.gridx = 0;
        constraints.gridy = 0;

        forwardLight = new JLabel();
        forwardLight->setIcon(frame->directionOffIcon);
        //forwardButton.addActionListener(new ActionListener()  {
        connect(forwardButton, &JButton::clicked, [=] {
//                                            /*public*/ void actionPerformed(ActionEvent e) {
                                                frame->setIsForward(true);
//                                            }
                                        });
        JPanel* forwardPanel = new JPanel();
        GridBagLayout* forwardPanelLayout;
        forwardPanel->setLayout(forwardPanelLayout = new GridBagLayout());
        forwardPanelLayout->addWidget(forwardLight, constraints);
        constraints.gridy = 1;
        forwardPanelLayout->addWidget(forwardButton, constraints);

        reverseLight = new JLabel();
        reverseLight->setIcon(frame->directionOffIcon);
//        reverseButton.addActionListener(new ActionListener() {
//                                            /*public*/ void actionPerformed(ActionEvent e) {
        connect(reverseLight, &JLabel::linkActivated, [=]{
                                                frame->setIsForward(false);
//                                            }
                                        });
        JPanel* reversePanel = new JPanel();
        GridBagLayout* reversePanelLayout;
        reversePanel->setLayout(reversePanelLayout =new GridBagLayout());
        constraints.gridy = 0;
        reversePanelLayout->addWidget(reverseLight, constraints);
        constraints.gridy = 1;
        reversePanelLayout->addWidget(reverseButton, constraints);

        stopLabel = new JLabel("Emergency");
        _gap = -(frame->stopIcon->getIconWidth()+stopLabel->sizeHint().width())/2;
        stopButton = new JButton("Stop");
//        stopButton.addActionListener(new ActionListener() {
//                                         /*public*/ void actionPerformed(ActionEvent e)  {
        connect(stopButton, &QPushButton::clicked, [=]{
                                             stop();
//                                         }
                                     });
        JPanel* stopPanel = new JPanel();
        GridBagLayout* stopPanelLayout;
        stopPanel->setLayout(stopPanelLayout = new GridBagLayout());
        constraints.gridy = 0;
        stopPanelLayout->addWidget(stopLabel, constraints);
        constraints.gridy = 1;
        stopPanelLayout->addWidget(stopButton, constraints);

        _buttonPanel->layout()->addWidget(Box::createHorizontalStrut(LearnThrottleFrame::STRUT_SIZE));
        _buttonPanel->layout()->addWidget(forwardPanel);
        _buttonPanel->layout()->addWidget(Box::createHorizontalStrut(LearnThrottleFrame::STRUT_SIZE));
        _buttonPanel->layout()->addWidget(stopPanel);
        _buttonPanel->layout()->addWidget(Box::createHorizontalStrut(LearnThrottleFrame::STRUT_SIZE));
        _buttonPanel->layout()->addWidget(reversePanel);
        _buttonPanel->layout()->addWidget(Box::createHorizontalStrut(LearnThrottleFrame::STRUT_SIZE));
        frame->pack();
    }

    /**
     *  Perform an emergency stop
     */
    /*public*/ void stop()
    {
        frame->_throttle->setSpeedSetting(-0.5F);
        //setSpeedSetting(-1);
        //setSpeedSetting(0);
        frame->_throttle->setSpeedSetting(0.0F);
        stopLabel->setIcon(frame->stopIcon);
//        stopLabel->setIconTextGap(_gap);
        frame->pack();
    }

    /*public*/ void notifyThrottleFound(DccThrottle* t) {
        bool isForward = t->getIsForward();
        this->setForwardDirection(isForward);
        frame->setIsForward(isForward);
    }

    /**
     *  Set the GUI to match that the loco is set to forward.
     * @param  isForward  True if the loco is set to forward, false otherwise.
     */
    /*public*/ void setForwardDirection(bool isForward) {
        if (isForward) {
            forwardLight->setIcon(frame->directionOnIcon);
            reverseLight->setIcon(frame->directionOffIcon);
        } else {
            forwardLight->setIcon(frame->directionOffIcon);
            reverseLight->setIcon(frame->directionOnIcon);
        }
        frame->pack();
    }
    friend class LearnThrottleFrame;
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
