#ifndef TURNOUT_H
#define TURNOUT_H

#include <QObject>
#include "sensor.h"
//#include "turnoutoperation.h"
//#include "namedbean.h"
#include "namedbeanhandle.h"
#include "libPr3_global.h"
#include "abstractnamedbean.h"

class TurnoutOperation;
class LIBPR3SHARED_EXPORT Turnout : public AbstractNamedBean
{
 Q_OBJECT
public:
 explicit Turnout(QObject *parent = 0) : AbstractNamedBean(parent) {}
 Turnout(QString sysName, QObject* parent=0) : AbstractNamedBean(sysName, parent) {}
 Turnout(QString sysName, QString userName, QObject* parent=0) : AbstractNamedBean(sysName, userName, parent) {}

    /**
     * Represent a Turnout on the layout.
     * <P>
     * A Turnout has two states:
     * <ul>
     * <li>The "commandedState" records the state that's been commanded in the
     *     program.  It might take some time, perhaps a long time, for that
     *     to actually take effect.
     * <li>The "knownState" is the program's best idea of the actual state on the
     *     the layout.
     * </ul>
     * <P>
     * There are a number of reasons that commandedState and knownState differ:
     * <ul>
     * <li>A change has been commanded, but it hasn't had time to happen yet
     * <li>Something has gone wrong, and a commanded change isn't actually going to happen
     * <li>Although the program hasn't commanded a change, something on the layout
     *     has made the turnout change.  This could be a local electrical button,
     *     a mechanical movement of the points, or something else.
     * <li>For a bus-like system, e.g. LocoNet or XPressNet, some other device might
     *     have sent a command to change the turnout.
     * </ul>
     * <P>
     * Turnout feedback is involved in the connection between these two states;
     * for more information see the
     * <a href="http://jmri.org/help/en/html/doc/Technical/TurnoutFeedback.shtml">feedback page</a>.
     * <P>
     * The AbstractTurnout class contains a basic implementation of the state and messaging
     * code, and forms a useful start for a system-specific implementation.
     * Specific implementations in the jmrix package, e.g. for LocoNet and NCE, will
     * convert to and from the layout commands.
     * <P>
     * The states  and names are Java Bean parameters, so that listeners can be
     * registered to be notified of any changes.
     * <P>
     * A sample use of the Turnout interface can be seen in the jmri.jmrit.simpleturnoutctrl.SimpleTurnoutCtrlFrame
     * class, which provides a simple GUI for controlling a single turnout.
     * <P>
     * Each Turnout object has a two names.  The "user" name is entirely free form, and
     * can be used for any purpose.  The "system" name is provided by the system-specific
     * implementations, and provides a unique mapping to the layout control system
     * (e.g. LocoNet, NCE, etc) and address within that system.
     * <p>
     * Turnouts exhibit some complex behaviors.  At the same time, they
     * are sometimes used as generic binary outputs where those get in the
     * way.  Eventually, we need to have a separate e.g. Output class, but
     * for now you can defeat much of the advanced behaviors with the
     * setBinaryOutput(true) method.  This is a configuration property;
     * changing it on the fly may give unexpected results. It's value is
     * not persisted.
     * <P>
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
     *
     * @author	Bob Jacobsen  Copyright (C) 2001
     * @version	$Revision: 17977 $
     * @see         jmri.TurnoutManager
     * @see         jmri.InstanceManager
     * @see         jmri.jmrit.simpleturnoutctrl.SimpleTurnoutCtrlFrame
     */
//    virtual interface Turnout extends NamedBean {
     enum STATES
     {
      UNKNOWN = 0x01,
      CLOSED = 0x02,
      THROWN = 0x04,
      INCONSISTENT = 0x08
     };
     Q_ENUM(STATES)
        /**
         * Constant representing an "closed" state, either in readback
         * or as a commanded state. Note that it's possible to be
         * both CLOSED and THROWN at the same time on some systems,
         * which should be called INCONSISTENT
         */
        //const static int CLOSED;//       = 0x02

        /**
         * Constant representing an "thrown" state, either in readback
         * or as a commanded state. Note that it's possible to be
         * both CLOSED and THROWN at the same time on some systems,
         * which should be called INCONSISTENT
         */
        //const static int THROWN;//       = 0x04;

        /**
         * Query the known state.  This is a bound parameter, so
         * you can also register a listener to be informed of changes.
         * A result is always returned; if no other feedback method is
         * available, the commanded state will be used.
         */
        virtual int getKnownState() { return 0;}

        /**
         * Change the commanded state, which results in the relevant command(s) being
         * sent to the hardware. The exception is thrown if there are
         * problems communicating with the layout hardware.
         */
        virtual void setCommandedState(int /*s*/) {}

        /**
         * Query the commanded state.  This is a bound parameter, so
         * you can also register a listener to be informed of changes.
         */
        virtual int getCommandedState() {return 0;}

        /**
         * Show whether state is one you can safely run trains over
         * @return	true iff state is a valid one and the known state is the same as commanded
         */
        virtual bool isConsistentState() {return false;}

        /**
         * Constant representing "direct feedback method".  In this case,
         * the commanded state is provided when the known state is requested.
         * The two states never differ.
         * This mode is always possible!
         */
        //const static int DIRECT; //     = 1;

        /**
         * Constant representing "exact feedback method".  In this case,
         * the layout hardware can sense both positions of the turnout, which is
         * used to set the known state.
         */
        //const static int EXACT;//    = 2;

        /**
         * Constant representing "indirect feedback".  In this case,
         * the layout hardware can only sense one setting of the turnout. The known
         * state is inferred from that info.
         */
        //const static int INDIRECT;// = 4;  // only one side directly sensed

        /**
         * Constant representing "feedback by monitoring sent commands".  In this case,
         * the known state tracks commands seen on the rails or bus.
         */
        //const static int MONITORING;//     = 8;

        /**
         * Constant representing "feedback by monitoring one sensor".
         * The sensor sets the state CLOSED when INACTIVE
         * and THROWN when ACTIVE
         */
        //const static int ONESENSOR;//     = 16;

        /**
         * Constant representing "feedback by monitoring two sensors".
         * The first sensor sets the state THROWN when ACTIVE;
         * the second sensor sets the state CLOSED when ACTIVE.
         */
        //const static int TWOSENSOR;//     =32;

        /**
         * Constant representing "feedback for signals" .  This is DIRECT feedback,
         * with minimal delay (for use with systems that wait for responses
         * returned by from the command station).
         */
        //const static int _SIGNAL;//        = 64;
        /**
         * Constant representing "automatic delayed feedback" . This is DIRECT feedback
         * with a fixed delay before the feedback (known state) takes effect.
         */
        // /*public*/ const static /*final*/ int DELAYED;// = 128;

        enum FEEDBACK
        {
        DIRECT = 1,
        ONESENSOR = 16,
        TWOSENSOR = 32,
        INDIRECT = 4,
        MONITORING = 8,
        EXACT    = 2,
        _SIGNAL = 64,
        DELAYED = 128

        };
        Q_ENUM(FEEDBACK)
        /**
         * Get a representation of the feedback type.  This is the OR of
         * possible values: DIRECT, EXACT, etc.
         * The valid combinations depend on the implemented system.
         */
        virtual int getValidFeedbackTypes() {return 0;}

        /**
         * Get a human readable
         * representation of the feedback type.
         * The values depend on the implemented system.
         */
        virtual QVector<QString> getValidFeedbackNames() {return QVector<QString>();}

        /**
         * Set the feedback mode from a human readable name.
         * This must be one of the names defined
         * in a previous {@link #getValidFeedbackNames} call.
         */
        virtual void setFeedbackMode(QString /*mode*/) {} // throws IllegalArgumentException;

        /**
         * Set the feedback mode from a integer.
         * This must be one of the bit values defined
         * in a previous {@link #getValidFeedbackTypes} call.
         * Having more than one bit set is an error.
         */
        virtual void setFeedbackMode(int /*mode*/) {} // throws IllegalArgumentException;

        /**
         * Get the feedback mode in human readable form.
         * This will be one of the names defined
         * in a {@link #getValidFeedbackNames} call.
         */
        virtual QString getFeedbackModeName() {return "";}
        /**
         * Get the feedback mode in machine readable form.
         * This will be one of the bits defined
         * in a {@link #getValidFeedbackTypes} call.
         */
        virtual int getFeedbackMode() {return 0;}
        /**
         * Request an update from the layout soft/hardware. May not even happen, and
         * if it does it will happen later; listen for the result.
         */
        virtual /*public*/ void requestUpdateFromLayout() {}
        /**
         * Get the indicator for whether automatic operation (retry) has been
         * inhibited for this turnout
         */
        virtual bool getInhibitOperation() {return false;}
        /**
         * Change the value of the inhibit operation indicator
         * @param io
         */
        virtual void setInhibitOperation(bool /*io*/) {}
        /**
         * @return current operation automation class
         */
        virtual TurnoutOperation* getTurnoutOperation() {return NULL;}
        /**
         * set current automation class
         * @param toper TurnoutOperation subclass instance
         */
        virtual void setTurnoutOperation(TurnoutOperation* /*toper*/) {}

        /**
         * return the inverted state of the specified state
         * @param inState the specified state
         * @return the inverted state
         */
        /*public*/ static int invertTurnoutState(int inState) {
            int result = CLOSED;
            if (result == inState) {
                result = THROWN;
            }
            return result;
        }
        /**
         * Provide Sensor objects needed for some feedback types.
         *
         * Since we defined two feeedback methods that require monitoring,
         * we provide these methods to define those sensors to the Turnout.
         *<P>
         * The second sensor can be null if needed.
         * <P>
         * Sensor-based feedback will not function until these
         * sensors have been provided.
         */
        //virtual void provideFirstFeedbackSensor(NamedBeanHandle<Sensor>* /*s*/) {}
        virtual void provideFirstFeedbackSensor(QString /*pName*/) throw (JmriException) {}
        virtual void provideSecondFeedbackSensor(QString /*pName*/) throw (JmriException) {}


        /**
         * Get the first sensor, if defined.
         *<P>
         * Returns null if no Sensor recorded.
         */
        virtual Sensor* getFirstSensor() {return NULL;}
        /**
         * Get the first sensor, if defined.
         *<P>
         * Returns null if no Sensor recorded.
         */
        virtual NamedBeanHandle<Sensor*>* getFirstNamedSensor() {return NULL;}

        /**
         * Get the Second sensor, if defined.
         *<P>
         * Returns null if no Sensor recorded.
         */
        virtual Sensor* getSecondSensor() {return NULL;}

        /**
         * Get the first sensor, if defined.
         *<P>
         * Returns null if no Sensor recorded.
         */
        virtual NamedBeanHandle<Sensor*>* getSecondNamedSensor() {return NULL;}

        /**
         * Sets the initial known state (CLOSED,THROWN,UNKNOWN) from feedback
         *    information, if appropriate.
         *<P>
         * This method is designed to be called only when Turnouts are loaded
         *    and when a new Turnout is defined in the Turnout table.
         *<P>
         * No change to known state is made if feedback information is not
         *    available.  If feedback information is inconsistent, or if
         *    sensor definition is missing in ONESENSOR and TWOSENSOR feedback,
         *    turnout state is set to UNKNOWN.
         */
        virtual void setInitialKnownStateFromFeedback() {}

        /**
         * Get number of output bits.
         *<P>
         * Currently must be one or two.
         */
        virtual int getNumberOutputBits() {return 0;}

        /**
         * Set number of output bits.
         *<P>
         * Currently must be one or two.
         */
        virtual void setNumberOutputBits(int /*num*/) {}

        /**
         * Get control type.
         *<P>
         * Currently must be either 0 for steady state, or n
         *    for pulse for n time units.
         */
        virtual int getControlType() {return 0;}

        /**
         * Set control type.
         *<P>
         * Currently must be either 0 for steady state, or n
         *    for pulse for n time units.
        */
        virtual void setControlType(int /*num*/) {}
        /**
         * Get turnout inverted
         *<P>
         * If true commands are reversed to layout
         */
        virtual bool getInverted() {return false;}

        /**
         * Set turnout inverted
         *<P>
         * If true commands are reversed to layout.
         * <p>
         * Changing this changes the known state from
         * CLOSED to THROWN and vice-versa, with notifications;
         * UNKNOWN and INCONSISTENT are left unchanged, as is
         * the commanded state.
         */
        virtual void setInverted(bool /*inverted*/) {}

        /**
         * Determine if turnout can be inverted
         *<P>
         * If true turnouts can be inverted
         */
        virtual bool canInvert() const =0;

        /**
         *  Constant representing turnout lockout cab commands
         */
        //const static int CABLOCKOUT = 1;

        /**
         *  Constant representing turnout lockout pushbuttons
         */
        //const static int PUSHBUTTONLOCKOUT = 2;

        /**
         * Constant representing a unlocked turnout
         */
        //const static int UNLOCKED = 0;

        /**
         * Constant representing a locked turnout
         */
        //const static int LOCKED = 1;
        enum LOCKS
        {
            CABLOCKOUT = 1,
            PUSHBUTTONLOCKOUT = 2,
            UNLOCKED = 0,
            LOCKED = 1
        };
        Q_ENUM(LOCKS)
        /**
         * Get turnout locked
         * <P>
         * If true turnout is locked, must specify which type of lock, will return
         * true if both tested and either type is locked.
         */
        virtual bool getLocked(int /*turnoutLockout*/) {return false;}

        /**
         * Enable turnout lock operators.
         *<P>
         * If true the type of lock specified is enabled.
         */
        virtual void enableLockOperation(int /*turnoutLockout*/, bool /*locked*/) {}

        /**
         * Determine if turnout can be locked.  Must specify the type of lock.
         *<P>
         * If true turnouts can be locked.
         */
        virtual bool canLock(int /*turnoutLockout*/) {return false;}

        /**
         * Provide the possible locking modes for a turnout.
         * These may require additional configuration, e.g.
         * setting of a decoder definition for PUSHBUTTONLOCKOUT,
         * before {@link #canLock(int)} will return true.
         *
         * @return One of 0 for none, CABLOCKOUT, PUSHBUTTONLOCKOUT
         * or CABLOCKOUT | PUSHBUTTONLOCKOUT for both
         */
        /*public*/ virtual int getPossibleLockModes() {return 0;}

        /**
         * Lock a turnout. Must specify the type of lock.
         *<P>
         * If true turnout is to be locked.
         */
        virtual void setLocked(int /*turnoutLockout*/, bool /*locked*/) {}

        /**
         * Determine if we should send a message to console when we detect that a
         * turnout that is locked has been accessed by a cab on the layout. If true,
         * report cab attempt to change turnout.
         */
        virtual bool getReportLocked() {return false;}

        /**
         * Set turnout report
         *<P>
         * If true report any attempts by a cab to modify turnout state
         */
        virtual void setReportLocked(bool /*reportLocked*/) {}

        /**
         * Get a human readable representation of the decoder types.
         */
        virtual QStringList getValidDecoderNames() {return QStringList();}

        /**
         * Get a human readable representation of the decoder type for this turnout.
         */
        virtual QString getDecoderName() {return "";}

        /**
         * Set a human readable representation of the decoder type for this turnout.
         */
        virtual void setDecoderName(QString /*decoderName*/) {}

        /**
         * Turn this object into just a binary output.
         */
        virtual void setBinaryOutput(bool /*state*/) {}

        virtual float getDivergingLimit() {return 0;}

        virtual QString getDivergingSpeed() {return "";}
        virtual void setDivergingSpeed(QString /*s*/) const throw (JmriException) {}

        virtual float getStraightLimit()  {return 0;}

        virtual QString getStraightSpeed() {return "";}
        virtual void setStraightSpeed(QString /*s*/) const  throw (JmriException) {}

signals:
    
public slots:

};
Q_DECLARE_INTERFACE(Turnout, "Turnout")
#endif // TURNOUT_H
