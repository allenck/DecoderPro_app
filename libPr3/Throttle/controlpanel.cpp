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
#include <QFormLayout>
#include "../../LayoutEditor/jlabel.h"
#include <QPushButton>
#include "namedicon.h"
#include "windowpreferences.h"

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


// Save the speed step mode to aid in storage of the throttle.
///*private*/ int _speedStepMode = DccThrottle::SpeedStepMode128;
/**
 *  Constructor.
 */
/*public*/ ControlPanel::ControlPanel(LearnThrottleFrame* ltf, QWidget *parent) : QDockWidget(tr("Speed"),parent)
{
 //super("Speed");
 _displaySlider = true;
 speedControllerEnable = false;
 _emergencyStop = false;

 _throttle = NULL;
 internalAdjust = false;
 buttonFrame = new ButtonFrame;

 trackSliderMinInterval = 500;          // milliseconds
 lastTrackedSliderMovementTime = 0;

 // LocoNet really only has 126 speed steps i.e. 0..127 - 1 for em stop
 MAX_SPEED = 126;

 _throttleFrame = ltf;
 speedSlider = new QSlider(/*0, MAX_SPEED*/);
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

 SpeedStep128Button = new QRadioButton(tr("128 SS"));
 SpeedStep28Button = new QRadioButton(tr("28 SS"));
 SpeedStep27Button = new QRadioButton(tr("27 SS"));
 SpeedStep14Button= new QRadioButton(tr("14 SS"));
 log = new Logger("ControlPanel");
 initGUI();
 //pack();
}

/**
 *  Get notification that a throttle has been found as we requested.
 *
 * @param  t  An instantiation of the DccThrottle with the address requested.
 */
/*public*/ void ControlPanel::notifyThrottleFound(DccThrottle* t)
{
 if(log->isDebugEnabled()) log->debug("control panel received new throttle");
 _throttle = t;
 this->setEnabled(true);
 this->setSpeedValues((int) t->getSpeedIncrement(),
                        (int) t->getSpeedSetting());
 this->setSpeedSteps(t->getSpeedStepMode());
 //_throttle.addPropertyChangeListener(this);
 AbstractThrottle* at = (AbstractThrottle*)_throttle;
 connect(at, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 buttonFrame->notifyThrottleFound(t);
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
 if(log->isDebugEnabled()) log->debug("propertyChange: "+e->getPropertyName()+", newValue= "+
                                       e->getNewValue().toString());
 if (e->getPropertyName()==("SpeedSetting"))
 {
  internalAdjust=true;
  float speed=( e->getNewValue().toFloat());
  speedSlider->blockSignals(true);
  speedSetting(speed);
  speedSlider->blockSignals(false);
  // _throttleFrame->setSpeedSetting(speed);
//  if (_emergencyStop && speed < 0.0F)
//  {
//   _throttleFrame.stopRunTrain();
//  }
  if (speed != 0.0)
  {
   _emergencyStop = (speed < 0.0);
  }
//  else
//  {
//   if(_emergencyStop)
//    buttonFrame->stop();
//  }
 }
 else if (e->getPropertyName()==("SpeedSteps"))
 {
  int steps=( e->getNewValue().toInt());
  setSpeedSteps(steps);
//        _throttleFrame->setSpeedStepMode(steps);
 }
 else if (e->getPropertyName()==("IsForward"))
 {
  bool bForward=( e->getNewValue().toBool());
//        _throttleFrame->setButtonForward(Forward);
  buttonFrame->setForwardDirection(bForward);
 }
 else
 {
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
 SpeedStep128Button->setEnabled(isEnabled);
 SpeedStep28Button->setEnabled(isEnabled);
 SpeedStep27Button->setEnabled(isEnabled);
 SpeedStep14Button->setEnabled(isEnabled);
 if(isEnabled) configureAvailableSpeedStepModes();
 speedControllerEnable = isEnabled;
 if (_displaySlider) {
     speedSpinner->setEnabled(false);
     speedSlider->setEnabled(isEnabled);
 } else {
     speedSpinner->setEnabled(isEnabled);
     speedSlider->setEnabled(false);
 }
 QDockWidget::setEnabled(isEnabled);
}

/**
 *  Set the GUI to match the speed steps of the current address.
 *
 * @param  steps Desired number of speed steps. One of 14,27,28,or 128.  Defaults to 128
 * step mode
 */
/*public*/ void ControlPanel::setSpeedSteps(int steps)
{
 // Save the old speed as a float
 float oldSpeed = (speedSlider->value() / ( MAX_SPEED * 1.0f ) ) ;

 if(steps == DccThrottle::SpeedStepMode14)
 {
        SpeedStep14Button->setChecked(true);
        SpeedStep27Button->setChecked(false);
        SpeedStep28Button->setChecked(false);
        SpeedStep128Button->setChecked(false);
        MAX_SPEED=14;
    } else  if(steps == DccThrottle::SpeedStepMode27) {
        SpeedStep14Button->setChecked(false);
        SpeedStep27Button->setChecked(true);
        SpeedStep28Button->setChecked(false);
        SpeedStep128Button->setChecked(false);
        MAX_SPEED=27;
    } else  if(steps == DccThrottle::SpeedStepMode28) {
        SpeedStep14Button->setChecked(false);
        SpeedStep27Button->setChecked(false);
        SpeedStep28Button->setChecked(true);
        SpeedStep128Button->setChecked(false);
        MAX_SPEED=28;
    } else  {
        SpeedStep14Button->setChecked(false);
        SpeedStep27Button->setChecked(false);
        SpeedStep28Button->setChecked(false);
        SpeedStep128Button->setChecked(true);
        MAX_SPEED=126;
    }
    //_speedStepMode=steps;

    // rescale the speed slider to match the new speed step mode
    internalAdjust=true;
    speedSlider->setMaximum(MAX_SPEED);
    speedSlider->setValue((int)(oldSpeed * MAX_SPEED));
    speedSlider->setTickInterval(MAX_SPEED/2);
    QHash<int,QLabel*> labelTable =  QHash<int,QLabel*>();
    labelTable.insert((MAX_SPEED/2), new QLabel("50%"));
    labelTable.insert((MAX_SPEED), new QLabel("100%"));
    labelTable.insert((0), new QLabel(tr("LabelStop")));
//    speedSlider->setLabelTable(labelTable);
//    speedSlider->setPaintTicks(true);
//    speedSlider->setPaintLabels(true);

    internalAdjust=true;
    speedSpinner->setMaximum(MAX_SPEED);
    speedSpinner->setMinimum(0);
    // rescale the speed value to match the new speed step mode
    speedSpinner->setValue(speedSlider->value());
}

/**
 *  Set the Speed Control selection method
 *
 *  @param displaySlider integer value. possible values:
 *	SLIDERDISPLAY  = use speed slider display
 *      STEPDISPLAY = use speed step display
 */
/*public*/ void ControlPanel::setSpeedController(bool displaySlider)
{
 if (displaySlider)
 {
  sliderPanel->setVisible(true);
  speedSlider->setEnabled(speedControllerEnable);
  spinnerPanel->setVisible(false);
  if (speedSpinner!=NULL) speedSpinner->setEnabled(false);
 }
 else
 {
  sliderPanel->setVisible(false);
  speedSlider->setEnabled(false);
  spinnerPanel->setVisible(true);
  speedSpinner->setEnabled(speedControllerEnable);
 }
 _displaySlider=displaySlider;
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
 QFont f = font();
 f.setPointSize(8);
 setFont(f);
 QWidget* mainPanel = new QWidget(this);
 QFormLayout* formLayout = new QFormLayout(mainPanel);
 mainPanel->setLayout(formLayout);
 formLayout->setObjectName("formLayout");
    //this->setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
 QVBoxLayout* mainPanelLayout = new QVBoxLayout();
 mainPanelLayout->setObjectName("mainPanelLayout");

 speedControlPanel = new QWidget();
 QHBoxLayout* speedControlPanelLayout;
 speedControlPanel->setLayout(speedControlPanelLayout = new QHBoxLayout);//(speedControlPanel,BoxLayout.X_AXIS));
 speedControlPanelLayout->setObjectName("speedControlPanelLayout");
 mainPanelLayout->addWidget(speedControlPanel,0,Qt::AlignCenter);

 sliderPanel = new QWidget();
 //sliderPanel->setContentsMargins(0,0,0,0);
 QGridLayout* sliderPanelLayout;
 sliderPanel->setLayout(sliderPanelLayout = new QGridLayout());

 GridBagConstraints constraints;// = GridBagConstraints();
 constraints.anchor = GridBagConstraints::CENTER;
 constraints.fill=GridBagConstraints::BOTH;
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

 sliderPanelLayout->addWidget(speedSlider, constraints.gridy, constraints.gridx, constraints.rowSpan(), constraints.colSpan());
    //this->getContentPane().add(sliderPanel,BorderLayout.CENTER);
 speedControlPanelLayout->addWidget(sliderPanel);
 speedSlider->setOrientation(Qt::Vertical);
 speedSlider->setTickInterval(MAX_SPEED/2);
 speedSlider->setMinimumSize(speedSlider->sizeHint());
 QHash<int,QLabel*> labelTable =  QHash<int,QLabel*>();  // TODO: see QWT!
//    labelTable.put(Integer.valueOf(MAX_SPEED/2), new JLabel("50%"));
//    labelTable.put(Integer.valueOf(MAX_SPEED), new JLabel("100%"));
//    labelTable.put(Integer.valueOf(0), new JLabel(tr("LabelStop")));
//    speedSlider->setLabelTable(labelTable);
//    speedSlider->setPaintTicks(true);
//    speedSlider->setPaintLabels(true);
    // remove old actions
//    speedSlider.addChangeListener( new ChangeListener()
//        {
//            /*public*/ void stateChanged(ChangeEvent e) {
//                if ( !internalAdjust) {
//                    bool doIt = false;
//                    if (!speedSlider->valueIsAdjusting()) {
//                        doIt = true;
//                    } else if (System.currentTimeMillis() - lastTrackedSliderMovementTime >= trackSliderMinInterval) {
//                        doIt = true;
//                        lastTrackedSliderMovementTime = System.currentTimeMillis();
//                    }
//                    if (doIt) {
//                        float newSpeed = (speedSlider->value() / ( MAX_SPEED * 1.0f ) ) ;
//                        if (log->isDebugEnabled()) {log->debug( "stateChanged: slider pos: " + speedSlider->value() + " speed: " + newSpeed );}
//                        _throttle->setSpeedSetting( newSpeed );
//                        if(speedSpinner!=NULL)
//                            speedSpinnerModel->setValue(Integer.valueOf(speedSlider->value()));
//                    }
//                } else {
//                    internalAdjust=false;
//                }
//            }
//        });
 connect(speedSlider, SIGNAL(valueChanged(int)), this, SLOT(OnSliderChanged(int)));

 spinnerPanel = new QWidget();
 QGridLayout* spinnerPanelLayout;
 spinnerPanel->setLayout(spinnerPanelLayout = new QGridLayout());
 spinnerPanelLayout->setObjectName("spinnerPanelLayout");
 if(speedSpinner!=NULL)
  spinnerPanelLayout->addWidget(speedSpinner, constraints.gridy, constraints.gridx, constraints.rowSpan(), constraints.colSpan());
 //this->getContentPane().add(spinnerPanel,BorderLayout.CENTER);
 speedControlPanelLayout->addWidget(spinnerPanel);
 // remove old actions
 if(speedSpinner!=NULL)
//        speedSpinner.addChangeListener(new ChangeListener()
//            {
//                /*public*/ void stateChanged(ChangeEvent e)
//                {
//                    if ( !internalAdjust) {
//                        float newSpeed = ((Integer)speedSpinner->value()).floatValue() / ( MAX_SPEED * 1.0f );
//                        if (log->isDebugEnabled()) {log->debug( "stateChanged: spinner pos: " + speedSpinner->value() + " speed: " + newSpeed );}
//                        _throttle->setSpeedSetting( newSpeed );
//                        //_throttleFrame->setSpeedSetting( newSpeed );
//                        speedSlider->setValue(((Integer)speedSpinner->value()).intValue());
//                    } else {
//                        internalAdjust=false;
//                    }
//                }
//            });
 connect(speedSpinner, SIGNAL(valueChanged(int)), this, SLOT(OnSpinnerChanged(int)));
 QButtonGroup* speedStepButtons = new QButtonGroup();
 speedStepButtons->addButton(SpeedStep128Button);
 speedStepButtons->addButton(SpeedStep28Button);
 speedStepButtons->addButton(SpeedStep27Button);
 speedStepButtons->addButton(SpeedStep14Button);
 constraints.gridy = GridBagConstraints::NONE;
 constraints.gridy = 1;
 spinnerPanelLayout->addWidget(SpeedStep128Button, constraints.gridy, constraints.gridx, constraints.rowSpan(), constraints.colSpan());
 constraints.gridy = 2;
 spinnerPanelLayout->addWidget(SpeedStep28Button, constraints.gridy, constraints.gridx, constraints.rowSpan(), constraints.colSpan());
 constraints.gridy = 3;
 spinnerPanelLayout->addWidget(SpeedStep27Button, constraints.gridy, constraints.gridx, constraints.rowSpan(), constraints.colSpan());
 constraints.gridy = 4;
 spinnerPanelLayout->addWidget(SpeedStep14Button, constraints.gridy, constraints.gridx, constraints.rowSpan(), constraints.colSpan());

//    SpeedStep14Button.addActionListener(new ActionListener()
//                                        {
//                                            /*public*/ void actionPerformed(ActionEvent e)
//                                            {
//                                                setSpeedSteps(DccThrottle::SpeedStepMode14);
//                                                _throttle->setSpeedStepMode(DccThrottle::SpeedStepMode14);
//                                            }
//                                        });
 connect(SpeedStep14Button, SIGNAL(clicked(bool)), this, SLOT(OnSpeedStep14()));

//    SpeedStep27Button.addActionListener(new ActionListener()
//                                        {
//                                            /*public*/ void actionPerformed(ActionEvent e)
//                                            {
//                                                setSpeedSteps(DccThrottle::SpeedStepMode27);
//                                                _throttle->setSpeedStepMode(DccThrottle::SpeedStepMode27);
//                                            }
//                                        });
 connect(SpeedStep27Button, SIGNAL(clicked(bool)), this, SLOT(OnSpeedStep27()));

//    SpeedStep28Button.addActionListener(new ActionListener()
//                                        {
//                                            /*public*/ void actionPerformed(ActionEvent e)
//                                            {
//                                                setSpeedSteps(DccThrottle::SpeedStepMode28);
//                                                _throttle->setSpeedStepMode(DccThrottle::SpeedStepMode28);
//                                            }
//                                        });
 connect(SpeedStep28Button, SIGNAL(clicked(bool)), this, SLOT(OnSpeedStep28()));


//    SpeedStep128Button.addActionListener(new ActionListener()
//                                         {
//                                             /*public*/ void actionPerformed(ActionEvent e)
//                                             {
//                                                 setSpeedSteps(DccThrottle::SpeedStepMode128);
//                                                 _throttle->setSpeedStepMode(DccThrottle::SpeedStepMode128);
//                                             }
//                                         });
 connect(SpeedStep128Button, SIGNAL(clicked(bool)), this, SLOT(OnSpeedStep128()));

    // set by default which speed selection method is on top
 setSpeedController(_displaySlider);
 mainPanelLayout->addWidget(buttonFrame);
 formLayout->setLayout(0, QFormLayout::SpanningRole, mainPanelLayout);
 this->setWidget(mainPanel);
 mainPanel->show();
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
void ControlPanel::OnSliderChanged(int )
{
 if ( !internalAdjust)
 {
  bool doIt = false;
//  if (!speedSlider->getValueIsAdjusting())
//  {
//   doIt = true;
//   lastTrackedSliderMovementTime = QDateTime::currentMSecsSinceEpoch() - trackSliderMinInterval;
//  }
//  else
  if (trackSlider
  && QDateTime::currentMSecsSinceEpoch() - lastTrackedSliderMovementTime >= trackSliderMinInterval) {
      doIt = true;
      lastTrackedSliderMovementTime = QDateTime::currentMSecsSinceEpoch();
  }  if (doIt)
  {
   float newSpeed = (speedSlider->value() / ( MAX_SPEED * 1.0f ) ) ;
   if (log->isDebugEnabled()) {log->debug( "stateChanged: slider pos: " + QString::number(speedSlider->value()) + " speed: " + QString::number(newSpeed) );}
   _throttle->setSpeedSetting(newSpeed );
   if(speedSpinner!=NULL)
    speedSpinner->setValue(speedSlider->value());
  }
 }
 else
 {
    internalAdjust=false;
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
    setSpeedSteps(DccThrottle::SpeedStepMode28);
    _throttle->setSpeedStepMode(DccThrottle::SpeedStepMode28);
}
void ControlPanel::OnSpeedStep14()
{
 setSpeedSteps(DccThrottle::SpeedStepMode14);
 _throttle->setSpeedStepMode(DccThrottle::SpeedStepMode14);
}
void ControlPanel::OnSpeedStep27()
{
 setSpeedSteps(DccThrottle::SpeedStepMode27);
 _throttle->setSpeedStepMode(DccThrottle::SpeedStepMode27);
}
void ControlPanel::OnSpeedStep128()
{
 setSpeedSteps(DccThrottle::SpeedStepMode128);
 _throttle->setSpeedStepMode(DccThrottle::SpeedStepMode128);
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
 * Configure the active Speed Step modes based on what is supported by
 * the DCC system
 */
/*private*/ void ControlPanel::configureAvailableSpeedStepModes()
{
 int modes = InstanceManager::throttleManagerInstance()->supportedSpeedModes();
 if((modes & DccThrottle::SpeedStepMode128) != 0)
 {
  SpeedStep128Button->setEnabled(true);
 }
 else
 {
  SpeedStep128Button->setEnabled(false);
 }
 if((modes & DccThrottle::SpeedStepMode28) != 0)
 {
  SpeedStep28Button->setEnabled(true);
 }
 else
 {
  SpeedStep28Button->setEnabled(false);
 }
 if((modes & DccThrottle::SpeedStepMode27) != 0)
 {
  SpeedStep27Button->setEnabled(true);
 }
 else
 {
  SpeedStep27Button->setEnabled(false);
 }
 if((modes & DccThrottle::SpeedStepMode14) != 0)
 {
  SpeedStep14Button->setEnabled(true);
 }
 else
 {
  SpeedStep14Button->setEnabled(false);
 }
}

// class Button Frame borrowed from LearnThrottleFrame
//class ButtonFrame extends JPanel {
        //private GridBagConstraints sliderConstraints;
 /*static*/ int ButtonFrame::STRUT_SIZE = 10;

ButtonFrame::ButtonFrame(/*DccThrottle* throttle,*/ QWidget* parent) : QWidget(parent)
{
            //super();
 this->_throttle = NULL;
 group = new QButtonGroup();

 forwardButton = new QRadioButton(tr("Forward"));
 group->addButton(forwardButton);
 reverseButton = new QRadioButton(tr("Reverse"));
 group->addButton(reverseButton);
 directionOffIcon = new NamedIcon("program:resources/icons/USS/sensor/amber-off.gif", "amber-off");
 directionOnIcon = new NamedIcon("program:resources/icons/USS/sensor/amber-on.gif", "amber-on");
 stopIcon = new NamedIcon("program:resources/icons/USS/sensor/red-on.gif", "red-on");
 initGUI();
}

/*private*/ void ButtonFrame::initGUI()
{
 QVBoxLayout* thisLayout = new QVBoxLayout;
 setLayout(thisLayout);
 //QWidget* _buttonPanel = new QWidget();
 QVBoxLayout* buttonPanelLayout= new QVBoxLayout;
// _buttonPanel->setLayout(buttonPanelLayout = new QVBoxLayout);//(_buttonPanel, BoxLayout.X_AXIS));

 thisLayout->addLayout(buttonPanelLayout);

 GridBagConstraints constraints;// = GridBagConstraints();
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
 forwardLight->setIcon(directionOffIcon);

// forwardButton.addActionListener(new ActionListener()
// {
//  /*public*/ void actionPerformed(ActionEvent e)
//  {
//    setIsForward(true);
//  }
// });
 connect(forwardButton, SIGNAL(clicked()), this, SLOT(OnForwardButton()));
 //QWidget* forwardPanel = new QWidget();
 QGridLayout* forwardPanelLayout = new QGridLayout();
 //forwardPanel->setLayout(forwardPanelLayout = new QGridLayout());
 forwardPanelLayout->addWidget(forwardLight, constraints.gridy, constraints.gridx, constraints.rowSpan(), constraints.colSpan());
 constraints.gridy = 1;
 forwardPanelLayout->addWidget(forwardButton, constraints.gridy, constraints.gridx, constraints.rowSpan(), constraints.colSpan());

 reverseLight = new JLabel();
 reverseLight->setIcon(directionOffIcon);
//    reverseButton.addActionListener(new ActionListener() {
//                                        /*public*/ void actionPerformed(ActionEvent e) {
//                                            setIsForward(false);
//                                        }
//                                    });
 connect(reverseButton, SIGNAL(clicked()), this, SLOT(OnReverseButton()));
 //QWidget* reversePanel = new QWidget();
 QGridLayout* reversePanelLayout = new QGridLayout();
 //reversePanel->setLayout(reversePanelLayout = new QGridLayout());
 constraints.gridy = 0;
 reversePanelLayout->addWidget(reverseLight, constraints.gridy, constraints.gridx, constraints.rowSpan(), constraints.colSpan());
 constraints.gridy = 1;
 reversePanelLayout->addWidget(reverseButton, constraints.gridy, constraints.gridx, constraints.rowSpan(), constraints.colSpan());

 stopLabel = new JLabel(tr("Emergency"));
 _gap = -(stopIcon->getIconWidth()+stopLabel->sizeHint().width())/2;
 stopButton = new QRadioButton(tr("Stop"));
 group->addButton(stopButton);

//    stopButton.addActionListener(new ActionListener() {
//                                     /*public*/ void actionPerformed(ActionEvent e)  {
//                                         stop();
//                                     }
//                                 });
 connect(stopButton, SIGNAL(clicked()),this, SLOT(stop()));
 //QWidget* stopPanel = new QWidget();
 QGridLayout* stopPanelLayout = new QGridLayout();
 //stopPanel->setLayout(stopPanelLayout = new QGridLayout());
 constraints.gridy = 0;
 stopPanelLayout->addWidget(stopLabel, constraints.gridy, constraints.gridx, constraints.rowSpan(), constraints.colSpan());
 constraints.gridy = 1;
 stopPanelLayout->addWidget(stopButton, constraints.gridy, constraints.gridx, constraints.rowSpan(), constraints.colSpan());

 //buttonPanelLayout->addStrut(STRUT_SIZE);
 //buttonPanelLayout->addWidget(forwardPanel);
 buttonPanelLayout->addLayout(forwardPanelLayout);
 //buttonPanelLayout->addStrut(STRUT_SIZE);
 buttonPanelLayout->addLayout(stopPanelLayout);
 //buttonPanelLayout->addStrut(STRUT_SIZE);
 buttonPanelLayout->addLayout(reversePanelLayout);
 //buttonPanelLayout->addStrut(STRUT_SIZE);
    //pack();
}
void ButtonFrame::OnForwardButton()
{
    //((ControlPanel*)parent())->setIsForward(true);
 if(_throttle != NULL)
  _throttle->setIsForward(true);

}
void ButtonFrame::OnReverseButton()
{
    //((ControlPanel*)parent())->setIsForward(false);
 if(_throttle != NULL)
  _throttle->setIsForward(false);
}

/**
 *  Perform an emergency stop
 */
/*public*/ void ButtonFrame::stop()
{
 if(_throttle != NULL)
 {
    _throttle->setSpeedSetting(-0.5F);
    //setSpeedSetting(-1);
    //setSpeedSetting(0);
    _throttle->setSpeedSetting(0.0F);
    stopLabel->setIcon(stopIcon);
    //stopLabel->setIconTextGap(_gap);
    //pack();
    stopButton->setChecked(true);
    repaint();
 }
}

/*public*/ void ButtonFrame::notifyThrottleFound(DccThrottle* t)
{
    bool isForward = t->getIsForward();
    this->setForwardDirection(isForward);
    _throttle = t;

    //((ControlPanel*)parent())->setIsForward(isForward);
    if(_throttle != NULL)
     _throttle->setIsForward(isForward);

}

/**
 *  Set the GUI to match that the loco is set to forward.
 * @param  isForward  True if the loco is set to forward, false otherwise.
 */
/*public*/ void ButtonFrame::setForwardDirection(bool isForward)
{
 if (isForward)
 {
  forwardLight->setIcon(directionOnIcon);
  reverseLight->setIcon(directionOffIcon);
  forwardButton->setChecked(true);
 }
 else
 {
  forwardLight->setIcon(directionOffIcon);
  reverseLight->setIcon(directionOnIcon);
  reverseButton->setChecked(true);
 }
    //pack();
 repaint();
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
//    me.setAttribute("trackSlider", (this->trackSlider));
    me.setAttribute("trackSliderMinInterval", QString::number(this->trackSliderMinInterval));
//    me.setAttribute("switchSliderOnFunction", switchSliderFunction != NULL ? switchSliderFunction : "Fxx");
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
/*public*/ void ControlPanel::setXml(QDomElement e) {
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
     if (trackSliderMinInterval < trackSliderMinIntervalMin) {
         trackSliderMinInterval = trackSliderMinIntervalMin;
     } else if (trackSliderMinInterval > trackSliderMinIntervalMax) {
         trackSliderMinInterval = trackSliderMinIntervalMax;
     }
    } else {
        trackSliderMinInterval = trackSliderMinIntervalDefault;
    }
    if ((prevShuntingFn == "") && (e.attribute("switchSliderOnFunction") != "")) {
        setSwitchSliderFunction(e.attribute("switchSliderOnFunction"));
    }
    internalAdjust = false;
    QDomElement window = e.firstChildElement("window");
    WindowPreferences::setPreferences(this, window);
}

/*public*/ void ControlPanel::setSwitchSliderFunction(QString fn) {
    switchSliderFunction = fn;
    if ((switchSliderFunction == "") || (switchSliderFunction.length() == 0)) {
        return;
    }
    if ((_throttle != NULL) && (_displaySlider != STEPDISPLAY)) { // Update UI depending on function state
#if 0
        try {
            java.lang.reflect.Method getter = throttle.getClass().getMethod("get" + switchSliderFunction, (Class[]) null);

            bool state = (Boolean) getter.invoke(throttle, (Object[]) null);
            if (state) {
                setSpeedController(SLIDERDISPLAYCONTINUOUS);
            } else {
                setSpeedController(SLIDERDISPLAY);
            }

        } catch (Exception ex) {
            log->debug("Exception in setSwitchSliderFunction: " + ex + " while looking for function " + switchSliderFunction);
        }
#endif
    }
}

/*public*/ QString ControlPanel::getSwitchSliderFunction() {
    return switchSliderFunction;
}
