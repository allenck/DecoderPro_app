#ifndef JMRICLIENTMESSAGE_H
#define JMRICLIENTMESSAGE_H
#include "abstractmrmessage.h"

class JMRIClientMessage : public AbstractMRMessage
{
public:
 JMRIClientMessage();
 /*public*/ JMRIClientMessage(int i);
 /*public*/ JMRIClientMessage(JMRIClientMessage* m);
 /*public*/ JMRIClientMessage(QString m);
 /*public*/ bool isKillMain();
 /*public*/ bool isEnableMain();
 // static methods to return a formatted message
 static /*public*/ JMRIClientMessage* getEnableMain();
 static /*public*/ JMRIClientMessage* getKillMain();
 static /*public*/ JMRIClientMessage* getProgMode();
 static /*public*/ JMRIClientMessage* getExitProgMode();

protected:
 /*final*/ static /*protected*/ int LONG_TIMEOUT;// = 180000;  // e.g. for programming options

};

#endif // JMRICLIENTMESSAGE_H
