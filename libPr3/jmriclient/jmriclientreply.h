#ifndef JMRICLIENTREPLY_H
#define JMRICLIENTREPLY_H
#include "abstractmrreply.h"


class JMRIClientReply : public AbstractMRReply
{
public:
 JMRIClientReply();
 /*public*/ JMRIClientReply(QString s);
 /*public*/ JMRIClientReply(JMRIClientReply* l);
 /*public*/ bool isResponseOK();
 /*public*/ QString getResponseCode();
 /*public*/ /*public*/ int value();
 /*public*/ bool isUnsolicited();

private:
 static Logger* log;

protected:
 /*protected*/ int skipPrefix(int index);

};

#endif // JMRICLIENTREPLY_H
