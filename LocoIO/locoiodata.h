#ifndef LOCOIODATA_H
#define LOCOIODATA_H
#include "lnpacketizer.h"
#include "locoiomode.h"
#include "locoiomodelist.h"
#include <QObject>
#include <QVector>
#include <QPalette>
//#include "libPr3_global.h"
#include "locoio_global.h"
#include "locoioaddress.h"


class LocoIOAddress;
class PropertyChangeSupport;
/* CV usage
 * CV
 *  0       Configuration byte:
 *          bit 0 port refresh
 *          bit 1 Alt code pbs
 *          bit 2 On if LocoBooster
 *          bit 3 On if LocoServo
 *          bits 4-7 Blink rate
 *  1       Unit Address
 *  2       Unit SubAddress
 *  3-50    16 groups of three(Config, value 2, value 2)
 *  51-98   16 groups of 3 Extra OpCode 1 values(OPC, Arg1, Arg2)
 *  101-124 8 groups of 3Servo Positions and speed values (speed, Position 1, Position 2)
 *  125     Unused?
 *  126     Unused?
 *  127     Holds value for determining power up checking options (Only for LocoBooster and LocoServo)
 *  128-177 16 groups of 3 Extra OpCode 2 values(OPC, Arg1, Arg2)
 */
Q_DECLARE_METATYPE(QList<int>*)
class LocoIOMode;
class LocoIOModeList;
class LOCOIOSHARED_EXPORT LocoIOData : public QObject
{
    Q_OBJECT

public:
 //explicit LocoIOData(QObject *parent = 0);
 ~LocoIOData();
 /*public*/ LocoIOData(LocoIOAddress* address, LnTrafficController* tc, QObject* parent = nullptr);
 /** Creates a new instance of LocoIOData */
 /*public*/ LocoIOData(int unitAddr, int unitSubAddr, LnTrafficController* tc, QObject* parent = nullptr);
 LocoIOData(const LocoIOData&);
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
 /*public synchronized*/ void changeUnitAddress(int unit, int unitSub);
 /*public synchronized*/ void setUnitAddress(int unit, int unitSub);
 /*public synchronized*/ void setUnitAddress(int unit);
 /*public synchronized*/ void setUnitSubAddress(int unitSub);
 /*public synchronized*/ int getUnitAddress();
 /*public synchronized*/ int getUnitSubAddress();
 /**
  * TODO: LocoIO Board level configuration
  *<p>
  * Bit 0: 0 =default, 1=Port Refresh<br>
  * Bit 1: 0 = Fixed code PBs, 1= Alternated code PBs<br>
  * Bit 2: 0 = default - Not used<br>
  * Bit 3: 0 = default, 1 = Ports 5-12 are Servo Ports<br>
  * Bit 4-7: Blink Rate<br>
  */
 /*public*/ void setUnitConfig(int portRefresh, int altCodePBs, int isServo, int blinkRate, int is4Pos = 0);
 /*public*/ int getUnitConfig();
 int getBlinkRate();
 void setBlinkRate(int iBlinkRate);
 int getAltCodePBs();
 void setAltCodePBs(int val);
 int getIsServo();
 void setIsServo(int val);
 void setIs4Pos(int val);
 int getIsBooster();
 void setIsBooster(int val);
 /*public*/ void setLBVersion(QString version);
 /*public*/ QString getLBVersion();
 /*public*/ void setLIOVersion(QString version);
 /*public*/ QString getLIOVersion();
 /*public*/ void setStatus(QString msg);
 /*public*/ QString getStatus();
 /*public*/ void setSV(int channel, int value, QString ss = "rgb(152,251,152)");
 /*public*/ int getSV(int channel);
 /*public*/ void setV1(int channel, LocoIOMode* l, int address, QString ss = "");
 /*public*/ void setV1(int channel, int value, QString ss = "rgb(152,251,152)");
 /*public*/ int getV1(int channel);
 /*public*/ void setV2(int channel, LocoIOMode* l, int address, QString ss = "");
 /*public*/ void setV2(int channel, int value, QString ss = "rgb(152,251,152)");
 /*public*/ int getV2(int channel);
 /**
  * The addr field (for the address info used in each LocoIO channel)
  *
  * @param channel integer value of the addresses in use for this row (0=invalid)
  */
 /*public*/ void setAddr(int channel, int value, QString ss = "rgb(152,251,152)");
 /*public*/ int getAddr(int channel);
 // Extra 2 values
 /*public*/ void setX2SV(int channel, int value, QString ss = "rgb(152,251,152)");
 /*public*/ int getX2SV(int channel);
 /*public*/ void setX2V1(int channel, LocoIOMode* l, int address);
 /*public*/ void setX2V1(int channel, int value, QString ss = "rgb(152,251,152)");
 /*public*/ int getX2V1(int channel);
 /*public*/ void setX2V2(int channel, LocoIOMode* l, int address);
 /*public*/ void setX2V2(int channel, int value, QString ss = "rgb(152,251,152)");
 /*public*/ int getX2V2(int channel);
 void setServoP1(int channel, int value, QString ss = "rgb(152,251,152)");
 void setServoP2(int channel, int value, QString ss = "rgb(152,251,152)");
 void setServoSpeed(int channel, int value, QString ss=  "rgb(152,251,152)");
 int getServoP1(int iServo);
 int getServoP2(int iServo);
 int getServoSpeed(int iServo);
 void setSV7D(int data);
 void setSV7E(int data);
 void setSV7F(int data);
 int getSV7D();
 int getSV7E();
 int getSV7F();
 void readSV0();
 void readSV125();
 void readSV7D();
 void writeSV7D();

 /**
  * The addr field (for the address info used in each LocoIO channel)
  *
  * @param channel integer value of the addresses in use for this row (0=invalid)
  */
 /*public*/ void setX2Addr(int channel, int value, QString ss);
 /*public*/ int getX2Addr(int channel);

 /*public*/ void setMode(int channel, QString m);
 /*public*/ QString getMode(int channel);
 /*public*/ void setLIM(int channel, QString s);
 /*public*/ void setLIM(int channel);
 /*public*/ void setLIM(int channel, LocoIOMode* m);
 /*public*/ LocoIOMode* getLIM(int channel);
 /*public*/ void readValues(int channel);
 /*public*/ void readX2Values(int channel);
 /*public*/ void readServoValues(int channel);

 /*public*/ void captureValues(int channel);
 /*public*/ void writeValues(int channel);
 /*public*/ void writeX2Values(int channel);
 /*public*/ void writeServoValues(int channel);

 /**
  * Start reading all rows back
  */
 /*public*/ void readAll();
 /*public*/ void readAllX2();
 void readAllServo();
 void readAllCVs();
 /**
  * Start writing all rows out
  */
 /*public*/ void writeAll();
 void writeAllX2();
 void writeAllServo();
 void writeAllCVs();
 /*public*/ LocoIOModeList* getLocoIOModeList();
 /*public*/ void dispose();

 void setDefaults();
 QList<int>* defaults();
 QList<int>* getVals();
 void setDirty(int row, bool bDirty);
 void setX2Dirty(int row, bool bDirty);
 void setServoDirty(int row, bool bDirty);
 bool dirty();
 bool x2Dirty();
 bool servoDirty();
 void getCVs();
 void setCVs(QVector<int>* cvs);
 void setValues(QList<int>* vals);
 void getConfig();
 void getOption(int cv);
 void setOption(int cv, int val);
 int numRows();
//    QPalette* pGreen;
//    QPalette* pGray;
//    QPalette* pRed;
//    QPalette* pYellow;
//    QPalette* pWhite;
//    QPalette* pMagenta;
 QString ssGreen;
 QString ssGray;
 QString ssPink;
 QString ssRed;
 QString ssYellow;
 QString ssLightYellow;
 QString ssWhite;
 QString ssMagenta;
 QString ssBlueGreen;
 QString ssPurple;
 QString ssBlack;
 QString ssLtBlue;
 QList<LocoIOAddress*> getProbedAddresses();

 void startProbe();
 bool bProbing;
 void emitAll();
 bool busy();
 void setModuleType(QString sType);
 QString getModuleType();
 void translateModeList();
 /**
  * Read a SV from a given LocoIO device
  *
  * @param locoIOAddress
  * @param locoIOSubAddress
  * @param cv
  */
 void sendReadCommand(int locoIOAddress, int locoIOSubAddress, int cv);
 /*public*/ void addPropertyChangeListener(PropertyChangeListener* pcl);
 /*public*/ void removePropertyChangeListener(PropertyChangeListener* pcl);
 LnTrafficController* getTrafficController();

signals:
 //void firePropertyChange(QString s_property, QVariant oldVal, QVariant newVal);
 void notifyPropertyChange(PropertyChangeEvent*);
 void dirtyChanged(bool bDirty);
 void cvRead(int cv, int value);
 void IOComplete(QList<int>*);
 void IOCompleteX2(QList<int>*);
 void IOCompleteServo();
 void IOComplete7D();
 void IOComplete0();
 void IOComplete125();
 void configRead(int value, LocoIOData* data);
 void optionByte(int cv, int value);
 void AddrChanged(int channel, int iOld, int iNew, QString ss);
 void SVChanged(int channel, int iOld, int iNew, QString ss);
 void V1Changed(int channel, int iOld, int iNew, QString ss);
 void V2Changed(int channel, int iOld, int iNew, QString ss);
 void X2AddrChanged(int channel, int iOld, int iNew, QString ss);
 void X2SVChanged(int channel, int iOld, int iNew, QString ss);
 void X2V1Changed(int channel, int iOld, int iNew, QString ss);
 void X2V2Changed(int channel, int iOld, int iNew, QString ss);
 void ServoP1Changed(int iServo, int iOld, int iNew, QString ss);
 void ServoP2Changed(int iServo, int iOld, int iNew, QString ss);
 void ServoSpeedChanged(int iServo, int iOld, int iNew, QString ss);

 void probeCompleted(QList<LocoIOAddress*>);
 void readAllComplete();
 void writeAllComplete();
 void ioAborted();

public slots:
 /**
  * Listen to the LocoNet.
  * We're listening for incoming OPC_PEER_XFR messages, which might
  * be part of a read or write sequence.  We're also
  * _sometimes_ listening for commands as part of a "capture"
  * operation.
  *<P>
  * The incoming LocoNet OPC_PEER_XFR messages don't retain any information
  * about the CV number or whether it was a read or write operation.
  * We store the data regardless of whether it was read or write, but
  * we need to remember the cv number in the lastOpCv member.
  *<P>
  * @param m Incoming message
  */
 /*public synchronized*/ void message(LocoNetMessage* m);
 void onCvRead(int cv, int val);
 /*public*/ /*synchronized*/ void message_alt(LocoNetMessage* m);
 /*public*/ void propertyChange(PropertyChangeEvent* evt);
 QString getFirmwareVersion();

private:
 Logger* log;
 void common(int unitAddr, int unitSubAddr, LnTrafficController* tc);
 /*private*/ int sv0, sv0a, sv1, sv2;
 int sv7D;
 int sv7E;
 int sv7F;
 /*private*/ int unitAddress;
 /*private*/ int unitSubAddress;
 /*private*/ LnTrafficController* tc;
 QList<LocoIOAddress*> probedAddresses;
 /*
  * This data model is shared between several views; each
  * needs to know when the data changes out from under it.
  */
 /*private*/ PropertyChangeSupport* dataListeners;// = new PropertyChangeSupport(this);
 /**
  * Define the number of rows in the table, which is also
  * the number of "channels" in a signel LocoIO unit
  */
 /*private*/ int _numRows; // = 16;
 int _numRowsServo; // =8
 /**
  * LocoBuffer is always address 0x01 0x50
  */
 /*private*/ static /*final*/ const int LocoBufferAddress;//  = 0x0150;
 /*private*/ QString locoBufferVersion;// = "<unknown>";
 /*private*/ QString locoIOVersion;//     = "<unknown>";
 /*private*/ QString status;//            = "<unknown>";  // LocoIO activity status
 /**
  * Per-port SV data
  */
 /*private*/ QVector<LocoIOMode*> lim;// = new QVector<LocoIOMode>(_numRows);
 /*private*/ QVector<LocoIOMode*> x2lim;// = new QVector<LocoIOMode>(_numRows);
 /*private*/ QVector<int> addr;//    = new int[_numRows];
 /*private*/ QVector<int> sv;//      = new int[_numRows];
 /*private*/ QVector<int> v1;//      = new int[_numRows];
 /*private*/ QVector<int> v2;//      = new int[_numRows];
 /*private*/ QVector<int> x2addr;//    = new int[_numRows];
 /*private*/ QVector<int> x2sv;//      = new int[_numRows];
 /*private*/ QVector<int> x2v1;//      = new int[_numRows];
 /*private*/ QVector<int> x2v2;//      = new int[_numRows];
 /*private*/ QVector<int> readState;//  = new int[_numRows];
 /*private*/ QVector<int> writeState;// = new int[_numRows];
 /*private*/ QVector<int> readStateX2;//  = new int[_numRows];
 /*private*/ QVector<int> writeStateX2;// = new int[_numRows];
 QVector<int> servoP1;
 QVector<int> servoP2;
 QVector<int> servoSpd;
 QVector<int> readStateServo;
 QVector<int> writeStateServo;
 int readState7D;
 int writeState7D;
 int readState0;
 int writeState0;
 int readState125;
 int writeState125;

 QVector<bool> _dirty;
 QVector<bool> _x2Dirty;
 QVector<bool> _servoDirty;
 bool b3ByteRead;
 /**
  * Record whether this pin is looking to capture a value
  * from the LocoNet
  */

 /*private*/ QVector<bool> capture;//    = new boolean[_numRows];
 /*private*/ QStringList mode;// = new String[_numRows];

 /*private*/ LocoIOModeList* validmodes;
 /*private*/ int lastOpCv;// = -1;
 /*private*/ bool reading;// = false;  // false means write in progress
 //private boolean writing = false;
 /*private*/ QString dotme(int val);
 /*private*/ int currentPin;// = 0;
 bool bReadingConfig;
 bool bReadingOption;
 bool bSettingOption;
 /**
  * Timer Management
  * Protect against communication failures,
  * addressing mixups and the like.
  */
 static const int TIMEOUT=2000;    // ms
 /*protected javax.swing.Timer*/ QTimer* timer;
 /*private*/ int timeoutcounter;
 QTimer* probeTimer;
 /**
  * Write an SV to a given LocoIO device
  *
  * @param locoIOAddress
  * @param locoIOSubAddress
  * @param cv
   *@param data
  */
 void sendWriteCommand(int locoIOAddress, int locoIOSubAddress, int cv, int data);
 void issueNextReadCv();

 QList<int> _defaults;
 QMutex mutex1;
 QMutex mutex2;
 QMutex mutexEx2;
 QMutex mutex2S;
 QMutex mutex7D;
 QMutex mutex2N;
 QMutex mutex3;
 QMutex mutex4;
 QMutex mutex5;
 QMutex mutex6;
 QMutex mutex7;
 QMutex mutex8;
 QMutex mutex9;
 bool bDirty;
 void setDirty(bool bDirty);
 bool bX2Dirty;
 void setX2Dirty(bool bX2Dirty);
 bool bServoDirty;
 void setServoDirty(bool bServoDirty);
 QList<int>* vals;
 QString moduleType;
 bool bWritingAll;
 bool bReadingAll;
 int readWriteState;
 int readWriteType; // 0 base, 1 extra, 2 servo
 bool checkWriteResponse(int locoIOAddress, int locoIOSubAddress, int cv, int data);
 QString firmwareVersion;
 LocoIOAddress* locoIOAddress;

protected:
 /**
  * Code for read activity needed.  See states
  * NONE, READMODE, READINGMODE,
  * READVALUE1, READINGVALUE1,
  * READVALUE2, READINGVALUE2
  */
 // int[] needRead = new int[_numRows];

 static const int NONE;// = 0;
 static const int READVALUE1;// = 1;
 static const int READINGVALUE1;// = 2;
 static const int READVALUE2;// = 3;
 static const int READINGVALUE2;// = 4;
 static const int READMODE;// = 5;
 static const int READINGMODE;// = 6;

/* protected final*/ int READ;// = READVALUE1;  // starting state

 /**
  * Code for write activity needed.  See states
  * NONE, WRITEMODE, WRITINGMODE,
  * WRITEVALUE1, WRITINGVALUE1,
  * WRITEVALUE2, WRITINGVALUE2
  */
 // int[] needWrite = new int[_numRows];

 static const int WRITEVALUE1 = 11;
 static const int WRITINGVALUE1 = 12;
 static const int WRITEVALUE2 = 13;
 static const int WRITINGVALUE2 = 14;
 static const int WRITEMODE = 15;
 static const int WRITINGMODE = 16;

 /*protected final*/ int WRITE;// = WRITEVALUE1;  // starting state
 /*protected*/ int highPart(int value);
 /*protected*/ int lowPart(int value); // generally value 2

 /**
  * A valid reply has been received, so the read/write
  * worked, and the state should be advanced.
  */
 /*protected synchronized*/ void replyReceived();

 /**
  * Look through the table to find the next thing that
  * needs to be read.
  */
 /*protected synchronized*/ void issueNextOperation();
 void issueNextExtra2Operation();
 void issueNextServoOperation();
 /*protected synchronized*/ void issueNext7DOperation();
 /*protected synchronized*/ void issueNext0Operation();
 /*protected synchronized*/ void issueNext125Operation();

 /**
  * Internal routine to start timer to protect the mode-change.
  */
 /*protected*/ void startTimer();
 /**
  * Internal routine to stop timer, as all is well
  */
 /*protected*/ void stopTimer();

 /**
  * Internal routine to handle timer starts & restarts
  */
 /*protected*/ void restartTimer(int delay);
private slots:
 /**
  * Internal routine to handle a timeout during read/write
  * by retrying the same operation.
  */
 /*synchronized protected*/ void timeout();
 void probeTimeout();
 void readWriteNext();

};

class ResponseCheck : public QObject
{
 Q_OBJECT
 int svUnitAddr, svUnitSubAddr, svCv, svData;
 LnTrafficController* tc;
 Logger* log;
 QString dotme(int);
 bool bResult;
public:
 ResponseCheck(int unitAddr, int unitSubAddr, int cv, int data, LnTrafficController* tc);
 ~ResponseCheck();
 bool getResult();
signals:
 void finished();
private slots:
 void processWriteResponse(LocoNetMessage* );
 void process();
};

#endif // LOCOIODATA_H
