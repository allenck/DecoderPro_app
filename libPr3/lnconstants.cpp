#include "lnconstants.h"

LnConstants::LnConstants()
{
}
/* Note that the values in this class have been taken from the llnmom C program of
* Ron W. Auld, which included some work of John Kabat.  The symbol names
* are copied from the loconet.h file, CVS revision 1.1.1.1, program release 0.3.0  Those
* parts are (C) Copyright 2001 Ron W. Auld, and are used with direct
* permission of the copyright holder.
* <P>
* Most major comment blocks here are quotes from the Digitrax Loconet(r)
* OPCODE SUMMARY: found in the Loconet(r) Personal Edition 1.
* <P>
* Al Silverstein provided the reverse-engineering effort for the
* OPC_MULTI_SENSE message.
* <P>
* Some of the message formats used in this class are Copyright Digitrax, Inc.
* and used with permission as part of the JMRI project.  That permission
* does not extend to uses in other software products.  If you wish to
* use this code, algorithm or these message formats outside of JMRI, please
* contact Digitrax Inc for separate permission.
*/

/* various bit masks */
int LnConstants::DIRF_DIR          = 0x20;  /* direction bit    */
int LnConstants::DIRF_F0           = 0x10;  /* Function 0 bit   */
int LnConstants::DIRF_F4           = 0x08;  /* Function 1 bit   */
int LnConstants::DIRF_F3           = 0x04;  /* Function 2 bit   */
int LnConstants::DIRF_F2           = 0x02;  /* Function 3 bit   */
int LnConstants::DIRF_F1           = 0x01;  /* Function 4 bit   */
int LnConstants::SND_F8            = 0x08;  /* Sound 4/Function 8 bit */
int LnConstants::SND_F7            = 0x04;  /* Sound 3/Function 7 bit */
int LnConstants::SND_F6            = 0x02;  /* Sound 2/Function 6 bit */
int LnConstants::SND_F5            = 0x01;  /* Sound 1/Function 5 bit */

const int LnConstants::OPC_SW_ACK_CLOSED = 0x20;  /* command switch closed/open bit   */
const int LnConstants::OPC_SW_ACK_OUTPUT = 0x10;  /* command switch output on/off bit */

int LnConstants::OPC_INPUT_REP_CB  = 0x40;  /* control bit, reserved otherwise      */
int LnConstants::OPC_INPUT_REP_SW  = 0x20;  /* input is switch input, aux otherwise */
int LnConstants::OPC_INPUT_REP_HI  = 0x10;  /* input is HI, LO otherwise            */

int LnConstants::OPC_SW_REP_SW     = 0x20;  /* switch input, aux input otherwise    */
int LnConstants::OPC_SW_REP_HI     = 0x10;  /* input is HI, LO otherwise            */
//const int LnConstants::OPC_SW_REP_CLOSED = 0x20;  /* 'Closed' line is ON, OFF otherwise   */
//const int LnConstants::OPC_SW_REP_THROWN = 0x10;  /* 'Thrown' line is ON, OFF otherwise   */
int LnConstants::OPC_SW_REP_INPUTS = 0x40;  /* sensor inputs, outputs otherwise     */

int LnConstants::OPC_SW_REQ_DIR    = 0x20;  /* switch direction - closed/thrown     */
int LnConstants::OPC_SW_REQ_OUT    = 0x10;  /* output On/Off                        */

int LnConstants::OPC_LOCO_SPD_ESTOP = 0x01; /* emergency stop command               */

//const int LnConstants::OPC_MULTI_SENSE_MSG     = 0x60; // byte 1
//const int LnConstants::OPC_MULTI_SENSE_PRESENT = 0x20; // MSG field: transponder seen
//const int LnConstants::OPC_MULTI_SENSE_ABSENT  = 0x00; // MSG field: transponder lost
//const int LnConstants::OPC_MULTI_SENSE_POWER   = 0x60; // MSG field: Power message

/* protocol level */

    /** The protocol has not been established */
    /*public final static*/int LnConstants::LOCONETPROTOCOL_UNKNOWN = 0;
    /** Supports loconet 1.1 */
    /*public final static*/int LnConstants::LOCONETPROTOCOL_ONE = 1;
    /** Supports the protocol introduced to DCS240, DCS210 */
    /*public final static*/int LnConstants::LOCONETPROTOCOL_TWO = 2;
#if 0
    /* Expanded slot codes */
    /*public final static*/int LnConstants::OPC_EXP_REQ_SLOT = 0xbe;
    /*public final static*/int LnConstants::OPC_EXP_SLOT_MOVE = 0xd4;
    /*public final static*/int LnConstants::OPC_EXP_RD_SL_DATA = 0xe6;
    /*public final static*/int LnConstants::OPC_EXP_WR_SL_DATA = 0xee;
    /*public final static*/int LnConstants::OPC_EXP_SEND_SUB_CODE_MASK_SPEED = 0b11110000;
    /*public final static*/int LnConstants::OPC_EXP_SEND_SUB_CODE_MASK_FUNCTION = 0b11111000;
    /*public final static*/int LnConstants::OPC_EXP_SEND_FUNCTION_OR_SPEED_AND_DIR = 0xd5;
    /*public final static*/int LnConstants::OPC_EXP_SEND_SPEED_AND_DIR_MASK = 0b00010000;
    /*public final static*/int LnConstants::OPC_EXP_SEND_FUNCTION_GROUP_F0F6_MASK = 0b00010000;
    /*public final static*/int LnConstants::OPC_EXP_SEND_FUNCTION_GROUP_F7F13_MASK = 0b00011000;
    /*public final static*/int LnConstants::OPC_EXP_SEND_FUNCTION_GROUP_F14F20_MASK = 0b00100000;
    /*public final static*/int LnConstants::OPC_EXP_SEND_FUNCTION_GROUP_F21F28_F28OFF_MASK = 0b00101000;
    /*public final static*/int LnConstants::OPC_EXP_SEND_FUNCTION_GROUP_F21F28_F28ON_MASK =  0b00110000;
#endif
/* Slot Status byte definitions and macros */
/***********************************************************************************
*   D7-SL_SPURGE    ; 1=SLOT purge en,                                             *
*                   ; ALSO adrSEL (INTERNAL use only) (not seen on NET!)           *
*                                                                                  *
*   D6-SL_CONUP     ; CONDN/CONUP: bit encoding-Control double linked Consist List *
*                   ;    11=LOGICAL MID CONSIST , Linked up AND down               *
*                   ;    10=LOGICAL CONSIST TOP, Only linked downwards             *
*                   ;    01=LOGICAL CONSIST SUB-MEMBER, Only linked upwards        *
*                   ;    00=FREE locomotive, no CONSIST indirection/linking        *
*                   ; ALLOWS "CONSISTS of CONSISTS". Uplinked means that           *
*                   ; Slot SPD number is now SLOT adr of SPD/DIR and STATUS        *
*                   ; of consist. i.e. is ;an Indirect pointer. This Slot          *
*                   ; has same BUSY/ACTIVE bits as TOP of Consist. TOP is          *
*                   ; loco with SPD/DIR for whole consist. (top of list).          *
*                   ; BUSY/ACTIVE: bit encoding for SLOT activity                  *
*                                                                                  *
*   D5-SL_BUSY      ; 11=IN_USE loco adr in SLOT -REFRESHED                        *
*                                                                                  *
*   D4-SL_ACTIVE    ; 10=IDLE loco adr in SLOT -NOT refreshed                      *
*                   ; 01=COMMON loco adr IN SLOT -refreshed                        *
*                   ; 00=FREE SLOT, no valid DATA -not refreshed                   *
*                                                                                  *
*   D3-SL_CONDN     ; shows other SLOT Consist linked INTO this slot, see SL_CONUP *
*                                                                                  *
*   D2-SL_SPDEX     ; 3 BITS for Decoder TYPE encoding for this SLOT               *
*                                                                                  *
*   D1-SL_SPD14     ; 011=send 128 speed mode packets                              *
*                                                                                  *
*   D0-SL_SPD28     ; 010=14 step MODE                                             *
*                   ; 001=28 step. Generate Trinary packets for this               *
*                   ;              Mobile ADR                                      *
*                   ; 000=28 step. 3 BYTE PKT regular mode                         *
*                   ; 111=128 Step decoder, Allow Advanced DCC consisting          *
*                   ; 100=28 Step decoder ,Allow Advanced DCC consisting           *
***********************************************************************************/

//int LnConstants::STAT1_SL_SPURGE   = 0x80;  /* internal use only, not seen on net */
//int LnConstants::STAT1_SL_CONUP    = 0x40;  /* consist status                     */
//int LnConstants::STAT1_SL_BUSY     = 0x20;  /* used with STAT1_SL_ACTIVE,         */
//int LnConstants::STAT1_SL_ACTIVE   = 0x10;  /*                                    */
//int LnConstants::STAT1_SL_CONDN    = 0x08;  /*                                    */
//int LnConstants::STAT1_SL_SPDEX    = 0x04;  /*                                    */
//int LnConstants::STAT1_SL_SPD14    = 0x02;  /*                                    */
//int LnConstants::STAT1_SL_SPD28    = 0x01;  /*                                    */
//int LnConstants::STAT2_SL_SUPPRESS = 0x01;  /* 1 = Adv. Consisting supressed      */
//int LnConstants::STAT2_SL_NOT_ID   = 0x04;  /* 1 = ID1/ID2 is not ID usage        */
//int LnConstants::STAT2_SL_NOTENCOD = 0x08;  /* 1 = ID1/ID2 is not encoded alias   */
//int LnConstants::STAT2_ALIAS_MASK  = STAT2_SL_NOTENCOD | STAT2_SL_NOT_ID;
//int LnConstants::STAT2_ID_IS_ALIAS = STAT2_SL_NOT_ID;

/* mask and values for consist determination */
int LnConstants::CONSIST_MASK      = STAT1_SL_CONDN | STAT1_SL_CONUP;
//const int LnConstants::CONSIST_MID       = STAT1_SL_CONDN | STAT1_SL_CONUP;
//const int LnConstants::CONSIST_TOP       = STAT1_SL_CONDN;
//const int LnConstants::CONSIST_SUB       = STAT1_SL_CONUP;
//const int LnConstants::CONSIST_NO        = 0;
QString LnConstants::CONSIST_STAT(int s) {   // encode consisting status as a string
      return ((s & CONSIST_MASK) == CONSIST_MID) ? "Mid Consist" :
           ( ((s & CONSIST_MASK) == CONSIST_TOP) ? "Consist TOP" :
           ( ((s & CONSIST_MASK) == CONSIST_SUB) ? "Sub Consist" :
                       "Not Consisted"));
      }

/* mask and values for locomotive use determination */
int LnConstants::LOCOSTAT_MASK     = STAT1_SL_BUSY  | STAT1_SL_ACTIVE;
//const int LnConstants::LOCO_IN_USE       = STAT1_SL_BUSY  | STAT1_SL_ACTIVE;
//const int LnConstants::LOCO_IDLE         = STAT1_SL_BUSY;
//const int LnConstants::LOCO_COMMON       = STAT1_SL_ACTIVE;
//const int LnConstants::LOCO_FREE         = 0;
QString LnConstants::LOCO_STAT(int s)   { // encode loco status as a string
      return ((s & LOCOSTAT_MASK) == LOCO_IN_USE) ? "In-Use" :
           ( ((s & LOCOSTAT_MASK) == LOCO_IDLE)   ? "Idle" :
           ( ((s & LOCOSTAT_MASK) == LOCO_COMMON) ? "Common" :
                          "Free"));
      }

/* mask and values for decoder type encoding for this slot */
int LnConstants::DEC_MODE_MASK     = STAT1_SL_SPDEX | STAT1_SL_SPD14 | STAT1_SL_SPD28;
/* Advanced consisting allowed for the next two */
//int LnConstants::DEC_MODE_128A     = STAT1_SL_SPDEX | STAT1_SL_SPD14 | STAT1_SL_SPD28;
//int LnConstants::DEC_MODE_28A      = STAT1_SL_SPDEX ;
///* normal modes */
//int LnConstants::DEC_MODE_128      = STAT1_SL_SPD14 | STAT1_SL_SPD28;
//int LnConstants::DEC_MODE_14       = STAT1_SL_SPD14;
//int LnConstants::DEC_MODE_28TRI    = STAT1_SL_SPD28;
//int LnConstants::DEC_MODE_28       = 0;
QString LnConstants::DEC_MODE(int s) { // encode decoder type as a string
      return ((s & DEC_MODE_MASK) == DEC_MODE_128A)  ? "128 (Allow Adv. consisting)" :
           ( ((s & DEC_MODE_MASK) == DEC_MODE_28A)   ? "28 (Allow Adv. consisting)" :
           ( ((s & DEC_MODE_MASK) == DEC_MODE_128)   ? "128" :
           ( ((s & DEC_MODE_MASK) == DEC_MODE_14)    ? "14" :
           ( ((s & DEC_MODE_MASK) == DEC_MODE_28TRI) ? "28 (Motorola)" :
                          "28"))));
      }

/* values for track status encoding for this slot */
//int LnConstants::GTRK_PROG_BUSY    = 0x08;      /* 1 = programming track in this master is Busy         */
//int LnConstants::GTRK_MLOK1        = 0x04;      /* 0 = Master is DT200, 1=Master implements LocoNet 1.1 */
//int LnConstants::GTRK_IDLE         = 0x02;      /* 0=TRACK is PAUSED, B'cast EMERG STOP.                */
//int LnConstants::GTRK_POWER        = 0x01;      /* 1=DCC packets are ON in MASTER, Global POWER up      */
//int LnConstants::FC_SLOT           = 0x7b;      /* Fast clock is in this slot                           */
//int LnConstants::PRG_SLOT          = 0x7c;      /* This slot communicates with the programming track    */
//int LnConstants::CFG_SLOT          = 0x7f;      /* This slot holds configuration bits                   */

/* values and macros to decode programming messages */
//int LnConstants::PCMD_RW           = 0x40;      /* 1 = write, 0 = read                                  */
//int LnConstants::PCMD_BYTE_MODE    = 0x20;      /* 1 = byte operation, 0 = bit operation (if possible)  */
//int LnConstants::PCMD_TY1          = 0x10;      /* TY1 Programming type select bit                      */
//int LnConstants::PCMD_TY0          = 0x08;      /* TY0 Programming type select bit                      */
//int LnConstants::PCMD_OPS_MODE     = 0x04;      /* 1 = Ops mode, 0 = Service Mode                       */
//int LnConstants::PCMD_RSVRD1       = 0x02;      /* reserved                                             */
//int LnConstants::PCMD_RSVRD0       = 0x01;      /* reserved                                             */

/* programming mode mask */
int LnConstants::PCMD_MODE_MASK    = PCMD_BYTE_MODE | PCMD_OPS_MODE | PCMD_TY1 | PCMD_TY0;

/*
*  programming modes
*/
/* Paged mode  byte R/W on Service Track */
//int LnConstants::PAGED_ON_SRVC_TRK       = PCMD_BYTE_MODE;

///* Direct mode byte R/W on Service Track */
//int LnConstants::DIR_BYTE_ON_SRVC_TRK    = PCMD_BYTE_MODE | PCMD_TY0;

///* Direct mode bit  R/W on Service Track */
//int LnConstants::DIR_BIT_ON_SRVC_TRK     = PCMD_TY0;

///* Physical Register byte R/W on Service Track */
//int LnConstants::REG_BYTE_RW_ON_SRVC_TRK = PCMD_TY1;

///* Service Track Reserved function */
//int LnConstants::SRVC_TRK_RESERVED       = PCMD_TY1 | PCMD_TY0;

///* Ops mode byte program - no feedback */
//int LnConstants::OPS_BYTE_NO_FEEDBACK    = PCMD_BYTE_MODE | PCMD_OPS_MODE;

///* Ops mode byte program - feedback */
//int LnConstants::OPS_BYTE_FEEDBACK       = OPS_BYTE_NO_FEEDBACK | PCMD_TY0;

///* Ops mode bit program - no feedback */
//int LnConstants::OPS_BIT_NO_FEEDBACK     = PCMD_OPS_MODE;

///* Ops mode bit program - feedback */
//int LnConstants::OPS_BIT_FEEDBACK        = OPS_BIT_NO_FEEDBACK | PCMD_TY0;

/* Programmer Status error flags */
int LnConstants::PSTAT_USER_ABORTED  = 0x08;    /* User aborted this command */
int LnConstants::PSTAT_READ_FAIL     = 0x04;    /* Failed to detect Read Compare Acknowledge from decoder */
int LnConstants::PSTAT_WRITE_FAIL    = 0x02;    /* No Write acknowledge from decoder                      */
int LnConstants::PSTAT_NO_DECODER    = 0x01;    /* Service mode programming track empty                   */

/* bit masks for CVH */
int LnConstants::CVH_CV8_CV9         = 0x30;    /* mask for CV# bits 8 and 9    */
int LnConstants::CVH_CV7             = 0x01;    /* mask for CV# bit 7           */
int LnConstants::CVH_D7              = 0x02;    /* MSbit for data value         */

// The following two are commented out pending some decisions as to (a) whether
// they belong here or in the parser and (b) understanding what they say about
// a data format; note use of a pointer dereference

/* build data byte from programmer message */
//int PROG_DATA(ptr)      (((ptr->cvh & CVH_D7) << 6) | (ptr->data7 & 0x7f))

/* build CV # from programmer message */
//int PROG_CV_NUM(ptr)    (((((ptr->cvh & CVH_CV8_CV9) >> 3) | (ptr->cvh & CVH_CV7)) * 128) + (ptr->cvl & 0x7f))


// The struct typedefs here have been moved to individual classes as follows:
// Locomotive Address Message:   	LocoAdrMsg
// Switch with/without Acknowledge:	SwitchAckMsg, SwitchReqMsg
// Slot data request:				SlotReqMsg
// Move/Link Slot Message:			SlotMoveMsg, slotLinkMsg
// Consist Function Message:		ConsistFuncMsg
// Write slot status message:		SlotStatusMsg
// Long ACK message:				LongAckMsg
// Sensor input report:				InputRepMsg
// Turnout sensor state report:		SwRepMsg
// Request Switch function:			SwReqMsg
// Set slot sound functions:		LocoSndMsg
// Set slot direction and F0-F4 functions:	locoDirfMsg
// Set slot speed functions:		LocoSpdMsg
// Read/Write Slot data messages:	RwSlotDataMsg
// Fast Clock Message:				fastClockMsg
// Programmer Task Message (used in Start and Final Reply, both):	progTaskMsg;
// Peer-peer transfer message:		PeerXferMsg;
// send packet immediate message:	SendPktMsg;


/* loconet opcodes */
//int LnConstants::OPC_GPBUSY        = 0x81;
//int LnConstants::OPC_GPOFF         = 0x82;
//int LnConstants::OPC_GPON          = 0x83;
//int LnConstants::OPC_IDLE          = 0x85;
//int LnConstants::OPC_LOCO_SPD      = 0xa0;
//int LnConstants::OPC_LOCO_DIRF     = 0xa1;
//int LnConstants::OPC_LOCO_SND      = 0xa2;
//int LnConstants::OPC_SW_REQ        = 0xb0;
//int LnConstants::OPC_SW_REP        = 0xb1;
//int LnConstants::OPC_INPUT_REP     = 0xb2;
//int LnConstants::OPC_UNKNOWN       = 0xb3;
//int LnConstants::OPC_LONG_ACK      = 0xb4;
//int LnConstants::OPC_SLOT_STAT1    = 0xb5;
//int LnConstants::OPC_CONSIST_FUNC  = 0xb6;
//int LnConstants::OPC_UNLINK_SLOTS  = 0xb8;
//int LnConstants::OPC_LINK_SLOTS    = 0xb9;
//int LnConstants::OPC_MOVE_SLOTS    = 0xba;
//int LnConstants::OPC_RQ_SL_DATA    = 0xbb;
//int LnConstants::OPC_SW_STATE      = 0xbc;
//int LnConstants::OPC_SW_ACK        = 0xbd;
//int LnConstants::OPC_LOCO_ADR      = 0xbf;
//int LnConstants::OPC_MULTI_SENSE   = 0xd0; // Undocumented name
//int LnConstants::OPC_PANEL_RESPONSE= 0xd7; // Undocumented name
//int LnConstants::OPC_PANEL_QUERY   = 0xdf; // Undocumented name
//int LnConstants::OPC_LISSY_UPDATE  = 0xe4; // Undocumented name
//int LnConstants::OPC_PEER_XFER     = 0xe5;
//int LnConstants::OPC_ALM_READ      = 0xe6; // Undocumented name
//int LnConstants::OPC_SL_RD_DATA    = 0xe7;
//int LnConstants::OPC_IMM_PACKET    = 0xed;
//int LnConstants::OPC_IMM_PACKET_2  = 0xee;
//int LnConstants::OPC_WR_SL_DATA    = 0xef;
//int LnConstants::OPC_WR_SL_DATA_EXP = 0xee;
//int LnConstants::OPC_ALM_WRITE     = 0xee; // Undocumented name
//int LnConstants::OPC_MASK          = 0x7f;  /* mask for acknowledge opcodes */
QString LnConstants::OPC_NAME(int opcode) { // encode LocoNet Opcode as a string
      return   (opcode == OPC_GPBUSY)      ? "OPC_GPBUSY" :
               (opcode == OPC_GPOFF)       ? "OPC_GPOFF" :
               (opcode == OPC_GPON)        ? "OPC_GPON"  :
           (opcode == OPC_IDLE)        ? "OPC_IDLE"  :
       (opcode == OPC_LOCO_SPD)    ? "OPC_LOCO_SPD"  :
       (opcode == OPC_LOCO_DIRF)   ? "OPC_LOCO_DIRF"  :
       (opcode == OPC_LOCO_SND)    ? "OPC_LOCO_SND"  :
       (opcode == OPC_SW_REQ)      ? "OPC_SW_REQ"  :
       (opcode == OPC_SW_REP)      ? "OPC_SW_REP"  :
       (opcode == OPC_INPUT_REP)   ? "OPC_INPUT_REP"  :
       (opcode == OPC_UNKNOWN)     ? "OPC_UNKNOWN"  :
       (opcode == OPC_LONG_ACK)    ? "OPC_LONG_ACK"  :
       (opcode == OPC_SLOT_STAT1)  ? "OPC_SLOT_STAT1"  :
       (opcode == OPC_CONSIST_FUNC)? "OPC_CONSIST_FUNC"  :
       (opcode == OPC_UNLINK_SLOTS)? "OPC_UNLINK_SLOTS"  :
       (opcode == OPC_LINK_SLOTS)  ? "OPC_LINK_SLOTS"  :
       (opcode == OPC_MOVE_SLOTS)  ? "OPC_MOVE_SLOTS"  :
       (opcode == OPC_RQ_SL_DATA)  ? "OPC_RQ_SL_DATA"  :
       (opcode == OPC_SW_STATE)    ? "OPC_SW_STATE"  :
       (opcode == OPC_SW_ACK)      ? "OPC_SW_ACK"  :
       (opcode == OPC_LOCO_ADR)    ? "OPC_LOCO_ADR"  :
       (opcode == OPC_MULTI_SENSE) ? "OPC_MULTI_SENSE"  :
       (opcode == OPC_PANEL_QUERY) ? "OPC_PANEL_QUERY"  :
       (opcode == OPC_PANEL_RESPONSE) ? "OPC_PANEL_RESPONSE"  :
       (opcode == OPC_LISSY_UPDATE) ? "OPC_LISSY_UPDATE" :
       (opcode == OPC_PEER_XFER)   ? "OPC_PEER_XFER"  :
       (opcode == OPC_ALM_READ)    ? "OPC_ALM_READ"  :
       (opcode == OPC_SL_RD_DATA)  ? "OPC_SL_RD_DATA"  :
       (opcode == OPC_IMM_PACKET)  ? "OPC_IMM_PACKET"  :
       (opcode == OPC_IMM_PACKET_2)? "OPC_IMM_PACKET_2"  :
       (opcode == OPC_WR_SL_DATA)  ? "OPC_WR_SL_DATA"  :
       (opcode == OPC_WR_SL_DATA_EXP)	? "OPC_WR_SL_DATA_EXP"  :
       (opcode == OPC_ALM_WRITE)   ? "OPC_ALM_WRITE"  :

                          "<unknown>";
      }

// start of values not from llnmon.c
/*public*/ /*final*/ /*static*/ int LnConstants::METER_INTERVAL_MS = 30000;


// Expanded slot index values
int LnConstants::EXP_MAST            = 0;
int LnConstants::EXP_SLOT            = 0x01;
int LnConstants::EXPD_LENGTH         = 16;

//offsets into message
int LnConstants::EXPD_STAT           = 0;
int LnConstants::EXPD_ADRL           = 1;
int LnConstants::EXPD_ADRH           = 2;
int LnConstants::EXPD_FLAGS          = 3;
int LnConstants::EXPD_SPD            = 4;
int LnConstants::EXPD_F28F20F12      = 5;
int LnConstants::EXPD_DIR_F0F4_F1    = 6;
int LnConstants::EXPD_F11_F5         = 7;
int LnConstants::EXPD_F19_F13        = 8;
int LnConstants::EXPD_F27_F21        = 9;

//  opcode keys used to express interest in various messages
//            note these are _not_ the loconet opcode values!

int LnConstants::KEY_GPBUSY 			= 1<<  0;
int LnConstants::KEY_GPOFF 			= 1<<  1;
int LnConstants::KEY_GPON 			= 1<<  2;
int LnConstants::KEY_IDLE  			= 1<<  3;

int LnConstants::KEY_LOCO_SPD		= 1<<  4;
int LnConstants::KEY_LOCO_DIRF		= 1<<  5;
int LnConstants::KEY_LOCO_SND		= 1<<  6;
int LnConstants::KEY_SW_REQ			= 1<<  7;

int LnConstants::KEY_SW_REP			= 1<<  8;
int LnConstants::KEY_INPUT_REP		= 1<<  9;
int LnConstants::KEY_LONG_ACK		= 1<< 10;
int LnConstants::KEY_SLOT_STAT1		= 1<< 11;

int LnConstants::KEY_CONSIST_FUNC	= 1<< 12;
int LnConstants::KEY_UNLINK_SLOTS	= 1<< 13;
int LnConstants::KEY_LINK_SLOTS		= 1<< 14;
int LnConstants::KEY_MOVE_SLOTS		= 1<< 15;

int LnConstants::KEY_RQ_SL_DATA		= 1<< 16;
int LnConstants::KEY_SW_STATE		= 1<< 17;
int LnConstants::KEY_SW_ACK			= 1<< 18;
int LnConstants::KEY_LOCO_ADR		= 1<< 19;

int LnConstants::KEY_PEER_XFR		= 1<< 20;
int LnConstants::KEY_IMM_PACKET		= 1<< 21;
int LnConstants::KEY_WR_SL_DATA		= 1<< 22;

// reverse-engineered constants
//int LnConstants::RE_IPL_MFR_DIGITRAX            = 0x00;
//int LnConstants::RE_IPL_MFR_ALL                 = 0x00;
//int LnConstants::RE_IPL_DIGITRAX_HOST_LNRP      = 0x01;
//int LnConstants::RE_IPL_DIGITRAX_HOST_UT4       = 0x04;
//int LnConstants::RE_IPL_DIGITRAX_HOST_WTL12     = 0x0c;
//int LnConstants::RE_IPL_DIGITRAX_HOST_DB210OPTO = 0x14;
//int LnConstants::RE_IPL_DIGITRAX_HOST_DB210     = 0x15;
//int LnConstants::RE_IPL_DIGITRAX_HOST_DB220     = 0x16;
//int LnConstants::RE_IPL_DIGITRAX_HOST_DCS210    = 0x1b;
//int LnConstants::RE_IPL_DIGITRAX_HOST_DCS240    = 0x1c;
//int LnConstants::RE_IPL_DIGITRAX_HOST_UR92      = 0x5C;
//int LnConstants::RE_IPL_DIGITRAX_HOST_DCS51     = 0x33;
//int LnConstants::RE_IPL_DIGITRAX_HOST_DT402     = 0x2A;
//int LnConstants::RE_IPL_DIGITRAX_HOST_DT500     = 0x32;
//int LnConstants::RE_IPL_DIGITRAX_HOST_PR3       = 0x23;
//int LnConstants::RE_IPL_DIGITRAX_HOST_PR4       = 0x24;
//int LnConstants::RE_IPL_DIGITRAX_HOST_BXP88     = 0x58;
//int LnConstants::RE_IPL_DIGITRAX_HOST_LNWI      = 0x63;
//int LnConstants::RE_IPL_DIGITRAX_HOST_ALL       = 0x00;
//int LnConstants::RE_IPL_DIGITRAX_SLAVE_RF24     = 0x18;
//int LnConstants::RE_IPL_DIGITRAX_SLAVE_ALL      = 0x00;
//int LnConstants::RE_IPL_PING_OPERATION          = 0x08;
//int LnConstants::RE_IPL_IDENTITY_OPERATION      = 0x0f;

const int LnConstants::RE_LACK_SPEC_CASE1             = 0x50; // special case LACK response for OpSw accesses
int LnConstants::RE_LACK_SPEC_CASE2             = 0x00; // special case LACK response for OpSw accesses
//int LnConstants::RE_OPC_PR3_MODE                = 0xD3;
//const int LnConstants::RE_MULTI_SENSE_DEV_TYPE_PM4X   = 0x00;
//int LnConstants::RE_MULTI_SENSE_DEV_TYPE_BDL16X = 0x01;
//int LnConstants::RE_MULTI_SENSE_DEV_TYPE_SE8    = 0x02;
//int LnConstants::RE_MULTI_SENSE_DEV_TYPE_DS64   = 0x03;

// Below data is assumed, based on firmware files available from RR-Cirkits web site
//int LnConstants::RE_IPL_MFR_RR_CIRKITS          = 87;
//int LnConstants::RE_IPL_RRCIRKITS_HOST_TC64     = 11;
//int LnConstants::RE_IPL_RRCIRKITS_SLAVE_ALL     = 00;

// Constants associated with OPC_PEER_XFR for Duplex operations
//int LnConstants::RE_DPLX_OP_TYPE_WRITE              = 0x00;
//int LnConstants::RE_DPLX_OP_TYPE_QUERY              = 0x08;
//int LnConstants::RE_DPLX_OP_TYPE_REPORT             = 0x10;
//int LnConstants::RE_DPLX_OP_LEN                     = 0x14;
//int LnConstants::RE_IPL_OP_LEN                      = 0x14;
//int LnConstants::RE_IPL_OP_QUERY                    = 0x08;
//int LnConstants::RE_IPL_OP_REPORT                   = 0x10;
//int LnConstants::RE_IPL_OP_SLV_QUERY                = 0x00;
//int LnConstants::RE_IPL_OP_HFW_QUERY                = 0x00;
//int LnConstants::RE_IPL_OP_HSNM_QUERY               = 0x00;
//int LnConstants::RE_IPL_OP_SFW_QUERY                = 0x00;
//int LnConstants::RE_IPL_OP_HSN0_QUERY               = 0x01;
//int LnConstants::RE_IPL_OP_HSN1_QUERY               = 0x00;
//int LnConstants::RE_IPL_OP_HSN2_QUERY               = 0x00;
//int LnConstants::RE_IPL_OP_SSNM_QUERY               = 0x00;
//int LnConstants::RE_IPL__OP_SSN0_QUERY              = 0x00;
//int LnConstants::RE_IPL_OP_SSN1_QUERY               = 0x00;
//int LnConstants::RE_IPL_OP_SSN2_QUERY               = 0x00;
//int LnConstants::RE_IPL_OP_SSN3_QUERY               = 0x00;
//int LnConstants::RE_DPLX_GP_CHAN_TYPE               = 2;
//int LnConstants::RE_DPLX_GP_NAME_TYPE               = 3;
//int LnConstants::RE_DPLX_GP_ID_TYPE                 = 4;
//int LnConstants::RE_DPLX_GP_PW_TYPE                 = 7;
//int LnConstants::RE_DPLX_OPC_BAD                    = 0x80;
//int LnConstants::RE_DPLX_MSB1_BIT                   = 1;
//int LnConstants::RE_DPLX_MSB2_BIT                   = 2;
//int LnConstants::RE_DPLX_MSB3_BIT                   = 4;
//int LnConstants::RE_DPLX_MSB4_BIT                   = 8;
//int LnConstants::RE_DPLX_BUMP_MSB1_BIT              = 7;
//int LnConstants::RE_DPLX_BUMP_MSB2_BIT              = 6;
//int LnConstants::RE_DPLX_BUMP_MSB3_BIT              = 5;
//int LnConstants::RE_DPLX_BUMP_MSB4_BIT              = 4;
//int LnConstants::RE_DPLX_7BITS_MAX                  = 127;
//int LnConstants::RE_DPLX_MAX_NOT_OPC                = 0x7F;
//int LnConstants::RE_DPLX_ALT_CH_MSB_BIT             = 0x4;
//int LnConstants::RE_DPLX_ALT_CH_MSB_SHIFT           = 0x5;
//int LnConstants::RE_DPLX_ALT_ID_MSB_BIT             = 0x8;
//int LnConstants::RE_DPLX_ALT_ID_MSB_SHIFT           = 0x4;
//int LnConstants::RE_DPLX_ALT_PW1_MSB_BIT            = 0x1;
//int LnConstants::RE_DPLX_ALT_PW1_MSB_SHIFT          = 0x3;
//int LnConstants::RE_DPLX_ALT_PW3_MSB_BIT            = 0x2;
//int LnConstants::RE_DPLX_ALT_PW3_MSB_SHIFT          = 0x2;

//int LnConstants::RE_DPLX_DATA_LS_NIBBLE             = 0x0F;
//int LnConstants::RE_DPLX_DATA_MS_NIBBLE             = 0x70;
//int LnConstants::RE_DPLX_DATA_MS_NIBBLE_SHIFT       = 4;

// Duplex Group Scan Operation Constants
int LnConstants::RE_DPLX_SCAN_OP_LEN                = 0x14 ;
int LnConstants::RE_DPLX_SCAN_QUERY_B2              = 0x10 ;
int LnConstants::RE_DPLX_SCAN_QUERY_B3              = 0x08 ;
int LnConstants::RE_DPLX_SCAN_QUERY_B4              = 0x00 ;
int LnConstants::RE_DPLX_SCAN_REPORT_B2             = 0x10 ;
int LnConstants::RE_DPLX_SCAN_REPORT_B3             = 0x10 ;

/*public*/ /*final*/ /*static*/ QString LnConstants::DIGITRAX_STRING = "Digitrax"; // NOI18N
/*public*/ /*final*/ /*static*/ QString LnConstants::RR_CIRKITS_STRING = "RR-CirKits"; // NOI18N};
