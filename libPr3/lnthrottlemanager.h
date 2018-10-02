#ifndef LNTHROTTLEMANAGER_H
#define LNTHROTTLEMANAGER_H
#include "abstractthrottlemanager.h"
#include "slotmanager.h"
/**
 * LocoNet implementation of a ThrottleManager.
 * <P>
 * Works in cooperation with the SlotManager, which actually
 * handles the communications.
 *
 * @see SlotManager
 * @author		Bob Jacobsen  Copyright (C) 2001
 * @version 		$Revision: 20637 $
 */

class LIBPR3SHARED_EXPORT LnThrottleManager : public AbstractThrottleManager
{
    Q_OBJECT
public:
    explicit LnThrottleManager(LocoNetSystemConnectionMemo* memo, QObject *parent = 0);
    /**
     * Start creating a Throttle object.
     *
     * This returns directly, having arranged for the Throttle
     * object to be delivered via callback
     */
    /*public*/ void requestThrottleSetup(LocoAddress* address, bool control);
    /**
     * LocoNet does have a Dispatch function
     **/
    /*public*/ virtual bool hasDispatchFunction();
    /**
     * What speed modes are supported by this system?
     * value should be xor of possible modes specifed by the
     * DccThrottle interface
     */
    /*public*/ virtual int supportedSpeedModes();

    /**
     * Address 128 and above is a long address
     **/
    /*public*/ virtual bool canBeLongAddress(int address);
    /**
     * Address 127 and below is a short address
     **/
    /*public*/ virtual bool canBeShortAddress(int address);
    /**
     * Are there any ambiguous addresses (short vs long) on this system?
     */
    /*public*/ bool addressTypeUnique();
    /*
     * Local method for deciding short/long address
     */
    /*public*/ virtual bool disposeThrottle(DccThrottle* t, ThrottleListener* l);
    /*public*/ virtual void dispatchThrottle(DccThrottle* t, ThrottleListener* l);
    /*public*/ void releaseThrottle(DccThrottle* t, ThrottleListener* l);

signals:
    
public slots:
 /**
  * SlotListener contract. Get notification that an address has changed slot.
  * This method creates a throttle for all ThrottleListeners of that address
  * and notifies them via the ThrottleListener.notifyThrottleFound method.
  */
 /*public*/ void notifyChangedSlot(LocoNetSlot* s);
protected:
 SlotManager* slotManager;
 LnTrafficController* tc;
 /**
  * LocoNet allows multiple throttles for the same device
  */
 bool singleUse();
 /*
  * Local method for deciding short/long address
  */
 /*protected*/ static bool isLongAddress(int num);
 friend class LocoNetConsistManager;
 friend class LocoNetThrottle;
};
//bool LnThrottleManager::isLongAddress(int num);
#endif // LNTHROTTLEMANAGER_H
