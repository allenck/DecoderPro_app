#ifndef LOCONETINTERFACESCAFFOLD_H
#define LOCONETINTERFACESCAFFOLD_H
#include "lntrafficcontroller.h"

class LocoNetSystemConnectionMemo;
class LocoNetInterfaceScaffold : public LnTrafficController
{
 Q_OBJECT
public:
    LocoNetInterfaceScaffold();
    /*public*/ LocoNetInterfaceScaffold(LocoNetSystemConnectionMemo* adaptermemo);
    /*public*/ bool status();
    /*public*/ void sendLocoNetMessage(LocoNetMessage* m);
    /*public*/ bool isXmtBusy();
    /*public*/ void sendTestMessage(LocoNetMessage* m) ;
    /*public*/ int numListeners();
    /*public*/ QVector<LocoNetListener*> getListeners();

signals:
    void sendMessage(LocoNetMessage *m);

private:
    static Logger* log;
    void forwardMessage(int i);
    /**
     * Record LocoNet messages sent, provide access for making sure they are OK.
     */
    QVector<LocoNetMessage*> outbound;// = new Vector<LocoNetMessage>();  // /*public*/ OK here, so long as this is a test class

 friend class SlotManagerTest;
 friend class LocoNetSlotTest;
 friend class LnOpsModeProgrammerTest;
 friend class LnTrafficRouterTest;
 friend class LnPowerManagerTest;
 friend class LnTurnoutTest;
 friend class ReleaseUntilO7;
 friend class LocoNetInterfaceScaffoldO2;
 friend class LnDeferProgrammerTest;
 friend class LnTurnoutManagerTest;
 friend class LocoNetThrottleTest;
 friend class LnPredefinedMetersTest;
};

#endif // LOCONETINTERFACESCAFFOLD_H
