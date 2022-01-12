#include "locoiodata.h"
#include "locoio.h"
#include "llnmon.h"
#include <QtAlgorithms>   // for qSort()
#include "sleeperthread.h"
#include "loconetmessageinterpret.h"

const int LocoIOData::LocoBufferAddress  = 0x0150;
/*static*/ const int LocoIOData::NONE = 0;
/*static*/ const int LocoIOData::READVALUE1 = 1;
/*static*/ const int LocoIOData::READINGVALUE1 = 2;
/*static*/ const int LocoIOData::READVALUE2 = 3;
/*static*/ const int LocoIOData::READINGVALUE2 = 4;
/*static*/ const int LocoIOData::READMODE = 5;
/*static*/ const int LocoIOData::READINGMODE = 6;

//LocoIOData::LocoIOData(QObject *parent) : QObject(parent)
//{
// common(0,0,NULL);
//}
/**
 *
 * @author plocher
 */
//public class LocoIOData
//        implements LocoNetListener, java.beans.PropertyChangeListener {

/*public*/ LocoIOData::LocoIOData(LocoIOAddress *address, LnTrafficController *tc, QObject *parent) : QObject(parent)
{
 common(address->unitAddress(), address->unitSubAddress(),tc);
 moduleType = address->moduleType();
}

/** Creates a new instance of LocoIOData */
/*public*/ LocoIOData::LocoIOData(int unitAddr, int unitSubAddr, LnTrafficController* tc, QObject *parent) : QObject(parent)
{
 common(unitAddr, unitSubAddr, tc);
}

/*public*/ LocoIOData::LocoIOData(const LocoIOData & other) : QObject()
{
 common(other.unitAddress, other.unitSubAddress, other.tc);
// for(int i = 0; i < other.probedAddresses.count(); i++)
//  probedAddresses.append(other.probedAddresses.at(i));
}

void LocoIOData::common(int unitAddr, int unitSubAddr, LnTrafficController *tc)
{
 setObjectName("LocoIOData");
 dataListeners = new SwingPropertyChangeSupport(this, nullptr);
 log = new Logger(this->objectName(), this);
 /**
  * Define the number of rows in the table, which is also
  * the number of "channels" in a signel LocoIO unit
  */
  _numRows = 16;
  _numRowsServo = 8;
 /**
  * LocoBuffer is always address 0x01 0x50
  */
 ///*private*/ /*static final int*/ LocoBufferAddress;//  = 0x0150; (PC's address!)
 /*private*/ /*QString*/ locoBufferVersion = "<unknown>";
 /*private*/ /*QString*/ locoIOVersion     = "<unknown>";
 /*private*/ /*QString*/ status            = "<unknown>";  // LocoIO activity status
 /**
  * Per-port SV data
  */
 /*private*/ /*LocoIOMode[]*/ lim =  QVector<LocoIOMode*>(_numRows, nullptr);
//    /*private*/ /*LocoIOMode[]*/ x2lim =  QVector<LocoIOMode*>(_numRows, NULL);

 /*private*/ /*int[]*/ addr    =  QVector<int>(_numRows*2, 0);
 /*private*/ /*int[]*/ sv      = QVector<int>(_numRows*2, 0);
 /*private*/ /*int[]*/ v1      =  QVector<int>(_numRows*2, 0);
 /*private*/ /*int[]*/ v2      =  QVector<int>(_numRows*2, 0);
 /*private*/ /*int[]*/ x2addr    =  QVector<int>(_numRows, 0);
 /*private*/ /*int[]*/ x2sv      = QVector<int>(_numRows, 0);
 /*private*/ /*int[]*/ x2v1      =  QVector<int>(_numRows, 0);
 /*private*/ /*int[]*/ x2v2      =  QVector<int>(_numRows, 0);
 /*private*/ /*int[]*/ readState  =  QVector<int>(_numRows*2, NONE);
 /*private*/ /*int[]*/ writeState =  QVector<int>(_numRows*2, NONE);
 /*private*/ /*int[]*/ readStateX2  =  QVector<int>(_numRows, NONE);
 /*private*/ /*int[]*/ writeStateX2 =  QVector<int>(_numRows, NONE);
  servoP1 = QVector<int>(_numRowsServo, 0);
  servoP2 = QVector<int>(_numRowsServo, 0);
  servoSpd = QVector<int>(_numRowsServo, 0);
  readStateServo = QVector<int>(_numRowsServo, NONE);
  writeStateServo = QVector<int>(_numRowsServo, NONE);

 _dirty = QVector<bool>(_numRows*2, false);
 _x2Dirty = QVector<bool>(_numRows, false);
 _servoDirty = QVector<bool>(_numRowsServo, false);
 bDirty=false;
 bX2Dirty = false;
 bServoDirty = false;
 vals = nullptr;
 b3ByteRead = true;
 bProbing = false;
 /**
  * Record whether this pin is looking to capture a value
  * from the LocoNet
  */

 /*private*/ /*boolean[]*/ capture    = QVector<bool>(_numRows*2, false);
 /*private*/ /*String[]*/ mode =  QStringList();


 timeoutcounter = 0;
 unitAddress    = unitAddr;
 unitSubAddress = unitSubAddr;
 validmodes = new LocoIOModeList();
 if(b3ByteRead)
  READ= READMODE;
 else
  READ = READVALUE1;  // starting state
 WRITE = WRITEVALUE1;  // starting state
 lastOpCv = -1;
 reading = false;  // false means write in progress
 currentPin = 0;
 timer = new QTimer(this);
 connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
 bReadingConfig=false;
 bReadingOption = false;
 bSettingOption = false;
//    pGreen = new QPalette();
//    pGreen->setColor(QPalette::Active, QPalette::Base, QColor(170,255,127));
//    pGray = new QPalette();
//    pGray->setColor(QPalette::Base, Qt::gray);
//    pRed = new QPalette();
//    pRed->setColor(QPalette::Base, QColor(255,85,0));
//    pYellow = new QPalette();
//    pYellow->setColor(QPalette::Base, QColor(255,255,127));
//    pWhite = new QPalette();
//    pWhite->setColor(QPalette::Active, QPalette::Base, QColor(255,255,255));
//    pMagenta = new QPalette();
//    pMagenta->setColor(QPalette::Base, QColor(255,170,255));
 ssGreen = "rgb(152,251,152)";
 ssGray = "gray";
 ssPink = "pink";
 ssRed = "rgb(255,85,0)";
 ssYellow = "yellow";
 ssLightYellow = "rgb(255,255,224)";
 ssWhite = "white";
 ssMagenta = "magenta";
 ssBlueGreen = "rgb(170, 255, 255)";
 ssPurple = "rgb(170, 170, 255)";
 ssBlack = "rgb(0,0,0)";
 ssLtBlue = "rgb(240,248,255)";
 sv0 = 0;
 probedAddresses.clear();
 bProbing = false;
 probeTimer = new QTimer(this);
 connect(probeTimer, SIGNAL(timeout()), this, SLOT(probeTimeout()));

 for (int i=0; i<_numRows*2; i++)
    // setMode(i, "<none>");
     mode.append("<none>");
//        lim[i] = NULL;
//        setAddr(i,0);
//        setSV(i,0);
//        setV1(i,0);
//        setV2(i,0);
//        readState[i]  = NONE;
//        writeState[i] = NONE;
//        capture[i]    = false;
//    }
 addPropertyChangeListener((PropertyChangeListener*)this);
 this->tc = tc;
 // for now, we're always listening to LocoNet
 if (this->tc!=nullptr)
 {
  //this->tc->addLocoNetListener(~0, (LocoNetListener*)this);
  connect(this->tc, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
 }
 else
 {
  log->error("No LocoNet interface available");
 }
 _defaults.reserve(16*3+3); // TODO:
 _defaults << 0 <<81<<1<< 192<<1<<0<<192<<1<<32<<192<<2<<0<<192<<2<<32<<192<<3<<0<<192<<3<<32<<192<<4<<0<<192<<4<<32<< 128<<1<<16<<128<<1<<46<<128<<2<<16<<128<<2<<48<<128<<3<<16<<192<<3<<48<<128<<4<<16<<128<<4<<48;
 for(int i=0; i <_numRows*2; i ++)
 {
  _defaults << 0 <<0;
 }
//    QMutexLocker locker1(&mutex1);
//    QMutexLocker locker2(&mutex2);
//    QMutexLocker locker3(&mutex3);
//    QMutexLocker locker4(&mutex4);
 connect(this, SIGNAL(cvRead(int,int)), this, SLOT(onCvRead(int,int)));

}

LocoIOData::~LocoIOData()
{
 disconnect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
 disconnect(probeTimer, SIGNAL(timeout()), this, SLOT(probeTimeout()));
 disconnect(this, SIGNAL(cvRead(int,int)), this, SLOT(onCvRead(int,int)));

 delete log;
 delete dataListeners;
}

int LocoIOData::numRows(){return _numRows;}
#if 1 // TODO::
/*public*/ void LocoIOData::addPropertyChangeListener(PropertyChangeListener* pcl) {
    dataListeners->SwingPropertyChangeSupport::addPropertyChangeListener(pcl);
}

/*public*/ void LocoIOData::removePropertyChangeListener(PropertyChangeListener* pcl) {
    dataListeners->removePropertyChangeListener(pcl);
}

/*public*/ void LocoIOData::propertyChange(PropertyChangeEvent* evt) {
    QString s = "LocoIOData: " + evt->getPropertyName() +
               " := "   + evt->getNewValue().toString() +
               " from " + evt->getSource()->metaObject()->className();
    //System.out.println(s);
    qDebug()<< s;
}
#endif

/**
 * Address and SubAddress of this device
 *<p>
 * High byte of the Address is fixed to 0x01
 *<p>
 * Low byte Address must be in the range of
 * 0x01 .. 0x4F, 0x51 .. 0x7F
 * <P>
 * 0x50 is reserved for the LocoBuffer
 *<p>
 *The subAddress is in the range of 0x01 .. 0x7E
 *<p>
 * 0x7f is reserved
 */
/*public*/ void LocoIOData::setUnitAddress(int unit, int unitSub)
{
 setUnitAddress(unit);
 setUnitSubAddress(unitSub);
}

/*public synchronized*/ void LocoIOData::changeUnitAddress(int unit, int unitSub)
{
 QMutexLocker locker(&mutex5);
//    setUnitAddress(unit);
//    setUnitSubAddress(unitSub);
//    if(unitAddress == 0)
//    {
//     sendWriteCommand(0, 0, 1, unit); // broadcast!
//     setUnitAddress(unit);
//     sendWriteCommand(0, 0, 2, unitSub); // broadcast
//     setUnitAddress(unitSub);
//    }
 bool bResult = false;
 if(unitAddress != (unit & 0xFF))
 {
  sendWriteCommand(unitAddress, unitSubAddress, 1, unit&0xFF);
  bResult = checkWriteResponse(unitAddress, unitSubAddress, 1, unit&0xFF);
  if(bResult)
   setUnitAddress(unit);
  else return; //error
 }
 sendWriteCommand(unitAddress, unitSubAddress, 2, unitSub);
 bResult = checkWriteResponse(unitAddress, unitSubAddress, 2, unitSub);
 if(bResult)
  setUnitSubAddress(unitSub);
}

/*public synchronized*/ void LocoIOData::setUnitAddress(int unit)
{
 QMutexLocker locker(&mutex6);
 //dataListeners.firePropertyChange("UnitAddress", Integer.valueOf(unitAddress), Integer.valueOf(0x0100 | (unit&0x07F))); I
 emit notifyPropertyChange(new PropertyChangeEvent((QObject*)this,"UnitAddress", QVariant(unitAddress), QVariant(0x0100 | (unit&0x07F))));
 unitAddress    = 0x0100 | (unit&0x07F);  // protect against high bits set
}
/*public synchronized*/ void LocoIOData::setUnitSubAddress(int unitSub)
{
 QMutexLocker locker(&mutex7);
 //dataListeners.firePropertyChange("UnitSubAddress", Integer.valueOf(unitSubAddress), Integer.valueOf(unitSub & 0x07F));
 emit notifyPropertyChange(new PropertyChangeEvent((QObject*)this,"UnitSubAddress", QVariant(unitSubAddress), QVariant(unitSub & 0x07F)));
 unitSubAddress = unitSub & 0x07F;
}

/*public synchronized*/ int LocoIOData::getUnitAddress()
{
 QMutexLocker locker(&mutex8);
 return unitAddress & 0x07F;
}
/*public synchronized*/ int LocoIOData::getUnitSubAddress()
{
 QMutexLocker locker(&mutex9);
 return unitSubAddress & 0x07F;
}

/**
 * TODO: LocoIO Board level configuration
 *<p>
 * Bit 0: 0 =default, 1=Port Refresh<br>
 * Bit 1: 0 = Fixed code PBs, 1= Alternated code PBs<br>
 * Bit 2: 0 = default - Not used<br>
 * Bit 3: 0 = default, 1 = Ports 5-12 are Servo Ports<br>
 * Bit 4-7: Blink Rate<br>
 */
/*public*/ void LocoIOData::setUnitConfig(int portRefresh, int altCodePBs, int isServo, int blinkRate, int is4Pos) {
    int newsv0 = ((portRefresh & 0x01) ) |  // bit 0
          ((altCodePBs  & 0x01) << 0x01) |  // bit 1
                                            // bit 2 left at zero
          ((is4Pos      & 0x01) << 0x02) |  // bit 2
          ((isServo     & 0x01) << 0x03) |  // bit 3
          ((blinkRate   & 0x0F) << 0x04);   // bits 4-7
    //dataListeners.firePropertyChange("UnitConfig", Integer.valueOf(sv0), Integer.valueOf(newsv0));
    int oldsv0 = sv0;
    sv0 = newsv0;
    setDirty(true);
    emit notifyPropertyChange(new PropertyChangeEvent((QObject*)this,"UnitConfig", QVariant(oldsv0), QVariant(sv0)));
}
/*public*/ int LocoIOData::getUnitConfig() {
    return sv0 & 0xFF;
}
int LocoIOData::getBlinkRate()
{
 return (sv0 & 0xF0) >> 4;
}
void LocoIOData::setBlinkRate(int iBlinkRate)
{
 Q_ASSERT(iBlinkRate >=0 && iBlinkRate<=15);
 int oldsv0 = sv0;
 sv0 = (sv0 & 0xF) | (iBlinkRate << 4);
 emit notifyPropertyChange(new PropertyChangeEvent((QObject*)this,"UnitConfig", QVariant(oldsv0), QVariant(sv0)));
}

int LocoIOData::getAltCodePBs()
{
 return (sv0 & 0x02)>>1;
}

void LocoIOData::setAltCodePBs(int val)
{
 int oldsv0 = sv0;
 int newVal = val==0?0:1;
 sv0 = (sv0 & 0xFD) | (newVal << 1);
 emit notifyPropertyChange(new PropertyChangeEvent((QObject*)this,"UnitConfig", QVariant(oldsv0), QVariant(sv0)));
}

int LocoIOData::getIsServo()
{
 return (sv0 & 0x08)>>3;
}

void LocoIOData::setIsServo(int val)
{
 int oldsv0 = sv0;
 int newVal = (val==0)?0:1;
 sv0 = (sv0 & 0xF3) | (newVal << 3);
 emit notifyPropertyChange(new PropertyChangeEvent((QObject*)this,"UnitConfig", QVariant(oldsv0), QVariant(sv0)));
}

void LocoIOData::setIs4Pos(int val)
{
 int oldsv0 = sv0;
 int newVal = (val==0)?0:1;
 sv0 = (sv0 & 0xFB) | (newVal << 2);
 emit notifyPropertyChange(new PropertyChangeEvent((QObject*)this,"UnitConfig", QVariant(oldsv0), QVariant(sv0)));
}

int LocoIOData::getIsBooster()
{
 return (sv0 & 0x04)>>2; // TODO: determine how to set this
}

void LocoIOData::setIsBooster(int val)
{
 int oldsv0 = sv0;
 int newVal = val==0?0:1;
 sv0 = (sv0 & 0xF3) | (newVal << 2);
 emit notifyPropertyChange(new PropertyChangeEvent((QObject*)this,"UnitConfig", QVariant(oldsv0), QVariant(sv0)));
}

/*public*/ void LocoIOData::setLBVersion(QString version)
{
 locoBufferVersion = version;
 //dataListeners.firePropertyChange("LBVersionChange", "", locoBufferVersion);
 emit notifyPropertyChange(new PropertyChangeEvent((QObject*)this,"LBVersionChange", QVariant(""), QVariant(locoBufferVersion)));
}
/*public*/ QString LocoIOData::getLBVersion() {
    return locoBufferVersion;
}
/*public*/ void LocoIOData::setLIOVersion(QString version)
{
 locoIOVersion = version;
 //dataListeners.firePropertyChange("LIOVersionChange", "", locoIOVersion);
 emit notifyPropertyChange(new PropertyChangeEvent((QObject*)this,"LIOVersionChange", QVariant(""), QVariant(locoIOVersion)));
}
/*public*/ QString LocoIOData::getLIOVersion()
{
 return locoIOVersion;
}

/*public*/ void LocoIOData::setStatus(QString msg)
{
 status = msg;
 //dataListeners.firePropertyChange("StatusChange", "", status);
 emit notifyPropertyChange(new PropertyChangeEvent((QObject*)this,"StatusChange", QVariant(""), QVariant(status)));
}
/*public*/ QString LocoIOData::getStatus()
{
 return status;
}

/*public*/ void LocoIOData::setSV(int channel, int value, QString ss)
{
 int iOld = sv[channel];
 int iNew = sv[channel] = value & 0xFF;
 //dataListeners.firePropertyChange("PortChange", Integer.valueOf(-1), Integer.valueOf(channel));
 emit notifyPropertyChange(new PropertyChangeEvent((QObject*)this,"PortChange", QVariant(-1), QVariant(channel)));
 setDirty(channel, !(ss == ssGreen || ss == ssPurple));
 emit SVChanged(channel, iOld, iNew, ss);
}

/*public*/ int LocoIOData::getSV(int channel) {
    return sv[channel] & 0xFF;
}
/*public*/ void LocoIOData::setV1(int channel, LocoIOMode* l, int address, QString ss)
{
 //Q_UNUSED(address)
 setV1(channel, validmodes->addressToValue1(l, address),!ss.isEmpty()?ss:ssGreen);
}
/*public*/ void LocoIOData::setV1(int channel, int value, QString ss) {
 int iOld = v1[channel];
 int iNew = v1[channel] = value & 0x7FF;
    //dataListeners.firePropertyChange("PortChange", Integer.valueOf(-1), Integer.valueOf(channel));
    emit notifyPropertyChange(new PropertyChangeEvent((QObject*)this,"PortChange", QVariant(-1), QVariant(channel)));
 setDirty(channel, !(ss == ssGreen || ss == ssPurple));
 emit V1Changed(channel, iOld, iNew, ss);
}
/*public*/ int LocoIOData::getV1(int channel) {
    return v1[channel] & 0x7FF;
}
/*public*/ void LocoIOData::setV2(int channel, LocoIOMode* l, int address, QString ss)
{
 //Q_UNUSED(address)
 setV2(channel, validmodes->addressToValue2(l,address),!ss.isEmpty()?ss:ssGreen);
}
/*public*/ void LocoIOData::setV2(int channel, int value, QString ss)
{
 int iOld = v2[channel];
 int iNew = v2[channel] = value & 0xFF;
 //dataListeners.firePropertyChange("PortChange", Integer.valueOf(-1), Integer.valueOf(channel));
 emit notifyPropertyChange(new PropertyChangeEvent((QObject*)this,"PortChange", QVariant(-1), QVariant(channel)));
 setDirty(channel, !(ss == ssGreen || ss == ssPurple));
 emit V2Changed(channel, iOld, iNew, ss);
}

/*public*/ int LocoIOData::getV2(int channel) {return v2[channel] & 0xFF;}

/**
 * The addr field (for the address info used in each LocoIO channel)
 *
 * @param channel integer value of the addresses in use for this row (0=invalid)
 */
/*public*/ void LocoIOData::setAddr(int channel, int value, QString ss)
{
 int iOld = addr[channel];
 int iNew = addr[channel] = value & 0x7FF;
 //dataListeners.firePropertyChange("PortChange", Integer.valueOf(-1), Integer.valueOf(channel));
 emit notifyPropertyChange(new PropertyChangeEvent((QObject*)this,"PortChange", QVariant(-1), QVariant(channel)));
 emit AddrChanged(channel, iOld, iNew, ss);
 if(channel < 16)
 {
  LocoIOMode* lim = getLIM(channel);
  LocoIOModeList l;
  if(lim  != nullptr)
  {
   QString ssNew = ss==ssBlueGreen?ssGreen:ss;
   setV1(channel, l.addressToValue1(lim,value),ssNew);
   //setV2(channel, l.addressToValue2(lim,v2[channel]&0xff),ssNew);
  }
  else
   setV1(channel, (value-1)/2,ss);
 }
}
/*public*/ int LocoIOData::getAddr(int channel) {
    return addr[channel] & 0x7FF;
}
/*public*/ void LocoIOData::setX2SV(int channel, int value, QString ss) {
    int iOld = x2sv[channel];
    int iNew = x2sv[channel] = value & 0xFF;
    //dataListeners.firePropertyChange("PortChange", Integer.valueOf(-1), Integer.valueOf(channel));
    //emit firePropertyChange("PortChange", QVariant(-1), QVariant(channel));
    setX2Dirty(channel, !(ss == ssGreen || ss == ssPurple));
    emit X2SVChanged(channel, iOld, iNew, ss);
}
/*public*/ int LocoIOData::getX2SV(int channel) {
    return x2sv[channel] & 0xFF;
}
/*public*/ void LocoIOData::setX2V1(int channel, LocoIOMode* l, int address) {
    Q_UNUSED(address)
    setX2V1(channel, validmodes->addressToValue1(l, getAddr(channel)),ssGreen);
}
/*public*/ void LocoIOData::setX2V1(int channel, int value, QString ss) {
 int iOld = x2v1[channel];
 int iNew = x2v1[channel] = value & 0x7FF;
    //dataListeners.firePropertyChange("PortChange", Integer.valueOf(-1), Integer.valueOf(channel));
    //emit firePropertyChange("PortChange", QVariant(-1), QVariant(channel));
 setX2Dirty(channel, !(ss == ssGreen || ss == ssPurple));
 emit X2V1Changed(channel, iOld, iNew, ss);
}

/*public*/ int LocoIOData::getX2V1(int channel) {
    return x2v1[channel] & 0x7FF;
}

/*public*/ void LocoIOData::setX2V2(int channel, LocoIOMode* l, int address) {
    Q_UNUSED(address)
    setX2V2(channel, validmodes->addressToValue2(l, getAddr(channel)),ssGreen);
}

/*public*/ void LocoIOData::setX2V2(int channel, int value, QString ss) {
    int iOld = x2v2[channel];
    int iNew = x2v2[channel] = value & 0xFF;
    //dataListeners.firePropertyChange("PortChange", Integer.valueOf(-1), Integer.valueOf(channel));
    //emit firePropertyChange("PortChange", QVariant(-1), QVariant(channel));
    setX2Dirty(channel, !(ss == ssGreen || ss == ssPurple));
    emit X2V2Changed(channel, iOld, iNew, ss);
}
/*public*/ int LocoIOData::getX2V2(int channel) {
    return x2v2[channel] & 0xFF;
}

/*public*/ void LocoIOData::setServoP1(int iServo, int value, QString ss) {
 int iOld = servoP1[iServo];
 int iNew = servoP1[iServo] = value & 0xFF;
    //dataListeners.firePropertyChange("PortChange", Integer.valueOf(-1), Integer.valueOf(channel));
    //emit firePropertyChange("PortChange", QVariant(-1), QVariant(channel));
 setServoDirty(iServo, !(ss == ssGreen || ss == ssPurple));
 emit ServoP1Changed(iServo, iOld, iNew, ss);
}

/*public*/ void LocoIOData::setServoP2(int iServo, int value, QString ss) {
 int iOld = servoP2[iServo];
 int iNew = servoP2[iServo] = value & 0xFF;
    //dataListeners.firePropertyChange("PortChange", Integer.valueOf(-1), Integer.valueOf(channel));
    //emit firePropertyChange("PortChange", QVariant(-1), QVariant(channel));
 setServoDirty(iServo, !(ss == ssGreen || ss == ssPurple));
 emit ServoP2Changed(iServo, iOld, iNew, ss);
}

/*public*/ void LocoIOData::setServoSpeed(int iServo, int value, QString ss) {
 int iOld = servoSpd[iServo];
 int iNew = servoSpd[iServo] = value & 0xFF;
    //dataListeners.firePropertyChange("PortChange", Integer.valueOf(-1), Integer.valueOf(channel));
    //emit firePropertyChange("PortChange", QVariant(-1), QVariant(channel));
 setServoDirty(iServo, !(ss == ssGreen || ss == ssPurple));
 emit ServoSpeedChanged(iServo, iOld, iNew, ss);
}

int LocoIOData::getServoP1(int iServo) { return servoP1[iServo] & 0xFF;}
int LocoIOData::getServoP2(int iServo) { return servoP2[iServo] & 0xFF;}
int LocoIOData::getServoSpeed(int iServo) { return servoSpd[iServo] & 0xFF;}

void LocoIOData::setSV7D(int data) { sv7D = data;}
void LocoIOData::setSV7E(int data) { sv7E = data;}
void LocoIOData::setSV7F(int data) { sv7F = data;}
int LocoIOData::getSV7D() { return sv7D;}
int LocoIOData::getSV7E() { return sv7E;}
int LocoIOData::getSV7F() { return sv7F;}

void LocoIOData::readSV0()
{
 readState0 = READVALUE1; //READ;
 writeState0 = NONE;

 lastOpCv = -1;
 issueNext0Operation();
 connect(this, SIGNAL(IOComplete0()), this, SLOT(readWriteNext()));
}

void LocoIOData::readSV125()
{
 readState125 = READVALUE1; //READ;
 writeState125 = NONE;

 lastOpCv = -1;
 issueNext0Operation();
 connect(this, SIGNAL(IOComplete0()), this, SLOT(readWriteNext()));
}


void LocoIOData::readSV7D()
{
 readState7D = READ;
 writeState7D = NONE;
 lastOpCv = -1;
 issueNext7DOperation();
}

void LocoIOData::writeSV7D()
{
 readState7D = NONE;
 writeState7D = WRITEMODE;
 issueNext7DOperation();
}

/**
 * The addr field (for the address info used in each LocoIO channel)
 *
 * @param channel integer value of the addresses in use for this row (0=invalid)
 */
/*public*/ void LocoIOData::setX2Addr(int channel, int value, QString ss) {
    int iOld = x2addr[channel];
    int iNew = x2addr[channel] = value & 0x7FF;
    //dataListeners.firePropertyChange("PortChange", Integer.valueOf(-1), Integer.valueOf(channel));
    //emit firePropertyChange("PortChange", QVariant(-1), QVariant(channel));
    emit X2AddrChanged(channel, iOld, iNew, ss);
}
/*public*/ int LocoIOData::getX2Addr(int channel) {
    return x2addr[channel] & 0x7FF;
}

/*public*/ void LocoIOData::setMode(int channel, QString m) {
    mode[channel] = m;
    //dataListeners.firePropertyChange("PortChange", Integer.valueOf(-1), Integer.valueOf(channel));
    emit notifyPropertyChange(new PropertyChangeEvent((QObject*)this,"PortChange", QVariant(-1), QVariant(channel)));
}
/*public*/ QString LocoIOData::getMode(int channel) {
    return mode[channel];
}

/*public*/ void LocoIOData::setLIM(int channel, QString s) {
    if (validmodes != nullptr) {
        setLIM(channel, validmodes->getLocoIOModeFor(s));
    }
}
/*public*/ void LocoIOData::setLIM(int channel) {
    if (validmodes != nullptr)
    {
     setLIM(channel, validmodes->getLocoIOModeFor(getSV(channel),getV1(channel),getV2(channel)));
    }
}
/*public*/ void LocoIOData::setLIM(int channel, LocoIOMode* m)
{
 lim[channel] = m;
 //dataListeners.firePropertyChange("PortChange", Integer.valueOf(-1), Integer.valueOf(channel));
 emit notifyPropertyChange(new PropertyChangeEvent((QObject*)this, "PortChange", QVariant(-1), QVariant(channel)));
}
/*public*/ LocoIOMode* LocoIOData::getLIM(int channel)
{
 if(channel >= lim.count())
     return nullptr;
 return lim[channel];
}
/*public*/ void LocoIOData::readValues(int channel)
{
 log->debug(tr("read channel %1").arg(channel));
 for(int row=0; row < _numRows*2; row++)
 {
  readState[row]= NONE;
  writeState[row]=NONE;
 }
 readState[channel] = READ;
 //readState[channel+16]= READ;
 addr[channel]=0;
 sv[channel]=0;
 v1[channel]=0;
 v2[channel]=0;
 lastOpCv = -1;
 vals = nullptr;
 issueNextOperation();
}
/*public*/ void LocoIOData::readX2Values(int channel) {
    log->debug(tr("read channel %1").arg(channel));
    for(int row=0; row < _numRows; row++)
    {
     readStateX2[row]= NONE;
     writeStateX2[row]=NONE;
    }
    readStateX2[channel] = READ;
    x2addr[channel]=0;
    x2sv[channel]=0;
    x2v1[channel]=0;
    x2v2[channel]=0;
    lastOpCv = -1;
    vals = nullptr;
    issueNextExtra2Operation();
}

/*public*/ void LocoIOData::readServoValues(int iServo) {
    log->debug(tr("read channel %1").arg(iServo));
    for(int row=0; row < _numRowsServo; row++)
    {
     readStateServo[row]= NONE;
     writeStateServo[row]=NONE;
    }
    readStateServo[iServo] = READ;
    //x2addr[channel]=0;
    servoP1[iServo]=0;
    servoP2[iServo]=0;
    servoSpd[iServo]=0;
    lastOpCv = -1;
    vals = nullptr;
    issueNextServoOperation();
}

/*public*/ void LocoIOData::captureValues(int channel) {
    capture[channel] = true;
}

/*public*/ void LocoIOData::writeValues(int channel)
{
 vals = nullptr;
 for(int row=0; row < _numRows*2; row++)
 {
  readState[row]= NONE;
  writeState[row]=NONE;
 }
 writeState[channel] = WRITE;
 //writeState[channel+16] = WRITE;
 issueNextOperation();
}
/*public*/ void LocoIOData::writeX2Values(int channel)
{
 vals = nullptr;
 for(int row=0; row < _numRows; row++)
 {
  readStateX2[row]= NONE;
  writeStateX2[row]=NONE;
 }
 writeStateX2[channel] = WRITE;
 issueNextExtra2Operation();
}
/*public*/ void LocoIOData::writeServoValues(int channel)
{
 vals = nullptr;
 for(int row=0; row < _numRowsServo; row++)
 {
  readStateServo[row]= NONE;
  writeStateServo[row]=NONE;
 }
 writeStateServo[channel] = WRITE;
 issueNextServoOperation();
}


/**
 * Start reading all rows back (base and Extra1)
 */
/*public*/ void LocoIOData::readAll()
{
 // System.out.println("readAll()");
 qDebug()<<"readAll()";
 for (int row=0; row<_numRows*2; row++)
 {
  readState[row] = READ;
  writeState[row] = NONE;
  if(row < 16)
   lim[row] = nullptr;
 }
 lastOpCv = -1;
 vals = nullptr;
 reading = true;  // false means write in progress
 issueNextOperation();
}

/**
 * Start reading all Extra2 rows back
 */
/*public*/ void LocoIOData::readAllX2()
{
 // System.out.println("readAll()");
 qDebug()<<"readAllX2()";
 for (int row=0; row<_numRows; row++)
 {
  readStateX2[row] = READ;
  writeStateX2[row] = NONE;
  //x2lim[row] = NULL;
 }
 lastOpCv = -1;
 vals = nullptr;
 reading = true;  // false means write in progress
 issueNextExtra2Operation();
}

/*public*/ void LocoIOData::readAllServo()
{
 qDebug()<<"readAllServo()";
 for (int row=0; row<_numRowsServo; row++)
 {
  readStateServo[row] = READ;
  writeStateServo[row] = NONE;
 }
 lastOpCv = -1;
 vals = nullptr;
 reading = true;  // false means write in progress
 issueNextServoOperation();
}
void LocoIOData::readAllCVs()
{
 bReadingAll = true;
 bWritingAll = false;
 readWriteState=0;
 connect(this, SIGNAL(IOComplete(QList<int>*)), this, SLOT(readWriteNext()));
 connect(this, SIGNAL(IOCompleteX2(QList<int>*)), this, SLOT(readWriteNext()));
 connect(this, SIGNAL(IOCompleteServo()), this, SLOT(readWriteNext()));
 connect(this, SIGNAL(IOComplete7D()), this, SLOT(readWriteNext()));
 readAll();
}
void LocoIOData::writeAllCVs()
{
 bReadingAll = false;
 bWritingAll = true;
 readWriteState=0;
 connect(this, SIGNAL(IOComplete(QList<int>*)), this, SLOT(readWriteNext()));
 connect(this, SIGNAL(IOCompleteX2(QList<int>*)), this, SLOT(readWriteNext()));
 connect(this, SIGNAL(IOCompleteServo()), this, SLOT(readWriteNext()));
 connect(this, SIGNAL(IOComplete7D()), this, SLOT(readWriteNext()));
 writeAll();
}
void LocoIOData::readWriteNext()
{
 if(bReadingAll)
 {
  switch(readWriteState)
  {
  case 0:
   readWriteState = 1;
   readAllX2();
   break;
  case 1:
   readWriteState = 2;
   if(getIsServo()==1)
   {
    readAllServo();
   }
   break;
  case 2:
   readWriteState = 3;
   readSV7D();
   break;
  case 3:
   readWriteState = 4;
   emit readAllComplete();
   break;
  default:
   readWriteState = -1;
   bReadingAll = false;
   disconnect(this, SIGNAL(IOComplete(QList<int>*)), this, SLOT(readWriteNext()));
   disconnect(this, SIGNAL(IOCompleteX2(QList<int>*)), this, SLOT(readWriteNext()));
   disconnect(this, SIGNAL(IOCompleteServo()), this, SLOT(readWriteNext()));
   disconnect(this, SIGNAL(IOComplete7D()), this, SLOT(readWriteNext()));
   break;
  }
 }
 if(bWritingAll)
 {
  switch(readWriteState)
  {
  case 0:
   readWriteState = 1;
   writeAllX2();
   break;
  case 1:
   if(getIsServo()==1)
   {
    readWriteState = 2;
    writeAllServo();
    break;
   }
   break;
  case 2:
   readWriteState =3;
   writeSV7D();
   break;
  case 3:
   emit writeAllComplete();
  default:
   readWriteState = -1;
   bWritingAll = false;
   disconnect(this, SIGNAL(IOComplete(QList<int>*)), this, SLOT(readWriteNext()));
   disconnect(this, SIGNAL(IOCompleteX2(QList<int>*)), this, SLOT(readWriteNext()));
   disconnect(this, SIGNAL(IOCompleteServo()), this, SLOT(readWriteNext()));
   disconnect(this, SIGNAL(IOComplete7D()), this, SLOT(readWriteNext()));
   break;
  }
 }
}

/**
 * Start writing all rows out (base registers and Extra1 registers)
 */
/*public*/ void LocoIOData::writeAll()
{
 for (int row=0; row<_numRows*2; row++)
 {
  writeState[row] = WRITE;
 }
 vals = nullptr;
 //connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));

 issueNextOperation();
}
// Write all Extra2 values.
/*public*/ void LocoIOData::writeAllX2()
{
 for (int row=0; row<_numRows; row++)
 {
  writeStateX2[row] = WRITE;
 }
 vals = nullptr;
 //connect(timer, SIGNAL(timeout()), this, SLOT(timeoutX2()));
 issueNextExtra2Operation();
}
// write all servo values.
/*public*/ void LocoIOData::writeAllServo()
{
 for (int row=0; row<_numRowsServo; row++)
 {
  writeStateServo[row] = WRITE;
 }
 vals = nullptr;
 //connect(timer, SIGNAL(timeout()), this, SLOT(timeoutServo()));
 issueNextServoOperation();
}

/*public*/ LocoIOModeList* LocoIOData::getLocoIOModeList() {
    return validmodes;
}


/*protected*/ int LocoIOData::highPart(int value) { // generally value 1
    return value/256;
}

/*protected*/ int LocoIOData::lowPart(int value) { // generally value 2
    return value-256*highPart(value);
}

/*private*/ QString LocoIOData::dotme(int val)
{
 int dit;
 int x = val;
 QString ret;// = new StringBuffer();
 if (val == 0) return "0";
 while (x != 0)
 {
  dit = x % 10;
  ret.insert(0,QString("%1").arg(dit));
  x = x / 10;
  if (x != 0) ret.insert(0, ".");
 }
 return ret/*.toString()*/;
}

/**
 * Listen to the LocoNet.
 * We're listening for incoming OPC_PEER_XFR messages, which might
 * be part of a read or write sequence.  We're also
 * _sometimes_ listening for commands as part of a "capture"
 * operation.issueNextOperation
 *<P>
 * The incoming LocoNet OPC_PEER_XFR messages don't retain any information
 * about the CV number or whether it was a read or write operation.
 * We store the data regardless of whether it was read or write, but
 * we need to remember the cv number in the lastOpCv member.
 *<P>
 * @param m Incoming message
 */
/*public synchronized*/ void LocoIOData::message(LocoNetMessage* m)
{
 //QMutexLocker locker1(&mutex1);
 // sort out the opCode
 int opCode = m->getOpCode();
 switch (opCode)
 {
 case LnConstants::OPC_PEER_XFER:
 {
  if(m->getElement(4)== 0x01)
  {
   // could be read or write operation
   // check that src_low_address is our unit, and
   // dst is "our" LocoBufferAddress
   int src = m->getElement(2);
   int dst = m->getElement(3)+m->getElement(4)*256;
   QVector<int> packet = m->getPeerXfrData();

   if ( src == lowPart(LocoBufferAddress))
   {
    QString lbv = ((packet[2] != 0) ?  dotme(packet[2]) : "1.0");
    setLBVersion(lbv);
   }
   //qDebug()<< QString("dst=%1 src=%2 unitAddr=%3").arg(dst,0,16).arg(src,0,16).arg(packet[4]);
   if(dst==LocoBufferAddress && m->getElement(7) == 0 && bProbing)
   {
    probeTimer->stop();
    stopTimer();
    log->debug( QString("probe %1 %2").arg(src).arg(packet[4]));
    locoIOAddress = new LocoIOAddress(src, packet.at(4));
//    paddr.unitAddr = src;
//    paddr.unitSubAddr = packet[4];
    firmwareVersion = ((packet[2] != 0) ? dotme(packet[2]) : "1.3.2");
    //setLIOVersion(fw);
    locoIOAddress->setFirmwareVersion(firmwareVersion);
    if(packet[2] == 0)
     locoIOAddress->setModuleType("<unknown>");
    else
     if(packet[2] >=1 && packet[2]<=4)
      locoIOAddress->setModuleType("LocoBooster");
     else
      if(packet[2] >=100 && packet[2]<=104)
       locoIOAddress->setModuleType("LocoServo");
      else
       if(packet[2] >=141 && packet[2]<=151)
        locoIOAddress->setModuleType("LocoIO");
       else
        locoIOAddress->setModuleType("<unknown>");
    bool bFound = false;
    foreach(LocoIOAddress* other, probedAddresses)
    {
     if(*other == *locoIOAddress )
      bFound = true;
    }
    if(!bFound)
     probedAddresses.append(locoIOAddress);
    probeTimer->start(TIMEOUT*2);
    timeoutcounter=1;
//   mutex1.unlock();
//   return;

   }
   if (dst==LocoBufferAddress && src==lowPart(unitAddress) && (packet[4] == unitSubAddress) )
   {
    // yes, we assume this is a reply to us
    stopTimer();
    replyReceived(); // advance state
    if((m->getElement(7) == 0) && bReadingConfig )
    {
     sv0 = (packet[2] != 0) ? packet[5] : packet[7];
     sv1 = (packet[2] != 0) ? packet[4] : packet[6];
     sv2 = (packet[2] != 0) ? packet[3] : packet[5];
     QString fw = ((packet[2] != 0) ? dotme(packet[2]) : "1.3.2");
     setLIOVersion(fw);
     if(packet[2] == 0)
      moduleType = "<unknown>";
     else
      if(packet[2] >=1 && packet[2]<=4)
      {
       moduleType = "LocoBooster";
       if((sv0 & 0x0C) != 0x04)
       {
        sv0 = (sv0& 0x0c) | 0x04;
       }
      }
      else
       if(packet[2] >=100 && packet[2]<=104)
       {
        moduleType = "LocoServo";
        if((sv0 & 0x0C) != 0x08)
        {
         sv0 = (sv0& 0x0c) | 0x08;
        }
       }
       else
        if(packet[2] >=141 && packet[2]<=151)
        {
         moduleType = "LocoIO";
         if((sv0 & 0x0C )!= 0x00)
         {
          sv0 = (sv0& 0x0c);
         }
        }
        else
         moduleType = "<unknown>";


     bReadingConfig = false;
     //mutex1.unlock();
     emit configRead((packet[2] != 0) ? packet[5] : packet[7],this);
     return; // done
    }
    if(bReadingOption)
    {
     emit optionByte(m->getElement(7),  (packet[2] != 0) ? packet[5] : packet[7]);
     bReadingOption=false;
    }
    if(bSettingOption)
     bSettingOption = false;
    if(vals != nullptr)
    {
     vals->replace(m->getElement(7),  (packet[2] != 0) ? packet[5] : packet[7]);
     emit cvRead(m->getElement(7),  (packet[2] != 0) ? packet[5] : packet[7]);
     lastOpCv++;
     if(lastOpCv < _defaults.size())
      issueNextReadCv();
     //mutex1.unlock();
     return;
    }
    //replyReceived(); // advance state

    QString fw = ((packet[2] != 0) ? dotme(packet[2]) : "1.3.2");
    setLIOVersion(fw);
    if (packet[0] == LocoIO::LOCOIO_SV_READ || reading)
    {  // read command
     if(packet[1] != lastOpCv)
     {
      qDebug()<< tr("read %1 expecting %2").arg(packet[1]).arg(lastOpCv);
      //LlnMon mon;
      qDebug()<< LocoNetMessageInterpret::interpretMessage(m, "LT", "LS", "LR");
      if(lastOpCv >0)
       sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
      //mutex1.unlock();
      return;
     }
     //replyReceived(); // advance state

    // get data and store
//                if (lastOpCv>=0 && lastOpCv<=50) {
    //if (lastOpCv>=0 && lastOpCv<=146)
     // there are two formats of the return packet...
     int data = (packet[2] != 0) ? packet[5] : packet[7];
     int data1 = (packet[2] != 0) ? packet[6] : -1;
     int data2 = (packet[2] != 0) ? packet[7] : -1;

     if(lastOpCv == 0)
     {
      sv0a = data;
      sv1 = data1;
      sv2 = data2;
     } else
     if (lastOpCv>=0 && lastOpCv<=98) // LocoIO SVs
     {

      int channel = (lastOpCv/3)-1;
      if (channel<0)
      {
       log->warn("... channel is less than zero!!!");
       channel = 0;
      }
      int type = lastOpCv - (channel*3+3);
      // type = 0 for cv, 1 for value1, 2 for value2
      // We can't update the mode until we have all three values
      // Sequence (from state machine below) is V2, V1, Mode
      log->debug("... updating port "+QString("%1").arg(channel)
                                      +" SV" + QString("%1").arg(type)
                                      + "("
                                      + (type == 1 ? "value1"
                                       : type == 2 ? "value2"
                                       : type == 0 ? "mode"
                                       :             "unknown")
                                      + ") = 0x"
                                      + QString("%1").arg(data, 0, 16));
      switch (type)
      {
      case 2: // v2
       setV2(channel,data, ssGreen);
       if(channel < 16)
        setMode(channel, "<none>");
       break;
      case 1:     // v1
       setV1(channel, data, ssGreen);
       if(channel < 16)
        setMode(channel, "<none>");
       if(channel >= 16)
        setAddr(channel, (data*2)+1, ssBlueGreen);
       break;
      case 0:       // cv
      {
       if(b3ByteRead)
       {
        setV1(channel, data1, ssGreen);
        setV2(channel, data2, ssGreen);
       }
       setSV(channel, data, ssGreen);
       if(channel >= 16)
       {
        setAddr(channel, (data1*2)+1, ssBlueGreen);
        break;
       }
       // Now that we have all the pieces, recalculate mode
       if(channel < 16)
       {
        LocoIOMode* lim = validmodes->getLocoIOModeFor(getSV(channel), getV1(channel), getV2(channel));
        if (lim == nullptr)
        {
         setMode(channel, "<none>");
         setAddr(channel, 0, ssWhite);
         log->debug(tr("Could not find mode! '%1' SV=%2 V1=%3 V2=%4").arg(data,0,16).arg(getSV(channel),0,16).arg(getV1(channel)).arg(getV2(channel),0,16));
        }
       else
        {
         setMode(channel, lim->getFullMode());
         setAddr(channel, validmodes->valuesToAddress(lim->getOpcode(),getSV(channel), getV1(channel), getV2(channel)),ssBlueGreen);
        }
       }
       log->debug(QString("... decoded address (")+
                    "cv="+ QString("0x%1").arg(getSV(channel),0,16)+" " +
                    "v1="+ QString("0x%1").arg(getV1(channel),0,16)+" " +
                    "v2="+ QString("0x%1").arg(getV2(channel),0,16)+") " +
                    "is "+ QString("%1").arg(getAddr(channel)) + "(0x" + QString("%1").arg(getAddr(channel),0,16) + ")");
       break;
      }
      default:
       log->warn("OPC_PEER_XFR: Type (" + QString("%1").arg(type) + ") is not {0,1,2} for channel " + QString::number(channel));
       break;
      }
     }
     else if((lastOpCv >=101 && lastOpCv < 125) && locoIOVersion == "1.0.4")  // servo values
     {
      // there are two formats of the return packet...
      //int data = (packet[2] != 0) ? packet[5] : packet[7];
      int iServo = ((lastOpCv-101)/3);
      if (iServo<0)
      {
       log->warn("... iServo is less than zero!!!");
       iServo = 0;
      }
      int type = (lastOpCv - 101)%3;
      // type = 0 for cv, 1 for value1, 2 for value2
      // We can't update the mode until we have all three values
      // Sequence (from state machine below) is V2, V1, Mode
      log->debug("... updating servo "+QString("%1").arg(iServo)
                                         +" SV" + QString("%1").arg(type)
                                         + "("
                                         + (type == 1 ? "Pos2"
                                         :  type == 2 ? "Speed"
                                         :  type == 0 ? "Pos1"
                                         :              "")
                                         + ") = 0x"
                                         + QString("%1").arg(data, 0, 16));
      switch (type)
      {
      case 2: // v2
       setServoSpeed(iServo,data, ssGreen);
       //setMode(iServo, "<none>");
       break;
      case 1:     // v1
       setServoP2(iServo, data, ssGreen);
       //setMode(channel, "<none>");
       break;
      case 0:       // cv
      {
       if(b3ByteRead)
       {
        setServoP2(iServo, data1, ssGreen);
        setServoSpeed(iServo, data2, ssGreen);
       }
       setServoP1(iServo, data, ssGreen);
       break;
      }
      default:
       log->warn("OPC_PEER_XFR: Type (" + QString("%1").arg(type) + ") is not {0,1,2} for channel " + QString::number(iServo));
       break;
      }
     }
     else if(lastOpCv >=125 && lastOpCv <=127)  // SV7D
     {
      int type = (lastOpCv - 125)%3;
      // type = 0 for cv, 1 for value1, 2 for value2
      // We can't update the mode until we have all three values
      // Sequence (from state machine below) is V2, V1, Mode
      switch (type)
      {
      case 2: // v2
       setSV7F(data);
       break;
      case 1:     // v1
       setSV7E(data);
       break;
      case 0:       // cv
       {
       if(b3ByteRead)
       {
        setSV7E(data1);
        setSV7F(data2);
       }
       setSV7D(data);
       break;
      }
      default:
       log->warn("OPC_PEER_XFR: Type (" + QString("%1").arg(type) + ") is not {0,1,2} for 7D-7F " );
       break;
      }
     }

     else
     {
      // Reading Extra2 CVs 101 +
      // there are two formats of the return packet...
      //int data = (packet[2] != 0) ? packet[5] : packet[7];
      int channel = (lastOpCv-128)/3;
      if (channel<0)
      {
       log->warn("... channel is less than zero!!!");
       channel = 0;
      }
      int type = (lastOpCv - 128)%3;
      // type = 0 for cv, 1 for value1, 2 for value2
      // We can't update the mode until we have all three values
      // Sequence (from state machine below) is V2, V1, Mode
      log->debug("... updating port "+QString("%1").arg(channel)
                                         +" SV" + QString("%1").arg(type)
                                         + "("
                                         + (type == 1 ? "value1"
                                         :  type == 2 ? "value2"
                                         :  type == 0 ? "mode"
                                         :              "unknown")
                                         + ") = 0x"
                                         + QString("%1").arg(data, 0, 16));
      switch (type)
      {
      case 2: // X2V2
       setX2V2(channel,data, ssGreen);
       //setMode(channel, "<none>");
       break;
      case 1:     // X2v1
       setX2V1(channel, data, ssGreen);
       //setMode(channel, "<none>");
       setX2Addr(channel, data+1, ssBlueGreen);
       break;
      case 0:       // cv
       if(b3ByteRead)
       {
        setX2V1(channel, data1, ssGreen);
        setX2V2(channel, data2, ssGreen);
       }
       setX2SV(channel, data, ssGreen);
       setX2Addr(channel, data1+1, ssBlueGreen);
       break;
      default:
       log->warn("OPC_PEER_XFR: Type (" + QString("%1").arg(type) + ") is not {0,1,2} for channel " + QString::number(channel));
       break;
      }
     }
//    else
//    {
//    //log->error("last CV recorded is invalid: "+QString("%1").arg(lastOpCv));
//    }
    }  // end of read processing
//    else
//    {
//     if (packet[0] == LocoIO::LOCOIO_SV_WRITE || reading)
//     {
//      replyReceived();
//     }
//    }
    // check for anything else to do
    if(lastOpCv < 101)
     issueNextOperation();
    else if((lastOpCv>=101 && lastOpCv < 125) && locoIOVersion == "1.0.4")
     issueNextServoOperation();
    else if(lastOpCv>=125 && lastOpCv <=127)
     issueNext7DOperation();
    else
     issueNextExtra2Operation();
    //mutex1.unlock();
    return;
   }
   else
   {
    //mutex1.unlock();
    return;
   }
  }
  else
  { // SV programming format 2
   qDebug()<< "LocoIOData: SV programming message 2 ";
  }
 }
 break;
 case LnConstants::OPC_INPUT_REP: // Block Sensors and other general sensor codes
  if (log->isDebugEnabled())
  {
   log->debug(LnConstants::OPC_NAME(opCode) + " received");
  }
  // these might require capture
  for (int i=0; i<_numRows; i++)
  {
   if (capture[i])
   {
    if (log->isDebugEnabled()) log->debug("row set for capture: "+QString::number(i));
    // This is a capture request, get address bytes
    int val1 = m->getElement(1);
    int val2 = m->getElement(2);
    // calculate address from val's, save result, mark as done
    // INPUT_REP's use val2's OPC_SW_REQ_DIR bit as LSB...'
    setAddr(i, (((val2 & 0x0F) << 5) * 256 + ((val1 & 0x7f) << 1)) |
                      (((val2 & LnConstants::OPC_SW_REQ_DIR) == LnConstants::OPC_SW_REQ_DIR) ? 0x01 : 0x00),ssWhite);
    capture[i] = false;
   }
  }
  //mutex1.unlock();
  return;

 case LnConstants::OPC_SW_REQ:    // Turnout SWITCH Request
  if (log->isDebugEnabled())
  {
   log->debug(QString("0x%1").arg(LnConstants::OPC_NAME(opCode)) + " received");
  }
  // these might require capture
  for (int i=0; i<_numRows; i++)
  {
   if (capture[i])
   {
    if (log->isDebugEnabled()) log->debug("row set for capture: "+i);
    // This is a capture request, get address bytes
    int val1 = m->getElement(1);
    int val2 = m->getElement(2);
    // calculate address from val's, save result, mark as done
    int addr = LocoIO::SENSOR_ADR(val1, val2);
    setAddr(i, addr,ssWhite);
    capture[i] = false;
   }
  }
  //mutex1.unlock();
  return;
 default:    // we ignore all other loconet messages
  // if (log->isDebugEnabled()) {
  //     log->debug(LnConstants.OPC_NAME(opCode) + " received (ignored)");
  // }
  //mutex1.unlock();
  break;
 }
 //mutex1.unlock();
}
/**
 * Listen to the LocoNet. We're listening for incoming OPC_PEER_XFR
 * messages, which might be part of a read or write sequence. We're also
 * _sometimes_ listening for commands as part of a "capture" operation.
 * <P>
 * The incoming LocoNet OPC_PEER_XFR messages don't retain any information
 * about the CV number or whether it was a read or write operation. We store
 * the data regardless of whether it was read or write, but we need to
 * remember the cv number in the lastOpCv member.
 * <P>
 * @param m Incoming message
 */
/*public*/ /*synchronized*/ void LocoIOData::message_alt(LocoNetMessage* m)
{
 // sort out the opCode
 int opCode = m->getOpCode();
 switch (opCode)
 {
  case LnConstants::OPC_PEER_XFER:
 {
  // could be read or write operation
  // check that src_low_address is our unit, and
  // dst is "our" LocoBufferAddress
  int src = m->getElement(2);
  int dst = m->getElement(3) + m->getElement(4) * 256;
  QVector<int> packet = m->getPeerXfrData();

  if (src == lowPart(LocoBufferAddress))
  {
   QString lbv = ((packet[2] != 0) ? dotme(packet[2]) : "1.0");
   setLBVersion(lbv);
  }

   if (dst == LocoBufferAddress && src == lowPart(unitAddress) && (packet[4] == unitSubAddress))
   {
    // yes, we assume this is a reply to us
    stopTimer();
    replyReceived(); // advance state

    QString fw = ((packet[2] != 0) ? dotme(packet[2]) : "1.3.2");
    setLIOVersion(fw);
    if (packet[0] == LocoIO::LOCOIO_SV_READ || reading)
    {  // read command
     // get data and store
     if (lastOpCv >= 0 && lastOpCv <= 50)
     {

      // there are two formats of the return packet...
      int data = (packet[2] != 0) ? packet[5] : packet[7];
      int channel = (lastOpCv / 3) - 1;
      if (channel < 0)
      {
       log->warn("... channel is less than zero!!!");
       channel = 0;
      }
      int type = lastOpCv - (channel * 3 + 3);
      // type = 0 for cv, 1 for value1, 2 for value2
      // We can't update the mode until we have all three values
      // Sequence (from state machine below) is V2, V1, Mode
      log->debug("... updating port " + QString::number(channel +1)
              + " SV" + QString::number(type)
              + "("
              + (type == 1 ? "value1"
               : type == 2 ? "value2"
               : type == 0 ? "mode"
               :             "unknown")
              + ") = 0x"
              + QString::number(data,0, 16));
      if (type == 2)
      {            // v2
       setV2(channel, data);
       setMode(channel, "<none>");
      }
      else if (type == 1)
      {     // v1
       setV1(channel, data);
       setMode(channel, "<none>");
      }
      else if (type == 0)
      {       // cv
       setSV(channel, data);
       // Now that we have all the pieces, recalculate mode
       LocoIOMode* lim = validmodes->getLocoIOModeFor(getSV(channel), getV1(channel), getV2(channel));
       if (lim == nullptr)
       {
        setMode(channel, "<none>");
        setAddr(channel, 0);
        log->debug("Could not find mode!");
       }
       else
       {
        setMode(channel, lim->getFullMode());
        setAddr(channel, validmodes->valuesToAddress(lim->getOpcode(), getSV(channel), getV1(channel), getV2(channel)));
    }
    log->debug(tr("... decoded address (")
            + "cv=" + QString::number(getSV(channel), 0, 16) + " "
            + "v1=" + QString::number(getV1(channel), 0, 16) + " "
            + "v2=" + QString::number(getV2(channel), 0, 16) + ") "
            + "is " + QString::number(getAddr(channel)) + "(0x" + QString::number(getAddr(channel), 0, 16) + ")");
      } else {
          log->warn("OPC_PEER_XFR: Type (" + QString::number(type) + ") is not {0,1,2} for channel " + QString::number(channel));
      }
     }
     else
     {
      // log->error("last CV recorded is invalid: "+lastOpCv);
     }
    }  // end of read processing

    // check for anything else to do
    issueNextOperation();
    return;
   }
   else
   {
    return;
   }
  }
  case LnConstants::OPC_INPUT_REP: // Block Sensors and other general sensor codes
  {
   if (log->isDebugEnabled())
   {
    log->debug(LnConstants::OPC_NAME(opCode) + " received");
   }
    // these might require capture
    for (int i = 0; i < _numRows; i++)
    {
     if (capture[i])
     {
      if (log->isDebugEnabled())
      {
          log->debug("row set for capture: " + i);
      }
      // This is a capture request, get address bytes
      int val1 = m->getElement(1);
      int val2 = m->getElement(2);
      // calculate address from val's, save result, mark as done
      // INPUT_REP's use val2's OPC_SW_REQ_DIR bit as LSB...'
      setAddr(i, (((val2 & 0x0F) << 5) * 256 + ((val1 & 0x7f) << 1))
              | (((val2 & LnConstants::OPC_SW_REQ_DIR) == LnConstants::OPC_SW_REQ_DIR) ? 0x01 : 0x00));
      capture[i] = false;
     }
    }
    return;
   }
   case LnConstants::OPC_SW_REQ:    // Turnout SWITCH Request
   {
    if (log->isDebugEnabled())
    {
        log->debug(LnConstants::OPC_NAME(opCode) + " received");
    }
    // these might require capture
    for (int i = 0; i < _numRows; i++)
    {
     if (capture[i])
     {
      if (log->isDebugEnabled())
      {
       log->debug("row set for capture: " + QString::number(i));
      }
      // This is a capture request, get address bytes
      int val1 = m->getElement(1);
      int val2 = m->getElement(2);
      // calculate address from val's, save result, mark as done
      int addr = LocoIO::SENSOR_ADR(val1, val2);
      setAddr(i, addr);
      capture[i] = false;
     }
    }
    return;
  }
  default:    // we ignore all other loconet messages
  {
  // if (log->isDebugEnabled()) {
  //     log->debug(LnConstants.OPC_NAME(opCode) + " received (ignored)");
  // }
  }
 } // end switch
}

/**
 * A valid reply has been received, so the read/write
 * worked, and the state should be advanced.
 */
/*protected synchronized*/ void LocoIOData::replyReceived()
{
 //mutex4.lock();
 timeoutcounter = 0;
 if(lastOpCv < 101)
 {
  // READ operations state machine
  switch (readState[currentPin])
  {
  case NONE:          break;   // try the write operations
  case READVALUE1:
  case READINGVALUE1: readState[currentPin] = READVALUE2;  return;
  case READVALUE2:
  case READINGVALUE2: readState[currentPin] = READMODE;    return;
  case READMODE:
  case READINGMODE:   readState[currentPin] = NONE;        return;
  default:
   log->error("Pin "+QString("0x%1").arg(currentPin)+" unexpected read state, can't advance "+readState[currentPin]);
   readState[currentPin] = NONE;        return;
  }
  // WRITE operations state machine
  switch (writeState[currentPin])
  {
  case NONE:          return;
  case WRITEVALUE1:
  case WRITINGVALUE1: writeState[currentPin] = WRITEVALUE2;return;
  case WRITEVALUE2:
  case WRITINGVALUE2: writeState[currentPin] = WRITEMODE;  return;
  case WRITEMODE:
  case WRITINGMODE:   writeState[currentPin] = NONE;       return;
  default:
   log->error("Pin "+QString("0x%1").arg(currentPin)+" unexpected write state, can't advance "+writeState[currentPin]);
   writeState[currentPin] = NONE;       return;
  }
  //mutex4.unlock();
 }
 else if(lastOpCv >=125 && lastOpCv <=127)  // 7D values
 {
  // READ operations state machine
  switch (readState7D)
  {
  case NONE:          break;   // try the write operations
  case READVALUE1:
  case READINGVALUE1: readState7D = READVALUE2;  return;
  case READVALUE2:
  case READINGVALUE2: readState7D = READMODE;    return;
  case READMODE:
  case READINGMODE:   readState7D = NONE;        return;
  default:
  log->error(" unexpected read state, can't advance "+readState7D);
  readState7D = NONE;        return;
  }
  // WRITE operations state machine
  switch (writeState7D)
  {
  case NONE:          return;
  case WRITEVALUE1:
  case WRITINGVALUE1: writeState7D = WRITEVALUE2;return;
  case WRITEVALUE2:
  case WRITINGVALUE2: writeState7D = WRITEMODE;  return;
  case WRITEMODE:
  case WRITINGMODE:   writeState7D = NONE;       return;
  default:
   log->error(" unexpected write state, can't advance "+writeState7D);
  }
 }
 else if(lastOpCv >= 101 && lastOpCv < 125)
 {
 // READ operations state machine
  switch (readStateServo[currentPin])
  {
  case NONE:          break;   // try the write operations
  case READVALUE1:
  case READINGVALUE1: readStateServo[currentPin] = READVALUE2;  return;
  case READVALUE2:
  case READINGVALUE2: readStateServo[currentPin] = READMODE;    return;
  case READMODE:
  case READINGMODE:   readStateServo[currentPin] = NONE;        return;
  default:
   log->error("Pin "+QString("0x%1").arg(currentPin)+" unexpected read state, can't advance "+readStateServo[currentPin]);
                            readStateServo[currentPin] = NONE;        return;
  }
  // WRITE operations state machine
  switch (writeStateServo[currentPin])
  {
  case NONE:          return;
  case WRITEVALUE1:
  case WRITINGVALUE1: writeStateServo[currentPin] = WRITEVALUE2;return;
  case WRITEVALUE2:
  case WRITINGVALUE2: writeStateServo[currentPin] = WRITEMODE;  return;
  case WRITEMODE:
  case WRITINGMODE:   writeStateServo[currentPin] = NONE;       return;
  default:
   log->error("Pin "+QString("0x%1").arg(currentPin)+" unexpected write state, can't advance "+writeStateServo[currentPin]);
  }
 }
 else
 {
 // READ operations state machine
  switch (readStateX2[currentPin])
  {
  case NONE:          break;   // try the write operations
  case READVALUE1:
  case READINGVALUE1: readStateX2[currentPin] = READVALUE2;  return;
  case READVALUE2:
  case READINGVALUE2: readStateX2[currentPin] = READMODE;    return;
  case READMODE:
  case READINGMODE:   readStateX2[currentPin] = NONE;        return;
  default:
   log->error("Pin "+QString("0x%1").arg(currentPin)+" unexpected read state, can't advance "+readStateX2[currentPin]);
                            readStateX2[currentPin] = NONE;        return;
  }
  // WRITE operations state machine
  switch (writeStateX2[currentPin])
  {
  case NONE:          return;
  case WRITEVALUE1:
  case WRITINGVALUE1: writeStateX2[currentPin] = WRITEVALUE2;return;
  case WRITEVALUE2:
  case WRITINGVALUE2: writeStateX2[currentPin] = WRITEMODE;  return;
  case WRITEMODE:
  case WRITINGMODE:   writeStateX2[currentPin] = NONE;       return;
  default:
   log->error("Pin "+QString("0x%1").arg(currentPin)+" unexpected write state, can't advance "+writeStateX2[currentPin]);
  }
 }
}

/**
 * Look through the table to find the next thing that
 * needs to be read.
 */
/*protected synchronized*/ void LocoIOData::issueNextOperation()
{
 //mutex2.lock();
 //QMutexLocker locker(&mutex2N);
 vals = nullptr;
 readWriteType = 0;
 bool bResult;
 // stop the timer while we figure this out
 stopTimer();
 SleeperThread::msleep(20); // necessary to allow servoio to echo command
 // find the first item that needs to be read
 for (int i=0; i<_numRows*2; i++)
 {
  currentPin = i;
  if (readState[i]!=NONE)
  {
   // yes, needs read.  Find what kind
   // System.out.println("iNO: readState[" + i + "] = " + readState[i]);
   switch (readState[i])
   {
   case READVALUE1:
   case READINGVALUE1:
    // set new state, send read, then done
    readState[i] = READINGVALUE1;
    lastOpCv = i*3+4;
    setStatus("read SV"+QString("%1").arg(lastOpCv)+" (port"+QString("%1").arg(i)+" v1)");
    sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
    //mutex2.unlock();
    return;
   case READVALUE2:
   case READINGVALUE2:
    // set new state, send read, then done
    readState[i] = READINGVALUE2;
    lastOpCv = i*3+5;
    setStatus("read SV"+QString("%1").arg(lastOpCv)+" (port "+QString("%1").arg(i)+" v2)");
    sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
    //mutex2.unlock();
    return;
   case READMODE:
   case READINGMODE:
    // set new state, send read, then done
    readState[i] = READINGMODE;
    lastOpCv = i*3+3;
    setStatus("read SV"+QString("%1").arg(lastOpCv)+" (port "+QString("%1").arg(i)+" mode)");
    sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
    //mutex2.unlock();
    return;
   default:
    log->error("found an unexpected state: "+QString("%1").arg(readState[i])+" on port "+QString("%1").arg(i));
    //mutex2.unlock();
    return;
   }
  }
 }
 // no reads, so continue to check writes
 for (int i=0; i<_numRows*2; i++)
 {
  currentPin = i;
  if (writeState[i]!=NONE)
  {
   // yes, needs read.  Find what kind
   // System.out.println("iNO: writeState[" + i + "] = " + readState[i]);
   switch (writeState[i])
   {
   case WRITEVALUE1:
   case WRITINGVALUE1:
    // set new state, send read, then done
    writeState[i] = WRITINGVALUE1;
    lastOpCv = i*3+4;
    setStatus("write SV"+QString("%1").arg(lastOpCv)+" ( port "+QString("%1").arg(i)+" v1)");
    sendWriteCommand(unitAddress, unitSubAddress, lastOpCv, getV1(i));
    bResult = checkWriteResponse(unitAddress, unitSubAddress, lastOpCv, getV1(i));
    if(bResult)
     setV1(i,v1[i] & 0xFF, ssLightYellow);
    //mutex2.unlock();
    return;
   case WRITEVALUE2:
   case WRITINGVALUE2:
    // set new state, send read, then done
    writeState[i] = WRITINGVALUE2;
    lastOpCv = i*3+5;
    setStatus("write SV"+QString("%1").arg(lastOpCv)+" (port"+QString("%1").arg(i)+" v2)");
    sendWriteCommand(unitAddress, unitSubAddress, lastOpCv, getV2(i));
    bResult = checkWriteResponse(unitAddress, unitSubAddress, lastOpCv, getV2(i));
    if(bResult)
     setV2(i,v2[i] & 0xFF, ssLightYellow);
    //mutex2.unlock();
    return;
   case WRITEMODE:
   case WRITINGMODE:
    // set new state, send write, then done
    writeState[i] = WRITINGMODE;
    lastOpCv = i*3+3;
    setStatus("write SV"+QString("%1").arg(lastOpCv)+" (port"+QString("%1").arg(i)+" mode)");
    sendWriteCommand(unitAddress, unitSubAddress, lastOpCv, getSV(i));
    bResult = checkWriteResponse(unitAddress, unitSubAddress, lastOpCv, getSV(i));
    if(bResult)
    {
     if(getSV(i) == 0xd8)
     {
      getSV(i);
     }
     setSV(i,sv[i] & 0xFF, ssLightYellow);
    }
    //mutex2.unlock();
    return;

   default:
    log->error("found an unexpected state: "+QString("%1").arg(writeState[1])+" on port "+QString("%1").arg(i));
    //mutex2.unlock();
    return;
   }
  }
 }
 // nothing of interest found, so just end gracefully
 //  if (log->isDebugEnabled()) log->debug("No operation needed");
 setStatus("OK");
 if(b3ByteRead)
  READ= READMODE;
 else
  READ = READVALUE1;  // starting state
 WRITE = WRITEVALUE1;  // starting state
 lastOpCv = -1;
 currentPin = 0;
 //mutex2.unlock();
 emit IOComplete(nullptr);
}
/**
 * Look through the table to find the next thing that
 * needs to be read.
 */
/*protected synchronized*/ void LocoIOData::issueNextExtra2Operation()
{
 //mutex2.lock();
 QMutexLocker locker(&mutexEx2);
 vals = nullptr;
 readWriteType = 1;

 // stop the timer while we figure this out
 stopTimer();
 SleeperThread::msleep(20); // necessary to allow servoio to echo command
 // find the first item that needs to be read
 for (int i=0; i<_numRows; i++)
 {
  currentPin = i;
  if (readStateX2[i]!=NONE)
  {
   // yes, needs read.  Find what kind
   // System.out.println("iNO: readState[" + i + "] = " + readState[i]);
   switch (readStateX2[i])
   {
   case READVALUE1:
   case READINGVALUE1:
    // set new state, send read, then done
    readStateX2[i] = READINGVALUE1;
    lastOpCv = i*3+128 +1;
    setStatus("read X2SV"+QString("%1").arg(lastOpCv)+" (port"+QString("%1").arg(i)+" v1)");
    sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
    //mutex2.unlock();
    return;
   case READVALUE2:
   case READINGVALUE2:
    // set new state, send read, then done
    readStateX2[i] = READINGVALUE2;
    lastOpCv = i*3+128+2;
    setStatus("read X2SV"+QString("%1").arg(lastOpCv)+" (port "+QString("%1").arg(i)+" v2)");
    sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
    //mutex2.unlock();
    return;
   case READMODE:
   case READINGMODE:
    // set new state, send read, then done
    readStateX2[i] = READINGMODE;
    lastOpCv = i*3+128;
    setStatus("read X2SV"+QString("%1").arg(lastOpCv)+" (port "+QString("%1").arg(i)+" mode)");
    sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
    //mutex2.unlock();
    return;
   default:
    log->error("found an unexpected state: "+QString("%1").arg(readStateX2[1])+" on port "+QString("%1").arg(i));
    //mutex2.unlock();
    return;
   }
  }
 }
 // no reads, so continue to check writes
 for (int i=0; i<_numRows; i++)
 {
  currentPin = i;
  if (writeStateX2[i]!=NONE)
  {
   // yes, needs read.  Find what kind
   // System.out.println("iNO: writeState[" + i + "] = " + readState[i]);
   switch (writeStateX2[i])
   {
   case WRITEVALUE1:
   case WRITINGVALUE1:
    // set new state, send read, then done
    writeStateX2[i] = WRITINGVALUE1;
    lastOpCv = i*3+128+1;
    setStatus("write X2SV"+QString("%1").arg(lastOpCv)+" ( port "+QString("%1").arg(i)+" v1)");
    sendWriteCommand(unitAddress, unitSubAddress, lastOpCv, getX2V1(i));
    setX2V1(i,x2v1[i] & 0xFF, ssLightYellow);
    //mutex2.unlock();
    return;
   case WRITEVALUE2:
   case WRITINGVALUE2:
    // set new state, send read, then done
    writeStateX2[i] = WRITINGVALUE2;
    lastOpCv = i*3+128+2;
    setStatus("write X2SV"+QString("%1").arg(lastOpCv)+" (port"+QString("%1").arg(i)+" v2)");
    sendWriteCommand(unitAddress, unitSubAddress, lastOpCv, getX2V2(i));
    setX2V2(i,x2v2[i] & 0xFF, ssLightYellow);
    //mutex2.unlock();
    return;
   case WRITEMODE:
   case WRITINGMODE:
    // set new state, send write, then done
    writeStateX2[i] = WRITINGMODE;
    lastOpCv = i*3+128;
    setStatus("write X2SV"+QString("%1").arg(lastOpCv)+" (port"+QString("%1").arg(i)+" mode)");
    sendWriteCommand(unitAddress, unitSubAddress, lastOpCv, getX2SV(i));
    setX2SV(i,x2sv[i] & 0xFF, ssLightYellow);
    //mutex2.unlock();
    return;

   default:
    log->error("found an unexpected state: "+QString("%1").arg(writeStateX2[1])+" on port "+QString("%1").arg(i));
    //mutex2.unlock();
    return;
   }
  }
 }
 // nothing of interest found, so just end gracefully
 //  if (log->isDebugEnabled()) log->debug("No operation needed");
 setStatus("OK");
 if(b3ByteRead)
  READ= READMODE;
 else
  READ = READVALUE1;  // starting state
 WRITE = WRITEVALUE1;  // starting state
 lastOpCv = -1;
 currentPin = 0;
 //mutex2.unlock();
 emit IOCompleteX2(nullptr);
}
/*protected synchronized*/ void LocoIOData::issueNextServoOperation()
{
 //mutex2.lock();
 QMutexLocker locker(&mutex2S);
 bool bResult;
 vals = nullptr;
 readWriteType = 2;
 // stop the timer while we figure this out
 stopTimer();
 SleeperThread::msleep(20); // necessary to allow servoio to echo command
 // find the first item that needs to be read
 for (int i=0; i<_numRowsServo; i++)
 {
  currentPin = i;
  if (readStateServo[i]!=NONE)
  {
   // yes, needs read.  Find what kind
   // System.out.println("iNO: readState[" + i + "] = " + readState[i]);
   switch (readStateServo[i])
   {
   case READVALUE1:
   case READINGVALUE1:
    // set new state, send read, then done
    readStateServo[i] = READINGVALUE1;
    lastOpCv = i*3+102;
    setStatus("read ServoP1"+QString("%1").arg(lastOpCv)+" (port"+QString("%1").arg(i)+" P1)");
    sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
    //mutex2.unlock();
    return;
   case READVALUE2:
   case READINGVALUE2:
    // set new state, send read, then done
    readStateServo[i] = READINGVALUE2;
    lastOpCv = i*3+103;
    setStatus("read ServoP2"+QString("%1").arg(lastOpCv)+" (port "+QString("%1").arg(i)+" P2)");
    sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
    //mutex2.unlock();
    return;
   case READMODE:
   case READINGMODE:
    // set new state, send read, then done
    readStateServo[i] = READINGMODE;
    lastOpCv = i*3+101;
    setStatus("read ServoSpeed"+QString("%1").arg(lastOpCv)+" (port "+QString("%1").arg(i)+" mode)");
    sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
    //mutex2.unlock();
    return;
   default:
    log->error("found an unexpected state: "+QString("%1").arg(readStateServo[1])+" on port "+QString("%1").arg(i));
    //mutex2.unlock();
    return;
   }
  }
 }
 // no reads, so continue to check writes
 for (int i=0; i<_numRowsServo; i++)
 {
  currentPin = i;

  if (writeStateServo[i]!=NONE)
  {
   // yes, needs read.  Find what kind
   // System.out.println("iNO: writeState[" + i + "] = " + readState[i]);
   switch (writeStateServo[i])
   {
   case WRITEVALUE1:
   case WRITINGVALUE1:
    // set new state, send read, then done
    writeStateServo[i] = WRITINGVALUE1;
    lastOpCv = i*3+101;
    setStatus("write ServoSV"+QString("%1").arg(lastOpCv)+" ( port "+QString("%1").arg(i)+" v1)");
    sendWriteCommand(unitAddress, unitSubAddress, lastOpCv, getServoP1(i));
    bResult = checkWriteResponse(unitAddress, unitSubAddress, lastOpCv, getServoP1(i));
    if(bResult)
    setServoP1(i,servoP1[i] & 0xFF, ssLightYellow);
    //mutex2.unlock();
    return;
   case WRITEVALUE2:
   case WRITINGVALUE2:
    // set new state, send read, then done
    writeStateServo[i] = WRITINGVALUE2;
    lastOpCv = i*3+102;
    setStatus("write ServoP2"+QString("%1").arg(lastOpCv)+" (port"+QString("%1").arg(i)+" v2)");
    sendWriteCommand(unitAddress, unitSubAddress, lastOpCv, getServoP2(i));
    bResult = checkWriteResponse(unitAddress, unitSubAddress, lastOpCv, getServoP2(i));
    if(bResult)
    setServoP2(i,servoP2[i] & 0xFF, ssLightYellow);
    //mutex2.unlock();
    return;
   case WRITEMODE:
   case WRITINGMODE:
    // set new state, send write, then done
    writeStateServo[i] = WRITINGMODE;
    lastOpCv = i*3+103;
    setStatus("write ServoSpeed"+QString("%1").arg(lastOpCv)+" (port"+QString("%1").arg(i)+" mode)");
    sendWriteCommand(unitAddress, unitSubAddress, lastOpCv, getServoSpeed(i));
    bResult = checkWriteResponse(unitAddress, unitSubAddress, lastOpCv, getServoSpeed(i));
    if(bResult)
    setServoSpeed(i,servoSpd[i] & 0xFF, ssLightYellow);
    //mutex2.unlock();
    return;

   default:
    log->error("found an unexpected state: "+QString("%1").arg(writeStateServo[1])+" on port "+QString("%1").arg(i));
    //mutex2.unlock();
    return;
   }
  }
 }
 // nothing of interest found, so just end gracefully
 //  if (log->isDebugEnabled()) log->debug("No operation needed");
 setStatus("OK");
 if(b3ByteRead)
  READ= READMODE;
 else
  READ = READVALUE1;  // starting state
 WRITE = WRITEVALUE1;  // starting state
 lastOpCv = -1;
 currentPin = 0;
 //mutex2.unlock();
 emit IOCompleteServo();
}

/*protected synchronized*/ void LocoIOData::issueNext7DOperation()
{
 //mutex2.lock();
 QMutexLocker locker(&mutex7D);

 vals = nullptr;
 readWriteType = 0;
 // stop the timer while we figure this out
 stopTimer();
 SleeperThread::msleep(20); // necessary to allow servoio to echo command
 // find the first item that needs to be read
// for (int i=0; i<_numRows*2; i++)
// {
//  currentPin = i;
  if (readState7D != NONE)
  {
   // yes, needs read.  Find what kind
   // System.out.println("iNO: readState[" + i + "] = " + readState[i]);
   switch (readState7D)
   {
   case READVALUE1:
   case READINGVALUE1:
    // set new state, send read, then done
    readState7D = READINGVALUE1;
    lastOpCv = 126;
    setStatus("read SV"+QString("%1").arg(lastOpCv));
    sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
    //mutex2.unlock();
    return;
   case READVALUE2:
   case READINGVALUE2:
    // set new state, send read, then done
    readState7D = READINGVALUE2;
    lastOpCv = 127;
    setStatus("read SV"+QString("%1").arg(lastOpCv));
    sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
    //mutex2.unlock();
    return;
   case READMODE:
   case READINGMODE:
    // set new state, send read, then done
    readState7D = READINGMODE;
    lastOpCv = 125;
    setStatus("read SV"+QString("%1").arg(lastOpCv));
    sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
    //mutex2.unlock();
    return;
   default:
    log->error("found an unexpected state: "+QString("%1").arg(readState7D));
    //mutex2.unlock();
    return;
   }
  }
 //}
 // no reads, so continue to check writes
// for (int i=0; i<_numRows*2; i++)
// {
//  currentPin = i;
  if (writeState7D != NONE)
  {
   // yes, needs read.  Find what kind
   // System.out.println("iNO: writeState[" + i + "] = " + readState[i]);
   switch (writeState7D)
   {
   case WRITEVALUE1:
   case WRITINGVALUE1:
    // set new state, send read, then done
    writeState7D = WRITINGVALUE1;
    lastOpCv = 125;
    setStatus("write SV"+QString("%1").arg(lastOpCv));
    sendWriteCommand(unitAddress, unitSubAddress, lastOpCv, getSV7D());
    //setV1(i,v1[i] & 0xFF, ssLightYellow);
    //mutex2.unlock();
    return;
   case WRITEVALUE2:
   case WRITINGVALUE2:
    // set new state, send read, then done
    writeState7D = WRITINGVALUE2;
    lastOpCv = 126;
    setStatus("write SV"+QString("%1").arg(lastOpCv));
    sendWriteCommand(unitAddress, unitSubAddress, lastOpCv, getSV7E());
    //setV2(i,v2[i] & 0xFF, ssLightYellow);
    //mutex2.unlock();
    return;
   case WRITEMODE:
   case WRITINGMODE:
    // set new state, send write, then done
    writeState7D = WRITINGMODE;
    lastOpCv = 127;
    setStatus("write SV"+QString("%1").arg(lastOpCv));
    sendWriteCommand(unitAddress, unitSubAddress, lastOpCv, getSV7F());

    //setSV(i,sv[i] & 0xFF, ssLightYellow);
    //mutex2.unlock();
    return;

   default:
    log->error("found an unexpected state: "+QString("%1").arg(writeState7D));
     //mutex2.unlock();
     return;
    }
  }
// }
 // nothing of interest found, so just end gracefully
 //  if (log->isDebugEnabled()) log->debug("No operation needed");
 setStatus("OK");
 if(b3ByteRead)
  READ= READMODE;
 else
  READ = READVALUE1;  // starting state
 WRITE = WRITEVALUE1;  // starting state
 lastOpCv = -1;
 currentPin = 0;
 //mutex2.unlock();
 emit IOComplete7D();
}

/*protected synchronized*/ void LocoIOData::issueNext0Operation()
{
 //mutex2.lock();
 QMutexLocker locker(&mutex7D);

 vals = nullptr;
 readWriteType = 0;
 // stop the timer while we figure this out
 stopTimer();
 SleeperThread::msleep(20); // necessary to allow servoio to echo command
 // find the first item that needs to be read
// for (int i=0; i<_numRows*2; i++)
// {
//  currentPin = i;
  if (readState0 != NONE)
  {
   // yes, needs read.  Find what kind
   // System.out.println("iNO: readState[" + i + "] = " + readState[i]);
   switch (readState0)
   {
   case READVALUE1:
   case READINGVALUE1:
    // set new state, send read, then done
    readState0 = READINGVALUE1;
    lastOpCv = 0;
    setStatus("read SV"+QString("%1").arg(lastOpCv));
    sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
    //mutex2.unlock();
    return;
   case READVALUE2:
   case READINGVALUE2:
    // set new state, send read, then done
    readState0 = READINGVALUE2;
    lastOpCv = 1;
    setStatus("read SV"+QString("%1").arg(lastOpCv));
    sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
    //mutex2.unlock();
    return;
   case READMODE:
   case READINGMODE:
    // set new state, send read, then done
    readState0 = READINGMODE;
    lastOpCv = 2;
    setStatus("read SV"+QString("%1").arg(lastOpCv));
    sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
    //mutex2.unlock();
    return;
   default:
    log->error("found an unexpected state: "+QString("%1").arg(readState7D));
    //mutex2.unlock();
    return;
   }
  }
 //}
 // no reads, so continue to check writes
// for (int i=0; i<_numRows*2; i++)
// {
//  currentPin = i;
#if 0
  if (writeState0 != NONE)
  {
   // yes, needs read.  Find what kind
   // System.out.println("iNO: writeState[" + i + "] = " + readState[i]);
   switch (writeState0)
   {
   case WRITEVALUE1:
   case WRITINGVALUE1:
    // set new state, send read, then done
    writeState0 = WRITINGVALUE1;
    lastOpCv = 0;
    setStatus("write SV"+QString("%1").arg(lastOpCv));
    sendWriteCommand(unitAddress, unitSubAddress, lastOpCv, getSV7D());
    //setV1(i,v1[i] & 0xFF, ssLightYellow);
    //mutex2.unlock();
    return;
   case WRITEVALUE2:
   case WRITINGVALUE2:
    // set new state, send read, then done
    writeState0 = WRITINGVALUE2;
    lastOpCv = 1;
    setStatus("write SV"+QString("%1").arg(lastOpCv));
    sendWriteCommand(unitAddress, unitSubAddress, lastOpCv, getSV7E());
    //setV2(i,v2[i] & 0xFF, ssLightYellow);
    //mutex2.unlock();
    return;
   case WRITEMODE:
   case WRITINGMODE:
    // set new state, send write, then done
    writeState0 = WRITINGMODE;
    lastOpCv = 2;
    setStatus("write SV"+QString("%1").arg(lastOpCv));
    sendWriteCommand(unitAddress, unitSubAddress, lastOpCv, getSV7F());

    //setSV(i,sv[i] & 0xFF, ssLightYellow);
    //mutex2.unlock();
    return;

   default:
    log->error("found an unexpected state: "+QString("%1").arg(writeState7D));
     //mutex2.unlock();
     return;
    }
  }
#endif
// }
 // nothing of interest found, so just end gracefully
 //  if (log->isDebugEnabled()) log->debug("No operation needed");
 setStatus("OK");
 if(b3ByteRead)
  READ= READMODE;
 else
  READ = READVALUE1;  // starting state
 WRITE = WRITEVALUE1;  // starting state
 lastOpCv = -1;
 currentPin = 0;
 //mutex2.unlock();
 emit IOComplete0();
}

/*protected synchronized*/ void LocoIOData::issueNext125Operation()
{
 //mutex2.lock();
 QMutexLocker locker(&mutex7D);

 vals = nullptr;
 readWriteType = 0;
 // stop the timer while we figure this out
 stopTimer();
 SleeperThread::msleep(20); // necessary to allow servoio to echo command
 // find the first item that needs to be read
// for (int i=0; i<_numRows*2; i++)
// {
//  currentPin = i;
  if (readState125 != NONE)
  {
   // yes, needs read.  Find what kind
   // System.out.println("iNO: readState[" + i + "] = " + readState[i]);
   switch (readState125)
   {
   case READVALUE1:
   case READINGVALUE1:
    // set new state, send read, then done
    readState125 = READINGVALUE1;
    lastOpCv = 125;
    setStatus("read SV"+QString("%1").arg(lastOpCv));
    sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
    //mutex2.unlock();
    return;
   case READVALUE2:
   case READINGVALUE2:
    // set new state, send read, then done
    readState125 = READINGVALUE2;
    lastOpCv = 126;
    setStatus("read SV"+QString("%1").arg(lastOpCv));
    sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
    //mutex2.unlock();
    return;
   case READMODE:
   case READINGMODE:
    // set new state, send read, then done
    readState125 = READINGMODE;
    lastOpCv = 127;
    setStatus("read SV"+QString("%1").arg(lastOpCv));
    sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
    //mutex2.unlock();
    return;
   default:
    log->error("found an unexpected state: "+QString("%1").arg(readState7D));
    //mutex2.unlock();
    return;
   }
  }
 //}
 // no reads, so continue to check writes
// for (int i=0; i<_numRows*2; i++)
// {
//  currentPin = i;
#if 0
  if (writeState125 != NONE)
  {
   // yes, needs read.  Find what kind
   // System.out.println("iNO: writeState[" + i + "] = " + readState[i]);
   switch (writeState125)
   {
   case WRITEVALUE1:
   case WRITINGVALUE1:
    // set new state, send read, then done
    writeState125 = WRITINGVALUE1;
    lastOpCv = 0;
    setStatus("write SV"+QString("%1").arg(lastOpCv));
    sendWriteCommand(unitAddress, unitSubAddress, lastOpCv, getSV7D());
    //setV1(i,v1[i] & 0xFF, ssLightYellow);
    //mutex2.unlock();
    return;
   case WRITEVALUE2:
   case WRITINGVALUE2:
    // set new state, send read, then done
    writeState125 = WRITINGVALUE2;
    lastOpCv = 1;
    setStatus("write SV"+QString("%1").arg(lastOpCv));
    sendWriteCommand(unitAddress, unitSubAddress, lastOpCv, getSV7E());
    //setV2(i,v2[i] & 0xFF, ssLightYellow);
    //mutex2.unlock();
    return;
   case WRITEMODE:
   case WRITINGMODE:
    // set new state, send write, then done
    writeState125 = WRITINGMODE;
    lastOpCv = 2;
    setStatus("write SV"+QString("%1").arg(lastOpCv));
    sendWriteCommand(unitAddress, unitSubAddress, lastOpCv, getSV7F());

    //setSV(i,sv[i] & 0xFF, ssLightYellow);
    //mutex2.unlock();
    return;

   default:
    log->error("found an unexpected state: "+QString("%1").arg(writeState7D));
     //mutex2.unlock();
     return;
    }
  }
#endif
// }
 // nothing of interest found, so just end gracefully
 //  if (log->isDebugEnabled()) log->debug("No operation needed");
 setStatus("OK");
 if(b3ByteRead)
  READ= READMODE;
 else
  READ = READVALUE1;  // starting state
 WRITE = WRITEVALUE1;  // starting state
 lastOpCv = -1;
 currentPin = 0;
 //mutex2.unlock();
 emit IOComplete125();

}
/**
 * Internal routine to handle a timeout during read/write
 * by retrying the same operation.
 */
/*synchronized protected*/ void LocoIOData::timeout() { // [slot]
 mutex3.lock();
 switch(readWriteType)
 {
 case 0:
  if (log->isDebugEnabled()) log->debug("timeout base!");
  setStatus("Timeout");
  if (timeoutcounter++ == 5)
  {
   for (int i=0; i<_numRows*2; i++)
   {
    readState[i] = NONE;
    writeState[i] = NONE;
   }
   setStatus("Aborted");
   setLIOVersion("<unknown>");
   timeoutcounter = 0;
   stopTimer();
   emit ioAborted();
  } else
  {
   issueNextOperation();
  }
  break;
 case 1:
  if (log->isDebugEnabled()) log->debug("timeout x2!");
  setStatus("Timeout X2");
  if (timeoutcounter++ == 5)
  {
   for (int i=0; i<_numRows; i++)
   {
    readStateX2[i] = NONE;
    writeStateX2[i] = NONE;
   }
   setStatus("Aborted");
   setLIOVersion("<unknown>");
   timeoutcounter = 0;
   stopTimer();
   emit ioAborted();
  } else
  {
   issueNextExtra2Operation();
  }
  break;
 case 2:
  if (log->isDebugEnabled()) log->debug("timeout Servo!");
  setStatus("Timeout Servo");
  if (timeoutcounter++ == 5)
  {
   for (int i=0; i<_numRows*2; i++)
   {
    readStateServo[i] = NONE;
    writeStateServo[i] = NONE;
   }
   setStatus("Aborted");
   //setLIOVersion("<unknown>");
   timeoutcounter = 0;
   stopTimer();
   emit ioAborted();
  } else
  {
   issueNextServoOperation();
  }
  break;
 default:
  break;
 }
 mutex3.unlock();
}

/**
 * Internal routine to start timer to protect the mode-change.
 */
/*protected*/ void LocoIOData::startTimer() {
    restartTimer(TIMEOUT);
}

/**
 * Internal routine to stop timer, as all is well
 */
/*protected*/ void LocoIOData::stopTimer() {
    if (timer!=nullptr) timer->stop();
}

/**
 * Internal routine to handle timer starts & restarts
 */
/*protected*/ void LocoIOData::restartTimer(int delay)
{
 Q_ASSERT(delay > 0);
 if(timer == nullptr)
 {
  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
 }
 timer->stop();
 //timer->setInterval(delay);
 //timer.setRepeats(false);
 timer->setSingleShot(true);
 timer->start(delay);
}



/**
 * Read a SV from a given LocoIO device
 *
 * @param locoIOAddress
 * @param locoIOSubAddress
 * @param cv
 */

void LocoIOData::sendReadCommand(int locoIOAddress, int locoIOSubAddress, int cv)
{
 // remember current op is read
 reading = true;
 //writing = false;
 log->debug("sendReadCommand to " + QString("%1").arg(locoIOAddress,0,16) + "/" +
  QString("%1").arg(locoIOSubAddress,0,16) + " SV" +QString("%1 (0x%2)").arg(cv).arg( cv,0,16));
 LocoNetMessage* msg = LocoIO::readCV(locoIOAddress | 0x100, locoIOSubAddress, cv);
 tc->sendLocoNetMessage(msg);
 startTimer();        // and set timeout on reply
}

/**
 * Write an SV to a given LocoIO device
 *
 * @param locoIOAddress
 * @param locoIOSubAddress
 * @param cv
  *@param data
 */
void LocoIOData::sendWriteCommand(int locoIOAddress, int locoIOSubAddress, int cv, int data)
{
 // remember current op is write
 reading = false;
 //writing = true;
// log->debug("sendWriteCommand to " + QString("%1").arg(locoIOAddress,0,16) + "/" +
//  QString("%1").arg(locoIOSubAddress,0,16) + " SV" +QString("%1 (0x%2)").arg(cv).arg( cv,0,16));
 log->debug(tr("sendWriteCommand to addr: %1/%2 SV: %3(0x%4) data: %5(%6)").arg(locoIOAddress,0,16).arg(locoIOSubAddress,0,16).arg(cv).arg( cv,0,16).arg(data).arg( data,0,16));

 tc->sendLocoNetMessage(
 LocoIO::writeCV(locoIOAddress | 0x100, locoIOSubAddress, cv, data));
 startTimer();        // and set timeout on reply
}

bool LocoIOData::checkWriteResponse(int locoIOAddress, int locoIOSubAddress, int cv, int data)
{
 ResponseCheck* rc = new ResponseCheck(locoIOAddress, locoIOSubAddress, cv, data, tc);
 QThread* thread = new QThread;
 rc->moveToThread(thread);
 //connect(rc, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
 connect(thread, SIGNAL(started()), rc, SLOT(process()));
 connect(rc, SIGNAL(finished()), thread, SLOT(quit()));
 connect(rc, SIGNAL(finished()), rc, SLOT(deleteLater()));
 connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
 thread->start();
 thread->wait(500);
 return rc->getResult();
}
ResponseCheck::ResponseCheck(int unitAddr, int unitSubAddr, int cv, int data, LnTrafficController* tc)
{
 svUnitAddr = unitAddr;
 svUnitSubAddr = unitSubAddr;
 svCv = cv;
 svData = data;
 this->tc = tc;
 bResult = false;
}

ResponseCheck::~ResponseCheck() {}
bool ResponseCheck::getResult() {return bResult;}

void ResponseCheck::processWriteResponse(LocoNetMessage *l)
{
 if(l->getOpCode() == LnConstants::OPC_PEER_XFER )
 {
  int src = l->getElement(2); // source of transfer
  int dst_l = l->getElement(3); // ls 7 bits of destination
  int dst_h = l->getElement(4); // ms 7 bits of destination
  int pxct1 = l->getElement(5);
  int pxct2 = l->getElement(10);

  QVector<int> d = l->getPeerXfrData();

  if (src == 0x50)
  {
   // Packets from the LocoBuffer
   QString dst_subaddrx = (dst_h != 0x01 ? "" : ((d[4] != 0) ? "/" + QString("%1").arg(d[4]) : ""));
   if (dst_h == 0x01 && ((pxct1 & 0xF0) == 0x00)
       && ((pxct2 & 0xF0) == 0x10))
   {
    // LocoBuffer to LocoIO
    log->info( "LocoBuffer => LocoIO@"
           + ((dst_l == 0) ? tr("broadcast") : QString("%1").arg(dst_l) + dst_subaddrx)
           + " "
           + (d[0] == 2 ? tr("Query SV") + QString("%1").arg(d[1]) : tr("Write SV") + QString("%1").arg(d[1]) + "=0x" + QString("%1").arg(d[3],0,16))
           + ((d[2] != 0) ? tr(" Firmware rev ") + QString("%1").arg(d[2]) : "") + ".\n");
   }
  }
  if (dst_h == 0x01 && ((pxct1 & 0xF0) == 0x00)
      && ((pxct2 & 0xF0) == 0x00))
  {
   // (Jabour/Deloof LocoIO), SV Programming messages format 1
   QString src_subaddrx = ((d[4] != 0) ? "/" + QString("%1").arg(d[4],0,16) : "");
   QString dst_subaddrx = (dst_h != 0x01 ? "" : ((d[4] != 0) ? "/" + QString("%1").arg(d[4],0,16) : ""));

   QString src_dev = ((src == 0x50) ? "Locobuffer" : "LocoIO@0x" + QString("%1").arg(src, 0, 16)) + src_subaddrx;
   QString dst_dev = (((dst_h == 0x01) && (dst_l == 0x50)) ? "LocoBuffer "
                        : (((dst_h == 0x01) && (dst_l == 0x0)) ? tr("broadcast")
                      : "LocoIO@0x" + QString("%1").arg(dst_l,0,16) + dst_subaddrx));
   QString operation = (src == 0x50) ?
           ((d[0] == 2) ? tr("Query") : tr("Write")) :
           ((d[0] == 2) ? tr("Report") : tr("Write"))
           ;

   log->info( src_dev + "=> " + dst_dev + " "
           + ((dst_h == 0x01) ? (operation + " SV" + QString("%1").arg(d[1])) : "")
          + ((src == 0x50) ? (d[0] != 2 ? ("=0x" + QString("%1").arg(d[3],0,16)) : "")
            : " = " + ((d[0] == 2) ? ((d[2] != 0) ? (d[5] < 10) ? "" + QString("%1").arg(d[5],0,16)
                      :  QString("%1").arg(d[5]) + " (0x" + QString("%1").arg(d[5],0,16) + ")"
                     : (d[7] < 10) ? "" + QString("%1").arg(d[7])
                      :  QString("%1").arg(d[7]) + " (0x" + QString("%1").arg(d[7],0,16) + ")")
                      : (d[7] < 10) ? "" + QString("%1").arg(d[7])
                      :  QString("%1").arg(d[7]) + " (0x" + QString("%1").arg(d[7],0,16) + ")"))
          + ((d[2] != 0) ? tr(" Firmware rev ") + dotme(d[2]) : "") + ".\n");
   if((dst_l == (svUnitAddr & 0xFF)) && (operation == "Write") && (d[1] == svCv) && (d[7] == svData))
   {
    bResult = true;
    emit finished();
   }
  }
 }
}

void ResponseCheck::process()
{
 log = new Logger("ResponseCheck");
 connect(this->tc, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(processWriteResponse(LocoNetMessage*)));
}

/*private*/ QString ResponseCheck::dotme(int val)
{
 int dit;
 int x = val;
 QString ret;// = new StringBuffer();
 if (val == 0) return "0";
 while (x != 0)
 {
  dit = x % 10;
  ret.insert(0,QString("%1").arg(dit));
  x = x / 10;
  if (x != 0) ret.insert(0, ".");
 }
 return ret/*.toString()*/;
}

/*public*/ void LocoIOData::dispose()
{
 if (log->isDebugEnabled()) log->debug("dispose");
 // disconnect from future events
 stopTimer();
 tc->removeLocoNetListener(~0, (LocoNetListener*)this);

 // nullptr references, so that they can be gc'd even if this isn't.
//    addr = nullptr;
//    mode = nullptr;
//    sv  = nullptr;
//    v1  = nullptr;
//    v2  = nullptr;
//    lim = nullptr;
 /*private*/ /*int[]*/ addr    =  QVector<int>(_numRows*2, 0);
 /*private*/ /*int[]*/ sv      = QVector<int>(_numRows*2, 0);
 /*private*/ /*int[]*/ v1      =  QVector<int>(_numRows*2, 0);
 /*private*/ /*int[]*/ v2      =  QVector<int>(_numRows*2, 0);
 /*private*/ /*LocoIOMode[]*/ lim =  QVector<LocoIOMode*>(_numRows*2, nullptr);
 mode =  QStringList();
}
    //static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LocoIOData.class.getName());
void LocoIOData::setDefaults()
{
 for(int cv=0; cv < _defaults.size(); cv++)
 {
  sendWriteCommand(unitAddress, unitSubAddress, cv, _defaults[cv]);
  if(cv == 1)
   setUnitAddress(_defaults[cv]);
  if(cv == 2)
   setUnitSubAddress(_defaults[cv]);
 }
 emit IOComplete(nullptr);
}
void LocoIOData::setValues(QList<int>* vals)
{
 for(int cv=0; cv < vals->size(); cv++)
 {
  sendWriteCommand(unitAddress, unitSubAddress, cv, vals->at(cv));
  if(cv == 1)
   setUnitAddress(vals->at(cv));
  if(cv == 2)
   setUnitSubAddress(vals->at(cv));
 }
 emit IOComplete(nullptr);
}

void LocoIOData::getCVs()
{
 vals = new QList<int>();
 vals->reserve(_defaults.size());
 for(int i=0; i < _defaults.size(); i++)
  vals->append(0);
 lastOpCv = 0;
 issueNextReadCv();
}
void LocoIOData::issueNextReadCv()
{
 sendReadCommand(unitAddress, unitSubAddress, lastOpCv);
}

QList<int>* LocoIOData::defaults() {return &_defaults;}

void LocoIOData::onCvRead(int cv, int val)
{
 if(vals !=nullptr)
 {
  vals->replace(cv,val);
 }
 if(cv == _defaults.size()-1)
 {
  emit IOComplete(vals);
 }
}

void LocoIOData::setCVs(QVector<int>* cvs)
{
 for(int cv=0; cv < _defaults.size(); cv++)
 {
  sendWriteCommand(unitAddress, unitSubAddress, cv, cvs->at(cv));
 }
 emit IOComplete(nullptr);
}

void LocoIOData::setDirty(bool bDirty)
{
 this->bDirty = bDirty;
}
void LocoIOData::setDirty(int row, bool bDirty)
{
 _dirty[row] = bDirty;
 this->bDirty = false;
 foreach(bool b, _dirty)
  if(b) this->bDirty = true;
 //emit dirtyChanged(this->bDirty);
}
bool LocoIOData::dirty()
{
 return this->bDirty;
}
void LocoIOData::setX2Dirty(int row, bool bDirty)
{
 _x2Dirty[row] = bDirty;
 this->bX2Dirty = false;
 foreach(bool b, _x2Dirty)
  if(b) this->bX2Dirty = true;
 //emit dirtyChanged(this->bX2Dirty);
}
bool LocoIOData::x2Dirty()
{
 return this->bX2Dirty;
}
void LocoIOData::setServoDirty(int row, bool bDirty)
{
 _servoDirty[row] = bDirty;
 this->bDirty = false;
 foreach(bool b, _servoDirty)
  if(b) this->bServoDirty = true;
 //emit dirtyChanged(this->bDirty);
}
bool LocoIOData::servoDirty()
{
 return this->bServoDirty;
}

QList<int>* LocoIOData::getVals()
{
 return vals;
}
void LocoIOData::getConfig()
{
 bReadingConfig = true;
 lastOpCv=0;
 sendReadCommand(unitAddress | 0x100, unitSubAddress, 0);
}

void LocoIOData::getOption(int cv)
{
 bReadingOption = true;
 lastOpCv=cv;
 sendReadCommand(unitAddress, unitSubAddress, cv);
}
void LocoIOData::setOption(int cv, int val)
{
 bSettingOption = true;
 lastOpCv = -1;
 sendWriteCommand(unitAddress, unitSubAddress,cv,val);
}

void LocoIOData::startProbe()
{
 probedAddresses.clear();
 probeTimer->start(TIMEOUT);
 lastOpCv = 0;
 bProbing = true;
 LocoIO::probeLocoIOs(tc);
}
void LocoIOData::probeTimeout()
{
// if(timeoutcounter-- > 0)
// {
//  LocoNetMessage* msg = new LocoNetMessage(2);
//  msg->setOpCode(LnConstants::OPC_GPBUSY);
//  tc->sendLocoNetMessage(msg);
//  probeTimer->start(TIMEOUT);
//  startTimer();        // and set timeout on reply
//  return;
// }
 bProbing = false;
 probeTimer->stop();
 qSort(probedAddresses.begin(), probedAddresses.end());
 emit probeCompleted(probedAddresses);
}
void LocoIOData::emitAll()
{
 for(int i = 0; i < numRows(); i++)
 {
  emit AddrChanged(i, 0, addr[i], ssWhite);
  emit V1Changed(i, 0, addr[i], ssWhite);
  emit V2Changed(i, 0, addr[i], ssWhite);
  emit SVChanged(i, 0, addr[i], ssWhite);
 }
}
bool LocoIOData::busy() {return lastOpCv != -1;}
void LocoIOData::setModuleType(QString sType)
{
 moduleType = sType;
}
QString LocoIOData::getModuleType() { return moduleType;}
void LocoIOData::translateModeList()
{
  validmodes = new LocoIOModeList();
}
LnTrafficController* LocoIOData::getTrafficController() { return tc;}

QList<LocoIOAddress*> LocoIOData::getProbedAddresses() {return probedAddresses;}

QString LocoIOData::getFirmwareVersion() {return firmwareVersion;}
