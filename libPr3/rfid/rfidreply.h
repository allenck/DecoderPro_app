#ifndef RFIDREPLY_H
#define RFIDREPLY_H
#include "abstractmrreply.h"

class RfidTrafficController;
class RfidReply : public AbstractMRReply
{
public:
 /*public*/ RfidReply(RfidTrafficController* tc, QObject* parent = nullptr) ;
 /*public*/ RfidReply(RfidTrafficController* tc, QString s, QObject* parent = nullptr);
 /*public*/ RfidReply(RfidTrafficController* tc, RfidReply* l, QObject* parent = nullptr);


protected:
 /*protected*/ RfidTrafficController* tc = nullptr;
  /*protected*/ int skipPrefix(int index);

};

#endif // RFIDREPLY_H
