#include "speedprofilepanel.h"
#include <QPushButton>
#include <QLabel>
#include "jtextfield.h"
#include "beanselectcreatepanel.h"
#include "rosterentrycombobox.h"
#include "instancemanager.h"
#include <QBoxLayout>
#include "dccthrottle.h"
#include "rosterentry.h"
#include <QMessageBox>
#include "sensor.h"
#include "logger.h"
#include "rosterspeedprofile.h"
#include "speedprofilepanel.h"
#include <QElapsedTimer>
#include "abstractthrottle.h"
#include "layoutblockmanager.h"
#include "systemnamecomparator.h"
#include "proxysensormanager.h"

//SpeedProfilePanel::SpeedProfilePanel(QWidget *parent) :
//  JmriPanel(parent)
//{
//}
/**
 * Set up and run automated speed table calibration.
 * <p>
 * Uses three sensors in a row:
 * <ul>
 * <li>Start sensor: Track where locomotive starts
 * <li>Block sensor: Middle track. This time through this is used to measure the
 * speed.
 * <li>Finish sensor: Track where locomotive stops before repeating.
 * </ul>
 * The expected sequence is:
 * <ul>
 * <li>Start moving with start sensor on, others off.
 * <li>Block (middle) sensor goes active: startListener calls startTiming
 * <li>Finish sensor goes active: finishListener calls stopCurrentSpeedStep
 * <li>Block (middle) sensor goes inactive: startListener calls stopLoco, which
 * stops loco after 2.5 seconds
 * </ul>
 * After a forward run, the start and finish sensors are swapped for a run in
 * reverse.
 */
//class SpeedProfilePanel extends jmri.util.swing.JmriPanel implements ThrottleListener {

//private static final long serialVersionUID = -7592615396122420235L;

/*public*/ SpeedProfilePanel::SpeedProfilePanel(QWidget *parent) :
                               JmriPanel(parent)
{
 profileButton = new QPushButton(tr("Profile"));
 cancelButton = new QPushButton(tr("Cancel"));
 testButton = new QPushButton(tr("Test"));
 lengthField = new JTextField(10);
 lengthField->setValidator(new QIntValidator());
 speedStepFrom = new JTextField(10);
 speedStepFrom->setValidator(new QIntValidator(1,126));
 sensorA = NULL;
 sensorB = NULL;
 middleBlockSensor = NULL;
 t = NULL;

 // Start or finish sensor
 //sensorAPanel = new BeanSelectCreatePanel(InstanceManager::sensorManagerInstance(), NULL);
 sensorAPanel = new BlockSensorComboBox();

 // Finish or start sensor
 //sensorBPanel = new BeanSelectCreatePanel(InstanceManager::sensorManagerInstance(), NULL);
 sensorBPanel = new BlockSensorComboBox();

 // Block sensor
 //blockCPanel = new BeanSelectCreatePanel(InstanceManager::blockManagerInstance(), NULL);
 //sensorCPanel = new BeanSelectCreatePanel(InstanceManager::sensorManagerInstance(), NULL);
 sensorCPanel = new BlockSensorComboBox();

 reBox = new RosterEntryComboBox();
 profile = false;
 test = false;
 profileStep = 1;
 log = new Logger("SpeedProfilePanel");
 overRunTimer = NULL;
 startListener = NULL;
 finishListener = NULL;
 middleListener = NULL;
 isForward = true;
 forwardOverRuns =  QList<double>();
 reverseOverRuns =  QList<double>();
 stepCalculated = false;
 speeds = QMap<int, SpeedStep*>();
 durationTimer = new QElapsedTimer;
 finishSpeedStep = 126;

 sourceLabel = new QLabel();
 QVBoxLayout* layout;
 setLayout(layout = new /*BorderLayout()*/QVBoxLayout);
 QWidget* main = new QWidget();
 QGridLayout* mainLayout;
 main->setLayout(mainLayout = new /*GridLayout(0, 2)*/QGridLayout);

 mainLayout->addWidget(new QLabel(tr("Length Of Block (mm)")),0,0);
 mainLayout->addWidget(lengthField,0,1);
 lengthField->setText("0");
 mainLayout->addWidget(new QLabel(tr("Start Sensor")),1,0);
 mainLayout->addWidget(sensorAPanel,1,1);
 mainLayout->addWidget(new QLabel(tr("Block Sensor")),2,0); //was optional
 mainLayout->addWidget(sensorCPanel,2,1);
 //mainLayout->addWidget(blockCPanel);
 mainLayout->addWidget(new QLabel(tr("Finish Sensor")),3,0);
 mainLayout->addWidget(sensorBPanel,3,1);

 //mainLayout->addWidget(new QLabel("Speed Steps"));
 //speedStepsCombo = new JComboBox(InstanceManager::throttleManagerInstance()
 mainLayout->addWidget(new QLabel(tr("Roster Entry")),4,0);
 mainLayout->addWidget(reBox,4,1);
 mainLayout->addWidget(new QLabel(""),5,0);
 mainLayout->addWidget(new QLabel(""),5,1);
 mainLayout->addWidget(cancelButton,6,0);

 mainLayout->addWidget(profileButton,6,1);

 mainLayout->addWidget(speedStepFrom,7,0);
 mainLayout->addWidget(testButton,7,1);

 //add(main, BorderLayout.CENTER);
 layout->addWidget(main,0, Qt::AlignVCenter);

 QWidget* panel1 = new QWidget();
 QVBoxLayout* panel1Layout;
 panel1->setLayout(panel1Layout = new /*BorderLayout()*/QVBoxLayout);
 sourceLabel = new QLabel("   ");
 panel1Layout->addWidget(sourceLabel, /*BorderLayout.SOUTH*/0, Qt::AlignBottom);

 layout->addWidget(panel1, /*BorderLayout.SOUTH*/0, Qt::AlignBottom);

// profileButton.addActionListener(
//         new ActionListener() {
//             /*public*/ void actionPerformed(ActionEvent e) {
//                 profile = true;
//                 setupProfile();
//             }
//         });
 connect(profileButton, SIGNAL(clicked()), this, SLOT(on_profileButton_clicked()));
// cancelButton.addActionListener(
//         new ActionListener() {
//             /*public*/ void actionPerformed(ActionEvent e) {
//                 cancelButton();
//             }
//         });
 connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_cancelButton_clicked()));
// testButton.addActionListener(
//         new ActionListener() {
//             /*public*/ void actionPerformed(ActionEvent e) {
//                 test = true;
//                 testButton();
//             }
//         });
 connect(testButton, SIGNAL(clicked()), this, SLOT(on_testButton_clicked()));
 setButtonStates(true);
}

void SpeedProfilePanel::setupProfile()
{
 lengthField->text().toInt();
 setButtonStates(false);
 if (sensorA == NULL)
 {
//        try {
  sensorA = new SensorDetails((Sensor*) sensorAPanel->getNamedBean());
//        } catch (Exception e) {
  if(sensorA == NULL)
  {
   //JOptionPane.showMessageDialog(NULL, tr("ErrorSensorNotFound", "Start"));
   QMessageBox::critical(NULL, tr("Error"), tr("No %1 Sensor found").arg(tr("Start")));
   setButtonStates(true);
   return;
  }
 }
 else
 {
  Sensor* tmpSen = NULL;
//        try {
  tmpSen = (Sensor*) sensorAPanel->getNamedBean();
//        } catch (Exception e) {
  if(tmpSen == NULL)
  {
//            JOptionPane.showMessageDialog(NULL, tr("ErrorSensorNotFound", "Start"));
   QMessageBox::critical(NULL, tr("Error"), tr("No %1 Sensor found").arg(tr("Start")));
   setButtonStates(true);
   return;
  }
  if (tmpSen != sensorA->getSensor())
  {
   sensorA->resetDetails();
   sensorA = new SensorDetails(tmpSen);
  }
 }
 if (sensorB == NULL)
 {
//        try {
  sensorB = new SensorDetails((Sensor*) sensorBPanel->getNamedBean());
//        } catch (Exception e) {
  if(sensorB == NULL)
  {
//            JOptionPane.showMessageDialog(NULL, tr("ErrorSensorNotFound", "Finish"));
   QMessageBox::critical(NULL, tr("Error"), tr("No %1 Sensor found").arg(tr("Finish")));
   setButtonStates(true);
   return;
  }
 }
 else
 {
  Sensor* tmpSen = NULL;
//        try {
  tmpSen = (Sensor*) sensorBPanel->getNamedBean();
//        } catch (Exception e) {
  if(tmpSen == NULL)
  {
            //JOptionPane.showMessageDialog(NULL, tr("ErrorSensorNotFound", "Finish"));
   QMessageBox::critical(NULL, tr("Error"), tr("No %1 Sensor found").arg(tr("Finish")));
   setButtonStates(true);
   return;
  }
  if (tmpSen != sensorB->getSensor())
  {
   sensorB->resetDetails();
   sensorB = new SensorDetails(tmpSen);
  }
 }
 if (middleBlockSensor == NULL)
 {
//        try {
  middleBlockSensor = new SensorDetails((Sensor*) sensorCPanel->getNamedBean());
//        } catch (Exception e) {
  if(middleBlockSensor == NULL)
  {
//            JOptionPane.showMessageDialog(NULL, tr("ErrorSensorNotFound", "Block"));
   QMessageBox::critical(NULL, tr("Error"), tr("No %1 Sensor found").arg(tr("Block")));
   setButtonStates(true);
   return;
  }
 }
 else
 {
  Sensor* tmpSen = NULL;
//        try {
  tmpSen = (Sensor*) sensorCPanel->getNamedBean();
//        } catch (Exception e) {
  if(tmpSen == NULL)
  {
//            JOptionPane.showMessageDialog(NULL, tr("ErrorSensorNotFound", "Block"));
   QMessageBox::critical(NULL, tr("Error"), tr("No %1 Sensor found").arg(tr("Block")));
   setButtonStates(true);
   return;
  }
  if (tmpSen != middleBlockSensor->getSensor())
  {
   middleBlockSensor->resetDetails();
   middleBlockSensor = new SensorDetails(tmpSen);
  }
 }
 if (reBox->getSelectedRosterEntries()->length() == 0)
 {
//        JOptionPane.showMessageDialog(NULL, tr("ErrorNoRosterSelected"));
  QMessageBox::critical(NULL, tr("Error"), tr("No Roster Entry Selected"));
  log->warn("No roster Entry selected.");
  setButtonStates(true);
  return;
 }
 if(t != NULL)
 {
  t->dispose((ThrottleListener*)this);
  t = NULL;
 }
 re = reBox->getSelectedRosterEntries()->at(0);
 bool ok = InstanceManager::throttleManagerInstance()->requestThrottle(re, (ThrottleListener*)this);
 if (!ok)
 {
  log->warn("Throttle for locomotive " + re->getId() + " could not be setup.");
  setButtonStates(true);
  return;
 }
}


/*public*/ void SpeedProfilePanel::notifyThrottleFound(DccThrottle* _throttle)
{
 t = _throttle;
 if (t == NULL)
 {
//        JOptionPane.showMessageDialog(NULL, tr("ErrorThrottleNotFound"));
  QMessageBox::critical(NULL, tr("Error"), tr("Unable to find throttle"));
  log->warn("NULL throttle returned for train  " + re->getId() + " during automatic initialization.");
  setButtonStates(true);
  return;
 }
 if (log->isDebugEnabled())
 {
  log->debug("throttle address= " + t->getLocoAddress()->getNumber());
 }
 AbstractThrottle* at = (AbstractThrottle*)t;
 connect(at, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

 int speedStepMode = t->getSpeedStepMode();
 profileIncrement = t->getSpeedIncrement();
 if (speedStepMode == DccThrottle::SpeedStepMode14)
 {
  finishSpeedStep = 14;
 } else if (speedStepMode == DccThrottle::SpeedStepMode27) {
  finishSpeedStep = 27;
 } else if (speedStepMode == DccThrottle::SpeedStepMode28) {
  finishSpeedStep = 28;
 } else {// default to 128 speed step mode
  finishSpeedStep = 126;
 }
 speedStepFrom->setValidator(new QIntValidator(1, finishSpeedStep));

 log->debug("Speed step mode " + QString::number(speedStepMode));
 profileStep = 1;
 profileSpeed = profileIncrement;

 if (profile)
 {
  startSensor = middleBlockSensor->getSensor();
  finishSensor = sensorB->getSensor();
//  startListener = new PropertyChangeListener()
//  {
//      /*public*/ void propertyChange(PropertyChangeEvent e) {
//          if (e.getPropertyName()==("KnownState")) {
//              if (((Integer) e.getNewValue()) == Sensor.ACTIVE) {
//                  startTiming();
//              }
//              if (((Integer) e.getNewValue()) == Sensor.INACTIVE) {
//                  stopLoco();
//              }
//          }
//      }
//  };
  startListener = new StartListenerA(this);

//  finishListener = new PropertyChangeListener() {
//      /*public*/ void propertyChange(PropertyChangeEvent e) {
//          if (e.getPropertyName()==("KnownState")) {
//              if (((Integer) e.getNewValue()) == Sensor.ACTIVE)   {
//                  stopCurrentSpeedStep();
//              }
//          }
//      }
//  };
  finishListener = new FinishListener(this);
  isForward = true;
  startProfile();
 }
 else
 {
  if (re->getSpeedProfile() == NULL)
  {
   log->error("Loco has no speed profile");
//   JOptionPane.showMessageDialog(NULL, tr("ErrorNoSpeedProfile"));
   QMessageBox::critical(NULL, tr("Error"), tr("Selected Roster Entry has no speed profile"));
   setButtonStates(true);
   return;
  }
  startSensor = middleBlockSensor->getSensor();
//  startListener = new PropertyChangeListener() {
//      /*public*/ void propertyChange(PropertyChangeEvent e) {
//          if (e.getPropertyName()==("KnownState")) {
//              if (((Integer) e.getNewValue()) == Sensor.ACTIVE) {
//                  stopTrainTest();
//              }
//          }
//      }
//  };
  startListener = new StartListenerB(this);
  //startSensor.addPropertyChangeListener(startListener);
  connect(startSensor, SIGNAL(propertyChange(PropertyChangeEvent*)), startListener, SLOT(propertyChange(PropertyChangeEvent*)));
  int startstep = speedStepFrom->text().toInt();
  Q_ASSERT(startstep > 0 && startstep <= 126);
  isForward = true;
  t->setIsForward(isForward);
  profileSpeed = profileIncrement * startstep;
  t->setSpeedSetting(profileSpeed);
 }
}

StartListenerA::StartListenerA(SpeedProfilePanel *panel)
{
 this->panel = panel;
}

void StartListenerA::propertyChange(PropertyChangeEvent *e)
{
 if (e->getPropertyName()==("KnownState"))
 {
  if (( e->getNewValue().toInt()) == Sensor::ACTIVE)
  {
   panel->startTiming();
  }
  if ((e->getNewValue().toInt()) == Sensor::INACTIVE)
  {
   panel->stopLoco();
  }
 }
}
FinishListener::FinishListener(SpeedProfilePanel *panel)
{
 this->panel = panel;
}
void FinishListener::propertyChange(PropertyChangeEvent *e)
{
 if (e->getPropertyName()==("KnownState"))
 {
  if (( e->getNewValue().toInt()) == Sensor::ACTIVE)
  {
   panel->stopCurrentSpeedStep();
  }
 }
}
StartListenerB::StartListenerB(SpeedProfilePanel *panel)
{
 this->panel = panel;
}
void  StartListenerB::propertyChange(PropertyChangeEvent *e)
{
 if (e->getPropertyName()==("KnownState"))
 {
  if (( e->getNewValue().toInt()) == Sensor::ACTIVE)
  {
   panel->stopTrainTest();
  }
 }
}

void SpeedProfilePanel::setButtonStates(bool state)
{
 cancelButton->setEnabled(!state);
 profileButton->setEnabled(state);
 testButton->setEnabled(state);
 if (state)
 {
  sourceLabel->setText("   ");
  profile = false;
  test = false;
 }
 if (sensorA != NULL)
 {
  sensorA->resetDetails();
 }
 if (sensorB != NULL)
 {
  sensorB->resetDetails();
 }
 if (middleBlockSensor != NULL)
 {
  middleBlockSensor->resetDetails();
 }
 sensorAPanel->setEnabled(state);
 sensorBPanel->setEnabled(state);
 sensorCPanel->setEnabled(state);
 reBox->setEnabled(state);
}

/*public*/ void SpeedProfilePanel::notifyFailedThrottleRequest(DccLocoAddress* address, QString reason)
{
//    JOptionPane.showMessageDialog(NULL, tr("ErrorFailThrottleRequest"));
 QMessageBox::critical(NULL, tr("Error"), tr("Unable to get a throttle for the loco"));
 log->error(tr("Throttle request failed for ") + address->toString() + " because " + reason);
 setButtonStates(true);
}


void SpeedProfilePanel::startProfile()
{
 stepCalculated = false;
 sourceLabel->setText(tr("Setting up for next run.."));
 if (isForward)
 {
  finishSensor = sensorB->getSensor();
 }
 else
 {
  finishSensor = sensorA->getSensor();
 }
 startSensor = middleBlockSensor->getSensor();
 //startSensor.addPropertyChangeListener(startListener);
 connect(startSensor, SIGNAL(propertyChange(PropertyChangeEvent*)), startListener, SLOT(propertyChange(PropertyChangeEvent*)));

 //finishSensor.addPropertyChangeListener(finishListener);
 connect(finishSensor, SIGNAL(propertyChange(PropertyChangeEvent*)), finishListener, SLOT(propertyChange(PropertyChangeEvent*)));
 t->setIsForward(isForward);
 log->debug("Set speed to " + QString::number(profileSpeed) + " isForward " + (isForward?"yes":"no"));
 t->setSpeedSetting(profileSpeed);
 sourceLabel->setText(tr("Waiting for the block sensor to go Active.."));
}


void SpeedProfilePanel::startTiming()
{
 //startTime = /*System.nanoTime();*/
 durationTimer->start();
 sourceLabel->setText(tr("Profiling Step %1 %2 of %3").arg( (isForward ? "(forward) " : "(reverse) ")).arg(profileStep).arg( finishSpeedStep));
}


void SpeedProfilePanel::stopCurrentSpeedStep()
{
 //finishTime = System.nanoTime();
 timerDuration = durationTimer->nsecsElapsed();
 stepCalculated = true;
 //finishSensor.removePropertyChangeListener(finishListener);
 disconnect(finishSensor, SIGNAL(propertyChange(PropertyChangeEvent*)), finishListener, SLOT(propertyChange(PropertyChangeEvent*)));
 sourceLabel->setText(tr("Calculating Speed"));
 if (profileStep >= 4)
 {
  t->setSpeedSetting(profileSpeed / 2);
 }
 calculateSpeed();
 sourceLabel->setText(tr("Waiting for loco to clear Block Sensor"));
}

void SpeedProfilePanel::stopLoco()
{
 if (!stepCalculated) {
     return;
 }

 //startSensor.removePropertyChangeListener(startListener);
 disconnect(startSensor, SIGNAL(propertyChange(PropertyChangeEvent*)), startListener, SLOT(propertyChange(PropertyChangeEvent*)));
 //finishSensor.removePropertyChangeListener(finishListener);
 disconnect(finishSensor, SIGNAL(propertyChange(PropertyChangeEvent*)), finishListener, SLOT(propertyChange(PropertyChangeEvent*)));

 isForward = !isForward;
 if (isForward)
 {
  profileSpeed = profileIncrement + profileSpeed;
  profileStep++;
 }

 if (profileStep > finishSpeedStep)
 {
  updateSpeedProfileWithResults();
  setButtonStates(true);
  re->updateFile();
  Roster::writeRosterFile();
  t->setSpeedSetting(0.0);
  return;
 }
 // Loco may have been brought to half-speed in stopCurrentSpeedStep, so wait for that to take effect then stop & restart
 QTimer* stopTimer = new QTimer();// 2500, new java.awt.event.ActionListener() {
 stopTimer->setInterval(2500);
 connect(stopTimer, SIGNAL(timeout()), this, SLOT(on_stopTimer_timeout()));
//     /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {

//         // finally command the stop
//         t.setSpeedSetting(0.0f);

//         // and a second later, restart going the other way
//         javax.swing.Timer restartTimer = new javax.swing.Timer(1000, new java.awt.event.ActionListener() {
//             /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                 startProfile();
//             }
//         });
//         restartTimer.setRepeats(false);
//         restartTimer.start();
//     }
// });
 stopTimer->setSingleShot(true);
 stopTimer->start();
}
void SpeedProfilePanel::on_stopTimer_timeout()
{
 // finally command the stop
 t->setSpeedSetting(0.0);

 // and a second later, restart going the other way
 QTimer* restartTimer = new QTimer; //(1000, new java.awt.event.ActionListener() {
 restartTimer->setInterval(2500);
//     /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//         startProfile();
//     }
// });
 connect(restartTimer, SIGNAL(timeout()), this, SLOT(startProfile()));
 restartTimer->setSingleShot(true);
 restartTimer->start();
}

void SpeedProfilePanel::calculateSpeed()
{
 float duration = (((float) (/*finishTime - startTime*/timerDuration)) / 1000000000); //Now in seconds
 duration = duration - 2.0;  // Abratory time to add in feedback delay
 float length = (lengthField->text().toInt()); //left as mm
 float speed = length / duration;
 if (log->isDebugEnabled()) {
     log->debug("Step:" + QString::number(profileStep) + " duration:" + QString::number(duration) + " length:" + QString::number(length) + " speed:" + QString::number(speed));
 }

 int iSpeedStep = qRound(profileSpeed * 1000);
 if (!speeds.contains(iSpeedStep)) {
     speeds.insert(iSpeedStep, new SpeedStep());
 }
 SpeedStep* ss = speeds.value(iSpeedStep);

 if (isForward) {
     ss->setForwardSpeed(speed);
 } else {
     ss->setReverseSpeed(speed);
 }
}

void SpeedProfilePanel::updateSpeedProfileWithResults()
{
 RosterSpeedProfile* rosterSpeedProfile = re->getSpeedProfile();
 if (rosterSpeedProfile == NULL) {
     rosterSpeedProfile = new RosterSpeedProfile(re);
     re->setSpeedProfile(rosterSpeedProfile);
 } else {
     rosterSpeedProfile->clearCurrentProfile();
 }
 foreach (int i, speeds.keys()) {
     rosterSpeedProfile->setSpeed(i, speeds.value(i)->getForwardSpeed(), speeds.value(i)->getReverseSpeed());
 }
}

void SpeedProfilePanel::on_cancelButton_clicked()
{
 if (t != NULL) {
     t->setSpeedSetting(0.0);
 }
 if (startSensor != NULL)
 {
  //startSensor.removePropertyChangeListener(startListener);
  disconnect(startSensor, SIGNAL(propertyChange(PropertyChangeEvent*)), startListener, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 if (finishSensor != NULL)
 {
  //finishSensor.removePropertyChangeListener(finishListener);
  disconnect(finishSensor, SIGNAL(propertyChange(PropertyChangeEvent*)), finishListener, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 if (middleListener != NULL)
 {
  //middleBlockSensor->getSensor().removePropertyChangeListener(middleListener);
  disconnect(middleBlockSensor->getSensor(), SIGNAL(propertyChange(PropertyChangeEvent*)), middleListener, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 setButtonStates(true);

 releaseAddress();
}

void SpeedProfilePanel::on_testButton_clicked()
{
 //Should also test that the step is no greater than those available on the throttle.
 //try {
 bool bOk;
 int s =speedStepFrom->text().toInt(&bOk);
// } catch (Exception e) {
 if(!bOk || s == 0 || s > finishSpeedStep )
 {
     //JOptionPane.showMessageDialog(NULL, tr("ErrorSpeedStep"));
  QMessageBox::critical(NULL, tr("Error"), tr("Speed step from must be a number between 1 and %1").arg(finishSpeedStep));
  return;
 }
 profile = false;
 setupProfile();
}

void SpeedProfilePanel::on_profileButton_clicked()
{
 profile = true;
 setupProfile();
}

void SpeedProfilePanel::stopTrainTest()
{
    int sectionlength = lengthField->text().toInt();
    re->getSpeedProfile()->changeLocoSpeed(t, sectionlength, 0.0f);
    setButtonStates(true);
    //startSensor->removePropertyChangeListener(startListener);
    disconnect(startSensor, SIGNAL(propertyChange(PropertyChangeEvent*)), startListener, SLOT(propertyChange(PropertyChangeEvent*)));
}



//static class SensorDetails {

//    Sensor sensor = NULL;
//    long inactiveDelay = 0;
//    long activeDelay = 0;
//    bool usingGlobal = false;

    SensorDetails::SensorDetails(Sensor* sen)
    {
     sensor = NULL;
     inactiveDelay = 0;
     activeDelay = 0;
     usingGlobal = false;

     sensor = sen;
     usingGlobal = sen->useDefaultTimerSettings();
     activeDelay = sen->getSensorDebounceGoingActiveTimer();
     inactiveDelay = sen->getSensorDebounceGoingInActiveTimer();
    }

    void SensorDetails::setupSensor()
    {
     sensor->useDefaultTimerSettings(false);
     sensor->setSensorDebounceGoingActiveTimer(0);
     sensor->setSensorDebounceGoingInActiveTimer(0);
    }

    void SensorDetails::resetDetails()
    {
     sensor->useDefaultTimerSettings(usingGlobal);
     sensor->setSensorDebounceGoingActiveTimer(activeDelay);
     sensor->setSensorDebounceGoingInActiveTimer(inactiveDelay);
    }

    Sensor*  SensorDetails::getSensor() {
        return sensor;
    }

//}

/**
 * Release the current address.
 */
/*public*/ void SpeedProfilePanel::releaseAddress()
    {
    InstanceManager::throttleManagerInstance()->releaseThrottle(t, (ThrottleListener*)this);
//    if (consistThrottle != NULL) {
//        InstanceManager::throttleManagerInstance()->releaseThrottle(consistThrottle, (ThrottleListener*)this);
//        consistThrottle = NULL;
//    }
    notifyThrottleDisposed();
}

/**
 * Receive notification that an address has been release or dispatched.
 */
/*public*/ void SpeedProfilePanel::notifyThrottleDisposed()
{
 log->debug("notifyThrottleDisposed");
 if (t != NULL)
 {
  t->removePropertyChangeListener((PropertyChangeListener*)this);
  AbstractThrottle* at = (AbstractThrottle*)t;
  disconnect(at, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 t = NULL;
 re = NULL;
}

/*public*/ void SpeedProfilePanel::propertyChange(PropertyChangeEvent* evt)
{
 if ("ThrottleConnected" == (evt->getPropertyName()))
 {
  if ((evt->getOldValue().toBool()) && (!evt->getNewValue().toBool()))
  {
   log->debug("propertyChange: ThrottleConnected to false");
   notifyThrottleDisposed();
  }
 }
}
BlockSensorComboBox::BlockSensorComboBox(QWidget* parent) : QComboBox(parent)
{
 LayoutBlockManager* mgr = (LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager");
 QStringList list = mgr->getSystemNameList();
 addItem("");
 foreach (QString s, list)
 {
  LayoutBlock* block = mgr->getBySystemName(s);
  if(block->occupancySensorName != "")
   sensorMap.insert(block->getOccupancySensor()->getSystemName(), block);
 }
 QStringList keyList = sensorMap.keys();
 qSort(keyList.begin(), keyList.end(), SystemNameComparator::compare);
 addItems(keyList);
}
Sensor* BlockSensorComboBox::getNamedBean()
{
 return ((ProxySensorManager*) InstanceManager::sensorManagerInstance())->getBySystemName(this->currentText());
}
LayoutBlock* BlockSensorComboBox::getBlock()
{
 return sensorMap.value(currentText());
}
