#include "abstractmessage.h"
#include "abstractmrmessage.h"
#include "abstractmrtrafficcontroller.h"

//AbstractMRMessage::AbstractMRMessage(QObject *parent) :
//    AbstractMessage(parent)
//{
//}
/**
 * Abstract base class for messages in a message/reply protocol.
 *
 * Carries a sequence of characters, with accessors.
 *
 * @author	        Bob Jacobsen  Copyright (C) 2003
 * @version             $Revision: 17977 $
 */
//abstract /*public*/ class AbstractMRMessage extends AbstractMessage {

/*public*/ AbstractMRMessage::AbstractMRMessage(QObject *parent) : AbstractMessage(parent)
{
 mRetries=0; // number of retries, default = 0;

 setBinary(false);
 setNeededMode(AbstractMRTrafficController::NORMALMODE);
 setTimeout(SHORT_TIMEOUT);  // default value is the short timeout
 setRetries(0);  // Default to no retries
}

// create a new one
/*public*/  AbstractMRMessage::AbstractMRMessage(int i, QObject *parent) : AbstractMessage(parent)
{
 //this();
 mRetries=0; // number of retries, default = 0;
 if (i<1)
  log.error("invalid length in call to ctor");
 _nDataChars = i;
 _dataChars = new QByteArray[i];
}

// copy one
//@SuppressWarnings("NULL")
/*public*/  AbstractMRMessage::AbstractMRMessage(AbstractMRMessage* m, QObject *parent) : AbstractMessage(parent)
{
    //this();
    mRetries=0; // number of retries, default = 0;
    if (m == NULL)
        log.error("copy ctor of NULL message");
    _nDataChars = m->_nDataChars;
    _dataChars = new QByteArray[_nDataChars];
    for (int i = 0; i<_nDataChars; i++) _dataChars->replace(i,m->_dataChars->at(i));
    setTimeout(m->getTimeout());
    setRetries(m->getRetries());
    setNeededMode(m->getNeededMode());
}

// from QString
/*public*/ AbstractMRMessage::AbstractMRMessage(QString s, QObject *parent) : AbstractMessage(parent)
{
    //this(s.length());
    mRetries=0; // number of retries, default = 0;

    for (int i = 0; i<_nDataChars; i++)
        _dataChars->replace(i, s.mid(i));
}

/*public*/ void AbstractMRMessage::setOpCode(int i) { _dataChars->replace(0,i);}
/*public*/ int AbstractMRMessage::getOpCode() {return _dataChars->at(0);}
/*public*/ QString AbstractMRMessage::getOpCodeHex() { return QString("0x%1").arg(getOpCode(),0,16); }

// accessors to the bulk data
/*public*/ void AbstractMRMessage::setNeededMode(int pMode) {mNeededMode = pMode; }
/*public*/ int AbstractMRMessage::getNeededMode() { return mNeededMode; }

/**
 * Is a reply expected to this message?
 * <P>
 * By default, a reply is expected to every message;
 * either a reply or a timeout is needed before the next
 * message can be sent.
 * <p>
 * If this returns false, the transmit queue will
 * immediately go on to transmitt the next message (if any).
 */
/*public*/ bool AbstractMRMessage::replyExpected() { return true; }

// mode accessors
bool _isBinary;
/*public*/ bool AbstractMRMessage::isBinary() { return _isBinary; }
/*public*/ void AbstractMRMessage::setBinary(bool b) { _isBinary = b; }

/**
 * Minimum timeout that's acceptable.
 * <P>
 * Also used as default for normal operations.  Don't shorten
 * this "to make recovery faster", as sometimes <i>internal</i> delays
 * can slow processing down.
 * <P>
 * Units are milliseconds.
 */
/*public*/ void AbstractMRMessage::setTimeout(int t) { mTimeout = t; }
/*public*/ int AbstractMRMessage::getTimeout() { return mTimeout; }

/* For some systems, we want to retry sending a message if the port
   isn't ready for them. */
/*public*/ void AbstractMRMessage::setRetries(int i) { mRetries = i; }
/*public*/ int AbstractMRMessage::getRetries() { return mRetries; }

// display format

// contents (private)

/*public*/ void AbstractMRMessage::addIntAsThree(int val, int offset) {
    QString s = QString("%1").arg(val);
    if (s.length() != 3) s = "0"+s;  // handle <10
    if (s.length() != 3) s = "0"+s;  // handle <100
    QByteArray ba = s.toLatin1();
    setElement(offset,ba.at(0));
    setElement(offset+1,ba.at(1));
    setElement(offset+2,ba.at(2));
    return;
}

/*public*/ void AbstractMRMessage::addIntAsTwoHex(int val, int offset) {
    QString s = (QString("%1").arg(val,0,16)).toUpper();
    if (s.length() < 2) s = "0"+s;  // handle one digit
    if (s.length() > 2) log.error("can't add as two hex digits: "+s);
    QByteArray ba = s.toLatin1();
    setElement(offset,ba.at(0));
    setElement(offset+1,ba.at(1));
    return;
}

/*public*/ void AbstractMRMessage::addIntAsThreeHex(int val, int offset) {
    QString s = (QString("%1").arg(val,0,16)).toUpper();
    if (s.length() > 3) log.error("can't add as three hex digits: "+s);
    if (s.length() != 3) s = "0"+s;
    if (s.length() != 3) s = "0"+s;
    QByteArray ba = s.toLatin1();
    setElement(offset,ba.at(0));
    setElement(offset+1,ba.at(1));
    setElement(offset+2,ba.at(2));
    return;
}

/*public*/ void AbstractMRMessage::addIntAsFourHex(int val, int offset) {
    QString s = (QString("%1").arg(val,0,16)).toUpper();
    if (s.length() > 4) log.error("can't add as three hex digits: "+s);
    if (s.length() != 4) s = "0"+s;
    if (s.length() != 4) s = "0"+s;
    if (s.length() != 4) s = "0"+s;
    QByteArray ba = s.toLatin1();
    setElement(offset,ba.at(0));
    setElement(offset+1,ba.at(1));
    setElement(offset+2,ba.at(2));
    setElement(offset+3,ba.at(3));
    return;
}
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractMRMessage.class.getName());

/*public*/ QString AbstractMRMessage::toString()
{
 QString s = "";
 for (int i = 0; i < _nDataChars; i++)
 {
  if (_isBinary)
  {
   if (i != 0)
    s += " ";
   //s = QStringUtil.appendTwoHexFromInt(_dataChars[i] & 255, s);
   if(_dataChars->at(i) < 0x10) s.append("0");
   s.append(QString("%1").arg(_dataChars->at(i),0,16));
  }
  else
  {
   s += (char) _dataChars->at(i);
  }
 }
 return s;
}

