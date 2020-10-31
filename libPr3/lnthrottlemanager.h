#ifndef LNTHROTTLEMANAGER_H
#define LNTHROTTLEMANAGER_H
#include "abstractthrottlemanager.h"
#include "slotmanager.h"
#include "slotlistener.h"

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
class ThrottleRequest;
class LIBPR3SHARED_EXPORT LnThrottleManager : public AbstractThrottleManager, public SlotListener
{
    Q_OBJECT
 Q_INTERFACES(SlotListener)
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
    /*public*/ bool hasDispatchFunction() override;
    /**
     * What speed modes are supported by this system?
     * value should be xor of possible modes specifed by the
     * DccThrottle interface
     */
    /*public*/ QSet<SpeedStepMode::SSMODES> supportedSpeedModes() override;

    /**
     * Address 128 and above is a long address
     **/
    /*public*/  bool canBeLongAddress(int address) override;
    /**
     * Address 127 and below is a short address
     **/
    /*public*/ bool canBeShortAddress(int address) override;
    /**
     * Are there any ambiguous addresses (short vs long) on this system?
     */
    /*public*/ bool addressTypeUnique() override;
    /*
     * Local method for deciding short/long address
     */
    /*public*/ virtual bool disposeThrottle(DccThrottle* t, ThrottleListener* l) override;
    /*public*/ virtual void dispatchThrottle(DccThrottle* t, ThrottleListener* l) override;
    /*public*/ void releaseThrottle(DccThrottle* t, ThrottleListener* l) override;
    /*public*/ void failedThrottleRequest(LocoAddress* address, QString reason);
    /*public*/ void cancelThrottleRequest(LocoAddress* address, ThrottleListener* l) override;
    /*public*/ int getThrottleID();
    /*public*/ void notifyStealRequest(int locoAddr);
    /*public*/ void responseThrottleDecision(LocoAddress* address, ThrottleListener* l, ThrottleListener::DecisionType decision) override;
    QObject* self()  override{return (QObject*)this;}

signals:
    
public slots:
 /**
  * SlotListener contract. Get notification that an address has changed slot.
  * This method creates a throttle for all ThrottleListeners of that address
  * and notifies them via the ThrottleListener.notifyThrottleFound method.
  */
 /*public*/ void notifyChangedSlot(LocoNetSlot* s) override;
 /*public*/ void notifyRefused(int address, QString cause);

private:
 void dispose();
 QHash<int, QThread*> waitingForNotification;// = new Hashtable<>(5);
 QHash<int, LocoNetSlot*> slotForAddress;
 /*LinkedBlockingQueue*>*/ QLinkedList<ThrottleRequest*> requestList;
 bool requestOutstanding = false;
 /*private*/ void commitToAcquireThrottle(LocoNetSlot* s);
 /*private*/ void processThrottleSetupRequest(LocoAddress* address, bool control);

 QThread* retrySetupThread = nullptr;
 static Logger* log;
 DccThrottle* createThrottle(LocoNetSystemConnectionMemo* memo, LocoNetSlot* s);

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
 /*protected*/ int throttleID = 0x0171;
 /*protected*/ void processQueuedThrottleSetupRequest();


 friend class LocoNetConsistManager;
 friend class LocoNetThrottle;
 friend class RetrySetup;
 friend class InformRejection;
 friend class LocoNetThrottleTest;
 friend class LocoNetConsistTest;
};

/*
 * Internal class for holding throttleListener/LocoAddress pairs for
 * outstanding requests.
 */
/*protected*/ /*static*/ class ThrottleRequest : public QObject
{
 Q_OBJECT
     /*private*/ LocoAddress* la = nullptr;
     /*private*/ bool tc = false;

     ThrottleRequest(LocoAddress* l,bool control, QObject* parent = nullptr) : QObject(parent){
         la = l;
         tc = control;
     }

     /*public*/ bool getControl(){
        return tc;
     }
     /*public*/ LocoAddress* getAddress(){
        return la;
     }
friend class LnThrottleManager;
};

class RetrySetup : public QObject//Runnable
{  //setup for retries and failure check
Q_OBJECT
    DccLocoAddress* address;
    //SlotListener* list;
    LnThrottleManager* list;
public:
    RetrySetup(DccLocoAddress* address, LnThrottleManager* list) {
     this->address = address;
     this->list = list;
     //this->lnThrottleManager = lnThrottleManager;
    }
public slots:
        //@Override
    /*public*/ void process()  // run
    {
        int attempts = 1; // already tried once above
        int maxAttempts = 10;
        while (attempts <= maxAttempts) {
            try {
                //Thread.sleep(1000); // wait one second
             SleeperThread::sleep(1000);
            } catch (InterruptedException ex) {
                return; // stop waiting if slot is found or error occurs
            }
            QString msg = tr("No response to slot request for %1, attempt %2").arg(address->toString()).arg(attempts); // NOI18N
            if (attempts < maxAttempts) {
                list->slotManager->slotFromLocoAddress(address->getNumber(), (SlotListener*)list);
                msg += ", trying again."; // NOI18N
            }
            list->log->debug(msg);
            attempts++;
        }
        list->log->error(tr("No response to slot request for %1 after %2 attempts.").arg(address->toString()).arg(attempts - 1)); // NOI18N
        list->failedThrottleRequest(address, "Failed to get response from command station");
        list->requestOutstanding = false;
        list->processQueuedThrottleSetupRequest();
    }
    void interrupted()
    {
     throw InterruptedException();
    }
signals:
    void finished();
};
class InformRejection : public Runnable {
 Q_OBJECT
    // inform the throttle from a new thread, so that
    // the modal dialog box doesn't block other LocoNet
    // message handling

    int address;
    QString cause;
    LnThrottleManager* lnThrottleManager;
public:
    InformRejection(int address, QString s, LnThrottleManager* lnThrottleManager) {
        this->address = address;
        this->cause = s;
     this->lnThrottleManager = lnThrottleManager;
    }

    //@Override
    /*public*/ void run() {

        lnThrottleManager->log->debug(tr("New thread launched to inform throttle user of failure to acquire loco %1 - %2").arg(address).arg(cause));
        lnThrottleManager->failedThrottleRequest(new DccLocoAddress(address, lnThrottleManager->isLongAddress(address)), cause);
    }
};

#endif // LNTHROTTLEMANAGER_H
