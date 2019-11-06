#ifndef SIMPLETIMEBASE_H
#define SIMPLETIMEBASE_H
#include "abstractnamedbean.h"
#include <QTimer>
#include "sensor.h"
#include "memory.h"
#include "clockcontrol.h"
#include "exceptions.h"
#include "timebase.h"

class LIBPR3SHARED_EXPORT SimpleTimebase : public Timebase
{
    Q_OBJECT
public:
    explicit SimpleTimebase(QObject *parent = 0);
    ~SimpleTimebase();
    /*public*/ QString getBeanType();
    /*public*/ virtual QDateTime getTime();
    /*public*/ virtual void setTime(QDateTime d);
    /*public*/ virtual void userSetTime(QDateTime d);
    /*public*/ virtual void setRun(bool run);
    /*public*/ bool getRun();
    /*public*/ void setRate(double factor);
    /*public*/ void userSetRate(double factor);
    /*public*/ double getRate();
    /*public*/ double userGetRate();
    /*public*/ void setInternalMaster(bool master, bool update);
    /*public*/ bool getInternalMaster();
    /*public*/ void setMasterName(QString name);
    /*public*/ QString getMasterName();
    /*public*/ void setSynchronize(bool synchronize, bool update);
    /*public*/ virtual bool getSynchronize();
    /*public*/ void setCorrectHardware(bool correct, bool update);
    /*public*/ bool getCorrectHardware();
    /*public*/ void set12HourDisplay(bool display, bool update);
    /*public*/ bool use12HourDisplay();
    /*public*/ void setStartStopped(bool stopped);
    /*public*/ bool getStartStopped();
    /*public*/ void setStartSetTime(bool set, QDateTime time);
    /*public*/ bool getStartSetTime();
    /*public*/ QDateTime getStartTime();
    /*public*/ void setStartClockOption(int option);
    /*public*/ int getStartClockOption();
    /*public*/ void initializeClock ();
    /*public*/ void initializeHardwareClock();
    /*public*/ bool getIsInitialized();
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
    /*public*/ void dispose();
    void startAlarm();
    //void handleAlarm(); // see slots
    void updateMemory(QDateTime date);
    void updateMemory(double factor) ;
    /*public*/ void addMinuteChangeListener(PropertyChangeListener* l);
    /*public*/ void removeMinuteChangeListener(PropertyChangeListener* l);
    /*public*/ QList<PropertyChangeListener *> *getMinuteChangeListeners() override;
    /*public*/ void setState(int s) throw (JmriException);
    /*public*/ int getState();
    PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
    /*public*/ void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener);

signals:
    void minuteTick();

public slots:
    void handleAlarm();

private:
    /**
     * Timebase variables and options
     */
    /*private*/ double mFactor;// = 1.0;  // this is the rate factor for the JMRI fast clock
    /*private*/ double hardwareFactor;// = 1.0;  // this is the rate factor for the hardware clock
    //  The above is necessary to support hardware clock Time Sources that fiddle with mFactor to
    //      synchronize, instead of sending over a new time to synchronize.
    /*private*/ QDateTime startAtTime;
    /*private*/ QDateTime setTimeValue;
    /*private*/ QDateTime pauseTime;   // NULL value indicates clock is running
    /*private*/ Sensor* clockSensor;// = NULL;   // active when clock is running, inactive when stopped
    /*private*/ Memory* clockMemory;// = NULL;   // contains current time on each tick
    /*private*/ Memory* factorMemory;// = NULL;  // contains the rate factor for the fast clock

    /*private*/ bool internalMaster;// = true;     // false indicates a hardware clock is the master
    /*private*/ QString masterName;// = "";		// name of hardware time source, if not internal master
    /*private*/ ClockControl* hardwareTimeSource;// = NULL;  // ClockControl instance of hardware time source
    /*private*/ bool synchronizeWithHardware;// = false;  // true indicates need to synchronize
    /*private*/ bool correctHardware;// = false;    // true indicates hardware correction requested
    /*private*/ bool display12HourClock;// = false; // true if 12-hour clock display is requested
    /*private*/ bool startStopped;// = false;    // true indicates start up with clock stopped requested
    /*private*/ bool startSetTime;// = false;    // true indicates set fast clock to specified time at
                                                            //start up requested
    /*private*/ QDateTime startTime;// = new QDateTime();	// specified time for setting fast clock at start up
    /*private*/ int startClockOption;// = NONE;	// request start of a clock at start up
    /*private*/ bool notInitialized;// = true;  // true before initialization received from start up

//    SimpleDateFormat timeStorageFormat = NULL;

    QTimer* timer;// = NULL;
    //PropertyChangeSupport* pcMinutes;// = new PropertyChangeSupport(this);
    int oldMinutes;// = 0;
    /*private*/ void clockSensorChanged();
 Logger* log;
protected:
//    /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);

  friend class ClockSensorPropertChangeListener;
};

class ClockSensorPropertChangeListener : public PropertyChangeListener
{
 Q_OBJECT
 SimpleTimebase* stb;
public:
 ClockSensorPropertChangeListener(SimpleTimebase* stb) {this->stb = stb;}
public slots:
 void propertyChange(PropertyChangeEvent*);
};
#endif // SIMPLETIMEBASE_H
