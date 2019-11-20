#ifndef MOCKSHUTDOWNMANAGER_H
#define MOCKSHUTDOWNMANAGER_H
#include "defaultshutdownmanager.h"


class MockShutDownManager : public DefaultShutDownManager
{
public:
 MockShutDownManager(QObject* parent = nullptr);
 /*public*/ bool restart();
 /*public*/ bool shutdown();
 /*public*/ void resetShuttingDown();

};

#endif // MOCKSHUTDOWNMANAGER_H
