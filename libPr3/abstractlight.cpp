#include "abstractlight.h"
#include "exceptions.h"
#include "light.h"

//AbstractLight::AbstractLight(QObject *parent) :
//    AbstractNamedBean(parent)
//{
//}
/**
 * Abstract class providing partial implementation of the
 *      the Light interface.
 * <P>
 * Light objects require a number of instance variables.  Since
 *     Light objects are created using the standard JMRI
 *     systemName/userName concept, accessor routines are provided
 *     for setting and editting these instance variables.
 * <P>
 * Each Light may have one or more control mechanisms, of the
 *		types defined in the Light interface. A Light may also not
 *		have any control mechanisms defined.
 * <P>
 * Information for each control mechanism is held in LightControl
 *		objects, which also implement the logic for control. A
 *		list of LightControls, if any, is kept here, and
 *		activation and deactivation of LightControls is through
 *		this module.
 * <P>
 * Instance variables are divided into system-independent and
 *    system dependent categories.  System independent instance
 *    variables are defined here, and their accessor routines are
 *    implemented here.
 * <p>
 * This implementation provides a notional implementation of
 * intensity and transitions.  The user can set intensity
 * so long as it's at least the max value (default 1.0) or
 * no more than the minimum value (default 0.0). In that case,
 * the setTargetIntensity operations become a setState to ON
 * or OFF.  Setting a target intensity between the min and max
 * is an error, because this type of Light does not support
 * a true analog intensity.
 * Transitions never happen, and setting a TransitionTime
 * greater than 0.0 gives an exception.
 * <p>
 * Since this form of Light does not do variable intensity
 * nor transitions, it stores both CurrentIntensity and
 * TargetIntensity in a single location, forcing them to be the same
 *
 * @author	Dave Duchamp Copyright (C) 2004, 2010
 * @author	Ken Cameron Copyright (C) 2008
 * @author	Bob Jacobsen Copyright (C) 2008
 * @version     $Revision: 17977 $
 */
//public abstract class AbstractLight extends AbstractNamedBean
//    implements Light, java.io.Serializable {

/*public*/ AbstractLight::AbstractLight(QString systemName, QString userName, QObject *parent)
 : Light(systemName.toUpper(), userName, parent)
{
 //super(systemName.toUpperCase(), userName);
 common();
}

/*public*/ AbstractLight::AbstractLight(QString systemName,QObject *parent)
 : Light(systemName.toUpper(), parent)
{
 //super(systemName.toUpperCase());
 common();
}

void AbstractLight::common()
{
 log = new Logger("AbstractLight");
 /**
  *  System independent instance variables (saved between runs)
  */
 lightControlList = QList<LightControl*>();
 mMaxIntensity = 1.0;
 mMinIntensity = 0.0;

 /**
  *  System independent operational instance variables (not saved between runs)
  */
 mActive = false;
 mEnabled = true;
 mCurrentIntensity = 0.0;
 mState = Light::OFF;

}

/**
 * Get enabled status
*/
/*public*/ bool AbstractLight::getEnabled() { return mEnabled; }
/**
 * Set enabled status
 */
/*public*/ void AbstractLight::setEnabled(bool v) {
    bool old = mEnabled;
    mEnabled = v;
    if (old != v) firePropertyChange("Enabled", QVariant(old), QVariant(v));
}

/** Check if this object can handle variable intensity.
 * <P>
 * @return false, as this abstract class does not implement
 * variable intensity. See e.g. {@link AbstractVariableLight} for
 * an abstract implementation of variable intensity.
*/
/*public*/ bool AbstractLight::isIntensityVariable() {
    return false;
}

/** Set the intended new intensity value for the Light.
*  <p>
*  Bound property between 0 and 1.
*  <p>
*  A value of 0.0 corresponds to full off, and
*  a value of 1.0 corresponds to full on.
*  <p>
*  Values at or below
*  the minIntensity property will result in the Light going
*  to the OFF state immediately.
*  Values at or above the maxIntensity property
*  will result in the Light going to the ON state immediately.
*  <p>
*  All others result in an exception, instead of the
*  INTERMEDIATE state, because this class does not implement analog intensity
*  <P>
*  @throws IllegalArgumentException when intensity is less than 0.0 or more than 1.0
*  @throws IllegalArgumentException when intensity is more than MinIntensity and less than MaxIntensity
*/
/*public*/ void AbstractLight::setTargetIntensity(double intensity) {
    if (log->isDebugEnabled()) log->debug(tr("setTargetIntensity ")+QString("%1").arg(intensity));
    if (intensity<0.0 || intensity>1.0)
        throw new IllegalArgumentException("Target intensity value "+QString("%1").arg(intensity)+" not in legal range");

    // limit
    if (intensity > mMaxIntensity ) intensity = mMaxIntensity;
    if (intensity < mMinIntensity ) intensity = mMinIntensity;

    // move directly to target, if possible
    if (intensity >= mMaxIntensity) {
        updateIntensityHigh(intensity);
    } else if (intensity <= mMinIntensity) {
        updateIntensityLow(intensity);
    } else {
        updateIntensityIntermediate(intensity);
    }
}

/**
 * Method for further implementation of
 * setTargetIntensity at or below the minimum.
 * <p>
 * Does not change state.
 */
/*protected*/ void AbstractLight::updateIntensityLow(double intensity) {
    notifyTargetIntensityChange(intensity);
    setState(Light::OFF);
}

/**
 * Method for further implementation of
 * setTargetIntensity between min and max
 * <p>
 * Does not change state.
 */
/*protected*/ void AbstractLight::updateIntensityIntermediate(double intensity) {
    // not in value range!
//    throw new IllegalArgumentException("intensity value "+QString("%1").arg(intensity)+" between min "+QString::number(mMinIntensity)+" and max "+QString::number(mMaxIntensity));
 notifyTargetIntensityChange(intensity);
 setState(Light::ON);

}

/**
 * Method for further implementation of
 * setTargetIntensity at or above the maximum
 * <p>
 * Does not change state.
 */
/*protected*/ void AbstractLight::updateIntensityHigh(double intensity) {
    notifyTargetIntensityChange(intensity);
    setState(Light::ON);
}

/** Get the current intensity value.
 * If the Light is currently transitioning, this may be either
 * an intermediate or final value.
 * <p>
 * A value of 0.0 corresponds to full off, and
 * a value of 1.0 corresponds to full on.
*/
/*public*/ double AbstractLight::getCurrentIntensity() {
    return mCurrentIntensity;
}

/** Get the target intensity value for the
 * current transition, if any. If the Light is not currently
 * transitioning, this is the current intensity value.
 * <p>
 * A value of 0.0 corresponds to full off, and
 * a value of 1.0 corresponds to full on.
 * <p>
 * Bound property
*/
/*public*/ double  AbstractLight::getTargetIntensity() {
    return mCurrentIntensity;
}

/** Set the value of the maxIntensity property.
 * <p>
 * Bound property between 0 and 1.
 * <p>
 * A value of 0.0 corresponds to full off, and
 * a value of 1.0 corresponds to full on.
 * @throws IllegalArgumentException when intensity is less than 0.0 or more than 1.0
 * @throws IllegalArgumentException when intensity is not greater than the current value of the minIntensity property
*/
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="FE_FLOATING_POINT_EQUALITY") // OK to compare floating point
/*public*/ void AbstractLight::setMaxIntensity(double intensity) {
    if (intensity<0.0 || intensity>1.0)
        throw  IllegalArgumentException("Illegal intensity value: "+QString("%1").arg(intensity));
    if (intensity <= mMinIntensity)
    {
     log->error("Requested intensity "+QString("%1").arg(intensity)+" not less than minIntensity "+mMinIntensity);
     throw  IllegalArgumentException("Requested intensity "+QString("%1").arg(intensity)+" not less than minIntensity "+mMinIntensity);
    }

    double oldValue = mMaxIntensity;
    mMaxIntensity = intensity;

    if (oldValue != intensity)
        firePropertyChange("MaxIntensity", QVariant(oldValue), QVariant(intensity));
}

/** Get the current value of the maxIntensity property.
 * <p>
 * A value of 0.0 corresponds to full off, and
 * a value of 1.0 corresponds to full on.
*/
/*public*/ double AbstractLight::getMaxIntensity() {
    return mMaxIntensity;
}

/** Set the value of the minIntensity property.
 * <p>
 * Bound property between 0 and 1.
 * <p>
 * A value of 0.0 corresponds to full off, and
 * a value of 1.0 corresponds to full on.
 * @throws IllegalArgumentException when intensity is less than 0.0 or more than 1.0
 * @throws IllegalArgumentException when intensity is not less than the current value of the maxIntensity property
*/
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="FE_FLOATING_POINT_EQUALITY") // OK to compare floating point
/*public*/ void AbstractLight::setMinIntensity(double intensity) {
    if (intensity<0.0 || intensity>1.0)
        throw  IllegalArgumentException("Illegal intensity value: "+QString("%1").arg(intensity));
    if (intensity >= mMaxIntensity)
        throw  IllegalArgumentException("Requested intensity "+QString("%1").arg(intensity)+" not more than maxIntensity "+mMaxIntensity);

    double oldValue = mMinIntensity;
    mMinIntensity = intensity;

    if (oldValue != intensity)
        firePropertyChange("MinIntensity", QVariant(oldValue), QVariant(intensity));
}

/**
 * Get the current value of the minIntensity property.
 * <p>
 * A value of 0.0 corresponds to full off, and
 * a value of 1.0 corresponds to full on.
 */
/*public*/ double AbstractLight::getMinIntensity() {
    return mMinIntensity;
}

/**
 * Can the Light change it's intensity setting slowly?
 * <p>
 * If true, this Light supports a non-zero value of the
 * transitionTime property, which controls how long the Light
 * will take to change from one intensity level to another.
 * <p>
 * Unbound property
 */
/*public*/ bool AbstractLight::isTransitionAvailable() { return false; }

/**
 * Set the fast-clock duration for a
 * transition from full ON to full OFF or vice-versa.
 * <P>
 * This class does not implement transitions, so this property
 * cannot be set from zero.
 * <p>
 * Bound property
 * <p>
 * @throws IllegalArgumentException if minutes is not 0.0
 */
/*public*/ void AbstractLight::setTransitionTime(double minutes) {
    if (minutes != 0.0) throw new IllegalArgumentException("Illegal transition time: "+QString("%1").arg(minutes));
}

/**
 * Get the number of fastclock minutes taken by a transition from
 * full ON to full OFF or vice versa.
 * <p>
 * @return 0.0 if the output intensity transition is instantaneous
 */
/*public*/ double AbstractLight::getTransitionTime() { return 0.0; }

/**
 * Convenience method for checking if the intensity of the light is currently
 * changing due to a transition.
 * <p>
 * Bound property so that listeners can conveniently learn when the transition is over.
 */
/*public*/ bool AbstractLight::isTransitioning() { return false; }

/**
 * Handle a request for a state change. For these lights,
 * ON and OFF just transition immediately
 * between MinIntensity and MaxIntensity
 */
/*public*/ void AbstractLight::setState(int newState)
{
 if (log->isDebugEnabled()) log->debug("setState "+QString("%1").arg(newState)+" was "+mState);
    //int oldState = mState;
 if ( newState != Light::ON && newState != Light::OFF)
  throw  IllegalArgumentException("cannot set state value "+QString("%1").arg(newState));
 double intensity = getTargetIntensity();
 if (newState == Light::ON && intensity < getMaxIntensity() )
 {
  setTargetIntensity(getMaxIntensity());
  // stop if state change was done as part of setTargetIntensity
  if (getState() == Light::ON) return;
 }
 if (newState == Light::OFF && intensity > getMinIntensity() )
 {
  setTargetIntensity(getMinIntensity());
  // stop if state change was done as part of setTargetIntensity
  if (getState() == Light::OFF) return;
 }
 // do the state change in the hardware
 doNewState(mState, newState); // old state, new state
    // change value and tell listeners
 notifyStateChange(mState, newState);
}

/**
 * Change the stored target intensity value and do notification, but don't
 * change anything in the hardware
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="FE_FLOATING_POINT_EQUALITY") // OK to compare floating point
/*protected*/ void AbstractLight::notifyTargetIntensityChange(double intensity)
{
 double oldValue = mCurrentIntensity;
 mCurrentIntensity = intensity;
 if (oldValue != intensity)
  firePropertyChange("TargetIntensity", QVariant(oldValue), QVariant(intensity));
}

/**
 * Change the stored state value and do notification, but don't
 * change anything in the hardware
 */
/*protected*/ void AbstractLight::notifyStateChange(int oldState, int newState)
{
 mState = newState;
 if (oldState!=newState)
  firePropertyChange("KnownState", QVariant(oldState), QVariant(newState));
 //emit propertyChange("KnownState", oldState, newState);
}

/**
 * Implement the specific change of state needed by hardware
 */
/*protected*/ void AbstractLight::doNewState(int /*oldState*/, int /*newState*/) {}

/*public*/ int AbstractLight::getState() {
    return mState;
}

/**
 * Activates a light activating all its LightControl objects.
 */
/*public*/ void AbstractLight::activateLight() {
    for (int i = 0; i<lightControlList.size(); i++) {
        LightControl* lc = lightControlList.at(i);
        lc->activateLightControl();
    }
}

/**
 * Deactivates a light by deactivating each of its LightControl objects.
 */
/*public*/ void AbstractLight::deactivateLight() {
    // skip if Light is not active
    if (mActive) {
        for (int i = 0; i<lightControlList.size(); i++) {
            LightControl* lc = lightControlList.at(i);
            lc->deactivateLightControl();
        }
        mActive = false;
    }
}

/**
 * LightControl management methods
 */
/*public*/ void AbstractLight::clearLightControls() {
    // deactivate all Light Controls if any are active
    deactivateLight();
    // clear all LightControls, if there are any
    for (int i = lightControlList.size()-1; i>=0; i--) {
        lightControlList.removeAt(i);
    }
}
/*public*/ void AbstractLight::addLightControl(LightControl* c)
{
    lightControlList.append(c);
}
/*public*/ QList<LightControl*>* AbstractLight::getLightControlList()
{
 QList<LightControl*>* listCopy =  new  QList<LightControl*>();
 for (int i = 0; i<lightControlList.size() ; i++)
 {
  listCopy->append(lightControlList.at(i));
 }
 return listCopy;
}

