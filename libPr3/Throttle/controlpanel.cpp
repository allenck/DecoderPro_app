#include "controlpanel.h"
#include <QSlider>
#include <QSpinBox>
#include <QRadioButton>
#include "dccthrottle.h"
#include "abstractthrottle.h"
#include <QLabel>
#include "instancemanager.h"
#include "learnthrottleframe.h"
#include <QVBoxLayout>
#include "jframe.h"
#include "gridbagconstraints.h"
#include <QSlider>
#include <QButtonGroup>
#include "flowlayout.h"
#include "jlabel.h"
#include <QPushButton>
#include "namedicon.h"
#include "windowpreferences.h"
#include "addresspanel.h"
#include "rosterentry.h"
#include "throttleframemanager.h"
#include "throttlespreferences.h"
#include "fileutil.h"
#include "gridbagconstraints.h"
#include "gridbaglayout.h"
#include "myslider.h"
#include <QSize>
#include "controlpanelpropertyeditor.h"

//ControlPanel::ControlPanel(QWidget *parent) :
//    QDockWidget(parent)
//{
//}
/**
 *  A JInternalFrame that contains a JSlider to control loco speed, and buttons
 *  for forward, reverse and STOP.
 *  <P>
 *  TODO: fix speed increments (14, 28)
 *
 * @author     glen   Copyright (C) 2002
 * @author Bob Jacobsen Copyright (C) 2007
 * @author Ken Cameron Copyright (C) 2008
 *
 * @version    $Revision: 22216 $
 */
///*public*/ class ControlPanel extends JInternalFrame implements java.beans.PropertyChangeListener
//{
/*final*/ /*public*/ /*static*/ int ControlPanel::BUTTON_SIZE = 40;

// Save the speed step mode to aid in storage of the throttle.
///*private*/ int _speedStepMode = DccThrottle::SpeedStepMode128;
/**
 *  Constructor.
 */
/*public*/ ControlPanel::ControlPanel(LearnThrottleFrame* ltf, QWidget *parent) : QDockWidget(tr("Speed"),parent)
{
 //super("Speed");
 _displaySlider = SLIDERDISPLAY;
 speedControllerEnable = false;
 _emergencyStop = false;

 _throttle = NULL;
 internalAdjust = false;

 trackSliderMinInterval = 500;          // milliseconds
 lastTrackedSliderMovementTime = 0;

 // LocoNet really only has 126 speed steps i.e. 0..127 - 1 for em stop
 intSpeedSteps = 126;
 MAX_SPEED = 126;

 _throttleFrame = ltf;
 speedSlider = new MySlider(/*0, MAX_SPEED*/);
 speedSlider->setMinimum(0);
 speedSlider->setMaximum(MAX_SPEED);
 speedSlider->setValue(0);
  //speedSlider->setFocusable(false);
 trackSlider = false;
 trackSliderDefault = false;
 trackSliderMinInterval = 200;         // milliseconds
 trackSliderMinIntervalDefault = 200;  // milliseconds
 trackSliderMinIntervalMin = 50;       // milliseconds
 trackSliderMinIntervalMax = 1000;     // milliseconds
 lastTrackedSliderMovementTime = 0;

  // add mouse-wheel support
//  speedSlider.addMouseWheelListener(new MouseWheelListener() {
//      /*public*/ void mouseWheelMoved(MouseWheelEvent e) {
//        if(e.getWheelRotation() > 0)
//          decelerate1();
//        else
//          accelerate1();
//      }
//    });

    speedSpinner = new QSpinBox();

//    speedSpinnerModel = new SpinnerNumberModel(0, 0, MAX_SPEED, 1);
//    speedSpinner->setModel(speedSpinnerModel);
//    speedSpinner->setFocusable(false);
 speedSpinner->setMinimum(0);
 speedSpinner->setMaximum(MAX_SPEED);
 speedSpinner->setSingleStep(1);
 speedSpinner->setValue(0);

 speedStep128Button = new QRadioButton(tr("128 SS"));
 speedStep28Button = new QRadioButton(tr("28 SS"));
 speedStep27Button = new QRadioButton(tr("27 SS"));
 speedStep14Button= new QRadioButton(tr("14 SS"));
 log = new Logger("ControlPanel");
 log->setDebugEnabled(true);
 initGUI();
 //pack();
}
/*
 * Set the AddressPanel this throttle control is listenning for new throttle event
 */
/*public*/ void ControlPanel::setAddressPanel(AddressPanel* addressPanel) {
    this->addressPanel = addressPanel;
}

/*
 * "Destructor"
 */
/*public*/ ControlPanel::~ControlPanel() {
#if 0
    if (addressPanel != NULL) {
        addressPanel->removeAddressListener((AddressListener*)this);
    }
    if (_throttle != NULL) {
        //_throttle->removePropertyChangeListener(this);
     disconnect(_throttle, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        _throttle = NULL;
    }
#endif
}

//@Override
/*public*/ void ControlPanel::notifyAddressChosen(LocoAddress* /*l*/) {
}

//@Override
/*public*/ void ControlPanel::notifyAddressReleased(LocoAddress* /*la*/) {
    this->setEnabled(false);
    if (_throttle != NULL) {
        //throttle.removePropertyChangeListener(this);
     disconnect(_throttle, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }
    _throttle = NULL;
    if (prevShuntingFn != NULL) {
        setSwitchSliderFunction(prevShuntingFn);
        prevShuntingFn = "";
    }
}
/**
 *  Get notification that a throttle has been found as we requested.
 *
 * @param  t  An instantiation of the DccThrottle with the address requested.
 */
/*public*/ void ControlPanel::notifyAddressThrottleFound(DccThrottle* t)
{
 if (log->isDebugEnabled())
 {
     log->debug("control panel received new throttle");
 }
 this->_throttle = t;
 this->setEnabled(true);
 this->setIsForward(_throttle->getIsForward());
 this->setSpeedValues(_throttle->getSpeedIncrement(), _throttle->getSpeedSetting());

 // Set speed steps
 this->setSpeedStepsMode(_throttle->getSpeedStepMode()->mode);

 //this->throttle.addPropertyChangeListener(this);
 connect(this->_throttle, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 if (log->isDebugEnabled())
 {
     DccLocoAddress* Address = (DccLocoAddress*) _throttle->getLocoAddress();
     log->debug("new address is " + Address->toString());
 }

 if ((addressPanel != NULL) && (addressPanel->getRosterEntry() != NULL) && (addressPanel->getRosterEntry()->getShuntingFunction() != NULL))
 {
     prevShuntingFn = getSwitchSliderFunction();
     setSwitchSliderFunction(addressPanel->getRosterEntry()->getShuntingFunction());
 } else {
     setSwitchSliderFunction(switchSliderFunction); // reset slider
 }
}

//@Override
/*public*/ void ControlPanel::notifyConsistAddressChosen(int /*newAddress*/, bool /*isLong*/) {
}

//@Override
/*public*/ void ControlPanel::notifyConsistAddressReleased(int /*address*/, bool /*isLong*/) {
}

//@Override
/*public*/ void ControlPanel::notifyConsistAddressThrottleFound(DccThrottle* throttle) {
    if (log->isDebugEnabled()) {
        log->debug("control panel received consist throttle");
    }
    notifyAddressThrottleFound(throttle);
}

/*public*/ void ControlPanel::dispose()
{
 if (_throttle!=NULL)
 {
  //_throttle.removePropertyChangeListener(this);
  AbstractThrottle* at = (AbstractThrottle*)_throttle;
  disconnect(at, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  _throttle = NULL;
 }
 //super.dispose();
}

// update the state of this panel if any of the properties change
/*public*/ void ControlPanel::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName() == ("SpeedSetting"))
 {
  internalAdjust = true;
  float speed =  e->getNewValue().toFloat();
  // multiply by MAX_SPEED, and round to find the new
  //slider setting.
  int newSliderSetting = qRound(speed * maxSpeed);
  if (log->isDebugEnabled())
  {
   log->debug("propertyChange: new speed float: " + QString::number(speed) + " slider pos: " + QString::number(newSliderSetting));
  }
  speedSlider->setValue(newSliderSetting);
  if (speedSpinner != NULL)
  {
   speedSpinner->setValue((newSliderSetting));
  }
  if (speedSliderContinuous != NULL)
  {
   if (forwardButton->isChecked())
   {
    speedSliderContinuous->setValue(speedSlider->value());
   }
   else
   {
    speedSliderContinuous->setValue(-(speedSlider->value()));
   }
  }
  internalAdjust = false;
 }
 else if (e->getPropertyName()==("SpeedSteps")) {
   int steps = ( e->getNewValue()).toInt();
   setSpeedStepsMode(steps);
 }
 else if (e->getPropertyName()==("IsForward")) {
   bool Forward = ( e->getNewValue()).toBool();
   setIsForward(Forward);
 }
 else if (e->getPropertyName()==(switchSliderFunction))
 {
  if ( e->getNewValue().toBool())
  { // switch only if displaying sliders
   if (_displaySlider == SLIDERDISPLAY)
   {
    setSpeedController(SLIDERDISPLAYCONTINUOUS);
   }
  }
  else
  {
   if (_displaySlider == SLIDERDISPLAYCONTINUOUS)
   {
    setSpeedController(SLIDERDISPLAY);
   }
  }
 }
 if (log->isDebugEnabled())
 {
  log->debug("Property change event received " + e->getPropertyName() + " / " + e->getNewValue().toString());
 }
}

/**
 *  Enable/Disable all buttons and slider.
 *
 * @param  isEnabled  True if the buttons/slider should be enabled, false
 *      otherwise.
 */
/*public*/ void ControlPanel::setEnabled(bool isEnabled)
{
 //super.setEnabled(isEnabled);
 forwardButton->setEnabled(isEnabled);
 reverseButton->setEnabled(isEnabled);
 speedStep128Button->setEnabled(isEnabled);
 speedStep28Button->setEnabled(isEnabled);
 speedStep27Button->setEnabled(isEnabled);
 speedStep14Button->setEnabled(isEnabled);
 if (isEnabled) {
     configureAvailableSpeedStepModes();
 }
 stopButton->setEnabled(isEnabled);
 idleButton->setEnabled(isEnabled);
 speedControllerEnable = isEnabled;
 switch (_displaySlider)
 {
  case STEPDISPLAY:
  {
   if (speedSpinner != NULL) {
       speedSpinner->setEnabled(isEnabled);
   }
   if (speedSliderContinuous != NULL) {
       speedSliderContinuous->setEnabled(false);
   }
   speedSlider->setEnabled(false);
   break;
  }
  case SLIDERDISPLAYCONTINUOUS:
  {
   if (speedSliderContinuous != NULL) {
       speedSliderContinuous->setEnabled(isEnabled);
   }
   if (speedSpinner != NULL) {
       speedSpinner->setEnabled(false);
   }
   speedSlider->setEnabled(false);
   break;
  }
  default:
  {
   if (speedSpinner != NULL) {
       speedSpinner->setEnabled(false);
   }
   if (speedSliderContinuous != NULL) {
       speedSliderContinuous->setEnabled(false);
   }
   speedSlider->setEnabled(isEnabled);
  }
 }
}
/**
 * is this enabled?
 * @return true if enabled
 */
//@Override
/*public*/ bool ControlPanel::isEnabled() {
    return speedControllerEnable;
}

/**
 * Set the GUI to match that the loco is set to forward.
 *
 * @param isForward True if the loco is set to forward, false otherwise.
 */
/*private*/ void ControlPanel::setIsForward(bool isForward) {
    forwardButton->setChecked(isForward);
    reverseButton->setChecked(!isForward);
    if (speedSliderContinuous != NULL) {
        internalAdjust = true;
        if (isForward) {
            speedSliderContinuous->setValue(qAbs(speedSliderContinuous->value()));
        } else {
            speedSliderContinuous->setValue(-qAbs(speedSliderContinuous->value()));
        }
        internalAdjust = false;
    }
}

/**
 * Set the GUI to match the speed steps of the current address. Initialises
 * the speed slider and spinner - including setting their maximums based on
 * the speed step setting and the max speed for the particular loco
 *
 * @param speedStepMode Desired speed step mode. One of:
 *                      DccThrottle.SpeedStepMode128,
 *                      DccThrottle.SpeedStepMode28,
 *                      DccThrottle.SpeedStepMode27,
 *                      DccThrottle.SpeedStepMode14 step mode
 */
/*private*/ void ControlPanel::setSpeedStepsMode(int speedStepMode)
{
 internalAdjust = true;
 int maxSpeedPCT = 100;
 if (addressPanel->getRosterEntry() != NULL) {
     maxSpeedPCT = addressPanel->getRosterEntry()->getMaxSpeedPCT();
 }

 // Save the old speed as a float
 float oldSpeed = (speedSlider->value() / (maxSpeed * 1.0f));

 if (speedStepMode == DccThrottle::SpeedStepMode14) {
     speedStep14Button->setChecked(true);
     speedStep27Button->setChecked(false);
     speedStep28Button->setChecked(false);
     speedStep128Button->setChecked(false);
     intSpeedSteps = 14;
 } else if (speedStepMode == DccThrottle::SpeedStepMode27) {
     speedStep14Button->setChecked(false);
     speedStep27Button->setChecked(true);
     speedStep28Button->setChecked(false);
     speedStep128Button->setChecked(false);
     intSpeedSteps = 27;
 } else if (speedStepMode == DccThrottle::SpeedStepMode28) {
     speedStep14Button->setChecked(false);
     speedStep27Button->setChecked(false);
     speedStep28Button->setChecked(true);
     speedStep128Button->setChecked(false);
     intSpeedSteps = 28;
 } else {
     speedStep14Button->setChecked(false);
     speedStep27Button->setChecked(false);
     speedStep28Button->setChecked(false);
     speedStep128Button->setChecked(true);
     intSpeedSteps = 126;
 }
 /* Set maximum speed based on the max speed stored in the roster as a percentage of the maximum */
 maxSpeed = (int) ((float) intSpeedSteps * ((float) maxSpeedPCT) / 100);

 // rescale the speed slider to match the new speed step mode
 speedSlider->setMaximum(maxSpeed);
 speedSlider->setValue((int) (oldSpeed * maxSpeed));
 speedSlider->setMajorTickSpacing(maxSpeed / 2); //see https://stackoverflow.com/questions/27661877/qt-slider-widget-with-tick-text-labels
//    QMap<int, QLabel*>* labelTable = new QMap<int, QLabel*>();
//    labelTable->insert((maxSpeed / 2), new QLabel("50%"));
//    labelTable->insert((maxSpeed), new QLabel("100%"));
//    labelTable->insert((0), new QLabel(tr("Stop")));
 QVector<QLabel*> labelTable = QVector<QLabel*>();
 labelTable.append(new QLabel("100%"));
 labelTable.append(new QLabel("50%"));
 labelTable.append(new QLabel(tr("Stop")));
 speedSlider->setLabelTable(labelTable);
//    speedSlider.setPaintTicks(true);
//    speedSlider.setPaintLabels(true);

 if (speedSliderContinuous != NULL)
 {
  speedSliderContinuous->setMaximum(maxSpeed);
  speedSliderContinuous->setMinimum(-maxSpeed);
  if (forwardButton->isChecked()) {
      speedSliderContinuous->setValue((int) (oldSpeed * maxSpeed));
  } else {
      speedSliderContinuous->setValue(-(int) (oldSpeed * maxSpeed));
  }
  speedSliderContinuous->setValue((int) (oldSpeed * maxSpeed));
  speedSliderContinuous->setMajorTickSpacing(maxSpeed / 2);
//        labelTable = new QMap<int, QLabel*>();
//        labelTable->insert((maxSpeed / 2), new QLabel("50%"));
//        labelTable->insert((maxSpeed), new QLabel("100%"));
//        labelTable->insert((0), new QLabel(tr("Stop")));
//        labelTable->insert((-maxSpeed / 2), new QLabel("-50%"));
//        labelTable->insert((-maxSpeed), new QLabel("-100%"));
  labelTable = QVector<QLabel*>();
  labelTable.append(new QLabel("100%"));
  labelTable.append(new QLabel("50%"));
  labelTable.append(new QLabel(tr("Stop")));
  labelTable.append(new QLabel("-50%"));
  labelTable.append(new QLabel("-100%"));
  speedSliderContinuous->setLabelTable(labelTable);
//        speedSliderContinuous.setPaintTicks(true);
//        speedSliderContinuous.setPaintLabels(true);
 }

//    speedSpinnerModel.setMaximum(Integer.valueOf(maxSpeed));
 speedSpinner->setMaximum(maxSpeed);
//    speedSpinnerModel.setMinimum(Integer.valueOf(0));
 speedSpinner->setMinimum(0);
//    // rescale the speed value to match the new speed step mode
//    speedSpinnerModel.setValue(Integer.valueOf(speedSlider.getValue()));
 speedSpinner->setValue(speedSlider->value());
 internalAdjust = false;
}
/**
 * Is this Speed Control selection method possible?
 *
 * @param displaySlider integer value. possible values: SLIDERDISPLAY = use
 *                      speed slider display STEPDISPLAY = use speed step
 *                      display
 */
/*public*/ bool ControlPanel::isSpeedControllerAvailable(int displaySlider)
{
 switch (displaySlider)
 {
  case STEPDISPLAY:
      return (speedSpinner != NULL);
  case SLIDERDISPLAY:
      return (speedSlider != NULL);
  case SLIDERDISPLAYCONTINUOUS:
      return (speedSliderContinuous != NULL);
  default:
      return false;
 }
}

/**
 * Set the Speed Control selection method
 *
 * TODO: move to private
 *
 * @deprecated You should not directly manipulate the UI. Use a throttle
 * object instead.
 *
 * @param displaySlider integer value. possible values: SLIDERDISPLAY = use
 *                      speed slider display STEPDISPLAY = use speed step
 *                      display
 */
//@Deprecated
/*public*/ void ControlPanel::setSpeedController(int displaySlider)
{
 _displaySlider = displaySlider;
 switch (displaySlider)
 {
  case STEPDISPLAY:
   if (speedSpinner != NULL)
   {
    sliderPanel->setVisible(false);
    speedSlider->setEnabled(false);
    speedSliderContinuousPanel->setVisible(false);
    if (speedSliderContinuous != NULL)
    {
     speedSliderContinuous->setEnabled(false);
    }
    spinnerPanel->setVisible(true);
    speedSpinner->setEnabled(speedControllerEnable);
    return;
   }
   break;
  case SLIDERDISPLAYCONTINUOUS:
   if (speedSliderContinuous != NULL)
   {
    sliderPanel->setVisible(false);
    speedSlider->setEnabled(false);
    speedSliderContinuousPanel->setVisible(true);
    speedSliderContinuous->setEnabled(speedControllerEnable);
    spinnerPanel->setVisible(false);
    if (speedSpinner != NULL)
    {
     speedSpinner->setEnabled(false);
    }
    return;
   }
   break;
}
 sliderPanel->setVisible(true);
 speedSlider->setEnabled(speedControllerEnable);
 spinnerPanel->setVisible(false);
 if (speedSpinner != NULL) {
     speedSpinner->setEnabled(false);
 }
 speedSliderContinuousPanel->setVisible(false);
 if (speedSliderContinuous != NULL) {
     speedSliderContinuous->setEnabled(false);
 }

}
/**
 * Get the value indicating what speed input we're displaying
 *
 */
/*public*/ int ControlPanel::getDisplaySlider() {
    return _displaySlider;
}

/**
 * Set real-time tracking of speed slider, or not
 *
 * @param track boolean value, true to track, false to set speed on unclick
 */
/*public*/ void ControlPanel::setTrackSlider(bool track) {
    trackSlider = track;
}

/**
 * Get status of real-time speed slider tracking
 */
/*public*/ bool ControlPanel::getTrackSlider() {
    return trackSlider;
}
/**
 *  Set the GUI to match that the loco speed.
 *
 * @param  speedIncrement  : TODO
 * @param  speed           The speed value of the loco.
 */
/*public*/ void ControlPanel::setSpeedValues(int speedIncrement, int speed)
{
 //this->speedIncrement = speedIncrement;
 speedSlider->setValue(speed * speedIncrement);
 // Spinner Speed should be the raw integer speed value
 if(speedSpinner!=NULL)
  //speedSpinnerModel->setValue(Integer.valueOf(speed));
  speedSpinner->setValue(speed);
}

/**
 *  Create, initialize and place GUI components.
 */
/*private*/ void ControlPanel::initGUI()
{
 mainPanel = new QWidget();
 //this.setContentPane(mainPanel);
 this->setWidget(mainPanel);
 QVBoxLayout* mainPanelLayout;
 mainPanel->setLayout(mainPanelLayout = new QVBoxLayout());
 //((JFrame*)this->window())->setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);

 speedControlPanel = new QFrame();
 //speedControlPanel->setMinimumHeight(200);
 //speedControlPanel->setFrameShape(QFrame::Box);
// QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Expanding);
// speedControlPanel->setSizePolicy(sp);
 QHBoxLayout* speedControlPanelLayout;
 speedControlPanel->setLayout(speedControlPanelLayout = new QHBoxLayout());//speedControlPanel, BoxLayout.X_AXIS));
 //speedControlPanel.setOpaque(false);
 mainPanelLayout->addWidget(speedControlPanel, 0, Qt::AlignCenter); //BorderLayout.CENTER);
 sliderPanel = new QFrame();
 //GridBagLayout* sliderPanelLayout;
 QHBoxLayout* sliderPanelLayout;
 //sliderPanel->setLayout(sliderPanelLayout = new GridBagLayout());
 sliderPanel->setLayout(sliderPanelLayout = new QHBoxLayout());
 //sliderPanel.setOpaque(false);
 //sliderPanel->setFrameShape(QFrame::Box);

 speedSlider = new MySlider(); //0, intSpeedSteps);
 speedSlider->setMinimum(0);
 speedSlider->setMaximum(intSpeedSteps);
 //speedSlider.setOpaque(false);
 speedSlider->setValue(0);
 //speedSlider.setFocusable(false);

 // add mouse-wheel support
// speedSlider.addMouseWheelListener(new MouseWheelListener() {
//     @Override
//     public void mouseWheelMoved(MouseWheelEvent e) {
//         if (e.getWheelRotation() > 0) {
//             for (int i = 0; i < e.getScrollAmount(); i++) {
//                 decelerate1();
//             }
//         } else {
//             for (int i = 0; i < e.getScrollAmount(); i++) {
//                 accelerate1();
//             }
//         }
//     }
// });

 speedSliderContinuous = new MySlider();//-intSpeedSteps, intSpeedSteps);
 speedSliderContinuous->setMinimum(-intSpeedSteps);
 speedSliderContinuous->setMaximum(intSpeedSteps);
 speedSliderContinuous->setValue(0);
// speedSliderContinuous.setOpaque(false);
// speedSliderContinuous.setFocusable(false);

 // add mouse-wheel support
// speedSliderContinuous.addMouseWheelListener(new MouseWheelListener() {
//     @Override
//     public void mouseWheelMoved(MouseWheelEvent e) {
//         if (e.getWheelRotation() > 0) {
//             for (int i = 0; i < e.getScrollAmount(); i++) {
//                 decelerate1();
//             }
//         } else {
//             for (int i = 0; i < e.getScrollAmount(); i++) {
//                 accelerate1();
//             }
//         }
//     }
// });

 speedSpinner = new QSpinBox();

// speedSpinnerModel = new SpinnerNumberModel(0, 0, intSpeedSteps, 1);
// speedSpinner.setModel(speedSpinnerModel);
 speedSpinner->setRange(0,intSpeedSteps);
 speedSpinner->setValue(0);
 speedSpinner->setSingleStep(1);
// speedSpinner.setFocusable(false);

 speedStep128Button = new QRadioButton(tr("128 SS"));
 speedStep28Button = new QRadioButton(tr("28 SS"));
 speedStep27Button = new QRadioButton(tr("27 SS"));
 speedStep14Button = new QRadioButton(tr("14 SS"));

 forwardButton = new QRadioButton();
 if (((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingExThrottle()
         && ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingFunctionIcon()) {
//     forwardButton.setBorderPainted(false);
//     forwardButton.setContentAreaFilled(false);
     forwardButton->setText("");
     forwardButton->setIcon( QIcon(FileUtil::findURL("resources/icons/throttles/up-red.png").path()));
//     forwardButton.setSelectedIcon(new ImageIcon(FileUtil.findURL("resources/icons/throttles/up-green.png")));
     forwardButton->resize(QSize(BUTTON_SIZE, BUTTON_SIZE));
     forwardButton->setToolTip(tr("Forward"));
 } else {
     forwardButton->setText(tr("Forward"));
 }

 reverseButton = new QRadioButton();
 if (((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingExThrottle()
         && ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingFunctionIcon()) {
//     reverseButton.setBorderPainted(false);
//     reverseButton.setContentAreaFilled(false);
     reverseButton->setText("");
     reverseButton->setIcon(QIcon(FileUtil::findURL("resources/icons/throttles/down-red.png").path()));
//     reverseButton.setSelectedIcon(new ImageIcon(FileUtil.findURL("resources/icons/throttles/down-green.png")));
     reverseButton->resize(QSize(BUTTON_SIZE, BUTTON_SIZE));
     reverseButton->setToolTip(tr("Reverse"));
 } else {
     reverseButton->setText(tr("Reverse"));
 }

 setContextMenuPolicy(Qt::CustomContextMenu);
 propertiesPopup = new QMenu();

 GridBagConstraints constraints = GridBagConstraints();
 constraints.anchor = GridBagConstraints::CENTER;
 constraints.fill = GridBagConstraints::BOTH;
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

 //sliderPanelLayout->addWidget(speedSlider, constraints);
 sliderPanelLayout->addWidget(speedSlider, 0, Qt::AlignCenter);
 //this.getContentPane().add(sliderPanel,BorderLayout.CENTER);
 speedControlPanelLayout->addWidget(sliderPanel,0,Qt::AlignCenter);
 speedSlider->setOrientation(Qt::Vertical);
 speedSlider->setMajorTickSpacing(maxSpeed / 2); //see https://stackoverflow.com/questions/27661877/qt-slider-widget-with-tick-text-labels
// QMap<int, QLabel*>* labelTable = new QMap<int, QLabel*>();
 QVector<QLabel*> labelTable = QVector<QLabel*>();
// labelTable->insert((maxSpeed / 2), new QLabel("50%"));
// labelTable->insert((maxSpeed), new QLabel("100%"));
// labelTable->insert((0), new QLabel(tr("Stop")));
 labelTable.append(new QLabel("100%"));
 labelTable.append(new QLabel("50%"));
 labelTable.append(new QLabel(tr("Stop")));
 speedSlider->setLabelTable(labelTable);

// speedSlider.setPaintTicks(true);
// speedSlider.setPaintLabels(true);
 // remove old actions
 connect(speedSlider, SIGNAL(valueChanged(int)), this, SLOT(OnSpeedSliderChanged(int)));
 connect(speedSliderContinuous, SIGNAL(valueChanged(int)), this, SLOT(speedSliderContinuousChanged(int)));


 speedSliderContinuousPanel = new QWidget();
 GridBagLayout* speedSliderContinuousPanelLayout;
 speedSliderContinuousPanel->setLayout(speedSliderContinuousPanelLayout = new GridBagLayout());

 constraints = GridBagConstraints();
 constraints.anchor = GridBagConstraints::CENTER;
 constraints.fill = GridBagConstraints::BOTH;
 constraints.gridheight = 1;
 constraints.gridwidth = 1;
 constraints.ipadx = 0;
 constraints.ipady = 0;
 insets = new Insets(2, 2, 2, 2);
 constraints.insets = insets;
 constraints.weightx = 1;
 constraints.weighty = 1;
 constraints.gridx = 0;
 constraints.gridy = 0;

 speedSliderContinuousPanelLayout->addWidget(speedSliderContinuous, constraints);
 //this.getContentPane().add(sliderPanel,BorderLayout.CENTER);
 speedControlPanelLayout->addWidget(speedSliderContinuousPanel, 0, Qt::AlignCenter);
 speedSliderContinuous->setOrientation(Qt::Vertical);
 speedSliderContinuous->setMajorTickSpacing(maxSpeed / 2);
// labelTable = new QMap<int, QLabel*>();
// labelTable->insert((maxSpeed / 2), new QLabel("50%"));
// labelTable->insert((maxSpeed), new QLabel("100%"));
// labelTable->insert((0), new QLabel(tr("Stop")));
// labelTable->insert((-maxSpeed / 2), new QLabel("-50%"));
// labelTable->insert((-maxSpeed), new QLabel("-100%"));
 labelTable = QVector<QLabel*>();
 labelTable.append(new QLabel("100%"));
 labelTable.append(new QLabel("50%"));
 labelTable.append(new QLabel(tr("Stop")));
 labelTable.append(new QLabel("-50%"));
 labelTable.append(new QLabel("-100%"));
 speedSliderContinuous->setLabelTable(labelTable);
// speedSliderContinuous.setPaintTicks(true);
// speedSliderContinuous.setPaintLabels(true);
 // remove old actions
// speedSliderContinuous.addChangeListener(
//         new ChangeListener() {
//             @Override
//             public void stateChanged(ChangeEvent e) {
//                 if (!internalAdjust) {
//                     boolean doIt = false;
//                     if (!speedSliderContinuous.getValueIsAdjusting()) {
//                         doIt = true;
//                         lastTrackedSliderMovementTime = System.currentTimeMillis() - trackSliderMinInterval;
//                     } else if (trackSlider
//                     && System.currentTimeMillis() - lastTrackedSliderMovementTime >= trackSliderMinInterval) {
//                         doIt = true;
//                         lastTrackedSliderMovementTime = System.currentTimeMillis();
//                     }
//                     if (doIt) {
//                         float newSpeed = (java.lang.Math.abs(speedSliderContinuous.getValue()) / (intSpeedSteps * 1.0f));
//                         boolean newDir = (speedSliderContinuous.getValue() >= 0);
//                         if (log.isDebugEnabled()) {
//                             log.debug("stateChanged: slider pos: " + speedSliderContinuous.getValue() + " speed: " + newSpeed + " dir: " + newDir);
//                         }
//                         if (speedSliderContinuousPanel.isVisible() && throttle != null) {
//                             throttle.setSpeedSetting(newSpeed);
//                             if ((newSpeed > 0) && (newDir != forwardButton.isSelected())) {
//                                 throttle.setIsForward(newDir);
//                             }
//                         }
//                         if (speedSpinner != null) {
//                             speedSpinnerModel.setValue(Integer.valueOf(java.lang.Math.abs(speedSliderContinuous.getValue())));
//                         }
//                         if (speedSlider != null) {
//                             speedSlider.setValue(Integer.valueOf(java.lang.Math.abs(speedSliderContinuous.getValue())));
//                         }
//                     }
//                 }
//             }
//         });

 spinnerPanel = new QWidget();
 GridBagLayout* spinnerPanelLayout;
 spinnerPanel->setLayout(spinnerPanelLayout = new GridBagLayout());

 spinnerPanelLayout->addWidget(speedSpinner, constraints);

 speedControlPanelLayout->addWidget(spinnerPanel, 0, Qt::AlignCenter);

 // remove old actions
 connect(speedSpinner, SIGNAL(valueChanged(int)), this, SLOT(OnSpinnerChanged(int)));

 QButtonGroup* speedStepButtons = new QButtonGroup();
 speedStepButtons->addButton(speedStep128Button);
 speedStepButtons->addButton(speedStep28Button);
 speedStepButtons->addButton(speedStep27Button);
 speedStepButtons->addButton(speedStep14Button);
 constraints.fill = GridBagConstraints::NONE;
 constraints.gridy = 1;
 spinnerPanelLayout->addWidget(speedStep128Button, constraints);
 constraints.gridy = 2;
 spinnerPanelLayout->addWidget(speedStep28Button, constraints);
 constraints.gridy = 3;
 spinnerPanelLayout->addWidget(speedStep27Button, constraints);
 constraints.gridy = 4;
 spinnerPanelLayout->addWidget(speedStep14Button, constraints);

// speedStep14Button.addActionListener(
//         new ActionListener() {
//             @Override
//             public void actionPerformed(ActionEvent e) {
//                 setSpeedStepsMode(DccThrottle.SpeedStepMode14);
//                 throttle.setSpeedStepMode(DccThrottle.SpeedStepMode14);
//             }
//         });
 connect(speedStep14Button, SIGNAL(clicked()), this, SLOT(OnSpeedStep14()));
// speedStep27Button.addActionListener(
//         new ActionListener() {
//             @Override
//             public void actionPerformed(ActionEvent e) {
//                 setSpeedStepsMode(DccThrottle.SpeedStepMode27);
//                 throttle.setSpeedStepMode(DccThrottle.SpeedStepMode27);
//             }
//         });
 connect(speedStep27Button, SIGNAL(clicked()), this, SLOT(OnSpeedStep27()));


// speedStep28Button.addActionListener(
//         new ActionListener() {
//             @Override
//             public void actionPerformed(ActionEvent e) {
//                 setSpeedStepsMode(DccThrottle.SpeedStepMode28);
//                 throttle.setSpeedStepMode(DccThrottle.SpeedStepMode28);
//             }
//         });
 connect(speedStep28Button, SIGNAL(clicked()), this, SLOT(OnSpeedStep28()));


// speedStep128Button.addActionListener(
//         new ActionListener() {
//             @Override
//             public void actionPerformed(ActionEvent e) {
//                 setSpeedStepsMode(DccThrottle.SpeedStepMode128);
//                 throttle.setSpeedStepMode(DccThrottle.SpeedStepMode128);
//             }
//         });
 connect(speedStep128Button, SIGNAL(clicked()), this, SLOT(OnSpeedStep128()));


 buttonPanel = new QWidget();
 GridBagLayout* buttonPanelLayout;
 buttonPanel->setLayout(buttonPanelLayout = new GridBagLayout());
// QSizePolicy bpsp = QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
// buttonPanel->setSizePolicy(bpsp);
 mainPanelLayout->addWidget(buttonPanel, 0, Qt::AlignBottom); //BorderLayout.SOUTH);

 QButtonGroup* directionButtons = new QButtonGroup();
 directionButtons->addButton(forwardButton);
 directionButtons->addButton(reverseButton);
// forwardButton.setFocusable(false);
// reverseButton.setFocusable(false);
 constraints.fill = GridBagConstraints::NONE;

 constraints.gridy = 1;
 if (((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingExThrottle()
         && ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingFunctionIcon()) {
     constraints.gridx = 3;
 }
 buttonPanelLayout->addWidget(forwardButton, constraints);

 if (((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingExThrottle()
         && ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingFunctionIcon()) {
     constraints.gridx = 1;
 } else {
     constraints.gridy = 2;
 }
 buttonPanelLayout->addWidget(reverseButton, constraints);

 if (((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingExThrottle()
         && ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingFunctionIcon()) {
     constraints.gridx = 2;
 }
// forwardButton.addActionListener(
//         new ActionListener() {
//             @Override
//             public void actionPerformed(ActionEvent e) {
//                 throttle.setIsForward(true);
//                 if (speedSliderContinuous != null) {
//                     speedSliderContinuous.setValue(java.lang.Math.abs(speedSliderContinuous.getValue()));
//                 }
//             }
//         });
 connect(forwardButton, SIGNAL(clicked(bool)), this, SLOT(forwardButtonClicked()));

// reverseButton.addActionListener(
//         new ActionListener() {
//             @Override
//             public void actionPerformed(ActionEvent e) {
//                 throttle.setIsForward(false);
//                 if (speedSliderContinuous != null) {
//                     speedSliderContinuous.setValue(-java.lang.Math.abs(speedSliderContinuous.getValue()));
//                 }
//             }
//         });

 stopButton = new QPushButton();
 if (((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingExThrottle()
         && ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingFunctionIcon()) {
//     stopButton.setBorderPainted(false);
//     stopButton.setContentAreaFilled(false);
     stopButton->setText("");
//     stopButton.setIcon(new ImageIcon(FileUtil.findURL("resources/icons/throttles/estop.png")));
//     stopButton.setPressedIcon(new ImageIcon(FileUtil.findURL("resources/icons/throttles/estop24.png")));
     stopButton->resize(QSize(BUTTON_SIZE, BUTTON_SIZE));
     stopButton->setToolTip(tr("EStop"));
 } else {
     stopButton->setText(tr("EStop"));
 }
 constraints.gridy = 4;
 constraints.fill = GridBagConstraints::HORIZONTAL;
 buttonPanelLayout->addWidget(stopButton, constraints);
// stopButton.addActionListener(
//         new ActionListener() {
//             @Override
//             public void actionPerformed(ActionEvent e) {
//                 stop();
//             }
//         });
 connect(stopButton, SIGNAL(clicked(bool)), this, SLOT(stop()));

// stopButton.addMouseListener(
//         new MouseListener() {
//             @Override
//             public void mousePressed(MouseEvent e) {
//                 stop();
//             }

//             @Override
//             public void mouseExited(MouseEvent e) {
//             }

//             @Override
//             public void mouseEntered(MouseEvent e) {
//             }

//             @Override
//             public void mouseReleased(MouseEvent e) {
//             }

//             @Override
//             public void mouseClicked(MouseEvent e) {
//             }
//         });
 idleButton = new QPushButton();
 if (((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingExThrottle()
         && ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingFunctionIcon()) {
//     idleButton.setBorderPainted(false);
//     idleButton.setContentAreaFilled(false);
     idleButton->setText("");
//     idleButton.setIcon(new ImageIcon(FileUtil.findURL("resources/icons/throttles/stop.png")));
//     idleButton.setPressedIcon(new ImageIcon(FileUtil.findURL("resources/icons/throttles/stop24.png")));
     idleButton->resize(QSize(BUTTON_SIZE, BUTTON_SIZE));
     idleButton->setToolTip(tr("Idle"));
 } else {
     idleButton->setText(tr("Idle"));
 }

 if (((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingExThrottle()
         && ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isUsingFunctionIcon()) {
     constraints.gridy = 1;
 } else {
     constraints.gridy = 3;
 }
 buttonPanelLayout->addWidget(idleButton, constraints);
 buttonPanel->setMaximumSize(buttonPanel->sizeHint());
// idleButton.addActionListener(
//         new ActionListener() {
//             @Override
//             public void actionPerformed(ActionEvent e) {
//                 speedSlider.setValue(0);
//                 if (speedSpinner != null) {
//                     speedSpinner.setValue(Integer.valueOf(0));
//                 }
//                 if (speedSliderContinuous != null) {
//                     speedSliderContinuous.setValue(Integer.valueOf(0));
//                 }
//                 throttle.setSpeedSetting(0);
//             }
//         });
 connect(idleButton, SIGNAL(clicked(bool)), this, SLOT(idleButtonClicked()));

#if 0
 addComponentListener(
         new ComponentAdapter() {
             @Override
             public void componentResized(ComponentEvent e) {
                 changeOrientation();
             }
         });
#endif

 QAction* propertiesItem = new QAction(tr("Properties"), this);

 //propertiesItem.addActionListener(this);
 connect(propertiesItem, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 propertiesPopup->addAction(propertiesItem);
 QAction* edit = new QAction(tr("Edit properties ..."), this);
 propertiesPopup->addAction(edit);
 connect(edit, SIGNAL(triggered(bool)), this, SLOT(on_editProperties()));
 connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_menu_requested()));

#if 0
 // Add a mouse listener all components to trigger the popup menu.
 MouseInputAdapter popupListener = new PopupListener(propertiesPopup, this);
 MouseInputAdapterInstaller.installMouseInputAdapterOnAllComponents(popupListener, this);

 // Install the Key bindings on all Components
 KeyListenerInstaller.installKeyListenerOnAllComponents(new ControlPadKeyListener(), this);
#endif
 // set by default which speed selection method is on top
 setSpeedController(_displaySlider);
}

void ControlPanel::forwardButtonClicked()
{
 _throttle->setIsForward(true);
 if (speedSliderContinuous != NULL) {
     speedSliderContinuous->setValue(qAbs(speedSliderContinuous->value()));
 }
}

void ControlPanel::reverseButtonClicked()
{
 _throttle->setIsForward(false);
 if (speedSliderContinuous != NULL)
 {
     speedSliderContinuous->setValue(-qAbs(speedSliderContinuous->value()));
 }
}

void ControlPanel::idleButtonClicked()
{
 speedSlider->setValue(0);
 if (speedSpinner != NULL)
 {
  speedSpinner->setValue((0));
 }
 if (speedSliderContinuous != NULL)
 {
  speedSliderContinuous->setValue((0));
 }
 _throttle->setSpeedSetting(0);

}

/**
 * Perform an emergency stop.
 *
 */
/*public*/ void ControlPanel::stop()
{
 if (this->_throttle == NULL) {
     return;
 }
 internalAdjust = true;
 _throttle->setSpeedSetting(-1);
 speedSlider->setValue(0);
 if (speedSpinner != NULL)
 {
  //speedSpinnerModel.setValue(Integer.valueOf(0));
  speedSpinner->setValue(0);
 }
 if (speedSliderContinuous != NULL)
 {
  speedSliderContinuous->setValue((0));
 }
 internalAdjust = false;
}

/**
 * The user has resized the Frame. Possibly change from Horizontal to
 * Vertical layout.
 */
/*private*/ void ControlPanel::changeOrientation() {
    if (mainPanel->width() > mainPanel->height()) {
        speedSlider->setOrientation(/*JSlider.HORIZONTAL*/Qt::Horizontal);
        if (speedSliderContinuous != nullptr) {
            speedSliderContinuous->setOrientation(/*JSlider.HORIZONTAL*/Qt::Horizontal);
        }
        mainPanel->layout()->removeWidget(buttonPanel);
        ((QHBoxLayout*)mainPanel->layout())->addWidget(buttonPanel, 0, Qt::AlignRight);//BorderLayout.EAST);
    } else {
        speedSlider->setOrientation(/*JSlider.VERTICAL*/Qt::Vertical);
        if (speedSliderContinuous != nullptr) {
            speedSliderContinuous->setOrientation(/*JSlider.VERTICAL*/Qt::Vertical);
        }
        mainPanel->layout()->removeWidget(buttonPanel);
        ((QVBoxLayout*)mainPanel->layout())->addWidget(buttonPanel, 0, Qt::AlignBottom); //BorderLayout.SOUTH);
    }
}

/*public*/ void ControlPanel::accelerate1()
{
 if (speedSlider->isEnabled())
 {
  if (speedSlider->value() != speedSlider->maximum())
  {
   speedSlider->setValue(speedSlider->value() + 1);
  }
 }
 else if(speedSpinner!=NULL && speedSpinner->isEnabled())
 {
  if ((speedSpinner->value()) < speedSpinner->maximum() &&
     speedSpinner->value() >= speedSpinner->minimum() )
  {
   speedSpinner->setValue(speedSpinner->value() + 1);
  }
 }
}

void ControlPanel::OnSpeedSliderChanged(int )
{
 if (!internalAdjust)
 {
  bool doIt = false;
  if (!speedSlider->getValueIsAdjusting())
  {
   doIt = true;
   lastTrackedSliderMovementTime = QDateTime::currentMSecsSinceEpoch() - trackSliderMinInterval;
  }
  else if (trackSlider
  && QDateTime::currentMSecsSinceEpoch() - lastTrackedSliderMovementTime >= trackSliderMinInterval)
  {
   doIt = true;
   lastTrackedSliderMovementTime = QDateTime::currentMSecsSinceEpoch();
  }
  if (doIt)
  {
   float newSpeed = (speedSlider->value() / (intSpeedSteps * 1.0f));
   if (log->isDebugEnabled())
   {
    log->debug("stateChanged: slider pos: " + QString::number(speedSlider->value()) + " speed: " + QString::number(newSpeed));
   }
   if (sliderPanel->isVisible() && _throttle != NULL)
   {
    _throttle->setSpeedSetting(newSpeed);
   }
   if (speedSpinner != NULL)
   {
       //speedSpinnerModel.setValue(Integer.valueOf(speedSlider.getValue()));
    speedSpinner->value();
   }
   if (speedSliderContinuous != NULL)
   {
    if (forwardButton->isChecked())
    {
     speedSliderContinuous->setValue(( speedSlider->value()));
    }
    else
    {
     speedSliderContinuous->setValue(-( speedSlider->value()));
    }
   }
  }
 }
}

void ControlPanel::speedSliderContinuousChanged(int)
{
 if (!internalAdjust)
 {
  bool doIt = false;
  if (!speedSliderContinuous->getValueIsAdjusting()) {
      doIt = true;
      lastTrackedSliderMovementTime = QDateTime::currentMSecsSinceEpoch() - trackSliderMinInterval;
  }
  else
  if (trackSlider
  && QDateTime::currentMSecsSinceEpoch()- lastTrackedSliderMovementTime >= trackSliderMinInterval) {
      doIt = true;
      lastTrackedSliderMovementTime = QDateTime::currentMSecsSinceEpoch();
  }
  if (doIt) {
      float newSpeed = (qAbs(speedSliderContinuous->value()) / (intSpeedSteps * 1.0f));
      bool newDir = (speedSliderContinuous->value() >= 0);
      if (log->isDebugEnabled()) {
          log->debug("stateChanged: slider pos: " + QString::number(speedSliderContinuous->value()) + " speed: " + QString::number(newSpeed) + " dir: " + newDir);
      }
      if (speedSliderContinuousPanel->isVisible() && _throttle != NULL) {
          _throttle->setSpeedSetting(newSpeed);
          if ((newSpeed > 0) && (newDir != forwardButton->isChecked())) {
              _throttle->setIsForward(newDir);
          }
      }
      if (speedSpinner != NULL) {
          //speedSpinnerModel.setValue(Integer.valueOf(java.lang.Math.abs(speedSliderContinuous.getValue())));
       speedSpinner->setValue(qAbs(speedSliderContinuous->value()));
      }
      if (speedSlider != NULL) {
          speedSlider->setValue(qAbs(speedSliderContinuous->value()));
      }
  }
 }
}


void ControlPanel::OnSpinnerChanged(int)
{
 if ( !internalAdjust)
 {
  float newSpeed =(float)speedSpinner->value() / ( MAX_SPEED * 1.0f );
  if (log->isDebugEnabled()) {log->debug( "stateChanged: spinner pos: " + QString::number(speedSpinner->value()) + " speed: " + QString::number(newSpeed) );
  }
  _throttle->setSpeedSetting( newSpeed );
  //_throttleFrame->setSpeedSetting( newSpeed );
  speedSlider->setValue(speedSpinner->value());
 }
 else
 {
  internalAdjust=false;
 }
}
void ControlPanel::OnSpeedStep28()
{
    setSpeedStepsMode(DccThrottle::SpeedStepMode28);
    _throttle->setSpeedStepMode(SpeedStepMode::NMRA_DCC_28);
}
void ControlPanel::OnSpeedStep14()
{
 setSpeedStepsMode(DccThrottle::SpeedStepMode14);
 _throttle->setSpeedStepMode(SpeedStepMode::NMRA_DCC_14);
}
void ControlPanel::OnSpeedStep27()
{
 setSpeedStepsMode(DccThrottle::SpeedStepMode27);
 _throttle->setSpeedStepMode(SpeedStepMode::NMRA_DCC_27);
}
void ControlPanel::OnSpeedStep128()
{
 setSpeedStepsMode(DccThrottle::SpeedStepMode128);
 _throttle->setSpeedStepMode(SpeedStepMode::NMRA_DCC_128);
}
/*public*/ void ControlPanel::accelerate10()
{
 if (speedSlider->isEnabled())
 {
  if (speedSlider->value() != speedSlider->maximum())
  {
   speedSlider->setValue(speedSlider->value() + 10);
  }
 }
 else if (speedSpinner!=NULL && speedSpinner->isEnabled())
 {
  if (speedSpinner->value() < speedSpinner->maximum() &&
                speedSpinner->value() >= speedSpinner->minimum() )
  {
   int speedvalue= speedSpinner->value() + 10;
   if(speedvalue<speedSpinner->maximum())
    speedSpinner->setValue(speedvalue);
   else
    speedSpinner->setValue(speedSpinner->maximum());
  }
 }
}

/*public*/ void ControlPanel::decelerate1()
{
 if (speedSlider->isEnabled())
 {
  if (speedSlider->value() != speedSlider->minimum())
  {
   speedSlider->setValue(speedSlider->value() - 1);
  }
 }
 else if (speedSpinner!=NULL && speedSpinner->isEnabled())
 {
  if (speedSpinner->value() <= speedSpinner->maximum() &&
            speedSpinner->value() > speedSpinner->minimum() )
  {
   speedSpinner->setValue(speedSpinner->value() - 1);
  }
 }
}

/*public*/ void ControlPanel::decelerate10()
{
if (speedSlider->isEnabled())
 {
  if (speedSlider->value() != speedSlider->minimum())
  {
   speedSlider->setValue(speedSlider->value() - 10);
  }
 }
else if (speedSpinner!=NULL && speedSpinner->isEnabled())
 {
  if (speedSpinner->value()<= speedSpinner->maximum() &&
      speedSpinner->value() > speedSpinner->minimum() )
  {
   int speedvalue= speedSpinner->value() - 10;
   if(speedvalue >speedSpinner->minimum())
    speedSpinner->setValue(speedvalue);
   else
    speedSpinner->setValue(speedSpinner->minimum());
  }
 }
}

/*private*/ void ControlPanel::speedSetting(float speed)
{
 // multiply by MAX_SPEED, and round to find the new slider setting.
 int newSliderSetting = qRound(speed * MAX_SPEED) ;
 if (log->isDebugEnabled())
 {
  log->debug( "speedSetting: new speed float: " + QString::number(speed) + " slider pos: " + QString::number(newSliderSetting) ) ;}
 speedSlider->setValue( newSliderSetting );
 //speedSlider.repaint();
 if(speedSpinner!=NULL)
     speedSpinner->setValue(newSliderSetting);
}
/**
 * Handle the selection from the popup menu.
 *
 * @param e The ActionEvent causing the action.
 */
//@Override
/*public*/ void ControlPanel::actionPerformed(/*ActionEvent e*/) {
    ControlPanelPropertyEditor* editor
            = new ControlPanelPropertyEditor(this);
    editor->setVisible(true);
}
/**
 * Configure the active Speed Step modes based on what is supported by
 * the DCC system
 */
/*private*/ void ControlPanel::configureAvailableSpeedStepModes()
{
 int modes = InstanceManager::throttleManagerInstance()->supportedSpeedModes();
 if((modes & DccThrottle::SpeedStepMode128) != 0)
 {
  speedStep128Button->setEnabled(true);
 }
 else
 {
  speedStep128Button->setEnabled(false);
 }
 if((modes & DccThrottle::SpeedStepMode28) != 0)
 {
  speedStep28Button->setEnabled(true);
 }
 else
 {
  speedStep28Button->setEnabled(false);
 }
 if((modes & DccThrottle::SpeedStepMode27) != 0)
 {
  speedStep27Button->setEnabled(true);
 }
 else
 {
  speedStep27Button->setEnabled(false);
 }
 if((modes & DccThrottle::SpeedStepMode14) != 0)
 {
  speedStep14Button->setEnabled(true);
 }
 else
 {
  speedStep14Button->setEnabled(false);
 }
}

void ControlPanel::on_menu_requested()
{
 propertiesPopup->exec(QCursor::pos());
}
/**
 * Collect the prefs of this object into XML Element
 * <ul>
 * <li> Window prefs
 * </ul>
 *
 *
 * @return the XML of this object.
 */
/*public*/ QDomElement ControlPanel::getXml()
{
 QDomDocument doc = QDomDocument();
    QDomElement me = doc.createElement("ControlPanel");
    me.setAttribute("displaySpeedSlider", (this->_displaySlider?"true":"false"));
    me.setAttribute("trackSlider", (this->trackSlider));
    me.setAttribute("trackSliderMinInterval", QString::number(this->trackSliderMinInterval));
    me.setAttribute("switchSliderOnFunction", switchSliderFunction != NULL ? switchSliderFunction : "Fxx");
    //Element window = new Element("window");
//    java.util.ArrayList<Element> children = new java.util.ArrayList<Element>(1);
//    children.add(WindowPreferences.getPreferences(this));
//    me.setContent(children);
    me.appendChild(WindowPreferences::getPreferences(this));
    return me;
}

/**
 * Set the preferences based on the XML Element.
 * <ul>
 * <li> Window prefs
 * </ul>
 *
 *
 * @param e The Element for this object.
 */
/*public*/ void ControlPanel::setXml(QDomElement e)
{
    internalAdjust = true;
    try {
     bool bok;
        this->setSpeedController(e.attribute("displaySpeedSlider").toInt());
     if(!bok) throw DataConversionException();
    } catch (DataConversionException ex) {
        log->error("DataConversionException in setXml: " + ex.getMessage());
    } catch (Exception em) {
        // in this case, recover by displaying the speed slider.
        this->setSpeedController(SLIDERDISPLAY);
    }
    QString tsAtt = e.attribute("trackSlider");
    if (tsAtt != NULL)
    {
     try
     {
      if(tsAtt == "true")
       trackSlider = true;
      else if(tsAtt == "false")
       trackSlider = false;
      else throw DataConversionException();
     }
     catch (DataConversionException ex) {
      trackSlider = trackSliderDefault;
     }
    } else {
        trackSlider = trackSliderDefault;
    }
    QString tsmiAtt = e.attribute("trackSliderMinInterval");
    if (tsmiAtt != "")
    {
     try
     {
      bool bok;
      trackSliderMinInterval = tsmiAtt.toLong(&bok);
      if(!bok) throw DataConversionException();
     }
     catch (DataConversionException ex) {
         trackSliderMinInterval = trackSliderMinIntervalDefault;
     }
     if (trackSliderMinInterval < trackSliderMinIntervalMin)
     {
         trackSliderMinInterval = trackSliderMinIntervalMin;
     } else if (trackSliderMinInterval > trackSliderMinIntervalMax)
     {
         trackSliderMinInterval = trackSliderMinIntervalMax;
     }
    }
    else
    {
        trackSliderMinInterval = trackSliderMinIntervalDefault;
    }
    if ((prevShuntingFn == "") && (e.attribute("switchSliderOnFunction") != ""))
    {
        setSwitchSliderFunction(e.attribute("switchSliderOnFunction"));
    }
    internalAdjust = false;
    QDomElement window = e.firstChildElement("window");
    WindowPreferences::setPreferences(this, window);
}

/*public*/ void ControlPanel::setSwitchSliderFunction(QString fn)
{
 switchSliderFunction = fn;
 if ((switchSliderFunction == "") || (switchSliderFunction.length() == 0)) {
     return;
 }
 if ((_throttle != NULL) && (_displaySlider != STEPDISPLAY))
 { // Update UI depending on function state
  try
  {
//            java.lang.reflect.Method getter = throttle.getClass().getMethod("get" + switchSliderFunction, (Class[]) null);
   QByteArray member = QMetaObject::normalizedSignature(QString("get"+switchSliderFunction).toLocal8Bit());

   int methodIndex = _throttle->metaObject()->indexOfMethod(member);
//   if(methodIndex < 0) throw Exception("invalid switchslider function "+ switchSliderFunction);

//            bool state = (Boolean) getter.invoke(throttle, (Object[]) null);
   bool state;
   if(QMetaObject::invokeMethod(_throttle, member, Qt::AutoConnection, Q_RETURN_ARG(bool, state)))
   {
    if (state) {
        setSpeedController(SLIDERDISPLAYCONTINUOUS);
    } else {
        setSpeedController(SLIDERDISPLAY);
    }
   }
   else throw Exception(QString("error invoking method ") + member);
  }
  catch (Exception ex)
  {
   log->debug("Exception in setSwitchSliderFunction: " + ex.getMessage() + " while looking for function " + switchSliderFunction);
  }
 }
}
void ControlPanel::resizeEvent(QResizeEvent *evt)
{
 QSize _size = evt->size();
 speedControlPanel->resize(speedControlPanel->size().width(), _size.height()- buttonPanel->height()-40);
 sliderPanel->resize(sliderPanel->size().width(), _size.height()- buttonPanel->height()-60);
}

/*public*/ QString ControlPanel::getSwitchSliderFunction() {
    return switchSliderFunction;
}

void ControlPanel::on_editProperties()
{
 ControlPanelPropertyEditor* editor
         = new ControlPanelPropertyEditor(this);
 editor->setVisible(true);

}
