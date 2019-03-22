#ifndef JMRICLIENTTRAFFICCONTROLLER_H
#define JMRICLIENTTRAFFICCONTROLLER_H
#include "abstractmrtrafficcontroller.h"

class JMRIClientMessage;
class JMRIClientListener;
class JMRIClientTrafficController : public AbstractMRTrafficController
{
public:
 JMRIClientTrafficController(QObject*parent = nullptr);
 /*public*/ /*synchronized*/ void addJMRIClientListener(JMRIClientListener* l);
 /*public*/ /*synchronized*/ void removeJMRIClientListener(JMRIClientListener* l);
 /*public*/ void sendJMRIClientMessage(JMRIClientMessage* m, JMRIClientListener* reply);

protected:
 /*protected*/ void forwardMessage(AbstractMRListener* client, AbstractMRMessage* m);
 /*protected*/ void forwardReply(AbstractMRListener* client, AbstractMRReply* m);
 /*protected*/ AbstractMRMessage* pollMessage();
 /*protected*/ AbstractMRListener* pollReplyHandler();
 /*protected*/ AbstractMRMessage* enterProgMode();
 /*protected*/ AbstractMRMessage* enterNormalMode();
 /*protected*/ AbstractMRReply* newReply();
 /*protected*/ bool endOfMessage(AbstractMRReply* msg);

};

#endif // JMRICLIENTTRAFFICCONTROLLER_H
