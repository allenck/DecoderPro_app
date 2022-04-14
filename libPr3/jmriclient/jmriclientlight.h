#ifndef JMRICLIENTLIGHT_H
#define JMRICLIENTLIGHT_H
#include "abstractlight.h"

class AbstractMRListener;
class JMRIClientMessage;
class JMRIClientReply;
class JMRIClientSystemConnectionMemo;
class JMRIClientTrafficController;
class JMRIClientLight : public AbstractLight
{
public:
 JMRIClientLight(int number, JMRIClientSystemConnectionMemo* memo, QObject* parent = nullptr);
 /*public*/ int getNumber();
 /*public*/ void requestUpdateFromLayout() override;
 /*public*/ /*synchronized*/ void doNewState(int oldState, int s);
 /*public*/ /*synchronized*/ void reply(JMRIClientReply* m);
 /*public*/ void message(JMRIClientMessage* m);
 //QObject* self() override {return this;}

 QObject* pself() override{return (QObject*)this;}

private:
 static Logger* log;
 // data members
 /*private*/ int _number;   // light number
 /*private*/ JMRIClientTrafficController* tc = nullptr;
 /*private*/ QString transmitName;// = null;

protected:
 /*protected*/ void sendMessage(bool on);

};

#endif // JMRICLIENTLIGHT_H
