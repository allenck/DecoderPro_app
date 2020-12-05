#ifndef ANALOGIO_H
#define ANALOGIO_H
#include "abstractnamedbean.h"

/**
 * Represent an analog I/O on the layout.
 *
 * @author Daniel Bergqvist Copyright (C) 2018
 */
/*public*/ /*interface*/class AnalogIO : public AbstractNamedBean {
  Q_OBJECT
 public:
    AnalogIO(QObject* parent = nullptr) : AbstractNamedBean(parent) {}
    AnalogIO(QString systemName, QObject* parent = nullptr) : AbstractNamedBean(systemName, parent) {}
    AnalogIO(QString systemName, QString userName, QObject* parent = nullptr) : AbstractNamedBean(systemName, userName, parent) {}

    /**
     * Is the value an absolute value or a relative value?
     * In both cases, AnalogIO.getMin() and AnalogIO.getMax() tells the
     * limits of the value.
     */
    /*public*/ class AbsoluteOrRelative {

//        ABSOLUTE(tr("AnalogIO_Absolute")),
//        RELATIVE(tr("AnalogIO_Relative"));
      enum TYPE
      {
       ABSOLUTE,
       RELATIVE
      };
        /*private*/ /*final*/ QString _str;

        /*private*/ AbsoluteOrRelative(QString str) {
            _str = str;
        }
        public:
        //@CheckReturnValue
        //@Override
        /*public*/ QString toString() {
            return _str;
        }
      friend class DefaultMeter;
    };

    /**
     * Show whether the analog value is stable.
     *
     * @return true if the analog value is stable
     */
    //@CheckReturnValue
    /*default*/ /*public*/ bool isConsistentValue() {
        return true;
    }

    /**
     * Change the commanded value, which results in the relevant command(s)
     * being sent to the hardware. The exception is thrown if there are problems
     * communicating with the layout hardware.
     * <p>
     * The value must be a valid number, not a NaN or infinity number.
     *
     * @param value the desired analog value
     * @throws jmri.JmriException general error when setting the value fails
     * @throws IllegalArgumentException if the value is Double.NaN,
     *                                  Double.NEGATIVE_INFINITY or
     *                                  Double.POSITIVE_INFINITY
     */
  virtual /*public*/ void setCommandedAnalogValue(double value) throw (JmriException) {}

    /**
     * Query the commanded value. This is a bound parameter, so you can also
     * register a listener to be informed of changes.
     * <p>
     * The result must be a valid number, not a NaN or infinity number.
     *
     * @return the analog value
     */
    //@CheckReturnValue
  virtual /*public*/ double getCommandedAnalogValue() {return 0;}

    /**
     * Query the known analog value. This is a bound parameter, so you can also
     * register a listener to be informed of changes. A result is always
     * returned; if no other feedback method is available, the commanded value
     * will be used.
     * <p>
     * The result must be a valid number, not a NaN or infinity number.
     *
     * @return the known analog value
     */
    //@CheckReturnValue
    virtual /*default*/ /*public*/ double getKnownAnalogValue() {
        return getCommandedAnalogValue();
    }

    /**
     * Provide generic access to internal state.
     * <p>
     * This generally shouldn't be used by Java code; use the class-specific
     * form instead (setCommandedAnalogValue). This is provided to
     * make scripts access easier to read.
     *
     * @param value the analog value
     * @throws JmriException general error when setting the state fails
     */
    //@InvokeOnLayoutThread
    virtual /*public*/ void setState(double value) throw (JmriException) =0;

    /**
     * Provide generic access to internal state.
     * <p>
     * This generally shouldn't be used by Java code; use the class-specific
     * form instead (getCommandedAnalogValue). This is provided to
     * make scripts easier to read.
     *
     * @param v only used to select this method which returns an analog value.
     *          It's recommended to use 0.0 as the parameter.
     * @return the state
     */
    //@CheckReturnValue
  virtual /*public*/ double getState(double v) {return 0;}

    /**
     * Get the minimum value of this AnalogIO.
     * @return minimum value.
     */
    //@CheckReturnValue
  virtual /*public*/ double getMin() {return 0;}

    /**
     * Get the maximum value of this AnalogIO.
     * @return maximum value.
     */
    //@CheckReturnValue
  virtual /*public*/ double getMax() {return 0;}

    /**
     * Get the resolution of this AnalogIO.
     * @return analog resolution.
     */
    //@CheckReturnValue
  virtual /*public*/ double getResolution() {return 0;}

    /**
     * Is this AnalogIO absolute or relative?
     * @return if absolute or relative.
     */
    //@CheckReturnValue
  virtual /*public*/ AbsoluteOrRelative getAbsoluteOrRelative() =0;

    /**
     * Request an update from the layout soft/hardware. May not even happen, and
     * if it does it will happen later; listen for the result.
     */
    virtual /*default*/ /*public*/ void requestUpdateFromLayout() {
    }
};

#endif // ANALOGIO_H
