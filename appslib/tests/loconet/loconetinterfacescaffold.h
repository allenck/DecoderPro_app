#ifndef LOCONETINTERFACESCAFFOLD_H
#define LOCONETINTERFACESCAFFOLD_H
#include "lntrafficcontroller.h"

class LocoNetSystemConnectionMemo;
class LocoNetInterfaceScaffold : public LnTrafficController
{
public:
    LocoNetInterfaceScaffold();
    /*public*/ LocoNetInterfaceScaffold(LocoNetSystemConnectionMemo* adaptermemo);
    /*public*/ bool status();
    /*public*/ void sendLocoNetMessage(LocoNetMessage* m);
    /*public*/ bool isXmtBusy();
    /*public*/ void sendTestMessage(LocoNetMessage* m) ;
    /*public*/ int numListeners();
    /*public*/ QVector<LocoNetListener*> getListeners();

private:
    static Logger* log;
    void forwardMessage(int i);
    /**
     * Record LocoNet messages sent, provide access for making sure they are OK.
     */
    QVector<LocoNetMessage*> outbound;// = new Vector<LocoNetMessage>();  // /*public*/ OK here, so long as this is a test class

 friend class SlotManagerTest;
};

#endif // LOCONETINTERFACESCAFFOLD_H
