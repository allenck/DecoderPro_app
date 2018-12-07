#ifndef COREIDRFIDPROTOCOL_H
#define COREIDRFIDPROTOCOL_H
#include "rfidprotocol.h"

class CoreIdRfidProtocol : public RfidProtocol
{
public:
 CoreIdRfidProtocol(QObject* parent = nullptr);
 /*public*/ CoreIdRfidProtocol(char concentratorFirst, char concentratorLast, int portPosition, QObject* parent = nullptr);
 /*public*/ static /*final*/ int getMaxSize();
 /*public*/ QString initString();
 /*public*/ QString getTag(AbstractMRReply*msg);
 /*public*/ bool providesChecksum();
 /*public*/ QString getCheckSum(AbstractMRReply*msg);
 /*public*/ bool isValid(AbstractMRReply*msg);
 /*public*/ bool isCheckSumValid(AbstractMRReply*msg);
 /*public*/ bool endOfMessage(AbstractMRReply* msg);
 /*public*/ QString toMonitorString(AbstractMRReply*msg);

private:
 /*private*/ static /*final*/ int SPECIFICMAXSIZE;// = 16;
 static Logger* log;
};
#endif // COREIDRFIDPROTOCOL_H
