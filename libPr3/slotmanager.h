#ifndef SLOTMANAGER_H
#define SLOTMANAGER_H

#include "lntrafficcontroller.h"
#include "abstractprogrammer.h"
#include "QTimer"
#include "loconetslot.h"
#include "loconetthrottledtransmitter.h"
#include "slotlistener.h"
#include "loconetsystemconnectionmemo.h"
#include "logger.h"
#include <QThread>
#include "exceptions.h"
#include "Roster/abstractidentify.h"
#include "Roster/cvvalue.h"
#include "dccconsist.h"
#include "simpleprogframe.h"
#include "runnable.h"
#include "programmingmode.h"
#include "sleeperthread.h"
#include "timertask.h"

/**
 * Controls a collection of slots, acting as the
 * counter-part of a LocoNet command station.
 * <P>
 * A SlotListener can register to hear changes. By registering here, the SlotListener
 * is saying that it wants to be notified of a change in any slot.  Alternately,
 * the SlotListener can register with some specific slot, done via the LocoNetSlot
 * object itself.
 * <p>
 * Strictly speaking, functions 9 through 28 are not in the
 * actual slot, but it's convenient to imagine there's an
 * "extended slot" and keep track of them here.  This is a
 * partial implementation, though, because setting is still
 * done directly in {@link LocoNetThrottle}. In particular,
 * if this slot has not been read from the command station,
 * the first message directly setting F9 through F28 will
 * not have a place to store information. Instead, it will
 * trigger a slot read, so the following messages
 * will be properly handled.
 * <P>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project.  That permission
 * does not extend to uses in other software products.  If you wish to
 * use this code, algorithm or these message formats outside of JMRI, please
 * contact Digitrax Inc for separate permission.
 * <P>
 * This Programmer implementation is single-user only. It's not clear whether
 * the command stations can have multiple programming requests outstanding
 * (e.g. service mode and ops mode, or two ops mode) at the same time, but this
 * code definitely can't.
 * <P>
 * @author	Bob Jacobsen  Copyright (C) 2001, 2003
 * @version     $Revision: 20788 $
 */
class CsOpSwAccess;
class LnCommandStationType;
class LocoNetSystemConnectionMemo;
class Logger;
class LIBPR3SHARED_EXPORT SlotManager : public  AbstractProgrammer, public LocoNetListener, public CommandStation
{
 Q_OBJECT
 Q_INTERFACES(LocoNetListener CommandStation)
public:
    /**
     * Time to wait after programming operation complete on LocoNet
     * before reporting completion and hence starting next operation
     */
    static /*public*/ int postProgDelay;// = 100; // this is public to allow changes via script

    /*public*/ int slotScanInterval = 50; // this is public to allow changes via script and tests
     /**
     * slotMapEntry - a from to pair of slot numbers defining a valid range of loco/system slots
     * TODO add slottype, eg systemslot, std slot, expanded slot etc
     * @author sg
     *
     */
    /*static*/ /*public*/ class SlotMapEntry {
     public:
        /*public*/ SlotMapEntry(int from, int to) {
            fromSlot = from;
            toSlot = to;
        }
        int fromSlot;
        int toSlot;
        /*public*/ int getFrom() {
            return fromSlot;
        }
        /*public*/ int getTo() {
            return toSlot;
        }
    };
    /*public*/ QList<SlotMapEntry*> slotMap = QList<SlotMapEntry*>();


    SlotManager(LnTrafficController* tc, QObject *parent = nullptr);
    /**
     * Send a DCC packet to the rails. This implements the CommandStation interface.
     * @param packet
     */
    bool sendPacket(QByteArray packet, int repeats);
    /**
     * Access the information in a specific slot.  Note that this is a
     * mutable access, so that the information in the LocoNetSlot object
     * can be changed.
     * @param i  Specific slot, counted starting from zero.
     * @return   The Slot object
     */
    LocoNetSlot* slot(int i);
    /**
     * Obtain a slot for a particular loco address.
     * <P>This requires access to the command station, even if the
     * locomotive address appears in the current contents of the slot
     * array, to ensure that our local image is up-to-date.
     * <P>
     * This method sends an info request.  When the echo of this is
     * returned from the LocoNet, the
     * next slot-read is recognized as the response.
     * <P>
     * The object that's looking for this information must provide
     * a SlotListener to notify when the slot ID becomes available.
     * <P>
     * The SlotListener is not subscribed for slot notifications; it can
     * do that later if it wants.  We don't currently think that's a race
     * condition.
     * @param i  Specific slot, counted starting from zero.
     * @param l  The SlotListener to notify of the answer.
     */
    void slotFromLocoAddress(int i, SlotListener* l);
    void addSlotListener(SlotListener* l);
    void removeSlotListener(SlotListener* l);
    /**
     * Determine whether this Programmer implementation is capable of
     * reading decoder contents. This is entirely determined by
     * the attached command station, not the code here, so it
     * refers to the mCanRead member variable which is recording
     * the known state of that.
     * @return True if reads are possible
     */
    virtual bool getCanRead();

//    /**
//     * Configure whether this Programmer implementation is capable of
//     * reading decoder contents. <P>
//     * This is not part of the Programmer interface, but is used
//     * as part of the startup sequence for the LocoNet objects.
//     *
//     * @param pCanRead True if reads are possible
//     */
//    void setCanRead(bool pCanRead);
    /**
     * Determine whether this Programmer implementation powers off the
     * main track after a service track programming operation.
     * This is entirely determined by
     * the attached command station, not the code here, so it
     * refers to the mProgPowersOff member variable which is recording
     * the known state of that.
     * @return True if main track off after service operation
     */
    bool getProgPowersOff();

    /**
     * Configure whether this Programmer owers off the
     * main track after a service track programming operation.<P>
     * This is not part of the Programmer interface, but is used
     * as part of the startup sequence for the LocoNet objects.
     *
     * @param pProgPowersOff True if power is off afterward
     */
    void setProgPowersOff(bool pProgPowersOff);
    /**
     * Set the command station type
     */
    void setCommandStationType(LnCommandStationType* value);
    /**
     * Provide a ThrottledTransmitter for sending immediate packets
     */
    void setThrottledTransmitter(LocoNetThrottledTransmitter* value, bool m);
    /**
     * Get the command station type
     */
    LnCommandStationType* getCommandStationType();
    /**
     * Determine is a mode is available for this Programmer implementation
     * @param mode A mode constant from the Programmer interface
     * @return True if paged or register mode
     */
//    virtual bool hasMode(int mode);
    void setSystemConnectionMemo(LocoNetSystemConnectionMemo* memo);
    /**> 0
     * Listen to the LocoNet. This is just a steering routine, which invokes
     * others for the various processing steps.
     * @param m incoming message
     */
//    void message(LocoNetMessage* m); // moved to slots
    /**
     * If this is a direct function command, return -1,
     * otherwise return DCC address word
     */
    int getDirectFunctionAddress(LocoNetMessage* m);

    /* if this is a direct DCC packet, return as one long
     * else return -1. Packet does not include
     * address bytes.
     */
    int getDirectDccPacket(LocoNetMessage* m);
    /**
     * True if the message is an external DCC packet
     * request for F9-F28
     */
    bool isExtFunctionMessage(LocoNetMessage* m);
    /**
     * FInd the slot number that a message references
     */
    int findSlotFromMessage(LocoNetMessage* m);
    void forwardMessageToSlot(LocoNetMessage* m, int i); // protected??

    /**
     * a Map of the CS slots.
     */
    /*synchronized*/ /*public*/ void update(QList<SlotMapEntry*> inputSlotMap, int interval);

    /**
     * Start the process of checking each slot for contents.
     * <P>
     * This is not invoked by this class, but can be invoked
     * from elsewhere to start the process of scanning all
     * slots to update their contents.
     */
    void update();
    /**
     * Send a message requesting the data from a particular slot.
     * @param slot Slot number
     */
    void sendReadSlot(int slot);
    /**
     * Provide a snapshot of the slots in use
     */
    int getInUseCount();
    void writeCVOpsMode(QString CVname, int val, ProgListener* p, int addr, bool longAddr) throw(ProgrammerException);
    void writeCV(QString cvNum, int val, ProgListener* p) throw(ProgrammerException);
    void doWrite(int CV, int val, ProgListener* p, int pcmd) throw(ProgrammerException);
    void confirmCVOpsMode(int CV, int val, ProgListener* p,
                          int addr, bool longAddr) throw(ProgrammerException);
    //void confirmCV(int CV, int val, ProgListener* p) throw(ProgrammerException);
    void doConfirm(int CV, int val, ProgListener* p, int pcmd) /*throw(ProgrammerException)*/;
    /**
     * Invoked by LnOpsModeProgrammer to start an ops-mode
     * read operation.
     * @param CV Which CV to read
     * @param p Who to notify on complete
     * @param addr Address of the locomotive
     * @param longAddr true if a long address, false if short address
     * @throws ProgrammerException
     */
    void readCVOpsMode(QString CVname, ProgListener* p, int addr, bool longAddr) throw(ProgrammerException);
    void doRead(int CV, ProgListener* p, int progByte) throw(ProgrammerException);
    QString getUserName();
    QString getSystemPrefix();
    LocoNetSystemConnectionMemo* getSystemConnectionMemo();
    /*public*/ void readCV(QString CV, ProgListener* p) throw (ProgrammerException);
    /*public*/ void confirmCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
    /*public*/ QList<QString> getSupportedModes();
    /*public*/ Programmer::WriteConfirmMode getWriteConfirmMode(QString addr);
    /*public*/ void setTranspondingAvailable(bool val);
    /*public*/ bool getTranspondingAvailable();

    ///*default*/ /*public*/ void notifyProgListenerEnd(ProgListener* p, int value, int status);
    /*public*/ QObject* self() {return (QObject*)this;}
    /*public*/ void dispose();

signals:
    void changedSlot(LocoNetSlot* s);
    void propertyChange(PropertyChangeEvent*);
    //void programmerException(QString);
    void notifyChangedSlot(LocoNetSlot*);

public slots:
 void message(LocoNetMessage* m);

private:
 int LONG_TIMEOUT;
 QTimer* staleSlotCheckTimer = nullptr;
 LnTrafficController* tc = nullptr;
 Logger* log;
 QVector<LocoNetSlot*> _slots;
 QMutex mutex;
 /**
  * Provide a mapping between locomotive addresses and the
  * SlotListener that's interested in them
  */
 QHash<int,SlotListener*> mLocoAddrHash;
 // data members to hold contact with the slot listeners
 QVector<SlotListener*> slotListeners;
 /**
  * Stores the opcode of the previously-processed message for context.
  * This is needed to know whether a SLOT DATA READ is a response to
  * a REQ LOCO ADDR, for example.
  */
 int lastMessage =-1;
/**
 * Remember whether the attached command station
 * needs a sequence sent after programming.
 * The default operation is implemented in doEndOfProgramming
 * and turns power back on by sending a GPON message.
 */
/*private*/ bool mProgEndSequence = false;
 /**
  * Remember whether the attached command station can read from
  * Decoders.
  */
 bool mCanRead = true;

 LocoNetMessage* immedPacket = nullptr;
 LocoNetThrottledTransmitter* throttledTransmitter = nullptr;
 bool mTurnoutNoRetry = false;
 /**
  * Remember whether the attached command station has powered
  * off the main track after programming
  */
 bool mProgPowersOff = false;
 int progState = 0;
 // 1 is commandPending
 // 2 is commandExecuting
 // 0 is notProgramming
 bool _progRead = false;
 bool _progConfirm = false;
 int _confirmVal;
 bool mServiceMode = true;
 int hopsa; // high address for CV read/write
 int lopsa; // low address for CV read/write
 ProgListener* _usingProgrammer = nullptr;
 QTimer* mPowerTimer= nullptr;
 LocoNetSystemConnectionMemo* adaptermemo = nullptr;
 ProgrammingMode* csOpSwProgrammingMode;// = new ProgrammingMode(
//             "LOCONETCSOPSWMODE",
//             Bundle.getMessage("LOCONETCSOPSWMODE"));
 CsOpSwAccess* csOpSwAccessor = nullptr;
 bool transpondingAvailable = false;


private slots:
 /**
  * method to scan the slot array looking for slots that are in-use but have
  * not had any updates in over 90s and issue a read slot request to update
  * their state as the command station may have purged or stopped updating
  * the slot without telling us via a LocoNet message.
  *
  * This is intended to be called from the staleSlotCheckTimer
  */
 void checkStaleSlots();
 /**
  * Information on slot state is stored in an array of LocoNetSlot objects.
  * This is declared final because we never need to modify the array itself,
  * just its contents.
  */
 /**
  * internal method to notify of the final result
  * @param value The cv value to be returned
  * @param status The error code, if any
  */
 void notifyProgListenerEnd(int value=-1, int status=0);
 /**
  * Internal routine to handle a timeout & turn power off
  */
 void doEndOfProgramming();

protected:
 LnCommandStationType* commandStationType;
 /**
  * Trigger the notification of all SlotListeners.
  * @param s The changed slot to notify.
  */
 //@SuppressWarnings("unchecked")
 void notify(LocoNetSlot* s);
 void respondToAddrRequest(LocoNetMessage* m, int i);
 void programmerOpMessage(LocoNetMessage* m, int i);
 /**
  * Records the current mode of the Programmer implementation.
 */
// ProgrammerMode* _mode;
 /**
  * Trigger notification of PropertyChangeListeners. The only bound
  * property is Mode from the Programmer interface. It is not clear
  * why this is not in AbstractProgrammer...
  * @param name Changed property
  * @param oldval
  * @param newval
  */
 //@SuppressWarnings("unchecked")
 void notifyPropertyChange(QString name, int oldval, int newval);
 /**
  * Internal method to notify of the LACK result.
  * This is a separate routine from nPLRead in case we need to handle something later
  * @param status The error code, if any
  */
 void notifyProgListenerLack(int status);
 /**
  * Internal routine to forward a programing reply.
  * This is delayed to prevent overruns of the
  * command station.
  * @param value the value to return
  * @param status The error code, if any
  */
 void sendProgrammingReply(ProgListener* p, int value, int status);
 /**
  * Internal routine to stop power timer, as another programming
  * operation has happened
  */
  void stopEndOfProgrammingTimer();
 /**
  * Internal routine to handle timer restart if needed to restore
  * power.  This is only needed in service mode.
  */
 /*protected*/ void restartEndOfProgrammingTimer();
 int nextReadSlot = 0;
 // internal method to remember who's using the programmer
 void useProgrammer(ProgListener* p); // throws jmri.ProgrammerException {

 /**
  * Internal method to create the LocoNetMessage for programmer task start
  */
 LocoNetMessage* progTaskStart(int pcmd, int val, int cvnum, bool write);
 /*protected*/ bool checkLackByte1 (int Byte1) ;
 /*protected*/ bool checkLackTaskAccepted (int Byte2);
 /*protected*/ bool checkLackProgrammerBusy (int Byte2);
 /*protected*/ bool checkLackAcceptedBlind (int Byte2);
 /*protected*/ void handleLongAck (LocoNetMessage* m);
 /*protected*/ void loadSlots();
 /*final*/ static /*protected*/ int NUM_SLOTS;// = 128;
 /*protected*/ void getMoreDetailsForSlot(LocoNetMessage* m, int i);
 /*protected*/ void sendReadSlotDelayed(int slotNo, long delay);

protected slots:
 void readNextSlot(int toSlot, int interval);
 void On_notifyProgListenerEnd();
 /*synchronized*/ /*protected*/ void timeout();

 friend class SlotManagerTest;
 friend class LnDeferProgrammer;
 friend class LnPredefinedMeters;
 friend class SMTimerTask;
};



class SendProgrammingReplyDelay : public QObject
{
 Q_OBJECT
 ProgListener* p;
 int value;
 int status;
 int delay;
 SlotManager* slotManager;
public:
 SendProgrammingReplyDelay(ProgListener* p, int value, int status, int delay, SlotManager* slotManager);

public slots:
 void timeout();
signals:
 void on_programmingOpReply(int value, int status);
};

class SMTimerTask : public TimerTask
{
  Q_OBJECT
  int slotNumber;// = slotNo;
  SlotManager* sm;
public:
  SMTimerTask (int slotNumber, SlotManager* sm) {
   this->slotNumber = slotNumber;
   this->sm = sm;
  }
  //@Override
  /*public*/ void run() {
      try {
          sm->sendReadSlot(slotNumber);
      } catch (Exception e) {
          sm->log->error("Exception occurred sendReadSlotDelayed:", e);
      }
  }
};

#endif // SLOTMANAGER_H
