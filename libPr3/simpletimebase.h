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
    /*public*/ QString getBeanType() override;
    /*public*/ virtual QDateTime getTime();
    /*public*/ void setTime(QDateTime d) override;
    /*public*/ void userSetTime(QDateTime d) override;
    /*public*/ void setRun(bool run) override;
    /*public*/ bool getRun() override;
    /*public*/ void setRate(double factor) override;
    /*public*/ void userSetRate(double factor) override;
    /*public*/ double getRate() override;
    /*public*/ double userGetRate() override;
    /*public*/ void setInternalMaster(bool master, bool update) override;
    /*public*/ bool getInternalMaster() override;
    /*public*/ void setMasterName(QString name);
    /*public*/ QString getMasterName() override;
    /*public*/ void setSynchronize(bool synchronize, bool update) override;
    /*public*/ virtual bool getSynchronize() override;
    /*public*/ void setCorrectHardware(bool correct, bool update) override;
    /*public*/ bool getCorrectHardware() override;
    /*public*/ void set12HourDisplay(bool display, bool update) override;
    /*public*/ bool use12HourDisplay() override;
    /*public*/ void setStartStopped(bool stopped) override;
    /*public*/ bool getStartStopped() override;
    /*public*/ void setStartSetTime(bool set, QDateTime time) override;
    /*public*/ void setStartRate(double factor);
    /*public*/ double getStartRate();
    /*public*/ void setSetRateAtStart(bool set);
    /*public*/ bool getSetRateAtStart();
    /*public*/ bool getStartSetTime() override;
    /*public*/ QDateTime getStartTime() override;
    /*public*/ void setStartClockOption(int option) override;
    /*public*/ int getStartClockOption() override;
    /*public*/ void initializeClock () override;
    /*public*/ void initializeHardwareClock() override;
    /*public*/ bool getIsInitialized() override;
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l) override;
    /*public*/ void dispose() override;
    void startAlarm();
    //void handleAlarm(); // see slots
    void updateMemory(QDateTime date);
    void updateMemory(double factor) ;
    /*public*/ void addMinuteChangeListener(PropertyChangeListener* l) override;
    /*public*/ void removeMinuteChangeListener(PropertyChangeListener* l) override;
    /*public*/ QVector<PropertyChangeListener *> getMinuteChangeListeners() override;
    /*public*/ void setState(int s) throw (JmriException) override;
    /*public*/ int getState() override;
    PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
    /*public*/ void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) override;

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
    /*private*/ double startupFactor = 1.0; // this is the rate requested at startup
    /*private*/ bool startSetRate = true; // if true, the hardware rate will be set to
    /*private*/ bool haveStartupFactor = false; // true if startup factor was ever set.

    // startupFactor at startup.
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
