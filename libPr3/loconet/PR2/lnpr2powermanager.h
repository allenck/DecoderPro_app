#ifndef LNPR2POWERMANAGER_H
#define LNPR2POWERMANAGER_H
#include "lnpowermanager.h"

class LnOpsModeProgrammer;
class LnPr2PowerManager : public LnPowerManager
{
public:
 /*public*/ LnPr2PowerManager(LocoNetSystemConnectionMemo* memo, QObject* parent = nullptr);
 /*public*/ void setPower(int v) /*throw (JmriException)*/;
 /*public*/ void message(LocoNetMessage* m);

public slots:
 void refresh();

private:
 // timer support to send updates & keep power alive
 QTimer* timer = nullptr;
 LnOpsModeProgrammer* pm = nullptr;
 SlotManager* sm;
 LnTrafficController* tc;
 LocoNetSystemConnectionMemo* memo;
 /*private*/ void checkOpsProg() /*throw (JmriException)*/;

};

#endif // LNPR2POWERMANAGER_H
