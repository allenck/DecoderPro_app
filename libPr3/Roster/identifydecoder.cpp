#include "identifydecoder.h"

IdentifyDecoder::IdentifyDecoder(QObject *parent) :
    AbstractIdentify(parent)
{
 mfgID = -1; 	// cv8
 modelID = -1;	// cv7
 productIDhigh = -1;
 productIDlow  = -1;
 productID  = -1;
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
    readCV(8);
    return false;
}

/*public*/ bool IdentifyDecoder::test2(int value) {
    mfgID = value;
    statusUpdate("Read MFG version - CV 7");
    readCV(7);
    return false;
}

/*public*/ bool IdentifyDecoder::test3(int value) {
    modelID = value;
    if (mfgID == 113) {  // QSI
        statusUpdate("Set PI for Read Product ID High Byte");
        writeCV(49, 254);
        return false;
    } else if (mfgID == 153) {  // TCS
        statusUpdate("Read decoder ID CV 249");
        readCV(249);
        return false;
    } else if (mfgID == 145) {  // Zimo
        statusUpdate("Read decoder ID CV 250");
        readCV(250);
        return false;
    }
    return true;
}

/*public*/ bool IdentifyDecoder::test4(int value) {
    if (mfgID == 113) {
        statusUpdate("Set SI for Read Product ID High Byte");
        writeCV(50, 4);
        return false;
    } else if (mfgID == 153) {
        productID = value;
        return true;
    } else if (mfgID == 145) {
        productID = value;
        return true;
    }
    log->error("unexpected step 4 reached with value: "+value);
    return true;
}

/*public*/ bool IdentifyDecoder::test5(int value) {
    if (mfgID == 113) {
        statusUpdate("Read Product ID High Byte");
        readCV(56);
        return false;
    }
    log->error("unexpected step 5 reached with value: "+value);
    return true;
}

/*public*/ bool IdentifyDecoder::test6(int value) {
    if (mfgID == 113) {
        productIDhigh = value;
        statusUpdate("Set SI for Read Product ID Low Byte");
        writeCV(50, 5);
        return false;
    }
    log->error("unexpected step 6 reached with value: "+value);
    return true;
}

/*public*/ bool IdentifyDecoder::test7(int value) {
    if (mfgID == 113) {
        statusUpdate("Read Product ID Low Byte");
        readCV(56);
        return false;
    }
    log->error("unexpected step 7 reached with value: "+value);
    return true;
}

/*public*/ bool IdentifyDecoder::test8(int value) {
    if (mfgID == 113) {
        productIDlow = value;
        productID = (productIDhigh * 256) + productIDlow;
        return true;
    }
    log->error("unexpected step 8 reached with value: "+value);
    return true;
}

/*protected*/ void IdentifyDecoder::statusUpdate(QString s)
{
 message(s);
 if (s==("Done")) done(mfgID, modelID, productID);
 else if (log->isDebugEnabled()) log->debug("received status: "+s);
}

//abstract protected void done(int mfgID, int modelID, int productID);

//abstract protected void message(String m);
