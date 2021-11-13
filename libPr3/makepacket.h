#ifndef MAKEPACKET_H
#define MAKEPACKET_H
#include <QByteArray>
#include <QVector>

class MakePacket
 {
 public:
    /*private*/ /*static*/ class Node {
      public:
      int bitPattern;
      int patternLength;
  };

  protected:
  MakePacket();

 public:
  /*public*/ static bool setPreambleLength(int preambleLen);
  /*public*/ static QVector<int> createStream(QByteArray packet);


 private:
  /*private*/ static int preambleLength;// = 15;
  /* This should be a multiple of 5. */
  /*private*/ static /*final*/  const int BITSTREAM_BITS_PER_BYTE = 9;
  /* number of bits per byte/
    nmra   s01234567s (hex equiv - note that in signal, 0 bit is left) */
  /*private*/ static /*final*/  const int BITS_0 = 0xF0; /* 0      _____----- (0xF0) */

  /*private*/ static /*final*/  const int BITS_00 = 0xC6; /* 00     __--___--- (0xC6) */

  /*private*/ static /*final*/  const int BITS_01 = 0x78; /* 01     ____----_- (0x78) */

  /*private*/ static /*final*/  const int BITS_10 = 0xE1; /* 10     _-____---- (0xE1) */

  /*private*/ static /*final*/  const int BITS_001 = 0x66; /* 001    __--__--_- (0x66) */

  /*private*/ static /*final*/  const int BITS_010 = 0x96; /* 010    __--_-__-- (0x96) */

  /*private*/ static /*final*/  const int BITS_011 = 0x5C; /* 011    ___---_-_- (0x5C) */

  /*private*/ static /*final*/  const int BITS_100 = 0x99; /* 100    _-__--__-- (0x99) */

  /*private*/ static /*final*/  const int BITS_101 = 0x71; /* 101    _-___---_- (0x71) */

  /*private*/ static /*final*/  const int BITS_110 = 0xC5; /* 110    _-_-___--- (0xC5) */

  /*private*/ static /*final*/  const int BITS_0111 = 0x56; /* 0111   __--_-_-_- (0x56) */

  /*private*/ static /*final*/  const int BITS_1011 = 0x59; /* 1011   _-__--_-_- (0x59) */

  /*private*/ static /*final*/  const int BITS_1101 = 0x65; /* 1101   _-_-__--_- (0x65) */

  /*private*/ static /*final*/  const int BITS_1110 = 0x95; /* 1110   _-_-_-__-- (0x95) */

  /*private*/ static /*final*/  const int BITS_11111 = 0x55; /* 11111  _-_-_-_-_- (0x55) */

  static QVector<int> bitStreamToSerialBytes(QVector<int> inputBitStream);
  static bool readNextChild(Node thisNode);
  static bool readFirstChild(QVector<int> bs,int offset, int validBits, Node thisNode);

};
#endif // MAKEPACKET_H
