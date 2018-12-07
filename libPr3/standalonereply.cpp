#include "standalonereply.h"
#include "rfid/rfidtrafficcontroller.h"
#include "rfid/rfidprotocol.h"
#include "rfid/rfidsystemconnectionmemo.h"

/**
 * Contains the data payload of a serial reply packet. Note that it's _only_ the
 * payload.
 *
 * @author Bob Jacobsen Copyright (C) 2002, 2006, 2007, 2008
 * @author Matthew Harris Copyright (C) 2011
 * @since 2.11.4
 */
///*public*/ class StandaloneReply extends RfidReply {


// create a new one
/*public*/ StandaloneReply::StandaloneReply(RfidTrafficController* tc, QObject *parent) : RfidReply(tc, parent){
    //super(tc);
    this->pr = this->tc->getAdapterMemo()->getProtocol();
    setBinary(true);
    setUnsolicited();
}

/*public*/ StandaloneReply::StandaloneReply(RfidTrafficController *tc, QString s, QObject* parent) : RfidReply(tc,s,parent) {
    //super(tc, s);
    this->pr = this->tc->getAdapterMemo()->getProtocol();
    setBinary(true);
    setUnsolicited();
}

/*public*/ StandaloneReply::StandaloneReply(RfidTrafficController* tc, RfidReply* l, QObject* parent) : RfidReply(tc, l, parent) {
    //super(tc, l);
    this->pr = this->tc->getAdapterMemo()->getProtocol();
    setBinary(true);
    setUnsolicited();
}

//@Override
/*public*/ QString StandaloneReply::toMonitorString() {
    return pr->toMonitorString(this);
}


