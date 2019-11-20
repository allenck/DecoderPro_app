#include "lnsensoraddress.h"

/**
 * Utilities for handling LocoNet sensor addresses.
 * <P>
 * There are three addressing spaces for LocoNet sensors:
 * <UL>
 * <LI>The space used for DS54 inputs, where the least-significant-bit in the address
 * refers to the "Aux" and "Switch" inputs. These are represented by
 * system names of the form LSnnnA and LSnnnS respectively. nnn is
 * then the turnout number of the DS54 channel.
 * <LI>The space used for BDL16 inputs, where the card and section
 * numbers are part of the address.  These are represented by names of
 * the form LScccA1 through LScccA4, LScccB1 through LScccB4, and
 * on through LScccD4.  ccc is the BDL16 card number.
 * <LI>A straight-forward numeric space, represented by LSmmm. Note
 * that this is a 1-4096 scheme, not a 0-4095.
 * </UL>
 * <P>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project.  That permission
 * does not extend to uses in other software products.  If you wish to
 * use this code, algorithm or these message formats outside of JMRI, please
 * contact Digitrax Inc for separate permission.
 * <P>
 * @author	Bob Jacobsen Copyright (C) 2001, 2002
 * @version     $Revision: 17977 $
 */
//public class LnSensorAddress {


    LnSensorAddress::LnSensorAddress(int sw1, int sw2, QString prefix) {
        _as = sw2&0x20;		// should be a LocoNet constant?
        _high = sw2&0x0F;
        _low = sw1&0x7F;
        _valid = true;
        this->prefix = prefix;
    }

//    /**
//     * Old style ctor for e.g. CATS migration.
//     * Cannot handle multiple system connections.
//     * @deprecated 2.9.4
//     */
//    @Deprecated
//    public LnSensorAddress(int sw1, int sw2) {
//        this(sw1, sw2, "L");
//    }

//    /**
//     * Old style ctor for e.g. CATS migration.
//     * Cannot handle multiple system connections.
//     * @deprecated 2.9.4
//     */
//    @Deprecated
//    public LnSensorAddress(QString s) {
//        this(s, "L");  // assume one connection
//    }

    /*public*/  LnSensorAddress::LnSensorAddress(QString s, QString prefix) {
        _valid = false;
        this->prefix = prefix;

        // check valid
        if (s.startsWith(prefix+"S")) {
            // parse out and decode the name
            if (s.at(s.length()-1)=='A') {
                // DS54 addressing, Aux input
                _as = 0x20;
                //int n = Integer.parseInt(s.substring(prefix.length()+1, s.length()-1));
                int n = s.mid(prefix.length()+1, s.length()-prefix.length()-2).toInt();
                _high = n/128;
                _low = n&0x7F;
                _valid = true;
            } else if (s.at(s.length()-1)=='S') {
                // DS54 addressing, Switch input
                _as = 0x00;
                int n = s.mid(prefix.length()+1, s.length()-prefix.length()-2).toInt();
                _high = n/128;
                _low = n&0x7F;
                _valid = true;
            } else {
                // BDL16?
                char c = s.at(s.length()-2).toLatin1();
                if (c>='A' && c<='D') {
                    // BDL16 addressing
                    int d=0;
                    switch (c) {
                    case 'A': d = 0; break;
                        case 'B': d = 1; break;
                        case 'C': d = 2; break;
                        case 'D': d = 3; break;
                    }
                    QString s1 = s.mid(prefix.length()+1, s.length()-prefix.length()-3);
                    QString s2 = s.mid(s.length()-1, s.length());
                    int n = s.mid(prefix.length()+1, s.length()-prefix.length()-3).toInt()*16+d*4
                            +s.mid(s.length()-1, s.length()).toInt();
                    _high = n/128;
                    _low = (n&0x7F)/2;
                    _as = (n&0x01)*0x20;
                    _valid = true;
                } else {
                    // assume that its LSnnn style
                    int n = s.mid(prefix.length()+1, s.length()).toInt()-1;
                    _high = n/256;
                    _low = (n&0xFE)/2;
                    _as = (n&0x01)*0x20;
                    _valid = true;
                }
            }
        } else {
            // didn't find a leading LS, complain
            reportParseError(s);
        }
    }

    void LnSensorAddress::reportParseError(QString s) {
        log.error("Can't parse sensor address string: "+s);
    }

    /**
     * Update a LocoNet message to have this address.
     * @param m
     */
    /*public*/ void LnSensorAddress::insertAddress(LocoNetMessage* m) {
        m->setElement(1, getLowBits());
        m->setElement(2, getHighBits() | getASBit());
    }

    // convenient calculations
    /*public*/ bool LnSensorAddress::matchAddress(int a1, int a2) { // a1 is byte 1 of ln msg, a2 is byte 2
        if (getHighBits() != (a2&0x0f)) return false;
        if (getLowBits() != (a1&0x7f)) return false;
        if (getASBit() != (a2&0x20)) return false;
        return true;
    }

    /**
     * @return integer value of this address in 0-4095 space
     */
    /*protected*/ int LnSensorAddress::asInt() {
        return _high*256+_low*2+(_as!=0 ? 1 : 0);
    }

    // accessors for parsed data
    /*public*/ int LnSensorAddress::getLowBits() 	{ return _low; }
    /*public*/ int LnSensorAddress::getHighBits() 	{ return _high; }
    /**
     * The bit representing the Aux or Sensor input
     * @return 0x20 for aux input, 0x00 for switch input
     */
    /*public*/ int LnSensorAddress::getASBit() 		{ return _as; }

    /*public*/ bool LnSensorAddress::isValid()    { return _valid; }

    /*public*/ QString LnSensorAddress::toString() {
        return getNumericAddress()+":"
                +getDS54Address()+":"
                +getBDL16Address();
    }

 /**
  * Name in the 1-4096 space
  * @return LSnnn
  */
 /*public*/ QString LnSensorAddress::getNumericAddress()
 {
  return prefix.mid(0,1)+"S"+QString("%1").arg(asInt()+1);
 }

    /**
     * Name in the DS54 space
     * @return LSnnnA or LSnnnS, depending on Aux or Switch input
     */
    /*public*/ QString LnSensorAddress::getDS54Address() {
        if (_as != 0 )
            return prefix+"S"+QString("%1").arg(_high*128+_low)+"A";
        else
            return prefix+"S"+QString("%1").arg(_high*128+_low)+"S";
    }

    /**
     * Name in the BDL16 space
     * @return e.g. LSnnnA3, with nnn the BDL16 number,
     *              A the section number, and 3 the channel number
     */
    /*public*/ QString LnSensorAddress::getBDL16Address() {
        QString letter;
        QString digit;

        switch (asInt()&0x03) {
            case 0: digit = "0"; break;
            case 1: digit = "1"; break;
            case 2: digit = "2"; break;
            case 3: digit = "3"; break;
            default: digit = "X"; log.error("Unexpected digit value: "+asInt());
        }
        switch ( (asInt()&0x0C)/4 ) {
            case 0: letter = "A"; break;
            case 1: letter = "B"; break;
            case 2: letter = "C"; break;
            case 3: letter = "D"; break;
            default: letter = "X"; log.error("Unexpected letter value: "+asInt());
        }
        return prefix+"S"+QString("%1").arg(asInt()/16)+letter+digit;
    }

    //static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LnSensorAddress.class.getName());
