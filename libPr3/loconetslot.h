#ifndef LOCONETSLOT_H
#define LOCONETSLOT_H

#include <QObject>
#include "loconetmessage.h"
#include "logger.h"
#include "slotlistener.h"
#include "exceptions.h"

class SlotListener;
class LIBPR3SHARED_EXPORT LocoNetSlot : public QObject
{
    Q_OBJECT
public:
    explicit LocoNetSlot(int slot, QObject *parent = 0);
    // accessors to specific information
    int getSlot() { return slot;}  // cannot modify the slot number once created
    /*public*/ int decoderType();
    /*public*/ int slotStatus();
    /*public*/ int ss2();
    virtual /*public*/ int consistStatus();
    /*public*/ bool isForward();
    /*public*/ bool isF0();
    /*public*/ bool isF1();
    /*public*/ bool isF2();
    /*public*/ bool isF3();
    /*public*/ bool isF4();
    /*public*/ bool isF5();
    /*public*/ bool isF6();
    /*public*/ bool isF7();
    /*public*/ bool isF8();
    /*public*/ bool isF9();
    /*public*/ bool isF10();
    /*public*/ bool isF11();
    /*public*/ bool isF12();
    /*public*/ bool isF13();
    /*public*/ bool isF14();
    /*public*/ bool isF15();
    /*public*/ bool isF16();
    /*public*/ bool isF17();
    /*public*/ bool isF18();
    /*public*/ bool isF19();
    /*public*/ bool isF20();
    /*public*/ bool isF21();
    /*public*/ bool isF22();
    /*public*/ bool isF23();
    /*public*/ bool isF24();
    /*public*/ bool isF25();
    /*public*/ bool isF26();
    /*public*/ bool isF27();
    /*public*/ bool isF28();
    /*public*/ int locoAddr();
    virtual /*public*/ int speed();
    /*public*/ int dirf();
    /*public*/ int snd();
    /*public*/ int id();
    /*public*/ int pcmd();
    /*public*/ int cvval();



    // global track status should be reference through SlotManager

    // create a specific slot
    //public LocoNetSlot(int slotNum)  { slot = slotNum;}
    LocoNetSlot(LocoNetMessage* l, QObject *parent = 0)  ;
    void setSlot(LocoNetMessage* l) /*throw (LocoNetException)*/;
    /**
     * Load functions 9 through 28 from loconet "Set Direct"
     * message.
     */
    void functionMessage(long pkt);
    /**
     * Update the decoder type bits in STAT1 (D2, D1, D0)
     * @param status New values for STAT1 (D2, D1, D0)
     * @return Formatted LocoNet message to change value.
     */
    LocoNetMessage* writeMode(int status);
    /*public*/ LocoNetMessage* writeThrottleID(int newID);
    /**
     * Update the status mode bits in STAT1 (D5, D4)
     * @param status New values for STAT1 (D5, D4)
     * @return Formatted LocoNet message to change value.
     */
    LocoNetMessage* writeStatus(int status);
    LocoNetMessage* dispatchSlot();
    /*public*/ LocoNetMessage* releaseSlot();
    LocoNetMessage* writeSlot();
    qint64 getLastUpdateTime() { return lastUpdateTime ; }
    /**
     * Only valid for fast-clock slot.
     * @return "Days" value currently in fast-clock slot.
     */
    int getFcDays();
    /**
     * For fast-clock slot, set "days" value.
     */
    void setFcDays(int val);
    /**
     * Only valid for fast-clock slot.
     * @return "Hours" value currently stored in fast clock slot.
     */
    int getFcHours();
    /**
     * For fast-clock slot, set "hours" value.
     */
    void setFcHours(int val);
    /**
     * Only valid for fast-clock slot.
     * @return Return minutes value currently stored in the fast clock slot.
     */
    int getFcMinutes();
    /**
     * For fast-clock slot, set "minutes" value.
     */
    void setFcMinutes(int val);
    /**
     * Only valid for fast-clock slot.
     * @return Return frac_mins field which is the number of 65ms ticks until then
     * next minute rollover. These ticks step at the current fast clock rate
     */
    int getFcFracMins();
    /**
     * For fast-clock slot, set "frac_mins" value.
     */
    void setFcFracMins(int val);
    /**
     * Only valid for fast-clock slot.
     * @return Rate stored in fast clock slot.
     */
    int getFcRate();
    /**
     * For fast-clock slot, set "rate" value.
     */
    void setFcRate(int val);
    /*public*/ /*synchronized*/ void addSlotListener(SlotListener* l);
    /*public*/ /*synchronized*/ void removeSlotListener(SlotListener* l);
    /*public*/ int getTrackStatus();
    /*public*/ void setTrackStatus(int status);
    /*public*/ bool isFunction(int Fn);

signals:
    //void LocoNetException(QString str = "");
public slots:
    void common(int slotNum);
private:
 bool localF9 ;
 bool localF10;
 bool localF11;
 bool localF12;
 bool localF13;
 bool localF14;
 bool localF15;
 bool localF16;
 bool localF17;
 bool localF18;
 bool localF19;
 bool localF20;
 bool localF21;
 bool localF22;
 bool localF23;
 bool localF24;
 bool localF25;
 bool localF26;
 bool localF27;
 bool localF28;
 // data values to echo slot contents
 int slot;   // <SLOT#> is the number of the slot that was read.
 int stat;	// <STAT> is the status of the slot
 int addr;	// full address of the loco, made from
 //    <ADDR> is the low 7 (0-6) bits of the Loco address
 //    <ADD2> is the high 7 bits (7-13) of the 14-bit loco address
 int spd;	// <SPD> is the current speed (0-127)
 int _dirf;	// <DIRF> is the current Direction and the setting for functions F0-F4
 int trk = 7;	// <TRK> is the global track status
 int _ss2;	// <SS2> is the an additional slot status
 int _snd; 	// <SND> is the settings for functions F5-F8
 int _id;		// throttle id, made from
 //     <ID1> and <ID2> normally identify the throttle controlling the loco

 int _pcmd;  // hold pcmd and pstat for programmer

 qint64 lastUpdateTime ; // Time of last update for detecting stale slots

 // data members to hold contact with the slot listeners
 QVector<SlotListener *> slotListeners;
  static Logger* log;
 QMutex mutex;
 // global track status should be reference through SlotManager
 /*private*/ QVector<bool> getFuncArray();

protected:
 void notifySlotListeners();
friend class LnClockControl;
friend class LocoNetSlotTest;
friend class LnThrottleManager;
};

#endif // LOCONETSLOT_H
