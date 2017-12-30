#ifndef ABSTRACTTHROTTLEMANAGER_H
#define ABSTRACTTHROTTLEMANAGER_H
#include "throttlemanager.h"
#include "systemconnectionmemo.h"
#include "Throttle/throttlelistener.h"
#include "basicrosterentry.h"
#include "dccthrottle.h"
#include "abstractthrottle.h"
#include "loconetthrottle.h"
#include "Roster/rosterentry.h"
#include "libPr3_global.h"

/**
 * Abstract implementation of a ThrottleManager.
 * <P>
 * Based on Glen Oberhauser's original LnThrottleManager implementation.
 *
 * @author	Bob Jacobsen  Copyright (C) 2001
 * @version     $Revision: 22484 $
 */
class LIBPR3SHARED_EXPORT WaitingThrottle : public QObject
{
 Q_OBJECT
 public:
 ThrottleListener* l;
 BasicRosterEntry* re;
 PropertyChangeListener* pl;

 WaitingThrottle(ThrottleListener* _l, BasicRosterEntry* _re);
 WaitingThrottle(PropertyChangeListener* _pl, BasicRosterEntry* _re);
 PropertyChangeListener* getPropertyChangeListener();
 ThrottleListener* getListener();
 BasicRosterEntry* getRosterEntry();
};
/*protected*/ /*static*/ class LIBPR3SHARED_EXPORT Addresses : public QObject
{
 Q_OBJECT
 friend class AbstractThrottleManager;

 public:
  int useActiveCount;// = 0;
  DccThrottle* throttle;// = NULL;
  QList<ThrottleListener*>* listeners;// = new ArrayList<ThrottleListener>();
  BasicRosterEntry* re;// = NULL;
 protected:
  /*protected*/ Addresses(DccThrottle* throttle);
  void incrementUse();
  void decrementUse();
  int getUseCount() ;
  DccThrottle* getThrottle();
  void setThrottle(DccThrottle* throttle);
  void setRosterEntry(BasicRosterEntry* _re);
  BasicRosterEntry* getRosterEntry();
  void addListener(ThrottleListener* l);
  void removeListener(ThrottleListener* l);
  bool containsListener(ThrottleListener* l);
 private:
 Logger log;

 };

class LIBPR3SHARED_EXPORT AbstractThrottleManager : public ThrottleManager
{
    Q_OBJECT
public:
    explicit AbstractThrottleManager(QObject *parent = 0);
    /*public*/ AbstractThrottleManager(SystemConnectionMemo* memo,QObject *parent = 0);
    /*public*/ QString getUserName();
    /**
     * By default, only DCC in this implementation
     */
    /*public*/ QStringList getAddressTypes();
    /*public*/ QList<LocoAddress::Protocol> getAddressProtocolTypes();
    /*public*/ LocoAddress* getAddress(QString value,LocoAddress::Protocol protocol);
    /*public*/ LocoAddress* getAddress(QString value, QString protocol);
    /*public*/ LocoAddress::Protocol getProtocolFromString(QString selection);
    /*public*/ bool requestThrottle(BasicRosterEntry* re, ThrottleListener* l);
    /*public*/ bool requestThrottle(int address, bool isLongAddress, ThrottleListener* l);
    /*public*/ bool requestThrottle(DccLocoAddress* la, ThrottleListener* l);
    /**
     * Request a throttle, given a decoder address. When the decoder address
     * is located, the ThrottleListener gets a callback via the ThrottleListener.notifyThrottleFound
     * method.
     * @param la DccLocoAddress of the decoder desired.
     * @param l The ThrottleListener awaiting notification of a found throttle.
     * @return True if the request will continue, false if the request will not
     * be made. False may be returned if a the throttle is already in use.
     */
    /*public*/ bool requestThrottle(DccLocoAddress* la, BasicRosterEntry* re, ThrottleListener* l);
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
    /*public*/ bool requestThrottle(int address, ThrottleListener* l);
    /**
     * Abstract member to actually do the work of configuring a new throttle,
     * usually via interaction with the DCC system
     */
    /*abstract public*/virtual void requestThrottleSetup(LocoAddress* a, bool control) = 0;
    /**
    * Abstract member to actually do the work of configuring a new throttle,
    * usually via interaction with the DCC system
    */
   /*public*/ void requestThrottleSetup(LocoAddress* a);
    /**
     * Cancel a request for a throttle
     * @param address The decoder address desired.
     * @param isLong True if this is a request for a DCC long (extended) address.
     * @param l The ThrottleListener cancelling request for a throttle.
     */
    /*public*/ void cancelThrottleRequest(int address, bool isLong, ThrottleListener* l);
    /*public*/ void cancelThrottleRequest(BasicRosterEntry* re, ThrottleListener* l);
    /**
     * Cancel a request for a throttle.
     * <P>
     * This is a convenience version of the call, which uses system-specific
     * logic to tell whether the address is a short or long form.
     * @param address The decoder address desired.
     * @param l The ThrottleListener cancelling request for a throttle.
     */
    /*public*/ void cancelThrottleRequest(int address, ThrottleListener* l);
    /**
     * If the system-specific ThrottleManager has been unable to create the DCC
     * throttle then it needs to be removed from the throttleListeners, otherwise
     * any subsequent request for that address results in the address being reported
     * as already in use, if singleUse is set.
     * This also sends a notification message back to the requestor with a string
     * reason as to why the request has failed.
     * @param address The DCC Loco Address that the request failed on.
     * @param reason A text string passed by the ThrottleManae as to why
     */
    /*public*/ void failedThrottleRequest(DccLocoAddress* address, QString reason);
    /**
     * Handle throttle information when it's finally available, e.g. when
     * a new Throttle object has been created.
     * <P>
     * This method creates a throttle for all ThrottleListeners of that address
     * and notifies them via the ThrottleListener.notifyThrottleFound method.
     */
    /*public*/ void notifyThrottleKnown(DccThrottle* throttle, LocoAddress* addr);
    /**
     * Check to see if the Dispatch Button should be enabled or not
     * Default to true, override if necessary
     **/
    /*public*/ bool hasDispatchFunction();
    /**
     * What speed modes are supported by this system?
     * value should be xor of possible modes specifed by the
     * DccThrottle interface
     */
    /*public*/ int supportedSpeedModes();
    /*public*/ void attachListener(BasicRosterEntry* re, PropertyChangeListener* p);
    /*public*/ void attachListener(DccLocoAddress* la, PropertyChangeListener* p);
    /*public*/ void attachListener(DccLocoAddress* la, BasicRosterEntry* re, PropertyChangeListener* p);
    /*public*/ void removeListener(DccLocoAddress* la, PropertyChangeListener* p);
    /*public*/ bool addressStillRequired(DccLocoAddress* la);
    /*public*/ void releaseThrottle(DccThrottle* t, ThrottleListener* l);
    /*public*/ bool disposeThrottle(DccThrottle* t, ThrottleListener* l);
    /*public*/ void dispatchThrottle(DccThrottle* t, ThrottleListener* l);
    /*public*/ QVariant getThrottleInfo(DccLocoAddress* la, QString item);
    /*public*/ QString getAddressTypeString(LocoAddress::Protocol prot);

signals:
    
public slots:
private:
    Logger* log;
    QObject* parent;
    /**
     * throttleListeners is indexed by the address, and
     * contains as elements an ArrayList of ThrottleListener
     * objects.  This allows more than one to request a throttle
     * at a time, the entries in this Hashmap are only valid during the
     * throttle setup process.
     */
    /*private*/ QHash<DccLocoAddress*,QList<WaitingThrottle*>* >* throttleListeners;// = new QHash<DccLocoAddress,QList<WaitingThrottle>>(5);
    /**
     * listenerOnly is indexed by the address, and
     * contains as elements an ArrayList of propertyChangeListeners
     * objects that have requested notification of changes to a throttle that
     * hasn't yet been created/
     * The entries in this Hashmap are only valid during the throttle setup process.
     */
    /*private*/ QHash<DccLocoAddress*,QList<WaitingThrottle*>* >* listenerOnly;// = new HashMap<DccLocoAddress,ArrayList<WaitingThrottle>>(5);
    //This keeps a map of all the current active DCC loco Addresses that are in use.
    /**
     * addressThrottles is indexed by the address, and
     * contains as elements a subclass of the throttle assigned to an address and
     * the number of requests and active users for this address.
     */
    /*private*/ QHash<DccLocoAddress*,Addresses*>* addressThrottles;// = new QHash<DccLocoAddress*,Addresses>();
    /*private*/ void cancelThrottleRequest(DccLocoAddress* la, ThrottleListener* l);

protected:
    /*protected*/ SystemConnectionMemo* adapterMemo;

    /*protected*/ QString userName;// = "Internal";
    /**
     * Does this DCC system allow a Throttle (e.g. an address) to be used
     * by only one user at a time?
     */
    /*protected*/ bool singleUse();
    /*protected*/ bool addressReleased(DccLocoAddress* la, ThrottleListener* l);
};

#endif // ABSTRACTTHROTTLEMANAGER_H
