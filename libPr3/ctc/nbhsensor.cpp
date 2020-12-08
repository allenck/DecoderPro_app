#include "nbhsensor.h"
#include "namedbeanhandlemanager.h"
#include "instancemanager.h"
#include "projectscommonsubs.h"
#include "ctcmanager.h"

/**
 * This object attempts to "extend" (implements) Sensor functionality that
 * is needed by the CTC system.
 * <p>
 * Goals:
 * <ol>
 * <li> Catches and thereby prevents exceptions from propagating upward.  No need
 *     for this everywhere in your code:
 *     try { sensor.getBean().setKnownState(Sensor.ACTIVE); } catch (JmriException ex) {}
 *     We ASSUME here that you are ALWAYS passing a valid "newState".  If not,
 *     then this call is effectively a no-op (do nothing).
 * <li> Use ONLY named beans internally for proper JMRI support of renaming objects.
 * <li> Allow any CTC Editor routines to mindlessly change the underlying sensor
 *     name used WITHOUT affecting any existing run time (CTCRunTime) code.
 *     For example: User changes existing IS:XYZ to IS:ABC, which is a different
 *     sensor altogether.  Everything happens under the covers, and the higher
 *     level code that uses these objects do not know the change happened, and
 *     they SHOULD continue to function without affect.
 * <li> Prevents "null" access to improperly constructed internal objects.  For example:
 *     If the caller passes invalid parameter(s) to the constructor(s), then this object's
 *     internal Sensor will be set to null by the constructor(s).  If the USER then
 *     attempts to use the CTC panel and the underlying code winds up calling method(s)
 *     in here that reference that null sensor, the JMRI system would crash.
 * <li> If the internal Sensor is null and you call a function that returns a value,
 *     that function will return a "sane" value.  See the constants below for
 *     general return values in this situation and individual functions for specific info.
 * <li> Support for required sensors.  If the sensor name doesn't exist or is invalid in ANY way,
 *     then it is considered an error, and this object logs it as such.  We do
 *     NOT create the JMRI object automatically in this situation.
 * <li> Support for optional sensors.  In my system, a sensor may be optional.
 *     If specified, it MUST be valid and exist in the system already.
 * <li> In each of the two above situations, ANY error situation will leave
 *     this object properly protected.
 * <li> My CTC system that uses this object can "mindlessly" call methods on this
 *     object at any time, and return "sane" values in ANY error situation and
 *     rely on these values being consistent.  This prevents the need of calling
 *     routines to CONSTANTLY check the internal status of this object, and can
 *     rely on those "sane" return values.  I'm a lazy programmer, and want to
 *     prevent the following at the call site:
 *     int blah;
 *     if (NBHSensor.valid()) blah = NBHSensor.getKnownState();
 *     or
 *     try { blah = NBHSensor.getKnownState()} catch() {}
 *     it becomes just:
 *     blah = NBHSensor.getKnownState();
 *     You may (and I do) have specific circumstances whereby you need to know
 *     the internal state of this object is valid or not, and act on
 *     it differently than the default sane values.  There is a function "valid()"
 *     for that situation.
 * </ol>
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019, 2020
 */

// Prefix NBH = Named Bean Handler....

// /*public*/ class NBHSensor {
//  Special case sane return values:
    /*public*/ /*static*/ /*final*/ int NBHSensor::DEFAULT_SENSOR_STATE_RV = Sensor::INACTIVE;
//  Standard sane return values for the types indicated:
//  /*public*/ static final Object DEFAULT_OBJECT_RV = null;       // For any function that returns something derived from Java's Object.
//  /*public*/ static final boolean DEFAULT_BOOLEAN_RV = false;    // For any function that returns boolean.
//  /*public*/ static final int DEFAULT_INT_RV = 0;                // For any function that returns int.
//  /*public*/ static final long DEFAULT_LONG_RV = 0;              // For any function that returns long.
//  /*public*/ static final String DEFAULT_STRING_RV = "UNKNOWN";  // NOI18N  For any function that returns String.
//  Functions that don't return any of the above have specific implementations.  Ex: PropertyChangeListener[] or ArrayList<>

//  The "thing" we're protecting:
    /*public*/ Sensor* NBHSensor::getBean() {
        if (valid()) return _mNamedBeanHandleSensor->getBean();
        return nullptr;
    }

    /*public*/ NamedBeanHandle<NamedBean *> *NBHSensor::getBeanHandle() {
        if (valid()) return (NamedBeanHandle<NamedBean *> *)_mNamedBeanHandleSensor;
        return nullptr;
    }

    /*public*/ bool NBHSensor::matchSensor(Sensor* sensor) {
        if (valid()) return (Sensor*)_mNamedBeanHandleSensor->getBean() == sensor;
        return false;
    }

    /*public*/ NBHSensor::NBHSensor(QString module, QString userIdentifier, QString parameter, QString sensor, bool optional,  QObject* parent) : QObject(parent){
        _mUserIdentifier = userIdentifier;
        _mParameter = parameter;
        _mOptional = optional;
        Sensor* tempSensor = _mOptional ? getSafeOptionalJMRISensor(module, userIdentifier, _mParameter, sensor) : getSafeExistingJMRISensor(module, userIdentifier, _mParameter, sensor);
        if (tempSensor != nullptr) {
            _mNamedBeanHandleSensor = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensor, tempSensor);
        } else {
            _mNamedBeanHandleSensor = nullptr;
        }
        registerSensor(sensor);
    }

    /*public*/ NBHSensor::NBHSensor(QString module, QString userIdentifier, QString parameter, QString sensorName, QObject* parent) : QObject(parent){
        _mUserIdentifier = userIdentifier;
        _mParameter = parameter;
        _mOptional = false;

        Sensor* tempSensor = getSafeInternalSensor(module, userIdentifier, parameter, sensorName);
        if (tempSensor != nullptr) {
            _mNamedBeanHandleSensor = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, tempSensor);
        } else {
            _mNamedBeanHandleSensor = nullptr;
        }
        registerSensor(sensorName);
    }

    void NBHSensor::registerSensor(QString sensorName) {
        if (valid()) ((CtcManager*)InstanceManager::getDefault("CtcManager"))->putNBHSensor(sensorName, this);
    }

//  Used by CallOn to create a temporary NBHSensor for the current sensor for a block.
    /*public*/ NBHSensor::NBHSensor(NamedBeanHandle<Sensor*>* namedBeanHandleSensor) {
        _mUserIdentifier = tr("Unknown");    // NOI18N
        _mParameter = _mUserIdentifier;
        _mOptional = true;              // We CAN'T know, but this is safe.
        _mNamedBeanHandleSensor = namedBeanHandleSensor;
    }

    /*public*/ bool NBHSensor::valid() { return _mNamedBeanHandleSensor != nullptr; }  // For those that want to know the internal state.

    /*private*/ /*static*/ Sensor* NBHSensor::getSafeExistingJMRISensor(QString module, QString userIdentifier, QString parameter, QString sensor) {
        try { return getExistingJMRISensor(module, userIdentifier, parameter, sensor); } catch (CTCException e) { e.logError(); }
        return nullptr;
    }

    /*private*/ /*static*/ Sensor* NBHSensor::getSafeOptionalJMRISensor(QString module, QString userIdentifier, QString parameter, QString sensor) {
        try { return getOptionalJMRISensor(module, userIdentifier, parameter, sensor); } catch (CTCException e) { e.logError(); }
        return nullptr;
    }

    /*private*/ /*static*/ Sensor* NBHSensor::getSafeInternalSensor(QString module, QString userIdentifier, QString parameter, QString sensor) {
        try { return getInternalSensor(module, userIdentifier, parameter, sensor); } catch (CTCException e) { e.logError(); }
        return nullptr;
    }

//  sensor is NOT optional and cannot be null.  Raises Exception in ALL error cases.
    /*private*/ /*static*/ Sensor* NBHSensor::getExistingJMRISensor(QString module, QString userIdentifier, QString parameter, QString sensor) throw (CTCException) {
        if (!ProjectsCommonSubs::isNullOrEmptyString(sensor)) {
            // Cannot use a constant Instance manager reference due to the dynamic nature of tests.
            Sensor* returnValue = ((SensorManager*)InstanceManager::getDefault("SensorManager"))->getSensor(sensor);
            if (returnValue == nullptr) { throw  CTCException(module, userIdentifier, parameter, tr("Sensor does not exist:") + " " + sensor); }  // NOI18N
            return returnValue;
        } else { throw CTCException(module, userIdentifier, parameter, tr("Required sensor missing")); }  // NOI18N
    }

//  sensor is optional, but must exist if given.  Raises Exception in ALL error cases.
    /*private*/ /*static*/ Sensor* NBHSensor::getOptionalJMRISensor(QString module, QString userIdentifier, QString parameter, QString sensor) throw (CTCException) {
        if (!ProjectsCommonSubs::isNullOrEmptyString(sensor)) {
            // Cannot use a constant Instance manager reference due to the dynamic nature of tests.
            Sensor* returnValue = ((SensorManager*)InstanceManager::getDefault("SensorManager"))->getSensor(sensor);
            if (returnValue == nullptr) { throw  CTCException(module, userIdentifier, parameter, tr("Sensor does not exist") + " " + sensor); }  // NOI18N
            return returnValue;
        } else { return nullptr; }
    }

// Special case for CTC internal sensors.  These are not always predefined so the provide() method is used.
    /*private*/ /*static*/ Sensor* NBHSensor::getInternalSensor(QString module, QString userIdentifier, QString parameter, QString sensor) throw (CTCException) {
        if (!ProjectsCommonSubs::isNullOrEmptyString(sensor)) {
            // Cannot use a constant Instance manager reference due to the dynamic nature of tests.
            return ((SensorManager*)InstanceManager::getDefault("SensorManager"))->provide(sensor);
        } else { return nullptr; }
    }

    /*public*/ int NBHSensor::getKnownState() {
        if (_mNamedBeanHandleSensor == nullptr) return DEFAULT_SENSOR_STATE_RV;
        return _mNamedBeanHandleSensor->getBean()->getKnownState();
    }

    //@SuppressFBWarnings(value = "DE_MIGHT_IGNORE", justification = "Let it not do anything if it fails.")
    /*public*/ void NBHSensor::setKnownState(int newState) {
        if (_mNamedBeanHandleSensor == nullptr) return;
        try { _mNamedBeanHandleSensor->getBean()->setKnownState(newState); } catch (JmriException ex) {}
    }


    /*public*/ void NBHSensor::addPropertyChangeListener(PropertyChangeListener* propertyChangeListener) {
        if (_mNamedBeanHandleSensor == nullptr) return;
        _mNamedBeanHandleSensor->getBean()->addPropertyChangeListener(propertyChangeListener);
        _mArrayListOfPropertyChangeListeners.append(propertyChangeListener);
    }

    /*public*/ void NBHSensor::removePropertyChangeListener(PropertyChangeListener* propertyChangeListener) {
        if (_mNamedBeanHandleSensor == nullptr) return;
        _mNamedBeanHandleSensor->getBean()->removePropertyChangeListener(propertyChangeListener);
        _mArrayListOfPropertyChangeListeners.removeOne(propertyChangeListener);
    }

//  Support for "Grand Unification" (Editor support):


    /**
     * @return The sensor's handle name.
     */
    /*public*/ QString NBHSensor::getHandleName() {
        return valid() ? _mNamedBeanHandleSensor->getName() : "";
    }

    /**
     * For Unit testing only.
     * @return Returns the present number of property change listeners registered with us so far.
     */
    /*public*/ int NBHSensor::testingGetCountOfPropertyChangeListenersRegistered() {
        return _mArrayListOfPropertyChangeListeners.size();
    }
