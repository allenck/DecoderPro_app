#ifndef ID12LARFIDPROTOCOL_H
#define ID12LARFIDPROTOCOL_H
#include "rfidprotocol.h"

class Id12LARfidProtocol : public RfidProtocol
{
public:
 Id12LARfidProtocol(QObject* parent = nullptr);
 /*public*/ static /*final*/ int SPECIFICMAXSIZE;// = 16;
 /*public*/ static /*final*/ int getMaxSize();
 /*public*/ QString initString();
 /*public*/ QString getTag(AbstractMRReply* msg);
 /*public*/ QString getCheckSum(AbstractMRReply* msg);
 /*public*/ bool isValid(AbstractMRReply* msg);
 /*public*/ bool endOfMessage(AbstractMRReply* msg);
 /*public*/ QString toMonitorString(AbstractMRReply* msg);

private:
 static Logger* log;
};
#endif // ID12LARFIDPROTOCOL_H
