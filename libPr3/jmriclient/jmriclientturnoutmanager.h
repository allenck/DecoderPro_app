#ifndef JMRICLIENTTURNOUTMANAGER_H
#define JMRICLIENTTURNOUTMANAGER_H
#include "abstractturnoutmanager.h"

class JMRIClientSystemConnectionMemo;
class JMRIClientTurnoutManager : public AbstractTurnoutManager
{
public:
 JMRIClientTurnoutManager(JMRIClientSystemConnectionMemo* memo, QObject* parent = nullptr);
 /*public*/ SystemConnectionMemo* getMemo();

 /*public*/ Turnout* createNewTurnout(QString systemName, QString userName)const;
 /*public*/ QString createSystemName(QString curAddress, QString prefix) throw (JmriException);
 /*public*/ bool allowMultipleAdditions(QString systemName);

private:
 /*private*/ JMRIClientSystemConnectionMemo* memo = nullptr;
 /*private*/ QString prefix;// = null;

};

#endif // JMRICLIENTTURNOUTMANAGER_H
