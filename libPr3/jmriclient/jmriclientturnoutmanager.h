#ifndef JMRICLIENTTURNOUTMANAGER_H
#define JMRICLIENTTURNOUTMANAGER_H
#include "abstractturnoutmanager.h"

class JMRIClientSystemConnectionMemo;
class JMRIClientTurnoutManager : public AbstractTurnoutManager
{
public:
 JMRIClientTurnoutManager(JMRIClientSystemConnectionMemo* memo, QObject* parent = nullptr);
 /*public*/ SystemConnectionMemo* getMemo()override;

 /*public*/ Turnout* createNewTurnout(QString systemName, QString userName) override;
 /*public*/ QString createSystemName(QString curAddress, QString prefix) /*throw (JmriException)*/override;
 /*public*/ bool allowMultipleAdditions(QString systemName) override;
 /*public*/ QString getNamedBeanClass()const override {
     return "Turnout";
 }
 QObject* self() override {return (QObject*)this;}

private:
 /*private*/ JMRIClientSystemConnectionMemo* memo = nullptr;
 /*private*/ QString prefix;// = null;

};

#endif // JMRICLIENTTURNOUTMANAGER_H
