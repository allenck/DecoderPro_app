#include "abstractanalogio.h"
#include "limits.h"
#include "math.h"
/**
 * Base implementation of the AnalogIO interface.
 *
 * @author Daniel Bergqvist Copyright (c) 2018
 */
// /*public*/ abstract class AbstractAnalogIO extends AbstractNamedBean implements AnalogIO {


    /**
     * Abstract constructor for new AnalogIO with system name
     *
     * @param systemName AnalogIO system name
     * @param commandedValueSetsKnownValue true if setCommandedValue() also sets
     * known value, false othervise
     */
    /*public*/ AbstractAnalogIO::AbstractAnalogIO(/*@Nonnull*/ QString systemName, bool commandedValueSetsKnownValue, QObject *parent)
     : AnalogIO(systemName, parent)
    {
        //super(systemName);
        this->_commandedValueSetsKnownValue = commandedValueSetsKnownValue;
    }

    /**
     * Abstract constructor for new AnalogIO with system name and user name
     *
     * @param systemName AnalogIO system name
     * @param userName   AnalogIO user name
     * @param commandedValueSetsKnownValue true if setCommandedValue() also sets
     * known value, false othervise
     */
    /*public*/ AbstractAnalogIO::AbstractAnalogIO(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName, bool commandedValueSetsKnownValue, QObject *parent)
     : AnalogIO(systemName, userName, parent)
    {
        //super(systemName, userName);
        this->_commandedValueSetsKnownValue = commandedValueSetsKnownValue;
    }

    /**
     * Sends the string to the layout.
     * The string [u]must not[/u] be longer than the value of getMaximumLength()
     * unless that value is zero. Some microcomputers have little memory and
     * it's very important that this method is never called with too long strings.
     *
     * @param value the desired string value
     * @throws jmri.JmriException general error when setting the value fails
     */
//    abstract protected void sendValueToLayout(double value) throws JmriException;

    /**
     * Set the value of this AnalogIO. Called from the implementation class
     * when the layout updates this AnalogIO.
     *
     * @param newValue the new value
     */
    /*protected*/ void AbstractAnalogIO::setValue(double newValue) {
        double _old = this->_knownValue;
        this->_knownValue = newValue;
        firePropertyChange(PROPERTY_STATE, _old, _knownValue); //NOI18N
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void AbstractAnalogIO::setCommandedAnalogValue(double value) throw (JmriException) {
        if (value == /*Double.NEGATIVE_INFINITY*/-INFINITY) {
            throw  IllegalArgumentException("value is negative infinity");
        }
        if (value == /*Double.POSITIVE_INFINITY*/INFINITY) {
            throw IllegalArgumentException("value is positive infinity");
        }
        if (/*Double.isNaN(value)*/value == NAN) {
            throw  IllegalArgumentException("value is not-a-number");
        }

        double min = getMin();
        double max = getMax();

        if (value < min) {
            if (cutOutOfBoundsValues()) value = min;
            else throw new JmriException("value out of bounds");
        }
        if (value > max) {
            if (cutOutOfBoundsValues()) value = max;
            else throw new JmriException("value out of bounds");
        }
        _commandedValue = value;

        if (_commandedValueSetsKnownValue) {
            setValue(_commandedValue);
        }
        sendValueToLayout(_commandedValue);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ double AbstractAnalogIO::getCommandedAnalogValue() {
        return _commandedValue;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ double AbstractAnalogIO::getKnownAnalogValue() {
        return _knownValue;
    }

    /**
     * Cut out of bounds values instead of throwing an exception?
     * For example, if the AnalogIO is a display, it could be desired to
     * accept too long strings.
     * On the other hand, if the AnalogIO is used to send a command, a too
     * long string is an error.
     *
     * @return true if long strings should be cut
     */
//    abstract protected boolean cutOutOfBoundsValues();

    /** {@inheritDoc} */
    //@Override
    /*public*/ double AbstractAnalogIO::getState(double v) {
        return getCommandedAnalogValue();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void AbstractAnalogIO::setState(double value) throw (JmriException) {
        setCommandedAnalogValue(value);
    }

    /** {@inheritDoc} */
    //@Override
    //@Nonnull
    /*public*/ QString AbstractAnalogIO::getBeanType() {
        return tr("AnalogIO");
    }

    /**
     * {@inheritDoc}
     *
     * Do a string comparison.
     */
    //@CheckReturnValue
    //@Override
    /*public*/ int AbstractAnalogIO::compareSystemNameSuffix(/*@Nonnull*/ QString suffix1, /*@Nonnull*/ QString suffix2, /*@Nonnull*/ NamedBean* n) {
        return suffix1.compare(suffix2);
    }
