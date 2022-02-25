#ifndef LIGHT_H
#define LIGHT_H
#include "abstractnamedbean.h"
//#include "lightcontrol.h"
#include "digitalio.h"

class LightControl;
class Light :  /* public AbstractNamedBean,*/ public DigitalIO, public virtual NamedBean
{
    //Q_OBJECT
  Q_INTERFACES(NamedBean DigitalIO)
public:
//  explicit Light(QObject *parent = 0) : AbstractNamedBean(parent) {}
//  Light(QString sysName, QObject* parent=0) : AbstractNamedBean(sysName, parent) {}
//  Light(QString sysName, QString userName, QObject* parent=0) : AbstractNamedBean(sysName, userName, parent) {}


    /**
     * Represent a single visible Light on the physical layout.
     * <p>
     * Each Light may have one or more control mechanisms.  Control mechanism
     *	types are defined here.  If a Light has any controls, the information
     *	is contained in LightControl objects, which are referenced via
     *	that Light.
     * <p>
     * Lights have a state and an intensity.
     * <p>
     * The intensity
     * of the hardware output is represented by the range from 0.0
     * to 1.0, with 1.0 being brightest.
     * <p>
     * The primary states are:
     * <ul>
     * <li>ON, corresponding to maximum intensity
     * <LI>INTERMEDIATE, some value between maximum and minimum
     * <li>OFF, corresponding to minimum intensity
     * </ul>
     * The underlying hardware may provide just the ON/OFF two levels,
     * or have a semi-continuous intensity setting with some number of steps.
     * <p>
     * The light has a TargetIntensity property which can be set directly.
     * In addition, it has a CurrentIntensity property which may differ
     * from TargetIntensity while the Light is being moved from one intensity to another.
     * <p>
     * Intensity is limited by MinIntensity and MaxIntensity parameters.
     * Setting the state to ON sets the TargetIntensity to MinIntensity, and
     * to OFF sets the TargetIntensity to MaxIntensity. Attempting to
     * directly set the TargetIntensity outside the values of MinIntensity and MaxIntensity
     * (inclusive) will result in the TargetIntensity being set to the relevant limit.
     * <p>
     * Because the actual light hardware has only finite resolution, the
     * intensity value is mapped to the nearest setting.
     * For example, in the special case of a two-state (on/off) Light,
     * setting a TargetIntensity of more than 0.5 will turn the Light on,
     * less than 0.5 will turn the light off.
     * <p>
     * Specific implementations will describe how the settings map to the
     * particular hardware commands.
     * <p>
     * The transition rate is absolute; the intensity changes at a constant rate
     * regardless of whether the change is a big one or a small one.
     *
     * <hr>
     * This file is part of JMRI.
     * <P>
     * JMRI is free software; you can redistribute it and/or modify it under
     * the terms of version 2 of the GNU General Public License as published
     * by the Free Software Foundation. See the "COPYING" file for a copy
     * of this license.
     * <P>
     * JMRI is distributed in the hope that it will be useful, but WITHOUT
     * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
     * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
     * for more details.
     * <P>
     * @author			Dave Duchamp Copyright (C) 2004, 2010
     * @author			Ken Cameron Copyright (C) 2008
     * @author			Bob Jacobsen Copyright (C) 2008
     * @version			$Revision: 17977 $
     */
    //virtual interface Light extends NamedBean {
    enum STATES
    {
     /**
         * Constant representing an "unknown" state, indicating that the object's
         * state is not necessarily that of the actual layout hardware. This is the
         * initial state of a newly created object before communication with the
         * layout.
         */
        /*public static final int*/ UNKNOWN = 0x01,

        /**
         * Constant representing an "inconsistent" state, indicating that some
         * inconsistency has been detected in the hardware readback.
         */
        /*public static final int*/ INCONSISTENT = 0x08,

        /** State value indicating output intensity is at or above maxIntensity */
        /*const static int*/ ON          = 0x02,

        /** State value indicating output intensity is at or below minIntensity */
        /*const static int*/ OFF         = 0x04,

        /** State value indicating output intensity is
         * less than maxIntensity and more than minIntensity,
         * and no transition is in progress */
        /*const static int*/ INTERMEDIATE         = 0x08,


        /** State value indicating output intensity is currently changing toward higher intensity, and will
            continue until full ON is reached */
        /*const static int*/ TRANSITIONINGTOFULLON   = 0x310,

        /** State value indicating output intensity is currently changing toward higher intensity. The current
            transition will stop before full ON is reached. */
        /*const static int*/ TRANSITIONINGHIGHER 	      = 0x210,

        /** State value indicating output intensity is currently changing toward lower intensity. The current
            transition will stop before full OFF is reached. */
        /*const static int*/ TRANSITIONINGLOWER        = 0x110,

        /** State value indicating output intensity is currently changing toward lower intensity, and will
            continue until full OFF is reached */
        /*const static int*/ TRANSITIONINGTOFULLOFF = 0x010,

        /** State value mask representing status where output is changing due to a request to transition. */
        /*const static int*/ TRANSITIONING         = 0x010
      };
        /** {@inheritDoc} */
        //@Override
        /*default*/ /*public*/ bool isConsistentState() {
            return (getState() == ON)
                    || (getState() == OFF);
        }

        /** {@inheritDoc} */
//        @Override
//        @InvokeOnLayoutThread
        /*default*/ /*public*/ void setCommandedState(int s) {
            setState(s);
        }

        /** {@inheritDoc} */
        //@Override
        /*default*/ /*public*/ int getCommandedState() {
            return getState();
        }

        /** {@inheritDoc} */
        //@Override
        /*default*/ /*public*/ int getKnownState() {
            return getState();
        }

        /** {@inheritDoc} */
        //@Override
        //@InvokeOnLayoutThread
        /*default*/ /*public*/ void requestUpdateFromLayout() {
            // Do nothing
        }

        /**
         * Set the demanded output state. Valid values are ON and OFF.
         * ON corresponds to the maxIntensity setting, and OFF
         * corresponds to minIntensity.
         * <p>
         * Bound parameter.
         * <p>
         * Note that the state may have other values, such as INTERMEDIATE
         * or a form of transitioning, but that these may not be directly set.
         * <p>
         * @throws IllegalArgumentException if invalid newState provided
        */
        virtual void setState(int /*newState*/) {}

        /**
           Get the current state of the Light's output.
        */
        virtual int  getState() {return 0;}

        // control types - types defined
    enum TYPES
    {
        /*const static int*/ SENSOR_CONTROL          = 0x01,
        /*const static int*/ FAST_CLOCK_CONTROL      = 0x02,
        /*const static int*/ TURNOUT_STATUS_CONTROL  = 0x03,
        /*const static int*/ TIMED_ON_CONTROL		= 0x04,
        /*const static int*/ TWO_SENSOR_CONTROL		= 0x05,
        /*const static int*/ NO_CONTROL              = 0x00
    };
        /** Check if this object can handle variable intensity.
            <P>
            Unbound property.
            @return false if only ON/OFF is available.
        */
        virtual bool isIntensityVariable() {return false;}

       /** Set the intended new intensity value for the Light.
        *  If transitions are in use, they will be applied.
        *  <p>
        *  Bound property between 0 and 1.
        *  <p>
        *  A value of 0.0 corresponds to full off, and
        *  a value of 1.0 corresponds to full on.
        *  <p>
        *  Attempting to set a value below the MinIntensity property value
        *  will result in MinIntensity being set. Similarly, setting a value
        *  above MaxIntensity will result in MaxINtensity being set.
        * <p>
        *  Setting the intensity to the value of
        *  the MinIntensity property will result in the Light going
        *  to the OFF state at the end of the transition.
        *  Similarly, setting the intensity to the MaxIntensity value
        *  will result in the Light going to the ON state at the end
        *  of the transition.
        * <p>
        *  All others result in the INTERMEDIATE state.
        * <p>
        *  Light implementations
        *  with isIntensityVariable false may not have their TargetIntensity
        *  set to values between MinIntensity and MaxIntensity, which would
        *  result in the INTERMEDIATE state, as that is invalid for them.
        *  <P>
        *  If a non-zero value is set in the transitionTime property,
        *  the state will be one of TRANSITIONTOFULLON, TRANSITIONHIGHER, TRANSITIONLOWER
        *  or TRANSITIONTOFULLOFF until the transition is complete.
        *  <P>
        *  @throws IllegalArgumentException when intensity is less than 0.0 or more than 1.0
        *  @throws IllegalArgumentException if isIntensityVariable is false
        *       and the new value is between MaxIntensity and MinIntensity
        */
        virtual void setTargetIntensity(double /*intensity*/) {}

        /** Get the current intensity value.
         * If the Light is currently transitioning, this may be either
         * an intermediate or final value.
         * <p>
         * A value of 0.0 corresponds to full off, and
         * a value of 1.0 corresponds to full on.
        */
        virtual double getCurrentIntensity() { return 0;}

        /** Get the target intensity value for the
         * current transition, if any. If the Light is not currently
         * transitioning, this is the current intensity value.
         * <p>
         * A value of 0.0 corresponds to full off, and
         * a value of 1.0 corresponds to full on.
         * <p>
         * Bound property
        */
        virtual double  getTargetIntensity() {return 0;}


        /** Set the value of the maxIntensity property.
         * <p>
         * Bound property between 0 and 1.
         * <p>
         * A value of 0.0 corresponds to full off, and
         * a value of 1.0 corresponds to full on.
         * @throws IllegalArgumentException when intensity is less than 0.0 or more than 1.0
         * @throws IllegalArgumentException when intensity is not greater than the current value of the minIntensity property
        */
        virtual void setMaxIntensity(double /*intensity*/) {}

        /** Get the current value of the maxIntensity property.
         * <p>
         * A value of 0.0 corresponds to full off, and
         * a value of 1.0 corresponds to full on.
        */
        virtual double getMaxIntensity() {return 0;}

        /** Set the value of the minIntensity property.
         * <p>
         * Bound property between 0 and 1.
         * <p>
         * A value of 0.0 corresponds to full off, and
         * a value of 1.0 corresponds to full on.
         * @throws IllegalArgumentException when intensity is less than 0.0 or more than 1.0
         * @throws IllegalArgumentException when intensity is not less than the current value of the maxIntensity property
        */
        virtual void setMinIntensity(double /*intensity*/) {}

        /** Get the current value of the minIntensity property.
            <p>
            A value of 0.0 corresponds to full off, and
            a value of 1.0 corresponds to full on.
        */
        virtual double getMinIntensity() = 0;

        /** Can the Light change it's intensity setting slowly?
            <p>
            If true, this Light supports a non-zero value of the
            transitionTime property, which controls how long the Light
            will take to change from one intensity level to another.
            <p>
            Unbound property
        */
        virtual bool isTransitionAvailable() {return false;}

        /** Set the fast-clock duration for a
            transition from full ON to full OFF or vice-versa.
            <P>
            Note there is no guarantee of how this scales when other
            changes in intensity take place.  In particular, some Light implementations
            will change at a constant fraction per fastclock minute and some will take
            a fixed duration regardless of the size of the intensity change.
            <p>
            Bound property
            <p>
            @throws IllegalArgumentException if isTransitionAvailable() is false and minutes is not 0.0
            @throws IllegalArgumentException if minutes is negative
        */
        virtual void setTransitionTime(double /*minutes*/) {}

        /** Get the number of fastclock minutes taken by a transition from
            full ON to full OFF or vice versa.
            <p>
            @return 0.0 if the output intensity transition is instantaneous
        */
        virtual double getTransitionTime() {return 0;}

        /**
            Convenience method for checking if the intensity of the light is currently
            changing due to a transition.
            <p>
            Bound property so that listeners can conveniently learn when the transition is over.
        */
        virtual bool isTransitioning() {return false;}

        /**
         * LightControl information management methods
         */
        virtual void clearLightControls() {}  // clears all Light Controls for this Light
        virtual void addLightControl(LightControl* /*c*/) {} // add a LightControl
        virtual QList<LightControl*> getLightControlList(){return QList<LightControl*>();}// return a list of all LightControls

        /**
         * Set the Enabled property, which determines whether the control logic
         * built in the light object is operating or not. Light objects are usually
         * enabled.
         */
        virtual void setEnabled(bool /*state*/) {}

        /**
         * Get the Enabled property, which determines whether the control logic
         * built in the light object is operating or not.
         */
        virtual bool getEnabled() {return false;}

        /**
         * Activates a Light.  This method activates each LightControl,
         *   setting up a control mechanism, appropriate to its
         *   control type.
         */
        virtual void activateLight() {}

        /**
         * Deactivates a Light.  This method deactivates each LightControl,
         *   shutting down its control mechanism.
         */
        virtual void deactivateLight() {}

    virtual QObject* self() =0;
signals:
    
public slots:
    
};
Q_DECLARE_INTERFACE(Light, "Light")
#endif // LIGHT_H
