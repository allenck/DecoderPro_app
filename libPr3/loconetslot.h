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

    // status accessors
    // decoder mode
    // possible values are  DEC_MODE_128A, DEC_MODE_28A, DEC_MODE_128,
    //						DEC_MODE_14, DEC_MODE_28TRI, DEC_MODE_28
    int decoderType() 	{ return stat&LnConstants::DEC_MODE_MASK;}

    // slot status
    // possible values are LOCO_IN_USE, LOCO_IDLE, LOCO_COMMON, LOCO_FREE
    int slotStatus() 	{ return stat&LnConstants::LOCOSTAT_MASK; }
    int ss2()            { return _ss2; }

    // consist status
    // possible values are CONSIST_MID, CONSIST_TOP, CONSIST_SUB, CONSIST_NO
    int consistStatus() 	{ return stat&LnConstants::CONSIST_MASK; }

    // direction and functions
    bool isForward()	{ return 0==(_dirf&LnConstants::DIRF_DIR); }
    bool isF0()	{ return 0!=(_dirf&LnConstants::DIRF_F0); }
    bool isF1()	{ return 0!=(_dirf&LnConstants::DIRF_F1); }
    bool isF2()	{ return 0!=(_dirf&LnConstants::DIRF_F2); }
    bool isF3()	{ return 0!=(_dirf&LnConstants::DIRF_F3); }
    bool isF4()	{ return 0!=(_dirf&LnConstants::DIRF_F4); }
    bool isF5()	{ return 0!=(_snd&LnConstants::SND_F5); }
    bool isF6()	{ return 0!=(_snd&LnConstants::SND_F6); }
    bool isF7()	{ return 0!=(_snd&LnConstants::SND_F7); }
    bool isF8()	{ return 0!=(_snd&LnConstants::SND_F8); }
    bool isF9()	 { return localF9; }
    bool isF10()	{ return localF10; }
    bool isF11()	{ return localF11; }
    bool isF12()	{ return localF12; }
    bool isF13()	{ return localF13; }
    bool isF14()	{ return localF14; }
    bool isF15()	{ return localF15; }
    bool isF16()	{ return localF16; }
    bool isF17()	{ return localF17; }
    bool isF18()	{ return localF18; }
    bool isF19()	{ return localF19; }
    bool isF20()	{ return localF20; }
    bool isF21()	{ return localF21; }
    bool isF22()	{ return localF22; }
    bool isF23()	{ return localF23; }
    bool isF24()	{ return localF24; }
    bool isF25()	{ return localF25; }
    bool isF26()	{ return localF26; }
    bool isF27()	{ return localF27; }
    bool isF28()	{ return localF28; }

    // loco address, speed
    int locoAddr()   	{ return addr; }
    int speed()      	{ return spd; }
    int dirf() 	    	{ return _dirf; }
    int snd()  	    	{ return _snd; }
    int id()		{ return _id; }

    // programmer track special case accessors
    int pcmd()          	{ return _pcmd; }
    int cvval()          { return _snd+(_ss2&2)*64; }
    // global track status should be reference through SlotManager

    // create a specific slot
    //public LocoNetSlot(int slotNum)  { slot = slotNum;}
    LocoNetSlot(LocoNetMessage* l, QObject *parent = 0)  throw (LocoNetException);
    void setSlot(LocoNetMessage* l) throw (LocoNetException);
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
protected:
 void notifySlotListeners();
friend class LnClockControl;
friend class LocoNetSlotTest;
};

#endif // LOCONETSLOT_H
