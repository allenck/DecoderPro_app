#ifndef LNPACKETIZERSTRICT_H
#define LNPACKETIZERSTRICT_H
#include "lnpacketizer.h"

class LnPacketizerStrict : public LnPacketizer
{
 Q_OBJECT
public:
 LnPacketizerStrict(LocoNetSystemConnectionMemo* m, QObject* parent = 0);
};

#endif // LNPACKETIZERSTRICT_H
