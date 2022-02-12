#ifndef JMRICLIENTREPORTER_H
#define JMRICLIENTREPORTER_H
#include "abstractreporter.h"

class AbstractMRListener;
class JMRIClientTrafficController;
class JMRIClientMessage;
class JMRIClientReply;
class JMRIClientSystemConnectionMemo;
class JMRIClientReporter : public AbstractReporter
{
public:
 JMRIClientReporter(int number, JMRIClientSystemConnectionMemo *memo, QObject* parent = nullptr);
 /*public*/ int getNumber();
 /*public*/ void requestUpdateFromLayout();
 /*public*/ void reply(JMRIClientReply* m);
 /*public*/ void message(JMRIClientMessage* m);
 /*public*/ void setState(int s);
 /*public*/ int getState();

 QObject* self() override{return (QObject*)this;}
private:
 static Logger* log;
 /*private*/ int state = UNKNOWN;
 // data members
 /*private*/ int _number;   // reporter number
 /*private*/ JMRIClientTrafficController* tc = nullptr;
 /*private*/ QString transmitName;// = null;


};

#endif // JMRICLIENTREPORTER_H
