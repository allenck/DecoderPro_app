#ifndef NMRAPACKET_H
#define NMRAPACKET_H
#include <QByteArray>
#include "logger.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT NmraPacket
{
public:
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


private:
    /**
     * Objects of this class should not be created.
     */
    /*private*/ NmraPacket() {}
    static bool addressCheck(int address, bool longAddr);
protected:
    /*protected*/ static QByteArray accSignalDecoderPktCommon(int lowAddr, int boardAddr, int aspect);

};

#endif // NMRAPACKET_H
