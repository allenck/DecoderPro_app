#ifndef MULTIMETER_H
#define MULTIMETER_H
#include <QObject>
#include "propertychangeprovider.h"
/**
 * Interface for displaying (and controlling where appropriate) Current,
 * Voltage, and other status data from the layout.
 *
 */
/*public*/ /*interface*/class  MultiMeter : public PropertyChangeProvider
{
public:
    /*public*/ static /*final*/ QString CURRENT;// = "MultiMeterCurrent";
    /*public*/ static /*final*/ QString VOLTAGE;// = "MultiMeterVoltage";

    /*public*/ virtual void enable() =0;

    /*public*/ virtual void disable() =0;

    /**
     * Set the current.
     *
     * @param c the current
     */
    /*public*/ virtual void setCurrent(float c) =0;

    /**
     * get the current
     * @return the current in units specified by getCurrentUnits
     */
    /*public*/ virtual float getCurrent() = 0;

    /**
     * The units returned by getCurrent.
     * CURRENT_UNITS_PERCENTAGE - 100.0 = 100%
     * CURRENT_UNITS_AMPS - 1 = 1AMP.
     * CURRENT_UNITS_MILLIAMPS - 1000 = 1AMP.
     */
    /*public*/ /*static*/ enum CurrentUnits {
        CURRENT_UNITS_PERCENTAGE,
        CURRENT_UNITS_AMPS,
        CURRENT_UNITS_MILLIAMPS
    };

    /**
     * Gets the unit used for current
     * @return the units used for current either percentage (100.0 = 100%) or Amps or milliamps.
     */
    /*public*/ virtual CurrentUnits getCurrentUnits() =0;

    /**
     * Set the voltage.
     *
     * @param v the voltage in volts.
     */
    /*public*/ virtual void setVoltage(float v) =0;

    /**
     * get the voltage.
     *
     * @return v the voltage in volts.
     */
    /*public*/ virtual float getVoltage() =0;

    /*public*/ virtual void initializeHardwareMeter() =0;

    /*public*/ virtual QString getHardwareMeterName() =0;

    /*public*/ virtual bool hasCurrent() =0;

    /*public*/ virtual bool hasVoltage() =0;

    /**
     * Remove references to and from this object, so that it can eventually be
     * garbage-collected.
     */
    /*public*/ virtual void dispose() =0;

    virtual QObject* self() =0;
};
Q_DECLARE_INTERFACE(MultiMeter, "MultiMeter")
#endif // MULTIMETER_H
