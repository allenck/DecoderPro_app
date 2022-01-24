#ifndef STANDALONEREPORTERMANAGER_H
#define STANDALONEREPORTERMANAGER_H
#include "rfidreportermanager.h"

class StandaloneReply;
class RfidMessage;
class RfidReply;
class RfidTrafficController;
class StandaloneReporterManager : public RfidReporterManager
{
public:
 StandaloneReporterManager(RfidSystemConnectionMemo* memo, QObject* parent = nullptr);
 /*public*/ void message(RfidMessage* m);
 /*public*/ /*synchronized*/ void reply(RfidReply* r);
 /*private*/ void processReply(StandaloneReply* r);


private:
 /*private*/ /*final*/ RfidTrafficController* tc;
 /*private*/ /*final*/ QString prefix;
 /*private*/ void attach();
 static Logger* log;
QObject* self() override {return (QObject*)this;}
protected:
 /*protected*/ Reporter* createNewReporter(QString systemName, QString userName);

};

#endif // STANDALONEREPORTERMANAGER_H
