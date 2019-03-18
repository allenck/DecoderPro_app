#ifndef JMRICLIENTSYSTEMCONNECTIONMEMO_H
#define JMRICLIENTSYSTEMCONNECTIONMEMO_H
#include "systemconnectionmemo.h"

class PowerManager;
class ComponentFactory;
class JMRIClientTrafficController;
class JMRIClientSystemConnectionMemo : public SystemConnectionMemo
{
public:
 JMRIClientSystemConnectionMemo();
 /*public*/ JMRIClientSystemConnectionMemo(JMRIClientTrafficController* jt);
 /*public*/ JMRIClientTrafficController* getJMRIClientTrafficController();
 /*public*/ void setJMRIClientTrafficController(JMRIClientTrafficController* jt);
 /*public*/ void dispose();
 /*public*/ void configureManagers();
 /*public*/ void requestAllStatus();
 /*public*/ PowerManager* getPowerManager();
 /*public*/ void setPowerManager(PowerManager* p);

private:
 ComponentFactory* cf = nullptr;
 /*private*/ JMRIClientTrafficController* jt;
 /*private*/ PowerManager* powerManager = nullptr;

};

#endif // JMRICLIENTSYSTEMCONNECTIONMEMO_H
