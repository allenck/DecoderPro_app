#include "llnmon.h"

LlnMon::LlnMon(QObject *parent) :
    QObject(parent)
{
 /*
 * Flag that determines if we print loconet opcodes
 */
showOpCode = false;

/**
 * Flag that determines if we show track status on every slot read
 */
showTrackStatus = true;

/**
 * Most recent track status value
 */
trackStatus = -1;
//protected:
/**
 * Global flag to indicate the message was not fully parsed, so the hex
 * should be included.
 */
 forceHex = false;
 locoNetSensorPrefix = "S";
 locoNetTurnoutPrefix = "LT";
 turnoutManager = NULL;
}
/**
 * A utility class for formatting LocoNet packets into human-readable text.
 * <P>
 * Much of this file is a Java-recoding of the display.c file from the llnmon
 * package of John Jabour. Some of the conversions involve explicit decoding of
 * structs defined in loconet.h in that same package. Those parts are (C)
 * Copyright 2001 Ron W. Auld. Use of these parts is by direct permission of the
 * author.
 * <P>
 * Most major comment blocks here are quotes from the Digitrax Loconet(r) OPCODE
 * SUMMARY: found in the Loconet(r) Personal Edition 1.
 * <P>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project. That permission does
 * not extend to uses in other software products. If you wish to use this code,
 * algorithm or these message formats outside of JMRI, please contact Digitrax
 * Inc for separate permission.
 * <P>
 * Note that the formatted strings end in a \n, and may contain more than one
 * line separated by \n. Someday this should be converted to proper Java line
 * handling, but for now it has to be handled in locomon, the sole user of this.
 * (It could be handled by moving the code from locomon into the display member
 * here)
 * <P>
 * Reverse engineering of OPC_MULTI_SENSE was provided by Al Silverstein, used
 * with permission.
 * <P>
 * Reverse engineering of the Duplex Group/Password/Channel management was
 * provided by Leo Bicknell with help from B. Milhaupt, used with permission.
 * <P>
 * Reverse-engineering of device-specific OpSw messages, throttle text
 * message, and throttle semaphore message was provided by B. Milhaupt, used
 * with permission.
 * <P>
 * @author Bob Jacobsen Copyright 2001, 2002, 2003
 * @version $Revision: 22622 $
 */
//public class Llnmon {


/**
 * Convert bytes from LocoNet packet into a locomotive address.
 *
 * @param a1
 *            Byte containing the upper bits.
 * @param a2
 *            Byte containting the lower bits.
 * @return 1-4096 address
 */
int LlnMon::LOCO_ADR(int a1, int a2)
{
 return (((a1 & 0x7f) * 128) + (a2 & 0x7f));
} // end of static private int LOCO_ADR(int a1, int a2)

/**
 * Convert bytes from LocoNet packet into a 1-based address for a sensor or
 * turnout.
 *
 * @param a1
 *            Byte containing the upper bits
 * @param a2
 *            Byte containing the lower bits
 * @return 1-4096 address
 */
int LlnMon::SENSOR_ADR(int a1, int a2)
{
 return (((a2 & 0x0f) * 128) + (a1 & 0x7f)) + 1;
} // end of static private int SENSOR_ADR(int a1, int a2)

/*
 * Take an int and convert it to a dotted version number
 * as used by the LocoIO protocol
 * Example:  123 => 1.2.3
 */

/**
 * Take the LocoIO version number and convert to human friendly format.
 *
 * @param val
 *            The LocoIO version.
 * @return String with human readable format.
 */
QString LlnMon::dotme(int val)
{
 int dit;
 int x = val;
 QString ret;
 if (val == 0)
     return "0";
 while (x != 0)
 {
  dit = x % 10;
  ret.insert(0, QString("%1").arg(dit));
  x = x / 10;
  if (x != 0)
   ret.insert(0, ".");
 }
    return ret/*.toString()*/;
} // end of private String dotme(int val)

/**
 * Convert throttle ID to a human friendly format.
 *
 * @param id1
 *            Byte #1 of the ID.
 * @param id2
 *            Byte #2 of the ID.
 * @return String with human friendly format.
 */
QString LlnMon::idString(int id1, int id2)
{
  return "0x" + QString("%1").arg((id2 & 0x7F),0,16) + " 0x"
            + QString("%1").arg((id1 & 0x7F),0,16) + " ("
           + QString("%1").arg((id2 & 0x7F) * 128 + (id1 & 0x7F)) + ")";
} // end of private String idString(int id1, int id2)

/**
 * This function creates a string representation of the loco address in
 * addressLow & addressHigh in a form appropriate for the type of address (2
 * or 4 digit) using the Digitrax 'mixed mode' if necessary.
 *
 * @param addressLow
 * @param addressHigh
 * @return
 */
QString LlnMon::convertToMixed(int addressLow, int addressHigh)
{
 // if we have a 2 digit decoder address and proceed accordingly
 if (addressHigh == 0)
 {
  if (addressLow >= 120)
   return QString("c%1 (%2)").arg(addressLow-120).arg(addressLow);
  else if (addressLow >= 110)
   return QString("c%1 (%2)").arg(addressLow-110).arg(addressLow);
  else if (addressLow >= 100)
   return QString("c%1 (%2)").arg(addressLow-110).arg(addressLow);
  else
   return QString("%1").arg(addressLow & 0x7f);
 }
 else
 {
  // return the full 4 digit address
  return QString("%1").arg(LOCO_ADR(addressHigh, addressLow));
 }
} // end of private static String convertToMixed(int addressLow, int addressHigh)

/**
 * Format the message into a text string.  If forceHex is set
 * upon return, the message was not fully parsed.
 * @param l Message to parse
 * @return String representation
 */
QString LlnMon::format(LocoNetMessage l)
{

 bool showStatus = false; /* show track status in this message? */

 int minutes; // temporary time values
 int hours;
 int frac_mins;
 //qDebug()<< QString("opcode 0x%1").arg(l.getOpCode() & 0xff,0,16);
 switch (l.getOpCode() & 0xff)
 {
 /*
  * 2 Byte MESSAGE OPCODES * ; FORMAT = <OPC>,<CKSUM> * ; *
  */

     /*
      * OPC_IDLE 0x85 ;FORCE IDLE state, Broadcast emergency STOP
      *
      * Page 8 of LocoNet Personal Edition v1.0.
      */
 case LnConstants::OPC_IDLE:
 {
  return tr("Force Idle, Broadcast Emergency STOP.\n");
 } // case LnConstants::OPC_IDLE

     /*
      * OPC_GPON 0x83 ;GLOBAL power ON request
      *
      * Page 8 of LocoNet Personal Edition v1.0.
      */
case LnConstants::OPC_GPON:
{
     return tr("Global Power ON.\n");
} // case LnConstants::OPC_GPON

     /*
      * OPC_GPOFF 0x82 ;GLOBAL power OFF request
      *
      * Page 8 of LocoNet Personal Edition v1.0.
      */
 case LnConstants::OPC_GPOFF:
 {
     return tr("Global Power OFF.\n");
 } // case LnConstants::OPC_GPOFF

     /*
      * OPC_GPBUSY 0x81 ;MASTER busy code, NULL
      *
      * Page 8 of LocoNet Personal Edition v1.0.
      */
 case LnConstants::OPC_GPBUSY:
 {
     return tr("Master is busy.\n");
 } // case LnConstants::OPC_GPBUSY

 /*
  * ; 4 byte MESSAGE OPCODES
  * ; FORMAT = <OPC>,<ARG1>,<ARG2>,<CKSUM>
  * :
  *  CODES 0xA8 to 0xAF have responses
  *  CODES 0xB8 to 0xBF have responses
  */

     /*
      * OPC_LOCO_ADR     0xBF   ; REQ loco ADR
      *                         ; Follow on message: <E7>SLOT READ
      *                         ; <0xBF>,<0>,<ADR>,<CHK> REQ loco ADR
      *                         ; DATA return <E7>, is SLOT#, DATA that ADR was
      *                         : found in.
      *                         ; IF ADR not found, MASTER puts ADR in FREE slot
      *                         ; and sends DATA/STATUS return <E7>......
      *                         ; IF no FREE slot, Fail LACK,0 is returned
      *                         ; [<B4>,<3F>,<0>,<CHK>]
      *
      * Page 8 of LocoNet Personal Edition v1.0.
      */
 case LnConstants::OPC_LOCO_ADR: {
     int adrHi = l.getElement(1); // Hi address listed as zero above
     int adrLo = l.getElement(2); // ADR above, the low part
     return tr("Request slot for loco address ")
            + convertToMixed(adrLo, adrHi) + ".\n";
 } // case LnConstants::OPC_LOCO_ADR

     /*
      * OPC_SW_ACK       0xBD   ; REQ SWITCH WITH acknowledge function (not DT200)
      *                         ; Follow on message: LACK
      *                         ; <0xBD>,<SW1>,<SW2>,<CHK> REQ SWITCH function
      *                         ;       <SW1> =<0,A6,A5,A4- A3,A2,A1,A0>
      *                         ;               7 ls adr bits.
      *                         ;               A1,A0 select 1 of 4 input pairs
      *                         ;               in a DS54
      *                         ;       <SW2> =<0,0,DIR,ON- A10,A9,A8,A7>
      *                         ;               Control bits and 4 MS adr bits.
      *                         ;               DIR=1 for Closed/GREEN
      *                         ;                  =0 for Thrown/RED
      *                         ;               ON=1 for Output ON
      *                         ;                 =0 FOR output OFF
      *                         ; response is:
      *                         ; <0xB4><3D><00> if DCS100 FIFO is full, rejected.
      *                         ; <0xB4><3D><7F> if DCS100 accepted
      *
      * Page 8 of LocoNet Personal Edition v1.0.
      */
case LnConstants::OPC_SW_ACK: {
     int sw2 = l.getElement(2);
     // get system and user names
     QString turnoutSystemName = "";
     QString turnoutUserName = "";
     turnoutSystemName = locoNetTurnoutPrefix +
             QString("%1").arg(SENSOR_ADR(l.getElement(1), l.getElement(2)));

     try {
         Turnout* turnout = turnoutManager->getBySystemName(turnoutSystemName);
         if ((turnout != NULL) && (turnout->getUserName().length() > 0))
             turnoutUserName = "(" + turnout->getUserName() + ")";
         else
             turnoutUserName = "()";
     }
     catch (Exception e) {
         turnoutUserName = "()";
     }
     return tr("Request switch ")
            + turnoutSystemName + " " + turnoutUserName
            + ((sw2 & /*LnConstants::*/OPC_SW_ACK_CLOSED) != 0 ? tr(" Closed/Green")
                    : tr(" Thrown/Red"))
            + ((sw2 & /*LnConstants::*/OPC_SW_ACK_OUTPUT) != 0 ? tr(" (Output On)")
                    : tr(" (Output Off)")) + tr(" with acknowledgement.\n");
} // case LnConstants::OPC_SW_ACK

    /*
     * OPC_SW_STATE     0xBC   ; REQ state of SWITCH
     *                         ; Follow on message: LACK
     *                         ; <0xBC>,<SW1>,<SW2>,<CHK> REQ state of SWITCH
     *
     * Page 8 of LocoNet Personal Edition v1.0.
     */
 case LnConstants::OPC_SW_STATE: {
     // get system and user names
     QString turnoutSystemName = "";
     QString turnoutUserName = "";
     turnoutSystemName = locoNetTurnoutPrefix +
             QString("%1").arg(SENSOR_ADR(l.getElement(1), l.getElement(2)));
     try {
         Turnout* turnout = turnoutManager->getBySystemName(turnoutSystemName);
         if ((turnout != NULL) && (turnout->getUserName().length() > 0))
             turnoutUserName = "(" + turnout->getUserName() + ")";
         else
             turnoutUserName = "()";
     }
     catch (Exception e) {
         turnoutUserName = "()";
     }
     return tr("Request status of switch ")
            + turnoutSystemName + " " + turnoutUserName
            + ".\n";
 } // case LnConstants::OPC_SW_STATE


     /*
      * OPC_RQ_SL_DATA   0xBB   ; Request SLOT DATA/status block
      *                         ; Follow on message: <E7>SLOT READ
      *                         ; <0xBB>,<SLOT>,<0>,<CHK> Request SLOT DATA/status block.
      *
      * Page 8 of LocoNet Personal Edition v1.0.
      */
 case LnConstants::OPC_RQ_SL_DATA: {
     int slot = l.getElement(1);

     switch (slot) {
     // Slots > 120 are all special, but these are the only ones we know to decode.
     case LnConstants::FC_SLOT:
         return tr("Request Fast Clock information.\n");
     case LnConstants::CFG_SLOT:
         return tr("Request Command Station Ops Switches.\n");
     case LnConstants::PRG_SLOT:
         return tr("Request Programming Track information.\n");
     default:
         return tr("Request data/status for slot ") + QString("%1").arg(slot) + ".\n";
     }
 } // case LnConstants::OPC_RQ_SL_DATA

     /*
      * OPC_MOVE_SLOTS   0xBA   ; MOVE slot SRC to DEST
      *                         ; Follow on message: <E7>SLOT READ
      *                         ; <0xBA>,<SRC>,<DEST>,<CHK> Move SRC to DEST if
      *                         ; SRC or LACK etc is NOT IN_USE, clr SRC
      *                         ; SPECIAL CASES:
      *                         ; If SRC=0 ( DISPATCH GET) , DEST=dont care,
      *                         ;    Return SLOT READ DATA of DISPATCH Slot
      *                         ; IF SRC=DEST (NULL move) then SRC=DEST is set to
      *                         ;    IN_USE , if legal move.
      *                         ; If DEST=0, is DISPATCH Put, mark SLOT as DISPATCH
      *                         ;    RETURN slot status <0xE7> of DESTINATION slot
      *                         ;       DEST if move legal
      *                         ;    RETURN Fail LACK code if illegal move
      *                         ;       <B4>,<3A>,<0>,<chk>, illegal to move to/from
      *                         ;       slots 120/127
      *
      * Page 8 of LocoNet Personal Edition v1.0.
      */
 case LnConstants::OPC_MOVE_SLOTS: {
     int src = l.getElement(1);
     int dest = l.getElement(2);

     /* check special cases */
     if (src == 0) { /* DISPATCH GET */
         return tr("Get most recently dispatched slot.\n");
     } else if (src == dest) { /* IN USE */
         return tr("Set status of slot ") + QString("%1").arg(src) + tr(" to IN_USE.\n");
     } else if (dest == 0) { /* DISPATCH PUT */
         return tr("Mark slot ") + QString("%1").arg(src) + tr(" as DISPATCHED.\n");
     } else { /* general move */
         return tr("Move data in slot ") + QString("%1").arg(src) + tr(" to slot ") + QString("%1").arg(dest) + ".\n";
     }
 } // case LnConstants::OPC_MOVE_SLOTS

     /*
      * OPC_LINK_SLOTS   0xB9   ; LINK slot ARG1 to slot ARG2=
      *                         ; Follow on message: <E7>SLOT READ=
      *                         ; <0xB9>,<SL1>,<SL2>,<CHK> SLAVE slot SL1 to slot SL2
      *                         ; Master LINKER sets the SL_CONUP/DN flags
      *                         ; appropriately. Reply is return of SLOT Status
      *                         ; <0xE7>. Inspect to see result of Link, invalid
      *                         ; Link will return Long Ack Fail <B4>,<39>,<0>,<CHK>
      *
      * Page 9 of LocoNet Personal Edition v1.0.
      */
 case LnConstants::OPC_LINK_SLOTS: {
     int src = l.getElement(1);
     int dest = l.getElement(2);
     return tr("Consist loco in slot ") + QString("%1").arg(src) + tr(" to loco in slot ") + QString("%1").arg(dest) + ".\n";
 } // case LnConstants::OPC_LINK_SLOTS

     /*
      * OPC_UNLINK_SLOTS 0xB8   ;UNLINK slot ARG1 from slot ARG2
      *                         ; Follow on message: <E7>SLOT READ
      *                         ; <0xB8>,<SL1>,<SL2>,<CHK> UNLINK slot SL1 from SL2
      *                         ; UNLINKER executes unlink STRATEGY and returns new SLOT#
      *                         ; DATA/STATUS of unlinked LOCO . Inspect data to evaluate UNLINK
      *
      * Page 9 of LocoNet Personal Edition v1.0.
      */
 case LnConstants::OPC_UNLINK_SLOTS: {
     int src = l.getElement(1);
     int dest = l.getElement(2);
     return tr("Remove loco in slot ") + QString("%1").arg(src) + tr(" from consist with loco in slot ") + QString("%1").arg(dest) + ".\n";
 } // case LnConstants::OPC_UNLINK_SLOTS

     /*
      * OPC_CONSIST_FUNC 0xB6   ; SET FUNC bits in a CONSIST uplink element
      *                         ; <0xB6>,<SLOT>,<DIRF>,<CHK> UP consist FUNC bits
      *                         ; NOTE this SLOT adr is considered in UPLINKED slot space.
      *
      * Page 9 of LocoNet Personal Edition v1.0.
      */
 case LnConstants::OPC_CONSIST_FUNC: {
     int slot = l.getElement(1);
     int dirf = l.getElement(2);
     return tr("Set consist in slot ") + QString("%1").arg(slot) + tr(" direction to ")
            + ((dirf & LnConstants::DIRF_DIR) != 0 ? "REV" : "FWD")
            + "F0="
            + ((dirf & LnConstants::DIRF_F0) != 0 ? tr("On, ") : tr("Off,"))
            + "F1="
            + ((dirf & LnConstants::DIRF_F1) != 0 ? tr("On, ") : tr("Off,"))
            + "F2="
            + ((dirf & LnConstants::DIRF_F2) != 0 ? tr("On, ") : tr("Off,"))
            + "F3="
            + ((dirf & LnConstants::DIRF_F3) != 0 ? tr("On, ") : tr("Off,"))
            + "F4="
            + ((dirf & LnConstants::DIRF_F4) != 0 ? tr("On") : tr("Off"))
            + ".\n";
 } // case LnConstants::OPC_CONSIST_FUNC

     /*
      * OPC_SLOT_STAT1   0xB5   ; WRITE slot stat1
      *                         ; <0xB5>,<SLOT>,<STAT1>,<CHK> WRITE stat1
      *
      * Page 9 of LocoNet Personal Edition v1.0.
      */
 case LnConstants::OPC_SLOT_STAT1: {
     int slot = l.getElement(1);
     int stat = l.getElement(2);
     return tr("Write slot ") + QString("%1").arg(slot) + tr(" with status value ") + QString("%1").arg(stat)
            + " (0x"+ QString("%1").arg(stat,0,16) + ") - Loco is "
            + LnConstants::CONSIST_STAT(stat) + ", " + LnConstants::LOCO_STAT(stat)
            + tr("\n\tand operating in ") + LnConstants::DEC_MODE(stat) + tr(" speed step mode.\n");
 } // case LnConstants::OPC_SLOT_STAT1

     /*
      * OPC_LONG_ACK     0xB4   ; Long acknowledge
      *                         ; <0xB4>,<LOPC>,<ACK1>,<CHK> Long acknowledge
      *                         ; <LOPC> is COPY of OPCODE responding to (msb=0).
      *                         ; LOPC=0 (unused OPC) is also VALID fail code
      *                         ; <ACK1> is appropriate response code for the OPCode
      *
      * Page 9 of LocoNet Personal Edition v1.0.
      */
case LnConstants::OPC_LONG_ACK: {
     int opcode = l.getElement(1);
     int ack1 = l.getElement(2);

     switch (opcode | 0x80) {
     case (LnConstants::OPC_LOCO_ADR):
         // response for OPC_LOCO_ADR
         return tr("LONG_ACK: NO FREE SLOTS!\n");

     case (LnConstants::OPC_LINK_SLOTS):
         // response for OPC_LINK_SLOTS
         return tr("LONG_ACK: Invalid consist, unable to link.\n");

     case (LnConstants::OPC_SW_ACK):
         // response for OPC_SW_ACK
         if (ack1 == 0) {
             return tr("LONG_ACK: The Command Station FIFO is full, the switch command was rejected.\n");
         } else if (ack1 == 0x7f) {
             return tr("LONG_ACK: The Command Station accepted the switch command.\n");
         } else {
             forceHex = true;
             return tr("LONG_ACK: Unknown response to 'Request Switch with ACK' command, value 0x")
                    + QString("%1").arg(ack1,0,16) + ".\n";
         }
         break;
     case (LnConstants::OPC_SW_REQ):
         // response for OPC_SW_REQ
         return tr("LONG_ACK: Switch request Failed!\n");

     case (LnConstants::OPC_WR_SL_DATA):
         // response for OPC_WR_SL_DATA
         if (ack1 == 0) {
             return tr("LONG_ACK: The Slot Write command was rejected.\n");
         } else if (ack1 == 0x01) {
             return tr("LONG_ACK: The Slot Write command was accepted.\n");
         } else if (ack1 == 0x23 || ack1 == 0x2b || ack1 == 0x6B) {
             return tr("LONG_ACK: DCS51 programming reply, thought to mean OK.\n");
         } else if (ack1 == 0x40) {
             return tr("LONG_ACK: The Slot Write command was accepted blind (no response will be sent).\n");
         } else if (ack1 == 0x7f) {
             return tr("LONG_ACK: Function not implemented, no reply will follow.\n");
         } else {
             forceHex = true;
             return tr("LONG_ACK: Unknown response to Write Slot Data message value 0x")
                    + QString("%1").arg(ack1,0,16) + ".\n";
         }
         break;
     case (LnConstants::OPC_SW_STATE):
         // response for OPC_SW_STATE
         return tr("LONG_ACK: Command station response to switch state request 0x")
                + QString("%1").arg(ack1,0,16)
                + (((ack1 & 0x20) != 0) ? tr(" (Closed)") : tr(" (Thrown)"))
                + ".\n";

     case (LnConstants::OPC_MOVE_SLOTS):
         // response for OPC_MOVE_SLOTS
         if (ack1 == 0) {
             return tr("LONG_ACK: The Move Slots command was rejected.\n");
         } else if (ack1 == 0x7f) {
             return tr("LONG_ACK: The Move Slots command was accepted.\n");
         } else {
             forceHex = true;
             return tr("LONG_ACK: unknown reponse to Move Slots message 0x")
                    + QString("%1").arg(ack1,0,16) + ".\n";
         }
         break;
     case LnConstants::OPC_IMM_PACKET:
         // response for OPC_IMM_PACKET
         if (ack1 == 0) {
             return tr("LONG_ACK: the Send IMM Packet command was rejected, the buffer is full/busy.\n");
         } else if (ack1 == 0x7f) {
             return tr("LONG_ACK: the Send IMM Packet command was accepted.\n");
         } else {
             forceHex = true;
             return tr("LONG_ACK: Unknown reponse to Send IMM Packet value 0x")
                    + QString("%1").arg(ack1,0,16) + ".\n";
         }
         break;
     case LnConstants::OPC_IMM_PACKET_2:
         // response for OPC_IMM_PACKET
         return tr("LONG_ACK: the Lim Master responded to the Send IMM Packet command with ")
                + QString("%1").arg(ack1) + " (0x" + QString("%1").arg(ack1,0,16) + ").\n";

     case (RE_LACK_SPEC_CASE1 | 0x80) : // 0x50 plus opcode bit so can match the switch'd value:
     case (RE_LACK_SPEC_CASE2 | 0x80): //0x00 plus opcode bit so can match the switch'd value:
     {
         // OpSwitch read response reverse-engineered by B. Milhaupt and
         // used with permission
         int responseValue = l.getElement(2);
         if (responseValue == 0x7f) {
             return tr("LONG_ACK: OpSwitch operation accepted.\n");
         }
         else {
             QString state = ( (responseValue & 0x20) == 0x20) ? tr("1 (Closed).\n") : tr("0 (Thrown).\n");
             return tr("LONG_ACK: OpSwitch report - opSwitch is ") +
                     state;
         }
         break;
     }
     default:
         // forceHex = TRUE;
         return tr("LONG_ACK: Response ") + QString("%1").arg(ack1)
                + " (0x" + QString("%1").arg(ack1,0,16) + tr(") to opcode 0x")
                + QString("%1").arg(opcode, 0,16) + tr(" not decoded.\n");
     } // switch (opcode | 0x80)
} // case LnConstants::OPC_LONG_ACK

    /*
     * OPC_INPUT_REP    0xB2   ; General SENSOR Input codes
     *                         ; <0xB2>, <IN1>, <IN2>, <CHK>
     *                         ;   <IN1> =<0,A6,A5,A4- A3,A2,A1,A0>,
     *                         ;           7 ls adr bits.
     *                         ;           A1,A0 select 1 of 4 inputs pairs in a DS54.
     *                         ;   <IN2> =<0,X,I,L- A10,A9,A8,A7>,
     *                         ;           Report/status bits and 4 MS adr bits.
     *                         ;           "I"=0 for DS54 "aux" inputs
     *                         ;              =1 for "switch" inputs mapped to 4K SENSOR space.
     *                         ;
     *                         ;           (This is effectively a least significant adr bit when
     *                         ;            using DS54 input configuration)
     *                         ;
     *                         ;           "L"=0 for input SENSOR now 0V (LO),
     *                         ;              =1 for Input sensor >=+6V (HI)
     *                         ;           "X"=1, control bit,
     *                         ;              =0 is RESERVED for future!
     *
     * Page 9 of LocoNet Personal Edition v1.0.
     */
 case LnConstants::OPC_INPUT_REP:
 {
  int in1 = l.getElement(1);
  int in2 = l.getElement(2);
  int contactNum = ((SENSOR_ADR(in1, in2)-1)*2+((in2 & LnConstants::OPC_INPUT_REP_SW)!=0?2:1));
  // get system and user names
  QString sensorSystemName = locoNetSensorPrefix + QString("%1").arg(contactNum);
  QString sensorUserName = "";
//            try {
  sensorSystemName = locoNetSensorPrefix + QString("%1").arg(contactNum);
  Sensor* sensor = (Sensor*)sensorManager->getBySystemName(sensorSystemName);
  if ((sensor != NULL) && (sensor->getUserName().length() > 0 ))
  {
   sensorUserName = " (" + sensor->getUserName() + ")";
  }
  else
  {
   sensorUserName = "()";
  }
//            }
//            catch (Exception e) {
//                sensorUserName = "()";
//            }
  int i_sensor = (SENSOR_ADR(in1, in2) - 1) * 2
           + ((in2 & LnConstants::OPC_INPUT_REP_SW) != 0 ? 2 : 1);

  int bdlid = ((i_sensor - 1) / 16) + 1;
  int bdlin = ((i_sensor - 1) % 16) + 1;
  QString bdl = "BDL16 #" + QString("%1").arg(bdlid) + ", DS" + QString("%1").arg(bdlin);

  int boardid = ((i_sensor - 1) / 8) + 1;
  int boardindex = ((i_sensor - 1) % 8);
  QString ds54sensors[] = { "AuxA", "SwiA", "AuxB", "SwiB", "AuxC", "SwiC", "AuxD", "SwiD" };
  QString ds64sensors[] = { "A1", "S1", "A2", "S2", "A3", "S3", "A4", "S4" };
  QString se8csensors[] = { "DS01", "DS02", "DS03", "DS04", "DS05", "DS06", "DS07", "DS08" };

  // There is no way to tell what kind of a board sent the message.
  // To be user friendly, we just print all the known combos.
  return "Sensor "
         + sensorSystemName + " " + sensorUserName
         + " is "
         + ((in2 & LnConstants::OPC_INPUT_REP_HI) != 0 ? "Hi" : "Lo")
         + ".  (" + bdl + "; DS54/64"
         + (i_sensor < 289 ? "/SE8c #" : " #")
         + QString("%1").arg(boardid) + ", "
         + ds54sensors[boardindex] + "/" + ds64sensors[boardindex]
         + ((i_sensor < 289) ? "/" + se8csensors[boardindex] : "")
         + ")\n";
 } // case LnConstants::OPC_INPUT_REP

     /*
      * OPC_SW_REP       0xB1   ; Turnout SENSOR state REPORT
      *                         ; <0xB1>,<SN1>,<SN2>,<CHK> SENSOR state REPORT
      *                         ;   <SN1> =<0,A6,A5,A4- A3,A2,A1,A0>,
      *                         ;           7 ls adr bits.
      *                         ;           A1,A0 select 1 of 4 input pairs in a DS54
      *                         ;   <SN2> =<0,1,I,L- A10,A9,A8,A7>
      *                         ;           Report/status bits and 4 MS adr bits.
      *                         ;           this <B1> opcode encodes input levels
      *                         ;           for turnout feedback
      *                         ;           "I" =0 for "aux" inputs (normally not feedback),
      *                         ;               =1 for "switch" input used for
      *                         ;                  turnout feedback for DS54
      *                         ;                  ouput/turnout # encoded by A0-A10
      *                         ;           "L" =0 for this input 0V (LO),
      *                         ;               =1 this input > +6V (HI)
      *                         ;
      *                         ;   alternately;
      *                         ;
      *                         ;   <SN2> =<0,0,C,T- A10,A9,A8,A7>
      *                         ;           Report/status bits and 4 MS adr bits.
      *                         ;           this <B1> opcode encodes current OUTPUT levels
      *                         ;           "C" =0 if "Closed" ouput line is OFF,
      *                         ;               =1 "closed" output line is ON
      *                         ;                  (sink current)
      *                         ;           "T" =0 if "Thrown" output line is OFF,
      *                         ;               =1 "thrown" output line is ON
      *                         ;                  (sink I)
      *
      * Page 9 of LocoNet Personal Edition v1.0.
      */
  case LnConstants::OPC_SW_REP: {
     int sn1 = l.getElement(1);
     int sn2 = l.getElement(2);
     // get system and user names
     QString turnoutSystemName = "";
     QString turnoutUserName = "";
     turnoutSystemName = locoNetTurnoutPrefix +
             QString("%1").arg(SENSOR_ADR(sn1, sn2));

     try {
         Turnout* turnout = turnoutManager->getBySystemName(turnoutSystemName);
         if ((turnout != NULL) && (turnout->getUserName().length() > 0))
             turnoutUserName = "(" + turnout->getUserName() + ")";
         else
             turnoutUserName = "()";
     }
     catch (Exception e) {
         turnoutUserName = "()";
     }

     if ((sn2 & LnConstants::OPC_SW_REP_INPUTS) != 0) {
         return tr("Turnout ")
                + turnoutSystemName + " " + turnoutUserName + " "
                + ((sn2 & LnConstants::OPC_SW_REP_SW) != 0 ? tr(" Switch input") : tr(" Aux input"))
                + " is "
                + (((sn2 & LnConstants::OPC_SW_REP_HI) != 0) ? tr("Closed (input off)")
                        : tr("Thrown (input on)")) + ".\n";
     } else { // OPC_SW_REP_INPUTS is 0
         return tr("Turnout ")
                + turnoutSystemName + " " + turnoutUserName + " "
                +  tr(" output state: Closed output is ")
                + ((sn2 & /*LnConstants::*/OPC_SW_REP_CLOSED) != 0 ? tr("ON (sink)") : tr("OFF (open)"))
                + tr(", Thrown output is ")
                + ((sn2 & /*LnConstants::*/OPC_SW_REP_THROWN) != 0 ? tr("ON (sink)") : tr("OFF (open)"))
                + ".\n";
     }
 } // case LnConstants::OPC_SW_REP

      /*
       * OPC_SW_REQ       0xB0   ; REQ SWITCH function
       *                         ; <0xB0>,<SW1>,<SW2>,<CHK> REQ SWITCH function
       *                         ;   <SW1> =<0,A6,A5,A4- A3,A2,A1,A0>,
       *                         ;           7 ls adr bits.
       *                         ;           A1,A0 select 1 of 4 input pairs in a DS54
       *                         ;   <SW2> =<0,0,DIR,ON- A10,A9,A8,A7>
       *                         ;           Control bits and 4 MS adr bits.
       *                         ;   DIR  =1 for Closed,/GREEN,
       *                         ;        =0 for Thrown/RED
       *                         ;   ON   =1 for Output ON,
       *                         ;        =0 FOR output OFF
       *                         ;
       *                         ;   Note-Immediate response of <0xB4><30><00> if command failed,
       *                         ;        otherwise no response "A" CLASS codes
       *
       * Page 9 of LocoNet Personal Edition v1.0.
       * Page 12 special form Broadcast.
       * Page 13 special form LocoNet interrogate.
       */
 case LnConstants::OPC_SW_REQ: {
     int sw1 = l.getElement(1);
     int sw2 = l.getElement(2);

     QString retVal;

     /*
      * This is probably poor code structure. The decodes of bits a/c/b
      * and the resulting list of addresses are used by 2 of the three
      * cases below. We construct them every time even though one case
      * may not use them.
      */
     int a = (sw2 & 0x20) >> 5;
     int c = (sw1 & 0x02) >> 1;
     int b = (sw1 & 0x01);

     /*
      * All this blob does is loop through the ranges indicated by the
      * a/c/b bits, they are mask bits in the midde of the range. The
      * idea is to get 8 sensors at a time, since that is generally what
      * units have, and to query units 1, 9, 17... then 2, 10, 18... and
      * so on such that if they are all in a row they don't get hit at
      * the same time.
      *
      * This is also part of the poor code structure, as it is only used
      * by 2 of the three cases.
      */
     int topbits = 0;
     int midbits = (a << 2) + (c << 1) + b;
     int count = 0;
     //StringBuilder addrListB = new StringBuilder();
     QString addrListB;
     for (topbits = 0; topbits < 32; topbits++) {
         // The extra "+1" adjusts for the fact that we show 1-2048,
         // rather than 0-2047 on the wire.
         int lval = (topbits << 6) + (midbits << 3) + 1;
         int hval = lval + 7;

         if ((count % 8) > 0) {
             addrListB.append(", ");
         } else {
             if (count == 0) {
                 addrListB.append("\t");
             } else {
                 addrListB.append(",\n\t");
             }
         }
         addrListB.append(QString("%1").arg(lval));
         addrListB.append("-" + QString("%1").arg(hval));
         count++;
     }
     addrListB.append("\n");

     QString addrList = addrListB;

     if (((sw2 & 0xCF) == 0x0F) && ((sw1 & 0xFC) == 0x78)) {
         // broadcast address LPU V1.0 page 12
         retVal = tr("Interrogate Stationary Decoders with bits a/c/b of ") + QString("%1").arg(a) + "/" + QString("%1").arg(c) + "/"
                 + QString("%1").arg(b) + tr("; turnouts...\n") + addrList;
     } else if (((sw2 & 0xCF) == 0x07) && ((sw1 & 0xFC) == 0x78)) {
         // broadcast address LPU V1.0 page 13
         retVal = tr("Interrogate LocoNet Turnouts/Sensors with bits a/c/b of ") + QString("%1").arg(a) + "/" + QString("%1").arg(c)
                  + "/" + QString("%1").arg(b) + tr("; addresses...\n") + addrList;
     } else {
         // get system and user names
         QString turnoutSystemName = "";
         QString turnoutUserName = "";
         turnoutSystemName = locoNetTurnoutPrefix +
                 QString("%1").arg(SENSOR_ADR(l.getElement(1), l.getElement(2)));

         try {
             Turnout* turnout = turnoutManager->getBySystemName(turnoutSystemName);
             if ((turnout != NULL) && (turnout->getUserName().length() > 0))
                 turnoutUserName = "(" + turnout->getUserName() + ")";
             else
                 turnoutUserName = "()";
         }
         catch (Exception e) {
             turnoutUserName = "()";
         }

         // ordinary form, LPU V1.0 page 9
         retVal = "Requesting Switch at " + turnoutSystemName + " " +
                 turnoutUserName + " to "
                  + ((sw2 & LnConstants::OPC_SW_REQ_DIR) != 0 ? tr("Closed") : tr("Thrown"))
                  + " (output " + ((sw2 & LnConstants::OPC_SW_REQ_OUT) != 0 ? tr("On") : tr("Off"))
                  + ").\n";
     }

    return retVal;
 } // case LnConstants::OPC_SW_REQ

     /*
      * OPC_LOCO_SND     0xA2   ;SET SLOT sound functions
      *
      * Page 10 of LocoNet Personal Edition v1.0.
      */
 case LnConstants::OPC_LOCO_SND: {
     int slot = l.getElement(1);
     int snd = l.getElement(2);

     return tr("Set loco in slot ") + QString("%1").arg(slot) + tr(" Sound1/F5=")
            + ((snd & LnConstants::SND_F5) != 0 ? tr("On") : tr("Off"))
            + tr(", Sound2/F6=")
            + ((snd & LnConstants::SND_F6) != 0 ? tr("On") : tr("Off"))
            + tr(", Sound3/F7=")
            + ((snd & LnConstants::SND_F7) != 0 ? tr("On") : tr("Off"))
            + tr(", Sound4/F8=")
            + ((snd & LnConstants::SND_F8) != 0 ? tr("On") : tr("Off")) + ".\n";
 } // case LnConstants::OPC_LOCO_SND

     /*
      * OPC_LOCO_DIRF 0xA1 ;SET SLOT dir, F0-4 state
      *
      * Page 10 of LocoNet Personal Edition v1.0.
      */
 case LnConstants::OPC_LOCO_DIRF: {
     int slot = l.getElement(1);
     int dirf = l.getElement(2);

     return tr("Set loco in slot ") + QString("%1").arg(slot) + tr(" direction to ")
            + ((dirf & LnConstants::DIRF_DIR) != 0 ? tr("REV") : tr("FWD"))
            + ", F0="
            + ((dirf & LnConstants::DIRF_F0) != 0 ? tr("On, ") : tr("Off,"))
            + " F1="
            + ((dirf & LnConstants::DIRF_F1) != 0 ? tr("On, ") : tr("Off,"))
            + " F2="
            + ((dirf & LnConstants::DIRF_F2) != 0 ? tr("On, ") : tr("Off,"))
            + " F3="
            + ((dirf & LnConstants::DIRF_F3) != 0 ? tr("On, ") : tr("Off,"))
            + " F4="
            + ((dirf & LnConstants::DIRF_F4) != 0 ? tr("On") : tr("Off"))
            + ".\n";
 } // case LnConstants::OPC_LOCO_DIRF

     /*
      * OPC_LOCO_SPD 0xA0 ;SET SLOT speed e.g. <0xA0><SLOT#><SPD><CHK>
      *
      * Page 10 of LocoNet Personal Edition v1.0.
      */
 case LnConstants::OPC_LOCO_SPD: {
     int slot = l.getElement(1);
     int spd = l.getElement(2);

     if (spd == LnConstants::OPC_LOCO_SPD_ESTOP) {
         return tr("Set speed of loco in slot ") + QString("%1").arg(slot) + tr(" to EMERGENCY STOP!\n");
     } else {
         return tr("Set speed of loco in slot ") + QString("%1").arg(slot) + " to " + QString("%1").arg(spd) + ".\n";
     }
 } // case LnConstants::OPC_LOCO_SPD

 /*
  * ; 6 byte MESSAGE OPCODES
  * ; FORMAT = <OPC>,<ARG1>,<ARG2>,<ARG3>,<ARG4>,<CKSUM>
  * :
  *  CODES 0xC8 to 0xCF have responses
  *  CODES 0xD8 to 0xDF have responses
  */

     /*
      * OPC_PANEL_QUERY 0xDF messages used by throttles to discover
      * panels
      *
      * This op code is not documented by Digitrax. Reverse engineering
      * performed by Leo Bicknell.  The opcode "name" OPC_PANEL_QUERY
      * is not necessarily the name used by Digitrax.
       */
 case LnConstants::OPC_PANEL_QUERY: {
     switch (l.getElement(1)) {
     case 0x00: {
         return tr("Query Tetherless Receivers.\n");
     }
     case 0x40: {
         if (l.getElement(2) == 0x1F) {
             // Some UR devices treat this operation as a set plus query, others
             // treat this only as a set.
             return tr("Set LocoNet ID to ") + QString("%1").arg(l.getElement(3)) + ".\n";
         } else {
             return tr("Unknown attempt to set the Loconet ID 0x") + QString("%1").arg(l.getElement(2),0,16)
                    + ".\n";
         }
     }
     default: {
         return tr("Unknown Tetherless Receivers Request 0x") + QString("%1").arg(l.getElement(1),0,16)
                + ".\n";
     }
     }
 } // case LnConstants::OPC_PANEL_QUERY

     /*
      * OPC_PANEL_RESPONSE 0xD7 messages used by throttles to discover
      * panels
      *
      * This op code is not documented by Digitrax. Reverse engineering
      * performed by Leo Bicknell.  The opcode "name" OPC_PANEL_RESPONSE
      * is not necessarily the name used by Digitrax.

      */
 case LnConstants::OPC_PANEL_RESPONSE: {
     switch (l.getElement(1)) {

     case 0x12: {
         // Bit 3 (0x08 in hex) is set by every UR-92 we've ever captured.
         // The hypothesis is this indicates duplex enabled, but this has
         // not been confirmed with Digitrax.
         return tr("UR92 Responding with LocoNet ID ") + QString("%1").arg(l.getElement(3) & 0x07)
                + ((l.getElement(3) & 0x08) == 0x08 ? tr(", duplex enabled.\n") : ".\n");
     }
     case 0x17: {
         return tr("UR90 Responding with LocoNet ID ") + QString("%1").arg(l.getElement(3)) + ".\n";
     }
     case 0x1F: {
         return tr("UR91 Responding with LocoNet ID ") + QString("%1").arg(l.getElement(3)) + ".\n";
     }
     default: {
         return tr("Unknown Tetherless Receiver of type 0x") + QString("%1").arg(l.getElement(1),0,16)
                + " responding.\n";

     }
   }
 } // case LnConstants::OPC_PANEL_RESPONSE

     /*
      * OPC_MULTI_SENSE 0xD0 messages about power management and
      * transponding
      *
      * If byte 1 high nibble is 0x20 or 0x00 this is a transponding
      * message
      *
      * This op code is not documented by Digitrax. Reverse engineering
      * performed by Al Silverstein, and corrections added by B. Milhaupt.
      */
 case LnConstants::OPC_MULTI_SENSE: {
     int type = l.getElement(1) & OPC_MULTI_SENSE_MSG;

     int section = (l.getElement(2) / 16) + (l.getElement(1) & 0x1F) * 8;

     switch (type) {
     case OPC_MULTI_SENSE_POWER:
     {
         // This is a PM42 power event.
         int pCMD = (l.getElement(3) & 0xF0);

         if ((pCMD == 0x30) || (pCMD == 0x10)) {
             // autoreverse
             int cm1 = l.getElement(3);
             int cm2 = l.getElement(4);
             //StringBuilder s = new StringBuilder("PM4x (Board ID ");
             QString s = "PM4x (Board ID ";
             s.append(QString::number((l.getElement(2) + 1)+(((l.getElement(1)&0x1)==1)?128:0)));
             s.append(tr(") Power Status Report\n\tSub-District 1 - "));
             if ((cm1 & 1) != 0) {
                 s.append (tr("AutoReversing mode - "));
                 s.append(((cm2&1)!=0)?tr("Reversed"):tr("Normal"));
             } else {
                 s.append (tr("CircuitBreaker mode - "));
                 s.append(((cm2&1)!=0)?tr("Shorted"):tr("Unshorted"));
             }

             s.append("\n\tSub-District 2 - ");
             if ((cm1 & 2) != 0) {
                 s.append (tr("AutoReversing mode - "));
                 s.append(((cm2&2)!=0)?tr("Reversed"):tr("Normal"));
             } else {
                 s.append (tr("CircuitBreaker mode - "));
                 s.append(((cm2&2)!=0)?tr("Shorted"):tr("Unshorted"));
             }

             s.append(tr("\n\tSub-District 3 - "));
             if ((cm1 & 4) != 0) {
                 s.append (tr("AutoReversing mode - "));
                 s.append(((cm2&4)!=0)?tr("Reversed"):tr("Normal"));
             } else {
                 s.append (tr("CircuitBreaker mode - "));
                 s.append(((cm2&4)!=0)?tr("Shorted"):tr("Unshorted"));
             }

             s.append(tr("\n\tSub-District 4 - "));
             if ((cm1 & 8) != 0) {
                 s.append (tr("AutoReversing mode - "));
                 s.append(((cm2&8)!=0)?tr("Reversed"):tr("Normal"));
             } else {
                 s.append (tr("CircuitBreaker mode - "));
                 s.append(((cm2&8)!=0)?tr("Shorted"):tr("Unshorted"));
             }
             s.append(".\n");

             return s/*.toString()*/;
         } else if (pCMD == 0x70) {
             // programming
             int deviceType = l.getElement(3) & 0x7;
             QString device;
             if (deviceType == LnConstants::RE_MULTI_SENSE_DEV_TYPE_PM4X)
                 device = "PM4(x) ";
             else if (deviceType == LnConstants::RE_MULTI_SENSE_DEV_TYPE_BDL16X)
                 device = "BDL16(x) ";
             else if (deviceType == LnConstants::RE_MULTI_SENSE_DEV_TYPE_SE8)
                 device = "SE8 ";
             // DS64 device type response reverse-engineered by B. Milhaupt and
             // used with permission
             else if (deviceType == LnConstants::RE_MULTI_SENSE_DEV_TYPE_DS64)
                 device = "DS64 ";
             else
                 device = tr("(unknown type) ");

             int bit = (l.getElement(4) & 0x0E) / 2;
             int val = (l.getElement(4) & 0x01);
             int wrd = (l.getElement(4) & 0x70) / 16;
             int opsw = (l.getElement(4) & 0x7E) / 2 + 1;
             int bdaddr = l.getElement(2) + 1;
             if ((l.getElement(1) & 0x1) != 0)
                 bdaddr += 128;
             QString returnVal = device
                    + bdaddr
                    + (((l.getElement(1) & 0x10) != 0) ? " write config bit "
                            : tr(" read config bit ")) + wrd + "," + QString("%1").arg(bit) + " (opsw " + QString("%1").arg(opsw)
                    + ") val=" + QString("%1").arg(val) + (val == 1 ? tr(" (closed)") : tr(" (thrown)"));
             if ((deviceType == 0) && (bdaddr == 0) && (bit == 0 ) && ( val == 0) && (wrd == 0) && (opsw ==1))  {
                 returnVal += " - Also acts as device query for some device types";
             }
             return returnVal +"\n";
         } else if (pCMD == 0x00) {
             /****************************************************************
              * Device type report                                           *
              *    The message bytes as assigned as follows:                 *
              * <0xD0> <DQT_REQ> <DQT_BRD> <DQT_B3> <DQT_B4> <CHK>           *
              *                                                              *
              * where:                                                       *
              *      <DQT_REQ>   contains the device query request,          *
              *                  encoded as:                                 *
              *          bits 7-4    always 0110b                            *
              *          bits 3-1    always 001b                             *
              *          bit 0       (BoardID-1)<7>                          *
              *      <DQT_BRD>   contains most the device board ID number,   *
              *                  encoded as:                                 *
              *          bit 7       always 0b                               *
              *          bits 6-0    (BoardID-1)<6:0>                        *
              *      <DQT_B3>    contains the board type identification,     *
              *                  encoded as:                                 *
              *          bits 7-4    always 0000b                            *
              *          bits 3-0    contain the encoded device type,        *
              *                      encoded as:                             *
              *                  0000b   PM4x device                         *
              *                  0001b   BDL16x device                       *
              *                  0010b   SE8C device                         *
              *                  0011b   DS64 device                         *
              *                  others  Unknown device type                 *
              *      <DQT_B4>    contains device version number:             *
              *          bit 7       always 0b                               *
              *          bits 6-0    VersionNumber(6:0)                      *
              *                                                              *
              * Information reverse-engineered by B. Milhaupt and used       *
              * with permission                                              *
              ****************************************************************/
             // This message is a report which is sent by a LocoNet device
             // in response to a query of attached devices
             // Note - this scheme is supported by only some Digitrax devices.
             //
             // A VersionNumber of 0 implies the hardware does not report
             // a valid version number.
             //
             // Device type report reverse-engineered by B. Milhaupt and
             // used with permission
             QString device;
             if ((l.getElement(3) & 0x7) == 0)
                 device = "PM4x ";
             else if ((l.getElement(3) & 0x7) == 1)
                 device = "BDL16x ";
             else if ((l.getElement(3) & 0x7) == 2)
                 device = "SE8c ";
             else if ((l.getElement(3) & 0x7) == 3)
                 device = "DS64 ";
             else
                 device = tr("(unknown type) ");

             int bdaddr = l.getElement(2) + 1;
             if ((l.getElement(1) & 0x1) != 0)
                 bdaddr += 128;
             int verNum = l.getElement(4);
             QString versionNumber;
             if (verNum > 0)
                 versionNumber= QString("%1").arg(verNum);
             else
                 versionNumber = tr("(unknown)");

             return tr("Device type report - ") +
                     device
                    + tr("Board ID ")
                    + QString("%1").arg(bdaddr)
                    + tr(" Version ") + versionNumber +
                    tr(" is present.\n");

         } else {
             // beats me
             forceHex = true;
             return tr("OPC_MULTI_SENSE power message PM4 ") + QString("%1").arg(l.getElement(2) + 1)
                    + tr(" unknown CMD=0x") + QString("%1").arg(pCMD,0,16) + " ";
         }
     }
     case OPC_MULTI_SENSE_PRESENT:
     case OPC_MULTI_SENSE_ABSENT:
     {
         // Transponding Event
         // get system and user names
         QString reporterSystemName = "";
         QString reporterUserName = "";
         QString zone;
         switch (l.getElement(2) & 0x0F) {
         case 0x00: zone = "A"; break;
         case 0x02: zone = "B"; break;
         case 0x04: zone = "C"; break;
         case 0x06: zone = "D"; break;
         case 0x08: zone = "E"; break;
         case 0x0A: zone = "F"; break;
         case 0x0C: zone = "G"; break;
         case 0x0E: zone = "H"; break;
         default:
             zone = tr("<unknown ") + QString("%1").arg(l.getElement(2) & 0x0F) + ">";
             break;
         }

         reporterSystemName = locoNetReporterPrefix +
                 QString("%1").arg((l.getElement(1)&0x1F)*128 + l.getElement(2) +1);

//                try {
//                    Reporter reporter = reporterManager->getBySystemName(reporterSystemName);
//                    if ((reporter != NULL) && (reporter.getUserName().length() > 0))
//                        reporterUserName = "(" + reporter.getUserName() + ")";
//                    else
//                        reporterUserName = "()";
//                }
//                catch (Exception e) {
//                    reporterUserName = "()";
//                }
#if 1
         LnReporter* reporter = (LnReporter*)reporterManager->getBySystemName(reporterSystemName);
         if ((reporter != NULL) && (reporter->getUserName().length() > 0))
             reporterUserName = "(" + reporter->getUserName() + ")";
         else
             reporterUserName = "()";
#endif
         return tr("Transponder address ")
                 + ((l.getElement(3) == 0x7d) ?
                    QString("%1").arg(l.getElement(4) +" (short)") :
                     QString("%1").arg(l.getElement(3) * 128 + l.getElement(4) + " (long)"))
                 + ((type == OPC_MULTI_SENSE_PRESENT) ?" present at " : " absent at ")
                 + reporterSystemName + " " + reporterUserName
                 + " (BDL16x Board " + (section + 1)  + " RX4 zone " + zone
             + ").\n";
     }
     default:
         forceHex = true;
         return "OPC_MULTI_SENSE unknown format.\n";
     }
 } //  case LnConstants::OPC_MULTI_SENSE

 /*
  * ; VARIABLE byte MESSAGE OPCODES
  * ; FORMAT = <OPC>,<COUNT>,<ARG2>,<ARG3>,...,<ARG(COUNT-3)>,<CKSUM>
  * :
  */

     /**********************************************************************************************
      * OPC_WR_SL_DATA   0xEF   ; WRITE SLOT DATA, 10 bytes                                         *
      *                         ; Follow on message: LACK                                           *
      *                         ; <0xEF>,<0E>,<SLOT#>,<STAT>,<ADR>,<SPD>,<DIRF>,                    *
      *                         ;        <TRK>,<SS2>,<ADR2>,<SND>,<ID1>,<ID2>,<CHK>                 *
      *                         ; SLOT DATA WRITE, 10 bytes data /14 byte MSG                       *
      ***********************************************************************************************
      * OPC_SL_RD_DATA   0xE7   ; SLOT DATA return, 10 bytes                                        *
      *                         ; <0xE7>,<0E>,<SLOT#>,<STAT>,<ADR>,<SPD>,<DIRF>,                    *
      *                         ;        <TRK>,<SS2>,<ADR2>,<SND>,<ID1>,<ID2>,<CHK>                 *
      *                         ; SLOT DATA READ, 10 bytes data /14 byte MSG                        *
      *                         ;                                                                   *
      *                         ; NOTE; If STAT2.2=0 EX1/EX2 encodes an ID#,                        *
      *                         ;       [if STAT2.2=1 the STAT.3=0 means EX1/EX2                    *
      *                         ;        are ALIAS]                                                 *
      *                         ;                                                                   *
      *                         ; ID1/ID2 are two 7 bit values encoding a 14 bit                    *
      *                         ;         unique DEVICE usage ID.                                   *
      *                         ;                                                                   *
      *                         ;   00/00 - means NO ID being used                                  *
      *                         ;                                                                   *
      *                         ;   01/00 - ID shows PC usage.                                      *
      *                         ;    to         Lo nibble is TYP PC#                                *
      *                         ;   7F/01       (PC can use hi values)                              *
      *                         ;                                                                   *
      *                         ;   00/02 -SYSTEM reserved                                          *
      *                         ;    to                                                             *
      *                         ;   7F/03                                                           *
      *                         ;                                                                   *
      *                         ;   00/04 -NORMAL throttle RANGE                                    *
      *                         ;    to                                                             *
      *                         ;   7F/7E                                                           *
      ***********************************************************************************************
      * Notes:                                                                                      *
      * The SLOT DATA bytes are, in order of TRANSMISSION for <E7> READ or <EF> WRITE.              *
      * NOTE SLOT 0 <E7> read will return MASTER config information bytes.                          *
      *                                                                                             *
      * 0) SLOT NUMBER:                                                                             *
      *                                                                                             *
      * ; 0-7FH, 0 is special SLOT,                                                                 *
      *                     ; 070H-07FH DIGITRAX reserved:                                          *
      *                                                                                             *
      * 1) SLOT STATUS1:                                                                            *
      *                                                                                             *
      *     D7-SL_SPURGE    ; 1=SLOT purge en,                                                      *
      *                     ; ALSO adrSEL (INTERNAL use only) (not seen on NET!)                    *
      *                                                                                             *
      *     D6-SL_CONUP     ; CONDN/CONUP: bit encoding-Control double linked Consist List          *
      *                     ;    11=LOGICAL MID CONSIST , Linked up AND down                        *
      *                     ;    10=LOGICAL CONSIST TOP, Only linked downwards                      *
      *                     ;    01=LOGICAL CONSIST SUB-MEMBER, Only linked upwards                 *
      *                     ;    00=FREE locomotive, no CONSIST indirection/linking                 *
      *                     ; ALLOWS "CONSISTS of CONSISTS". Uplinked means that                    *
      *                     ; Slot SPD number is now SLOT adr of SPD/DIR and STATUS                 *
      *                     ; of consist. i.e. is ;an Indirect pointer. This Slot                   *
      *                     ; has same BUSY/ACTIVE bits as TOP of Consist. TOP is                   *
      *                     ; loco with SPD/DIR for whole consist. (top of list).                   *
      *                     ; BUSY/ACTIVE: bit encoding for SLOT activity                           *
      *                                                                                             *
      *     D5-SL_BUSY      ; 11=IN_USE loco adr in SLOT -REFRESHED                                 *
      *                                                                                             *
      *     D4-SL_ACTIVE    ; 10=IDLE loco adr in SLOT -NOT refreshed                               *
      *                     ; 01=COMMON loco adr IN SLOT -refreshed                                 *
      *                     ; 00=FREE SLOT, no valid DATA -not refreshed                            *
      *                                                                                             *
      *     D3-SL_CONDN     ; shows other SLOT Consist linked INTO this slot, see SL_CONUP          *
      *                                                                                             *
      *     D2-SL_SPDEX     ; 3 BITS for Decoder TYPE encoding for this SLOT                        *
      *                                                                                             *
      *     D1-SL_SPD14     ; 011=send 128 speed mode packets                                       *
      *                                                                                             *
      *     D0-SL_SPD28     ; 010=14 step MODE                                                      *
      *                     ; 001=28 step. Generate Trinary packets for this                        *
      *                     ;              Mobile ADR                                               *
      *                     ; 000=28 step. 3 BYTE PKT regular mode                                  *
      *                     ; 111=128 Step decoder, Allow Advanced DCC consisting                   *
      *                     ; 100=28 Step decoder ,Allow Advanced DCC consisting                    *
      *                                                                                             *
      * 2) SLOT LOCO ADR:                                                                           *
      *                                                                                             *
      *     LOCO adr Low 7 bits (byte sent as ARG2 in ADR req opcode <0xBF>)                        *
      *                                                                                             *
      * 3) SLOT SPEED:                                                                              *
      *     0x00=SPEED 0 ,STOP inertially                                                           *
      *     0x01=SPEED 0 EMERGENCY stop                                                             *
      *     0x02->0x7F increasing SPEED,0x7F=MAX speed                                              *
      *     (byte also sent as ARG2 in SPD opcode <0xA0> )                                          *
      *                                                                                             *
      * 4) SLOT DIRF byte: (byte also sent as ARG2 in DIRF opcode <0xA1>)                           *
      *                                                                                             *
      *     D7-0        ; always 0                                                                  *
      *     D6-SL_XCNT  ; reserved , set 0                                                          *
      *     D5-SL_DIR   ; 1=loco direction FORWARD                                                  *
      *     D4-SL_F0    ; 1=Directional lighting ON                                                 *
      *     D3-SL_F4    ; 1=F4 ON                                                                   *
      *     D2-SL_F3    ; 1=F3 ON                                                                   *
      *     D1-SL_F2    ; 1=F2 ON                                                                   *
      *     D0-SL_F1    ; 1=F1 ON                                                                   *
      *                                                                                             *
      *                                                                                             *
      *                                                                                             *
      *                                                                                             *
      * 5) TRK byte: (GLOBAL system /track status)                                                  *
      *                                                                                             *
      *     D7-D4       Reserved                                                                    *
      *     D3          GTRK_PROG_BUSY 1=Programming TRACK in this Master is BUSY.                  *
      *     D2          GTRK_MLOK1     1=This Master IMPLEMENTS LocoNet 1.1 capability,             *
      *                                0=Master is DT200                                            *
      *     D1          GTRK_IDLE      0=TRACK is PAUSED, B'cast EMERG STOP.                        *
      *     D0          GTRK_POWER     1=DCC packets are ON in MASTER, Global POWER up              *
      *                                                                                             *
      * 6) SLOT STATUS:                                                                             *
      *                                                                                             *
      *     D3          1=expansion IN ID1/2, 0=ENCODED alias                                       *
      *     D2          1=Expansion ID1/2 is NOT ID usage                                           *
      *     D0          1=this slot has SUPPRESSED ADV consist-7)                                   *
      *                                                                                             *
      * 7) SLOT LOCO ADR HIGH:                                                                      *
      *                                                                                             *
      * Locomotive address high 7 bits. If this is 0 then Low address is normal 7 bit NMRA SHORT    *
      * address. If this is not zero then the most significant 6 bits of this address are used in   *
      * the first LONG address byte ( matching CV17). The second DCC LONG address byte matches CV18 *
      * and includes the Adr Low 7 bit value with the LS bit of ADR high in the MS postion of this  *
      * track adr byte.                                                                             *
      *                                                                                             *
      * Note a DT200 MASTER will always interpret this as 0.                                        *
      *                                                                                             *
      * 8) SLOT SOUND:                                                                              *
      *                                                                                             *
      *     Slot sound/ Accesory Function mode II packets. F5-F8                                    *
      *     (byte also sent as ARG2 in SND opcode)                                                  *
      *                                                                                             *
      *     D7-D4           reserved                                                                *
      *     D3-SL_SND4/F8                                                                           *
      *     D2-SL_SND3/F7                                                                           *
      *     D1-SL_SND2/F6                                                                           *
      *     D0-SL_SND1/F5   1= SLOT Sound 1 function 1active (accessory 2)                          *
      *                                                                                             *
      * 9) EXPANSION RESERVED ID1:                                                                  *
      *                                                                                             *
      *     7 bit ls ID code written by THROTTLE/PC when STAT2.4=1                                  *
      *                                                                                             *
      * 10) EXPANSION RESERVED ID2:                                                                 *
      *                                                                                             *
      *     7 bit ms ID code written by THROTTLE/PC when STAT2.4=1                                  *
      **********************************************************************************************/
 case LnConstants::OPC_WR_SL_DATA: /* page 10 of Loconet PE */
 case LnConstants::OPC_SL_RD_DATA: { // Page 10 of LocoNet PE
     QString mode;
     QString locoAdrStr;
     QString mixedAdrStr;
     QString logString;

     // rwSlotData = (rwSlotDataMsg *) msgBuf;
     int command = l.getElement(0);
     // int mesg_size = l.getElement(1); // ummmmm, size of the message
     // in bytes?
     int slot = l.getElement(2); // slot number for this request
     int stat = l.getElement(3); // slot status
     int adr = l.getElement(4); // loco address
     int spd = l.getElement(5); // command speed
     int dirf = l.getElement(6); // direction and F0-F4 bits
     int trk = l.getElement(7); // track status
     int ss2 = l.getElement(8); // slot status 2 (tells how to use
                                // ID1/ID2 & ADV Consist)
     int adr2 = l.getElement(9); // loco address high
     int snd = l.getElement(10); // Sound 1-4 / F5-F8
     int id1 = l.getElement(11); // ls 7 bits of ID code
     int id2 = l.getElement(12); // ms 7 bits of ID code

     /* build loco address string */
     mixedAdrStr = convertToMixed(adr, adr2);

     /*
      * figure out the alias condition, and create the loco address
      * string
      */
     if (adr2 == 0x7f) {
         if ((ss2 & LnConstants::STAT2_ALIAS_MASK) == LnConstants::STAT2_ID_IS_ALIAS) {
             /* this is an aliased address and we have the alias */
             locoAdrStr = QString("%1").arg(LOCO_ADR(id2, id1)) + " (Alias for loco "
                          + QString("%1").arg(mixedAdrStr) + ")";
         } else {
             /* this is an aliased address and we don't have the alias */
             locoAdrStr = mixedAdrStr + " (via Alias)";
         }
     } else {
         /* regular 4 digit address, 128 to 9983 */
         locoAdrStr = mixedAdrStr;
     }

     /*
      * These share a common data format with the only difference being
      * whether we are reading or writing the slot data.
      */

     if (command == LnConstants::OPC_WR_SL_DATA) {
         mode = "Request";
     } else {
         mode = "Response";
     }

     if (slot == LnConstants::FC_SLOT) {
             /**********************************************************************************************
              * FAST Clock:                                                                                 *
              * ===========                                                                                 *
              * The system FAST clock and parameters are implemented in Slot#123 <7B>.                      *
              *                                                                                             *
              * Use <EF> to write new clock information, Slot read of 0x7B,<BB><7B>.., will return current  *
              * System clock information, and other throttles will update to this SYNC. Note that all       *
              * attached display devices keep a current clock calculation based on this SYNC read value,    *
              * i.e. devices MUST not continuously poll the clock SLOT to generate time, but use this       *
              * merely to restore SYNC and follow current RATE etc. This clock slot is typically "pinged"   *
              * or read SYNC'd every 70 to 100 seconds , by a single user, so all attached devices can      *
              * synchronise any phase drifts. Upon seeing a SYNC read, all devices should reset their local *
              * sub-minute phase counter and invalidate the SYNC update ping generator.                     *
              *                                                                                             *
              * Clock Slot Format:                                                                          *
              *                                                                                             *
              * <0xEF>,<0E>,<7B>,<CLK_RATE>,<FRAC_MINSL>,<FRAC_MINSH>,<256-MINS_60>,                        *
              * <TRK><256-HRS_24>,<DAYS>,<CLK_CNTRL>,<ID1>,<1D2>,<CHK>                                      *
              *                                                                                             *
              *     <CLK_RATE>      0=Freeze clock,                                                         *
              *                     1=normal 1:1 rate,                                                      *
              *                     10=10:1 etc, max VALUE is 7F/128 to 1                                   *
              *     <FRAC_MINSL>    FRAC mins hi/lo are a sub-minute counter , depending                    *
              *                         on the CLOCK generator                                              *
              *     <FRAC_MINSH>    Not for ext. usage. This counter is reset when valid                    *
              *                         <E6><7B> SYNC msg seen                                              *
              *     <256-MINS_60>   This is FAST clock MINUTES subtracted from 256. Modulo 0-59             *
              *     <256-HRS_24>    This is FAST clock HOURS subtracted from 256. Modulo 0-23               *
              *     <DAYS>          number of 24 Hr clock rolls, positive count                             *
              *     <CLK_CNTRL>     Clock Control Byte                                                      *
              *                         D6- 1=This is valid Clock information,                              *
              *                             0=ignore this <E6><7B>, SYNC reply                              *
              *     <ID1>,<1D2>     This is device ID last setting the clock.                               *
              *                         <00><00> shows no set has happened                                  *
              *     <7F><7x>        are reserved for PC access                                              *
              **********************************************************************************************/

         /* make message easier to deal with internally */
         // fastClock = (fastClockMsg *)msgBuf;
         int clk_rate = l.getElement(3); // 0 = Freeze clock, 1 = normal,
                                         // 10 = 10:1 etc. Max is 0x7f
         int frac_minsl = l.getElement(4); // fractional minutes. not for
                                           // external use.
         int frac_minsh = l.getElement(5);
         int mins_60 = l.getElement(6); // 256 - minutes
         int track_stat = l.getElement(7); // track status
         int hours_24 = l.getElement(8); // 256 - hours
         int days = l.getElement(9); // clock rollovers
         int clk_cntrl = l.getElement(10); // bit 6 = 1; data is valid
                                           // clock info
         // "  " 0; ignore this reply
         // id1/id2 is device id of last device to set the clock
         // "   " = zero shows not set has happened

         /* recover hours and minutes values */
         minutes = ((255 - mins_60) & 0x7f) % 60;
         hours = ((256 - hours_24) & 0x7f) % 24;
         hours = (24 - hours) % 24;
         minutes = (60 - minutes) % 60;
         frac_mins = 0x3FFF - (frac_minsl + (frac_minsh << 7));

         /* check track status value and display */
         if ((trackStatus != track_stat) || showTrackStatus) {
             trackStatus = track_stat;
             showStatus = true;
         }

         if (showStatus) {
             logString = mode + " Fast Clock is "
                         + ((clk_cntrl & 0x20) != 0 ? "" : "Synchronized, ")
                         + (clk_rate != 0 ? "Running, " : "Frozen, ")
                         + "rate is " + QString("%1").arg(clk_rate)
                         + ":1. Day " + QString("%1").arg(days) + ", " + QString("%1").arg(hours) + ":" + QString("%1").arg(minutes) + "." + QString("%1").arg(frac_mins)
                         + ". Last set by ID "+ idString(id1, id2)
                         + ".\n\tMaster: "
                         + ((track_stat & LnConstants::GTRK_MLOK1) != 0 ? "LocoNet 1.1" : "DT-200")
                         + "; Track Status: "
                         + ((track_stat & LnConstants::GTRK_POWER) != 0 ? tr("On") : tr("Off"))
                         + "/"
                         + ((track_stat & LnConstants::GTRK_IDLE) == 0 ? "Paused" : "Running")
                         + "; Programming Track: "
                         + ((track_stat & LnConstants::GTRK_PROG_BUSY) != 0 ? "Busy" : "Available") + "\n";
         } else {
             logString = mode + " Fast Clock is "
                         + ((clk_cntrl & 0x20) != 0 ? "" : "Synchronized, ")
                         + (clk_rate != 0 ? "Running, " : "Frozen, ")
                         + "rate is " + QString("%1").arg(clk_rate)
                     + ":1. Day " + QString("%1").arg(days) + ", " + QString("%1").arg(hours) + ":" + QString("%1").arg(minutes) + "." + QString("%1").arg(frac_mins)
                         + ". Last set by ID "+ idString(id1, id2)
                         + ".\n";
         }
         // end fast clock block

     } else if (slot == LnConstants::PRG_SLOT) {
             /**********************************************************************************************
              * Programmer track:                                                                           *
              * =================                                                                           *
              * The programmer track is accessed as Special slot #124 ( $7C, 0x7C). It is a full            *
              * asynchronous shared system resource.                                                        *
              *                                                                                             *
              * To start Programmer task, write to slot 124. There will be an immediate LACK acknowledge    *
              * that indicates what programming will be allowed. If a valid programming task is started,    *
              * then at the final (asynchronous) programming completion, a Slot read <E7> from slot 124     *
              * will be sent. This is the final task status reply.                                          *
              *                                                                                             *
              * Programmer Task Start:                                                                      *
              * ----------------------                                                                      *
              * <0xEF>,<0E>,<7C>,<PCMD>,<0>,<HOPSA>,<LOPSA>,<TRK>;<CVH>,<CVL>,                              *
              *        <DATA7>,<0>,<0>,<CHK>                                                                *
              *                                                                                             *
              * This OPC leads to immediate LACK codes:                                                     *
              *     <B4>,<7F>,<7F>,<chk>    Function NOT implemented, no reply.                             *
              *     <B4>,<7F>,<0>,<chk>     Programmer BUSY , task aborted, no reply.                       *
              *     <B4>,<7F>,<1>,<chk>     Task accepted , <E7> reply at completion.                       *
              *     <B4>,<7F>,<0x40>,<chk>  Task accepted blind NO <E7> reply at completion.                *
              *                                                                                             *
              * Note that the <7F> code will occur in Operations Mode Read requests if the System is not    *
              * configured for and has no Advanced Acknowlegement detection installed.. Operations Mode     *
              * requests can be made and executed whilst a current Service Mode programming task is keeping *
              * the Programming track BUSY. If a Programming request is rejected, delay and resend the      *
              * complete request later. Some readback operations can keep the Programming track busy for up *
              * to a minute. Multiple devices, throttles/PC's etc, can share and sequentially use the       *
              * Programming track as long as they correctly interpret the response messages. Any Slot RD    *
              * from the master will also contain the Programmer Busy status in bit 3 of the <TRK> byte.    *
              *                                                                                             *
              * A <PCMD> value of <00> will abort current SERVICE mode programming task and will echo with  *
              * an <E6> RD the command string that was aborted.                                             *
              *                                                                                             *
              * <PCMD> Programmer Command:                                                                  *
              * --------------------------                                                                  *
              * Defined as                                                                                  *
              *     D7 -0                                                                                   *
              *     D6 -Write/Read  1= Write,                                                               *
              *                     0=Read                                                                  *
              *     D5 -Byte Mode   1= Byte operation,                                                      *
              *                     0=Bit operation (if possible)                                           *
              *     D4 -TY1 Programming Type select bit                                                     *
              *     D3 -TY0 Prog type select bit                                                            *
              *     D2 -Ops Mode    1=Ops Mode on Mainlines,                                                *
              *                     0=Service Mode on Programming Track                                     *
              *     D1 -0 reserved                                                                          *
              *     D0 -0-reserved                                                                          *
              *                                                                                             *
              * Type codes:                                                                                 *
              * -----------                                                                                 *
              *     Byte Mode   Ops Mode   TY1   TY0   Meaning                                              *
              *        1           0        0     0    Paged mode byte Read/Write on Service Track          *
              *        1           0        0     0    Paged mode byte Read/Write on Service Track          *
              *        1           0        0     1    Direct mode byteRead/Write on Service Track          *
              *        0           0        0     1    Direct mode bit Read/Write on Service Track          *
              *        x           0        1     0    Physical Register byte Read/Write on Service Track   *
              *        x           0        1     1    Service Track- reserved function                     *
              *        1           1        0     0    Ops mode Byte program, no feedback                   *
              *        1           1        0     1    Ops mode Byte program, feedback                      *
              *        0           1        0     0    Ops mode Bit program, no feedback                    *
              *        0           1        0     1    Ops mode Bit program, feedback                       *
              *                                                                                             *
              *     <HOPSA>Operations Mode Programming                                                      *
              *         7 High address bits of Loco to program, 0 if Service Mode                           *
              *     <LOPSA>Operations Mode Programming                                                      *
              *         7 Low address bits of Loco to program, 0 if Service Mode                            *
              *     <TRK> Normal Global Track status for this Master,                                       *
              *         Bit 3 also is 1 WHEN Service Mode track is BUSY                                     *
              *     <CVH> High 3 BITS of CV#, and ms bit of DATA.7                                          *
              *         <0,0,CV9,CV8 - 0,0, D7,CV7>                                                         *
              *     <CVL> Low 7 bits of 10 bit CV address.                                                  *
              *         <0,CV6,CV5,CV4-CV3,CV2,CV1,CV0>                                                     *
              *     <DATA7>Low 7 BITS OF data to WR or RD COMPARE                                           *
              *         <0,D6,D5,D4 - D3,D2,D1,D0>                                                          *
              *         ms bit is at CVH bit 1 position.                                                    *
              *                                                                                             *
              * Programmer Task Final Reply:                                                                *
              * ----------------------------                                                                *
              * (if saw LACK <B4>,<7F>,<1>,<chk> code reply at task start)                                  *
              *                                                                                             *
              * <0xE7>,<0E>,<7C>,<PCMD>,<PSTAT>,<HOPSA>,<LOPSA>,<TRK>;<CVH>,<CVL>,                          *
              * <DATA7>,<0>,<0>,<CHK>                                                                       *
              *                                                                                             *
              *     <PSTAT> Programmer Status error flags. Reply codes resulting from                       *
              *             completed task in PCMD                                                          *
              *         D7-D4 -reserved                                                                     *
              *         D3    -1= User Aborted this command                                                 *
              *         D2    -1= Failed to detect READ Compare acknowledge response                        *
              *                   from decoder                                                              *
              *         D1    -1= No Write acknowledge response from decoder                                *
              *         D0    -1= Service Mode programming track empty- No decoder detected                 *
              *                                                                                             *
              * This <E7> response is issued whenever a Programming task is completed. It echos most of the *
              * request information and returns the PSTAT status code to indicate how the task completed.   *
              * If a READ was requested <DATA7> and <CVH> contain the returned data, if the PSTAT indicates *
              * a successful readback (typically =0). Note that if a Paged Read fails to detect a           *
              * successful Page write acknowledge when first setting the Page register, the read will be    *
              * aborted, showing no Write acknowledge flag D1=1.                                            *
              **********************************************************************************************/
         QString operation;
         QString progMode;
         int cvData;
         bool opsMode = false;
         int cvNumber;

         // progTask = (progTaskMsg *) msgBuf;
         // slot - slot number for this request - slot 124 is programmer
         int pcmd = l.getElement(3); // programmer command
         int pstat = l.getElement(4); // programmer status error flags in
                                      // reply message
         int hopsa = l.getElement(5); // Ops mode - 7 high address bits
                                      // of loco to program
         int lopsa = l.getElement(6); // Ops mode - 7 low address bits of
                                      // loco to program
         /* trk - track status. Note: bit 3 shows if prog track is busy */
         int cvh = l.getElement(8); // hi 3 bits of CV# and msb of data7
         int cvl = l.getElement(9); // lo 7 bits of CV#
         int data7 = l.getElement(10); // 7 bits of data to program, msb
                                       // is in cvh above

         cvData = (((cvh & LnConstants::CVH_D7) << 6) | (data7 & 0x7f)); // was
                                                                        // PROG_DATA
         cvNumber = (((((cvh & LnConstants::CVH_CV8_CV9) >> 3) | (cvh & LnConstants::CVH_CV7)) * 128) + (cvl & 0x7f)) + 1; // was
                                                                                                                         // PROG_CV_NUM(progTask)

         /* generate loco address, mixed mode or true 4 digit */
         mixedAdrStr = convertToMixed(lopsa, hopsa);

         /* determine programming mode for printing */
         if ((pcmd & LnConstants::PCMD_MODE_MASK) == LnConstants::PAGED_ON_SRVC_TRK) {
             progMode = "Byte in Paged Mode on Service Track";
         } else if ((pcmd & LnConstants::PCMD_MODE_MASK) == LnConstants::DIR_BYTE_ON_SRVC_TRK) {
             progMode = "Byte in Direct Mode on Service Track";
         } else if ((pcmd & LnConstants::PCMD_MODE_MASK) == LnConstants::DIR_BIT_ON_SRVC_TRK) {
             progMode = "Bits in Direct Mode on Service Track";
         } else if (((pcmd & ~LnConstants::PCMD_BYTE_MODE) & LnConstants::PCMD_MODE_MASK) == LnConstants::REG_BYTE_RW_ON_SRVC_TRK) {
             progMode = "Byte in Physical Register R/W Mode on Service Track";
         } else if ((pcmd & LnConstants::PCMD_MODE_MASK) == LnConstants::OPS_BYTE_NO_FEEDBACK) {
             progMode = "Byte in OP's Mode (NO feedback)";
             opsMode = true;
         } else if ((pcmd & LnConstants::PCMD_MODE_MASK) == LnConstants::OPS_BYTE_FEEDBACK) {
             progMode = "Byte in OP's Mode";
             opsMode = true;
         } else if ((pcmd & LnConstants::PCMD_MODE_MASK) == LnConstants::OPS_BIT_NO_FEEDBACK) {
             progMode = "Bits in OP's Mode (NO feedback)";
             opsMode = true;
         } else if ((pcmd & LnConstants::PCMD_MODE_MASK) == LnConstants::OPS_BIT_FEEDBACK) {
             progMode = "Bits in OP's Mode";
             opsMode = true;
         } else if (((pcmd & ~LnConstants::PCMD_BYTE_MODE) & LnConstants::PCMD_MODE_MASK) == LnConstants::SRVC_TRK_RESERVED) {
             progMode = "SERVICE TRACK RESERVED MODE DETECTED!";
         } else {
             progMode = "Unknown mode " + QString("%1").arg(pcmd) + " (0x" + QString("%1").arg(pcmd,0,16) + ")";
             forceHex = true;
         }

         /* are we sending or receiving? */
         if ((pcmd & LnConstants::PCMD_RW) != 0)
         {
          /* sending a command */
          operation = "Programming " + mode + ": Write " + progMode;

          /* printout based on whether we're doing Ops mode or not */
          if (opsMode)
          {
           logString = operation + " to CV" + QString("%1").arg(cvNumber) + " of Loco " + mixedAdrStr
                          + " value " + QString("%1").arg(cvData) + " (0x" + QString("%1").arg(cvData,0,16)
                          + ", " + QString("%1").arg(cvData,0,2) + ").\n";
          }
          else
          {
           logString = operation + " to CV" + QString::number(cvNumber) + " value " + QString::number(cvData) + " (0x"
                          + QString("%1").arg(cvData,0,16) + ", "
                          + QString("%1").arg(cvData) + ").\n";
          }
         } else {
             /* receiving a reply */
             operation = "Programming Track " + mode + ": Read " + progMode + " ";

             /* if we're reading the slot back, check the status */
             /* this is supposed to be the Programming task final reply */
             /* and will have the resulting status byte */

             if (command == LnConstants::OPC_SL_RD_DATA) {
                 if (pstat != 0) {
                     if ((pstat & LnConstants::PSTAT_USER_ABORTED) != 0) {
                         operation += "Failed, User Aborted: ";
                     }

                     if ((pstat & LnConstants::PSTAT_READ_FAIL) != 0) {
                         operation += "Failed, Read Compare Acknowledge not detected: ";
                     }

                     if ((pstat & LnConstants::PSTAT_WRITE_FAIL) != 0) {
                         operation += "Failed, No Write Acknowledge from decoder: ";
                     }

                     if ((pstat & LnConstants::PSTAT_NO_DECODER) != 0) {
                         operation += "Failed, Service Mode programming track empty: ";
                     }
                     if ((pstat & 0xF0) != 0) {
                         if ((pstat & 0xF0) == 0x10) {
                             // response from transponding decoder
                             operation += "Was successful via RX4/BDL16x:";

                         } else {
                         operation += "Unable to decode response = 0x"
                                      + QString("%1").arg(pstat,0,16) + ": ";
                         }
                     }
                 } else {
                     operation += "Was Successful, set ";
                 }
             } else {
                 operation += "variable ";
             }
             /* printout based on whether we're doing Ops mode or not */
             if (opsMode) {
                 logString = operation + " CV" + QString("%1").arg(cvNumber) + " of Loco " +QString("%1").arg( mixedAdrStr)
                             + " value " + QString("%1").arg(cvData) + " (0x" +QString("%1").arg(cvData,0,16)
                             + ", " + QString("%1").arg(cvData,0,2) + ").\n";
             } else {
                 logString = operation + " CV" + QString("%1").arg(cvNumber) + " value " + QString("%1").arg(cvData) + " (0x"
                             + QString("%1").arg(cvData,0,16) + ", "
                             + QString("%1").arg(cvData,0,2) + ").\n";
             }
         }
         // end programming track block

     } else if (slot == LnConstants::CFG_SLOT) {
         /**************************************************
          * Configuration slot, holding op switches
          **************************************************/
         logString = mode
                     + " Comand Station OpSw that are Closed (non-default):\n"
                     + ((l.getElement(3) & 0x01) > 0 ? "\tOpSw1=c, reserved.\n" : "")
                     + ((l.getElement(3) & 0x02) > 0 ? "\tOpSw2=c, DCS100 booster only.\n" : "")
                     + ((l.getElement(3) & 0x04) > 0 ? "\tOpSw3=c, Booster Autoreversing.\n" : "")
                     + ((l.getElement(3) & 0x08) > 0 ? "\tOpSw4=c, reserved.\n" : "")
                     + ((l.getElement(3) & 0x10) > 0 ? "\tOpSw5=c, Master Mode.\n" : "")
                     + ((l.getElement(3) & 0x20) > 0 ? "\tOpSw6=c, reserved.\n" : "")
                     + ((l.getElement(3) & 0x40) > 0 ? "\tOpSw7=c, reserved.\n" : "")
// this bit implies an OpCode, so ignore it!                            + ((l.getElement(3) & 0x80) > 0 ? "\tOpSw8=c, reserved.\n" : "")
                     + ((l.getElement(4) & 0x01) > 0 ? "\tOpSw9=c, Allow Motorola trinary echo 1-256.\n" : "")
                     + ((l.getElement(4) & 0x02) > 0 ? "\tOpSw10=c, Expand trinary switch echo.\n" : "")
                     + ((l.getElement(4) & 0x04) > 0 ? "\tOpSw11=c, Make certian trinary switches long duration.\n" : "")
                     + ((l.getElement(4) & 0x08) > 0 ? "\tOpSw12=c, Trinary addresses 1-80 allowed.\n" : "")
                     + ((l.getElement(4) & 0x10) > 0 ? "\tOpSw13=c, Raise loco address purge time to 600 seconds.\n" : "")
                     + ((l.getElement(4) & 0x20) > 0 ? "\tOpSw14=c, Disable loco address purging.\n" : "")
                     + ((l.getElement(4) & 0x40) > 0 ? "\tOpSw15=c, Purge will force loco to zero speed.\n" : "")
// this bit implies an OpCode, so ignore it!                            + ((l.getElement(4) & 0x80) > 0 ? "\tOpSw16=c, reserved.\n" : "")
                     + ((l.getElement(5) & 0x01) > 0 ? "\tOpSw17=c, Automatic advanced consists are disabled.\n" : "")
                     + ((l.getElement(5) & 0x02) > 0 ? "\tOpSw18=c, Extend booster short shutdown to 1/2 second.\n" : "")
                     + ((l.getElement(5) & 0x04) > 0 ? "\tOpSw19=c, reserved.\n" : "")
                     + ((l.getElement(5) & 0x08) > 0 ? "\tOpSw20=c, Disable address 00 analog operation.\n" : "")
                     + ((l.getElement(5) & 0x10) > 0 ? "\tOpSw21=c, Global default for new loco is FX.\n" : "")
                     + ((l.getElement(5) & 0x20) > 0 ? "\tOpSw22=c, Global default for new loco is 28 step.\n" : "")
                     + ((l.getElement(5) & 0x40) > 0 ? "\tOpSw23=c, Global default for new loco is 14 step.\n" : "")
// this bit implies an OpCode, so ignore it!                            + ((l.getElement(5) & 0x80) > 0 ? "\tOpSw24=c, reserved.\n" : "")
                     + ((l.getElement(6) & 0x01) > 0 ? "\tOpSw25=c, Disable aliasing.\n" : "")
                     + ((l.getElement(6) & 0x02) > 0 ? "\tOpSw26=c, Enable routes.\n" : "")
                     + ((l.getElement(6) & 0x04) > 0 ? "\tOpSw27=c, Disable normal switch commands (Bushby bit).\n" : "")
                     + ((l.getElement(6) & 0x08) > 0 ? "\tOpSw28=c, Disable DS54/64/SE8C interrogate at power on.\n" : "")
                     + ((l.getElement(6) & 0x10) > 0 ? "\tOpSw29=c, reserved.\n" : "")
                     + ((l.getElement(6) & 0x20) > 0 ? "\tOpSw30=c, reserved.\n" : "")
                     + ((l.getElement(6) & 0x40) > 0 ? "\tOpSw31=c, Meter route/switch output when not in trinary.\n" : "")
// this bit implies an OpCode, so ignore it!                            + ((l.getElement(6) & 0x80) > 0 ? "\tOpSw32=c, reserved.\n" : "")
// element 7 is skipped intentionally - it contains the "Track Status" byte
                     + ((l.getElement(8) & 0x01) > 0 ? "\tOpSw33=c, Restore track power to previous state at power on.\n" : "")
                     + ((l.getElement(8) & 0x02) > 0 ? "\tOpSw34=c, Allow track to power up to run state.\n" : "")
                     + ((l.getElement(8) & 0x04) > 0 ? "\tOpSw35=c, reserved.\n" : "")
                     + ((l.getElement(8) & 0x08) > 0 ? "\tOpSw36=c, Clear all moble decoder information and consists.\n" : "")
                     + ((l.getElement(8) & 0x10) > 0 ? "\tOpSw37=c, Clear all routes.\n" : "")
                     + ((l.getElement(8) & 0x20) > 0 ? "\tOpSw38=c, Clear loco roster.\n" : "")
                     + ((l.getElement(8) & 0x40) > 0 ? "\tOpSw39=c, Clear internal memory.\n" : "")
// this bit implies an OpCode, so ignore it!                            + ((l.getElement(8) & 0x80) > 0 ? "\tOpSw40=c, reserved.\n" : "")
                     + ((l.getElement(9) & 0x01) > 0 ? "\tOpSw41=c, Diagnostic click when LocoNet command is received.\n" : "")
                     + ((l.getElement(9) & 0x02) > 0 ? "\tOpSw42=c, Disable 3 beeps when loco address is purged.\n" : "")
                     + ((l.getElement(9) & 0x04) > 0 ? "\tOpSw43=c, Disable LocoNet update of track status.\n" : "")
                     + ((l.getElement(9) & 0x08) > 0 ? "\tOpSw44=c, Expand slots to 120.\n" : "")
                     + ((l.getElement(9) & 0x10) > 0 ? "\tOpSw45=c, Disable replay for switch state request.\n" : "")
                     + ((l.getElement(9) & 0x20) > 0 ? "\tOpSw46=c, reserved.\n" : "")
                     + ((l.getElement(9) & 0x40) > 0 ? "\tOpSw47=c, Programming track is break generator.\n" : "")
// this bit implies an OpCode, so ignore it!                            + ((l.getElement(9) & 0x80) > 0 ? "\tOpSw48=c, reserved.\n" : "")
                     + ((l.getElement(10) & 0x01) > 0 ? "\tOpSw49=c, reserved.\n" : "")
                     + ((l.getElement(10) & 0x02) > 0 ? "\tOpSw50=c, reserved.\n" : "")
                     + ((l.getElement(10) & 0x04) > 0 ? "\tOpSw51=c, reserved.\n" : "")
                     + ((l.getElement(10) & 0x08) > 0 ? "\tOpSw52=c, reserved.\n" : "")
                     + ((l.getElement(10) & 0x10) > 0 ? "\tOpSw53=c, reserved.\n" : "")
                     + ((l.getElement(10) & 0x20) > 0 ? "\tOpSw54=c, reserved.\n" : "")
                     + ((l.getElement(10) & 0x40) > 0 ? "\tOpSw55=c, reserved.\n" : "")
// this bit implies an OpCode, so ignore it!                            + ((l.getElement(10) & 0x80) > 0 ? "\tOpSw56=c, reserved.\n" : "")
                     + ((l.getElement(11) & 0x01) > 0 ? "\tOpSw57=c, reserved.\n" : "")
                     + ((l.getElement(11) & 0x02) > 0 ? "\tOpSw58=c, reserved.\n" : "")
                     + ((l.getElement(11) & 0x04) > 0 ? "\tOpSw59=c, reserved.\n" : "")
                     + ((l.getElement(11) & 0x08) > 0 ? "\tOpSw60=c, reserved.\n" : "")
                     + ((l.getElement(11) & 0x10) > 0 ? "\tOpSw61=c, reserved.\n" : "")
                     + ((l.getElement(11) & 0x20) > 0 ? "\tOpSw62=c, reserved.\n" : "")
                     + ((l.getElement(11) & 0x40) > 0 ? "\tOpSw63=c, reserved.\n" : "")
// this bit implies an OpCode, so ignore it!                            + ((l.getElement(11) & 0x80) > 0 ? "\tOpSw64=c, reserved.\n" : "")
                     ;
     } else {
         /**************************************************
          * normal slot read/write message - see info above *
          **************************************************/

         if ((trackStatus != trk) || showTrackStatus) {
             trackStatus = trk;
             showStatus = true;
         }

         if (showStatus) {
             logString = mode + " slot " + QString("%1").arg(slot) + " information:\n\tLoco " + locoAdrStr
                         + " is " + LnConstants::CONSIST_STAT(stat) + ", "
                         + LnConstants::LOCO_STAT(stat) + ", operating in "
                         + LnConstants::DEC_MODE(stat) + " SS mode, and is going "
                         + ((dirf & LnConstants::DIRF_DIR) != 0 ? "in Reverse" : "Forward")
                         + " at speed " + QString("%1").arg(spd) + ",\n" + "\tF0="
                         + ((dirf & LnConstants::DIRF_F0) != 0 ? tr("On, ") : tr("Off,"))
                         + " F1="
                         + ((dirf & LnConstants::DIRF_F1) != 0 ? tr("On, ") : tr("Off,"))
                         + " F2="
                         + ((dirf & LnConstants::DIRF_F2) != 0 ? tr("On, ") : tr("Off,"))
                         + " F3="
                         + ((dirf & LnConstants::DIRF_F3) != 0 ? tr("On, ") : tr("Off,"))
                         + " F4="
                         + ((dirf & LnConstants::DIRF_F4) != 0 ? tr("On, ") : tr("Off,"))
                         + " Sound1/F5="
                         + ((snd & LnConstants::SND_F5) != 0 ? tr("On, ") : tr("Off,"))
                         + " Sound2/F6="
                         + ((snd & LnConstants::SND_F6) != 0 ? tr("On, ") : tr("Off,"))
                         + " Sound3/F7="
                         + ((snd & LnConstants::SND_F7) != 0 ? tr("On, ") : tr("Off,"))
                         + " Sound4/F8=" + ((snd & LnConstants::SND_F8) != 0 ? "On" : tr("Off"))
                         + "\n\tMaster: "
                         + ((trk & LnConstants::GTRK_MLOK1) != 0 ? "LocoNet 1.1" : "DT-200")
                         + "; Track: "
                         + ((trk & LnConstants::GTRK_IDLE) != 0 ? "On" : tr("Off"))
                         + "; Programming Track: "
                         + ((trk & LnConstants::GTRK_PROG_BUSY) != 0 ? "Busy" : "Available")
                         + "; SS2=0x" + QString("%1").arg(ss2,0,16)
                         + ", ThrottleID=" + idString(id1, id2) + "\n";
         } else {
             logString = mode + " slot " + QString("%1").arg(slot) + " information:\n\tLoco " + locoAdrStr
                         + " is " + LnConstants::CONSIST_STAT(stat) + ", "
                         + LnConstants::LOCO_STAT(stat) + ", operating in "
                         + LnConstants::DEC_MODE(stat) + " SS mode, and is going "
                         + ((dirf & LnConstants::DIRF_DIR) != 0 ? "in Reverse" : "Forward")
                     + " at speed " + QString("%1").arg(spd) + ",\n" + "\tF0="
                         + ((dirf & LnConstants::DIRF_F0) != 0 ? tr("On, ") : tr("Off,"))
                         + " F1="
                         + ((dirf & LnConstants::DIRF_F1) != 0 ? tr("On, ") : tr("Off,"))
                         + " F2="
                         + ((dirf & LnConstants::DIRF_F2) != 0 ? tr("On, ") : tr("Off,"))
                         + " F3="
                         + ((dirf & LnConstants::DIRF_F3) != 0 ? tr("On, ") : tr("Off,"))
                         + " F4="
                         + ((dirf & LnConstants::DIRF_F4) != 0 ? tr("On, ") : tr("Off,"))
                         + " Sound1/F5="
                         + ((snd & LnConstants::SND_F5) != 0 ? tr("On, ") : tr("Off,"))
                         + " Sound2/F6="
                         + ((snd & LnConstants::SND_F6) != 0 ? tr("On, ") : tr("Off,"))
                         + " Sound3/F7="
                         + ((snd & LnConstants::SND_F7) != 0 ? tr("On, ") : tr("Off,"))
                         + " Sound4/F8=" + ((snd & LnConstants::SND_F8) != 0 ? "On" : tr("Off"))
                         + "\n\tSS2=0x" + QString("%1").arg(ss2,0,16)
                         + ", ThrottleID =" + idString(id1, id2) + "\n";
         }
         // end normal slot read/write case
     }
     return logString;
 } // case LnConstants::OPC_SL_RD_DATA

 case LnConstants::OPC_ALM_WRITE:
 case LnConstants::OPC_ALM_READ: {
     QString message;
     if (l.getElement(0) == LnConstants::OPC_ALM_WRITE) {
         message = "Write ALM msg ";
     } else {
         message = "Read ALM msg (Write reply) ";
     }

     if (l.getElement(1) == 0x10) {
         // ALM read and write messages
         message = message + l.getElement(2) + " ATASK=" + l.getElement(3);
         if (l.getElement(3) == 2) {
             message = message + " (RD)";
         } else if (l.getElement(3) == 3) {
             message = message + " (WR)";
         } else if (l.getElement(3) == 0) {
             message = message + " (ID)";
         }
         return message + " BLKL=" + l.getElement(4)
                        + " BLKH=" + l.getElement(5)
                        + " LOGIC=" + l.getElement(6)
                        + "\n      "
                        + " ARG1L=0x" + QString("%1").arg(l.getElement(7),0,16)
                        + " ARG1H=0x" + QString("%1").arg(l.getElement(8),0,16)
                        + " ARG2L=0x" + QString("%1").arg(l.getElement(9),0,16)
                        + " ARG2H=0x" + QString("%1").arg(l.getElement(10),0,16)
                        + "\n      "
                        + " ARG3L=0x" + QString("%1").arg(l.getElement(11),0,16)
                        + " ARG3H=0x" + QString("%1").arg(l.getElement(12),0,16)
                        + " ARG4L=0x" + QString("%1").arg(l.getElement(13),0,16)
                        + " ARG4H=0x" + QString("%1").arg(l.getElement(14),0,16)
                        + "\n";
     } else if (l.getElement(1) == 0x15) {
         // write extended master message
         if (l.getElement(0) == 0xEE) {
             message = "Write extended slot: ";
         } else {
             message = "Read extended slot (Write reply): ";
         }
         return message + "slot " + QString("%1").arg(l.getElement(3))
                        + " stat " + QString("%1").arg(l.getElement(4))
                        + " addr " + QString("%1").arg(l.getElement(6) * 128 + l.getElement(5))
                        + " speed " + QString("%1").arg(l.getElement(8))
                        + ".\n";
     } else {
         return message + " with unexpected length " + l.getElement(1) + ".\n";
     }
 } // case LnConstants::OPC_ALM_READ

     /*
      * OPC_PEER_XFER   0xE5    ; move 8 bytes PEER to PEER, SRC->DST   NO resp
      *                         ; <0xE5>,<10>,<SRC>,<DSTL><DSTH>,<PXCT1>,<D1>,<D2>,<D3>,<D4>,
      *                         ; <PXCT2>,<D5>,<D6>,<D7>,<D8>,<CHK>
      *                         ; SRC/DST are 7 bit args. DSTL/H=0 is BROADCAST msg
      *                         ;     SRC=0 is MASTER
      *                         ;     SRC=0x70-0x7E are reserved
      *
      * Page 10 of LocoNet Personal Edition v1.0.
      *
      * Duplex group management reverse engineered by Leo Bicknell, with input from
      * B. Milhaupt.
      */
 case LnConstants::OPC_PEER_XFER:
 {
     // The first byte seems to determine the type of message.
     switch (l.getElement(1)) {
         case 0x10: {
             /*
              * SRC=7F is THROTTLE msg xfer
              *  ; <DSTL><DSTH> encode ID#,
              *  ; <0><0> is THROT B'CAST
              *  ; <PXCT1>=<0,XC2,XC1,XC0 - D4.7,D3.7,D2.7,D1.7>
              *  ; XC0-XC2=ADR type CODE-0=7 bit Peer
              * TO Peer adrs *
              *  ; 1=<D1>is SRC HI,<D2>is DST HI
              *  ; <PXCT2>=<0,XC5,XC4,XC3 - D8.7,D7.7,D6.7,D5.7>
              *  ; XC3-XC5=data type CODE- 0=ANSI TEXT string,
              *  ; balance RESERVED *
              * ****************************************************
              * SV programming format 1
              *
              * This is the message format as implemented by the certain
              * existing devices. New designs should not use this format. The
              * message bytes are assigned as follows:
              *   ; <0xE5> <0x10> <SRC> <DST> <0x01> <PXCT1>
              *   ; <D1> <D2> <D3> <D4> <PXCT2>
              *   ; <D5> <D6> <D7> <D8> <CHK>
              *
              * The upper nibble of PXCT1 must be 0,
              * and the upper nibble of PXCT2 must be 1. The meanings of the
              * remaining bytes are as defined in the LocoNet Personal
              * Edition specification.
              * *********************************************
              * SV programming format 2
              *
              * This is the recommended format for new designs.
              * The message bytes as assigned as follows: *
              *  ; <0xE5> <0x10> <SRC> <SV_CMD> <SV_TYPE> <SVX1>
              *  ; <DST_L> <DST_H> <SV_ADRL> <SV_ADRH> <SVX2>
              *  ; <D1> <D2> <D3> <D4> <CHK>
              *
              * The upper nibble of both SVX1 (PXCT1) and SVX2 (PXCT2) must be 1.
              */

             int src = l.getElement(2); // source of transfer
             int dst_l = l.getElement(3); // ls 7 bits of destination
             int dst_h = l.getElement(4); // ms 7 bits of destination
             int pxct1 = l.getElement(5);
             int pxct2 = l.getElement(10);

             QVector<int> d = l.getPeerXfrData();

             QString generic;
             QString data;
             if(dst_h == 0x02)
             { // SV Programming version 2
              int dstl = l.getElement(6);
              int dsth = l.getElement(7);
              int svcmd = l.getElement(3);
              int svadrl = l.getElement(8);
              int svadrh = l.getElement(9);
              generic = tr("Peer to Peer transfer: SRC=0x")
                              + QString("%1").arg(src,0,16)
                              + ", SV_CMD = 0x"
                              + QString("%1").arg(svcmd,0,16)
                              + ", SV_TYPE = 0x"
                              + QString("%1").arg(dst_h,0,16)
                              + ", DST_L=0x"
                              + QString("%1").arg(dstl,0,16)
                              + ", DST_H=0x"
                              + QString("%1").arg(dsth,0,16)
                              + ", SV ADRL=0x"
                              + QString("%1").arg(svadrl,0,16)
                              + ", SV_ADRH=0x"
                              + QString("%1").arg(svadrh,0,16)
                              + ", SVX1=0x"
                              + QString("%1").arg(pxct1, 0,16)
                              + ", SVX2=0x"
                              + QString("%1").arg(pxct2, 0,16);
               data = tr("Data [0x") + QString("%1").arg(d[4],0,16)
                           + " 0x" + QString("%1").arg(d[5],0,16)
                           + " 0x" + QString("%1").arg(d[6],0,16)
                           + " 0x" + QString("%1").arg(d[7],0,16) + "]\n";
              }
              else
             {
              generic = tr("Peer to Peer transfer: SRC=0x")
                                 + QString("%1").arg(src,0,16)
                                 + ", DSTL=0x"
                                 + QString("%1").arg(dst_l,0,16)
                                 + ", DSTH=0x"
                                 + QString("%1").arg(dst_h,0,16)
                                 + ", PXCT1=0x"
                                 + QString("%1").arg(pxct1, 0,16)
                                 + ", PXCT2=0x"
                                 + QString("%1").arg(pxct2, 0,16);
              data = tr("Data [0x") + QString("%1").arg(d[0],0,16)
                              + " 0x" + QString("%1").arg(d[1],0,16)
                              + " 0x" + QString("%1").arg(d[2],0,16)
                              + " 0x" + QString("%1").arg(d[3],0,16)
                              + ",0x" + QString("%1").arg(d[4],0,16)
                              + " 0x" + QString("%1").arg(d[5],0,16)
                              + " 0x" + QString("%1").arg(d[6],0,16)
                              + " 0x" + QString("%1").arg(d[7],0,16) + "]\n";

             }
             if ((src == 0x7F) && (dst_l == 0x7F) && (dst_h == 0x7F)
                 && ((pxct1 & 0x70) == 0x40)) {
                 // Download (firmware?) messages.
                 int sub = pxct2 & 0x70;
                 switch (sub) {
                 case 0x00: // setup
                 {
                     QString s = tr("Download setup message: mfg ");
                     s.append(QString("%1").arg(l.getElement(6)));
                     s.append(", hw ver ");
                     s.append(QString("%1").arg(l.getElement(8)));
                     s.append(", sw ver ");
                     s.append(QString("%1").arg(l.getElement(9)));
                     s.append(", device 0x");
                     s.append((QString("%1").arg(l.getElement(7),0,16)).toUpper());
                     s.append(", options ");
                     s.append(QString("%1").arg(l.getElement(11)));
                     s.append("\n");
                     return s;
                 }
                 case 0x10: // set address
//                            return tr("Download message, set address ")
//                                   + StringUtil.twoHexFromInt(d[0])
//                                   + StringUtil.twoHexFromInt(d[1])
//                                   + StringUtil.twoHexFromInt(d[2]) + ".\n";
                 case 0x20: // send data
                     return tr("Download message, send data ")
                            + QString("%1").arg(d[0],0,16) + " "
                            + QString("%1").arg(d[1],0,16) + " "
                            + QString("%1").arg(d[2],0,16) + " "
                            + QString("%1").arg(d[3],0,16) + " "
                            + QString("%1").arg(d[4],0,16) + " "
                            + QString("%1").arg(d[5],0,16) + " "
                            + QString("%1").arg(d[6],0,16) + " "
                            + QString("%1").arg(d[7],0,16) + ".\n";
                 case 0x30: // verify
                     return tr("Download message, verify.\n");
                 case 0x40: // end op
                     return tr("Download message, end operation.\n");
                 default: // everything else isn't understood, go to default
                  break;}
             }
             if (src == 0x50)
             {
                 // Packets from the LocoBuffer
                 QString dst_subaddrx = (dst_h != 0x01 ? "" : ((d[4] != 0) ? "/" + QString("%1").arg(d[4]) : ""));
                 if (dst_h == 0x01 && ((pxct1 & 0xF0) == 0x00)
                     && ((pxct2 & 0xF0) == 0x10)) {
                     // LocoBuffer to LocoIO
                     return "LocoBuffer => LocoIO@"
                            + ((dst_l == 0) ? tr("broadcast") : QString("%1").arg(dst_l) + dst_subaddrx)
                            + " "
                            + (d[0] == 2 ? tr("Query SV") + QString("%1").arg(d[1]) : tr("Write SV") + QString("%1").arg(d[1]) + "=0x" + QString("%1").arg(d[3],0,16))
                            + ((d[2] != 0) ? tr(" Firmware rev ") + QString("%1").arg(d[2]) : "") + ".\n";
                 }
             }
             if (dst_h == 0x01 && ((pxct1 & 0xF0) == 0x00)
                 && ((pxct2 & 0xF0) == 0x00))
             {
                 // (Jabour/Deloof LocoIO), SV Programming messages format 1
                 QString src_subaddrx = ((d[4] != 0) ? "/" + QString("%1").arg(d[4],0,16) : "");
                 QString dst_subaddrx = (dst_h != 0x01 ? "" : ((d[4] != 0) ? "/" + QString("%1").arg(d[4],0,16) : ""));

                 QString src_dev = ((src == 0x50) ? "Locobuffer" : "LocoIO@0x" + QString("%1").arg(src, 0, 16)) + src_subaddrx;
                 QString dst_dev = (((dst_h == 0x01) && (dst_l == 0x50)) ? "LocoBuffer "
                                      : (((dst_h == 0x01) && (dst_l == 0x0)) ? tr("broadcast")
                                    : "LocoIO@0x" + QString("%1").arg(dst_l,0,16) + dst_subaddrx));
                 QString operation = (src == 0x50) ?
                         ((d[0] == 2) ? tr("Query") : tr("Write")) :
                         ((d[0] == 2) ? tr("Report") : tr("Write"))
                         ;

                 return src_dev + "=> " + dst_dev + " "
                         + ((dst_h == 0x01) ? (operation + " SV" + QString("%1").arg(d[1])) : "")
                        + ((src == 0x50) ? (d[0] != 2 ? ("=0x" + QString("%1").arg(d[3],0,16)) : "")
                          : " = " + ((d[0] == 2) ? ((d[2] != 0) ? (d[5] < 10) ? QString("%1").arg(d[5],0,16)
                                    :  QString("%1").arg(d[5]) + " (0x" + QString("%1").arg(d[5],0,16) + ")"
                                   : (d[7] < 10) ? QString("%1").arg(d[7])
                                    :  QString("%1").arg(d[7]) + " (0x" + QString("%1").arg(d[7],0,16) + ")")
                                    : (d[7] < 10) ? QString("%1").arg(d[7])
                                    :  QString("%1").arg(d[7]) + " (0x" + QString("%1").arg(d[7],0,16) + ")"))
                        + ((d[2] != 0) ? tr(" Firmware rev ") + dotme(d[2]) : "") + ".\n";
             }
             // check for a specific type - SV Programming messages format 2
             // (New Designs)
             if (((pxct1 & 0xF0) == 0x10) && ((pxct2 & 0xF0) == 0x10)) {
                 // New Designs, SV Programming messages format 2
                 // We don't know what to do with them yet.
                 return tr("SV Programming Protocol v2: ") + generic + "\n\t"
                        + QString("%1").arg(data);
             }
             if ((src == 0x7F) && (dst_l == 0x0) && (dst_h == 0x0)
                 && ((pxct1 & 0x3) == 0x00) && ((pxct2 & 0x70) == 0x70)) {
                 // throttle semaphore symbol message
                 return tr("Throttle Semaphore Symbol Control: Loco ") +
                         QString("%1").arg((d[0]*128)+d[1]) +
                         tr(" Semaphore body ") +
                         (((d[2]&0x10)==0x10) ? tr("lit, ") : tr("unlit, ")) +
                         tr("Vertical arm ") +
                         (((d[2]&0x08)==0x08) ? tr("lit, ") : tr("unlit, ")) +
                         tr("Diagonal arm ") +
                         (((d[2]&0x04)==0x04) ? tr("lit, ") : tr("unlit, ")) +
                         tr("Horizontal arm ") +
                         (((d[2]&0x02)==0x02) ? tr("lit, ") : tr("unlit, ")) +
                         tr("Any lit arms are ") +
                         (((d[2]&0x01)==0x01) ? tr("blinking.\n") : tr("unblinking.\n"));
             }
             if ((src == 0x7F) && ((pxct1 & 0x70) == 0x00) ) {
                 // throttle text message
                 //StringBuilder s = new StringBuilder("Send Throttle Text Message to ");
                 QString s = tr("Send Throttle Text Message to ");
                 if ((dst_l == 0x00) && (dst_h == 0x00)) {
                     s.append(tr("all throttles"));
                 } else {
                     s.append(tr("Throttle "));
//                            s.append(StringUtil.twoHexFromInt(dst_h));
//                            s.append(StringUtil.twoHexFromInt(dst_l));
                 }
                 s.append(tr(" with message '"));
                 s.append((char) d[0]);
                 s.append((char) d[1]);
                 s.append((char) d[2]);
                 s.append((char) d[3]);
                 s.append((char) d[4]);
                 s.append((char) d[5]);
                 s.append((char) d[6]);
                 s.append((char) d[7]);
                 s.append("'.\n");
                 return s/*.toString()*/;
             }

             // no specific type, return generic format
             return generic + "\n\t" + data;
         } // case 0x10

         case 0x0A: {
             // throttle status
             int tcntrl = l.getElement(2);
             QString stat;
             if (tcntrl == 0x40)
                 stat = " (OK) ";
             else if (tcntrl == 0x7F)
                 stat = tr(" (no key, immed, ignored) ");
             else if (tcntrl == 0x43)
                 stat = tr(" (+ key during msg) ");
             else if (tcntrl == 0x42)
                 stat = tr(" (- key during msg) ");
             else if (tcntrl == 0x41)
                 stat = tr(" (R/S key during msg, aborts) ");
             else if (tcntrl == 0x4e) {
                 return tr("Throttle response to Semaphore Display Command\n");
             }
             else
                 stat = tr(" (unknown) ");

             return tr("Throttle status TCNTRL=") + QString("0x%1").arg(tcntrl,0,16)
                    + stat + " ID1,ID2="
                    + QString("%1").arg(l.getElement(3),0,16)
                    + QString("%1").arg(l.getElement(4),0,16) + " SLA="
                    + QString("%1").arg(l.getElement(7), 0,16) + " SLB="
                    + QString("%1").arg(l.getElement(8),0,16) + ".\n";
         } // case 0x0A

         case 0x14: {
             // Duplex Radio Management
             // DigiIPL messages
             // LocoIO, LocoServo, LocoBuffer, LocoBooster configuration messages

             switch (l.getElement(2)) {
                 case 0x01: {
                         // Seems to be a query for just duplex devices.
                         switch (l.getElement(3)) {
                             case 0x08: {
                                     return tr("Query Duplex Receivers.\n");
                             }
                             case 0x10: {
                                     return tr("Duplex Receiver Response.\n");
                             }
                             default: {
                                 forceHex = true;
                                 return tr("Unknown Duplex Channel message.\n");
                         }
                     } // end of switch (l.getElement(3))
                 }
                 case 0x02: {
                     // Request Duplex Radio Channel
                     switch (l.getElement(3)) {
                         case 0x00: {
                             // The MSB is stuffed elsewhere again...
                             int channel = l.getElement(5) | ((l.getElement(4) & 0x01) << 7);

                             return tr("Set Duplex Channel to ") + QString("%1").arg(channel) + ".\n";
                         }
                         case 0x08: {
                             return tr("Query Duplex Channel.\n");
                         }
                         case 0x10: {
                             // The MSB is stuffed elsewhere again...
                             int channel = l.getElement(5) | ((l.getElement(4) & 0x01) << 7);

                             return tr("Reported Duplex Channel is ") + QString("%1").arg(channel) + ".\n";
                         }
                         default: {
                             forceHex = true;
                             return tr("Unknown Duplex Channel message.\n");
                         }
                     } // end of switch (l.getElement(3))
                 }

                 case 0x03: {
                     // Duplex Group Name
                     // Characters appear to be 8 bit values, but transmitted over a 7 bit
                     // encoding, so high order bits are stashed in element 4 and 9.
//                            char[] groupNameArray = { (char) (l.getElement(5)  | ((l.getElement(4) & 0x01) << 7)),
//                                                                              (char) (l.getElement(6)  | ((l.getElement(4) & 0x02) << 6)),
//                                                                              (char) (l.getElement(7)  | ((l.getElement(4) & 0x04) << 5)),
//                                                                              (char) (l.getElement(8)  | ((l.getElement(4) & 0x08) << 4)),
//                                                                              (char) (l.getElement(10) | ((l.getElement(9) & 0x01) << 7)),
//                                                                              (char) (l.getElement(11) | ((l.getElement(9) & 0x02) << 6)),
//                                                                              (char) (l.getElement(12) | ((l.getElement(9) & 0x04) << 5)),
//                                                                              (char) (l.getElement(13) | ((l.getElement(9) & 0x08) << 4)) };
//                            QString groupName = new QString(groupNameArray);
                 QString groupName = "tbd";

                     // The pass code is stuffed in here, each digit in 4 bits.  But again, it's a
                     // 7 bit encoding, so the MSB of the "upper" half is stuffed into byte 14.
                     int p1 = ((l.getElement(14) & 0x01) << 3) | ((l.getElement(15) & 0x70) >> 4);
                     int p2 = l.getElement(15) & 0x0F;
                     int p3 = ((l.getElement(14) & 0x02) << 2) | ((l.getElement(16) & 0x70) >> 4);
                     int p4 = l.getElement(16) & 0x0F;

                     // It's not clear you can set A-F from throttles or Digitrax's tools, but
                     // they do take and get returned if you send them on the wire...
                     QString passcode = QString("%1").arg(p1,0,16) + QString("%1").arg(p2,0,16)
                                                 + QString("%1").arg(p3,0,16) + QString("%1").arg(p4,0,16);
                     // The MSB is stuffed elsewhere again...
                     int channel = l.getElement(17) | ((l.getElement(14) & 0x04) << 5);

                     // The MSB is stuffed elsewhere one last time.
                     int id = l.getElement(18) | ((l.getElement(14) & 0x08) << 4);

                     switch (l.getElement(3)) {
                         case 0x00: {
                             return tr("Set Duplex Group Name to '") + groupName + "'.\n";
                         }
                         case 0x08: {
                             return tr("Query Duplex Group Information.\n");
                         }
                         case 0x10: {
                              return tr("Reported Duplex Group Name is '") + groupName
                                     + tr("', Password ") + passcode
                                     + tr(", Channel ") + QString("%1").arg(channel)
                                     + ", ID " + QString("%1").arg(id)
                                     + ".\n";
                         }
                         default: {
                             forceHex = true;
                             return tr("Unknown Duplex Group Name message.\n");
                         }
                     } // end of switch (l.getElement(3))
                 }
                 case 0x04: {
                         // Duplex Group ID

                     // The MSB is stuffed elsewhere again...
                     int id = l.getElement(5) | ((l.getElement(4) & 0x01) << 7);

                     switch (l.getElement(3)) {
                         case 0x00: {
                             return "Set Duplex Group ID to '" + QString("%1").arg(id) + "'.\n";
                         }
                         case 0x08: {
                             return "Query Duplex Group ID.\n";
                         }
                         case 0x10: {
                              return "Reported Duplex Group ID is " + QString("%1").arg(id) + ".\n";
                         }
                         default: {
                             forceHex = true;
                             return "Unknown Duplex Group ID message.\n";
                         }
                     } // end of switch (l.getElement(3))
                 }
                 case 0x07: {
                     // Duplex Group Password
//                            char[] groupPasswordArray = { (char) l.getElement(5),
//                                                                                  (char) l.getElement(6),
//                                                                                  (char) l.getElement(7),
//                                                                                  (char) l.getElement(8)};
//                            String groupPassword = new String(groupPasswordArray);
                 QString groupPassword = "?????";

                     switch (l.getElement(3)) {
                         case 0x00: {
                             return "Set Duplex Group Password to '" + groupPassword + "'.\n";
                         }
                         case 0x08: {
                             return "Query Duplex Group Password.\n";
                         }
                         case 0x10: {
                             return "Reported Duplex Group Password is '" + groupPassword + "'.\n";
                         }
                         default: {
                             forceHex = true;
                             return "Unknown Duplex Group Password message.\n";
                         }
                     } // end of switch (l.getElement(3))
                 }
                 case 0x10: {
                         // Radio Channel Noise/Activity
                     switch (l.getElement(3)) {
                         case 0x08: {
                             return "Query Duplex Channel " + QString("%1").arg(l.getElement(5)) + " noise/activity report.\n";
                         }
                         case 0x10: {
                             // High order bit stashed in another element again.
                             int level = (l.getElement(6) & 0x7F) | ((l.getElement(4) & 0x02) << 6);

                             return "Reported Duplex Channel " + QString("%1").arg(l.getElement(5)) + " noise/activity level is "
                                    + QString("%1").arg(level) + "/255.\n";
                         }
                         default: {
                             forceHex = true;
                             return "Unknown Duplex Channel Activity message.\n";
                         }
                     } // end of switch (l.getElement(3))

                 }

                 case RE_IPL_PING_OPERATION: {
                     QString interpretedMessage;

                     /************************************************************************************
                      * IPL-capable device ping - OPC_RE_IPL (Device Ping Operations)                    *
                      *    The message bytes as assigned as follows:                                     *
                      *     <E5> <14> <08> <GR_OP_T> <DI_F2> <DI_Ss0> <DI_Ss1> ...                       *
                      *     <DI_Ss2> <DI_Ss3> <DI_U1> <00> <00> <DI_U2> <DI_U3> ...                      *
                      *     <00> <00><00> <00><00> <CHK>                                                 *
                      *     where:                                                                       *
                      *         <DI_F2>      encodes additional bits for the Slave device serial number. *
                      *              bits 7-4    always 0000b                                            *
                      *              bit 3       Bit 31 of Slave Device Serial Number                    *
                      *              bit 2       Bit 23 of Slave Device Serial Number                    *
                      *              bit 1       Bit 15 of Slave device Serial Number                    *
                      *              bit 0       Bit 7 of Slave device Serial Number                     *
                      *         <DI_Ss0>     encodes 7 bits of the 32 bit Host device serial number:     *
                      *             bit 7        always 0                                                *
                      *             bits 6-0     Bits 6:0 of Slave device serial number                  *
                      *         <DI_Ss1>     encodes 7 bits of the 32 bit Host device serial number:     *
                      *             bit 7        always 0                                                *
                      *             bits 6-0     Bits 14:8 of Slave device serial number                 *
                      *         <DI_Ss2>     encodes 7 bits of the 32 bit Host device serial number:     *
                      *             bit 7        always 0                                                *
                      *             bits 6-0     Bits 22:16 of Slave device serial number                *
                      *         <DI_Ss3>     encodes 7 bits of the 32 bit Host device serial number:     *
                      *              bit 7       always 0                                                *
                      *              bits 6-0    Bits 30:24 of Slave device serial number                *
                      *         <DI_U1>      unknown data                                                *
                      *             when <GR_OP_T> = 0x08                                                *
                      *                 is always 0                                                      *
                      *             when <GR_OP_T> = 0x10                                                *
                      *                 is not reverse-engineered and may be non-zero.                   *
                      *         <DI_U2>      unknown data                                                *
                      *             when <GR_OP_T> = 0x08                                                *
                      *                 is always 0                                                      *
                      *             when <GR_OP_T> = 0x10                                                *
                      *                 is not reverse-engineered and may be non-zero.                   *
                      *         <DI_U3>      unknown data                                                *
                      *             when <GR_OP_T> = 0x08                                                *
                      *                 is always 0                                                      *
                      *             when <GR_OP_T> = 0x10                                                *
                      *                 is not reverse-engineered and may be non-zero.                   *
                      *                                                                                  *
                      * Information reverse-engineered by B. Milhaupt and used with permission           *
                      ************************************************************************************/
                     /* OPC_RE_IPL (IPL Ping Operation) */
                     // Operations related to DigiIPL Device "Ping" operations
                     //
                     // "Ping" request issued from DigiIPL ver 1.09 issues this message on LocoNet.
                     // The LocoNet request message encodes a serial number but NOT a device type.
                     //
                     // Depending on which devices are selected in DigiIPL when the "ping"
                     // is selected, (and probably the S/Ns of the devices attached to the LocoNet,
                     // the response is as follows:
                     //     DT402D  LocoNet message includes the serial number from the DT402D's
                     //             Slave (RF24) serial number.  If a UR92 is attached to LocoNet,
                     //             it will send the message via its RF link to the addressed
                     //             DT402D.  (UR92 apparantly assumes that the long 802.15.4
                     //             address of the DT402D is based on the serial number embedded
                     //             in the LocoNet message, with the MS 32 bits based on the UR92
                     //             long address MS 32 bits).  If more than one UR92 is attached
                     //             to LocoNet, all will pass the message to the RF interface.
                     //     UR92    LocoNet message includes the Slave serial number from the UR92.
                     //             These messages are not passed to the RF link by the addressed
                     //             UR92.  If more than one UR92 is attached to LocoNet, and the
                     //             addressed UR92 hears the RF version of the LocoNet message, it
                     //             will respond via the RF interface with an acknowledge packet,
                     //             and a UR92 (not sure which one) responds on LocoNet with a
                     //             Ping report <e5><14><08><10>.
                     //     PR3     LocoNet message includes an effective serial number of all
                     //             zeros.  There is no LocoNet message reply generated to a
                     //             request to a PR3 S/N, but there will be a reply on the PR3's
                     //             computer interface if the ping request was sent via the PR3's
                     //             computer interface (i.e. not from some other loconet agent).
                     //     UT4D    While it has been suggested that the UT4D supports firmware
                     //             updates, the UT4D does not respond to the Ping message.
                     //     LNRP    While it has been suggested that the LNRP supports firmware
                     //             updates, the LNRP does not respond to the Ping message.
                     //
                     // Ping Report values:
                     //     <unkn1> Seems always to be <0C>.  None of the bytes relate to
                     //             Duplex Channel Number.
                     //     <unkn2> Matches byte 15 of the MAC payload of the reply sent by the
                     //             targeted UR92.
                     //     <unkn3> Unclear what this byte means.
                     //
                     // Information reverse-engineered by B. Milhaupt and used with permission

                     if (l.getElement(3) == 0x08) {  /* OPC_RE_IPL (IPL Ping Query) */
                     // Ping Request: <e5><14><08><08><msBits><Sn0><Sn1><Sn2><Sn3><0><0><0><0><0><0><0><0><0><0><0><Chk>


                         if ((((l.getElement(4)&0xF) != 0) || (l.getElement(5) != 0) ||
                             (l.getElement(6) != 0) || (l.getElement(7) != 0) || (l.getElement(8) != 0)) &&
                             (l.getElement(9) == 0) && (l.getElement(10) == 0) &&
                             (l.getElement(11) == 0) && (l.getElement(12) == 0) &&
                             (l.getElement(13) == 0) && (l.getElement(14) == 0) &&
                             (l.getElement(15) == 0) && (l.getElement(16) == 0) &&
                             (l.getElement(17) == 0) && (l.getElement(18) == 0)) {

                             interpretedMessage = tr("Ping request.\n");
                             int hostSnInt = 0;
                             hostSnInt = ( l.getElement(5)+(((l.getElement(4)&0x1)==1)?128:0))+
                                 ((l.getElement(6)+(((l.getElement(4)&0x2)==2)?128:0))*256)+
                                 ((l.getElement(7)+(((l.getElement(4)&0x4)==4)?128:0))*256*256)+
                                 ((l.getElement(8)+(((l.getElement(4)&0x8)==8)?128:0))*256*256*256)
                                     ;
                             interpretedMessage += tr("\tPinging device with serial number ")+
                                     QString("0x%1").arg(hostSnInt,0,16).toUpper()+"\n";
                             return interpretedMessage;
                         }
                         else {
                             // 0xE5 message of unknown format
                             forceHex = true;
                             return tr("Message with opcode 0xE5 and unknown format.");
                         }
                     }
                     else if (l.getElement(3) == 0x10) {  /* OPC_RE_IPL (IPL Ping Report) */
                     // Ping Report:  <e5><14><08><10><msbits><Sn0><Sn1><Sn2><Sn3><unkn1><0><0><Unkn2><Unkn3><0><0><0><0><0><Chk>
                         if (((l.getElement(4)&0xF) != 0) ||(l.getElement(5) != 0) || (l.getElement(6) != 0) ||
                                 (l.getElement(7) != 0) || (l.getElement(8) != 0)) {   // if any serial number bit is non-zero //

                             interpretedMessage = tr("Ping Report.\n");
                             int hostSnInt = 0;
                             hostSnInt = ( l.getElement(5)+(((l.getElement(4)&0x1)==1)?128:0))+
                                 ((l.getElement(6)+(((l.getElement(4)&0x2)==2)?128:0))*256)+
                                 ((l.getElement(7)+(((l.getElement(4)&0x4)==4)?128:0))*256*256)+
                                 ((l.getElement(8)+(((l.getElement(4)&0x8)==8)?128:0))*256*256*256)
                                     ;
                             interpretedMessage += tr("\tPing response from device with serial number ")+
                                 QString("%1").arg(hostSnInt,0,16).toUpper()+
                                 " Local RSSI = 0x"+ QString("%1").arg(l.getElement(12) + (((l.getElement(9))&0x4) == 0x4 ? 128 : 0),0,16).toUpper()+
                                 " Remote RSSI = 0x"+QString("%1").arg(l.getElement(13) + (((l.getElement(9))&0x8) == 0x8 ? 128 : 0),0,16).toUpper()+
                                 ".\n";
                             return interpretedMessage;
                         }
                         else {
                             // 0xE5 message of unknown format
                             forceHex = true;
                             return tr("Message with opcode 0xE5 and unknown format.");
                         }
                     }
                     else {
                         // 0xE5 message of unknown format
                         forceHex = true;
                         return tr("Message with opcode 0xE5 and unknown format.");
                     }
                 } //end of case 0x08, which decodes 0xe5 0x14 0x08

                 case RE_IPL_IDENTITY_OPERATION: {
                     QString interpretedMessage;
                     // Operations related to DigiIPL "Ping", "Identify" and "Discover"
                     QString device = "";

                     switch (l.getElement(3)) {
                         case 0x08: {
                             if ((l.getElement(4) == 0) &&
                                 (l.getElement(5) == 0) && (l.getElement(6) == 0) &&
                                 (l.getElement(7) == 0) && (l.getElement(8) == 0) &&
                                 (l.getElement(9) == 0) && (l.getElement(10) == 0) &&
                                 (l.getElement(11) == 1) && (l.getElement(12) == 0) &&
                                 (l.getElement(13) == 0) && (l.getElement(14) == 0) &&
                                 (l.getElement(15) == 0) && (l.getElement(16) == 0) &&
                                 (l.getElement(17) == 0) && (l.getElement(18) == 0)) {
                                 /************************************************************************************
                                  * IPL capable device query - RE_IPL_IDENTITY_OPERATION (Device Query)              *
                                  *    The message bytes are assigned as follows:                                    *
                                  *     <E5> <14> <0F> <08> <00> <00> <00> <00> <00> <00> <00> <01> <00> <00> ...    *
                                  *             <00> <00> <00> <00> <00> <CHK>                                       *
                                  *                                                                                  *
                                  *      Information reverse-engineered by B. Milhaupt and used with permission      *
                                  ************************************************************************************/
                                 // Request for all IPL-queryable devices to report their presence
                                 //
                                 // Information reverse-engineered by B. Milhaupt and used with permission

                                 return "Discover all IPL-capable devices request.\n";
                             }
                             else if (((l.getElement(5) != 0) || (l.getElement(6) != 0)) ) {
                                 /************************************************************************************
                                  * IPL device query by type - RE_IPL_IDENTITY_OPERATION (Device Query)              *
                                  *    The message bytes are assigned as follows:                                    *
                                  *     <E5> <14> <0F> <08> <DI_Hmf> <DI_Hst> <DI_Slv> <00> <00> <00> <00> <01> ...  *
                                  *             <00> <00> <00> <00> <00> <00> <00> <CHK>                             *
                                  *    where:                                                                        *
                                  *       <DI_Hmf>  DigiIPL-capable Host device manufacturer number.  This is not    *
                                  *                 the same as an NMRA Manufacturer ID.                             *
                                  *                 0x00                     Digitrax                                *
                                  *                 Others                   No other Host device manufacturer       *
                                  *                                                numbers have been reverse-        *
                                  *                                                engineered                        *
                                  *       <DI_Hst> encodes the DigiIPL-capable Host device type as follows:          *
                                  *             When <DI_Hmf> = 0x00                                                 *
                                  *                 0x00 (0 decimal)         No Host device type reported            *
                                  *                 0x04 (4 decimal)         UT4D (Note that UT4D, UT4 and UT4R do   *
                                  *                                                not respond to this DigiIPL       *
                                  *                                                request)                          *
                                  *                 0x18 (24 decimal)        RF24 - not typically a Host device      *
                                  *                 0x23 (35 decimal)        PR3                                     *
                                  *                 0x2A (42 decimal)        DT402 (or DT402R or DT402D)             *
                                  *                 0x33 (51 decimal)        DCS51                                   *
                                  *                 0x5C (92 decimal)        UR92                                    *
                                  *                 Others                   No other Host device types have been    *
                                  *                                                reverse-engineered                *
                                  *             When <DI_Hmf> is not 0x00                                            *
                                  *                 All values               Not reverse-engineered                  *
                                  *       <DI_Slv> encodes the DigiIPL-capable Slave device type as follows:         *
                                  *             When <DI_Smf> = 0x00                                                 *
                                  *                 0x00 (0 decimal)         Report for all Slave device types       *
                                  *                 0x18 (24 decimal)        RF24                                    *
                                  *                 Others                   No other Slave device types have been   *
                                  *                                                reverse-engineered                *
                                  *                                                                                  *
                                  *      Information reverse-engineered by B. Milhaupt and used with permission      *
                                  ************************************************************************************/
                                 // Request for IPL-queryable devices of given manufacturer and type to report
                                 // their presence
                                 //
                                 // Note that standard definitions are provided for UT4D and RF24, even though these
                                 // devices do not respond to this query.  Note that UT4D will respond to IPL capable
                                 // device query with DI_Hmf = 0, DI_Hst = 0, DI_Slv = 0, and DI_Smf = 0.
                                 //
                                 // Information reverse-engineered by B. Milhaupt and used with permission

                                 device =  getDeviceNameFromIPLInfo(l.getElement(4), l.getElement(5));
                                 QString slave =  getSlaveNameFromIPLInfo(l.getElement(4), l.getElement(6));
                                 interpretedMessage = "Discover " + device +
                                         " devices and/or " + QString("%1").arg(slave) +" devices.\n";
                                 return interpretedMessage;
                             }
                             else {
                                 // 0xE5 message of unknown format
                                 forceHex = true;
                                 return "Message with opcode 0xE5 and unknown format.";
                             }
                         } // end case 0x08, which decodes 0xe5 0x14 0x0f 0x08
                         case 0x10: {
                             /************************************************************************************
                              * IPL device identity report - RE_IPL_IDENTITY_OPERATION (Device Report)           *
                              *    The message bytes are assigned as follows:                                    *
                              *     <E5> <14> <0F> <08> <DI_Hmf> <DI_Hst> <DI_Slv> <DI_Smf> <DI_Hsw> ...         *
                              *             <DI_F1> <DI_Ssw> <DI_Hs0> <DI_Hs1> <DI_Hs2> <DI_F2> <DI_Ss0> ...     *
                              *             <DI_Ss1> <DI_Ss2> <DI_Ss3> <CHK>                                     *
                              *    where:                                                                        *
                              *       <DI_Hmf>  DigiIPL-capable Host device manufacturer number.  This is not    *
                              *                 the same as an NMRA Manufacturer ID.                             *
                              *                 0x00                     Digitrax                                *
                              *                 Others                   No other Host device manufacturer       *
                              *                                                numbers have been reverse-        *
                              *                                                engineered                        *
                              *       <DI_Hst> encodes the DigiIPL-capable Host device type as follows:          *
                              *             When <DI_Hmf> = 0x00                                                 *
                              *                 0x00 (0 decimal)         No Host device type reported            *
                              *                 0x04 (4 decimal)         UT4D                                    *
                              *                 0x23 (35 decimal)        PR3                                     *
                              *                 0x2A (42 decimal)        DT402 (or DT402R or DT402D)             *
                              *                 0x33 (51 decimal)        DCS51                                   *
                              *                 0x5C (92 decimal)        UR92                                    *
                              *                 Others                   No other Host device types have been    *
                              *                                                reverse-engineered                *
                              *             When <DI_Hmf> is not 0x00                                            *
                              *                 All values               Not reverse-engineered                  *
                              *       <DI_Slv> encodes the DigiIPL-capable Slave device type as follows:         *
                              *             When <DI_Smf> = 0x00                                                 *
                              *                 0x00 (0 decimal)         Report for all Slave device types       *
                              *                 0x18 (24 decimal)        RF24                                    *
                              *                 Others                   No other Slave device types have been   *
                              *                                                reverse-engineered                *
                              *       <DI_Smf>  DigiIPL-capable Slave device manufacturer number.  This is not   *
                              *                 the same as an NMRA Manufacturer ID.                             *
                              *                 0x00                     Digitrax                                *
                              *                 Others                   No other Slave device manufacturer      *
                              *                                                numbers have been reverse-        *
                              *                                                engineered                        *
                              *       <DI_Hsw> encodes the DigiIPL-capable Host device firmware revision         *
                              *                number as follows:                                                *
                              *              bit 7       always 0                                                *
                              *              bits 6-3    Host device firmware major revision number              *
                              *              bits 2-0    Host device firmware minor revision number              *
                              *       <DI_F1> encodes additional bits for the Slave device firmware major        *
                              *               revision number and for the Host device serial number.             *
                              *              bits 7-4    always 0000b                                            *
                              *              bit 3       Bit 23 of Host Device Serial Number                     *
                              *              bit 2       Bit 15 of Host Device Serial Number                     *
                              *              bit 1       Bit 7 of Host Device Serial Number                      *
                              *              bit 0       bit 4 of Slave device firmware Major number             *
                              *       <DI_Ssw> encodes the DigiIPL-capable Slave device firmware revision        *
                              *                number as follows:                                                *
                              *              bit 7       always 0                                                *
                              *              bits 6-3    Host device firmware major revision number              *
                              *              bits 6-3    4 least-significant bits of Slave device firmware major *
                              *                              revision number (see also <DI_F1>[0])               *
                              *              bits 2-0    Slave device firmware minor revision number             *
                              *       <DI_Hs0> encodes 7 bits of the 24 bit Host device serial number:           *
                              *              bit 7       always 0                                                *
                              *              bits 6-3    Bits 6-0 of Host device serial number                   *
                              *       <DI_Hs1> encodes 7 bits of the 24 bit Host device serial number:           *
                              *              bit 7       always 0                                                *
                              *              bits 6-3    Bits 14-9 of Host device serial number                  *
                              *       <DI_Hs2> encodes 7 bits of the 24 bit Host device serial number:           *
                              *              bit 7       always 0                                                *
                              *              bits 6-3    Bits 22-16 of Host device serial number                 *
                              *       <DI_F2> encodes additional bits for the Slave device serial number.        *
                              *              bits 7-4    always 0000b                                            *
                              *              bit 3       Bit 31 of Slave Device Serial Number                    *
                              *              bit 2       Bit 23 of Slave Device Serial Number                    *
                              *              bit 1       Bit 15 of Slave Device Serial Number                    *
                              *              bit 0       Bit 7 of Slave Device Serial Number                     *
                              *       <DI_Ss0> encodes 7 bits of the 32 bit Slave device serial number:          *
                              *              bit 7       always 0                                                *
                              *              bits 6-3    Bits 6-0 of Slave device serial number                  *
                              *       <DI_Ss1> encodes 7 bits of the 32 bit Slave device serial number:          *
                              *              bit 7       always 0                                                *
                              *              bits 6-3    Bits 14-9 of Slave device serial number                 *
                              *       <DI_Ss2> encodes 7 bits of the 32 bit Slave device serial number:          *
                              *              bit 7       always 0                                                *
                              *              bits 6-3    Bits 22-16 of Slave device serial number                *
                              *       <DI_Ss3> encodes 7 bits of the 32 bit Slave device serial number:          *
                              *              bit 7       always 0                                                *
                              *              bits 6-3    Bits 30-24 of Slave device serial number                *
                              *                                                                                  *
                              * Information reverse-engineered by B. Milhaupt and used with permission           *
                              ************************************************************************************/
                             // Request for one specific IPL-queryable device to return its identity information.
                             // Expected response is of type <E5><14><10>...
                             //
                             // Note that standard definitions are provided for RF24, even though these
                             // devices do not generate this report.
                             //
                             // Information reverse-engineered by B. Milhaupt and used with permission
                             interpretedMessage = tr("IPL Identity report.\n");
                             QString HostType =  getDeviceNameFromIPLInfo(l.getElement(4), l.getElement(5));
                             QString HostVer = QString("%1").arg((l.getElement(8)&0x78)>> 3)+"."+QString("%1").arg((l.getElement(8)&0x7));
                             int hostSnInt = ((l.getElement(13)+(((l.getElement(9)&0x8)==8)?128:0))*256*256)+
                                         ((l.getElement(12)+(((l.getElement(9)&0x4)==4)?128:0))*256)+
                                         (l.getElement(11)+(((l.getElement(9)&0x2)==2)?128:0)) ;
                             QString HostSN = QString("%1").arg(hostSnInt,0,16).toUpper();

                             QString SlaveType = getSlaveNameFromIPLInfo(l.getElement(4), l.getElement(6));
                             QString SlaveVer = "";
                             QString SlaveSN = "";
                             if (l.getElement(6) > 0) {
                                 SlaveVer = (((l.getElement(10)&0x78)>> 3)+((l.getElement(9)&1)<<4))+"."+((l.getElement(10)&0x7));
                                 int slaveSnInt =
                                         ((l.getElement(15)+(((l.getElement(14)&0x1)==1)?128:0)))+
                                         ((l.getElement(16)+(((l.getElement(14)&0x2)==2)?128:0))*256)+
                                         ((l.getElement(17)+(((l.getElement(14)&0x4)==4)?128:0))*256*256)+
                                         ((l.getElement(18)+(((l.getElement(14)&0x8)==8)?128:0))*256*256*256);
                                 SlaveSN =
                                         QString("%1").arg(slaveSnInt,0,16).toUpper();
                             }
                             else {
                                 SlaveVer = "N/A";
                                 SlaveSN = "N/A";
                             }

                             interpretedMessage += "\tHost: "+HostType+
                                     ", S/N: " +HostSN+
                                     ", S/W Version: "+HostVer+
                                     "\n\tSlave: "+SlaveType+
                                     ", S/N: "+SlaveSN+
                                     ", S/W Version: "+SlaveVer+"\n";
                             return interpretedMessage;
                         } // end case 0x10, which decodes 0xe5 0x14 0x0f 0x10
                         default: {
                             // 0xE5 message of unknown format
                             forceHex = true;
                             return tr("Message with opcode 0xE5 and unknown format.");
                         }

                     } // end of switch (l.getElement(3)), which decodes 0xe5 0x14 0x0f 0x??
                 } //end of case 0x0f, which decodes 0xe5 0x14 0x0f

                 default: {
                     // 0xE5 message of unknown format
                     forceHex = true;
                     return tr("Message with opcode 0xE5 and unknown format.");

                 }
             } // switch (l.getElement(2))
         } // case 0x14  (length of message)
         case 0x09: {
             /*
              * Transponding "find" query and report messages
              *
              * Information reverse-engineered by B. Milhaupt and used with permission */
             switch (l.getElement(2)) {
                 case 0x40: {
                     /************************************************************************************
                      * Transponding "find" query message                                                *
                      *    The message bytes are assigned as follows:                                    *
                      *     <0xE5> <0x09> <0x40> <AD_H> <AD_L> <0x00> <0x00> <0x00> <CHK>                *
                      *    where:                                                                        *
                      *       <AD_H> is encoded as shown below:                                          *
                      *          When <AD_H>  = 0x7D,                                                    *
                      *              Address is a 7 bit value defined solely by <AD_L>.                  *
                      *          When <AD_H>  is not 0x7D,                                               *
                      *              Address is a 14 bit value; AD_H{6:0} represent the upper 7 bits     *
                      *              of the 14 bit address.                                              *
                      *       <AD_L> contains the least significant 7 bits of the 14 or 7 bit address.   *
                      *                                                                                  *
                      * Information reverse-engineered by B. Milhaupt and used with permission           *
                      ************************************************************************************/
                     int locoAddr = l.getElement(4);
                     if (l.getElement(3) != 0x7d) {
                         locoAddr += l.getElement(3)<<7;
                     }
                     return tr("Transponding Find query for loco address ") +
                             QString("%1").arg(locoAddr) + ".\n";
                 }
                 case 0x00: {
                     /************************************************************************************
                      * Transponding "find" report message                                               *
                      *    The message bytes are assigned as follows:                                    *
                      *     <0xE5> <0x09> <0x00> <AD_H> <AD_L> <TR_ST> <TR_ZS> <0x00> <CHK>              *
                      * where:                                                                           *
                      *      <AD_H>  is encoded as shown below:                                          *
                      *          When <AD_H>  = 0x7D,                                                    *
                      *              Address is a 7 bit value defined solely by <AD_L>.                  *
                      *          When <AD_H>  is not 0x7D,                                               *
                      *              Address is a 14 bit value; AD_H{6:0} represent the upper 7 bits     *
                      *              of the 14 bit address.                                              *
                      *      <AD_L>  contains the least significant 7 bits of the 14 or 7 bit address.   *
                      *      <TR_ST> contains the transponding status for the addressed equipment,       *
                      *              encoded as:                                                         *
                      *          bits 7-6    always 00b                                                  *
                      *          bit 5       encodes transponding presence                               *
                      *                  0 = Addressed equipment is absent                               *
                      *                  1 = Addressed equipment is present                              *
                      *          bits 4-0    encode bits 7-3 of the Detection Section                    *
                      *   <TR_ZS> contains the zone number and detection section, encoded as:            *
                      *          bit 7       always 0                                                    *
                      *          bits 6-4    encode bits 2-0 of the Detection Section                    *
                      *          bits 3-1    encode the Transponding Zone as shown below                 *
                      *                 000b     Zone A                                                  *
                      *                 001b     Zone B                                                  *
                      *                 010b     Zone C                                                  *
                      *                 011b     Zone D                                                  *
                      *                 100b     Zone E                                                  *
                      *                 101b     Zone F                                                  *
                      *                 110b     Zone G                                                  *
                      *                 111b     Zone H                                                  *
                      *          bit 0       always 0                                                    *
                      *                                                                                  *
                      * Information reverse-engineered by B. Milhaupt and used with permission           *
                      ************************************************************************************/

                     int section = ((l.getElement(5) & 0x1F)<<3) +((l.getElement(6)&0x70) >>4)+1;
                     QString zone;
                     int locoAddr = l.getElement(4);

                     if (l.getElement(3) != 0x7d) {
                         locoAddr += l.getElement(3)<<7;
                     }

                     switch (l.getElement(6)&0x0F) {
                         case 0x00: zone = "A"; break;
                         case 0x02: zone = "B"; break;
                         case 0x04: zone = "C"; break;
                         case 0x06: zone = "D"; break;
                         case 0x08: zone = "E"; break;
                         case 0x0A: zone = "F"; break;
                         case 0x0C: zone = "G"; break;
                         case 0x0E: zone = "H"; break;
                         default: zone=tr("<unknown ")+QString("%1").arg(l.getElement(2)&0x0F)+">"; break;
                     }

                     // get system and user names
                     QString reporterSystemName = "";
                     QString reporterUserName = "";

                     reporterSystemName = locoNetReporterPrefix +
                            QString("%1").arg((l.getElement(5)&0x1F)*128 + l.getElement(6) +1);

                     try {
                         Reporter* reporter = reporterManager->getBySystemName(reporterSystemName);
                         if ((reporter != NULL) && (reporter->getUserName().length() > 0))
                             reporterUserName = "(" + reporter->getUserName() + ")";
                         else
                             reporterUserName = "()";
                     }
                     catch (Exception e) {
                         reporterUserName = "()";
                     }
                     return "Transponder Find report : address "
                             + QString("%1").arg(locoAddr)
                             +((l.getElement(3) == 0x7d) ? " (short)" : " (long)")
                             + " present at "
                             + reporterSystemName + " " + reporterUserName
                             + " (BDL16x Board " + QString("%1").arg(section)  + " RX4 zone " + QString("%1").arg(zone)
                             + ").\n";
                 }
                 default: {
                     // 0xE5 message of unknown format
                     forceHex = true;
                     return tr("Message with opcode 0xE5 and unknown format.");
                 }
             } // end of switch (l.getElement(2))
         } // end of case 0x09:

         default: {
             // 0xE5 message of unknown format
             forceHex = true;
             return tr("Message with opcode 0xE5 and unknown format.");

         }
     } // end of switch (l.getElement(1))
 } // case LnConstants::OPC_PEER_XFER

 case LnConstants::OPC_LISSY_UPDATE: {
     /*
      * OPC_LISSY_UPDATE   0xE5
      *
      * LISSY is an automatic train detection system made by Uhlenbrock.
      * All documentation appears to be in German.
      *
      */
     switch (l.getElement(1))
     {
         case 0x08: // Format LISSY message
         {
             int unit = (l.getElement(4) & 0x7F);
             int address = (l.getElement(6) & 0x7F) + 128 * (l.getElement(5) & 0x7F);
             if (l.getElement(2) == 0x00) {
                 // Reverse-engineering note: interpretation of element 2 per wiki.rocrail.net
                 // OPC_LISSY_REP
                 return "Lissy " + QString("%1").arg(unit) +
                         " IR Report: Loco " + QString("%1").arg(address) +
                         " moving " +
                         ((l.getElement(3)&0x20)==0 ? "north\n":"south\n");
             }
             else if (l.getElement(2) == 0x01) {
                 // Reverse-engineering note: interpretation of element 2 per wiki.rocrail.net
                 // OPC_WHEELCNT_REP
                 int wheelCount = (l.getElement(6)&0x7F)+128*(l.getElement(5)&0x7F);
                 return "Lissy " + QString("%1").arg(unit) +
                         " Wheel Report: " + QString("%1").arg(wheelCount) +
                         " wheels moving " +
                         ((l.getElement(3)&0x20)==0 ? "north\n":"south\n");
             }
             else {
                 forceHex = true;
                 return "Unrecognized Lissy message varient.\n";
              }
         }
         case 0x0A: // Format special message
         {
             int element = l.getElement(2) * 128 + l.getElement(3);
             int stat1 = l.getElement(5);
             int stat2 = l.getElement(6);
             QString status;
             if ((stat1 & 0x10) != 0)
                 if ((stat1 & 0x20) != 0)
                     status = " AX, XA reserved; ";
                 else
                     status = " AX reserved; ";
             else if ((stat1 & 0x20) != 0)
                 status = " XA reserved; ";
             else
                 status = " no reservation; ";
             if ((stat2 & 0x01) != 0)
                 status += "Turnout thrown; ";
             else
                 status += "Turnout closed; ";
             if ((stat1 & 0x01) != 0)
                 status += "Occupied";
             else
                 status += "Not occupied";
             return "SE" + QString("%1").arg(element + 1) + " (" + QString("%1").arg(element) + ") reports AX:" + QString("%1").arg(l.getElement(7))
                    + " XA:" + QString("%1").arg(l.getElement(8)) + status + "\n";
         }
         default:
             forceHex = true;
             return "Unrecognized OPC_LISSY_UPDATE command varient.\n";
         }
     } // case LnConstants::OPC_LISSY_UPDATE

     /*
      * OPC_IMM_PACKET   0xED   ;SEND n-byte packet immediate LACK
      *                         ; Follow on message: LACK
      *                         ; <0xED>,<0B>,<7F>,<REPS>,<DHI>,<IM1>,<IM2>,
      *                         ;        <IM3>,<IM4>,<IM5>,<CHK>
      *                         ;   <DHI>=<0,0,1,IM5.7-IM4.7,IM3.7,IM2.7,IM1.7>
      *                         ;   <REPS>  D4,5,6=#IM bytes,
      *                         ;           D3=0(reserved);
      *                         ;           D2,1,0=repeat CNT
      *                         ; IF Not limited MASTER then
      *                         ;   LACK=<B4>,<7D>,<7F>,<chk> if CMD ok
      *                         ; IF limited MASTER then Lim Masters respond
      *                         ;   with <B4>,<7E>,<lim adr>,<chk>
      *                         ; IF internal buffer BUSY/full respond
      *                         ;   with <B4>,<7D>,<0>,<chk>
      *                         ;   (NOT IMPLEMENTED IN DT200)
      *
      * This sends a raw NMRA packet across the LocoNet.
      *
      * Page 11 of LocoNet Personal Edition v1.0.
      *
      * Decodes for the F9-F28 functions taken from the NMRA standards and
      * coded by Leo Bicknell.
      */
     case LnConstants::OPC_IMM_PACKET: {
         // sendPkt = (sendPktMsg *) msgBuf;
         int val7f = l.getElement(2); /* fixed value of 0x7f */
         int reps = l.getElement(3); /* repeat count */
         int dhi = l.getElement(4); /* high bits of data bytes */
         int im1 = l.getElement(5);
         int im2 = l.getElement(6);
         int im3 = l.getElement(7);
         int im4 = l.getElement(8);
         int im5 = l.getElement(9);
         int mobileDecoderAddress =-999;
         int nmraInstructionType = -999;
         int nmraSubInstructionType = -999;
         int playableWhistleLevel = -999;

         // see if it really is a 'Send Packet' as defined in Loconet PE
         if (val7f == 0x7f) {
             int len = ((reps & 0x70) >> 4);
             // duplication of packet data as packetInt was deemed necessary
             // due to issues with msBit loss when converting from "byte" to
             // integral forms
             //byte[] packet = new byte[len];
             QList<char> packet;
             for(int i =0; i < len; i++)
              packet.append(0);
             //packet.reserve(len);
             //int[] packetInt = new int[len];
             QList<int> packetInt;
             packetInt.reserve(len);
             for(int i =0; i < len; i++)
              packetInt.append(0);
             packet[0] = (char) (im1 + ((dhi & 0x01) != 0 ? 0x80 : 0));
             packetInt[0] = (im1 + ((dhi & 0x01) != 0 ? 0x80 : 0));
             if (len >= 2) {
                 packet[1] = (char) (im2 + ((dhi & 0x02) != 0 ? 0x80 : 0));
                 packetInt[1] = (im2 + ((dhi & 0x02) != 0 ? 0x80 : 0));
             }
             if (len >= 3) {
                 packet[2] = (char) (im3 + ((dhi & 0x04) != 0 ? 0x80 : 0));
                 packetInt[2] = (im3 + ((dhi & 0x04) != 0 ? 0x80 : 0));
             }
             if (len >= 4) {
                 packet[3] = (char) (im4 + ((dhi & 0x08) != 0 ? 0x80 : 0));
                 packetInt[3] = (im4 + ((dhi & 0x08) != 0 ? 0x80 : 0));
             }
             if (len >= 5) {
                 packet[4] = (char) (im5 + ((dhi & 0x10) != 0 ? 0x80 : 0));
                 packetInt[4] = (im5 + ((dhi & 0x10) != 0 ? 0x80 : 0));
             }

             int address;
             // compute some information which is useful for decoding
             // the "Playable" whistle message
             // Information reverse-engineered by B. Milhaupt and used with permission
             if ((packetInt[0] & 0x80)  == 0x0) {
                 // immediate packet addresses a 7-bit multi-function (mobile) decoder
                 mobileDecoderAddress = packetInt[0];
                 nmraInstructionType = (packetInt[1] & 0xE) >> 5;
                 nmraSubInstructionType = (packetInt[1] & 0x1f);
                 if ((nmraSubInstructionType == 0x1d) && (packetInt[2] == 0x7f)) {
                     playableWhistleLevel = packetInt[3];
                 }
             }
             else if ((packetInt[0] & 0xC0) == 0xC0) {
                 // immediate packet addresses a 14-bit multi-function (mobile) decoder
                 mobileDecoderAddress =  ( (packetInt[0] & 0x3F) << 8) + packetInt[1];
                 nmraInstructionType = (packetInt[2] & 0xE0) >> 5;
                 nmraSubInstructionType = (packetInt[2] & 0x1f);
                 if ((nmraSubInstructionType == 0x1d) && (packetInt[3] == 0x7f)) {
                     playableWhistleLevel = packetInt[4];
                 }
             }
             else {
                 // immediate packet not addressed to a multi-function (mobile) decoder
             }
             QString generic = "";
             if ((mobileDecoderAddress >= 0) &&
                     (nmraInstructionType == 1) &&
                     (nmraSubInstructionType == 0x1D)) {
                 // the "Playable" whistle message
                 // Information reverse-engineered by B. Milhaupt and used with permission
                  generic = "Playable Whistle control - Loco " +
                         QString("%1").arg(mobileDecoderAddress) +
                         " whistle to " +
                         QString("%1").arg(playableWhistleLevel) +
                         " (repeat "+ (reps & 0x7) +" times).\n";
                  return generic;
             }
             /*
              * We use this two places below, so we generate it once here.
              * That seems wrong, but what we really need is to be able to
              * decode any NMRA packet here, which is a lot more work!
              */
             generic = "Send packet immediate: "
                              + QString("%1").arg((reps & 0x70) >> 4)
                              + " bytes, repeat count " + QString("%1").arg(reps & 0x07)
                              + "(" + QString("%1").arg(reps) + ")" + "\n\tDHI=0x"
                              + QString("%1").arg(dhi,0,16) + ", IM1=0x"
                              + QString("%1").arg(im1,0,16) + ", IM2=0x"
                              + QString("%1").arg(im2,0,16) + ", IM3=0x"
                              + QString("%1").arg(im3,0,16) + ", IM4=0x"
                              + QString("%1").arg(im4,0,16) + ", IM5=0x"
                              + QString("%1").arg(im5,0,16) + "\n\tpacket: ";

             // F9-F28 w/a long address.
             if ((packetInt[0] & 0xC0) == 0xC0) {
                 address = ((packetInt[0] & 0x3F) << 8) + packetInt[1];

                 if ((packetInt[2] & 0xFF) == 0xDF) {
                     // Functions 21-28
                     return "Send packet immediate: Locomotive " + QString("%1").arg(address)
                            + " set" + " F21="
                            + ((packetInt[3] & 0x01) > 0 ? tr("On") : tr("Off"))
                            + ", F22="
                            + ((packetInt[3] & 0x02) > 0 ? tr("On") : tr("Off"))
                            + ", F23="
                            + ((packetInt[3] & 0x04) > 0 ? tr("On") : tr("Off"))
                            + ", F24="
                            + ((packetInt[3] & 0x08) > 0 ? tr("On") : tr("Off"))
                            + ", F25="
                            + ((packetInt[3] & 0x10) > 0 ? tr("On") : tr("Off"))
                            + ", F26="
                            + ((packetInt[3] & 0x20) > 0 ? tr("On") : tr("Off"))
                            + ", F27="
                            + ((packetInt[3] & 0x40) > 0 ? tr("On") : tr("Off"))
                            + ", F28="
                            + ((packetInt[3] & 0x80) > 0 ? tr("On") : tr("Off")) + "\n";
                 } else if ((packetInt[2] & 0xFF) == 0xDE) {
                     // Functions 13-20
                     return "Send packet immediate: Locomotive " + QString("%1").arg(address)
                            + " set" + " F13="
                            + ((packetInt[3] & 0x01) > 0 ? tr("On") : tr("Off"))
                            + ", F14="
                            + ((packetInt[3] & 0x02) > 0 ? tr("On") : tr("Off"))
                            + ", F15="
                            + ((packetInt[3] & 0x04) > 0 ? tr("On") : tr("Off"))
                            + ", F16="
                            + ((packetInt[3] & 0x08) > 0 ? tr("On") : tr("Off"))
                            + ", F17="
                            + ((packetInt[3] & 0x10) > 0 ? tr("On") : tr("Off"))
                            + ", F18="
                            + ((packetInt[3] & 0x20) > 0 ? tr("On") : tr("Off"))
                            + ", F19="
                            + ((packetInt[3] & 0x40) > 0 ? tr("On") : tr("Off"))
                            + ", F20="
                            + ((packetInt[3] & 0x80) > 0 ? tr("On") : tr("Off")) + "\n";
                 } else if ((packetInt[2] & 0xF0) == 0xA0) {
                     // Functions 8-12
                     return "Send packet immediate: Locomotive " + QString("%1").arg(address)
                            + " set" + ", F09="
                            + ((packetInt[2] & 0x01) > 0 ? tr("On") : tr("Off"))
                            + ", F10="
                            + ((packetInt[2] & 0x02) > 0 ? tr("On") : tr("Off"))
                            + ", F11="
                            + ((packetInt[2] & 0x04) > 0 ? tr("On") : tr("Off"))
                            + ", F12="
                            + ((packetInt[2] & 0x08) > 0 ? tr("On") : tr("Off")) + "\n";
                 } else {
                     // Unknown
                     return generic /*+ jmri.NmraPacket.format(packet) */+ "\n";
                 }
             } else { // F9-F28 w/a short address.
                 address = packetInt[0];
                 if ((packetInt[1] & 0xFF) == 0xDF) {
                     // Functions 21-28
                     return "Send packet immediate: Locomotive " + QString("%1").arg(address)
                            + " set" + " F21="
                            + ((packetInt[2] & 0x01) > 0 ? tr("On") : tr("Off"))
                            + ", F22="
                            + ((packetInt[2] & 0x02) > 0 ? tr("On") : tr("Off"))
                            + ", F23="
                            + ((packetInt[2] & 0x04) > 0 ? tr("On") : tr("Off"))
                            + ", F24="
                            + ((packetInt[2] & 0x08) > 0 ? tr("On") : tr("Off"))
                            + ", F25="
                            + ((packetInt[2] & 0x10) > 0 ? tr("On") : tr("Off"))
                            + ", F26="
                            + ((packetInt[2] & 0x20) > 0 ? tr("On") : tr("Off"))
                            + ", F27="
                            + ((packetInt[2] & 0x40) > 0 ? tr("On") : tr("Off"))
                            + ", F28="
                            + ((packetInt[2] & 0x80) > 0 ? tr("On") : tr("Off")) + "\n";
                 } else if ((packetInt[1] & 0xFF) == 0xDE) {
                     // Functions 13-20
                     return "Send packet immediate: Locomotive " + QString("%1").arg(address)
                            + " set" + " F13="
                            + ((packetInt[2] & 0x01) > 0 ? tr("On") : tr("Off"))
                            + ", F14="
                            + ((packetInt[2] & 0x02) > 0 ? tr("On") : tr("Off"))
                            + ", F15="
                            + ((packetInt[2] & 0x04) > 0 ? tr("On") : tr("Off"))
                            + ", F16="
                            + ((packetInt[2] & 0x08) > 0 ? tr("On") : tr("Off"))
                            + ", F17="
                            + ((packetInt[2] & 0x10) > 0 ? tr("On") : tr("Off"))
                            + ", F18="
                            + ((packetInt[2] & 0x20) > 0 ? tr("On") : tr("Off"))
                            + ", F19="
                            + ((packetInt[2] & 0x40) > 0 ? tr("On") : tr("Off"))
                            + ", F20="
                            + ((packetInt[2] & 0x80) > 0 ? tr("On") : tr("Off")) + "\n";
                 } else if ((packetInt[1] & 0xF0) == 0xA0) {
                     // Functions 8-12
                     return "Send packet immediate: Locomotive " + QString("%1").arg(address)
                            + " set" + " F09="
                            + ((packetInt[1] & 0x01) > 0 ? tr("On") : tr("Off"))
                            + ", F10="
                            + ((packetInt[1] & 0x02) > 0 ? tr("On") : tr("Off"))
                            + ", F11="
                            + ((packetInt[1] & 0x04) > 0 ? tr("On") : tr("Off"))
                            + ", F12="
                            + ((packetInt[1] & 0x08) > 0 ? tr("On") : tr("Off")) + "\n";
                 } else {
                     // Unknown
                     return generic /*+ jmri.NmraPacket.format(packet)*/ + "\n";
                 }
             } // else { // F9-F28 w/a short address.
         } else {
             /* Hmmmm... */
             forceHex = true;
             return "Undefined Send Packet Immediate, 3rd byte id 0x"
                    + QString("%1").arg(val7f,0,16) + " not 0x7f.\n";
         }
     } // case LnConstants::OPC_IMM_PACKET

     case RE_OPC_PR3_MODE: {
         /*
          * Sets the operating mode of the PR3 device, if present.
          *
          * Information reverse-engineered by B. Milhaupt and used with permission
          */

         if ((l.getElement(1) == 0x10) && ((l.getElement(2)&0x7c) == 0) &&
                 (l.getElement(3) == 0) && (l.getElement(4) == 0) ) {
             // set PR3 mode of operation, where LS 2 bits of byte 2 are encoded as:
             //	0x00	Set the PR3 mode to MS100 interface mode with PR3 Loconet termination disabled
             //  0x01	Set the PR3 to decoder programming track mode
             //  0x03	Set the PR3 to MS100 interface mode with PR3 Loconet termination enabled


             switch (l.getElement(2)&0x3) {
                 case 0x00: {
                     return "Set PR3 to MS100 mode without PR3 termination of LocoNet (i.e. use PR3 with command station present).\n";
                 }
                 case 0x01: {
                     return "Set PR3 to decoder programming track mode (i.e. no command station present).\n";
                 }
                 case 0x03: {
                     return "Set PR3 to MS100 mode with PR3 termination of LocoNet (i.e. use PR3 without command station present).\n";
                 }
                 default: {
                     return "Set PR3 to (not understood) mode.\n";
                 }
             }
         }
         else {
             forceHex = true;
             return "Unable to parse command.\n";
         }
     }

     default:
     forceHex = true;
     return "Unable to parse command.\n";

 } // end switch over opcode type - default handles unrecognized cases,
 // so can't reach here
} // end of protected String format(LocoNetMessage l)

/**
 * This function creates a string representation of a LocoNet buffer. The
 * string may be more than one line, and is terminated with a newline.
 *
 * @return The created string representation.
 */
QString LlnMon::displayMessage(LocoNetMessage l)
{

 forceHex = false;
 QString s = format(l);
 if (forceHex)
  s += "contents: " + l.toString() + "\n";
 if (showOpCode)
  s = LnConstants::OPC_NAME(l.getOpCode()) + ": " + s;
 return s;
} // end of public String displayMessage(LocoNetMessage l)

QString LlnMon::getDeviceNameFromIPLInfo(int manuf, int type)
{
 return(
            (manuf != LnConstants::RE_IPL_MFR_DIGITRAX)? "Unknown manufacturer "+QString("%1").arg(manuf)+", unknown device "+type :
                (type == LnConstants::RE_IPL_DIGITRAX_HOST_ALL) ? "Digitrax (no host device type specified)" :
                (type == LnConstants::RE_IPL_DIGITRAX_HOST_UT4) ? "Digitrax UT4(x) host" :
                (type == LnConstants::RE_IPL_DIGITRAX_HOST_UR92) ? "Digitrax UR92 host" :
                (type == LnConstants::RE_IPL_DIGITRAX_HOST_DT402) ? "Digitrax DT402(x) host" :
                (type == LnConstants::RE_IPL_DIGITRAX_HOST_DCS51) ? "Digitrax DCS51 host" :
                (type == LnConstants::RE_IPL_DIGITRAX_HOST_PR3) ? "Digitrax PR3 host" :
                "Digitrax (unknown host device type)");
} // end of public static String getDeviceNameFromIPLInfo

QString LlnMon::getSlaveNameFromIPLInfo(int manuf, int slaveNum)
{
 return(
            (manuf != LnConstants::RE_IPL_MFR_DIGITRAX)? "Unknown manufacturer "+QString("%1").arg(manuf)+", unknown device "+slaveNum :
                (slaveNum == LnConstants::RE_IPL_DIGITRAX_SLAVE_ALL) ? "Digitrax (no slave device type specified)" :
                (slaveNum == LnConstants::RE_IPL_DIGITRAX_SLAVE_RF24) ? "Digitrax RF24 slave" :
                "Digitrax (unknown slave device type)");
} // end of public static String getSlaveNameFromIPLInfo

//    private jmri.TurnoutManager turnoutManager;
//    private jmri.SensorManager sensorManager;
//    private jmri.ReporterManager reporterManager;

/**
* sets the loconet turnout manager which is used to find turnout "user names" from
* turnout "system names"
* @param loconetTurnoutManager
*/
/*public*/ void LlnMon::setLocoNetTurnoutManager (LnTurnoutManager* loconetTurnoutManager)
{
 turnoutManager = loconetTurnoutManager;
 qDebug() << QString("systemPrefix = %1").arg(turnoutManager->getSystemPrefix());
 locoNetTurnoutPrefix = turnoutManager->getSystemPrefix().mid(0,1).append( "T");
}

/**
* sets the loconet sensor manager which is used to find sensor "user names" from
* sensor "system names"
* @param loconetSensorManager
*/
/*public*/ void LlnMon::setLocoNetSensorManager (LnSensorManager* loconetSensorManager)
{
 sensorManager = loconetSensorManager;
 locoNetSensorPrefix = sensorManager->getSystemPrefix().mid(0,1) +"S";
}

/*public*/ void LlnMon::setLocoNetReporterManager (LnReporterManager* loconetReporterManager)
{
 reporterManager =  loconetReporterManager;
 locoNetReporterPrefix = reporterManager->getSystemPrefix().mid(0,1) + "R";
}
