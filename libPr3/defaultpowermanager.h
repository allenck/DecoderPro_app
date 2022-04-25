#ifndef DEFAULTPOWERMANAGER_H
#define DEFAULTPOWERMANAGER_H
#include "abstractpowermanager.h"
#include "internalsystemconnectionmemo.h"

class SwingPropertyChangeSupport;
class DefaultPowerManager : public AbstractPowerManager
{
  Q_OBJECT
public:
 DefaultPowerManager(InternalSystemConnectionMemo* memo, QObject* parent=nullptr);
 /*public*/ void dispose()override;

};

#endif // DEFAULTPOWERMANAGER_H
