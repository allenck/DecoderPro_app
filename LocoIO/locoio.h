#ifndef LOCOIO_H
#define LOCOIO_H

#include <QObject>
#include "loconetmessage.h"
#include "pr3adapter.h"
//#include "libPr3_global.h"
#include "locoio_global.h"

class LOCOIOSHARED_EXPORT LocoIO : public QObject
{
    Q_OBJECT
public:
    explicit LocoIO(QObject *parent = 0);
    static int LOCOIO_SV_WRITE;//             = 0x01;
    static int LOCOIO_SV_READ;//              = 0x02;
    static int LOCOIO_BROADCAST_ADDRESS;//    = 0x1000; // LocoIO broadcast

    static int LOCOIO_PEER_CODE_7BIT_ADDRS;// = 0x00;
    static int LOCOIO_PEER_CODE_ANSI_TEXT;//  = 0x00;
    static int LOCOIO_PEER_CODE_SV_VER1;//    = 0x08;
    static int LOCOIO_PEER_CODE_SV_VER2;//    = 0x09;
    static int LOCOIO_DISCOVER;//             = 0x07;
    /*public*/ static int SENSOR_ADR(int a1, int a2);
    /*public*/ static LocoNetMessage* readCV(int locoIOAddress, int locoIOSubAddress, int cv);
    /*public*/ static LocoNetMessage* writeCV(int locoIOAddress, int locoIOSubAddress, int cv, int data);
    /*public*/ static void programLocoIOAddress(int address, int subAddress, LnTrafficController* ln);
    /*public*/ static void probeLocoIOs(LnTrafficController* ln);
    static void discover(LnTrafficController* ln);

signals:
    
public slots:
    
};

#endif // LOCOIO_H
