#ifndef SPROGMESSAGE_H
#define SPROGMESSAGE_H
#include "abstractmrmessage.h"
#include "sprogconstants.h"
#include "programmingmode.h"

namespace Sprog {

 class SprogMessage : public AbstractMRMessage
 {
  Q_OBJECT
 public:
  SprogMessage(int i, QObject* parent = 0);
  // Special characters (NOTE: microchip bootloader does not use standard ASCII)
  /*public*/ static /*final*/ int STX;// = 15;
  /*public*/ static /*final*/ int DLE;// = 5;
  /*public*/ static /*final*/ int ETX;// = 4;
  /*public*/ static /*final*/ int CR;// = 0x0d;
  /*public*/ static /*final*/ int LF;// = 0x0a;

  // bootloader commands
  /*public*/ static /*final*/ int RD_VER;// = 0;
  /*public*/ static /*final*/ int WT_FLASH;// = 2;
  /*public*/ static /*final*/ int ER_FLASH;// = 3;
  /*public*/ static /*final*/ int WT_EEDATA;// = 5;
  /*public*/ static /*final*/ int MAXSIZE;// = 515;
  /*public*/ int getId();
  /*public*/ SprogMessage(QString s, QObject* parent = 0);
  /*public*/ SprogMessage(SprogMessage* m, QObject* parent = 0);
  /*public*/ void setElement(int n, int v);
  /*public*/ QString toString();
  /*public*/ QString toString(bool isSIIBootMode);
  /*public*/ SprogMessage(QByteArray packet);
  /*public*/ QByteArray getFormattedMessage(SprogConstants::SprogState sprogState);
  /*public*/ bool isKillMain();
  /*public*/ bool isEnableMain();
  // static methods to return a formatted message
  static /*public*/ SprogMessage* getEnableMain();
  static /*public*/ SprogMessage* getKillMain();
  QT_DEPRECATED static /*public*/ SprogMessage* getProgMode();
  QT_DEPRECATED static /*public*/ SprogMessage* getExitProgMode();
  static /*public*/ SprogMessage* getStatus();
  static /*public*/ SprogMessage* getReadCV(int cv, ProgrammingMode* mode);
  static /*public*/ SprogMessage* getWriteCV(int cv, int val, ProgrammingMode* mode);
  // [AC] 11/09/2002 SPROG doesn't currently support registered mode
  static /*public*/ SprogMessage* getReadRegister(int reg);
  static /*public*/ SprogMessage* getWriteRegister(int reg, int val);
  static /*public*/ SprogMessage* getPacketMessage(QByteArray bytes);
  static /*public*/ SprogMessage* getReadBootVersion();
  static /*public*/ SprogMessage* getWriteFlash(int addr, QVector<int> data, int blockLen);
  static /*public*/ SprogMessage* getV4WriteFlash(int addr, QVector<int> data, int type) ;
  static /*public*/ SprogMessage* getV4EndOfFile() ;
  static /*public*/ SprogMessage* getv4ExtAddr();
  static /*public*/ SprogMessage* getEraseFlash(int addr, int rows) ;
  static /*public*/ SprogMessage* getWriteEE(int addr, QVector<int> data);
  static /*public*/ SprogMessage* getReset();

 private:
  void common(int i);

  /*private*/ static int msgId;// = 0;
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogMessage");
  /*private*/ void setLength(int i);
  /*private*/ void setV4Length(int i);
  /*private*/ void setAddress(int i);
  /*private*/ void setV4Address(int i);
  /*private*/ void setV4RecType(int i);
  /*private*/ void setData(QVector<int> d);
  /*private*/ void setV4Data(QVector<int> d);
  /*private*/ void setChecksum() ;
  /*private*/ void setV4Checksum(int length, int addr, int type, QVector<int> data);
  /*private*/ int hexDigit(int b);
  /*private*/ SprogMessage* frame();
  /*private*/ SprogMessage* v4frame();
  /*private*/ static QString addSpace(SprogMessage* m, int offset);
  /*private*/ static QString addIntAsTwo(int val, SprogMessage* m, int offset);
  /*private*/ static QString addIntAsThree(int val, SprogMessage* m, int offset);
  /*private*/ static QString addIntAsFour(int val, SprogMessage* m, int offset);

 protected:
  /*protected*/ int _id;// = -1;
  /*protected*/ /*synchronized*/ int newMsgId();

 };
}
#endif // SPROGMESSAGE_H
