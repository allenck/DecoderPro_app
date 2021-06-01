#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H

#include <QObject>
#include "light.h"
#include "instancemanager.h"
#include "namedbean.h"
#include "namedbeanhandlemanager.h"
#include "namedbeanhandle.h"
#include "actionlistener.h"
#include <QTimer>
#include "predicate.h"
#include "propertychangelistener.h"

class Timebase;
class Light;
class LIBPR3SHARED_EXPORT LightControl : public QObject
{
    Q_OBJECT
public:
    explicit LightControl(QObject *parent = 0);
    LightControl(Light *l, QObject *parent = 0);
    Q_INVOKABLE /*public*/ bool equals(QObject* o);

    /**
     * Accessor methods
     */
    virtual /*public*/ int getControlType();
    virtual /*public*/ int hashCode();
    virtual /*public*/ void setControlType(int type);
    virtual /*public*/ void setControlSensorName(QString sensorName);
    virtual /*public*/ int getControlSensorSense() ;
    virtual /*public*/ QString getControlSensorName();
    virtual /*public*/ void setControlSensorSense(int sense);
    virtual /*public*/ int getFastClockOnHour();
    virtual /*public*/ int getFastClockOnMin();
    virtual /*public*/ int getFastClockOffHour();
    virtual /*public*/ int getFastClockOffMin();
    virtual /*public*/ void setFastClockControlSchedule(int onHour,int onMin,int offHour, int offMin);
    virtual /*public*/ QString getControlTurnoutName();
    virtual /*public*/ void setControlTurnout(QString turnoutName);
    virtual /*public*/ int getControlTurnoutState();
    virtual /*public*/ void setControlTurnoutState(int state);
    virtual /*public*/ QString getTimedSensorName() {return QString();}
    virtual /*public*/ QString getControlTimedOnSensorName();
    virtual /*public*/ void setControlTimedOnSensorName(QString sensorName);
    virtual /*public*/ int getTimedOnDuration();
    virtual /*public*/ void setTimedOnDuration(int duration);
    virtual /*public*/ QString getControlSensor2Name();
    virtual /*public*/ void setControlSensor2Name(QString sensorName);
    virtual /*public*/ void setParentLight(Light* l);
    /**
     * Activates a Light Control by control type.  This method tests the
     *   control type, and set up a control mechanism, appropriate
     *   for the control type.
     */
    virtual /*public*/ void activateLightControl();
    /**
     * Deactivates a LightControl by control type.  This method tests the
     *   control type, and deactivates the control mechanism, appropriate
     *   for the control type.
     */
    virtual/*public*/ void deactivateLightControl();
    virtual /*public*/ bool onOffTimesFaulty();
    virtual /*public*/ bool areFollowerTimesFaulty( QList<LightControl*> compareList );
    virtual /*public*/ QString getDescriptionText(QString lightName);


signals:
    
public slots:
private:
    // instance variables - saved with Light in configuration file
    int _controlType;    // control type
    QString _controlSensorName;   // controlling Sensor if SENSOR_CONTROL
    int _fastClockOnHour;         // on Hour if FAST_CLOCK_CONTROL
    int _fastClockOnMin;          // on Minute if FAST_CLOCK_CONTROL
    int _fastClockOffHour;        // off Hour if FAST_CLOCK_CONTROL
    int _fastClockOffMin;         // off Minute if FAST_CLOCK_CONTROL
    QString _controlTurnoutName;  // turnout whose status is shown if TURNOUT_STATUS_CONTROL
    int _turnoutState;  // turnout state corresponding to this Light ON
    QString _timedSensorName;     // trigger Sensor if TIMED_ON_CONTROL
    QString _controlSensor2Name; // second controlling sensor if TWO_SENSOR_CONTROL
    // operational instance variables - not saved between runs
    /*private*/ Light* _parentLight = nullptr;        // Light that is being controlled
    bool _active = false;
    /*private*/ NamedBeanHandle<Sensor*>* _namedControlSensor = nullptr;
    PropertyChangeListener* _sensorListener = nullptr;
    /*private*/ NamedBeanHandle<Sensor*>* _namedControlSensor2 = nullptr;
    /*private*/ PropertyChangeListener* _timedSensorListener = nullptr;
    /*private*/ QTimer* _timedControlTimer = nullptr;
    /*private*/ ActionListener* _timedControlListener = nullptr;
    /*private*/ int _timeNow = 0;
    /*private*/ PropertyChangeListener* _parentLightListener = nullptr;
    PropertyChangeListener* _sensor2Listener = nullptr;
    PropertyChangeListener* _timebaseListener = nullptr;
    PropertyChangeListener* _turnoutListener = nullptr;
    bool _lightOnTimerActive = false;
    Timebase* _clock = nullptr;


    NamedBeanHandleManager* nbhm;
    /**
     *  Updates the status of a Light under FAST_CLOCK_CONTROL.  This
     *   method is called every FastClock minute.
     */
    //@SuppressWarnings("deprecation")
    /*private*/ void updateClockControlLightFollower();
    void common();
    static Logger* log;
    /*private*/ void setTheTime();
    /*private*/ bool isMasterFastClockFollower();
    /*private*/ bool isFastClockEqual(int time);
    /*private*/ void oneSensorChanged(int newSensorState);
    /*private*/ void oneTurnoutChanged(int newTurnoutState);
    /*private*/ static QString getControlSensorSenseText(LightControl* lc);
    /*private*/ static QString getControlTurnoutStateText(LightControl* lc);

protected:
    int _controlSensorSense = Sensor::ACTIVE;  // sense of Sensor for Light ON
    int _timeOnDuration =0;          // duration (milliseconds) if TIMED_ON_CONTROL
    // operational instance variables - not saved between runs
    int _timeOn=0;
    int _timeOff=0;
    Turnout* _controlTurnout= nullptr;
    NamedBeanHandle<Sensor*>* _namedTimedControlSensor = nullptr;
    /*protected*/ void twoSensorChanged();
    virtual /*protected*/ int getFastClockOffCombined();
    virtual /*protected*/ int getFastClockOnCombined();

    friend class LightControlTest;
    friend class TimeLight;
    friend class LC1PropertyChangeListener;
    friend class LC2PropertyChangeListener;
    friend class LC3PropertyChangeListener;
    friend class LC4PropertyChangeListener;
    friend class LC5PropertyChangeListener;
    friend class LC6PropertyChangeListener;
    friend class LightTableAction;
    friend class DefaultLightControl;
};

class LC1PropertyChangeListener : public QObject, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 LightControl* lc;
 public:
 LC1PropertyChangeListener(LightControl* lc) {this->lc = lc;}
 QObject* self() override{return (QObject*)this;}

public slots:
 void propertyChange(PropertyChangeEvent*);
};

class LC2PropertyChangeListener : public QObject,public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 LightControl* lc;
 public:
 LC2PropertyChangeListener(LightControl* lc) {this->lc = lc;}
 QObject* self() override{return (QObject*)this;}
public slots:
 void propertyChange(PropertyChangeEvent*) override;
};

class LC3PropertyChangeListener : public QObject, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 LightControl* lc;
 public:
 LC3PropertyChangeListener(LightControl* lc) {this->lc = lc;}
 QObject* self() override{return (QObject*)this;}
public slots:
 void propertyChange(PropertyChangeEvent*);
};

class LC4PropertyChangeListener : public QObject, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 LightControl* lc;
 public:
 LC4PropertyChangeListener(LightControl* lc) {this->lc = lc;}
 QObject* self() override{return (QObject*)this;}
public slots:
 void propertyChange(PropertyChangeEvent*);
};

class LC5PropertyChangeListener : public QObject, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 LightControl* lc;
 public:
 LC5PropertyChangeListener(LightControl* lc) {this->lc = lc;}
 QObject* self() override{return (QObject*)this;}
public slots:
 void propertyChange(PropertyChangeEvent*);
};

class LC6PropertyChangeListener : public QObject, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 LightControl* lc;
 public:
 LC6PropertyChangeListener(LightControl* lc) {this->lc = lc;}
 QObject* self() override{return (QObject*)this;}
public slots:
 void propertyChange(PropertyChangeEvent*);
};

//class TimeLight : public ActionListener
//{
// Q_OBJECT
// LightControl* lc;
//public:
// TimeLight(LightControl* lc) {this->lc = lc;}
// public slots:
//    /*public*/ void actionPerformed(/*ActionEvent* event*/);
//};

#endif // LIGHTCONTROL_H
