#include "layout.h"
#include "loggerfactory.h"
#include "scale.h"
#include "timetabledatamanager.h"
#include "timetableframe.h"
#include "timetable/tttrain.h"
#include "timetable/ttschedule.h"
#include "instancemanager.h"
#include "timetablexml.h"

namespace TimeTable
{

/**
 * Define the content of a Layout record.
 * <p>
 * The fast clock, scale and metric values affect the scale mile / scale km.
 * When these are changed, the stop times for all of the trains have to be
 * re-calculated.  Depending on the schedule limits, this can result in
 * calculation errors.  When this occurs, exceptions occur which trigger
 * rolling back the changes.
 * @author Dave Sand Copyright (C) 2018
 */
// /*public*/ class Layout implements VetoableChangeListener {

    /*public*/ /*static*/ /*final*/ QString Layout::SCALE_RATIO = "ScaleRatio";

    /**
     * Create a new layout with default values.
     */
    /*public*/ Layout::Layout(QObject *parent) : QObject(parent) {
     _dm = TimeTableDataManager::getDataManager();

        _layoutId = _dm->getNextId("Layout");  // NOI18N
        _dm->addLayout(_layoutId, this);
        _scale->addVetoableChangeListener(SCALE_RATIO, (VetoableChangeListener*)this);  // NOI18N
        setScaleMK();
    }

    /*public*/ Layout::Layout(int layoutId, QString layoutName, Scale *scale, int fastClock, int throttles, bool metric, QObject *parent) : QObject(parent) {
     _dm = TimeTableDataManager::getDataManager();
        _layoutId = layoutId;
        setLayoutName(layoutName);
        setScale(scale);
        setFastClock(fastClock);
        setThrottles(throttles);
        setMetric(metric);
    }

    /**
     * Calculate the length of a scale mile or scale kilometer.
     * The values are adjusted for scale and fast clock ratio.
     * The resulting value is the real feet or meters.
     * The final step is to re-calculate the train times.
     * @throws IllegalArgumentException The calculate can throw an exception which will get re-thrown.
     */
    /*public*/ void Layout::setScaleMK() {
        double distance = (_metric) ? 1000 : 5280;
        _scaleMK = distance / _ratio / _fastClock;
        log->debug(tr("scaleMK = %1, scale = %2").arg(_scaleMK).arg(_scale->getScaleName()));  // NOI18N

        _dm->calculateLayoutTrains(getLayoutId(), false);
        _dm->calculateLayoutTrains(getLayoutId(), true);
    }

    /*public*/ double Layout::getScaleMK() {
        return _scaleMK;
    }

    /*public*/ int Layout::getLayoutId() {
        return _layoutId;
    }

    /*public*/ QString Layout::getLayoutName() {
        return _layoutName;
    }

    /*public*/ void Layout::setLayoutName(QString newName) {
        _layoutName = newName;
    }

    /*public*/ double Layout::getRatio() {
        return _ratio;
    }

    /*public*/ Scale* Layout::getScale() {
        return _scale;
    }

    /*public*/ void Layout::setScale(Scale* newScale) {
        _scale->removeVetoableChangeListener(SCALE_RATIO, (VetoableChangeListener*)this);  // NOI18N
        if (newScale == nullptr) {
            newScale = ScaleManager::getScale("HO");  // NOI18N
            log->warn("No scale found, defaulting to HO");  // NOI18N
        }

        Scale* oldScale = _scale;
        double oldRatio = _ratio;
        _scale = newScale;
        _ratio = newScale->getScaleRatio();

        try {
            // Update the smile/skm which includes stop recalcs
            setScaleMK();
        } catch (IllegalArgumentException* ex) {
            _scale = oldScale;  // roll back scale and ratio
            _ratio = oldRatio;
            setScaleMK();
            throw ex;
        }
        _scale->addVetoableChangeListener(SCALE_RATIO, (VetoableChangeListener*)this);  // NOI18N
    }

    /*public*/ int Layout::getFastClock() {
        return _fastClock;
    }

    /**
     * Set a new fast clock speed, update smile/skm.
     * @param newClock The value to be used.
     * @throws IllegalArgumentException (CLOCK_LT_1) if the value is less than 1.
     * will also re-throw a recalc error.
     */
    /*public*/ void Layout::setFastClock(int newClock) {
        if (newClock < 1) {
            throw  IllegalArgumentException(TimeTableDataManager::CLOCK_LT_1);
        }
        int oldClock = _fastClock;
        _fastClock = newClock;

        try {
            // Update the smile/skm which includes stop recalcs
            setScaleMK();
        } catch (IllegalArgumentException* ex) {
            _fastClock = oldClock;  // roll back
            setScaleMK();
            throw ex;
        }
    }

    /*public*/ int Layout::getThrottles() {
        return _throttles;
    }

    /**
     * Set the new value for throttles.
     * @param newThrottles The new throttle count.
     * @throws IllegalArgumentException (THROTTLES_USED, THROTTLES_LT_0) when the
     * new count is less than train references or a negative number was passed.
     */
    /*public*/ void Layout::setThrottles(int newThrottles) {
        if (newThrottles < 0) {
            throw new IllegalArgumentException(TimeTableDataManager::THROTTLES_LT_0);
        }
        for (TTSchedule* schedule : _dm->getSchedules(_layoutId, true)) {
            for (TTTrain* train : _dm->getTrains(schedule->getScheduleId(), 0, true)) {
                if (train->getThrottle() > newThrottles) {
                    throw  IllegalArgumentException(TimeTableDataManager::THROTTLES_IN_USE);
                }
            }
        }
        _throttles = newThrottles;
    }

    /*public*/ bool Layout::getMetric() {
        return _metric;
    }

    /**
     * Set metric flag, update smile/skm.
     * @param newMetric True for metric units.
     * @throws IllegalArgumentException if there was a recalc error.
     */
    /*public*/ void Layout::setMetric(bool newMetric) {
        bool oldMetric = _metric;
        _metric = newMetric;

        try {
            // Update the smile/skm which includes stop recalcs
            setScaleMK();
        } catch (IllegalArgumentException* ex) {
            _metric = oldMetric;  // roll back
            setScaleMK();
            throw ex;
        }
    }

    //@Override
    /*public*/ QString Layout::toString() {
        return _layoutName;
    }

    /**
     * Listen for ratio changes to my current scale.  Verify that the new ratio
     * is neither too small nor too large.  Too large can cause train times to move
     * outside of the schedule window.  If the new ratio is invalid, the change
     * will be vetoed.
     * @param evt The scale ratio property change event.
     * @throws PropertyVetoException The message will depend on the actual error.
     */
    //@Override
    /*public*/ void Layout::vetoableChange(PropertyChangeEvent* evt) /*throw (PropertyVetoException)*/ {
        log->debug(tr("scale change event: layout = %1, evt = %2").arg(_layoutName).arg(evt->toString()));
        double newRatio =  evt->getNewValue().toDouble();
        if (newRatio < 1.0) {
            throw PropertyVetoException("Ratio is less than 1", evt);
        }

        double oldRatio = _ratio;
        _ratio = newRatio;

        try {
            // Update the smile/skm which includes stop recalcs
            setScaleMK();
        } catch (IllegalArgumentException* ex) {
            // Roll back the ratio change
            _ratio = oldRatio;
            setScaleMK();
            throw PropertyVetoException("New ratio causes calc errors", evt);
        }

        TimeTableFrame* frame = (TimeTableFrame*)InstanceManager::getNullableDefault("TimeTableFrame");
        if (frame != nullptr) {
            frame->setShowReminder(true);
        } else {
            // Save any changes
            TimeTableXml::doStore();
        }
    }

    /*private*/ /*static*/ /*final*/ Logger* Layout::log = LoggerFactory::getLogger("Layout");

}
