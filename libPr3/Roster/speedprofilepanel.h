#ifndef SPEEDPROFILEPANEL_H
#define SPEEDPROFILEPANEL_H

#include "jmripanel.h"
#include "propertychangelistener.h"
#include <QComboBox>
#include <QMap>

class LayoutBlock;
class QElapsedTimer;
class Sensor;
class PropertyChangeListener;
class DccLocoAddress;
class Logger;
class RosterSpeedProfile;
class SensorDetails;
class RosterEntry;
class DccThrottle;
class QLabel;
class RosterEntryComboBox;
class BeanSelectCreatePanel;
class JTextField;
class QPushButton;
class BlockSensorComboBox : public QComboBox
{
 Q_OBJECT
 QMap<QString, LayoutBlock*> sensorMap;

public:
 BlockSensorComboBox(QWidget* parent = 0);
 Sensor* getNamedBean();
 LayoutBlock* getBlock();
};
class SpeedProfilePanel : public JmriPanel
{
 Q_OBJECT
public:
 explicit SpeedProfilePanel(QWidget *parent = 0);

signals:

public slots:
 void on_profileButton_clicked();
 void on_cancelButton_clicked();
 void on_testButton_clicked();
 /*public*/ void notifyThrottleFound(DccThrottle* _throttle);
 /*public*/ void notifyFailedThrottleRequest(DccLocoAddress* address, QString reason);
 void on_stopTimer_timeout();
 /*public*/ void releaseAddress();
 /*public*/ void notifyThrottleDisposed();
 /*public*/ void propertyChange(PropertyChangeEvent* evt);


private:
 QPushButton* profileButton;// = new QPushButton(tr("ButtonProfile"));
 QPushButton* cancelButton;// = new QPushButton(tr("ButtonCancel"));
 QPushButton* testButton;// = new QPushButton(tr("ButtonTest"));
 JTextField* lengthField;// = new JTextField(10);
 JTextField* speedStepFrom;// = new JTextField(10);

 // Start or finish sensor
 //BeanSelectCreatePanel* sensorAPanel;// = new BeanSelectCreatePanel(InstanceManager::sensorManagerInstance(), NULL);
 BlockSensorComboBox* sensorAPanel;

 // Finish or start sensor
 //BeanSelectCreatePanel* sensorBPanel;// = new BeanSelectCreatePanel(InstanceManager.sensorManagerInstance(), NULL);
 BlockSensorComboBox* sensorBPanel;

 // Block sensor
 //BeanSelectCreatePanel* blockCPanel;// = new BeanSelectCreatePanel(InstanceManager.blockManagerInstance(), NULL);
 //BeanSelectCreatePanel* sensorCPanel;// = new BeanSelectCreatePanel(InstanceManager.sensorManagerInstance(), NULL);
 BlockSensorComboBox* sensorCPanel;

 RosterEntryComboBox* reBox;// = new RosterEntryComboBox();
 bool profile;// = false;
 bool test;// = false;

 QLabel* sourceLabel;// = new QLabel();
 SensorDetails* sensorA;
 SensorDetails* sensorB;
 RosterEntry* re;
 DccThrottle* t;
 int finishSpeedStep;
 RosterSpeedProfile* rosterSpeedProfile;
 void setupProfile();
 Logger* log;
 QTimer* overRunTimer;// = NULL;
 void setButtonStates(bool state);
 PropertyChangeListener* startListener;// = NULL;
 PropertyChangeListener* finishListener;// = NULL;
 PropertyChangeListener* middleListener;// = NULL;

 Sensor* startSensor;
 Sensor* finishSensor;
 SensorDetails* middleBlockSensor;
 bool isForward;// = true;
 /*static*/ class SpeedStep
 {
  float forward;// = 0.0;
  float reverse;// = 0.0;
public:
  SpeedStep()
  {
   forward = 0.0;
   reverse = 0.0;
  }

  void setForwardSpeed(float speed) {
      forward = speed;
  }

  void setReverseSpeed(float speed) {
      reverse = speed;
  }

  float getForwardSpeed() {
      return forward;
  }

  float getReverseSpeed() {
      return reverse;
  }
 };
 QMap<int, SpeedStep*> speeds;// = new TreeMap<Integer, SpeedStep>();
// long startTime;
 QElapsedTimer* durationTimer;
// long finishTime;
 qint64 timerDuration;

 QList<double> forwardOverRuns;// = new ArrayList<Double>();
 QList<double> reverseOverRuns;// = new ArrayList<Double>();
 bool stepCalculated;// = false;
 void startTiming();
 void stopCurrentSpeedStep();
 void stopLoco();
 void calculateSpeed();
 void updateSpeedProfileWithResults();
 void stopTrainTest();
 QWidget* update;


private slots:
 void startProfile();

protected:
 /*protected*/ int profileStep;// = 1;
 /*protected*/ float profileSpeed;
 /*protected*/ float profileIncrement;
friend class FinishListener;
friend class StartListenerA;
friend class StartListenerB;
};
/*static*/ class SensorDetails : public QObject
{
 Q_OBJECT

    Sensor* sensor;// = NULL;
    long inactiveDelay;// = 0;
    long activeDelay;// = 0;
    bool usingGlobal;// = false;
public:
    SensorDetails(Sensor* sen);
    void setupSensor();
    void resetDetails() ;
    Sensor* getSensor();

};
class StartListenerA : public PropertyChangeListener
{
 Q_OBJECT
 SpeedProfilePanel* panel;

public:
 StartListenerA(SpeedProfilePanel* panel);
public slots:
 void propertyChange(PropertyChangeEvent *e);

};
class StartListenerB : public PropertyChangeListener
{
 Q_OBJECT
 SpeedProfilePanel* panel;

public:
 StartListenerB(SpeedProfilePanel* panel);
public slots:
 void propertyChange(PropertyChangeEvent *e);

};
class FinishListener : public PropertyChangeListener
{
 Q_OBJECT
 SpeedProfilePanel* panel;

public:
 FinishListener(SpeedProfilePanel* panel);
public slots:
 void propertyChange(PropertyChangeEvent *e);

};

#endif // SPEEDPROFILEPANEL_H
