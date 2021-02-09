#ifndef THROTTLEMANAGER_H
#define THROTTLEMANAGER_H

#include <QObject>
#include "basicrosterentry.h"
#include "dccthrottle.h"
#include "Throttle/throttlelistener.h"
#include "logger.h"

class AbstractThrottleManager;
class ThrottleManager : public QObject
{
    Q_OBJECT
public:
    explicit ThrottleManager(QObject *parent = 0);
    static /*public*/ ThrottleManager* instance();
//    /*public*/ void requestThrottleSetup(LocoAddress* address, bool control);
//    /*public*/ bool addressTypeUnique();
//    /*public*/ bool canBeShortAddress(int a);
//    /*public*/ bool canBeLongAddress(int a);
//    /*public*/ bool disposeThrottle(DccThrottle* t, ThrottleListener* l);

    /**
     * Interface for allocating {@link Throttle} objects.
     * <P>
     * "Address" is interpreted in the context of the DCC implementation.
     * Different systems will distinquish between short and long addresses
     * in different ways.
     * <P>
     * When the allocated Throttle is no longer needed, it is told that
     * it's released.  If a specific ThrottleManager and/or
     * Throttle implementation needs to keep track of
     * that operation, it is handled internally.
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
     * @author			Glen Oberhauser
     * @author			Bob Jacobsen Copyright 2006
     * @version			$Revision: 21273 $
     */
//    public interface ThrottleManager {


/**
 * Request a throttle from a given Roster Entry. When the decoder address
 * is located, the ThrottleListener gets a callback via the ThrottleListener.notifyThrottleFound
 * method.
 * @param re The Roster Entry desired.
 * @param l The ThrottleListener awaiting notification of a found throttle.
 * @return True if the request will continue, false if the request will not
 * be made. False may be returned if a the throttle is already in use.
 */
virtual bool requestThrottle(BasicRosterEntry* /*re*/, ThrottleListener* /*l*/) {return false;}

/**
 * Request a throttle, given a decoder address. When the decoder address
 * is located, the ThrottleListener gets a callback via the ThrottleListener.notifyThrottleFound
 * method.
 * <P>
 * This is a convenience version of the call, which uses system-specific
 * logic to tell whether the address is a short or long form.
 * @param address The decoder address desired.
 * @param l The ThrottleListener awaiting notification of a found throttle.
 * @return True if the request will continue, false if the request will not
 * be made. False may be returned if a the throttle is already in use.
 */
virtual bool requestThrottle(int /*address*/, ThrottleListener* /*l*/) {return false;}

/**
 * Request a throttle, given a decoder address. When the decoder address is
 * located, the ThrottleListener gets a callback via the
 * ThrottleListener.notifyThrottleFound method.
 * <P>
 * This is a convenience version of the call, which uses system-specific
 * logic to tell whether the address is a short or long form,
 * and assumes that the hardware makes and steal / share decisions.
 * <p>
 * @param canHandleDecisions true if the ThrottleListener has a mechanism for dealing with
 *        Share / Steal decisions, else false
 * @param address desired decoder address
 * @param l       ThrottleListener awaiting notification of a found throttle

 * @return true if the request will continue, false if the request will not
 *         be made; false may be returned if a the throttle is already in
 *         use
 */
/*public*/ virtual bool requestThrottle(int /*address*/, ThrottleListener* /*l*/, bool /*canHandleDecisions*/){return false;}

/**
 * Request a throttle, given a decoder address & whether it is a long
 * or short DCC address. When the decoder address
 * is located, the ThrottleListener gets a callback via the ThrottleListener.notifyThrottleFound
 * method.
 * @param address The decoder address desired.
 * @param isLong True if this is a request for a DCC long (extended) address.
 * @param l The ThrottleListener awaiting notification of a found throttle.
 * @return True if the request will continue, false if the request will not
 * be made. False may be returned if a the throttle is already in use.
 */
QT_DEPRECATED virtual bool  requestThrottle(int /*address*/, bool  /*isLong*/, ThrottleListener* /*l*/) {return false;}

/**
 * Request a throttle, given a decoder address and whether it is a long or
 * short DCC address. When the decoder address is located, the
 * ThrottleListener gets a callback via the
 * ThrottleListener.notifyThrottleFound method.
 *
 * @param address desired decoder address
 * @param isLong  true if requesting a DCC long (extended) address
 * @param l       ThrottleListener awaiting notification of a found throttle
 * @param canHandleDecisions true if the ThrottleListener has a mechanism for dealing with
 *                Share / Steal decisions, else false
 * @return true if the request will continue, false if the request will not
 *         be made; false may be returned if a the throttle is already in
 *         use
 */
/*public*/ virtual bool requestThrottle(int address, bool isLong, ThrottleListener* l, bool canHandleDecisions) {return false;}

/**
 * Request a throttle, given a decoder address. When the decoder address
 * is located, the ThrottleListener gets a callback via the ThrottleListener.notifyThrottleFound
 * method.
 * <P>
 * This is a convenience version of the call, which uses system-specific
 * logic to tell whether the address is a short or long form.
 * @param address The decoder address desired.
 * @param l The ThrottleListener awaiting notification of a found throttle.
 * @return True if the request will continue, false if the request will not
 * be made. False may be returned if a the throttle is already in use.
 */
QT_DEPRECATED virtual bool  requestThrottle(LocoAddress* /*address*/, ThrottleListener* /*l*/) {return false;}

/**
 * Request a throttle, given a LocoAddress. When the address is
 * located, the ThrottleListener gets a callback via the
 * ThrottleListener.notifyThrottleFound method.
 *
 * @param address desired loco address
 * @param l       ThrottleListener awaiting notification of a found throttle
 * @param canHandleDecisions true if the ThrottleListener has a mechanism for dealing with
 *        Share / Steal decisions, else false
 * @return true if the request will continue, false if the request will not
 *         be made; false may be returned if a the throttle is already in
 *         use
 */
virtual /*public*/ bool requestThrottle(LocoAddress* /*address*/, ThrottleListener* /*l*/, bool /*canHandleDecisions*/) {return false;}
/**
 * Request a throttle, given a decoder address or a RosterEntry. When the decoder address
 * is located, the ThrottleListener gets a callback via the ThrottleListener.notifyThrottleFound
 * method.
 * <P>
 * This is a convenience version of the call, which uses system-specific
 * logic to tell whether the address is a short or long form.
 * @param address The decoder address desired.
 * @param re The RosterEntry desired.
 * @param l The ThrottleListener awaiting notification of a found throttle.
 * @return True if the request will continue, false if the request will not
 * be made. False may be returned if a the throttle is already in use.
 */
QT_DEPRECATED virtual bool  requestThrottle(LocoAddress* /*address*/, BasicRosterEntry* /*re*/, ThrottleListener* /*l*/) {return false;}
/**
 * Request a throttle from a given RosterEntry. When the decoder address is
 * located, the ThrottleListener gets a callback via the
 * ThrottleListener.notifyThrottleFound method.
 *
 * @param re desired RosterEntry
 * @param l  ThrottleListener awaiting notification of a found throttle
 * @param canHandleDecisions true if the ThrottleListener has a mechanism for dealing with
 *        Share / Steal decisions, else false
 * @return true if the request will continue, false if the request will not
 *         be made; false may be returned if a the throttle is already in
 *         use
 */
/*public*/ virtual bool requestThrottle(BasicRosterEntry* /*re*/, ThrottleListener* /*l*/, bool /*canHandleDecisions*/) {return false;}
/**
 * Cancel a request for a throttle.
 * <P>
 * This is a convenience version of the call, which uses system-specific
 * logic to tell whether the address is a short or long form.
 * @param re The Roster Entry desired.
 * @param l The ThrottleListener cancelling request for a throttle.
 */
virtual void cancelThrottleRequest(BasicRosterEntry* /*re*/, ThrottleListener* /*l*/) {}


/**
 * Cancel a request for a throttle.
 * <P>
 * This is a convenience version of the call, which uses system-specific
 * logic to tell whether the address is a short or long form.
 * @param address The decoder address desired.
 * @param l The ThrottleListener cancelling request for a throttle.
 */
virtual void cancelThrottleRequest(int /*address*/, ThrottleListener* /*l*/) {}

/**
 * Cancel a request for a throttle.
 * @param address The decoder address desired.
 * @param isLong True if this is a request for a DCC long (extended) address.
 * @param l The ThrottleListener cancelling request for a throttle.
 */
virtual void cancelThrottleRequest(int /*address*/, bool  /*isLong*/, ThrottleListener* /*l*/) {}

/**
 * Cancel a request for a throttle.
 *
 * @param address unwanted Loco address
 * @param l       ThrottleListener canceling request for a throttle
 */
/*public*/ virtual void cancelThrottleRequest(LocoAddress* /*address*/, ThrottleListener* /*l*/) {}
/**
 * Steal a requested throttle.
 * <P>
 * This is a convenience version of the call, which uses system-specific
 * logic to tell whether the address is a short or long form.
 *
 * @param re desired Roster Entry
 * @param l  ThrottleListener requesting the throttle steal occur.
 * @param steal true if the request should continue, false otherwise.
 * @since 4.9.2
 */
/*public*/ virtual void stealThrottleRequest(BasicRosterEntry* /*re*/, ThrottleListener* /*l*/, bool /*steal*/) {}

/**
 * Steal a requested throttle.
 * <P>
 * This is a convenience version of the call, which uses system-specific
 * logic to tell whether the address is a short or long form.
 *
 * @param address desired decoder address
 * @param l  ThrottleListener requesting the throttle steal occur.
 * @param steal true if the request should continue, false otherwise.
 * @since 4.9.2
 */
/*public*/ virtual void stealThrottleRequest(int /*address*/, ThrottleListener* /*l*/,bool /*steal*/) {}

/**
 * Steal a requested throttle.
 *
 * @param address desired decoder address
 * @param isLong  true if requesting a DCC long (extended) address
 * @param l  ThrottleListener requesting the throttle steal occur.
 * @param steal true if the request should continue, false otherwise.
 * @since 4.9.2
 */
/*public*/ virtual void stealThrottleRequest(int /*address*/, bool /*isLong*/, ThrottleListener* /*l*/,bool /*steal*/) {}

/**
 * Steal a requested throttle.
 *
 * @param address desired LocoAddress
 * @param l  ThrottleListener requesting the throttle steal occur.
 * @param steal true if the request should continue, false otherwise.
 * @since 4.9.2
 */
/*public*/ virtual void stealThrottleRequest(LocoAddress* /*address*/, ThrottleListener* /*l*/,bool /*steal*/) {}
/**
 * Steal or Share a requested throttle.
 * <P>
 * This is a convenience version of the call, which uses system-specific
 * logic to tell whether the address is a short or long form.
 *
 * @param address desired decoder address
 * @param isLong  true if requesting a DCC long (extended) address
 * @param l  ThrottleListener requesting the throttle steal occur.
 * @param decision from the ThrottleListener, STEAL or SHARE.
 */
/*public*/ virtual void responseThrottleDecision(int /*address*/, bool /*isLong*/, ThrottleListener* /*l*/, ThrottleListener::DecisionType /*decision*/) {}

/**
 * Steal or Share a requested throttle.
 *
 * @param address desired LocoAddress
 * @param l The ThrottleListener which has made the decision
 * @param decision from the ThrottleListener, STEAL or SHARE.
 * @since 4.9.2
 */
/*public*/ virtual void responseThrottleDecision(LocoAddress* /*address*/, ThrottleListener* /*l*/, ThrottleListener::DecisionType /*decision*/) {}

/**
 * Check to see if the Dispatch Button should be enabled or not
 **/
virtual bool  hasDispatchFunction() {return false;}

/**
 * Check to see if a specific number is a valid long address on this system
 **/
virtual bool  canBeLongAddress(int /*address*/) {return false;}

/**
 * Check to see if a specific number is a valid short address on this system
 **/
virtual bool  canBeShortAddress(int /*address*/) {return false;}
/**
 * Are there not any ambiguous addresses (short vs long) on this system?
 * This is also used to indicate systems that support multi-protocol decoders
 */
virtual bool addressTypeUnique() {return false;}

/**
* This returns a list of the different protocols that are supported by the
* system, to include short vs long or DCC vs Selectrix vs Motorola
*/
 virtual QStringList getAddressTypes() {return QStringList();}

/**
* return a string value for a given int protocol value
*/
    virtual QString getAddressTypeString(LocoAddress::Protocol /*prot*/) {return "";}

/**
 * returns an Integer list of different protocols that are supported by
 * system, to include short vs long or DCC vs Selectrix vs Motorola
 */
    virtual QList<LocoAddress::Protocol> getAddressProtocolTypes() {return QList<LocoAddress::Protocol>();}

/**
 * Get the integer value representing a protocol
 * @param selection
 * @return the integer value of the protocol
 */
virtual LocoAddress::Protocol getProtocolFromString(QString /*selection*/) {return (LocoAddress::Protocol)0;}

/**
 * Get the object representing a particular address
 * @param value String in format specific to the protocol
 * @param protocol specific protocol string, see the specific throttle manager for values
 * @return probably of a subtype
 */
virtual LocoAddress* getAddress(QString /*value*/, QString /*protocol*/) {return NULL;}
virtual LocoAddress* getAddress(QString /*value*/, LocoAddress::Protocol /*protocol*/) {return NULL;}

/**
* The string provided in the getAddressTypes of a protocol for a given address
*/
virtual int getMode(int /*address*/) {return 0;}

/**
 * Get the supported speed modes.
 *
 * @return an XOR of the possible modes specified in the throttle interface
 */
/*public*/ virtual QSet<SpeedStepMode::SSMODES> supportedSpeedModes() {return QSet<SpeedStepMode::SSMODES>();}

/**
 * Provides a Proxy method to return the SpeedSetting, Direction, Function
 * Settings, of a throttle, where the requesting code has used the
 * {@link #attachListener(DccLocoAddress, java.beans.PropertyChangeListener) attachListener}
 * to only be notified of changes in the throttle and not control it.
 * <P>
 * Valid values for item are
 * IsForward
 * SpeedSetting
 * SpeedIncrement
 * SpeedStepMode
 * F0-F28
 * <P>
 * @param la   DccLocoAddress that we wish interrogate
 * @param item A string of the item we wish to know the value of.
 * @return the value as an objet, if the loco address has not been assigned
 * to a throttle or the item value is not valid, null is returned.
 */
    virtual QVariant getThrottleInfo(LocoAddress* /*la*/, QString /*item*/) {return QVariant();}

    virtual bool addressStillRequired(LocoAddress* /*la*/) {return false;}

/**
 * The specified Throttle Listener has finished using a given throttle and
 * no longer requires access to it.
 * <P>
 * After releasing the throttle, the manager will perform further checks to
 * see if it is in use by any other listeners or if there are any
 * propertychangelisteners attached.
 * If there are no other uses of the throttle then it is disposed of.
 * <P>
 * Normally, release ends with a call to dispose.
 * @param t Throttle being released
 * @param l Throttle Listener releasing the throttle
 */
virtual void releaseThrottle(DccThrottle* /*t*/, ThrottleListener* /*l*/) {}

/**
 * Not for general use, see {@link #releaseThrottle(DccThrottle, ThrottleListener) releaseThrottle}
 * and {@link #dispatchThrottle(DccThrottle, ThrottleListener) dispatchThrottle}.
 * <p>
 * Dispose of object when finished it.  This will free up hardware resource
 * <P>
 * Used for handling certain internal error conditions, where
 * the object still exists but hardware is not associated with it.
 * <P>
 * After this, further usage of
 * this Throttle object will result in a JmriException.
 * @param t Throttle being released
 * @param l Throttle Listener releasing the throttle
 * @return true if the throttle has been disposed of.
 */
virtual bool disposeThrottle(DccThrottle* /*t*/, ThrottleListener* /*l*/) {return false;}

/**
 * The throttle listener has finished with the specific Throttle and is
 * is available for reuse/reallocation by somebody else. If possible,
 * tell the layout that this locomotive has been dispatched to another user.
 * Not all layouts will implement this, in which case it is synomous with
 * release();
 * <P>
 * Normally, dispatch ends with a call to dispose.
 * @param t Throttle being released
 * @param l Throttle Listener releasing the throttle
 */
virtual void dispatchThrottle(DccThrottle* /*t*/, ThrottleListener* /*l*/) {}

/**
 * Attach a PropertyChangeListener to a specific loco address, where the
 * requesting code does not need or require control over the loco. If the
 * loco address is not in the active in the list, then a new throttle will
 * be created by the manager and the listener attached.
 * <p>
 * The PropertyChangeListener will be notified if it has been attached to a
 * loco address or not, via a PropertyChange notification.
 * <p>
 * @param la LocoAddress of the loco we wish to monitor
 * @param p  PropertyChangeListener to attach to the throttle
 */
/*public*/ virtual void attachListener(LocoAddress* la, PropertyChangeListener* p) = 0;

/**
 * Remove a PropertyChangeListener to a specific loco address, where the
 * requesting code has used {@link #attachListener(DccLocoAddress, java.beans.PropertyChangeListener) attachListener}
 * to get notification of changes in a throttle.
 * <P>
 * The propertyChangeListener will be notified if it has been removed
 * via a propertyChange notification.
 * <P>
 * @param la - DccLocoAddress of the loco we wish to monitor
 * @param p - PropertyChangeListener to attachremove from the throttle
*/
virtual void removeListener(LocoAddress* /*la*/, PropertyChangeListener* /*p*/) {}

/**
 * A method to get the Name of the system that the programmer is associated with.
 */
    virtual QString getUserName() {return "";}
signals:
    
public slots:
private:
    static /*private*/ ThrottleManager* mInstance;// = null;
    Throttle* currentThrottle;// = NULL;
 Logger* log;
    
};
Q_DECLARE_INTERFACE(ThrottleManager, "Throttle manager")
#endif // THROTTLEMANAGER_H
