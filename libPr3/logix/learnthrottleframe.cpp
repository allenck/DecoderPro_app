#include "learnthrottleframe.h"
#include "dccthrottle.h"
#include "loconetthrottle.h"
#include "../LayoutEditor/warrantframe.h"
#include "instancemanager.h"
#include "powermanager.h"
#include "rosterentry.h"
#include "powerpane.h"
#include "logix/learncontrolpanel.h"
#include "logix/learnfunctionpanel.h"
#include "jdesktoppane.h"
#include <QActionGroup>
#include <QMenuBar>
#include <QMenu>
#include "speedutil.h"
#include "learnspeedpanel.h"
#include "loggerfactory.h"

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

        _controlPanel->notifyAddressThrottleFound(t);
        _functionPanel->notifyAddressThrottleFound(t);
        _speedPanel->notifyAddressThrottleFound(t);
        setSpeedSetting(0.0f);      // be sure loco is stopped.

        setButtonForward(t->getIsForward());
        RosterEntry* re = _warrantFrame->_speedUtil->getRosterEntry();
        QString name;
        if (re != nullptr) {
            name = re->getId();
        } else {
            name = _warrantFrame->getTrainName();
        }
        setTitle(name + " (" + t->getLocoAddress()->toString() + ")");}

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

        _controlPanel = new LearnControlPanel(this);
     _controlPanel->setVisible(true);
     _controlPanel->setEnabled(false);
     _controlPanel->setWindowTitle(tr("Speed"));
     _controlPanel->resize(_controlPanel->sizeHint());

     int width = 3 * (FunctionButton::getButtonWidth()) + 2 * 3 * 5 + 11;   // = 192
     int height = 6 * (FunctionButton::getButtonHeight()) + 2 * 6 * 5 + 20; // FunctionButton.BUT_IMG_SIZE = 45
     _functionPanel = new LearnFunctionPanel(this);
     _functionPanel->resize(width, height);
     _functionPanel->setVisible(true);
     _functionPanel->setEnabled(false);
     _functionPanel->setWindowTitle(tr("Function Key"));

     _speedPanel = new LearnSpeedPanel(_warrantFrame->getWarrant());
     _speedPanel->resize(_functionPanel->width(), _controlPanel->height() - _functionPanel->height());
     _speedPanel->setVisible(true);
//     _speedPanel->setClosable(true);
     _speedPanel->setTitle(tr("Speed Panel"));

     _controlPanel->move(0, 0);
     _functionPanel->move(_controlPanel->width(), 0);
     _speedPanel->move(_controlPanel->width(), _functionPanel->height());

     JDesktopPane* desktop = new JDesktopPane();
     getContentPane()->layout()->addWidget(desktop);
     desktop->layout()->addWidget(_controlPanel);
     desktop->layout()->addWidget(_functionPanel);
     desktop->layout()->addWidget(_speedPanel);

     desktop->resize(QSize(
             _controlPanel->width() + _functionPanel->width(), _controlPanel->height()));

//     setResizable(false);
//     jmri.util.PlaceWindow.getDefault().nextTo(_warrantFrame, null, this);
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
//         powerOn.addActionListener(new ActionListener() {

//             @Override
//             public void actionPerformed(ActionEvent e) {
         connect(powerOn, &QAction::triggered, [=]{
                 try {
                     powerMgr->setPower(PowerManager::ON);
                 } catch (JmriException e1) {
                     log->error(tr("Error when setting power %1").arg(e1.getMessage()));
                 }
         });

         QAction* powerOff = new QAction(tr("Power Off"),this);
         powerMenu->addAction(powerOff);
//         powerOff.addActionListener(new ActionListener() {

//             @Override
//             public void actionPerformed(ActionEvent e) {
         connect(powerOff, &QAction::triggered, [=]{
                 try {
                     powerMgr->setPower(PowerManager::OFF);
                 } catch (JmriException e1) {
                     log->error(tr("Error when setting power %1").arg(e1.getMessage()));
                 }
//             }
         });

         this->menuBar()->addMenu(powerMenu);
     }
     // add help selection
     addHelpMenu("package.jmri.jmrit.throttle.ThrottleFrame", true);
    }

    /*public*/ void LearnThrottleFrame::dispose() {
        if (powerMgr!=NULL) powerMgr->removePropertyChangeListener((PropertyChangeListener*)this);
        _controlPanel->dispose();
        JmriJFrame::dispose();
    }

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

      /*private*/ /*static*/ /*final*/ Logger* LearnThrottleFrame::log = LoggerFactory::getLogger("LearnThrottleFrame");
