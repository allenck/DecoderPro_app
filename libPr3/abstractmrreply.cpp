#include "abstractmrreply.h"
#include "exceptions.h"

AbstractMRReply::AbstractMRReply(QObject *parent) :
    AbstractMessage(parent)
{
 init();
}
/**
 * Abstract base class for replies in a message/reply protocol.
 * <P>
 * Handles the character manipulation.
 * <p>
 * This is a variable length reply, which can grow as
 * needed.  The length is given by the largest index written so far.
 *
 * @author		Bob Jacobsen  Copyright (C) 2003
 * @version             $Revision: 17977 $
 */
//abstract /*public*/ class AbstractMRReply extends AbstractMessage {
    // is this logically an abstract class?

// create a new one
///*public*/  AbstractMRReply() {
//    setBinary(false);
//    unsolicited = false;
//    _dataChars = new int[maxSize()];
//}

// copy one
/*public*/  AbstractMRReply::AbstractMRReply(AbstractMRReply* m, QObject *parent) : AbstractMessage(parent){
    //this();
    init();
    if (m == NULL)
        log->error("copy ctor of NULL message");
    else{
        _nDataChars = m->_nDataChars;
        for (int i = 0; i<_nDataChars; i++) _dataChars.replace(i, m->_dataChars.at(i));
    }
}

// from String
/*public*/ AbstractMRReply::AbstractMRReply(QString s, QObject *parent) : AbstractMessage(parent) {
    //this();
    init();
    _nDataChars = s.length();
    for (int i = 0; i<_nDataChars; i++)
        _dataChars.replace(i, s.mid(i,1));
}
void AbstractMRReply::init()
{
    log = new Logger("AbstractMRReply");
    setBinary(false);
    unsolicited = false;
    _dataChars = QByteArray(maxSize(),0);

}

// keep track of length
/*public*/ void AbstractMRReply::setElement(int n, int v) {
    _dataChars[n] = (char) v;
    _nDataChars = qMax(_nDataChars, n+1);
}

/*public*/ void AbstractMRReply::setOpCode(int i) { _dataChars.replace(0, (char)i);}
/*public*/ int AbstractMRReply::getOpCode() {return _dataChars.at(0);}

// accessors to the bulk data
/*public*/ void AbstractMRReply::flush(){
    _nDataChars = 0;
}

// mode accessors
/*public*/ bool AbstractMRReply::isBinary() { return _isBinary; }
/*public*/ void AbstractMRReply::setBinary(bool b) { _isBinary = b; }

/*public*/ /*final*/ void AbstractMRReply::setUnsolicited() { unsolicited = true; }

/*public*/ bool AbstractMRReply::isUnsolicited() { return unsolicited; }

/*
 * Return true if the message is an error and we can automatically
 * recover by retransmitting the message.  Override in system specific
 * classes if required.
 */
/*public*/ bool AbstractMRReply::isRetransmittableErrorMsg() { return false; }

// display format
/*public*/ QString AbstractMRReply::toString()
{
 QString s = "";
 for (int i=0; i<_nDataChars; i++)
 {
  if (_isBinary)
  {
   if (i!=0) s+=" ";
   //s = jmri.util.StringUtil.appendTwoHexFromInt(_dataChars[i]&0xFF, s);
   if((_dataChars.at(i)& 0xFF) < 0x10) s.append("0");
   s.append(QString("%1").arg((_dataChars.at(i)& 0xFF),0,16));

  }
  else
  {
   s+=(char)_dataChars.at(i);
  }
 }
 return s;
}


/*public*/ int AbstractMRReply::value() {  // integer value of 1st three digits
    int index = 0;
    index = skipWhiteSpace(index);
    index = skipPrefix(index);
    index = skipWhiteSpace(index);
    QString s = ""+(char)getElement(index)+(char)getElement(index+1)+(char)getElement(index+2);
    int val = -1;
    bool bOk = false;
    try {
        val = s.toInt(&bOk);
    } catch (Exception e) {
        log->error("Unable to get number from reply: \""+s+"\" index: "+index
                  +" message: \""+toString()+"\"");
    }
    return val;
}

/*public*/ int AbstractMRReply::pollValue() {  // integer value of HHHH
    int index = 0;
    index = skipWhiteSpace(index);
    index = skipPrefix(index);
    index = skipWhiteSpace(index);
    QString s = ""+(char)getElement(index)+(char)getElement(index+1)
                +(char)getElement(index+2)+(char)getElement(index+3);
    int val = -1;
    bool bOk = false;
    try
    {
        val = /*Integer.parseInt(s,16);*/s.toInt(&bOk,16);
        if(!bOk) throw new Exception();
    } catch (Exception e) {
        log->error("Unable to get number from reply: \""+s+"\" index: "+index
                  +" message: \""+toString()+"\"");
    }
    return val;
}

/*public*/ int AbstractMRReply::match(QString s) {
    // loop over starting positions
    outer:
    for (int i=0; i<_nDataChars-s.length()+1; i++) {
        // loop to check each start position
        QByteArray ba = s.toLatin1();
        for (int j=0; j<s.length(); j++)
        {
            //if (_dataChars.at(i+j) != s.mid(j, 1)) continue outer;
            if (_dataChars.at(i+j) != ba.at(j)) break; // ???

        }
        // here we succeed
        return i;
     }

    return -1;

    // find a specific string in the reply
    //String rep = new String(_dataChars, 0, _nDataChars);
    //return rep.indexOf(s);
}

/*public*/ int AbstractMRReply::skipWhiteSpace(int index) {
    // start at index, passing any whitespace & control characters at the start of the buffer
    while (index < getNumDataElements()-1 &&
           ((char)getElement(index) <= ' '))
        index++;
    return index;
}

/*public*/ int AbstractMRReply::maxSize() { return DEFAULTMAXSIZE; }


//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractMRReply.class.getName());

//}
