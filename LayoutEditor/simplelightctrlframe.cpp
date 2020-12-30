#include "simplelightctrlframe.h"
#include <QLabel>
#include "jtextfield.h"
#include "decimalformat.h"
#include <QPushButton>
#include "light.h"
#include <QVBoxLayout>
#include "flowlayout.h"
#include <QCheckBox>
#include "instancemanager.h"
#include "proxylightmanager.h"
#include <QIntValidator>

//SimpleLightCtrlFrame::SimpleLightCtrlFrame(QWidget *parent) :
//  JmriJFrame(parent)
//{
//}
/**
 * Frame controlling a single light
 *
 * This was a copy of simple turnout control.
 *
 * @author	Ken Cameron Copyright (C) 2008
 * @author	Bob Jacobsen Copyright (C) 2001, 2008
 * @version $Revision: 28746 $
 */
///*public*/ class SimpleLightCtrlFrame extends jmri.util.JmriJFrame implements java.beans.PropertyChangeListener {

/**
 *
 */
//private static final long serialVersionUID = 7837647126381592983L;
//ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.simplelightctrl.SimpleLightCtrlBundle");
//static final ResourceBundle rbean = ResourceBundle.getBundle("jmri.NamedBeanBundle");



/*public*/ SimpleLightCtrlFrame::SimpleLightCtrlFrame(QWidget *parent) :
JmriJFrame(parent)
{
    //super();
 threeDigits = new DecimalFormat("000");
 oneDigits = new DecimalFormat("0");
 oneDotTwoDigits = new DecimalFormat("0.00");

 light = NULL;
 newState = "";

 // GUI member declarations
 textAdrLabel = new QLabel();
 adrTextField = new JTextField(5);
 //adrTextField->setValidator(new QIntValidator(1, 4096));
 statusButton = new QPushButton();

 onButton = new QPushButton();
 offButton = new QPushButton();

 textStateLabel = new QLabel();
 nowStateTextField = new QLabel();
 textIsEnabledLabel = new QLabel();
 statusIsEnabledCheckBox = new QCheckBox();
 textIsVariableLabel = new QLabel();
 statusIsVariableCheckBox = new QCheckBox();
 textIsTransitionLabel = new QLabel();
 statusIsTransitionCheckBox = new QCheckBox();

 intensityTextLabel1 = new QLabel();
 nowIntensityLabel = new QLabel();
 intensityTextField = new JTextField(4);
 intensityTextField->setValidator(new QIntValidator(0,100));
 intensityTextLabel2 = new QLabel();
 intensityButton = new QPushButton();

 intensityMinTextLabel = new QLabel();
 nowIntensityMinLabel = new QLabel();
 intensityMinTextField = new JTextField(4);
 intensityMinTextField->setValidator(new QIntValidator(0,100));
 intensityMaxTextLabel = new QLabel();
 nowIntensityMaxLabel = new QLabel();
 intensityMaxTextField = new JTextField(4);
 intensityMaxTextField->setValidator(new QIntValidator(0,100));
 transitionTimeTextLabel = new QLabel();
 nowTransitionTimeLabel = new QLabel();
 transitionTimeTextField = new JTextField(4);
 transitionTimeTextField->setValidator(new QIntValidator());

 applyButton = new QPushButton();
 log = new Logger("SimpleLightCtrlFrame");
 // configure items for GUI
 textAdrLabel->setText(tr("Light:"));
 textAdrLabel->setVisible(true);

 adrTextField->setText("");
 adrTextField->setVisible(true);
 adrTextField->setToolTip(tr("light number being controlled"));

 statusButton->setText(tr("Get Status"));
 statusButton->setVisible(true);
 statusButton->setToolTip(tr("LightGetStatusToolTip"));
//        statusButton.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                statusButtonActionPerformed(e);
//            }
//        });
 connect(statusButton, SIGNAL(clicked()), this, SLOT(statusButtonActionPerformed()));
 textStateLabel->setText(tr("Current State:"));
 textStateLabel->setVisible(true);
 nowStateTextField->setText(tr("<unknown>"));
 nowStateTextField->setVisible(true);
 textIsEnabledLabel->setText(tr("Enabled:"));
 textIsEnabledLabel->setVisible(true);
 statusIsEnabledCheckBox->setVisible(true);
 statusIsEnabledCheckBox->setEnabled(false);
 textIsVariableLabel->setText(tr("Variable:"));
 textIsVariableLabel->setVisible(true);
 statusIsVariableCheckBox->setVisible(true);
 statusIsVariableCheckBox->setEnabled(false);
 textIsTransitionLabel->setText(tr("Transitional:"));
 textIsTransitionLabel->setVisible(true);
 statusIsTransitionCheckBox->setVisible(true);
 statusIsTransitionCheckBox->setEnabled(false);

 onButton->setText(tr("On"));
 onButton->setVisible(true);
 onButton->setToolTip(tr("Press to turn light on/bright"));
//        onButton.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                onButtonActionPerformed(e);
//            }
//        });
 connect(onButton, SIGNAL(clicked()), this, SLOT(onButtonActionPerformed()));
 offButton->setText(tr("Off"));
 offButton->setVisible(true);
 offButton->setToolTip(tr("Press to turn light off/dim"));
//        offButton.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                offButtonActionPerformed(e);
//            }
//        });
 connect(offButton, SIGNAL(clicked()), this, SLOT(offButtonActionPerformed()));

 intensityTextLabel1->setText(tr("Intensity"));
 intensityTextLabel1->setVisible(true);
 nowIntensityLabel->setText("");
 nowIntensityLabel->setVisible(true);
 intensityTextField->setText(oneDigits->format(0));
 intensityTextField->setVisible(true);
 intensityTextLabel2->setText("%");
 intensityTextField->setToolTip(tr("0 to 100 for percent of output"));

 intensityMinTextLabel->setText(tr("Min Intensity: "));
 nowIntensityMinLabel->setText("");
 nowIntensityMinLabel->setVisible(true);
 intensityMinTextField->setText(oneDigits->format(0));
 intensityMinTextField->setVisible(true);
 intensityMinTextField->setToolTip(tr("Intensity for off, 0% to 100%"));
 intensityMaxTextLabel->setText(tr("Max Intensity: "));
 nowIntensityMaxLabel->setText("");
 nowIntensityMaxLabel->setVisible(true);
 intensityMaxTextField->setText(oneDigits->format(100));
 intensityMaxTextField->setVisible(true);
 intensityMaxTextField->setToolTip(tr("Intensity for on, 0% to 100%"));
 transitionTimeTextLabel->setText(tr("Transition Time: "));
 nowTransitionTimeLabel->setText("");
 nowTransitionTimeLabel->setVisible(true);
 transitionTimeTextField->setText(oneDigits->format(0));
 transitionTimeTextField->setVisible(true);
 transitionTimeTextField->setEnabled(true);
 transitionTimeTextField->setToolTip(tr("Speed of dimming, fast minutes for 0% to 100%"));
 intensityButton->setText(tr("Change Intensity"));
 intensityButton->setVisible(true);
 intensityButton->setToolTip(tr("Press to set target intensity"));
//        intensityButton.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                intensityButtonActionPerformed(e);
//            }
//        });
 connect(intensityButton, SIGNAL(clicked()), this, SLOT(intensityButtonActionPerformed()));

 applyButton->setText(tr("Apply"));
 applyButton->setVisible(true);
 applyButton->setToolTip(tr("Press to apply settings"));
//        applyButton.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                applyButtonActionPerformed(e);
//            }
//        });
 connect(applyButton, SIGNAL(clicked()), this, SLOT(applyButtonActionPerformed()));

 // general GUI config
 setTitle(tr("Light Control"));
//        getContentPane()->setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
 QWidget* centralWidget = new QWidget();
 QVBoxLayout* thisLayout = new QVBoxLayout(centralWidget);
 setCentralWidget(centralWidget);

 // install items in GUI
 //QWidget* pane2 = new QWidget();
 FlowLayout* p2Layout = new FlowLayout();
 p2Layout->addWidget(textAdrLabel);
 p2Layout->addWidget(adrTextField);
 p2Layout->addWidget(statusButton);
 thisLayout->addLayout(p2Layout);

 //pane2 = new QWidget();
 {
  FlowLayout* p2Layout = new FlowLayout();
 p2Layout->addWidget(textStateLabel);
 p2Layout->addWidget(nowStateTextField);
 p2Layout->addWidget(textIsEnabledLabel);
 p2Layout->addWidget(statusIsEnabledCheckBox);
 p2Layout->addWidget(textIsVariableLabel);
 p2Layout->addWidget(statusIsVariableCheckBox);
 p2Layout->addWidget(textIsTransitionLabel);
 p2Layout->addWidget(statusIsTransitionCheckBox);
 thisLayout->addLayout(p2Layout);
 }

 //pane2 = new QWidget();
 {
  FlowLayout* p2Layout = new FlowLayout();
 p2Layout->addWidget(onButton);
 p2Layout->addWidget(offButton);
 thisLayout->addLayout(p2Layout);
 }

 //pane2 = new QWidget();
 {
  FlowLayout* p2Layout = new FlowLayout();
 p2Layout->addWidget(intensityTextLabel1);
 p2Layout->addWidget(nowIntensityLabel);
 p2Layout->addWidget(intensityTextField);
 p2Layout->addWidget(intensityTextLabel2);
 p2Layout->addWidget(intensityButton);
 thisLayout->addLayout(p2Layout);
 }

 //pane2 = new QWidget();
 {
  FlowLayout* p2Layout = new FlowLayout();
 p2Layout->addWidget(intensityMinTextLabel);
 p2Layout->addWidget(nowIntensityMinLabel);
 p2Layout->addWidget(intensityMinTextField);
 p2Layout->addWidget(intensityMaxTextLabel);
 p2Layout->addWidget(nowIntensityMaxLabel);
 p2Layout->addWidget(intensityMaxTextField);
 p2Layout->addWidget(transitionTimeTextLabel);
 p2Layout->addWidget(nowTransitionTimeLabel);
 p2Layout->addWidget(transitionTimeTextField);
 thisLayout->addLayout(p2Layout);
 }

 //pane2 = new QWidget();
 {
  FlowLayout* p2Layout = new FlowLayout();
 p2Layout->addWidget(applyButton);
 thisLayout->addLayout(p2Layout);
 }

 // add help menu to window
 addHelpMenu("package.jmri.jmrit.simplelightctrl.SimpleLightCtrl", true);

 setMinimumSize(QSize(600, 200));
 resize(700, 300);
 adjustSize();
}

/*public*/ void SimpleLightCtrlFrame::offButtonActionPerformed(JActionEvent* /*e*/)
{
 // load address from switchAddrTextField
 try {
     if (light != NULL)
     {
         // we're changing the light we're watching
         light->removePropertyChangeListener((PropertyChangeListener*)this);
         //disconnect(light->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     light = ((ProxyLightManager*)InstanceManager::lightManagerInstance())->provideLight(
             adrTextField->text());

     if (light == NULL) {
         log->error(tr("Light name invalid: ") + adrTextField->text());
     } else {
         light->addPropertyChangeListener((PropertyChangeListener*)this);
         //connect(light->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         if (log->isDebugEnabled()) {
             log->debug("about to command CLOSED");
         }
         // and set commanded state to CLOSED
         light->setState(Light::OFF);
     }
 } catch (Exception ex) {
     log->error(tr("offButtonActionPerformed, exception: ") /*+ ex.toString()*/);
     nowStateTextField->setText("ERROR");
 }
}

/*public*/ void SimpleLightCtrlFrame::onButtonActionPerformed(JActionEvent* /*e*/)
{
 // load address from switchAddrTextField
 try
 {
  if (light != NULL)
  {
   // we're changing the light we're watching
   light->removePropertyChangeListener((PropertyChangeListener*)this);
//   disconnect(light->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
  light = ((ProxyLightManager*)InstanceManager::lightManagerInstance())->provideLight(
          adrTextField->text());

  if (light == NULL)
  {
   log->error(tr("Light name invalid: ") + adrTextField->text());
  }
  else
  {
   light->addPropertyChangeListener((PropertyChangeListener*)this);
//   connect(light->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   if (log->isDebugEnabled())
   {
    log->debug("about to command ON");
   }
   // and set commanded state to ON
   light->setState(Light::ON);
  }
 }
 catch (Exception ex)
 {
  log->error(tr("LightErrorOnButtonException") /*+ ex.toString()*/);
  nowStateTextField->setText("ERROR");
 }
}

/*public*/ void SimpleLightCtrlFrame::intensityButtonActionPerformed(JActionEvent* /*e*/)
{
 // load address from switchAddrTextField
 try
 {
  if (light != NULL)
  {
      // we're changing the light we're watching
   light->removePropertyChangeListener((PropertyChangeListener*)this);
//   disconnect(light->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
  light = ((ProxyLightManager*)InstanceManager::lightManagerInstance())->provideLight(
          adrTextField->text());

  if (light == NULL) {
      log->error(tr("Light name invalid: ") + adrTextField->text());
  }
  else
  {
   light->addPropertyChangeListener((PropertyChangeListener*)this);
//   connect(light->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   if (log->isDebugEnabled()) {
       log->debug("about to command DIM");
   }
   // and set commanded state to DIM
   light->setTargetIntensity(intensityTextField->text().trimmed().toDouble() / 100);
  }
 }
 catch (Exception ex)
 {
     log->error(tr("intensityButtonActionPerformed, exception: ")/* + ex.toString()*/);
     nowStateTextField->setText("ERROR");
 }
}

/**
 * handle changes for intensity, rate, etc...
 */
/*public*/ void SimpleLightCtrlFrame::applyButtonActionPerformed(JActionEvent* /*e*/) {
    // load address from switchAddrTextField
    try {
        if (light != NULL) {
            // we're changing the light we're watching
         light->removePropertyChangeListener((PropertyChangeListener*)this);
//         disconnect(light->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        }
        light = ((ProxyLightManager*)InstanceManager::lightManagerInstance())->provideLight(adrTextField->text());

        if (light == NULL) {
            nowStateTextField->setText(tr("Light name invalid: ") + adrTextField->text());
        } else {
            double min = intensityMinTextField->text().toDouble() / 100.;
            double max = intensityMaxTextField->text().toDouble() / 100.;
            double time = transitionTimeTextField->text().toDouble();
            if (log->isDebugEnabled()) {
                log->debug("setting min: " + QString::number(min) + " max: " + QString::number(max) + " transition: " + QString::number(time));
            }
            light->setMinIntensity(min);
            light->setMaxIntensity(max);
            light->setTransitionTime(time);
            updateLightStatusFields(false);
        }
    } catch (Exception ex) {
        log->error(tr("LightErrorApplyButtonException") /*+ ex.toString()*/);
        nowStateTextField->setText("ERROR");
    }
}

/**
 * handles request to update status
 *
 * @param e
 */
/*public*/ void SimpleLightCtrlFrame::statusButtonActionPerformed(JActionEvent* /*e*/)
{
 // load address from switchAddrTextField
 try
 {
  if (light != NULL)
  {
   // we're changing the light we're watching
   light->removePropertyChangeListener((PropertyChangeListener*)this);
//   disconnect(light->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
  light = ((ProxyLightManager*)InstanceManager::lightManagerInstance())->provideLight(adrTextField->text());

  if (light == NULL)
  {
   nowStateTextField->setText(tr("Light name invalid: ") + adrTextField->text());
  }
  else
  {
   updateLightStatusFields(true);
  }
 }
 catch (Exception ex)
 {
     log->error(tr("statusButtonActionPerformed, exception: ") /*+ ex.toString()*/);
     nowStateTextField->setText("ERROR");
 }
}

//	/*public*/ void lockButtonActionPerformed(java.awt.event.ActionEvent e) {
//		// load address from switchAddrTextField
//		try {
//			if (light != NULL)
//				light->removePropertyChangeListener(this);
//			light = InstanceManager.lightManagerInstance().provideLight(
//					adrTextField.text());
//
//			if (light == NULL) {
//				log->error("Light " + adrTextField.text()
//						+ " is not available");
//			} else {
//				light->addPropertyChangeListener(this);
//
//			}
//		} catch (Exception ex) {
//			log->error("LockButtonActionPerformed, exception: "
//							+ ex.toString());
//			nowStateTextField->setText("ERROR");
//		}
//	}
//	/*public*/ void lockPushButtonActionPerformed(java.awt.event.ActionEvent e) {
//		// load address from switchAddrTextField
//		try {
//			if (light != NULL)
//				light->removePropertyChangeListener(this);
//			light = InstanceManager.lightManagerInstance().provideLight(
//					adrTextField.text());
//
//			if (light == NULL) {
//				log->error("Light " + adrTextField.text()
//						+ " is not available");
//			} else {
//				light->addPropertyChangeListener(this);
//
//			}
//		} catch (Exception ex) {
//			log->error("LockPushButtonActionPerformed, exception: "
//							+ ex.toString());
//			nowStateTextField->setText("ERROR");
//		}
//	}

// update state field in GUI as state of light changes
/*public*/ void SimpleLightCtrlFrame::propertyChange(PropertyChangeEvent* e) {
    if (log->isDebugEnabled()) {
        log->debug("recv propertyChange: " + e->getPropertyName() + " " + e->getOldValue().toString() + " -> " + e->getNewValue().toString());
    }
    updateLightStatusFields(false);
}

/*private*/ void SimpleLightCtrlFrame::updateLightStatusFields(bool flag)
{
 int knownState = light->getState();
 switch (knownState)
 {
  case Light::ON:
      nowStateTextField->setText(tr("On"));
      break;
  case Light::INTERMEDIATE:
      nowStateTextField->setText(tr("Intermediate"));
      break;
  case Light::OFF:
      nowStateTextField->setText(tr("Off"));
      break;
  case Light::TRANSITIONINGTOFULLON:
      nowStateTextField->setText(tr("Transitioning To Full On"));
      break;
  case Light::TRANSITIONINGHIGHER:
      nowStateTextField->setText(tr("Transitioning Higher"));
      break;
  case Light::TRANSITIONINGLOWER:
      nowStateTextField->setText(tr("Transitioning Lower"));
      break;
  case Light::TRANSITIONINGTOFULLOFF:
      nowStateTextField->setText(tr("Transitioning To Full Off"));
      break;
  default:
      nowStateTextField->setText("Unexpected value: " + QString::number(knownState));
      break;
 }
 statusIsEnabledCheckBox->setChecked(light->getEnabled());
 statusIsVariableCheckBox->setChecked(light->isIntensityVariable());
 statusIsTransitionCheckBox->setChecked(light->isTransitionAvailable());
 nowIntensityLabel->setText(oneDigits->format(light->getCurrentIntensity() * 100));
 nowTransitionTimeLabel->setText(oneDotTwoDigits->format(light->getTransitionTime()));
 nowIntensityMinLabel->setText(oneDigits->format(light->getMinIntensity() * 100));
 nowIntensityMaxLabel->setText(oneDigits->format(light->getMaxIntensity() * 100));
 if (flag)
 {
  intensityTextField->setText(oneDigits->format(light->getTargetIntensity() * 100));
  transitionTimeTextField->setText(oneDotTwoDigits->format(light->getTransitionTime()));
  intensityMinTextField->setText(oneDigits->format(light->getMinIntensity() * 100));
  intensityMaxTextField->setText(oneDigits->format(light->getMaxIntensity() * 100));
 }
}

/*public*/ QString SimpleLightCtrlFrame::getClassName()
{
 return "jmri.jmrit.simplelight.ctrl.SimpleLightCtrlFrame";
}
