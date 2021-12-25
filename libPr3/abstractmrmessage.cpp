#include "abstractmrmessage.h"
#include "exceptions.h"
#include "loggerfactory.h"
#include "stringutil.h"
#include "abstractmrtrafficcontroller.h"

/**
 * Abstract base class for messages in a message/reply protocol.
 * <p>
 * Carries a sequence of characters, with accessors.
 *
 * @author Bob Jacobsen Copyright (C) 2003
 */
///*abstract*/ /*public*/ class AbstractMRMessage extends AbstractMessage {

/*public*/ AbstractMRMessage::AbstractMRMessage(QObject* parent) : AbstractMessage(parent){
common();
}

void AbstractMRMessage::common()
{
 mRetries = 0; // number of retries, default = 0;
    setBinary(false);
    setNeededMode(AbstractMRTrafficController::NORMALMODE);
    setTimeout(SHORT_TIMEOUT);  // default value is the short timeout
    setRetries(0); // default to no retries

}

// create a new one
/*public*/ AbstractMRMessage::AbstractMRMessage(int i, QObject* parent ) : AbstractMessage(parent)
{
 common(i);
}
void AbstractMRMessage::common(int i)
{
if (i < 1) {
        log->error("invalid length in call to ctor");
        throw new IllegalArgumentException("invalid length in call to ctor");
    }
    _nDataChars = i;
    _dataChars = QVector<int>(i);
}

// copy one
/*public*/ AbstractMRMessage::AbstractMRMessage(/*@Nonnull*/ AbstractMRMessage* m, QObject* parent ): AbstractMessage(parent) {
    common();
    //Objects.requireNonNull(m, "copy ctor of null message");
    _nDataChars = m->_nDataChars;
//    _dataChars = new int[_nDataChars];
//    System.arraycopy(m._dataChars, 0, _dataChars, 0, _nDataChars);
    //_dataChars = QByteArray(m->_dataChars);
    for(int i=0; i < m->getNumDataElements(); i++)
     _dataChars[i] = m->_dataChars.at(i);

    setTimeout(m->getTimeout());
    setRetries(m->getRetries());
    setNeededMode(m->getNeededMode());
}

// from String
/*public*/ AbstractMRMessage::AbstractMRMessage(QString s, QObject* parent): AbstractMessage(parent) {
 common();
    common(s.length());
    for (int i = 0; i < _nDataChars; i++) {
        _dataChars[i] = s.toLocal8Bit().at(i);
    }
}

/*public*/ void AbstractMRMessage::setOpCode(int i) {
    _dataChars.replace(0, i);
}

/*public*/ int AbstractMRMessage::getOpCode() {
    try {
        return _dataChars[0];
    } catch(ArrayIndexOutOfBoundsException* e) {
        return 0;
    }
}

/*public*/ QString AbstractMRMessage::getOpCodeHex() {
    return "0x" + QString::number(getOpCode(),0,16);
}

// accessors to the bulk data


/*public*/ void AbstractMRMessage::setNeededMode(int pMode) {
    mNeededMode = pMode;
}

/*public*/ int AbstractMRMessage::getNeededMode() {
    return mNeededMode;
}

/**
 * Is a reply expected to this message?
 * <p>
 * By default, a reply is expected to every message; either a reply or a
 * timeout is needed before the next message can be sent.
 * <p>
 * If this returns false, the transmit queue will immediately go on to
 * transmitt the next message (if any).
 */
/*public*/ bool AbstractMRMessage::replyExpected() {
    return true;
}

// mode accessors

/*public*/ bool AbstractMRMessage::isBinary() {
    return _isBinary;
}

/*public*/ void AbstractMRMessage::setBinary(bool b) {
    _isBinary = b;
}

/**
 * Minimum timeout that's acceptable.
 * <p>
 * Also used as default for normal operations. Don't shorten this "to make
 * recovery faster", as sometimes <i>internal</i> delays can slow processing
 * down.
 * <p>
 * Units are milliseconds.
 */
/*static*/ /*protected*/ /*final*/ int AbstractMRMessage::SHORT_TIMEOUT = 2000;
/*static*/ /*protected*/ /*final*/ int AbstractMRMessage::LONG_TIMEOUT = 60000;  // e.g. for programming options

/*public*/ void AbstractMRMessage::setTimeout(int t) {
    mTimeout = t;
}

/*public*/ int AbstractMRMessage::getTimeout() {
    return mTimeout;
}

/*public*/ void AbstractMRMessage::setRetries(int i) {
    mRetries = i;
}

/*public*/ int AbstractMRMessage::getRetries() {
    return mRetries;
}

// display format

// contents (private)
/*public*/ void AbstractMRMessage::addIntAsThree(int val, int offset) {
    QString s = "" + val;
    if (s.length() != 3) {
        s = "0" + s;  // handle <10
    }
    if (s.length() != 3) {
        s = "0" + s;  // handle <100
    }
    setElement(offset, s.toLocal8Bit().at(0));
    setElement(offset + 1, s.toLocal8Bit().at(1));
    setElement(offset + 2, s.toLocal8Bit().at(2));
}

/*public*/ void AbstractMRMessage::addIntAsTwoHex(int val, int offset) {
    QString s = ("" + QString::number(val,0,16).toUpper());
    if (s.length() < 2) {
        s = "0" + s;  // handle one digit
    }
    if (s.length() > 2) {
        log->error("can't add as two hex digits: " + s);
    }
    setElement(offset, s.toLocal8Bit().at(0));
    setElement(offset + 1, s.toLocal8Bit().at(1));
}

/*public*/ void AbstractMRMessage::addIntAsThreeHex(int val, int offset) {
    QString s = ("" + QString::number(val,0,16)).toUpper();
    if (s.length() > 3) {
        log->error("can't add as three hex digits: " + s);
    }
    if (s.length() != 3) {
        s = "0" + s;
    }
    if (s.length() != 3) {
        s = "0" + s;
    }
    setElement(offset, s.toLocal8Bit().at(0));
    setElement(offset + 1, s.toLocal8Bit().at(1));
    setElement(offset + 2, s.toLocal8Bit().at(2));
}

/*public*/ void AbstractMRMessage::addIntAsFourHex(int val, int offset) {
    QString s = ("" + QString::number((val,0,16)).toUpper());
    if (s.length() > 4) {
        log->error("can't add as three hex digits: " + s);
    }
    if (s.length() != 4) {
        s = "0" + s;
    }
    if (s.length() != 4) {
        s = "0" + s;
    }
    if (s.length() != 4) {
        s = "0" + s;
    }
    setElement(offset, s.toLocal8Bit().at(0));
    setElement(offset + 1, s.toLocal8Bit().at(1));
    setElement(offset + 2, s.toLocal8Bit().at(2));
    setElement(offset + 3, s.toLocal8Bit().at(3));
}

//@Override
/*public*/ QString AbstractMRMessage::toString() {
    QString s = "";
    for (int i = 0; i < _nDataChars; i++) {
        if (_isBinary) {
            if (i != 0) {
                s += " ";
            }
            s = StringUtil::appendTwoHexFromInt(_dataChars[i] & 255, s);
        } else {
            s += QChar(_dataChars[i]);
        }
    }
    return s;
}

/*private*/ /*final*/ /*static*/ Logger* AbstractMRMessage::log = LoggerFactory::getLogger("AbstractMRMessage");
