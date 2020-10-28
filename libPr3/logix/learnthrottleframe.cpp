#include "learnthrottleframe.h"
#include "dccthrottle.h"
#include "loconetthrottle.h"
#include "../LayoutEditor/warrantframe.h"
#include "instancemanager.h"
#include "powermanager.h"
#include "rosterentry.h"
#include "powerpane.h"
#include "logix/ltfcontrolpanel.h"
#include "logix/ltffunctionpanel.h"
#include "jdesktoppane.h"
#include <QActionGroup>
#include <QMenuBar>
#include <QMenu>

//LearnThrottleFrame::LearnThrottleFrame(QWidget *parent) :
//    JmriJFrame(parent)
//{
//}
/**
 *  A JFrame to contain throttle elements such as speed control,
 *  function panel.  It keeps a record of the throttle commands
 *  for playback later. <p>
 *
 *  Modeled on package jmri.jmrit.throttle by
 * @author     Glen Oberhauser
 * @author     Bob Jacobsen    Copyright 2008

 * @author     Pete Cressman   Copyright 2009
 * @version    $Revision: 22216 $
 */
/*static*/ int LearnThrottleFrame::STRUT_SIZE = 10;
///*public*/ class LearnThrottleFrame extends JmriJFrame implements java.beans.PropertyChangeListener
//{




    /**
     *  Default constructor
     */
/*public*/ LearnThrottleFrame::LearnThrottleFrame(WarrantFrame* warrantFrame, QWidget *parent) : JmriJFrame(false, false, parent)
    {
        //super(false, false);
        _warrantFrame = warrantFrame;
        powerControl  = new PowerPane();

        powerMgr = (PowerManager*)InstanceManager::getDefault("PowerManager");
        if (powerMgr == NULL) {
            log->info("No power manager instance found, panel not active");
        }
        else
            //powerMgr.addPropertyChangeListener(this);
            connect(powerMgr, SIGNAL(), this, SLOT());
//        initGUI();
        setVisible(true);
    }

    /**
     * Get notification that a throttle has been found as you requested.
     * @param t An instantiation of the DccThrottle with the address requested.
     */
    /*public*/ void LearnThrottleFrame::notifyThrottleFound(DccThrottle* t)
    {
        if(log->isDebugEnabled()) {
           log->debug("notifyThrottleFound address= " +((DccLocoAddress*)((LocoNetThrottle*)t)->getLocoAddress())->toString());
        }
        _throttle = t;
#if 1
        _controlPanel->notifyThrottleFound(t);
        _functionPanel->notifyThrottleFound(t);
        _buttonPanel->notifyThrottleFound(t);
        setSpeedSetting(0.0f);      // be sure loco is stopped.
#endif
        RosterEntry* train = _warrantFrame->getTrain();
        QString name = "";
        if (train != nullptr) {
            name = train->getId();
        }
        setWindowTitle(name+" ("+((DccLocoAddress*)((LocoNetThrottle*)t)->getLocoAddress())->toString()+")");
    }
#if 1
    /*private*/ void LearnThrottleFrame::initGUI()
    {
        setTitle("Throttle");
//        this.addWindowListener (new WindowAdapter() {
//                                   /*public*/ void windowClosing(WindowEvent e) {
//                                       _warrantFrame.stopRunTrain();
//                                       dispose();
//                                   }
//                               });
        this->addWindowListener(new LTFWindowListener(this));
        initializeMenu();
        _functionPanel = new LTFFunctionPanel(_warrantFrame->getTrain(), this);
        // assumes button width of 54, height of 30 (set in class FunctionButton) with
        // horiz and vert gaps of 5 each (set in FunctionPanel class)
        // with 3 buttons across and 6 rows high
        int width = 3*(FunctionButton::getButtonWidth()) + 2*3*5; 		// = 192
        int height = 6*(FunctionButton::getButtonHeight()) + 2*6*5 +10;	// = 240 (another 10 needed?)
        _functionPanel->resize(width, height);
        _functionPanel->setVisible(true);
        _functionPanel->setEnabled(false);
        //functionPanel.addInternalFrameListener(InternalFrameAdapter);

        _controlPanel = new LTFControlPanel(this);
        _controlPanel->setVisible(true);
        _controlPanel->setEnabled(false);
        _controlPanel->resize(_controlPanel->sizeHint().width(), height);

        _buttonPanel = new ButtonFrame(this);
        _buttonPanel->setVisible(true);
        _buttonPanel->setEnabled(false);
        _buttonPanel->resize(_controlPanel->getWidth()+_functionPanel->getWidth(), _buttonPanel->sizeHint().height());

//        _buttonPanel->setLocation(0, 0);
        _controlPanel->setLocation(0, _buttonPanel->getHeight());
        _functionPanel->setLocation(_controlPanel->getWidth(), _buttonPanel->getHeight());

        getContentPane()->layout()->addWidget(_buttonPanel);
        JDesktopPane* desktop = new JDesktopPane();
        getContentPane()->layout()->addWidget(desktop);
        desktop->layout()->addWidget(_controlPanel);
        desktop->layout()->addWidget(_functionPanel);

        desktop->resize(QSize(
                    qMax(_controlPanel->getWidth()+_functionPanel->getWidth(),_buttonPanel->getWidth()),
                    qMax(_functionPanel->getHeight(),_controlPanel->getHeight())+_buttonPanel->getHeight()));

        // Install the Key bindings on all Components
//        KeyListenerInstaller.installKeyListenerOnAllComponents(new ControlPadKeyListener(), this);
//        setResizable(false);
        pack();
    }


    /**
     *  Set up View, Edit and Power Menus
     */
    /*private*/ void LearnThrottleFrame::initializeMenu()
    {
     QMenu* speedControl = new QMenu(tr("SpeedControl"));
     QActionGroup* buttonGroup = new QActionGroup(this);
     QAction* displaySlider = new QAction(tr("DisplaySpeedSlider"));
     displaySlider->setCheckable(true);
     //displaySlider.addActionListener((ActionEvent e)->_controlPanel.setSpeedController(true));
     connect(displaySlider, &QAction::triggered, [=]{
      _controlPanel->setSpeedController(true);
     });
     displaySlider->setChecked(true);
     buttonGroup->addAction(displaySlider);
     speedControl->addAction(displaySlider);
     QAction* displaySteps = new QAction(tr("DisplaySpeedSteps"));
     //displaySteps.addActionListener((ActionEvent e)->_controlPanel.setSpeedController(false));
     connect(displaySteps, &QAction::triggered, [=]{
      _controlPanel->setSpeedController(false);
     });
     buttonGroup->addAction(displaySteps);
     speedControl->addAction(displaySteps);
     this->setMenuBar(new QMenuBar());
     this->menuBar()->addMenu(speedControl);

     if (powerMgr != nullptr) {
         QMenu* powerMenu = new QMenu(tr("Power"));
         QAction* powerOn = new QAction(tr("Power On"), this);
         powerMenu->addAction(powerOn);
         //powerOn.addActionListener((ActionEvent e)-> powerControl.onButtonPushed());
         connect(powerOn, &QAction::triggered, [=]{
          powerControl->onButtonPushed();
         });

         QAction* powerOff = new QAction(tr("Power Off"));
         powerMenu->addAction(powerOff);
         //powerOff.addActionListener((ActionEvent e) -> powerControl.offButtonPushed());
         connect(powerOff, &QAction::triggered, [=]{
          powerControl->offButtonPushed();
         });

         this->menuBar()->addMenu(powerMenu);
         powerLight = new QAction(this);//new JButton();
         setPowerIcons();
         this->menuBar()->addAction(powerLight);
     }
     // add help selection
     addHelpMenu("package.jmri.jmrit.throttle.ThrottleFrame", true);
    }

    /*public*/ void LearnThrottleFrame::dispose() {
        if (powerMgr!=NULL) powerMgr->removePropertyChangeListener((PropertyChangeListener*)this);
        _controlPanel->dispose();
        _functionPanel->dispose();
        JmriJFrame::dispose();
    }

    /**
     *  implement a property change listener for power and throttle
     *  Set the GUI's to correspond to the throttle settings
     */
    /*public*/ void LearnThrottleFrame::propertyChange(PropertyChangeEvent* evt) {
        if (log->isDebugEnabled()) log->debug("propertyChange "+evt->getPropertyName()+"= "+evt->getNewValue().toString());
        if (evt->getPropertyName() == "Power") {
            setPowerIcons();
        }
    }

#endif
    /**
    *  Record throttle commands that have been sent to the throttle.
    */
    /* from ControlPanel */
    /*protected*/ void LearnThrottleFrame::setSpeedSetting(float speed) {
        _warrantFrame->setThrottleCommand("Speed", QString::number(speed));
    }
    /* from ControlPanel */
    /*protected*/ void LearnThrottleFrame::setSpeedStepMode(SpeedStepMode::SSMODES speedStep) {
        _warrantFrame->setThrottleCommand("SpeedStep", QString::number(speedStep));
    }

    /* from FunctionPanel */
    /*protected*/ void LearnThrottleFrame::setFunctionState(int num, bool isSet) {
        _warrantFrame->setThrottleCommand("F"+QString::number(num), /*Boolean.toString(isSet)*/ isSet?"true":"false");
    }
    /* from FunctionPanel */
    /*protected*/ void LearnThrottleFrame::setFunctionState(QString FNum, bool isSet) {
        _warrantFrame->setThrottleCommand(FNum, /*Boolean.toString(isSet)*/ isSet?"true":"false");
    }
    /* from FunctionPanel */
    /*protected*/ void LearnThrottleFrame::setFunctionLock(int num, bool isLockable) {
        _warrantFrame->setThrottleCommand("LockF"+num, /*Boolean.toString(isLockable)*/ isLockable?"true":"false");
    }
    /* from FunctionPanel */
    /*protected*/ void LearnThrottleFrame::setFunctionLock(QString FMom, bool isLockable) {
        _warrantFrame->setThrottleCommand(FMom, /*Boolean.toString(isLockable)*/ isLockable?"true":"false");
    }
    /* from ControlPanel */
    /*protected*/ void LearnThrottleFrame::setButtonForward(bool isForward) {
        _buttonPanel->setForwardDirection(isForward);
        _warrantFrame->setThrottleCommand("Forward", /*Boolean.toString(isForward)*/ isForward?"true":"false");
    }
    /* from ButtonPanel */
    /*protected*/ void LearnThrottleFrame::setIsForward(bool isForward) {
        _throttle->setIsForward(isForward);
        //setButtonForward(isForward);
    }
    /*protected*/ void LearnThrottleFrame::stopRunTrain() {
        _warrantFrame->setThrottleCommand("Speed", "-1.0");
        _warrantFrame->stopRunTrain();
    }

    /**
     *  change the power LED displayed as appropriate and set corresponding tooltip
     *
     */
    /*public*/ void LearnThrottleFrame::setPowerIcons() {
        if (powerMgr==NULL) return;
        try {
            if (powerMgr->getPower()==PowerManager::ON) {
                powerLight->setIcon(/*powerOnIcon*/QIcon(QPixmap::fromImage(powerOnIcon->getImage())));
                powerLight->setToolTip(tr("Layout Power On.  Click light to turn off, or use Power menu"));
            }
            else if (powerMgr->getPower()==PowerManager::OFF) {
                powerLight->setIcon(QIcon(QPixmap::fromImage(powerOffIcon->getImage())));
                powerLight->setToolTip(tr("Layout Power Off.  Click light to turn on, or use Power menu"));
            }
            else if (powerMgr->getPower()==PowerManager::UNKNOWN) {
                powerLight->setIcon(QIcon(QPixmap::fromImage(powerXIcon->getImage())));
                powerLight->setToolTip(tr("Layout Power state unknown.  Click light to turn off, or use Power menu"));
            }
            else {
                powerLight->setIcon(QIcon(QPixmap::fromImage(powerXIcon->getImage())));
                powerLight->setToolTip(tr("Layout Power state unknown.  Click light to turn off, or use Power menu"));
                log->error("Unexpected state value: +"+powerMgr->getPower());
            }
        } catch (JmriException ex) {
            powerLight->setIcon(QIcon(QPixmap::fromImage(powerXIcon->getImage())));
            powerLight->setToolTip(tr("Layout Power state unknown.  Click light to turn off, or use Power menu"));
        }
    }
#if 0

    /**
     *  A KeyAdapter that listens for the keys that work the control pad buttons
     *
     * @author     glen
     * @version    $Revision: 22216 $
     */
    class ControlPadKeyListener extends KeyAdapter
    {
        /**
         *  Description of the Method
         *
         * @param  e  Description of the Parameter
         */
        /*public*/ void keyPressed(KeyEvent e)
        {
            if ( (e.getKeyCode() == accelerateKey) || (e.getKeyCode() == accelerateKey1) ) {
                _controlPanel.accelerate1();
            } else if ( e.getKeyCode() == accelerateKey2 ) {
                _controlPanel.accelerate10();
            } else if ( (e.getKeyCode() == decelerateKey) || (e.getKeyCode() == decelerateKey1) ) {
                _controlPanel.decelerate1();
            } else if ( e.getKeyCode() == decelerateKey2 ) {
                _controlPanel.decelerate10();
            } else if (e.getKeyCode() == forwardKey) {
                _buttonPanel.forwardButton.doClick();
            } else if (e.getKeyCode() == reverseKey) {
                _buttonPanel.reverseButton.doClick();
            } else if (e.getKeyCode() == stopKey) {
                _buttonPanel.stop();
            }
        }
    }

    class ButtonFrame extends JPanel {
        //private GridBagConstraints sliderConstraints;
        private JButton forwardButton, reverseButton;
        private JLabel forwardLight, reverseLight, stopLabel;
        private JButton stopButton;
        private int _gap;

        ButtonFrame() {
            super();
            forwardButton = new JButton(Bundle.getMessage("ButtonForward"));
            reverseButton = new JButton(Bundle.getMessage("ButtonReverse"));
            initGUI();
        }

        private void initGUI() {
            JPanel _buttonPanel = new JPanel();
            _buttonPanel.setLayout(new BoxLayout(_buttonPanel, BoxLayout.X_AXIS));
            add(_buttonPanel);

            GridBagConstraints constraints = new GridBagConstraints();
            constraints.anchor = GridBagConstraints.CENTER;
            //constraints.fill = GridBagConstraints.BOTH;
            constraints.gridheight = 1;
            constraints.gridwidth = 1;
            constraints.ipadx = 0;
            constraints.ipady = 0;
            Insets insets = new Insets(2, 2, 2, 2);
            constraints.insets = insets;
            constraints.weightx = 1;
            constraints.weighty = 1;
            constraints.gridx = 0;
            constraints.gridy = 0;

            forwardLight = new JLabel();
            forwardLight.setIcon(directionOffIcon);
            forwardButton.addActionListener(new ActionListener()  {
                                                /*public*/ void actionPerformed(ActionEvent e) {
                                                    setIsForward(true);
                                                }
                                            });
            JPanel forwardPanel = new JPanel();
            forwardPanel.setLayout(new GridBagLayout());
            forwardPanel.add(forwardLight, constraints);
            constraints.gridy = 1;
            forwardPanel.add(forwardButton, constraints);

            reverseLight = new JLabel();
            reverseLight.setIcon(directionOffIcon);
            reverseButton.addActionListener(new ActionListener() {
                                                /*public*/ void actionPerformed(ActionEvent e) {
                                                    setIsForward(false);
                                                }
                                            });
            JPanel reversePanel = new JPanel();
            reversePanel.setLayout(new GridBagLayout());
            constraints.gridy = 0;
            reversePanel.add(reverseLight, constraints);
            constraints.gridy = 1;
            reversePanel.add(reverseButton, constraints);

            stopLabel = new JLabel("Emergency");
            _gap = -(stopIcon.getIconWidth()+stopLabel.getPreferredSize().width)/2;
            stopButton = new JButton("Stop");
            stopButton.addActionListener(new ActionListener() {
                                             /*public*/ void actionPerformed(ActionEvent e)  {
                                                 stop();
                                             }
                                         });
            JPanel stopPanel = new JPanel();
            stopPanel.setLayout(new GridBagLayout());
            constraints.gridy = 0;
            stopPanel.add(stopLabel, constraints);
            constraints.gridy = 1;
            stopPanel.add(stopButton, constraints);

            _buttonPanel.add(Box.createHorizontalStrut(STRUT_SIZE));
            _buttonPanel.add(forwardPanel);
            _buttonPanel.add(Box.createHorizontalStrut(STRUT_SIZE));
            _buttonPanel.add(stopPanel);
            _buttonPanel.add(Box.createHorizontalStrut(STRUT_SIZE));
            _buttonPanel.add(reversePanel);
            _buttonPanel.add(Box.createHorizontalStrut(STRUT_SIZE));
            pack();
        }

        /**
         *  Perform an emergency stop
         */
        /*public*/ void stop()
        {
            _throttle.setSpeedSetting(-0.5F);
            //setSpeedSetting(-1);
            //setSpeedSetting(0);
            _throttle.setSpeedSetting(0.0F);
            stopLabel.setIcon(stopIcon);
            stopLabel.setIconTextGap(_gap);
            pack();
        }

        /*public*/ void notifyThrottleFound(DccThrottle t) {
            boolean isForward = t.getIsForward();
            this.setForwardDirection(isForward);
            setIsForward(isForward);
        }

        /**
         *  Set the GUI to match that the loco is set to forward.
         * @param  isForward  True if the loco is set to forward, false otherwise.
         */
        /*public*/ void setForwardDirection(boolean isForward) {
            if (isForward) {
                forwardLight.setIcon(directionOnIcon);
                reverseLight.setIcon(directionOffIcon);
            } else {
                forwardLight.setIcon(directionOffIcon);
                reverseLight.setIcon(directionOnIcon);
            }
            pack();
        }


    }
    #endif
