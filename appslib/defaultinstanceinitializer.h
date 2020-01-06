#ifndef DEFAULTINSTANCEINITIALIZER_H
#define DEFAULTINSTANCEINITIALIZER_H
#include "instanceinitializer.h"
#include "blockmanager.h"
#include "timebase.h"
#include "defaultidtagmanager.h"

class SectionManager;
class DefaultRouteManager;
//class DefaultIdTagManager;
class DefaultMemoryManager;
class DefaultClockControl;
class LIBPR3SHARED_EXPORT DefaultInstanceInitializer : public InstanceInitializer
{
 Q_OBJECT
public:
 DefaultInstanceInitializer();
 virtual QObject* getDefault(QString type) const;
private:
 static Logger* log;

};

#endif // DEFAULTINSTANCEINITIALIZER_H
