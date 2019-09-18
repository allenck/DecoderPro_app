#include "sprogreply.h"
#include "loggerfactory.h"
#include "sprogconstants.h"
#include "sprogmessage.h"
#include "exceptions.h"

using namespace Sprog;

/**
 * Carries the reply to a SprogMessage.
 *
 * @author	Bob Jacobsen Copyright (C) 2001
 * @author	Andrew Berridge - refactored, cleaned up, Feb 2010
  */
///*public*/ class SprogReply extends AbstractMRReply {

// Longest boot reply is 256bytes each preceded by DLE + 2xSTX + ETX
/*static*/ /*public*/ /*final*/ int SprogReply::maxSize = 515;

// create a new one
/*public*/ SprogReply::SprogReply(QObject *parent) : AbstractMRReply(parent){
    //super();
     _isBoot = false;
     _id = -1;

}

/*public*/ void SprogReply::setId(int id) {
    _id = id;
}

/*public*/ int SprogReply::getId() {
    return _id;
}

// no need to do anything
//@Override
/*protected*/ int SprogReply::skipPrefix(int index) {
    return index;
}

/**
 * Create a new SprogReply as a deep copy of an existing SprogReply.
 *
 * @param m the SprogReply to copy
 */
//@SuppressWarnings("null")
/*public*/ SprogReply::SprogReply(SprogReply* m, QObject* parent) : AbstractMRReply(parent) {
    //this();
    if (m == NULL) {
        log->error("copy ctor of null message");
        return;
    }
    _nDataChars = m->_nDataChars;
    _isBoot = m->_isBoot;
    if (m->isUnsolicited()) {
        AbstractMRReply::setUnsolicited();
    }
    for (int i = 0; i < _nDataChars; i++) {
        _dataChars.replace(i, m->_dataChars[i]);
    }
    _id = m->_id;
}

/**
 * Create a SprogReply from a String.
 *
 * @param replyString a String containing the contents of the reply
 * @param isBoot a bool indicating if this is a boot reply
 */
/*public*/ SprogReply::SprogReply(QString replyString, bool isBoot, QObject* parent) : AbstractMRReply(replyString, parent){
    //this(replyString);
    _isBoot = isBoot;
}

/*public*/ SprogReply::SprogReply(QString replyString, QObject *parent) : AbstractMRReply(replyString, parent){
    //super(replyString);
}

/**
 * Is this reply indicating that an overload condition was detected?
 */
/*public*/ bool SprogReply::isOverload() {
    return (this->toString().indexOf("!O") >= 0);
}

/**
 * Is this reply indicating that a general error has occurred?
 */
/*public*/ bool SprogReply::isError() {
    return (this->toString().indexOf("!E") >= 0);
}

/**
 * Check and strip framing characters and DLE from a SPROG bootloader reply.
 */
/*public*/ bool SprogReply::strip() {
    QByteArray tmp = QByteArray(_nDataChars, 0);
    int j = 0;
    _isBoot = true; // definitely a boot message
    // Check framing characters
    if (_dataChars[0] != SprogMessage::STX) {
        return false;
    }
    if (_dataChars[1] != SprogMessage::STX) {
        return false;
    }
    if (_dataChars[_nDataChars - 1] != SprogMessage::ETX) {
        return false;
    }

    // Ignore framing characters and strip DLEs
    for (int i = 2; i < _nDataChars - 1; i++) {
        if (_dataChars[i] == SprogMessage::DLE) {
            i++;
        }
        tmp.replace(j++, _dataChars[i]);
    }

    // Copy back to original SprogReply
    for (int i = 0; i < j; i++) {
        _dataChars.replace(i, tmp[i]);
    }
    _nDataChars = j;
    return true;
}

/**
 * Check and strip checksum from a SPROG bootloader reply.
 * <p>
 * Assumes framing and DLE chars have been stripped
 */
/*public*/ bool SprogReply::getChecksum() {
    int checksum = 0;
    for (int i = 0; i < _nDataChars; i++) {
        checksum += _dataChars[i] & 0xff;
    }
    _nDataChars--;
    return ((checksum & 0xff) == 0);
}

/**
 * Return a string representation of this SprogReply.
 */
//@Override
/*public*/ QString SprogReply::toString() {
    //String s = "";
    QString buf;// = new StringBuffer();
    if (_isBoot || (_dataChars[0] == SprogMessage::STX)) {
        for (int i = 0; i < _nDataChars; i++) {
            //s+="<"+(((char)_dataChars[i]) & 0xff)+">";
            buf.append("<");
            buf.append(QChar(_dataChars[i]));
            buf.append(">");
        }
    } else {
        for (int i = 0; i < _nDataChars; i++) {
            //s+=;
            buf.append((char) _dataChars[i]);
        }
    }
    return buf/*.toString()*/;
}

/**
 * Extract Read-CV returned value from a message.
 * <p>
 * SPROG is assumed to not be echoing commands. A reply to a command may
 * include the prompt that was printed after the previous command.
 * <p>
 * Reply to a CV read is of the form " = hvv" where vv is the CV value in hex
 *
 * @return -1 if message can't be parsed
 */
//@Override
/*public*/ int SprogReply::value() {
    int index = 0;
    index = skipWhiteSpace(index);
    index = skipEqual(index);
    index = skipWhiteSpace(index);
    QString s1 = QString((char) getElement(index));
    QString s2 = QString((char) getElement(index + 1));
    int val = -1;
    try {
     bool ok;
        int sum = s2.toInt(&ok, 16);
        if(!ok) throw NumberFormatException();
        sum += 16 * s1.toInt(&ok, 16);
        if(!ok) throw NumberFormatException();
        val = sum;  // don't do this assign until now in case the conversion throws
    } catch (NumberFormatException e) {
        log->error(tr("Unable to get number from reply: \"%1%2\" index: %3 message: \"%4\"").arg(s1).arg(s2).arg(index).arg(toString()));
    }
    return val;
}

/**
 * Find a specific string in the reply.
 *
 * @param s string to look for
 * @return index of String s in the reply
 */
//@Override
/*public*/ int SprogReply::match(QString s) {
    //QString rep = QString(_dataChars, 0, _nDataChars);
 QString rep;// = QString(_dataChars.mid(0, _nDataChars));
 for(int i=0; i < _nDataChars; i++)
  rep.append(_dataChars.at(0));
    return rep.indexOf(s);
}

/*private*/ int SprogReply::skipEqual(int index) {
    // start at index, skip over the equals and hex prefix
    //int len = "= h".length();
 int len = 3; // ??
    if (getNumDataElements() >= index + len - 1
            && '=' == (char) getElement(index)
            && ' ' == (char) getElement(index + 1)
            && 'h' == (char) getElement(index + 2)) {
        index += len;
    }
    return index;
}

/**
 * Normal SPROG replies will end with the prompt for the next command.
 * Bootloader will end with ETX with no preceding DLE.
 * SPROG v4 bootloader replies "L{@literal >}" on entry and replies "." at other
 * times.
 */
/*public*/ bool SprogReply::endNormalReply()
{
 // Detect that the reply buffer ends with "P> " or "R> " (note ending space)
 int num = this->getNumDataElements();
 if (num >= 3)
 {
  // ptr is offset of last element in SprogReply
  int ptr = num - 1;
  if (this->getElement(ptr) != ' ')
  {
      return false;
  }
  if (this->getElement(ptr - 1) != '>')
  {
      return false;
  }
  if ((this->getElement(ptr - 2) != 'P') && (this->getElement(ptr - 2) != 'R'))
  {
      return false;
  }
  // Now see if it's unsolicited !O for overload
  if (num >= 5)
  {
   for (int i = 0; i < num - 1; i++)
   {
    if ((this->getElement(i) == '!'))
    {
     AbstractMRReply::setUnsolicited();
    }
   }
  }
  return true;
 }
 else
 {
  return false;
 }
}

/*public*/ bool SprogReply::endBootReply() {
    // Detect that the reply buffer ends with ETX with no preceding DLE.
    // This is the end of a SPROG II bootloader reply or the end of
    // a SPROG v4 echoing the bootloader version request
    int num =this->getNumDataElements();
    if (num >= 2) {
        // ptr is offset of last element in SprogReply
        int ptr = num - 1;
        if ((this->getElement(ptr) & 0xff) != SprogMessage::ETX) {
            return false;
        }
        if ((this->getElement(ptr - 1) & 0xff) == SprogMessage::DLE) {
            return false;
        }
        return true;
    } else {
        return false;
    }
}

/*public*/ bool SprogReply::endBootloaderReply(SprogConstants::SprogState sprogState) {
    // Detect that the reply buffer ends with "L>" or "." from a SPROG v4
    // bootloader
    int num =this->getNumDataElements();
    int ptr = num - 1;
    if ((sprogState == SprogConstants::SprogState::V4BOOTMODE) && ((this->getElement(ptr) == '.')
            || (this->getElement(ptr) == 'S'))) {
        return true;
    }
    if (num >= 2) {
        // ptr is offset of last element in SprogReply
        if (this->getElement(ptr) != '>') {
            return false;
        }
        if (this->getElement(ptr - 1) != 'L') {
            return false;
        }
        return true;
    } else {
        return false;
    }
}

/*private*/ /*final*/ /*static*/ Logger* SprogReply::log = LoggerFactory::getLogger("SprogReply");
