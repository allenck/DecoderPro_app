#ifndef DEFAULTROUTE_H
#define DEFAULTROUTE_H
#include "abstractnamedbean.h"
#include "turnout.h"
#include "instancemanager.h"
#include "route.h"
#include "abstractsensor.h"
#include "namedbean.h"

class ControlSensor;
class OutputSensor;
class OutputTurnout;
class InstanceManager;
class LIBPR3SHARED_EXPORT DefaultRoute : public Route
{
    Q_OBJECT
public:
    //explicit DefaultRoute(QObject *parent = 0);
    /*public*/ DefaultRoute(QString systemName, QString userName,QObject *parent = 0) ;
    /*public*/ DefaultRoute(QString systemName, QObject *parent = 0);
    /*public*/ bool getEnabled();
    /*public*/ void setEnabled(bool v);
    /*public*/ bool getLocked();
    /*public*/ void setLocked(bool v);
    /*public*/ bool canLock();
    /*public*/ bool addOutputTurnout(QString turnoutName, int turnoutState);
    /*public*/ void clearOutputTurnouts();
    /*public*/ int getNumOutputTurnouts() ;
    /*public*/ QString getOutputTurnoutByIndex(int index);
    /*public*/ bool isOutputTurnoutIncluded(QString turnoutName);
    /*public*/ int getOutputTurnoutSetState(QString name);
    /*public*/ Turnout* getOutputTurnout(int k);
    /*public*/ int getOutputTurnoutState(int k);
    /*public*/ bool addOutputSensor(QString sensorName, int state) ;
    /*public*/ void clearOutputSensors();
    /*public*/ int getNumOutputSensors();
    /*public*/ QString getOutputSensorByIndex(int index);
    /*public*/ bool isOutputSensorIncluded(QString sensorName);
    /*public*/ int getOutputSensorSetState(QString name);
    /*public*/ Sensor* getOutputSensor(int k);
    /*public*/ int getOutputSensorState(int k);
    /*public*/ void setOutputScriptName(QString filename);
    /*public*/ QString getOutputScriptName();
    /*public*/ void setOutputSoundName(QString filename);
    /*public*/ QString getOutputSoundName();
    /*public*/ void setTurnoutsAlignedSensor(QString sensorName);
    /*public*/ QString getTurnoutsAlignedSensor();
    /*public*/ Sensor* getTurnoutsAlgdSensor();
    /*public*/ void clearRouteSensors();
    /*public*/ bool addSensorToRoute(QString sensorName, int mode);
    /*public*/ QString getRouteSensorName(int index);
    /*public*/ Sensor* getRouteSensor(int index);
    /*public*/ int getRouteSensorMode(int index);
    /*public*/ void setControlTurnout(QString turnoutName);
    /*public*/ QString getControlTurnout();
    /*public*/ Turnout* getCtlTurnout();
    /*public*/ void setLockControlTurnout(QString turnoutName);
    /*public*/ QString getLockControlTurnout();
    /*public*/ Turnout* getLockCtlTurnout();
    /*public*/ void setRouteCommandDelay(int delay);
    /*public*/ int getRouteCommandDelay();
    /*public*/ void setControlTurnoutState(int turnoutState);
    /*public*/ int getControlTurnoutState();
    /*public*/ void setLockControlTurnoutState(int turnoutState);
    /*public*/ int getLockControlTurnoutState();
    /*public*/ void setRoute();
    void checkLockTurnout(int newState, int oldState, Turnout* t);
    void checkTurnout(int newState, int oldState, Turnout* t) ;
    /*public*/ void checkTurnoutAlignment();
    /*public*/ void activateRoute();
    bool isVetoed();
    /*public*/ void deActivateRoute();
    /*public*/ void setRouteBusy();
    /*public*/ void setRouteNotBusy();
    /*public*/ bool isRouteBusy();
    /*public*/ int getState();
    /*public*/ void setState(int state);

signals:

public slots:
    void propertyChange(PropertyChangeEvent* e);
private:
    /*private*/ DefaultRoute* r;
  Logger* log;
  /*private*/ static /*final*/ const long serialVersionUID = 1L;
  void init();
  QList <ControlSensor*>* _controlSensorList;// = new QList<ControlSensor>();

  QList <OutputSensor*>* _outputSensorList;// = new QList<OutputSensor*>();
  /*private*/ bool busy;// = false;
  /*private*/ bool _enabled;// = true;
  /*private*/ bool _locked;// = false;
  /**
   * Lock or unlock turnouts that are part of a route
   */
  /*private*/ void lockTurnouts(bool lock);

protected:
  /**
   *  Persistant instance variables (saved between runs)
   */
  /*protected*/ QString mControlTurnout;// = "";
  /*protected*/ NamedBeanHandle<Turnout*>* mControlNamedTurnout;// = NULL;
  /*protected*/ int mControlTurnoutState;// = Turnout::THROWN;
  /*protected*/ int mDelay;// = 0;

  /*protected*/ QString mLockControlTurnout;// = "";
  /*protected*/ NamedBeanHandle<Turnout*>* mLockControlNamedTurnout;// = NULL;
  /*protected*/ int mLockControlTurnoutState;// = jmri.Turnout.THROWN;

  /*protected*/ QString mTurnoutsAlignedSensor;// = "";
  /*protected*/ NamedBeanHandle<Sensor*>* mTurnoutsAlignedNamedSensor;// = NULL;

  /*protected*/ QString soundFilename;
  /*protected*/ QString scriptFilename;

  /*protected*/ NamedBeanHandleManager* nbhm;// = InstanceManager::getDefault("NamedBeanHandleManager");
  ///*protected*/ Turnout mTurnout = NULL;
  /*protected*/ /*transient*/ PropertyChangeListener* mTurnoutListener;// = NULL;
  ///*protected*/ Turnout mLockTurnout = NULL;
  /*protected*/ /*transient*/ PropertyChangeListener* mLockTurnoutListener;// = NULL;

  QList <OutputTurnout*>* _outputTurnoutList;// = new QList<OutputTurnout*>();
  /*protected*/ void checkSensor(int newState, int oldState, Sensor* sensor);

 friend class ControlSensor;
};
/*private*/ class OutputSensor : public QObject
{
    Q_OBJECT
 public:
    //Sensor _sensor;
    NamedBeanHandle<Sensor*>* _sensor;
    int _state;// = Sensor::ACTIVE;
    OutputSensor(QString name, DefaultRoute* parent);
    DefaultRoute* parent;
    QString getName();
    bool setState(int state);
    int getState();
    Sensor* getSensor();
private:
 Logger* log;
protected:
    /*protected*/ NamedBeanHandleManager* nbhm;// = InstanceManager::getDefault("NamedBeanHandleManager");

};
/*private*/ class ControlSensor : public OutputSensor /*implements PropertyChangeListener*/
{
    Q_OBJECT
 public:
    ControlSensor (QString name, DefaultRoute* parent);
    bool setState(int state);
    void addListener();
    void removeListener() ;
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
};
/*private*/ class OutputTurnout : public PropertyChangeListener
{
    Q_OBJECT
public:
    NamedBeanHandle<Turnout*>* _turnout;
    //Turnout _turnout;
    int _state;

    OutputTurnout(QString name, DefaultRoute* parent);
    QString getName();
    bool setState(int state);
    int getState() ;
    Turnout* getTurnout();
    void addListener();
    void removeListener() ;
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e) ;
private:
    DefaultRoute* parent;
  Logger* log;
  NamedBeanHandleManager* nbhm;
};
/**
* Class providing a thread to set route turnouts
*/
class SetRouteThread : public QThread
{
    Q_OBJECT
public:
 /**
  * Constructs the thread
  */
 /*public*/ SetRouteThread(DefaultRoute* aRoute);

 /*public*/ void run();
 private:
 DefaultRoute* r;
 Logger* log;
};
#endif // DEFAULTROUTE_H
