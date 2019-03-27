#ifndef JMRICLIENTSENSOR_H
#define JMRICLIENTSENSOR_H
#include "abstractsensor.h"

class AbstractMRListener;
class JMRIClientMessage;
class JMRIClientReply;
class JMRIClientSystemConnectionMemo;
class JMRIClientTrafficController;
class JMRIClientSensor : public AbstractSensor
{
public:
 JMRIClientSensor(int number, JMRIClientSystemConnectionMemo* memo, QObject* parent = nullptr);
 /*public*/ int getNumber() ;
 /*public*/ void setKnownState(int s) throw (JmriException) ;
 /*public*/ void requestUpdateFromLayout();
 /*public*/ void reply(JMRIClientReply* m);
 /*public*/ void message(JMRIClientMessage *m);

private:
 static Logger* log;
 // data members
 /*private*/ int _number;   // sensor number
 /*private*/ JMRIClientTrafficController* tc = nullptr;
 /*private*/ QString transmitName;// = null;

protected:
 /*protected*/ void sendMessage(bool active);

};

#endif // JMRICLIENTSENSOR_H
