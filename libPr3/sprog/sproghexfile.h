#ifndef SPROGHEXFILE_H
#define SPROGHEXFILE_H
#include "jmrijframe.h"
#include "file.h"

namespace Sprog
{
 class SprogHexFile : public JmriJFrame
 {
 public:
  /*public*/ SprogHexFile(QString fileName, QWidget* parent = 0);
  /*public*/ QString getName();
  /*public*/ bool openRd();
  /*public*/ bool openWr();
  /*public*/ void close();
  /*public*/ int read();
  /*public*/ QVector<int> readLine();
  /*public*/ void write(int addr, char type, QByteArray data);
  /*public*/ void wrExtAddr(int addr);
  /*public*/ void wrEof();
  /*public*/ int getRecordType();
  /*public*/ int getLen();
  /*public*/ int getAddress();
  /*public*/ char getAddressL();
  /*public*/ char getAddressH();
  /*public*/ char getAddressU();
  /*public*/ QVector<int> getData();


 private:
  /*private*/ /*final*/ static Logger* log;
  /*private*/ File* file;
  /*private*/ QDataStream* in;
//  /*private*/ BufferedInputStream buffIn;
  /*private*/ QDataStream* out;
//  /*private*/ BufferedOutputStream buffOut;
  /*private*/ int address = 0;
  /*private*/ int type;
  /*private*/ int len;
  /*private*/ QVector<int> data;
  /*private*/ bool _read;
  /*private*/ int lineNo = 0;
  /*private*/ int charIn;
  /*private*/ QString name;
  static /*final*/ char EXT_ADDR;// = 4;
  static /*final*/ char DATA;// = 0;
  static /*final*/ char END;// = 1;
  /*private*/ static /*final*/ int MAX_LEN;// = (255 + 1 + 2 + 1 + 1) * 2;
  // Offsets of fields within the record
  /*private*/ static /*final*/ int LEN;// = 0;
  /*private*/ static /*final*/ int ADDRH;// = 1;
  /*private*/ static /*final*/ int ADDRL;// = 2;
  /*private*/ static /*final*/ int TYPE;// = 3;
  /*private*/ int rdHexByte();
  /*private*/ int rdHexDigit();
  /*private*/ void writeLine(QByteArray data);
  /*private*/ void writeHexByte(char b);
  /*private*/ void writeHexDigit(char b);

 };
}
#endif // SPROGHEXFILE_H
