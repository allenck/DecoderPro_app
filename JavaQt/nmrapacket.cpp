#include "nmrapacket.h"
#include "logger.h"
#include "loggerfactory.h"
#include "exceptions.h"
#include "stringutil.h"

/*static*/ /*final*/ /*public*/ int NmraPacket::NOADDRESS = 1;
/*static*/ /*final*/ /*public*/ int NmraPacket::LOCO_SHORT_ADDRESS = 2;
/*static*/ /*final*/ /*public*/ int NmraPacket::LOCO_LONG_ADDRESS = 4;
/*static*/ /*final*/ /*public*/ int NmraPacket::ACCESSORY_SHORT_ADDRESS = 8;

/*static*/ /*final*/ /*public*/ int NmraPacket::accIdLowLimit = 1;
    /*static*/ /*final*/ /*public*/ int NmraPacket::accIdHighLimit = 2044;
    /*static*/ /*final*/ /*public*/ int NmraPacket::accIdAltHighLimit = 2048;

//NmraPacket::NmraPacket()
//{
//}
/**
 * Utilities for coding/decoding NMRA S&RP DCC packets.
 *<P>
 * Packets are (now) represented by an array of bytes. Preamble/postamble
 * not included. Note that this is a data representation, _not_ a representation
 * of the waveform!  But this is a class, which might eventually also
 * form a representation object.
 *<P>
 * This is meant to be a general Java NMRA implementation, so does NOT use
 * JMRI utilities. In particular, it returns NULL instead of throwing JmriException
 * for invalid requests. Callers need to check upstream.
 *<P>
 * The function is provided by static member functions; objects of this
 * class should not be created.
 *<P>
 * Note that these functions are structured by packet type, not by what want to do.  E.g.
 * there are functions to create specific packet formats instead of a general "loco speed
 * packet" routine which figures out which type of packet to use.  Those decisions
 * are to be made somewhere else.
 * <P>
 * Range and value checking is intended to be aggressive; if we can check, we
 * should.  Problems are reported as warnings.
 *<P>
 * The basic function is to build a packet with proper addressing, etc:
 * <UL>
 * <li>oneBytePacket
 * <li>twoBytePacket
 * <li>threeBytePacket
 * <li>fourBytePacket
 * </ul>
 * On top of those are built various special-purpose packet formats.
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
 *
 * @author      Bob Jacobsen Copyright (C) 2001, 2003
 * @version     $Revision: 19981 $
 */
///*public*/ class NmraPacket {

/**
     * Create a packet containing a decoder idle instruction.
     *
     * @return the packet as a byte array or null if the address is not valid
     */
    //@CheckForNull
    /*public*/ /*static*/ QByteArray NmraPacket::idlePacket() {
        QByteArray retVal;
        retVal = QByteArray(3, 0);
        retVal.replace(0, (0xFF));  // address byte for decoder idle
        retVal.replace(1, (char)(0));     // decoder idle instruction
        retVal.replace(2, (0xFF));  // checksum byte
        return retVal;
    }

    /**
     * Create a packet containing a one-byte instruction.
     */
    /*public*/ /*static*/ QByteArray NmraPacket::oneBytePacket(int address, bool longAddr,
                            char arg1) {
        if (!addressCheck(address, longAddr)) {
            return NULL;  // failed!
        }

        // end sanity check, format output
        QByteArray retVal;
        if (longAddr) {
            // long address form
            retVal = QByteArray(4,0);
            retVal.replace(0, (192+((address/256)&0x3F)));
            retVal.replace(1, (address&0xFF));
            retVal.replace(2, arg1);
            retVal.replace(3, (retVal[0] ^ retVal[1] ^ retVal[2]));
            // short address form
            retVal = QByteArray(3,0);
            retVal.replace(0, (address&0xFF));
            retVal.replace(1, arg1);
            retVal.replace(2, (retVal[0] ^ retVal[1]));
        }
        return retVal;
    }

    /**
     * Create a packet containing a two-byte instruction.
     */
    /*public*/ /*static*/ QByteArray NmraPacket::twoBytePacket(int address, bool longAddr,
                            char arg1, char arg2) {
        if (!addressCheck(address, longAddr)) {
            return NULL;  // failed!
        }

        // end sanity check, format output
        QByteArray retVal;
        if (longAddr) {
            // long address form
            retVal = QByteArray(5,0);
            retVal.replace(0, (192+((address/256)&0x3F)));
            retVal.replace(1, (address&0xFF));
            retVal.replace(2, arg1);
            retVal.replace(3, arg2);
            retVal.replace(4, (retVal[0] ^ retVal[1] ^ retVal[2] ^ retVal[3]));
        } else {
            // short address form
            retVal = QByteArray(4,0);
            retVal.replace(0, (address&0xFF));
            retVal.replace(1, arg1);
            retVal.replace(2, arg2);
            retVal.replace(3, (retVal[0] ^ retVal[1] ^ retVal[2]));
        }
        return retVal;
    }

    /**
     * Create a packet containing a three-byte instruction.
     */
    /*public*/ /*static*/ QByteArray NmraPacket::threeBytePacket(int address, bool longAddr,
                            char arg1, char arg2, char arg3) {
        if (!addressCheck(address, longAddr)) {
            return NULL;  // failed!
        }

        // end sanity check, format output
        QByteArray retVal;
        if (longAddr) {
            // long address form
            retVal = QByteArray(6,0);
            retVal.replace(0, (192+((address/256)&0x3F)));
            retVal.replace(1, (address&0xFF));
            retVal.replace(2, arg1);
            retVal.replace(3, arg2);
            retVal.replace(4, arg3);
            retVal.replace(5, (retVal[0] ^ retVal[1] ^ retVal[2] ^ retVal[3] ^ retVal[4]));
        } else {
            // short address form
            retVal = QByteArray(5,0);
            retVal.replace(0, (address&0xFF));
            retVal.replace(1, arg1);
            retVal.replace(2, arg2);
            retVal.replace(3, arg3);
            retVal.replace(4, (retVal[0] ^ retVal[1] ^ retVal[2] ^ retVal[3]));
        }
        return retVal;
    }

    /**
     * Create a packet containing a four-byte instruction.
     */
    /*public*/ /*static*/ QByteArray NmraPacket::fourBytePacket(int address, bool longAddr,
                            char arg1, char arg2, char arg3, char arg4) {
        if (!addressCheck(address, longAddr)) {
            return NULL;  // failed!
        }

        // end sanity check, format output
        QByteArray retVal;
        if (longAddr) {
            // long address form
            retVal = QByteArray(7,0);
            retVal.replace(0, (192+((address/256)&0x3F)));
            retVal.replace(1, (address&0xFF));
            retVal.replace(2, arg1);
            retVal.replace(3, arg2);
            retVal.replace(4, arg3);
            retVal.replace(5, arg4);
            retVal.replace(6, (retVal[0] ^ retVal[1] ^ retVal[2] ^ retVal[3] ^ retVal[4] ^ retVal[5]));
        } else {
            // short address form
            retVal = QByteArray(6,0);
            retVal.replace(0, (address&0xFF));
            retVal.replace(1, arg1);
            retVal.replace(2, arg2);
            retVal.replace(3, arg3);
            retVal.replace(4, arg4);
            retVal.replace(5, (retVal[0] ^ retVal[1] ^ retVal[2] ^ retVal[3] ^ retVal[4]));
        }
        return retVal;
    }


    /*public*/ /*static*/ QByteArray NmraPacket::accDecoderPkt(int addr, int active, int outputChannel) {
    //Logger* log = new Logger("NmraPacket");
        // From the NMRA RP:
        // 0 10AAAAAA 0 1AAACDDD 0 EEEEEEEE 1
        // Accessory Digital Decoders can be designed to control momentary or
        // constant-on devices, the duration of time each output is active being controlled
        // by configuration variables CVs #515 through 518. Bit 3 of the second byte "C" is
        // used to activate or deactivate the addressed device. (Note if the duration the
        // device is intended to be on is less than or equal the set duration, no deactivation
        // is necessary.) Since most devices are paired, the convention is that bit "0" of
        // the second byte is used to distinguish between which of a pair of outputs the
        // accessory decoder is activating or deactivating. Bits 1 and 2 of byte two is used
        // to indicate which of 4 pairs of outputs the packet is controlling. The significant
        // bits of the 9 bit address are bits 4-6 of the second data byte. By convention
        // these three bits are in ones complement. The use of bit 7 of the second byte
        // is reserved for future use.

        // Note that A=1 is the first (lowest) valid address field, and the
        // largest is 512!  I don't know why this is, but it gets the
        // right hardware addresses

        if (addr < 1 || addr>511) {
            log->error("invalid address "+addr);
            return NULL;
        }
        if (active < 0 || active>1) {
            log->error("invalid active (C) bit "+addr);
            return NULL;
        }
        if (outputChannel < 0 || outputChannel>7) {
            log->error("invalid output channel "+addr);
            return NULL;
        }

        int lowAddr = addr & 0x3F;
        int highAddr = ( (~addr) >> 6) & 0x07;

        QByteArray retVal = QByteArray(3,0);

        retVal.replace(0, (0x80 | lowAddr));
        retVal.replace(1, (0x80 | (highAddr << 4 ) | ( active << 3) | outputChannel&0x07));
        retVal.replace(2, (retVal[0] ^ retVal[1]));

        return retVal;
    }

    /**
     * From the NMRA RP:
     * Basic Accessory Decoder Packet address for operations mode programming
     * 10AAAAAA 0 1AAACDDD 0 1110CCVV 0 VVVVVVVV 0 DDDDDDDD
     * Where DDD is used to indicate the output whose CVs are being modified and C=1.
     * If CDDD= 0000 then the CVs refer to the entire decoder. The resulting packet would be
     * {preamble} 10AAAAAA 0 1AAACDDD 0 (1110CCVV   0   VVVVVVVV   0   DDDDDDDD) 0 EEEEEEEE 1
     * Accessory Decoder Address   (Configuration Variable Access Instruction)     Error Byte
     */
     /*public*/ /*static*/ QByteArray NmraPacket::accDecoderPktOpsMode(int addr, int active, int outputChannel, int cvNum, int data) {

    Logger log("NmraPacket::accDecoderPktOpsMode");
        if (addr < 1 || addr>511) {
            Logger::error("invalid address "+addr);
            return NULL;
        }
        if (active < 0 || active>1) {
            Logger::error("invalid active (C) bit "+addr);
            return NULL;
        }
        if (outputChannel < 0 || outputChannel>7) {
            Logger::error("invalid output channel "+addr);
            return NULL;
        }

        if (cvNum < 1 || cvNum>1023) {
            Logger::error("invalid CV number "+cvNum);
            return NULL;
        }

        if (data<0 || data>255) {
            Logger::error("invalid data "+data);
            return NULL;
        }

        int lowAddr = addr & 0x3F;
        int highAddr = ( (~addr) >> 6) & 0x07;

        int lowCVnum = (cvNum-1) & 0xFF;
        int highCVnum = ((cvNum-1) >> 8) & 0x03;

        //QByteArray retVal = QByteArray(6];
        QByteArray retVal(6,0);
        retVal.replace(0, (0x80 | lowAddr));
        retVal.replace(1,(0x80 | (highAddr << 4 ) | ( active << 3) | outputChannel&0x07));
        retVal.replace(2,(0xEC | highCVnum));
        retVal.replace(3,(lowCVnum));
        retVal.replace(4, (0xFF & data));
        retVal.replace(5,  (retVal[0] ^ retVal[1] ^ retVal[2] ^ retVal[3] ^ retVal[4]));

        return retVal;
    }

     /**
      * From the NMRA RP:
      * The format for Accessory Decoder Configuration Variable Access Instructions is:
      * {preamble} 0 10AAAAAA 0 0AAA11VV 0 VVVVVVVV 0 DDDDDDDD 0 EEEEEEEE 1
      * Where:
      *  A = Decoder address bits
      *  V = Desired CV address - (CV 513 = 10 00000000)
      *  D = Data for CV
      *
      *  This is the old "legacy" format, newer decoders use the "Basic Accessory Decoder Packet"
      */
     /*public*/ /*static*/ QByteArray NmraPacket::accDecPktOpsModeLegacy(int addr, int cvNum, int data) {
    Logger log("NmraPacket::accDecPktOpsModeLegacy");
         if (addr < 1 || addr>511) {
             Logger::error("invalid address "+addr);
             return NULL;
         }

         if (cvNum < 1 || cvNum>1023) {
             Logger::error("invalid CV number "+cvNum);
             return NULL;
         }

         if (data<0 || data>255) {
             Logger::error("invalid data "+data);
             return NULL;
         }

         int lowAddr = addr & 0x3F;
         int highAddr = ( (~addr) >> 6) & 0x07;

         int lowCVnum = (cvNum-1) & 0xFF;
         int highCVnum = ((cvNum-1) >> 8) & 0x03;

         //QByteArray retVal = QByteArray(5];
         QByteArray retVal(5,0);
         retVal.replace (0, (0x80 | lowAddr));
         retVal.replace(1, (0x0C | (highAddr << 4 ) | highCVnum));
         retVal.replace(2, (lowCVnum));
         retVal.replace(3, (0xFF & data));
         retVal.replace(4, (retVal[0] ^ retVal[1] ^ retVal[2] ^ retVal[3]));

         return retVal;
     }

    /**
     * From the RP:
     * Extended Accessory Decoder Control Packet Format
     * The Extended Accessory Decoder Control Packet is included for the purpose
     *  of transmitting aspect control to signal decoders or data bytes to more
     *  complex accessory decoders. Each signal head can display one aspect at a time.
     *
     * {preamble} 0 10AAAAAA 0 0AAA0AA1 0 000XXXXX 0 EEEEEEEE 1
     *
     * XXXXX is for a single head. A value of 00000 for XXXXX indicates the absolute
     *  stop aspect. All other aspects represented by the values for XXXXX are
     *  determined by the signaling system used and the prototype being modeled.
     *
     * @param outputAddr Address of accessory output, starting with 1 and a maximum of 2044
     * @param aspect Aspect Number starting with 0 and a maximum of 31
     */
    /*public*/ /*static*/ QByteArray NmraPacket::accSignalDecoderPkt(int outputAddr, int aspect) {

      if (outputAddr < 1 || outputAddr>2044) {
          Logger::error("invalid address " + outputAddr);
          return NULL;
      }

      /*if (aspect < 0 || aspect >31) {
          Logger::error("invalid aspect "+aspect);
          return NULL;
      }*/

      outputAddr -= 1; // Make the address 0 based
      int lowAddr = (outputAddr & 0x03 ) ;  // Output Pair Address
      int boardAddr = (outputAddr >> 2) + 1 ; // Board Address

      return accSignalDecoderPktCommon(lowAddr, boardAddr, aspect);

    }

/**
 * Provide an extended operations mode accessory CV programming packet via a
 * simplified interface, given a signal address.
 * <br><br>
 * From the NMRA Standard: Extended Decoder Packet address for operations
 * mode programming
 * <br><br>
 * 10AAAAAA 0 0AAA0AA1
 * <br><br>
 * <br>
 * The resulting packet would be
 * <br><br>
 * {preamble} 10AAAAAA 0 0AAA0AA1 0 (1110CCVV 0 VVVVVVVV 0 DDDDDDDD) 0
 * EEEEEEEE 1
 *
 * @param addr  the signal address
 * @param cvNum the CV
 * @param data  the data
 * @return a packet
 */
/*public*/ /*static*/ QByteArray NmraPacket::accSignalDecoderPktOpsMode(int addr, int cvNum, int data) {

    if (addr < 1 || addr > 2044) {
        log->error("invalid address " + QString::number(addr));
        throw new IllegalArgumentException();
    }

    if (cvNum < 1 || cvNum > 1024) {
        log->error("invalid CV number " + QString::number(cvNum));
        return NULL;
    }

    if (data < 0 || data > 255) {
        log->error("invalid data " + QString::number(data));
        return NULL;
    }

    int outputAddr = addr - 1; // Make the address 0 based
    int lowAddr = (outputAddr & 0x03);
    int boardAddr = (outputAddr >> 2) + 1; // Board Address
    int midAddr = (boardAddr & 0x3F);
    int highAddr = (~(boardAddr >> 6)) & 0x07;

    int lowCVnum = (cvNum - 1) & 0xFF;
    int highCVnum = ((cvNum - 1) >> 8) & 0x03;

    QByteArray retVal = QByteArray(6,0);
    retVal[0] = (char) (0x80 | midAddr);
    retVal[1] = (char) (0x01 | (highAddr << 4) | (lowAddr << 1));
    retVal[2] = (char) (0xEC | highCVnum);
    retVal[3] = (char) (lowCVnum);
    retVal[4] = (char) (0xFF & data);
    retVal[5] = (char) (retVal[0] ^ retVal[1] ^ retVal[2] ^ retVal[3] ^ retVal[4]);

    return retVal;
}

/**
 * An alternative interpretation of RP-9.2.1 due to an omission in the address definition of extended accessory packets.
 * Since there is no such description for the address bits of the Extended Accessory Decoder Control Packet,
 * this interpretation assumes that the least significant bits of the extended packet type are still
 * in bits 1 and 2 of byte two, see Basic Accessory Packet.
 * @param outputAddr Address of accessory output, starting with 1 and a maximum of 2044
 * @param aspect Aspect Number starting with 0 and a maximum of 31
 */
/*public*/ /*static*/ QByteArray NmraPacket::altAccSignalDecoderPkt(int outputAddr, int aspect) {

    if (outputAddr < 1 || outputAddr>2048) {
        Logger::error("invalid address " + outputAddr);
        return NULL;
    }

    outputAddr -= 1; // Make the address 0 based
    int lowAddr = (outputAddr & 0x03 ) ;  // Output Pair Address
    int boardAddr = (outputAddr >> 2); // Board Address

    return accSignalDecoderPktCommon(lowAddr, boardAddr, aspect);
}
/**
 * Provide an extended operations mode accessory CV programming packet via a
 * simplified interface, given a signal address, using the alternative
 * interpretation of S-9.2.1, due to an omission in the address definition
 * of extended accessory packets.
 *
 * @param addr  the signal address
 * @param cvNum the CV
 * @param data  the data
 * @return a packet
 */
/*public*/ /*static*/ QByteArray NmraPacket::altAccSignalDecoderPktOpsMode(int addr, int cvNum, int data) {

    if (addr < 1 || addr > 2044) {
        log->error("invalid address " + QString::number(addr));
        throw new IllegalArgumentException();
    }

    if (cvNum < 1 || cvNum > 1024) {
        log->error("invalid CV number " + QString::number(cvNum));
        return NULL;
    }

    if (data < 0 || data > 255) {
        log->error("invalid data " + QString::number(data));
        return NULL;
    }

    int outputAddr = addr - 1; // Make the address 0 based
    int lowAddr = (outputAddr & 0x03);
    int boardAddr = (outputAddr >> 2); // Board Address
    int midAddr = (boardAddr & 0x3F);
    int highAddr = (~(boardAddr >> 6)) & 0x07;

    int lowCVnum = (cvNum - 1) & 0xFF;
    int highCVnum = ((cvNum - 1) >> 8) & 0x03;

    QByteArray retVal = QByteArray(6,0);
    retVal[0] = (char) (0x80 | midAddr);
    retVal[1] = (char) (0x01 | (highAddr << 4) | (lowAddr << 1));
    retVal[2] = (char) (0xEC | highCVnum);
    retVal[3] = (char) (lowCVnum);
    retVal[4] = (char) (0xFF & data);
    retVal[5] = (char) (retVal[0] ^ retVal[1] ^ retVal[2] ^ retVal[3] ^ retVal[4]);

    return retVal;
}

/*protected*/ /*static*/ QByteArray NmraPacket::accSignalDecoderPktCommon(int lowAddr, int boardAddr, int aspect)
{
 if (aspect < 0 || aspect >31)
 {
  Logger::error("invalid aspect "+aspect);
  return NULL;
 }

 int midAddr =  boardAddr & 0x3F ;
 int highAddr = ( (~boardAddr) >> 6) & 0x07;

 QByteArray retVal =  QByteArray(4,0);
 retVal.replace(0,  (0x80 | midAddr ) );
 retVal.replace(1,  (0x01 | (highAddr<<4) | (lowAddr << 1))) ;
 retVal.replace(2,  (0x1F & aspect));
 retVal.replace(3,  (retVal[0] ^ retVal[1] ^ retVal[2]));

 return retVal;
}



    /**
     * Provide an accessory control packet via a simplified interface
     * @param number Address of accessory output, starting with 1
     * @param closed true if the output is to be configured to the "closed", a.k.a. the
     * "normal" or "unset" position
     */

    /*public*/ /*static*/ QByteArray NmraPacket::accDecoderPkt(int number, bool closed) {
        // dBit is the "channel" info, least 7 bits, for the packet
        // The lowest channel bit represents CLOSED (1) and THROWN (0)
        int dBits = (( (number-1) & 0x03) << 1 );  // without the low CLOSED vs THROWN bit
        dBits = closed ? (dBits | 1) : dBits;

        // aBits is the "address" part of the nmra packet, which starts with 1
        // 07/01/05 R.Scheffler - Removed the mask, this will allow any 'too high' numbers
        // through to accDecoderPkt() above which will log the error if out of bounds. If we
        // mask it here, then the number will 'wrap' without any indication that it did so.
        int aBits = (number-1) >> 2;      // Divide by 4 to get the 'base'
        aBits += 1;                       // Base is +1

        // cBit is the control bit, we're always setting it active
        int cBit = 1;

        // get the packet
        return NmraPacket::accDecoderPkt(aBits, cBit, dBits);
    }

    /**
     * Provide an operation mode accessory control packet via a simplified interface
     * @param number Address of accessory, starting with 1
     * @param cvNum CV number to access
     * @param data Data to be written
     */
    /*public*/ /*static*/ QByteArray NmraPacket::accDecoderPktOpsMode(int number, int cvNum, int data) {
        // dBit is the "channel" info, least 7 bits, for the packet
        // The lowest channel bit represents CLOSED (1) and THROWN (0)
        int dBits = (( (number-1) & 0x03) << 1 );  // without the low CLOSED vs THROWN bit

        // aBits is the "address" part of the nmra packet, which starts with 1
        int aBits = (number-1) >> 2;      // Divide by 4 to get the 'base'
        aBits += 1;                       // Base is +1

        // cBit is the control bit, we're always setting it active
        int cBit = 1;

        // get the packet
        return NmraPacket::accDecoderPktOpsMode(aBits, cBit, dBits, cvNum, data);
    }
/**
 * Provide a basic operations mode accessory CV programming packet via a
 * simplified interface, given a decoder address.
 * <br><br>
 * From the NMRA Standard: Basic Accessory Decoder Packet address for
 * operations mode programming
 * <br><br>
 * 10AAAAAA 0 1AAACDDD
 * <br><br>
 * Where DDD is used to indicate the output whose CVs are being modified and
 * C=1.
 * <br>
 * If CDDD= 0000 then the CVs refer to the entire decoder.
 * <br><br>
 * Hence this method uses CDDD= 0000.
 * <br><br>
 * For programming individual outputs use
 * {@link #accDecoderPktOpsMode(int accAddr, int cvNum, int data)}
 * <br><br>
 *
 * @param decAddr Address of decoder, in the range 1 to 511
 * @param cvNum   CV number to access
 * @param data    Data to be written
 * @return a packet
 */
/*public*/ /*static*/ QByteArray NmraPacket::accDecPktOpsMode(int decAddr, int cvNum, int data) {
    // dBit is the "channel" info, least 7 bits, for the packet
    // The lowest channel bit represents CLOSED (1) and THROWN (0)
    int dBits = 0;  // dBits is the "channel" info, CDDD= 0000 indicates the entire decoder

    // aBits is the "address" part of the nmra packet, which starts with 1
    int aBits = decAddr;

    // cBit is the control bit, CDDD= 0000 indicates the entire decoder
    int cBit = 0;

    // get the packet
    return NmraPacket::accDecoderPktOpsMode(aBits, cBit, dBits, cvNum, data);
}

/**
 * Provide a legacy operation mode accessory control packet via a simplified interface
 * @param number Address of accessory, starting with 1
 * @param cvNum CV number to access
 * @param data Data to be written
 */
/*public*/ /*static*/ QByteArray NmraPacket::accDecoderPktOpsModeLegacy(int number, int cvNum, int data) {

    // aBits is the "address" part of the nmra packet, which starts with 1
    int aBits = (number-1) >> 2;      // Divide by 4 to get the 'base'
    aBits += 1;                       // Base is +1

    // get the packet
    return NmraPacket::accDecPktOpsModeLegacy(aBits, cvNum, data);
}

/*public*/ /*static*/ QByteArray NmraPacket::opsCvWriteByte(int address, bool longAddr, int cvNum, int data ) {
    if (log->isDebugEnabled()) log->debug("opswrite "+QString::number(address)+" "+QString::number(cvNum)+" "+QString::number(data));

    if (!addressCheck(address, longAddr)) {
        return NULL;  // failed!
    }

    if (data<0 || data>255) {
        Logger::error("invalid data "+data);
        return NULL;
    }
    if (cvNum<1 || cvNum>1024) {
        Logger::error("invalid CV number "+cvNum);
        return NULL;
    }

    // end sanity checks, format output
    QByteArray retVal;
    int arg1 = 0xEC + (((cvNum-1)>>8)&0x03);
    int arg2 = (cvNum-1)&0xFF;
    int arg3 = data&0xFF;

    return NmraPacket::threeBytePacket(address, longAddr, (char)arg1,  (char)arg2,  (char)arg3);
}

/*public*/ /*static*/ QByteArray NmraPacket::speedStep128Packet(int address, bool longAddr, int speed, bool fwd ) {
    if (log->isDebugEnabled()) log->debug("128 step packet "+QString::number(address)+" "+QString::number(speed));

    if (!addressCheck(address, longAddr)) {
        return NULL;  // failed!
    }

    if (speed<0 || speed>127) {
        Logger::error("invalid speed "+speed);
        return NULL;
    }

    // end sanity checks, format output
    QByteArray retVal;
    int arg1 = 0x3F;
    int arg2 = (speed&0x7F) | (fwd ? 0x80 : 0);

    if (longAddr) {
        // long address form
        retVal = QByteArray(5, 0);
        retVal.replace(0, (192+((address/256)&0x3F)));
        retVal.replace(1, (address&0xFF));
        retVal.replace(2, arg1);
        retVal.replace(3, arg2);
        retVal.replace(4, (retVal[0] ^ retVal[1] ^ retVal[2] ^ retVal[3]));
    } else {
        // short address form
        retVal = QByteArray(4,0);
        retVal.replace(0, (address&0xFF));
        retVal.replace(1, arg1);
        retVal.replace(2, arg2);
        retVal.replace(3, (retVal[0] ^ retVal[1] ^ retVal[2]));
    }
    return retVal;
}
#if 0
    /**
     * From NMRA RP 9.2.1
         * [A Crosland 05/02/12] There is an issue with this method in that it cannot
         * create a 28 step speed packet for maximum speed. Input speed value in the
         * range 0 - 28 is converted to speed steps, 0, estop, 1, 2, ..., 27.
         *
         * This method should probably be deprecated. It is used only by
         * NceThrottle.java and EasyDccThrottle.java which themselves have issues
         * in the way floating point speed values are converted to integer
         * speed steps.
         *
     * A speed and direction instruction is used send information to motors
     * connected to Multi Function Digital Decoders. Instruction "010" indicates
     * a Speed and Direction Instruction for reverse operation and instruction
     * "011" indicates a Speed and Direction Instruction for forward operation.
     * In these instructions the data is used to control speed with bits 0-3
     * being defined exactly as in S-9.2 Section B. If Bit 1 of CV#29 has a
     * value of one (1), then bit 4 is used as an intermediate speed step, as
     * defined in S-9.2, Section B. If Bit 1 of CV#29 has a value of zero (0),
     * then bit 4 shall 230 be used to control FL4. In this mode, Speed U0000 is
     * stop, speed U0001 is emergency stop, speed U0010 is the first speed step
     * and speed U1111 is full speed. This provides 14 discrete speed steps in
     * each direction.
     */
    /*public*/ static QByteArray speedStep28Packet(int address, bool longAddr, int speed, bool fwd ) {
        if (log->isDebugEnabled()) log->debug("28 step packet "+address+" "+speed);

        if (!addressCheck(address, longAddr)) {
            return NULL;  // failed!
        }

        if (speed<0 || speed>28) {
            Logger::error("invalid speed "+speed);
            return NULL;
        }
        int speedC = (speed&0x1F) >> 1;
        if (speed > 0)
            speedC = speedC +1;
        int c = (speed&0x01) << 4;	// intermediate speed step

        speedC = speedC + c;

        // end sanity checks, format output
        QByteArray retVal;
        int arg1 = (fwd ? 0x60 : 0x40)| speedC;

        if (longAddr) {
            // long address form
            retVal = QByteArray(4];
            retVal.replace(0, (192+((address/256)&0x3F));
            retVal.replace(1, (address&0xFF);
            retVal.replace(2, arg1;
            retVal.replace(3, (retVal.replace(0]^retVal.replace(1]^retVal.replace(2]^retVal.replace(3]);
        } else {
            // short address form
            retVal = QByteArray(3];
            retVal.replace(0, (address&0xFF);
            retVal.replace(1, arg1;
            retVal.replace(2, (retVal.replace(0]^retVal.replace(1]^retVal.replace(2]);
        }
        return retVal;
    }
#endif
    /**
     * New version of speedStep28Packet to allow access to the whole range of 28
     * step speed packets
     *
     * Simply constructs a packet using the 5 bit speed value. This is consistent
     * with the 128 and 14 step methods which do no further processing of the
     * speed value.
     *
     * @param full      must be true
     * @param address
     * @param longAddr
     * @param speed     speed step value 0 - 31 for insertion into DC packet
     * @param fwd
     */
    /*public*/ /*static*/ QByteArray NmraPacket::speedStep28Packet(bool full, int address, bool longAddr, int speed, bool fwd ) {
        if (log->isDebugEnabled()) log->debug("28 step packet "+QString::number(address)+" "+QString::number(speed));

        if (full != true) {
            Logger::error("invalid method invocation");
            return NULL;    // failed!
        }

        if (!addressCheck(address, longAddr)) {
            return NULL;  // failed!
        }

        if (speed<0 || speed>31) {
            Logger::error("invalid speed "+speed);
            return NULL;
        }
        int speedC = (speed&0x1F) >> 1;
        int c = (speed&0x01) << 4;	// intermediate speed step

        speedC = speedC + c;

        // end sanity checks, format output
       QByteArray retVal;
        int arg1 = (fwd ? 0x60 : 0x40)| speedC;

        if (longAddr) {
            // long address form
            retVal = QByteArray(4,0);
            retVal.replace(0, (192+((address/256)&0x3F)));
            retVal.replace(1, (address&0xFF));
            retVal.replace(2, arg1);
            retVal.replace(3, (retVal[0] ^ retVal[1] ^ retVal[2] ^ retVal[3]));
        } else {
            // short address form
            retVal = QByteArray(3,0);
            retVal.replace(0, (address&0xFF));
            retVal.replace(1, arg1);
            retVal.replace(2, (retVal[0] ^ retVal[1] ^ retVal[2]));
        }
        return retVal;
    }

#if 0
    /*public*/ static QByteArray speedStep14Packet(int address, bool longAddr,
            int speed, bool fwd, bool F0) {
        if (log->isDebugEnabled())
            log->debug("14 step packet " + address + " " + speed + " " + F0);

        if (speed < 0 || speed > 15) {
            Logger::error("invalid speed " + speed);
            return NULL;
        }

        int speedC = (speed&0xF);

        if (F0)
            speedC = speedC + 0x10;

        // end sanity checks, format output
        QByteArray retVal;
        int arg1 = (fwd ? 0x60 : 0x40)| speedC;

        if (longAddr) {
            // long address form
            retVal = QByteArray(4,0);
            retVal.replace(0, (192+((address/256)&0x3F)));
            retVal.replace(1, (address&0xFF));
            retVal.replace(2, arg1);
            retVal.replace(3, (retVal[0] ^ retVal[1] ^ retVal[2] ^ retVal[3]));
        } else {
            // short address form
            retVal = QByteArray(3,0);
            retVal.replace(0, (address&0xFF));
            retVal.replace(1, arg1);
            retVal.replace(2, (retVal[0] ^ retVal[1] ^ retVal[2]));
        }


        return retVal;
    }
#endif
    /*public*/ /*static*/ QByteArray NmraPacket::function0Through4Packet(int address, bool longAddr,
                        bool f0, bool f1, bool f2, bool f3, bool f4 ) {
        if (log->isDebugEnabled()) log->debug("f0 through f4 packet "+address);

        if (!addressCheck(address, longAddr)) {
            return NULL;  // failed!
        }

        // end sanity check, format output

        QByteArray retVal;
        int arg1 = 0x80 |
                    ( f0 ? 0x10 : 0) |
                    ( f1 ? 0x01 : 0) |
                    ( f2 ? 0x02 : 0) |
                    ( f3 ? 0x04 : 0) |
                    ( f4 ? 0x08 : 0);

        if (longAddr) {
            // long address form
            retVal = QByteArray(4,0);
            retVal.replace(0, (192+((address/256)&0x3F)));
            retVal.replace(1, (address&0xFF));
            retVal.replace(2, arg1);
            retVal.replace(3, (retVal[0] ^ retVal[1] ^ retVal[2]));
        } else {
            // short address form
            retVal = QByteArray(3,0);
            retVal.replace(0, (address&0xFF));
            retVal.replace(1, arg1);
            retVal.replace(2, (retVal[0] ^ retVal[1]));
        }
        return retVal;
    }

    /*public*/ /*static*/ QByteArray NmraPacket::function5Through8Packet(int address, bool longAddr,
                        bool f5, bool f6, bool f7, bool f8 ) {
        if (log->isDebugEnabled()) log->debug("f5 through f8 packet "+address);

        if (!addressCheck(address, longAddr)) {
            return NULL;  // failed!
        }

        // end sanity check, format output
        QByteArray retVal;
        int arg1 = 0xB0 |
                    ( f8 ? 0x08 : 0) |
                    ( f7 ? 0x04 : 0) |
                    ( f6 ? 0x02 : 0) |
                    ( f5 ? 0x01 : 0);

        if (longAddr) {
            // long address form
            retVal = QByteArray(4,0);
            retVal.replace(0, (192+((address/256)&0x3F)));
            retVal.replace(1, (address&0xFF));
            retVal.replace(2, arg1);
            retVal.replace(3, (retVal[0] ^ retVal[1] ^ retVal[2]));
        } else {
            // short address form
            retVal = QByteArray(3,0);
            retVal.replace(0, (address&0xFF));
            retVal.replace(1, arg1);
            retVal.replace(2, (retVal[0] ^ retVal[1]));
        }
        return retVal;
    }

/*public*/ /*static*/ QByteArray NmraPacket::function9Through12Packet(int address, bool longAddr, bool f9, bool f10, bool f11, bool f12 )
{
 Logger* log = new Logger("NmraPacket");
 if (log->isDebugEnabled()) log->debug("f9 through f12 packet "+address);

 if (!addressCheck(address, longAddr))
 {
  return NULL;  // failed!
 }

 // end sanity check, format output
 QByteArray retVal;
 int arg1 = 0xA0 |
                    ( f12 ? 0x08 : 0) |
                    ( f11 ? 0x04 : 0) |
                    ( f10 ? 0x02 : 0) |
                    ( f9  ? 0x01 : 0);

 if (longAddr)
 {
  // long address form
    //retVal = new QByteArray(4,0);
  QByteArray retVal(4,0);
    retVal.replace(0, (192+((address/256)&0x3F)));
    retVal.replace(1,(address&0xFF));
    retVal.replace(2,arg1);
    retVal.replace(3,(retVal[0] ^ retVal[1] ^ retVal[2]));
 }
 else
 {
  // short address form
  //retVal = new QByteArray(3,0);
  QByteArray retVal(3,0);
  retVal.replace(0, (address&0xFF));
  retVal.replace(1, arg1);
  retVal.replace(2, (retVal[0] ^ retVal[1]));
 }
 return retVal;
}

/*public*/ /*static*/ QByteArray NmraPacket::function13Through20Packet(int address, bool longAddr,
                    bool f13, bool f14, bool f15, bool f16,
                    bool f17, bool f18, bool f19, bool f20 )
{
    //if (log->isDebugEnabled()) log->debug("f13 through f20 packet "+address);

    if (!addressCheck(address, longAddr)) {
        return NULL;  // failed!
    }

    // end sanity check, format output
    QByteArray retVal;
    int arg1 = 0xDE;
    int arg2 =  ( f20 ? 0x80 : 0) |
                ( f19 ? 0x40 : 0) |
                ( f18 ? 0x20 : 0) |
                ( f17 ? 0x10 : 0) |
                ( f16 ? 0x08 : 0) |
                ( f15 ? 0x04 : 0) |
                ( f14 ? 0x02 : 0) |
                ( f13 ? 0x01 : 0);

    return NmraPacket::twoBytePacket(address, longAddr, (char) arg1,(char)arg2);
}

/*public*/ /*static*/ QByteArray NmraPacket::function21Through28Packet(int address, bool longAddr,
                        bool f21, bool f22, bool f23, bool f24,
                        bool f25, bool f26, bool f27, bool f28 )
{
 //if (log->isDebugEnabled()) log->debug("f21 through f28 packet "+address);

 if (!addressCheck(address, longAddr))
 {
  return NULL;  // failed!
 }

 // end sanity check, format output
 QByteArray retVal;
 int arg1 = 0xDF;
 int arg2 =  ( f28 ? 0x80 : 0) |
                    ( f27 ? 0x40 : 0) |
                    ( f26 ? 0x20 : 0) |
                    ( f25 ? 0x10 : 0) |
                    ( f24 ? 0x08 : 0) |
                    ( f23 ? 0x04 : 0) |
                    ( f22 ? 0x02 : 0) |
                    ( f21 ? 0x01 : 0);

return NmraPacket::twoBytePacket(address, longAddr, (char) arg1, (char) arg2);
}
#if 0
    /**
     * Provide an NMRA analog control instruction
     *<P>Note that the NMRA draft of Fall 2004 only defines the value
     * of "1" for the "function parameter", calling that the value for
     * "volume control".  However, DCC systems in the wild have been
     * observed to use 0x7F for the function byte for volume control.
     * @param address  DCC locomotive address
     * @param longAddr true if this is a long address, false if short address
     * @param function see note above
     * @param value  value to be sent in analog control instruction
     */
    /*public*/ static QByteArray  analogControl(int address, bool longAddr,
                                        int function, int value) {

        if (!addressCheck(address, longAddr)) {
            return NULL;  // failed!
        }

        // end sanity check, format output
        QByteArray retVal;
        int arg1 = 0x3D;  // analog instruction tag


        if (longAddr) {
            // long address form
            retVal = QByteArray(6];
            retVal.replace(0, (192+((address/256)&0x3F));
            retVal.replace(1, (address&0xFF);
            retVal.replace(2, arg1;
            retVal.replace(3, (function&0xFF);
            retVal.replace(4, (value&0xFF);
            retVal.replace(5, (retVal.replace(0]^retVal.replace(1]^retVal.replace(2]^retVal.replace(3]^retVal.replace(4]);
        } else {
            // short address form
            retVal = QByteArray(5];
            retVal.replace(0, (address&0xFF);
            retVal.replace(1, arg1;
            retVal.replace(2, (function&0xFF);
            retVal.replace(3, (value&0xFF);
            retVal.replace(4, (retVal.replace(0]^retVal.replace(1]^retVal.replace(2]^retVal.replace(3]);
        }
        return retVal;
    }
#endif
/**
 * Provide an NMRA consist control instruction
 * @param address  DCC locomotive address
 * @param longAddr true if this is a long address, false if short address
 * @param consist the consist address to set for this locomotive. Send
 * 00 as consist address if deleteing from consist.
 * @param directionNormal true if the normal direction of travel for this
 * address is the normal direction of travel for the consist.
 */
/*public*/ /*static*/ QByteArray  NmraPacket::consistControl(int address, bool longAddr,
                                    int consist, bool directionNormal) {

    if (!addressCheck(address, longAddr)) {
        return NULL;  // failed!
    } else if(!addressCheck(consist,false)) {
    return NULL;  // failed - Consist address is not a short address!
}

    // end sanity check, format output
    QByteArray retVal;
    int arg1 = 0x10;  // Consist Control instruction tag
if (directionNormal)
    arg1|=0x02;   // Forward Direction
else
    arg1|=0x03;   // Reverse Direction

    if (longAddr) {
        // long address form
        retVal = QByteArray(5,0);
        retVal.replace(0, (192+((address/256)&0x3F)));
        retVal.replace(1, (address&0xFF));
        retVal.replace(2, arg1);
        retVal.replace(3,(consist&0xFF));
        retVal.replace(4,(retVal[0] ^ retVal[1] ^ retVal[2] ^ retVal[3]));
    } else {
        // short address form
        retVal =QByteArray(4,0);
        retVal.replace(0, (address&0xFF));
        retVal.replace(1, arg1);
        retVal.replace(2, (consist&0xFF));
        retVal.replace(3,(retVal[0] ^ retVal[1] ^ retVal[2]));
    }
    return retVal;
}

/*static*/ bool NmraPacket::addressCheck(int address, bool longAddr) {
    if (address < 0 ) {  // zero is valid broadcast
        Logger::error("invalid address "+address);
        return false;
    }
    if (longAddr&& (address> (255+(231-192)*256)) ) {
        Logger::error("invalid address "+address);
        return false;
    }
    if (!longAddr&& (address> 127) ) {
        Logger::error("invalid address "+address);
        return false;
    }
    return true;  // passes test, hence OK
}

#if 0
    /**
     * Extract the address type from an NMRA packet.
     *<P>
     * This finds and returns the type of address within a specific
     * packet, e.g. "the stationary decoder space".
     */
    static int extractAddressType(QByteArray packet) {
        return 0;
    }

    /**
     * Extract the numerical address from an NMRA packet.
     *<P>
     * This finds and returns the numerical address within a specific
     * type, e.g. "first address within the stationary decoder space".
     */
    static int extractAddressNumber(QByteArray packet) {
        return 0;
    }

     /**
     * Extract the instruction from an NMRA packet
     *<P>
     * This finds and returns the instruction bits within a specific
     * type of packet/instruction, masking off the other bits.
     *
     */
    static int extractInstruction(QByteArray packet) {
        return 0;
    }
#endif
    /**
     * Convert NMRA packet to a readable form
     */
    /*static*/ /*public*/ QString NmraPacket::format(QByteArray p) {
        return StringUtil::hexStringFromBytes(p);
    }


/*static*/ Logger* NmraPacket::log = LoggerFactory::getLogger("NmraPacket");
//}


///* @(#)NmraPacket.java */

