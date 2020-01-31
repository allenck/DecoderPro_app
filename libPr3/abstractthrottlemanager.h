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
 bool _canHandleDecisions;
public:
 WaitingThrottle(ThrottleListener* _l, BasicRosterEntry* _re, bool _canHandleDecisions);
 WaitingThrottle(PropertyChangeListener* _pl, BasicRosterEntry* _re, bool _canHandleDecisions);
 PropertyChangeListener* getPropertyChangeListener();
 ThrottleListener* getListener();
 BasicRosterEntry* getRosterEntry();
 bool canHandleDecisions() {
  return _canHandleDecisions;
 }
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
    /*public*/ QList<locoAddress::Protocol> getAddressProtocolTypes();
    /*public*/ locoAddress* getAddress(QString value,locoAddress::Protocol protocol);
    /*public*/ locoAddress* getAddress(QString value, QString protocol);
    /*public*/ locoAddress::Protocol getProtocolFromString(QString selection);
    QT_DEPRECATED /*public*/ bool requestThrottle(BasicRosterEntry* re, ThrottleListener* l);
    QT_DEPRECATED /*public*/ bool requestThrottle(int address, bool isLongAddress, ThrottleListener* l);
    QT_DEPRECATED /*public*/ bool requestThrottle(locoAddress *la, ThrottleListener* l);
    /*public*/ bool requestThrottle(int address, bool isLongAddress, ThrottleListener* l, bool canHandleDecisions);
    /*public*/ bool requestThrottle(/*@Nonnull*/ BasicRosterEntry* re, ThrottleListener* l, bool canHandleDecisions);
    /*public*/ bool requestThrottle(locoAddress* la, ThrottleListener* l, bool canHandleDecisions);
    QT_DEPRECATED /*public*/ bool requestThrottle(locoAddress* la, BasicRosterEntry* re, ThrottleListener* l);
    /*public*/ bool requestThrottle(int address, ThrottleListener* l);
    /*public*/ bool requestThrottle(int address, ThrottleListener* l, bool canHandleDecisions);

    /**
     * Abstract member to actually do the work of configuring a new throttle,
     * usually via interaction with the DCC system
     */
    /*abstract public*/virtual void requestThrottleSetup(locoAddress* /*a*/, bool /*control*/) {}
    /**
    * Abstract member to actually do the work of configuring a new throttle,
    * usually via interaction with the DCC system
    */
   /*public*/ void requestThrottleSetup(locoAddress* a);
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
    /*public*/ void failedThrottleRequest(locoAddress *address, QString reason);
    /**
     * Handle throttle information when it's finally available, e.g. when
     * a new Throttle object has been created.
     * <P>
     * This method creates a throttle for all ThrottleListeners of that address
     * and notifies them via the ThrottleListener.notifyThrottleFound method.
     */
    /*public*/ void notifyThrottleKnown(DccThrottle* throttle, locoAddress* addr);
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
    /*public*/ QString getAddressTypeString(locoAddress::Protocol prot);
    /*public*/ void responseThrottleDecision(int address, bool isLong, ThrottleListener* l, ThrottleListener::DecisionType decision);
    /*public*/ void responseThrottleDecision(locoAddress* address, ThrottleListener* l, ThrottleListener::DecisionType decision);

signals:
    
public slots:
private:
    static Logger* log;
    QObject* parent;
    /**
     * throttleListeners is indexed by the address, and
     * contains as elements an ArrayList of ThrottleListener
     * objects.  This allows more than one to request a throttle
     * at a time, the entries in this Hashmap are only valid during the
     * throttle setup process.
     */
    /*private*/ QHash<locoAddress*,QList<WaitingThrottle*>* >* throttleListeners;// = new QHash<DccLocoAddress,QList<WaitingThrottle>>(5);
    /*private*/ QList<WaitingThrottle*>* getWaiting(locoAddress* addr);

    /**
     * listenerOnly is indexed by the address, and
     * contains as elements an ArrayList of propertyChangeListeners
     * objects that have requested notification of changes to a throttle that
     * hasn't yet been created/
     * The entries in this Hashmap are only valid during the throttle setup process.
     */
    /*private*/ QHash<locoAddress*,QList<WaitingThrottle*>* >* listenerOnly;// = new HashMap<DccLocoAddress,ArrayList<WaitingThrottle>>(5);
    //This keeps a map of all the current active DCC loco Addresses that are in use.
    /**
     * addressThrottles is indexed by the address, and
     * contains as elements a subclass of the throttle assigned to an address and
     * the number of requests and active users for this address.
     */
    /*private*/ QHash<locoAddress*,Addresses*>* addressThrottles;// = new QHash<DccLocoAddress*,Addresses>();
    /*private*/ void cancelThrottleRequest(locoAddress *la, ThrottleListener* l);

protected:
    /*protected*/ SystemConnectionMemo* adapterMemo;

    /*protected*/ QString userName;// = "Internal";
    /**
     * Does this DCC system allow a Throttle (e.g. an address) to be used
     * by only one user at a time?
     */
    /*protected*/ bool singleUse();
    /*protected*/ bool addressReleased(DccLocoAddress* la, ThrottleListener* l);
    /*protected*/ void makeHardwareDecision(locoAddress* address, ThrottleListener::DecisionType question);
    /*protected*/ void notifyDecisionRequest(locoAddress* address, ThrottleListener::DecisionType question);
    /*protected*/ bool requestThrottle(locoAddress* la, BasicRosterEntry* re, ThrottleListener* l, bool canHandleDecisions);
    /*protected*/ void updateNumUsers( locoAddress* la, int numUsers );

    friend class RetrySetup;
    friend class LnThrottleManager;
};

#endif // ABSTRACTTHROTTLEMANAGER_H
