#ifndef DEFAULTPOWERMANAGER_H
#define DEFAULTPOWERMANAGER_H
#include "abstractpowermanager.h"
#include "internalsystemconnectionmemo.h"

class SwingPropertyChangeSupport;
class DefaultPowerManager : public AbstractPowerManager
{
public:
 DefaultPowerManager(InternalSystemConnectionMemo* memo);
 /*public*/ void dispose();

};

#endif // DEFAULTPOWERMANAGER_H
