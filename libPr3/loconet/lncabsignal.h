#ifndef LNCABSIGNAL_H
#define LNCABSIGNAL_H
#include "defaultcabsignal.h"

class LocoNetSystemConnectionMemo;
class LnCabSignal : public DefaultCabSignal
{
public:
 LnCabSignal(LocoNetSystemConnectionMemo *memo, LocoAddress* address, QObject* parent = nullptr);
 /*public*/ void dispose();

private:
 /*private*/ LocoNetSystemConnectionMemo* _memo = nullptr;
 static Logger* log;

protected:
 /*protected*/ void forwardAspectToLayout();
 /*protected*/ void resetLayoutCabSignal();

};

#endif // LNCABSIGNAL_H
