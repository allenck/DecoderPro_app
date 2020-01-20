#ifndef LNPR2PACKETIZER_H
#define LNPR2PACKETIZER_H
#include "lnpacketizer.h"

class LnPr2Packetizer : public LnPacketizer
{
 Q_OBJECT
public:
 LnPr2Packetizer(QObject* parent = nullptr);// : LnPacketizer(new LocoNetSystemConnectionMemo(), parent) {}
 /**
  * Create a Packetizer against an existing LocoNetSystemConnectionMemo.
  * <p>
  * This allows for re-configuring an existing LocoNetSystemConnectionMemo,
  * which was created during PR3Adapter initialization, for use in the PR3's
  * "PR2 Mode" (i.e. "Standalone Programmer Mode".)
  *
  * @param memo pre-existing LocoNetSystemConnectionMemo
  */
 /*public*/ LnPr2Packetizer(LocoNetSystemConnectionMemo* memo, QObject* parent = nullptr);
};

#endif // LNPR2PACKTIZER_H
