#ifndef JMRICLIENTTURNOUTMANAGER_H
#define JMRICLIENTTURNOUTMANAGER_H
#include "abstractturnoutmanager.h"

class JMRIClientSystemConnectionMemo;
class JMRIClientTurnoutManager : public AbstractTurnoutManager
{
public:
 JMRIClientTurnoutManager(JMRIClientSystemConnectionMemo* memo, QObject* parent = nullptr);
 /*public*/ SystemConnectionMemo* getMemo();

 /*public*/ Turnout* createNewTurnout(QString systemName, QString userName)const override;
 /*public*/ QString createSystemName(QString curAddress, QString prefix)const throw (JmriException)override;
 /*public*/ bool allowMultipleAdditions(QString systemName) override;
 /*public*/ QString getNamedBeanClass()const override {
     return "Turnout";
 }

private:
 /*private*/ JMRIClientSystemConnectionMemo* memo = nullptr;
 /*private*/ QString prefix;// = null;

};

#endif // JMRICLIENTTURNOUTMANAGER_H
