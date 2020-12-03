#include "loconetmessage.h"
#include "loconetmessageinterpret.h"
#include "loggerfactory.h"

LocoNetMessage::LocoNetMessage(int len, QObject *parent) :
    AbstractMessage(parent)
{
 if (len < 2) {
     _nDataChars = 0;
     _dataChars = QVector<int>(1);
     log->error("LocoNetMessage does not allow object creation if length is less than 2."); // NOI18N
     return;
 }
 _nDataChars = len;
 _dataChars = QVector<int>(len);
 setObjectName("LocoNetMessage");
}

/*public*/ LocoNetMessage::LocoNetMessage(LocoNetMessage* original) {
//    Objects.requireNonNull(original,
 if(original == nullptr)
    throw Exception( "Unable to create message by copying a null message"); // NOI18N

    _nDataChars = original->getNumDataElements();
    _dataChars = QVector<int>(_nDataChars);

    for (int i = 0; i < original->getNumDataElements(); i++) {
        _dataChars[i] = original->_dataChars[i];
    }
}

LocoNetMessage::~LocoNetMessage()
{
}
/**
 * Create a message with specified contents
 * @param contents The array of contents for the message. The error
 * check word must be present, e.g. a 4-byte message must have
 * four values in the array
 */
LocoNetMessage::LocoNetMessage(QVector<int> contents, QObject *parent) :
    AbstractMessage(parent)
{
 if (contents.length() < 2) {
     _nDataChars = 0;
     _dataChars = QVector<int>(1);
     log->error("Cannot create a LocoNet message of length shorter than two."); // NOI18N
 }
 _nDataChars = contents.count();
 for (int i=0; i<contents.count(); i++) _dataChars.append(contents[i]);
 setObjectName("LocoNetMessage");
}
/**
 * Create a LocoNetMessage object without providing any
 * indication of its size or contents.
 * <p>
 * Because a LocoNet message requires at least a size, if
 * not actual contents, this constructor always logs an error.
 *
 */
/*public*/ LocoNetMessage::LocoNetMessage() {
    _nDataChars = 0;
    _dataChars = QVector<int>(1);
    log->error("LocoNetMessage does not allow a constructor with no argument"); // NOI18N
}
/**
 * Create a LocoNetMessage from a String
 * <p>
 * Because it is difficult to create a complete LocoNet object using a string,
 * this method of AbstractMessage is not supported.
 * <p>
 * This constructor always logs an error
 * @param s an unused parameter
 */
/*public*/ LocoNetMessage::LocoNetMessage(QString s) {
    _nDataChars = 0;
    _dataChars = QVector<int>(1);
    log->error("LocoNetMessage does not allow a constructor with a 'String' argument"); // NOI18N
}

LocoNetMessage::LocoNetMessage(QVector<char> contents, QObject *parent) :
    AbstractMessage(parent)
{
 if (contents.length() < 2) {
     _nDataChars = 0;
     _dataChars = QVector<int>(1);
     log->error("Cannot create a LocoNet message of length shorter than two."); // NOI18N
 }
 _nDataChars = contents.count();
 _dataChars = QVector<int>(contents.length());
 for (int i = 0; i < contents.length(); i++) {
     _dataChars[i] = contents[i] & 0xFF;
 }
 setObjectName("LocoNetMessage");

}

LocoNetMessage::LocoNetMessage(const LocoNetMessage& original, QObject *parent) :
    AbstractMessage(parent)
{
  _nDataChars = original._dataChars.count();
  this->_dataChars.reserve(_nDataChars);
  this->_dataChars = original._dataChars;
  setObjectName("LocoNetMessage");
}

//void LocoNetMessage::setOpCode(int i) { _dataBytes[0]=i;}
void LocoNetMessage::setOpCode(int i) { _dataChars.replace(0,i);}
int LocoNetMessage::getOpCode() {return _dataChars[0] & 0xff;}

/** Get a String representation of the op code in hex */
QString LocoNetMessage::getOpCodeHex() { return QString("0x%1").arg(getOpCode(),0,16); }

    /** Get length, including op code and error-detection byte */
int LocoNetMessage::getNumDataElements() {return _nDataChars;}

int LocoNetMessage::getElement(int n)
{
 if (n < 0 || n >= _dataChars.size())
 {
   log->error("reference element "+QString("%1").arg(n)
            +" in message of "+QString("%1").arg(_dataChars.size())
                      +" elements: "+this->toString());
  return 0;
 }
 return _dataChars[n] & 0xFF;
}
void LocoNetMessage::setElement(int n, int v)
{
 if (n < 0 || n >= _dataChars.size())
  log->error("reference element "+ QString("%1").arg(n)
            +" in message of "+_dataChars.size()
                      +" elements: "+this->toString());
// _dataBytes[n] = v;
 _dataChars.replace(n,v);
// _dataBytes.insert(n,v);
 if((_dataChars.size() != _nDataChars))
     qDebug()<< "length does not match size ";
}

/** Get a String representation of the entire message in hex */
QString LocoNetMessage::toString()
{
 int val ;
 QString sb;
 //for (int i=0; i<_nDataBytes; i++)
 for(int i=0; i<_nDataChars; i++)
 {
  if( i > 0 )
   sb.append( ' ' ) ;

  val = _dataChars[i] & 0xFF ;
// sb.append( hexChars[ val >> 4 ] );
// sb.append( hexChars[ val & 0x0F ] ) ;
  if(val < 16)
   sb.append(QString("0%1").arg(val,0,16));
  else
   sb.append(QString("%1").arg(val,0,16));
 }
 return sb ;
}
/** Get a QVector representing the entire message */
QVector<char> LocoNetMessage::toCharArray()
{
 int val;
 QVector<char> v;
 for (int i=0; i<_nDataChars; i++)
 {
  val = _dataChars.at(i) & 0xFF ;
  v.append(val);
 }
 return v;
}
/** Get a QByteArray representing the entire message */
QByteArray LocoNetMessage::toByteArray()
{
 int val;
 QByteArray ba;
 for (int i=0; i<_nDataChars; i++)
 {
  val = _dataChars.at(i) & 0xFF ;
  ba.append(val);
 }
 return ba;
}

/**
 * Set the parity byte(s) of this message
 */
 void LocoNetMessage::setParity()
 {
  // check for the D3 special case
  if (getOpCode() == 0xD3 && getNumDataElements() > 6 )
  {
   // sum the D3 header separately
   int sum = 0xFF;
   for (int i = 0; i< 5; i++) sum = sum ^ getElement(i);
   setElement(5, sum);
   // sum back half to 0xFF
   sum = 0xFF;
   for (int i = 6; i< getNumDataElements()-1; i++) sum = sum ^ getElement(i);
   setElement(getNumDataElements()-1, sum);
   return;
  }

  // normal case - just sum entire message
  int len = getNumDataElements();
  int chksum = 0xff;  /* the seed */
  int loop;

  for(loop = 0; loop < len-1; loop++)
  {  // calculate contents for data part
   chksum ^= getElement(loop);
  }
  setElement(len-1, chksum);  // checksum is last element of message    }
 }

/**
 * check whether the message has a valid parity
 */
bool LocoNetMessage::checkParity()
{
 int len = getNumDataElements();
 int chksum = 0xff;  /* the seed */
 int loop;

 // check for the D3 special case
 if (getOpCode() == 0xD3 && len > 6 )
 {
  // sum the D3 header separately
  int sum = 0xFF;
  for (loop = 0; loop< 5; loop++) sum = sum ^ getElement(loop);
  if (getElement(5) != sum) return false;
  // sum back half to 0xFF
  sum = 0xFF;
  for (loop = 6; loop< len-1; loop++) sum = sum ^ getElement(loop);
  if (getElement(len-1) != sum) return false;
  return true;
 }
 // normal case - just sum entire message

 for(loop = 0; loop < len-1; loop++)
 {  // calculate contents for data part
  chksum ^= getElement(loop);
 }
 return (chksum == getElement(len-1));
}

// decode messages of a particular form

// create messages of a particular form
/**
 * Get the 8 data bytes from an OPC_PEER_XFR message
 * @return int[8] data bytes
 */
/*public*/ QVector<int> LocoNetMessage::getPeerXfrData()
{
 if (getOpCode()!=LnConstants::OPC_PEER_XFER)
     log->error("getPeerXfrData called with wrong opcode "+QString("0x%1").arg(getOpCode(),0,16));
 if (getElement(1)!=0x10)
     log->error("getPeerXfrData called with wrong secondary code "+QString("0x%1").arg(getElement(1),0,16));
 if (getNumDataElements()!=16)
     log->error("getPeerXfrData called with wrong length "+QString("0x%1").arg(getNumDataElements(),0,16));

 //int[] data = new int[]{0,0,0,0,  0,0,0,0};
 QVector<int> data(8,0);

 int pxct1 = getElement(5);
 int pxct2 = getElement(10);

 // fill the 8 data items
 data[0]= (getElement(6)&0x7F)+((pxct1&0x01)!=0?0x80:0);
 data[1]= (getElement(7)&0x7F)+((pxct1&0x02)!=0?0x80:0);
 data[2]= (getElement(8)&0x7F)+((pxct1&0x04)!=0?0x80:0);
 data[3]= (getElement(9)&0x7F)+((pxct1&0x08)!=0?0x80:0);

 data[4]= (getElement(11)&0x7F)+((pxct2&0x01)!=0?0x80:0);
 data[5]= (getElement(12)&0x7F)+((pxct2&0x02)!=0?0x80:0);
 data[6]= (getElement(13)&0x7F)+((pxct2&0x04)!=0?0x80:0);
 data[7]= (getElement(14)&0x7F)+((pxct2&0x08)!=0?0x80:0);

 return data;
}

/**
 * Two messages are the same if their entire data content
 * is the same.  We ignore the error-check byte to ease
 * comparisons before a message is transmitted.
 * @return true if objects contain the same message contents
 */
/*public*/ bool LocoNetMessage::equals(QObject* o)
{
 if (o == nullptr) return false;
 if (this == nullptr) return false;
 //if (! (o instanceof LocoNetMessage)) return false;
 if(o->objectName() != "LocoNetMessage") return false;
 LocoNetMessage* m = (LocoNetMessage*) o;
 if (m->_nDataChars != this->_nDataChars) return false;
 for (int i = 0; i<_nDataChars-1; i++)
  if ((m->_dataChars[i]&0xFF) != (this->_dataChars[i]&0xFF))
   return false;
 return true;
}

/*public*/ int LocoNetMessage::hashCode()
{
 int r = _nDataChars;
 if (_nDataChars>0) r+= _dataChars[0];
 if (_nDataChars>1) r+= _dataChars[1]*128;
 if (_nDataChars>2) r+= _dataChars[2]*128*128;
  return r;
}

//@Override
/**
 * Interprets a LocoNet message into a string describing the
 * message.
 * <p>
 * Where appropriate, this method presents both the JMRI "System Name" and
 * the JMRI "User Name" (where available) for messages which contain control
 * or status information for a Turnout, Sensor or Reporter.
 * <p>
 * Display of "User Name" information is acquired from the appropriate "manager",
 * via a reference to an object with an assembled "System Name".  This method
 * assumes a system connection "prefix" of "L" when assembling that system name.
 * The remainder of the assembled system name depends on the message contents -
 * message type determines which JMRI object type letter to add - "T" for turnouts,
 * "S" for sensors, and "R" for transponding reporters.
 * <p>
 * If the appropriate manager already has an object for the system name being
 * referenced, the method requests the associated user name.  If a user name is
 * returned, then the method uses that user name as part of the message.  If
 * there is no associated JMRI object configured, or if the associated JMRI
 * object does not have a user name assigned, then the method does not display
 * a user name.
 * <p>
 * The method is not appropriate when the user has multiple LocoNet connections
 * or when the user has a single LocoNet connection but has changed the connection
 * prefix to something other than the default of "L".
 * <p>
 * @return a human readable representation of the message.
 */
/*public*/ QString LocoNetMessage::toMonitorString(){
      return toMonitorString("L"); // NOI18N
}

/**
 * Interprets a LocoNet message into a string describing the
 * message when a specific connection prefix is known.
 * <p>
 * Where appropriate, this method presents both the JMRI "System Name" and
 * the JMRI "User Name" (where available) for messages which contain control
 * or status information for a Turnout, Sensor or Reporter.
 * <p>
 * Display of "User Name" information is acquired from the appropriate "manager",
 * via a reference to an object with an assembled "System Name".  This method
 * uses system connection "prefix" as specified in the "prefix" argument when
 * assembling that system name.  The remainder of the assembled system name
 * depends on the message contents.  Message type determines which JMRI
 * object type letter is added after the "prefix" - "T" for turnouts, * "S"
 * for sensors, and "R" for transponding reporters.  The item number
 * specified in the LocoNet message is appended to finish the system name.
 * <p>
 * If the appropriate manager already has an object for the system name being
 * referenced, the method requests the associated user name.  If a user name is
 * returned, then the method uses that user name as part of the message.  If
 * there is no associated JMRI object configured, or if the associated JMRI
 * object does not have a user name assigned, then the method does not display
 * a user name.
 * <p>
 * @param prefix - the "System Name" prefix denoting the connection
 * @return a human readable representation of the message.
 */
/*public*/ QString LocoNetMessage::toMonitorString(/*@Nonnull*/ QString prefix){
      return LocoNetMessageInterpret::interpretMessage(this,
              prefix+"T", prefix+"S", prefix+"R");
}

/**
 * Return a newly created OPC_PEER_XFR message.
 * @param src Source address
 * @param dst Destination address
 * @param d   int[8] for the data contents or null
 * @param code The instruction code placed in the pcxt1 pcxt2 bytes
 * @return    The formatted message
 */
/*static*/ /*public*/ LocoNetMessage* LocoNetMessage::makePeerXfr(int src, int dst, QVector<int> d, int code)
{
 LocoNetMessage* msg = new LocoNetMessage(16);
 msg->setOpCode(LnConstants::OPC_PEER_XFER);
 msg->setElement(1, 0x10);  // 2nd part of op code

 // accumulate the pxct1,2 bytes
 int pxct1 = 0;
 int pxct2 = 0;

 // install the "CODE" in pxct1, pxct2
 pxct1 |= (code&0x7)*0x10;       // lower 3 bits
 pxct2 |= ( (code&0x38)/8)*0x10; // next 4 bits

 // store the addresses
 msg->setElement(2,src&0x7F); //src
 msg->setElement(3,dst&0x7F); //dstl
 msg->setElement(4,highByte(dst)&0x7F); //dsth

 // store the data bytes
 msg->setElement(6, d[0]&0x7F);        if (highBit(d[0])) pxct1 |= 0x01;
 msg->setElement(7, d[1]&0x7F);        if (highBit(d[1])) pxct1 |= 0x02;
 msg->setElement(8, d[2]&0x7F);        if (highBit(d[2])) pxct1 |= 0x04;
 msg->setElement(9, d[3]&0x7F);        if (highBit(d[3])) pxct1 |= 0x08;

 msg->setElement(11, d[4]&0x7F);       if (highBit(d[4])) pxct2 |= 0x01;
 msg->setElement(12, d[5]&0x7F);       if (highBit(d[5])) pxct2 |= 0x02;
 msg->setElement(13, d[6]&0x7F);       if (highBit(d[6])) pxct2 |= 0x04;
 msg->setElement(14, d[7]&0x7F);       if (highBit(d[7])) pxct2 |= 0x08;

 // store the pxct1,2 values
 msg->setElement( 5, pxct1);
 msg->setElement(10, pxct2);

 return msg;
}
/*static*/ /*public*/ LocoNetMessage* LocoNetMessage::makePeerXfr2(int src, int dsth, int dstl, int svAdrh, int svAdrl, QVector<int> d, int code)
{
 LocoNetMessage* msg = new LocoNetMessage(16);
 msg->setOpCode(LnConstants::OPC_PEER_XFER);
 msg->setElement(1, 0x10);  // 2nd part of op code

 msg->setElement(2,src &0x7F); //src
 msg->setElement(3, code &0x7f);
 msg->setElement(4, 0x02); //SV_TYPE
 int svx1 = 0x10;
 if(highBit(dstl))   svx1 |= 0x01;
 if(highBit(dsth))   svx1 |= 0x02;
 if(highBit(svAdrl)) svx1 |= 0x04;
 if(highBit(svAdrh)) svx1 |= 0x08;

 msg->setElement(6,dstl &0x7f);   // DST_L
 msg->setElement(7,dsth &0x7f);   // DST_H
 msg->setElement(8,svAdrl &0x7f); // SV_ADRL
 msg->setElement(9,svAdrh &0x7f); // SV_ADRH
 int svx2 = 0x10;
 if(highBit(d[0])) svx2 |= 0x01;
 if(highBit(d[1])) svx2 |= 0x02;
 if(highBit(d[2])) svx2 |= 0x04;
 if(highBit(d[3])) svx2 |= 0x08;
 msg->setElement(11, d[0] &0x7F); // D1
 msg->setElement(12, d[1] &0x7F); // D2
 msg->setElement(13, d[2] &0x7F); // D3
 msg->setElement(14, d[3] &0x7F); // D4
 msg->setElement(5, svx1);        // SVX1
 msg->setElement(10, svx2);       // SVX2
 return msg;
}
/**
 * Check if a high bit is set, usually used to store it in some
 * other location (LocoNet does not allow the high bit to be set
 * in data bytes)
 * @param val
 * @return True if the argument has the high bit set
 */
/*static protected*/ bool LocoNetMessage::highBit(int val)
{
 if ((val&(~0xFF)) != 0)
 {
  Logger::error("highBit called with too large value: 0x"
                                      +QString("%1").arg(val,0,16));
 }
 return (0!=(val&0x80));
}

/*static protected*/ int LocoNetMessage::lowByte(int val) { return val&0xFF; }
/*static protected*/ int LocoNetMessage::highByte(int val)
{
 if ((val&(~0xFFFF)) != 0) Logger::error("highByte called with too large value: "
                                        +QString("%1").arg(val,0,16));
 return (val&0xFF00)/256;
}

/**
 * Sensor-format 0-n address
 * @return 0 to n-1 address
 */
/*public*/ int LocoNetMessage::sensorAddr()
{
 int sw1 = getElement(1);
 int sw2 = getElement(2);
 int as = sw2&0x20;		// should be a LocoNet constant?
 int high = sw2&0x0F;
 int low = sw1&0x7F;
 return high*256+low*2+(as!=0 ? 1 : 0);
}

/**
 * If this is an OPC_INPUT_REP, return the 0-n address, else -1
 * @return 0 to n-1 address
 */
/*public*/ int LocoNetMessage::inputRepAddr() {
    if (getOpCode()==LnConstants::OPC_INPUT_REP) {
        return sensorAddr();
    } else return -1;
}

/**
 * Return the 1-N turnout address
 * @return 1-N address
 */
/*public*/ int LocoNetMessage::turnoutAddr() {
    int a1 = getElement(1);
    int a2 = getElement(2);
    return (((a2 & 0x0f) * 128) + (a1 & 0x7f))+1;
}

//// contents (private)
//private int _nDataBytes = 0;
//private int _dataBytes[] = null;

//      // Hex char array for toString conversion
//    static char[] hexChars = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' } ;

// initialize logging
Logger* LocoNetMessage::log = LoggerFactory::getLogger("LocoNetMessage");


