#ifndef ROUTECONTROLLER_H
#define ROUTECONTROLLER_H
#include "abstractcontroller.h"
#include "namedbeanhandle.h"

class NamedBeanHandleManager;
class Logger;
class Route;
class Sensor;
class RouteManager;
class RouteController : public AbstractController
{
 Q_OBJECT
public:
 RouteController();
 /*public*/ void filterList();
 /*public*/ void sendTitles();
 /*public*/ void sendList();
 /*public*/ void _register();
 /*public*/ void deregister();

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* evt);

private:
 /*private*/ RouteManager* manager;// = null;
 /*private*/ QHash<NamedBeanHandle<Sensor*>*, Route*>* indication;    //  Monitor turnouts for aligned status
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("RouteController");
 bool verifyCreation();
 void handleMessage(QString message);

protected:
 /*protected*/ NamedBeanHandleManager* nbhm ;//= jmri.InstanceManager.getDefault(jmri.NamedBeanHandleManager.class);
friend class DeviceServer;
};

#endif // ROUTECONTROLLER_H
