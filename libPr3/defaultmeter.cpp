#include "defaultmeter.h"
#include "meterupdatetask.h"
#include "loggerfactory.h"

/**
 * Abstract base class for current meter objects.
 *
 * @author Mark Underwood    (C) 2015
 * @author Daniel Bergqvist  (C) 2020
 */
///*public*/ class DefaultMeter extends AbstractAnalogIO implements Meter {


    /*public*/ DefaultMeter::DefaultMeter(/*@Nonnull*/ QString sys,
            /*@Nonnull*/ Meter::Unit unit,
            double min, double max, double resolution,
            /*@Nonnull*/ MeterUpdateTask* updateTask, QObject *parent)
        : AbstractAnalogIO(sys, true, parent) {
        //super(sys, true);
        this->_unit = unit;
        this->_updateTask = updateTask;
        this->_min = min;
        this->_max = max;
        this->_resolution = resolution;
        _updateTask->addMeter(this);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultMeter::enable() {
        if (_updateTask != nullptr) {
            log->debug("Enabling meter.");
            _updateTask->enable(this);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultMeter::disable() {
        if (_updateTask != nullptr) {
            log->debug("Disabling meter.");
            _updateTask->disable(this);
        }
    }

    /**
     * {@inheritDoc}
     * <p>
     * Override this if the meter can send value to the layout.
     */
    //@Override
    /*protected*/ void DefaultMeter::sendValueToLayout(double value) throw (JmriException) {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*protected*/ bool DefaultMeter::cutOutOfBoundsValues() {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultMeter::setState(int s) throw (JmriException) {
        throw UnsupportedOperationException("Not supported.");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ int DefaultMeter::getState() {
        throw UnsupportedOperationException("Not supported.");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString DefaultMeter::getBeanType() {
        return tr("Meter");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Meter::Unit DefaultMeter::getUnit() {
        return _unit;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ double DefaultMeter::getMin() {
        return _min;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ double DefaultMeter::getMax() {
        return _max;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ double DefaultMeter::getResolution() {
        return _resolution;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ AnalogIO::AbsoluteOrRelative DefaultMeter::getAbsoluteOrRelative() {
//        return (AnalogIO::AbsoluteOrRelative::TYPE)(_unit == Unit::Percent) ? AnalogIO::AbsoluteOrRelative::RELATIVE : AnalogIO::AbsoluteOrRelative::ABSOLUTE;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultMeter::dispose() {
        _updateTask->removeMeter(this);
        AbstractAnalogIO::dispose();
    }

    /**
     * Request an update from the layout.
     */
    //@Override
    /*public*/ void DefaultMeter::requestUpdateFromLayout() {
        if (_updateTask != nullptr) _updateTask->requestUpdateFromLayout();
    }


//    /**
//     * Default implementation of a voltage meter.
//     */
//    /*public*/ static class DefaultVoltageMeter extends DefaultMeter implements VoltageMeter
//    {
//        /*public*/ DefaultVoltageMeter(@Nonnull String sys, Unit unit, double min, double max, double resolution, MeterUpdateTask updateTask) {
//            super(sys, unit, min, max, resolution, updateTask);
//        }
//    }


//    /**
//     * Default implementation of a current meter.
//     */
//    /*public*/ static class DefaultCurrentMeter extends DefaultMeter implements CurrentMeter
//    {
//        /*public*/ DefaultCurrentMeter(@Nonnull String sys, Unit unit, double min, double max, double resolution, MeterUpdateTask updateTask) {
//            super(sys, unit, min, max, resolution, updateTask);
//        }
//    }


    /*private*/ /*final*/ /*static*/ Logger* DefaultMeter::log = LoggerFactory::getLogger("DefaultMeter");
