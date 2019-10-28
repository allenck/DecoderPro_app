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
    /*public*/ int getControlType();
    /*public*/ int hashCode();
    /*public*/ void setControlType(int type);
    /*public*/ void setControlSensorName(QString sensorName);
    /*public*/ int getControlSensorSense() ;
    /*public*/ QString getControlSensorName();
    /*public*/ void setControlSensorSense(int sense);
    /*public*/ int getFastClockOnHour();
    /*public*/ int getFastClockOnMin();
    /*public*/ int getFastClockOffHour();
    /*public*/ int getFastClockOffMin();
    /*public*/ void setFastClockControlSchedule(int onHour,int onMin,int offHour, int offMin);
    /*public*/ QString getControlTurnoutName();
    /*public*/ void setControlTurnout(QString turnoutName);
    /*public*/ int getControlTurnoutState();
    /*public*/ void setControlTurnoutState(int state);
    /*public*/ QString getControlTimedOnSensorName();
    /*public*/ void setControlTimedOnSensorName(QString sensorName);
    /*public*/ int getTimedOnDuration();
    /*public*/ void setTimedOnDuration(int duration);
    /*public*/ QString getControlSensor2Name();
    /*public*/ void setControlSensor2Name(QString sensorName);
    /*public*/ void setParentLight(Light* l);
    /**
     * Activates a Light Control by control type.  This method tests the
     *   control type, and set up a control mechanism, appropriate
     *   for the control type.
     */
    /*public*/ void activateLightControl();
    /**
     * Deactivates a LightControl by control type.  This method tests the
     *   control type, and deactivates the control mechanism, appropriate
     *   for the control type.
     */
    /*public*/ void deactivateLightControl();
    /*public*/ bool onOffTimesFaulty();
    /*public*/ bool areFollowerTimesFaulty( QList<LightControl*> compareList );


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
    /*private*/ void updateClockControlLight();
    void common();
Logger* log;
    /*private*/ bool isMasterFastClockFollower();
    /*private*/ Predicate<LightControl*> isFastClockEqual(int time);

protected:
    int _controlSensorSense = 0;  // sense of Sensor for Light ON
    int _timeOnDuration =0;          // duration (milliseconds) if TIMED_ON_CONTROL
    // operational instance variables - not saved between runs
    int _timeOn=0;
    int _timeOff=0;
    Turnout* _controlTurnout= nullptr;
    NamedBeanHandle<Sensor*>* _namedTimedControlSensor = nullptr;
    /*protected*/ void twoSensorChanged(PropertyChangeEvent* e);
    /*protected*/ int getFastClockOffCombined();
    /*protected*/ int getFastClockOnCombined();

    friend class LightControlTest;
};

#endif // LIGHTCONTROL_H
