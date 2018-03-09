#ifndef NMRAPACKET_H
#define NMRAPACKET_H
#include <QByteArray>
#include "logger.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT NmraPacket
{
public:
 /*public*/ static QByteArray idlePacket();

    /*public*/ static QByteArray accDecoderPkt(int addr, int active, int outputChannel);
    /*public*/ static QByteArray accDecoderPkt(int number, bool closed);
    /*public*/ static QByteArray function9Through12Packet(int address, bool longAddr, bool f9, bool f10, bool f11, bool f12 );
    /*public*/ static QByteArray function13Through20Packet(int address, bool longAddr, bool f13, bool f14, bool f15, bool f16,                                            bool f17, bool f18, bool f19, bool f20 );

    /*public*/ static QByteArray function21Through28Packet(int address, bool longAddr, bool f21, bool f22, bool f23, bool f24,                                                       bool f25, bool f26, bool f27, bool f28 );
    static /*final*/ /*public*/ int NOADDRESS;// = 1;
    static /*final*/ /*public*/ int LOCO_SHORT_ADDRESS;// = 2;
    static /*final*/ /*public*/ int LOCO_LONG_ADDRESS;// = 4;
    static /*final*/ /*public*/ int ACCESSORY_SHORT_ADDRESS;// = 8;
    /*public*/ static QByteArray accDecoderPktOpsMode(int number, int cvNum, int data);
    /*public*/ static QByteArray accDecoderPktOpsMode(int addr, int active, int outputChannel, int cvNum, int data);
    /*public*/ static QByteArray accDecoderPktOpsModeLegacy(int number, int cvNum, int data);
    /*public*/ static QByteArray accDecPktOpsModeLegacy(int addr, int cvNum, int data);
    /*public*/ static QByteArray  consistControl(int address, bool longAddr, int consist, bool directionNormal);
    /*public*/ static QByteArray altAccSignalDecoderPkt(int outputAddr, int aspect);
    /*public*/ static QByteArray speedStep128Packet(int address, bool longAddr, int speed, bool fwd );
    /*public*/ static QByteArray speedStep28Packet(bool full, int address, bool longAddr, int speed, bool fwd );
    /*public*/ static QByteArray opsCvWriteByte(int address, bool longAddr, int cvNum, int data );
    /*public*/ static QByteArray function5Through8Packet(int address, bool longAddr,
                        bool f5, bool f6, bool f7, bool f8 );
    /*public*/ static QByteArray oneBytePacket(int address, bool longAddr,
                            char arg1);
    /*public*/ static QByteArray twoBytePacket(int address, bool longAddr,
                            char arg1, char arg2);
    /*public*/ static QByteArray threeBytePacket(int address, bool longAddr,
                            char arg1, char arg2, char arg3);
    /*public*/ static QByteArray fourBytePacket(int address, bool longAddr,
                            char arg1, char arg2, char arg3, char arg4);

    /*public*/ static QByteArray function0Through4Packet(int address, bool longAddr,
                        bool f0, bool f1, bool f2, bool f3, bool f4 );
    /*public*/ static QByteArray accSignalDecoderPkt(int outputAddr, int aspect);
    /*public*/ static QByteArray accSignalDecoderPktOpsMode(int addr, int cvNum, int data);
    /*public*/ static QByteArray altAccSignalDecoderPktOpsMode(int addr, int cvNum, int data);
    /*public*/ static QByteArray accDecPktOpsMode(int decAddr, int cvNum, int data);

private:
    /**
     * Objects of this class should not be created.
     */
    /*private*/ NmraPacket() {}
    static bool addressCheck(int address, bool longAddr);
protected:
    /*protected*/ static QByteArray accSignalDecoderPktCommon(int lowAddr, int boardAddr, int aspect);
    static Logger* log;// = LoggerFactory:.getLogger("NmraPacket");

};

#endif // NMRAPACKET_H
