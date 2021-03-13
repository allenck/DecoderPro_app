#ifndef TRANSITACTIONSECTION_H
#define TRANSITACTIONSECTION_H

#include <QObject>

class Sensor;
class PropertyChangeListener;
class TransitSection;
class TransitSectionAction : public QObject
{
  Q_OBJECT
public:
    TransitSectionAction();
    /*public*/ TransitSectionAction(int when, int what);
    /*public*/ TransitSectionAction(int when, int what, int dataWhen, int dataWhat1, int dataWhat2, QString sWhen, QString sWhat);
    /**
     * Constants representing the "when" (when the action is to be initiated) of
     * the Action
     */
    enum WHEN
    {
     NUM_WHENS = 8, // Must correspond to the number of entries below
     ENTRY = 1,   // On entry to Section
     EXIT = 2,	  // On exit from Section
     BLOCKENTRY = 3, // On entry to specified Block in the Section
     BLOCKEXIT = 4, // On exit from specified Block in the Section
     TRAINSTOP = 5,  // When train stops
     TRAINSTART = 6, // When train starts
     SENSORACTIVE = 7, // When specified Sensor changes to Active
     SENSORINACTIVE = 8 // When specified Sensor changtes to Inactive
    // other action 'whens" may be defined here
    };
    /**
     * Constants designating the "what" (the action to be taken) of the Action
     */
    enum WHAT
    {
     PAUSE = 1,    // pause for the number of fast minutes in mDataWhat (e.g. station stop)
     SETMAXSPEED = 2, // set maximum train speed to value entered
     SETCURRENTSPEED = 3, // set current speed to target speed immediately - no ramping
     RAMPTRAINSPEED = 4, // set current speed to target with ramping
     TOMANUALMODE = 5, // drop out of automated mode, and allow manual throttle control
     SETLIGHT = 6, // set light on or off
     STARTBELL = 7,  // start bell (only works with sound decoder, function 1 ON)
     STOPBELL = 8,   // stop bell (only works with sound decoder, function 1 OFF)
     SOUNDHORN = 9,  // sound horn for specified number of milliseconds
    //													(only works with sound decoder, function 2)
     SOUNDHORNPATTERN = 10, // sound horn according to specified pattern
    //													(only works with sound decoder, function 2)
     LOCOFUNCTION = 11,  // execute the specified decoder function
     SETSENSORACTIVE = 12, // set specified sensor active (offers access to Logix)
     SETSENSORINACTIVE = 13, // set specified sensor inactive
     HOLDSIGNAL = 14,    // set specified signalhead or signalmast to HELD
     RELEASESIGNAL = 15, // set specified signalhead or signalmast to NOT HELD
     NUM_WHATS = 15 // Must correspond to the number of entries above
    // other action 'whats" may be defined here
    };
    /*public*/ int getWhenCode();
    /*public*/ void setWhenCode(int n) ;
    /*public*/ int getWhatCode();
    /*public*/ void setWhatCode(int n) ;
    /*public*/ int getDataWhen();
    /*public*/ void setDataWhen(int n);
    /*public*/ int getDataWhat1();
    /*public*/ void setDataWhat1(int n);
    /*public*/ int getDataWhat2();
    /*public*/ void setDataWhat2(int n);
    /*public*/ QString getStringWhen();
    /*public*/ void setStringWhen(QString s);
    /*public*/ QString getStringWhat();
    /*public*/ void setStringWhat(QString s);

    /**
     * Operational access methods
     */
    /*public*/ void initialize();
    /*public*/ QThread* getWaitingThread();
    /*public*/ void setWaitingThread(QThread* t);
    /*public*/ bool getWaitingForSectionExit();
    /*public*/ void setWaitingForSectionExit(bool w);
    /*public*/ TransitSection* getTargetTransitSection();
    /*public*/ void setTargetTransitSection(TransitSection* ts);
    /*public*/ bool getWaitingForBlock();
    /*public*/ void setWaitingForBlock(bool w);
    /*public*/ bool getWaitingForSensor();
    /*public*/ void setWaitingForSensor(bool w) ;
    /*public*/ Sensor* getTriggerSensor();
    /*public*/ void setTriggerSensor(Sensor* s);
    /*public*/ PropertyChangeListener* getSensorListener();
    /*public*/ void setSensorListener(PropertyChangeListener* l);
    /*public*/ void disposeSensorListener();
    /*public*/ void dispose();

private:
    void common();
    // instance variables
    /*private*/ int mWhen;// = 0;
    /*private*/ int mWhat;// = 0;
    /*private*/ int mDataWhen;// = -1;	// negative number signified no data
    /*private*/ int mDataWhat1;// = -1;    // negative number signified no data
    /*private*/ int mDataWhat2;// = -1;    // negative number signified no data
    /*private*/ QString mStringWhen;// = "";
    /*private*/ QString mStringWhat;// = "";
    /**
     * operational instance variables - flags and data for executing the action
     * (see jmri.jmrit.dispatcher.AutoActiveTrain.java)
     */
    /*private*/ QThread* _waitingThread;// = null;
    /*private*/ bool _waitingForSectionExit;// = false;
    /*private*/ TransitSection* _targetTransitSection;// = null;
    /*private*/ bool _waitingForBlock;// = false;
    /*private*/ bool _waitingForSensor;// = false;
    /*private*/ Sensor* _triggerSensor;// = null;
    /*private*/ PropertyChangeListener* _sensorListener;// = null;
};

#endif // TRANSITACTIONSECTION_H
