#include <QtCore>
#include "message.h"
#include "abstractmessage.h"
#include "abstractmrmessage.h"
#include "rfidmessage.h"


RfidMessage::RfidMessage(QObject *parent) :
    AbstractMRMessage(parent)
{
}

/**
 * Contains the data payload of a serial
 * packet.
 * <P>
 * The transmission protocol can come in one of several forms:
 * <ul>
 * <li>If the interlocked parameter is false (default),
 * the packet is just sent.  If the response length is not zero,
 * a reply of that length is expected.
 * <li>If the interlocked parameter is true, the transmission
 * will require a CRC interlock, which will be automatically added.
 * (Design note: this is done to make sure that the messages
 * remain atomic)
 * </ul>
 *
 * @author      Bob Jacobsen  Copyright (C) 2001,2003, 2006, 2007, 2008
 * @author      Matthew Harris  Copyright (C) 2011
 * @version     $Revision: 17977 $
 * @since       2.11.4
 */

//abstract /*public*/ class RfidMessage extends jmri.jmrix.AbstractMRMessage {
    // is this logically an abstract class?

/** Suppress the default ctor, as the
 * length must always be specified
 */
///*protected*/ RfidMessage() {}

/*public*/ RfidMessage::RfidMessage(int l, QObject *parent) : AbstractMRMessage(l, parent)
{
    //super(l);
    interlocked = false;
    responseLength = -1;  // -1 is an invalid value, indicating it hasn't been set

    setResponseLength(0);  // only polls require a response
    setBinary(true);
    setTimeout(5000);
}

/**
 * This ctor interprets the QString as the exact
 * sequence to send, byte-for-byte.
 * @param m
 */
/*public*/ RfidMessage::RfidMessage(QString m,int l, QObject *parent) : AbstractMRMessage(m, parent)
{
    //super(m);
    interlocked = false;
    responseLength = -1;  // -1 is an invalid value, indicating it hasn't been set
    setResponseLength(l);
    setBinary(true);
    setTimeout(5000);
}

/*public*/ void RfidMessage::setInterlocked(bool v) { interlocked = v; }
/*public*/ bool RfidMessage::getInterlocked() { return interlocked; }

/**
 * This ctor interprets the byte array as
 * a sequence of characters to send.
 * @param a Array of bytes to send
 */
/*public*/ RfidMessage::RfidMessage(QByteArray* a, int l, QObject *parent) : AbstractMRMessage(QString(*a), parent)
{
    //super(QString.valueOf(a));
    interlocked = false;
    responseLength = -1;  // -1 is an invalid value, indicating it hasn't been set
    setResponseLength(l);
    setBinary(true);
    setTimeout(5000);
}

/*public*/ /*final*/ void RfidMessage::setResponseLength(int l) { responseLength = l; }
/*public*/ int RfidMessage::getResponseLength() { return responseLength; }

/*abstract*/ /*public*/ QString toMonitorString();


