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
class LIBPR3SHARED_EXPORT DefaultRoute : public Route, public VetoableChangeListener
{
    Q_OBJECT
  Q_INTERFACES(VetoableChangeListener)
public:
    //explicit DefaultRoute(QObject *parent = 0);
    /*public*/ DefaultRoute(QString systemName, QString userName,QObject *parent = 0) ;
    /*public*/ DefaultRoute(QString systemName, QObject *parent = 0);
    /*public*/ bool getEnabled() const override ;
    /*public*/ void setEnabled(bool v) override ;
    /*public*/ bool getLocked() override ;
    /*public*/ void setLocked(bool v) override ;
    /*public*/ bool canLock() override ;
    /*public*/ bool addOutputTurnout(QString turnoutName, int turnoutState) override ;
    /*public*/ void clearOutputTurnouts() override ;
    /*public*/ int getNumOutputTurnouts()  override ;
    /*public*/ QString getOutputTurnoutByIndex(int index) override ;
    /*public*/ bool isOutputTurnoutIncluded(QString turnoutName) override ;
    /*public*/ int getOutputTurnoutSetState(QString name) override ;
    /*public*/ Turnout* getOutputTurnout(int k) override ;
    /*public*/ int getOutputTurnoutState(int k) override ;
    /*public*/ bool addOutputSensor(QString sensorName, int state)  override ;
    /*public*/ void clearOutputSensors() override ;
    /*public*/ int getNumOutputSensors() override ;
    /*public*/ QString getOutputSensorByIndex(int index) override ;
    /*public*/ bool isOutputSensorIncluded(QString sensorName) override ;
    /*public*/ int getOutputSensorSetState(QString name) override ;
    /*public*/ Sensor* getOutputSensor(int k) override ;
    /*public*/ int getOutputSensorState(int k) override ;
    /*public*/ void setOutputScriptName(QString filename) override ;
    /*public*/ QString getOutputScriptName() override ;
    /*public*/ void setOutputSoundName(QString filename) override ;
    /*public*/ QString getOutputSoundName() override ;
    /*public*/ void setTurnoutsAlignedSensor(QString sensorName) override ;
    /*public*/ QString getTurnoutsAlignedSensor() override ;
    /*public*/ Sensor* getTurnoutsAlgdSensor() override ;
    /*public*/ void clearRouteSensors() override ;
    /*public*/ bool addSensorToRoute(QString sensorName, int mode) override ;
    /*public*/ QString getRouteSensorName(int index) override ;
    /*public*/ Sensor* getRouteSensor(int index) override ;
    /*public*/ int getRouteSensorMode(int index) override ;
    /*public*/ void setControlTurnout(QString turnoutName) override ;
    /*public*/ QString getControlTurnout() override ;
    /*public*/ Turnout* getCtlTurnout() override ;
    /*public*/ void setLockControlTurnout(QString turnoutName) override ;
    /*public*/ QString getLockControlTurnout() override ;
    /*public*/ Turnout* getLockCtlTurnout() override ;
    /*public*/ void setRouteCommandDelay(int delay) override ;
    /*public*/ int getRouteCommandDelay() override ;
    /*public*/ void setControlTurnoutState(int turnoutState) override ;
    /*public*/ int getControlTurnoutState() override ;
    /*public*/ void setLockControlTurnoutState(int turnoutState) override ;
    /*public*/ int getLockControlTurnoutState() override ;
    /*public*/ void setRoute() override ;
    void checkLockTurnout(int newState, int oldState, Turnout* t);
    void checkTurnout(int newState, int oldState, Turnout* t) ;
    /*public*/ void checkTurnoutAlignment();
    /*public*/ void activateRoute() override ;
    bool isVetoed();
    /*public*/ void deActivateRoute() override ;
    /*public*/ void setRouteBusy();
    /*public*/ void setRouteNotBusy();
    /*public*/ bool isRouteBusy();
    /*public*/ int getState() override ;
    /*public*/ void setState(int state) override ;
    /*public*/ QObject* self() override {return (QObject*)this;}
    /*public*/ QList<NamedBeanUsageReport*> getUsageReport(NamedBean* bean);

signals:

public slots:

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
  /*private*/ bool activatedRoute = false;

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
  /*protected*/ /*transient*/ PropertyChangeListener* mTurnoutListener;// = NULL;
  /*protected*/ /*transient*/ PropertyChangeListener* mLockTurnoutListener;// = NULL;

  QList <OutputTurnout*>* _outputTurnoutList;// = new QList<OutputTurnout*>();
  /*protected*/ void checkSensor(int newState, int oldState, Sensor* sensor);

 friend class ControlSensor;
 friend class MLockTurnoutListener;
 friend class MTurnoutListener;

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

/*private*/ class OutputTurnout : public QObject, public PropertyChangeListener
{
    Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
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
    QObject* pself() {return (QObject*)this;}

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

class MTurnoutListener : public QObject, public PropertyChangeListener
{
  Q_OBJECT
  DefaultRoute* dr;
 public:
  MTurnoutListener(DefaultRoute* dr ){this->dr = dr;}
  QObject* pself() override {return (QObject*)this;}

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) override
  {
      if (e->getPropertyName() == ("KnownState")) {
          int now = ( e->getNewValue()).toInt();
          int then = ( e->getOldValue()).toInt();
          dr->checkTurnout(now, then, (Turnout*)e->getSource());
      }
  }
};

class MLockTurnoutListener : public QObject, public PropertyChangeListener
{
  Q_OBJECT
  DefaultRoute* dr;
 public:
  QObject* pself() override {return (QObject*)this;}
  MLockTurnoutListener(DefaultRoute* dr ){this->dr = dr;}
 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) override
  {
   if (e->getPropertyName() == ("KnownState")) {
       int now = ( e->getNewValue().toInt());
       int then = (e->getOldValue().toInt());
       dr->checkLockTurnout(now, then, (Turnout*) e->getSource());
   }
  }
};

#endif // DEFAULTROUTE_H
