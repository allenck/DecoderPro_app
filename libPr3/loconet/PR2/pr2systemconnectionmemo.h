#ifndef PR2SYSTEMCONNECTIONMEMO_H
#define PR2SYSTEMCONNECTIONMEMO_H
#include "loconetsystemconnectionmemo.h"

class LnPr2PowerManager;
class LnPr2ThrottleManager;
class PR2SystemConnectionMemo : public LocoNetSystemConnectionMemo
{
public:
 PR2SystemConnectionMemo(QObject* parent = nullptr);
 /*public*/ PR2SystemConnectionMemo(LnTrafficController* lt, SlotManager* sm, QObject *parent = nullptr);
 /*public*/ void configureManagers();
 /*public*/ LnPr2PowerManager* getPowerPr2Manager();
 /*public*/ LnPr2ThrottleManager* getPr2ThrottleManager();
 /*public*/ /*<T>*/ Manager* get(QString type);
 /*public*/ bool provides(/*Class<?>*/QString type);
 /*public*/ void dispose();

private:
 static Logger* log;
 /*private*/ LnPr2PowerManager* powerPr2Manager;
 /*private*/ LnPr2ThrottleManager* throttlePr2Manager;

};

#endif // PR2SYSTEMCONNECTIONMEMO_H
