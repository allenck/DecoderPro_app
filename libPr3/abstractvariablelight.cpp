#include "abstractvariablelight.h"
#include "exceptions.h"
#include "instancemanager.h"
#include "light.h"
#include "simpletimebase.h"

//AbstractVariableLight::AbstractVariableLight(QObject *parent) :
//    AbstractLight(parent)
//{
//}
/**
 * Abstract class providing partial implementation of the logic
 * of the Light interface when the Intensity is variable.
 * <p>
 * Now it includes the transition code, but
 * it only does the steps on the fast minute clock.
 * Later it may do it's own timing but this was simple to piggy back
 * on the fast minute listener.
 * <p>
 * The structure is in part dictated by the limitations of the
 * X10 protocol and implementations. However, it is not limited to X10
 * devices only. Other interfaces that have a way to provide a dimmable
 * light should use it.
 *
 * X10 has on/off commands, and separate commands for setting
 * a variable intensity via "dim" commands.  Some X10
 * implementations use relative dimming, some use absolute dimming.
 * Some people set the dim level of their Lights and then
 * just use on/off to turn control the lamps; in that case
 * we don't want to send dim commands.  Further, X10 communications
 * is very slow, and sending a complete set of dim operations
 * can take a long time. So the algorithm is:
 * <ol>
 * <li>Until the intensity has been explicitly set different
 * from 1.0 or 0.0, no intensity commands are to be sent over
 * the power line.
 * </ul>
 * <p>
 * Unlike the parent class, this stores CurrentIntensity and TargetIntensity
 * in separate variables.
 *
 * @author	Dave Duchamp Copyright (C) 2004
 * @author	Ken Cameron Copyright (C) 2008,2009
 * @author	Bob Jacobsen Copyright (C) 2008,2009
 * @version     $Revision: 17977 $
 */
//public abstract class AbstractVariableLight extends AbstractLight
//    implements java.io.Serializable {

/*public*/ AbstractVariableLight::AbstractVariableLight(QString systemName, QString userName, QObject *parent)
 : AbstractLight(systemName, userName, parent)
{
 //super(systemName, userName);
 init();
 if (internalClock == NULL)
 {
  initClocks();
 }
}

/*public*/ AbstractVariableLight::AbstractVariableLight(QString systemName, QObject *parent) : AbstractLight(systemName, parent)
{
 //super(systemName);
 init();
 if (internalClock == NULL)
 {
  initClocks();
 }
}
void AbstractVariableLight::init()
{
 log = new Logger("AbstractVariableLight");
 mTransitionTargetIntensity = 0.0;
 mLastTransitionDate = NULL;
 mNextTransitionTs = 0;
 internalClock = NULL;
 alarmSyncUpdate = NULL;
 minuteChangeListener = NULL;
 mTransitionDuration = 0.0;
}
/**
 * Handle a request for a state change. ON and OFF
 * go to the MaxIntensity and MinIntensity, specifically, and
 * all others are not permitted
 * <p>
 * ON and OFF avoid use of variable intensity if MaxIntensity = 1.0
 * or MinIntensity = 0.0, and no transition is being used.
 */
/*public*/ void AbstractVariableLight::setState(int newState)
{
 if (log->isDebugEnabled()) log->debug("setState "+QString("%1").arg(newState)+" was "+mState);
 int oldState = mState;
 if ( newState != Light::ON && newState != Light::OFF)
        throw new IllegalArgumentException("cannot set state value "+newState);

    // first, send the on command
    sendOnOffCommand(newState);

    if (newState == Light::ON)
    {
        // see how to handle intensity
        if (getMaxIntensity() == 1.0 && getTransitionTime() <= 0)
        {
            // treat as not variable light
            if (log->isDebugEnabled()) log->debug("setState("+QString("%1").arg(newState)+") considers not variable for ON");
            // update the intensity without invoking the hardware
            notifyTargetIntensityChange(1.0);
        } else {
            // requires an intensity change, check for transition
            if (getTransitionTime() <= 0) {
                // no transition, just to directly to target using on/off
                if (log->isDebugEnabled()) log->debug("setState("+QString("%1").arg(newState)+") using variable intensity");
                // tell the hardware to change intensity
                sendIntensity(getMaxIntensity());
                // update the intensity value and listeners without invoking the hardware
                notifyTargetIntensityChange(getMaxIntensity());
            } else {
                // using transition
                startTransition(getMaxIntensity());
            }
        }
    }
    if (newState == Light::OFF) {
        // see how to handle intensity
        if (getMinIntensity() == 0.0 && getTransitionTime() <= 0) {
            // treat as not variable light
            if (log->isDebugEnabled()) log->debug("setState("+QString("%1").arg(newState)+") considers not variable for OFF");
            // update the intensity without invoking the hardware
            notifyTargetIntensityChange(0.0);
        } else {
            // requires an intensity change
            if (getTransitionTime() <= 0) {
                // no transition, just to directly to target using on/off
                if (log->isDebugEnabled()) log->debug("setState("+QString("%1").arg(newState)+") using variable intensity");
                // tell the hardware to change intensity
                sendIntensity(getMinIntensity());
                // update the intensity value and listeners without invoking the hardware
                notifyTargetIntensityChange(getMinIntensity());
            } else {
                // using transition
                startTransition(getMinIntensity());
            }
        }
    }

    // notify of state change
    notifyStateChange(oldState, newState);
}

/** Set the intended new intensity value for the Light.
*  If transitions are in use, they will be applied.
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
*  @throws IllegalArgumentException when intensity is less than 0.0 or more than 1.0
*/
/*public*/ void AbstractVariableLight::setTargetIntensity(double intensity)
{
 if (log->isDebugEnabled()) log->debug("setTargetIntensity "+QString("%1").arg(intensity));
 if (intensity<0.0 || intensity>1.0)
  throw new IllegalArgumentException("Target intensity value "+QString("%1").arg(intensity)+" not in legal range");

 // limit
 if (intensity > mMaxIntensity ) intensity = mMaxIntensity;
 if (intensity < mMinIntensity ) intensity = mMinIntensity;

 // see if there's a transition in use
 if (getTransitionTime()>0.0)
 {
  startTransition(intensity);
 } else
 {
  // No transition in use, move immediately

  // Set intensity and intermediate state
  sendIntensity(intensity);
  // update value and tell listeners
  notifyTargetIntensityChange(intensity);

  // decide if this is a state change operation
  if (intensity >= mMaxIntensity) setState(Light::ON);
  else if (intensity <= mMinIntensity) setState(Light::OFF);
  else notifyStateChange(mState, Light::INTERMEDIATE);
 }
}

/**
 * Set up to start a transition
 */
/*protected*/ void AbstractVariableLight::startTransition(double intensity)
{
        // set target value
        mTransitionTargetIntensity = intensity;

        // set state
        int nextState;
        if (intensity >= getMaxIntensity() ) nextState = Light::TRANSITIONINGTOFULLON;
        else if (intensity <= getMinIntensity() ) nextState = Light::TRANSITIONINGTOFULLOFF;
        else if (intensity >= mCurrentIntensity ) nextState = Light::TRANSITIONINGHIGHER;
        else if (intensity <= mCurrentIntensity ) nextState = Light::TRANSITIONINGLOWER;
        else nextState = Light::TRANSITIONING;  // not expected

        notifyStateChange(mState, nextState);
        // make sure clocks running to handle it
        initClocks();
}

/**
 * Send a Dim/Bright commands to the hardware
 * to reach a specific intensity.
 */
///*abstract*/ /*protected*/ void sendIntensity(double intensity);

/**
 *  Send a On/Off Command to the hardware
 */
///*abstract*/ /*protected*/ void sendOnOffCommand(int newState);


/**
 * setup internal clock, start minute listener
 */
/*private*/ void AbstractVariableLight::initClocks()
{
 if (minuteChangeListener != NULL) return; // already done

 // Create a Timebase listener for the Minute change events
 internalClock = InstanceManager::timebaseInstance();
 if (internalClock == NULL)
 {
  log->error("No Timebase Instance");
 }
 else
//    minuteChangeListener = new java.beans.PropertyChangeListener() {
//            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                //process change to new minute
//                newInternalMinute();
//            }
//        } ;
 {
  ((SimpleTimebase*)internalClock)->addMinuteChangeListener(minuteChangeListener);
  connect(internalClock, SIGNAL(minuteTick()), this, SLOT(newInternalMinute()));
 }
}

/**
 * Layout time has changed to a new minute.
 * Process effect that might be having on
 * intensity.
 * Currently, this implementation assumes there's a
 * fixed number of steps between min and max brightness.
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="FE_FLOATING_POINT_EQUALITY") // OK to compare floating point
/*protected*/ void AbstractVariableLight::newInternalMinute() // SLOT[]
{
 double origCurrent = mCurrentIntensity;
 int origState = mState;
 int steps = getNumberOfSteps();

 if ((mTransitionDuration > 0) && (steps > 0))
 {
  double stepsPerMinute = steps / mTransitionDuration;
  double stepSize = 1 / (double)steps;
  double intensityDiffPerMinute = stepSize * stepsPerMinute;
  // if we are more than one step away, keep stepping
  if (qAbs(mCurrentIntensity - mTransitionTargetIntensity) != 0)
  {
   if (log->isDebugEnabled())
   {
    log->debug("before Target: " + QString("%1").arg(mTransitionTargetIntensity) + " Current: " + QString("%1").arg(mCurrentIntensity));
   }

   if (mTransitionTargetIntensity > mCurrentIntensity)
   {
    mCurrentIntensity = mCurrentIntensity + intensityDiffPerMinute;
    if (mCurrentIntensity >= mTransitionTargetIntensity)
    {
     // Done!
     mCurrentIntensity = mTransitionTargetIntensity;
     if (mCurrentIntensity >= getMaxIntensity())
      mState = Light::ON;
     else
      mState = Light::INTERMEDIATE;
    }
   }
   else
   {
    mCurrentIntensity = mCurrentIntensity - intensityDiffPerMinute;
    if (mCurrentIntensity <= mTransitionTargetIntensity)
    {
                    // Done!
                    mCurrentIntensity = mTransitionTargetIntensity;
                    if (mCurrentIntensity <= getMinIntensity())
                        mState = Light::OFF;
                    else
                        mState = Light::INTERMEDIATE;
                }
            }

            // command new intensity
            sendIntensity(mCurrentIntensity);

            if (log->isDebugEnabled()){
                log->debug("after Target: " + QString("%1").arg(mTransitionTargetIntensity) + " Current: " + QString("%1").arg(mCurrentIntensity));
            }
        }
    }
    if (origCurrent != mCurrentIntensity) {
        firePropertyChange("CurrentIntensity", QVariant(origCurrent), QVariant(mCurrentIntensity));
        if (log->isDebugEnabled()){
            log->debug("firePropertyChange intensity " + QString("%1").arg(origCurrent) + " -> " + QString("%1").arg(mCurrentIntensity));
        }
    }
    if (origState != mState) {
        firePropertyChange("KnownState", QVariant(origState), QVariant(mState));
        if (log->isDebugEnabled()){
            log->debug("firePropertyChange intensity " + QString("%1").arg(origCurrent) + " -> " + mCurrentIntensity);
        }
    }
}

/**
 * Provide the number of steps available
 * between min and max intensity
 */
///*abstract*/ /*protected*/ int getNumberOfSteps();

/**
 * Change the stored target intensity value and do notification, but don't
 * change anything in the hardware
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="FE_FLOATING_POINT_EQUALITY") // OK to compare floating point
/*protected*/ void AbstractVariableLight::notifyTargetIntensityChange(double intensity) {
    double oldValue = mCurrentIntensity;
    mCurrentIntensity = intensity;
    if (oldValue != intensity)
        firePropertyChange("TargetIntensity", QVariant(oldValue), QVariant(intensity));
}

/** Check if this object can handle variable intensity.
 * <P>
 * @return true, as this abstract class implements
 * variable intensity.
*/
/*public*/ bool AbstractVariableLight::isIntensityVariable() {
    return true;
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
/*public*/ bool AbstractVariableLight::isTransitionAvailable() { return true; }

/**
 * Set the fast-clock duration for a
 * transition from full ON to full OFF or vice-versa.
 * <P>
 * Bound property
 * <p>
 * @throws IllegalArgumentException if minutes is not valid
 */
/*public*/ void AbstractVariableLight::setTransitionTime(double minutes) {
    if (minutes < 0.0) throw new IllegalArgumentException("Invalid transition time: " + QString("%1").arg(minutes));
    mTransitionDuration = minutes;
}

/**
 * Get the number of fastclock minutes taken by a transition from
 * full ON to full OFF or vice versa.
 * <p>
 * @return 0.0 if the output intensity transition is instantaneous
 */
/*public*/ double AbstractVariableLight::getTransitionTime() { return mTransitionDuration; }

/**
 * Convenience method for checking if the intensity of the light is currently
 * changing due to a transition.
 * <p>
 * Bound property so that listeners can conveniently learn when the transition is over.
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="FE_FLOATING_POINT_EQUALITY") // OK to compare floating point
/*public*/ bool AbstractVariableLight::isTransitioning()
{
    if (mTransitionTargetIntensity != mCurrentIntensity) {
        return true;
    } else {
        return false;
    }
}
/*protected*/ void AbstractVariableLight::forwardCommandChangeToLayout(int /*s*/) {}
/*protected*/ void AbstractVariableLight::sendIntensity(double /*intensity*/) {}
/*protected*/ void AbstractVariableLight::sendOnOffCommand(int /*newState*/) {}
/*protected*/ int AbstractVariableLight::getNumberOfSteps() { return 100; }

