#include "identifydecoder.h"

IdentifyDecoder::IdentifyDecoder(Programmer* programmer, QObject *parent) :
    AbstractIdentify(programmer,parent)
{
 log = new Logger("IdentifyDecoder");
}
/**
 * Interact with a programmer to identify the DecoderIndexFile entry for a decoder
 * on the programming track.
 *
 * This is a class (instead of a Roster member function) to simplify use of
 * ProgListener callbacks.
 *
 * Once started, this maintains a List of possible RosterEntrys as
 * it works through the identification progress.
 *
 * Contains special case code for QSI (mfgID == 113),
 * TCS (mfgID == 153) and Zimo (mfgID == 145)
 *
 * @author    Bob Jacobsen   Copyright (C) 2001, 2010
 * @author    Howard G. Penny   Copyright (C) 2005
 * @version   $Revision: 17977 $
 * @see       jmri.jmrit.roster.RosterEntry
 * @see       jmri.jmrit.symbolicprog.CombinedLocoSelPane
 * @see       jmri.jmrit.symbolicprog.NewLocoSelPane
 */
// /*abstract*/ /*public*/ class IdentifyDecoder extends jmri.jmrit.AbstractIdentify {


    // steps of the identification state machine
/*public*/ bool IdentifyDecoder::test1() {
    // read cv8
    statusUpdate("Read MFG ID - CV 8");
    readCV("8");
    return false;
}

/*public*/ bool IdentifyDecoder::test2(int value) {
    mfgID = value;
    statusUpdate("Read MFG version - CV 7");
    readCV("7");
    return false;
}

/*public*/ bool IdentifyDecoder::test3(int value) {
 modelID = value;
 if (mfgID == 113) {  // QSI
     statusUpdate("Set PI for Read Product ID High Byte");
     writeCV("49", 254);
     return false;
 } else if (mfgID == 153) {  // TCS
     statusUpdate("Read decoder ID CV 249");
     readCV("249");
     return false;
 } else if (mfgID == 48) {  // Hornby
     statusUpdate("Read optional decoder ID CV 159");
     setOptionalCv(true);
     readCV("159");
     return false;
 } else if (mfgID == 145) {  // Zimo
     statusUpdate("Read decoder ID CV 250");
     readCV("250");
     return false;
 } else if (mfgID == 141 && (modelID == 70 || modelID == 71)) {  // SoundTraxx Econami and Tsunami2
     statusUpdate("Read productID high CV253");
     readCV("253");
     return false;
 } else if (mfgID == 98) {  // Harman
     statusUpdate("Read decoder ID high CV 112");
     readCV("112");
     return false;
 } else if (mfgID == 151 && modelID == 255) {  // ESU recent
     statusUpdate("Set PI for Read productID");
     writeCV("31", 0);
     return false;
 } else if (mfgID == 13) {  // DIY
     statusUpdate("Read decoder product ID #1 CV 47");
     readCV("47");
     return false;
 }
 return true;
}

/*public*/ bool IdentifyDecoder::test4(int value) {
 if (mfgID == 113) {  // QSI
     statusUpdate("Set SI for Read Product ID High Byte");
     writeCV("50", 4);
     return false;
 } else if (mfgID == 153) {  // TCS
     productID = value;
     return true;
 } else if (mfgID == 48) {  // Hornby
     if (isOptionalCv()) {
         return true;
     }
     if (value == 143) {
         productIDlow = value;
         statusUpdate("Read Product ID High Byte");
         readCV("158");
         return false;
     } else {
         productID = value;
         return true;
     }
 } else if (mfgID == 145) {  // Zimo
     productID = value;
     return true;
 } else if (mfgID == 141 && (modelID == 70 || modelID == 71)) {  // SoundTraxx
     productIDhigh = value;
     statusUpdate("Read decoder productID low CV256");
     readCV("256");
     return false;
 } else if (mfgID == 98) {  // Harman
     productIDhigh = value;
     statusUpdate("Read decoder ID low CV 113");
     readCV("113");
     return false;
 } else if (mfgID == 151) {  // ESU
     statusUpdate("Set SI for Read productID");
     writeCV("32", 255);
     return false;
 } else if (mfgID == 13) {  // DIY
     productIDhighest = value;
     statusUpdate("Read decoder product ID #2 CV 48");
     readCV("48");
     return false;
 }
 log->error(tr("unexpected step 4 reached with value: %1").arg(value));
 return true;
}

/*public*/ bool IdentifyDecoder::test5(int value) {
 if (mfgID == 113) {  // QSI
     statusUpdate("Read Product ID High Byte");
     readCV("56");
     return false;
 } else if (mfgID == 48) {  // Hornby
     productIDhigh = value;
     productID = (productIDhigh << 8) | productIDlow;
     return true;
 } else if (mfgID == 141 && (modelID == 70 || modelID == 71)) {  // SoundTraxx
     productIDlow = value;
     productID = (productIDhigh << 8) | productIDlow;
     return true;
 } else if (mfgID == 98) {  // Harman
     productIDlow = value;
     productID = (productIDhigh << 8) | productIDlow;
     return true;
 } else if (mfgID == 151) {  // ESU
     statusUpdate("Read productID Byte 1");
     readCV("261");
     return false;
 } else if (mfgID == 13) {  // DIY
     productIDhigh = value;
     statusUpdate("Read decoder product ID #3 CV 49");
     readCV("49");
     return false;
 }
 log->error(tr("unexpected step 5 reached with value: %1").arg(value));
 return true;
}

/*public*/ bool IdentifyDecoder::test6(int value) {
 if (mfgID == 113) {  // QSI
     productIDhigh = value;
     statusUpdate("Set SI for Read Product ID Low Byte");
     writeCV("50", 5);
     return false;
 } else if (mfgID == 151) {  // ESU
     productID = value;
     statusUpdate("Read productID Byte 2");
     readCV("262");
     return false;
 } else if (mfgID == 13) {  // DIY
     productIDlow = value;
     statusUpdate("Read decoder product ID #4 CV 50");
     readCV("50");
     return false;
 }
 log->error(tr("unexpected step 6 reached with value: %1").arg(value));
 return true;
}

/*public*/ bool IdentifyDecoder::test7(int value) {
 if (mfgID == 113) {  // QSI
     statusUpdate("Read Product ID Low Byte");
     readCV("56");
     return false;
 } else if (mfgID == 151) {  // ESU
     productID = productID + (value * 256);
     statusUpdate("Read productID Byte 3");
     readCV("263");
     return false;
 } else if (mfgID == 13) {  // DIY
     productIDlowest = value;
     productID = (((((productIDhighest << 8) | productIDhigh) << 8) | productIDlow) << 8) | productIDlowest;
     return true;
 }
 log->error(tr("unexpected step 7 reached with value: %1").arg(value));
 return true;
}

/*public*/ bool IdentifyDecoder::test8(int value) {
 if (mfgID == 113) {  // QSI
     productIDlow = value;
     productID = (productIDhigh * 256) + productIDlow;
     return true;
 } else if (mfgID == 151) {  // ESU
     productID = productID + (value * 256 * 256);
     statusUpdate("Read productID Byte 4");
     readCV("264");
     return false;
 }
 log->error(tr("unexpected step 8 reached with value: %1").arg(value));
 return true;
}

//@Override
/*public*/ bool IdentifyDecoder::test9(int value) {
    if (mfgID == 151) {  // ESU
        productID = productID + (value * 256 * 256 * 256);
        log->info("Decoder returns mfgID:" + QString::number(mfgID) + ";modelID:" + QString::number(modelID) + ";productID:" + QString::number(productID));
        return true;
    }
    log->error(tr("unexpected step 9 reached with value: %1").arg(value));
    return true;
}

/*protected*/ void IdentifyDecoder::statusUpdate(QString s)
{
 message(s);
 if (s == ("Done")) {
     done(mfgID, modelID, productID);
     log->info(tr("Decoder returns mfgID:%1;modelID:%2;productID:%3").arg(mfgID).arg(modelID).arg(productID));
 } else if (log->isDebugEnabled()) {
     log->debug(tr("received status: %1").arg(s));
 }
}

//abstract protected void done(int mfgID, int modelID, int productID);

//abstract protected void message(String m);
