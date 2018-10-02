#ifndef WIFICONSIST_H
#define WIFICONSIST_H
#include "dccconsist.h"

class WiFiConsist : public DccConsist
{
public:
 WiFiConsist(DccLocoAddress* address, QObject* parent = 0);
 /*public*/ void add(DccLocoAddress* loco, bool dirNorm) ;
 /*public*/ void remove(DccLocoAddress* loco) ;
 /*public*/ void sendConsistCommand(DccLocoAddress* loco, bool dirNorm, WiFiConsist* consist);

private:
     /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger(WiFiConsist);
};

#endif // WIFICONSIST_H
