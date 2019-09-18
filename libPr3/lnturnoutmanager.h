#ifndef LNTURNOUTMANAGER_H
#define LNTURNOUTMANAGER_H
#include "loconetinterface.h"
#include "abstractturnoutmanager.h"
#include "lntrafficcontroller.h"

//class AbstractTurnoutManager;
class LIBPR3SHARED_EXPORT LnTurnoutManager : public AbstractTurnoutManager
{
 Q_OBJECT
public:
    LnTurnoutManager(LnTrafficController* fastcontroller, LnTrafficController* throttledcontroller, QString prefix, bool mTurnoutNoRetry, QObject* parent = 0);
    /*public*/ LnTurnoutManager(LocoNetSystemConnectionMemo* memo, LocoNetInterface* throttledcontroller, bool mTurnoutNoRetry, QObject *parent = nullptr);
    virtual QString getSystemPrefix();
    virtual void dispose();
    virtual Turnout* createNewTurnout(QString systemName, QString userName);
public slots:
    // listen for turnouts, creating them as needed
    void message(LocoNetMessage* l);

private:
    LocoNetInterface* fastcontroller;
    LocoNetInterface* throttledcontroller;
    bool mTurnoutNoRetry;

    QString prefix;
    int address(int a1, int a2);
    // holds last seen turnout request for possible resend
    LocoNetMessage* lastSWREQ;


 Logger log;
};

#endif // LNTURNOUTMANAGER_H
