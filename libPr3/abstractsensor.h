#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H
#include "abstractnamedbean.h"
#include "reporter.h"
#include "sensor.h"
#include "runnable.h"

class LIBPR3SHARED_EXPORT AbstractSensor : public Sensor/*, public Sensor*/
{
 Q_OBJECT
public:
 explicit AbstractSensor(QObject *parent = 0);
 // ctor takes a system-name string for initialization
 AbstractSensor(QString systemName, QObject *parent = 0);
 AbstractSensor(QString systemName, QString userName, QObject *parent = 0);
 int getKnownState() const;
 void setSensorDebounceGoingActiveTimer(long time);
 long getSensorDebounceGoingActiveTimer();
 void setSensorDebounceGoingInActiveTimer(long time);
 long getSensorDebounceGoingInActiveTimer();
 void useDefaultTimerSettings(bool boo);
 bool useDefaultTimerSettings();
 // setKnownState() for implementations that can't
 // actually do it on the layout. Not intended for use by implementations
 // that can
 void setKnownState(int s); // throws jmri.JmriException {
    /**
     * Set our internal state information, and notify bean listeners.
     */
    void setOwnState(int s);
    int getRawState();
    /**
     * Implement a shorter name for setKnownState.
     *<P>
     * This generally shouldn't be used by Java code; use
     * setKnownState instead.  The is provided to make Jython
     * script access easier to read.
     */
    void setState(int s);// throws jmri.JmriException { setKnownState(s); }
    /**
     * Implement a shorter name for getKnownState.
     *<P>
     * This generally shouldn't be used by Java code; use
     * getKnownState instead.  The is provided to make Jython
     * script access easier to read.
     */
    int getState();
    /**
     * Control whether the actual sensor input is
     * considered to be inverted, e.g. the normal
     * electrical signal that results in an ACTIVE state
     * now results in an INACTIVE state.
     */
    void setInverted(bool inverted);
    /**
     * Get the inverted state.  If true, the
     * electrical signal that results in an ACTIVE state
     * now results in an INACTIVE state.
     * <P>
     * Used in polling loops in system-specific code,
     * so made final to allow optimization.
     */
    /*final public*/ bool getInverted();
    /**
     * Some sensor boards also serve the function of being able to report
     * back train identities via such methods as RailCom.
     * The setting and creation of the reporter against the sensor should be
     * done when the sensor is created.  This information is not saved.
     * <p>
     * returns NULL if there is no direct reporter.
     */
    void setReporter(Reporter* er);
    Reporter* getReporter();
    QString getStateName(int);

signals:
    //void propertyChange(QString propertyName, int oldState, int knownState);
    //void propertyChange(PropertyChangeEvent*);

public slots:
private:
    int restartcount = 0;
    Reporter* reporter = nullptr;
    int lastKnownState = _knownState;
    Logger log;
protected:
    long sensorDebounceGoingActive = 0L;
    long sensorDebounceGoingInActive = 0L;
    bool _useDefaultTimerSettings = false;
    QThread* thr = nullptr;
    Runnable* r;
    void sensorDebounce();
    bool _inverted = false;

    // internal data members
    int _knownState     = UNKNOWN;
    int _rawState       = UNKNOWN;
 friend class LnSensor;
 friend class ASRunnable;
};
class ASRunnable : public Runnable
{
public:
 ASRunnable(QObject* as);
 void run();
};

#endif // ABSTRACTSENSOR_H
