#ifndef INTERNALCONSISTMANAGER_H
#define INTERNALCONSISTMANAGER_H
#include "abstractconsistmanager.h"

class InternalConsistManager : public AbstractConsistManager
{
public:
 InternalConsistManager(QObject* parent = nullptr);
 /*public*/ bool isCommandStationConsistPossible();
 /*public*/ bool csConsistNeedsSeparateAddress();
 /*public*/ DccConsist *addConsist(locoAddress* address);

};

#endif // INTERNALCONSISTMANAGER_H
