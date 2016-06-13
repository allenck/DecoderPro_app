#ifndef DEFAULTCLOCKCONTROL_H
#define DEFAULTCLOCKCONTROL_H

#include "logger.h"
#include "clockcontrol.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT DefaultClockControl : public ClockControl
{
    Q_OBJECT
public:
    explicit DefaultClockControl(QObject *parent = 0);
    /**
     * Get Status of the Fast Clock
     */
    virtual int getStatus();
    /**
     * Get name of hardware clock
     * Note: If there is no hardware clock, this method returns null.
     */
    virtual QString getHardwareClockName();
    /**
     * Returns true if hardware clock accuracy can be corrected using the
     *		computer clock. Hardware implementations should override this and
     *		return true if they can correct their hardware clock.
     */
    virtual bool canCorrectHardwareClock();
    /**
     * Returns true if hardware clock can be set to 12 or 24 hour display from
     *              JMRI software.
     * Note: Default implementation is to return false.
     */
    virtual bool canSet12Or24HourClock();
    /**
     * Returns true if hardware clock requires an integer rate
     * Note: Default implementation returns false. If an integer rate is required
     *			by the hardware, this method should be overridden.
     */
    virtual bool requiresIntegerRate();
    /**
     * Get and set the rate of the fast clock
     * Note: The rate is an integer that multiplies the wall clock
     *    For example, a rate of 4 specifies that the fast clock runs 4 times
     *		faster than the wall clock.
     * For the default implementation, setRate is ignored, and getRate returns
     *		the rate of the internal clock;
     */
    virtual void setRate(double newRate);
    virtual double getRate();
    /**
     * Set and get the fast clock time
     * For the default implementation,set time is ignored and getTime returns
     *		the time of the internal clock;
     */
    virtual void setTime(QDateTime now);
    virtual QDateTime getTime();
/**
 * Start and stop hardware fast clock
 * Many hardware fast clocks continue to run indefinitely. This is provided
 *		for the case where the hardware clock can be stopped and started.
 */
virtual void startHardwareClock(QDateTime now);
virtual void stopHardwareClock();
/**
 * Initialize the hardware fast clock
 * Note: When the hardware clock control receives this, it should
 *		initialize those clock settings that are available on the
 *		hardware clock.
 * Default implementation is to ignore this request.
 */
virtual void initializeHardwareClock(double rate, QDateTime now, bool getTime);

signals:
    
public slots:
private:
 Logger log;
    
};

#endif // DEFAULTCLOCKCONTROL_H
