#include "rfidreply.h"
#include "rfidtrafficcontroller.h"

/**
 * Contains the data payload of a serial reply packet. Note that it's _only_ the
 * payload.
 *
 * @author	Bob Jacobsen Copyright (C) 2002, 2006, 2007, 2008
 * @author Matthew Harris Copyright (C) 2011
 * @since 2.11.4
 */
//abstract /*public*/ class RfidReply extends jmri.jmrix.AbstractMRReply {

    //@SuppressFBWarnings(value = "URF_UNREAD_FIELD", justification = "used by derived classes to fetch protocol in use")

// create a new one
/*public*/ RfidReply::RfidReply(RfidTrafficController* tc, QObject* parent) : AbstractMRReply(parent){
    //super();
    this->tc = tc;
    setBinary(true);
}

/*public*/ RfidReply::RfidReply(RfidTrafficController* tc, QString s, QObject* parent) : AbstractMRReply(s, parent){
    //super(s);
    this->tc = tc;
    setBinary(true);
}

/*public*/ RfidReply::RfidReply(RfidTrafficController* tc, RfidReply* l, QObject* parent) : AbstractMRReply(l,parent){
   // super(l);
    this->tc = tc;
    setBinary(true);
}

//@Override
/*protected*/ int RfidReply::skipPrefix(int index) {
    // doesn't have to do anything
    return index;
}


