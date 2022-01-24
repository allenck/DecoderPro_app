#ifndef DEFAULTLIGHTCONTROL_H
#define DEFAULTLIGHTCONTROL_H

#include "lightcontrol.h"

class DefaultLightControl : public QObject, public LightControl
{
  Q_OBJECT
  Q_INTERFACES(LightControl)
 public:
  DefaultLightControl();
  /*public*/ DefaultLightControl(Light* l);
  /*public*/ DefaultLightControl(/*@Nonnull*/ LightControl* lc);
  /*public*/ bool equals(QObject *o);
  /*public*/ int hashCode();
  /*public*/ int getControlType()override;
  /*public*/ void setControlType(int type)override;
  /*public*/ void setControlSensorName(QString sensorName)override;
  /*public*/ int getControlSensorSense()override;
  /*public*/ QString getControlSensorName()override;
  /*public*/ void setControlSensorSense(int sense)override;
  /*public*/ int getFastClockOnHour()override;
  /*public*/ int getFastClockOnMin()override;
  /*public*/ int getFastClockOnCombined()override;
  /*public*/ int getFastClockOffHour()override;
  /*public*/ int getFastClockOffMin()override;
  /*public*/ int getFastClockOffCombined()override;
  /*public*/ void setFastClockControlSchedule(int onHour, int onMin, int offHour, int offMin)override;
  /*public*/ QString getControlTurnoutName()override;
  /*public*/ void setControlTurnout(QString turnoutName)override;
  /*public*/ int getControlTurnoutState()override;
  /*public*/ void setControlTurnoutState(int state)override;
  /*public*/ QString getTimedSensorName()override;
  /*public*/ QString getControlTimedOnSensorName()override;
  /*public*/ void setControlTimedOnSensorName(QString sensorName)override;
  /*public*/ int getTimedOnDuration()override;
  /*public*/ void setTimedOnDuration(int duration)override;
  /*public*/ QString getControlSensor2Name()override;
  /*public*/ void setControlSensor2Name(QString sensorName)override;
  /*public*/ void setParentLight(AbstractLight* l)override;
  /*public*/ QString getDescriptionText(QString lightName)override;
  /*public*/ void activateLightControl() override;
  /*public*/ bool onOffTimesFaulty() override;
  /*public*/ bool areFollowerTimesFaulty( QList<LightControl*> compareList )override;
  /*public*/ void deactivateLightControl() override;

  QObject* self() override {return (QObject*)this;}

 private:
  static Logger* log;
  // instance variables - saved with Light in configuration file
  /*private*/ int _controlType = Light::NO_CONTROL;    // control type
  /*private*/ QString _controlSensorName = "";   // controlling Sensor if SENSOR_CONTROL
  /*private*/ int _fastClockOnHour = 0;         // on Hour if FAST_CLOCK_CONTROL
  /*private*/ int _fastClockOnMin = 0;          // on Minute if FAST_CLOCK_CONTROL
  /*private*/ int _fastClockOffHour = 0;        // off Hour if FAST_CLOCK_CONTROL
  /*private*/ int _fastClockOffMin = 0;         // off Minute if FAST_CLOCK_CONTROL
  /*private*/ QString _controlTurnoutName = "";  // turnout whose status is shown if TURNOUT_STATUS_CONTROL
  /*private*/ int _turnoutState = Turnout::CLOSED;  // turnout state corresponding to this Light ON
  /*private*/ QString _timedSensorName = "";     // trigger Sensor if TIMED_ON_CONTROL
  /*private*/ QString _controlSensor2Name = ""; // second controlling sensor if TWO_SENSOR_CONTROL

  // operational instance variables - not saved between runs
  /*private*/ Light* _parentLight = nullptr;        // Light that is being controlled
  /*private*/ bool _active = false;
  /*private*/ NamedBeanHandle<Sensor*>* _namedControlSensor = nullptr;
  /*private*/ PropertyChangeListener* _sensorListener = nullptr;
  /*private*/ NamedBeanHandle<Sensor*>* _namedControlSensor2 = nullptr;
  /*private*/ PropertyChangeListener* _sensor2Listener = nullptr;
  /*private*/ PropertyChangeListener* _timebaseListener = nullptr;
  /*private*/ Timebase* _clock = nullptr;
  /*private*/ Turnout* _controlTurnout = nullptr;
  /*private*/ PropertyChangeListener* _turnoutListener = nullptr;
  /*private*/ NamedBeanHandle<Sensor*>* _namedTimedControlSensor = nullptr;
  /*private*/ PropertyChangeListener* _timedSensorListener = nullptr;
  /*private*/ QTimer* _timedControlTimer = nullptr;
  /*private*/ ActionListener* _timedControlListener = nullptr;
  /*private*/ int _timeNow;
  /*private*/ PropertyChangeListener* _parentLightListener = nullptr;
  /*private*/ NamedBeanHandleManager* nbhm = (NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager");
  /*private*/ PropertyChangeListener* addTwoSensorListener(Sensor* sensor);
  /*private*/ void addNamedTimedControlListener();
  /*private*/ void oneSensorChanged(int newSensorState);
  /*private*/ void oneTurnoutChanged(int newTurnoutState);
  /*private*/ bool isMasterFastClockFollower();
  /*private*/ bool isFastClockEqual(int time);
  /*private*/ void setTheTime();
  /*private*/ void updateClockControlLightFollower();
  /*private*/ void logTimeChanges(QString onOrOff);


 protected:
  /*protected*/ int _controlSensorSense = Sensor::ACTIVE;  // sense of Sensor for Light ON
  /*protected*/ int _timeOnDuration = 0;          // duration (milliseconds) if TIMED_ON_CONTROL
  /*protected*/ void twoSensorChanged();

  friend class TimeLight;
  friend class TimedSensorListener;
  friend class  DLC_minuteListener;
  friend class LC1PropertyChangeListener;
  friend class LC2PropertyChangeListener;
  friend class LC3PropertyChangeListener;
  friend class LC4PropertyChangeListener;
  friend class LC5PropertyChangeListener;
  friend class LC6PropertyChangeListener;
};
/**
 * Class for defining ActionListener for TIMED_ON_CONTROL
 */
/*private*/ class TimeLight : public QObject, public ActionListener {
    Q_OBJECT
    Q_INTERFACES(ActionListener)
  DefaultLightControl* ctl;
 public:
  TimeLight(DefaultLightControl* ctl){this->ctl = ctl;}
  QObject* self() override{return (QObject*)this;}
 public slots:
  //@Override
    /*public*/ void actionPerformed(JActionEvent* /*event*/) override{
        // Turn Light OFF
       ctl-> _parentLight->setState(Light::OFF);
        // Turn Timer OFF
        if (ctl->_timedControlTimer != nullptr ) {
            ctl->_timedControlTimer->stop();
        }
        ctl->_timedControlTimer = nullptr;
    }
};

//class TimedSensorListener : public PropertyChangeListener
//{
//  Q_OBJECT
//  DefaultLightControl* dlc;
// public:
//  TimedSensorListener(DefaultLightControl* dlc) {this->dlc = dlc;}
// public slots:
//  void PropertyChange(PropertyChangeEvent* e){
//   if (e->getPropertyName() == ("KnownState")
//       && (int) e->getNewValue().toInt() == Sensor::ACTIVE
//       && dlc->_timedControlTimer == nullptr
//       && dlc->_parentLight->getEnabled()) {
//       // Turn light on
//       dlc->_parentLight->setState(Light::ON);
//       // Create a timer if one does not exist
//       dlc->_timedControlListener = new TimeLight(dlc);
////       dlc->_timedControlTimer = new QTimer(dlc->_timeOnDuration,
////           dlc->_timedControlListener);
//       dlc->_timedControlTimer = new QTimer();
//       dlc->_timedControlTimer->setSingleShot(true);
//       // Start the Timer to turn the light OFF
//       connect(dlc->_timedControlTimer, SIGNAL(timeout()), dlc->_timedControlListener, SLOT(timeout()));
//       dlc->_timedControlTimer->start(dlc->_timeOnDuration);
//   }
//  }
//};

class DLC_minuteListener : public QObject, public PropertyChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
  DefaultLightControl* dlc;
 public:
  DLC_minuteListener(DefaultLightControl* dlc) {this->dlc = dlc;}
 public slots:
  void PropertyChange(PropertyChangeEvent* e)
  {
   dlc->updateClockControlLightFollower();
  }
  QObject* self() override {return (QObject*)this;}
};
class LC1PropertyChangeListener : public QObject, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 DefaultLightControl* lc;
 public:
 LC1PropertyChangeListener(DefaultLightControl* lc) {this->lc = lc;}
 QObject* self() override{return (QObject*)this;}

public slots:
 void propertyChange(PropertyChangeEvent*)override{}
};

class LC2PropertyChangeListener : public QObject,public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 DefaultLightControl* lc;
 public:
 LC2PropertyChangeListener(DefaultLightControl* lc) {this->lc = lc;}
 QObject* self() override{return (QObject*)this;}
public slots:
 void propertyChange(PropertyChangeEvent* e) override
 {
  if (e->getPropertyName()==("KnownState"))
  {
   lc->oneSensorChanged( e->getNewValue().toInt() );
  }
 }
};

class LC3PropertyChangeListener : public QObject, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 DefaultLightControl* lc;
 public:
 LC3PropertyChangeListener(DefaultLightControl* lc) {this->lc = lc;}
 QObject* self() override{return (QObject*)this;}
public slots:
 void propertyChange(PropertyChangeEvent* ) override
 {
  lc->updateClockControlLightFollower();
 }
};

class LC4PropertyChangeListener : public QObject, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 DefaultLightControl* lc;
 public:
 LC4PropertyChangeListener(DefaultLightControl* lc) {this->lc = lc;}
 QObject* self() override{return (QObject*)this;}
public slots:
 void propertyChange(PropertyChangeEvent* e) override
 {
     if (e->getPropertyName() == ("KnownState")) {
         lc->oneTurnoutChanged(  e->getNewValue().toInt() );
     }
 }
};

class LC5PropertyChangeListener : public QObject, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 DefaultLightControl* lc;
 public:
 LC5PropertyChangeListener(DefaultLightControl* lc) {this->lc = lc;}
 QObject* self() override{return (QObject*)this;}
public slots:
 void propertyChange(PropertyChangeEvent* e) override{
  if (e->getPropertyName()==("KnownState")) {
      if (e->getNewValue().toInt() == Sensor::ACTIVE) {
          if (lc->_timedControlTimer == nullptr && lc->_parentLight->getEnabled()) {
              // Turn light on
              lc->_parentLight->setState(Light::ON);
              // Create a timer if one does not exist
              lc->_timedControlListener = new TimeLight((DefaultLightControl*)lc);
              lc->_timedControlTimer = new QTimer();
              lc->_timedControlTimer->setInterval(lc->_timeOnDuration);
//                    _timedControlListener);
              connect(lc->_timedControlTimer, SIGNAL(timeout()),lc->_timedControlListener->self(), SLOT(actionPerformed()));
              // Start the Timer to turn the light OFF
              lc->_timedControlTimer->start();
          }
      }
  }
 }
};

class LC6PropertyChangeListener : public QObject, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 DefaultLightControl* lc;
 public:
 LC6PropertyChangeListener(DefaultLightControl* lc) {this->lc = lc;}
 QObject* self() override{return (QObject*)this;}
public slots:
 void propertyChange(PropertyChangeEvent*)override {
  lc->twoSensorChanged();
 }
};
#endif // DEFAULTLIGHTCONTROL_H
