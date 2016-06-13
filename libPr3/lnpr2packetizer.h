#ifndef LNPR2PACKETIZER_H
#define LNPR2PACKETIZER_H

#include "lnpacketizer.h"

class LnPr2Packetizer : public LnPacketizer
{
 Q_OBJECT
public:
    LnPr2Packetizer(QObject* parent = 0);
private:
    /*final*/ static bool fulldebug;// = false;

    bool debug;// = false;
    Logger* log;
};

#endif // LNPR2PACKETIZER_H
