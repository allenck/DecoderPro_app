#ifndef STANDALONEREPLY_H
#define STANDALONEREPLY_H
#include "rfid/rfidreply.h"

class RfidProtocol;
class StandaloneReply : public RfidReply
{
 Q_OBJECT
public:
 /*public*/ StandaloneReply(RfidTrafficController* tc, QObject*parent = nullptr);
 /*public*/ StandaloneReply(RfidTrafficController* tc, QString s, QObject *parent = nullptr);
 /*public*/ StandaloneReply(RfidTrafficController *tc, RfidReply *l, QObject *parent = nullptr) ;
 /*public*/ QString toMonitorString();


private:
 RfidProtocol* pr = nullptr;

};

#endif // STANDALONEREPLY_H
