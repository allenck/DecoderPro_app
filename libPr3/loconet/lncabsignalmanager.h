#ifndef LNCABSIGNALMANAGER_H
#define LNCABSIGNALMANAGER_H
#include "abstractcabsignalmanager.h"

class LocoNetSystemConnectionMemo;
class LnCabSignalManager : public AbstractCabSignalManager
{
public:
 LnCabSignalManager(LocoNetSystemConnectionMemo* memo, QObject* parent = nullptr);
 QObject* self() {return (QObject*)this;}

private:
 static Logger* log;
 /*private*/ LocoNetSystemConnectionMemo* _memo = nullptr;

protected:
 /*protected*/ CabSignal* createCabSignal(LocoAddress* address);

};

#endif // LNCABSIGNALMANAGER_H
