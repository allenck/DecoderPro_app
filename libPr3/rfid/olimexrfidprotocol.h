#ifndef OLIMEXRFIDPROTOCOL_H
#define OLIMEXRFIDPROTOCOL_H
#include "rfidprotocol.h"

class OlimexRfidProtocol : public RfidProtocol
{
public:
 OlimexRfidProtocol(QObject* parent = nullptr);
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

#endif // OLIMEXRFIDPROTOCOL_H
