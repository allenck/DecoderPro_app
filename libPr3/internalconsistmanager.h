#ifndef INTERNALCONSISTMANAGER_H
#define INTERNALCONSISTMANAGER_H
#include "abstractconsistmanager.h"

class InternalConsistManager : public AbstractConsistManager
{
public:
 InternalConsistManager(QObject* parent = nullptr);
 /*public*/ bool isCommandStationConsistPossible();
 /*public*/ bool csConsistNeedsSeperateAddress();
 /*public*/ Consist* addConsist(LocoAddress* address);

};

#endif // INTERNALCONSISTMANAGER_H
