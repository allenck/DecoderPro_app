#include "defaultclockcontrol.h"
#include "instancemanager.h"
/**
 * Class providing default logic of the ClockControl interface.
 *
 * Hardware systems that have fast clocks should "extend DefaultClockControl"
 *	and override the appropriate methods.

 * This class provides default implementations of ClockControl methods that
 *  are not needed in the hardware implementation if one exists, or for those
 *	systems with no hardware fast clock.
 *
 * @author	Dave Duchamp Copyright (C) 2007
 * @version     $Revision: 17977 $
 */

DefaultClockControl::DefaultClockControl(QObject */*parent*/) /*:
    ClockControl(parent)*/
{
 setObjectName("DefaultClockControl");
}

/**
 *  Operational instance variables (not saved between runs)
 */

/**
 * Get Status of the Fast Clock
 */
int DefaultClockControl::getStatus() {return 0;}

/**
 * Get name of hardware clock
 * Note: If there is no hardware clock, this method returns NULL.
 */
QString DefaultClockControl::getHardwareClockName(){return "";}

/**
 * Returns true if hardware clock accuracy can be corrected using the
 *		computer clock. Hardware implementations should override this and
 *		return true if they can correct their hardware clock.
 */
bool DefaultClockControl::canCorrectHardwareClock() {return false;}

/**
 * Returns true if hardware clock can be set to 12 or 24 hour display from
 *              JMRI software.
 * Note: Default implementation is to return false.
 */
bool DefaultClockControl::canSet12Or24HourClock() {return false;}

/**
 * Returns true if hardware clock requires an integer rate
 * Note: Default implementation returns false. If an integer rate is required
 *			by the hardware, this method should be overridden.
 */
bool DefaultClockControl::requiresIntegerRate() {return false;}

/**
 * Get and set the rate of the fast clock
 * Note: The rate is an integer that multiplies the wall clock
 *    For example, a rate of 4 specifies that the fast clock runs 4 times
 *		faster than the wall clock.
 * For the default implementation, setRate is ignored, and getRate returns
 *		the rate of the internal clock;
 */
void DefaultClockControl::setRate(double /*newRate*/) {return;}
double DefaultClockControl::getRate() {
    return static_cast<Timebase*>(InstanceManager::getDefault("Timebase"))->getRate();
}

/**
 * Set and get the fast clock time
 * For the default implementation,set time is ignored and getTime returns
 *		the time of the internal clock;
 */
void DefaultClockControl::setTime(QDateTime /*now*/){return;}
QDateTime DefaultClockControl::getTime() {
    return static_cast<Timebase*>(InstanceManager::getDefault("Timebase"))->getTime();
}

/**
 * Start and stop hardware fast clock
 * Many hardware fast clocks continue to run indefinitely. This is provided
 *		for the case where the hardware clock can be stopped and started.
 */
void DefaultClockControl::startHardwareClock(QDateTime now) {
    setTime(now);
    return;
}
void DefaultClockControl::stopHardwareClock() {return;}

/**
 * Initialize the hardware fast clock
 * Note: When the hardware clock control receives this, it should
 *		initialize those clock settings that are available on the
 *		hardware clock.
 * Default implementation is to ignore this request.
 */
void DefaultClockControl::initializeHardwareClock(double /*rate*/, QDateTime /*now*/, bool /*getTime*/) {return;}


//static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(DefaultClockControl.class.getName());
